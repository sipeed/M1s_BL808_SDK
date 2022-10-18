/**
  ******************************************************************************
  * @file    dsp2_front_reg.h
  * @version V1.2
  * @date    2019-09-04
  * @brief   This file is the description of.IP register
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2018 Bouffalo Lab</center></h2>
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
#ifndef  __DSP2_FRONT_REG_H__
#define  __DSP2_FRONT_REG_H__

#include "bl808.h"

/* 0x110 : pattern_mode */
#define DSP2_FRONT_PATTERN_MODE_OFFSET                           (0x110)
#define DSP2_FRONT_PATTERN_MODE_W                                DSP2_FRONT_PATTERN_MODE_W
#define DSP2_FRONT_PATTERN_MODE_W_POS                            (0U)
#define DSP2_FRONT_PATTERN_MODE_W_LEN                            (3U)
#define DSP2_FRONT_PATTERN_MODE_W_MSK                            (((1U<<DSP2_FRONT_PATTERN_MODE_W_LEN)-1)<<DSP2_FRONT_PATTERN_MODE_W_POS)
#define DSP2_FRONT_PATTERN_MODE_W_UMSK                           (~(((1U<<DSP2_FRONT_PATTERN_MODE_W_LEN)-1)<<DSP2_FRONT_PATTERN_MODE_W_POS))
#define DSP2_FRONT_PID_INV_RGB_PRE                               DSP2_FRONT_PID_INV_RGB_PRE
#define DSP2_FRONT_PID_INV_RGB_PRE_POS                           (8U)
#define DSP2_FRONT_PID_INV_RGB_PRE_LEN                           (1U)
#define DSP2_FRONT_PID_INV_RGB_PRE_MSK                           (((1U<<DSP2_FRONT_PID_INV_RGB_PRE_LEN)-1)<<DSP2_FRONT_PID_INV_RGB_PRE_POS)
#define DSP2_FRONT_PID_INV_RGB_PRE_UMSK                          (~(((1U<<DSP2_FRONT_PID_INV_RGB_PRE_LEN)-1)<<DSP2_FRONT_PID_INV_RGB_PRE_POS))
#define DSP2_FRONT_LID_INV_RGB_PRE                               DSP2_FRONT_LID_INV_RGB_PRE
#define DSP2_FRONT_LID_INV_RGB_PRE_POS                           (9U)
#define DSP2_FRONT_LID_INV_RGB_PRE_LEN                           (1U)
#define DSP2_FRONT_LID_INV_RGB_PRE_MSK                           (((1U<<DSP2_FRONT_LID_INV_RGB_PRE_LEN)-1)<<DSP2_FRONT_LID_INV_RGB_PRE_POS)
#define DSP2_FRONT_LID_INV_RGB_PRE_UMSK                          (~(((1U<<DSP2_FRONT_LID_INV_RGB_PRE_LEN)-1)<<DSP2_FRONT_LID_INV_RGB_PRE_POS))
#define DSP2_FRONT_ACT_HSIZE_W                                   DSP2_FRONT_ACT_HSIZE_W
#define DSP2_FRONT_ACT_HSIZE_W_POS                               (16U)
#define DSP2_FRONT_ACT_HSIZE_W_LEN                               (16U)
#define DSP2_FRONT_ACT_HSIZE_W_MSK                               (((1U<<DSP2_FRONT_ACT_HSIZE_W_LEN)-1)<<DSP2_FRONT_ACT_HSIZE_W_POS)
#define DSP2_FRONT_ACT_HSIZE_W_UMSK                              (~(((1U<<DSP2_FRONT_ACT_HSIZE_W_LEN)-1)<<DSP2_FRONT_ACT_HSIZE_W_POS))

/* 0x114 : clamp_R_Gr */
#define DSP2_FRONT_CLAMP_R_GR_OFFSET                             (0x114)
#define DSP2_FRONT_CLP_R_PRE                                     DSP2_FRONT_CLP_R_PRE
#define DSP2_FRONT_CLP_R_PRE_POS                                 (0U)
#define DSP2_FRONT_CLP_R_PRE_LEN                                 (16U)
#define DSP2_FRONT_CLP_R_PRE_MSK                                 (((1U<<DSP2_FRONT_CLP_R_PRE_LEN)-1)<<DSP2_FRONT_CLP_R_PRE_POS)
#define DSP2_FRONT_CLP_R_PRE_UMSK                                (~(((1U<<DSP2_FRONT_CLP_R_PRE_LEN)-1)<<DSP2_FRONT_CLP_R_PRE_POS))
#define DSP2_FRONT_CLP_GR_PRE                                    DSP2_FRONT_CLP_GR_PRE
#define DSP2_FRONT_CLP_GR_PRE_POS                                (16U)
#define DSP2_FRONT_CLP_GR_PRE_LEN                                (16U)
#define DSP2_FRONT_CLP_GR_PRE_MSK                                (((1U<<DSP2_FRONT_CLP_GR_PRE_LEN)-1)<<DSP2_FRONT_CLP_GR_PRE_POS)
#define DSP2_FRONT_CLP_GR_PRE_UMSK                               (~(((1U<<DSP2_FRONT_CLP_GR_PRE_LEN)-1)<<DSP2_FRONT_CLP_GR_PRE_POS))

/* 0x118 : clamp_B_Gb */
#define DSP2_FRONT_CLAMP_B_GB_OFFSET                             (0x118)
#define DSP2_FRONT_CLP_GB_PRE                                    DSP2_FRONT_CLP_GB_PRE
#define DSP2_FRONT_CLP_GB_PRE_POS                                (0U)
#define DSP2_FRONT_CLP_GB_PRE_LEN                                (16U)
#define DSP2_FRONT_CLP_GB_PRE_MSK                                (((1U<<DSP2_FRONT_CLP_GB_PRE_LEN)-1)<<DSP2_FRONT_CLP_GB_PRE_POS)
#define DSP2_FRONT_CLP_GB_PRE_UMSK                               (~(((1U<<DSP2_FRONT_CLP_GB_PRE_LEN)-1)<<DSP2_FRONT_CLP_GB_PRE_POS))
#define DSP2_FRONT_CLP_B_PRE                                     DSP2_FRONT_CLP_B_PRE
#define DSP2_FRONT_CLP_B_PRE_POS                                 (16U)
#define DSP2_FRONT_CLP_B_PRE_LEN                                 (16U)
#define DSP2_FRONT_CLP_B_PRE_MSK                                 (((1U<<DSP2_FRONT_CLP_B_PRE_LEN)-1)<<DSP2_FRONT_CLP_B_PRE_POS)
#define DSP2_FRONT_CLP_B_PRE_UMSK                                (~(((1U<<DSP2_FRONT_CLP_B_PRE_LEN)-1)<<DSP2_FRONT_CLP_B_PRE_POS))

/* 0x130 : ob_win */
#define DSP2_FRONT_OB_WIN_OFFSET                                 (0x130)
#define DSP2_FRONT_OB_WIN_STARTX_W                               DSP2_FRONT_OB_WIN_STARTX_W
#define DSP2_FRONT_OB_WIN_STARTX_W_POS                           (0U)
#define DSP2_FRONT_OB_WIN_STARTX_W_LEN                           (16U)
#define DSP2_FRONT_OB_WIN_STARTX_W_MSK                           (((1U<<DSP2_FRONT_OB_WIN_STARTX_W_LEN)-1)<<DSP2_FRONT_OB_WIN_STARTX_W_POS)
#define DSP2_FRONT_OB_WIN_STARTX_W_UMSK                          (~(((1U<<DSP2_FRONT_OB_WIN_STARTX_W_LEN)-1)<<DSP2_FRONT_OB_WIN_STARTX_W_POS))
#define DSP2_FRONT_OB_WIN_STARTY_W                               DSP2_FRONT_OB_WIN_STARTY_W
#define DSP2_FRONT_OB_WIN_STARTY_W_POS                           (16U)
#define DSP2_FRONT_OB_WIN_STARTY_W_LEN                           (16U)
#define DSP2_FRONT_OB_WIN_STARTY_W_MSK                           (((1U<<DSP2_FRONT_OB_WIN_STARTY_W_LEN)-1)<<DSP2_FRONT_OB_WIN_STARTY_W_POS)
#define DSP2_FRONT_OB_WIN_STARTY_W_UMSK                          (~(((1U<<DSP2_FRONT_OB_WIN_STARTY_W_LEN)-1)<<DSP2_FRONT_OB_WIN_STARTY_W_POS))

/* 0x134 : black_columns_bit */
#define DSP2_FRONT_BLACK_COLUMNS_BIT_OFFSET                      (0x134)
#define DSP2_FRONT_BLACK_ROWS_BIT_W                              DSP2_FRONT_BLACK_ROWS_BIT_W
#define DSP2_FRONT_BLACK_ROWS_BIT_W_POS                          (0U)
#define DSP2_FRONT_BLACK_ROWS_BIT_W_LEN                          (4U)
#define DSP2_FRONT_BLACK_ROWS_BIT_W_MSK                          (((1U<<DSP2_FRONT_BLACK_ROWS_BIT_W_LEN)-1)<<DSP2_FRONT_BLACK_ROWS_BIT_W_POS)
#define DSP2_FRONT_BLACK_ROWS_BIT_W_UMSK                         (~(((1U<<DSP2_FRONT_BLACK_ROWS_BIT_W_LEN)-1)<<DSP2_FRONT_BLACK_ROWS_BIT_W_POS))
#define DSP2_FRONT_BLACK_COLUMNS_BIT_W                           DSP2_FRONT_BLACK_COLUMNS_BIT_W
#define DSP2_FRONT_BLACK_COLUMNS_BIT_W_POS                       (4U)
#define DSP2_FRONT_BLACK_COLUMNS_BIT_W_LEN                       (4U)
#define DSP2_FRONT_BLACK_COLUMNS_BIT_W_MSK                       (((1U<<DSP2_FRONT_BLACK_COLUMNS_BIT_W_LEN)-1)<<DSP2_FRONT_BLACK_COLUMNS_BIT_W_POS)
#define DSP2_FRONT_BLACK_COLUMNS_BIT_W_UMSK                      (~(((1U<<DSP2_FRONT_BLACK_COLUMNS_BIT_W_LEN)-1)<<DSP2_FRONT_BLACK_COLUMNS_BIT_W_POS))

/* 0x138 : Ob_R_Gr */
#define DSP2_FRONT_OB_R_GR_OFFSET                                (0x138)
#define DSP2_FRONT_OB_R_R                                        DSP2_FRONT_OB_R_R
#define DSP2_FRONT_OB_R_R_POS                                    (0U)
#define DSP2_FRONT_OB_R_R_LEN                                    (16U)
#define DSP2_FRONT_OB_R_R_MSK                                    (((1U<<DSP2_FRONT_OB_R_R_LEN)-1)<<DSP2_FRONT_OB_R_R_POS)
#define DSP2_FRONT_OB_R_R_UMSK                                   (~(((1U<<DSP2_FRONT_OB_R_R_LEN)-1)<<DSP2_FRONT_OB_R_R_POS))
#define DSP2_FRONT_OB_GR_R                                       DSP2_FRONT_OB_GR_R
#define DSP2_FRONT_OB_GR_R_POS                                   (16U)
#define DSP2_FRONT_OB_GR_R_LEN                                   (16U)
#define DSP2_FRONT_OB_GR_R_MSK                                   (((1U<<DSP2_FRONT_OB_GR_R_LEN)-1)<<DSP2_FRONT_OB_GR_R_POS)
#define DSP2_FRONT_OB_GR_R_UMSK                                  (~(((1U<<DSP2_FRONT_OB_GR_R_LEN)-1)<<DSP2_FRONT_OB_GR_R_POS))

/* 0x13C : Ob_B_Gb */
#define DSP2_FRONT_OB_B_GB_OFFSET                                (0x13C)
#define DSP2_FRONT_OB_GB_R                                       DSP2_FRONT_OB_GB_R
#define DSP2_FRONT_OB_GB_R_POS                                   (0U)
#define DSP2_FRONT_OB_GB_R_LEN                                   (16U)
#define DSP2_FRONT_OB_GB_R_MSK                                   (((1U<<DSP2_FRONT_OB_GB_R_LEN)-1)<<DSP2_FRONT_OB_GB_R_POS)
#define DSP2_FRONT_OB_GB_R_UMSK                                  (~(((1U<<DSP2_FRONT_OB_GB_R_LEN)-1)<<DSP2_FRONT_OB_GB_R_POS))
#define DSP2_FRONT_OB_B_R                                        DSP2_FRONT_OB_B_R
#define DSP2_FRONT_OB_B_R_POS                                    (16U)
#define DSP2_FRONT_OB_B_R_LEN                                    (16U)
#define DSP2_FRONT_OB_B_R_MSK                                    (((1U<<DSP2_FRONT_OB_B_R_LEN)-1)<<DSP2_FRONT_OB_B_R_POS)
#define DSP2_FRONT_OB_B_R_UMSK                                   (~(((1U<<DSP2_FRONT_OB_B_R_LEN)-1)<<DSP2_FRONT_OB_B_R_POS))

