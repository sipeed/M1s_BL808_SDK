/**
 * @file ili9488_dpi.h
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

#ifndef _ILI9488_DBI_H_
#define _ILI9488_DBI_H_

#include "bflb_platform.h"

/* Optional pixel data format type */
#define ILI9488_DPI_PIXEL_FORMAT_RGB888 888 /* Equivalent to RGB888 */
#define ILI9488_DPI_PIXEL_FORMAT_RGB565 565

/* Select pixel format */
#define ILI9488_DPI_PIXEL_FORMAT ILI9488_DPI_PIXEL_FORMAT_RGB565

/* ILI9488 LCD width */
#define ILI9488_DPI_W 320
/* ILI9488 LCD height */
#define ILI9488_DPI_H 480

#if (ILI9488_DPI_PIXEL_FORMAT == ILI9488_DPI_PIXEL_FORMAT_RGB565)
#define ILI9488_DPI_COLOR_DEPTH 16
typedef uint16_t ili9488_dpi_color_t;
#elif (ILI9488_DPI_PIXEL_FORMAT == ILI9488_DPI_PIXEL_FORMAT_RGB888)
#define ILI9488_DPI_COLOR_DEPTH 32
typedef uint32_t ili9488_dpi_color_t;
#endif

/* Ili9488 needs to be initialized using the DBI(typeC) or SPI interface */
typedef struct {
    uint8_t cmd; /* 0xFF : delay(databytes)ms */
    const char *data;
    uint8_t databytes; /* Num of data in data; or delay time */
} ili9488_dpi_init_cmd_t;

int ili9488_dpi_init(ili9488_dpi_color_t *screen_buffer);
int ili9488_dpi_screen_switch(ili9488_dpi_color_t *screen_buffer);
ili9488_dpi_color_t *ili9488_dpi_get_screen_using(void);
int ili9488_dpi_frame_callback_register(uint32_t callback_type, void (*callback)(void));

#endif
