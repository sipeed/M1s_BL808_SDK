#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <aos/kernel.h>
#include <vfs.h>
#include <cli.h>
#include <unistd.h>
#include <bl808_ipc.h>
#include <FreeRTOS.h>
#include <semphr.h>

#include <bl_venc.h>
#include <bl_ipc.h>
#include "file_sink.h"
#include "mm_osal.h"
#include "mm_encoder.h"
#include "sample_common.h"
#include "helper_venc.h"
#include "helper_venc_parse.h"

//#define IPC_STREAM_ON_E907

#ifndef IPC_STREAM_ON_E907
#include "librtspsrv.h"
#endif

enum numeric_short_options {
	H264_LOW_POWER_MODE = 1000,
	H264_DIRECT_LINK_EN,
	H264_RATE_CTRL_MODE,
	H264_BIT_RATE,
	H264_MAX_BIT_RATE,
	H264_FRAME_RATE,
	H264_GOP_SIZE,
	H264_QUALITY_LEVEL,
	H264_IP_RATIO,
	H264_PROFILE,
	H264_MIN_QP,
	H264_MAX_QP,
	H264_VIDEO,
	H264_YUV_ALLOC,
	H264_YUV_FREE,
	H264_START_STREAMING,
	H264_START_FRAME_MODE,
	H264_SET_RATE_CTRL_LEVEL,
	H264_GET_RATE_CTRL_LEVEL,
	JPEG_QUALITY,
	UPDATE_CFG,
	BS_ADDR,
	BS_SIZE,
	NO_WRITE,
	START_YUV_ENCODE,
	STOP_YUV_ENCODE,
	SD_FILE_PATH_NAME = 2000,
	SD_FILE_PATH,
	SD_FILE_NAME,
	SD_FILE_NUM,
	SD_FILE_SIZE,
	SCENCE_CTRL_REG,
	VENC_REG,
	JPEG_REG,
};

typedef enum {
    WRITE_PSRAM = 0,
    WRITE_SD_CARD,
    WRITE_RTSP_STREAM,
    WRITE_NONE,
} sink_type;

typedef struct {
    uint8_t* base_addr;
    uint32_t size;
    uint8_t* sec_base_addr;
    uint32_t sec_size;
    uint8_t frame_type;
} stream_buffer_t;

struct stream_stats_t {
    int chn_id;
    TickType_t start_time;
};

struct stream_input_sw_buffer_t {
    uint32_t y_addr;
    uint32_t y_size;
    uint32_t uv_addr;
    uint32_t uv_size;
};

typedef struct {
    uint8_t* base_addr;
    uint32_t size;
    int curr_frm_cnt;
    int tot_byte_cnt;
    int stat_byte_cnt;
    uint8_t *curr_wr_ptr;
    uint8_t reset_req;
    sink_type sink;
    void *file_sink;
    struct stream_stats_t stat;
    uint8_t bStart;
    void *streamQueue_sw_mode_src;
    void *streamQueue;
    MMEncoderFrameEncMode enc_sw_mode;
    uint8_t stop_enc_flag;
    uint8_t stop_src_flag;
} stream_manager_t;

#include "helper_venc_parse.h"

static char module[32] = {'\0'};
static char argv_reg[32] = {'\0'};
static char argv_val[128] = {'\0'};
static char ret_string[128] = {'\0'};

static stream_manager_t stream_mngr[MAX_CHN_NUM];
static save_file_config_t save_sd_config = {0};
static int max_frame_cnt = 100000000;
stream_buffer_t jpeg_hdr_buf;
stream_buffer_t jpeg_tail_buf;

static uint32_t sw_bs_addr[MAX_CHN_NUM];
// used for push yuv buffer (external)
static uint8_t *g_yuv_buf_addr = NULL;
static uint32_t g_yuv_buf_size = 0;
static SemaphoreHandle_t gEncFrameMutex; // for dual stream, frame start should be done once at a time
static uint8_t g_rtsp_server_started = 0;

static int get_bitrate_mode_param(char *optarg, uint32_t *bitrate_mode)
{
    if ((!strncmp(optarg, "cbr", strlen("cbr")))
        || (!strncmp(optarg, "CBR", strlen("CBR")))) {
        *bitrate_mode = 0;
    } else if ((!strncmp(optarg, "vbr", strlen("vbr")))
        || (!strncmp(optarg, "VBR", strlen("vbr")))) {
        *bitrate_mode = 1;
    } else if ((!strncmp(optarg, "fixqp", strlen("fixqp")))
        || (!strncmp(optarg, "FIXQP", strlen("FIXQP")))) {
        *bitrate_mode = 2;
    } else {
        return -1;
    }

    return 0;
}

static int get_profile_param(char *optarg, uint32_t *profile)
{
    if ((strstr(optarg, "baseline") != 0) || (strstr(optarg, "BP") != 0)) {
        *profile = 0;
    } else if ((strstr(optarg, "main") != 0) || (strstr(optarg, "MP") != 0)) {
        *profile = 1;
    } else {
        return -1;
    }

    return 0;
}

static void bitrate_stats(struct stream_stats_t *stream_stat)
{
    TickType_t curr_time_ms = xTaskGetTickCount();

    if (curr_time_ms - stream_stat->start_time >= 3000) {
        BL_LOGI("[CHN %d]Bitrate: %.3f Mbps, FPS: %.3f\r\n",
            stream_stat->chn_id,
            MM_Encoder_GetStreamBitrate(stream_stat->chn_id),
            MM_Encoder_GetStreamFPS(stream_stat->chn_id));
        stream_stat->start_time = curr_time_ms;
    }
}

