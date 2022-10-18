/**
  ******************************************************************************
  * @file    dsp2_misc_reg.h
  * @version V1.2
  * @date    2019-07-03
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
#ifndef  __DSP2_MISC_REG_H__
#define  __DSP2_MISC_REG_H__

#include "bl808.h"

/* 0x0 : config */
#define DSP2_MISC_CONFIG_OFFSET                                  (0x0)
#define DSP2_MISC_RG_DVP_MUX_HDMI_SEL                            DSP2_MISC_RG_DVP_MUX_HDMI_SEL
#define DSP2_MISC_RG_DVP_MUX_HDMI_SEL_POS                        (0U)
#define DSP2_MISC_RG_DVP_MUX_HDMI_SEL_LEN                        (1U)
#define DSP2_MISC_RG_DVP_MUX_HDMI_SEL_MSK                        (((1U<<DSP2_MISC_RG_DVP_MUX_HDMI_SEL_LEN)-1)<<DSP2_MISC_RG_DVP_MUX_HDMI_SEL_POS)
#define DSP2_MISC_RG_DVP_MUX_HDMI_SEL_UMSK                       (~(((1U<<DSP2_MISC_RG_DVP_MUX_HDMI_SEL_LEN)-1)<<DSP2_MISC_RG_DVP_MUX_HDMI_SEL_POS))
#define DSP2_MISC_DVP_MUX_CH4_SEL                                DSP2_MISC_DVP_MUX_CH4_SEL
#define DSP2_MISC_DVP_MUX_CH4_SEL_POS                            (1U)
#define DSP2_MISC_DVP_MUX_CH4_SEL_LEN                            (1U)
#define DSP2_MISC_DVP_MUX_CH4_SEL_MSK                            (((1U<<DSP2_MISC_DVP_MUX_CH4_SEL_LEN)-1)<<DSP2_MISC_DVP_MUX_CH4_SEL_POS)
#define DSP2_MISC_DVP_MUX_CH4_SEL_UMSK                           (~(((1U<<DSP2_MISC_DVP_MUX_CH4_SEL_LEN)-1)<<DSP2_MISC_DVP_MUX_CH4_SEL_POS))
#define DSP2_MISC_CR_DSP2_DE_AS_HSYNC                             DSP2_MISC_CR_DSP2_DE_AS_HSYNC
#define DSP2_MISC_CR_DSP2_DE_AS_HSYNC_POS                         (2U)
#define DSP2_MISC_CR_DSP2_DE_AS_HSYNC_LEN                         (1U)
#define DSP2_MISC_CR_DSP2_DE_AS_HSYNC_MSK                         (((1U<<DSP2_MISC_CR_DSP2_DE_AS_HSYNC_LEN)-1)<<DSP2_MISC_CR_DSP2_DE_AS_HSYNC_POS)
#define DSP2_MISC_CR_DSP2_DE_AS_HSYNC_UMSK                        (~(((1U<<DSP2_MISC_CR_DSP2_DE_AS_HSYNC_LEN)-1)<<DSP2_MISC_CR_DSP2_DE_AS_HSYNC_POS))
#define DSP2_MISC_NEW_AE_SEL                                     DSP2_MISC_NEW_AE_SEL
#define DSP2_MISC_NEW_AE_SEL_POS                                 (4U)
#define DSP2_MISC_NEW_AE_SEL_LEN                                 (1U)
#define DSP2_MISC_NEW_AE_SEL_MSK                                 (((1U<<DSP2_MISC_NEW_AE_SEL_LEN)-1)<<DSP2_MISC_NEW_AE_SEL_POS)
#define DSP2_MISC_NEW_AE_SEL_UMSK                                (~(((1U<<DSP2_MISC_NEW_AE_SEL_LEN)-1)<<DSP2_MISC_NEW_AE_SEL_POS))
#define DSP2_MISC_NEW_AWB_SEL                                    DSP2_MISC_NEW_AWB_SEL
#define DSP2_MISC_NEW_AWB_SEL_POS                                (5U)
#define DSP2_MISC_NEW_AWB_SEL_LEN                                (1U)
#define DSP2_MISC_NEW_AWB_SEL_MSK                                (((1U<<DSP2_MISC_NEW_AWB_SEL_LEN)-1)<<DSP2_MISC_NEW_AWB_SEL_POS)
#define DSP2_MISC_NEW_AWB_SEL_UMSK                               (~(((1U<<DSP2_MISC_NEW_AWB_SEL_LEN)-1)<<DSP2_MISC_NEW_AWB_SEL_POS))

/* 0x4 : pix_data_ctrl */
#define DSP2_MISC_PIX_DATA_CTRL_OFFSET                           (0x4)
#define DSP2_MISC_REG_PIX_DATA_CTRL                              DSP2_MISC_REG_PIX_DATA_CTRL
#define DSP2_MISC_REG_PIX_DATA_CTRL_POS                          (0U)
#define DSP2_MISC_REG_PIX_DATA_CTRL_LEN                          (12U)
#define DSP2_MISC_REG_PIX_DATA_CTRL_MSK                          (((1U<<DSP2_MISC_REG_PIX_DATA_CTRL_LEN)-1)<<DSP2_MISC_REG_PIX_DATA_CTRL_POS)
#define DSP2_MISC_REG_PIX_DATA_CTRL_UMSK                         (~(((1U<<DSP2_MISC_REG_PIX_DATA_CTRL_LEN)-1)<<DSP2_MISC_REG_PIX_DATA_CTRL_POS))
#define DSP2_MISC_REG_PIX_DATA_SHT_BIT                           DSP2_MISC_REG_PIX_DATA_SHT_BIT
#define DSP2_MISC_REG_PIX_DATA_SHT_BIT_POS                       (16U)
#define DSP2_MISC_REG_PIX_DATA_SHT_BIT_LEN                       (4U)
#define DSP2_MISC_REG_PIX_DATA_SHT_BIT_MSK                       (((1U<<DSP2_MISC_REG_PIX_DATA_SHT_BIT_LEN)-1)<<DSP2_MISC_REG_PIX_DATA_SHT_BIT_POS)
#define DSP2_MISC_REG_PIX_DATA_SHT_BIT_UMSK                      (~(((1U<<DSP2_MISC_REG_PIX_DATA_SHT_BIT_LEN)-1)<<DSP2_MISC_REG_PIX_DATA_SHT_BIT_POS))
#define DSP2_MISC_REG_PIX_DATA_SHT_DIR                           DSP2_MISC_REG_PIX_DATA_SHT_DIR
#define DSP2_MISC_REG_PIX_DATA_SHT_DIR_POS                       (20U)
#define DSP2_MISC_REG_PIX_DATA_SHT_DIR_LEN                       (1U)
#define DSP2_MISC_REG_PIX_DATA_SHT_DIR_MSK                       (((1U<<DSP2_MISC_REG_PIX_DATA_SHT_DIR_LEN)-1)<<DSP2_MISC_REG_PIX_DATA_SHT_DIR_POS)
#define DSP2_MISC_REG_PIX_DATA_SHT_DIR_UMSK                      (~(((1U<<DSP2_MISC_REG_PIX_DATA_SHT_DIR_LEN)-1)<<DSP2_MISC_REG_PIX_DATA_SHT_DIR_POS))

