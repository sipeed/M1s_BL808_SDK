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
#ifndef  __MIPI_REG_H__
#define  __MIPI_REG_H__

#include "bl808.h"

/* 0x0 : mipi_config */
#define MIPI_CONFIG_OFFSET                                      (0x0)
#define MIPI_CR_MIPI_EN                                         MIPI_CR_MIPI_EN
#define MIPI_CR_MIPI_EN_POS                                     (0U)
#define MIPI_CR_MIPI_EN_LEN                                     (1U)
#define MIPI_CR_MIPI_EN_MSK                                     (((1U<<MIPI_CR_MIPI_EN_LEN)-1)<<MIPI_CR_MIPI_EN_POS)
#define MIPI_CR_MIPI_EN_UMSK                                    (~(((1U<<MIPI_CR_MIPI_EN_LEN)-1)<<MIPI_CR_MIPI_EN_POS))
#define MIPI_CR_LANE_NUM                                        MIPI_CR_LANE_NUM
#define MIPI_CR_LANE_NUM_POS                                    (1U)
#define MIPI_CR_LANE_NUM_LEN                                    (1U)
#define MIPI_CR_LANE_NUM_MSK                                    (((1U<<MIPI_CR_LANE_NUM_LEN)-1)<<MIPI_CR_LANE_NUM_POS)
#define MIPI_CR_LANE_NUM_UMSK                                   (~(((1U<<MIPI_CR_LANE_NUM_LEN)-1)<<MIPI_CR_LANE_NUM_POS))
#define MIPI_CR_DATA_BIT_INV                                    MIPI_CR_DATA_BIT_INV
#define MIPI_CR_DATA_BIT_INV_POS                                (4U)
#define MIPI_CR_DATA_BIT_INV_LEN                                (1U)
#define MIPI_CR_DATA_BIT_INV_MSK                                (((1U<<MIPI_CR_DATA_BIT_INV_LEN)-1)<<MIPI_CR_DATA_BIT_INV_POS)
#define MIPI_CR_DATA_BIT_INV_UMSK                               (~(((1U<<MIPI_CR_DATA_BIT_INV_LEN)-1)<<MIPI_CR_DATA_BIT_INV_POS))
#define MIPI_CR_SYNC_SP_EN                                      MIPI_CR_SYNC_SP_EN
#define MIPI_CR_SYNC_SP_EN_POS                                  (5U)
#define MIPI_CR_SYNC_SP_EN_LEN                                  (1U)
#define MIPI_CR_SYNC_SP_EN_MSK                                  (((1U<<MIPI_CR_SYNC_SP_EN_LEN)-1)<<MIPI_CR_SYNC_SP_EN_POS)
#define MIPI_CR_SYNC_SP_EN_UMSK                                 (~(((1U<<MIPI_CR_SYNC_SP_EN_LEN)-1)<<MIPI_CR_SYNC_SP_EN_POS))
#define MIPI_CR_UNPACK_EN                                       MIPI_CR_UNPACK_EN
#define MIPI_CR_UNPACK_EN_POS                                   (6U)
#define MIPI_CR_UNPACK_EN_LEN                                   (1U)
#define MIPI_CR_UNPACK_EN_MSK                                   (((1U<<MIPI_CR_UNPACK_EN_LEN)-1)<<MIPI_CR_UNPACK_EN_POS)
#define MIPI_CR_UNPACK_EN_UMSK                                  (~(((1U<<MIPI_CR_UNPACK_EN_LEN)-1)<<MIPI_CR_UNPACK_EN_POS))
#define MIPI_CR_VC_DVP0                                         MIPI_CR_VC_DVP0
#define MIPI_CR_VC_DVP0_POS                                     (12U)
#define MIPI_CR_VC_DVP0_LEN                                     (2U)
#define MIPI_CR_VC_DVP0_MSK                                     (((1U<<MIPI_CR_VC_DVP0_LEN)-1)<<MIPI_CR_VC_DVP0_POS)
#define MIPI_CR_VC_DVP0_UMSK                                    (~(((1U<<MIPI_CR_VC_DVP0_LEN)-1)<<MIPI_CR_VC_DVP0_POS))
#define MIPI_CR_VC_DVP1                                         MIPI_CR_VC_DVP1
#define MIPI_CR_VC_DVP1_POS                                     (14U)
#define MIPI_CR_VC_DVP1_LEN                                     (2U)
#define MIPI_CR_VC_DVP1_MSK                                     (((1U<<MIPI_CR_VC_DVP1_LEN)-1)<<MIPI_CR_VC_DVP1_POS)
#define MIPI_CR_VC_DVP1_UMSK                                    (~(((1U<<MIPI_CR_VC_DVP1_LEN)-1)<<MIPI_CR_VC_DVP1_POS))

