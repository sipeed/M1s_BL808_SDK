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
#ifndef __VENC_FRAMEWORK_H__
#define __VENC_FRAMEWORK_H__
#include <stdint.h>
#include <stdbool.h>


typedef struct venc_framework_device venc_framework_device_t;
typedef struct venc_buf_s venc_buf_t;
typedef struct venc_result_s venc_result_t;

typedef void (*venc_framework_alloc_cb)(venc_framework_device_t *device,
                                        uint32_t suggested_size,
                                        int is_high_usage,
                                        venc_buf_t *buf);

typedef void (*venc_framework_free_cb)(venc_framework_device_t *device,
                                        void *buf_base);

typedef void (*venc_framework_recv_cb)(venc_framework_device_t *device,
                                        venc_result_t *buf);

typedef void (*venc_framework_stop_cb)(venc_framework_device_t *device, int stream_id);

typedef enum venc_framework_codec_type {
    VENC_FRAMEWORK_CODEC_TYPE_H264,
    VENC_FRAMEWORK_CODEC_TYPE_JPEG,
} VENC_FRAMEWORK_CODEC_TYPE_T;

typedef enum {
    VENC_FRAMEWORK_H264_I_FRAME,
    VENC_FRAMEWORK_H264_P_FRAME,
    VENC_FRAMEWORK_JPEG_FRAME,
} VENC_FRAMEWORK_FRAME_TYPE_T;

typedef enum venc_framework_h264_rc_mode {
    VENC_FRAMEWORK_H264_RC_CBR,
    VENC_FRAMEWORK_H264_RC_VBR,
    VENC_FRAMEWORK_H264_RC_FIXQP,
} VENC_FRAMEWORK_H264_RC_MODE_T;

typedef enum venc_framework_video_format_key {
    VIDEO_FORMAT_KEY_LOW_POWER_MODE,
    VIDEO_FORMAT_KEY_BITRATE_MODE,
    VIDEO_FORMAT_KEY_BIT_RATE,
    VIDEO_FORMAT_KEY_FRAME_RATE,
    VIDEO_FORMAT_KEY_GOP_SIZE,
    VIDEO_FORMAT_KEY_TARGET_I_QP,
    VIDEO_FORMAT_KEY_TARGET_P_QP,
    VIDEO_FORMAT_KEY_INIT_QP,
    VIDEO_FORMAT_KEY_MIN_QP,
    VIDEO_FORMAT_KEY_MAX_QP,
    VIDEO_FORMAT_KEY_FORCE_IP_RATIO,
    VIDEO_FORMAT_KEY_PROFILE,
    VIDEO_FORMAT_KEY_QUALITY,
    VIDEO_FORMAT_KEY_NUM,
} VENC_FRAMEWORK_VIDEO_FORMAT_KEY_T;

typedef struct venc_buf_s {
    uint32_t len;
    void* base;
} venc_buf_t;

typedef struct venc_result_s {
    VENC_FRAMEWORK_FRAME_TYPE_T frame_type;
    int stream_id;
    uint32_t frame_id;
    uint8_t *frame_start_addr;
    uint32_t frame_size;
    uint8_t *frame_sec_addr;
    uint32_t frame_sec_size;
} venc_result_t;

int venc_framework_factory_build(const char *name, venc_framework_device_t **device);
int venc_framework_factory_destory(venc_framework_device_t **device);

struct venc_framework_device {
    char name[32];
    int (*init)(venc_framework_device_t *device);
    int (*config)(venc_framework_device_t *device);
    int (*deinit)(venc_framework_device_t *device);
    int (*bind_to_dsp2_channel)(venc_framework_device_t *device,
                            int chann_id);
    int (*set_input_y_buffer)(venc_framework_device_t *device,
                    uint8_t *y_frame_base_addr,
                    uint32_t y_frame_size);
    int (*set_input_uv_buffer)(venc_framework_device_t *device,
                    uint8_t *uv_frame_base_addr,
                    uint32_t uv_frame_size);
    int (*set_resolution)(venc_framework_device_t *device,
                        uint32_t width,
                        uint32_t height);
    int (*get_resolution)(venc_framework_device_t *device,
                        uint32_t *width,
                        uint32_t *height);
    int (*set_video_param)(venc_framework_device_t *device,
                        VENC_FRAMEWORK_VIDEO_FORMAT_KEY_T key,
                        int value);
    int (*get_video_param)(venc_framework_device_t *device,
                        VENC_FRAMEWORK_VIDEO_FORMAT_KEY_T key,
                        int *value);
    /* configure venc callback */
    int (*set_callback)(venc_framework_device_t *device,
                        venc_framework_alloc_cb alloc_cb,
                        venc_framework_free_cb free_cb,
                        venc_framework_recv_cb recv_cb);
    int (*start)(venc_framework_device_t *device, int stream_id);
    int (*stop)(venc_framework_device_t *device, venc_framework_stop_cb cb);
    int (*stop_recv_pic)(venc_framework_device_t *device);
    int (*encode_frame)(venc_framework_device_t *device, int stream_id);

    VENC_FRAMEWORK_CODEC_TYPE_T (*get_codec_type)(venc_framework_device_t *device);
    bool (*is_busy)(venc_framework_device_t *device);

    /* Private pointer holder for private used data in device driver */
    void *priv;
};

#define ATTR_VENC_DEVICE_TABLE __attribute__((section(".framework.venc_device")))  __attribute__((used))

#endif  /* __VENC_FRAMEWORK_H__ */