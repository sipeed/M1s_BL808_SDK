#include <string.h>
#include <aos/kernel.h>
#include <bl_dsp2.h>
#include <bl_venc.h>
#include <bl_mmsys.h>
#include <venc_framework.h>
#include "sensor.h"
#include "img_proc.h"
#include "bl808_clkrst.h"
#include "bl808_dsp2_misc.h"
#include "hdmi.h"
#include "mm_osal.h"
#include "mm_sensor.h"
#include "mm_dsp2.h"
#include "mm_encoder.h"
#include "mm_system.h"
#include "mm_utility.h"
#include "mm_debug.h"
#include "mm_encoder_param.h"

#define ALPHA_PRECISION         (8)

#define MAX_NUM_SENSOR              (2)
#define MAX_NUM_FRAMESOURCE         (4)
#define MAX_NUM_ENCODER             (3)
#define MAX_NUM_H264_ENCODER        (2)
#define FRAME_FIFO_LEN              (2)
#define VENC_RESULT_FIFO_LEN        (16)
#define HDMI_FRAMESRC_ID            (1)
#define MAX_NUM_RATECTRLLVL         (6)

#define ENC_MSG_ENCODER_STOPPED     (1)

#define MAX_NAME_SIZE               (64)

typedef void * mm_queue_t;
static bl_dsp2_update_fps_cb update_fps_cb;

typedef struct {
    MMSensorAttr snsAttr;
} SensorChann;

typedef struct {
    mm_queue_t streamQueue;
	MMDSP2FrmSrcAttr frmSrcAttr;
    bl_mmsys_bind_buffer_t bind_buffer;
    uint8_t* image_base_addr;
    bool image_dump_enable;
    int refCnt;
} FrmSrcChann;

typedef struct {
    MMEncoderFrameEncMode mode;
    uint8_t *yuv_sequence_addr;
} YuvEncodeMode;

typedef struct {
    venc_framework_device_t *dev;
    MMEncoderAttr encAttr;
    mm_queue_t streamQueue;
    mm_queue_t msgQueue;
    SemaphoreHandle_t mutex;
    int frmSrcChn;
    YuvEncodeMode yuv_encode_mode;
} EncoderChann;

typedef struct {
    uint32_t msgType;
} EncoderMsg;

typedef enum {
    FRMSRC_ID_H264_MAIN = 0,
    FRMSRC_ID_H264_SUB,
    FRMSRC_ID_MJPEG,
    FRMSRC_ID_AI,
    FRMSRC_ID_MAX
}FRMSRC_ID;

typedef enum {
    ENCODER_ID_H264_STREAMA = 0,
    ENCODER_ID_H264_STREAMB,
    ENCODER_ID_MJPEG,
    ENCODER_ID_MAX
}ENCODER_ID;

typedef enum {
    ENCODER_SCENCE_ID_STATIC = 0,
    ENCODER_SCENCE_ID_UNSTABLE,
    ENCODER_SCENCE_ID_MOVING,
    ENCODER_SCENCE_ID_BIGMOVING,
    ENCODER_SCENCE_ID_MAX
}ENCODER_SCENCE_ID;

typedef struct {
    int ip_ratio;
    int min_qp;
    int max_qp;
    MMEncoderGOPSizeCfg gopSizeCfg;
    int last_scence_status;
    int last_i_frame_id;
    int force_update;
    int update_HW_setting;
} EncoderScenceCtrl;

typedef struct {
    uint8_t rateCtrlLevel;
    uint32_t bitRate;
} EncoderRateCtrlLvl;

static SensorChann sensor_chn[MAX_NUM_SENSOR];
static FrmSrcChann framesource_chn[MAX_NUM_FRAMESOURCE];
static EncoderChann encoder_chn[MAX_NUM_ENCODER];
static MMEncoderRcAttr encoder_rc[MAX_NUM_H264_ENCODER];
static uint8_t gEncRecvRateLimit[MAX_NUM_ENCODER] = {0};

static bool direct_link_mode = false;
static bool is_virt_sensor = false;
static int g_pattern_gen_mode = -1;
static uint32_t* dsp2_tsrc_pic_addr = 0;
static bl_vin_config_t g_vin_cfg;
static int sensor_start_time = 0;
static EncoderScenceCtrl scence_ctrl = {0};
static MMEncoderScenceCtrlAttr scence_ctrl_reg[MAX_NUM_ENCODER] = {0};
static uint8_t scence_ctrl_en[MAX_NUM_ENCODER] = {0};
static EncoderRateCtrlLvl rate_ctrl_lvl[MAX_NUM_ENCODER] = {0};
static uint32_t bitrate_num_list[ENC_BITRATE_CTRL_NUM] = {512000, 1000000, 2000000, 4000000};

static VirtualSensorInfo virt_sns_info = {
    .width = 1920,
    .height = 1080,
    .sensor_name = "SC2232",
};

struct dsp2_sensor_if sensor_func[2] = {0};
static void MM_Encoder_InitVbrDynamicQP(int encChan);

static int check_resolution(uint32_t width, uint32_t height)
{
    if (width < 160 || width > 1920) {
        return -1;
    }

    if (height < 120 || height > 1080) {
        return -1;
    }

    return 0;
}

static void alloc_cb(venc_framework_device_t *device, size_t suggested_size, int is_high_usage, venc_buf_t *buf)
{
    uint8_t mem_id = (is_high_usage) ? 1 : 0;
    buf->base = (void*)BL_MallocDMA(mem_id, suggested_size);
    buf->len = suggested_size;
}

static void free_cb(venc_framework_device_t *device, void* buf_base)
{
    BL_FreeDMA(buf_base);
}

