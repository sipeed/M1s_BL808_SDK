/**
 * @file standard_dpi.c
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

#include "../lcd.h"

#if defined(LCD_DPI_STANDARD) 

#include "bflb_platform.h"

#include "bl808_dvp_tsrc.h"
#include "bl808_dsp2_misc.h"
#include "bl808_dbi.h"
#include "bl808_glb.h"
#include "dtsrc_reg.h"

#include "standard_dpi.h"

/* Video memory used for this frame, Update in frame interrupt*/
static volatile standard_dpi_color_t *screen_last = NULL;

typedef void (*standard_dpi_callback)(void);
static volatile standard_dpi_callback standard_dpi_frame_callback = NULL;
static volatile standard_dpi_callback standard_dpi_frame_swap_callback = NULL;

static DVP_TSRC_Cfg_Type dvpTsrcCfg = {
    .dataFromSensor = DISABLE,             /* Enable: pixel data is from sensor, disable: pixel data is from AXI */
    .sensorHsyncInverse = DISABLE,         /* Enable or disable inverse signal of sensor hsync */
    .sensorVsyncInverse = DISABLE,         /* Enable or disable inverse signal of sensor vsync */
    .yuv420Enable = DISABLE,               /* Enable or disable YUV420 mode, YUV420 data is from 2 different planar buffers when enable */
    .lineType = DVP_TSRC_YUV420_LINE_EVEN, /* Select UV send in Y even lines or odd lines */
    .swapMode = ENABLE,                    /* Enable or disable swap mode */
    .swapControl = DVP_TSRC_SWAP_SOFTWARE, /* Set swap index controlled by hardware or software */
    .dvp2axi = DVP_TSRC_DVP2AXI_0,         /* Choose dvp2axi used */
#if (STANDARD_DPI_PIXEL_FORMAT == STANDARD_DPI_PIXEL_FORMAT_RGB565)
    .format = DVP_TSRC_PIXEL_RGB565_16TO24BIT, /* Set pixel data format */
    .byte0 = 0,                                /* Byte 0 selection */
    .byte1 = 2,                                /* Byte 1 Selection */
    .byte2 = 1,                                /* Byte 2 Selection */
#elif (STANDARD_DPI_PIXEL_FORMAT == STANDARD_DPI_PIXEL_FORMAT_RGB888)
    .format = DVP_TSRC_PIXEL_RGBA8888_32TO24BIT, /* Set pixel data format */
    .byte0 = 0,                                  /* Byte 0 selection */
    .byte1 = 1,                                  /* Byte 1 Selection */
    .byte2 = 2,                                  /* Byte 2 Selection */
#endif
    .burst = DVP_TSRC_BURST_TYPE_INCR16, /* AXI burst length */
    .hTotalCnt = 900 - 1,                /* Horizontal total pixel count */
    .hBlankCnt = 100 - 1,                /* Horizontal blank stage pixel count */
    .vTotalCnt = 530 - 1,                /* Vertical total pixel count */
    .vBlankCnt = 50 - 1,                 /* Vertical blank stage pixel count */

    .prefetch = 0,                                                               /* Vertical prefetch start position, relativeto blank start position */
    .fifoThreshold = STANDARD_DPI_W,                                             /* FIFO threshold for each DVP line to start to output */
    .memStartY0 = 0,                                                             /* AXI2DVP start address, Y-planar in YUV420 mode, frame 0 in swap mode */
    .memSizeY0 = sizeof(standard_dpi_color_t) * STANDARD_DPI_W * STANDARD_DPI_H, /* AXI2DVP memory size of memStartY0 */
    .memStartY1 = 0,                                                             /* AXI2DVP start address, Y-planar in YUV420 mode,  frame 1 in swap mode, don't care if not swap mode */
    .memStartUV0 = 0,                                                            /* AXI2DVP start address, UV-planar in YUV420 mode, frame 0 in swap mode, don't care if not YUV420 mode */
    .memStartUV1 = 0,                                                            /* AXI2DVP start address, UV-planar in YUV420 mode, frame 1 in swap mode, don't care if not YUV420 swap mode */
};

