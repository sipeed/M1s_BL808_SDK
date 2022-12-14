/**
  ******************************************************************************
  * @file    dsp2_middle3_reg.h
  * @version V1.2
  * @date    2021-07-15
  * @brief   This file is the description of.IP register
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
#ifndef  __DSP2_MIDDLE3_REG_H__
#define  __DSP2_MIDDLE3_REG_H__

#include "bl808.h"

/* 0x500 : awb2_sta_xaxis */
#define DSP2_MIDDLE3_AWB2_STA_XAXIS_OFFSET                       (0x500)
#define DSP2_MIDDLE3_AWB2_X_MIN_PRE                              DSP2_MIDDLE3_AWB2_X_MIN_PRE
#define DSP2_MIDDLE3_AWB2_X_MIN_PRE_POS                          (0U)
#define DSP2_MIDDLE3_AWB2_X_MIN_PRE_LEN                          (11U)
#define DSP2_MIDDLE3_AWB2_X_MIN_PRE_MSK                          (((1U<<DSP2_MIDDLE3_AWB2_X_MIN_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_X_MIN_PRE_POS)
#define DSP2_MIDDLE3_AWB2_X_MIN_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE3_AWB2_X_MIN_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_X_MIN_PRE_POS))
#define DSP2_MIDDLE3_AWB2_X_MAX_PRE                              DSP2_MIDDLE3_AWB2_X_MAX_PRE
#define DSP2_MIDDLE3_AWB2_X_MAX_PRE_POS                          (16U)
#define DSP2_MIDDLE3_AWB2_X_MAX_PRE_LEN                          (11U)
#define DSP2_MIDDLE3_AWB2_X_MAX_PRE_MSK                          (((1U<<DSP2_MIDDLE3_AWB2_X_MAX_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_X_MAX_PRE_POS)
#define DSP2_MIDDLE3_AWB2_X_MAX_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE3_AWB2_X_MAX_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_X_MAX_PRE_POS))

/* 0x504 : awb2_sta_yaxis */
#define DSP2_MIDDLE3_AWB2_STA_YAXIS_OFFSET                       (0x504)
#define DSP2_MIDDLE3_AWB2_Y_MIN_PRE                              DSP2_MIDDLE3_AWB2_Y_MIN_PRE
#define DSP2_MIDDLE3_AWB2_Y_MIN_PRE_POS                          (0U)
#define DSP2_MIDDLE3_AWB2_Y_MIN_PRE_LEN                          (11U)
#define DSP2_MIDDLE3_AWB2_Y_MIN_PRE_MSK                          (((1U<<DSP2_MIDDLE3_AWB2_Y_MIN_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_Y_MIN_PRE_POS)
#define DSP2_MIDDLE3_AWB2_Y_MIN_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE3_AWB2_Y_MIN_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_Y_MIN_PRE_POS))
#define DSP2_MIDDLE3_AWB2_Y_MAX_PRE                              DSP2_MIDDLE3_AWB2_Y_MAX_PRE
#define DSP2_MIDDLE3_AWB2_Y_MAX_PRE_POS                          (16U)
#define DSP2_MIDDLE3_AWB2_Y_MAX_PRE_LEN                          (11U)
#define DSP2_MIDDLE3_AWB2_Y_MAX_PRE_MSK                          (((1U<<DSP2_MIDDLE3_AWB2_Y_MAX_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_Y_MAX_PRE_POS)
#define DSP2_MIDDLE3_AWB2_Y_MAX_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE3_AWB2_Y_MAX_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_Y_MAX_PRE_POS))

/* 0x508 : awb2_sta_pixel_num */
#define DSP2_MIDDLE3_AWB2_STA_PIXEL_NUM_OFFSET                   (0x508)
#define DSP2_MIDDLE3_AWB2_PIXEL_NUM_PRE                          DSP2_MIDDLE3_AWB2_PIXEL_NUM_PRE
#define DSP2_MIDDLE3_AWB2_PIXEL_NUM_PRE_POS                      (0U)
#define DSP2_MIDDLE3_AWB2_PIXEL_NUM_PRE_LEN                      (21U)
#define DSP2_MIDDLE3_AWB2_PIXEL_NUM_PRE_MSK                      (((1U<<DSP2_MIDDLE3_AWB2_PIXEL_NUM_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_PIXEL_NUM_PRE_POS)
#define DSP2_MIDDLE3_AWB2_PIXEL_NUM_PRE_UMSK                     (~(((1U<<DSP2_MIDDLE3_AWB2_PIXEL_NUM_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_PIXEL_NUM_PRE_POS))

/* 0x50C : awb2_sta_gain0 */
#define DSP2_MIDDLE3_AWB2_STA_GAIN0_OFFSET                       (0x50C)
#define DSP2_MIDDLE3_AWB2_STAT_GGAIN_PRE                         DSP2_MIDDLE3_AWB2_STAT_GGAIN_PRE
#define DSP2_MIDDLE3_AWB2_STAT_GGAIN_PRE_POS                     (0U)
#define DSP2_MIDDLE3_AWB2_STAT_GGAIN_PRE_LEN                     (16U)
#define DSP2_MIDDLE3_AWB2_STAT_GGAIN_PRE_MSK                     (((1U<<DSP2_MIDDLE3_AWB2_STAT_GGAIN_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_STAT_GGAIN_PRE_POS)
#define DSP2_MIDDLE3_AWB2_STAT_GGAIN_PRE_UMSK                    (~(((1U<<DSP2_MIDDLE3_AWB2_STAT_GGAIN_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_STAT_GGAIN_PRE_POS))
#define DSP2_MIDDLE3_AWB2_STAT_RGAIN_PRE                         DSP2_MIDDLE3_AWB2_STAT_RGAIN_PRE
#define DSP2_MIDDLE3_AWB2_STAT_RGAIN_PRE_POS                     (16U)
#define DSP2_MIDDLE3_AWB2_STAT_RGAIN_PRE_LEN                     (16U)
#define DSP2_MIDDLE3_AWB2_STAT_RGAIN_PRE_MSK                     (((1U<<DSP2_MIDDLE3_AWB2_STAT_RGAIN_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_STAT_RGAIN_PRE_POS)
#define DSP2_MIDDLE3_AWB2_STAT_RGAIN_PRE_UMSK                    (~(((1U<<DSP2_MIDDLE3_AWB2_STAT_RGAIN_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_STAT_RGAIN_PRE_POS))

/* 0x510 : awb2_sta_gain1 */
#define DSP2_MIDDLE3_AWB2_STA_GAIN1_OFFSET                       (0x510)
#define DSP2_MIDDLE3_AWB2_RGAIN_PRE                              DSP2_MIDDLE3_AWB2_RGAIN_PRE
#define DSP2_MIDDLE3_AWB2_RGAIN_PRE_POS                          (0U)
#define DSP2_MIDDLE3_AWB2_RGAIN_PRE_LEN                          (16U)
#define DSP2_MIDDLE3_AWB2_RGAIN_PRE_MSK                          (((1U<<DSP2_MIDDLE3_AWB2_RGAIN_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_RGAIN_PRE_POS)
#define DSP2_MIDDLE3_AWB2_RGAIN_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE3_AWB2_RGAIN_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_RGAIN_PRE_POS))
#define DSP2_MIDDLE3_AWB2_STAT_BGAIN_PRE                         DSP2_MIDDLE3_AWB2_STAT_BGAIN_PRE
#define DSP2_MIDDLE3_AWB2_STAT_BGAIN_PRE_POS                     (16U)
#define DSP2_MIDDLE3_AWB2_STAT_BGAIN_PRE_LEN                     (16U)
#define DSP2_MIDDLE3_AWB2_STAT_BGAIN_PRE_MSK                     (((1U<<DSP2_MIDDLE3_AWB2_STAT_BGAIN_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_STAT_BGAIN_PRE_POS)
#define DSP2_MIDDLE3_AWB2_STAT_BGAIN_PRE_UMSK                    (~(((1U<<DSP2_MIDDLE3_AWB2_STAT_BGAIN_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_STAT_BGAIN_PRE_POS))

/* 0x514 : awb2_sta_gain2 */
#define DSP2_MIDDLE3_AWB2_STA_GAIN2_OFFSET                       (0x514)
#define DSP2_MIDDLE3_AWB2_BGAIN_PRE                              DSP2_MIDDLE3_AWB2_BGAIN_PRE
#define DSP2_MIDDLE3_AWB2_BGAIN_PRE_POS                          (0U)
#define DSP2_MIDDLE3_AWB2_BGAIN_PRE_LEN                          (16U)
#define DSP2_MIDDLE3_AWB2_BGAIN_PRE_MSK                          (((1U<<DSP2_MIDDLE3_AWB2_BGAIN_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_BGAIN_PRE_POS)
#define DSP2_MIDDLE3_AWB2_BGAIN_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE3_AWB2_BGAIN_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_BGAIN_PRE_POS))
#define DSP2_MIDDLE3_AWB2_GGAIN_PRE                              DSP2_MIDDLE3_AWB2_GGAIN_PRE
#define DSP2_MIDDLE3_AWB2_GGAIN_PRE_POS                          (16U)
#define DSP2_MIDDLE3_AWB2_GGAIN_PRE_LEN                          (16U)
#define DSP2_MIDDLE3_AWB2_GGAIN_PRE_MSK                          (((1U<<DSP2_MIDDLE3_AWB2_GGAIN_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_GGAIN_PRE_POS)
#define DSP2_MIDDLE3_AWB2_GGAIN_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE3_AWB2_GGAIN_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_GGAIN_PRE_POS))

/* 0x518 : awb2_sta_gain3 */
#define DSP2_MIDDLE3_AWB2_STA_GAIN3_OFFSET                       (0x518)
#define DSP2_MIDDLE3_AWB2_VGAIN_PRE                              DSP2_MIDDLE3_AWB2_VGAIN_PRE
#define DSP2_MIDDLE3_AWB2_VGAIN_PRE_POS                          (0U)
#define DSP2_MIDDLE3_AWB2_VGAIN_PRE_LEN                          (10U)
#define DSP2_MIDDLE3_AWB2_VGAIN_PRE_MSK                          (((1U<<DSP2_MIDDLE3_AWB2_VGAIN_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_VGAIN_PRE_POS)
#define DSP2_MIDDLE3_AWB2_VGAIN_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE3_AWB2_VGAIN_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_VGAIN_PRE_POS))
#define DSP2_MIDDLE3_AWB2_UGAIN_PRE                              DSP2_MIDDLE3_AWB2_UGAIN_PRE
#define DSP2_MIDDLE3_AWB2_UGAIN_PRE_POS                          (16U)
#define DSP2_MIDDLE3_AWB2_UGAIN_PRE_LEN                          (10U)
#define DSP2_MIDDLE3_AWB2_UGAIN_PRE_MSK                          (((1U<<DSP2_MIDDLE3_AWB2_UGAIN_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_UGAIN_PRE_POS)
#define DSP2_MIDDLE3_AWB2_UGAIN_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE3_AWB2_UGAIN_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_UGAIN_PRE_POS))

