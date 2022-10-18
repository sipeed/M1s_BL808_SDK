/*
 * Copyright (c) 2020 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
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
 */
#ifndef  __DVP2AXI_REG_H__
#define  __DVP2AXI_REG_H__

#include "bl808.h"

/* 0x0 : dvp2axi_configue */
#define DVP2AXI_CONFIGUE_OFFSET                                 (0x0)
#define DVP2AXI_REG_DVP_ENABLE                                  DVP2AXI_REG_DVP_ENABLE
#define DVP2AXI_REG_DVP_ENABLE_POS                              (0U)
#define DVP2AXI_REG_DVP_ENABLE_LEN                              (1U)
#define DVP2AXI_REG_DVP_ENABLE_MSK                              (((1U<<DVP2AXI_REG_DVP_ENABLE_LEN)-1)<<DVP2AXI_REG_DVP_ENABLE_POS)
#define DVP2AXI_REG_DVP_ENABLE_UMSK                             (~(((1U<<DVP2AXI_REG_DVP_ENABLE_LEN)-1)<<DVP2AXI_REG_DVP_ENABLE_POS))
#define DVP2AXI_REG_SW_MODE                                     DVP2AXI_REG_SW_MODE
#define DVP2AXI_REG_SW_MODE_POS                                 (1U)
#define DVP2AXI_REG_SW_MODE_LEN                                 (1U)
#define DVP2AXI_REG_SW_MODE_MSK                                 (((1U<<DVP2AXI_REG_SW_MODE_LEN)-1)<<DVP2AXI_REG_SW_MODE_POS)
#define DVP2AXI_REG_SW_MODE_UMSK                                (~(((1U<<DVP2AXI_REG_SW_MODE_LEN)-1)<<DVP2AXI_REG_SW_MODE_POS))
#define DVP2AXI_REG_FRAM_VLD_POL                                DVP2AXI_REG_FRAM_VLD_POL
#define DVP2AXI_REG_FRAM_VLD_POL_POS                            (2U)
#define DVP2AXI_REG_FRAM_VLD_POL_LEN                            (1U)
#define DVP2AXI_REG_FRAM_VLD_POL_MSK                            (((1U<<DVP2AXI_REG_FRAM_VLD_POL_LEN)-1)<<DVP2AXI_REG_FRAM_VLD_POL_POS)
#define DVP2AXI_REG_FRAM_VLD_POL_UMSK                           (~(((1U<<DVP2AXI_REG_FRAM_VLD_POL_LEN)-1)<<DVP2AXI_REG_FRAM_VLD_POL_POS))
#define DVP2AXI_REG_LINE_VLD_POL                                DVP2AXI_REG_LINE_VLD_POL
#define DVP2AXI_REG_LINE_VLD_POL_POS                            (3U)
#define DVP2AXI_REG_LINE_VLD_POL_LEN                            (1U)
#define DVP2AXI_REG_LINE_VLD_POL_MSK                            (((1U<<DVP2AXI_REG_LINE_VLD_POL_LEN)-1)<<DVP2AXI_REG_LINE_VLD_POL_POS)
#define DVP2AXI_REG_LINE_VLD_POL_UMSK                           (~(((1U<<DVP2AXI_REG_LINE_VLD_POL_LEN)-1)<<DVP2AXI_REG_LINE_VLD_POL_POS))
#define DVP2AXI_REG_XLEN                                        DVP2AXI_REG_XLEN
#define DVP2AXI_REG_XLEN_POS                                    (4U)
#define DVP2AXI_REG_XLEN_LEN                                    (3U)
#define DVP2AXI_REG_XLEN_MSK                                    (((1U<<DVP2AXI_REG_XLEN_LEN)-1)<<DVP2AXI_REG_XLEN_POS)
#define DVP2AXI_REG_XLEN_UMSK                                   (~(((1U<<DVP2AXI_REG_XLEN_LEN)-1)<<DVP2AXI_REG_XLEN_POS))
#define DVP2AXI_REG_DVP_MODE                                    DVP2AXI_REG_DVP_MODE
#define DVP2AXI_REG_DVP_MODE_POS                                (8U)
#define DVP2AXI_REG_DVP_MODE_LEN                                (3U)
#define DVP2AXI_REG_DVP_MODE_MSK                                (((1U<<DVP2AXI_REG_DVP_MODE_LEN)-1)<<DVP2AXI_REG_DVP_MODE_POS)
#define DVP2AXI_REG_DVP_MODE_UMSK                               (~(((1U<<DVP2AXI_REG_DVP_MODE_LEN)-1)<<DVP2AXI_REG_DVP_MODE_POS))
#define DVP2AXI_REG_HW_MODE_FWRAP                               DVP2AXI_REG_HW_MODE_FWRAP
#define DVP2AXI_REG_HW_MODE_FWRAP_POS                           (11U)
#define DVP2AXI_REG_HW_MODE_FWRAP_LEN                           (1U)
#define DVP2AXI_REG_HW_MODE_FWRAP_MSK                           (((1U<<DVP2AXI_REG_HW_MODE_FWRAP_LEN)-1)<<DVP2AXI_REG_HW_MODE_FWRAP_POS)
#define DVP2AXI_REG_HW_MODE_FWRAP_UMSK                          (~(((1U<<DVP2AXI_REG_HW_MODE_FWRAP_LEN)-1)<<DVP2AXI_REG_HW_MODE_FWRAP_POS))
#define DVP2AXI_REG_DROP_EN                                     DVP2AXI_REG_DROP_EN
#define DVP2AXI_REG_DROP_EN_POS                                 (12U)
#define DVP2AXI_REG_DROP_EN_LEN                                 (1U)
#define DVP2AXI_REG_DROP_EN_MSK                                 (((1U<<DVP2AXI_REG_DROP_EN_LEN)-1)<<DVP2AXI_REG_DROP_EN_POS)
#define DVP2AXI_REG_DROP_EN_UMSK                                (~(((1U<<DVP2AXI_REG_DROP_EN_LEN)-1)<<DVP2AXI_REG_DROP_EN_POS))
#define DVP2AXI_REG_DROP_EVEN                                   DVP2AXI_REG_DROP_EVEN
#define DVP2AXI_REG_DROP_EVEN_POS                               (13U)
#define DVP2AXI_REG_DROP_EVEN_LEN                               (1U)
#define DVP2AXI_REG_DROP_EVEN_MSK                               (((1U<<DVP2AXI_REG_DROP_EVEN_LEN)-1)<<DVP2AXI_REG_DROP_EVEN_POS)
#define DVP2AXI_REG_DROP_EVEN_UMSK                              (~(((1U<<DVP2AXI_REG_DROP_EVEN_LEN)-1)<<DVP2AXI_REG_DROP_EVEN_POS))
#define DVP2AXI_REG_DVP_DATA_MODE                               DVP2AXI_REG_DVP_DATA_MODE
#define DVP2AXI_REG_DVP_DATA_MODE_POS                           (16U)
#define DVP2AXI_REG_DVP_DATA_MODE_LEN                           (3U)
#define DVP2AXI_REG_DVP_DATA_MODE_MSK                           (((1U<<DVP2AXI_REG_DVP_DATA_MODE_LEN)-1)<<DVP2AXI_REG_DVP_DATA_MODE_POS)
#define DVP2AXI_REG_DVP_DATA_MODE_UMSK                          (~(((1U<<DVP2AXI_REG_DVP_DATA_MODE_LEN)-1)<<DVP2AXI_REG_DVP_DATA_MODE_POS))
#define DVP2AXI_REG_DVP_DATA_BSEL                               DVP2AXI_REG_DVP_DATA_BSEL
#define DVP2AXI_REG_DVP_DATA_BSEL_POS                           (19U)
#define DVP2AXI_REG_DVP_DATA_BSEL_LEN                           (1U)
#define DVP2AXI_REG_DVP_DATA_BSEL_MSK                           (((1U<<DVP2AXI_REG_DVP_DATA_BSEL_LEN)-1)<<DVP2AXI_REG_DVP_DATA_BSEL_POS)
#define DVP2AXI_REG_DVP_DATA_BSEL_UMSK                          (~(((1U<<DVP2AXI_REG_DVP_DATA_BSEL_LEN)-1)<<DVP2AXI_REG_DVP_DATA_BSEL_POS))
#define DVP2AXI_REG_DVP_PIX_CLK_CG                              DVP2AXI_REG_DVP_PIX_CLK_CG
#define DVP2AXI_REG_DVP_PIX_CLK_CG_POS                          (20U)
#define DVP2AXI_REG_DVP_PIX_CLK_CG_LEN                          (1U)
#define DVP2AXI_REG_DVP_PIX_CLK_CG_MSK                          (((1U<<DVP2AXI_REG_DVP_PIX_CLK_CG_LEN)-1)<<DVP2AXI_REG_DVP_PIX_CLK_CG_POS)
#define DVP2AXI_REG_DVP_PIX_CLK_CG_UMSK                         (~(((1U<<DVP2AXI_REG_DVP_PIX_CLK_CG_LEN)-1)<<DVP2AXI_REG_DVP_PIX_CLK_CG_POS))
#define DVP2AXI_REG_V_SUBSAMPLE_EN                              DVP2AXI_REG_V_SUBSAMPLE_EN
#define DVP2AXI_REG_V_SUBSAMPLE_EN_POS                          (22U)
#define DVP2AXI_REG_V_SUBSAMPLE_EN_LEN                          (1U)
#define DVP2AXI_REG_V_SUBSAMPLE_EN_MSK                          (((1U<<DVP2AXI_REG_V_SUBSAMPLE_EN_LEN)-1)<<DVP2AXI_REG_V_SUBSAMPLE_EN_POS)
#define DVP2AXI_REG_V_SUBSAMPLE_EN_UMSK                         (~(((1U<<DVP2AXI_REG_V_SUBSAMPLE_EN_LEN)-1)<<DVP2AXI_REG_V_SUBSAMPLE_EN_POS))
#define DVP2AXI_REG_V_SUBSAMPLE_POL                             DVP2AXI_REG_V_SUBSAMPLE_POL
#define DVP2AXI_REG_V_SUBSAMPLE_POL_POS                         (23U)
#define DVP2AXI_REG_V_SUBSAMPLE_POL_LEN                         (1U)
#define DVP2AXI_REG_V_SUBSAMPLE_POL_MSK                         (((1U<<DVP2AXI_REG_V_SUBSAMPLE_POL_LEN)-1)<<DVP2AXI_REG_V_SUBSAMPLE_POL_POS)
#define DVP2AXI_REG_V_SUBSAMPLE_POL_UMSK                        (~(((1U<<DVP2AXI_REG_V_SUBSAMPLE_POL_LEN)-1)<<DVP2AXI_REG_V_SUBSAMPLE_POL_POS))
#define DVP2AXI_REG_DVP_WAIT_CYCLE                              DVP2AXI_REG_DVP_WAIT_CYCLE
#define DVP2AXI_REG_DVP_WAIT_CYCLE_POS                          (24U)
#define DVP2AXI_REG_DVP_WAIT_CYCLE_LEN                          (8U)
#define DVP2AXI_REG_DVP_WAIT_CYCLE_MSK                          (((1U<<DVP2AXI_REG_DVP_WAIT_CYCLE_LEN)-1)<<DVP2AXI_REG_DVP_WAIT_CYCLE_POS)
#define DVP2AXI_REG_DVP_WAIT_CYCLE_UMSK                         (~(((1U<<DVP2AXI_REG_DVP_WAIT_CYCLE_LEN)-1)<<DVP2AXI_REG_DVP_WAIT_CYCLE_POS))

