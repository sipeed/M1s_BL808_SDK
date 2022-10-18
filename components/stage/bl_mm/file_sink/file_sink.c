#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "FreeRTOS.h"
#include "vfs.h"
#include "fcntl.h"
#include "bl808_common.h"
#include "file_sink.h"

extern long long aos_now_ms();
#define min(a,b) ((a) < (b) ? (a):(b))

#define I_FRAME_SIZE          (50*1024)
#define FILE_PATH_NAME_PREFIX (64)
#define FILE_PATH_NAME_SUFFIX (12)
/* integer to ascaii, the strlen is 10 of the maximum unsigned int */
#define FILE_INDEX_STR_LEN    (10)
#define FILE_PTS_STR_LEN      (24)
#define FILE_CNT_STR_LEN      (16)
/* First +1 means char '_' in FILE_PATH_NAME_MAX, second +1 means '\0', ex:test_1.h264 */
#define FILE_PATH_NAME_MAX    (FILE_PATH_NAME_PREFIX + FILE_PTS_STR_LEN + \
                               FILE_CNT_STR_LEN + (FILE_INDEX_STR_LEN + 1) + FILE_PATH_NAME_SUFFIX + 1)

#define FILE_PATH_NAME_DEFAULT       "/sdcard/save.bin"
#define FILE_FIFO_SIZE_DEFAULT       (256*1024)
#define FILE_FIFO_WRITE_UNIT_DEFAULT (4*1024)
#define FILE_SAVE_SIZE_DEFAULT       (4*1024*1024)
#define FILE_SINK_GET_TIMESTAMP()    aos_now_ms()
#define file_fifo_malloc(size)       pvPortMalloc(size)
#define file_fifo_free(ptr)          vPortFree(ptr)
#define file_fifo_dma_malloc(size)   pvPortMalloc(size) //pvPortMallocDMA(1, size)
#define file_fifo_dma_free(ptr)      vPortFree(ptr) //vPortFreeDMA(ptr)

typedef struct file_fifo {
    unsigned char *buffer; /* the buffer holding the data*/
    unsigned int size;     /* the size of the allocated buffer*/
    unsigned int in;       /* data is added at offset (in % size)*/
    unsigned int out;      /* data is extracted from off. (out % size)*/
    unsigned int release;
}file_fifo_t;

typedef struct save_file_info {
    uint32_t cur_file_size;
    uint32_t file_size;
    uint32_t write_unit;
    file_fifo_t *fifo;
    uint32_t cur_file_cnt;
    uint32_t save_file_cnt;
    int fd;
    int type;
    char path_name[FILE_PATH_NAME_PREFIX];
    char suffix[FILE_PATH_NAME_SUFFIX];
}save_file_info_t;

static int file_sink_start_cnt[FILE_SINK_TYPE_MAX] = {0};
static int file_after_save_done(save_file_info_t *f_info);
static int file_sink_gen_file_name(char *prefix, char *suffix, uint32_t index, char *file_name, uint32_t cnt);

unsigned int file_fifo_put(file_fifo_t *fifo, unsigned char *buffer, unsigned int len)
{
    unsigned int l;
    len = min(len, fifo->size - fifo->in + fifo->release);

    /* first put the data starting from fifo->in to buffer end*/
    l = min(len, fifo->size - (fifo->in & (fifo->size -1)));
    memcpy(fifo->buffer + (fifo->in & (fifo->size -1)), buffer, l);
    //printf("[DEBUG]first len:%d  offset:%d\n", l, fifo->in & (fifo->size -1));

    /* then put the rest (if any) at the beginning of the buffer*/
    memcpy(fifo->buffer, buffer + l, len - l);
    //printf("[DEBUG]second len:%d\n", len - l);

    fifo->in += len;
    return len;
}

unsigned int file_fifo_get(file_fifo_t *fifo, uint32_t write_unit, uint32_t *offset)
{
    unsigned int l;
    unsigned int len;
    len = fifo->in - fifo->out;
    /* first get the data from fifo->out until the end of the buffer*/
    l = min(len, fifo->size - (fifo->out & (fifo->size -1)));
    if(l < write_unit)
        return 0;

    *offset = fifo->out & (fifo->size -1);
    fifo->out += write_unit;

    return write_unit;
}

unsigned int file_fifo_release(struct file_fifo *fifo, unsigned int len)
{
    fifo->release += len;
    return len;
}

