/*
 * Copyright (c) 2020 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <string.h>
#include <venc_framework.h>

#include "bl_venc.h"

//#define TEST_ROI
//#define TEST_ROI_RUNNING
//#define TEST_QTABLE

#define SET_VENC_STATE(venc, state)     ((venc)->enc_state = state)
#define GET_VENC_STATE(venc)            ((venc)->enc_state)
#define GET_FRAMERATE_NUM(fps)          (fps >> 16)
#define GET_FRAMERATE_DEN(fps)          (fps & 0xFFFF)

#define H264_3DNR_DEFAULT_LEVEL         1
#define H264_3DNR_DEFAULT_STRENGTH      15

typedef enum {
    VENC_UNCFG = 0,
    VENC_IDLE = 1,
    VENC_BUSY = 2,
} VENC_STATE_T;

typedef struct venc {
    VENC_FRAMEWORK_CODEC_TYPE_T codec_type;
    venc_framework_alloc_cb alloc_cb;
    venc_framework_free_cb free_cb;
    venc_framework_recv_cb recv_cb;
    venc_framework_stop_cb stop_cb;
    uint8_t *y_frame_base_addr;
    uint32_t y_frame_size; 
    uint8_t *uv_frame_base_addr;
    uint32_t uv_frame_size;
    uint32_t width;
    uint32_t height;
    uint32_t device_id;
    uint32_t dsp2_chann_id;
    int video_param[VIDEO_FORMAT_KEY_NUM];
    int video_param_range[VIDEO_FORMAT_KEY_NUM][2];
    VENC_STATE_T enc_state;
    int stream_id;  /* app level data */
    bool session_started;
    bool sw_mode;
} venc_t;


// Get handle to h264enc from device priv data
#define DEV_TO_VENC(dev)     ((venc_t*)(dev->priv))
#define DEV_TO_CHANN_ID(dev)    (DEV_TO_VENC(dev)->device_id)

static int h264_video_param_range[VIDEO_FORMAT_KEY_NUM][2] = {
    [VIDEO_FORMAT_KEY_LOW_POWER_MODE]   = { 0,      1,          },
    [VIDEO_FORMAT_KEY_BITRATE_MODE]     = { 0,      2,          },
    [VIDEO_FORMAT_KEY_BIT_RATE]         = { 1000,   10000000,   },
    [VIDEO_FORMAT_KEY_FRAME_RATE]       = { 1,      (60 << 16), },
    [VIDEO_FORMAT_KEY_GOP_SIZE]         = { 1,      300,        },
    [VIDEO_FORMAT_KEY_TARGET_I_QP]      = { 1,      51,         },
    [VIDEO_FORMAT_KEY_TARGET_P_QP]      = { 1,      51,         },
    [VIDEO_FORMAT_KEY_INIT_QP]        = { 1,      51,         },
    [VIDEO_FORMAT_KEY_MIN_QP]         = { 1,      51,         },
    [VIDEO_FORMAT_KEY_MAX_QP]         = { 1,      51,         },
    [VIDEO_FORMAT_KEY_FORCE_IP_RATIO]   = { 1,      100,        },
    [VIDEO_FORMAT_KEY_PROFILE]          = { 0,      1,          },
    [VIDEO_FORMAT_KEY_QUALITY]          = { 1,      1000,       },
};

static int venc_alloc_cb(void *usrdata, size_t size, int is_high_usage, void **ptr_mem)
{
    //FIXME critical section protect
    venc_framework_device_t *device = (venc_framework_device_t*)usrdata;
    venc_framework_alloc_cb alloc_cb;
    venc_buf_t buf;

    alloc_cb = DEV_TO_VENC(device)->alloc_cb;
    if (alloc_cb) {
        alloc_cb(device, size, is_high_usage, &buf);
        if (buf.len < size) {
            BL_LOGE("venc_alloc_cb: alloc failed\r\n");
            return -1;
        }
        *ptr_mem = (void*)buf.base;
    }
    return 0;
}

