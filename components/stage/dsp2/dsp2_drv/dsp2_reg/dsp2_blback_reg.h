/**
  ******************************************************************************
  * @file    dsp2_blback_reg.h
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
#ifndef  __DSP2_BLBACK_REG_H__
#define  __DSP2_BLBACK_REG_H__

#include "bl808.h"

/* 0x314 : ccr_coef_A */
#define DSP2_BLBACK_CCR_COEF_A_OFFSET                            (0x314)
#define DSP2_BLBACK_A11_PRE                                      DSP2_BLBACK_A11_PRE
#define DSP2_BLBACK_A11_PRE_POS                                  (16U)
#define DSP2_BLBACK_A11_PRE_LEN                                  (12U)
#define DSP2_BLBACK_A11_PRE_MSK                                  (((1U<<DSP2_BLBACK_A11_PRE_LEN)-1)<<DSP2_BLBACK_A11_PRE_POS)
#define DSP2_BLBACK_A11_PRE_UMSK                                 (~(((1U<<DSP2_BLBACK_A11_PRE_LEN)-1)<<DSP2_BLBACK_A11_PRE_POS))

/* 0x318 : ccr_coef_B */
#define DSP2_BLBACK_CCR_COEF_B_OFFSET                            (0x318)
#define DSP2_BLBACK_A12_PRE                                      DSP2_BLBACK_A12_PRE
#define DSP2_BLBACK_A12_PRE_POS                                  (0U)
#define DSP2_BLBACK_A12_PRE_LEN                                  (12U)
#define DSP2_BLBACK_A12_PRE_MSK                                  (((1U<<DSP2_BLBACK_A12_PRE_LEN)-1)<<DSP2_BLBACK_A12_PRE_POS)
#define DSP2_BLBACK_A12_PRE_UMSK                                 (~(((1U<<DSP2_BLBACK_A12_PRE_LEN)-1)<<DSP2_BLBACK_A12_PRE_POS))
#define DSP2_BLBACK_A13_PRE                                      DSP2_BLBACK_A13_PRE
#define DSP2_BLBACK_A13_PRE_POS                                  (16U)
#define DSP2_BLBACK_A13_PRE_LEN                                  (12U)
#define DSP2_BLBACK_A13_PRE_MSK                                  (((1U<<DSP2_BLBACK_A13_PRE_LEN)-1)<<DSP2_BLBACK_A13_PRE_POS)
#define DSP2_BLBACK_A13_PRE_UMSK                                 (~(((1U<<DSP2_BLBACK_A13_PRE_LEN)-1)<<DSP2_BLBACK_A13_PRE_POS))

/* 0x31C : ccr_coef_C */
#define DSP2_BLBACK_CCR_COEF_C_OFFSET                            (0x31C)
#define DSP2_BLBACK_A21_PRE                                      DSP2_BLBACK_A21_PRE
#define DSP2_BLBACK_A21_PRE_POS                                  (0U)
#define DSP2_BLBACK_A21_PRE_LEN                                  (12U)
#define DSP2_BLBACK_A21_PRE_MSK                                  (((1U<<DSP2_BLBACK_A21_PRE_LEN)-1)<<DSP2_BLBACK_A21_PRE_POS)
#define DSP2_BLBACK_A21_PRE_UMSK                                 (~(((1U<<DSP2_BLBACK_A21_PRE_LEN)-1)<<DSP2_BLBACK_A21_PRE_POS))
#define DSP2_BLBACK_A22_PRE                                      DSP2_BLBACK_A22_PRE
#define DSP2_BLBACK_A22_PRE_POS                                  (16U)
#define DSP2_BLBACK_A22_PRE_LEN                                  (12U)
#define DSP2_BLBACK_A22_PRE_MSK                                  (((1U<<DSP2_BLBACK_A22_PRE_LEN)-1)<<DSP2_BLBACK_A22_PRE_POS)
#define DSP2_BLBACK_A22_PRE_UMSK                                 (~(((1U<<DSP2_BLBACK_A22_PRE_LEN)-1)<<DSP2_BLBACK_A22_PRE_POS))

/* 0x320 : ccr_coef_D */
#define DSP2_BLBACK_CCR_COEF_D_OFFSET                            (0x320)
#define DSP2_BLBACK_A23_PRE                                      DSP2_BLBACK_A23_PRE
#define DSP2_BLBACK_A23_PRE_POS                                  (0U)
#define DSP2_BLBACK_A23_PRE_LEN                                  (12U)
#define DSP2_BLBACK_A23_PRE_MSK                                  (((1U<<DSP2_BLBACK_A23_PRE_LEN)-1)<<DSP2_BLBACK_A23_PRE_POS)
#define DSP2_BLBACK_A23_PRE_UMSK                                 (~(((1U<<DSP2_BLBACK_A23_PRE_LEN)-1)<<DSP2_BLBACK_A23_PRE_POS))
#define DSP2_BLBACK_A31_PRE                                      DSP2_BLBACK_A31_PRE
#define DSP2_BLBACK_A31_PRE_POS                                  (16U)
#define DSP2_BLBACK_A31_PRE_LEN                                  (12U)
#define DSP2_BLBACK_A31_PRE_MSK                                  (((1U<<DSP2_BLBACK_A31_PRE_LEN)-1)<<DSP2_BLBACK_A31_PRE_POS)
#define DSP2_BLBACK_A31_PRE_UMSK                                 (~(((1U<<DSP2_BLBACK_A31_PRE_LEN)-1)<<DSP2_BLBACK_A31_PRE_POS))

/* 0x324 : ccr_coef_E */
#define DSP2_BLBACK_CCR_COEF_E_OFFSET                            (0x324)
#define DSP2_BLBACK_A32_PRE                                      DSP2_BLBACK_A32_PRE
#define DSP2_BLBACK_A32_PRE_POS                                  (0U)
#define DSP2_BLBACK_A32_PRE_LEN                                  (12U)
#define DSP2_BLBACK_A32_PRE_MSK                                  (((1U<<DSP2_BLBACK_A32_PRE_LEN)-1)<<DSP2_BLBACK_A32_PRE_POS)
#define DSP2_BLBACK_A32_PRE_UMSK                                 (~(((1U<<DSP2_BLBACK_A32_PRE_LEN)-1)<<DSP2_BLBACK_A32_PRE_POS))
#define DSP2_BLBACK_A33_PRE                                      DSP2_BLBACK_A33_PRE
#define DSP2_BLBACK_A33_PRE_POS                                  (16U)
#define DSP2_BLBACK_A33_PRE_LEN                                  (12U)
#define DSP2_BLBACK_A33_PRE_MSK                                  (((1U<<DSP2_BLBACK_A33_PRE_LEN)-1)<<DSP2_BLBACK_A33_PRE_POS)
#define DSP2_BLBACK_A33_PRE_UMSK                                 (~(((1U<<DSP2_BLBACK_A33_PRE_LEN)-1)<<DSP2_BLBACK_A33_PRE_POS))

/* 0x328 : gamma_A */
#define DSP2_BLBACK_GAMMA_A_OFFSET                               (0x328)
#define DSP2_BLBACK_GAMMA_ON_PRE                                 DSP2_BLBACK_GAMMA_ON_PRE
#define DSP2_BLBACK_GAMMA_ON_PRE_POS                             (0U)
#define DSP2_BLBACK_GAMMA_ON_PRE_LEN                             (1U)
#define DSP2_BLBACK_GAMMA_ON_PRE_MSK                             (((1U<<DSP2_BLBACK_GAMMA_ON_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_ON_PRE_POS)
#define DSP2_BLBACK_GAMMA_ON_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_GAMMA_ON_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_ON_PRE_POS))
#define DSP2_BLBACK_GAMMA_EB_PRE                                 DSP2_BLBACK_GAMMA_EB_PRE
#define DSP2_BLBACK_GAMMA_EB_PRE_POS                             (1U)
#define DSP2_BLBACK_GAMMA_EB_PRE_LEN                             (1U)
#define DSP2_BLBACK_GAMMA_EB_PRE_MSK                             (((1U<<DSP2_BLBACK_GAMMA_EB_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_EB_PRE_POS)
#define DSP2_BLBACK_GAMMA_EB_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_GAMMA_EB_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_EB_PRE_POS))
#define DSP2_BLBACK_BL_GAMMA_EN_PRE                              DSP2_BLBACK_BL_GAMMA_EN_PRE
#define DSP2_BLBACK_BL_GAMMA_EN_PRE_POS                          (4U)
#define DSP2_BLBACK_BL_GAMMA_EN_PRE_LEN                          (1U)
#define DSP2_BLBACK_BL_GAMMA_EN_PRE_MSK                          (((1U<<DSP2_BLBACK_BL_GAMMA_EN_PRE_LEN)-1)<<DSP2_BLBACK_BL_GAMMA_EN_PRE_POS)
#define DSP2_BLBACK_BL_GAMMA_EN_PRE_UMSK                         (~(((1U<<DSP2_BLBACK_BL_GAMMA_EN_PRE_LEN)-1)<<DSP2_BLBACK_BL_GAMMA_EN_PRE_POS))

/* 0x33C : conv_mode */
#define DSP2_BLBACK_CONV_MODE_OFFSET                             (0x33C)
#define DSP2_BLBACK_CONV_MODE_W                                  DSP2_BLBACK_CONV_MODE_W
#define DSP2_BLBACK_CONV_MODE_W_POS                              (0U)
#define DSP2_BLBACK_CONV_MODE_W_LEN                              (1U)
#define DSP2_BLBACK_CONV_MODE_W_MSK                              (((1U<<DSP2_BLBACK_CONV_MODE_W_LEN)-1)<<DSP2_BLBACK_CONV_MODE_W_POS)
#define DSP2_BLBACK_CONV_MODE_W_UMSK                             (~(((1U<<DSP2_BLBACK_CONV_MODE_W_LEN)-1)<<DSP2_BLBACK_CONV_MODE_W_POS))

/* 0x34C : YUVC_A */
#define DSP2_BLBACK_YUVC_A_OFFSET                                (0x34C)
#define DSP2_BLBACK_YBRIGHTNESS_W                                DSP2_BLBACK_YBRIGHTNESS_W
#define DSP2_BLBACK_YBRIGHTNESS_W_POS                            (0U)
#define DSP2_BLBACK_YBRIGHTNESS_W_LEN                            (8U)
#define DSP2_BLBACK_YBRIGHTNESS_W_MSK                            (((1U<<DSP2_BLBACK_YBRIGHTNESS_W_LEN)-1)<<DSP2_BLBACK_YBRIGHTNESS_W_POS)
#define DSP2_BLBACK_YBRIGHTNESS_W_UMSK                           (~(((1U<<DSP2_BLBACK_YBRIGHTNESS_W_LEN)-1)<<DSP2_BLBACK_YBRIGHTNESS_W_POS))
#define DSP2_BLBACK_YCONTRAST_W                                  DSP2_BLBACK_YCONTRAST_W
#define DSP2_BLBACK_YCONTRAST_W_POS                              (8U)
#define DSP2_BLBACK_YCONTRAST_W_LEN                              (8U)
#define DSP2_BLBACK_YCONTRAST_W_MSK                              (((1U<<DSP2_BLBACK_YCONTRAST_W_LEN)-1)<<DSP2_BLBACK_YCONTRAST_W_POS)
#define DSP2_BLBACK_YCONTRAST_W_UMSK                             (~(((1U<<DSP2_BLBACK_YCONTRAST_W_LEN)-1)<<DSP2_BLBACK_YCONTRAST_W_POS))
#define DSP2_BLBACK_CBSATURATION_PRE                             DSP2_BLBACK_CBSATURATION_PRE
#define DSP2_BLBACK_CBSATURATION_PRE_POS                         (16U)
#define DSP2_BLBACK_CBSATURATION_PRE_LEN                         (8U)
#define DSP2_BLBACK_CBSATURATION_PRE_MSK                         (((1U<<DSP2_BLBACK_CBSATURATION_PRE_LEN)-1)<<DSP2_BLBACK_CBSATURATION_PRE_POS)
#define DSP2_BLBACK_CBSATURATION_PRE_UMSK                        (~(((1U<<DSP2_BLBACK_CBSATURATION_PRE_LEN)-1)<<DSP2_BLBACK_CBSATURATION_PRE_POS))
#define DSP2_BLBACK_CRSATURATION_PRE                             DSP2_BLBACK_CRSATURATION_PRE
#define DSP2_BLBACK_CRSATURATION_PRE_POS                         (24U)
#define DSP2_BLBACK_CRSATURATION_PRE_LEN                         (8U)
#define DSP2_BLBACK_CRSATURATION_PRE_MSK                         (((1U<<DSP2_BLBACK_CRSATURATION_PRE_LEN)-1)<<DSP2_BLBACK_CRSATURATION_PRE_POS)
#define DSP2_BLBACK_CRSATURATION_PRE_UMSK                        (~(((1U<<DSP2_BLBACK_CRSATURATION_PRE_LEN)-1)<<DSP2_BLBACK_CRSATURATION_PRE_POS))

/* 0x350 : YUVC_B */
#define DSP2_BLBACK_YUVC_B_OFFSET                                (0x350)
#define DSP2_BLBACK_SPECIALMODE_W                                DSP2_BLBACK_SPECIALMODE_W
#define DSP2_BLBACK_SPECIALMODE_W_POS                            (0U)
#define DSP2_BLBACK_SPECIALMODE_W_LEN                            (3U)
#define DSP2_BLBACK_SPECIALMODE_W_MSK                            (((1U<<DSP2_BLBACK_SPECIALMODE_W_LEN)-1)<<DSP2_BLBACK_SPECIALMODE_W_POS)
#define DSP2_BLBACK_SPECIALMODE_W_UMSK                           (~(((1U<<DSP2_BLBACK_SPECIALMODE_W_LEN)-1)<<DSP2_BLBACK_SPECIALMODE_W_POS))
#define DSP2_BLBACK_C444TO422FILTERINGMODE_W                     DSP2_BLBACK_C444TO422FILTERINGMODE_W
#define DSP2_BLBACK_C444TO422FILTERINGMODE_W_POS                 (4U)
#define DSP2_BLBACK_C444TO422FILTERINGMODE_W_LEN                 (1U)
#define DSP2_BLBACK_C444TO422FILTERINGMODE_W_MSK                 (((1U<<DSP2_BLBACK_C444TO422FILTERINGMODE_W_LEN)-1)<<DSP2_BLBACK_C444TO422FILTERINGMODE_W_POS)
#define DSP2_BLBACK_C444TO422FILTERINGMODE_W_UMSK                (~(((1U<<DSP2_BLBACK_C444TO422FILTERINGMODE_W_LEN)-1)<<DSP2_BLBACK_C444TO422FILTERINGMODE_W_POS))
#define DSP2_BLBACK_SEPIACB_W                                    DSP2_BLBACK_SEPIACB_W
#define DSP2_BLBACK_SEPIACB_W_POS                                (8U)
#define DSP2_BLBACK_SEPIACB_W_LEN                                (8U)
#define DSP2_BLBACK_SEPIACB_W_MSK                                (((1U<<DSP2_BLBACK_SEPIACB_W_LEN)-1)<<DSP2_BLBACK_SEPIACB_W_POS)
#define DSP2_BLBACK_SEPIACB_W_UMSK                               (~(((1U<<DSP2_BLBACK_SEPIACB_W_LEN)-1)<<DSP2_BLBACK_SEPIACB_W_POS))
#define DSP2_BLBACK_SEPIACR_W                                    DSP2_BLBACK_SEPIACR_W
#define DSP2_BLBACK_SEPIACR_W_POS                                (16U)
#define DSP2_BLBACK_SEPIACR_W_LEN                                (8U)
#define DSP2_BLBACK_SEPIACR_W_MSK                                (((1U<<DSP2_BLBACK_SEPIACR_W_LEN)-1)<<DSP2_BLBACK_SEPIACR_W_POS)
#define DSP2_BLBACK_SEPIACR_W_UMSK                               (~(((1U<<DSP2_BLBACK_SEPIACR_W_LEN)-1)<<DSP2_BLBACK_SEPIACR_W_POS))
#define DSP2_BLBACK_SOLARTHRED_W                                 DSP2_BLBACK_SOLARTHRED_W
#define DSP2_BLBACK_SOLARTHRED_W_POS                             (24U)
#define DSP2_BLBACK_SOLARTHRED_W_LEN                             (8U)
#define DSP2_BLBACK_SOLARTHRED_W_MSK                             (((1U<<DSP2_BLBACK_SOLARTHRED_W_LEN)-1)<<DSP2_BLBACK_SOLARTHRED_W_POS)
#define DSP2_BLBACK_SOLARTHRED_W_UMSK                            (~(((1U<<DSP2_BLBACK_SOLARTHRED_W_LEN)-1)<<DSP2_BLBACK_SOLARTHRED_W_POS))

/* 0x354 : DNR_A */
#define DSP2_BLBACK_DNR_A_OFFSET                                 (0x354)
#define DSP2_BLBACK_NOISE_LEVEL_PRE                              DSP2_BLBACK_NOISE_LEVEL_PRE
#define DSP2_BLBACK_NOISE_LEVEL_PRE_POS                          (0U)
#define DSP2_BLBACK_NOISE_LEVEL_PRE_LEN                          (6U)
#define DSP2_BLBACK_NOISE_LEVEL_PRE_MSK                          (((1U<<DSP2_BLBACK_NOISE_LEVEL_PRE_LEN)-1)<<DSP2_BLBACK_NOISE_LEVEL_PRE_POS)
#define DSP2_BLBACK_NOISE_LEVEL_PRE_UMSK                         (~(((1U<<DSP2_BLBACK_NOISE_LEVEL_PRE_LEN)-1)<<DSP2_BLBACK_NOISE_LEVEL_PRE_POS))
#define DSP2_BLBACK_NR_HSIZE_PRE                                 DSP2_BLBACK_NR_HSIZE_PRE
#define DSP2_BLBACK_NR_HSIZE_PRE_POS                             (8U)
#define DSP2_BLBACK_NR_HSIZE_PRE_LEN                             (16U)
#define DSP2_BLBACK_NR_HSIZE_PRE_MSK                             (((1U<<DSP2_BLBACK_NR_HSIZE_PRE_LEN)-1)<<DSP2_BLBACK_NR_HSIZE_PRE_POS)
#define DSP2_BLBACK_NR_HSIZE_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_NR_HSIZE_PRE_LEN)-1)<<DSP2_BLBACK_NR_HSIZE_PRE_POS))
#define DSP2_BLBACK_FILT_STRENGTH_2D_PRE                         DSP2_BLBACK_FILT_STRENGTH_2D_PRE
#define DSP2_BLBACK_FILT_STRENGTH_2D_PRE_POS                     (24U)
#define DSP2_BLBACK_FILT_STRENGTH_2D_PRE_LEN                     (4U)
#define DSP2_BLBACK_FILT_STRENGTH_2D_PRE_MSK                     (((1U<<DSP2_BLBACK_FILT_STRENGTH_2D_PRE_LEN)-1)<<DSP2_BLBACK_FILT_STRENGTH_2D_PRE_POS)
#define DSP2_BLBACK_FILT_STRENGTH_2D_PRE_UMSK                    (~(((1U<<DSP2_BLBACK_FILT_STRENGTH_2D_PRE_LEN)-1)<<DSP2_BLBACK_FILT_STRENGTH_2D_PRE_POS))
#define DSP2_BLBACK_FILT_STRENGTH_3D_PRE                         DSP2_BLBACK_FILT_STRENGTH_3D_PRE
#define DSP2_BLBACK_FILT_STRENGTH_3D_PRE_POS                     (28U)
#define DSP2_BLBACK_FILT_STRENGTH_3D_PRE_LEN                     (4U)
#define DSP2_BLBACK_FILT_STRENGTH_3D_PRE_MSK                     (((1U<<DSP2_BLBACK_FILT_STRENGTH_3D_PRE_LEN)-1)<<DSP2_BLBACK_FILT_STRENGTH_3D_PRE_POS)
#define DSP2_BLBACK_FILT_STRENGTH_3D_PRE_UMSK                    (~(((1U<<DSP2_BLBACK_FILT_STRENGTH_3D_PRE_LEN)-1)<<DSP2_BLBACK_FILT_STRENGTH_3D_PRE_POS))

/* 0x358 : DNR_B */
#define DSP2_BLBACK_DNR_B_OFFSET                                 (0x358)
#define DSP2_BLBACK_CBCR_SELECT_W                                DSP2_BLBACK_CBCR_SELECT_W
#define DSP2_BLBACK_CBCR_SELECT_W_POS                            (8U)
#define DSP2_BLBACK_CBCR_SELECT_W_LEN                            (1U)
#define DSP2_BLBACK_CBCR_SELECT_W_MSK                            (((1U<<DSP2_BLBACK_CBCR_SELECT_W_LEN)-1)<<DSP2_BLBACK_CBCR_SELECT_W_POS)
#define DSP2_BLBACK_CBCR_SELECT_W_UMSK                           (~(((1U<<DSP2_BLBACK_CBCR_SELECT_W_LEN)-1)<<DSP2_BLBACK_CBCR_SELECT_W_POS))
#define DSP2_BLBACK_OUT_FORMAT_W                                 DSP2_BLBACK_OUT_FORMAT_W
#define DSP2_BLBACK_OUT_FORMAT_W_POS                             (9U)
#define DSP2_BLBACK_OUT_FORMAT_W_LEN                             (2U)
#define DSP2_BLBACK_OUT_FORMAT_W_MSK                             (((1U<<DSP2_BLBACK_OUT_FORMAT_W_LEN)-1)<<DSP2_BLBACK_OUT_FORMAT_W_POS)
#define DSP2_BLBACK_OUT_FORMAT_W_UMSK                            (~(((1U<<DSP2_BLBACK_OUT_FORMAT_W_LEN)-1)<<DSP2_BLBACK_OUT_FORMAT_W_POS))

/* 0x360 : BLEE_0 */
#define DSP2_BLBACK_BLEE_0_OFFSET                                (0x360)
#define DSP2_BLBACK_EE_EB_PRE                                    DSP2_BLBACK_EE_EB_PRE
#define DSP2_BLBACK_EE_EB_PRE_POS                                (0U)
#define DSP2_BLBACK_EE_EB_PRE_LEN                                (1U)
#define DSP2_BLBACK_EE_EB_PRE_MSK                                (((1U<<DSP2_BLBACK_EE_EB_PRE_LEN)-1)<<DSP2_BLBACK_EE_EB_PRE_POS)
#define DSP2_BLBACK_EE_EB_PRE_UMSK                               (~(((1U<<DSP2_BLBACK_EE_EB_PRE_LEN)-1)<<DSP2_BLBACK_EE_EB_PRE_POS))
#define DSP2_BLBACK_OVRSHT_EB_PRE                                DSP2_BLBACK_OVRSHT_EB_PRE
#define DSP2_BLBACK_OVRSHT_EB_PRE_POS                            (1U)
#define DSP2_BLBACK_OVRSHT_EB_PRE_LEN                            (1U)
#define DSP2_BLBACK_OVRSHT_EB_PRE_MSK                            (((1U<<DSP2_BLBACK_OVRSHT_EB_PRE_LEN)-1)<<DSP2_BLBACK_OVRSHT_EB_PRE_POS)
#define DSP2_BLBACK_OVRSHT_EB_PRE_UMSK                           (~(((1U<<DSP2_BLBACK_OVRSHT_EB_PRE_LEN)-1)<<DSP2_BLBACK_OVRSHT_EB_PRE_POS))
#define DSP2_BLBACK_TXT_THR_PRE                                  DSP2_BLBACK_TXT_THR_PRE
#define DSP2_BLBACK_TXT_THR_PRE_POS                              (16U)
#define DSP2_BLBACK_TXT_THR_PRE_LEN                              (9U)
#define DSP2_BLBACK_TXT_THR_PRE_MSK                              (((1U<<DSP2_BLBACK_TXT_THR_PRE_LEN)-1)<<DSP2_BLBACK_TXT_THR_PRE_POS)
#define DSP2_BLBACK_TXT_THR_PRE_UMSK                             (~(((1U<<DSP2_BLBACK_TXT_THR_PRE_LEN)-1)<<DSP2_BLBACK_TXT_THR_PRE_POS))

/* 0x364 : BLEE_1 */
#define DSP2_BLBACK_BLEE_1_OFFSET                                (0x364)
#define DSP2_BLBACK_THRESH1_PRE                                  DSP2_BLBACK_THRESH1_PRE
#define DSP2_BLBACK_THRESH1_PRE_POS                              (0U)
#define DSP2_BLBACK_THRESH1_PRE_LEN                              (7U)
#define DSP2_BLBACK_THRESH1_PRE_MSK                              (((1U<<DSP2_BLBACK_THRESH1_PRE_LEN)-1)<<DSP2_BLBACK_THRESH1_PRE_POS)
#define DSP2_BLBACK_THRESH1_PRE_UMSK                             (~(((1U<<DSP2_BLBACK_THRESH1_PRE_LEN)-1)<<DSP2_BLBACK_THRESH1_PRE_POS))
#define DSP2_BLBACK_THRESH2_PRE                                  DSP2_BLBACK_THRESH2_PRE
#define DSP2_BLBACK_THRESH2_PRE_POS                              (8U)
#define DSP2_BLBACK_THRESH2_PRE_LEN                              (7U)
#define DSP2_BLBACK_THRESH2_PRE_MSK                              (((1U<<DSP2_BLBACK_THRESH2_PRE_LEN)-1)<<DSP2_BLBACK_THRESH2_PRE_POS)
#define DSP2_BLBACK_THRESH2_PRE_UMSK                             (~(((1U<<DSP2_BLBACK_THRESH2_PRE_LEN)-1)<<DSP2_BLBACK_THRESH2_PRE_POS))
#define DSP2_BLBACK_FLAT_THR_PRE                                 DSP2_BLBACK_FLAT_THR_PRE
#define DSP2_BLBACK_FLAT_THR_PRE_POS                             (16U)
#define DSP2_BLBACK_FLAT_THR_PRE_LEN                             (8U)
#define DSP2_BLBACK_FLAT_THR_PRE_MSK                             (((1U<<DSP2_BLBACK_FLAT_THR_PRE_LEN)-1)<<DSP2_BLBACK_FLAT_THR_PRE_POS)
#define DSP2_BLBACK_FLAT_THR_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_FLAT_THR_PRE_LEN)-1)<<DSP2_BLBACK_FLAT_THR_PRE_POS))

/* 0x368 : BLEE_2 */
#define DSP2_BLBACK_BLEE_2_OFFSET                                (0x368)
#define DSP2_BLBACK_OVRSHT_POS_PRE                               DSP2_BLBACK_OVRSHT_POS_PRE
#define DSP2_BLBACK_OVRSHT_POS_PRE_POS                           (0U)
#define DSP2_BLBACK_OVRSHT_POS_PRE_LEN                           (7U)
#define DSP2_BLBACK_OVRSHT_POS_PRE_MSK                           (((1U<<DSP2_BLBACK_OVRSHT_POS_PRE_LEN)-1)<<DSP2_BLBACK_OVRSHT_POS_PRE_POS)
#define DSP2_BLBACK_OVRSHT_POS_PRE_UMSK                          (~(((1U<<DSP2_BLBACK_OVRSHT_POS_PRE_LEN)-1)<<DSP2_BLBACK_OVRSHT_POS_PRE_POS))
#define DSP2_BLBACK_OVRSHT_NEG_PRE                               DSP2_BLBACK_OVRSHT_NEG_PRE
#define DSP2_BLBACK_OVRSHT_NEG_PRE_POS                           (8U)
#define DSP2_BLBACK_OVRSHT_NEG_PRE_LEN                           (7U)
#define DSP2_BLBACK_OVRSHT_NEG_PRE_MSK                           (((1U<<DSP2_BLBACK_OVRSHT_NEG_PRE_LEN)-1)<<DSP2_BLBACK_OVRSHT_NEG_PRE_POS)
#define DSP2_BLBACK_OVRSHT_NEG_PRE_UMSK                          (~(((1U<<DSP2_BLBACK_OVRSHT_NEG_PRE_LEN)-1)<<DSP2_BLBACK_OVRSHT_NEG_PRE_POS))
#define DSP2_BLBACK_POSEE_STR_PRE                                DSP2_BLBACK_POSEE_STR_PRE
#define DSP2_BLBACK_POSEE_STR_PRE_POS                            (16U)
#define DSP2_BLBACK_POSEE_STR_PRE_LEN                            (7U)
#define DSP2_BLBACK_POSEE_STR_PRE_MSK                            (((1U<<DSP2_BLBACK_POSEE_STR_PRE_LEN)-1)<<DSP2_BLBACK_POSEE_STR_PRE_POS)
#define DSP2_BLBACK_POSEE_STR_PRE_UMSK                           (~(((1U<<DSP2_BLBACK_POSEE_STR_PRE_LEN)-1)<<DSP2_BLBACK_POSEE_STR_PRE_POS))
#define DSP2_BLBACK_NEGEE_STR_PRE                                DSP2_BLBACK_NEGEE_STR_PRE
#define DSP2_BLBACK_NEGEE_STR_PRE_POS                            (24U)
#define DSP2_BLBACK_NEGEE_STR_PRE_LEN                            (7U)
#define DSP2_BLBACK_NEGEE_STR_PRE_MSK                            (((1U<<DSP2_BLBACK_NEGEE_STR_PRE_LEN)-1)<<DSP2_BLBACK_NEGEE_STR_PRE_POS)
#define DSP2_BLBACK_NEGEE_STR_PRE_UMSK                           (~(((1U<<DSP2_BLBACK_NEGEE_STR_PRE_LEN)-1)<<DSP2_BLBACK_NEGEE_STR_PRE_POS))

/* 0x36C : BLEE_3 */
#define DSP2_BLBACK_BLEE_3_OFFSET                                (0x36C)
#define DSP2_BLBACK_EDGE_THR_PRE                                 DSP2_BLBACK_EDGE_THR_PRE
#define DSP2_BLBACK_EDGE_THR_PRE_POS                             (0U)
#define DSP2_BLBACK_EDGE_THR_PRE_LEN                             (16U)
#define DSP2_BLBACK_EDGE_THR_PRE_MSK                             (((1U<<DSP2_BLBACK_EDGE_THR_PRE_LEN)-1)<<DSP2_BLBACK_EDGE_THR_PRE_POS)
#define DSP2_BLBACK_EDGE_THR_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_EDGE_THR_PRE_LEN)-1)<<DSP2_BLBACK_EDGE_THR_PRE_POS))
#define DSP2_BLBACK_NR_STR_PRE                                   DSP2_BLBACK_NR_STR_PRE
#define DSP2_BLBACK_NR_STR_PRE_POS                               (16U)
#define DSP2_BLBACK_NR_STR_PRE_LEN                               (8U)
#define DSP2_BLBACK_NR_STR_PRE_MSK                               (((1U<<DSP2_BLBACK_NR_STR_PRE_LEN)-1)<<DSP2_BLBACK_NR_STR_PRE_POS)
#define DSP2_BLBACK_NR_STR_PRE_UMSK                              (~(((1U<<DSP2_BLBACK_NR_STR_PRE_LEN)-1)<<DSP2_BLBACK_NR_STR_PRE_POS))

/* 0x370 : BLEE_4 */
#define DSP2_BLBACK_BLEE_4_OFFSET                                (0x370)
#define DSP2_BLBACK_LUMA_WGT0_PRE                                DSP2_BLBACK_LUMA_WGT0_PRE
#define DSP2_BLBACK_LUMA_WGT0_PRE_POS                            (0U)
#define DSP2_BLBACK_LUMA_WGT0_PRE_LEN                            (10U)
#define DSP2_BLBACK_LUMA_WGT0_PRE_MSK                            (((1U<<DSP2_BLBACK_LUMA_WGT0_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT0_PRE_POS)
#define DSP2_BLBACK_LUMA_WGT0_PRE_UMSK                           (~(((1U<<DSP2_BLBACK_LUMA_WGT0_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT0_PRE_POS))
#define DSP2_BLBACK_LUMA_WGT1_PRE                                DSP2_BLBACK_LUMA_WGT1_PRE
#define DSP2_BLBACK_LUMA_WGT1_PRE_POS                            (16U)
#define DSP2_BLBACK_LUMA_WGT1_PRE_LEN                            (10U)
#define DSP2_BLBACK_LUMA_WGT1_PRE_MSK                            (((1U<<DSP2_BLBACK_LUMA_WGT1_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT1_PRE_POS)
#define DSP2_BLBACK_LUMA_WGT1_PRE_UMSK                           (~(((1U<<DSP2_BLBACK_LUMA_WGT1_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT1_PRE_POS))

/* 0x374 : BLEE_5 */
#define DSP2_BLBACK_BLEE_5_OFFSET                                (0x374)
#define DSP2_BLBACK_LUMA_WGT2_PRE                                DSP2_BLBACK_LUMA_WGT2_PRE
#define DSP2_BLBACK_LUMA_WGT2_PRE_POS                            (0U)
#define DSP2_BLBACK_LUMA_WGT2_PRE_LEN                            (10U)
#define DSP2_BLBACK_LUMA_WGT2_PRE_MSK                            (((1U<<DSP2_BLBACK_LUMA_WGT2_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT2_PRE_POS)
#define DSP2_BLBACK_LUMA_WGT2_PRE_UMSK                           (~(((1U<<DSP2_BLBACK_LUMA_WGT2_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT2_PRE_POS))
#define DSP2_BLBACK_LUMA_WGT3_PRE                                DSP2_BLBACK_LUMA_WGT3_PRE
#define DSP2_BLBACK_LUMA_WGT3_PRE_POS                            (16U)
#define DSP2_BLBACK_LUMA_WGT3_PRE_LEN                            (10U)
#define DSP2_BLBACK_LUMA_WGT3_PRE_MSK                            (((1U<<DSP2_BLBACK_LUMA_WGT3_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT3_PRE_POS)
#define DSP2_BLBACK_LUMA_WGT3_PRE_UMSK                           (~(((1U<<DSP2_BLBACK_LUMA_WGT3_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT3_PRE_POS))

/* 0x378 : BLEE_6 */
#define DSP2_BLBACK_BLEE_6_OFFSET                                (0x378)
#define DSP2_BLBACK_LUMA_WGT4_PRE                                DSP2_BLBACK_LUMA_WGT4_PRE
#define DSP2_BLBACK_LUMA_WGT4_PRE_POS                            (0U)
#define DSP2_BLBACK_LUMA_WGT4_PRE_LEN                            (10U)
#define DSP2_BLBACK_LUMA_WGT4_PRE_MSK                            (((1U<<DSP2_BLBACK_LUMA_WGT4_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT4_PRE_POS)
#define DSP2_BLBACK_LUMA_WGT4_PRE_UMSK                           (~(((1U<<DSP2_BLBACK_LUMA_WGT4_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT4_PRE_POS))
#define DSP2_BLBACK_LUMA_WGT5_PRE                                DSP2_BLBACK_LUMA_WGT5_PRE
#define DSP2_BLBACK_LUMA_WGT5_PRE_POS                            (16U)
#define DSP2_BLBACK_LUMA_WGT5_PRE_LEN                            (10U)
#define DSP2_BLBACK_LUMA_WGT5_PRE_MSK                            (((1U<<DSP2_BLBACK_LUMA_WGT5_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT5_PRE_POS)
#define DSP2_BLBACK_LUMA_WGT5_PRE_UMSK                           (~(((1U<<DSP2_BLBACK_LUMA_WGT5_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT5_PRE_POS))

/* 0x37C : BLEE_7 */
#define DSP2_BLBACK_BLEE_7_OFFSET                                (0x37C)
#define DSP2_BLBACK_LUMA_WGT6_PRE                                DSP2_BLBACK_LUMA_WGT6_PRE
#define DSP2_BLBACK_LUMA_WGT6_PRE_POS                            (0U)
#define DSP2_BLBACK_LUMA_WGT6_PRE_LEN                            (10U)
#define DSP2_BLBACK_LUMA_WGT6_PRE_MSK                            (((1U<<DSP2_BLBACK_LUMA_WGT6_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT6_PRE_POS)
#define DSP2_BLBACK_LUMA_WGT6_PRE_UMSK                           (~(((1U<<DSP2_BLBACK_LUMA_WGT6_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT6_PRE_POS))
#define DSP2_BLBACK_LUMA_WGT7_PRE                                DSP2_BLBACK_LUMA_WGT7_PRE
#define DSP2_BLBACK_LUMA_WGT7_PRE_POS                            (16U)
#define DSP2_BLBACK_LUMA_WGT7_PRE_LEN                            (10U)
#define DSP2_BLBACK_LUMA_WGT7_PRE_MSK                            (((1U<<DSP2_BLBACK_LUMA_WGT7_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT7_PRE_POS)
#define DSP2_BLBACK_LUMA_WGT7_PRE_UMSK                           (~(((1U<<DSP2_BLBACK_LUMA_WGT7_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT7_PRE_POS))

/* 0x380 : BLEE_8 */
#define DSP2_BLBACK_BLEE_8_OFFSET                                (0x380)
#define DSP2_BLBACK_LUMA_WGT8_PRE                                DSP2_BLBACK_LUMA_WGT8_PRE
#define DSP2_BLBACK_LUMA_WGT8_PRE_POS                            (0U)
#define DSP2_BLBACK_LUMA_WGT8_PRE_LEN                            (10U)
#define DSP2_BLBACK_LUMA_WGT8_PRE_MSK                            (((1U<<DSP2_BLBACK_LUMA_WGT8_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT8_PRE_POS)
#define DSP2_BLBACK_LUMA_WGT8_PRE_UMSK                           (~(((1U<<DSP2_BLBACK_LUMA_WGT8_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT8_PRE_POS))
#define DSP2_BLBACK_LUMA_WGT9_PRE                                DSP2_BLBACK_LUMA_WGT9_PRE
#define DSP2_BLBACK_LUMA_WGT9_PRE_POS                            (16U)
#define DSP2_BLBACK_LUMA_WGT9_PRE_LEN                            (10U)
#define DSP2_BLBACK_LUMA_WGT9_PRE_MSK                            (((1U<<DSP2_BLBACK_LUMA_WGT9_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT9_PRE_POS)
#define DSP2_BLBACK_LUMA_WGT9_PRE_UMSK                           (~(((1U<<DSP2_BLBACK_LUMA_WGT9_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT9_PRE_POS))

/* 0x384 : BLEE_9 */
#define DSP2_BLBACK_BLEE_9_OFFSET                                (0x384)
#define DSP2_BLBACK_LUMA_WGT10_PRE                               DSP2_BLBACK_LUMA_WGT10_PRE
#define DSP2_BLBACK_LUMA_WGT10_PRE_POS                           (0U)
#define DSP2_BLBACK_LUMA_WGT10_PRE_LEN                           (10U)
#define DSP2_BLBACK_LUMA_WGT10_PRE_MSK                           (((1U<<DSP2_BLBACK_LUMA_WGT10_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT10_PRE_POS)
#define DSP2_BLBACK_LUMA_WGT10_PRE_UMSK                          (~(((1U<<DSP2_BLBACK_LUMA_WGT10_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT10_PRE_POS))
#define DSP2_BLBACK_LUMA_WGT11_PRE                               DSP2_BLBACK_LUMA_WGT11_PRE
#define DSP2_BLBACK_LUMA_WGT11_PRE_POS                           (16U)
#define DSP2_BLBACK_LUMA_WGT11_PRE_LEN                           (10U)
#define DSP2_BLBACK_LUMA_WGT11_PRE_MSK                           (((1U<<DSP2_BLBACK_LUMA_WGT11_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT11_PRE_POS)
#define DSP2_BLBACK_LUMA_WGT11_PRE_UMSK                          (~(((1U<<DSP2_BLBACK_LUMA_WGT11_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT11_PRE_POS))

/* 0x388 : BLEE_A */
#define DSP2_BLBACK_BLEE_A_OFFSET                                (0x388)
#define DSP2_BLBACK_LUMA_WGT12_PRE                               DSP2_BLBACK_LUMA_WGT12_PRE
#define DSP2_BLBACK_LUMA_WGT12_PRE_POS                           (0U)
#define DSP2_BLBACK_LUMA_WGT12_PRE_LEN                           (10U)
#define DSP2_BLBACK_LUMA_WGT12_PRE_MSK                           (((1U<<DSP2_BLBACK_LUMA_WGT12_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT12_PRE_POS)
#define DSP2_BLBACK_LUMA_WGT12_PRE_UMSK                          (~(((1U<<DSP2_BLBACK_LUMA_WGT12_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT12_PRE_POS))
#define DSP2_BLBACK_LUMA_WGT13_PRE                               DSP2_BLBACK_LUMA_WGT13_PRE
#define DSP2_BLBACK_LUMA_WGT13_PRE_POS                           (16U)
#define DSP2_BLBACK_LUMA_WGT13_PRE_LEN                           (10U)
#define DSP2_BLBACK_LUMA_WGT13_PRE_MSK                           (((1U<<DSP2_BLBACK_LUMA_WGT13_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT13_PRE_POS)
#define DSP2_BLBACK_LUMA_WGT13_PRE_UMSK                          (~(((1U<<DSP2_BLBACK_LUMA_WGT13_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT13_PRE_POS))

/* 0x38C : BLEE_B */
#define DSP2_BLBACK_BLEE_B_OFFSET                                (0x38C)
#define DSP2_BLBACK_LUMA_WGT14_PRE                               DSP2_BLBACK_LUMA_WGT14_PRE
#define DSP2_BLBACK_LUMA_WGT14_PRE_POS                           (0U)
#define DSP2_BLBACK_LUMA_WGT14_PRE_LEN                           (10U)
#define DSP2_BLBACK_LUMA_WGT14_PRE_MSK                           (((1U<<DSP2_BLBACK_LUMA_WGT14_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT14_PRE_POS)
#define DSP2_BLBACK_LUMA_WGT14_PRE_UMSK                          (~(((1U<<DSP2_BLBACK_LUMA_WGT14_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT14_PRE_POS))
#define DSP2_BLBACK_LUMA_WGT15_PRE                               DSP2_BLBACK_LUMA_WGT15_PRE
#define DSP2_BLBACK_LUMA_WGT15_PRE_POS                           (16U)
#define DSP2_BLBACK_LUMA_WGT15_PRE_LEN                           (10U)
#define DSP2_BLBACK_LUMA_WGT15_PRE_MSK                           (((1U<<DSP2_BLBACK_LUMA_WGT15_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT15_PRE_POS)
#define DSP2_BLBACK_LUMA_WGT15_PRE_UMSK                          (~(((1U<<DSP2_BLBACK_LUMA_WGT15_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT15_PRE_POS))

/* 0x390 : BLEE_C */
#define DSP2_BLBACK_BLEE_C_OFFSET                                (0x390)
#define DSP2_BLBACK_LUMA_WGT16_PRE                               DSP2_BLBACK_LUMA_WGT16_PRE
#define DSP2_BLBACK_LUMA_WGT16_PRE_POS                           (0U)
#define DSP2_BLBACK_LUMA_WGT16_PRE_LEN                           (10U)
#define DSP2_BLBACK_LUMA_WGT16_PRE_MSK                           (((1U<<DSP2_BLBACK_LUMA_WGT16_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT16_PRE_POS)
#define DSP2_BLBACK_LUMA_WGT16_PRE_UMSK                          (~(((1U<<DSP2_BLBACK_LUMA_WGT16_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT16_PRE_POS))
#define DSP2_BLBACK_LUMA_WGT17_PRE                               DSP2_BLBACK_LUMA_WGT17_PRE
#define DSP2_BLBACK_LUMA_WGT17_PRE_POS                           (16U)
#define DSP2_BLBACK_LUMA_WGT17_PRE_LEN                           (10U)
#define DSP2_BLBACK_LUMA_WGT17_PRE_MSK                           (((1U<<DSP2_BLBACK_LUMA_WGT17_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT17_PRE_POS)
#define DSP2_BLBACK_LUMA_WGT17_PRE_UMSK                          (~(((1U<<DSP2_BLBACK_LUMA_WGT17_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT17_PRE_POS))

/* 0x394 : BLEE_D */
#define DSP2_BLBACK_BLEE_D_OFFSET                                (0x394)
#define DSP2_BLBACK_LUMA_WGT18_PRE                               DSP2_BLBACK_LUMA_WGT18_PRE
#define DSP2_BLBACK_LUMA_WGT18_PRE_POS                           (0U)
#define DSP2_BLBACK_LUMA_WGT18_PRE_LEN                           (10U)
#define DSP2_BLBACK_LUMA_WGT18_PRE_MSK                           (((1U<<DSP2_BLBACK_LUMA_WGT18_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT18_PRE_POS)
#define DSP2_BLBACK_LUMA_WGT18_PRE_UMSK                          (~(((1U<<DSP2_BLBACK_LUMA_WGT18_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT18_PRE_POS))
#define DSP2_BLBACK_LUMA_WGT19_PRE                               DSP2_BLBACK_LUMA_WGT19_PRE
#define DSP2_BLBACK_LUMA_WGT19_PRE_POS                           (16U)
#define DSP2_BLBACK_LUMA_WGT19_PRE_LEN                           (10U)
#define DSP2_BLBACK_LUMA_WGT19_PRE_MSK                           (((1U<<DSP2_BLBACK_LUMA_WGT19_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT19_PRE_POS)
#define DSP2_BLBACK_LUMA_WGT19_PRE_UMSK                          (~(((1U<<DSP2_BLBACK_LUMA_WGT19_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT19_PRE_POS))

/* 0x398 : BLEE_E */
#define DSP2_BLBACK_BLEE_E_OFFSET                                (0x398)
#define DSP2_BLBACK_LUMA_WGT20_PRE                               DSP2_BLBACK_LUMA_WGT20_PRE
#define DSP2_BLBACK_LUMA_WGT20_PRE_POS                           (0U)
#define DSP2_BLBACK_LUMA_WGT20_PRE_LEN                           (10U)
#define DSP2_BLBACK_LUMA_WGT20_PRE_MSK                           (((1U<<DSP2_BLBACK_LUMA_WGT20_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT20_PRE_POS)
#define DSP2_BLBACK_LUMA_WGT20_PRE_UMSK                          (~(((1U<<DSP2_BLBACK_LUMA_WGT20_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT20_PRE_POS))
#define DSP2_BLBACK_LUMA_WGT21_PRE                               DSP2_BLBACK_LUMA_WGT21_PRE
#define DSP2_BLBACK_LUMA_WGT21_PRE_POS                           (16U)
#define DSP2_BLBACK_LUMA_WGT21_PRE_LEN                           (10U)
#define DSP2_BLBACK_LUMA_WGT21_PRE_MSK                           (((1U<<DSP2_BLBACK_LUMA_WGT21_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT21_PRE_POS)
#define DSP2_BLBACK_LUMA_WGT21_PRE_UMSK                          (~(((1U<<DSP2_BLBACK_LUMA_WGT21_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT21_PRE_POS))

/* 0x39C : BLEE_F */
#define DSP2_BLBACK_BLEE_F_OFFSET                                (0x39C)
#define DSP2_BLBACK_LUMA_WGT22_PRE                               DSP2_BLBACK_LUMA_WGT22_PRE
#define DSP2_BLBACK_LUMA_WGT22_PRE_POS                           (0U)
#define DSP2_BLBACK_LUMA_WGT22_PRE_LEN                           (10U)
#define DSP2_BLBACK_LUMA_WGT22_PRE_MSK                           (((1U<<DSP2_BLBACK_LUMA_WGT22_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT22_PRE_POS)
#define DSP2_BLBACK_LUMA_WGT22_PRE_UMSK                          (~(((1U<<DSP2_BLBACK_LUMA_WGT22_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT22_PRE_POS))
#define DSP2_BLBACK_LUMA_WGT23_PRE                               DSP2_BLBACK_LUMA_WGT23_PRE
#define DSP2_BLBACK_LUMA_WGT23_PRE_POS                           (16U)
#define DSP2_BLBACK_LUMA_WGT23_PRE_LEN                           (10U)
#define DSP2_BLBACK_LUMA_WGT23_PRE_MSK                           (((1U<<DSP2_BLBACK_LUMA_WGT23_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT23_PRE_POS)
#define DSP2_BLBACK_LUMA_WGT23_PRE_UMSK                          (~(((1U<<DSP2_BLBACK_LUMA_WGT23_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT23_PRE_POS))

/* 0x3A0 : BLEE_10 */
#define DSP2_BLBACK_BLEE_10_OFFSET                               (0x3A0)
#define DSP2_BLBACK_LUMA_WGT24_PRE                               DSP2_BLBACK_LUMA_WGT24_PRE
#define DSP2_BLBACK_LUMA_WGT24_PRE_POS                           (0U)
#define DSP2_BLBACK_LUMA_WGT24_PRE_LEN                           (10U)
#define DSP2_BLBACK_LUMA_WGT24_PRE_MSK                           (((1U<<DSP2_BLBACK_LUMA_WGT24_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT24_PRE_POS)
#define DSP2_BLBACK_LUMA_WGT24_PRE_UMSK                          (~(((1U<<DSP2_BLBACK_LUMA_WGT24_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT24_PRE_POS))
#define DSP2_BLBACK_LUMA_WGT25_PRE                               DSP2_BLBACK_LUMA_WGT25_PRE
#define DSP2_BLBACK_LUMA_WGT25_PRE_POS                           (16U)
#define DSP2_BLBACK_LUMA_WGT25_PRE_LEN                           (10U)
#define DSP2_BLBACK_LUMA_WGT25_PRE_MSK                           (((1U<<DSP2_BLBACK_LUMA_WGT25_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT25_PRE_POS)
#define DSP2_BLBACK_LUMA_WGT25_PRE_UMSK                          (~(((1U<<DSP2_BLBACK_LUMA_WGT25_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT25_PRE_POS))

/* 0x3A4 : BLEE_11 */
#define DSP2_BLBACK_BLEE_11_OFFSET                               (0x3A4)
#define DSP2_BLBACK_LUMA_WGT26_PRE                               DSP2_BLBACK_LUMA_WGT26_PRE
#define DSP2_BLBACK_LUMA_WGT26_PRE_POS                           (0U)
#define DSP2_BLBACK_LUMA_WGT26_PRE_LEN                           (10U)
#define DSP2_BLBACK_LUMA_WGT26_PRE_MSK                           (((1U<<DSP2_BLBACK_LUMA_WGT26_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT26_PRE_POS)
#define DSP2_BLBACK_LUMA_WGT26_PRE_UMSK                          (~(((1U<<DSP2_BLBACK_LUMA_WGT26_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT26_PRE_POS))
#define DSP2_BLBACK_LUMA_WGT27_PRE                               DSP2_BLBACK_LUMA_WGT27_PRE
#define DSP2_BLBACK_LUMA_WGT27_PRE_POS                           (16U)
#define DSP2_BLBACK_LUMA_WGT27_PRE_LEN                           (10U)
#define DSP2_BLBACK_LUMA_WGT27_PRE_MSK                           (((1U<<DSP2_BLBACK_LUMA_WGT27_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT27_PRE_POS)
#define DSP2_BLBACK_LUMA_WGT27_PRE_UMSK                          (~(((1U<<DSP2_BLBACK_LUMA_WGT27_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT27_PRE_POS))

/* 0x3A8 : BLEE_12 */
#define DSP2_BLBACK_BLEE_12_OFFSET                               (0x3A8)
#define DSP2_BLBACK_LUMA_WGT28_PRE                               DSP2_BLBACK_LUMA_WGT28_PRE
#define DSP2_BLBACK_LUMA_WGT28_PRE_POS                           (0U)
#define DSP2_BLBACK_LUMA_WGT28_PRE_LEN                           (10U)
#define DSP2_BLBACK_LUMA_WGT28_PRE_MSK                           (((1U<<DSP2_BLBACK_LUMA_WGT28_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT28_PRE_POS)
#define DSP2_BLBACK_LUMA_WGT28_PRE_UMSK                          (~(((1U<<DSP2_BLBACK_LUMA_WGT28_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT28_PRE_POS))
#define DSP2_BLBACK_LUMA_WGT29_PRE                               DSP2_BLBACK_LUMA_WGT29_PRE
#define DSP2_BLBACK_LUMA_WGT29_PRE_POS                           (16U)
#define DSP2_BLBACK_LUMA_WGT29_PRE_LEN                           (10U)
#define DSP2_BLBACK_LUMA_WGT29_PRE_MSK                           (((1U<<DSP2_BLBACK_LUMA_WGT29_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT29_PRE_POS)
#define DSP2_BLBACK_LUMA_WGT29_PRE_UMSK                          (~(((1U<<DSP2_BLBACK_LUMA_WGT29_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT29_PRE_POS))

/* 0x3AC : BLEE_13 */
#define DSP2_BLBACK_BLEE_13_OFFSET                               (0x3AC)
#define DSP2_BLBACK_LUMA_WGT30_PRE                               DSP2_BLBACK_LUMA_WGT30_PRE
#define DSP2_BLBACK_LUMA_WGT30_PRE_POS                           (0U)
#define DSP2_BLBACK_LUMA_WGT30_PRE_LEN                           (10U)
#define DSP2_BLBACK_LUMA_WGT30_PRE_MSK                           (((1U<<DSP2_BLBACK_LUMA_WGT30_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT30_PRE_POS)
#define DSP2_BLBACK_LUMA_WGT30_PRE_UMSK                          (~(((1U<<DSP2_BLBACK_LUMA_WGT30_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT30_PRE_POS))
#define DSP2_BLBACK_LUMA_WGT31_PRE                               DSP2_BLBACK_LUMA_WGT31_PRE
#define DSP2_BLBACK_LUMA_WGT31_PRE_POS                           (16U)
#define DSP2_BLBACK_LUMA_WGT31_PRE_LEN                           (10U)
#define DSP2_BLBACK_LUMA_WGT31_PRE_MSK                           (((1U<<DSP2_BLBACK_LUMA_WGT31_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT31_PRE_POS)
#define DSP2_BLBACK_LUMA_WGT31_PRE_UMSK                          (~(((1U<<DSP2_BLBACK_LUMA_WGT31_PRE_LEN)-1)<<DSP2_BLBACK_LUMA_WGT31_PRE_POS))

/* 0x3B0 : CS1 */
#define DSP2_BLBACK_CS1_OFFSET                                   (0x3B0)
#define DSP2_BLBACK_CS1_GREY_TH_PRE                              DSP2_BLBACK_CS1_GREY_TH_PRE
#define DSP2_BLBACK_CS1_GREY_TH_PRE_POS                          (0U)
#define DSP2_BLBACK_CS1_GREY_TH_PRE_LEN                          (4U)
#define DSP2_BLBACK_CS1_GREY_TH_PRE_MSK                          (((1U<<DSP2_BLBACK_CS1_GREY_TH_PRE_LEN)-1)<<DSP2_BLBACK_CS1_GREY_TH_PRE_POS)
#define DSP2_BLBACK_CS1_GREY_TH_PRE_UMSK                         (~(((1U<<DSP2_BLBACK_CS1_GREY_TH_PRE_LEN)-1)<<DSP2_BLBACK_CS1_GREY_TH_PRE_POS))
#define DSP2_BLBACK_CS1_ENABLE_PRE                               DSP2_BLBACK_CS1_ENABLE_PRE
#define DSP2_BLBACK_CS1_ENABLE_PRE_POS                           (4U)
#define DSP2_BLBACK_CS1_ENABLE_PRE_LEN                           (1U)
#define DSP2_BLBACK_CS1_ENABLE_PRE_MSK                           (((1U<<DSP2_BLBACK_CS1_ENABLE_PRE_LEN)-1)<<DSP2_BLBACK_CS1_ENABLE_PRE_POS)
#define DSP2_BLBACK_CS1_ENABLE_PRE_UMSK                          (~(((1U<<DSP2_BLBACK_CS1_ENABLE_PRE_LEN)-1)<<DSP2_BLBACK_CS1_ENABLE_PRE_POS))
#define DSP2_BLBACK_CS1_WEIGHT_PRE                               DSP2_BLBACK_CS1_WEIGHT_PRE
#define DSP2_BLBACK_CS1_WEIGHT_PRE_POS                           (8U)
#define DSP2_BLBACK_CS1_WEIGHT_PRE_LEN                           (5U)
#define DSP2_BLBACK_CS1_WEIGHT_PRE_MSK                           (((1U<<DSP2_BLBACK_CS1_WEIGHT_PRE_LEN)-1)<<DSP2_BLBACK_CS1_WEIGHT_PRE_POS)
#define DSP2_BLBACK_CS1_WEIGHT_PRE_UMSK                          (~(((1U<<DSP2_BLBACK_CS1_WEIGHT_PRE_LEN)-1)<<DSP2_BLBACK_CS1_WEIGHT_PRE_POS))
#define DSP2_BLBACK_CS1_GAIN_PRE                                 DSP2_BLBACK_CS1_GAIN_PRE
#define DSP2_BLBACK_CS1_GAIN_PRE_POS                             (16U)
#define DSP2_BLBACK_CS1_GAIN_PRE_LEN                             (9U)
#define DSP2_BLBACK_CS1_GAIN_PRE_MSK                             (((1U<<DSP2_BLBACK_CS1_GAIN_PRE_LEN)-1)<<DSP2_BLBACK_CS1_GAIN_PRE_POS)
#define DSP2_BLBACK_CS1_GAIN_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CS1_GAIN_PRE_LEN)-1)<<DSP2_BLBACK_CS1_GAIN_PRE_POS))

/* 0x3B4 : CS2 */
#define DSP2_BLBACK_CS2_OFFSET                                   (0x3B4)
#define DSP2_BLBACK_CS2_GREY_TH_PRE                              DSP2_BLBACK_CS2_GREY_TH_PRE
#define DSP2_BLBACK_CS2_GREY_TH_PRE_POS                          (0U)
#define DSP2_BLBACK_CS2_GREY_TH_PRE_LEN                          (4U)
#define DSP2_BLBACK_CS2_GREY_TH_PRE_MSK                          (((1U<<DSP2_BLBACK_CS2_GREY_TH_PRE_LEN)-1)<<DSP2_BLBACK_CS2_GREY_TH_PRE_POS)
#define DSP2_BLBACK_CS2_GREY_TH_PRE_UMSK                         (~(((1U<<DSP2_BLBACK_CS2_GREY_TH_PRE_LEN)-1)<<DSP2_BLBACK_CS2_GREY_TH_PRE_POS))
#define DSP2_BLBACK_CS2_ENABLE_PRE                               DSP2_BLBACK_CS2_ENABLE_PRE
#define DSP2_BLBACK_CS2_ENABLE_PRE_POS                           (4U)
#define DSP2_BLBACK_CS2_ENABLE_PRE_LEN                           (1U)
#define DSP2_BLBACK_CS2_ENABLE_PRE_MSK                           (((1U<<DSP2_BLBACK_CS2_ENABLE_PRE_LEN)-1)<<DSP2_BLBACK_CS2_ENABLE_PRE_POS)
#define DSP2_BLBACK_CS2_ENABLE_PRE_UMSK                          (~(((1U<<DSP2_BLBACK_CS2_ENABLE_PRE_LEN)-1)<<DSP2_BLBACK_CS2_ENABLE_PRE_POS))
#define DSP2_BLBACK_CS2_WEIGHT_PRE                               DSP2_BLBACK_CS2_WEIGHT_PRE
#define DSP2_BLBACK_CS2_WEIGHT_PRE_POS                           (8U)
#define DSP2_BLBACK_CS2_WEIGHT_PRE_LEN                           (5U)
#define DSP2_BLBACK_CS2_WEIGHT_PRE_MSK                           (((1U<<DSP2_BLBACK_CS2_WEIGHT_PRE_LEN)-1)<<DSP2_BLBACK_CS2_WEIGHT_PRE_POS)
#define DSP2_BLBACK_CS2_WEIGHT_PRE_UMSK                          (~(((1U<<DSP2_BLBACK_CS2_WEIGHT_PRE_LEN)-1)<<DSP2_BLBACK_CS2_WEIGHT_PRE_POS))
#define DSP2_BLBACK_CS2_GAIN_PRE                                 DSP2_BLBACK_CS2_GAIN_PRE
#define DSP2_BLBACK_CS2_GAIN_PRE_POS                             (16U)
#define DSP2_BLBACK_CS2_GAIN_PRE_LEN                             (9U)
#define DSP2_BLBACK_CS2_GAIN_PRE_MSK                             (((1U<<DSP2_BLBACK_CS2_GAIN_PRE_LEN)-1)<<DSP2_BLBACK_CS2_GAIN_PRE_POS)
#define DSP2_BLBACK_CS2_GAIN_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CS2_GAIN_PRE_LEN)-1)<<DSP2_BLBACK_CS2_GAIN_PRE_POS))

/* 0x3FC : DUMMY_CTRL */
#define DSP2_BLBACK_DUMMY_CTRL_OFFSET                            (0x3FC)
#define DSP2_BLBACK_REG_BL444TO422_EN_W                          DSP2_BLBACK_REG_BL444TO422_EN_W
#define DSP2_BLBACK_REG_BL444TO422_EN_W_POS                      (0U)
#define DSP2_BLBACK_REG_BL444TO422_EN_W_LEN                      (1U)
#define DSP2_BLBACK_REG_BL444TO422_EN_W_MSK                      (((1U<<DSP2_BLBACK_REG_BL444TO422_EN_W_LEN)-1)<<DSP2_BLBACK_REG_BL444TO422_EN_W_POS)
#define DSP2_BLBACK_REG_BL444TO422_EN_W_UMSK                     (~(((1U<<DSP2_BLBACK_REG_BL444TO422_EN_W_LEN)-1)<<DSP2_BLBACK_REG_BL444TO422_EN_W_POS))

/* 0x900 : WDR_0 */
#define DSP2_BLBACK_WDR_0_OFFSET                                 (0x900)
#define DSP2_BLBACK_WDR_EN_PRE                                   DSP2_BLBACK_WDR_EN_PRE
#define DSP2_BLBACK_WDR_EN_PRE_POS                               (0U)
#define DSP2_BLBACK_WDR_EN_PRE_LEN                               (1U)
#define DSP2_BLBACK_WDR_EN_PRE_MSK                               (((1U<<DSP2_BLBACK_WDR_EN_PRE_LEN)-1)<<DSP2_BLBACK_WDR_EN_PRE_POS)
#define DSP2_BLBACK_WDR_EN_PRE_UMSK                              (~(((1U<<DSP2_BLBACK_WDR_EN_PRE_LEN)-1)<<DSP2_BLBACK_WDR_EN_PRE_POS))
#define DSP2_BLBACK_BLWDR_BUF_IDX_R                              DSP2_BLBACK_BLWDR_BUF_IDX_R
#define DSP2_BLBACK_BLWDR_BUF_IDX_R_POS                          (1U)
#define DSP2_BLBACK_BLWDR_BUF_IDX_R_LEN                          (1U)
#define DSP2_BLBACK_BLWDR_BUF_IDX_R_MSK                          (((1U<<DSP2_BLBACK_BLWDR_BUF_IDX_R_LEN)-1)<<DSP2_BLBACK_BLWDR_BUF_IDX_R_POS)
#define DSP2_BLBACK_BLWDR_BUF_IDX_R_UMSK                         (~(((1U<<DSP2_BLBACK_BLWDR_BUF_IDX_R_LEN)-1)<<DSP2_BLBACK_BLWDR_BUF_IDX_R_POS))
#define DSP2_BLBACK_BLWDR_W_CNT_R                                DSP2_BLBACK_BLWDR_W_CNT_R
#define DSP2_BLBACK_BLWDR_W_CNT_R_POS                            (4U)
#define DSP2_BLBACK_BLWDR_W_CNT_R_LEN                            (5U)
#define DSP2_BLBACK_BLWDR_W_CNT_R_MSK                            (((1U<<DSP2_BLBACK_BLWDR_W_CNT_R_LEN)-1)<<DSP2_BLBACK_BLWDR_W_CNT_R_POS)
#define DSP2_BLBACK_BLWDR_W_CNT_R_UMSK                           (~(((1U<<DSP2_BLBACK_BLWDR_W_CNT_R_LEN)-1)<<DSP2_BLBACK_BLWDR_W_CNT_R_POS))
#define DSP2_BLBACK_WDR_CS_GAIN_PRE                              DSP2_BLBACK_WDR_CS_GAIN_PRE
#define DSP2_BLBACK_WDR_CS_GAIN_PRE_POS                          (16U)
#define DSP2_BLBACK_WDR_CS_GAIN_PRE_LEN                          (13U)
#define DSP2_BLBACK_WDR_CS_GAIN_PRE_MSK                          (((1U<<DSP2_BLBACK_WDR_CS_GAIN_PRE_LEN)-1)<<DSP2_BLBACK_WDR_CS_GAIN_PRE_POS)
#define DSP2_BLBACK_WDR_CS_GAIN_PRE_UMSK                         (~(((1U<<DSP2_BLBACK_WDR_CS_GAIN_PRE_LEN)-1)<<DSP2_BLBACK_WDR_CS_GAIN_PRE_POS))

/* 0x904 : WDR_CS_0 */
#define DSP2_BLBACK_WDR_CS_0_OFFSET                              (0x904)
#define DSP2_BLBACK_WDR_CS_EN_PRE                                DSP2_BLBACK_WDR_CS_EN_PRE
#define DSP2_BLBACK_WDR_CS_EN_PRE_POS                            (0U)
#define DSP2_BLBACK_WDR_CS_EN_PRE_LEN                            (1U)
#define DSP2_BLBACK_WDR_CS_EN_PRE_MSK                            (((1U<<DSP2_BLBACK_WDR_CS_EN_PRE_LEN)-1)<<DSP2_BLBACK_WDR_CS_EN_PRE_POS)
#define DSP2_BLBACK_WDR_CS_EN_PRE_UMSK                           (~(((1U<<DSP2_BLBACK_WDR_CS_EN_PRE_LEN)-1)<<DSP2_BLBACK_WDR_CS_EN_PRE_POS))
#define DSP2_BLBACK_WDR_CS_WEIGHT_PRE                            DSP2_BLBACK_WDR_CS_WEIGHT_PRE
#define DSP2_BLBACK_WDR_CS_WEIGHT_PRE_POS                        (8U)
#define DSP2_BLBACK_WDR_CS_WEIGHT_PRE_LEN                        (5U)
#define DSP2_BLBACK_WDR_CS_WEIGHT_PRE_MSK                        (((1U<<DSP2_BLBACK_WDR_CS_WEIGHT_PRE_LEN)-1)<<DSP2_BLBACK_WDR_CS_WEIGHT_PRE_POS)
#define DSP2_BLBACK_WDR_CS_WEIGHT_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_WDR_CS_WEIGHT_PRE_LEN)-1)<<DSP2_BLBACK_WDR_CS_WEIGHT_PRE_POS))
#define DSP2_BLBACK_WDR_CS_GREY_TH_PRE                           DSP2_BLBACK_WDR_CS_GREY_TH_PRE
#define DSP2_BLBACK_WDR_CS_GREY_TH_PRE_POS                       (16U)
#define DSP2_BLBACK_WDR_CS_GREY_TH_PRE_LEN                       (8U)
#define DSP2_BLBACK_WDR_CS_GREY_TH_PRE_MSK                       (((1U<<DSP2_BLBACK_WDR_CS_GREY_TH_PRE_LEN)-1)<<DSP2_BLBACK_WDR_CS_GREY_TH_PRE_POS)
#define DSP2_BLBACK_WDR_CS_GREY_TH_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_WDR_CS_GREY_TH_PRE_LEN)-1)<<DSP2_BLBACK_WDR_CS_GREY_TH_PRE_POS))

/* 0x908 : WDR_HIST_1 */
#define DSP2_BLBACK_WDR_HIST_1_OFFSET                            (0x908)
#define DSP2_BLBACK_HIST_ROI0_EN_PRE                             DSP2_BLBACK_HIST_ROI0_EN_PRE
#define DSP2_BLBACK_HIST_ROI0_EN_PRE_POS                         (0U)
#define DSP2_BLBACK_HIST_ROI0_EN_PRE_LEN                         (1U)
#define DSP2_BLBACK_HIST_ROI0_EN_PRE_MSK                         (((1U<<DSP2_BLBACK_HIST_ROI0_EN_PRE_LEN)-1)<<DSP2_BLBACK_HIST_ROI0_EN_PRE_POS)
#define DSP2_BLBACK_HIST_ROI0_EN_PRE_UMSK                        (~(((1U<<DSP2_BLBACK_HIST_ROI0_EN_PRE_LEN)-1)<<DSP2_BLBACK_HIST_ROI0_EN_PRE_POS))
#define DSP2_BLBACK_HIST_ROI0_WEIGHT_PRE                         DSP2_BLBACK_HIST_ROI0_WEIGHT_PRE
#define DSP2_BLBACK_HIST_ROI0_WEIGHT_PRE_POS                     (8U)
#define DSP2_BLBACK_HIST_ROI0_WEIGHT_PRE_LEN                     (4U)
#define DSP2_BLBACK_HIST_ROI0_WEIGHT_PRE_MSK                     (((1U<<DSP2_BLBACK_HIST_ROI0_WEIGHT_PRE_LEN)-1)<<DSP2_BLBACK_HIST_ROI0_WEIGHT_PRE_POS)
#define DSP2_BLBACK_HIST_ROI0_WEIGHT_PRE_UMSK                    (~(((1U<<DSP2_BLBACK_HIST_ROI0_WEIGHT_PRE_LEN)-1)<<DSP2_BLBACK_HIST_ROI0_WEIGHT_PRE_POS))
#define DSP2_BLBACK_HIST_ROI1_EN_PRE                             DSP2_BLBACK_HIST_ROI1_EN_PRE
#define DSP2_BLBACK_HIST_ROI1_EN_PRE_POS                         (16U)
#define DSP2_BLBACK_HIST_ROI1_EN_PRE_LEN                         (1U)
#define DSP2_BLBACK_HIST_ROI1_EN_PRE_MSK                         (((1U<<DSP2_BLBACK_HIST_ROI1_EN_PRE_LEN)-1)<<DSP2_BLBACK_HIST_ROI1_EN_PRE_POS)
#define DSP2_BLBACK_HIST_ROI1_EN_PRE_UMSK                        (~(((1U<<DSP2_BLBACK_HIST_ROI1_EN_PRE_LEN)-1)<<DSP2_BLBACK_HIST_ROI1_EN_PRE_POS))
#define DSP2_BLBACK_HIST_ROI1_WEIGHT_PRE                         DSP2_BLBACK_HIST_ROI1_WEIGHT_PRE
#define DSP2_BLBACK_HIST_ROI1_WEIGHT_PRE_POS                     (24U)
#define DSP2_BLBACK_HIST_ROI1_WEIGHT_PRE_LEN                     (4U)
#define DSP2_BLBACK_HIST_ROI1_WEIGHT_PRE_MSK                     (((1U<<DSP2_BLBACK_HIST_ROI1_WEIGHT_PRE_LEN)-1)<<DSP2_BLBACK_HIST_ROI1_WEIGHT_PRE_POS)
#define DSP2_BLBACK_HIST_ROI1_WEIGHT_PRE_UMSK                    (~(((1U<<DSP2_BLBACK_HIST_ROI1_WEIGHT_PRE_LEN)-1)<<DSP2_BLBACK_HIST_ROI1_WEIGHT_PRE_POS))

/* 0x90C : WDR_HIST_2 */
#define DSP2_BLBACK_WDR_HIST_2_OFFSET                            (0x90C)
#define DSP2_BLBACK_HIST_ROI2_EN_PRE                             DSP2_BLBACK_HIST_ROI2_EN_PRE
#define DSP2_BLBACK_HIST_ROI2_EN_PRE_POS                         (0U)
#define DSP2_BLBACK_HIST_ROI2_EN_PRE_LEN                         (1U)
#define DSP2_BLBACK_HIST_ROI2_EN_PRE_MSK                         (((1U<<DSP2_BLBACK_HIST_ROI2_EN_PRE_LEN)-1)<<DSP2_BLBACK_HIST_ROI2_EN_PRE_POS)
#define DSP2_BLBACK_HIST_ROI2_EN_PRE_UMSK                        (~(((1U<<DSP2_BLBACK_HIST_ROI2_EN_PRE_LEN)-1)<<DSP2_BLBACK_HIST_ROI2_EN_PRE_POS))
#define DSP2_BLBACK_HIST_ROI2_WEIGHT_PRE                         DSP2_BLBACK_HIST_ROI2_WEIGHT_PRE
#define DSP2_BLBACK_HIST_ROI2_WEIGHT_PRE_POS                     (8U)
#define DSP2_BLBACK_HIST_ROI2_WEIGHT_PRE_LEN                     (4U)
#define DSP2_BLBACK_HIST_ROI2_WEIGHT_PRE_MSK                     (((1U<<DSP2_BLBACK_HIST_ROI2_WEIGHT_PRE_LEN)-1)<<DSP2_BLBACK_HIST_ROI2_WEIGHT_PRE_POS)
#define DSP2_BLBACK_HIST_ROI2_WEIGHT_PRE_UMSK                    (~(((1U<<DSP2_BLBACK_HIST_ROI2_WEIGHT_PRE_LEN)-1)<<DSP2_BLBACK_HIST_ROI2_WEIGHT_PRE_POS))
#define DSP2_BLBACK_HIST_ROI3_EN_PRE                             DSP2_BLBACK_HIST_ROI3_EN_PRE
#define DSP2_BLBACK_HIST_ROI3_EN_PRE_POS                         (16U)
#define DSP2_BLBACK_HIST_ROI3_EN_PRE_LEN                         (1U)
#define DSP2_BLBACK_HIST_ROI3_EN_PRE_MSK                         (((1U<<DSP2_BLBACK_HIST_ROI3_EN_PRE_LEN)-1)<<DSP2_BLBACK_HIST_ROI3_EN_PRE_POS)
#define DSP2_BLBACK_HIST_ROI3_EN_PRE_UMSK                        (~(((1U<<DSP2_BLBACK_HIST_ROI3_EN_PRE_LEN)-1)<<DSP2_BLBACK_HIST_ROI3_EN_PRE_POS))
#define DSP2_BLBACK_HIST_ROI3_WEIGHT_PRE                         DSP2_BLBACK_HIST_ROI3_WEIGHT_PRE
#define DSP2_BLBACK_HIST_ROI3_WEIGHT_PRE_POS                     (24U)
#define DSP2_BLBACK_HIST_ROI3_WEIGHT_PRE_LEN                     (4U)
#define DSP2_BLBACK_HIST_ROI3_WEIGHT_PRE_MSK                     (((1U<<DSP2_BLBACK_HIST_ROI3_WEIGHT_PRE_LEN)-1)<<DSP2_BLBACK_HIST_ROI3_WEIGHT_PRE_POS)
#define DSP2_BLBACK_HIST_ROI3_WEIGHT_PRE_UMSK                    (~(((1U<<DSP2_BLBACK_HIST_ROI3_WEIGHT_PRE_LEN)-1)<<DSP2_BLBACK_HIST_ROI3_WEIGHT_PRE_POS))

/* 0x910 : WDR_HIST_3 */
#define DSP2_BLBACK_WDR_HIST_3_OFFSET                            (0x910)
#define DSP2_BLBACK_HIST_ROI4_EN_PRE                             DSP2_BLBACK_HIST_ROI4_EN_PRE
#define DSP2_BLBACK_HIST_ROI4_EN_PRE_POS                         (0U)
#define DSP2_BLBACK_HIST_ROI4_EN_PRE_LEN                         (1U)
#define DSP2_BLBACK_HIST_ROI4_EN_PRE_MSK                         (((1U<<DSP2_BLBACK_HIST_ROI4_EN_PRE_LEN)-1)<<DSP2_BLBACK_HIST_ROI4_EN_PRE_POS)
#define DSP2_BLBACK_HIST_ROI4_EN_PRE_UMSK                        (~(((1U<<DSP2_BLBACK_HIST_ROI4_EN_PRE_LEN)-1)<<DSP2_BLBACK_HIST_ROI4_EN_PRE_POS))
#define DSP2_BLBACK_HIST_ROI4_WEIGHT_PRE                         DSP2_BLBACK_HIST_ROI4_WEIGHT_PRE
#define DSP2_BLBACK_HIST_ROI4_WEIGHT_PRE_POS                     (8U)
#define DSP2_BLBACK_HIST_ROI4_WEIGHT_PRE_LEN                     (4U)
#define DSP2_BLBACK_HIST_ROI4_WEIGHT_PRE_MSK                     (((1U<<DSP2_BLBACK_HIST_ROI4_WEIGHT_PRE_LEN)-1)<<DSP2_BLBACK_HIST_ROI4_WEIGHT_PRE_POS)
#define DSP2_BLBACK_HIST_ROI4_WEIGHT_PRE_UMSK                    (~(((1U<<DSP2_BLBACK_HIST_ROI4_WEIGHT_PRE_LEN)-1)<<DSP2_BLBACK_HIST_ROI4_WEIGHT_PRE_POS))
#define DSP2_BLBACK_HIST_ROI5_EN_PRE                             DSP2_BLBACK_HIST_ROI5_EN_PRE
#define DSP2_BLBACK_HIST_ROI5_EN_PRE_POS                         (16U)
#define DSP2_BLBACK_HIST_ROI5_EN_PRE_LEN                         (1U)
#define DSP2_BLBACK_HIST_ROI5_EN_PRE_MSK                         (((1U<<DSP2_BLBACK_HIST_ROI5_EN_PRE_LEN)-1)<<DSP2_BLBACK_HIST_ROI5_EN_PRE_POS)
#define DSP2_BLBACK_HIST_ROI5_EN_PRE_UMSK                        (~(((1U<<DSP2_BLBACK_HIST_ROI5_EN_PRE_LEN)-1)<<DSP2_BLBACK_HIST_ROI5_EN_PRE_POS))
#define DSP2_BLBACK_HIST_ROI5_WEIGHT_PRE                         DSP2_BLBACK_HIST_ROI5_WEIGHT_PRE
#define DSP2_BLBACK_HIST_ROI5_WEIGHT_PRE_POS                     (24U)
#define DSP2_BLBACK_HIST_ROI5_WEIGHT_PRE_LEN                     (4U)
#define DSP2_BLBACK_HIST_ROI5_WEIGHT_PRE_MSK                     (((1U<<DSP2_BLBACK_HIST_ROI5_WEIGHT_PRE_LEN)-1)<<DSP2_BLBACK_HIST_ROI5_WEIGHT_PRE_POS)
#define DSP2_BLBACK_HIST_ROI5_WEIGHT_PRE_UMSK                    (~(((1U<<DSP2_BLBACK_HIST_ROI5_WEIGHT_PRE_LEN)-1)<<DSP2_BLBACK_HIST_ROI5_WEIGHT_PRE_POS))

/* 0x914 : WDR_HIST_4 */
#define DSP2_BLBACK_WDR_HIST_4_OFFSET                            (0x914)
#define DSP2_BLBACK_HIST_ROI6_EN_PRE                             DSP2_BLBACK_HIST_ROI6_EN_PRE
#define DSP2_BLBACK_HIST_ROI6_EN_PRE_POS                         (0U)
#define DSP2_BLBACK_HIST_ROI6_EN_PRE_LEN                         (1U)
#define DSP2_BLBACK_HIST_ROI6_EN_PRE_MSK                         (((1U<<DSP2_BLBACK_HIST_ROI6_EN_PRE_LEN)-1)<<DSP2_BLBACK_HIST_ROI6_EN_PRE_POS)
#define DSP2_BLBACK_HIST_ROI6_EN_PRE_UMSK                        (~(((1U<<DSP2_BLBACK_HIST_ROI6_EN_PRE_LEN)-1)<<DSP2_BLBACK_HIST_ROI6_EN_PRE_POS))
#define DSP2_BLBACK_HIST_ROI6_WEIGHT_PRE                         DSP2_BLBACK_HIST_ROI6_WEIGHT_PRE
#define DSP2_BLBACK_HIST_ROI6_WEIGHT_PRE_POS                     (8U)
#define DSP2_BLBACK_HIST_ROI6_WEIGHT_PRE_LEN                     (4U)
#define DSP2_BLBACK_HIST_ROI6_WEIGHT_PRE_MSK                     (((1U<<DSP2_BLBACK_HIST_ROI6_WEIGHT_PRE_LEN)-1)<<DSP2_BLBACK_HIST_ROI6_WEIGHT_PRE_POS)
#define DSP2_BLBACK_HIST_ROI6_WEIGHT_PRE_UMSK                    (~(((1U<<DSP2_BLBACK_HIST_ROI6_WEIGHT_PRE_LEN)-1)<<DSP2_BLBACK_HIST_ROI6_WEIGHT_PRE_POS))
#define DSP2_BLBACK_HIST_ROI7_EN_PRE                             DSP2_BLBACK_HIST_ROI7_EN_PRE
#define DSP2_BLBACK_HIST_ROI7_EN_PRE_POS                         (16U)
#define DSP2_BLBACK_HIST_ROI7_EN_PRE_LEN                         (1U)
#define DSP2_BLBACK_HIST_ROI7_EN_PRE_MSK                         (((1U<<DSP2_BLBACK_HIST_ROI7_EN_PRE_LEN)-1)<<DSP2_BLBACK_HIST_ROI7_EN_PRE_POS)
#define DSP2_BLBACK_HIST_ROI7_EN_PRE_UMSK                        (~(((1U<<DSP2_BLBACK_HIST_ROI7_EN_PRE_LEN)-1)<<DSP2_BLBACK_HIST_ROI7_EN_PRE_POS))
#define DSP2_BLBACK_HIST_ROI7_WEIGHT_PRE                         DSP2_BLBACK_HIST_ROI7_WEIGHT_PRE
#define DSP2_BLBACK_HIST_ROI7_WEIGHT_PRE_POS                     (24U)
#define DSP2_BLBACK_HIST_ROI7_WEIGHT_PRE_LEN                     (4U)
#define DSP2_BLBACK_HIST_ROI7_WEIGHT_PRE_MSK                     (((1U<<DSP2_BLBACK_HIST_ROI7_WEIGHT_PRE_LEN)-1)<<DSP2_BLBACK_HIST_ROI7_WEIGHT_PRE_POS)
#define DSP2_BLBACK_HIST_ROI7_WEIGHT_PRE_UMSK                    (~(((1U<<DSP2_BLBACK_HIST_ROI7_WEIGHT_PRE_LEN)-1)<<DSP2_BLBACK_HIST_ROI7_WEIGHT_PRE_POS))

/* 0x918 : WDR_HIST_5 */
#define DSP2_BLBACK_WDR_HIST_5_OFFSET                            (0x918)
#define DSP2_BLBACK_HIST_X0_MAX_PRE                              DSP2_BLBACK_HIST_X0_MAX_PRE
#define DSP2_BLBACK_HIST_X0_MAX_PRE_POS                          (0U)
#define DSP2_BLBACK_HIST_X0_MAX_PRE_LEN                          (11U)
#define DSP2_BLBACK_HIST_X0_MAX_PRE_MSK                          (((1U<<DSP2_BLBACK_HIST_X0_MAX_PRE_LEN)-1)<<DSP2_BLBACK_HIST_X0_MAX_PRE_POS)
#define DSP2_BLBACK_HIST_X0_MAX_PRE_UMSK                         (~(((1U<<DSP2_BLBACK_HIST_X0_MAX_PRE_LEN)-1)<<DSP2_BLBACK_HIST_X0_MAX_PRE_POS))
#define DSP2_BLBACK_HIST_X0_MIN_PRE                              DSP2_BLBACK_HIST_X0_MIN_PRE
#define DSP2_BLBACK_HIST_X0_MIN_PRE_POS                          (16U)
#define DSP2_BLBACK_HIST_X0_MIN_PRE_LEN                          (11U)
#define DSP2_BLBACK_HIST_X0_MIN_PRE_MSK                          (((1U<<DSP2_BLBACK_HIST_X0_MIN_PRE_LEN)-1)<<DSP2_BLBACK_HIST_X0_MIN_PRE_POS)
#define DSP2_BLBACK_HIST_X0_MIN_PRE_UMSK                         (~(((1U<<DSP2_BLBACK_HIST_X0_MIN_PRE_LEN)-1)<<DSP2_BLBACK_HIST_X0_MIN_PRE_POS))

/* 0x91C : WDR_HIST_6 */
#define DSP2_BLBACK_WDR_HIST_6_OFFSET                            (0x91C)
#define DSP2_BLBACK_HIST_Y0_MAX_PRE                              DSP2_BLBACK_HIST_Y0_MAX_PRE
#define DSP2_BLBACK_HIST_Y0_MAX_PRE_POS                          (0U)
#define DSP2_BLBACK_HIST_Y0_MAX_PRE_LEN                          (11U)
#define DSP2_BLBACK_HIST_Y0_MAX_PRE_MSK                          (((1U<<DSP2_BLBACK_HIST_Y0_MAX_PRE_LEN)-1)<<DSP2_BLBACK_HIST_Y0_MAX_PRE_POS)
#define DSP2_BLBACK_HIST_Y0_MAX_PRE_UMSK                         (~(((1U<<DSP2_BLBACK_HIST_Y0_MAX_PRE_LEN)-1)<<DSP2_BLBACK_HIST_Y0_MAX_PRE_POS))
#define DSP2_BLBACK_HIST_Y0_MIN_PRE                              DSP2_BLBACK_HIST_Y0_MIN_PRE
#define DSP2_BLBACK_HIST_Y0_MIN_PRE_POS                          (16U)
#define DSP2_BLBACK_HIST_Y0_MIN_PRE_LEN                          (11U)
#define DSP2_BLBACK_HIST_Y0_MIN_PRE_MSK                          (((1U<<DSP2_BLBACK_HIST_Y0_MIN_PRE_LEN)-1)<<DSP2_BLBACK_HIST_Y0_MIN_PRE_POS)
#define DSP2_BLBACK_HIST_Y0_MIN_PRE_UMSK                         (~(((1U<<DSP2_BLBACK_HIST_Y0_MIN_PRE_LEN)-1)<<DSP2_BLBACK_HIST_Y0_MIN_PRE_POS))

/* 0x920 : WDR_HIST_7 */
#define DSP2_BLBACK_WDR_HIST_7_OFFSET                            (0x920)
#define DSP2_BLBACK_HIST_X1_MAX_PRE                              DSP2_BLBACK_HIST_X1_MAX_PRE
#define DSP2_BLBACK_HIST_X1_MAX_PRE_POS                          (0U)
#define DSP2_BLBACK_HIST_X1_MAX_PRE_LEN                          (11U)
#define DSP2_BLBACK_HIST_X1_MAX_PRE_MSK                          (((1U<<DSP2_BLBACK_HIST_X1_MAX_PRE_LEN)-1)<<DSP2_BLBACK_HIST_X1_MAX_PRE_POS)
#define DSP2_BLBACK_HIST_X1_MAX_PRE_UMSK                         (~(((1U<<DSP2_BLBACK_HIST_X1_MAX_PRE_LEN)-1)<<DSP2_BLBACK_HIST_X1_MAX_PRE_POS))
#define DSP2_BLBACK_HIST_X1_MIN_PRE                              DSP2_BLBACK_HIST_X1_MIN_PRE
#define DSP2_BLBACK_HIST_X1_MIN_PRE_POS                          (16U)
#define DSP2_BLBACK_HIST_X1_MIN_PRE_LEN                          (11U)
#define DSP2_BLBACK_HIST_X1_MIN_PRE_MSK                          (((1U<<DSP2_BLBACK_HIST_X1_MIN_PRE_LEN)-1)<<DSP2_BLBACK_HIST_X1_MIN_PRE_POS)
#define DSP2_BLBACK_HIST_X1_MIN_PRE_UMSK                         (~(((1U<<DSP2_BLBACK_HIST_X1_MIN_PRE_LEN)-1)<<DSP2_BLBACK_HIST_X1_MIN_PRE_POS))

/* 0x924 : WDR_HIST_8 */
#define DSP2_BLBACK_WDR_HIST_8_OFFSET                            (0x924)
#define DSP2_BLBACK_HIST_Y1_MAX_PRE                              DSP2_BLBACK_HIST_Y1_MAX_PRE
#define DSP2_BLBACK_HIST_Y1_MAX_PRE_POS                          (0U)
#define DSP2_BLBACK_HIST_Y1_MAX_PRE_LEN                          (11U)
#define DSP2_BLBACK_HIST_Y1_MAX_PRE_MSK                          (((1U<<DSP2_BLBACK_HIST_Y1_MAX_PRE_LEN)-1)<<DSP2_BLBACK_HIST_Y1_MAX_PRE_POS)
#define DSP2_BLBACK_HIST_Y1_MAX_PRE_UMSK                         (~(((1U<<DSP2_BLBACK_HIST_Y1_MAX_PRE_LEN)-1)<<DSP2_BLBACK_HIST_Y1_MAX_PRE_POS))
#define DSP2_BLBACK_HIST_Y1_MIN_PRE                              DSP2_BLBACK_HIST_Y1_MIN_PRE
#define DSP2_BLBACK_HIST_Y1_MIN_PRE_POS                          (16U)
#define DSP2_BLBACK_HIST_Y1_MIN_PRE_LEN                          (11U)
#define DSP2_BLBACK_HIST_Y1_MIN_PRE_MSK                          (((1U<<DSP2_BLBACK_HIST_Y1_MIN_PRE_LEN)-1)<<DSP2_BLBACK_HIST_Y1_MIN_PRE_POS)
#define DSP2_BLBACK_HIST_Y1_MIN_PRE_UMSK                         (~(((1U<<DSP2_BLBACK_HIST_Y1_MIN_PRE_LEN)-1)<<DSP2_BLBACK_HIST_Y1_MIN_PRE_POS))

/* 0x928 : WDR_HIST_9 */
#define DSP2_BLBACK_WDR_HIST_9_OFFSET                            (0x928)
#define DSP2_BLBACK_HIST_X2_MAX_PRE                              DSP2_BLBACK_HIST_X2_MAX_PRE
#define DSP2_BLBACK_HIST_X2_MAX_PRE_POS                          (0U)
#define DSP2_BLBACK_HIST_X2_MAX_PRE_LEN                          (11U)
#define DSP2_BLBACK_HIST_X2_MAX_PRE_MSK                          (((1U<<DSP2_BLBACK_HIST_X2_MAX_PRE_LEN)-1)<<DSP2_BLBACK_HIST_X2_MAX_PRE_POS)
#define DSP2_BLBACK_HIST_X2_MAX_PRE_UMSK                         (~(((1U<<DSP2_BLBACK_HIST_X2_MAX_PRE_LEN)-1)<<DSP2_BLBACK_HIST_X2_MAX_PRE_POS))
#define DSP2_BLBACK_HIST_X2_MIN_PRE                              DSP2_BLBACK_HIST_X2_MIN_PRE
#define DSP2_BLBACK_HIST_X2_MIN_PRE_POS                          (16U)
#define DSP2_BLBACK_HIST_X2_MIN_PRE_LEN                          (11U)
#define DSP2_BLBACK_HIST_X2_MIN_PRE_MSK                          (((1U<<DSP2_BLBACK_HIST_X2_MIN_PRE_LEN)-1)<<DSP2_BLBACK_HIST_X2_MIN_PRE_POS)
#define DSP2_BLBACK_HIST_X2_MIN_PRE_UMSK                         (~(((1U<<DSP2_BLBACK_HIST_X2_MIN_PRE_LEN)-1)<<DSP2_BLBACK_HIST_X2_MIN_PRE_POS))

/* 0x92C : WDR_HIST_10 */
#define DSP2_BLBACK_WDR_HIST_10_OFFSET                           (0x92C)
#define DSP2_BLBACK_HIST_Y2_MAX_PRE                              DSP2_BLBACK_HIST_Y2_MAX_PRE
#define DSP2_BLBACK_HIST_Y2_MAX_PRE_POS                          (0U)
#define DSP2_BLBACK_HIST_Y2_MAX_PRE_LEN                          (11U)
#define DSP2_BLBACK_HIST_Y2_MAX_PRE_MSK                          (((1U<<DSP2_BLBACK_HIST_Y2_MAX_PRE_LEN)-1)<<DSP2_BLBACK_HIST_Y2_MAX_PRE_POS)
#define DSP2_BLBACK_HIST_Y2_MAX_PRE_UMSK                         (~(((1U<<DSP2_BLBACK_HIST_Y2_MAX_PRE_LEN)-1)<<DSP2_BLBACK_HIST_Y2_MAX_PRE_POS))
#define DSP2_BLBACK_HIST_Y2_MIN_PRE                              DSP2_BLBACK_HIST_Y2_MIN_PRE
#define DSP2_BLBACK_HIST_Y2_MIN_PRE_POS                          (16U)
#define DSP2_BLBACK_HIST_Y2_MIN_PRE_LEN                          (11U)
#define DSP2_BLBACK_HIST_Y2_MIN_PRE_MSK                          (((1U<<DSP2_BLBACK_HIST_Y2_MIN_PRE_LEN)-1)<<DSP2_BLBACK_HIST_Y2_MIN_PRE_POS)
#define DSP2_BLBACK_HIST_Y2_MIN_PRE_UMSK                         (~(((1U<<DSP2_BLBACK_HIST_Y2_MIN_PRE_LEN)-1)<<DSP2_BLBACK_HIST_Y2_MIN_PRE_POS))

/* 0x930 : WDR_HIST_11 */
#define DSP2_BLBACK_WDR_HIST_11_OFFSET                           (0x930)
#define DSP2_BLBACK_HIST_X3_MAX_PRE                              DSP2_BLBACK_HIST_X3_MAX_PRE
#define DSP2_BLBACK_HIST_X3_MAX_PRE_POS                          (0U)
#define DSP2_BLBACK_HIST_X3_MAX_PRE_LEN                          (11U)
#define DSP2_BLBACK_HIST_X3_MAX_PRE_MSK                          (((1U<<DSP2_BLBACK_HIST_X3_MAX_PRE_LEN)-1)<<DSP2_BLBACK_HIST_X3_MAX_PRE_POS)
#define DSP2_BLBACK_HIST_X3_MAX_PRE_UMSK                         (~(((1U<<DSP2_BLBACK_HIST_X3_MAX_PRE_LEN)-1)<<DSP2_BLBACK_HIST_X3_MAX_PRE_POS))
#define DSP2_BLBACK_HIST_X3_MIN_PRE                              DSP2_BLBACK_HIST_X3_MIN_PRE
#define DSP2_BLBACK_HIST_X3_MIN_PRE_POS                          (16U)
#define DSP2_BLBACK_HIST_X3_MIN_PRE_LEN                          (11U)
#define DSP2_BLBACK_HIST_X3_MIN_PRE_MSK                          (((1U<<DSP2_BLBACK_HIST_X3_MIN_PRE_LEN)-1)<<DSP2_BLBACK_HIST_X3_MIN_PRE_POS)
#define DSP2_BLBACK_HIST_X3_MIN_PRE_UMSK                         (~(((1U<<DSP2_BLBACK_HIST_X3_MIN_PRE_LEN)-1)<<DSP2_BLBACK_HIST_X3_MIN_PRE_POS))

/* 0x934 : WDR_HIST_12 */
#define DSP2_BLBACK_WDR_HIST_12_OFFSET                           (0x934)
#define DSP2_BLBACK_HIST_Y3_MAX_PRE                              DSP2_BLBACK_HIST_Y3_MAX_PRE
#define DSP2_BLBACK_HIST_Y3_MAX_PRE_POS                          (0U)
#define DSP2_BLBACK_HIST_Y3_MAX_PRE_LEN                          (11U)
#define DSP2_BLBACK_HIST_Y3_MAX_PRE_MSK                          (((1U<<DSP2_BLBACK_HIST_Y3_MAX_PRE_LEN)-1)<<DSP2_BLBACK_HIST_Y3_MAX_PRE_POS)
#define DSP2_BLBACK_HIST_Y3_MAX_PRE_UMSK                         (~(((1U<<DSP2_BLBACK_HIST_Y3_MAX_PRE_LEN)-1)<<DSP2_BLBACK_HIST_Y3_MAX_PRE_POS))
#define DSP2_BLBACK_HIST_Y3_MIN_PRE                              DSP2_BLBACK_HIST_Y3_MIN_PRE
#define DSP2_BLBACK_HIST_Y3_MIN_PRE_POS                          (16U)
#define DSP2_BLBACK_HIST_Y3_MIN_PRE_LEN                          (11U)
#define DSP2_BLBACK_HIST_Y3_MIN_PRE_MSK                          (((1U<<DSP2_BLBACK_HIST_Y3_MIN_PRE_LEN)-1)<<DSP2_BLBACK_HIST_Y3_MIN_PRE_POS)
#define DSP2_BLBACK_HIST_Y3_MIN_PRE_UMSK                         (~(((1U<<DSP2_BLBACK_HIST_Y3_MIN_PRE_LEN)-1)<<DSP2_BLBACK_HIST_Y3_MIN_PRE_POS))

/* 0x938 : WDR_HIST_13 */
#define DSP2_BLBACK_WDR_HIST_13_OFFSET                           (0x938)
#define DSP2_BLBACK_HIST_X4_MAX_PRE                              DSP2_BLBACK_HIST_X4_MAX_PRE
#define DSP2_BLBACK_HIST_X4_MAX_PRE_POS                          (0U)
#define DSP2_BLBACK_HIST_X4_MAX_PRE_LEN                          (11U)
#define DSP2_BLBACK_HIST_X4_MAX_PRE_MSK                          (((1U<<DSP2_BLBACK_HIST_X4_MAX_PRE_LEN)-1)<<DSP2_BLBACK_HIST_X4_MAX_PRE_POS)
#define DSP2_BLBACK_HIST_X4_MAX_PRE_UMSK                         (~(((1U<<DSP2_BLBACK_HIST_X4_MAX_PRE_LEN)-1)<<DSP2_BLBACK_HIST_X4_MAX_PRE_POS))
#define DSP2_BLBACK_HIST_X4_MIN_PRE                              DSP2_BLBACK_HIST_X4_MIN_PRE
#define DSP2_BLBACK_HIST_X4_MIN_PRE_POS                          (16U)
#define DSP2_BLBACK_HIST_X4_MIN_PRE_LEN                          (11U)
#define DSP2_BLBACK_HIST_X4_MIN_PRE_MSK                          (((1U<<DSP2_BLBACK_HIST_X4_MIN_PRE_LEN)-1)<<DSP2_BLBACK_HIST_X4_MIN_PRE_POS)
#define DSP2_BLBACK_HIST_X4_MIN_PRE_UMSK                         (~(((1U<<DSP2_BLBACK_HIST_X4_MIN_PRE_LEN)-1)<<DSP2_BLBACK_HIST_X4_MIN_PRE_POS))

/* 0x93C : WDR_HIST_14 */
#define DSP2_BLBACK_WDR_HIST_14_OFFSET                           (0x93C)
#define DSP2_BLBACK_HIST_Y4_MAX_PRE                              DSP2_BLBACK_HIST_Y4_MAX_PRE
#define DSP2_BLBACK_HIST_Y4_MAX_PRE_POS                          (0U)
#define DSP2_BLBACK_HIST_Y4_MAX_PRE_LEN                          (11U)
#define DSP2_BLBACK_HIST_Y4_MAX_PRE_MSK                          (((1U<<DSP2_BLBACK_HIST_Y4_MAX_PRE_LEN)-1)<<DSP2_BLBACK_HIST_Y4_MAX_PRE_POS)
#define DSP2_BLBACK_HIST_Y4_MAX_PRE_UMSK                         (~(((1U<<DSP2_BLBACK_HIST_Y4_MAX_PRE_LEN)-1)<<DSP2_BLBACK_HIST_Y4_MAX_PRE_POS))
#define DSP2_BLBACK_HIST_Y4_MIN_PRE                              DSP2_BLBACK_HIST_Y4_MIN_PRE
#define DSP2_BLBACK_HIST_Y4_MIN_PRE_POS                          (16U)
#define DSP2_BLBACK_HIST_Y4_MIN_PRE_LEN                          (11U)
#define DSP2_BLBACK_HIST_Y4_MIN_PRE_MSK                          (((1U<<DSP2_BLBACK_HIST_Y4_MIN_PRE_LEN)-1)<<DSP2_BLBACK_HIST_Y4_MIN_PRE_POS)
#define DSP2_BLBACK_HIST_Y4_MIN_PRE_UMSK                         (~(((1U<<DSP2_BLBACK_HIST_Y4_MIN_PRE_LEN)-1)<<DSP2_BLBACK_HIST_Y4_MIN_PRE_POS))

/* 0x940 : WDR_HIST_15 */
#define DSP2_BLBACK_WDR_HIST_15_OFFSET                           (0x940)
#define DSP2_BLBACK_HIST_X5_MAX_PRE                              DSP2_BLBACK_HIST_X5_MAX_PRE
#define DSP2_BLBACK_HIST_X5_MAX_PRE_POS                          (0U)
#define DSP2_BLBACK_HIST_X5_MAX_PRE_LEN                          (11U)
#define DSP2_BLBACK_HIST_X5_MAX_PRE_MSK                          (((1U<<DSP2_BLBACK_HIST_X5_MAX_PRE_LEN)-1)<<DSP2_BLBACK_HIST_X5_MAX_PRE_POS)
#define DSP2_BLBACK_HIST_X5_MAX_PRE_UMSK                         (~(((1U<<DSP2_BLBACK_HIST_X5_MAX_PRE_LEN)-1)<<DSP2_BLBACK_HIST_X5_MAX_PRE_POS))
#define DSP2_BLBACK_HIST_X5_MIN_PRE                              DSP2_BLBACK_HIST_X5_MIN_PRE
#define DSP2_BLBACK_HIST_X5_MIN_PRE_POS                          (16U)
#define DSP2_BLBACK_HIST_X5_MIN_PRE_LEN                          (11U)
#define DSP2_BLBACK_HIST_X5_MIN_PRE_MSK                          (((1U<<DSP2_BLBACK_HIST_X5_MIN_PRE_LEN)-1)<<DSP2_BLBACK_HIST_X5_MIN_PRE_POS)
#define DSP2_BLBACK_HIST_X5_MIN_PRE_UMSK                         (~(((1U<<DSP2_BLBACK_HIST_X5_MIN_PRE_LEN)-1)<<DSP2_BLBACK_HIST_X5_MIN_PRE_POS))

/* 0x944 : WDR_HIST_16 */
#define DSP2_BLBACK_WDR_HIST_16_OFFSET                           (0x944)
#define DSP2_BLBACK_HIST_Y5_MAX_PRE                              DSP2_BLBACK_HIST_Y5_MAX_PRE
#define DSP2_BLBACK_HIST_Y5_MAX_PRE_POS                          (0U)
#define DSP2_BLBACK_HIST_Y5_MAX_PRE_LEN                          (11U)
#define DSP2_BLBACK_HIST_Y5_MAX_PRE_MSK                          (((1U<<DSP2_BLBACK_HIST_Y5_MAX_PRE_LEN)-1)<<DSP2_BLBACK_HIST_Y5_MAX_PRE_POS)
#define DSP2_BLBACK_HIST_Y5_MAX_PRE_UMSK                         (~(((1U<<DSP2_BLBACK_HIST_Y5_MAX_PRE_LEN)-1)<<DSP2_BLBACK_HIST_Y5_MAX_PRE_POS))
#define DSP2_BLBACK_HIST_Y5_MIN_PRE                              DSP2_BLBACK_HIST_Y5_MIN_PRE
#define DSP2_BLBACK_HIST_Y5_MIN_PRE_POS                          (16U)
#define DSP2_BLBACK_HIST_Y5_MIN_PRE_LEN                          (11U)
#define DSP2_BLBACK_HIST_Y5_MIN_PRE_MSK                          (((1U<<DSP2_BLBACK_HIST_Y5_MIN_PRE_LEN)-1)<<DSP2_BLBACK_HIST_Y5_MIN_PRE_POS)
#define DSP2_BLBACK_HIST_Y5_MIN_PRE_UMSK                         (~(((1U<<DSP2_BLBACK_HIST_Y5_MIN_PRE_LEN)-1)<<DSP2_BLBACK_HIST_Y5_MIN_PRE_POS))

/* 0x948 : WDR_HIST_17 */
#define DSP2_BLBACK_WDR_HIST_17_OFFSET                           (0x948)
#define DSP2_BLBACK_HIST_X6_MAX_PRE                              DSP2_BLBACK_HIST_X6_MAX_PRE
#define DSP2_BLBACK_HIST_X6_MAX_PRE_POS                          (0U)
#define DSP2_BLBACK_HIST_X6_MAX_PRE_LEN                          (11U)
#define DSP2_BLBACK_HIST_X6_MAX_PRE_MSK                          (((1U<<DSP2_BLBACK_HIST_X6_MAX_PRE_LEN)-1)<<DSP2_BLBACK_HIST_X6_MAX_PRE_POS)
#define DSP2_BLBACK_HIST_X6_MAX_PRE_UMSK                         (~(((1U<<DSP2_BLBACK_HIST_X6_MAX_PRE_LEN)-1)<<DSP2_BLBACK_HIST_X6_MAX_PRE_POS))
#define DSP2_BLBACK_HIST_X6_MIN_PRE                              DSP2_BLBACK_HIST_X6_MIN_PRE
#define DSP2_BLBACK_HIST_X6_MIN_PRE_POS                          (16U)
#define DSP2_BLBACK_HIST_X6_MIN_PRE_LEN                          (11U)
#define DSP2_BLBACK_HIST_X6_MIN_PRE_MSK                          (((1U<<DSP2_BLBACK_HIST_X6_MIN_PRE_LEN)-1)<<DSP2_BLBACK_HIST_X6_MIN_PRE_POS)
#define DSP2_BLBACK_HIST_X6_MIN_PRE_UMSK                         (~(((1U<<DSP2_BLBACK_HIST_X6_MIN_PRE_LEN)-1)<<DSP2_BLBACK_HIST_X6_MIN_PRE_POS))

/* 0x94C : WDR_HIST_18 */
#define DSP2_BLBACK_WDR_HIST_18_OFFSET                           (0x94C)
#define DSP2_BLBACK_HIST_Y6_MAX_PRE                              DSP2_BLBACK_HIST_Y6_MAX_PRE
#define DSP2_BLBACK_HIST_Y6_MAX_PRE_POS                          (0U)
#define DSP2_BLBACK_HIST_Y6_MAX_PRE_LEN                          (11U)
#define DSP2_BLBACK_HIST_Y6_MAX_PRE_MSK                          (((1U<<DSP2_BLBACK_HIST_Y6_MAX_PRE_LEN)-1)<<DSP2_BLBACK_HIST_Y6_MAX_PRE_POS)
#define DSP2_BLBACK_HIST_Y6_MAX_PRE_UMSK                         (~(((1U<<DSP2_BLBACK_HIST_Y6_MAX_PRE_LEN)-1)<<DSP2_BLBACK_HIST_Y6_MAX_PRE_POS))
#define DSP2_BLBACK_HIST_Y6_MIN_PRE                              DSP2_BLBACK_HIST_Y6_MIN_PRE
#define DSP2_BLBACK_HIST_Y6_MIN_PRE_POS                          (16U)
#define DSP2_BLBACK_HIST_Y6_MIN_PRE_LEN                          (11U)
#define DSP2_BLBACK_HIST_Y6_MIN_PRE_MSK                          (((1U<<DSP2_BLBACK_HIST_Y6_MIN_PRE_LEN)-1)<<DSP2_BLBACK_HIST_Y6_MIN_PRE_POS)
#define DSP2_BLBACK_HIST_Y6_MIN_PRE_UMSK                         (~(((1U<<DSP2_BLBACK_HIST_Y6_MIN_PRE_LEN)-1)<<DSP2_BLBACK_HIST_Y6_MIN_PRE_POS))

/* 0x950 : WDR_HIST_19 */
#define DSP2_BLBACK_WDR_HIST_19_OFFSET                           (0x950)
#define DSP2_BLBACK_HIST_X7_MAX_PRE                              DSP2_BLBACK_HIST_X7_MAX_PRE
#define DSP2_BLBACK_HIST_X7_MAX_PRE_POS                          (0U)
#define DSP2_BLBACK_HIST_X7_MAX_PRE_LEN                          (11U)
#define DSP2_BLBACK_HIST_X7_MAX_PRE_MSK                          (((1U<<DSP2_BLBACK_HIST_X7_MAX_PRE_LEN)-1)<<DSP2_BLBACK_HIST_X7_MAX_PRE_POS)
#define DSP2_BLBACK_HIST_X7_MAX_PRE_UMSK                         (~(((1U<<DSP2_BLBACK_HIST_X7_MAX_PRE_LEN)-1)<<DSP2_BLBACK_HIST_X7_MAX_PRE_POS))
#define DSP2_BLBACK_HIST_X7_MIN_PRE                              DSP2_BLBACK_HIST_X7_MIN_PRE
#define DSP2_BLBACK_HIST_X7_MIN_PRE_POS                          (16U)
#define DSP2_BLBACK_HIST_X7_MIN_PRE_LEN                          (11U)
#define DSP2_BLBACK_HIST_X7_MIN_PRE_MSK                          (((1U<<DSP2_BLBACK_HIST_X7_MIN_PRE_LEN)-1)<<DSP2_BLBACK_HIST_X7_MIN_PRE_POS)
#define DSP2_BLBACK_HIST_X7_MIN_PRE_UMSK                         (~(((1U<<DSP2_BLBACK_HIST_X7_MIN_PRE_LEN)-1)<<DSP2_BLBACK_HIST_X7_MIN_PRE_POS))

/* 0x954 : WDR_HIST_20 */
#define DSP2_BLBACK_WDR_HIST_20_OFFSET                           (0x954)
#define DSP2_BLBACK_HIST_Y7_MAX_PRE                              DSP2_BLBACK_HIST_Y7_MAX_PRE
#define DSP2_BLBACK_HIST_Y7_MAX_PRE_POS                          (0U)
#define DSP2_BLBACK_HIST_Y7_MAX_PRE_LEN                          (11U)
#define DSP2_BLBACK_HIST_Y7_MAX_PRE_MSK                          (((1U<<DSP2_BLBACK_HIST_Y7_MAX_PRE_LEN)-1)<<DSP2_BLBACK_HIST_Y7_MAX_PRE_POS)
#define DSP2_BLBACK_HIST_Y7_MAX_PRE_UMSK                         (~(((1U<<DSP2_BLBACK_HIST_Y7_MAX_PRE_LEN)-1)<<DSP2_BLBACK_HIST_Y7_MAX_PRE_POS))
#define DSP2_BLBACK_HIST_Y7_MIN_PRE                              DSP2_BLBACK_HIST_Y7_MIN_PRE
#define DSP2_BLBACK_HIST_Y7_MIN_PRE_POS                          (16U)
#define DSP2_BLBACK_HIST_Y7_MIN_PRE_LEN                          (11U)
#define DSP2_BLBACK_HIST_Y7_MIN_PRE_MSK                          (((1U<<DSP2_BLBACK_HIST_Y7_MIN_PRE_LEN)-1)<<DSP2_BLBACK_HIST_Y7_MIN_PRE_POS)
#define DSP2_BLBACK_HIST_Y7_MIN_PRE_UMSK                         (~(((1U<<DSP2_BLBACK_HIST_Y7_MIN_PRE_LEN)-1)<<DSP2_BLBACK_HIST_Y7_MIN_PRE_POS))

/* 0x958 : REG_HIST0_64 */
#define DSP2_BLBACK_REG_HIST0_64_OFFSET                          (0x958)
#define DSP2_BLBACK_HIST0_64_R                                   DSP2_BLBACK_HIST0_64_R
#define DSP2_BLBACK_HIST0_64_R_POS                               (0U)
#define DSP2_BLBACK_HIST0_64_R_LEN                               (24U)
#define DSP2_BLBACK_HIST0_64_R_MSK                               (((1U<<DSP2_BLBACK_HIST0_64_R_LEN)-1)<<DSP2_BLBACK_HIST0_64_R_POS)
#define DSP2_BLBACK_HIST0_64_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST0_64_R_LEN)-1)<<DSP2_BLBACK_HIST0_64_R_POS))

/* 0x95C : REG_HIST1_64 */
#define DSP2_BLBACK_REG_HIST1_64_OFFSET                          (0x95C)
#define DSP2_BLBACK_HIST1_64_R                                   DSP2_BLBACK_HIST1_64_R
#define DSP2_BLBACK_HIST1_64_R_POS                               (0U)
#define DSP2_BLBACK_HIST1_64_R_LEN                               (24U)
#define DSP2_BLBACK_HIST1_64_R_MSK                               (((1U<<DSP2_BLBACK_HIST1_64_R_LEN)-1)<<DSP2_BLBACK_HIST1_64_R_POS)
#define DSP2_BLBACK_HIST1_64_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST1_64_R_LEN)-1)<<DSP2_BLBACK_HIST1_64_R_POS))

/* 0xA00 : REG_HIST0_0 */
#define DSP2_BLBACK_REG_HIST0_0_OFFSET                           (0xA00)
#define DSP2_BLBACK_HIST0_0_R                                    DSP2_BLBACK_HIST0_0_R
#define DSP2_BLBACK_HIST0_0_R_POS                                (0U)
#define DSP2_BLBACK_HIST0_0_R_LEN                                (24U)
#define DSP2_BLBACK_HIST0_0_R_MSK                                (((1U<<DSP2_BLBACK_HIST0_0_R_LEN)-1)<<DSP2_BLBACK_HIST0_0_R_POS)
#define DSP2_BLBACK_HIST0_0_R_UMSK                               (~(((1U<<DSP2_BLBACK_HIST0_0_R_LEN)-1)<<DSP2_BLBACK_HIST0_0_R_POS))

/* 0xA04 : REG_HIST0_1 */
#define DSP2_BLBACK_REG_HIST0_1_OFFSET                           (0xA04)
#define DSP2_BLBACK_HIST0_1_R                                    DSP2_BLBACK_HIST0_1_R
#define DSP2_BLBACK_HIST0_1_R_POS                                (0U)
#define DSP2_BLBACK_HIST0_1_R_LEN                                (24U)
#define DSP2_BLBACK_HIST0_1_R_MSK                                (((1U<<DSP2_BLBACK_HIST0_1_R_LEN)-1)<<DSP2_BLBACK_HIST0_1_R_POS)
#define DSP2_BLBACK_HIST0_1_R_UMSK                               (~(((1U<<DSP2_BLBACK_HIST0_1_R_LEN)-1)<<DSP2_BLBACK_HIST0_1_R_POS))

/* 0xA08 : REG_HIST0_2 */
#define DSP2_BLBACK_REG_HIST0_2_OFFSET                           (0xA08)
#define DSP2_BLBACK_HIST0_2_R                                    DSP2_BLBACK_HIST0_2_R
#define DSP2_BLBACK_HIST0_2_R_POS                                (0U)
#define DSP2_BLBACK_HIST0_2_R_LEN                                (24U)
#define DSP2_BLBACK_HIST0_2_R_MSK                                (((1U<<DSP2_BLBACK_HIST0_2_R_LEN)-1)<<DSP2_BLBACK_HIST0_2_R_POS)
#define DSP2_BLBACK_HIST0_2_R_UMSK                               (~(((1U<<DSP2_BLBACK_HIST0_2_R_LEN)-1)<<DSP2_BLBACK_HIST0_2_R_POS))

/* 0xA0C : REG_HIST0_3 */
#define DSP2_BLBACK_REG_HIST0_3_OFFSET                           (0xA0C)
#define DSP2_BLBACK_HIST0_3_R                                    DSP2_BLBACK_HIST0_3_R
#define DSP2_BLBACK_HIST0_3_R_POS                                (0U)
#define DSP2_BLBACK_HIST0_3_R_LEN                                (24U)
#define DSP2_BLBACK_HIST0_3_R_MSK                                (((1U<<DSP2_BLBACK_HIST0_3_R_LEN)-1)<<DSP2_BLBACK_HIST0_3_R_POS)
#define DSP2_BLBACK_HIST0_3_R_UMSK                               (~(((1U<<DSP2_BLBACK_HIST0_3_R_LEN)-1)<<DSP2_BLBACK_HIST0_3_R_POS))

/* 0xA10 : REG_HIST0_4 */
#define DSP2_BLBACK_REG_HIST0_4_OFFSET                           (0xA10)
#define DSP2_BLBACK_HIST0_4_R                                    DSP2_BLBACK_HIST0_4_R
#define DSP2_BLBACK_HIST0_4_R_POS                                (0U)
#define DSP2_BLBACK_HIST0_4_R_LEN                                (24U)
#define DSP2_BLBACK_HIST0_4_R_MSK                                (((1U<<DSP2_BLBACK_HIST0_4_R_LEN)-1)<<DSP2_BLBACK_HIST0_4_R_POS)
#define DSP2_BLBACK_HIST0_4_R_UMSK                               (~(((1U<<DSP2_BLBACK_HIST0_4_R_LEN)-1)<<DSP2_BLBACK_HIST0_4_R_POS))

/* 0xA14 : REG_HIST0_5 */
#define DSP2_BLBACK_REG_HIST0_5_OFFSET                           (0xA14)
#define DSP2_BLBACK_HIST0_5_R                                    DSP2_BLBACK_HIST0_5_R
#define DSP2_BLBACK_HIST0_5_R_POS                                (0U)
#define DSP2_BLBACK_HIST0_5_R_LEN                                (24U)
#define DSP2_BLBACK_HIST0_5_R_MSK                                (((1U<<DSP2_BLBACK_HIST0_5_R_LEN)-1)<<DSP2_BLBACK_HIST0_5_R_POS)
#define DSP2_BLBACK_HIST0_5_R_UMSK                               (~(((1U<<DSP2_BLBACK_HIST0_5_R_LEN)-1)<<DSP2_BLBACK_HIST0_5_R_POS))

/* 0xA18 : REG_HIST0_6 */
#define DSP2_BLBACK_REG_HIST0_6_OFFSET                           (0xA18)
#define DSP2_BLBACK_HIST0_6_R                                    DSP2_BLBACK_HIST0_6_R
#define DSP2_BLBACK_HIST0_6_R_POS                                (0U)
#define DSP2_BLBACK_HIST0_6_R_LEN                                (24U)
#define DSP2_BLBACK_HIST0_6_R_MSK                                (((1U<<DSP2_BLBACK_HIST0_6_R_LEN)-1)<<DSP2_BLBACK_HIST0_6_R_POS)
#define DSP2_BLBACK_HIST0_6_R_UMSK                               (~(((1U<<DSP2_BLBACK_HIST0_6_R_LEN)-1)<<DSP2_BLBACK_HIST0_6_R_POS))

/* 0xA1C : REG_HIST0_7 */
#define DSP2_BLBACK_REG_HIST0_7_OFFSET                           (0xA1C)
#define DSP2_BLBACK_HIST0_7_R                                    DSP2_BLBACK_HIST0_7_R
#define DSP2_BLBACK_HIST0_7_R_POS                                (0U)
#define DSP2_BLBACK_HIST0_7_R_LEN                                (24U)
#define DSP2_BLBACK_HIST0_7_R_MSK                                (((1U<<DSP2_BLBACK_HIST0_7_R_LEN)-1)<<DSP2_BLBACK_HIST0_7_R_POS)
#define DSP2_BLBACK_HIST0_7_R_UMSK                               (~(((1U<<DSP2_BLBACK_HIST0_7_R_LEN)-1)<<DSP2_BLBACK_HIST0_7_R_POS))

/* 0xA20 : REG_HIST0_8 */
#define DSP2_BLBACK_REG_HIST0_8_OFFSET                           (0xA20)
#define DSP2_BLBACK_HIST0_8_R                                    DSP2_BLBACK_HIST0_8_R
#define DSP2_BLBACK_HIST0_8_R_POS                                (0U)
#define DSP2_BLBACK_HIST0_8_R_LEN                                (24U)
#define DSP2_BLBACK_HIST0_8_R_MSK                                (((1U<<DSP2_BLBACK_HIST0_8_R_LEN)-1)<<DSP2_BLBACK_HIST0_8_R_POS)
#define DSP2_BLBACK_HIST0_8_R_UMSK                               (~(((1U<<DSP2_BLBACK_HIST0_8_R_LEN)-1)<<DSP2_BLBACK_HIST0_8_R_POS))

/* 0xA24 : REG_HIST0_9 */
#define DSP2_BLBACK_REG_HIST0_9_OFFSET                           (0xA24)
#define DSP2_BLBACK_HIST0_9_R                                    DSP2_BLBACK_HIST0_9_R
#define DSP2_BLBACK_HIST0_9_R_POS                                (0U)
#define DSP2_BLBACK_HIST0_9_R_LEN                                (24U)
#define DSP2_BLBACK_HIST0_9_R_MSK                                (((1U<<DSP2_BLBACK_HIST0_9_R_LEN)-1)<<DSP2_BLBACK_HIST0_9_R_POS)
#define DSP2_BLBACK_HIST0_9_R_UMSK                               (~(((1U<<DSP2_BLBACK_HIST0_9_R_LEN)-1)<<DSP2_BLBACK_HIST0_9_R_POS))

/* 0xA28 : REG_HIST0_10 */
#define DSP2_BLBACK_REG_HIST0_10_OFFSET                          (0xA28)
#define DSP2_BLBACK_HIST0_10_R                                   DSP2_BLBACK_HIST0_10_R
#define DSP2_BLBACK_HIST0_10_R_POS                               (0U)
#define DSP2_BLBACK_HIST0_10_R_LEN                               (24U)
#define DSP2_BLBACK_HIST0_10_R_MSK                               (((1U<<DSP2_BLBACK_HIST0_10_R_LEN)-1)<<DSP2_BLBACK_HIST0_10_R_POS)
#define DSP2_BLBACK_HIST0_10_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST0_10_R_LEN)-1)<<DSP2_BLBACK_HIST0_10_R_POS))

/* 0xA2C : REG_HIST0_11 */
#define DSP2_BLBACK_REG_HIST0_11_OFFSET                          (0xA2C)
#define DSP2_BLBACK_HIST0_11_R                                   DSP2_BLBACK_HIST0_11_R
#define DSP2_BLBACK_HIST0_11_R_POS                               (0U)
#define DSP2_BLBACK_HIST0_11_R_LEN                               (24U)
#define DSP2_BLBACK_HIST0_11_R_MSK                               (((1U<<DSP2_BLBACK_HIST0_11_R_LEN)-1)<<DSP2_BLBACK_HIST0_11_R_POS)
#define DSP2_BLBACK_HIST0_11_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST0_11_R_LEN)-1)<<DSP2_BLBACK_HIST0_11_R_POS))

/* 0xA30 : REG_HIST0_12 */
#define DSP2_BLBACK_REG_HIST0_12_OFFSET                          (0xA30)
#define DSP2_BLBACK_HIST0_12_R                                   DSP2_BLBACK_HIST0_12_R
#define DSP2_BLBACK_HIST0_12_R_POS                               (0U)
#define DSP2_BLBACK_HIST0_12_R_LEN                               (24U)
#define DSP2_BLBACK_HIST0_12_R_MSK                               (((1U<<DSP2_BLBACK_HIST0_12_R_LEN)-1)<<DSP2_BLBACK_HIST0_12_R_POS)
#define DSP2_BLBACK_HIST0_12_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST0_12_R_LEN)-1)<<DSP2_BLBACK_HIST0_12_R_POS))

/* 0xA34 : REG_HIST0_13 */
#define DSP2_BLBACK_REG_HIST0_13_OFFSET                          (0xA34)
#define DSP2_BLBACK_HIST0_13_R                                   DSP2_BLBACK_HIST0_13_R
#define DSP2_BLBACK_HIST0_13_R_POS                               (0U)
#define DSP2_BLBACK_HIST0_13_R_LEN                               (24U)
#define DSP2_BLBACK_HIST0_13_R_MSK                               (((1U<<DSP2_BLBACK_HIST0_13_R_LEN)-1)<<DSP2_BLBACK_HIST0_13_R_POS)
#define DSP2_BLBACK_HIST0_13_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST0_13_R_LEN)-1)<<DSP2_BLBACK_HIST0_13_R_POS))

/* 0xA38 : REG_HIST0_14 */
#define DSP2_BLBACK_REG_HIST0_14_OFFSET                          (0xA38)
#define DSP2_BLBACK_HIST0_14_R                                   DSP2_BLBACK_HIST0_14_R
#define DSP2_BLBACK_HIST0_14_R_POS                               (0U)
#define DSP2_BLBACK_HIST0_14_R_LEN                               (24U)
#define DSP2_BLBACK_HIST0_14_R_MSK                               (((1U<<DSP2_BLBACK_HIST0_14_R_LEN)-1)<<DSP2_BLBACK_HIST0_14_R_POS)
#define DSP2_BLBACK_HIST0_14_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST0_14_R_LEN)-1)<<DSP2_BLBACK_HIST0_14_R_POS))

/* 0xA3C : REG_HIST0_15 */
#define DSP2_BLBACK_REG_HIST0_15_OFFSET                          (0xA3C)
#define DSP2_BLBACK_HIST0_15_R                                   DSP2_BLBACK_HIST0_15_R
#define DSP2_BLBACK_HIST0_15_R_POS                               (0U)
#define DSP2_BLBACK_HIST0_15_R_LEN                               (24U)
#define DSP2_BLBACK_HIST0_15_R_MSK                               (((1U<<DSP2_BLBACK_HIST0_15_R_LEN)-1)<<DSP2_BLBACK_HIST0_15_R_POS)
#define DSP2_BLBACK_HIST0_15_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST0_15_R_LEN)-1)<<DSP2_BLBACK_HIST0_15_R_POS))

/* 0xA40 : REG_HIST0_16 */
#define DSP2_BLBACK_REG_HIST0_16_OFFSET                          (0xA40)
#define DSP2_BLBACK_HIST0_16_R                                   DSP2_BLBACK_HIST0_16_R
#define DSP2_BLBACK_HIST0_16_R_POS                               (0U)
#define DSP2_BLBACK_HIST0_16_R_LEN                               (24U)
#define DSP2_BLBACK_HIST0_16_R_MSK                               (((1U<<DSP2_BLBACK_HIST0_16_R_LEN)-1)<<DSP2_BLBACK_HIST0_16_R_POS)
#define DSP2_BLBACK_HIST0_16_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST0_16_R_LEN)-1)<<DSP2_BLBACK_HIST0_16_R_POS))

/* 0xA44 : REG_HIST0_17 */
#define DSP2_BLBACK_REG_HIST0_17_OFFSET                          (0xA44)
#define DSP2_BLBACK_HIST0_17_R                                   DSP2_BLBACK_HIST0_17_R
#define DSP2_BLBACK_HIST0_17_R_POS                               (0U)
#define DSP2_BLBACK_HIST0_17_R_LEN                               (24U)
#define DSP2_BLBACK_HIST0_17_R_MSK                               (((1U<<DSP2_BLBACK_HIST0_17_R_LEN)-1)<<DSP2_BLBACK_HIST0_17_R_POS)
#define DSP2_BLBACK_HIST0_17_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST0_17_R_LEN)-1)<<DSP2_BLBACK_HIST0_17_R_POS))

/* 0xA48 : REG_HIST0_18 */
#define DSP2_BLBACK_REG_HIST0_18_OFFSET                          (0xA48)
#define DSP2_BLBACK_HIST0_18_R                                   DSP2_BLBACK_HIST0_18_R
#define DSP2_BLBACK_HIST0_18_R_POS                               (0U)
#define DSP2_BLBACK_HIST0_18_R_LEN                               (24U)
#define DSP2_BLBACK_HIST0_18_R_MSK                               (((1U<<DSP2_BLBACK_HIST0_18_R_LEN)-1)<<DSP2_BLBACK_HIST0_18_R_POS)
#define DSP2_BLBACK_HIST0_18_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST0_18_R_LEN)-1)<<DSP2_BLBACK_HIST0_18_R_POS))

/* 0xA4C : REG_HIST0_19 */
#define DSP2_BLBACK_REG_HIST0_19_OFFSET                          (0xA4C)
#define DSP2_BLBACK_HIST0_19_R                                   DSP2_BLBACK_HIST0_19_R
#define DSP2_BLBACK_HIST0_19_R_POS                               (0U)
#define DSP2_BLBACK_HIST0_19_R_LEN                               (24U)
#define DSP2_BLBACK_HIST0_19_R_MSK                               (((1U<<DSP2_BLBACK_HIST0_19_R_LEN)-1)<<DSP2_BLBACK_HIST0_19_R_POS)
#define DSP2_BLBACK_HIST0_19_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST0_19_R_LEN)-1)<<DSP2_BLBACK_HIST0_19_R_POS))

/* 0xA50 : REG_HIST0_20 */
#define DSP2_BLBACK_REG_HIST0_20_OFFSET                          (0xA50)
#define DSP2_BLBACK_HIST0_20_R                                   DSP2_BLBACK_HIST0_20_R
#define DSP2_BLBACK_HIST0_20_R_POS                               (0U)
#define DSP2_BLBACK_HIST0_20_R_LEN                               (24U)
#define DSP2_BLBACK_HIST0_20_R_MSK                               (((1U<<DSP2_BLBACK_HIST0_20_R_LEN)-1)<<DSP2_BLBACK_HIST0_20_R_POS)
#define DSP2_BLBACK_HIST0_20_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST0_20_R_LEN)-1)<<DSP2_BLBACK_HIST0_20_R_POS))

/* 0xA54 : REG_HIST0_21 */
#define DSP2_BLBACK_REG_HIST0_21_OFFSET                          (0xA54)
#define DSP2_BLBACK_HIST0_21_R                                   DSP2_BLBACK_HIST0_21_R
#define DSP2_BLBACK_HIST0_21_R_POS                               (0U)
#define DSP2_BLBACK_HIST0_21_R_LEN                               (24U)
#define DSP2_BLBACK_HIST0_21_R_MSK                               (((1U<<DSP2_BLBACK_HIST0_21_R_LEN)-1)<<DSP2_BLBACK_HIST0_21_R_POS)
#define DSP2_BLBACK_HIST0_21_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST0_21_R_LEN)-1)<<DSP2_BLBACK_HIST0_21_R_POS))

/* 0xA58 : REG_HIST0_22 */
#define DSP2_BLBACK_REG_HIST0_22_OFFSET                          (0xA58)
#define DSP2_BLBACK_HIST0_22_R                                   DSP2_BLBACK_HIST0_22_R
#define DSP2_BLBACK_HIST0_22_R_POS                               (0U)
#define DSP2_BLBACK_HIST0_22_R_LEN                               (24U)
#define DSP2_BLBACK_HIST0_22_R_MSK                               (((1U<<DSP2_BLBACK_HIST0_22_R_LEN)-1)<<DSP2_BLBACK_HIST0_22_R_POS)
#define DSP2_BLBACK_HIST0_22_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST0_22_R_LEN)-1)<<DSP2_BLBACK_HIST0_22_R_POS))

/* 0xA5C : REG_HIST0_23 */
#define DSP2_BLBACK_REG_HIST0_23_OFFSET                          (0xA5C)
#define DSP2_BLBACK_HIST0_23_R                                   DSP2_BLBACK_HIST0_23_R
#define DSP2_BLBACK_HIST0_23_R_POS                               (0U)
#define DSP2_BLBACK_HIST0_23_R_LEN                               (24U)
#define DSP2_BLBACK_HIST0_23_R_MSK                               (((1U<<DSP2_BLBACK_HIST0_23_R_LEN)-1)<<DSP2_BLBACK_HIST0_23_R_POS)
#define DSP2_BLBACK_HIST0_23_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST0_23_R_LEN)-1)<<DSP2_BLBACK_HIST0_23_R_POS))

/* 0xA60 : REG_HIST0_24 */
#define DSP2_BLBACK_REG_HIST0_24_OFFSET                          (0xA60)
#define DSP2_BLBACK_HIST0_24_R                                   DSP2_BLBACK_HIST0_24_R
#define DSP2_BLBACK_HIST0_24_R_POS                               (0U)
#define DSP2_BLBACK_HIST0_24_R_LEN                               (24U)
#define DSP2_BLBACK_HIST0_24_R_MSK                               (((1U<<DSP2_BLBACK_HIST0_24_R_LEN)-1)<<DSP2_BLBACK_HIST0_24_R_POS)
#define DSP2_BLBACK_HIST0_24_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST0_24_R_LEN)-1)<<DSP2_BLBACK_HIST0_24_R_POS))

/* 0xA64 : REG_HIST0_25 */
#define DSP2_BLBACK_REG_HIST0_25_OFFSET                          (0xA64)
#define DSP2_BLBACK_HIST0_25_R                                   DSP2_BLBACK_HIST0_25_R
#define DSP2_BLBACK_HIST0_25_R_POS                               (0U)
#define DSP2_BLBACK_HIST0_25_R_LEN                               (24U)
#define DSP2_BLBACK_HIST0_25_R_MSK                               (((1U<<DSP2_BLBACK_HIST0_25_R_LEN)-1)<<DSP2_BLBACK_HIST0_25_R_POS)
#define DSP2_BLBACK_HIST0_25_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST0_25_R_LEN)-1)<<DSP2_BLBACK_HIST0_25_R_POS))

/* 0xA68 : REG_HIST0_26 */
#define DSP2_BLBACK_REG_HIST0_26_OFFSET                          (0xA68)
#define DSP2_BLBACK_HIST0_26_R                                   DSP2_BLBACK_HIST0_26_R
#define DSP2_BLBACK_HIST0_26_R_POS                               (0U)
#define DSP2_BLBACK_HIST0_26_R_LEN                               (24U)
#define DSP2_BLBACK_HIST0_26_R_MSK                               (((1U<<DSP2_BLBACK_HIST0_26_R_LEN)-1)<<DSP2_BLBACK_HIST0_26_R_POS)
#define DSP2_BLBACK_HIST0_26_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST0_26_R_LEN)-1)<<DSP2_BLBACK_HIST0_26_R_POS))

/* 0xA6C : REG_HIST0_27 */
#define DSP2_BLBACK_REG_HIST0_27_OFFSET                          (0xA6C)
#define DSP2_BLBACK_HIST0_27_R                                   DSP2_BLBACK_HIST0_27_R
#define DSP2_BLBACK_HIST0_27_R_POS                               (0U)
#define DSP2_BLBACK_HIST0_27_R_LEN                               (24U)
#define DSP2_BLBACK_HIST0_27_R_MSK                               (((1U<<DSP2_BLBACK_HIST0_27_R_LEN)-1)<<DSP2_BLBACK_HIST0_27_R_POS)
#define DSP2_BLBACK_HIST0_27_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST0_27_R_LEN)-1)<<DSP2_BLBACK_HIST0_27_R_POS))

/* 0xA70 : REG_HIST0_28 */
#define DSP2_BLBACK_REG_HIST0_28_OFFSET                          (0xA70)
#define DSP2_BLBACK_HIST0_28_R                                   DSP2_BLBACK_HIST0_28_R
#define DSP2_BLBACK_HIST0_28_R_POS                               (0U)
#define DSP2_BLBACK_HIST0_28_R_LEN                               (24U)
#define DSP2_BLBACK_HIST0_28_R_MSK                               (((1U<<DSP2_BLBACK_HIST0_28_R_LEN)-1)<<DSP2_BLBACK_HIST0_28_R_POS)
#define DSP2_BLBACK_HIST0_28_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST0_28_R_LEN)-1)<<DSP2_BLBACK_HIST0_28_R_POS))

/* 0xA74 : REG_HIST0_29 */
#define DSP2_BLBACK_REG_HIST0_29_OFFSET                          (0xA74)
#define DSP2_BLBACK_HIST0_29_R                                   DSP2_BLBACK_HIST0_29_R
#define DSP2_BLBACK_HIST0_29_R_POS                               (0U)
#define DSP2_BLBACK_HIST0_29_R_LEN                               (24U)
#define DSP2_BLBACK_HIST0_29_R_MSK                               (((1U<<DSP2_BLBACK_HIST0_29_R_LEN)-1)<<DSP2_BLBACK_HIST0_29_R_POS)
#define DSP2_BLBACK_HIST0_29_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST0_29_R_LEN)-1)<<DSP2_BLBACK_HIST0_29_R_POS))

/* 0xA78 : REG_HIST0_30 */
#define DSP2_BLBACK_REG_HIST0_30_OFFSET                          (0xA78)
#define DSP2_BLBACK_HIST0_30_R                                   DSP2_BLBACK_HIST0_30_R
#define DSP2_BLBACK_HIST0_30_R_POS                               (0U)
#define DSP2_BLBACK_HIST0_30_R_LEN                               (24U)
#define DSP2_BLBACK_HIST0_30_R_MSK                               (((1U<<DSP2_BLBACK_HIST0_30_R_LEN)-1)<<DSP2_BLBACK_HIST0_30_R_POS)
#define DSP2_BLBACK_HIST0_30_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST0_30_R_LEN)-1)<<DSP2_BLBACK_HIST0_30_R_POS))

/* 0xA7C : REG_HIST0_31 */
#define DSP2_BLBACK_REG_HIST0_31_OFFSET                          (0xA7C)
#define DSP2_BLBACK_HIST0_31_R                                   DSP2_BLBACK_HIST0_31_R
#define DSP2_BLBACK_HIST0_31_R_POS                               (0U)
#define DSP2_BLBACK_HIST0_31_R_LEN                               (24U)
#define DSP2_BLBACK_HIST0_31_R_MSK                               (((1U<<DSP2_BLBACK_HIST0_31_R_LEN)-1)<<DSP2_BLBACK_HIST0_31_R_POS)
#define DSP2_BLBACK_HIST0_31_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST0_31_R_LEN)-1)<<DSP2_BLBACK_HIST0_31_R_POS))

/* 0xA80 : REG_HIST0_32 */
#define DSP2_BLBACK_REG_HIST0_32_OFFSET                          (0xA80)
#define DSP2_BLBACK_HIST0_32_R                                   DSP2_BLBACK_HIST0_32_R
#define DSP2_BLBACK_HIST0_32_R_POS                               (0U)
#define DSP2_BLBACK_HIST0_32_R_LEN                               (24U)
#define DSP2_BLBACK_HIST0_32_R_MSK                               (((1U<<DSP2_BLBACK_HIST0_32_R_LEN)-1)<<DSP2_BLBACK_HIST0_32_R_POS)
#define DSP2_BLBACK_HIST0_32_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST0_32_R_LEN)-1)<<DSP2_BLBACK_HIST0_32_R_POS))

/* 0xA84 : REG_HIST0_33 */
#define DSP2_BLBACK_REG_HIST0_33_OFFSET                          (0xA84)
#define DSP2_BLBACK_HIST0_33_R                                   DSP2_BLBACK_HIST0_33_R
#define DSP2_BLBACK_HIST0_33_R_POS                               (0U)
#define DSP2_BLBACK_HIST0_33_R_LEN                               (24U)
#define DSP2_BLBACK_HIST0_33_R_MSK                               (((1U<<DSP2_BLBACK_HIST0_33_R_LEN)-1)<<DSP2_BLBACK_HIST0_33_R_POS)
#define DSP2_BLBACK_HIST0_33_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST0_33_R_LEN)-1)<<DSP2_BLBACK_HIST0_33_R_POS))

/* 0xA88 : REG_HIST0_34 */
#define DSP2_BLBACK_REG_HIST0_34_OFFSET                          (0xA88)
#define DSP2_BLBACK_HIST0_34_R                                   DSP2_BLBACK_HIST0_34_R
#define DSP2_BLBACK_HIST0_34_R_POS                               (0U)
#define DSP2_BLBACK_HIST0_34_R_LEN                               (24U)
#define DSP2_BLBACK_HIST0_34_R_MSK                               (((1U<<DSP2_BLBACK_HIST0_34_R_LEN)-1)<<DSP2_BLBACK_HIST0_34_R_POS)
#define DSP2_BLBACK_HIST0_34_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST0_34_R_LEN)-1)<<DSP2_BLBACK_HIST0_34_R_POS))

/* 0xA8C : REG_HIST0_35 */
#define DSP2_BLBACK_REG_HIST0_35_OFFSET                          (0xA8C)
#define DSP2_BLBACK_HIST0_35_R                                   DSP2_BLBACK_HIST0_35_R
#define DSP2_BLBACK_HIST0_35_R_POS                               (0U)
#define DSP2_BLBACK_HIST0_35_R_LEN                               (24U)
#define DSP2_BLBACK_HIST0_35_R_MSK                               (((1U<<DSP2_BLBACK_HIST0_35_R_LEN)-1)<<DSP2_BLBACK_HIST0_35_R_POS)
#define DSP2_BLBACK_HIST0_35_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST0_35_R_LEN)-1)<<DSP2_BLBACK_HIST0_35_R_POS))

/* 0xA90 : REG_HIST0_36 */
#define DSP2_BLBACK_REG_HIST0_36_OFFSET                          (0xA90)
#define DSP2_BLBACK_HIST0_36_R                                   DSP2_BLBACK_HIST0_36_R
#define DSP2_BLBACK_HIST0_36_R_POS                               (0U)
#define DSP2_BLBACK_HIST0_36_R_LEN                               (24U)
#define DSP2_BLBACK_HIST0_36_R_MSK                               (((1U<<DSP2_BLBACK_HIST0_36_R_LEN)-1)<<DSP2_BLBACK_HIST0_36_R_POS)
#define DSP2_BLBACK_HIST0_36_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST0_36_R_LEN)-1)<<DSP2_BLBACK_HIST0_36_R_POS))

/* 0xA94 : REG_HIST0_37 */
#define DSP2_BLBACK_REG_HIST0_37_OFFSET                          (0xA94)
#define DSP2_BLBACK_HIST0_37_R                                   DSP2_BLBACK_HIST0_37_R
#define DSP2_BLBACK_HIST0_37_R_POS                               (0U)
#define DSP2_BLBACK_HIST0_37_R_LEN                               (24U)
#define DSP2_BLBACK_HIST0_37_R_MSK                               (((1U<<DSP2_BLBACK_HIST0_37_R_LEN)-1)<<DSP2_BLBACK_HIST0_37_R_POS)
#define DSP2_BLBACK_HIST0_37_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST0_37_R_LEN)-1)<<DSP2_BLBACK_HIST0_37_R_POS))

/* 0xA98 : REG_HIST0_38 */
#define DSP2_BLBACK_REG_HIST0_38_OFFSET                          (0xA98)
#define DSP2_BLBACK_HIST0_38_R                                   DSP2_BLBACK_HIST0_38_R
#define DSP2_BLBACK_HIST0_38_R_POS                               (0U)
#define DSP2_BLBACK_HIST0_38_R_LEN                               (24U)
#define DSP2_BLBACK_HIST0_38_R_MSK                               (((1U<<DSP2_BLBACK_HIST0_38_R_LEN)-1)<<DSP2_BLBACK_HIST0_38_R_POS)
#define DSP2_BLBACK_HIST0_38_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST0_38_R_LEN)-1)<<DSP2_BLBACK_HIST0_38_R_POS))

/* 0xA9C : REG_HIST0_39 */
#define DSP2_BLBACK_REG_HIST0_39_OFFSET                          (0xA9C)
#define DSP2_BLBACK_HIST0_39_R                                   DSP2_BLBACK_HIST0_39_R
#define DSP2_BLBACK_HIST0_39_R_POS                               (0U)
#define DSP2_BLBACK_HIST0_39_R_LEN                               (24U)
#define DSP2_BLBACK_HIST0_39_R_MSK                               (((1U<<DSP2_BLBACK_HIST0_39_R_LEN)-1)<<DSP2_BLBACK_HIST0_39_R_POS)
#define DSP2_BLBACK_HIST0_39_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST0_39_R_LEN)-1)<<DSP2_BLBACK_HIST0_39_R_POS))

/* 0xAA0 : REG_HIST0_40 */
#define DSP2_BLBACK_REG_HIST0_40_OFFSET                          (0xAA0)
#define DSP2_BLBACK_HIST0_40_R                                   DSP2_BLBACK_HIST0_40_R
#define DSP2_BLBACK_HIST0_40_R_POS                               (0U)
#define DSP2_BLBACK_HIST0_40_R_LEN                               (24U)
#define DSP2_BLBACK_HIST0_40_R_MSK                               (((1U<<DSP2_BLBACK_HIST0_40_R_LEN)-1)<<DSP2_BLBACK_HIST0_40_R_POS)
#define DSP2_BLBACK_HIST0_40_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST0_40_R_LEN)-1)<<DSP2_BLBACK_HIST0_40_R_POS))

/* 0xAA4 : REG_HIST0_41 */
#define DSP2_BLBACK_REG_HIST0_41_OFFSET                          (0xAA4)
#define DSP2_BLBACK_HIST0_41_R                                   DSP2_BLBACK_HIST0_41_R
#define DSP2_BLBACK_HIST0_41_R_POS                               (0U)
#define DSP2_BLBACK_HIST0_41_R_LEN                               (24U)
#define DSP2_BLBACK_HIST0_41_R_MSK                               (((1U<<DSP2_BLBACK_HIST0_41_R_LEN)-1)<<DSP2_BLBACK_HIST0_41_R_POS)
#define DSP2_BLBACK_HIST0_41_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST0_41_R_LEN)-1)<<DSP2_BLBACK_HIST0_41_R_POS))

/* 0xAA8 : REG_HIST0_42 */
#define DSP2_BLBACK_REG_HIST0_42_OFFSET                          (0xAA8)
#define DSP2_BLBACK_HIST0_42_R                                   DSP2_BLBACK_HIST0_42_R
#define DSP2_BLBACK_HIST0_42_R_POS                               (0U)
#define DSP2_BLBACK_HIST0_42_R_LEN                               (24U)
#define DSP2_BLBACK_HIST0_42_R_MSK                               (((1U<<DSP2_BLBACK_HIST0_42_R_LEN)-1)<<DSP2_BLBACK_HIST0_42_R_POS)
#define DSP2_BLBACK_HIST0_42_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST0_42_R_LEN)-1)<<DSP2_BLBACK_HIST0_42_R_POS))

/* 0xAAC : REG_HIST0_43 */
#define DSP2_BLBACK_REG_HIST0_43_OFFSET                          (0xAAC)
#define DSP2_BLBACK_HIST0_43_R                                   DSP2_BLBACK_HIST0_43_R
#define DSP2_BLBACK_HIST0_43_R_POS                               (0U)
#define DSP2_BLBACK_HIST0_43_R_LEN                               (24U)
#define DSP2_BLBACK_HIST0_43_R_MSK                               (((1U<<DSP2_BLBACK_HIST0_43_R_LEN)-1)<<DSP2_BLBACK_HIST0_43_R_POS)
#define DSP2_BLBACK_HIST0_43_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST0_43_R_LEN)-1)<<DSP2_BLBACK_HIST0_43_R_POS))

/* 0xAB0 : REG_HIST0_44 */
#define DSP2_BLBACK_REG_HIST0_44_OFFSET                          (0xAB0)
#define DSP2_BLBACK_HIST0_44_R                                   DSP2_BLBACK_HIST0_44_R
#define DSP2_BLBACK_HIST0_44_R_POS                               (0U)
#define DSP2_BLBACK_HIST0_44_R_LEN                               (24U)
#define DSP2_BLBACK_HIST0_44_R_MSK                               (((1U<<DSP2_BLBACK_HIST0_44_R_LEN)-1)<<DSP2_BLBACK_HIST0_44_R_POS)
#define DSP2_BLBACK_HIST0_44_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST0_44_R_LEN)-1)<<DSP2_BLBACK_HIST0_44_R_POS))

/* 0xAB4 : REG_HIST0_45 */
#define DSP2_BLBACK_REG_HIST0_45_OFFSET                          (0xAB4)
#define DSP2_BLBACK_HIST0_45_R                                   DSP2_BLBACK_HIST0_45_R
#define DSP2_BLBACK_HIST0_45_R_POS                               (0U)
#define DSP2_BLBACK_HIST0_45_R_LEN                               (24U)
#define DSP2_BLBACK_HIST0_45_R_MSK                               (((1U<<DSP2_BLBACK_HIST0_45_R_LEN)-1)<<DSP2_BLBACK_HIST0_45_R_POS)
#define DSP2_BLBACK_HIST0_45_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST0_45_R_LEN)-1)<<DSP2_BLBACK_HIST0_45_R_POS))

/* 0xAB8 : REG_HIST0_46 */
#define DSP2_BLBACK_REG_HIST0_46_OFFSET                          (0xAB8)
#define DSP2_BLBACK_HIST0_46_R                                   DSP2_BLBACK_HIST0_46_R
#define DSP2_BLBACK_HIST0_46_R_POS                               (0U)
#define DSP2_BLBACK_HIST0_46_R_LEN                               (24U)
#define DSP2_BLBACK_HIST0_46_R_MSK                               (((1U<<DSP2_BLBACK_HIST0_46_R_LEN)-1)<<DSP2_BLBACK_HIST0_46_R_POS)
#define DSP2_BLBACK_HIST0_46_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST0_46_R_LEN)-1)<<DSP2_BLBACK_HIST0_46_R_POS))

/* 0xABC : REG_HIST0_47 */
#define DSP2_BLBACK_REG_HIST0_47_OFFSET                          (0xABC)
#define DSP2_BLBACK_HIST0_47_R                                   DSP2_BLBACK_HIST0_47_R
#define DSP2_BLBACK_HIST0_47_R_POS                               (0U)
#define DSP2_BLBACK_HIST0_47_R_LEN                               (24U)
#define DSP2_BLBACK_HIST0_47_R_MSK                               (((1U<<DSP2_BLBACK_HIST0_47_R_LEN)-1)<<DSP2_BLBACK_HIST0_47_R_POS)
#define DSP2_BLBACK_HIST0_47_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST0_47_R_LEN)-1)<<DSP2_BLBACK_HIST0_47_R_POS))

/* 0xAC0 : REG_HIST0_48 */
#define DSP2_BLBACK_REG_HIST0_48_OFFSET                          (0xAC0)
#define DSP2_BLBACK_HIST0_48_R                                   DSP2_BLBACK_HIST0_48_R
#define DSP2_BLBACK_HIST0_48_R_POS                               (0U)
#define DSP2_BLBACK_HIST0_48_R_LEN                               (24U)
#define DSP2_BLBACK_HIST0_48_R_MSK                               (((1U<<DSP2_BLBACK_HIST0_48_R_LEN)-1)<<DSP2_BLBACK_HIST0_48_R_POS)
#define DSP2_BLBACK_HIST0_48_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST0_48_R_LEN)-1)<<DSP2_BLBACK_HIST0_48_R_POS))

/* 0xAC4 : REG_HIST0_49 */
#define DSP2_BLBACK_REG_HIST0_49_OFFSET                          (0xAC4)
#define DSP2_BLBACK_HIST0_49_R                                   DSP2_BLBACK_HIST0_49_R
#define DSP2_BLBACK_HIST0_49_R_POS                               (0U)
#define DSP2_BLBACK_HIST0_49_R_LEN                               (24U)
#define DSP2_BLBACK_HIST0_49_R_MSK                               (((1U<<DSP2_BLBACK_HIST0_49_R_LEN)-1)<<DSP2_BLBACK_HIST0_49_R_POS)
#define DSP2_BLBACK_HIST0_49_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST0_49_R_LEN)-1)<<DSP2_BLBACK_HIST0_49_R_POS))

/* 0xAC8 : REG_HIST0_50 */
#define DSP2_BLBACK_REG_HIST0_50_OFFSET                          (0xAC8)
#define DSP2_BLBACK_HIST0_50_R                                   DSP2_BLBACK_HIST0_50_R
#define DSP2_BLBACK_HIST0_50_R_POS                               (0U)
#define DSP2_BLBACK_HIST0_50_R_LEN                               (24U)
#define DSP2_BLBACK_HIST0_50_R_MSK                               (((1U<<DSP2_BLBACK_HIST0_50_R_LEN)-1)<<DSP2_BLBACK_HIST0_50_R_POS)
#define DSP2_BLBACK_HIST0_50_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST0_50_R_LEN)-1)<<DSP2_BLBACK_HIST0_50_R_POS))

/* 0xACC : REG_HIST0_51 */
#define DSP2_BLBACK_REG_HIST0_51_OFFSET                          (0xACC)
#define DSP2_BLBACK_HIST0_51_R                                   DSP2_BLBACK_HIST0_51_R
#define DSP2_BLBACK_HIST0_51_R_POS                               (0U)
#define DSP2_BLBACK_HIST0_51_R_LEN                               (24U)
#define DSP2_BLBACK_HIST0_51_R_MSK                               (((1U<<DSP2_BLBACK_HIST0_51_R_LEN)-1)<<DSP2_BLBACK_HIST0_51_R_POS)
#define DSP2_BLBACK_HIST0_51_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST0_51_R_LEN)-1)<<DSP2_BLBACK_HIST0_51_R_POS))

/* 0xAD0 : REG_HIST0_52 */
#define DSP2_BLBACK_REG_HIST0_52_OFFSET                          (0xAD0)
#define DSP2_BLBACK_HIST0_52_R                                   DSP2_BLBACK_HIST0_52_R
#define DSP2_BLBACK_HIST0_52_R_POS                               (0U)
#define DSP2_BLBACK_HIST0_52_R_LEN                               (24U)
#define DSP2_BLBACK_HIST0_52_R_MSK                               (((1U<<DSP2_BLBACK_HIST0_52_R_LEN)-1)<<DSP2_BLBACK_HIST0_52_R_POS)
#define DSP2_BLBACK_HIST0_52_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST0_52_R_LEN)-1)<<DSP2_BLBACK_HIST0_52_R_POS))

/* 0xAD4 : REG_HIST0_53 */
#define DSP2_BLBACK_REG_HIST0_53_OFFSET                          (0xAD4)
#define DSP2_BLBACK_HIST0_53_R                                   DSP2_BLBACK_HIST0_53_R
#define DSP2_BLBACK_HIST0_53_R_POS                               (0U)
#define DSP2_BLBACK_HIST0_53_R_LEN                               (24U)
#define DSP2_BLBACK_HIST0_53_R_MSK                               (((1U<<DSP2_BLBACK_HIST0_53_R_LEN)-1)<<DSP2_BLBACK_HIST0_53_R_POS)
#define DSP2_BLBACK_HIST0_53_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST0_53_R_LEN)-1)<<DSP2_BLBACK_HIST0_53_R_POS))

/* 0xAD8 : REG_HIST0_54 */
#define DSP2_BLBACK_REG_HIST0_54_OFFSET                          (0xAD8)
#define DSP2_BLBACK_HIST0_54_R                                   DSP2_BLBACK_HIST0_54_R
#define DSP2_BLBACK_HIST0_54_R_POS                               (0U)
#define DSP2_BLBACK_HIST0_54_R_LEN                               (24U)
#define DSP2_BLBACK_HIST0_54_R_MSK                               (((1U<<DSP2_BLBACK_HIST0_54_R_LEN)-1)<<DSP2_BLBACK_HIST0_54_R_POS)
#define DSP2_BLBACK_HIST0_54_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST0_54_R_LEN)-1)<<DSP2_BLBACK_HIST0_54_R_POS))

/* 0xADC : REG_HIST0_55 */
#define DSP2_BLBACK_REG_HIST0_55_OFFSET                          (0xADC)
#define DSP2_BLBACK_HIST0_55_R                                   DSP2_BLBACK_HIST0_55_R
#define DSP2_BLBACK_HIST0_55_R_POS                               (0U)
#define DSP2_BLBACK_HIST0_55_R_LEN                               (24U)
#define DSP2_BLBACK_HIST0_55_R_MSK                               (((1U<<DSP2_BLBACK_HIST0_55_R_LEN)-1)<<DSP2_BLBACK_HIST0_55_R_POS)
#define DSP2_BLBACK_HIST0_55_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST0_55_R_LEN)-1)<<DSP2_BLBACK_HIST0_55_R_POS))

/* 0xAE0 : REG_HIST0_56 */
#define DSP2_BLBACK_REG_HIST0_56_OFFSET                          (0xAE0)
#define DSP2_BLBACK_HIST0_56_R                                   DSP2_BLBACK_HIST0_56_R
#define DSP2_BLBACK_HIST0_56_R_POS                               (0U)
#define DSP2_BLBACK_HIST0_56_R_LEN                               (24U)
#define DSP2_BLBACK_HIST0_56_R_MSK                               (((1U<<DSP2_BLBACK_HIST0_56_R_LEN)-1)<<DSP2_BLBACK_HIST0_56_R_POS)
#define DSP2_BLBACK_HIST0_56_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST0_56_R_LEN)-1)<<DSP2_BLBACK_HIST0_56_R_POS))

/* 0xAE4 : REG_HIST0_57 */
#define DSP2_BLBACK_REG_HIST0_57_OFFSET                          (0xAE4)
#define DSP2_BLBACK_HIST0_57_R                                   DSP2_BLBACK_HIST0_57_R
#define DSP2_BLBACK_HIST0_57_R_POS                               (0U)
#define DSP2_BLBACK_HIST0_57_R_LEN                               (24U)
#define DSP2_BLBACK_HIST0_57_R_MSK                               (((1U<<DSP2_BLBACK_HIST0_57_R_LEN)-1)<<DSP2_BLBACK_HIST0_57_R_POS)
#define DSP2_BLBACK_HIST0_57_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST0_57_R_LEN)-1)<<DSP2_BLBACK_HIST0_57_R_POS))

/* 0xAE8 : REG_HIST0_58 */
#define DSP2_BLBACK_REG_HIST0_58_OFFSET                          (0xAE8)
#define DSP2_BLBACK_HIST0_58_R                                   DSP2_BLBACK_HIST0_58_R
#define DSP2_BLBACK_HIST0_58_R_POS                               (0U)
#define DSP2_BLBACK_HIST0_58_R_LEN                               (24U)
#define DSP2_BLBACK_HIST0_58_R_MSK                               (((1U<<DSP2_BLBACK_HIST0_58_R_LEN)-1)<<DSP2_BLBACK_HIST0_58_R_POS)
#define DSP2_BLBACK_HIST0_58_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST0_58_R_LEN)-1)<<DSP2_BLBACK_HIST0_58_R_POS))

/* 0xAEC : REG_HIST0_59 */
#define DSP2_BLBACK_REG_HIST0_59_OFFSET                          (0xAEC)
#define DSP2_BLBACK_HIST0_59_R                                   DSP2_BLBACK_HIST0_59_R
#define DSP2_BLBACK_HIST0_59_R_POS                               (0U)
#define DSP2_BLBACK_HIST0_59_R_LEN                               (24U)
#define DSP2_BLBACK_HIST0_59_R_MSK                               (((1U<<DSP2_BLBACK_HIST0_59_R_LEN)-1)<<DSP2_BLBACK_HIST0_59_R_POS)
#define DSP2_BLBACK_HIST0_59_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST0_59_R_LEN)-1)<<DSP2_BLBACK_HIST0_59_R_POS))

/* 0xAF0 : REG_HIST0_60 */
#define DSP2_BLBACK_REG_HIST0_60_OFFSET                          (0xAF0)
#define DSP2_BLBACK_HIST0_60_R                                   DSP2_BLBACK_HIST0_60_R
#define DSP2_BLBACK_HIST0_60_R_POS                               (0U)
#define DSP2_BLBACK_HIST0_60_R_LEN                               (24U)
#define DSP2_BLBACK_HIST0_60_R_MSK                               (((1U<<DSP2_BLBACK_HIST0_60_R_LEN)-1)<<DSP2_BLBACK_HIST0_60_R_POS)
#define DSP2_BLBACK_HIST0_60_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST0_60_R_LEN)-1)<<DSP2_BLBACK_HIST0_60_R_POS))

/* 0xAF4 : REG_HIST0_61 */
#define DSP2_BLBACK_REG_HIST0_61_OFFSET                          (0xAF4)
#define DSP2_BLBACK_HIST0_61_R                                   DSP2_BLBACK_HIST0_61_R
#define DSP2_BLBACK_HIST0_61_R_POS                               (0U)
#define DSP2_BLBACK_HIST0_61_R_LEN                               (24U)
#define DSP2_BLBACK_HIST0_61_R_MSK                               (((1U<<DSP2_BLBACK_HIST0_61_R_LEN)-1)<<DSP2_BLBACK_HIST0_61_R_POS)
#define DSP2_BLBACK_HIST0_61_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST0_61_R_LEN)-1)<<DSP2_BLBACK_HIST0_61_R_POS))

/* 0xAF8 : REG_HIST0_62 */
#define DSP2_BLBACK_REG_HIST0_62_OFFSET                          (0xAF8)
#define DSP2_BLBACK_HIST0_62_R                                   DSP2_BLBACK_HIST0_62_R
#define DSP2_BLBACK_HIST0_62_R_POS                               (0U)
#define DSP2_BLBACK_HIST0_62_R_LEN                               (24U)
#define DSP2_BLBACK_HIST0_62_R_MSK                               (((1U<<DSP2_BLBACK_HIST0_62_R_LEN)-1)<<DSP2_BLBACK_HIST0_62_R_POS)
#define DSP2_BLBACK_HIST0_62_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST0_62_R_LEN)-1)<<DSP2_BLBACK_HIST0_62_R_POS))

/* 0xAFC : REG_HIST0_63 */
#define DSP2_BLBACK_REG_HIST0_63_OFFSET                          (0xAFC)
#define DSP2_BLBACK_HIST0_63_R                                   DSP2_BLBACK_HIST0_63_R
#define DSP2_BLBACK_HIST0_63_R_POS                               (0U)
#define DSP2_BLBACK_HIST0_63_R_LEN                               (24U)
#define DSP2_BLBACK_HIST0_63_R_MSK                               (((1U<<DSP2_BLBACK_HIST0_63_R_LEN)-1)<<DSP2_BLBACK_HIST0_63_R_POS)
#define DSP2_BLBACK_HIST0_63_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST0_63_R_LEN)-1)<<DSP2_BLBACK_HIST0_63_R_POS))

/* 0xB00 : REG_HIST1_0 */
#define DSP2_BLBACK_REG_HIST1_0_OFFSET                           (0xB00)
#define DSP2_BLBACK_HIST1_0_R                                    DSP2_BLBACK_HIST1_0_R
#define DSP2_BLBACK_HIST1_0_R_POS                                (0U)
#define DSP2_BLBACK_HIST1_0_R_LEN                                (24U)
#define DSP2_BLBACK_HIST1_0_R_MSK                                (((1U<<DSP2_BLBACK_HIST1_0_R_LEN)-1)<<DSP2_BLBACK_HIST1_0_R_POS)
#define DSP2_BLBACK_HIST1_0_R_UMSK                               (~(((1U<<DSP2_BLBACK_HIST1_0_R_LEN)-1)<<DSP2_BLBACK_HIST1_0_R_POS))

/* 0xB04 : REG_HIST1_1 */
#define DSP2_BLBACK_REG_HIST1_1_OFFSET                           (0xB04)
#define DSP2_BLBACK_HIST1_1_R                                    DSP2_BLBACK_HIST1_1_R
#define DSP2_BLBACK_HIST1_1_R_POS                                (0U)
#define DSP2_BLBACK_HIST1_1_R_LEN                                (24U)
#define DSP2_BLBACK_HIST1_1_R_MSK                                (((1U<<DSP2_BLBACK_HIST1_1_R_LEN)-1)<<DSP2_BLBACK_HIST1_1_R_POS)
#define DSP2_BLBACK_HIST1_1_R_UMSK                               (~(((1U<<DSP2_BLBACK_HIST1_1_R_LEN)-1)<<DSP2_BLBACK_HIST1_1_R_POS))

/* 0xB08 : REG_HIST1_2 */
#define DSP2_BLBACK_REG_HIST1_2_OFFSET                           (0xB08)
#define DSP2_BLBACK_HIST1_2_R                                    DSP2_BLBACK_HIST1_2_R
#define DSP2_BLBACK_HIST1_2_R_POS                                (0U)
#define DSP2_BLBACK_HIST1_2_R_LEN                                (24U)
#define DSP2_BLBACK_HIST1_2_R_MSK                                (((1U<<DSP2_BLBACK_HIST1_2_R_LEN)-1)<<DSP2_BLBACK_HIST1_2_R_POS)
#define DSP2_BLBACK_HIST1_2_R_UMSK                               (~(((1U<<DSP2_BLBACK_HIST1_2_R_LEN)-1)<<DSP2_BLBACK_HIST1_2_R_POS))

/* 0xB0C : REG_HIST1_3 */
#define DSP2_BLBACK_REG_HIST1_3_OFFSET                           (0xB0C)
#define DSP2_BLBACK_HIST1_3_R                                    DSP2_BLBACK_HIST1_3_R
#define DSP2_BLBACK_HIST1_3_R_POS                                (0U)
#define DSP2_BLBACK_HIST1_3_R_LEN                                (24U)
#define DSP2_BLBACK_HIST1_3_R_MSK                                (((1U<<DSP2_BLBACK_HIST1_3_R_LEN)-1)<<DSP2_BLBACK_HIST1_3_R_POS)
#define DSP2_BLBACK_HIST1_3_R_UMSK                               (~(((1U<<DSP2_BLBACK_HIST1_3_R_LEN)-1)<<DSP2_BLBACK_HIST1_3_R_POS))

/* 0xB10 : REG_HIST1_4 */
#define DSP2_BLBACK_REG_HIST1_4_OFFSET                           (0xB10)
#define DSP2_BLBACK_HIST1_4_R                                    DSP2_BLBACK_HIST1_4_R
#define DSP2_BLBACK_HIST1_4_R_POS                                (0U)
#define DSP2_BLBACK_HIST1_4_R_LEN                                (24U)
#define DSP2_BLBACK_HIST1_4_R_MSK                                (((1U<<DSP2_BLBACK_HIST1_4_R_LEN)-1)<<DSP2_BLBACK_HIST1_4_R_POS)
#define DSP2_BLBACK_HIST1_4_R_UMSK                               (~(((1U<<DSP2_BLBACK_HIST1_4_R_LEN)-1)<<DSP2_BLBACK_HIST1_4_R_POS))

/* 0xB14 : REG_HIST1_5 */
#define DSP2_BLBACK_REG_HIST1_5_OFFSET                           (0xB14)
#define DSP2_BLBACK_HIST1_5_R                                    DSP2_BLBACK_HIST1_5_R
#define DSP2_BLBACK_HIST1_5_R_POS                                (0U)
#define DSP2_BLBACK_HIST1_5_R_LEN                                (24U)
#define DSP2_BLBACK_HIST1_5_R_MSK                                (((1U<<DSP2_BLBACK_HIST1_5_R_LEN)-1)<<DSP2_BLBACK_HIST1_5_R_POS)
#define DSP2_BLBACK_HIST1_5_R_UMSK                               (~(((1U<<DSP2_BLBACK_HIST1_5_R_LEN)-1)<<DSP2_BLBACK_HIST1_5_R_POS))

/* 0xB18 : REG_HIST1_6 */
#define DSP2_BLBACK_REG_HIST1_6_OFFSET                           (0xB18)
#define DSP2_BLBACK_HIST1_6_R                                    DSP2_BLBACK_HIST1_6_R
#define DSP2_BLBACK_HIST1_6_R_POS                                (0U)
#define DSP2_BLBACK_HIST1_6_R_LEN                                (24U)
#define DSP2_BLBACK_HIST1_6_R_MSK                                (((1U<<DSP2_BLBACK_HIST1_6_R_LEN)-1)<<DSP2_BLBACK_HIST1_6_R_POS)
#define DSP2_BLBACK_HIST1_6_R_UMSK                               (~(((1U<<DSP2_BLBACK_HIST1_6_R_LEN)-1)<<DSP2_BLBACK_HIST1_6_R_POS))

/* 0xB1C : REG_HIST1_7 */
#define DSP2_BLBACK_REG_HIST1_7_OFFSET                           (0xB1C)
#define DSP2_BLBACK_HIST1_7_R                                    DSP2_BLBACK_HIST1_7_R
#define DSP2_BLBACK_HIST1_7_R_POS                                (0U)
#define DSP2_BLBACK_HIST1_7_R_LEN                                (24U)
#define DSP2_BLBACK_HIST1_7_R_MSK                                (((1U<<DSP2_BLBACK_HIST1_7_R_LEN)-1)<<DSP2_BLBACK_HIST1_7_R_POS)
#define DSP2_BLBACK_HIST1_7_R_UMSK                               (~(((1U<<DSP2_BLBACK_HIST1_7_R_LEN)-1)<<DSP2_BLBACK_HIST1_7_R_POS))

/* 0xB20 : REG_HIST1_8 */
#define DSP2_BLBACK_REG_HIST1_8_OFFSET                           (0xB20)
#define DSP2_BLBACK_HIST1_8_R                                    DSP2_BLBACK_HIST1_8_R
#define DSP2_BLBACK_HIST1_8_R_POS                                (0U)
#define DSP2_BLBACK_HIST1_8_R_LEN                                (24U)
#define DSP2_BLBACK_HIST1_8_R_MSK                                (((1U<<DSP2_BLBACK_HIST1_8_R_LEN)-1)<<DSP2_BLBACK_HIST1_8_R_POS)
#define DSP2_BLBACK_HIST1_8_R_UMSK                               (~(((1U<<DSP2_BLBACK_HIST1_8_R_LEN)-1)<<DSP2_BLBACK_HIST1_8_R_POS))

/* 0xB24 : REG_HIST1_9 */
#define DSP2_BLBACK_REG_HIST1_9_OFFSET                           (0xB24)
#define DSP2_BLBACK_HIST1_9_R                                    DSP2_BLBACK_HIST1_9_R
#define DSP2_BLBACK_HIST1_9_R_POS                                (0U)
#define DSP2_BLBACK_HIST1_9_R_LEN                                (24U)
#define DSP2_BLBACK_HIST1_9_R_MSK                                (((1U<<DSP2_BLBACK_HIST1_9_R_LEN)-1)<<DSP2_BLBACK_HIST1_9_R_POS)
#define DSP2_BLBACK_HIST1_9_R_UMSK                               (~(((1U<<DSP2_BLBACK_HIST1_9_R_LEN)-1)<<DSP2_BLBACK_HIST1_9_R_POS))

/* 0xB28 : REG_HIST1_10 */
#define DSP2_BLBACK_REG_HIST1_10_OFFSET                          (0xB28)
#define DSP2_BLBACK_HIST1_10_R                                   DSP2_BLBACK_HIST1_10_R
#define DSP2_BLBACK_HIST1_10_R_POS                               (0U)
#define DSP2_BLBACK_HIST1_10_R_LEN                               (24U)
#define DSP2_BLBACK_HIST1_10_R_MSK                               (((1U<<DSP2_BLBACK_HIST1_10_R_LEN)-1)<<DSP2_BLBACK_HIST1_10_R_POS)
#define DSP2_BLBACK_HIST1_10_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST1_10_R_LEN)-1)<<DSP2_BLBACK_HIST1_10_R_POS))

/* 0xB2C : REG_HIST1_11 */
#define DSP2_BLBACK_REG_HIST1_11_OFFSET                          (0xB2C)
#define DSP2_BLBACK_HIST1_11_R                                   DSP2_BLBACK_HIST1_11_R
#define DSP2_BLBACK_HIST1_11_R_POS                               (0U)
#define DSP2_BLBACK_HIST1_11_R_LEN                               (24U)
#define DSP2_BLBACK_HIST1_11_R_MSK                               (((1U<<DSP2_BLBACK_HIST1_11_R_LEN)-1)<<DSP2_BLBACK_HIST1_11_R_POS)
#define DSP2_BLBACK_HIST1_11_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST1_11_R_LEN)-1)<<DSP2_BLBACK_HIST1_11_R_POS))

/* 0xB30 : REG_HIST1_12 */
#define DSP2_BLBACK_REG_HIST1_12_OFFSET                          (0xB30)
#define DSP2_BLBACK_HIST1_12_R                                   DSP2_BLBACK_HIST1_12_R
#define DSP2_BLBACK_HIST1_12_R_POS                               (0U)
#define DSP2_BLBACK_HIST1_12_R_LEN                               (24U)
#define DSP2_BLBACK_HIST1_12_R_MSK                               (((1U<<DSP2_BLBACK_HIST1_12_R_LEN)-1)<<DSP2_BLBACK_HIST1_12_R_POS)
#define DSP2_BLBACK_HIST1_12_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST1_12_R_LEN)-1)<<DSP2_BLBACK_HIST1_12_R_POS))

/* 0xB34 : REG_HIST1_13 */
#define DSP2_BLBACK_REG_HIST1_13_OFFSET                          (0xB34)
#define DSP2_BLBACK_HIST1_13_R                                   DSP2_BLBACK_HIST1_13_R
#define DSP2_BLBACK_HIST1_13_R_POS                               (0U)
#define DSP2_BLBACK_HIST1_13_R_LEN                               (24U)
#define DSP2_BLBACK_HIST1_13_R_MSK                               (((1U<<DSP2_BLBACK_HIST1_13_R_LEN)-1)<<DSP2_BLBACK_HIST1_13_R_POS)
#define DSP2_BLBACK_HIST1_13_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST1_13_R_LEN)-1)<<DSP2_BLBACK_HIST1_13_R_POS))

/* 0xB38 : REG_HIST1_14 */
#define DSP2_BLBACK_REG_HIST1_14_OFFSET                          (0xB38)
#define DSP2_BLBACK_HIST1_14_R                                   DSP2_BLBACK_HIST1_14_R
#define DSP2_BLBACK_HIST1_14_R_POS                               (0U)
#define DSP2_BLBACK_HIST1_14_R_LEN                               (24U)
#define DSP2_BLBACK_HIST1_14_R_MSK                               (((1U<<DSP2_BLBACK_HIST1_14_R_LEN)-1)<<DSP2_BLBACK_HIST1_14_R_POS)
#define DSP2_BLBACK_HIST1_14_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST1_14_R_LEN)-1)<<DSP2_BLBACK_HIST1_14_R_POS))

/* 0xB3C : REG_HIST1_15 */
#define DSP2_BLBACK_REG_HIST1_15_OFFSET                          (0xB3C)
#define DSP2_BLBACK_HIST1_15_R                                   DSP2_BLBACK_HIST1_15_R
#define DSP2_BLBACK_HIST1_15_R_POS                               (0U)
#define DSP2_BLBACK_HIST1_15_R_LEN                               (24U)
#define DSP2_BLBACK_HIST1_15_R_MSK                               (((1U<<DSP2_BLBACK_HIST1_15_R_LEN)-1)<<DSP2_BLBACK_HIST1_15_R_POS)
#define DSP2_BLBACK_HIST1_15_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST1_15_R_LEN)-1)<<DSP2_BLBACK_HIST1_15_R_POS))

/* 0xB40 : REG_HIST1_16 */
#define DSP2_BLBACK_REG_HIST1_16_OFFSET                          (0xB40)
#define DSP2_BLBACK_HIST1_16_R                                   DSP2_BLBACK_HIST1_16_R
#define DSP2_BLBACK_HIST1_16_R_POS                               (0U)
#define DSP2_BLBACK_HIST1_16_R_LEN                               (24U)
#define DSP2_BLBACK_HIST1_16_R_MSK                               (((1U<<DSP2_BLBACK_HIST1_16_R_LEN)-1)<<DSP2_BLBACK_HIST1_16_R_POS)
#define DSP2_BLBACK_HIST1_16_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST1_16_R_LEN)-1)<<DSP2_BLBACK_HIST1_16_R_POS))

/* 0xB44 : REG_HIST1_17 */
#define DSP2_BLBACK_REG_HIST1_17_OFFSET                          (0xB44)
#define DSP2_BLBACK_HIST1_17_R                                   DSP2_BLBACK_HIST1_17_R
#define DSP2_BLBACK_HIST1_17_R_POS                               (0U)
#define DSP2_BLBACK_HIST1_17_R_LEN                               (24U)
#define DSP2_BLBACK_HIST1_17_R_MSK                               (((1U<<DSP2_BLBACK_HIST1_17_R_LEN)-1)<<DSP2_BLBACK_HIST1_17_R_POS)
#define DSP2_BLBACK_HIST1_17_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST1_17_R_LEN)-1)<<DSP2_BLBACK_HIST1_17_R_POS))

/* 0xB48 : REG_HIST1_18 */
#define DSP2_BLBACK_REG_HIST1_18_OFFSET                          (0xB48)
#define DSP2_BLBACK_HIST1_18_R                                   DSP2_BLBACK_HIST1_18_R
#define DSP2_BLBACK_HIST1_18_R_POS                               (0U)
#define DSP2_BLBACK_HIST1_18_R_LEN                               (24U)
#define DSP2_BLBACK_HIST1_18_R_MSK                               (((1U<<DSP2_BLBACK_HIST1_18_R_LEN)-1)<<DSP2_BLBACK_HIST1_18_R_POS)
#define DSP2_BLBACK_HIST1_18_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST1_18_R_LEN)-1)<<DSP2_BLBACK_HIST1_18_R_POS))

/* 0xB4C : REG_HIST1_19 */
#define DSP2_BLBACK_REG_HIST1_19_OFFSET                          (0xB4C)
#define DSP2_BLBACK_HIST1_19_R                                   DSP2_BLBACK_HIST1_19_R
#define DSP2_BLBACK_HIST1_19_R_POS                               (0U)
#define DSP2_BLBACK_HIST1_19_R_LEN                               (24U)
#define DSP2_BLBACK_HIST1_19_R_MSK                               (((1U<<DSP2_BLBACK_HIST1_19_R_LEN)-1)<<DSP2_BLBACK_HIST1_19_R_POS)
#define DSP2_BLBACK_HIST1_19_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST1_19_R_LEN)-1)<<DSP2_BLBACK_HIST1_19_R_POS))

/* 0xB50 : REG_HIST1_20 */
#define DSP2_BLBACK_REG_HIST1_20_OFFSET                          (0xB50)
#define DSP2_BLBACK_HIST1_20_R                                   DSP2_BLBACK_HIST1_20_R
#define DSP2_BLBACK_HIST1_20_R_POS                               (0U)
#define DSP2_BLBACK_HIST1_20_R_LEN                               (24U)
#define DSP2_BLBACK_HIST1_20_R_MSK                               (((1U<<DSP2_BLBACK_HIST1_20_R_LEN)-1)<<DSP2_BLBACK_HIST1_20_R_POS)
#define DSP2_BLBACK_HIST1_20_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST1_20_R_LEN)-1)<<DSP2_BLBACK_HIST1_20_R_POS))

/* 0xB54 : REG_HIST1_21 */
#define DSP2_BLBACK_REG_HIST1_21_OFFSET                          (0xB54)
#define DSP2_BLBACK_HIST1_21_R                                   DSP2_BLBACK_HIST1_21_R
#define DSP2_BLBACK_HIST1_21_R_POS                               (0U)
#define DSP2_BLBACK_HIST1_21_R_LEN                               (24U)
#define DSP2_BLBACK_HIST1_21_R_MSK                               (((1U<<DSP2_BLBACK_HIST1_21_R_LEN)-1)<<DSP2_BLBACK_HIST1_21_R_POS)
#define DSP2_BLBACK_HIST1_21_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST1_21_R_LEN)-1)<<DSP2_BLBACK_HIST1_21_R_POS))

/* 0xB58 : REG_HIST1_22 */
#define DSP2_BLBACK_REG_HIST1_22_OFFSET                          (0xB58)
#define DSP2_BLBACK_HIST1_22_R                                   DSP2_BLBACK_HIST1_22_R
#define DSP2_BLBACK_HIST1_22_R_POS                               (0U)
#define DSP2_BLBACK_HIST1_22_R_LEN                               (24U)
#define DSP2_BLBACK_HIST1_22_R_MSK                               (((1U<<DSP2_BLBACK_HIST1_22_R_LEN)-1)<<DSP2_BLBACK_HIST1_22_R_POS)
#define DSP2_BLBACK_HIST1_22_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST1_22_R_LEN)-1)<<DSP2_BLBACK_HIST1_22_R_POS))

/* 0xB5C : REG_HIST1_23 */
#define DSP2_BLBACK_REG_HIST1_23_OFFSET                          (0xB5C)
#define DSP2_BLBACK_HIST1_23_R                                   DSP2_BLBACK_HIST1_23_R
#define DSP2_BLBACK_HIST1_23_R_POS                               (0U)
#define DSP2_BLBACK_HIST1_23_R_LEN                               (24U)
#define DSP2_BLBACK_HIST1_23_R_MSK                               (((1U<<DSP2_BLBACK_HIST1_23_R_LEN)-1)<<DSP2_BLBACK_HIST1_23_R_POS)
#define DSP2_BLBACK_HIST1_23_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST1_23_R_LEN)-1)<<DSP2_BLBACK_HIST1_23_R_POS))

/* 0xB60 : REG_HIST1_24 */
#define DSP2_BLBACK_REG_HIST1_24_OFFSET                          (0xB60)
#define DSP2_BLBACK_HIST1_24_R                                   DSP2_BLBACK_HIST1_24_R
#define DSP2_BLBACK_HIST1_24_R_POS                               (0U)
#define DSP2_BLBACK_HIST1_24_R_LEN                               (24U)
#define DSP2_BLBACK_HIST1_24_R_MSK                               (((1U<<DSP2_BLBACK_HIST1_24_R_LEN)-1)<<DSP2_BLBACK_HIST1_24_R_POS)
#define DSP2_BLBACK_HIST1_24_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST1_24_R_LEN)-1)<<DSP2_BLBACK_HIST1_24_R_POS))

/* 0xB64 : REG_HIST1_25 */
#define DSP2_BLBACK_REG_HIST1_25_OFFSET                          (0xB64)
#define DSP2_BLBACK_HIST1_25_R                                   DSP2_BLBACK_HIST1_25_R
#define DSP2_BLBACK_HIST1_25_R_POS                               (0U)
#define DSP2_BLBACK_HIST1_25_R_LEN                               (24U)
#define DSP2_BLBACK_HIST1_25_R_MSK                               (((1U<<DSP2_BLBACK_HIST1_25_R_LEN)-1)<<DSP2_BLBACK_HIST1_25_R_POS)
#define DSP2_BLBACK_HIST1_25_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST1_25_R_LEN)-1)<<DSP2_BLBACK_HIST1_25_R_POS))

/* 0xB68 : REG_HIST1_26 */
#define DSP2_BLBACK_REG_HIST1_26_OFFSET                          (0xB68)
#define DSP2_BLBACK_HIST1_26_R                                   DSP2_BLBACK_HIST1_26_R
#define DSP2_BLBACK_HIST1_26_R_POS                               (0U)
#define DSP2_BLBACK_HIST1_26_R_LEN                               (24U)
#define DSP2_BLBACK_HIST1_26_R_MSK                               (((1U<<DSP2_BLBACK_HIST1_26_R_LEN)-1)<<DSP2_BLBACK_HIST1_26_R_POS)
#define DSP2_BLBACK_HIST1_26_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST1_26_R_LEN)-1)<<DSP2_BLBACK_HIST1_26_R_POS))

/* 0xB6C : REG_HIST1_27 */
#define DSP2_BLBACK_REG_HIST1_27_OFFSET                          (0xB6C)
#define DSP2_BLBACK_HIST1_27_R                                   DSP2_BLBACK_HIST1_27_R
#define DSP2_BLBACK_HIST1_27_R_POS                               (0U)
#define DSP2_BLBACK_HIST1_27_R_LEN                               (24U)
#define DSP2_BLBACK_HIST1_27_R_MSK                               (((1U<<DSP2_BLBACK_HIST1_27_R_LEN)-1)<<DSP2_BLBACK_HIST1_27_R_POS)
#define DSP2_BLBACK_HIST1_27_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST1_27_R_LEN)-1)<<DSP2_BLBACK_HIST1_27_R_POS))

/* 0xB70 : REG_HIST1_28 */
#define DSP2_BLBACK_REG_HIST1_28_OFFSET                          (0xB70)
#define DSP2_BLBACK_HIST1_28_R                                   DSP2_BLBACK_HIST1_28_R
#define DSP2_BLBACK_HIST1_28_R_POS                               (0U)
#define DSP2_BLBACK_HIST1_28_R_LEN                               (24U)
#define DSP2_BLBACK_HIST1_28_R_MSK                               (((1U<<DSP2_BLBACK_HIST1_28_R_LEN)-1)<<DSP2_BLBACK_HIST1_28_R_POS)
#define DSP2_BLBACK_HIST1_28_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST1_28_R_LEN)-1)<<DSP2_BLBACK_HIST1_28_R_POS))

/* 0xB74 : REG_HIST1_29 */
#define DSP2_BLBACK_REG_HIST1_29_OFFSET                          (0xB74)
#define DSP2_BLBACK_HIST1_29_R                                   DSP2_BLBACK_HIST1_29_R
#define DSP2_BLBACK_HIST1_29_R_POS                               (0U)
#define DSP2_BLBACK_HIST1_29_R_LEN                               (24U)
#define DSP2_BLBACK_HIST1_29_R_MSK                               (((1U<<DSP2_BLBACK_HIST1_29_R_LEN)-1)<<DSP2_BLBACK_HIST1_29_R_POS)
#define DSP2_BLBACK_HIST1_29_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST1_29_R_LEN)-1)<<DSP2_BLBACK_HIST1_29_R_POS))

/* 0xB78 : REG_HIST1_30 */
#define DSP2_BLBACK_REG_HIST1_30_OFFSET                          (0xB78)
#define DSP2_BLBACK_HIST1_30_R                                   DSP2_BLBACK_HIST1_30_R
#define DSP2_BLBACK_HIST1_30_R_POS                               (0U)
#define DSP2_BLBACK_HIST1_30_R_LEN                               (24U)
#define DSP2_BLBACK_HIST1_30_R_MSK                               (((1U<<DSP2_BLBACK_HIST1_30_R_LEN)-1)<<DSP2_BLBACK_HIST1_30_R_POS)
#define DSP2_BLBACK_HIST1_30_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST1_30_R_LEN)-1)<<DSP2_BLBACK_HIST1_30_R_POS))

/* 0xB7C : REG_HIST1_31 */
#define DSP2_BLBACK_REG_HIST1_31_OFFSET                          (0xB7C)
#define DSP2_BLBACK_HIST1_31_R                                   DSP2_BLBACK_HIST1_31_R
#define DSP2_BLBACK_HIST1_31_R_POS                               (0U)
#define DSP2_BLBACK_HIST1_31_R_LEN                               (24U)
#define DSP2_BLBACK_HIST1_31_R_MSK                               (((1U<<DSP2_BLBACK_HIST1_31_R_LEN)-1)<<DSP2_BLBACK_HIST1_31_R_POS)
#define DSP2_BLBACK_HIST1_31_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST1_31_R_LEN)-1)<<DSP2_BLBACK_HIST1_31_R_POS))

/* 0xB80 : REG_HIST1_32 */
#define DSP2_BLBACK_REG_HIST1_32_OFFSET                          (0xB80)
#define DSP2_BLBACK_HIST1_32_R                                   DSP2_BLBACK_HIST1_32_R
#define DSP2_BLBACK_HIST1_32_R_POS                               (0U)
#define DSP2_BLBACK_HIST1_32_R_LEN                               (24U)
#define DSP2_BLBACK_HIST1_32_R_MSK                               (((1U<<DSP2_BLBACK_HIST1_32_R_LEN)-1)<<DSP2_BLBACK_HIST1_32_R_POS)
#define DSP2_BLBACK_HIST1_32_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST1_32_R_LEN)-1)<<DSP2_BLBACK_HIST1_32_R_POS))

/* 0xB84 : REG_HIST1_33 */
#define DSP2_BLBACK_REG_HIST1_33_OFFSET                          (0xB84)
#define DSP2_BLBACK_HIST1_33_R                                   DSP2_BLBACK_HIST1_33_R
#define DSP2_BLBACK_HIST1_33_R_POS                               (0U)
#define DSP2_BLBACK_HIST1_33_R_LEN                               (24U)
#define DSP2_BLBACK_HIST1_33_R_MSK                               (((1U<<DSP2_BLBACK_HIST1_33_R_LEN)-1)<<DSP2_BLBACK_HIST1_33_R_POS)
#define DSP2_BLBACK_HIST1_33_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST1_33_R_LEN)-1)<<DSP2_BLBACK_HIST1_33_R_POS))

/* 0xB88 : REG_HIST1_34 */
#define DSP2_BLBACK_REG_HIST1_34_OFFSET                          (0xB88)
#define DSP2_BLBACK_HIST1_34_R                                   DSP2_BLBACK_HIST1_34_R
#define DSP2_BLBACK_HIST1_34_R_POS                               (0U)
#define DSP2_BLBACK_HIST1_34_R_LEN                               (24U)
#define DSP2_BLBACK_HIST1_34_R_MSK                               (((1U<<DSP2_BLBACK_HIST1_34_R_LEN)-1)<<DSP2_BLBACK_HIST1_34_R_POS)
#define DSP2_BLBACK_HIST1_34_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST1_34_R_LEN)-1)<<DSP2_BLBACK_HIST1_34_R_POS))

/* 0xB8C : REG_HIST1_35 */
#define DSP2_BLBACK_REG_HIST1_35_OFFSET                          (0xB8C)
#define DSP2_BLBACK_HIST1_35_R                                   DSP2_BLBACK_HIST1_35_R
#define DSP2_BLBACK_HIST1_35_R_POS                               (0U)
#define DSP2_BLBACK_HIST1_35_R_LEN                               (24U)
#define DSP2_BLBACK_HIST1_35_R_MSK                               (((1U<<DSP2_BLBACK_HIST1_35_R_LEN)-1)<<DSP2_BLBACK_HIST1_35_R_POS)
#define DSP2_BLBACK_HIST1_35_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST1_35_R_LEN)-1)<<DSP2_BLBACK_HIST1_35_R_POS))

/* 0xB90 : REG_HIST1_36 */
#define DSP2_BLBACK_REG_HIST1_36_OFFSET                          (0xB90)
#define DSP2_BLBACK_HIST1_36_R                                   DSP2_BLBACK_HIST1_36_R
#define DSP2_BLBACK_HIST1_36_R_POS                               (0U)
#define DSP2_BLBACK_HIST1_36_R_LEN                               (24U)
#define DSP2_BLBACK_HIST1_36_R_MSK                               (((1U<<DSP2_BLBACK_HIST1_36_R_LEN)-1)<<DSP2_BLBACK_HIST1_36_R_POS)
#define DSP2_BLBACK_HIST1_36_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST1_36_R_LEN)-1)<<DSP2_BLBACK_HIST1_36_R_POS))

/* 0xB94 : REG_HIST1_37 */
#define DSP2_BLBACK_REG_HIST1_37_OFFSET                          (0xB94)
#define DSP2_BLBACK_HIST1_37_R                                   DSP2_BLBACK_HIST1_37_R
#define DSP2_BLBACK_HIST1_37_R_POS                               (0U)
#define DSP2_BLBACK_HIST1_37_R_LEN                               (24U)
#define DSP2_BLBACK_HIST1_37_R_MSK                               (((1U<<DSP2_BLBACK_HIST1_37_R_LEN)-1)<<DSP2_BLBACK_HIST1_37_R_POS)
#define DSP2_BLBACK_HIST1_37_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST1_37_R_LEN)-1)<<DSP2_BLBACK_HIST1_37_R_POS))

/* 0xB98 : REG_HIST1_38 */
#define DSP2_BLBACK_REG_HIST1_38_OFFSET                          (0xB98)
#define DSP2_BLBACK_HIST1_38_R                                   DSP2_BLBACK_HIST1_38_R
#define DSP2_BLBACK_HIST1_38_R_POS                               (0U)
#define DSP2_BLBACK_HIST1_38_R_LEN                               (24U)
#define DSP2_BLBACK_HIST1_38_R_MSK                               (((1U<<DSP2_BLBACK_HIST1_38_R_LEN)-1)<<DSP2_BLBACK_HIST1_38_R_POS)
#define DSP2_BLBACK_HIST1_38_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST1_38_R_LEN)-1)<<DSP2_BLBACK_HIST1_38_R_POS))

/* 0xB9C : REG_HIST1_39 */
#define DSP2_BLBACK_REG_HIST1_39_OFFSET                          (0xB9C)
#define DSP2_BLBACK_HIST1_39_R                                   DSP2_BLBACK_HIST1_39_R
#define DSP2_BLBACK_HIST1_39_R_POS                               (0U)
#define DSP2_BLBACK_HIST1_39_R_LEN                               (24U)
#define DSP2_BLBACK_HIST1_39_R_MSK                               (((1U<<DSP2_BLBACK_HIST1_39_R_LEN)-1)<<DSP2_BLBACK_HIST1_39_R_POS)
#define DSP2_BLBACK_HIST1_39_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST1_39_R_LEN)-1)<<DSP2_BLBACK_HIST1_39_R_POS))

/* 0xBA0 : REG_HIST1_40 */
#define DSP2_BLBACK_REG_HIST1_40_OFFSET                          (0xBA0)
#define DSP2_BLBACK_HIST1_40_R                                   DSP2_BLBACK_HIST1_40_R
#define DSP2_BLBACK_HIST1_40_R_POS                               (0U)
#define DSP2_BLBACK_HIST1_40_R_LEN                               (24U)
#define DSP2_BLBACK_HIST1_40_R_MSK                               (((1U<<DSP2_BLBACK_HIST1_40_R_LEN)-1)<<DSP2_BLBACK_HIST1_40_R_POS)
#define DSP2_BLBACK_HIST1_40_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST1_40_R_LEN)-1)<<DSP2_BLBACK_HIST1_40_R_POS))

/* 0xBA4 : REG_HIST1_41 */
#define DSP2_BLBACK_REG_HIST1_41_OFFSET                          (0xBA4)
#define DSP2_BLBACK_HIST1_41_R                                   DSP2_BLBACK_HIST1_41_R
#define DSP2_BLBACK_HIST1_41_R_POS                               (0U)
#define DSP2_BLBACK_HIST1_41_R_LEN                               (24U)
#define DSP2_BLBACK_HIST1_41_R_MSK                               (((1U<<DSP2_BLBACK_HIST1_41_R_LEN)-1)<<DSP2_BLBACK_HIST1_41_R_POS)
#define DSP2_BLBACK_HIST1_41_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST1_41_R_LEN)-1)<<DSP2_BLBACK_HIST1_41_R_POS))

/* 0xBA8 : REG_HIST1_42 */
#define DSP2_BLBACK_REG_HIST1_42_OFFSET                          (0xBA8)
#define DSP2_BLBACK_HIST1_42_R                                   DSP2_BLBACK_HIST1_42_R
#define DSP2_BLBACK_HIST1_42_R_POS                               (0U)
#define DSP2_BLBACK_HIST1_42_R_LEN                               (24U)
#define DSP2_BLBACK_HIST1_42_R_MSK                               (((1U<<DSP2_BLBACK_HIST1_42_R_LEN)-1)<<DSP2_BLBACK_HIST1_42_R_POS)
#define DSP2_BLBACK_HIST1_42_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST1_42_R_LEN)-1)<<DSP2_BLBACK_HIST1_42_R_POS))

/* 0xBAC : REG_HIST1_43 */
#define DSP2_BLBACK_REG_HIST1_43_OFFSET                          (0xBAC)
#define DSP2_BLBACK_HIST1_43_R                                   DSP2_BLBACK_HIST1_43_R
#define DSP2_BLBACK_HIST1_43_R_POS                               (0U)
#define DSP2_BLBACK_HIST1_43_R_LEN                               (24U)
#define DSP2_BLBACK_HIST1_43_R_MSK                               (((1U<<DSP2_BLBACK_HIST1_43_R_LEN)-1)<<DSP2_BLBACK_HIST1_43_R_POS)
#define DSP2_BLBACK_HIST1_43_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST1_43_R_LEN)-1)<<DSP2_BLBACK_HIST1_43_R_POS))

/* 0xBB0 : REG_HIST1_44 */
#define DSP2_BLBACK_REG_HIST1_44_OFFSET                          (0xBB0)
#define DSP2_BLBACK_HIST1_44_R                                   DSP2_BLBACK_HIST1_44_R
#define DSP2_BLBACK_HIST1_44_R_POS                               (0U)
#define DSP2_BLBACK_HIST1_44_R_LEN                               (24U)
#define DSP2_BLBACK_HIST1_44_R_MSK                               (((1U<<DSP2_BLBACK_HIST1_44_R_LEN)-1)<<DSP2_BLBACK_HIST1_44_R_POS)
#define DSP2_BLBACK_HIST1_44_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST1_44_R_LEN)-1)<<DSP2_BLBACK_HIST1_44_R_POS))

/* 0xBB4 : REG_HIST1_45 */
#define DSP2_BLBACK_REG_HIST1_45_OFFSET                          (0xBB4)
#define DSP2_BLBACK_HIST1_45_R                                   DSP2_BLBACK_HIST1_45_R
#define DSP2_BLBACK_HIST1_45_R_POS                               (0U)
#define DSP2_BLBACK_HIST1_45_R_LEN                               (24U)
#define DSP2_BLBACK_HIST1_45_R_MSK                               (((1U<<DSP2_BLBACK_HIST1_45_R_LEN)-1)<<DSP2_BLBACK_HIST1_45_R_POS)
#define DSP2_BLBACK_HIST1_45_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST1_45_R_LEN)-1)<<DSP2_BLBACK_HIST1_45_R_POS))

/* 0xBB8 : REG_HIST1_46 */
#define DSP2_BLBACK_REG_HIST1_46_OFFSET                          (0xBB8)
#define DSP2_BLBACK_HIST1_46_R                                   DSP2_BLBACK_HIST1_46_R
#define DSP2_BLBACK_HIST1_46_R_POS                               (0U)
#define DSP2_BLBACK_HIST1_46_R_LEN                               (24U)
#define DSP2_BLBACK_HIST1_46_R_MSK                               (((1U<<DSP2_BLBACK_HIST1_46_R_LEN)-1)<<DSP2_BLBACK_HIST1_46_R_POS)
#define DSP2_BLBACK_HIST1_46_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST1_46_R_LEN)-1)<<DSP2_BLBACK_HIST1_46_R_POS))

/* 0xBBC : REG_HIST1_47 */
#define DSP2_BLBACK_REG_HIST1_47_OFFSET                          (0xBBC)
#define DSP2_BLBACK_HIST1_47_R                                   DSP2_BLBACK_HIST1_47_R
#define DSP2_BLBACK_HIST1_47_R_POS                               (0U)
#define DSP2_BLBACK_HIST1_47_R_LEN                               (24U)
#define DSP2_BLBACK_HIST1_47_R_MSK                               (((1U<<DSP2_BLBACK_HIST1_47_R_LEN)-1)<<DSP2_BLBACK_HIST1_47_R_POS)
#define DSP2_BLBACK_HIST1_47_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST1_47_R_LEN)-1)<<DSP2_BLBACK_HIST1_47_R_POS))

/* 0xBC0 : REG_HIST1_48 */
#define DSP2_BLBACK_REG_HIST1_48_OFFSET                          (0xBC0)
#define DSP2_BLBACK_HIST1_48_R                                   DSP2_BLBACK_HIST1_48_R
#define DSP2_BLBACK_HIST1_48_R_POS                               (0U)
#define DSP2_BLBACK_HIST1_48_R_LEN                               (24U)
#define DSP2_BLBACK_HIST1_48_R_MSK                               (((1U<<DSP2_BLBACK_HIST1_48_R_LEN)-1)<<DSP2_BLBACK_HIST1_48_R_POS)
#define DSP2_BLBACK_HIST1_48_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST1_48_R_LEN)-1)<<DSP2_BLBACK_HIST1_48_R_POS))

/* 0xBC4 : REG_HIST1_49 */
#define DSP2_BLBACK_REG_HIST1_49_OFFSET                          (0xBC4)
#define DSP2_BLBACK_HIST1_49_R                                   DSP2_BLBACK_HIST1_49_R
#define DSP2_BLBACK_HIST1_49_R_POS                               (0U)
#define DSP2_BLBACK_HIST1_49_R_LEN                               (24U)
#define DSP2_BLBACK_HIST1_49_R_MSK                               (((1U<<DSP2_BLBACK_HIST1_49_R_LEN)-1)<<DSP2_BLBACK_HIST1_49_R_POS)
#define DSP2_BLBACK_HIST1_49_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST1_49_R_LEN)-1)<<DSP2_BLBACK_HIST1_49_R_POS))

/* 0xBC8 : REG_HIST1_50 */
#define DSP2_BLBACK_REG_HIST1_50_OFFSET                          (0xBC8)
#define DSP2_BLBACK_HIST1_50_R                                   DSP2_BLBACK_HIST1_50_R
#define DSP2_BLBACK_HIST1_50_R_POS                               (0U)
#define DSP2_BLBACK_HIST1_50_R_LEN                               (24U)
#define DSP2_BLBACK_HIST1_50_R_MSK                               (((1U<<DSP2_BLBACK_HIST1_50_R_LEN)-1)<<DSP2_BLBACK_HIST1_50_R_POS)
#define DSP2_BLBACK_HIST1_50_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST1_50_R_LEN)-1)<<DSP2_BLBACK_HIST1_50_R_POS))

/* 0xBCC : REG_HIST1_51 */
#define DSP2_BLBACK_REG_HIST1_51_OFFSET                          (0xBCC)
#define DSP2_BLBACK_HIST1_51_R                                   DSP2_BLBACK_HIST1_51_R
#define DSP2_BLBACK_HIST1_51_R_POS                               (0U)
#define DSP2_BLBACK_HIST1_51_R_LEN                               (24U)
#define DSP2_BLBACK_HIST1_51_R_MSK                               (((1U<<DSP2_BLBACK_HIST1_51_R_LEN)-1)<<DSP2_BLBACK_HIST1_51_R_POS)
#define DSP2_BLBACK_HIST1_51_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST1_51_R_LEN)-1)<<DSP2_BLBACK_HIST1_51_R_POS))

/* 0xBD0 : REG_HIST1_52 */
#define DSP2_BLBACK_REG_HIST1_52_OFFSET                          (0xBD0)
#define DSP2_BLBACK_HIST1_52_R                                   DSP2_BLBACK_HIST1_52_R
#define DSP2_BLBACK_HIST1_52_R_POS                               (0U)
#define DSP2_BLBACK_HIST1_52_R_LEN                               (24U)
#define DSP2_BLBACK_HIST1_52_R_MSK                               (((1U<<DSP2_BLBACK_HIST1_52_R_LEN)-1)<<DSP2_BLBACK_HIST1_52_R_POS)
#define DSP2_BLBACK_HIST1_52_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST1_52_R_LEN)-1)<<DSP2_BLBACK_HIST1_52_R_POS))

/* 0xBD4 : REG_HIST1_53 */
#define DSP2_BLBACK_REG_HIST1_53_OFFSET                          (0xBD4)
#define DSP2_BLBACK_HIST1_53_R                                   DSP2_BLBACK_HIST1_53_R
#define DSP2_BLBACK_HIST1_53_R_POS                               (0U)
#define DSP2_BLBACK_HIST1_53_R_LEN                               (24U)
#define DSP2_BLBACK_HIST1_53_R_MSK                               (((1U<<DSP2_BLBACK_HIST1_53_R_LEN)-1)<<DSP2_BLBACK_HIST1_53_R_POS)
#define DSP2_BLBACK_HIST1_53_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST1_53_R_LEN)-1)<<DSP2_BLBACK_HIST1_53_R_POS))

/* 0xBD8 : REG_HIST1_54 */
#define DSP2_BLBACK_REG_HIST1_54_OFFSET                          (0xBD8)
#define DSP2_BLBACK_HIST1_54_R                                   DSP2_BLBACK_HIST1_54_R
#define DSP2_BLBACK_HIST1_54_R_POS                               (0U)
#define DSP2_BLBACK_HIST1_54_R_LEN                               (24U)
#define DSP2_BLBACK_HIST1_54_R_MSK                               (((1U<<DSP2_BLBACK_HIST1_54_R_LEN)-1)<<DSP2_BLBACK_HIST1_54_R_POS)
#define DSP2_BLBACK_HIST1_54_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST1_54_R_LEN)-1)<<DSP2_BLBACK_HIST1_54_R_POS))

/* 0xBDC : REG_HIST1_55 */
#define DSP2_BLBACK_REG_HIST1_55_OFFSET                          (0xBDC)
#define DSP2_BLBACK_HIST1_55_R                                   DSP2_BLBACK_HIST1_55_R
#define DSP2_BLBACK_HIST1_55_R_POS                               (0U)
#define DSP2_BLBACK_HIST1_55_R_LEN                               (24U)
#define DSP2_BLBACK_HIST1_55_R_MSK                               (((1U<<DSP2_BLBACK_HIST1_55_R_LEN)-1)<<DSP2_BLBACK_HIST1_55_R_POS)
#define DSP2_BLBACK_HIST1_55_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST1_55_R_LEN)-1)<<DSP2_BLBACK_HIST1_55_R_POS))

/* 0xBE0 : REG_HIST1_56 */
#define DSP2_BLBACK_REG_HIST1_56_OFFSET                          (0xBE0)
#define DSP2_BLBACK_HIST1_56_R                                   DSP2_BLBACK_HIST1_56_R
#define DSP2_BLBACK_HIST1_56_R_POS                               (0U)
#define DSP2_BLBACK_HIST1_56_R_LEN                               (24U)
#define DSP2_BLBACK_HIST1_56_R_MSK                               (((1U<<DSP2_BLBACK_HIST1_56_R_LEN)-1)<<DSP2_BLBACK_HIST1_56_R_POS)
#define DSP2_BLBACK_HIST1_56_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST1_56_R_LEN)-1)<<DSP2_BLBACK_HIST1_56_R_POS))

/* 0xBE4 : REG_HIST1_57 */
#define DSP2_BLBACK_REG_HIST1_57_OFFSET                          (0xBE4)
#define DSP2_BLBACK_HIST1_57_R                                   DSP2_BLBACK_HIST1_57_R
#define DSP2_BLBACK_HIST1_57_R_POS                               (0U)
#define DSP2_BLBACK_HIST1_57_R_LEN                               (24U)
#define DSP2_BLBACK_HIST1_57_R_MSK                               (((1U<<DSP2_BLBACK_HIST1_57_R_LEN)-1)<<DSP2_BLBACK_HIST1_57_R_POS)
#define DSP2_BLBACK_HIST1_57_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST1_57_R_LEN)-1)<<DSP2_BLBACK_HIST1_57_R_POS))

/* 0xBE8 : REG_HIST1_58 */
#define DSP2_BLBACK_REG_HIST1_58_OFFSET                          (0xBE8)
#define DSP2_BLBACK_HIST1_58_R                                   DSP2_BLBACK_HIST1_58_R
#define DSP2_BLBACK_HIST1_58_R_POS                               (0U)
#define DSP2_BLBACK_HIST1_58_R_LEN                               (24U)
#define DSP2_BLBACK_HIST1_58_R_MSK                               (((1U<<DSP2_BLBACK_HIST1_58_R_LEN)-1)<<DSP2_BLBACK_HIST1_58_R_POS)
#define DSP2_BLBACK_HIST1_58_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST1_58_R_LEN)-1)<<DSP2_BLBACK_HIST1_58_R_POS))

/* 0xBEC : REG_HIST1_59 */
#define DSP2_BLBACK_REG_HIST1_59_OFFSET                          (0xBEC)
#define DSP2_BLBACK_HIST1_59_R                                   DSP2_BLBACK_HIST1_59_R
#define DSP2_BLBACK_HIST1_59_R_POS                               (0U)
#define DSP2_BLBACK_HIST1_59_R_LEN                               (24U)
#define DSP2_BLBACK_HIST1_59_R_MSK                               (((1U<<DSP2_BLBACK_HIST1_59_R_LEN)-1)<<DSP2_BLBACK_HIST1_59_R_POS)
#define DSP2_BLBACK_HIST1_59_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST1_59_R_LEN)-1)<<DSP2_BLBACK_HIST1_59_R_POS))

/* 0xBF0 : REG_HIST1_60 */
#define DSP2_BLBACK_REG_HIST1_60_OFFSET                          (0xBF0)
#define DSP2_BLBACK_HIST1_60_R                                   DSP2_BLBACK_HIST1_60_R
#define DSP2_BLBACK_HIST1_60_R_POS                               (0U)
#define DSP2_BLBACK_HIST1_60_R_LEN                               (24U)
#define DSP2_BLBACK_HIST1_60_R_MSK                               (((1U<<DSP2_BLBACK_HIST1_60_R_LEN)-1)<<DSP2_BLBACK_HIST1_60_R_POS)
#define DSP2_BLBACK_HIST1_60_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST1_60_R_LEN)-1)<<DSP2_BLBACK_HIST1_60_R_POS))

/* 0xBF4 : REG_HIST1_61 */
#define DSP2_BLBACK_REG_HIST1_61_OFFSET                          (0xBF4)
#define DSP2_BLBACK_HIST1_61_R                                   DSP2_BLBACK_HIST1_61_R
#define DSP2_BLBACK_HIST1_61_R_POS                               (0U)
#define DSP2_BLBACK_HIST1_61_R_LEN                               (24U)
#define DSP2_BLBACK_HIST1_61_R_MSK                               (((1U<<DSP2_BLBACK_HIST1_61_R_LEN)-1)<<DSP2_BLBACK_HIST1_61_R_POS)
#define DSP2_BLBACK_HIST1_61_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST1_61_R_LEN)-1)<<DSP2_BLBACK_HIST1_61_R_POS))

/* 0xBF8 : REG_HIST1_62 */
#define DSP2_BLBACK_REG_HIST1_62_OFFSET                          (0xBF8)
#define DSP2_BLBACK_HIST1_62_R                                   DSP2_BLBACK_HIST1_62_R
#define DSP2_BLBACK_HIST1_62_R_POS                               (0U)
#define DSP2_BLBACK_HIST1_62_R_LEN                               (24U)
#define DSP2_BLBACK_HIST1_62_R_MSK                               (((1U<<DSP2_BLBACK_HIST1_62_R_LEN)-1)<<DSP2_BLBACK_HIST1_62_R_POS)
#define DSP2_BLBACK_HIST1_62_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST1_62_R_LEN)-1)<<DSP2_BLBACK_HIST1_62_R_POS))

/* 0xBFC : REG_HIST1_63 */
#define DSP2_BLBACK_REG_HIST1_63_OFFSET                          (0xBFC)
#define DSP2_BLBACK_HIST1_63_R                                   DSP2_BLBACK_HIST1_63_R
#define DSP2_BLBACK_HIST1_63_R_POS                               (0U)
#define DSP2_BLBACK_HIST1_63_R_LEN                               (24U)
#define DSP2_BLBACK_HIST1_63_R_MSK                               (((1U<<DSP2_BLBACK_HIST1_63_R_LEN)-1)<<DSP2_BLBACK_HIST1_63_R_POS)
#define DSP2_BLBACK_HIST1_63_R_UMSK                              (~(((1U<<DSP2_BLBACK_HIST1_63_R_LEN)-1)<<DSP2_BLBACK_HIST1_63_R_POS))

/* 0xC00 : WDR_CURVE_1 */
#define DSP2_BLBACK_WDR_CURVE_1_OFFSET                           (0xC00)
#define DSP2_BLBACK_CURVE_0_PRE                                  DSP2_BLBACK_CURVE_0_PRE
#define DSP2_BLBACK_CURVE_0_PRE_POS                              (0U)
#define DSP2_BLBACK_CURVE_0_PRE_LEN                              (10U)
#define DSP2_BLBACK_CURVE_0_PRE_MSK                              (((1U<<DSP2_BLBACK_CURVE_0_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_0_PRE_POS)
#define DSP2_BLBACK_CURVE_0_PRE_UMSK                             (~(((1U<<DSP2_BLBACK_CURVE_0_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_0_PRE_POS))
#define DSP2_BLBACK_CURVE_1_PRE                                  DSP2_BLBACK_CURVE_1_PRE
#define DSP2_BLBACK_CURVE_1_PRE_POS                              (16U)
#define DSP2_BLBACK_CURVE_1_PRE_LEN                              (10U)
#define DSP2_BLBACK_CURVE_1_PRE_MSK                              (((1U<<DSP2_BLBACK_CURVE_1_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_1_PRE_POS)
#define DSP2_BLBACK_CURVE_1_PRE_UMSK                             (~(((1U<<DSP2_BLBACK_CURVE_1_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_1_PRE_POS))

/* 0xC04 : WDR_CURVE_2 */
#define DSP2_BLBACK_WDR_CURVE_2_OFFSET                           (0xC04)
#define DSP2_BLBACK_CURVE_2_PRE                                  DSP2_BLBACK_CURVE_2_PRE
#define DSP2_BLBACK_CURVE_2_PRE_POS                              (0U)
#define DSP2_BLBACK_CURVE_2_PRE_LEN                              (10U)
#define DSP2_BLBACK_CURVE_2_PRE_MSK                              (((1U<<DSP2_BLBACK_CURVE_2_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_2_PRE_POS)
#define DSP2_BLBACK_CURVE_2_PRE_UMSK                             (~(((1U<<DSP2_BLBACK_CURVE_2_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_2_PRE_POS))
#define DSP2_BLBACK_CURVE_3_PRE                                  DSP2_BLBACK_CURVE_3_PRE
#define DSP2_BLBACK_CURVE_3_PRE_POS                              (16U)
#define DSP2_BLBACK_CURVE_3_PRE_LEN                              (10U)
#define DSP2_BLBACK_CURVE_3_PRE_MSK                              (((1U<<DSP2_BLBACK_CURVE_3_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_3_PRE_POS)
#define DSP2_BLBACK_CURVE_3_PRE_UMSK                             (~(((1U<<DSP2_BLBACK_CURVE_3_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_3_PRE_POS))

/* 0xC08 : WDR_CURVE_3 */
#define DSP2_BLBACK_WDR_CURVE_3_OFFSET                           (0xC08)
#define DSP2_BLBACK_CURVE_4_PRE                                  DSP2_BLBACK_CURVE_4_PRE
#define DSP2_BLBACK_CURVE_4_PRE_POS                              (0U)
#define DSP2_BLBACK_CURVE_4_PRE_LEN                              (10U)
#define DSP2_BLBACK_CURVE_4_PRE_MSK                              (((1U<<DSP2_BLBACK_CURVE_4_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_4_PRE_POS)
#define DSP2_BLBACK_CURVE_4_PRE_UMSK                             (~(((1U<<DSP2_BLBACK_CURVE_4_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_4_PRE_POS))
#define DSP2_BLBACK_CURVE_5_PRE                                  DSP2_BLBACK_CURVE_5_PRE
#define DSP2_BLBACK_CURVE_5_PRE_POS                              (16U)
#define DSP2_BLBACK_CURVE_5_PRE_LEN                              (10U)
#define DSP2_BLBACK_CURVE_5_PRE_MSK                              (((1U<<DSP2_BLBACK_CURVE_5_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_5_PRE_POS)
#define DSP2_BLBACK_CURVE_5_PRE_UMSK                             (~(((1U<<DSP2_BLBACK_CURVE_5_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_5_PRE_POS))

/* 0xC0C : WDR_CURVE_4 */
#define DSP2_BLBACK_WDR_CURVE_4_OFFSET                           (0xC0C)
#define DSP2_BLBACK_CURVE_6_PRE                                  DSP2_BLBACK_CURVE_6_PRE
#define DSP2_BLBACK_CURVE_6_PRE_POS                              (0U)
#define DSP2_BLBACK_CURVE_6_PRE_LEN                              (10U)
#define DSP2_BLBACK_CURVE_6_PRE_MSK                              (((1U<<DSP2_BLBACK_CURVE_6_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_6_PRE_POS)
#define DSP2_BLBACK_CURVE_6_PRE_UMSK                             (~(((1U<<DSP2_BLBACK_CURVE_6_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_6_PRE_POS))
#define DSP2_BLBACK_CURVE_7_PRE                                  DSP2_BLBACK_CURVE_7_PRE
#define DSP2_BLBACK_CURVE_7_PRE_POS                              (16U)
#define DSP2_BLBACK_CURVE_7_PRE_LEN                              (10U)
#define DSP2_BLBACK_CURVE_7_PRE_MSK                              (((1U<<DSP2_BLBACK_CURVE_7_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_7_PRE_POS)
#define DSP2_BLBACK_CURVE_7_PRE_UMSK                             (~(((1U<<DSP2_BLBACK_CURVE_7_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_7_PRE_POS))

/* 0xC10 : WDR_CURVE_5 */
#define DSP2_BLBACK_WDR_CURVE_5_OFFSET                           (0xC10)
#define DSP2_BLBACK_CURVE_8_PRE                                  DSP2_BLBACK_CURVE_8_PRE
#define DSP2_BLBACK_CURVE_8_PRE_POS                              (0U)
#define DSP2_BLBACK_CURVE_8_PRE_LEN                              (10U)
#define DSP2_BLBACK_CURVE_8_PRE_MSK                              (((1U<<DSP2_BLBACK_CURVE_8_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_8_PRE_POS)
#define DSP2_BLBACK_CURVE_8_PRE_UMSK                             (~(((1U<<DSP2_BLBACK_CURVE_8_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_8_PRE_POS))
#define DSP2_BLBACK_CURVE_9_PRE                                  DSP2_BLBACK_CURVE_9_PRE
#define DSP2_BLBACK_CURVE_9_PRE_POS                              (16U)
#define DSP2_BLBACK_CURVE_9_PRE_LEN                              (10U)
#define DSP2_BLBACK_CURVE_9_PRE_MSK                              (((1U<<DSP2_BLBACK_CURVE_9_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_9_PRE_POS)
#define DSP2_BLBACK_CURVE_9_PRE_UMSK                             (~(((1U<<DSP2_BLBACK_CURVE_9_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_9_PRE_POS))

/* 0xC14 : WDR_CURVE_6 */
#define DSP2_BLBACK_WDR_CURVE_6_OFFSET                           (0xC14)
#define DSP2_BLBACK_CURVE_10_PRE                                 DSP2_BLBACK_CURVE_10_PRE
#define DSP2_BLBACK_CURVE_10_PRE_POS                             (0U)
#define DSP2_BLBACK_CURVE_10_PRE_LEN                             (10U)
#define DSP2_BLBACK_CURVE_10_PRE_MSK                             (((1U<<DSP2_BLBACK_CURVE_10_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_10_PRE_POS)
#define DSP2_BLBACK_CURVE_10_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CURVE_10_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_10_PRE_POS))
#define DSP2_BLBACK_CURVE_11_PRE                                 DSP2_BLBACK_CURVE_11_PRE
#define DSP2_BLBACK_CURVE_11_PRE_POS                             (16U)
#define DSP2_BLBACK_CURVE_11_PRE_LEN                             (10U)
#define DSP2_BLBACK_CURVE_11_PRE_MSK                             (((1U<<DSP2_BLBACK_CURVE_11_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_11_PRE_POS)
#define DSP2_BLBACK_CURVE_11_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CURVE_11_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_11_PRE_POS))

/* 0xC18 : WDR_CURVE_7 */
#define DSP2_BLBACK_WDR_CURVE_7_OFFSET                           (0xC18)
#define DSP2_BLBACK_CURVE_12_PRE                                 DSP2_BLBACK_CURVE_12_PRE
#define DSP2_BLBACK_CURVE_12_PRE_POS                             (0U)
#define DSP2_BLBACK_CURVE_12_PRE_LEN                             (10U)
#define DSP2_BLBACK_CURVE_12_PRE_MSK                             (((1U<<DSP2_BLBACK_CURVE_12_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_12_PRE_POS)
#define DSP2_BLBACK_CURVE_12_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CURVE_12_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_12_PRE_POS))
#define DSP2_BLBACK_CURVE_13_PRE                                 DSP2_BLBACK_CURVE_13_PRE
#define DSP2_BLBACK_CURVE_13_PRE_POS                             (16U)
#define DSP2_BLBACK_CURVE_13_PRE_LEN                             (10U)
#define DSP2_BLBACK_CURVE_13_PRE_MSK                             (((1U<<DSP2_BLBACK_CURVE_13_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_13_PRE_POS)
#define DSP2_BLBACK_CURVE_13_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CURVE_13_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_13_PRE_POS))

/* 0xC1C : WDR_CURVE_8 */
#define DSP2_BLBACK_WDR_CURVE_8_OFFSET                           (0xC1C)
#define DSP2_BLBACK_CURVE_14_PRE                                 DSP2_BLBACK_CURVE_14_PRE
#define DSP2_BLBACK_CURVE_14_PRE_POS                             (0U)
#define DSP2_BLBACK_CURVE_14_PRE_LEN                             (10U)
#define DSP2_BLBACK_CURVE_14_PRE_MSK                             (((1U<<DSP2_BLBACK_CURVE_14_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_14_PRE_POS)
#define DSP2_BLBACK_CURVE_14_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CURVE_14_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_14_PRE_POS))
#define DSP2_BLBACK_CURVE_15_PRE                                 DSP2_BLBACK_CURVE_15_PRE
#define DSP2_BLBACK_CURVE_15_PRE_POS                             (16U)
#define DSP2_BLBACK_CURVE_15_PRE_LEN                             (10U)
#define DSP2_BLBACK_CURVE_15_PRE_MSK                             (((1U<<DSP2_BLBACK_CURVE_15_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_15_PRE_POS)
#define DSP2_BLBACK_CURVE_15_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CURVE_15_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_15_PRE_POS))

/* 0xC20 : WDR_CURVE_9 */
#define DSP2_BLBACK_WDR_CURVE_9_OFFSET                           (0xC20)
#define DSP2_BLBACK_CURVE_16_PRE                                 DSP2_BLBACK_CURVE_16_PRE
#define DSP2_BLBACK_CURVE_16_PRE_POS                             (0U)
#define DSP2_BLBACK_CURVE_16_PRE_LEN                             (10U)
#define DSP2_BLBACK_CURVE_16_PRE_MSK                             (((1U<<DSP2_BLBACK_CURVE_16_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_16_PRE_POS)
#define DSP2_BLBACK_CURVE_16_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CURVE_16_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_16_PRE_POS))
#define DSP2_BLBACK_CURVE_17_PRE                                 DSP2_BLBACK_CURVE_17_PRE
#define DSP2_BLBACK_CURVE_17_PRE_POS                             (16U)
#define DSP2_BLBACK_CURVE_17_PRE_LEN                             (10U)
#define DSP2_BLBACK_CURVE_17_PRE_MSK                             (((1U<<DSP2_BLBACK_CURVE_17_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_17_PRE_POS)
#define DSP2_BLBACK_CURVE_17_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CURVE_17_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_17_PRE_POS))

/* 0xC24 : WDR_CURVE_10 */
#define DSP2_BLBACK_WDR_CURVE_10_OFFSET                          (0xC24)
#define DSP2_BLBACK_CURVE_18_PRE                                 DSP2_BLBACK_CURVE_18_PRE
#define DSP2_BLBACK_CURVE_18_PRE_POS                             (0U)
#define DSP2_BLBACK_CURVE_18_PRE_LEN                             (10U)
#define DSP2_BLBACK_CURVE_18_PRE_MSK                             (((1U<<DSP2_BLBACK_CURVE_18_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_18_PRE_POS)
#define DSP2_BLBACK_CURVE_18_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CURVE_18_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_18_PRE_POS))
#define DSP2_BLBACK_CURVE_19_PRE                                 DSP2_BLBACK_CURVE_19_PRE
#define DSP2_BLBACK_CURVE_19_PRE_POS                             (16U)
#define DSP2_BLBACK_CURVE_19_PRE_LEN                             (10U)
#define DSP2_BLBACK_CURVE_19_PRE_MSK                             (((1U<<DSP2_BLBACK_CURVE_19_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_19_PRE_POS)
#define DSP2_BLBACK_CURVE_19_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CURVE_19_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_19_PRE_POS))

/* 0xC28 : WDR_CURVE_11 */
#define DSP2_BLBACK_WDR_CURVE_11_OFFSET                          (0xC28)
#define DSP2_BLBACK_CURVE_20_PRE                                 DSP2_BLBACK_CURVE_20_PRE
#define DSP2_BLBACK_CURVE_20_PRE_POS                             (0U)
#define DSP2_BLBACK_CURVE_20_PRE_LEN                             (10U)
#define DSP2_BLBACK_CURVE_20_PRE_MSK                             (((1U<<DSP2_BLBACK_CURVE_20_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_20_PRE_POS)
#define DSP2_BLBACK_CURVE_20_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CURVE_20_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_20_PRE_POS))
#define DSP2_BLBACK_CURVE_21_PRE                                 DSP2_BLBACK_CURVE_21_PRE
#define DSP2_BLBACK_CURVE_21_PRE_POS                             (16U)
#define DSP2_BLBACK_CURVE_21_PRE_LEN                             (10U)
#define DSP2_BLBACK_CURVE_21_PRE_MSK                             (((1U<<DSP2_BLBACK_CURVE_21_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_21_PRE_POS)
#define DSP2_BLBACK_CURVE_21_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CURVE_21_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_21_PRE_POS))

/* 0xC2C : WDR_CURVE_12 */
#define DSP2_BLBACK_WDR_CURVE_12_OFFSET                          (0xC2C)
#define DSP2_BLBACK_CURVE_22_PRE                                 DSP2_BLBACK_CURVE_22_PRE
#define DSP2_BLBACK_CURVE_22_PRE_POS                             (0U)
#define DSP2_BLBACK_CURVE_22_PRE_LEN                             (10U)
#define DSP2_BLBACK_CURVE_22_PRE_MSK                             (((1U<<DSP2_BLBACK_CURVE_22_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_22_PRE_POS)
#define DSP2_BLBACK_CURVE_22_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CURVE_22_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_22_PRE_POS))
#define DSP2_BLBACK_CURVE_23_PRE                                 DSP2_BLBACK_CURVE_23_PRE
#define DSP2_BLBACK_CURVE_23_PRE_POS                             (16U)
#define DSP2_BLBACK_CURVE_23_PRE_LEN                             (10U)
#define DSP2_BLBACK_CURVE_23_PRE_MSK                             (((1U<<DSP2_BLBACK_CURVE_23_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_23_PRE_POS)
#define DSP2_BLBACK_CURVE_23_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CURVE_23_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_23_PRE_POS))

/* 0xC30 : WDR_CURVE_13 */
#define DSP2_BLBACK_WDR_CURVE_13_OFFSET                          (0xC30)
#define DSP2_BLBACK_CURVE_24_PRE                                 DSP2_BLBACK_CURVE_24_PRE
#define DSP2_BLBACK_CURVE_24_PRE_POS                             (0U)
#define DSP2_BLBACK_CURVE_24_PRE_LEN                             (10U)
#define DSP2_BLBACK_CURVE_24_PRE_MSK                             (((1U<<DSP2_BLBACK_CURVE_24_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_24_PRE_POS)
#define DSP2_BLBACK_CURVE_24_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CURVE_24_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_24_PRE_POS))
#define DSP2_BLBACK_CURVE_25_PRE                                 DSP2_BLBACK_CURVE_25_PRE
#define DSP2_BLBACK_CURVE_25_PRE_POS                             (16U)
#define DSP2_BLBACK_CURVE_25_PRE_LEN                             (10U)
#define DSP2_BLBACK_CURVE_25_PRE_MSK                             (((1U<<DSP2_BLBACK_CURVE_25_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_25_PRE_POS)
#define DSP2_BLBACK_CURVE_25_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CURVE_25_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_25_PRE_POS))

/* 0xC34 : WDR_CURVE_14 */
#define DSP2_BLBACK_WDR_CURVE_14_OFFSET                          (0xC34)
#define DSP2_BLBACK_CURVE_26_PRE                                 DSP2_BLBACK_CURVE_26_PRE
#define DSP2_BLBACK_CURVE_26_PRE_POS                             (0U)
#define DSP2_BLBACK_CURVE_26_PRE_LEN                             (10U)
#define DSP2_BLBACK_CURVE_26_PRE_MSK                             (((1U<<DSP2_BLBACK_CURVE_26_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_26_PRE_POS)
#define DSP2_BLBACK_CURVE_26_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CURVE_26_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_26_PRE_POS))
#define DSP2_BLBACK_CURVE_27_PRE                                 DSP2_BLBACK_CURVE_27_PRE
#define DSP2_BLBACK_CURVE_27_PRE_POS                             (16U)
#define DSP2_BLBACK_CURVE_27_PRE_LEN                             (10U)
#define DSP2_BLBACK_CURVE_27_PRE_MSK                             (((1U<<DSP2_BLBACK_CURVE_27_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_27_PRE_POS)
#define DSP2_BLBACK_CURVE_27_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CURVE_27_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_27_PRE_POS))

/* 0xC38 : WDR_CURVE_15 */
#define DSP2_BLBACK_WDR_CURVE_15_OFFSET                          (0xC38)
#define DSP2_BLBACK_CURVE_28_PRE                                 DSP2_BLBACK_CURVE_28_PRE
#define DSP2_BLBACK_CURVE_28_PRE_POS                             (0U)
#define DSP2_BLBACK_CURVE_28_PRE_LEN                             (10U)
#define DSP2_BLBACK_CURVE_28_PRE_MSK                             (((1U<<DSP2_BLBACK_CURVE_28_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_28_PRE_POS)
#define DSP2_BLBACK_CURVE_28_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CURVE_28_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_28_PRE_POS))
#define DSP2_BLBACK_CURVE_29_PRE                                 DSP2_BLBACK_CURVE_29_PRE
#define DSP2_BLBACK_CURVE_29_PRE_POS                             (16U)
#define DSP2_BLBACK_CURVE_29_PRE_LEN                             (10U)
#define DSP2_BLBACK_CURVE_29_PRE_MSK                             (((1U<<DSP2_BLBACK_CURVE_29_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_29_PRE_POS)
#define DSP2_BLBACK_CURVE_29_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CURVE_29_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_29_PRE_POS))

/* 0xC3C : WDR_CURVE_16 */
#define DSP2_BLBACK_WDR_CURVE_16_OFFSET                          (0xC3C)
#define DSP2_BLBACK_CURVE_30_PRE                                 DSP2_BLBACK_CURVE_30_PRE
#define DSP2_BLBACK_CURVE_30_PRE_POS                             (0U)
#define DSP2_BLBACK_CURVE_30_PRE_LEN                             (10U)
#define DSP2_BLBACK_CURVE_30_PRE_MSK                             (((1U<<DSP2_BLBACK_CURVE_30_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_30_PRE_POS)
#define DSP2_BLBACK_CURVE_30_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CURVE_30_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_30_PRE_POS))
#define DSP2_BLBACK_CURVE_31_PRE                                 DSP2_BLBACK_CURVE_31_PRE
#define DSP2_BLBACK_CURVE_31_PRE_POS                             (16U)
#define DSP2_BLBACK_CURVE_31_PRE_LEN                             (10U)
#define DSP2_BLBACK_CURVE_31_PRE_MSK                             (((1U<<DSP2_BLBACK_CURVE_31_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_31_PRE_POS)
#define DSP2_BLBACK_CURVE_31_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CURVE_31_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_31_PRE_POS))

/* 0xC40 : WDR_CURVE_17 */
#define DSP2_BLBACK_WDR_CURVE_17_OFFSET                          (0xC40)
#define DSP2_BLBACK_CURVE_32_PRE                                 DSP2_BLBACK_CURVE_32_PRE
#define DSP2_BLBACK_CURVE_32_PRE_POS                             (0U)
#define DSP2_BLBACK_CURVE_32_PRE_LEN                             (10U)
#define DSP2_BLBACK_CURVE_32_PRE_MSK                             (((1U<<DSP2_BLBACK_CURVE_32_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_32_PRE_POS)
#define DSP2_BLBACK_CURVE_32_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CURVE_32_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_32_PRE_POS))
#define DSP2_BLBACK_CURVE_33_PRE                                 DSP2_BLBACK_CURVE_33_PRE
#define DSP2_BLBACK_CURVE_33_PRE_POS                             (16U)
#define DSP2_BLBACK_CURVE_33_PRE_LEN                             (10U)
#define DSP2_BLBACK_CURVE_33_PRE_MSK                             (((1U<<DSP2_BLBACK_CURVE_33_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_33_PRE_POS)
#define DSP2_BLBACK_CURVE_33_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CURVE_33_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_33_PRE_POS))

/* 0xC44 : WDR_CURVE_18 */
#define DSP2_BLBACK_WDR_CURVE_18_OFFSET                          (0xC44)
#define DSP2_BLBACK_CURVE_34_PRE                                 DSP2_BLBACK_CURVE_34_PRE
#define DSP2_BLBACK_CURVE_34_PRE_POS                             (0U)
#define DSP2_BLBACK_CURVE_34_PRE_LEN                             (10U)
#define DSP2_BLBACK_CURVE_34_PRE_MSK                             (((1U<<DSP2_BLBACK_CURVE_34_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_34_PRE_POS)
#define DSP2_BLBACK_CURVE_34_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CURVE_34_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_34_PRE_POS))
#define DSP2_BLBACK_CURVE_35_PRE                                 DSP2_BLBACK_CURVE_35_PRE
#define DSP2_BLBACK_CURVE_35_PRE_POS                             (16U)
#define DSP2_BLBACK_CURVE_35_PRE_LEN                             (10U)
#define DSP2_BLBACK_CURVE_35_PRE_MSK                             (((1U<<DSP2_BLBACK_CURVE_35_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_35_PRE_POS)
#define DSP2_BLBACK_CURVE_35_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CURVE_35_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_35_PRE_POS))

/* 0xC48 : WDR_CURVE_19 */
#define DSP2_BLBACK_WDR_CURVE_19_OFFSET                          (0xC48)
#define DSP2_BLBACK_CURVE_36_PRE                                 DSP2_BLBACK_CURVE_36_PRE
#define DSP2_BLBACK_CURVE_36_PRE_POS                             (0U)
#define DSP2_BLBACK_CURVE_36_PRE_LEN                             (10U)
#define DSP2_BLBACK_CURVE_36_PRE_MSK                             (((1U<<DSP2_BLBACK_CURVE_36_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_36_PRE_POS)
#define DSP2_BLBACK_CURVE_36_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CURVE_36_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_36_PRE_POS))
#define DSP2_BLBACK_CURVE_37_PRE                                 DSP2_BLBACK_CURVE_37_PRE
#define DSP2_BLBACK_CURVE_37_PRE_POS                             (16U)
#define DSP2_BLBACK_CURVE_37_PRE_LEN                             (10U)
#define DSP2_BLBACK_CURVE_37_PRE_MSK                             (((1U<<DSP2_BLBACK_CURVE_37_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_37_PRE_POS)
#define DSP2_BLBACK_CURVE_37_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CURVE_37_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_37_PRE_POS))

/* 0xC4C : WDR_CURVE_20 */
#define DSP2_BLBACK_WDR_CURVE_20_OFFSET                          (0xC4C)
#define DSP2_BLBACK_CURVE_38_PRE                                 DSP2_BLBACK_CURVE_38_PRE
#define DSP2_BLBACK_CURVE_38_PRE_POS                             (0U)
#define DSP2_BLBACK_CURVE_38_PRE_LEN                             (10U)
#define DSP2_BLBACK_CURVE_38_PRE_MSK                             (((1U<<DSP2_BLBACK_CURVE_38_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_38_PRE_POS)
#define DSP2_BLBACK_CURVE_38_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CURVE_38_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_38_PRE_POS))
#define DSP2_BLBACK_CURVE_39_PRE                                 DSP2_BLBACK_CURVE_39_PRE
#define DSP2_BLBACK_CURVE_39_PRE_POS                             (16U)
#define DSP2_BLBACK_CURVE_39_PRE_LEN                             (10U)
#define DSP2_BLBACK_CURVE_39_PRE_MSK                             (((1U<<DSP2_BLBACK_CURVE_39_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_39_PRE_POS)
#define DSP2_BLBACK_CURVE_39_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CURVE_39_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_39_PRE_POS))

/* 0xC50 : WDR_CURVE_21 */
#define DSP2_BLBACK_WDR_CURVE_21_OFFSET                          (0xC50)
#define DSP2_BLBACK_CURVE_40_PRE                                 DSP2_BLBACK_CURVE_40_PRE
#define DSP2_BLBACK_CURVE_40_PRE_POS                             (0U)
#define DSP2_BLBACK_CURVE_40_PRE_LEN                             (10U)
#define DSP2_BLBACK_CURVE_40_PRE_MSK                             (((1U<<DSP2_BLBACK_CURVE_40_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_40_PRE_POS)
#define DSP2_BLBACK_CURVE_40_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CURVE_40_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_40_PRE_POS))
#define DSP2_BLBACK_CURVE_41_PRE                                 DSP2_BLBACK_CURVE_41_PRE
#define DSP2_BLBACK_CURVE_41_PRE_POS                             (16U)
#define DSP2_BLBACK_CURVE_41_PRE_LEN                             (10U)
#define DSP2_BLBACK_CURVE_41_PRE_MSK                             (((1U<<DSP2_BLBACK_CURVE_41_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_41_PRE_POS)
#define DSP2_BLBACK_CURVE_41_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CURVE_41_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_41_PRE_POS))

/* 0xC54 : WDR_CURVE_22 */
#define DSP2_BLBACK_WDR_CURVE_22_OFFSET                          (0xC54)
#define DSP2_BLBACK_CURVE_42_PRE                                 DSP2_BLBACK_CURVE_42_PRE
#define DSP2_BLBACK_CURVE_42_PRE_POS                             (0U)
#define DSP2_BLBACK_CURVE_42_PRE_LEN                             (10U)
#define DSP2_BLBACK_CURVE_42_PRE_MSK                             (((1U<<DSP2_BLBACK_CURVE_42_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_42_PRE_POS)
#define DSP2_BLBACK_CURVE_42_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CURVE_42_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_42_PRE_POS))
#define DSP2_BLBACK_CURVE_43_PRE                                 DSP2_BLBACK_CURVE_43_PRE
#define DSP2_BLBACK_CURVE_43_PRE_POS                             (16U)
#define DSP2_BLBACK_CURVE_43_PRE_LEN                             (10U)
#define DSP2_BLBACK_CURVE_43_PRE_MSK                             (((1U<<DSP2_BLBACK_CURVE_43_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_43_PRE_POS)
#define DSP2_BLBACK_CURVE_43_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CURVE_43_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_43_PRE_POS))

/* 0xC58 : WDR_CURVE_23 */
#define DSP2_BLBACK_WDR_CURVE_23_OFFSET                          (0xC58)
#define DSP2_BLBACK_CURVE_44_PRE                                 DSP2_BLBACK_CURVE_44_PRE
#define DSP2_BLBACK_CURVE_44_PRE_POS                             (0U)
#define DSP2_BLBACK_CURVE_44_PRE_LEN                             (10U)
#define DSP2_BLBACK_CURVE_44_PRE_MSK                             (((1U<<DSP2_BLBACK_CURVE_44_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_44_PRE_POS)
#define DSP2_BLBACK_CURVE_44_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CURVE_44_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_44_PRE_POS))
#define DSP2_BLBACK_CURVE_45_PRE                                 DSP2_BLBACK_CURVE_45_PRE
#define DSP2_BLBACK_CURVE_45_PRE_POS                             (16U)
#define DSP2_BLBACK_CURVE_45_PRE_LEN                             (10U)
#define DSP2_BLBACK_CURVE_45_PRE_MSK                             (((1U<<DSP2_BLBACK_CURVE_45_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_45_PRE_POS)
#define DSP2_BLBACK_CURVE_45_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CURVE_45_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_45_PRE_POS))

/* 0xC5C : WDR_CURVE_24 */
#define DSP2_BLBACK_WDR_CURVE_24_OFFSET                          (0xC5C)
#define DSP2_BLBACK_CURVE_46_PRE                                 DSP2_BLBACK_CURVE_46_PRE
#define DSP2_BLBACK_CURVE_46_PRE_POS                             (0U)
#define DSP2_BLBACK_CURVE_46_PRE_LEN                             (10U)
#define DSP2_BLBACK_CURVE_46_PRE_MSK                             (((1U<<DSP2_BLBACK_CURVE_46_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_46_PRE_POS)
#define DSP2_BLBACK_CURVE_46_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CURVE_46_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_46_PRE_POS))
#define DSP2_BLBACK_CURVE_47_PRE                                 DSP2_BLBACK_CURVE_47_PRE
#define DSP2_BLBACK_CURVE_47_PRE_POS                             (16U)
#define DSP2_BLBACK_CURVE_47_PRE_LEN                             (10U)
#define DSP2_BLBACK_CURVE_47_PRE_MSK                             (((1U<<DSP2_BLBACK_CURVE_47_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_47_PRE_POS)
#define DSP2_BLBACK_CURVE_47_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CURVE_47_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_47_PRE_POS))

/* 0xC60 : WDR_CURVE_25 */
#define DSP2_BLBACK_WDR_CURVE_25_OFFSET                          (0xC60)
#define DSP2_BLBACK_CURVE_48_PRE                                 DSP2_BLBACK_CURVE_48_PRE
#define DSP2_BLBACK_CURVE_48_PRE_POS                             (0U)
#define DSP2_BLBACK_CURVE_48_PRE_LEN                             (10U)
#define DSP2_BLBACK_CURVE_48_PRE_MSK                             (((1U<<DSP2_BLBACK_CURVE_48_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_48_PRE_POS)
#define DSP2_BLBACK_CURVE_48_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CURVE_48_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_48_PRE_POS))
#define DSP2_BLBACK_CURVE_49_PRE                                 DSP2_BLBACK_CURVE_49_PRE
#define DSP2_BLBACK_CURVE_49_PRE_POS                             (16U)
#define DSP2_BLBACK_CURVE_49_PRE_LEN                             (10U)
#define DSP2_BLBACK_CURVE_49_PRE_MSK                             (((1U<<DSP2_BLBACK_CURVE_49_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_49_PRE_POS)
#define DSP2_BLBACK_CURVE_49_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CURVE_49_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_49_PRE_POS))

/* 0xC64 : WDR_CURVE_26 */
#define DSP2_BLBACK_WDR_CURVE_26_OFFSET                          (0xC64)
#define DSP2_BLBACK_CURVE_50_PRE                                 DSP2_BLBACK_CURVE_50_PRE
#define DSP2_BLBACK_CURVE_50_PRE_POS                             (0U)
#define DSP2_BLBACK_CURVE_50_PRE_LEN                             (10U)
#define DSP2_BLBACK_CURVE_50_PRE_MSK                             (((1U<<DSP2_BLBACK_CURVE_50_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_50_PRE_POS)
#define DSP2_BLBACK_CURVE_50_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CURVE_50_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_50_PRE_POS))
#define DSP2_BLBACK_CURVE_51_PRE                                 DSP2_BLBACK_CURVE_51_PRE
#define DSP2_BLBACK_CURVE_51_PRE_POS                             (16U)
#define DSP2_BLBACK_CURVE_51_PRE_LEN                             (10U)
#define DSP2_BLBACK_CURVE_51_PRE_MSK                             (((1U<<DSP2_BLBACK_CURVE_51_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_51_PRE_POS)
#define DSP2_BLBACK_CURVE_51_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CURVE_51_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_51_PRE_POS))

/* 0xC68 : WDR_CURVE_27 */
#define DSP2_BLBACK_WDR_CURVE_27_OFFSET                          (0xC68)
#define DSP2_BLBACK_CURVE_52_PRE                                 DSP2_BLBACK_CURVE_52_PRE
#define DSP2_BLBACK_CURVE_52_PRE_POS                             (0U)
#define DSP2_BLBACK_CURVE_52_PRE_LEN                             (10U)
#define DSP2_BLBACK_CURVE_52_PRE_MSK                             (((1U<<DSP2_BLBACK_CURVE_52_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_52_PRE_POS)
#define DSP2_BLBACK_CURVE_52_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CURVE_52_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_52_PRE_POS))
#define DSP2_BLBACK_CURVE_53_PRE                                 DSP2_BLBACK_CURVE_53_PRE
#define DSP2_BLBACK_CURVE_53_PRE_POS                             (16U)
#define DSP2_BLBACK_CURVE_53_PRE_LEN                             (10U)
#define DSP2_BLBACK_CURVE_53_PRE_MSK                             (((1U<<DSP2_BLBACK_CURVE_53_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_53_PRE_POS)
#define DSP2_BLBACK_CURVE_53_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CURVE_53_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_53_PRE_POS))

/* 0xC6C : WDR_CURVE_28 */
#define DSP2_BLBACK_WDR_CURVE_28_OFFSET                          (0xC6C)
#define DSP2_BLBACK_CURVE_54_PRE                                 DSP2_BLBACK_CURVE_54_PRE
#define DSP2_BLBACK_CURVE_54_PRE_POS                             (0U)
#define DSP2_BLBACK_CURVE_54_PRE_LEN                             (10U)
#define DSP2_BLBACK_CURVE_54_PRE_MSK                             (((1U<<DSP2_BLBACK_CURVE_54_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_54_PRE_POS)
#define DSP2_BLBACK_CURVE_54_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CURVE_54_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_54_PRE_POS))
#define DSP2_BLBACK_CURVE_55_PRE                                 DSP2_BLBACK_CURVE_55_PRE
#define DSP2_BLBACK_CURVE_55_PRE_POS                             (16U)
#define DSP2_BLBACK_CURVE_55_PRE_LEN                             (10U)
#define DSP2_BLBACK_CURVE_55_PRE_MSK                             (((1U<<DSP2_BLBACK_CURVE_55_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_55_PRE_POS)
#define DSP2_BLBACK_CURVE_55_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CURVE_55_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_55_PRE_POS))

/* 0xC70 : WDR_CURVE_29 */
#define DSP2_BLBACK_WDR_CURVE_29_OFFSET                          (0xC70)
#define DSP2_BLBACK_CURVE_56_PRE                                 DSP2_BLBACK_CURVE_56_PRE
#define DSP2_BLBACK_CURVE_56_PRE_POS                             (0U)
#define DSP2_BLBACK_CURVE_56_PRE_LEN                             (10U)
#define DSP2_BLBACK_CURVE_56_PRE_MSK                             (((1U<<DSP2_BLBACK_CURVE_56_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_56_PRE_POS)
#define DSP2_BLBACK_CURVE_56_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CURVE_56_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_56_PRE_POS))
#define DSP2_BLBACK_CURVE_57_PRE                                 DSP2_BLBACK_CURVE_57_PRE
#define DSP2_BLBACK_CURVE_57_PRE_POS                             (16U)
#define DSP2_BLBACK_CURVE_57_PRE_LEN                             (10U)
#define DSP2_BLBACK_CURVE_57_PRE_MSK                             (((1U<<DSP2_BLBACK_CURVE_57_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_57_PRE_POS)
#define DSP2_BLBACK_CURVE_57_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CURVE_57_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_57_PRE_POS))

/* 0xC74 : WDR_CURVE_30 */
#define DSP2_BLBACK_WDR_CURVE_30_OFFSET                          (0xC74)
#define DSP2_BLBACK_CURVE_58_PRE                                 DSP2_BLBACK_CURVE_58_PRE
#define DSP2_BLBACK_CURVE_58_PRE_POS                             (0U)
#define DSP2_BLBACK_CURVE_58_PRE_LEN                             (10U)
#define DSP2_BLBACK_CURVE_58_PRE_MSK                             (((1U<<DSP2_BLBACK_CURVE_58_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_58_PRE_POS)
#define DSP2_BLBACK_CURVE_58_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CURVE_58_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_58_PRE_POS))
#define DSP2_BLBACK_CURVE_59_PRE                                 DSP2_BLBACK_CURVE_59_PRE
#define DSP2_BLBACK_CURVE_59_PRE_POS                             (16U)
#define DSP2_BLBACK_CURVE_59_PRE_LEN                             (10U)
#define DSP2_BLBACK_CURVE_59_PRE_MSK                             (((1U<<DSP2_BLBACK_CURVE_59_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_59_PRE_POS)
#define DSP2_BLBACK_CURVE_59_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CURVE_59_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_59_PRE_POS))

/* 0xC78 : WDR_CURVE_31 */
#define DSP2_BLBACK_WDR_CURVE_31_OFFSET                          (0xC78)
#define DSP2_BLBACK_CURVE_60_PRE                                 DSP2_BLBACK_CURVE_60_PRE
#define DSP2_BLBACK_CURVE_60_PRE_POS                             (0U)
#define DSP2_BLBACK_CURVE_60_PRE_LEN                             (10U)
#define DSP2_BLBACK_CURVE_60_PRE_MSK                             (((1U<<DSP2_BLBACK_CURVE_60_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_60_PRE_POS)
#define DSP2_BLBACK_CURVE_60_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CURVE_60_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_60_PRE_POS))
#define DSP2_BLBACK_CURVE_61_PRE                                 DSP2_BLBACK_CURVE_61_PRE
#define DSP2_BLBACK_CURVE_61_PRE_POS                             (16U)
#define DSP2_BLBACK_CURVE_61_PRE_LEN                             (10U)
#define DSP2_BLBACK_CURVE_61_PRE_MSK                             (((1U<<DSP2_BLBACK_CURVE_61_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_61_PRE_POS)
#define DSP2_BLBACK_CURVE_61_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CURVE_61_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_61_PRE_POS))

/* 0xC7C : WDR_CURVE_32 */
#define DSP2_BLBACK_WDR_CURVE_32_OFFSET                          (0xC7C)
#define DSP2_BLBACK_CURVE_62_PRE                                 DSP2_BLBACK_CURVE_62_PRE
#define DSP2_BLBACK_CURVE_62_PRE_POS                             (0U)
#define DSP2_BLBACK_CURVE_62_PRE_LEN                             (10U)
#define DSP2_BLBACK_CURVE_62_PRE_MSK                             (((1U<<DSP2_BLBACK_CURVE_62_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_62_PRE_POS)
#define DSP2_BLBACK_CURVE_62_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CURVE_62_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_62_PRE_POS))
#define DSP2_BLBACK_CURVE_63_PRE                                 DSP2_BLBACK_CURVE_63_PRE
#define DSP2_BLBACK_CURVE_63_PRE_POS                             (16U)
#define DSP2_BLBACK_CURVE_63_PRE_LEN                             (10U)
#define DSP2_BLBACK_CURVE_63_PRE_MSK                             (((1U<<DSP2_BLBACK_CURVE_63_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_63_PRE_POS)
#define DSP2_BLBACK_CURVE_63_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CURVE_63_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_63_PRE_POS))

/* 0xC80 : WDR_CURVE_33 */
#define DSP2_BLBACK_WDR_CURVE_33_OFFSET                          (0xC80)
#define DSP2_BLBACK_CURVE_EN_PRE                                 DSP2_BLBACK_CURVE_EN_PRE
#define DSP2_BLBACK_CURVE_EN_PRE_POS                             (0U)
#define DSP2_BLBACK_CURVE_EN_PRE_LEN                             (1U)
#define DSP2_BLBACK_CURVE_EN_PRE_MSK                             (((1U<<DSP2_BLBACK_CURVE_EN_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_EN_PRE_POS)
#define DSP2_BLBACK_CURVE_EN_PRE_UMSK                            (~(((1U<<DSP2_BLBACK_CURVE_EN_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_EN_PRE_POS))
#define DSP2_BLBACK_CURVE_WEIGHT_PRE                             DSP2_BLBACK_CURVE_WEIGHT_PRE
#define DSP2_BLBACK_CURVE_WEIGHT_PRE_POS                         (8U)
#define DSP2_BLBACK_CURVE_WEIGHT_PRE_LEN                         (5U)
#define DSP2_BLBACK_CURVE_WEIGHT_PRE_MSK                         (((1U<<DSP2_BLBACK_CURVE_WEIGHT_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_WEIGHT_PRE_POS)
#define DSP2_BLBACK_CURVE_WEIGHT_PRE_UMSK                        (~(((1U<<DSP2_BLBACK_CURVE_WEIGHT_PRE_LEN)-1)<<DSP2_BLBACK_CURVE_WEIGHT_PRE_POS))

/* 0xC84 : WDR_ENH_1 */
#define DSP2_BLBACK_WDR_ENH_1_OFFSET                             (0xC84)
#define DSP2_BLBACK_ENH_EN_PRE                                   DSP2_BLBACK_ENH_EN_PRE
#define DSP2_BLBACK_ENH_EN_PRE_POS                               (0U)
#define DSP2_BLBACK_ENH_EN_PRE_LEN                               (1U)
#define DSP2_BLBACK_ENH_EN_PRE_MSK                               (((1U<<DSP2_BLBACK_ENH_EN_PRE_LEN)-1)<<DSP2_BLBACK_ENH_EN_PRE_POS)
#define DSP2_BLBACK_ENH_EN_PRE_UMSK                              (~(((1U<<DSP2_BLBACK_ENH_EN_PRE_LEN)-1)<<DSP2_BLBACK_ENH_EN_PRE_POS))
#define DSP2_BLBACK_ENH_WEIGHT_PRE                               DSP2_BLBACK_ENH_WEIGHT_PRE
#define DSP2_BLBACK_ENH_WEIGHT_PRE_POS                           (8U)
#define DSP2_BLBACK_ENH_WEIGHT_PRE_LEN                           (5U)
#define DSP2_BLBACK_ENH_WEIGHT_PRE_MSK                           (((1U<<DSP2_BLBACK_ENH_WEIGHT_PRE_LEN)-1)<<DSP2_BLBACK_ENH_WEIGHT_PRE_POS)
#define DSP2_BLBACK_ENH_WEIGHT_PRE_UMSK                          (~(((1U<<DSP2_BLBACK_ENH_WEIGHT_PRE_LEN)-1)<<DSP2_BLBACK_ENH_WEIGHT_PRE_POS))
#define DSP2_BLBACK_ENH_Y_OFFSET_PRE                             DSP2_BLBACK_ENH_Y_OFFSET_PRE
#define DSP2_BLBACK_ENH_Y_OFFSET_PRE_POS                         (16U)
#define DSP2_BLBACK_ENH_Y_OFFSET_PRE_LEN                         (12U)
#define DSP2_BLBACK_ENH_Y_OFFSET_PRE_MSK                         (((1U<<DSP2_BLBACK_ENH_Y_OFFSET_PRE_LEN)-1)<<DSP2_BLBACK_ENH_Y_OFFSET_PRE_POS)
#define DSP2_BLBACK_ENH_Y_OFFSET_PRE_UMSK                        (~(((1U<<DSP2_BLBACK_ENH_Y_OFFSET_PRE_LEN)-1)<<DSP2_BLBACK_ENH_Y_OFFSET_PRE_POS))

/* 0xC88 : WDR_ENH_2 */
#define DSP2_BLBACK_WDR_ENH_2_OFFSET                             (0xC88)
#define DSP2_BLBACK_ENH_C_GAIN_PRE                               DSP2_BLBACK_ENH_C_GAIN_PRE
#define DSP2_BLBACK_ENH_C_GAIN_PRE_POS                           (0U)
#define DSP2_BLBACK_ENH_C_GAIN_PRE_LEN                           (15U)
#define DSP2_BLBACK_ENH_C_GAIN_PRE_MSK                           (((1U<<DSP2_BLBACK_ENH_C_GAIN_PRE_LEN)-1)<<DSP2_BLBACK_ENH_C_GAIN_PRE_POS)
#define DSP2_BLBACK_ENH_C_GAIN_PRE_UMSK                          (~(((1U<<DSP2_BLBACK_ENH_C_GAIN_PRE_LEN)-1)<<DSP2_BLBACK_ENH_C_GAIN_PRE_POS))
#define DSP2_BLBACK_ENH_Y_GAIN_PRE                               DSP2_BLBACK_ENH_Y_GAIN_PRE
#define DSP2_BLBACK_ENH_Y_GAIN_PRE_POS                           (16U)
#define DSP2_BLBACK_ENH_Y_GAIN_PRE_LEN                           (15U)
#define DSP2_BLBACK_ENH_Y_GAIN_PRE_MSK                           (((1U<<DSP2_BLBACK_ENH_Y_GAIN_PRE_LEN)-1)<<DSP2_BLBACK_ENH_Y_GAIN_PRE_POS)
#define DSP2_BLBACK_ENH_Y_GAIN_PRE_UMSK                          (~(((1U<<DSP2_BLBACK_ENH_Y_GAIN_PRE_LEN)-1)<<DSP2_BLBACK_ENH_Y_GAIN_PRE_POS))

/* 0xD00 : BL_GAMMA_TABLE_1 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_1_OFFSET                      (0xD00)
#define DSP2_BLBACK_GAMMA_TABLE0_PRE                             DSP2_BLBACK_GAMMA_TABLE0_PRE
#define DSP2_BLBACK_GAMMA_TABLE0_PRE_POS                         (0U)
#define DSP2_BLBACK_GAMMA_TABLE0_PRE_LEN                         (12U)
#define DSP2_BLBACK_GAMMA_TABLE0_PRE_MSK                         (((1U<<DSP2_BLBACK_GAMMA_TABLE0_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE0_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE0_PRE_UMSK                        (~(((1U<<DSP2_BLBACK_GAMMA_TABLE0_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE0_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE1_PRE                             DSP2_BLBACK_GAMMA_TABLE1_PRE
#define DSP2_BLBACK_GAMMA_TABLE1_PRE_POS                         (16U)
#define DSP2_BLBACK_GAMMA_TABLE1_PRE_LEN                         (12U)
#define DSP2_BLBACK_GAMMA_TABLE1_PRE_MSK                         (((1U<<DSP2_BLBACK_GAMMA_TABLE1_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE1_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE1_PRE_UMSK                        (~(((1U<<DSP2_BLBACK_GAMMA_TABLE1_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE1_PRE_POS))

/* 0xD04 : BL_GAMMA_TABLE_2 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_2_OFFSET                      (0xD04)
#define DSP2_BLBACK_GAMMA_TABLE2_PRE                             DSP2_BLBACK_GAMMA_TABLE2_PRE
#define DSP2_BLBACK_GAMMA_TABLE2_PRE_POS                         (0U)
#define DSP2_BLBACK_GAMMA_TABLE2_PRE_LEN                         (12U)
#define DSP2_BLBACK_GAMMA_TABLE2_PRE_MSK                         (((1U<<DSP2_BLBACK_GAMMA_TABLE2_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE2_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE2_PRE_UMSK                        (~(((1U<<DSP2_BLBACK_GAMMA_TABLE2_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE2_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE3_PRE                             DSP2_BLBACK_GAMMA_TABLE3_PRE
#define DSP2_BLBACK_GAMMA_TABLE3_PRE_POS                         (16U)
#define DSP2_BLBACK_GAMMA_TABLE3_PRE_LEN                         (12U)
#define DSP2_BLBACK_GAMMA_TABLE3_PRE_MSK                         (((1U<<DSP2_BLBACK_GAMMA_TABLE3_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE3_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE3_PRE_UMSK                        (~(((1U<<DSP2_BLBACK_GAMMA_TABLE3_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE3_PRE_POS))

/* 0xD08 : BL_GAMMA_TABLE_3 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_3_OFFSET                      (0xD08)
#define DSP2_BLBACK_GAMMA_TABLE4_PRE                             DSP2_BLBACK_GAMMA_TABLE4_PRE
#define DSP2_BLBACK_GAMMA_TABLE4_PRE_POS                         (0U)
#define DSP2_BLBACK_GAMMA_TABLE4_PRE_LEN                         (12U)
#define DSP2_BLBACK_GAMMA_TABLE4_PRE_MSK                         (((1U<<DSP2_BLBACK_GAMMA_TABLE4_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE4_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE4_PRE_UMSK                        (~(((1U<<DSP2_BLBACK_GAMMA_TABLE4_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE4_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE5_PRE                             DSP2_BLBACK_GAMMA_TABLE5_PRE
#define DSP2_BLBACK_GAMMA_TABLE5_PRE_POS                         (16U)
#define DSP2_BLBACK_GAMMA_TABLE5_PRE_LEN                         (12U)
#define DSP2_BLBACK_GAMMA_TABLE5_PRE_MSK                         (((1U<<DSP2_BLBACK_GAMMA_TABLE5_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE5_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE5_PRE_UMSK                        (~(((1U<<DSP2_BLBACK_GAMMA_TABLE5_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE5_PRE_POS))

/* 0xD0C : BL_GAMMA_TABLE_4 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_4_OFFSET                      (0xD0C)
#define DSP2_BLBACK_GAMMA_TABLE6_PRE                             DSP2_BLBACK_GAMMA_TABLE6_PRE
#define DSP2_BLBACK_GAMMA_TABLE6_PRE_POS                         (0U)
#define DSP2_BLBACK_GAMMA_TABLE6_PRE_LEN                         (12U)
#define DSP2_BLBACK_GAMMA_TABLE6_PRE_MSK                         (((1U<<DSP2_BLBACK_GAMMA_TABLE6_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE6_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE6_PRE_UMSK                        (~(((1U<<DSP2_BLBACK_GAMMA_TABLE6_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE6_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE7_PRE                             DSP2_BLBACK_GAMMA_TABLE7_PRE
#define DSP2_BLBACK_GAMMA_TABLE7_PRE_POS                         (16U)
#define DSP2_BLBACK_GAMMA_TABLE7_PRE_LEN                         (12U)
#define DSP2_BLBACK_GAMMA_TABLE7_PRE_MSK                         (((1U<<DSP2_BLBACK_GAMMA_TABLE7_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE7_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE7_PRE_UMSK                        (~(((1U<<DSP2_BLBACK_GAMMA_TABLE7_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE7_PRE_POS))

/* 0xD10 : BL_GAMMA_TABLE_5 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_5_OFFSET                      (0xD10)
#define DSP2_BLBACK_GAMMA_TABLE8_PRE                             DSP2_BLBACK_GAMMA_TABLE8_PRE
#define DSP2_BLBACK_GAMMA_TABLE8_PRE_POS                         (0U)
#define DSP2_BLBACK_GAMMA_TABLE8_PRE_LEN                         (12U)
#define DSP2_BLBACK_GAMMA_TABLE8_PRE_MSK                         (((1U<<DSP2_BLBACK_GAMMA_TABLE8_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE8_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE8_PRE_UMSK                        (~(((1U<<DSP2_BLBACK_GAMMA_TABLE8_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE8_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE9_PRE                             DSP2_BLBACK_GAMMA_TABLE9_PRE
#define DSP2_BLBACK_GAMMA_TABLE9_PRE_POS                         (16U)
#define DSP2_BLBACK_GAMMA_TABLE9_PRE_LEN                         (12U)
#define DSP2_BLBACK_GAMMA_TABLE9_PRE_MSK                         (((1U<<DSP2_BLBACK_GAMMA_TABLE9_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE9_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE9_PRE_UMSK                        (~(((1U<<DSP2_BLBACK_GAMMA_TABLE9_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE9_PRE_POS))

/* 0xD14 : BL_GAMMA_TABLE_6 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_6_OFFSET                      (0xD14)
#define DSP2_BLBACK_GAMMA_TABLE10_PRE                            DSP2_BLBACK_GAMMA_TABLE10_PRE
#define DSP2_BLBACK_GAMMA_TABLE10_PRE_POS                        (0U)
#define DSP2_BLBACK_GAMMA_TABLE10_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE10_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE10_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE10_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE10_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE10_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE10_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE11_PRE                            DSP2_BLBACK_GAMMA_TABLE11_PRE
#define DSP2_BLBACK_GAMMA_TABLE11_PRE_POS                        (16U)
#define DSP2_BLBACK_GAMMA_TABLE11_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE11_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE11_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE11_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE11_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE11_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE11_PRE_POS))

/* 0xD18 : BL_GAMMA_TABLE_7 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_7_OFFSET                      (0xD18)
#define DSP2_BLBACK_GAMMA_TABLE12_PRE                            DSP2_BLBACK_GAMMA_TABLE12_PRE
#define DSP2_BLBACK_GAMMA_TABLE12_PRE_POS                        (0U)
#define DSP2_BLBACK_GAMMA_TABLE12_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE12_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE12_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE12_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE12_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE12_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE12_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE13_PRE                            DSP2_BLBACK_GAMMA_TABLE13_PRE
#define DSP2_BLBACK_GAMMA_TABLE13_PRE_POS                        (16U)
#define DSP2_BLBACK_GAMMA_TABLE13_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE13_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE13_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE13_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE13_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE13_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE13_PRE_POS))

/* 0xD1C : BL_GAMMA_TABLE_8 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_8_OFFSET                      (0xD1C)
#define DSP2_BLBACK_GAMMA_TABLE14_PRE                            DSP2_BLBACK_GAMMA_TABLE14_PRE
#define DSP2_BLBACK_GAMMA_TABLE14_PRE_POS                        (0U)
#define DSP2_BLBACK_GAMMA_TABLE14_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE14_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE14_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE14_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE14_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE14_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE14_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE15_PRE                            DSP2_BLBACK_GAMMA_TABLE15_PRE
#define DSP2_BLBACK_GAMMA_TABLE15_PRE_POS                        (16U)
#define DSP2_BLBACK_GAMMA_TABLE15_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE15_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE15_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE15_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE15_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE15_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE15_PRE_POS))

/* 0xD20 : BL_GAMMA_TABLE_9 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_9_OFFSET                      (0xD20)
#define DSP2_BLBACK_GAMMA_TABLE16_PRE                            DSP2_BLBACK_GAMMA_TABLE16_PRE
#define DSP2_BLBACK_GAMMA_TABLE16_PRE_POS                        (0U)
#define DSP2_BLBACK_GAMMA_TABLE16_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE16_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE16_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE16_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE16_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE16_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE16_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE17_PRE                            DSP2_BLBACK_GAMMA_TABLE17_PRE
#define DSP2_BLBACK_GAMMA_TABLE17_PRE_POS                        (16U)
#define DSP2_BLBACK_GAMMA_TABLE17_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE17_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE17_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE17_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE17_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE17_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE17_PRE_POS))

/* 0xD24 : BL_GAMMA_TABLE_10 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_10_OFFSET                     (0xD24)
#define DSP2_BLBACK_GAMMA_TABLE18_PRE                            DSP2_BLBACK_GAMMA_TABLE18_PRE
#define DSP2_BLBACK_GAMMA_TABLE18_PRE_POS                        (0U)
#define DSP2_BLBACK_GAMMA_TABLE18_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE18_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE18_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE18_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE18_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE18_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE18_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE19_PRE                            DSP2_BLBACK_GAMMA_TABLE19_PRE
#define DSP2_BLBACK_GAMMA_TABLE19_PRE_POS                        (16U)
#define DSP2_BLBACK_GAMMA_TABLE19_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE19_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE19_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE19_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE19_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE19_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE19_PRE_POS))

/* 0xD28 : BL_GAMMA_TABLE_11 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_11_OFFSET                     (0xD28)
#define DSP2_BLBACK_GAMMA_TABLE20_PRE                            DSP2_BLBACK_GAMMA_TABLE20_PRE
#define DSP2_BLBACK_GAMMA_TABLE20_PRE_POS                        (0U)
#define DSP2_BLBACK_GAMMA_TABLE20_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE20_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE20_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE20_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE20_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE20_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE20_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE21_PRE                            DSP2_BLBACK_GAMMA_TABLE21_PRE
#define DSP2_BLBACK_GAMMA_TABLE21_PRE_POS                        (16U)
#define DSP2_BLBACK_GAMMA_TABLE21_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE21_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE21_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE21_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE21_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE21_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE21_PRE_POS))

/* 0xD2C : BL_GAMMA_TABLE_12 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_12_OFFSET                     (0xD2C)
#define DSP2_BLBACK_GAMMA_TABLE22_PRE                            DSP2_BLBACK_GAMMA_TABLE22_PRE
#define DSP2_BLBACK_GAMMA_TABLE22_PRE_POS                        (0U)
#define DSP2_BLBACK_GAMMA_TABLE22_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE22_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE22_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE22_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE22_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE22_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE22_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE23_PRE                            DSP2_BLBACK_GAMMA_TABLE23_PRE
#define DSP2_BLBACK_GAMMA_TABLE23_PRE_POS                        (16U)
#define DSP2_BLBACK_GAMMA_TABLE23_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE23_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE23_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE23_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE23_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE23_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE23_PRE_POS))

/* 0xD30 : BL_GAMMA_TABLE_13 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_13_OFFSET                     (0xD30)
#define DSP2_BLBACK_GAMMA_TABLE24_PRE                            DSP2_BLBACK_GAMMA_TABLE24_PRE
#define DSP2_BLBACK_GAMMA_TABLE24_PRE_POS                        (0U)
#define DSP2_BLBACK_GAMMA_TABLE24_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE24_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE24_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE24_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE24_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE24_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE24_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE25_PRE                            DSP2_BLBACK_GAMMA_TABLE25_PRE
#define DSP2_BLBACK_GAMMA_TABLE25_PRE_POS                        (16U)
#define DSP2_BLBACK_GAMMA_TABLE25_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE25_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE25_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE25_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE25_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE25_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE25_PRE_POS))

/* 0xD34 : BL_GAMMA_TABLE_14 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_14_OFFSET                     (0xD34)
#define DSP2_BLBACK_GAMMA_TABLE26_PRE                            DSP2_BLBACK_GAMMA_TABLE26_PRE
#define DSP2_BLBACK_GAMMA_TABLE26_PRE_POS                        (0U)
#define DSP2_BLBACK_GAMMA_TABLE26_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE26_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE26_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE26_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE26_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE26_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE26_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE27_PRE                            DSP2_BLBACK_GAMMA_TABLE27_PRE
#define DSP2_BLBACK_GAMMA_TABLE27_PRE_POS                        (16U)
#define DSP2_BLBACK_GAMMA_TABLE27_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE27_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE27_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE27_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE27_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE27_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE27_PRE_POS))

/* 0xD38 : BL_GAMMA_TABLE_15 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_15_OFFSET                     (0xD38)
#define DSP2_BLBACK_GAMMA_TABLE28_PRE                            DSP2_BLBACK_GAMMA_TABLE28_PRE
#define DSP2_BLBACK_GAMMA_TABLE28_PRE_POS                        (0U)
#define DSP2_BLBACK_GAMMA_TABLE28_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE28_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE28_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE28_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE28_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE28_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE28_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE29_PRE                            DSP2_BLBACK_GAMMA_TABLE29_PRE
#define DSP2_BLBACK_GAMMA_TABLE29_PRE_POS                        (16U)
#define DSP2_BLBACK_GAMMA_TABLE29_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE29_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE29_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE29_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE29_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE29_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE29_PRE_POS))

/* 0xD3C : BL_GAMMA_TABLE_16 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_16_OFFSET                     (0xD3C)
#define DSP2_BLBACK_GAMMA_TABLE30_PRE                            DSP2_BLBACK_GAMMA_TABLE30_PRE
#define DSP2_BLBACK_GAMMA_TABLE30_PRE_POS                        (0U)
#define DSP2_BLBACK_GAMMA_TABLE30_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE30_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE30_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE30_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE30_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE30_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE30_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE31_PRE                            DSP2_BLBACK_GAMMA_TABLE31_PRE
#define DSP2_BLBACK_GAMMA_TABLE31_PRE_POS                        (16U)
#define DSP2_BLBACK_GAMMA_TABLE31_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE31_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE31_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE31_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE31_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE31_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE31_PRE_POS))

/* 0xD40 : BL_GAMMA_TABLE_17 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_17_OFFSET                     (0xD40)
#define DSP2_BLBACK_GAMMA_TABLE32_PRE                            DSP2_BLBACK_GAMMA_TABLE32_PRE
#define DSP2_BLBACK_GAMMA_TABLE32_PRE_POS                        (0U)
#define DSP2_BLBACK_GAMMA_TABLE32_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE32_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE32_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE32_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE32_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE32_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE32_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE33_PRE                            DSP2_BLBACK_GAMMA_TABLE33_PRE
#define DSP2_BLBACK_GAMMA_TABLE33_PRE_POS                        (16U)
#define DSP2_BLBACK_GAMMA_TABLE33_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE33_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE33_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE33_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE33_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE33_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE33_PRE_POS))

/* 0xD44 : BL_GAMMA_TABLE_18 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_18_OFFSET                     (0xD44)
#define DSP2_BLBACK_GAMMA_TABLE34_PRE                            DSP2_BLBACK_GAMMA_TABLE34_PRE
#define DSP2_BLBACK_GAMMA_TABLE34_PRE_POS                        (0U)
#define DSP2_BLBACK_GAMMA_TABLE34_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE34_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE34_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE34_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE34_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE34_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE34_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE35_PRE                            DSP2_BLBACK_GAMMA_TABLE35_PRE
#define DSP2_BLBACK_GAMMA_TABLE35_PRE_POS                        (16U)
#define DSP2_BLBACK_GAMMA_TABLE35_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE35_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE35_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE35_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE35_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE35_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE35_PRE_POS))

/* 0xD48 : BL_GAMMA_TABLE_19 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_19_OFFSET                     (0xD48)
#define DSP2_BLBACK_GAMMA_TABLE36_PRE                            DSP2_BLBACK_GAMMA_TABLE36_PRE
#define DSP2_BLBACK_GAMMA_TABLE36_PRE_POS                        (0U)
#define DSP2_BLBACK_GAMMA_TABLE36_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE36_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE36_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE36_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE36_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE36_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE36_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE37_PRE                            DSP2_BLBACK_GAMMA_TABLE37_PRE
#define DSP2_BLBACK_GAMMA_TABLE37_PRE_POS                        (16U)
#define DSP2_BLBACK_GAMMA_TABLE37_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE37_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE37_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE37_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE37_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE37_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE37_PRE_POS))

/* 0xD4C : BL_GAMMA_TABLE_20 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_20_OFFSET                     (0xD4C)
#define DSP2_BLBACK_GAMMA_TABLE38_PRE                            DSP2_BLBACK_GAMMA_TABLE38_PRE
#define DSP2_BLBACK_GAMMA_TABLE38_PRE_POS                        (0U)
#define DSP2_BLBACK_GAMMA_TABLE38_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE38_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE38_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE38_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE38_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE38_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE38_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE39_PRE                            DSP2_BLBACK_GAMMA_TABLE39_PRE
#define DSP2_BLBACK_GAMMA_TABLE39_PRE_POS                        (16U)
#define DSP2_BLBACK_GAMMA_TABLE39_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE39_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE39_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE39_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE39_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE39_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE39_PRE_POS))

/* 0xD50 : BL_GAMMA_TABLE_21 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_21_OFFSET                     (0xD50)
#define DSP2_BLBACK_GAMMA_TABLE40_PRE                            DSP2_BLBACK_GAMMA_TABLE40_PRE
#define DSP2_BLBACK_GAMMA_TABLE40_PRE_POS                        (0U)
#define DSP2_BLBACK_GAMMA_TABLE40_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE40_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE40_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE40_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE40_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE40_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE40_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE41_PRE                            DSP2_BLBACK_GAMMA_TABLE41_PRE
#define DSP2_BLBACK_GAMMA_TABLE41_PRE_POS                        (16U)
#define DSP2_BLBACK_GAMMA_TABLE41_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE41_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE41_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE41_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE41_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE41_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE41_PRE_POS))

/* 0xD54 : BL_GAMMA_TABLE_22 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_22_OFFSET                     (0xD54)
#define DSP2_BLBACK_GAMMA_TABLE42_PRE                            DSP2_BLBACK_GAMMA_TABLE42_PRE
#define DSP2_BLBACK_GAMMA_TABLE42_PRE_POS                        (0U)
#define DSP2_BLBACK_GAMMA_TABLE42_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE42_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE42_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE42_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE42_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE42_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE42_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE43_PRE                            DSP2_BLBACK_GAMMA_TABLE43_PRE
#define DSP2_BLBACK_GAMMA_TABLE43_PRE_POS                        (16U)
#define DSP2_BLBACK_GAMMA_TABLE43_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE43_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE43_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE43_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE43_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE43_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE43_PRE_POS))

/* 0xD58 : BL_GAMMA_TABLE_23 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_23_OFFSET                     (0xD58)
#define DSP2_BLBACK_GAMMA_TABLE44_PRE                            DSP2_BLBACK_GAMMA_TABLE44_PRE
#define DSP2_BLBACK_GAMMA_TABLE44_PRE_POS                        (0U)
#define DSP2_BLBACK_GAMMA_TABLE44_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE44_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE44_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE44_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE44_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE44_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE44_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE45_PRE                            DSP2_BLBACK_GAMMA_TABLE45_PRE
#define DSP2_BLBACK_GAMMA_TABLE45_PRE_POS                        (16U)
#define DSP2_BLBACK_GAMMA_TABLE45_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE45_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE45_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE45_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE45_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE45_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE45_PRE_POS))

/* 0xD5C : BL_GAMMA_TABLE_24 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_24_OFFSET                     (0xD5C)
#define DSP2_BLBACK_GAMMA_TABLE46_PRE                            DSP2_BLBACK_GAMMA_TABLE46_PRE
#define DSP2_BLBACK_GAMMA_TABLE46_PRE_POS                        (0U)
#define DSP2_BLBACK_GAMMA_TABLE46_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE46_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE46_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE46_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE46_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE46_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE46_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE47_PRE                            DSP2_BLBACK_GAMMA_TABLE47_PRE
#define DSP2_BLBACK_GAMMA_TABLE47_PRE_POS                        (16U)
#define DSP2_BLBACK_GAMMA_TABLE47_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE47_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE47_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE47_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE47_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE47_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE47_PRE_POS))

/* 0xD60 : BL_GAMMA_TABLE_25 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_25_OFFSET                     (0xD60)
#define DSP2_BLBACK_GAMMA_TABLE48_PRE                            DSP2_BLBACK_GAMMA_TABLE48_PRE
#define DSP2_BLBACK_GAMMA_TABLE48_PRE_POS                        (0U)
#define DSP2_BLBACK_GAMMA_TABLE48_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE48_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE48_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE48_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE48_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE48_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE48_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE49_PRE                            DSP2_BLBACK_GAMMA_TABLE49_PRE
#define DSP2_BLBACK_GAMMA_TABLE49_PRE_POS                        (16U)
#define DSP2_BLBACK_GAMMA_TABLE49_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE49_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE49_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE49_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE49_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE49_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE49_PRE_POS))

/* 0xD64 : BL_GAMMA_TABLE_26 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_26_OFFSET                     (0xD64)
#define DSP2_BLBACK_GAMMA_TABLE50_PRE                            DSP2_BLBACK_GAMMA_TABLE50_PRE
#define DSP2_BLBACK_GAMMA_TABLE50_PRE_POS                        (0U)
#define DSP2_BLBACK_GAMMA_TABLE50_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE50_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE50_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE50_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE50_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE50_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE50_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE51_PRE                            DSP2_BLBACK_GAMMA_TABLE51_PRE
#define DSP2_BLBACK_GAMMA_TABLE51_PRE_POS                        (16U)
#define DSP2_BLBACK_GAMMA_TABLE51_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE51_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE51_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE51_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE51_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE51_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE51_PRE_POS))

/* 0xD68 : BL_GAMMA_TABLE_27 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_27_OFFSET                     (0xD68)
#define DSP2_BLBACK_GAMMA_TABLE52_PRE                            DSP2_BLBACK_GAMMA_TABLE52_PRE
#define DSP2_BLBACK_GAMMA_TABLE52_PRE_POS                        (0U)
#define DSP2_BLBACK_GAMMA_TABLE52_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE52_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE52_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE52_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE52_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE52_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE52_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE53_PRE                            DSP2_BLBACK_GAMMA_TABLE53_PRE
#define DSP2_BLBACK_GAMMA_TABLE53_PRE_POS                        (16U)
#define DSP2_BLBACK_GAMMA_TABLE53_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE53_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE53_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE53_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE53_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE53_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE53_PRE_POS))

/* 0xD6C : BL_GAMMA_TABLE_28 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_28_OFFSET                     (0xD6C)
#define DSP2_BLBACK_GAMMA_TABLE54_PRE                            DSP2_BLBACK_GAMMA_TABLE54_PRE
#define DSP2_BLBACK_GAMMA_TABLE54_PRE_POS                        (0U)
#define DSP2_BLBACK_GAMMA_TABLE54_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE54_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE54_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE54_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE54_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE54_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE54_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE55_PRE                            DSP2_BLBACK_GAMMA_TABLE55_PRE
#define DSP2_BLBACK_GAMMA_TABLE55_PRE_POS                        (16U)
#define DSP2_BLBACK_GAMMA_TABLE55_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE55_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE55_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE55_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE55_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE55_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE55_PRE_POS))

/* 0xD70 : BL_GAMMA_TABLE_29 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_29_OFFSET                     (0xD70)
#define DSP2_BLBACK_GAMMA_TABLE56_PRE                            DSP2_BLBACK_GAMMA_TABLE56_PRE
#define DSP2_BLBACK_GAMMA_TABLE56_PRE_POS                        (0U)
#define DSP2_BLBACK_GAMMA_TABLE56_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE56_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE56_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE56_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE56_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE56_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE56_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE57_PRE                            DSP2_BLBACK_GAMMA_TABLE57_PRE
#define DSP2_BLBACK_GAMMA_TABLE57_PRE_POS                        (16U)
#define DSP2_BLBACK_GAMMA_TABLE57_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE57_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE57_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE57_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE57_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE57_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE57_PRE_POS))

/* 0xD74 : BL_GAMMA_TABLE_30 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_30_OFFSET                     (0xD74)
#define DSP2_BLBACK_GAMMA_TABLE58_PRE                            DSP2_BLBACK_GAMMA_TABLE58_PRE
#define DSP2_BLBACK_GAMMA_TABLE58_PRE_POS                        (0U)
#define DSP2_BLBACK_GAMMA_TABLE58_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE58_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE58_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE58_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE58_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE58_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE58_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE59_PRE                            DSP2_BLBACK_GAMMA_TABLE59_PRE
#define DSP2_BLBACK_GAMMA_TABLE59_PRE_POS                        (16U)
#define DSP2_BLBACK_GAMMA_TABLE59_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE59_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE59_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE59_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE59_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE59_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE59_PRE_POS))

/* 0xD78 : BL_GAMMA_TABLE_31 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_31_OFFSET                     (0xD78)
#define DSP2_BLBACK_GAMMA_TABLE60_PRE                            DSP2_BLBACK_GAMMA_TABLE60_PRE
#define DSP2_BLBACK_GAMMA_TABLE60_PRE_POS                        (0U)
#define DSP2_BLBACK_GAMMA_TABLE60_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE60_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE60_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE60_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE60_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE60_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE60_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE61_PRE                            DSP2_BLBACK_GAMMA_TABLE61_PRE
#define DSP2_BLBACK_GAMMA_TABLE61_PRE_POS                        (16U)
#define DSP2_BLBACK_GAMMA_TABLE61_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE61_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE61_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE61_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE61_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE61_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE61_PRE_POS))

/* 0xD7C : BL_GAMMA_TABLE_32 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_32_OFFSET                     (0xD7C)
#define DSP2_BLBACK_GAMMA_TABLE62_PRE                            DSP2_BLBACK_GAMMA_TABLE62_PRE
#define DSP2_BLBACK_GAMMA_TABLE62_PRE_POS                        (0U)
#define DSP2_BLBACK_GAMMA_TABLE62_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE62_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE62_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE62_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE62_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE62_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE62_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE63_PRE                            DSP2_BLBACK_GAMMA_TABLE63_PRE
#define DSP2_BLBACK_GAMMA_TABLE63_PRE_POS                        (16U)
#define DSP2_BLBACK_GAMMA_TABLE63_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE63_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE63_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE63_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE63_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE63_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE63_PRE_POS))

/* 0xD80 : BL_GAMMA_TABLE_33 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_33_OFFSET                     (0xD80)
#define DSP2_BLBACK_GAMMA_TABLE64_PRE                            DSP2_BLBACK_GAMMA_TABLE64_PRE
#define DSP2_BLBACK_GAMMA_TABLE64_PRE_POS                        (0U)
#define DSP2_BLBACK_GAMMA_TABLE64_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE64_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE64_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE64_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE64_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE64_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE64_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE65_PRE                            DSP2_BLBACK_GAMMA_TABLE65_PRE
#define DSP2_BLBACK_GAMMA_TABLE65_PRE_POS                        (16U)
#define DSP2_BLBACK_GAMMA_TABLE65_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE65_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE65_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE65_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE65_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE65_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE65_PRE_POS))

/* 0xD84 : BL_GAMMA_TABLE_34 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_34_OFFSET                     (0xD84)
#define DSP2_BLBACK_GAMMA_TABLE66_PRE                            DSP2_BLBACK_GAMMA_TABLE66_PRE
#define DSP2_BLBACK_GAMMA_TABLE66_PRE_POS                        (0U)
#define DSP2_BLBACK_GAMMA_TABLE66_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE66_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE66_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE66_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE66_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE66_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE66_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE67_PRE                            DSP2_BLBACK_GAMMA_TABLE67_PRE
#define DSP2_BLBACK_GAMMA_TABLE67_PRE_POS                        (16U)
#define DSP2_BLBACK_GAMMA_TABLE67_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE67_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE67_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE67_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE67_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE67_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE67_PRE_POS))

/* 0xD88 : BL_GAMMA_TABLE_35 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_35_OFFSET                     (0xD88)
#define DSP2_BLBACK_GAMMA_TABLE68_PRE                            DSP2_BLBACK_GAMMA_TABLE68_PRE
#define DSP2_BLBACK_GAMMA_TABLE68_PRE_POS                        (0U)
#define DSP2_BLBACK_GAMMA_TABLE68_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE68_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE68_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE68_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE68_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE68_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE68_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE69_PRE                            DSP2_BLBACK_GAMMA_TABLE69_PRE
#define DSP2_BLBACK_GAMMA_TABLE69_PRE_POS                        (16U)
#define DSP2_BLBACK_GAMMA_TABLE69_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE69_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE69_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE69_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE69_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE69_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE69_PRE_POS))

/* 0xD8C : BL_GAMMA_TABLE_36 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_36_OFFSET                     (0xD8C)
#define DSP2_BLBACK_GAMMA_TABLE70_PRE                            DSP2_BLBACK_GAMMA_TABLE70_PRE
#define DSP2_BLBACK_GAMMA_TABLE70_PRE_POS                        (0U)
#define DSP2_BLBACK_GAMMA_TABLE70_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE70_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE70_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE70_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE70_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE70_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE70_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE71_PRE                            DSP2_BLBACK_GAMMA_TABLE71_PRE
#define DSP2_BLBACK_GAMMA_TABLE71_PRE_POS                        (16U)
#define DSP2_BLBACK_GAMMA_TABLE71_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE71_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE71_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE71_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE71_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE71_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE71_PRE_POS))

/* 0xD90 : BL_GAMMA_TABLE_37 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_37_OFFSET                     (0xD90)
#define DSP2_BLBACK_GAMMA_TABLE72_PRE                            DSP2_BLBACK_GAMMA_TABLE72_PRE
#define DSP2_BLBACK_GAMMA_TABLE72_PRE_POS                        (0U)
#define DSP2_BLBACK_GAMMA_TABLE72_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE72_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE72_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE72_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE72_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE72_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE72_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE73_PRE                            DSP2_BLBACK_GAMMA_TABLE73_PRE
#define DSP2_BLBACK_GAMMA_TABLE73_PRE_POS                        (16U)
#define DSP2_BLBACK_GAMMA_TABLE73_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE73_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE73_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE73_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE73_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE73_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE73_PRE_POS))

/* 0xD94 : BL_GAMMA_TABLE_38 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_38_OFFSET                     (0xD94)
#define DSP2_BLBACK_GAMMA_TABLE74_PRE                            DSP2_BLBACK_GAMMA_TABLE74_PRE
#define DSP2_BLBACK_GAMMA_TABLE74_PRE_POS                        (0U)
#define DSP2_BLBACK_GAMMA_TABLE74_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE74_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE74_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE74_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE74_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE74_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE74_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE75_PRE                            DSP2_BLBACK_GAMMA_TABLE75_PRE
#define DSP2_BLBACK_GAMMA_TABLE75_PRE_POS                        (16U)
#define DSP2_BLBACK_GAMMA_TABLE75_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE75_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE75_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE75_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE75_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE75_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE75_PRE_POS))

/* 0xD98 : BL_GAMMA_TABLE_39 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_39_OFFSET                     (0xD98)
#define DSP2_BLBACK_GAMMA_TABLE76_PRE                            DSP2_BLBACK_GAMMA_TABLE76_PRE
#define DSP2_BLBACK_GAMMA_TABLE76_PRE_POS                        (0U)
#define DSP2_BLBACK_GAMMA_TABLE76_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE76_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE76_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE76_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE76_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE76_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE76_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE77_PRE                            DSP2_BLBACK_GAMMA_TABLE77_PRE
#define DSP2_BLBACK_GAMMA_TABLE77_PRE_POS                        (16U)
#define DSP2_BLBACK_GAMMA_TABLE77_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE77_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE77_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE77_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE77_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE77_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE77_PRE_POS))

/* 0xD9C : BL_GAMMA_TABLE_40 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_40_OFFSET                     (0xD9C)
#define DSP2_BLBACK_GAMMA_TABLE78_PRE                            DSP2_BLBACK_GAMMA_TABLE78_PRE
#define DSP2_BLBACK_GAMMA_TABLE78_PRE_POS                        (0U)
#define DSP2_BLBACK_GAMMA_TABLE78_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE78_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE78_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE78_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE78_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE78_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE78_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE79_PRE                            DSP2_BLBACK_GAMMA_TABLE79_PRE
#define DSP2_BLBACK_GAMMA_TABLE79_PRE_POS                        (16U)
#define DSP2_BLBACK_GAMMA_TABLE79_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE79_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE79_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE79_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE79_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE79_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE79_PRE_POS))

/* 0xDA0 : BL_GAMMA_TABLE_41 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_41_OFFSET                     (0xDA0)
#define DSP2_BLBACK_GAMMA_TABLE80_PRE                            DSP2_BLBACK_GAMMA_TABLE80_PRE
#define DSP2_BLBACK_GAMMA_TABLE80_PRE_POS                        (0U)
#define DSP2_BLBACK_GAMMA_TABLE80_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE80_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE80_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE80_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE80_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE80_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE80_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE81_PRE                            DSP2_BLBACK_GAMMA_TABLE81_PRE
#define DSP2_BLBACK_GAMMA_TABLE81_PRE_POS                        (16U)
#define DSP2_BLBACK_GAMMA_TABLE81_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE81_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE81_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE81_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE81_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE81_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE81_PRE_POS))

/* 0xDA4 : BL_GAMMA_TABLE_42 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_42_OFFSET                     (0xDA4)
#define DSP2_BLBACK_GAMMA_TABLE82_PRE                            DSP2_BLBACK_GAMMA_TABLE82_PRE
#define DSP2_BLBACK_GAMMA_TABLE82_PRE_POS                        (0U)
#define DSP2_BLBACK_GAMMA_TABLE82_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE82_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE82_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE82_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE82_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE82_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE82_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE83_PRE                            DSP2_BLBACK_GAMMA_TABLE83_PRE
#define DSP2_BLBACK_GAMMA_TABLE83_PRE_POS                        (16U)
#define DSP2_BLBACK_GAMMA_TABLE83_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE83_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE83_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE83_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE83_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE83_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE83_PRE_POS))

/* 0xDA8 : BL_GAMMA_TABLE_43 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_43_OFFSET                     (0xDA8)
#define DSP2_BLBACK_GAMMA_TABLE84_PRE                            DSP2_BLBACK_GAMMA_TABLE84_PRE
#define DSP2_BLBACK_GAMMA_TABLE84_PRE_POS                        (0U)
#define DSP2_BLBACK_GAMMA_TABLE84_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE84_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE84_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE84_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE84_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE84_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE84_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE85_PRE                            DSP2_BLBACK_GAMMA_TABLE85_PRE
#define DSP2_BLBACK_GAMMA_TABLE85_PRE_POS                        (16U)
#define DSP2_BLBACK_GAMMA_TABLE85_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE85_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE85_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE85_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE85_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE85_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE85_PRE_POS))

/* 0xDAC : BL_GAMMA_TABLE_44 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_44_OFFSET                     (0xDAC)
#define DSP2_BLBACK_GAMMA_TABLE86_PRE                            DSP2_BLBACK_GAMMA_TABLE86_PRE
#define DSP2_BLBACK_GAMMA_TABLE86_PRE_POS                        (0U)
#define DSP2_BLBACK_GAMMA_TABLE86_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE86_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE86_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE86_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE86_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE86_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE86_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE87_PRE                            DSP2_BLBACK_GAMMA_TABLE87_PRE
#define DSP2_BLBACK_GAMMA_TABLE87_PRE_POS                        (16U)
#define DSP2_BLBACK_GAMMA_TABLE87_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE87_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE87_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE87_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE87_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE87_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE87_PRE_POS))

/* 0xDB0 : BL_GAMMA_TABLE_45 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_45_OFFSET                     (0xDB0)
#define DSP2_BLBACK_GAMMA_TABLE88_PRE                            DSP2_BLBACK_GAMMA_TABLE88_PRE
#define DSP2_BLBACK_GAMMA_TABLE88_PRE_POS                        (0U)
#define DSP2_BLBACK_GAMMA_TABLE88_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE88_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE88_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE88_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE88_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE88_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE88_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE89_PRE                            DSP2_BLBACK_GAMMA_TABLE89_PRE
#define DSP2_BLBACK_GAMMA_TABLE89_PRE_POS                        (16U)
#define DSP2_BLBACK_GAMMA_TABLE89_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE89_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE89_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE89_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE89_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE89_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE89_PRE_POS))

/* 0xDB4 : BL_GAMMA_TABLE_46 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_46_OFFSET                     (0xDB4)
#define DSP2_BLBACK_GAMMA_TABLE90_PRE                            DSP2_BLBACK_GAMMA_TABLE90_PRE
#define DSP2_BLBACK_GAMMA_TABLE90_PRE_POS                        (0U)
#define DSP2_BLBACK_GAMMA_TABLE90_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE90_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE90_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE90_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE90_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE90_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE90_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE91_PRE                            DSP2_BLBACK_GAMMA_TABLE91_PRE
#define DSP2_BLBACK_GAMMA_TABLE91_PRE_POS                        (16U)
#define DSP2_BLBACK_GAMMA_TABLE91_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE91_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE91_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE91_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE91_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE91_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE91_PRE_POS))

/* 0xDB8 : BL_GAMMA_TABLE_47 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_47_OFFSET                     (0xDB8)
#define DSP2_BLBACK_GAMMA_TABLE92_PRE                            DSP2_BLBACK_GAMMA_TABLE92_PRE
#define DSP2_BLBACK_GAMMA_TABLE92_PRE_POS                        (0U)
#define DSP2_BLBACK_GAMMA_TABLE92_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE92_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE92_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE92_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE92_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE92_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE92_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE93_PRE                            DSP2_BLBACK_GAMMA_TABLE93_PRE
#define DSP2_BLBACK_GAMMA_TABLE93_PRE_POS                        (16U)
#define DSP2_BLBACK_GAMMA_TABLE93_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE93_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE93_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE93_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE93_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE93_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE93_PRE_POS))

/* 0xDBC : BL_GAMMA_TABLE_48 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_48_OFFSET                     (0xDBC)
#define DSP2_BLBACK_GAMMA_TABLE94_PRE                            DSP2_BLBACK_GAMMA_TABLE94_PRE
#define DSP2_BLBACK_GAMMA_TABLE94_PRE_POS                        (0U)
#define DSP2_BLBACK_GAMMA_TABLE94_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE94_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE94_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE94_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE94_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE94_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE94_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE95_PRE                            DSP2_BLBACK_GAMMA_TABLE95_PRE
#define DSP2_BLBACK_GAMMA_TABLE95_PRE_POS                        (16U)
#define DSP2_BLBACK_GAMMA_TABLE95_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE95_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE95_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE95_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE95_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE95_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE95_PRE_POS))

/* 0xDC0 : BL_GAMMA_TABLE_49 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_49_OFFSET                     (0xDC0)
#define DSP2_BLBACK_GAMMA_TABLE96_PRE                            DSP2_BLBACK_GAMMA_TABLE96_PRE
#define DSP2_BLBACK_GAMMA_TABLE96_PRE_POS                        (0U)
#define DSP2_BLBACK_GAMMA_TABLE96_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE96_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE96_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE96_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE96_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE96_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE96_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE97_PRE                            DSP2_BLBACK_GAMMA_TABLE97_PRE
#define DSP2_BLBACK_GAMMA_TABLE97_PRE_POS                        (16U)
#define DSP2_BLBACK_GAMMA_TABLE97_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE97_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE97_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE97_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE97_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE97_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE97_PRE_POS))

/* 0xDC4 : BL_GAMMA_TABLE_50 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_50_OFFSET                     (0xDC4)
#define DSP2_BLBACK_GAMMA_TABLE98_PRE                            DSP2_BLBACK_GAMMA_TABLE98_PRE
#define DSP2_BLBACK_GAMMA_TABLE98_PRE_POS                        (0U)
#define DSP2_BLBACK_GAMMA_TABLE98_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE98_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE98_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE98_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE98_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE98_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE98_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE99_PRE                            DSP2_BLBACK_GAMMA_TABLE99_PRE
#define DSP2_BLBACK_GAMMA_TABLE99_PRE_POS                        (16U)
#define DSP2_BLBACK_GAMMA_TABLE99_PRE_LEN                        (12U)
#define DSP2_BLBACK_GAMMA_TABLE99_PRE_MSK                        (((1U<<DSP2_BLBACK_GAMMA_TABLE99_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE99_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE99_PRE_UMSK                       (~(((1U<<DSP2_BLBACK_GAMMA_TABLE99_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE99_PRE_POS))

/* 0xDC8 : BL_GAMMA_TABLE_51 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_51_OFFSET                     (0xDC8)
#define DSP2_BLBACK_GAMMA_TABLE100_PRE                           DSP2_BLBACK_GAMMA_TABLE100_PRE
#define DSP2_BLBACK_GAMMA_TABLE100_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE100_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE100_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE100_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE100_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE100_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE100_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE100_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE101_PRE                           DSP2_BLBACK_GAMMA_TABLE101_PRE
#define DSP2_BLBACK_GAMMA_TABLE101_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE101_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE101_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE101_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE101_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE101_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE101_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE101_PRE_POS))

/* 0xDCC : BL_GAMMA_TABLE_52 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_52_OFFSET                     (0xDCC)
#define DSP2_BLBACK_GAMMA_TABLE102_PRE                           DSP2_BLBACK_GAMMA_TABLE102_PRE
#define DSP2_BLBACK_GAMMA_TABLE102_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE102_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE102_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE102_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE102_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE102_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE102_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE102_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE103_PRE                           DSP2_BLBACK_GAMMA_TABLE103_PRE
#define DSP2_BLBACK_GAMMA_TABLE103_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE103_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE103_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE103_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE103_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE103_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE103_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE103_PRE_POS))

/* 0xDD0 : BL_GAMMA_TABLE_53 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_53_OFFSET                     (0xDD0)
#define DSP2_BLBACK_GAMMA_TABLE104_PRE                           DSP2_BLBACK_GAMMA_TABLE104_PRE
#define DSP2_BLBACK_GAMMA_TABLE104_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE104_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE104_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE104_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE104_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE104_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE104_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE104_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE105_PRE                           DSP2_BLBACK_GAMMA_TABLE105_PRE
#define DSP2_BLBACK_GAMMA_TABLE105_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE105_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE105_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE105_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE105_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE105_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE105_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE105_PRE_POS))

/* 0xDD4 : BL_GAMMA_TABLE_54 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_54_OFFSET                     (0xDD4)
#define DSP2_BLBACK_GAMMA_TABLE106_PRE                           DSP2_BLBACK_GAMMA_TABLE106_PRE
#define DSP2_BLBACK_GAMMA_TABLE106_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE106_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE106_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE106_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE106_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE106_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE106_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE106_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE107_PRE                           DSP2_BLBACK_GAMMA_TABLE107_PRE
#define DSP2_BLBACK_GAMMA_TABLE107_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE107_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE107_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE107_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE107_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE107_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE107_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE107_PRE_POS))

/* 0xDD8 : BL_GAMMA_TABLE_55 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_55_OFFSET                     (0xDD8)
#define DSP2_BLBACK_GAMMA_TABLE108_PRE                           DSP2_BLBACK_GAMMA_TABLE108_PRE
#define DSP2_BLBACK_GAMMA_TABLE108_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE108_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE108_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE108_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE108_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE108_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE108_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE108_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE109_PRE                           DSP2_BLBACK_GAMMA_TABLE109_PRE
#define DSP2_BLBACK_GAMMA_TABLE109_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE109_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE109_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE109_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE109_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE109_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE109_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE109_PRE_POS))

/* 0xDDC : BL_GAMMA_TABLE_56 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_56_OFFSET                     (0xDDC)
#define DSP2_BLBACK_GAMMA_TABLE110_PRE                           DSP2_BLBACK_GAMMA_TABLE110_PRE
#define DSP2_BLBACK_GAMMA_TABLE110_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE110_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE110_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE110_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE110_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE110_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE110_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE110_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE111_PRE                           DSP2_BLBACK_GAMMA_TABLE111_PRE
#define DSP2_BLBACK_GAMMA_TABLE111_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE111_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE111_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE111_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE111_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE111_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE111_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE111_PRE_POS))

/* 0xDE0 : BL_GAMMA_TABLE_57 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_57_OFFSET                     (0xDE0)
#define DSP2_BLBACK_GAMMA_TABLE112_PRE                           DSP2_BLBACK_GAMMA_TABLE112_PRE
#define DSP2_BLBACK_GAMMA_TABLE112_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE112_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE112_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE112_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE112_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE112_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE112_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE112_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE113_PRE                           DSP2_BLBACK_GAMMA_TABLE113_PRE
#define DSP2_BLBACK_GAMMA_TABLE113_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE113_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE113_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE113_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE113_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE113_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE113_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE113_PRE_POS))

/* 0xDE4 : BL_GAMMA_TABLE_58 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_58_OFFSET                     (0xDE4)
#define DSP2_BLBACK_GAMMA_TABLE114_PRE                           DSP2_BLBACK_GAMMA_TABLE114_PRE
#define DSP2_BLBACK_GAMMA_TABLE114_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE114_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE114_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE114_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE114_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE114_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE114_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE114_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE115_PRE                           DSP2_BLBACK_GAMMA_TABLE115_PRE
#define DSP2_BLBACK_GAMMA_TABLE115_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE115_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE115_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE115_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE115_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE115_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE115_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE115_PRE_POS))

/* 0xDE8 : BL_GAMMA_TABLE_59 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_59_OFFSET                     (0xDE8)
#define DSP2_BLBACK_GAMMA_TABLE116_PRE                           DSP2_BLBACK_GAMMA_TABLE116_PRE
#define DSP2_BLBACK_GAMMA_TABLE116_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE116_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE116_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE116_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE116_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE116_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE116_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE116_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE117_PRE                           DSP2_BLBACK_GAMMA_TABLE117_PRE
#define DSP2_BLBACK_GAMMA_TABLE117_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE117_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE117_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE117_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE117_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE117_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE117_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE117_PRE_POS))

/* 0xDEC : BL_GAMMA_TABLE_60 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_60_OFFSET                     (0xDEC)
#define DSP2_BLBACK_GAMMA_TABLE118_PRE                           DSP2_BLBACK_GAMMA_TABLE118_PRE
#define DSP2_BLBACK_GAMMA_TABLE118_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE118_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE118_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE118_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE118_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE118_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE118_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE118_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE119_PRE                           DSP2_BLBACK_GAMMA_TABLE119_PRE
#define DSP2_BLBACK_GAMMA_TABLE119_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE119_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE119_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE119_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE119_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE119_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE119_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE119_PRE_POS))

/* 0xDF0 : BL_GAMMA_TABLE_61 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_61_OFFSET                     (0xDF0)
#define DSP2_BLBACK_GAMMA_TABLE120_PRE                           DSP2_BLBACK_GAMMA_TABLE120_PRE
#define DSP2_BLBACK_GAMMA_TABLE120_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE120_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE120_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE120_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE120_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE120_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE120_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE120_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE121_PRE                           DSP2_BLBACK_GAMMA_TABLE121_PRE
#define DSP2_BLBACK_GAMMA_TABLE121_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE121_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE121_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE121_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE121_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE121_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE121_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE121_PRE_POS))

/* 0xDF4 : BL_GAMMA_TABLE_62 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_62_OFFSET                     (0xDF4)
#define DSP2_BLBACK_GAMMA_TABLE122_PRE                           DSP2_BLBACK_GAMMA_TABLE122_PRE
#define DSP2_BLBACK_GAMMA_TABLE122_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE122_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE122_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE122_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE122_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE122_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE122_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE122_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE123_PRE                           DSP2_BLBACK_GAMMA_TABLE123_PRE
#define DSP2_BLBACK_GAMMA_TABLE123_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE123_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE123_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE123_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE123_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE123_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE123_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE123_PRE_POS))

/* 0xDF8 : BL_GAMMA_TABLE_63 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_63_OFFSET                     (0xDF8)
#define DSP2_BLBACK_GAMMA_TABLE124_PRE                           DSP2_BLBACK_GAMMA_TABLE124_PRE
#define DSP2_BLBACK_GAMMA_TABLE124_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE124_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE124_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE124_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE124_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE124_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE124_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE124_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE125_PRE                           DSP2_BLBACK_GAMMA_TABLE125_PRE
#define DSP2_BLBACK_GAMMA_TABLE125_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE125_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE125_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE125_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE125_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE125_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE125_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE125_PRE_POS))

/* 0xDFC : BL_GAMMA_TABLE_64 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_64_OFFSET                     (0xDFC)
#define DSP2_BLBACK_GAMMA_TABLE126_PRE                           DSP2_BLBACK_GAMMA_TABLE126_PRE
#define DSP2_BLBACK_GAMMA_TABLE126_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE126_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE126_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE126_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE126_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE126_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE126_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE126_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE127_PRE                           DSP2_BLBACK_GAMMA_TABLE127_PRE
#define DSP2_BLBACK_GAMMA_TABLE127_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE127_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE127_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE127_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE127_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE127_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE127_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE127_PRE_POS))

/* 0xE00 : BL_GAMMA_TABLE_65 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_65_OFFSET                     (0xE00)
#define DSP2_BLBACK_GAMMA_TABLE128_PRE                           DSP2_BLBACK_GAMMA_TABLE128_PRE
#define DSP2_BLBACK_GAMMA_TABLE128_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE128_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE128_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE128_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE128_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE128_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE128_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE128_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE129_PRE                           DSP2_BLBACK_GAMMA_TABLE129_PRE
#define DSP2_BLBACK_GAMMA_TABLE129_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE129_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE129_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE129_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE129_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE129_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE129_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE129_PRE_POS))

/* 0xE04 : BL_GAMMA_TABLE_66 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_66_OFFSET                     (0xE04)
#define DSP2_BLBACK_GAMMA_TABLE130_PRE                           DSP2_BLBACK_GAMMA_TABLE130_PRE
#define DSP2_BLBACK_GAMMA_TABLE130_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE130_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE130_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE130_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE130_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE130_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE130_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE130_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE131_PRE                           DSP2_BLBACK_GAMMA_TABLE131_PRE
#define DSP2_BLBACK_GAMMA_TABLE131_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE131_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE131_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE131_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE131_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE131_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE131_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE131_PRE_POS))

/* 0xE08 : BL_GAMMA_TABLE_67 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_67_OFFSET                     (0xE08)
#define DSP2_BLBACK_GAMMA_TABLE132_PRE                           DSP2_BLBACK_GAMMA_TABLE132_PRE
#define DSP2_BLBACK_GAMMA_TABLE132_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE132_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE132_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE132_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE132_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE132_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE132_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE132_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE133_PRE                           DSP2_BLBACK_GAMMA_TABLE133_PRE
#define DSP2_BLBACK_GAMMA_TABLE133_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE133_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE133_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE133_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE133_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE133_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE133_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE133_PRE_POS))

/* 0xE0C : BL_GAMMA_TABLE_68 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_68_OFFSET                     (0xE0C)
#define DSP2_BLBACK_GAMMA_TABLE134_PRE                           DSP2_BLBACK_GAMMA_TABLE134_PRE
#define DSP2_BLBACK_GAMMA_TABLE134_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE134_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE134_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE134_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE134_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE134_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE134_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE134_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE135_PRE                           DSP2_BLBACK_GAMMA_TABLE135_PRE
#define DSP2_BLBACK_GAMMA_TABLE135_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE135_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE135_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE135_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE135_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE135_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE135_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE135_PRE_POS))

/* 0xE10 : BL_GAMMA_TABLE_69 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_69_OFFSET                     (0xE10)
#define DSP2_BLBACK_GAMMA_TABLE136_PRE                           DSP2_BLBACK_GAMMA_TABLE136_PRE
#define DSP2_BLBACK_GAMMA_TABLE136_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE136_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE136_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE136_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE136_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE136_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE136_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE136_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE137_PRE                           DSP2_BLBACK_GAMMA_TABLE137_PRE
#define DSP2_BLBACK_GAMMA_TABLE137_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE137_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE137_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE137_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE137_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE137_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE137_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE137_PRE_POS))

/* 0xE14 : BL_GAMMA_TABLE_70 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_70_OFFSET                     (0xE14)
#define DSP2_BLBACK_GAMMA_TABLE138_PRE                           DSP2_BLBACK_GAMMA_TABLE138_PRE
#define DSP2_BLBACK_GAMMA_TABLE138_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE138_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE138_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE138_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE138_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE138_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE138_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE138_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE139_PRE                           DSP2_BLBACK_GAMMA_TABLE139_PRE
#define DSP2_BLBACK_GAMMA_TABLE139_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE139_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE139_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE139_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE139_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE139_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE139_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE139_PRE_POS))

/* 0xE18 : BL_GAMMA_TABLE_71 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_71_OFFSET                     (0xE18)
#define DSP2_BLBACK_GAMMA_TABLE140_PRE                           DSP2_BLBACK_GAMMA_TABLE140_PRE
#define DSP2_BLBACK_GAMMA_TABLE140_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE140_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE140_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE140_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE140_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE140_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE140_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE140_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE141_PRE                           DSP2_BLBACK_GAMMA_TABLE141_PRE
#define DSP2_BLBACK_GAMMA_TABLE141_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE141_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE141_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE141_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE141_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE141_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE141_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE141_PRE_POS))

/* 0xE1C : BL_GAMMA_TABLE_72 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_72_OFFSET                     (0xE1C)
#define DSP2_BLBACK_GAMMA_TABLE142_PRE                           DSP2_BLBACK_GAMMA_TABLE142_PRE
#define DSP2_BLBACK_GAMMA_TABLE142_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE142_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE142_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE142_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE142_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE142_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE142_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE142_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE143_PRE                           DSP2_BLBACK_GAMMA_TABLE143_PRE
#define DSP2_BLBACK_GAMMA_TABLE143_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE143_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE143_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE143_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE143_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE143_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE143_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE143_PRE_POS))

/* 0xE20 : BL_GAMMA_TABLE_73 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_73_OFFSET                     (0xE20)
#define DSP2_BLBACK_GAMMA_TABLE144_PRE                           DSP2_BLBACK_GAMMA_TABLE144_PRE
#define DSP2_BLBACK_GAMMA_TABLE144_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE144_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE144_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE144_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE144_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE144_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE144_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE144_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE145_PRE                           DSP2_BLBACK_GAMMA_TABLE145_PRE
#define DSP2_BLBACK_GAMMA_TABLE145_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE145_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE145_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE145_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE145_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE145_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE145_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE145_PRE_POS))

/* 0xE24 : BL_GAMMA_TABLE_74 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_74_OFFSET                     (0xE24)
#define DSP2_BLBACK_GAMMA_TABLE146_PRE                           DSP2_BLBACK_GAMMA_TABLE146_PRE
#define DSP2_BLBACK_GAMMA_TABLE146_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE146_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE146_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE146_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE146_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE146_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE146_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE146_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE147_PRE                           DSP2_BLBACK_GAMMA_TABLE147_PRE
#define DSP2_BLBACK_GAMMA_TABLE147_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE147_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE147_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE147_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE147_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE147_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE147_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE147_PRE_POS))

/* 0xE28 : BL_GAMMA_TABLE_75 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_75_OFFSET                     (0xE28)
#define DSP2_BLBACK_GAMMA_TABLE148_PRE                           DSP2_BLBACK_GAMMA_TABLE148_PRE
#define DSP2_BLBACK_GAMMA_TABLE148_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE148_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE148_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE148_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE148_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE148_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE148_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE148_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE149_PRE                           DSP2_BLBACK_GAMMA_TABLE149_PRE
#define DSP2_BLBACK_GAMMA_TABLE149_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE149_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE149_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE149_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE149_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE149_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE149_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE149_PRE_POS))

/* 0xE2C : BL_GAMMA_TABLE_76 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_76_OFFSET                     (0xE2C)
#define DSP2_BLBACK_GAMMA_TABLE150_PRE                           DSP2_BLBACK_GAMMA_TABLE150_PRE
#define DSP2_BLBACK_GAMMA_TABLE150_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE150_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE150_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE150_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE150_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE150_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE150_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE150_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE151_PRE                           DSP2_BLBACK_GAMMA_TABLE151_PRE
#define DSP2_BLBACK_GAMMA_TABLE151_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE151_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE151_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE151_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE151_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE151_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE151_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE151_PRE_POS))

/* 0xE30 : BL_GAMMA_TABLE_77 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_77_OFFSET                     (0xE30)
#define DSP2_BLBACK_GAMMA_TABLE152_PRE                           DSP2_BLBACK_GAMMA_TABLE152_PRE
#define DSP2_BLBACK_GAMMA_TABLE152_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE152_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE152_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE152_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE152_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE152_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE152_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE152_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE153_PRE                           DSP2_BLBACK_GAMMA_TABLE153_PRE
#define DSP2_BLBACK_GAMMA_TABLE153_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE153_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE153_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE153_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE153_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE153_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE153_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE153_PRE_POS))

/* 0xE34 : BL_GAMMA_TABLE_78 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_78_OFFSET                     (0xE34)
#define DSP2_BLBACK_GAMMA_TABLE154_PRE                           DSP2_BLBACK_GAMMA_TABLE154_PRE
#define DSP2_BLBACK_GAMMA_TABLE154_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE154_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE154_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE154_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE154_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE154_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE154_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE154_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE155_PRE                           DSP2_BLBACK_GAMMA_TABLE155_PRE
#define DSP2_BLBACK_GAMMA_TABLE155_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE155_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE155_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE155_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE155_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE155_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE155_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE155_PRE_POS))

/* 0xE38 : BL_GAMMA_TABLE_79 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_79_OFFSET                     (0xE38)
#define DSP2_BLBACK_GAMMA_TABLE156_PRE                           DSP2_BLBACK_GAMMA_TABLE156_PRE
#define DSP2_BLBACK_GAMMA_TABLE156_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE156_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE156_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE156_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE156_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE156_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE156_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE156_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE157_PRE                           DSP2_BLBACK_GAMMA_TABLE157_PRE
#define DSP2_BLBACK_GAMMA_TABLE157_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE157_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE157_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE157_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE157_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE157_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE157_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE157_PRE_POS))

/* 0xE3C : BL_GAMMA_TABLE_80 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_80_OFFSET                     (0xE3C)
#define DSP2_BLBACK_GAMMA_TABLE158_PRE                           DSP2_BLBACK_GAMMA_TABLE158_PRE
#define DSP2_BLBACK_GAMMA_TABLE158_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE158_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE158_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE158_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE158_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE158_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE158_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE158_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE159_PRE                           DSP2_BLBACK_GAMMA_TABLE159_PRE
#define DSP2_BLBACK_GAMMA_TABLE159_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE159_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE159_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE159_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE159_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE159_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE159_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE159_PRE_POS))

/* 0xE40 : BL_GAMMA_TABLE_81 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_81_OFFSET                     (0xE40)
#define DSP2_BLBACK_GAMMA_TABLE160_PRE                           DSP2_BLBACK_GAMMA_TABLE160_PRE
#define DSP2_BLBACK_GAMMA_TABLE160_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE160_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE160_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE160_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE160_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE160_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE160_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE160_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE161_PRE                           DSP2_BLBACK_GAMMA_TABLE161_PRE
#define DSP2_BLBACK_GAMMA_TABLE161_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE161_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE161_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE161_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE161_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE161_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE161_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE161_PRE_POS))

/* 0xE44 : BL_GAMMA_TABLE_82 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_82_OFFSET                     (0xE44)
#define DSP2_BLBACK_GAMMA_TABLE162_PRE                           DSP2_BLBACK_GAMMA_TABLE162_PRE
#define DSP2_BLBACK_GAMMA_TABLE162_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE162_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE162_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE162_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE162_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE162_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE162_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE162_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE163_PRE                           DSP2_BLBACK_GAMMA_TABLE163_PRE
#define DSP2_BLBACK_GAMMA_TABLE163_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE163_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE163_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE163_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE163_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE163_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE163_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE163_PRE_POS))

/* 0xE48 : BL_GAMMA_TABLE_83 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_83_OFFSET                     (0xE48)
#define DSP2_BLBACK_GAMMA_TABLE164_PRE                           DSP2_BLBACK_GAMMA_TABLE164_PRE
#define DSP2_BLBACK_GAMMA_TABLE164_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE164_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE164_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE164_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE164_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE164_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE164_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE164_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE165_PRE                           DSP2_BLBACK_GAMMA_TABLE165_PRE
#define DSP2_BLBACK_GAMMA_TABLE165_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE165_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE165_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE165_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE165_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE165_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE165_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE165_PRE_POS))

/* 0xE4C : BL_GAMMA_TABLE_84 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_84_OFFSET                     (0xE4C)
#define DSP2_BLBACK_GAMMA_TABLE166_PRE                           DSP2_BLBACK_GAMMA_TABLE166_PRE
#define DSP2_BLBACK_GAMMA_TABLE166_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE166_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE166_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE166_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE166_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE166_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE166_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE166_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE167_PRE                           DSP2_BLBACK_GAMMA_TABLE167_PRE
#define DSP2_BLBACK_GAMMA_TABLE167_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE167_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE167_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE167_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE167_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE167_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE167_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE167_PRE_POS))

/* 0xE50 : BL_GAMMA_TABLE_85 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_85_OFFSET                     (0xE50)
#define DSP2_BLBACK_GAMMA_TABLE168_PRE                           DSP2_BLBACK_GAMMA_TABLE168_PRE
#define DSP2_BLBACK_GAMMA_TABLE168_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE168_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE168_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE168_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE168_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE168_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE168_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE168_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE169_PRE                           DSP2_BLBACK_GAMMA_TABLE169_PRE
#define DSP2_BLBACK_GAMMA_TABLE169_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE169_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE169_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE169_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE169_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE169_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE169_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE169_PRE_POS))

/* 0xE54 : BL_GAMMA_TABLE_86 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_86_OFFSET                     (0xE54)
#define DSP2_BLBACK_GAMMA_TABLE170_PRE                           DSP2_BLBACK_GAMMA_TABLE170_PRE
#define DSP2_BLBACK_GAMMA_TABLE170_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE170_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE170_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE170_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE170_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE170_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE170_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE170_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE171_PRE                           DSP2_BLBACK_GAMMA_TABLE171_PRE
#define DSP2_BLBACK_GAMMA_TABLE171_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE171_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE171_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE171_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE171_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE171_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE171_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE171_PRE_POS))

/* 0xE58 : BL_GAMMA_TABLE_87 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_87_OFFSET                     (0xE58)
#define DSP2_BLBACK_GAMMA_TABLE172_PRE                           DSP2_BLBACK_GAMMA_TABLE172_PRE
#define DSP2_BLBACK_GAMMA_TABLE172_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE172_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE172_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE172_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE172_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE172_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE172_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE172_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE173_PRE                           DSP2_BLBACK_GAMMA_TABLE173_PRE
#define DSP2_BLBACK_GAMMA_TABLE173_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE173_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE173_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE173_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE173_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE173_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE173_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE173_PRE_POS))

/* 0xE5C : BL_GAMMA_TABLE_88 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_88_OFFSET                     (0xE5C)
#define DSP2_BLBACK_GAMMA_TABLE174_PRE                           DSP2_BLBACK_GAMMA_TABLE174_PRE
#define DSP2_BLBACK_GAMMA_TABLE174_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE174_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE174_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE174_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE174_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE174_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE174_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE174_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE175_PRE                           DSP2_BLBACK_GAMMA_TABLE175_PRE
#define DSP2_BLBACK_GAMMA_TABLE175_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE175_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE175_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE175_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE175_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE175_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE175_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE175_PRE_POS))

/* 0xE60 : BL_GAMMA_TABLE_89 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_89_OFFSET                     (0xE60)
#define DSP2_BLBACK_GAMMA_TABLE176_PRE                           DSP2_BLBACK_GAMMA_TABLE176_PRE
#define DSP2_BLBACK_GAMMA_TABLE176_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE176_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE176_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE176_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE176_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE176_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE176_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE176_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE177_PRE                           DSP2_BLBACK_GAMMA_TABLE177_PRE
#define DSP2_BLBACK_GAMMA_TABLE177_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE177_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE177_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE177_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE177_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE177_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE177_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE177_PRE_POS))

/* 0xE64 : BL_GAMMA_TABLE_90 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_90_OFFSET                     (0xE64)
#define DSP2_BLBACK_GAMMA_TABLE178_PRE                           DSP2_BLBACK_GAMMA_TABLE178_PRE
#define DSP2_BLBACK_GAMMA_TABLE178_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE178_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE178_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE178_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE178_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE178_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE178_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE178_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE179_PRE                           DSP2_BLBACK_GAMMA_TABLE179_PRE
#define DSP2_BLBACK_GAMMA_TABLE179_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE179_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE179_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE179_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE179_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE179_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE179_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE179_PRE_POS))

/* 0xE68 : BL_GAMMA_TABLE_91 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_91_OFFSET                     (0xE68)
#define DSP2_BLBACK_GAMMA_TABLE180_PRE                           DSP2_BLBACK_GAMMA_TABLE180_PRE
#define DSP2_BLBACK_GAMMA_TABLE180_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE180_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE180_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE180_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE180_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE180_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE180_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE180_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE181_PRE                           DSP2_BLBACK_GAMMA_TABLE181_PRE
#define DSP2_BLBACK_GAMMA_TABLE181_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE181_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE181_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE181_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE181_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE181_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE181_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE181_PRE_POS))

/* 0xE6C : BL_GAMMA_TABLE_92 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_92_OFFSET                     (0xE6C)
#define DSP2_BLBACK_GAMMA_TABLE182_PRE                           DSP2_BLBACK_GAMMA_TABLE182_PRE
#define DSP2_BLBACK_GAMMA_TABLE182_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE182_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE182_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE182_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE182_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE182_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE182_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE182_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE183_PRE                           DSP2_BLBACK_GAMMA_TABLE183_PRE
#define DSP2_BLBACK_GAMMA_TABLE183_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE183_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE183_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE183_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE183_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE183_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE183_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE183_PRE_POS))

/* 0xE70 : BL_GAMMA_TABLE_93 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_93_OFFSET                     (0xE70)
#define DSP2_BLBACK_GAMMA_TABLE184_PRE                           DSP2_BLBACK_GAMMA_TABLE184_PRE
#define DSP2_BLBACK_GAMMA_TABLE184_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE184_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE184_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE184_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE184_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE184_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE184_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE184_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE185_PRE                           DSP2_BLBACK_GAMMA_TABLE185_PRE
#define DSP2_BLBACK_GAMMA_TABLE185_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE185_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE185_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE185_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE185_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE185_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE185_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE185_PRE_POS))

/* 0xE74 : BL_GAMMA_TABLE_94 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_94_OFFSET                     (0xE74)
#define DSP2_BLBACK_GAMMA_TABLE186_PRE                           DSP2_BLBACK_GAMMA_TABLE186_PRE
#define DSP2_BLBACK_GAMMA_TABLE186_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE186_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE186_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE186_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE186_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE186_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE186_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE186_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE187_PRE                           DSP2_BLBACK_GAMMA_TABLE187_PRE
#define DSP2_BLBACK_GAMMA_TABLE187_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE187_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE187_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE187_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE187_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE187_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE187_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE187_PRE_POS))

/* 0xE78 : BL_GAMMA_TABLE_95 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_95_OFFSET                     (0xE78)
#define DSP2_BLBACK_GAMMA_TABLE188_PRE                           DSP2_BLBACK_GAMMA_TABLE188_PRE
#define DSP2_BLBACK_GAMMA_TABLE188_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE188_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE188_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE188_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE188_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE188_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE188_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE188_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE189_PRE                           DSP2_BLBACK_GAMMA_TABLE189_PRE
#define DSP2_BLBACK_GAMMA_TABLE189_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE189_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE189_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE189_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE189_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE189_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE189_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE189_PRE_POS))

/* 0xE7C : BL_GAMMA_TABLE_96 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_96_OFFSET                     (0xE7C)
#define DSP2_BLBACK_GAMMA_TABLE190_PRE                           DSP2_BLBACK_GAMMA_TABLE190_PRE
#define DSP2_BLBACK_GAMMA_TABLE190_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE190_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE190_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE190_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE190_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE190_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE190_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE190_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE191_PRE                           DSP2_BLBACK_GAMMA_TABLE191_PRE
#define DSP2_BLBACK_GAMMA_TABLE191_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE191_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE191_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE191_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE191_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE191_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE191_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE191_PRE_POS))

/* 0xE80 : BL_GAMMA_TABLE_97 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_97_OFFSET                     (0xE80)
#define DSP2_BLBACK_GAMMA_TABLE192_PRE                           DSP2_BLBACK_GAMMA_TABLE192_PRE
#define DSP2_BLBACK_GAMMA_TABLE192_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE192_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE192_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE192_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE192_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE192_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE192_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE192_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE193_PRE                           DSP2_BLBACK_GAMMA_TABLE193_PRE
#define DSP2_BLBACK_GAMMA_TABLE193_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE193_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE193_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE193_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE193_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE193_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE193_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE193_PRE_POS))

/* 0xE84 : BL_GAMMA_TABLE_98 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_98_OFFSET                     (0xE84)
#define DSP2_BLBACK_GAMMA_TABLE194_PRE                           DSP2_BLBACK_GAMMA_TABLE194_PRE
#define DSP2_BLBACK_GAMMA_TABLE194_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE194_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE194_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE194_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE194_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE194_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE194_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE194_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE195_PRE                           DSP2_BLBACK_GAMMA_TABLE195_PRE
#define DSP2_BLBACK_GAMMA_TABLE195_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE195_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE195_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE195_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE195_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE195_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE195_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE195_PRE_POS))

/* 0xE88 : BL_GAMMA_TABLE_99 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_99_OFFSET                     (0xE88)
#define DSP2_BLBACK_GAMMA_TABLE196_PRE                           DSP2_BLBACK_GAMMA_TABLE196_PRE
#define DSP2_BLBACK_GAMMA_TABLE196_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE196_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE196_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE196_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE196_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE196_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE196_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE196_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE197_PRE                           DSP2_BLBACK_GAMMA_TABLE197_PRE
#define DSP2_BLBACK_GAMMA_TABLE197_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE197_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE197_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE197_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE197_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE197_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE197_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE197_PRE_POS))

/* 0xE8C : BL_GAMMA_TABLE_100 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_100_OFFSET                    (0xE8C)
#define DSP2_BLBACK_GAMMA_TABLE198_PRE                           DSP2_BLBACK_GAMMA_TABLE198_PRE
#define DSP2_BLBACK_GAMMA_TABLE198_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE198_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE198_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE198_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE198_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE198_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE198_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE198_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE199_PRE                           DSP2_BLBACK_GAMMA_TABLE199_PRE
#define DSP2_BLBACK_GAMMA_TABLE199_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE199_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE199_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE199_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE199_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE199_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE199_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE199_PRE_POS))

/* 0xE90 : BL_GAMMA_TABLE_101 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_101_OFFSET                    (0xE90)
#define DSP2_BLBACK_GAMMA_TABLE200_PRE                           DSP2_BLBACK_GAMMA_TABLE200_PRE
#define DSP2_BLBACK_GAMMA_TABLE200_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE200_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE200_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE200_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE200_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE200_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE200_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE200_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE201_PRE                           DSP2_BLBACK_GAMMA_TABLE201_PRE
#define DSP2_BLBACK_GAMMA_TABLE201_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE201_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE201_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE201_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE201_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE201_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE201_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE201_PRE_POS))

/* 0xE94 : BL_GAMMA_TABLE_102 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_102_OFFSET                    (0xE94)
#define DSP2_BLBACK_GAMMA_TABLE202_PRE                           DSP2_BLBACK_GAMMA_TABLE202_PRE
#define DSP2_BLBACK_GAMMA_TABLE202_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE202_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE202_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE202_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE202_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE202_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE202_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE202_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE203_PRE                           DSP2_BLBACK_GAMMA_TABLE203_PRE
#define DSP2_BLBACK_GAMMA_TABLE203_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE203_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE203_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE203_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE203_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE203_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE203_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE203_PRE_POS))

/* 0xE98 : BL_GAMMA_TABLE_103 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_103_OFFSET                    (0xE98)
#define DSP2_BLBACK_GAMMA_TABLE204_PRE                           DSP2_BLBACK_GAMMA_TABLE204_PRE
#define DSP2_BLBACK_GAMMA_TABLE204_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE204_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE204_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE204_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE204_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE204_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE204_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE204_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE205_PRE                           DSP2_BLBACK_GAMMA_TABLE205_PRE
#define DSP2_BLBACK_GAMMA_TABLE205_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE205_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE205_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE205_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE205_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE205_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE205_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE205_PRE_POS))

/* 0xE9C : BL_GAMMA_TABLE_104 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_104_OFFSET                    (0xE9C)
#define DSP2_BLBACK_GAMMA_TABLE206_PRE                           DSP2_BLBACK_GAMMA_TABLE206_PRE
#define DSP2_BLBACK_GAMMA_TABLE206_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE206_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE206_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE206_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE206_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE206_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE206_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE206_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE207_PRE                           DSP2_BLBACK_GAMMA_TABLE207_PRE
#define DSP2_BLBACK_GAMMA_TABLE207_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE207_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE207_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE207_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE207_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE207_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE207_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE207_PRE_POS))

/* 0xEA0 : BL_GAMMA_TABLE_105 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_105_OFFSET                    (0xEA0)
#define DSP2_BLBACK_GAMMA_TABLE208_PRE                           DSP2_BLBACK_GAMMA_TABLE208_PRE
#define DSP2_BLBACK_GAMMA_TABLE208_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE208_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE208_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE208_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE208_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE208_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE208_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE208_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE209_PRE                           DSP2_BLBACK_GAMMA_TABLE209_PRE
#define DSP2_BLBACK_GAMMA_TABLE209_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE209_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE209_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE209_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE209_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE209_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE209_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE209_PRE_POS))

/* 0xEA4 : BL_GAMMA_TABLE_106 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_106_OFFSET                    (0xEA4)
#define DSP2_BLBACK_GAMMA_TABLE210_PRE                           DSP2_BLBACK_GAMMA_TABLE210_PRE
#define DSP2_BLBACK_GAMMA_TABLE210_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE210_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE210_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE210_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE210_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE210_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE210_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE210_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE211_PRE                           DSP2_BLBACK_GAMMA_TABLE211_PRE
#define DSP2_BLBACK_GAMMA_TABLE211_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE211_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE211_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE211_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE211_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE211_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE211_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE211_PRE_POS))

/* 0xEA8 : BL_GAMMA_TABLE_107 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_107_OFFSET                    (0xEA8)
#define DSP2_BLBACK_GAMMA_TABLE212_PRE                           DSP2_BLBACK_GAMMA_TABLE212_PRE
#define DSP2_BLBACK_GAMMA_TABLE212_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE212_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE212_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE212_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE212_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE212_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE212_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE212_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE213_PRE                           DSP2_BLBACK_GAMMA_TABLE213_PRE
#define DSP2_BLBACK_GAMMA_TABLE213_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE213_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE213_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE213_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE213_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE213_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE213_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE213_PRE_POS))

/* 0xEAC : BL_GAMMA_TABLE_108 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_108_OFFSET                    (0xEAC)
#define DSP2_BLBACK_GAMMA_TABLE214_PRE                           DSP2_BLBACK_GAMMA_TABLE214_PRE
#define DSP2_BLBACK_GAMMA_TABLE214_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE214_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE214_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE214_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE214_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE214_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE214_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE214_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE215_PRE                           DSP2_BLBACK_GAMMA_TABLE215_PRE
#define DSP2_BLBACK_GAMMA_TABLE215_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE215_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE215_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE215_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE215_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE215_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE215_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE215_PRE_POS))

/* 0xEB0 : BL_GAMMA_TABLE_109 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_109_OFFSET                    (0xEB0)
#define DSP2_BLBACK_GAMMA_TABLE216_PRE                           DSP2_BLBACK_GAMMA_TABLE216_PRE
#define DSP2_BLBACK_GAMMA_TABLE216_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE216_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE216_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE216_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE216_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE216_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE216_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE216_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE217_PRE                           DSP2_BLBACK_GAMMA_TABLE217_PRE
#define DSP2_BLBACK_GAMMA_TABLE217_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE217_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE217_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE217_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE217_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE217_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE217_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE217_PRE_POS))

/* 0xEB4 : BL_GAMMA_TABLE_110 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_110_OFFSET                    (0xEB4)
#define DSP2_BLBACK_GAMMA_TABLE218_PRE                           DSP2_BLBACK_GAMMA_TABLE218_PRE
#define DSP2_BLBACK_GAMMA_TABLE218_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE218_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE218_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE218_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE218_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE218_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE218_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE218_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE219_PRE                           DSP2_BLBACK_GAMMA_TABLE219_PRE
#define DSP2_BLBACK_GAMMA_TABLE219_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE219_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE219_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE219_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE219_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE219_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE219_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE219_PRE_POS))

/* 0xEB8 : BL_GAMMA_TABLE_111 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_111_OFFSET                    (0xEB8)
#define DSP2_BLBACK_GAMMA_TABLE220_PRE                           DSP2_BLBACK_GAMMA_TABLE220_PRE
#define DSP2_BLBACK_GAMMA_TABLE220_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE220_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE220_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE220_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE220_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE220_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE220_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE220_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE221_PRE                           DSP2_BLBACK_GAMMA_TABLE221_PRE
#define DSP2_BLBACK_GAMMA_TABLE221_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE221_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE221_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE221_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE221_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE221_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE221_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE221_PRE_POS))

/* 0xEBC : BL_GAMMA_TABLE_112 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_112_OFFSET                    (0xEBC)
#define DSP2_BLBACK_GAMMA_TABLE222_PRE                           DSP2_BLBACK_GAMMA_TABLE222_PRE
#define DSP2_BLBACK_GAMMA_TABLE222_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE222_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE222_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE222_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE222_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE222_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE222_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE222_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE223_PRE                           DSP2_BLBACK_GAMMA_TABLE223_PRE
#define DSP2_BLBACK_GAMMA_TABLE223_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE223_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE223_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE223_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE223_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE223_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE223_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE223_PRE_POS))

/* 0xEC0 : BL_GAMMA_TABLE_113 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_113_OFFSET                    (0xEC0)
#define DSP2_BLBACK_GAMMA_TABLE224_PRE                           DSP2_BLBACK_GAMMA_TABLE224_PRE
#define DSP2_BLBACK_GAMMA_TABLE224_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE224_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE224_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE224_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE224_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE224_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE224_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE224_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE225_PRE                           DSP2_BLBACK_GAMMA_TABLE225_PRE
#define DSP2_BLBACK_GAMMA_TABLE225_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE225_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE225_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE225_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE225_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE225_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE225_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE225_PRE_POS))

/* 0xEC4 : BL_GAMMA_TABLE_114 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_114_OFFSET                    (0xEC4)
#define DSP2_BLBACK_GAMMA_TABLE226_PRE                           DSP2_BLBACK_GAMMA_TABLE226_PRE
#define DSP2_BLBACK_GAMMA_TABLE226_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE226_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE226_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE226_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE226_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE226_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE226_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE226_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE227_PRE                           DSP2_BLBACK_GAMMA_TABLE227_PRE
#define DSP2_BLBACK_GAMMA_TABLE227_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE227_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE227_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE227_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE227_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE227_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE227_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE227_PRE_POS))

/* 0xEC8 : BL_GAMMA_TABLE_115 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_115_OFFSET                    (0xEC8)
#define DSP2_BLBACK_GAMMA_TABLE228_PRE                           DSP2_BLBACK_GAMMA_TABLE228_PRE
#define DSP2_BLBACK_GAMMA_TABLE228_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE228_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE228_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE228_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE228_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE228_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE228_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE228_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE229_PRE                           DSP2_BLBACK_GAMMA_TABLE229_PRE
#define DSP2_BLBACK_GAMMA_TABLE229_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE229_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE229_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE229_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE229_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE229_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE229_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE229_PRE_POS))

/* 0xECC : BL_GAMMA_TABLE_116 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_116_OFFSET                    (0xECC)
#define DSP2_BLBACK_GAMMA_TABLE230_PRE                           DSP2_BLBACK_GAMMA_TABLE230_PRE
#define DSP2_BLBACK_GAMMA_TABLE230_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE230_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE230_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE230_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE230_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE230_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE230_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE230_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE231_PRE                           DSP2_BLBACK_GAMMA_TABLE231_PRE
#define DSP2_BLBACK_GAMMA_TABLE231_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE231_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE231_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE231_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE231_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE231_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE231_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE231_PRE_POS))

/* 0xED0 : BL_GAMMA_TABLE_117 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_117_OFFSET                    (0xED0)
#define DSP2_BLBACK_GAMMA_TABLE232_PRE                           DSP2_BLBACK_GAMMA_TABLE232_PRE
#define DSP2_BLBACK_GAMMA_TABLE232_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE232_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE232_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE232_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE232_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE232_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE232_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE232_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE233_PRE                           DSP2_BLBACK_GAMMA_TABLE233_PRE
#define DSP2_BLBACK_GAMMA_TABLE233_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE233_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE233_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE233_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE233_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE233_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE233_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE233_PRE_POS))

/* 0xED4 : BL_GAMMA_TABLE_118 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_118_OFFSET                    (0xED4)
#define DSP2_BLBACK_GAMMA_TABLE234_PRE                           DSP2_BLBACK_GAMMA_TABLE234_PRE
#define DSP2_BLBACK_GAMMA_TABLE234_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE234_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE234_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE234_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE234_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE234_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE234_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE234_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE235_PRE                           DSP2_BLBACK_GAMMA_TABLE235_PRE
#define DSP2_BLBACK_GAMMA_TABLE235_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE235_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE235_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE235_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE235_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE235_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE235_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE235_PRE_POS))

/* 0xED8 : BL_GAMMA_TABLE_119 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_119_OFFSET                    (0xED8)
#define DSP2_BLBACK_GAMMA_TABLE236_PRE                           DSP2_BLBACK_GAMMA_TABLE236_PRE
#define DSP2_BLBACK_GAMMA_TABLE236_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE236_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE236_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE236_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE236_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE236_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE236_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE236_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE237_PRE                           DSP2_BLBACK_GAMMA_TABLE237_PRE
#define DSP2_BLBACK_GAMMA_TABLE237_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE237_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE237_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE237_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE237_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE237_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE237_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE237_PRE_POS))

/* 0xEDC : BL_GAMMA_TABLE_120 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_120_OFFSET                    (0xEDC)
#define DSP2_BLBACK_GAMMA_TABLE238_PRE                           DSP2_BLBACK_GAMMA_TABLE238_PRE
#define DSP2_BLBACK_GAMMA_TABLE238_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE238_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE238_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE238_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE238_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE238_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE238_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE238_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE239_PRE                           DSP2_BLBACK_GAMMA_TABLE239_PRE
#define DSP2_BLBACK_GAMMA_TABLE239_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE239_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE239_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE239_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE239_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE239_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE239_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE239_PRE_POS))

/* 0xEE0 : BL_GAMMA_TABLE_121 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_121_OFFSET                    (0xEE0)
#define DSP2_BLBACK_GAMMA_TABLE240_PRE                           DSP2_BLBACK_GAMMA_TABLE240_PRE
#define DSP2_BLBACK_GAMMA_TABLE240_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE240_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE240_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE240_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE240_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE240_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE240_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE240_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE241_PRE                           DSP2_BLBACK_GAMMA_TABLE241_PRE
#define DSP2_BLBACK_GAMMA_TABLE241_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE241_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE241_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE241_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE241_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE241_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE241_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE241_PRE_POS))

/* 0xEE4 : BL_GAMMA_TABLE_122 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_122_OFFSET                    (0xEE4)
#define DSP2_BLBACK_GAMMA_TABLE242_PRE                           DSP2_BLBACK_GAMMA_TABLE242_PRE
#define DSP2_BLBACK_GAMMA_TABLE242_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE242_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE242_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE242_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE242_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE242_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE242_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE242_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE243_PRE                           DSP2_BLBACK_GAMMA_TABLE243_PRE
#define DSP2_BLBACK_GAMMA_TABLE243_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE243_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE243_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE243_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE243_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE243_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE243_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE243_PRE_POS))

/* 0xEE8 : BL_GAMMA_TABLE_123 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_123_OFFSET                    (0xEE8)
#define DSP2_BLBACK_GAMMA_TABLE244_PRE                           DSP2_BLBACK_GAMMA_TABLE244_PRE
#define DSP2_BLBACK_GAMMA_TABLE244_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE244_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE244_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE244_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE244_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE244_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE244_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE244_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE245_PRE                           DSP2_BLBACK_GAMMA_TABLE245_PRE
#define DSP2_BLBACK_GAMMA_TABLE245_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE245_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE245_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE245_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE245_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE245_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE245_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE245_PRE_POS))

/* 0xEEC : BL_GAMMA_TABLE_124 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_124_OFFSET                    (0xEEC)
#define DSP2_BLBACK_GAMMA_TABLE246_PRE                           DSP2_BLBACK_GAMMA_TABLE246_PRE
#define DSP2_BLBACK_GAMMA_TABLE246_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE246_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE246_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE246_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE246_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE246_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE246_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE246_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE247_PRE                           DSP2_BLBACK_GAMMA_TABLE247_PRE
#define DSP2_BLBACK_GAMMA_TABLE247_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE247_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE247_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE247_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE247_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE247_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE247_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE247_PRE_POS))

/* 0xEF0 : BL_GAMMA_TABLE_125 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_125_OFFSET                    (0xEF0)
#define DSP2_BLBACK_GAMMA_TABLE248_PRE                           DSP2_BLBACK_GAMMA_TABLE248_PRE
#define DSP2_BLBACK_GAMMA_TABLE248_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE248_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE248_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE248_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE248_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE248_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE248_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE248_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE249_PRE                           DSP2_BLBACK_GAMMA_TABLE249_PRE
#define DSP2_BLBACK_GAMMA_TABLE249_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE249_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE249_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE249_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE249_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE249_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE249_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE249_PRE_POS))

/* 0xEF4 : BL_GAMMA_TABLE_126 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_126_OFFSET                    (0xEF4)
#define DSP2_BLBACK_GAMMA_TABLE250_PRE                           DSP2_BLBACK_GAMMA_TABLE250_PRE
#define DSP2_BLBACK_GAMMA_TABLE250_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE250_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE250_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE250_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE250_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE250_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE250_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE250_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE251_PRE                           DSP2_BLBACK_GAMMA_TABLE251_PRE
#define DSP2_BLBACK_GAMMA_TABLE251_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE251_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE251_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE251_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE251_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE251_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE251_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE251_PRE_POS))

/* 0xEF8 : BL_GAMMA_TABLE_127 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_127_OFFSET                    (0xEF8)
#define DSP2_BLBACK_GAMMA_TABLE252_PRE                           DSP2_BLBACK_GAMMA_TABLE252_PRE
#define DSP2_BLBACK_GAMMA_TABLE252_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE252_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE252_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE252_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE252_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE252_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE252_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE252_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE253_PRE                           DSP2_BLBACK_GAMMA_TABLE253_PRE
#define DSP2_BLBACK_GAMMA_TABLE253_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE253_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE253_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE253_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE253_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE253_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE253_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE253_PRE_POS))

/* 0xEFC : BL_GAMMA_TABLE_128 */
#define DSP2_BLBACK_BL_GAMMA_TABLE_128_OFFSET                    (0xEFC)
#define DSP2_BLBACK_GAMMA_TABLE254_PRE                           DSP2_BLBACK_GAMMA_TABLE254_PRE
#define DSP2_BLBACK_GAMMA_TABLE254_PRE_POS                       (0U)
#define DSP2_BLBACK_GAMMA_TABLE254_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE254_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE254_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE254_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE254_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE254_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE254_PRE_POS))
#define DSP2_BLBACK_GAMMA_TABLE255_PRE                           DSP2_BLBACK_GAMMA_TABLE255_PRE
#define DSP2_BLBACK_GAMMA_TABLE255_PRE_POS                       (16U)
#define DSP2_BLBACK_GAMMA_TABLE255_PRE_LEN                       (12U)
#define DSP2_BLBACK_GAMMA_TABLE255_PRE_MSK                       (((1U<<DSP2_BLBACK_GAMMA_TABLE255_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE255_PRE_POS)
#define DSP2_BLBACK_GAMMA_TABLE255_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_GAMMA_TABLE255_PRE_LEN)-1)<<DSP2_BLBACK_GAMMA_TABLE255_PRE_POS))

/* 0xF00 : CC_OFFSET_0 */
#define DSP2_BLBACK_CC_OFFSET_0_OFFSET                           (0xF00)
#define DSP2_BLBACK_CC_PRE_OFFSET0_PRE                           DSP2_BLBACK_CC_PRE_OFFSET0_PRE
#define DSP2_BLBACK_CC_PRE_OFFSET0_PRE_POS                       (0U)
#define DSP2_BLBACK_CC_PRE_OFFSET0_PRE_LEN                       (13U)
#define DSP2_BLBACK_CC_PRE_OFFSET0_PRE_MSK                       (((1U<<DSP2_BLBACK_CC_PRE_OFFSET0_PRE_LEN)-1)<<DSP2_BLBACK_CC_PRE_OFFSET0_PRE_POS)
#define DSP2_BLBACK_CC_PRE_OFFSET0_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_CC_PRE_OFFSET0_PRE_LEN)-1)<<DSP2_BLBACK_CC_PRE_OFFSET0_PRE_POS))
#define DSP2_BLBACK_CC_PRE_OFFSET1_PRE                           DSP2_BLBACK_CC_PRE_OFFSET1_PRE
#define DSP2_BLBACK_CC_PRE_OFFSET1_PRE_POS                       (16U)
#define DSP2_BLBACK_CC_PRE_OFFSET1_PRE_LEN                       (13U)
#define DSP2_BLBACK_CC_PRE_OFFSET1_PRE_MSK                       (((1U<<DSP2_BLBACK_CC_PRE_OFFSET1_PRE_LEN)-1)<<DSP2_BLBACK_CC_PRE_OFFSET1_PRE_POS)
#define DSP2_BLBACK_CC_PRE_OFFSET1_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_CC_PRE_OFFSET1_PRE_LEN)-1)<<DSP2_BLBACK_CC_PRE_OFFSET1_PRE_POS))
#define DSP2_BLBACK_CC_ENABLE_PRE                                DSP2_BLBACK_CC_ENABLE_PRE
#define DSP2_BLBACK_CC_ENABLE_PRE_POS                            (31U)
#define DSP2_BLBACK_CC_ENABLE_PRE_LEN                            (1U)
#define DSP2_BLBACK_CC_ENABLE_PRE_MSK                            (((1U<<DSP2_BLBACK_CC_ENABLE_PRE_LEN)-1)<<DSP2_BLBACK_CC_ENABLE_PRE_POS)
#define DSP2_BLBACK_CC_ENABLE_PRE_UMSK                           (~(((1U<<DSP2_BLBACK_CC_ENABLE_PRE_LEN)-1)<<DSP2_BLBACK_CC_ENABLE_PRE_POS))

/* 0xF04 : CC_OFFSET_1 */
#define DSP2_BLBACK_CC_OFFSET_1_OFFSET                           (0xF04)
#define DSP2_BLBACK_CC_PRE_OFFSET2_PRE                           DSP2_BLBACK_CC_PRE_OFFSET2_PRE
#define DSP2_BLBACK_CC_PRE_OFFSET2_PRE_POS                       (0U)
#define DSP2_BLBACK_CC_PRE_OFFSET2_PRE_LEN                       (13U)
#define DSP2_BLBACK_CC_PRE_OFFSET2_PRE_MSK                       (((1U<<DSP2_BLBACK_CC_PRE_OFFSET2_PRE_LEN)-1)<<DSP2_BLBACK_CC_PRE_OFFSET2_PRE_POS)
#define DSP2_BLBACK_CC_PRE_OFFSET2_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_CC_PRE_OFFSET2_PRE_LEN)-1)<<DSP2_BLBACK_CC_PRE_OFFSET2_PRE_POS))
#define DSP2_BLBACK_CC_POST_OFFSET2_PRE                          DSP2_BLBACK_CC_POST_OFFSET2_PRE
#define DSP2_BLBACK_CC_POST_OFFSET2_PRE_POS                      (16U)
#define DSP2_BLBACK_CC_POST_OFFSET2_PRE_LEN                      (13U)
#define DSP2_BLBACK_CC_POST_OFFSET2_PRE_MSK                      (((1U<<DSP2_BLBACK_CC_POST_OFFSET2_PRE_LEN)-1)<<DSP2_BLBACK_CC_POST_OFFSET2_PRE_POS)
#define DSP2_BLBACK_CC_POST_OFFSET2_PRE_UMSK                     (~(((1U<<DSP2_BLBACK_CC_POST_OFFSET2_PRE_LEN)-1)<<DSP2_BLBACK_CC_POST_OFFSET2_PRE_POS))

/* 0xF08 : CC_OFFSET_2 */
#define DSP2_BLBACK_CC_OFFSET_2_OFFSET                           (0xF08)
#define DSP2_BLBACK_CC_POST_OFFSET0_PRE                          DSP2_BLBACK_CC_POST_OFFSET0_PRE
#define DSP2_BLBACK_CC_POST_OFFSET0_PRE_POS                      (0U)
#define DSP2_BLBACK_CC_POST_OFFSET0_PRE_LEN                      (13U)
#define DSP2_BLBACK_CC_POST_OFFSET0_PRE_MSK                      (((1U<<DSP2_BLBACK_CC_POST_OFFSET0_PRE_LEN)-1)<<DSP2_BLBACK_CC_POST_OFFSET0_PRE_POS)
#define DSP2_BLBACK_CC_POST_OFFSET0_PRE_UMSK                     (~(((1U<<DSP2_BLBACK_CC_POST_OFFSET0_PRE_LEN)-1)<<DSP2_BLBACK_CC_POST_OFFSET0_PRE_POS))
#define DSP2_BLBACK_CC_POST_OFFSET1_PRE                          DSP2_BLBACK_CC_POST_OFFSET1_PRE
#define DSP2_BLBACK_CC_POST_OFFSET1_PRE_POS                      (16U)
#define DSP2_BLBACK_CC_POST_OFFSET1_PRE_LEN                      (13U)
#define DSP2_BLBACK_CC_POST_OFFSET1_PRE_MSK                      (((1U<<DSP2_BLBACK_CC_POST_OFFSET1_PRE_LEN)-1)<<DSP2_BLBACK_CC_POST_OFFSET1_PRE_POS)
#define DSP2_BLBACK_CC_POST_OFFSET1_PRE_UMSK                     (~(((1U<<DSP2_BLBACK_CC_POST_OFFSET1_PRE_LEN)-1)<<DSP2_BLBACK_CC_POST_OFFSET1_PRE_POS))

/* 0xF0C : CC_MATRIX_0 */
#define DSP2_BLBACK_CC_MATRIX_0_OFFSET                           (0xF0C)
#define DSP2_BLBACK_CC_MATRIX00_PRE                              DSP2_BLBACK_CC_MATRIX00_PRE
#define DSP2_BLBACK_CC_MATRIX00_PRE_POS                          (0U)
#define DSP2_BLBACK_CC_MATRIX00_PRE_LEN                          (12U)
#define DSP2_BLBACK_CC_MATRIX00_PRE_MSK                          (((1U<<DSP2_BLBACK_CC_MATRIX00_PRE_LEN)-1)<<DSP2_BLBACK_CC_MATRIX00_PRE_POS)
#define DSP2_BLBACK_CC_MATRIX00_PRE_UMSK                         (~(((1U<<DSP2_BLBACK_CC_MATRIX00_PRE_LEN)-1)<<DSP2_BLBACK_CC_MATRIX00_PRE_POS))
#define DSP2_BLBACK_CC_MATRIX01_PRE                              DSP2_BLBACK_CC_MATRIX01_PRE
#define DSP2_BLBACK_CC_MATRIX01_PRE_POS                          (16U)
#define DSP2_BLBACK_CC_MATRIX01_PRE_LEN                          (12U)
#define DSP2_BLBACK_CC_MATRIX01_PRE_MSK                          (((1U<<DSP2_BLBACK_CC_MATRIX01_PRE_LEN)-1)<<DSP2_BLBACK_CC_MATRIX01_PRE_POS)
#define DSP2_BLBACK_CC_MATRIX01_PRE_UMSK                         (~(((1U<<DSP2_BLBACK_CC_MATRIX01_PRE_LEN)-1)<<DSP2_BLBACK_CC_MATRIX01_PRE_POS))

/* 0xF10 : CC_MATRIX_1 */
#define DSP2_BLBACK_CC_MATRIX_1_OFFSET                           (0xF10)
#define DSP2_BLBACK_CC_MATRIX10_PRE                              DSP2_BLBACK_CC_MATRIX10_PRE
#define DSP2_BLBACK_CC_MATRIX10_PRE_POS                          (0U)
#define DSP2_BLBACK_CC_MATRIX10_PRE_LEN                          (12U)
#define DSP2_BLBACK_CC_MATRIX10_PRE_MSK                          (((1U<<DSP2_BLBACK_CC_MATRIX10_PRE_LEN)-1)<<DSP2_BLBACK_CC_MATRIX10_PRE_POS)
#define DSP2_BLBACK_CC_MATRIX10_PRE_UMSK                         (~(((1U<<DSP2_BLBACK_CC_MATRIX10_PRE_LEN)-1)<<DSP2_BLBACK_CC_MATRIX10_PRE_POS))
#define DSP2_BLBACK_CC_MATRIX02_PRE                              DSP2_BLBACK_CC_MATRIX02_PRE
#define DSP2_BLBACK_CC_MATRIX02_PRE_POS                          (16U)
#define DSP2_BLBACK_CC_MATRIX02_PRE_LEN                          (12U)
#define DSP2_BLBACK_CC_MATRIX02_PRE_MSK                          (((1U<<DSP2_BLBACK_CC_MATRIX02_PRE_LEN)-1)<<DSP2_BLBACK_CC_MATRIX02_PRE_POS)
#define DSP2_BLBACK_CC_MATRIX02_PRE_UMSK                         (~(((1U<<DSP2_BLBACK_CC_MATRIX02_PRE_LEN)-1)<<DSP2_BLBACK_CC_MATRIX02_PRE_POS))

/* 0xF14 : CC_MATRIX_2 */
#define DSP2_BLBACK_CC_MATRIX_2_OFFSET                           (0xF14)
#define DSP2_BLBACK_CC_MATRIX11_PRE                              DSP2_BLBACK_CC_MATRIX11_PRE
#define DSP2_BLBACK_CC_MATRIX11_PRE_POS                          (0U)
#define DSP2_BLBACK_CC_MATRIX11_PRE_LEN                          (12U)
#define DSP2_BLBACK_CC_MATRIX11_PRE_MSK                          (((1U<<DSP2_BLBACK_CC_MATRIX11_PRE_LEN)-1)<<DSP2_BLBACK_CC_MATRIX11_PRE_POS)
#define DSP2_BLBACK_CC_MATRIX11_PRE_UMSK                         (~(((1U<<DSP2_BLBACK_CC_MATRIX11_PRE_LEN)-1)<<DSP2_BLBACK_CC_MATRIX11_PRE_POS))
#define DSP2_BLBACK_CC_MATRIX12_PRE                              DSP2_BLBACK_CC_MATRIX12_PRE
#define DSP2_BLBACK_CC_MATRIX12_PRE_POS                          (16U)
#define DSP2_BLBACK_CC_MATRIX12_PRE_LEN                          (12U)
#define DSP2_BLBACK_CC_MATRIX12_PRE_MSK                          (((1U<<DSP2_BLBACK_CC_MATRIX12_PRE_LEN)-1)<<DSP2_BLBACK_CC_MATRIX12_PRE_POS)
#define DSP2_BLBACK_CC_MATRIX12_PRE_UMSK                         (~(((1U<<DSP2_BLBACK_CC_MATRIX12_PRE_LEN)-1)<<DSP2_BLBACK_CC_MATRIX12_PRE_POS))

/* 0xF18 : CC_MATRIX_3 */
#define DSP2_BLBACK_CC_MATRIX_3_OFFSET                           (0xF18)
#define DSP2_BLBACK_CC_MATRIX20_PRE                              DSP2_BLBACK_CC_MATRIX20_PRE
#define DSP2_BLBACK_CC_MATRIX20_PRE_POS                          (0U)
#define DSP2_BLBACK_CC_MATRIX20_PRE_LEN                          (12U)
#define DSP2_BLBACK_CC_MATRIX20_PRE_MSK                          (((1U<<DSP2_BLBACK_CC_MATRIX20_PRE_LEN)-1)<<DSP2_BLBACK_CC_MATRIX20_PRE_POS)
#define DSP2_BLBACK_CC_MATRIX20_PRE_UMSK                         (~(((1U<<DSP2_BLBACK_CC_MATRIX20_PRE_LEN)-1)<<DSP2_BLBACK_CC_MATRIX20_PRE_POS))
#define DSP2_BLBACK_CC_MATRIX21_PRE                              DSP2_BLBACK_CC_MATRIX21_PRE
#define DSP2_BLBACK_CC_MATRIX21_PRE_POS                          (16U)
#define DSP2_BLBACK_CC_MATRIX21_PRE_LEN                          (12U)
#define DSP2_BLBACK_CC_MATRIX21_PRE_MSK                          (((1U<<DSP2_BLBACK_CC_MATRIX21_PRE_LEN)-1)<<DSP2_BLBACK_CC_MATRIX21_PRE_POS)
#define DSP2_BLBACK_CC_MATRIX21_PRE_UMSK                         (~(((1U<<DSP2_BLBACK_CC_MATRIX21_PRE_LEN)-1)<<DSP2_BLBACK_CC_MATRIX21_PRE_POS))

/* 0xF1C : CC_CE_MATRIX */
#define DSP2_BLBACK_CC_CE_MATRIX_OFFSET                          (0xF1C)
#define DSP2_BLBACK_CC_MATRIX22_PRE                              DSP2_BLBACK_CC_MATRIX22_PRE
#define DSP2_BLBACK_CC_MATRIX22_PRE_POS                          (0U)
#define DSP2_BLBACK_CC_MATRIX22_PRE_LEN                          (12U)
#define DSP2_BLBACK_CC_MATRIX22_PRE_MSK                          (((1U<<DSP2_BLBACK_CC_MATRIX22_PRE_LEN)-1)<<DSP2_BLBACK_CC_MATRIX22_PRE_POS)
#define DSP2_BLBACK_CC_MATRIX22_PRE_UMSK                         (~(((1U<<DSP2_BLBACK_CC_MATRIX22_PRE_LEN)-1)<<DSP2_BLBACK_CC_MATRIX22_PRE_POS))
#define DSP2_BLBACK_CE_MATRIX02_PRE                              DSP2_BLBACK_CE_MATRIX02_PRE
#define DSP2_BLBACK_CE_MATRIX02_PRE_POS                          (16U)
#define DSP2_BLBACK_CE_MATRIX02_PRE_LEN                          (12U)
#define DSP2_BLBACK_CE_MATRIX02_PRE_MSK                          (((1U<<DSP2_BLBACK_CE_MATRIX02_PRE_LEN)-1)<<DSP2_BLBACK_CE_MATRIX02_PRE_POS)
#define DSP2_BLBACK_CE_MATRIX02_PRE_UMSK                         (~(((1U<<DSP2_BLBACK_CE_MATRIX02_PRE_LEN)-1)<<DSP2_BLBACK_CE_MATRIX02_PRE_POS))

/* 0xF20 : CE_MATRIX_0 */
#define DSP2_BLBACK_CE_MATRIX_0_OFFSET                           (0xF20)
#define DSP2_BLBACK_CE_MATRIX00_PRE                              DSP2_BLBACK_CE_MATRIX00_PRE
#define DSP2_BLBACK_CE_MATRIX00_PRE_POS                          (0U)
#define DSP2_BLBACK_CE_MATRIX00_PRE_LEN                          (12U)
#define DSP2_BLBACK_CE_MATRIX00_PRE_MSK                          (((1U<<DSP2_BLBACK_CE_MATRIX00_PRE_LEN)-1)<<DSP2_BLBACK_CE_MATRIX00_PRE_POS)
#define DSP2_BLBACK_CE_MATRIX00_PRE_UMSK                         (~(((1U<<DSP2_BLBACK_CE_MATRIX00_PRE_LEN)-1)<<DSP2_BLBACK_CE_MATRIX00_PRE_POS))
#define DSP2_BLBACK_CE_MATRIX01_PRE                              DSP2_BLBACK_CE_MATRIX01_PRE
#define DSP2_BLBACK_CE_MATRIX01_PRE_POS                          (16U)
#define DSP2_BLBACK_CE_MATRIX01_PRE_LEN                          (12U)
#define DSP2_BLBACK_CE_MATRIX01_PRE_MSK                          (((1U<<DSP2_BLBACK_CE_MATRIX01_PRE_LEN)-1)<<DSP2_BLBACK_CE_MATRIX01_PRE_POS)
#define DSP2_BLBACK_CE_MATRIX01_PRE_UMSK                         (~(((1U<<DSP2_BLBACK_CE_MATRIX01_PRE_LEN)-1)<<DSP2_BLBACK_CE_MATRIX01_PRE_POS))

/* 0xF24 : CE_MATRIX_1 */
#define DSP2_BLBACK_CE_MATRIX_1_OFFSET                           (0xF24)
#define DSP2_BLBACK_CE_MATRIX10_PRE                              DSP2_BLBACK_CE_MATRIX10_PRE
#define DSP2_BLBACK_CE_MATRIX10_PRE_POS                          (0U)
#define DSP2_BLBACK_CE_MATRIX10_PRE_LEN                          (12U)
#define DSP2_BLBACK_CE_MATRIX10_PRE_MSK                          (((1U<<DSP2_BLBACK_CE_MATRIX10_PRE_LEN)-1)<<DSP2_BLBACK_CE_MATRIX10_PRE_POS)
#define DSP2_BLBACK_CE_MATRIX10_PRE_UMSK                         (~(((1U<<DSP2_BLBACK_CE_MATRIX10_PRE_LEN)-1)<<DSP2_BLBACK_CE_MATRIX10_PRE_POS))
#define DSP2_BLBACK_CE_MATRIX11_PRE                              DSP2_BLBACK_CE_MATRIX11_PRE
#define DSP2_BLBACK_CE_MATRIX11_PRE_POS                          (16U)
#define DSP2_BLBACK_CE_MATRIX11_PRE_LEN                          (12U)
#define DSP2_BLBACK_CE_MATRIX11_PRE_MSK                          (((1U<<DSP2_BLBACK_CE_MATRIX11_PRE_LEN)-1)<<DSP2_BLBACK_CE_MATRIX11_PRE_POS)
#define DSP2_BLBACK_CE_MATRIX11_PRE_UMSK                         (~(((1U<<DSP2_BLBACK_CE_MATRIX11_PRE_LEN)-1)<<DSP2_BLBACK_CE_MATRIX11_PRE_POS))

/* 0xF28 : CE_MATRIX_2 */
#define DSP2_BLBACK_CE_MATRIX_2_OFFSET                           (0xF28)
#define DSP2_BLBACK_CE_MATRIX20_PRE                              DSP2_BLBACK_CE_MATRIX20_PRE
#define DSP2_BLBACK_CE_MATRIX20_PRE_POS                          (0U)
#define DSP2_BLBACK_CE_MATRIX20_PRE_LEN                          (12U)
#define DSP2_BLBACK_CE_MATRIX20_PRE_MSK                          (((1U<<DSP2_BLBACK_CE_MATRIX20_PRE_LEN)-1)<<DSP2_BLBACK_CE_MATRIX20_PRE_POS)
#define DSP2_BLBACK_CE_MATRIX20_PRE_UMSK                         (~(((1U<<DSP2_BLBACK_CE_MATRIX20_PRE_LEN)-1)<<DSP2_BLBACK_CE_MATRIX20_PRE_POS))
#define DSP2_BLBACK_CE_MATRIX12_PRE                              DSP2_BLBACK_CE_MATRIX12_PRE
#define DSP2_BLBACK_CE_MATRIX12_PRE_POS                          (16U)
#define DSP2_BLBACK_CE_MATRIX12_PRE_LEN                          (12U)
#define DSP2_BLBACK_CE_MATRIX12_PRE_MSK                          (((1U<<DSP2_BLBACK_CE_MATRIX12_PRE_LEN)-1)<<DSP2_BLBACK_CE_MATRIX12_PRE_POS)
#define DSP2_BLBACK_CE_MATRIX12_PRE_UMSK                         (~(((1U<<DSP2_BLBACK_CE_MATRIX12_PRE_LEN)-1)<<DSP2_BLBACK_CE_MATRIX12_PRE_POS))

/* 0xF2C : CE_MATRIX_3 */
#define DSP2_BLBACK_CE_MATRIX_3_OFFSET                           (0xF2C)
#define DSP2_BLBACK_CE_MATRIX21_PRE                              DSP2_BLBACK_CE_MATRIX21_PRE
#define DSP2_BLBACK_CE_MATRIX21_PRE_POS                          (0U)
#define DSP2_BLBACK_CE_MATRIX21_PRE_LEN                          (12U)
#define DSP2_BLBACK_CE_MATRIX21_PRE_MSK                          (((1U<<DSP2_BLBACK_CE_MATRIX21_PRE_LEN)-1)<<DSP2_BLBACK_CE_MATRIX21_PRE_POS)
#define DSP2_BLBACK_CE_MATRIX21_PRE_UMSK                         (~(((1U<<DSP2_BLBACK_CE_MATRIX21_PRE_LEN)-1)<<DSP2_BLBACK_CE_MATRIX21_PRE_POS))
#define DSP2_BLBACK_CE_MATRIX22_PRE                              DSP2_BLBACK_CE_MATRIX22_PRE
#define DSP2_BLBACK_CE_MATRIX22_PRE_POS                          (16U)
#define DSP2_BLBACK_CE_MATRIX22_PRE_LEN                          (12U)
#define DSP2_BLBACK_CE_MATRIX22_PRE_MSK                          (((1U<<DSP2_BLBACK_CE_MATRIX22_PRE_LEN)-1)<<DSP2_BLBACK_CE_MATRIX22_PRE_POS)
#define DSP2_BLBACK_CE_MATRIX22_PRE_UMSK                         (~(((1U<<DSP2_BLBACK_CE_MATRIX22_PRE_LEN)-1)<<DSP2_BLBACK_CE_MATRIX22_PRE_POS))

/* 0xF30 : CE_OFFSET_0 */
#define DSP2_BLBACK_CE_OFFSET_0_OFFSET                           (0xF30)
#define DSP2_BLBACK_CE_PRE_OFFSET0_PRE                           DSP2_BLBACK_CE_PRE_OFFSET0_PRE
#define DSP2_BLBACK_CE_PRE_OFFSET0_PRE_POS                       (0U)
#define DSP2_BLBACK_CE_PRE_OFFSET0_PRE_LEN                       (13U)
#define DSP2_BLBACK_CE_PRE_OFFSET0_PRE_MSK                       (((1U<<DSP2_BLBACK_CE_PRE_OFFSET0_PRE_LEN)-1)<<DSP2_BLBACK_CE_PRE_OFFSET0_PRE_POS)
#define DSP2_BLBACK_CE_PRE_OFFSET0_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_CE_PRE_OFFSET0_PRE_LEN)-1)<<DSP2_BLBACK_CE_PRE_OFFSET0_PRE_POS))
#define DSP2_BLBACK_CE_PRE_OFFSET1_PRE                           DSP2_BLBACK_CE_PRE_OFFSET1_PRE
#define DSP2_BLBACK_CE_PRE_OFFSET1_PRE_POS                       (16U)
#define DSP2_BLBACK_CE_PRE_OFFSET1_PRE_LEN                       (13U)
#define DSP2_BLBACK_CE_PRE_OFFSET1_PRE_MSK                       (((1U<<DSP2_BLBACK_CE_PRE_OFFSET1_PRE_LEN)-1)<<DSP2_BLBACK_CE_PRE_OFFSET1_PRE_POS)
#define DSP2_BLBACK_CE_PRE_OFFSET1_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_CE_PRE_OFFSET1_PRE_LEN)-1)<<DSP2_BLBACK_CE_PRE_OFFSET1_PRE_POS))

/* 0xF34 : CE_OFFSET_1 */
#define DSP2_BLBACK_CE_OFFSET_1_OFFSET                           (0xF34)
#define DSP2_BLBACK_CE_PRE_OFFSET2_PRE                           DSP2_BLBACK_CE_PRE_OFFSET2_PRE
#define DSP2_BLBACK_CE_PRE_OFFSET2_PRE_POS                       (0U)
#define DSP2_BLBACK_CE_PRE_OFFSET2_PRE_LEN                       (13U)
#define DSP2_BLBACK_CE_PRE_OFFSET2_PRE_MSK                       (((1U<<DSP2_BLBACK_CE_PRE_OFFSET2_PRE_LEN)-1)<<DSP2_BLBACK_CE_PRE_OFFSET2_PRE_POS)
#define DSP2_BLBACK_CE_PRE_OFFSET2_PRE_UMSK                      (~(((1U<<DSP2_BLBACK_CE_PRE_OFFSET2_PRE_LEN)-1)<<DSP2_BLBACK_CE_PRE_OFFSET2_PRE_POS))
#define DSP2_BLBACK_CE_POST_OFFSET2_PRE                          DSP2_BLBACK_CE_POST_OFFSET2_PRE
#define DSP2_BLBACK_CE_POST_OFFSET2_PRE_POS                      (16U)
#define DSP2_BLBACK_CE_POST_OFFSET2_PRE_LEN                      (13U)
#define DSP2_BLBACK_CE_POST_OFFSET2_PRE_MSK                      (((1U<<DSP2_BLBACK_CE_POST_OFFSET2_PRE_LEN)-1)<<DSP2_BLBACK_CE_POST_OFFSET2_PRE_POS)
#define DSP2_BLBACK_CE_POST_OFFSET2_PRE_UMSK                     (~(((1U<<DSP2_BLBACK_CE_POST_OFFSET2_PRE_LEN)-1)<<DSP2_BLBACK_CE_POST_OFFSET2_PRE_POS))

/* 0xF38 : CE_OFFSET_2 */
#define DSP2_BLBACK_CE_OFFSET_2_OFFSET                           (0xF38)
#define DSP2_BLBACK_CE_POST_OFFSET0_PRE                          DSP2_BLBACK_CE_POST_OFFSET0_PRE
#define DSP2_BLBACK_CE_POST_OFFSET0_PRE_POS                      (0U)
#define DSP2_BLBACK_CE_POST_OFFSET0_PRE_LEN                      (13U)
#define DSP2_BLBACK_CE_POST_OFFSET0_PRE_MSK                      (((1U<<DSP2_BLBACK_CE_POST_OFFSET0_PRE_LEN)-1)<<DSP2_BLBACK_CE_POST_OFFSET0_PRE_POS)
#define DSP2_BLBACK_CE_POST_OFFSET0_PRE_UMSK                     (~(((1U<<DSP2_BLBACK_CE_POST_OFFSET0_PRE_LEN)-1)<<DSP2_BLBACK_CE_POST_OFFSET0_PRE_POS))
#define DSP2_BLBACK_CE_POST_OFFSET1_PRE                          DSP2_BLBACK_CE_POST_OFFSET1_PRE
#define DSP2_BLBACK_CE_POST_OFFSET1_PRE_POS                      (16U)
#define DSP2_BLBACK_CE_POST_OFFSET1_PRE_LEN                      (13U)
#define DSP2_BLBACK_CE_POST_OFFSET1_PRE_MSK                      (((1U<<DSP2_BLBACK_CE_POST_OFFSET1_PRE_LEN)-1)<<DSP2_BLBACK_CE_POST_OFFSET1_PRE_POS)
#define DSP2_BLBACK_CE_POST_OFFSET1_PRE_UMSK                     (~(((1U<<DSP2_BLBACK_CE_POST_OFFSET1_PRE_LEN)-1)<<DSP2_BLBACK_CE_POST_OFFSET1_PRE_POS))


struct  dsp2_blback_reg {
    /* 0x0  reserved */
    uint8_t RESERVED0x0[788];

    /* 0x314 : ccr_coef_A */
    union {
        struct {
            uint32_t reserved_0_15                  : 16; /* [15: 0],       rsvd,        0x0 */
            uint32_t a11_pre                        : 12; /* [27:16],        r/w,      0x200 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ccr_coef_A;

    /* 0x318 : ccr_coef_B */
    union {
        struct {
            uint32_t a12_pre                        : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t a13_pre                        : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ccr_coef_B;

    /* 0x31C : ccr_coef_C */
    union {
        struct {
            uint32_t a21_pre                        : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t a22_pre                        : 12; /* [27:16],        r/w,      0x200 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ccr_coef_C;

    /* 0x320 : ccr_coef_D */
    union {
        struct {
            uint32_t a23_pre                        : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t a31_pre                        : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ccr_coef_D;

    /* 0x324 : ccr_coef_E */
    union {
        struct {
            uint32_t a32_pre                        : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t a33_pre                        : 12; /* [27:16],        r/w,      0x200 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ccr_coef_E;

    /* 0x328 : gamma_A */
    union {
        struct {
            uint32_t gamma_on_pre                   :  1; /* [    0],        r/w,        0x0 */
            uint32_t gamma_eb_pre                   :  1; /* [    1],        r/w,        0x0 */
            uint32_t reserved_2_3                   :  2; /* [ 3: 2],       rsvd,        0x0 */
            uint32_t bl_gamma_en_pre                :  1; /* [    4],        r/w,        0x0 */
            uint32_t reserved_5_31                  : 27; /* [31: 5],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } gamma_A;

    /* 0x32c  reserved */
    uint8_t RESERVED0x32c[16];

    /* 0x33C : conv_mode */
    union {
        struct {
            uint32_t conv_mode_w                    :  1; /* [    0],        r/w,        0x0 */
            uint32_t reserved_1_31                  : 31; /* [31: 1],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } conv_mode;

    /* 0x340  reserved */
    uint8_t RESERVED0x340[12];

    /* 0x34C : YUVC_A */
    union {
        struct {
            uint32_t YBrightness_w                  :  8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t YContrast_w                    :  8; /* [15: 8],        r/w,        0x0 */
            uint32_t CbSaturation_pre               :  8; /* [23:16],        r/w,       0x80 */
            uint32_t CrSaturation_pre               :  8; /* [31:24],        r/w,       0x80 */
        }BF;
        uint32_t WORD;
    } YUVC_A;

    /* 0x350 : YUVC_B */
    union {
        struct {
            uint32_t SpecialMode_w                  :  3; /* [ 2: 0],        r/w,        0x0 */
            uint32_t reserved_3                     :  1; /* [    3],       rsvd,        0x0 */
            uint32_t C444to422Filteringmode_w       :  1; /* [    4],        r/w,        0x0 */
            uint32_t reserved_5_7                   :  3; /* [ 7: 5],       rsvd,        0x0 */
            uint32_t SepiaCb_w                      :  8; /* [15: 8],        r/w,       0x73 */
            uint32_t SepiaCr_w                      :  8; /* [23:16],        r/w,       0x89 */
            uint32_t SolarThred_w                   :  8; /* [31:24],        r/w,       0x80 */
        }BF;
        uint32_t WORD;
    } YUVC_B;

    /* 0x354 : DNR_A */
    union {
        struct {
            uint32_t noise_level_pre                :  6; /* [ 5: 0],        r/w,        0x0 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t nr_hsize_pre                   : 16; /* [23: 8],        r/w,      0x788 */
            uint32_t Filt_Strength_2D_pre           :  4; /* [27:24],        r/w,        0x6 */
            uint32_t Filt_Strength_3D_pre           :  4; /* [31:28],        r/w,        0x5 */
        }BF;
        uint32_t WORD;
    } DNR_A;

    /* 0x358 : DNR_B */
    union {
        struct {
            uint32_t reserved_0_7                   :  8; /* [ 7: 0],       rsvd,        0x0 */
            uint32_t CbCr_select_w                  :  1; /* [    8],        r/w,        0x1 */
            uint32_t out_format_w                   :  2; /* [10: 9],        r/w,        0x1 */
            uint32_t reserved_11_31                 : 21; /* [31:11],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } DNR_B;

    /* 0x35c  reserved */
    uint8_t RESERVED0x35c[4];

    /* 0x360 : BLEE_0 */
    union {
        struct {
            uint32_t ee_eb_pre                      :  1; /* [    0],        r/w,        0x0 */
            uint32_t ovrsht_eb_pre                  :  1; /* [    1],        r/w,        0x0 */
            uint32_t reserved_2_15                  : 14; /* [15: 2],       rsvd,        0x0 */
            uint32_t txt_thr_pre                    :  9; /* [24:16],        r/w,        0x0 */
            uint32_t reserved_25_31                 :  7; /* [31:25],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BLEE_0;

    /* 0x364 : BLEE_1 */
    union {
        struct {
            uint32_t thresh1_pre                    :  7; /* [ 6: 0],        r/w,        0x0 */
            uint32_t reserved_7                     :  1; /* [    7],       rsvd,        0x0 */
            uint32_t thresh2_pre                    :  7; /* [14: 8],        r/w,        0x0 */
            uint32_t reserved_15                    :  1; /* [   15],       rsvd,        0x0 */
            uint32_t flat_thr_pre                   :  8; /* [23:16],        r/w,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BLEE_1;

    /* 0x368 : BLEE_2 */
    union {
        struct {
            uint32_t ovrsht_pos_pre                 :  7; /* [ 6: 0],        r/w,        0x0 */
            uint32_t reserved_7                     :  1; /* [    7],       rsvd,        0x0 */
            uint32_t ovrsht_neg_pre                 :  7; /* [14: 8],        r/w,        0x0 */
            uint32_t reserved_15                    :  1; /* [   15],       rsvd,        0x0 */
            uint32_t posee_str_pre                  :  7; /* [22:16],        r/w,        0x0 */
            uint32_t reserved_23                    :  1; /* [   23],       rsvd,        0x0 */
            uint32_t negee_str_pre                  :  7; /* [30:24],        r/w,        0x0 */
            uint32_t reserved_31                    :  1; /* [   31],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BLEE_2;

    /* 0x36C : BLEE_3 */
    union {
        struct {
            uint32_t edge_thr_pre                   : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t nr_str_pre                     :  8; /* [23:16],        r/w,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BLEE_3;

    /* 0x370 : BLEE_4 */
    union {
        struct {
            uint32_t luma_wgt0_pre                  : 10; /* [ 9: 0],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t luma_wgt1_pre                  : 10; /* [25:16],        r/w,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BLEE_4;

    /* 0x374 : BLEE_5 */
    union {
        struct {
            uint32_t luma_wgt2_pre                  : 10; /* [ 9: 0],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t luma_wgt3_pre                  : 10; /* [25:16],        r/w,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BLEE_5;

    /* 0x378 : BLEE_6 */
    union {
        struct {
            uint32_t luma_wgt4_pre                  : 10; /* [ 9: 0],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t luma_wgt5_pre                  : 10; /* [25:16],        r/w,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BLEE_6;

    /* 0x37C : BLEE_7 */
    union {
        struct {
            uint32_t luma_wgt6_pre                  : 10; /* [ 9: 0],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t luma_wgt7_pre                  : 10; /* [25:16],        r/w,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BLEE_7;

    /* 0x380 : BLEE_8 */
    union {
        struct {
            uint32_t luma_wgt8_pre                  : 10; /* [ 9: 0],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t luma_wgt9_pre                  : 10; /* [25:16],        r/w,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BLEE_8;

    /* 0x384 : BLEE_9 */
    union {
        struct {
            uint32_t luma_wgt10_pre                 : 10; /* [ 9: 0],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t luma_wgt11_pre                 : 10; /* [25:16],        r/w,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BLEE_9;

    /* 0x388 : BLEE_A */
    union {
        struct {
            uint32_t luma_wgt12_pre                 : 10; /* [ 9: 0],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t luma_wgt13_pre                 : 10; /* [25:16],        r/w,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BLEE_A;

    /* 0x38C : BLEE_B */
    union {
        struct {
            uint32_t luma_wgt14_pre                 : 10; /* [ 9: 0],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t luma_wgt15_pre                 : 10; /* [25:16],        r/w,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BLEE_B;

    /* 0x390 : BLEE_C */
    union {
        struct {
            uint32_t luma_wgt16_pre                 : 10; /* [ 9: 0],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t luma_wgt17_pre                 : 10; /* [25:16],        r/w,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BLEE_C;

    /* 0x394 : BLEE_D */
    union {
        struct {
            uint32_t luma_wgt18_pre                 : 10; /* [ 9: 0],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t luma_wgt19_pre                 : 10; /* [25:16],        r/w,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BLEE_D;

    /* 0x398 : BLEE_E */
    union {
        struct {
            uint32_t luma_wgt20_pre                 : 10; /* [ 9: 0],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t luma_wgt21_pre                 : 10; /* [25:16],        r/w,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BLEE_E;

    /* 0x39C : BLEE_F */
    union {
        struct {
            uint32_t luma_wgt22_pre                 : 10; /* [ 9: 0],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t luma_wgt23_pre                 : 10; /* [25:16],        r/w,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BLEE_F;

    /* 0x3A0 : BLEE_10 */
    union {
        struct {
            uint32_t luma_wgt24_pre                 : 10; /* [ 9: 0],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t luma_wgt25_pre                 : 10; /* [25:16],        r/w,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BLEE_10;

    /* 0x3A4 : BLEE_11 */
    union {
        struct {
            uint32_t luma_wgt26_pre                 : 10; /* [ 9: 0],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t luma_wgt27_pre                 : 10; /* [25:16],        r/w,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BLEE_11;

    /* 0x3A8 : BLEE_12 */
    union {
        struct {
            uint32_t luma_wgt28_pre                 : 10; /* [ 9: 0],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t luma_wgt29_pre                 : 10; /* [25:16],        r/w,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BLEE_12;

    /* 0x3AC : BLEE_13 */
    union {
        struct {
            uint32_t luma_wgt30_pre                 : 10; /* [ 9: 0],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t luma_wgt31_pre                 : 10; /* [25:16],        r/w,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BLEE_13;

    /* 0x3B0 : CS1 */
    union {
        struct {
            uint32_t cs1_grey_th_pre                :  4; /* [ 3: 0],        r/w,        0x0 */
            uint32_t cs1_enable_pre                 :  1; /* [    4],        r/w,        0x0 */
            uint32_t reserved_5_7                   :  3; /* [ 7: 5],       rsvd,        0x0 */
            uint32_t cs1_weight_pre                 :  5; /* [12: 8],        r/w,        0x0 */
            uint32_t reserved_13_15                 :  3; /* [15:13],       rsvd,        0x0 */
            uint32_t cs1_gain_pre                   :  9; /* [24:16],        r/w,        0x0 */
            uint32_t reserved_25_31                 :  7; /* [31:25],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } CS1;

    /* 0x3B4 : CS2 */
    union {
        struct {
            uint32_t cs2_grey_th_pre                :  4; /* [ 3: 0],        r/w,        0x0 */
            uint32_t cs2_enable_pre                 :  1; /* [    4],        r/w,        0x0 */
            uint32_t reserved_5_7                   :  3; /* [ 7: 5],       rsvd,        0x0 */
            uint32_t cs2_weight_pre                 :  5; /* [12: 8],        r/w,        0x0 */
            uint32_t reserved_13_15                 :  3; /* [15:13],       rsvd,        0x0 */
            uint32_t cs2_gain_pre                   :  9; /* [24:16],        r/w,        0x0 */
            uint32_t reserved_25_31                 :  7; /* [31:25],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } CS2;

    /* 0x3b8  reserved */
    uint8_t RESERVED0x3b8[68];

    /* 0x3FC : DUMMY_CTRL */
    union {
        struct {
            uint32_t reg_bl444to422_en_w            :  1; /* [    0],        r/w,        0x0 */
            uint32_t reserved_1_31                  : 31; /* [31: 1],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } DUMMY_CTRL;

    /* 0x400  reserved */
    uint8_t RESERVED0x400[1280];

    /* 0x900 : WDR_0 */
    union {
        struct {
            uint32_t wdr_en_pre                     :  1; /* [    0],        r/w,        0x0 */
            uint32_t blwdr_buf_idx_r                :  1; /* [    1],          r,        0x0 */
            uint32_t reserved_2_3                   :  2; /* [ 3: 2],       rsvd,        0x0 */
            uint32_t blwdr_w_cnt_r                  :  5; /* [ 8: 4],          r,        0x0 */
            uint32_t reserved_9_15                  :  7; /* [15: 9],       rsvd,        0x0 */
            uint32_t wdr_cs_gain_pre                : 13; /* [28:16],        r/w,        0x0 */
            uint32_t reserved_29_31                 :  3; /* [31:29],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_0;

    /* 0x904 : WDR_CS_0 */
    union {
        struct {
            uint32_t wdr_cs_en_pre                  :  1; /* [    0],        r/w,        0x0 */
            uint32_t reserved_1_7                   :  7; /* [ 7: 1],       rsvd,        0x0 */
            uint32_t wdr_cs_weight_pre              :  5; /* [12: 8],        r/w,        0x0 */
            uint32_t reserved_13_15                 :  3; /* [15:13],       rsvd,        0x0 */
            uint32_t wdr_cs_grey_th_pre             :  8; /* [23:16],        r/w,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_CS_0;

    /* 0x908 : WDR_HIST_1 */
    union {
        struct {
            uint32_t hist_roi0_en_pre               :  1; /* [    0],        r/w,        0x0 */
            uint32_t reserved_1_7                   :  7; /* [ 7: 1],       rsvd,        0x0 */
            uint32_t hist_roi0_weight_pre           :  4; /* [11: 8],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t hist_roi1_en_pre               :  1; /* [   16],        r/w,        0x0 */
            uint32_t reserved_17_23                 :  7; /* [23:17],       rsvd,        0x0 */
            uint32_t hist_roi1_weight_pre           :  4; /* [27:24],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_HIST_1;

    /* 0x90C : WDR_HIST_2 */
    union {
        struct {
            uint32_t hist_roi2_en_pre               :  1; /* [    0],        r/w,        0x0 */
            uint32_t reserved_1_7                   :  7; /* [ 7: 1],       rsvd,        0x0 */
            uint32_t hist_roi2_weight_pre           :  4; /* [11: 8],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t hist_roi3_en_pre               :  1; /* [   16],        r/w,        0x0 */
            uint32_t reserved_17_23                 :  7; /* [23:17],       rsvd,        0x0 */
            uint32_t hist_roi3_weight_pre           :  4; /* [27:24],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_HIST_2;

    /* 0x910 : WDR_HIST_3 */
    union {
        struct {
            uint32_t hist_roi4_en_pre               :  1; /* [    0],        r/w,        0x0 */
            uint32_t reserved_1_7                   :  7; /* [ 7: 1],       rsvd,        0x0 */
            uint32_t hist_roi4_weight_pre           :  4; /* [11: 8],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t hist_roi5_en_pre               :  1; /* [   16],        r/w,        0x0 */
            uint32_t reserved_17_23                 :  7; /* [23:17],       rsvd,        0x0 */
            uint32_t hist_roi5_weight_pre           :  4; /* [27:24],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_HIST_3;

    /* 0x914 : WDR_HIST_4 */
    union {
        struct {
            uint32_t hist_roi6_en_pre               :  1; /* [    0],        r/w,        0x0 */
            uint32_t reserved_1_7                   :  7; /* [ 7: 1],       rsvd,        0x0 */
            uint32_t hist_roi6_weight_pre           :  4; /* [11: 8],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t hist_roi7_en_pre               :  1; /* [   16],        r/w,        0x0 */
            uint32_t reserved_17_23                 :  7; /* [23:17],       rsvd,        0x0 */
            uint32_t hist_roi7_weight_pre           :  4; /* [27:24],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_HIST_4;

    /* 0x918 : WDR_HIST_5 */
    union {
        struct {
            uint32_t hist_x0_max_pre                : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15                 :  5; /* [15:11],       rsvd,        0x0 */
            uint32_t hist_x0_min_pre                : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31                 :  5; /* [31:27],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_HIST_5;

    /* 0x91C : WDR_HIST_6 */
    union {
        struct {
            uint32_t hist_y0_max_pre                : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15                 :  5; /* [15:11],       rsvd,        0x0 */
            uint32_t hist_y0_min_pre                : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31                 :  5; /* [31:27],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_HIST_6;

    /* 0x920 : WDR_HIST_7 */
    union {
        struct {
            uint32_t hist_x1_max_pre                : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15                 :  5; /* [15:11],       rsvd,        0x0 */
            uint32_t hist_x1_min_pre                : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31                 :  5; /* [31:27],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_HIST_7;

    /* 0x924 : WDR_HIST_8 */
    union {
        struct {
            uint32_t hist_y1_max_pre                : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15                 :  5; /* [15:11],       rsvd,        0x0 */
            uint32_t hist_y1_min_pre                : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31                 :  5; /* [31:27],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_HIST_8;

    /* 0x928 : WDR_HIST_9 */
    union {
        struct {
            uint32_t hist_x2_max_pre                : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15                 :  5; /* [15:11],       rsvd,        0x0 */
            uint32_t hist_x2_min_pre                : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31                 :  5; /* [31:27],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_HIST_9;

    /* 0x92C : WDR_HIST_10 */
    union {
        struct {
            uint32_t hist_y2_max_pre                : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15                 :  5; /* [15:11],       rsvd,        0x0 */
            uint32_t hist_y2_min_pre                : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31                 :  5; /* [31:27],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_HIST_10;

    /* 0x930 : WDR_HIST_11 */
    union {
        struct {
            uint32_t hist_x3_max_pre                : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15                 :  5; /* [15:11],       rsvd,        0x0 */
            uint32_t hist_x3_min_pre                : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31                 :  5; /* [31:27],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_HIST_11;

    /* 0x934 : WDR_HIST_12 */
    union {
        struct {
            uint32_t hist_y3_max_pre                : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15                 :  5; /* [15:11],       rsvd,        0x0 */
            uint32_t hist_y3_min_pre                : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31                 :  5; /* [31:27],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_HIST_12;

    /* 0x938 : WDR_HIST_13 */
    union {
        struct {
            uint32_t hist_x4_max_pre                : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15                 :  5; /* [15:11],       rsvd,        0x0 */
            uint32_t hist_x4_min_pre                : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31                 :  5; /* [31:27],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_HIST_13;

    /* 0x93C : WDR_HIST_14 */
    union {
        struct {
            uint32_t hist_y4_max_pre                : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15                 :  5; /* [15:11],       rsvd,        0x0 */
            uint32_t hist_y4_min_pre                : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31                 :  5; /* [31:27],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_HIST_14;

    /* 0x940 : WDR_HIST_15 */
    union {
        struct {
            uint32_t hist_x5_max_pre                : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15                 :  5; /* [15:11],       rsvd,        0x0 */
            uint32_t hist_x5_min_pre                : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31                 :  5; /* [31:27],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_HIST_15;

    /* 0x944 : WDR_HIST_16 */
    union {
        struct {
            uint32_t hist_y5_max_pre                : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15                 :  5; /* [15:11],       rsvd,        0x0 */
            uint32_t hist_y5_min_pre                : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31                 :  5; /* [31:27],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_HIST_16;

    /* 0x948 : WDR_HIST_17 */
    union {
        struct {
            uint32_t hist_x6_max_pre                : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15                 :  5; /* [15:11],       rsvd,        0x0 */
            uint32_t hist_x6_min_pre                : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31                 :  5; /* [31:27],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_HIST_17;

    /* 0x94C : WDR_HIST_18 */
    union {
        struct {
            uint32_t hist_y6_max_pre                : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15                 :  5; /* [15:11],       rsvd,        0x0 */
            uint32_t hist_y6_min_pre                : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31                 :  5; /* [31:27],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_HIST_18;

    /* 0x950 : WDR_HIST_19 */
    union {
        struct {
            uint32_t hist_x7_max_pre                : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15                 :  5; /* [15:11],       rsvd,        0x0 */
            uint32_t hist_x7_min_pre                : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31                 :  5; /* [31:27],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_HIST_19;

    /* 0x954 : WDR_HIST_20 */
    union {
        struct {
            uint32_t hist_y7_max_pre                : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15                 :  5; /* [15:11],       rsvd,        0x0 */
            uint32_t hist_y7_min_pre                : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31                 :  5; /* [31:27],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_HIST_20;

    /* 0x958 : REG_HIST0_64 */
    union {
        struct {
            uint32_t hist0_64_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_64;

    /* 0x95C : REG_HIST1_64 */
    union {
        struct {
            uint32_t hist1_64_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_64;

    /* 0x960  reserved */
    uint8_t RESERVED0x960[160];

    /* 0xA00 : REG_HIST0_0 */
    union {
        struct {
            uint32_t hist0_0_r                      : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_0;

    /* 0xA04 : REG_HIST0_1 */
    union {
        struct {
            uint32_t hist0_1_r                      : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_1;

    /* 0xA08 : REG_HIST0_2 */
    union {
        struct {
            uint32_t hist0_2_r                      : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_2;

    /* 0xA0C : REG_HIST0_3 */
    union {
        struct {
            uint32_t hist0_3_r                      : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_3;

    /* 0xA10 : REG_HIST0_4 */
    union {
        struct {
            uint32_t hist0_4_r                      : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_4;

    /* 0xA14 : REG_HIST0_5 */
    union {
        struct {
            uint32_t hist0_5_r                      : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_5;

    /* 0xA18 : REG_HIST0_6 */
    union {
        struct {
            uint32_t hist0_6_r                      : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_6;

    /* 0xA1C : REG_HIST0_7 */
    union {
        struct {
            uint32_t hist0_7_r                      : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_7;

    /* 0xA20 : REG_HIST0_8 */
    union {
        struct {
            uint32_t hist0_8_r                      : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_8;

    /* 0xA24 : REG_HIST0_9 */
    union {
        struct {
            uint32_t hist0_9_r                      : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_9;

    /* 0xA28 : REG_HIST0_10 */
    union {
        struct {
            uint32_t hist0_10_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_10;

    /* 0xA2C : REG_HIST0_11 */
    union {
        struct {
            uint32_t hist0_11_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_11;

    /* 0xA30 : REG_HIST0_12 */
    union {
        struct {
            uint32_t hist0_12_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_12;

    /* 0xA34 : REG_HIST0_13 */
    union {
        struct {
            uint32_t hist0_13_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_13;

    /* 0xA38 : REG_HIST0_14 */
    union {
        struct {
            uint32_t hist0_14_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_14;

    /* 0xA3C : REG_HIST0_15 */
    union {
        struct {
            uint32_t hist0_15_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_15;

    /* 0xA40 : REG_HIST0_16 */
    union {
        struct {
            uint32_t hist0_16_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_16;

    /* 0xA44 : REG_HIST0_17 */
    union {
        struct {
            uint32_t hist0_17_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_17;

    /* 0xA48 : REG_HIST0_18 */
    union {
        struct {
            uint32_t hist0_18_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_18;

    /* 0xA4C : REG_HIST0_19 */
    union {
        struct {
            uint32_t hist0_19_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_19;

    /* 0xA50 : REG_HIST0_20 */
    union {
        struct {
            uint32_t hist0_20_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_20;

    /* 0xA54 : REG_HIST0_21 */
    union {
        struct {
            uint32_t hist0_21_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_21;

    /* 0xA58 : REG_HIST0_22 */
    union {
        struct {
            uint32_t hist0_22_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_22;

    /* 0xA5C : REG_HIST0_23 */
    union {
        struct {
            uint32_t hist0_23_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_23;

    /* 0xA60 : REG_HIST0_24 */
    union {
        struct {
            uint32_t hist0_24_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_24;

    /* 0xA64 : REG_HIST0_25 */
    union {
        struct {
            uint32_t hist0_25_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_25;

    /* 0xA68 : REG_HIST0_26 */
    union {
        struct {
            uint32_t hist0_26_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_26;

    /* 0xA6C : REG_HIST0_27 */
    union {
        struct {
            uint32_t hist0_27_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_27;

    /* 0xA70 : REG_HIST0_28 */
    union {
        struct {
            uint32_t hist0_28_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_28;

    /* 0xA74 : REG_HIST0_29 */
    union {
        struct {
            uint32_t hist0_29_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_29;

    /* 0xA78 : REG_HIST0_30 */
    union {
        struct {
            uint32_t hist0_30_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_30;

    /* 0xA7C : REG_HIST0_31 */
    union {
        struct {
            uint32_t hist0_31_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_31;

    /* 0xA80 : REG_HIST0_32 */
    union {
        struct {
            uint32_t hist0_32_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_32;

    /* 0xA84 : REG_HIST0_33 */
    union {
        struct {
            uint32_t hist0_33_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_33;

    /* 0xA88 : REG_HIST0_34 */
    union {
        struct {
            uint32_t hist0_34_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_34;

    /* 0xA8C : REG_HIST0_35 */
    union {
        struct {
            uint32_t hist0_35_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_35;

    /* 0xA90 : REG_HIST0_36 */
    union {
        struct {
            uint32_t hist0_36_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_36;

    /* 0xA94 : REG_HIST0_37 */
    union {
        struct {
            uint32_t hist0_37_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_37;

    /* 0xA98 : REG_HIST0_38 */
    union {
        struct {
            uint32_t hist0_38_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_38;

    /* 0xA9C : REG_HIST0_39 */
    union {
        struct {
            uint32_t hist0_39_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_39;

    /* 0xAA0 : REG_HIST0_40 */
    union {
        struct {
            uint32_t hist0_40_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_40;

    /* 0xAA4 : REG_HIST0_41 */
    union {
        struct {
            uint32_t hist0_41_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_41;

    /* 0xAA8 : REG_HIST0_42 */
    union {
        struct {
            uint32_t hist0_42_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_42;

    /* 0xAAC : REG_HIST0_43 */
    union {
        struct {
            uint32_t hist0_43_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_43;

    /* 0xAB0 : REG_HIST0_44 */
    union {
        struct {
            uint32_t hist0_44_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_44;

    /* 0xAB4 : REG_HIST0_45 */
    union {
        struct {
            uint32_t hist0_45_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_45;

    /* 0xAB8 : REG_HIST0_46 */
    union {
        struct {
            uint32_t hist0_46_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_46;

    /* 0xABC : REG_HIST0_47 */
    union {
        struct {
            uint32_t hist0_47_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_47;

    /* 0xAC0 : REG_HIST0_48 */
    union {
        struct {
            uint32_t hist0_48_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_48;

    /* 0xAC4 : REG_HIST0_49 */
    union {
        struct {
            uint32_t hist0_49_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_49;

    /* 0xAC8 : REG_HIST0_50 */
    union {
        struct {
            uint32_t hist0_50_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_50;

    /* 0xACC : REG_HIST0_51 */
    union {
        struct {
            uint32_t hist0_51_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_51;

    /* 0xAD0 : REG_HIST0_52 */
    union {
        struct {
            uint32_t hist0_52_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_52;

    /* 0xAD4 : REG_HIST0_53 */
    union {
        struct {
            uint32_t hist0_53_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_53;

    /* 0xAD8 : REG_HIST0_54 */
    union {
        struct {
            uint32_t hist0_54_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_54;

    /* 0xADC : REG_HIST0_55 */
    union {
        struct {
            uint32_t hist0_55_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_55;

    /* 0xAE0 : REG_HIST0_56 */
    union {
        struct {
            uint32_t hist0_56_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_56;

    /* 0xAE4 : REG_HIST0_57 */
    union {
        struct {
            uint32_t hist0_57_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_57;

    /* 0xAE8 : REG_HIST0_58 */
    union {
        struct {
            uint32_t hist0_58_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_58;

    /* 0xAEC : REG_HIST0_59 */
    union {
        struct {
            uint32_t hist0_59_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_59;

    /* 0xAF0 : REG_HIST0_60 */
    union {
        struct {
            uint32_t hist0_60_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_60;

    /* 0xAF4 : REG_HIST0_61 */
    union {
        struct {
            uint32_t hist0_61_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_61;

    /* 0xAF8 : REG_HIST0_62 */
    union {
        struct {
            uint32_t hist0_62_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_62;

    /* 0xAFC : REG_HIST0_63 */
    union {
        struct {
            uint32_t hist0_63_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST0_63;

    /* 0xB00 : REG_HIST1_0 */
    union {
        struct {
            uint32_t hist1_0_r                      : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_0;

    /* 0xB04 : REG_HIST1_1 */
    union {
        struct {
            uint32_t hist1_1_r                      : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_1;

    /* 0xB08 : REG_HIST1_2 */
    union {
        struct {
            uint32_t hist1_2_r                      : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_2;

    /* 0xB0C : REG_HIST1_3 */
    union {
        struct {
            uint32_t hist1_3_r                      : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_3;

    /* 0xB10 : REG_HIST1_4 */
    union {
        struct {
            uint32_t hist1_4_r                      : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_4;

    /* 0xB14 : REG_HIST1_5 */
    union {
        struct {
            uint32_t hist1_5_r                      : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_5;

    /* 0xB18 : REG_HIST1_6 */
    union {
        struct {
            uint32_t hist1_6_r                      : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_6;

    /* 0xB1C : REG_HIST1_7 */
    union {
        struct {
            uint32_t hist1_7_r                      : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_7;

    /* 0xB20 : REG_HIST1_8 */
    union {
        struct {
            uint32_t hist1_8_r                      : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_8;

    /* 0xB24 : REG_HIST1_9 */
    union {
        struct {
            uint32_t hist1_9_r                      : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_9;

    /* 0xB28 : REG_HIST1_10 */
    union {
        struct {
            uint32_t hist1_10_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_10;

    /* 0xB2C : REG_HIST1_11 */
    union {
        struct {
            uint32_t hist1_11_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_11;

    /* 0xB30 : REG_HIST1_12 */
    union {
        struct {
            uint32_t hist1_12_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_12;

    /* 0xB34 : REG_HIST1_13 */
    union {
        struct {
            uint32_t hist1_13_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_13;

    /* 0xB38 : REG_HIST1_14 */
    union {
        struct {
            uint32_t hist1_14_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_14;

    /* 0xB3C : REG_HIST1_15 */
    union {
        struct {
            uint32_t hist1_15_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_15;

    /* 0xB40 : REG_HIST1_16 */
    union {
        struct {
            uint32_t hist1_16_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_16;

    /* 0xB44 : REG_HIST1_17 */
    union {
        struct {
            uint32_t hist1_17_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_17;

    /* 0xB48 : REG_HIST1_18 */
    union {
        struct {
            uint32_t hist1_18_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_18;

    /* 0xB4C : REG_HIST1_19 */
    union {
        struct {
            uint32_t hist1_19_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_19;

    /* 0xB50 : REG_HIST1_20 */
    union {
        struct {
            uint32_t hist1_20_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_20;

    /* 0xB54 : REG_HIST1_21 */
    union {
        struct {
            uint32_t hist1_21_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_21;

    /* 0xB58 : REG_HIST1_22 */
    union {
        struct {
            uint32_t hist1_22_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_22;

    /* 0xB5C : REG_HIST1_23 */
    union {
        struct {
            uint32_t hist1_23_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_23;

    /* 0xB60 : REG_HIST1_24 */
    union {
        struct {
            uint32_t hist1_24_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_24;

    /* 0xB64 : REG_HIST1_25 */
    union {
        struct {
            uint32_t hist1_25_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_25;

    /* 0xB68 : REG_HIST1_26 */
    union {
        struct {
            uint32_t hist1_26_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_26;

    /* 0xB6C : REG_HIST1_27 */
    union {
        struct {
            uint32_t hist1_27_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_27;

    /* 0xB70 : REG_HIST1_28 */
    union {
        struct {
            uint32_t hist1_28_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_28;

    /* 0xB74 : REG_HIST1_29 */
    union {
        struct {
            uint32_t hist1_29_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_29;

    /* 0xB78 : REG_HIST1_30 */
    union {
        struct {
            uint32_t hist1_30_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_30;

    /* 0xB7C : REG_HIST1_31 */
    union {
        struct {
            uint32_t hist1_31_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_31;

    /* 0xB80 : REG_HIST1_32 */
    union {
        struct {
            uint32_t hist1_32_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_32;

    /* 0xB84 : REG_HIST1_33 */
    union {
        struct {
            uint32_t hist1_33_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_33;

    /* 0xB88 : REG_HIST1_34 */
    union {
        struct {
            uint32_t hist1_34_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_34;

    /* 0xB8C : REG_HIST1_35 */
    union {
        struct {
            uint32_t hist1_35_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_35;

    /* 0xB90 : REG_HIST1_36 */
    union {
        struct {
            uint32_t hist1_36_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_36;

    /* 0xB94 : REG_HIST1_37 */
    union {
        struct {
            uint32_t hist1_37_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_37;

    /* 0xB98 : REG_HIST1_38 */
    union {
        struct {
            uint32_t hist1_38_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_38;

    /* 0xB9C : REG_HIST1_39 */
    union {
        struct {
            uint32_t hist1_39_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_39;

    /* 0xBA0 : REG_HIST1_40 */
    union {
        struct {
            uint32_t hist1_40_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_40;

    /* 0xBA4 : REG_HIST1_41 */
    union {
        struct {
            uint32_t hist1_41_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_41;

    /* 0xBA8 : REG_HIST1_42 */
    union {
        struct {
            uint32_t hist1_42_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_42;

    /* 0xBAC : REG_HIST1_43 */
    union {
        struct {
            uint32_t hist1_43_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_43;

    /* 0xBB0 : REG_HIST1_44 */
    union {
        struct {
            uint32_t hist1_44_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_44;

    /* 0xBB4 : REG_HIST1_45 */
    union {
        struct {
            uint32_t hist1_45_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_45;

    /* 0xBB8 : REG_HIST1_46 */
    union {
        struct {
            uint32_t hist1_46_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_46;

    /* 0xBBC : REG_HIST1_47 */
    union {
        struct {
            uint32_t hist1_47_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_47;

    /* 0xBC0 : REG_HIST1_48 */
    union {
        struct {
            uint32_t hist1_48_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_48;

    /* 0xBC4 : REG_HIST1_49 */
    union {
        struct {
            uint32_t hist1_49_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_49;

    /* 0xBC8 : REG_HIST1_50 */
    union {
        struct {
            uint32_t hist1_50_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_50;

    /* 0xBCC : REG_HIST1_51 */
    union {
        struct {
            uint32_t hist1_51_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_51;

    /* 0xBD0 : REG_HIST1_52 */
    union {
        struct {
            uint32_t hist1_52_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_52;

    /* 0xBD4 : REG_HIST1_53 */
    union {
        struct {
            uint32_t hist1_53_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_53;

    /* 0xBD8 : REG_HIST1_54 */
    union {
        struct {
            uint32_t hist1_54_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_54;

    /* 0xBDC : REG_HIST1_55 */
    union {
        struct {
            uint32_t hist1_55_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_55;

    /* 0xBE0 : REG_HIST1_56 */
    union {
        struct {
            uint32_t hist1_56_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_56;

    /* 0xBE4 : REG_HIST1_57 */
    union {
        struct {
            uint32_t hist1_57_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_57;

    /* 0xBE8 : REG_HIST1_58 */
    union {
        struct {
            uint32_t hist1_58_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_58;

    /* 0xBEC : REG_HIST1_59 */
    union {
        struct {
            uint32_t hist1_59_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_59;

    /* 0xBF0 : REG_HIST1_60 */
    union {
        struct {
            uint32_t hist1_60_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_60;

    /* 0xBF4 : REG_HIST1_61 */
    union {
        struct {
            uint32_t hist1_61_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_61;

    /* 0xBF8 : REG_HIST1_62 */
    union {
        struct {
            uint32_t hist1_62_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_62;

    /* 0xBFC : REG_HIST1_63 */
    union {
        struct {
            uint32_t hist1_63_r                     : 24; /* [23: 0],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } REG_HIST1_63;

    /* 0xC00 : WDR_CURVE_1 */
    union {
        struct {
            uint32_t curve_0_pre                    : 10; /* [ 9: 0],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t curve_1_pre                    : 10; /* [25:16],        r/w,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_CURVE_1;

    /* 0xC04 : WDR_CURVE_2 */
    union {
        struct {
            uint32_t curve_2_pre                    : 10; /* [ 9: 0],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t curve_3_pre                    : 10; /* [25:16],        r/w,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_CURVE_2;

    /* 0xC08 : WDR_CURVE_3 */
    union {
        struct {
            uint32_t curve_4_pre                    : 10; /* [ 9: 0],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t curve_5_pre                    : 10; /* [25:16],        r/w,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_CURVE_3;

    /* 0xC0C : WDR_CURVE_4 */
    union {
        struct {
            uint32_t curve_6_pre                    : 10; /* [ 9: 0],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t curve_7_pre                    : 10; /* [25:16],        r/w,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_CURVE_4;

    /* 0xC10 : WDR_CURVE_5 */
    union {
        struct {
            uint32_t curve_8_pre                    : 10; /* [ 9: 0],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t curve_9_pre                    : 10; /* [25:16],        r/w,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_CURVE_5;

    /* 0xC14 : WDR_CURVE_6 */
    union {
        struct {
            uint32_t curve_10_pre                   : 10; /* [ 9: 0],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t curve_11_pre                   : 10; /* [25:16],        r/w,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_CURVE_6;

    /* 0xC18 : WDR_CURVE_7 */
    union {
        struct {
            uint32_t curve_12_pre                   : 10; /* [ 9: 0],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t curve_13_pre                   : 10; /* [25:16],        r/w,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_CURVE_7;

    /* 0xC1C : WDR_CURVE_8 */
    union {
        struct {
            uint32_t curve_14_pre                   : 10; /* [ 9: 0],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t curve_15_pre                   : 10; /* [25:16],        r/w,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_CURVE_8;

    /* 0xC20 : WDR_CURVE_9 */
    union {
        struct {
            uint32_t curve_16_pre                   : 10; /* [ 9: 0],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t curve_17_pre                   : 10; /* [25:16],        r/w,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_CURVE_9;

    /* 0xC24 : WDR_CURVE_10 */
    union {
        struct {
            uint32_t curve_18_pre                   : 10; /* [ 9: 0],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t curve_19_pre                   : 10; /* [25:16],        r/w,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_CURVE_10;

    /* 0xC28 : WDR_CURVE_11 */
    union {
        struct {
            uint32_t curve_20_pre                   : 10; /* [ 9: 0],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t curve_21_pre                   : 10; /* [25:16],        r/w,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_CURVE_11;

    /* 0xC2C : WDR_CURVE_12 */
    union {
        struct {
            uint32_t curve_22_pre                   : 10; /* [ 9: 0],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t curve_23_pre                   : 10; /* [25:16],        r/w,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_CURVE_12;

    /* 0xC30 : WDR_CURVE_13 */
    union {
        struct {
            uint32_t curve_24_pre                   : 10; /* [ 9: 0],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t curve_25_pre                   : 10; /* [25:16],        r/w,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_CURVE_13;

    /* 0xC34 : WDR_CURVE_14 */
    union {
        struct {
            uint32_t curve_26_pre                   : 10; /* [ 9: 0],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t curve_27_pre                   : 10; /* [25:16],        r/w,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_CURVE_14;

    /* 0xC38 : WDR_CURVE_15 */
    union {
        struct {
            uint32_t curve_28_pre                   : 10; /* [ 9: 0],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t curve_29_pre                   : 10; /* [25:16],        r/w,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_CURVE_15;

    /* 0xC3C : WDR_CURVE_16 */
    union {
        struct {
            uint32_t curve_30_pre                   : 10; /* [ 9: 0],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t curve_31_pre                   : 10; /* [25:16],        r/w,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_CURVE_16;

    /* 0xC40 : WDR_CURVE_17 */
    union {
        struct {
            uint32_t curve_32_pre                   : 10; /* [ 9: 0],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t curve_33_pre                   : 10; /* [25:16],        r/w,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_CURVE_17;

    /* 0xC44 : WDR_CURVE_18 */
    union {
        struct {
            uint32_t curve_34_pre                   : 10; /* [ 9: 0],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t curve_35_pre                   : 10; /* [25:16],        r/w,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_CURVE_18;

    /* 0xC48 : WDR_CURVE_19 */
    union {
        struct {
            uint32_t curve_36_pre                   : 10; /* [ 9: 0],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t curve_37_pre                   : 10; /* [25:16],        r/w,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_CURVE_19;

    /* 0xC4C : WDR_CURVE_20 */
    union {
        struct {
            uint32_t curve_38_pre                   : 10; /* [ 9: 0],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t curve_39_pre                   : 10; /* [25:16],        r/w,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_CURVE_20;

    /* 0xC50 : WDR_CURVE_21 */
    union {
        struct {
            uint32_t curve_40_pre                   : 10; /* [ 9: 0],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t curve_41_pre                   : 10; /* [25:16],        r/w,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_CURVE_21;

    /* 0xC54 : WDR_CURVE_22 */
    union {
        struct {
            uint32_t curve_42_pre                   : 10; /* [ 9: 0],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t curve_43_pre                   : 10; /* [25:16],        r/w,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_CURVE_22;

    /* 0xC58 : WDR_CURVE_23 */
    union {
        struct {
            uint32_t curve_44_pre                   : 10; /* [ 9: 0],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t curve_45_pre                   : 10; /* [25:16],        r/w,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_CURVE_23;

    /* 0xC5C : WDR_CURVE_24 */
    union {
        struct {
            uint32_t curve_46_pre                   : 10; /* [ 9: 0],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t curve_47_pre                   : 10; /* [25:16],        r/w,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_CURVE_24;

    /* 0xC60 : WDR_CURVE_25 */
    union {
        struct {
            uint32_t curve_48_pre                   : 10; /* [ 9: 0],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t curve_49_pre                   : 10; /* [25:16],        r/w,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_CURVE_25;

    /* 0xC64 : WDR_CURVE_26 */
    union {
        struct {
            uint32_t curve_50_pre                   : 10; /* [ 9: 0],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t curve_51_pre                   : 10; /* [25:16],        r/w,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_CURVE_26;

    /* 0xC68 : WDR_CURVE_27 */
    union {
        struct {
            uint32_t curve_52_pre                   : 10; /* [ 9: 0],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t curve_53_pre                   : 10; /* [25:16],        r/w,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_CURVE_27;

    /* 0xC6C : WDR_CURVE_28 */
    union {
        struct {
            uint32_t curve_54_pre                   : 10; /* [ 9: 0],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t curve_55_pre                   : 10; /* [25:16],        r/w,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_CURVE_28;

    /* 0xC70 : WDR_CURVE_29 */
    union {
        struct {
            uint32_t curve_56_pre                   : 10; /* [ 9: 0],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t curve_57_pre                   : 10; /* [25:16],        r/w,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_CURVE_29;

    /* 0xC74 : WDR_CURVE_30 */
    union {
        struct {
            uint32_t curve_58_pre                   : 10; /* [ 9: 0],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t curve_59_pre                   : 10; /* [25:16],        r/w,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_CURVE_30;

    /* 0xC78 : WDR_CURVE_31 */
    union {
        struct {
            uint32_t curve_60_pre                   : 10; /* [ 9: 0],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t curve_61_pre                   : 10; /* [25:16],        r/w,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_CURVE_31;

    /* 0xC7C : WDR_CURVE_32 */
    union {
        struct {
            uint32_t curve_62_pre                   : 10; /* [ 9: 0],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t curve_63_pre                   : 10; /* [25:16],        r/w,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_CURVE_32;

    /* 0xC80 : WDR_CURVE_33 */
    union {
        struct {
            uint32_t curve_en_pre                   :  1; /* [    0],        r/w,        0x0 */
            uint32_t reserved_1_7                   :  7; /* [ 7: 1],       rsvd,        0x0 */
            uint32_t curve_weight_pre               :  5; /* [12: 8],        r/w,        0x0 */
            uint32_t reserved_13_31                 : 19; /* [31:13],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_CURVE_33;

    /* 0xC84 : WDR_ENH_1 */
    union {
        struct {
            uint32_t enh_en_pre                     :  1; /* [    0],        r/w,        0x0 */
            uint32_t reserved_1_7                   :  7; /* [ 7: 1],       rsvd,        0x0 */
            uint32_t enh_weight_pre                 :  5; /* [12: 8],        r/w,        0x0 */
            uint32_t reserved_13_15                 :  3; /* [15:13],       rsvd,        0x0 */
            uint32_t enh_y_offset_pre               : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_ENH_1;

    /* 0xC88 : WDR_ENH_2 */
    union {
        struct {
            uint32_t enh_c_gain_pre                 : 15; /* [14: 0],        r/w,        0x0 */
            uint32_t reserved_15                    :  1; /* [   15],       rsvd,        0x0 */
            uint32_t enh_y_gain_pre                 : 15; /* [30:16],        r/w,        0x0 */
            uint32_t reserved_31                    :  1; /* [   31],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } WDR_ENH_2;

    /* 0xc8c  reserved */
    uint8_t RESERVED0xc8c[116];

    /* 0xD00 : BL_GAMMA_TABLE_1 */
    union {
        struct {
            uint32_t gamma_table0_pre               : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table1_pre               : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_1;

    /* 0xD04 : BL_GAMMA_TABLE_2 */
    union {
        struct {
            uint32_t gamma_table2_pre               : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table3_pre               : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_2;

    /* 0xD08 : BL_GAMMA_TABLE_3 */
    union {
        struct {
            uint32_t gamma_table4_pre               : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table5_pre               : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_3;

    /* 0xD0C : BL_GAMMA_TABLE_4 */
    union {
        struct {
            uint32_t gamma_table6_pre               : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table7_pre               : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_4;

    /* 0xD10 : BL_GAMMA_TABLE_5 */
    union {
        struct {
            uint32_t gamma_table8_pre               : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table9_pre               : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_5;

    /* 0xD14 : BL_GAMMA_TABLE_6 */
    union {
        struct {
            uint32_t gamma_table10_pre              : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table11_pre              : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_6;

    /* 0xD18 : BL_GAMMA_TABLE_7 */
    union {
        struct {
            uint32_t gamma_table12_pre              : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table13_pre              : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_7;

    /* 0xD1C : BL_GAMMA_TABLE_8 */
    union {
        struct {
            uint32_t gamma_table14_pre              : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table15_pre              : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_8;

    /* 0xD20 : BL_GAMMA_TABLE_9 */
    union {
        struct {
            uint32_t gamma_table16_pre              : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table17_pre              : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_9;

    /* 0xD24 : BL_GAMMA_TABLE_10 */
    union {
        struct {
            uint32_t gamma_table18_pre              : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table19_pre              : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_10;

    /* 0xD28 : BL_GAMMA_TABLE_11 */
    union {
        struct {
            uint32_t gamma_table20_pre              : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table21_pre              : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_11;

    /* 0xD2C : BL_GAMMA_TABLE_12 */
    union {
        struct {
            uint32_t gamma_table22_pre              : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table23_pre              : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_12;

    /* 0xD30 : BL_GAMMA_TABLE_13 */
    union {
        struct {
            uint32_t gamma_table24_pre              : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table25_pre              : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_13;

    /* 0xD34 : BL_GAMMA_TABLE_14 */
    union {
        struct {
            uint32_t gamma_table26_pre              : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table27_pre              : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_14;

    /* 0xD38 : BL_GAMMA_TABLE_15 */
    union {
        struct {
            uint32_t gamma_table28_pre              : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table29_pre              : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_15;

    /* 0xD3C : BL_GAMMA_TABLE_16 */
    union {
        struct {
            uint32_t gamma_table30_pre              : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table31_pre              : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_16;

    /* 0xD40 : BL_GAMMA_TABLE_17 */
    union {
        struct {
            uint32_t gamma_table32_pre              : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table33_pre              : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_17;

    /* 0xD44 : BL_GAMMA_TABLE_18 */
    union {
        struct {
            uint32_t gamma_table34_pre              : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table35_pre              : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_18;

    /* 0xD48 : BL_GAMMA_TABLE_19 */
    union {
        struct {
            uint32_t gamma_table36_pre              : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table37_pre              : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_19;

    /* 0xD4C : BL_GAMMA_TABLE_20 */
    union {
        struct {
            uint32_t gamma_table38_pre              : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table39_pre              : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_20;

    /* 0xD50 : BL_GAMMA_TABLE_21 */
    union {
        struct {
            uint32_t gamma_table40_pre              : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table41_pre              : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_21;

    /* 0xD54 : BL_GAMMA_TABLE_22 */
    union {
        struct {
            uint32_t gamma_table42_pre              : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table43_pre              : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_22;

    /* 0xD58 : BL_GAMMA_TABLE_23 */
    union {
        struct {
            uint32_t gamma_table44_pre              : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table45_pre              : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_23;

    /* 0xD5C : BL_GAMMA_TABLE_24 */
    union {
        struct {
            uint32_t gamma_table46_pre              : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table47_pre              : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_24;

    /* 0xD60 : BL_GAMMA_TABLE_25 */
    union {
        struct {
            uint32_t gamma_table48_pre              : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table49_pre              : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_25;

    /* 0xD64 : BL_GAMMA_TABLE_26 */
    union {
        struct {
            uint32_t gamma_table50_pre              : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table51_pre              : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_26;

    /* 0xD68 : BL_GAMMA_TABLE_27 */
    union {
        struct {
            uint32_t gamma_table52_pre              : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table53_pre              : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_27;

    /* 0xD6C : BL_GAMMA_TABLE_28 */
    union {
        struct {
            uint32_t gamma_table54_pre              : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table55_pre              : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_28;

    /* 0xD70 : BL_GAMMA_TABLE_29 */
    union {
        struct {
            uint32_t gamma_table56_pre              : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table57_pre              : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_29;

    /* 0xD74 : BL_GAMMA_TABLE_30 */
    union {
        struct {
            uint32_t gamma_table58_pre              : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table59_pre              : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_30;

    /* 0xD78 : BL_GAMMA_TABLE_31 */
    union {
        struct {
            uint32_t gamma_table60_pre              : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table61_pre              : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_31;

    /* 0xD7C : BL_GAMMA_TABLE_32 */
    union {
        struct {
            uint32_t gamma_table62_pre              : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table63_pre              : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_32;

    /* 0xD80 : BL_GAMMA_TABLE_33 */
    union {
        struct {
            uint32_t gamma_table64_pre              : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table65_pre              : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_33;

    /* 0xD84 : BL_GAMMA_TABLE_34 */
    union {
        struct {
            uint32_t gamma_table66_pre              : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table67_pre              : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_34;

    /* 0xD88 : BL_GAMMA_TABLE_35 */
    union {
        struct {
            uint32_t gamma_table68_pre              : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table69_pre              : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_35;

    /* 0xD8C : BL_GAMMA_TABLE_36 */
    union {
        struct {
            uint32_t gamma_table70_pre              : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table71_pre              : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_36;

    /* 0xD90 : BL_GAMMA_TABLE_37 */
    union {
        struct {
            uint32_t gamma_table72_pre              : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table73_pre              : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_37;

    /* 0xD94 : BL_GAMMA_TABLE_38 */
    union {
        struct {
            uint32_t gamma_table74_pre              : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table75_pre              : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_38;

    /* 0xD98 : BL_GAMMA_TABLE_39 */
    union {
        struct {
            uint32_t gamma_table76_pre              : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table77_pre              : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_39;

    /* 0xD9C : BL_GAMMA_TABLE_40 */
    union {
        struct {
            uint32_t gamma_table78_pre              : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table79_pre              : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_40;

    /* 0xDA0 : BL_GAMMA_TABLE_41 */
    union {
        struct {
            uint32_t gamma_table80_pre              : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table81_pre              : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_41;

    /* 0xDA4 : BL_GAMMA_TABLE_42 */
    union {
        struct {
            uint32_t gamma_table82_pre              : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table83_pre              : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_42;

    /* 0xDA8 : BL_GAMMA_TABLE_43 */
    union {
        struct {
            uint32_t gamma_table84_pre              : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table85_pre              : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_43;

    /* 0xDAC : BL_GAMMA_TABLE_44 */
    union {
        struct {
            uint32_t gamma_table86_pre              : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table87_pre              : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_44;

    /* 0xDB0 : BL_GAMMA_TABLE_45 */
    union {
        struct {
            uint32_t gamma_table88_pre              : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table89_pre              : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_45;

    /* 0xDB4 : BL_GAMMA_TABLE_46 */
    union {
        struct {
            uint32_t gamma_table90_pre              : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table91_pre              : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_46;

    /* 0xDB8 : BL_GAMMA_TABLE_47 */
    union {
        struct {
            uint32_t gamma_table92_pre              : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table93_pre              : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_47;

    /* 0xDBC : BL_GAMMA_TABLE_48 */
    union {
        struct {
            uint32_t gamma_table94_pre              : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table95_pre              : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_48;

    /* 0xDC0 : BL_GAMMA_TABLE_49 */
    union {
        struct {
            uint32_t gamma_table96_pre              : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table97_pre              : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_49;

    /* 0xDC4 : BL_GAMMA_TABLE_50 */
    union {
        struct {
            uint32_t gamma_table98_pre              : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table99_pre              : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_50;

    /* 0xDC8 : BL_GAMMA_TABLE_51 */
    union {
        struct {
            uint32_t gamma_table100_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table101_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_51;

    /* 0xDCC : BL_GAMMA_TABLE_52 */
    union {
        struct {
            uint32_t gamma_table102_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table103_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_52;

    /* 0xDD0 : BL_GAMMA_TABLE_53 */
    union {
        struct {
            uint32_t gamma_table104_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table105_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_53;

    /* 0xDD4 : BL_GAMMA_TABLE_54 */
    union {
        struct {
            uint32_t gamma_table106_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table107_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_54;

    /* 0xDD8 : BL_GAMMA_TABLE_55 */
    union {
        struct {
            uint32_t gamma_table108_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table109_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_55;

    /* 0xDDC : BL_GAMMA_TABLE_56 */
    union {
        struct {
            uint32_t gamma_table110_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table111_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_56;

    /* 0xDE0 : BL_GAMMA_TABLE_57 */
    union {
        struct {
            uint32_t gamma_table112_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table113_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_57;

    /* 0xDE4 : BL_GAMMA_TABLE_58 */
    union {
        struct {
            uint32_t gamma_table114_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table115_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_58;

    /* 0xDE8 : BL_GAMMA_TABLE_59 */
    union {
        struct {
            uint32_t gamma_table116_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table117_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_59;

    /* 0xDEC : BL_GAMMA_TABLE_60 */
    union {
        struct {
            uint32_t gamma_table118_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table119_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_60;

    /* 0xDF0 : BL_GAMMA_TABLE_61 */
    union {
        struct {
            uint32_t gamma_table120_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table121_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_61;

    /* 0xDF4 : BL_GAMMA_TABLE_62 */
    union {
        struct {
            uint32_t gamma_table122_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table123_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_62;

    /* 0xDF8 : BL_GAMMA_TABLE_63 */
    union {
        struct {
            uint32_t gamma_table124_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table125_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_63;

    /* 0xDFC : BL_GAMMA_TABLE_64 */
    union {
        struct {
            uint32_t gamma_table126_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table127_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_64;

    /* 0xE00 : BL_GAMMA_TABLE_65 */
    union {
        struct {
            uint32_t gamma_table128_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table129_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_65;

    /* 0xE04 : BL_GAMMA_TABLE_66 */
    union {
        struct {
            uint32_t gamma_table130_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table131_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_66;

    /* 0xE08 : BL_GAMMA_TABLE_67 */
    union {
        struct {
            uint32_t gamma_table132_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table133_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_67;

    /* 0xE0C : BL_GAMMA_TABLE_68 */
    union {
        struct {
            uint32_t gamma_table134_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table135_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_68;

    /* 0xE10 : BL_GAMMA_TABLE_69 */
    union {
        struct {
            uint32_t gamma_table136_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table137_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_69;

    /* 0xE14 : BL_GAMMA_TABLE_70 */
    union {
        struct {
            uint32_t gamma_table138_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table139_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_70;

    /* 0xE18 : BL_GAMMA_TABLE_71 */
    union {
        struct {
            uint32_t gamma_table140_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table141_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_71;

    /* 0xE1C : BL_GAMMA_TABLE_72 */
    union {
        struct {
            uint32_t gamma_table142_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table143_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_72;

    /* 0xE20 : BL_GAMMA_TABLE_73 */
    union {
        struct {
            uint32_t gamma_table144_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table145_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_73;

    /* 0xE24 : BL_GAMMA_TABLE_74 */
    union {
        struct {
            uint32_t gamma_table146_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table147_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_74;

    /* 0xE28 : BL_GAMMA_TABLE_75 */
    union {
        struct {
            uint32_t gamma_table148_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table149_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_75;

    /* 0xE2C : BL_GAMMA_TABLE_76 */
    union {
        struct {
            uint32_t gamma_table150_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table151_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_76;

    /* 0xE30 : BL_GAMMA_TABLE_77 */
    union {
        struct {
            uint32_t gamma_table152_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table153_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_77;

    /* 0xE34 : BL_GAMMA_TABLE_78 */
    union {
        struct {
            uint32_t gamma_table154_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table155_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_78;

    /* 0xE38 : BL_GAMMA_TABLE_79 */
    union {
        struct {
            uint32_t gamma_table156_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table157_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_79;

    /* 0xE3C : BL_GAMMA_TABLE_80 */
    union {
        struct {
            uint32_t gamma_table158_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table159_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_80;

    /* 0xE40 : BL_GAMMA_TABLE_81 */
    union {
        struct {
            uint32_t gamma_table160_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table161_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_81;

    /* 0xE44 : BL_GAMMA_TABLE_82 */
    union {
        struct {
            uint32_t gamma_table162_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table163_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_82;

    /* 0xE48 : BL_GAMMA_TABLE_83 */
    union {
        struct {
            uint32_t gamma_table164_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table165_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_83;

    /* 0xE4C : BL_GAMMA_TABLE_84 */
    union {
        struct {
            uint32_t gamma_table166_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table167_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_84;

    /* 0xE50 : BL_GAMMA_TABLE_85 */
    union {
        struct {
            uint32_t gamma_table168_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table169_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_85;

    /* 0xE54 : BL_GAMMA_TABLE_86 */
    union {
        struct {
            uint32_t gamma_table170_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table171_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_86;

    /* 0xE58 : BL_GAMMA_TABLE_87 */
    union {
        struct {
            uint32_t gamma_table172_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table173_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_87;

    /* 0xE5C : BL_GAMMA_TABLE_88 */
    union {
        struct {
            uint32_t gamma_table174_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table175_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_88;

    /* 0xE60 : BL_GAMMA_TABLE_89 */
    union {
        struct {
            uint32_t gamma_table176_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table177_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_89;

    /* 0xE64 : BL_GAMMA_TABLE_90 */
    union {
        struct {
            uint32_t gamma_table178_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table179_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_90;

    /* 0xE68 : BL_GAMMA_TABLE_91 */
    union {
        struct {
            uint32_t gamma_table180_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table181_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_91;

    /* 0xE6C : BL_GAMMA_TABLE_92 */
    union {
        struct {
            uint32_t gamma_table182_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table183_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_92;

    /* 0xE70 : BL_GAMMA_TABLE_93 */
    union {
        struct {
            uint32_t gamma_table184_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table185_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_93;

    /* 0xE74 : BL_GAMMA_TABLE_94 */
    union {
        struct {
            uint32_t gamma_table186_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table187_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_94;

    /* 0xE78 : BL_GAMMA_TABLE_95 */
    union {
        struct {
            uint32_t gamma_table188_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table189_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_95;

    /* 0xE7C : BL_GAMMA_TABLE_96 */
    union {
        struct {
            uint32_t gamma_table190_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table191_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_96;

    /* 0xE80 : BL_GAMMA_TABLE_97 */
    union {
        struct {
            uint32_t gamma_table192_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table193_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_97;

    /* 0xE84 : BL_GAMMA_TABLE_98 */
    union {
        struct {
            uint32_t gamma_table194_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table195_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_98;

    /* 0xE88 : BL_GAMMA_TABLE_99 */
    union {
        struct {
            uint32_t gamma_table196_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table197_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_99;

    /* 0xE8C : BL_GAMMA_TABLE_100 */
    union {
        struct {
            uint32_t gamma_table198_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table199_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_100;

    /* 0xE90 : BL_GAMMA_TABLE_101 */
    union {
        struct {
            uint32_t gamma_table200_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table201_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_101;

    /* 0xE94 : BL_GAMMA_TABLE_102 */
    union {
        struct {
            uint32_t gamma_table202_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table203_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_102;

    /* 0xE98 : BL_GAMMA_TABLE_103 */
    union {
        struct {
            uint32_t gamma_table204_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table205_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_103;

    /* 0xE9C : BL_GAMMA_TABLE_104 */
    union {
        struct {
            uint32_t gamma_table206_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table207_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_104;

    /* 0xEA0 : BL_GAMMA_TABLE_105 */
    union {
        struct {
            uint32_t gamma_table208_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table209_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_105;

    /* 0xEA4 : BL_GAMMA_TABLE_106 */
    union {
        struct {
            uint32_t gamma_table210_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table211_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_106;

    /* 0xEA8 : BL_GAMMA_TABLE_107 */
    union {
        struct {
            uint32_t gamma_table212_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table213_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_107;

    /* 0xEAC : BL_GAMMA_TABLE_108 */
    union {
        struct {
            uint32_t gamma_table214_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table215_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_108;

    /* 0xEB0 : BL_GAMMA_TABLE_109 */
    union {
        struct {
            uint32_t gamma_table216_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table217_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_109;

    /* 0xEB4 : BL_GAMMA_TABLE_110 */
    union {
        struct {
            uint32_t gamma_table218_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table219_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_110;

    /* 0xEB8 : BL_GAMMA_TABLE_111 */
    union {
        struct {
            uint32_t gamma_table220_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table221_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_111;

    /* 0xEBC : BL_GAMMA_TABLE_112 */
    union {
        struct {
            uint32_t gamma_table222_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table223_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_112;

    /* 0xEC0 : BL_GAMMA_TABLE_113 */
    union {
        struct {
            uint32_t gamma_table224_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table225_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_113;

    /* 0xEC4 : BL_GAMMA_TABLE_114 */
    union {
        struct {
            uint32_t gamma_table226_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table227_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_114;

    /* 0xEC8 : BL_GAMMA_TABLE_115 */
    union {
        struct {
            uint32_t gamma_table228_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table229_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_115;

    /* 0xECC : BL_GAMMA_TABLE_116 */
    union {
        struct {
            uint32_t gamma_table230_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table231_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_116;

    /* 0xED0 : BL_GAMMA_TABLE_117 */
    union {
        struct {
            uint32_t gamma_table232_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table233_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_117;

    /* 0xED4 : BL_GAMMA_TABLE_118 */
    union {
        struct {
            uint32_t gamma_table234_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table235_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_118;

    /* 0xED8 : BL_GAMMA_TABLE_119 */
    union {
        struct {
            uint32_t gamma_table236_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table237_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_119;

    /* 0xEDC : BL_GAMMA_TABLE_120 */
    union {
        struct {
            uint32_t gamma_table238_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table239_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_120;

    /* 0xEE0 : BL_GAMMA_TABLE_121 */
    union {
        struct {
            uint32_t gamma_table240_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table241_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_121;

    /* 0xEE4 : BL_GAMMA_TABLE_122 */
    union {
        struct {
            uint32_t gamma_table242_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table243_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_122;

    /* 0xEE8 : BL_GAMMA_TABLE_123 */
    union {
        struct {
            uint32_t gamma_table244_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table245_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_123;

    /* 0xEEC : BL_GAMMA_TABLE_124 */
    union {
        struct {
            uint32_t gamma_table246_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table247_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_124;

    /* 0xEF0 : BL_GAMMA_TABLE_125 */
    union {
        struct {
            uint32_t gamma_table248_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table249_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_125;

    /* 0xEF4 : BL_GAMMA_TABLE_126 */
    union {
        struct {
            uint32_t gamma_table250_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table251_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_126;

    /* 0xEF8 : BL_GAMMA_TABLE_127 */
    union {
        struct {
            uint32_t gamma_table252_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table253_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_127;

    /* 0xEFC : BL_GAMMA_TABLE_128 */
    union {
        struct {
            uint32_t gamma_table254_pre             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t gamma_table255_pre             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BL_GAMMA_TABLE_128;

    /* 0xF00 : CC_OFFSET_0 */
    union {
        struct {
            uint32_t cc_pre_offset0_pre             : 13; /* [12: 0],        r/w,        0x0 */
            uint32_t reserved_13_15                 :  3; /* [15:13],       rsvd,        0x0 */
            uint32_t cc_pre_offset1_pre             : 13; /* [28:16],        r/w,        0x0 */
            uint32_t reserved_29_30                 :  2; /* [30:29],       rsvd,        0x0 */
            uint32_t cc_enable_pre                  :  1; /* [   31],        r/w,        0x1 */
        }BF;
        uint32_t WORD;
    } CC_OFFSET_0;

    /* 0xF04 : CC_OFFSET_1 */
    union {
        struct {
            uint32_t cc_pre_offset2_pre             : 13; /* [12: 0],        r/w,        0x0 */
            uint32_t reserved_13_15                 :  3; /* [15:13],       rsvd,        0x0 */
            uint32_t cc_post_offset2_pre            : 13; /* [28:16],        r/w,        0x0 */
            uint32_t reserved_29_31                 :  3; /* [31:29],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } CC_OFFSET_1;

    /* 0xF08 : CC_OFFSET_2 */
    union {
        struct {
            uint32_t cc_post_offset0_pre            : 13; /* [12: 0],        r/w,        0x0 */
            uint32_t reserved_13_15                 :  3; /* [15:13],       rsvd,        0x0 */
            uint32_t cc_post_offset1_pre            : 13; /* [28:16],        r/w,        0x0 */
            uint32_t reserved_29_31                 :  3; /* [31:29],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } CC_OFFSET_2;

    /* 0xF0C : CC_MATRIX_0 */
    union {
        struct {
            uint32_t cc_matrix00_pre                : 12; /* [11: 0],        r/w,      0x200 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t cc_matrix01_pre                : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } CC_MATRIX_0;

    /* 0xF10 : CC_MATRIX_1 */
    union {
        struct {
            uint32_t cc_matrix10_pre                : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t cc_matrix02_pre                : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } CC_MATRIX_1;

    /* 0xF14 : CC_MATRIX_2 */
    union {
        struct {
            uint32_t cc_matrix11_pre                : 12; /* [11: 0],        r/w,      0x200 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t cc_matrix12_pre                : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } CC_MATRIX_2;

    /* 0xF18 : CC_MATRIX_3 */
    union {
        struct {
            uint32_t cc_matrix20_pre                : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t cc_matrix21_pre                : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } CC_MATRIX_3;

    /* 0xF1C : CC_CE_MATRIX */
    union {
        struct {
            uint32_t cc_matrix22_pre                : 12; /* [11: 0],        r/w,      0x200 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t ce_matrix02_pre                : 12; /* [27:16],        r/w,       0x3a */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } CC_CE_MATRIX;

    /* 0xF20 : CE_MATRIX_0 */
    union {
        struct {
            uint32_t ce_matrix00_pre                : 12; /* [11: 0],        r/w,       0x99 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t ce_matrix01_pre                : 12; /* [27:16],        r/w,      0x12d */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } CE_MATRIX_0;

    /* 0xF24 : CE_MATRIX_1 */
    union {
        struct {
            uint32_t ce_matrix10_pre                : 12; /* [11: 0],        r/w,      0xfa9 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t ce_matrix11_pre                : 12; /* [27:16],        r/w,      0xf57 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } CE_MATRIX_1;

    /* 0xF28 : CE_MATRIX_2 */
    union {
        struct {
            uint32_t ce_matrix20_pre                : 12; /* [11: 0],        r/w,      0x100 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t ce_matrix12_pre                : 12; /* [27:16],        r/w,      0x100 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } CE_MATRIX_2;

    /* 0xF2C : CE_MATRIX_3 */
    union {
        struct {
            uint32_t ce_matrix21_pre                : 12; /* [11: 0],        r/w,      0xf29 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t ce_matrix22_pre                : 12; /* [27:16],        r/w,      0xfd7 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } CE_MATRIX_3;

    /* 0xF30 : CE_OFFSET_0 */
    union {
        struct {
            uint32_t ce_pre_offset0_pre             : 13; /* [12: 0],        r/w,        0x0 */
            uint32_t reserved_13_15                 :  3; /* [15:13],       rsvd,        0x0 */
            uint32_t ce_pre_offset1_pre             : 13; /* [28:16],        r/w,        0x0 */
            uint32_t reserved_29_31                 :  3; /* [31:29],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } CE_OFFSET_0;

    /* 0xF34 : CE_OFFSET_1 */
    union {
        struct {
            uint32_t ce_pre_offset2_pre             : 13; /* [12: 0],        r/w,        0x0 */
            uint32_t reserved_13_15                 :  3; /* [15:13],       rsvd,        0x0 */
            uint32_t ce_post_offset2_pre            : 13; /* [28:16],        r/w,      0x800 */
            uint32_t reserved_29_31                 :  3; /* [31:29],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } CE_OFFSET_1;

    /* 0xF38 : CE_OFFSET_2 */
    union {
        struct {
            uint32_t ce_post_offset0_pre            : 13; /* [12: 0],        r/w,        0x0 */
            uint32_t reserved_13_15                 :  3; /* [15:13],       rsvd,        0x0 */
            uint32_t ce_post_offset1_pre            : 13; /* [28:16],        r/w,      0x800 */
            uint32_t reserved_29_31                 :  3; /* [31:29],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } CE_OFFSET_2;

};

typedef volatile struct dsp2_blback_reg dsp2_blback_reg_t;


#endif  /* __DSP2_BLBACK_REG_H__ */