unsigned int file_fifo_size(struct file_fifo *fifo)
{
    unsigned int len;
    if(!fifo)
        return 0;
    len = fifo->in - fifo->out;
    return len;
}

int32_t file_fifo_reset(struct file_fifo *fifo)
{
    if(!fifo)
        return FILE_HANDLE_FALSE;
    fifo->in = fifo->out = fifo->release=0;
    //printf("[INFO] reset ring buffer of file!\r\n");
    return FILE_HANDLE_TRUE;
}

static int file_save_handle(save_file_info_t *file_info, uint32_t offset)
{
    int ret = -1;
    uint32_t write_unit = 0;
    char *buffer = NULL;
    if(!file_info)
        return FILE_HANDLE_FALSE;
    if(file_info->fd < 0)
        return FILE_HANDLE_FALSE;
    write_unit = file_info->write_unit;
    buffer = (char *)(file_info->fifo->buffer + offset);

    file_info->cur_file_size += write_unit;
    ret = aos_write(file_info->fd, buffer, write_unit);
    if(ret != write_unit){
        printf("[ERROR] Write file fail! ret:%d, %s line:%d\r\n", ret, __func__, __LINE__);
        return FILE_HANDLE_FALSE;
    }

    return FILE_HANDLE_TRUE;
}

int file_sink_handle(void *file_info, char *addr, uint32_t len)
{
    uint32_t ret = 0, offset = 0, write_unit = 0;
    save_file_info_t *f_info = NULL;
    file_fifo_t *fifo = NULL;
    if(!file_info || !addr)
        return FILE_HANDLE_FALSE;
    f_info = (save_file_info_t *)file_info;
    if(f_info->fd < 0)
        return FILE_HANDLE_FALSE;
    write_unit = f_info->write_unit;
    fifo = f_info->fifo;
    ret = file_fifo_put(fifo, (unsigned char *)addr, len);
    if(ret != len){
        printf("[ERROR] File fifo is full!! ret:%d, len:%d, %s line:%d\r\n", ret, len, __func__, __LINE__);
        return FILE_HANDLE_FALSE;
    }

    while(1){
        ret = file_fifo_get(fifo, write_unit, &offset);
        if(ret != write_unit){
            break;
        }
        //printf("offset:%d\r\n", offset);
        file_save_handle(f_info, offset);
        file_fifo_release(fifo, write_unit);
    }

    if(f_info->file_size && (f_info->cur_file_size > f_info->file_size)){
        printf("[File_sink][INFO] Data save over!!\r\n");
        aos_close(f_info->fd);
        f_info->fd = -1;
    }
    return FILE_HANDLE_TRUE;
}

static int file_fifo_get_all(file_fifo_t *fifo, uint32_t *offset, uint32_t *get_len)
{
    unsigned int l;
    unsigned int len;

    len = fifo->in - fifo->out;
    l = min(len, fifo->size - (fifo->out & (fifo->size -1)));
    if(len != l){
        printf("[ERROR] Fifo has two part!! Not support! %s line:%d\r\n", __func__, __LINE__);
        return FILE_HANDLE_FALSE;
    }
    *offset = fifo->out & (fifo->size -1);
    *get_len = l;

    return FILE_HANDLE_TRUE;
}

static inline int file_after_save_done(save_file_info_t *f_info)
{
    int fd, ret;
    char path_name[FILE_PATH_NAME_MAX] = {0};
    if((!f_info) || (f_info->fd < 0))
        return FILE_HANDLE_FALSE;
    aos_close(f_info->fd);

    f_info->fd = -1;
    f_info->cur_file_size = 0;
    f_info->cur_file_cnt++;
    if(f_info->cur_file_cnt >= f_info->save_file_cnt){
        printf("[INFO] Save file over, file numbers:%d\r\n", f_info->cur_file_cnt);
        f_info->cur_file_cnt = 0;
        return FILE_HANDLE_FALSE;
    }

    ret = file_sink_gen_file_name(f_info->path_name, f_info->suffix, f_info->cur_file_cnt, \
                                  path_name, file_sink_start_cnt[f_info->type]);
    if(ret){
        printf("[ERROR] File sink gen file name fail!!\r\n");
        return NULL;
    }

    fd = aos_open(path_name, O_RDWR | O_CREAT | O_TRUNC);
    if(fd < 0){
        printf("[ERROR] file open fail! file_name:%s, fd:%d, %s line:%d\r\n", \
               path_name, fd, __func__, __LINE__);
        return FILE_HANDLE_FALSE;
    }
    f_info->fd = fd;
    printf("[INFO] The file:%s open successfully to be saved!\r\n", path_name);

    return FILE_HANDLE_TRUE;
}