static int venc_free_cb(void *usrdata, void *ptr_mem)
{
    //FIXME critical section protect
    venc_framework_device_t *device = (venc_framework_device_t*)usrdata;
    venc_framework_free_cb free_cb;

    free_cb = DEV_TO_VENC(device)->free_cb;
    if (free_cb) {
        free_cb(device, ptr_mem);
    }
    return 0;
}

static int venc_frame_cb(void *usrdata, venc_frame_desc_t *frame_desc, int is_overflow)
{
    //FIXME critical section protect
    venc_framework_device_t *device = (venc_framework_device_t*)usrdata;
    venc_t *venc = DEV_TO_VENC(device);
    venc_framework_recv_cb recv_cb;
    venc_result_t result;

    recv_cb = DEV_TO_VENC(device)->recv_cb;
    if (recv_cb) {
        if (venc->codec_type == VENC_FRAMEWORK_CODEC_TYPE_JPEG) {
            result.frame_type = VENC_FRAMEWORK_JPEG_FRAME;
        } else {
#if (BL80X_HW_VER <= BL80X_HW_A0)
            result.frame_type = (frame_desc->frame_id % venc->video_param[VIDEO_FORMAT_KEY_GOP_SIZE]) ?
                VENC_FRAMEWORK_H264_P_FRAME : VENC_FRAMEWORK_H264_I_FRAME;
#else
            result.frame_type = (frame_desc->frame_type == BL_H264_P_FRAME) ? 
                VENC_FRAMEWORK_H264_P_FRAME : VENC_FRAMEWORK_H264_I_FRAME;
#endif
        }

        result.stream_id = venc->stream_id;
        result.frame_id = frame_desc->frame_id;
        result.frame_start_addr = frame_desc->frame_start_addr;
        result.frame_size = frame_desc->frame_size;
        result.frame_sec_addr = frame_desc->frame_sec_half_start_addr;
        result.frame_sec_size = frame_desc->frame_sec_half_size;
        recv_cb(device, &result);

#ifdef TEST_ROI_RUNNING
extern int test_roi_running_main(int stream_id, int frame_cnt);
        BL_LOGI("TEST ROI id:%d\r\n", result.frame_id);
        test_roi_running_main(result.stream_id, result.frame_id);
#endif

#ifdef TEST_QTABLE
extern int test_Mjpeg_qtable_main();
        test_Mjpeg_qtable_main();
#endif

        if (venc->sw_mode) {
            /* in sw mode, encoder automatically goes to idle after each frame done and should be restarted */
            SET_VENC_STATE(venc, VENC_IDLE);
        }
    }

    return 0;
}

static int venc_stop_cb(void *usrdata, int stream_id)
{
    venc_framework_device_t *device = (venc_framework_device_t*)usrdata;
    venc_t *venc = DEV_TO_VENC(device);

    if (venc->stop_cb) {
        venc->stop_cb(device, stream_id);
        venc->stop_cb = NULL;
    }

    return 0;
}

