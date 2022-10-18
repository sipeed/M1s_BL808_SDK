/**
 * @file gc9c01_disp_qspi.h
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

#ifndef _GC9C01_DISP_QSPI_H_
#define _GC9C01_DISP_QSPI_H_

#include "bflb_platform.h"

/* Optional pixel data format type */
#define GC9C01_DISP_QSPI_PIXEL_FORMAT_RGB888 888
#define GC9C01_DISP_QSPI_PIXEL_FORMAT_RGB565 565

/* Select qspi Wire width for cmd */
/* Wire width for cmd, gc9c01 must 1 */
#define GC9C01_DISP_QSPI_WIRE_WIDTH_CMD 1
/* Wire width for address, 1 or 4 */
#define GC9C01_DISP_QSPI_WIRE_WIDTH_ADDR 4
/* Wire width for data, 1 or 4, and it's not less than address */
#define GC9C01_DISP_QSPI_WIRE_WIDTH_DATA 4

/* Select pixel format */
#define GC9C01_DISP_QSPI_PIXEL_FORMAT GC9C01_DISP_QSPI_PIXEL_FORMAT_RGB565

/* GC9C01 LCD width */
#define GC9C01_DISP_QSPI_W 360
/* GC9C01 LCD height */
#define GC9C01_DISP_QSPI_H 360

/* The offset of the area can be displayed */
#define GC9C01_DISP_QSPI_OFFSET_X 0
#define GC9C01_DISP_QSPI_OFFSET_Y 0

#if (GC9C01_DISP_QSPI_PIXEL_FORMAT == GC9C01_DISP_QSPI_PIXEL_FORMAT_RGB565)
#define GC9C01_DISP_QSPI_COLOR_DEPTH 16
typedef uint16_t gc9c01_disp_qspi_color_t;
#elif (GC9C01_DISP_QSPI_PIXEL_FORMAT == GC9C01_DISP_QSPI_PIXEL_FORMAT_RGB888)
#define GC9C01_DISP_QSPI_COLOR_DEPTH 32
typedef uint32_t gc9c01_disp_qspi_color_t;
#endif

typedef struct {
    uint8_t cmd; /* 0xFF : delay(databytes)ms */
    const char *data;
    uint8_t databytes; /* Num of data in data; or delay time */
} gc9c01_disp_qspi_init_cmd_t;

int gc9c01_disp_qspi_init();
void gc9c01_disp_qspi_async_callback_register(void (*callback)(void));
int gc9c01_disp_qspi_set_dir(uint8_t dir, uint8_t mir_flag);
void gc9c01_disp_qspi_set_draw_window(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void gc9c01_disp_qspi_draw_point(uint16_t x, uint16_t y, gc9c01_disp_qspi_color_t color);
void gc9c01_disp_qspi_draw_area(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, gc9c01_disp_qspi_color_t color);
void gc9c01_disp_qspi_draw_picture_nonblocking(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, gc9c01_disp_qspi_color_t *picture);
void gc9c01_disp_qspi_draw_picture_blocking(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, gc9c01_disp_qspi_color_t *picture);
int gc9c01_disp_qspi_draw_is_busy(void);

#endif