static int streamer_init(int chn_id, save_file_config_t *record_info)
{
    stream_manager_t *streamer = &stream_mngr[chn_id];

    if (NULL == streamer->base_addr) {
        BL_LOGI("Alloc stream buffer\r\n");
        streamer->base_addr = BL_MallocDMA(PSRAM_ID_FOR_STREAM_BUF, STREAM_BUF_SIZE);
    }
    sw_bs_addr[chn_id] = streamer->base_addr;
    streamer->size = STREAM_BUF_SIZE;
    streamer->curr_wr_ptr = streamer->base_addr;
    streamer->curr_frm_cnt = 0;
    streamer->tot_byte_cnt = 0;
    streamer->stat_byte_cnt = 0;
    streamer->reset_req = 0;
    streamer->stat.chn_id = chn_id;
    streamer->stat.start_time = 0;
    streamer->enc_sw_mode = ENC_SW_MODE_DISABLED;

    streamer->streamQueue_sw_mode_src = BL_Queue_Create(3, sizeof(struct stream_input_sw_buffer_t));
    streamer->streamQueue = BL_Queue_Create(25, sizeof(stream_buffer_t));
    streamer->bStart = 0;

    if (record_info && ((record_info->file_path_name) || (record_info->path))) {
        /* Mjpec save file by frame, one frame save into one file, the frame number is decided by file_save_cnt;
           Others save data one file, the size is decided by save_size */
        streamer->sink = WRITE_SD_CARD;
        if (NULL == streamer->file_sink) {
            streamer->file_sink = file_sink_new(record_info);
            if(!streamer->file_sink){
                BL_LOGE("File sink creat fail!!\r\n");
                return -1;
            }
        }
    } else {
        streamer->sink = WRITE_PSRAM;
    }

    return 0;
}

static int streamer_deinit(int chn_id)
{
    stream_manager_t *streamer = &stream_mngr[chn_id];

    if (NULL != streamer->base_addr) {
        BL_FreeDMA(streamer->base_addr);
        streamer->base_addr = NULL;
    }
    if (NULL != streamer->file_sink) {
        file_sink_destroy(streamer->file_sink);
        streamer->file_sink = NULL;
    }

    BL_Queue_Delete(streamer->streamQueue_sw_mode_src);
    BL_Queue_Reset(streamer->streamQueue);
    BL_Queue_Delete(streamer->streamQueue);
    return 0;
}

static int streamer_save_into_sd(void *file_sink, const stream_buffer_t *buf_info)
{
    if (!file_sink || !buf_info)
        return -1;

    file_sink_handle(file_sink, (void *)buf_info->base_addr, buf_info->size);
    if (buf_info->sec_size > 0) {
        file_sink_handle(file_sink, (void *)(buf_info->sec_base_addr), buf_info->sec_size);
    }

    return 0;
}

#ifdef IPC_STREAM_ON_E907
static int g_streamStart = 0;
static int g_stream_wptr = 0;
static int g_stream_rptr = 0;
struct ipc_stream_buffer_t {
    uint8_t frame_type;
    uint8_t used;
    uint32_t frame_id;
    uint32_t frame_start_addr;
    uint32_t frame_size;
    uint32_t frame_sec_addr;
    uint32_t frame_sec_size;
};

struct ipc_sync_buffer_t {
    uint32_t index;
};

enum {
    IPC_ACTION_START_STREAMING = 0,
    IPC_ACTION_FRAME_DONE,
    IPC_ACTION_STOP_STREAMING,
};

#define BUF_INFO_NUM    (1*25)
static uint32_t gIPCAllocSize[BUF_INFO_NUM] = {0};
static struct ipc_sync_buffer_t *gIPCinfo = (struct ipc_sync_buffer_t *)0x40000000;
static struct ipc_stream_buffer_t *gStreamBufInfo = (struct ipc_stream_buffer_t *)0x40000004;

static void on_m0_trigger_callback(uint32_t src)
{
    switch (src) {
    case (1 << IPC_ACTION_START_STREAMING):
        g_streamStart = 1;
        g_stream_rptr = 0;
        g_stream_wptr = 0;
        memset(gStreamBufInfo, 0, sizeof(struct ipc_stream_buffer_t)*BUF_INFO_NUM);
        break;
    case (1 << IPC_ACTION_FRAME_DONE):
        g_stream_rptr = (g_stream_rptr + 1) % BUF_INFO_NUM;;
        break;
    case (1 << IPC_ACTION_STOP_STREAMING):
        g_streamStart = 0;
        break;
    default:
        break;
    }
}
#endif


