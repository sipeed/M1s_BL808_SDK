/**
  ******************************************************************************
  * @file    dsp2_middle2_reg.h
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
#ifndef  __DSP2_MIDDLE2_REG_H__
#define  __DSP2_MIDDLE2_REG_H__

#include "bl808.h"

/* 0x800 : BDM_1 */
#define DSP2_MIDDLE2_BDM_1_OFFSET                                (0x800)
#define DSP2_MIDDLE2_BDM_EB_PRE                                  DSP2_MIDDLE2_BDM_EB_PRE
#define DSP2_MIDDLE2_BDM_EB_PRE_POS                              (0U)
#define DSP2_MIDDLE2_BDM_EB_PRE_LEN                              (1U)
#define DSP2_MIDDLE2_BDM_EB_PRE_MSK                              (((1U<<DSP2_MIDDLE2_BDM_EB_PRE_LEN)-1)<<DSP2_MIDDLE2_BDM_EB_PRE_POS)
#define DSP2_MIDDLE2_BDM_EB_PRE_UMSK                             (~(((1U<<DSP2_MIDDLE2_BDM_EB_PRE_LEN)-1)<<DSP2_MIDDLE2_BDM_EB_PRE_POS))
#define DSP2_MIDDLE2_GW_THR_PRE                                  DSP2_MIDDLE2_GW_THR_PRE
#define DSP2_MIDDLE2_GW_THR_PRE_POS                              (8U)
#define DSP2_MIDDLE2_GW_THR_PRE_LEN                              (5U)
#define DSP2_MIDDLE2_GW_THR_PRE_MSK                              (((1U<<DSP2_MIDDLE2_GW_THR_PRE_LEN)-1)<<DSP2_MIDDLE2_GW_THR_PRE_POS)
#define DSP2_MIDDLE2_GW_THR_PRE_UMSK                             (~(((1U<<DSP2_MIDDLE2_GW_THR_PRE_LEN)-1)<<DSP2_MIDDLE2_GW_THR_PRE_POS))
#define DSP2_MIDDLE2_G_SCAL_FACTOR_PRE                           DSP2_MIDDLE2_G_SCAL_FACTOR_PRE
#define DSP2_MIDDLE2_G_SCAL_FACTOR_PRE_POS                       (16U)
#define DSP2_MIDDLE2_G_SCAL_FACTOR_PRE_LEN                       (9U)
#define DSP2_MIDDLE2_G_SCAL_FACTOR_PRE_MSK                       (((1U<<DSP2_MIDDLE2_G_SCAL_FACTOR_PRE_LEN)-1)<<DSP2_MIDDLE2_G_SCAL_FACTOR_PRE_POS)
#define DSP2_MIDDLE2_G_SCAL_FACTOR_PRE_UMSK                      (~(((1U<<DSP2_MIDDLE2_G_SCAL_FACTOR_PRE_LEN)-1)<<DSP2_MIDDLE2_G_SCAL_FACTOR_PRE_POS))

/* 0x804 : BDM_2 */
#define DSP2_MIDDLE2_BDM_2_OFFSET                                (0x804)
#define DSP2_MIDDLE2_R_SCAL_FACTOR_PRE                           DSP2_MIDDLE2_R_SCAL_FACTOR_PRE
#define DSP2_MIDDLE2_R_SCAL_FACTOR_PRE_POS                       (0U)
#define DSP2_MIDDLE2_R_SCAL_FACTOR_PRE_LEN                       (9U)
#define DSP2_MIDDLE2_R_SCAL_FACTOR_PRE_MSK                       (((1U<<DSP2_MIDDLE2_R_SCAL_FACTOR_PRE_LEN)-1)<<DSP2_MIDDLE2_R_SCAL_FACTOR_PRE_POS)
#define DSP2_MIDDLE2_R_SCAL_FACTOR_PRE_UMSK                      (~(((1U<<DSP2_MIDDLE2_R_SCAL_FACTOR_PRE_LEN)-1)<<DSP2_MIDDLE2_R_SCAL_FACTOR_PRE_POS))
#define DSP2_MIDDLE2_B_SCAL_FACTOR_PRE                           DSP2_MIDDLE2_B_SCAL_FACTOR_PRE
#define DSP2_MIDDLE2_B_SCAL_FACTOR_PRE_POS                       (16U)
#define DSP2_MIDDLE2_B_SCAL_FACTOR_PRE_LEN                       (9U)
#define DSP2_MIDDLE2_B_SCAL_FACTOR_PRE_MSK                       (((1U<<DSP2_MIDDLE2_B_SCAL_FACTOR_PRE_LEN)-1)<<DSP2_MIDDLE2_B_SCAL_FACTOR_PRE_POS)
#define DSP2_MIDDLE2_B_SCAL_FACTOR_PRE_UMSK                      (~(((1U<<DSP2_MIDDLE2_B_SCAL_FACTOR_PRE_LEN)-1)<<DSP2_MIDDLE2_B_SCAL_FACTOR_PRE_POS))

/* 0x808 : BDM_3 */
#define DSP2_MIDDLE2_BDM_3_OFFSET                                (0x808)
#define DSP2_MIDDLE2_NR_PROFILE10_PRE                            DSP2_MIDDLE2_NR_PROFILE10_PRE
#define DSP2_MIDDLE2_NR_PROFILE10_PRE_POS                        (0U)
#define DSP2_MIDDLE2_NR_PROFILE10_PRE_LEN                        (12U)
#define DSP2_MIDDLE2_NR_PROFILE10_PRE_MSK                        (((1U<<DSP2_MIDDLE2_NR_PROFILE10_PRE_LEN)-1)<<DSP2_MIDDLE2_NR_PROFILE10_PRE_POS)
#define DSP2_MIDDLE2_NR_PROFILE10_PRE_UMSK                       (~(((1U<<DSP2_MIDDLE2_NR_PROFILE10_PRE_LEN)-1)<<DSP2_MIDDLE2_NR_PROFILE10_PRE_POS))
#define DSP2_MIDDLE2_NR_PROFILE00_PRE                            DSP2_MIDDLE2_NR_PROFILE00_PRE
#define DSP2_MIDDLE2_NR_PROFILE00_PRE_POS                        (16U)
#define DSP2_MIDDLE2_NR_PROFILE00_PRE_LEN                        (12U)
#define DSP2_MIDDLE2_NR_PROFILE00_PRE_MSK                        (((1U<<DSP2_MIDDLE2_NR_PROFILE00_PRE_LEN)-1)<<DSP2_MIDDLE2_NR_PROFILE00_PRE_POS)
#define DSP2_MIDDLE2_NR_PROFILE00_PRE_UMSK                       (~(((1U<<DSP2_MIDDLE2_NR_PROFILE00_PRE_LEN)-1)<<DSP2_MIDDLE2_NR_PROFILE00_PRE_POS))

/* 0x80C : BDM_4 */
#define DSP2_MIDDLE2_BDM_4_OFFSET                                (0x80C)
#define DSP2_MIDDLE2_NR_PROFILE30_PRE                            DSP2_MIDDLE2_NR_PROFILE30_PRE
#define DSP2_MIDDLE2_NR_PROFILE30_PRE_POS                        (0U)
#define DSP2_MIDDLE2_NR_PROFILE30_PRE_LEN                        (12U)
#define DSP2_MIDDLE2_NR_PROFILE30_PRE_MSK                        (((1U<<DSP2_MIDDLE2_NR_PROFILE30_PRE_LEN)-1)<<DSP2_MIDDLE2_NR_PROFILE30_PRE_POS)
#define DSP2_MIDDLE2_NR_PROFILE30_PRE_UMSK                       (~(((1U<<DSP2_MIDDLE2_NR_PROFILE30_PRE_LEN)-1)<<DSP2_MIDDLE2_NR_PROFILE30_PRE_POS))
#define DSP2_MIDDLE2_NR_PROFILE20_PRE                            DSP2_MIDDLE2_NR_PROFILE20_PRE
#define DSP2_MIDDLE2_NR_PROFILE20_PRE_POS                        (16U)
#define DSP2_MIDDLE2_NR_PROFILE20_PRE_LEN                        (12U)
#define DSP2_MIDDLE2_NR_PROFILE20_PRE_MSK                        (((1U<<DSP2_MIDDLE2_NR_PROFILE20_PRE_LEN)-1)<<DSP2_MIDDLE2_NR_PROFILE20_PRE_POS)
#define DSP2_MIDDLE2_NR_PROFILE20_PRE_UMSK                       (~(((1U<<DSP2_MIDDLE2_NR_PROFILE20_PRE_LEN)-1)<<DSP2_MIDDLE2_NR_PROFILE20_PRE_POS))

/* 0x810 : BDM_5 */
#define DSP2_MIDDLE2_BDM_5_OFFSET                                (0x810)
#define DSP2_MIDDLE2_NR_PROFILE50_PRE                            DSP2_MIDDLE2_NR_PROFILE50_PRE
#define DSP2_MIDDLE2_NR_PROFILE50_PRE_POS                        (0U)
#define DSP2_MIDDLE2_NR_PROFILE50_PRE_LEN                        (12U)
#define DSP2_MIDDLE2_NR_PROFILE50_PRE_MSK                        (((1U<<DSP2_MIDDLE2_NR_PROFILE50_PRE_LEN)-1)<<DSP2_MIDDLE2_NR_PROFILE50_PRE_POS)
#define DSP2_MIDDLE2_NR_PROFILE50_PRE_UMSK                       (~(((1U<<DSP2_MIDDLE2_NR_PROFILE50_PRE_LEN)-1)<<DSP2_MIDDLE2_NR_PROFILE50_PRE_POS))
#define DSP2_MIDDLE2_NR_PROFILE40_PRE                            DSP2_MIDDLE2_NR_PROFILE40_PRE
#define DSP2_MIDDLE2_NR_PROFILE40_PRE_POS                        (16U)
#define DSP2_MIDDLE2_NR_PROFILE40_PRE_LEN                        (12U)
#define DSP2_MIDDLE2_NR_PROFILE40_PRE_MSK                        (((1U<<DSP2_MIDDLE2_NR_PROFILE40_PRE_LEN)-1)<<DSP2_MIDDLE2_NR_PROFILE40_PRE_POS)
#define DSP2_MIDDLE2_NR_PROFILE40_PRE_UMSK                       (~(((1U<<DSP2_MIDDLE2_NR_PROFILE40_PRE_LEN)-1)<<DSP2_MIDDLE2_NR_PROFILE40_PRE_POS))

