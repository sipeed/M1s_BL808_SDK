#include <string.h>
#include <aos/kernel.h>
#include <bl808_common.h>
#include <bl_venc.h>

#include "mm_system.h"
#include "mm_sensor.h"
#include "mm_dsp2.h"
#include "mm_encoder.h"
#include "file_sink.h"

#include "sample_common.h"

#define ENC_CH0_ID                          (0)
#define ENC_CH1_ID                          (1)
#define ENC_CH2_ID                          (2)
#define DSP2_CH0_ID                          (0)
#define DSP2_CH1_ID                          (1)
#define DSP2_CH2_ID                          (2)

#define VENC_RESULT_FIFO_LEN                (16)
#define MEMCPY_ALIGN_EN

#ifdef MEMCPY_ALIGN_EN
#define MEMCPY_ALIGN(x, mask)  (((x) + ((mask)-1)) & ~((mask)-1))
#else
#define MEMCPY_ALIGN(x, mask)  (x)
#endif

typedef struct {
    MMEncoderType stream_type;
    int enc_chn_id;
    int dsp2_chn_id;
    MMDSP2FrmSrcAttr dsp2_chn_attr;
    MMEncoderAttr enc_chn_attr;
    MMEncoderRcAttr enc_rc_attr;
} chn_cfg_t;

static chn_cfg_t *chn = NULL;

static void sample_common_init(void)
{
    if (NULL != chn) {
        return;
    }

    chn =  (chn_cfg_t *)pvPortMalloc(MAX_CHN_NUM*sizeof(chn_cfg_t));
    if (NULL == chn) {
        printf("malloc sample channel error!\r\n");
        return;
    }
}

static void sample_set_h264_main(chn_cfg_t * cfg, MMSensorAttr *snsAttr)
{
    cfg->stream_type = ENC_TYPE_H264;

    cfg->enc_chn_id = ENC_CH0_ID;
    cfg->dsp2_chn_id = DSP2_CH0_ID;

    cfg->dsp2_chn_attr.pixFmt = PIX_FMT_NV12;
    cfg->dsp2_chn_attr.picWidth = snsAttr->picWidth;
    cfg->dsp2_chn_attr.picHeight = snsAttr->picHeight;
    cfg->dsp2_chn_attr.outFrmRateNum = snsAttr->fps;
    cfg->dsp2_chn_attr.outFrmRateDen = 1;
    cfg->dsp2_chn_attr.isFullRange = false;

    cfg->enc_chn_attr.encType = ENC_TYPE_H264;
    cfg->enc_chn_attr.picWidth = snsAttr->picWidth;
    cfg->enc_chn_attr.picHeight = snsAttr->picHeight;
    cfg->enc_chn_attr.frmRateNum = snsAttr->fps;
    cfg->enc_chn_attr.frmRateDen = 1;

    cfg->enc_chn_attr.attrH264.profile = ENC_PROFILE_BASELINE;
    cfg->enc_chn_attr.attrH264.lowPwrMode = ENC_NORMAL_MODE;
    cfg->enc_chn_attr.attrH264.gopSize = 25;

    cfg->enc_rc_attr.rcMode = ENC_RC_MODE_CBR;
}

static void sample_set_h264_sub(chn_cfg_t * cfg, MMSensorAttr *snsAttr)
{
    cfg->stream_type = ENC_TYPE_H264;
    cfg->enc_chn_id = ENC_CH1_ID;
    cfg->dsp2_chn_id = DSP2_CH1_ID;

    cfg->dsp2_chn_attr.pixFmt = PIX_FMT_NV12;
    cfg->dsp2_chn_attr.picWidth = 640;
    cfg->dsp2_chn_attr.picHeight = 480;
    cfg->dsp2_chn_attr.outFrmRateNum = snsAttr->fps;
    cfg->dsp2_chn_attr.outFrmRateDen = 1;
    cfg->dsp2_chn_attr.isFullRange = false;

    cfg->enc_chn_attr.encType = ENC_TYPE_H264;
    cfg->enc_chn_attr.picWidth = 640;
    cfg->enc_chn_attr.picHeight = 480;
    cfg->enc_chn_attr.frmRateNum = snsAttr->fps;
    cfg->enc_chn_attr.frmRateDen = 1;

    cfg->enc_chn_attr.attrH264.profile = ENC_PROFILE_BASELINE;
    cfg->enc_chn_attr.attrH264.lowPwrMode = ENC_NORMAL_MODE;
    cfg->enc_chn_attr.attrH264.gopSize = 25;

    cfg->enc_rc_attr.rcMode = ENC_RC_MODE_CBR;
}

static void sample_set_jpeg(chn_cfg_t * cfg, MMSensorAttr *snsAttr)
{
    cfg->stream_type = ENC_TYPE_JPEG;
    cfg->enc_chn_id = ENC_CH2_ID;
    cfg->dsp2_chn_id = DSP2_CH2_ID;

    cfg->dsp2_chn_attr.pixFmt = PIX_FMT_NV12;
    cfg->dsp2_chn_attr.picWidth = snsAttr->picWidth;
    cfg->dsp2_chn_attr.picHeight = snsAttr->picHeight;
    cfg->dsp2_chn_attr.outFrmRateNum = snsAttr->fps;
    cfg->dsp2_chn_attr.outFrmRateDen = 1;
    cfg->dsp2_chn_attr.isFullRange = true;

    cfg->enc_chn_attr.encType = ENC_TYPE_JPEG;
    cfg->enc_chn_attr.picWidth = snsAttr->picWidth;
    cfg->enc_chn_attr.picHeight = snsAttr->picHeight;
    cfg->enc_chn_attr.frmRateNum = snsAttr->fps;
    cfg->enc_chn_attr.frmRateDen = 1;
    cfg->enc_chn_attr.attrJpeg.quality = 50;
}

