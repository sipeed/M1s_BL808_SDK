#include "lfs_c906.h"

#include <FreeRTOS_POSIX/errno.h>
#include <aos/kernel.h>
#include <lfs.h>
#include <sys/fcntl.h>
#include <sys/unistd.h>
#include <vfs.h>
#include <vfs_inode.h>
#include <vfs_register.h>

#include "m1s_c906_xram_flash.h"

#define LFS_MOUNTPOINT "/lfs"
// partion media
#define LFS_OFFSET_IN_FLASH (0x300000)

/*
 * @brief 从指定块内的某区域读数据
 * @param [in] lfs_config格式参数
 * @param [in] block 逻辑块索引号，从0开始
 * @param [in] off 块内偏移，该值需能被read_size整除
 * @param [out] 读出数据的输出缓冲区
 * @param [in] size
 * 要读取的字节数，该值需能被read_size整除，lfs在读取时会确保不会跨块；
 * @retval 0 成功, < 0 错误码
 */
static int lfs_spi_flash_read(const struct lfs_config *cfg, lfs_block_t block, lfs_off_t off, void *buffer,
                              lfs_size_t size)
{
    // check if read is valid
    LFS_ASSERT(off % cfg->read_size == 0);
    LFS_ASSERT(size % cfg->read_size == 0);
    LFS_ASSERT(block < cfg->block_count);
    return m1s_xram_flash_read(LFS_OFFSET_IN_FLASH + block * cfg->block_size + off, (uint32_t)buffer, size)
               ? LFS_ERR_IO
               : LFS_ERR_OK;
}

/*
 * @brief 将数据写入指定块内的某区域。该区域必须已经先被擦除过，可以返回
 * LFS_ERR_CORRUPT 表示该块已损坏
 * @param [in] lfs_config格式参数
 * @param [in] block 逻辑块索引号，从0开始
 * @param [in] off 块内偏移，该值需能被rprog_size整除
 * @param [in] 写入数据的缓冲区
 * @param [in] size
 * 要写入的字节数，该值需能被read_size整除，lfs在读取时会确保不会跨块；
 * @retval 0 成功, < 0 错误码
 */
static int lfs_spi_flash_prog(const struct lfs_config *cfg, lfs_block_t block, lfs_off_t off, const void *buffer,
                              lfs_size_t size)
{
    // check if write is valid
    LFS_ASSERT(off % cfg->prog_size == 0);
    LFS_ASSERT(size % cfg->prog_size == 0);
    LFS_ASSERT(block < cfg->block_count);
    return m1s_xram_flash_write(LFS_OFFSET_IN_FLASH + block * cfg->block_size + off, (uint32_t)buffer, size)
               ? LFS_ERR_IO
               : LFS_ERR_OK;
}

/*
 * @brief 擦除指定块。块在写入之前必须先被擦除过，被擦除块的状态是未定义
 * @param [in] lfs_config格式参数
 * @param [in] block 要擦除的逻辑块索引号，从0开始
 * @retval 0 成功, < 0 错误码
 */
static int lfs_spi_flash_erase(const struct lfs_config *cfg, lfs_block_t block)
{
    // check if erase is valid
    LFS_ASSERT(block < cfg->block_count);
    return m1s_xram_flash_erase(LFS_OFFSET_IN_FLASH + block * cfg->block_size, cfg->block_size) ? LFS_ERR_IO
                                                                                                : LFS_ERR_OK;
}

/*
 * @brief 对底层块设备做同步操作。若底层块设备不没有同步这项操作可以直接返回
 * @param [in] lfs_config格式参数;
 * @retval 0 成功, < 0 错误码
 */
static int lfs_spi_flash_sync(const struct lfs_config *cfg) { return LFS_ERR_OK; }

// configuration of the filesystem is provided by this struct
static struct lfs_config cfg = {
    // block device operations
    .read = lfs_spi_flash_read,
    .prog = lfs_spi_flash_prog,
    .erase = lfs_spi_flash_erase,
    .sync = lfs_spi_flash_sync,