static int streamer_send_jpeg(stream_manager_t *streamer, const stream_buffer_t *jpeg_hdr,
    const stream_buffer_t *frame, const stream_buffer_t *jpeg_tail)
{
    uint8_t *curr_wr_ptr = streamer->curr_wr_ptr;
    uint32_t wr_size = (jpeg_hdr->size + frame->size + frame->sec_size + jpeg_tail->size);
    void *file_sink = streamer->file_sink;

    BL_LOGD("JPEG stream, addr 0x%p, size 0x%x\r\n", frame->base_addr, frame->size);
    BL_LOGD("Send JPEG frame, addr 0x%p, size 0x%x\r\n", curr_wr_ptr, wr_size);
    if (streamer->sink == WRITE_PSRAM) {
        if ((curr_wr_ptr + wr_size) > (streamer->base_addr + streamer->size)) {
            BL_LOGI("stream size exceed limit 0x%x!\r\n", streamer->size);
            BL_ABORT();
        } else {

#if (!MJPG_AUTO_HEADER)
            memcpy(curr_wr_ptr, (void *)jpeg_hdr->base_addr, jpeg_hdr->size);
            curr_wr_ptr += jpeg_hdr->size;
#endif
            //BL60X_MemCpy_Fastest(curr_wr_ptr, (void *)frame->base_addr, frame->size);
            csi_dcache_invalid_range((void *)frame->base_addr, frame->size);
            memcpy(curr_wr_ptr, (void *)frame->base_addr, frame->size);
            curr_wr_ptr += frame->size;

            if (frame->sec_size) {
                //BL60X_MemCpy_Fastest(curr_wr_ptr, (void *)frame->sec_base_addr, frame->sec_size);
                csi_dcache_invalid_range((void *)frame->sec_base_addr, frame->sec_size);
                memcpy(curr_wr_ptr, (void *)frame->sec_base_addr, frame->sec_size);
                curr_wr_ptr += frame->sec_size;
            }
#if (!MJPG_AUTO_HEADER)
            memcpy(curr_wr_ptr, (void *)jpeg_tail->base_addr, jpeg_tail->size);
            curr_wr_ptr += jpeg_tail->size;
#endif

            streamer->curr_wr_ptr = curr_wr_ptr;
            streamer->tot_byte_cnt = curr_wr_ptr - streamer->base_addr;
        }
    } else if (streamer->sink == WRITE_SD_CARD) {
#if (!MJPG_AUTO_HEADER)
        file_sink_handle(file_sink, (void *)jpeg_hdr->base_addr, jpeg_hdr->size);
#endif
        file_sink_handle(file_sink, (void *)frame->base_addr, frame->size);
        if (frame->sec_size) {
            file_sink_handle(file_sink, (void *)frame->sec_base_addr, frame->sec_size);
        }
        streamer->tot_byte_cnt += frame->size + frame->sec_size;
#if (!MJPG_AUTO_HEADER)
        file_sink_handle(file_sink, (void *)jpeg_tail->base_addr, jpeg_tail->size);
        streamer->tot_byte_cnt += jpeg_hdr->size + jpeg_tail->size;
#endif
        file_save_all_data(file_sink);
    }

    streamer->curr_frm_cnt++;
    bitrate_stats(&streamer->stat);

    return 0;
}

static int streamer_send_h264(stream_manager_t *streamer, const stream_buffer_t *frame)
{
    uint8_t *curr_wr_ptr = streamer->base_addr + streamer->tot_byte_cnt;
    void *file_sink = streamer->file_sink;
    static int flag = 0, total_size = 0;

    BL_LOGD("[H264] write addr 0x%p, size 0x%x\r\n", streamer->curr_wr_ptr, frame->size);

    streamer->stat_byte_cnt += frame->size + frame->sec_size;


    if (streamer->sink == WRITE_PSRAM) {
        if ((streamer->tot_byte_cnt + frame->size + frame->sec_size) > streamer->size) {
            if (!flag) {
                total_size = streamer->tot_byte_cnt;
                flag = 1;
            }
            BL_LOGD("stream size exceed limit 0x%x! save_addr:%p size:0x%x\r\n",
                    streamer->size, streamer->base_addr, total_size);
            BL_ABORT();
        } else {
            //BL60X_MemCpy_Fastest(curr_wr_ptr, (void *)frame->base_addr, frame->size);
            csi_dcache_invalid_range((void *)frame->base_addr, frame->size);
            memcpy(curr_wr_ptr, (void *)frame->base_addr, frame->size);
            streamer->tot_byte_cnt += frame->size;

            if (frame->sec_size) {
                curr_wr_ptr += frame->size;
                //BL60X_MemCpy_Fastest(curr_wr_ptr, (void *)frame->sec_base_addr, frame->sec_size);
                csi_dcache_invalid_range((void *)frame->sec_base_addr, frame->sec_size);
                memcpy(curr_wr_ptr, (void *)frame->sec_base_addr, frame->sec_size);
                streamer->tot_byte_cnt += frame->sec_size;
            }
        }
    }else if (streamer->sink == WRITE_SD_CARD) {
        streamer_save_into_sd(file_sink, frame);
    } else if (streamer->sink == WRITE_RTSP_STREAM) {
#ifdef IPC_STREAM_ON_E907
        if (g_streamStart == 1) {
            struct ipc_stream_buffer_t *buf = &gStreamBufInfo[g_stream_wptr];
            csi_dcache_invalid_range((void *)buf, sizeof(struct ipc_stream_buffer_t));
            if (((g_stream_wptr + 1) % BUF_INFO_NUM) == g_stream_rptr) {
                BL_LOGD("Buffer Full, wptr = %d, rptr = %d\r\n", g_stream_wptr, g_stream_rptr);
            } else {
                buf->frame_id = streamer->curr_frm_cnt;
                buf->frame_start_addr = frame->base_addr;
                buf->frame_size = frame->size;
                buf->frame_sec_addr = frame->sec_base_addr;
                buf->frame_sec_size = frame->sec_size;
                buf->frame_type = frame->frame_type;
        
                gIPCinfo->index = g_stream_wptr;
                g_stream_wptr = (g_stream_wptr + 1) % BUF_INFO_NUM;
                buf->used = 1;
                csi_dcache_clean_range(gIPCinfo, sizeof(struct ipc_sync_buffer_t));
                csi_dcache_clean_range(buf, sizeof(struct ipc_stream_buffer_t));
        
                IPC_Trigger_Target_CPU(GLB_CORE_ID_M0, 2);
            }
        }
#else
        if (streamer->bStart == 1) {
            if (BL_Queue_Put_Item(streamer->streamQueue, frame) == pdFALSE) {
                BL_LOGD("[%d] Stream Queue Full\r\n", streamer->stat.chn_id);
            }
        }
#endif
    }

    streamer->curr_frm_cnt++;
    bitrate_stats(&streamer->stat);

    return 0;
}