static void sample_set_ai(chn_cfg_t * cfg, MMSensorAttr *snsAttr)
{
    cfg->stream_type = ENC_TYPE_H264;
    cfg->enc_chn_id = 3;
    cfg->dsp2_chn_id = 3;

    cfg->dsp2_chn_attr.pixFmt = PIX_FMT_NV12;
    cfg->dsp2_chn_attr.picWidth = snsAttr->picWidth;
    cfg->dsp2_chn_attr.picHeight = snsAttr->picHeight;
    cfg->dsp2_chn_attr.outFrmRateNum = snsAttr->fps;
    cfg->dsp2_chn_attr.outFrmRateDen = 1;
    cfg->dsp2_chn_attr.isFullRange = true;
    cfg->dsp2_chn_attr.dsp2Position = BL_IMAGE_DUMP_SRC_YUV2RGB;
    cfg->enc_chn_attr.encType = ENC_TYPE_H264;
    cfg->enc_chn_attr.picWidth = snsAttr->picWidth;
    cfg->enc_chn_attr.picHeight = snsAttr->picHeight;
    cfg->enc_chn_attr.frmRateNum = snsAttr->fps;
    cfg->enc_chn_attr.frmRateDen = 1;
}

static void sample_set_dsp2_sensor_param(chn_cfg_t * cfg, MMSensorAttr *snsAttr)
{
    cfg->dsp2_chn_attr.picWidth = snsAttr->picWidth;
    cfg->dsp2_chn_attr.picHeight = snsAttr->picHeight;
    cfg->dsp2_chn_attr.outFrmRateNum = snsAttr->fps;
    cfg->dsp2_chn_attr.outFrmRateDen = 1;
}

int sample_sub_system_init(void)
{
    int i;
    MMSensorAttr snsAttr;

    MM_Sensor_GetChnAttr(0, &snsAttr);

    sample_common_init();
    sample_set_h264_main(&chn[CH0_ID], &snsAttr);
    sample_set_h264_sub( &chn[CH1_ID], &snsAttr);
    sample_set_jpeg(     &chn[CH2_ID], &snsAttr);
    sample_set_ai(       &chn[CH3_ID], &snsAttr);

    for (i = 0; i < MAX_CHN_NUM; i++) {
        MM_DSP2_SetFrameSrcChnAttr(chn[i].dsp2_chn_id, &chn[i].dsp2_chn_attr);
    }

    return 0;
}

int sample_system_init(void)
{
    int i, ret;
    MMSensorAttr snsAttr;

    bl_dsp2_update_fps_cb cb = sample_set_chann_frame_rate_from_sensor;
    MM_DSP2_Update_FPS_Register(&cb);

    ret = MM_DSP2_Init_Run();
    if (-1 == ret) {
        BL_LOGE("DSP2 Init failed!\r\n");
        return -1;
    }

    MM_Sensor_GetChnAttr(0, &snsAttr);

    sample_common_init();
    sample_set_h264_main(&chn[CH0_ID], &snsAttr);
    sample_set_h264_sub( &chn[CH1_ID], &snsAttr);
    sample_set_jpeg(     &chn[CH2_ID], &snsAttr);
    sample_set_ai(       &chn[CH3_ID], &snsAttr);

    for (i = 0; i < MAX_CHN_NUM; i++) {
        MM_DSP2_SetFrameSrcChnAttr(chn[i].dsp2_chn_id, &chn[i].dsp2_chn_attr);
    }

    return 0;
}

int sample_system_vir_encoder_init()
{
    int i;
    MMSensorAttr snsAttr;

    MM_Sensor_GetChnAttr(0, &snsAttr);

    sample_common_init();

    sample_set_h264_main(&chn[CH0_ID], &snsAttr);
    sample_set_h264_sub( &chn[CH1_ID], &snsAttr);
    sample_set_jpeg(     &chn[CH2_ID], &snsAttr);
    sample_set_ai(       &chn[CH3_ID], &snsAttr);

    for (i = 0; i < MAX_CHN_NUM; i++) {
        MM_DSP2_SetFrameSrcChnAttr(chn[i].dsp2_chn_id, &chn[i].dsp2_chn_attr);
    }

    return 0;
}

int sample_system_vir_init(void)
{
    int i;
    MMSensorAttr snsAttr;

    int ret;
    ret = MM_DSP2_Init_Run();
    if (-1 == ret) {
        BL_LOGE("DSP2 Init failed!\r\n");
        return -1;
    }
    MM_Sensor_GetChnAttr(0, &snsAttr);
    sample_common_init();

    sample_set_h264_main(&chn[CH0_ID], &snsAttr);
    sample_set_h264_sub( &chn[CH1_ID], &snsAttr);
    sample_set_jpeg(     &chn[CH2_ID], &snsAttr);
    sample_set_ai(       &chn[CH3_ID], &snsAttr);

    for (i = 0; i < MAX_CHN_NUM; i++) {
        MM_DSP2_SetFrameSrcChnAttr(chn[i].dsp2_chn_id, &chn[i].dsp2_chn_attr);
    }

    return 0;
}

int sample_system_quick_init(void)
{
    int i;
    MMSensorAttr snsAttr;

    MM_DSP2_Init_Run();

    MM_Sensor_GetChnAttr(0, &snsAttr);

    sample_common_init();
    sample_set_h264_main(&chn[CH0_ID], &snsAttr);
    sample_set_h264_sub( &chn[CH1_ID], &snsAttr);
    sample_set_jpeg(     &chn[CH2_ID], &snsAttr);
    sample_set_ai(       &chn[CH3_ID], &snsAttr);

    for (i = 0; i < MAX_CHN_NUM; i++) {
        MM_DSP2_SetFrameSrcChnAttr(chn[i].dsp2_chn_id, &chn[i].dsp2_chn_attr);
    }

    return 0;
}

int sample_system_mjpeg_init(void)
{
    int i, ret;
    MMSensorAttr snsAttr;

    ret = MM_DSP2_Init_Run();
    if (-1 == ret) {
        BL_LOGE("DSP2 Init failed!\r\n");
        return -1;
    }

    MM_Sensor_GetChnAttr(0, &snsAttr);

    sample_common_init();
    sample_set_h264_main(&chn[CH0_ID], &snsAttr);
    sample_set_h264_sub( &chn[CH1_ID], &snsAttr);
    sample_set_jpeg(     &chn[CH2_ID], &snsAttr);
    sample_set_ai(       &chn[CH3_ID], &snsAttr);
    sample_set_dsp2_sensor_param(&chn[CH0_ID], &snsAttr);
    sample_set_dsp2_sensor_param(&chn[CH1_ID], &snsAttr);

    for (i = 0; i < MAX_CHN_NUM; i++) {
        MM_DSP2_SetFrameSrcChnAttr(chn[i].dsp2_chn_id, &chn[i].dsp2_chn_attr);
    }

    return 0;
}

