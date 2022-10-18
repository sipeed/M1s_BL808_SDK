/**
 * @file bl_gpu_dma2d.h
 * @brief
 *
 * Copyright (c) 2021 Bouffalolab team
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 */

#ifndef _BL_GPU_DMA2D_H_
#define _BL_GPU_DMA2D_H_

#include "lvgl.h"

#ifndef LV_GPU_BL808_DMA2D_COPY_SIZE_LIMIT
/** Minimum area (in pixels) for image copy with 100% opacity to be handled by PXP */
#define LV_GPU_BL808_DMA2D_COPY_SIZE_LIMIT 64
#endif

#ifndef LV_GPU_BL808_DMA2D_COPY_OPA_SIZE_LIMIT
/** Minimum area (in pixels) for image copy with transparency to be handled by PXP */
#define LV_GPU_BL808_DMA2D_COPY_OPA_SIZE_LIMIT 32
#endif

#ifndef LV_GPU_BL808_DMA2D_FILL_SIZE_LIMIT
/** Minimum area (in pixels) to be filled by PXP with 100% opacity */
#define LV_GPU_BL808_DMA2D_FILL_SIZE_LIMIT 64
#endif

#ifndef LV_GPU_BL808_DMA2D_FILL_OPA_SIZE_LIMIT
/** Minimum area (in pixels) to be filled by PXP with transparency */
#define LV_GPU_BL808_DMA2D_FILL_OPA_SIZE_LIMIT 32
#endif

/**
 * Reset and initialize DMA2D device. This function should be called as a part
 * of display init sequence.
 *
 * @return LV_RES_OK: PXP init ok; LV_RES_INV: init error. See error log for more information.
 */
lv_res_t bl_gpu_dma2d_init(void);

/**
 * Disable DMA2D device. Should be called during display deinit sequence.
 */
void bl_gpu_dma2d_deinit(void);

/**
 * Fill area, with optional opacity.
 *
 * @param[in/out] dest_buf destination buffer
 * @param[in] dest_width width (stride) of destination buffer in pixels
 * @param[in] fill_area area to fill
 * @param[in] color color
 */
lv_res_t bl_gpu_dma2d_fill(lv_color_t *dest_buf, lv_coord_t dest_width, const lv_area_t *fill_area, lv_color_t color);

/**
 * @brief BLock Image Transfer - copy rectangular image from src buffer to dst buffer with effects.
 *
 * By default, image is copied directly, with optional opacity configured by \p opa.
 * Color keying can be enabled by calling lv_gpu_nxp_pxp_enable_color_key() before calling this function.
 * Recoloring can be enabled by calling lv_gpu_nxp_pxp_enable_recolor() before calling this function.
 * Note that color keying and recoloring at the same time is not supported and black rectangle is rendered.
 *
 * @param[in/out] dest destination buffer
 * @param[in] dest_width width (stride) of destination buffer in pixels
 * @param[in] src source buffer
 * @param[in] src_with width (stride) of source buffer in pixels
 * @param[in] copy_w width of area to be copied from src to dest
 * @param[in] copy_h height of area to be copied from src to dest
 */
lv_res_t bl_gpu_dma2d_copy(lv_color_t *dest, lv_coord_t dest_width, const lv_color_t *src, lv_coord_t src_width,
                         lv_coord_t copy_width, lv_coord_t copy_height);

/**
 * @brief Enable color keying for subsequent calls to lv_gpu_nxp_pxp_blit()
 *
 * Color key is defined by LV_COLOR_TRANSP symbol in lv_conf.h
 */
void bl_gpu_dma2d_enable_color_key(void);

/**
 * @brief Disable color keying for subsequent calls to lv_gpu_nxp_pxp_blit()
 *
 */
void bl_gpu_dma2d_disable_color_key(void);

#endif