    // block device configuration
    .read_size = 4096,
    .prog_size = 4096,
    .block_size = 4096,
    .block_count = 10 * 256, /* 10 MB */
    .cache_size = 4096,
    .lookahead_size = 8192,
    .block_cycles = 512,
};

/* ----------------------aos----------------------- */
#define CONFIG_LITTLEFS_CNT (1)

typedef aos_mutex_t lfs_lock_t;

typedef struct {
    struct lfs_config *config;
    lfs_t *lfs;
    lfs_lock_t *lock;
    char *mountpath;
    bool mounted;
} lfs_manager_t;

typedef struct _lfsvfs_dir_t {
    aos_dir_t dir;
    lfs_dir_t lfsdir;
    aos_dirent_t cur_dirent;
} lfsvfs_dir_t;

static lfs_manager_t *g_lfs_manager[CONFIG_LITTLEFS_CNT] = {
    [0] = NULL,
};

/* Global FS lock init */
static void lfs_lock_create(lfs_lock_t *lock)
{
    if (lock) {
        aos_mutex_new(lock);
        LFS_TRACE("%s: lock %p created", aos_task_name(), lock);
    }
}

/* Global FS lock destroy */
static void lfs_lock_destory(lfs_lock_t *lock)
{
    if (lock) {
        aos_mutex_free(lock);
        LFS_TRACE("%s: lock %p destroyed", aos_task_name(), lock);
    }
}

static void lfs_lock(lfs_lock_t *lock)
{
    if (lock) {
        aos_mutex_lock(lock, AOS_WAIT_FOREVER);
        LFS_TRACE("%s: lock %p locked", aos_task_name(), lock);
    }
}

static void lfs_unlock(lfs_lock_t *lock)
{
    if (lock) {
        LFS_TRACE("%s: lock %p to be unlocked", aos_task_name(), lock);
        aos_mutex_unlock(lock);
    }
}

static int vfs_to_lfs_idx(file_t *vfs)
{
    int i = 0;
    char *name;

    if (!vfs) return -1;

    LFS_ASSERT(vfs->node != NULL);
    name = vfs->node->i_name;
    LFS_ASSERT(name != NULL);

    while (i < CONFIG_LITTLEFS_CNT) {
        if (!memcmp(g_lfs_manager[i]->mountpath, name, strlen(name))) {
            /* return error for unounted fs */
            if (g_lfs_manager[i]->mounted == false) {
                LFS_ERROR("Something was wrong, parition %s is unmounted now.", name);
                return -1;
            }
            return i;
        } else {
            i++;
        }
    }

    return -1;
}

/* Relative path convert */
static char *path_convert(const char *path, int *idx)
{
    int i;
    int32_t len, prefix;
    char *target_path, *p, *mountpath;

    if (path == NULL) {
        return NULL;
    }

    len = strlen(path);

    for (i = 0; i < CONFIG_LITTLEFS_CNT; i++) {
        LFS_ASSERT(g_lfs_manager[i]->mountpath != NULL);
        mountpath = g_lfs_manager[i]->mountpath;

        prefix = strlen(mountpath);
        if (strncmp(mountpath, path, prefix) != 0) {
            continue;
        } else {
            *idx = i;
            break;
        }
    }

    if (i >= CONFIG_LITTLEFS_CNT) {
        *idx = -1;
        return NULL;
    } else {
        /* return error for unounted fs */
        if (g_lfs_manager[i]->mounted == false) {
            LFS_ERROR("Something was wrong, parition %s is unmounted now.", path);
            *idx = -1;
            return NULL;
        }
    }

    len = len - prefix;
    target_path = (char *)lfs_malloc(len + 1);
    if (target_path == NULL) {
        return NULL;
    }

    memset(target_path, 0, len + 1);
    if (len > 0) {
        if (0 == strcmp(mountpath, "/")) {
            p = (char *)(path + prefix);
            memcpy(target_path, p, len);
        } else {
            p = (char *)(path + prefix + 1);
            memcpy(target_path, p, len - 1);
        }
    }

    target_path[len] = '\0';
    return target_path;
}