void sample_deinit(void)
{
    if (NULL != chn) {
        vPortFree(chn);
        chn = NULL;
    }

    return;
}

int sample_encoder_init(void)
{
    int i;
    MMEncoderAttr *encAttr;
    MMEncoderRcAttr *encRcAttr;
    MMEncoderRcAttr init_encRcAttr;

    for (i = 0; i < MAX_CHN_NUM; i++) {
        encAttr = &chn[i].enc_chn_attr;
        if (ENC_TYPE_H264 == encAttr->encType) {
            encRcAttr = &chn[i].enc_rc_attr;
            
            MM_Encoder_GetRegInit(&init_encRcAttr);
            encRcAttr->rcMode = init_encRcAttr.rcMode;

            encRcAttr->attrH264Cbr.outBitRate = init_encRcAttr.attrH264Cbr.outBitRate;
            encRcAttr->attrH264Cbr.initQp = init_encRcAttr.attrH264Cbr.initQp;
            encRcAttr->attrH264Cbr.maxQp = init_encRcAttr.attrH264Cbr.maxQp;
            encRcAttr->attrH264Cbr.minQp = init_encRcAttr.attrH264Cbr.minQp;
            encRcAttr->attrH264Cbr.iBiasLvl = init_encRcAttr.attrH264Cbr.iBiasLvl;

            encRcAttr->attrH264Vbr.targetBitRate = init_encRcAttr.attrH264Vbr.targetBitRate;
            encRcAttr->attrH264Vbr.maxBitRate = init_encRcAttr.attrH264Vbr.maxBitRate;
            encRcAttr->attrH264Vbr.qualityLvl = init_encRcAttr.attrH264Vbr.qualityLvl;
            encRcAttr->attrH264Vbr.maxQp = init_encRcAttr.attrH264Vbr.maxQp;
            encRcAttr->attrH264Vbr.minQp = init_encRcAttr.attrH264Vbr.minQp;
            encRcAttr->attrH264Vbr.iBiasLvl = init_encRcAttr.attrH264Vbr.iBiasLvl;
            MM_Encoder_SetChnRcAttr(chn[i].enc_chn_id, encRcAttr);

            MM_Encoder_GetScenceCtrlRegInit(i, encRcAttr->attrH264Cbr.outBitRate);
        }

        MM_Encoder_CreateChn(chn[i].enc_chn_id);
        MM_Encoder_SetChnAttr(chn[i].enc_chn_id, encAttr);
    }

	return 0;
}

int sample_set_chann_resolution(int chn_id, uint32_t width, uint32_t height)
{
    int dsp2_chn_id, enc_chn_id;
    MMDSP2FrmSrcAttr frmsrc_attr;
    MMEncoderAttr enc_attr;

    if (chn_id >= MAX_CHN_NUM) {
        BL_LOGE("Invalid channel id\r\n");
        return -1;
    }

    dsp2_chn_id = chn[chn_id].dsp2_chn_id;
    enc_chn_id = chn[chn_id].enc_chn_id;


    MM_DSP2_GetFrameSrcChnAttr(dsp2_chn_id, &frmsrc_attr);
    frmsrc_attr.picWidth = width;
    frmsrc_attr.picHeight = height;
    MM_DSP2_SetFrameSrcChnAttr(dsp2_chn_id, &frmsrc_attr);

    MM_Encoder_GetChnAttr(enc_chn_id, &enc_attr);
    enc_attr.picWidth = width;
    enc_attr.picHeight = height;
    MM_Encoder_SetChnAttr(enc_chn_id, &enc_attr);

    return 0;
}

int sample_get_chann_resolution(int chn_id, uint32_t *width, uint32_t *height)
{
    int dsp2_chn_id;
    MMDSP2FrmSrcAttr frmsrc_attr;

    if (chn_id >= MAX_CHN_NUM) {
        BL_LOGE("Invalid channel id\r\n");
        return -1;
    }

    dsp2_chn_id = chn[chn_id].dsp2_chn_id;

    MM_DSP2_GetFrameSrcChnAttr(dsp2_chn_id, &frmsrc_attr);
    *width = frmsrc_attr.picWidth;
    *height = frmsrc_attr.picHeight;

    return 0;
}

int sample_get_chann_frame_rate(int chn_id)
{
    MMDSP2FrmRate outFpsCfg;

    if (chn_id >= MAX_CHN_NUM) {
        BL_LOGE("Invalid channel id\r\n");
        return -1;
    }

    MM_DSP2_GetFrameSrcChnFPS(chn[chn_id].dsp2_chn_id, &outFpsCfg);

    return outFpsCfg.frmRateNum / outFpsCfg.frmRateDen;
}


int sample_set_chann_frame_rate_from_sensor(int chn_id, uint32_t fps)
{
    int dsp2_chn_id, enc_chn_id;
    MMDSP2FrmRate outFpsCfg;
    MMEncoderFrmRate fpsCfg;
    MMEncoderGOPSizeCfg gopSizeCfg;
    MMSensorAttr snsAttr;

    if (chn_id >= MAX_CHN_NUM) {
        BL_LOGE("Invalid channel id\r\n");
        return -1;
    }

    if (fps <= 0) {
        BL_LOGE("Invalid fps\r\n");
        return -1;
    }

    dsp2_chn_id = chn[chn_id].dsp2_chn_id;
    enc_chn_id = chn[chn_id].enc_chn_id;

    // fps: 15, 30
    if (MM_Sensor_ChangeFPS(fps) < 0) return -1;
    MM_Sensor_GetChnAttr(dsp2_chn_id, &snsAttr);
    snsAttr.fps = fps;
    MM_Sensor_SetChnAttr(dsp2_chn_id, &snsAttr);

    outFpsCfg.frmRateNum = fps;
    outFpsCfg.frmRateDen = 1;
    MM_DSP2_SetFrameSrcChnFPS(dsp2_chn_id, &outFpsCfg);

    fpsCfg.frmRateNum = fps;
    fpsCfg.frmRateDen = 1;
    MM_Encoder_SetChnFrmRate(enc_chn_id, &fpsCfg);

    /* keep I frame rate as 1 fps */
    gopSizeCfg.gopSize = fps;
    MM_Encoder_SetChnGOPSize(enc_chn_id, &gopSizeCfg);

    return 0;
}