static int do_venc_start(venc_framework_device_t *device, int stream_id, bool sw_mode)
{
    bl_venc_input_buffer_t input_buffer;
    int ret = 0;

    venc_t *venc = DEV_TO_VENC(device);
    int device_id = DEV_TO_CHANN_ID(device);

    if (GET_VENC_STATE(venc) != VENC_IDLE) {
        return -1;
    }

    venc->stream_id = stream_id;
    if (venc->alloc_cb && venc->free_cb && venc->recv_cb) {
        bl_venc_set_callback(device_id, venc_alloc_cb, venc_free_cb, venc_frame_cb, device);
    }
    input_buffer.y_frame_base_addr = venc->y_frame_base_addr;
    input_buffer.y_frame_size = venc->y_frame_size;
    input_buffer.uv_frame_base_addr = venc->uv_frame_base_addr;
    input_buffer.uv_frame_size = venc->uv_frame_size;

    if (VENC_FRAMEWORK_CODEC_TYPE_H264 == venc->codec_type) {
        bl_venc_set_h264_sw_mode(device_id, sw_mode ? ENABLE : DISABLE);
        /* Config SramckMode */
#if (H264_ENABLE_SRAMCK_OLD)
        bl_venc_set_h264_sramck_old(ENABLE);
#else
        bl_venc_set_h264_sramck_old(DISABLE);
#endif
        /* initialize resource only at session start */ 
        if (!venc->session_started) {
            if (!sw_mode) {
                bl_venc_set_h264_input_channel(device_id, venc->dsp2_chann_id);
            }
            bl_venc_set_h264_internal_buffer(device_id);
            bl_venc_start_h264_enc_session(device_id);
            venc->session_started = true;
            venc->sw_mode = sw_mode;
        }

        bl_venc_set_h264_input_buffer(device_id, &input_buffer);
        bl_venc_sync_buffer(stream_id);
#ifdef TEST_ROI
extern int test_roi_main(int stream_id);
        if(test_roi_main(stream_id)) {
            BL_LOGE("Roi test handle fail!! %s line:%d\r\n", __func__, __LINE__);
            return 1;
        }
#endif

#ifdef ENABLE_3DNR_H264
        ret = bl_venc_set_3dnr(device_id, H264_3DNR_DEFAULT_LEVEL, H264_3DNR_DEFAULT_STRENGTH);
        if (ret) {
            BL_LOGE("Set 3DNR fail!! %s line:%d\r\n", __func__, __LINE__);
            return 1;
        }
#endif

        bl_venc_start_h264_enc(device_id);
    } else if (VENC_FRAMEWORK_CODEC_TYPE_JPEG == venc->codec_type) {
        bl_venc_set_jpeg_input_channel(device_id, venc->dsp2_chann_id);
        bl_venc_start_jpeg_enc(device_id, &input_buffer);
    }

    SET_VENC_STATE(venc, VENC_BUSY);

    return 0;
}

static int bl808_venc_init(venc_framework_device_t *device)
{
    venc_t *venc = DEV_TO_VENC(device);
    SET_VENC_STATE(venc, VENC_UNCFG);

    bl_venc_init();

    return 0;
}

static int bl808_venc_bind_to_dsp2_channel(venc_framework_device_t *device, int chann_id)
{
    venc_t *venc = DEV_TO_VENC(device);
    venc->dsp2_chann_id = chann_id;

    return 0;
}

static int bl808_venc_set_input_y_buffer(venc_framework_device_t *device,
                                        uint8_t *y_frame_base_addr,
                                        uint32_t y_frame_size)
{
    DEV_TO_VENC(device)->y_frame_base_addr = y_frame_base_addr;
    DEV_TO_VENC(device)->y_frame_size = y_frame_size;

    return 0;
}
                                        
static int bl808_venc_set_input_uv_buffer(venc_framework_device_t *device,
                                        uint8_t *uv_frame_base_addr,
                                        uint32_t uv_frame_size)
{
    DEV_TO_VENC(device)->uv_frame_base_addr = uv_frame_base_addr;
    DEV_TO_VENC(device)->uv_frame_size = uv_frame_size;

    return 0;
}

static int bl808_venc_set_resolution(venc_framework_device_t *device,
    uint32_t width, uint32_t height)
{
    venc_t *venc = DEV_TO_VENC(device);
    venc->width = width;
    venc->height = height;

    return 0;
}
    
static int bl808_venc_get_resolution(venc_framework_device_t *device,
    uint32_t *width, uint32_t *height)
{
    venc_t *venc = DEV_TO_VENC(device);
    *width = venc->width;
    *height = venc->height;

    return 0;
}