/* 0x8 : dvp2bus_src_sel */
#define DSP2_MISC_DVP2BUS_SRC_SEL_OFFSET                         (0x8)
#define DSP2_MISC_RG_D2B_DVP_SEL_A                               DSP2_MISC_RG_D2B_DVP_SEL_A
#define DSP2_MISC_RG_D2B_DVP_SEL_A_POS                           (0U)
#define DSP2_MISC_RG_D2B_DVP_SEL_A_LEN                           (8U)
#define DSP2_MISC_RG_D2B_DVP_SEL_A_MSK                           (((1U<<DSP2_MISC_RG_D2B_DVP_SEL_A_LEN)-1)<<DSP2_MISC_RG_D2B_DVP_SEL_A_POS)
#define DSP2_MISC_RG_D2B_DVP_SEL_A_UMSK                          (~(((1U<<DSP2_MISC_RG_D2B_DVP_SEL_A_LEN)-1)<<DSP2_MISC_RG_D2B_DVP_SEL_A_POS))
#define DSP2_MISC_RG_D2B_DVP_SEL_B                               DSP2_MISC_RG_D2B_DVP_SEL_B
#define DSP2_MISC_RG_D2B_DVP_SEL_B_POS                           (8U)
#define DSP2_MISC_RG_D2B_DVP_SEL_B_LEN                           (8U)
#define DSP2_MISC_RG_D2B_DVP_SEL_B_MSK                           (((1U<<DSP2_MISC_RG_D2B_DVP_SEL_B_LEN)-1)<<DSP2_MISC_RG_D2B_DVP_SEL_B_POS)
#define DSP2_MISC_RG_D2B_DVP_SEL_B_UMSK                          (~(((1U<<DSP2_MISC_RG_D2B_DVP_SEL_B_LEN)-1)<<DSP2_MISC_RG_D2B_DVP_SEL_B_POS))
#define DSP2_MISC_RG_D2B_DVP_SEL_C                               DSP2_MISC_RG_D2B_DVP_SEL_C
#define DSP2_MISC_RG_D2B_DVP_SEL_C_POS                           (16U)
#define DSP2_MISC_RG_D2B_DVP_SEL_C_LEN                           (8U)
#define DSP2_MISC_RG_D2B_DVP_SEL_C_MSK                           (((1U<<DSP2_MISC_RG_D2B_DVP_SEL_C_LEN)-1)<<DSP2_MISC_RG_D2B_DVP_SEL_C_POS)
#define DSP2_MISC_RG_D2B_DVP_SEL_C_UMSK                          (~(((1U<<DSP2_MISC_RG_D2B_DVP_SEL_C_LEN)-1)<<DSP2_MISC_RG_D2B_DVP_SEL_C_POS))
#define DSP2_MISC_RG_D2B_DVP_SEL_D                               DSP2_MISC_RG_D2B_DVP_SEL_D
#define DSP2_MISC_RG_D2B_DVP_SEL_D_POS                           (24U)
#define DSP2_MISC_RG_D2B_DVP_SEL_D_LEN                           (8U)
#define DSP2_MISC_RG_D2B_DVP_SEL_D_MSK                           (((1U<<DSP2_MISC_RG_D2B_DVP_SEL_D_LEN)-1)<<DSP2_MISC_RG_D2B_DVP_SEL_D_POS)
#define DSP2_MISC_RG_D2B_DVP_SEL_D_UMSK                          (~(((1U<<DSP2_MISC_RG_D2B_DVP_SEL_D_LEN)-1)<<DSP2_MISC_RG_D2B_DVP_SEL_D_POS))

/* 0xC : dvp_frame_m_to_n */
#define DSP2_MISC_DVP_FRAME_M_TO_N_OFFSET                        (0xC)
#define DSP2_MISC_CR_FRAME_M_TO_N_EN                             DSP2_MISC_CR_FRAME_M_TO_N_EN
#define DSP2_MISC_CR_FRAME_M_TO_N_EN_POS                         (0U)
#define DSP2_MISC_CR_FRAME_M_TO_N_EN_LEN                         (1U)
#define DSP2_MISC_CR_FRAME_M_TO_N_EN_MSK                         (((1U<<DSP2_MISC_CR_FRAME_M_TO_N_EN_LEN)-1)<<DSP2_MISC_CR_FRAME_M_TO_N_EN_POS)
#define DSP2_MISC_CR_FRAME_M_TO_N_EN_UMSK                        (~(((1U<<DSP2_MISC_CR_FRAME_M_TO_N_EN_LEN)-1)<<DSP2_MISC_CR_FRAME_M_TO_N_EN_POS))
#define DSP2_MISC_CR_FRAME_INTERVAL                              DSP2_MISC_CR_FRAME_INTERVAL
#define DSP2_MISC_CR_FRAME_INTERVAL_POS                          (4U)
#define DSP2_MISC_CR_FRAME_INTERVAL_LEN                          (4U)
#define DSP2_MISC_CR_FRAME_INTERVAL_MSK                          (((1U<<DSP2_MISC_CR_FRAME_INTERVAL_LEN)-1)<<DSP2_MISC_CR_FRAME_INTERVAL_POS)
#define DSP2_MISC_CR_FRAME_INTERVAL_UMSK                         (~(((1U<<DSP2_MISC_CR_FRAME_INTERVAL_LEN)-1)<<DSP2_MISC_CR_FRAME_INTERVAL_POS))
#define DSP2_MISC_CR_FRAME_CNT_N                                 DSP2_MISC_CR_FRAME_CNT_N
#define DSP2_MISC_CR_FRAME_CNT_N_POS                             (8U)
#define DSP2_MISC_CR_FRAME_CNT_N_LEN                             (4U)
#define DSP2_MISC_CR_FRAME_CNT_N_MSK                             (((1U<<DSP2_MISC_CR_FRAME_CNT_N_LEN)-1)<<DSP2_MISC_CR_FRAME_CNT_N_POS)
#define DSP2_MISC_CR_FRAME_CNT_N_UMSK                            (~(((1U<<DSP2_MISC_CR_FRAME_CNT_N_LEN)-1)<<DSP2_MISC_CR_FRAME_CNT_N_POS))
#define DSP2_MISC_CR_FRAME_CNT_M                                 DSP2_MISC_CR_FRAME_CNT_M
#define DSP2_MISC_CR_FRAME_CNT_M_POS                             (12U)
#define DSP2_MISC_CR_FRAME_CNT_M_LEN                             (4U)
#define DSP2_MISC_CR_FRAME_CNT_M_MSK                             (((1U<<DSP2_MISC_CR_FRAME_CNT_M_LEN)-1)<<DSP2_MISC_CR_FRAME_CNT_M_POS)
#define DSP2_MISC_CR_FRAME_CNT_M_UMSK                            (~(((1U<<DSP2_MISC_CR_FRAME_CNT_M_LEN)-1)<<DSP2_MISC_CR_FRAME_CNT_M_POS))