static int handle_coded_frame(MMEncoderStream *stream, stream_manager_t *streamer)
{
    stream_buffer_t coded_frame_buf;
    int chn_id = stream->stream_id;

    if (stream->frame_size > 0) {
        coded_frame_buf.base_addr = stream->frame_start_addr;
        coded_frame_buf.size = stream->frame_size;
        coded_frame_buf.sec_base_addr = stream->frame_sec_addr;
        coded_frame_buf.sec_size = stream->frame_sec_size;
        coded_frame_buf.frame_type = stream->frame_type;

        if (ENC_H264_I_FRAME == stream->frame_type || ENC_H264_P_FRAME == stream->frame_type) {
            streamer_send_h264(streamer, &coded_frame_buf);
        } else if (ENC_JPEG_FRAME == stream->frame_type) {
            streamer_send_jpeg(streamer, &jpeg_hdr_buf, &coded_frame_buf, &jpeg_tail_buf);
        }
    }
    BL_LOGD("[APP] [CHN %d] size 0x%x, addr 0x%p, frm_cnt %d, tot_bytes 0x%x\r\n", chn_id,
        stream->frame_size, stream->frame_start_addr, streamer->curr_frm_cnt, streamer->tot_byte_cnt);

    return 0;
}

static void get_jpeg_info(void)
{
    bl_venc_get_JFIF_header(&jpeg_hdr_buf.base_addr, &jpeg_hdr_buf.size);
    bl_venc_get_JFIF_tail(&jpeg_tail_buf.base_addr, &jpeg_tail_buf.size);
    BL_LOGI("jpeg header size: 0x%x\r\n", jpeg_hdr_buf.size);
}

#ifndef IPC_STREAM_ON_E907
static void rtsp_action_cb(int action)
{
    int chn_id = 0;
    stream_manager_t *streamer = &stream_mngr[chn_id];

    switch (action) {
    case RTSP_STRM_REPORT_CLIENT_EXIT:
        BL_LOGI("RTSP disconnect\r\n");
        streamer->bStart = 0;
        break;
    default:
        break;
    }
}

static int get_frm_cb(struct strm_info *strm_info, struct frm_info *frm_info)
{
    MMEncoderStream stream;
    stream_buffer_t frame;
    int chn_id = 0;
    stream_manager_t *streamer = &stream_mngr[chn_id];

    if (streamer->bStart == 0) {
        BL_Queue_Reset(streamer->streamQueue);
        streamer->bStart = 1;
    }

    if (BL_Queue_Get_Item(streamer->streamQueue, &frame, QUEUE_NO_WATI) == pdFALSE) {
        //BL_LOGE("Frame data not ready\r\n");
        return 0;
    }

    frm_info->frm_sz = frame.size + frame.sec_size;
    //printf("[%d]frame: 0x%x size %d, frame_sec: 0x%x, sz: 0x%d\r\n",
    //    streamer->curr_frm_cnt, (uint32_t)frame.base_addr, frame.size,
    //    (uint32_t)frame.sec_base_addr, frame.sec_size);
    csi_dcache_invalid_range((void*)frame.base_addr, frame.size);
    memcpy(frm_info->frm_buf, (void *)frame.base_addr, frame.size);
    if (frame.sec_size > 0) {
        csi_dcache_invalid_range((void*)frame.sec_base_addr, frame.sec_size);
        memcpy(frm_info->frm_buf + frame.size, (void *)frame.sec_base_addr, frame.sec_size);
    }

    if (frame.frame_type == ENC_H264_I_FRAME)
        frm_info->frm_type = FRM_TYPE_I;
    else
        frm_info->frm_type = FRM_TYPE_P;

    return 1;
}
#endif

static void get_video_stream(void *pvParameters)
{
    stream_manager_t *streamer;
    MMEncoderStream stream;
    struct stream_input_sw_buffer_t swBufInfo;
    int chn_id;

    chn_id = (int)pvParameters;
    streamer = &stream_mngr[chn_id];
    streamer->stop_enc_flag = 0;
#ifdef IPC_STREAM_ON_E907
    memset(gIPCinfo, 0, sizeof(struct ipc_sync_buffer_t));
#endif

    while (!streamer->stop_enc_flag && streamer->curr_frm_cnt < max_frame_cnt) {
        if (streamer->reset_req) {
            streamer->tot_byte_cnt = 0;
            streamer->reset_req = 0;
        }
        MM_Encoder_GetStream(chn_id, &stream);
        handle_coded_frame(&stream, streamer);
        if (stream.frame_type != ENC_JPEG_FRAME)
            MM_Encoder_H264_Frame_Done(chn_id, &stream);
    }
    csi_dcache_clean_range(sw_bs_addr[chn_id], streamer->tot_byte_cnt); // flush cache due to smp
    BL_LOGI("[CHN %d] 0x%x - 0x%x\r\n", chn_id, (uint32_t)sw_bs_addr[chn_id], sw_bs_addr[chn_id] + streamer->tot_byte_cnt);
    sample_close_stream(chn_id);
    streamer_deinit(chn_id);
}