int file_save_all_data(void *file_info){
    save_file_info_t *f_info = NULL;
    file_fifo_t *fifo = NULL;
    uint32_t offset, len;
    int ret;
    if(!file_info)
        return FILE_HANDLE_FALSE;
    f_info = (save_file_info_t *)file_info;
    if(f_info->fd < 0)
        return FILE_HANDLE_FALSE;
    fifo = f_info->fifo;

    ret = file_fifo_get_all(fifo, &offset, &len);
    if(ret){
        printf("[ERROR] Get fifo all fail! %s line:%d\r\n", __func__, __LINE__);
        return FILE_HANDLE_FALSE;
    }

    ret = aos_write(f_info->fd, fifo->buffer + offset, len);
    if(ret != len){
        printf("[ERROR] File write fail!! ret:%d len:%d, %s line:%d\r\n", ret, len, __func__, __LINE__);
        return FILE_HANDLE_FALSE;
    }

    file_fifo_reset(f_info->fifo);
    ret = file_after_save_done(f_info);
    if(ret){
        //printf("[INFO] File handle over!!\r\n");
        return FILE_HANDLE_FALSE;
    }

    return FILE_HANDLE_TRUE;
}

static int file_sink_gen_file_prefix(char *path, char *name, char *file_name_prefix)
{
    if(!path || !name || !file_name_prefix)
        return FILE_HANDLE_FALSE;

    sprintf(file_name_prefix, "%s%s", path, name);
    return FILE_HANDLE_TRUE;
}

static int file_sink_gen_file_suffix(int type, char *file_name_suffix)
{
    int ret = FILE_HANDLE_TRUE;
    if(!file_name_suffix)
        return FILE_HANDLE_FALSE;

    switch (type) {
        case FILE_SINK_TYPE_VIDEO_MJPEG:
            sprintf(file_name_suffix, "%s", ".jpg");
            break;
        case FILE_SINK_TYPE_VIDEO_H264:
            sprintf(file_name_suffix, "%s", ".h264");
            break;
        case FILE_SINK_TYPE_AUDIO_PCM:
            sprintf(file_name_suffix, "%s", ".pcm");
            break;
        case FILE_SINK_TYPE_AUDIO_AMR:
            sprintf(file_name_suffix, "%s", ".amr");
            break;
        default:
            printf("[ERROR] Not support file data type!! %s line:%d\r\n", __func__, __LINE__);
            ret = FILE_HANDLE_FALSE;
            break;
    }

    return ret;
}

static int file_sink_gen_file_name(char *prefix, char *suffix, uint32_t index, char *file_name, uint32_t cnt)
{
    long long time_stamp = 0;
    if(!prefix || !suffix || !file_name)
        return FILE_HANDLE_FALSE;
    time_stamp = FILE_SINK_GET_TIMESTAMP();
    if(index){
        sprintf(file_name, "%s_pts%llu_%d_%d%s",
                           prefix, time_stamp, cnt, index, suffix);
    }else{
        sprintf(file_name, "%s_pts%llu_%d%s",
                            prefix, time_stamp, cnt, suffix);
    }

    return FILE_HANDLE_TRUE;
}

static int file_sink_check_param(save_file_config_t *config)
{
    uint32_t pre_len = 0, suf_len = 0;
    if(!config)
        return FILE_HANDLE_FALSE;

    if(config->type >= FILE_SINK_TYPE_MAX){
        printf("[ERROR] Type is illegal!! input_type:%d\r\n", config->type);
        return FILE_HANDLE_FALSE;
    }
    pre_len = strlen(config->file_path_name);
    suf_len = strlen(config->file_suffix);
    /* +2 is char '_' and '\0', ex:test_1.h264 */
    if((pre_len + suf_len + FILE_INDEX_STR_LEN + 2) > FILE_PATH_NAME_MAX){
        printf("[ERROR] String len is to large, prefix_len:%d suffix_len:%d max_len:%d, %s line:%d\r\n",
                pre_len, suf_len, FILE_PATH_NAME_MAX, __func__, __LINE__);
        return FILE_HANDLE_FALSE;
    }

    return FILE_HANDLE_TRUE;
}