/* 0x51C : awb2_sta_l0 */
#define DSP2_MIDDLE3_AWB2_STA_L0_OFFSET                          (0x51C)
#define DSP2_MIDDLE3_AWB2_YTH1_PRE                               DSP2_MIDDLE3_AWB2_YTH1_PRE
#define DSP2_MIDDLE3_AWB2_YTH1_PRE_POS                           (0U)
#define DSP2_MIDDLE3_AWB2_YTH1_PRE_LEN                           (8U)
#define DSP2_MIDDLE3_AWB2_YTH1_PRE_MSK                           (((1U<<DSP2_MIDDLE3_AWB2_YTH1_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_YTH1_PRE_POS)
#define DSP2_MIDDLE3_AWB2_YTH1_PRE_UMSK                          (~(((1U<<DSP2_MIDDLE3_AWB2_YTH1_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_YTH1_PRE_POS))
#define DSP2_MIDDLE3_AWB2_YTH2_PRE                               DSP2_MIDDLE3_AWB2_YTH2_PRE
#define DSP2_MIDDLE3_AWB2_YTH2_PRE_POS                           (8U)
#define DSP2_MIDDLE3_AWB2_YTH2_PRE_LEN                           (8U)
#define DSP2_MIDDLE3_AWB2_YTH2_PRE_MSK                           (((1U<<DSP2_MIDDLE3_AWB2_YTH2_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_YTH2_PRE_POS)
#define DSP2_MIDDLE3_AWB2_YTH2_PRE_UMSK                          (~(((1U<<DSP2_MIDDLE3_AWB2_YTH2_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_YTH2_PRE_POS))
#define DSP2_MIDDLE3_AWB2_YTH3_PRE                               DSP2_MIDDLE3_AWB2_YTH3_PRE
#define DSP2_MIDDLE3_AWB2_YTH3_PRE_POS                           (16U)
#define DSP2_MIDDLE3_AWB2_YTH3_PRE_LEN                           (8U)
#define DSP2_MIDDLE3_AWB2_YTH3_PRE_MSK                           (((1U<<DSP2_MIDDLE3_AWB2_YTH3_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_YTH3_PRE_POS)
#define DSP2_MIDDLE3_AWB2_YTH3_PRE_UMSK                          (~(((1U<<DSP2_MIDDLE3_AWB2_YTH3_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_YTH3_PRE_POS))
#define DSP2_MIDDLE3_AWB2_YTH4_PRE                               DSP2_MIDDLE3_AWB2_YTH4_PRE
#define DSP2_MIDDLE3_AWB2_YTH4_PRE_POS                           (24U)
#define DSP2_MIDDLE3_AWB2_YTH4_PRE_LEN                           (8U)
#define DSP2_MIDDLE3_AWB2_YTH4_PRE_MSK                           (((1U<<DSP2_MIDDLE3_AWB2_YTH4_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_YTH4_PRE_POS)
#define DSP2_MIDDLE3_AWB2_YTH4_PRE_UMSK                          (~(((1U<<DSP2_MIDDLE3_AWB2_YTH4_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_YTH4_PRE_POS))

/* 0x520 : awb2_sta_l1 */
#define DSP2_MIDDLE3_AWB2_STA_L1_OFFSET                          (0x520)
#define DSP2_MIDDLE3_AWB2_YWEIGHT2_PRE                           DSP2_MIDDLE3_AWB2_YWEIGHT2_PRE
#define DSP2_MIDDLE3_AWB2_YWEIGHT2_PRE_POS                       (0U)
#define DSP2_MIDDLE3_AWB2_YWEIGHT2_PRE_LEN                       (8U)
#define DSP2_MIDDLE3_AWB2_YWEIGHT2_PRE_MSK                       (((1U<<DSP2_MIDDLE3_AWB2_YWEIGHT2_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_YWEIGHT2_PRE_POS)
#define DSP2_MIDDLE3_AWB2_YWEIGHT2_PRE_UMSK                      (~(((1U<<DSP2_MIDDLE3_AWB2_YWEIGHT2_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_YWEIGHT2_PRE_POS))
#define DSP2_MIDDLE3_AWB2_YWEIGHT3_PRE                           DSP2_MIDDLE3_AWB2_YWEIGHT3_PRE
#define DSP2_MIDDLE3_AWB2_YWEIGHT3_PRE_POS                       (8U)
#define DSP2_MIDDLE3_AWB2_YWEIGHT3_PRE_LEN                       (8U)
#define DSP2_MIDDLE3_AWB2_YWEIGHT3_PRE_MSK                       (((1U<<DSP2_MIDDLE3_AWB2_YWEIGHT3_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_YWEIGHT3_PRE_POS)
#define DSP2_MIDDLE3_AWB2_YWEIGHT3_PRE_UMSK                      (~(((1U<<DSP2_MIDDLE3_AWB2_YWEIGHT3_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_YWEIGHT3_PRE_POS))
#define DSP2_MIDDLE3_AWB2_YWEIGHT4_PRE                           DSP2_MIDDLE3_AWB2_YWEIGHT4_PRE
#define DSP2_MIDDLE3_AWB2_YWEIGHT4_PRE_POS                       (16U)
#define DSP2_MIDDLE3_AWB2_YWEIGHT4_PRE_LEN                       (8U)
#define DSP2_MIDDLE3_AWB2_YWEIGHT4_PRE_MSK                       (((1U<<DSP2_MIDDLE3_AWB2_YWEIGHT4_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_YWEIGHT4_PRE_POS)
#define DSP2_MIDDLE3_AWB2_YWEIGHT4_PRE_UMSK                      (~(((1U<<DSP2_MIDDLE3_AWB2_YWEIGHT4_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_YWEIGHT4_PRE_POS))
#define DSP2_MIDDLE3_AWB2_YTH0_PRE                               DSP2_MIDDLE3_AWB2_YTH0_PRE
#define DSP2_MIDDLE3_AWB2_YTH0_PRE_POS                           (24U)
#define DSP2_MIDDLE3_AWB2_YTH0_PRE_LEN                           (8U)
#define DSP2_MIDDLE3_AWB2_YTH0_PRE_MSK                           (((1U<<DSP2_MIDDLE3_AWB2_YTH0_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_YTH0_PRE_POS)
#define DSP2_MIDDLE3_AWB2_YTH0_PRE_UMSK                          (~(((1U<<DSP2_MIDDLE3_AWB2_YTH0_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_YTH0_PRE_POS))

/* 0x524 : awb2_sta_l2 */
#define DSP2_MIDDLE3_AWB2_STA_L2_OFFSET                          (0x524)
#define DSP2_MIDDLE3_AWB2_YSLOPE4_PRE                            DSP2_MIDDLE3_AWB2_YSLOPE4_PRE
#define DSP2_MIDDLE3_AWB2_YSLOPE4_PRE_POS                        (0U)
#define DSP2_MIDDLE3_AWB2_YSLOPE4_PRE_LEN                        (9U)
#define DSP2_MIDDLE3_AWB2_YSLOPE4_PRE_MSK                        (((1U<<DSP2_MIDDLE3_AWB2_YSLOPE4_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_YSLOPE4_PRE_POS)
#define DSP2_MIDDLE3_AWB2_YSLOPE4_PRE_UMSK                       (~(((1U<<DSP2_MIDDLE3_AWB2_YSLOPE4_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_YSLOPE4_PRE_POS))
#define DSP2_MIDDLE3_AWB2_YWEIGHT0_PRE                           DSP2_MIDDLE3_AWB2_YWEIGHT0_PRE
#define DSP2_MIDDLE3_AWB2_YWEIGHT0_PRE_POS                       (16U)
#define DSP2_MIDDLE3_AWB2_YWEIGHT0_PRE_LEN                       (8U)
#define DSP2_MIDDLE3_AWB2_YWEIGHT0_PRE_MSK                       (((1U<<DSP2_MIDDLE3_AWB2_YWEIGHT0_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_YWEIGHT0_PRE_POS)
#define DSP2_MIDDLE3_AWB2_YWEIGHT0_PRE_UMSK                      (~(((1U<<DSP2_MIDDLE3_AWB2_YWEIGHT0_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_YWEIGHT0_PRE_POS))
#define DSP2_MIDDLE3_AWB2_YWEIGHT1_PRE                           DSP2_MIDDLE3_AWB2_YWEIGHT1_PRE
#define DSP2_MIDDLE3_AWB2_YWEIGHT1_PRE_POS                       (24U)
#define DSP2_MIDDLE3_AWB2_YWEIGHT1_PRE_LEN                       (8U)
#define DSP2_MIDDLE3_AWB2_YWEIGHT1_PRE_MSK                       (((1U<<DSP2_MIDDLE3_AWB2_YWEIGHT1_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_YWEIGHT1_PRE_POS)
#define DSP2_MIDDLE3_AWB2_YWEIGHT1_PRE_UMSK                      (~(((1U<<DSP2_MIDDLE3_AWB2_YWEIGHT1_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_YWEIGHT1_PRE_POS))

/* 0x528 : awb2_sta_l3 */
#define DSP2_MIDDLE3_AWB2_STA_L3_OFFSET                          (0x528)
#define DSP2_MIDDLE3_AWB2_YSLOPE2_PRE                            DSP2_MIDDLE3_AWB2_YSLOPE2_PRE
#define DSP2_MIDDLE3_AWB2_YSLOPE2_PRE_POS                        (0U)
#define DSP2_MIDDLE3_AWB2_YSLOPE2_PRE_LEN                        (9U)
#define DSP2_MIDDLE3_AWB2_YSLOPE2_PRE_MSK                        (((1U<<DSP2_MIDDLE3_AWB2_YSLOPE2_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_YSLOPE2_PRE_POS)
#define DSP2_MIDDLE3_AWB2_YSLOPE2_PRE_UMSK                       (~(((1U<<DSP2_MIDDLE3_AWB2_YSLOPE2_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_YSLOPE2_PRE_POS))
#define DSP2_MIDDLE3_AWB2_YSLOPE3_PRE                            DSP2_MIDDLE3_AWB2_YSLOPE3_PRE
#define DSP2_MIDDLE3_AWB2_YSLOPE3_PRE_POS                        (16U)
#define DSP2_MIDDLE3_AWB2_YSLOPE3_PRE_LEN                        (9U)
#define DSP2_MIDDLE3_AWB2_YSLOPE3_PRE_MSK                        (((1U<<DSP2_MIDDLE3_AWB2_YSLOPE3_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_YSLOPE3_PRE_POS)
#define DSP2_MIDDLE3_AWB2_YSLOPE3_PRE_UMSK                       (~(((1U<<DSP2_MIDDLE3_AWB2_YSLOPE3_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_YSLOPE3_PRE_POS))