int sample_set_chann_frame_rate(int chn_id, uint32_t fps)
{
    int dsp2_chn_id, enc_chn_id;
    MMDSP2FrmRate outFpsCfg;
    MMEncoderFrmRate fpsCfg;
    MMEncoderGOPSizeCfg gopSizeCfg;

    if (chn_id >= MAX_CHN_NUM) {
        BL_LOGE("Invalid channel id\r\n");
        return -1;
    }

    if (fps <= 0) {
        BL_LOGE("Invalid fps\r\n");
        return -1;
    }

    dsp2_chn_id = chn[chn_id].dsp2_chn_id;
    enc_chn_id = chn[chn_id].enc_chn_id;

    outFpsCfg.frmRateNum = fps;
    outFpsCfg.frmRateDen = 1;
    MM_DSP2_SetFrameSrcChnFPS(dsp2_chn_id, &outFpsCfg);

    fpsCfg.frmRateNum = fps;
    fpsCfg.frmRateDen = 1;
    MM_Encoder_SetChnFrmRate(enc_chn_id, &fpsCfg);

    /* keep I frame rate as 1 fps */
    gopSizeCfg.gopSize = fps;
    MM_Encoder_SetChnGOPSize(enc_chn_id, &gopSizeCfg);

    return 0;
}

int sample_set_chann_rc_mode(int chn_id, MMEncoderRcMode rcMode)
{
    int enc_chn_id;
    MMEncoderRcAttr encRcAttr;

    if (chn_id >= MAX_CHN_NUM) {
        BL_LOGE("Invalid channel id\r\n");
        return -1;
    }

    enc_chn_id = chn[chn_id].enc_chn_id;

    MM_Encoder_GetChnRcAttr(enc_chn_id, &encRcAttr);
    encRcAttr.rcMode = rcMode;
    MM_Encoder_SetChnRcAttr(enc_chn_id, &encRcAttr);

    return 0;
}

int sample_set_chann_bit_rate(int chn_id, uint32_t bitRate)
{
    int enc_chn_id;
    MMEncoderBitRateCfg bitRateCfg;

    if (chn_id >= MAX_CHN_NUM) {
        BL_LOGE("Invalid channel id\r\n");
        return -1;
    }

    enc_chn_id = chn[chn_id].enc_chn_id;

    bitRateCfg.bitRate = bitRate;
    MM_Encoder_SetChnBitRate(enc_chn_id, &bitRateCfg);

    return 0;
}

int sample_set_chann_vbr_max_bit_rate(int chn_id, uint32_t bitRate)
{
    int enc_chn_id;
    MMEncoderBitRateCfg bitRateCfg;

    if (chn_id >= MAX_CHN_NUM) {
        BL_LOGE("Invalid channel id\r\n");
        return -1;
    }

    enc_chn_id = chn[chn_id].enc_chn_id;

    bitRateCfg.bitRate = bitRate;
    MM_Encoder_SetChnMaxBitRate(enc_chn_id, &bitRateCfg);

    return 0;
}

int sample_set_chann_ip_ratio(int chn_id, uint32_t ip_ratio)
{
    int enc_chn_id;

    if (chn_id >= MAX_CHN_NUM) {
        BL_LOGE("Invalid channel id\r\n");
        return -1;
    }

    enc_chn_id = chn[chn_id].enc_chn_id;
    MM_Encoder_SetChnIpRatio(enc_chn_id, ip_ratio);

    return 0;
}
int sample_set_chann_max_qp(int chn_id, uint32_t qp)
{
    int enc_chn_id;

    if (chn_id >= MAX_CHN_NUM) {
        BL_LOGE("Invalid channel id\r\n");
        return -1;
    }

    enc_chn_id = chn[chn_id].enc_chn_id;
    MM_Encoder_SetChnMaxQP(enc_chn_id, qp);

    return 0;
}

int sample_set_chann_min_qp(int chn_id, uint32_t qp)
{
    int enc_chn_id;

    if (chn_id >= MAX_CHN_NUM) {
        BL_LOGE("Invalid channel id\r\n");
        return -1;
    }

    enc_chn_id = chn[chn_id].enc_chn_id;
    MM_Encoder_SetChnMinQP(enc_chn_id, qp);

    return 0;
}

int sample_set_rc_level(int chn_id, uint32_t level)
{
    int ctrl_fps = 0;
    uint32_t init_fps = NULL;
    int dsp2_chn_id, enc_chn_id;
    MMDSP2FrmRate outFpsCfg;
    MMEncoderFrmRate fpsCfg;
    MMEncoderGOPSizeCfg gopSizeCfg;

    if (chn_id >= MAX_CHN_NUM) {
        BL_LOGE("Invalid channel id\r\n");
        return -1;
    }

    dsp2_chn_id = chn[chn_id].dsp2_chn_id;
    enc_chn_id = chn[chn_id].enc_chn_id;

    if (MM_Sensor_GetFPS(&init_fps) < 0) return -1;
    if (level == 0) {
        ctrl_fps = init_fps;
    } else if (level == 1) {
        ctrl_fps = (init_fps * 192) >> 8;//0.75 init_fps
    } else if (level == 2) {
        ctrl_fps = (init_fps * 128) >> 8;//0.5 init_fps
    } else if (level == 3) {
        ctrl_fps = (init_fps * 64) >> 8;//0.25 init_fps
    } else if (level == 4) {
        ctrl_fps = (init_fps * 25) >> 8;//0.1 init_fps
    } else if (level == 5) {
        ctrl_fps = 1;//1 fps
    } else return -1;

    outFpsCfg.frmRateNum = ctrl_fps;
    outFpsCfg.frmRateDen = 1;
    MM_DSP2_SetFrameSrcChnFPS(dsp2_chn_id, &outFpsCfg);

    fpsCfg.frmRateNum = ctrl_fps;
    fpsCfg.frmRateDen = 1;
    MM_Encoder_SetChnFrmRate(enc_chn_id, &fpsCfg);

    MM_Encoder_SetRcLevel(enc_chn_id, level);

    return 0;
}

