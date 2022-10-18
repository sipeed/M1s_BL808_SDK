/**
  ******************************************************************************
  * @file    vdo_reg.h
  * @version V1.2
  * @date    2019-08-05
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
#ifndef  __VDO_REG_H__
#define  __VDO_REG_H__

#include "bl808.h"

/* 0x00 : h264_encoder_ctrl */
#define VDO_H264_ENCODER_CTRL_OFFSET                            (0x00)
#define VDO_CFG_ENC_CTRL_MBY_IDX                                VDO_CFG_ENC_CTRL_MBY_IDX
#define VDO_CFG_ENC_CTRL_MBY_IDX_POS                            (0U)
#define VDO_CFG_ENC_CTRL_MBY_IDX_LEN                            (7U)
#define VDO_CFG_ENC_CTRL_MBY_IDX_MSK                            (((1U<<VDO_CFG_ENC_CTRL_MBY_IDX_LEN)-1)<<VDO_CFG_ENC_CTRL_MBY_IDX_POS)
#define VDO_CFG_ENC_CTRL_MBY_IDX_UMSK                           (~(((1U<<VDO_CFG_ENC_CTRL_MBY_IDX_LEN)-1)<<VDO_CFG_ENC_CTRL_MBY_IDX_POS))
#define VDO_CFG_CORE_CLK_EN                                     VDO_CFG_CORE_CLK_EN
#define VDO_CFG_CORE_CLK_EN_POS                                 (8U)
#define VDO_CFG_CORE_CLK_EN_LEN                                 (1U)
#define VDO_CFG_CORE_CLK_EN_MSK                                 (((1U<<VDO_CFG_CORE_CLK_EN_LEN)-1)<<VDO_CFG_CORE_CLK_EN_POS)
#define VDO_CFG_CORE_CLK_EN_UMSK                                (~(((1U<<VDO_CFG_CORE_CLK_EN_LEN)-1)<<VDO_CFG_CORE_CLK_EN_POS))
#define VDO_CFG_MEM_CLK_EN                                      VDO_CFG_MEM_CLK_EN
#define VDO_CFG_MEM_CLK_EN_POS                                  (12U)
#define VDO_CFG_MEM_CLK_EN_LEN                                  (1U)
#define VDO_CFG_MEM_CLK_EN_MSK                                  (((1U<<VDO_CFG_MEM_CLK_EN_LEN)-1)<<VDO_CFG_MEM_CLK_EN_POS)
#define VDO_CFG_MEM_CLK_EN_UMSK                                 (~(((1U<<VDO_CFG_MEM_CLK_EN_LEN)-1)<<VDO_CFG_MEM_CLK_EN_POS))
#define VDO_CFG_BUF_CLR                                         VDO_CFG_BUF_CLR
#define VDO_CFG_BUF_CLR_POS                                     (16U)
#define VDO_CFG_BUF_CLR_LEN                                     (1U)
#define VDO_CFG_BUF_CLR_MSK                                     (((1U<<VDO_CFG_BUF_CLR_LEN)-1)<<VDO_CFG_BUF_CLR_POS)
#define VDO_CFG_BUF_CLR_UMSK                                    (~(((1U<<VDO_CFG_BUF_CLR_LEN)-1)<<VDO_CFG_BUF_CLR_POS))
#define VDO_CFG_BS_STATUS_INIT                                  VDO_CFG_BS_STATUS_INIT
#define VDO_CFG_BS_STATUS_INIT_POS                              (20U)
#define VDO_CFG_BS_STATUS_INIT_LEN                              (1U)
#define VDO_CFG_BS_STATUS_INIT_MSK                              (((1U<<VDO_CFG_BS_STATUS_INIT_LEN)-1)<<VDO_CFG_BS_STATUS_INIT_POS)
#define VDO_CFG_BS_STATUS_INIT_UMSK                             (~(((1U<<VDO_CFG_BS_STATUS_INIT_LEN)-1)<<VDO_CFG_BS_STATUS_INIT_POS))
#define VDO_CFG_CTRL_MODE                                       VDO_CFG_CTRL_MODE
#define VDO_CFG_CTRL_MODE_POS                                   (24U)
#define VDO_CFG_CTRL_MODE_LEN                                   (2U)
#define VDO_CFG_CTRL_MODE_MSK                                   (((1U<<VDO_CFG_CTRL_MODE_LEN)-1)<<VDO_CFG_CTRL_MODE_POS)
#define VDO_CFG_CTRL_MODE_UMSK                                  (~(((1U<<VDO_CFG_CTRL_MODE_LEN)-1)<<VDO_CFG_CTRL_MODE_POS))
#define VDO_CFG_CREF_EN                                         VDO_CFG_CREF_EN
#define VDO_CFG_CREF_EN_POS                                     (26U)
#define VDO_CFG_CREF_EN_LEN                                     (1U)
#define VDO_CFG_CREF_EN_MSK                                     (((1U<<VDO_CFG_CREF_EN_LEN)-1)<<VDO_CFG_CREF_EN_POS)
#define VDO_CFG_CREF_EN_UMSK                                    (~(((1U<<VDO_CFG_CREF_EN_LEN)-1)<<VDO_CFG_CREF_EN_POS))
#define VDO_CFG_FRAME_START                                     VDO_CFG_FRAME_START
#define VDO_CFG_FRAME_START_POS                                 (28U)
#define VDO_CFG_FRAME_START_LEN                                 (1U)
#define VDO_CFG_FRAME_START_MSK                                 (((1U<<VDO_CFG_FRAME_START_LEN)-1)<<VDO_CFG_FRAME_START_POS)
#define VDO_CFG_FRAME_START_UMSK                                (~(((1U<<VDO_CFG_FRAME_START_LEN)-1)<<VDO_CFG_FRAME_START_POS))
#define VDO_CFG_ENC_SEQ_EN                                      VDO_CFG_ENC_SEQ_EN
#define VDO_CFG_ENC_SEQ_EN_POS                                  (29U)
#define VDO_CFG_ENC_SEQ_EN_LEN                                  (1U)
#define VDO_CFG_ENC_SEQ_EN_MSK                                  (((1U<<VDO_CFG_ENC_SEQ_EN_LEN)-1)<<VDO_CFG_ENC_SEQ_EN_POS)
#define VDO_CFG_ENC_SEQ_EN_UMSK                                 (~(((1U<<VDO_CFG_ENC_SEQ_EN_LEN)-1)<<VDO_CFG_ENC_SEQ_EN_POS))

/* 0x04 : h264_frame_size */
#define VDO_H264_FRAME_SIZE_OFFSET                              (0x04)
#define VDO_CFG_FRAME_WIDTH                                     VDO_CFG_FRAME_WIDTH
#define VDO_CFG_FRAME_WIDTH_POS                                 (0U)
#define VDO_CFG_FRAME_WIDTH_LEN                                 (11U)
#define VDO_CFG_FRAME_WIDTH_MSK                                 (((1U<<VDO_CFG_FRAME_WIDTH_LEN)-1)<<VDO_CFG_FRAME_WIDTH_POS)
#define VDO_CFG_FRAME_WIDTH_UMSK                                (~(((1U<<VDO_CFG_FRAME_WIDTH_LEN)-1)<<VDO_CFG_FRAME_WIDTH_POS))
#define VDO_CFG_FRAME_HEIGHT                                    VDO_CFG_FRAME_HEIGHT
#define VDO_CFG_FRAME_HEIGHT_POS                                (16U)
#define VDO_CFG_FRAME_HEIGHT_LEN                                (11U)
#define VDO_CFG_FRAME_HEIGHT_MSK                                (((1U<<VDO_CFG_FRAME_HEIGHT_LEN)-1)<<VDO_CFG_FRAME_HEIGHT_POS)
#define VDO_CFG_FRAME_HEIGHT_UMSK                               (~(((1U<<VDO_CFG_FRAME_HEIGHT_LEN)-1)<<VDO_CFG_FRAME_HEIGHT_POS))

/* 0x08 : h264_frame_base_addr_y */
#define VDO_H264_FRAME_BASE_ADDR_Y_OFFSET                       (0x08)
#define VDO_CFG_FRAME_BASE_ADDR_Y                               VDO_CFG_FRAME_BASE_ADDR_Y
#define VDO_CFG_FRAME_BASE_ADDR_Y_POS                           (0U)
#define VDO_CFG_FRAME_BASE_ADDR_Y_LEN                           (32U)
#define VDO_CFG_FRAME_BASE_ADDR_Y_MSK                           (((1U<<VDO_CFG_FRAME_BASE_ADDR_Y_LEN)-1)<<VDO_CFG_FRAME_BASE_ADDR_Y_POS)
#define VDO_CFG_FRAME_BASE_ADDR_Y_UMSK                          (~(((1U<<VDO_CFG_FRAME_BASE_ADDR_Y_LEN)-1)<<VDO_CFG_FRAME_BASE_ADDR_Y_POS))

/* 0xC : h264_frame_base_addr_uv */
#define VDO_H264_FRAME_BASE_ADDR_UV_OFFSET                      (0xC)
#define VDO_CFG_FRAME_BASE_ADDR_UV                              VDO_CFG_FRAME_BASE_ADDR_UV
#define VDO_CFG_FRAME_BASE_ADDR_UV_POS                          (0U)
#define VDO_CFG_FRAME_BASE_ADDR_UV_LEN                          (32U)
#define VDO_CFG_FRAME_BASE_ADDR_UV_MSK                          (((1U<<VDO_CFG_FRAME_BASE_ADDR_UV_LEN)-1)<<VDO_CFG_FRAME_BASE_ADDR_UV_POS)
#define VDO_CFG_FRAME_BASE_ADDR_UV_UMSK                         (~(((1U<<VDO_CFG_FRAME_BASE_ADDR_UV_LEN)-1)<<VDO_CFG_FRAME_BASE_ADDR_UV_POS))

/* 0x10 : h264_bs_base_addr */
#define VDO_H264_BS_BASE_ADDR_OFFSET                            (0x10)
#define VDO_CFG_BS_BASE_ADDR                                    VDO_CFG_BS_BASE_ADDR
#define VDO_CFG_BS_BASE_ADDR_POS                                (0U)
#define VDO_CFG_BS_BASE_ADDR_LEN                                (32U)
#define VDO_CFG_BS_BASE_ADDR_MSK                                (((1U<<VDO_CFG_BS_BASE_ADDR_LEN)-1)<<VDO_CFG_BS_BASE_ADDR_POS)
#define VDO_CFG_BS_BASE_ADDR_UMSK                               (~(((1U<<VDO_CFG_BS_BASE_ADDR_LEN)-1)<<VDO_CFG_BS_BASE_ADDR_POS))

/* 0x14 : h264_ref_base_addr */
#define VDO_H264_REF_BASE_ADDR_OFFSET                           (0x14)
#define VDO_CFG_REF_BASE_ADDR                                   VDO_CFG_REF_BASE_ADDR
#define VDO_CFG_REF_BASE_ADDR_POS                               (0U)
#define VDO_CFG_REF_BASE_ADDR_LEN                               (32U)
#define VDO_CFG_REF_BASE_ADDR_MSK                               (((1U<<VDO_CFG_REF_BASE_ADDR_LEN)-1)<<VDO_CFG_REF_BASE_ADDR_POS)
#define VDO_CFG_REF_BASE_ADDR_UMSK                              (~(((1U<<VDO_CFG_REF_BASE_ADDR_LEN)-1)<<VDO_CFG_REF_BASE_ADDR_POS))

/* 0x18 : h264_bs_size */
#define VDO_H264_BS_SIZE_OFFSET                                 (0x18)
#define VDO_CFG_BS_SIZE                                         VDO_CFG_BS_SIZE
#define VDO_CFG_BS_SIZE_POS                                     (0U)
#define VDO_CFG_BS_SIZE_LEN                                     (32U)
#define VDO_CFG_BS_SIZE_MSK                                     (((1U<<VDO_CFG_BS_SIZE_LEN)-1)<<VDO_CFG_BS_SIZE_POS)
#define VDO_CFG_BS_SIZE_UMSK                                    (~(((1U<<VDO_CFG_BS_SIZE_LEN)-1)<<VDO_CFG_BS_SIZE_POS))

/* 0x1C : h264_bs_full_thr */
#define VDO_H264_BS_FULL_THR_OFFSET                             (0x1C)
#define VDO_CFG_BS_FULL_THR                                     VDO_CFG_BS_FULL_THR
#define VDO_CFG_BS_FULL_THR_POS                                 (0U)
#define VDO_CFG_BS_FULL_THR_LEN                                 (32U)
#define VDO_CFG_BS_FULL_THR_MSK                                 (((1U<<VDO_CFG_BS_FULL_THR_LEN)-1)<<VDO_CFG_BS_FULL_THR_POS)
#define VDO_CFG_BS_FULL_THR_UMSK                                (~(((1U<<VDO_CFG_BS_FULL_THR_LEN)-1)<<VDO_CFG_BS_FULL_THR_POS))

