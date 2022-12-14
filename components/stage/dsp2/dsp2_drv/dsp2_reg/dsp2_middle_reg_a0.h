/**
  ******************************************************************************
  * @file    dsp2_middle_reg.h
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
#ifndef  __DSP2_MIDDLE_REG_H__
#define  __DSP2_MIDDLE_REG_H__

#include "bl808.h"

/* 0x224 : LSC_setting */
#define DSP2_MIDDLE_LSC_SETTING_OFFSET                           (0x224)
#define DSP2_MIDDLE_LSC_ON_W                                     DSP2_MIDDLE_LSC_ON_W
#define DSP2_MIDDLE_LSC_ON_W_POS                                 (8U)
#define DSP2_MIDDLE_LSC_ON_W_LEN                                 (1U)
#define DSP2_MIDDLE_LSC_ON_W_MSK                                 (((1U<<DSP2_MIDDLE_LSC_ON_W_LEN)-1)<<DSP2_MIDDLE_LSC_ON_W_POS)
#define DSP2_MIDDLE_LSC_ON_W_UMSK                                (~(((1U<<DSP2_MIDDLE_LSC_ON_W_LEN)-1)<<DSP2_MIDDLE_LSC_ON_W_POS))
#define DSP2_MIDDLE_X_OFFSET_W                                   DSP2_MIDDLE_X_OFFSET_W
#define DSP2_MIDDLE_X_OFFSET_W_POS                               (16U)
#define DSP2_MIDDLE_X_OFFSET_W_LEN                               (8U)
#define DSP2_MIDDLE_X_OFFSET_W_MSK                               (((1U<<DSP2_MIDDLE_X_OFFSET_W_LEN)-1)<<DSP2_MIDDLE_X_OFFSET_W_POS)
#define DSP2_MIDDLE_X_OFFSET_W_UMSK                              (~(((1U<<DSP2_MIDDLE_X_OFFSET_W_LEN)-1)<<DSP2_MIDDLE_X_OFFSET_W_POS))
#define DSP2_MIDDLE_Y_OFFSET_W                                   DSP2_MIDDLE_Y_OFFSET_W
#define DSP2_MIDDLE_Y_OFFSET_W_POS                               (24U)
#define DSP2_MIDDLE_Y_OFFSET_W_LEN                               (8U)
#define DSP2_MIDDLE_Y_OFFSET_W_MSK                               (((1U<<DSP2_MIDDLE_Y_OFFSET_W_LEN)-1)<<DSP2_MIDDLE_Y_OFFSET_W_POS)
#define DSP2_MIDDLE_Y_OFFSET_W_UMSK                              (~(((1U<<DSP2_MIDDLE_Y_OFFSET_W_LEN)-1)<<DSP2_MIDDLE_Y_OFFSET_W_POS))

/* 0x228 : LSC_coeff_R_A */
#define DSP2_MIDDLE_LSC_COEFF_R_A_OFFSET                         (0x228)
#define DSP2_MIDDLE_R_ACOEFF_W                                   DSP2_MIDDLE_R_ACOEFF_W
#define DSP2_MIDDLE_R_ACOEFF_W_POS                               (0U)
#define DSP2_MIDDLE_R_ACOEFF_W_LEN                               (23U)
#define DSP2_MIDDLE_R_ACOEFF_W_MSK                               (((1U<<DSP2_MIDDLE_R_ACOEFF_W_LEN)-1)<<DSP2_MIDDLE_R_ACOEFF_W_POS)
#define DSP2_MIDDLE_R_ACOEFF_W_UMSK                              (~(((1U<<DSP2_MIDDLE_R_ACOEFF_W_LEN)-1)<<DSP2_MIDDLE_R_ACOEFF_W_POS))

/* 0x22C : LSC_coeff_R_BE */
#define DSP2_MIDDLE_LSC_COEFF_R_BE_OFFSET                        (0x22C)
#define DSP2_MIDDLE_R_BCOEFF_W                                   DSP2_MIDDLE_R_BCOEFF_W
#define DSP2_MIDDLE_R_BCOEFF_W_POS                               (0U)
#define DSP2_MIDDLE_R_BCOEFF_W_LEN                               (13U)
#define DSP2_MIDDLE_R_BCOEFF_W_MSK                               (((1U<<DSP2_MIDDLE_R_BCOEFF_W_LEN)-1)<<DSP2_MIDDLE_R_BCOEFF_W_POS)
#define DSP2_MIDDLE_R_BCOEFF_W_UMSK                              (~(((1U<<DSP2_MIDDLE_R_BCOEFF_W_LEN)-1)<<DSP2_MIDDLE_R_BCOEFF_W_POS))
#define DSP2_MIDDLE_R_ECOEFF_W                                   DSP2_MIDDLE_R_ECOEFF_W
#define DSP2_MIDDLE_R_ECOEFF_W_POS                               (16U)
#define DSP2_MIDDLE_R_ECOEFF_W_LEN                               (13U)
#define DSP2_MIDDLE_R_ECOEFF_W_MSK                               (((1U<<DSP2_MIDDLE_R_ECOEFF_W_LEN)-1)<<DSP2_MIDDLE_R_ECOEFF_W_POS)
#define DSP2_MIDDLE_R_ECOEFF_W_UMSK                              (~(((1U<<DSP2_MIDDLE_R_ECOEFF_W_LEN)-1)<<DSP2_MIDDLE_R_ECOEFF_W_POS))

/* 0x230 : LSC_coeff_R_CD */
#define DSP2_MIDDLE_LSC_COEFF_R_CD_OFFSET                        (0x230)
#define DSP2_MIDDLE_R_DCOEFF_W                                   DSP2_MIDDLE_R_DCOEFF_W
#define DSP2_MIDDLE_R_DCOEFF_W_POS                               (0U)
#define DSP2_MIDDLE_R_DCOEFF_W_LEN                               (23U)
#define DSP2_MIDDLE_R_DCOEFF_W_MSK                               (((1U<<DSP2_MIDDLE_R_DCOEFF_W_LEN)-1)<<DSP2_MIDDLE_R_DCOEFF_W_POS)
#define DSP2_MIDDLE_R_DCOEFF_W_UMSK                              (~(((1U<<DSP2_MIDDLE_R_DCOEFF_W_LEN)-1)<<DSP2_MIDDLE_R_DCOEFF_W_POS))
#define DSP2_MIDDLE_R_CCOEFF_W                                   DSP2_MIDDLE_R_CCOEFF_W
#define DSP2_MIDDLE_R_CCOEFF_W_POS                               (24U)
#define DSP2_MIDDLE_R_CCOEFF_W_LEN                               (8U)
#define DSP2_MIDDLE_R_CCOEFF_W_MSK                               (((1U<<DSP2_MIDDLE_R_CCOEFF_W_LEN)-1)<<DSP2_MIDDLE_R_CCOEFF_W_POS)
#define DSP2_MIDDLE_R_CCOEFF_W_UMSK                              (~(((1U<<DSP2_MIDDLE_R_CCOEFF_W_LEN)-1)<<DSP2_MIDDLE_R_CCOEFF_W_POS))

/* 0x234 : LSC_coeff_R_G */
#define DSP2_MIDDLE_LSC_COEFF_R_G_OFFSET                         (0x234)
#define DSP2_MIDDLE_R_GCOEFF_W                                   DSP2_MIDDLE_R_GCOEFF_W
#define DSP2_MIDDLE_R_GCOEFF_W_POS                               (0U)
#define DSP2_MIDDLE_R_GCOEFF_W_LEN                               (23U)
#define DSP2_MIDDLE_R_GCOEFF_W_MSK                               (((1U<<DSP2_MIDDLE_R_GCOEFF_W_LEN)-1)<<DSP2_MIDDLE_R_GCOEFF_W_POS)
#define DSP2_MIDDLE_R_GCOEFF_W_UMSK                              (~(((1U<<DSP2_MIDDLE_R_GCOEFF_W_LEN)-1)<<DSP2_MIDDLE_R_GCOEFF_W_POS))

/* 0x238 : LSC_coeff_G_A */
#define DSP2_MIDDLE_LSC_COEFF_G_A_OFFSET                         (0x238)
#define DSP2_MIDDLE_G_ACOEFF_W                                   DSP2_MIDDLE_G_ACOEFF_W
#define DSP2_MIDDLE_G_ACOEFF_W_POS                               (0U)
#define DSP2_MIDDLE_G_ACOEFF_W_LEN                               (23U)
#define DSP2_MIDDLE_G_ACOEFF_W_MSK                               (((1U<<DSP2_MIDDLE_G_ACOEFF_W_LEN)-1)<<DSP2_MIDDLE_G_ACOEFF_W_POS)
#define DSP2_MIDDLE_G_ACOEFF_W_UMSK                              (~(((1U<<DSP2_MIDDLE_G_ACOEFF_W_LEN)-1)<<DSP2_MIDDLE_G_ACOEFF_W_POS))

/* 0x23C : LSC_coeff_G_BE */
#define DSP2_MIDDLE_LSC_COEFF_G_BE_OFFSET                        (0x23C)
#define DSP2_MIDDLE_G_BCOEFF_W                                   DSP2_MIDDLE_G_BCOEFF_W
#define DSP2_MIDDLE_G_BCOEFF_W_POS                               (0U)
#define DSP2_MIDDLE_G_BCOEFF_W_LEN                               (13U)
#define DSP2_MIDDLE_G_BCOEFF_W_MSK                               (((1U<<DSP2_MIDDLE_G_BCOEFF_W_LEN)-1)<<DSP2_MIDDLE_G_BCOEFF_W_POS)
#define DSP2_MIDDLE_G_BCOEFF_W_UMSK                              (~(((1U<<DSP2_MIDDLE_G_BCOEFF_W_LEN)-1)<<DSP2_MIDDLE_G_BCOEFF_W_POS))
#define DSP2_MIDDLE_G_ECOEFF_W                                   DSP2_MIDDLE_G_ECOEFF_W
#define DSP2_MIDDLE_G_ECOEFF_W_POS                               (16U)
#define DSP2_MIDDLE_G_ECOEFF_W_LEN                               (13U)
#define DSP2_MIDDLE_G_ECOEFF_W_MSK                               (((1U<<DSP2_MIDDLE_G_ECOEFF_W_LEN)-1)<<DSP2_MIDDLE_G_ECOEFF_W_POS)
#define DSP2_MIDDLE_G_ECOEFF_W_UMSK                              (~(((1U<<DSP2_MIDDLE_G_ECOEFF_W_LEN)-1)<<DSP2_MIDDLE_G_ECOEFF_W_POS))