/* 0x814 : BDM_6 */
#define DSP2_MIDDLE2_BDM_6_OFFSET                                (0x814)
#define DSP2_MIDDLE2_NR_PROFILE01_PRE                            DSP2_MIDDLE2_NR_PROFILE01_PRE
#define DSP2_MIDDLE2_NR_PROFILE01_PRE_POS                        (0U)
#define DSP2_MIDDLE2_NR_PROFILE01_PRE_LEN                        (17U)
#define DSP2_MIDDLE2_NR_PROFILE01_PRE_MSK                        (((1U<<DSP2_MIDDLE2_NR_PROFILE01_PRE_LEN)-1)<<DSP2_MIDDLE2_NR_PROFILE01_PRE_POS)
#define DSP2_MIDDLE2_NR_PROFILE01_PRE_UMSK                       (~(((1U<<DSP2_MIDDLE2_NR_PROFILE01_PRE_LEN)-1)<<DSP2_MIDDLE2_NR_PROFILE01_PRE_POS))

/* 0x818 : BDM_7 */
#define DSP2_MIDDLE2_BDM_7_OFFSET                                (0x818)
#define DSP2_MIDDLE2_NR_PROFILE11_PRE                            DSP2_MIDDLE2_NR_PROFILE11_PRE
#define DSP2_MIDDLE2_NR_PROFILE11_PRE_POS                        (0U)
#define DSP2_MIDDLE2_NR_PROFILE11_PRE_LEN                        (17U)
#define DSP2_MIDDLE2_NR_PROFILE11_PRE_MSK                        (((1U<<DSP2_MIDDLE2_NR_PROFILE11_PRE_LEN)-1)<<DSP2_MIDDLE2_NR_PROFILE11_PRE_POS)
#define DSP2_MIDDLE2_NR_PROFILE11_PRE_UMSK                       (~(((1U<<DSP2_MIDDLE2_NR_PROFILE11_PRE_LEN)-1)<<DSP2_MIDDLE2_NR_PROFILE11_PRE_POS))

/* 0x81C : BDM_8 */
#define DSP2_MIDDLE2_BDM_8_OFFSET                                (0x81C)
#define DSP2_MIDDLE2_NR_PROFILE21_PRE                            DSP2_MIDDLE2_NR_PROFILE21_PRE
#define DSP2_MIDDLE2_NR_PROFILE21_PRE_POS                        (0U)
#define DSP2_MIDDLE2_NR_PROFILE21_PRE_LEN                        (17U)
#define DSP2_MIDDLE2_NR_PROFILE21_PRE_MSK                        (((1U<<DSP2_MIDDLE2_NR_PROFILE21_PRE_LEN)-1)<<DSP2_MIDDLE2_NR_PROFILE21_PRE_POS)
#define DSP2_MIDDLE2_NR_PROFILE21_PRE_UMSK                       (~(((1U<<DSP2_MIDDLE2_NR_PROFILE21_PRE_LEN)-1)<<DSP2_MIDDLE2_NR_PROFILE21_PRE_POS))

/* 0x820 : BDM_9 */
#define DSP2_MIDDLE2_BDM_9_OFFSET                                (0x820)
#define DSP2_MIDDLE2_NR_PROFILE31_PRE                            DSP2_MIDDLE2_NR_PROFILE31_PRE
#define DSP2_MIDDLE2_NR_PROFILE31_PRE_POS                        (0U)
#define DSP2_MIDDLE2_NR_PROFILE31_PRE_LEN                        (17U)
#define DSP2_MIDDLE2_NR_PROFILE31_PRE_MSK                        (((1U<<DSP2_MIDDLE2_NR_PROFILE31_PRE_LEN)-1)<<DSP2_MIDDLE2_NR_PROFILE31_PRE_POS)
#define DSP2_MIDDLE2_NR_PROFILE31_PRE_UMSK                       (~(((1U<<DSP2_MIDDLE2_NR_PROFILE31_PRE_LEN)-1)<<DSP2_MIDDLE2_NR_PROFILE31_PRE_POS))

/* 0x824 : BDM_10 */
#define DSP2_MIDDLE2_BDM_10_OFFSET                               (0x824)
#define DSP2_MIDDLE2_NR_PROFILE41_PRE                            DSP2_MIDDLE2_NR_PROFILE41_PRE
#define DSP2_MIDDLE2_NR_PROFILE41_PRE_POS                        (0U)
#define DSP2_MIDDLE2_NR_PROFILE41_PRE_LEN                        (17U)
#define DSP2_MIDDLE2_NR_PROFILE41_PRE_MSK                        (((1U<<DSP2_MIDDLE2_NR_PROFILE41_PRE_LEN)-1)<<DSP2_MIDDLE2_NR_PROFILE41_PRE_POS)
#define DSP2_MIDDLE2_NR_PROFILE41_PRE_UMSK                       (~(((1U<<DSP2_MIDDLE2_NR_PROFILE41_PRE_LEN)-1)<<DSP2_MIDDLE2_NR_PROFILE41_PRE_POS))

/* 0x828 : BDM_11 */
#define DSP2_MIDDLE2_BDM_11_OFFSET                               (0x828)
#define DSP2_MIDDLE2_NR_PROFILE51_PRE                            DSP2_MIDDLE2_NR_PROFILE51_PRE
#define DSP2_MIDDLE2_NR_PROFILE51_PRE_POS                        (0U)
#define DSP2_MIDDLE2_NR_PROFILE51_PRE_LEN                        (17U)
#define DSP2_MIDDLE2_NR_PROFILE51_PRE_MSK                        (((1U<<DSP2_MIDDLE2_NR_PROFILE51_PRE_LEN)-1)<<DSP2_MIDDLE2_NR_PROFILE51_PRE_POS)
#define DSP2_MIDDLE2_NR_PROFILE51_PRE_UMSK                       (~(((1U<<DSP2_MIDDLE2_NR_PROFILE51_PRE_LEN)-1)<<DSP2_MIDDLE2_NR_PROFILE51_PRE_POS))

/* 0x82C : BDM_12 */
#define DSP2_MIDDLE2_BDM_12_OFFSET                               (0x82C)
#define DSP2_MIDDLE2_LUMA_G_W1_PRE                               DSP2_MIDDLE2_LUMA_G_W1_PRE
#define DSP2_MIDDLE2_LUMA_G_W1_PRE_POS                           (0U)
#define DSP2_MIDDLE2_LUMA_G_W1_PRE_LEN                           (9U)
#define DSP2_MIDDLE2_LUMA_G_W1_PRE_MSK                           (((1U<<DSP2_MIDDLE2_LUMA_G_W1_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W1_PRE_POS)
#define DSP2_MIDDLE2_LUMA_G_W1_PRE_UMSK                          (~(((1U<<DSP2_MIDDLE2_LUMA_G_W1_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W1_PRE_POS))
#define DSP2_MIDDLE2_LUMA_G_W0_PRE                               DSP2_MIDDLE2_LUMA_G_W0_PRE
#define DSP2_MIDDLE2_LUMA_G_W0_PRE_POS                           (16U)
#define DSP2_MIDDLE2_LUMA_G_W0_PRE_LEN                           (9U)
#define DSP2_MIDDLE2_LUMA_G_W0_PRE_MSK                           (((1U<<DSP2_MIDDLE2_LUMA_G_W0_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W0_PRE_POS)
#define DSP2_MIDDLE2_LUMA_G_W0_PRE_UMSK                          (~(((1U<<DSP2_MIDDLE2_LUMA_G_W0_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W0_PRE_POS))

/* 0x830 : BDM_13 */
#define DSP2_MIDDLE2_BDM_13_OFFSET                               (0x830)
#define DSP2_MIDDLE2_LUMA_G_W3_PRE                               DSP2_MIDDLE2_LUMA_G_W3_PRE
#define DSP2_MIDDLE2_LUMA_G_W3_PRE_POS                           (0U)
#define DSP2_MIDDLE2_LUMA_G_W3_PRE_LEN                           (9U)
#define DSP2_MIDDLE2_LUMA_G_W3_PRE_MSK                           (((1U<<DSP2_MIDDLE2_LUMA_G_W3_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W3_PRE_POS)
#define DSP2_MIDDLE2_LUMA_G_W3_PRE_UMSK                          (~(((1U<<DSP2_MIDDLE2_LUMA_G_W3_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W3_PRE_POS))
#define DSP2_MIDDLE2_LUMA_G_W2_PRE                               DSP2_MIDDLE2_LUMA_G_W2_PRE
#define DSP2_MIDDLE2_LUMA_G_W2_PRE_POS                           (16U)
#define DSP2_MIDDLE2_LUMA_G_W2_PRE_LEN                           (9U)
#define DSP2_MIDDLE2_LUMA_G_W2_PRE_MSK                           (((1U<<DSP2_MIDDLE2_LUMA_G_W2_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W2_PRE_POS)
#define DSP2_MIDDLE2_LUMA_G_W2_PRE_UMSK                          (~(((1U<<DSP2_MIDDLE2_LUMA_G_W2_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W2_PRE_POS))

/* 0x834 : BDM_14 */
#define DSP2_MIDDLE2_BDM_14_OFFSET                               (0x834)
#define DSP2_MIDDLE2_LUMA_G_W5_PRE                               DSP2_MIDDLE2_LUMA_G_W5_PRE
#define DSP2_MIDDLE2_LUMA_G_W5_PRE_POS                           (0U)
#define DSP2_MIDDLE2_LUMA_G_W5_PRE_LEN                           (9U)
#define DSP2_MIDDLE2_LUMA_G_W5_PRE_MSK                           (((1U<<DSP2_MIDDLE2_LUMA_G_W5_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W5_PRE_POS)
#define DSP2_MIDDLE2_LUMA_G_W5_PRE_UMSK                          (~(((1U<<DSP2_MIDDLE2_LUMA_G_W5_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W5_PRE_POS))
#define DSP2_MIDDLE2_LUMA_G_W4_PRE                               DSP2_MIDDLE2_LUMA_G_W4_PRE
#define DSP2_MIDDLE2_LUMA_G_W4_PRE_POS                           (16U)
#define DSP2_MIDDLE2_LUMA_G_W4_PRE_LEN                           (9U)
#define DSP2_MIDDLE2_LUMA_G_W4_PRE_MSK                           (((1U<<DSP2_MIDDLE2_LUMA_G_W4_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W4_PRE_POS)
#define DSP2_MIDDLE2_LUMA_G_W4_PRE_UMSK                          (~(((1U<<DSP2_MIDDLE2_LUMA_G_W4_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W4_PRE_POS))

