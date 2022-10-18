/**
  ******************************************************************************
  * @file    dpi_hw_mode.c
  * @version V1.0
  * @date
  * @brief   This file is the peripheral case c file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2020 Bouffalo Lab</center></h2>
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
  *
  ******************************************************************************
  */

#include "bl808_dbi.h"
#include "ili9488.h"
#include "bl808_cam.h"
#include "bl808_dsp2.h"
#include "bl808_dsp2_misc.h"
#include "bl808_dvp_tsrc.h"
#include "bl808_glb.h"
#include "bflb_platform.h"
#include <cli.h>
#include <mm_dsp2.h>

#include <sample_common.h>
#include <FreeRTOS.h>
#include <task.h>

/** @addtogroup  BL808_Peripheral_Case
 *  @{
 */

/** @addtogroup  DPI
 *  @{
 */

/** @defgroup  DPI_Private_Macros
 *  @{
 */
#define CAMERA_WIDTH                   (1920)
#define CAMERA_HEIGHT                  (1080)
#define SCALER_WIDTH                   (960)
#define SCALER_HEIGHT                  (540)
#define CROP_WIDTH                     (320)
#define CROP_HEIGHT                    (480)
#define CAM_USE_ID                     CAM7_ID
#define MEMORY_ADDR_USE                (0x84000000)
#define YUV422_FRAME_SIZE              (CROP_WIDTH * CROP_HEIGHT * 2)
#define MEMORY_SIZE_USE                (YUV422_FRAME_SIZE*2)

#define YUV_SENSOR_SELETCT      0
/*@} end of group DPI_Private_Macros */

/** @defgroup  DPI_Private_Variables
 *  @{
 */
static DBI_CFG_Type dbiCfg =
{
    .mode = DBI_TYPE_C_3_WIRE,                          /* DBI type B or C select */
    .pixelFormat = DBI_PIXEL_RGB666,                    /* DBI pixel format */
    .fifoFormat = DBI_FIFO_888_NBGR,                    /* DBI fifo format */
    .continueEn = ENABLE,                               /* Enable:CS will stay asserted between each consecutive pixel, disable:CS will de-assert between each pixel */
    .dummyEn = DISABLE,                                 /* Enable:dummy cycle will be inserted between command phase adn data phase, disable:no dummy cycle */
    .dummyCnt = 0,                                      /* Dummy cycle count,effective only in type C(fixed to 1 in type B) */
    .clkPhase = DBI_SCL_CLK_PHASE_0,                    /* DBI clock phase */
    .clkPolarity = DBI_SCL_CLK_POLARITY_LOW,            /* DBI clock polarity */
    .startLen = 0,                                      /* Length of start/stop condition  */
    .dataPhase0Len = 0,                                 /* Length of data phase 0 */
    .dataPhase1Len = 0,                                 /* Length of data phase 1 */
    .intervalLen = 0                                    /* Length of interval between pixel data */
};

static DVP_TSRC_Cfg_Type dvpTsrcCfg =
{
    .dataFromSensor = DISABLE,                          /* Enable: pixel data is from sensor, disable: pixel data is from AXI */
    .sensorHsyncInverse = DISABLE,                      /* Enable or disable inverse signal of sensor hsync */
    .sensorVsyncInverse = DISABLE,                      /* Enable or disable inverse signal of sensor vsync */
    .yuv420Enable = DISABLE,                            /* Enable or disable YUV420 mode, YUV420 data is from 2 different planar buffers when enable */
    .lineType = DVP_TSRC_YUV420_LINE_EVEN,              /* Select UV send in Y even lines or odd lines */
    .swapMode = ENABLE,                                 /* Enable or disable swap mode */
    .swapControl = DVP_TSRC_SWAP_HARDWARE,              /* Set swap index controlled by hardware or software */
    .dvp2axi = DVP_TSRC_DVP2AXI_7,                      /* Choose dvp2axi used */
    .format = DVP_TSRC_PIXEL_YUV422_16BIT,              /* Set pixel data format */
    .burst = DVP_TSRC_BURST_TYPE_INCR16,                /* AXI burst length */
    .byte0 = 0,                                         /* Byte 0 selection */
    .byte1 = 1,                                         /* Byte 1 Selection */
    .byte2 = 2,                                         /* Byte 2 Selection */
    .hTotalCnt = 499,                                   /* Horizontal total pixel count */
    .hBlankCnt = 179,                                   /* Horizontal blank stage pixel count */
    .vTotalCnt = 499,                                   /* Vertical total pixel count */
    .vBlankCnt = 19,                                    /* Vertical blank stage pixel count */
    .prefetch = 0,                                      /* Vertical prefetch start position, relativeto blank start position */
    .fifoThreshold = 0,                                 /* FIFO threshold for each DVP line to start to output */
    .memStartY0 = MEMORY_ADDR_USE,                      /* AXI2DVP start address, Y-planar in YUV420 mode, frame 0 in swap mode */
    .memSizeY0 = YUV422_FRAME_SIZE,                     /* AXI2DVP memory size of memStartY0 */
    .memStartY1 = MEMORY_ADDR_USE+YUV422_FRAME_SIZE,    /* AXI2DVP start address, Y-planar in YUV420 mode, frame 1 in swap mode, don't care if not swap mode */
    .memStartUV0 = 0,                                   /* AXI2DVP start address, UV-planar in YUV420 mode, frame 0 in swap mode, don't care if not YUV420 mode */
    .memStartUV1 = 0,                                   /* AXI2DVP start address, UV-planar in YUV420 mode, frame 1 in swap mode, don't care if not YUV420 swap mode */
};