/* 0x240 : LSC_coeff_G_CD */
#define DSP2_MIDDLE_LSC_COEFF_G_CD_OFFSET                        (0x240)
#define DSP2_MIDDLE_G_DCOEFF_W                                   DSP2_MIDDLE_G_DCOEFF_W
#define DSP2_MIDDLE_G_DCOEFF_W_POS                               (0U)
#define DSP2_MIDDLE_G_DCOEFF_W_LEN                               (23U)
#define DSP2_MIDDLE_G_DCOEFF_W_MSK                               (((1U<<DSP2_MIDDLE_G_DCOEFF_W_LEN)-1)<<DSP2_MIDDLE_G_DCOEFF_W_POS)
#define DSP2_MIDDLE_G_DCOEFF_W_UMSK                              (~(((1U<<DSP2_MIDDLE_G_DCOEFF_W_LEN)-1)<<DSP2_MIDDLE_G_DCOEFF_W_POS))
#define DSP2_MIDDLE_G_CCOEFF_W                                   DSP2_MIDDLE_G_CCOEFF_W
#define DSP2_MIDDLE_G_CCOEFF_W_POS                               (24U)
#define DSP2_MIDDLE_G_CCOEFF_W_LEN                               (8U)
#define DSP2_MIDDLE_G_CCOEFF_W_MSK                               (((1U<<DSP2_MIDDLE_G_CCOEFF_W_LEN)-1)<<DSP2_MIDDLE_G_CCOEFF_W_POS)
#define DSP2_MIDDLE_G_CCOEFF_W_UMSK                              (~(((1U<<DSP2_MIDDLE_G_CCOEFF_W_LEN)-1)<<DSP2_MIDDLE_G_CCOEFF_W_POS))

/* 0x244 : LSC_coeff_G_G */
#define DSP2_MIDDLE_LSC_COEFF_G_G_OFFSET                         (0x244)
#define DSP2_MIDDLE_G_GCOEFF_W                                   DSP2_MIDDLE_G_GCOEFF_W
#define DSP2_MIDDLE_G_GCOEFF_W_POS                               (0U)
#define DSP2_MIDDLE_G_GCOEFF_W_LEN                               (23U)
#define DSP2_MIDDLE_G_GCOEFF_W_MSK                               (((1U<<DSP2_MIDDLE_G_GCOEFF_W_LEN)-1)<<DSP2_MIDDLE_G_GCOEFF_W_POS)
#define DSP2_MIDDLE_G_GCOEFF_W_UMSK                              (~(((1U<<DSP2_MIDDLE_G_GCOEFF_W_LEN)-1)<<DSP2_MIDDLE_G_GCOEFF_W_POS))

/* 0x248 : LSC_coeff_B_A */
#define DSP2_MIDDLE_LSC_COEFF_B_A_OFFSET                         (0x248)
#define DSP2_MIDDLE_B_ACOEFF_W                                   DSP2_MIDDLE_B_ACOEFF_W
#define DSP2_MIDDLE_B_ACOEFF_W_POS                               (0U)
#define DSP2_MIDDLE_B_ACOEFF_W_LEN                               (23U)
#define DSP2_MIDDLE_B_ACOEFF_W_MSK                               (((1U<<DSP2_MIDDLE_B_ACOEFF_W_LEN)-1)<<DSP2_MIDDLE_B_ACOEFF_W_POS)
#define DSP2_MIDDLE_B_ACOEFF_W_UMSK                              (~(((1U<<DSP2_MIDDLE_B_ACOEFF_W_LEN)-1)<<DSP2_MIDDLE_B_ACOEFF_W_POS))

/* 0x24C : LSC_coeff_B_BE */
#define DSP2_MIDDLE_LSC_COEFF_B_BE_OFFSET                        (0x24C)
#define DSP2_MIDDLE_B_BCOEFF_W                                   DSP2_MIDDLE_B_BCOEFF_W
#define DSP2_MIDDLE_B_BCOEFF_W_POS                               (0U)
#define DSP2_MIDDLE_B_BCOEFF_W_LEN                               (13U)
#define DSP2_MIDDLE_B_BCOEFF_W_MSK                               (((1U<<DSP2_MIDDLE_B_BCOEFF_W_LEN)-1)<<DSP2_MIDDLE_B_BCOEFF_W_POS)
#define DSP2_MIDDLE_B_BCOEFF_W_UMSK                              (~(((1U<<DSP2_MIDDLE_B_BCOEFF_W_LEN)-1)<<DSP2_MIDDLE_B_BCOEFF_W_POS))
#define DSP2_MIDDLE_B_ECOEFF_W                                   DSP2_MIDDLE_B_ECOEFF_W
#define DSP2_MIDDLE_B_ECOEFF_W_POS                               (16U)
#define DSP2_MIDDLE_B_ECOEFF_W_LEN                               (13U)
#define DSP2_MIDDLE_B_ECOEFF_W_MSK                               (((1U<<DSP2_MIDDLE_B_ECOEFF_W_LEN)-1)<<DSP2_MIDDLE_B_ECOEFF_W_POS)
#define DSP2_MIDDLE_B_ECOEFF_W_UMSK                              (~(((1U<<DSP2_MIDDLE_B_ECOEFF_W_LEN)-1)<<DSP2_MIDDLE_B_ECOEFF_W_POS))

/* 0x250 : LSC_coeff_B_CD */
#define DSP2_MIDDLE_LSC_COEFF_B_CD_OFFSET                        (0x250)
#define DSP2_MIDDLE_B_DCOEFF_W                                   DSP2_MIDDLE_B_DCOEFF_W
#define DSP2_MIDDLE_B_DCOEFF_W_POS                               (0U)
#define DSP2_MIDDLE_B_DCOEFF_W_LEN                               (23U)
#define DSP2_MIDDLE_B_DCOEFF_W_MSK                               (((1U<<DSP2_MIDDLE_B_DCOEFF_W_LEN)-1)<<DSP2_MIDDLE_B_DCOEFF_W_POS)
#define DSP2_MIDDLE_B_DCOEFF_W_UMSK                              (~(((1U<<DSP2_MIDDLE_B_DCOEFF_W_LEN)-1)<<DSP2_MIDDLE_B_DCOEFF_W_POS))
#define DSP2_MIDDLE_B_CCOEFF_W                                   DSP2_MIDDLE_B_CCOEFF_W
#define DSP2_MIDDLE_B_CCOEFF_W_POS                               (24U)
#define DSP2_MIDDLE_B_CCOEFF_W_LEN                               (8U)
#define DSP2_MIDDLE_B_CCOEFF_W_MSK                               (((1U<<DSP2_MIDDLE_B_CCOEFF_W_LEN)-1)<<DSP2_MIDDLE_B_CCOEFF_W_POS)
#define DSP2_MIDDLE_B_CCOEFF_W_UMSK                              (~(((1U<<DSP2_MIDDLE_B_CCOEFF_W_LEN)-1)<<DSP2_MIDDLE_B_CCOEFF_W_POS))

/* 0x254 : LSC_coeff_B_G */
#define DSP2_MIDDLE_LSC_COEFF_B_G_OFFSET                         (0x254)
#define DSP2_MIDDLE_B_GCOEFF_W                                   DSP2_MIDDLE_B_GCOEFF_W
#define DSP2_MIDDLE_B_GCOEFF_W_POS                               (0U)
#define DSP2_MIDDLE_B_GCOEFF_W_LEN                               (23U)
#define DSP2_MIDDLE_B_GCOEFF_W_MSK                               (((1U<<DSP2_MIDDLE_B_GCOEFF_W_LEN)-1)<<DSP2_MIDDLE_B_GCOEFF_W_POS)
#define DSP2_MIDDLE_B_GCOEFF_W_UMSK                              (~(((1U<<DSP2_MIDDLE_B_GCOEFF_W_LEN)-1)<<DSP2_MIDDLE_B_GCOEFF_W_POS))

/* 0x258 : MAX_R_G */
#define DSP2_MIDDLE_MAX_R_G_OFFSET                               (0x258)
#define DSP2_MIDDLE_MAXR_W                                       DSP2_MIDDLE_MAXR_W
#define DSP2_MIDDLE_MAXR_W_POS                                   (0U)
#define DSP2_MIDDLE_MAXR_W_LEN                                   (16U)
#define DSP2_MIDDLE_MAXR_W_MSK                                   (((1U<<DSP2_MIDDLE_MAXR_W_LEN)-1)<<DSP2_MIDDLE_MAXR_W_POS)
#define DSP2_MIDDLE_MAXR_W_UMSK                                  (~(((1U<<DSP2_MIDDLE_MAXR_W_LEN)-1)<<DSP2_MIDDLE_MAXR_W_POS))
#define DSP2_MIDDLE_MAXG_W                                       DSP2_MIDDLE_MAXG_W
#define DSP2_MIDDLE_MAXG_W_POS                                   (16U)
#define DSP2_MIDDLE_MAXG_W_LEN                                   (16U)
#define DSP2_MIDDLE_MAXG_W_MSK                                   (((1U<<DSP2_MIDDLE_MAXG_W_LEN)-1)<<DSP2_MIDDLE_MAXG_W_POS)
#define DSP2_MIDDLE_MAXG_W_UMSK                                  (~(((1U<<DSP2_MIDDLE_MAXG_W_LEN)-1)<<DSP2_MIDDLE_MAXG_W_POS))