/* 0x20 : h264_src_bf_height */
#define VDO_H264_SRC_BF_HEIGHT_OFFSET                           (0x20)
#define VDO_CFG_C_SRC_BF_HEIGHT                                 VDO_CFG_C_SRC_BF_HEIGHT
#define VDO_CFG_C_SRC_BF_HEIGHT_POS                             (0U)
#define VDO_CFG_C_SRC_BF_HEIGHT_LEN                             (11U)
#define VDO_CFG_C_SRC_BF_HEIGHT_MSK                             (((1U<<VDO_CFG_C_SRC_BF_HEIGHT_LEN)-1)<<VDO_CFG_C_SRC_BF_HEIGHT_POS)
#define VDO_CFG_C_SRC_BF_HEIGHT_UMSK                            (~(((1U<<VDO_CFG_C_SRC_BF_HEIGHT_LEN)-1)<<VDO_CFG_C_SRC_BF_HEIGHT_POS))
#define VDO_CFG_Y_SRC_BF_HEIGHT                                 VDO_CFG_Y_SRC_BF_HEIGHT
#define VDO_CFG_Y_SRC_BF_HEIGHT_POS                             (16U)
#define VDO_CFG_Y_SRC_BF_HEIGHT_LEN                             (11U)
#define VDO_CFG_Y_SRC_BF_HEIGHT_MSK                             (((1U<<VDO_CFG_Y_SRC_BF_HEIGHT_LEN)-1)<<VDO_CFG_Y_SRC_BF_HEIGHT_POS)
#define VDO_CFG_Y_SRC_BF_HEIGHT_UMSK                            (~(((1U<<VDO_CFG_Y_SRC_BF_HEIGHT_LEN)-1)<<VDO_CFG_Y_SRC_BF_HEIGHT_POS))

/* 0x24 : core_reg0 */
#define VDO_CORE_REG0_OFFSET                                    (0x24)
#define VDO_ENC_EN                                              VDO_ENC_EN
#define VDO_ENC_EN_POS                                          (0U)
#define VDO_ENC_EN_LEN                                          (1U)
#define VDO_ENC_EN_MSK                                          (((1U<<VDO_ENC_EN_LEN)-1)<<VDO_ENC_EN_POS)
#define VDO_ENC_EN_UMSK                                         (~(((1U<<VDO_ENC_EN_LEN)-1)<<VDO_ENC_EN_POS))
#define VDO_VUI_ASPECT_INFO                                     VDO_VUI_ASPECT_INFO
#define VDO_VUI_ASPECT_INFO_POS                                 (12U)
#define VDO_VUI_ASPECT_INFO_LEN                                 (1U)
#define VDO_VUI_ASPECT_INFO_MSK                                 (((1U<<VDO_VUI_ASPECT_INFO_LEN)-1)<<VDO_VUI_ASPECT_INFO_POS)
#define VDO_VUI_ASPECT_INFO_UMSK                                (~(((1U<<VDO_VUI_ASPECT_INFO_LEN)-1)<<VDO_VUI_ASPECT_INFO_POS))
#define VDO_VUI_FIXED_F_RATE                                    VDO_VUI_FIXED_F_RATE
#define VDO_VUI_FIXED_F_RATE_POS                                (13U)
#define VDO_VUI_FIXED_F_RATE_LEN                                (1U)
#define VDO_VUI_FIXED_F_RATE_MSK                                (((1U<<VDO_VUI_FIXED_F_RATE_LEN)-1)<<VDO_VUI_FIXED_F_RATE_POS)
#define VDO_VUI_FIXED_F_RATE_UMSK                               (~(((1U<<VDO_VUI_FIXED_F_RATE_LEN)-1)<<VDO_VUI_FIXED_F_RATE_POS))
#define VDO_VUI_TIMING_INFO                                     VDO_VUI_TIMING_INFO
#define VDO_VUI_TIMING_INFO_POS                                 (14U)
#define VDO_VUI_TIMING_INFO_LEN                                 (1U)
#define VDO_VUI_TIMING_INFO_MSK                                 (((1U<<VDO_VUI_TIMING_INFO_LEN)-1)<<VDO_VUI_TIMING_INFO_POS)
#define VDO_VUI_TIMING_INFO_UMSK                                (~(((1U<<VDO_VUI_TIMING_INFO_LEN)-1)<<VDO_VUI_TIMING_INFO_POS))
#define VDO_IDR_ENABLE                                          VDO_IDR_ENABLE
#define VDO_IDR_ENABLE_POS                                      (15U)
#define VDO_IDR_ENABLE_LEN                                      (1U)
#define VDO_IDR_ENABLE_MSK                                      (((1U<<VDO_IDR_ENABLE_LEN)-1)<<VDO_IDR_ENABLE_POS)
#define VDO_IDR_ENABLE_UMSK                                     (~(((1U<<VDO_IDR_ENABLE_LEN)-1)<<VDO_IDR_ENABLE_POS))

/* 0x28 : core_reg1 */
#define VDO_CORE_REG1_OFFSET                                    (0x28)
#define VDO_IMG_WIDTH                                           VDO_IMG_WIDTH
#define VDO_IMG_WIDTH_POS                                       (0U)
#define VDO_IMG_WIDTH_LEN                                       (11U)
#define VDO_IMG_WIDTH_MSK                                       (((1U<<VDO_IMG_WIDTH_LEN)-1)<<VDO_IMG_WIDTH_POS)
#define VDO_IMG_WIDTH_UMSK                                      (~(((1U<<VDO_IMG_WIDTH_LEN)-1)<<VDO_IMG_WIDTH_POS))

/* 0x2C : core_reg2 */
#define VDO_CORE_REG2_OFFSET                                    (0x2C)
#define VDO_IMG_HEIGHT                                          VDO_IMG_HEIGHT
#define VDO_IMG_HEIGHT_POS                                      (0U)
#define VDO_IMG_HEIGHT_LEN                                      (11U)
#define VDO_IMG_HEIGHT_MSK                                      (((1U<<VDO_IMG_HEIGHT_LEN)-1)<<VDO_IMG_HEIGHT_POS)
#define VDO_IMG_HEIGHT_UMSK                                     (~(((1U<<VDO_IMG_HEIGHT_LEN)-1)<<VDO_IMG_HEIGHT_POS))

/* 0x30 : core_reg3 */
#define VDO_CORE_REG3_OFFSET                                    (0x30)
#define VDO_TARGET_I_QP                                         VDO_TARGET_I_QP
#define VDO_TARGET_I_QP_POS                                     (0U)
#define VDO_TARGET_I_QP_LEN                                     (6U)
#define VDO_TARGET_I_QP_MSK                                     (((1U<<VDO_TARGET_I_QP_LEN)-1)<<VDO_TARGET_I_QP_POS)
#define VDO_TARGET_I_QP_UMSK                                    (~(((1U<<VDO_TARGET_I_QP_LEN)-1)<<VDO_TARGET_I_QP_POS))

/* 0x34 : core_reg4 */
#define VDO_CORE_REG4_OFFSET                                    (0x34)
#define VDO_CQP_OFFSET                                          VDO_CQP_OFFSET
#define VDO_CQP_OFFSET_POS                                      (0U)
#define VDO_CQP_OFFSET_LEN                                      (5U)
#define VDO_CQP_OFFSET_MSK                                      (((1U<<VDO_CQP_OFFSET_LEN)-1)<<VDO_CQP_OFFSET_POS)
#define VDO_CQP_OFFSET_UMSK                                     (~(((1U<<VDO_CQP_OFFSET_LEN)-1)<<VDO_CQP_OFFSET_POS))

/* 0x38 : core_reg5 */
#define VDO_CORE_REG5_OFFSET                                    (0x38)
#define VDO_TARGET_P_QP                                         VDO_TARGET_P_QP
#define VDO_TARGET_P_QP_POS                                     (0U)
#define VDO_TARGET_P_QP_LEN                                     (6U)
#define VDO_TARGET_P_QP_MSK                                     (((1U<<VDO_TARGET_P_QP_LEN)-1)<<VDO_TARGET_P_QP_POS)
#define VDO_TARGET_P_QP_UMSK                                    (~(((1U<<VDO_TARGET_P_QP_LEN)-1)<<VDO_TARGET_P_QP_POS))

/* 0x3C : core_reg6 */
#define VDO_CORE_REG6_OFFSET                                    (0x3C)
#define VDO_MB_LINES                                            VDO_MB_LINES
#define VDO_MB_LINES_POS                                        (0U)
#define VDO_MB_LINES_LEN                                        (7U)
#define VDO_MB_LINES_MSK                                        (((1U<<VDO_MB_LINES_LEN)-1)<<VDO_MB_LINES_POS)
#define VDO_MB_LINES_UMSK                                       (~(((1U<<VDO_MB_LINES_LEN)-1)<<VDO_MB_LINES_POS))

/* 0x40 : core_reg7 */
#define VDO_CORE_REG7_OFFSET                                    (0x40)
#define VDO_NUM_SLICES                                          VDO_NUM_SLICES
#define VDO_NUM_SLICES_POS                                      (0U)
#define VDO_NUM_SLICES_LEN                                      (4U)
#define VDO_NUM_SLICES_MSK                                      (((1U<<VDO_NUM_SLICES_LEN)-1)<<VDO_NUM_SLICES_POS)
#define VDO_NUM_SLICES_UMSK                                     (~(((1U<<VDO_NUM_SLICES_LEN)-1)<<VDO_NUM_SLICES_POS))

/* 0x44 : core_reg8 */
#define VDO_CORE_REG8_OFFSET                                    (0x44)
#define VDO_NUM_PFRAMES                                         VDO_NUM_PFRAMES
#define VDO_NUM_PFRAMES_POS                                     (0U)
#define VDO_NUM_PFRAMES_LEN                                     (10U)
#define VDO_NUM_PFRAMES_MSK                                     (((1U<<VDO_NUM_PFRAMES_LEN)-1)<<VDO_NUM_PFRAMES_POS)
#define VDO_NUM_PFRAMES_UMSK                                    (~(((1U<<VDO_NUM_PFRAMES_LEN)-1)<<VDO_NUM_PFRAMES_POS))

/* 0x48 : core_reg9 */
#define VDO_CORE_REG9_OFFSET                                    (0x48)
#define VDO_DIS_FILTER                                          VDO_DIS_FILTER
#define VDO_DIS_FILTER_POS                                      (0U)
#define VDO_DIS_FILTER_LEN                                      (1U)
#define VDO_DIS_FILTER_MSK                                      (((1U<<VDO_DIS_FILTER_LEN)-1)<<VDO_DIS_FILTER_POS)
#define VDO_DIS_FILTER_UMSK                                     (~(((1U<<VDO_DIS_FILTER_LEN)-1)<<VDO_DIS_FILTER_POS))

/* 0x4C : core_reg10 */
#define VDO_CORE_REG10_OFFSET                                   (0x4C)
#define VDO_ALPHA_OFF                                           VDO_ALPHA_OFF
#define VDO_ALPHA_OFF_POS                                       (0U)
#define VDO_ALPHA_OFF_LEN                                       (4U)
#define VDO_ALPHA_OFF_MSK                                       (((1U<<VDO_ALPHA_OFF_LEN)-1)<<VDO_ALPHA_OFF_POS)
#define VDO_ALPHA_OFF_UMSK                                      (~(((1U<<VDO_ALPHA_OFF_LEN)-1)<<VDO_ALPHA_OFF_POS))

/* 0x50 : core_reg11 */
#define VDO_CORE_REG11_OFFSET                                   (0x50)
#define VDO_BETA_OFF                                            VDO_BETA_OFF
#define VDO_BETA_OFF_POS                                        (0U)
#define VDO_BETA_OFF_LEN                                        (4U)
#define VDO_BETA_OFF_MSK                                        (((1U<<VDO_BETA_OFF_LEN)-1)<<VDO_BETA_OFF_POS)
#define VDO_BETA_OFF_UMSK                                       (~(((1U<<VDO_BETA_OFF_LEN)-1)<<VDO_BETA_OFF_POS))

/* 0x54 : core_reg12 */
#define VDO_CORE_REG12_OFFSET                                   (0x54)
#define VDO_PROFILE_IDC                                         VDO_PROFILE_IDC
#define VDO_PROFILE_IDC_POS                                     (0U)
#define VDO_PROFILE_IDC_LEN                                     (1U)
#define VDO_PROFILE_IDC_MSK                                     (((1U<<VDO_PROFILE_IDC_LEN)-1)<<VDO_PROFILE_IDC_POS)
#define VDO_PROFILE_IDC_UMSK                                    (~(((1U<<VDO_PROFILE_IDC_LEN)-1)<<VDO_PROFILE_IDC_POS))