/* 0x4 : mipi_int_status */
#define MIPI_INT_STATUS_OFFSET                                  (0x4)
#define MIPI_INT_STATUS                                         MIPI_INT_STATUS
#define MIPI_INT_STATUS_POS                                     (0U)
#define MIPI_INT_STATUS_LEN                                     (4U)
#define MIPI_INT_STATUS_MSK                                     (((1U<<MIPI_INT_STATUS_LEN)-1)<<MIPI_INT_STATUS_POS)
#define MIPI_INT_STATUS_UMSK                                    (~(((1U<<MIPI_INT_STATUS_LEN)-1)<<MIPI_INT_STATUS_POS))

/* 0x8 : mipi_int_mask */
#define MIPI_INT_MASK_OFFSET                                    (0x8)
#define MIPI_INT_MASK                                           MIPI_INT_MASK
#define MIPI_INT_MASK_POS                                       (0U)
#define MIPI_INT_MASK_LEN                                       (4U)
#define MIPI_INT_MASK_MSK                                       (((1U<<MIPI_INT_MASK_LEN)-1)<<MIPI_INT_MASK_POS)
#define MIPI_INT_MASK_UMSK                                      (~(((1U<<MIPI_INT_MASK_LEN)-1)<<MIPI_INT_MASK_POS))

/* 0xC : mipi_int_clear */
#define MIPI_INT_CLEAR_OFFSET                                   (0xC)
#define MIPI_INT_CLEAR                                          MIPI_INT_CLEAR
#define MIPI_INT_CLEAR_POS                                      (0U)
#define MIPI_INT_CLEAR_LEN                                      (4U)
#define MIPI_INT_CLEAR_MSK                                      (((1U<<MIPI_INT_CLEAR_LEN)-1)<<MIPI_INT_CLEAR_POS)
#define MIPI_INT_CLEAR_UMSK                                     (~(((1U<<MIPI_INT_CLEAR_LEN)-1)<<MIPI_INT_CLEAR_POS))

/* 0x20 : gnr_buf_status */
#define MIPI_GNR_BUF_STATUS_OFFSET                              (0x20)
#define MIPI_ST_GNR_FIFO_CNT                                    MIPI_ST_GNR_FIFO_CNT
#define MIPI_ST_GNR_FIFO_CNT_POS                                (0U)
#define MIPI_ST_GNR_FIFO_CNT_LEN                                (4U)
#define MIPI_ST_GNR_FIFO_CNT_MSK                                (((1U<<MIPI_ST_GNR_FIFO_CNT_LEN)-1)<<MIPI_ST_GNR_FIFO_CNT_POS)
#define MIPI_ST_GNR_FIFO_CNT_UMSK                               (~(((1U<<MIPI_ST_GNR_FIFO_CNT_LEN)-1)<<MIPI_ST_GNR_FIFO_CNT_POS))

/* 0x24 : gnr_buf_rdata */
#define MIPI_GNR_BUF_RDATA_OFFSET                               (0x24)
#define MIPI_GNR_BUF_RDATA                                      MIPI_GNR_BUF_RDATA
#define MIPI_GNR_BUF_RDATA_POS                                  (0U)
#define MIPI_GNR_BUF_RDATA_LEN                                  (32U)
#define MIPI_GNR_BUF_RDATA_MSK                                  (((1U<<MIPI_GNR_BUF_RDATA_LEN)-1)<<MIPI_GNR_BUF_RDATA_POS)
#define MIPI_GNR_BUF_RDATA_UMSK                                 (~(((1U<<MIPI_GNR_BUF_RDATA_LEN)-1)<<MIPI_GNR_BUF_RDATA_POS))