/* 0x25C : MAX_B */
#define DSP2_MIDDLE_MAX_B_OFFSET                                 (0x25C)
#define DSP2_MIDDLE_MAXB_W                                       DSP2_MIDDLE_MAXB_W
#define DSP2_MIDDLE_MAXB_W_POS                                   (0U)
#define DSP2_MIDDLE_MAXB_W_LEN                                   (16U)
#define DSP2_MIDDLE_MAXB_W_MSK                                   (((1U<<DSP2_MIDDLE_MAXB_W_LEN)-1)<<DSP2_MIDDLE_MAXB_W_POS)
#define DSP2_MIDDLE_MAXB_W_UMSK                                  (~(((1U<<DSP2_MIDDLE_MAXB_W_LEN)-1)<<DSP2_MIDDLE_MAXB_W_POS))

/* 0x260 : defect_setting */
#define DSP2_MIDDLE_DEFECT_SETTING_OFFSET                        (0x260)
#define DSP2_MIDDLE_DEFECT_CORRECT_MODE_W                        DSP2_MIDDLE_DEFECT_CORRECT_MODE_W
#define DSP2_MIDDLE_DEFECT_CORRECT_MODE_W_POS                    (0U)
#define DSP2_MIDDLE_DEFECT_CORRECT_MODE_W_LEN                    (3U)
#define DSP2_MIDDLE_DEFECT_CORRECT_MODE_W_MSK                    (((1U<<DSP2_MIDDLE_DEFECT_CORRECT_MODE_W_LEN)-1)<<DSP2_MIDDLE_DEFECT_CORRECT_MODE_W_POS)
#define DSP2_MIDDLE_DEFECT_CORRECT_MODE_W_UMSK                   (~(((1U<<DSP2_MIDDLE_DEFECT_CORRECT_MODE_W_LEN)-1)<<DSP2_MIDDLE_DEFECT_CORRECT_MODE_W_POS))
#define DSP2_MIDDLE_RESOLUTION_ENHANCE1_W                        DSP2_MIDDLE_RESOLUTION_ENHANCE1_W
#define DSP2_MIDDLE_RESOLUTION_ENHANCE1_W_POS                    (8U)
#define DSP2_MIDDLE_RESOLUTION_ENHANCE1_W_LEN                    (1U)
#define DSP2_MIDDLE_RESOLUTION_ENHANCE1_W_MSK                    (((1U<<DSP2_MIDDLE_RESOLUTION_ENHANCE1_W_LEN)-1)<<DSP2_MIDDLE_RESOLUTION_ENHANCE1_W_POS)
#define DSP2_MIDDLE_RESOLUTION_ENHANCE1_W_UMSK                   (~(((1U<<DSP2_MIDDLE_RESOLUTION_ENHANCE1_W_LEN)-1)<<DSP2_MIDDLE_RESOLUTION_ENHANCE1_W_POS))
#define DSP2_MIDDLE_RESOLUTION_ENHANCE2_W                        DSP2_MIDDLE_RESOLUTION_ENHANCE2_W
#define DSP2_MIDDLE_RESOLUTION_ENHANCE2_W_POS                    (9U)
#define DSP2_MIDDLE_RESOLUTION_ENHANCE2_W_LEN                    (1U)
#define DSP2_MIDDLE_RESOLUTION_ENHANCE2_W_MSK                    (((1U<<DSP2_MIDDLE_RESOLUTION_ENHANCE2_W_LEN)-1)<<DSP2_MIDDLE_RESOLUTION_ENHANCE2_W_POS)
#define DSP2_MIDDLE_RESOLUTION_ENHANCE2_W_UMSK                   (~(((1U<<DSP2_MIDDLE_RESOLUTION_ENHANCE2_W_LEN)-1)<<DSP2_MIDDLE_RESOLUTION_ENHANCE2_W_POS))
#define DSP2_MIDDLE_RESOLUTION_ENHANCE3_W                        DSP2_MIDDLE_RESOLUTION_ENHANCE3_W
#define DSP2_MIDDLE_RESOLUTION_ENHANCE3_W_POS                    (10U)
#define DSP2_MIDDLE_RESOLUTION_ENHANCE3_W_LEN                    (1U)
#define DSP2_MIDDLE_RESOLUTION_ENHANCE3_W_MSK                    (((1U<<DSP2_MIDDLE_RESOLUTION_ENHANCE3_W_LEN)-1)<<DSP2_MIDDLE_RESOLUTION_ENHANCE3_W_POS)
#define DSP2_MIDDLE_RESOLUTION_ENHANCE3_W_UMSK                   (~(((1U<<DSP2_MIDDLE_RESOLUTION_ENHANCE3_W_LEN)-1)<<DSP2_MIDDLE_RESOLUTION_ENHANCE3_W_POS))
#define DSP2_MIDDLE_DEFECT_ADDRESS_W                             DSP2_MIDDLE_DEFECT_ADDRESS_W
#define DSP2_MIDDLE_DEFECT_ADDRESS_W_POS                         (16U)
#define DSP2_MIDDLE_DEFECT_ADDRESS_W_LEN                         (8U)
#define DSP2_MIDDLE_DEFECT_ADDRESS_W_MSK                         (((1U<<DSP2_MIDDLE_DEFECT_ADDRESS_W_LEN)-1)<<DSP2_MIDDLE_DEFECT_ADDRESS_W_POS)
#define DSP2_MIDDLE_DEFECT_ADDRESS_W_UMSK                        (~(((1U<<DSP2_MIDDLE_DEFECT_ADDRESS_W_LEN)-1)<<DSP2_MIDDLE_DEFECT_ADDRESS_W_POS))

/* 0x264 : defect_position */
#define DSP2_MIDDLE_DEFECT_POSITION_OFFSET                       (0x264)
#define DSP2_MIDDLE_X_POSITION_W                                 DSP2_MIDDLE_X_POSITION_W
#define DSP2_MIDDLE_X_POSITION_W_POS                             (0U)
#define DSP2_MIDDLE_X_POSITION_W_LEN                             (16U)
#define DSP2_MIDDLE_X_POSITION_W_MSK                             (((1U<<DSP2_MIDDLE_X_POSITION_W_LEN)-1)<<DSP2_MIDDLE_X_POSITION_W_POS)
#define DSP2_MIDDLE_X_POSITION_W_UMSK                            (~(((1U<<DSP2_MIDDLE_X_POSITION_W_LEN)-1)<<DSP2_MIDDLE_X_POSITION_W_POS))
#define DSP2_MIDDLE_Y_POSITION_W                                 DSP2_MIDDLE_Y_POSITION_W
#define DSP2_MIDDLE_Y_POSITION_W_POS                             (16U)
#define DSP2_MIDDLE_Y_POSITION_W_LEN                             (16U)
#define DSP2_MIDDLE_Y_POSITION_W_MSK                             (((1U<<DSP2_MIDDLE_Y_POSITION_W_LEN)-1)<<DSP2_MIDDLE_Y_POSITION_W_POS)
#define DSP2_MIDDLE_Y_POSITION_W_UMSK                            (~(((1U<<DSP2_MIDDLE_Y_POSITION_W_LEN)-1)<<DSP2_MIDDLE_Y_POSITION_W_POS))

/* 0x268 : defect_th_A */
#define DSP2_MIDDLE_DEFECT_TH_A_OFFSET                           (0x268)
#define DSP2_MIDDLE_DEFECT_TH1_W                                 DSP2_MIDDLE_DEFECT_TH1_W
#define DSP2_MIDDLE_DEFECT_TH1_W_POS                             (0U)
#define DSP2_MIDDLE_DEFECT_TH1_W_LEN                             (8U)
#define DSP2_MIDDLE_DEFECT_TH1_W_MSK                             (((1U<<DSP2_MIDDLE_DEFECT_TH1_W_LEN)-1)<<DSP2_MIDDLE_DEFECT_TH1_W_POS)
#define DSP2_MIDDLE_DEFECT_TH1_W_UMSK                            (~(((1U<<DSP2_MIDDLE_DEFECT_TH1_W_LEN)-1)<<DSP2_MIDDLE_DEFECT_TH1_W_POS))
#define DSP2_MIDDLE_DEFECT_TH2_W                                 DSP2_MIDDLE_DEFECT_TH2_W
#define DSP2_MIDDLE_DEFECT_TH2_W_POS                             (8U)
#define DSP2_MIDDLE_DEFECT_TH2_W_LEN                             (8U)
#define DSP2_MIDDLE_DEFECT_TH2_W_MSK                             (((1U<<DSP2_MIDDLE_DEFECT_TH2_W_LEN)-1)<<DSP2_MIDDLE_DEFECT_TH2_W_POS)
#define DSP2_MIDDLE_DEFECT_TH2_W_UMSK                            (~(((1U<<DSP2_MIDDLE_DEFECT_TH2_W_LEN)-1)<<DSP2_MIDDLE_DEFECT_TH2_W_POS))
#define DSP2_MIDDLE_DEFECT_TH3_W                                 DSP2_MIDDLE_DEFECT_TH3_W
#define DSP2_MIDDLE_DEFECT_TH3_W_POS                             (16U)
#define DSP2_MIDDLE_DEFECT_TH3_W_LEN                             (8U)
#define DSP2_MIDDLE_DEFECT_TH3_W_MSK                             (((1U<<DSP2_MIDDLE_DEFECT_TH3_W_LEN)-1)<<DSP2_MIDDLE_DEFECT_TH3_W_POS)
#define DSP2_MIDDLE_DEFECT_TH3_W_UMSK                            (~(((1U<<DSP2_MIDDLE_DEFECT_TH3_W_LEN)-1)<<DSP2_MIDDLE_DEFECT_TH3_W_POS))
#define DSP2_MIDDLE_DEFECT_TH4_W                                 DSP2_MIDDLE_DEFECT_TH4_W
#define DSP2_MIDDLE_DEFECT_TH4_W_POS                             (24U)
#define DSP2_MIDDLE_DEFECT_TH4_W_LEN                             (8U)
#define DSP2_MIDDLE_DEFECT_TH4_W_MSK                             (((1U<<DSP2_MIDDLE_DEFECT_TH4_W_LEN)-1)<<DSP2_MIDDLE_DEFECT_TH4_W_POS)
#define DSP2_MIDDLE_DEFECT_TH4_W_UMSK                            (~(((1U<<DSP2_MIDDLE_DEFECT_TH4_W_LEN)-1)<<DSP2_MIDDLE_DEFECT_TH4_W_POS))