/* 0x10 : dsp2_sub_bus_control */
#define DSP2_MISC_DSP2_SUB_BUS_CONTROL_OFFSET                     (0x10)
#define DSP2_MISC_REG_NR3D_AWQOS                                 DSP2_MISC_REG_NR3D_AWQOS
#define DSP2_MISC_REG_NR3D_AWQOS_POS                             (0U)
#define DSP2_MISC_REG_NR3D_AWQOS_LEN                             (1U)
#define DSP2_MISC_REG_NR3D_AWQOS_MSK                             (((1U<<DSP2_MISC_REG_NR3D_AWQOS_LEN)-1)<<DSP2_MISC_REG_NR3D_AWQOS_POS)
#define DSP2_MISC_REG_NR3D_AWQOS_UMSK                            (~(((1U<<DSP2_MISC_REG_NR3D_AWQOS_LEN)-1)<<DSP2_MISC_REG_NR3D_AWQOS_POS))
#define DSP2_MISC_REG_NR3D_ARQOS                                 DSP2_MISC_REG_NR3D_ARQOS
#define DSP2_MISC_REG_NR3D_ARQOS_POS                             (1U)
#define DSP2_MISC_REG_NR3D_ARQOS_LEN                             (1U)
#define DSP2_MISC_REG_NR3D_ARQOS_MSK                             (((1U<<DSP2_MISC_REG_NR3D_ARQOS_LEN)-1)<<DSP2_MISC_REG_NR3D_ARQOS_POS)
#define DSP2_MISC_REG_NR3D_ARQOS_UMSK                            (~(((1U<<DSP2_MISC_REG_NR3D_ARQOS_LEN)-1)<<DSP2_MISC_REG_NR3D_ARQOS_POS))
#define DSP2_MISC_REG_D2BA_AWQOS                                 DSP2_MISC_REG_D2BA_AWQOS
#define DSP2_MISC_REG_D2BA_AWQOS_POS                             (2U)
#define DSP2_MISC_REG_D2BA_AWQOS_LEN                             (1U)
#define DSP2_MISC_REG_D2BA_AWQOS_MSK                             (((1U<<DSP2_MISC_REG_D2BA_AWQOS_LEN)-1)<<DSP2_MISC_REG_D2BA_AWQOS_POS)
#define DSP2_MISC_REG_D2BA_AWQOS_UMSK                            (~(((1U<<DSP2_MISC_REG_D2BA_AWQOS_LEN)-1)<<DSP2_MISC_REG_D2BA_AWQOS_POS))
#define DSP2_MISC_REG_D2BB_AWQOS                                 DSP2_MISC_REG_D2BB_AWQOS
#define DSP2_MISC_REG_D2BB_AWQOS_POS                             (3U)
#define DSP2_MISC_REG_D2BB_AWQOS_LEN                             (1U)
#define DSP2_MISC_REG_D2BB_AWQOS_MSK                             (((1U<<DSP2_MISC_REG_D2BB_AWQOS_LEN)-1)<<DSP2_MISC_REG_D2BB_AWQOS_POS)
#define DSP2_MISC_REG_D2BB_AWQOS_UMSK                            (~(((1U<<DSP2_MISC_REG_D2BB_AWQOS_LEN)-1)<<DSP2_MISC_REG_D2BB_AWQOS_POS))
#define DSP2_MISC_REG_D2BC_AWQOS                                 DSP2_MISC_REG_D2BC_AWQOS
#define DSP2_MISC_REG_D2BC_AWQOS_POS                             (4U)
#define DSP2_MISC_REG_D2BC_AWQOS_LEN                             (1U)
#define DSP2_MISC_REG_D2BC_AWQOS_MSK                             (((1U<<DSP2_MISC_REG_D2BC_AWQOS_LEN)-1)<<DSP2_MISC_REG_D2BC_AWQOS_POS)
#define DSP2_MISC_REG_D2BC_AWQOS_UMSK                            (~(((1U<<DSP2_MISC_REG_D2BC_AWQOS_LEN)-1)<<DSP2_MISC_REG_D2BC_AWQOS_POS))
#define DSP2_MISC_REG_D2BD_AWQOS                                 DSP2_MISC_REG_D2BD_AWQOS
#define DSP2_MISC_REG_D2BD_AWQOS_POS                             (5U)
#define DSP2_MISC_REG_D2BD_AWQOS_LEN                             (1U)
#define DSP2_MISC_REG_D2BD_AWQOS_MSK                             (((1U<<DSP2_MISC_REG_D2BD_AWQOS_LEN)-1)<<DSP2_MISC_REG_D2BD_AWQOS_POS)
#define DSP2_MISC_REG_D2BD_AWQOS_UMSK                            (~(((1U<<DSP2_MISC_REG_D2BD_AWQOS_LEN)-1)<<DSP2_MISC_REG_D2BD_AWQOS_POS))
#define DSP2_MISC_REG_DSP2_DTSRC_ARQOS                            DSP2_MISC_REG_DSP2_DTSRC_ARQOS
#define DSP2_MISC_REG_DSP2_DTSRC_ARQOS_POS                        (6U)
#define DSP2_MISC_REG_DSP2_DTSRC_ARQOS_LEN                        (1U)
#define DSP2_MISC_REG_DSP2_DTSRC_ARQOS_MSK                        (((1U<<DSP2_MISC_REG_DSP2_DTSRC_ARQOS_LEN)-1)<<DSP2_MISC_REG_DSP2_DTSRC_ARQOS_POS)
#define DSP2_MISC_REG_DSP2_DTSRC_ARQOS_UMSK                       (~(((1U<<DSP2_MISC_REG_DSP2_DTSRC_ARQOS_LEN)-1)<<DSP2_MISC_REG_DSP2_DTSRC_ARQOS_POS))
#define DSP2_MISC_REG_HDMI_DTSRC_ARQOS                           DSP2_MISC_REG_HDMI_DTSRC_ARQOS
#define DSP2_MISC_REG_HDMI_DTSRC_ARQOS_POS                       (7U)
#define DSP2_MISC_REG_HDMI_DTSRC_ARQOS_LEN                       (1U)
#define DSP2_MISC_REG_HDMI_DTSRC_ARQOS_MSK                       (((1U<<DSP2_MISC_REG_HDMI_DTSRC_ARQOS_LEN)-1)<<DSP2_MISC_REG_HDMI_DTSRC_ARQOS_POS)
#define DSP2_MISC_REG_HDMI_DTSRC_ARQOS_UMSK                      (~(((1U<<DSP2_MISC_REG_HDMI_DTSRC_ARQOS_LEN)-1)<<DSP2_MISC_REG_HDMI_DTSRC_ARQOS_POS))