static DSP2_MISC_Display_Cfg_Type displayCfg =
{
    .dpiEnable = ENABLE,                                /* Enable or disable dpi function */
    .bt1120Enable = DISABLE,                            /* Enable or disable BT1120 function, BT1120 and BT656 should not be enabled at the same time */
    .bt656Enable = DISABLE,                             /* Enable or disable BT656 function, BT1120 and BT656 should not be enabled at the same time */
    .inputType = DSP2_MISC_DISPLAY_YUV2RGB_OUTPUT,       /* Select display input */
    .osdType = DSP2_MISC_DISPLAY_OSD_YUV420TO422_OUTPUT, /* Select display OSD input */
    .hsyncWidth = 45,                                   /* Horizontal synchronization width */
    .hfpWidth = 89,                                     /* Horizontal front porch width */
    .vsyncWidth = 6,                                    /* Vertical synchronization width */
    .vfpWidth = 5,                                      /* Vertical front porch width */
};

static DSP2_MISC_Scaler_Cfg_Type scalerCfg =
{
    .inputWidth = CAMERA_WIDTH,                         /* Width of input frame */
    .inputHeight = CAMERA_HEIGHT,                       /* Height of input frame */
    .outputWidth = SCALER_WIDTH,                        /* Width of output frame */
    .outputHeight = SCALER_HEIGHT,                      /* Height of output frame */
};

static DSP2_MISC_Scaler_Cfg_Type sub_scalerCfg =
{
    .inputWidth = CAMERA_WIDTH,                         /* Width of input frame */
    .inputHeight = CAMERA_HEIGHT,                       /* Height of input frame */
    .outputWidth = 640,                        /* Width of output frame */
    .outputHeight = 480,                      /* Height of output frame */
};

static CAM_CFG_Type cameraCfg =
{
    .swMode = CAM_SW_MODE_AUTO,
    .swIntCnt = 0,
    .pixWidth = CAM_PIX_DATA_BIT_16,
    .dropMode = CAM_DROP_NONE,
    .linePol = CAM_LINE_ACTIVE_POLARITY_HIGH,
    .framePol = CAM_FRAME_ACTIVE_POLARITY_HIGH,
    .camSensorMode = CAM_SENSOR_MODE_V_AND_H,
    .burstType = CAM_BURST_TYPE_INCR16,
    .waitCount = 0x40,
    .memStart = MEMORY_ADDR_USE,
    .memSize = MEMORY_SIZE_USE,
    .frameSize = YUV422_FRAME_SIZE,
};

static DSP2_MISC_YUV2RGB_Cfg_Type yuv2rgbCfg =
{
    .enable = ENABLE,
    .preOffset0 = 0,
    .preOffset1 = 0xff80,
    .preOffset2 = 0xff80,
    .postOffset0 = 0,
    .postOffset1 = 0,
    .postOffset2 = 0,
    .matrix00 = 512,
    .matrix01 = 0,
    .matrix02 = 718,
    .matrix10 = 512,
    .matrix11 = 0xff50,
    .matrix12 = 0xfe92,
    .matrix20 = 512,
    .matrix21 = 907,
    .matrix22 = 0,
};