static void get_video_stream_frame_mode(void *pvParameters)
{
    stream_manager_t *streamer;
    MMEncoderStream stream;
    struct stream_input_sw_buffer_t swBufInfo;
    int chn_id;

    chn_id = (int)pvParameters;
    streamer = &stream_mngr[chn_id];
    streamer->stop_enc_flag = 0;
#ifdef IPC_STREAM_ON_E907
	memset(gIPCinfo, 0, sizeof(struct ipc_sync_buffer_t));
#endif

    while (!streamer->stop_enc_flag && streamer->curr_frm_cnt < max_frame_cnt) {
        if (streamer->reset_req) {
            streamer->tot_byte_cnt = 0;
            streamer->reset_req = 0;
        }
        BL_Queue_Get_Item(streamer->streamQueue_sw_mode_src, &swBufInfo, QUEUE_WAIT_FOREVER);
        xSemaphoreTake(gEncFrameMutex, portMAX_DELAY);
        MM_Encoder_Frame_Encode_Next(chn_id, swBufInfo.y_addr, swBufInfo.y_size, swBufInfo.uv_addr, swBufInfo.uv_size);
        MM_Encoder_GetStream(chn_id, &stream);
        xSemaphoreGive(gEncFrameMutex);
        handle_coded_frame(&stream, streamer);
        if (stream.frame_type != ENC_JPEG_FRAME)
            MM_Encoder_H264_Frame_Done(chn_id, &stream);
    }
    streamer->stop_src_flag = 1;
    csi_dcache_clean_range(sw_bs_addr[chn_id], streamer->tot_byte_cnt); // flush cache due to smp
    BL_LOGI("[CHN %d] 0x%x - 0x%x\r\n", chn_id, (uint32_t)sw_bs_addr[chn_id], sw_bs_addr[chn_id] + streamer->tot_byte_cnt);
}

static void get_video_input_from_dsp2(void *pvParameters)
{
    int chn_id = (int)pvParameters;
    stream_manager_t *streamer = &stream_mngr[chn_id];
    uint8_t is_y_uv;
    uint32_t start_addr, size;
    struct stream_input_sw_buffer_t swBufInfo;
    memset(&swBufInfo, 0, sizeof(swBufInfo));

    streamer->stop_src_flag = 0;

    while (!streamer->stop_src_flag) {
        if (MM_Encoder_FrameModeGetSource(chn_id, &start_addr, &size, &is_y_uv) == 0) {
            if (is_y_uv == 0) {
                if (swBufInfo.y_size > 0) {
                    BL_LOGE("UV frame not recieved\r\n");
                    memset(&swBufInfo, 0, sizeof(swBufInfo));
                }
                swBufInfo.y_addr = start_addr;
                swBufInfo.y_size = size;
            } else {
                if (swBufInfo.uv_size > 0) {
                    BL_LOGE("Y frame not recieved\r\n");
                    memset(&swBufInfo, 0, sizeof(swBufInfo));
                }
                swBufInfo.uv_addr = start_addr;
                swBufInfo.uv_size = size;
            }
            if (swBufInfo.y_size > 0 && swBufInfo.uv_size > 0) {
                if (BL_Queue_Put_Item(streamer->streamQueue_sw_mode_src, &swBufInfo) == pdFALSE) {
                    BL_LOGD("[%d]Put item into queue fail! %s line:%d\r\n", chn_id, __func__, __LINE__);
                }
                memset(&swBufInfo, 0, sizeof(swBufInfo));
            }
        }
    }
    sample_close_stream(chn_id);
    streamer_deinit(chn_id);
}


static void set_h264_profile(int encChn, int profile)
{
    MMEncoderAttr encAttr;

    MM_Encoder_GetChnAttr(encChn, &encAttr);
    encAttr.attrH264.profile = profile;
    encAttr.encType = ENC_TYPE_H264;
    MM_Encoder_SetChnAttr(encChn, &encAttr);
}

static void set_low_power_mode(int encChn, int lowPwrMode)
{
    MMEncoderAttr encAttr;

    MM_Encoder_GetChnAttr(encChn, &encAttr);
    encAttr.attrH264.lowPwrMode = lowPwrMode;
    MM_Encoder_SetChnAttr(encChn, &encAttr);
}

static void set_gop_size(int encChn, int gopSize)
{
    MMEncoderGOPSizeCfg GOPSizeCfg;

    GOPSizeCfg.gopSize = gopSize;
    MM_Encoder_SetChnGOPSize(encChn, &GOPSizeCfg);
}

static int vencfw_config(void)
{
#if	BITTRUE_REGRESSION_TEST
    h264_bittrue_init();
#endif
    sample_encoder_init();

    get_jpeg_info();

    gEncFrameMutex = xSemaphoreCreateMutex();

    return 0;
}