/* 0x20 : int_clr */
#define DSP2_MISC_INT_CLR_OFFSET                                 (0x20)
#define DSP2_MISC_RG_AWB_INT_CLR                                 DSP2_MISC_RG_AWB_INT_CLR
#define DSP2_MISC_RG_AWB_INT_CLR_POS                             (0U)
#define DSP2_MISC_RG_AWB_INT_CLR_LEN                             (1U)
#define DSP2_MISC_RG_AWB_INT_CLR_MSK                             (((1U<<DSP2_MISC_RG_AWB_INT_CLR_LEN)-1)<<DSP2_MISC_RG_AWB_INT_CLR_POS)
#define DSP2_MISC_RG_AWB_INT_CLR_UMSK                            (~(((1U<<DSP2_MISC_RG_AWB_INT_CLR_LEN)-1)<<DSP2_MISC_RG_AWB_INT_CLR_POS))
#define DSP2_MISC_RG_AE_INT_CLR                                  DSP2_MISC_RG_AE_INT_CLR
#define DSP2_MISC_RG_AE_INT_CLR_POS                              (1U)
#define DSP2_MISC_RG_AE_INT_CLR_LEN                              (1U)
#define DSP2_MISC_RG_AE_INT_CLR_MSK                              (((1U<<DSP2_MISC_RG_AE_INT_CLR_LEN)-1)<<DSP2_MISC_RG_AE_INT_CLR_POS)
#define DSP2_MISC_RG_AE_INT_CLR_UMSK                             (~(((1U<<DSP2_MISC_RG_AE_INT_CLR_LEN)-1)<<DSP2_MISC_RG_AE_INT_CLR_POS))
#define DSP2_MISC_RG_SEOF1_INT_CLR                               DSP2_MISC_RG_SEOF1_INT_CLR
#define DSP2_MISC_RG_SEOF1_INT_CLR_POS                           (8U)
#define DSP2_MISC_RG_SEOF1_INT_CLR_LEN                           (1U)
#define DSP2_MISC_RG_SEOF1_INT_CLR_MSK                           (((1U<<DSP2_MISC_RG_SEOF1_INT_CLR_LEN)-1)<<DSP2_MISC_RG_SEOF1_INT_CLR_POS)
#define DSP2_MISC_RG_SEOF1_INT_CLR_UMSK                          (~(((1U<<DSP2_MISC_RG_SEOF1_INT_CLR_LEN)-1)<<DSP2_MISC_RG_SEOF1_INT_CLR_POS))
#define DSP2_MISC_RG_SEOF2_INT_CLR                               DSP2_MISC_RG_SEOF2_INT_CLR
#define DSP2_MISC_RG_SEOF2_INT_CLR_POS                           (9U)
#define DSP2_MISC_RG_SEOF2_INT_CLR_LEN                           (1U)
#define DSP2_MISC_RG_SEOF2_INT_CLR_MSK                           (((1U<<DSP2_MISC_RG_SEOF2_INT_CLR_LEN)-1)<<DSP2_MISC_RG_SEOF2_INT_CLR_POS)
#define DSP2_MISC_RG_SEOF2_INT_CLR_UMSK                          (~(((1U<<DSP2_MISC_RG_SEOF2_INT_CLR_LEN)-1)<<DSP2_MISC_RG_SEOF2_INT_CLR_POS))
#define DSP2_MISC_RG_SEOF3_INT_CLR                               DSP2_MISC_RG_SEOF3_INT_CLR
#define DSP2_MISC_RG_SEOF3_INT_CLR_POS                           (10U)
#define DSP2_MISC_RG_SEOF3_INT_CLR_LEN                           (1U)
#define DSP2_MISC_RG_SEOF3_INT_CLR_MSK                           (((1U<<DSP2_MISC_RG_SEOF3_INT_CLR_LEN)-1)<<DSP2_MISC_RG_SEOF3_INT_CLR_POS)
#define DSP2_MISC_RG_SEOF3_INT_CLR_UMSK                          (~(((1U<<DSP2_MISC_RG_SEOF3_INT_CLR_LEN)-1)<<DSP2_MISC_RG_SEOF3_INT_CLR_POS))