/* 0x80 : dphy_config_0 */
#define MIPI_DPHY_CONFIG_0_OFFSET                               (0x80)
#define MIPI_DL0_ENABLE                                         MIPI_DL0_ENABLE
#define MIPI_DL0_ENABLE_POS                                     (0U)
#define MIPI_DL0_ENABLE_LEN                                     (1U)
#define MIPI_DL0_ENABLE_MSK                                     (((1U<<MIPI_DL0_ENABLE_LEN)-1)<<MIPI_DL0_ENABLE_POS)
#define MIPI_DL0_ENABLE_UMSK                                    (~(((1U<<MIPI_DL0_ENABLE_LEN)-1)<<MIPI_DL0_ENABLE_POS))
#define MIPI_DL1_ENABLE                                         MIPI_DL1_ENABLE
#define MIPI_DL1_ENABLE_POS                                     (1U)
#define MIPI_DL1_ENABLE_LEN                                     (1U)
#define MIPI_DL1_ENABLE_MSK                                     (((1U<<MIPI_DL1_ENABLE_LEN)-1)<<MIPI_DL1_ENABLE_POS)
#define MIPI_DL1_ENABLE_UMSK                                    (~(((1U<<MIPI_DL1_ENABLE_LEN)-1)<<MIPI_DL1_ENABLE_POS))
#define MIPI_CL_ENABLE                                          MIPI_CL_ENABLE
#define MIPI_CL_ENABLE_POS                                      (2U)
#define MIPI_CL_ENABLE_LEN                                      (1U)
#define MIPI_CL_ENABLE_MSK                                      (((1U<<MIPI_CL_ENABLE_LEN)-1)<<MIPI_CL_ENABLE_POS)
#define MIPI_CL_ENABLE_UMSK                                     (~(((1U<<MIPI_CL_ENABLE_LEN)-1)<<MIPI_CL_ENABLE_POS))
#define MIPI_DL0_STOPSTATE                                      MIPI_DL0_STOPSTATE
#define MIPI_DL0_STOPSTATE_POS                                  (4U)
#define MIPI_DL0_STOPSTATE_LEN                                  (1U)
#define MIPI_DL0_STOPSTATE_MSK                                  (((1U<<MIPI_DL0_STOPSTATE_LEN)-1)<<MIPI_DL0_STOPSTATE_POS)
#define MIPI_DL0_STOPSTATE_UMSK                                 (~(((1U<<MIPI_DL0_STOPSTATE_LEN)-1)<<MIPI_DL0_STOPSTATE_POS))
#define MIPI_DL1_STOPSTATE                                      MIPI_DL1_STOPSTATE
#define MIPI_DL1_STOPSTATE_POS                                  (5U)
#define MIPI_DL1_STOPSTATE_LEN                                  (1U)
#define MIPI_DL1_STOPSTATE_MSK                                  (((1U<<MIPI_DL1_STOPSTATE_LEN)-1)<<MIPI_DL1_STOPSTATE_POS)
#define MIPI_DL1_STOPSTATE_UMSK                                 (~(((1U<<MIPI_DL1_STOPSTATE_LEN)-1)<<MIPI_DL1_STOPSTATE_POS))
#define MIPI_CL_STOPSTATE                                       MIPI_CL_STOPSTATE
#define MIPI_CL_STOPSTATE_POS                                   (6U)
#define MIPI_CL_STOPSTATE_LEN                                   (1U)
#define MIPI_CL_STOPSTATE_MSK                                   (((1U<<MIPI_CL_STOPSTATE_LEN)-1)<<MIPI_CL_STOPSTATE_POS)
#define MIPI_CL_STOPSTATE_UMSK                                  (~(((1U<<MIPI_CL_STOPSTATE_LEN)-1)<<MIPI_CL_STOPSTATE_POS))
#define MIPI_DL0_ULPSACTIVENOT                                  MIPI_DL0_ULPSACTIVENOT
#define MIPI_DL0_ULPSACTIVENOT_POS                              (8U)
#define MIPI_DL0_ULPSACTIVENOT_LEN                              (1U)
#define MIPI_DL0_ULPSACTIVENOT_MSK                              (((1U<<MIPI_DL0_ULPSACTIVENOT_LEN)-1)<<MIPI_DL0_ULPSACTIVENOT_POS)
#define MIPI_DL0_ULPSACTIVENOT_UMSK                             (~(((1U<<MIPI_DL0_ULPSACTIVENOT_LEN)-1)<<MIPI_DL0_ULPSACTIVENOT_POS))
#define MIPI_DL1_ULPSACTIVENOT                                  MIPI_DL1_ULPSACTIVENOT
#define MIPI_DL1_ULPSACTIVENOT_POS                              (9U)
#define MIPI_DL1_ULPSACTIVENOT_LEN                              (1U)
#define MIPI_DL1_ULPSACTIVENOT_MSK                              (((1U<<MIPI_DL1_ULPSACTIVENOT_LEN)-1)<<MIPI_DL1_ULPSACTIVENOT_POS)
#define MIPI_DL1_ULPSACTIVENOT_UMSK                             (~(((1U<<MIPI_DL1_ULPSACTIVENOT_LEN)-1)<<MIPI_DL1_ULPSACTIVENOT_POS))
#define MIPI_CL_ULPSACTIVENOT                                   MIPI_CL_ULPSACTIVENOT
#define MIPI_CL_ULPSACTIVENOT_POS                               (10U)
#define MIPI_CL_ULPSACTIVENOT_LEN                               (1U)
#define MIPI_CL_ULPSACTIVENOT_MSK                               (((1U<<MIPI_CL_ULPSACTIVENOT_LEN)-1)<<MIPI_CL_ULPSACTIVENOT_POS)
#define MIPI_CL_ULPSACTIVENOT_UMSK                              (~(((1U<<MIPI_CL_ULPSACTIVENOT_LEN)-1)<<MIPI_CL_ULPSACTIVENOT_POS))
#define MIPI_DL0_FORCERXMODE                                    MIPI_DL0_FORCERXMODE
#define MIPI_DL0_FORCERXMODE_POS                                (12U)
#define MIPI_DL0_FORCERXMODE_LEN                                (1U)
#define MIPI_DL0_FORCERXMODE_MSK                                (((1U<<MIPI_DL0_FORCERXMODE_LEN)-1)<<MIPI_DL0_FORCERXMODE_POS)
#define MIPI_DL0_FORCERXMODE_UMSK                               (~(((1U<<MIPI_DL0_FORCERXMODE_LEN)-1)<<MIPI_DL0_FORCERXMODE_POS))
#define MIPI_DL1_FORCERXMODE                                    MIPI_DL1_FORCERXMODE
#define MIPI_DL1_FORCERXMODE_POS                                (13U)
#define MIPI_DL1_FORCERXMODE_LEN                                (1U)
#define MIPI_DL1_FORCERXMODE_MSK                                (((1U<<MIPI_DL1_FORCERXMODE_LEN)-1)<<MIPI_DL1_FORCERXMODE_POS)
#define MIPI_DL1_FORCERXMODE_UMSK                               (~(((1U<<MIPI_DL1_FORCERXMODE_LEN)-1)<<MIPI_DL1_FORCERXMODE_POS))
#define MIPI_CL_RXCLKACTIVEHS                                   MIPI_CL_RXCLKACTIVEHS
#define MIPI_CL_RXCLKACTIVEHS_POS                               (14U)
#define MIPI_CL_RXCLKACTIVEHS_LEN                               (1U)
#define MIPI_CL_RXCLKACTIVEHS_MSK                               (((1U<<MIPI_CL_RXCLKACTIVEHS_LEN)-1)<<MIPI_CL_RXCLKACTIVEHS_POS)
#define MIPI_CL_RXCLKACTIVEHS_UMSK                              (~(((1U<<MIPI_CL_RXCLKACTIVEHS_LEN)-1)<<MIPI_CL_RXCLKACTIVEHS_POS))
#define MIPI_CL_RXULPSCLKNOT                                    MIPI_CL_RXULPSCLKNOT
#define MIPI_CL_RXULPSCLKNOT_POS                                (15U)
#define MIPI_CL_RXULPSCLKNOT_LEN                                (1U)
#define MIPI_CL_RXULPSCLKNOT_MSK                                (((1U<<MIPI_CL_RXULPSCLKNOT_LEN)-1)<<MIPI_CL_RXULPSCLKNOT_POS)
#define MIPI_CL_RXULPSCLKNOT_UMSK                               (~(((1U<<MIPI_CL_RXULPSCLKNOT_LEN)-1)<<MIPI_CL_RXULPSCLKNOT_POS))
#define MIPI_CSI_RESET_N                                        MIPI_CSI_RESET_N
#define MIPI_CSI_RESET_N_POS                                    (31U)
#define MIPI_CSI_RESET_N_LEN                                    (1U)
#define MIPI_CSI_RESET_N_MSK                                    (((1U<<MIPI_CSI_RESET_N_LEN)-1)<<MIPI_CSI_RESET_N_POS)
#define MIPI_CSI_RESET_N_UMSK                                   (~(((1U<<MIPI_CSI_RESET_N_LEN)-1)<<MIPI_CSI_RESET_N_POS))