/* 0x150 : gain_R_G */
#define DSP2_FRONT_GAIN_R_G_OFFSET                               (0x150)
#define DSP2_FRONT_RGAIN1_PRE                                    DSP2_FRONT_RGAIN1_PRE
#define DSP2_FRONT_RGAIN1_PRE_POS                                (0U)
#define DSP2_FRONT_RGAIN1_PRE_LEN                                (11U)
#define DSP2_FRONT_RGAIN1_PRE_MSK                                (((1U<<DSP2_FRONT_RGAIN1_PRE_LEN)-1)<<DSP2_FRONT_RGAIN1_PRE_POS)
#define DSP2_FRONT_RGAIN1_PRE_UMSK                               (~(((1U<<DSP2_FRONT_RGAIN1_PRE_LEN)-1)<<DSP2_FRONT_RGAIN1_PRE_POS))
#define DSP2_FRONT_GGAIN1_PRE                                    DSP2_FRONT_GGAIN1_PRE
#define DSP2_FRONT_GGAIN1_PRE_POS                                (16U)
#define DSP2_FRONT_GGAIN1_PRE_LEN                                (11U)
#define DSP2_FRONT_GGAIN1_PRE_MSK                                (((1U<<DSP2_FRONT_GGAIN1_PRE_LEN)-1)<<DSP2_FRONT_GGAIN1_PRE_POS)
#define DSP2_FRONT_GGAIN1_PRE_UMSK                               (~(((1U<<DSP2_FRONT_GGAIN1_PRE_LEN)-1)<<DSP2_FRONT_GGAIN1_PRE_POS))

/* 0x154 : gain_B */
#define DSP2_FRONT_GAIN_B_OFFSET                                 (0x154)
#define DSP2_FRONT_BGAIN1_PRE                                    DSP2_FRONT_BGAIN1_PRE
#define DSP2_FRONT_BGAIN1_PRE_POS                                (0U)
#define DSP2_FRONT_BGAIN1_PRE_LEN                                (11U)
#define DSP2_FRONT_BGAIN1_PRE_MSK                                (((1U<<DSP2_FRONT_BGAIN1_PRE_LEN)-1)<<DSP2_FRONT_BGAIN1_PRE_POS)
#define DSP2_FRONT_BGAIN1_PRE_UMSK                               (~(((1U<<DSP2_FRONT_BGAIN1_PRE_LEN)-1)<<DSP2_FRONT_BGAIN1_PRE_POS))

/* 0x158 : gain2_R_G */
#define DSP2_FRONT_GAIN2_R_G_OFFSET                              (0x158)
#define DSP2_FRONT_RGAIN2_PRE                                    DSP2_FRONT_RGAIN2_PRE
#define DSP2_FRONT_RGAIN2_PRE_POS                                (0U)
#define DSP2_FRONT_RGAIN2_PRE_LEN                                (11U)
#define DSP2_FRONT_RGAIN2_PRE_MSK                                (((1U<<DSP2_FRONT_RGAIN2_PRE_LEN)-1)<<DSP2_FRONT_RGAIN2_PRE_POS)
#define DSP2_FRONT_RGAIN2_PRE_UMSK                               (~(((1U<<DSP2_FRONT_RGAIN2_PRE_LEN)-1)<<DSP2_FRONT_RGAIN2_PRE_POS))
#define DSP2_FRONT_GGAIN2_PRE                                    DSP2_FRONT_GGAIN2_PRE
#define DSP2_FRONT_GGAIN2_PRE_POS                                (16U)
#define DSP2_FRONT_GGAIN2_PRE_LEN                                (11U)
#define DSP2_FRONT_GGAIN2_PRE_MSK                                (((1U<<DSP2_FRONT_GGAIN2_PRE_LEN)-1)<<DSP2_FRONT_GGAIN2_PRE_POS)
#define DSP2_FRONT_GGAIN2_PRE_UMSK                               (~(((1U<<DSP2_FRONT_GGAIN2_PRE_LEN)-1)<<DSP2_FRONT_GGAIN2_PRE_POS))

/* 0x15C : gain2_B */
#define DSP2_FRONT_GAIN2_B_OFFSET                                (0x15C)
#define DSP2_FRONT_BGAIN2_PRE                                    DSP2_FRONT_BGAIN2_PRE
#define DSP2_FRONT_BGAIN2_PRE_POS                                (0U)
#define DSP2_FRONT_BGAIN2_PRE_LEN                                (11U)
#define DSP2_FRONT_BGAIN2_PRE_MSK                                (((1U<<DSP2_FRONT_BGAIN2_PRE_LEN)-1)<<DSP2_FRONT_BGAIN2_PRE_POS)
#define DSP2_FRONT_BGAIN2_PRE_UMSK                               (~(((1U<<DSP2_FRONT_BGAIN2_PRE_LEN)-1)<<DSP2_FRONT_BGAIN2_PRE_POS))

/* 0x174 : Bright_coeff_A */
#define DSP2_FRONT_BRIGHT_COEFF_A_OFFSET                         (0x174)
#define DSP2_FRONT_B0_AVC_PRE                                    DSP2_FRONT_B0_AVC_PRE
#define DSP2_FRONT_B0_AVC_PRE_POS                                (16U)
#define DSP2_FRONT_B0_AVC_PRE_LEN                                (8U)
#define DSP2_FRONT_B0_AVC_PRE_MSK                                (((1U<<DSP2_FRONT_B0_AVC_PRE_LEN)-1)<<DSP2_FRONT_B0_AVC_PRE_POS)
#define DSP2_FRONT_B0_AVC_PRE_UMSK                               (~(((1U<<DSP2_FRONT_B0_AVC_PRE_LEN)-1)<<DSP2_FRONT_B0_AVC_PRE_POS))
#define DSP2_FRONT_B1_AVC_PRE                                    DSP2_FRONT_B1_AVC_PRE
#define DSP2_FRONT_B1_AVC_PRE_POS                                (24U)
#define DSP2_FRONT_B1_AVC_PRE_LEN                                (8U)
#define DSP2_FRONT_B1_AVC_PRE_MSK                                (((1U<<DSP2_FRONT_B1_AVC_PRE_LEN)-1)<<DSP2_FRONT_B1_AVC_PRE_POS)
#define DSP2_FRONT_B1_AVC_PRE_UMSK                               (~(((1U<<DSP2_FRONT_B1_AVC_PRE_LEN)-1)<<DSP2_FRONT_B1_AVC_PRE_POS))

/* 0x178 : Bright_coeff_B */
#define DSP2_FRONT_BRIGHT_COEFF_B_OFFSET                         (0x178)
#define DSP2_FRONT_B2_AVC_PRE                                    DSP2_FRONT_B2_AVC_PRE
#define DSP2_FRONT_B2_AVC_PRE_POS                                (0U)
#define DSP2_FRONT_B2_AVC_PRE_LEN                                (8U)
#define DSP2_FRONT_B2_AVC_PRE_MSK                                (((1U<<DSP2_FRONT_B2_AVC_PRE_LEN)-1)<<DSP2_FRONT_B2_AVC_PRE_POS)
#define DSP2_FRONT_B2_AVC_PRE_UMSK                               (~(((1U<<DSP2_FRONT_B2_AVC_PRE_LEN)-1)<<DSP2_FRONT_B2_AVC_PRE_POS))
#define DSP2_FRONT_B3_AVC_PRE                                    DSP2_FRONT_B3_AVC_PRE
#define DSP2_FRONT_B3_AVC_PRE_POS                                (8U)
#define DSP2_FRONT_B3_AVC_PRE_LEN                                (8U)
#define DSP2_FRONT_B3_AVC_PRE_MSK                                (((1U<<DSP2_FRONT_B3_AVC_PRE_LEN)-1)<<DSP2_FRONT_B3_AVC_PRE_POS)
#define DSP2_FRONT_B3_AVC_PRE_UMSK                               (~(((1U<<DSP2_FRONT_B3_AVC_PRE_LEN)-1)<<DSP2_FRONT_B3_AVC_PRE_POS))
#define DSP2_FRONT_B4_AVC_PRE                                    DSP2_FRONT_B4_AVC_PRE
#define DSP2_FRONT_B4_AVC_PRE_POS                                (16U)
#define DSP2_FRONT_B4_AVC_PRE_LEN                                (8U)
#define DSP2_FRONT_B4_AVC_PRE_MSK                                (((1U<<DSP2_FRONT_B4_AVC_PRE_LEN)-1)<<DSP2_FRONT_B4_AVC_PRE_POS)
#define DSP2_FRONT_B4_AVC_PRE_UMSK                               (~(((1U<<DSP2_FRONT_B4_AVC_PRE_LEN)-1)<<DSP2_FRONT_B4_AVC_PRE_POS))
#define DSP2_FRONT_B5_AVC_PRE                                    DSP2_FRONT_B5_AVC_PRE
#define DSP2_FRONT_B5_AVC_PRE_POS                                (24U)
#define DSP2_FRONT_B5_AVC_PRE_LEN                                (8U)
#define DSP2_FRONT_B5_AVC_PRE_MSK                                (((1U<<DSP2_FRONT_B5_AVC_PRE_LEN)-1)<<DSP2_FRONT_B5_AVC_PRE_POS)
#define DSP2_FRONT_B5_AVC_PRE_UMSK                               (~(((1U<<DSP2_FRONT_B5_AVC_PRE_LEN)-1)<<DSP2_FRONT_B5_AVC_PRE_POS))

/* 0x180 : ex_win */
#define DSP2_FRONT_EX_WIN_OFFSET                                 (0x180)
#define DSP2_FRONT_EXWSX_PRE                                     DSP2_FRONT_EXWSX_PRE
#define DSP2_FRONT_EXWSX_PRE_POS                                 (0U)
#define DSP2_FRONT_EXWSX_PRE_LEN                                 (8U)
#define DSP2_FRONT_EXWSX_PRE_MSK                                 (((1U<<DSP2_FRONT_EXWSX_PRE_LEN)-1)<<DSP2_FRONT_EXWSX_PRE_POS)
#define DSP2_FRONT_EXWSX_PRE_UMSK                                (~(((1U<<DSP2_FRONT_EXWSX_PRE_LEN)-1)<<DSP2_FRONT_EXWSX_PRE_POS))
#define DSP2_FRONT_EXWSY_PRE                                     DSP2_FRONT_EXWSY_PRE
#define DSP2_FRONT_EXWSY_PRE_POS                                 (8U)
#define DSP2_FRONT_EXWSY_PRE_LEN                                 (8U)
#define DSP2_FRONT_EXWSY_PRE_MSK                                 (((1U<<DSP2_FRONT_EXWSY_PRE_LEN)-1)<<DSP2_FRONT_EXWSY_PRE_POS)
#define DSP2_FRONT_EXWSY_PRE_UMSK                                (~(((1U<<DSP2_FRONT_EXWSY_PRE_LEN)-1)<<DSP2_FRONT_EXWSY_PRE_POS))
#define DSP2_FRONT_EXWEX_PRE                                     DSP2_FRONT_EXWEX_PRE
#define DSP2_FRONT_EXWEX_PRE_POS                                 (16U)
#define DSP2_FRONT_EXWEX_PRE_LEN                                 (8U)
#define DSP2_FRONT_EXWEX_PRE_MSK                                 (((1U<<DSP2_FRONT_EXWEX_PRE_LEN)-1)<<DSP2_FRONT_EXWEX_PRE_POS)
#define DSP2_FRONT_EXWEX_PRE_UMSK                                (~(((1U<<DSP2_FRONT_EXWEX_PRE_LEN)-1)<<DSP2_FRONT_EXWEX_PRE_POS))
#define DSP2_FRONT_EXWEY_PRE                                     DSP2_FRONT_EXWEY_PRE
#define DSP2_FRONT_EXWEY_PRE_POS                                 (24U)
#define DSP2_FRONT_EXWEY_PRE_LEN                                 (8U)
#define DSP2_FRONT_EXWEY_PRE_MSK                                 (((1U<<DSP2_FRONT_EXWEY_PRE_LEN)-1)<<DSP2_FRONT_EXWEY_PRE_POS)
#define DSP2_FRONT_EXWEY_PRE_UMSK                                (~(((1U<<DSP2_FRONT_EXWEY_PRE_LEN)-1)<<DSP2_FRONT_EXWEY_PRE_POS))