/* 0x838 : BDM_15 */
#define DSP2_MIDDLE2_BDM_15_OFFSET                               (0x838)
#define DSP2_MIDDLE2_LUMA_G_W7_PRE                               DSP2_MIDDLE2_LUMA_G_W7_PRE
#define DSP2_MIDDLE2_LUMA_G_W7_PRE_POS                           (0U)
#define DSP2_MIDDLE2_LUMA_G_W7_PRE_LEN                           (9U)
#define DSP2_MIDDLE2_LUMA_G_W7_PRE_MSK                           (((1U<<DSP2_MIDDLE2_LUMA_G_W7_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W7_PRE_POS)
#define DSP2_MIDDLE2_LUMA_G_W7_PRE_UMSK                          (~(((1U<<DSP2_MIDDLE2_LUMA_G_W7_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W7_PRE_POS))
#define DSP2_MIDDLE2_LUMA_G_W6_PRE                               DSP2_MIDDLE2_LUMA_G_W6_PRE
#define DSP2_MIDDLE2_LUMA_G_W6_PRE_POS                           (16U)
#define DSP2_MIDDLE2_LUMA_G_W6_PRE_LEN                           (9U)
#define DSP2_MIDDLE2_LUMA_G_W6_PRE_MSK                           (((1U<<DSP2_MIDDLE2_LUMA_G_W6_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W6_PRE_POS)
#define DSP2_MIDDLE2_LUMA_G_W6_PRE_UMSK                          (~(((1U<<DSP2_MIDDLE2_LUMA_G_W6_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W6_PRE_POS))

/* 0x83C : BDM_16 */
#define DSP2_MIDDLE2_BDM_16_OFFSET                               (0x83C)
#define DSP2_MIDDLE2_LUMA_G_W9_PRE                               DSP2_MIDDLE2_LUMA_G_W9_PRE
#define DSP2_MIDDLE2_LUMA_G_W9_PRE_POS                           (0U)
#define DSP2_MIDDLE2_LUMA_G_W9_PRE_LEN                           (9U)
#define DSP2_MIDDLE2_LUMA_G_W9_PRE_MSK                           (((1U<<DSP2_MIDDLE2_LUMA_G_W9_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W9_PRE_POS)
#define DSP2_MIDDLE2_LUMA_G_W9_PRE_UMSK                          (~(((1U<<DSP2_MIDDLE2_LUMA_G_W9_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W9_PRE_POS))
#define DSP2_MIDDLE2_LUMA_G_W8_PRE                               DSP2_MIDDLE2_LUMA_G_W8_PRE
#define DSP2_MIDDLE2_LUMA_G_W8_PRE_POS                           (16U)
#define DSP2_MIDDLE2_LUMA_G_W8_PRE_LEN                           (9U)
#define DSP2_MIDDLE2_LUMA_G_W8_PRE_MSK                           (((1U<<DSP2_MIDDLE2_LUMA_G_W8_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W8_PRE_POS)
#define DSP2_MIDDLE2_LUMA_G_W8_PRE_UMSK                          (~(((1U<<DSP2_MIDDLE2_LUMA_G_W8_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W8_PRE_POS))

/* 0x840 : BDM_17 */
#define DSP2_MIDDLE2_BDM_17_OFFSET                               (0x840)
#define DSP2_MIDDLE2_LUMA_G_W11_PRE                              DSP2_MIDDLE2_LUMA_G_W11_PRE
#define DSP2_MIDDLE2_LUMA_G_W11_PRE_POS                          (0U)
#define DSP2_MIDDLE2_LUMA_G_W11_PRE_LEN                          (9U)
#define DSP2_MIDDLE2_LUMA_G_W11_PRE_MSK                          (((1U<<DSP2_MIDDLE2_LUMA_G_W11_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W11_PRE_POS)
#define DSP2_MIDDLE2_LUMA_G_W11_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE2_LUMA_G_W11_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W11_PRE_POS))
#define DSP2_MIDDLE2_LUMA_G_W10_PRE                              DSP2_MIDDLE2_LUMA_G_W10_PRE
#define DSP2_MIDDLE2_LUMA_G_W10_PRE_POS                          (16U)
#define DSP2_MIDDLE2_LUMA_G_W10_PRE_LEN                          (9U)
#define DSP2_MIDDLE2_LUMA_G_W10_PRE_MSK                          (((1U<<DSP2_MIDDLE2_LUMA_G_W10_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W10_PRE_POS)
#define DSP2_MIDDLE2_LUMA_G_W10_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE2_LUMA_G_W10_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W10_PRE_POS))

/* 0x844 : BDM_18 */
#define DSP2_MIDDLE2_BDM_18_OFFSET                               (0x844)
#define DSP2_MIDDLE2_LUMA_G_W13_PRE                              DSP2_MIDDLE2_LUMA_G_W13_PRE
#define DSP2_MIDDLE2_LUMA_G_W13_PRE_POS                          (0U)
#define DSP2_MIDDLE2_LUMA_G_W13_PRE_LEN                          (9U)
#define DSP2_MIDDLE2_LUMA_G_W13_PRE_MSK                          (((1U<<DSP2_MIDDLE2_LUMA_G_W13_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W13_PRE_POS)
#define DSP2_MIDDLE2_LUMA_G_W13_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE2_LUMA_G_W13_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W13_PRE_POS))
#define DSP2_MIDDLE2_LUMA_G_W12_PRE                              DSP2_MIDDLE2_LUMA_G_W12_PRE
#define DSP2_MIDDLE2_LUMA_G_W12_PRE_POS                          (16U)
#define DSP2_MIDDLE2_LUMA_G_W12_PRE_LEN                          (9U)
#define DSP2_MIDDLE2_LUMA_G_W12_PRE_MSK                          (((1U<<DSP2_MIDDLE2_LUMA_G_W12_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W12_PRE_POS)
#define DSP2_MIDDLE2_LUMA_G_W12_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE2_LUMA_G_W12_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W12_PRE_POS))

/* 0x848 : BDM_19 */
#define DSP2_MIDDLE2_BDM_19_OFFSET                               (0x848)
#define DSP2_MIDDLE2_LUMA_G_W15_PRE                              DSP2_MIDDLE2_LUMA_G_W15_PRE
#define DSP2_MIDDLE2_LUMA_G_W15_PRE_POS                          (0U)
#define DSP2_MIDDLE2_LUMA_G_W15_PRE_LEN                          (9U)
#define DSP2_MIDDLE2_LUMA_G_W15_PRE_MSK                          (((1U<<DSP2_MIDDLE2_LUMA_G_W15_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W15_PRE_POS)
#define DSP2_MIDDLE2_LUMA_G_W15_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE2_LUMA_G_W15_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W15_PRE_POS))
#define DSP2_MIDDLE2_LUMA_G_W14_PRE                              DSP2_MIDDLE2_LUMA_G_W14_PRE
#define DSP2_MIDDLE2_LUMA_G_W14_PRE_POS                          (16U)
#define DSP2_MIDDLE2_LUMA_G_W14_PRE_LEN                          (9U)
#define DSP2_MIDDLE2_LUMA_G_W14_PRE_MSK                          (((1U<<DSP2_MIDDLE2_LUMA_G_W14_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W14_PRE_POS)
#define DSP2_MIDDLE2_LUMA_G_W14_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE2_LUMA_G_W14_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W14_PRE_POS))

/* 0x84C : BDM_20 */
#define DSP2_MIDDLE2_BDM_20_OFFSET                               (0x84C)
#define DSP2_MIDDLE2_LUMA_G_W17_PRE                              DSP2_MIDDLE2_LUMA_G_W17_PRE
#define DSP2_MIDDLE2_LUMA_G_W17_PRE_POS                          (0U)
#define DSP2_MIDDLE2_LUMA_G_W17_PRE_LEN                          (9U)
#define DSP2_MIDDLE2_LUMA_G_W17_PRE_MSK                          (((1U<<DSP2_MIDDLE2_LUMA_G_W17_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W17_PRE_POS)
#define DSP2_MIDDLE2_LUMA_G_W17_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE2_LUMA_G_W17_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W17_PRE_POS))
#define DSP2_MIDDLE2_LUMA_G_W16_PRE                              DSP2_MIDDLE2_LUMA_G_W16_PRE
#define DSP2_MIDDLE2_LUMA_G_W16_PRE_POS                          (16U)
#define DSP2_MIDDLE2_LUMA_G_W16_PRE_LEN                          (9U)
#define DSP2_MIDDLE2_LUMA_G_W16_PRE_MSK                          (((1U<<DSP2_MIDDLE2_LUMA_G_W16_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W16_PRE_POS)
#define DSP2_MIDDLE2_LUMA_G_W16_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE2_LUMA_G_W16_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W16_PRE_POS))

/* 0x850 : BDM_21 */
#define DSP2_MIDDLE2_BDM_21_OFFSET                               (0x850)
#define DSP2_MIDDLE2_LUMA_G_W19_PRE                              DSP2_MIDDLE2_LUMA_G_W19_PRE
#define DSP2_MIDDLE2_LUMA_G_W19_PRE_POS                          (0U)
#define DSP2_MIDDLE2_LUMA_G_W19_PRE_LEN                          (9U)
#define DSP2_MIDDLE2_LUMA_G_W19_PRE_MSK                          (((1U<<DSP2_MIDDLE2_LUMA_G_W19_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W19_PRE_POS)
#define DSP2_MIDDLE2_LUMA_G_W19_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE2_LUMA_G_W19_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W19_PRE_POS))
#define DSP2_MIDDLE2_LUMA_G_W18_PRE                              DSP2_MIDDLE2_LUMA_G_W18_PRE
#define DSP2_MIDDLE2_LUMA_G_W18_PRE_POS                          (16U)
#define DSP2_MIDDLE2_LUMA_G_W18_PRE_LEN                          (9U)
#define DSP2_MIDDLE2_LUMA_G_W18_PRE_MSK                          (((1U<<DSP2_MIDDLE2_LUMA_G_W18_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W18_PRE_POS)
#define DSP2_MIDDLE2_LUMA_G_W18_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE2_LUMA_G_W18_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W18_PRE_POS))

