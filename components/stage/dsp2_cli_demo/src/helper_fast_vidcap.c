#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include <aos/kernel.h>
#include <vfs.h>
#include <cli.h>
#include <bl_dsp2.h>
#include <bl_venc.h>
#include <bl_mmsys.h>
#include "sensor.h"
#include "img_proc.h"
#include <bl808_mmsys_misc.h>
#include <bl808_clkrst.h>
#include <bl808_dvp2axi.h>
#include <bl808_dsp2_misc.h>

#include <bl808_mjenc.h>
#include "file_sink.h"
#include "mm_dsp2.h"
#include "mm_system.h"
#include "mm_encoder.h"
#include "sample_common.h"


#define SD_FILE_NAME_MAX_LEN                (64)
#define VENC_RESULT_FIFO_LEN                (4)

#define TASK_EXC_TYPE_INIT                  (0x0000)
#define TASK_EXC_TYPE_RECORD                (0x0001)
#define TASK_EXC_TYPE_RECORD_SD             (0x0002)
#define TASK_EXC_TYPE_RECORD_PSRAM          (0x0004)


enum numeric_short_options {
	H264_LOW_BANDW_MODE = 1000,
	H264_DUAL_ENC_EN,
	H264_DIRECT_LINK_EN,
	H264_RATE_CTRL_MODE,
	H264_BIT_RATE,
	H264_FRAME_RATE,
	H264_I_FRAME_INTERVAL,
	H264_QUALITY_LEVEL,
	H264_IP_RATIO,
	H264_PROFILE,
	JPEG_QUALITY,
	UPDATE_CFG,
	BS_ADDR,
	BS_SIZE,
	NO_WRITE,
	START_YUV_ENCODE,
	STOP_YUV_ENCODE,
};
    
typedef enum {
    WRITE_PSRAM = 0,
    WRITE_SD_CARD,
    WRITE_NONE,
} sink_type;

typedef struct {
    uint8_t* base_addr;
    uint32_t size;
    uint8_t* sec_base_addr;
    uint32_t sec_size;
} stream_buffer_t;

typedef struct {
    uint8_t* base_addr;
    uint32_t size;
	int curr_frm_cnt;
	int tot_byte_cnt;
    uint8_t *curr_wr_ptr;
    sink_type sink;
    void *file_sink;
} stream_manager_t;

static stream_manager_t stream_mngr[MAX_CHN_NUM];


static int streamer_init(int chn_id, save_file_config_t *record_info)
{
    stream_manager_t *streamer = &stream_mngr[chn_id];

    BL_LOGI("Alloc stream buffer\r\n");
    streamer->base_addr = BL_MallocDMA(PSRAM_ID_FOR_STREAM_BUF, STREAM_BUF_SIZE);
    streamer->size = STREAM_BUF_SIZE;
    streamer->curr_wr_ptr = streamer->base_addr;
    streamer->curr_frm_cnt = 0;
    streamer->tot_byte_cnt = 0;

    if (record_info && ((record_info->file_path_name) || (record_info->path))) {
        /* Mjpec save file by frame, one frame save into one file, the frame number is decided by file_save_cnt;
           Others save data one file, the size is decided by save_size */
        streamer->sink = WRITE_SD_CARD;
        streamer->file_sink = file_sink_new(record_info);
        if(!streamer->file_sink){
            BL_LOGE("File sink creat fail!!\r\n");
            return -1;
        }
    } else {
        streamer->sink = WRITE_PSRAM;
    }

    return 0;
}

static int streamer_deinit(int chn_id)
{
    stream_manager_t *streamer = &stream_mngr[chn_id];

    BL_FreeDMA(streamer->base_addr);

    return 0;
}

static int streamer_send_h264(stream_manager_t *streamer, const stream_buffer_t *frame)
{
    uint8_t *curr_wr_ptr = streamer->curr_wr_ptr;

    BL_LOGD("[H264] write addr 0x%p, size 0x%x\r\n", streamer->curr_wr_ptr, frame->size);

    if (streamer->sink != WRITE_NONE) {
        if ((curr_wr_ptr + frame->size) > (streamer->base_addr + streamer->size)) {
            BL_LOGE("stream size exceed limit 0x%x!\r\n", streamer->size);
            BL_ABORT();
        }

        BL60X_MemCpy_Fastest(curr_wr_ptr, (void *)frame->base_addr, frame->size);
        curr_wr_ptr += frame->size;
    }

    streamer->curr_wr_ptr = curr_wr_ptr;
    streamer->curr_frm_cnt++;
    streamer->tot_byte_cnt = curr_wr_ptr - streamer->base_addr;

    BL_LOGD("[H264] frm_cnt %d, tot_byte_cnt %d (0x%x)\r\n",
        streamer->curr_frm_cnt, streamer->tot_byte_cnt, streamer->tot_byte_cnt);

    return 0; 
}

static void vidcap_cmd(char *buf, int len, int argc, char **argv)
{
    static int stream_id = 0;
    static char fw_init = 0;
    uint32_t value = 0;

    printf("ENTRY %lu\r\n", xTaskGetTickCount());

    sample_system_quick_init();
    sample_encoder_init();
    
#if 1
    BL_LOGI ("start stream[%d]\r\n", stream_id);
    streamer_init(stream_id, NULL);
    sample_set_chann_resolution(0, 640, 480);
    sample_start_stream(0);
    vTaskDelay(2000);
    sample_close_stream(0);
    streamer_deinit(stream_id);
#endif

    return;
}

const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
    { "fast_vidcap", "fast video capture", vidcap_cmd },
};

int helper_fast_vidcap_cli_init(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user) / sizeof(cmds_user[0]));
    return 0;
}

