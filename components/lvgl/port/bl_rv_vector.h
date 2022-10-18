/**
 * @file bl_rv_vector.h
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

#ifndef _BL_RV_VECTOR_H_
#define _BL_RV_VECTOR_H_

#include "lvgl.h"

/* copy */
#ifndef LV_CPU_RV_VECTOR_COPY_WIDTH_LIMIT
#define LV_CPU_RV_VECTOR_COPY_WIDTH_LIMIT 16
#endif

#ifndef LV_CPU_RV_VECTOR_COPY_SIZE_LIMIT
#define LV_CPU_RV_VECTOR_COPY_SIZE_LIMIT 64
#endif

/* copy with opa */
#ifndef LV_CPU_RV_VECTOR_COPY_OPA_WIDTH_LIMIT
#define LV_CPU_RV_VECTOR_COPY_OPA_WIDTH_LIMIT 16
#endif

#ifndef LV_CPU_RV_VECTOR_COPY_OPA_SIZE_LIMIT
#define LV_CPU_RV_VECTOR_COPY_OPA_SIZE_LIMIT 64
#endif

/* copy with alpha */
#ifndef LV_CPU_RV_VECTOR_COPY_ALPHA_WIDTH_LIMIT
#define LV_CPU_RV_VECTOR_COPY_ALPHA_WIDTH_LIMIT 16
#endif

#ifndef LV_CPU_RV_VECTOR_COPY_ALPHA_SIZE_LIMIT
#define LV_CPU_RV_VECTOR_COPY_ALPHA_SIZE_LIMIT 64
#endif

/* fill */
#ifndef LV_CPU_RV_VECTOR_FILL_WIDTH_LIMIT
#define LV_CPU_RV_VECTOR_FILL_WIDTH_LIMIT 16
#endif

#ifndef LV_CPU_RV_VECTOR_FILL_SIZE_LIMIT
#define LV_CPU_RV_VECTOR_FILL_SIZE_LIMIT 128
#endif

/* fill with opa */
#ifndef LV_CPU_RV_VECTOR_FILL_OPA_WIDTH_LIMIT
#define LV_CPU_RV_VECTOR_FILL_OPA_WIDTH_LIMIT 16
#endif

#ifndef LV_CPU_RV_VECTOR_FILL_OPA_SIZE_LIMIT
#define LV_CPU_RV_VECTOR_FILL_OPA_SIZE_LIMIT 128
#endif


lv_res_t bl_rv_vector_fill(lv_color_t *dest_buf, lv_coord_t dest_width, const lv_area_t *fill_area, lv_color_t color);
lv_res_t bl_rv_vector_fill_with_opa(lv_color_t *dest_buf, lv_coord_t dest_width, const lv_area_t *fill_area, lv_color_t color, lv_opa_t opa);

lv_res_t bl_rv_vector_copy(lv_color_t *dest, lv_coord_t dest_width, const lv_color_t *src, lv_coord_t src_width, lv_coord_t copy_width, lv_coord_t copy_height);
lv_res_t bl_rv_vector_blit_with_opa(lv_color_t *dest, lv_coord_t dest_width, const lv_color_t *src, lv_coord_t src_width, lv_coord_t copy_width, lv_coord_t copy_height, lv_opa_t opa);

lv_res_t bl_rv_vector_blit_with_alpha(lv_color_t *dest, lv_coord_t dest_width, const lv_color_t *src, lv_coord_t src_width, lv_coord_t copy_width, lv_coord_t copy_height);

#endif