/* 0x58 : core_reg13 */
#define VDO_CORE_REG13_OFFSET                                   (0x58)
#define VDO_LEVEL_IDC                                           VDO_LEVEL_IDC
#define VDO_LEVEL_IDC_POS                                       (0U)
#define VDO_LEVEL_IDC_LEN                                       (8U)
#define VDO_LEVEL_IDC_MSK                                       (((1U<<VDO_LEVEL_IDC_LEN)-1)<<VDO_LEVEL_IDC_POS)
#define VDO_LEVEL_IDC_UMSK                                      (~(((1U<<VDO_LEVEL_IDC_LEN)-1)<<VDO_LEVEL_IDC_POS))

/* 0x5C : core_reg14 */
#define VDO_CORE_REG14_OFFSET                                   (0x5C)
#define VDO_LUMA8X8_COST                                        VDO_LUMA8X8_COST
#define VDO_LUMA8X8_COST_POS                                    (0U)
#define VDO_LUMA8X8_COST_LEN                                    (3U)
#define VDO_LUMA8X8_COST_MSK                                    (((1U<<VDO_LUMA8X8_COST_LEN)-1)<<VDO_LUMA8X8_COST_POS)
#define VDO_LUMA8X8_COST_UMSK                                   (~(((1U<<VDO_LUMA8X8_COST_LEN)-1)<<VDO_LUMA8X8_COST_POS))
#define VDO_LUMA16X16_COST                                      VDO_LUMA16X16_COST
#define VDO_LUMA16X16_COST_POS                                  (3U)
#define VDO_LUMA16X16_COST_LEN                                  (3U)
#define VDO_LUMA16X16_COST_MSK                                  (((1U<<VDO_LUMA16X16_COST_LEN)-1)<<VDO_LUMA16X16_COST_POS)
#define VDO_LUMA16X16_COST_UMSK                                 (~(((1U<<VDO_LUMA16X16_COST_LEN)-1)<<VDO_LUMA16X16_COST_POS))
#define VDO_CHROMA8X8_COST                                      VDO_CHROMA8X8_COST
#define VDO_CHROMA8X8_COST_POS                                  (6U)
#define VDO_CHROMA8X8_COST_LEN                                  (3U)
#define VDO_CHROMA8X8_COST_MSK                                  (((1U<<VDO_CHROMA8X8_COST_LEN)-1)<<VDO_CHROMA8X8_COST_POS)
#define VDO_CHROMA8X8_COST_UMSK                                 (~(((1U<<VDO_CHROMA8X8_COST_LEN)-1)<<VDO_CHROMA8X8_COST_POS))

/* 0x64 : core_reg16 */
#define VDO_CORE_REG16_OFFSET                                   (0x64)
#define VDO_FRAME0                                              VDO_FRAME0
#define VDO_FRAME0_POS                                          (0U)
#define VDO_FRAME0_LEN                                          (14U)
#define VDO_FRAME0_MSK                                          (((1U<<VDO_FRAME0_LEN)-1)<<VDO_FRAME0_POS)
#define VDO_FRAME0_UMSK                                         (~(((1U<<VDO_FRAME0_LEN)-1)<<VDO_FRAME0_POS))

/* 0x68 : core_reg17 */
#define VDO_CORE_REG17_OFFSET                                   (0x68)
#define VDO_FRAME1                                              VDO_FRAME1
#define VDO_FRAME1_POS                                          (0U)
#define VDO_FRAME1_LEN                                          (14U)
#define VDO_FRAME1_MSK                                          (((1U<<VDO_FRAME1_LEN)-1)<<VDO_FRAME1_POS)
#define VDO_FRAME1_UMSK                                         (~(((1U<<VDO_FRAME1_LEN)-1)<<VDO_FRAME1_POS))

/* 0x6C : core_reg18 */
#define VDO_CORE_REG18_OFFSET                                   (0x6C)
#define VDO_EXT_DATA                                            VDO_EXT_DATA
#define VDO_EXT_DATA_POS                                        (0U)
#define VDO_EXT_DATA_LEN                                        (14U)
#define VDO_EXT_DATA_MSK                                        (((1U<<VDO_EXT_DATA_LEN)-1)<<VDO_EXT_DATA_POS)
#define VDO_EXT_DATA_UMSK                                       (~(((1U<<VDO_EXT_DATA_LEN)-1)<<VDO_EXT_DATA_POS))

/* 0x70 : core_reg19 */
#define VDO_CORE_REG19_OFFSET                                   (0x70)
#define VDO_EXT_MEM_CONFIG0                                     VDO_EXT_MEM_CONFIG0
#define VDO_EXT_MEM_CONFIG0_POS                                 (0U)
#define VDO_EXT_MEM_CONFIG0_LEN                                 (6U)
#define VDO_EXT_MEM_CONFIG0_MSK                                 (((1U<<VDO_EXT_MEM_CONFIG0_LEN)-1)<<VDO_EXT_MEM_CONFIG0_POS)
#define VDO_EXT_MEM_CONFIG0_UMSK                                (~(((1U<<VDO_EXT_MEM_CONFIG0_LEN)-1)<<VDO_EXT_MEM_CONFIG0_POS))

/* 0x74 : core_reg20 */
#define VDO_CORE_REG20_OFFSET                                   (0x74)
#define VDO_EXT_MEM_CONFIG1                                     VDO_EXT_MEM_CONFIG1
#define VDO_EXT_MEM_CONFIG1_POS                                 (0U)
#define VDO_EXT_MEM_CONFIG1_LEN                                 (5U)
#define VDO_EXT_MEM_CONFIG1_MSK                                 (((1U<<VDO_EXT_MEM_CONFIG1_LEN)-1)<<VDO_EXT_MEM_CONFIG1_POS)
#define VDO_EXT_MEM_CONFIG1_UMSK                                (~(((1U<<VDO_EXT_MEM_CONFIG1_LEN)-1)<<VDO_EXT_MEM_CONFIG1_POS))

/* 0x78 : core_reg21 */
#define VDO_CORE_REG21_OFFSET                                   (0x78)
#define VDO_EXT_MEM_CONFIG2                                     VDO_EXT_MEM_CONFIG2
#define VDO_EXT_MEM_CONFIG2_POS                                 (0U)
#define VDO_EXT_MEM_CONFIG2_LEN                                 (12U)
#define VDO_EXT_MEM_CONFIG2_MSK                                 (((1U<<VDO_EXT_MEM_CONFIG2_LEN)-1)<<VDO_EXT_MEM_CONFIG2_POS)
#define VDO_EXT_MEM_CONFIG2_UMSK                                (~(((1U<<VDO_EXT_MEM_CONFIG2_LEN)-1)<<VDO_EXT_MEM_CONFIG2_POS))

/* 0x7C : core_reg22 */
#define VDO_CORE_REG22_OFFSET                                   (0x7C)
#define VDO_EXT_MEM_CONFIG3                                     VDO_EXT_MEM_CONFIG3
#define VDO_EXT_MEM_CONFIG3_POS                                 (0U)
#define VDO_EXT_MEM_CONFIG3_LEN                                 (10U)
#define VDO_EXT_MEM_CONFIG3_MSK                                 (((1U<<VDO_EXT_MEM_CONFIG3_LEN)-1)<<VDO_EXT_MEM_CONFIG3_POS)
#define VDO_EXT_MEM_CONFIG3_UMSK                                (~(((1U<<VDO_EXT_MEM_CONFIG3_LEN)-1)<<VDO_EXT_MEM_CONFIG3_POS))

/* 0x80 : core_reg23 */
#define VDO_CORE_REG23_OFFSET                                   (0x80)
#define VDO_NUM_IMB_BITS                                        VDO_NUM_IMB_BITS
#define VDO_NUM_IMB_BITS_POS                                    (0U)
#define VDO_NUM_IMB_BITS_LEN                                    (12U)
#define VDO_NUM_IMB_BITS_MSK                                    (((1U<<VDO_NUM_IMB_BITS_LEN)-1)<<VDO_NUM_IMB_BITS_POS)
#define VDO_NUM_IMB_BITS_UMSK                                   (~(((1U<<VDO_NUM_IMB_BITS_LEN)-1)<<VDO_NUM_IMB_BITS_POS))
#define VDO_NAL_ALIGN                                           VDO_NAL_ALIGN
#define VDO_NAL_ALIGN_POS                                       (13U)
#define VDO_NAL_ALIGN_LEN                                       (1U)
#define VDO_NAL_ALIGN_MSK                                       (((1U<<VDO_NAL_ALIGN_LEN)-1)<<VDO_NAL_ALIGN_POS)
#define VDO_NAL_ALIGN_UMSK                                      (~(((1U<<VDO_NAL_ALIGN_LEN)-1)<<VDO_NAL_ALIGN_POS))
#define VDO_CONS_IPRED                                          VDO_CONS_IPRED
#define VDO_CONS_IPRED_POS                                      (14U)
#define VDO_CONS_IPRED_LEN                                      (1U)
#define VDO_CONS_IPRED_MSK                                      (((1U<<VDO_CONS_IPRED_LEN)-1)<<VDO_CONS_IPRED_POS)
#define VDO_CONS_IPRED_UMSK                                     (~(((1U<<VDO_CONS_IPRED_LEN)-1)<<VDO_CONS_IPRED_POS))

/* 0x84 : core_reg24 */
#define VDO_CORE_REG24_OFFSET                                   (0x84)
#define VDO_NUM_PMB_BITS                                        VDO_NUM_PMB_BITS
#define VDO_NUM_PMB_BITS_POS                                    (0U)
#define VDO_NUM_PMB_BITS_LEN                                    (12U)
#define VDO_NUM_PMB_BITS_MSK                                    (((1U<<VDO_NUM_PMB_BITS_LEN)-1)<<VDO_NUM_PMB_BITS_POS)
#define VDO_NUM_PMB_BITS_UMSK                                   (~(((1U<<VDO_NUM_PMB_BITS_LEN)-1)<<VDO_NUM_PMB_BITS_POS))

/* 0x88 : core_reg25 */
#define VDO_CORE_REG25_OFFSET                                   (0x88)
#define VDO_INTERLACE_MODE                                      VDO_INTERLACE_MODE
#define VDO_INTERLACE_MODE_POS                                  (0U)
#define VDO_INTERLACE_MODE_LEN                                  (1U)
#define VDO_INTERLACE_MODE_MSK                                  (((1U<<VDO_INTERLACE_MODE_LEN)-1)<<VDO_INTERLACE_MODE_POS)
#define VDO_INTERLACE_MODE_UMSK                                 (~(((1U<<VDO_INTERLACE_MODE_LEN)-1)<<VDO_INTERLACE_MODE_POS))
#define VDO_BOTTOM_FIELD_FIRST                                  VDO_BOTTOM_FIELD_FIRST
#define VDO_BOTTOM_FIELD_FIRST_POS                              (1U)
#define VDO_BOTTOM_FIELD_FIRST_LEN                              (1U)
#define VDO_BOTTOM_FIELD_FIRST_MSK                              (((1U<<VDO_BOTTOM_FIELD_FIRST_LEN)-1)<<VDO_BOTTOM_FIELD_FIRST_POS)
#define VDO_BOTTOM_FIELD_FIRST_UMSK                             (~(((1U<<VDO_BOTTOM_FIELD_FIRST_LEN)-1)<<VDO_BOTTOM_FIELD_FIRST_POS))
#define VDO_PREV_FIELD_REF                                      VDO_PREV_FIELD_REF
#define VDO_PREV_FIELD_REF_POS                                  (2U)
#define VDO_PREV_FIELD_REF_LEN                                  (1U)
#define VDO_PREV_FIELD_REF_MSK                                  (((1U<<VDO_PREV_FIELD_REF_LEN)-1)<<VDO_PREV_FIELD_REF_POS)
#define VDO_PREV_FIELD_REF_UMSK                                 (~(((1U<<VDO_PREV_FIELD_REF_LEN)-1)<<VDO_PREV_FIELD_REF_POS))

/* 0x94 : core_reg28 */
#define VDO_CORE_REG28_OFFSET                                   (0x94)
#define VDO_PFRAME_MIN_QP                                       VDO_PFRAME_MIN_QP
#define VDO_PFRAME_MIN_QP_POS                                   (0U)
#define VDO_PFRAME_MIN_QP_LEN                                   (6U)
#define VDO_PFRAME_MIN_QP_MSK                                   (((1U<<VDO_PFRAME_MIN_QP_LEN)-1)<<VDO_PFRAME_MIN_QP_POS)
#define VDO_PFRAME_MIN_QP_UMSK                                  (~(((1U<<VDO_PFRAME_MIN_QP_LEN)-1)<<VDO_PFRAME_MIN_QP_POS))
#define VDO_PFRAME_MAX_QP                                       VDO_PFRAME_MAX_QP
#define VDO_PFRAME_MAX_QP_POS                                   (8U)
#define VDO_PFRAME_MAX_QP_LEN                                   (6U)
#define VDO_PFRAME_MAX_QP_MSK                                   (((1U<<VDO_PFRAME_MAX_QP_LEN)-1)<<VDO_PFRAME_MAX_QP_POS)
#define VDO_PFRAME_MAX_QP_UMSK                                  (~(((1U<<VDO_PFRAME_MAX_QP_LEN)-1)<<VDO_PFRAME_MAX_QP_POS))