/*@} end of group DPI_Private_Variables */

/** @defgroup  DPI_Global_Variables
 *  @{
 */

/*@} end of group DPI_Global_Variables */

/** @defgroup  DPI_Private_Fun_Declaration
 *  @{
 */



/*@} end of group DPI_Private_Fun_Declaration */

/** @defgroup  DPI_Private_Functions
 *  @{
 */

static DVP_2x_Cfg_Type dvpCfg =
{
    .hSyncLevel = DSP2_MISC_ACTIVE_HIGH,
    .vSyncLevel = DSP2_MISC_ACTIVE_HIGH,
    .dataOrder = DSP2_MISC_2X_DATA_BYTE_LOWER,
    .fifoThreshold = 600,
};
/****************************************************************************//**
 * @brief  DPI case
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/

static void DPI_Case(void)
{
    ((*(volatile uint32_t*)(0x300000fc)) = ((*(volatile uint32_t*)(0x300000fc))|1<<5));
    GLB_Set_HDMI_CLK(ENABLE, HDMI_CLK_27_MHZ, 0);

    DBI_Init(&dbiCfg);
 
    CAM_Hsync_Crop(CAM_USE_ID,0,CROP_WIDTH);
    CAM_Vsync_Crop(CAM_USE_ID,0,CROP_HEIGHT);
    CAM_HW_Cover_First_Frame_Everytime(CAM_USE_ID,DISABLE);
 
    DVP_TSRC_Init(DVP_TSRC1_ID,&dvpTsrcCfg);
    DSP2_MISC_YUV2RGB_Init(DSP2_MISC_YUV2RGB_DISPLAY_ID,&yuv2rgbCfg);

#if !YUV_SENSOR_SELETCT
    DSP2_MISC_Scaler_Init(DSP2_MISC_SCALER_1_ID,&scalerCfg);
    DSP2_MISC_Scaler_Input_Select(DSP2_MISC_SCALER_1_ID,DSP2_MISC_SCALER_OSD_1_OUTPUT);
    DSP2_MISC_Scaler_Enable(DSP2_MISC_SCALER_1_ID);
#else
    DSP2_MSIC_DVP_2x_Init(&dvpCfg);
    MM_YUVSensor_Init();
    bl_dsp2_scaler_path_dvp2x(DSP2_MISC_SCALER_B);
    DSP2_MSIC_DVP_2x_Enable();
#endif
    CAM_Init(CAM_USE_ID, &cameraCfg);
    DSP2_MISC_CAM_Input_Select(DSP2_MISC_CAM_7_ID,DSP2_MISC_CAM_SCALER_1_OUTPUT);
    CAM_Enable(CAM_USE_ID);

    LCD_DPI_Init();
    ((*(volatile uint32_t*)(0x300000fc)) = ((*(volatile uint32_t*)(0x300000fc))&(~(3<<4))));

    DSP2_MISC_Display_Init(&displayCfg);

    DVP_TSRC_Enable(DVP_TSRC1_ID);
    //DVP_TSRC_Enable(DVP_TSRC0_ID);
}

static void dpi_hw_mode_task(void *p_arg)
{
    MSG("DPI HW case:\r\n");

    DPI_Case();
    MSG("OK\n");
    vTaskDelete(NULL);
}


/*@} end of group DPI_Private_Functions */

/** @defgroup  DPI_Public_Functions
 *  @{
 */

/****************************************************************************//**
 * @brief  DPI in hardware mode case main function
 *
 * @param  None
 *
 * @return SUCCESS
 *
*******************************************************************************/

static void dpi_hw_mode_entry(char *buf, int len, int argc, char **argv)
{
    xTaskCreate(dpi_hw_mode_task, (char*)"dpi task", 2048, NULL, 31, NULL);
}

static void dpi_close(char *buf, int len, int argc, char **argv)
{
    CAM_Disable(CAM_USE_ID);
}

const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
    { "dpi_hw", "dpi_hw", dpi_hw_mode_entry },
    { "close_display", "dpi_close", dpi_close },
};

int helper_dpi_hw_cli_init(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user) / sizeof(cmds_user[0]));
    return 0;
}
/*@} end of group DPI_Public_Functions */

/*@} end of group DPI */

/*@} end of group BL808_Peripheral_Case */