/* 0x52C : awb2_sta_l4 */
#define DSP2_MIDDLE3_AWB2_STA_L4_OFFSET                          (0x52C)
#define DSP2_MIDDLE3_AWB2_YSLOPE0_PRE                            DSP2_MIDDLE3_AWB2_YSLOPE0_PRE
#define DSP2_MIDDLE3_AWB2_YSLOPE0_PRE_POS                        (0U)
#define DSP2_MIDDLE3_AWB2_YSLOPE0_PRE_LEN                        (9U)
#define DSP2_MIDDLE3_AWB2_YSLOPE0_PRE_MSK                        (((1U<<DSP2_MIDDLE3_AWB2_YSLOPE0_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_YSLOPE0_PRE_POS)
#define DSP2_MIDDLE3_AWB2_YSLOPE0_PRE_UMSK                       (~(((1U<<DSP2_MIDDLE3_AWB2_YSLOPE0_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_YSLOPE0_PRE_POS))
#define DSP2_MIDDLE3_AWB2_YSLOPE1_PRE                            DSP2_MIDDLE3_AWB2_YSLOPE1_PRE
#define DSP2_MIDDLE3_AWB2_YSLOPE1_PRE_POS                        (16U)
#define DSP2_MIDDLE3_AWB2_YSLOPE1_PRE_LEN                        (9U)
#define DSP2_MIDDLE3_AWB2_YSLOPE1_PRE_MSK                        (((1U<<DSP2_MIDDLE3_AWB2_YSLOPE1_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_YSLOPE1_PRE_POS)
#define DSP2_MIDDLE3_AWB2_YSLOPE1_PRE_UMSK                       (~(((1U<<DSP2_MIDDLE3_AWB2_YSLOPE1_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_YSLOPE1_PRE_POS))

/* 0x530 : awb2_sta_c0 */
#define DSP2_MIDDLE3_AWB2_STA_C0_OFFSET                          (0x530)
#define DSP2_MIDDLE3_AWB2_UREG4_PRE                              DSP2_MIDDLE3_AWB2_UREG4_PRE
#define DSP2_MIDDLE3_AWB2_UREG4_PRE_POS                          (0U)
#define DSP2_MIDDLE3_AWB2_UREG4_PRE_LEN                          (8U)
#define DSP2_MIDDLE3_AWB2_UREG4_PRE_MSK                          (((1U<<DSP2_MIDDLE3_AWB2_UREG4_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_UREG4_PRE_POS)
#define DSP2_MIDDLE3_AWB2_UREG4_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE3_AWB2_UREG4_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_UREG4_PRE_POS))
#define DSP2_MIDDLE3_AWB2_UREG5_PRE                              DSP2_MIDDLE3_AWB2_UREG5_PRE
#define DSP2_MIDDLE3_AWB2_UREG5_PRE_POS                          (8U)
#define DSP2_MIDDLE3_AWB2_UREG5_PRE_LEN                          (8U)
#define DSP2_MIDDLE3_AWB2_UREG5_PRE_MSK                          (((1U<<DSP2_MIDDLE3_AWB2_UREG5_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_UREG5_PRE_POS)
#define DSP2_MIDDLE3_AWB2_UREG5_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE3_AWB2_UREG5_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_UREG5_PRE_POS))
#define DSP2_MIDDLE3_AWB2_UREG6_PRE                              DSP2_MIDDLE3_AWB2_UREG6_PRE
#define DSP2_MIDDLE3_AWB2_UREG6_PRE_POS                          (16U)
#define DSP2_MIDDLE3_AWB2_UREG6_PRE_LEN                          (8U)
#define DSP2_MIDDLE3_AWB2_UREG6_PRE_MSK                          (((1U<<DSP2_MIDDLE3_AWB2_UREG6_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_UREG6_PRE_POS)
#define DSP2_MIDDLE3_AWB2_UREG6_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE3_AWB2_UREG6_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_UREG6_PRE_POS))
#define DSP2_MIDDLE3_AWB2_UREG7_PRE                              DSP2_MIDDLE3_AWB2_UREG7_PRE
#define DSP2_MIDDLE3_AWB2_UREG7_PRE_POS                          (24U)
#define DSP2_MIDDLE3_AWB2_UREG7_PRE_LEN                          (8U)
#define DSP2_MIDDLE3_AWB2_UREG7_PRE_MSK                          (((1U<<DSP2_MIDDLE3_AWB2_UREG7_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_UREG7_PRE_POS)
#define DSP2_MIDDLE3_AWB2_UREG7_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE3_AWB2_UREG7_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_UREG7_PRE_POS))

/* 0x534 : awb2_sta_c1 */
#define DSP2_MIDDLE3_AWB2_STA_C1_OFFSET                          (0x534)
#define DSP2_MIDDLE3_AWB2_UREG0_PRE                              DSP2_MIDDLE3_AWB2_UREG0_PRE
#define DSP2_MIDDLE3_AWB2_UREG0_PRE_POS                          (0U)
#define DSP2_MIDDLE3_AWB2_UREG0_PRE_LEN                          (8U)
#define DSP2_MIDDLE3_AWB2_UREG0_PRE_MSK                          (((1U<<DSP2_MIDDLE3_AWB2_UREG0_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_UREG0_PRE_POS)
#define DSP2_MIDDLE3_AWB2_UREG0_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE3_AWB2_UREG0_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_UREG0_PRE_POS))
#define DSP2_MIDDLE3_AWB2_UREG1_PRE                              DSP2_MIDDLE3_AWB2_UREG1_PRE
#define DSP2_MIDDLE3_AWB2_UREG1_PRE_POS                          (8U)
#define DSP2_MIDDLE3_AWB2_UREG1_PRE_LEN                          (8U)
#define DSP2_MIDDLE3_AWB2_UREG1_PRE_MSK                          (((1U<<DSP2_MIDDLE3_AWB2_UREG1_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_UREG1_PRE_POS)
#define DSP2_MIDDLE3_AWB2_UREG1_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE3_AWB2_UREG1_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_UREG1_PRE_POS))
#define DSP2_MIDDLE3_AWB2_UREG2_PRE                              DSP2_MIDDLE3_AWB2_UREG2_PRE
#define DSP2_MIDDLE3_AWB2_UREG2_PRE_POS                          (16U)
#define DSP2_MIDDLE3_AWB2_UREG2_PRE_LEN                          (8U)
#define DSP2_MIDDLE3_AWB2_UREG2_PRE_MSK                          (((1U<<DSP2_MIDDLE3_AWB2_UREG2_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_UREG2_PRE_POS)
#define DSP2_MIDDLE3_AWB2_UREG2_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE3_AWB2_UREG2_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_UREG2_PRE_POS))
#define DSP2_MIDDLE3_AWB2_UREG3_PRE                              DSP2_MIDDLE3_AWB2_UREG3_PRE
#define DSP2_MIDDLE3_AWB2_UREG3_PRE_POS                          (24U)
#define DSP2_MIDDLE3_AWB2_UREG3_PRE_LEN                          (8U)
#define DSP2_MIDDLE3_AWB2_UREG3_PRE_MSK                          (((1U<<DSP2_MIDDLE3_AWB2_UREG3_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_UREG3_PRE_POS)
#define DSP2_MIDDLE3_AWB2_UREG3_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE3_AWB2_UREG3_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_UREG3_PRE_POS))

/* 0x538 : awb2_sta_c2 */
#define DSP2_MIDDLE3_AWB2_STA_C2_OFFSET                          (0x538)
#define DSP2_MIDDLE3_AWB2_VREG4_PRE                              DSP2_MIDDLE3_AWB2_VREG4_PRE
#define DSP2_MIDDLE3_AWB2_VREG4_PRE_POS                          (0U)
#define DSP2_MIDDLE3_AWB2_VREG4_PRE_LEN                          (8U)
#define DSP2_MIDDLE3_AWB2_VREG4_PRE_MSK                          (((1U<<DSP2_MIDDLE3_AWB2_VREG4_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_VREG4_PRE_POS)
#define DSP2_MIDDLE3_AWB2_VREG4_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE3_AWB2_VREG4_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_VREG4_PRE_POS))
#define DSP2_MIDDLE3_AWB2_VREG5_PRE                              DSP2_MIDDLE3_AWB2_VREG5_PRE
#define DSP2_MIDDLE3_AWB2_VREG5_PRE_POS                          (8U)
#define DSP2_MIDDLE3_AWB2_VREG5_PRE_LEN                          (8U)
#define DSP2_MIDDLE3_AWB2_VREG5_PRE_MSK                          (((1U<<DSP2_MIDDLE3_AWB2_VREG5_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_VREG5_PRE_POS)
#define DSP2_MIDDLE3_AWB2_VREG5_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE3_AWB2_VREG5_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_VREG5_PRE_POS))
#define DSP2_MIDDLE3_AWB2_VREG6_PRE                              DSP2_MIDDLE3_AWB2_VREG6_PRE
#define DSP2_MIDDLE3_AWB2_VREG6_PRE_POS                          (16U)
#define DSP2_MIDDLE3_AWB2_VREG6_PRE_LEN                          (8U)
#define DSP2_MIDDLE3_AWB2_VREG6_PRE_MSK                          (((1U<<DSP2_MIDDLE3_AWB2_VREG6_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_VREG6_PRE_POS)
#define DSP2_MIDDLE3_AWB2_VREG6_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE3_AWB2_VREG6_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_VREG6_PRE_POS))
#define DSP2_MIDDLE3_AWB2_VREG7_PRE                              DSP2_MIDDLE3_AWB2_VREG7_PRE
#define DSP2_MIDDLE3_AWB2_VREG7_PRE_POS                          (24U)
#define DSP2_MIDDLE3_AWB2_VREG7_PRE_LEN                          (8U)
#define DSP2_MIDDLE3_AWB2_VREG7_PRE_MSK                          (((1U<<DSP2_MIDDLE3_AWB2_VREG7_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_VREG7_PRE_POS)
#define DSP2_MIDDLE3_AWB2_VREG7_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE3_AWB2_VREG7_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_VREG7_PRE_POS))