/* 0x184 : ex_limit1 */
#define DSP2_FRONT_EX_LIMIT1_OFFSET                              (0x184)
#define DSP2_FRONT_UNEX_MIN1_PRE                                 DSP2_FRONT_UNEX_MIN1_PRE
#define DSP2_FRONT_UNEX_MIN1_PRE_POS                             (0U)
#define DSP2_FRONT_UNEX_MIN1_PRE_LEN                             (8U)
#define DSP2_FRONT_UNEX_MIN1_PRE_MSK                             (((1U<<DSP2_FRONT_UNEX_MIN1_PRE_LEN)-1)<<DSP2_FRONT_UNEX_MIN1_PRE_POS)
#define DSP2_FRONT_UNEX_MIN1_PRE_UMSK                            (~(((1U<<DSP2_FRONT_UNEX_MIN1_PRE_LEN)-1)<<DSP2_FRONT_UNEX_MIN1_PRE_POS))
#define DSP2_FRONT_UNEX_MAX1_PRE                                 DSP2_FRONT_UNEX_MAX1_PRE
#define DSP2_FRONT_UNEX_MAX1_PRE_POS                             (8U)
#define DSP2_FRONT_UNEX_MAX1_PRE_LEN                             (8U)
#define DSP2_FRONT_UNEX_MAX1_PRE_MSK                             (((1U<<DSP2_FRONT_UNEX_MAX1_PRE_LEN)-1)<<DSP2_FRONT_UNEX_MAX1_PRE_POS)
#define DSP2_FRONT_UNEX_MAX1_PRE_UMSK                            (~(((1U<<DSP2_FRONT_UNEX_MAX1_PRE_LEN)-1)<<DSP2_FRONT_UNEX_MAX1_PRE_POS))
#define DSP2_FRONT_OVEX_MIN1_PRE                                 DSP2_FRONT_OVEX_MIN1_PRE
#define DSP2_FRONT_OVEX_MIN1_PRE_POS                             (16U)
#define DSP2_FRONT_OVEX_MIN1_PRE_LEN                             (8U)
#define DSP2_FRONT_OVEX_MIN1_PRE_MSK                             (((1U<<DSP2_FRONT_OVEX_MIN1_PRE_LEN)-1)<<DSP2_FRONT_OVEX_MIN1_PRE_POS)
#define DSP2_FRONT_OVEX_MIN1_PRE_UMSK                            (~(((1U<<DSP2_FRONT_OVEX_MIN1_PRE_LEN)-1)<<DSP2_FRONT_OVEX_MIN1_PRE_POS))
#define DSP2_FRONT_OVEX_MAX1_PRE                                 DSP2_FRONT_OVEX_MAX1_PRE
#define DSP2_FRONT_OVEX_MAX1_PRE_POS                             (24U)
#define DSP2_FRONT_OVEX_MAX1_PRE_LEN                             (8U)
#define DSP2_FRONT_OVEX_MAX1_PRE_MSK                             (((1U<<DSP2_FRONT_OVEX_MAX1_PRE_LEN)-1)<<DSP2_FRONT_OVEX_MAX1_PRE_POS)
#define DSP2_FRONT_OVEX_MAX1_PRE_UMSK                            (~(((1U<<DSP2_FRONT_OVEX_MAX1_PRE_LEN)-1)<<DSP2_FRONT_OVEX_MAX1_PRE_POS))

/* 0x188 : Unex_sum1 */
#define DSP2_FRONT_UNEX_SUM1_OFFSET                              (0x188)
#define DSP2_FRONT_UNEX_SUM1_R                                   DSP2_FRONT_UNEX_SUM1_R
#define DSP2_FRONT_UNEX_SUM1_R_POS                               (0U)
#define DSP2_FRONT_UNEX_SUM1_R_LEN                               (20U)
#define DSP2_FRONT_UNEX_SUM1_R_MSK                               (((1U<<DSP2_FRONT_UNEX_SUM1_R_LEN)-1)<<DSP2_FRONT_UNEX_SUM1_R_POS)
#define DSP2_FRONT_UNEX_SUM1_R_UMSK                              (~(((1U<<DSP2_FRONT_UNEX_SUM1_R_LEN)-1)<<DSP2_FRONT_UNEX_SUM1_R_POS))

/* 0x18C : Ovex_sum1 */
#define DSP2_FRONT_OVEX_SUM1_OFFSET                              (0x18C)
#define DSP2_FRONT_OVEX_SUM1_R                                   DSP2_FRONT_OVEX_SUM1_R
#define DSP2_FRONT_OVEX_SUM1_R_POS                               (0U)
#define DSP2_FRONT_OVEX_SUM1_R_LEN                               (20U)
#define DSP2_FRONT_OVEX_SUM1_R_MSK                               (((1U<<DSP2_FRONT_OVEX_SUM1_R_LEN)-1)<<DSP2_FRONT_OVEX_SUM1_R_POS)
#define DSP2_FRONT_OVEX_SUM1_R_UMSK                              (~(((1U<<DSP2_FRONT_OVEX_SUM1_R_LEN)-1)<<DSP2_FRONT_OVEX_SUM1_R_POS))

/* 0x190 : ex_limit2 */
#define DSP2_FRONT_EX_LIMIT2_OFFSET                              (0x190)
#define DSP2_FRONT_UNEX_MIN2_PRE                                 DSP2_FRONT_UNEX_MIN2_PRE
#define DSP2_FRONT_UNEX_MIN2_PRE_POS                             (0U)
#define DSP2_FRONT_UNEX_MIN2_PRE_LEN                             (8U)
#define DSP2_FRONT_UNEX_MIN2_PRE_MSK                             (((1U<<DSP2_FRONT_UNEX_MIN2_PRE_LEN)-1)<<DSP2_FRONT_UNEX_MIN2_PRE_POS)
#define DSP2_FRONT_UNEX_MIN2_PRE_UMSK                            (~(((1U<<DSP2_FRONT_UNEX_MIN2_PRE_LEN)-1)<<DSP2_FRONT_UNEX_MIN2_PRE_POS))
#define DSP2_FRONT_UNEX_MAX2_PRE                                 DSP2_FRONT_UNEX_MAX2_PRE
#define DSP2_FRONT_UNEX_MAX2_PRE_POS                             (8U)
#define DSP2_FRONT_UNEX_MAX2_PRE_LEN                             (8U)
#define DSP2_FRONT_UNEX_MAX2_PRE_MSK                             (((1U<<DSP2_FRONT_UNEX_MAX2_PRE_LEN)-1)<<DSP2_FRONT_UNEX_MAX2_PRE_POS)
#define DSP2_FRONT_UNEX_MAX2_PRE_UMSK                            (~(((1U<<DSP2_FRONT_UNEX_MAX2_PRE_LEN)-1)<<DSP2_FRONT_UNEX_MAX2_PRE_POS))
#define DSP2_FRONT_OVEX_MIN2_PRE                                 DSP2_FRONT_OVEX_MIN2_PRE
#define DSP2_FRONT_OVEX_MIN2_PRE_POS                             (16U)
#define DSP2_FRONT_OVEX_MIN2_PRE_LEN                             (8U)
#define DSP2_FRONT_OVEX_MIN2_PRE_MSK                             (((1U<<DSP2_FRONT_OVEX_MIN2_PRE_LEN)-1)<<DSP2_FRONT_OVEX_MIN2_PRE_POS)
#define DSP2_FRONT_OVEX_MIN2_PRE_UMSK                            (~(((1U<<DSP2_FRONT_OVEX_MIN2_PRE_LEN)-1)<<DSP2_FRONT_OVEX_MIN2_PRE_POS))
#define DSP2_FRONT_OVEX_MAX2_PRE                                 DSP2_FRONT_OVEX_MAX2_PRE
#define DSP2_FRONT_OVEX_MAX2_PRE_POS                             (24U)
#define DSP2_FRONT_OVEX_MAX2_PRE_LEN                             (8U)
#define DSP2_FRONT_OVEX_MAX2_PRE_MSK                             (((1U<<DSP2_FRONT_OVEX_MAX2_PRE_LEN)-1)<<DSP2_FRONT_OVEX_MAX2_PRE_POS)
#define DSP2_FRONT_OVEX_MAX2_PRE_UMSK                            (~(((1U<<DSP2_FRONT_OVEX_MAX2_PRE_LEN)-1)<<DSP2_FRONT_OVEX_MAX2_PRE_POS))

/* 0x194 : Unex_sum2 */
#define DSP2_FRONT_UNEX_SUM2_OFFSET                              (0x194)
#define DSP2_FRONT_UNEX_SUM2_R                                   DSP2_FRONT_UNEX_SUM2_R
#define DSP2_FRONT_UNEX_SUM2_R_POS                               (0U)
#define DSP2_FRONT_UNEX_SUM2_R_LEN                               (20U)
#define DSP2_FRONT_UNEX_SUM2_R_MSK                               (((1U<<DSP2_FRONT_UNEX_SUM2_R_LEN)-1)<<DSP2_FRONT_UNEX_SUM2_R_POS)
#define DSP2_FRONT_UNEX_SUM2_R_UMSK                              (~(((1U<<DSP2_FRONT_UNEX_SUM2_R_LEN)-1)<<DSP2_FRONT_UNEX_SUM2_R_POS))

/* 0x198 : Ovex_sum2 */
#define DSP2_FRONT_OVEX_SUM2_OFFSET                              (0x198)
#define DSP2_FRONT_OVEX_SUM2_R                                   DSP2_FRONT_OVEX_SUM2_R
#define DSP2_FRONT_OVEX_SUM2_R_POS                               (0U)
#define DSP2_FRONT_OVEX_SUM2_R_LEN                               (20U)
#define DSP2_FRONT_OVEX_SUM2_R_MSK                               (((1U<<DSP2_FRONT_OVEX_SUM2_R_LEN)-1)<<DSP2_FRONT_OVEX_SUM2_R_POS)
#define DSP2_FRONT_OVEX_SUM2_R_UMSK                              (~(((1U<<DSP2_FRONT_OVEX_SUM2_R_LEN)-1)<<DSP2_FRONT_OVEX_SUM2_R_POS))

/* 0x1A0 : HDR_1 */
#define DSP2_FRONT_HDR_1_OFFSET                                  (0x1A0)
#define DSP2_FRONT_HDR_ON_OFF_PRE                                DSP2_FRONT_HDR_ON_OFF_PRE
#define DSP2_FRONT_HDR_ON_OFF_PRE_POS                            (0U)
#define DSP2_FRONT_HDR_ON_OFF_PRE_LEN                            (1U)
#define DSP2_FRONT_HDR_ON_OFF_PRE_MSK                            (((1U<<DSP2_FRONT_HDR_ON_OFF_PRE_LEN)-1)<<DSP2_FRONT_HDR_ON_OFF_PRE_POS)
#define DSP2_FRONT_HDR_ON_OFF_PRE_UMSK                           (~(((1U<<DSP2_FRONT_HDR_ON_OFF_PRE_LEN)-1)<<DSP2_FRONT_HDR_ON_OFF_PRE_POS))
#define DSP2_FRONT_EXPOSURE_RATE_PRE                             DSP2_FRONT_EXPOSURE_RATE_PRE
#define DSP2_FRONT_EXPOSURE_RATE_PRE_POS                         (8U)
#define DSP2_FRONT_EXPOSURE_RATE_PRE_LEN                         (3U)
#define DSP2_FRONT_EXPOSURE_RATE_PRE_MSK                         (((1U<<DSP2_FRONT_EXPOSURE_RATE_PRE_LEN)-1)<<DSP2_FRONT_EXPOSURE_RATE_PRE_POS)
#define DSP2_FRONT_EXPOSURE_RATE_PRE_UMSK                        (~(((1U<<DSP2_FRONT_EXPOSURE_RATE_PRE_LEN)-1)<<DSP2_FRONT_EXPOSURE_RATE_PRE_POS))
#define DSP2_FRONT_GHOST_THRESHOLD_PRE                           DSP2_FRONT_GHOST_THRESHOLD_PRE
#define DSP2_FRONT_GHOST_THRESHOLD_PRE_POS                       (16U)
#define DSP2_FRONT_GHOST_THRESHOLD_PRE_LEN                       (8U)
#define DSP2_FRONT_GHOST_THRESHOLD_PRE_MSK                       (((1U<<DSP2_FRONT_GHOST_THRESHOLD_PRE_LEN)-1)<<DSP2_FRONT_GHOST_THRESHOLD_PRE_POS)
#define DSP2_FRONT_GHOST_THRESHOLD_PRE_UMSK                      (~(((1U<<DSP2_FRONT_GHOST_THRESHOLD_PRE_LEN)-1)<<DSP2_FRONT_GHOST_THRESHOLD_PRE_POS))
#define DSP2_FRONT_DILATIONTHRESHOLD_PRE                         DSP2_FRONT_DILATIONTHRESHOLD_PRE
#define DSP2_FRONT_DILATIONTHRESHOLD_PRE_POS                     (24U)
#define DSP2_FRONT_DILATIONTHRESHOLD_PRE_LEN                     (8U)
#define DSP2_FRONT_DILATIONTHRESHOLD_PRE_MSK                     (((1U<<DSP2_FRONT_DILATIONTHRESHOLD_PRE_LEN)-1)<<DSP2_FRONT_DILATIONTHRESHOLD_PRE_POS)
#define DSP2_FRONT_DILATIONTHRESHOLD_PRE_UMSK                    (~(((1U<<DSP2_FRONT_DILATIONTHRESHOLD_PRE_LEN)-1)<<DSP2_FRONT_DILATIONTHRESHOLD_PRE_POS))