static int32_t mode_convert(int32_t flags)
{
    int32_t mode, res = 0;

    mode = flags & O_ACCMODE;
    if (mode == O_RDONLY) {
        res |= LFS_O_RDONLY;
    } else if (mode == O_WRONLY) {
        res |= LFS_O_WRONLY;
    } else if (mode == O_RDWR) {
        res |= LFS_O_RDWR;
    }

    if (flags & O_CREAT) {
        res |= LFS_O_CREAT;
    }
    if (flags & O_EXCL) {
        res |= LFS_O_EXCL;
    }
    if (flags & O_TRUNC) {
        res |= LFS_O_TRUNC;
    }
    if (flags & O_APPEND) {
        res |= LFS_O_CREAT | LFS_O_APPEND;
    }
    return res;
}

static int lfs_ret_value_convert(int lfs_ret)
{
    int ret;

    if (lfs_ret > 0) {
        return lfs_ret;
    }

    switch (lfs_ret) {
        case LFS_ERR_OK:
            ret = 0;
            break;
        case LFS_ERR_IO:
            ret = -EIO;
            break;
        case LFS_ERR_CORRUPT:
            ret = -EIO;
            break;
        case LFS_ERR_NOENT:
            ret = -ENOENT;
            break;
        case LFS_ERR_EXIST:
            ret = -EEXIST;
            break;
        case LFS_ERR_NOTDIR:
            ret = -ENOTDIR;
            break;
        case LFS_ERR_ISDIR:
            ret = -EISDIR;
            break;
        case LFS_ERR_NOTEMPTY:
            ret = -ENOTEMPTY;
            break;
        case LFS_ERR_BADF:
            ret = -EBADF;
            break;
        case LFS_ERR_FBIG:
            ret = -EFBIG;
            break;
        case LFS_ERR_INVAL:
            ret = -EINVAL;
            break;
        case LFS_ERR_NOSPC:
            ret = -ENOSPC;
            break;
        case LFS_ERR_NOMEM:
            ret = -ENOMEM;
            break;
        case LFS_ERR_NOATTR:
            ret = -ENODATA;
            break;
        case LFS_ERR_NAMETOOLONG:
            ret = -ENAMETOOLONG;
            break;
        default:
            ret = lfs_ret;
            break;
    }

    return ret;
}

static int lfs_vfs_open(file_t *fp, const char *path, int flags)
{
    int ret;
    char *target_path = NULL;
    lfs_file_t *file = NULL;

    int idx;
    target_path = path_convert(path, &idx);
    if (target_path == NULL || idx < 0) {
        return -EINVAL;
    }

    if (!strlen(target_path)) {
        return -EINVAL;
    }

#ifdef CONFIG_LFS_SYSTEM_READONLY
    if ((idx == 1) && ((flags & O_ACCMODE) != O_RDONLY)) {
        LFS_ERROR(
            "Failed to open %s due to unacceptable flags %d, "
            "this partition is readonly!",
            path, flags);
        return -EINVAL;
    }
#endif

    file = (lfs_file_t *)lfs_malloc(sizeof(lfs_file_t));
    if (file == NULL) {
        lfs_free(target_path);
        return -EINVAL;
    }

    lfs_lock(g_lfs_manager[idx]->lock);

    ret = lfs_file_open(g_lfs_manager[idx]->lfs, file, target_path, mode_convert(flags));
    lfs_unlock(g_lfs_manager[idx]->lock);

    ret = lfs_ret_value_convert(ret);
    if (ret < 0) {
        LFS_DEBUG("%s %s failed, ret - %d", __func__, path, ret);
        lfs_free(target_path);
        lfs_free(file);
        return ret;
    } else {
        fp->f_arg = (void *)file;
    }

    lfs_free(target_path);

    return ret;
}