/* 0x854 : BDM_22 */
#define DSP2_MIDDLE2_BDM_22_OFFSET                               (0x854)
#define DSP2_MIDDLE2_LUMA_G_W21_PRE                              DSP2_MIDDLE2_LUMA_G_W21_PRE
#define DSP2_MIDDLE2_LUMA_G_W21_PRE_POS                          (0U)
#define DSP2_MIDDLE2_LUMA_G_W21_PRE_LEN                          (9U)
#define DSP2_MIDDLE2_LUMA_G_W21_PRE_MSK                          (((1U<<DSP2_MIDDLE2_LUMA_G_W21_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W21_PRE_POS)
#define DSP2_MIDDLE2_LUMA_G_W21_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE2_LUMA_G_W21_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W21_PRE_POS))
#define DSP2_MIDDLE2_LUMA_G_W20_PRE                              DSP2_MIDDLE2_LUMA_G_W20_PRE
#define DSP2_MIDDLE2_LUMA_G_W20_PRE_POS                          (16U)
#define DSP2_MIDDLE2_LUMA_G_W20_PRE_LEN                          (9U)
#define DSP2_MIDDLE2_LUMA_G_W20_PRE_MSK                          (((1U<<DSP2_MIDDLE2_LUMA_G_W20_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W20_PRE_POS)
#define DSP2_MIDDLE2_LUMA_G_W20_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE2_LUMA_G_W20_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W20_PRE_POS))

/* 0x858 : BDM_23 */
#define DSP2_MIDDLE2_BDM_23_OFFSET                               (0x858)
#define DSP2_MIDDLE2_LUMA_G_W23_PRE                              DSP2_MIDDLE2_LUMA_G_W23_PRE
#define DSP2_MIDDLE2_LUMA_G_W23_PRE_POS                          (0U)
#define DSP2_MIDDLE2_LUMA_G_W23_PRE_LEN                          (9U)
#define DSP2_MIDDLE2_LUMA_G_W23_PRE_MSK                          (((1U<<DSP2_MIDDLE2_LUMA_G_W23_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W23_PRE_POS)
#define DSP2_MIDDLE2_LUMA_G_W23_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE2_LUMA_G_W23_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W23_PRE_POS))
#define DSP2_MIDDLE2_LUMA_G_W22_PRE                              DSP2_MIDDLE2_LUMA_G_W22_PRE
#define DSP2_MIDDLE2_LUMA_G_W22_PRE_POS                          (16U)
#define DSP2_MIDDLE2_LUMA_G_W22_PRE_LEN                          (9U)
#define DSP2_MIDDLE2_LUMA_G_W22_PRE_MSK                          (((1U<<DSP2_MIDDLE2_LUMA_G_W22_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W22_PRE_POS)
#define DSP2_MIDDLE2_LUMA_G_W22_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE2_LUMA_G_W22_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W22_PRE_POS))

/* 0x85C : BDM_24 */
#define DSP2_MIDDLE2_BDM_24_OFFSET                               (0x85C)
#define DSP2_MIDDLE2_LUMA_G_W25_PRE                              DSP2_MIDDLE2_LUMA_G_W25_PRE
#define DSP2_MIDDLE2_LUMA_G_W25_PRE_POS                          (0U)
#define DSP2_MIDDLE2_LUMA_G_W25_PRE_LEN                          (9U)
#define DSP2_MIDDLE2_LUMA_G_W25_PRE_MSK                          (((1U<<DSP2_MIDDLE2_LUMA_G_W25_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W25_PRE_POS)
#define DSP2_MIDDLE2_LUMA_G_W25_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE2_LUMA_G_W25_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W25_PRE_POS))
#define DSP2_MIDDLE2_LUMA_G_W24_PRE                              DSP2_MIDDLE2_LUMA_G_W24_PRE
#define DSP2_MIDDLE2_LUMA_G_W24_PRE_POS                          (16U)
#define DSP2_MIDDLE2_LUMA_G_W24_PRE_LEN                          (9U)
#define DSP2_MIDDLE2_LUMA_G_W24_PRE_MSK                          (((1U<<DSP2_MIDDLE2_LUMA_G_W24_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W24_PRE_POS)
#define DSP2_MIDDLE2_LUMA_G_W24_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE2_LUMA_G_W24_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W24_PRE_POS))

/* 0x860 : BDM_25 */
#define DSP2_MIDDLE2_BDM_25_OFFSET                               (0x860)
#define DSP2_MIDDLE2_LUMA_G_W27_PRE                              DSP2_MIDDLE2_LUMA_G_W27_PRE
#define DSP2_MIDDLE2_LUMA_G_W27_PRE_POS                          (0U)
#define DSP2_MIDDLE2_LUMA_G_W27_PRE_LEN                          (9U)
#define DSP2_MIDDLE2_LUMA_G_W27_PRE_MSK                          (((1U<<DSP2_MIDDLE2_LUMA_G_W27_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W27_PRE_POS)
#define DSP2_MIDDLE2_LUMA_G_W27_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE2_LUMA_G_W27_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W27_PRE_POS))
#define DSP2_MIDDLE2_LUMA_G_W26_PRE                              DSP2_MIDDLE2_LUMA_G_W26_PRE
#define DSP2_MIDDLE2_LUMA_G_W26_PRE_POS                          (16U)
#define DSP2_MIDDLE2_LUMA_G_W26_PRE_LEN                          (9U)
#define DSP2_MIDDLE2_LUMA_G_W26_PRE_MSK                          (((1U<<DSP2_MIDDLE2_LUMA_G_W26_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W26_PRE_POS)
#define DSP2_MIDDLE2_LUMA_G_W26_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE2_LUMA_G_W26_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W26_PRE_POS))

/* 0x864 : BDM_26 */
#define DSP2_MIDDLE2_BDM_26_OFFSET                               (0x864)
#define DSP2_MIDDLE2_LUMA_G_W29_PRE                              DSP2_MIDDLE2_LUMA_G_W29_PRE
#define DSP2_MIDDLE2_LUMA_G_W29_PRE_POS                          (0U)
#define DSP2_MIDDLE2_LUMA_G_W29_PRE_LEN                          (9U)
#define DSP2_MIDDLE2_LUMA_G_W29_PRE_MSK                          (((1U<<DSP2_MIDDLE2_LUMA_G_W29_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W29_PRE_POS)
#define DSP2_MIDDLE2_LUMA_G_W29_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE2_LUMA_G_W29_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W29_PRE_POS))
#define DSP2_MIDDLE2_LUMA_G_W28_PRE                              DSP2_MIDDLE2_LUMA_G_W28_PRE
#define DSP2_MIDDLE2_LUMA_G_W28_PRE_POS                          (16U)
#define DSP2_MIDDLE2_LUMA_G_W28_PRE_LEN                          (9U)
#define DSP2_MIDDLE2_LUMA_G_W28_PRE_MSK                          (((1U<<DSP2_MIDDLE2_LUMA_G_W28_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W28_PRE_POS)
#define DSP2_MIDDLE2_LUMA_G_W28_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE2_LUMA_G_W28_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W28_PRE_POS))

/* 0x868 : BDM_27 */
#define DSP2_MIDDLE2_BDM_27_OFFSET                               (0x868)
#define DSP2_MIDDLE2_LUMA_G_W31_PRE                              DSP2_MIDDLE2_LUMA_G_W31_PRE
#define DSP2_MIDDLE2_LUMA_G_W31_PRE_POS                          (0U)
#define DSP2_MIDDLE2_LUMA_G_W31_PRE_LEN                          (9U)
#define DSP2_MIDDLE2_LUMA_G_W31_PRE_MSK                          (((1U<<DSP2_MIDDLE2_LUMA_G_W31_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W31_PRE_POS)
#define DSP2_MIDDLE2_LUMA_G_W31_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE2_LUMA_G_W31_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W31_PRE_POS))
#define DSP2_MIDDLE2_LUMA_G_W30_PRE                              DSP2_MIDDLE2_LUMA_G_W30_PRE
#define DSP2_MIDDLE2_LUMA_G_W30_PRE_POS                          (16U)
#define DSP2_MIDDLE2_LUMA_G_W30_PRE_LEN                          (9U)
#define DSP2_MIDDLE2_LUMA_G_W30_PRE_MSK                          (((1U<<DSP2_MIDDLE2_LUMA_G_W30_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W30_PRE_POS)
#define DSP2_MIDDLE2_LUMA_G_W30_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE2_LUMA_G_W30_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_G_W30_PRE_POS))

/* 0x870 : BDM_28 */
#define DSP2_MIDDLE2_BDM_28_OFFSET                               (0x870)
#define DSP2_MIDDLE2_LUMA_BR_W1_PRE                              DSP2_MIDDLE2_LUMA_BR_W1_PRE
#define DSP2_MIDDLE2_LUMA_BR_W1_PRE_POS                          (0U)
#define DSP2_MIDDLE2_LUMA_BR_W1_PRE_LEN                          (9U)
#define DSP2_MIDDLE2_LUMA_BR_W1_PRE_MSK                          (((1U<<DSP2_MIDDLE2_LUMA_BR_W1_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W1_PRE_POS)
#define DSP2_MIDDLE2_LUMA_BR_W1_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE2_LUMA_BR_W1_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W1_PRE_POS))
#define DSP2_MIDDLE2_LUMA_BR_W0_PRE                              DSP2_MIDDLE2_LUMA_BR_W0_PRE
#define DSP2_MIDDLE2_LUMA_BR_W0_PRE_POS                          (16U)
#define DSP2_MIDDLE2_LUMA_BR_W0_PRE_LEN                          (9U)
#define DSP2_MIDDLE2_LUMA_BR_W0_PRE_MSK                          (((1U<<DSP2_MIDDLE2_LUMA_BR_W0_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W0_PRE_POS)
#define DSP2_MIDDLE2_LUMA_BR_W0_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE2_LUMA_BR_W0_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W0_PRE_POS))

/* 0x874 : BDM_29 */
#define DSP2_MIDDLE2_BDM_29_OFFSET                               (0x874)
#define DSP2_MIDDLE2_LUMA_BR_W3_PRE                              DSP2_MIDDLE2_LUMA_BR_W3_PRE
#define DSP2_MIDDLE2_LUMA_BR_W3_PRE_POS                          (0U)
#define DSP2_MIDDLE2_LUMA_BR_W3_PRE_LEN                          (9U)
#define DSP2_MIDDLE2_LUMA_BR_W3_PRE_MSK                          (((1U<<DSP2_MIDDLE2_LUMA_BR_W3_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W3_PRE_POS)
#define DSP2_MIDDLE2_LUMA_BR_W3_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE2_LUMA_BR_W3_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W3_PRE_POS))
#define DSP2_MIDDLE2_LUMA_BR_W2_PRE                              DSP2_MIDDLE2_LUMA_BR_W2_PRE
#define DSP2_MIDDLE2_LUMA_BR_W2_PRE_POS                          (16U)
#define DSP2_MIDDLE2_LUMA_BR_W2_PRE_LEN                          (9U)
#define DSP2_MIDDLE2_LUMA_BR_W2_PRE_MSK                          (((1U<<DSP2_MIDDLE2_LUMA_BR_W2_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W2_PRE_POS)
#define DSP2_MIDDLE2_LUMA_BR_W2_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE2_LUMA_BR_W2_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W2_PRE_POS))