/* 0x1A4 : HDR_2 */
#define DSP2_FRONT_HDR_2_OFFSET                                  (0x1A4)
#define DSP2_FRONT_GHOST_REMOVE_PRE                              DSP2_FRONT_GHOST_REMOVE_PRE
#define DSP2_FRONT_GHOST_REMOVE_PRE_POS                          (0U)
#define DSP2_FRONT_GHOST_REMOVE_PRE_LEN                          (1U)
#define DSP2_FRONT_GHOST_REMOVE_PRE_MSK                          (((1U<<DSP2_FRONT_GHOST_REMOVE_PRE_LEN)-1)<<DSP2_FRONT_GHOST_REMOVE_PRE_POS)
#define DSP2_FRONT_GHOST_REMOVE_PRE_UMSK                         (~(((1U<<DSP2_FRONT_GHOST_REMOVE_PRE_LEN)-1)<<DSP2_FRONT_GHOST_REMOVE_PRE_POS))
#define DSP2_FRONT_HSTRENGTH_PRE                                 DSP2_FRONT_HSTRENGTH_PRE
#define DSP2_FRONT_HSTRENGTH_PRE_POS                             (8U)
#define DSP2_FRONT_HSTRENGTH_PRE_LEN                             (4U)
#define DSP2_FRONT_HSTRENGTH_PRE_MSK                             (((1U<<DSP2_FRONT_HSTRENGTH_PRE_LEN)-1)<<DSP2_FRONT_HSTRENGTH_PRE_POS)
#define DSP2_FRONT_HSTRENGTH_PRE_UMSK                            (~(((1U<<DSP2_FRONT_HSTRENGTH_PRE_LEN)-1)<<DSP2_FRONT_HSTRENGTH_PRE_POS))
#define DSP2_FRONT_SETRMAPMIN_PRE                                DSP2_FRONT_SETRMAPMIN_PRE
#define DSP2_FRONT_SETRMAPMIN_PRE_POS                            (16U)
#define DSP2_FRONT_SETRMAPMIN_PRE_LEN                            (8U)
#define DSP2_FRONT_SETRMAPMIN_PRE_MSK                            (((1U<<DSP2_FRONT_SETRMAPMIN_PRE_LEN)-1)<<DSP2_FRONT_SETRMAPMIN_PRE_POS)
#define DSP2_FRONT_SETRMAPMIN_PRE_UMSK                           (~(((1U<<DSP2_FRONT_SETRMAPMIN_PRE_LEN)-1)<<DSP2_FRONT_SETRMAPMIN_PRE_POS))
#define DSP2_FRONT_RADIANCEMAPMODE_PRE                           DSP2_FRONT_RADIANCEMAPMODE_PRE
#define DSP2_FRONT_RADIANCEMAPMODE_PRE_POS                       (24U)
#define DSP2_FRONT_RADIANCEMAPMODE_PRE_LEN                       (2U)
#define DSP2_FRONT_RADIANCEMAPMODE_PRE_MSK                       (((1U<<DSP2_FRONT_RADIANCEMAPMODE_PRE_LEN)-1)<<DSP2_FRONT_RADIANCEMAPMODE_PRE_POS)
#define DSP2_FRONT_RADIANCEMAPMODE_PRE_UMSK                      (~(((1U<<DSP2_FRONT_RADIANCEMAPMODE_PRE_LEN)-1)<<DSP2_FRONT_RADIANCEMAPMODE_PRE_POS))
#define DSP2_FRONT_AUTOSETRMAPMAX_PRE                            DSP2_FRONT_AUTOSETRMAPMAX_PRE
#define DSP2_FRONT_AUTOSETRMAPMAX_PRE_POS                        (31U)
#define DSP2_FRONT_AUTOSETRMAPMAX_PRE_LEN                        (1U)
#define DSP2_FRONT_AUTOSETRMAPMAX_PRE_MSK                        (((1U<<DSP2_FRONT_AUTOSETRMAPMAX_PRE_LEN)-1)<<DSP2_FRONT_AUTOSETRMAPMAX_PRE_POS)
#define DSP2_FRONT_AUTOSETRMAPMAX_PRE_UMSK                       (~(((1U<<DSP2_FRONT_AUTOSETRMAPMAX_PRE_LEN)-1)<<DSP2_FRONT_AUTOSETRMAPMAX_PRE_POS))

/* 0x1A8 : HDR_3 */
#define DSP2_FRONT_HDR_3_OFFSET                                  (0x1A8)
#define DSP2_FRONT_SETRMAPMAX_PRE                                DSP2_FRONT_SETRMAPMAX_PRE
#define DSP2_FRONT_SETRMAPMAX_PRE_POS                            (0U)
#define DSP2_FRONT_SETRMAPMAX_PRE_LEN                            (24U)
#define DSP2_FRONT_SETRMAPMAX_PRE_MSK                            (((1U<<DSP2_FRONT_SETRMAPMAX_PRE_LEN)-1)<<DSP2_FRONT_SETRMAPMAX_PRE_POS)
#define DSP2_FRONT_SETRMAPMAX_PRE_UMSK                           (~(((1U<<DSP2_FRONT_SETRMAPMAX_PRE_LEN)-1)<<DSP2_FRONT_SETRMAPMAX_PRE_POS))

/* 0x1AC : HDR_4 */
#define DSP2_FRONT_HDR_4_OFFSET                                  (0x1AC)
#define DSP2_FRONT_RMAPMAX_R                                     DSP2_FRONT_RMAPMAX_R
#define DSP2_FRONT_RMAPMAX_R_POS                                 (0U)
#define DSP2_FRONT_RMAPMAX_R_LEN                                 (24U)
#define DSP2_FRONT_RMAPMAX_R_MSK                                 (((1U<<DSP2_FRONT_RMAPMAX_R_LEN)-1)<<DSP2_FRONT_RMAPMAX_R_POS)
#define DSP2_FRONT_RMAPMAX_R_UMSK                                (~(((1U<<DSP2_FRONT_RMAPMAX_R_LEN)-1)<<DSP2_FRONT_RMAPMAX_R_POS))

/* 0x1B0 : SH_1 */
#define DSP2_FRONT_SH_1_OFFSET                                   (0x1B0)
#define DSP2_FRONT_HIGHLIGHTCOMPESATIONMODE_PRE                  DSP2_FRONT_HIGHLIGHTCOMPESATIONMODE_PRE
#define DSP2_FRONT_HIGHLIGHTCOMPESATIONMODE_PRE_POS              (0U)
#define DSP2_FRONT_HIGHLIGHTCOMPESATIONMODE_PRE_LEN              (1U)
#define DSP2_FRONT_HIGHLIGHTCOMPESATIONMODE_PRE_MSK              (((1U<<DSP2_FRONT_HIGHLIGHTCOMPESATIONMODE_PRE_LEN)-1)<<DSP2_FRONT_HIGHLIGHTCOMPESATIONMODE_PRE_POS)
#define DSP2_FRONT_HIGHLIGHTCOMPESATIONMODE_PRE_UMSK             (~(((1U<<DSP2_FRONT_HIGHLIGHTCOMPESATIONMODE_PRE_LEN)-1)<<DSP2_FRONT_HIGHLIGHTCOMPESATIONMODE_PRE_POS))
#define DSP2_FRONT_AUTOHIGHTLIGHTCOMPENSATION_PRE                DSP2_FRONT_AUTOHIGHTLIGHTCOMPENSATION_PRE
#define DSP2_FRONT_AUTOHIGHTLIGHTCOMPENSATION_PRE_POS            (1U)
#define DSP2_FRONT_AUTOHIGHTLIGHTCOMPENSATION_PRE_LEN            (1U)
#define DSP2_FRONT_AUTOHIGHTLIGHTCOMPENSATION_PRE_MSK            (((1U<<DSP2_FRONT_AUTOHIGHTLIGHTCOMPENSATION_PRE_LEN)-1)<<DSP2_FRONT_AUTOHIGHTLIGHTCOMPENSATION_PRE_POS)
#define DSP2_FRONT_AUTOHIGHTLIGHTCOMPENSATION_PRE_UMSK           (~(((1U<<DSP2_FRONT_AUTOHIGHTLIGHTCOMPENSATION_PRE_LEN)-1)<<DSP2_FRONT_AUTOHIGHTLIGHTCOMPENSATION_PRE_POS))
#define DSP2_FRONT_SHADOWCOMPESATIONMODE_PRE                     DSP2_FRONT_SHADOWCOMPESATIONMODE_PRE
#define DSP2_FRONT_SHADOWCOMPESATIONMODE_PRE_POS                 (2U)
#define DSP2_FRONT_SHADOWCOMPESATIONMODE_PRE_LEN                 (1U)
#define DSP2_FRONT_SHADOWCOMPESATIONMODE_PRE_MSK                 (((1U<<DSP2_FRONT_SHADOWCOMPESATIONMODE_PRE_LEN)-1)<<DSP2_FRONT_SHADOWCOMPESATIONMODE_PRE_POS)
#define DSP2_FRONT_SHADOWCOMPESATIONMODE_PRE_UMSK                (~(((1U<<DSP2_FRONT_SHADOWCOMPESATIONMODE_PRE_LEN)-1)<<DSP2_FRONT_SHADOWCOMPESATIONMODE_PRE_POS))
#define DSP2_FRONT_AUTOSHADOWCOMPENSATION_PRE                    DSP2_FRONT_AUTOSHADOWCOMPENSATION_PRE
#define DSP2_FRONT_AUTOSHADOWCOMPENSATION_PRE_POS                (3U)
#define DSP2_FRONT_AUTOSHADOWCOMPENSATION_PRE_LEN                (1U)
#define DSP2_FRONT_AUTOSHADOWCOMPENSATION_PRE_MSK                (((1U<<DSP2_FRONT_AUTOSHADOWCOMPENSATION_PRE_LEN)-1)<<DSP2_FRONT_AUTOSHADOWCOMPENSATION_PRE_POS)
#define DSP2_FRONT_AUTOSHADOWCOMPENSATION_PRE_UMSK               (~(((1U<<DSP2_FRONT_AUTOSHADOWCOMPENSATION_PRE_LEN)-1)<<DSP2_FRONT_AUTOSHADOWCOMPENSATION_PRE_POS))
#define DSP2_FRONT_SETSHADOWSTRENGTH_PRE                         DSP2_FRONT_SETSHADOWSTRENGTH_PRE
#define DSP2_FRONT_SETSHADOWSTRENGTH_PRE_POS                     (8U)
#define DSP2_FRONT_SETSHADOWSTRENGTH_PRE_LEN                     (8U)
#define DSP2_FRONT_SETSHADOWSTRENGTH_PRE_MSK                     (((1U<<DSP2_FRONT_SETSHADOWSTRENGTH_PRE_LEN)-1)<<DSP2_FRONT_SETSHADOWSTRENGTH_PRE_POS)
#define DSP2_FRONT_SETSHADOWSTRENGTH_PRE_UMSK                    (~(((1U<<DSP2_FRONT_SETSHADOWSTRENGTH_PRE_LEN)-1)<<DSP2_FRONT_SETSHADOWSTRENGTH_PRE_POS))
#define DSP2_FRONT_SETSHADOWRANGE_PRE                            DSP2_FRONT_SETSHADOWRANGE_PRE
#define DSP2_FRONT_SETSHADOWRANGE_PRE_POS                        (16U)
#define DSP2_FRONT_SETSHADOWRANGE_PRE_LEN                        (7U)
#define DSP2_FRONT_SETSHADOWRANGE_PRE_MSK                        (((1U<<DSP2_FRONT_SETSHADOWRANGE_PRE_LEN)-1)<<DSP2_FRONT_SETSHADOWRANGE_PRE_POS)
#define DSP2_FRONT_SETSHADOWRANGE_PRE_UMSK                       (~(((1U<<DSP2_FRONT_SETSHADOWRANGE_PRE_LEN)-1)<<DSP2_FRONT_SETSHADOWRANGE_PRE_POS))
#define DSP2_FRONT_SETHIGHLITSTRENGTH_PRE                        DSP2_FRONT_SETHIGHLITSTRENGTH_PRE
#define DSP2_FRONT_SETHIGHLITSTRENGTH_PRE_POS                    (24U)
#define DSP2_FRONT_SETHIGHLITSTRENGTH_PRE_LEN                    (8U)
#define DSP2_FRONT_SETHIGHLITSTRENGTH_PRE_MSK                    (((1U<<DSP2_FRONT_SETHIGHLITSTRENGTH_PRE_LEN)-1)<<DSP2_FRONT_SETHIGHLITSTRENGTH_PRE_POS)
#define DSP2_FRONT_SETHIGHLITSTRENGTH_PRE_UMSK                   (~(((1U<<DSP2_FRONT_SETHIGHLITSTRENGTH_PRE_LEN)-1)<<DSP2_FRONT_SETHIGHLITSTRENGTH_PRE_POS))