static void show_usage(void)
{
	aos_cli_printf("enc [options]\r\n");
	aos_cli_printf("-A Select stream A \r\n");
	aos_cli_printf("-B Select stream B \r\n");
	aos_cli_printf("-H Enable h264 encoder \r\n");
	aos_cli_printf("-M Enable jpeg encoder \r\n");
	aos_cli_printf("-s Start encoder \r\n");
	aos_cli_printf("-e Stop encoder \r\n");
	aos_cli_printf("--snapshot JPEG Snapshot \r\n");
	aos_cli_printf("-i [resolution] Set DSP2 input resolution \r\n");
	aos_cli_printf("--rc-mode [cbr/vbr] Set bitrate mode for H264 encoder \r\n");
	aos_cli_printf("--bitrate [bitrate] Set bit rate for H264 encoder \r\n");
	aos_cli_printf("--fps [framerate] Set encoder frame rate \r\n");
	aos_cli_printf("--gop-size [frm_num] Set H264 GOP size \r\n");
	aos_cli_printf("--profile [baseline/main] Set profile for H264 encoder \r\n");
	aos_cli_printf("--ip-ratio [ratio] Set bits budget ratio between I and P frame \r\n");
	aos_cli_printf("--quality [quality] Set JPEG quality \r\n");
	aos_cli_printf("--frm-num [value] Set number of frames for burst encoding \r\n");
	aos_cli_printf("--update-cfg Update configuration to the specific encoder \r\n");
	aos_cli_printf("--bs-addr Get address of coded bitstream \r\n");
	aos_cli_printf("--bs-size Get size of coded bitstream \r\n");
	aos_cli_printf("--start-yuv-enc Start YUV encoding \r\n");
	aos_cli_printf("--sd-path-name The file path and name of saving data, sample:/sdcard/test \r\n");
	aos_cli_printf("--sd-path The file path of the saving data, sample:/sdcard/ \r\n");
	aos_cli_printf("--sd-name The file name of saving data, sample:test \r\n");
	aos_cli_printf("--sd-file-num The file numbers to be saved by frame \r\n");
	aos_cli_printf("--sd-file-size The file size to be saved by stream \r\n");
}