/* 0x9C : core_reg30 */
#define VDO_CORE_REG30_OFFSET                                   (0x9C)
#define VDO_RESET_I_STATE                                       VDO_RESET_I_STATE
#define VDO_RESET_I_STATE_POS                                   (15U)
#define VDO_RESET_I_STATE_LEN                                   (1U)
#define VDO_RESET_I_STATE_MSK                                   (((1U<<VDO_RESET_I_STATE_LEN)-1)<<VDO_RESET_I_STATE_POS)
#define VDO_RESET_I_STATE_UMSK                                  (~(((1U<<VDO_RESET_I_STATE_LEN)-1)<<VDO_RESET_I_STATE_POS))

/* 0xA0 : core_reg31 */
#define VDO_CORE_REG31_OFFSET                                   (0xA0)
#define VDO_IFRAME_MIN_QP                                       VDO_IFRAME_MIN_QP
#define VDO_IFRAME_MIN_QP_POS                                   (0U)
#define VDO_IFRAME_MIN_QP_LEN                                   (6U)
#define VDO_IFRAME_MIN_QP_MSK                                   (((1U<<VDO_IFRAME_MIN_QP_LEN)-1)<<VDO_IFRAME_MIN_QP_POS)
#define VDO_IFRAME_MIN_QP_UMSK                                  (~(((1U<<VDO_IFRAME_MIN_QP_LEN)-1)<<VDO_IFRAME_MIN_QP_POS))
#define VDO_IFRAME_MAX_QP                                       VDO_IFRAME_MAX_QP
#define VDO_IFRAME_MAX_QP_POS                                   (8U)
#define VDO_IFRAME_MAX_QP_LEN                                   (6U)
#define VDO_IFRAME_MAX_QP_MSK                                   (((1U<<VDO_IFRAME_MAX_QP_LEN)-1)<<VDO_IFRAME_MAX_QP_POS)
#define VDO_IFRAME_MAX_QP_UMSK                                  (~(((1U<<VDO_IFRAME_MAX_QP_LEN)-1)<<VDO_IFRAME_MAX_QP_POS))

/* 0xA4 : core_reg32 */
#define VDO_CORE_REG32_OFFSET                                   (0xA4)
#define VDO_VUI_TIME_SCALE_L                                    VDO_VUI_TIME_SCALE_L
#define VDO_VUI_TIME_SCALE_L_POS                                (0U)
#define VDO_VUI_TIME_SCALE_L_LEN                                (16U)
#define VDO_VUI_TIME_SCALE_L_MSK                                (((1U<<VDO_VUI_TIME_SCALE_L_LEN)-1)<<VDO_VUI_TIME_SCALE_L_POS)
#define VDO_VUI_TIME_SCALE_L_UMSK                               (~(((1U<<VDO_VUI_TIME_SCALE_L_LEN)-1)<<VDO_VUI_TIME_SCALE_L_POS))

/* 0xA8 : core_reg33 */
#define VDO_CORE_REG33_OFFSET                                   (0xA8)
#define VDO_VUI_TIME_SCALE_H                                    VDO_VUI_TIME_SCALE_H
#define VDO_VUI_TIME_SCALE_H_POS                                (0U)
#define VDO_VUI_TIME_SCALE_H_LEN                                (16U)
#define VDO_VUI_TIME_SCALE_H_MSK                                (((1U<<VDO_VUI_TIME_SCALE_H_LEN)-1)<<VDO_VUI_TIME_SCALE_H_POS)
#define VDO_VUI_TIME_SCALE_H_UMSK                               (~(((1U<<VDO_VUI_TIME_SCALE_H_LEN)-1)<<VDO_VUI_TIME_SCALE_H_POS))

/* 0xAC : core_reg34 */
#define VDO_CORE_REG34_OFFSET                                   (0xAC)
#define VDO_VUI_NUM_U_TICK_L                                    VDO_VUI_NUM_U_TICK_L
#define VDO_VUI_NUM_U_TICK_L_POS                                (0U)
#define VDO_VUI_NUM_U_TICK_L_LEN                                (16U)
#define VDO_VUI_NUM_U_TICK_L_MSK                                (((1U<<VDO_VUI_NUM_U_TICK_L_LEN)-1)<<VDO_VUI_NUM_U_TICK_L_POS)
#define VDO_VUI_NUM_U_TICK_L_UMSK                               (~(((1U<<VDO_VUI_NUM_U_TICK_L_LEN)-1)<<VDO_VUI_NUM_U_TICK_L_POS))

/* 0xB0 : core_reg35 */
#define VDO_CORE_REG35_OFFSET                                   (0xB0)
#define VDO_VUI_NUM_U_TICK_H                                    VDO_VUI_NUM_U_TICK_H
#define VDO_VUI_NUM_U_TICK_H_POS                                (0U)
#define VDO_VUI_NUM_U_TICK_H_LEN                                (16U)
#define VDO_VUI_NUM_U_TICK_H_MSK                                (((1U<<VDO_VUI_NUM_U_TICK_H_LEN)-1)<<VDO_VUI_NUM_U_TICK_H_POS)
#define VDO_VUI_NUM_U_TICK_H_UMSK                               (~(((1U<<VDO_VUI_NUM_U_TICK_H_LEN)-1)<<VDO_VUI_NUM_U_TICK_H_POS))

/* 0xB4 : core_reg36 */
#define VDO_CORE_REG36_OFFSET                                   (0xB4)
#define VDO_VUI_ASPECT_IDC                                      VDO_VUI_ASPECT_IDC
#define VDO_VUI_ASPECT_IDC_POS                                  (0U)
#define VDO_VUI_ASPECT_IDC_LEN                                  (8U)
#define VDO_VUI_ASPECT_IDC_MSK                                  (((1U<<VDO_VUI_ASPECT_IDC_LEN)-1)<<VDO_VUI_ASPECT_IDC_POS)
#define VDO_VUI_ASPECT_IDC_UMSK                                 (~(((1U<<VDO_VUI_ASPECT_IDC_LEN)-1)<<VDO_VUI_ASPECT_IDC_POS))

/* 0xB8 : core_reg37 */
#define VDO_CORE_REG37_OFFSET                                   (0xB8)
#define VDO_VUI_ASPECT_WIDTH                                    VDO_VUI_ASPECT_WIDTH
#define VDO_VUI_ASPECT_WIDTH_POS                                (0U)
#define VDO_VUI_ASPECT_WIDTH_LEN                                (16U)
#define VDO_VUI_ASPECT_WIDTH_MSK                                (((1U<<VDO_VUI_ASPECT_WIDTH_LEN)-1)<<VDO_VUI_ASPECT_WIDTH_POS)
#define VDO_VUI_ASPECT_WIDTH_UMSK                               (~(((1U<<VDO_VUI_ASPECT_WIDTH_LEN)-1)<<VDO_VUI_ASPECT_WIDTH_POS))

/* 0xBC : core_reg38 */
#define VDO_CORE_REG38_OFFSET                                   (0xBC)
#define VDO_VUI_ASPECT_HEIGHT                                   VDO_VUI_ASPECT_HEIGHT
#define VDO_VUI_ASPECT_HEIGHT_POS                               (0U)
#define VDO_VUI_ASPECT_HEIGHT_LEN                               (16U)
#define VDO_VUI_ASPECT_HEIGHT_MSK                               (((1U<<VDO_VUI_ASPECT_HEIGHT_LEN)-1)<<VDO_VUI_ASPECT_HEIGHT_POS)
#define VDO_VUI_ASPECT_HEIGHT_UMSK                              (~(((1U<<VDO_VUI_ASPECT_HEIGHT_LEN)-1)<<VDO_VUI_ASPECT_HEIGHT_POS))

/* 0xC0 : src_dvp_sel */
#define VDO_SRC_DVP_SEL_OFFSET                                  (0xC0)
#define VDO_UV_DVP2AXI_SEL                                      VDO_UV_DVP2AXI_SEL
#define VDO_UV_DVP2AXI_SEL_POS                                  (0U)
#define VDO_UV_DVP2AXI_SEL_LEN                                  (2U)
#define VDO_UV_DVP2AXI_SEL_MSK                                  (((1U<<VDO_UV_DVP2AXI_SEL_LEN)-1)<<VDO_UV_DVP2AXI_SEL_POS)
#define VDO_UV_DVP2AXI_SEL_UMSK                                 (~(((1U<<VDO_UV_DVP2AXI_SEL_LEN)-1)<<VDO_UV_DVP2AXI_SEL_POS))
#define VDO_Y_DVP2AXI_SEL                                       VDO_Y_DVP2AXI_SEL
#define VDO_Y_DVP2AXI_SEL_POS                                   (2U)
#define VDO_Y_DVP2AXI_SEL_LEN                                   (2U)
#define VDO_Y_DVP2AXI_SEL_MSK                                   (((1U<<VDO_Y_DVP2AXI_SEL_LEN)-1)<<VDO_Y_DVP2AXI_SEL_POS)
#define VDO_Y_DVP2AXI_SEL_UMSK                                  (~(((1U<<VDO_Y_DVP2AXI_SEL_LEN)-1)<<VDO_Y_DVP2AXI_SEL_POS))

/* 0xC4 : padding_ctrl */
#define VDO_PADDING_CTRL_OFFSET                                 (0xC4)
#define VDO_Y_PADDING_PIXEL                                     VDO_Y_PADDING_PIXEL
#define VDO_Y_PADDING_PIXEL_POS                                 (0U)
#define VDO_Y_PADDING_PIXEL_LEN                                 (8U)
#define VDO_Y_PADDING_PIXEL_MSK                                 (((1U<<VDO_Y_PADDING_PIXEL_LEN)-1)<<VDO_Y_PADDING_PIXEL_POS)
#define VDO_Y_PADDING_PIXEL_UMSK                                (~(((1U<<VDO_Y_PADDING_PIXEL_LEN)-1)<<VDO_Y_PADDING_PIXEL_POS))
#define VDO_U_PADDING_PIXEL                                     VDO_U_PADDING_PIXEL
#define VDO_U_PADDING_PIXEL_POS                                 (8U)
#define VDO_U_PADDING_PIXEL_LEN                                 (8U)
#define VDO_U_PADDING_PIXEL_MSK                                 (((1U<<VDO_U_PADDING_PIXEL_LEN)-1)<<VDO_U_PADDING_PIXEL_POS)
#define VDO_U_PADDING_PIXEL_UMSK                                (~(((1U<<VDO_U_PADDING_PIXEL_LEN)-1)<<VDO_U_PADDING_PIXEL_POS))
#define VDO_V_PADDING_PIXEL                                     VDO_V_PADDING_PIXEL
#define VDO_V_PADDING_PIXEL_POS                                 (16U)
#define VDO_V_PADDING_PIXEL_LEN                                 (8U)
#define VDO_V_PADDING_PIXEL_MSK                                 (((1U<<VDO_V_PADDING_PIXEL_LEN)-1)<<VDO_V_PADDING_PIXEL_POS)
#define VDO_V_PADDING_PIXEL_UMSK                                (~(((1U<<VDO_V_PADDING_PIXEL_LEN)-1)<<VDO_V_PADDING_PIXEL_POS))
#define VDO_Y_LINE_PAD                                          VDO_Y_LINE_PAD
#define VDO_Y_LINE_PAD_POS                                      (24U)
#define VDO_Y_LINE_PAD_LEN                                      (5U)
#define VDO_Y_LINE_PAD_MSK                                      (((1U<<VDO_Y_LINE_PAD_LEN)-1)<<VDO_Y_LINE_PAD_POS)
#define VDO_Y_LINE_PAD_UMSK                                     (~(((1U<<VDO_Y_LINE_PAD_LEN)-1)<<VDO_Y_LINE_PAD_POS))

/* 0xC8 : h264_cref0_base_addr */
#define VDO_H264_CREF0_BASE_ADDR_OFFSET                         (0xC8)
#define VDO_H264_CREF0_BASE_ADDR                                VDO_H264_CREF0_BASE_ADDR
#define VDO_H264_CREF0_BASE_ADDR_POS                            (0U)
#define VDO_H264_CREF0_BASE_ADDR_LEN                            (32U)
#define VDO_H264_CREF0_BASE_ADDR_MSK                            (((1U<<VDO_H264_CREF0_BASE_ADDR_LEN)-1)<<VDO_H264_CREF0_BASE_ADDR_POS)
#define VDO_H264_CREF0_BASE_ADDR_UMSK                           (~(((1U<<VDO_H264_CREF0_BASE_ADDR_LEN)-1)<<VDO_H264_CREF0_BASE_ADDR_POS))