static void bl808_venc_get_h264_config(venc_t *venc, bl_h264_config_t *h264_cfg)
{
    if (1 == venc->video_param[VIDEO_FORMAT_KEY_LOW_POWER_MODE]) {
        h264_cfg->enc_type = BL_H264_ENC_LOW_BANDW;
    } else {
        h264_cfg->enc_type = BL_H264_ENC_NORMAL;
    }

    if (VENC_FRAMEWORK_H264_RC_CBR == venc->video_param[VIDEO_FORMAT_KEY_BITRATE_MODE]) {
        h264_cfg->bitrate_mode = BL_BITRATE_MODE_CBR;
    } else if (VENC_FRAMEWORK_H264_RC_VBR == venc->video_param[VIDEO_FORMAT_KEY_BITRATE_MODE]) {
        h264_cfg->bitrate_mode = BL_BITRATE_MODE_VBR;
    } else {
        h264_cfg->bitrate_mode = BL_BITRATE_MODE_FIXQP;
    }

    h264_cfg->width = venc->width;
    h264_cfg->height = venc->height;
    h264_cfg->enc_type = venc->video_param[VIDEO_FORMAT_KEY_LOW_POWER_MODE];
    h264_cfg->bit_rate = venc->video_param[VIDEO_FORMAT_KEY_BIT_RATE];
    h264_cfg->frame_rate_num = GET_FRAMERATE_NUM(venc->video_param[VIDEO_FORMAT_KEY_FRAME_RATE]);
    h264_cfg->frame_rate_den = GET_FRAMERATE_DEN(venc->video_param[VIDEO_FORMAT_KEY_FRAME_RATE]);
    h264_cfg->gop_size = venc->video_param[VIDEO_FORMAT_KEY_GOP_SIZE];
    h264_cfg->target_i_qp = venc->video_param[VIDEO_FORMAT_KEY_TARGET_I_QP];
    h264_cfg->target_p_qp = venc->video_param[VIDEO_FORMAT_KEY_TARGET_P_QP];
    h264_cfg->init_qp = venc->video_param[VIDEO_FORMAT_KEY_INIT_QP];
    h264_cfg->min_qp = venc->video_param[VIDEO_FORMAT_KEY_MIN_QP];
    h264_cfg->max_qp = venc->video_param[VIDEO_FORMAT_KEY_MAX_QP];
    h264_cfg->force_ip_ratio = venc->video_param[VIDEO_FORMAT_KEY_FORCE_IP_RATIO];
    h264_cfg->profile = venc->video_param[VIDEO_FORMAT_KEY_PROFILE];
}

static int bl808_venc_set_video_param(venc_framework_device_t *device,
    VENC_FRAMEWORK_VIDEO_FORMAT_KEY_T key, int value)
{
    venc_t *venc = DEV_TO_VENC(device);
    int device_id = DEV_TO_CHANN_ID(device);

    if (value < h264_video_param_range[key][0] || value > h264_video_param_range[key][1]) {
        return -1;
    }

    /* apply dynamic configuration if encoder is busy */
    if (GET_VENC_STATE(venc) == VENC_BUSY) {
        if (key == VIDEO_FORMAT_KEY_FRAME_RATE) {
            bl_venc_set_h264_FPS_on_the_fly(device_id, GET_FRAMERATE_NUM(value), GET_FRAMERATE_DEN(value));
        } else if (key == VIDEO_FORMAT_KEY_BIT_RATE) {
            bl_h264_config_t h264_cfg;
            bl808_venc_get_h264_config(venc, &h264_cfg);
            h264_cfg.bit_rate = value;
            bl_venc_set_h264_bitrate_on_the_fly(device_id, &h264_cfg);
        } else if (key == VIDEO_FORMAT_KEY_GOP_SIZE) {
            /* change cbr bitrate based on old bitrate value */
            bl_venc_set_h264_gop_size_on_the_fly(device_id, value);
        } else if (key == VIDEO_FORMAT_KEY_TARGET_I_QP) {
            bl_venc_set_h264_target_i_qp_on_the_fly(device_id, value);
        } else if (key == VIDEO_FORMAT_KEY_TARGET_P_QP) {
            bl_venc_set_h264_target_p_qp_on_the_fly(device_id, value);
        } else if (key == VIDEO_FORMAT_KEY_MAX_QP) {
            bl_venc_set_h264_max_qp_on_the_fly(device_id, value);
        } else if (key == VIDEO_FORMAT_KEY_MIN_QP) {
            bl_venc_set_h264_min_qp_on_the_fly(device_id, value);
        }
    }

    if (VIDEO_FORMAT_KEY_PROFILE == key) {
        /* Set profile */
        bl_venc_set_h264_profile(device_id, value);
    }

    /* save the new value */
    venc->video_param[key] = value;

    return 0;
}