/* 0x26C : defect_th_B */
#define DSP2_MIDDLE_DEFECT_TH_B_OFFSET                           (0x26C)
#define DSP2_MIDDLE_DEFECT_TH5_W                                 DSP2_MIDDLE_DEFECT_TH5_W
#define DSP2_MIDDLE_DEFECT_TH5_W_POS                             (0U)
#define DSP2_MIDDLE_DEFECT_TH5_W_LEN                             (8U)
#define DSP2_MIDDLE_DEFECT_TH5_W_MSK                             (((1U<<DSP2_MIDDLE_DEFECT_TH5_W_LEN)-1)<<DSP2_MIDDLE_DEFECT_TH5_W_POS)
#define DSP2_MIDDLE_DEFECT_TH5_W_UMSK                            (~(((1U<<DSP2_MIDDLE_DEFECT_TH5_W_LEN)-1)<<DSP2_MIDDLE_DEFECT_TH5_W_POS))

/* 0x270 : awb_setting */
#define DSP2_MIDDLE_AWB_SETTING_OFFSET                           (0x270)
#define DSP2_MIDDLE_AWB_SWITCH_BANK_EN_W                         DSP2_MIDDLE_AWB_SWITCH_BANK_EN_W
#define DSP2_MIDDLE_AWB_SWITCH_BANK_EN_W_POS                     (0U)
#define DSP2_MIDDLE_AWB_SWITCH_BANK_EN_W_LEN                     (1U)
#define DSP2_MIDDLE_AWB_SWITCH_BANK_EN_W_MSK                     (((1U<<DSP2_MIDDLE_AWB_SWITCH_BANK_EN_W_LEN)-1)<<DSP2_MIDDLE_AWB_SWITCH_BANK_EN_W_POS)
#define DSP2_MIDDLE_AWB_SWITCH_BANK_EN_W_UMSK                    (~(((1U<<DSP2_MIDDLE_AWB_SWITCH_BANK_EN_W_LEN)-1)<<DSP2_MIDDLE_AWB_SWITCH_BANK_EN_W_POS))
#define DSP2_MIDDLE_NEW_AWB_STA_ENABLE_W                         DSP2_MIDDLE_NEW_AWB_STA_ENABLE_W
#define DSP2_MIDDLE_NEW_AWB_STA_ENABLE_W_POS                     (1U)
#define DSP2_MIDDLE_NEW_AWB_STA_ENABLE_W_LEN                     (1U)
#define DSP2_MIDDLE_NEW_AWB_STA_ENABLE_W_MSK                     (((1U<<DSP2_MIDDLE_NEW_AWB_STA_ENABLE_W_LEN)-1)<<DSP2_MIDDLE_NEW_AWB_STA_ENABLE_W_POS)
#define DSP2_MIDDLE_NEW_AWB_STA_ENABLE_W_UMSK                    (~(((1U<<DSP2_MIDDLE_NEW_AWB_STA_ENABLE_W_LEN)-1)<<DSP2_MIDDLE_NEW_AWB_STA_ENABLE_W_POS))
#define DSP2_MIDDLE_BL_AWB_GAIN_SEL_W                            DSP2_MIDDLE_BL_AWB_GAIN_SEL_W
#define DSP2_MIDDLE_BL_AWB_GAIN_SEL_W_POS                        (2U)
#define DSP2_MIDDLE_BL_AWB_GAIN_SEL_W_LEN                        (1U)
#define DSP2_MIDDLE_BL_AWB_GAIN_SEL_W_MSK                        (((1U<<DSP2_MIDDLE_BL_AWB_GAIN_SEL_W_LEN)-1)<<DSP2_MIDDLE_BL_AWB_GAIN_SEL_W_POS)
#define DSP2_MIDDLE_BL_AWB_GAIN_SEL_W_UMSK                       (~(((1U<<DSP2_MIDDLE_BL_AWB_GAIN_SEL_W_LEN)-1)<<DSP2_MIDDLE_BL_AWB_GAIN_SEL_W_POS))
#define DSP2_MIDDLE_GRID_CNT_WITHIN_THRE_R                       DSP2_MIDDLE_GRID_CNT_WITHIN_THRE_R
#define DSP2_MIDDLE_GRID_CNT_WITHIN_THRE_R_POS                   (16U)
#define DSP2_MIDDLE_GRID_CNT_WITHIN_THRE_R_LEN                   (11U)
#define DSP2_MIDDLE_GRID_CNT_WITHIN_THRE_R_MSK                   (((1U<<DSP2_MIDDLE_GRID_CNT_WITHIN_THRE_R_LEN)-1)<<DSP2_MIDDLE_GRID_CNT_WITHIN_THRE_R_POS)
#define DSP2_MIDDLE_GRID_CNT_WITHIN_THRE_R_UMSK                  (~(((1U<<DSP2_MIDDLE_GRID_CNT_WITHIN_THRE_R_LEN)-1)<<DSP2_MIDDLE_GRID_CNT_WITHIN_THRE_R_POS))

/* 0x274 : awb_roi_x */
#define DSP2_MIDDLE_AWB_ROI_X_OFFSET                             (0x274)
#define DSP2_MIDDLE_AWB_ROI_START_X_W                            DSP2_MIDDLE_AWB_ROI_START_X_W
#define DSP2_MIDDLE_AWB_ROI_START_X_W_POS                        (0U)
#define DSP2_MIDDLE_AWB_ROI_START_X_W_LEN                        (11U)
#define DSP2_MIDDLE_AWB_ROI_START_X_W_MSK                        (((1U<<DSP2_MIDDLE_AWB_ROI_START_X_W_LEN)-1)<<DSP2_MIDDLE_AWB_ROI_START_X_W_POS)
#define DSP2_MIDDLE_AWB_ROI_START_X_W_UMSK                       (~(((1U<<DSP2_MIDDLE_AWB_ROI_START_X_W_LEN)-1)<<DSP2_MIDDLE_AWB_ROI_START_X_W_POS))
#define DSP2_MIDDLE_AWB_ROI_WIDTH_W                              DSP2_MIDDLE_AWB_ROI_WIDTH_W
#define DSP2_MIDDLE_AWB_ROI_WIDTH_W_POS                          (16U)
#define DSP2_MIDDLE_AWB_ROI_WIDTH_W_LEN                          (11U)
#define DSP2_MIDDLE_AWB_ROI_WIDTH_W_MSK                          (((1U<<DSP2_MIDDLE_AWB_ROI_WIDTH_W_LEN)-1)<<DSP2_MIDDLE_AWB_ROI_WIDTH_W_POS)
#define DSP2_MIDDLE_AWB_ROI_WIDTH_W_UMSK                         (~(((1U<<DSP2_MIDDLE_AWB_ROI_WIDTH_W_LEN)-1)<<DSP2_MIDDLE_AWB_ROI_WIDTH_W_POS))

/* 0x278 : awb_roi_y */
#define DSP2_MIDDLE_AWB_ROI_Y_OFFSET                             (0x278)
#define DSP2_MIDDLE_AWB_ROI_START_Y_W                            DSP2_MIDDLE_AWB_ROI_START_Y_W
#define DSP2_MIDDLE_AWB_ROI_START_Y_W_POS                        (0U)
#define DSP2_MIDDLE_AWB_ROI_START_Y_W_LEN                        (11U)
#define DSP2_MIDDLE_AWB_ROI_START_Y_W_MSK                        (((1U<<DSP2_MIDDLE_AWB_ROI_START_Y_W_LEN)-1)<<DSP2_MIDDLE_AWB_ROI_START_Y_W_POS)
#define DSP2_MIDDLE_AWB_ROI_START_Y_W_UMSK                       (~(((1U<<DSP2_MIDDLE_AWB_ROI_START_Y_W_LEN)-1)<<DSP2_MIDDLE_AWB_ROI_START_Y_W_POS))
#define DSP2_MIDDLE_AWB_ROI_HEIGHT_W                             DSP2_MIDDLE_AWB_ROI_HEIGHT_W
#define DSP2_MIDDLE_AWB_ROI_HEIGHT_W_POS                         (16U)
#define DSP2_MIDDLE_AWB_ROI_HEIGHT_W_LEN                         (11U)
#define DSP2_MIDDLE_AWB_ROI_HEIGHT_W_MSK                         (((1U<<DSP2_MIDDLE_AWB_ROI_HEIGHT_W_LEN)-1)<<DSP2_MIDDLE_AWB_ROI_HEIGHT_W_POS)
#define DSP2_MIDDLE_AWB_ROI_HEIGHT_W_UMSK                        (~(((1U<<DSP2_MIDDLE_AWB_ROI_HEIGHT_W_LEN)-1)<<DSP2_MIDDLE_AWB_ROI_HEIGHT_W_POS))