/* 0x24 : int_ctrl */
#define DSP2_MISC_INT_CTRL_OFFSET                                (0x24)
#define DSP2_MISC_RG_AE_INT_MASK                                 DSP2_MISC_RG_AE_INT_MASK
#define DSP2_MISC_RG_AE_INT_MASK_POS                             (0U)
#define DSP2_MISC_RG_AE_INT_MASK_LEN                             (1U)
#define DSP2_MISC_RG_AE_INT_MASK_MSK                             (((1U<<DSP2_MISC_RG_AE_INT_MASK_LEN)-1)<<DSP2_MISC_RG_AE_INT_MASK_POS)
#define DSP2_MISC_RG_AE_INT_MASK_UMSK                            (~(((1U<<DSP2_MISC_RG_AE_INT_MASK_LEN)-1)<<DSP2_MISC_RG_AE_INT_MASK_POS))
#define DSP2_MISC_RG_AWB_INT_MASK                                DSP2_MISC_RG_AWB_INT_MASK
#define DSP2_MISC_RG_AWB_INT_MASK_POS                            (1U)
#define DSP2_MISC_RG_AWB_INT_MASK_LEN                            (1U)
#define DSP2_MISC_RG_AWB_INT_MASK_MSK                            (((1U<<DSP2_MISC_RG_AWB_INT_MASK_LEN)-1)<<DSP2_MISC_RG_AWB_INT_MASK_POS)
#define DSP2_MISC_RG_AWB_INT_MASK_UMSK                           (~(((1U<<DSP2_MISC_RG_AWB_INT_MASK_LEN)-1)<<DSP2_MISC_RG_AWB_INT_MASK_POS))
#define DSP2_MISC_RG_SEOF1_INT_MASK                              DSP2_MISC_RG_SEOF1_INT_MASK
#define DSP2_MISC_RG_SEOF1_INT_MASK_POS                          (8U)
#define DSP2_MISC_RG_SEOF1_INT_MASK_LEN                          (1U)
#define DSP2_MISC_RG_SEOF1_INT_MASK_MSK                          (((1U<<DSP2_MISC_RG_SEOF1_INT_MASK_LEN)-1)<<DSP2_MISC_RG_SEOF1_INT_MASK_POS)
#define DSP2_MISC_RG_SEOF1_INT_MASK_UMSK                         (~(((1U<<DSP2_MISC_RG_SEOF1_INT_MASK_LEN)-1)<<DSP2_MISC_RG_SEOF1_INT_MASK_POS))
#define DSP2_MISC_RG_SEOF1_INT_EDGE                              DSP2_MISC_RG_SEOF1_INT_EDGE
#define DSP2_MISC_RG_SEOF1_INT_EDGE_POS                          (9U)
#define DSP2_MISC_RG_SEOF1_INT_EDGE_LEN                          (1U)
#define DSP2_MISC_RG_SEOF1_INT_EDGE_MSK                          (((1U<<DSP2_MISC_RG_SEOF1_INT_EDGE_LEN)-1)<<DSP2_MISC_RG_SEOF1_INT_EDGE_POS)
#define DSP2_MISC_RG_SEOF1_INT_EDGE_UMSK                         (~(((1U<<DSP2_MISC_RG_SEOF1_INT_EDGE_LEN)-1)<<DSP2_MISC_RG_SEOF1_INT_EDGE_POS))
#define DSP2_MISC_RG_SEOF1_INT_SRC                               DSP2_MISC_RG_SEOF1_INT_SRC
#define DSP2_MISC_RG_SEOF1_INT_SRC_POS                           (10U)
#define DSP2_MISC_RG_SEOF1_INT_SRC_LEN                           (2U)
#define DSP2_MISC_RG_SEOF1_INT_SRC_MSK                           (((1U<<DSP2_MISC_RG_SEOF1_INT_SRC_LEN)-1)<<DSP2_MISC_RG_SEOF1_INT_SRC_POS)
#define DSP2_MISC_RG_SEOF1_INT_SRC_UMSK                          (~(((1U<<DSP2_MISC_RG_SEOF1_INT_SRC_LEN)-1)<<DSP2_MISC_RG_SEOF1_INT_SRC_POS))
#define DSP2_MISC_RG_SEOF2_INT_MASK                              DSP2_MISC_RG_SEOF2_INT_MASK
#define DSP2_MISC_RG_SEOF2_INT_MASK_POS                          (12U)
#define DSP2_MISC_RG_SEOF2_INT_MASK_LEN                          (1U)
#define DSP2_MISC_RG_SEOF2_INT_MASK_MSK                          (((1U<<DSP2_MISC_RG_SEOF2_INT_MASK_LEN)-1)<<DSP2_MISC_RG_SEOF2_INT_MASK_POS)
#define DSP2_MISC_RG_SEOF2_INT_MASK_UMSK                         (~(((1U<<DSP2_MISC_RG_SEOF2_INT_MASK_LEN)-1)<<DSP2_MISC_RG_SEOF2_INT_MASK_POS))
#define DSP2_MISC_RG_SEOF2_INT_EDGE                              DSP2_MISC_RG_SEOF2_INT_EDGE
#define DSP2_MISC_RG_SEOF2_INT_EDGE_POS                          (13U)
#define DSP2_MISC_RG_SEOF2_INT_EDGE_LEN                          (1U)
#define DSP2_MISC_RG_SEOF2_INT_EDGE_MSK                          (((1U<<DSP2_MISC_RG_SEOF2_INT_EDGE_LEN)-1)<<DSP2_MISC_RG_SEOF2_INT_EDGE_POS)
#define DSP2_MISC_RG_SEOF2_INT_EDGE_UMSK                         (~(((1U<<DSP2_MISC_RG_SEOF2_INT_EDGE_LEN)-1)<<DSP2_MISC_RG_SEOF2_INT_EDGE_POS))
#define DSP2_MISC_RG_SEOF2_INT_SRC                               DSP2_MISC_RG_SEOF2_INT_SRC
#define DSP2_MISC_RG_SEOF2_INT_SRC_POS                           (14U)
#define DSP2_MISC_RG_SEOF2_INT_SRC_LEN                           (2U)
#define DSP2_MISC_RG_SEOF2_INT_SRC_MSK                           (((1U<<DSP2_MISC_RG_SEOF2_INT_SRC_LEN)-1)<<DSP2_MISC_RG_SEOF2_INT_SRC_POS)
#define DSP2_MISC_RG_SEOF2_INT_SRC_UMSK                          (~(((1U<<DSP2_MISC_RG_SEOF2_INT_SRC_LEN)-1)<<DSP2_MISC_RG_SEOF2_INT_SRC_POS))
#define DSP2_MISC_RG_SEOF3_INT_MASK                              DSP2_MISC_RG_SEOF3_INT_MASK
#define DSP2_MISC_RG_SEOF3_INT_MASK_POS                          (16U)
#define DSP2_MISC_RG_SEOF3_INT_MASK_LEN                          (1U)
#define DSP2_MISC_RG_SEOF3_INT_MASK_MSK                          (((1U<<DSP2_MISC_RG_SEOF3_INT_MASK_LEN)-1)<<DSP2_MISC_RG_SEOF3_INT_MASK_POS)
#define DSP2_MISC_RG_SEOF3_INT_MASK_UMSK                         (~(((1U<<DSP2_MISC_RG_SEOF3_INT_MASK_LEN)-1)<<DSP2_MISC_RG_SEOF3_INT_MASK_POS))
#define DSP2_MISC_RG_SEOF3_INT_EDGE                              DSP2_MISC_RG_SEOF3_INT_EDGE
#define DSP2_MISC_RG_SEOF3_INT_EDGE_POS                          (17U)
#define DSP2_MISC_RG_SEOF3_INT_EDGE_LEN                          (1U)
#define DSP2_MISC_RG_SEOF3_INT_EDGE_MSK                          (((1U<<DSP2_MISC_RG_SEOF3_INT_EDGE_LEN)-1)<<DSP2_MISC_RG_SEOF3_INT_EDGE_POS)
#define DSP2_MISC_RG_SEOF3_INT_EDGE_UMSK                         (~(((1U<<DSP2_MISC_RG_SEOF3_INT_EDGE_LEN)-1)<<DSP2_MISC_RG_SEOF3_INT_EDGE_POS))
#define DSP2_MISC_RG_SEOF3_INT_SRC                               DSP2_MISC_RG_SEOF3_INT_SRC
#define DSP2_MISC_RG_SEOF3_INT_SRC_POS                           (18U)
#define DSP2_MISC_RG_SEOF3_INT_SRC_LEN                           (2U)
#define DSP2_MISC_RG_SEOF3_INT_SRC_MSK                           (((1U<<DSP2_MISC_RG_SEOF3_INT_SRC_LEN)-1)<<DSP2_MISC_RG_SEOF3_INT_SRC_POS)
#define DSP2_MISC_RG_SEOF3_INT_SRC_UMSK                          (~(((1U<<DSP2_MISC_RG_SEOF3_INT_SRC_LEN)-1)<<DSP2_MISC_RG_SEOF3_INT_SRC_POS))

/* 0x40 : hdmi_scaler_i_size */
#define DSP2_MISC_HDMI_SCALER_I_SIZE_OFFSET                      (0x40)
#define DSP2_MISC_RG_HDMI_SCALER_I_W                             DSP2_MISC_RG_HDMI_SCALER_I_W
#define DSP2_MISC_RG_HDMI_SCALER_I_W_POS                         (0U)
#define DSP2_MISC_RG_HDMI_SCALER_I_W_LEN                         (11U)
#define DSP2_MISC_RG_HDMI_SCALER_I_W_MSK                         (((1U<<DSP2_MISC_RG_HDMI_SCALER_I_W_LEN)-1)<<DSP2_MISC_RG_HDMI_SCALER_I_W_POS)
#define DSP2_MISC_RG_HDMI_SCALER_I_W_UMSK                        (~(((1U<<DSP2_MISC_RG_HDMI_SCALER_I_W_LEN)-1)<<DSP2_MISC_RG_HDMI_SCALER_I_W_POS))
#define DSP2_MISC_RG_HDMI_SCALER_I_H                             DSP2_MISC_RG_HDMI_SCALER_I_H
#define DSP2_MISC_RG_HDMI_SCALER_I_H_POS                         (16U)
#define DSP2_MISC_RG_HDMI_SCALER_I_H_LEN                         (11U)
#define DSP2_MISC_RG_HDMI_SCALER_I_H_MSK                         (((1U<<DSP2_MISC_RG_HDMI_SCALER_I_H_LEN)-1)<<DSP2_MISC_RG_HDMI_SCALER_I_H_POS)
#define DSP2_MISC_RG_HDMI_SCALER_I_H_UMSK                        (~(((1U<<DSP2_MISC_RG_HDMI_SCALER_I_H_LEN)-1)<<DSP2_MISC_RG_HDMI_SCALER_I_H_POS))
#define DSP2_MISC_RG_HDMI_SCALER_BYPASS                          DSP2_MISC_RG_HDMI_SCALER_BYPASS
#define DSP2_MISC_RG_HDMI_SCALER_BYPASS_POS                      (28U)
#define DSP2_MISC_RG_HDMI_SCALER_BYPASS_LEN                      (1U)
#define DSP2_MISC_RG_HDMI_SCALER_BYPASS_MSK                      (((1U<<DSP2_MISC_RG_HDMI_SCALER_BYPASS_LEN)-1)<<DSP2_MISC_RG_HDMI_SCALER_BYPASS_POS)
#define DSP2_MISC_RG_HDMI_SCALER_BYPASS_UMSK                     (~(((1U<<DSP2_MISC_RG_HDMI_SCALER_BYPASS_LEN)-1)<<DSP2_MISC_RG_HDMI_SCALER_BYPASS_POS))