/* 0x4 : dvp2axi_addr_start */
#define DVP2AXI_ADDR_START_OFFSET                               (0x4)
#define DVP2AXI_REG_ADDR_START                                  DVP2AXI_REG_ADDR_START
#define DVP2AXI_REG_ADDR_START_POS                              (0U)
#define DVP2AXI_REG_ADDR_START_LEN                              (32U)
#define DVP2AXI_REG_ADDR_START_MSK                              (((1U<<DVP2AXI_REG_ADDR_START_LEN)-1)<<DVP2AXI_REG_ADDR_START_POS)
#define DVP2AXI_REG_ADDR_START_UMSK                             (~(((1U<<DVP2AXI_REG_ADDR_START_LEN)-1)<<DVP2AXI_REG_ADDR_START_POS))

/* 0x8 : dvp2axi_mem_bcnt */
#define DVP2AXI_MEM_BCNT_OFFSET                                 (0x8)
#define DVP2AXI_REG_MEM_BURST_CNT                               DVP2AXI_REG_MEM_BURST_CNT
#define DVP2AXI_REG_MEM_BURST_CNT_POS                           (0U)
#define DVP2AXI_REG_MEM_BURST_CNT_LEN                           (32U)
#define DVP2AXI_REG_MEM_BURST_CNT_MSK                           (((1U<<DVP2AXI_REG_MEM_BURST_CNT_LEN)-1)<<DVP2AXI_REG_MEM_BURST_CNT_POS)
#define DVP2AXI_REG_MEM_BURST_CNT_UMSK                          (~(((1U<<DVP2AXI_REG_MEM_BURST_CNT_LEN)-1)<<DVP2AXI_REG_MEM_BURST_CNT_POS))