/* 0x84 : dphy_config_1 */
#define MIPI_DPHY_CONFIG_1_OFFSET                               (0x84)
#define MIPI_REG_TIME_CK_SETTLE                                 MIPI_REG_TIME_CK_SETTLE
#define MIPI_REG_TIME_CK_SETTLE_POS                             (0U)
#define MIPI_REG_TIME_CK_SETTLE_LEN                             (8U)
#define MIPI_REG_TIME_CK_SETTLE_MSK                             (((1U<<MIPI_REG_TIME_CK_SETTLE_LEN)-1)<<MIPI_REG_TIME_CK_SETTLE_POS)
#define MIPI_REG_TIME_CK_SETTLE_UMSK                            (~(((1U<<MIPI_REG_TIME_CK_SETTLE_LEN)-1)<<MIPI_REG_TIME_CK_SETTLE_POS))
#define MIPI_REG_TIME_CK_TERM_EN                                MIPI_REG_TIME_CK_TERM_EN
#define MIPI_REG_TIME_CK_TERM_EN_POS                            (8U)
#define MIPI_REG_TIME_CK_TERM_EN_LEN                            (8U)
#define MIPI_REG_TIME_CK_TERM_EN_MSK                            (((1U<<MIPI_REG_TIME_CK_TERM_EN_LEN)-1)<<MIPI_REG_TIME_CK_TERM_EN_POS)
#define MIPI_REG_TIME_CK_TERM_EN_UMSK                           (~(((1U<<MIPI_REG_TIME_CK_TERM_EN_LEN)-1)<<MIPI_REG_TIME_CK_TERM_EN_POS))
#define MIPI_REG_TIME_HS_SETTLE                                 MIPI_REG_TIME_HS_SETTLE
#define MIPI_REG_TIME_HS_SETTLE_POS                             (16U)
#define MIPI_REG_TIME_HS_SETTLE_LEN                             (8U)
#define MIPI_REG_TIME_HS_SETTLE_MSK                             (((1U<<MIPI_REG_TIME_HS_SETTLE_LEN)-1)<<MIPI_REG_TIME_HS_SETTLE_POS)
#define MIPI_REG_TIME_HS_SETTLE_UMSK                            (~(((1U<<MIPI_REG_TIME_HS_SETTLE_LEN)-1)<<MIPI_REG_TIME_HS_SETTLE_POS))
#define MIPI_REG_TIME_HS_TERM_EN                                MIPI_REG_TIME_HS_TERM_EN
#define MIPI_REG_TIME_HS_TERM_EN_POS                            (24U)
#define MIPI_REG_TIME_HS_TERM_EN_LEN                            (8U)
#define MIPI_REG_TIME_HS_TERM_EN_MSK                            (((1U<<MIPI_REG_TIME_HS_TERM_EN_LEN)-1)<<MIPI_REG_TIME_HS_TERM_EN_POS)
#define MIPI_REG_TIME_HS_TERM_EN_UMSK                           (~(((1U<<MIPI_REG_TIME_HS_TERM_EN_LEN)-1)<<MIPI_REG_TIME_HS_TERM_EN_POS))