static DSP2_MISC_Display_Cfg_Type displayCfg = {
    .dpiEnable = ENABLE,                               /* Enable or disable dpi function */
    .bt1120Enable = DISABLE,                           /* Enable or disable BT1120 function, BT1120 and BT656 should not be enabled at the same time */
    .inputType = DSP2_MISC_DISPLAY_TSRC_RGB_OUTPUT,     /* Select display input */
    .osdType = DSP2_MISC_DISPLAY_OSD_RGB2YUV422_OUTPUT, /* Select display OSD input */
    .hsyncWidth = 4 - 1,                               /* Horizontal synchronization width */
    .hfpWidth = 100 - 4 - 82 - 1,                      /* Horizontal front porch width */
    .vsyncWidth = 5 - 1,                               /* Vertical synchronization width */
    .vfpWidth = 50 - 5 - 6 - 1,                        /* Vertical front porch width */
};

void standard_dpi_frame_interrupt(void)
{
    uint8_t swap_flag = 0;
    DSP2_MISC_Int_Clear_1(DSP2_MISC_INT_DISPLAY);

    standard_dpi_color_t *screen_next = (standard_dpi_color_t *)(uintptr_t)BL_RD_REG(DVP_TSRC1_BASE, DTSRC_AXI2DVP_START_ADDR_BY);

    if (screen_last != screen_next) {
        swap_flag = 1;
        screen_last = screen_next;
    }

    if (standard_dpi_frame_callback != NULL) {
        standard_dpi_frame_callback();
    }

    if (standard_dpi_frame_swap_callback != 0 && swap_flag) {
        standard_dpi_frame_swap_callback();
    }
}

static int standard_dpi_peripheral_init(standard_dpi_color_t *screen_buffer)
{
    /* MIPI clock config */
    GLB_Config_MIPI_PLL(GLB_XTAL_40M, mipiPllCfg_1500M);
    GLB_Set_Display_CLK(ENABLE, GLB_DISP_CLK_MIPIPLL_1500M, 45);

    dvpTsrcCfg.memStartY0 = (uint32_t)(uintptr_t)screen_buffer;

    /* DPI config */
    DVP_TSRC_Set_Swap_Index(DVP_TSRC1_ID, 1);
    DVP_TSRC_Init(DVP_TSRC1_ID, &dvpTsrcCfg);
    DSP2_MISC_Display_Init(&displayCfg);

    /* Set display interrupt */
    DSP2_MISC_Int_Mask(DSP2_MISC_INT_ALL, MASK);
    DSP2_MISC_SEOF_Set_Source(DSP2_MISC_INT_DISPLAY, DSP2_MISC_SEOF_DISPLAY_OUTPUT);
    DSP2_MISC_SEOF_Set_Edge(DSP2_MISC_INT_DISPLAY, DSP2_MISC_SEOF_VSYNC_NEGEDGE);
    DSP2_MISC_Int_Callback_Install(DSP2_MISC_INT_DISPLAY, &standard_dpi_frame_interrupt);
    DSP2_MISC_Int_Mask(DSP2_MISC_INT_DISPLAY, UNMASK);
    CPU_Interrupt_Enable(DISPLAY_IRQn);
    System_NVIC_SetPriority(DISPLAY_IRQn, 4, 1);
    return 0;
}

int standard_dpi_init(standard_dpi_color_t *screen_buffer)
{
    if (screen_buffer == NULL) {
        return -1;
    }

    /* init DBI and DPI peripheral*/
    standard_dpi_peripheral_init(screen_buffer);

    /* enable DPI, Start output data*/
    DVP_TSRC_Enable(DVP_TSRC1_ID);
    return 0;
}

int standard_dpi_screen_switch(standard_dpi_color_t *screen_buffer)
{
    if (screen_buffer == NULL) {
        return -1;
    }

    csi_dcache_clean_range((void *)screen_buffer, (sizeof(standard_dpi_color_t) * STANDARD_DPI_W * STANDARD_DPI_H));

    BL_WR_REG(DVP_TSRC1_BASE, DTSRC_AXI2DVP_START_ADDR_BY, (uint32_t)(uintptr_t)screen_buffer);

    return 0;
}

standard_dpi_color_t *standard_dpi_get_screen_using(void)
{
    return (standard_dpi_color_t *)screen_last;
}

int standard_dpi_frame_callback_register(uint32_t callback_type, void (*callback)(void))
{
    if (callback_type == FRAME_INT_TYPE_SWAP) {
        standard_dpi_frame_swap_callback = callback;
    } else if (callback_type == FRAME_INT_TYPE_CYCLE) {
        standard_dpi_frame_callback = callback;
    }
    return 0;
}

#elif defined(LCD_DPI_STANDARD)
#error "Devices that do not support DPI! Replace the driver port (lcd.h)"
#endif