/* 0x878 : BDM_30 */
#define DSP2_MIDDLE2_BDM_30_OFFSET                               (0x878)
#define DSP2_MIDDLE2_LUMA_BR_W5_PRE                              DSP2_MIDDLE2_LUMA_BR_W5_PRE
#define DSP2_MIDDLE2_LUMA_BR_W5_PRE_POS                          (0U)
#define DSP2_MIDDLE2_LUMA_BR_W5_PRE_LEN                          (9U)
#define DSP2_MIDDLE2_LUMA_BR_W5_PRE_MSK                          (((1U<<DSP2_MIDDLE2_LUMA_BR_W5_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W5_PRE_POS)
#define DSP2_MIDDLE2_LUMA_BR_W5_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE2_LUMA_BR_W5_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W5_PRE_POS))
#define DSP2_MIDDLE2_LUMA_BR_W4_PRE                              DSP2_MIDDLE2_LUMA_BR_W4_PRE
#define DSP2_MIDDLE2_LUMA_BR_W4_PRE_POS                          (16U)
#define DSP2_MIDDLE2_LUMA_BR_W4_PRE_LEN                          (9U)
#define DSP2_MIDDLE2_LUMA_BR_W4_PRE_MSK                          (((1U<<DSP2_MIDDLE2_LUMA_BR_W4_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W4_PRE_POS)
#define DSP2_MIDDLE2_LUMA_BR_W4_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE2_LUMA_BR_W4_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W4_PRE_POS))

/* 0x87C : BDM_31 */
#define DSP2_MIDDLE2_BDM_31_OFFSET                               (0x87C)
#define DSP2_MIDDLE2_LUMA_BR_W7_PRE                              DSP2_MIDDLE2_LUMA_BR_W7_PRE
#define DSP2_MIDDLE2_LUMA_BR_W7_PRE_POS                          (0U)
#define DSP2_MIDDLE2_LUMA_BR_W7_PRE_LEN                          (9U)
#define DSP2_MIDDLE2_LUMA_BR_W7_PRE_MSK                          (((1U<<DSP2_MIDDLE2_LUMA_BR_W7_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W7_PRE_POS)
#define DSP2_MIDDLE2_LUMA_BR_W7_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE2_LUMA_BR_W7_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W7_PRE_POS))
#define DSP2_MIDDLE2_LUMA_BR_W6_PRE                              DSP2_MIDDLE2_LUMA_BR_W6_PRE
#define DSP2_MIDDLE2_LUMA_BR_W6_PRE_POS                          (16U)
#define DSP2_MIDDLE2_LUMA_BR_W6_PRE_LEN                          (9U)
#define DSP2_MIDDLE2_LUMA_BR_W6_PRE_MSK                          (((1U<<DSP2_MIDDLE2_LUMA_BR_W6_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W6_PRE_POS)
#define DSP2_MIDDLE2_LUMA_BR_W6_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE2_LUMA_BR_W6_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W6_PRE_POS))

/* 0x880 : BDM_32 */
#define DSP2_MIDDLE2_BDM_32_OFFSET                               (0x880)
#define DSP2_MIDDLE2_LUMA_BR_W9_PRE                              DSP2_MIDDLE2_LUMA_BR_W9_PRE
#define DSP2_MIDDLE2_LUMA_BR_W9_PRE_POS                          (0U)
#define DSP2_MIDDLE2_LUMA_BR_W9_PRE_LEN                          (9U)
#define DSP2_MIDDLE2_LUMA_BR_W9_PRE_MSK                          (((1U<<DSP2_MIDDLE2_LUMA_BR_W9_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W9_PRE_POS)
#define DSP2_MIDDLE2_LUMA_BR_W9_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE2_LUMA_BR_W9_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W9_PRE_POS))
#define DSP2_MIDDLE2_LUMA_BR_W8_PRE                              DSP2_MIDDLE2_LUMA_BR_W8_PRE
#define DSP2_MIDDLE2_LUMA_BR_W8_PRE_POS                          (16U)
#define DSP2_MIDDLE2_LUMA_BR_W8_PRE_LEN                          (9U)
#define DSP2_MIDDLE2_LUMA_BR_W8_PRE_MSK                          (((1U<<DSP2_MIDDLE2_LUMA_BR_W8_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W8_PRE_POS)
#define DSP2_MIDDLE2_LUMA_BR_W8_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE2_LUMA_BR_W8_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W8_PRE_POS))

/* 0x884 : BDM_33 */
#define DSP2_MIDDLE2_BDM_33_OFFSET                               (0x884)
#define DSP2_MIDDLE2_LUMA_BR_W11_PRE                             DSP2_MIDDLE2_LUMA_BR_W11_PRE
#define DSP2_MIDDLE2_LUMA_BR_W11_PRE_POS                         (0U)
#define DSP2_MIDDLE2_LUMA_BR_W11_PRE_LEN                         (9U)
#define DSP2_MIDDLE2_LUMA_BR_W11_PRE_MSK                         (((1U<<DSP2_MIDDLE2_LUMA_BR_W11_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W11_PRE_POS)
#define DSP2_MIDDLE2_LUMA_BR_W11_PRE_UMSK                        (~(((1U<<DSP2_MIDDLE2_LUMA_BR_W11_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W11_PRE_POS))
#define DSP2_MIDDLE2_LUMA_BR_W10_PRE                             DSP2_MIDDLE2_LUMA_BR_W10_PRE
#define DSP2_MIDDLE2_LUMA_BR_W10_PRE_POS                         (16U)
#define DSP2_MIDDLE2_LUMA_BR_W10_PRE_LEN                         (9U)
#define DSP2_MIDDLE2_LUMA_BR_W10_PRE_MSK                         (((1U<<DSP2_MIDDLE2_LUMA_BR_W10_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W10_PRE_POS)
#define DSP2_MIDDLE2_LUMA_BR_W10_PRE_UMSK                        (~(((1U<<DSP2_MIDDLE2_LUMA_BR_W10_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W10_PRE_POS))

/* 0x888 : BDM_34 */
#define DSP2_MIDDLE2_BDM_34_OFFSET                               (0x888)
#define DSP2_MIDDLE2_LUMA_BR_W13_PRE                             DSP2_MIDDLE2_LUMA_BR_W13_PRE
#define DSP2_MIDDLE2_LUMA_BR_W13_PRE_POS                         (0U)
#define DSP2_MIDDLE2_LUMA_BR_W13_PRE_LEN                         (9U)
#define DSP2_MIDDLE2_LUMA_BR_W13_PRE_MSK                         (((1U<<DSP2_MIDDLE2_LUMA_BR_W13_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W13_PRE_POS)
#define DSP2_MIDDLE2_LUMA_BR_W13_PRE_UMSK                        (~(((1U<<DSP2_MIDDLE2_LUMA_BR_W13_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W13_PRE_POS))
#define DSP2_MIDDLE2_LUMA_BR_W12_PRE                             DSP2_MIDDLE2_LUMA_BR_W12_PRE
#define DSP2_MIDDLE2_LUMA_BR_W12_PRE_POS                         (16U)
#define DSP2_MIDDLE2_LUMA_BR_W12_PRE_LEN                         (9U)
#define DSP2_MIDDLE2_LUMA_BR_W12_PRE_MSK                         (((1U<<DSP2_MIDDLE2_LUMA_BR_W12_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W12_PRE_POS)
#define DSP2_MIDDLE2_LUMA_BR_W12_PRE_UMSK                        (~(((1U<<DSP2_MIDDLE2_LUMA_BR_W12_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W12_PRE_POS))

/* 0x88C : BDM_35 */
#define DSP2_MIDDLE2_BDM_35_OFFSET                               (0x88C)
#define DSP2_MIDDLE2_LUMA_BR_W15_PRE                             DSP2_MIDDLE2_LUMA_BR_W15_PRE
#define DSP2_MIDDLE2_LUMA_BR_W15_PRE_POS                         (0U)
#define DSP2_MIDDLE2_LUMA_BR_W15_PRE_LEN                         (9U)
#define DSP2_MIDDLE2_LUMA_BR_W15_PRE_MSK                         (((1U<<DSP2_MIDDLE2_LUMA_BR_W15_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W15_PRE_POS)
#define DSP2_MIDDLE2_LUMA_BR_W15_PRE_UMSK                        (~(((1U<<DSP2_MIDDLE2_LUMA_BR_W15_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W15_PRE_POS))
#define DSP2_MIDDLE2_LUMA_BR_W14_PRE                             DSP2_MIDDLE2_LUMA_BR_W14_PRE
#define DSP2_MIDDLE2_LUMA_BR_W14_PRE_POS                         (16U)
#define DSP2_MIDDLE2_LUMA_BR_W14_PRE_LEN                         (9U)
#define DSP2_MIDDLE2_LUMA_BR_W14_PRE_MSK                         (((1U<<DSP2_MIDDLE2_LUMA_BR_W14_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W14_PRE_POS)
#define DSP2_MIDDLE2_LUMA_BR_W14_PRE_UMSK                        (~(((1U<<DSP2_MIDDLE2_LUMA_BR_W14_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W14_PRE_POS))

/* 0x890 : BDM_36 */
#define DSP2_MIDDLE2_BDM_36_OFFSET                               (0x890)
#define DSP2_MIDDLE2_LUMA_BR_W17_PRE                             DSP2_MIDDLE2_LUMA_BR_W17_PRE
#define DSP2_MIDDLE2_LUMA_BR_W17_PRE_POS                         (0U)
#define DSP2_MIDDLE2_LUMA_BR_W17_PRE_LEN                         (9U)
#define DSP2_MIDDLE2_LUMA_BR_W17_PRE_MSK                         (((1U<<DSP2_MIDDLE2_LUMA_BR_W17_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W17_PRE_POS)
#define DSP2_MIDDLE2_LUMA_BR_W17_PRE_UMSK                        (~(((1U<<DSP2_MIDDLE2_LUMA_BR_W17_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W17_PRE_POS))
#define DSP2_MIDDLE2_LUMA_BR_W16_PRE                             DSP2_MIDDLE2_LUMA_BR_W16_PRE
#define DSP2_MIDDLE2_LUMA_BR_W16_PRE_POS                         (16U)
#define DSP2_MIDDLE2_LUMA_BR_W16_PRE_LEN                         (9U)
#define DSP2_MIDDLE2_LUMA_BR_W16_PRE_MSK                         (((1U<<DSP2_MIDDLE2_LUMA_BR_W16_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W16_PRE_POS)
#define DSP2_MIDDLE2_LUMA_BR_W16_PRE_UMSK                        (~(((1U<<DSP2_MIDDLE2_LUMA_BR_W16_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W16_PRE_POS))