/* 0x1B4 : SH_2 */
#define DSP2_FRONT_SH_2_OFFSET                                   (0x1B4)
#define DSP2_FRONT_SETHIGHLITRANGE_PRE                           DSP2_FRONT_SETHIGHLITRANGE_PRE
#define DSP2_FRONT_SETHIGHLITRANGE_PRE_POS                       (0U)
#define DSP2_FRONT_SETHIGHLITRANGE_PRE_LEN                       (7U)
#define DSP2_FRONT_SETHIGHLITRANGE_PRE_MSK                       (((1U<<DSP2_FRONT_SETHIGHLITRANGE_PRE_LEN)-1)<<DSP2_FRONT_SETHIGHLITRANGE_PRE_POS)
#define DSP2_FRONT_SETHIGHLITRANGE_PRE_UMSK                      (~(((1U<<DSP2_FRONT_SETHIGHLITRANGE_PRE_LEN)-1)<<DSP2_FRONT_SETHIGHLITRANGE_PRE_POS))
#define DSP2_FRONT_SHADOWSTRENGTHMULT_PRE                        DSP2_FRONT_SHADOWSTRENGTHMULT_PRE
#define DSP2_FRONT_SHADOWSTRENGTHMULT_PRE_POS                    (8U)
#define DSP2_FRONT_SHADOWSTRENGTHMULT_PRE_LEN                    (6U)
#define DSP2_FRONT_SHADOWSTRENGTHMULT_PRE_MSK                    (((1U<<DSP2_FRONT_SHADOWSTRENGTHMULT_PRE_LEN)-1)<<DSP2_FRONT_SHADOWSTRENGTHMULT_PRE_POS)
#define DSP2_FRONT_SHADOWSTRENGTHMULT_PRE_UMSK                   (~(((1U<<DSP2_FRONT_SHADOWSTRENGTHMULT_PRE_LEN)-1)<<DSP2_FRONT_SHADOWSTRENGTHMULT_PRE_POS))
#define DSP2_FRONT_SHADOWRANGEMULT_PRE                           DSP2_FRONT_SHADOWRANGEMULT_PRE
#define DSP2_FRONT_SHADOWRANGEMULT_PRE_POS                       (16U)
#define DSP2_FRONT_SHADOWRANGEMULT_PRE_LEN                       (6U)
#define DSP2_FRONT_SHADOWRANGEMULT_PRE_MSK                       (((1U<<DSP2_FRONT_SHADOWRANGEMULT_PRE_LEN)-1)<<DSP2_FRONT_SHADOWRANGEMULT_PRE_POS)
#define DSP2_FRONT_SHADOWRANGEMULT_PRE_UMSK                      (~(((1U<<DSP2_FRONT_SHADOWRANGEMULT_PRE_LEN)-1)<<DSP2_FRONT_SHADOWRANGEMULT_PRE_POS))
#define DSP2_FRONT_HIGHLITSTRENGTHMULT_PRE                       DSP2_FRONT_HIGHLITSTRENGTHMULT_PRE
#define DSP2_FRONT_HIGHLITSTRENGTHMULT_PRE_POS                   (24U)
#define DSP2_FRONT_HIGHLITSTRENGTHMULT_PRE_LEN                   (6U)
#define DSP2_FRONT_HIGHLITSTRENGTHMULT_PRE_MSK                   (((1U<<DSP2_FRONT_HIGHLITSTRENGTHMULT_PRE_LEN)-1)<<DSP2_FRONT_HIGHLITSTRENGTHMULT_PRE_POS)
#define DSP2_FRONT_HIGHLITSTRENGTHMULT_PRE_UMSK                  (~(((1U<<DSP2_FRONT_HIGHLITSTRENGTHMULT_PRE_LEN)-1)<<DSP2_FRONT_HIGHLITSTRENGTHMULT_PRE_POS))

/* 0x1B8 : SH_3 */
#define DSP2_FRONT_SH_3_OFFSET                                   (0x1B8)
#define DSP2_FRONT_HIGHLITRANGEMULT_PRE                          DSP2_FRONT_HIGHLITRANGEMULT_PRE
#define DSP2_FRONT_HIGHLITRANGEMULT_PRE_POS                      (0U)
#define DSP2_FRONT_HIGHLITRANGEMULT_PRE_LEN                      (6U)
#define DSP2_FRONT_HIGHLITRANGEMULT_PRE_MSK                      (((1U<<DSP2_FRONT_HIGHLITRANGEMULT_PRE_LEN)-1)<<DSP2_FRONT_HIGHLITRANGEMULT_PRE_POS)
#define DSP2_FRONT_HIGHLITRANGEMULT_PRE_UMSK                     (~(((1U<<DSP2_FRONT_HIGHLITRANGEMULT_PRE_LEN)-1)<<DSP2_FRONT_HIGHLITRANGEMULT_PRE_POS))
#define DSP2_FRONT_SHADOWSTRENGTH_R                              DSP2_FRONT_SHADOWSTRENGTH_R
#define DSP2_FRONT_SHADOWSTRENGTH_R_POS                          (8U)
#define DSP2_FRONT_SHADOWSTRENGTH_R_LEN                          (8U)
#define DSP2_FRONT_SHADOWSTRENGTH_R_MSK                          (((1U<<DSP2_FRONT_SHADOWSTRENGTH_R_LEN)-1)<<DSP2_FRONT_SHADOWSTRENGTH_R_POS)
#define DSP2_FRONT_SHADOWSTRENGTH_R_UMSK                         (~(((1U<<DSP2_FRONT_SHADOWSTRENGTH_R_LEN)-1)<<DSP2_FRONT_SHADOWSTRENGTH_R_POS))
#define DSP2_FRONT_HIGHLIGHTSTRENGTH_R                           DSP2_FRONT_HIGHLIGHTSTRENGTH_R
#define DSP2_FRONT_HIGHLIGHTSTRENGTH_R_POS                       (16U)
#define DSP2_FRONT_HIGHLIGHTSTRENGTH_R_LEN                       (8U)
#define DSP2_FRONT_HIGHLIGHTSTRENGTH_R_MSK                       (((1U<<DSP2_FRONT_HIGHLIGHTSTRENGTH_R_LEN)-1)<<DSP2_FRONT_HIGHLIGHTSTRENGTH_R_POS)
#define DSP2_FRONT_HIGHLIGHTSTRENGTH_R_UMSK                      (~(((1U<<DSP2_FRONT_HIGHLIGHTSTRENGTH_R_LEN)-1)<<DSP2_FRONT_HIGHLIGHTSTRENGTH_R_POS))

/* 0x1BC : ae_roi_x */
#define DSP2_FRONT_AE_ROI_X_OFFSET                               (0x1BC)
#define DSP2_FRONT_AE_ROI_START_X_PRE                            DSP2_FRONT_AE_ROI_START_X_PRE
#define DSP2_FRONT_AE_ROI_START_X_PRE_POS                        (0U)
#define DSP2_FRONT_AE_ROI_START_X_PRE_LEN                        (11U)
#define DSP2_FRONT_AE_ROI_START_X_PRE_MSK                        (((1U<<DSP2_FRONT_AE_ROI_START_X_PRE_LEN)-1)<<DSP2_FRONT_AE_ROI_START_X_PRE_POS)
#define DSP2_FRONT_AE_ROI_START_X_PRE_UMSK                       (~(((1U<<DSP2_FRONT_AE_ROI_START_X_PRE_LEN)-1)<<DSP2_FRONT_AE_ROI_START_X_PRE_POS))
#define DSP2_FRONT_AE_ROI_WIDTH_PRE                              DSP2_FRONT_AE_ROI_WIDTH_PRE
#define DSP2_FRONT_AE_ROI_WIDTH_PRE_POS                          (16U)
#define DSP2_FRONT_AE_ROI_WIDTH_PRE_LEN                          (11U)
#define DSP2_FRONT_AE_ROI_WIDTH_PRE_MSK                          (((1U<<DSP2_FRONT_AE_ROI_WIDTH_PRE_LEN)-1)<<DSP2_FRONT_AE_ROI_WIDTH_PRE_POS)
#define DSP2_FRONT_AE_ROI_WIDTH_PRE_UMSK                         (~(((1U<<DSP2_FRONT_AE_ROI_WIDTH_PRE_LEN)-1)<<DSP2_FRONT_AE_ROI_WIDTH_PRE_POS))

/* 0x1C0 : ae_roi_y */
#define DSP2_FRONT_AE_ROI_Y_OFFSET                               (0x1C0)
#define DSP2_FRONT_AE_ROI_START_Y_PRE                            DSP2_FRONT_AE_ROI_START_Y_PRE
#define DSP2_FRONT_AE_ROI_START_Y_PRE_POS                        (0U)
#define DSP2_FRONT_AE_ROI_START_Y_PRE_LEN                        (11U)
#define DSP2_FRONT_AE_ROI_START_Y_PRE_MSK                        (((1U<<DSP2_FRONT_AE_ROI_START_Y_PRE_LEN)-1)<<DSP2_FRONT_AE_ROI_START_Y_PRE_POS)
#define DSP2_FRONT_AE_ROI_START_Y_PRE_UMSK                       (~(((1U<<DSP2_FRONT_AE_ROI_START_Y_PRE_LEN)-1)<<DSP2_FRONT_AE_ROI_START_Y_PRE_POS))
#define DSP2_FRONT_AE_ROI_HEIGHT_PRE                             DSP2_FRONT_AE_ROI_HEIGHT_PRE
#define DSP2_FRONT_AE_ROI_HEIGHT_PRE_POS                         (16U)
#define DSP2_FRONT_AE_ROI_HEIGHT_PRE_LEN                         (11U)
#define DSP2_FRONT_AE_ROI_HEIGHT_PRE_MSK                         (((1U<<DSP2_FRONT_AE_ROI_HEIGHT_PRE_LEN)-1)<<DSP2_FRONT_AE_ROI_HEIGHT_PRE_POS)
#define DSP2_FRONT_AE_ROI_HEIGHT_PRE_UMSK                        (~(((1U<<DSP2_FRONT_AE_ROI_HEIGHT_PRE_LEN)-1)<<DSP2_FRONT_AE_ROI_HEIGHT_PRE_POS))

/* 0x1C4 : ae_image_size */
#define DSP2_FRONT_AE_IMAGE_SIZE_OFFSET                          (0x1C4)
#define DSP2_FRONT_AE_IMAGE_WIDTH_PRE                            DSP2_FRONT_AE_IMAGE_WIDTH_PRE
#define DSP2_FRONT_AE_IMAGE_WIDTH_PRE_POS                        (0U)
#define DSP2_FRONT_AE_IMAGE_WIDTH_PRE_LEN                        (11U)
#define DSP2_FRONT_AE_IMAGE_WIDTH_PRE_MSK                        (((1U<<DSP2_FRONT_AE_IMAGE_WIDTH_PRE_LEN)-1)<<DSP2_FRONT_AE_IMAGE_WIDTH_PRE_POS)
#define DSP2_FRONT_AE_IMAGE_WIDTH_PRE_UMSK                       (~(((1U<<DSP2_FRONT_AE_IMAGE_WIDTH_PRE_LEN)-1)<<DSP2_FRONT_AE_IMAGE_WIDTH_PRE_POS))
#define DSP2_FRONT_AE_IMAGE_HEIGHT_PRE                           DSP2_FRONT_AE_IMAGE_HEIGHT_PRE
#define DSP2_FRONT_AE_IMAGE_HEIGHT_PRE_POS                       (16U)
#define DSP2_FRONT_AE_IMAGE_HEIGHT_PRE_LEN                       (11U)
#define DSP2_FRONT_AE_IMAGE_HEIGHT_PRE_MSK                       (((1U<<DSP2_FRONT_AE_IMAGE_HEIGHT_PRE_LEN)-1)<<DSP2_FRONT_AE_IMAGE_HEIGHT_PRE_POS)
#define DSP2_FRONT_AE_IMAGE_HEIGHT_PRE_UMSK                      (~(((1U<<DSP2_FRONT_AE_IMAGE_HEIGHT_PRE_LEN)-1)<<DSP2_FRONT_AE_IMAGE_HEIGHT_PRE_POS))