/* 0xCC : h264_cref1_base_addr */
#define VDO_H264_CREF1_BASE_ADDR_OFFSET                         (0xCC)
#define VDO_H264_CREF1_BASE_ADDR                                VDO_H264_CREF1_BASE_ADDR
#define VDO_H264_CREF1_BASE_ADDR_POS                            (0U)
#define VDO_H264_CREF1_BASE_ADDR_LEN                            (32U)
#define VDO_H264_CREF1_BASE_ADDR_MSK                            (((1U<<VDO_H264_CREF1_BASE_ADDR_LEN)-1)<<VDO_H264_CREF1_BASE_ADDR_POS)
#define VDO_H264_CREF1_BASE_ADDR_UMSK                           (~(((1U<<VDO_H264_CREF1_BASE_ADDR_LEN)-1)<<VDO_H264_CREF1_BASE_ADDR_POS))

/* 0xD0 : h264_head0_base_addr */
#define VDO_H264_HEAD0_BASE_ADDR_OFFSET                         (0xD0)
#define VDO_H264_HEAD0_BASE_ADDR                                VDO_H264_HEAD0_BASE_ADDR
#define VDO_H264_HEAD0_BASE_ADDR_POS                            (0U)
#define VDO_H264_HEAD0_BASE_ADDR_LEN                            (32U)
#define VDO_H264_HEAD0_BASE_ADDR_MSK                            (((1U<<VDO_H264_HEAD0_BASE_ADDR_LEN)-1)<<VDO_H264_HEAD0_BASE_ADDR_POS)
#define VDO_H264_HEAD0_BASE_ADDR_UMSK                           (~(((1U<<VDO_H264_HEAD0_BASE_ADDR_LEN)-1)<<VDO_H264_HEAD0_BASE_ADDR_POS))

/* 0xD4 : h264_head1_base_addr */
#define VDO_H264_HEAD1_BASE_ADDR_OFFSET                         (0xD4)
#define VDO_H264_HEAD1_BASE_ADDR                                VDO_H264_HEAD1_BASE_ADDR
#define VDO_H264_HEAD1_BASE_ADDR_POS                            (0U)
#define VDO_H264_HEAD1_BASE_ADDR_LEN                            (32U)
#define VDO_H264_HEAD1_BASE_ADDR_MSK                            (((1U<<VDO_H264_HEAD1_BASE_ADDR_LEN)-1)<<VDO_H264_HEAD1_BASE_ADDR_POS)
#define VDO_H264_HEAD1_BASE_ADDR_UMSK                           (~(((1U<<VDO_H264_HEAD1_BASE_ADDR_LEN)-1)<<VDO_H264_HEAD1_BASE_ADDR_POS))

/* 0xD8 : cref_qp */
#define VDO_CREF_QP_OFFSET                                      (0xD8)
#define VDO_CREF_QP                                             VDO_CREF_QP
#define VDO_CREF_QP_POS                                         (0U)
#define VDO_CREF_QP_LEN                                         (6U)
#define VDO_CREF_QP_MSK                                         (((1U<<VDO_CREF_QP_LEN)-1)<<VDO_CREF_QP_POS)
#define VDO_CREF_QP_UMSK                                        (~(((1U<<VDO_CREF_QP_LEN)-1)<<VDO_CREF_QP_POS))

/* 0x100 : vdo_int */
#define VDO_INT_OFFSET                                          (0x100)
#define VDO_FRM_DONE_INT                                        VDO_FRM_DONE_INT
#define VDO_FRM_DONE_INT_POS                                    (0U)
#define VDO_FRM_DONE_INT_LEN                                    (1U)
#define VDO_FRM_DONE_INT_MSK                                    (((1U<<VDO_FRM_DONE_INT_LEN)-1)<<VDO_FRM_DONE_INT_POS)
#define VDO_FRM_DONE_INT_UMSK                                   (~(((1U<<VDO_FRM_DONE_INT_LEN)-1)<<VDO_FRM_DONE_INT_POS))
#define VDO_SEQ_DONE_INT                                        VDO_SEQ_DONE_INT
#define VDO_SEQ_DONE_INT_POS                                    (4U)
#define VDO_SEQ_DONE_INT_LEN                                    (1U)
#define VDO_SEQ_DONE_INT_MSK                                    (((1U<<VDO_SEQ_DONE_INT_LEN)-1)<<VDO_SEQ_DONE_INT_POS)
#define VDO_SEQ_DONE_INT_UMSK                                   (~(((1U<<VDO_SEQ_DONE_INT_LEN)-1)<<VDO_SEQ_DONE_INT_POS))
#define VDO_BS_FULL_INT                                         VDO_BS_FULL_INT
#define VDO_BS_FULL_INT_POS                                     (8U)
#define VDO_BS_FULL_INT_LEN                                     (1U)
#define VDO_BS_FULL_INT_MSK                                     (((1U<<VDO_BS_FULL_INT_LEN)-1)<<VDO_BS_FULL_INT_POS)
#define VDO_BS_FULL_INT_UMSK                                    (~(((1U<<VDO_BS_FULL_INT_LEN)-1)<<VDO_BS_FULL_INT_POS))

/* 0x104 : vdo_int_clr */
#define VDO_INT_CLR_OFFSET                                      (0x104)
#define VDO_FRM_DONE_INT_CLR                                    VDO_FRM_DONE_INT_CLR
#define VDO_FRM_DONE_INT_CLR_POS                                (0U)
#define VDO_FRM_DONE_INT_CLR_LEN                                (1U)
#define VDO_FRM_DONE_INT_CLR_MSK                                (((1U<<VDO_FRM_DONE_INT_CLR_LEN)-1)<<VDO_FRM_DONE_INT_CLR_POS)
#define VDO_FRM_DONE_INT_CLR_UMSK                               (~(((1U<<VDO_FRM_DONE_INT_CLR_LEN)-1)<<VDO_FRM_DONE_INT_CLR_POS))
#define VDO_SEQ_DONE_INT_CLR                                    VDO_SEQ_DONE_INT_CLR
#define VDO_SEQ_DONE_INT_CLR_POS                                (4U)
#define VDO_SEQ_DONE_INT_CLR_LEN                                (1U)
#define VDO_SEQ_DONE_INT_CLR_MSK                                (((1U<<VDO_SEQ_DONE_INT_CLR_LEN)-1)<<VDO_SEQ_DONE_INT_CLR_POS)
#define VDO_SEQ_DONE_INT_CLR_UMSK                               (~(((1U<<VDO_SEQ_DONE_INT_CLR_LEN)-1)<<VDO_SEQ_DONE_INT_CLR_POS))
#define VDO_BS_FULL_INT_CLR                                     VDO_BS_FULL_INT_CLR
#define VDO_BS_FULL_INT_CLR_POS                                 (8U)
#define VDO_BS_FULL_INT_CLR_LEN                                 (1U)
#define VDO_BS_FULL_INT_CLR_MSK                                 (((1U<<VDO_BS_FULL_INT_CLR_LEN)-1)<<VDO_BS_FULL_INT_CLR_POS)
#define VDO_BS_FULL_INT_CLR_UMSK                                (~(((1U<<VDO_BS_FULL_INT_CLR_LEN)-1)<<VDO_BS_FULL_INT_CLR_POS))

/* 0x108 : vdo_int_mask */
#define VDO_INT_MASK_OFFSET                                     (0x108)
#define VDO_FRM_DONE_INT_MASK                                   VDO_FRM_DONE_INT_MASK
#define VDO_FRM_DONE_INT_MASK_POS                               (0U)
#define VDO_FRM_DONE_INT_MASK_LEN                               (1U)
#define VDO_FRM_DONE_INT_MASK_MSK                               (((1U<<VDO_FRM_DONE_INT_MASK_LEN)-1)<<VDO_FRM_DONE_INT_MASK_POS)
#define VDO_FRM_DONE_INT_MASK_UMSK                              (~(((1U<<VDO_FRM_DONE_INT_MASK_LEN)-1)<<VDO_FRM_DONE_INT_MASK_POS))
#define VDO_SEQ_DONE_INT_MASK                                   VDO_SEQ_DONE_INT_MASK
#define VDO_SEQ_DONE_INT_MASK_POS                               (4U)
#define VDO_SEQ_DONE_INT_MASK_LEN                               (1U)
#define VDO_SEQ_DONE_INT_MASK_MSK                               (((1U<<VDO_SEQ_DONE_INT_MASK_LEN)-1)<<VDO_SEQ_DONE_INT_MASK_POS)
#define VDO_SEQ_DONE_INT_MASK_UMSK                              (~(((1U<<VDO_SEQ_DONE_INT_MASK_LEN)-1)<<VDO_SEQ_DONE_INT_MASK_POS))
#define VDO_BS_FULL_INT_MASK                                    VDO_BS_FULL_INT_MASK
#define VDO_BS_FULL_INT_MASK_POS                                (8U)
#define VDO_BS_FULL_INT_MASK_LEN                                (1U)
#define VDO_BS_FULL_INT_MASK_MSK                                (((1U<<VDO_BS_FULL_INT_MASK_LEN)-1)<<VDO_BS_FULL_INT_MASK_POS)
#define VDO_BS_FULL_INT_MASK_UMSK                               (~(((1U<<VDO_BS_FULL_INT_MASK_LEN)-1)<<VDO_BS_FULL_INT_MASK_POS))

/* 0x10C : vdo_total_bytecount */
#define VDO_TOTAL_BYTECOUNT_OFFSET                              (0x10C)
#define VDO_BS_TOT_BYCNT                                        VDO_BS_TOT_BYCNT
#define VDO_BS_TOT_BYCNT_POS                                    (0U)
#define VDO_BS_TOT_BYCNT_LEN                                    (32U)
#define VDO_BS_TOT_BYCNT_MSK                                    (((1U<<VDO_BS_TOT_BYCNT_LEN)-1)<<VDO_BS_TOT_BYCNT_POS)
#define VDO_BS_TOT_BYCNT_UMSK                                   (~(((1U<<VDO_BS_TOT_BYCNT_LEN)-1)<<VDO_BS_TOT_BYCNT_POS))

/* 0x110 : vdo_frame_bytecount */
#define VDO_FRAME_BYTECOUNT_OFFSET                              (0x110)
#define VDO_BS_FRM_BYCNT                                        VDO_BS_FRM_BYCNT
#define VDO_BS_FRM_BYCNT_POS                                    (0U)
#define VDO_BS_FRM_BYCNT_LEN                                    (32U)
#define VDO_BS_FRM_BYCNT_MSK                                    (((1U<<VDO_BS_FRM_BYCNT_LEN)-1)<<VDO_BS_FRM_BYCNT_POS)
#define VDO_BS_FRM_BYCNT_UMSK                                   (~(((1U<<VDO_BS_FRM_BYCNT_LEN)-1)<<VDO_BS_FRM_BYCNT_POS))

/* 0x114 : vdo_src_r_dbg */
#define VDO_SRC_R_DBG_OFFSET                                    (0x114)
#define VDO_Y_READ_MBX                                          VDO_Y_READ_MBX
#define VDO_Y_READ_MBX_POS                                      (0U)
#define VDO_Y_READ_MBX_LEN                                      (13U)
#define VDO_Y_READ_MBX_MSK                                      (((1U<<VDO_Y_READ_MBX_LEN)-1)<<VDO_Y_READ_MBX_POS)
#define VDO_Y_READ_MBX_UMSK                                     (~(((1U<<VDO_Y_READ_MBX_LEN)-1)<<VDO_Y_READ_MBX_POS))
#define VDO_UV_READ_MBX                                         VDO_UV_READ_MBX
#define VDO_UV_READ_MBX_POS                                     (16U)
#define VDO_UV_READ_MBX_LEN                                     (13U)
#define VDO_UV_READ_MBX_MSK                                     (((1U<<VDO_UV_READ_MBX_LEN)-1)<<VDO_UV_READ_MBX_POS)
#define VDO_UV_READ_MBX_UMSK                                    (~(((1U<<VDO_UV_READ_MBX_LEN)-1)<<VDO_UV_READ_MBX_POS))
#define VDO_AXI_R_IDLE                                          VDO_AXI_R_IDLE
#define VDO_AXI_R_IDLE_POS                                      (30U)
#define VDO_AXI_R_IDLE_LEN                                      (1U)
#define VDO_AXI_R_IDLE_MSK                                      (((1U<<VDO_AXI_R_IDLE_LEN)-1)<<VDO_AXI_R_IDLE_POS)
#define VDO_AXI_R_IDLE_UMSK                                     (~(((1U<<VDO_AXI_R_IDLE_LEN)-1)<<VDO_AXI_R_IDLE_POS))
#define VDO_SRC_WR_OV_RD                                        VDO_SRC_WR_OV_RD
#define VDO_SRC_WR_OV_RD_POS                                    (31U)
#define VDO_SRC_WR_OV_RD_LEN                                    (1U)
#define VDO_SRC_WR_OV_RD_MSK                                    (((1U<<VDO_SRC_WR_OV_RD_LEN)-1)<<VDO_SRC_WR_OV_RD_POS)
#define VDO_SRC_WR_OV_RD_UMSK                                   (~(((1U<<VDO_SRC_WR_OV_RD_LEN)-1)<<VDO_SRC_WR_OV_RD_POS))