/* 0x53C : awb2_sta_c3 */
#define DSP2_MIDDLE3_AWB2_STA_C3_OFFSET                          (0x53C)
#define DSP2_MIDDLE3_AWB2_VREG0_PRE                              DSP2_MIDDLE3_AWB2_VREG0_PRE
#define DSP2_MIDDLE3_AWB2_VREG0_PRE_POS                          (0U)
#define DSP2_MIDDLE3_AWB2_VREG0_PRE_LEN                          (8U)
#define DSP2_MIDDLE3_AWB2_VREG0_PRE_MSK                          (((1U<<DSP2_MIDDLE3_AWB2_VREG0_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_VREG0_PRE_POS)
#define DSP2_MIDDLE3_AWB2_VREG0_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE3_AWB2_VREG0_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_VREG0_PRE_POS))
#define DSP2_MIDDLE3_AWB2_VREG1_PRE                              DSP2_MIDDLE3_AWB2_VREG1_PRE
#define DSP2_MIDDLE3_AWB2_VREG1_PRE_POS                          (8U)
#define DSP2_MIDDLE3_AWB2_VREG1_PRE_LEN                          (8U)
#define DSP2_MIDDLE3_AWB2_VREG1_PRE_MSK                          (((1U<<DSP2_MIDDLE3_AWB2_VREG1_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_VREG1_PRE_POS)
#define DSP2_MIDDLE3_AWB2_VREG1_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE3_AWB2_VREG1_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_VREG1_PRE_POS))
#define DSP2_MIDDLE3_AWB2_VREG2_PRE                              DSP2_MIDDLE3_AWB2_VREG2_PRE
#define DSP2_MIDDLE3_AWB2_VREG2_PRE_POS                          (16U)
#define DSP2_MIDDLE3_AWB2_VREG2_PRE_LEN                          (8U)
#define DSP2_MIDDLE3_AWB2_VREG2_PRE_MSK                          (((1U<<DSP2_MIDDLE3_AWB2_VREG2_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_VREG2_PRE_POS)
#define DSP2_MIDDLE3_AWB2_VREG2_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE3_AWB2_VREG2_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_VREG2_PRE_POS))
#define DSP2_MIDDLE3_AWB2_VREG3_PRE                              DSP2_MIDDLE3_AWB2_VREG3_PRE
#define DSP2_MIDDLE3_AWB2_VREG3_PRE_POS                          (24U)
#define DSP2_MIDDLE3_AWB2_VREG3_PRE_LEN                          (8U)
#define DSP2_MIDDLE3_AWB2_VREG3_PRE_MSK                          (((1U<<DSP2_MIDDLE3_AWB2_VREG3_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_VREG3_PRE_POS)
#define DSP2_MIDDLE3_AWB2_VREG3_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE3_AWB2_VREG3_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_VREG3_PRE_POS))

/* 0x540 : awb2_sta_c4 */
#define DSP2_MIDDLE3_AWB2_STA_C4_OFFSET                          (0x540)
#define DSP2_MIDDLE3_AWB2_CTH4_PRE                               DSP2_MIDDLE3_AWB2_CTH4_PRE
#define DSP2_MIDDLE3_AWB2_CTH4_PRE_POS                           (0U)
#define DSP2_MIDDLE3_AWB2_CTH4_PRE_LEN                           (6U)
#define DSP2_MIDDLE3_AWB2_CTH4_PRE_MSK                           (((1U<<DSP2_MIDDLE3_AWB2_CTH4_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_CTH4_PRE_POS)
#define DSP2_MIDDLE3_AWB2_CTH4_PRE_UMSK                          (~(((1U<<DSP2_MIDDLE3_AWB2_CTH4_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_CTH4_PRE_POS))
#define DSP2_MIDDLE3_AWB2_CTH5_PRE                               DSP2_MIDDLE3_AWB2_CTH5_PRE
#define DSP2_MIDDLE3_AWB2_CTH5_PRE_POS                           (8U)
#define DSP2_MIDDLE3_AWB2_CTH5_PRE_LEN                           (6U)
#define DSP2_MIDDLE3_AWB2_CTH5_PRE_MSK                           (((1U<<DSP2_MIDDLE3_AWB2_CTH5_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_CTH5_PRE_POS)
#define DSP2_MIDDLE3_AWB2_CTH5_PRE_UMSK                          (~(((1U<<DSP2_MIDDLE3_AWB2_CTH5_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_CTH5_PRE_POS))
#define DSP2_MIDDLE3_AWB2_CTH6_PRE                               DSP2_MIDDLE3_AWB2_CTH6_PRE
#define DSP2_MIDDLE3_AWB2_CTH6_PRE_POS                           (16U)
#define DSP2_MIDDLE3_AWB2_CTH6_PRE_LEN                           (6U)
#define DSP2_MIDDLE3_AWB2_CTH6_PRE_MSK                           (((1U<<DSP2_MIDDLE3_AWB2_CTH6_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_CTH6_PRE_POS)
#define DSP2_MIDDLE3_AWB2_CTH6_PRE_UMSK                          (~(((1U<<DSP2_MIDDLE3_AWB2_CTH6_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_CTH6_PRE_POS))
#define DSP2_MIDDLE3_AWB2_CTH7_PRE                               DSP2_MIDDLE3_AWB2_CTH7_PRE
#define DSP2_MIDDLE3_AWB2_CTH7_PRE_POS                           (24U)
#define DSP2_MIDDLE3_AWB2_CTH7_PRE_LEN                           (6U)
#define DSP2_MIDDLE3_AWB2_CTH7_PRE_MSK                           (((1U<<DSP2_MIDDLE3_AWB2_CTH7_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_CTH7_PRE_POS)
#define DSP2_MIDDLE3_AWB2_CTH7_PRE_UMSK                          (~(((1U<<DSP2_MIDDLE3_AWB2_CTH7_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_CTH7_PRE_POS))

/* 0x544 : awb2_sta_c5 */
#define DSP2_MIDDLE3_AWB2_STA_C5_OFFSET                          (0x544)
#define DSP2_MIDDLE3_AWB2_CTH0_PRE                               DSP2_MIDDLE3_AWB2_CTH0_PRE
#define DSP2_MIDDLE3_AWB2_CTH0_PRE_POS                           (0U)
#define DSP2_MIDDLE3_AWB2_CTH0_PRE_LEN                           (6U)
#define DSP2_MIDDLE3_AWB2_CTH0_PRE_MSK                           (((1U<<DSP2_MIDDLE3_AWB2_CTH0_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_CTH0_PRE_POS)
#define DSP2_MIDDLE3_AWB2_CTH0_PRE_UMSK                          (~(((1U<<DSP2_MIDDLE3_AWB2_CTH0_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_CTH0_PRE_POS))
#define DSP2_MIDDLE3_AWB2_CTH1_PRE                               DSP2_MIDDLE3_AWB2_CTH1_PRE
#define DSP2_MIDDLE3_AWB2_CTH1_PRE_POS                           (8U)
#define DSP2_MIDDLE3_AWB2_CTH1_PRE_LEN                           (6U)
#define DSP2_MIDDLE3_AWB2_CTH1_PRE_MSK                           (((1U<<DSP2_MIDDLE3_AWB2_CTH1_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_CTH1_PRE_POS)
#define DSP2_MIDDLE3_AWB2_CTH1_PRE_UMSK                          (~(((1U<<DSP2_MIDDLE3_AWB2_CTH1_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_CTH1_PRE_POS))
#define DSP2_MIDDLE3_AWB2_CTH2_PRE                               DSP2_MIDDLE3_AWB2_CTH2_PRE
#define DSP2_MIDDLE3_AWB2_CTH2_PRE_POS                           (16U)
#define DSP2_MIDDLE3_AWB2_CTH2_PRE_LEN                           (6U)
#define DSP2_MIDDLE3_AWB2_CTH2_PRE_MSK                           (((1U<<DSP2_MIDDLE3_AWB2_CTH2_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_CTH2_PRE_POS)
#define DSP2_MIDDLE3_AWB2_CTH2_PRE_UMSK                          (~(((1U<<DSP2_MIDDLE3_AWB2_CTH2_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_CTH2_PRE_POS))
#define DSP2_MIDDLE3_AWB2_CTH3_PRE                               DSP2_MIDDLE3_AWB2_CTH3_PRE
#define DSP2_MIDDLE3_AWB2_CTH3_PRE_POS                           (24U)
#define DSP2_MIDDLE3_AWB2_CTH3_PRE_LEN                           (6U)
#define DSP2_MIDDLE3_AWB2_CTH3_PRE_MSK                           (((1U<<DSP2_MIDDLE3_AWB2_CTH3_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_CTH3_PRE_POS)
#define DSP2_MIDDLE3_AWB2_CTH3_PRE_UMSK                          (~(((1U<<DSP2_MIDDLE3_AWB2_CTH3_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_CTH3_PRE_POS))

/* 0x548 : awb2_sta_c6 */
#define DSP2_MIDDLE3_AWB2_STA_C6_OFFSET                          (0x548)
#define DSP2_MIDDLE3_AWB2_CSLOPE4_PRE                            DSP2_MIDDLE3_AWB2_CSLOPE4_PRE
#define DSP2_MIDDLE3_AWB2_CSLOPE4_PRE_POS                        (0U)
#define DSP2_MIDDLE3_AWB2_CSLOPE4_PRE_LEN                        (8U)
#define DSP2_MIDDLE3_AWB2_CSLOPE4_PRE_MSK                        (((1U<<DSP2_MIDDLE3_AWB2_CSLOPE4_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_CSLOPE4_PRE_POS)
#define DSP2_MIDDLE3_AWB2_CSLOPE4_PRE_UMSK                       (~(((1U<<DSP2_MIDDLE3_AWB2_CSLOPE4_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_CSLOPE4_PRE_POS))
#define DSP2_MIDDLE3_AWB2_CSLOPE5_PRE                            DSP2_MIDDLE3_AWB2_CSLOPE5_PRE
#define DSP2_MIDDLE3_AWB2_CSLOPE5_PRE_POS                        (8U)
#define DSP2_MIDDLE3_AWB2_CSLOPE5_PRE_LEN                        (8U)
#define DSP2_MIDDLE3_AWB2_CSLOPE5_PRE_MSK                        (((1U<<DSP2_MIDDLE3_AWB2_CSLOPE5_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_CSLOPE5_PRE_POS)
#define DSP2_MIDDLE3_AWB2_CSLOPE5_PRE_UMSK                       (~(((1U<<DSP2_MIDDLE3_AWB2_CSLOPE5_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_CSLOPE5_PRE_POS))
#define DSP2_MIDDLE3_AWB2_CSLOPE6_PRE                            DSP2_MIDDLE3_AWB2_CSLOPE6_PRE
#define DSP2_MIDDLE3_AWB2_CSLOPE6_PRE_POS                        (16U)
#define DSP2_MIDDLE3_AWB2_CSLOPE6_PRE_LEN                        (8U)
#define DSP2_MIDDLE3_AWB2_CSLOPE6_PRE_MSK                        (((1U<<DSP2_MIDDLE3_AWB2_CSLOPE6_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_CSLOPE6_PRE_POS)
#define DSP2_MIDDLE3_AWB2_CSLOPE6_PRE_UMSK                       (~(((1U<<DSP2_MIDDLE3_AWB2_CSLOPE6_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_CSLOPE6_PRE_POS))
#define DSP2_MIDDLE3_AWB2_CSLOPE7_PRE                            DSP2_MIDDLE3_AWB2_CSLOPE7_PRE
#define DSP2_MIDDLE3_AWB2_CSLOPE7_PRE_POS                        (24U)
#define DSP2_MIDDLE3_AWB2_CSLOPE7_PRE_LEN                        (8U)
#define DSP2_MIDDLE3_AWB2_CSLOPE7_PRE_MSK                        (((1U<<DSP2_MIDDLE3_AWB2_CSLOPE7_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_CSLOPE7_PRE_POS)
#define DSP2_MIDDLE3_AWB2_CSLOPE7_PRE_UMSK                       (~(((1U<<DSP2_MIDDLE3_AWB2_CSLOPE7_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_CSLOPE7_PRE_POS))