/* 0x1C8 : ae_grid_size */
#define DSP2_FRONT_AE_GRID_SIZE_OFFSET                           (0x1C8)
#define DSP2_FRONT_AE_GRID_WIDTH_PRE                             DSP2_FRONT_AE_GRID_WIDTH_PRE
#define DSP2_FRONT_AE_GRID_WIDTH_PRE_POS                         (0U)
#define DSP2_FRONT_AE_GRID_WIDTH_PRE_LEN                         (8U)
#define DSP2_FRONT_AE_GRID_WIDTH_PRE_MSK                         (((1U<<DSP2_FRONT_AE_GRID_WIDTH_PRE_LEN)-1)<<DSP2_FRONT_AE_GRID_WIDTH_PRE_POS)
#define DSP2_FRONT_AE_GRID_WIDTH_PRE_UMSK                        (~(((1U<<DSP2_FRONT_AE_GRID_WIDTH_PRE_LEN)-1)<<DSP2_FRONT_AE_GRID_WIDTH_PRE_POS))
#define DSP2_FRONT_AE_GRID_HEIGHT_PRE                            DSP2_FRONT_AE_GRID_HEIGHT_PRE
#define DSP2_FRONT_AE_GRID_HEIGHT_PRE_POS                        (8U)
#define DSP2_FRONT_AE_GRID_HEIGHT_PRE_LEN                        (8U)
#define DSP2_FRONT_AE_GRID_HEIGHT_PRE_MSK                        (((1U<<DSP2_FRONT_AE_GRID_HEIGHT_PRE_LEN)-1)<<DSP2_FRONT_AE_GRID_HEIGHT_PRE_POS)
#define DSP2_FRONT_AE_GRID_HEIGHT_PRE_UMSK                       (~(((1U<<DSP2_FRONT_AE_GRID_HEIGHT_PRE_LEN)-1)<<DSP2_FRONT_AE_GRID_HEIGHT_PRE_POS))
#define DSP2_FRONT_AE_GRID_Y_MAX_PRE                             DSP2_FRONT_AE_GRID_Y_MAX_PRE
#define DSP2_FRONT_AE_GRID_Y_MAX_PRE_POS                         (16U)
#define DSP2_FRONT_AE_GRID_Y_MAX_PRE_LEN                         (4U)
#define DSP2_FRONT_AE_GRID_Y_MAX_PRE_MSK                         (((1U<<DSP2_FRONT_AE_GRID_Y_MAX_PRE_LEN)-1)<<DSP2_FRONT_AE_GRID_Y_MAX_PRE_POS)
#define DSP2_FRONT_AE_GRID_Y_MAX_PRE_UMSK                        (~(((1U<<DSP2_FRONT_AE_GRID_Y_MAX_PRE_LEN)-1)<<DSP2_FRONT_AE_GRID_Y_MAX_PRE_POS))
#define DSP2_FRONT_AE_GRID_X_MAX_PRE                             DSP2_FRONT_AE_GRID_X_MAX_PRE
#define DSP2_FRONT_AE_GRID_X_MAX_PRE_POS                         (20U)
#define DSP2_FRONT_AE_GRID_X_MAX_PRE_LEN                         (4U)
#define DSP2_FRONT_AE_GRID_X_MAX_PRE_MSK                         (((1U<<DSP2_FRONT_AE_GRID_X_MAX_PRE_LEN)-1)<<DSP2_FRONT_AE_GRID_X_MAX_PRE_POS)
#define DSP2_FRONT_AE_GRID_X_MAX_PRE_UMSK                        (~(((1U<<DSP2_FRONT_AE_GRID_X_MAX_PRE_LEN)-1)<<DSP2_FRONT_AE_GRID_X_MAX_PRE_POS))
#define DSP2_FRONT_NEW_AE_STA_ENABLE_W                           DSP2_FRONT_NEW_AE_STA_ENABLE_W
#define DSP2_FRONT_NEW_AE_STA_ENABLE_W_POS                       (24U)
#define DSP2_FRONT_NEW_AE_STA_ENABLE_W_LEN                       (1U)
#define DSP2_FRONT_NEW_AE_STA_ENABLE_W_MSK                       (((1U<<DSP2_FRONT_NEW_AE_STA_ENABLE_W_LEN)-1)<<DSP2_FRONT_NEW_AE_STA_ENABLE_W_POS)
#define DSP2_FRONT_NEW_AE_STA_ENABLE_W_UMSK                      (~(((1U<<DSP2_FRONT_NEW_AE_STA_ENABLE_W_LEN)-1)<<DSP2_FRONT_NEW_AE_STA_ENABLE_W_POS))
#define DSP2_FRONT_AE_SWITCH_BANK_EN_PRE                         DSP2_FRONT_AE_SWITCH_BANK_EN_PRE
#define DSP2_FRONT_AE_SWITCH_BANK_EN_PRE_POS                     (25U)
#define DSP2_FRONT_AE_SWITCH_BANK_EN_PRE_LEN                     (1U)
#define DSP2_FRONT_AE_SWITCH_BANK_EN_PRE_MSK                     (((1U<<DSP2_FRONT_AE_SWITCH_BANK_EN_PRE_LEN)-1)<<DSP2_FRONT_AE_SWITCH_BANK_EN_PRE_POS)
#define DSP2_FRONT_AE_SWITCH_BANK_EN_PRE_UMSK                    (~(((1U<<DSP2_FRONT_AE_SWITCH_BANK_EN_PRE_LEN)-1)<<DSP2_FRONT_AE_SWITCH_BANK_EN_PRE_POS))

/* 0x1CC : ae_coeff */
#define DSP2_FRONT_AE_COEFF_OFFSET                               (0x1CC)
#define DSP2_FRONT_AE_YSUM_COEFF_R_PRE                           DSP2_FRONT_AE_YSUM_COEFF_R_PRE
#define DSP2_FRONT_AE_YSUM_COEFF_R_PRE_POS                       (0U)
#define DSP2_FRONT_AE_YSUM_COEFF_R_PRE_LEN                       (8U)
#define DSP2_FRONT_AE_YSUM_COEFF_R_PRE_MSK                       (((1U<<DSP2_FRONT_AE_YSUM_COEFF_R_PRE_LEN)-1)<<DSP2_FRONT_AE_YSUM_COEFF_R_PRE_POS)
#define DSP2_FRONT_AE_YSUM_COEFF_R_PRE_UMSK                      (~(((1U<<DSP2_FRONT_AE_YSUM_COEFF_R_PRE_LEN)-1)<<DSP2_FRONT_AE_YSUM_COEFF_R_PRE_POS))
#define DSP2_FRONT_AE_YSUM_COEFF_G_PRE                           DSP2_FRONT_AE_YSUM_COEFF_G_PRE
#define DSP2_FRONT_AE_YSUM_COEFF_G_PRE_POS                       (8U)
#define DSP2_FRONT_AE_YSUM_COEFF_G_PRE_LEN                       (8U)
#define DSP2_FRONT_AE_YSUM_COEFF_G_PRE_MSK                       (((1U<<DSP2_FRONT_AE_YSUM_COEFF_G_PRE_LEN)-1)<<DSP2_FRONT_AE_YSUM_COEFF_G_PRE_POS)
#define DSP2_FRONT_AE_YSUM_COEFF_G_PRE_UMSK                      (~(((1U<<DSP2_FRONT_AE_YSUM_COEFF_G_PRE_LEN)-1)<<DSP2_FRONT_AE_YSUM_COEFF_G_PRE_POS))
#define DSP2_FRONT_AE_YSUM_COEFF_B_PRE                           DSP2_FRONT_AE_YSUM_COEFF_B_PRE
#define DSP2_FRONT_AE_YSUM_COEFF_B_PRE_POS                       (16U)
#define DSP2_FRONT_AE_YSUM_COEFF_B_PRE_LEN                       (8U)
#define DSP2_FRONT_AE_YSUM_COEFF_B_PRE_MSK                       (((1U<<DSP2_FRONT_AE_YSUM_COEFF_B_PRE_LEN)-1)<<DSP2_FRONT_AE_YSUM_COEFF_B_PRE_POS)
#define DSP2_FRONT_AE_YSUM_COEFF_B_PRE_UMSK                      (~(((1U<<DSP2_FRONT_AE_YSUM_COEFF_B_PRE_LEN)-1)<<DSP2_FRONT_AE_YSUM_COEFF_B_PRE_POS))

/* 0x1D0 : clp_rgr_gain */
#define DSP2_FRONT_CLP_RGR_GAIN_OFFSET                           (0x1D0)
#define DSP2_FRONT_CLP_GR_GAIN_PRE                               DSP2_FRONT_CLP_GR_GAIN_PRE
#define DSP2_FRONT_CLP_GR_GAIN_PRE_POS                           (0U)
#define DSP2_FRONT_CLP_GR_GAIN_PRE_LEN                           (15U)
#define DSP2_FRONT_CLP_GR_GAIN_PRE_MSK                           (((1U<<DSP2_FRONT_CLP_GR_GAIN_PRE_LEN)-1)<<DSP2_FRONT_CLP_GR_GAIN_PRE_POS)
#define DSP2_FRONT_CLP_GR_GAIN_PRE_UMSK                          (~(((1U<<DSP2_FRONT_CLP_GR_GAIN_PRE_LEN)-1)<<DSP2_FRONT_CLP_GR_GAIN_PRE_POS))
#define DSP2_FRONT_CLP_R_GAIN_PRE                                DSP2_FRONT_CLP_R_GAIN_PRE
#define DSP2_FRONT_CLP_R_GAIN_PRE_POS                            (16U)
#define DSP2_FRONT_CLP_R_GAIN_PRE_LEN                            (15U)
#define DSP2_FRONT_CLP_R_GAIN_PRE_MSK                            (((1U<<DSP2_FRONT_CLP_R_GAIN_PRE_LEN)-1)<<DSP2_FRONT_CLP_R_GAIN_PRE_POS)
#define DSP2_FRONT_CLP_R_GAIN_PRE_UMSK                           (~(((1U<<DSP2_FRONT_CLP_R_GAIN_PRE_LEN)-1)<<DSP2_FRONT_CLP_R_GAIN_PRE_POS))
#define DSP2_FRONT_CLP_GAIN_EN_PRE                               DSP2_FRONT_CLP_GAIN_EN_PRE
#define DSP2_FRONT_CLP_GAIN_EN_PRE_POS                           (31U)
#define DSP2_FRONT_CLP_GAIN_EN_PRE_LEN                           (1U)
#define DSP2_FRONT_CLP_GAIN_EN_PRE_MSK                           (((1U<<DSP2_FRONT_CLP_GAIN_EN_PRE_LEN)-1)<<DSP2_FRONT_CLP_GAIN_EN_PRE_POS)
#define DSP2_FRONT_CLP_GAIN_EN_PRE_UMSK                          (~(((1U<<DSP2_FRONT_CLP_GAIN_EN_PRE_LEN)-1)<<DSP2_FRONT_CLP_GAIN_EN_PRE_POS))

/* 0x1D4 : clp_bgb_gain */
#define DSP2_FRONT_CLP_BGB_GAIN_OFFSET                           (0x1D4)
#define DSP2_FRONT_CLP_GB_GAIN_PRE                               DSP2_FRONT_CLP_GB_GAIN_PRE
#define DSP2_FRONT_CLP_GB_GAIN_PRE_POS                           (0U)
#define DSP2_FRONT_CLP_GB_GAIN_PRE_LEN                           (15U)
#define DSP2_FRONT_CLP_GB_GAIN_PRE_MSK                           (((1U<<DSP2_FRONT_CLP_GB_GAIN_PRE_LEN)-1)<<DSP2_FRONT_CLP_GB_GAIN_PRE_POS)
#define DSP2_FRONT_CLP_GB_GAIN_PRE_UMSK                          (~(((1U<<DSP2_FRONT_CLP_GB_GAIN_PRE_LEN)-1)<<DSP2_FRONT_CLP_GB_GAIN_PRE_POS))
#define DSP2_FRONT_CLP_B_GAIN_PRE                                DSP2_FRONT_CLP_B_GAIN_PRE
#define DSP2_FRONT_CLP_B_GAIN_PRE_POS                            (16U)
#define DSP2_FRONT_CLP_B_GAIN_PRE_LEN                            (15U)
#define DSP2_FRONT_CLP_B_GAIN_PRE_MSK                            (((1U<<DSP2_FRONT_CLP_B_GAIN_PRE_LEN)-1)<<DSP2_FRONT_CLP_B_GAIN_PRE_POS)
#define DSP2_FRONT_CLP_B_GAIN_PRE_UMSK                           (~(((1U<<DSP2_FRONT_CLP_B_GAIN_PRE_LEN)-1)<<DSP2_FRONT_CLP_B_GAIN_PRE_POS))