/* 0x118 : vdo_core_dbg */
#define VDO_CORE_DBG_OFFSET                                     (0x118)
#define VDO_CORE_MBX                                            VDO_CORE_MBX
#define VDO_CORE_MBX_POS                                        (0U)
#define VDO_CORE_MBX_LEN                                        (7U)
#define VDO_CORE_MBX_MSK                                        (((1U<<VDO_CORE_MBX_LEN)-1)<<VDO_CORE_MBX_POS)
#define VDO_CORE_MBX_UMSK                                       (~(((1U<<VDO_CORE_MBX_LEN)-1)<<VDO_CORE_MBX_POS))
#define VDO_CORE_MBY                                            VDO_CORE_MBY
#define VDO_CORE_MBY_POS                                        (8U)
#define VDO_CORE_MBY_LEN                                        (7U)
#define VDO_CORE_MBY_MSK                                        (((1U<<VDO_CORE_MBY_LEN)-1)<<VDO_CORE_MBY_POS)
#define VDO_CORE_MBY_UMSK                                       (~(((1U<<VDO_CORE_MBY_LEN)-1)<<VDO_CORE_MBY_POS))
#define VDO_TCLOCK                                              VDO_TCLOCK
#define VDO_TCLOCK_POS                                          (16U)
#define VDO_TCLOCK_LEN                                          (10U)
#define VDO_TCLOCK_MSK                                          (((1U<<VDO_TCLOCK_LEN)-1)<<VDO_TCLOCK_POS)
#define VDO_TCLOCK_UMSK                                         (~(((1U<<VDO_TCLOCK_LEN)-1)<<VDO_TCLOCK_POS))
#define VDO_CORE_IDLE                                           VDO_CORE_IDLE
#define VDO_CORE_IDLE_POS                                       (27U)
#define VDO_CORE_IDLE_LEN                                       (1U)
#define VDO_CORE_IDLE_MSK                                       (((1U<<VDO_CORE_IDLE_LEN)-1)<<VDO_CORE_IDLE_POS)
#define VDO_CORE_IDLE_UMSK                                      (~(((1U<<VDO_CORE_IDLE_LEN)-1)<<VDO_CORE_IDLE_POS))
#define VDO_PFRAME                                              VDO_PFRAME
#define VDO_PFRAME_POS                                          (28U)
#define VDO_PFRAME_LEN                                          (1U)
#define VDO_PFRAME_MSK                                          (((1U<<VDO_PFRAME_LEN)-1)<<VDO_PFRAME_POS)
#define VDO_PFRAME_UMSK                                         (~(((1U<<VDO_PFRAME_LEN)-1)<<VDO_PFRAME_POS))
#define VDO_OCLK_EN                                             VDO_OCLK_EN
#define VDO_OCLK_EN_POS                                         (29U)
#define VDO_OCLK_EN_LEN                                         (1U)
#define VDO_OCLK_EN_MSK                                         (((1U<<VDO_OCLK_EN_LEN)-1)<<VDO_OCLK_EN_POS)
#define VDO_OCLK_EN_UMSK                                        (~(((1U<<VDO_OCLK_EN_LEN)-1)<<VDO_OCLK_EN_POS))
#define VDO_TIMEOUT_STATE                                       VDO_TIMEOUT_STATE
#define VDO_TIMEOUT_STATE_POS                                   (30U)
#define VDO_TIMEOUT_STATE_LEN                                   (1U)
#define VDO_TIMEOUT_STATE_MSK                                   (((1U<<VDO_TIMEOUT_STATE_LEN)-1)<<VDO_TIMEOUT_STATE_POS)
#define VDO_TIMEOUT_STATE_UMSK                                  (~(((1U<<VDO_TIMEOUT_STATE_LEN)-1)<<VDO_TIMEOUT_STATE_POS))
#define VDO_MEM_CTRL_IDLE                                       VDO_MEM_CTRL_IDLE
#define VDO_MEM_CTRL_IDLE_POS                                   (31U)
#define VDO_MEM_CTRL_IDLE_LEN                                   (1U)
#define VDO_MEM_CTRL_IDLE_MSK                                   (((1U<<VDO_MEM_CTRL_IDLE_LEN)-1)<<VDO_MEM_CTRL_IDLE_POS)
#define VDO_MEM_CTRL_IDLE_UMSK                                  (~(((1U<<VDO_MEM_CTRL_IDLE_LEN)-1)<<VDO_MEM_CTRL_IDLE_POS))

/* 0x11C : vdo_ctrl_dbg */
#define VDO_CTRL_DBG_OFFSET                                     (0x11C)
#define VDO_CTRL_STATE                                          VDO_CTRL_STATE
#define VDO_CTRL_STATE_POS                                      (0U)
#define VDO_CTRL_STATE_LEN                                      (3U)
#define VDO_CTRL_STATE_MSK                                      (((1U<<VDO_CTRL_STATE_LEN)-1)<<VDO_CTRL_STATE_POS)
#define VDO_CTRL_STATE_UMSK                                     (~(((1U<<VDO_CTRL_STATE_LEN)-1)<<VDO_CTRL_STATE_POS))
#define VDO_CTRL_CE                                             VDO_CTRL_CE
#define VDO_CTRL_CE_POS                                         (4U)
#define VDO_CTRL_CE_LEN                                         (1U)
#define VDO_CTRL_CE_MSK                                         (((1U<<VDO_CTRL_CE_LEN)-1)<<VDO_CTRL_CE_POS)
#define VDO_CTRL_CE_UMSK                                        (~(((1U<<VDO_CTRL_CE_LEN)-1)<<VDO_CTRL_CE_POS))

/* 0x120 : vdo_checksum_0 */
#define VDO_CHECKSUM_0_OFFSET                                   (0x120)
#define VDO0_AXI_RDATA_CHKSUM                                   VDO0_AXI_RDATA_CHKSUM
#define VDO0_AXI_RDATA_CHKSUM_POS                               (0U)
#define VDO0_AXI_RDATA_CHKSUM_LEN                               (32U)
#define VDO0_AXI_RDATA_CHKSUM_MSK                               (((1U<<VDO0_AXI_RDATA_CHKSUM_LEN)-1)<<VDO0_AXI_RDATA_CHKSUM_POS)
#define VDO0_AXI_RDATA_CHKSUM_UMSK                              (~(((1U<<VDO0_AXI_RDATA_CHKSUM_LEN)-1)<<VDO0_AXI_RDATA_CHKSUM_POS))

/* 0x124 : vdo_checksum_1 */
#define VDO_CHECKSUM_1_OFFSET                                   (0x124)
#define VDO0_AXI_WDATA_CHKSUM                                   VDO0_AXI_WDATA_CHKSUM
#define VDO0_AXI_WDATA_CHKSUM_POS                               (0U)
#define VDO0_AXI_WDATA_CHKSUM_LEN                               (32U)
#define VDO0_AXI_WDATA_CHKSUM_MSK                               (((1U<<VDO0_AXI_WDATA_CHKSUM_LEN)-1)<<VDO0_AXI_WDATA_CHKSUM_POS)
#define VDO0_AXI_WDATA_CHKSUM_UMSK                              (~(((1U<<VDO0_AXI_WDATA_CHKSUM_LEN)-1)<<VDO0_AXI_WDATA_CHKSUM_POS))

/* 0x128 : vdo_checksum_2 */
#define VDO_CHECKSUM_2_OFFSET                                   (0x128)
#define VDO1_AXI_RDATA_CHKSUM                                   VDO1_AXI_RDATA_CHKSUM
#define VDO1_AXI_RDATA_CHKSUM_POS                               (0U)
#define VDO1_AXI_RDATA_CHKSUM_LEN                               (32U)
#define VDO1_AXI_RDATA_CHKSUM_MSK                               (((1U<<VDO1_AXI_RDATA_CHKSUM_LEN)-1)<<VDO1_AXI_RDATA_CHKSUM_POS)
#define VDO1_AXI_RDATA_CHKSUM_UMSK                              (~(((1U<<VDO1_AXI_RDATA_CHKSUM_LEN)-1)<<VDO1_AXI_RDATA_CHKSUM_POS))

/* 0x12C : vdo_checksum_3 */
#define VDO_CHECKSUM_3_OFFSET                                   (0x12C)
#define VDO1_AXI_WDATA_CHKSUM                                   VDO1_AXI_WDATA_CHKSUM
#define VDO1_AXI_WDATA_CHKSUM_POS                               (0U)
#define VDO1_AXI_WDATA_CHKSUM_LEN                               (32U)
#define VDO1_AXI_WDATA_CHKSUM_MSK                               (((1U<<VDO1_AXI_WDATA_CHKSUM_LEN)-1)<<VDO1_AXI_WDATA_CHKSUM_POS)
#define VDO1_AXI_WDATA_CHKSUM_UMSK                              (~(((1U<<VDO1_AXI_WDATA_CHKSUM_LEN)-1)<<VDO1_AXI_WDATA_CHKSUM_POS))

/* 0x130 : vdo_checksum_4 */
#define VDO_CHECKSUM_4_OFFSET                                   (0x130)
#define VDO_LD_YBLK_CHKSUM                                      VDO_LD_YBLK_CHKSUM
#define VDO_LD_YBLK_CHKSUM_POS                                  (0U)
#define VDO_LD_YBLK_CHKSUM_LEN                                  (32U)
#define VDO_LD_YBLK_CHKSUM_MSK                                  (((1U<<VDO_LD_YBLK_CHKSUM_LEN)-1)<<VDO_LD_YBLK_CHKSUM_POS)
#define VDO_LD_YBLK_CHKSUM_UMSK                                 (~(((1U<<VDO_LD_YBLK_CHKSUM_LEN)-1)<<VDO_LD_YBLK_CHKSUM_POS))

/* 0x134 : vdo_checksum_5 */
#define VDO_CHECKSUM_5_OFFSET                                   (0x134)
#define VDO_LD_CBLK_CHKSUM                                      VDO_LD_CBLK_CHKSUM
#define VDO_LD_CBLK_CHKSUM_POS                                  (0U)
#define VDO_LD_CBLK_CHKSUM_LEN                                  (32U)
#define VDO_LD_CBLK_CHKSUM_MSK                                  (((1U<<VDO_LD_CBLK_CHKSUM_LEN)-1)<<VDO_LD_CBLK_CHKSUM_POS)
#define VDO_LD_CBLK_CHKSUM_UMSK                                 (~(((1U<<VDO_LD_CBLK_CHKSUM_LEN)-1)<<VDO_LD_CBLK_CHKSUM_POS))

/* 0x138 : vdo_checksum_6 */
#define VDO_CHECKSUM_6_OFFSET                                   (0x138)
#define VDO_MEM_DIN_CHKSUM                                      VDO_MEM_DIN_CHKSUM
#define VDO_MEM_DIN_CHKSUM_POS                                  (0U)
#define VDO_MEM_DIN_CHKSUM_LEN                                  (32U)
#define VDO_MEM_DIN_CHKSUM_MSK                                  (((1U<<VDO_MEM_DIN_CHKSUM_LEN)-1)<<VDO_MEM_DIN_CHKSUM_POS)
#define VDO_MEM_DIN_CHKSUM_UMSK                                 (~(((1U<<VDO_MEM_DIN_CHKSUM_LEN)-1)<<VDO_MEM_DIN_CHKSUM_POS))

/* 0x13C : vdo_checksum_7 */
#define VDO_CHECKSUM_7_OFFSET                                   (0x13C)
#define VDO_MEM_DOUT_CHKSUM                                     VDO_MEM_DOUT_CHKSUM
#define VDO_MEM_DOUT_CHKSUM_POS                                 (0U)
#define VDO_MEM_DOUT_CHKSUM_LEN                                 (32U)
#define VDO_MEM_DOUT_CHKSUM_MSK                                 (((1U<<VDO_MEM_DOUT_CHKSUM_LEN)-1)<<VDO_MEM_DOUT_CHKSUM_POS)
#define VDO_MEM_DOUT_CHKSUM_UMSK                                (~(((1U<<VDO_MEM_DOUT_CHKSUM_LEN)-1)<<VDO_MEM_DOUT_CHKSUM_POS))