/* 0xC : dvp_status_and_error */
#define DVP2AXI_DVP_STATUS_AND_ERROR_OFFSET                     (0xC)
#define DVP2AXI_REG_FRAME_CNT_TRGR_INT                          DVP2AXI_REG_FRAME_CNT_TRGR_INT
#define DVP2AXI_REG_FRAME_CNT_TRGR_INT_POS                      (0U)
#define DVP2AXI_REG_FRAME_CNT_TRGR_INT_LEN                      (5U)
#define DVP2AXI_REG_FRAME_CNT_TRGR_INT_MSK                      (((1U<<DVP2AXI_REG_FRAME_CNT_TRGR_INT_LEN)-1)<<DVP2AXI_REG_FRAME_CNT_TRGR_INT_POS)
#define DVP2AXI_REG_FRAME_CNT_TRGR_INT_UMSK                     (~(((1U<<DVP2AXI_REG_FRAME_CNT_TRGR_INT_LEN)-1)<<DVP2AXI_REG_FRAME_CNT_TRGR_INT_POS))
#define DVP2AXI_REG_INT_HCNT_EN                                 DVP2AXI_REG_INT_HCNT_EN
#define DVP2AXI_REG_INT_HCNT_EN_POS                             (6U)
#define DVP2AXI_REG_INT_HCNT_EN_LEN                             (1U)
#define DVP2AXI_REG_INT_HCNT_EN_MSK                             (((1U<<DVP2AXI_REG_INT_HCNT_EN_LEN)-1)<<DVP2AXI_REG_INT_HCNT_EN_POS)
#define DVP2AXI_REG_INT_HCNT_EN_UMSK                            (~(((1U<<DVP2AXI_REG_INT_HCNT_EN_LEN)-1)<<DVP2AXI_REG_INT_HCNT_EN_POS))
#define DVP2AXI_REG_INT_VCNT_EN                                 DVP2AXI_REG_INT_VCNT_EN
#define DVP2AXI_REG_INT_VCNT_EN_POS                             (7U)
#define DVP2AXI_REG_INT_VCNT_EN_LEN                             (1U)
#define DVP2AXI_REG_INT_VCNT_EN_MSK                             (((1U<<DVP2AXI_REG_INT_VCNT_EN_LEN)-1)<<DVP2AXI_REG_INT_VCNT_EN_POS)
#define DVP2AXI_REG_INT_VCNT_EN_UMSK                            (~(((1U<<DVP2AXI_REG_INT_VCNT_EN_LEN)-1)<<DVP2AXI_REG_INT_VCNT_EN_POS))
#define DVP2AXI_REG_INT_NORMAL_EN                               DVP2AXI_REG_INT_NORMAL_EN
#define DVP2AXI_REG_INT_NORMAL_EN_POS                           (8U)
#define DVP2AXI_REG_INT_NORMAL_EN_LEN                           (1U)
#define DVP2AXI_REG_INT_NORMAL_EN_MSK                           (((1U<<DVP2AXI_REG_INT_NORMAL_EN_LEN)-1)<<DVP2AXI_REG_INT_NORMAL_EN_POS)
#define DVP2AXI_REG_INT_NORMAL_EN_UMSK                          (~(((1U<<DVP2AXI_REG_INT_NORMAL_EN_LEN)-1)<<DVP2AXI_REG_INT_NORMAL_EN_POS))
#define DVP2AXI_REG_INT_MEM_EN                                  DVP2AXI_REG_INT_MEM_EN
#define DVP2AXI_REG_INT_MEM_EN_POS                              (9U)
#define DVP2AXI_REG_INT_MEM_EN_LEN                              (1U)
#define DVP2AXI_REG_INT_MEM_EN_MSK                              (((1U<<DVP2AXI_REG_INT_MEM_EN_LEN)-1)<<DVP2AXI_REG_INT_MEM_EN_POS)
#define DVP2AXI_REG_INT_MEM_EN_UMSK                             (~(((1U<<DVP2AXI_REG_INT_MEM_EN_LEN)-1)<<DVP2AXI_REG_INT_MEM_EN_POS))
#define DVP2AXI_REG_INT_FRAME_EN                                DVP2AXI_REG_INT_FRAME_EN
#define DVP2AXI_REG_INT_FRAME_EN_POS                            (10U)
#define DVP2AXI_REG_INT_FRAME_EN_LEN                            (1U)
#define DVP2AXI_REG_INT_FRAME_EN_MSK                            (((1U<<DVP2AXI_REG_INT_FRAME_EN_LEN)-1)<<DVP2AXI_REG_INT_FRAME_EN_POS)
#define DVP2AXI_REG_INT_FRAME_EN_UMSK                           (~(((1U<<DVP2AXI_REG_INT_FRAME_EN_LEN)-1)<<DVP2AXI_REG_INT_FRAME_EN_POS))
#define DVP2AXI_REG_INT_FIFO_EN                                 DVP2AXI_REG_INT_FIFO_EN
#define DVP2AXI_REG_INT_FIFO_EN_POS                             (11U)
#define DVP2AXI_REG_INT_FIFO_EN_LEN                             (1U)
#define DVP2AXI_REG_INT_FIFO_EN_MSK                             (((1U<<DVP2AXI_REG_INT_FIFO_EN_LEN)-1)<<DVP2AXI_REG_INT_FIFO_EN_POS)
#define DVP2AXI_REG_INT_FIFO_EN_UMSK                            (~(((1U<<DVP2AXI_REG_INT_FIFO_EN_LEN)-1)<<DVP2AXI_REG_INT_FIFO_EN_POS))
#define DVP2AXI_STS_NORMAL_INT                                  DVP2AXI_STS_NORMAL_INT
#define DVP2AXI_STS_NORMAL_INT_POS                              (12U)
#define DVP2AXI_STS_NORMAL_INT_LEN                              (1U)
#define DVP2AXI_STS_NORMAL_INT_MSK                              (((1U<<DVP2AXI_STS_NORMAL_INT_LEN)-1)<<DVP2AXI_STS_NORMAL_INT_POS)
#define DVP2AXI_STS_NORMAL_INT_UMSK                             (~(((1U<<DVP2AXI_STS_NORMAL_INT_LEN)-1)<<DVP2AXI_STS_NORMAL_INT_POS))
#define DVP2AXI_STS_MEM_INT                                     DVP2AXI_STS_MEM_INT
#define DVP2AXI_STS_MEM_INT_POS                                 (13U)
#define DVP2AXI_STS_MEM_INT_LEN                                 (1U)
#define DVP2AXI_STS_MEM_INT_MSK                                 (((1U<<DVP2AXI_STS_MEM_INT_LEN)-1)<<DVP2AXI_STS_MEM_INT_POS)
#define DVP2AXI_STS_MEM_INT_UMSK                                (~(((1U<<DVP2AXI_STS_MEM_INT_LEN)-1)<<DVP2AXI_STS_MEM_INT_POS))
#define DVP2AXI_STS_FRAME_INT                                   DVP2AXI_STS_FRAME_INT
#define DVP2AXI_STS_FRAME_INT_POS                               (14U)
#define DVP2AXI_STS_FRAME_INT_LEN                               (1U)
#define DVP2AXI_STS_FRAME_INT_MSK                               (((1U<<DVP2AXI_STS_FRAME_INT_LEN)-1)<<DVP2AXI_STS_FRAME_INT_POS)
#define DVP2AXI_STS_FRAME_INT_UMSK                              (~(((1U<<DVP2AXI_STS_FRAME_INT_LEN)-1)<<DVP2AXI_STS_FRAME_INT_POS))
#define DVP2AXI_STS_FIFO_INT                                    DVP2AXI_STS_FIFO_INT
#define DVP2AXI_STS_FIFO_INT_POS                                (15U)
#define DVP2AXI_STS_FIFO_INT_LEN                                (1U)
#define DVP2AXI_STS_FIFO_INT_MSK                                (((1U<<DVP2AXI_STS_FIFO_INT_LEN)-1)<<DVP2AXI_STS_FIFO_INT_POS)
#define DVP2AXI_STS_FIFO_INT_UMSK                               (~(((1U<<DVP2AXI_STS_FIFO_INT_LEN)-1)<<DVP2AXI_STS_FIFO_INT_POS))
#define DVP2AXI_FRAME_VALID_CNT                                 DVP2AXI_FRAME_VALID_CNT
#define DVP2AXI_FRAME_VALID_CNT_POS                             (16U)
#define DVP2AXI_FRAME_VALID_CNT_LEN                             (5U)
#define DVP2AXI_FRAME_VALID_CNT_MSK                             (((1U<<DVP2AXI_FRAME_VALID_CNT_LEN)-1)<<DVP2AXI_FRAME_VALID_CNT_POS)
#define DVP2AXI_FRAME_VALID_CNT_UMSK                            (~(((1U<<DVP2AXI_FRAME_VALID_CNT_LEN)-1)<<DVP2AXI_FRAME_VALID_CNT_POS))
#define DVP2AXI_STS_HCNT_INT                                    DVP2AXI_STS_HCNT_INT
#define DVP2AXI_STS_HCNT_INT_POS                                (21U)
#define DVP2AXI_STS_HCNT_INT_LEN                                (1U)
#define DVP2AXI_STS_HCNT_INT_MSK                                (((1U<<DVP2AXI_STS_HCNT_INT_LEN)-1)<<DVP2AXI_STS_HCNT_INT_POS)
#define DVP2AXI_STS_HCNT_INT_UMSK                               (~(((1U<<DVP2AXI_STS_HCNT_INT_LEN)-1)<<DVP2AXI_STS_HCNT_INT_POS))
#define DVP2AXI_STS_VCNT_INT                                    DVP2AXI_STS_VCNT_INT
#define DVP2AXI_STS_VCNT_INT_POS                                (22U)
#define DVP2AXI_STS_VCNT_INT_LEN                                (1U)
#define DVP2AXI_STS_VCNT_INT_MSK                                (((1U<<DVP2AXI_STS_VCNT_INT_LEN)-1)<<DVP2AXI_STS_VCNT_INT_POS)
#define DVP2AXI_STS_VCNT_INT_UMSK                               (~(((1U<<DVP2AXI_STS_VCNT_INT_LEN)-1)<<DVP2AXI_STS_VCNT_INT_POS))
#define DVP2AXI_ST_BUS_IDLE                                     DVP2AXI_ST_BUS_IDLE
#define DVP2AXI_ST_BUS_IDLE_POS                                 (24U)
#define DVP2AXI_ST_BUS_IDLE_LEN                                 (1U)
#define DVP2AXI_ST_BUS_IDLE_MSK                                 (((1U<<DVP2AXI_ST_BUS_IDLE_LEN)-1)<<DVP2AXI_ST_BUS_IDLE_POS)
#define DVP2AXI_ST_BUS_IDLE_UMSK                                (~(((1U<<DVP2AXI_ST_BUS_IDLE_LEN)-1)<<DVP2AXI_ST_BUS_IDLE_POS))
#define DVP2AXI_ST_BUS_FUNC                                     DVP2AXI_ST_BUS_FUNC
#define DVP2AXI_ST_BUS_FUNC_POS                                 (25U)
#define DVP2AXI_ST_BUS_FUNC_LEN                                 (1U)
#define DVP2AXI_ST_BUS_FUNC_MSK                                 (((1U<<DVP2AXI_ST_BUS_FUNC_LEN)-1)<<DVP2AXI_ST_BUS_FUNC_POS)
#define DVP2AXI_ST_BUS_FUNC_UMSK                                (~(((1U<<DVP2AXI_ST_BUS_FUNC_LEN)-1)<<DVP2AXI_ST_BUS_FUNC_POS))
#define DVP2AXI_ST_BUS_WAIT                                     DVP2AXI_ST_BUS_WAIT
#define DVP2AXI_ST_BUS_WAIT_POS                                 (26U)
#define DVP2AXI_ST_BUS_WAIT_LEN                                 (1U)
#define DVP2AXI_ST_BUS_WAIT_MSK                                 (((1U<<DVP2AXI_ST_BUS_WAIT_LEN)-1)<<DVP2AXI_ST_BUS_WAIT_POS)
#define DVP2AXI_ST_BUS_WAIT_UMSK                                (~(((1U<<DVP2AXI_ST_BUS_WAIT_LEN)-1)<<DVP2AXI_ST_BUS_WAIT_POS))
#define DVP2AXI_ST_BUS_FLSH                                     DVP2AXI_ST_BUS_FLSH
#define DVP2AXI_ST_BUS_FLSH_POS                                 (27U)
#define DVP2AXI_ST_BUS_FLSH_LEN                                 (1U)
#define DVP2AXI_ST_BUS_FLSH_MSK                                 (((1U<<DVP2AXI_ST_BUS_FLSH_LEN)-1)<<DVP2AXI_ST_BUS_FLSH_POS)
#define DVP2AXI_ST_BUS_FLSH_UMSK                                (~(((1U<<DVP2AXI_ST_BUS_FLSH_LEN)-1)<<DVP2AXI_ST_BUS_FLSH_POS))
#define DVP2AXI_AXI_IDLE                                        DVP2AXI_AXI_IDLE
#define DVP2AXI_AXI_IDLE_POS                                    (28U)
#define DVP2AXI_AXI_IDLE_LEN                                    (1U)
#define DVP2AXI_AXI_IDLE_MSK                                    (((1U<<DVP2AXI_AXI_IDLE_LEN)-1)<<DVP2AXI_AXI_IDLE_POS)
#define DVP2AXI_AXI_IDLE_UMSK                                   (~(((1U<<DVP2AXI_AXI_IDLE_LEN)-1)<<DVP2AXI_AXI_IDLE_POS))
#define DVP2AXI_ST_DVP_IDLE                                     DVP2AXI_ST_DVP_IDLE
#define DVP2AXI_ST_DVP_IDLE_POS                                 (29U)
#define DVP2AXI_ST_DVP_IDLE_LEN                                 (1U)
#define DVP2AXI_ST_DVP_IDLE_MSK                                 (((1U<<DVP2AXI_ST_DVP_IDLE_LEN)-1)<<DVP2AXI_ST_DVP_IDLE_POS)
#define DVP2AXI_ST_DVP_IDLE_UMSK                                (~(((1U<<DVP2AXI_ST_DVP_IDLE_LEN)-1)<<DVP2AXI_ST_DVP_IDLE_POS))