/* 0x1E8 : ae_status */
#define DSP2_FRONT_AE_STATUS_OFFSET                              (0x1E8)
#define DSP2_FRONT_BLAE_BUF_IDX_R                                DSP2_FRONT_BLAE_BUF_IDX_R
#define DSP2_FRONT_BLAE_BUF_IDX_R_POS                            (16U)
#define DSP2_FRONT_BLAE_BUF_IDX_R_LEN                            (1U)
#define DSP2_FRONT_BLAE_BUF_IDX_R_MSK                            (((1U<<DSP2_FRONT_BLAE_BUF_IDX_R_LEN)-1)<<DSP2_FRONT_BLAE_BUF_IDX_R_POS)
#define DSP2_FRONT_BLAE_BUF_IDX_R_UMSK                           (~(((1U<<DSP2_FRONT_BLAE_BUF_IDX_R_LEN)-1)<<DSP2_FRONT_BLAE_BUF_IDX_R_POS))
#define DSP2_FRONT_BLAE_W_CNT_R                                  DSP2_FRONT_BLAE_W_CNT_R
#define DSP2_FRONT_BLAE_W_CNT_R_POS                              (20U)
#define DSP2_FRONT_BLAE_W_CNT_R_LEN                              (5U)
#define DSP2_FRONT_BLAE_W_CNT_R_MSK                              (((1U<<DSP2_FRONT_BLAE_W_CNT_R_LEN)-1)<<DSP2_FRONT_BLAE_W_CNT_R_POS)
#define DSP2_FRONT_BLAE_W_CNT_R_UMSK                             (~(((1U<<DSP2_FRONT_BLAE_W_CNT_R_LEN)-1)<<DSP2_FRONT_BLAE_W_CNT_R_POS))

/* 0x1EC : ae_sta_dbg */
#define DSP2_FRONT_AE_STA_DBG_OFFSET                             (0x1EC)
#define DSP2_FRONT_AE_GRID_CNT                                   DSP2_FRONT_AE_GRID_CNT
#define DSP2_FRONT_AE_GRID_CNT_POS                               (0U)
#define DSP2_FRONT_AE_GRID_CNT_LEN                               (7U)
#define DSP2_FRONT_AE_GRID_CNT_MSK                               (((1U<<DSP2_FRONT_AE_GRID_CNT_LEN)-1)<<DSP2_FRONT_AE_GRID_CNT_POS)
#define DSP2_FRONT_AE_GRID_CNT_UMSK                              (~(((1U<<DSP2_FRONT_AE_GRID_CNT_LEN)-1)<<DSP2_FRONT_AE_GRID_CNT_POS))
#define DSP2_FRONT_AE_STA_DONE                                   DSP2_FRONT_AE_STA_DONE
#define DSP2_FRONT_AE_STA_DONE_POS                               (7U)
#define DSP2_FRONT_AE_STA_DONE_LEN                               (1U)
#define DSP2_FRONT_AE_STA_DONE_MSK                               (((1U<<DSP2_FRONT_AE_STA_DONE_LEN)-1)<<DSP2_FRONT_AE_STA_DONE_POS)
#define DSP2_FRONT_AE_STA_DONE_UMSK                              (~(((1U<<DSP2_FRONT_AE_STA_DONE_LEN)-1)<<DSP2_FRONT_AE_STA_DONE_POS))
#define DSP2_FRONT_AE_WRITE_DATA_CNT                             DSP2_FRONT_AE_WRITE_DATA_CNT
#define DSP2_FRONT_AE_WRITE_DATA_CNT_POS                         (8U)
#define DSP2_FRONT_AE_WRITE_DATA_CNT_LEN                         (8U)
#define DSP2_FRONT_AE_WRITE_DATA_CNT_MSK                         (((1U<<DSP2_FRONT_AE_WRITE_DATA_CNT_LEN)-1)<<DSP2_FRONT_AE_WRITE_DATA_CNT_POS)
#define DSP2_FRONT_AE_WRITE_DATA_CNT_UMSK                        (~(((1U<<DSP2_FRONT_AE_WRITE_DATA_CNT_LEN)-1)<<DSP2_FRONT_AE_WRITE_DATA_CNT_POS))
#define DSP2_FRONT_AE_STA_INT_FLAG                               DSP2_FRONT_AE_STA_INT_FLAG
#define DSP2_FRONT_AE_STA_INT_FLAG_POS                           (16U)
#define DSP2_FRONT_AE_STA_INT_FLAG_LEN                           (1U)
#define DSP2_FRONT_AE_STA_INT_FLAG_MSK                           (((1U<<DSP2_FRONT_AE_STA_INT_FLAG_LEN)-1)<<DSP2_FRONT_AE_STA_INT_FLAG_POS)
#define DSP2_FRONT_AE_STA_INT_FLAG_UMSK                          (~(((1U<<DSP2_FRONT_AE_STA_INT_FLAG_LEN)-1)<<DSP2_FRONT_AE_STA_INT_FLAG_POS))
#define DSP2_FRONT_AE_GRID_CNT_MAX                               DSP2_FRONT_AE_GRID_CNT_MAX
#define DSP2_FRONT_AE_GRID_CNT_MAX_POS                           (17U)
#define DSP2_FRONT_AE_GRID_CNT_MAX_LEN                           (7U)
#define DSP2_FRONT_AE_GRID_CNT_MAX_MSK                           (((1U<<DSP2_FRONT_AE_GRID_CNT_MAX_LEN)-1)<<DSP2_FRONT_AE_GRID_CNT_MAX_POS)
#define DSP2_FRONT_AE_GRID_CNT_MAX_UMSK                          (~(((1U<<DSP2_FRONT_AE_GRID_CNT_MAX_LEN)-1)<<DSP2_FRONT_AE_GRID_CNT_MAX_POS))
#define DSP2_FRONT_AE_FIFO_FULL                                  DSP2_FRONT_AE_FIFO_FULL
#define DSP2_FRONT_AE_FIFO_FULL_POS                              (24U)
#define DSP2_FRONT_AE_FIFO_FULL_LEN                              (1U)
#define DSP2_FRONT_AE_FIFO_FULL_MSK                              (((1U<<DSP2_FRONT_AE_FIFO_FULL_LEN)-1)<<DSP2_FRONT_AE_FIFO_FULL_POS)
#define DSP2_FRONT_AE_FIFO_FULL_UMSK                             (~(((1U<<DSP2_FRONT_AE_FIFO_FULL_LEN)-1)<<DSP2_FRONT_AE_FIFO_FULL_POS))
#define DSP2_FRONT_AE_CONTROL_STATUS                             DSP2_FRONT_AE_CONTROL_STATUS
#define DSP2_FRONT_AE_CONTROL_STATUS_POS                         (25U)
#define DSP2_FRONT_AE_CONTROL_STATUS_LEN                         (4U)
#define DSP2_FRONT_AE_CONTROL_STATUS_MSK                         (((1U<<DSP2_FRONT_AE_CONTROL_STATUS_LEN)-1)<<DSP2_FRONT_AE_CONTROL_STATUS_POS)
#define DSP2_FRONT_AE_CONTROL_STATUS_UMSK                        (~(((1U<<DSP2_FRONT_AE_CONTROL_STATUS_LEN)-1)<<DSP2_FRONT_AE_CONTROL_STATUS_POS))
#define DSP2_FRONT_AE_OPERATION_DONE                             DSP2_FRONT_AE_OPERATION_DONE
#define DSP2_FRONT_AE_OPERATION_DONE_POS                         (29U)
#define DSP2_FRONT_AE_OPERATION_DONE_LEN                         (1U)
#define DSP2_FRONT_AE_OPERATION_DONE_MSK                         (((1U<<DSP2_FRONT_AE_OPERATION_DONE_LEN)-1)<<DSP2_FRONT_AE_OPERATION_DONE_POS)
#define DSP2_FRONT_AE_OPERATION_DONE_UMSK                        (~(((1U<<DSP2_FRONT_AE_OPERATION_DONE_LEN)-1)<<DSP2_FRONT_AE_OPERATION_DONE_POS))
#define DSP2_FRONT_AE_FIFO_EMPTY                                 DSP2_FRONT_AE_FIFO_EMPTY
#define DSP2_FRONT_AE_FIFO_EMPTY_POS                             (30U)
#define DSP2_FRONT_AE_FIFO_EMPTY_LEN                             (1U)
#define DSP2_FRONT_AE_FIFO_EMPTY_MSK                             (((1U<<DSP2_FRONT_AE_FIFO_EMPTY_LEN)-1)<<DSP2_FRONT_AE_FIFO_EMPTY_POS)
#define DSP2_FRONT_AE_FIFO_EMPTY_UMSK                            (~(((1U<<DSP2_FRONT_AE_FIFO_EMPTY_LEN)-1)<<DSP2_FRONT_AE_FIFO_EMPTY_POS))

/* 0x1F0 : Image_select */
#define DSP2_FRONT_IMAGE_SELECT_OFFSET                           (0x1F0)
#define DSP2_FRONT_IMAGE_SELECT_PRE                              DSP2_FRONT_IMAGE_SELECT_PRE
#define DSP2_FRONT_IMAGE_SELECT_PRE_POS                          (0U)
#define DSP2_FRONT_IMAGE_SELECT_PRE_LEN                          (2U)
#define DSP2_FRONT_IMAGE_SELECT_PRE_MSK                          (((1U<<DSP2_FRONT_IMAGE_SELECT_PRE_LEN)-1)<<DSP2_FRONT_IMAGE_SELECT_PRE_POS)
#define DSP2_FRONT_IMAGE_SELECT_PRE_UMSK                         (~(((1U<<DSP2_FRONT_IMAGE_SELECT_PRE_LEN)-1)<<DSP2_FRONT_IMAGE_SELECT_PRE_POS))


struct  dsp2_front_reg {
    /* 0x0  reserved */
    uint8_t RESERVED0x0[272];

    /* 0x110 : pattern_mode */
    union {
        struct {
            uint32_t pattern_mode_w                 :  3; /* [ 2: 0],        r/w,        0x0 */
            uint32_t reserved_3_7                   :  5; /* [ 7: 3],       rsvd,        0x0 */
            uint32_t pid_inv_rgb_pre                :  1; /* [    8],        r/w,        0x0 */
            uint32_t lid_inv_rgb_pre                :  1; /* [    9],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t act_hsize_w                    : 16; /* [31:16],        r/w,      0x788 */
        }BF;
        uint32_t WORD;
    } pattern_mode;

    /* 0x114 : clamp_R_Gr */
    union {
        struct {
            uint32_t clp_R_pre                      : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t clp_Gr_pre                     : 16; /* [31:16],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } clamp_R_Gr;

    /* 0x118 : clamp_B_Gb */
    union {
        struct {
            uint32_t clp_Gb_pre                     : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t clp_B_pre                      : 16; /* [31:16],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } clamp_B_Gb;

    /* 0x11c  reserved */
    uint8_t RESERVED0x11c[20];

    /* 0x130 : ob_win */
    union {
        struct {
            uint32_t ob_win_startx_w                : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t ob_win_starty_w                : 16; /* [31:16],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ob_win;

    /* 0x134 : black_columns_bit */
    union {
        struct {
            uint32_t black_rows_bit_w               :  4; /* [ 3: 0],        r/w,        0x2 */
            uint32_t black_columns_bit_w            :  4; /* [ 7: 4],        r/w,        0x8 */
            uint32_t reserved_8_31                  : 24; /* [31: 8],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } black_columns_bit;

    /* 0x138 : Ob_R_Gr */
    union {
        struct {
            uint32_t Ob_R_r                         : 16; /* [15: 0],          r,        0x0 */
            uint32_t Ob_Gr_r                        : 16; /* [31:16],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } Ob_R_Gr;

    /* 0x13C : Ob_B_Gb */
    union {
        struct {
            uint32_t Ob_Gb_r                        : 16; /* [15: 0],          r,        0x0 */
            uint32_t Ob_B_r                         : 16; /* [31:16],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } Ob_B_Gb;

    /* 0x140  reserved */
    uint8_t RESERVED0x140[16];

    /* 0x150 : gain_R_G */
    union {
        struct {
            uint32_t rgain1_pre                     : 11; /* [10: 0],        r/w,       0x80 */
            uint32_t reserved_11_15                 :  5; /* [15:11],       rsvd,        0x0 */
            uint32_t ggain1_pre                     : 11; /* [26:16],        r/w,       0x80 */
            uint32_t reserved_27_31                 :  5; /* [31:27],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } gain_R_G;

    /* 0x154 : gain_B */
    union {
        struct {
            uint32_t bgain1_pre                     : 11; /* [10: 0],        r/w,       0x80 */
            uint32_t reserved_11_31                 : 21; /* [31:11],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } gain_B;

    /* 0x158 : gain2_R_G */
    union {
        struct {
            uint32_t rgain2_pre                     : 11; /* [10: 0],        r/w,       0x80 */
            uint32_t reserved_11_15                 :  5; /* [15:11],       rsvd,        0x0 */
            uint32_t ggain2_pre                     : 11; /* [26:16],        r/w,       0x80 */
            uint32_t reserved_27_31                 :  5; /* [31:27],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } gain2_R_G;

    /* 0x15C : gain2_B */
    union {
        struct {
            uint32_t bgain2_pre                     : 11; /* [10: 0],        r/w,       0x80 */
            uint32_t reserved_11_31                 : 21; /* [31:11],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } gain2_B;

    /* 0x160  reserved */
    uint8_t RESERVED0x160[20];