/* 0x140 : vdo_cref_dbg */
#define VDO_CREF_DBG_OFFSET                                     (0x140)
#define VDO_CREF_D_WAIT                                         VDO_CREF_D_WAIT
#define VDO_CREF_D_WAIT_POS                                     (0U)
#define VDO_CREF_D_WAIT_LEN                                     (1U)
#define VDO_CREF_D_WAIT_MSK                                     (((1U<<VDO_CREF_D_WAIT_LEN)-1)<<VDO_CREF_D_WAIT_POS)
#define VDO_CREF_D_WAIT_UMSK                                    (~(((1U<<VDO_CREF_D_WAIT_LEN)-1)<<VDO_CREF_D_WAIT_POS))
#define VDO_CREF_D_FRAME_BUSY                                   VDO_CREF_D_FRAME_BUSY
#define VDO_CREF_D_FRAME_BUSY_POS                               (4U)
#define VDO_CREF_D_FRAME_BUSY_LEN                               (1U)
#define VDO_CREF_D_FRAME_BUSY_MSK                               (((1U<<VDO_CREF_D_FRAME_BUSY_LEN)-1)<<VDO_CREF_D_FRAME_BUSY_POS)
#define VDO_CREF_D_FRAME_BUSY_UMSK                              (~(((1U<<VDO_CREF_D_FRAME_BUSY_LEN)-1)<<VDO_CREF_D_FRAME_BUSY_POS))
#define VDO_CREF_D_DONE                                         VDO_CREF_D_DONE
#define VDO_CREF_D_DONE_POS                                     (8U)
#define VDO_CREF_D_DONE_LEN                                     (1U)
#define VDO_CREF_D_DONE_MSK                                     (((1U<<VDO_CREF_D_DONE_LEN)-1)<<VDO_CREF_D_DONE_POS)
#define VDO_CREF_D_DONE_UMSK                                    (~(((1U<<VDO_CREF_D_DONE_LEN)-1)<<VDO_CREF_D_DONE_POS))
#define VDO_CREF_E_WAIT                                         VDO_CREF_E_WAIT
#define VDO_CREF_E_WAIT_POS                                     (16U)
#define VDO_CREF_E_WAIT_LEN                                     (1U)
#define VDO_CREF_E_WAIT_MSK                                     (((1U<<VDO_CREF_E_WAIT_LEN)-1)<<VDO_CREF_E_WAIT_POS)
#define VDO_CREF_E_WAIT_UMSK                                    (~(((1U<<VDO_CREF_E_WAIT_LEN)-1)<<VDO_CREF_E_WAIT_POS))
#define VDO_CREF_E_FRAME_BUSY                                   VDO_CREF_E_FRAME_BUSY
#define VDO_CREF_E_FRAME_BUSY_POS                               (24U)
#define VDO_CREF_E_FRAME_BUSY_LEN                               (1U)
#define VDO_CREF_E_FRAME_BUSY_MSK                               (((1U<<VDO_CREF_E_FRAME_BUSY_LEN)-1)<<VDO_CREF_E_FRAME_BUSY_POS)
#define VDO_CREF_E_FRAME_BUSY_UMSK                              (~(((1U<<VDO_CREF_E_FRAME_BUSY_LEN)-1)<<VDO_CREF_E_FRAME_BUSY_POS))
#define VDO_CREF_E_DONE                                         VDO_CREF_E_DONE
#define VDO_CREF_E_DONE_POS                                     (28U)
#define VDO_CREF_E_DONE_LEN                                     (1U)
#define VDO_CREF_E_DONE_MSK                                     (((1U<<VDO_CREF_E_DONE_LEN)-1)<<VDO_CREF_E_DONE_POS)
#define VDO_CREF_E_DONE_UMSK                                    (~(((1U<<VDO_CREF_E_DONE_LEN)-1)<<VDO_CREF_E_DONE_POS))


struct  vdo_reg {
    /* 0x00 : h264_encoder_ctrl */
    union {
        struct {
            uint32_t cfg_enc_ctrl_mby_idx           :  7; /* [ 6: 0],        r/w,        0x0 */
            uint32_t reserved_7                     :  1; /* [    7],       rsvd,        0x0 */
            uint32_t cfg_core_clk_en                :  1; /* [    8],        r/w,        0x0 */
            uint32_t reserved_9_11                  :  3; /* [11: 9],       rsvd,        0x0 */
            uint32_t cfg_mem_clk_en                 :  1; /* [   12],        r/w,        0x0 */
            uint32_t reserved_13_15                 :  3; /* [15:13],       rsvd,        0x0 */
            uint32_t cfg_buf_clr                    :  1; /* [   16],        w1p,        0x0 */
            uint32_t reserved_17_19                 :  3; /* [19:17],       rsvd,        0x0 */
            uint32_t cfg_bs_status_init             :  1; /* [   20],        w1p,        0x0 */
            uint32_t reserved_21_23                 :  3; /* [23:21],       rsvd,        0x0 */
            uint32_t cfg_ctrl_mode                  :  2; /* [25:24],        r/w,        0x0 */
            uint32_t cfg_cref_en                    :  1; /* [   26],        r/w,        0x0 */
            uint32_t reserved_27                    :  1; /* [   27],       rsvd,        0x0 */
            uint32_t cfg_frame_start                :  1; /* [   28],        w1p,        0x0 */
            uint32_t cfg_enc_seq_en                 :  1; /* [   29],        r/w,        0x0 */
            uint32_t reserved_30_31                 :  2; /* [31:30],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } h264_encoder_ctrl;

    /* 0x04 : h264_frame_size */
    union {
        struct {
            uint32_t cfg_frame_width                : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15                 :  5; /* [15:11],       rsvd,        0x0 */
            uint32_t cfg_frame_height               : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31                 :  5; /* [31:27],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } h264_frame_size;

    /* 0x08 : h264_frame_base_addr_y */
    union {
        struct {
            uint32_t cfg_frame_base_addr_y          : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } h264_frame_base_addr_y;

    /* 0xC : h264_frame_base_addr_uv */
    union {
        struct {
            uint32_t cfg_frame_base_addr_uv         : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } h264_frame_base_addr_uv;

    /* 0x10 : h264_bs_base_addr */
    union {
        struct {
            uint32_t cfg_bs_base_addr               : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } h264_bs_base_addr;

    /* 0x14 : h264_ref_base_addr */
    union {
        struct {
            uint32_t cfg_ref_base_addr              : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } h264_ref_base_addr;

    /* 0x18 : h264_bs_size */
    union {
        struct {
            uint32_t cfg_bs_size                    : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } h264_bs_size;

    /* 0x1C : h264_bs_full_thr */
    union {
        struct {
            uint32_t cfg_bs_full_thr                : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } h264_bs_full_thr;

    /* 0x20 : h264_src_bf_height */
    union {
        struct {
            uint32_t cfg_c_src_bf_height            : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15                 :  5; /* [15:11],       rsvd,        0x0 */
            uint32_t cfg_y_src_bf_height            : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31                 :  5; /* [31:27],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } h264_src_bf_height;

    /* 0x24 : core_reg0 */
    union {
        struct {
            uint32_t ENC_EN                         :  1; /* [    0],        r/w,        0x0 */
            uint32_t reserved_1_11                  : 11; /* [11: 1],       rsvd,        0x0 */
            uint32_t VUI_ASPECT_INFO                :  1; /* [   12],        r/w,        0x0 */
            uint32_t VUI_FIXED_F_RATE               :  1; /* [   13],        r/w,        0x0 */
            uint32_t VUI_TIMING_INFO                :  1; /* [   14],        r/w,        0x0 */
            uint32_t IDR_ENABLE                     :  1; /* [   15],        r/w,        0x0 */
            uint32_t reserved_16_31                 : 16; /* [31:16],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } core_reg0;

    /* 0x28 : core_reg1 */
    union {
        struct {
            uint32_t IMG_WIDTH                      : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_31                 : 21; /* [31:11],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } core_reg1;

    /* 0x2C : core_reg2 */
    union {
        struct {
            uint32_t IMG_HEIGHT                     : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_31                 : 21; /* [31:11],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } core_reg2;

    /* 0x30 : core_reg3 */
    union {
        struct {
            uint32_t TARGET_I_QP                    :  6; /* [ 5: 0],        r/w,        0x0 */
            uint32_t reserved_6_31                  : 26; /* [31: 6],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } core_reg3;

    /* 0x34 : core_reg4 */
    union {
        struct {
            uint32_t CQP_OFFSET                     :  5; /* [ 4: 0],        r/w,        0x0 */
            uint32_t reserved_5_31                  : 27; /* [31: 5],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } core_reg4;

    /* 0x38 : core_reg5 */
    union {
        struct {
            uint32_t TARGET_P_QP                    :  6; /* [ 5: 0],        r/w,        0x0 */
            uint32_t reserved_6_31                  : 26; /* [31: 6],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } core_reg5;

    /* 0x3C : core_reg6 */
    union {
        struct {
            uint32_t MB_LINES                       :  7; /* [ 6: 0],        r/w,        0x0 */
            uint32_t reserved_7_31                  : 25; /* [31: 7],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } core_reg6;

    /* 0x40 : core_reg7 */
    union {
        struct {
            uint32_t NUM_SLICES                     :  4; /* [ 3: 0],        r/w,        0x0 */
            uint32_t reserved_4_31                  : 28; /* [31: 4],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } core_reg7;

    /* 0x44 : core_reg8 */
    union {
        struct {
            uint32_t NUM_PFRAMES                    : 10; /* [ 9: 0],        r/w,        0x0 */
            uint32_t reserved_10_31                 : 22; /* [31:10],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } core_reg8;

    /* 0x48 : core_reg9 */
    union {
        struct {
            uint32_t DIS_FILTER                     :  1; /* [    0],        r/w,        0x0 */
            uint32_t reserved_1_31                  : 31; /* [31: 1],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } core_reg9;

    /* 0x4C : core_reg10 */
    union {
        struct {
            uint32_t ALPHA_OFF                      :  4; /* [ 3: 0],        r/w,        0x0 */
            uint32_t reserved_4_31                  : 28; /* [31: 4],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } core_reg10;

    /* 0x50 : core_reg11 */
    union {
        struct {
            uint32_t BETA_OFF                       :  4; /* [ 3: 0],        r/w,        0x0 */
            uint32_t reserved_4_31                  : 28; /* [31: 4],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } core_reg11;

    /* 0x54 : core_reg12 */
    union {
        struct {
            uint32_t PROFILE_IDC                    :  1; /* [    0],        r/w,        0x0 */
            uint32_t reserved_1_31                  : 31; /* [31: 1],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } core_reg12;

    /* 0x58 : core_reg13 */
    union {
        struct {
            uint32_t LEVEL_IDC                      :  8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t reserved_8_31                  : 24; /* [31: 8],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } core_reg13;

    /* 0x5C : core_reg14 */
    union {
        struct {
            uint32_t LUMA8X8_COST                   :  3; /* [ 2: 0],        r/w,        0x0 */
            uint32_t LUMA16X16_COST                 :  3; /* [ 5: 3],        r/w,        0x0 */
            uint32_t CHROMA8X8_COST                 :  3; /* [ 8: 6],        r/w,        0x0 */
            uint32_t reserved_9_31                  : 23; /* [31: 9],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } core_reg14;

    /* 0x60  reserved */
    uint8_t RESERVED0x60[4];

    /* 0x64 : core_reg16 */
    union {
        struct {
            uint32_t FRAME0                         : 14; /* [13: 0],        r/w,        0x0 */
            uint32_t reserved_14_31                 : 18; /* [31:14],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } core_reg16;

    /* 0x68 : core_reg17 */
    union {
        struct {
            uint32_t FRAME1                         : 14; /* [13: 0],        r/w,        0x0 */
            uint32_t reserved_14_31                 : 18; /* [31:14],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } core_reg17;

    /* 0x6C : core_reg18 */
    union {
        struct {
            uint32_t EXT_DATA                       : 14; /* [13: 0],        r/w,        0x0 */
            uint32_t reserved_14_31                 : 18; /* [31:14],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } core_reg18;

    /* 0x70 : core_reg19 */
    union {
        struct {
            uint32_t EXT_MEM_CONFIG0                :  6; /* [ 5: 0],        r/w,        0x0 */
            uint32_t reserved_6_31                  : 26; /* [31: 6],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } core_reg19;

    /* 0x74 : core_reg20 */
    union {
        struct {
            uint32_t EXT_MEM_CONFIG1                :  5; /* [ 4: 0],        r/w,        0x0 */
            uint32_t reserved_5_31                  : 27; /* [31: 5],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } core_reg20;

    /* 0x78 : core_reg21 */
    union {
        struct {
            uint32_t EXT_MEM_CONFIG2                : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_31                 : 20; /* [31:12],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } core_reg21;

    /* 0x7C : core_reg22 */
    union {
        struct {
            uint32_t EXT_MEM_CONFIG3                : 10; /* [ 9: 0],        r/w,        0x0 */
            uint32_t reserved_10_31                 : 22; /* [31:10],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } core_reg22;

    /* 0x80 : core_reg23 */
    union {
        struct {
            uint32_t NUM_IMB_BITS                   : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12                    :  1; /* [   12],       rsvd,        0x0 */
            uint32_t NAL_ALIGN                      :  1; /* [   13],        r/w,        0x0 */
            uint32_t CONS_IPRED                     :  1; /* [   14],        r/w,        0x0 */
            uint32_t reserved_15_31                 : 17; /* [31:15],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } core_reg23;

    /* 0x84 : core_reg24 */
    union {
        struct {
            uint32_t NUM_PMB_BITS                   : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_31                 : 20; /* [31:12],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } core_reg24;

    /* 0x88 : core_reg25 */
    union {
        struct {
            uint32_t INTERLACE_MODE                 :  1; /* [    0],        r/w,        0x0 */
            uint32_t BOTTOM_FIELD_FIRST             :  1; /* [    1],        r/w,        0x0 */
            uint32_t PREV_FIELD_REF                 :  1; /* [    2],        r/w,        0x0 */
            uint32_t reserved_3_31                  : 29; /* [31: 3],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } core_reg25;

    /* 0x8c  reserved */
    uint8_t RESERVED0x8c[8];