/* 0x10 : dvp2axi_frame_bcnt */
#define DVP2AXI_FRAME_BCNT_OFFSET                               (0x10)
#define DVP2AXI_REG_FRAME_BYTE_CNT                              DVP2AXI_REG_FRAME_BYTE_CNT
#define DVP2AXI_REG_FRAME_BYTE_CNT_POS                          (0U)
#define DVP2AXI_REG_FRAME_BYTE_CNT_LEN                          (32U)
#define DVP2AXI_REG_FRAME_BYTE_CNT_MSK                          (((1U<<DVP2AXI_REG_FRAME_BYTE_CNT_LEN)-1)<<DVP2AXI_REG_FRAME_BYTE_CNT_POS)
#define DVP2AXI_REG_FRAME_BYTE_CNT_UMSK                         (~(((1U<<DVP2AXI_REG_FRAME_BYTE_CNT_LEN)-1)<<DVP2AXI_REG_FRAME_BYTE_CNT_POS))

/* 0x14 : dvp_frame_fifo_pop */
#define DVP2AXI_DVP_FRAME_FIFO_POP_OFFSET                       (0x14)
#define DVP2AXI_RFIFO_POP                                       DVP2AXI_RFIFO_POP
#define DVP2AXI_RFIFO_POP_POS                                   (0U)
#define DVP2AXI_RFIFO_POP_LEN                                   (1U)
#define DVP2AXI_RFIFO_POP_MSK                                   (((1U<<DVP2AXI_RFIFO_POP_LEN)-1)<<DVP2AXI_RFIFO_POP_POS)
#define DVP2AXI_RFIFO_POP_UMSK                                  (~(((1U<<DVP2AXI_RFIFO_POP_LEN)-1)<<DVP2AXI_RFIFO_POP_POS))
#define DVP2AXI_REG_INT_NORMAL_CLR                              DVP2AXI_REG_INT_NORMAL_CLR
#define DVP2AXI_REG_INT_NORMAL_CLR_POS                          (4U)
#define DVP2AXI_REG_INT_NORMAL_CLR_LEN                          (1U)
#define DVP2AXI_REG_INT_NORMAL_CLR_MSK                          (((1U<<DVP2AXI_REG_INT_NORMAL_CLR_LEN)-1)<<DVP2AXI_REG_INT_NORMAL_CLR_POS)
#define DVP2AXI_REG_INT_NORMAL_CLR_UMSK                         (~(((1U<<DVP2AXI_REG_INT_NORMAL_CLR_LEN)-1)<<DVP2AXI_REG_INT_NORMAL_CLR_POS))
#define DVP2AXI_REG_INT_MEM_CLR                                 DVP2AXI_REG_INT_MEM_CLR
#define DVP2AXI_REG_INT_MEM_CLR_POS                             (5U)
#define DVP2AXI_REG_INT_MEM_CLR_LEN                             (1U)
#define DVP2AXI_REG_INT_MEM_CLR_MSK                             (((1U<<DVP2AXI_REG_INT_MEM_CLR_LEN)-1)<<DVP2AXI_REG_INT_MEM_CLR_POS)
#define DVP2AXI_REG_INT_MEM_CLR_UMSK                            (~(((1U<<DVP2AXI_REG_INT_MEM_CLR_LEN)-1)<<DVP2AXI_REG_INT_MEM_CLR_POS))
#define DVP2AXI_REG_INT_FRAME_CLR                               DVP2AXI_REG_INT_FRAME_CLR
#define DVP2AXI_REG_INT_FRAME_CLR_POS                           (6U)
#define DVP2AXI_REG_INT_FRAME_CLR_LEN                           (1U)
#define DVP2AXI_REG_INT_FRAME_CLR_MSK                           (((1U<<DVP2AXI_REG_INT_FRAME_CLR_LEN)-1)<<DVP2AXI_REG_INT_FRAME_CLR_POS)
#define DVP2AXI_REG_INT_FRAME_CLR_UMSK                          (~(((1U<<DVP2AXI_REG_INT_FRAME_CLR_LEN)-1)<<DVP2AXI_REG_INT_FRAME_CLR_POS))
#define DVP2AXI_REG_INT_FIFO_CLR                                DVP2AXI_REG_INT_FIFO_CLR
#define DVP2AXI_REG_INT_FIFO_CLR_POS                            (7U)
#define DVP2AXI_REG_INT_FIFO_CLR_LEN                            (1U)
#define DVP2AXI_REG_INT_FIFO_CLR_MSK                            (((1U<<DVP2AXI_REG_INT_FIFO_CLR_LEN)-1)<<DVP2AXI_REG_INT_FIFO_CLR_POS)
#define DVP2AXI_REG_INT_FIFO_CLR_UMSK                           (~(((1U<<DVP2AXI_REG_INT_FIFO_CLR_LEN)-1)<<DVP2AXI_REG_INT_FIFO_CLR_POS))
#define DVP2AXI_REG_INT_HCNT_CLR                                DVP2AXI_REG_INT_HCNT_CLR
#define DVP2AXI_REG_INT_HCNT_CLR_POS                            (8U)
#define DVP2AXI_REG_INT_HCNT_CLR_LEN                            (1U)
#define DVP2AXI_REG_INT_HCNT_CLR_MSK                            (((1U<<DVP2AXI_REG_INT_HCNT_CLR_LEN)-1)<<DVP2AXI_REG_INT_HCNT_CLR_POS)
#define DVP2AXI_REG_INT_HCNT_CLR_UMSK                           (~(((1U<<DVP2AXI_REG_INT_HCNT_CLR_LEN)-1)<<DVP2AXI_REG_INT_HCNT_CLR_POS))
#define DVP2AXI_REG_INT_VCNT_CLR                                DVP2AXI_REG_INT_VCNT_CLR
#define DVP2AXI_REG_INT_VCNT_CLR_POS                            (9U)
#define DVP2AXI_REG_INT_VCNT_CLR_LEN                            (1U)
#define DVP2AXI_REG_INT_VCNT_CLR_MSK                            (((1U<<DVP2AXI_REG_INT_VCNT_CLR_LEN)-1)<<DVP2AXI_REG_INT_VCNT_CLR_POS)
#define DVP2AXI_REG_INT_VCNT_CLR_UMSK                           (~(((1U<<DVP2AXI_REG_INT_VCNT_CLR_LEN)-1)<<DVP2AXI_REG_INT_VCNT_CLR_POS))