static int bl808_venc_get_video_param(venc_framework_device_t *device,
    VENC_FRAMEWORK_VIDEO_FORMAT_KEY_T key, int *value)
{
    venc_t *venc = DEV_TO_VENC(device);
    *value = venc->video_param[key];

    return 0;
}

static int bl808_venc_set_h264_config(venc_framework_device_t *device)
{
    bl_h264_config_t h264_cfg;
    venc_t *venc = DEV_TO_VENC(device);
    int device_id = DEV_TO_CHANN_ID(device);

    if (GET_VENC_STATE(venc) == VENC_BUSY) {
        return -1;
    }

    bl808_venc_get_h264_config(venc, &h264_cfg);

    bl_venc_set_h264_config(device_id, &h264_cfg);

    SET_VENC_STATE(venc, VENC_IDLE);

    return 0;
}

static int bl808_venc_set_jpeg_config(venc_framework_device_t *device)
{
    bl_jpeg_config_t config;
    venc_t *venc = DEV_TO_VENC(device);
    int device_id = DEV_TO_CHANN_ID(device);

    if (GET_VENC_STATE(venc) == VENC_BUSY) {
        return -1;
    }

    config.width = venc->width;
    config.height = venc->height;
    config.quality = venc->video_param[VIDEO_FORMAT_KEY_QUALITY];

    bl_venc_set_jpeg_config(device_id, &config);

    SET_VENC_STATE(venc, VENC_IDLE);

    return 0;
}

static int bl808_venc_set_callback(venc_framework_device_t *device,
                                        venc_framework_alloc_cb alloc_cb,
                                        venc_framework_free_cb free_cb,
                                        venc_framework_recv_cb recv_cb)
{
    DEV_TO_VENC(device)->alloc_cb = alloc_cb;
    DEV_TO_VENC(device)->free_cb = free_cb;
    DEV_TO_VENC(device)->recv_cb = recv_cb;

    return 0;
}

static int bl808_venc_encode_frame(venc_framework_device_t *device, int stream_id)
{
    return do_venc_start(device, stream_id, true);
}

static int bl808_venc_start(venc_framework_device_t *device, int stream_id)
{
    return do_venc_start(device, stream_id, false);
}

static int bl808_venc_stop_h264(venc_framework_device_t *device, venc_framework_stop_cb cb)
{
    venc_t *venc = DEV_TO_VENC(device);
    int device_id = DEV_TO_CHANN_ID(device);
    venc->stop_cb = cb;

    if (venc->sw_mode) {
        /* In SW mode, do nothing but end the session */
        bl_venc_stop_h264_enc_session(device_id);
    } else {
        if (GET_VENC_STATE(venc) != VENC_BUSY) {
            return -1;
        }
        bl_venc_stop_h264_enc(device_id, venc_stop_cb);
#if (BL80X_HW_VER <= BL80X_HW_A0)
        bl_venc_stop_h264_enc_session(device_id);
#endif
    }

    venc->session_started = false;
    SET_VENC_STATE(venc, VENC_IDLE);

    return 0;
}

static int bl808_venc_stop_recv_pic(venc_framework_device_t *device)
{
    venc_t *venc = DEV_TO_VENC(device);
    int device_id = DEV_TO_CHANN_ID(device);

    if (GET_VENC_STATE(venc) == VENC_IDLE) {
        if (VENC_FRAMEWORK_CODEC_TYPE_H264 == venc->codec_type) {
            bl_venc_stop_recv_h264_pic(device_id);
        } else if (VENC_FRAMEWORK_CODEC_TYPE_JPEG == venc->codec_type) {
            bl_venc_stop_recv_jpeg_pic(device_id);
        }
        bl_venc_set_callback(venc->device_id, NULL, NULL, NULL, device);
    }

    return 0;
}

static int bl808_venc_stop_jpeg(venc_framework_device_t *device, venc_framework_stop_cb cb)
{
    venc_t *venc = DEV_TO_VENC(device);
    int device_id = DEV_TO_CHANN_ID(device);

    if (GET_VENC_STATE(venc) != VENC_BUSY) {
        return -1;
    }

    venc->stop_cb = cb;

    bl_venc_stop_jpeg_enc(device_id, venc_stop_cb);

    SET_VENC_STATE(venc, VENC_IDLE);

    return 0;
}