/* 0x44 : hdmi_scaler_o_size */
#define DSP2_MISC_HDMI_SCALER_O_SIZE_OFFSET                      (0x44)
#define DSP2_MISC_RG_HDMI_SCALER_O_W                             DSP2_MISC_RG_HDMI_SCALER_O_W
#define DSP2_MISC_RG_HDMI_SCALER_O_W_POS                         (0U)
#define DSP2_MISC_RG_HDMI_SCALER_O_W_LEN                         (11U)
#define DSP2_MISC_RG_HDMI_SCALER_O_W_MSK                         (((1U<<DSP2_MISC_RG_HDMI_SCALER_O_W_LEN)-1)<<DSP2_MISC_RG_HDMI_SCALER_O_W_POS)
#define DSP2_MISC_RG_HDMI_SCALER_O_W_UMSK                        (~(((1U<<DSP2_MISC_RG_HDMI_SCALER_O_W_LEN)-1)<<DSP2_MISC_RG_HDMI_SCALER_O_W_POS))
#define DSP2_MISC_RG_HDMI_SCALER_O_H                             DSP2_MISC_RG_HDMI_SCALER_O_H
#define DSP2_MISC_RG_HDMI_SCALER_O_H_POS                         (16U)
#define DSP2_MISC_RG_HDMI_SCALER_O_H_LEN                         (11U)
#define DSP2_MISC_RG_HDMI_SCALER_O_H_MSK                         (((1U<<DSP2_MISC_RG_HDMI_SCALER_O_H_LEN)-1)<<DSP2_MISC_RG_HDMI_SCALER_O_H_POS)
#define DSP2_MISC_RG_HDMI_SCALER_O_H_UMSK                        (~(((1U<<DSP2_MISC_RG_HDMI_SCALER_O_H_LEN)-1)<<DSP2_MISC_RG_HDMI_SCALER_O_H_POS))

/* 0x48 : codec_scaler_i_size */
#define DSP2_MISC_CODEC_SCALER_I_SIZE_OFFSET                     (0x48)
#define DSP2_MISC_RG_CODEC_SCALER_I_W                            DSP2_MISC_RG_CODEC_SCALER_I_W
#define DSP2_MISC_RG_CODEC_SCALER_I_W_POS                        (0U)
#define DSP2_MISC_RG_CODEC_SCALER_I_W_LEN                        (11U)
#define DSP2_MISC_RG_CODEC_SCALER_I_W_MSK                        (((1U<<DSP2_MISC_RG_CODEC_SCALER_I_W_LEN)-1)<<DSP2_MISC_RG_CODEC_SCALER_I_W_POS)
#define DSP2_MISC_RG_CODEC_SCALER_I_W_UMSK                       (~(((1U<<DSP2_MISC_RG_CODEC_SCALER_I_W_LEN)-1)<<DSP2_MISC_RG_CODEC_SCALER_I_W_POS))
#define DSP2_MISC_RG_CODEC_SCALER_I_H                            DSP2_MISC_RG_CODEC_SCALER_I_H
#define DSP2_MISC_RG_CODEC_SCALER_I_H_POS                        (16U)
#define DSP2_MISC_RG_CODEC_SCALER_I_H_LEN                        (11U)
#define DSP2_MISC_RG_CODEC_SCALER_I_H_MSK                        (((1U<<DSP2_MISC_RG_CODEC_SCALER_I_H_LEN)-1)<<DSP2_MISC_RG_CODEC_SCALER_I_H_POS)
#define DSP2_MISC_RG_CODEC_SCALER_I_H_UMSK                       (~(((1U<<DSP2_MISC_RG_CODEC_SCALER_I_H_LEN)-1)<<DSP2_MISC_RG_CODEC_SCALER_I_H_POS))
#define DSP2_MISC_RG_CODEC_SCALER_BYPASS                         DSP2_MISC_RG_CODEC_SCALER_BYPASS
#define DSP2_MISC_RG_CODEC_SCALER_BYPASS_POS                     (28U)
#define DSP2_MISC_RG_CODEC_SCALER_BYPASS_LEN                     (1U)
#define DSP2_MISC_RG_CODEC_SCALER_BYPASS_MSK                     (((1U<<DSP2_MISC_RG_CODEC_SCALER_BYPASS_LEN)-1)<<DSP2_MISC_RG_CODEC_SCALER_BYPASS_POS)
#define DSP2_MISC_RG_CODEC_SCALER_BYPASS_UMSK                    (~(((1U<<DSP2_MISC_RG_CODEC_SCALER_BYPASS_LEN)-1)<<DSP2_MISC_RG_CODEC_SCALER_BYPASS_POS))

/* 0x4C : codec_scaler_o_size */
#define DSP2_MISC_CODEC_SCALER_O_SIZE_OFFSET                     (0x4C)
#define DSP2_MISC_RG_CODEC_SCALER_O_W                            DSP2_MISC_RG_CODEC_SCALER_O_W
#define DSP2_MISC_RG_CODEC_SCALER_O_W_POS                        (0U)
#define DSP2_MISC_RG_CODEC_SCALER_O_W_LEN                        (11U)
#define DSP2_MISC_RG_CODEC_SCALER_O_W_MSK                        (((1U<<DSP2_MISC_RG_CODEC_SCALER_O_W_LEN)-1)<<DSP2_MISC_RG_CODEC_SCALER_O_W_POS)
#define DSP2_MISC_RG_CODEC_SCALER_O_W_UMSK                       (~(((1U<<DSP2_MISC_RG_CODEC_SCALER_O_W_LEN)-1)<<DSP2_MISC_RG_CODEC_SCALER_O_W_POS))
#define DSP2_MISC_RG_CODEC_SCALER_O_H                            DSP2_MISC_RG_CODEC_SCALER_O_H
#define DSP2_MISC_RG_CODEC_SCALER_O_H_POS                        (16U)
#define DSP2_MISC_RG_CODEC_SCALER_O_H_LEN                        (11U)
#define DSP2_MISC_RG_CODEC_SCALER_O_H_MSK                        (((1U<<DSP2_MISC_RG_CODEC_SCALER_O_H_LEN)-1)<<DSP2_MISC_RG_CODEC_SCALER_O_H_POS)
#define DSP2_MISC_RG_CODEC_SCALER_O_H_UMSK                       (~(((1U<<DSP2_MISC_RG_CODEC_SCALER_O_H_LEN)-1)<<DSP2_MISC_RG_CODEC_SCALER_O_H_POS))