/* 0x88 : dphy_config_2 */
#define MIPI_DPHY_CONFIG_2_OFFSET                               (0x88)
#define MIPI_REG_ANA_LPRXEN_CLK                                 MIPI_REG_ANA_LPRXEN_CLK
#define MIPI_REG_ANA_LPRXEN_CLK_POS                             (0U)
#define MIPI_REG_ANA_LPRXEN_CLK_LEN                             (1U)
#define MIPI_REG_ANA_LPRXEN_CLK_MSK                             (((1U<<MIPI_REG_ANA_LPRXEN_CLK_LEN)-1)<<MIPI_REG_ANA_LPRXEN_CLK_POS)
#define MIPI_REG_ANA_LPRXEN_CLK_UMSK                            (~(((1U<<MIPI_REG_ANA_LPRXEN_CLK_LEN)-1)<<MIPI_REG_ANA_LPRXEN_CLK_POS))
#define MIPI_REG_ANA_HSRXEN_CLK                                 MIPI_REG_ANA_HSRXEN_CLK
#define MIPI_REG_ANA_HSRXEN_CLK_POS                             (1U)
#define MIPI_REG_ANA_HSRXEN_CLK_LEN                             (1U)
#define MIPI_REG_ANA_HSRXEN_CLK_MSK                             (((1U<<MIPI_REG_ANA_HSRXEN_CLK_LEN)-1)<<MIPI_REG_ANA_HSRXEN_CLK_POS)
#define MIPI_REG_ANA_HSRXEN_CLK_UMSK                            (~(((1U<<MIPI_REG_ANA_HSRXEN_CLK_LEN)-1)<<MIPI_REG_ANA_HSRXEN_CLK_POS))
#define MIPI_REG_ANA_HSRX_STOP_STATE                            MIPI_REG_ANA_HSRX_STOP_STATE
#define MIPI_REG_ANA_HSRX_STOP_STATE_POS                        (2U)
#define MIPI_REG_ANA_HSRX_STOP_STATE_LEN                        (2U)
#define MIPI_REG_ANA_HSRX_STOP_STATE_MSK                        (((1U<<MIPI_REG_ANA_HSRX_STOP_STATE_LEN)-1)<<MIPI_REG_ANA_HSRX_STOP_STATE_POS)
#define MIPI_REG_ANA_HSRX_STOP_STATE_UMSK                       (~(((1U<<MIPI_REG_ANA_HSRX_STOP_STATE_LEN)-1)<<MIPI_REG_ANA_HSRX_STOP_STATE_POS))
#define MIPI_REG_ANA_HSRX_SYNC_EN                               MIPI_REG_ANA_HSRX_SYNC_EN
#define MIPI_REG_ANA_HSRX_SYNC_EN_POS                           (4U)
#define MIPI_REG_ANA_HSRX_SYNC_EN_LEN                           (2U)
#define MIPI_REG_ANA_HSRX_SYNC_EN_MSK                           (((1U<<MIPI_REG_ANA_HSRX_SYNC_EN_LEN)-1)<<MIPI_REG_ANA_HSRX_SYNC_EN_POS)
#define MIPI_REG_ANA_HSRX_SYNC_EN_UMSK                          (~(((1U<<MIPI_REG_ANA_HSRX_SYNC_EN_LEN)-1)<<MIPI_REG_ANA_HSRX_SYNC_EN_POS))
#define MIPI_REG_ANA_LPRXEN                                     MIPI_REG_ANA_LPRXEN
#define MIPI_REG_ANA_LPRXEN_POS                                 (6U)
#define MIPI_REG_ANA_LPRXEN_LEN                                 (2U)
#define MIPI_REG_ANA_LPRXEN_MSK                                 (((1U<<MIPI_REG_ANA_LPRXEN_LEN)-1)<<MIPI_REG_ANA_LPRXEN_POS)
#define MIPI_REG_ANA_LPRXEN_UMSK                                (~(((1U<<MIPI_REG_ANA_LPRXEN_LEN)-1)<<MIPI_REG_ANA_LPRXEN_POS))
#define MIPI_REG_ANA_HSRXEN                                     MIPI_REG_ANA_HSRXEN
#define MIPI_REG_ANA_HSRXEN_POS                                 (8U)
#define MIPI_REG_ANA_HSRXEN_LEN                                 (2U)
#define MIPI_REG_ANA_HSRXEN_MSK                                 (((1U<<MIPI_REG_ANA_HSRXEN_LEN)-1)<<MIPI_REG_ANA_HSRXEN_POS)
#define MIPI_REG_ANA_HSRXEN_UMSK                                (~(((1U<<MIPI_REG_ANA_HSRXEN_LEN)-1)<<MIPI_REG_ANA_HSRXEN_POS))
#define MIPI_REG_ANA_TERM_EN                                    MIPI_REG_ANA_TERM_EN
#define MIPI_REG_ANA_TERM_EN_POS                                (10U)
#define MIPI_REG_ANA_TERM_EN_LEN                                (5U)
#define MIPI_REG_ANA_TERM_EN_MSK                                (((1U<<MIPI_REG_ANA_TERM_EN_LEN)-1)<<MIPI_REG_ANA_TERM_EN_POS)
#define MIPI_REG_ANA_TERM_EN_UMSK                               (~(((1U<<MIPI_REG_ANA_TERM_EN_LEN)-1)<<MIPI_REG_ANA_TERM_EN_POS))
#define MIPI_REG_ANA_TEST_EN                                    MIPI_REG_ANA_TEST_EN
#define MIPI_REG_ANA_TEST_EN_POS                                (15U)
#define MIPI_REG_ANA_TEST_EN_LEN                                (1U)
#define MIPI_REG_ANA_TEST_EN_MSK                                (((1U<<MIPI_REG_ANA_TEST_EN_LEN)-1)<<MIPI_REG_ANA_TEST_EN_POS)
#define MIPI_REG_ANA_TEST_EN_UMSK                               (~(((1U<<MIPI_REG_ANA_TEST_EN_LEN)-1)<<MIPI_REG_ANA_TEST_EN_POS))
#define MIPI_REG_PT_LOCK_COUNTER                                MIPI_REG_PT_LOCK_COUNTER
#define MIPI_REG_PT_LOCK_COUNTER_POS                            (16U)
#define MIPI_REG_PT_LOCK_COUNTER_LEN                            (4U)
#define MIPI_REG_PT_LOCK_COUNTER_MSK                            (((1U<<MIPI_REG_PT_LOCK_COUNTER_LEN)-1)<<MIPI_REG_PT_LOCK_COUNTER_POS)
#define MIPI_REG_PT_LOCK_COUNTER_UMSK                           (~(((1U<<MIPI_REG_PT_LOCK_COUNTER_LEN)-1)<<MIPI_REG_PT_LOCK_COUNTER_POS))
#define MIPI_REG_PT_PRBS_OR_JITT                                MIPI_REG_PT_PRBS_OR_JITT
#define MIPI_REG_PT_PRBS_OR_JITT_POS                            (20U)
#define MIPI_REG_PT_PRBS_OR_JITT_LEN                            (1U)
#define MIPI_REG_PT_PRBS_OR_JITT_MSK                            (((1U<<MIPI_REG_PT_PRBS_OR_JITT_LEN)-1)<<MIPI_REG_PT_PRBS_OR_JITT_POS)
#define MIPI_REG_PT_PRBS_OR_JITT_UMSK                           (~(((1U<<MIPI_REG_PT_PRBS_OR_JITT_LEN)-1)<<MIPI_REG_PT_PRBS_OR_JITT_POS))
#define MIPI_REG_PT_LP_MODE                                     MIPI_REG_PT_LP_MODE
#define MIPI_REG_PT_LP_MODE_POS                                 (21U)
#define MIPI_REG_PT_LP_MODE_LEN                                 (1U)
#define MIPI_REG_PT_LP_MODE_MSK                                 (((1U<<MIPI_REG_PT_LP_MODE_LEN)-1)<<MIPI_REG_PT_LP_MODE_POS)
#define MIPI_REG_PT_LP_MODE_UMSK                                (~(((1U<<MIPI_REG_PT_LP_MODE_LEN)-1)<<MIPI_REG_PT_LP_MODE_POS))
#define MIPI_REG_PT_EN                                          MIPI_REG_PT_EN
#define MIPI_REG_PT_EN_POS                                      (22U)
#define MIPI_REG_PT_EN_LEN                                      (1U)
#define MIPI_REG_PT_EN_MSK                                      (((1U<<MIPI_REG_PT_EN_LEN)-1)<<MIPI_REG_PT_EN_POS)
#define MIPI_REG_PT_EN_UMSK                                     (~(((1U<<MIPI_REG_PT_EN_LEN)-1)<<MIPI_REG_PT_EN_POS))