/* 0x54C : awb2_sta_c7 */
#define DSP2_MIDDLE3_AWB2_STA_C7_OFFSET                          (0x54C)
#define DSP2_MIDDLE3_AWB2_CSLOPE0_PRE                            DSP2_MIDDLE3_AWB2_CSLOPE0_PRE
#define DSP2_MIDDLE3_AWB2_CSLOPE0_PRE_POS                        (0U)
#define DSP2_MIDDLE3_AWB2_CSLOPE0_PRE_LEN                        (8U)
#define DSP2_MIDDLE3_AWB2_CSLOPE0_PRE_MSK                        (((1U<<DSP2_MIDDLE3_AWB2_CSLOPE0_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_CSLOPE0_PRE_POS)
#define DSP2_MIDDLE3_AWB2_CSLOPE0_PRE_UMSK                       (~(((1U<<DSP2_MIDDLE3_AWB2_CSLOPE0_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_CSLOPE0_PRE_POS))
#define DSP2_MIDDLE3_AWB2_CSLOPE1_PRE                            DSP2_MIDDLE3_AWB2_CSLOPE1_PRE
#define DSP2_MIDDLE3_AWB2_CSLOPE1_PRE_POS                        (8U)
#define DSP2_MIDDLE3_AWB2_CSLOPE1_PRE_LEN                        (8U)
#define DSP2_MIDDLE3_AWB2_CSLOPE1_PRE_MSK                        (((1U<<DSP2_MIDDLE3_AWB2_CSLOPE1_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_CSLOPE1_PRE_POS)
#define DSP2_MIDDLE3_AWB2_CSLOPE1_PRE_UMSK                       (~(((1U<<DSP2_MIDDLE3_AWB2_CSLOPE1_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_CSLOPE1_PRE_POS))
#define DSP2_MIDDLE3_AWB2_CSLOPE2_PRE                            DSP2_MIDDLE3_AWB2_CSLOPE2_PRE
#define DSP2_MIDDLE3_AWB2_CSLOPE2_PRE_POS                        (16U)
#define DSP2_MIDDLE3_AWB2_CSLOPE2_PRE_LEN                        (8U)
#define DSP2_MIDDLE3_AWB2_CSLOPE2_PRE_MSK                        (((1U<<DSP2_MIDDLE3_AWB2_CSLOPE2_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_CSLOPE2_PRE_POS)
#define DSP2_MIDDLE3_AWB2_CSLOPE2_PRE_UMSK                       (~(((1U<<DSP2_MIDDLE3_AWB2_CSLOPE2_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_CSLOPE2_PRE_POS))
#define DSP2_MIDDLE3_AWB2_CSLOPE3_PRE                            DSP2_MIDDLE3_AWB2_CSLOPE3_PRE
#define DSP2_MIDDLE3_AWB2_CSLOPE3_PRE_POS                        (24U)
#define DSP2_MIDDLE3_AWB2_CSLOPE3_PRE_LEN                        (8U)
#define DSP2_MIDDLE3_AWB2_CSLOPE3_PRE_MSK                        (((1U<<DSP2_MIDDLE3_AWB2_CSLOPE3_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_CSLOPE3_PRE_POS)
#define DSP2_MIDDLE3_AWB2_CSLOPE3_PRE_UMSK                       (~(((1U<<DSP2_MIDDLE3_AWB2_CSLOPE3_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_CSLOPE3_PRE_POS))

/* 0x550 : awb2_sta_r0 */
#define DSP2_MIDDLE3_AWB2_STA_R0_OFFSET                          (0x550)
#define DSP2_MIDDLE3_AWB2_G_AVG0_R                               DSP2_MIDDLE3_AWB2_G_AVG0_R
#define DSP2_MIDDLE3_AWB2_G_AVG0_R_POS                           (0U)
#define DSP2_MIDDLE3_AWB2_G_AVG0_R_LEN                           (12U)
#define DSP2_MIDDLE3_AWB2_G_AVG0_R_MSK                           (((1U<<DSP2_MIDDLE3_AWB2_G_AVG0_R_LEN)-1)<<DSP2_MIDDLE3_AWB2_G_AVG0_R_POS)
#define DSP2_MIDDLE3_AWB2_G_AVG0_R_UMSK                          (~(((1U<<DSP2_MIDDLE3_AWB2_G_AVG0_R_LEN)-1)<<DSP2_MIDDLE3_AWB2_G_AVG0_R_POS))
#define DSP2_MIDDLE3_AWB2_R_AVG0_R                               DSP2_MIDDLE3_AWB2_R_AVG0_R
#define DSP2_MIDDLE3_AWB2_R_AVG0_R_POS                           (16U)
#define DSP2_MIDDLE3_AWB2_R_AVG0_R_LEN                           (12U)
#define DSP2_MIDDLE3_AWB2_R_AVG0_R_MSK                           (((1U<<DSP2_MIDDLE3_AWB2_R_AVG0_R_LEN)-1)<<DSP2_MIDDLE3_AWB2_R_AVG0_R_POS)
#define DSP2_MIDDLE3_AWB2_R_AVG0_R_UMSK                          (~(((1U<<DSP2_MIDDLE3_AWB2_R_AVG0_R_LEN)-1)<<DSP2_MIDDLE3_AWB2_R_AVG0_R_POS))

/* 0x554 : awb2_sta_r1 */
#define DSP2_MIDDLE3_AWB2_STA_R1_OFFSET                          (0x554)
#define DSP2_MIDDLE3_AWB2_WHITE_RATIO0_R                         DSP2_MIDDLE3_AWB2_WHITE_RATIO0_R
#define DSP2_MIDDLE3_AWB2_WHITE_RATIO0_R_POS                     (0U)
#define DSP2_MIDDLE3_AWB2_WHITE_RATIO0_R_LEN                     (15U)
#define DSP2_MIDDLE3_AWB2_WHITE_RATIO0_R_MSK                     (((1U<<DSP2_MIDDLE3_AWB2_WHITE_RATIO0_R_LEN)-1)<<DSP2_MIDDLE3_AWB2_WHITE_RATIO0_R_POS)
#define DSP2_MIDDLE3_AWB2_WHITE_RATIO0_R_UMSK                    (~(((1U<<DSP2_MIDDLE3_AWB2_WHITE_RATIO0_R_LEN)-1)<<DSP2_MIDDLE3_AWB2_WHITE_RATIO0_R_POS))
#define DSP2_MIDDLE3_AWB2_B_AVG0_R                               DSP2_MIDDLE3_AWB2_B_AVG0_R
#define DSP2_MIDDLE3_AWB2_B_AVG0_R_POS                           (16U)
#define DSP2_MIDDLE3_AWB2_B_AVG0_R_LEN                           (12U)
#define DSP2_MIDDLE3_AWB2_B_AVG0_R_MSK                           (((1U<<DSP2_MIDDLE3_AWB2_B_AVG0_R_LEN)-1)<<DSP2_MIDDLE3_AWB2_B_AVG0_R_POS)
#define DSP2_MIDDLE3_AWB2_B_AVG0_R_UMSK                          (~(((1U<<DSP2_MIDDLE3_AWB2_B_AVG0_R_LEN)-1)<<DSP2_MIDDLE3_AWB2_B_AVG0_R_POS))

/* 0x558 : awb2_sta_r2 */
#define DSP2_MIDDLE3_AWB2_STA_R2_OFFSET                          (0x558)
#define DSP2_MIDDLE3_AWB2_G_AVG1_R                               DSP2_MIDDLE3_AWB2_G_AVG1_R
#define DSP2_MIDDLE3_AWB2_G_AVG1_R_POS                           (0U)
#define DSP2_MIDDLE3_AWB2_G_AVG1_R_LEN                           (12U)
#define DSP2_MIDDLE3_AWB2_G_AVG1_R_MSK                           (((1U<<DSP2_MIDDLE3_AWB2_G_AVG1_R_LEN)-1)<<DSP2_MIDDLE3_AWB2_G_AVG1_R_POS)
#define DSP2_MIDDLE3_AWB2_G_AVG1_R_UMSK                          (~(((1U<<DSP2_MIDDLE3_AWB2_G_AVG1_R_LEN)-1)<<DSP2_MIDDLE3_AWB2_G_AVG1_R_POS))
#define DSP2_MIDDLE3_AWB2_R_AVG1_R                               DSP2_MIDDLE3_AWB2_R_AVG1_R
#define DSP2_MIDDLE3_AWB2_R_AVG1_R_POS                           (16U)
#define DSP2_MIDDLE3_AWB2_R_AVG1_R_LEN                           (12U)
#define DSP2_MIDDLE3_AWB2_R_AVG1_R_MSK                           (((1U<<DSP2_MIDDLE3_AWB2_R_AVG1_R_LEN)-1)<<DSP2_MIDDLE3_AWB2_R_AVG1_R_POS)
#define DSP2_MIDDLE3_AWB2_R_AVG1_R_UMSK                          (~(((1U<<DSP2_MIDDLE3_AWB2_R_AVG1_R_LEN)-1)<<DSP2_MIDDLE3_AWB2_R_AVG1_R_POS))