/* 0x18 : dvp2axi_frame_vld */
#define DVP2AXI_FRAME_VLD_OFFSET                                (0x18)
#define DVP2AXI_REG_FRAME_N_VLD                                 DVP2AXI_REG_FRAME_N_VLD
#define DVP2AXI_REG_FRAME_N_VLD_POS                             (0U)
#define DVP2AXI_REG_FRAME_N_VLD_LEN                             (32U)
#define DVP2AXI_REG_FRAME_N_VLD_MSK                             (((1U<<DVP2AXI_REG_FRAME_N_VLD_LEN)-1)<<DVP2AXI_REG_FRAME_N_VLD_POS)
#define DVP2AXI_REG_FRAME_N_VLD_UMSK                            (~(((1U<<DVP2AXI_REG_FRAME_N_VLD_LEN)-1)<<DVP2AXI_REG_FRAME_N_VLD_POS))

/* 0x1C : dvp2axi_frame_period */
#define DVP2AXI_FRAME_PERIOD_OFFSET                             (0x1C)
#define DVP2AXI_REG_FRAME_PERIOD                                DVP2AXI_REG_FRAME_PERIOD
#define DVP2AXI_REG_FRAME_PERIOD_POS                            (0U)
#define DVP2AXI_REG_FRAME_PERIOD_LEN                            (5U)
#define DVP2AXI_REG_FRAME_PERIOD_MSK                            (((1U<<DVP2AXI_REG_FRAME_PERIOD_LEN)-1)<<DVP2AXI_REG_FRAME_PERIOD_POS)
#define DVP2AXI_REG_FRAME_PERIOD_UMSK                           (~(((1U<<DVP2AXI_REG_FRAME_PERIOD_LEN)-1)<<DVP2AXI_REG_FRAME_PERIOD_POS))