/* 0x8C : dphy_config_3 */
#define MIPI_DPHY_CONFIG_3_OFFSET                               (0x8C)
#define MIPI_REG_CSI_ANA_1                                      MIPI_REG_CSI_ANA_1
#define MIPI_REG_CSI_ANA_1_POS                                  (0U)
#define MIPI_REG_CSI_ANA_1_LEN                                  (16U)
#define MIPI_REG_CSI_ANA_1_MSK                                  (((1U<<MIPI_REG_CSI_ANA_1_LEN)-1)<<MIPI_REG_CSI_ANA_1_POS)
#define MIPI_REG_CSI_ANA_1_UMSK                                 (~(((1U<<MIPI_REG_CSI_ANA_1_LEN)-1)<<MIPI_REG_CSI_ANA_1_POS))
#define MIPI_REG_CSI_ANA_0                                      MIPI_REG_CSI_ANA_0
#define MIPI_REG_CSI_ANA_0_POS                                  (16U)
#define MIPI_REG_CSI_ANA_0_LEN                                  (16U)
#define MIPI_REG_CSI_ANA_0_MSK                                  (((1U<<MIPI_REG_CSI_ANA_0_LEN)-1)<<MIPI_REG_CSI_ANA_0_POS)
#define MIPI_REG_CSI_ANA_0_UMSK                                 (~(((1U<<MIPI_REG_CSI_ANA_0_LEN)-1)<<MIPI_REG_CSI_ANA_0_POS))

