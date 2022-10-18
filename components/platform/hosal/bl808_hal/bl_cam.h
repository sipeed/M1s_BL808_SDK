/*
 * Copyright (c) 2016-2022 Bouffalolab.
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
#ifndef __BL_CAM_H__
#define __BL_CAM_H__
typedef void (cam_callback_type)(void);
int bl_cam_yuv_init(void);
int bl_cam_rgb_frame_get(uint8_t **pic, uint32_t *len);
void bl_cam_yuv_frame_pop(void);
void bl_cam_yuv_deinit(void);
void bl_cam_yuv_cb_register(cam_callback_type *cb);
int bl_cam_mjpeg_init(void);
int bl_cam_mjpeg_get(uint8_t **ptr, uint32_t *len);
int bl_cam_mjpeg_pop();
int bl_cam_mjpeg_deinit(void);
int bl_cam_mipi_yuv_init(void);
void bl_cam_mipi_yuv_deinit(void);
int bl_cam_mipi_rgb_frame_get(uint8_t **pic, uint32_t *len);
void bl_cam_mipi_frame_pop(void);
int bl_cam_mipi_rgb565_init(void);
void bl_cam_mipi_rgb565_deinit(void);
int bl_cam_mipi_rgb565_frame_get(uint8_t **pic, uint32_t *len);
void bl_cam_mipi_rgb565_frame_pop(void);
int bl_cam_mipi_mjpeg_init(void);
#endif
