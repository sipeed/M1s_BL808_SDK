/**
 * @file ili9881c_dsi_vidio.h
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
#ifndef __ILI9881C_DSI_VIDIO_H__
#define __ILI9881C_DSI_VIDIO_H__

#include "bflb_platform.h"

/* ILI9881c LCD width */
#define ILI9881C_DSI_VIDIO_W 720
/* ILI9881c LCD height */
#define ILI9881C_DSI_VIDIO_H 1280

#define ILI9881C_DSI_VIDIO_COLOR_DEPTH 32
typedef uint32_t ili9881c_dsi_vidio_color_t;

#define DSI_LANE_NUMBER_USE    2
#define DSI_ILI9881C_BSIT_MODE 0
#define DSI_USE_ID             DSI0_ID

int ili9881c_dsi_vidio_init(ili9881c_dsi_vidio_color_t *screen_buffer);
int ili9881c_dsi_vidio_screen_switch(ili9881c_dsi_vidio_color_t *screen_buffer);
ili9881c_dsi_vidio_color_t *ili9881c_dsi_vidio_get_screen_using(void);
int ili9881c_dsi_vidio_frame_callback_register(uint32_t callback_type, void (*callback)(void));

#endif