/* 0xFC : dummy_reg */
#define MIPI_DUMMY_REG_OFFSET                                   (0xFC)
#define MIPI_DUMMY_REG                                          MIPI_DUMMY_REG
#define MIPI_DUMMY_REG_POS                                      (0U)
#define MIPI_DUMMY_REG_LEN                                      (32U)
#define MIPI_DUMMY_REG_MSK                                      (((1U<<MIPI_DUMMY_REG_LEN)-1)<<MIPI_DUMMY_REG_POS)
#define MIPI_DUMMY_REG_UMSK                                     (~(((1U<<MIPI_DUMMY_REG_LEN)-1)<<MIPI_DUMMY_REG_POS))


struct  mipi_reg {
    /* 0x0 : mipi_config */
    union {
        struct {
            uint32_t cr_mipi_en                     :  1; /* [    0],        r/w,        0x0 */
            uint32_t cr_lane_num                    :  1; /* [    1],        r/w,        0x1 */
            uint32_t rsvd_2                         :  1; /* [    2],       rsvd,        0x0 */
            uint32_t reserved_3                     :  1; /* [    3],       rsvd,        0x0 */
            uint32_t cr_data_bit_inv                :  1; /* [    4],        r/w,        0x0 */
            uint32_t cr_sync_sp_en                  :  1; /* [    5],        r/w,        0x0 */
            uint32_t cr_unpack_en                   :  1; /* [    6],        r/w,        0x1 */
            uint32_t reserved_7_11                  :  5; /* [11: 7],       rsvd,        0x0 */
            uint32_t cr_vc_dvp0                     :  2; /* [13:12],        r/w,        0x0 */
            uint32_t cr_vc_dvp1                     :  2; /* [15:14],        r/w,        0x1 */
            uint32_t reserved_16_31                 : 16; /* [31:16],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } mipi_config;

    /* 0x4 : mipi_int_status */
    union {
        struct {
            uint32_t mipi_int_status                :  4; /* [ 3: 0],          r,        0x0 */
            uint32_t reserved_4_31                  : 28; /* [31: 4],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } mipi_int_status;

    /* 0x8 : mipi_int_mask */
    union {
        struct {
            uint32_t mipi_int_mask                  :  4; /* [ 3: 0],        r/w,        0xf */
            uint32_t reserved_4_31                  : 28; /* [31: 4],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } mipi_int_mask;

    /* 0xC : mipi_int_clear */
    union {
        struct {
            uint32_t mipi_int_clear                 :  4; /* [ 3: 0],        w1c,        0x0 */
            uint32_t reserved_4_31                  : 28; /* [31: 4],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } mipi_int_clear;

    /* 0x10  reserved */
    uint8_t RESERVED0x10[16];