/* 0x60 : dsp2_subsys_bus_ctrl */
#define DSP2_MISC_DSP2_SUBSYS_BUS_CTRL_OFFSET                     (0x60)
#define DSP2_MISC_RG_PCLK_FORCE_ON                               DSP2_MISC_RG_PCLK_FORCE_ON
#define DSP2_MISC_RG_PCLK_FORCE_ON_POS                           (0U)
#define DSP2_MISC_RG_PCLK_FORCE_ON_LEN                           (16U)
#define DSP2_MISC_RG_PCLK_FORCE_ON_MSK                           (((1U<<DSP2_MISC_RG_PCLK_FORCE_ON_LEN)-1)<<DSP2_MISC_RG_PCLK_FORCE_ON_POS)
#define DSP2_MISC_RG_PCLK_FORCE_ON_UMSK                          (~(((1U<<DSP2_MISC_RG_PCLK_FORCE_ON_LEN)-1)<<DSP2_MISC_RG_PCLK_FORCE_ON_POS))
#define DSP2_MISC_REG_DSP2_PCLK_FORCE_ON                          DSP2_MISC_REG_DSP2_PCLK_FORCE_ON
#define DSP2_MISC_REG_DSP2_PCLK_FORCE_ON_POS                      (16U)
#define DSP2_MISC_REG_DSP2_PCLK_FORCE_ON_LEN                      (1U)
#define DSP2_MISC_REG_DSP2_PCLK_FORCE_ON_MSK                      (((1U<<DSP2_MISC_REG_DSP2_PCLK_FORCE_ON_LEN)-1)<<DSP2_MISC_REG_DSP2_PCLK_FORCE_ON_POS)
#define DSP2_MISC_REG_DSP2_PCLK_FORCE_ON_UMSK                     (~(((1U<<DSP2_MISC_REG_DSP2_PCLK_FORCE_ON_LEN)-1)<<DSP2_MISC_REG_DSP2_PCLK_FORCE_ON_POS))

/* 0xC0 : dsp2_subsys_dbg_sel */
#define DSP2_MISC_DSP2_SUBSYS_DBG_SEL_OFFSET                      (0xC0)
#define DSP2_MISC_REG_DSP2_SUB_DBG_EN                             DSP2_MISC_REG_DSP2_SUB_DBG_EN
#define DSP2_MISC_REG_DSP2_SUB_DBG_EN_POS                         (0U)
#define DSP2_MISC_REG_DSP2_SUB_DBG_EN_LEN                         (1U)
#define DSP2_MISC_REG_DSP2_SUB_DBG_EN_MSK                         (((1U<<DSP2_MISC_REG_DSP2_SUB_DBG_EN_LEN)-1)<<DSP2_MISC_REG_DSP2_SUB_DBG_EN_POS)
#define DSP2_MISC_REG_DSP2_SUB_DBG_EN_UMSK                        (~(((1U<<DSP2_MISC_REG_DSP2_SUB_DBG_EN_LEN)-1)<<DSP2_MISC_REG_DSP2_SUB_DBG_EN_POS))
#define DSP2_MISC_REG_DSP2_SUB_DBG_SEL                            DSP2_MISC_REG_DSP2_SUB_DBG_SEL
#define DSP2_MISC_REG_DSP2_SUB_DBG_SEL_POS                        (4U)
#define DSP2_MISC_REG_DSP2_SUB_DBG_SEL_LEN                        (4U)
#define DSP2_MISC_REG_DSP2_SUB_DBG_SEL_MSK                        (((1U<<DSP2_MISC_REG_DSP2_SUB_DBG_SEL_LEN)-1)<<DSP2_MISC_REG_DSP2_SUB_DBG_SEL_POS)
#define DSP2_MISC_REG_DSP2_SUB_DBG_SEL_UMSK                       (~(((1U<<DSP2_MISC_REG_DSP2_SUB_DBG_SEL_LEN)-1)<<DSP2_MISC_REG_DSP2_SUB_DBG_SEL_POS))

/* 0xFC : DSP2_MISC_Dummy */
#define DSP2_MISC_DUMMY_OFFSET                                   (0xFC)
#define DSP2_MISC_DUMMY_REG                                      DSP2_MISC_DUMMY_REG
#define DSP2_MISC_DUMMY_REG_POS                                  (0U)
#define DSP2_MISC_DUMMY_REG_LEN                                  (32U)
#define DSP2_MISC_DUMMY_REG_MSK                                  (((1U<<DSP2_MISC_DUMMY_REG_LEN)-1)<<DSP2_MISC_DUMMY_REG_POS)
#define DSP2_MISC_DUMMY_REG_UMSK                                 (~(((1U<<DSP2_MISC_DUMMY_REG_LEN)-1)<<DSP2_MISC_DUMMY_REG_POS))


struct  dsp2_misc_reg {
    /* 0x0 : config */
    union {
        struct {
            uint32_t rg_dvp_mux_hdmi_sel            :  1; /* [    0],        r/w,        0x0 */
            uint32_t dvp_mux_ch4_sel                :  1; /* [    1],        r/w,        0x0 */
            uint32_t cr_dsp2_de_as_hsync             :  1; /* [    2],        r/w,        0x0 */
            uint32_t reserved_3                     :  1; /* [    3],       rsvd,        0x0 */
            uint32_t new_ae_sel                     :  1; /* [    4],        r/w,        0x0 */
            uint32_t new_awb_sel                    :  1; /* [    5],        r/w,        0x0 */
            uint32_t reserved_6_31                  : 26; /* [31: 6],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } config;

    /* 0x4 : pix_data_ctrl */
    union {
        struct {
            uint32_t reg_pix_data_ctrl              : 12; /* [11: 0],        r/w,      0xfff */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t reg_pix_data_sht_bit           :  4; /* [19:16],        r/w,        0x0 */
            uint32_t reg_pix_data_sht_dir           :  1; /* [   20],        r/w,        0x0 */
            uint32_t reserved_21_31                 : 11; /* [31:21],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } pix_data_ctrl;

    /* 0x8 : dvp2bus_src_sel */
    union {
        struct {
            uint32_t rg_d2b_dvp_sel_a               :  8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t rg_d2b_dvp_sel_b               :  8; /* [15: 8],        r/w,        0x0 */
            uint32_t rg_d2b_dvp_sel_c               :  8; /* [23:16],        r/w,        0x0 */
            uint32_t rg_d2b_dvp_sel_d               :  8; /* [31:24],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } dvp2bus_src_sel;

    /* 0xC : dvp_frame_m_to_n */
    union {
        struct {
            uint32_t cr_frame_m_to_n_en             :  1; /* [    0],        r/w,        0x0 */
            uint32_t reserved_1_3                   :  3; /* [ 3: 1],       rsvd,        0x0 */
            uint32_t cr_frame_interval              :  4; /* [ 7: 4],        r/w,        0x0 */
            uint32_t cr_frame_cnt_n                 :  4; /* [11: 8],        r/w,        0x0 */
            uint32_t cr_frame_cnt_m                 :  4; /* [15:12],        r/w,        0x0 */
            uint32_t reserved_16_31                 : 16; /* [31:16],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } dvp_frame_m_to_n;

    /* 0x10 : dsp2_sub_bus_control */
    union {
        struct {
            uint32_t reg_nr3d_awqos                 :  1; /* [    0],        r/w,        0x0 */
            uint32_t reg_nr3d_arqos                 :  1; /* [    1],        r/w,        0x0 */
            uint32_t reg_d2bA_awqos                 :  1; /* [    2],        r/w,        0x0 */
            uint32_t reg_d2bB_awqos                 :  1; /* [    3],        r/w,        0x0 */
            uint32_t reg_d2bC_awqos                 :  1; /* [    4],        r/w,        0x0 */
            uint32_t reg_d2bD_awqos                 :  1; /* [    5],        r/w,        0x0 */
            uint32_t reg_dsp2_dtsrc_arqos            :  1; /* [    6],        r/w,        0x0 */
            uint32_t reg_hdmi_dtsrc_arqos           :  1; /* [    7],        r/w,        0x0 */
            uint32_t reserved_8_31                  : 24; /* [31: 8],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } dsp2_sub_bus_control;

    /* 0x14  reserved */
    uint8_t RESERVED0x14[12];