int sample_get_rc_level(int chn_id, uint32_t *level)
{
    int enc_chn_id;

    if (chn_id >= MAX_CHN_NUM) {
        BL_LOGE("Invalid channel id\r\n");
        return -1;
    }

    enc_chn_id = chn[chn_id].enc_chn_id;
    MM_Encoder_GetRcLevel(enc_chn_id, level);

    return 0;
}

int sample_set_chann_quality_level(int chn_id, uint32_t qualityLvl)
{
    int enc_chn_id;
    MMEncoderRcAttr encRcAttr;

    if (chn_id >= MAX_CHN_NUM) {
        BL_LOGE("Invalid channel id\r\n");
        return -1;
    }

    enc_chn_id = chn[chn_id].enc_chn_id;

    MM_Encoder_GetChnRcAttr(enc_chn_id, &encRcAttr);
    if (ENC_RC_MODE_VBR != encRcAttr.rcMode) {
        BL_LOGE("Encoder channel is not configured as VBR. Can't set quality level\r\n");
        return -1;
    }

    encRcAttr.attrH264Vbr.qualityLvl = qualityLvl;
    MM_Encoder_SetChnRcAttr(enc_chn_id, &encRcAttr);

    return 0;
}

int sample_set_jpeg_quality(int chn_id, uint32_t quality)
{
    int enc_chn_id;
    MMEncoderAttr enc_attr;

    if (chn_id >= MAX_CHN_NUM) {
        BL_LOGE("Invalid channel id\r\n");
        return -1;
    }

    enc_chn_id = chn[chn_id].enc_chn_id;

    MM_Encoder_GetChnAttr(enc_chn_id, &enc_attr);

    if (ENC_TYPE_JPEG != enc_attr.encType) {
        BL_LOGE("Encoder channel is not JPEG. Can't set quality\r\n");
        return -1;
    }
    enc_attr.attrJpeg.quality = quality;
    MM_Encoder_SetChnAttr(enc_chn_id, &enc_attr);

    return 0;
}

int sample_get_jpeg_info(uint8_t *quality, uint16_t *width, uint16_t *height)
{
    int enc_chn_id;
    MMEncoderAttr enc_attr;
    if (NULL == chn) {
        *width = 1920;
        *height = 1080;
        *quality = 50;
        return -1;
    }
    enc_chn_id = chn[2].enc_chn_id;

    MM_Encoder_GetChnAttr(enc_chn_id, &enc_attr);

    if (ENC_TYPE_JPEG != enc_attr.encType) {
        BL_LOGE("Encoder channel is not JPEG.\r\n");
        return -1;
    }

    *width = (uint16_t)enc_attr.picWidth;
    *height = (uint16_t)enc_attr.picHeight;
    *quality = (uint8_t)enc_attr.attrJpeg.quality;
    return 0;
}

int sample_get_jpeg_pic(uint8_t **pic_ptr, uint32_t *len, int stream_id)
{
    int ret;
    MMEncoderStream stream_info = {0};
    if (NULL == chn) {
        ret = -1;
        goto exit;
    }
    if (0 != MM_Encoder_ResetStreamQueue(stream_id)) {
        ret = -1;
        goto exit;
    }
retry:
    ret = MM_Encoder_GetStream(stream_id, &stream_info);
    if (!ret) {
        if (stream_info.frame_sec_addr) {
            memset(&stream_info, 0, sizeof(MMEncoderStream));
            goto retry;
        }
        *pic_ptr = stream_info.frame_start_addr;
        *len = stream_info.frame_size;
    } else {
        printf("don't get jpeg\r\n");
    }
exit:
    return ret;
}

int sample_get_h264_frame(uint8_t **pic_ptr1, uint32_t *len1, uint8_t **pic_ptr2, uint32_t *len2,int stream_id)
{
    int ret;
    MMEncoderStream stream_info = {0};
    //MM_Encoder_ResetStreamQueue(stream_id);
    if (NULL == chn) {
        return -1;
    }

    ret = MM_Encoder_GetStream(stream_id, &stream_info);
    if (!ret) {
        if (stream_info.frame_sec_size) {
            *pic_ptr2 = stream_info.frame_sec_addr;
            *len2 = stream_info.frame_sec_size;
        }
        *pic_ptr1 = stream_info.frame_start_addr;
        *len1 = stream_info.frame_size;
    } else {
        printf("don't get h264\r\n");
    }
    return ret;
}

int sample_get_raw_pic(uint8_t **pic_ptr, uint32_t *len, int stream_id)
{
    MMDSP2YuvFrame yuv_frame;
    MM_DSP2_StartDumpPic(stream_id , PIX_FMT_DATA16, BL_IMAGE_DUMP_SRC_DSP2_INPUT);
    MM_DSP2_GetOnePicture(stream_id , &yuv_frame);
    MM_DSP2_StopRecvPic(stream_id);
    *pic_ptr = yuv_frame.frameStartAddr;
    *len = yuv_frame.frameSize;
    return 0;
}

int sample_start_yuv_pic(int stream_id)
{
    MM_DSP2_StartDumpPic(stream_id , PIX_FMT_DATA16, BL_IMAGE_DUMP_SRC_DSP2_OUTPUT);
    return 0;
}

int sample_get_yuv_pic(uint8_t **pic_ptr, uint32_t *len, int stream_id)
{
    int ret;
    MMDSP2YuvFrame yuv_frame;
    ret = MM_DSP2_GetOnePicture(stream_id , &yuv_frame);
    if (-2 == ret) {
        MM_DSP2_StartDumpPic(stream_id , PIX_FMT_DATA16, BL_IMAGE_DUMP_SRC_DSP2_OUTPUT);
        MM_DSP2_GetOnePicture(stream_id , &yuv_frame);
    } else if (ret == -1) {
        printf("get yuv frame fail\r\n");
        return -1;
    }
    MM_DSP2_StopRecvPic(stream_id);
    *pic_ptr = yuv_frame.frameStartAddr;
    *len = yuv_frame.frameSize;
    return 0;
}