static void enc_cmd(char *buf, int len, int argc, char **argv)
{
    static int chn_id = 0;
    static uint32_t width, height;
    static char fw_init = 0;
    static int sleep_cnt = 0;
    uint32_t bs_addr, bs_size;
    uint32_t value = 0;
    int ch;

    if (!fw_init) {
        if (0 != vencfw_config()) {
            BL_LOGE("vencfw_config err.\r\n");
            return;
        }
        fw_init = 1;
    }

    optind = 0;

    static struct option long_options[] =
    {
        {"bl-enc",          required_argument, 0, H264_LOW_POWER_MODE},
        {"direct-link",     required_argument, 0, H264_DIRECT_LINK_EN},
        {"stream-A",        no_argument,       0, 'A'},
        {"stream-B",        no_argument,       0, 'B'},
        {"stream-C",        no_argument,       0, 'C'},
        {"mjpg",            no_argument,       0, 'm'},
        {"start",           no_argument,       0, 's'},
        {"start-stream",    no_argument,       0, H264_START_STREAMING},
        {"start-frame",     no_argument,       0, H264_START_FRAME_MODE},
        {"end",             no_argument,       0, 'e'},
        {"snapshot",        no_argument,       0, 'S'},
        {"reset"  ,         no_argument,       0, 'r'},
        {"in-size",         required_argument, 0, 'i'},
        {"rc-mode",         required_argument, 0, H264_RATE_CTRL_MODE},
        {"bitrate",         required_argument, 0, H264_BIT_RATE},
        {"maxbitrate",      required_argument, 0, H264_MAX_BIT_RATE},
        {"fps",             required_argument, 0, H264_FRAME_RATE},
        {"gop-size",        required_argument, 0, H264_GOP_SIZE},
        {"profile",         required_argument, 0, H264_PROFILE},
        {"quality-lvl",     required_argument, 0, H264_QUALITY_LEVEL},
        {"ip-ratio",        required_argument, 0, H264_IP_RATIO},
        {"min-qp",        required_argument, 0, H264_MIN_QP},
        {"max-qp",        required_argument, 0, H264_MAX_QP},
        {"set-rc-level",    required_argument, 0, H264_SET_RATE_CTRL_LEVEL},
        {"get-rc-level",    no_argument,       0, H264_GET_RATE_CTRL_LEVEL},
        {"video",           required_argument, 0, H264_VIDEO},
        {"quality",         required_argument, 0, JPEG_QUALITY},
        {"is-running",      no_argument,       0, 'R'},
        {"frm-num",         required_argument, 0, 'F'},
        {"yuv-alloc",       required_argument, 0, H264_YUV_ALLOC},
        {"yuv-free",        required_argument, 0, H264_YUV_FREE},
        {"update-cfg",      no_argument,       0, UPDATE_CFG},
        {"bs-addr",         no_argument,       0, BS_ADDR},
        {"bs-size",         no_argument,       0, BS_SIZE},
        {"start-yuv-enc",   no_argument,       0, START_YUV_ENCODE},
        {"sd-path-name",    required_argument, 0, SD_FILE_PATH_NAME},
        {"sd-path",	        required_argument, 0, SD_FILE_PATH},
        {"sd-name",	        required_argument, 0, SD_FILE_NAME},
        {"sd-file-num",     required_argument, 0, SD_FILE_NUM},
        {"sd-file-size",    required_argument, 0, SD_FILE_SIZE},
        {"scence_ctrl",     required_argument, 0, SCENCE_CTRL_REG},
        {"venc-reg",        required_argument, 0, VENC_REG},
        {"jpeg-reg",        required_argument, 0, JPEG_REG},
        {0, 0, 0, 0}
    };

    while ((ch = getopt_long (argc, argv, "ABCHMsrSei:F:h", long_options, NULL)) != -1) {
        switch (ch)
        {
        case 'A':
            chn_id = CH0_ID;
            save_sd_config.type = FILE_SINK_TYPE_VIDEO_H264;
            break;

        case 'B':
            chn_id = CH1_ID;
            save_sd_config.type = FILE_SINK_TYPE_VIDEO_H264;
            break;

        case 'C':
            chn_id = CH2_ID;
            save_sd_config.type = FILE_SINK_TYPE_VIDEO_MJPEG;
            break;
        case 'H':
            /* Deprecated */
            break;

        case 'M':
            /* Deprecated */
            break;

        case UPDATE_CFG:
            /* Deprecated */
            break;

        case 's':
            streamer_init(chn_id, &save_sd_config);
            sample_start_stream(chn_id);
            aos_task_new("venc_stream", get_video_stream, (void*)chn_id, 4096);
            break;

        case H264_START_FRAME_MODE:
            streamer_init(chn_id, &save_sd_config);
            if (chn_id == CH0_ID) // ch0 for stream, ch1 for psram in frame mode
                stream_mngr[chn_id].sink = WRITE_RTSP_STREAM;
            stream_mngr[chn_id].enc_sw_mode = ENC_SW_MODE_MANUAL;
            sample_start_stream_frame_mode(chn_id);
            aos_task_new("venc_input_task", get_video_input_from_dsp2, (void*)chn_id, 4096);
            aos_task_new("venc_stream_frame", get_video_stream_frame_mode, (void*)chn_id, 4096);
            break;
        case H264_START_STREAMING:
            if (g_rtsp_server_started == 0) {
#ifdef IPC_STREAM_ON_E907
                ipc_d0_init(on_m0_trigger_callback, NULL);
                memset(gStreamBufInfo, 0, sizeof(struct ipc_stream_buffer_t)*BUF_INFO_NUM);
#else
                rtsp_set_video_en(1);
                rtsp_set_audio_en(0);
                set_strm_cb(get_frm_cb);
                rtsp_set_video_fps(sample_get_chann_frame_rate(chn_id));
                rtsp_set_strm_report_cb(rtsp_action_cb);
            
                rtsp_init_lib();
#endif
                g_rtsp_server_started = 1;
            }

            streamer_init(chn_id, &save_sd_config);
            stream_mngr[chn_id].sink = WRITE_RTSP_STREAM;
            sample_start_stream(chn_id);
            aos_task_new("venc_stream", get_video_stream, (void*)chn_id, 4096);
            break;
        case 'S':
            streamer_init(chn_id, &save_sd_config);
            max_frame_cnt = 1;  /* take only one frame */
            sample_start_stream(chn_id);
            aos_task_new("venc_stream", get_video_stream, (void*)chn_id, 4096);
            break;

        case 'r':
            stream_mngr[chn_id].reset_req = 1;
            break;
        case 'e':
            stream_mngr[chn_id].stop_enc_flag = 1;
            break;
        case H264_YUV_ALLOC:
            g_yuv_buf_size = atoi(optarg);
            if (g_yuv_buf_addr)
                BL_FreeDMA(g_yuv_buf_addr);
            g_yuv_buf_addr = BL_MallocDMA(0, g_yuv_buf_size);
            aos_cli_printf("[OK] %u\r\n", (uint32_t)g_yuv_buf_addr);
            break;
        case H264_YUV_FREE:
            if (g_yuv_buf_addr)
                BL_FreeDMA(g_yuv_buf_addr);
            g_yuv_buf_addr = NULL;
            g_yuv_buf_size = 0;
            break;
        case START_YUV_ENCODE:
            streamer_init(chn_id, &save_sd_config);
            if (g_yuv_buf_addr != NULL) {
                csi_dcache_invalid_range(g_yuv_buf_addr, g_yuv_buf_size);
                sample_start_stream_from_yuv_src(chn_id, (uint8_t*)g_yuv_buf_addr);
                aos_task_new("venc_stream", get_video_stream, (void*)chn_id, 4096);
            }
            break;

        case 'i':
            if (utils_get_resolution_param(optarg, &width, &height) == 0) {
                BL_LOGI("set resolution %dx%d\r\n", width, height);
                sample_set_chann_resolution(chn_id, width, height);
            } else {
                goto FAIL;
            }
            break;

        case H264_PROFILE:
            if (get_profile_param(optarg, &value) == 0) {
                set_h264_profile(chn_id, value);
            } else {
                goto FAIL;
            }
            break;

        case H264_LOW_POWER_MODE:
            value = atoi(optarg);
            set_low_power_mode(chn_id, value);
            break;

        case H264_DIRECT_LINK_EN:
            value = atoi(optarg);
            MM_Encoder_SetDirectLinkMode(value);
            break;

        case H264_FRAME_RATE:
            value = atoi(optarg);
            sample_set_chann_frame_rate(chn_id, value);
#ifndef IPC_STREAM_ON_E907
            rtsp_set_video_fps(value);
#endif
            break;

        case H264_RATE_CTRL_MODE:
            if (get_bitrate_mode_param(optarg, &value) == 0) {
                sample_set_chann_rc_mode(chn_id, value);
            } else {
                goto FAIL;
            }
            break;

        case H264_BIT_RATE:
            value = atoi(optarg);
            sample_set_chann_bit_rate(chn_id, value);
            break;

        case H264_MAX_BIT_RATE:
            value = atoi(optarg);
            sample_set_chann_vbr_max_bit_rate(chn_id, value);
            break;

        case H264_QUALITY_LEVEL:
            value = atoi(optarg);
            sample_set_chann_quality_level(chn_id, value);
            break;

        case H264_GOP_SIZE:
            value = atoi(optarg);
            set_gop_size(chn_id, value);
            break;

        case H264_IP_RATIO:
            value = atoi(optarg);
            sample_set_chann_ip_ratio(chn_id, value);
            break;

        case H264_MIN_QP:
            value = atoi(optarg);
            sample_set_chann_min_qp(chn_id, value);
            break;

        case H264_MAX_QP:
            value = atoi(optarg);
            sample_set_chann_max_qp(chn_id, value);
            break;

        case H264_SET_RATE_CTRL_LEVEL:
            value = atoi(optarg);
            sample_set_rc_level(chn_id, value);
            break;
            
        case H264_GET_RATE_CTRL_LEVEL:
            sample_get_rc_level(chn_id, &value);
            aos_cli_printf("[OK] rate ctrl level: %d\r\n", value);
            break;

        case H264_VIDEO:
            sleep_cnt = 0;
            value = atoi(optarg);

            streamer_init(chn_id, &save_sd_config);
            sample_start_stream(chn_id);
            aos_task_new("venc_stream", get_video_stream, (void*)chn_id, 4096);

            while (sleep_cnt < value) {
                sleep_cnt++;
                sleep(1);
            }

            bs_addr = (uint32_t)sw_bs_addr[chn_id];
            bs_size = stream_mngr[chn_id].tot_byte_cnt;
            aos_cli_printf("[OK] addr: 0x%x 0x%x\r\n", bs_addr, (uint32_t)(bs_addr + bs_size));

            stream_mngr[chn_id].stop_enc_flag = 1;
            break;

        case JPEG_QUALITY:
            value = atoi(optarg);
            sample_set_jpeg_quality(chn_id, value);
            break;

        case 'R':
            /* encoder is running if the target frame number is not reached */
            value = (stream_mngr[chn_id].curr_frm_cnt < max_frame_cnt);
            aos_cli_printf("[OK] %u\r\n", value);
            break;

        case 'F':
            value = atoi(optarg);
            max_frame_cnt = value;
            break;

        case BS_ADDR:
            value = (uint32_t)sw_bs_addr[chn_id];
            aos_cli_printf("[OK] %u\r\n", value);
            break;

        case BS_SIZE:
            value = stream_mngr[chn_id].tot_byte_cnt;
            aos_cli_printf("[OK] %u\r\n", value);
            break;

        case SD_FILE_PATH_NAME:
            save_sd_config.file_path_name = optarg;
            break;

        case SD_FILE_PATH:
            save_sd_config.path = optarg;
            break;

        case SD_FILE_NAME:
            save_sd_config.name = optarg;
            break;

        case SD_FILE_NUM:
            save_sd_config.file_save_cnt = atoi(optarg);
            aos_cli_printf("[OK] %u\r\n", save_sd_config.file_save_cnt);
            break;

        case SD_FILE_SIZE:
            save_sd_config.save_size = atoi(optarg);
            aos_cli_printf("[OK] %u\r\n", save_sd_config.save_size);
            break;

        case VENC_REG:
        case JPEG_REG:
        case SCENCE_CTRL_REG:{
            const char *format = "--%s";
            int payload_len_in = 0;
            int ret = -1;

            memset(module, '\0', sizeof(char) * 32);
            memset(argv_reg, '\0', sizeof(char) * 32);
            memset(argv_val, '\0', sizeof(char) * 128);
            memset(ret_string, '\0', sizeof(char) * 128);

            if(sscanf(argv[optind - 2], format, module) != 1) goto FAIL;
            sprintf(argv_reg, "%s", argv[optind - 1]);
            sprintf(argv_val, "%s", argv[optind]);
            payload_len_in = strlen(argv_val);

            //printf("cli avgv  module %s, argv_reg %s, argv_val %s\r\n", argv[optind - 2], argv[optind - 1], argv[optind]);
            //printf("cli  module %s, argv_reg %s, argv_val %s\r\n", module, argv_reg, argv_val);

            setChnId(chn_id);
            ret = parse_venc_cmd(module, argv_reg, argv_val, payload_len_in, ret_string);
            if (ret == -1) goto FAIL;
            else aos_cli_printf("[OK] %s\r\n", ret_string);
            break;
        }

        case 'h':
		default:
			show_usage();
            goto FAIL;
        }
    }
    aos_cli_printf("[OK] \r\n");
    return;

FAIL:
    aos_cli_printf("[NG] \r\n");
    return;
}

static void venc_white_box_test_cmd(char *buf, int len, int argc, char **argv)
{
extern void venc_white_box_test_main(void *param);
    venc_white_box_test_main(NULL);
}

const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
    { "venc", "encoder related operation", enc_cmd },
    { "venc_white_box_test", "video encoder white box test api", venc_white_box_test_cmd },
};

int helper_venc_cli_init(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user) / sizeof(cmds_user[0]));
    return 0;
}