/* 0x20 : dvp2axi_misc */
#define DVP2AXI_MISC_OFFSET                                     (0x20)
#define DVP2AXI_REG_ALPHA                                       DVP2AXI_REG_ALPHA
#define DVP2AXI_REG_ALPHA_POS                                   (0U)
#define DVP2AXI_REG_ALPHA_LEN                                   (8U)
#define DVP2AXI_REG_ALPHA_MSK                                   (((1U<<DVP2AXI_REG_ALPHA_LEN)-1)<<DVP2AXI_REG_ALPHA_POS)
#define DVP2AXI_REG_ALPHA_UMSK                                  (~(((1U<<DVP2AXI_REG_ALPHA_LEN)-1)<<DVP2AXI_REG_ALPHA_POS))
#define DVP2AXI_REG_FORMAT_565                                  DVP2AXI_REG_FORMAT_565
#define DVP2AXI_REG_FORMAT_565_POS                              (8U)
#define DVP2AXI_REG_FORMAT_565_LEN                              (3U)
#define DVP2AXI_REG_FORMAT_565_MSK                              (((1U<<DVP2AXI_REG_FORMAT_565_LEN)-1)<<DVP2AXI_REG_FORMAT_565_POS)
#define DVP2AXI_REG_FORMAT_565_UMSK                             (~(((1U<<DVP2AXI_REG_FORMAT_565_LEN)-1)<<DVP2AXI_REG_FORMAT_565_POS))

/* 0x30 : dvp2axi_hsync_crop */
#define DVP2AXI_HSYNC_CROP_OFFSET                               (0x30)
#define DVP2AXI_REG_HSYNC_ACT_END                               DVP2AXI_REG_HSYNC_ACT_END
#define DVP2AXI_REG_HSYNC_ACT_END_POS                           (0U)
#define DVP2AXI_REG_HSYNC_ACT_END_LEN                           (16U)
#define DVP2AXI_REG_HSYNC_ACT_END_MSK                           (((1U<<DVP2AXI_REG_HSYNC_ACT_END_LEN)-1)<<DVP2AXI_REG_HSYNC_ACT_END_POS)
#define DVP2AXI_REG_HSYNC_ACT_END_UMSK                          (~(((1U<<DVP2AXI_REG_HSYNC_ACT_END_LEN)-1)<<DVP2AXI_REG_HSYNC_ACT_END_POS))
#define DVP2AXI_REG_HSYNC_ACT_START                             DVP2AXI_REG_HSYNC_ACT_START
#define DVP2AXI_REG_HSYNC_ACT_START_POS                         (16U)
#define DVP2AXI_REG_HSYNC_ACT_START_LEN                         (16U)
#define DVP2AXI_REG_HSYNC_ACT_START_MSK                         (((1U<<DVP2AXI_REG_HSYNC_ACT_START_LEN)-1)<<DVP2AXI_REG_HSYNC_ACT_START_POS)
#define DVP2AXI_REG_HSYNC_ACT_START_UMSK                        (~(((1U<<DVP2AXI_REG_HSYNC_ACT_START_LEN)-1)<<DVP2AXI_REG_HSYNC_ACT_START_POS))

/* 0x34 : dvp2axi_vsync_crop */
#define DVP2AXI_VSYNC_CROP_OFFSET                               (0x34)
#define DVP2AXI_REG_VSYNC_ACT_END                               DVP2AXI_REG_VSYNC_ACT_END
#define DVP2AXI_REG_VSYNC_ACT_END_POS                           (0U)
#define DVP2AXI_REG_VSYNC_ACT_END_LEN                           (16U)
#define DVP2AXI_REG_VSYNC_ACT_END_MSK                           (((1U<<DVP2AXI_REG_VSYNC_ACT_END_LEN)-1)<<DVP2AXI_REG_VSYNC_ACT_END_POS)
#define DVP2AXI_REG_VSYNC_ACT_END_UMSK                          (~(((1U<<DVP2AXI_REG_VSYNC_ACT_END_LEN)-1)<<DVP2AXI_REG_VSYNC_ACT_END_POS))
#define DVP2AXI_REG_VSYNC_ACT_START                             DVP2AXI_REG_VSYNC_ACT_START
#define DVP2AXI_REG_VSYNC_ACT_START_POS                         (16U)
#define DVP2AXI_REG_VSYNC_ACT_START_LEN                         (16U)
#define DVP2AXI_REG_VSYNC_ACT_START_MSK                         (((1U<<DVP2AXI_REG_VSYNC_ACT_START_LEN)-1)<<DVP2AXI_REG_VSYNC_ACT_START_POS)
#define DVP2AXI_REG_VSYNC_ACT_START_UMSK                        (~(((1U<<DVP2AXI_REG_VSYNC_ACT_START_LEN)-1)<<DVP2AXI_REG_VSYNC_ACT_START_POS))

/* 0x38 : dvp2axi_fram_exm */
#define DVP2AXI_FRAM_EXM_OFFSET                                 (0x38)
#define DVP2AXI_REG_TOTAL_HCNT                                  DVP2AXI_REG_TOTAL_HCNT
#define DVP2AXI_REG_TOTAL_HCNT_POS                              (0U)
#define DVP2AXI_REG_TOTAL_HCNT_LEN                              (16U)
#define DVP2AXI_REG_TOTAL_HCNT_MSK                              (((1U<<DVP2AXI_REG_TOTAL_HCNT_LEN)-1)<<DVP2AXI_REG_TOTAL_HCNT_POS)
#define DVP2AXI_REG_TOTAL_HCNT_UMSK                             (~(((1U<<DVP2AXI_REG_TOTAL_HCNT_LEN)-1)<<DVP2AXI_REG_TOTAL_HCNT_POS))
#define DVP2AXI_REG_TOTAL_VCNT                                  DVP2AXI_REG_TOTAL_VCNT
#define DVP2AXI_REG_TOTAL_VCNT_POS                              (16U)
#define DVP2AXI_REG_TOTAL_VCNT_LEN                              (16U)
#define DVP2AXI_REG_TOTAL_VCNT_MSK                              (((1U<<DVP2AXI_REG_TOTAL_VCNT_LEN)-1)<<DVP2AXI_REG_TOTAL_VCNT_POS)
#define DVP2AXI_REG_TOTAL_VCNT_UMSK                             (~(((1U<<DVP2AXI_REG_TOTAL_VCNT_LEN)-1)<<DVP2AXI_REG_TOTAL_VCNT_POS))

/* 0x40 : frame_start_addr0 */
#define DVP2AXI_FRAME_START_ADDR0_OFFSET                        (0x40)
#define DVP2AXI_FRAME_START_ADDR_0                              DVP2AXI_FRAME_START_ADDR_0
#define DVP2AXI_FRAME_START_ADDR_0_POS                          (0U)
#define DVP2AXI_FRAME_START_ADDR_0_LEN                          (32U)
#define DVP2AXI_FRAME_START_ADDR_0_MSK                          (((1U<<DVP2AXI_FRAME_START_ADDR_0_LEN)-1)<<DVP2AXI_FRAME_START_ADDR_0_POS)
#define DVP2AXI_FRAME_START_ADDR_0_UMSK                         (~(((1U<<DVP2AXI_FRAME_START_ADDR_0_LEN)-1)<<DVP2AXI_FRAME_START_ADDR_0_POS))