    /* 0x174 : Bright_coeff_A */
    union {
        struct {
            uint32_t reserved_0_15                  : 16; /* [15: 0],       rsvd,        0x0 */
            uint32_t b0_avc_pre                     :  8; /* [23:16],        r/w,        0x0 */
            uint32_t b1_avc_pre                     :  8; /* [31:24],        r/w,       0x10 */
        }BF;
        uint32_t WORD;
    } Bright_coeff_A;

    /* 0x178 : Bright_coeff_B */
    union {
        struct {
            uint32_t b2_avc_pre                     :  8; /* [ 7: 0],        r/w,       0x20 */
            uint32_t b3_avc_pre                     :  8; /* [15: 8],        r/w,       0x40 */
            uint32_t b4_avc_pre                     :  8; /* [23:16],        r/w,       0x80 */
            uint32_t b5_avc_pre                     :  8; /* [31:24],        r/w,       0xff */
        }BF;
        uint32_t WORD;
    } Bright_coeff_B;

    /* 0x17c  reserved */
    uint8_t RESERVED0x17c[4];

    /* 0x180 : ex_win */
    union {
        struct {
            uint32_t exwsx_pre                      :  8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t exwsy_pre                      :  8; /* [15: 8],        r/w,        0x0 */
            uint32_t exwex_pre                      :  8; /* [23:16],        r/w,        0x0 */
            uint32_t exwey_pre                      :  8; /* [31:24],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ex_win;

    /* 0x184 : ex_limit1 */
    union {
        struct {
            uint32_t Unex_Min1_pre                  :  8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t Unex_Max1_pre                  :  8; /* [15: 8],        r/w,        0x0 */
            uint32_t Ovex_Min1_pre                  :  8; /* [23:16],        r/w,        0x0 */
            uint32_t Ovex_Max1_pre                  :  8; /* [31:24],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ex_limit1;

    /* 0x188 : Unex_sum1 */
    union {
        struct {
            uint32_t Unex_sum1_r                    : 20; /* [19: 0],          r,        0x0 */
            uint32_t reserved_20_31                 : 12; /* [31:20],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } Unex_sum1;

    /* 0x18C : Ovex_sum1 */
    union {
        struct {
            uint32_t Ovex_sum1_r                    : 20; /* [19: 0],          r,        0x0 */
            uint32_t reserved_20_31                 : 12; /* [31:20],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } Ovex_sum1;

    /* 0x190 : ex_limit2 */
    union {
        struct {
            uint32_t Unex_Min2_pre                  :  8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t Unex_Max2_pre                  :  8; /* [15: 8],        r/w,        0x0 */
            uint32_t Ovex_Min2_pre                  :  8; /* [23:16],        r/w,        0x0 */
            uint32_t Ovex_Max2_pre                  :  8; /* [31:24],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ex_limit2;

    /* 0x194 : Unex_sum2 */
    union {
        struct {
            uint32_t Unex_sum2_r                    : 20; /* [19: 0],          r,        0x0 */
            uint32_t reserved_20_31                 : 12; /* [31:20],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } Unex_sum2;

    /* 0x198 : Ovex_sum2 */
    union {
        struct {
            uint32_t Ovex_sum2_r                    : 20; /* [19: 0],          r,        0x0 */
            uint32_t reserved_20_31                 : 12; /* [31:20],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } Ovex_sum2;

    /* 0x19c  reserved */
    uint8_t RESERVED0x19c[4];

    /* 0x1A0 : HDR_1 */
    union {
        struct {
            uint32_t HDR_on_off_pre                 :  1; /* [    0],        r/w,        0x0 */
            uint32_t reserved_1_7                   :  7; /* [ 7: 1],       rsvd,        0x0 */
            uint32_t Exposure_rate_pre              :  3; /* [10: 8],        r/w,        0x2 */
            uint32_t reserved_11_15                 :  5; /* [15:11],       rsvd,        0x0 */
            uint32_t Ghost_Threshold_pre            :  8; /* [23:16],        r/w,       0x1e */
            uint32_t DilationThreshold_pre          :  8; /* [31:24],        r/w,       0x40 */
        }BF;
        uint32_t WORD;
    } HDR_1;

    /* 0x1A4 : HDR_2 */
    union {
        struct {
            uint32_t Ghost_remove_pre               :  1; /* [    0],        r/w,        0x1 */
            uint32_t reserved_1_7                   :  7; /* [ 7: 1],       rsvd,        0x0 */
            uint32_t HStrength_pre                  :  4; /* [11: 8],        r/w,        0x8 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t SetRmapMin_pre                 :  8; /* [23:16],        r/w,        0x0 */
            uint32_t RadianceMapMode_pre            :  2; /* [25:24],        r/w,        0x0 */
            uint32_t reserved_26_30                 :  5; /* [30:26],       rsvd,        0x0 */
            uint32_t AutoSetRmapMax_pre             :  1; /* [   31],        r/w,        0x1 */
        }BF;
        uint32_t WORD;
    } HDR_2;

    /* 0x1A8 : HDR_3 */
    union {
        struct {
            uint32_t SetRmapMax_pre                 : 24; /* [23: 0],        r/w,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } HDR_3;

    /* 0x1AC : HDR_4 */
    union {
        struct {
            uint32_t RmapMax_r                      : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } HDR_4;

    /* 0x1B0 : SH_1 */
    union {
        struct {
            uint32_t HighlightCompesationMode_pre   :  1; /* [    0],        r/w,        0x0 */
            uint32_t AutoHightlightCompensation_pre :  1; /* [    1],        r/w,        0x0 */
            uint32_t ShadowCompesationMode_pre      :  1; /* [    2],        r/w,        0x0 */
            uint32_t AutoShadowCompensation_pre     :  1; /* [    3],        r/w,        0x0 */
            uint32_t reserved_4_7                   :  4; /* [ 7: 4],       rsvd,        0x0 */
            uint32_t SetShadowStrength_pre          :  8; /* [15: 8],        r/w,        0x0 */
            uint32_t SetShadowRange_pre             :  7; /* [22:16],        r/w,       0x20 */
            uint32_t reserved_23                    :  1; /* [   23],       rsvd,        0x0 */
            uint32_t SetHighlitStrength_pre         :  8; /* [31:24],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } SH_1;

    /* 0x1B4 : SH_2 */
    union {
        struct {
            uint32_t SetHighlitRange_pre            :  7; /* [ 6: 0],        r/w,       0x40 */
            uint32_t reserved_7                     :  1; /* [    7],       rsvd,        0x0 */
            uint32_t ShadowStrengthMult_pre         :  6; /* [13: 8],        r/w,       0x10 */
            uint32_t reserved_14_15                 :  2; /* [15:14],       rsvd,        0x0 */
            uint32_t ShadowRangeMult_pre            :  6; /* [21:16],        r/w,       0x10 */
            uint32_t reserved_22_23                 :  2; /* [23:22],       rsvd,        0x0 */
            uint32_t HighlitStrengthMult_pre        :  6; /* [29:24],        r/w,       0x10 */
            uint32_t reserved_30_31                 :  2; /* [31:30],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } SH_2;

    /* 0x1B8 : SH_3 */
    union {
        struct {
            uint32_t HighlitRangeMult_pre           :  6; /* [ 5: 0],        r/w,       0x10 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t ShadowStrength_r               :  8; /* [15: 8],          r,        0x0 */
            uint32_t HighlightStrength_r            :  8; /* [23:16],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } SH_3;

    /* 0x1BC : ae_roi_x */
    union {
        struct {
            uint32_t ae_roi_start_x_pre             : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15                 :  5; /* [15:11],       rsvd,        0x0 */
            uint32_t ae_roi_width_pre               : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31                 :  5; /* [31:27],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ae_roi_x;

    /* 0x1C0 : ae_roi_y */
    union {
        struct {
            uint32_t ae_roi_start_y_pre             : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15                 :  5; /* [15:11],       rsvd,        0x0 */
            uint32_t ae_roi_height_pre              : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31                 :  5; /* [31:27],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ae_roi_y;

    /* 0x1C4 : ae_image_size */
    union {
        struct {
            uint32_t ae_image_width_pre             : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15                 :  5; /* [15:11],       rsvd,        0x0 */
            uint32_t ae_image_height_pre            : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31                 :  5; /* [31:27],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ae_image_size;

    /* 0x1C8 : ae_grid_size */
    union {
        struct {
            uint32_t ae_grid_width_pre              :  8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t ae_grid_height_pre             :  8; /* [15: 8],        r/w,        0x0 */
            uint32_t ae_grid_y_max_pre              :  4; /* [19:16],        r/w,        0x0 */
            uint32_t ae_grid_x_max_pre              :  4; /* [23:20],        r/w,        0x0 */
            uint32_t new_ae_sta_enable_w            :  1; /* [   24],        r/w,        0x0 */
            uint32_t ae_switch_bank_en_pre          :  1; /* [   25],        r/w,        0x1 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ae_grid_size;

    /* 0x1CC : ae_coeff */
    union {
        struct {
            uint32_t ae_ysum_coeff_r_pre            :  8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t ae_ysum_coeff_g_pre            :  8; /* [15: 8],        r/w,        0x0 */
            uint32_t ae_ysum_coeff_b_pre            :  8; /* [23:16],        r/w,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ae_coeff;

    /* 0x1D0 : clp_rgr_gain */
    union {
        struct {
            uint32_t clp_gr_gain_pre                : 15; /* [14: 0],        r/w,     0x1000 */
            uint32_t reserved_15                    :  1; /* [   15],       rsvd,        0x0 */
            uint32_t clp_r_gain_pre                 : 15; /* [30:16],        r/w,     0x1000 */
            uint32_t clp_gain_en_pre                :  1; /* [   31],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } clp_rgr_gain;

    /* 0x1D4 : clp_bgb_gain */
    union {
        struct {
            uint32_t clp_gb_gain_pre                : 15; /* [14: 0],        r/w,     0x1000 */
            uint32_t reserved_15                    :  1; /* [   15],       rsvd,        0x0 */
            uint32_t clp_b_gain_pre                 : 15; /* [30:16],        r/w,     0x1000 */
            uint32_t reserved_31                    :  1; /* [   31],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } clp_bgb_gain;

    /* 0x1d8  reserved */
    uint8_t RESERVED0x1d8[16];

    /* 0x1E8 : ae_status */
    union {
        struct {
            uint32_t reserved_0_15                  : 16; /* [15: 0],       rsvd,        0x0 */
            uint32_t blae_buf_idx_r                 :  1; /* [   16],          r,        0x0 */
            uint32_t reserved_17_19                 :  3; /* [19:17],       rsvd,        0x0 */
            uint32_t blae_w_cnt_r                   :  5; /* [24:20],          r,        0x0 */
            uint32_t reserved_25_31                 :  7; /* [31:25],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ae_status;

    /* 0x1EC : ae_sta_dbg */
    union {
        struct {
            uint32_t ae_grid_cnt                    :  7; /* [ 6: 0],          r,        0x0 */
            uint32_t ae_sta_done                    :  1; /* [    7],          r,        0x0 */
            uint32_t ae_write_data_cnt              :  8; /* [15: 8],          r,        0x0 */
            uint32_t ae_sta_int_flag                :  1; /* [   16],          r,        0x0 */
            uint32_t ae_grid_cnt_max                :  7; /* [23:17],          r,        0x0 */
            uint32_t ae_fifo_full                   :  1; /* [   24],          r,        0x0 */
            uint32_t ae_control_status              :  4; /* [28:25],          r,        0x0 */
            uint32_t ae_operation_done              :  1; /* [   29],          r,        0x0 */
            uint32_t ae_fifo_empty                  :  1; /* [   30],          r,        0x0 */
            uint32_t reserved_31                    :  1; /* [   31],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ae_sta_dbg;

    /* 0x1F0 : Image_select */
    union {
        struct {
            uint32_t Image_Select_pre               :  2; /* [ 1: 0],        r/w,        0x0 */
            uint32_t reserved_2_31                  : 30; /* [31: 2],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } Image_select;

};

typedef volatile struct dsp2_front_reg dsp2_front_reg_t;


#endif  /* __DSP2_FRONT_REG_H__ */