static VENC_FRAMEWORK_CODEC_TYPE_T bl808_venc_get_codec_type(venc_framework_device_t *device)
{
    venc_t *venc = DEV_TO_VENC(device);
    return venc->codec_type;
}

static bool bl808_venc_is_busy(venc_framework_device_t *device)
{
    venc_t *venc = DEV_TO_VENC(device);

    return (VENC_BUSY == venc->enc_state);
}

static venc_t h264_enc_main = {
    .device_id = 0,
    .codec_type = VENC_FRAMEWORK_CODEC_TYPE_H264,
};

static venc_t h264_enc_sub = {
    .device_id = 1,
    .codec_type = VENC_FRAMEWORK_CODEC_TYPE_H264,
};

static venc_t jpeg_enc = {
    .device_id = 2,
    .codec_type = VENC_FRAMEWORK_CODEC_TYPE_JPEG,
};

venc_framework_device_t h264enc_main_dev = {
    .name = "bl808_h264enc_main",
    .init = bl808_venc_init,
    .bind_to_dsp2_channel = bl808_venc_bind_to_dsp2_channel,
    .set_input_y_buffer = bl808_venc_set_input_y_buffer,
    .set_input_uv_buffer = bl808_venc_set_input_uv_buffer,
    .set_callback = bl808_venc_set_callback,
    .set_resolution = bl808_venc_set_resolution,
    .get_resolution = bl808_venc_get_resolution,
    .set_video_param = bl808_venc_set_video_param,
    .get_video_param = bl808_venc_get_video_param,
    .config = bl808_venc_set_h264_config,
    .start = bl808_venc_start,
    .stop = bl808_venc_stop_h264,
    .stop_recv_pic = bl808_venc_stop_recv_pic,
    .encode_frame = bl808_venc_encode_frame,
    .get_codec_type = bl808_venc_get_codec_type,
    .is_busy = bl808_venc_is_busy,
    .priv = &h264_enc_main,
};

venc_framework_device_t h264enc_sub_dev = {
    .name = "bl808_h264enc_sub",
    .init = bl808_venc_init,
    .bind_to_dsp2_channel = bl808_venc_bind_to_dsp2_channel,
    .set_input_y_buffer = bl808_venc_set_input_y_buffer,
    .set_input_uv_buffer = bl808_venc_set_input_uv_buffer,
    .set_callback = bl808_venc_set_callback,
    .set_resolution = bl808_venc_set_resolution,
    .get_resolution = bl808_venc_get_resolution,
    .set_video_param = bl808_venc_set_video_param,
    .get_video_param = bl808_venc_get_video_param,
    .config = bl808_venc_set_h264_config,
    .start = bl808_venc_start,
    .stop = bl808_venc_stop_h264,
    .stop_recv_pic = bl808_venc_stop_recv_pic,
    .encode_frame = bl808_venc_encode_frame,
    .get_codec_type = bl808_venc_get_codec_type,
    .is_busy = bl808_venc_is_busy,
    .priv = &h264_enc_sub,
};

venc_framework_device_t jpeg_enc_dev = {
    .name = "bl808_jpeg_enc",
    .init = bl808_venc_init,
    .bind_to_dsp2_channel = bl808_venc_bind_to_dsp2_channel,
    .set_input_y_buffer = bl808_venc_set_input_y_buffer,
    .set_input_uv_buffer = bl808_venc_set_input_uv_buffer,
    .set_callback = bl808_venc_set_callback,
    .set_resolution = bl808_venc_set_resolution,
    .get_resolution = bl808_venc_get_resolution,
    .set_video_param = bl808_venc_set_video_param,
    .get_video_param = bl808_venc_get_video_param,
    .config = bl808_venc_set_jpeg_config,
    .start = bl808_venc_start,
    .stop = bl808_venc_stop_jpeg,
    .stop_recv_pic = bl808_venc_stop_recv_pic,
    .encode_frame = NULL,
    .get_codec_type = bl808_venc_get_codec_type,
    .is_busy = bl808_venc_is_busy,
    .priv = &jpeg_enc,
};