/* 0x48 : frame_start_addr1 */
#define DVP2AXI_FRAME_START_ADDR1_OFFSET                        (0x48)
#define DVP2AXI_FRAME_START_ADDR_1                              DVP2AXI_FRAME_START_ADDR_1
#define DVP2AXI_FRAME_START_ADDR_1_POS                          (0U)
#define DVP2AXI_FRAME_START_ADDR_1_LEN                          (32U)
#define DVP2AXI_FRAME_START_ADDR_1_MSK                          (((1U<<DVP2AXI_FRAME_START_ADDR_1_LEN)-1)<<DVP2AXI_FRAME_START_ADDR_1_POS)
#define DVP2AXI_FRAME_START_ADDR_1_UMSK                         (~(((1U<<DVP2AXI_FRAME_START_ADDR_1_LEN)-1)<<DVP2AXI_FRAME_START_ADDR_1_POS))

/* 0x50 : frame_start_addr2 */
#define DVP2AXI_FRAME_START_ADDR2_OFFSET                        (0x50)
#define DVP2AXI_FRAME_START_ADDR_2                              DVP2AXI_FRAME_START_ADDR_2
#define DVP2AXI_FRAME_START_ADDR_2_POS                          (0U)
#define DVP2AXI_FRAME_START_ADDR_2_LEN                          (32U)
#define DVP2AXI_FRAME_START_ADDR_2_MSK                          (((1U<<DVP2AXI_FRAME_START_ADDR_2_LEN)-1)<<DVP2AXI_FRAME_START_ADDR_2_POS)
#define DVP2AXI_FRAME_START_ADDR_2_UMSK                         (~(((1U<<DVP2AXI_FRAME_START_ADDR_2_LEN)-1)<<DVP2AXI_FRAME_START_ADDR_2_POS))

/* 0x58 : frame_start_addr3 */
#define DVP2AXI_FRAME_START_ADDR3_OFFSET                        (0x58)
#define DVP2AXI_FRAME_START_ADDR_3                              DVP2AXI_FRAME_START_ADDR_3
#define DVP2AXI_FRAME_START_ADDR_3_POS                          (0U)
#define DVP2AXI_FRAME_START_ADDR_3_LEN                          (32U)
#define DVP2AXI_FRAME_START_ADDR_3_MSK                          (((1U<<DVP2AXI_FRAME_START_ADDR_3_LEN)-1)<<DVP2AXI_FRAME_START_ADDR_3_POS)
#define DVP2AXI_FRAME_START_ADDR_3_UMSK                         (~(((1U<<DVP2AXI_FRAME_START_ADDR_3_LEN)-1)<<DVP2AXI_FRAME_START_ADDR_3_POS))

/* 0xF0 : dvp_debug */
#define DVP2AXI_DVP_DEBUG_OFFSET                                (0xF0)
#define DVP2AXI_REG_DVP_DBG_EN                                  DVP2AXI_REG_DVP_DBG_EN
#define DVP2AXI_REG_DVP_DBG_EN_POS                              (0U)
#define DVP2AXI_REG_DVP_DBG_EN_LEN                              (1U)
#define DVP2AXI_REG_DVP_DBG_EN_MSK                              (((1U<<DVP2AXI_REG_DVP_DBG_EN_LEN)-1)<<DVP2AXI_REG_DVP_DBG_EN_POS)
#define DVP2AXI_REG_DVP_DBG_EN_UMSK                             (~(((1U<<DVP2AXI_REG_DVP_DBG_EN_LEN)-1)<<DVP2AXI_REG_DVP_DBG_EN_POS))
#define DVP2AXI_REG_DVP_DBG_SEL                                 DVP2AXI_REG_DVP_DBG_SEL
#define DVP2AXI_REG_DVP_DBG_SEL_POS                             (1U)
#define DVP2AXI_REG_DVP_DBG_SEL_LEN                             (3U)
#define DVP2AXI_REG_DVP_DBG_SEL_MSK                             (((1U<<DVP2AXI_REG_DVP_DBG_SEL_LEN)-1)<<DVP2AXI_REG_DVP_DBG_SEL_POS)
#define DVP2AXI_REG_DVP_DBG_SEL_UMSK                            (~(((1U<<DVP2AXI_REG_DVP_DBG_SEL_LEN)-1)<<DVP2AXI_REG_DVP_DBG_SEL_POS))

/* 0xFC : dvp_dummy_reg */
#define DVP2AXI_DVP_DUMMY_REG_OFFSET                            (0xFC)


struct  dvp2axi_reg {
    /* 0x0 : dvp2axi_configue */
    union {
        struct {
            uint32_t reg_dvp_enable                 :  1; /* [    0],        r/w,        0x0 */
            uint32_t reg_sw_mode                    :  1; /* [    1],        r/w,        0x0 */
            uint32_t reg_fram_vld_pol               :  1; /* [    2],        r/w,        0x1 */
            uint32_t reg_line_vld_pol               :  1; /* [    3],        r/w,        0x1 */
            uint32_t reg_xlen                       :  3; /* [ 6: 4],        r/w,        0x3 */
            uint32_t reserved_7                     :  1; /* [    7],       rsvd,        0x0 */
            uint32_t reg_dvp_mode                   :  3; /* [10: 8],        r/w,        0x0 */
            uint32_t reg_hw_mode_fwrap              :  1; /* [   11],        r/w,        0x1 */
            uint32_t reg_drop_en                    :  1; /* [   12],        r/w,        0x0 */
            uint32_t reg_drop_even                  :  1; /* [   13],        r/w,        0x0 */
            uint32_t reserved_14_15                 :  2; /* [15:14],       rsvd,        0x0 */
            uint32_t reg_dvp_data_mode              :  3; /* [18:16],        r/w,        0x0 */
            uint32_t reg_dvp_data_bsel              :  1; /* [   19],        r/w,        0x0 */
            uint32_t reg_dvp_pix_clk_cg             :  1; /* [   20],        r/w,        0x0 */
            uint32_t reserved_21                    :  1; /* [   21],       rsvd,        0x0 */
            uint32_t reg_v_subsample_en             :  1; /* [   22],        r/w,        0x0 */
            uint32_t reg_v_subsample_pol            :  1; /* [   23],        r/w,        0x0 */
            uint32_t reg_dvp_wait_cycle             :  8; /* [31:24],        r/w,       0x40 */
        }BF;
        uint32_t WORD;
    } dvp2axi_configue;

    /* 0x4 : dvp2axi_addr_start */
    union {
        struct {
            uint32_t reg_addr_start                 : 32; /* [31: 0],        r/w, 0x80000000 */
        }BF;
        uint32_t WORD;
    } dvp2axi_addr_start;

    /* 0x8 : dvp2axi_mem_bcnt */
    union {
        struct {
            uint32_t reg_mem_burst_cnt              : 32; /* [31: 0],        r/w,     0xc000 */
        }BF;
        uint32_t WORD;
    } dvp2axi_mem_bcnt;