/* 0x27C : awb_image_size */
#define DSP2_MIDDLE_AWB_IMAGE_SIZE_OFFSET                        (0x27C)
#define DSP2_MIDDLE_AWB_IMAGE_WIDTH_W                            DSP2_MIDDLE_AWB_IMAGE_WIDTH_W
#define DSP2_MIDDLE_AWB_IMAGE_WIDTH_W_POS                        (0U)
#define DSP2_MIDDLE_AWB_IMAGE_WIDTH_W_LEN                        (11U)
#define DSP2_MIDDLE_AWB_IMAGE_WIDTH_W_MSK                        (((1U<<DSP2_MIDDLE_AWB_IMAGE_WIDTH_W_LEN)-1)<<DSP2_MIDDLE_AWB_IMAGE_WIDTH_W_POS)
#define DSP2_MIDDLE_AWB_IMAGE_WIDTH_W_UMSK                       (~(((1U<<DSP2_MIDDLE_AWB_IMAGE_WIDTH_W_LEN)-1)<<DSP2_MIDDLE_AWB_IMAGE_WIDTH_W_POS))
#define DSP2_MIDDLE_AWB_IMAGE_HEIGHT_W                           DSP2_MIDDLE_AWB_IMAGE_HEIGHT_W
#define DSP2_MIDDLE_AWB_IMAGE_HEIGHT_W_POS                       (16U)
#define DSP2_MIDDLE_AWB_IMAGE_HEIGHT_W_LEN                       (11U)
#define DSP2_MIDDLE_AWB_IMAGE_HEIGHT_W_MSK                       (((1U<<DSP2_MIDDLE_AWB_IMAGE_HEIGHT_W_LEN)-1)<<DSP2_MIDDLE_AWB_IMAGE_HEIGHT_W_POS)
#define DSP2_MIDDLE_AWB_IMAGE_HEIGHT_W_UMSK                      (~(((1U<<DSP2_MIDDLE_AWB_IMAGE_HEIGHT_W_LEN)-1)<<DSP2_MIDDLE_AWB_IMAGE_HEIGHT_W_POS))

/* 0x280 : awb_grid_size */
#define DSP2_MIDDLE_AWB_GRID_SIZE_OFFSET                         (0x280)
#define DSP2_MIDDLE_AWB_GRID_WIDTH_W                             DSP2_MIDDLE_AWB_GRID_WIDTH_W
#define DSP2_MIDDLE_AWB_GRID_WIDTH_W_POS                         (0U)
#define DSP2_MIDDLE_AWB_GRID_WIDTH_W_LEN                         (8U)
#define DSP2_MIDDLE_AWB_GRID_WIDTH_W_MSK                         (((1U<<DSP2_MIDDLE_AWB_GRID_WIDTH_W_LEN)-1)<<DSP2_MIDDLE_AWB_GRID_WIDTH_W_POS)
#define DSP2_MIDDLE_AWB_GRID_WIDTH_W_UMSK                        (~(((1U<<DSP2_MIDDLE_AWB_GRID_WIDTH_W_LEN)-1)<<DSP2_MIDDLE_AWB_GRID_WIDTH_W_POS))
#define DSP2_MIDDLE_AWB_GRID_HEIGHT_W                            DSP2_MIDDLE_AWB_GRID_HEIGHT_W
#define DSP2_MIDDLE_AWB_GRID_HEIGHT_W_POS                        (8U)
#define DSP2_MIDDLE_AWB_GRID_HEIGHT_W_LEN                        (8U)
#define DSP2_MIDDLE_AWB_GRID_HEIGHT_W_MSK                        (((1U<<DSP2_MIDDLE_AWB_GRID_HEIGHT_W_LEN)-1)<<DSP2_MIDDLE_AWB_GRID_HEIGHT_W_POS)
#define DSP2_MIDDLE_AWB_GRID_HEIGHT_W_UMSK                       (~(((1U<<DSP2_MIDDLE_AWB_GRID_HEIGHT_W_LEN)-1)<<DSP2_MIDDLE_AWB_GRID_HEIGHT_W_POS))
#define DSP2_MIDDLE_AWB_GRID_X_MAX_W                             DSP2_MIDDLE_AWB_GRID_X_MAX_W
#define DSP2_MIDDLE_AWB_GRID_X_MAX_W_POS                         (16U)
#define DSP2_MIDDLE_AWB_GRID_X_MAX_W_LEN                         (6U)
#define DSP2_MIDDLE_AWB_GRID_X_MAX_W_MSK                         (((1U<<DSP2_MIDDLE_AWB_GRID_X_MAX_W_LEN)-1)<<DSP2_MIDDLE_AWB_GRID_X_MAX_W_POS)
#define DSP2_MIDDLE_AWB_GRID_X_MAX_W_UMSK                        (~(((1U<<DSP2_MIDDLE_AWB_GRID_X_MAX_W_LEN)-1)<<DSP2_MIDDLE_AWB_GRID_X_MAX_W_POS))
#define DSP2_MIDDLE_AWB_GRID_Y_MAX_W                             DSP2_MIDDLE_AWB_GRID_Y_MAX_W
#define DSP2_MIDDLE_AWB_GRID_Y_MAX_W_POS                         (24U)
#define DSP2_MIDDLE_AWB_GRID_Y_MAX_W_LEN                         (6U)
#define DSP2_MIDDLE_AWB_GRID_Y_MAX_W_MSK                         (((1U<<DSP2_MIDDLE_AWB_GRID_Y_MAX_W_LEN)-1)<<DSP2_MIDDLE_AWB_GRID_Y_MAX_W_POS)
#define DSP2_MIDDLE_AWB_GRID_Y_MAX_W_UMSK                        (~(((1U<<DSP2_MIDDLE_AWB_GRID_Y_MAX_W_LEN)-1)<<DSP2_MIDDLE_AWB_GRID_Y_MAX_W_POS))

/* 0x284 : awb_r_thre */
#define DSP2_MIDDLE_AWB_R_THRE_OFFSET                            (0x284)
#define DSP2_MIDDLE_AWB_R_MAX_THR_W                              DSP2_MIDDLE_AWB_R_MAX_THR_W
#define DSP2_MIDDLE_AWB_R_MAX_THR_W_POS                          (0U)
#define DSP2_MIDDLE_AWB_R_MAX_THR_W_LEN                          (12U)
#define DSP2_MIDDLE_AWB_R_MAX_THR_W_MSK                          (((1U<<DSP2_MIDDLE_AWB_R_MAX_THR_W_LEN)-1)<<DSP2_MIDDLE_AWB_R_MAX_THR_W_POS)
#define DSP2_MIDDLE_AWB_R_MAX_THR_W_UMSK                         (~(((1U<<DSP2_MIDDLE_AWB_R_MAX_THR_W_LEN)-1)<<DSP2_MIDDLE_AWB_R_MAX_THR_W_POS))
#define DSP2_MIDDLE_AWB_R_MIN_THR_W                              DSP2_MIDDLE_AWB_R_MIN_THR_W
#define DSP2_MIDDLE_AWB_R_MIN_THR_W_POS                          (16U)
#define DSP2_MIDDLE_AWB_R_MIN_THR_W_LEN                          (12U)
#define DSP2_MIDDLE_AWB_R_MIN_THR_W_MSK                          (((1U<<DSP2_MIDDLE_AWB_R_MIN_THR_W_LEN)-1)<<DSP2_MIDDLE_AWB_R_MIN_THR_W_POS)
#define DSP2_MIDDLE_AWB_R_MIN_THR_W_UMSK                         (~(((1U<<DSP2_MIDDLE_AWB_R_MIN_THR_W_LEN)-1)<<DSP2_MIDDLE_AWB_R_MIN_THR_W_POS))

/* 0x288 : awb_g_thre */
#define DSP2_MIDDLE_AWB_G_THRE_OFFSET                            (0x288)
#define DSP2_MIDDLE_AWB_G_MAX_THR_W                              DSP2_MIDDLE_AWB_G_MAX_THR_W
#define DSP2_MIDDLE_AWB_G_MAX_THR_W_POS                          (0U)
#define DSP2_MIDDLE_AWB_G_MAX_THR_W_LEN                          (12U)
#define DSP2_MIDDLE_AWB_G_MAX_THR_W_MSK                          (((1U<<DSP2_MIDDLE_AWB_G_MAX_THR_W_LEN)-1)<<DSP2_MIDDLE_AWB_G_MAX_THR_W_POS)
#define DSP2_MIDDLE_AWB_G_MAX_THR_W_UMSK                         (~(((1U<<DSP2_MIDDLE_AWB_G_MAX_THR_W_LEN)-1)<<DSP2_MIDDLE_AWB_G_MAX_THR_W_POS))
#define DSP2_MIDDLE_AWB_G_MIN_THR_W                              DSP2_MIDDLE_AWB_G_MIN_THR_W
#define DSP2_MIDDLE_AWB_G_MIN_THR_W_POS                          (16U)
#define DSP2_MIDDLE_AWB_G_MIN_THR_W_LEN                          (12U)
#define DSP2_MIDDLE_AWB_G_MIN_THR_W_MSK                          (((1U<<DSP2_MIDDLE_AWB_G_MIN_THR_W_LEN)-1)<<DSP2_MIDDLE_AWB_G_MIN_THR_W_POS)
#define DSP2_MIDDLE_AWB_G_MIN_THR_W_UMSK                         (~(((1U<<DSP2_MIDDLE_AWB_G_MIN_THR_W_LEN)-1)<<DSP2_MIDDLE_AWB_G_MIN_THR_W_POS))