    /* 0x20 : int_clr */
    union {
        struct {
            uint32_t rg_awb_int_clr                 :  1; /* [    0],        w1p,        0x0 */
            uint32_t rg_ae_int_clr                  :  1; /* [    1],        w1p,        0x0 */
            uint32_t reserved_2_7                   :  6; /* [ 7: 2],       rsvd,        0x0 */
            uint32_t rg_seof1_int_clr               :  1; /* [    8],        w1p,        0x0 */
            uint32_t rg_seof2_int_clr               :  1; /* [    9],        w1p,        0x0 */
            uint32_t rg_seof3_int_clr               :  1; /* [   10],        w1p,        0x0 */
            uint32_t reserved_11_31                 : 21; /* [31:11],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } int_clr;

    /* 0x24 : int_ctrl */
    union {
        struct {
            uint32_t rg_ae_int_mask                 :  1; /* [    0],        r/w,        0x0 */
            uint32_t rg_awb_int_mask                :  1; /* [    1],        r/w,        0x0 */
            uint32_t reserved_2_7                   :  6; /* [ 7: 2],       rsvd,        0x0 */
            uint32_t rg_seof1_int_mask              :  1; /* [    8],        r/w,        0x0 */
            uint32_t rg_seof1_int_edge              :  1; /* [    9],        r/w,        0x0 */
            uint32_t rg_seof1_int_src               :  2; /* [11:10],        r/w,        0x2 */
            uint32_t rg_seof2_int_mask              :  1; /* [   12],        r/w,        0x0 */
            uint32_t rg_seof2_int_edge              :  1; /* [   13],        r/w,        0x0 */
            uint32_t rg_seof2_int_src               :  2; /* [15:14],        r/w,        0x2 */
            uint32_t rg_seof3_int_mask              :  1; /* [   16],        r/w,        0x0 */
            uint32_t rg_seof3_int_edge              :  1; /* [   17],        r/w,        0x0 */
            uint32_t rg_seof3_int_src               :  2; /* [19:18],        r/w,        0x2 */
            uint32_t reserved_20_31                 : 12; /* [31:20],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } int_ctrl;

    /* 0x28  reserved */
    uint8_t RESERVED0x28[24];

    /* 0x40 : hdmi_scaler_i_size */
    union {
        struct {
            uint32_t rg_hdmi_scaler_i_w             : 11; /* [10: 0],        r/w,      0x780 */
            uint32_t reserved_11_15                 :  5; /* [15:11],       rsvd,        0x0 */
            uint32_t rg_hdmi_scaler_i_h             : 11; /* [26:16],        r/w,      0x438 */
            uint32_t reserved_27                    :  1; /* [   27],       rsvd,        0x0 */
            uint32_t rg_hdmi_scaler_bypass          :  1; /* [   28],        r/w,        0x1 */
            uint32_t reserved_29_31                 :  3; /* [31:29],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } hdmi_scaler_i_size;

    /* 0x44 : hdmi_scaler_o_size */
    union {
        struct {
            uint32_t rg_hdmi_scaler_o_w             : 11; /* [10: 0],        r/w,      0x500 */
            uint32_t reserved_11_15                 :  5; /* [15:11],       rsvd,        0x0 */
            uint32_t rg_hdmi_scaler_o_h             : 11; /* [26:16],        r/w,      0x2d0 */
            uint32_t reserved_27_31                 :  5; /* [31:27],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } hdmi_scaler_o_size;

    /* 0x48 : codec_scaler_i_size */
    union {
        struct {
            uint32_t rg_codec_scaler_i_w            : 11; /* [10: 0],        r/w,      0x780 */
            uint32_t reserved_11_15                 :  5; /* [15:11],       rsvd,        0x0 */
            uint32_t rg_codec_scaler_i_h            : 11; /* [26:16],        r/w,      0x438 */
            uint32_t reserved_27                    :  1; /* [   27],       rsvd,        0x0 */
            uint32_t rg_codec_scaler_bypass         :  1; /* [   28],        r/w,        0x1 */
            uint32_t reserved_29_31                 :  3; /* [31:29],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } codec_scaler_i_size;

    /* 0x4C : codec_scaler_o_size */
    union {
        struct {
            uint32_t rg_codec_scaler_o_w            : 11; /* [10: 0],        r/w,      0x500 */
            uint32_t reserved_11_15                 :  5; /* [15:11],       rsvd,        0x0 */
            uint32_t rg_codec_scaler_o_h            : 11; /* [26:16],        r/w,      0x2d0 */
            uint32_t reserved_27_31                 :  5; /* [31:27],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } codec_scaler_o_size;

    /* 0x50  reserved */
    uint8_t RESERVED0x50[16];

    /* 0x60 : dsp2_subsys_bus_ctrl */
    union {
        struct {
            uint32_t rg_pclk_force_on               : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t reg_dsp2_pclk_force_on          :  1; /* [   16],        r/w,        0x0 */
            uint32_t reserved_17_31                 : 15; /* [31:17],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } dsp2_subsys_bus_ctrl;

    /* 0x64  reserved */
    uint8_t RESERVED0x64[92];

    /* 0xC0 : dsp2_subsys_dbg_sel */
    union {
        struct {
            uint32_t reg_dsp2_sub_dbg_en             :  1; /* [    0],        r/w,        0x0 */
            uint32_t reserved_1_3                   :  3; /* [ 3: 1],       rsvd,        0x0 */
            uint32_t reg_dsp2_sub_dbg_sel            :  4; /* [ 7: 4],        r/w,        0x0 */
            uint32_t reserved_8_31                  : 24; /* [31: 8],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } dsp2_subsys_dbg_sel;

    /* 0xc4  reserved */
    uint8_t RESERVED0xc4[56];

    /* 0xFC : DSP2_MISC_Dummy */
    union {
        struct {
            uint32_t dummy_reg                      : 32; /* [31: 0],        r/w, 0xffff0000 */
        }BF;
        uint32_t WORD;
    } DSP2_MISC_Dummy;

};

typedef volatile struct dsp2_misc_reg dsp2_misc_reg_t;


#endif  /* __DSP2_MISC_REG_H__ */