/* 0x55C : awb2_sta_r3 */
#define DSP2_MIDDLE3_AWB2_STA_R3_OFFSET                          (0x55C)
#define DSP2_MIDDLE3_AWB2_WHITE_RATIO1_R                         DSP2_MIDDLE3_AWB2_WHITE_RATIO1_R
#define DSP2_MIDDLE3_AWB2_WHITE_RATIO1_R_POS                     (0U)
#define DSP2_MIDDLE3_AWB2_WHITE_RATIO1_R_LEN                     (15U)
#define DSP2_MIDDLE3_AWB2_WHITE_RATIO1_R_MSK                     (((1U<<DSP2_MIDDLE3_AWB2_WHITE_RATIO1_R_LEN)-1)<<DSP2_MIDDLE3_AWB2_WHITE_RATIO1_R_POS)
#define DSP2_MIDDLE3_AWB2_WHITE_RATIO1_R_UMSK                    (~(((1U<<DSP2_MIDDLE3_AWB2_WHITE_RATIO1_R_LEN)-1)<<DSP2_MIDDLE3_AWB2_WHITE_RATIO1_R_POS))
#define DSP2_MIDDLE3_AWB2_B_AVG1_R                               DSP2_MIDDLE3_AWB2_B_AVG1_R
#define DSP2_MIDDLE3_AWB2_B_AVG1_R_POS                           (16U)
#define DSP2_MIDDLE3_AWB2_B_AVG1_R_LEN                           (12U)
#define DSP2_MIDDLE3_AWB2_B_AVG1_R_MSK                           (((1U<<DSP2_MIDDLE3_AWB2_B_AVG1_R_LEN)-1)<<DSP2_MIDDLE3_AWB2_B_AVG1_R_POS)
#define DSP2_MIDDLE3_AWB2_B_AVG1_R_UMSK                          (~(((1U<<DSP2_MIDDLE3_AWB2_B_AVG1_R_LEN)-1)<<DSP2_MIDDLE3_AWB2_B_AVG1_R_POS))

/* 0x560 : awb2_sta_r4 */
#define DSP2_MIDDLE3_AWB2_STA_R4_OFFSET                          (0x560)
#define DSP2_MIDDLE3_AWB2_WHITER_SUMH0_R                         DSP2_MIDDLE3_AWB2_WHITER_SUMH0_R
#define DSP2_MIDDLE3_AWB2_WHITER_SUMH0_R_POS                     (0U)
#define DSP2_MIDDLE3_AWB2_WHITER_SUMH0_R_LEN                     (32U)
#define DSP2_MIDDLE3_AWB2_WHITER_SUMH0_R_MSK                     (((1U<<DSP2_MIDDLE3_AWB2_WHITER_SUMH0_R_LEN)-1)<<DSP2_MIDDLE3_AWB2_WHITER_SUMH0_R_POS)
#define DSP2_MIDDLE3_AWB2_WHITER_SUMH0_R_UMSK                    (~(((1U<<DSP2_MIDDLE3_AWB2_WHITER_SUMH0_R_LEN)-1)<<DSP2_MIDDLE3_AWB2_WHITER_SUMH0_R_POS))

/* 0x564 : awb2_sta_r5 */
#define DSP2_MIDDLE3_AWB2_STA_R5_OFFSET                          (0x564)
#define DSP2_MIDDLE3_AWB2_WHITER_SUML1_R                         DSP2_MIDDLE3_AWB2_WHITER_SUML1_R
#define DSP2_MIDDLE3_AWB2_WHITER_SUML1_R_POS                     (0U)
#define DSP2_MIDDLE3_AWB2_WHITER_SUML1_R_LEN                     (9U)
#define DSP2_MIDDLE3_AWB2_WHITER_SUML1_R_MSK                     (((1U<<DSP2_MIDDLE3_AWB2_WHITER_SUML1_R_LEN)-1)<<DSP2_MIDDLE3_AWB2_WHITER_SUML1_R_POS)
#define DSP2_MIDDLE3_AWB2_WHITER_SUML1_R_UMSK                    (~(((1U<<DSP2_MIDDLE3_AWB2_WHITER_SUML1_R_LEN)-1)<<DSP2_MIDDLE3_AWB2_WHITER_SUML1_R_POS))
#define DSP2_MIDDLE3_AWB2_WHITER_SUML0_R                         DSP2_MIDDLE3_AWB2_WHITER_SUML0_R
#define DSP2_MIDDLE3_AWB2_WHITER_SUML0_R_POS                     (16U)
#define DSP2_MIDDLE3_AWB2_WHITER_SUML0_R_LEN                     (9U)
#define DSP2_MIDDLE3_AWB2_WHITER_SUML0_R_MSK                     (((1U<<DSP2_MIDDLE3_AWB2_WHITER_SUML0_R_LEN)-1)<<DSP2_MIDDLE3_AWB2_WHITER_SUML0_R_POS)
#define DSP2_MIDDLE3_AWB2_WHITER_SUML0_R_UMSK                    (~(((1U<<DSP2_MIDDLE3_AWB2_WHITER_SUML0_R_LEN)-1)<<DSP2_MIDDLE3_AWB2_WHITER_SUML0_R_POS))

/* 0x568 : awb2_sta_r6 */
#define DSP2_MIDDLE3_AWB2_STA_R6_OFFSET                          (0x568)
#define DSP2_MIDDLE3_AWB2_WHITER_SUMH1_R                         DSP2_MIDDLE3_AWB2_WHITER_SUMH1_R
#define DSP2_MIDDLE3_AWB2_WHITER_SUMH1_R_POS                     (0U)
#define DSP2_MIDDLE3_AWB2_WHITER_SUMH1_R_LEN                     (32U)
#define DSP2_MIDDLE3_AWB2_WHITER_SUMH1_R_MSK                     (((1U<<DSP2_MIDDLE3_AWB2_WHITER_SUMH1_R_LEN)-1)<<DSP2_MIDDLE3_AWB2_WHITER_SUMH1_R_POS)
#define DSP2_MIDDLE3_AWB2_WHITER_SUMH1_R_UMSK                    (~(((1U<<DSP2_MIDDLE3_AWB2_WHITER_SUMH1_R_LEN)-1)<<DSP2_MIDDLE3_AWB2_WHITER_SUMH1_R_POS))

/* 0x56C : awb2_sta_r7 */
#define DSP2_MIDDLE3_AWB2_STA_R7_OFFSET                          (0x56C)
#define DSP2_MIDDLE3_AWB2_WHITEG_SUMH0_R                         DSP2_MIDDLE3_AWB2_WHITEG_SUMH0_R
#define DSP2_MIDDLE3_AWB2_WHITEG_SUMH0_R_POS                     (0U)
#define DSP2_MIDDLE3_AWB2_WHITEG_SUMH0_R_LEN                     (32U)
#define DSP2_MIDDLE3_AWB2_WHITEG_SUMH0_R_MSK                     (((1U<<DSP2_MIDDLE3_AWB2_WHITEG_SUMH0_R_LEN)-1)<<DSP2_MIDDLE3_AWB2_WHITEG_SUMH0_R_POS)
#define DSP2_MIDDLE3_AWB2_WHITEG_SUMH0_R_UMSK                    (~(((1U<<DSP2_MIDDLE3_AWB2_WHITEG_SUMH0_R_LEN)-1)<<DSP2_MIDDLE3_AWB2_WHITEG_SUMH0_R_POS))

/* 0x570 : awb2_sta_r8 */
#define DSP2_MIDDLE3_AWB2_STA_R8_OFFSET                          (0x570)
#define DSP2_MIDDLE3_AWB2_WHITEG_SUML1_R                         DSP2_MIDDLE3_AWB2_WHITEG_SUML1_R
#define DSP2_MIDDLE3_AWB2_WHITEG_SUML1_R_POS                     (0U)
#define DSP2_MIDDLE3_AWB2_WHITEG_SUML1_R_LEN                     (9U)
#define DSP2_MIDDLE3_AWB2_WHITEG_SUML1_R_MSK                     (((1U<<DSP2_MIDDLE3_AWB2_WHITEG_SUML1_R_LEN)-1)<<DSP2_MIDDLE3_AWB2_WHITEG_SUML1_R_POS)
#define DSP2_MIDDLE3_AWB2_WHITEG_SUML1_R_UMSK                    (~(((1U<<DSP2_MIDDLE3_AWB2_WHITEG_SUML1_R_LEN)-1)<<DSP2_MIDDLE3_AWB2_WHITEG_SUML1_R_POS))
#define DSP2_MIDDLE3_AWB2_WHITEG_SUML0_R                         DSP2_MIDDLE3_AWB2_WHITEG_SUML0_R
#define DSP2_MIDDLE3_AWB2_WHITEG_SUML0_R_POS                     (16U)
#define DSP2_MIDDLE3_AWB2_WHITEG_SUML0_R_LEN                     (9U)
#define DSP2_MIDDLE3_AWB2_WHITEG_SUML0_R_MSK                     (((1U<<DSP2_MIDDLE3_AWB2_WHITEG_SUML0_R_LEN)-1)<<DSP2_MIDDLE3_AWB2_WHITEG_SUML0_R_POS)
#define DSP2_MIDDLE3_AWB2_WHITEG_SUML0_R_UMSK                    (~(((1U<<DSP2_MIDDLE3_AWB2_WHITEG_SUML0_R_LEN)-1)<<DSP2_MIDDLE3_AWB2_WHITEG_SUML0_R_POS))

/* 0x574 : awb2_sta_r9 */
#define DSP2_MIDDLE3_AWB2_STA_R9_OFFSET                          (0x574)
#define DSP2_MIDDLE3_AWB2_WHITEG_SUMH1_R                         DSP2_MIDDLE3_AWB2_WHITEG_SUMH1_R
#define DSP2_MIDDLE3_AWB2_WHITEG_SUMH1_R_POS                     (0U)
#define DSP2_MIDDLE3_AWB2_WHITEG_SUMH1_R_LEN                     (32U)
#define DSP2_MIDDLE3_AWB2_WHITEG_SUMH1_R_MSK                     (((1U<<DSP2_MIDDLE3_AWB2_WHITEG_SUMH1_R_LEN)-1)<<DSP2_MIDDLE3_AWB2_WHITEG_SUMH1_R_POS)
#define DSP2_MIDDLE3_AWB2_WHITEG_SUMH1_R_UMSK                    (~(((1U<<DSP2_MIDDLE3_AWB2_WHITEG_SUMH1_R_LEN)-1)<<DSP2_MIDDLE3_AWB2_WHITEG_SUMH1_R_POS))

/* 0x578 : awb2_sta_ra */
#define DSP2_MIDDLE3_AWB2_STA_RA_OFFSET                          (0x578)
#define DSP2_MIDDLE3_AWB2_WHITEB_SUMH0_R                         DSP2_MIDDLE3_AWB2_WHITEB_SUMH0_R
#define DSP2_MIDDLE3_AWB2_WHITEB_SUMH0_R_POS                     (0U)
#define DSP2_MIDDLE3_AWB2_WHITEB_SUMH0_R_LEN                     (32U)
#define DSP2_MIDDLE3_AWB2_WHITEB_SUMH0_R_MSK                     (((1U<<DSP2_MIDDLE3_AWB2_WHITEB_SUMH0_R_LEN)-1)<<DSP2_MIDDLE3_AWB2_WHITEB_SUMH0_R_POS)
#define DSP2_MIDDLE3_AWB2_WHITEB_SUMH0_R_UMSK                    (~(((1U<<DSP2_MIDDLE3_AWB2_WHITEB_SUMH0_R_LEN)-1)<<DSP2_MIDDLE3_AWB2_WHITEB_SUMH0_R_POS))