/* 0x28C : awb_b_thre */
#define DSP2_MIDDLE_AWB_B_THRE_OFFSET                            (0x28C)
#define DSP2_MIDDLE_AWB_B_MAX_THR_W                              DSP2_MIDDLE_AWB_B_MAX_THR_W
#define DSP2_MIDDLE_AWB_B_MAX_THR_W_POS                          (0U)
#define DSP2_MIDDLE_AWB_B_MAX_THR_W_LEN                          (12U)
#define DSP2_MIDDLE_AWB_B_MAX_THR_W_MSK                          (((1U<<DSP2_MIDDLE_AWB_B_MAX_THR_W_LEN)-1)<<DSP2_MIDDLE_AWB_B_MAX_THR_W_POS)
#define DSP2_MIDDLE_AWB_B_MAX_THR_W_UMSK                         (~(((1U<<DSP2_MIDDLE_AWB_B_MAX_THR_W_LEN)-1)<<DSP2_MIDDLE_AWB_B_MAX_THR_W_POS))
#define DSP2_MIDDLE_AWB_B_MIN_THR_W                              DSP2_MIDDLE_AWB_B_MIN_THR_W
#define DSP2_MIDDLE_AWB_B_MIN_THR_W_POS                          (16U)
#define DSP2_MIDDLE_AWB_B_MIN_THR_W_LEN                          (12U)
#define DSP2_MIDDLE_AWB_B_MIN_THR_W_MSK                          (((1U<<DSP2_MIDDLE_AWB_B_MIN_THR_W_LEN)-1)<<DSP2_MIDDLE_AWB_B_MIN_THR_W_POS)
#define DSP2_MIDDLE_AWB_B_MIN_THR_W_UMSK                         (~(((1U<<DSP2_MIDDLE_AWB_B_MIN_THR_W_LEN)-1)<<DSP2_MIDDLE_AWB_B_MIN_THR_W_POS))

/* 0x290 : awb_rgr_gain */
#define DSP2_MIDDLE_AWB_RGR_GAIN_OFFSET                          (0x290)
#define DSP2_MIDDLE_AWB_GR_GAIN_PRE                              DSP2_MIDDLE_AWB_GR_GAIN_PRE
#define DSP2_MIDDLE_AWB_GR_GAIN_PRE_POS                          (0U)
#define DSP2_MIDDLE_AWB_GR_GAIN_PRE_LEN                          (15U)
#define DSP2_MIDDLE_AWB_GR_GAIN_PRE_MSK                          (((1U<<DSP2_MIDDLE_AWB_GR_GAIN_PRE_LEN)-1)<<DSP2_MIDDLE_AWB_GR_GAIN_PRE_POS)
#define DSP2_MIDDLE_AWB_GR_GAIN_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE_AWB_GR_GAIN_PRE_LEN)-1)<<DSP2_MIDDLE_AWB_GR_GAIN_PRE_POS))
#define DSP2_MIDDLE_AWB_R_GAIN_PRE                               DSP2_MIDDLE_AWB_R_GAIN_PRE
#define DSP2_MIDDLE_AWB_R_GAIN_PRE_POS                           (16U)
#define DSP2_MIDDLE_AWB_R_GAIN_PRE_LEN                           (15U)
#define DSP2_MIDDLE_AWB_R_GAIN_PRE_MSK                           (((1U<<DSP2_MIDDLE_AWB_R_GAIN_PRE_LEN)-1)<<DSP2_MIDDLE_AWB_R_GAIN_PRE_POS)
#define DSP2_MIDDLE_AWB_R_GAIN_PRE_UMSK                          (~(((1U<<DSP2_MIDDLE_AWB_R_GAIN_PRE_LEN)-1)<<DSP2_MIDDLE_AWB_R_GAIN_PRE_POS))

/* 0x294 : awb_bgb_gain */
#define DSP2_MIDDLE_AWB_BGB_GAIN_OFFSET                          (0x294)
#define DSP2_MIDDLE_AWB_GB_GAIN_PRE                              DSP2_MIDDLE_AWB_GB_GAIN_PRE
#define DSP2_MIDDLE_AWB_GB_GAIN_PRE_POS                          (0U)
#define DSP2_MIDDLE_AWB_GB_GAIN_PRE_LEN                          (15U)
#define DSP2_MIDDLE_AWB_GB_GAIN_PRE_MSK                          (((1U<<DSP2_MIDDLE_AWB_GB_GAIN_PRE_LEN)-1)<<DSP2_MIDDLE_AWB_GB_GAIN_PRE_POS)
#define DSP2_MIDDLE_AWB_GB_GAIN_PRE_UMSK                         (~(((1U<<DSP2_MIDDLE_AWB_GB_GAIN_PRE_LEN)-1)<<DSP2_MIDDLE_AWB_GB_GAIN_PRE_POS))
#define DSP2_MIDDLE_AWB_B_GAIN_PRE                               DSP2_MIDDLE_AWB_B_GAIN_PRE
#define DSP2_MIDDLE_AWB_B_GAIN_PRE_POS                           (16U)
#define DSP2_MIDDLE_AWB_B_GAIN_PRE_LEN                           (15U)
#define DSP2_MIDDLE_AWB_B_GAIN_PRE_MSK                           (((1U<<DSP2_MIDDLE_AWB_B_GAIN_PRE_LEN)-1)<<DSP2_MIDDLE_AWB_B_GAIN_PRE_POS)
#define DSP2_MIDDLE_AWB_B_GAIN_PRE_UMSK                          (~(((1U<<DSP2_MIDDLE_AWB_B_GAIN_PRE_LEN)-1)<<DSP2_MIDDLE_AWB_B_GAIN_PRE_POS))

/* 0x2A0 : cfa_int_1 */
#define DSP2_MIDDLE_CFA_INT_1_OFFSET                             (0x2A0)
#define DSP2_MIDDLE_REG_CFA_FRINGE_ON_W                          DSP2_MIDDLE_REG_CFA_FRINGE_ON_W
#define DSP2_MIDDLE_REG_CFA_FRINGE_ON_W_POS                      (0U)
#define DSP2_MIDDLE_REG_CFA_FRINGE_ON_W_LEN                      (1U)
#define DSP2_MIDDLE_REG_CFA_FRINGE_ON_W_MSK                      (((1U<<DSP2_MIDDLE_REG_CFA_FRINGE_ON_W_LEN)-1)<<DSP2_MIDDLE_REG_CFA_FRINGE_ON_W_POS)
#define DSP2_MIDDLE_REG_CFA_FRINGE_ON_W_UMSK                     (~(((1U<<DSP2_MIDDLE_REG_CFA_FRINGE_ON_W_LEN)-1)<<DSP2_MIDDLE_REG_CFA_FRINGE_ON_W_POS))

/* 0x2F4 : awb_sta_dbg1 */
#define DSP2_MIDDLE_AWB_STA_DBG1_OFFSET                          (0x2F4)
#define DSP2_MIDDLE_AWB_GRID_CNT_MAX                             DSP2_MIDDLE_AWB_GRID_CNT_MAX
#define DSP2_MIDDLE_AWB_GRID_CNT_MAX_POS                         (0U)
#define DSP2_MIDDLE_AWB_GRID_CNT_MAX_LEN                         (11U)
#define DSP2_MIDDLE_AWB_GRID_CNT_MAX_MSK                         (((1U<<DSP2_MIDDLE_AWB_GRID_CNT_MAX_LEN)-1)<<DSP2_MIDDLE_AWB_GRID_CNT_MAX_POS)
#define DSP2_MIDDLE_AWB_GRID_CNT_MAX_UMSK                        (~(((1U<<DSP2_MIDDLE_AWB_GRID_CNT_MAX_LEN)-1)<<DSP2_MIDDLE_AWB_GRID_CNT_MAX_POS))
#define DSP2_MIDDLE_AWB_FIFO_FULL                                DSP2_MIDDLE_AWB_FIFO_FULL
#define DSP2_MIDDLE_AWB_FIFO_FULL_POS                            (12U)
#define DSP2_MIDDLE_AWB_FIFO_FULL_LEN                            (1U)
#define DSP2_MIDDLE_AWB_FIFO_FULL_MSK                            (((1U<<DSP2_MIDDLE_AWB_FIFO_FULL_LEN)-1)<<DSP2_MIDDLE_AWB_FIFO_FULL_POS)
#define DSP2_MIDDLE_AWB_FIFO_FULL_UMSK                           (~(((1U<<DSP2_MIDDLE_AWB_FIFO_FULL_LEN)-1)<<DSP2_MIDDLE_AWB_FIFO_FULL_POS))
#define DSP2_MIDDLE_AWB_CONTROL_STATUS                           DSP2_MIDDLE_AWB_CONTROL_STATUS
#define DSP2_MIDDLE_AWB_CONTROL_STATUS_POS                       (16U)
#define DSP2_MIDDLE_AWB_CONTROL_STATUS_LEN                       (4U)
#define DSP2_MIDDLE_AWB_CONTROL_STATUS_MSK                       (((1U<<DSP2_MIDDLE_AWB_CONTROL_STATUS_LEN)-1)<<DSP2_MIDDLE_AWB_CONTROL_STATUS_POS)
#define DSP2_MIDDLE_AWB_CONTROL_STATUS_UMSK                      (~(((1U<<DSP2_MIDDLE_AWB_CONTROL_STATUS_LEN)-1)<<DSP2_MIDDLE_AWB_CONTROL_STATUS_POS))
#define DSP2_MIDDLE_AWB_OPERATION_DONE                           DSP2_MIDDLE_AWB_OPERATION_DONE
#define DSP2_MIDDLE_AWB_OPERATION_DONE_POS                       (20U)
#define DSP2_MIDDLE_AWB_OPERATION_DONE_LEN                       (1U)
#define DSP2_MIDDLE_AWB_OPERATION_DONE_MSK                       (((1U<<DSP2_MIDDLE_AWB_OPERATION_DONE_LEN)-1)<<DSP2_MIDDLE_AWB_OPERATION_DONE_POS)
#define DSP2_MIDDLE_AWB_OPERATION_DONE_UMSK                      (~(((1U<<DSP2_MIDDLE_AWB_OPERATION_DONE_LEN)-1)<<DSP2_MIDDLE_AWB_OPERATION_DONE_POS))
#define DSP2_MIDDLE_AWB_FIFO_EMPTY                               DSP2_MIDDLE_AWB_FIFO_EMPTY
#define DSP2_MIDDLE_AWB_FIFO_EMPTY_POS                           (21U)
#define DSP2_MIDDLE_AWB_FIFO_EMPTY_LEN                           (1U)
#define DSP2_MIDDLE_AWB_FIFO_EMPTY_MSK                           (((1U<<DSP2_MIDDLE_AWB_FIFO_EMPTY_LEN)-1)<<DSP2_MIDDLE_AWB_FIFO_EMPTY_POS)
#define DSP2_MIDDLE_AWB_FIFO_EMPTY_UMSK                          (~(((1U<<DSP2_MIDDLE_AWB_FIFO_EMPTY_LEN)-1)<<DSP2_MIDDLE_AWB_FIFO_EMPTY_POS))
#define DSP2_MIDDLE_BLAWB_W_CNT_R                                DSP2_MIDDLE_BLAWB_W_CNT_R
#define DSP2_MIDDLE_BLAWB_W_CNT_R_POS                            (24U)
#define DSP2_MIDDLE_BLAWB_W_CNT_R_LEN                            (5U)
#define DSP2_MIDDLE_BLAWB_W_CNT_R_MSK                            (((1U<<DSP2_MIDDLE_BLAWB_W_CNT_R_LEN)-1)<<DSP2_MIDDLE_BLAWB_W_CNT_R_POS)
#define DSP2_MIDDLE_BLAWB_W_CNT_R_UMSK                           (~(((1U<<DSP2_MIDDLE_BLAWB_W_CNT_R_LEN)-1)<<DSP2_MIDDLE_BLAWB_W_CNT_R_POS))
#define DSP2_MIDDLE_BLAWB_BUF_IDX_R                              DSP2_MIDDLE_BLAWB_BUF_IDX_R
#define DSP2_MIDDLE_BLAWB_BUF_IDX_R_POS                          (31U)
#define DSP2_MIDDLE_BLAWB_BUF_IDX_R_LEN                          (1U)
#define DSP2_MIDDLE_BLAWB_BUF_IDX_R_MSK                          (((1U<<DSP2_MIDDLE_BLAWB_BUF_IDX_R_LEN)-1)<<DSP2_MIDDLE_BLAWB_BUF_IDX_R_POS)
#define DSP2_MIDDLE_BLAWB_BUF_IDX_R_UMSK                         (~(((1U<<DSP2_MIDDLE_BLAWB_BUF_IDX_R_LEN)-1)<<DSP2_MIDDLE_BLAWB_BUF_IDX_R_POS))