/* 0x894 : BDM_37 */
#define DSP2_MIDDLE2_BDM_37_OFFSET                               (0x894)
#define DSP2_MIDDLE2_LUMA_BR_W19_PRE                             DSP2_MIDDLE2_LUMA_BR_W19_PRE
#define DSP2_MIDDLE2_LUMA_BR_W19_PRE_POS                         (0U)
#define DSP2_MIDDLE2_LUMA_BR_W19_PRE_LEN                         (9U)
#define DSP2_MIDDLE2_LUMA_BR_W19_PRE_MSK                         (((1U<<DSP2_MIDDLE2_LUMA_BR_W19_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W19_PRE_POS)
#define DSP2_MIDDLE2_LUMA_BR_W19_PRE_UMSK                        (~(((1U<<DSP2_MIDDLE2_LUMA_BR_W19_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W19_PRE_POS))
#define DSP2_MIDDLE2_LUMA_BR_W18_PRE                             DSP2_MIDDLE2_LUMA_BR_W18_PRE
#define DSP2_MIDDLE2_LUMA_BR_W18_PRE_POS                         (16U)
#define DSP2_MIDDLE2_LUMA_BR_W18_PRE_LEN                         (9U)
#define DSP2_MIDDLE2_LUMA_BR_W18_PRE_MSK                         (((1U<<DSP2_MIDDLE2_LUMA_BR_W18_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W18_PRE_POS)
#define DSP2_MIDDLE2_LUMA_BR_W18_PRE_UMSK                        (~(((1U<<DSP2_MIDDLE2_LUMA_BR_W18_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W18_PRE_POS))

/* 0x898 : BDM_38 */
#define DSP2_MIDDLE2_BDM_38_OFFSET                               (0x898)
#define DSP2_MIDDLE2_LUMA_BR_W21_PRE                             DSP2_MIDDLE2_LUMA_BR_W21_PRE
#define DSP2_MIDDLE2_LUMA_BR_W21_PRE_POS                         (0U)
#define DSP2_MIDDLE2_LUMA_BR_W21_PRE_LEN                         (9U)
#define DSP2_MIDDLE2_LUMA_BR_W21_PRE_MSK                         (((1U<<DSP2_MIDDLE2_LUMA_BR_W21_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W21_PRE_POS)
#define DSP2_MIDDLE2_LUMA_BR_W21_PRE_UMSK                        (~(((1U<<DSP2_MIDDLE2_LUMA_BR_W21_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W21_PRE_POS))
#define DSP2_MIDDLE2_LUMA_BR_W20_PRE                             DSP2_MIDDLE2_LUMA_BR_W20_PRE
#define DSP2_MIDDLE2_LUMA_BR_W20_PRE_POS                         (16U)
#define DSP2_MIDDLE2_LUMA_BR_W20_PRE_LEN                         (9U)
#define DSP2_MIDDLE2_LUMA_BR_W20_PRE_MSK                         (((1U<<DSP2_MIDDLE2_LUMA_BR_W20_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W20_PRE_POS)
#define DSP2_MIDDLE2_LUMA_BR_W20_PRE_UMSK                        (~(((1U<<DSP2_MIDDLE2_LUMA_BR_W20_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W20_PRE_POS))

/* 0x89C : BDM_39 */
#define DSP2_MIDDLE2_BDM_39_OFFSET                               (0x89C)
#define DSP2_MIDDLE2_LUMA_BR_W23_PRE                             DSP2_MIDDLE2_LUMA_BR_W23_PRE
#define DSP2_MIDDLE2_LUMA_BR_W23_PRE_POS                         (0U)
#define DSP2_MIDDLE2_LUMA_BR_W23_PRE_LEN                         (9U)
#define DSP2_MIDDLE2_LUMA_BR_W23_PRE_MSK                         (((1U<<DSP2_MIDDLE2_LUMA_BR_W23_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W23_PRE_POS)
#define DSP2_MIDDLE2_LUMA_BR_W23_PRE_UMSK                        (~(((1U<<DSP2_MIDDLE2_LUMA_BR_W23_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W23_PRE_POS))
#define DSP2_MIDDLE2_LUMA_BR_W22_PRE                             DSP2_MIDDLE2_LUMA_BR_W22_PRE
#define DSP2_MIDDLE2_LUMA_BR_W22_PRE_POS                         (16U)
#define DSP2_MIDDLE2_LUMA_BR_W22_PRE_LEN                         (9U)
#define DSP2_MIDDLE2_LUMA_BR_W22_PRE_MSK                         (((1U<<DSP2_MIDDLE2_LUMA_BR_W22_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W22_PRE_POS)
#define DSP2_MIDDLE2_LUMA_BR_W22_PRE_UMSK                        (~(((1U<<DSP2_MIDDLE2_LUMA_BR_W22_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W22_PRE_POS))

/* 0x8A0 : BDM_40 */
#define DSP2_MIDDLE2_BDM_40_OFFSET                               (0x8A0)
#define DSP2_MIDDLE2_LUMA_BR_W25_PRE                             DSP2_MIDDLE2_LUMA_BR_W25_PRE
#define DSP2_MIDDLE2_LUMA_BR_W25_PRE_POS                         (0U)
#define DSP2_MIDDLE2_LUMA_BR_W25_PRE_LEN                         (9U)
#define DSP2_MIDDLE2_LUMA_BR_W25_PRE_MSK                         (((1U<<DSP2_MIDDLE2_LUMA_BR_W25_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W25_PRE_POS)
#define DSP2_MIDDLE2_LUMA_BR_W25_PRE_UMSK                        (~(((1U<<DSP2_MIDDLE2_LUMA_BR_W25_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W25_PRE_POS))
#define DSP2_MIDDLE2_LUMA_BR_W24_PRE                             DSP2_MIDDLE2_LUMA_BR_W24_PRE
#define DSP2_MIDDLE2_LUMA_BR_W24_PRE_POS                         (16U)
#define DSP2_MIDDLE2_LUMA_BR_W24_PRE_LEN                         (9U)
#define DSP2_MIDDLE2_LUMA_BR_W24_PRE_MSK                         (((1U<<DSP2_MIDDLE2_LUMA_BR_W24_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W24_PRE_POS)
#define DSP2_MIDDLE2_LUMA_BR_W24_PRE_UMSK                        (~(((1U<<DSP2_MIDDLE2_LUMA_BR_W24_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W24_PRE_POS))

/* 0x8A4 : BDM_41 */
#define DSP2_MIDDLE2_BDM_41_OFFSET                               (0x8A4)
#define DSP2_MIDDLE2_LUMA_BR_W27_PRE                             DSP2_MIDDLE2_LUMA_BR_W27_PRE
#define DSP2_MIDDLE2_LUMA_BR_W27_PRE_POS                         (0U)
#define DSP2_MIDDLE2_LUMA_BR_W27_PRE_LEN                         (9U)
#define DSP2_MIDDLE2_LUMA_BR_W27_PRE_MSK                         (((1U<<DSP2_MIDDLE2_LUMA_BR_W27_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W27_PRE_POS)
#define DSP2_MIDDLE2_LUMA_BR_W27_PRE_UMSK                        (~(((1U<<DSP2_MIDDLE2_LUMA_BR_W27_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W27_PRE_POS))
#define DSP2_MIDDLE2_LUMA_BR_W26_PRE                             DSP2_MIDDLE2_LUMA_BR_W26_PRE
#define DSP2_MIDDLE2_LUMA_BR_W26_PRE_POS                         (16U)
#define DSP2_MIDDLE2_LUMA_BR_W26_PRE_LEN                         (9U)
#define DSP2_MIDDLE2_LUMA_BR_W26_PRE_MSK                         (((1U<<DSP2_MIDDLE2_LUMA_BR_W26_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W26_PRE_POS)
#define DSP2_MIDDLE2_LUMA_BR_W26_PRE_UMSK                        (~(((1U<<DSP2_MIDDLE2_LUMA_BR_W26_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W26_PRE_POS))

/* 0x8A8 : BDM_42 */
#define DSP2_MIDDLE2_BDM_42_OFFSET                               (0x8A8)
#define DSP2_MIDDLE2_LUMA_BR_W29_PRE                             DSP2_MIDDLE2_LUMA_BR_W29_PRE
#define DSP2_MIDDLE2_LUMA_BR_W29_PRE_POS                         (0U)
#define DSP2_MIDDLE2_LUMA_BR_W29_PRE_LEN                         (9U)
#define DSP2_MIDDLE2_LUMA_BR_W29_PRE_MSK                         (((1U<<DSP2_MIDDLE2_LUMA_BR_W29_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W29_PRE_POS)
#define DSP2_MIDDLE2_LUMA_BR_W29_PRE_UMSK                        (~(((1U<<DSP2_MIDDLE2_LUMA_BR_W29_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W29_PRE_POS))
#define DSP2_MIDDLE2_LUMA_BR_W28_PRE                             DSP2_MIDDLE2_LUMA_BR_W28_PRE
#define DSP2_MIDDLE2_LUMA_BR_W28_PRE_POS                         (16U)
#define DSP2_MIDDLE2_LUMA_BR_W28_PRE_LEN                         (9U)
#define DSP2_MIDDLE2_LUMA_BR_W28_PRE_MSK                         (((1U<<DSP2_MIDDLE2_LUMA_BR_W28_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W28_PRE_POS)
#define DSP2_MIDDLE2_LUMA_BR_W28_PRE_UMSK                        (~(((1U<<DSP2_MIDDLE2_LUMA_BR_W28_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W28_PRE_POS))