static int lfs_vfs_close(file_t *fp)
{
    int ret;
    lfs_file_t *file = (lfs_file_t *)(fp->f_arg);

    int idx;
    idx = vfs_to_lfs_idx(fp);
    if (idx < 0 || idx >= CONFIG_LITTLEFS_CNT) return -1;

    lfs_lock(g_lfs_manager[idx]->lock);
    ret = lfs_file_close(g_lfs_manager[idx]->lfs, file);
    lfs_unlock(g_lfs_manager[idx]->lock);

    ret = lfs_ret_value_convert(ret);
    if (ret < 0) {
        LFS_DEBUG("%s failed, ret - %d", __func__, ret);
        return ret;
    }

    lfs_free(file);

    return ret;
}

static int32_t lfs_vfs_read(file_t *fp, char *buf, uint32_t len)
{
    int ret;

    lfs_file_t *file = (lfs_file_t *)(fp->f_arg);

    int idx;
    idx = vfs_to_lfs_idx(fp);
    if (idx < 0 || idx >= CONFIG_LITTLEFS_CNT) return -1;

    lfs_lock(g_lfs_manager[idx]->lock);
    ret = lfs_file_read(g_lfs_manager[idx]->lfs, file, buf, len);
    lfs_unlock(g_lfs_manager[idx]->lock);

    if (ret < LFS_ERR_OK) LFS_DEBUG("%s return %d", __func__, ret);
    return lfs_ret_value_convert(ret);
}

static int32_t lfs_vfs_write(file_t *fp, const char *buf, uint32_t len)
{
    int ret;

    lfs_file_t *file = (lfs_file_t *)(fp->f_arg);

    int idx;
    idx = vfs_to_lfs_idx(fp);
    if (idx < 0 || idx >= CONFIG_LITTLEFS_CNT) return -1;

#ifdef CONFIG_LFS_SYSTEM_READONLY
    if (idx == 1) {
        LFS_ERROR(
            "Failed to write(len: %d) since "
            "this partition is readonly!",
            len);
        return -EINVAL;
    }
#endif

    lfs_lock(g_lfs_manager[idx]->lock);
    ret = lfs_file_write(g_lfs_manager[idx]->lfs, file, buf, len);
    lfs_unlock(g_lfs_manager[idx]->lock);

    if (ret < LFS_ERR_OK) LFS_DEBUG("%s return %d", __func__, ret);
    return lfs_ret_value_convert(ret);
}

static uint32_t lfs_vfs_lseek(file_t *fp, int64_t off, int32_t whence)
{
    int32_t ret;

    lfs_file_t *file = (lfs_file_t *)(fp->f_arg);

    int idx;
    idx = vfs_to_lfs_idx(fp);
    if (idx < 0 || idx >= CONFIG_LITTLEFS_CNT) return -1;

    lfs_lock(g_lfs_manager[idx]->lock);
    ret = lfs_file_seek(g_lfs_manager[idx]->lfs, file, off, whence);
    lfs_unlock(g_lfs_manager[idx]->lock);

    return lfs_ret_value_convert(ret);
}

static int32_t lfs_vfs_sync(file_t *fp)
{
    int ret;

    lfs_file_t *file = (lfs_file_t *)(fp->f_arg);

    int idx;
    idx = vfs_to_lfs_idx(fp);
    if (idx < 0 || idx >= CONFIG_LITTLEFS_CNT) return -1;

    lfs_lock(g_lfs_manager[idx]->lock);
    ret = lfs_file_sync(g_lfs_manager[idx]->lfs, file);
    lfs_unlock(g_lfs_manager[idx]->lock);

    return lfs_ret_value_convert(ret);
}

static int32_t lfs_vfs_stat(file_t *fp, const char *path, struct stat *st)
{
    struct lfs_info s;
    int ret;
    char *target_path = NULL;

    int idx;
    target_path = path_convert(path, &idx);
    if (target_path == NULL) {
        return -EINVAL;
    }

    lfs_lock(g_lfs_manager[idx]->lock);
    ret = lfs_stat(g_lfs_manager[idx]->lfs, target_path, &s);
    lfs_unlock(g_lfs_manager[idx]->lock);

    ret = lfs_ret_value_convert(ret);
    if (ret == 0) {
        st->st_size = (s.type == LFS_TYPE_DIR) ? 0 : s.size;
        st->st_mode = S_IRWXU | S_IRWXG | S_IRWXO | ((s.type == LFS_TYPE_DIR ? S_IFDIR : S_IFREG));
#ifdef FS_TIMESTAMP_WORKAROUND
        time_t t = time(NULL);
        st->st_actime = t;
        st->st_modtime = t;
#endif
    }

    lfs_free(target_path);

    return ret;
}