/* 0x2F8 : awb_sta_dbg0 */
#define DSP2_MIDDLE_AWB_STA_DBG0_OFFSET                          (0x2F8)
#define DSP2_MIDDLE_AWB_GRID_CNT                                 DSP2_MIDDLE_AWB_GRID_CNT
#define DSP2_MIDDLE_AWB_GRID_CNT_POS                             (0U)
#define DSP2_MIDDLE_AWB_GRID_CNT_LEN                             (10U)
#define DSP2_MIDDLE_AWB_GRID_CNT_MSK                             (((1U<<DSP2_MIDDLE_AWB_GRID_CNT_LEN)-1)<<DSP2_MIDDLE_AWB_GRID_CNT_POS)
#define DSP2_MIDDLE_AWB_GRID_CNT_UMSK                            (~(((1U<<DSP2_MIDDLE_AWB_GRID_CNT_LEN)-1)<<DSP2_MIDDLE_AWB_GRID_CNT_POS))
#define DSP2_MIDDLE_AWB_STA_DONE                                 DSP2_MIDDLE_AWB_STA_DONE
#define DSP2_MIDDLE_AWB_STA_DONE_POS                             (12U)
#define DSP2_MIDDLE_AWB_STA_DONE_LEN                             (1U)
#define DSP2_MIDDLE_AWB_STA_DONE_MSK                             (((1U<<DSP2_MIDDLE_AWB_STA_DONE_LEN)-1)<<DSP2_MIDDLE_AWB_STA_DONE_POS)
#define DSP2_MIDDLE_AWB_STA_DONE_UMSK                            (~(((1U<<DSP2_MIDDLE_AWB_STA_DONE_LEN)-1)<<DSP2_MIDDLE_AWB_STA_DONE_POS))
#define DSP2_MIDDLE_AWB_WRITE_DATA_CNT                           DSP2_MIDDLE_AWB_WRITE_DATA_CNT
#define DSP2_MIDDLE_AWB_WRITE_DATA_CNT_POS                       (16U)
#define DSP2_MIDDLE_AWB_WRITE_DATA_CNT_LEN                       (12U)
#define DSP2_MIDDLE_AWB_WRITE_DATA_CNT_MSK                       (((1U<<DSP2_MIDDLE_AWB_WRITE_DATA_CNT_LEN)-1)<<DSP2_MIDDLE_AWB_WRITE_DATA_CNT_POS)
#define DSP2_MIDDLE_AWB_WRITE_DATA_CNT_UMSK                      (~(((1U<<DSP2_MIDDLE_AWB_WRITE_DATA_CNT_LEN)-1)<<DSP2_MIDDLE_AWB_WRITE_DATA_CNT_POS))
#define DSP2_MIDDLE_AWB_STA_INT_FLAG                             DSP2_MIDDLE_AWB_STA_INT_FLAG
#define DSP2_MIDDLE_AWB_STA_INT_FLAG_POS                         (28U)
#define DSP2_MIDDLE_AWB_STA_INT_FLAG_LEN                         (1U)
#define DSP2_MIDDLE_AWB_STA_INT_FLAG_MSK                         (((1U<<DSP2_MIDDLE_AWB_STA_INT_FLAG_LEN)-1)<<DSP2_MIDDLE_AWB_STA_INT_FLAG_POS)
#define DSP2_MIDDLE_AWB_STA_INT_FLAG_UMSK                        (~(((1U<<DSP2_MIDDLE_AWB_STA_INT_FLAG_LEN)-1)<<DSP2_MIDDLE_AWB_STA_INT_FLAG_POS))

/* 0x2FC : dummy */
#define DSP2_MIDDLE_DUMMY_OFFSET                                 (0x2FC)


struct  dsp2_middle_reg {
    /* 0x0  reserved */
    uint8_t RESERVED0x0[548];

    /* 0x224 : LSC_setting */
    union {
        struct {
            uint32_t reserved_0_7                   :  8; /* [ 7: 0],       rsvd,        0x0 */
            uint32_t Lsc_on_w                       :  1; /* [    8],        r/w,        0x0 */
            uint32_t reserved_9_15                  :  7; /* [15: 9],       rsvd,        0x0 */
            uint32_t X_offset_w                     :  8; /* [23:16],        r/w,        0x4 */
            uint32_t Y_offset_w                     :  8; /* [31:24],        r/w,        0x4 */
        }BF;
        uint32_t WORD;
    } LSC_setting;

    /* 0x228 : LSC_coeff_R_A */
    union {
        struct {
            uint32_t R_Acoeff_w                     : 23; /* [22: 0],        r/w,        0x0 */
            uint32_t reserved_23_31                 :  9; /* [31:23],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } LSC_coeff_R_A;

    /* 0x22C : LSC_coeff_R_BE */
    union {
        struct {
            uint32_t R_Bcoeff_w                     : 13; /* [12: 0],        r/w,        0x0 */
            uint32_t reserved_13_15                 :  3; /* [15:13],       rsvd,        0x0 */
            uint32_t R_Ecoeff_w                     : 13; /* [28:16],        r/w,        0x0 */
            uint32_t reserved_29_31                 :  3; /* [31:29],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } LSC_coeff_R_BE;

    /* 0x230 : LSC_coeff_R_CD */
    union {
        struct {
            uint32_t R_Dcoeff_w                     : 23; /* [22: 0],        r/w,        0x0 */
            uint32_t reserved_23                    :  1; /* [   23],       rsvd,        0x0 */
            uint32_t R_Ccoeff_w                     :  8; /* [31:24],        r/w,       0xff */
        }BF;
        uint32_t WORD;
    } LSC_coeff_R_CD;

    /* 0x234 : LSC_coeff_R_G */
    union {
        struct {
            uint32_t R_Gcoeff_w                     : 23; /* [22: 0],        r/w,        0x0 */
            uint32_t reserved_23_31                 :  9; /* [31:23],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } LSC_coeff_R_G;

    /* 0x238 : LSC_coeff_G_A */
    union {
        struct {
            uint32_t G_Acoeff_w                     : 23; /* [22: 0],        r/w,        0x0 */
            uint32_t reserved_23_31                 :  9; /* [31:23],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } LSC_coeff_G_A;

    /* 0x23C : LSC_coeff_G_BE */
    union {
        struct {
            uint32_t G_Bcoeff_w                     : 13; /* [12: 0],        r/w,        0x0 */
            uint32_t reserved_13_15                 :  3; /* [15:13],       rsvd,        0x0 */
            uint32_t G_Ecoeff_w                     : 13; /* [28:16],        r/w,        0x0 */
            uint32_t reserved_29_31                 :  3; /* [31:29],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } LSC_coeff_G_BE;

    /* 0x240 : LSC_coeff_G_CD */
    union {
        struct {
            uint32_t G_Dcoeff_w                     : 23; /* [22: 0],        r/w,        0x0 */
            uint32_t reserved_23                    :  1; /* [   23],       rsvd,        0x0 */
            uint32_t G_Ccoeff_w                     :  8; /* [31:24],        r/w,       0xff */
        }BF;
        uint32_t WORD;
    } LSC_coeff_G_CD;