/* 0x8AC : BDM_43 */
#define DSP2_MIDDLE2_BDM_43_OFFSET                               (0x8AC)
#define DSP2_MIDDLE2_LUMA_BR_W31_PRE                             DSP2_MIDDLE2_LUMA_BR_W31_PRE
#define DSP2_MIDDLE2_LUMA_BR_W31_PRE_POS                         (0U)
#define DSP2_MIDDLE2_LUMA_BR_W31_PRE_LEN                         (9U)
#define DSP2_MIDDLE2_LUMA_BR_W31_PRE_MSK                         (((1U<<DSP2_MIDDLE2_LUMA_BR_W31_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W31_PRE_POS)
#define DSP2_MIDDLE2_LUMA_BR_W31_PRE_UMSK                        (~(((1U<<DSP2_MIDDLE2_LUMA_BR_W31_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W31_PRE_POS))
#define DSP2_MIDDLE2_LUMA_BR_W30_PRE                             DSP2_MIDDLE2_LUMA_BR_W30_PRE
#define DSP2_MIDDLE2_LUMA_BR_W30_PRE_POS                         (16U)
#define DSP2_MIDDLE2_LUMA_BR_W30_PRE_LEN                         (9U)
#define DSP2_MIDDLE2_LUMA_BR_W30_PRE_MSK                         (((1U<<DSP2_MIDDLE2_LUMA_BR_W30_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W30_PRE_POS)
#define DSP2_MIDDLE2_LUMA_BR_W30_PRE_UMSK                        (~(((1U<<DSP2_MIDDLE2_LUMA_BR_W30_PRE_LEN)-1)<<DSP2_MIDDLE2_LUMA_BR_W30_PRE_POS))

/* 0x8B0 : BDM_44 */
#define DSP2_MIDDLE2_BDM_44_OFFSET                               (0x8B0)
#define DSP2_MIDDLE2_G_COREW_PRE                                 DSP2_MIDDLE2_G_COREW_PRE
#define DSP2_MIDDLE2_G_COREW_PRE_POS                             (0U)
#define DSP2_MIDDLE2_G_COREW_PRE_LEN                             (8U)
#define DSP2_MIDDLE2_G_COREW_PRE_MSK                             (((1U<<DSP2_MIDDLE2_G_COREW_PRE_LEN)-1)<<DSP2_MIDDLE2_G_COREW_PRE_POS)
#define DSP2_MIDDLE2_G_COREW_PRE_UMSK                            (~(((1U<<DSP2_MIDDLE2_G_COREW_PRE_LEN)-1)<<DSP2_MIDDLE2_G_COREW_PRE_POS))
#define DSP2_MIDDLE2_BR_COREW_PRE                                DSP2_MIDDLE2_BR_COREW_PRE
#define DSP2_MIDDLE2_BR_COREW_PRE_POS                            (8U)
#define DSP2_MIDDLE2_BR_COREW_PRE_LEN                            (8U)
#define DSP2_MIDDLE2_BR_COREW_PRE_MSK                            (((1U<<DSP2_MIDDLE2_BR_COREW_PRE_LEN)-1)<<DSP2_MIDDLE2_BR_COREW_PRE_POS)
#define DSP2_MIDDLE2_BR_COREW_PRE_UMSK                           (~(((1U<<DSP2_MIDDLE2_BR_COREW_PRE_LEN)-1)<<DSP2_MIDDLE2_BR_COREW_PRE_POS))


struct  dsp2_middle2_reg {
    /* 0x0  reserved */
    uint8_t RESERVED0x0[2048];

    /* 0x800 : BDM_1 */
    union {
        struct {
            uint32_t bdm_eb_pre                     :  1; /* [    0],        r/w,        0x0 */
            uint32_t reserved_1_7                   :  7; /* [ 7: 1],       rsvd,        0x0 */
            uint32_t gw_thr_pre                     :  5; /* [12: 8],        r/w,        0x5 */
            uint32_t reserved_13_15                 :  3; /* [15:13],       rsvd,        0x0 */
            uint32_t g_scal_factor_pre              :  9; /* [24:16],        r/w,       0x40 */
            uint32_t reserved_25_31                 :  7; /* [31:25],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BDM_1;

    /* 0x804 : BDM_2 */
    union {
        struct {
            uint32_t r_scal_factor_pre              :  9; /* [ 8: 0],        r/w,       0x40 */
            uint32_t reserved_9_15                  :  7; /* [15: 9],       rsvd,        0x0 */
            uint32_t b_scal_factor_pre              :  9; /* [24:16],        r/w,       0x40 */
            uint32_t reserved_25_31                 :  7; /* [31:25],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BDM_2;

    /* 0x808 : BDM_3 */
    union {
        struct {
            uint32_t nr_profile10_pre               : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t nr_profile00_pre               : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BDM_3;

    /* 0x80C : BDM_4 */
    union {
        struct {
            uint32_t nr_profile30_pre               : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t nr_profile20_pre               : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BDM_4;

    /* 0x810 : BDM_5 */
    union {
        struct {
            uint32_t nr_profile50_pre               : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t nr_profile40_pre               : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BDM_5;

    /* 0x814 : BDM_6 */
    union {
        struct {
            uint32_t nr_profile01_pre               : 17; /* [16: 0],        r/w,        0x0 */
            uint32_t reserved_17_31                 : 15; /* [31:17],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BDM_6;

    /* 0x818 : BDM_7 */
    union {
        struct {
            uint32_t nr_profile11_pre               : 17; /* [16: 0],        r/w,        0x0 */
            uint32_t reserved_17_31                 : 15; /* [31:17],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BDM_7;

    /* 0x81C : BDM_8 */
    union {
        struct {
            uint32_t nr_profile21_pre               : 17; /* [16: 0],        r/w,        0x0 */
            uint32_t reserved_17_31                 : 15; /* [31:17],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BDM_8;

    /* 0x820 : BDM_9 */
    union {
        struct {
            uint32_t nr_profile31_pre               : 17; /* [16: 0],        r/w,        0x0 */
            uint32_t reserved_17_31                 : 15; /* [31:17],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BDM_9;

    /* 0x824 : BDM_10 */
    union {
        struct {
            uint32_t nr_profile41_pre               : 17; /* [16: 0],        r/w,        0x0 */
            uint32_t reserved_17_31                 : 15; /* [31:17],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BDM_10;

    /* 0x828 : BDM_11 */
    union {
        struct {
            uint32_t nr_profile51_pre               : 17; /* [16: 0],        r/w,        0x0 */
            uint32_t reserved_17_31                 : 15; /* [31:17],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BDM_11;

    /* 0x82C : BDM_12 */
    union {
        struct {
            uint32_t luma_g_w1_pre                  :  9; /* [ 8: 0],        r/w,       0x80 */
            uint32_t reserved_9_15                  :  7; /* [15: 9],       rsvd,        0x0 */
            uint32_t luma_g_w0_pre                  :  9; /* [24:16],        r/w,       0x80 */
            uint32_t reserved_25_31                 :  7; /* [31:25],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BDM_12;

    /* 0x830 : BDM_13 */
    union {
        struct {
            uint32_t luma_g_w3_pre                  :  9; /* [ 8: 0],        r/w,       0x80 */
            uint32_t reserved_9_15                  :  7; /* [15: 9],       rsvd,        0x0 */
            uint32_t luma_g_w2_pre                  :  9; /* [24:16],        r/w,       0x80 */
            uint32_t reserved_25_31                 :  7; /* [31:25],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BDM_13;

    /* 0x834 : BDM_14 */
    union {
        struct {
            uint32_t luma_g_w5_pre                  :  9; /* [ 8: 0],        r/w,       0x80 */
            uint32_t reserved_9_15                  :  7; /* [15: 9],       rsvd,        0x0 */
            uint32_t luma_g_w4_pre                  :  9; /* [24:16],        r/w,       0x80 */
            uint32_t reserved_25_31                 :  7; /* [31:25],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BDM_14;

    /* 0x838 : BDM_15 */
    union {
        struct {
            uint32_t luma_g_w7_pre                  :  9; /* [ 8: 0],        r/w,       0x80 */
            uint32_t reserved_9_15                  :  7; /* [15: 9],       rsvd,        0x0 */
            uint32_t luma_g_w6_pre                  :  9; /* [24:16],        r/w,       0x80 */
            uint32_t reserved_25_31                 :  7; /* [31:25],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BDM_15;

    /* 0x83C : BDM_16 */
    union {
        struct {
            uint32_t luma_g_w9_pre                  :  9; /* [ 8: 0],        r/w,       0x80 */
            uint32_t reserved_9_15                  :  7; /* [15: 9],       rsvd,        0x0 */
            uint32_t luma_g_w8_pre                  :  9; /* [24:16],        r/w,       0x80 */
            uint32_t reserved_25_31                 :  7; /* [31:25],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BDM_16;

    /* 0x840 : BDM_17 */
    union {
        struct {
            uint32_t luma_g_w11_pre                 :  9; /* [ 8: 0],        r/w,       0x80 */
            uint32_t reserved_9_15                  :  7; /* [15: 9],       rsvd,        0x0 */
            uint32_t luma_g_w10_pre                 :  9; /* [24:16],        r/w,       0x80 */
            uint32_t reserved_25_31                 :  7; /* [31:25],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BDM_17;

    /* 0x844 : BDM_18 */
    union {
        struct {
            uint32_t luma_g_w13_pre                 :  9; /* [ 8: 0],        r/w,       0x80 */
            uint32_t reserved_9_15                  :  7; /* [15: 9],       rsvd,        0x0 */
            uint32_t luma_g_w12_pre                 :  9; /* [24:16],        r/w,       0x80 */
            uint32_t reserved_25_31                 :  7; /* [31:25],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BDM_18;

    /* 0x848 : BDM_19 */
    union {
        struct {
            uint32_t luma_g_w15_pre                 :  9; /* [ 8: 0],        r/w,       0x80 */
            uint32_t reserved_9_15                  :  7; /* [15: 9],       rsvd,        0x0 */
            uint32_t luma_g_w14_pre                 :  9; /* [24:16],        r/w,       0x80 */
            uint32_t reserved_25_31                 :  7; /* [31:25],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BDM_19;

    /* 0x84C : BDM_20 */
    union {
        struct {
            uint32_t luma_g_w17_pre                 :  9; /* [ 8: 0],        r/w,       0x80 */
            uint32_t reserved_9_15                  :  7; /* [15: 9],       rsvd,        0x0 */
            uint32_t luma_g_w16_pre                 :  9; /* [24:16],        r/w,       0x80 */
            uint32_t reserved_25_31                 :  7; /* [31:25],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BDM_20;

    /* 0x850 : BDM_21 */
    union {
        struct {
            uint32_t luma_g_w19_pre                 :  9; /* [ 8: 0],        r/w,       0x80 */
            uint32_t reserved_9_15                  :  7; /* [15: 9],       rsvd,        0x0 */
            uint32_t luma_g_w18_pre                 :  9; /* [24:16],        r/w,       0x80 */
            uint32_t reserved_25_31                 :  7; /* [31:25],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BDM_21;

    /* 0x854 : BDM_22 */
    union {
        struct {
            uint32_t luma_g_w21_pre                 :  9; /* [ 8: 0],        r/w,       0x80 */
            uint32_t reserved_9_15                  :  7; /* [15: 9],       rsvd,        0x0 */
            uint32_t luma_g_w20_pre                 :  9; /* [24:16],        r/w,       0x80 */
            uint32_t reserved_25_31                 :  7; /* [31:25],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BDM_22;

    /* 0x858 : BDM_23 */
    union {
        struct {
            uint32_t luma_g_w23_pre                 :  9; /* [ 8: 0],        r/w,       0x80 */
            uint32_t reserved_9_15                  :  7; /* [15: 9],       rsvd,        0x0 */
            uint32_t luma_g_w22_pre                 :  9; /* [24:16],        r/w,       0x80 */
            uint32_t reserved_25_31                 :  7; /* [31:25],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BDM_23;

    /* 0x85C : BDM_24 */
    union {
        struct {
            uint32_t luma_g_w25_pre                 :  9; /* [ 8: 0],        r/w,       0x80 */
            uint32_t reserved_9_15                  :  7; /* [15: 9],       rsvd,        0x0 */
            uint32_t luma_g_w24_pre                 :  9; /* [24:16],        r/w,       0x80 */
            uint32_t reserved_25_31                 :  7; /* [31:25],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BDM_24;

    /* 0x860 : BDM_25 */
    union {
        struct {
            uint32_t luma_g_w27_pre                 :  9; /* [ 8: 0],        r/w,       0x80 */
            uint32_t reserved_9_15                  :  7; /* [15: 9],       rsvd,        0x0 */
            uint32_t luma_g_w26_pre                 :  9; /* [24:16],        r/w,       0x80 */
            uint32_t reserved_25_31                 :  7; /* [31:25],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BDM_25;

    /* 0x864 : BDM_26 */
    union {
        struct {
            uint32_t luma_g_w29_pre                 :  9; /* [ 8: 0],        r/w,       0x80 */
            uint32_t reserved_9_15                  :  7; /* [15: 9],       rsvd,        0x0 */
            uint32_t luma_g_w28_pre                 :  9; /* [24:16],        r/w,       0x80 */
            uint32_t reserved_25_31                 :  7; /* [31:25],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BDM_26;

    /* 0x868 : BDM_27 */
    union {
        struct {
            uint32_t luma_g_w31_pre                 :  9; /* [ 8: 0],        r/w,       0x80 */
            uint32_t reserved_9_15                  :  7; /* [15: 9],       rsvd,        0x0 */
            uint32_t luma_g_w30_pre                 :  9; /* [24:16],        r/w,       0x80 */
            uint32_t reserved_25_31                 :  7; /* [31:25],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BDM_27;

    /* 0x86c  reserved */
    uint8_t RESERVED0x86c[4];

