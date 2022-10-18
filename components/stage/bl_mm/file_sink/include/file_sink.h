#ifndef __FIFE_SINK_H__
#define __FILE_SINK_H__

#ifdef __cpluscplus
extern "C"
{
#endif

#define FILE_HANDLE_TRUE (0)
#define FILE_HANDLE_FALSE (1)

typedef enum {
    /* video data type */
    FILE_SINK_TYPE_VIDEO_START = 0,
    FILE_SINK_TYPE_VIDEO_MJPEG,
    FILE_SINK_TYPE_VIDEO_H264,
    FILE_SINK_TYPE_VIDEO_END,
    /* audio data type */
    FILE_SINK_TYPE_AUDIO_START,
    FILE_SINK_TYPE_AUDIO_PCM,
    FILE_SINK_TYPE_AUDIO_AMR,
    FILE_SINK_TYPE_AUDIO_END,
    FILE_SINK_TYPE_MAX,
} FILE_SINK_TYPE;

typedef struct save_file_config {
    int type;
    char *path;
    char *name;
    char *file_path_name;
    char *file_suffix;
    uint32_t save_size;
    uint32_t file_save_cnt;
} save_file_config_t;

void * file_sink_new(save_file_config_t *config);
int file_sink_handle(void *file_info, char *addr, uint32_t len);
int file_save_all_data(void *file_info);
void file_sink_destroy(void *file_info);

#ifdef __cpluscplus
}
#endif

#endif /* __FILE_SINK_H__ */