/* 0x57C : awb2_sta_rb */
#define DSP2_MIDDLE3_AWB2_STA_RB_OFFSET                          (0x57C)
#define DSP2_MIDDLE3_AWB2_WHITEB_SUML1_R                         DSP2_MIDDLE3_AWB2_WHITEB_SUML1_R
#define DSP2_MIDDLE3_AWB2_WHITEB_SUML1_R_POS                     (0U)
#define DSP2_MIDDLE3_AWB2_WHITEB_SUML1_R_LEN                     (9U)
#define DSP2_MIDDLE3_AWB2_WHITEB_SUML1_R_MSK                     (((1U<<DSP2_MIDDLE3_AWB2_WHITEB_SUML1_R_LEN)-1)<<DSP2_MIDDLE3_AWB2_WHITEB_SUML1_R_POS)
#define DSP2_MIDDLE3_AWB2_WHITEB_SUML1_R_UMSK                    (~(((1U<<DSP2_MIDDLE3_AWB2_WHITEB_SUML1_R_LEN)-1)<<DSP2_MIDDLE3_AWB2_WHITEB_SUML1_R_POS))
#define DSP2_MIDDLE3_AWB2_WHITEB_SUML0_R                         DSP2_MIDDLE3_AWB2_WHITEB_SUML0_R
#define DSP2_MIDDLE3_AWB2_WHITEB_SUML0_R_POS                     (16U)
#define DSP2_MIDDLE3_AWB2_WHITEB_SUML0_R_LEN                     (9U)
#define DSP2_MIDDLE3_AWB2_WHITEB_SUML0_R_MSK                     (((1U<<DSP2_MIDDLE3_AWB2_WHITEB_SUML0_R_LEN)-1)<<DSP2_MIDDLE3_AWB2_WHITEB_SUML0_R_POS)
#define DSP2_MIDDLE3_AWB2_WHITEB_SUML0_R_UMSK                    (~(((1U<<DSP2_MIDDLE3_AWB2_WHITEB_SUML0_R_LEN)-1)<<DSP2_MIDDLE3_AWB2_WHITEB_SUML0_R_POS))

/* 0x580 : awb2_sta_rc */
#define DSP2_MIDDLE3_AWB2_STA_RC_OFFSET                          (0x580)
#define DSP2_MIDDLE3_AWB2_WHITEB_SUMH1_R                         DSP2_MIDDLE3_AWB2_WHITEB_SUMH1_R
#define DSP2_MIDDLE3_AWB2_WHITEB_SUMH1_R_POS                     (0U)
#define DSP2_MIDDLE3_AWB2_WHITEB_SUMH1_R_LEN                     (32U)
#define DSP2_MIDDLE3_AWB2_WHITEB_SUMH1_R_MSK                     (((1U<<DSP2_MIDDLE3_AWB2_WHITEB_SUMH1_R_LEN)-1)<<DSP2_MIDDLE3_AWB2_WHITEB_SUMH1_R_POS)
#define DSP2_MIDDLE3_AWB2_WHITEB_SUMH1_R_UMSK                    (~(((1U<<DSP2_MIDDLE3_AWB2_WHITEB_SUMH1_R_LEN)-1)<<DSP2_MIDDLE3_AWB2_WHITEB_SUMH1_R_POS))

/* 0x584 : awb2_sta_int */
#define DSP2_MIDDLE3_AWB2_STA_INT_OFFSET                         (0x584)
#define DSP2_MIDDLE3_AWB2_GAIN_EN_PRE                            DSP2_MIDDLE3_AWB2_GAIN_EN_PRE
#define DSP2_MIDDLE3_AWB2_GAIN_EN_PRE_POS                        (0U)
#define DSP2_MIDDLE3_AWB2_GAIN_EN_PRE_LEN                        (1U)
#define DSP2_MIDDLE3_AWB2_GAIN_EN_PRE_MSK                        (((1U<<DSP2_MIDDLE3_AWB2_GAIN_EN_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_GAIN_EN_PRE_POS)
#define DSP2_MIDDLE3_AWB2_GAIN_EN_PRE_UMSK                       (~(((1U<<DSP2_MIDDLE3_AWB2_GAIN_EN_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_GAIN_EN_PRE_POS))
#define DSP2_MIDDLE3_AWB2_STAT_EN_PRE                            DSP2_MIDDLE3_AWB2_STAT_EN_PRE
#define DSP2_MIDDLE3_AWB2_STAT_EN_PRE_POS                        (1U)
#define DSP2_MIDDLE3_AWB2_STAT_EN_PRE_LEN                        (1U)
#define DSP2_MIDDLE3_AWB2_STAT_EN_PRE_MSK                        (((1U<<DSP2_MIDDLE3_AWB2_STAT_EN_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_STAT_EN_PRE_POS)
#define DSP2_MIDDLE3_AWB2_STAT_EN_PRE_UMSK                       (~(((1U<<DSP2_MIDDLE3_AWB2_STAT_EN_PRE_LEN)-1)<<DSP2_MIDDLE3_AWB2_STAT_EN_PRE_POS))
#define DSP2_MIDDLE3_AWB2_BUF_IDX_R                              DSP2_MIDDLE3_AWB2_BUF_IDX_R
#define DSP2_MIDDLE3_AWB2_BUF_IDX_R_POS                          (2U)
#define DSP2_MIDDLE3_AWB2_BUF_IDX_R_LEN                          (1U)
#define DSP2_MIDDLE3_AWB2_BUF_IDX_R_MSK                          (((1U<<DSP2_MIDDLE3_AWB2_BUF_IDX_R_LEN)-1)<<DSP2_MIDDLE3_AWB2_BUF_IDX_R_POS)
#define DSP2_MIDDLE3_AWB2_BUF_IDX_R_UMSK                         (~(((1U<<DSP2_MIDDLE3_AWB2_BUF_IDX_R_LEN)-1)<<DSP2_MIDDLE3_AWB2_BUF_IDX_R_POS))
#define DSP2_MIDDLE3_AWB2_W_CNT_R                                DSP2_MIDDLE3_AWB2_W_CNT_R
#define DSP2_MIDDLE3_AWB2_W_CNT_R_POS                            (8U)
#define DSP2_MIDDLE3_AWB2_W_CNT_R_LEN                            (5U)
#define DSP2_MIDDLE3_AWB2_W_CNT_R_MSK                            (((1U<<DSP2_MIDDLE3_AWB2_W_CNT_R_LEN)-1)<<DSP2_MIDDLE3_AWB2_W_CNT_R_POS)
#define DSP2_MIDDLE3_AWB2_W_CNT_R_UMSK                           (~(((1U<<DSP2_MIDDLE3_AWB2_W_CNT_R_LEN)-1)<<DSP2_MIDDLE3_AWB2_W_CNT_R_POS))


struct  dsp2_middle3_reg {
    /* 0x0  reserved */
    uint8_t RESERVED0x0[1280];

    /* 0x500 : awb2_sta_xaxis */
    union {
        struct {
            uint32_t awb2_x_min_pre                 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15                 :  5; /* [15:11],       rsvd,        0x0 */
            uint32_t awb2_x_max_pre                 : 11; /* [26:16],        r/w,      0x77f */
            uint32_t reserved_27_31                 :  5; /* [31:27],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } awb2_sta_xaxis;

    /* 0x504 : awb2_sta_yaxis */
    union {
        struct {
            uint32_t awb2_y_min_pre                 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15                 :  5; /* [15:11],       rsvd,        0x0 */
            uint32_t awb2_y_max_pre                 : 11; /* [26:16],        r/w,      0x437 */
            uint32_t reserved_27_31                 :  5; /* [31:27],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } awb2_sta_yaxis;

    /* 0x508 : awb2_sta_pixel_num */
    union {
        struct {
            uint32_t awb2_pixel_num_pre             : 21; /* [20: 0],        r/w,   0x1fa400 */
            uint32_t reserved_21_31                 : 11; /* [31:21],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } awb2_sta_pixel_num;

    /* 0x50C : awb2_sta_gain0 */
    union {
        struct {
            uint32_t awb2_stat_ggain_pre            : 16; /* [15: 0],        r/w,     0x1000 */
            uint32_t awb2_stat_rgain_pre            : 16; /* [31:16],        r/w,     0x1000 */
        }BF;
        uint32_t WORD;
    } awb2_sta_gain0;

    /* 0x510 : awb2_sta_gain1 */
    union {
        struct {
            uint32_t awb2_rgain_pre                 : 16; /* [15: 0],        r/w,     0x1000 */
            uint32_t awb2_stat_bgain_pre            : 16; /* [31:16],        r/w,     0x1000 */
        }BF;
        uint32_t WORD;
    } awb2_sta_gain1;

    /* 0x514 : awb2_sta_gain2 */
    union {
        struct {
            uint32_t awb2_bgain_pre                 : 16; /* [15: 0],        r/w,     0x1000 */
            uint32_t awb2_ggain_pre                 : 16; /* [31:16],        r/w,     0x1000 */
        }BF;
        uint32_t WORD;
    } awb2_sta_gain2;

    /* 0x518 : awb2_sta_gain3 */
    union {
        struct {
            uint32_t awb2_vgain_pre                 : 10; /* [ 9: 0],        r/w,      0x100 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t awb2_ugain_pre                 : 10; /* [25:16],        r/w,      0x100 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } awb2_sta_gain3;

    /* 0x51C : awb2_sta_l0 */
    union {
        struct {
            uint32_t awb2_yth1_pre                  :  8; /* [ 7: 0],        r/w,       0x10 */
            uint32_t awb2_yth2_pre                  :  8; /* [15: 8],        r/w,       0x30 */
            uint32_t awb2_yth3_pre                  :  8; /* [23:16],        r/w,       0xd0 */
            uint32_t awb2_yth4_pre                  :  8; /* [31:24],        r/w,       0xf0 */
        }BF;
        uint32_t WORD;
    } awb2_sta_l0;