    /* 0x870 : BDM_28 */
    union {
        struct {
            uint32_t luma_br_w1_pre                 :  9; /* [ 8: 0],        r/w,       0x80 */
            uint32_t reserved_9_15                  :  7; /* [15: 9],       rsvd,        0x0 */
            uint32_t luma_br_w0_pre                 :  9; /* [24:16],        r/w,       0x80 */
            uint32_t reserved_25_31                 :  7; /* [31:25],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BDM_28;

    /* 0x874 : BDM_29 */
    union {
        struct {
            uint32_t luma_br_w3_pre                 :  9; /* [ 8: 0],        r/w,       0x80 */
            uint32_t reserved_9_15                  :  7; /* [15: 9],       rsvd,        0x0 */
            uint32_t luma_br_w2_pre                 :  9; /* [24:16],        r/w,       0x80 */
            uint32_t reserved_25_31                 :  7; /* [31:25],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BDM_29;

    /* 0x878 : BDM_30 */
    union {
        struct {
            uint32_t luma_br_w5_pre                 :  9; /* [ 8: 0],        r/w,       0x80 */
            uint32_t reserved_9_15                  :  7; /* [15: 9],       rsvd,        0x0 */
            uint32_t luma_br_w4_pre                 :  9; /* [24:16],        r/w,       0x80 */
            uint32_t reserved_25_31                 :  7; /* [31:25],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BDM_30;

    /* 0x87C : BDM_31 */
    union {
        struct {
            uint32_t luma_br_w7_pre                 :  9; /* [ 8: 0],        r/w,       0x80 */
            uint32_t reserved_9_15                  :  7; /* [15: 9],       rsvd,        0x0 */
            uint32_t luma_br_w6_pre                 :  9; /* [24:16],        r/w,       0x80 */
            uint32_t reserved_25_31                 :  7; /* [31:25],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BDM_31;

    /* 0x880 : BDM_32 */
    union {
        struct {
            uint32_t luma_br_w9_pre                 :  9; /* [ 8: 0],        r/w,       0x80 */
            uint32_t reserved_9_15                  :  7; /* [15: 9],       rsvd,        0x0 */
            uint32_t luma_br_w8_pre                 :  9; /* [24:16],        r/w,       0x80 */
            uint32_t reserved_25_31                 :  7; /* [31:25],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BDM_32;

    /* 0x884 : BDM_33 */
    union {
        struct {
            uint32_t luma_br_w11_pre                :  9; /* [ 8: 0],        r/w,       0x80 */
            uint32_t reserved_9_15                  :  7; /* [15: 9],       rsvd,        0x0 */
            uint32_t luma_br_w10_pre                :  9; /* [24:16],        r/w,       0x80 */
            uint32_t reserved_25_31                 :  7; /* [31:25],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BDM_33;

    /* 0x888 : BDM_34 */
    union {
        struct {
            uint32_t luma_br_w13_pre                :  9; /* [ 8: 0],        r/w,       0x80 */
            uint32_t reserved_9_15                  :  7; /* [15: 9],       rsvd,        0x0 */
            uint32_t luma_br_w12_pre                :  9; /* [24:16],        r/w,       0x80 */
            uint32_t reserved_25_31                 :  7; /* [31:25],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BDM_34;

    /* 0x88C : BDM_35 */
    union {
        struct {
            uint32_t luma_br_w15_pre                :  9; /* [ 8: 0],        r/w,       0x80 */
            uint32_t reserved_9_15                  :  7; /* [15: 9],       rsvd,        0x0 */
            uint32_t luma_br_w14_pre                :  9; /* [24:16],        r/w,       0x80 */
            uint32_t reserved_25_31                 :  7; /* [31:25],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BDM_35;

    /* 0x890 : BDM_36 */
    union {
        struct {
            uint32_t luma_br_w17_pre                :  9; /* [ 8: 0],        r/w,       0x80 */
            uint32_t reserved_9_15                  :  7; /* [15: 9],       rsvd,        0x0 */
            uint32_t luma_br_w16_pre                :  9; /* [24:16],        r/w,       0x80 */
            uint32_t reserved_25_31                 :  7; /* [31:25],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BDM_36;

    /* 0x894 : BDM_37 */
    union {
        struct {
            uint32_t luma_br_w19_pre                :  9; /* [ 8: 0],        r/w,       0x80 */
            uint32_t reserved_9_15                  :  7; /* [15: 9],       rsvd,        0x0 */
            uint32_t luma_br_w18_pre                :  9; /* [24:16],        r/w,       0x80 */
            uint32_t reserved_25_31                 :  7; /* [31:25],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BDM_37;

    /* 0x898 : BDM_38 */
    union {
        struct {
            uint32_t luma_br_w21_pre                :  9; /* [ 8: 0],        r/w,       0x80 */
            uint32_t reserved_9_15                  :  7; /* [15: 9],       rsvd,        0x0 */
            uint32_t luma_br_w20_pre                :  9; /* [24:16],        r/w,       0x80 */
            uint32_t reserved_25_31                 :  7; /* [31:25],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BDM_38;

    /* 0x89C : BDM_39 */
    union {
        struct {
            uint32_t luma_br_w23_pre                :  9; /* [ 8: 0],        r/w,       0x80 */
            uint32_t reserved_9_15                  :  7; /* [15: 9],       rsvd,        0x0 */
            uint32_t luma_br_w22_pre                :  9; /* [24:16],        r/w,       0x80 */
            uint32_t reserved_25_31                 :  7; /* [31:25],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BDM_39;

    /* 0x8A0 : BDM_40 */
    union {
        struct {
            uint32_t luma_br_w25_pre                :  9; /* [ 8: 0],        r/w,       0x80 */
            uint32_t reserved_9_15                  :  7; /* [15: 9],       rsvd,        0x0 */
            uint32_t luma_br_w24_pre                :  9; /* [24:16],        r/w,       0x80 */
            uint32_t reserved_25_31                 :  7; /* [31:25],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BDM_40;

    /* 0x8A4 : BDM_41 */
    union {
        struct {
            uint32_t luma_br_w27_pre                :  9; /* [ 8: 0],        r/w,       0x80 */
            uint32_t reserved_9_15                  :  7; /* [15: 9],       rsvd,        0x0 */
            uint32_t luma_br_w26_pre                :  9; /* [24:16],        r/w,       0x80 */
            uint32_t reserved_25_31                 :  7; /* [31:25],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BDM_41;

    /* 0x8A8 : BDM_42 */
    union {
        struct {
            uint32_t luma_br_w29_pre                :  9; /* [ 8: 0],        r/w,       0x80 */
            uint32_t reserved_9_15                  :  7; /* [15: 9],       rsvd,        0x0 */
            uint32_t luma_br_w28_pre                :  9; /* [24:16],        r/w,       0x80 */
            uint32_t reserved_25_31                 :  7; /* [31:25],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BDM_42;

    /* 0x8AC : BDM_43 */
    union {
        struct {
            uint32_t luma_br_w31_pre                :  9; /* [ 8: 0],        r/w,       0x80 */
            uint32_t reserved_9_15                  :  7; /* [15: 9],       rsvd,        0x0 */
            uint32_t luma_br_w30_pre                :  9; /* [24:16],        r/w,       0x80 */
            uint32_t reserved_25_31                 :  7; /* [31:25],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BDM_43;

    /* 0x8B0 : BDM_44 */
    union {
        struct {
            uint32_t g_corew_pre                    :  8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t br_corew_pre                   :  8; /* [15: 8],        r/w,        0x0 */
            uint32_t reserved_16_31                 : 16; /* [31:16],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BDM_44;

};

typedef volatile struct dsp2_middle2_reg dsp2_middle2_reg_t;


#endif  /* __DSP2_MIDDLE2_REG_H__ */