static int32_t lfs_vfs_access(file_t *fp, const char *path, int mode)
{
    struct stat s;
    int ret;

    ret = lfs_vfs_stat(fp, path, &s);
    ret = lfs_ret_value_convert(ret);
    if (ret == 0) {
        switch (mode) {
            case F_OK:
                return 0;
            case R_OK:
                return s.st_mode & S_IRUSR ? 0 : 1;
            case W_OK:
                return s.st_mode & S_IWUSR ? 0 : 1;
            case X_OK:
                return s.st_mode & S_IXUSR ? 0 : 1;
        }
    }

    return ret;
}

static int32_t lfs_vfs_statfs(file_t *fp, const char *path, struct statfs *sfs)
{
    int32_t block_used;
    int ret;

    int idx;
    idx = vfs_to_lfs_idx(fp);
    if (idx < 0 || idx >= CONFIG_LITTLEFS_CNT) return -1;

    lfs_lock(g_lfs_manager[idx]->lock);
    ret = lfs_fs_size(g_lfs_manager[idx]->lfs);
    lfs_unlock(g_lfs_manager[idx]->lock);
    ret = lfs_ret_value_convert(ret);
    if (ret >= 0) {
        block_used = ret;
        memset(sfs, 0, sizeof(struct statfs));
        sfs->f_type = 0xd3fc;
        sfs->f_bsize = g_lfs_manager[idx]->config->block_size;
        sfs->f_blocks = g_lfs_manager[idx]->config->block_count;
        sfs->f_bfree = g_lfs_manager[idx]->config->block_count - block_used;
        sfs->f_bavail = sfs->f_bfree;
        sfs->f_files = 1024;
    }

    return ret;
}

static int32_t lfs_vfs_remove(file_t *fp, const char *path)
{
    int ret;
    char *target_path = NULL;

    int idx;
    target_path = path_convert(path, &idx);
    if (target_path == NULL) {
        return -EINVAL;
    }

#ifdef CONFIG_LFS_SYSTEM_READONLY
    if (idx == 1) {
        LFS_ERROR(
            "Failed to remove %s since "
            "this partition is readonly!",
            path);
        return -EINVAL;
    }
#endif

    lfs_lock(g_lfs_manager[idx]->lock);
    ret = lfs_remove(g_lfs_manager[idx]->lfs, target_path);
    lfs_unlock(g_lfs_manager[idx]->lock);

    if (ret < LFS_ERR_OK) LFS_DEBUG("%s %s return %d", __func__, path, ret);
    ret = lfs_ret_value_convert(ret);

    lfs_free(target_path);

    return ret;
}

static int32_t lfs_vfs_rename(file_t *fp, const char *oldpath, const char *newpath)
{
    int32_t ret;

    char *oldname = NULL;
    char *newname = NULL;

    int idx;
    oldname = path_convert(oldpath, &idx);
    if (!oldname) {
        return -EINVAL;
    }

#ifdef CONFIG_LFS_SYSTEM_READONLY
    if (idx == 1) {
        LFS_ERROR(
            "Failed to rename from %s since "
            "this partition is readonly!",
            oldpath);
        return -EINVAL;
    }
#endif

    newname = path_convert(newpath, &idx);
    if (!newname) {
        lfs_free(oldname);
        return -EINVAL;
    }

#ifdef CONFIG_LFS_SYSTEM_READONLY
    if (idx == 1) {
        LFS_ERROR(
            "Failed to rename to %s since "
            "this partition is readonly!",
            newpath);
        return -EINVAL;
    }
#endif

    idx = vfs_to_lfs_idx(fp);
    if (idx < 0 || idx >= CONFIG_LITTLEFS_CNT) return -1;

    lfs_lock(g_lfs_manager[idx]->lock);
    ret = lfs_rename(g_lfs_manager[idx]->lfs, oldname, newname);
    lfs_unlock(g_lfs_manager[idx]->lock);

    if (ret < LFS_ERR_OK) LFS_DEBUG("%s %s->%s return %d", __func__, oldpath, newpath, ret);
    ret = lfs_ret_value_convert(ret);

    lfs_free(oldname);
    lfs_free(newname);

    return ret;
}