    /* 0x520 : awb2_sta_l1 */
    union {
        struct {
            uint32_t awb2_yweight2_pre              :  8; /* [ 7: 0],        r/w,       0xff */
            uint32_t awb2_yweight3_pre              :  8; /* [15: 8],        r/w,       0xff */
            uint32_t awb2_yweight4_pre              :  8; /* [23:16],        r/w,        0x0 */
            uint32_t awb2_yth0_pre                  :  8; /* [31:24],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } awb2_sta_l1;

    /* 0x524 : awb2_sta_l2 */
    union {
        struct {
            uint32_t awb2_yslope4_pre               :  9; /* [ 8: 0],        r/w,        0x0 */
            uint32_t reserved_9_15                  :  7; /* [15: 9],       rsvd,        0x0 */
            uint32_t awb2_yweight0_pre              :  8; /* [23:16],        r/w,        0x0 */
            uint32_t awb2_yweight1_pre              :  8; /* [31:24],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } awb2_sta_l2;

    /* 0x528 : awb2_sta_l3 */
    union {
        struct {
            uint32_t awb2_yslope2_pre               :  9; /* [ 8: 0],        r/w,        0x0 */
            uint32_t reserved_9_15                  :  7; /* [15: 9],       rsvd,        0x0 */
            uint32_t awb2_yslope3_pre               :  9; /* [24:16],        r/w,      0x1e0 */
            uint32_t reserved_25_31                 :  7; /* [31:25],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } awb2_sta_l3;

    /* 0x52C : awb2_sta_l4 */
    union {
        struct {
            uint32_t awb2_yslope0_pre               :  9; /* [ 8: 0],        r/w,        0x0 */
            uint32_t reserved_9_15                  :  7; /* [15: 9],       rsvd,        0x0 */
            uint32_t awb2_yslope1_pre               :  9; /* [24:16],        r/w,       0x20 */
            uint32_t reserved_25_31                 :  7; /* [31:25],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } awb2_sta_l4;

    /* 0x530 : awb2_sta_c0 */
    union {
        struct {
            uint32_t awb2_ureg4_pre                 :  8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t awb2_ureg5_pre                 :  8; /* [15: 8],        r/w,        0x0 */
            uint32_t awb2_ureg6_pre                 :  8; /* [23:16],        r/w,        0x0 */
            uint32_t awb2_ureg7_pre                 :  8; /* [31:24],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } awb2_sta_c0;

    /* 0x534 : awb2_sta_c1 */
    union {
        struct {
            uint32_t awb2_ureg0_pre                 :  8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t awb2_ureg1_pre                 :  8; /* [15: 8],        r/w,        0x0 */
            uint32_t awb2_ureg2_pre                 :  8; /* [23:16],        r/w,        0x0 */
            uint32_t awb2_ureg3_pre                 :  8; /* [31:24],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } awb2_sta_c1;

    /* 0x538 : awb2_sta_c2 */
    union {
        struct {
            uint32_t awb2_vreg4_pre                 :  8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t awb2_vreg5_pre                 :  8; /* [15: 8],        r/w,        0x0 */
            uint32_t awb2_vreg6_pre                 :  8; /* [23:16],        r/w,        0x0 */
            uint32_t awb2_vreg7_pre                 :  8; /* [31:24],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } awb2_sta_c2;

    /* 0x53C : awb2_sta_c3 */
    union {
        struct {
            uint32_t awb2_vreg0_pre                 :  8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t awb2_vreg1_pre                 :  8; /* [15: 8],        r/w,        0x0 */
            uint32_t awb2_vreg2_pre                 :  8; /* [23:16],        r/w,        0x0 */
            uint32_t awb2_vreg3_pre                 :  8; /* [31:24],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } awb2_sta_c3;

    /* 0x540 : awb2_sta_c4 */
    union {
        struct {
            uint32_t awb2_cth4_pre                  :  6; /* [ 5: 0],        r/w,       0x10 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t awb2_cth5_pre                  :  6; /* [13: 8],        r/w,       0x10 */
            uint32_t reserved_14_15                 :  2; /* [15:14],       rsvd,        0x0 */
            uint32_t awb2_cth6_pre                  :  6; /* [21:16],        r/w,       0x10 */
            uint32_t reserved_22_23                 :  2; /* [23:22],       rsvd,        0x0 */
            uint32_t awb2_cth7_pre                  :  6; /* [29:24],        r/w,       0x10 */
            uint32_t reserved_30_31                 :  2; /* [31:30],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } awb2_sta_c4;

    /* 0x544 : awb2_sta_c5 */
    union {
        struct {
            uint32_t awb2_cth0_pre                  :  6; /* [ 5: 0],        r/w,       0x10 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t awb2_cth1_pre                  :  6; /* [13: 8],        r/w,       0x10 */
            uint32_t reserved_14_15                 :  2; /* [15:14],       rsvd,        0x0 */
            uint32_t awb2_cth2_pre                  :  6; /* [21:16],        r/w,       0x10 */
            uint32_t reserved_22_23                 :  2; /* [23:22],       rsvd,        0x0 */
            uint32_t awb2_cth3_pre                  :  6; /* [29:24],        r/w,       0x10 */
            uint32_t reserved_30_31                 :  2; /* [31:30],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } awb2_sta_c5;

    /* 0x548 : awb2_sta_c6 */
    union {
        struct {
            uint32_t awb2_cslope4_pre               :  8; /* [ 7: 0],        r/w,       0x40 */
            uint32_t awb2_cslope5_pre               :  8; /* [15: 8],        r/w,       0x40 */
            uint32_t awb2_cslope6_pre               :  8; /* [23:16],        r/w,       0x40 */
            uint32_t awb2_cslope7_pre               :  8; /* [31:24],        r/w,       0x40 */
        }BF;
        uint32_t WORD;
    } awb2_sta_c6;

    /* 0x54C : awb2_sta_c7 */
    union {
        struct {
            uint32_t awb2_cslope0_pre               :  8; /* [ 7: 0],        r/w,       0x40 */
            uint32_t awb2_cslope1_pre               :  8; /* [15: 8],        r/w,       0x40 */
            uint32_t awb2_cslope2_pre               :  8; /* [23:16],        r/w,       0x40 */
            uint32_t awb2_cslope3_pre               :  8; /* [31:24],        r/w,       0x40 */
        }BF;
        uint32_t WORD;
    } awb2_sta_c7;

    /* 0x550 : awb2_sta_r0 */
    union {
        struct {
            uint32_t awb2_g_avg0_r                  : 12; /* [11: 0],          r,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t awb2_r_avg0_r                  : 12; /* [27:16],          r,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } awb2_sta_r0;

    /* 0x554 : awb2_sta_r1 */
    union {
        struct {
            uint32_t awb2_white_ratio0_r            : 15; /* [14: 0],          r,        0x0 */
            uint32_t reserved_15                    :  1; /* [   15],       rsvd,        0x0 */
            uint32_t awb2_b_avg0_r                  : 12; /* [27:16],          r,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } awb2_sta_r1;

    /* 0x558 : awb2_sta_r2 */
    union {
        struct {
            uint32_t awb2_g_avg1_r                  : 12; /* [11: 0],          r,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t awb2_r_avg1_r                  : 12; /* [27:16],          r,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } awb2_sta_r2;

    /* 0x55C : awb2_sta_r3 */
    union {
        struct {
            uint32_t awb2_white_ratio1_r            : 15; /* [14: 0],          r,        0x0 */
            uint32_t reserved_15                    :  1; /* [   15],       rsvd,        0x0 */
            uint32_t awb2_b_avg1_r                  : 12; /* [27:16],          r,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } awb2_sta_r3;

    /* 0x560 : awb2_sta_r4 */
    union {
        struct {
            uint32_t awb2_whiter_sumh0_r            : 32; /* [31: 0],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } awb2_sta_r4;

    /* 0x564 : awb2_sta_r5 */
    union {
        struct {
            uint32_t awb2_whiter_suml1_r            :  9; /* [ 8: 0],          r,        0x0 */
            uint32_t reserved_9_15                  :  7; /* [15: 9],       rsvd,        0x0 */
            uint32_t awb2_whiter_suml0_r            :  9; /* [24:16],          r,        0x0 */
            uint32_t reserved_25_31                 :  7; /* [31:25],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } awb2_sta_r5;

    /* 0x568 : awb2_sta_r6 */
    union {
        struct {
            uint32_t awb2_whiter_sumh1_r            : 32; /* [31: 0],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } awb2_sta_r6;

    /* 0x56C : awb2_sta_r7 */
    union {
        struct {
            uint32_t awb2_whiteg_sumh0_r            : 32; /* [31: 0],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } awb2_sta_r7;

    /* 0x570 : awb2_sta_r8 */
    union {
        struct {
            uint32_t awb2_whiteg_suml1_r            :  9; /* [ 8: 0],          r,        0x0 */
            uint32_t reserved_9_15                  :  7; /* [15: 9],       rsvd,        0x0 */
            uint32_t awb2_whiteg_suml0_r            :  9; /* [24:16],          r,        0x0 */
            uint32_t reserved_25_31                 :  7; /* [31:25],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } awb2_sta_r8;

    /* 0x574 : awb2_sta_r9 */
    union {
        struct {
            uint32_t awb2_whiteg_sumh1_r            : 32; /* [31: 0],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } awb2_sta_r9;

    /* 0x578 : awb2_sta_ra */
    union {
        struct {
            uint32_t awb2_whiteb_sumh0_r            : 32; /* [31: 0],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } awb2_sta_ra;

    /* 0x57C : awb2_sta_rb */
    union {
        struct {
            uint32_t awb2_whiteb_suml1_r            :  9; /* [ 8: 0],          r,        0x0 */
            uint32_t reserved_9_15                  :  7; /* [15: 9],       rsvd,        0x0 */
            uint32_t awb2_whiteb_suml0_r            :  9; /* [24:16],          r,        0x0 */
            uint32_t reserved_25_31                 :  7; /* [31:25],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } awb2_sta_rb;

    /* 0x580 : awb2_sta_rc */
    union {
        struct {
            uint32_t awb2_whiteb_sumh1_r            : 32; /* [31: 0],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } awb2_sta_rc;

    /* 0x584 : awb2_sta_int */
    union {
        struct {
            uint32_t awb2_gain_en_pre               :  1; /* [    0],        r/w,        0x0 */
            uint32_t awb2_stat_en_pre               :  1; /* [    1],        r/w,        0x0 */
            uint32_t awb2_buf_idx_r                 :  1; /* [    2],          r,        0x0 */
            uint32_t reserved_3_7                   :  5; /* [ 7: 3],       rsvd,        0x0 */
            uint32_t awb2_w_cnt_r                   :  5; /* [12: 8],          r,        0x0 */
            uint32_t reserved_13_31                 : 19; /* [31:13],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } awb2_sta_int;

};

typedef volatile struct dsp2_middle3_reg dsp2_middle3_reg_t;


#endif  /* __DSP2_MIDDLE3_REG_H__ */