    /* 0x244 : LSC_coeff_G_G */
    union {
        struct {
            uint32_t G_Gcoeff_w                     : 23; /* [22: 0],        r/w,        0x0 */
            uint32_t reserved_23_31                 :  9; /* [31:23],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } LSC_coeff_G_G;

    /* 0x248 : LSC_coeff_B_A */
    union {
        struct {
            uint32_t B_Acoeff_w                     : 23; /* [22: 0],        r/w,        0x0 */
            uint32_t reserved_23_31                 :  9; /* [31:23],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } LSC_coeff_B_A;

    /* 0x24C : LSC_coeff_B_BE */
    union {
        struct {
            uint32_t B_Bcoeff_w                     : 13; /* [12: 0],        r/w,        0x0 */
            uint32_t reserved_13_15                 :  3; /* [15:13],       rsvd,        0x0 */
            uint32_t B_Ecoeff_w                     : 13; /* [28:16],        r/w,        0x0 */
            uint32_t reserved_29_31                 :  3; /* [31:29],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } LSC_coeff_B_BE;

    /* 0x250 : LSC_coeff_B_CD */
    union {
        struct {
            uint32_t B_Dcoeff_w                     : 23; /* [22: 0],        r/w,        0x0 */
            uint32_t reserved_23                    :  1; /* [   23],       rsvd,        0x0 */
            uint32_t B_Ccoeff_w                     :  8; /* [31:24],        r/w,       0xff */
        }BF;
        uint32_t WORD;
    } LSC_coeff_B_CD;

    /* 0x254 : LSC_coeff_B_G */
    union {
        struct {
            uint32_t B_Gcoeff_w                     : 23; /* [22: 0],        r/w,        0x0 */
            uint32_t reserved_23_31                 :  9; /* [31:23],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } LSC_coeff_B_G;

    /* 0x258 : MAX_R_G */
    union {
        struct {
            uint32_t MAXR_w                         : 16; /* [15: 0],        r/w,       0xff */
            uint32_t MAXG_w                         : 16; /* [31:16],        r/w,       0xff */
        }BF;
        uint32_t WORD;
    } MAX_R_G;

    /* 0x25C : MAX_B */
    union {
        struct {
            uint32_t MAXB_w                         : 16; /* [15: 0],        r/w,       0xff */
            uint32_t reserved_16_31                 : 16; /* [31:16],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } MAX_B;

    /* 0x260 : defect_setting */
    union {
        struct {
            uint32_t defect_correct_mode_w          :  3; /* [ 2: 0],        r/w,        0x0 */
            uint32_t reserved_3_7                   :  5; /* [ 7: 3],       rsvd,        0x0 */
            uint32_t resolution_enhance1_w          :  1; /* [    8],        r/w,        0x1 */
            uint32_t resolution_enhance2_w          :  1; /* [    9],        r/w,        0x1 */
            uint32_t resolution_enhance3_w          :  1; /* [   10],        r/w,        0x1 */
            uint32_t reserved_11_15                 :  5; /* [15:11],       rsvd,        0x0 */
            uint32_t defect_address_w               :  8; /* [23:16],        r/w,        0x4 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } defect_setting;

    /* 0x264 : defect_position */
    union {
        struct {
            uint32_t x_position_w                   : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t y_position_w                   : 16; /* [31:16],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } defect_position;

    /* 0x268 : defect_th_A */
    union {
        struct {
            uint32_t defect_th1_w                   :  8; /* [ 7: 0],        r/w,       0x46 */
            uint32_t defect_th2_w                   :  8; /* [15: 8],        r/w,       0x14 */
            uint32_t defect_th3_w                   :  8; /* [23:16],        r/w,       0x32 */
            uint32_t defect_th4_w                   :  8; /* [31:24],        r/w,       0x32 */
        }BF;
        uint32_t WORD;
    } defect_th_A;

    /* 0x26C : defect_th_B */
    union {
        struct {
            uint32_t defect_th5_w                   :  8; /* [ 7: 0],        r/w,       0x14 */
            uint32_t reserved_8_31                  : 24; /* [31: 8],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } defect_th_B;

    /* 0x270 : awb_setting */
    union {
        struct {
            uint32_t awb_switch_bank_en_w           :  1; /* [    0],        r/w,        0x1 */
            uint32_t new_awb_sta_enable_w           :  1; /* [    1],        r/w,        0x0 */
            uint32_t bl_awb_gain_sel_w              :  1; /* [    2],        r/w,        0x1 */
            uint32_t reserved_3_15                  : 13; /* [15: 3],       rsvd,        0x0 */
            uint32_t grid_cnt_within_thre_r         : 11; /* [26:16],          r,        0x0 */
            uint32_t reserved_27_31                 :  5; /* [31:27],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } awb_setting;

    /* 0x274 : awb_roi_x */
    union {
        struct {
            uint32_t awb_roi_start_x_w              : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15                 :  5; /* [15:11],       rsvd,        0x0 */
            uint32_t awb_roi_width_w                : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31                 :  5; /* [31:27],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } awb_roi_x;

    /* 0x278 : awb_roi_y */
    union {
        struct {
            uint32_t awb_roi_start_y_w              : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15                 :  5; /* [15:11],       rsvd,        0x0 */
            uint32_t awb_roi_height_w               : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31                 :  5; /* [31:27],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } awb_roi_y;

    /* 0x27C : awb_image_size */
    union {
        struct {
            uint32_t awb_image_width_w              : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15                 :  5; /* [15:11],       rsvd,        0x0 */
            uint32_t awb_image_height_w             : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31                 :  5; /* [31:27],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } awb_image_size;

    /* 0x280 : awb_grid_size */
    union {
        struct {
            uint32_t awb_grid_width_w               :  8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t awb_grid_height_w              :  8; /* [15: 8],        r/w,        0x0 */
            uint32_t awb_grid_x_max_w               :  6; /* [21:16],        r/w,        0x0 */
            uint32_t reserved_22_23                 :  2; /* [23:22],       rsvd,        0x0 */
            uint32_t awb_grid_y_max_w               :  6; /* [29:24],        r/w,        0x0 */
            uint32_t reserved_30_31                 :  2; /* [31:30],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } awb_grid_size;

    /* 0x284 : awb_r_thre */
    union {
        struct {
            uint32_t awb_r_max_thr_w                : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t awb_r_min_thr_w                : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } awb_r_thre;

    /* 0x288 : awb_g_thre */
    union {
        struct {
            uint32_t awb_g_max_thr_w                : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t awb_g_min_thr_w                : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } awb_g_thre;

    /* 0x28C : awb_b_thre */
    union {
        struct {
            uint32_t awb_b_max_thr_w                : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t awb_b_min_thr_w                : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } awb_b_thre;

    /* 0x290 : awb_rgr_gain */
    union {
        struct {
            uint32_t awb_gr_gain_pre                : 15; /* [14: 0],        r/w,     0x1000 */
            uint32_t reserved_15                    :  1; /* [   15],       rsvd,        0x0 */
            uint32_t awb_r_gain_pre                 : 15; /* [30:16],        r/w,     0x1000 */
            uint32_t reserved_31                    :  1; /* [   31],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } awb_rgr_gain;

    /* 0x294 : awb_bgb_gain */
    union {
        struct {
            uint32_t awb_gb_gain_pre                : 15; /* [14: 0],        r/w,     0x1000 */
            uint32_t reserved_15                    :  1; /* [   15],       rsvd,        0x0 */
            uint32_t awb_b_gain_pre                 : 15; /* [30:16],        r/w,     0x1000 */
            uint32_t reserved_31                    :  1; /* [   31],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } awb_bgb_gain;

    /* 0x298  reserved */
    uint8_t RESERVED0x298[8];

    /* 0x2A0 : cfa_int_1 */
    union {
        struct {
            uint32_t reg_cfa_fringe_on_w            :  1; /* [    0],        r/w,        0x1 */
            uint32_t reserved_1_31                  : 31; /* [31: 1],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } cfa_int_1;

    /* 0x2a4  reserved */
    uint8_t RESERVED0x2a4[80];

    /* 0x2F4 : awb_sta_dbg1 */
    union {
        struct {
            uint32_t awb_grid_cnt_max               : 11; /* [10: 0],          r,        0x0 */
            uint32_t reserved_11                    :  1; /* [   11],       rsvd,        0x0 */
            uint32_t awb_fifo_full                  :  1; /* [   12],          r,        0x0 */
            uint32_t reserved_13_15                 :  3; /* [15:13],       rsvd,        0x0 */
            uint32_t awb_control_status             :  4; /* [19:16],          r,        0x0 */
            uint32_t awb_operation_done             :  1; /* [   20],          r,        0x0 */
            uint32_t awb_fifo_empty                 :  1; /* [   21],          r,        0x0 */
            uint32_t reserved_22_23                 :  2; /* [23:22],       rsvd,        0x0 */
            uint32_t blawb_w_cnt_r                  :  5; /* [28:24],          r,        0x0 */
            uint32_t reserved_29_30                 :  2; /* [30:29],       rsvd,        0x0 */
            uint32_t blawb_buf_idx_r                :  1; /* [   31],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } awb_sta_dbg1;

    /* 0x2F8 : awb_sta_dbg0 */
    union {
        struct {
            uint32_t awb_grid_cnt                   : 10; /* [ 9: 0],          r,        0x0 */
            uint32_t reserved_10_11                 :  2; /* [11:10],       rsvd,        0x0 */
            uint32_t awb_sta_done                   :  1; /* [   12],          r,        0x0 */
            uint32_t reserved_13_15                 :  3; /* [15:13],       rsvd,        0x0 */
            uint32_t awb_write_data_cnt             : 12; /* [27:16],          r,        0x0 */
            uint32_t awb_sta_int_flag               :  1; /* [   28],          r,        0x0 */
            uint32_t reserved_29_31                 :  3; /* [31:29],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } awb_sta_dbg0;

    /* 0x2FC : dummy */
    union {
        struct {
            uint32_t Reserved_31_0                  : 32; /* [31: 0],        r/w, 0xf0f0f0f0 */
        }BF;
        uint32_t WORD;
    } dummy;

};

typedef volatile struct dsp2_middle_reg dsp2_middle_reg_t;


#endif  /* __DSP2_MIDDLE_REG_H__ */