static aos_dir_t *lfs_vfs_opendir(file_t *fp, const char *path)
{
    lfsvfs_dir_t *lfsvfs_dir = NULL;
    char *relpath = NULL;
    int32_t ret;

    int idx;
    relpath = path_convert(path, &idx);
    if (!relpath) {
        return NULL;
    }

    lfsvfs_dir = (lfsvfs_dir_t *)lfs_malloc(sizeof(lfsvfs_dir_t) + LFS_NAME_MAX + 1);
    if (!lfsvfs_dir) {
#ifdef CONFIG_VFS_USE_ERRNO
        errno = ENOMEM;
#endif
        lfs_free(relpath);
        return NULL;
    }

    memset(lfsvfs_dir, 0, sizeof(lfsvfs_dir_t) + LFS_NAME_MAX + 1);

    lfs_lock(g_lfs_manager[idx]->lock);
    ret = lfs_dir_open(g_lfs_manager[idx]->lfs, &lfsvfs_dir->lfsdir, relpath);
    lfs_unlock(g_lfs_manager[idx]->lock);

    if (ret < LFS_ERR_OK) LFS_DEBUG("%s return %d", __func__, ret);
    ret = lfs_ret_value_convert(ret);
    if (ret < 0) {
#ifdef CONFIG_VFS_USE_ERRNO
        errno = -ret;
#endif
        lfs_free(relpath);
        lfs_free(lfsvfs_dir);
        return NULL;
    } else {
        fp->f_arg = (void *)lfsvfs_dir;
    }

    lfs_free(relpath);

    return (aos_dir_t *)lfsvfs_dir;
}

static aos_dirent_t *lfs_vfs_readdir(file_t *fp, aos_dir_t *dir)
{
    lfsvfs_dir_t *lfsvfs_dir = (lfsvfs_dir_t *)dir;
    struct lfs_info info;
    int32_t ret;

    if (!lfsvfs_dir) {
        return NULL;
    }

    int idx;
    idx = vfs_to_lfs_idx(fp);
    if (idx < 0 || idx >= CONFIG_LITTLEFS_CNT) return NULL;

    lfs_lock(g_lfs_manager[idx]->lock);
    ret = lfs_dir_read(g_lfs_manager[idx]->lfs, &lfsvfs_dir->lfsdir, &info);
    lfs_unlock(g_lfs_manager[idx]->lock);

    if (ret != true) {
        ret = lfs_ret_value_convert(ret);
#ifdef CONFIG_VFS_USE_ERRNO
        errno = -ret;
#endif
        return NULL;
    }

    if (info.name[0] == 0) {
#ifdef CONFIG_VFS_USE_ERRNO
        errno = EINVAL;
#endif
        return NULL;
    }

    lfsvfs_dir->cur_dirent.d_ino = 0;
    lfsvfs_dir->cur_dirent.d_type = info.type;
    strncpy(lfsvfs_dir->cur_dirent.d_name, info.name, LFS_NAME_MAX);
    lfsvfs_dir->cur_dirent.d_name[LFS_NAME_MAX] = '\0';

    return &lfsvfs_dir->cur_dirent;
}

static int32_t lfs_vfs_closedir(file_t *fp, aos_dir_t *dir)
{
    lfsvfs_dir_t *lfsvfs_dir = (lfsvfs_dir_t *)dir;
    int32_t ret;

    if (!lfsvfs_dir) {
        return -EINVAL;
    }

    int idx;
    idx = vfs_to_lfs_idx(fp);
    if (idx < 0 || idx >= CONFIG_LITTLEFS_CNT) return -1;

    lfs_lock(g_lfs_manager[idx]->lock);
    ret = lfs_dir_close(g_lfs_manager[idx]->lfs, &lfsvfs_dir->lfsdir);
    lfs_unlock(g_lfs_manager[idx]->lock);

    if (ret < LFS_ERR_OK) LFS_DEBUG("%s return %d", __func__, ret);
    ret = lfs_ret_value_convert(ret);
    if (ret < 0) {
        return ret;
    }

    lfs_free(lfsvfs_dir);

    return ret;
}