static void recv_cb(venc_framework_device_t *device, venc_result_t *result)
{
    int ret;
    BaseType_t xHigherPriorityTaskWoken = pdTRUE;   /* always yeild assuming the HW data needs handling ASAP*/

    EncoderChann *enc_chann = &encoder_chn[result->stream_id];

    ret = BL_Queue_Put_Item_FromISR(enc_chann->streamQueue, result);
    if (pdFALSE == ret) {
        if (gEncRecvRateLimit[result->stream_id]++ < 5)
            BL_LOGE("Put item into queue fail! %s line:%d\r\n", __func__, __LINE__);
    } else {
        gEncRecvRateLimit[result->stream_id] = 0;
    }

    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

static void stop_cb(venc_framework_device_t *device, int stream_id)
{
    int ret;
    EncoderMsg enc_msg;
    EncoderChann *enc_chann = &encoder_chn[stream_id];

    enc_msg.msgType = ENC_MSG_ENCODER_STOPPED;
    ret = BL_Queue_Put_Item_FromISR(enc_chann->msgQueue, &enc_msg);
    if (pdFALSE == ret) {
        BL_LOGE("Put item into queue fail! %s line:%d\r\n", __func__, __LINE__);
    }
}

static void frame_ready_cb(void *usrdata, bl_dsp2_frame_desc_t *frame)
{
    int ret;
    FrmSrcChann *fs_chann;
    BaseType_t xHigherPriorityTaskWoken = pdTRUE;   /* always yeild assuming the HW data needs handling ASAP*/

    fs_chann = &framesource_chn[frame->chann_id];

    ret = BL_Queue_Put_Item_FromISR(fs_chann->streamQueue, frame);
    if (pdFALSE == ret) {
        BL_LOGE("Put item into queue fail! %s line:%d\r\n", __func__, __LINE__);
    }

    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

static void set_h264_encoder_default(int encChn)
{
    venc_framework_device_t *device;

    device = encoder_chn[encChn].dev;

    device->init(device);
}

static void set_jpeg_encoder_default(int encChn)
{
    venc_framework_device_t *device;

    device = encoder_chn[encChn].dev;

    device->init(device);
    device->set_video_param(device, VIDEO_FORMAT_KEY_QUALITY, 50);
}

static int set_frame_src_default(FRMSRC_ID frmSrcChn, MMDSP2FrmSrcAttr *frmSrcAttr)
{
    MMSensorAttr snsAttr;
    MM_Sensor_GetChnAttr(0, &snsAttr);

    switch (frmSrcChn) {
        case FRMSRC_ID_H264_MAIN:
            frmSrcAttr->pixFmt = PIX_FMT_NV12;
            frmSrcAttr->picWidth = snsAttr.picWidth;
            frmSrcAttr->picHeight = snsAttr.picHeight;
            frmSrcAttr->outFrmRateNum = 22;
            frmSrcAttr->outFrmRateDen = 2;
            frmSrcAttr->isFullRange = false;
        case FRMSRC_ID_H264_SUB:
            frmSrcAttr->pixFmt = PIX_FMT_NV12;
            frmSrcAttr->picWidth = 640;
            frmSrcAttr->picHeight = 480;
            frmSrcAttr->outFrmRateNum = 20;
            frmSrcAttr->outFrmRateDen = 2;
            frmSrcAttr->isFullRange = false;
        case FRMSRC_ID_MJPEG:
            frmSrcAttr->pixFmt = PIX_FMT_NV12;
            frmSrcAttr->picWidth = snsAttr.picWidth;
            frmSrcAttr->picHeight = snsAttr.picHeight;
            frmSrcAttr->outFrmRateNum = snsAttr.fps;
            frmSrcAttr->outFrmRateDen = 1;
            frmSrcAttr->isFullRange = true;
        case FRMSRC_ID_AI:
            frmSrcAttr->pixFmt = PIX_FMT_NV12;
            frmSrcAttr->picWidth = snsAttr.picWidth;
            frmSrcAttr->picHeight = snsAttr.picHeight;
            frmSrcAttr->outFrmRateNum = snsAttr.fps;
            frmSrcAttr->outFrmRateDen = 1;
            frmSrcAttr->isFullRange = true;
            frmSrcAttr->dsp2Position = BL_IMAGE_DUMP_SRC_YUV2RGB;
            break;
        default:
            return -1;
    }

    return 0;
}

static int do_set_framesrc_out_frame_rate(int frmSrcChn, uint32_t outFrmRateNum, uint32_t outFrmRateDen)
{
    uint32_t sns_fps;
    MMSensorAttr snsAttr;

    MM_Sensor_GetChnAttr(0, &snsAttr);
    sns_fps = snsAttr.fps;

    if (outFrmRateNum > (sns_fps * outFrmRateDen)) {
        BL_LOGE("Invalid chann fps. Must be lower than sensor fps\r\n");
        return -1;
    }

    bl_dsp2_set_channel_frame_rate(frmSrcChn, sns_fps, outFrmRateNum, outFrmRateDen);

    return 0;
}

static int do_set_encoder_resolution(int encChn, uint32_t picWidth, uint32_t picHeight)
{
    venc_framework_device_t *device;

    device = encoder_chn[encChn].dev;
    device->set_resolution(device, picWidth, picHeight);

    return 0;
}

static int do_set_encoder_frame_rate(int encChn, uint32_t frmRateNum, uint32_t frmRateDen)
{
    venc_framework_device_t *device;

    device = encoder_chn[encChn].dev;

    /* FPS[31:16] = frmRateNum, FPS[15:0] = frmRateDen */
    device->set_video_param(device, VIDEO_FORMAT_KEY_FRAME_RATE, (frmRateNum << 16 | frmRateDen));

    return 0;
}

static int do_set_encoder_gop_size(int encChn, uint32_t gopSize)
{
    venc_framework_device_t *device;

    device = encoder_chn[encChn].dev;
    device->set_video_param(device, VIDEO_FORMAT_KEY_GOP_SIZE, gopSize);

    return 0;
}

static int do_set_encoder_profile(int encChn, MMEncoderProfile profile)
{
    venc_framework_device_t *device;

    device = encoder_chn[encChn].dev;
    device->set_video_param(device, VIDEO_FORMAT_KEY_PROFILE, (int)profile);

    return 0;
}

static int do_set_low_power_mode(int encChn, MMEncoderLowPowerMode lowPwrMode)
{
    venc_framework_device_t *device;

    device = encoder_chn[encChn].dev;
    device->set_video_param(device, VIDEO_FORMAT_KEY_LOW_POWER_MODE, (int)lowPwrMode);

    return 0;
}

static int do_set_encoder_rc_mode(int encChn, MMEncoderRcMode rcMode)
{
    venc_framework_device_t *device;

    device = encoder_chn[encChn].dev;
    device->set_video_param(device, VIDEO_FORMAT_KEY_BITRATE_MODE, (int)rcMode);

    return 0;
}

static int do_set_encoder_bitrate(int encChn, uint32_t bitRate)
{
    venc_framework_device_t *device;

    device = encoder_chn[encChn].dev;
    device->set_video_param(device, VIDEO_FORMAT_KEY_BIT_RATE, bitRate);

    return 0;
}

static int do_set_i_bias_level(int encChn, int iBaisLvl)
{
    venc_framework_device_t *device;
    int ip_ratio;

    device = encoder_chn[encChn].dev;

    /* TODO: add logic to calculate ip_ratio from iBaisLvl */
    ip_ratio = iBaisLvl;

    device->set_video_param(device, VIDEO_FORMAT_KEY_FORCE_IP_RATIO, ip_ratio);

    return 0;
}

static int do_set_encoder_init_qp(int encChn, uint32_t qp)
{
    venc_framework_device_t *device;

    device = encoder_chn[encChn].dev;

    device->set_video_param(device, VIDEO_FORMAT_KEY_INIT_QP, qp);

    return 0;
}

static int do_set_encoder_min_qp(int encChn, uint32_t qp)
{
    venc_framework_device_t *device;

    device = encoder_chn[encChn].dev;

    device->set_video_param(device, VIDEO_FORMAT_KEY_MIN_QP, qp);

    return 0;
}

static int do_set_encoder_max_qp(int encChn, uint32_t qp)
{
    venc_framework_device_t *device;

    device = encoder_chn[encChn].dev;

    device->set_video_param(device, VIDEO_FORMAT_KEY_MAX_QP, qp);

    return 0;
}

static int do_set_encoder_quality_lvl(int encChn, uint32_t qualityLvl)
{
    venc_framework_device_t *device;
    int target_qp;

    device = encoder_chn[encChn].dev;

    /* TODO: add logic to calculate target QP from quality level */
    target_qp = qualityLvl;

    device->set_video_param(device, VIDEO_FORMAT_KEY_TARGET_I_QP, target_qp);
    device->set_video_param(device, VIDEO_FORMAT_KEY_TARGET_P_QP, target_qp);

    return 0;
}

static int do_set_encoder_jpeg_quality(int encChn, uint32_t quality)
{
    venc_framework_device_t *device;

    device = encoder_chn[encChn].dev;
    device->set_video_param(device, VIDEO_FORMAT_KEY_QUALITY, quality);

    return 0;
}

static uint32_t calc_dsp2_clk(uint32_t pix_clk)
{
    // dsp2 clk should be higher than sensor clk
    //FIXME TODO  dsp2 clk value should be define accrording to DSP2_Clk_Sel
    return 80000000;
    // return 120000000;
}

static void cal_dsp2_clk(uint32_t pix_clk, uint32_t *dsp2_clk)
{
    uint32_t dsp2_clk_tmp;

    /* config DSP2 clock */
    dsp2_clk_tmp = calc_dsp2_clk(pix_clk);
    // TODO dsp2 clk should be higher than sensor clk,
    DSP2_Clk_Sel(DSP2_CLK_160MHz, ENABLE, 1);
    // DSP2_Clk_Sel(DSP2_CLK_240MHz, ENABLE, 1);
    *dsp2_clk = dsp2_clk_tmp;
}

static void build_vin_from_sensor(bl_vin_config_t *vin_cfg)
{
    uint32_t pix_clk;
    BAYER_PATTERN_E bayer;
    MMSensorAttr sns_attr;
    const char* curr_sensor;

    sensor_get_total_window(&(vin_cfg->total_win));
    sensor_get_output_window(&(vin_cfg->act_win));
    sensor_get_dsp2_output_window(&(vin_cfg->out_win));

    sensor_get_pix_clk(&pix_clk);
    vin_cfg->pix_clk = pix_clk;

    sensor_get_bayer_pattern(&bayer);
    vin_cfg->bayer_pattern = bayer;

    vin_cfg->bit_depth = 10;
    vin_cfg->is_hsync_toggle_in_vblank = 0;
    vin_cfg->is_virtual = 0;

    sensor_get_name(&curr_sensor);
    strncpy(vin_cfg->sensor_name, curr_sensor, sizeof(vin_cfg->sensor_name) - 1);

    sns_attr.picWidth  = vin_cfg->out_win.width;
    sns_attr.picHeight = vin_cfg->out_win.height;
    sensor_get_fps(&(sns_attr.fps));
    vin_cfg->fps = sns_attr.fps;
    MM_Sensor_SetChnAttr(0, &sns_attr);

    cal_dsp2_clk(vin_cfg->pix_clk, &vin_cfg->dsp2_clk);

}

void build_vin_from_virt_sensor(bl_vin_config_t *vin_cfg, VirtualSensorInfo *vir_sns_info)
{
    MMSensorAttr sns_attr;

    vin_cfg->total_win.width  = vir_sns_info->width + 100;
    vin_cfg->total_win.height = vir_sns_info->height + 100;

    vin_cfg->act_win.width  = vir_sns_info->width;
    vin_cfg->act_win.height = vir_sns_info->height;

    vin_cfg->out_win.width  = vir_sns_info->width;
    vin_cfg->out_win.height = vir_sns_info->height;

    vin_cfg->pix_clk = 40000000;
    vin_cfg->bayer_pattern = BAYER_PATTERN_BG;

    vin_cfg->bit_depth = 12;
    vin_cfg->is_hsync_toggle_in_vblank = 1;
    vin_cfg->is_virtual = 1;

    strncpy(vin_cfg->sensor_name, vir_sns_info->sensor_name, sizeof(vin_cfg->sensor_name) - 1);

    sns_attr.picWidth  = vin_cfg->out_win.width;
    sns_attr.picHeight = vin_cfg->out_win.height;
    sns_attr.fps = (int)(vin_cfg->pix_clk/vin_cfg->total_win.width/vin_cfg->total_win.width);
    MM_Sensor_SetChnAttr(0, &sns_attr);

    cal_dsp2_clk(vin_cfg->pix_clk, &vin_cfg->dsp2_clk);

}


static void build_frame_source_chn(void)
{
    int i;
    MMDSP2FrmSrcAttr frmSrcAttr;

    for (i = 0; i < FRMSRC_ID_MAX; i++) {
        set_frame_src_default(i, &frmSrcAttr);
        MM_DSP2_CreateFrameSrcChn(i, &frmSrcAttr);
    }

}

static int parse_scence_ctrl_reg_from_bitrate(MMEncoderScenceCtrlAttr *encScenceCtrlAttr, uint32_t bitrate)
{
    int i = 0, bitrate_idx = 0;
    int alpha_hex = 0;
    int scence_thr, gop_size, ip_ratio, min_qp, max_qp;

    if (bitrate <= bitrate_num_list[ENC_BITRATE_CTRL_512K]) {
        bitrate_idx = 0;
        for (i = 0; i < ENC_SC_MODE_NUM; i++) {
            encScenceCtrlAttr->scence_attr[i].scence_thr = bitrate_ctrl_init_reg.bitrate_ctrl[bitrate_idx].scence_attr[i].scence_thr;
            encScenceCtrlAttr->scence_attr[i].gop_size = bitrate_ctrl_init_reg.bitrate_ctrl[bitrate_idx].scence_attr[i].gop_size;
            encScenceCtrlAttr->scence_attr[i].ip_ratio = bitrate_ctrl_init_reg.bitrate_ctrl[bitrate_idx].scence_attr[i].ip_ratio;
            encScenceCtrlAttr->scence_attr[i].min_qp = bitrate_ctrl_init_reg.bitrate_ctrl[bitrate_idx].scence_attr[i].min_qp;
            encScenceCtrlAttr->scence_attr[i].max_qp = bitrate_ctrl_init_reg.bitrate_ctrl[bitrate_idx].scence_attr[i].max_qp;
        }
    } else if (bitrate >= bitrate_num_list[ENC_BITRATE_CTRL_4M]) {
        bitrate_idx = 3;
        for (i = 0; i < ENC_SC_MODE_NUM; i++) {
            encScenceCtrlAttr->scence_attr[i].scence_thr = bitrate_ctrl_init_reg.bitrate_ctrl[bitrate_idx].scence_attr[i].scence_thr;
            encScenceCtrlAttr->scence_attr[i].gop_size = bitrate_ctrl_init_reg.bitrate_ctrl[bitrate_idx].scence_attr[i].gop_size;
            encScenceCtrlAttr->scence_attr[i].ip_ratio = bitrate_ctrl_init_reg.bitrate_ctrl[bitrate_idx].scence_attr[i].ip_ratio;
            encScenceCtrlAttr->scence_attr[i].min_qp = bitrate_ctrl_init_reg.bitrate_ctrl[bitrate_idx].scence_attr[i].min_qp;
            encScenceCtrlAttr->scence_attr[i].max_qp = bitrate_ctrl_init_reg.bitrate_ctrl[bitrate_idx].scence_attr[i].max_qp;
        }
    } else {
        for (bitrate_idx = 1; bitrate_idx < ENC_BITRATE_CTRL_NUM; bitrate_idx++) {
            if (bitrate < bitrate_num_list[bitrate_idx]) {
                alpha_hex = ((bitrate_num_list[bitrate_idx] - bitrate) << ALPHA_PRECISION) / (bitrate_num_list[bitrate_idx] - bitrate_num_list[bitrate_idx - 1]);//color_temp dist weight is 2
                for (i = 0; i < ENC_SC_MODE_NUM; i++) {
                    encScenceCtrlAttr->scence_attr[i].scence_thr = alpha_blend(bitrate_ctrl_init_reg.bitrate_ctrl[bitrate_idx - 1].scence_attr[i].scence_thr, bitrate_ctrl_init_reg.bitrate_ctrl[bitrate_idx].scence_attr[i].scence_thr, alpha_hex, ALPHA_PRECISION);
                    encScenceCtrlAttr->scence_attr[i].gop_size = alpha_blend(bitrate_ctrl_init_reg.bitrate_ctrl[bitrate_idx - 1].scence_attr[i].gop_size, bitrate_ctrl_init_reg.bitrate_ctrl[bitrate_idx].scence_attr[i].gop_size, alpha_hex, ALPHA_PRECISION);
                    encScenceCtrlAttr->scence_attr[i].ip_ratio = alpha_blend(bitrate_ctrl_init_reg.bitrate_ctrl[bitrate_idx - 1].scence_attr[i].ip_ratio, bitrate_ctrl_init_reg.bitrate_ctrl[bitrate_idx].scence_attr[i].ip_ratio, alpha_hex, ALPHA_PRECISION);
                    encScenceCtrlAttr->scence_attr[i].min_qp = alpha_blend(bitrate_ctrl_init_reg.bitrate_ctrl[bitrate_idx - 1].scence_attr[i].min_qp, bitrate_ctrl_init_reg.bitrate_ctrl[bitrate_idx].scence_attr[i].min_qp, alpha_hex, ALPHA_PRECISION);
                    encScenceCtrlAttr->scence_attr[i].max_qp = alpha_blend(bitrate_ctrl_init_reg.bitrate_ctrl[bitrate_idx - 1].scence_attr[i].max_qp, bitrate_ctrl_init_reg.bitrate_ctrl[bitrate_idx].scence_attr[i].max_qp, alpha_hex, ALPHA_PRECISION);
                }
                break;
            }
        }
    }

    for (i = 0; i < ENC_SC_MODE_NUM; i++) {
        BL_LOGI("========encScenceCtrlAttr %d,%d,  %d, %d, %d, %d, %d\r\n",bitrate_idx, i,
                    encScenceCtrlAttr->scence_attr[i].scence_thr,
                    encScenceCtrlAttr->scence_attr[i].gop_size,
                    encScenceCtrlAttr->scence_attr[i].ip_ratio,
                    encScenceCtrlAttr->scence_attr[i].min_qp,
                    encScenceCtrlAttr->scence_attr[i].max_qp);
    }

    return 0;
}

static void MM_System_CHN_Init()
{
    memset(sensor_chn,      0, MAX_NUM_SENSOR*sizeof(SensorChann));
    memset(framesource_chn, 0, MAX_NUM_FRAMESOURCE*sizeof(FrmSrcChann));
    memset(encoder_chn,     0, MAX_NUM_ENCODER*sizeof(EncoderChann));
    memset(encoder_rc,      0, MAX_NUM_H264_ENCODER*sizeof(MMEncoderRcAttr));
}


/************************************* sensor call back functions *************************************/
int MM_Sensor_RegisterCb(uint32_t chanId, struct dsp2_sensor_if** pstSensorFunc)
{
    memset(&sensor_func[chanId], 0, sizeof(struct dsp2_sensor_if));

    sensor_func[chanId].name                 = sensor_get_name;
    sensor_func[chanId].init                 = sensor_init;
    sensor_func[chanId].reset                = sensor_reset;

    sensor_func[chanId].get_gain             = sensor_get_gain;
    sensor_func[chanId].set_gain             = sensor_set_gain;
    sensor_func[chanId].get_intt             = sensor_get_exposure;
    sensor_func[chanId].set_intt             = sensor_set_exposure;
    sensor_func[chanId].set_flipmirror       = sensor_set_flipmirror;
    sensor_func[chanId].get_flipmirror       = sensor_get_flipmirror;

    sensor_func[chanId].get_fps               = sensor_get_fps;
    sensor_func[chanId].get_bayer_pattern     = sensor_get_bayer_pattern;
    sensor_func[chanId].get_sensor_window     = sensor_get_total_window;//total_win
    sensor_func[chanId].get_act_window        = sensor_get_output_window;//act_win
    sensor_func[chanId].get_pic_window        = sensor_get_dsp2_output_window;//out_win

    sensor_func[chanId].set_sns_fmt          = sensor_setFmt;
    sensor_func[chanId].set_sns_reg          = sensor_set_sensor_reg;

    *pstSensorFunc = &sensor_func[chanId];

    return 0;
}

int MM_Sensor_UnRegisterCb(uint32_t chanId)
{
    memset(&sensor_func[chanId], 0, sizeof(struct dsp2_sensor_if));

    return 0;
}

int MM_Sensor_Init(void)
{
    DSP2_DVP_TSrc_Disable(DVP_TSRC_DSP2);
    CLKRST_ResetDSP2TSrc();  /* TODO: workaround HW bug, DDR input leads to corrupted image */

    if (!is_virt_sensor) {
        if (sensor_init() < 0) return -1;
    }

    return 0;
}

int MM_Sensor_GetSensorTime(void)
{
    return sensor_start_time;
}

int MM_Sensor_SetFmt(VIDEO_MODE_E format)
{
    int ret = 0;

    if (!is_virt_sensor) {
        if (sensor_setFmt(format) < 0) return -1;
        build_vin_from_sensor(&g_vin_cfg);
    } else {
        build_vin_from_virt_sensor(&g_vin_cfg, &virt_sns_info);
    }

    build_frame_source_chn();

    return 0;
}

int MM_Sensor_GetFmt(VIDEO_MODE_E *format)
{
    sensor_getFmt(format);

    return 0;
}

int MM_Sensor_ChangeFmt(VIDEO_MODE_E format)
{
    if (sensor_disable() < 0) return -1;
    if (MM_Sensor_Init() < 0) return -1;
    if (MM_Sensor_SetFmt(format) < 0) return -1;

    return 0;
}

int MM_Sensor_ChangeFPS(uint32_t fps)
{
    if (sensor_set_fps(fps) < 0) return -1;

    return 0;
}

int MM_Sensor_GetFPS(uint32_t *fps)
{
    if (sensor_get_fps(fps) < 0) return -1;

    return 0;
}

int MM_DSP2_SetVinAttr(MMDSP2VinAttr *vin_attr)
{
    MMSensorAttr snsAttr;

    if (sensor_is_enabled())
        return -1;

    g_vin_cfg.total_win.width =  vin_attr->total_win.width;
    g_vin_cfg.total_win.height = vin_attr->total_win.height;
    g_vin_cfg.act_win.width =  vin_attr->act_win.width;
    g_vin_cfg.act_win.height = vin_attr->act_win.height;
    g_vin_cfg.out_win.width =  vin_attr->out_win.width;
    g_vin_cfg.out_win.height = vin_attr->out_win.height;
    g_vin_cfg.bayer_pattern = vin_attr->bayer_pattern;
    g_vin_cfg.fps = vin_attr->fps;

    snsAttr.picWidth = g_vin_cfg.out_win.width;
    snsAttr.picHeight = g_vin_cfg.out_win.height;
    snsAttr.fps = g_vin_cfg.fps;
    MM_Sensor_SetChnAttr(0, &snsAttr);

    return 0;

}

int MM_DSP2_GetVinAttr(MMDSP2VinAttr *vin_attr)
{
    vin_attr->total_win.width =  g_vin_cfg.total_win.width;
    vin_attr->total_win.height = g_vin_cfg.total_win.height;
    vin_attr->act_win.width =  g_vin_cfg.act_win.width;
    vin_attr->act_win.height = g_vin_cfg.act_win.height;
    vin_attr->out_win.width =  g_vin_cfg.out_win.width;
    vin_attr->out_win.height = g_vin_cfg.out_win.height;
    vin_attr->bayer_pattern = g_vin_cfg.bayer_pattern;
    vin_attr->fps = g_vin_cfg.fps;

    return 0;
}

int MM_DSP2_GetBinAddr(uint32_t *addr,uint32_t *size)
{
    img_param_get_sw_bin_Addr(addr);
    *size = sizeof(BL_IMG_PARAM_SW_BIN_DESC_T);

    return 0;
}

int MM_DSP2_LoadDsp2Param(uint32_t *dsp2_param_buff)
{
    uint32_t addr = NULL;
    BL_IMG_PARAM_SW_BIN_DESC_T *addr_init = NULL;

    img_param_get_sw_bin_Addr(&addr);
    addr_init = addr;

    memcpy(addr_init, dsp2_param_buff, sizeof(BL_IMG_PARAM_SW_BIN_DESC_T));
    return 0;
}

int MM_DSP2_SetDsp2Param(BL_IMG_PARAM_SW_BIN_DESC_T *pstDefaultParam)
{
    uint32_t addr = NULL;
    BL_IMG_PARAM_SW_BIN_DESC_T *addr_init = NULL;

    img_param_get_sw_bin_Addr(&addr);
    addr_init = addr;

    memcpy(addr_init->name, pstDefaultParam->name, sizeof(char) * 16);
    memcpy(&addr_init->state_tbl, &pstDefaultParam->state_tbl, sizeof(img_param_state_container_t));
    memcpy(&addr_init->ae_tbl, &pstDefaultParam->ae_tbl, sizeof(ae_container_sw_t));
    memcpy(&addr_init->awb_tbl, &pstDefaultParam->awb_tbl, sizeof(awb_container_sw_t));
    memcpy(&addr_init->blc_tbl, &pstDefaultParam->blc_tbl, sizeof(blc_container_sw_t));
    memcpy(&addr_init->dpc_tbl, &pstDefaultParam->dpc_tbl, sizeof(dpc_container_sw_t));
    memcpy(&addr_init->bnr_tbl, &pstDefaultParam->bnr_tbl, sizeof(bnr_container_sw_t));
    memcpy(&addr_init->lsc_tbl, &pstDefaultParam->lsc_tbl, sizeof(lsc_container_sw_t));
    memcpy(&addr_init->ccm_tbl, &pstDefaultParam->ccm_tbl, sizeof(ccm_container_sw_t));
    memcpy(&addr_init->gamma_cal_tbl, &pstDefaultParam->gamma_cal_tbl, sizeof(gamma_container_cal_t));
    memcpy(&addr_init->gamma_tbl, &pstDefaultParam->gamma_tbl, sizeof(gamma_container_sw_t));
    memcpy(&addr_init->wdr_tbl, &pstDefaultParam->wdr_tbl, sizeof(wdr_container_sw_t));
    memcpy(&addr_init->sat_tbl, &pstDefaultParam->sat_tbl, sizeof(sat_container_sw_t));
    memcpy(&addr_init->yc_tbl, &pstDefaultParam->yc_tbl, sizeof(yc_container_sw_t));
    memcpy(&addr_init->nr_tbl, &pstDefaultParam->nr_tbl, sizeof(nr_container_sw_t));
    memcpy(&addr_init->ee_tbl, &pstDefaultParam->ee_tbl, sizeof(ee_container_sw_t));
    memcpy(&addr_init->cs_tbl, &pstDefaultParam->cs_tbl, sizeof(cs_container_sw_t));

    return 0;
}

int MM_DSP2_GetDsp2Reg(uint32_t addr,uint32_t *data)
{
    bl_get_addr_data(addr, data);

    return 0;
}

int MM_DSP2_SetDsp2Reg(uint32_t addr,uint32_t data)
{
    bl_set_addr_data(addr, data);

    return addr;
}

int MM_DSP2_GetHWmoduleCfg(uint32_t *modulecfg)
{
    int i, val, shift = 0;
    uint32_t module_val;
    BL_Fun_Type state;
    module_val = 0;

    for (i = 0; i < DSP2_ADJ_PARAM_NUM; i++) {
        state = imgproc_is_module_enable(i);
        val = state;

        switch (i)
        {
        case DSP2_ADJ_AE:
            shift = DSP2_HW_MODULE_AE;
            break;
        case DSP2_ADJ_AWB:
            shift = DSP2_HW_MODULE_AWB;
            break;
        case DSP2_ADJ_DPC:
            shift = DSP2_HW_MODULE_DPC;
            break;
        case DSP2_ADJ_BNR:
            shift = DSP2_HW_MODULE_BNR;
            break;
        case DSP2_ADJ_LSC:
            shift = DSP2_HW_MODULE_LSC;
            break;
        case DSP2_ADJ_CCM:
            shift = DSP2_HW_MODULE_CCM;
            break;
        case DSP2_ADJ_GAMMA:
            shift = DSP2_HW_MODULE_GAMMA;
            break;
        case DSP2_ADJ_WDR:
            shift = DSP2_HW_MODULE_WDR;
            break;
        case DSP2_ADJ_EE:
            shift = DSP2_HW_MODULE_EE;
            break;
        case DSP2_ADJ_CS:
            shift = DSP2_HW_MODULE_CS;
            break;
        default:
            val = 0;
            shift = 0;
            continue;
        }

        module_val += (val << shift);
    }

    *modulecfg = module_val;
    return 0;
}

int MM_DSP2_SetHWmoduleCfg(uint32_t modulecfg)
{
    int i, shift;
    BL_Fun_Type state;
    uint32_t state_list = modulecfg;

    for (i = 0; i < DSP2_HW_MODULE_PARAM_NUM; i++) {
        if (state_list & 0x1) state = ENABLE;
        else state = DISABLE;

        switch (i)
        {
        case DSP2_HW_MODULE_AE:
            shift = DSP2_ADJ_AE;
            break;
        case DSP2_HW_MODULE_AWB:
            shift = DSP2_ADJ_AWB;
            break;
        case DSP2_HW_MODULE_DPC:
            shift = DSP2_ADJ_DPC;
            break;
        case DSP2_HW_MODULE_BNR:
            shift = DSP2_ADJ_BNR;
            break;
        case DSP2_HW_MODULE_LSC:
            shift = DSP2_ADJ_LSC;
            break;
        case DSP2_HW_MODULE_CCM:
            shift = DSP2_ADJ_CCM;
            break;
        case DSP2_HW_MODULE_GAMMA:
            shift = DSP2_ADJ_GAMMA;
            break;
        case DSP2_HW_MODULE_WDR:
            shift = DSP2_ADJ_WDR;
            break;
        case DSP2_HW_MODULE_EE:
            shift = DSP2_ADJ_EE;
            break;
        case DSP2_HW_MODULE_CS:
            shift = DSP2_ADJ_CS;
            break;
        default:
            shift = 0;
            continue;
        }
        state_list = (state_list >> 1);

        imgproc_set_module_enable(shift, state);
    }

    return 0;
}

void MM_DSP2_Update_FPS_Register(bl_dsp2_update_fps_cb *cb)
{
    update_fps_cb = *cb;
    imgproc_update_fps_register(&update_fps_cb);
}

int MM_DSP2_Status(void)
{
    int ret = 0, status = 0;
    ret = imgproc_status(&status);
    if (ret < 0) return -1;

    return status;
}

int MM_DSP2_Init(void)
{
    DSP2_Enable();

    bl_dsp2_misc_init();
    bl_dsp2_sys_init();
    bl_dsp2_cfg_init(&g_vin_cfg);
    bl_hdmi_init();

    // move scaler init to other place
    // bl_dsp2_set_scaler_resolution(0, &(vin_cfg.out_win));
    // bl_dsp2_set_scaler_resolution(1, &(vin_cfg.out_win));

    imgproc_init(&g_vin_cfg);

    return 0;
}

int MM_DSP2_Run(void)
{

    uint32_t buf_size;
    uint8_t* buf_addr;
    uint32_t pix_clk;
    uint32_t dsp2_clk;

    imgproc_start();

    if (!is_virt_sensor) {
        // dvp
        if (DSP2_INPUT_DVP == DSP2_INPUT_MODE) {
            DSP2_MSIC_Dtsrc_Set_Mode(DVP_TSRC_SRC_DVP);
            bl_vin_enable_dvp_input(g_vin_cfg.pix_clk, g_vin_cfg.dsp2_clk);
        }
        // mipi
        else {
            DSP2_MSIC_Dtsrc_Set_Mode(DVP_TSRC_SRC_MIPI_CSI);
            bl_vin_enable_mipi_input(g_vin_cfg.pix_clk, g_vin_cfg.dsp2_clk, DSP2_INPUT_MODE);
        }
        sensor_enable();
        sensor_start_time = xTaskGetTickCount();
    } else {
        if (g_pattern_gen_mode != -1) {
            bl_vin_enable_fakedata_input(g_pattern_gen_mode);
        }
        else {
            buf_size = (g_vin_cfg.act_win.width * g_vin_cfg.act_win.height << 1);   /* bayer raw image size */
            if (dsp2_tsrc_pic_addr == 0) {
                dsp2_tsrc_pic_addr = BL_MallocDMA(PSRAM_ID_FOR_REF_BUF, buf_size);
            } else return 0;
            bl_vin_enable_raw_file_input((uint8_t *)dsp2_tsrc_pic_addr, buf_size);
        }
    }
    return 0;
}

int MM_DSP2_Pause(void)
{
    imgproc_stop();
#if ENABLE_3DNR
    if (!is_virt_sensor) bl_dsp2_disable_3dnr();
#endif
    DSP2_Disable();
    return 0;
}

int MM_DSP2_Resume(void)
{
    int ret;

    MM_DSP2_Init();
    ret = MM_DSP2_Run();

    return ret;
}

int MM_DSP2_Exit(void)
{
    imgproc_stop();

#if ENABLE_3DNR
    if (!is_virt_sensor) bl_dsp2_disable_3dnr();
#endif
    bl_dsp2_disable_dump_chann(0);
    bl_dsp2_disable_dump_chann(1);

    DSP2_Disable();

    return 0;
}

int MM_DSP2_Init_Run(void)
{
    MM_System_Init();

    MM_Sensor_Init();
    if (MM_Sensor_SetFmt(VIDEO_MODE_1080P_25) < 0) return -1;

    MM_DSP2_Exit();
    MM_DSP2_Init();
    MM_DSP2_Run();

#if PRINT_FAST_CAP_TIMING
    printf("SNS START %lu\r\n", xTaskGetTickCount());
#endif

    return 0;
}

int MM_Sensor_Raw2Mem_Init_Run(VIDEO_MODE_E video_mode)
{
    uint32_t dsp2_clk;
    MMDSP2FrmSrcAttr chn_attr;

    MM_Sensor_Init();
    sensor_setFmt(video_mode);
    build_vin_from_sensor(&g_vin_cfg);
    bl_dsp2_tg_init(&g_vin_cfg);
    bl_dsp2_sys_init();

    chn_attr.picWidth = g_vin_cfg.act_win.width;
    chn_attr.picHeight = g_vin_cfg.act_win.height;
    chn_attr.dsp2Position = DSP2_POSITION_DSP2_INPUT;
    framesource_chn[0].frmSrcAttr = chn_attr;

    if (DSP2_INPUT_DVP == DSP2_INPUT_MODE) {
        DSP2_MSIC_Dtsrc_Set_Mode(DVP_TSRC_SRC_DVP);
        bl_vin_enable_dvp_input(g_vin_cfg.pix_clk, g_vin_cfg.dsp2_clk);
    }
    // mipi
    else {
        DSP2_MSIC_Dtsrc_Set_Mode(DVP_TSRC_SRC_MIPI_CSI);
        bl_vin_enable_mipi_input(g_vin_cfg.pix_clk, g_vin_cfg.dsp2_clk, DSP2_INPUT_MODE);
    }
    sensor_enable();

    return 0;
}

int MM_Virsensor_Init(uint8_t *buf, uint8_t is_fakedata)
{
    uint32_t dsp2_clk;
    uint32_t buf_size;
    uint8_t* buf_addr;

    bl_dsp2_disable_dump_chann(0);
    bl_dsp2_disable_dump_chann(1);

    DSP2_DVP_TSrc_Disable(DVP_TSRC_DSP2);
    CLKRST_ResetDSP2TSrc();  /* TODO: workaround HW bug, DDR input leads to corrupted image */

    build_vin_from_virt_sensor(&g_vin_cfg, &virt_sns_info);
    if (imgproc_bind_sensor_model(g_vin_cfg.sensor_name) < 0) {
        BL_LOGE("cannot match any IQ param to sensor model %s\r\n", g_vin_cfg.sensor_name);
        return -1;
    }
    ///* config DSP2 clock */
    dsp2_clk = calc_dsp2_clk(g_vin_cfg.pix_clk);
    DSP2_Clk_Sel(DSP2_CLK_160MHz, ENABLE, 1);

    bl_dsp2_sys_init(&g_vin_cfg);      /* assume sensor input */

    bl_dsp2_misc_init();

    buf_addr = buf;
    buf_size = (g_vin_cfg.act_win.width * g_vin_cfg.act_win.height << 1);   /* bayer raw image size */

    if (is_fakedata) {
        bl_vin_enable_fakedata_input(&g_vin_cfg);
    }
    else {
        bl_vin_enable_raw_file_input(buf_addr, buf_size);
    }

    return 0;
}

int MM_YUVSensor_Init(void)
{
    return yuvsensor_init();
}

int MM_Sensor_SetChnAttr(int snsChn, const MMSensorAttr *snsAttr)
{
    if (snsChn < 0 || snsChn >= MAX_NUM_SENSOR) {
        BL_LOGE("MM_Sensor_SetChnAttr: invalid snsChn %d\r\n", snsChn);
        return -1;
    }

    sensor_chn[snsChn].snsAttr = *snsAttr;

    return 0;
}

int MM_Sensor_GetChnAttr(int snsChn, MMSensorAttr *snsAttr)
{
    if (snsChn < 0 || snsChn >= MAX_NUM_SENSOR) {
        BL_LOGE("MM_Sensor_GetChnAttr: invalid snsChn %d\r\n", snsChn);
        return -1;
    }

    *snsAttr = sensor_chn[snsChn].snsAttr;

    return 0;
}

int MM_Sensor_GetPixClk(uint32_t *pix_clk)
{
    *pix_clk = g_vin_cfg.pix_clk;

    return 0;
}

int MM_Sensor_SetPixClk(uint32_t pix_clk)
{
    g_vin_cfg.pix_clk = pix_clk;
    cal_dsp2_clk(pix_clk, &g_vin_cfg.dsp2_clk);

    return 0;
}

int MM_Sensor_GetSensorReg(uint16_t addr,uint8_t *data)
{
    if (sensor_get_sensor_reg(addr, data) < 0) return -1;
    return 0;
}

int MM_Sensor_SetSensorReg(uint16_t addr,uint8_t data)
{
    if (sensor_set_sensor_reg(addr, data) < 0) return -1;
    return 0;
}

int MM_DSP2_CreateFrameSrcChn(int frmSrcChn, MMDSP2FrmSrcAttr *frmSrcAttr)
{
    framesource_chn[frmSrcChn].frmSrcAttr = *frmSrcAttr;
    framesource_chn[frmSrcChn].refCnt = 0;

    return 0;
}

int MM_DSP2_SetFrameSrcChnAttr_crop(int frmSrcChn, MMDSP2FrmSrcCrop *frmSrcCropRoi)
{
    int ret = 0;
    bl_dsp2_crop_roi_t roi = {0};
    BL_Img_Size_T win;

    if (frmSrcChn < 0 || frmSrcChn >= MAX_NUM_FRAMESOURCE) {
        BL_LOGE("MM_DSP2_SetFrameSrcChnAttr_crop: invalid frmSrcChn %d\r\n", frmSrcChn);
        return -1;
    }

    roi.start_x = frmSrcCropRoi->left;
    roi.end_x = frmSrcCropRoi->left + frmSrcCropRoi->width;
    roi.start_y = frmSrcCropRoi->top;
    roi.end_y = frmSrcCropRoi->top + frmSrcCropRoi->height;
    ret = bl_dsp2_set_crop_roi(frmSrcChn, &roi);
    if (ret == -1) return -1;
        
    /* Update scaler settings because that the input window changed by crop settings */
    win.width  = framesource_chn[frmSrcChn].frmSrcAttr.picWidth;
    win.height = framesource_chn[frmSrcChn].frmSrcAttr.picHeight;
    ret = bl_dsp2_set_scaler_resolution(frmSrcChn, &win);
    if (ret == -1) return -1;

    return 0;
}

int MM_DSP2_SetFrameSrcChnAttr(int frmSrcChn, const MMDSP2FrmSrcAttr *frmSrcAttr)
{
    BL_Img_Size_T win;

    if (frmSrcChn < 0 || frmSrcChn >= MAX_NUM_FRAMESOURCE) {
        BL_LOGE("MM_DSP2_GetFrameSrcChnAttr: invalid frmSrcChn %d\r\n", frmSrcChn);
        return -1;
    }

    // if (frmSrcAttr->dsp2Position == DSP2_POSITION_SCALER_A || frmSrcAttr->dsp2Position == DSP2_POSITION_SCALER_B) {
        win.width  = frmSrcAttr->picWidth;
        win.height = frmSrcAttr->picHeight;
        bl_dsp2_set_scaler_resolution(frmSrcChn, &win);
        bl_dsp2_set_yuv_adj_state(frmSrcChn, !frmSrcAttr->isFullRange);
    // } else {
        /* check if frame sournce resolution match up with DSP2 resolution */
//       bl_dsp2_get_input_resolution(&win);
//        if (frmSrcAttr->picWidth != win.width || frmSrcAttr->picHeight != win.height) {
//            BL_LOGE("MM_DSP2_SetFrameSrcChnAttr: invalid frame source resolution!\r\n");
//            return -1;
//        }
    // }

    do_set_framesrc_out_frame_rate(frmSrcChn, frmSrcAttr->outFrmRateNum, frmSrcAttr->outFrmRateDen);

    framesource_chn[frmSrcChn].frmSrcAttr = *frmSrcAttr;

    return 0;
}

int MM_DSP2_GetFrameSrcChnAttr(int frmSrcChn, MMDSP2FrmSrcAttr *frmSrcAttr)
{
    if (frmSrcChn < 0 || frmSrcChn >= MAX_NUM_FRAMESOURCE) {
        BL_LOGE("MM_DSP2_GetFrameSrcChnAttr: invalid frmSrcChn %d\r\n", frmSrcChn);
        return -1;
    }

    *frmSrcAttr = framesource_chn[frmSrcChn].frmSrcAttr;

    return 0;
}

int MM_DSP2_SetFrameSrcChnFPS(int frmSrcChn, const MMDSP2FrmRate *fpsCfg)
{
    if (frmSrcChn < 0 || frmSrcChn >= MAX_NUM_FRAMESOURCE) {
        BL_LOGE("MM_DSP2_GetFrameSrcChnAttr: invalid frmSrcChn %d\r\n", frmSrcChn);
        return -1;
    }

    do_set_framesrc_out_frame_rate(frmSrcChn, fpsCfg->frmRateNum, fpsCfg->frmRateDen);

    framesource_chn[frmSrcChn].frmSrcAttr.outFrmRateNum = fpsCfg->frmRateNum;
    framesource_chn[frmSrcChn].frmSrcAttr.outFrmRateDen = fpsCfg->frmRateDen;

    return 0;
}

int MM_DSP2_GetFrameSrcChnFPS(int frmSrcChn, MMDSP2FrmRate *fpsCfg)
{
    if (frmSrcChn < 0 || frmSrcChn >= MAX_NUM_FRAMESOURCE) {
        BL_LOGE("MM_DSP2_GetFrameSrcChnAttr: invalid frmSrcChn %d\r\n", frmSrcChn);
        return -1;
    }

    fpsCfg->frmRateNum = framesource_chn[frmSrcChn].frmSrcAttr.outFrmRateNum;
    fpsCfg->frmRateDen = framesource_chn[frmSrcChn].frmSrcAttr.outFrmRateDen;

    return 0;
}

int MM_DSP2_StartRecvPic(int frmSrcChn, MMPixelFormat picFormat)
{
    FrmSrcChann *fs_chann;
    MMDSP2FrmSrcAttr *frmSrcAttr;
    uint32_t buf_size, frm_size;
    BL_DSP2_IMAGE_DUMP_SRC_T img_src;
    bl_dsp2_dump_cfg_t dump_cfg;
    BL_DSP2_IMAGE_PLANE_T image_plane;

    if (frmSrcChn < 0 || frmSrcChn >= MAX_NUM_FRAMESOURCE) {
        BL_LOGE("MM_DSP2_StartRecvPic: invalid frmSrcChn %d\r\n", frmSrcChn);
        return -1;
    }

    fs_chann = &framesource_chn[frmSrcChn];
    frmSrcAttr = &fs_chann->frmSrcAttr;

    img_src = (BL_DSP2_IMAGE_DUMP_SRC_T)frmSrcAttr->dsp2Position;
    if (picFormat == PIX_FMT_GRAY8 || picFormat == PIX_FMT_DATA8) {
        frm_size = (frmSrcAttr->picWidth * frmSrcAttr->picHeight);   /* 8bit frame buffer */
        image_plane = IMAGE_PLANE_8BIT;
    } else if (picFormat == PIX_FMT_RGB0) {
        frm_size = (frmSrcAttr->picWidth * frmSrcAttr->picHeight) << 2;   /* 32bit frame buffer */
        image_plane = IMAGE_PLANE_24_EXP_32BIT;
    } else {
        frm_size = (frmSrcAttr->picWidth * frmSrcAttr->picHeight) << 1;   /* 16bit frame buffer */
        image_plane = IMAGE_PLANE_16BIT;
    }


    BL_LOGI("Alloc Pic buffer ...\r\n");
    buf_size = frm_size * FRAME_FIFO_LEN;
    if (0 == buf_size) {
    	BL_LOGE("buf size is 0 ...\r\n");
    	return -1;
    }
    fs_chann->image_base_addr = BL_MallocDMA(PSRAM_ID_FOR_DSP2_PORT_BUF, buf_size);
    fs_chann->image_dump_enable = true;

    /* Create a queue instance for frame FIFO */
    fs_chann->streamQueue = BL_Queue_Create(FRAME_FIFO_LEN, sizeof(bl_dsp2_frame_desc_t));
    bl_dsp2_frame_ready_config(frmSrcChn, frame_ready_cb, NULL);

    dump_cfg.buf_base_addr = fs_chann->image_base_addr;
    dump_cfg.buf_size      = buf_size;
    dump_cfg.frame_size    = frm_size;
    dump_cfg.win.width     = frmSrcAttr->picWidth;
    dump_cfg.win.height    = frmSrcAttr->picHeight;
    bl_dsp2_enable_dump_chann(frmSrcChn, img_src, image_plane, &dump_cfg);

    return 0;
}

int MM_DSP2_StartDumpPic(int frmSrcChn, MMPixelFormat picFormat, BL_DSP2_IMAGE_DUMP_SRC_T frm_src)
{
    FrmSrcChann *fs_chann;
    MMDSP2FrmSrcAttr *frmSrcAttr;
    uint32_t buf_size, frm_size;
    BL_DSP2_IMAGE_DUMP_SRC_T img_src;
    bl_dsp2_dump_cfg_t dump_cfg;
    BL_DSP2_IMAGE_PLANE_T image_plane;

    if (frmSrcChn < 0 || frmSrcChn >= MAX_NUM_FRAMESOURCE) {
        BL_LOGE("MM_DSP2_StartRecvPic: invalid frmSrcChn %d\r\n", frmSrcChn);
        return -1;
    }

    fs_chann = &framesource_chn[frmSrcChn];
    frmSrcAttr = &fs_chann->frmSrcAttr;

    img_src = frm_src;
    if (picFormat == PIX_FMT_GRAY8 || picFormat == PIX_FMT_DATA8) {
        frm_size = (frmSrcAttr->picWidth * frmSrcAttr->picHeight);   /* 8bit frame buffer */
        image_plane = IMAGE_PLANE_8BIT;
    } else if (picFormat == PIX_FMT_RGB0) {
        frm_size = (frmSrcAttr->picWidth * frmSrcAttr->picHeight) << 2;   /* 32bit frame buffer */
        image_plane = IMAGE_PLANE_24_EXP_32BIT;
    } else {
        frm_size = (frmSrcAttr->picWidth * frmSrcAttr->picHeight) << 1;   /* 16bit frame buffer */
        image_plane = IMAGE_PLANE_16BIT;
    }

    BL_LOGI("Alloc Pic buffer ...\r\n");
    buf_size = frm_size * FRAME_FIFO_LEN;
    if (0 == buf_size) {
    	BL_LOGE("buf size is 0 ...\r\n");
    	return -1;
    }
    fs_chann->image_base_addr = BL_MallocDMA(1, buf_size);
    fs_chann->image_dump_enable = true;

    /* Create a queue instance for frame FIFO */
    fs_chann->streamQueue = BL_Queue_Create(FRAME_FIFO_LEN, sizeof(bl_dsp2_frame_desc_t));
    bl_dsp2_frame_ready_config(frmSrcChn, frame_ready_cb, NULL);

    dump_cfg.buf_base_addr = fs_chann->image_base_addr;
    dump_cfg.buf_size      = buf_size;
    dump_cfg.frame_size    = frm_size;
    dump_cfg.win.width     = frmSrcAttr->picWidth;
    dump_cfg.win.height    = frmSrcAttr->picHeight;
    bl_dsp2_enable_dump_chann(frmSrcChn, img_src, image_plane, &dump_cfg);

    return 0;
}

int MM_DSP2_StopRecvPic(int frmSrcChn)
{
    FrmSrcChann *fs_chann;

    if (frmSrcChn < 0 || frmSrcChn >= MAX_NUM_FRAMESOURCE) {
        BL_LOGE("MM_DSP2_StopRecvPic: invalid frmSrcChn %d\r\n", frmSrcChn);
        return -1;
    }

    fs_chann = &framesource_chn[frmSrcChn];

    bl_dsp2_disable_dump_chann(frmSrcChn);
    bl_dsp2_frame_ready_config(frmSrcChn, NULL, NULL);

    if (fs_chann->image_dump_enable) {
        BL_LOGI("Free YUV buffer ...\r\n");
        if (NULL != fs_chann->image_base_addr) {
            BL_FreeDMA(fs_chann->image_base_addr);
            fs_chann->image_base_addr = NULL;
        }
        fs_chann->image_dump_enable = false;
    }

    BL_Queue_Delete(fs_chann->streamQueue);
    fs_chann->streamQueue = NULL;

    return 0;
}

int MM_DSP2_GetOnePicture(int frmSrcChn, MMDSP2YuvFrame *yuvFrame)
{
    int ret;
    FrmSrcChann *fs_chann;
    bl_dsp2_frame_desc_t yuv_frame;

    if (frmSrcChn < 0 || frmSrcChn >= MAX_NUM_FRAMESOURCE) {
        BL_LOGE("MM_DSP2_StopRecvPic: invalid frmSrcChn %d\r\n", frmSrcChn);
        return -1;
    }

    fs_chann = &framesource_chn[frmSrcChn];

    if (NULL == fs_chann->streamQueue) {
        BL_LOGE("fs streamqueue is NULL!\r\n");
        return -2;
    }

    ret = BL_Queue_Get_Item(fs_chann->streamQueue, &yuv_frame, QUEUE_WAIT_FOREVER);
    if (pdFALSE == ret) {
        BL_LOGE("Get item from queue fail!\r\n");
        return -1;
    }

    yuvFrame->frameStartAddr = yuv_frame.frame_start_addr;
    yuvFrame->frameSize = yuv_frame.frame_size;

    bl_dsp2_dump_next_frame(frmSrcChn);

    return 0;
}

int MM_DSP2_ResumDumpPic(int frmSrcChn)
{
    bl_dsp2_resume_dump_chann(frmSrcChn);
    return 0;
}

int MM_DSP2_PauseDumpPic(int frmSrcChn)
{
    bl_dsp2_disable_dump_chann(frmSrcChn);
    return 0;
}

int MM_DSP2_HDMI_Start(void)
{
    FrmSrcChann *fs_chann;
    BL_Img_Size_T win;
    uint32_t buf_size;

    fs_chann = &framesource_chn[HDMI_FRAMESRC_ID];

    bl_dsp2_get_scaler_resolution(HDMI_FRAMESRC_ID, &win);

    BL_LOGI("Alloc HDMI buffer ...\r\n");
    buf_size = ((win.width * win.height << 1) << 1);    /* double frame buffer shared with HDMI */

    if (NULL != fs_chann->image_base_addr) {
        BL_FreeDMA(fs_chann->image_base_addr);
        fs_chann->image_base_addr = NULL;
    }
    fs_chann->image_base_addr = BL_MallocDMA(PSRAM_ID_FOR_DSP2_PORT_BUF, buf_size);
    fs_chann->image_dump_enable = true;

    bl_dsp2_enable_hdmi_port(HDMI_FRAMESRC_ID, fs_chann->image_base_addr, buf_size);
    bl_vout_enable_hdmi_out(HDMI_FRAMESRC_ID, fs_chann->image_base_addr, buf_size);

    return 0;
}

int MM_DSP2_HDMI_Stop(void)
{
    FrmSrcChann *fs_chann;

    fs_chann = &framesource_chn[HDMI_FRAMESRC_ID];

    bl_vout_disable_hdmi_out();
    bl_dsp2_disable_hdmi_port(HDMI_FRAMESRC_ID);
    CLKRST_ResetHdmiTSrc();

    if (fs_chann->image_dump_enable) {
        BL_LOGI("Free HDMI buffer ...\r\n");
        if (NULL != fs_chann->image_base_addr) {
            BL_FreeDMA(fs_chann->image_base_addr);
            fs_chann->image_base_addr = NULL;
        }
        fs_chann->image_dump_enable = false;
    }

    return 0;
}

int MM_Encoder_GetRegInit(MMEncoderRcAttr *encRcAttr)
{
    encRcAttr->rcMode=  rcAttr_init_reg.rcMode;

    encRcAttr->attrH264Cbr.outBitRate = rcAttr_init_reg.attrH264Cbr.outBitRate;
    encRcAttr->attrH264Cbr.initQp = rcAttr_init_reg.attrH264Cbr.initQp;
    encRcAttr->attrH264Cbr.maxQp = rcAttr_init_reg.attrH264Cbr.maxQp;
    encRcAttr->attrH264Cbr.minQp = rcAttr_init_reg.attrH264Cbr.minQp;
    encRcAttr->attrH264Cbr.iBiasLvl = rcAttr_init_reg.attrH264Cbr.iBiasLvl;

    encRcAttr->attrH264Vbr.targetBitRate = rcAttr_init_reg.attrH264Vbr.targetBitRate;
    encRcAttr->attrH264Vbr.maxBitRate = rcAttr_init_reg.attrH264Vbr.maxBitRate;
    encRcAttr->attrH264Vbr.qualityLvl = rcAttr_init_reg.attrH264Vbr.qualityLvl;
    encRcAttr->attrH264Vbr.maxQp = rcAttr_init_reg.attrH264Vbr.maxQp;
    encRcAttr->attrH264Vbr.minQp = rcAttr_init_reg.attrH264Vbr.minQp;
    encRcAttr->attrH264Vbr.iBiasLvl = rcAttr_init_reg.attrH264Vbr.iBiasLvl;

    return 0;
}

int MM_Encoder_GetScenceCtrlRegInit(int encChn, uint32_t bitrate)
{
    int i, ret = 0;
    MMEncoderScenceCtrlAttr encScenceCtrlAttr;
    uint8_t status = bitrate_ctrl_init_reg.enable;

    ret = MM_Encoder_SetScenceCtrlStatus(encChn, status);
    if (ret < 0) return -1;
    ret = parse_scence_ctrl_reg_from_bitrate(&encScenceCtrlAttr, bitrate);

    for (i = 0; i < ENC_SC_MODE_NUM; i++) {
        MM_Encoder_SetScenceCtrlReg(encChn, i, &encScenceCtrlAttr.scence_attr[i]);
    }

    return ret;
}

int MM_Encoder_SetScenceCtrlStatus(int encChn, uint8_t status)
{
    int i = 0;
    MMEncoderRcAttr init_encRcAttr = {0};
    MMEncoderGOPSizeCfg gopSizeCfg = {0};
    MMSensorAttr snsAttr = {0};

    if (encChn < 0 || encChn >= MAX_NUM_ENCODER) {
        BL_LOGE("MM_Encoder_SetScenceCtrlStatus: invalid encChn %d\r\n", encChn);
        return -1;
    }

    MM_Sensor_GetChnAttr(0, &snsAttr);
    gopSizeCfg.gopSize = snsAttr.fps;

    scence_ctrl_en[encChn]= status;
    if (scence_ctrl_en[encChn] == 0) {
        MM_Encoder_GetRegInit(&init_encRcAttr);
        if (init_encRcAttr.rcMode == ENC_RC_MODE_CBR) {
            MM_Encoder_SetChnMinQP(encChn, init_encRcAttr.attrH264Cbr.minQp);
            MM_Encoder_SetChnMaxQP(encChn, init_encRcAttr.attrH264Cbr.maxQp);
            MM_Encoder_SetChnIpRatio(encChn, init_encRcAttr.attrH264Cbr.iBiasLvl);
            MM_Encoder_SetChnGOPSize(encChn, &gopSizeCfg.gopSize);
        } /*else {
            MM_Encoder_SetChnMinQP(encChn, init_encRcAttr.attrH264Vbr.minQp);
            MM_Encoder_SetChnMaxQP(encChn, init_encRcAttr.attrH264Vbr.maxQp);
            MM_Encoder_SetChnIpRatio(encChn, init_encRcAttr.attrH264Vbr.iBiasLvl);
            MM_Encoder_SetChnGOPSize(encChn, &scence_ctrl.gopSizeCfg);
        }*/
    }
    return 0;
}

int MM_Encoder_GetScenceCtrlStatus(int encChn, uint8_t *status)
{
    if (encChn < 0 || encChn >= MAX_NUM_ENCODER) {
        BL_LOGE("MM_Encoder_GetScenceCtrlStatus: invalid encChn %d\r\n", encChn);
        return -1;
    }

    *status = scence_ctrl_en[encChn];
    return 0;
}

int MM_Encoder_SetScenceCtrlReg(int encChn, const MMEncoderScenceCtrlMode mode, const MMEncoderScenceAttr *attr)
{
    if (encChn < 0 || encChn >= MAX_NUM_ENCODER) {
        BL_LOGE("MM_Encoder_SetScenceCtrlReg: invalid encChn %d\r\n", encChn);
        return -1;
    }

    if (mode < 0 || mode >= ENC_SC_MODE_NUM) {
        BL_LOGE("MM_Encoder_SetScenceCtrlReg: Invalid mode %d\r\n", mode);
        return -1;
    }

    scence_ctrl_reg[encChn].scence_attr[mode].scence_thr = attr->scence_thr;
    scence_ctrl_reg[encChn].scence_attr[mode].gop_size = attr->gop_size;
    scence_ctrl_reg[encChn].scence_attr[mode].ip_ratio = attr->ip_ratio;
    scence_ctrl_reg[encChn].scence_attr[mode].min_qp = attr->min_qp;
    scence_ctrl_reg[encChn].scence_attr[mode].max_qp = attr->max_qp;

    return 0;
}

int MM_Encoder_GetScenceCtrlReg(int encChn, const MMEncoderScenceCtrlMode mode, MMEncoderScenceAttr *attr)
{
    if (encChn < 0 || encChn >= MAX_NUM_ENCODER) {
        BL_LOGE("MM_Encoder_GetScenceCtrlReg: invalid encChn %d\r\n", encChn);
        return -1;
    }

    if (mode < 0 || mode >= ENC_SC_MODE_NUM) {
        BL_LOGE("MM_Encoder_GetScenceCtrlReg: Invalid mode %d\r\n", mode);
        return -1;
    }

    attr->scence_thr = scence_ctrl_reg[encChn].scence_attr[mode].scence_thr;
    attr->gop_size = scence_ctrl_reg[encChn].scence_attr[mode].gop_size;
    attr->ip_ratio = scence_ctrl_reg[encChn].scence_attr[mode].ip_ratio;
    attr->min_qp = scence_ctrl_reg[encChn].scence_attr[mode].min_qp;
    attr->max_qp = scence_ctrl_reg[encChn].scence_attr[mode].max_qp;

    return 0;
}

int MM_Encoder_CreateChn(int encChn)
{
    EncoderChann *enc_chann;

    if (encChn < 0 || encChn >= MAX_NUM_ENCODER) {
        BL_LOGE("MM_Encoder_CreateChn: Invalid encChn %d\r\n", encChn);
        return -1;
    }

    enc_chann = &encoder_chn[encChn];

    enc_chann->mutex = xSemaphoreCreateMutex();

    return 0;
}

int MM_Encoder_SetChnAttr(int encChn, const MMEncoderAttr *encAttr)
{
    if (encChn < 0 || encChn >= MAX_NUM_ENCODER) {
        BL_LOGE("MM_Encoder_SetChnAttr: invalid encChn %d\r\n", encChn);
        return -1;
    }

    encoder_chn[encChn].encAttr = *encAttr;

    do_set_encoder_resolution(encChn, encAttr->picWidth, encAttr->picHeight);
    do_set_encoder_frame_rate(encChn, encAttr->frmRateNum, encAttr->frmRateDen);

    if (ENC_TYPE_H264 == encAttr->encType) {
        do_set_encoder_gop_size(encChn, encAttr->attrH264.gopSize);
        do_set_encoder_profile(encChn, encAttr->attrH264.profile);
        do_set_low_power_mode(encChn, encAttr->attrH264.lowPwrMode);
    } else if (ENC_TYPE_JPEG == encAttr->encType) {
        do_set_encoder_jpeg_quality(encChn, encAttr->attrJpeg.quality);
    }

    return 0;
}

int MM_Encoder_GetChnAttr(int encChn, MMEncoderAttr *encAttr)
{
    if (encChn < 0 || encChn >= MAX_NUM_ENCODER) {
        BL_LOGE("MM_Encoder_GetChnAttr: invalid encChn %d\r\n", encChn);
        return -1;
    }

    *encAttr = encoder_chn[encChn].encAttr;

    return 0;
}

int MM_Encoder_SetChnRcAttr(int encChn, const MMEncoderRcAttr *encRcAttr)
{
    if (encChn < 0 || encChn >= MAX_NUM_H264_ENCODER) {
        BL_LOGE("MM_Encoder_SetChnRcAttr: invalid encChn %d\r\n", encChn);
        return -1;
    }

    do_set_encoder_rc_mode(encChn, encRcAttr->rcMode);
    do_set_encoder_quality_lvl(encChn, encRcAttr->attrH264Vbr.qualityLvl);
    if (encRcAttr->rcMode == ENC_RC_MODE_CBR) {
        do_set_i_bias_level(encChn, encRcAttr->attrH264Cbr.iBiasLvl);
        do_set_encoder_init_qp(encChn, encRcAttr->attrH264Cbr.initQp);
        do_set_encoder_min_qp(encChn, encRcAttr->attrH264Cbr.minQp);
        do_set_encoder_max_qp(encChn, encRcAttr->attrH264Cbr.maxQp);
        do_set_encoder_bitrate(encChn, encRcAttr->attrH264Cbr.outBitRate);
    } else {
        do_set_i_bias_level(encChn, encRcAttr->attrH264Vbr.iBiasLvl);
        do_set_encoder_init_qp(encChn, encRcAttr->attrH264Vbr.qualityLvl);
        do_set_encoder_min_qp(encChn, encRcAttr->attrH264Vbr.minQp);
        do_set_encoder_max_qp(encChn, encRcAttr->attrH264Vbr.maxQp);
        do_set_encoder_bitrate(encChn, encRcAttr->attrH264Vbr.targetBitRate);
    }
    encoder_rc[encChn] = *encRcAttr;

    return 0;
}

int MM_Encoder_GetChnRcAttr(int encChn, MMEncoderRcAttr *encRcAttr)
{
    if (encChn < 0 || encChn >= MAX_NUM_H264_ENCODER) {
        BL_LOGE("MM_Encoder_GetChnRcAttr: invalid encChn %d\r\n", encChn);
        return -1;
    }

    *encRcAttr = encoder_rc[encChn];

    return 0;
}

int MM_Encoder_SetChnFrmRate(int encChn, const MMEncoderFrmRate *fpsCfg)
{
    if (encChn < 0 || encChn >= MAX_NUM_ENCODER) {
        BL_LOGE("MM_Encoder_SetChnFrmRate: Invalid encChn %d\r\n", encChn);
        return -1;
    }

    do_set_encoder_frame_rate(encChn, fpsCfg->frmRateNum, fpsCfg->frmRateDen);

    encoder_chn[encChn].encAttr.frmRateNum = fpsCfg->frmRateNum;
    encoder_chn[encChn].encAttr.frmRateDen = fpsCfg->frmRateDen;

    return 0;
}

int MM_Encoder_GetChnFrmRate(int encChn, MMEncoderFrmRate *fpsCfg)
{
    if (encChn < 0 || encChn >= MAX_NUM_ENCODER) {
        BL_LOGE("MM_Encoder_GetChnFrmRate: Invalid encChn %d\r\n", encChn);
        return -1;
    }

    fpsCfg->frmRateNum = encoder_chn[encChn].encAttr.frmRateNum;
    fpsCfg->frmRateDen = encoder_chn[encChn].encAttr.frmRateDen;

    return 0;
}

int MM_Encoder_SetChnGOPSize(int encChn, const MMEncoderGOPSizeCfg *gopSizeCfg)
{
    if (encChn < 0 || encChn >= MAX_NUM_ENCODER) {
        BL_LOGE("MM_Encoder_SetChnGOPSize: Invalid encChn %d\r\n", encChn);
        return -1;
    }
    if (gopSizeCfg->gopSize == 1) {
       // all I frame need to close H264_PREFETCH_MODE
       BL_LOGI("Please check #define H264_PREFETCH_MODE is 0\r\n");
    }

    do_set_encoder_gop_size(encChn, gopSizeCfg->gopSize);

    encoder_chn[encChn].encAttr.attrH264.gopSize = gopSizeCfg->gopSize;

    return 0;
}

int MM_Encoder_GetChnGOPSize(int encChn, MMEncoderGOPSizeCfg *gopSizeCfg)
{
    if (encChn < 0 || encChn >= MAX_NUM_ENCODER) {
        BL_LOGE("MM_Encoder_GetChnGOPSize: Invalid encChn %d\r\n", encChn);
        return -1;
    }

    gopSizeCfg->gopSize = encoder_chn[encChn].encAttr.attrH264.gopSize;

    return 0;
}

int MM_Encoder_SetChnBitRate(int encChn, const MMEncoderBitRateCfg *bitRateCfg)
{
    int i = 0;
    uint8_t status;
    MMEncoderRcAttr *rcAttr;
    MMEncoderScenceCtrlAttr encScenceCtrlAttr;

    if (encChn < 0 || encChn >= MAX_NUM_ENCODER) {
        BL_LOGE("MM_Encoder_SetChnBitRate: Invalid encChn %d\r\n", encChn);
        return -1;
    }

    rcAttr = &encoder_rc[encChn];

    do_set_encoder_bitrate(encChn, bitRateCfg->bitRate);
    rcAttr->attrH264Cbr.outBitRate = bitRateCfg->bitRate;
    rcAttr->attrH264Vbr.targetBitRate = bitRateCfg->bitRate;

    MM_Encoder_GetScenceCtrlStatus(encChn, &status);
    if ((status == 1) && (rate_ctrl_lvl[encChn].rateCtrlLevel == 0)) {
        parse_scence_ctrl_reg_from_bitrate(&encScenceCtrlAttr, bitRateCfg->bitRate);
        for (i = 0; i < ENC_SC_MODE_NUM; i++) {
            MM_Encoder_SetScenceCtrlReg(encChn, i, &encScenceCtrlAttr.scence_attr[i]);
        }
    }


#if MMENCODER_VBR_ADAPTIVE_QP
    // restart bitrate control params
    MM_Encoder_InitVbrDynamicQP(encChn);
#endif
    return 0;
}

int MM_Encoder_GetChnBitRate(int encChn, MMEncoderBitRateCfg *bitRateCfg)
{
    MMEncoderRcAttr *rcAttr;
    if (encChn < 0 || encChn >= MAX_NUM_ENCODER) {
        BL_LOGE("MM_Encoder_GetChnBitRate: Invalid encChn %d\r\n", encChn);
        return -1;
    }

    rcAttr = &encoder_rc[encChn];

    if (rcAttr->rcMode == ENC_RC_MODE_CBR)
        bitRateCfg->bitRate = rcAttr->attrH264Cbr.outBitRate;
    else
        bitRateCfg->bitRate = rcAttr->attrH264Vbr.targetBitRate;
    return 0;
}

int MM_Encoder_SetChnMaxBitRate(int encChn, const MMEncoderBitRateCfg *bitRateCfg)
{
    MMEncoderRcAttr *rcAttr;
    if (encChn < 0 || encChn >= MAX_NUM_ENCODER) {
        BL_LOGE("MM_Encoder_SetChnMaxBitRate: Invalid encChn %d\r\n", encChn);
        return -1;
    }

    rcAttr = &encoder_rc[encChn];
    rcAttr->attrH264Vbr.maxBitRate = bitRateCfg->bitRate;

    return 0;
}

int MM_Encoder_GetChnMaxBitRate(int encChn, MMEncoderBitRateCfg *bitRateCfg)
{
    MMEncoderRcAttr *rcAttr;
    if (encChn < 0 || encChn >= MAX_NUM_ENCODER) {
        BL_LOGE("MM_Encoder_GetChnMaxBitRate: Invalid encChn %d\r\n", encChn);
        return -1;
    }

    rcAttr = &encoder_rc[encChn];
    bitRateCfg->bitRate = rcAttr->attrH264Vbr.maxBitRate;
    return 0;
}

int MM_Encoder_SetChnIpRatio(int encChn, const uint32_t ip_ratio)
{
    // updste ip ratio need re-calculate imb, pmb
    MMEncoderRcAttr *rcAttr;
    if (encChn < 0 || encChn >= MAX_NUM_ENCODER) {
        BL_LOGE("MM_Encoder_SetChnIpRatio: Invalid encChn %d\r\n", encChn);
        return -1;
    }

    rcAttr = &encoder_rc[encChn];
    if (rcAttr->rcMode == ENC_RC_MODE_CBR) {
        rcAttr->attrH264Cbr.iBiasLvl = ip_ratio;
    } else if (rcAttr->rcMode == ENC_RC_MODE_VBR) {
        rcAttr->attrH264Vbr.iBiasLvl = ip_ratio;
    }
    MM_Encoder_SetChnRcAttr(encChn, rcAttr);

    return 0;
}

int MM_Encoder_GetChnIpRatio(int encChn, uint32_t *ip_ratio)
{
    MMEncoderRcAttr *rcAttr;
    if (encChn < 0 || encChn >= MAX_NUM_ENCODER) {
        BL_LOGE("MM_Encoder_GetChnIpRatio: Invalid encChn %d\r\n", encChn);
        return -1;
    }

    rcAttr = &encoder_rc[encChn];
    if (rcAttr->rcMode == ENC_RC_MODE_CBR) {
        *ip_ratio = rcAttr->attrH264Cbr.iBiasLvl;
    } else if (rcAttr->rcMode == ENC_RC_MODE_VBR) {
        *ip_ratio = rcAttr->attrH264Vbr.iBiasLvl;
    }
    return 0;
}


int MM_Encoder_SetChnMaxQP(int encChn, const uint32_t qp)
{
    MMEncoderRcAttr *rcAttr;
    if (encChn < 0 || encChn >= MAX_NUM_ENCODER) {
        BL_LOGE("MM_Encoder_SetChnMaxQP: Invalid encChn %d\r\n", encChn);
        return -1;
    }

    if (qp > MMENCODER_IFRAME_MAX_QP) {
        BL_LOGE("MM_Encoder_SetChnMaxQP: Invalid max qp %d, limited max qp %d\r\n", qp, MMENCODER_IFRAME_MAX_QP);
        return -1;
    }

    rcAttr = &encoder_rc[encChn];
    if (rcAttr->rcMode == ENC_RC_MODE_CBR) {
        if (qp <= rcAttr->attrH264Cbr.minQp) {
            BL_LOGE("MM_Encoder_SetChnMaxQP: Invalid max qp %d, smaller then min qp %d\r\n", qp, rcAttr->attrH264Cbr.minQp);
            return -1;
        }
        rcAttr->attrH264Cbr.maxQp = qp;
    } else if (rcAttr->rcMode == ENC_RC_MODE_VBR) {
        if (qp <= rcAttr->attrH264Vbr.minQp) {
            BL_LOGE("MM_Encoder_SetChnMaxQP: Invalid max qp %d, smaller then min qp %d\r\n", qp, rcAttr->attrH264Vbr.minQp);
            return -1;
        }
        rcAttr->attrH264Vbr.maxQp = qp;
    }
    do_set_encoder_max_qp(encChn, qp);
    return 0;
}

int MM_Encoder_GetChnMaxQP(int encChn, uint32_t *qp)
{
    MMEncoderRcAttr *rcAttr;
    if (encChn < 0 || encChn >= MAX_NUM_ENCODER) {
        BL_LOGE("MM_Encoder_GetChnMaxQP: Invalid encChn %d\r\n", encChn);
        return -1;
    }

    rcAttr = &encoder_rc[encChn];
    if (rcAttr->rcMode == ENC_RC_MODE_CBR) {
        *qp = rcAttr->attrH264Cbr.maxQp;
    } else if (rcAttr->rcMode == ENC_RC_MODE_VBR) {
        *qp = rcAttr->attrH264Vbr.maxQp;
    }

    return 0;
}

int MM_Encoder_SetChnMinQP(int encChn, const uint32_t qp)
{
    MMEncoderRcAttr *rcAttr;
    if (encChn < 0 || encChn >= MAX_NUM_ENCODER) {
        BL_LOGE("MM_Encoder_SetChnMinQP: Invalid encChn %d\r\n", encChn);
        return -1;
    }

    rcAttr = &encoder_rc[encChn];
    if (rcAttr->rcMode == ENC_RC_MODE_CBR) {
        if (qp >= rcAttr->attrH264Cbr.maxQp) {
            BL_LOGE("MM_Encoder_SetChnMinQP: Invalid min qp %d, bigger then max qp %d\r\n", qp, rcAttr->attrH264Cbr.maxQp);
            return -1;
        }
        rcAttr->attrH264Cbr.minQp = qp;
    } else if (rcAttr->rcMode == ENC_RC_MODE_VBR) {
        if (qp >= rcAttr->attrH264Vbr.maxQp) {
            BL_LOGE("MM_Encoder_SetChnMinQP: Invalid min qp %d, bigger then max qp %d\r\n", qp, rcAttr->attrH264Vbr.maxQp);
            return -1;
        }
        rcAttr->attrH264Vbr.minQp = qp;
    }
    do_set_encoder_min_qp(encChn, qp);

    return 0;
}

int MM_Encoder_GetChnMinQP(int encChn, uint32_t *qp)
{
    MMEncoderRcAttr *rcAttr;
    if (encChn < 0 || encChn >= MAX_NUM_ENCODER) {
        BL_LOGE("MM_Encoder_GetChnMinQP: Invalid encChn %d\r\n", encChn);
        return -1;
    }

    rcAttr = &encoder_rc[encChn];
    if (rcAttr->rcMode == ENC_RC_MODE_CBR) {
        *qp = rcAttr->attrH264Cbr.minQp;
    } else if (rcAttr->rcMode == ENC_RC_MODE_VBR) {
        *qp = rcAttr->attrH264Vbr.minQp;
    }

    return 0;
}

int MM_Encoder_SetChnQualityLvl(int encChn, const MMEncoderQualityLvlCfg *qualityLvlCfg)
{
    MMEncoderRcAttr *rcAttr;
    if (encChn < 0 || encChn >= MAX_NUM_ENCODER) {
        BL_LOGE("MM_Encoder_SetChnQualityLvl: Invalid encChn %d\r\n", encChn);
        return -1;
    }

    rcAttr = &encoder_rc[encChn];

    do_set_encoder_quality_lvl(encChn, qualityLvlCfg->qualityLvl);
    rcAttr->attrH264Vbr.qualityLvl = qualityLvlCfg->qualityLvl;

    return 0;
}

int MM_Encoder_GetChnQualityLvl(int encChn, MMEncoderQualityLvlCfg *qualityLvlCfg)
{
    MMEncoderRcAttr *rcAttr;
    if (encChn < 0 || encChn >= MAX_NUM_ENCODER) {
        BL_LOGE("MM_Encoder_GetChnQualityLvl: Invalid encChn %d\r\n", encChn);
        return -1;
    }

    rcAttr = &encoder_rc[encChn];

    qualityLvlCfg->qualityLvl = rcAttr->attrH264Vbr.qualityLvl;
    return 0;
}

int MM_Encoder_SetChnJpegQuality(int encChn, const MMEncoderJpegQualityCfg *qualityCfg)
{
    MMEncoderRcAttr *rcAttr;
    if (encChn < 0 || encChn >= MAX_NUM_ENCODER) {
        BL_LOGE("MM_Encoder_SetChnJpegQuality: Invalid encChn %d\r\n", encChn);
        return -1;
    }

    encoder_chn[encChn].encAttr.attrJpeg.quality = qualityCfg->quality;
    do_set_encoder_jpeg_quality(encChn, qualityCfg->quality);
    return 0;
}

int MM_Encoder_GetChnJpegQuality(int encChn, MMEncoderJpegQualityCfg *qualityCfg)
{

    if (encChn < 0 || encChn >= MAX_NUM_ENCODER) {
        BL_LOGE("MM_Encoder_GetChnJpegQuality: Invalid encChn %d\r\n", encChn);
        return -1;
    }

    qualityCfg->quality = encoder_chn[encChn].encAttr.attrJpeg.quality;
    return 0;
}

int MM_Encoder_SetRcLevel(int encChn, const uint8_t level)
{
    MMEncoderRcAttr *rcAttr ;

    if (encChn < 0 || encChn >= MAX_NUM_ENCODER) {
        BL_LOGE("MM_Encoder_SetRateCtrlLevel: Invalid encChn %d\r\n", encChn);
        return -1;
    }
    if (level < 0 || level >= MAX_NUM_RATECTRLLVL) {
        BL_LOGE("MM_Encoder_SetRateCtrlLevel: Invalid level %d\r\n", level);
        return -1;
    }

    rcAttr = &encoder_rc[encChn];
    rate_ctrl_lvl[encChn].rateCtrlLevel = level;

    return 0;
}

int MM_Encoder_GetRcLevel(int encChn, uint8_t *level)
{

    if (encChn < 0 || encChn >= MAX_NUM_ENCODER) {
        BL_LOGE("MM_Encoder_GetRateCtrlLevel: Invalid encChn %d\r\n", encChn);
        return -1;
    }

    *level = rate_ctrl_lvl[encChn].rateCtrlLevel;
    return 0;
}

int MM_Encoder_SetDirectLinkMode(bool enable)
{
    direct_link_mode = enable;

    return 0;
}

static void MM_Encoder_StreamStats(mmenc_stream_stats_t *stream_stat, MMEncoderStream *stream)
{
    TickType_t elapse_time_ms;
    TickType_t curr_time_ms = xTaskGetTickCount();

    stream_stat->stat_byte_cnt += (stream->frame_size + stream->frame_sec_size);
    stream_stat->curr_frm_cnt++;

    elapse_time_ms = curr_time_ms - stream_stat->start_time;
    if (elapse_time_ms >= MMENCODER_STREAM_STATS_DUR) {

        /* calculate bitrate */
        stream_stat->br_mbps = (float)(stream_stat->stat_byte_cnt << 3) / elapse_time_ms / 1000;
        /* calculate fps */
        stream_stat->fps = (float)(stream_stat->curr_frm_cnt) * 1000 / elapse_time_ms;
        /* housekeeping for next round of stats */
        stream_stat->stat_byte_cnt = 0;
        stream_stat->start_time = curr_time_ms;
        stream_stat->curr_frm_cnt = 0;
    }
}

#if MMENCODER_VBR_ADAPTIVE_QP
static void MM_Encoder_InitVbrDynamicQP(int encChan)
{
    MMEncoderAttr *attr = &encoder_chn[encChan].encAttr;
    struct mmenc_vbrDynQP_t *qpinfo = &encoder_rc[encChan].attrH264Vbr.qpInfo;

    memset(qpinfo, 0, sizeof(struct mmenc_vbrDynQP_t));
    //Algo. parameters of short-term tuning
    qpinfo->inc_ratio = 1.05;       //bit-rate trend sesitiviey, recommend 1.05~1.20
    qpinfo->dec_ratio = 0.95;       //bit-rate trend sesitiviey, recommend 0.95~0.90
    qpinfo->intra_pasu = 0.7;       //large motion/scence change, recommend 0.6~0.75
    qpinfo->upWL = 5;         //up     trend monitor window length, recommend >=3 (unit : frame)
    qpinfo->dnWL =10;         //down   trend monitor window length, recommend >=10(unit : frame)
    qpinfo->sbWL = 5;         //stable trend monitor window length, recommend >=5 (unit : frame)
    qpinfo->gop_prelen = 1;

    //Algo. parameters of Global tuning
    qpinfo->sta_WL = 100;     //frame bycnt log buffer,            recommend : 100(unit : frame)
    qpinfo->prate_WL = 5;     //peak rate qp tunning smooth size,  recommend : 5  (unit : frame)
    qpinfo->prate_count = 5;
    qpinfo->gp_WL = 60;       //group qp smooth size,              recommend : 60  (unit: frame)
    qpinfo->gp_prelen = 1;

    qpinfo->tot_mbcnt = attr->picWidth * attr->picHeight / 256; //frame_width/height is 16x aligned;
    bl_venc_get_h264_rc_param(encChan, &qpinfo->target_i_qp, &qpinfo->target_p_qp, &qpinfo->iframe_min_qp, &qpinfo->ipratio, &qpinfo->iqp_ofst);
}

static void MM_Encoder_GetVbrDynamicQP(MMEncoderStream *stream)
{
    MMEncoderAttr *attr = &encoder_chn[stream->stream_id].encAttr;
    MMEncoderRcAttr *rc_attr = &encoder_rc[stream->stream_id];
    struct mmenc_vbrDynQP_t *qpinfo = &rc_attr->attrH264Vbr.qpInfo;

    unsigned int vbr_max_rate = 2 * rc_attr->attrH264Vbr.targetBitRate; //VBR max bitrate
    uint8_t fps = attr->frmRateNum/attr->frmRateDen;  //frame rate

    uint8_t target_i_qp = qpinfo->target_i_qp;      //TARGET_I_QP (0x30)
    uint8_t target_p_qp = qpinfo->target_p_qp;      //TARGET_P_QP (0x38)

    unsigned int hw_frm_bitcnt = (stream->frame_size + stream->frame_sec_size) << 3;

    //short-term
    unsigned int intra_mbcnt = 0;
    unsigned int win_size = 0;
    unsigned int widx = 0;
    //Global
    unsigned int frm_idel_avg = 0;
    unsigned int temp_gprate = 0;
    double rate2 = 0;

    if (rc_attr->rcMode != ENC_RC_MODE_VBR)
        return;

    if (rc_attr->attrH264Vbr.maxBitRate > rc_attr->attrH264Vbr.targetBitRate)
        vbr_max_rate = rc_attr->attrH264Vbr.maxBitRate;

    intra_mbcnt = bl_venc_get_h264_intra_mbcnt(stream->stream_id);
    //----------------------
    //HW Encoding Processes
    //----------------------
    frm_idel_avg = rc_attr->attrH264Vbr.targetBitRate/ (double)(fps); //target bit/frame
    qpinfo->frm_size_hist[qpinfo->frm_size_idx_cur] = hw_frm_bitcnt;
    qpinfo->frm_size_idx_cur = (qpinfo->frm_size_idx_cur + 1) % MMENCODER_VBR_QP_FRAME_BCNT_HIST_NUM;

    qpinfo->vbr_budget += (frm_idel_avg - hw_frm_bitcnt);
    //short-term tuning---------
    if (((double)hw_frm_bitcnt >= (qpinfo->inc_ratio*(double)qpinfo->prev_bit_count)))
        qpinfo->inc_count++;
    else
        qpinfo->inc_count = 0;

    if (((double)hw_frm_bitcnt <  (qpinfo->dec_ratio*(double)qpinfo->prev_bit_count)))
        qpinfo->dec_count++;
    else
        qpinfo->dec_count = 0;

    if(((double)hw_frm_bitcnt >= qpinfo->dec_ratio *(double)qpinfo->prev_bit_count ) &&
      ((double)hw_frm_bitcnt <  qpinfo->inc_ratio *(double)qpinfo->prev_bit_count))
        qpinfo->stb_count++;
    else
        qpinfo->stb_count=0;

    //BL_LOGI("[QP] ideal: %d, cur: %d, prev_bit_count = %d, vbr_budget = %d, qpinfo->target_p_qp = %d, target_p_qp = %d\r\n",frm_idel_avg, hw_frm_bitcnt, qpinfo->prev_bit_count, qpinfo->vbr_budget, qpinfo->target_p_qp, target_p_qp);

    if( qpinfo->inc_count >= qpinfo->upWL ) { //new vbr_pqp hold 3 frames at least, pay more bits for hard-compress content
        qpinfo->target_p_qp -= (qpinfo->target_p_qp > 35) ? 1 : 2;
        qpinfo->inc_count = 0;
        if (stream->frame_type == ENC_H264_P_FRAME && qpinfo->target_p_qp < target_i_qp && ((float)intra_mbcnt > (float)qpinfo->tot_mbcnt*qpinfo->intra_pasu))
            qpinfo->target_p_qp += 1; //to prevent P_SLICE has QP lower than I_SLICE as intra dominates in P-frame
    }
    if (qpinfo->dec_count >= qpinfo->dnWL )  { //new vbr_pqp hold 5 frames at least
        qpinfo->target_p_qp += (qpinfo->target_p_qp > 35) ? 1 : 2;
        qpinfo->dec_count = 0;
    }
    if (qpinfo->stb_count >= qpinfo->sbWL) { //new vbr_pqp hold 5 frames at least
        if (qpinfo->vbr_budget <0  && ((qpinfo->target_p_qp+1) <= target_p_qp))
          qpinfo->target_p_qp += 1; //increase QP to save bits
        qpinfo->stb_count =0;
    }
    //--------------------------
    //Global tuning-------------
    //1. most recent 1 rate >= 80% of max rate, increase QP to reduce bits
    double cw = (double)fps*0.7;
    int pqp_mod_peak =0;
    if (qpinfo->frm_cnt > cw) {
        win_size = 0;
        for (widx = 0; widx <(int)cw; widx++) // only use most recent cw frames
          win_size += qpinfo->frm_size_hist[(qpinfo->frm_size_idx_cur - 1 - widx + MMENCODER_VBR_QP_FRAME_BCNT_HIST_NUM)%MMENCODER_VBR_QP_FRAME_BCNT_HIST_NUM];

        rate2 = (double)win_size / ((double)cw/ (double)fps);
        if(rate2 >= 0.90*(double)vbr_max_rate) {
          BL_LOGI("bitrate = %.2f%% of vbr_max_rate\n", 100.0*rate2 / vbr_max_rate);
          if(qpinfo->prate_count == qpinfo->prate_WL) {
            pqp_mod_peak = 1;
            qpinfo->target_p_qp += pqp_mod_peak;
            qpinfo->target_i_qp += 1;
            qpinfo->prate_count = 0;
          }
          if (qpinfo->prate_count < qpinfo->prate_WL)
            qpinfo->prate_count++;
        }

    }
    //BL_LOGI("[QP Info Cnt1] inc_cnt %d, dec_cnt %d, stb_cnt %d, cw %f, frm idx %d, win_size %d, rate2 %f\r\n", qpinfo->inc_count, qpinfo->dec_count, qpinfo->stb_count, cw, qpinfo->frm_size_idx_cur, win_size, rate2);
    //2. group tuning to fit target bit-rate
    if (qpinfo->gp_WL > qpinfo->sta_WL) {
        // Todo: recovery mechanism
        MM_Encoder_InitVbrDynamicQP(stream->stream_id);
        return;
    }
    //BL_LOGI("[QP Info Cnt2] pr_count %d, gp_prelen %d, gpWL %d, staWL %d\r\n", qpinfo->prate_count, qpinfo->gp_prelen, qpinfo->gp_WL, qpinfo->sta_WL);
    qpinfo->vbr_qp_ctrl=0;
    if ((qpinfo->frm_cnt % qpinfo->gp_WL) == (qpinfo->gp_WL - qpinfo->gp_prelen)) {
        win_size=0;
        for (widx = 0; widx < qpinfo->gp_WL; widx++) //use most recent gp_WL frames
          win_size += qpinfo->frm_size_hist[(qpinfo->frm_size_idx_cur - 1 - widx + MMENCODER_VBR_QP_FRAME_BCNT_HIST_NUM)%MMENCODER_VBR_QP_FRAME_BCNT_HIST_NUM];

        qpinfo->bitrate_sta = (double)win_size / ((double)(qpinfo->gp_WL) / (double)(fps)); //group bitrate
        temp_gprate = (int)qpinfo->bitrate_sta;
        //BL_LOGI("[QP Info Cnt2.1] temp_gprate %d, target %d, win_size = %d\r\n", temp_gprate, rc_attr->attrH264Vbr.targetBitRate, win_size);
        if(rc_attr->attrH264Vbr.targetBitRate > temp_gprate){
            while(rc_attr->attrH264Vbr.targetBitRate > (temp_gprate << qpinfo->vbr_qp_ctrl))
                qpinfo->vbr_qp_ctrl += 1;

          qpinfo->vbr_qp_ctrl = -qpinfo->vbr_qp_ctrl;
        }
        else if(rc_attr->attrH264Vbr.targetBitRate < temp_gprate) {
            while (temp_gprate > (rc_attr->attrH264Vbr.targetBitRate << qpinfo->vbr_qp_ctrl))
                qpinfo->vbr_qp_ctrl += 1;
        }
        qpinfo->target_p_qp = qpinfo->target_p_qp + qpinfo->vbr_qp_ctrl - pqp_mod_peak; //target qp of next group
//        if(abs(qpinfo->vbr_qp_ctrl)<2)
//            qpinfo->target_p_qp -= qpinfo->vbr_qp_ctrl; // for vbr_qp_ctrl = +-1
    }
    if (qpinfo->frm_cnt % (attr->attrH264.gopSize) == (attr->attrH264.gopSize) - qpinfo->gop_prelen) //update vbr_iqp
        qpinfo->target_i_qp = qpinfo->target_p_qp + qpinfo->iqp_ofst;

    //final clip to max_qp/min_qp
    if (qpinfo->target_i_qp > MMENCODER_IFRAME_MAX_QP)
        qpinfo->target_i_qp = MMENCODER_IFRAME_MAX_QP;
    else if (qpinfo->target_i_qp < MMENCODER_IFRAME_MIN_QP)
        qpinfo->target_i_qp = MMENCODER_IFRAME_MIN_QP;

    if (qpinfo->target_p_qp > MMENCODER_PFRAME_MAX_QP)
        qpinfo->target_p_qp = MMENCODER_PFRAME_MAX_QP;
    else if (qpinfo->target_p_qp < MMENCODER_PFRAME_MIN_QP)
        qpinfo->target_p_qp = MMENCODER_PFRAME_MIN_QP;

    if(stream->frame_type == ENC_H264_P_FRAME)
        qpinfo->prev_bit_count = hw_frm_bitcnt;

    //BL_LOGI("[QP Info Cnt3] frm_cnt %d, gop %d, vbr_qp_ctrl %d, iqp %d, pqp %d\r\n", qpinfo->frm_cnt, attr->attrH264.gopSize, qpinfo->vbr_qp_ctrl, qpinfo->target_i_qp, qpinfo->target_p_qp);

    bl_venc_set_qp(stream->stream_id, qpinfo->target_i_qp, qpinfo->target_p_qp);

    qpinfo->frm_cnt++;
}
#endif

int MM_Encoder_UpdateCbrScenceCtrl(void)
{
    scence_ctrl.force_update = 1;
    return 0;
}

static void MM_Encoder_GetCbrScenceCtrl(int encChn, MMEncoderStream *stream)
{
    int is_enable = 0;
    int ip_ratio = 0, gop_size = 0, min_qp = 10, max_qp = 51;
    int scence_weight = 0;
    int big_motion_weight = 0;
    int scence_status_change = 0;
    MMEncoderGOPSizeCfg gopSizeCfg;
    MMEncoderScenceAttr static_attr, motion_attr, big_motion_attr;
    MMEncoderRcAttr encRcAttr;

    if (stream->frame_type == ENC_JPEG_FRAME) return;
    if (stream->frame_type == ENC_H264_I_FRAME) scence_ctrl.last_i_frame_id = stream->frame_id;

    MM_Encoder_GetChnRcAttr(encChn, &encRcAttr);
    if (encRcAttr.rcMode != ENC_RC_MODE_CBR) return;

    MM_Encoder_GetScenceCtrlStatus(encChn, &is_enable);
    if (is_enable != 1) return;

    MM_Encoder_GetChnGOPSize(encChn, &gopSizeCfg);
    MM_Encoder_GetScenceCtrlReg(encChn,ENC_SC_MODE_STATIC, &static_attr);
    MM_Encoder_GetScenceCtrlReg(encChn,ENC_SC_MODE_MOVING, &motion_attr);
    MM_Encoder_GetScenceCtrlReg(encChn,ENC_SC_MODE_BIGMOVING, &big_motion_attr);
    //printf("========= static %d, %d, %d, %d \r\n",static_attr.scence_thr,static_attr.gop_ratio,static_attr.ip_ratio,static_attr.min_qp,static_attr.max_qp);
   // printf("========= motion %d, %d, %d, %d \r\n",motion_attr.scence_thr,motion_attr.gop_ratio,motion_attr.ip_ratio,motion_attr.min_qp,motion_attr.max_qp);
   // printf("========= big motion %d, %d, %d, %d \r\n",big_motion_attr.scence_thr,big_motion_attr.gop_ratio,big_motion_attr.ip_ratio,big_motion_attr.min_qp,big_motion_attr.max_qp);

    //BL_LOGI("\r\n========stream->frame_id %d, scence_ctrl.last_i_frame_id %d gop %d \r\n", stream->frame_id, scence_ctrl.last_i_frame_id, gopSizeCfg.gopSize);

    bl_venc_get_h264_mv_scence_weight(encChn, &scence_weight, &big_motion_weight);
    if (scence_weight > static_attr.scence_thr) {
        if (scence_ctrl.force_update == 1 || (scence_ctrl.last_scence_status != ENCODER_SCENCE_ID_STATIC)) scence_status_change = 1;
        ip_ratio = static_attr.ip_ratio;
        gop_size = static_attr.gop_size;
        min_qp = static_attr.min_qp;
        max_qp = static_attr.max_qp;
        scence_ctrl.last_scence_status = ENCODER_SCENCE_ID_STATIC;
        //BL_LOGI("==================================================== ENCODER_SCENCE_ID_STATIC \r\n");
    } else if (scence_weight < motion_attr.scence_thr) {
        if (big_motion_weight > big_motion_attr.scence_thr) {
            if (scence_ctrl.force_update == 1 || (scence_ctrl.last_scence_status != ENCODER_SCENCE_ID_BIGMOVING)) scence_status_change = 1;
            ip_ratio = big_motion_attr.ip_ratio;
            gop_size = big_motion_attr.gop_size;
            min_qp = big_motion_attr.min_qp;
            max_qp = big_motion_attr.max_qp;
            scence_ctrl.last_scence_status = ENCODER_SCENCE_ID_BIGMOVING;
            //BL_LOGI("==================================================== ENCODER_SCENCE_ID_BIGMOVING \r\n");
        } else {
            if (scence_ctrl.force_update == 1 || (scence_ctrl.last_scence_status != ENCODER_SCENCE_ID_MOVING)) scence_status_change = 1;
            ip_ratio = motion_attr.ip_ratio;
            gop_size = motion_attr.gop_size;
            min_qp = motion_attr.min_qp;
            max_qp = motion_attr.max_qp;
            scence_ctrl.last_scence_status = ENCODER_SCENCE_ID_MOVING;
            //BL_LOGI("==================================================== ENCODER_SCENCE_ID_MOVING \r\n");
        }
    } else {
        scence_status_change = 1;
        ip_ratio = (scence_weight - motion_attr.scence_thr) * (static_attr.ip_ratio - motion_attr.ip_ratio) / (static_attr.scence_thr - motion_attr.scence_thr) + motion_attr.ip_ratio;
        gop_size = (scence_weight - motion_attr.scence_thr) * (static_attr.gop_size - motion_attr.gop_size) / (static_attr.scence_thr - motion_attr.scence_thr) + motion_attr.gop_size;
        min_qp = (scence_weight - motion_attr.scence_thr) * (static_attr.min_qp - motion_attr.min_qp) / (static_attr.scence_thr - motion_attr.scence_thr) + motion_attr.min_qp;
        max_qp = (scence_weight - motion_attr.scence_thr) * (static_attr.max_qp - motion_attr.max_qp) / (static_attr.scence_thr - motion_attr.scence_thr) + motion_attr.max_qp;
        scence_ctrl.last_scence_status = ENCODER_SCENCE_ID_UNSTABLE;
    }

    if (scence_status_change == 1) {
        scence_ctrl.ip_ratio = ip_ratio;
        scence_ctrl.gopSizeCfg.gopSize = gop_size;
        scence_ctrl.min_qp = min_qp;
        scence_ctrl.max_qp = max_qp;
        scence_ctrl.update_HW_setting = 1;
    }

    if ((stream->frame_id == scence_ctrl.last_i_frame_id + gopSizeCfg.gopSize - 1) && (scence_ctrl.update_HW_setting == 1)) {//setting on this p_frame
        scence_ctrl.update_HW_setting = 0;
        MM_Encoder_SetChnMinQP(encChn, scence_ctrl.min_qp);
        MM_Encoder_SetChnMaxQP(encChn, scence_ctrl.max_qp);
        MM_Encoder_SetChnIpRatio(encChn, scence_ctrl.ip_ratio);
        MM_Encoder_SetChnGOPSize(encChn, &scence_ctrl.gopSizeCfg);
        //BL_LOGI("========stream->frame_id %d, scence_weight %d change %d, ip_ratio %d, gopSize %d, min_qp %d, max_qp %d \r\n",
        //    stream->frame_id, scence_weight, scence_status_change, scence_ctrl.ip_ratio,
        //    scence_ctrl.gopSizeCfg.gopSize, scence_ctrl.min_qp, scence_ctrl.max_qp);
#if 0
        MMEncoderRcAttr *currEncRcAttr = &encoder_rc[encChn];
        MMEncoderAttr *currEncAttr = &encoder_chn[encChn].encAttr;
        BL_LOGI("==================================================== scence_ctrl.last_scence_status %d \r\n", scence_ctrl.last_scence_status);
        printf("===== GetCbrScenceCtrl curr_bitrate %d, gop_ratio %u, ip_ratio %d, min_qp %d, max_qp %d \r\n",
            currEncRcAttr->attrH264Cbr.outBitRate,currEncAttr->attrH264.gopSize,
            currEncRcAttr->attrH264Cbr.iBiasLvl, currEncRcAttr->attrH264Cbr.minQp,currEncRcAttr->attrH264Cbr.maxQp);
#endif
    }
    scence_ctrl.force_update = 0;

}

int MM_Encoder_StartRecvPic(int encChn)
{
    venc_framework_device_t *device;
    MMEncoderAttr *encAttr;
    EncoderChann *enc_chann;
    uint32_t image_size;

    if (encChn < 0 || encChn >= MAX_NUM_ENCODER) {
        BL_LOGE("MM_Encoder_GetStream: Invalid encChn %d\r\n", encChn);
        return -1;
    }

    enc_chann = &encoder_chn[encChn];
    encAttr = &enc_chann->encAttr;
    device = enc_chann->dev;

    if (enc_chann->yuv_encode_mode.mode == ENC_SW_MODE_AUTO) {
        image_size = encAttr->picWidth * encAttr->picHeight;
        device->set_input_y_buffer(device, enc_chann->yuv_encode_mode.yuv_sequence_addr, image_size);
        device->set_input_uv_buffer(device, (enc_chann->yuv_encode_mode.yuv_sequence_addr + image_size), (image_size >> 1));
    }

    /* Create a queue instance for YUV frame queue and msg queue */
    enc_chann->streamQueue = BL_Queue_Create(VENC_RESULT_FIFO_LEN, sizeof(venc_result_t));
    enc_chann->msgQueue = BL_Queue_Create(1, sizeof(EncoderMsg));

    device->config(device);
    device->set_callback(device, alloc_cb, free_cb, recv_cb);
#if MMENCODER_VBR_ADAPTIVE_QP
    MM_Encoder_InitVbrDynamicQP(encChn);
#endif
    memset(&encAttr->stats, 0, sizeof(encAttr->stats));
    if (enc_chann->yuv_encode_mode.mode == ENC_SW_MODE_AUTO) {
        if (device->encode_frame(device, encChn) != 0) {
            return -1;
        }
    } else {
        if (enc_chann->yuv_encode_mode.mode == ENC_SW_MODE_DISABLED) {
            if (device->start(device, encChn) != 0) {
                return -1;
            }
        }
        bl_dsp2_enable_ouput_channel(enc_chann->frmSrcChn);
    }

#if PRINT_FAST_CAP_TIMING
    printf("dsp2 go %lu\r\n", xTaskGetTickCount());
#endif

    return 0;
}

int MM_Encoder_StartRecvSnapshot(int encChn)
{
    venc_framework_device_t *device;
    int dsp2_chn_id;

    if (encChn < 0 || encChn >= MAX_NUM_ENCODER) {
        BL_LOGE("MM_Encoder_GetStream: Invalid encChn %d\r\n", encChn);
        return -1;
    }

    device = encoder_chn[encChn].dev;
    dsp2_chn_id = encoder_chn[encChn].frmSrcChn;

    if (device->get_codec_type(device) != VENC_FRAMEWORK_CODEC_TYPE_JPEG) {
        BL_LOGE("MM_Encoder_StartRecvSnapshot: Codec type doesn't support snapshot\r\n");
        return -1;
    }

    device->config(device);
    device->set_callback(device, alloc_cb, free_cb, recv_cb);

    if (0 != device->encode_frame(device, encChn)) {
        return -1;
    }

    bl_dsp2_enable_ouput_channel(dsp2_chn_id);

    return 0;
}

int MM_Encoder_Stop(int encChn)
{
    int ret;
    EncoderChann *enc_chann;
    venc_framework_device_t *device;
    EncoderMsg enc_msg = {0};

    if (encChn < 0 || encChn >= MAX_NUM_ENCODER) {
        BL_LOGE("MM_Encoder_GetStream: Invalid encChn %d\r\n", encChn);
        return -1;
    }

    enc_chann = &encoder_chn[encChn];
    device = enc_chann->dev;

    if (device->stop(device, stop_cb) != 0) {
        return -1;
    }

    if (enc_chann->yuv_encode_mode.mode == ENC_SW_MODE_DISABLED) {
        /* wait until the encoder is effectively stopped */
        while (ENC_MSG_ENCODER_STOPPED != enc_msg.msgType) {
            ret = BL_Queue_Get_Item(enc_chann->msgQueue, &enc_msg, QUEUE_WAIT_FOREVER);
            if (pdFALSE == ret) {
                BL_LOGE("Get item from queue fail!\r\n");
                return -1;
            }
        }
    }

    return 0;
}

int MM_Encoder_StopRecvPic(int encChn)
{
    EncoderChann *enc_chann;
    venc_framework_device_t *device;

    if (encChn < 0 || encChn >= MAX_NUM_ENCODER) {
        BL_LOGE("MM_Encoder_GetStream: Invalid encChn %d\r\n", encChn);
        return -1;
    }

    enc_chann = &encoder_chn[encChn];
    device = enc_chann->dev;

    device->stop_recv_pic(device);
    device->set_callback(device, NULL, NULL, NULL);

    xSemaphoreTake(enc_chann->mutex, portMAX_DELAY);
    BL_Queue_Delete(enc_chann->streamQueue);
    BL_Queue_Delete(enc_chann->msgQueue);
    enc_chann->streamQueue = NULL;
    enc_chann->msgQueue = NULL;
    xSemaphoreGive(enc_chann->mutex);

    return 0;
}

int MM_Encoder_Frame_Encode_Next(int encChn, uint32_t y_buffer, uint32_t y_size, uint32_t uv_buffer, uint32_t uv_size)
{
    /* continue to encode next frame */
    venc_framework_device_t *device;
    MMEncoderAttr *encAttr;
    uint32_t image_size;
    EncoderChann *enc_chann = &encoder_chn[encChn];

    encAttr = &enc_chann->encAttr;
    device = enc_chann->dev;

    if (enc_chann->yuv_encode_mode.mode != ENC_SW_MODE_DISABLED) {
        device->set_input_y_buffer(device, y_buffer, y_size);
        device->set_input_uv_buffer(device, uv_buffer, uv_size);
//        printf("Encode Next\r\n");
        if (device->encode_frame(device, encChn) != 0) {
            return -1;
        }
    }
    return 0;
}


float MM_Encoder_GetStreamBitrate(int encChn)
{
    return encoder_chn[encChn].encAttr.stats.br_mbps;
}

float MM_Encoder_GetStreamFPS(int encChn)
{
    return encoder_chn[encChn].encAttr.stats.fps;

}

int MM_Encoder_FrameModeGetSource(int frmSrcChn, uint32_t *start_addr, uint32_t *size, uint8_t *y_uv)
{
    FrmSrcChann *fs_chann = &framesource_chn[frmSrcChn];
    bl_dsp2_frame_desc_t yuv_frame;
    int ret = 0;


    if (NULL == fs_chann->streamQueue) {
        BL_LOGE("fs streamqueue is NULL!\r\n");
        return -2;
    }
    ret = BL_Queue_Get_Item(fs_chann->streamQueue, &yuv_frame, QUEUE_WAIT_FOREVER);
    if (pdFALSE == ret) {
//        BL_LOGE("Get item from queue fail!\r\n");
        return -1;
    }
    //BL_LOGD("[%d]start address: 0x%x, size: %d\r\n", yuv_frame.port, (uint32_t) yuv_frame.frame_start_addr, yuv_frame.frame_size);
    *start_addr = (uint32_t) yuv_frame.frame_start_addr;
    *size = yuv_frame.frame_size;
    if (yuv_frame.port & 0x1)
        *y_uv = 1; // uv
    else
        *y_uv = 0; // y

    return 0;
}


int MM_Encoder_GetStream(int encChn, MMEncoderStream *stream)
{
    int ret;
    EncoderChann *enc_chann;
    venc_result_t venc_result;
    venc_framework_device_t *device;
    MMEncoderAttr *encAttr;
    uint32_t image_size;

    if (encChn < 0 || encChn >= MAX_NUM_ENCODER) {
        BL_LOGE("MM_Encoder_GetStream: Invalid encChn %d\r\n", encChn);
        return -1;
    }

    enc_chann = &encoder_chn[encChn];
    if (enc_chann->mutex == NULL) {
        printf("dsp2 is not init\r\n");
        return -1;
    }
    encAttr = &enc_chann->encAttr;
    device = enc_chann->dev;

    xSemaphoreTake(enc_chann->mutex, portMAX_DELAY);

    if (NULL == enc_chann->streamQueue) {
        BL_LOGE("MM_Encoder_GetStream: Stream is already closed!\r\n");
        ret = -1;
        goto abort;
    }

    ret = BL_Queue_Get_Item(enc_chann->streamQueue, &venc_result, QUEUE_WAIT_FOREVER);
    if (pdFALSE == ret) {
        BL_LOGE("Get item from queue fail!\r\n");
        ret = -1;
        goto abort;
    }
    ret = 0;

abort:
    xSemaphoreGive(enc_chann->mutex);
    if (ret) {
        return ret;
    }

    stream->stream_id = venc_result.stream_id;
    stream->frame_type = (venc_result.frame_type == VENC_FRAMEWORK_JPEG_FRAME) ?
                            ENC_JPEG_FRAME : ((venc_result.frame_type == VENC_FRAMEWORK_H264_I_FRAME) ?
                                ENC_H264_I_FRAME : ENC_H264_P_FRAME);
    stream->frame_id = venc_result.frame_id;
    stream->frame_start_addr = venc_result.frame_start_addr;
    stream->frame_size = venc_result.frame_size;
    stream->frame_sec_addr = venc_result.frame_sec_addr;
    stream->frame_sec_size = venc_result.frame_sec_size;
    MM_Encoder_StreamStats(&enc_chann->encAttr.stats, stream);
#if MMENCODER_VBR_ADAPTIVE_QP
    MM_Encoder_GetVbrDynamicQP(stream);
#endif
    if (rate_ctrl_lvl[encChn].rateCtrlLevel == 0) MM_Encoder_GetCbrScenceCtrl(encChn, stream);

    /* continue to encode next frame */
    if (enc_chann->yuv_encode_mode.mode == ENC_SW_MODE_AUTO) {
        image_size = encAttr->picWidth * encAttr->picHeight;
        enc_chann->yuv_encode_mode.yuv_sequence_addr += (image_size * 3 >> 1);
        if (MM_Encoder_Frame_Encode_Next(encChn, enc_chann->yuv_encode_mode.yuv_sequence_addr, image_size,
            enc_chann->yuv_encode_mode.yuv_sequence_addr + image_size, image_size >> 1) < 0)
            return -1;
    }

    return 0;
}

int MM_Encoder_H264_Frame_Done(int encChn, MMEncoderStream *stream)
{
    bl_h264_bs_buff_info_t buf_info = {0};
    int ret = 0;

    if (encChn < 0 || encChn >= MAX_NUM_ENCODER) {
        BL_LOGE("[ERROR] Invalid encChn %d\r\n", encChn);
        return -1;
    }

    if ((!stream) || ((stream->frame_type != ENC_H264_I_FRAME)
         && (stream->frame_type != ENC_H264_P_FRAME))) {
        BL_LOGE("[ERROR] Only support handling h264 frame done!!\r\n");
        return -1;
    }

    memset(&buf_info, 0, sizeof(bl_h264_bs_buff_info_t));
    buf_info.base_addr = stream->frame_start_addr;
    buf_info.size = stream->frame_size;
    buf_info.sec_base_addr = stream->frame_sec_addr;
    buf_info.sec_size = stream->frame_sec_size;
    /*
    BL_LOGI("free addr:%p size:0x%x sec_addr:%p sec_size:0x%0x\r\n",
            buf_info.base_addr,
            buf_info.size,
            buf_info.sec_base_addr,
            buf_info.sec_size);
    */
    ret = bl_venc_h264_frame_done(encChn, &buf_info);
    if (ret) {
        BL_LOGE("[ERROR] H264 Frame done error!!\r\n");
        return 1;
    }

    return 0;
}

int MM_Encoder_ResetStreamQueue(int encChn)
{
    int ret = 0;
    EncoderChann *enc_chann;

    if (encChn < 0 || encChn >= MAX_NUM_ENCODER) {
        BL_LOGE("MM_Encoder_GetStream: Invalid encChn %d\r\n", encChn);
        return -1;
    }

    enc_chann = &encoder_chn[encChn];
    if (NULL == enc_chann->mutex) {
        printf("reset stream mutex null\r\n");
        return -1;
    }
    xSemaphoreTake(enc_chann->mutex, portMAX_DELAY);

    if (NULL == enc_chann->streamQueue) {
        BL_LOGE("MM_Encoder_GetStream: Stream is already closed!\r\n");
        ret = -1;
        goto exit;
    }

    if (BL_Queue_Get_Spaces_Available(enc_chann->streamQueue) <= 14) {
        BL_Queue_Reset(enc_chann->streamQueue);
    }
exit:
    xSemaphoreGive(enc_chann->mutex);
    return ret;
}

bool MM_Encoder_CheckStreamBusy(int encChn)
{
    venc_framework_device_t *device;

    if (encChn < 0 || encChn >= MAX_NUM_ENCODER) {
        BL_LOGE("MM_Encoder_GetStream: Invalid encChn %d\r\n", encChn);
        return -1;
    }
    device = encoder_chn[encChn].dev;

    return device->is_busy(device);
}

void MM_Encoder_SWModeConfig(int encChn, MMEncoderFrameEncMode mode, uint8_t *base_addr)
{
    encoder_chn[encChn].yuv_encode_mode.mode = mode;
    encoder_chn[encChn].yuv_encode_mode.yuv_sequence_addr = base_addr;
}

int MM_Encoder_EncodeOneFrame(int encChn, uint8_t *yuv_frame_addr, uint32_t *read_bytes)
{
    uint32_t image_size;
    uint32_t width, height;
    venc_framework_device_t *device;

    if (encChn < 0 || encChn >= MAX_NUM_ENCODER) {
        BL_LOGE("MM_Encoder_GetStream: Invalid encChn %d\r\n", encChn);
        return -1;
    }

    device = encoder_chn[encChn].dev;

    device->get_resolution(device, &width, &height);
    image_size = width * height;

    device->set_input_y_buffer(device, yuv_frame_addr, image_size);
    device->set_input_uv_buffer(device, (yuv_frame_addr + image_size), (image_size >> 1));
    device->config(device);
    device->encode_frame(device, encChn);

    *read_bytes = (image_size * 3 >> 1);

    return 0;
}

void* MM_Encoder_Get_Device(int id)
{
    void *device;

    if (id < 0 || id >= MAX_NUM_ENCODER) {
        BL_LOGE("Get encoder device fail!! input_id:%d\r\n", id);
        return NULL;
    }

    device = &encoder_chn[id].dev;

    return device;
}

int MM_Encoder_New(int id)
{
    char name[MAX_NAME_SIZE] = {0};
    void *device = NULL;
    int ret = 0;

    if (id < 0 || id >= MAX_NUM_ENCODER) {
        BL_LOGE("Creat encoder fail!! id is illegal!! input_id:%d\r\n", id);
        return -1;
    }

    switch (id) {
        case ENCODER_ID_H264_STREAMA:
            memcpy(name, "h264_main", sizeof("h264_main"));
            break;
        case ENCODER_ID_H264_STREAMB:
            memcpy(name, "h264_sub", sizeof("h264_sub"));
            break;
        case ENCODER_ID_MJPEG:
            memcpy(name, "jpeg", sizeof("jpeg"));
            break;
        default:
            BL_LOGE("Encoder id is illegal!!\r\n");
            ret = 1;
            break;
    }

    if (ret)
        return ret;

    device = MM_Encoder_Get_Device(id);
    if (!device) {
        BL_LOGE("Get encoder device fail!! %s line:%d\r\n", __func__, __LINE__);
        return -1;
    }

    ret = venc_framework_factory_build(name, device);
    if (ret) {
        BL_LOGE("Build device fail!! %s line:%d\r\n", __func__, __LINE__);
        return -1;
    }

    set_h264_encoder_default(id);

    return 0;
}

int MM_Encoder_Delete(int id)
{
    void *device = NULL;
    int ret = 0;

    if (id < 0 || id >= MAX_NUM_ENCODER) {
        BL_LOGE("Delete encoder fail!! id is illegal!! input_id:%d\r\n", id);
        return -1;
    }

    device = MM_Encoder_Get_Device(id);
    if (!device) {
        BL_LOGE("Get encoder device fail!! %s line:%d\r\n", __func__, __LINE__);
        return -1;
    }

    ret = venc_framework_factory_destory(device);
    if (ret) {
		BL_LOGE("Destroy encoder fail %s line:%d\r\n", __func__, __LINE__);
        return -1;
    }

    return 0;
}

int MM_System_Init(void)
{
    MM_System_CHN_Init();

    venc_framework_factory_build("h264_main", &encoder_chn[0].dev);
    venc_framework_factory_build("h264_sub", &encoder_chn[1].dev);
    venc_framework_factory_build("jpeg", &encoder_chn[2].dev);

    set_h264_encoder_default(0);
    set_h264_encoder_default(1);
    set_jpeg_encoder_default(2);

    return 0;
}

int MM_System_Bind(int frmSrcChn, int encChn)
{
    venc_framework_device_t *device;
    bl_mmsys_bind_buffer_t *bind_buffer;
    uint32_t width, height;
    BL_MMSYS_BIND_TARGET_T bind_target;
    bl_dsp2_output_buffer_t dsp2_out_buf;
    MMDSP2FrmSrcAttr *frmSrcAttr;
    MMEncoderAttr *encAttr;
    FrmSrcChann *fs_chann;

    if (frmSrcChn < 0 || frmSrcChn >= MAX_NUM_FRAMESOURCE) {
        BL_LOGE("MM_System_Bind: invalid frmSrcChn %d\r\n", frmSrcChn);
        return -1;
    }

    if (encChn < 0 || encChn >= MAX_NUM_ENCODER) {
        BL_LOGE("MM_System_Bind: invalid encChn %d\r\n", encChn);
        return -1;
    }

    fs_chann = &framesource_chn[frmSrcChn];
    frmSrcAttr = &fs_chann->frmSrcAttr;
    encAttr = &encoder_chn[encChn].encAttr;

    if (frmSrcAttr->pixFmt != PIX_FMT_NV12) {
        BL_LOGE("MM_System_Bind: framesource is not NV12 format!\r\n");
        return -1;
    }
    if ((frmSrcAttr->picWidth != encAttr->picWidth) ||
        (frmSrcAttr->picHeight != encAttr->picHeight)) {
        BL_LOGE("MM_System_Bind: resolution doesn't match! %dx%d != %dx%d\r\n",
            frmSrcAttr->picWidth, frmSrcAttr->picHeight,
            encAttr->picWidth, encAttr->picHeight);
        return -1;
    }

    if ((frmSrcAttr->outFrmRateNum != encAttr->frmRateNum) ||
        (frmSrcAttr->outFrmRateDen != encAttr->frmRateDen)) {
        BL_LOGW("[WARNING] MM_System_Bind: frame rate doesn't match!"
                " frmSrcAttr->outFrmRateNum:%d frmSrcAttr->outFrmRateDen:%d"
                " encAttr->frmRateNum:%d encAttr->frmRateDen:%d\r\n",
                frmSrcAttr->outFrmRateNum, frmSrcAttr->outFrmRateDen,
                encAttr->frmRateNum, encAttr->frmRateDen);
    }

    bind_buffer = &fs_chann->bind_buffer;
    bind_target = (direct_link_mode ? BL_MMSYS_BIND_TO_VENC_DIRECT_LINK : BL_MMSYS_BIND_TO_VENC);
    device = encoder_chn[encChn].dev;

    device->get_resolution(device, &width, &height);
    bl_mmsys_create_bind_buffer(width, height, bind_target, bind_buffer);

    dsp2_out_buf.y_frame_base_addr = bind_buffer->y_frame_base_addr;
    dsp2_out_buf.y_frame_size = bind_buffer->y_frame_size;
    dsp2_out_buf.uv_frame_base_addr = bind_buffer->uv_frame_base_addr;
    dsp2_out_buf.uv_frame_size = bind_buffer->uv_frame_size;
    if (encoder_chn[encChn].yuv_encode_mode.mode == ENC_SW_MODE_DISABLED)
        bl_dsp2_set_ouput_buffer(frmSrcChn, &dsp2_out_buf, DISABLE);
    else
        bl_dsp2_set_ouput_buffer(frmSrcChn, &dsp2_out_buf, ENABLE);

    if (encoder_chn[encChn].yuv_encode_mode.mode == ENC_SW_MODE_MANUAL) {
        fs_chann->streamQueue = BL_Queue_Create(FRAME_FIFO_LEN, sizeof(bl_dsp2_frame_desc_t));
        bl_dsp2_frame_ready_config(frmSrcChn, frame_ready_cb, NULL);
    }

#if 1
    device->set_input_y_buffer(device, bind_buffer->y_frame_base_addr, bind_buffer->y_frame_size);
    device->set_input_uv_buffer(device, bind_buffer->uv_frame_base_addr, bind_buffer->uv_frame_size);
#else   /* fix input yuv content for debug purpose */
    device->set_input_y_buffer(device, 0xa0000000, 921600*2);
    device->set_input_uv_buffer(device, (0xa0000000 + 921600), (921600*2 >> 1));
#endif

    device->bind_to_dsp2_channel(device, frmSrcChn);

    fs_chann->refCnt++;
    encoder_chn[encChn].frmSrcChn = frmSrcChn;

    return 0;
}

int MM_System_UnBind(int frmSrcChn, int encChn)
{
    if (frmSrcChn < 0 || frmSrcChn >= MAX_NUM_FRAMESOURCE) {
        BL_LOGE("MM_System_UnBind: invalid frmSrcChn %d\r\n", frmSrcChn);
        return -1;
    }

    if (encChn < 0 || encChn >= MAX_NUM_ENCODER) {
        BL_LOGE("MM_System_UnBind: invalid encChn %d\r\n", encChn);
        return -1;
    }

    if (--framesource_chn[frmSrcChn].refCnt == 0) {
        BL_LOGI("[MM_LIB] release bind buffer\r\n");
        if (encoder_chn[encChn].yuv_encode_mode.mode == ENC_SW_MODE_MANUAL) {
            BL_Queue_Delete(framesource_chn[frmSrcChn].streamQueue);
            bl_dsp2_frame_ready_config(frmSrcChn, NULL, NULL);
        }

        BL_MMSYS_BIND_TARGET_T bind_target = (direct_link_mode ? BL_MMSYS_BIND_TO_VENC_DIRECT_LINK : BL_MMSYS_BIND_TO_VENC);
        bl_dsp2_disable_output_channel(frmSrcChn);
        bl_mmsys_delete_bind_buffer(&framesource_chn[frmSrcChn].bind_buffer, bind_target);
    }

    return 0;
}

int MM_DBG_EnableVirtualSensor(bool enable, const VirtualSensorInfo *virtSnsInfo)
{
    if (enable) {
        if (check_resolution(virtSnsInfo->width, virtSnsInfo->height) != 0) {
            return -1;
        }
        virt_sns_info = *virtSnsInfo;
    }

    is_virt_sensor = enable;
    return 0;
}

int MM_DBG_IsVirtualSensor(bool *enable)
{
    *enable = is_virt_sensor;
    return 0;
}

int MM_DBG_SetPatternGenMode(int mode)
{
    g_pattern_gen_mode = mode;
    return 0;
}

int MM_DBG_GetSensorName(const char** name)
{
    *name = g_vin_cfg.sensor_name;

    return 0;
}

int MM_DBG_GetSensorBayerPattern(uint32_t *bayerPatternID)
{
    *bayerPatternID = g_vin_cfg.bayer_pattern;

    return 0;
}

int MM_DBG_GetVirtSensorTsrcAddr(uint32_t *addr)
{
    *addr = dsp2_tsrc_pic_addr;

    return 0;
}