    /* 0x94 : core_reg28 */
    union {
        struct {
            uint32_t PFRAME_MIN_QP                  :  6; /* [ 5: 0],        r/w,        0x0 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t PFRAME_MAX_QP                  :  6; /* [13: 8],        r/w,       0x33 */
            uint32_t reserved_14_31                 : 18; /* [31:14],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } core_reg28;

    /* 0x98  reserved */
    uint8_t RESERVED0x98[4];

    /* 0x9C : core_reg30 */
    union {
        struct {
            uint32_t reserved_0_14                  : 15; /* [14: 0],       rsvd,        0x0 */
            uint32_t RESET_I_STATE                  :  1; /* [   15],        r/w,        0x1 */
            uint32_t reserved_16_31                 : 16; /* [31:16],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } core_reg30;

    /* 0xA0 : core_reg31 */
    union {
        struct {
            uint32_t IFRAME_MIN_QP                  :  6; /* [ 5: 0],        r/w,        0x0 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t IFRAME_MAX_QP                  :  6; /* [13: 8],        r/w,       0x33 */
            uint32_t reserved_14_31                 : 18; /* [31:14],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } core_reg31;

    /* 0xA4 : core_reg32 */
    union {
        struct {
            uint32_t VUI_TIME_SCALE_L               : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t reserved_16_31                 : 16; /* [31:16],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } core_reg32;

    /* 0xA8 : core_reg33 */
    union {
        struct {
            uint32_t VUI_TIME_SCALE_H               : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t reserved_16_31                 : 16; /* [31:16],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } core_reg33;

    /* 0xAC : core_reg34 */
    union {
        struct {
            uint32_t VUI_NUM_U_TICK_L               : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t reserved_16_31                 : 16; /* [31:16],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } core_reg34;

    /* 0xB0 : core_reg35 */
    union {
        struct {
            uint32_t VUI_NUM_U_TICK_H               : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t reserved_16_31                 : 16; /* [31:16],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } core_reg35;

    /* 0xB4 : core_reg36 */
    union {
        struct {
            uint32_t VUI_ASPECT_IDC                 :  8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t reserved_8_31                  : 24; /* [31: 8],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } core_reg36;

    /* 0xB8 : core_reg37 */
    union {
        struct {
            uint32_t VUI_ASPECT_WIDTH               : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t reserved_16_31                 : 16; /* [31:16],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } core_reg37;

    /* 0xBC : core_reg38 */
    union {
        struct {
            uint32_t VUI_ASPECT_HEIGHT              : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t reserved_16_31                 : 16; /* [31:16],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } core_reg38;

    /* 0xC0 : src_dvp_sel */
    union {
        struct {
            uint32_t uv_dvp2axi_sel                 :  2; /* [ 1: 0],        r/w,        0x0 */
            uint32_t y_dvp2axi_sel                  :  2; /* [ 3: 2],        r/w,        0x0 */
            uint32_t reserved_4_31                  : 28; /* [31: 4],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } src_dvp_sel;

    /* 0xC4 : padding_ctrl */
    union {
        struct {
            uint32_t y_padding_pixel                :  8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t u_padding_pixel                :  8; /* [15: 8],        r/w,       0x80 */
            uint32_t v_padding_pixel                :  8; /* [23:16],        r/w,       0x80 */
            uint32_t y_line_pad                     :  5; /* [28:24],        r/w,        0x0 */
            uint32_t reserved_29_31                 :  3; /* [31:29],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } padding_ctrl;

    /* 0xC8 : h264_cref0_base_addr */
    union {
        struct {
            uint32_t h264_cref0_base_addr           : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } h264_cref0_base_addr;

    /* 0xCC : h264_cref1_base_addr */
    union {
        struct {
            uint32_t h264_cref1_base_addr           : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } h264_cref1_base_addr;

    /* 0xD0 : h264_head0_base_addr */
    union {
        struct {
            uint32_t h264_head0_base_addr           : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } h264_head0_base_addr;

    /* 0xD4 : h264_head1_base_addr */
    union {
        struct {
            uint32_t h264_head1_base_addr           : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } h264_head1_base_addr;

    /* 0xD8 : cref_qp */
    union {
        struct {
            uint32_t cref_qp                        :  6; /* [ 5: 0],        r/w,        0x0 */
            uint32_t reserved_6_31                  : 26; /* [31: 6],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } cref_qp;

    /* 0xdc  reserved */
    uint8_t RESERVED0xdc[36];

    /* 0x100 : vdo_int */
    union {
        struct {
            uint32_t frm_done_int                   :  1; /* [    0],          r,        0x0 */
            uint32_t reserved_1_3                   :  3; /* [ 3: 1],       rsvd,        0x0 */
            uint32_t seq_done_int                   :  1; /* [    4],          r,        0x0 */
            uint32_t reserved_5_7                   :  3; /* [ 7: 5],       rsvd,        0x0 */
            uint32_t bs_full_int                    :  1; /* [    8],          r,        0x0 */
            uint32_t reserved_9_31                  : 23; /* [31: 9],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } vdo_int;

    /* 0x104 : vdo_int_clr */
    union {
        struct {
            uint32_t frm_done_int_clr               :  1; /* [    0],        w1p,        0x0 */
            uint32_t reserved_1_3                   :  3; /* [ 3: 1],       rsvd,        0x0 */
            uint32_t seq_done_int_clr               :  1; /* [    4],        w1p,        0x0 */
            uint32_t reserved_5_7                   :  3; /* [ 7: 5],       rsvd,        0x0 */
            uint32_t bs_full_int_clr                :  1; /* [    8],        w1p,        0x0 */
            uint32_t reserved_9_31                  : 23; /* [31: 9],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } vdo_int_clr;

    /* 0x108 : vdo_int_mask */
    union {
        struct {
            uint32_t frm_done_int_mask              :  1; /* [    0],        r/w,        0x0 */
            uint32_t reserved_1_3                   :  3; /* [ 3: 1],       rsvd,        0x0 */
            uint32_t seq_done_int_mask              :  1; /* [    4],        r/w,        0x0 */
            uint32_t reserved_5_7                   :  3; /* [ 7: 5],       rsvd,        0x0 */
            uint32_t bs_full_int_mask               :  1; /* [    8],        r/w,        0x0 */
            uint32_t reserved_9_31                  : 23; /* [31: 9],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } vdo_int_mask;

    /* 0x10C : vdo_total_bytecount */
    union {
        struct {
            uint32_t bs_tot_bycnt                   : 32; /* [31: 0],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } vdo_total_bytecount;

    /* 0x110 : vdo_frame_bytecount */
    union {
        struct {
            uint32_t bs_frm_bycnt                   : 32; /* [31: 0],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } vdo_frame_bytecount;

    /* 0x114 : vdo_src_r_dbg */
    union {
        struct {
            uint32_t y_read_mbx                     : 13; /* [12: 0],          r,        0x0 */
            uint32_t reserved_13_15                 :  3; /* [15:13],       rsvd,        0x0 */
            uint32_t uv_read_mbx                    : 13; /* [28:16],          r,        0x0 */
            uint32_t reserved_29                    :  1; /* [   29],       rsvd,        0x0 */
            uint32_t axi_r_idle                     :  1; /* [   30],          r,        0x0 */
            uint32_t src_wr_ov_rd                   :  1; /* [   31],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } vdo_src_r_dbg;

    /* 0x118 : vdo_core_dbg */
    union {
        struct {
            uint32_t core_mbx                       :  7; /* [ 6: 0],          r,        0x0 */
            uint32_t reserved_7                     :  1; /* [    7],       rsvd,        0x0 */
            uint32_t core_mby                       :  7; /* [14: 8],          r,        0x0 */
            uint32_t reserved_15                    :  1; /* [   15],       rsvd,        0x0 */
            uint32_t tclock                         : 10; /* [25:16],          r,        0x0 */
            uint32_t reserved_26                    :  1; /* [   26],       rsvd,        0x0 */
            uint32_t core_idle                      :  1; /* [   27],          r,        0x0 */
            uint32_t pframe                         :  1; /* [   28],          r,        0x0 */
            uint32_t oclk_en                        :  1; /* [   29],          r,        0x0 */
            uint32_t timeout_state                  :  1; /* [   30],          r,        0x0 */
            uint32_t mem_ctrl_idle                  :  1; /* [   31],          r,        0x1 */
        }BF;
        uint32_t WORD;
    } vdo_core_dbg;

    /* 0x11C : vdo_ctrl_dbg */
    union {
        struct {
            uint32_t ctrl_state                     :  3; /* [ 2: 0],          r,        0x0 */
            uint32_t reserved_3                     :  1; /* [    3],       rsvd,        0x0 */
            uint32_t ctrl_ce                        :  1; /* [    4],          r,        0x0 */
            uint32_t reserved_5_31                  : 27; /* [31: 5],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } vdo_ctrl_dbg;

    /* 0x120 : vdo_checksum_0 */
    union {
        struct {
            uint32_t vdo0_axi_rdata_chksum          : 32; /* [31: 0],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } vdo_checksum_0;

    /* 0x124 : vdo_checksum_1 */
    union {
        struct {
            uint32_t vdo0_axi_wdata_chksum          : 32; /* [31: 0],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } vdo_checksum_1;

    /* 0x128 : vdo_checksum_2 */
    union {
        struct {
            uint32_t vdo1_axi_rdata_chksum          : 32; /* [31: 0],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } vdo_checksum_2;

    /* 0x12C : vdo_checksum_3 */
    union {
        struct {
            uint32_t vdo1_axi_wdata_chksum          : 32; /* [31: 0],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } vdo_checksum_3;

    /* 0x130 : vdo_checksum_4 */
    union {
        struct {
            uint32_t ld_yblk_chksum                 : 32; /* [31: 0],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } vdo_checksum_4;

    /* 0x134 : vdo_checksum_5 */
    union {
        struct {
            uint32_t ld_cblk_chksum                 : 32; /* [31: 0],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } vdo_checksum_5;

    /* 0x138 : vdo_checksum_6 */
    union {
        struct {
            uint32_t mem_din_chksum                 : 32; /* [31: 0],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } vdo_checksum_6;

    /* 0x13C : vdo_checksum_7 */
    union {
        struct {
            uint32_t mem_dout_chksum                : 32; /* [31: 0],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } vdo_checksum_7;

    /* 0x140 : vdo_cref_dbg */
    union {
        struct {
            uint32_t cref_d_wait                    :  1; /* [    0],          r,        0x0 */
            uint32_t reserved_1_3                   :  3; /* [ 3: 1],       rsvd,        0x0 */
            uint32_t cref_d_frame_busy              :  1; /* [    4],          r,        0x0 */
            uint32_t reserved_5_7                   :  3; /* [ 7: 5],       rsvd,        0x0 */
            uint32_t cref_d_done                    :  1; /* [    8],          r,        0x0 */
            uint32_t reserved_9_15                  :  7; /* [15: 9],       rsvd,        0x0 */
            uint32_t cref_e_wait                    :  1; /* [   16],          r,        0x0 */
            uint32_t reserved_17_23                 :  7; /* [23:17],       rsvd,        0x0 */
            uint32_t cref_e_frame_busy              :  1; /* [   24],          r,        0x0 */
            uint32_t reserved_25_27                 :  3; /* [27:25],       rsvd,        0x0 */
            uint32_t cref_e_done                    :  1; /* [   28],          r,        0x0 */
            uint32_t reserved_29_31                 :  3; /* [31:29],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } vdo_cref_dbg;

};

typedef volatile struct vdo_reg vdo_reg_t;


#endif  /* __VDO_REG_H__ */