static int32_t lfs_vfs_mkdir(file_t *fp, const char *path)
{
    int32_t ret;
    char *pathname = NULL;

    int idx;
    pathname = path_convert(path, &idx);
    if (!pathname) {
        return -EINVAL;
    }

#ifdef CONFIG_LFS_SYSTEM_READONLY
    if (idx == 1) {
        LFS_ERROR(
            "Failed to rename to %s since "
            "this partition is readonly!",
            path);
        return -EINVAL;
    }
#endif

    lfs_lock(g_lfs_manager[idx]->lock);
    ret = lfs_mkdir(g_lfs_manager[idx]->lfs, pathname);
    lfs_unlock(g_lfs_manager[idx]->lock);

    if ((ret < LFS_ERR_OK) && (ret != LFS_ERR_EXIST)) {
        LFS_DEBUG("%s %s return %d", __func__, path, ret);
    }

    ret = lfs_ret_value_convert(ret);

    lfs_free(pathname);

    return ret;
}

static int32_t lfs_vfs_rmdir(file_t *fp, const char *path)
{
    int32_t ret;
    char *pathname = NULL;

    int idx;
    pathname = path_convert(path, &idx);
    if (!pathname) {
        return -EINVAL;
    }

#ifdef CONFIG_LFS_SYSTEM_READONLY
    if (idx == 1) {
        LFS_ERROR(
            "Failed to remove dir %s since "
            "this partition is readonly!",
            path);
        return -EINVAL;
    }
#endif

    lfs_lock(g_lfs_manager[idx]->lock);
    ret = lfs_remove(g_lfs_manager[idx]->lfs, pathname);
    lfs_unlock(g_lfs_manager[idx]->lock);

    if (ret < LFS_ERR_OK) LFS_DEBUG("%s %s return %d", __func__, path, ret);
    ret = lfs_ret_value_convert(ret);

    lfs_free(pathname);

    return ret;
}

static void lfs_vfs_rewinddir(file_t *fp, aos_dir_t *dir)
{
    lfsvfs_dir_t *lfsvfs_dir = (lfsvfs_dir_t *)dir;

    if (!lfsvfs_dir) {
        return;
    }

    int idx;
    idx = vfs_to_lfs_idx(fp);
    if (idx < 0 || idx >= CONFIG_LITTLEFS_CNT) return;

    lfs_lock(g_lfs_manager[idx]->lock);
    lfs_dir_rewind(g_lfs_manager[idx]->lfs, &lfsvfs_dir->lfsdir);
    lfs_unlock(g_lfs_manager[idx]->lock);
}

static int32_t lfs_vfs_telldir(file_t *fp, aos_dir_t *dir)
{
    lfsvfs_dir_t *lfsvfs_dir = (lfsvfs_dir_t *)dir;
    int32_t ret;

    if (!lfsvfs_dir) {
        return -EINVAL;
    }

    int idx;
    idx = vfs_to_lfs_idx(fp);
    if (idx < 0 || idx >= CONFIG_LITTLEFS_CNT) return -1;

    lfs_lock(g_lfs_manager[idx]->lock);
    ret = lfs_dir_tell(g_lfs_manager[idx]->lfs, &lfsvfs_dir->lfsdir);
    lfs_unlock(g_lfs_manager[idx]->lock);

    return lfs_ret_value_convert(ret);
}