int sample_start_stream(int chn_id)
{
	int ret;
    int dsp2_chn_id, enc_chn_id;
    MMDSP2FrmSrcAttr frmsrc_attr;

    if (chn_id >= MAX_CHN_NUM) {
        BL_LOGE("Invalid channel id\r\n");
        return -1;
    }

    dsp2_chn_id = chn[chn_id].dsp2_chn_id;
    enc_chn_id = chn[chn_id].enc_chn_id;

    /* Set frame source attribute for encoding */
    MM_DSP2_GetFrameSrcChnAttr(dsp2_chn_id, &frmsrc_attr);
    frmsrc_attr.pixFmt = PIX_FMT_NV12;
    MM_DSP2_SetFrameSrcChnAttr(dsp2_chn_id, &frmsrc_attr);

    MM_Encoder_SWModeConfig(enc_chn_id, ENC_SW_MODE_DISABLED, NULL);

    MM_System_Bind(dsp2_chn_id, enc_chn_id);

    ret = MM_Encoder_StartRecvPic(enc_chn_id);
    if (ret < 0) {
        return ret;
    }

    return 0;
}

int sample_start_stream_frame_mode(int chn_id)
{
	int ret;
    int dsp2_chn_id, enc_chn_id;
    MMDSP2FrmSrcAttr frmsrc_attr;

    if (chn_id >= MAX_CHN_NUM) {
        BL_LOGE("Invalid channel id\r\n");
        return -1;
    }

    dsp2_chn_id = chn[chn_id].dsp2_chn_id;
    enc_chn_id = chn[chn_id].enc_chn_id;

    /* Set frame source attribute for encoding */
    MM_DSP2_GetFrameSrcChnAttr(dsp2_chn_id, &frmsrc_attr);
    frmsrc_attr.pixFmt = PIX_FMT_NV12;
    MM_DSP2_SetFrameSrcChnAttr(dsp2_chn_id, &frmsrc_attr);

    MM_Encoder_SWModeConfig(enc_chn_id, ENC_SW_MODE_MANUAL, NULL);

    MM_System_Bind(dsp2_chn_id, enc_chn_id);

    ret = MM_Encoder_StartRecvPic(enc_chn_id);
    if (ret < 0) {
        return ret;
    }

    return 0;
}


int sample_start_stream_from_yuv_src(int chn_id, uint8_t *yuv_src_base_addr)
{
	int ret;
    int enc_chn_id;

    if (chn_id >= MAX_CHN_NUM) {
        BL_LOGE("Invalid channel id\r\n");
        return -1;
    }

    enc_chn_id = chn[chn_id].enc_chn_id;

    MM_Encoder_SWModeConfig(enc_chn_id, ENC_SW_MODE_AUTO, yuv_src_base_addr);

    ret = MM_Encoder_StartRecvPic(enc_chn_id);
    if (ret < 0) {
        return ret;
    }

    return 0;
}

int sample_close_stream(int chn_id)
{
    int dsp2_chn_id, enc_chn_id;

    if (chn_id >= MAX_CHN_NUM) {
        BL_LOGE("Invalid channel id\r\n");
        return -1;
    }

    dsp2_chn_id = chn[chn_id].dsp2_chn_id;
    enc_chn_id = chn[chn_id].enc_chn_id;

    MM_Encoder_Stop(enc_chn_id);

    /* make sure encoder idle status is reached before reclaiming resource and unbinding upstream HW */
    MM_Encoder_StopRecvPic(enc_chn_id);

    /* TODO: check if unbinding from upstream is necessary */
    MM_System_UnBind(dsp2_chn_id, enc_chn_id);

    return 0;
}

int h264_bittrue_init(void)
{
    int ret = 0;
    MMSensorAttr snsAttr = {1920, 1080, 15};

    ret = MM_Encoder_New(0);
    if (ret) {
        BL_LOGE("Encoder creat fail!!\r\n");
        return 1;
    }

    sample_common_init();
    sample_set_h264_main(&chn[CH0_ID], &snsAttr);

    return 0;
}

int h264_file_sink_init(void **file_sink)
{
    void *f_sink = NULL;
    save_file_config_t config = {0};

    if (!file_sink)
        return -1;

    config.file_path_name = "/sdcard/video";
    config.type = FILE_SINK_TYPE_VIDEO_H264;
    config.save_size = 1024*1024;
    f_sink = file_sink_new(&config);
    if (!f_sink) {
        BL_LOGE("File_sink new fail!!\r\n");
        return -1;
    }

    *file_sink = f_sink;

    return 0;
}

int h264_record(void *file_sink, MMEncoderStream *stream_info)
{
    int ret = -1;
    if (!file_sink || !stream_info)
        return -1;

    ret = file_sink_handle(file_sink, (void *)stream_info->frame_start_addr, stream_info->frame_size);
    if (ret) {
        return -1;
    }

    if (stream_info->frame_sec_size > 0) {
        ret = file_sink_handle(file_sink, (void *)(stream_info->frame_sec_addr), stream_info->frame_sec_size);
        if (ret){
            return -1;
        }
    }

    return 0;
}

void h264_stream_handle_task(void *param)
{
    int ret = -1;
    TaskHandle_t task_handle = NULL;
    void *file_sink = NULL;
    MMEncoderStream stream_info = {0};
    int stream_id;

    task_handle = xTaskGetCurrentTaskHandle();

    stream_id = (int)(param);
    if ((stream_id < 0) || (stream_id > 2)) {
        BL_LOGE("Stream id is illegal! input_id:%d\r\n", stream_id);
        vTaskDelete(task_handle);
    }

    ret = h264_file_sink_init(&file_sink);
    if (ret) {
        BL_LOGE("File_sink init fail!!\r\n");
        vTaskDelete(task_handle);
    }

    /* Get video buffer and save data into sdcard */
    while (1) {
        ret = MM_Encoder_GetStream(stream_id, &stream_info);
        if (!ret) {
            ret = h264_record(file_sink, &stream_info);
            MM_Encoder_H264_Frame_Done(stream_id, &stream_info);
            if (ret) {
                BL_LOGI("Save data into sd over!!\r\n");
                break;
            }
        } else {
           BL_LOGE("Get video stream fail!!\r\n");
        }
    }

    /* Destroy file sink */
    file_sink_destroy(file_sink);

    /* Close stream */
    sample_close_stream(stream_id);

    vTaskDelete(task_handle);
}

int jpeg_file_sink_init(void **file_sink)
{
    void *f_sink = NULL;
    save_file_config_t config = {0};

    if (!file_sink)
        return -1;

    config.file_path_name = "/sdcard/jpeg";
    config.type = FILE_SINK_TYPE_VIDEO_MJPEG;
    config.file_save_cnt = 5;
    f_sink = file_sink_new(&config);
    if (!f_sink) {
        BL_LOGE("File_sink new fail!!\r\n");
        return -1;
    }

    *file_sink = f_sink;

    return 0;
}