    /* 0x20 : gnr_buf_status */
    union {
        struct {
            uint32_t st_gnr_fifo_cnt                :  4; /* [ 3: 0],          r,        0x0 */
            uint32_t reserved_4_31                  : 28; /* [31: 4],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } gnr_buf_status;

    /* 0x24 : gnr_buf_rdata */
    union {
        struct {
            uint32_t gnr_buf_rdata                  : 32; /* [31: 0],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } gnr_buf_rdata;

    /* 0x28  reserved */
    uint8_t RESERVED0x28[88];

    /* 0x80 : dphy_config_0 */
    union {
        struct {
            uint32_t dl0_enable                     :  1; /* [    0],        r/w,        0x0 */
            uint32_t dl1_enable                     :  1; /* [    1],        r/w,        0x0 */
            uint32_t cl_enable                      :  1; /* [    2],        r/w,        0x0 */
            uint32_t reserved_3                     :  1; /* [    3],       rsvd,        0x0 */
            uint32_t dl0_stopstate                  :  1; /* [    4],          r,        0x1 */
            uint32_t dl1_stopstate                  :  1; /* [    5],          r,        0x1 */
            uint32_t cl_stopstate                   :  1; /* [    6],          r,        0x1 */
            uint32_t reserved_7                     :  1; /* [    7],       rsvd,        0x0 */
            uint32_t dl0_ulpsactivenot              :  1; /* [    8],          r,        0x1 */
            uint32_t dl1_ulpsactivenot              :  1; /* [    9],          r,        0x1 */
            uint32_t cl_ulpsactivenot               :  1; /* [   10],          r,        0x1 */
            uint32_t reserved_11                    :  1; /* [   11],       rsvd,        0x0 */
            uint32_t dl0_forcerxmode                :  1; /* [   12],        r/w,        0x0 */
            uint32_t dl1_forcerxmode                :  1; /* [   13],        r/w,        0x0 */
            uint32_t cl_rxclkactivehs               :  1; /* [   14],          r,        0x0 */
            uint32_t cl_rxulpsclknot                :  1; /* [   15],          r,        0x1 */
            uint32_t reserved_16_30                 : 15; /* [30:16],       rsvd,        0x0 */
            uint32_t csi_reset_n                    :  1; /* [   31],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } dphy_config_0;

    /* 0x84 : dphy_config_1 */
    union {
        struct {
            uint32_t reg_time_ck_settle             :  8; /* [ 7: 0],        r/w,        0xa */
            uint32_t reg_time_ck_term_en            :  8; /* [15: 8],        r/w,        0x0 */
            uint32_t reg_time_hs_settle             :  8; /* [23:16],        r/w,       0x30 */
            uint32_t reg_time_hs_term_en            :  8; /* [31:24],        r/w,       0x18 */
        }BF;
        uint32_t WORD;
    } dphy_config_1;

    /* 0x88 : dphy_config_2 */
    union {
        struct {
            uint32_t reg_ana_lprxen_clk             :  1; /* [    0],        r/w,        0x0 */
            uint32_t reg_ana_hsrxen_clk             :  1; /* [    1],        r/w,        0x0 */
            uint32_t reg_ana_hsrx_stop_state        :  2; /* [ 3: 2],        r/w,        0x0 */
            uint32_t reg_ana_hsrx_sync_en           :  2; /* [ 5: 4],        r/w,        0x0 */
            uint32_t reg_ana_lprxen                 :  2; /* [ 7: 6],        r/w,        0x0 */
            uint32_t reg_ana_hsrxen                 :  2; /* [ 9: 8],        r/w,        0x0 */
            uint32_t reg_ana_term_en                :  5; /* [14:10],        r/w,        0x0 */
            uint32_t reg_ana_test_en                :  1; /* [   15],        r/w,        0x0 */
            uint32_t reg_pt_lock_counter            :  4; /* [19:16],        r/w,        0x0 */
            uint32_t reg_pt_prbs_or_jitt            :  1; /* [   20],        r/w,        0x0 */
            uint32_t reg_pt_lp_mode                 :  1; /* [   21],        r/w,        0x0 */
            uint32_t reg_pt_en                      :  1; /* [   22],        r/w,        0x0 */
            uint32_t reserved_23_31                 :  9; /* [31:23],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } dphy_config_2;

    /* 0x8C : dphy_config_3 */
    union {
        struct {
            uint32_t reg_csi_ana_1                  : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t reg_csi_ana_0                  : 16; /* [31:16],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } dphy_config_3;

    /* 0x90  reserved */
    uint8_t RESERVED0x90[108];

    /* 0xFC : dummy_reg */
    union {
        struct {
            uint32_t dummy_reg                      : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } dummy_reg;

};

typedef volatile struct mipi_reg mipi_reg_t;


#endif  /* __MIPI_REG_H__ */