    /* 0xC : dvp_status_and_error */
    union {
        struct {
            uint32_t reg_frame_cnt_trgr_int         :  5; /* [ 4: 0],        r/w,        0x0 */
            uint32_t reserved_5                     :  1; /* [    5],       rsvd,        0x0 */
            uint32_t reg_int_hcnt_en                :  1; /* [    6],        r/w,        0x0 */
            uint32_t reg_int_vcnt_en                :  1; /* [    7],        r/w,        0x0 */
            uint32_t reg_int_normal_en              :  1; /* [    8],        r/w,        0x0 */
            uint32_t reg_int_mem_en                 :  1; /* [    9],        r/w,        0x0 */
            uint32_t reg_int_frame_en               :  1; /* [   10],        r/w,        0x0 */
            uint32_t reg_int_fifo_en                :  1; /* [   11],        r/w,        0x1 */
            uint32_t sts_normal_int                 :  1; /* [   12],          r,        0x0 */
            uint32_t sts_mem_int                    :  1; /* [   13],          r,        0x0 */
            uint32_t sts_frame_int                  :  1; /* [   14],          r,        0x0 */
            uint32_t sts_fifo_int                   :  1; /* [   15],          r,        0x0 */
            uint32_t frame_valid_cnt                :  5; /* [20:16],          r,        0x0 */
            uint32_t sts_hcnt_int                   :  1; /* [   21],          r,        0x0 */
            uint32_t sts_vcnt_int                   :  1; /* [   22],          r,        0x0 */
            uint32_t reserved_23                    :  1; /* [   23],       rsvd,        0x0 */
            uint32_t st_bus_idle                    :  1; /* [   24],          r,        0x1 */
            uint32_t st_bus_func                    :  1; /* [   25],          r,        0x0 */
            uint32_t st_bus_wait                    :  1; /* [   26],          r,        0x0 */
            uint32_t st_bus_flsh                    :  1; /* [   27],          r,        0x0 */
            uint32_t axi_idle                       :  1; /* [   28],          r,        0x1 */
            uint32_t st_dvp_idle                    :  1; /* [   29],          r,        0x1 */
            uint32_t reserved_30_31                 :  2; /* [31:30],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } dvp_status_and_error;

    /* 0x10 : dvp2axi_frame_bcnt */
    union {
        struct {
            uint32_t reg_frame_byte_cnt             : 32; /* [31: 0],        r/w,     0x7e90 */
        }BF;
        uint32_t WORD;
    } dvp2axi_frame_bcnt;

    /* 0x14 : dvp_frame_fifo_pop */
    union {
        struct {
            uint32_t rfifo_pop                      :  1; /* [    0],        w1p,        0x0 */
            uint32_t reserved_1_3                   :  3; /* [ 3: 1],       rsvd,        0x0 */
            uint32_t reg_int_normal_clr             :  1; /* [    4],        w1p,        0x0 */
            uint32_t reg_int_mem_clr                :  1; /* [    5],        w1p,        0x0 */
            uint32_t reg_int_frame_clr              :  1; /* [    6],        w1p,        0x0 */
            uint32_t reg_int_fifo_clr               :  1; /* [    7],        w1p,        0x0 */
            uint32_t reg_int_hcnt_clr               :  1; /* [    8],        w1p,        0x0 */
            uint32_t reg_int_vcnt_clr               :  1; /* [    9],        w1p,        0x0 */
            uint32_t reserved_10_31                 : 22; /* [31:10],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } dvp_frame_fifo_pop;

    /* 0x18 : dvp2axi_frame_vld */
    union {
        struct {
            uint32_t reg_frame_n_vld                : 32; /* [31: 0],        r/w, 0xffffffff */
        }BF;
        uint32_t WORD;
    } dvp2axi_frame_vld;

    /* 0x1C : dvp2axi_frame_period */
    union {
        struct {
            uint32_t reg_frame_period               :  5; /* [ 4: 0],        r/w,        0x0 */
            uint32_t reserved_5_31                  : 27; /* [31: 5],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } dvp2axi_frame_period;

    /* 0x20 : dvp2axi_misc */
    union {
        struct {
            uint32_t reg_alpha                      :  8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t reg_format_565                 :  3; /* [10: 8],        r/w,        0x0 */
            uint32_t reserved_11_31                 : 21; /* [31:11],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } dvp2axi_misc;

    /* 0x24  reserved */
    uint8_t RESERVED0x24[12];

    /* 0x30 : dvp2axi_hsync_crop */
    union {
        struct {
            uint32_t reg_hsync_act_end              : 16; /* [15: 0],        r/w,     0xffff */
            uint32_t reg_hsync_act_start            : 16; /* [31:16],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } dvp2axi_hsync_crop;

    /* 0x34 : dvp2axi_vsync_crop */
    union {
        struct {
            uint32_t reg_vsync_act_end              : 16; /* [15: 0],        r/w,     0xffff */
            uint32_t reg_vsync_act_start            : 16; /* [31:16],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } dvp2axi_vsync_crop;

    /* 0x38 : dvp2axi_fram_exm */
    union {
        struct {
            uint32_t reg_total_hcnt                 : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t reg_total_vcnt                 : 16; /* [31:16],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } dvp2axi_fram_exm;

    /* 0x3c  reserved */
    uint8_t RESERVED0x3c[4];

    /* 0x40 : frame_start_addr0 */
    union {
        struct {
            uint32_t frame_start_addr_0             : 32; /* [31: 0],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } frame_start_addr0;

    /* 0x44  reserved */
    uint8_t RESERVED0x44[4];

    /* 0x48 : frame_start_addr1 */
    union {
        struct {
            uint32_t frame_start_addr_1             : 32; /* [31: 0],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } frame_start_addr1;

    /* 0x4c  reserved */
    uint8_t RESERVED0x4c[4];

    /* 0x50 : frame_start_addr2 */
    union {
        struct {
            uint32_t frame_start_addr_2             : 32; /* [31: 0],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } frame_start_addr2;

    /* 0x54  reserved */
    uint8_t RESERVED0x54[4];

    /* 0x58 : frame_start_addr3 */
    union {
        struct {
            uint32_t frame_start_addr_3             : 32; /* [31: 0],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } frame_start_addr3;

    /* 0x5c  reserved */
    uint8_t RESERVED0x5c[148];

    /* 0xF0 : dvp_debug */
    union {
        struct {
            uint32_t reg_dvp_dbg_en                 :  1; /* [    0],        r/w,        0x0 */
            uint32_t reg_dvp_dbg_sel                :  3; /* [ 3: 1],        r/w,        0x0 */
            uint32_t reserved_4_31                  : 28; /* [31: 4],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } dvp_debug;

    /* 0xf4  reserved */
    uint8_t RESERVED0xf4[8];

    /* 0xFC : dvp_dummy_reg */
    union {
        struct {
            uint32_t RESERVED_31_0                  : 32; /* [31: 0],       rsvd, 0xf0f0f0f0 */
        }BF;
        uint32_t WORD;
    } dvp_dummy_reg;

};

typedef volatile struct dvp2axi_reg dvp2axi_reg_t;


#endif  /* __DVP2AXI_REG_H__ */