int jpeg_record(void *file_sink, MMEncoderStream *stream_info)
{
    int ret = -1;
#if (!MJPG_AUTO_HEADER)
    uint8_t *buf_addr;
    uint32_t buf_size;
#endif

    if (!file_sink || !stream_info)
        return -1;

#if (!MJPG_AUTO_HEADER)
    /* Write jpeg header data */
    bl_venc_get_JFIF_header(&buf_addr, &buf_size);
    ret = file_sink_handle(file_sink, (void *)buf_addr, buf_size);
    if (ret) {
        return -1;
    }
#endif

    /* Write jpeg payload */
    ret = file_sink_handle(file_sink, (void *)stream_info->frame_start_addr, stream_info->frame_size);
    if (ret) {
        return -1;
    }
    if (stream_info->frame_sec_size > 0) {
        ret = file_sink_handle(file_sink, (void *)(stream_info->frame_sec_addr), stream_info->frame_sec_size);
        if (ret){
            return -1;
        }
    }

#if (!MJPG_AUTO_HEADER)
    /* Write jpeg tail data */
    bl_venc_get_JFIF_tail(&buf_addr, &buf_size);
    ret = file_sink_handle(file_sink, (void *)buf_addr, buf_size);
    if (ret) {
        return -1;
    }
#endif

    ret = file_save_all_data(file_sink);
    if (ret) {
        return -1;
    }

    return 0;
}

void jpeg_record_in_ddr(MMEncoderStream *stream_info)
{
    static int cnt = 0;
    void *addr = NULL;
    int size = 0;

    if (!stream_info) {
       BL_LOGE("Param is error! %s line:%d\r\n", __func__, __LINE__);
       return;
    }

    if (cnt > 5) {
        BL_LOGI("5 frame get over!!!!!\r\n");
        return;
    }

    cnt++;

    size = stream_info->frame_size + stream_info->frame_sec_size;
    addr = pvPortMalloc(MEMCPY_ALIGN(size, 4));
    if (!addr) {
        BL_LOGE("Malloc fail!! %s line:%d\r\n", __func__, __LINE__);
        return;
    }

    memcpy(addr, stream_info->frame_start_addr, MEMCPY_ALIGN(stream_info->frame_size, 4));
    if (stream_info->frame_sec_size) {
        BL_LOGI("%s line:%d sec_size:0x%x\r\n", __func__, __LINE__, stream_info->frame_sec_size);
        memcpy(addr + stream_info->frame_size, stream_info->frame_sec_addr, MEMCPY_ALIGN(stream_info->frame_sec_size, 4));
    }

    BL_LOGI("%d frame have been saved, addr:0x%p size:0x%x\r\n", cnt, addr, MEMCPY_ALIGN(size, 4));
}

void jpeg_stream_handle_jlink_dump_task(void *param)
{
    int ret = -1;
    TaskHandle_t task_handle = NULL;
    MMEncoderStream stream_info = {0};
    int stream_id;

    task_handle = xTaskGetCurrentTaskHandle();

    stream_id = (int)(param);
    if (stream_id != 2) {
        BL_LOGE("Jpeg stream id is illegal! input_id:%d\r\n", stream_id);
        vTaskDelete(task_handle);
    }


    /* Get video buffer and save data into ddr */
    while (1) {
        ret = MM_Encoder_GetStream(stream_id, &stream_info);
        if (!ret) {
            jpeg_record_in_ddr(&stream_info);
        } else {
           BL_LOGE("Get video stream fail!!\r\n");
        }
    }

    vTaskDelete(task_handle);
}

void jpeg_stream_handle_task(void *param)
{
    int ret = -1;
    TaskHandle_t task_handle = NULL;
    void *file_sink = NULL;
    MMEncoderStream stream_info = {0};
    int stream_id;

    task_handle = xTaskGetCurrentTaskHandle();

    stream_id = (int)(param);
    if (stream_id != 2) {
        BL_LOGE("Jpeg stream id is illegal! input_id:%d\r\n", stream_id);
        vTaskDelete(task_handle);
    }

    ret = jpeg_file_sink_init(&file_sink);
    if (ret) {
        BL_LOGE("File_sink init fail!!\r\n");
        vTaskDelete(task_handle);
    }

    /* Get video buffer and save data into sdcard */
    while (1) {
        ret = MM_Encoder_GetStream(stream_id, &stream_info);
        if (!ret) {
            ret = jpeg_record(file_sink, &stream_info);
            if (ret) {
                BL_LOGI("Save data into sd over!!\r\n");
                break;
            }
        } else {
           BL_LOGE("Get video stream fail!!\r\n");
        }
    }

    /* Destroy file sink */
    file_sink_destroy(file_sink);

    /* Close stream */
    sample_close_stream(stream_id);

    vTaskDelete(task_handle);
}

int h264_handle_data(int stream_id)
{
    int ret = -1;
    void *file_sink = NULL;
    MMEncoderStream stream_info = {0};
    long long start_timer = 0, end_timer = 0;
    uint32_t frame_cnt = 0;

    if(stream_id < 0 || stream_id > 2) {
        BL_LOGE("Stream id is illegal!! input stream_id:%d\r\n", stream_id);
        return -1;
    }

    ret = h264_file_sink_init(&file_sink);
    if (ret) {
        BL_LOGE("File_sink init fail!!\r\n");
        return -1;
    }

    start_timer = aos_now_ms();

    /* Get video buffer and save data into sdcard */
    while (1) {
        ret = MM_Encoder_GetStream(stream_id, &stream_info);
        if (!ret) {
            frame_cnt++;
            ret = h264_record(file_sink, &stream_info);
            if (ret) {
                BL_LOGI("Save data into sd over!!\r\n");
                break;
            }
        } else {
           BL_LOGE("Get video stream fail!!\r\n");
        }
    }

    end_timer = aos_now_ms();
    BL_LOGI("[SAMPLE]Statics fps:%d\r\n", (int)(frame_cnt/((end_timer - start_timer) / 1000)));

    file_sink_destroy(file_sink);

    return 0;
}

