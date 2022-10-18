/**
  ******************************************************************************
  * @file    vdo_reg.h
  * @version V1.2
  * @date    2020-10-09
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
#ifndef __VDO_REG_H__
#define __VDO_REG_H__
#include "bl808.h"

/* 0x0 : vdo_h264_encoder_ctrl */
#define VDO_H264_ENCODER_CTRL_OFFSET                            (0x0)
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
#define VDO_CFG_ZSTUF_DIS                                       VDO_CFG_ZSTUF_DIS
#define VDO_CFG_ZSTUF_DIS_POS                                   (9U)
#define VDO_CFG_ZSTUF_DIS_LEN                                   (1U)
#define VDO_CFG_ZSTUF_DIS_MSK                                   (((1U<<VDO_CFG_ZSTUF_DIS_LEN)-1)<<VDO_CFG_ZSTUF_DIS_POS)
#define VDO_CFG_ZSTUF_DIS_UMSK                                  (~(((1U<<VDO_CFG_ZSTUF_DIS_LEN)-1)<<VDO_CFG_ZSTUF_DIS_POS))
#define VDO_CFG_QR_UPD                                          VDO_CFG_QR_UPD
#define VDO_CFG_QR_UPD_POS                                      (10U)
#define VDO_CFG_QR_UPD_LEN                                      (1U)
#define VDO_CFG_QR_UPD_MSK                                      (((1U<<VDO_CFG_QR_UPD_LEN)-1)<<VDO_CFG_QR_UPD_POS)
#define VDO_CFG_QR_UPD_UMSK                                     (~(((1U<<VDO_CFG_QR_UPD_LEN)-1)<<VDO_CFG_QR_UPD_POS))
#define VDO_CFG_S_QR_UPD                                        VDO_CFG_S_QR_UPD
#define VDO_CFG_S_QR_UPD_POS                                    (11U)
#define VDO_CFG_S_QR_UPD_LEN                                    (1U)
#define VDO_CFG_S_QR_UPD_MSK                                    (((1U<<VDO_CFG_S_QR_UPD_LEN)-1)<<VDO_CFG_S_QR_UPD_POS)
#define VDO_CFG_S_QR_UPD_UMSK                                   (~(((1U<<VDO_CFG_S_QR_UPD_LEN)-1)<<VDO_CFG_S_QR_UPD_POS))
#define VDO_CFG_MEM_CLK_EN                                      VDO_CFG_MEM_CLK_EN
#define VDO_CFG_MEM_CLK_EN_POS                                  (12U)
#define VDO_CFG_MEM_CLK_EN_LEN                                  (1U)
#define VDO_CFG_MEM_CLK_EN_MSK                                  (((1U<<VDO_CFG_MEM_CLK_EN_LEN)-1)<<VDO_CFG_MEM_CLK_EN_POS)
#define VDO_CFG_MEM_CLK_EN_UMSK                                 (~(((1U<<VDO_CFG_MEM_CLK_EN_LEN)-1)<<VDO_CFG_MEM_CLK_EN_POS))
#define VDO_CFG_RC_GOP_UPD                                      VDO_CFG_RC_GOP_UPD
#define VDO_CFG_RC_GOP_UPD_POS                                  (13U)
#define VDO_CFG_RC_GOP_UPD_LEN                                  (1U)
#define VDO_CFG_RC_GOP_UPD_MSK                                  (((1U<<VDO_CFG_RC_GOP_UPD_LEN)-1)<<VDO_CFG_RC_GOP_UPD_POS)
#define VDO_CFG_RC_GOP_UPD_UMSK                                 (~(((1U<<VDO_CFG_RC_GOP_UPD_LEN)-1)<<VDO_CFG_RC_GOP_UPD_POS))
#define VDO_CFG_S_RC_GOP_UPD                                    VDO_CFG_S_RC_GOP_UPD
#define VDO_CFG_S_RC_GOP_UPD_POS                                (14U)
#define VDO_CFG_S_RC_GOP_UPD_LEN                                (1U)
#define VDO_CFG_S_RC_GOP_UPD_MSK                                (((1U<<VDO_CFG_S_RC_GOP_UPD_LEN)-1)<<VDO_CFG_S_RC_GOP_UPD_POS)
#define VDO_CFG_S_RC_GOP_UPD_UMSK                               (~(((1U<<VDO_CFG_S_RC_GOP_UPD_LEN)-1)<<VDO_CFG_S_RC_GOP_UPD_POS))
#define VDO_CFG_DUO_BS_EN                                       VDO_CFG_DUO_BS_EN
#define VDO_CFG_DUO_BS_EN_POS                                   (15U)
#define VDO_CFG_DUO_BS_EN_LEN                                   (1U)
#define VDO_CFG_DUO_BS_EN_MSK                                   (((1U<<VDO_CFG_DUO_BS_EN_LEN)-1)<<VDO_CFG_DUO_BS_EN_POS)
#define VDO_CFG_DUO_BS_EN_UMSK                                  (~(((1U<<VDO_CFG_DUO_BS_EN_LEN)-1)<<VDO_CFG_DUO_BS_EN_POS))
#define VDO_CFG_BUF_CLR                                         VDO_CFG_BUF_CLR
#define VDO_CFG_BUF_CLR_POS                                     (16U)
#define VDO_CFG_BUF_CLR_LEN                                     (1U)
#define VDO_CFG_BUF_CLR_MSK                                     (((1U<<VDO_CFG_BUF_CLR_LEN)-1)<<VDO_CFG_BUF_CLR_POS)
#define VDO_CFG_BUF_CLR_UMSK                                    (~(((1U<<VDO_CFG_BUF_CLR_LEN)-1)<<VDO_CFG_BUF_CLR_POS))
#define VDO_CFG_S_BUF_CLR                                       VDO_CFG_S_BUF_CLR
#define VDO_CFG_S_BUF_CLR_POS                                   (17U)
#define VDO_CFG_S_BUF_CLR_LEN                                   (1U)
#define VDO_CFG_S_BUF_CLR_MSK                                   (((1U<<VDO_CFG_S_BUF_CLR_LEN)-1)<<VDO_CFG_S_BUF_CLR_POS)
#define VDO_CFG_S_BUF_CLR_UMSK                                  (~(((1U<<VDO_CFG_S_BUF_CLR_LEN)-1)<<VDO_CFG_S_BUF_CLR_POS))
#define VDO_CFG_VDONR_EN                                        VDO_CFG_VDONR_EN
#define VDO_CFG_VDONR_EN_POS                                    (18U)
#define VDO_CFG_VDONR_EN_LEN                                    (1U)
#define VDO_CFG_VDONR_EN_MSK                                    (((1U<<VDO_CFG_VDONR_EN_LEN)-1)<<VDO_CFG_VDONR_EN_POS)
#define VDO_CFG_VDONR_EN_UMSK                                   (~(((1U<<VDO_CFG_VDONR_EN_LEN)-1)<<VDO_CFG_VDONR_EN_POS))
#define VDO_CFG_S_VDONR_EN                                      VDO_CFG_S_VDONR_EN
#define VDO_CFG_S_VDONR_EN_POS                                  (19U)
#define VDO_CFG_S_VDONR_EN_LEN                                  (1U)
#define VDO_CFG_S_VDONR_EN_MSK                                  (((1U<<VDO_CFG_S_VDONR_EN_LEN)-1)<<VDO_CFG_S_VDONR_EN_POS)
#define VDO_CFG_S_VDONR_EN_UMSK                                 (~(((1U<<VDO_CFG_S_VDONR_EN_LEN)-1)<<VDO_CFG_S_VDONR_EN_POS))
#define VDO_CFG_BS_STATUS_INIT                                  VDO_CFG_BS_STATUS_INIT
#define VDO_CFG_BS_STATUS_INIT_POS                              (20U)
#define VDO_CFG_BS_STATUS_INIT_LEN                              (1U)
#define VDO_CFG_BS_STATUS_INIT_MSK                              (((1U<<VDO_CFG_BS_STATUS_INIT_LEN)-1)<<VDO_CFG_BS_STATUS_INIT_POS)
#define VDO_CFG_BS_STATUS_INIT_UMSK                             (~(((1U<<VDO_CFG_BS_STATUS_INIT_LEN)-1)<<VDO_CFG_BS_STATUS_INIT_POS))
#define VDO_CFG_S_BS_STATUS_INIT                                VDO_CFG_S_BS_STATUS_INIT
#define VDO_CFG_S_BS_STATUS_INIT_POS                            (21U)
#define VDO_CFG_S_BS_STATUS_INIT_LEN                            (1U)
#define VDO_CFG_S_BS_STATUS_INIT_MSK                            (((1U<<VDO_CFG_S_BS_STATUS_INIT_LEN)-1)<<VDO_CFG_S_BS_STATUS_INIT_POS)
#define VDO_CFG_S_BS_STATUS_INIT_UMSK                           (~(((1U<<VDO_CFG_S_BS_STATUS_INIT_LEN)-1)<<VDO_CFG_S_BS_STATUS_INIT_POS))
#define VDO_CFG_SRC_LINE_CLR                                    VDO_CFG_SRC_LINE_CLR
#define VDO_CFG_SRC_LINE_CLR_POS                                (22U)
#define VDO_CFG_SRC_LINE_CLR_LEN                                (1U)
#define VDO_CFG_SRC_LINE_CLR_MSK                                (((1U<<VDO_CFG_SRC_LINE_CLR_LEN)-1)<<VDO_CFG_SRC_LINE_CLR_POS)
#define VDO_CFG_SRC_LINE_CLR_UMSK                               (~(((1U<<VDO_CFG_SRC_LINE_CLR_LEN)-1)<<VDO_CFG_SRC_LINE_CLR_POS))
#define VDO_CFG_S_SRC_LINE_CLR                                  VDO_CFG_S_SRC_LINE_CLR
#define VDO_CFG_S_SRC_LINE_CLR_POS                              (23U)
#define VDO_CFG_S_SRC_LINE_CLR_LEN                              (1U)
#define VDO_CFG_S_SRC_LINE_CLR_MSK                              (((1U<<VDO_CFG_S_SRC_LINE_CLR_LEN)-1)<<VDO_CFG_S_SRC_LINE_CLR_POS)
#define VDO_CFG_S_SRC_LINE_CLR_UMSK                             (~(((1U<<VDO_CFG_S_SRC_LINE_CLR_LEN)-1)<<VDO_CFG_S_SRC_LINE_CLR_POS))
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
#define VDO_CFG_S_CREF_EN                                       VDO_CFG_S_CREF_EN
#define VDO_CFG_S_CREF_EN_POS                                   (27U)
#define VDO_CFG_S_CREF_EN_LEN                                   (1U)
#define VDO_CFG_S_CREF_EN_MSK                                   (((1U<<VDO_CFG_S_CREF_EN_LEN)-1)<<VDO_CFG_S_CREF_EN_POS)
#define VDO_CFG_S_CREF_EN_UMSK                                  (~(((1U<<VDO_CFG_S_CREF_EN_LEN)-1)<<VDO_CFG_S_CREF_EN_POS))
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
#define VDO_CFG_S_FRAME_START                                   VDO_CFG_S_FRAME_START
#define VDO_CFG_S_FRAME_START_POS                               (30U)
#define VDO_CFG_S_FRAME_START_LEN                               (1U)
#define VDO_CFG_S_FRAME_START_MSK                               (((1U<<VDO_CFG_S_FRAME_START_LEN)-1)<<VDO_CFG_S_FRAME_START_POS)
#define VDO_CFG_S_FRAME_START_UMSK                              (~(((1U<<VDO_CFG_S_FRAME_START_LEN)-1)<<VDO_CFG_S_FRAME_START_POS))
#define VDO_CFG_S_ENC_SEQ_EN                                    VDO_CFG_S_ENC_SEQ_EN
#define VDO_CFG_S_ENC_SEQ_EN_POS                                (31U)
#define VDO_CFG_S_ENC_SEQ_EN_LEN                                (1U)
#define VDO_CFG_S_ENC_SEQ_EN_MSK                                (((1U<<VDO_CFG_S_ENC_SEQ_EN_LEN)-1)<<VDO_CFG_S_ENC_SEQ_EN_POS)
#define VDO_CFG_S_ENC_SEQ_EN_UMSK                               (~(((1U<<VDO_CFG_S_ENC_SEQ_EN_LEN)-1)<<VDO_CFG_S_ENC_SEQ_EN_POS))

/* 0x4 : vdo_h264_frame_size */
#define VDO_H264_FRAME_SIZE_OFFSET                              (0x4)
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

/* 0x8 : vdo_h264_frame_base_addr_y */
#define VDO_H264_FRAME_BASE_ADDR_Y_OFFSET                       (0x8)
#define VDO_CFG_FRAME_BASE_ADDR_Y                               VDO_CFG_FRAME_BASE_ADDR_Y
#define VDO_CFG_FRAME_BASE_ADDR_Y_POS                           (0U)
#define VDO_CFG_FRAME_BASE_ADDR_Y_LEN                           (32U)
#define VDO_CFG_FRAME_BASE_ADDR_Y_MSK                           (((1U<<VDO_CFG_FRAME_BASE_ADDR_Y_LEN)-1)<<VDO_CFG_FRAME_BASE_ADDR_Y_POS)
#define VDO_CFG_FRAME_BASE_ADDR_Y_UMSK                          (~(((1U<<VDO_CFG_FRAME_BASE_ADDR_Y_LEN)-1)<<VDO_CFG_FRAME_BASE_ADDR_Y_POS))

/* 0xc : vdo_h264_frame_base_addr_uv */
#define VDO_H264_FRAME_BASE_ADDR_UV_OFFSET                      (0xc)
#define VDO_CFG_FRAME_BASE_ADDR_UV                              VDO_CFG_FRAME_BASE_ADDR_UV
#define VDO_CFG_FRAME_BASE_ADDR_UV_POS                          (0U)
#define VDO_CFG_FRAME_BASE_ADDR_UV_LEN                          (32U)
#define VDO_CFG_FRAME_BASE_ADDR_UV_MSK                          (((1U<<VDO_CFG_FRAME_BASE_ADDR_UV_LEN)-1)<<VDO_CFG_FRAME_BASE_ADDR_UV_POS)
#define VDO_CFG_FRAME_BASE_ADDR_UV_UMSK                         (~(((1U<<VDO_CFG_FRAME_BASE_ADDR_UV_LEN)-1)<<VDO_CFG_FRAME_BASE_ADDR_UV_POS))

/* 0x10 : vdo_h264_bs_base_addr */
#define VDO_H264_BS_BASE_ADDR_OFFSET                            (0x10)
#define VDO_CFG_BS_BASE_ADDR                                    VDO_CFG_BS_BASE_ADDR
#define VDO_CFG_BS_BASE_ADDR_POS                                (0U)
#define VDO_CFG_BS_BASE_ADDR_LEN                                (32U)
#define VDO_CFG_BS_BASE_ADDR_MSK                                (((1U<<VDO_CFG_BS_BASE_ADDR_LEN)-1)<<VDO_CFG_BS_BASE_ADDR_POS)
#define VDO_CFG_BS_BASE_ADDR_UMSK                               (~(((1U<<VDO_CFG_BS_BASE_ADDR_LEN)-1)<<VDO_CFG_BS_BASE_ADDR_POS))

/* 0x14 : vdo_h264_lb_base_addr */
#define VDO_H264_LB_BASE_ADDR_OFFSET                            (0x14)
#define VDO_CFG_LB_BASE_ADDR                                    VDO_CFG_LB_BASE_ADDR
#define VDO_CFG_LB_BASE_ADDR_POS                                (0U)
#define VDO_CFG_LB_BASE_ADDR_LEN                                (32U)
#define VDO_CFG_LB_BASE_ADDR_MSK                                (((1U<<VDO_CFG_LB_BASE_ADDR_LEN)-1)<<VDO_CFG_LB_BASE_ADDR_POS)
#define VDO_CFG_LB_BASE_ADDR_UMSK                               (~(((1U<<VDO_CFG_LB_BASE_ADDR_LEN)-1)<<VDO_CFG_LB_BASE_ADDR_POS))

/* 0x18 : vdo_h264_bs_size */
#define VDO_H264_BS_SIZE_OFFSET                                 (0x18)
#define VDO_CFG_BS_SIZE                                         VDO_CFG_BS_SIZE
#define VDO_CFG_BS_SIZE_POS                                     (0U)
#define VDO_CFG_BS_SIZE_LEN                                     (32U)
#define VDO_CFG_BS_SIZE_MSK                                     (((1U<<VDO_CFG_BS_SIZE_LEN)-1)<<VDO_CFG_BS_SIZE_POS)
#define VDO_CFG_BS_SIZE_UMSK                                    (~(((1U<<VDO_CFG_BS_SIZE_LEN)-1)<<VDO_CFG_BS_SIZE_POS))

/* 0x1c : vdo_h264_bs_full_thr */
#define VDO_H264_BS_FULL_THR_OFFSET                             (0x1c)
#define VDO_CFG_BS_FULL_THR                                     VDO_CFG_BS_FULL_THR
#define VDO_CFG_BS_FULL_THR_POS                                 (0U)
#define VDO_CFG_BS_FULL_THR_LEN                                 (32U)
#define VDO_CFG_BS_FULL_THR_MSK                                 (((1U<<VDO_CFG_BS_FULL_THR_LEN)-1)<<VDO_CFG_BS_FULL_THR_POS)
#define VDO_CFG_BS_FULL_THR_UMSK                                (~(((1U<<VDO_CFG_BS_FULL_THR_LEN)-1)<<VDO_CFG_BS_FULL_THR_POS))

/* 0x20 : vdo_h264_src_bf_height */
#define VDO_H264_SRC_BF_HEIGHT_OFFSET                           (0x20)
#define VDO_CFG_C_SRC_BF_HEIGHT                                 VDO_CFG_C_SRC_BF_HEIGHT
#define VDO_CFG_C_SRC_BF_HEIGHT_POS                             (0U)
#define VDO_CFG_C_SRC_BF_HEIGHT_LEN                             (15U)
#define VDO_CFG_C_SRC_BF_HEIGHT_MSK                             (((1U<<VDO_CFG_C_SRC_BF_HEIGHT_LEN)-1)<<VDO_CFG_C_SRC_BF_HEIGHT_POS)
#define VDO_CFG_C_SRC_BF_HEIGHT_UMSK                            (~(((1U<<VDO_CFG_C_SRC_BF_HEIGHT_LEN)-1)<<VDO_CFG_C_SRC_BF_HEIGHT_POS))
#define VDO_CFG_Y_SRC_BF_HEIGHT                                 VDO_CFG_Y_SRC_BF_HEIGHT
#define VDO_CFG_Y_SRC_BF_HEIGHT_POS                             (16U)
#define VDO_CFG_Y_SRC_BF_HEIGHT_LEN                             (15U)
#define VDO_CFG_Y_SRC_BF_HEIGHT_MSK                             (((1U<<VDO_CFG_Y_SRC_BF_HEIGHT_LEN)-1)<<VDO_CFG_Y_SRC_BF_HEIGHT_POS)
#define VDO_CFG_Y_SRC_BF_HEIGHT_UMSK                            (~(((1U<<VDO_CFG_Y_SRC_BF_HEIGHT_LEN)-1)<<VDO_CFG_Y_SRC_BF_HEIGHT_POS))

/* 0x24 : vdo_core_reg0 */
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
#define VDO_S_ENC_EN                                            VDO_S_ENC_EN
#define VDO_S_ENC_EN_POS                                        (16U)
#define VDO_S_ENC_EN_LEN                                        (1U)
#define VDO_S_ENC_EN_MSK                                        (((1U<<VDO_S_ENC_EN_LEN)-1)<<VDO_S_ENC_EN_POS)
#define VDO_S_ENC_EN_UMSK                                       (~(((1U<<VDO_S_ENC_EN_LEN)-1)<<VDO_S_ENC_EN_POS))
#define VDO_S_VUI_ASPECT_INFO                                   VDO_S_VUI_ASPECT_INFO
#define VDO_S_VUI_ASPECT_INFO_POS                               (28U)
#define VDO_S_VUI_ASPECT_INFO_LEN                               (1U)
#define VDO_S_VUI_ASPECT_INFO_MSK                               (((1U<<VDO_S_VUI_ASPECT_INFO_LEN)-1)<<VDO_S_VUI_ASPECT_INFO_POS)
#define VDO_S_VUI_ASPECT_INFO_UMSK                              (~(((1U<<VDO_S_VUI_ASPECT_INFO_LEN)-1)<<VDO_S_VUI_ASPECT_INFO_POS))
#define VDO_S_VUI_FIXED_F_RATE                                  VDO_S_VUI_FIXED_F_RATE
#define VDO_S_VUI_FIXED_F_RATE_POS                              (29U)
#define VDO_S_VUI_FIXED_F_RATE_LEN                              (1U)
#define VDO_S_VUI_FIXED_F_RATE_MSK                              (((1U<<VDO_S_VUI_FIXED_F_RATE_LEN)-1)<<VDO_S_VUI_FIXED_F_RATE_POS)
#define VDO_S_VUI_FIXED_F_RATE_UMSK                             (~(((1U<<VDO_S_VUI_FIXED_F_RATE_LEN)-1)<<VDO_S_VUI_FIXED_F_RATE_POS))
#define VDO_S_VUI_TIMING_INFO                                   VDO_S_VUI_TIMING_INFO
#define VDO_S_VUI_TIMING_INFO_POS                               (30U)
#define VDO_S_VUI_TIMING_INFO_LEN                               (1U)
#define VDO_S_VUI_TIMING_INFO_MSK                               (((1U<<VDO_S_VUI_TIMING_INFO_LEN)-1)<<VDO_S_VUI_TIMING_INFO_POS)
#define VDO_S_VUI_TIMING_INFO_UMSK                              (~(((1U<<VDO_S_VUI_TIMING_INFO_LEN)-1)<<VDO_S_VUI_TIMING_INFO_POS))
#define VDO_S_IDR_ENABLE                                        VDO_S_IDR_ENABLE
#define VDO_S_IDR_ENABLE_POS                                    (31U)
#define VDO_S_IDR_ENABLE_LEN                                    (1U)
#define VDO_S_IDR_ENABLE_MSK                                    (((1U<<VDO_S_IDR_ENABLE_LEN)-1)<<VDO_S_IDR_ENABLE_POS)
#define VDO_S_IDR_ENABLE_UMSK                                   (~(((1U<<VDO_S_IDR_ENABLE_LEN)-1)<<VDO_S_IDR_ENABLE_POS))

/* 0x28 : vdo_core_reg1 */
#define VDO_CORE_REG1_OFFSET                                    (0x28)
#define VDO_IMG_WIDTH                                           VDO_IMG_WIDTH
#define VDO_IMG_WIDTH_POS                                       (0U)
#define VDO_IMG_WIDTH_LEN                                       (11U)
#define VDO_IMG_WIDTH_MSK                                       (((1U<<VDO_IMG_WIDTH_LEN)-1)<<VDO_IMG_WIDTH_POS)
#define VDO_IMG_WIDTH_UMSK                                      (~(((1U<<VDO_IMG_WIDTH_LEN)-1)<<VDO_IMG_WIDTH_POS))
#define VDO_S_IMG_WIDTH                                         VDO_S_IMG_WIDTH
#define VDO_S_IMG_WIDTH_POS                                     (16U)
#define VDO_S_IMG_WIDTH_LEN                                     (11U)
#define VDO_S_IMG_WIDTH_MSK                                     (((1U<<VDO_S_IMG_WIDTH_LEN)-1)<<VDO_S_IMG_WIDTH_POS)
#define VDO_S_IMG_WIDTH_UMSK                                    (~(((1U<<VDO_S_IMG_WIDTH_LEN)-1)<<VDO_S_IMG_WIDTH_POS))

/* 0x2c : vdo_core_reg2 */
#define VDO_CORE_REG2_OFFSET                                    (0x2c)
#define VDO_IMG_HEIGHT                                          VDO_IMG_HEIGHT
#define VDO_IMG_HEIGHT_POS                                      (0U)
#define VDO_IMG_HEIGHT_LEN                                      (11U)
#define VDO_IMG_HEIGHT_MSK                                      (((1U<<VDO_IMG_HEIGHT_LEN)-1)<<VDO_IMG_HEIGHT_POS)
#define VDO_IMG_HEIGHT_UMSK                                     (~(((1U<<VDO_IMG_HEIGHT_LEN)-1)<<VDO_IMG_HEIGHT_POS))
#define VDO_S_IMG_HEIGHT                                        VDO_S_IMG_HEIGHT
#define VDO_S_IMG_HEIGHT_POS                                    (16U)
#define VDO_S_IMG_HEIGHT_LEN                                    (11U)
#define VDO_S_IMG_HEIGHT_MSK                                    (((1U<<VDO_S_IMG_HEIGHT_LEN)-1)<<VDO_S_IMG_HEIGHT_POS)
#define VDO_S_IMG_HEIGHT_UMSK                                   (~(((1U<<VDO_S_IMG_HEIGHT_LEN)-1)<<VDO_S_IMG_HEIGHT_POS))

/* 0x30 : vdo_core_reg3 */
#define VDO_CORE_REG3_OFFSET                                    (0x30)
#define VDO_TARGET_I_QP                                         VDO_TARGET_I_QP
#define VDO_TARGET_I_QP_POS                                     (0U)
#define VDO_TARGET_I_QP_LEN                                     (6U)
#define VDO_TARGET_I_QP_MSK                                     (((1U<<VDO_TARGET_I_QP_LEN)-1)<<VDO_TARGET_I_QP_POS)
#define VDO_TARGET_I_QP_UMSK                                    (~(((1U<<VDO_TARGET_I_QP_LEN)-1)<<VDO_TARGET_I_QP_POS))
#define VDO_S_TARGET_I_QP                                       VDO_S_TARGET_I_QP
#define VDO_S_TARGET_I_QP_POS                                   (16U)
#define VDO_S_TARGET_I_QP_LEN                                   (6U)
#define VDO_S_TARGET_I_QP_MSK                                   (((1U<<VDO_S_TARGET_I_QP_LEN)-1)<<VDO_S_TARGET_I_QP_POS)
#define VDO_S_TARGET_I_QP_UMSK                                  (~(((1U<<VDO_S_TARGET_I_QP_LEN)-1)<<VDO_S_TARGET_I_QP_POS))

/* 0x34 : vdo_core_reg4 */
#define VDO_CORE_REG4_OFFSET                                    (0x34)
#define VDO_CQP_OFFSET                                          VDO_CQP_OFFSET
#define VDO_CQP_OFFSET_POS                                      (0U)
#define VDO_CQP_OFFSET_LEN                                      (5U)
#define VDO_CQP_OFFSET_MSK                                      (((1U<<VDO_CQP_OFFSET_LEN)-1)<<VDO_CQP_OFFSET_POS)
#define VDO_CQP_OFFSET_UMSK                                     (~(((1U<<VDO_CQP_OFFSET_LEN)-1)<<VDO_CQP_OFFSET_POS))
#define VDO_S_CQP_OFFSET                                        VDO_S_CQP_OFFSET
#define VDO_S_CQP_OFFSET_POS                                    (16U)
#define VDO_S_CQP_OFFSET_LEN                                    (5U)
#define VDO_S_CQP_OFFSET_MSK                                    (((1U<<VDO_S_CQP_OFFSET_LEN)-1)<<VDO_S_CQP_OFFSET_POS)
#define VDO_S_CQP_OFFSET_UMSK                                   (~(((1U<<VDO_S_CQP_OFFSET_LEN)-1)<<VDO_S_CQP_OFFSET_POS))

/* 0x38 : vdo_core_reg5 */
#define VDO_CORE_REG5_OFFSET                                    (0x38)
#define VDO_TARGET_P_QP                                         VDO_TARGET_P_QP
#define VDO_TARGET_P_QP_POS                                     (0U)
#define VDO_TARGET_P_QP_LEN                                     (6U)
#define VDO_TARGET_P_QP_MSK                                     (((1U<<VDO_TARGET_P_QP_LEN)-1)<<VDO_TARGET_P_QP_POS)
#define VDO_TARGET_P_QP_UMSK                                    (~(((1U<<VDO_TARGET_P_QP_LEN)-1)<<VDO_TARGET_P_QP_POS))
#define VDO_S_TARGET_P_QP                                       VDO_S_TARGET_P_QP
#define VDO_S_TARGET_P_QP_POS                                   (16U)
#define VDO_S_TARGET_P_QP_LEN                                   (6U)
#define VDO_S_TARGET_P_QP_MSK                                   (((1U<<VDO_S_TARGET_P_QP_LEN)-1)<<VDO_S_TARGET_P_QP_POS)
#define VDO_S_TARGET_P_QP_UMSK                                  (~(((1U<<VDO_S_TARGET_P_QP_LEN)-1)<<VDO_S_TARGET_P_QP_POS))

/* 0x3c : vdo_core_reg6 */
#define VDO_CORE_REG6_OFFSET                                    (0x3c)
#define VDO_MB_LINES                                            VDO_MB_LINES
#define VDO_MB_LINES_POS                                        (0U)
#define VDO_MB_LINES_LEN                                        (7U)
#define VDO_MB_LINES_MSK                                        (((1U<<VDO_MB_LINES_LEN)-1)<<VDO_MB_LINES_POS)
#define VDO_MB_LINES_UMSK                                       (~(((1U<<VDO_MB_LINES_LEN)-1)<<VDO_MB_LINES_POS))
#define VDO_S_MB_LINES                                          VDO_S_MB_LINES
#define VDO_S_MB_LINES_POS                                      (16U)
#define VDO_S_MB_LINES_LEN                                      (7U)
#define VDO_S_MB_LINES_MSK                                      (((1U<<VDO_S_MB_LINES_LEN)-1)<<VDO_S_MB_LINES_POS)
#define VDO_S_MB_LINES_UMSK                                     (~(((1U<<VDO_S_MB_LINES_LEN)-1)<<VDO_S_MB_LINES_POS))

/* 0x40 : vdo_core_reg7 */
#define VDO_CORE_REG7_OFFSET                                    (0x40)
#define VDO_NUM_SLICES                                          VDO_NUM_SLICES
#define VDO_NUM_SLICES_POS                                      (0U)
#define VDO_NUM_SLICES_LEN                                      (4U)
#define VDO_NUM_SLICES_MSK                                      (((1U<<VDO_NUM_SLICES_LEN)-1)<<VDO_NUM_SLICES_POS)
#define VDO_NUM_SLICES_UMSK                                     (~(((1U<<VDO_NUM_SLICES_LEN)-1)<<VDO_NUM_SLICES_POS))
#define VDO_S_NUM_SLICES                                        VDO_S_NUM_SLICES
#define VDO_S_NUM_SLICES_POS                                    (16U)
#define VDO_S_NUM_SLICES_LEN                                    (4U)
#define VDO_S_NUM_SLICES_MSK                                    (((1U<<VDO_S_NUM_SLICES_LEN)-1)<<VDO_S_NUM_SLICES_POS)
#define VDO_S_NUM_SLICES_UMSK                                   (~(((1U<<VDO_S_NUM_SLICES_LEN)-1)<<VDO_S_NUM_SLICES_POS))

/* 0x44 : vdo_core_reg8 */
#define VDO_CORE_REG8_OFFSET                                    (0x44)
#define VDO_NUM_PFRAMES                                         VDO_NUM_PFRAMES
#define VDO_NUM_PFRAMES_POS                                     (0U)
#define VDO_NUM_PFRAMES_LEN                                     (10U)
#define VDO_NUM_PFRAMES_MSK                                     (((1U<<VDO_NUM_PFRAMES_LEN)-1)<<VDO_NUM_PFRAMES_POS)
#define VDO_NUM_PFRAMES_UMSK                                    (~(((1U<<VDO_NUM_PFRAMES_LEN)-1)<<VDO_NUM_PFRAMES_POS))
#define VDO_S_NUM_PFRAMES                                       VDO_S_NUM_PFRAMES
#define VDO_S_NUM_PFRAMES_POS                                   (16U)
#define VDO_S_NUM_PFRAMES_LEN                                   (10U)
#define VDO_S_NUM_PFRAMES_MSK                                   (((1U<<VDO_S_NUM_PFRAMES_LEN)-1)<<VDO_S_NUM_PFRAMES_POS)
#define VDO_S_NUM_PFRAMES_UMSK                                  (~(((1U<<VDO_S_NUM_PFRAMES_LEN)-1)<<VDO_S_NUM_PFRAMES_POS))

/* 0x48 : vdo_core_reg9 */
#define VDO_CORE_REG9_OFFSET                                    (0x48)
#define VDO_DIS_FILTER                                          VDO_DIS_FILTER
#define VDO_DIS_FILTER_POS                                      (0U)
#define VDO_DIS_FILTER_LEN                                      (1U)
#define VDO_DIS_FILTER_MSK                                      (((1U<<VDO_DIS_FILTER_LEN)-1)<<VDO_DIS_FILTER_POS)
#define VDO_DIS_FILTER_UMSK                                     (~(((1U<<VDO_DIS_FILTER_LEN)-1)<<VDO_DIS_FILTER_POS))
#define VDO_S_DIS_FILTER                                        VDO_S_DIS_FILTER
#define VDO_S_DIS_FILTER_POS                                    (16U)
#define VDO_S_DIS_FILTER_LEN                                    (1U)
#define VDO_S_DIS_FILTER_MSK                                    (((1U<<VDO_S_DIS_FILTER_LEN)-1)<<VDO_S_DIS_FILTER_POS)
#define VDO_S_DIS_FILTER_UMSK                                   (~(((1U<<VDO_S_DIS_FILTER_LEN)-1)<<VDO_S_DIS_FILTER_POS))

/* 0x4c : vdo_core_reg10 */
#define VDO_CORE_REG10_OFFSET                                   (0x4c)
#define VDO_ALPHA_OFF                                           VDO_ALPHA_OFF
#define VDO_ALPHA_OFF_POS                                       (0U)
#define VDO_ALPHA_OFF_LEN                                       (4U)
#define VDO_ALPHA_OFF_MSK                                       (((1U<<VDO_ALPHA_OFF_LEN)-1)<<VDO_ALPHA_OFF_POS)
#define VDO_ALPHA_OFF_UMSK                                      (~(((1U<<VDO_ALPHA_OFF_LEN)-1)<<VDO_ALPHA_OFF_POS))
#define VDO_S_ALPHA_OFF                                         VDO_S_ALPHA_OFF
#define VDO_S_ALPHA_OFF_POS                                     (16U)
#define VDO_S_ALPHA_OFF_LEN                                     (4U)
#define VDO_S_ALPHA_OFF_MSK                                     (((1U<<VDO_S_ALPHA_OFF_LEN)-1)<<VDO_S_ALPHA_OFF_POS)
#define VDO_S_ALPHA_OFF_UMSK                                    (~(((1U<<VDO_S_ALPHA_OFF_LEN)-1)<<VDO_S_ALPHA_OFF_POS))

/* 0x50 : vdo_core_reg11 */
#define VDO_CORE_REG11_OFFSET                                   (0x50)
#define VDO_BETA_OFF                                            VDO_BETA_OFF
#define VDO_BETA_OFF_POS                                        (0U)
#define VDO_BETA_OFF_LEN                                        (4U)
#define VDO_BETA_OFF_MSK                                        (((1U<<VDO_BETA_OFF_LEN)-1)<<VDO_BETA_OFF_POS)
#define VDO_BETA_OFF_UMSK                                       (~(((1U<<VDO_BETA_OFF_LEN)-1)<<VDO_BETA_OFF_POS))
#define VDO_S_BETA_OFF                                          VDO_S_BETA_OFF
#define VDO_S_BETA_OFF_POS                                      (16U)
#define VDO_S_BETA_OFF_LEN                                      (4U)
#define VDO_S_BETA_OFF_MSK                                      (((1U<<VDO_S_BETA_OFF_LEN)-1)<<VDO_S_BETA_OFF_POS)
#define VDO_S_BETA_OFF_UMSK                                     (~(((1U<<VDO_S_BETA_OFF_LEN)-1)<<VDO_S_BETA_OFF_POS))

/* 0x54 : vdo_core_reg12 */
#define VDO_CORE_REG12_OFFSET                                   (0x54)
#define VDO_PROFILE_IDC                                         VDO_PROFILE_IDC
#define VDO_PROFILE_IDC_POS                                     (0U)
#define VDO_PROFILE_IDC_LEN                                     (1U)
#define VDO_PROFILE_IDC_MSK                                     (((1U<<VDO_PROFILE_IDC_LEN)-1)<<VDO_PROFILE_IDC_POS)
#define VDO_PROFILE_IDC_UMSK                                    (~(((1U<<VDO_PROFILE_IDC_LEN)-1)<<VDO_PROFILE_IDC_POS))
#define VDO_S_PROFILE_IDC                                       VDO_S_PROFILE_IDC
#define VDO_S_PROFILE_IDC_POS                                   (16U)
#define VDO_S_PROFILE_IDC_LEN                                   (1U)
#define VDO_S_PROFILE_IDC_MSK                                   (((1U<<VDO_S_PROFILE_IDC_LEN)-1)<<VDO_S_PROFILE_IDC_POS)
#define VDO_S_PROFILE_IDC_UMSK                                  (~(((1U<<VDO_S_PROFILE_IDC_LEN)-1)<<VDO_S_PROFILE_IDC_POS))

/* 0x58 : vdo_core_reg13 */
#define VDO_CORE_REG13_OFFSET                                   (0x58)
#define VDO_LEVEL_IDC                                           VDO_LEVEL_IDC
#define VDO_LEVEL_IDC_POS                                       (0U)
#define VDO_LEVEL_IDC_LEN                                       (8U)
#define VDO_LEVEL_IDC_MSK                                       (((1U<<VDO_LEVEL_IDC_LEN)-1)<<VDO_LEVEL_IDC_POS)
#define VDO_LEVEL_IDC_UMSK                                      (~(((1U<<VDO_LEVEL_IDC_LEN)-1)<<VDO_LEVEL_IDC_POS))
#define VDO_S_LEVEL_IDC                                         VDO_S_LEVEL_IDC
#define VDO_S_LEVEL_IDC_POS                                     (16U)
#define VDO_S_LEVEL_IDC_LEN                                     (8U)
#define VDO_S_LEVEL_IDC_MSK                                     (((1U<<VDO_S_LEVEL_IDC_LEN)-1)<<VDO_S_LEVEL_IDC_POS)
#define VDO_S_LEVEL_IDC_UMSK                                    (~(((1U<<VDO_S_LEVEL_IDC_LEN)-1)<<VDO_S_LEVEL_IDC_POS))

/* 0x5c : vdo_core_reg14 */
#define VDO_CORE_REG14_OFFSET                                   (0x5c)
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
#define VDO_S_LUMA8X8_COST                                      VDO_S_LUMA8X8_COST
#define VDO_S_LUMA8X8_COST_POS                                  (16U)
#define VDO_S_LUMA8X8_COST_LEN                                  (3U)
#define VDO_S_LUMA8X8_COST_MSK                                  (((1U<<VDO_S_LUMA8X8_COST_LEN)-1)<<VDO_S_LUMA8X8_COST_POS)
#define VDO_S_LUMA8X8_COST_UMSK                                 (~(((1U<<VDO_S_LUMA8X8_COST_LEN)-1)<<VDO_S_LUMA8X8_COST_POS))
#define VDO_S_LUMA16X16_COST                                    VDO_S_LUMA16X16_COST
#define VDO_S_LUMA16X16_COST_POS                                (19U)
#define VDO_S_LUMA16X16_COST_LEN                                (3U)
#define VDO_S_LUMA16X16_COST_MSK                                (((1U<<VDO_S_LUMA16X16_COST_LEN)-1)<<VDO_S_LUMA16X16_COST_POS)
#define VDO_S_LUMA16X16_COST_UMSK                               (~(((1U<<VDO_S_LUMA16X16_COST_LEN)-1)<<VDO_S_LUMA16X16_COST_POS))
#define VDO_S_CHROMA8X8_COST                                    VDO_S_CHROMA8X8_COST
#define VDO_S_CHROMA8X8_COST_POS                                (22U)
#define VDO_S_CHROMA8X8_COST_LEN                                (3U)
#define VDO_S_CHROMA8X8_COST_MSK                                (((1U<<VDO_S_CHROMA8X8_COST_LEN)-1)<<VDO_S_CHROMA8X8_COST_POS)
#define VDO_S_CHROMA8X8_COST_UMSK                               (~(((1U<<VDO_S_CHROMA8X8_COST_LEN)-1)<<VDO_S_CHROMA8X8_COST_POS))

/* 0x64 : vdo_core_reg16 */
#define VDO_CORE_REG16_OFFSET                                   (0x64)
#define VDO_FRAME0                                              VDO_FRAME0
#define VDO_FRAME0_POS                                          (0U)
#define VDO_FRAME0_LEN                                          (14U)
#define VDO_FRAME0_MSK                                          (((1U<<VDO_FRAME0_LEN)-1)<<VDO_FRAME0_POS)
#define VDO_FRAME0_UMSK                                         (~(((1U<<VDO_FRAME0_LEN)-1)<<VDO_FRAME0_POS))
#define VDO_S_FRAME0                                            VDO_S_FRAME0
#define VDO_S_FRAME0_POS                                        (16U)
#define VDO_S_FRAME0_LEN                                        (14U)
#define VDO_S_FRAME0_MSK                                        (((1U<<VDO_S_FRAME0_LEN)-1)<<VDO_S_FRAME0_POS)
#define VDO_S_FRAME0_UMSK                                       (~(((1U<<VDO_S_FRAME0_LEN)-1)<<VDO_S_FRAME0_POS))

/* 0x68 : vdo_core_reg17 */
#define VDO_CORE_REG17_OFFSET                                   (0x68)
#define VDO_FRAME1                                              VDO_FRAME1
#define VDO_FRAME1_POS                                          (0U)
#define VDO_FRAME1_LEN                                          (14U)
#define VDO_FRAME1_MSK                                          (((1U<<VDO_FRAME1_LEN)-1)<<VDO_FRAME1_POS)
#define VDO_FRAME1_UMSK                                         (~(((1U<<VDO_FRAME1_LEN)-1)<<VDO_FRAME1_POS))
#define VDO_S_FRAME1                                            VDO_S_FRAME1
#define VDO_S_FRAME1_POS                                        (16U)
#define VDO_S_FRAME1_LEN                                        (14U)
#define VDO_S_FRAME1_MSK                                        (((1U<<VDO_S_FRAME1_LEN)-1)<<VDO_S_FRAME1_POS)
#define VDO_S_FRAME1_UMSK                                       (~(((1U<<VDO_S_FRAME1_LEN)-1)<<VDO_S_FRAME1_POS))

/* 0x6c : vdo_core_reg18 */
#define VDO_CORE_REG18_OFFSET                                   (0x6c)
#define VDO_EXT_DATA                                            VDO_EXT_DATA
#define VDO_EXT_DATA_POS                                        (0U)
#define VDO_EXT_DATA_LEN                                        (14U)
#define VDO_EXT_DATA_MSK                                        (((1U<<VDO_EXT_DATA_LEN)-1)<<VDO_EXT_DATA_POS)
#define VDO_EXT_DATA_UMSK                                       (~(((1U<<VDO_EXT_DATA_LEN)-1)<<VDO_EXT_DATA_POS))
#define VDO_S_EXT_DATA                                          VDO_S_EXT_DATA
#define VDO_S_EXT_DATA_POS                                      (16U)
#define VDO_S_EXT_DATA_LEN                                      (14U)
#define VDO_S_EXT_DATA_MSK                                      (((1U<<VDO_S_EXT_DATA_LEN)-1)<<VDO_S_EXT_DATA_POS)
#define VDO_S_EXT_DATA_UMSK                                     (~(((1U<<VDO_S_EXT_DATA_LEN)-1)<<VDO_S_EXT_DATA_POS))

/* 0x70 : vdo_core_reg19 */
#define VDO_CORE_REG19_OFFSET                                   (0x70)
#define VDO_EXT_MEM_CONFIG0                                     VDO_EXT_MEM_CONFIG0
#define VDO_EXT_MEM_CONFIG0_POS                                 (0U)
#define VDO_EXT_MEM_CONFIG0_LEN                                 (6U)
#define VDO_EXT_MEM_CONFIG0_MSK                                 (((1U<<VDO_EXT_MEM_CONFIG0_LEN)-1)<<VDO_EXT_MEM_CONFIG0_POS)
#define VDO_EXT_MEM_CONFIG0_UMSK                                (~(((1U<<VDO_EXT_MEM_CONFIG0_LEN)-1)<<VDO_EXT_MEM_CONFIG0_POS))
#define VDO_S_EXT_MEM_CONFIG0                                   VDO_S_EXT_MEM_CONFIG0
#define VDO_S_EXT_MEM_CONFIG0_POS                               (16U)
#define VDO_S_EXT_MEM_CONFIG0_LEN                               (6U)
#define VDO_S_EXT_MEM_CONFIG0_MSK                               (((1U<<VDO_S_EXT_MEM_CONFIG0_LEN)-1)<<VDO_S_EXT_MEM_CONFIG0_POS)
#define VDO_S_EXT_MEM_CONFIG0_UMSK                              (~(((1U<<VDO_S_EXT_MEM_CONFIG0_LEN)-1)<<VDO_S_EXT_MEM_CONFIG0_POS))

/* 0x74 : vdo_core_reg20 */
#define VDO_CORE_REG20_OFFSET                                   (0x74)
#define VDO_EXT_MEM_CONFIG1                                     VDO_EXT_MEM_CONFIG1
#define VDO_EXT_MEM_CONFIG1_POS                                 (0U)
#define VDO_EXT_MEM_CONFIG1_LEN                                 (5U)
#define VDO_EXT_MEM_CONFIG1_MSK                                 (((1U<<VDO_EXT_MEM_CONFIG1_LEN)-1)<<VDO_EXT_MEM_CONFIG1_POS)
#define VDO_EXT_MEM_CONFIG1_UMSK                                (~(((1U<<VDO_EXT_MEM_CONFIG1_LEN)-1)<<VDO_EXT_MEM_CONFIG1_POS))
#define VDO_S_EXT_MEM_CONFIG1                                   VDO_S_EXT_MEM_CONFIG1
#define VDO_S_EXT_MEM_CONFIG1_POS                               (16U)
#define VDO_S_EXT_MEM_CONFIG1_LEN                               (5U)
#define VDO_S_EXT_MEM_CONFIG1_MSK                               (((1U<<VDO_S_EXT_MEM_CONFIG1_LEN)-1)<<VDO_S_EXT_MEM_CONFIG1_POS)
#define VDO_S_EXT_MEM_CONFIG1_UMSK                              (~(((1U<<VDO_S_EXT_MEM_CONFIG1_LEN)-1)<<VDO_S_EXT_MEM_CONFIG1_POS))

/* 0x78 : vdo_core_reg21 */
#define VDO_CORE_REG21_OFFSET                                   (0x78)
#define VDO_EXT_MEM_CONFIG2                                     VDO_EXT_MEM_CONFIG2
#define VDO_EXT_MEM_CONFIG2_POS                                 (0U)
#define VDO_EXT_MEM_CONFIG2_LEN                                 (12U)
#define VDO_EXT_MEM_CONFIG2_MSK                                 (((1U<<VDO_EXT_MEM_CONFIG2_LEN)-1)<<VDO_EXT_MEM_CONFIG2_POS)
#define VDO_EXT_MEM_CONFIG2_UMSK                                (~(((1U<<VDO_EXT_MEM_CONFIG2_LEN)-1)<<VDO_EXT_MEM_CONFIG2_POS))
#define VDO_S_EXT_MEM_CONFIG2                                   VDO_S_EXT_MEM_CONFIG2
#define VDO_S_EXT_MEM_CONFIG2_POS                               (16U)
#define VDO_S_EXT_MEM_CONFIG2_LEN                               (12U)
#define VDO_S_EXT_MEM_CONFIG2_MSK                               (((1U<<VDO_S_EXT_MEM_CONFIG2_LEN)-1)<<VDO_S_EXT_MEM_CONFIG2_POS)
#define VDO_S_EXT_MEM_CONFIG2_UMSK                              (~(((1U<<VDO_S_EXT_MEM_CONFIG2_LEN)-1)<<VDO_S_EXT_MEM_CONFIG2_POS))

/* 0x7c : vdo_core_reg22 */
#define VDO_CORE_REG22_OFFSET                                   (0x7c)
#define VDO_EXT_MEM_CONFIG3                                     VDO_EXT_MEM_CONFIG3
#define VDO_EXT_MEM_CONFIG3_POS                                 (0U)
#define VDO_EXT_MEM_CONFIG3_LEN                                 (10U)
#define VDO_EXT_MEM_CONFIG3_MSK                                 (((1U<<VDO_EXT_MEM_CONFIG3_LEN)-1)<<VDO_EXT_MEM_CONFIG3_POS)
#define VDO_EXT_MEM_CONFIG3_UMSK                                (~(((1U<<VDO_EXT_MEM_CONFIG3_LEN)-1)<<VDO_EXT_MEM_CONFIG3_POS))
#define VDO_S_EXT_MEM_CONFIG3                                   VDO_S_EXT_MEM_CONFIG3
#define VDO_S_EXT_MEM_CONFIG3_POS                               (16U)
#define VDO_S_EXT_MEM_CONFIG3_LEN                               (10U)
#define VDO_S_EXT_MEM_CONFIG3_MSK                               (((1U<<VDO_S_EXT_MEM_CONFIG3_LEN)-1)<<VDO_S_EXT_MEM_CONFIG3_POS)
#define VDO_S_EXT_MEM_CONFIG3_UMSK                              (~(((1U<<VDO_S_EXT_MEM_CONFIG3_LEN)-1)<<VDO_S_EXT_MEM_CONFIG3_POS))

/* 0x80 : vdo_core_reg23 */
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
#define VDO_S_NUM_IMB_BITS                                      VDO_S_NUM_IMB_BITS
#define VDO_S_NUM_IMB_BITS_POS                                  (16U)
#define VDO_S_NUM_IMB_BITS_LEN                                  (12U)
#define VDO_S_NUM_IMB_BITS_MSK                                  (((1U<<VDO_S_NUM_IMB_BITS_LEN)-1)<<VDO_S_NUM_IMB_BITS_POS)
#define VDO_S_NUM_IMB_BITS_UMSK                                 (~(((1U<<VDO_S_NUM_IMB_BITS_LEN)-1)<<VDO_S_NUM_IMB_BITS_POS))
#define VDO_S_NAL_ALIGN                                         VDO_S_NAL_ALIGN
#define VDO_S_NAL_ALIGN_POS                                     (29U)
#define VDO_S_NAL_ALIGN_LEN                                     (1U)
#define VDO_S_NAL_ALIGN_MSK                                     (((1U<<VDO_S_NAL_ALIGN_LEN)-1)<<VDO_S_NAL_ALIGN_POS)
#define VDO_S_NAL_ALIGN_UMSK                                    (~(((1U<<VDO_S_NAL_ALIGN_LEN)-1)<<VDO_S_NAL_ALIGN_POS))
#define VDO_S_CONS_IPRED                                        VDO_S_CONS_IPRED
#define VDO_S_CONS_IPRED_POS                                    (30U)
#define VDO_S_CONS_IPRED_LEN                                    (1U)
#define VDO_S_CONS_IPRED_MSK                                    (((1U<<VDO_S_CONS_IPRED_LEN)-1)<<VDO_S_CONS_IPRED_POS)
#define VDO_S_CONS_IPRED_UMSK                                   (~(((1U<<VDO_S_CONS_IPRED_LEN)-1)<<VDO_S_CONS_IPRED_POS))

/* 0x84 : vdo_core_reg24 */
#define VDO_CORE_REG24_OFFSET                                   (0x84)
#define VDO_NUM_PMB_BITS                                        VDO_NUM_PMB_BITS
#define VDO_NUM_PMB_BITS_POS                                    (0U)
#define VDO_NUM_PMB_BITS_LEN                                    (12U)
#define VDO_NUM_PMB_BITS_MSK                                    (((1U<<VDO_NUM_PMB_BITS_LEN)-1)<<VDO_NUM_PMB_BITS_POS)
#define VDO_NUM_PMB_BITS_UMSK                                   (~(((1U<<VDO_NUM_PMB_BITS_LEN)-1)<<VDO_NUM_PMB_BITS_POS))
#define VDO_S_NUM_PMB_BITS                                      VDO_S_NUM_PMB_BITS
#define VDO_S_NUM_PMB_BITS_POS                                  (16U)
#define VDO_S_NUM_PMB_BITS_LEN                                  (12U)
#define VDO_S_NUM_PMB_BITS_MSK                                  (((1U<<VDO_S_NUM_PMB_BITS_LEN)-1)<<VDO_S_NUM_PMB_BITS_POS)
#define VDO_S_NUM_PMB_BITS_UMSK                                 (~(((1U<<VDO_S_NUM_PMB_BITS_LEN)-1)<<VDO_S_NUM_PMB_BITS_POS))

/* 0x88 : vdo_core_reg25 */
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
#define VDO_S_INTERLACE_MODE                                    VDO_S_INTERLACE_MODE
#define VDO_S_INTERLACE_MODE_POS                                (16U)
#define VDO_S_INTERLACE_MODE_LEN                                (1U)
#define VDO_S_INTERLACE_MODE_MSK                                (((1U<<VDO_S_INTERLACE_MODE_LEN)-1)<<VDO_S_INTERLACE_MODE_POS)
#define VDO_S_INTERLACE_MODE_UMSK                               (~(((1U<<VDO_S_INTERLACE_MODE_LEN)-1)<<VDO_S_INTERLACE_MODE_POS))
#define VDO_S_BOTTOM_FIELD_FIRST                                VDO_S_BOTTOM_FIELD_FIRST
#define VDO_S_BOTTOM_FIELD_FIRST_POS                            (17U)
#define VDO_S_BOTTOM_FIELD_FIRST_LEN                            (1U)
#define VDO_S_BOTTOM_FIELD_FIRST_MSK                            (((1U<<VDO_S_BOTTOM_FIELD_FIRST_LEN)-1)<<VDO_S_BOTTOM_FIELD_FIRST_POS)
#define VDO_S_BOTTOM_FIELD_FIRST_UMSK                           (~(((1U<<VDO_S_BOTTOM_FIELD_FIRST_LEN)-1)<<VDO_S_BOTTOM_FIELD_FIRST_POS))
#define VDO_S_PREV_FIELD_REF                                    VDO_S_PREV_FIELD_REF
#define VDO_S_PREV_FIELD_REF_POS                                (18U)
#define VDO_S_PREV_FIELD_REF_LEN                                (1U)
#define VDO_S_PREV_FIELD_REF_MSK                                (((1U<<VDO_S_PREV_FIELD_REF_LEN)-1)<<VDO_S_PREV_FIELD_REF_POS)
#define VDO_S_PREV_FIELD_REF_UMSK                               (~(((1U<<VDO_S_PREV_FIELD_REF_LEN)-1)<<VDO_S_PREV_FIELD_REF_POS))

/* 0x94 : vdo_core_reg28 */
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
#define VDO_S_PFRAME_MIN_QP                                     VDO_S_PFRAME_MIN_QP
#define VDO_S_PFRAME_MIN_QP_POS                                 (16U)
#define VDO_S_PFRAME_MIN_QP_LEN                                 (6U)
#define VDO_S_PFRAME_MIN_QP_MSK                                 (((1U<<VDO_S_PFRAME_MIN_QP_LEN)-1)<<VDO_S_PFRAME_MIN_QP_POS)
#define VDO_S_PFRAME_MIN_QP_UMSK                                (~(((1U<<VDO_S_PFRAME_MIN_QP_LEN)-1)<<VDO_S_PFRAME_MIN_QP_POS))
#define VDO_S_PFRAME_MAX_QP                                     VDO_S_PFRAME_MAX_QP
#define VDO_S_PFRAME_MAX_QP_POS                                 (24U)
#define VDO_S_PFRAME_MAX_QP_LEN                                 (6U)
#define VDO_S_PFRAME_MAX_QP_MSK                                 (((1U<<VDO_S_PFRAME_MAX_QP_LEN)-1)<<VDO_S_PFRAME_MAX_QP_POS)
#define VDO_S_PFRAME_MAX_QP_UMSK                                (~(((1U<<VDO_S_PFRAME_MAX_QP_LEN)-1)<<VDO_S_PFRAME_MAX_QP_POS))

/* 0x9c : vdo_core_reg30 */
#define VDO_CORE_REG30_OFFSET                                   (0x9c)
#define VDO_RESET_I_STATE                                       VDO_RESET_I_STATE
#define VDO_RESET_I_STATE_POS                                   (15U)
#define VDO_RESET_I_STATE_LEN                                   (1U)
#define VDO_RESET_I_STATE_MSK                                   (((1U<<VDO_RESET_I_STATE_LEN)-1)<<VDO_RESET_I_STATE_POS)
#define VDO_RESET_I_STATE_UMSK                                  (~(((1U<<VDO_RESET_I_STATE_LEN)-1)<<VDO_RESET_I_STATE_POS))
#define VDO_S_RESET_I_STATE                                     VDO_S_RESET_I_STATE
#define VDO_S_RESET_I_STATE_POS                                 (31U)
#define VDO_S_RESET_I_STATE_LEN                                 (1U)
#define VDO_S_RESET_I_STATE_MSK                                 (((1U<<VDO_S_RESET_I_STATE_LEN)-1)<<VDO_S_RESET_I_STATE_POS)
#define VDO_S_RESET_I_STATE_UMSK                                (~(((1U<<VDO_S_RESET_I_STATE_LEN)-1)<<VDO_S_RESET_I_STATE_POS))

/* 0xa0 : vdo_core_reg31 */
#define VDO_CORE_REG31_OFFSET                                   (0xa0)
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
#define VDO_S_IFRAME_MIN_QP                                     VDO_S_IFRAME_MIN_QP
#define VDO_S_IFRAME_MIN_QP_POS                                 (16U)
#define VDO_S_IFRAME_MIN_QP_LEN                                 (6U)
#define VDO_S_IFRAME_MIN_QP_MSK                                 (((1U<<VDO_S_IFRAME_MIN_QP_LEN)-1)<<VDO_S_IFRAME_MIN_QP_POS)
#define VDO_S_IFRAME_MIN_QP_UMSK                                (~(((1U<<VDO_S_IFRAME_MIN_QP_LEN)-1)<<VDO_S_IFRAME_MIN_QP_POS))
#define VDO_S_IFRAME_MAX_QP                                     VDO_S_IFRAME_MAX_QP
#define VDO_S_IFRAME_MAX_QP_POS                                 (24U)
#define VDO_S_IFRAME_MAX_QP_LEN                                 (6U)
#define VDO_S_IFRAME_MAX_QP_MSK                                 (((1U<<VDO_S_IFRAME_MAX_QP_LEN)-1)<<VDO_S_IFRAME_MAX_QP_POS)
#define VDO_S_IFRAME_MAX_QP_UMSK                                (~(((1U<<VDO_S_IFRAME_MAX_QP_LEN)-1)<<VDO_S_IFRAME_MAX_QP_POS))

/* 0xa4 : vdo_core_reg32 */
#define VDO_CORE_REG32_OFFSET                                   (0xa4)
#define VDO_VUI_TIME_SCALE_L                                    VDO_VUI_TIME_SCALE_L
#define VDO_VUI_TIME_SCALE_L_POS                                (0U)
#define VDO_VUI_TIME_SCALE_L_LEN                                (16U)
#define VDO_VUI_TIME_SCALE_L_MSK                                (((1U<<VDO_VUI_TIME_SCALE_L_LEN)-1)<<VDO_VUI_TIME_SCALE_L_POS)
#define VDO_VUI_TIME_SCALE_L_UMSK                               (~(((1U<<VDO_VUI_TIME_SCALE_L_LEN)-1)<<VDO_VUI_TIME_SCALE_L_POS))
#define VDO_S_VUI_TIME_SCALE_L                                  VDO_S_VUI_TIME_SCALE_L
#define VDO_S_VUI_TIME_SCALE_L_POS                              (16U)
#define VDO_S_VUI_TIME_SCALE_L_LEN                              (16U)
#define VDO_S_VUI_TIME_SCALE_L_MSK                              (((1U<<VDO_S_VUI_TIME_SCALE_L_LEN)-1)<<VDO_S_VUI_TIME_SCALE_L_POS)
#define VDO_S_VUI_TIME_SCALE_L_UMSK                             (~(((1U<<VDO_S_VUI_TIME_SCALE_L_LEN)-1)<<VDO_S_VUI_TIME_SCALE_L_POS))

/* 0xa8 : vdo_core_reg33 */
#define VDO_CORE_REG33_OFFSET                                   (0xa8)
#define VDO_VUI_TIME_SCALE_H                                    VDO_VUI_TIME_SCALE_H
#define VDO_VUI_TIME_SCALE_H_POS                                (0U)
#define VDO_VUI_TIME_SCALE_H_LEN                                (16U)
#define VDO_VUI_TIME_SCALE_H_MSK                                (((1U<<VDO_VUI_TIME_SCALE_H_LEN)-1)<<VDO_VUI_TIME_SCALE_H_POS)
#define VDO_VUI_TIME_SCALE_H_UMSK                               (~(((1U<<VDO_VUI_TIME_SCALE_H_LEN)-1)<<VDO_VUI_TIME_SCALE_H_POS))
#define VDO_S_VUI_TIME_SCALE_H                                  VDO_S_VUI_TIME_SCALE_H
#define VDO_S_VUI_TIME_SCALE_H_POS                              (16U)
#define VDO_S_VUI_TIME_SCALE_H_LEN                              (16U)
#define VDO_S_VUI_TIME_SCALE_H_MSK                              (((1U<<VDO_S_VUI_TIME_SCALE_H_LEN)-1)<<VDO_S_VUI_TIME_SCALE_H_POS)
#define VDO_S_VUI_TIME_SCALE_H_UMSK                             (~(((1U<<VDO_S_VUI_TIME_SCALE_H_LEN)-1)<<VDO_S_VUI_TIME_SCALE_H_POS))

/* 0xac : vdo_core_reg34 */
#define VDO_CORE_REG34_OFFSET                                   (0xac)
#define VDO_VUI_NUM_U_TICK_L                                    VDO_VUI_NUM_U_TICK_L
#define VDO_VUI_NUM_U_TICK_L_POS                                (0U)
#define VDO_VUI_NUM_U_TICK_L_LEN                                (16U)
#define VDO_VUI_NUM_U_TICK_L_MSK                                (((1U<<VDO_VUI_NUM_U_TICK_L_LEN)-1)<<VDO_VUI_NUM_U_TICK_L_POS)
#define VDO_VUI_NUM_U_TICK_L_UMSK                               (~(((1U<<VDO_VUI_NUM_U_TICK_L_LEN)-1)<<VDO_VUI_NUM_U_TICK_L_POS))
#define VDO_S_VUI_NUM_U_TICK_L                                  VDO_S_VUI_NUM_U_TICK_L
#define VDO_S_VUI_NUM_U_TICK_L_POS                              (16U)
#define VDO_S_VUI_NUM_U_TICK_L_LEN                              (16U)
#define VDO_S_VUI_NUM_U_TICK_L_MSK                              (((1U<<VDO_S_VUI_NUM_U_TICK_L_LEN)-1)<<VDO_S_VUI_NUM_U_TICK_L_POS)
#define VDO_S_VUI_NUM_U_TICK_L_UMSK                             (~(((1U<<VDO_S_VUI_NUM_U_TICK_L_LEN)-1)<<VDO_S_VUI_NUM_U_TICK_L_POS))

/* 0xb0 : vdo_core_reg35 */
#define VDO_CORE_REG35_OFFSET                                   (0xb0)
#define VDO_VUI_NUM_U_TICK_H                                    VDO_VUI_NUM_U_TICK_H
#define VDO_VUI_NUM_U_TICK_H_POS                                (0U)
#define VDO_VUI_NUM_U_TICK_H_LEN                                (16U)
#define VDO_VUI_NUM_U_TICK_H_MSK                                (((1U<<VDO_VUI_NUM_U_TICK_H_LEN)-1)<<VDO_VUI_NUM_U_TICK_H_POS)
#define VDO_VUI_NUM_U_TICK_H_UMSK                               (~(((1U<<VDO_VUI_NUM_U_TICK_H_LEN)-1)<<VDO_VUI_NUM_U_TICK_H_POS))
#define VDO_S_VUI_NUM_U_TICK_H                                  VDO_S_VUI_NUM_U_TICK_H
#define VDO_S_VUI_NUM_U_TICK_H_POS                              (16U)
#define VDO_S_VUI_NUM_U_TICK_H_LEN                              (16U)
#define VDO_S_VUI_NUM_U_TICK_H_MSK                              (((1U<<VDO_S_VUI_NUM_U_TICK_H_LEN)-1)<<VDO_S_VUI_NUM_U_TICK_H_POS)
#define VDO_S_VUI_NUM_U_TICK_H_UMSK                             (~(((1U<<VDO_S_VUI_NUM_U_TICK_H_LEN)-1)<<VDO_S_VUI_NUM_U_TICK_H_POS))

/* 0xb4 : vdo_core_reg36 */
#define VDO_CORE_REG36_OFFSET                                   (0xb4)
#define VDO_VUI_ASPECT_IDC                                      VDO_VUI_ASPECT_IDC
#define VDO_VUI_ASPECT_IDC_POS                                  (0U)
#define VDO_VUI_ASPECT_IDC_LEN                                  (8U)
#define VDO_VUI_ASPECT_IDC_MSK                                  (((1U<<VDO_VUI_ASPECT_IDC_LEN)-1)<<VDO_VUI_ASPECT_IDC_POS)
#define VDO_VUI_ASPECT_IDC_UMSK                                 (~(((1U<<VDO_VUI_ASPECT_IDC_LEN)-1)<<VDO_VUI_ASPECT_IDC_POS))
#define VDO_S_VUI_ASPECT_IDC                                    VDO_S_VUI_ASPECT_IDC
#define VDO_S_VUI_ASPECT_IDC_POS                                (16U)
#define VDO_S_VUI_ASPECT_IDC_LEN                                (8U)
#define VDO_S_VUI_ASPECT_IDC_MSK                                (((1U<<VDO_S_VUI_ASPECT_IDC_LEN)-1)<<VDO_S_VUI_ASPECT_IDC_POS)
#define VDO_S_VUI_ASPECT_IDC_UMSK                               (~(((1U<<VDO_S_VUI_ASPECT_IDC_LEN)-1)<<VDO_S_VUI_ASPECT_IDC_POS))

/* 0xb8 : vdo_core_reg37 */
#define VDO_CORE_REG37_OFFSET                                   (0xb8)
#define VDO_VUI_ASPECT_WIDTH                                    VDO_VUI_ASPECT_WIDTH
#define VDO_VUI_ASPECT_WIDTH_POS                                (0U)
#define VDO_VUI_ASPECT_WIDTH_LEN                                (16U)
#define VDO_VUI_ASPECT_WIDTH_MSK                                (((1U<<VDO_VUI_ASPECT_WIDTH_LEN)-1)<<VDO_VUI_ASPECT_WIDTH_POS)
#define VDO_VUI_ASPECT_WIDTH_UMSK                               (~(((1U<<VDO_VUI_ASPECT_WIDTH_LEN)-1)<<VDO_VUI_ASPECT_WIDTH_POS))
#define VDO_S_VUI_ASPECT_WIDTH                                  VDO_S_VUI_ASPECT_WIDTH
#define VDO_S_VUI_ASPECT_WIDTH_POS                              (16U)
#define VDO_S_VUI_ASPECT_WIDTH_LEN                              (16U)
#define VDO_S_VUI_ASPECT_WIDTH_MSK                              (((1U<<VDO_S_VUI_ASPECT_WIDTH_LEN)-1)<<VDO_S_VUI_ASPECT_WIDTH_POS)
#define VDO_S_VUI_ASPECT_WIDTH_UMSK                             (~(((1U<<VDO_S_VUI_ASPECT_WIDTH_LEN)-1)<<VDO_S_VUI_ASPECT_WIDTH_POS))

/* 0xbc : vdo_core_reg38 */
#define VDO_CORE_REG38_OFFSET                                   (0xbc)
#define VDO_VUI_ASPECT_HEIGHT                                   VDO_VUI_ASPECT_HEIGHT
#define VDO_VUI_ASPECT_HEIGHT_POS                               (0U)
#define VDO_VUI_ASPECT_HEIGHT_LEN                               (16U)
#define VDO_VUI_ASPECT_HEIGHT_MSK                               (((1U<<VDO_VUI_ASPECT_HEIGHT_LEN)-1)<<VDO_VUI_ASPECT_HEIGHT_POS)
#define VDO_VUI_ASPECT_HEIGHT_UMSK                              (~(((1U<<VDO_VUI_ASPECT_HEIGHT_LEN)-1)<<VDO_VUI_ASPECT_HEIGHT_POS))
#define VDO_S_VUI_ASPECT_HEIGHT                                 VDO_S_VUI_ASPECT_HEIGHT
#define VDO_S_VUI_ASPECT_HEIGHT_POS                             (16U)
#define VDO_S_VUI_ASPECT_HEIGHT_LEN                             (16U)
#define VDO_S_VUI_ASPECT_HEIGHT_MSK                             (((1U<<VDO_S_VUI_ASPECT_HEIGHT_LEN)-1)<<VDO_S_VUI_ASPECT_HEIGHT_POS)
#define VDO_S_VUI_ASPECT_HEIGHT_UMSK                            (~(((1U<<VDO_S_VUI_ASPECT_HEIGHT_LEN)-1)<<VDO_S_VUI_ASPECT_HEIGHT_POS))

/* 0xc0 : vdo_src_dvp_sel */
#define VDO_SRC_DVP_SEL_OFFSET                                  (0xc0)
#define VDO_UV_DVP2AXI_SEL                                      VDO_UV_DVP2AXI_SEL
#define VDO_UV_DVP2AXI_SEL_POS                                  (0U)
#define VDO_UV_DVP2AXI_SEL_LEN                                  (3U)
#define VDO_UV_DVP2AXI_SEL_MSK                                  (((1U<<VDO_UV_DVP2AXI_SEL_LEN)-1)<<VDO_UV_DVP2AXI_SEL_POS)
#define VDO_UV_DVP2AXI_SEL_UMSK                                 (~(((1U<<VDO_UV_DVP2AXI_SEL_LEN)-1)<<VDO_UV_DVP2AXI_SEL_POS))
#define VDO_Y_DVP2AXI_SEL                                       VDO_Y_DVP2AXI_SEL
#define VDO_Y_DVP2AXI_SEL_POS                                   (4U)
#define VDO_Y_DVP2AXI_SEL_LEN                                   (3U)
#define VDO_Y_DVP2AXI_SEL_MSK                                   (((1U<<VDO_Y_DVP2AXI_SEL_LEN)-1)<<VDO_Y_DVP2AXI_SEL_POS)
#define VDO_Y_DVP2AXI_SEL_UMSK                                  (~(((1U<<VDO_Y_DVP2AXI_SEL_LEN)-1)<<VDO_Y_DVP2AXI_SEL_POS))
#define VDO_S_UV_DVP2AXI_SEL                                    VDO_S_UV_DVP2AXI_SEL
#define VDO_S_UV_DVP2AXI_SEL_POS                                (16U)
#define VDO_S_UV_DVP2AXI_SEL_LEN                                (3U)
#define VDO_S_UV_DVP2AXI_SEL_MSK                                (((1U<<VDO_S_UV_DVP2AXI_SEL_LEN)-1)<<VDO_S_UV_DVP2AXI_SEL_POS)
#define VDO_S_UV_DVP2AXI_SEL_UMSK                               (~(((1U<<VDO_S_UV_DVP2AXI_SEL_LEN)-1)<<VDO_S_UV_DVP2AXI_SEL_POS))
#define VDO_S_Y_DVP2AXI_SEL                                     VDO_S_Y_DVP2AXI_SEL
#define VDO_S_Y_DVP2AXI_SEL_POS                                 (20U)
#define VDO_S_Y_DVP2AXI_SEL_LEN                                 (3U)
#define VDO_S_Y_DVP2AXI_SEL_MSK                                 (((1U<<VDO_S_Y_DVP2AXI_SEL_LEN)-1)<<VDO_S_Y_DVP2AXI_SEL_POS)
#define VDO_S_Y_DVP2AXI_SEL_UMSK                                (~(((1U<<VDO_S_Y_DVP2AXI_SEL_LEN)-1)<<VDO_S_Y_DVP2AXI_SEL_POS))

/* 0xc4 : vdo_padding_ctrl */
#define VDO_PADDING_CTRL_OFFSET                                 (0xc4)
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

/* 0xd8 : vdo_frame_id_clr */
#define VDO_FRAME_ID_CLR_OFFSET                                 (0xd8)
#define VDO_FRAME_ID_CLR                                        VDO_FRAME_ID_CLR
#define VDO_FRAME_ID_CLR_POS                                    (0U)
#define VDO_FRAME_ID_CLR_LEN                                    (1U)
#define VDO_FRAME_ID_CLR_MSK                                    (((1U<<VDO_FRAME_ID_CLR_LEN)-1)<<VDO_FRAME_ID_CLR_POS)
#define VDO_FRAME_ID_CLR_UMSK                                   (~(((1U<<VDO_FRAME_ID_CLR_LEN)-1)<<VDO_FRAME_ID_CLR_POS))
#define VDO_S_FRAME_ID_CLR                                      VDO_S_FRAME_ID_CLR
#define VDO_S_FRAME_ID_CLR_POS                                  (1U)
#define VDO_S_FRAME_ID_CLR_LEN                                  (1U)
#define VDO_S_FRAME_ID_CLR_MSK                                  (((1U<<VDO_S_FRAME_ID_CLR_LEN)-1)<<VDO_S_FRAME_ID_CLR_POS)
#define VDO_S_FRAME_ID_CLR_UMSK                                 (~(((1U<<VDO_S_FRAME_ID_CLR_LEN)-1)<<VDO_S_FRAME_ID_CLR_POS))

/* 0x100 : vdo_int */
#define VDO_INT_OFFSET                                          (0x100)
#define VDO_FRM_DONE_INT                                        VDO_FRM_DONE_INT
#define VDO_FRM_DONE_INT_POS                                    (0U)
#define VDO_FRM_DONE_INT_LEN                                    (1U)
#define VDO_FRM_DONE_INT_MSK                                    (((1U<<VDO_FRM_DONE_INT_LEN)-1)<<VDO_FRM_DONE_INT_POS)
#define VDO_FRM_DONE_INT_UMSK                                   (~(((1U<<VDO_FRM_DONE_INT_LEN)-1)<<VDO_FRM_DONE_INT_POS))
#define VDO_S_FRM_DONE_INT                                      VDO_S_FRM_DONE_INT
#define VDO_S_FRM_DONE_INT_POS                                  (1U)
#define VDO_S_FRM_DONE_INT_LEN                                  (1U)
#define VDO_S_FRM_DONE_INT_MSK                                  (((1U<<VDO_S_FRM_DONE_INT_LEN)-1)<<VDO_S_FRM_DONE_INT_POS)
#define VDO_S_FRM_DONE_INT_UMSK                                 (~(((1U<<VDO_S_FRM_DONE_INT_LEN)-1)<<VDO_S_FRM_DONE_INT_POS))
#define VDO_SEQ_DONE_INT                                        VDO_SEQ_DONE_INT
#define VDO_SEQ_DONE_INT_POS                                    (4U)
#define VDO_SEQ_DONE_INT_LEN                                    (1U)
#define VDO_SEQ_DONE_INT_MSK                                    (((1U<<VDO_SEQ_DONE_INT_LEN)-1)<<VDO_SEQ_DONE_INT_POS)
#define VDO_SEQ_DONE_INT_UMSK                                   (~(((1U<<VDO_SEQ_DONE_INT_LEN)-1)<<VDO_SEQ_DONE_INT_POS))
#define VDO_S_SEQ_DONE_INT                                      VDO_S_SEQ_DONE_INT
#define VDO_S_SEQ_DONE_INT_POS                                  (5U)
#define VDO_S_SEQ_DONE_INT_LEN                                  (1U)
#define VDO_S_SEQ_DONE_INT_MSK                                  (((1U<<VDO_S_SEQ_DONE_INT_LEN)-1)<<VDO_S_SEQ_DONE_INT_POS)
#define VDO_S_SEQ_DONE_INT_UMSK                                 (~(((1U<<VDO_S_SEQ_DONE_INT_LEN)-1)<<VDO_S_SEQ_DONE_INT_POS))
#define VDO_BS_FULL_INT                                         VDO_BS_FULL_INT
#define VDO_BS_FULL_INT_POS                                     (8U)
#define VDO_BS_FULL_INT_LEN                                     (1U)
#define VDO_BS_FULL_INT_MSK                                     (((1U<<VDO_BS_FULL_INT_LEN)-1)<<VDO_BS_FULL_INT_POS)
#define VDO_BS_FULL_INT_UMSK                                    (~(((1U<<VDO_BS_FULL_INT_LEN)-1)<<VDO_BS_FULL_INT_POS))
#define VDO_S_BS_FULL_INT                                       VDO_S_BS_FULL_INT
#define VDO_S_BS_FULL_INT_POS                                   (9U)
#define VDO_S_BS_FULL_INT_LEN                                   (1U)
#define VDO_S_BS_FULL_INT_MSK                                   (((1U<<VDO_S_BS_FULL_INT_LEN)-1)<<VDO_S_BS_FULL_INT_POS)
#define VDO_S_BS_FULL_INT_UMSK                                  (~(((1U<<VDO_S_BS_FULL_INT_LEN)-1)<<VDO_S_BS_FULL_INT_POS))

/* 0x104 : vdo_int_clr */
#define VDO_INT_CLR_OFFSET                                      (0x104)
#define VDO_FRM_DONE_INT_CLR                                    VDO_FRM_DONE_INT_CLR
#define VDO_FRM_DONE_INT_CLR_POS                                (0U)
#define VDO_FRM_DONE_INT_CLR_LEN                                (1U)
#define VDO_FRM_DONE_INT_CLR_MSK                                (((1U<<VDO_FRM_DONE_INT_CLR_LEN)-1)<<VDO_FRM_DONE_INT_CLR_POS)
#define VDO_FRM_DONE_INT_CLR_UMSK                               (~(((1U<<VDO_FRM_DONE_INT_CLR_LEN)-1)<<VDO_FRM_DONE_INT_CLR_POS))
#define VDO_S_FRM_DONE_INT_CLR                                  VDO_S_FRM_DONE_INT_CLR
#define VDO_S_FRM_DONE_INT_CLR_POS                              (1U)
#define VDO_S_FRM_DONE_INT_CLR_LEN                              (1U)
#define VDO_S_FRM_DONE_INT_CLR_MSK                              (((1U<<VDO_S_FRM_DONE_INT_CLR_LEN)-1)<<VDO_S_FRM_DONE_INT_CLR_POS)
#define VDO_S_FRM_DONE_INT_CLR_UMSK                             (~(((1U<<VDO_S_FRM_DONE_INT_CLR_LEN)-1)<<VDO_S_FRM_DONE_INT_CLR_POS))
#define VDO_SEQ_DONE_INT_CLR                                    VDO_SEQ_DONE_INT_CLR
#define VDO_SEQ_DONE_INT_CLR_POS                                (4U)
#define VDO_SEQ_DONE_INT_CLR_LEN                                (1U)
#define VDO_SEQ_DONE_INT_CLR_MSK                                (((1U<<VDO_SEQ_DONE_INT_CLR_LEN)-1)<<VDO_SEQ_DONE_INT_CLR_POS)
#define VDO_SEQ_DONE_INT_CLR_UMSK                               (~(((1U<<VDO_SEQ_DONE_INT_CLR_LEN)-1)<<VDO_SEQ_DONE_INT_CLR_POS))
#define VDO_S_SEQ_DONE_INT_CLR                                  VDO_S_SEQ_DONE_INT_CLR
#define VDO_S_SEQ_DONE_INT_CLR_POS                              (5U)
#define VDO_S_SEQ_DONE_INT_CLR_LEN                              (1U)
#define VDO_S_SEQ_DONE_INT_CLR_MSK                              (((1U<<VDO_S_SEQ_DONE_INT_CLR_LEN)-1)<<VDO_S_SEQ_DONE_INT_CLR_POS)
#define VDO_S_SEQ_DONE_INT_CLR_UMSK                             (~(((1U<<VDO_S_SEQ_DONE_INT_CLR_LEN)-1)<<VDO_S_SEQ_DONE_INT_CLR_POS))
#define VDO_BS_FULL_INT_CLR                                     VDO_BS_FULL_INT_CLR
#define VDO_BS_FULL_INT_CLR_POS                                 (8U)
#define VDO_BS_FULL_INT_CLR_LEN                                 (1U)
#define VDO_BS_FULL_INT_CLR_MSK                                 (((1U<<VDO_BS_FULL_INT_CLR_LEN)-1)<<VDO_BS_FULL_INT_CLR_POS)
#define VDO_BS_FULL_INT_CLR_UMSK                                (~(((1U<<VDO_BS_FULL_INT_CLR_LEN)-1)<<VDO_BS_FULL_INT_CLR_POS))
#define VDO_S_BS_FULL_INT_CLR                                   VDO_S_BS_FULL_INT_CLR
#define VDO_S_BS_FULL_INT_CLR_POS                               (9U)
#define VDO_S_BS_FULL_INT_CLR_LEN                               (1U)
#define VDO_S_BS_FULL_INT_CLR_MSK                               (((1U<<VDO_S_BS_FULL_INT_CLR_LEN)-1)<<VDO_S_BS_FULL_INT_CLR_POS)
#define VDO_S_BS_FULL_INT_CLR_UMSK                              (~(((1U<<VDO_S_BS_FULL_INT_CLR_LEN)-1)<<VDO_S_BS_FULL_INT_CLR_POS))

/* 0x108 : vdo_int_mask */
#define VDO_INT_MASK_OFFSET                                     (0x108)
#define VDO_FRM_DONE_INT_MASK                                   VDO_FRM_DONE_INT_MASK
#define VDO_FRM_DONE_INT_MASK_POS                               (0U)
#define VDO_FRM_DONE_INT_MASK_LEN                               (1U)
#define VDO_FRM_DONE_INT_MASK_MSK                               (((1U<<VDO_FRM_DONE_INT_MASK_LEN)-1)<<VDO_FRM_DONE_INT_MASK_POS)
#define VDO_FRM_DONE_INT_MASK_UMSK                              (~(((1U<<VDO_FRM_DONE_INT_MASK_LEN)-1)<<VDO_FRM_DONE_INT_MASK_POS))
#define VDO_S_FRM_DONE_INT_MASK                                 VDO_S_FRM_DONE_INT_MASK
#define VDO_S_FRM_DONE_INT_MASK_POS                             (1U)
#define VDO_S_FRM_DONE_INT_MASK_LEN                             (1U)
#define VDO_S_FRM_DONE_INT_MASK_MSK                             (((1U<<VDO_S_FRM_DONE_INT_MASK_LEN)-1)<<VDO_S_FRM_DONE_INT_MASK_POS)
#define VDO_S_FRM_DONE_INT_MASK_UMSK                            (~(((1U<<VDO_S_FRM_DONE_INT_MASK_LEN)-1)<<VDO_S_FRM_DONE_INT_MASK_POS))
#define VDO_SEQ_DONE_INT_MASK                                   VDO_SEQ_DONE_INT_MASK
#define VDO_SEQ_DONE_INT_MASK_POS                               (4U)
#define VDO_SEQ_DONE_INT_MASK_LEN                               (1U)
#define VDO_SEQ_DONE_INT_MASK_MSK                               (((1U<<VDO_SEQ_DONE_INT_MASK_LEN)-1)<<VDO_SEQ_DONE_INT_MASK_POS)
#define VDO_SEQ_DONE_INT_MASK_UMSK                              (~(((1U<<VDO_SEQ_DONE_INT_MASK_LEN)-1)<<VDO_SEQ_DONE_INT_MASK_POS))
#define VDO_S_SEQ_DONE_INT_MASK                                 VDO_S_SEQ_DONE_INT_MASK
#define VDO_S_SEQ_DONE_INT_MASK_POS                             (5U)
#define VDO_S_SEQ_DONE_INT_MASK_LEN                             (1U)
#define VDO_S_SEQ_DONE_INT_MASK_MSK                             (((1U<<VDO_S_SEQ_DONE_INT_MASK_LEN)-1)<<VDO_S_SEQ_DONE_INT_MASK_POS)
#define VDO_S_SEQ_DONE_INT_MASK_UMSK                            (~(((1U<<VDO_S_SEQ_DONE_INT_MASK_LEN)-1)<<VDO_S_SEQ_DONE_INT_MASK_POS))
#define VDO_BS_FULL_INT_MASK                                    VDO_BS_FULL_INT_MASK
#define VDO_BS_FULL_INT_MASK_POS                                (8U)
#define VDO_BS_FULL_INT_MASK_LEN                                (1U)
#define VDO_BS_FULL_INT_MASK_MSK                                (((1U<<VDO_BS_FULL_INT_MASK_LEN)-1)<<VDO_BS_FULL_INT_MASK_POS)
#define VDO_BS_FULL_INT_MASK_UMSK                               (~(((1U<<VDO_BS_FULL_INT_MASK_LEN)-1)<<VDO_BS_FULL_INT_MASK_POS))
#define VDO_S_BS_FULL_INT_MASK                                  VDO_S_BS_FULL_INT_MASK
#define VDO_S_BS_FULL_INT_MASK_POS                              (9U)
#define VDO_S_BS_FULL_INT_MASK_LEN                              (1U)
#define VDO_S_BS_FULL_INT_MASK_MSK                              (((1U<<VDO_S_BS_FULL_INT_MASK_LEN)-1)<<VDO_S_BS_FULL_INT_MASK_POS)
#define VDO_S_BS_FULL_INT_MASK_UMSK                             (~(((1U<<VDO_S_BS_FULL_INT_MASK_LEN)-1)<<VDO_S_BS_FULL_INT_MASK_POS))

/* 0x10c : vdo_total_bytecount */
#define VDO_TOTAL_BYTECOUNT_OFFSET                              (0x10c)
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
#define VDO_M_CORE_IDLE                                         VDO_M_CORE_IDLE
#define VDO_M_CORE_IDLE_POS                                     (16U)
#define VDO_M_CORE_IDLE_LEN                                     (1U)
#define VDO_M_CORE_IDLE_MSK                                     (((1U<<VDO_M_CORE_IDLE_LEN)-1)<<VDO_M_CORE_IDLE_POS)
#define VDO_M_CORE_IDLE_UMSK                                    (~(((1U<<VDO_M_CORE_IDLE_LEN)-1)<<VDO_M_CORE_IDLE_POS))
#define VDO_S_CORE_IDLE                                         VDO_S_CORE_IDLE
#define VDO_S_CORE_IDLE_POS                                     (17U)
#define VDO_S_CORE_IDLE_LEN                                     (1U)
#define VDO_S_CORE_IDLE_MSK                                     (((1U<<VDO_S_CORE_IDLE_LEN)-1)<<VDO_S_CORE_IDLE_POS)
#define VDO_S_CORE_IDLE_UMSK                                    (~(((1U<<VDO_S_CORE_IDLE_LEN)-1)<<VDO_S_CORE_IDLE_POS))
#define VDO_SE_FSM                                              VDO_SE_FSM
#define VDO_SE_FSM_POS                                          (20U)
#define VDO_SE_FSM_LEN                                          (5U)
#define VDO_SE_FSM_MSK                                          (((1U<<VDO_SE_FSM_LEN)-1)<<VDO_SE_FSM_POS)
#define VDO_SE_FSM_UMSK                                         (~(((1U<<VDO_SE_FSM_LEN)-1)<<VDO_SE_FSM_POS))
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

/* 0x11c : vdo_ctrl_dbg */
#define VDO_CTRL_DBG_OFFSET                                     (0x11c)
#define VDO_CTRL_STATE                                          VDO_CTRL_STATE
#define VDO_CTRL_STATE_POS                                      (0U)
#define VDO_CTRL_STATE_LEN                                      (3U)
#define VDO_CTRL_STATE_MSK                                      (((1U<<VDO_CTRL_STATE_LEN)-1)<<VDO_CTRL_STATE_POS)
#define VDO_CTRL_STATE_UMSK                                     (~(((1U<<VDO_CTRL_STATE_LEN)-1)<<VDO_CTRL_STATE_POS))
#define VDO_H264_PROC                                           VDO_H264_PROC
#define VDO_H264_PROC_POS                                       (3U)
#define VDO_H264_PROC_LEN                                       (1U)
#define VDO_H264_PROC_MSK                                       (((1U<<VDO_H264_PROC_LEN)-1)<<VDO_H264_PROC_POS)
#define VDO_H264_PROC_UMSK                                      (~(((1U<<VDO_H264_PROC_LEN)-1)<<VDO_H264_PROC_POS))
#define VDO_S_CTRL_STATE                                        VDO_S_CTRL_STATE
#define VDO_S_CTRL_STATE_POS                                    (4U)
#define VDO_S_CTRL_STATE_LEN                                    (3U)
#define VDO_S_CTRL_STATE_MSK                                    (((1U<<VDO_S_CTRL_STATE_LEN)-1)<<VDO_S_CTRL_STATE_POS)
#define VDO_S_CTRL_STATE_UMSK                                   (~(((1U<<VDO_S_CTRL_STATE_LEN)-1)<<VDO_S_CTRL_STATE_POS))
#define VDO_S_H264_PROC                                         VDO_S_H264_PROC
#define VDO_S_H264_PROC_POS                                     (7U)
#define VDO_S_H264_PROC_LEN                                     (1U)
#define VDO_S_H264_PROC_MSK                                     (((1U<<VDO_S_H264_PROC_LEN)-1)<<VDO_S_H264_PROC_POS)
#define VDO_S_H264_PROC_UMSK                                    (~(((1U<<VDO_S_H264_PROC_LEN)-1)<<VDO_S_H264_PROC_POS))
#define VDO_CTRL_CE                                             VDO_CTRL_CE
#define VDO_CTRL_CE_POS                                         (8U)
#define VDO_CTRL_CE_LEN                                         (1U)
#define VDO_CTRL_CE_MSK                                         (((1U<<VDO_CTRL_CE_LEN)-1)<<VDO_CTRL_CE_POS)
#define VDO_CTRL_CE_UMSK                                        (~(((1U<<VDO_CTRL_CE_LEN)-1)<<VDO_CTRL_CE_POS))
#define VDO_STREAM_IDX                                          VDO_STREAM_IDX
#define VDO_STREAM_IDX_POS                                      (12U)
#define VDO_STREAM_IDX_LEN                                      (1U)
#define VDO_STREAM_IDX_MSK                                      (((1U<<VDO_STREAM_IDX_LEN)-1)<<VDO_STREAM_IDX_POS)
#define VDO_STREAM_IDX_UMSK                                     (~(((1U<<VDO_STREAM_IDX_LEN)-1)<<VDO_STREAM_IDX_POS))
#define VDO_CTRLER_FRM_CNT                                      VDO_CTRLER_FRM_CNT
#define VDO_CTRLER_FRM_CNT_POS                                  (16U)
#define VDO_CTRLER_FRM_CNT_LEN                                  (8U)
#define VDO_CTRLER_FRM_CNT_MSK                                  (((1U<<VDO_CTRLER_FRM_CNT_LEN)-1)<<VDO_CTRLER_FRM_CNT_POS)
#define VDO_CTRLER_FRM_CNT_UMSK                                 (~(((1U<<VDO_CTRLER_FRM_CNT_LEN)-1)<<VDO_CTRLER_FRM_CNT_POS))
#define VDO_S_CTRLER_FRM_CNT                                    VDO_S_CTRLER_FRM_CNT
#define VDO_S_CTRLER_FRM_CNT_POS                                (24U)
#define VDO_S_CTRLER_FRM_CNT_LEN                                (8U)
#define VDO_S_CTRLER_FRM_CNT_MSK                                (((1U<<VDO_S_CTRLER_FRM_CNT_LEN)-1)<<VDO_S_CTRLER_FRM_CNT_POS)
#define VDO_S_CTRLER_FRM_CNT_UMSK                               (~(((1U<<VDO_S_CTRLER_FRM_CNT_LEN)-1)<<VDO_S_CTRLER_FRM_CNT_POS))

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

/* 0x12c : vdo_checksum_3 */
#define VDO_CHECKSUM_3_OFFSET                                   (0x12c)
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

/* 0x13c : vdo_checksum_7 */
#define VDO_CHECKSUM_7_OFFSET                                   (0x13c)
#define VDO_MEM_DOUT_CHKSUM                                     VDO_MEM_DOUT_CHKSUM
#define VDO_MEM_DOUT_CHKSUM_POS                                 (0U)
#define VDO_MEM_DOUT_CHKSUM_LEN                                 (32U)
#define VDO_MEM_DOUT_CHKSUM_MSK                                 (((1U<<VDO_MEM_DOUT_CHKSUM_LEN)-1)<<VDO_MEM_DOUT_CHKSUM_POS)
#define VDO_MEM_DOUT_CHKSUM_UMSK                                (~(((1U<<VDO_MEM_DOUT_CHKSUM_LEN)-1)<<VDO_MEM_DOUT_CHKSUM_POS))

/* 0x140 : vdo_reserved */
#define VDO_RESERVED_OFFSET                                     (0x140)
#define VDO_RESERVED                                            VDO_RESERVED
#define VDO_RESERVED_POS                                        (0U)
#define VDO_RESERVED_LEN                                        (32U)
#define VDO_RESERVED_MSK                                        (((1U<<VDO_RESERVED_LEN)-1)<<VDO_RESERVED_POS)
#define VDO_RESERVED_UMSK                                       (~(((1U<<VDO_RESERVED_LEN)-1)<<VDO_RESERVED_POS))

/* 0x144 : vdo_h264_y_frame_mem_size */
#define VDO_H264_Y_FRAME_MEM_SIZE_OFFSET                        (0x144)
#define VDO_CFG_MEM_BCNT_Y                                      VDO_CFG_MEM_BCNT_Y
#define VDO_CFG_MEM_BCNT_Y_POS                                  (0U)
#define VDO_CFG_MEM_BCNT_Y_LEN                                  (32U)
#define VDO_CFG_MEM_BCNT_Y_MSK                                  (((1U<<VDO_CFG_MEM_BCNT_Y_LEN)-1)<<VDO_CFG_MEM_BCNT_Y_POS)
#define VDO_CFG_MEM_BCNT_Y_UMSK                                 (~(((1U<<VDO_CFG_MEM_BCNT_Y_LEN)-1)<<VDO_CFG_MEM_BCNT_Y_POS))

/* 0x148 : vdo_h264_uv_frame_mem_size */
#define VDO_H264_UV_FRAME_MEM_SIZE_OFFSET                       (0x148)
#define VDO_CFG_MEM_BCNT_UV                                     VDO_CFG_MEM_BCNT_UV
#define VDO_CFG_MEM_BCNT_UV_POS                                 (0U)
#define VDO_CFG_MEM_BCNT_UV_LEN                                 (32U)
#define VDO_CFG_MEM_BCNT_UV_MSK                                 (((1U<<VDO_CFG_MEM_BCNT_UV_LEN)-1)<<VDO_CFG_MEM_BCNT_UV_POS)
#define VDO_CFG_MEM_BCNT_UV_UMSK                                (~(((1U<<VDO_CFG_MEM_BCNT_UV_LEN)-1)<<VDO_CFG_MEM_BCNT_UV_POS))

/* 0x14c : vdo_h264_s_frame_size */
#define VDO_H264_S_FRAME_SIZE_OFFSET                            (0x14c)
#define VDO_CFG_S_FRAME_WIDTH                                   VDO_CFG_S_FRAME_WIDTH
#define VDO_CFG_S_FRAME_WIDTH_POS                               (0U)
#define VDO_CFG_S_FRAME_WIDTH_LEN                               (11U)
#define VDO_CFG_S_FRAME_WIDTH_MSK                               (((1U<<VDO_CFG_S_FRAME_WIDTH_LEN)-1)<<VDO_CFG_S_FRAME_WIDTH_POS)
#define VDO_CFG_S_FRAME_WIDTH_UMSK                              (~(((1U<<VDO_CFG_S_FRAME_WIDTH_LEN)-1)<<VDO_CFG_S_FRAME_WIDTH_POS))
#define VDO_CFG_S_FRAME_HEIGHT                                  VDO_CFG_S_FRAME_HEIGHT
#define VDO_CFG_S_FRAME_HEIGHT_POS                              (16U)
#define VDO_CFG_S_FRAME_HEIGHT_LEN                              (11U)
#define VDO_CFG_S_FRAME_HEIGHT_MSK                              (((1U<<VDO_CFG_S_FRAME_HEIGHT_LEN)-1)<<VDO_CFG_S_FRAME_HEIGHT_POS)
#define VDO_CFG_S_FRAME_HEIGHT_UMSK                             (~(((1U<<VDO_CFG_S_FRAME_HEIGHT_LEN)-1)<<VDO_CFG_S_FRAME_HEIGHT_POS))

/* 0x150 : vdo_h264_s_frame_base_addr_y */
#define VDO_H264_S_FRAME_BASE_ADDR_Y_OFFSET                     (0x150)
#define VDO_CFG_S_FRAME_BASE_ADDR_Y                             VDO_CFG_S_FRAME_BASE_ADDR_Y
#define VDO_CFG_S_FRAME_BASE_ADDR_Y_POS                         (0U)
#define VDO_CFG_S_FRAME_BASE_ADDR_Y_LEN                         (32U)
#define VDO_CFG_S_FRAME_BASE_ADDR_Y_MSK                         (((1U<<VDO_CFG_S_FRAME_BASE_ADDR_Y_LEN)-1)<<VDO_CFG_S_FRAME_BASE_ADDR_Y_POS)
#define VDO_CFG_S_FRAME_BASE_ADDR_Y_UMSK                        (~(((1U<<VDO_CFG_S_FRAME_BASE_ADDR_Y_LEN)-1)<<VDO_CFG_S_FRAME_BASE_ADDR_Y_POS))

/* 0x154 : vdo_h264_s_frame_base_addr_uv */
#define VDO_H264_S_FRAME_BASE_ADDR_UV_OFFSET                    (0x154)
#define VDO_CFG_S_FRAME_BASE_ADDR_UV                            VDO_CFG_S_FRAME_BASE_ADDR_UV
#define VDO_CFG_S_FRAME_BASE_ADDR_UV_POS                        (0U)
#define VDO_CFG_S_FRAME_BASE_ADDR_UV_LEN                        (32U)
#define VDO_CFG_S_FRAME_BASE_ADDR_UV_MSK                        (((1U<<VDO_CFG_S_FRAME_BASE_ADDR_UV_LEN)-1)<<VDO_CFG_S_FRAME_BASE_ADDR_UV_POS)
#define VDO_CFG_S_FRAME_BASE_ADDR_UV_UMSK                       (~(((1U<<VDO_CFG_S_FRAME_BASE_ADDR_UV_LEN)-1)<<VDO_CFG_S_FRAME_BASE_ADDR_UV_POS))

/* 0x158 : vdo_h264_s_y_frame_mem_size */
#define VDO_H264_S_Y_FRAME_MEM_SIZE_OFFSET                      (0x158)
#define VDO_CFG_S_MEM_BCNT_Y                                    VDO_CFG_S_MEM_BCNT_Y
#define VDO_CFG_S_MEM_BCNT_Y_POS                                (0U)
#define VDO_CFG_S_MEM_BCNT_Y_LEN                                (32U)
#define VDO_CFG_S_MEM_BCNT_Y_MSK                                (((1U<<VDO_CFG_S_MEM_BCNT_Y_LEN)-1)<<VDO_CFG_S_MEM_BCNT_Y_POS)
#define VDO_CFG_S_MEM_BCNT_Y_UMSK                               (~(((1U<<VDO_CFG_S_MEM_BCNT_Y_LEN)-1)<<VDO_CFG_S_MEM_BCNT_Y_POS))

/* 0x15c : vdo_h264_s_uv_frame_mem_size */
#define VDO_H264_S_UV_FRAME_MEM_SIZE_OFFSET                     (0x15c)
#define VDO_CFG_S_MEM_BCNT_UV                                   VDO_CFG_S_MEM_BCNT_UV
#define VDO_CFG_S_MEM_BCNT_UV_POS                               (0U)
#define VDO_CFG_S_MEM_BCNT_UV_LEN                               (32U)
#define VDO_CFG_S_MEM_BCNT_UV_MSK                               (((1U<<VDO_CFG_S_MEM_BCNT_UV_LEN)-1)<<VDO_CFG_S_MEM_BCNT_UV_POS)
#define VDO_CFG_S_MEM_BCNT_UV_UMSK                              (~(((1U<<VDO_CFG_S_MEM_BCNT_UV_LEN)-1)<<VDO_CFG_S_MEM_BCNT_UV_POS))

/* 0x160 : vdo_h264_s_bs_base_addr */
#define VDO_H264_S_BS_BASE_ADDR_OFFSET                          (0x160)
#define VDO_CFG_S_BS_BASE_ADDR                                  VDO_CFG_S_BS_BASE_ADDR
#define VDO_CFG_S_BS_BASE_ADDR_POS                              (0U)
#define VDO_CFG_S_BS_BASE_ADDR_LEN                              (32U)
#define VDO_CFG_S_BS_BASE_ADDR_MSK                              (((1U<<VDO_CFG_S_BS_BASE_ADDR_LEN)-1)<<VDO_CFG_S_BS_BASE_ADDR_POS)
#define VDO_CFG_S_BS_BASE_ADDR_UMSK                             (~(((1U<<VDO_CFG_S_BS_BASE_ADDR_LEN)-1)<<VDO_CFG_S_BS_BASE_ADDR_POS))

/* 0x164 : vdo_reserved2 */
#define VDO_RESERVED2_OFFSET                                    (0x164)
#define VDO_RESERVED2                                           VDO_RESERVED2
#define VDO_RESERVED2_POS                                       (0U)
#define VDO_RESERVED2_LEN                                       (32U)
#define VDO_RESERVED2_MSK                                       (((1U<<VDO_RESERVED2_LEN)-1)<<VDO_RESERVED2_POS)
#define VDO_RESERVED2_UMSK                                      (~(((1U<<VDO_RESERVED2_LEN)-1)<<VDO_RESERVED2_POS))

/* 0x168 : vdo_h264_s_bs_size */
#define VDO_H264_S_BS_SIZE_OFFSET                               (0x168)
#define VDO_CFG_S_BS_SIZE                                       VDO_CFG_S_BS_SIZE
#define VDO_CFG_S_BS_SIZE_POS                                   (0U)
#define VDO_CFG_S_BS_SIZE_LEN                                   (32U)
#define VDO_CFG_S_BS_SIZE_MSK                                   (((1U<<VDO_CFG_S_BS_SIZE_LEN)-1)<<VDO_CFG_S_BS_SIZE_POS)
#define VDO_CFG_S_BS_SIZE_UMSK                                  (~(((1U<<VDO_CFG_S_BS_SIZE_LEN)-1)<<VDO_CFG_S_BS_SIZE_POS))

/* 0x16c : vdo_h264_s_bs_full_thr */
#define VDO_H264_S_BS_FULL_THR_OFFSET                           (0x16c)
#define VDO_CFG_S_BS_FULL_THR                                   VDO_CFG_S_BS_FULL_THR
#define VDO_CFG_S_BS_FULL_THR_POS                               (0U)
#define VDO_CFG_S_BS_FULL_THR_LEN                               (32U)
#define VDO_CFG_S_BS_FULL_THR_MSK                               (((1U<<VDO_CFG_S_BS_FULL_THR_LEN)-1)<<VDO_CFG_S_BS_FULL_THR_POS)
#define VDO_CFG_S_BS_FULL_THR_UMSK                              (~(((1U<<VDO_CFG_S_BS_FULL_THR_LEN)-1)<<VDO_CFG_S_BS_FULL_THR_POS))

/* 0x170 : vdo_h264_s_src_bf_height */
#define VDO_H264_S_SRC_BF_HEIGHT_OFFSET                         (0x170)
#define VDO_CFG_S_C_SRC_BF_HEIGHT                               VDO_CFG_S_C_SRC_BF_HEIGHT
#define VDO_CFG_S_C_SRC_BF_HEIGHT_POS                           (0U)
#define VDO_CFG_S_C_SRC_BF_HEIGHT_LEN                           (15U)
#define VDO_CFG_S_C_SRC_BF_HEIGHT_MSK                           (((1U<<VDO_CFG_S_C_SRC_BF_HEIGHT_LEN)-1)<<VDO_CFG_S_C_SRC_BF_HEIGHT_POS)
#define VDO_CFG_S_C_SRC_BF_HEIGHT_UMSK                          (~(((1U<<VDO_CFG_S_C_SRC_BF_HEIGHT_LEN)-1)<<VDO_CFG_S_C_SRC_BF_HEIGHT_POS))
#define VDO_CFG_S_Y_SRC_BF_HEIGHT                               VDO_CFG_S_Y_SRC_BF_HEIGHT
#define VDO_CFG_S_Y_SRC_BF_HEIGHT_POS                           (16U)
#define VDO_CFG_S_Y_SRC_BF_HEIGHT_LEN                           (15U)
#define VDO_CFG_S_Y_SRC_BF_HEIGHT_MSK                           (((1U<<VDO_CFG_S_Y_SRC_BF_HEIGHT_LEN)-1)<<VDO_CFG_S_Y_SRC_BF_HEIGHT_POS)
#define VDO_CFG_S_Y_SRC_BF_HEIGHT_UMSK                          (~(((1U<<VDO_CFG_S_Y_SRC_BF_HEIGHT_LEN)-1)<<VDO_CFG_S_Y_SRC_BF_HEIGHT_POS))

/* 0x174 : vdo_s_padding_ctrl */
#define VDO_S_PADDING_CTRL_OFFSET                               (0x174)
#define VDO_S_Y_PADDING_PIXEL                                   VDO_S_Y_PADDING_PIXEL
#define VDO_S_Y_PADDING_PIXEL_POS                               (0U)
#define VDO_S_Y_PADDING_PIXEL_LEN                               (8U)
#define VDO_S_Y_PADDING_PIXEL_MSK                               (((1U<<VDO_S_Y_PADDING_PIXEL_LEN)-1)<<VDO_S_Y_PADDING_PIXEL_POS)
#define VDO_S_Y_PADDING_PIXEL_UMSK                              (~(((1U<<VDO_S_Y_PADDING_PIXEL_LEN)-1)<<VDO_S_Y_PADDING_PIXEL_POS))
#define VDO_S_U_PADDING_PIXEL                                   VDO_S_U_PADDING_PIXEL
#define VDO_S_U_PADDING_PIXEL_POS                               (8U)
#define VDO_S_U_PADDING_PIXEL_LEN                               (8U)
#define VDO_S_U_PADDING_PIXEL_MSK                               (((1U<<VDO_S_U_PADDING_PIXEL_LEN)-1)<<VDO_S_U_PADDING_PIXEL_POS)
#define VDO_S_U_PADDING_PIXEL_UMSK                              (~(((1U<<VDO_S_U_PADDING_PIXEL_LEN)-1)<<VDO_S_U_PADDING_PIXEL_POS))
#define VDO_S_V_PADDING_PIXEL                                   VDO_S_V_PADDING_PIXEL
#define VDO_S_V_PADDING_PIXEL_POS                               (16U)
#define VDO_S_V_PADDING_PIXEL_LEN                               (8U)
#define VDO_S_V_PADDING_PIXEL_MSK                               (((1U<<VDO_S_V_PADDING_PIXEL_LEN)-1)<<VDO_S_V_PADDING_PIXEL_POS)
#define VDO_S_V_PADDING_PIXEL_UMSK                              (~(((1U<<VDO_S_V_PADDING_PIXEL_LEN)-1)<<VDO_S_V_PADDING_PIXEL_POS))
#define VDO_S_Y_LINE_PAD                                        VDO_S_Y_LINE_PAD
#define VDO_S_Y_LINE_PAD_POS                                    (24U)
#define VDO_S_Y_LINE_PAD_LEN                                    (5U)
#define VDO_S_Y_LINE_PAD_MSK                                    (((1U<<VDO_S_Y_LINE_PAD_LEN)-1)<<VDO_S_Y_LINE_PAD_POS)
#define VDO_S_Y_LINE_PAD_UMSK                                   (~(((1U<<VDO_S_Y_LINE_PAD_LEN)-1)<<VDO_S_Y_LINE_PAD_POS))

/* 0x178 : vdo_s_total_bytecount */
#define VDO_S_TOTAL_BYTECOUNT_OFFSET                            (0x178)
#define VDO_S_BS_TOT_BYCNT                                      VDO_S_BS_TOT_BYCNT
#define VDO_S_BS_TOT_BYCNT_POS                                  (0U)
#define VDO_S_BS_TOT_BYCNT_LEN                                  (32U)
#define VDO_S_BS_TOT_BYCNT_MSK                                  (((1U<<VDO_S_BS_TOT_BYCNT_LEN)-1)<<VDO_S_BS_TOT_BYCNT_POS)
#define VDO_S_BS_TOT_BYCNT_UMSK                                 (~(((1U<<VDO_S_BS_TOT_BYCNT_LEN)-1)<<VDO_S_BS_TOT_BYCNT_POS))

/* 0x17c : vdo_s_frame_bytecount */
#define VDO_S_FRAME_BYTECOUNT_OFFSET                            (0x17c)
#define VDO_S_BS_FRM_BYCNT                                      VDO_S_BS_FRM_BYCNT
#define VDO_S_BS_FRM_BYCNT_POS                                  (0U)
#define VDO_S_BS_FRM_BYCNT_LEN                                  (32U)
#define VDO_S_BS_FRM_BYCNT_MSK                                  (((1U<<VDO_S_BS_FRM_BYCNT_LEN)-1)<<VDO_S_BS_FRM_BYCNT_POS)
#define VDO_S_BS_FRM_BYCNT_UMSK                                 (~(((1U<<VDO_S_BS_FRM_BYCNT_LEN)-1)<<VDO_S_BS_FRM_BYCNT_POS))

/* 0x180 : vdo_s_src_r_dbg */
#define VDO_S_SRC_R_DBG_OFFSET                                  (0x180)
#define VDO_S_Y_READ_MBX                                        VDO_S_Y_READ_MBX
#define VDO_S_Y_READ_MBX_POS                                    (0U)
#define VDO_S_Y_READ_MBX_LEN                                    (13U)
#define VDO_S_Y_READ_MBX_MSK                                    (((1U<<VDO_S_Y_READ_MBX_LEN)-1)<<VDO_S_Y_READ_MBX_POS)
#define VDO_S_Y_READ_MBX_UMSK                                   (~(((1U<<VDO_S_Y_READ_MBX_LEN)-1)<<VDO_S_Y_READ_MBX_POS))
#define VDO_S_UV_READ_MBX                                       VDO_S_UV_READ_MBX
#define VDO_S_UV_READ_MBX_POS                                   (16U)
#define VDO_S_UV_READ_MBX_LEN                                   (13U)
#define VDO_S_UV_READ_MBX_MSK                                   (((1U<<VDO_S_UV_READ_MBX_LEN)-1)<<VDO_S_UV_READ_MBX_POS)
#define VDO_S_UV_READ_MBX_UMSK                                  (~(((1U<<VDO_S_UV_READ_MBX_LEN)-1)<<VDO_S_UV_READ_MBX_POS))
#define VDO_S_AXI_R_IDLE                                        VDO_S_AXI_R_IDLE
#define VDO_S_AXI_R_IDLE_POS                                    (30U)
#define VDO_S_AXI_R_IDLE_LEN                                    (1U)
#define VDO_S_AXI_R_IDLE_MSK                                    (((1U<<VDO_S_AXI_R_IDLE_LEN)-1)<<VDO_S_AXI_R_IDLE_POS)
#define VDO_S_AXI_R_IDLE_UMSK                                   (~(((1U<<VDO_S_AXI_R_IDLE_LEN)-1)<<VDO_S_AXI_R_IDLE_POS))
#define VDO_S_SRC_WR_OV_RD                                      VDO_S_SRC_WR_OV_RD
#define VDO_S_SRC_WR_OV_RD_POS                                  (31U)
#define VDO_S_SRC_WR_OV_RD_LEN                                  (1U)
#define VDO_S_SRC_WR_OV_RD_MSK                                  (((1U<<VDO_S_SRC_WR_OV_RD_LEN)-1)<<VDO_S_SRC_WR_OV_RD_POS)
#define VDO_S_SRC_WR_OV_RD_UMSK                                 (~(((1U<<VDO_S_SRC_WR_OV_RD_LEN)-1)<<VDO_S_SRC_WR_OV_RD_POS))

/* 0x184 : vdo_src_sta_clr */
#define VDO_SRC_STA_CLR_OFFSET                                  (0x184)
#define VDO_SRC_UV_WOVR_CLR                                     VDO_SRC_UV_WOVR_CLR
#define VDO_SRC_UV_WOVR_CLR_POS                                 (0U)
#define VDO_SRC_UV_WOVR_CLR_LEN                                 (1U)
#define VDO_SRC_UV_WOVR_CLR_MSK                                 (((1U<<VDO_SRC_UV_WOVR_CLR_LEN)-1)<<VDO_SRC_UV_WOVR_CLR_POS)
#define VDO_SRC_UV_WOVR_CLR_UMSK                                (~(((1U<<VDO_SRC_UV_WOVR_CLR_LEN)-1)<<VDO_SRC_UV_WOVR_CLR_POS))
#define VDO_SRC_Y_WOVR_CLR                                      VDO_SRC_Y_WOVR_CLR
#define VDO_SRC_Y_WOVR_CLR_POS                                  (4U)
#define VDO_SRC_Y_WOVR_CLR_LEN                                  (1U)
#define VDO_SRC_Y_WOVR_CLR_MSK                                  (((1U<<VDO_SRC_Y_WOVR_CLR_LEN)-1)<<VDO_SRC_Y_WOVR_CLR_POS)
#define VDO_SRC_Y_WOVR_CLR_UMSK                                 (~(((1U<<VDO_SRC_Y_WOVR_CLR_LEN)-1)<<VDO_SRC_Y_WOVR_CLR_POS))
#define VDO_S_SRC_UV_WOVR_CLR                                   VDO_S_SRC_UV_WOVR_CLR
#define VDO_S_SRC_UV_WOVR_CLR_POS                               (8U)
#define VDO_S_SRC_UV_WOVR_CLR_LEN                               (1U)
#define VDO_S_SRC_UV_WOVR_CLR_MSK                               (((1U<<VDO_S_SRC_UV_WOVR_CLR_LEN)-1)<<VDO_S_SRC_UV_WOVR_CLR_POS)
#define VDO_S_SRC_UV_WOVR_CLR_UMSK                              (~(((1U<<VDO_S_SRC_UV_WOVR_CLR_LEN)-1)<<VDO_S_SRC_UV_WOVR_CLR_POS))
#define VDO_S_SRC_Y_WOVR_CLR                                    VDO_S_SRC_Y_WOVR_CLR
#define VDO_S_SRC_Y_WOVR_CLR_POS                                (12U)
#define VDO_S_SRC_Y_WOVR_CLR_LEN                                (1U)
#define VDO_S_SRC_Y_WOVR_CLR_MSK                                (((1U<<VDO_S_SRC_Y_WOVR_CLR_LEN)-1)<<VDO_S_SRC_Y_WOVR_CLR_POS)
#define VDO_S_SRC_Y_WOVR_CLR_UMSK                               (~(((1U<<VDO_S_SRC_Y_WOVR_CLR_LEN)-1)<<VDO_S_SRC_Y_WOVR_CLR_POS))

/* 0x188 : vdo_src_ctrl */
#define VDO_SRC_CTRL_OFFSET                                     (0x188)
#define VDO_FRM_BUF_NUM                                         VDO_FRM_BUF_NUM
#define VDO_FRM_BUF_NUM_POS                                     (0U)
#define VDO_FRM_BUF_NUM_LEN                                     (4U)
#define VDO_FRM_BUF_NUM_MSK                                     (((1U<<VDO_FRM_BUF_NUM_LEN)-1)<<VDO_FRM_BUF_NUM_POS)
#define VDO_FRM_BUF_NUM_UMSK                                    (~(((1U<<VDO_FRM_BUF_NUM_LEN)-1)<<VDO_FRM_BUF_NUM_POS))
#define VDO_MFRM_BUF_EN                                         VDO_MFRM_BUF_EN
#define VDO_MFRM_BUF_EN_POS                                     (4U)
#define VDO_MFRM_BUF_EN_LEN                                     (1U)
#define VDO_MFRM_BUF_EN_MSK                                     (((1U<<VDO_MFRM_BUF_EN_LEN)-1)<<VDO_MFRM_BUF_EN_POS)
#define VDO_MFRM_BUF_EN_UMSK                                    (~(((1U<<VDO_MFRM_BUF_EN_LEN)-1)<<VDO_MFRM_BUF_EN_POS))
#define VDO_REQ_PERIOD                                          VDO_REQ_PERIOD
#define VDO_REQ_PERIOD_POS                                      (5U)
#define VDO_REQ_PERIOD_LEN                                      (10U)
#define VDO_REQ_PERIOD_MSK                                      (((1U<<VDO_REQ_PERIOD_LEN)-1)<<VDO_REQ_PERIOD_POS)
#define VDO_REQ_PERIOD_UMSK                                     (~(((1U<<VDO_REQ_PERIOD_LEN)-1)<<VDO_REQ_PERIOD_POS))
#define VDO_NO_WAIT_1ST_VSYNC                                   VDO_NO_WAIT_1ST_VSYNC
#define VDO_NO_WAIT_1ST_VSYNC_POS                               (15U)
#define VDO_NO_WAIT_1ST_VSYNC_LEN                               (1U)
#define VDO_NO_WAIT_1ST_VSYNC_MSK                               (((1U<<VDO_NO_WAIT_1ST_VSYNC_LEN)-1)<<VDO_NO_WAIT_1ST_VSYNC_POS)
#define VDO_NO_WAIT_1ST_VSYNC_UMSK                              (~(((1U<<VDO_NO_WAIT_1ST_VSYNC_LEN)-1)<<VDO_NO_WAIT_1ST_VSYNC_POS))
#define VDO_S_FRM_BUF_NUM                                       VDO_S_FRM_BUF_NUM
#define VDO_S_FRM_BUF_NUM_POS                                   (16U)
#define VDO_S_FRM_BUF_NUM_LEN                                   (4U)
#define VDO_S_FRM_BUF_NUM_MSK                                   (((1U<<VDO_S_FRM_BUF_NUM_LEN)-1)<<VDO_S_FRM_BUF_NUM_POS)
#define VDO_S_FRM_BUF_NUM_UMSK                                  (~(((1U<<VDO_S_FRM_BUF_NUM_LEN)-1)<<VDO_S_FRM_BUF_NUM_POS))
#define VDO_S_MFRM_BUF_EN                                       VDO_S_MFRM_BUF_EN
#define VDO_S_MFRM_BUF_EN_POS                                   (20U)
#define VDO_S_MFRM_BUF_EN_LEN                                   (1U)
#define VDO_S_MFRM_BUF_EN_MSK                                   (((1U<<VDO_S_MFRM_BUF_EN_LEN)-1)<<VDO_S_MFRM_BUF_EN_POS)
#define VDO_S_MFRM_BUF_EN_UMSK                                  (~(((1U<<VDO_S_MFRM_BUF_EN_LEN)-1)<<VDO_S_MFRM_BUF_EN_POS))
#define VDO_S_REQ_PERIOD                                        VDO_S_REQ_PERIOD
#define VDO_S_REQ_PERIOD_POS                                    (21U)
#define VDO_S_REQ_PERIOD_LEN                                    (10U)
#define VDO_S_REQ_PERIOD_MSK                                    (((1U<<VDO_S_REQ_PERIOD_LEN)-1)<<VDO_S_REQ_PERIOD_POS)
#define VDO_S_REQ_PERIOD_UMSK                                   (~(((1U<<VDO_S_REQ_PERIOD_LEN)-1)<<VDO_S_REQ_PERIOD_POS))
#define VDO_S_NO_WAIT_1ST_VSYNC                                 VDO_S_NO_WAIT_1ST_VSYNC
#define VDO_S_NO_WAIT_1ST_VSYNC_POS                             (31U)
#define VDO_S_NO_WAIT_1ST_VSYNC_LEN                             (1U)
#define VDO_S_NO_WAIT_1ST_VSYNC_MSK                             (((1U<<VDO_S_NO_WAIT_1ST_VSYNC_LEN)-1)<<VDO_S_NO_WAIT_1ST_VSYNC_POS)
#define VDO_S_NO_WAIT_1ST_VSYNC_UMSK                            (~(((1U<<VDO_S_NO_WAIT_1ST_VSYNC_LEN)-1)<<VDO_S_NO_WAIT_1ST_VSYNC_POS))

/* 0x18c : vdo_h264_refy0_base_addr */
#define VDO_H264_REFY0_BASE_ADDR_OFFSET                         (0x18c)
#define VDO_CFG_REFY0_BASE_ADDR                                 VDO_CFG_REFY0_BASE_ADDR
#define VDO_CFG_REFY0_BASE_ADDR_POS                             (0U)
#define VDO_CFG_REFY0_BASE_ADDR_LEN                             (32U)
#define VDO_CFG_REFY0_BASE_ADDR_MSK                             (((1U<<VDO_CFG_REFY0_BASE_ADDR_LEN)-1)<<VDO_CFG_REFY0_BASE_ADDR_POS)
#define VDO_CFG_REFY0_BASE_ADDR_UMSK                            (~(((1U<<VDO_CFG_REFY0_BASE_ADDR_LEN)-1)<<VDO_CFG_REFY0_BASE_ADDR_POS))

/* 0x190 : vdo_h264_refu0_base_addr */
#define VDO_H264_REFU0_BASE_ADDR_OFFSET                         (0x190)
#define VDO_CFG_REFU0_BASE_ADDR                                 VDO_CFG_REFU0_BASE_ADDR
#define VDO_CFG_REFU0_BASE_ADDR_POS                             (0U)
#define VDO_CFG_REFU0_BASE_ADDR_LEN                             (32U)
#define VDO_CFG_REFU0_BASE_ADDR_MSK                             (((1U<<VDO_CFG_REFU0_BASE_ADDR_LEN)-1)<<VDO_CFG_REFU0_BASE_ADDR_POS)
#define VDO_CFG_REFU0_BASE_ADDR_UMSK                            (~(((1U<<VDO_CFG_REFU0_BASE_ADDR_LEN)-1)<<VDO_CFG_REFU0_BASE_ADDR_POS))

/* 0x194 : vdo_h264_refv0_base_addr */
#define VDO_H264_REFV0_BASE_ADDR_OFFSET                         (0x194)
#define VDO_CFG_REFV0_BASE_ADDR                                 VDO_CFG_REFV0_BASE_ADDR
#define VDO_CFG_REFV0_BASE_ADDR_POS                             (0U)
#define VDO_CFG_REFV0_BASE_ADDR_LEN                             (32U)
#define VDO_CFG_REFV0_BASE_ADDR_MSK                             (((1U<<VDO_CFG_REFV0_BASE_ADDR_LEN)-1)<<VDO_CFG_REFV0_BASE_ADDR_POS)
#define VDO_CFG_REFV0_BASE_ADDR_UMSK                            (~(((1U<<VDO_CFG_REFV0_BASE_ADDR_LEN)-1)<<VDO_CFG_REFV0_BASE_ADDR_POS))

/* 0x198 : vdo_h264_refy1_base_addr */
#define VDO_H264_REFY1_BASE_ADDR_OFFSET                         (0x198)
#define VDO_CFG_REFY1_BASE_ADDR                                 VDO_CFG_REFY1_BASE_ADDR
#define VDO_CFG_REFY1_BASE_ADDR_POS                             (0U)
#define VDO_CFG_REFY1_BASE_ADDR_LEN                             (32U)
#define VDO_CFG_REFY1_BASE_ADDR_MSK                             (((1U<<VDO_CFG_REFY1_BASE_ADDR_LEN)-1)<<VDO_CFG_REFY1_BASE_ADDR_POS)
#define VDO_CFG_REFY1_BASE_ADDR_UMSK                            (~(((1U<<VDO_CFG_REFY1_BASE_ADDR_LEN)-1)<<VDO_CFG_REFY1_BASE_ADDR_POS))

/* 0x19c : vdo_h264_refu1_base_addr */
#define VDO_H264_REFU1_BASE_ADDR_OFFSET                         (0x19c)
#define VDO_CFG_REFU1_BASE_ADDR                                 VDO_CFG_REFU1_BASE_ADDR
#define VDO_CFG_REFU1_BASE_ADDR_POS                             (0U)
#define VDO_CFG_REFU1_BASE_ADDR_LEN                             (32U)
#define VDO_CFG_REFU1_BASE_ADDR_MSK                             (((1U<<VDO_CFG_REFU1_BASE_ADDR_LEN)-1)<<VDO_CFG_REFU1_BASE_ADDR_POS)
#define VDO_CFG_REFU1_BASE_ADDR_UMSK                            (~(((1U<<VDO_CFG_REFU1_BASE_ADDR_LEN)-1)<<VDO_CFG_REFU1_BASE_ADDR_POS))

/* 0x1a0 : vdo_h264_refv1_base_addr */
#define VDO_H264_REFV1_BASE_ADDR_OFFSET                         (0x1a0)
#define VDO_CFG_REFV1_BASE_ADDR                                 VDO_CFG_REFV1_BASE_ADDR
#define VDO_CFG_REFV1_BASE_ADDR_POS                             (0U)
#define VDO_CFG_REFV1_BASE_ADDR_LEN                             (32U)
#define VDO_CFG_REFV1_BASE_ADDR_MSK                             (((1U<<VDO_CFG_REFV1_BASE_ADDR_LEN)-1)<<VDO_CFG_REFV1_BASE_ADDR_POS)
#define VDO_CFG_REFV1_BASE_ADDR_UMSK                            (~(((1U<<VDO_CFG_REFV1_BASE_ADDR_LEN)-1)<<VDO_CFG_REFV1_BASE_ADDR_POS))

/* 0x1a4 : vdo_h264_ext_base_addr */
#define VDO_H264_EXT_BASE_ADDR_OFFSET                           (0x1a4)
#define VDO_CFG_EXT_BASE_ADDR                                   VDO_CFG_EXT_BASE_ADDR
#define VDO_CFG_EXT_BASE_ADDR_POS                               (0U)
#define VDO_CFG_EXT_BASE_ADDR_LEN                               (32U)
#define VDO_CFG_EXT_BASE_ADDR_MSK                               (((1U<<VDO_CFG_EXT_BASE_ADDR_LEN)-1)<<VDO_CFG_EXT_BASE_ADDR_POS)
#define VDO_CFG_EXT_BASE_ADDR_UMSK                              (~(((1U<<VDO_CFG_EXT_BASE_ADDR_LEN)-1)<<VDO_CFG_EXT_BASE_ADDR_POS))

/* 0x1a8 : vdo_h264_s_refy0_base_addr */
#define VDO_H264_S_REFY0_BASE_ADDR_OFFSET                       (0x1a8)
#define VDO_CFG_S_REFY0_BASE_ADDR                               VDO_CFG_S_REFY0_BASE_ADDR
#define VDO_CFG_S_REFY0_BASE_ADDR_POS                           (0U)
#define VDO_CFG_S_REFY0_BASE_ADDR_LEN                           (32U)
#define VDO_CFG_S_REFY0_BASE_ADDR_MSK                           (((1U<<VDO_CFG_S_REFY0_BASE_ADDR_LEN)-1)<<VDO_CFG_S_REFY0_BASE_ADDR_POS)
#define VDO_CFG_S_REFY0_BASE_ADDR_UMSK                          (~(((1U<<VDO_CFG_S_REFY0_BASE_ADDR_LEN)-1)<<VDO_CFG_S_REFY0_BASE_ADDR_POS))

/* 0x1ac : vdo_h264_s_refu0_base_addr */
#define VDO_H264_S_REFU0_BASE_ADDR_OFFSET                       (0x1ac)
#define VDO_CFG_S_REFU0_BASE_ADDR                               VDO_CFG_S_REFU0_BASE_ADDR
#define VDO_CFG_S_REFU0_BASE_ADDR_POS                           (0U)
#define VDO_CFG_S_REFU0_BASE_ADDR_LEN                           (32U)
#define VDO_CFG_S_REFU0_BASE_ADDR_MSK                           (((1U<<VDO_CFG_S_REFU0_BASE_ADDR_LEN)-1)<<VDO_CFG_S_REFU0_BASE_ADDR_POS)
#define VDO_CFG_S_REFU0_BASE_ADDR_UMSK                          (~(((1U<<VDO_CFG_S_REFU0_BASE_ADDR_LEN)-1)<<VDO_CFG_S_REFU0_BASE_ADDR_POS))

/* 0x1b0 : vdo_h264_s_refv0_base_addr */
#define VDO_H264_S_REFV0_BASE_ADDR_OFFSET                       (0x1b0)
#define VDO_CFG_S_REFV0_BASE_ADDR                               VDO_CFG_S_REFV0_BASE_ADDR
#define VDO_CFG_S_REFV0_BASE_ADDR_POS                           (0U)
#define VDO_CFG_S_REFV0_BASE_ADDR_LEN                           (32U)
#define VDO_CFG_S_REFV0_BASE_ADDR_MSK                           (((1U<<VDO_CFG_S_REFV0_BASE_ADDR_LEN)-1)<<VDO_CFG_S_REFV0_BASE_ADDR_POS)
#define VDO_CFG_S_REFV0_BASE_ADDR_UMSK                          (~(((1U<<VDO_CFG_S_REFV0_BASE_ADDR_LEN)-1)<<VDO_CFG_S_REFV0_BASE_ADDR_POS))

/* 0x1b4 : vdo_h264_s_refy1_base_addr */
#define VDO_H264_S_REFY1_BASE_ADDR_OFFSET                       (0x1b4)
#define VDO_CFG_S_REFY1_BASE_ADDR                               VDO_CFG_S_REFY1_BASE_ADDR
#define VDO_CFG_S_REFY1_BASE_ADDR_POS                           (0U)
#define VDO_CFG_S_REFY1_BASE_ADDR_LEN                           (32U)
#define VDO_CFG_S_REFY1_BASE_ADDR_MSK                           (((1U<<VDO_CFG_S_REFY1_BASE_ADDR_LEN)-1)<<VDO_CFG_S_REFY1_BASE_ADDR_POS)
#define VDO_CFG_S_REFY1_BASE_ADDR_UMSK                          (~(((1U<<VDO_CFG_S_REFY1_BASE_ADDR_LEN)-1)<<VDO_CFG_S_REFY1_BASE_ADDR_POS))

/* 0x1b8 : vdo_h264_s_refu1_base_addr */
#define VDO_H264_S_REFU1_BASE_ADDR_OFFSET                       (0x1b8)
#define VDO_CFG_S_REFU1_BASE_ADDR                               VDO_CFG_S_REFU1_BASE_ADDR
#define VDO_CFG_S_REFU1_BASE_ADDR_POS                           (0U)
#define VDO_CFG_S_REFU1_BASE_ADDR_LEN                           (32U)
#define VDO_CFG_S_REFU1_BASE_ADDR_MSK                           (((1U<<VDO_CFG_S_REFU1_BASE_ADDR_LEN)-1)<<VDO_CFG_S_REFU1_BASE_ADDR_POS)
#define VDO_CFG_S_REFU1_BASE_ADDR_UMSK                          (~(((1U<<VDO_CFG_S_REFU1_BASE_ADDR_LEN)-1)<<VDO_CFG_S_REFU1_BASE_ADDR_POS))

/* 0x1bc : vdo_h264_s_refv1_base_addr */
#define VDO_H264_S_REFV1_BASE_ADDR_OFFSET                       (0x1bc)
#define VDO_CFG_S_REFV1_BASE_ADDR                               VDO_CFG_S_REFV1_BASE_ADDR
#define VDO_CFG_S_REFV1_BASE_ADDR_POS                           (0U)
#define VDO_CFG_S_REFV1_BASE_ADDR_LEN                           (32U)
#define VDO_CFG_S_REFV1_BASE_ADDR_MSK                           (((1U<<VDO_CFG_S_REFV1_BASE_ADDR_LEN)-1)<<VDO_CFG_S_REFV1_BASE_ADDR_POS)
#define VDO_CFG_S_REFV1_BASE_ADDR_UMSK                          (~(((1U<<VDO_CFG_S_REFV1_BASE_ADDR_LEN)-1)<<VDO_CFG_S_REFV1_BASE_ADDR_POS))

/* 0x1c0 : vdo_h264_s_ext_base_addr */
#define VDO_H264_S_EXT_BASE_ADDR_OFFSET                         (0x1c0)
#define VDO_CFG_S_EXT_BASE_ADDR                                 VDO_CFG_S_EXT_BASE_ADDR
#define VDO_CFG_S_EXT_BASE_ADDR_POS                             (0U)
#define VDO_CFG_S_EXT_BASE_ADDR_LEN                             (32U)
#define VDO_CFG_S_EXT_BASE_ADDR_MSK                             (((1U<<VDO_CFG_S_EXT_BASE_ADDR_LEN)-1)<<VDO_CFG_S_EXT_BASE_ADDR_POS)
#define VDO_CFG_S_EXT_BASE_ADDR_UMSK                            (~(((1U<<VDO_CFG_S_EXT_BASE_ADDR_LEN)-1)<<VDO_CFG_S_EXT_BASE_ADDR_POS))

/* 0x1c4 : vdo_core_dbg2 */
#define VDO_CORE_DBG2_OFFSET                                    (0x1c4)
#define VDO_PFRAME                                              VDO_PFRAME
#define VDO_PFRAME_POS                                          (0U)
#define VDO_PFRAME_LEN                                          (1U)
#define VDO_PFRAME_MSK                                          (((1U<<VDO_PFRAME_LEN)-1)<<VDO_PFRAME_POS)
#define VDO_PFRAME_UMSK                                         (~(((1U<<VDO_PFRAME_LEN)-1)<<VDO_PFRAME_POS))
#define VDO_PFRAME_CNT                                          VDO_PFRAME_CNT
#define VDO_PFRAME_CNT_POS                                      (4U)
#define VDO_PFRAME_CNT_LEN                                      (10U)
#define VDO_PFRAME_CNT_MSK                                      (((1U<<VDO_PFRAME_CNT_LEN)-1)<<VDO_PFRAME_CNT_POS)
#define VDO_PFRAME_CNT_UMSK                                     (~(((1U<<VDO_PFRAME_CNT_LEN)-1)<<VDO_PFRAME_CNT_POS))
#define VDO_TCLOCK                                              VDO_TCLOCK
#define VDO_TCLOCK_POS                                          (16U)
#define VDO_TCLOCK_LEN                                          (10U)
#define VDO_TCLOCK_MSK                                          (((1U<<VDO_TCLOCK_LEN)-1)<<VDO_TCLOCK_POS)
#define VDO_TCLOCK_UMSK                                         (~(((1U<<VDO_TCLOCK_LEN)-1)<<VDO_TCLOCK_POS))
#define VDO_R_YREF_WAIT                                         VDO_R_YREF_WAIT
#define VDO_R_YREF_WAIT_POS                                     (26U)
#define VDO_R_YREF_WAIT_LEN                                     (1U)
#define VDO_R_YREF_WAIT_MSK                                     (((1U<<VDO_R_YREF_WAIT_LEN)-1)<<VDO_R_YREF_WAIT_POS)
#define VDO_R_YREF_WAIT_UMSK                                    (~(((1U<<VDO_R_YREF_WAIT_LEN)-1)<<VDO_R_YREF_WAIT_POS))
#define VDO_R_VREF_WAIT                                         VDO_R_VREF_WAIT
#define VDO_R_VREF_WAIT_POS                                     (27U)
#define VDO_R_VREF_WAIT_LEN                                     (1U)
#define VDO_R_VREF_WAIT_MSK                                     (((1U<<VDO_R_VREF_WAIT_LEN)-1)<<VDO_R_VREF_WAIT_POS)
#define VDO_R_VREF_WAIT_UMSK                                    (~(((1U<<VDO_R_VREF_WAIT_LEN)-1)<<VDO_R_VREF_WAIT_POS))
#define VDO_W_YREC_WAIT                                         VDO_W_YREC_WAIT
#define VDO_W_YREC_WAIT_POS                                     (28U)
#define VDO_W_YREC_WAIT_LEN                                     (1U)
#define VDO_W_YREC_WAIT_MSK                                     (((1U<<VDO_W_YREC_WAIT_LEN)-1)<<VDO_W_YREC_WAIT_POS)
#define VDO_W_YREC_WAIT_UMSK                                    (~(((1U<<VDO_W_YREC_WAIT_LEN)-1)<<VDO_W_YREC_WAIT_POS))
#define VDO_PFCH_VBUF_WAIT                                      VDO_PFCH_VBUF_WAIT
#define VDO_PFCH_VBUF_WAIT_POS                                  (29U)
#define VDO_PFCH_VBUF_WAIT_LEN                                  (1U)
#define VDO_PFCH_VBUF_WAIT_MSK                                  (((1U<<VDO_PFCH_VBUF_WAIT_LEN)-1)<<VDO_PFCH_VBUF_WAIT_POS)
#define VDO_PFCH_VBUF_WAIT_UMSK                                 (~(((1U<<VDO_PFCH_VBUF_WAIT_LEN)-1)<<VDO_PFCH_VBUF_WAIT_POS))
#define VDO_CABAC_WAIT                                          VDO_CABAC_WAIT
#define VDO_CABAC_WAIT_POS                                      (30U)
#define VDO_CABAC_WAIT_LEN                                      (1U)
#define VDO_CABAC_WAIT_MSK                                      (((1U<<VDO_CABAC_WAIT_LEN)-1)<<VDO_CABAC_WAIT_POS)
#define VDO_CABAC_WAIT_UMSK                                     (~(((1U<<VDO_CABAC_WAIT_LEN)-1)<<VDO_CABAC_WAIT_POS))
#define VDO_ENC_BUSY                                            VDO_ENC_BUSY
#define VDO_ENC_BUSY_POS                                        (31U)
#define VDO_ENC_BUSY_LEN                                        (1U)
#define VDO_ENC_BUSY_MSK                                        (((1U<<VDO_ENC_BUSY_LEN)-1)<<VDO_ENC_BUSY_POS)
#define VDO_ENC_BUSY_UMSK                                       (~(((1U<<VDO_ENC_BUSY_LEN)-1)<<VDO_ENC_BUSY_POS))

/* 0x1c8 : vdo_s_core_dbg2 */
#define VDO_S_CORE_DBG2_OFFSET                                  (0x1c8)
#define VDO_S_PFRAME                                            VDO_S_PFRAME
#define VDO_S_PFRAME_POS                                        (0U)
#define VDO_S_PFRAME_LEN                                        (1U)
#define VDO_S_PFRAME_MSK                                        (((1U<<VDO_S_PFRAME_LEN)-1)<<VDO_S_PFRAME_POS)
#define VDO_S_PFRAME_UMSK                                       (~(((1U<<VDO_S_PFRAME_LEN)-1)<<VDO_S_PFRAME_POS))
#define VDO_S_PFRAME_CNT                                        VDO_S_PFRAME_CNT
#define VDO_S_PFRAME_CNT_POS                                    (4U)
#define VDO_S_PFRAME_CNT_LEN                                    (10U)
#define VDO_S_PFRAME_CNT_MSK                                    (((1U<<VDO_S_PFRAME_CNT_LEN)-1)<<VDO_S_PFRAME_CNT_POS)
#define VDO_S_PFRAME_CNT_UMSK                                   (~(((1U<<VDO_S_PFRAME_CNT_LEN)-1)<<VDO_S_PFRAME_CNT_POS))
#define VDO_S_TCLOCK                                            VDO_S_TCLOCK
#define VDO_S_TCLOCK_POS                                        (16U)
#define VDO_S_TCLOCK_LEN                                        (10U)
#define VDO_S_TCLOCK_MSK                                        (((1U<<VDO_S_TCLOCK_LEN)-1)<<VDO_S_TCLOCK_POS)
#define VDO_S_TCLOCK_UMSK                                       (~(((1U<<VDO_S_TCLOCK_LEN)-1)<<VDO_S_TCLOCK_POS))
#define VDO_S_R_YREF_WAIT                                       VDO_S_R_YREF_WAIT
#define VDO_S_R_YREF_WAIT_POS                                   (26U)
#define VDO_S_R_YREF_WAIT_LEN                                   (1U)
#define VDO_S_R_YREF_WAIT_MSK                                   (((1U<<VDO_S_R_YREF_WAIT_LEN)-1)<<VDO_S_R_YREF_WAIT_POS)
#define VDO_S_R_YREF_WAIT_UMSK                                  (~(((1U<<VDO_S_R_YREF_WAIT_LEN)-1)<<VDO_S_R_YREF_WAIT_POS))
#define VDO_S_R_VREF_WAIT                                       VDO_S_R_VREF_WAIT
#define VDO_S_R_VREF_WAIT_POS                                   (27U)
#define VDO_S_R_VREF_WAIT_LEN                                   (1U)
#define VDO_S_R_VREF_WAIT_MSK                                   (((1U<<VDO_S_R_VREF_WAIT_LEN)-1)<<VDO_S_R_VREF_WAIT_POS)
#define VDO_S_R_VREF_WAIT_UMSK                                  (~(((1U<<VDO_S_R_VREF_WAIT_LEN)-1)<<VDO_S_R_VREF_WAIT_POS))
#define VDO_S_W_YREC_WAIT                                       VDO_S_W_YREC_WAIT
#define VDO_S_W_YREC_WAIT_POS                                   (28U)
#define VDO_S_W_YREC_WAIT_LEN                                   (1U)
#define VDO_S_W_YREC_WAIT_MSK                                   (((1U<<VDO_S_W_YREC_WAIT_LEN)-1)<<VDO_S_W_YREC_WAIT_POS)
#define VDO_S_W_YREC_WAIT_UMSK                                  (~(((1U<<VDO_S_W_YREC_WAIT_LEN)-1)<<VDO_S_W_YREC_WAIT_POS))
#define VDO_S_PFCH_VBUF_WAIT                                    VDO_S_PFCH_VBUF_WAIT
#define VDO_S_PFCH_VBUF_WAIT_POS                                (29U)
#define VDO_S_PFCH_VBUF_WAIT_LEN                                (1U)
#define VDO_S_PFCH_VBUF_WAIT_MSK                                (((1U<<VDO_S_PFCH_VBUF_WAIT_LEN)-1)<<VDO_S_PFCH_VBUF_WAIT_POS)
#define VDO_S_PFCH_VBUF_WAIT_UMSK                               (~(((1U<<VDO_S_PFCH_VBUF_WAIT_LEN)-1)<<VDO_S_PFCH_VBUF_WAIT_POS))
#define VDO_S_CABAC_WAIT                                        VDO_S_CABAC_WAIT
#define VDO_S_CABAC_WAIT_POS                                    (30U)
#define VDO_S_CABAC_WAIT_LEN                                    (1U)
#define VDO_S_CABAC_WAIT_MSK                                    (((1U<<VDO_S_CABAC_WAIT_LEN)-1)<<VDO_S_CABAC_WAIT_POS)
#define VDO_S_CABAC_WAIT_UMSK                                   (~(((1U<<VDO_S_CABAC_WAIT_LEN)-1)<<VDO_S_CABAC_WAIT_POS))
#define VDO_S_ENC_BUSY                                          VDO_S_ENC_BUSY
#define VDO_S_ENC_BUSY_POS                                      (31U)
#define VDO_S_ENC_BUSY_LEN                                      (1U)
#define VDO_S_ENC_BUSY_MSK                                      (((1U<<VDO_S_ENC_BUSY_LEN)-1)<<VDO_S_ENC_BUSY_POS)
#define VDO_S_ENC_BUSY_UMSK                                     (~(((1U<<VDO_S_ENC_BUSY_LEN)-1)<<VDO_S_ENC_BUSY_POS))

/* 0x1cc : vdo_h264_y_srcbf_size */
#define VDO_H264_Y_SRCBF_SIZE_OFFSET                            (0x1cc)
#define VDO_CFG_Y_SRCBF_BYCNT                                   VDO_CFG_Y_SRCBF_BYCNT
#define VDO_CFG_Y_SRCBF_BYCNT_POS                               (0U)
#define VDO_CFG_Y_SRCBF_BYCNT_LEN                               (32U)
#define VDO_CFG_Y_SRCBF_BYCNT_MSK                               (((1U<<VDO_CFG_Y_SRCBF_BYCNT_LEN)-1)<<VDO_CFG_Y_SRCBF_BYCNT_POS)
#define VDO_CFG_Y_SRCBF_BYCNT_UMSK                              (~(((1U<<VDO_CFG_Y_SRCBF_BYCNT_LEN)-1)<<VDO_CFG_Y_SRCBF_BYCNT_POS))

/* 0x1d0 : vdo_h264_uv_srcbf_size */
#define VDO_H264_UV_SRCBF_SIZE_OFFSET                           (0x1d0)
#define VDO_CFG_UV_SRCBF_BYCNT                                  VDO_CFG_UV_SRCBF_BYCNT
#define VDO_CFG_UV_SRCBF_BYCNT_POS                              (0U)
#define VDO_CFG_UV_SRCBF_BYCNT_LEN                              (32U)
#define VDO_CFG_UV_SRCBF_BYCNT_MSK                              (((1U<<VDO_CFG_UV_SRCBF_BYCNT_LEN)-1)<<VDO_CFG_UV_SRCBF_BYCNT_POS)
#define VDO_CFG_UV_SRCBF_BYCNT_UMSK                             (~(((1U<<VDO_CFG_UV_SRCBF_BYCNT_LEN)-1)<<VDO_CFG_UV_SRCBF_BYCNT_POS))

/* 0x1d4 : vdo_h264_s_y_srcbf_size */
#define VDO_H264_S_Y_SRCBF_SIZE_OFFSET                          (0x1d4)
#define VDO_CFG_S_Y_SRCBF_BYCNT                                 VDO_CFG_S_Y_SRCBF_BYCNT
#define VDO_CFG_S_Y_SRCBF_BYCNT_POS                             (0U)
#define VDO_CFG_S_Y_SRCBF_BYCNT_LEN                             (32U)
#define VDO_CFG_S_Y_SRCBF_BYCNT_MSK                             (((1U<<VDO_CFG_S_Y_SRCBF_BYCNT_LEN)-1)<<VDO_CFG_S_Y_SRCBF_BYCNT_POS)
#define VDO_CFG_S_Y_SRCBF_BYCNT_UMSK                            (~(((1U<<VDO_CFG_S_Y_SRCBF_BYCNT_LEN)-1)<<VDO_CFG_S_Y_SRCBF_BYCNT_POS))

/* 0x1d8 : vdo_h264_s_uv_srcbf_size */
#define VDO_H264_S_UV_SRCBF_SIZE_OFFSET                         (0x1d8)
#define VDO_CFG_S_UV_SRCBF_BYCNT                                VDO_CFG_S_UV_SRCBF_BYCNT
#define VDO_CFG_S_UV_SRCBF_BYCNT_POS                            (0U)
#define VDO_CFG_S_UV_SRCBF_BYCNT_LEN                            (32U)
#define VDO_CFG_S_UV_SRCBF_BYCNT_MSK                            (((1U<<VDO_CFG_S_UV_SRCBF_BYCNT_LEN)-1)<<VDO_CFG_S_UV_SRCBF_BYCNT_POS)
#define VDO_CFG_S_UV_SRCBF_BYCNT_UMSK                           (~(((1U<<VDO_CFG_S_UV_SRCBF_BYCNT_LEN)-1)<<VDO_CFG_S_UV_SRCBF_BYCNT_POS))

/* 0x1dc : vdo_h264_src_dbg */
#define VDO_H264_SRC_DBG_OFFSET                                 (0x1dc)
#define VDO_D2B_SYNC_EN                                         VDO_D2B_SYNC_EN
#define VDO_D2B_SYNC_EN_POS                                     (0U)
#define VDO_D2B_SYNC_EN_LEN                                     (1U)
#define VDO_D2B_SYNC_EN_MSK                                     (((1U<<VDO_D2B_SYNC_EN_LEN)-1)<<VDO_D2B_SYNC_EN_POS)
#define VDO_D2B_SYNC_EN_UMSK                                    (~(((1U<<VDO_D2B_SYNC_EN_LEN)-1)<<VDO_D2B_SYNC_EN_POS))
#define VDO_OLD_READ_MODE                                       VDO_OLD_READ_MODE
#define VDO_OLD_READ_MODE_POS                                   (4U)
#define VDO_OLD_READ_MODE_LEN                                   (5U)
#define VDO_OLD_READ_MODE_MSK                                   (((1U<<VDO_OLD_READ_MODE_LEN)-1)<<VDO_OLD_READ_MODE_POS)
#define VDO_OLD_READ_MODE_UMSK                                  (~(((1U<<VDO_OLD_READ_MODE_LEN)-1)<<VDO_OLD_READ_MODE_POS))
#define VDO_S_D2B_SYNC_EN                                       VDO_S_D2B_SYNC_EN
#define VDO_S_D2B_SYNC_EN_POS                                   (16U)
#define VDO_S_D2B_SYNC_EN_LEN                                   (1U)
#define VDO_S_D2B_SYNC_EN_MSK                                   (((1U<<VDO_S_D2B_SYNC_EN_LEN)-1)<<VDO_S_D2B_SYNC_EN_POS)
#define VDO_S_D2B_SYNC_EN_UMSK                                  (~(((1U<<VDO_S_D2B_SYNC_EN_LEN)-1)<<VDO_S_D2B_SYNC_EN_POS))
#define VDO_S_OLD_READ_MODE                                     VDO_S_OLD_READ_MODE
#define VDO_S_OLD_READ_MODE_POS                                 (20U)
#define VDO_S_OLD_READ_MODE_LEN                                 (5U)
#define VDO_S_OLD_READ_MODE_MSK                                 (((1U<<VDO_S_OLD_READ_MODE_LEN)-1)<<VDO_S_OLD_READ_MODE_POS)
#define VDO_S_OLD_READ_MODE_UMSK                                (~(((1U<<VDO_S_OLD_READ_MODE_LEN)-1)<<VDO_S_OLD_READ_MODE_POS))

/* 0x1e0 : vdo_h264_yy_d2b_addr */
#define VDO_H264_YY_D2B_ADDR_OFFSET                             (0x1e0)
#define VDO_YY_D2B_ADDR_DBG                                     VDO_YY_D2B_ADDR_DBG
#define VDO_YY_D2B_ADDR_DBG_POS                                 (0U)
#define VDO_YY_D2B_ADDR_DBG_LEN                                 (32U)
#define VDO_YY_D2B_ADDR_DBG_MSK                                 (((1U<<VDO_YY_D2B_ADDR_DBG_LEN)-1)<<VDO_YY_D2B_ADDR_DBG_POS)
#define VDO_YY_D2B_ADDR_DBG_UMSK                                (~(((1U<<VDO_YY_D2B_ADDR_DBG_LEN)-1)<<VDO_YY_D2B_ADDR_DBG_POS))

/* 0x1e4 : vdo_h264_uv_d2b_addr */
#define VDO_H264_UV_D2B_ADDR_OFFSET                             (0x1e4)
#define VDO_UV_D2B_ADDR_DBG                                     VDO_UV_D2B_ADDR_DBG
#define VDO_UV_D2B_ADDR_DBG_POS                                 (0U)
#define VDO_UV_D2B_ADDR_DBG_LEN                                 (32U)
#define VDO_UV_D2B_ADDR_DBG_MSK                                 (((1U<<VDO_UV_D2B_ADDR_DBG_LEN)-1)<<VDO_UV_D2B_ADDR_DBG_POS)
#define VDO_UV_D2B_ADDR_DBG_UMSK                                (~(((1U<<VDO_UV_D2B_ADDR_DBG_LEN)-1)<<VDO_UV_D2B_ADDR_DBG_POS))

/* 0x1e8 : vdo_h264_yy_ofst_addr */
#define VDO_H264_YY_OFST_ADDR_OFFSET                            (0x1e8)
#define VDO_YY_MFRM_OFST_DBG                                    VDO_YY_MFRM_OFST_DBG
#define VDO_YY_MFRM_OFST_DBG_POS                                (0U)
#define VDO_YY_MFRM_OFST_DBG_LEN                                (32U)
#define VDO_YY_MFRM_OFST_DBG_MSK                                (((1U<<VDO_YY_MFRM_OFST_DBG_LEN)-1)<<VDO_YY_MFRM_OFST_DBG_POS)
#define VDO_YY_MFRM_OFST_DBG_UMSK                               (~(((1U<<VDO_YY_MFRM_OFST_DBG_LEN)-1)<<VDO_YY_MFRM_OFST_DBG_POS))

/* 0x1ec : vdo_h264_uv_ofst_addr */
#define VDO_H264_UV_OFST_ADDR_OFFSET                            (0x1ec)
#define VDO_UV_MFRM_OFST_DBG                                    VDO_UV_MFRM_OFST_DBG
#define VDO_UV_MFRM_OFST_DBG_POS                                (0U)
#define VDO_UV_MFRM_OFST_DBG_LEN                                (32U)
#define VDO_UV_MFRM_OFST_DBG_MSK                                (((1U<<VDO_UV_MFRM_OFST_DBG_LEN)-1)<<VDO_UV_MFRM_OFST_DBG_POS)
#define VDO_UV_MFRM_OFST_DBG_UMSK                               (~(((1U<<VDO_UV_MFRM_OFST_DBG_LEN)-1)<<VDO_UV_MFRM_OFST_DBG_POS))

/* 0x1f0 : vdo_h264_d2b_ml */
#define VDO_H264_D2B_ML_OFFSET                                  (0x1f0)
#define VDO_YY_D2B_ML_DBG                                       VDO_YY_D2B_ML_DBG
#define VDO_YY_D2B_ML_DBG_POS                                   (0U)
#define VDO_YY_D2B_ML_DBG_LEN                                   (16U)
#define VDO_YY_D2B_ML_DBG_MSK                                   (((1U<<VDO_YY_D2B_ML_DBG_LEN)-1)<<VDO_YY_D2B_ML_DBG_POS)
#define VDO_YY_D2B_ML_DBG_UMSK                                  (~(((1U<<VDO_YY_D2B_ML_DBG_LEN)-1)<<VDO_YY_D2B_ML_DBG_POS))
#define VDO_UV_D2B_ML_DBG                                       VDO_UV_D2B_ML_DBG
#define VDO_UV_D2B_ML_DBG_POS                                   (16U)
#define VDO_UV_D2B_ML_DBG_LEN                                   (16U)
#define VDO_UV_D2B_ML_DBG_MSK                                   (((1U<<VDO_UV_D2B_ML_DBG_LEN)-1)<<VDO_UV_D2B_ML_DBG_POS)
#define VDO_UV_D2B_ML_DBG_UMSK                                  (~(((1U<<VDO_UV_D2B_ML_DBG_LEN)-1)<<VDO_UV_D2B_ML_DBG_POS))

/* 0x1f4 : vdo_h264_load_mbidx_dbg */
#define VDO_H264_LOAD_MBIDX_DBG_OFFSET                          (0x1f4)
#define VDO_LOAD_MBIDX_DBG                                      VDO_LOAD_MBIDX_DBG
#define VDO_LOAD_MBIDX_DBG_POS                                  (0U)
#define VDO_LOAD_MBIDX_DBG_LEN                                  (32U)
#define VDO_LOAD_MBIDX_DBG_MSK                                  (((1U<<VDO_LOAD_MBIDX_DBG_LEN)-1)<<VDO_LOAD_MBIDX_DBG_POS)
#define VDO_LOAD_MBIDX_DBG_UMSK                                 (~(((1U<<VDO_LOAD_MBIDX_DBG_LEN)-1)<<VDO_LOAD_MBIDX_DBG_POS))

/* 0x1f8 : vdo_h264_yc_mb_err */
#define VDO_H264_YC_MB_ERR_OFFSET                               (0x1f8)
#define VDO_YC_MB_ERR                                           VDO_YC_MB_ERR
#define VDO_YC_MB_ERR_POS                                       (0U)
#define VDO_YC_MB_ERR_LEN                                       (3U)
#define VDO_YC_MB_ERR_MSK                                       (((1U<<VDO_YC_MB_ERR_LEN)-1)<<VDO_YC_MB_ERR_POS)
#define VDO_YC_MB_ERR_UMSK                                      (~(((1U<<VDO_YC_MB_ERR_LEN)-1)<<VDO_YC_MB_ERR_POS))

/* 0x1fc : vdo_h264_s_yy_d2b_addr */
#define VDO_H264_S_YY_D2B_ADDR_OFFSET                           (0x1fc)
#define VDO_S_YY_D2B_ADDR_DBG                                   VDO_S_YY_D2B_ADDR_DBG
#define VDO_S_YY_D2B_ADDR_DBG_POS                               (0U)
#define VDO_S_YY_D2B_ADDR_DBG_LEN                               (32U)
#define VDO_S_YY_D2B_ADDR_DBG_MSK                               (((1U<<VDO_S_YY_D2B_ADDR_DBG_LEN)-1)<<VDO_S_YY_D2B_ADDR_DBG_POS)
#define VDO_S_YY_D2B_ADDR_DBG_UMSK                              (~(((1U<<VDO_S_YY_D2B_ADDR_DBG_LEN)-1)<<VDO_S_YY_D2B_ADDR_DBG_POS))

/* 0x200 : vdo_h264_s_uv_d2b_addr */
#define VDO_H264_S_UV_D2B_ADDR_OFFSET                           (0x200)
#define VDO_S_UV_D2B_ADDR_DBG                                   VDO_S_UV_D2B_ADDR_DBG
#define VDO_S_UV_D2B_ADDR_DBG_POS                               (0U)
#define VDO_S_UV_D2B_ADDR_DBG_LEN                               (32U)
#define VDO_S_UV_D2B_ADDR_DBG_MSK                               (((1U<<VDO_S_UV_D2B_ADDR_DBG_LEN)-1)<<VDO_S_UV_D2B_ADDR_DBG_POS)
#define VDO_S_UV_D2B_ADDR_DBG_UMSK                              (~(((1U<<VDO_S_UV_D2B_ADDR_DBG_LEN)-1)<<VDO_S_UV_D2B_ADDR_DBG_POS))

/* 0x204 : vdo_h264_s_yy_ofst_addr */
#define VDO_H264_S_YY_OFST_ADDR_OFFSET                          (0x204)
#define VDO_S_YY_MFRM_OFST_DBG                                  VDO_S_YY_MFRM_OFST_DBG
#define VDO_S_YY_MFRM_OFST_DBG_POS                              (0U)
#define VDO_S_YY_MFRM_OFST_DBG_LEN                              (32U)
#define VDO_S_YY_MFRM_OFST_DBG_MSK                              (((1U<<VDO_S_YY_MFRM_OFST_DBG_LEN)-1)<<VDO_S_YY_MFRM_OFST_DBG_POS)
#define VDO_S_YY_MFRM_OFST_DBG_UMSK                             (~(((1U<<VDO_S_YY_MFRM_OFST_DBG_LEN)-1)<<VDO_S_YY_MFRM_OFST_DBG_POS))

/* 0x208 : vdo_h264_s_uv_ofst_addr */
#define VDO_H264_S_UV_OFST_ADDR_OFFSET                          (0x208)
#define VDO_S_UV_MFRM_OFST_DBG                                  VDO_S_UV_MFRM_OFST_DBG
#define VDO_S_UV_MFRM_OFST_DBG_POS                              (0U)
#define VDO_S_UV_MFRM_OFST_DBG_LEN                              (32U)
#define VDO_S_UV_MFRM_OFST_DBG_MSK                              (((1U<<VDO_S_UV_MFRM_OFST_DBG_LEN)-1)<<VDO_S_UV_MFRM_OFST_DBG_POS)
#define VDO_S_UV_MFRM_OFST_DBG_UMSK                             (~(((1U<<VDO_S_UV_MFRM_OFST_DBG_LEN)-1)<<VDO_S_UV_MFRM_OFST_DBG_POS))

/* 0x20c : vdo_h264_s_d2b_ml */
#define VDO_H264_S_D2B_ML_OFFSET                                (0x20c)
#define VDO_S_YY_D2B_ML_DBG                                     VDO_S_YY_D2B_ML_DBG
#define VDO_S_YY_D2B_ML_DBG_POS                                 (0U)
#define VDO_S_YY_D2B_ML_DBG_LEN                                 (16U)
#define VDO_S_YY_D2B_ML_DBG_MSK                                 (((1U<<VDO_S_YY_D2B_ML_DBG_LEN)-1)<<VDO_S_YY_D2B_ML_DBG_POS)
#define VDO_S_YY_D2B_ML_DBG_UMSK                                (~(((1U<<VDO_S_YY_D2B_ML_DBG_LEN)-1)<<VDO_S_YY_D2B_ML_DBG_POS))
#define VDO_S_UV_D2B_ML_DBG                                     VDO_S_UV_D2B_ML_DBG
#define VDO_S_UV_D2B_ML_DBG_POS                                 (16U)
#define VDO_S_UV_D2B_ML_DBG_LEN                                 (16U)
#define VDO_S_UV_D2B_ML_DBG_MSK                                 (((1U<<VDO_S_UV_D2B_ML_DBG_LEN)-1)<<VDO_S_UV_D2B_ML_DBG_POS)
#define VDO_S_UV_D2B_ML_DBG_UMSK                                (~(((1U<<VDO_S_UV_D2B_ML_DBG_LEN)-1)<<VDO_S_UV_D2B_ML_DBG_POS))

/* 0x210 : vdo_h264_s_load_mbidx_dbg */
#define VDO_H264_S_LOAD_MBIDX_DBG_OFFSET                        (0x210)
#define VDO_S_LOAD_MBIDX_DBG                                    VDO_S_LOAD_MBIDX_DBG
#define VDO_S_LOAD_MBIDX_DBG_POS                                (0U)
#define VDO_S_LOAD_MBIDX_DBG_LEN                                (32U)
#define VDO_S_LOAD_MBIDX_DBG_MSK                                (((1U<<VDO_S_LOAD_MBIDX_DBG_LEN)-1)<<VDO_S_LOAD_MBIDX_DBG_POS)
#define VDO_S_LOAD_MBIDX_DBG_UMSK                               (~(((1U<<VDO_S_LOAD_MBIDX_DBG_LEN)-1)<<VDO_S_LOAD_MBIDX_DBG_POS))

/* 0x214 : vdo_h264_s_yc_mb_err */
#define VDO_H264_S_YC_MB_ERR_OFFSET                             (0x214)
#define VDO_S_YC_MB_ERR                                         VDO_S_YC_MB_ERR
#define VDO_S_YC_MB_ERR_POS                                     (0U)
#define VDO_S_YC_MB_ERR_LEN                                     (3U)
#define VDO_S_YC_MB_ERR_MSK                                     (((1U<<VDO_S_YC_MB_ERR_LEN)-1)<<VDO_S_YC_MB_ERR_POS)
#define VDO_S_YC_MB_ERR_UMSK                                    (~(((1U<<VDO_S_YC_MB_ERR_LEN)-1)<<VDO_S_YC_MB_ERR_POS))

/* 0x228 : vdo_h264_pfch_ctrl */
#define VDO_H264_PFCH_CTRL_OFFSET                               (0x228)
#define VDO_CFG_PFCH_MBX_S                                      VDO_CFG_PFCH_MBX_S
#define VDO_CFG_PFCH_MBX_S_POS                                  (0U)
#define VDO_CFG_PFCH_MBX_S_LEN                                  (7U)
#define VDO_CFG_PFCH_MBX_S_MSK                                  (((1U<<VDO_CFG_PFCH_MBX_S_LEN)-1)<<VDO_CFG_PFCH_MBX_S_POS)
#define VDO_CFG_PFCH_MBX_S_UMSK                                 (~(((1U<<VDO_CFG_PFCH_MBX_S_LEN)-1)<<VDO_CFG_PFCH_MBX_S_POS))
#define VDO_CFG_PFCH_MBY_S                                      VDO_CFG_PFCH_MBY_S
#define VDO_CFG_PFCH_MBY_S_POS                                  (8U)
#define VDO_CFG_PFCH_MBY_S_LEN                                  (7U)
#define VDO_CFG_PFCH_MBY_S_MSK                                  (((1U<<VDO_CFG_PFCH_MBY_S_LEN)-1)<<VDO_CFG_PFCH_MBY_S_POS)
#define VDO_CFG_PFCH_MBY_S_UMSK                                 (~(((1U<<VDO_CFG_PFCH_MBY_S_LEN)-1)<<VDO_CFG_PFCH_MBY_S_POS))
#define VDO_CFG_PFCH_EN                                         VDO_CFG_PFCH_EN
#define VDO_CFG_PFCH_EN_POS                                     (16U)
#define VDO_CFG_PFCH_EN_LEN                                     (1U)
#define VDO_CFG_PFCH_EN_MSK                                     (((1U<<VDO_CFG_PFCH_EN_LEN)-1)<<VDO_CFG_PFCH_EN_POS)
#define VDO_CFG_PFCH_EN_UMSK                                    (~(((1U<<VDO_CFG_PFCH_EN_LEN)-1)<<VDO_CFG_PFCH_EN_POS))

/* 0x22c : vdo_h264_pfch_base */
#define VDO_H264_PFCH_BASE_OFFSET                               (0x22c)
#define VDO_CFG_PFCH_BASE_ADDR                                  VDO_CFG_PFCH_BASE_ADDR
#define VDO_CFG_PFCH_BASE_ADDR_POS                              (0U)
#define VDO_CFG_PFCH_BASE_ADDR_LEN                              (32U)
#define VDO_CFG_PFCH_BASE_ADDR_MSK                              (((1U<<VDO_CFG_PFCH_BASE_ADDR_LEN)-1)<<VDO_CFG_PFCH_BASE_ADDR_POS)
#define VDO_CFG_PFCH_BASE_ADDR_UMSK                             (~(((1U<<VDO_CFG_PFCH_BASE_ADDR_LEN)-1)<<VDO_CFG_PFCH_BASE_ADDR_POS))

/* 0x230 : vdo_h264_pfchv_base */
#define VDO_H264_PFCHV_BASE_OFFSET                              (0x230)
#define VDO_CFG_PFCHV_BASE_ADDR                                 VDO_CFG_PFCHV_BASE_ADDR
#define VDO_CFG_PFCHV_BASE_ADDR_POS                             (0U)
#define VDO_CFG_PFCHV_BASE_ADDR_LEN                             (32U)
#define VDO_CFG_PFCHV_BASE_ADDR_MSK                             (((1U<<VDO_CFG_PFCHV_BASE_ADDR_LEN)-1)<<VDO_CFG_PFCHV_BASE_ADDR_POS)
#define VDO_CFG_PFCHV_BASE_ADDR_UMSK                            (~(((1U<<VDO_CFG_PFCHV_BASE_ADDR_LEN)-1)<<VDO_CFG_PFCHV_BASE_ADDR_POS))

/* 0x234 : vdo_h264_s_pfch_ctrl */
#define VDO_H264_S_PFCH_CTRL_OFFSET                             (0x234)
#define VDO_CFG_S_PFCH_MBX_S                                    VDO_CFG_S_PFCH_MBX_S
#define VDO_CFG_S_PFCH_MBX_S_POS                                (0U)
#define VDO_CFG_S_PFCH_MBX_S_LEN                                (7U)
#define VDO_CFG_S_PFCH_MBX_S_MSK                                (((1U<<VDO_CFG_S_PFCH_MBX_S_LEN)-1)<<VDO_CFG_S_PFCH_MBX_S_POS)
#define VDO_CFG_S_PFCH_MBX_S_UMSK                               (~(((1U<<VDO_CFG_S_PFCH_MBX_S_LEN)-1)<<VDO_CFG_S_PFCH_MBX_S_POS))
#define VDO_CFG_S_PFCH_MBY_S                                    VDO_CFG_S_PFCH_MBY_S
#define VDO_CFG_S_PFCH_MBY_S_POS                                (8U)
#define VDO_CFG_S_PFCH_MBY_S_LEN                                (7U)
#define VDO_CFG_S_PFCH_MBY_S_MSK                                (((1U<<VDO_CFG_S_PFCH_MBY_S_LEN)-1)<<VDO_CFG_S_PFCH_MBY_S_POS)
#define VDO_CFG_S_PFCH_MBY_S_UMSK                               (~(((1U<<VDO_CFG_S_PFCH_MBY_S_LEN)-1)<<VDO_CFG_S_PFCH_MBY_S_POS))
#define VDO_CFG_S_PFCH_EN                                       VDO_CFG_S_PFCH_EN
#define VDO_CFG_S_PFCH_EN_POS                                   (16U)
#define VDO_CFG_S_PFCH_EN_LEN                                   (1U)
#define VDO_CFG_S_PFCH_EN_MSK                                   (((1U<<VDO_CFG_S_PFCH_EN_LEN)-1)<<VDO_CFG_S_PFCH_EN_POS)
#define VDO_CFG_S_PFCH_EN_UMSK                                  (~(((1U<<VDO_CFG_S_PFCH_EN_LEN)-1)<<VDO_CFG_S_PFCH_EN_POS))

/* 0x238 : vdo_h264_s_pfch_base */
#define VDO_H264_S_PFCH_BASE_OFFSET                             (0x238)
#define VDO_CFG_S_PFCH_BASE_ADDR                                VDO_CFG_S_PFCH_BASE_ADDR
#define VDO_CFG_S_PFCH_BASE_ADDR_POS                            (0U)
#define VDO_CFG_S_PFCH_BASE_ADDR_LEN                            (32U)
#define VDO_CFG_S_PFCH_BASE_ADDR_MSK                            (((1U<<VDO_CFG_S_PFCH_BASE_ADDR_LEN)-1)<<VDO_CFG_S_PFCH_BASE_ADDR_POS)
#define VDO_CFG_S_PFCH_BASE_ADDR_UMSK                           (~(((1U<<VDO_CFG_S_PFCH_BASE_ADDR_LEN)-1)<<VDO_CFG_S_PFCH_BASE_ADDR_POS))

/* 0x23c : vdo_h264_s_pfchv_base */
#define VDO_H264_S_PFCHV_BASE_OFFSET                            (0x23c)
#define VDO_CFG_S_PFCHV_BASE_ADDR                               VDO_CFG_S_PFCHV_BASE_ADDR
#define VDO_CFG_S_PFCHV_BASE_ADDR_POS                           (0U)
#define VDO_CFG_S_PFCHV_BASE_ADDR_LEN                           (32U)
#define VDO_CFG_S_PFCHV_BASE_ADDR_MSK                           (((1U<<VDO_CFG_S_PFCHV_BASE_ADDR_LEN)-1)<<VDO_CFG_S_PFCHV_BASE_ADDR_POS)
#define VDO_CFG_S_PFCHV_BASE_ADDR_UMSK                          (~(((1U<<VDO_CFG_S_PFCHV_BASE_ADDR_LEN)-1)<<VDO_CFG_S_PFCHV_BASE_ADDR_POS))

/* 0x240 : vdo_h264_hwback_mode */
#define VDO_H264_HWBACK_MODE_OFFSET                             (0x240)
#define VDO_CFG_SRAMCK_MODE                                     VDO_CFG_SRAMCK_MODE
#define VDO_CFG_SRAMCK_MODE_POS                                 (0U)
#define VDO_CFG_SRAMCK_MODE_LEN                                 (1U)
#define VDO_CFG_SRAMCK_MODE_MSK                                 (((1U<<VDO_CFG_SRAMCK_MODE_LEN)-1)<<VDO_CFG_SRAMCK_MODE_POS)
#define VDO_CFG_SRAMCK_MODE_UMSK                                (~(((1U<<VDO_CFG_SRAMCK_MODE_LEN)-1)<<VDO_CFG_SRAMCK_MODE_POS))
#define VDO_CFG_NAL_MP_MODE                                     VDO_CFG_NAL_MP_MODE
#define VDO_CFG_NAL_MP_MODE_POS                                 (1U)
#define VDO_CFG_NAL_MP_MODE_LEN                                 (1U)
#define VDO_CFG_NAL_MP_MODE_MSK                                 (((1U<<VDO_CFG_NAL_MP_MODE_LEN)-1)<<VDO_CFG_NAL_MP_MODE_POS)
#define VDO_CFG_NAL_MP_MODE_UMSK                                (~(((1U<<VDO_CFG_NAL_MP_MODE_LEN)-1)<<VDO_CFG_NAL_MP_MODE_POS))
#define VDO_CFG_S_NAL_MP_MODE                                   VDO_CFG_S_NAL_MP_MODE
#define VDO_CFG_S_NAL_MP_MODE_POS                               (2U)
#define VDO_CFG_S_NAL_MP_MODE_LEN                               (1U)
#define VDO_CFG_S_NAL_MP_MODE_MSK                               (((1U<<VDO_CFG_S_NAL_MP_MODE_LEN)-1)<<VDO_CFG_S_NAL_MP_MODE_POS)
#define VDO_CFG_S_NAL_MP_MODE_UMSK                              (~(((1U<<VDO_CFG_S_NAL_MP_MODE_LEN)-1)<<VDO_CFG_S_NAL_MP_MODE_POS))

/* 0x244 : vdo_h264_roi_mode */
#define VDO_H264_ROI_MODE_OFFSET                                (0x244)
#define VDO_CFG_ROI_EN                                          VDO_CFG_ROI_EN
#define VDO_CFG_ROI_EN_POS                                      (0U)
#define VDO_CFG_ROI_EN_LEN                                      (8U)
#define VDO_CFG_ROI_EN_MSK                                      (((1U<<VDO_CFG_ROI_EN_LEN)-1)<<VDO_CFG_ROI_EN_POS)
#define VDO_CFG_ROI_EN_UMSK                                     (~(((1U<<VDO_CFG_ROI_EN_LEN)-1)<<VDO_CFG_ROI_EN_POS))
#define VDO_CFG_ROI_UPD                                         VDO_CFG_ROI_UPD
#define VDO_CFG_ROI_UPD_POS                                     (8U)
#define VDO_CFG_ROI_UPD_LEN                                     (1U)
#define VDO_CFG_ROI_UPD_MSK                                     (((1U<<VDO_CFG_ROI_UPD_LEN)-1)<<VDO_CFG_ROI_UPD_POS)
#define VDO_CFG_ROI_UPD_UMSK                                    (~(((1U<<VDO_CFG_ROI_UPD_LEN)-1)<<VDO_CFG_ROI_UPD_POS))

/* 0x248 : vdo_h264_roi_bit */
#define VDO_H264_ROI_BIT_OFFSET                                 (0x248)
#define VDO_CFG_PBIT_RATIO                                      VDO_CFG_PBIT_RATIO
#define VDO_CFG_PBIT_RATIO_POS                                  (0U)
#define VDO_CFG_PBIT_RATIO_LEN                                  (13U)
#define VDO_CFG_PBIT_RATIO_MSK                                  (((1U<<VDO_CFG_PBIT_RATIO_LEN)-1)<<VDO_CFG_PBIT_RATIO_POS)
#define VDO_CFG_PBIT_RATIO_UMSK                                 (~(((1U<<VDO_CFG_PBIT_RATIO_LEN)-1)<<VDO_CFG_PBIT_RATIO_POS))
#define VDO_CFG_IBIT_RATIO                                      VDO_CFG_IBIT_RATIO
#define VDO_CFG_IBIT_RATIO_POS                                  (13U)
#define VDO_CFG_IBIT_RATIO_LEN                                  (13U)
#define VDO_CFG_IBIT_RATIO_MSK                                  (((1U<<VDO_CFG_IBIT_RATIO_LEN)-1)<<VDO_CFG_IBIT_RATIO_POS)
#define VDO_CFG_IBIT_RATIO_UMSK                                 (~(((1U<<VDO_CFG_IBIT_RATIO_LEN)-1)<<VDO_CFG_IBIT_RATIO_POS))
#define VDO_CFG_ITHRE                                           VDO_CFG_ITHRE
#define VDO_CFG_ITHRE_POS                                       (26U)
#define VDO_CFG_ITHRE_LEN                                       (6U)
#define VDO_CFG_ITHRE_MSK                                       (((1U<<VDO_CFG_ITHRE_LEN)-1)<<VDO_CFG_ITHRE_POS)
#define VDO_CFG_ITHRE_UMSK                                      (~(((1U<<VDO_CFG_ITHRE_LEN)-1)<<VDO_CFG_ITHRE_POS))

/* 0x24c : vdo_h264_roi_qptune */
#define VDO_H264_ROI_QPTUNE_OFFSET                              (0x24c)
#define VDO_CFG_PQP_DECR                                        VDO_CFG_PQP_DECR
#define VDO_CFG_PQP_DECR_POS                                    (0U)
#define VDO_CFG_PQP_DECR_LEN                                    (6U)
#define VDO_CFG_PQP_DECR_MSK                                    (((1U<<VDO_CFG_PQP_DECR_LEN)-1)<<VDO_CFG_PQP_DECR_POS)
#define VDO_CFG_PQP_DECR_UMSK                                   (~(((1U<<VDO_CFG_PQP_DECR_LEN)-1)<<VDO_CFG_PQP_DECR_POS))
#define VDO_CFG_IQP_DECR                                        VDO_CFG_IQP_DECR
#define VDO_CFG_IQP_DECR_POS                                    (8U)
#define VDO_CFG_IQP_DECR_LEN                                    (6U)
#define VDO_CFG_IQP_DECR_MSK                                    (((1U<<VDO_CFG_IQP_DECR_LEN)-1)<<VDO_CFG_IQP_DECR_POS)
#define VDO_CFG_IQP_DECR_UMSK                                   (~(((1U<<VDO_CFG_IQP_DECR_LEN)-1)<<VDO_CFG_IQP_DECR_POS))
#define VDO_CFG_N2R_QP_DECR                                     VDO_CFG_N2R_QP_DECR
#define VDO_CFG_N2R_QP_DECR_POS                                 (16U)
#define VDO_CFG_N2R_QP_DECR_LEN                                 (6U)
#define VDO_CFG_N2R_QP_DECR_MSK                                 (((1U<<VDO_CFG_N2R_QP_DECR_LEN)-1)<<VDO_CFG_N2R_QP_DECR_POS)
#define VDO_CFG_N2R_QP_DECR_UMSK                                (~(((1U<<VDO_CFG_N2R_QP_DECR_LEN)-1)<<VDO_CFG_N2R_QP_DECR_POS))
#define VDO_CFG_FIXQP                                           VDO_CFG_FIXQP
#define VDO_CFG_FIXQP_POS                                       (24U)
#define VDO_CFG_FIXQP_LEN                                       (6U)
#define VDO_CFG_FIXQP_MSK                                       (((1U<<VDO_CFG_FIXQP_LEN)-1)<<VDO_CFG_FIXQP_POS)
#define VDO_CFG_FIXQP_UMSK                                      (~(((1U<<VDO_CFG_FIXQP_LEN)-1)<<VDO_CFG_FIXQP_POS))

/* 0x250 : vdo_h264_roi_bittune */
#define VDO_H264_ROI_BITTUNE_OFFSET                             (0x250)
#define VDO_CFG_ROI_PBIT_OFST                                   VDO_CFG_ROI_PBIT_OFST
#define VDO_CFG_ROI_PBIT_OFST_POS                               (0U)
#define VDO_CFG_ROI_PBIT_OFST_LEN                               (5U)
#define VDO_CFG_ROI_PBIT_OFST_MSK                               (((1U<<VDO_CFG_ROI_PBIT_OFST_LEN)-1)<<VDO_CFG_ROI_PBIT_OFST_POS)
#define VDO_CFG_ROI_PBIT_OFST_UMSK                              (~(((1U<<VDO_CFG_ROI_PBIT_OFST_LEN)-1)<<VDO_CFG_ROI_PBIT_OFST_POS))
#define VDO_CFG_ROI_IBIT_OFST                                   VDO_CFG_ROI_IBIT_OFST
#define VDO_CFG_ROI_IBIT_OFST_POS                               (8U)
#define VDO_CFG_ROI_IBIT_OFST_LEN                               (8U)
#define VDO_CFG_ROI_IBIT_OFST_MSK                               (((1U<<VDO_CFG_ROI_IBIT_OFST_LEN)-1)<<VDO_CFG_ROI_IBIT_OFST_POS)
#define VDO_CFG_ROI_IBIT_OFST_UMSK                              (~(((1U<<VDO_CFG_ROI_IBIT_OFST_LEN)-1)<<VDO_CFG_ROI_IBIT_OFST_POS))
#define VDO_CFG_NROI_PBIT_OFST                                  VDO_CFG_NROI_PBIT_OFST
#define VDO_CFG_NROI_PBIT_OFST_POS                              (16U)
#define VDO_CFG_NROI_PBIT_OFST_LEN                              (5U)
#define VDO_CFG_NROI_PBIT_OFST_MSK                              (((1U<<VDO_CFG_NROI_PBIT_OFST_LEN)-1)<<VDO_CFG_NROI_PBIT_OFST_POS)
#define VDO_CFG_NROI_PBIT_OFST_UMSK                             (~(((1U<<VDO_CFG_NROI_PBIT_OFST_LEN)-1)<<VDO_CFG_NROI_PBIT_OFST_POS))
#define VDO_CFG_NROI_IBIT_OFST                                  VDO_CFG_NROI_IBIT_OFST
#define VDO_CFG_NROI_IBIT_OFST_POS                              (24U)
#define VDO_CFG_NROI_IBIT_OFST_LEN                              (8U)
#define VDO_CFG_NROI_IBIT_OFST_MSK                              (((1U<<VDO_CFG_NROI_IBIT_OFST_LEN)-1)<<VDO_CFG_NROI_IBIT_OFST_POS)
#define VDO_CFG_NROI_IBIT_OFST_UMSK                             (~(((1U<<VDO_CFG_NROI_IBIT_OFST_LEN)-1)<<VDO_CFG_NROI_IBIT_OFST_POS))

/* 0x254 : vdo_h264_roi0 */
#define VDO_H264_ROI0_OFFSET                                    (0x254)
#define VDO_CFG_ROI0_MBX_S                                      VDO_CFG_ROI0_MBX_S
#define VDO_CFG_ROI0_MBX_S_POS                                  (0U)
#define VDO_CFG_ROI0_MBX_S_LEN                                  (7U)
#define VDO_CFG_ROI0_MBX_S_MSK                                  (((1U<<VDO_CFG_ROI0_MBX_S_LEN)-1)<<VDO_CFG_ROI0_MBX_S_POS)
#define VDO_CFG_ROI0_MBX_S_UMSK                                 (~(((1U<<VDO_CFG_ROI0_MBX_S_LEN)-1)<<VDO_CFG_ROI0_MBX_S_POS))
#define VDO_CFG_ROI0_MBX_E                                      VDO_CFG_ROI0_MBX_E
#define VDO_CFG_ROI0_MBX_E_POS                                  (8U)
#define VDO_CFG_ROI0_MBX_E_LEN                                  (7U)
#define VDO_CFG_ROI0_MBX_E_MSK                                  (((1U<<VDO_CFG_ROI0_MBX_E_LEN)-1)<<VDO_CFG_ROI0_MBX_E_POS)
#define VDO_CFG_ROI0_MBX_E_UMSK                                 (~(((1U<<VDO_CFG_ROI0_MBX_E_LEN)-1)<<VDO_CFG_ROI0_MBX_E_POS))
#define VDO_CFG_ROI0_MBY_S                                      VDO_CFG_ROI0_MBY_S
#define VDO_CFG_ROI0_MBY_S_POS                                  (16U)
#define VDO_CFG_ROI0_MBY_S_LEN                                  (7U)
#define VDO_CFG_ROI0_MBY_S_MSK                                  (((1U<<VDO_CFG_ROI0_MBY_S_LEN)-1)<<VDO_CFG_ROI0_MBY_S_POS)
#define VDO_CFG_ROI0_MBY_S_UMSK                                 (~(((1U<<VDO_CFG_ROI0_MBY_S_LEN)-1)<<VDO_CFG_ROI0_MBY_S_POS))
#define VDO_CFG_ROI0_MBY_E                                      VDO_CFG_ROI0_MBY_E
#define VDO_CFG_ROI0_MBY_E_POS                                  (24U)
#define VDO_CFG_ROI0_MBY_E_LEN                                  (7U)
#define VDO_CFG_ROI0_MBY_E_MSK                                  (((1U<<VDO_CFG_ROI0_MBY_E_LEN)-1)<<VDO_CFG_ROI0_MBY_E_POS)
#define VDO_CFG_ROI0_MBY_E_UMSK                                 (~(((1U<<VDO_CFG_ROI0_MBY_E_LEN)-1)<<VDO_CFG_ROI0_MBY_E_POS))

/* 0x258 : vdo_h264_roi1 */
#define VDO_H264_ROI1_OFFSET                                    (0x258)
#define VDO_CFG_ROI1_MBX_S                                      VDO_CFG_ROI1_MBX_S
#define VDO_CFG_ROI1_MBX_S_POS                                  (0U)
#define VDO_CFG_ROI1_MBX_S_LEN                                  (7U)
#define VDO_CFG_ROI1_MBX_S_MSK                                  (((1U<<VDO_CFG_ROI1_MBX_S_LEN)-1)<<VDO_CFG_ROI1_MBX_S_POS)
#define VDO_CFG_ROI1_MBX_S_UMSK                                 (~(((1U<<VDO_CFG_ROI1_MBX_S_LEN)-1)<<VDO_CFG_ROI1_MBX_S_POS))
#define VDO_CFG_ROI1_MBX_E                                      VDO_CFG_ROI1_MBX_E
#define VDO_CFG_ROI1_MBX_E_POS                                  (8U)
#define VDO_CFG_ROI1_MBX_E_LEN                                  (7U)
#define VDO_CFG_ROI1_MBX_E_MSK                                  (((1U<<VDO_CFG_ROI1_MBX_E_LEN)-1)<<VDO_CFG_ROI1_MBX_E_POS)
#define VDO_CFG_ROI1_MBX_E_UMSK                                 (~(((1U<<VDO_CFG_ROI1_MBX_E_LEN)-1)<<VDO_CFG_ROI1_MBX_E_POS))
#define VDO_CFG_ROI1_MBY_S                                      VDO_CFG_ROI1_MBY_S
#define VDO_CFG_ROI1_MBY_S_POS                                  (16U)
#define VDO_CFG_ROI1_MBY_S_LEN                                  (7U)
#define VDO_CFG_ROI1_MBY_S_MSK                                  (((1U<<VDO_CFG_ROI1_MBY_S_LEN)-1)<<VDO_CFG_ROI1_MBY_S_POS)
#define VDO_CFG_ROI1_MBY_S_UMSK                                 (~(((1U<<VDO_CFG_ROI1_MBY_S_LEN)-1)<<VDO_CFG_ROI1_MBY_S_POS))
#define VDO_CFG_ROI1_MBY_E                                      VDO_CFG_ROI1_MBY_E
#define VDO_CFG_ROI1_MBY_E_POS                                  (24U)
#define VDO_CFG_ROI1_MBY_E_LEN                                  (7U)
#define VDO_CFG_ROI1_MBY_E_MSK                                  (((1U<<VDO_CFG_ROI1_MBY_E_LEN)-1)<<VDO_CFG_ROI1_MBY_E_POS)
#define VDO_CFG_ROI1_MBY_E_UMSK                                 (~(((1U<<VDO_CFG_ROI1_MBY_E_LEN)-1)<<VDO_CFG_ROI1_MBY_E_POS))

/* 0x25c : vdo_h264_roi2 */
#define VDO_H264_ROI2_OFFSET                                    (0x25c)
#define VDO_CFG_ROI2_MBX_S                                      VDO_CFG_ROI2_MBX_S
#define VDO_CFG_ROI2_MBX_S_POS                                  (0U)
#define VDO_CFG_ROI2_MBX_S_LEN                                  (7U)
#define VDO_CFG_ROI2_MBX_S_MSK                                  (((1U<<VDO_CFG_ROI2_MBX_S_LEN)-1)<<VDO_CFG_ROI2_MBX_S_POS)
#define VDO_CFG_ROI2_MBX_S_UMSK                                 (~(((1U<<VDO_CFG_ROI2_MBX_S_LEN)-1)<<VDO_CFG_ROI2_MBX_S_POS))
#define VDO_CFG_ROI2_MBX_E                                      VDO_CFG_ROI2_MBX_E
#define VDO_CFG_ROI2_MBX_E_POS                                  (8U)
#define VDO_CFG_ROI2_MBX_E_LEN                                  (7U)
#define VDO_CFG_ROI2_MBX_E_MSK                                  (((1U<<VDO_CFG_ROI2_MBX_E_LEN)-1)<<VDO_CFG_ROI2_MBX_E_POS)
#define VDO_CFG_ROI2_MBX_E_UMSK                                 (~(((1U<<VDO_CFG_ROI2_MBX_E_LEN)-1)<<VDO_CFG_ROI2_MBX_E_POS))
#define VDO_CFG_ROI2_MBY_S                                      VDO_CFG_ROI2_MBY_S
#define VDO_CFG_ROI2_MBY_S_POS                                  (16U)
#define VDO_CFG_ROI2_MBY_S_LEN                                  (7U)
#define VDO_CFG_ROI2_MBY_S_MSK                                  (((1U<<VDO_CFG_ROI2_MBY_S_LEN)-1)<<VDO_CFG_ROI2_MBY_S_POS)
#define VDO_CFG_ROI2_MBY_S_UMSK                                 (~(((1U<<VDO_CFG_ROI2_MBY_S_LEN)-1)<<VDO_CFG_ROI2_MBY_S_POS))
#define VDO_CFG_ROI2_MBY_E                                      VDO_CFG_ROI2_MBY_E
#define VDO_CFG_ROI2_MBY_E_POS                                  (24U)
#define VDO_CFG_ROI2_MBY_E_LEN                                  (7U)
#define VDO_CFG_ROI2_MBY_E_MSK                                  (((1U<<VDO_CFG_ROI2_MBY_E_LEN)-1)<<VDO_CFG_ROI2_MBY_E_POS)
#define VDO_CFG_ROI2_MBY_E_UMSK                                 (~(((1U<<VDO_CFG_ROI2_MBY_E_LEN)-1)<<VDO_CFG_ROI2_MBY_E_POS))

/* 0x260 : vdo_h264_roi3 */
#define VDO_H264_ROI3_OFFSET                                    (0x260)
#define VDO_CFG_ROI3_MBX_S                                      VDO_CFG_ROI3_MBX_S
#define VDO_CFG_ROI3_MBX_S_POS                                  (0U)
#define VDO_CFG_ROI3_MBX_S_LEN                                  (7U)
#define VDO_CFG_ROI3_MBX_S_MSK                                  (((1U<<VDO_CFG_ROI3_MBX_S_LEN)-1)<<VDO_CFG_ROI3_MBX_S_POS)
#define VDO_CFG_ROI3_MBX_S_UMSK                                 (~(((1U<<VDO_CFG_ROI3_MBX_S_LEN)-1)<<VDO_CFG_ROI3_MBX_S_POS))
#define VDO_CFG_ROI3_MBX_E                                      VDO_CFG_ROI3_MBX_E
#define VDO_CFG_ROI3_MBX_E_POS                                  (8U)
#define VDO_CFG_ROI3_MBX_E_LEN                                  (7U)
#define VDO_CFG_ROI3_MBX_E_MSK                                  (((1U<<VDO_CFG_ROI3_MBX_E_LEN)-1)<<VDO_CFG_ROI3_MBX_E_POS)
#define VDO_CFG_ROI3_MBX_E_UMSK                                 (~(((1U<<VDO_CFG_ROI3_MBX_E_LEN)-1)<<VDO_CFG_ROI3_MBX_E_POS))
#define VDO_CFG_ROI3_MBY_S                                      VDO_CFG_ROI3_MBY_S
#define VDO_CFG_ROI3_MBY_S_POS                                  (16U)
#define VDO_CFG_ROI3_MBY_S_LEN                                  (7U)
#define VDO_CFG_ROI3_MBY_S_MSK                                  (((1U<<VDO_CFG_ROI3_MBY_S_LEN)-1)<<VDO_CFG_ROI3_MBY_S_POS)
#define VDO_CFG_ROI3_MBY_S_UMSK                                 (~(((1U<<VDO_CFG_ROI3_MBY_S_LEN)-1)<<VDO_CFG_ROI3_MBY_S_POS))
#define VDO_CFG_ROI3_MBY_E                                      VDO_CFG_ROI3_MBY_E
#define VDO_CFG_ROI3_MBY_E_POS                                  (24U)
#define VDO_CFG_ROI3_MBY_E_LEN                                  (7U)
#define VDO_CFG_ROI3_MBY_E_MSK                                  (((1U<<VDO_CFG_ROI3_MBY_E_LEN)-1)<<VDO_CFG_ROI3_MBY_E_POS)
#define VDO_CFG_ROI3_MBY_E_UMSK                                 (~(((1U<<VDO_CFG_ROI3_MBY_E_LEN)-1)<<VDO_CFG_ROI3_MBY_E_POS))

/* 0x264 : vdo_h264_roi4 */
#define VDO_H264_ROI4_OFFSET                                    (0x264)
#define VDO_CFG_ROI4_MBX_S                                      VDO_CFG_ROI4_MBX_S
#define VDO_CFG_ROI4_MBX_S_POS                                  (0U)
#define VDO_CFG_ROI4_MBX_S_LEN                                  (7U)
#define VDO_CFG_ROI4_MBX_S_MSK                                  (((1U<<VDO_CFG_ROI4_MBX_S_LEN)-1)<<VDO_CFG_ROI4_MBX_S_POS)
#define VDO_CFG_ROI4_MBX_S_UMSK                                 (~(((1U<<VDO_CFG_ROI4_MBX_S_LEN)-1)<<VDO_CFG_ROI4_MBX_S_POS))
#define VDO_CFG_ROI4_MBX_E                                      VDO_CFG_ROI4_MBX_E
#define VDO_CFG_ROI4_MBX_E_POS                                  (8U)
#define VDO_CFG_ROI4_MBX_E_LEN                                  (7U)
#define VDO_CFG_ROI4_MBX_E_MSK                                  (((1U<<VDO_CFG_ROI4_MBX_E_LEN)-1)<<VDO_CFG_ROI4_MBX_E_POS)
#define VDO_CFG_ROI4_MBX_E_UMSK                                 (~(((1U<<VDO_CFG_ROI4_MBX_E_LEN)-1)<<VDO_CFG_ROI4_MBX_E_POS))
#define VDO_CFG_ROI4_MBY_S                                      VDO_CFG_ROI4_MBY_S
#define VDO_CFG_ROI4_MBY_S_POS                                  (16U)
#define VDO_CFG_ROI4_MBY_S_LEN                                  (7U)
#define VDO_CFG_ROI4_MBY_S_MSK                                  (((1U<<VDO_CFG_ROI4_MBY_S_LEN)-1)<<VDO_CFG_ROI4_MBY_S_POS)
#define VDO_CFG_ROI4_MBY_S_UMSK                                 (~(((1U<<VDO_CFG_ROI4_MBY_S_LEN)-1)<<VDO_CFG_ROI4_MBY_S_POS))
#define VDO_CFG_ROI4_MBY_E                                      VDO_CFG_ROI4_MBY_E
#define VDO_CFG_ROI4_MBY_E_POS                                  (24U)
#define VDO_CFG_ROI4_MBY_E_LEN                                  (7U)
#define VDO_CFG_ROI4_MBY_E_MSK                                  (((1U<<VDO_CFG_ROI4_MBY_E_LEN)-1)<<VDO_CFG_ROI4_MBY_E_POS)
#define VDO_CFG_ROI4_MBY_E_UMSK                                 (~(((1U<<VDO_CFG_ROI4_MBY_E_LEN)-1)<<VDO_CFG_ROI4_MBY_E_POS))

/* 0x268 : vdo_h264_roi5 */
#define VDO_H264_ROI5_OFFSET                                    (0x268)
#define VDO_CFG_ROI5_MBX_S                                      VDO_CFG_ROI5_MBX_S
#define VDO_CFG_ROI5_MBX_S_POS                                  (0U)
#define VDO_CFG_ROI5_MBX_S_LEN                                  (7U)
#define VDO_CFG_ROI5_MBX_S_MSK                                  (((1U<<VDO_CFG_ROI5_MBX_S_LEN)-1)<<VDO_CFG_ROI5_MBX_S_POS)
#define VDO_CFG_ROI5_MBX_S_UMSK                                 (~(((1U<<VDO_CFG_ROI5_MBX_S_LEN)-1)<<VDO_CFG_ROI5_MBX_S_POS))
#define VDO_CFG_ROI5_MBX_E                                      VDO_CFG_ROI5_MBX_E
#define VDO_CFG_ROI5_MBX_E_POS                                  (8U)
#define VDO_CFG_ROI5_MBX_E_LEN                                  (7U)
#define VDO_CFG_ROI5_MBX_E_MSK                                  (((1U<<VDO_CFG_ROI5_MBX_E_LEN)-1)<<VDO_CFG_ROI5_MBX_E_POS)
#define VDO_CFG_ROI5_MBX_E_UMSK                                 (~(((1U<<VDO_CFG_ROI5_MBX_E_LEN)-1)<<VDO_CFG_ROI5_MBX_E_POS))
#define VDO_CFG_ROI5_MBY_S                                      VDO_CFG_ROI5_MBY_S
#define VDO_CFG_ROI5_MBY_S_POS                                  (16U)
#define VDO_CFG_ROI5_MBY_S_LEN                                  (7U)
#define VDO_CFG_ROI5_MBY_S_MSK                                  (((1U<<VDO_CFG_ROI5_MBY_S_LEN)-1)<<VDO_CFG_ROI5_MBY_S_POS)
#define VDO_CFG_ROI5_MBY_S_UMSK                                 (~(((1U<<VDO_CFG_ROI5_MBY_S_LEN)-1)<<VDO_CFG_ROI5_MBY_S_POS))
#define VDO_CFG_ROI5_MBY_E                                      VDO_CFG_ROI5_MBY_E
#define VDO_CFG_ROI5_MBY_E_POS                                  (24U)
#define VDO_CFG_ROI5_MBY_E_LEN                                  (7U)
#define VDO_CFG_ROI5_MBY_E_MSK                                  (((1U<<VDO_CFG_ROI5_MBY_E_LEN)-1)<<VDO_CFG_ROI5_MBY_E_POS)
#define VDO_CFG_ROI5_MBY_E_UMSK                                 (~(((1U<<VDO_CFG_ROI5_MBY_E_LEN)-1)<<VDO_CFG_ROI5_MBY_E_POS))

/* 0x26c : vdo_h264_roi6 */
#define VDO_H264_ROI6_OFFSET                                    (0x26c)
#define VDO_CFG_ROI6_MBX_S                                      VDO_CFG_ROI6_MBX_S
#define VDO_CFG_ROI6_MBX_S_POS                                  (0U)
#define VDO_CFG_ROI6_MBX_S_LEN                                  (7U)
#define VDO_CFG_ROI6_MBX_S_MSK                                  (((1U<<VDO_CFG_ROI6_MBX_S_LEN)-1)<<VDO_CFG_ROI6_MBX_S_POS)
#define VDO_CFG_ROI6_MBX_S_UMSK                                 (~(((1U<<VDO_CFG_ROI6_MBX_S_LEN)-1)<<VDO_CFG_ROI6_MBX_S_POS))
#define VDO_CFG_ROI6_MBX_E                                      VDO_CFG_ROI6_MBX_E
#define VDO_CFG_ROI6_MBX_E_POS                                  (8U)
#define VDO_CFG_ROI6_MBX_E_LEN                                  (7U)
#define VDO_CFG_ROI6_MBX_E_MSK                                  (((1U<<VDO_CFG_ROI6_MBX_E_LEN)-1)<<VDO_CFG_ROI6_MBX_E_POS)
#define VDO_CFG_ROI6_MBX_E_UMSK                                 (~(((1U<<VDO_CFG_ROI6_MBX_E_LEN)-1)<<VDO_CFG_ROI6_MBX_E_POS))
#define VDO_CFG_ROI6_MBY_S                                      VDO_CFG_ROI6_MBY_S
#define VDO_CFG_ROI6_MBY_S_POS                                  (16U)
#define VDO_CFG_ROI6_MBY_S_LEN                                  (7U)
#define VDO_CFG_ROI6_MBY_S_MSK                                  (((1U<<VDO_CFG_ROI6_MBY_S_LEN)-1)<<VDO_CFG_ROI6_MBY_S_POS)
#define VDO_CFG_ROI6_MBY_S_UMSK                                 (~(((1U<<VDO_CFG_ROI6_MBY_S_LEN)-1)<<VDO_CFG_ROI6_MBY_S_POS))
#define VDO_CFG_ROI6_MBY_E                                      VDO_CFG_ROI6_MBY_E
#define VDO_CFG_ROI6_MBY_E_POS                                  (24U)
#define VDO_CFG_ROI6_MBY_E_LEN                                  (7U)
#define VDO_CFG_ROI6_MBY_E_MSK                                  (((1U<<VDO_CFG_ROI6_MBY_E_LEN)-1)<<VDO_CFG_ROI6_MBY_E_POS)
#define VDO_CFG_ROI6_MBY_E_UMSK                                 (~(((1U<<VDO_CFG_ROI6_MBY_E_LEN)-1)<<VDO_CFG_ROI6_MBY_E_POS))

/* 0x270 : vdo_h264_roi7 */
#define VDO_H264_ROI7_OFFSET                                    (0x270)
#define VDO_CFG_ROI7_MBX_S                                      VDO_CFG_ROI7_MBX_S
#define VDO_CFG_ROI7_MBX_S_POS                                  (0U)
#define VDO_CFG_ROI7_MBX_S_LEN                                  (7U)
#define VDO_CFG_ROI7_MBX_S_MSK                                  (((1U<<VDO_CFG_ROI7_MBX_S_LEN)-1)<<VDO_CFG_ROI7_MBX_S_POS)
#define VDO_CFG_ROI7_MBX_S_UMSK                                 (~(((1U<<VDO_CFG_ROI7_MBX_S_LEN)-1)<<VDO_CFG_ROI7_MBX_S_POS))
#define VDO_CFG_ROI7_MBX_E                                      VDO_CFG_ROI7_MBX_E
#define VDO_CFG_ROI7_MBX_E_POS                                  (8U)
#define VDO_CFG_ROI7_MBX_E_LEN                                  (7U)
#define VDO_CFG_ROI7_MBX_E_MSK                                  (((1U<<VDO_CFG_ROI7_MBX_E_LEN)-1)<<VDO_CFG_ROI7_MBX_E_POS)
#define VDO_CFG_ROI7_MBX_E_UMSK                                 (~(((1U<<VDO_CFG_ROI7_MBX_E_LEN)-1)<<VDO_CFG_ROI7_MBX_E_POS))
#define VDO_CFG_ROI7_MBY_S                                      VDO_CFG_ROI7_MBY_S
#define VDO_CFG_ROI7_MBY_S_POS                                  (16U)
#define VDO_CFG_ROI7_MBY_S_LEN                                  (7U)
#define VDO_CFG_ROI7_MBY_S_MSK                                  (((1U<<VDO_CFG_ROI7_MBY_S_LEN)-1)<<VDO_CFG_ROI7_MBY_S_POS)
#define VDO_CFG_ROI7_MBY_S_UMSK                                 (~(((1U<<VDO_CFG_ROI7_MBY_S_LEN)-1)<<VDO_CFG_ROI7_MBY_S_POS))
#define VDO_CFG_ROI7_MBY_E                                      VDO_CFG_ROI7_MBY_E
#define VDO_CFG_ROI7_MBY_E_POS                                  (24U)
#define VDO_CFG_ROI7_MBY_E_LEN                                  (7U)
#define VDO_CFG_ROI7_MBY_E_MSK                                  (((1U<<VDO_CFG_ROI7_MBY_E_LEN)-1)<<VDO_CFG_ROI7_MBY_E_POS)
#define VDO_CFG_ROI7_MBY_E_UMSK                                 (~(((1U<<VDO_CFG_ROI7_MBY_E_LEN)-1)<<VDO_CFG_ROI7_MBY_E_POS))

/* 0x274 : vdo_h264_s_roi_mode */
#define VDO_H264_S_ROI_MODE_OFFSET                              (0x274)
#define VDO_CFG_S_ROI_EN                                        VDO_CFG_S_ROI_EN
#define VDO_CFG_S_ROI_EN_POS                                    (0U)
#define VDO_CFG_S_ROI_EN_LEN                                    (8U)
#define VDO_CFG_S_ROI_EN_MSK                                    (((1U<<VDO_CFG_S_ROI_EN_LEN)-1)<<VDO_CFG_S_ROI_EN_POS)
#define VDO_CFG_S_ROI_EN_UMSK                                   (~(((1U<<VDO_CFG_S_ROI_EN_LEN)-1)<<VDO_CFG_S_ROI_EN_POS))
#define VDO_CFG_S_ROI_UPD                                       VDO_CFG_S_ROI_UPD
#define VDO_CFG_S_ROI_UPD_POS                                   (8U)
#define VDO_CFG_S_ROI_UPD_LEN                                   (1U)
#define VDO_CFG_S_ROI_UPD_MSK                                   (((1U<<VDO_CFG_S_ROI_UPD_LEN)-1)<<VDO_CFG_S_ROI_UPD_POS)
#define VDO_CFG_S_ROI_UPD_UMSK                                  (~(((1U<<VDO_CFG_S_ROI_UPD_LEN)-1)<<VDO_CFG_S_ROI_UPD_POS))

/* 0x278 : vdo_h264_s_roi_bit */
#define VDO_H264_S_ROI_BIT_OFFSET                               (0x278)
#define VDO_CFG_S_PBIT_RATIO                                    VDO_CFG_S_PBIT_RATIO
#define VDO_CFG_S_PBIT_RATIO_POS                                (0U)
#define VDO_CFG_S_PBIT_RATIO_LEN                                (13U)
#define VDO_CFG_S_PBIT_RATIO_MSK                                (((1U<<VDO_CFG_S_PBIT_RATIO_LEN)-1)<<VDO_CFG_S_PBIT_RATIO_POS)
#define VDO_CFG_S_PBIT_RATIO_UMSK                               (~(((1U<<VDO_CFG_S_PBIT_RATIO_LEN)-1)<<VDO_CFG_S_PBIT_RATIO_POS))
#define VDO_CFG_S_IBIT_RATIO                                    VDO_CFG_S_IBIT_RATIO
#define VDO_CFG_S_IBIT_RATIO_POS                                (13U)
#define VDO_CFG_S_IBIT_RATIO_LEN                                (13U)
#define VDO_CFG_S_IBIT_RATIO_MSK                                (((1U<<VDO_CFG_S_IBIT_RATIO_LEN)-1)<<VDO_CFG_S_IBIT_RATIO_POS)
#define VDO_CFG_S_IBIT_RATIO_UMSK                               (~(((1U<<VDO_CFG_S_IBIT_RATIO_LEN)-1)<<VDO_CFG_S_IBIT_RATIO_POS))
#define VDO_CFG_S_ITHRE                                         VDO_CFG_S_ITHRE
#define VDO_CFG_S_ITHRE_POS                                     (26U)
#define VDO_CFG_S_ITHRE_LEN                                     (6U)
#define VDO_CFG_S_ITHRE_MSK                                     (((1U<<VDO_CFG_S_ITHRE_LEN)-1)<<VDO_CFG_S_ITHRE_POS)
#define VDO_CFG_S_ITHRE_UMSK                                    (~(((1U<<VDO_CFG_S_ITHRE_LEN)-1)<<VDO_CFG_S_ITHRE_POS))

/* 0x27c : vdo_h264_s_roi_qptune */
#define VDO_H264_S_ROI_QPTUNE_OFFSET                            (0x27c)
#define VDO_CFG_S_PQP_DECR                                      VDO_CFG_S_PQP_DECR
#define VDO_CFG_S_PQP_DECR_POS                                  (0U)
#define VDO_CFG_S_PQP_DECR_LEN                                  (6U)
#define VDO_CFG_S_PQP_DECR_MSK                                  (((1U<<VDO_CFG_S_PQP_DECR_LEN)-1)<<VDO_CFG_S_PQP_DECR_POS)
#define VDO_CFG_S_PQP_DECR_UMSK                                 (~(((1U<<VDO_CFG_S_PQP_DECR_LEN)-1)<<VDO_CFG_S_PQP_DECR_POS))
#define VDO_CFG_S_IQP_DECR                                      VDO_CFG_S_IQP_DECR
#define VDO_CFG_S_IQP_DECR_POS                                  (8U)
#define VDO_CFG_S_IQP_DECR_LEN                                  (6U)
#define VDO_CFG_S_IQP_DECR_MSK                                  (((1U<<VDO_CFG_S_IQP_DECR_LEN)-1)<<VDO_CFG_S_IQP_DECR_POS)
#define VDO_CFG_S_IQP_DECR_UMSK                                 (~(((1U<<VDO_CFG_S_IQP_DECR_LEN)-1)<<VDO_CFG_S_IQP_DECR_POS))
#define VDO_CFG_S_N2R_QP_DECR                                   VDO_CFG_S_N2R_QP_DECR
#define VDO_CFG_S_N2R_QP_DECR_POS                               (16U)
#define VDO_CFG_S_N2R_QP_DECR_LEN                               (6U)
#define VDO_CFG_S_N2R_QP_DECR_MSK                               (((1U<<VDO_CFG_S_N2R_QP_DECR_LEN)-1)<<VDO_CFG_S_N2R_QP_DECR_POS)
#define VDO_CFG_S_N2R_QP_DECR_UMSK                              (~(((1U<<VDO_CFG_S_N2R_QP_DECR_LEN)-1)<<VDO_CFG_S_N2R_QP_DECR_POS))
#define VDO_CFG_S_FIXQP                                         VDO_CFG_S_FIXQP
#define VDO_CFG_S_FIXQP_POS                                     (24U)
#define VDO_CFG_S_FIXQP_LEN                                     (6U)
#define VDO_CFG_S_FIXQP_MSK                                     (((1U<<VDO_CFG_S_FIXQP_LEN)-1)<<VDO_CFG_S_FIXQP_POS)
#define VDO_CFG_S_FIXQP_UMSK                                    (~(((1U<<VDO_CFG_S_FIXQP_LEN)-1)<<VDO_CFG_S_FIXQP_POS))

/* 0x280 : vdo_h264_s_roi_bittune */
#define VDO_H264_S_ROI_BITTUNE_OFFSET                           (0x280)
#define VDO_CFG_S_ROI_PBIT_OFST                                 VDO_CFG_S_ROI_PBIT_OFST
#define VDO_CFG_S_ROI_PBIT_OFST_POS                             (0U)
#define VDO_CFG_S_ROI_PBIT_OFST_LEN                             (5U)
#define VDO_CFG_S_ROI_PBIT_OFST_MSK                             (((1U<<VDO_CFG_S_ROI_PBIT_OFST_LEN)-1)<<VDO_CFG_S_ROI_PBIT_OFST_POS)
#define VDO_CFG_S_ROI_PBIT_OFST_UMSK                            (~(((1U<<VDO_CFG_S_ROI_PBIT_OFST_LEN)-1)<<VDO_CFG_S_ROI_PBIT_OFST_POS))
#define VDO_CFG_S_ROI_IBIT_OFST                                 VDO_CFG_S_ROI_IBIT_OFST
#define VDO_CFG_S_ROI_IBIT_OFST_POS                             (8U)
#define VDO_CFG_S_ROI_IBIT_OFST_LEN                             (8U)
#define VDO_CFG_S_ROI_IBIT_OFST_MSK                             (((1U<<VDO_CFG_S_ROI_IBIT_OFST_LEN)-1)<<VDO_CFG_S_ROI_IBIT_OFST_POS)
#define VDO_CFG_S_ROI_IBIT_OFST_UMSK                            (~(((1U<<VDO_CFG_S_ROI_IBIT_OFST_LEN)-1)<<VDO_CFG_S_ROI_IBIT_OFST_POS))
#define VDO_CFG_S_NROI_PBIT_OFST                                VDO_CFG_S_NROI_PBIT_OFST
#define VDO_CFG_S_NROI_PBIT_OFST_POS                            (16U)
#define VDO_CFG_S_NROI_PBIT_OFST_LEN                            (5U)
#define VDO_CFG_S_NROI_PBIT_OFST_MSK                            (((1U<<VDO_CFG_S_NROI_PBIT_OFST_LEN)-1)<<VDO_CFG_S_NROI_PBIT_OFST_POS)
#define VDO_CFG_S_NROI_PBIT_OFST_UMSK                           (~(((1U<<VDO_CFG_S_NROI_PBIT_OFST_LEN)-1)<<VDO_CFG_S_NROI_PBIT_OFST_POS))
#define VDO_CFG_S_NROI_IBIT_OFST                                VDO_CFG_S_NROI_IBIT_OFST
#define VDO_CFG_S_NROI_IBIT_OFST_POS                            (24U)
#define VDO_CFG_S_NROI_IBIT_OFST_LEN                            (8U)
#define VDO_CFG_S_NROI_IBIT_OFST_MSK                            (((1U<<VDO_CFG_S_NROI_IBIT_OFST_LEN)-1)<<VDO_CFG_S_NROI_IBIT_OFST_POS)
#define VDO_CFG_S_NROI_IBIT_OFST_UMSK                           (~(((1U<<VDO_CFG_S_NROI_IBIT_OFST_LEN)-1)<<VDO_CFG_S_NROI_IBIT_OFST_POS))

/* 0x284 : vdo_h264_s_roi0 */
#define VDO_H264_S_ROI0_OFFSET                                  (0x284)
#define VDO_CFG_S_ROI0_MBX_S                                    VDO_CFG_S_ROI0_MBX_S
#define VDO_CFG_S_ROI0_MBX_S_POS                                (0U)
#define VDO_CFG_S_ROI0_MBX_S_LEN                                (7U)
#define VDO_CFG_S_ROI0_MBX_S_MSK                                (((1U<<VDO_CFG_S_ROI0_MBX_S_LEN)-1)<<VDO_CFG_S_ROI0_MBX_S_POS)
#define VDO_CFG_S_ROI0_MBX_S_UMSK                               (~(((1U<<VDO_CFG_S_ROI0_MBX_S_LEN)-1)<<VDO_CFG_S_ROI0_MBX_S_POS))
#define VDO_CFG_S_ROI0_MBX_E                                    VDO_CFG_S_ROI0_MBX_E
#define VDO_CFG_S_ROI0_MBX_E_POS                                (8U)
#define VDO_CFG_S_ROI0_MBX_E_LEN                                (7U)
#define VDO_CFG_S_ROI0_MBX_E_MSK                                (((1U<<VDO_CFG_S_ROI0_MBX_E_LEN)-1)<<VDO_CFG_S_ROI0_MBX_E_POS)
#define VDO_CFG_S_ROI0_MBX_E_UMSK                               (~(((1U<<VDO_CFG_S_ROI0_MBX_E_LEN)-1)<<VDO_CFG_S_ROI0_MBX_E_POS))
#define VDO_CFG_S_ROI0_MBY_S                                    VDO_CFG_S_ROI0_MBY_S
#define VDO_CFG_S_ROI0_MBY_S_POS                                (16U)
#define VDO_CFG_S_ROI0_MBY_S_LEN                                (7U)
#define VDO_CFG_S_ROI0_MBY_S_MSK                                (((1U<<VDO_CFG_S_ROI0_MBY_S_LEN)-1)<<VDO_CFG_S_ROI0_MBY_S_POS)
#define VDO_CFG_S_ROI0_MBY_S_UMSK                               (~(((1U<<VDO_CFG_S_ROI0_MBY_S_LEN)-1)<<VDO_CFG_S_ROI0_MBY_S_POS))
#define VDO_CFG_S_ROI0_MBY_E                                    VDO_CFG_S_ROI0_MBY_E
#define VDO_CFG_S_ROI0_MBY_E_POS                                (24U)
#define VDO_CFG_S_ROI0_MBY_E_LEN                                (7U)
#define VDO_CFG_S_ROI0_MBY_E_MSK                                (((1U<<VDO_CFG_S_ROI0_MBY_E_LEN)-1)<<VDO_CFG_S_ROI0_MBY_E_POS)
#define VDO_CFG_S_ROI0_MBY_E_UMSK                               (~(((1U<<VDO_CFG_S_ROI0_MBY_E_LEN)-1)<<VDO_CFG_S_ROI0_MBY_E_POS))

/* 0x288 : vdo_h264_s_roi1 */
#define VDO_H264_S_ROI1_OFFSET                                  (0x288)
#define VDO_CFG_S_ROI1_MBX_S                                    VDO_CFG_S_ROI1_MBX_S
#define VDO_CFG_S_ROI1_MBX_S_POS                                (0U)
#define VDO_CFG_S_ROI1_MBX_S_LEN                                (7U)
#define VDO_CFG_S_ROI1_MBX_S_MSK                                (((1U<<VDO_CFG_S_ROI1_MBX_S_LEN)-1)<<VDO_CFG_S_ROI1_MBX_S_POS)
#define VDO_CFG_S_ROI1_MBX_S_UMSK                               (~(((1U<<VDO_CFG_S_ROI1_MBX_S_LEN)-1)<<VDO_CFG_S_ROI1_MBX_S_POS))
#define VDO_CFG_S_ROI1_MBX_E                                    VDO_CFG_S_ROI1_MBX_E
#define VDO_CFG_S_ROI1_MBX_E_POS                                (8U)
#define VDO_CFG_S_ROI1_MBX_E_LEN                                (7U)
#define VDO_CFG_S_ROI1_MBX_E_MSK                                (((1U<<VDO_CFG_S_ROI1_MBX_E_LEN)-1)<<VDO_CFG_S_ROI1_MBX_E_POS)
#define VDO_CFG_S_ROI1_MBX_E_UMSK                               (~(((1U<<VDO_CFG_S_ROI1_MBX_E_LEN)-1)<<VDO_CFG_S_ROI1_MBX_E_POS))
#define VDO_CFG_S_ROI1_MBY_S                                    VDO_CFG_S_ROI1_MBY_S
#define VDO_CFG_S_ROI1_MBY_S_POS                                (16U)
#define VDO_CFG_S_ROI1_MBY_S_LEN                                (7U)
#define VDO_CFG_S_ROI1_MBY_S_MSK                                (((1U<<VDO_CFG_S_ROI1_MBY_S_LEN)-1)<<VDO_CFG_S_ROI1_MBY_S_POS)
#define VDO_CFG_S_ROI1_MBY_S_UMSK                               (~(((1U<<VDO_CFG_S_ROI1_MBY_S_LEN)-1)<<VDO_CFG_S_ROI1_MBY_S_POS))
#define VDO_CFG_S_ROI1_MBY_E                                    VDO_CFG_S_ROI1_MBY_E
#define VDO_CFG_S_ROI1_MBY_E_POS                                (24U)
#define VDO_CFG_S_ROI1_MBY_E_LEN                                (7U)
#define VDO_CFG_S_ROI1_MBY_E_MSK                                (((1U<<VDO_CFG_S_ROI1_MBY_E_LEN)-1)<<VDO_CFG_S_ROI1_MBY_E_POS)
#define VDO_CFG_S_ROI1_MBY_E_UMSK                               (~(((1U<<VDO_CFG_S_ROI1_MBY_E_LEN)-1)<<VDO_CFG_S_ROI1_MBY_E_POS))

/* 0x28c : vdo_h264_s_roi2 */
#define VDO_H264_S_ROI2_OFFSET                                  (0x28c)
#define VDO_CFG_S_ROI2_MBX_S                                    VDO_CFG_S_ROI2_MBX_S
#define VDO_CFG_S_ROI2_MBX_S_POS                                (0U)
#define VDO_CFG_S_ROI2_MBX_S_LEN                                (7U)
#define VDO_CFG_S_ROI2_MBX_S_MSK                                (((1U<<VDO_CFG_S_ROI2_MBX_S_LEN)-1)<<VDO_CFG_S_ROI2_MBX_S_POS)
#define VDO_CFG_S_ROI2_MBX_S_UMSK                               (~(((1U<<VDO_CFG_S_ROI2_MBX_S_LEN)-1)<<VDO_CFG_S_ROI2_MBX_S_POS))
#define VDO_CFG_S_ROI2_MBX_E                                    VDO_CFG_S_ROI2_MBX_E
#define VDO_CFG_S_ROI2_MBX_E_POS                                (8U)
#define VDO_CFG_S_ROI2_MBX_E_LEN                                (7U)
#define VDO_CFG_S_ROI2_MBX_E_MSK                                (((1U<<VDO_CFG_S_ROI2_MBX_E_LEN)-1)<<VDO_CFG_S_ROI2_MBX_E_POS)
#define VDO_CFG_S_ROI2_MBX_E_UMSK                               (~(((1U<<VDO_CFG_S_ROI2_MBX_E_LEN)-1)<<VDO_CFG_S_ROI2_MBX_E_POS))
#define VDO_CFG_S_ROI2_MBY_S                                    VDO_CFG_S_ROI2_MBY_S
#define VDO_CFG_S_ROI2_MBY_S_POS                                (16U)
#define VDO_CFG_S_ROI2_MBY_S_LEN                                (7U)
#define VDO_CFG_S_ROI2_MBY_S_MSK                                (((1U<<VDO_CFG_S_ROI2_MBY_S_LEN)-1)<<VDO_CFG_S_ROI2_MBY_S_POS)
#define VDO_CFG_S_ROI2_MBY_S_UMSK                               (~(((1U<<VDO_CFG_S_ROI2_MBY_S_LEN)-1)<<VDO_CFG_S_ROI2_MBY_S_POS))
#define VDO_CFG_S_ROI2_MBY_E                                    VDO_CFG_S_ROI2_MBY_E
#define VDO_CFG_S_ROI2_MBY_E_POS                                (24U)
#define VDO_CFG_S_ROI2_MBY_E_LEN                                (7U)
#define VDO_CFG_S_ROI2_MBY_E_MSK                                (((1U<<VDO_CFG_S_ROI2_MBY_E_LEN)-1)<<VDO_CFG_S_ROI2_MBY_E_POS)
#define VDO_CFG_S_ROI2_MBY_E_UMSK                               (~(((1U<<VDO_CFG_S_ROI2_MBY_E_LEN)-1)<<VDO_CFG_S_ROI2_MBY_E_POS))

/* 0x290 : vdo_h264_s_roi3 */
#define VDO_H264_S_ROI3_OFFSET                                  (0x290)
#define VDO_CFG_S_ROI3_MBX_S                                    VDO_CFG_S_ROI3_MBX_S
#define VDO_CFG_S_ROI3_MBX_S_POS                                (0U)
#define VDO_CFG_S_ROI3_MBX_S_LEN                                (7U)
#define VDO_CFG_S_ROI3_MBX_S_MSK                                (((1U<<VDO_CFG_S_ROI3_MBX_S_LEN)-1)<<VDO_CFG_S_ROI3_MBX_S_POS)
#define VDO_CFG_S_ROI3_MBX_S_UMSK                               (~(((1U<<VDO_CFG_S_ROI3_MBX_S_LEN)-1)<<VDO_CFG_S_ROI3_MBX_S_POS))
#define VDO_CFG_S_ROI3_MBX_E                                    VDO_CFG_S_ROI3_MBX_E
#define VDO_CFG_S_ROI3_MBX_E_POS                                (8U)
#define VDO_CFG_S_ROI3_MBX_E_LEN                                (7U)
#define VDO_CFG_S_ROI3_MBX_E_MSK                                (((1U<<VDO_CFG_S_ROI3_MBX_E_LEN)-1)<<VDO_CFG_S_ROI3_MBX_E_POS)
#define VDO_CFG_S_ROI3_MBX_E_UMSK                               (~(((1U<<VDO_CFG_S_ROI3_MBX_E_LEN)-1)<<VDO_CFG_S_ROI3_MBX_E_POS))
#define VDO_CFG_S_ROI3_MBY_S                                    VDO_CFG_S_ROI3_MBY_S
#define VDO_CFG_S_ROI3_MBY_S_POS                                (16U)
#define VDO_CFG_S_ROI3_MBY_S_LEN                                (7U)
#define VDO_CFG_S_ROI3_MBY_S_MSK                                (((1U<<VDO_CFG_S_ROI3_MBY_S_LEN)-1)<<VDO_CFG_S_ROI3_MBY_S_POS)
#define VDO_CFG_S_ROI3_MBY_S_UMSK                               (~(((1U<<VDO_CFG_S_ROI3_MBY_S_LEN)-1)<<VDO_CFG_S_ROI3_MBY_S_POS))
#define VDO_CFG_S_ROI3_MBY_E                                    VDO_CFG_S_ROI3_MBY_E
#define VDO_CFG_S_ROI3_MBY_E_POS                                (24U)
#define VDO_CFG_S_ROI3_MBY_E_LEN                                (7U)
#define VDO_CFG_S_ROI3_MBY_E_MSK                                (((1U<<VDO_CFG_S_ROI3_MBY_E_LEN)-1)<<VDO_CFG_S_ROI3_MBY_E_POS)
#define VDO_CFG_S_ROI3_MBY_E_UMSK                               (~(((1U<<VDO_CFG_S_ROI3_MBY_E_LEN)-1)<<VDO_CFG_S_ROI3_MBY_E_POS))

/* 0x294 : vdo_h264_s_roi4 */
#define VDO_H264_S_ROI4_OFFSET                                  (0x294)
#define VDO_CFG_S_ROI4_MBX_S                                    VDO_CFG_S_ROI4_MBX_S
#define VDO_CFG_S_ROI4_MBX_S_POS                                (0U)
#define VDO_CFG_S_ROI4_MBX_S_LEN                                (7U)
#define VDO_CFG_S_ROI4_MBX_S_MSK                                (((1U<<VDO_CFG_S_ROI4_MBX_S_LEN)-1)<<VDO_CFG_S_ROI4_MBX_S_POS)
#define VDO_CFG_S_ROI4_MBX_S_UMSK                               (~(((1U<<VDO_CFG_S_ROI4_MBX_S_LEN)-1)<<VDO_CFG_S_ROI4_MBX_S_POS))
#define VDO_CFG_S_ROI4_MBX_E                                    VDO_CFG_S_ROI4_MBX_E
#define VDO_CFG_S_ROI4_MBX_E_POS                                (8U)
#define VDO_CFG_S_ROI4_MBX_E_LEN                                (7U)
#define VDO_CFG_S_ROI4_MBX_E_MSK                                (((1U<<VDO_CFG_S_ROI4_MBX_E_LEN)-1)<<VDO_CFG_S_ROI4_MBX_E_POS)
#define VDO_CFG_S_ROI4_MBX_E_UMSK                               (~(((1U<<VDO_CFG_S_ROI4_MBX_E_LEN)-1)<<VDO_CFG_S_ROI4_MBX_E_POS))
#define VDO_CFG_S_ROI4_MBY_S                                    VDO_CFG_S_ROI4_MBY_S
#define VDO_CFG_S_ROI4_MBY_S_POS                                (16U)
#define VDO_CFG_S_ROI4_MBY_S_LEN                                (7U)
#define VDO_CFG_S_ROI4_MBY_S_MSK                                (((1U<<VDO_CFG_S_ROI4_MBY_S_LEN)-1)<<VDO_CFG_S_ROI4_MBY_S_POS)
#define VDO_CFG_S_ROI4_MBY_S_UMSK                               (~(((1U<<VDO_CFG_S_ROI4_MBY_S_LEN)-1)<<VDO_CFG_S_ROI4_MBY_S_POS))
#define VDO_CFG_S_ROI4_MBY_E                                    VDO_CFG_S_ROI4_MBY_E
#define VDO_CFG_S_ROI4_MBY_E_POS                                (24U)
#define VDO_CFG_S_ROI4_MBY_E_LEN                                (7U)
#define VDO_CFG_S_ROI4_MBY_E_MSK                                (((1U<<VDO_CFG_S_ROI4_MBY_E_LEN)-1)<<VDO_CFG_S_ROI4_MBY_E_POS)
#define VDO_CFG_S_ROI4_MBY_E_UMSK                               (~(((1U<<VDO_CFG_S_ROI4_MBY_E_LEN)-1)<<VDO_CFG_S_ROI4_MBY_E_POS))

/* 0x298 : vdo_h264_s_roi5 */
#define VDO_H264_S_ROI5_OFFSET                                  (0x298)
#define VDO_CFG_S_ROI5_MBX_S                                    VDO_CFG_S_ROI5_MBX_S
#define VDO_CFG_S_ROI5_MBX_S_POS                                (0U)
#define VDO_CFG_S_ROI5_MBX_S_LEN                                (7U)
#define VDO_CFG_S_ROI5_MBX_S_MSK                                (((1U<<VDO_CFG_S_ROI5_MBX_S_LEN)-1)<<VDO_CFG_S_ROI5_MBX_S_POS)
#define VDO_CFG_S_ROI5_MBX_S_UMSK                               (~(((1U<<VDO_CFG_S_ROI5_MBX_S_LEN)-1)<<VDO_CFG_S_ROI5_MBX_S_POS))
#define VDO_CFG_S_ROI5_MBX_E                                    VDO_CFG_S_ROI5_MBX_E
#define VDO_CFG_S_ROI5_MBX_E_POS                                (8U)
#define VDO_CFG_S_ROI5_MBX_E_LEN                                (7U)
#define VDO_CFG_S_ROI5_MBX_E_MSK                                (((1U<<VDO_CFG_S_ROI5_MBX_E_LEN)-1)<<VDO_CFG_S_ROI5_MBX_E_POS)
#define VDO_CFG_S_ROI5_MBX_E_UMSK                               (~(((1U<<VDO_CFG_S_ROI5_MBX_E_LEN)-1)<<VDO_CFG_S_ROI5_MBX_E_POS))
#define VDO_CFG_S_ROI5_MBY_S                                    VDO_CFG_S_ROI5_MBY_S
#define VDO_CFG_S_ROI5_MBY_S_POS                                (16U)
#define VDO_CFG_S_ROI5_MBY_S_LEN                                (7U)
#define VDO_CFG_S_ROI5_MBY_S_MSK                                (((1U<<VDO_CFG_S_ROI5_MBY_S_LEN)-1)<<VDO_CFG_S_ROI5_MBY_S_POS)
#define VDO_CFG_S_ROI5_MBY_S_UMSK                               (~(((1U<<VDO_CFG_S_ROI5_MBY_S_LEN)-1)<<VDO_CFG_S_ROI5_MBY_S_POS))
#define VDO_CFG_S_ROI5_MBY_E                                    VDO_CFG_S_ROI5_MBY_E
#define VDO_CFG_S_ROI5_MBY_E_POS                                (24U)
#define VDO_CFG_S_ROI5_MBY_E_LEN                                (7U)
#define VDO_CFG_S_ROI5_MBY_E_MSK                                (((1U<<VDO_CFG_S_ROI5_MBY_E_LEN)-1)<<VDO_CFG_S_ROI5_MBY_E_POS)
#define VDO_CFG_S_ROI5_MBY_E_UMSK                               (~(((1U<<VDO_CFG_S_ROI5_MBY_E_LEN)-1)<<VDO_CFG_S_ROI5_MBY_E_POS))

/* 0x29c : vdo_h264_s_roi6 */
#define VDO_H264_S_ROI6_OFFSET                                  (0x29c)
#define VDO_CFG_S_ROI6_MBX_S                                    VDO_CFG_S_ROI6_MBX_S
#define VDO_CFG_S_ROI6_MBX_S_POS                                (0U)
#define VDO_CFG_S_ROI6_MBX_S_LEN                                (7U)
#define VDO_CFG_S_ROI6_MBX_S_MSK                                (((1U<<VDO_CFG_S_ROI6_MBX_S_LEN)-1)<<VDO_CFG_S_ROI6_MBX_S_POS)
#define VDO_CFG_S_ROI6_MBX_S_UMSK                               (~(((1U<<VDO_CFG_S_ROI6_MBX_S_LEN)-1)<<VDO_CFG_S_ROI6_MBX_S_POS))
#define VDO_CFG_S_ROI6_MBX_E                                    VDO_CFG_S_ROI6_MBX_E
#define VDO_CFG_S_ROI6_MBX_E_POS                                (8U)
#define VDO_CFG_S_ROI6_MBX_E_LEN                                (7U)
#define VDO_CFG_S_ROI6_MBX_E_MSK                                (((1U<<VDO_CFG_S_ROI6_MBX_E_LEN)-1)<<VDO_CFG_S_ROI6_MBX_E_POS)
#define VDO_CFG_S_ROI6_MBX_E_UMSK                               (~(((1U<<VDO_CFG_S_ROI6_MBX_E_LEN)-1)<<VDO_CFG_S_ROI6_MBX_E_POS))
#define VDO_CFG_S_ROI6_MBY_S                                    VDO_CFG_S_ROI6_MBY_S
#define VDO_CFG_S_ROI6_MBY_S_POS                                (16U)
#define VDO_CFG_S_ROI6_MBY_S_LEN                                (7U)
#define VDO_CFG_S_ROI6_MBY_S_MSK                                (((1U<<VDO_CFG_S_ROI6_MBY_S_LEN)-1)<<VDO_CFG_S_ROI6_MBY_S_POS)
#define VDO_CFG_S_ROI6_MBY_S_UMSK                               (~(((1U<<VDO_CFG_S_ROI6_MBY_S_LEN)-1)<<VDO_CFG_S_ROI6_MBY_S_POS))
#define VDO_CFG_S_ROI6_MBY_E                                    VDO_CFG_S_ROI6_MBY_E
#define VDO_CFG_S_ROI6_MBY_E_POS                                (24U)
#define VDO_CFG_S_ROI6_MBY_E_LEN                                (7U)
#define VDO_CFG_S_ROI6_MBY_E_MSK                                (((1U<<VDO_CFG_S_ROI6_MBY_E_LEN)-1)<<VDO_CFG_S_ROI6_MBY_E_POS)
#define VDO_CFG_S_ROI6_MBY_E_UMSK                               (~(((1U<<VDO_CFG_S_ROI6_MBY_E_LEN)-1)<<VDO_CFG_S_ROI6_MBY_E_POS))

/* 0x300 : vdo_h264_s_roi7 */
#define VDO_H264_S_ROI7_OFFSET                                  (0x300)
#define VDO_CFG_S_ROI7_MBX_S                                    VDO_CFG_S_ROI7_MBX_S
#define VDO_CFG_S_ROI7_MBX_S_POS                                (0U)
#define VDO_CFG_S_ROI7_MBX_S_LEN                                (7U)
#define VDO_CFG_S_ROI7_MBX_S_MSK                                (((1U<<VDO_CFG_S_ROI7_MBX_S_LEN)-1)<<VDO_CFG_S_ROI7_MBX_S_POS)
#define VDO_CFG_S_ROI7_MBX_S_UMSK                               (~(((1U<<VDO_CFG_S_ROI7_MBX_S_LEN)-1)<<VDO_CFG_S_ROI7_MBX_S_POS))
#define VDO_CFG_S_ROI7_MBX_E                                    VDO_CFG_S_ROI7_MBX_E
#define VDO_CFG_S_ROI7_MBX_E_POS                                (8U)
#define VDO_CFG_S_ROI7_MBX_E_LEN                                (7U)
#define VDO_CFG_S_ROI7_MBX_E_MSK                                (((1U<<VDO_CFG_S_ROI7_MBX_E_LEN)-1)<<VDO_CFG_S_ROI7_MBX_E_POS)
#define VDO_CFG_S_ROI7_MBX_E_UMSK                               (~(((1U<<VDO_CFG_S_ROI7_MBX_E_LEN)-1)<<VDO_CFG_S_ROI7_MBX_E_POS))
#define VDO_CFG_S_ROI7_MBY_S                                    VDO_CFG_S_ROI7_MBY_S
#define VDO_CFG_S_ROI7_MBY_S_POS                                (16U)
#define VDO_CFG_S_ROI7_MBY_S_LEN                                (7U)
#define VDO_CFG_S_ROI7_MBY_S_MSK                                (((1U<<VDO_CFG_S_ROI7_MBY_S_LEN)-1)<<VDO_CFG_S_ROI7_MBY_S_POS)
#define VDO_CFG_S_ROI7_MBY_S_UMSK                               (~(((1U<<VDO_CFG_S_ROI7_MBY_S_LEN)-1)<<VDO_CFG_S_ROI7_MBY_S_POS))
#define VDO_CFG_S_ROI7_MBY_E                                    VDO_CFG_S_ROI7_MBY_E
#define VDO_CFG_S_ROI7_MBY_E_POS                                (24U)
#define VDO_CFG_S_ROI7_MBY_E_LEN                                (7U)
#define VDO_CFG_S_ROI7_MBY_E_MSK                                (((1U<<VDO_CFG_S_ROI7_MBY_E_LEN)-1)<<VDO_CFG_S_ROI7_MBY_E_POS)
#define VDO_CFG_S_ROI7_MBY_E_UMSK                               (~(((1U<<VDO_CFG_S_ROI7_MBY_E_LEN)-1)<<VDO_CFG_S_ROI7_MBY_E_POS))

/* 0x304 : vdo_h264_osd_en */
#define VDO_H264_OSD_EN_OFFSET                                  (0x304)
#define VDO_CFG_OSD_EN                                          VDO_CFG_OSD_EN
#define VDO_CFG_OSD_EN_POS                                      (0U)
#define VDO_CFG_OSD_EN_LEN                                      (16U)
#define VDO_CFG_OSD_EN_MSK                                      (((1U<<VDO_CFG_OSD_EN_LEN)-1)<<VDO_CFG_OSD_EN_POS)
#define VDO_CFG_OSD_EN_UMSK                                     (~(((1U<<VDO_CFG_OSD_EN_LEN)-1)<<VDO_CFG_OSD_EN_POS))
#define VDO_CFG_OSD_MSSEL                                       VDO_CFG_OSD_MSSEL
#define VDO_CFG_OSD_MSSEL_POS                                   (16U)
#define VDO_CFG_OSD_MSSEL_LEN                                   (16U)
#define VDO_CFG_OSD_MSSEL_MSK                                   (((1U<<VDO_CFG_OSD_MSSEL_LEN)-1)<<VDO_CFG_OSD_MSSEL_POS)
#define VDO_CFG_OSD_MSSEL_UMSK                                  (~(((1U<<VDO_CFG_OSD_MSSEL_LEN)-1)<<VDO_CFG_OSD_MSSEL_POS))

/* 0x308 : vdo_h264_osd0 */
#define VDO_H264_OSD0_OFFSET                                    (0x308)
#define VDO_CFG_OSD0_MBX_S                                      VDO_CFG_OSD0_MBX_S
#define VDO_CFG_OSD0_MBX_S_POS                                  (0U)
#define VDO_CFG_OSD0_MBX_S_LEN                                  (7U)
#define VDO_CFG_OSD0_MBX_S_MSK                                  (((1U<<VDO_CFG_OSD0_MBX_S_LEN)-1)<<VDO_CFG_OSD0_MBX_S_POS)
#define VDO_CFG_OSD0_MBX_S_UMSK                                 (~(((1U<<VDO_CFG_OSD0_MBX_S_LEN)-1)<<VDO_CFG_OSD0_MBX_S_POS))
#define VDO_CFG_OSD0_MBX_E                                      VDO_CFG_OSD0_MBX_E
#define VDO_CFG_OSD0_MBX_E_POS                                  (8U)
#define VDO_CFG_OSD0_MBX_E_LEN                                  (7U)
#define VDO_CFG_OSD0_MBX_E_MSK                                  (((1U<<VDO_CFG_OSD0_MBX_E_LEN)-1)<<VDO_CFG_OSD0_MBX_E_POS)
#define VDO_CFG_OSD0_MBX_E_UMSK                                 (~(((1U<<VDO_CFG_OSD0_MBX_E_LEN)-1)<<VDO_CFG_OSD0_MBX_E_POS))
#define VDO_CFG_OSD0_MBY_S                                      VDO_CFG_OSD0_MBY_S
#define VDO_CFG_OSD0_MBY_S_POS                                  (16U)
#define VDO_CFG_OSD0_MBY_S_LEN                                  (7U)
#define VDO_CFG_OSD0_MBY_S_MSK                                  (((1U<<VDO_CFG_OSD0_MBY_S_LEN)-1)<<VDO_CFG_OSD0_MBY_S_POS)
#define VDO_CFG_OSD0_MBY_S_UMSK                                 (~(((1U<<VDO_CFG_OSD0_MBY_S_LEN)-1)<<VDO_CFG_OSD0_MBY_S_POS))
#define VDO_CFG_OSD0_MBY_E                                      VDO_CFG_OSD0_MBY_E
#define VDO_CFG_OSD0_MBY_E_POS                                  (24U)
#define VDO_CFG_OSD0_MBY_E_LEN                                  (7U)
#define VDO_CFG_OSD0_MBY_E_MSK                                  (((1U<<VDO_CFG_OSD0_MBY_E_LEN)-1)<<VDO_CFG_OSD0_MBY_E_POS)
#define VDO_CFG_OSD0_MBY_E_UMSK                                 (~(((1U<<VDO_CFG_OSD0_MBY_E_LEN)-1)<<VDO_CFG_OSD0_MBY_E_POS))

/* 0x30c : vdo_h264_osd1 */
#define VDO_H264_OSD1_OFFSET                                    (0x30c)
#define VDO_CFG_OSD1_MBX_S                                      VDO_CFG_OSD1_MBX_S
#define VDO_CFG_OSD1_MBX_S_POS                                  (0U)
#define VDO_CFG_OSD1_MBX_S_LEN                                  (7U)
#define VDO_CFG_OSD1_MBX_S_MSK                                  (((1U<<VDO_CFG_OSD1_MBX_S_LEN)-1)<<VDO_CFG_OSD1_MBX_S_POS)
#define VDO_CFG_OSD1_MBX_S_UMSK                                 (~(((1U<<VDO_CFG_OSD1_MBX_S_LEN)-1)<<VDO_CFG_OSD1_MBX_S_POS))
#define VDO_CFG_OSD1_MBX_E                                      VDO_CFG_OSD1_MBX_E
#define VDO_CFG_OSD1_MBX_E_POS                                  (8U)
#define VDO_CFG_OSD1_MBX_E_LEN                                  (7U)
#define VDO_CFG_OSD1_MBX_E_MSK                                  (((1U<<VDO_CFG_OSD1_MBX_E_LEN)-1)<<VDO_CFG_OSD1_MBX_E_POS)
#define VDO_CFG_OSD1_MBX_E_UMSK                                 (~(((1U<<VDO_CFG_OSD1_MBX_E_LEN)-1)<<VDO_CFG_OSD1_MBX_E_POS))
#define VDO_CFG_OSD1_MBY_S                                      VDO_CFG_OSD1_MBY_S
#define VDO_CFG_OSD1_MBY_S_POS                                  (16U)
#define VDO_CFG_OSD1_MBY_S_LEN                                  (7U)
#define VDO_CFG_OSD1_MBY_S_MSK                                  (((1U<<VDO_CFG_OSD1_MBY_S_LEN)-1)<<VDO_CFG_OSD1_MBY_S_POS)
#define VDO_CFG_OSD1_MBY_S_UMSK                                 (~(((1U<<VDO_CFG_OSD1_MBY_S_LEN)-1)<<VDO_CFG_OSD1_MBY_S_POS))
#define VDO_CFG_OSD1_MBY_E                                      VDO_CFG_OSD1_MBY_E
#define VDO_CFG_OSD1_MBY_E_POS                                  (24U)
#define VDO_CFG_OSD1_MBY_E_LEN                                  (7U)
#define VDO_CFG_OSD1_MBY_E_MSK                                  (((1U<<VDO_CFG_OSD1_MBY_E_LEN)-1)<<VDO_CFG_OSD1_MBY_E_POS)
#define VDO_CFG_OSD1_MBY_E_UMSK                                 (~(((1U<<VDO_CFG_OSD1_MBY_E_LEN)-1)<<VDO_CFG_OSD1_MBY_E_POS))

/* 0x310 : vdo_h264_osd2 */
#define VDO_H264_OSD2_OFFSET                                    (0x310)
#define VDO_CFG_OSD2_MBX_S                                      VDO_CFG_OSD2_MBX_S
#define VDO_CFG_OSD2_MBX_S_POS                                  (0U)
#define VDO_CFG_OSD2_MBX_S_LEN                                  (7U)
#define VDO_CFG_OSD2_MBX_S_MSK                                  (((1U<<VDO_CFG_OSD2_MBX_S_LEN)-1)<<VDO_CFG_OSD2_MBX_S_POS)
#define VDO_CFG_OSD2_MBX_S_UMSK                                 (~(((1U<<VDO_CFG_OSD2_MBX_S_LEN)-1)<<VDO_CFG_OSD2_MBX_S_POS))
#define VDO_CFG_OSD2_MBX_E                                      VDO_CFG_OSD2_MBX_E
#define VDO_CFG_OSD2_MBX_E_POS                                  (8U)
#define VDO_CFG_OSD2_MBX_E_LEN                                  (7U)
#define VDO_CFG_OSD2_MBX_E_MSK                                  (((1U<<VDO_CFG_OSD2_MBX_E_LEN)-1)<<VDO_CFG_OSD2_MBX_E_POS)
#define VDO_CFG_OSD2_MBX_E_UMSK                                 (~(((1U<<VDO_CFG_OSD2_MBX_E_LEN)-1)<<VDO_CFG_OSD2_MBX_E_POS))
#define VDO_CFG_OSD2_MBY_S                                      VDO_CFG_OSD2_MBY_S
#define VDO_CFG_OSD2_MBY_S_POS                                  (16U)
#define VDO_CFG_OSD2_MBY_S_LEN                                  (7U)
#define VDO_CFG_OSD2_MBY_S_MSK                                  (((1U<<VDO_CFG_OSD2_MBY_S_LEN)-1)<<VDO_CFG_OSD2_MBY_S_POS)
#define VDO_CFG_OSD2_MBY_S_UMSK                                 (~(((1U<<VDO_CFG_OSD2_MBY_S_LEN)-1)<<VDO_CFG_OSD2_MBY_S_POS))
#define VDO_CFG_OSD2_MBY_E                                      VDO_CFG_OSD2_MBY_E
#define VDO_CFG_OSD2_MBY_E_POS                                  (24U)
#define VDO_CFG_OSD2_MBY_E_LEN                                  (7U)
#define VDO_CFG_OSD2_MBY_E_MSK                                  (((1U<<VDO_CFG_OSD2_MBY_E_LEN)-1)<<VDO_CFG_OSD2_MBY_E_POS)
#define VDO_CFG_OSD2_MBY_E_UMSK                                 (~(((1U<<VDO_CFG_OSD2_MBY_E_LEN)-1)<<VDO_CFG_OSD2_MBY_E_POS))

/* 0x314 : vdo_h264_osd3 */
#define VDO_H264_OSD3_OFFSET                                    (0x314)
#define VDO_CFG_OSD3_MBX_S                                      VDO_CFG_OSD3_MBX_S
#define VDO_CFG_OSD3_MBX_S_POS                                  (0U)
#define VDO_CFG_OSD3_MBX_S_LEN                                  (7U)
#define VDO_CFG_OSD3_MBX_S_MSK                                  (((1U<<VDO_CFG_OSD3_MBX_S_LEN)-1)<<VDO_CFG_OSD3_MBX_S_POS)
#define VDO_CFG_OSD3_MBX_S_UMSK                                 (~(((1U<<VDO_CFG_OSD3_MBX_S_LEN)-1)<<VDO_CFG_OSD3_MBX_S_POS))
#define VDO_CFG_OSD3_MBX_E                                      VDO_CFG_OSD3_MBX_E
#define VDO_CFG_OSD3_MBX_E_POS                                  (8U)
#define VDO_CFG_OSD3_MBX_E_LEN                                  (7U)
#define VDO_CFG_OSD3_MBX_E_MSK                                  (((1U<<VDO_CFG_OSD3_MBX_E_LEN)-1)<<VDO_CFG_OSD3_MBX_E_POS)
#define VDO_CFG_OSD3_MBX_E_UMSK                                 (~(((1U<<VDO_CFG_OSD3_MBX_E_LEN)-1)<<VDO_CFG_OSD3_MBX_E_POS))
#define VDO_CFG_OSD3_MBY_S                                      VDO_CFG_OSD3_MBY_S
#define VDO_CFG_OSD3_MBY_S_POS                                  (16U)
#define VDO_CFG_OSD3_MBY_S_LEN                                  (7U)
#define VDO_CFG_OSD3_MBY_S_MSK                                  (((1U<<VDO_CFG_OSD3_MBY_S_LEN)-1)<<VDO_CFG_OSD3_MBY_S_POS)
#define VDO_CFG_OSD3_MBY_S_UMSK                                 (~(((1U<<VDO_CFG_OSD3_MBY_S_LEN)-1)<<VDO_CFG_OSD3_MBY_S_POS))
#define VDO_CFG_OSD3_MBY_E                                      VDO_CFG_OSD3_MBY_E
#define VDO_CFG_OSD3_MBY_E_POS                                  (24U)
#define VDO_CFG_OSD3_MBY_E_LEN                                  (7U)
#define VDO_CFG_OSD3_MBY_E_MSK                                  (((1U<<VDO_CFG_OSD3_MBY_E_LEN)-1)<<VDO_CFG_OSD3_MBY_E_POS)
#define VDO_CFG_OSD3_MBY_E_UMSK                                 (~(((1U<<VDO_CFG_OSD3_MBY_E_LEN)-1)<<VDO_CFG_OSD3_MBY_E_POS))

/* 0x318 : vdo_h264_osd4 */
#define VDO_H264_OSD4_OFFSET                                    (0x318)
#define VDO_CFG_OSD4_MBX_S                                      VDO_CFG_OSD4_MBX_S
#define VDO_CFG_OSD4_MBX_S_POS                                  (0U)
#define VDO_CFG_OSD4_MBX_S_LEN                                  (7U)
#define VDO_CFG_OSD4_MBX_S_MSK                                  (((1U<<VDO_CFG_OSD4_MBX_S_LEN)-1)<<VDO_CFG_OSD4_MBX_S_POS)
#define VDO_CFG_OSD4_MBX_S_UMSK                                 (~(((1U<<VDO_CFG_OSD4_MBX_S_LEN)-1)<<VDO_CFG_OSD4_MBX_S_POS))
#define VDO_CFG_OSD4_MBX_E                                      VDO_CFG_OSD4_MBX_E
#define VDO_CFG_OSD4_MBX_E_POS                                  (8U)
#define VDO_CFG_OSD4_MBX_E_LEN                                  (7U)
#define VDO_CFG_OSD4_MBX_E_MSK                                  (((1U<<VDO_CFG_OSD4_MBX_E_LEN)-1)<<VDO_CFG_OSD4_MBX_E_POS)
#define VDO_CFG_OSD4_MBX_E_UMSK                                 (~(((1U<<VDO_CFG_OSD4_MBX_E_LEN)-1)<<VDO_CFG_OSD4_MBX_E_POS))
#define VDO_CFG_OSD4_MBY_S                                      VDO_CFG_OSD4_MBY_S
#define VDO_CFG_OSD4_MBY_S_POS                                  (16U)
#define VDO_CFG_OSD4_MBY_S_LEN                                  (7U)
#define VDO_CFG_OSD4_MBY_S_MSK                                  (((1U<<VDO_CFG_OSD4_MBY_S_LEN)-1)<<VDO_CFG_OSD4_MBY_S_POS)
#define VDO_CFG_OSD4_MBY_S_UMSK                                 (~(((1U<<VDO_CFG_OSD4_MBY_S_LEN)-1)<<VDO_CFG_OSD4_MBY_S_POS))
#define VDO_CFG_OSD4_MBY_E                                      VDO_CFG_OSD4_MBY_E
#define VDO_CFG_OSD4_MBY_E_POS                                  (24U)
#define VDO_CFG_OSD4_MBY_E_LEN                                  (7U)
#define VDO_CFG_OSD4_MBY_E_MSK                                  (((1U<<VDO_CFG_OSD4_MBY_E_LEN)-1)<<VDO_CFG_OSD4_MBY_E_POS)
#define VDO_CFG_OSD4_MBY_E_UMSK                                 (~(((1U<<VDO_CFG_OSD4_MBY_E_LEN)-1)<<VDO_CFG_OSD4_MBY_E_POS))

/* 0x31c : vdo_h264_osd5 */
#define VDO_H264_OSD5_OFFSET                                    (0x31c)
#define VDO_CFG_OSD5_MBX_S                                      VDO_CFG_OSD5_MBX_S
#define VDO_CFG_OSD5_MBX_S_POS                                  (0U)
#define VDO_CFG_OSD5_MBX_S_LEN                                  (7U)
#define VDO_CFG_OSD5_MBX_S_MSK                                  (((1U<<VDO_CFG_OSD5_MBX_S_LEN)-1)<<VDO_CFG_OSD5_MBX_S_POS)
#define VDO_CFG_OSD5_MBX_S_UMSK                                 (~(((1U<<VDO_CFG_OSD5_MBX_S_LEN)-1)<<VDO_CFG_OSD5_MBX_S_POS))
#define VDO_CFG_OSD5_MBX_E                                      VDO_CFG_OSD5_MBX_E
#define VDO_CFG_OSD5_MBX_E_POS                                  (8U)
#define VDO_CFG_OSD5_MBX_E_LEN                                  (7U)
#define VDO_CFG_OSD5_MBX_E_MSK                                  (((1U<<VDO_CFG_OSD5_MBX_E_LEN)-1)<<VDO_CFG_OSD5_MBX_E_POS)
#define VDO_CFG_OSD5_MBX_E_UMSK                                 (~(((1U<<VDO_CFG_OSD5_MBX_E_LEN)-1)<<VDO_CFG_OSD5_MBX_E_POS))
#define VDO_CFG_OSD5_MBY_S                                      VDO_CFG_OSD5_MBY_S
#define VDO_CFG_OSD5_MBY_S_POS                                  (16U)
#define VDO_CFG_OSD5_MBY_S_LEN                                  (7U)
#define VDO_CFG_OSD5_MBY_S_MSK                                  (((1U<<VDO_CFG_OSD5_MBY_S_LEN)-1)<<VDO_CFG_OSD5_MBY_S_POS)
#define VDO_CFG_OSD5_MBY_S_UMSK                                 (~(((1U<<VDO_CFG_OSD5_MBY_S_LEN)-1)<<VDO_CFG_OSD5_MBY_S_POS))
#define VDO_CFG_OSD5_MBY_E                                      VDO_CFG_OSD5_MBY_E
#define VDO_CFG_OSD5_MBY_E_POS                                  (24U)
#define VDO_CFG_OSD5_MBY_E_LEN                                  (7U)
#define VDO_CFG_OSD5_MBY_E_MSK                                  (((1U<<VDO_CFG_OSD5_MBY_E_LEN)-1)<<VDO_CFG_OSD5_MBY_E_POS)
#define VDO_CFG_OSD5_MBY_E_UMSK                                 (~(((1U<<VDO_CFG_OSD5_MBY_E_LEN)-1)<<VDO_CFG_OSD5_MBY_E_POS))

/* 0x320 : vdo_h264_osd6 */
#define VDO_H264_OSD6_OFFSET                                    (0x320)
#define VDO_CFG_OSD6_MBX_S                                      VDO_CFG_OSD6_MBX_S
#define VDO_CFG_OSD6_MBX_S_POS                                  (0U)
#define VDO_CFG_OSD6_MBX_S_LEN                                  (7U)
#define VDO_CFG_OSD6_MBX_S_MSK                                  (((1U<<VDO_CFG_OSD6_MBX_S_LEN)-1)<<VDO_CFG_OSD6_MBX_S_POS)
#define VDO_CFG_OSD6_MBX_S_UMSK                                 (~(((1U<<VDO_CFG_OSD6_MBX_S_LEN)-1)<<VDO_CFG_OSD6_MBX_S_POS))
#define VDO_CFG_OSD6_MBX_E                                      VDO_CFG_OSD6_MBX_E
#define VDO_CFG_OSD6_MBX_E_POS                                  (8U)
#define VDO_CFG_OSD6_MBX_E_LEN                                  (7U)
#define VDO_CFG_OSD6_MBX_E_MSK                                  (((1U<<VDO_CFG_OSD6_MBX_E_LEN)-1)<<VDO_CFG_OSD6_MBX_E_POS)
#define VDO_CFG_OSD6_MBX_E_UMSK                                 (~(((1U<<VDO_CFG_OSD6_MBX_E_LEN)-1)<<VDO_CFG_OSD6_MBX_E_POS))
#define VDO_CFG_OSD6_MBY_S                                      VDO_CFG_OSD6_MBY_S
#define VDO_CFG_OSD6_MBY_S_POS                                  (16U)
#define VDO_CFG_OSD6_MBY_S_LEN                                  (7U)
#define VDO_CFG_OSD6_MBY_S_MSK                                  (((1U<<VDO_CFG_OSD6_MBY_S_LEN)-1)<<VDO_CFG_OSD6_MBY_S_POS)
#define VDO_CFG_OSD6_MBY_S_UMSK                                 (~(((1U<<VDO_CFG_OSD6_MBY_S_LEN)-1)<<VDO_CFG_OSD6_MBY_S_POS))
#define VDO_CFG_OSD6_MBY_E                                      VDO_CFG_OSD6_MBY_E
#define VDO_CFG_OSD6_MBY_E_POS                                  (24U)
#define VDO_CFG_OSD6_MBY_E_LEN                                  (7U)
#define VDO_CFG_OSD6_MBY_E_MSK                                  (((1U<<VDO_CFG_OSD6_MBY_E_LEN)-1)<<VDO_CFG_OSD6_MBY_E_POS)
#define VDO_CFG_OSD6_MBY_E_UMSK                                 (~(((1U<<VDO_CFG_OSD6_MBY_E_LEN)-1)<<VDO_CFG_OSD6_MBY_E_POS))

/* 0x324 : vdo_h264_osd7 */
#define VDO_H264_OSD7_OFFSET                                    (0x324)
#define VDO_CFG_OSD7_MBX_S                                      VDO_CFG_OSD7_MBX_S
#define VDO_CFG_OSD7_MBX_S_POS                                  (0U)
#define VDO_CFG_OSD7_MBX_S_LEN                                  (7U)
#define VDO_CFG_OSD7_MBX_S_MSK                                  (((1U<<VDO_CFG_OSD7_MBX_S_LEN)-1)<<VDO_CFG_OSD7_MBX_S_POS)
#define VDO_CFG_OSD7_MBX_S_UMSK                                 (~(((1U<<VDO_CFG_OSD7_MBX_S_LEN)-1)<<VDO_CFG_OSD7_MBX_S_POS))
#define VDO_CFG_OSD7_MBX_E                                      VDO_CFG_OSD7_MBX_E
#define VDO_CFG_OSD7_MBX_E_POS                                  (8U)
#define VDO_CFG_OSD7_MBX_E_LEN                                  (7U)
#define VDO_CFG_OSD7_MBX_E_MSK                                  (((1U<<VDO_CFG_OSD7_MBX_E_LEN)-1)<<VDO_CFG_OSD7_MBX_E_POS)
#define VDO_CFG_OSD7_MBX_E_UMSK                                 (~(((1U<<VDO_CFG_OSD7_MBX_E_LEN)-1)<<VDO_CFG_OSD7_MBX_E_POS))
#define VDO_CFG_OSD7_MBY_S                                      VDO_CFG_OSD7_MBY_S
#define VDO_CFG_OSD7_MBY_S_POS                                  (16U)
#define VDO_CFG_OSD7_MBY_S_LEN                                  (7U)
#define VDO_CFG_OSD7_MBY_S_MSK                                  (((1U<<VDO_CFG_OSD7_MBY_S_LEN)-1)<<VDO_CFG_OSD7_MBY_S_POS)
#define VDO_CFG_OSD7_MBY_S_UMSK                                 (~(((1U<<VDO_CFG_OSD7_MBY_S_LEN)-1)<<VDO_CFG_OSD7_MBY_S_POS))
#define VDO_CFG_OSD7_MBY_E                                      VDO_CFG_OSD7_MBY_E
#define VDO_CFG_OSD7_MBY_E_POS                                  (24U)
#define VDO_CFG_OSD7_MBY_E_LEN                                  (7U)
#define VDO_CFG_OSD7_MBY_E_MSK                                  (((1U<<VDO_CFG_OSD7_MBY_E_LEN)-1)<<VDO_CFG_OSD7_MBY_E_POS)
#define VDO_CFG_OSD7_MBY_E_UMSK                                 (~(((1U<<VDO_CFG_OSD7_MBY_E_LEN)-1)<<VDO_CFG_OSD7_MBY_E_POS))

/* 0x328 : vdo_h264_osd8 */
#define VDO_H264_OSD8_OFFSET                                    (0x328)
#define VDO_CFG_OSD8_MBX_S                                      VDO_CFG_OSD8_MBX_S
#define VDO_CFG_OSD8_MBX_S_POS                                  (0U)
#define VDO_CFG_OSD8_MBX_S_LEN                                  (7U)
#define VDO_CFG_OSD8_MBX_S_MSK                                  (((1U<<VDO_CFG_OSD8_MBX_S_LEN)-1)<<VDO_CFG_OSD8_MBX_S_POS)
#define VDO_CFG_OSD8_MBX_S_UMSK                                 (~(((1U<<VDO_CFG_OSD8_MBX_S_LEN)-1)<<VDO_CFG_OSD8_MBX_S_POS))
#define VDO_CFG_OSD8_MBX_E                                      VDO_CFG_OSD8_MBX_E
#define VDO_CFG_OSD8_MBX_E_POS                                  (8U)
#define VDO_CFG_OSD8_MBX_E_LEN                                  (7U)
#define VDO_CFG_OSD8_MBX_E_MSK                                  (((1U<<VDO_CFG_OSD8_MBX_E_LEN)-1)<<VDO_CFG_OSD8_MBX_E_POS)
#define VDO_CFG_OSD8_MBX_E_UMSK                                 (~(((1U<<VDO_CFG_OSD8_MBX_E_LEN)-1)<<VDO_CFG_OSD8_MBX_E_POS))
#define VDO_CFG_OSD8_MBY_S                                      VDO_CFG_OSD8_MBY_S
#define VDO_CFG_OSD8_MBY_S_POS                                  (16U)
#define VDO_CFG_OSD8_MBY_S_LEN                                  (7U)
#define VDO_CFG_OSD8_MBY_S_MSK                                  (((1U<<VDO_CFG_OSD8_MBY_S_LEN)-1)<<VDO_CFG_OSD8_MBY_S_POS)
#define VDO_CFG_OSD8_MBY_S_UMSK                                 (~(((1U<<VDO_CFG_OSD8_MBY_S_LEN)-1)<<VDO_CFG_OSD8_MBY_S_POS))
#define VDO_CFG_OSD8_MBY_E                                      VDO_CFG_OSD8_MBY_E
#define VDO_CFG_OSD8_MBY_E_POS                                  (24U)
#define VDO_CFG_OSD8_MBY_E_LEN                                  (7U)
#define VDO_CFG_OSD8_MBY_E_MSK                                  (((1U<<VDO_CFG_OSD8_MBY_E_LEN)-1)<<VDO_CFG_OSD8_MBY_E_POS)
#define VDO_CFG_OSD8_MBY_E_UMSK                                 (~(((1U<<VDO_CFG_OSD8_MBY_E_LEN)-1)<<VDO_CFG_OSD8_MBY_E_POS))

/* 0x32c : vdo_h264_osd9 */
#define VDO_H264_OSD9_OFFSET                                    (0x32c)
#define VDO_CFG_OSD9_MBX_S                                      VDO_CFG_OSD9_MBX_S
#define VDO_CFG_OSD9_MBX_S_POS                                  (0U)
#define VDO_CFG_OSD9_MBX_S_LEN                                  (7U)
#define VDO_CFG_OSD9_MBX_S_MSK                                  (((1U<<VDO_CFG_OSD9_MBX_S_LEN)-1)<<VDO_CFG_OSD9_MBX_S_POS)
#define VDO_CFG_OSD9_MBX_S_UMSK                                 (~(((1U<<VDO_CFG_OSD9_MBX_S_LEN)-1)<<VDO_CFG_OSD9_MBX_S_POS))
#define VDO_CFG_OSD9_MBX_E                                      VDO_CFG_OSD9_MBX_E
#define VDO_CFG_OSD9_MBX_E_POS                                  (8U)
#define VDO_CFG_OSD9_MBX_E_LEN                                  (7U)
#define VDO_CFG_OSD9_MBX_E_MSK                                  (((1U<<VDO_CFG_OSD9_MBX_E_LEN)-1)<<VDO_CFG_OSD9_MBX_E_POS)
#define VDO_CFG_OSD9_MBX_E_UMSK                                 (~(((1U<<VDO_CFG_OSD9_MBX_E_LEN)-1)<<VDO_CFG_OSD9_MBX_E_POS))
#define VDO_CFG_OSD9_MBY_S                                      VDO_CFG_OSD9_MBY_S
#define VDO_CFG_OSD9_MBY_S_POS                                  (16U)
#define VDO_CFG_OSD9_MBY_S_LEN                                  (7U)
#define VDO_CFG_OSD9_MBY_S_MSK                                  (((1U<<VDO_CFG_OSD9_MBY_S_LEN)-1)<<VDO_CFG_OSD9_MBY_S_POS)
#define VDO_CFG_OSD9_MBY_S_UMSK                                 (~(((1U<<VDO_CFG_OSD9_MBY_S_LEN)-1)<<VDO_CFG_OSD9_MBY_S_POS))
#define VDO_CFG_OSD9_MBY_E                                      VDO_CFG_OSD9_MBY_E
#define VDO_CFG_OSD9_MBY_E_POS                                  (24U)
#define VDO_CFG_OSD9_MBY_E_LEN                                  (7U)
#define VDO_CFG_OSD9_MBY_E_MSK                                  (((1U<<VDO_CFG_OSD9_MBY_E_LEN)-1)<<VDO_CFG_OSD9_MBY_E_POS)
#define VDO_CFG_OSD9_MBY_E_UMSK                                 (~(((1U<<VDO_CFG_OSD9_MBY_E_LEN)-1)<<VDO_CFG_OSD9_MBY_E_POS))

/* 0x330 : vdo_h264_osd10 */
#define VDO_H264_OSD10_OFFSET                                   (0x330)
#define VDO_CFG_OSD10_MBX_S                                     VDO_CFG_OSD10_MBX_S
#define VDO_CFG_OSD10_MBX_S_POS                                 (0U)
#define VDO_CFG_OSD10_MBX_S_LEN                                 (7U)
#define VDO_CFG_OSD10_MBX_S_MSK                                 (((1U<<VDO_CFG_OSD10_MBX_S_LEN)-1)<<VDO_CFG_OSD10_MBX_S_POS)
#define VDO_CFG_OSD10_MBX_S_UMSK                                (~(((1U<<VDO_CFG_OSD10_MBX_S_LEN)-1)<<VDO_CFG_OSD10_MBX_S_POS))
#define VDO_CFG_OSD10_MBX_E                                     VDO_CFG_OSD10_MBX_E
#define VDO_CFG_OSD10_MBX_E_POS                                 (8U)
#define VDO_CFG_OSD10_MBX_E_LEN                                 (7U)
#define VDO_CFG_OSD10_MBX_E_MSK                                 (((1U<<VDO_CFG_OSD10_MBX_E_LEN)-1)<<VDO_CFG_OSD10_MBX_E_POS)
#define VDO_CFG_OSD10_MBX_E_UMSK                                (~(((1U<<VDO_CFG_OSD10_MBX_E_LEN)-1)<<VDO_CFG_OSD10_MBX_E_POS))
#define VDO_CFG_OSD10_MBY_S                                     VDO_CFG_OSD10_MBY_S
#define VDO_CFG_OSD10_MBY_S_POS                                 (16U)
#define VDO_CFG_OSD10_MBY_S_LEN                                 (7U)
#define VDO_CFG_OSD10_MBY_S_MSK                                 (((1U<<VDO_CFG_OSD10_MBY_S_LEN)-1)<<VDO_CFG_OSD10_MBY_S_POS)
#define VDO_CFG_OSD10_MBY_S_UMSK                                (~(((1U<<VDO_CFG_OSD10_MBY_S_LEN)-1)<<VDO_CFG_OSD10_MBY_S_POS))
#define VDO_CFG_OSD10_MBY_E                                     VDO_CFG_OSD10_MBY_E
#define VDO_CFG_OSD10_MBY_E_POS                                 (24U)
#define VDO_CFG_OSD10_MBY_E_LEN                                 (7U)
#define VDO_CFG_OSD10_MBY_E_MSK                                 (((1U<<VDO_CFG_OSD10_MBY_E_LEN)-1)<<VDO_CFG_OSD10_MBY_E_POS)
#define VDO_CFG_OSD10_MBY_E_UMSK                                (~(((1U<<VDO_CFG_OSD10_MBY_E_LEN)-1)<<VDO_CFG_OSD10_MBY_E_POS))

/* 0x334 : vdo_h264_osd11 */
#define VDO_H264_OSD11_OFFSET                                   (0x334)
#define VDO_CFG_OSD11_MBX_S                                     VDO_CFG_OSD11_MBX_S
#define VDO_CFG_OSD11_MBX_S_POS                                 (0U)
#define VDO_CFG_OSD11_MBX_S_LEN                                 (7U)
#define VDO_CFG_OSD11_MBX_S_MSK                                 (((1U<<VDO_CFG_OSD11_MBX_S_LEN)-1)<<VDO_CFG_OSD11_MBX_S_POS)
#define VDO_CFG_OSD11_MBX_S_UMSK                                (~(((1U<<VDO_CFG_OSD11_MBX_S_LEN)-1)<<VDO_CFG_OSD11_MBX_S_POS))
#define VDO_CFG_OSD11_MBX_E                                     VDO_CFG_OSD11_MBX_E
#define VDO_CFG_OSD11_MBX_E_POS                                 (8U)
#define VDO_CFG_OSD11_MBX_E_LEN                                 (7U)
#define VDO_CFG_OSD11_MBX_E_MSK                                 (((1U<<VDO_CFG_OSD11_MBX_E_LEN)-1)<<VDO_CFG_OSD11_MBX_E_POS)
#define VDO_CFG_OSD11_MBX_E_UMSK                                (~(((1U<<VDO_CFG_OSD11_MBX_E_LEN)-1)<<VDO_CFG_OSD11_MBX_E_POS))
#define VDO_CFG_OSD11_MBY_S                                     VDO_CFG_OSD11_MBY_S
#define VDO_CFG_OSD11_MBY_S_POS                                 (16U)
#define VDO_CFG_OSD11_MBY_S_LEN                                 (7U)
#define VDO_CFG_OSD11_MBY_S_MSK                                 (((1U<<VDO_CFG_OSD11_MBY_S_LEN)-1)<<VDO_CFG_OSD11_MBY_S_POS)
#define VDO_CFG_OSD11_MBY_S_UMSK                                (~(((1U<<VDO_CFG_OSD11_MBY_S_LEN)-1)<<VDO_CFG_OSD11_MBY_S_POS))
#define VDO_CFG_OSD11_MBY_E                                     VDO_CFG_OSD11_MBY_E
#define VDO_CFG_OSD11_MBY_E_POS                                 (24U)
#define VDO_CFG_OSD11_MBY_E_LEN                                 (7U)
#define VDO_CFG_OSD11_MBY_E_MSK                                 (((1U<<VDO_CFG_OSD11_MBY_E_LEN)-1)<<VDO_CFG_OSD11_MBY_E_POS)
#define VDO_CFG_OSD11_MBY_E_UMSK                                (~(((1U<<VDO_CFG_OSD11_MBY_E_LEN)-1)<<VDO_CFG_OSD11_MBY_E_POS))

/* 0x338 : vdo_h264_osd12 */
#define VDO_H264_OSD12_OFFSET                                   (0x338)
#define VDO_CFG_OSD12_MBX_S                                     VDO_CFG_OSD12_MBX_S
#define VDO_CFG_OSD12_MBX_S_POS                                 (0U)
#define VDO_CFG_OSD12_MBX_S_LEN                                 (7U)
#define VDO_CFG_OSD12_MBX_S_MSK                                 (((1U<<VDO_CFG_OSD12_MBX_S_LEN)-1)<<VDO_CFG_OSD12_MBX_S_POS)
#define VDO_CFG_OSD12_MBX_S_UMSK                                (~(((1U<<VDO_CFG_OSD12_MBX_S_LEN)-1)<<VDO_CFG_OSD12_MBX_S_POS))
#define VDO_CFG_OSD12_MBX_E                                     VDO_CFG_OSD12_MBX_E
#define VDO_CFG_OSD12_MBX_E_POS                                 (8U)
#define VDO_CFG_OSD12_MBX_E_LEN                                 (7U)
#define VDO_CFG_OSD12_MBX_E_MSK                                 (((1U<<VDO_CFG_OSD12_MBX_E_LEN)-1)<<VDO_CFG_OSD12_MBX_E_POS)
#define VDO_CFG_OSD12_MBX_E_UMSK                                (~(((1U<<VDO_CFG_OSD12_MBX_E_LEN)-1)<<VDO_CFG_OSD12_MBX_E_POS))
#define VDO_CFG_OSD12_MBY_S                                     VDO_CFG_OSD12_MBY_S
#define VDO_CFG_OSD12_MBY_S_POS                                 (16U)
#define VDO_CFG_OSD12_MBY_S_LEN                                 (7U)
#define VDO_CFG_OSD12_MBY_S_MSK                                 (((1U<<VDO_CFG_OSD12_MBY_S_LEN)-1)<<VDO_CFG_OSD12_MBY_S_POS)
#define VDO_CFG_OSD12_MBY_S_UMSK                                (~(((1U<<VDO_CFG_OSD12_MBY_S_LEN)-1)<<VDO_CFG_OSD12_MBY_S_POS))
#define VDO_CFG_OSD12_MBY_E                                     VDO_CFG_OSD12_MBY_E
#define VDO_CFG_OSD12_MBY_E_POS                                 (24U)
#define VDO_CFG_OSD12_MBY_E_LEN                                 (7U)
#define VDO_CFG_OSD12_MBY_E_MSK                                 (((1U<<VDO_CFG_OSD12_MBY_E_LEN)-1)<<VDO_CFG_OSD12_MBY_E_POS)
#define VDO_CFG_OSD12_MBY_E_UMSK                                (~(((1U<<VDO_CFG_OSD12_MBY_E_LEN)-1)<<VDO_CFG_OSD12_MBY_E_POS))

/* 0x33c : vdo_h264_osd13 */
#define VDO_H264_OSD13_OFFSET                                   (0x33c)
#define VDO_CFG_OSD13_MBX_S                                     VDO_CFG_OSD13_MBX_S
#define VDO_CFG_OSD13_MBX_S_POS                                 (0U)
#define VDO_CFG_OSD13_MBX_S_LEN                                 (7U)
#define VDO_CFG_OSD13_MBX_S_MSK                                 (((1U<<VDO_CFG_OSD13_MBX_S_LEN)-1)<<VDO_CFG_OSD13_MBX_S_POS)
#define VDO_CFG_OSD13_MBX_S_UMSK                                (~(((1U<<VDO_CFG_OSD13_MBX_S_LEN)-1)<<VDO_CFG_OSD13_MBX_S_POS))
#define VDO_CFG_OSD13_MBX_E                                     VDO_CFG_OSD13_MBX_E
#define VDO_CFG_OSD13_MBX_E_POS                                 (8U)
#define VDO_CFG_OSD13_MBX_E_LEN                                 (7U)
#define VDO_CFG_OSD13_MBX_E_MSK                                 (((1U<<VDO_CFG_OSD13_MBX_E_LEN)-1)<<VDO_CFG_OSD13_MBX_E_POS)
#define VDO_CFG_OSD13_MBX_E_UMSK                                (~(((1U<<VDO_CFG_OSD13_MBX_E_LEN)-1)<<VDO_CFG_OSD13_MBX_E_POS))
#define VDO_CFG_OSD13_MBY_S                                     VDO_CFG_OSD13_MBY_S
#define VDO_CFG_OSD13_MBY_S_POS                                 (16U)
#define VDO_CFG_OSD13_MBY_S_LEN                                 (7U)
#define VDO_CFG_OSD13_MBY_S_MSK                                 (((1U<<VDO_CFG_OSD13_MBY_S_LEN)-1)<<VDO_CFG_OSD13_MBY_S_POS)
#define VDO_CFG_OSD13_MBY_S_UMSK                                (~(((1U<<VDO_CFG_OSD13_MBY_S_LEN)-1)<<VDO_CFG_OSD13_MBY_S_POS))
#define VDO_CFG_OSD13_MBY_E                                     VDO_CFG_OSD13_MBY_E
#define VDO_CFG_OSD13_MBY_E_POS                                 (24U)
#define VDO_CFG_OSD13_MBY_E_LEN                                 (7U)
#define VDO_CFG_OSD13_MBY_E_MSK                                 (((1U<<VDO_CFG_OSD13_MBY_E_LEN)-1)<<VDO_CFG_OSD13_MBY_E_POS)
#define VDO_CFG_OSD13_MBY_E_UMSK                                (~(((1U<<VDO_CFG_OSD13_MBY_E_LEN)-1)<<VDO_CFG_OSD13_MBY_E_POS))

/* 0x340 : vdo_h264_osd14 */
#define VDO_H264_OSD14_OFFSET                                   (0x340)
#define VDO_CFG_OSD14_MBX_S                                     VDO_CFG_OSD14_MBX_S
#define VDO_CFG_OSD14_MBX_S_POS                                 (0U)
#define VDO_CFG_OSD14_MBX_S_LEN                                 (7U)
#define VDO_CFG_OSD14_MBX_S_MSK                                 (((1U<<VDO_CFG_OSD14_MBX_S_LEN)-1)<<VDO_CFG_OSD14_MBX_S_POS)
#define VDO_CFG_OSD14_MBX_S_UMSK                                (~(((1U<<VDO_CFG_OSD14_MBX_S_LEN)-1)<<VDO_CFG_OSD14_MBX_S_POS))
#define VDO_CFG_OSD14_MBX_E                                     VDO_CFG_OSD14_MBX_E
#define VDO_CFG_OSD14_MBX_E_POS                                 (8U)
#define VDO_CFG_OSD14_MBX_E_LEN                                 (7U)
#define VDO_CFG_OSD14_MBX_E_MSK                                 (((1U<<VDO_CFG_OSD14_MBX_E_LEN)-1)<<VDO_CFG_OSD14_MBX_E_POS)
#define VDO_CFG_OSD14_MBX_E_UMSK                                (~(((1U<<VDO_CFG_OSD14_MBX_E_LEN)-1)<<VDO_CFG_OSD14_MBX_E_POS))
#define VDO_CFG_OSD14_MBY_S                                     VDO_CFG_OSD14_MBY_S
#define VDO_CFG_OSD14_MBY_S_POS                                 (16U)
#define VDO_CFG_OSD14_MBY_S_LEN                                 (7U)
#define VDO_CFG_OSD14_MBY_S_MSK                                 (((1U<<VDO_CFG_OSD14_MBY_S_LEN)-1)<<VDO_CFG_OSD14_MBY_S_POS)
#define VDO_CFG_OSD14_MBY_S_UMSK                                (~(((1U<<VDO_CFG_OSD14_MBY_S_LEN)-1)<<VDO_CFG_OSD14_MBY_S_POS))
#define VDO_CFG_OSD14_MBY_E                                     VDO_CFG_OSD14_MBY_E
#define VDO_CFG_OSD14_MBY_E_POS                                 (24U)
#define VDO_CFG_OSD14_MBY_E_LEN                                 (7U)
#define VDO_CFG_OSD14_MBY_E_MSK                                 (((1U<<VDO_CFG_OSD14_MBY_E_LEN)-1)<<VDO_CFG_OSD14_MBY_E_POS)
#define VDO_CFG_OSD14_MBY_E_UMSK                                (~(((1U<<VDO_CFG_OSD14_MBY_E_LEN)-1)<<VDO_CFG_OSD14_MBY_E_POS))

/* 0x344 : vdo_h264_osd15 */
#define VDO_H264_OSD15_OFFSET                                   (0x344)
#define VDO_CFG_OSD15_MBX_S                                     VDO_CFG_OSD15_MBX_S
#define VDO_CFG_OSD15_MBX_S_POS                                 (0U)
#define VDO_CFG_OSD15_MBX_S_LEN                                 (7U)
#define VDO_CFG_OSD15_MBX_S_MSK                                 (((1U<<VDO_CFG_OSD15_MBX_S_LEN)-1)<<VDO_CFG_OSD15_MBX_S_POS)
#define VDO_CFG_OSD15_MBX_S_UMSK                                (~(((1U<<VDO_CFG_OSD15_MBX_S_LEN)-1)<<VDO_CFG_OSD15_MBX_S_POS))
#define VDO_CFG_OSD15_MBX_E                                     VDO_CFG_OSD15_MBX_E
#define VDO_CFG_OSD15_MBX_E_POS                                 (8U)
#define VDO_CFG_OSD15_MBX_E_LEN                                 (7U)
#define VDO_CFG_OSD15_MBX_E_MSK                                 (((1U<<VDO_CFG_OSD15_MBX_E_LEN)-1)<<VDO_CFG_OSD15_MBX_E_POS)
#define VDO_CFG_OSD15_MBX_E_UMSK                                (~(((1U<<VDO_CFG_OSD15_MBX_E_LEN)-1)<<VDO_CFG_OSD15_MBX_E_POS))
#define VDO_CFG_OSD15_MBY_S                                     VDO_CFG_OSD15_MBY_S
#define VDO_CFG_OSD15_MBY_S_POS                                 (16U)
#define VDO_CFG_OSD15_MBY_S_LEN                                 (7U)
#define VDO_CFG_OSD15_MBY_S_MSK                                 (((1U<<VDO_CFG_OSD15_MBY_S_LEN)-1)<<VDO_CFG_OSD15_MBY_S_POS)
#define VDO_CFG_OSD15_MBY_S_UMSK                                (~(((1U<<VDO_CFG_OSD15_MBY_S_LEN)-1)<<VDO_CFG_OSD15_MBY_S_POS))
#define VDO_CFG_OSD15_MBY_E                                     VDO_CFG_OSD15_MBY_E
#define VDO_CFG_OSD15_MBY_E_POS                                 (24U)
#define VDO_CFG_OSD15_MBY_E_LEN                                 (7U)
#define VDO_CFG_OSD15_MBY_E_MSK                                 (((1U<<VDO_CFG_OSD15_MBY_E_LEN)-1)<<VDO_CFG_OSD15_MBY_E_POS)
#define VDO_CFG_OSD15_MBY_E_UMSK                                (~(((1U<<VDO_CFG_OSD15_MBY_E_LEN)-1)<<VDO_CFG_OSD15_MBY_E_POS))

/* 0x348 : vdo_h264_mv0_en */
#define VDO_H264_MV0_EN_OFFSET                                  (0x348)
#define VDO_CFG_MV0_EN                                          VDO_CFG_MV0_EN
#define VDO_CFG_MV0_EN_POS                                      (0U)
#define VDO_CFG_MV0_EN_LEN                                      (1U)
#define VDO_CFG_MV0_EN_MSK                                      (((1U<<VDO_CFG_MV0_EN_LEN)-1)<<VDO_CFG_MV0_EN_POS)
#define VDO_CFG_MV0_EN_UMSK                                     (~(((1U<<VDO_CFG_MV0_EN_LEN)-1)<<VDO_CFG_MV0_EN_POS))
#define VDO_CFG_S_MV0_EN                                        VDO_CFG_S_MV0_EN
#define VDO_CFG_S_MV0_EN_POS                                    (1U)
#define VDO_CFG_S_MV0_EN_LEN                                    (1U)
#define VDO_CFG_S_MV0_EN_MSK                                    (((1U<<VDO_CFG_S_MV0_EN_LEN)-1)<<VDO_CFG_S_MV0_EN_POS)
#define VDO_CFG_S_MV0_EN_UMSK                                   (~(((1U<<VDO_CFG_S_MV0_EN_LEN)-1)<<VDO_CFG_S_MV0_EN_POS))

/* 0x34c : vdo_pfch_dbg_reqcnt */
#define VDO_PFCH_DBG_REQCNT_OFFSET                              (0x34c)
#define VDO_DBG_REQCNT                                          VDO_DBG_REQCNT
#define VDO_DBG_REQCNT_POS                                      (0U)
#define VDO_DBG_REQCNT_LEN                                      (32U)
#define VDO_DBG_REQCNT_MSK                                      (((1U<<VDO_DBG_REQCNT_LEN)-1)<<VDO_DBG_REQCNT_POS)
#define VDO_DBG_REQCNT_UMSK                                     (~(((1U<<VDO_DBG_REQCNT_LEN)-1)<<VDO_DBG_REQCNT_POS))

/* 0x350 : vdo_pfch_dbg_rcmd */
#define VDO_PFCH_DBG_RCMD_OFFSET                                (0x350)
#define VDO_DBG_RCMD                                            VDO_DBG_RCMD
#define VDO_DBG_RCMD_POS                                        (0U)
#define VDO_DBG_RCMD_LEN                                        (32U)
#define VDO_DBG_RCMD_MSK                                        (((1U<<VDO_DBG_RCMD_LEN)-1)<<VDO_DBG_RCMD_POS)
#define VDO_DBG_RCMD_UMSK                                       (~(((1U<<VDO_DBG_RCMD_LEN)-1)<<VDO_DBG_RCMD_POS))

/* 0x354 : vdo_pfch_dbg_wcmd */
#define VDO_PFCH_DBG_WCMD_OFFSET                                (0x354)
#define VDO_DBG_WCMD                                            VDO_DBG_WCMD
#define VDO_DBG_WCMD_POS                                        (0U)
#define VDO_DBG_WCMD_LEN                                        (32U)
#define VDO_DBG_WCMD_MSK                                        (((1U<<VDO_DBG_WCMD_LEN)-1)<<VDO_DBG_WCMD_POS)
#define VDO_DBG_WCMD_UMSK                                       (~(((1U<<VDO_DBG_WCMD_LEN)-1)<<VDO_DBG_WCMD_POS))

/* 0x358 : vdo_pfch_dbg_wdata */
#define VDO_PFCH_DBG_WDATA_OFFSET                               (0x358)
#define VDO_DBG_WDATA                                           VDO_DBG_WDATA
#define VDO_DBG_WDATA_POS                                       (0U)
#define VDO_DBG_WDATA_LEN                                       (32U)
#define VDO_DBG_WDATA_MSK                                       (((1U<<VDO_DBG_WDATA_LEN)-1)<<VDO_DBG_WDATA_POS)
#define VDO_DBG_WDATA_UMSK                                      (~(((1U<<VDO_DBG_WDATA_LEN)-1)<<VDO_DBG_WDATA_POS))

/* 0x35c : vdo_pfch_dbg_pfchsta */
#define VDO_PFCH_DBG_PFCHSTA_OFFSET                             (0x35c)
#define VDO_DBG_PFCHSTA                                         VDO_DBG_PFCHSTA
#define VDO_DBG_PFCHSTA_POS                                     (0U)
#define VDO_DBG_PFCHSTA_LEN                                     (32U)
#define VDO_DBG_PFCHSTA_MSK                                     (((1U<<VDO_DBG_PFCHSTA_LEN)-1)<<VDO_DBG_PFCHSTA_POS)
#define VDO_DBG_PFCHSTA_UMSK                                    (~(((1U<<VDO_DBG_PFCHSTA_LEN)-1)<<VDO_DBG_PFCHSTA_POS))

/* 0x360 : vdo_pfchv_dbg_reqcnt */
#define VDO_PFCHV_DBG_REQCNT_OFFSET                             (0x360)
#define VDO_DBGV_REQCNT                                         VDO_DBGV_REQCNT
#define VDO_DBGV_REQCNT_POS                                     (0U)
#define VDO_DBGV_REQCNT_LEN                                     (32U)
#define VDO_DBGV_REQCNT_MSK                                     (((1U<<VDO_DBGV_REQCNT_LEN)-1)<<VDO_DBGV_REQCNT_POS)
#define VDO_DBGV_REQCNT_UMSK                                    (~(((1U<<VDO_DBGV_REQCNT_LEN)-1)<<VDO_DBGV_REQCNT_POS))

/* 0x364 : vdo_pfchv_dbg_rcmd */
#define VDO_PFCHV_DBG_RCMD_OFFSET                               (0x364)
#define VDO_DBGV_RCMD                                           VDO_DBGV_RCMD
#define VDO_DBGV_RCMD_POS                                       (0U)
#define VDO_DBGV_RCMD_LEN                                       (32U)
#define VDO_DBGV_RCMD_MSK                                       (((1U<<VDO_DBGV_RCMD_LEN)-1)<<VDO_DBGV_RCMD_POS)
#define VDO_DBGV_RCMD_UMSK                                      (~(((1U<<VDO_DBGV_RCMD_LEN)-1)<<VDO_DBGV_RCMD_POS))

/* 0x368 : vdo_pfchv_dbg_wcmd */
#define VDO_PFCHV_DBG_WCMD_OFFSET                               (0x368)
#define VDO_DBGV_WCMD                                           VDO_DBGV_WCMD
#define VDO_DBGV_WCMD_POS                                       (0U)
#define VDO_DBGV_WCMD_LEN                                       (32U)
#define VDO_DBGV_WCMD_MSK                                       (((1U<<VDO_DBGV_WCMD_LEN)-1)<<VDO_DBGV_WCMD_POS)
#define VDO_DBGV_WCMD_UMSK                                      (~(((1U<<VDO_DBGV_WCMD_LEN)-1)<<VDO_DBGV_WCMD_POS))

/* 0x36c : vdo_pfchv_dbg_wdata */
#define VDO_PFCHV_DBG_WDATA_OFFSET                              (0x36c)
#define VDO_DBGV_WDATA                                          VDO_DBGV_WDATA
#define VDO_DBGV_WDATA_POS                                      (0U)
#define VDO_DBGV_WDATA_LEN                                      (32U)
#define VDO_DBGV_WDATA_MSK                                      (((1U<<VDO_DBGV_WDATA_LEN)-1)<<VDO_DBGV_WDATA_POS)
#define VDO_DBGV_WDATA_UMSK                                     (~(((1U<<VDO_DBGV_WDATA_LEN)-1)<<VDO_DBGV_WDATA_POS))

/* 0x370 : vdo_pfchv_dbg_pfchsta */
#define VDO_PFCHV_DBG_PFCHSTA_OFFSET                            (0x370)
#define VDO_DBGV_PFCHSTA                                        VDO_DBGV_PFCHSTA
#define VDO_DBGV_PFCHSTA_POS                                    (0U)
#define VDO_DBGV_PFCHSTA_LEN                                    (32U)
#define VDO_DBGV_PFCHSTA_MSK                                    (((1U<<VDO_DBGV_PFCHSTA_LEN)-1)<<VDO_DBGV_PFCHSTA_POS)
#define VDO_DBGV_PFCHSTA_UMSK                                   (~(((1U<<VDO_DBGV_PFCHSTA_LEN)-1)<<VDO_DBGV_PFCHSTA_POS))

/* 0x374 : vdo_pfch_s_dbg_reqcnt */
#define VDO_PFCH_S_DBG_REQCNT_OFFSET                            (0x374)
#define VDO_S_DBG_REQCNT                                        VDO_S_DBG_REQCNT
#define VDO_S_DBG_REQCNT_POS                                    (0U)
#define VDO_S_DBG_REQCNT_LEN                                    (32U)
#define VDO_S_DBG_REQCNT_MSK                                    (((1U<<VDO_S_DBG_REQCNT_LEN)-1)<<VDO_S_DBG_REQCNT_POS)
#define VDO_S_DBG_REQCNT_UMSK                                   (~(((1U<<VDO_S_DBG_REQCNT_LEN)-1)<<VDO_S_DBG_REQCNT_POS))

/* 0x378 : vdo_pfch_s_dbg_rcmd */
#define VDO_PFCH_S_DBG_RCMD_OFFSET                              (0x378)
#define VDO_S_DBG_RCMD                                          VDO_S_DBG_RCMD
#define VDO_S_DBG_RCMD_POS                                      (0U)
#define VDO_S_DBG_RCMD_LEN                                      (32U)
#define VDO_S_DBG_RCMD_MSK                                      (((1U<<VDO_S_DBG_RCMD_LEN)-1)<<VDO_S_DBG_RCMD_POS)
#define VDO_S_DBG_RCMD_UMSK                                     (~(((1U<<VDO_S_DBG_RCMD_LEN)-1)<<VDO_S_DBG_RCMD_POS))

/* 0x37c : vdo_pfch_s_dbg_wcmd */
#define VDO_PFCH_S_DBG_WCMD_OFFSET                              (0x37c)
#define VDO_S_DBG_WCMD                                          VDO_S_DBG_WCMD
#define VDO_S_DBG_WCMD_POS                                      (0U)
#define VDO_S_DBG_WCMD_LEN                                      (32U)
#define VDO_S_DBG_WCMD_MSK                                      (((1U<<VDO_S_DBG_WCMD_LEN)-1)<<VDO_S_DBG_WCMD_POS)
#define VDO_S_DBG_WCMD_UMSK                                     (~(((1U<<VDO_S_DBG_WCMD_LEN)-1)<<VDO_S_DBG_WCMD_POS))

/* 0x380 : vdo_pfch_s_dbg_wdata */
#define VDO_PFCH_S_DBG_WDATA_OFFSET                             (0x380)
#define VDO_S_DBG_WDATA                                         VDO_S_DBG_WDATA
#define VDO_S_DBG_WDATA_POS                                     (0U)
#define VDO_S_DBG_WDATA_LEN                                     (32U)
#define VDO_S_DBG_WDATA_MSK                                     (((1U<<VDO_S_DBG_WDATA_LEN)-1)<<VDO_S_DBG_WDATA_POS)
#define VDO_S_DBG_WDATA_UMSK                                    (~(((1U<<VDO_S_DBG_WDATA_LEN)-1)<<VDO_S_DBG_WDATA_POS))

/* 0x384 : vdo_pfch_s_dbg_pfchsta */
#define VDO_PFCH_S_DBG_PFCHSTA_OFFSET                           (0x384)
#define VDO_S_DBG_PFCHSTA                                       VDO_S_DBG_PFCHSTA
#define VDO_S_DBG_PFCHSTA_POS                                   (0U)
#define VDO_S_DBG_PFCHSTA_LEN                                   (32U)
#define VDO_S_DBG_PFCHSTA_MSK                                   (((1U<<VDO_S_DBG_PFCHSTA_LEN)-1)<<VDO_S_DBG_PFCHSTA_POS)
#define VDO_S_DBG_PFCHSTA_UMSK                                  (~(((1U<<VDO_S_DBG_PFCHSTA_LEN)-1)<<VDO_S_DBG_PFCHSTA_POS))

/* 0x388 : vdo_pfchv_s_dbg_reqcnt */
#define VDO_PFCHV_S_DBG_REQCNT_OFFSET                           (0x388)
#define VDO_S_DBGV_REQCNT                                       VDO_S_DBGV_REQCNT
#define VDO_S_DBGV_REQCNT_POS                                   (0U)
#define VDO_S_DBGV_REQCNT_LEN                                   (32U)
#define VDO_S_DBGV_REQCNT_MSK                                   (((1U<<VDO_S_DBGV_REQCNT_LEN)-1)<<VDO_S_DBGV_REQCNT_POS)
#define VDO_S_DBGV_REQCNT_UMSK                                  (~(((1U<<VDO_S_DBGV_REQCNT_LEN)-1)<<VDO_S_DBGV_REQCNT_POS))

/* 0x38c : vdo_pfchv_s_dbg_rcmd */
#define VDO_PFCHV_S_DBG_RCMD_OFFSET                             (0x38c)
#define VDO_S_DBGV_RCMD                                         VDO_S_DBGV_RCMD
#define VDO_S_DBGV_RCMD_POS                                     (0U)
#define VDO_S_DBGV_RCMD_LEN                                     (32U)
#define VDO_S_DBGV_RCMD_MSK                                     (((1U<<VDO_S_DBGV_RCMD_LEN)-1)<<VDO_S_DBGV_RCMD_POS)
#define VDO_S_DBGV_RCMD_UMSK                                    (~(((1U<<VDO_S_DBGV_RCMD_LEN)-1)<<VDO_S_DBGV_RCMD_POS))

/* 0x390 : vdo_pfchv_s_dbg_wcmd */
#define VDO_PFCHV_S_DBG_WCMD_OFFSET                             (0x390)
#define VDO_S_DBGV_WCMD                                         VDO_S_DBGV_WCMD
#define VDO_S_DBGV_WCMD_POS                                     (0U)
#define VDO_S_DBGV_WCMD_LEN                                     (32U)
#define VDO_S_DBGV_WCMD_MSK                                     (((1U<<VDO_S_DBGV_WCMD_LEN)-1)<<VDO_S_DBGV_WCMD_POS)
#define VDO_S_DBGV_WCMD_UMSK                                    (~(((1U<<VDO_S_DBGV_WCMD_LEN)-1)<<VDO_S_DBGV_WCMD_POS))

/* 0x394 : vdo_pfchv_s_dbg_wdata */
#define VDO_PFCHV_S_DBG_WDATA_OFFSET                            (0x394)
#define VDO_S_DBGV_WDATA                                        VDO_S_DBGV_WDATA
#define VDO_S_DBGV_WDATA_POS                                    (0U)
#define VDO_S_DBGV_WDATA_LEN                                    (32U)
#define VDO_S_DBGV_WDATA_MSK                                    (((1U<<VDO_S_DBGV_WDATA_LEN)-1)<<VDO_S_DBGV_WDATA_POS)
#define VDO_S_DBGV_WDATA_UMSK                                   (~(((1U<<VDO_S_DBGV_WDATA_LEN)-1)<<VDO_S_DBGV_WDATA_POS))

/* 0x398 : vdo_pfchv_s_dbg_pfchsta */
#define VDO_PFCHV_S_DBG_PFCHSTA_OFFSET                          (0x398)
#define VDO_S_DBGV_PFCHSTA                                      VDO_S_DBGV_PFCHSTA
#define VDO_S_DBGV_PFCHSTA_POS                                  (0U)
#define VDO_S_DBGV_PFCHSTA_LEN                                  (32U)
#define VDO_S_DBGV_PFCHSTA_MSK                                  (((1U<<VDO_S_DBGV_PFCHSTA_LEN)-1)<<VDO_S_DBGV_PFCHSTA_POS)
#define VDO_S_DBGV_PFCHSTA_UMSK                                 (~(((1U<<VDO_S_DBGV_PFCHSTA_LEN)-1)<<VDO_S_DBGV_PFCHSTA_POS))

/* 0x39c : vdonr */
#define VDONR_OFFSET                                            (0x39c)
#define VDO_NOISELEVEL                                          VDO_NOISELEVEL
#define VDO_NOISELEVEL_POS                                      (0U)
#define VDO_NOISELEVEL_LEN                                      (6U)
#define VDO_NOISELEVEL_MSK                                      (((1U<<VDO_NOISELEVEL_LEN)-1)<<VDO_NOISELEVEL_POS)
#define VDO_NOISELEVEL_UMSK                                     (~(((1U<<VDO_NOISELEVEL_LEN)-1)<<VDO_NOISELEVEL_POS))
#define VDO_TEMPERALFILTERSTRENGTH                              VDO_TEMPERALFILTERSTRENGTH
#define VDO_TEMPERALFILTERSTRENGTH_POS                          (8U)
#define VDO_TEMPERALFILTERSTRENGTH_LEN                          (4U)
#define VDO_TEMPERALFILTERSTRENGTH_MSK                          (((1U<<VDO_TEMPERALFILTERSTRENGTH_LEN)-1)<<VDO_TEMPERALFILTERSTRENGTH_POS)
#define VDO_TEMPERALFILTERSTRENGTH_UMSK                         (~(((1U<<VDO_TEMPERALFILTERSTRENGTH_LEN)-1)<<VDO_TEMPERALFILTERSTRENGTH_POS))
#define VDO_S_NOISELEVEL                                        VDO_S_NOISELEVEL
#define VDO_S_NOISELEVEL_POS                                    (16U)
#define VDO_S_NOISELEVEL_LEN                                    (6U)
#define VDO_S_NOISELEVEL_MSK                                    (((1U<<VDO_S_NOISELEVEL_LEN)-1)<<VDO_S_NOISELEVEL_POS)
#define VDO_S_NOISELEVEL_UMSK                                   (~(((1U<<VDO_S_NOISELEVEL_LEN)-1)<<VDO_S_NOISELEVEL_POS))
#define VDO_S_TEMPERALFILTERSTRENGTH                            VDO_S_TEMPERALFILTERSTRENGTH
#define VDO_S_TEMPERALFILTERSTRENGTH_POS                        (24U)
#define VDO_S_TEMPERALFILTERSTRENGTH_LEN                        (4U)
#define VDO_S_TEMPERALFILTERSTRENGTH_MSK                        (((1U<<VDO_S_TEMPERALFILTERSTRENGTH_LEN)-1)<<VDO_S_TEMPERALFILTERSTRENGTH_POS)
#define VDO_S_TEMPERALFILTERSTRENGTH_UMSK                       (~(((1U<<VDO_S_TEMPERALFILTERSTRENGTH_LEN)-1)<<VDO_S_TEMPERALFILTERSTRENGTH_POS))

/* 0x3a0 : vdonr_mvctrl */
#define VDONR_MVCTRL_OFFSET                                     (0x3a0)
#define VDO_ZMV_PFLEVEL                                         VDO_ZMV_PFLEVEL
#define VDO_ZMV_PFLEVEL_POS                                     (0U)
#define VDO_ZMV_PFLEVEL_LEN                                     (17U)
#define VDO_ZMV_PFLEVEL_MSK                                     (((1U<<VDO_ZMV_PFLEVEL_LEN)-1)<<VDO_ZMV_PFLEVEL_POS)
#define VDO_ZMV_PFLEVEL_UMSK                                    (~(((1U<<VDO_ZMV_PFLEVEL_LEN)-1)<<VDO_ZMV_PFLEVEL_POS))

/* 0x3a4 : vdonr_sta_ctrl */
#define VDONR_STA_CTRL_OFFSET                                   (0x3a4)
#define VDO_YSMLR_THR                                           VDO_YSMLR_THR
#define VDO_YSMLR_THR_POS                                       (0U)
#define VDO_YSMLR_THR_LEN                                       (16U)
#define VDO_YSMLR_THR_MSK                                       (((1U<<VDO_YSMLR_THR_LEN)-1)<<VDO_YSMLR_THR_POS)
#define VDO_YSMLR_THR_UMSK                                      (~(((1U<<VDO_YSMLR_THR_LEN)-1)<<VDO_YSMLR_THR_POS))

/* 0x3a8 : vdonr_absmv_sum */
#define VDONR_ABSMV_SUM_OFFSET                                  (0x3a8)
#define VDO_ABSMV_SUM                                           VDO_ABSMV_SUM
#define VDO_ABSMV_SUM_POS                                       (0U)
#define VDO_ABSMV_SUM_LEN                                       (22U)
#define VDO_ABSMV_SUM_MSK                                       (((1U<<VDO_ABSMV_SUM_LEN)-1)<<VDO_ABSMV_SUM_POS)
#define VDO_ABSMV_SUM_UMSK                                      (~(((1U<<VDO_ABSMV_SUM_LEN)-1)<<VDO_ABSMV_SUM_POS))

/* 0x3ac : vdonr_mvlevel */
#define VDONR_MVLEVEL_OFFSET                                    (0x3ac)
#define VDO_NZMV_MBCNT                                          VDO_NZMV_MBCNT
#define VDO_NZMV_MBCNT_POS                                      (0U)
#define VDO_NZMV_MBCNT_LEN                                      (14U)
#define VDO_NZMV_MBCNT_MSK                                      (((1U<<VDO_NZMV_MBCNT_LEN)-1)<<VDO_NZMV_MBCNT_POS)
#define VDO_NZMV_MBCNT_UMSK                                     (~(((1U<<VDO_NZMV_MBCNT_LEN)-1)<<VDO_NZMV_MBCNT_POS))
#define VDO_YSMLR_MBCNT                                         VDO_YSMLR_MBCNT
#define VDO_YSMLR_MBCNT_POS                                     (16U)
#define VDO_YSMLR_MBCNT_LEN                                     (14U)
#define VDO_YSMLR_MBCNT_MSK                                     (((1U<<VDO_YSMLR_MBCNT_LEN)-1)<<VDO_YSMLR_MBCNT_POS)
#define VDO_YSMLR_MBCNT_UMSK                                    (~(((1U<<VDO_YSMLR_MBCNT_LEN)-1)<<VDO_YSMLR_MBCNT_POS))

/* 0x3b0 : vdonr_pmbsad */
#define VDONR_PMBSAD_OFFSET                                     (0x3b0)
#define VDO_PMB_SAD                                             VDO_PMB_SAD
#define VDO_PMB_SAD_POS                                         (0U)
#define VDO_PMB_SAD_LEN                                         (30U)
#define VDO_PMB_SAD_MSK                                         (((1U<<VDO_PMB_SAD_LEN)-1)<<VDO_PMB_SAD_POS)
#define VDO_PMB_SAD_UMSK                                        (~(((1U<<VDO_PMB_SAD_LEN)-1)<<VDO_PMB_SAD_POS))

/* 0x3b4 : vdonr_imbcnt */
#define VDONR_IMBCNT_OFFSET                                     (0x3b4)
#define VDO_INTRA_MBCNT                                         VDO_INTRA_MBCNT
#define VDO_INTRA_MBCNT_POS                                     (0U)
#define VDO_INTRA_MBCNT_LEN                                     (14U)
#define VDO_INTRA_MBCNT_MSK                                     (((1U<<VDO_INTRA_MBCNT_LEN)-1)<<VDO_INTRA_MBCNT_POS)
#define VDO_INTRA_MBCNT_UMSK                                    (~(((1U<<VDO_INTRA_MBCNT_LEN)-1)<<VDO_INTRA_MBCNT_POS))

/* 0x3b8 : vdonr_s_mvctrl */
#define VDONR_S_MVCTRL_OFFSET                                   (0x3b8)
#define VDO_S_ZMV_PFLEVEL                                       VDO_S_ZMV_PFLEVEL
#define VDO_S_ZMV_PFLEVEL_POS                                   (0U)
#define VDO_S_ZMV_PFLEVEL_LEN                                   (17U)
#define VDO_S_ZMV_PFLEVEL_MSK                                   (((1U<<VDO_S_ZMV_PFLEVEL_LEN)-1)<<VDO_S_ZMV_PFLEVEL_POS)
#define VDO_S_ZMV_PFLEVEL_UMSK                                  (~(((1U<<VDO_S_ZMV_PFLEVEL_LEN)-1)<<VDO_S_ZMV_PFLEVEL_POS))

/* 0x3bc : vdonr_s_sta_ctrl */
#define VDONR_S_STA_CTRL_OFFSET                                 (0x3bc)
#define VDO_S_YSMLR_THR                                         VDO_S_YSMLR_THR
#define VDO_S_YSMLR_THR_POS                                     (0U)
#define VDO_S_YSMLR_THR_LEN                                     (16U)
#define VDO_S_YSMLR_THR_MSK                                     (((1U<<VDO_S_YSMLR_THR_LEN)-1)<<VDO_S_YSMLR_THR_POS)
#define VDO_S_YSMLR_THR_UMSK                                    (~(((1U<<VDO_S_YSMLR_THR_LEN)-1)<<VDO_S_YSMLR_THR_POS))

/* 0x3c0 : vdonr_s_absmv_sum */
#define VDONR_S_ABSMV_SUM_OFFSET                                (0x3c0)
#define VDO_S_ABSMV_SUM                                         VDO_S_ABSMV_SUM
#define VDO_S_ABSMV_SUM_POS                                     (0U)
#define VDO_S_ABSMV_SUM_LEN                                     (22U)
#define VDO_S_ABSMV_SUM_MSK                                     (((1U<<VDO_S_ABSMV_SUM_LEN)-1)<<VDO_S_ABSMV_SUM_POS)
#define VDO_S_ABSMV_SUM_UMSK                                    (~(((1U<<VDO_S_ABSMV_SUM_LEN)-1)<<VDO_S_ABSMV_SUM_POS))

/* 0x3c4 : vdonr_s_mvlevel */
#define VDONR_S_MVLEVEL_OFFSET                                  (0x3c4)
#define VDO_S_NZMV_MBCNT                                        VDO_S_NZMV_MBCNT
#define VDO_S_NZMV_MBCNT_POS                                    (0U)
#define VDO_S_NZMV_MBCNT_LEN                                    (14U)
#define VDO_S_NZMV_MBCNT_MSK                                    (((1U<<VDO_S_NZMV_MBCNT_LEN)-1)<<VDO_S_NZMV_MBCNT_POS)
#define VDO_S_NZMV_MBCNT_UMSK                                   (~(((1U<<VDO_S_NZMV_MBCNT_LEN)-1)<<VDO_S_NZMV_MBCNT_POS))
#define VDO_S_YSMLR_MBCNT                                       VDO_S_YSMLR_MBCNT
#define VDO_S_YSMLR_MBCNT_POS                                   (16U)
#define VDO_S_YSMLR_MBCNT_LEN                                   (14U)
#define VDO_S_YSMLR_MBCNT_MSK                                   (((1U<<VDO_S_YSMLR_MBCNT_LEN)-1)<<VDO_S_YSMLR_MBCNT_POS)
#define VDO_S_YSMLR_MBCNT_UMSK                                  (~(((1U<<VDO_S_YSMLR_MBCNT_LEN)-1)<<VDO_S_YSMLR_MBCNT_POS))

/* 0x3c8 : vdonr_s_pmbsad */
#define VDONR_S_PMBSAD_OFFSET                                   (0x3c8)
#define VDO_S_PMB_SAD                                           VDO_S_PMB_SAD
#define VDO_S_PMB_SAD_POS                                       (0U)
#define VDO_S_PMB_SAD_LEN                                       (30U)
#define VDO_S_PMB_SAD_MSK                                       (((1U<<VDO_S_PMB_SAD_LEN)-1)<<VDO_S_PMB_SAD_POS)
#define VDO_S_PMB_SAD_UMSK                                      (~(((1U<<VDO_S_PMB_SAD_LEN)-1)<<VDO_S_PMB_SAD_POS))

/* 0x3cc : vdonr_s_imbcnt */
#define VDONR_S_IMBCNT_OFFSET                                   (0x3cc)
#define VDO_S_INTRA_MBCNT                                       VDO_S_INTRA_MBCNT
#define VDO_S_INTRA_MBCNT_POS                                   (0U)
#define VDO_S_INTRA_MBCNT_LEN                                   (14U)
#define VDO_S_INTRA_MBCNT_MSK                                   (((1U<<VDO_S_INTRA_MBCNT_LEN)-1)<<VDO_S_INTRA_MBCNT_POS)
#define VDO_S_INTRA_MBCNT_UMSK                                  (~(((1U<<VDO_S_INTRA_MBCNT_LEN)-1)<<VDO_S_INTRA_MBCNT_POS))

/* 0x3d0 : vdo_stuf_dbg */
#define VDO_STUF_DBG_OFFSET                                     (0x3d0)
#define VDO_PIC_BYCNT                                           VDO_PIC_BYCNT
#define VDO_PIC_BYCNT_POS                                       (0U)
#define VDO_PIC_BYCNT_LEN                                       (26U)
#define VDO_PIC_BYCNT_MSK                                       (((1U<<VDO_PIC_BYCNT_LEN)-1)<<VDO_PIC_BYCNT_POS)
#define VDO_PIC_BYCNT_UMSK                                      (~(((1U<<VDO_PIC_BYCNT_LEN)-1)<<VDO_PIC_BYCNT_POS))
#define VDO_PIC_BYCNT_OVF                                       VDO_PIC_BYCNT_OVF
#define VDO_PIC_BYCNT_OVF_POS                                   (26U)
#define VDO_PIC_BYCNT_OVF_LEN                                   (1U)
#define VDO_PIC_BYCNT_OVF_MSK                                   (((1U<<VDO_PIC_BYCNT_OVF_LEN)-1)<<VDO_PIC_BYCNT_OVF_POS)
#define VDO_PIC_BYCNT_OVF_UMSK                                  (~(((1U<<VDO_PIC_BYCNT_OVF_LEN)-1)<<VDO_PIC_BYCNT_OVF_POS))
#define VDO_STUF_OVF                                            VDO_STUF_OVF
#define VDO_STUF_OVF_POS                                        (27U)
#define VDO_STUF_OVF_LEN                                        (1U)
#define VDO_STUF_OVF_MSK                                        (((1U<<VDO_STUF_OVF_LEN)-1)<<VDO_STUF_OVF_POS)
#define VDO_STUF_OVF_UMSK                                       (~(((1U<<VDO_STUF_OVF_LEN)-1)<<VDO_STUF_OVF_POS))
#define VDO_BINCNT_OVF                                          VDO_BINCNT_OVF
#define VDO_BINCNT_OVF_POS                                      (28U)
#define VDO_BINCNT_OVF_LEN                                      (1U)
#define VDO_BINCNT_OVF_MSK                                      (((1U<<VDO_BINCNT_OVF_LEN)-1)<<VDO_BINCNT_OVF_POS)
#define VDO_BINCNT_OVF_UMSK                                     (~(((1U<<VDO_BINCNT_OVF_LEN)-1)<<VDO_BINCNT_OVF_POS))

/* 0x3d4 : vdo_nal_dbg1 */
#define VDO_NAL_DBG1_OFFSET                                     (0x3d4)
#define VDO_STUF_CNT                                            VDO_STUF_CNT
#define VDO_STUF_CNT_POS                                        (0U)
#define VDO_STUF_CNT_LEN                                        (26U)
#define VDO_STUF_CNT_MSK                                        (((1U<<VDO_STUF_CNT_LEN)-1)<<VDO_STUF_CNT_POS)
#define VDO_STUF_CNT_UMSK                                       (~(((1U<<VDO_STUF_CNT_LEN)-1)<<VDO_STUF_CNT_POS))
#define VDO_SH_STATE                                            VDO_SH_STATE
#define VDO_SH_STATE_POS                                        (26U)
#define VDO_SH_STATE_LEN                                        (6U)
#define VDO_SH_STATE_MSK                                        (((1U<<VDO_SH_STATE_LEN)-1)<<VDO_SH_STATE_POS)
#define VDO_SH_STATE_UMSK                                       (~(((1U<<VDO_SH_STATE_LEN)-1)<<VDO_SH_STATE_POS))

/* 0x3d8 : vdo_nal_dbg2 */
#define VDO_NAL_DBG2_OFFSET                                     (0x3d8)
#define VDO_BINCNTX3                                            VDO_BINCNTX3
#define VDO_BINCNTX3_POS                                        (0U)
#define VDO_BINCNTX3_LEN                                        (30U)
#define VDO_BINCNTX3_MSK                                        (((1U<<VDO_BINCNTX3_LEN)-1)<<VDO_BINCNTX3_POS)
#define VDO_BINCNTX3_UMSK                                       (~(((1U<<VDO_BINCNTX3_LEN)-1)<<VDO_BINCNTX3_POS))

/* 0x3dc : vdo_nal_dbg3 */
#define VDO_NAL_DBG3_OFFSET                                     (0x3dc)
#define VDO_MP_MBX                                              VDO_MP_MBX
#define VDO_MP_MBX_POS                                          (0U)
#define VDO_MP_MBX_LEN                                          (7U)
#define VDO_MP_MBX_MSK                                          (((1U<<VDO_MP_MBX_LEN)-1)<<VDO_MP_MBX_POS)
#define VDO_MP_MBX_UMSK                                         (~(((1U<<VDO_MP_MBX_LEN)-1)<<VDO_MP_MBX_POS))
#define VDO_MP_MBY                                              VDO_MP_MBY
#define VDO_MP_MBY_POS                                          (8U)
#define VDO_MP_MBY_LEN                                          (7U)
#define VDO_MP_MBY_MSK                                          (((1U<<VDO_MP_MBY_LEN)-1)<<VDO_MP_MBY_POS)
#define VDO_MP_MBY_UMSK                                         (~(((1U<<VDO_MP_MBY_LEN)-1)<<VDO_MP_MBY_POS))

/* 0x3e0 : vdo_roi_dbg */
#define VDO_ROI_DBG_OFFSET                                      (0x3e0)
#define VDO_ROI_PMBBITS                                         VDO_ROI_PMBBITS
#define VDO_ROI_PMBBITS_POS                                     (0U)
#define VDO_ROI_PMBBITS_LEN                                     (12U)
#define VDO_ROI_PMBBITS_MSK                                     (((1U<<VDO_ROI_PMBBITS_LEN)-1)<<VDO_ROI_PMBBITS_POS)
#define VDO_ROI_PMBBITS_UMSK                                    (~(((1U<<VDO_ROI_PMBBITS_LEN)-1)<<VDO_ROI_PMBBITS_POS))
#define VDO_NROI_PMBBITS                                        VDO_NROI_PMBBITS
#define VDO_NROI_PMBBITS_POS                                    (16U)
#define VDO_NROI_PMBBITS_LEN                                    (12U)
#define VDO_NROI_PMBBITS_MSK                                    (((1U<<VDO_NROI_PMBBITS_LEN)-1)<<VDO_NROI_PMBBITS_POS)
#define VDO_NROI_PMBBITS_UMSK                                   (~(((1U<<VDO_NROI_PMBBITS_LEN)-1)<<VDO_NROI_PMBBITS_POS))

/* 0x3e4 : vdo_rc_dbg */
#define VDO_RC_DBG_OFFSET                                       (0x3e4)
#define VDO_RC_MIN_QP                                           VDO_RC_MIN_QP
#define VDO_RC_MIN_QP_POS                                       (0U)
#define VDO_RC_MIN_QP_LEN                                       (6U)
#define VDO_RC_MIN_QP_MSK                                       (((1U<<VDO_RC_MIN_QP_LEN)-1)<<VDO_RC_MIN_QP_POS)
#define VDO_RC_MIN_QP_UMSK                                      (~(((1U<<VDO_RC_MIN_QP_LEN)-1)<<VDO_RC_MIN_QP_POS))
#define VDO_RC_QP                                               VDO_RC_QP
#define VDO_RC_QP_POS                                           (8U)
#define VDO_RC_QP_LEN                                           (6U)
#define VDO_RC_QP_MSK                                           (((1U<<VDO_RC_QP_LEN)-1)<<VDO_RC_QP_POS)
#define VDO_RC_QP_UMSK                                          (~(((1U<<VDO_RC_QP_LEN)-1)<<VDO_RC_QP_POS))

/* 0x3e8 : vdo_s_stuf_dbg */
#define VDO_S_STUF_DBG_OFFSET                                   (0x3e8)
#define VDO_S_PIC_BYCNT                                         VDO_S_PIC_BYCNT
#define VDO_S_PIC_BYCNT_POS                                     (0U)
#define VDO_S_PIC_BYCNT_LEN                                     (26U)
#define VDO_S_PIC_BYCNT_MSK                                     (((1U<<VDO_S_PIC_BYCNT_LEN)-1)<<VDO_S_PIC_BYCNT_POS)
#define VDO_S_PIC_BYCNT_UMSK                                    (~(((1U<<VDO_S_PIC_BYCNT_LEN)-1)<<VDO_S_PIC_BYCNT_POS))
#define VDO_S_PIC_BYCNT_OVF                                     VDO_S_PIC_BYCNT_OVF
#define VDO_S_PIC_BYCNT_OVF_POS                                 (26U)
#define VDO_S_PIC_BYCNT_OVF_LEN                                 (1U)
#define VDO_S_PIC_BYCNT_OVF_MSK                                 (((1U<<VDO_S_PIC_BYCNT_OVF_LEN)-1)<<VDO_S_PIC_BYCNT_OVF_POS)
#define VDO_S_PIC_BYCNT_OVF_UMSK                                (~(((1U<<VDO_S_PIC_BYCNT_OVF_LEN)-1)<<VDO_S_PIC_BYCNT_OVF_POS))
#define VDO_S_STUF_OVF                                          VDO_S_STUF_OVF
#define VDO_S_STUF_OVF_POS                                      (27U)
#define VDO_S_STUF_OVF_LEN                                      (1U)
#define VDO_S_STUF_OVF_MSK                                      (((1U<<VDO_S_STUF_OVF_LEN)-1)<<VDO_S_STUF_OVF_POS)
#define VDO_S_STUF_OVF_UMSK                                     (~(((1U<<VDO_S_STUF_OVF_LEN)-1)<<VDO_S_STUF_OVF_POS))
#define VDO_S_BINCNT_OVF                                        VDO_S_BINCNT_OVF
#define VDO_S_BINCNT_OVF_POS                                    (28U)
#define VDO_S_BINCNT_OVF_LEN                                    (1U)
#define VDO_S_BINCNT_OVF_MSK                                    (((1U<<VDO_S_BINCNT_OVF_LEN)-1)<<VDO_S_BINCNT_OVF_POS)
#define VDO_S_BINCNT_OVF_UMSK                                   (~(((1U<<VDO_S_BINCNT_OVF_LEN)-1)<<VDO_S_BINCNT_OVF_POS))

/* 0x3ec : vdo_s_nal_dbg1 */
#define VDO_S_NAL_DBG1_OFFSET                                   (0x3ec)
#define VDO_S_STUF_CNT                                          VDO_S_STUF_CNT
#define VDO_S_STUF_CNT_POS                                      (0U)
#define VDO_S_STUF_CNT_LEN                                      (26U)
#define VDO_S_STUF_CNT_MSK                                      (((1U<<VDO_S_STUF_CNT_LEN)-1)<<VDO_S_STUF_CNT_POS)
#define VDO_S_STUF_CNT_UMSK                                     (~(((1U<<VDO_S_STUF_CNT_LEN)-1)<<VDO_S_STUF_CNT_POS))
#define VDO_S_SH_STATE                                          VDO_S_SH_STATE
#define VDO_S_SH_STATE_POS                                      (26U)
#define VDO_S_SH_STATE_LEN                                      (6U)
#define VDO_S_SH_STATE_MSK                                      (((1U<<VDO_S_SH_STATE_LEN)-1)<<VDO_S_SH_STATE_POS)
#define VDO_S_SH_STATE_UMSK                                     (~(((1U<<VDO_S_SH_STATE_LEN)-1)<<VDO_S_SH_STATE_POS))

/* 0x3f0 : vdo_s_nal_dbg2 */
#define VDO_S_NAL_DBG2_OFFSET                                   (0x3f0)
#define VDO_S_BINCNTX3                                          VDO_S_BINCNTX3
#define VDO_S_BINCNTX3_POS                                      (0U)
#define VDO_S_BINCNTX3_LEN                                      (30U)
#define VDO_S_BINCNTX3_MSK                                      (((1U<<VDO_S_BINCNTX3_LEN)-1)<<VDO_S_BINCNTX3_POS)
#define VDO_S_BINCNTX3_UMSK                                     (~(((1U<<VDO_S_BINCNTX3_LEN)-1)<<VDO_S_BINCNTX3_POS))

/* 0x3f4 : vdo_s_nal_dbg3 */
#define VDO_S_NAL_DBG3_OFFSET                                   (0x3f4)
#define VDO_S_MP_MBX                                            VDO_S_MP_MBX
#define VDO_S_MP_MBX_POS                                        (0U)
#define VDO_S_MP_MBX_LEN                                        (7U)
#define VDO_S_MP_MBX_MSK                                        (((1U<<VDO_S_MP_MBX_LEN)-1)<<VDO_S_MP_MBX_POS)
#define VDO_S_MP_MBX_UMSK                                       (~(((1U<<VDO_S_MP_MBX_LEN)-1)<<VDO_S_MP_MBX_POS))
#define VDO_S_MP_MBY                                            VDO_S_MP_MBY
#define VDO_S_MP_MBY_POS                                        (8U)
#define VDO_S_MP_MBY_LEN                                        (7U)
#define VDO_S_MP_MBY_MSK                                        (((1U<<VDO_S_MP_MBY_LEN)-1)<<VDO_S_MP_MBY_POS)
#define VDO_S_MP_MBY_UMSK                                       (~(((1U<<VDO_S_MP_MBY_LEN)-1)<<VDO_S_MP_MBY_POS))

/* 0x3f8 : vdo_s_roi_dbg */
#define VDO_S_ROI_DBG_OFFSET                                    (0x3f8)
#define VDO_S_ROI_PMBBITS                                       VDO_S_ROI_PMBBITS
#define VDO_S_ROI_PMBBITS_POS                                   (0U)
#define VDO_S_ROI_PMBBITS_LEN                                   (12U)
#define VDO_S_ROI_PMBBITS_MSK                                   (((1U<<VDO_S_ROI_PMBBITS_LEN)-1)<<VDO_S_ROI_PMBBITS_POS)
#define VDO_S_ROI_PMBBITS_UMSK                                  (~(((1U<<VDO_S_ROI_PMBBITS_LEN)-1)<<VDO_S_ROI_PMBBITS_POS))
#define VDO_S_NROI_PMBBITS                                      VDO_S_NROI_PMBBITS
#define VDO_S_NROI_PMBBITS_POS                                  (16U)
#define VDO_S_NROI_PMBBITS_LEN                                  (12U)
#define VDO_S_NROI_PMBBITS_MSK                                  (((1U<<VDO_S_NROI_PMBBITS_LEN)-1)<<VDO_S_NROI_PMBBITS_POS)
#define VDO_S_NROI_PMBBITS_UMSK                                 (~(((1U<<VDO_S_NROI_PMBBITS_LEN)-1)<<VDO_S_NROI_PMBBITS_POS))

/* 0x3fc : vdo_s_rc_dbg */
#define VDO_S_RC_DBG_OFFSET                                     (0x3fc)
#define VDO_S_RC_MIN_QP                                         VDO_S_RC_MIN_QP
#define VDO_S_RC_MIN_QP_POS                                     (0U)
#define VDO_S_RC_MIN_QP_LEN                                     (6U)
#define VDO_S_RC_MIN_QP_MSK                                     (((1U<<VDO_S_RC_MIN_QP_LEN)-1)<<VDO_S_RC_MIN_QP_POS)
#define VDO_S_RC_MIN_QP_UMSK                                    (~(((1U<<VDO_S_RC_MIN_QP_LEN)-1)<<VDO_S_RC_MIN_QP_POS))
#define VDO_S_RC_QP                                             VDO_S_RC_QP
#define VDO_S_RC_QP_POS                                         (8U)
#define VDO_S_RC_QP_LEN                                         (6U)
#define VDO_S_RC_QP_MSK                                         (((1U<<VDO_S_RC_QP_LEN)-1)<<VDO_S_RC_QP_POS)
#define VDO_S_RC_QP_UMSK                                        (~(((1U<<VDO_S_RC_QP_LEN)-1)<<VDO_S_RC_QP_POS))

/* 0x400 : vdo_refaxi_dbg */
#define VDO_REFAXI_DBG_OFFSET                                   (0x400)
#define VDO_REF2AXI_BUSY                                        VDO_REF2AXI_BUSY
#define VDO_REF2AXI_BUSY_POS                                    (0U)
#define VDO_REF2AXI_BUSY_LEN                                    (1U)
#define VDO_REF2AXI_BUSY_MSK                                    (((1U<<VDO_REF2AXI_BUSY_LEN)-1)<<VDO_REF2AXI_BUSY_POS)
#define VDO_REF2AXI_BUSY_UMSK                                   (~(((1U<<VDO_REF2AXI_BUSY_LEN)-1)<<VDO_REF2AXI_BUSY_POS))
#define VDO_REF_RFIFO_ERROR                                     VDO_REF_RFIFO_ERROR
#define VDO_REF_RFIFO_ERROR_POS                                 (4U)
#define VDO_REF_RFIFO_ERROR_LEN                                 (2U)
#define VDO_REF_RFIFO_ERROR_MSK                                 (((1U<<VDO_REF_RFIFO_ERROR_LEN)-1)<<VDO_REF_RFIFO_ERROR_POS)
#define VDO_REF_RFIFO_ERROR_UMSK                                (~(((1U<<VDO_REF_RFIFO_ERROR_LEN)-1)<<VDO_REF_RFIFO_ERROR_POS))
#define VDO_REF_WFIFO_ERROR                                     VDO_REF_WFIFO_ERROR
#define VDO_REF_WFIFO_ERROR_POS                                 (6U)
#define VDO_REF_WFIFO_ERROR_LEN                                 (2U)
#define VDO_REF_WFIFO_ERROR_MSK                                 (((1U<<VDO_REF_WFIFO_ERROR_LEN)-1)<<VDO_REF_WFIFO_ERROR_POS)
#define VDO_REF_WFIFO_ERROR_UMSK                                (~(((1U<<VDO_REF_WFIFO_ERROR_LEN)-1)<<VDO_REF_WFIFO_ERROR_POS))
#define VDO_REF_RFIFO_EMPTY                                     VDO_REF_RFIFO_EMPTY
#define VDO_REF_RFIFO_EMPTY_POS                                 (8U)
#define VDO_REF_RFIFO_EMPTY_LEN                                 (3U)
#define VDO_REF_RFIFO_EMPTY_MSK                                 (((1U<<VDO_REF_RFIFO_EMPTY_LEN)-1)<<VDO_REF_RFIFO_EMPTY_POS)
#define VDO_REF_RFIFO_EMPTY_UMSK                                (~(((1U<<VDO_REF_RFIFO_EMPTY_LEN)-1)<<VDO_REF_RFIFO_EMPTY_POS))
#define VDO_REF_WFIFO_EMPTY                                     VDO_REF_WFIFO_EMPTY
#define VDO_REF_WFIFO_EMPTY_POS                                 (12U)
#define VDO_REF_WFIFO_EMPTY_LEN                                 (5U)
#define VDO_REF_WFIFO_EMPTY_MSK                                 (((1U<<VDO_REF_WFIFO_EMPTY_LEN)-1)<<VDO_REF_WFIFO_EMPTY_POS)
#define VDO_REF_WFIFO_EMPTY_UMSK                                (~(((1U<<VDO_REF_WFIFO_EMPTY_LEN)-1)<<VDO_REF_WFIFO_EMPTY_POS))

/* 0x404 : vdo_pfchaxi_dbg */
#define VDO_PFCHAXI_DBG_OFFSET                                  (0x404)
#define VDO_PFCH_RFIFO_BUSY                                     VDO_PFCH_RFIFO_BUSY
#define VDO_PFCH_RFIFO_BUSY_POS                                 (0U)
#define VDO_PFCH_RFIFO_BUSY_LEN                                 (1U)
#define VDO_PFCH_RFIFO_BUSY_MSK                                 (((1U<<VDO_PFCH_RFIFO_BUSY_LEN)-1)<<VDO_PFCH_RFIFO_BUSY_POS)
#define VDO_PFCH_RFIFO_BUSY_UMSK                                (~(((1U<<VDO_PFCH_RFIFO_BUSY_LEN)-1)<<VDO_PFCH_RFIFO_BUSY_POS))
#define VDO_PFCH_RFIFO_ERROR                                    VDO_PFCH_RFIFO_ERROR
#define VDO_PFCH_RFIFO_ERROR_POS                                (4U)
#define VDO_PFCH_RFIFO_ERROR_LEN                                (2U)
#define VDO_PFCH_RFIFO_ERROR_MSK                                (((1U<<VDO_PFCH_RFIFO_ERROR_LEN)-1)<<VDO_PFCH_RFIFO_ERROR_POS)
#define VDO_PFCH_RFIFO_ERROR_UMSK                               (~(((1U<<VDO_PFCH_RFIFO_ERROR_LEN)-1)<<VDO_PFCH_RFIFO_ERROR_POS))
#define VDO_PFCH_RFIFO_EMPTY                                    VDO_PFCH_RFIFO_EMPTY
#define VDO_PFCH_RFIFO_EMPTY_POS                                (8U)
#define VDO_PFCH_RFIFO_EMPTY_LEN                                (3U)
#define VDO_PFCH_RFIFO_EMPTY_MSK                                (((1U<<VDO_PFCH_RFIFO_EMPTY_LEN)-1)<<VDO_PFCH_RFIFO_EMPTY_POS)
#define VDO_PFCH_RFIFO_EMPTY_UMSK                               (~(((1U<<VDO_PFCH_RFIFO_EMPTY_LEN)-1)<<VDO_PFCH_RFIFO_EMPTY_POS))
#define VDO_PFCHV_RFIFO_BUSY                                    VDO_PFCHV_RFIFO_BUSY
#define VDO_PFCHV_RFIFO_BUSY_POS                                (12U)
#define VDO_PFCHV_RFIFO_BUSY_LEN                                (1U)
#define VDO_PFCHV_RFIFO_BUSY_MSK                                (((1U<<VDO_PFCHV_RFIFO_BUSY_LEN)-1)<<VDO_PFCHV_RFIFO_BUSY_POS)
#define VDO_PFCHV_RFIFO_BUSY_UMSK                               (~(((1U<<VDO_PFCHV_RFIFO_BUSY_LEN)-1)<<VDO_PFCHV_RFIFO_BUSY_POS))
#define VDO_PFCHV_RFIFO_ERROR                                   VDO_PFCHV_RFIFO_ERROR
#define VDO_PFCHV_RFIFO_ERROR_POS                               (16U)
#define VDO_PFCHV_RFIFO_ERROR_LEN                               (2U)
#define VDO_PFCHV_RFIFO_ERROR_MSK                               (((1U<<VDO_PFCHV_RFIFO_ERROR_LEN)-1)<<VDO_PFCHV_RFIFO_ERROR_POS)
#define VDO_PFCHV_RFIFO_ERROR_UMSK                              (~(((1U<<VDO_PFCHV_RFIFO_ERROR_LEN)-1)<<VDO_PFCHV_RFIFO_ERROR_POS))
#define VDO_PFCHV_RFIFO_EMPTY                                   VDO_PFCHV_RFIFO_EMPTY
#define VDO_PFCHV_RFIFO_EMPTY_POS                               (20U)
#define VDO_PFCHV_RFIFO_EMPTY_LEN                               (3U)
#define VDO_PFCHV_RFIFO_EMPTY_MSK                               (((1U<<VDO_PFCHV_RFIFO_EMPTY_LEN)-1)<<VDO_PFCHV_RFIFO_EMPTY_POS)
#define VDO_PFCHV_RFIFO_EMPTY_UMSK                              (~(((1U<<VDO_PFCHV_RFIFO_EMPTY_LEN)-1)<<VDO_PFCHV_RFIFO_EMPTY_POS))

/* 0x408 : vdo_bsaxi_dbg */
#define VDO_BSAXI_DBG_OFFSET                                    (0x408)
#define VDO_BS_WFIFO_BUSY                                       VDO_BS_WFIFO_BUSY
#define VDO_BS_WFIFO_BUSY_POS                                   (0U)
#define VDO_BS_WFIFO_BUSY_LEN                                   (1U)
#define VDO_BS_WFIFO_BUSY_MSK                                   (((1U<<VDO_BS_WFIFO_BUSY_LEN)-1)<<VDO_BS_WFIFO_BUSY_POS)
#define VDO_BS_WFIFO_BUSY_UMSK                                  (~(((1U<<VDO_BS_WFIFO_BUSY_LEN)-1)<<VDO_BS_WFIFO_BUSY_POS))
#define VDO_BS_WFIFO_ERROR                                      VDO_BS_WFIFO_ERROR
#define VDO_BS_WFIFO_ERROR_POS                                  (4U)
#define VDO_BS_WFIFO_ERROR_LEN                                  (2U)
#define VDO_BS_WFIFO_ERROR_MSK                                  (((1U<<VDO_BS_WFIFO_ERROR_LEN)-1)<<VDO_BS_WFIFO_ERROR_POS)
#define VDO_BS_WFIFO_ERROR_UMSK                                 (~(((1U<<VDO_BS_WFIFO_ERROR_LEN)-1)<<VDO_BS_WFIFO_ERROR_POS))
#define VDO_BS_WFIFO_EMPTY                                      VDO_BS_WFIFO_EMPTY
#define VDO_BS_WFIFO_EMPTY_POS                                  (8U)
#define VDO_BS_WFIFO_EMPTY_LEN                                  (5U)
#define VDO_BS_WFIFO_EMPTY_MSK                                  (((1U<<VDO_BS_WFIFO_EMPTY_LEN)-1)<<VDO_BS_WFIFO_EMPTY_POS)
#define VDO_BS_WFIFO_EMPTY_UMSK                                 (~(((1U<<VDO_BS_WFIFO_EMPTY_LEN)-1)<<VDO_BS_WFIFO_EMPTY_POS))
#define VDO_BS_ST                                               VDO_BS_ST
#define VDO_BS_ST_POS                                           (16U)
#define VDO_BS_ST_LEN                                           (2U)
#define VDO_BS_ST_MSK                                           (((1U<<VDO_BS_ST_LEN)-1)<<VDO_BS_ST_POS)
#define VDO_BS_ST_UMSK                                          (~(((1U<<VDO_BS_ST_LEN)-1)<<VDO_BS_ST_POS))

/* 0x40c : vdo_frame_id */
#define VDO_FRAME_ID_OFFSET                                     (0x40c)
#define VDO_FRAME_ID                                            VDO_FRAME_ID
#define VDO_FRAME_ID_POS                                        (0U)
#define VDO_FRAME_ID_LEN                                        (32U)
#define VDO_FRAME_ID_MSK                                        (((1U<<VDO_FRAME_ID_LEN)-1)<<VDO_FRAME_ID_POS)
#define VDO_FRAME_ID_UMSK                                       (~(((1U<<VDO_FRAME_ID_LEN)-1)<<VDO_FRAME_ID_POS))

/* 0x410 : vdo_s_vdo_frame_id */
#define VDO_S_VDO_FRAME_ID_OFFSET                               (0x410)
#define VDO_S_FRAME_ID                                          VDO_S_FRAME_ID
#define VDO_S_FRAME_ID_POS                                      (0U)
#define VDO_S_FRAME_ID_LEN                                      (32U)
#define VDO_S_FRAME_ID_MSK                                      (((1U<<VDO_S_FRAME_ID_LEN)-1)<<VDO_S_FRAME_ID_POS)
#define VDO_S_FRAME_ID_UMSK                                     (~(((1U<<VDO_S_FRAME_ID_LEN)-1)<<VDO_S_FRAME_ID_POS))

 struct vdo_reg {

    /* 0x0 : h264_encoder_ctrl */
    union {
        struct {
            uint32_t cfg_enc_ctrl_mby_idx           :  7; /* [ 6: 0],       r/w,       0x0 */
            uint32_t reserved_7                     :  1; /* [    7],      rsvd,       0x0 */
            uint32_t cfg_core_clk_en                :  1; /* [    8],       r/w,       0x0 */
            uint32_t cfg_zstuf_dis                  :  1; /* [    9],       r/w,       0x0 */
            uint32_t cfg_qr_upd                     :  1; /* [   10],       w1p,       0x0 */
            uint32_t cfg_s_qr_upd                   :  1; /* [   11],       w1p,       0x0 */
            uint32_t cfg_mem_clk_en                 :  1; /* [   12],       r/w,       0x0 */
            uint32_t cfg_rc_gop_upd                 :  1; /* [   13],       w1p,       0x0 */
            uint32_t cfg_s_rc_gop_upd               :  1; /* [   14],       w1p,       0x0 */
            uint32_t cfg_duo_bs_en                  :  1; /* [   15],       r/w,       0x0 */
            uint32_t cfg_buf_clr                    :  1; /* [   16],       w1p,       0x0 */
            uint32_t cfg_s_buf_clr                  :  1; /* [   17],       w1p,       0x0 */
            uint32_t cfg_vdonr_en                   :  1; /* [   18],       r/w,       0x0 */
            uint32_t cfg_s_vdonr_en                 :  1; /* [   19],       r/w,       0x0 */
            uint32_t cfg_bs_status_init             :  1; /* [   20],       w1p,       0x0 */
            uint32_t cfg_s_bs_status_init           :  1; /* [   21],       w1p,       0x0 */
            uint32_t cfg_src_line_clr               :  1; /* [   22],       w1p,       0x0 */
            uint32_t cfg_s_src_line_clr             :  1; /* [   23],       w1p,       0x0 */
            uint32_t cfg_ctrl_mode                  :  2; /* [25:24],       r/w,       0x0 */
            uint32_t cfg_cref_en                    :  1; /* [   26],       r/w,       0x0 */
            uint32_t cfg_s_cref_en                  :  1; /* [   27],       r/w,       0x0 */
            uint32_t cfg_frame_start                :  1; /* [   28],       w1p,       0x0 */
            uint32_t cfg_enc_seq_en                 :  1; /* [   29],       r/w,       0x0 */
            uint32_t cfg_s_frame_start              :  1; /* [   30],       w1p,       0x0 */
            uint32_t cfg_s_enc_seq_en               :  1; /* [   31],       r/w,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_encoder_ctrl;

    /* 0x4 : h264_frame_size */
    union {
        struct {
            uint32_t cfg_frame_width                : 11; /* [10: 0],       r/w,       0x0 */
            uint32_t reserved_11_15                 :  5; /* [15:11],      rsvd,       0x0 */
            uint32_t cfg_frame_height               : 11; /* [26:16],       r/w,       0x0 */
            uint32_t reserved_27_31                 :  5; /* [31:27],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_frame_size;

    /* 0x8 : h264_frame_base_addr_y */
    union {
        struct {
            uint32_t cfg_frame_base_addr_y          : 32; /* [31: 0],       r/w,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_frame_base_addr_y;

    /* 0xc : h264_frame_base_addr_uv */
    union {
        struct {
            uint32_t cfg_frame_base_addr_uv         : 32; /* [31: 0],       r/w,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_frame_base_addr_uv;

    /* 0x10 : h264_bs_base_addr */
    union {
        struct {
            uint32_t cfg_bs_base_addr               : 32; /* [31: 0],       r/w,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_bs_base_addr;

    /* 0x14 : h264_lb_base_addr */
    union {
        struct {
            uint32_t cfg_lb_base_addr               : 32; /* [31: 0],       r/w,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_lb_base_addr;

    /* 0x18 : h264_bs_size */
    union {
        struct {
            uint32_t cfg_bs_size                    : 32; /* [31: 0],       r/w,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_bs_size;

    /* 0x1c : h264_bs_full_thr */
    union {
        struct {
            uint32_t cfg_bs_full_thr                : 32; /* [31: 0],       r/w,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_bs_full_thr;

    /* 0x20 : h264_src_bf_height */
    union {
        struct {
            uint32_t cfg_c_src_bf_height            : 15; /* [14: 0],       r/w,       0x0 */
            uint32_t reserved_15                    :  1; /* [   15],      rsvd,       0x0 */
            uint32_t cfg_y_src_bf_height            : 15; /* [30:16],       r/w,       0x0 */
            uint32_t reserved_31                    :  1; /* [   31],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_src_bf_height;

    /* 0x24 : core_reg0 */
    union {
        struct {
            uint32_t enc_en                         :  1; /* [    0],       r/w,       0x0 */
            uint32_t reserved_1_11                  : 11; /* [11: 1],      rsvd,       0x0 */
            uint32_t vui_aspect_info                :  1; /* [   12],       r/w,       0x0 */
            uint32_t vui_fixed_f_rate               :  1; /* [   13],       r/w,       0x0 */
            uint32_t vui_timing_info                :  1; /* [   14],       r/w,       0x0 */
            uint32_t idr_enable                     :  1; /* [   15],       r/w,       0x0 */
            uint32_t s_enc_en                       :  1; /* [   16],       r/w,       0x0 */
            uint32_t reserved_17_27                 : 11; /* [27:17],      rsvd,       0x0 */
            uint32_t s_vui_aspect_info              :  1; /* [   28],       r/w,       0x0 */
            uint32_t s_vui_fixed_f_rate             :  1; /* [   29],       r/w,       0x0 */
            uint32_t s_vui_timing_info              :  1; /* [   30],       r/w,       0x0 */
            uint32_t s_idr_enable                   :  1; /* [   31],       r/w,       0x0 */
        }BF;
        uint32_t WORD;
    } core_reg0;

    /* 0x28 : core_reg1 */
    union {
        struct {
            uint32_t img_width                      : 11; /* [10: 0],       r/w,       0x0 */
            uint32_t reserved_11_15                 :  5; /* [15:11],      rsvd,       0x0 */
            uint32_t s_img_width                    : 11; /* [26:16],       r/w,       0x0 */
            uint32_t reserved_27_31                 :  5; /* [31:27],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } core_reg1;

    /* 0x2c : core_reg2 */
    union {
        struct {
            uint32_t img_height                     : 11; /* [10: 0],       r/w,       0x0 */
            uint32_t reserved_11_15                 :  5; /* [15:11],      rsvd,       0x0 */
            uint32_t s_img_height                   : 11; /* [26:16],       r/w,       0x0 */
            uint32_t reserved_27_31                 :  5; /* [31:27],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } core_reg2;

    /* 0x30 : core_reg3 */
    union {
        struct {
            uint32_t target_i_qp                    :  6; /* [ 5: 0],       r/w,       0x0 */
            uint32_t reserved_6_15                  : 10; /* [15: 6],      rsvd,       0x0 */
            uint32_t s_target_i_qp                  :  6; /* [21:16],       r/w,       0x0 */
            uint32_t reserved_22_31                 : 10; /* [31:22],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } core_reg3;

    /* 0x34 : core_reg4 */
    union {
        struct {
            uint32_t cqp_offset                     :  5; /* [ 4: 0],       r/w,       0x0 */
            uint32_t reserved_5_15                  : 11; /* [15: 5],      rsvd,       0x0 */
            uint32_t s_cqp_offset                   :  5; /* [20:16],       r/w,       0x0 */
            uint32_t reserved_21_31                 : 11; /* [31:21],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } core_reg4;

    /* 0x38 : core_reg5 */
    union {
        struct {
            uint32_t target_p_qp                    :  6; /* [ 5: 0],       r/w,       0x0 */
            uint32_t reserved_6_15                  : 10; /* [15: 6],      rsvd,       0x0 */
            uint32_t s_target_p_qp                  :  6; /* [21:16],       r/w,       0x0 */
            uint32_t reserved_22_31                 : 10; /* [31:22],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } core_reg5;

    /* 0x3c : core_reg6 */
    union {
        struct {
            uint32_t mb_lines                       :  7; /* [ 6: 0],       r/w,       0x0 */
            uint32_t reserved_7_15                  :  9; /* [15: 7],      rsvd,       0x0 */
            uint32_t s_mb_lines                     :  7; /* [22:16],       r/w,       0x0 */
            uint32_t reserved_23_31                 :  9; /* [31:23],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } core_reg6;

    /* 0x40 : core_reg7 */
    union {
        struct {
            uint32_t num_slices                     :  4; /* [ 3: 0],       r/w,       0x0 */
            uint32_t reserved_4_15                  : 12; /* [15: 4],      rsvd,       0x0 */
            uint32_t s_num_slices                   :  4; /* [19:16],       r/w,       0x0 */
            uint32_t reserved_20_31                 : 12; /* [31:20],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } core_reg7;

    /* 0x44 : core_reg8 */
    union {
        struct {
            uint32_t num_pframes                    : 10; /* [ 9: 0],       r/w,       0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],      rsvd,       0x0 */
            uint32_t s_num_pframes                  : 10; /* [25:16],       r/w,       0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } core_reg8;

    /* 0x48 : core_reg9 */
    union {
        struct {
            uint32_t dis_filter                     :  1; /* [    0],       r/w,       0x0 */
            uint32_t reserved_1_15                  : 15; /* [15: 1],      rsvd,       0x0 */
            uint32_t s_dis_filter                   :  1; /* [   16],       r/w,       0x0 */
            uint32_t reserved_17_31                 : 15; /* [31:17],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } core_reg9;

    /* 0x4c : core_reg10 */
    union {
        struct {
            uint32_t alpha_off                      :  4; /* [ 3: 0],       r/w,       0x0 */
            uint32_t reserved_4_15                  : 12; /* [15: 4],      rsvd,       0x0 */
            uint32_t s_alpha_off                    :  4; /* [19:16],       r/w,       0x0 */
            uint32_t reserved_20_31                 : 12; /* [31:20],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } core_reg10;

    /* 0x50 : core_reg11 */
    union {
        struct {
            uint32_t beta_off                       :  4; /* [ 3: 0],       r/w,       0x0 */
            uint32_t reserved_4_15                  : 12; /* [15: 4],      rsvd,       0x0 */
            uint32_t s_beta_off                     :  4; /* [19:16],       r/w,       0x0 */
            uint32_t reserved_20_31                 : 12; /* [31:20],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } core_reg11;

    /* 0x54 : core_reg12 */
    union {
        struct {
            uint32_t profile_idc                    :  1; /* [    0],       r/w,       0x0 */
            uint32_t reserved_1_15                  : 15; /* [15: 1],      rsvd,       0x0 */
            uint32_t s_profile_idc                  :  1; /* [   16],       r/w,       0x0 */
            uint32_t reserved_17_31                 : 15; /* [31:17],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } core_reg12;

    /* 0x58 : core_reg13 */
    union {
        struct {
            uint32_t level_idc                      :  8; /* [ 7: 0],       r/w,       0x0 */
            uint32_t reserved_8_15                  :  8; /* [15: 8],      rsvd,       0x0 */
            uint32_t s_level_idc                    :  8; /* [23:16],       r/w,       0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } core_reg13;

    /* 0x5c : core_reg14 */
    union {
        struct {
            uint32_t luma8x8_cost                   :  3; /* [ 2: 0],       r/w,       0x0 */
            uint32_t luma16x16_cost                 :  3; /* [ 5: 3],       r/w,       0x0 */
            uint32_t chroma8x8_cost                 :  3; /* [ 8: 6],       r/w,       0x0 */
            uint32_t reserved_9_15                  :  7; /* [15: 9],      rsvd,       0x0 */
            uint32_t s_luma8x8_cost                 :  3; /* [18:16],       r/w,       0x0 */
            uint32_t s_luma16x16_cost               :  3; /* [21:19],       r/w,       0x0 */
            uint32_t s_chroma8x8_cost               :  3; /* [24:22],       r/w,       0x0 */
            uint32_t reserved_25_31                 :  7; /* [31:25],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } core_reg14;

    /* 0x60 : reserved */
    uint8_t reserved96[4];

    /* 0x64 : core_reg16 */
    union {
        struct {
            uint32_t frame0                         : 14; /* [13: 0],       r/w,       0x0 */
            uint32_t reserved_14_15                 :  2; /* [15:14],      rsvd,       0x0 */
            uint32_t s_frame0                       : 14; /* [29:16],       r/w,       0x0 */
            uint32_t reserved_30_31                 :  2; /* [31:30],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } core_reg16;

    /* 0x68 : core_reg17 */
    union {
        struct {
            uint32_t frame1                         : 14; /* [13: 0],       r/w,       0x0 */
            uint32_t reserved_14_15                 :  2; /* [15:14],      rsvd,       0x0 */
            uint32_t s_frame1                       : 14; /* [29:16],       r/w,       0x0 */
            uint32_t reserved_30_31                 :  2; /* [31:30],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } core_reg17;

    /* 0x6c : core_reg18 */
    union {
        struct {
            uint32_t ext_data                       : 14; /* [13: 0],       r/w,       0x0 */
            uint32_t reserved_14_15                 :  2; /* [15:14],      rsvd,       0x0 */
            uint32_t s_ext_data                     : 14; /* [29:16],       r/w,       0x0 */
            uint32_t reserved_30_31                 :  2; /* [31:30],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } core_reg18;

    /* 0x70 : core_reg19 */
    union {
        struct {
            uint32_t ext_mem_config0                :  6; /* [ 5: 0],       r/w,       0x0 */
            uint32_t reserved_6_15                  : 10; /* [15: 6],      rsvd,       0x0 */
            uint32_t s_ext_mem_config0              :  6; /* [21:16],       r/w,       0x0 */
            uint32_t reserved_22_31                 : 10; /* [31:22],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } core_reg19;

    /* 0x74 : core_reg20 */
    union {
        struct {
            uint32_t ext_mem_config1                :  5; /* [ 4: 0],       r/w,       0x0 */
            uint32_t reserved_5_15                  : 11; /* [15: 5],      rsvd,       0x0 */
            uint32_t s_ext_mem_config1              :  5; /* [20:16],       r/w,       0x0 */
            uint32_t reserved_21_31                 : 11; /* [31:21],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } core_reg20;

    /* 0x78 : core_reg21 */
    union {
        struct {
            uint32_t ext_mem_config2                : 12; /* [11: 0],       r/w,       0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],      rsvd,       0x0 */
            uint32_t s_ext_mem_config2              : 12; /* [27:16],       r/w,       0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } core_reg21;

    /* 0x7c : core_reg22 */
    union {
        struct {
            uint32_t ext_mem_config3                : 10; /* [ 9: 0],       r/w,       0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],      rsvd,       0x0 */
            uint32_t s_ext_mem_config3              : 10; /* [25:16],       r/w,       0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } core_reg22;

    /* 0x80 : core_reg23 */
    union {
        struct {
            uint32_t num_imb_bits                   : 12; /* [11: 0],       r/w,       0x0 */
            uint32_t reserved_12                    :  1; /* [   12],      rsvd,       0x0 */
            uint32_t nal_align                      :  1; /* [   13],       r/w,       0x0 */
            uint32_t cons_ipred                     :  1; /* [   14],       r/w,       0x0 */
            uint32_t reserved_15                    :  1; /* [   15],      rsvd,       0x0 */
            uint32_t s_num_imb_bits                 : 12; /* [27:16],       r/w,       0x0 */
            uint32_t reserved_28                    :  1; /* [   28],      rsvd,       0x0 */
            uint32_t s_nal_align                    :  1; /* [   29],       r/w,       0x0 */
            uint32_t s_cons_ipred                   :  1; /* [   30],       r/w,       0x0 */
            uint32_t reserved_31                    :  1; /* [   31],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } core_reg23;

    /* 0x84 : core_reg24 */
    union {
        struct {
            uint32_t num_pmb_bits                   : 12; /* [11: 0],       r/w,       0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],      rsvd,       0x0 */
            uint32_t s_num_pmb_bits                 : 12; /* [27:16],       r/w,       0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } core_reg24;

    /* 0x88 : core_reg25 */
    union {
        struct {
            uint32_t interlace_mode                 :  1; /* [    0],       r/w,       0x0 */
            uint32_t bottom_field_first             :  1; /* [    1],       r/w,       0x0 */
            uint32_t prev_field_ref                 :  1; /* [    2],       r/w,       0x0 */
            uint32_t reserved_3_15                  : 13; /* [15: 3],      rsvd,       0x0 */
            uint32_t s_interlace_mode               :  1; /* [   16],       r/w,       0x0 */
            uint32_t s_bottom_field_first           :  1; /* [   17],       r/w,       0x0 */
            uint32_t s_prev_field_ref               :  1; /* [   18],       r/w,       0x0 */
            uint32_t reserved_19_31                 : 13; /* [31:19],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } core_reg25;

    /* 0x8c : reserved */
    uint8_t reserved140[8];

    /* 0x94 : core_reg28 */
    union {
        struct {
            uint32_t pframe_min_qp                  :  6; /* [ 5: 0],       r/w,       0x0 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],      rsvd,       0x0 */
            uint32_t pframe_max_qp                  :  6; /* [13: 8],       r/w,      0x33 */
            uint32_t reserved_14_15                 :  2; /* [15:14],      rsvd,       0x0 */
            uint32_t s_pframe_min_qp                :  6; /* [21:16],       r/w,       0x0 */
            uint32_t reserved_22_23                 :  2; /* [23:22],      rsvd,       0x0 */
            uint32_t s_pframe_max_qp                :  6; /* [29:24],       r/w,      0x33 */
            uint32_t reserved_30_31                 :  2; /* [31:30],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } core_reg28;

    /* 0x98 : reserved */
    uint8_t reserved152[4];

    /* 0x9c : core_reg30 */
    union {
        struct {
            uint32_t reserved_0_14                  : 15; /* [14: 0],      rsvd,       0x0 */
            uint32_t reset_i_state                  :  1; /* [   15],       r/w,       0x1 */
            uint32_t reserved_16_30                 : 15; /* [30:16],      rsvd,       0x0 */
            uint32_t s_reset_i_state                :  1; /* [   31],       r/w,       0x1 */
        }BF;
        uint32_t WORD;
    } core_reg30;

    /* 0xa0 : core_reg31 */
    union {
        struct {
            uint32_t iframe_min_qp                  :  6; /* [ 5: 0],       r/w,       0x0 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],      rsvd,       0x0 */
            uint32_t iframe_max_qp                  :  6; /* [13: 8],       r/w,      0x33 */
            uint32_t reserved_14_15                 :  2; /* [15:14],      rsvd,       0x0 */
            uint32_t s_iframe_min_qp                :  6; /* [21:16],       r/w,       0x0 */
            uint32_t reserved_22_23                 :  2; /* [23:22],      rsvd,       0x0 */
            uint32_t s_iframe_max_qp                :  6; /* [29:24],       r/w,      0x33 */
            uint32_t reserved_30_31                 :  2; /* [31:30],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } core_reg31;

    /* 0xa4 : core_reg32 */
    union {
        struct {
            uint32_t vui_time_scale_l               : 16; /* [15: 0],       r/w,       0x0 */
            uint32_t s_vui_time_scale_l             : 16; /* [31:16],       r/w,       0x0 */
        }BF;
        uint32_t WORD;
    } core_reg32;

    /* 0xa8 : core_reg33 */
    union {
        struct {
            uint32_t vui_time_scale_h               : 16; /* [15: 0],       r/w,       0x0 */
            uint32_t s_vui_time_scale_h             : 16; /* [31:16],       r/w,       0x0 */
        }BF;
        uint32_t WORD;
    } core_reg33;

    /* 0xac : core_reg34 */
    union {
        struct {
            uint32_t vui_num_u_tick_l               : 16; /* [15: 0],       r/w,       0x0 */
            uint32_t s_vui_num_u_tick_l             : 16; /* [31:16],       r/w,       0x0 */
        }BF;
        uint32_t WORD;
    } core_reg34;

    /* 0xb0 : core_reg35 */
    union {
        struct {
            uint32_t vui_num_u_tick_h               : 16; /* [15: 0],       r/w,       0x0 */
            uint32_t s_vui_num_u_tick_h             : 16; /* [31:16],       r/w,       0x0 */
        }BF;
        uint32_t WORD;
    } core_reg35;

    /* 0xb4 : core_reg36 */
    union {
        struct {
            uint32_t vui_aspect_idc                 :  8; /* [ 7: 0],       r/w,       0x0 */
            uint32_t reserved_8_15                  :  8; /* [15: 8],      rsvd,       0x0 */
            uint32_t s_vui_aspect_idc               :  8; /* [23:16],       r/w,       0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } core_reg36;

    /* 0xb8 : core_reg37 */
    union {
        struct {
            uint32_t vui_aspect_width               : 16; /* [15: 0],       r/w,       0x0 */
            uint32_t s_vui_aspect_width             : 16; /* [31:16],       r/w,       0x0 */
        }BF;
        uint32_t WORD;
    } core_reg37;

    /* 0xbc : core_reg38 */
    union {
        struct {
            uint32_t vui_aspect_height              : 16; /* [15: 0],       r/w,       0x0 */
            uint32_t s_vui_aspect_height            : 16; /* [31:16],       r/w,       0x0 */
        }BF;
        uint32_t WORD;
    } core_reg38;

    /* 0xc0 : src_dvp_sel */
    union {
        struct {
            uint32_t uv_dvp2axi_sel                 :  3; /* [ 2: 0],       r/w,       0x0 */
            uint32_t reserved_3                     :  1; /* [    3],      rsvd,       0x0 */
            uint32_t y_dvp2axi_sel                  :  3; /* [ 6: 4],       r/w,       0x0 */
            uint32_t reserved_7_15                  :  9; /* [15: 7],      rsvd,       0x0 */
            uint32_t s_uv_dvp2axi_sel               :  3; /* [18:16],       r/w,       0x0 */
            uint32_t reserved_19                    :  1; /* [   19],      rsvd,       0x0 */
            uint32_t s_y_dvp2axi_sel                :  3; /* [22:20],       r/w,       0x0 */
            uint32_t reserved_23_31                 :  9; /* [31:23],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } src_dvp_sel;

    /* 0xc4 : padding_ctrl */
    union {
        struct {
            uint32_t y_padding_pixel                :  8; /* [ 7: 0],       r/w,       0x0 */
            uint32_t u_padding_pixel                :  8; /* [15: 8],       r/w,      0x80 */
            uint32_t v_padding_pixel                :  8; /* [23:16],       r/w,      0x80 */
            uint32_t y_line_pad                     :  5; /* [28:24],       r/w,       0x0 */
            uint32_t reserved_29_31                 :  3; /* [31:29],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } padding_ctrl;

    /* 0xc8 : reserved */
    uint8_t reserved200[16];

    /* 0xd8 : vdo_frame_id_clr */
    union {
        struct {
            uint32_t frame_id_clr                   :  1; /* [    0],       w1p,       0x0 */
            uint32_t s_frame_id_clr                 :  1; /* [    1],       w1p,       0x0 */
            uint32_t reserved_2_31                  : 30; /* [31: 2],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } vdo_frame_id_clr;

    /* 0xdc : reserved */
    uint8_t reserved220[36];

    /* 0x100 : vdo_int */
    union {
        struct {
            uint32_t frm_done_int                   :  1; /* [    0],         r,       0x0 */
            uint32_t s_frm_done_int                 :  1; /* [    1],         r,       0x0 */
            uint32_t reserved_2_3                   :  2; /* [ 3: 2],      rsvd,       0x0 */
            uint32_t seq_done_int                   :  1; /* [    4],         r,       0x0 */
            uint32_t s_seq_done_int                 :  1; /* [    5],         r,       0x0 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],      rsvd,       0x0 */
            uint32_t bs_full_int                    :  1; /* [    8],         r,       0x0 */
            uint32_t s_bs_full_int                  :  1; /* [    9],         r,       0x0 */
            uint32_t reserved_10_31                 : 22; /* [31:10],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } vdo_int;

    /* 0x104 : vdo_int_clr */
    union {
        struct {
            uint32_t frm_done_int_clr               :  1; /* [    0],       w1p,       0x0 */
            uint32_t s_frm_done_int_clr             :  1; /* [    1],       w1p,       0x0 */
            uint32_t reserved_2_3                   :  2; /* [ 3: 2],      rsvd,       0x0 */
            uint32_t seq_done_int_clr               :  1; /* [    4],       w1p,       0x0 */
            uint32_t s_seq_done_int_clr             :  1; /* [    5],       w1p,       0x0 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],      rsvd,       0x0 */
            uint32_t bs_full_int_clr                :  1; /* [    8],       w1p,       0x0 */
            uint32_t s_bs_full_int_clr              :  1; /* [    9],       w1p,       0x0 */
            uint32_t reserved_10_31                 : 22; /* [31:10],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } vdo_int_clr;

    /* 0x108 : vdo_int_mask */
    union {
        struct {
            uint32_t frm_done_int_mask              :  1; /* [    0],       r/w,       0x0 */
            uint32_t s_frm_done_int_mask            :  1; /* [    1],       r/w,       0x0 */
            uint32_t reserved_2_3                   :  2; /* [ 3: 2],      rsvd,       0x0 */
            uint32_t seq_done_int_mask              :  1; /* [    4],       r/w,       0x0 */
            uint32_t s_seq_done_int_mask            :  1; /* [    5],       r/w,       0x0 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],      rsvd,       0x0 */
            uint32_t bs_full_int_mask               :  1; /* [    8],       r/w,       0x0 */
            uint32_t s_bs_full_int_mask             :  1; /* [    9],       r/w,       0x0 */
            uint32_t reserved_10_31                 : 22; /* [31:10],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } vdo_int_mask;

    /* 0x10c : vdo_total_bytecount */
    union {
        struct {
            uint32_t bs_tot_bycnt                   : 32; /* [31: 0],         r,       0x0 */
        }BF;
        uint32_t WORD;
    } vdo_total_bytecount;

    /* 0x110 : vdo_frame_bytecount */
    union {
        struct {
            uint32_t bs_frm_bycnt                   : 32; /* [31: 0],         r,       0x0 */
        }BF;
        uint32_t WORD;
    } vdo_frame_bytecount;

    /* 0x114 : vdo_src_r_dbg */
    union {
        struct {
            uint32_t y_read_mbx                     : 13; /* [12: 0],         r,       0x0 */
            uint32_t reserved_13_15                 :  3; /* [15:13],      rsvd,       0x0 */
            uint32_t uv_read_mbx                    : 13; /* [28:16],         r,       0x0 */
            uint32_t reserved_29                    :  1; /* [   29],      rsvd,       0x0 */
            uint32_t axi_r_idle                     :  1; /* [   30],         r,       0x0 */
            uint32_t src_wr_ov_rd                   :  1; /* [   31],         r,       0x0 */
        }BF;
        uint32_t WORD;
    } vdo_src_r_dbg;

    /* 0x118 : vdo_core_dbg */
    union {
        struct {
            uint32_t core_mbx                       :  7; /* [ 6: 0],         r,       0x0 */
            uint32_t reserved_7                     :  1; /* [    7],      rsvd,       0x0 */
            uint32_t core_mby                       :  7; /* [14: 8],         r,       0x0 */
            uint32_t reserved_15                    :  1; /* [   15],      rsvd,       0x0 */
            uint32_t m_core_idle                    :  1; /* [   16],         r,       0x1 */
            uint32_t s_core_idle                    :  1; /* [   17],         r,       0x1 */
            uint32_t reserved_18_19                 :  2; /* [19:18],      rsvd,       0x0 */
            uint32_t se_fsm                         :  5; /* [24:20],         r,       0x0 */
            uint32_t reserved_25_28                 :  4; /* [28:25],      rsvd,       0x0 */
            uint32_t oclk_en                        :  1; /* [   29],         r,       0x0 */
            uint32_t timeout_state                  :  1; /* [   30],         r,       0x0 */
            uint32_t mem_ctrl_idle                  :  1; /* [   31],         r,       0x1 */
        }BF;
        uint32_t WORD;
    } vdo_core_dbg;

    /* 0x11c : vdo_ctrl_dbg */
    union {
        struct {
            uint32_t ctrl_state                     :  3; /* [ 2: 0],         r,       0x0 */
            uint32_t h264_proc                      :  1; /* [    3],         r,       0x0 */
            uint32_t s_ctrl_state                   :  3; /* [ 6: 4],         r,       0x0 */
            uint32_t s_h264_proc                    :  1; /* [    7],         r,       0x0 */
            uint32_t ctrl_ce                        :  1; /* [    8],         r,       0x0 */
            uint32_t reserved_9_11                  :  3; /* [11: 9],      rsvd,       0x0 */
            uint32_t stream_idx                     :  1; /* [   12],         r,       0x0 */
            uint32_t reserved_13_15                 :  3; /* [15:13],      rsvd,       0x0 */
            uint32_t ctrler_frm_cnt                 :  8; /* [23:16],         r,       0x0 */
            uint32_t s_ctrler_frm_cnt               :  8; /* [31:24],         r,       0x0 */
        }BF;
        uint32_t WORD;
    } vdo_ctrl_dbg;

    /* 0x120 : vdo_checksum_0 */
    union {
        struct {
            uint32_t vdo0_axi_rdata_chksum          : 32; /* [31: 0],         r,       0x0 */
        }BF;
        uint32_t WORD;
    } vdo_checksum_0;

    /* 0x124 : vdo_checksum_1 */
    union {
        struct {
            uint32_t vdo0_axi_wdata_chksum          : 32; /* [31: 0],         r,       0x0 */
        }BF;
        uint32_t WORD;
    } vdo_checksum_1;

    /* 0x128 : vdo_checksum_2 */
    union {
        struct {
            uint32_t vdo1_axi_rdata_chksum          : 32; /* [31: 0],         r,       0x0 */
        }BF;
        uint32_t WORD;
    } vdo_checksum_2;

    /* 0x12c : vdo_checksum_3 */
    union {
        struct {
            uint32_t vdo1_axi_wdata_chksum          : 32; /* [31: 0],         r,       0x0 */
        }BF;
        uint32_t WORD;
    } vdo_checksum_3;

    /* 0x130 : vdo_checksum_4 */
    union {
        struct {
            uint32_t ld_yblk_chksum                 : 32; /* [31: 0],         r,       0x0 */
        }BF;
        uint32_t WORD;
    } vdo_checksum_4;

    /* 0x134 : vdo_checksum_5 */
    union {
        struct {
            uint32_t ld_cblk_chksum                 : 32; /* [31: 0],         r,       0x0 */
        }BF;
        uint32_t WORD;
    } vdo_checksum_5;

    /* 0x138 : vdo_checksum_6 */
    union {
        struct {
            uint32_t mem_din_chksum                 : 32; /* [31: 0],         r,       0x0 */
        }BF;
        uint32_t WORD;
    } vdo_checksum_6;

    /* 0x13c : vdo_checksum_7 */
    union {
        struct {
            uint32_t mem_dout_chksum                : 32; /* [31: 0],         r,       0x0 */
        }BF;
        uint32_t WORD;
    } vdo_checksum_7;

    /* 0x140 : vdo_reserved */
    union {
        struct {
            uint32_t vdo_reserved                   : 32; /* [31: 0],       r/w,       0x0 */
        }BF;
        uint32_t WORD;
    } vdo_reserved;

    /* 0x144 : h264_y_frame_mem_size */
    union {
        struct {
            uint32_t cfg_mem_bcnt_y                 : 32; /* [31: 0],       r/w,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_y_frame_mem_size;

    /* 0x148 : h264_uv_frame_mem_size */
    union {
        struct {
            uint32_t cfg_mem_bcnt_uv                : 32; /* [31: 0],       r/w,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_uv_frame_mem_size;

    /* 0x14c : h264_s_frame_size */
    union {
        struct {
            uint32_t cfg_s_frame_width              : 11; /* [10: 0],       r/w,       0x0 */
            uint32_t reserved_11_15                 :  5; /* [15:11],      rsvd,       0x0 */
            uint32_t cfg_s_frame_height             : 11; /* [26:16],       r/w,       0x0 */
            uint32_t reserved_27_31                 :  5; /* [31:27],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_s_frame_size;

    /* 0x150 : h264_s_frame_base_addr_y */
    union {
        struct {
            uint32_t cfg_s_frame_base_addr_y        : 32; /* [31: 0],       r/w,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_s_frame_base_addr_y;

    /* 0x154 : h264_s_frame_base_addr_uv */
    union {
        struct {
            uint32_t cfg_s_frame_base_addr_uv       : 32; /* [31: 0],       r/w,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_s_frame_base_addr_uv;

    /* 0x158 : h264_s_y_frame_mem_size */
    union {
        struct {
            uint32_t cfg_s_mem_bcnt_y               : 32; /* [31: 0],       r/w,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_s_y_frame_mem_size;

    /* 0x15c : h264_s_uv_frame_mem_size */
    union {
        struct {
            uint32_t cfg_s_mem_bcnt_uv              : 32; /* [31: 0],       r/w,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_s_uv_frame_mem_size;

    /* 0x160 : h264_s_bs_base_addr */
    union {
        struct {
            uint32_t cfg_s_bs_base_addr             : 32; /* [31: 0],       r/w,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_s_bs_base_addr;

    /* 0x164 : vdo_reserved2 */
    union {
        struct {
            uint32_t vdo_reserved2                  : 32; /* [31: 0],       r/w,       0x0 */
        }BF;
        uint32_t WORD;
    } vdo_reserved2;

    /* 0x168 : h264_s_bs_size */
    union {
        struct {
            uint32_t cfg_s_bs_size                  : 32; /* [31: 0],       r/w,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_s_bs_size;

    /* 0x16c : h264_s_bs_full_thr */
    union {
        struct {
            uint32_t cfg_s_bs_full_thr              : 32; /* [31: 0],       r/w,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_s_bs_full_thr;

    /* 0x170 : h264_s_src_bf_height */
    union {
        struct {
            uint32_t cfg_s_c_src_bf_height          : 15; /* [14: 0],       r/w,       0x0 */
            uint32_t reserved_15                    :  1; /* [   15],      rsvd,       0x0 */
            uint32_t cfg_s_y_src_bf_height          : 15; /* [30:16],       r/w,       0x0 */
            uint32_t reserved_31                    :  1; /* [   31],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_s_src_bf_height;

    /* 0x174 : s_padding_ctrl */
    union {
        struct {
            uint32_t s_y_padding_pixel              :  8; /* [ 7: 0],       r/w,       0x0 */
            uint32_t s_u_padding_pixel              :  8; /* [15: 8],       r/w,      0x80 */
            uint32_t s_v_padding_pixel              :  8; /* [23:16],       r/w,      0x80 */
            uint32_t s_y_line_pad                   :  5; /* [28:24],       r/w,       0x0 */
            uint32_t reserved_29_31                 :  3; /* [31:29],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } s_padding_ctrl;

    /* 0x178 : vdo_s_total_bytecount */
    union {
        struct {
            uint32_t s_bs_tot_bycnt                 : 32; /* [31: 0],         r,       0x0 */
        }BF;
        uint32_t WORD;
    } vdo_s_total_bytecount;

    /* 0x17c : vdo_s_frame_bytecount */
    union {
        struct {
            uint32_t s_bs_frm_bycnt                 : 32; /* [31: 0],         r,       0x0 */
        }BF;
        uint32_t WORD;
    } vdo_s_frame_bytecount;

    /* 0x180 : vdo_s_src_r_dbg */
    union {
        struct {
            uint32_t s_y_read_mbx                   : 13; /* [12: 0],         r,       0x0 */
            uint32_t reserved_13_15                 :  3; /* [15:13],      rsvd,       0x0 */
            uint32_t s_uv_read_mbx                  : 13; /* [28:16],         r,       0x0 */
            uint32_t reserved_29                    :  1; /* [   29],      rsvd,       0x0 */
            uint32_t s_axi_r_idle                   :  1; /* [   30],         r,       0x0 */
            uint32_t s_src_wr_ov_rd                 :  1; /* [   31],         r,       0x0 */
        }BF;
        uint32_t WORD;
    } vdo_s_src_r_dbg;

    /* 0x184 : vdo_src_sta_clr */
    union {
        struct {
            uint32_t src_uv_wovr_clr                :  1; /* [    0],       w1p,       0x0 */
            uint32_t reserved_1_3                   :  3; /* [ 3: 1],      rsvd,       0x0 */
            uint32_t src_y_wovr_clr                 :  1; /* [    4],       w1p,       0x0 */
            uint32_t reserved_5_7                   :  3; /* [ 7: 5],      rsvd,       0x0 */
            uint32_t s_src_uv_wovr_clr              :  1; /* [    8],       w1p,       0x0 */
            uint32_t reserved_9_11                  :  3; /* [11: 9],      rsvd,       0x0 */
            uint32_t s_src_y_wovr_clr               :  1; /* [   12],       w1p,       0x0 */
            uint32_t reserved_13_31                 : 19; /* [31:13],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } vdo_src_sta_clr;

    /* 0x188 : vdo_src_ctrl */
    union {
        struct {
            uint32_t frm_buf_num                    :  4; /* [ 3: 0],       r/w,       0x0 */
            uint32_t mfrm_buf_en                    :  1; /* [    4],       r/w,       0x0 */
            uint32_t req_period                     : 10; /* [14: 5],       r/w,       0x0 */
            uint32_t no_wait_1st_vsync              :  1; /* [   15],       r/w,       0x0 */
            uint32_t s_frm_buf_num                  :  4; /* [19:16],       r/w,       0x0 */
            uint32_t s_mfrm_buf_en                  :  1; /* [   20],       r/w,       0x0 */
            uint32_t s_req_period                   : 10; /* [30:21],       r/w,       0x0 */
            uint32_t s_no_wait_1st_vsync            :  1; /* [   31],       r/w,       0x0 */
        }BF;
        uint32_t WORD;
    } vdo_src_ctrl;

    /* 0x18c : h264_refy0_base_addr */
    union {
        struct {
            uint32_t cfg_refy0_base_addr            : 32; /* [31: 0],       r/w,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_refy0_base_addr;

    /* 0x190 : h264_refu0_base_addr */
    union {
        struct {
            uint32_t cfg_refu0_base_addr            : 32; /* [31: 0],       r/w,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_refu0_base_addr;

    /* 0x194 : h264_refv0_base_addr */
    union {
        struct {
            uint32_t cfg_refv0_base_addr            : 32; /* [31: 0],       r/w,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_refv0_base_addr;

    /* 0x198 : h264_refy1_base_addr */
    union {
        struct {
            uint32_t cfg_refy1_base_addr            : 32; /* [31: 0],       r/w,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_refy1_base_addr;

    /* 0x19c : h264_refu1_base_addr */
    union {
        struct {
            uint32_t cfg_refu1_base_addr            : 32; /* [31: 0],       r/w,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_refu1_base_addr;

    /* 0x1a0 : h264_refv1_base_addr */
    union {
        struct {
            uint32_t cfg_refv1_base_addr            : 32; /* [31: 0],       r/w,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_refv1_base_addr;

    /* 0x1a4 : h264_ext_base_addr */
    union {
        struct {
            uint32_t cfg_ext_base_addr              : 32; /* [31: 0],       r/w,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_ext_base_addr;

    /* 0x1a8 : h264_s_refy0_base_addr */
    union {
        struct {
            uint32_t cfg_s_refy0_base_addr          : 32; /* [31: 0],       r/w,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_s_refy0_base_addr;

    /* 0x1ac : h264_s_refu0_base_addr */
    union {
        struct {
            uint32_t cfg_s_refu0_base_addr          : 32; /* [31: 0],       r/w,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_s_refu0_base_addr;

    /* 0x1b0 : h264_s_refv0_base_addr */
    union {
        struct {
            uint32_t cfg_s_refv0_base_addr          : 32; /* [31: 0],       r/w,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_s_refv0_base_addr;

    /* 0x1b4 : h264_s_refy1_base_addr */
    union {
        struct {
            uint32_t cfg_s_refy1_base_addr          : 32; /* [31: 0],       r/w,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_s_refy1_base_addr;

    /* 0x1b8 : h264_s_refu1_base_addr */
    union {
        struct {
            uint32_t cfg_s_refu1_base_addr          : 32; /* [31: 0],       r/w,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_s_refu1_base_addr;

    /* 0x1bc : h264_s_refv1_base_addr */
    union {
        struct {
            uint32_t cfg_s_refv1_base_addr          : 32; /* [31: 0],       r/w,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_s_refv1_base_addr;

    /* 0x1c0 : h264_s_ext_base_addr */
    union {
        struct {
            uint32_t cfg_s_ext_base_addr            : 32; /* [31: 0],       r/w,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_s_ext_base_addr;

    /* 0x1c4 : vdo_core_dbg2 */
    union {
        struct {
            uint32_t pframe                         :  1; /* [    0],         r,       0x0 */
            uint32_t reserved_1_3                   :  3; /* [ 3: 1],      rsvd,       0x0 */
            uint32_t pframe_cnt                     : 10; /* [13: 4],         r,       0x0 */
            uint32_t reserved_14_15                 :  2; /* [15:14],      rsvd,       0x0 */
            uint32_t tclock                         : 10; /* [25:16],         r,       0x0 */
            uint32_t r_yref_wait                    :  1; /* [   26],         r,       0x0 */
            uint32_t r_vref_wait                    :  1; /* [   27],         r,       0x0 */
            uint32_t w_yrec_wait                    :  1; /* [   28],         r,       0x0 */
            uint32_t pfch_vbuf_wait                 :  1; /* [   29],         r,       0x0 */
            uint32_t cabac_wait                     :  1; /* [   30],         r,       0x0 */
            uint32_t enc_busy                       :  1; /* [   31],         r,       0x0 */
        }BF;
        uint32_t WORD;
    } vdo_core_dbg2;

    /* 0x1c8 : vdo_s_core_dbg2 */
    union {
        struct {
            uint32_t s_pframe                       :  1; /* [    0],         r,       0x0 */
            uint32_t reserved_1_3                   :  3; /* [ 3: 1],      rsvd,       0x0 */
            uint32_t s_pframe_cnt                   : 10; /* [13: 4],         r,       0x0 */
            uint32_t reserved_14_15                 :  2; /* [15:14],      rsvd,       0x0 */
            uint32_t s_tclock                       : 10; /* [25:16],         r,       0x0 */
            uint32_t s_r_yref_wait                  :  1; /* [   26],         r,       0x0 */
            uint32_t s_r_vref_wait                  :  1; /* [   27],         r,       0x0 */
            uint32_t s_w_yrec_wait                  :  1; /* [   28],         r,       0x0 */
            uint32_t s_pfch_vbuf_wait               :  1; /* [   29],         r,       0x0 */
            uint32_t s_cabac_wait                   :  1; /* [   30],         r,       0x0 */
            uint32_t s_enc_busy                     :  1; /* [   31],         r,       0x0 */
        }BF;
        uint32_t WORD;
    } vdo_s_core_dbg2;

    /* 0x1cc : h264_y_srcbf_size */
    union {
        struct {
            uint32_t cfg_y_srcbf_bycnt              : 32; /* [31: 0],       r/w,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_y_srcbf_size;

    /* 0x1d0 : h264_uv_srcbf_size */
    union {
        struct {
            uint32_t cfg_uv_srcbf_bycnt             : 32; /* [31: 0],       r/w,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_uv_srcbf_size;

    /* 0x1d4 : h264_s_y_srcbf_size */
    union {
        struct {
            uint32_t cfg_s_y_srcbf_bycnt            : 32; /* [31: 0],       r/w,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_s_y_srcbf_size;

    /* 0x1d8 : h264_s_uv_srcbf_size */
    union {
        struct {
            uint32_t cfg_s_uv_srcbf_bycnt           : 32; /* [31: 0],       r/w,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_s_uv_srcbf_size;

    /* 0x1dc : h264_src_dbg */
    union {
        struct {
            uint32_t d2b_sync_en                    :  1; /* [    0],       r/w,       0x0 */
            uint32_t reserved_1_3                   :  3; /* [ 3: 1],      rsvd,       0x0 */
            uint32_t old_read_mode                  :  5; /* [ 8: 4],       r/w,       0x0 */
            uint32_t reserved_9_15                  :  7; /* [15: 9],      rsvd,       0x0 */
            uint32_t s_d2b_sync_en                  :  1; /* [   16],       r/w,       0x0 */
            uint32_t reserved_17_19                 :  3; /* [19:17],      rsvd,       0x0 */
            uint32_t s_old_read_mode                :  5; /* [24:20],       r/w,       0x0 */
            uint32_t reserved_25_31                 :  7; /* [31:25],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_src_dbg;

    /* 0x1e0 : h264_yy_d2b_addr */
    union {
        struct {
            uint32_t yy_d2b_addr_dbg                : 32; /* [31: 0],         r,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_yy_d2b_addr;

    /* 0x1e4 : h264_uv_d2b_addr */
    union {
        struct {
            uint32_t uv_d2b_addr_dbg                : 32; /* [31: 0],         r,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_uv_d2b_addr;

    /* 0x1e8 : h264_yy_ofst_addr */
    union {
        struct {
            uint32_t yy_mfrm_ofst_dbg               : 32; /* [31: 0],         r,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_yy_ofst_addr;

    /* 0x1ec : h264_uv_ofst_addr */
    union {
        struct {
            uint32_t uv_mfrm_ofst_dbg               : 32; /* [31: 0],         r,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_uv_ofst_addr;

    /* 0x1f0 : h264_d2b_ml */
    union {
        struct {
            uint32_t yy_d2b_ml_dbg                  : 16; /* [15: 0],         r,       0x0 */
            uint32_t uv_d2b_ml_dbg                  : 16; /* [31:16],         r,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_d2b_ml;

    /* 0x1f4 : h264_load_mbidx_dbg */
    union {
        struct {
            uint32_t load_mbidx_dbg                 : 32; /* [31: 0],         r,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_load_mbidx_dbg;

    /* 0x1f8 : h264_yc_mb_err */
    union {
        struct {
            uint32_t yc_mb_err                      :  3; /* [ 2: 0],         r,       0x0 */
            uint32_t reserved_3_31                  : 29; /* [31: 3],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_yc_mb_err;

    /* 0x1fc : h264_s_yy_d2b_addr */
    union {
        struct {
            uint32_t s_yy_d2b_addr_dbg              : 32; /* [31: 0],         r,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_s_yy_d2b_addr;

    /* 0x200 : h264_s_uv_d2b_addr */
    union {
        struct {
            uint32_t s_uv_d2b_addr_dbg              : 32; /* [31: 0],         r,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_s_uv_d2b_addr;

    /* 0x204 : h264_s_yy_ofst_addr */
    union {
        struct {
            uint32_t s_yy_mfrm_ofst_dbg             : 32; /* [31: 0],         r,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_s_yy_ofst_addr;

    /* 0x208 : h264_s_uv_ofst_addr */
    union {
        struct {
            uint32_t s_uv_mfrm_ofst_dbg             : 32; /* [31: 0],         r,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_s_uv_ofst_addr;

    /* 0x20c : h264_s_d2b_ml */
    union {
        struct {
            uint32_t s_yy_d2b_ml_dbg                : 16; /* [15: 0],         r,       0x0 */
            uint32_t s_uv_d2b_ml_dbg                : 16; /* [31:16],         r,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_s_d2b_ml;

    /* 0x210 : h264_s_load_mbidx_dbg */
    union {
        struct {
            uint32_t s_load_mbidx_dbg               : 32; /* [31: 0],         r,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_s_load_mbidx_dbg;

    /* 0x214 : h264_s_yc_mb_err */
    union {
        struct {
            uint32_t s_yc_mb_err                    :  3; /* [ 2: 0],         r,       0x0 */
            uint32_t reserved_3_31                  : 29; /* [31: 3],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_s_yc_mb_err;

    /* 0x218 : reserved */
    uint8_t reserved536[16];

    /* 0x228 : h264_pfch_ctrl */
    union {
        struct {
            uint32_t cfg_pfch_mbx_s                 :  7; /* [ 6: 0],       r/w,       0x0 */
            uint32_t reserved_7                     :  1; /* [    7],      rsvd,       0x0 */
            uint32_t cfg_pfch_mby_s                 :  7; /* [14: 8],       r/w,       0x0 */
            uint32_t reserved_15                    :  1; /* [   15],      rsvd,       0x0 */
            uint32_t cfg_pfch_en                    :  1; /* [   16],       r/w,       0x0 */
            uint32_t reserved_17_31                 : 15; /* [31:17],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_pfch_ctrl;

    /* 0x22c : h264_pfch_base */
    union {
        struct {
            uint32_t cfg_pfch_base_addr             : 32; /* [31: 0],       r/w,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_pfch_base;

    /* 0x230 : h264_pfchv_base */
    union {
        struct {
            uint32_t cfg_pfchv_base_addr            : 32; /* [31: 0],       r/w,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_pfchv_base;

    /* 0x234 : h264_s_pfch_ctrl */
    union {
        struct {
            uint32_t cfg_s_pfch_mbx_s               :  7; /* [ 6: 0],       r/w,       0x0 */
            uint32_t reserved_7                     :  1; /* [    7],      rsvd,       0x0 */
            uint32_t cfg_s_pfch_mby_s               :  7; /* [14: 8],       r/w,       0x0 */
            uint32_t reserved_15                    :  1; /* [   15],      rsvd,       0x0 */
            uint32_t cfg_s_pfch_en                  :  1; /* [   16],       r/w,       0x0 */
            uint32_t reserved_17_31                 : 15; /* [31:17],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_s_pfch_ctrl;

    /* 0x238 : h264_s_pfch_base */
    union {
        struct {
            uint32_t cfg_s_pfch_base_addr           : 32; /* [31: 0],       r/w,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_s_pfch_base;

    /* 0x23c : h264_s_pfchv_base */
    union {
        struct {
            uint32_t cfg_s_pfchv_base_addr          : 32; /* [31: 0],       r/w,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_s_pfchv_base;

    /* 0x240 : h264_hwback_mode */
    union {
        struct {
            uint32_t cfg_sramck_mode                :  1; /* [    0],       r/w,       0x0 */
            uint32_t cfg_nal_mp_mode                :  1; /* [    1],       r/w,       0x0 */
            uint32_t cfg_s_nal_mp_mode              :  1; /* [    2],       r/w,       0x0 */
            uint32_t reserved_3_31                  : 29; /* [31: 3],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_hwback_mode;

    /* 0x244 : h264_roi_mode */
    union {
        struct {
            uint32_t cfg_roi_en                     :  8; /* [ 7: 0],       r/w,       0x0 */
            uint32_t cfg_roi_upd                    :  1; /* [    8],       w1p,       0x0 */
            uint32_t reserved_9_31                  : 23; /* [31: 9],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_roi_mode;

    /* 0x248 : h264_roi_bit */
    union {
        struct {
            uint32_t cfg_pbit_ratio                 : 13; /* [12: 0],       r/w,     0x400 */
            uint32_t cfg_ibit_ratio                 : 13; /* [25:13],       r/w,     0x400 */
            uint32_t cfg_ithre                      :  6; /* [31:26],       r/w,      0x20 */
        }BF;
        uint32_t WORD;
    } h264_roi_bit;

    /* 0x24c : h264_roi_qptune */
    union {
        struct {
            uint32_t cfg_pqp_decr                   :  6; /* [ 5: 0],       r/w,       0x0 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],      rsvd,       0x0 */
            uint32_t cfg_iqp_decr                   :  6; /* [13: 8],       r/w,       0x0 */
            uint32_t reserved_14_15                 :  2; /* [15:14],      rsvd,       0x0 */
            uint32_t cfg_n2r_qp_decr                :  6; /* [21:16],       r/w,       0x0 */
            uint32_t reserved_22_23                 :  2; /* [23:22],      rsvd,       0x0 */
            uint32_t cfg_fixqp                      :  6; /* [29:24],       r/w,       0x0 */
            uint32_t reserved_30_31                 :  2; /* [31:30],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_roi_qptune;

    /* 0x250 : h264_roi_bittune */
    union {
        struct {
            uint32_t cfg_roi_pbit_ofst              :  5; /* [ 4: 0],       r/w,       0x0 */
            uint32_t reserved_5_7                   :  3; /* [ 7: 5],      rsvd,       0x0 */
            uint32_t cfg_roi_ibit_ofst              :  8; /* [15: 8],       r/w,       0x0 */
            uint32_t cfg_nroi_pbit_ofst             :  5; /* [20:16],       r/w,       0x0 */
            uint32_t reserved_21_23                 :  3; /* [23:21],      rsvd,       0x0 */
            uint32_t cfg_nroi_ibit_ofst             :  8; /* [31:24],       r/w,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_roi_bittune;

    /* 0x254 : h264_roi0 */
    union {
        struct {
            uint32_t cfg_roi0_mbx_s                 :  7; /* [ 6: 0],       r/w,       0x0 */
            uint32_t reserved_7                     :  1; /* [    7],      rsvd,       0x0 */
            uint32_t cfg_roi0_mbx_e                 :  7; /* [14: 8],       r/w,       0x0 */
            uint32_t reserved_15                    :  1; /* [   15],      rsvd,       0x0 */
            uint32_t cfg_roi0_mby_s                 :  7; /* [22:16],       r/w,       0x0 */
            uint32_t reserved_23                    :  1; /* [   23],      rsvd,       0x0 */
            uint32_t cfg_roi0_mby_e                 :  7; /* [30:24],       r/w,       0x0 */
            uint32_t reserved_31                    :  1; /* [   31],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_roi0;

    /* 0x258 : h264_roi1 */
    union {
        struct {
            uint32_t cfg_roi1_mbx_s                 :  7; /* [ 6: 0],       r/w,       0x0 */
            uint32_t reserved_7                     :  1; /* [    7],      rsvd,       0x0 */
            uint32_t cfg_roi1_mbx_e                 :  7; /* [14: 8],       r/w,       0x0 */
            uint32_t reserved_15                    :  1; /* [   15],      rsvd,       0x0 */
            uint32_t cfg_roi1_mby_s                 :  7; /* [22:16],       r/w,       0x0 */
            uint32_t reserved_23                    :  1; /* [   23],      rsvd,       0x0 */
            uint32_t cfg_roi1_mby_e                 :  7; /* [30:24],       r/w,       0x0 */
            uint32_t reserved_31                    :  1; /* [   31],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_roi1;

    /* 0x25c : h264_roi2 */
    union {
        struct {
            uint32_t cfg_roi2_mbx_s                 :  7; /* [ 6: 0],       r/w,       0x0 */
            uint32_t reserved_7                     :  1; /* [    7],      rsvd,       0x0 */
            uint32_t cfg_roi2_mbx_e                 :  7; /* [14: 8],       r/w,       0x0 */
            uint32_t reserved_15                    :  1; /* [   15],      rsvd,       0x0 */
            uint32_t cfg_roi2_mby_s                 :  7; /* [22:16],       r/w,       0x0 */
            uint32_t reserved_23                    :  1; /* [   23],      rsvd,       0x0 */
            uint32_t cfg_roi2_mby_e                 :  7; /* [30:24],       r/w,       0x0 */
            uint32_t reserved_31                    :  1; /* [   31],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_roi2;

    /* 0x260 : h264_roi3 */
    union {
        struct {
            uint32_t cfg_roi3_mbx_s                 :  7; /* [ 6: 0],       r/w,       0x0 */
            uint32_t reserved_7                     :  1; /* [    7],      rsvd,       0x0 */
            uint32_t cfg_roi3_mbx_e                 :  7; /* [14: 8],       r/w,       0x0 */
            uint32_t reserved_15                    :  1; /* [   15],      rsvd,       0x0 */
            uint32_t cfg_roi3_mby_s                 :  7; /* [22:16],       r/w,       0x0 */
            uint32_t reserved_23                    :  1; /* [   23],      rsvd,       0x0 */
            uint32_t cfg_roi3_mby_e                 :  7; /* [30:24],       r/w,       0x0 */
            uint32_t reserved_31                    :  1; /* [   31],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_roi3;

    /* 0x264 : h264_roi4 */
    union {
        struct {
            uint32_t cfg_roi4_mbx_s                 :  7; /* [ 6: 0],       r/w,       0x0 */
            uint32_t reserved_7                     :  1; /* [    7],      rsvd,       0x0 */
            uint32_t cfg_roi4_mbx_e                 :  7; /* [14: 8],       r/w,       0x0 */
            uint32_t reserved_15                    :  1; /* [   15],      rsvd,       0x0 */
            uint32_t cfg_roi4_mby_s                 :  7; /* [22:16],       r/w,       0x0 */
            uint32_t reserved_23                    :  1; /* [   23],      rsvd,       0x0 */
            uint32_t cfg_roi4_mby_e                 :  7; /* [30:24],       r/w,       0x0 */
            uint32_t reserved_31                    :  1; /* [   31],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_roi4;

    /* 0x268 : h264_roi5 */
    union {
        struct {
            uint32_t cfg_roi5_mbx_s                 :  7; /* [ 6: 0],       r/w,       0x0 */
            uint32_t reserved_7                     :  1; /* [    7],      rsvd,       0x0 */
            uint32_t cfg_roi5_mbx_e                 :  7; /* [14: 8],       r/w,       0x0 */
            uint32_t reserved_15                    :  1; /* [   15],      rsvd,       0x0 */
            uint32_t cfg_roi5_mby_s                 :  7; /* [22:16],       r/w,       0x0 */
            uint32_t reserved_23                    :  1; /* [   23],      rsvd,       0x0 */
            uint32_t cfg_roi5_mby_e                 :  7; /* [30:24],       r/w,       0x0 */
            uint32_t reserved_31                    :  1; /* [   31],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_roi5;

    /* 0x26c : h264_roi6 */
    union {
        struct {
            uint32_t cfg_roi6_mbx_s                 :  7; /* [ 6: 0],       r/w,       0x0 */
            uint32_t reserved_7                     :  1; /* [    7],      rsvd,       0x0 */
            uint32_t cfg_roi6_mbx_e                 :  7; /* [14: 8],       r/w,       0x0 */
            uint32_t reserved_15                    :  1; /* [   15],      rsvd,       0x0 */
            uint32_t cfg_roi6_mby_s                 :  7; /* [22:16],       r/w,       0x0 */
            uint32_t reserved_23                    :  1; /* [   23],      rsvd,       0x0 */
            uint32_t cfg_roi6_mby_e                 :  7; /* [30:24],       r/w,       0x0 */
            uint32_t reserved_31                    :  1; /* [   31],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_roi6;

    /* 0x270 : h264_roi7 */
    union {
        struct {
            uint32_t cfg_roi7_mbx_s                 :  7; /* [ 6: 0],       r/w,       0x0 */
            uint32_t reserved_7                     :  1; /* [    7],      rsvd,       0x0 */
            uint32_t cfg_roi7_mbx_e                 :  7; /* [14: 8],       r/w,       0x0 */
            uint32_t reserved_15                    :  1; /* [   15],      rsvd,       0x0 */
            uint32_t cfg_roi7_mby_s                 :  7; /* [22:16],       r/w,       0x0 */
            uint32_t reserved_23                    :  1; /* [   23],      rsvd,       0x0 */
            uint32_t cfg_roi7_mby_e                 :  7; /* [30:24],       r/w,       0x0 */
            uint32_t reserved_31                    :  1; /* [   31],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_roi7;

    /* 0x274 : h264_s_roi_mode */
    union {
        struct {
            uint32_t cfg_s_roi_en                   :  8; /* [ 7: 0],       r/w,       0x0 */
            uint32_t cfg_s_roi_upd                  :  1; /* [    8],       w1p,       0x0 */
            uint32_t reserved_9_31                  : 23; /* [31: 9],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_s_roi_mode;

    /* 0x278 : h264_s_roi_bit */
    union {
        struct {
            uint32_t cfg_s_pbit_ratio               : 13; /* [12: 0],       r/w,     0x400 */
            uint32_t cfg_s_ibit_ratio               : 13; /* [25:13],       r/w,     0x400 */
            uint32_t cfg_s_ithre                    :  6; /* [31:26],       r/w,      0x20 */
        }BF;
        uint32_t WORD;
    } h264_s_roi_bit;

    /* 0x27c : h264_s_roi_qptune */
    union {
        struct {
            uint32_t cfg_s_pqp_decr                 :  6; /* [ 5: 0],       r/w,       0x0 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],      rsvd,       0x0 */
            uint32_t cfg_s_iqp_decr                 :  6; /* [13: 8],       r/w,       0x0 */
            uint32_t reserved_14_15                 :  2; /* [15:14],      rsvd,       0x0 */
            uint32_t cfg_s_n2r_qp_decr              :  6; /* [21:16],       r/w,       0x0 */
            uint32_t reserved_22_23                 :  2; /* [23:22],      rsvd,       0x0 */
            uint32_t cfg_s_fixqp                    :  6; /* [29:24],       r/w,       0x0 */
            uint32_t reserved_30_31                 :  2; /* [31:30],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_s_roi_qptune;

    /* 0x280 : h264_s_roi_bittune */
    union {
        struct {
            uint32_t cfg_s_roi_pbit_ofst            :  5; /* [ 4: 0],       r/w,       0x0 */
            uint32_t reserved_5_7                   :  3; /* [ 7: 5],      rsvd,       0x0 */
            uint32_t cfg_s_roi_ibit_ofst            :  8; /* [15: 8],       r/w,       0x0 */
            uint32_t cfg_s_nroi_pbit_ofst           :  5; /* [20:16],       r/w,       0x0 */
            uint32_t reserved_21_23                 :  3; /* [23:21],      rsvd,       0x0 */
            uint32_t cfg_s_nroi_ibit_ofst           :  8; /* [31:24],       r/w,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_s_roi_bittune;

    /* 0x284 : h264_s_roi0 */
    union {
        struct {
            uint32_t cfg_s_roi0_mbx_s               :  7; /* [ 6: 0],       r/w,       0x0 */
            uint32_t reserved_7                     :  1; /* [    7],      rsvd,       0x0 */
            uint32_t cfg_s_roi0_mbx_e               :  7; /* [14: 8],       r/w,       0x0 */
            uint32_t reserved_15                    :  1; /* [   15],      rsvd,       0x0 */
            uint32_t cfg_s_roi0_mby_s               :  7; /* [22:16],       r/w,       0x0 */
            uint32_t reserved_23                    :  1; /* [   23],      rsvd,       0x0 */
            uint32_t cfg_s_roi0_mby_e               :  7; /* [30:24],       r/w,       0x0 */
            uint32_t reserved_31                    :  1; /* [   31],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_s_roi0;

    /* 0x288 : h264_s_roi1 */
    union {
        struct {
            uint32_t cfg_s_roi1_mbx_s               :  7; /* [ 6: 0],       r/w,       0x0 */
            uint32_t reserved_7                     :  1; /* [    7],      rsvd,       0x0 */
            uint32_t cfg_s_roi1_mbx_e               :  7; /* [14: 8],       r/w,       0x0 */
            uint32_t reserved_15                    :  1; /* [   15],      rsvd,       0x0 */
            uint32_t cfg_s_roi1_mby_s               :  7; /* [22:16],       r/w,       0x0 */
            uint32_t reserved_23                    :  1; /* [   23],      rsvd,       0x0 */
            uint32_t cfg_s_roi1_mby_e               :  7; /* [30:24],       r/w,       0x0 */
            uint32_t reserved_31                    :  1; /* [   31],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_s_roi1;

    /* 0x28c : h264_s_roi2 */
    union {
        struct {
            uint32_t cfg_s_roi2_mbx_s               :  7; /* [ 6: 0],       r/w,       0x0 */
            uint32_t reserved_7                     :  1; /* [    7],      rsvd,       0x0 */
            uint32_t cfg_s_roi2_mbx_e               :  7; /* [14: 8],       r/w,       0x0 */
            uint32_t reserved_15                    :  1; /* [   15],      rsvd,       0x0 */
            uint32_t cfg_s_roi2_mby_s               :  7; /* [22:16],       r/w,       0x0 */
            uint32_t reserved_23                    :  1; /* [   23],      rsvd,       0x0 */
            uint32_t cfg_s_roi2_mby_e               :  7; /* [30:24],       r/w,       0x0 */
            uint32_t reserved_31                    :  1; /* [   31],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_s_roi2;

    /* 0x290 : h264_s_roi3 */
    union {
        struct {
            uint32_t cfg_s_roi3_mbx_s               :  7; /* [ 6: 0],       r/w,       0x0 */
            uint32_t reserved_7                     :  1; /* [    7],      rsvd,       0x0 */
            uint32_t cfg_s_roi3_mbx_e               :  7; /* [14: 8],       r/w,       0x0 */
            uint32_t reserved_15                    :  1; /* [   15],      rsvd,       0x0 */
            uint32_t cfg_s_roi3_mby_s               :  7; /* [22:16],       r/w,       0x0 */
            uint32_t reserved_23                    :  1; /* [   23],      rsvd,       0x0 */
            uint32_t cfg_s_roi3_mby_e               :  7; /* [30:24],       r/w,       0x0 */
            uint32_t reserved_31                    :  1; /* [   31],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_s_roi3;

    /* 0x294 : h264_s_roi4 */
    union {
        struct {
            uint32_t cfg_s_roi4_mbx_s               :  7; /* [ 6: 0],       r/w,       0x0 */
            uint32_t reserved_7                     :  1; /* [    7],      rsvd,       0x0 */
            uint32_t cfg_s_roi4_mbx_e               :  7; /* [14: 8],       r/w,       0x0 */
            uint32_t reserved_15                    :  1; /* [   15],      rsvd,       0x0 */
            uint32_t cfg_s_roi4_mby_s               :  7; /* [22:16],       r/w,       0x0 */
            uint32_t reserved_23                    :  1; /* [   23],      rsvd,       0x0 */
            uint32_t cfg_s_roi4_mby_e               :  7; /* [30:24],       r/w,       0x0 */
            uint32_t reserved_31                    :  1; /* [   31],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_s_roi4;

    /* 0x298 : h264_s_roi5 */
    union {
        struct {
            uint32_t cfg_s_roi5_mbx_s               :  7; /* [ 6: 0],       r/w,       0x0 */
            uint32_t reserved_7                     :  1; /* [    7],      rsvd,       0x0 */
            uint32_t cfg_s_roi5_mbx_e               :  7; /* [14: 8],       r/w,       0x0 */
            uint32_t reserved_15                    :  1; /* [   15],      rsvd,       0x0 */
            uint32_t cfg_s_roi5_mby_s               :  7; /* [22:16],       r/w,       0x0 */
            uint32_t reserved_23                    :  1; /* [   23],      rsvd,       0x0 */
            uint32_t cfg_s_roi5_mby_e               :  7; /* [30:24],       r/w,       0x0 */
            uint32_t reserved_31                    :  1; /* [   31],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_s_roi5;

    /* 0x29c : h264_s_roi6 */
    union {
        struct {
            uint32_t cfg_s_roi6_mbx_s               :  7; /* [ 6: 0],       r/w,       0x0 */
            uint32_t reserved_7                     :  1; /* [    7],      rsvd,       0x0 */
            uint32_t cfg_s_roi6_mbx_e               :  7; /* [14: 8],       r/w,       0x0 */
            uint32_t reserved_15                    :  1; /* [   15],      rsvd,       0x0 */
            uint32_t cfg_s_roi6_mby_s               :  7; /* [22:16],       r/w,       0x0 */
            uint32_t reserved_23                    :  1; /* [   23],      rsvd,       0x0 */
            uint32_t cfg_s_roi6_mby_e               :  7; /* [30:24],       r/w,       0x0 */
            uint32_t reserved_31                    :  1; /* [   31],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_s_roi6;

    /* 0x2a0 : reserved */
    uint8_t reserved672[96];

    /* 0x300 : h264_s_roi7 */
    union {
        struct {
            uint32_t cfg_s_roi7_mbx_s               :  7; /* [ 6: 0],       r/w,       0x0 */
            uint32_t reserved_7                     :  1; /* [    7],      rsvd,       0x0 */
            uint32_t cfg_s_roi7_mbx_e               :  7; /* [14: 8],       r/w,       0x0 */
            uint32_t reserved_15                    :  1; /* [   15],      rsvd,       0x0 */
            uint32_t cfg_s_roi7_mby_s               :  7; /* [22:16],       r/w,       0x0 */
            uint32_t reserved_23                    :  1; /* [   23],      rsvd,       0x0 */
            uint32_t cfg_s_roi7_mby_e               :  7; /* [30:24],       r/w,       0x0 */
            uint32_t reserved_31                    :  1; /* [   31],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_s_roi7;

    /* 0x304 : h264_osd_en */
    union {
        struct {
            uint32_t cfg_osd_en                     : 16; /* [15: 0],       r/w,       0x0 */
            uint32_t cfg_osd_mssel                  : 16; /* [31:16],       r/w,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_osd_en;

    /* 0x308 : h264_osd0 */
    union {
        struct {
            uint32_t cfg_osd0_mbx_s                 :  7; /* [ 6: 0],       r/w,       0x0 */
            uint32_t reserved_7                     :  1; /* [    7],      rsvd,       0x0 */
            uint32_t cfg_osd0_mbx_e                 :  7; /* [14: 8],       r/w,       0x0 */
            uint32_t reserved_15                    :  1; /* [   15],      rsvd,       0x0 */
            uint32_t cfg_osd0_mby_s                 :  7; /* [22:16],       r/w,       0x0 */
            uint32_t reserved_23                    :  1; /* [   23],      rsvd,       0x0 */
            uint32_t cfg_osd0_mby_e                 :  7; /* [30:24],       r/w,       0x0 */
            uint32_t reserved_31                    :  1; /* [   31],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_osd0;

    /* 0x30c : h264_osd1 */
    union {
        struct {
            uint32_t cfg_osd1_mbx_s                 :  7; /* [ 6: 0],       r/w,       0x0 */
            uint32_t reserved_7                     :  1; /* [    7],      rsvd,       0x0 */
            uint32_t cfg_osd1_mbx_e                 :  7; /* [14: 8],       r/w,       0x0 */
            uint32_t reserved_15                    :  1; /* [   15],      rsvd,       0x0 */
            uint32_t cfg_osd1_mby_s                 :  7; /* [22:16],       r/w,       0x0 */
            uint32_t reserved_23                    :  1; /* [   23],      rsvd,       0x0 */
            uint32_t cfg_osd1_mby_e                 :  7; /* [30:24],       r/w,       0x0 */
            uint32_t reserved_31                    :  1; /* [   31],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_osd1;

    /* 0x310 : h264_osd2 */
    union {
        struct {
            uint32_t cfg_osd2_mbx_s                 :  7; /* [ 6: 0],       r/w,       0x0 */
            uint32_t reserved_7                     :  1; /* [    7],      rsvd,       0x0 */
            uint32_t cfg_osd2_mbx_e                 :  7; /* [14: 8],       r/w,       0x0 */
            uint32_t reserved_15                    :  1; /* [   15],      rsvd,       0x0 */
            uint32_t cfg_osd2_mby_s                 :  7; /* [22:16],       r/w,       0x0 */
            uint32_t reserved_23                    :  1; /* [   23],      rsvd,       0x0 */
            uint32_t cfg_osd2_mby_e                 :  7; /* [30:24],       r/w,       0x0 */
            uint32_t reserved_31                    :  1; /* [   31],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_osd2;

    /* 0x314 : h264_osd3 */
    union {
        struct {
            uint32_t cfg_osd3_mbx_s                 :  7; /* [ 6: 0],       r/w,       0x0 */
            uint32_t reserved_7                     :  1; /* [    7],      rsvd,       0x0 */
            uint32_t cfg_osd3_mbx_e                 :  7; /* [14: 8],       r/w,       0x0 */
            uint32_t reserved_15                    :  1; /* [   15],      rsvd,       0x0 */
            uint32_t cfg_osd3_mby_s                 :  7; /* [22:16],       r/w,       0x0 */
            uint32_t reserved_23                    :  1; /* [   23],      rsvd,       0x0 */
            uint32_t cfg_osd3_mby_e                 :  7; /* [30:24],       r/w,       0x0 */
            uint32_t reserved_31                    :  1; /* [   31],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_osd3;

    /* 0x318 : h264_osd4 */
    union {
        struct {
            uint32_t cfg_osd4_mbx_s                 :  7; /* [ 6: 0],       r/w,       0x0 */
            uint32_t reserved_7                     :  1; /* [    7],      rsvd,       0x0 */
            uint32_t cfg_osd4_mbx_e                 :  7; /* [14: 8],       r/w,       0x0 */
            uint32_t reserved_15                    :  1; /* [   15],      rsvd,       0x0 */
            uint32_t cfg_osd4_mby_s                 :  7; /* [22:16],       r/w,       0x0 */
            uint32_t reserved_23                    :  1; /* [   23],      rsvd,       0x0 */
            uint32_t cfg_osd4_mby_e                 :  7; /* [30:24],       r/w,       0x0 */
            uint32_t reserved_31                    :  1; /* [   31],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_osd4;

    /* 0x31c : h264_osd5 */
    union {
        struct {
            uint32_t cfg_osd5_mbx_s                 :  7; /* [ 6: 0],       r/w,       0x0 */
            uint32_t reserved_7                     :  1; /* [    7],      rsvd,       0x0 */
            uint32_t cfg_osd5_mbx_e                 :  7; /* [14: 8],       r/w,       0x0 */
            uint32_t reserved_15                    :  1; /* [   15],      rsvd,       0x0 */
            uint32_t cfg_osd5_mby_s                 :  7; /* [22:16],       r/w,       0x0 */
            uint32_t reserved_23                    :  1; /* [   23],      rsvd,       0x0 */
            uint32_t cfg_osd5_mby_e                 :  7; /* [30:24],       r/w,       0x0 */
            uint32_t reserved_31                    :  1; /* [   31],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_osd5;

    /* 0x320 : h264_osd6 */
    union {
        struct {
            uint32_t cfg_osd6_mbx_s                 :  7; /* [ 6: 0],       r/w,       0x0 */
            uint32_t reserved_7                     :  1; /* [    7],      rsvd,       0x0 */
            uint32_t cfg_osd6_mbx_e                 :  7; /* [14: 8],       r/w,       0x0 */
            uint32_t reserved_15                    :  1; /* [   15],      rsvd,       0x0 */
            uint32_t cfg_osd6_mby_s                 :  7; /* [22:16],       r/w,       0x0 */
            uint32_t reserved_23                    :  1; /* [   23],      rsvd,       0x0 */
            uint32_t cfg_osd6_mby_e                 :  7; /* [30:24],       r/w,       0x0 */
            uint32_t reserved_31                    :  1; /* [   31],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_osd6;

    /* 0x324 : h264_osd7 */
    union {
        struct {
            uint32_t cfg_osd7_mbx_s                 :  7; /* [ 6: 0],       r/w,       0x0 */
            uint32_t reserved_7                     :  1; /* [    7],      rsvd,       0x0 */
            uint32_t cfg_osd7_mbx_e                 :  7; /* [14: 8],       r/w,       0x0 */
            uint32_t reserved_15                    :  1; /* [   15],      rsvd,       0x0 */
            uint32_t cfg_osd7_mby_s                 :  7; /* [22:16],       r/w,       0x0 */
            uint32_t reserved_23                    :  1; /* [   23],      rsvd,       0x0 */
            uint32_t cfg_osd7_mby_e                 :  7; /* [30:24],       r/w,       0x0 */
            uint32_t reserved_31                    :  1; /* [   31],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_osd7;

    /* 0x328 : h264_osd8 */
    union {
        struct {
            uint32_t cfg_osd8_mbx_s                 :  7; /* [ 6: 0],       r/w,       0x0 */
            uint32_t reserved_7                     :  1; /* [    7],      rsvd,       0x0 */
            uint32_t cfg_osd8_mbx_e                 :  7; /* [14: 8],       r/w,       0x0 */
            uint32_t reserved_15                    :  1; /* [   15],      rsvd,       0x0 */
            uint32_t cfg_osd8_mby_s                 :  7; /* [22:16],       r/w,       0x0 */
            uint32_t reserved_23                    :  1; /* [   23],      rsvd,       0x0 */
            uint32_t cfg_osd8_mby_e                 :  7; /* [30:24],       r/w,       0x0 */
            uint32_t reserved_31                    :  1; /* [   31],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_osd8;

    /* 0x32c : h264_osd9 */
    union {
        struct {
            uint32_t cfg_osd9_mbx_s                 :  7; /* [ 6: 0],       r/w,       0x0 */
            uint32_t reserved_7                     :  1; /* [    7],      rsvd,       0x0 */
            uint32_t cfg_osd9_mbx_e                 :  7; /* [14: 8],       r/w,       0x0 */
            uint32_t reserved_15                    :  1; /* [   15],      rsvd,       0x0 */
            uint32_t cfg_osd9_mby_s                 :  7; /* [22:16],       r/w,       0x0 */
            uint32_t reserved_23                    :  1; /* [   23],      rsvd,       0x0 */
            uint32_t cfg_osd9_mby_e                 :  7; /* [30:24],       r/w,       0x0 */
            uint32_t reserved_31                    :  1; /* [   31],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_osd9;

    /* 0x330 : h264_osd10 */
    union {
        struct {
            uint32_t cfg_osd10_mbx_s                :  7; /* [ 6: 0],       r/w,       0x0 */
            uint32_t reserved_7                     :  1; /* [    7],      rsvd,       0x0 */
            uint32_t cfg_osd10_mbx_e                :  7; /* [14: 8],       r/w,       0x0 */
            uint32_t reserved_15                    :  1; /* [   15],      rsvd,       0x0 */
            uint32_t cfg_osd10_mby_s                :  7; /* [22:16],       r/w,       0x0 */
            uint32_t reserved_23                    :  1; /* [   23],      rsvd,       0x0 */
            uint32_t cfg_osd10_mby_e                :  7; /* [30:24],       r/w,       0x0 */
            uint32_t reserved_31                    :  1; /* [   31],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_osd10;

    /* 0x334 : h264_osd11 */
    union {
        struct {
            uint32_t cfg_osd11_mbx_s                :  7; /* [ 6: 0],       r/w,       0x0 */
            uint32_t reserved_7                     :  1; /* [    7],      rsvd,       0x0 */
            uint32_t cfg_osd11_mbx_e                :  7; /* [14: 8],       r/w,       0x0 */
            uint32_t reserved_15                    :  1; /* [   15],      rsvd,       0x0 */
            uint32_t cfg_osd11_mby_s                :  7; /* [22:16],       r/w,       0x0 */
            uint32_t reserved_23                    :  1; /* [   23],      rsvd,       0x0 */
            uint32_t cfg_osd11_mby_e                :  7; /* [30:24],       r/w,       0x0 */
            uint32_t reserved_31                    :  1; /* [   31],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_osd11;

    /* 0x338 : h264_osd12 */
    union {
        struct {
            uint32_t cfg_osd12_mbx_s                :  7; /* [ 6: 0],       r/w,       0x0 */
            uint32_t reserved_7                     :  1; /* [    7],      rsvd,       0x0 */
            uint32_t cfg_osd12_mbx_e                :  7; /* [14: 8],       r/w,       0x0 */
            uint32_t reserved_15                    :  1; /* [   15],      rsvd,       0x0 */
            uint32_t cfg_osd12_mby_s                :  7; /* [22:16],       r/w,       0x0 */
            uint32_t reserved_23                    :  1; /* [   23],      rsvd,       0x0 */
            uint32_t cfg_osd12_mby_e                :  7; /* [30:24],       r/w,       0x0 */
            uint32_t reserved_31                    :  1; /* [   31],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_osd12;

    /* 0x33c : h264_osd13 */
    union {
        struct {
            uint32_t cfg_osd13_mbx_s                :  7; /* [ 6: 0],       r/w,       0x0 */
            uint32_t reserved_7                     :  1; /* [    7],      rsvd,       0x0 */
            uint32_t cfg_osd13_mbx_e                :  7; /* [14: 8],       r/w,       0x0 */
            uint32_t reserved_15                    :  1; /* [   15],      rsvd,       0x0 */
            uint32_t cfg_osd13_mby_s                :  7; /* [22:16],       r/w,       0x0 */
            uint32_t reserved_23                    :  1; /* [   23],      rsvd,       0x0 */
            uint32_t cfg_osd13_mby_e                :  7; /* [30:24],       r/w,       0x0 */
            uint32_t reserved_31                    :  1; /* [   31],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_osd13;

    /* 0x340 : h264_osd14 */
    union {
        struct {
            uint32_t cfg_osd14_mbx_s                :  7; /* [ 6: 0],       r/w,       0x0 */
            uint32_t reserved_7                     :  1; /* [    7],      rsvd,       0x0 */
            uint32_t cfg_osd14_mbx_e                :  7; /* [14: 8],       r/w,       0x0 */
            uint32_t reserved_15                    :  1; /* [   15],      rsvd,       0x0 */
            uint32_t cfg_osd14_mby_s                :  7; /* [22:16],       r/w,       0x0 */
            uint32_t reserved_23                    :  1; /* [   23],      rsvd,       0x0 */
            uint32_t cfg_osd14_mby_e                :  7; /* [30:24],       r/w,       0x0 */
            uint32_t reserved_31                    :  1; /* [   31],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_osd14;

    /* 0x344 : h264_osd15 */
    union {
        struct {
            uint32_t cfg_osd15_mbx_s                :  7; /* [ 6: 0],       r/w,       0x0 */
            uint32_t reserved_7                     :  1; /* [    7],      rsvd,       0x0 */
            uint32_t cfg_osd15_mbx_e                :  7; /* [14: 8],       r/w,       0x0 */
            uint32_t reserved_15                    :  1; /* [   15],      rsvd,       0x0 */
            uint32_t cfg_osd15_mby_s                :  7; /* [22:16],       r/w,       0x0 */
            uint32_t reserved_23                    :  1; /* [   23],      rsvd,       0x0 */
            uint32_t cfg_osd15_mby_e                :  7; /* [30:24],       r/w,       0x0 */
            uint32_t reserved_31                    :  1; /* [   31],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_osd15;

    /* 0x348 : h264_mv0_en */
    union {
        struct {
            uint32_t cfg_mv0_en                     :  1; /* [    0],       r/w,       0x0 */
            uint32_t cfg_s_mv0_en                   :  1; /* [    1],       r/w,       0x0 */
            uint32_t reserved_2_31                  : 30; /* [31: 2],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } h264_mv0_en;

    /* 0x34c : pfch_dbg_reqcnt */
    union {
        struct {
            uint32_t dbg_reqcnt                     : 32; /* [31: 0],         r,       0x0 */
        }BF;
        uint32_t WORD;
    } pfch_dbg_reqcnt;

    /* 0x350 : pfch_dbg_rcmd */
    union {
        struct {
            uint32_t dbg_rcmd                       : 32; /* [31: 0],         r,       0x0 */
        }BF;
        uint32_t WORD;
    } pfch_dbg_rcmd;

    /* 0x354 : pfch_dbg_wcmd */
    union {
        struct {
            uint32_t dbg_wcmd                       : 32; /* [31: 0],         r,       0x0 */
        }BF;
        uint32_t WORD;
    } pfch_dbg_wcmd;

    /* 0x358 : pfch_dbg_wdata */
    union {
        struct {
            uint32_t dbg_wdata                      : 32; /* [31: 0],         r,       0x0 */
        }BF;
        uint32_t WORD;
    } pfch_dbg_wdata;

    /* 0x35c : pfch_dbg_pfchsta */
    union {
        struct {
            uint32_t dbg_pfchsta                    : 32; /* [31: 0],         r,       0x0 */
        }BF;
        uint32_t WORD;
    } pfch_dbg_pfchsta;

    /* 0x360 : pfchv_dbg_reqcnt */
    union {
        struct {
            uint32_t dbgv_reqcnt                    : 32; /* [31: 0],         r,       0x0 */
        }BF;
        uint32_t WORD;
    } pfchv_dbg_reqcnt;

    /* 0x364 : pfchv_dbg_rcmd */
    union {
        struct {
            uint32_t dbgv_rcmd                      : 32; /* [31: 0],         r,       0x0 */
        }BF;
        uint32_t WORD;
    } pfchv_dbg_rcmd;

    /* 0x368 : pfchv_dbg_wcmd */
    union {
        struct {
            uint32_t dbgv_wcmd                      : 32; /* [31: 0],         r,       0x0 */
        }BF;
        uint32_t WORD;
    } pfchv_dbg_wcmd;

    /* 0x36c : pfchv_dbg_wdata */
    union {
        struct {
            uint32_t dbgv_wdata                     : 32; /* [31: 0],         r,       0x0 */
        }BF;
        uint32_t WORD;
    } pfchv_dbg_wdata;

    /* 0x370 : pfchv_dbg_pfchsta */
    union {
        struct {
            uint32_t dbgv_pfchsta                   : 32; /* [31: 0],         r,       0x0 */
        }BF;
        uint32_t WORD;
    } pfchv_dbg_pfchsta;

    /* 0x374 : pfch_s_dbg_reqcnt */
    union {
        struct {
            uint32_t s_dbg_reqcnt                   : 32; /* [31: 0],         r,       0x0 */
        }BF;
        uint32_t WORD;
    } pfch_s_dbg_reqcnt;

    /* 0x378 : pfch_s_dbg_rcmd */
    union {
        struct {
            uint32_t s_dbg_rcmd                     : 32; /* [31: 0],         r,       0x0 */
        }BF;
        uint32_t WORD;
    } pfch_s_dbg_rcmd;

    /* 0x37c : pfch_s_dbg_wcmd */
    union {
        struct {
            uint32_t s_dbg_wcmd                     : 32; /* [31: 0],         r,       0x0 */
        }BF;
        uint32_t WORD;
    } pfch_s_dbg_wcmd;

    /* 0x380 : pfch_s_dbg_wdata */
    union {
        struct {
            uint32_t s_dbg_wdata                    : 32; /* [31: 0],         r,       0x0 */
        }BF;
        uint32_t WORD;
    } pfch_s_dbg_wdata;

    /* 0x384 : pfch_s_dbg_pfchsta */
    union {
        struct {
            uint32_t s_dbg_pfchsta                  : 32; /* [31: 0],         r,       0x0 */
        }BF;
        uint32_t WORD;
    } pfch_s_dbg_pfchsta;

    /* 0x388 : pfchv_s_dbg_reqcnt */
    union {
        struct {
            uint32_t s_dbgv_reqcnt                  : 32; /* [31: 0],         r,       0x0 */
        }BF;
        uint32_t WORD;
    } pfchv_s_dbg_reqcnt;

    /* 0x38c : pfchv_s_dbg_rcmd */
    union {
        struct {
            uint32_t s_dbgv_rcmd                    : 32; /* [31: 0],         r,       0x0 */
        }BF;
        uint32_t WORD;
    } pfchv_s_dbg_rcmd;

    /* 0x390 : pfchv_s_dbg_wcmd */
    union {
        struct {
            uint32_t s_dbgv_wcmd                    : 32; /* [31: 0],         r,       0x0 */
        }BF;
        uint32_t WORD;
    } pfchv_s_dbg_wcmd;

    /* 0x394 : pfchv_s_dbg_wdata */
    union {
        struct {
            uint32_t s_dbgv_wdata                   : 32; /* [31: 0],         r,       0x0 */
        }BF;
        uint32_t WORD;
    } pfchv_s_dbg_wdata;

    /* 0x398 : pfchv_s_dbg_pfchsta */
    union {
        struct {
            uint32_t s_dbgv_pfchsta                 : 32; /* [31: 0],         r,       0x0 */
        }BF;
        uint32_t WORD;
    } pfchv_s_dbg_pfchsta;

    /* 0x39c : vdonr */
    union {
        struct {
            uint32_t noiselevel                     :  6; /* [ 5: 0],       r/w,       0x0 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],      rsvd,       0x0 */
            uint32_t temperalfilterstrength         :  4; /* [11: 8],       r/w,       0x5 */
            uint32_t reserved_12_15                 :  4; /* [15:12],      rsvd,       0x0 */
            uint32_t s_noiselevel                   :  6; /* [21:16],       r/w,       0x0 */
            uint32_t reserved_22_23                 :  2; /* [23:22],      rsvd,       0x0 */
            uint32_t s_temperalfilterstrength       :  4; /* [27:24],       r/w,       0x5 */
            uint32_t reserved_28_31                 :  4; /* [31:28],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } vdonr;

    /* 0x3a0 : vdonr_mvctrl */
    union {
        struct {
            uint32_t zmv_pflevel                    : 17; /* [16: 0],       r/w,       0x0 */
            uint32_t reserved_17_31                 : 15; /* [31:17],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } vdonr_mvctrl;

    /* 0x3a4 : vdonr_sta_ctrl */
    union {
        struct {
            uint32_t ysmlr_thr                      : 16; /* [15: 0],       r/w,       0x0 */
            uint32_t reserved_16_31                 : 16; /* [31:16],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } vdonr_sta_ctrl;

    /* 0x3a8 : vdonr_absmv_sum */
    union {
        struct {
            uint32_t absmv_sum                      : 22; /* [21: 0],         r,       0x0 */
            uint32_t reserved_22_31                 : 10; /* [31:22],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } vdonr_absmv_sum;

    /* 0x3ac : vdonr_mvlevel */
    union {
        struct {
            uint32_t nzmv_mbcnt                     : 14; /* [13: 0],         r,       0x0 */
            uint32_t reserved_14_15                 :  2; /* [15:14],      rsvd,       0x0 */
            uint32_t ysmlr_mbcnt                    : 14; /* [29:16],         r,       0x0 */
            uint32_t reserved_30_31                 :  2; /* [31:30],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } vdonr_mvlevel;

    /* 0x3b0 : vdonr_pmbsad */
    union {
        struct {
            uint32_t pmb_sad                        : 30; /* [29: 0],         r,       0x0 */
            uint32_t reserved_30_31                 :  2; /* [31:30],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } vdonr_pmbsad;

    /* 0x3b4 : vdonr_imbcnt */
    union {
        struct {
            uint32_t intra_mbcnt                    : 14; /* [13: 0],         r,       0x0 */
            uint32_t reserved_14_31                 : 18; /* [31:14],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } vdonr_imbcnt;

    /* 0x3b8 : vdonr_s_mvctrl */
    union {
        struct {
            uint32_t s_zmv_pflevel                  : 17; /* [16: 0],       r/w,       0x0 */
            uint32_t reserved_17_31                 : 15; /* [31:17],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } vdonr_s_mvctrl;

    /* 0x3bc : vdonr_s_sta_ctrl */
    union {
        struct {
            uint32_t s_ysmlr_thr                    : 16; /* [15: 0],       r/w,       0x0 */
            uint32_t reserved_16_31                 : 16; /* [31:16],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } vdonr_s_sta_ctrl;

    /* 0x3c0 : vdonr_s_absmv_sum */
    union {
        struct {
            uint32_t s_absmv_sum                    : 22; /* [21: 0],         r,       0x0 */
            uint32_t reserved_22_31                 : 10; /* [31:22],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } vdonr_s_absmv_sum;

    /* 0x3c4 : vdonr_s_mvlevel */
    union {
        struct {
            uint32_t s_nzmv_mbcnt                   : 14; /* [13: 0],         r,       0x0 */
            uint32_t reserved_14_15                 :  2; /* [15:14],      rsvd,       0x0 */
            uint32_t s_ysmlr_mbcnt                  : 14; /* [29:16],         r,       0x0 */
            uint32_t reserved_30_31                 :  2; /* [31:30],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } vdonr_s_mvlevel;

    /* 0x3c8 : vdonr_s_pmbsad */
    union {
        struct {
            uint32_t s_pmb_sad                      : 30; /* [29: 0],         r,       0x0 */
            uint32_t reserved_30_31                 :  2; /* [31:30],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } vdonr_s_pmbsad;

    /* 0x3cc : vdonr_s_imbcnt */
    union {
        struct {
            uint32_t s_intra_mbcnt                  : 14; /* [13: 0],         r,       0x0 */
            uint32_t reserved_14_31                 : 18; /* [31:14],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } vdonr_s_imbcnt;

    /* 0x3d0 : vdo_stuf_dbg */
    union {
        struct {
            uint32_t pic_bycnt                      : 26; /* [25: 0],         r,       0x0 */
            uint32_t pic_bycnt_ovf                  :  1; /* [   26],         r,       0x0 */
            uint32_t stuf_ovf                       :  1; /* [   27],         r,       0x0 */
            uint32_t bincnt_ovf                     :  1; /* [   28],         r,       0x0 */
            uint32_t reserved_29_31                 :  3; /* [31:29],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } vdo_stuf_dbg;

    /* 0x3d4 : vdo_nal_dbg1 */
    union {
        struct {
            uint32_t stuf_cnt                       : 26; /* [25: 0],         r,       0x0 */
            uint32_t sh_state                       :  6; /* [31:26],         r,       0x0 */
        }BF;
        uint32_t WORD;
    } vdo_nal_dbg1;

    /* 0x3d8 : vdo_nal_dbg2 */
    union {
        struct {
            uint32_t bincntx3                       : 30; /* [29: 0],         r,       0x0 */
            uint32_t reserved_30_31                 :  2; /* [31:30],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } vdo_nal_dbg2;

    /* 0x3dc : vdo_nal_dbg3 */
    union {
        struct {
            uint32_t mp_mbx                         :  7; /* [ 6: 0],         r,       0x0 */
            uint32_t reserved_7                     :  1; /* [    7],      rsvd,       0x0 */
            uint32_t mp_mby                         :  7; /* [14: 8],         r,       0x0 */
            uint32_t reserved_15_31                 : 17; /* [31:15],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } vdo_nal_dbg3;

    /* 0x3e0 : vdo_roi_dbg */
    union {
        struct {
            uint32_t roi_pmbbits                    : 12; /* [11: 0],         r,       0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],      rsvd,       0x0 */
            uint32_t nroi_pmbbits                   : 12; /* [27:16],         r,       0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } vdo_roi_dbg;

    /* 0x3e4 : vdo_rc_dbg */
    union {
        struct {
            uint32_t rc_min_qp                      :  6; /* [ 5: 0],         r,       0x0 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],      rsvd,       0x0 */
            uint32_t rc_qp                          :  6; /* [13: 8],         r,       0x0 */
            uint32_t reserved_14_31                 : 18; /* [31:14],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } vdo_rc_dbg;

    /* 0x3e8 : vdo_s_stuf_dbg */
    union {
        struct {
            uint32_t s_pic_bycnt                    : 26; /* [25: 0],         r,       0x0 */
            uint32_t s_pic_bycnt_ovf                :  1; /* [   26],         r,       0x0 */
            uint32_t s_stuf_ovf                     :  1; /* [   27],         r,       0x0 */
            uint32_t s_bincnt_ovf                   :  1; /* [   28],         r,       0x0 */
            uint32_t reserved_29_31                 :  3; /* [31:29],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } vdo_s_stuf_dbg;

    /* 0x3ec : vdo_s_nal_dbg1 */
    union {
        struct {
            uint32_t s_stuf_cnt                     : 26; /* [25: 0],         r,       0x0 */
            uint32_t s_sh_state                     :  6; /* [31:26],         r,       0x0 */
        }BF;
        uint32_t WORD;
    } vdo_s_nal_dbg1;

    /* 0x3f0 : vdo_s_nal_dbg2 */
    union {
        struct {
            uint32_t s_bincntx3                     : 30; /* [29: 0],         r,       0x0 */
            uint32_t reserved_30_31                 :  2; /* [31:30],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } vdo_s_nal_dbg2;

    /* 0x3f4 : vdo_s_nal_dbg3 */
    union {
        struct {
            uint32_t s_mp_mbx                       :  7; /* [ 6: 0],         r,       0x0 */
            uint32_t reserved_7                     :  1; /* [    7],      rsvd,       0x0 */
            uint32_t s_mp_mby                       :  7; /* [14: 8],         r,       0x0 */
            uint32_t reserved_15_31                 : 17; /* [31:15],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } vdo_s_nal_dbg3;

    /* 0x3f8 : vdo_s_roi_dbg */
    union {
        struct {
            uint32_t s_roi_pmbbits                  : 12; /* [11: 0],         r,       0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],      rsvd,       0x0 */
            uint32_t s_nroi_pmbbits                 : 12; /* [27:16],         r,       0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } vdo_s_roi_dbg;

    /* 0x3fc : vdo_s_rc_dbg */
    union {
        struct {
            uint32_t s_rc_min_qp                    :  6; /* [ 5: 0],         r,       0x0 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],      rsvd,       0x0 */
            uint32_t s_rc_qp                        :  6; /* [13: 8],         r,       0x0 */
            uint32_t reserved_14_31                 : 18; /* [31:14],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } vdo_s_rc_dbg;

    /* 0x400 : vdo_refaxi_dbg */
    union {
        struct {
            uint32_t ref2axi_busy                   :  1; /* [    0],         r,       0x0 */
            uint32_t reserved_1_3                   :  3; /* [ 3: 1],      rsvd,       0x0 */
            uint32_t ref_rfifo_error                :  2; /* [ 5: 4],         r,       0x0 */
            uint32_t ref_wfifo_error                :  2; /* [ 7: 6],         r,       0x0 */
            uint32_t ref_rfifo_empty                :  3; /* [10: 8],         r,       0x0 */
            uint32_t reserved_11                    :  1; /* [   11],      rsvd,       0x0 */
            uint32_t ref_wfifo_empty                :  5; /* [16:12],         r,       0x0 */
            uint32_t reserved_17_31                 : 15; /* [31:17],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } vdo_refaxi_dbg;

    /* 0x404 : vdo_pfchaxi_dbg */
    union {
        struct {
            uint32_t pfch_rfifo_busy                :  1; /* [    0],         r,       0x0 */
            uint32_t reserved_1_3                   :  3; /* [ 3: 1],      rsvd,       0x0 */
            uint32_t pfch_rfifo_error               :  2; /* [ 5: 4],         r,       0x0 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],      rsvd,       0x0 */
            uint32_t pfch_rfifo_empty               :  3; /* [10: 8],         r,       0x0 */
            uint32_t reserved_11                    :  1; /* [   11],      rsvd,       0x0 */
            uint32_t pfchv_rfifo_busy               :  1; /* [   12],         r,       0x0 */
            uint32_t reserved_13_15                 :  3; /* [15:13],      rsvd,       0x0 */
            uint32_t pfchv_rfifo_error              :  2; /* [17:16],         r,       0x0 */
            uint32_t reserved_18_19                 :  2; /* [19:18],      rsvd,       0x0 */
            uint32_t pfchv_rfifo_empty              :  3; /* [22:20],         r,       0x0 */
            uint32_t reserved_23_31                 :  9; /* [31:23],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } vdo_pfchaxi_dbg;

    /* 0x408 : vdo_bsaxi_dbg */
    union {
        struct {
            uint32_t bs_wfifo_busy                  :  1; /* [    0],         r,       0x0 */
            uint32_t reserved_1_3                   :  3; /* [ 3: 1],      rsvd,       0x0 */
            uint32_t bs_wfifo_error                 :  2; /* [ 5: 4],         r,       0x0 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],      rsvd,       0x0 */
            uint32_t bs_wfifo_empty                 :  5; /* [12: 8],         r,       0x0 */
            uint32_t reserved_13_15                 :  3; /* [15:13],      rsvd,       0x0 */
            uint32_t bs_st                          :  2; /* [17:16],         r,       0x0 */
            uint32_t reserved_18_31                 : 14; /* [31:18],      rsvd,       0x0 */
        }BF;
        uint32_t WORD;
    } vdo_bsaxi_dbg;

    /* 0x40c : vdo_frame_id */
    union {
        struct {
            uint32_t frame_id                       : 32; /* [31: 0],         r,       0x0 */
        }BF;
        uint32_t WORD;
    } vdo_frame_id;

    /* 0x410 : s_vdo_frame_id */
    union {
        struct {
            uint32_t s_frame_id                     : 32; /* [31: 0],         r,       0x0 */
        }BF;
        uint32_t WORD;
    } s_vdo_frame_id;
};

typedef volatile struct vdo_reg vdo_reg_t;

#endif // __VDO_REG_H__