static void lfs_vfs_seekdir(file_t *fp, aos_dir_t *dir, int32_t loc)
{
    lfsvfs_dir_t *lfsvfs_dir = (lfsvfs_dir_t *)dir;

    if (!lfsvfs_dir) {
        return;
    }

    int idx;
    idx = vfs_to_lfs_idx(fp);
    if (idx < 0 || idx >= CONFIG_LITTLEFS_CNT) return;

    lfs_lock(g_lfs_manager[idx]->lock);
    lfs_dir_seek(g_lfs_manager[idx]->lfs, &lfsvfs_dir->lfsdir, (lfs_off_t)loc);
    lfs_unlock(g_lfs_manager[idx]->lock);
}
static fs_ops_t lfs_vfs_ops = {
    .open = &lfs_vfs_open,
    .close = &lfs_vfs_close,
    .read = &lfs_vfs_read,
    .write = &lfs_vfs_write,
    .lseek = &lfs_vfs_lseek,
    .sync = &lfs_vfs_sync,
    .stat = &lfs_vfs_stat,
    .unlink = &lfs_vfs_remove,
    .rename = &lfs_vfs_rename,
    .access = &lfs_vfs_access,
    .statfs = &lfs_vfs_statfs,
    .opendir = &lfs_vfs_opendir,
    .readdir = &lfs_vfs_readdir,
    .closedir = &lfs_vfs_closedir,
    .mkdir = &lfs_vfs_mkdir,
    .rmdir = &lfs_vfs_rmdir,
    .rewinddir = &lfs_vfs_rewinddir,
    .telldir = &lfs_vfs_telldir,
    .seekdir = &lfs_vfs_seekdir,
    .ioctl = NULL,
};

int lfs_register(void)
{
    g_lfs_manager[0] = lfs_malloc(sizeof(lfs_manager_t));

    memset(g_lfs_manager[0], 0, sizeof(lfs_manager_t));
    g_lfs_manager[0]->config = &cfg;
    g_lfs_manager[0]->lfs = malloc(sizeof(lfs_t));
    g_lfs_manager[0]->mountpath = LFS_MOUNTPOINT;

    // mount the filesystem
    if (LFS_ERR_OK != lfs_mount(g_lfs_manager[0]->lfs, g_lfs_manager[0]->config)) {
        // reformat if we can't mount the filesystem
        // this should only happen on the first boot
        lfs_format(g_lfs_manager[0]->lfs, g_lfs_manager[0]->config);
        if (LFS_ERR_OK != lfs_mount(g_lfs_manager[0]->lfs, g_lfs_manager[0]->config)) return -1;
    }
    g_lfs_manager[0]->mounted = true;
    g_lfs_manager[0]->lock = (lfs_lock_t *)lfs_malloc(sizeof(lfs_lock_t));
    lfs_lock_create(g_lfs_manager[0]->lock);
    return aos_register_fs(g_lfs_manager[0]->mountpath, &lfs_vfs_ops, NULL);
}

int lfs_unregister(void)
{
    int ret = -1;
    ret = aos_unregister_fs(g_lfs_manager[0]->mountpath);
    g_lfs_manager[0]->mounted = false;
    lfs_lock_destory(g_lfs_manager[0]->lock);
    lfs_free(g_lfs_manager[0]->lock);
    ret = lfs_unmount(g_lfs_manager[0]->lfs);
    lfs_free(g_lfs_manager[0]->lfs);
    lfs_free(g_lfs_manager[0]);
    g_lfs_manager[0] = NULL;
    // release any resources we were using
    return ret;
}

#if 0
void TestLFS()
{
    lfs_t *lfs = g_lfs_manager[0]->lfs;
    lfs_file_t file;

    // read current count
    uint32_t boot_count = 0;
    lfs_file_open(lfs, &file, "boot_count", LFS_O_RDWR | LFS_O_CREAT);
    lfs_file_read(lfs, &file, &boot_count, sizeof(boot_count));

    // update boot count
    boot_count += 1;
    lfs_file_rewind(lfs, &file);
    lfs_file_write(lfs, &file, &boot_count, sizeof(boot_count));

    // remember the storage is not updated until the file is closed successfully
    lfs_file_close(lfs, &file);

    // release any resources we were using
    lfs_unmount(lfs);

    // print the boot count
    printf("boot_count: %d\n", boot_count);
}
#endif