void h264_change_resolution_task(void *param)
{
    int ret = -1;
    TaskHandle_t task_handle = NULL;
    int stream_id;

    task_handle = xTaskGetCurrentTaskHandle();

    stream_id = (int)(param);
    if ((stream_id < 0) || (stream_id > 2)) {
        BL_LOGE("Stream id is illegal! input_id:%d\r\n", stream_id);
        vTaskDelete(task_handle);
    }

    ret = h264_handle_data(stream_id);
    if (ret) {
        BL_LOGE("h264 handle data fail!!\r\n");
        vTaskDelete(task_handle);
    }

    /* Close stream */
    sample_close_stream(stream_id);

    /* Change resolution */
    uint32_t width = 640;
    uint32_t height = 480;
    ret = sample_set_chann_resolution(stream_id, width, height);
    if (ret) {
        BL_LOGE("Set resolution fail!!\r\n");
        return;
    }
    BL_LOGI("Resolution width:%d height:%d\r\n", width, height);

    /* Start stream */
    sample_start_stream(stream_id);

    ret = h264_handle_data(stream_id);
    if (ret) {
        BL_LOGE("h264 handle data fail!!\r\n");
        vTaskDelete(task_handle);
    }

    /* Close stream */
    sample_close_stream(stream_id);

    vTaskDelete(task_handle);
}

int h264_statistics_handle(int stream_id, int frame_per_time, int static_times)
{
    int ret = -1;
    MMEncoderStream stream_info = {0};
    long long start_timer = 0, end_timer = 0;
    uint32_t frame_cnt = 0, recv_size = 0, interval, index = 0;

    if(stream_id < 0 || stream_id > 2) {
        BL_LOGE("Stream id is illegal!! input stream_id:%d\r\n", stream_id);
        return -1;
    }

    for (index = 0; index < static_times; index++) {
        /* Statistics */
        start_timer = aos_now_ms();
        frame_cnt = 0;
        recv_size = 0;
        while (1) {
            ret = MM_Encoder_GetStream(stream_id, &stream_info);
            if (!ret) {
                frame_cnt++;
                //BL_LOGI("frame_cnt:%d\r\n", frame_cnt);
                recv_size += stream_info.frame_size + stream_info.frame_sec_size;
                /* Satistics 90 frame */
                if (frame_per_time == frame_cnt) {
                    break;
                }
            } else {
               BL_LOGE("Get video stream fail!!\r\n");
            }
        }

        end_timer = aos_now_ms();
        interval = (end_timer - start_timer) / 1000;
        BL_LOGI("[SAMPLE]Statics fps:%d bitrate:%d(bps)\r\n",
                (int)(frame_cnt / interval),
                (int)((recv_size * 8) / interval));
    }

    return 0;
}

void h264_change_fps_task(void *param)
{
    int ret = -1;
    TaskHandle_t task_handle = NULL;
    int stream_id;
    uint32_t fps = 0;
    int statics_times = 0, frame_per_time = 0;

    task_handle = xTaskGetCurrentTaskHandle();

    stream_id = (int)(param);
    if ((stream_id < 0) || (stream_id > 2)) {
        BL_LOGE("Stream id is illegal! input_id:%d\r\n", stream_id);
        vTaskDelete(task_handle);
    }

    /* Handle data */
    frame_per_time = 50;
    statics_times = 3;
    ret = h264_statistics_handle(stream_id, frame_per_time, statics_times);
    if (ret) {
        BL_LOGE("h264 handle data fail!!\r\n");
        vTaskDelete(task_handle);
    }

    /* Stop stream */
    //After codec handle last frame over, call sample_close_stream to release resourece
    vTaskDelay(1000);
    sample_close_stream(stream_id);

    /* Change fps */
    fps = 4;
    ret = sample_set_chann_frame_rate(stream_id, fps);
    if (ret) {
        BL_LOGE("Set fps fail!!\r\n");
        return;
    }
    BL_LOGI("[Sample]Change fps:%d\r\n", fps);

    /* Start stream */
    sample_start_stream(stream_id);

    ret = h264_statistics_handle(stream_id, frame_per_time, statics_times);
    if (ret) {
        BL_LOGE("h264 handle data fail!!\r\n");
        vTaskDelete(task_handle);
    }

    /* Change fps dynamiclly */
    fps = 2;
    ret = sample_set_chann_frame_rate(stream_id, fps);
    if (ret) {
        BL_LOGE("Set fps fail!!\r\n");
        return;
    }
    BL_LOGI("[Sample]Change fps dynamiclly, fps:%d\r\n", fps);

    ret = h264_statistics_handle(stream_id, frame_per_time, statics_times);
    if (ret) {
        BL_LOGE("h264 handle data fail!!\r\n");
        vTaskDelete(task_handle);
    }

    /* Close stream */
    vTaskDelay(1000);
    sample_close_stream(stream_id);

    vTaskDelete(task_handle);
}

void h264_change_bitrate_task(void *param)
{
    int ret = -1;
    TaskHandle_t task_handle = NULL;
    int stream_id;
    uint32_t bitrate = 0;
    int statics_times = 0, frame_per_time = 0;

    task_handle = xTaskGetCurrentTaskHandle();

    stream_id = (int)(param);
    if ((stream_id < 0) || (stream_id > 2)) {
        BL_LOGE("Stream id is illegal! input_id:%d\r\n", stream_id);
        vTaskDelete(task_handle);
    }

    /* Statistics handle */
    frame_per_time = 50;
    statics_times = 3;
    ret = h264_statistics_handle(stream_id, frame_per_time, statics_times);
    if (ret) {
        BL_LOGE("h264 handle data fail!!\r\n");
        vTaskDelete(task_handle);
    }

    /* Change bitrate dynamically */
    bitrate = 2000000;
    ret = sample_set_chann_bit_rate(stream_id, bitrate);
    if (ret) {
        BL_LOGE("Set bitrate fail!!\r\n");
        vTaskDelete(task_handle);
    }
    BL_LOGI("[Sample]Change bitrate:%d\r\n", bitrate);

    /* Statistics handle */
    ret = h264_statistics_handle(stream_id, frame_per_time, statics_times);
    if (ret) {
        BL_LOGE("h264 handle data fail!!\r\n");
        vTaskDelete(task_handle);
    }

    /* Close stream */
    vTaskDelay(1000);
    sample_close_stream(stream_id);

    vTaskDelete(task_handle);
}
