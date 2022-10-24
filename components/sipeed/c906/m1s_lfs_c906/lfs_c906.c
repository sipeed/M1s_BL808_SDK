#include "lfs_c906.h"

#include <FreeRTOS_POSIX/errno.h>
#include <aos/kernel.h>
#include <lfs.h>
#include <sys/fcntl.h>
#include <vfs.h>
#include <vfs_inode.h>
#include <vfs_register.h>

#include "m1s_c906_xram_flash.h"

#define LFS_MOUNTPOINT "/lfs"
// partion media
#define LFS_OFFSET_IN_FLASH (0x300000)

// variables used by the filesystem
static lfs_t lfs;

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
static int lfs_spi_flash_read(const struct lfs_config *cfg, lfs_block_t block,
                              lfs_off_t off, void *buffer, lfs_size_t size) {
  // check if read is valid
  LFS_ASSERT(off % cfg->read_size == 0);
  LFS_ASSERT(size % cfg->read_size == 0);
  LFS_ASSERT(block < cfg->block_count);
  return m1s_xram_flash_read(
             LFS_OFFSET_IN_FLASH + block * cfg->block_size + off,
             (uint32_t)buffer, size)
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
static int lfs_spi_flash_prog(const struct lfs_config *cfg, lfs_block_t block,
                              lfs_off_t off, const void *buffer,
                              lfs_size_t size) {
  // check if write is valid
  LFS_ASSERT(off % cfg->prog_size == 0);
  LFS_ASSERT(size % cfg->prog_size == 0);
  LFS_ASSERT(block < cfg->block_count);
  return m1s_xram_flash_write(
             LFS_OFFSET_IN_FLASH + block * cfg->block_size + off,
             (uint32_t)buffer, size)
             ? LFS_ERR_IO
             : LFS_ERR_OK;
}

/*
 * @brief 擦除指定块。块在写入之前必须先被擦除过，被擦除块的状态是未定义
 * @param [in] lfs_config格式参数
 * @param [in] block 要擦除的逻辑块索引号，从0开始
 * @retval 0 成功, < 0 错误码
 */
static int lfs_spi_flash_erase(const struct lfs_config *cfg,
                               lfs_block_t block) {
  // check if erase is valid
  LFS_ASSERT(block < cfg->block_count);
  return m1s_xram_flash_erase(LFS_OFFSET_IN_FLASH, block * cfg->block_size)
             ? LFS_ERR_IO
             : LFS_ERR_OK;
}

/*
 * @brief 对底层块设备做同步操作。若底层块设备不没有同步这项操作可以直接返回
 * @param [in] lfs_config格式参数;
 * @retval 0 成功, < 0 错误码
 */
static int lfs_spi_flash_sync(const struct lfs_config *cfg) {
  return LFS_ERR_OK;
}

// configuration of the filesystem is provided by this struct
static struct lfs_config cfg = {
    // block device operations
    .read = lfs_spi_flash_read,
    .prog = lfs_spi_flash_prog,
    .erase = lfs_spi_flash_erase,
    .sync = lfs_spi_flash_sync,

    // block device configuration
    .read_size = 64,
    .prog_size = 64,
    .block_size = 4096,
    .block_count = 256,
    .cache_size = 64,
    .lookahead_size = 64,
    .block_cycles = 500,
};

/* ----------------------aos----------------------- */
#define CONFIG_LITTLEFS_CNT (1)

typedef struct {
  struct lfs_config *config;
  lfs_t *lfs;
  // lfs_lock_t *lock;
  char *mountpath;
  bool mounted;
} lfs_manager_t;

static lfs_manager_t g_lfs_manager[CONFIG_LITTLEFS_CNT] = {
    [0] =
        {
            .config = &cfg,
            .lfs = &lfs,
            .mountpath = LFS_MOUNTPOINT,
            .mounted = 0,
        },
};

static int vfs_to_lfs_idx(file_t *vfs) {
  int i = 0;
  char *name;

  if (!vfs) return -1;

  LFS_ASSERT(vfs->node != NULL);
  name = vfs->node->i_name;
  LFS_ASSERT(name != NULL);

  while (i < CONFIG_LITTLEFS_CNT) {
    if (!memcmp(g_lfs_manager[i].mountpath, name, strlen(name))) {
      /* return error for unounted fs */
      if (g_lfs_manager[i].mounted == false) {
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
static char *path_convert(const char *path, int *idx) {
  int i;
  int32_t len, prefix;
  char *target_path, *p, *mountpath;

  if (path == NULL) {
    return NULL;
  }

  len = strlen(path);

  for (i = 0; i < CONFIG_LITTLEFS_CNT; i++) {
    LFS_ASSERT(g_lfs_manager[i].mountpath != NULL);
    mountpath = g_lfs_manager[i].mountpath;

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
    if (g_lfs_manager[i].mounted == false) {
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

static int32_t mode_convert(int32_t flags) {
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

static int lfs_ret_value_convert(int lfs_ret) {
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

static int lfs_vfs_open(file_t *fp, const char *path, int flags) {
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

  // lfs_lock(g_lfs_manager[idx].lock);

  ret = lfs_file_open(g_lfs_manager[idx].lfs, file, target_path,
                      mode_convert(flags));
  // lfs_unlock(g_lfs_manager[idx].lock);

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

static int lfs_vfs_close(file_t *fp) {
  int ret;
  lfs_file_t *file = (lfs_file_t *)(fp->f_arg);

  int idx;
  idx = vfs_to_lfs_idx(fp);
  if (idx < 0 || idx >= CONFIG_LITTLEFS_CNT) return -1;

  // lfs_lock(g_lfs_manager[idx].lock);
  ret = lfs_file_close(g_lfs_manager[idx].lfs, file);
  // lfs_unlock(g_lfs_manager[idx].lock);

  ret = lfs_ret_value_convert(ret);
  if (ret < 0) {
    LFS_DEBUG("%s failed, ret - %d", __func__, ret);
    return ret;
  }

  lfs_free(file);

  return ret;
}

static int32_t lfs_vfs_read(file_t *fp, char *buf, uint32_t len) {
  int ret;

  lfs_file_t *file = (lfs_file_t *)(fp->f_arg);

  int idx;
  idx = vfs_to_lfs_idx(fp);
  if (idx < 0 || idx >= CONFIG_LITTLEFS_CNT) return -1;

  // lfs_lock(g_lfs_manager[idx].lock);
  ret = lfs_file_read(g_lfs_manager[idx].lfs, file, buf, len);
  // lfs_unlock(g_lfs_manager[idx].lock);

  if (ret < LFS_ERR_OK) LFS_DEBUG("%s return %d", __func__, ret);
  return lfs_ret_value_convert(ret);
}

static int32_t lfs_vfs_write(file_t *fp, const char *buf, uint32_t len) {
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

  // lfs_lock(g_lfs_manager[idx].lock);
  ret = lfs_file_write(g_lfs_manager[idx].lfs, file, buf, len);
  // lfs_unlock(g_lfs_manager[idx].lock);

  if (ret < LFS_ERR_OK) LFS_DEBUG("%s return %d", __func__, ret);
  return lfs_ret_value_convert(ret);
}

static uint32_t lfs_vfs_lseek(file_t *fp, int64_t off, int32_t whence) {
  int32_t ret;

  lfs_file_t *file = (lfs_file_t *)(fp->f_arg);

  int idx;
  idx = vfs_to_lfs_idx(fp);
  if (idx < 0 || idx >= CONFIG_LITTLEFS_CNT) return -1;

  // lfs_lock(g_lfs_manager[idx].lock);
  ret = lfs_file_seek(g_lfs_manager[idx].lfs, file, off, whence);
  // lfs_unlock(g_lfs_manager[idx].lock);

  return lfs_ret_value_convert(ret);
}

static int32_t lfs_vfs_sync(file_t *fp) {
  int ret;

  lfs_file_t *file = (lfs_file_t *)(fp->f_arg);

  int idx;
  idx = vfs_to_lfs_idx(fp);
  if (idx < 0 || idx >= CONFIG_LITTLEFS_CNT) return -1;

  // lfs_lock(g_lfs_manager[idx].lock);
  ret = lfs_file_sync(g_lfs_manager[idx].lfs, file);
  // lfs_unlock(g_lfs_manager[idx].lock);

  return lfs_ret_value_convert(ret);
}

static int32_t lfs_vfs_fstat(file_t *fp, struct stat *st);
static int32_t lfs_vfs_stat(file_t *fp, const char *path, struct stat *st);
static int32_t lfs_vfs_truncate(file_t *fp, int64_t size);
static int32_t lfs_vfs_access(file_t *fp, const char *path, int mode);
static int32_t lfs_vfs_statfs(file_t *fp, const char *path, struct statfs *sfs);
static int32_t lfs_vfs_remove(file_t *fp, const char *path);
static int32_t lfs_vfs_rename(file_t *fp, const char *oldpath,
                              const char *newpath);

static aos_dir_t *lfs_vfs_opendir(file_t *fp, const char *path);
static aos_dirent_t *lfs_vfs_readdir(file_t *fp, aos_dir_t *dir);
static int32_t lfs_vfs_closedir(file_t *fp, aos_dir_t *dir);
static int32_t lfs_vfs_mkdir(file_t *fp, const char *path);
static int32_t lfs_vfs_rmdir(file_t *fp, const char *path);
static void lfs_vfs_rewinddir(file_t *fp, aos_dir_t *dir);
static int32_t lfs_vfs_telldir(file_t *fp, aos_dir_t *dir);
static void lfs_vfs_seekdir(file_t *fp, aos_dir_t *dir, int32_t loc);

static fs_ops_t lfs_vfs_ops = {
    .open = &lfs_vfs_open,
    .close = &lfs_vfs_close,
    .read = &lfs_vfs_read,
    .write = &lfs_vfs_write,
    .lseek = &lfs_vfs_lseek,
    .sync = &lfs_vfs_sync,
    .access = NULL,
    .stat = NULL,
    .unlink = NULL,
    .opendir = NULL,
    .readdir = NULL,
    .closedir = NULL,
    .telldir = NULL,
    .seekdir = NULL,
};

int lfs_register(void) {
  // mount the filesystem
  if (LFS_ERR_OK != lfs_mount(&lfs, &cfg)) {
    // reformat if we can't mount the filesystem
    // this should only happen on the first boot
    lfs_format(&lfs, &cfg);
    if (LFS_ERR_OK != lfs_mount(&lfs, &cfg)) return -1;
  }
  g_lfs_manager[0].mounted = true;
  return aos_register_fs(LFS_MOUNTPOINT, &lfs_vfs_ops, NULL);
}

int lfs_unregister(void) {
  g_lfs_manager[0].mounted = false;
  // release any resources we were using
  return lfs_unmount(&lfs);
}

#if 0
void TestLFS()
{
    lfs_file_t file;

    // read current count
    uint32_t boot_count = 0;
    lfs_file_open(&lfs, &file, "boot_count", LFS_O_RDWR | LFS_O_CREAT);
    lfs_file_read(&lfs, &file, &boot_count, sizeof(boot_count));

    // update boot count
    boot_count += 1;
    lfs_file_rewind(&lfs, &file);
    lfs_file_write(&lfs, &file, &boot_count, sizeof(boot_count));

    // remember the storage is not updated until the file is closed successfully
    lfs_file_close(&lfs, &file);

    // release any resources we were using
    lfs_unmount(&lfs);

    // print the boot count
    printf("boot_count: %d\n", boot_count);
}
#endif