void * file_sink_new(save_file_config_t *config)
{
    uint32_t fifo_size = 0;
    save_file_info_t *file_info = NULL;
    file_fifo_t *fifo = NULL;
    char *fifo_buffer = NULL;
    char *prefix = NULL, *suffix = NULL;
    char path_name_prefix[FILE_PATH_NAME_PREFIX] = {0};
    char path_name_suffix[FILE_PATH_NAME_SUFFIX] = {0};
    char path_name[FILE_PATH_NAME_MAX] = {0};
    int fd = -1, ret = -1;
    if(!config){
        printf("[ERROR] File config is null!!\r\n");
        return NULL;
    }

    printf("[INFO] type:%d path:%s name:%s path_name:%s suffix:%s save_size:%d file_nu:%d\r\n",
            config->type,
            config->path,
            config->name,
            config->file_path_name,
            config->file_suffix,
            config->save_size,
            config->file_save_cnt);
    if(file_sink_check_param(config)){
        printf("[ERROR] File sink check param fail!!\r\n");
        return NULL;
    }

    fifo_size = FILE_FIFO_SIZE_DEFAULT;
    if(!config->file_path_name){
        ret = file_sink_gen_file_prefix(config->path, config->name, path_name_prefix);
        if(ret){
            printf("[ERROR] File sink gen file prefix name fail!!\r\n");
            return NULL;
        }
        prefix = path_name_prefix;
    }else{
        prefix = config->file_path_name;
    }

    if(!config->file_suffix){
        ret = file_sink_gen_file_suffix(config->type, path_name_suffix);
        if(ret){
            printf("[ERROR] File sink gen file suffix name fail!!\r\n");
            return NULL;
        }
        suffix = path_name_suffix;
    }else{
        suffix = config->file_suffix;
    }

    file_sink_start_cnt[config->type]++;
    ret = file_sink_gen_file_name(prefix, suffix, 0, path_name, file_sink_start_cnt[config->type]);
    if(ret){
        printf("[ERROR] File sink gen file name fail!!\r\n");
        return NULL;
    }

    fd = aos_open(path_name, O_RDWR | O_CREAT | O_TRUNC);
    if(fd < 0){
        printf("[ERROR] file open fail! file_name:%s, fd:%d %s line:%d\r\n", \
               path_name, fd, __func__, __LINE__);
        return NULL;
    }
    printf("[INFO] The file:%s open successfully to be saved!\r\n", path_name);

    file_info = file_fifo_malloc(sizeof(save_file_info_t));
    if(!file_info){
        printf("[ERROR] File instance malloc fail! %s line:%d\r\n", __func__, __LINE__);
        return NULL;
    }
    memset(file_info, 0, sizeof(save_file_info_t));

    fifo = file_fifo_malloc(sizeof(file_fifo_t));
    if(!fifo){
        file_fifo_free(file_info);
        printf("[ERROR] File fifo instance malloc fail! %s line:%d\r\n", __func__, __LINE__);
        return NULL;
    }
    memset(fifo, 0, sizeof(file_fifo_t));

    fifo_buffer = file_fifo_dma_malloc(fifo_size);
    if(!fifo){
        file_fifo_free(file_info);
        file_fifo_free(fifo);
        printf("[ERROR] Fifo malloc fail! %s line:%d\r\n", __func__, __LINE__);
        return NULL;
    }
    memset(fifo_buffer, 0, fifo_size);

    fifo->buffer = (unsigned char *)fifo_buffer;
    fifo->size = fifo_size;
    fifo->in = fifo->out = fifo->release = 0;
    file_info->fd = fd;
    file_info->cur_file_size = 0;
    file_info->file_size = config->save_size;
    file_info->write_unit = FILE_FIFO_WRITE_UNIT_DEFAULT;
    file_info->fifo = fifo;
    file_info->save_file_cnt = config->file_save_cnt;
    file_info->cur_file_cnt = 0;
    file_info->type = config->type;
    memcpy(file_info->path_name, prefix, strlen(prefix));
    memcpy(file_info->suffix, suffix, strlen(suffix));

    return file_info;
}

void file_sink_destroy(void *file_info)
{
    save_file_info_t *f_info = NULL;
    f_info = (save_file_info_t *)file_info;
    if(f_info){
        if(f_info->fifo){
            if(f_info->fifo->buffer){
                file_fifo_dma_free(f_info->fifo->buffer);
            }
            file_fifo_free(f_info->fifo);
        }
        if(f_info->fd >= 0)
            aos_close(f_info->fd);
        file_fifo_free(f_info);
    }
}
