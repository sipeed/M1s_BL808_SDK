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
#ifndef  __EF_CTRL_REG_H__
#define  __EF_CTRL_REG_H__

#include "bl808.h"

/* 0x800 : ef_if_ctrl_0 */
#define EF_CTRL_EF_IF_CTRL_0_OFFSET                             (0x800)
#define EF_CTRL_EF_IF_0_AUTOLOAD_P1_DONE                        EF_CTRL_EF_IF_0_AUTOLOAD_P1_DONE
#define EF_CTRL_EF_IF_0_AUTOLOAD_P1_DONE_POS                    (0U)
#define EF_CTRL_EF_IF_0_AUTOLOAD_P1_DONE_LEN                    (1U)
#define EF_CTRL_EF_IF_0_AUTOLOAD_P1_DONE_MSK                    (((1U<<EF_CTRL_EF_IF_0_AUTOLOAD_P1_DONE_LEN)-1)<<EF_CTRL_EF_IF_0_AUTOLOAD_P1_DONE_POS)
#define EF_CTRL_EF_IF_0_AUTOLOAD_P1_DONE_UMSK                   (~(((1U<<EF_CTRL_EF_IF_0_AUTOLOAD_P1_DONE_LEN)-1)<<EF_CTRL_EF_IF_0_AUTOLOAD_P1_DONE_POS))
#define EF_CTRL_EF_IF_0_AUTOLOAD_DONE                           EF_CTRL_EF_IF_0_AUTOLOAD_DONE
#define EF_CTRL_EF_IF_0_AUTOLOAD_DONE_POS                       (1U)
#define EF_CTRL_EF_IF_0_AUTOLOAD_DONE_LEN                       (1U)
#define EF_CTRL_EF_IF_0_AUTOLOAD_DONE_MSK                       (((1U<<EF_CTRL_EF_IF_0_AUTOLOAD_DONE_LEN)-1)<<EF_CTRL_EF_IF_0_AUTOLOAD_DONE_POS)
#define EF_CTRL_EF_IF_0_AUTOLOAD_DONE_UMSK                      (~(((1U<<EF_CTRL_EF_IF_0_AUTOLOAD_DONE_LEN)-1)<<EF_CTRL_EF_IF_0_AUTOLOAD_DONE_POS))
#define EF_CTRL_EF_IF_0_BUSY                                    EF_CTRL_EF_IF_0_BUSY
#define EF_CTRL_EF_IF_0_BUSY_POS                                (2U)
#define EF_CTRL_EF_IF_0_BUSY_LEN                                (1U)
#define EF_CTRL_EF_IF_0_BUSY_MSK                                (((1U<<EF_CTRL_EF_IF_0_BUSY_LEN)-1)<<EF_CTRL_EF_IF_0_BUSY_POS)
#define EF_CTRL_EF_IF_0_BUSY_UMSK                               (~(((1U<<EF_CTRL_EF_IF_0_BUSY_LEN)-1)<<EF_CTRL_EF_IF_0_BUSY_POS))
#define EF_CTRL_EF_IF_0_RW                                      EF_CTRL_EF_IF_0_RW
#define EF_CTRL_EF_IF_0_RW_POS                                  (3U)
#define EF_CTRL_EF_IF_0_RW_LEN                                  (1U)
#define EF_CTRL_EF_IF_0_RW_MSK                                  (((1U<<EF_CTRL_EF_IF_0_RW_LEN)-1)<<EF_CTRL_EF_IF_0_RW_POS)
#define EF_CTRL_EF_IF_0_RW_UMSK                                 (~(((1U<<EF_CTRL_EF_IF_0_RW_LEN)-1)<<EF_CTRL_EF_IF_0_RW_POS))
#define EF_CTRL_EF_IF_0_TRIG                                    EF_CTRL_EF_IF_0_TRIG
#define EF_CTRL_EF_IF_0_TRIG_POS                                (4U)
#define EF_CTRL_EF_IF_0_TRIG_LEN                                (1U)
#define EF_CTRL_EF_IF_0_TRIG_MSK                                (((1U<<EF_CTRL_EF_IF_0_TRIG_LEN)-1)<<EF_CTRL_EF_IF_0_TRIG_POS)
#define EF_CTRL_EF_IF_0_TRIG_UMSK                               (~(((1U<<EF_CTRL_EF_IF_0_TRIG_LEN)-1)<<EF_CTRL_EF_IF_0_TRIG_POS))
#define EF_CTRL_EF_IF_0_MANUAL_EN                               EF_CTRL_EF_IF_0_MANUAL_EN
#define EF_CTRL_EF_IF_0_MANUAL_EN_POS                           (5U)
#define EF_CTRL_EF_IF_0_MANUAL_EN_LEN                           (1U)
#define EF_CTRL_EF_IF_0_MANUAL_EN_MSK                           (((1U<<EF_CTRL_EF_IF_0_MANUAL_EN_LEN)-1)<<EF_CTRL_EF_IF_0_MANUAL_EN_POS)
#define EF_CTRL_EF_IF_0_MANUAL_EN_UMSK                          (~(((1U<<EF_CTRL_EF_IF_0_MANUAL_EN_LEN)-1)<<EF_CTRL_EF_IF_0_MANUAL_EN_POS))
#define EF_CTRL_EF_IF_0_CYC_MODIFY                              EF_CTRL_EF_IF_0_CYC_MODIFY
#define EF_CTRL_EF_IF_0_CYC_MODIFY_POS                          (6U)
#define EF_CTRL_EF_IF_0_CYC_MODIFY_LEN                          (1U)
#define EF_CTRL_EF_IF_0_CYC_MODIFY_MSK                          (((1U<<EF_CTRL_EF_IF_0_CYC_MODIFY_LEN)-1)<<EF_CTRL_EF_IF_0_CYC_MODIFY_POS)
#define EF_CTRL_EF_IF_0_CYC_MODIFY_UMSK                         (~(((1U<<EF_CTRL_EF_IF_0_CYC_MODIFY_LEN)-1)<<EF_CTRL_EF_IF_0_CYC_MODIFY_POS))
#define EF_CTRL_EF_CLK_SAHB_DATA_SEL                            EF_CTRL_EF_CLK_SAHB_DATA_SEL
#define EF_CTRL_EF_CLK_SAHB_DATA_SEL_POS                        (7U)
#define EF_CTRL_EF_CLK_SAHB_DATA_SEL_LEN                        (1U)
#define EF_CTRL_EF_CLK_SAHB_DATA_SEL_MSK                        (((1U<<EF_CTRL_EF_CLK_SAHB_DATA_SEL_LEN)-1)<<EF_CTRL_EF_CLK_SAHB_DATA_SEL_POS)
#define EF_CTRL_EF_CLK_SAHB_DATA_SEL_UMSK                       (~(((1U<<EF_CTRL_EF_CLK_SAHB_DATA_SEL_LEN)-1)<<EF_CTRL_EF_CLK_SAHB_DATA_SEL_POS))
#define EF_CTRL_EF_IF_PROT_CODE_CTRL                            EF_CTRL_EF_IF_PROT_CODE_CTRL
#define EF_CTRL_EF_IF_PROT_CODE_CTRL_POS                        (8U)
#define EF_CTRL_EF_IF_PROT_CODE_CTRL_LEN                        (8U)
#define EF_CTRL_EF_IF_PROT_CODE_CTRL_MSK                        (((1U<<EF_CTRL_EF_IF_PROT_CODE_CTRL_LEN)-1)<<EF_CTRL_EF_IF_PROT_CODE_CTRL_POS)
#define EF_CTRL_EF_IF_PROT_CODE_CTRL_UMSK                       (~(((1U<<EF_CTRL_EF_IF_PROT_CODE_CTRL_LEN)-1)<<EF_CTRL_EF_IF_PROT_CODE_CTRL_POS))
#define EF_CTRL_EF_IF_POR_DIG                                   EF_CTRL_EF_IF_POR_DIG
#define EF_CTRL_EF_IF_POR_DIG_POS                               (16U)
#define EF_CTRL_EF_IF_POR_DIG_LEN                               (1U)
#define EF_CTRL_EF_IF_POR_DIG_MSK                               (((1U<<EF_CTRL_EF_IF_POR_DIG_LEN)-1)<<EF_CTRL_EF_IF_POR_DIG_POS)
#define EF_CTRL_EF_IF_POR_DIG_UMSK                              (~(((1U<<EF_CTRL_EF_IF_POR_DIG_LEN)-1)<<EF_CTRL_EF_IF_POR_DIG_POS))
#define EF_CTRL_EF_CLK_SAHB_DATA_GATE                           EF_CTRL_EF_CLK_SAHB_DATA_GATE
#define EF_CTRL_EF_CLK_SAHB_DATA_GATE_POS                       (17U)
#define EF_CTRL_EF_CLK_SAHB_DATA_GATE_LEN                       (1U)
#define EF_CTRL_EF_CLK_SAHB_DATA_GATE_MSK                       (((1U<<EF_CTRL_EF_CLK_SAHB_DATA_GATE_LEN)-1)<<EF_CTRL_EF_CLK_SAHB_DATA_GATE_POS)
#define EF_CTRL_EF_CLK_SAHB_DATA_GATE_UMSK                      (~(((1U<<EF_CTRL_EF_CLK_SAHB_DATA_GATE_LEN)-1)<<EF_CTRL_EF_CLK_SAHB_DATA_GATE_POS))
#define EF_CTRL_EF_IF_AUTO_RD_EN                                EF_CTRL_EF_IF_AUTO_RD_EN
#define EF_CTRL_EF_IF_AUTO_RD_EN_POS                            (18U)
#define EF_CTRL_EF_IF_AUTO_RD_EN_LEN                            (1U)
#define EF_CTRL_EF_IF_AUTO_RD_EN_MSK                            (((1U<<EF_CTRL_EF_IF_AUTO_RD_EN_LEN)-1)<<EF_CTRL_EF_IF_AUTO_RD_EN_POS)
#define EF_CTRL_EF_IF_AUTO_RD_EN_UMSK                           (~(((1U<<EF_CTRL_EF_IF_AUTO_RD_EN_LEN)-1)<<EF_CTRL_EF_IF_AUTO_RD_EN_POS))
#define EF_CTRL_EF_IF_CYC_MODIFY_LOCK                           EF_CTRL_EF_IF_CYC_MODIFY_LOCK
#define EF_CTRL_EF_IF_CYC_MODIFY_LOCK_POS                       (19U)
#define EF_CTRL_EF_IF_CYC_MODIFY_LOCK_LEN                       (1U)
#define EF_CTRL_EF_IF_CYC_MODIFY_LOCK_MSK                       (((1U<<EF_CTRL_EF_IF_CYC_MODIFY_LOCK_LEN)-1)<<EF_CTRL_EF_IF_CYC_MODIFY_LOCK_POS)
#define EF_CTRL_EF_IF_CYC_MODIFY_LOCK_UMSK                      (~(((1U<<EF_CTRL_EF_IF_CYC_MODIFY_LOCK_LEN)-1)<<EF_CTRL_EF_IF_CYC_MODIFY_LOCK_POS))
#define EF_CTRL_EF_IF_0_INT                                     EF_CTRL_EF_IF_0_INT
#define EF_CTRL_EF_IF_0_INT_POS                                 (20U)
#define EF_CTRL_EF_IF_0_INT_LEN                                 (1U)
#define EF_CTRL_EF_IF_0_INT_MSK                                 (((1U<<EF_CTRL_EF_IF_0_INT_LEN)-1)<<EF_CTRL_EF_IF_0_INT_POS)
#define EF_CTRL_EF_IF_0_INT_UMSK                                (~(((1U<<EF_CTRL_EF_IF_0_INT_LEN)-1)<<EF_CTRL_EF_IF_0_INT_POS))
#define EF_CTRL_EF_IF_0_INT_CLR                                 EF_CTRL_EF_IF_0_INT_CLR
#define EF_CTRL_EF_IF_0_INT_CLR_POS                             (21U)
#define EF_CTRL_EF_IF_0_INT_CLR_LEN                             (1U)
#define EF_CTRL_EF_IF_0_INT_CLR_MSK                             (((1U<<EF_CTRL_EF_IF_0_INT_CLR_LEN)-1)<<EF_CTRL_EF_IF_0_INT_CLR_POS)
#define EF_CTRL_EF_IF_0_INT_CLR_UMSK                            (~(((1U<<EF_CTRL_EF_IF_0_INT_CLR_LEN)-1)<<EF_CTRL_EF_IF_0_INT_CLR_POS))
#define EF_CTRL_EF_IF_0_INT_SET                                 EF_CTRL_EF_IF_0_INT_SET
#define EF_CTRL_EF_IF_0_INT_SET_POS                             (22U)
#define EF_CTRL_EF_IF_0_INT_SET_LEN                             (1U)
#define EF_CTRL_EF_IF_0_INT_SET_MSK                             (((1U<<EF_CTRL_EF_IF_0_INT_SET_LEN)-1)<<EF_CTRL_EF_IF_0_INT_SET_POS)
#define EF_CTRL_EF_IF_0_INT_SET_UMSK                            (~(((1U<<EF_CTRL_EF_IF_0_INT_SET_LEN)-1)<<EF_CTRL_EF_IF_0_INT_SET_POS))
#define EF_CTRL_EF_IF_PROT_CODE_CYC                             EF_CTRL_EF_IF_PROT_CODE_CYC
#define EF_CTRL_EF_IF_PROT_CODE_CYC_POS                         (24U)
#define EF_CTRL_EF_IF_PROT_CODE_CYC_LEN                         (8U)
#define EF_CTRL_EF_IF_PROT_CODE_CYC_MSK                         (((1U<<EF_CTRL_EF_IF_PROT_CODE_CYC_LEN)-1)<<EF_CTRL_EF_IF_PROT_CODE_CYC_POS)
#define EF_CTRL_EF_IF_PROT_CODE_CYC_UMSK                        (~(((1U<<EF_CTRL_EF_IF_PROT_CODE_CYC_LEN)-1)<<EF_CTRL_EF_IF_PROT_CODE_CYC_POS))

/* 0x804 : ef_if_cyc_0 */
#define EF_CTRL_EF_IF_CYC_0_OFFSET                              (0x804)
#define EF_CTRL_EF_IF_CYC_RD_DMY                                EF_CTRL_EF_IF_CYC_RD_DMY
#define EF_CTRL_EF_IF_CYC_RD_DMY_POS                            (0U)
#define EF_CTRL_EF_IF_CYC_RD_DMY_LEN                            (6U)
#define EF_CTRL_EF_IF_CYC_RD_DMY_MSK                            (((1U<<EF_CTRL_EF_IF_CYC_RD_DMY_LEN)-1)<<EF_CTRL_EF_IF_CYC_RD_DMY_POS)
#define EF_CTRL_EF_IF_CYC_RD_DMY_UMSK                           (~(((1U<<EF_CTRL_EF_IF_CYC_RD_DMY_LEN)-1)<<EF_CTRL_EF_IF_CYC_RD_DMY_POS))
#define EF_CTRL_EF_IF_CYC_RD_DAT                                EF_CTRL_EF_IF_CYC_RD_DAT
#define EF_CTRL_EF_IF_CYC_RD_DAT_POS                            (6U)
#define EF_CTRL_EF_IF_CYC_RD_DAT_LEN                            (6U)
#define EF_CTRL_EF_IF_CYC_RD_DAT_MSK                            (((1U<<EF_CTRL_EF_IF_CYC_RD_DAT_LEN)-1)<<EF_CTRL_EF_IF_CYC_RD_DAT_POS)
#define EF_CTRL_EF_IF_CYC_RD_DAT_UMSK                           (~(((1U<<EF_CTRL_EF_IF_CYC_RD_DAT_LEN)-1)<<EF_CTRL_EF_IF_CYC_RD_DAT_POS))
#define EF_CTRL_EF_IF_CYC_RD_ADR                                EF_CTRL_EF_IF_CYC_RD_ADR
#define EF_CTRL_EF_IF_CYC_RD_ADR_POS                            (12U)
#define EF_CTRL_EF_IF_CYC_RD_ADR_LEN                            (6U)
#define EF_CTRL_EF_IF_CYC_RD_ADR_MSK                            (((1U<<EF_CTRL_EF_IF_CYC_RD_ADR_LEN)-1)<<EF_CTRL_EF_IF_CYC_RD_ADR_POS)
#define EF_CTRL_EF_IF_CYC_RD_ADR_UMSK                           (~(((1U<<EF_CTRL_EF_IF_CYC_RD_ADR_LEN)-1)<<EF_CTRL_EF_IF_CYC_RD_ADR_POS))
#define EF_CTRL_EF_IF_CYC_CS                                    EF_CTRL_EF_IF_CYC_CS
#define EF_CTRL_EF_IF_CYC_CS_POS                                (18U)
#define EF_CTRL_EF_IF_CYC_CS_LEN                                (6U)
#define EF_CTRL_EF_IF_CYC_CS_MSK                                (((1U<<EF_CTRL_EF_IF_CYC_CS_LEN)-1)<<EF_CTRL_EF_IF_CYC_CS_POS)
#define EF_CTRL_EF_IF_CYC_CS_UMSK                               (~(((1U<<EF_CTRL_EF_IF_CYC_CS_LEN)-1)<<EF_CTRL_EF_IF_CYC_CS_POS))
#define EF_CTRL_EF_IF_CYC_PD_CS_S                               EF_CTRL_EF_IF_CYC_PD_CS_S
#define EF_CTRL_EF_IF_CYC_PD_CS_S_POS                           (24U)
#define EF_CTRL_EF_IF_CYC_PD_CS_S_LEN                           (8U)
#define EF_CTRL_EF_IF_CYC_PD_CS_S_MSK                           (((1U<<EF_CTRL_EF_IF_CYC_PD_CS_S_LEN)-1)<<EF_CTRL_EF_IF_CYC_PD_CS_S_POS)
#define EF_CTRL_EF_IF_CYC_PD_CS_S_UMSK                          (~(((1U<<EF_CTRL_EF_IF_CYC_PD_CS_S_LEN)-1)<<EF_CTRL_EF_IF_CYC_PD_CS_S_POS))

/* 0x808 : ef_if_cyc_1 */
#define EF_CTRL_EF_IF_CYC_1_OFFSET                              (0x808)
#define EF_CTRL_EF_IF_CYC_PI                                    EF_CTRL_EF_IF_CYC_PI
#define EF_CTRL_EF_IF_CYC_PI_POS                                (0U)
#define EF_CTRL_EF_IF_CYC_PI_LEN                                (6U)
#define EF_CTRL_EF_IF_CYC_PI_MSK                                (((1U<<EF_CTRL_EF_IF_CYC_PI_LEN)-1)<<EF_CTRL_EF_IF_CYC_PI_POS)
#define EF_CTRL_EF_IF_CYC_PI_UMSK                               (~(((1U<<EF_CTRL_EF_IF_CYC_PI_LEN)-1)<<EF_CTRL_EF_IF_CYC_PI_POS))
#define EF_CTRL_EF_IF_CYC_PP                                    EF_CTRL_EF_IF_CYC_PP
#define EF_CTRL_EF_IF_CYC_PP_POS                                (6U)
#define EF_CTRL_EF_IF_CYC_PP_LEN                                (8U)
#define EF_CTRL_EF_IF_CYC_PP_MSK                                (((1U<<EF_CTRL_EF_IF_CYC_PP_LEN)-1)<<EF_CTRL_EF_IF_CYC_PP_POS)
#define EF_CTRL_EF_IF_CYC_PP_UMSK                               (~(((1U<<EF_CTRL_EF_IF_CYC_PP_LEN)-1)<<EF_CTRL_EF_IF_CYC_PP_POS))
#define EF_CTRL_EF_IF_CYC_WR_ADR                                EF_CTRL_EF_IF_CYC_WR_ADR
#define EF_CTRL_EF_IF_CYC_WR_ADR_POS                            (14U)
#define EF_CTRL_EF_IF_CYC_WR_ADR_LEN                            (6U)
#define EF_CTRL_EF_IF_CYC_WR_ADR_MSK                            (((1U<<EF_CTRL_EF_IF_CYC_WR_ADR_LEN)-1)<<EF_CTRL_EF_IF_CYC_WR_ADR_POS)
#define EF_CTRL_EF_IF_CYC_WR_ADR_UMSK                           (~(((1U<<EF_CTRL_EF_IF_CYC_WR_ADR_LEN)-1)<<EF_CTRL_EF_IF_CYC_WR_ADR_POS))
#define EF_CTRL_EF_IF_CYC_PS_CS                                 EF_CTRL_EF_IF_CYC_PS_CS
#define EF_CTRL_EF_IF_CYC_PS_CS_POS                             (20U)
#define EF_CTRL_EF_IF_CYC_PS_CS_LEN                             (6U)
#define EF_CTRL_EF_IF_CYC_PS_CS_MSK                             (((1U<<EF_CTRL_EF_IF_CYC_PS_CS_LEN)-1)<<EF_CTRL_EF_IF_CYC_PS_CS_POS)
#define EF_CTRL_EF_IF_CYC_PS_CS_UMSK                            (~(((1U<<EF_CTRL_EF_IF_CYC_PS_CS_LEN)-1)<<EF_CTRL_EF_IF_CYC_PS_CS_POS))
#define EF_CTRL_EF_IF_CYC_PD_CS_H                               EF_CTRL_EF_IF_CYC_PD_CS_H
#define EF_CTRL_EF_IF_CYC_PD_CS_H_POS                           (26U)
#define EF_CTRL_EF_IF_CYC_PD_CS_H_LEN                           (6U)
#define EF_CTRL_EF_IF_CYC_PD_CS_H_MSK                           (((1U<<EF_CTRL_EF_IF_CYC_PD_CS_H_LEN)-1)<<EF_CTRL_EF_IF_CYC_PD_CS_H_POS)
#define EF_CTRL_EF_IF_CYC_PD_CS_H_UMSK                          (~(((1U<<EF_CTRL_EF_IF_CYC_PD_CS_H_LEN)-1)<<EF_CTRL_EF_IF_CYC_PD_CS_H_POS))

/* 0x80C : ef_if_0_manual */
#define EF_CTRL_EF_IF_0_MANUAL_OFFSET                           (0x80C)
#define EF_CTRL_EF_IF_A                                         EF_CTRL_EF_IF_A
#define EF_CTRL_EF_IF_A_POS                                     (0U)
#define EF_CTRL_EF_IF_A_LEN                                     (10U)
#define EF_CTRL_EF_IF_A_MSK                                     (((1U<<EF_CTRL_EF_IF_A_LEN)-1)<<EF_CTRL_EF_IF_A_POS)
#define EF_CTRL_EF_IF_A_UMSK                                    (~(((1U<<EF_CTRL_EF_IF_A_LEN)-1)<<EF_CTRL_EF_IF_A_POS))
#define EF_CTRL_EF_IF_PD                                        EF_CTRL_EF_IF_PD
#define EF_CTRL_EF_IF_PD_POS                                    (10U)
#define EF_CTRL_EF_IF_PD_LEN                                    (1U)
#define EF_CTRL_EF_IF_PD_MSK                                    (((1U<<EF_CTRL_EF_IF_PD_LEN)-1)<<EF_CTRL_EF_IF_PD_POS)
#define EF_CTRL_EF_IF_PD_UMSK                                   (~(((1U<<EF_CTRL_EF_IF_PD_LEN)-1)<<EF_CTRL_EF_IF_PD_POS))
#define EF_CTRL_EF_IF_PS                                        EF_CTRL_EF_IF_PS
#define EF_CTRL_EF_IF_PS_POS                                    (11U)
#define EF_CTRL_EF_IF_PS_LEN                                    (1U)
#define EF_CTRL_EF_IF_PS_MSK                                    (((1U<<EF_CTRL_EF_IF_PS_LEN)-1)<<EF_CTRL_EF_IF_PS_POS)
#define EF_CTRL_EF_IF_PS_UMSK                                   (~(((1U<<EF_CTRL_EF_IF_PS_LEN)-1)<<EF_CTRL_EF_IF_PS_POS))
#define EF_CTRL_EF_IF_STROBE                                    EF_CTRL_EF_IF_STROBE
#define EF_CTRL_EF_IF_STROBE_POS                                (12U)
#define EF_CTRL_EF_IF_STROBE_LEN                                (1U)
#define EF_CTRL_EF_IF_STROBE_MSK                                (((1U<<EF_CTRL_EF_IF_STROBE_LEN)-1)<<EF_CTRL_EF_IF_STROBE_POS)
#define EF_CTRL_EF_IF_STROBE_UMSK                               (~(((1U<<EF_CTRL_EF_IF_STROBE_LEN)-1)<<EF_CTRL_EF_IF_STROBE_POS))
#define EF_CTRL_EF_IF_PGENB                                     EF_CTRL_EF_IF_PGENB
#define EF_CTRL_EF_IF_PGENB_POS                                 (13U)
#define EF_CTRL_EF_IF_PGENB_LEN                                 (1U)
#define EF_CTRL_EF_IF_PGENB_MSK                                 (((1U<<EF_CTRL_EF_IF_PGENB_LEN)-1)<<EF_CTRL_EF_IF_PGENB_POS)
#define EF_CTRL_EF_IF_PGENB_UMSK                                (~(((1U<<EF_CTRL_EF_IF_PGENB_LEN)-1)<<EF_CTRL_EF_IF_PGENB_POS))
#define EF_CTRL_EF_IF_LOAD                                      EF_CTRL_EF_IF_LOAD
#define EF_CTRL_EF_IF_LOAD_POS                                  (14U)
#define EF_CTRL_EF_IF_LOAD_LEN                                  (1U)
#define EF_CTRL_EF_IF_LOAD_MSK                                  (((1U<<EF_CTRL_EF_IF_LOAD_LEN)-1)<<EF_CTRL_EF_IF_LOAD_POS)
#define EF_CTRL_EF_IF_LOAD_UMSK                                 (~(((1U<<EF_CTRL_EF_IF_LOAD_LEN)-1)<<EF_CTRL_EF_IF_LOAD_POS))
#define EF_CTRL_EF_IF_CSB                                       EF_CTRL_EF_IF_CSB
#define EF_CTRL_EF_IF_CSB_POS                                   (15U)
#define EF_CTRL_EF_IF_CSB_LEN                                   (1U)
#define EF_CTRL_EF_IF_CSB_MSK                                   (((1U<<EF_CTRL_EF_IF_CSB_LEN)-1)<<EF_CTRL_EF_IF_CSB_POS)
#define EF_CTRL_EF_IF_CSB_UMSK                                  (~(((1U<<EF_CTRL_EF_IF_CSB_LEN)-1)<<EF_CTRL_EF_IF_CSB_POS))
#define EF_CTRL_EF_IF_0_Q                                       EF_CTRL_EF_IF_0_Q
#define EF_CTRL_EF_IF_0_Q_POS                                   (16U)
#define EF_CTRL_EF_IF_0_Q_LEN                                   (8U)
#define EF_CTRL_EF_IF_0_Q_MSK                                   (((1U<<EF_CTRL_EF_IF_0_Q_LEN)-1)<<EF_CTRL_EF_IF_0_Q_POS)
#define EF_CTRL_EF_IF_0_Q_UMSK                                  (~(((1U<<EF_CTRL_EF_IF_0_Q_LEN)-1)<<EF_CTRL_EF_IF_0_Q_POS))
#define EF_CTRL_EF_IF_PROT_CODE_MANUAL                          EF_CTRL_EF_IF_PROT_CODE_MANUAL
#define EF_CTRL_EF_IF_PROT_CODE_MANUAL_POS                      (24U)
#define EF_CTRL_EF_IF_PROT_CODE_MANUAL_LEN                      (8U)
#define EF_CTRL_EF_IF_PROT_CODE_MANUAL_MSK                      (((1U<<EF_CTRL_EF_IF_PROT_CODE_MANUAL_LEN)-1)<<EF_CTRL_EF_IF_PROT_CODE_MANUAL_POS)
#define EF_CTRL_EF_IF_PROT_CODE_MANUAL_UMSK                     (~(((1U<<EF_CTRL_EF_IF_PROT_CODE_MANUAL_LEN)-1)<<EF_CTRL_EF_IF_PROT_CODE_MANUAL_POS))

/* 0x810 : ef_if_0_status */
#define EF_CTRL_EF_IF_0_STATUS_OFFSET                           (0x810)
#define EF_CTRL_EF_IF_0_STATUS                                  EF_CTRL_EF_IF_0_STATUS
#define EF_CTRL_EF_IF_0_STATUS_POS                              (0U)
#define EF_CTRL_EF_IF_0_STATUS_LEN                              (32U)
#define EF_CTRL_EF_IF_0_STATUS_MSK                              (((1U<<EF_CTRL_EF_IF_0_STATUS_LEN)-1)<<EF_CTRL_EF_IF_0_STATUS_POS)
#define EF_CTRL_EF_IF_0_STATUS_UMSK                             (~(((1U<<EF_CTRL_EF_IF_0_STATUS_LEN)-1)<<EF_CTRL_EF_IF_0_STATUS_POS))

/* 0x814 : ef_if_cfg_0 */
#define EF_CTRL_EF_IF_CFG_0_OFFSET                              (0x814)
#define EF_CTRL_EF_IF_SF_AES_MODE                               EF_CTRL_EF_IF_SF_AES_MODE
#define EF_CTRL_EF_IF_SF_AES_MODE_POS                           (0U)
#define EF_CTRL_EF_IF_SF_AES_MODE_LEN                           (2U)
#define EF_CTRL_EF_IF_SF_AES_MODE_MSK                           (((1U<<EF_CTRL_EF_IF_SF_AES_MODE_LEN)-1)<<EF_CTRL_EF_IF_SF_AES_MODE_POS)
#define EF_CTRL_EF_IF_SF_AES_MODE_UMSK                          (~(((1U<<EF_CTRL_EF_IF_SF_AES_MODE_LEN)-1)<<EF_CTRL_EF_IF_SF_AES_MODE_POS))
#define EF_CTRL_EF_IF_AI_DIS                                    EF_CTRL_EF_IF_AI_DIS
#define EF_CTRL_EF_IF_AI_DIS_POS                                (2U)
#define EF_CTRL_EF_IF_AI_DIS_LEN                                (1U)
#define EF_CTRL_EF_IF_AI_DIS_MSK                                (((1U<<EF_CTRL_EF_IF_AI_DIS_LEN)-1)<<EF_CTRL_EF_IF_AI_DIS_POS)
#define EF_CTRL_EF_IF_AI_DIS_UMSK                               (~(((1U<<EF_CTRL_EF_IF_AI_DIS_LEN)-1)<<EF_CTRL_EF_IF_AI_DIS_POS))
#define EF_CTRL_EF_IF_CPU0_DIS                                  EF_CTRL_EF_IF_CPU0_DIS
#define EF_CTRL_EF_IF_CPU0_DIS_POS                              (3U)
#define EF_CTRL_EF_IF_CPU0_DIS_LEN                              (1U)
#define EF_CTRL_EF_IF_CPU0_DIS_MSK                              (((1U<<EF_CTRL_EF_IF_CPU0_DIS_LEN)-1)<<EF_CTRL_EF_IF_CPU0_DIS_POS)
#define EF_CTRL_EF_IF_CPU0_DIS_UMSK                             (~(((1U<<EF_CTRL_EF_IF_CPU0_DIS_LEN)-1)<<EF_CTRL_EF_IF_CPU0_DIS_POS))
#define EF_CTRL_EF_IF_SBOOT_EN                                  EF_CTRL_EF_IF_SBOOT_EN
#define EF_CTRL_EF_IF_SBOOT_EN_POS                              (4U)
#define EF_CTRL_EF_IF_SBOOT_EN_LEN                              (2U)
#define EF_CTRL_EF_IF_SBOOT_EN_MSK                              (((1U<<EF_CTRL_EF_IF_SBOOT_EN_LEN)-1)<<EF_CTRL_EF_IF_SBOOT_EN_POS)
#define EF_CTRL_EF_IF_SBOOT_EN_UMSK                             (~(((1U<<EF_CTRL_EF_IF_SBOOT_EN_LEN)-1)<<EF_CTRL_EF_IF_SBOOT_EN_POS))
#define EF_CTRL_EF_IF_UART_DIS                                  EF_CTRL_EF_IF_UART_DIS
#define EF_CTRL_EF_IF_UART_DIS_POS                              (6U)
#define EF_CTRL_EF_IF_UART_DIS_LEN                              (4U)
#define EF_CTRL_EF_IF_UART_DIS_MSK                              (((1U<<EF_CTRL_EF_IF_UART_DIS_LEN)-1)<<EF_CTRL_EF_IF_UART_DIS_POS)
#define EF_CTRL_EF_IF_UART_DIS_UMSK                             (~(((1U<<EF_CTRL_EF_IF_UART_DIS_LEN)-1)<<EF_CTRL_EF_IF_UART_DIS_POS))
#define EF_CTRL_EF_IF_BLE2_DIS                                  EF_CTRL_EF_IF_BLE2_DIS
#define EF_CTRL_EF_IF_BLE2_DIS_POS                              (10U)
#define EF_CTRL_EF_IF_BLE2_DIS_LEN                              (1U)
#define EF_CTRL_EF_IF_BLE2_DIS_MSK                              (((1U<<EF_CTRL_EF_IF_BLE2_DIS_LEN)-1)<<EF_CTRL_EF_IF_BLE2_DIS_POS)
#define EF_CTRL_EF_IF_BLE2_DIS_UMSK                             (~(((1U<<EF_CTRL_EF_IF_BLE2_DIS_LEN)-1)<<EF_CTRL_EF_IF_BLE2_DIS_POS))
#define EF_CTRL_EF_IF_M1542_DIS                                 EF_CTRL_EF_IF_M1542_DIS
#define EF_CTRL_EF_IF_M1542_DIS_POS                             (11U)
#define EF_CTRL_EF_IF_M1542_DIS_LEN                             (1U)
#define EF_CTRL_EF_IF_M1542_DIS_MSK                             (((1U<<EF_CTRL_EF_IF_M1542_DIS_LEN)-1)<<EF_CTRL_EF_IF_M1542_DIS_POS)
#define EF_CTRL_EF_IF_M1542_DIS_UMSK                            (~(((1U<<EF_CTRL_EF_IF_M1542_DIS_LEN)-1)<<EF_CTRL_EF_IF_M1542_DIS_POS))
#define EF_CTRL_EF_IF_SF_KEY_RE_SEL                             EF_CTRL_EF_IF_SF_KEY_RE_SEL
#define EF_CTRL_EF_IF_SF_KEY_RE_SEL_POS                         (12U)
#define EF_CTRL_EF_IF_SF_KEY_RE_SEL_LEN                         (2U)
#define EF_CTRL_EF_IF_SF_KEY_RE_SEL_MSK                         (((1U<<EF_CTRL_EF_IF_SF_KEY_RE_SEL_LEN)-1)<<EF_CTRL_EF_IF_SF_KEY_RE_SEL_POS)
#define EF_CTRL_EF_IF_SF_KEY_RE_SEL_UMSK                        (~(((1U<<EF_CTRL_EF_IF_SF_KEY_RE_SEL_LEN)-1)<<EF_CTRL_EF_IF_SF_KEY_RE_SEL_POS))
#define EF_CTRL_EF_IF_SDU_DIS                                   EF_CTRL_EF_IF_SDU_DIS
#define EF_CTRL_EF_IF_SDU_DIS_POS                               (14U)
#define EF_CTRL_EF_IF_SDU_DIS_LEN                               (1U)
#define EF_CTRL_EF_IF_SDU_DIS_MSK                               (((1U<<EF_CTRL_EF_IF_SDU_DIS_LEN)-1)<<EF_CTRL_EF_IF_SDU_DIS_POS)
#define EF_CTRL_EF_IF_SDU_DIS_UMSK                              (~(((1U<<EF_CTRL_EF_IF_SDU_DIS_LEN)-1)<<EF_CTRL_EF_IF_SDU_DIS_POS))
#define EF_CTRL_EF_IF_BTDM_DIS                                  EF_CTRL_EF_IF_BTDM_DIS
#define EF_CTRL_EF_IF_BTDM_DIS_POS                              (15U)
#define EF_CTRL_EF_IF_BTDM_DIS_LEN                              (1U)
#define EF_CTRL_EF_IF_BTDM_DIS_MSK                              (((1U<<EF_CTRL_EF_IF_BTDM_DIS_LEN)-1)<<EF_CTRL_EF_IF_BTDM_DIS_POS)
#define EF_CTRL_EF_IF_BTDM_DIS_UMSK                             (~(((1U<<EF_CTRL_EF_IF_BTDM_DIS_LEN)-1)<<EF_CTRL_EF_IF_BTDM_DIS_POS))
#define EF_CTRL_EF_IF_WIFI_DIS                                  EF_CTRL_EF_IF_WIFI_DIS
#define EF_CTRL_EF_IF_WIFI_DIS_POS                              (16U)
#define EF_CTRL_EF_IF_WIFI_DIS_LEN                              (1U)
#define EF_CTRL_EF_IF_WIFI_DIS_MSK                              (((1U<<EF_CTRL_EF_IF_WIFI_DIS_LEN)-1)<<EF_CTRL_EF_IF_WIFI_DIS_POS)
#define EF_CTRL_EF_IF_WIFI_DIS_UMSK                             (~(((1U<<EF_CTRL_EF_IF_WIFI_DIS_LEN)-1)<<EF_CTRL_EF_IF_WIFI_DIS_POS))
#define EF_CTRL_EF_IF_0_KEY_ENC_EN                              EF_CTRL_EF_IF_0_KEY_ENC_EN
#define EF_CTRL_EF_IF_0_KEY_ENC_EN_POS                          (17U)
#define EF_CTRL_EF_IF_0_KEY_ENC_EN_LEN                          (1U)
#define EF_CTRL_EF_IF_0_KEY_ENC_EN_MSK                          (((1U<<EF_CTRL_EF_IF_0_KEY_ENC_EN_LEN)-1)<<EF_CTRL_EF_IF_0_KEY_ENC_EN_POS)
#define EF_CTRL_EF_IF_0_KEY_ENC_EN_UMSK                         (~(((1U<<EF_CTRL_EF_IF_0_KEY_ENC_EN_LEN)-1)<<EF_CTRL_EF_IF_0_KEY_ENC_EN_POS))
#define EF_CTRL_EF_IF_CAM_DIS                                   EF_CTRL_EF_IF_CAM_DIS
#define EF_CTRL_EF_IF_CAM_DIS_POS                               (18U)
#define EF_CTRL_EF_IF_CAM_DIS_LEN                               (1U)
#define EF_CTRL_EF_IF_CAM_DIS_MSK                               (((1U<<EF_CTRL_EF_IF_CAM_DIS_LEN)-1)<<EF_CTRL_EF_IF_CAM_DIS_POS)
#define EF_CTRL_EF_IF_CAM_DIS_UMSK                              (~(((1U<<EF_CTRL_EF_IF_CAM_DIS_LEN)-1)<<EF_CTRL_EF_IF_CAM_DIS_POS))
#define EF_CTRL_EF_IF_M154_DIS                                  EF_CTRL_EF_IF_M154_DIS
#define EF_CTRL_EF_IF_M154_DIS_POS                              (19U)
#define EF_CTRL_EF_IF_M154_DIS_LEN                              (1U)
#define EF_CTRL_EF_IF_M154_DIS_MSK                              (((1U<<EF_CTRL_EF_IF_M154_DIS_LEN)-1)<<EF_CTRL_EF_IF_M154_DIS_POS)
#define EF_CTRL_EF_IF_M154_DIS_UMSK                             (~(((1U<<EF_CTRL_EF_IF_M154_DIS_LEN)-1)<<EF_CTRL_EF_IF_M154_DIS_POS))
#define EF_CTRL_EF_IF_CPU1_DIS                                  EF_CTRL_EF_IF_CPU1_DIS
#define EF_CTRL_EF_IF_CPU1_DIS_POS                              (20U)
#define EF_CTRL_EF_IF_CPU1_DIS_LEN                              (1U)
#define EF_CTRL_EF_IF_CPU1_DIS_MSK                              (((1U<<EF_CTRL_EF_IF_CPU1_DIS_LEN)-1)<<EF_CTRL_EF_IF_CPU1_DIS_POS)
#define EF_CTRL_EF_IF_CPU1_DIS_UMSK                             (~(((1U<<EF_CTRL_EF_IF_CPU1_DIS_LEN)-1)<<EF_CTRL_EF_IF_CPU1_DIS_POS))
#define EF_CTRL_EF_IF_CPU_RST_DBG_DIS                           EF_CTRL_EF_IF_CPU_RST_DBG_DIS
#define EF_CTRL_EF_IF_CPU_RST_DBG_DIS_POS                       (21U)
#define EF_CTRL_EF_IF_CPU_RST_DBG_DIS_LEN                       (1U)
#define EF_CTRL_EF_IF_CPU_RST_DBG_DIS_MSK                       (((1U<<EF_CTRL_EF_IF_CPU_RST_DBG_DIS_LEN)-1)<<EF_CTRL_EF_IF_CPU_RST_DBG_DIS_POS)
#define EF_CTRL_EF_IF_CPU_RST_DBG_DIS_UMSK                      (~(((1U<<EF_CTRL_EF_IF_CPU_RST_DBG_DIS_LEN)-1)<<EF_CTRL_EF_IF_CPU_RST_DBG_DIS_POS))
#define EF_CTRL_EF_IF_SE_DBG_DIS                                EF_CTRL_EF_IF_SE_DBG_DIS
#define EF_CTRL_EF_IF_SE_DBG_DIS_POS                            (22U)
#define EF_CTRL_EF_IF_SE_DBG_DIS_LEN                            (1U)
#define EF_CTRL_EF_IF_SE_DBG_DIS_MSK                            (((1U<<EF_CTRL_EF_IF_SE_DBG_DIS_LEN)-1)<<EF_CTRL_EF_IF_SE_DBG_DIS_POS)
#define EF_CTRL_EF_IF_SE_DBG_DIS_UMSK                           (~(((1U<<EF_CTRL_EF_IF_SE_DBG_DIS_LEN)-1)<<EF_CTRL_EF_IF_SE_DBG_DIS_POS))
#define EF_CTRL_EF_IF_EFUSE_DBG_DIS                             EF_CTRL_EF_IF_EFUSE_DBG_DIS
#define EF_CTRL_EF_IF_EFUSE_DBG_DIS_POS                         (23U)
#define EF_CTRL_EF_IF_EFUSE_DBG_DIS_LEN                         (1U)
#define EF_CTRL_EF_IF_EFUSE_DBG_DIS_MSK                         (((1U<<EF_CTRL_EF_IF_EFUSE_DBG_DIS_LEN)-1)<<EF_CTRL_EF_IF_EFUSE_DBG_DIS_POS)
#define EF_CTRL_EF_IF_EFUSE_DBG_DIS_UMSK                        (~(((1U<<EF_CTRL_EF_IF_EFUSE_DBG_DIS_LEN)-1)<<EF_CTRL_EF_IF_EFUSE_DBG_DIS_POS))
#define EF_CTRL_EF_IF_DBG_JTAG_1_DIS                            EF_CTRL_EF_IF_DBG_JTAG_1_DIS
#define EF_CTRL_EF_IF_DBG_JTAG_1_DIS_POS                        (24U)
#define EF_CTRL_EF_IF_DBG_JTAG_1_DIS_LEN                        (2U)
#define EF_CTRL_EF_IF_DBG_JTAG_1_DIS_MSK                        (((1U<<EF_CTRL_EF_IF_DBG_JTAG_1_DIS_LEN)-1)<<EF_CTRL_EF_IF_DBG_JTAG_1_DIS_POS)
#define EF_CTRL_EF_IF_DBG_JTAG_1_DIS_UMSK                       (~(((1U<<EF_CTRL_EF_IF_DBG_JTAG_1_DIS_LEN)-1)<<EF_CTRL_EF_IF_DBG_JTAG_1_DIS_POS))
#define EF_CTRL_EF_IF_DBG_JTAG_0_DIS                            EF_CTRL_EF_IF_DBG_JTAG_0_DIS
#define EF_CTRL_EF_IF_DBG_JTAG_0_DIS_POS                        (26U)
#define EF_CTRL_EF_IF_DBG_JTAG_0_DIS_LEN                        (2U)
#define EF_CTRL_EF_IF_DBG_JTAG_0_DIS_MSK                        (((1U<<EF_CTRL_EF_IF_DBG_JTAG_0_DIS_LEN)-1)<<EF_CTRL_EF_IF_DBG_JTAG_0_DIS_POS)
#define EF_CTRL_EF_IF_DBG_JTAG_0_DIS_UMSK                       (~(((1U<<EF_CTRL_EF_IF_DBG_JTAG_0_DIS_LEN)-1)<<EF_CTRL_EF_IF_DBG_JTAG_0_DIS_POS))
#define EF_CTRL_EF_IF_DBG_MODE                                  EF_CTRL_EF_IF_DBG_MODE
#define EF_CTRL_EF_IF_DBG_MODE_POS                              (28U)
#define EF_CTRL_EF_IF_DBG_MODE_LEN                              (4U)
#define EF_CTRL_EF_IF_DBG_MODE_MSK                              (((1U<<EF_CTRL_EF_IF_DBG_MODE_LEN)-1)<<EF_CTRL_EF_IF_DBG_MODE_POS)
#define EF_CTRL_EF_IF_DBG_MODE_UMSK                             (~(((1U<<EF_CTRL_EF_IF_DBG_MODE_LEN)-1)<<EF_CTRL_EF_IF_DBG_MODE_POS))

/* 0x818 : ef_sw_cfg_0 */
#define EF_CTRL_EF_SW_CFG_0_OFFSET                              (0x818)
#define EF_CTRL_EF_SW_SF_AES_MODE                               EF_CTRL_EF_SW_SF_AES_MODE
#define EF_CTRL_EF_SW_SF_AES_MODE_POS                           (0U)
#define EF_CTRL_EF_SW_SF_AES_MODE_LEN                           (2U)
#define EF_CTRL_EF_SW_SF_AES_MODE_MSK                           (((1U<<EF_CTRL_EF_SW_SF_AES_MODE_LEN)-1)<<EF_CTRL_EF_SW_SF_AES_MODE_POS)
#define EF_CTRL_EF_SW_SF_AES_MODE_UMSK                          (~(((1U<<EF_CTRL_EF_SW_SF_AES_MODE_LEN)-1)<<EF_CTRL_EF_SW_SF_AES_MODE_POS))
#define EF_CTRL_EF_SW_AI_DIS                                    EF_CTRL_EF_SW_AI_DIS
#define EF_CTRL_EF_SW_AI_DIS_POS                                (2U)
#define EF_CTRL_EF_SW_AI_DIS_LEN                                (1U)
#define EF_CTRL_EF_SW_AI_DIS_MSK                                (((1U<<EF_CTRL_EF_SW_AI_DIS_LEN)-1)<<EF_CTRL_EF_SW_AI_DIS_POS)
#define EF_CTRL_EF_SW_AI_DIS_UMSK                               (~(((1U<<EF_CTRL_EF_SW_AI_DIS_LEN)-1)<<EF_CTRL_EF_SW_AI_DIS_POS))
#define EF_CTRL_EF_SW_CPU0_DIS                                  EF_CTRL_EF_SW_CPU0_DIS
#define EF_CTRL_EF_SW_CPU0_DIS_POS                              (3U)
#define EF_CTRL_EF_SW_CPU0_DIS_LEN                              (1U)
#define EF_CTRL_EF_SW_CPU0_DIS_MSK                              (((1U<<EF_CTRL_EF_SW_CPU0_DIS_LEN)-1)<<EF_CTRL_EF_SW_CPU0_DIS_POS)
#define EF_CTRL_EF_SW_CPU0_DIS_UMSK                             (~(((1U<<EF_CTRL_EF_SW_CPU0_DIS_LEN)-1)<<EF_CTRL_EF_SW_CPU0_DIS_POS))
#define EF_CTRL_EF_SW_SBOOT_EN                                  EF_CTRL_EF_SW_SBOOT_EN
#define EF_CTRL_EF_SW_SBOOT_EN_POS                              (4U)
#define EF_CTRL_EF_SW_SBOOT_EN_LEN                              (2U)
#define EF_CTRL_EF_SW_SBOOT_EN_MSK                              (((1U<<EF_CTRL_EF_SW_SBOOT_EN_LEN)-1)<<EF_CTRL_EF_SW_SBOOT_EN_POS)
#define EF_CTRL_EF_SW_SBOOT_EN_UMSK                             (~(((1U<<EF_CTRL_EF_SW_SBOOT_EN_LEN)-1)<<EF_CTRL_EF_SW_SBOOT_EN_POS))
#define EF_CTRL_EF_SW_UART_DIS                                  EF_CTRL_EF_SW_UART_DIS
#define EF_CTRL_EF_SW_UART_DIS_POS                              (6U)
#define EF_CTRL_EF_SW_UART_DIS_LEN                              (4U)
#define EF_CTRL_EF_SW_UART_DIS_MSK                              (((1U<<EF_CTRL_EF_SW_UART_DIS_LEN)-1)<<EF_CTRL_EF_SW_UART_DIS_POS)
#define EF_CTRL_EF_SW_UART_DIS_UMSK                             (~(((1U<<EF_CTRL_EF_SW_UART_DIS_LEN)-1)<<EF_CTRL_EF_SW_UART_DIS_POS))
#define EF_CTRL_EF_SW_BLE2_DIS                                  EF_CTRL_EF_SW_BLE2_DIS
#define EF_CTRL_EF_SW_BLE2_DIS_POS                              (10U)
#define EF_CTRL_EF_SW_BLE2_DIS_LEN                              (1U)
#define EF_CTRL_EF_SW_BLE2_DIS_MSK                              (((1U<<EF_CTRL_EF_SW_BLE2_DIS_LEN)-1)<<EF_CTRL_EF_SW_BLE2_DIS_POS)
#define EF_CTRL_EF_SW_BLE2_DIS_UMSK                             (~(((1U<<EF_CTRL_EF_SW_BLE2_DIS_LEN)-1)<<EF_CTRL_EF_SW_BLE2_DIS_POS))
#define EF_CTRL_EF_SW_M1542_DIS                                 EF_CTRL_EF_SW_M1542_DIS
#define EF_CTRL_EF_SW_M1542_DIS_POS                             (11U)
#define EF_CTRL_EF_SW_M1542_DIS_LEN                             (1U)
#define EF_CTRL_EF_SW_M1542_DIS_MSK                             (((1U<<EF_CTRL_EF_SW_M1542_DIS_LEN)-1)<<EF_CTRL_EF_SW_M1542_DIS_POS)
#define EF_CTRL_EF_SW_M1542_DIS_UMSK                            (~(((1U<<EF_CTRL_EF_SW_M1542_DIS_LEN)-1)<<EF_CTRL_EF_SW_M1542_DIS_POS))
#define EF_CTRL_EF_SW_SF_KEY_RE_SEL                             EF_CTRL_EF_SW_SF_KEY_RE_SEL
#define EF_CTRL_EF_SW_SF_KEY_RE_SEL_POS                         (12U)
#define EF_CTRL_EF_SW_SF_KEY_RE_SEL_LEN                         (2U)
#define EF_CTRL_EF_SW_SF_KEY_RE_SEL_MSK                         (((1U<<EF_CTRL_EF_SW_SF_KEY_RE_SEL_LEN)-1)<<EF_CTRL_EF_SW_SF_KEY_RE_SEL_POS)
#define EF_CTRL_EF_SW_SF_KEY_RE_SEL_UMSK                        (~(((1U<<EF_CTRL_EF_SW_SF_KEY_RE_SEL_LEN)-1)<<EF_CTRL_EF_SW_SF_KEY_RE_SEL_POS))
#define EF_CTRL_EF_SW_SDU_DIS                                   EF_CTRL_EF_SW_SDU_DIS
#define EF_CTRL_EF_SW_SDU_DIS_POS                               (14U)
#define EF_CTRL_EF_SW_SDU_DIS_LEN                               (1U)
#define EF_CTRL_EF_SW_SDU_DIS_MSK                               (((1U<<EF_CTRL_EF_SW_SDU_DIS_LEN)-1)<<EF_CTRL_EF_SW_SDU_DIS_POS)
#define EF_CTRL_EF_SW_SDU_DIS_UMSK                              (~(((1U<<EF_CTRL_EF_SW_SDU_DIS_LEN)-1)<<EF_CTRL_EF_SW_SDU_DIS_POS))
#define EF_CTRL_EF_SW_BTDM_DIS                                  EF_CTRL_EF_SW_BTDM_DIS
#define EF_CTRL_EF_SW_BTDM_DIS_POS                              (15U)
#define EF_CTRL_EF_SW_BTDM_DIS_LEN                              (1U)
#define EF_CTRL_EF_SW_BTDM_DIS_MSK                              (((1U<<EF_CTRL_EF_SW_BTDM_DIS_LEN)-1)<<EF_CTRL_EF_SW_BTDM_DIS_POS)
#define EF_CTRL_EF_SW_BTDM_DIS_UMSK                             (~(((1U<<EF_CTRL_EF_SW_BTDM_DIS_LEN)-1)<<EF_CTRL_EF_SW_BTDM_DIS_POS))
#define EF_CTRL_EF_SW_WIFI_DIS                                  EF_CTRL_EF_SW_WIFI_DIS
#define EF_CTRL_EF_SW_WIFI_DIS_POS                              (16U)
#define EF_CTRL_EF_SW_WIFI_DIS_LEN                              (1U)
#define EF_CTRL_EF_SW_WIFI_DIS_MSK                              (((1U<<EF_CTRL_EF_SW_WIFI_DIS_LEN)-1)<<EF_CTRL_EF_SW_WIFI_DIS_POS)
#define EF_CTRL_EF_SW_WIFI_DIS_UMSK                             (~(((1U<<EF_CTRL_EF_SW_WIFI_DIS_LEN)-1)<<EF_CTRL_EF_SW_WIFI_DIS_POS))
#define EF_CTRL_EF_SW_0_KEY_ENC_EN                              EF_CTRL_EF_SW_0_KEY_ENC_EN
#define EF_CTRL_EF_SW_0_KEY_ENC_EN_POS                          (17U)
#define EF_CTRL_EF_SW_0_KEY_ENC_EN_LEN                          (1U)
#define EF_CTRL_EF_SW_0_KEY_ENC_EN_MSK                          (((1U<<EF_CTRL_EF_SW_0_KEY_ENC_EN_LEN)-1)<<EF_CTRL_EF_SW_0_KEY_ENC_EN_POS)
#define EF_CTRL_EF_SW_0_KEY_ENC_EN_UMSK                         (~(((1U<<EF_CTRL_EF_SW_0_KEY_ENC_EN_LEN)-1)<<EF_CTRL_EF_SW_0_KEY_ENC_EN_POS))
#define EF_CTRL_EF_SW_CAM_DIS                                   EF_CTRL_EF_SW_CAM_DIS
#define EF_CTRL_EF_SW_CAM_DIS_POS                               (18U)
#define EF_CTRL_EF_SW_CAM_DIS_LEN                               (1U)
#define EF_CTRL_EF_SW_CAM_DIS_MSK                               (((1U<<EF_CTRL_EF_SW_CAM_DIS_LEN)-1)<<EF_CTRL_EF_SW_CAM_DIS_POS)
#define EF_CTRL_EF_SW_CAM_DIS_UMSK                              (~(((1U<<EF_CTRL_EF_SW_CAM_DIS_LEN)-1)<<EF_CTRL_EF_SW_CAM_DIS_POS))
#define EF_CTRL_EF_SW_M154_DIS                                  EF_CTRL_EF_SW_M154_DIS
#define EF_CTRL_EF_SW_M154_DIS_POS                              (19U)
#define EF_CTRL_EF_SW_M154_DIS_LEN                              (1U)
#define EF_CTRL_EF_SW_M154_DIS_MSK                              (((1U<<EF_CTRL_EF_SW_M154_DIS_LEN)-1)<<EF_CTRL_EF_SW_M154_DIS_POS)
#define EF_CTRL_EF_SW_M154_DIS_UMSK                             (~(((1U<<EF_CTRL_EF_SW_M154_DIS_LEN)-1)<<EF_CTRL_EF_SW_M154_DIS_POS))
#define EF_CTRL_EF_SW_CPU1_DIS                                  EF_CTRL_EF_SW_CPU1_DIS
#define EF_CTRL_EF_SW_CPU1_DIS_POS                              (20U)
#define EF_CTRL_EF_SW_CPU1_DIS_LEN                              (1U)
#define EF_CTRL_EF_SW_CPU1_DIS_MSK                              (((1U<<EF_CTRL_EF_SW_CPU1_DIS_LEN)-1)<<EF_CTRL_EF_SW_CPU1_DIS_POS)
#define EF_CTRL_EF_SW_CPU1_DIS_UMSK                             (~(((1U<<EF_CTRL_EF_SW_CPU1_DIS_LEN)-1)<<EF_CTRL_EF_SW_CPU1_DIS_POS))
#define EF_CTRL_EF_SW_CPU_RST_DBG_DIS                           EF_CTRL_EF_SW_CPU_RST_DBG_DIS
#define EF_CTRL_EF_SW_CPU_RST_DBG_DIS_POS                       (21U)
#define EF_CTRL_EF_SW_CPU_RST_DBG_DIS_LEN                       (1U)
#define EF_CTRL_EF_SW_CPU_RST_DBG_DIS_MSK                       (((1U<<EF_CTRL_EF_SW_CPU_RST_DBG_DIS_LEN)-1)<<EF_CTRL_EF_SW_CPU_RST_DBG_DIS_POS)
#define EF_CTRL_EF_SW_CPU_RST_DBG_DIS_UMSK                      (~(((1U<<EF_CTRL_EF_SW_CPU_RST_DBG_DIS_LEN)-1)<<EF_CTRL_EF_SW_CPU_RST_DBG_DIS_POS))
#define EF_CTRL_EF_SW_SE_DBG_DIS                                EF_CTRL_EF_SW_SE_DBG_DIS
#define EF_CTRL_EF_SW_SE_DBG_DIS_POS                            (22U)
#define EF_CTRL_EF_SW_SE_DBG_DIS_LEN                            (1U)
#define EF_CTRL_EF_SW_SE_DBG_DIS_MSK                            (((1U<<EF_CTRL_EF_SW_SE_DBG_DIS_LEN)-1)<<EF_CTRL_EF_SW_SE_DBG_DIS_POS)
#define EF_CTRL_EF_SW_SE_DBG_DIS_UMSK                           (~(((1U<<EF_CTRL_EF_SW_SE_DBG_DIS_LEN)-1)<<EF_CTRL_EF_SW_SE_DBG_DIS_POS))
#define EF_CTRL_EF_SW_EFUSE_DBG_DIS                             EF_CTRL_EF_SW_EFUSE_DBG_DIS
#define EF_CTRL_EF_SW_EFUSE_DBG_DIS_POS                         (23U)
#define EF_CTRL_EF_SW_EFUSE_DBG_DIS_LEN                         (1U)
#define EF_CTRL_EF_SW_EFUSE_DBG_DIS_MSK                         (((1U<<EF_CTRL_EF_SW_EFUSE_DBG_DIS_LEN)-1)<<EF_CTRL_EF_SW_EFUSE_DBG_DIS_POS)
#define EF_CTRL_EF_SW_EFUSE_DBG_DIS_UMSK                        (~(((1U<<EF_CTRL_EF_SW_EFUSE_DBG_DIS_LEN)-1)<<EF_CTRL_EF_SW_EFUSE_DBG_DIS_POS))
#define EF_CTRL_EF_SW_DBG_JTAG_1_DIS                            EF_CTRL_EF_SW_DBG_JTAG_1_DIS
#define EF_CTRL_EF_SW_DBG_JTAG_1_DIS_POS                        (24U)
#define EF_CTRL_EF_SW_DBG_JTAG_1_DIS_LEN                        (2U)
#define EF_CTRL_EF_SW_DBG_JTAG_1_DIS_MSK                        (((1U<<EF_CTRL_EF_SW_DBG_JTAG_1_DIS_LEN)-1)<<EF_CTRL_EF_SW_DBG_JTAG_1_DIS_POS)
#define EF_CTRL_EF_SW_DBG_JTAG_1_DIS_UMSK                       (~(((1U<<EF_CTRL_EF_SW_DBG_JTAG_1_DIS_LEN)-1)<<EF_CTRL_EF_SW_DBG_JTAG_1_DIS_POS))
#define EF_CTRL_EF_SW_DBG_JTAG_0_DIS                            EF_CTRL_EF_SW_DBG_JTAG_0_DIS
#define EF_CTRL_EF_SW_DBG_JTAG_0_DIS_POS                        (26U)
#define EF_CTRL_EF_SW_DBG_JTAG_0_DIS_LEN                        (2U)
#define EF_CTRL_EF_SW_DBG_JTAG_0_DIS_MSK                        (((1U<<EF_CTRL_EF_SW_DBG_JTAG_0_DIS_LEN)-1)<<EF_CTRL_EF_SW_DBG_JTAG_0_DIS_POS)
#define EF_CTRL_EF_SW_DBG_JTAG_0_DIS_UMSK                       (~(((1U<<EF_CTRL_EF_SW_DBG_JTAG_0_DIS_LEN)-1)<<EF_CTRL_EF_SW_DBG_JTAG_0_DIS_POS))
#define EF_CTRL_EF_SW_DBG_MODE                                  EF_CTRL_EF_SW_DBG_MODE
#define EF_CTRL_EF_SW_DBG_MODE_POS                              (28U)
#define EF_CTRL_EF_SW_DBG_MODE_LEN                              (4U)
#define EF_CTRL_EF_SW_DBG_MODE_MSK                              (((1U<<EF_CTRL_EF_SW_DBG_MODE_LEN)-1)<<EF_CTRL_EF_SW_DBG_MODE_POS)
#define EF_CTRL_EF_SW_DBG_MODE_UMSK                             (~(((1U<<EF_CTRL_EF_SW_DBG_MODE_LEN)-1)<<EF_CTRL_EF_SW_DBG_MODE_POS))

/* 0x81C : ef_reserved */
#define EF_CTRL_EF_RESERVED_OFFSET                              (0x81C)
#define EF_CTRL_EF_RESERVED                                     EF_CTRL_EF_RESERVED
#define EF_CTRL_EF_RESERVED_POS                                 (0U)
#define EF_CTRL_EF_RESERVED_LEN                                 (32U)
#define EF_CTRL_EF_RESERVED_MSK                                 (((1U<<EF_CTRL_EF_RESERVED_LEN)-1)<<EF_CTRL_EF_RESERVED_POS)
#define EF_CTRL_EF_RESERVED_UMSK                                (~(((1U<<EF_CTRL_EF_RESERVED_LEN)-1)<<EF_CTRL_EF_RESERVED_POS))

/* 0x820 : ef_if_ana_trim_0 */
#define EF_CTRL_EF_IF_ANA_TRIM_0_OFFSET                         (0x820)
#define EF_CTRL_EF_IF_ANA_TRIM_0                                EF_CTRL_EF_IF_ANA_TRIM_0
#define EF_CTRL_EF_IF_ANA_TRIM_0_POS                            (0U)
#define EF_CTRL_EF_IF_ANA_TRIM_0_LEN                            (32U)
#define EF_CTRL_EF_IF_ANA_TRIM_0_MSK                            (((1U<<EF_CTRL_EF_IF_ANA_TRIM_0_LEN)-1)<<EF_CTRL_EF_IF_ANA_TRIM_0_POS)
#define EF_CTRL_EF_IF_ANA_TRIM_0_UMSK                           (~(((1U<<EF_CTRL_EF_IF_ANA_TRIM_0_LEN)-1)<<EF_CTRL_EF_IF_ANA_TRIM_0_POS))

/* 0x824 : ef_if_sw_usage_0 */
#define EF_CTRL_EF_IF_SW_USAGE_0_OFFSET                         (0x824)
#define EF_CTRL_EF_IF_SW_USAGE_0                                EF_CTRL_EF_IF_SW_USAGE_0
#define EF_CTRL_EF_IF_SW_USAGE_0_POS                            (0U)
#define EF_CTRL_EF_IF_SW_USAGE_0_LEN                            (32U)
#define EF_CTRL_EF_IF_SW_USAGE_0_MSK                            (((1U<<EF_CTRL_EF_IF_SW_USAGE_0_LEN)-1)<<EF_CTRL_EF_IF_SW_USAGE_0_POS)
#define EF_CTRL_EF_IF_SW_USAGE_0_UMSK                           (~(((1U<<EF_CTRL_EF_IF_SW_USAGE_0_LEN)-1)<<EF_CTRL_EF_IF_SW_USAGE_0_POS))

/* 0x900 : ef_if_ctrl_1 */
#define EF_CTRL_EF_IF_CTRL_1_OFFSET                             (0x900)
#define EF_CTRL_EF_IF_1_BUSY                                    EF_CTRL_EF_IF_1_BUSY
#define EF_CTRL_EF_IF_1_BUSY_POS                                (2U)
#define EF_CTRL_EF_IF_1_BUSY_LEN                                (1U)
#define EF_CTRL_EF_IF_1_BUSY_MSK                                (((1U<<EF_CTRL_EF_IF_1_BUSY_LEN)-1)<<EF_CTRL_EF_IF_1_BUSY_POS)
#define EF_CTRL_EF_IF_1_BUSY_UMSK                               (~(((1U<<EF_CTRL_EF_IF_1_BUSY_LEN)-1)<<EF_CTRL_EF_IF_1_BUSY_POS))
#define EF_CTRL_EF_IF_1_RW                                      EF_CTRL_EF_IF_1_RW
#define EF_CTRL_EF_IF_1_RW_POS                                  (3U)
#define EF_CTRL_EF_IF_1_RW_LEN                                  (1U)
#define EF_CTRL_EF_IF_1_RW_MSK                                  (((1U<<EF_CTRL_EF_IF_1_RW_LEN)-1)<<EF_CTRL_EF_IF_1_RW_POS)
#define EF_CTRL_EF_IF_1_RW_UMSK                                 (~(((1U<<EF_CTRL_EF_IF_1_RW_LEN)-1)<<EF_CTRL_EF_IF_1_RW_POS))
#define EF_CTRL_EF_IF_1_TRIG                                    EF_CTRL_EF_IF_1_TRIG
#define EF_CTRL_EF_IF_1_TRIG_POS                                (4U)
#define EF_CTRL_EF_IF_1_TRIG_LEN                                (1U)
#define EF_CTRL_EF_IF_1_TRIG_MSK                                (((1U<<EF_CTRL_EF_IF_1_TRIG_LEN)-1)<<EF_CTRL_EF_IF_1_TRIG_POS)
#define EF_CTRL_EF_IF_1_TRIG_UMSK                               (~(((1U<<EF_CTRL_EF_IF_1_TRIG_LEN)-1)<<EF_CTRL_EF_IF_1_TRIG_POS))
#define EF_CTRL_EF_IF_1_MANUAL_EN                               EF_CTRL_EF_IF_1_MANUAL_EN
#define EF_CTRL_EF_IF_1_MANUAL_EN_POS                           (5U)
#define EF_CTRL_EF_IF_1_MANUAL_EN_LEN                           (1U)
#define EF_CTRL_EF_IF_1_MANUAL_EN_MSK                           (((1U<<EF_CTRL_EF_IF_1_MANUAL_EN_LEN)-1)<<EF_CTRL_EF_IF_1_MANUAL_EN_POS)
#define EF_CTRL_EF_IF_1_MANUAL_EN_UMSK                          (~(((1U<<EF_CTRL_EF_IF_1_MANUAL_EN_LEN)-1)<<EF_CTRL_EF_IF_1_MANUAL_EN_POS))
#define EF_CTRL_EF_IF_1_CYC_MODIFY                              EF_CTRL_EF_IF_1_CYC_MODIFY
#define EF_CTRL_EF_IF_1_CYC_MODIFY_POS                          (6U)
#define EF_CTRL_EF_IF_1_CYC_MODIFY_LEN                          (1U)
#define EF_CTRL_EF_IF_1_CYC_MODIFY_MSK                          (((1U<<EF_CTRL_EF_IF_1_CYC_MODIFY_LEN)-1)<<EF_CTRL_EF_IF_1_CYC_MODIFY_POS)
#define EF_CTRL_EF_IF_1_CYC_MODIFY_UMSK                         (~(((1U<<EF_CTRL_EF_IF_1_CYC_MODIFY_LEN)-1)<<EF_CTRL_EF_IF_1_CYC_MODIFY_POS))
#define EF_CTRL_EF_IF_1_INT                                     EF_CTRL_EF_IF_1_INT
#define EF_CTRL_EF_IF_1_INT_POS                                 (20U)
#define EF_CTRL_EF_IF_1_INT_LEN                                 (1U)
#define EF_CTRL_EF_IF_1_INT_MSK                                 (((1U<<EF_CTRL_EF_IF_1_INT_LEN)-1)<<EF_CTRL_EF_IF_1_INT_POS)
#define EF_CTRL_EF_IF_1_INT_UMSK                                (~(((1U<<EF_CTRL_EF_IF_1_INT_LEN)-1)<<EF_CTRL_EF_IF_1_INT_POS))
#define EF_CTRL_EF_IF_1_INT_CLR                                 EF_CTRL_EF_IF_1_INT_CLR
#define EF_CTRL_EF_IF_1_INT_CLR_POS                             (21U)
#define EF_CTRL_EF_IF_1_INT_CLR_LEN                             (1U)
#define EF_CTRL_EF_IF_1_INT_CLR_MSK                             (((1U<<EF_CTRL_EF_IF_1_INT_CLR_LEN)-1)<<EF_CTRL_EF_IF_1_INT_CLR_POS)
#define EF_CTRL_EF_IF_1_INT_CLR_UMSK                            (~(((1U<<EF_CTRL_EF_IF_1_INT_CLR_LEN)-1)<<EF_CTRL_EF_IF_1_INT_CLR_POS))
#define EF_CTRL_EF_IF_1_INT_SET                                 EF_CTRL_EF_IF_1_INT_SET
#define EF_CTRL_EF_IF_1_INT_SET_POS                             (22U)
#define EF_CTRL_EF_IF_1_INT_SET_LEN                             (1U)
#define EF_CTRL_EF_IF_1_INT_SET_MSK                             (((1U<<EF_CTRL_EF_IF_1_INT_SET_LEN)-1)<<EF_CTRL_EF_IF_1_INT_SET_POS)
#define EF_CTRL_EF_IF_1_INT_SET_UMSK                            (~(((1U<<EF_CTRL_EF_IF_1_INT_SET_LEN)-1)<<EF_CTRL_EF_IF_1_INT_SET_POS))

/* 0x904 : ef_if_1_manual */
#define EF_CTRL_EF_IF_1_MANUAL_OFFSET                           (0x904)
#define EF_CTRL_EF_IF_1_Q                                       EF_CTRL_EF_IF_1_Q
#define EF_CTRL_EF_IF_1_Q_POS                                   (16U)
#define EF_CTRL_EF_IF_1_Q_LEN                                   (8U)
#define EF_CTRL_EF_IF_1_Q_MSK                                   (((1U<<EF_CTRL_EF_IF_1_Q_LEN)-1)<<EF_CTRL_EF_IF_1_Q_POS)
#define EF_CTRL_EF_IF_1_Q_UMSK                                  (~(((1U<<EF_CTRL_EF_IF_1_Q_LEN)-1)<<EF_CTRL_EF_IF_1_Q_POS))

/* 0x908 : ef_if_1_status */
#define EF_CTRL_EF_IF_1_STATUS_OFFSET                           (0x908)
#define EF_CTRL_EF_IF_1_STATUS                                  EF_CTRL_EF_IF_1_STATUS
#define EF_CTRL_EF_IF_1_STATUS_POS                              (0U)
#define EF_CTRL_EF_IF_1_STATUS_LEN                              (32U)
#define EF_CTRL_EF_IF_1_STATUS_MSK                              (((1U<<EF_CTRL_EF_IF_1_STATUS_LEN)-1)<<EF_CTRL_EF_IF_1_STATUS_POS)
#define EF_CTRL_EF_IF_1_STATUS_UMSK                             (~(((1U<<EF_CTRL_EF_IF_1_STATUS_LEN)-1)<<EF_CTRL_EF_IF_1_STATUS_POS))

/* 0x910 : ef_if_ctrl_2 */
#define EF_CTRL_EF_IF_CTRL_2_OFFSET                             (0x910)

/* 0x914 : ef_if_2_manual */
#define EF_CTRL_EF_IF_2_MANUAL_OFFSET                           (0x914)

/* 0x918 : ef_if_2_status */
#define EF_CTRL_EF_IF_2_STATUS_OFFSET                           (0x918)

/* 0xA00 : ef_crc_ctrl_0 */
#define EF_CTRL_EF_CRC_CTRL_0_OFFSET                            (0xA00)
#define EF_CTRL_EF_CRC_BUSY                                     EF_CTRL_EF_CRC_BUSY
#define EF_CTRL_EF_CRC_BUSY_POS                                 (0U)
#define EF_CTRL_EF_CRC_BUSY_LEN                                 (1U)
#define EF_CTRL_EF_CRC_BUSY_MSK                                 (((1U<<EF_CTRL_EF_CRC_BUSY_LEN)-1)<<EF_CTRL_EF_CRC_BUSY_POS)
#define EF_CTRL_EF_CRC_BUSY_UMSK                                (~(((1U<<EF_CTRL_EF_CRC_BUSY_LEN)-1)<<EF_CTRL_EF_CRC_BUSY_POS))
#define EF_CTRL_EF_CRC_TRIG                                     EF_CTRL_EF_CRC_TRIG
#define EF_CTRL_EF_CRC_TRIG_POS                                 (1U)
#define EF_CTRL_EF_CRC_TRIG_LEN                                 (1U)
#define EF_CTRL_EF_CRC_TRIG_MSK                                 (((1U<<EF_CTRL_EF_CRC_TRIG_LEN)-1)<<EF_CTRL_EF_CRC_TRIG_POS)
#define EF_CTRL_EF_CRC_TRIG_UMSK                                (~(((1U<<EF_CTRL_EF_CRC_TRIG_LEN)-1)<<EF_CTRL_EF_CRC_TRIG_POS))
#define EF_CTRL_EF_CRC_EN                                       EF_CTRL_EF_CRC_EN
#define EF_CTRL_EF_CRC_EN_POS                                   (2U)
#define EF_CTRL_EF_CRC_EN_LEN                                   (1U)
#define EF_CTRL_EF_CRC_EN_MSK                                   (((1U<<EF_CTRL_EF_CRC_EN_LEN)-1)<<EF_CTRL_EF_CRC_EN_POS)
#define EF_CTRL_EF_CRC_EN_UMSK                                  (~(((1U<<EF_CTRL_EF_CRC_EN_LEN)-1)<<EF_CTRL_EF_CRC_EN_POS))
#define EF_CTRL_EF_CRC_MODE                                     EF_CTRL_EF_CRC_MODE
#define EF_CTRL_EF_CRC_MODE_POS                                 (3U)
#define EF_CTRL_EF_CRC_MODE_LEN                                 (1U)
#define EF_CTRL_EF_CRC_MODE_MSK                                 (((1U<<EF_CTRL_EF_CRC_MODE_LEN)-1)<<EF_CTRL_EF_CRC_MODE_POS)
#define EF_CTRL_EF_CRC_MODE_UMSK                                (~(((1U<<EF_CTRL_EF_CRC_MODE_LEN)-1)<<EF_CTRL_EF_CRC_MODE_POS))
#define EF_CTRL_EF_CRC_ERROR                                    EF_CTRL_EF_CRC_ERROR
#define EF_CTRL_EF_CRC_ERROR_POS                                (4U)
#define EF_CTRL_EF_CRC_ERROR_LEN                                (1U)
#define EF_CTRL_EF_CRC_ERROR_MSK                                (((1U<<EF_CTRL_EF_CRC_ERROR_LEN)-1)<<EF_CTRL_EF_CRC_ERROR_POS)
#define EF_CTRL_EF_CRC_ERROR_UMSK                               (~(((1U<<EF_CTRL_EF_CRC_ERROR_LEN)-1)<<EF_CTRL_EF_CRC_ERROR_POS))
#define EF_CTRL_EF_CRC_DOUT_INV_EN                              EF_CTRL_EF_CRC_DOUT_INV_EN
#define EF_CTRL_EF_CRC_DOUT_INV_EN_POS                          (5U)
#define EF_CTRL_EF_CRC_DOUT_INV_EN_LEN                          (1U)
#define EF_CTRL_EF_CRC_DOUT_INV_EN_MSK                          (((1U<<EF_CTRL_EF_CRC_DOUT_INV_EN_LEN)-1)<<EF_CTRL_EF_CRC_DOUT_INV_EN_POS)
#define EF_CTRL_EF_CRC_DOUT_INV_EN_UMSK                         (~(((1U<<EF_CTRL_EF_CRC_DOUT_INV_EN_LEN)-1)<<EF_CTRL_EF_CRC_DOUT_INV_EN_POS))
#define EF_CTRL_EF_CRC_DOUT_ENDIAN                              EF_CTRL_EF_CRC_DOUT_ENDIAN
#define EF_CTRL_EF_CRC_DOUT_ENDIAN_POS                          (6U)
#define EF_CTRL_EF_CRC_DOUT_ENDIAN_LEN                          (1U)
#define EF_CTRL_EF_CRC_DOUT_ENDIAN_MSK                          (((1U<<EF_CTRL_EF_CRC_DOUT_ENDIAN_LEN)-1)<<EF_CTRL_EF_CRC_DOUT_ENDIAN_POS)
#define EF_CTRL_EF_CRC_DOUT_ENDIAN_UMSK                         (~(((1U<<EF_CTRL_EF_CRC_DOUT_ENDIAN_LEN)-1)<<EF_CTRL_EF_CRC_DOUT_ENDIAN_POS))
#define EF_CTRL_EF_CRC_DIN_ENDIAN                               EF_CTRL_EF_CRC_DIN_ENDIAN
#define EF_CTRL_EF_CRC_DIN_ENDIAN_POS                           (7U)
#define EF_CTRL_EF_CRC_DIN_ENDIAN_LEN                           (1U)
#define EF_CTRL_EF_CRC_DIN_ENDIAN_MSK                           (((1U<<EF_CTRL_EF_CRC_DIN_ENDIAN_LEN)-1)<<EF_CTRL_EF_CRC_DIN_ENDIAN_POS)
#define EF_CTRL_EF_CRC_DIN_ENDIAN_UMSK                          (~(((1U<<EF_CTRL_EF_CRC_DIN_ENDIAN_LEN)-1)<<EF_CTRL_EF_CRC_DIN_ENDIAN_POS))
#define EF_CTRL_EF_CRC_INT                                      EF_CTRL_EF_CRC_INT
#define EF_CTRL_EF_CRC_INT_POS                                  (8U)
#define EF_CTRL_EF_CRC_INT_LEN                                  (1U)
#define EF_CTRL_EF_CRC_INT_MSK                                  (((1U<<EF_CTRL_EF_CRC_INT_LEN)-1)<<EF_CTRL_EF_CRC_INT_POS)
#define EF_CTRL_EF_CRC_INT_UMSK                                 (~(((1U<<EF_CTRL_EF_CRC_INT_LEN)-1)<<EF_CTRL_EF_CRC_INT_POS))
#define EF_CTRL_EF_CRC_INT_CLR                                  EF_CTRL_EF_CRC_INT_CLR
#define EF_CTRL_EF_CRC_INT_CLR_POS                              (9U)
#define EF_CTRL_EF_CRC_INT_CLR_LEN                              (1U)
#define EF_CTRL_EF_CRC_INT_CLR_MSK                              (((1U<<EF_CTRL_EF_CRC_INT_CLR_LEN)-1)<<EF_CTRL_EF_CRC_INT_CLR_POS)
#define EF_CTRL_EF_CRC_INT_CLR_UMSK                             (~(((1U<<EF_CTRL_EF_CRC_INT_CLR_LEN)-1)<<EF_CTRL_EF_CRC_INT_CLR_POS))
#define EF_CTRL_EF_CRC_INT_SET                                  EF_CTRL_EF_CRC_INT_SET
#define EF_CTRL_EF_CRC_INT_SET_POS                              (10U)
#define EF_CTRL_EF_CRC_INT_SET_LEN                              (1U)
#define EF_CTRL_EF_CRC_INT_SET_MSK                              (((1U<<EF_CTRL_EF_CRC_INT_SET_LEN)-1)<<EF_CTRL_EF_CRC_INT_SET_POS)
#define EF_CTRL_EF_CRC_INT_SET_UMSK                             (~(((1U<<EF_CTRL_EF_CRC_INT_SET_LEN)-1)<<EF_CTRL_EF_CRC_INT_SET_POS))
#define EF_CTRL_EF_CRC_LOCK                                     EF_CTRL_EF_CRC_LOCK
#define EF_CTRL_EF_CRC_LOCK_POS                                 (11U)
#define EF_CTRL_EF_CRC_LOCK_LEN                                 (1U)
#define EF_CTRL_EF_CRC_LOCK_MSK                                 (((1U<<EF_CTRL_EF_CRC_LOCK_LEN)-1)<<EF_CTRL_EF_CRC_LOCK_POS)
#define EF_CTRL_EF_CRC_LOCK_UMSK                                (~(((1U<<EF_CTRL_EF_CRC_LOCK_LEN)-1)<<EF_CTRL_EF_CRC_LOCK_POS))
#define EF_CTRL_EF_CRC_SLP_N                                    EF_CTRL_EF_CRC_SLP_N
#define EF_CTRL_EF_CRC_SLP_N_POS                                (16U)
#define EF_CTRL_EF_CRC_SLP_N_LEN                                (16U)
#define EF_CTRL_EF_CRC_SLP_N_MSK                                (((1U<<EF_CTRL_EF_CRC_SLP_N_LEN)-1)<<EF_CTRL_EF_CRC_SLP_N_POS)
#define EF_CTRL_EF_CRC_SLP_N_UMSK                               (~(((1U<<EF_CTRL_EF_CRC_SLP_N_LEN)-1)<<EF_CTRL_EF_CRC_SLP_N_POS))

/* 0xA04 : ef_crc_ctrl_1 */
#define EF_CTRL_EF_CRC_CTRL_1_OFFSET                            (0xA04)
#define EF_CTRL_EF_CRC_DATA_0_EN                                EF_CTRL_EF_CRC_DATA_0_EN
#define EF_CTRL_EF_CRC_DATA_0_EN_POS                            (0U)
#define EF_CTRL_EF_CRC_DATA_0_EN_LEN                            (32U)
#define EF_CTRL_EF_CRC_DATA_0_EN_MSK                            (((1U<<EF_CTRL_EF_CRC_DATA_0_EN_LEN)-1)<<EF_CTRL_EF_CRC_DATA_0_EN_POS)
#define EF_CTRL_EF_CRC_DATA_0_EN_UMSK                           (~(((1U<<EF_CTRL_EF_CRC_DATA_0_EN_LEN)-1)<<EF_CTRL_EF_CRC_DATA_0_EN_POS))

/* 0xA08 : ef_crc_ctrl_2 */
#define EF_CTRL_EF_CRC_CTRL_2_OFFSET                            (0xA08)
#define EF_CTRL_EF_CRC_DATA_1_EN                                EF_CTRL_EF_CRC_DATA_1_EN
#define EF_CTRL_EF_CRC_DATA_1_EN_POS                            (0U)
#define EF_CTRL_EF_CRC_DATA_1_EN_LEN                            (32U)
#define EF_CTRL_EF_CRC_DATA_1_EN_MSK                            (((1U<<EF_CTRL_EF_CRC_DATA_1_EN_LEN)-1)<<EF_CTRL_EF_CRC_DATA_1_EN_POS)
#define EF_CTRL_EF_CRC_DATA_1_EN_UMSK                           (~(((1U<<EF_CTRL_EF_CRC_DATA_1_EN_LEN)-1)<<EF_CTRL_EF_CRC_DATA_1_EN_POS))

/* 0xA0C : ef_crc_ctrl_3 */
#define EF_CTRL_EF_CRC_CTRL_3_OFFSET                            (0xA0C)
#define EF_CTRL_EF_CRC_IV                                       EF_CTRL_EF_CRC_IV
#define EF_CTRL_EF_CRC_IV_POS                                   (0U)
#define EF_CTRL_EF_CRC_IV_LEN                                   (32U)
#define EF_CTRL_EF_CRC_IV_MSK                                   (((1U<<EF_CTRL_EF_CRC_IV_LEN)-1)<<EF_CTRL_EF_CRC_IV_POS)
#define EF_CTRL_EF_CRC_IV_UMSK                                  (~(((1U<<EF_CTRL_EF_CRC_IV_LEN)-1)<<EF_CTRL_EF_CRC_IV_POS))

/* 0xA10 : ef_crc_ctrl_4 */
#define EF_CTRL_EF_CRC_CTRL_4_OFFSET                            (0xA10)
#define EF_CTRL_EF_CRC_GOLDEN                                   EF_CTRL_EF_CRC_GOLDEN
#define EF_CTRL_EF_CRC_GOLDEN_POS                               (0U)
#define EF_CTRL_EF_CRC_GOLDEN_LEN                               (32U)
#define EF_CTRL_EF_CRC_GOLDEN_MSK                               (((1U<<EF_CTRL_EF_CRC_GOLDEN_LEN)-1)<<EF_CTRL_EF_CRC_GOLDEN_POS)
#define EF_CTRL_EF_CRC_GOLDEN_UMSK                              (~(((1U<<EF_CTRL_EF_CRC_GOLDEN_LEN)-1)<<EF_CTRL_EF_CRC_GOLDEN_POS))

/* 0xA14 : ef_crc_ctrl_5 */
#define EF_CTRL_EF_CRC_CTRL_5_OFFSET                            (0xA14)
#define EF_CTRL_EF_CRC_DOUT                                     EF_CTRL_EF_CRC_DOUT
#define EF_CTRL_EF_CRC_DOUT_POS                                 (0U)
#define EF_CTRL_EF_CRC_DOUT_LEN                                 (32U)
#define EF_CTRL_EF_CRC_DOUT_MSK                                 (((1U<<EF_CTRL_EF_CRC_DOUT_LEN)-1)<<EF_CTRL_EF_CRC_DOUT_POS)
#define EF_CTRL_EF_CRC_DOUT_UMSK                                (~(((1U<<EF_CTRL_EF_CRC_DOUT_LEN)-1)<<EF_CTRL_EF_CRC_DOUT_POS))


struct  ef_ctrl_reg {
    /* 0x0  reserved */
    uint8_t RESERVED0x0[2048];

    /* 0x800 : ef_if_ctrl_0 */
    union {
        struct {
            uint32_t ef_if_0_autoload_p1_done       :  1; /* [    0],          r,        0x1 */
            uint32_t ef_if_0_autoload_done          :  1; /* [    1],          r,        0x1 */
            uint32_t ef_if_0_busy                   :  1; /* [    2],          r,        0x0 */
            uint32_t ef_if_0_rw                     :  1; /* [    3],        r/w,        0x0 */
            uint32_t ef_if_0_trig                   :  1; /* [    4],        r/w,        0x0 */
            uint32_t ef_if_0_manual_en              :  1; /* [    5],        r/w,        0x0 */
            uint32_t ef_if_0_cyc_modify             :  1; /* [    6],        r/w,        0x0 */
            uint32_t ef_clk_sahb_data_sel           :  1; /* [    7],        r/w,        0x0 */
            uint32_t ef_if_prot_code_ctrl           :  8; /* [15: 8],        r/w,        0x0 */
            uint32_t ef_if_por_dig                  :  1; /* [   16],        r/w,        0x0 */
            uint32_t ef_clk_sahb_data_gate          :  1; /* [   17],        r/w,        0x0 */
            uint32_t ef_if_auto_rd_en               :  1; /* [   18],        r/w,        0x1 */
            uint32_t ef_if_cyc_modify_lock          :  1; /* [   19],        r/w,        0x0 */
            uint32_t ef_if_0_int                    :  1; /* [   20],          r,        0x0 */
            uint32_t ef_if_0_int_clr                :  1; /* [   21],        r/w,        0x1 */
            uint32_t ef_if_0_int_set                :  1; /* [   22],        r/w,        0x0 */
            uint32_t reserved_23                    :  1; /* [   23],       rsvd,        0x0 */
            uint32_t ef_if_prot_code_cyc            :  8; /* [31:24],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_if_ctrl_0;

    /* 0x804 : ef_if_cyc_0 */
    union {
        struct {
            uint32_t ef_if_cyc_rd_dmy               :  6; /* [ 5: 0],        r/w,        0x0 */
            uint32_t ef_if_cyc_rd_dat               :  6; /* [11: 6],        r/w,        0x1 */
            uint32_t ef_if_cyc_rd_adr               :  6; /* [17:12],        r/w,        0x0 */
            uint32_t ef_if_cyc_cs                   :  6; /* [23:18],        r/w,        0x0 */
            uint32_t ef_if_cyc_pd_cs_s              :  8; /* [31:24],        r/w,       0x16 */
        }BF;
        uint32_t WORD;
    } ef_if_cyc_0;

    /* 0x808 : ef_if_cyc_1 */
    union {
        struct {
            uint32_t ef_if_cyc_pi                   :  6; /* [ 5: 0],        r/w,        0x9 */
            uint32_t ef_if_cyc_pp                   :  8; /* [13: 6],        r/w,       0x98 */
            uint32_t ef_if_cyc_wr_adr               :  6; /* [19:14],        r/w,        0x1 */
            uint32_t ef_if_cyc_ps_cs                :  6; /* [25:20],        r/w,        0x2 */
            uint32_t ef_if_cyc_pd_cs_h              :  6; /* [31:26],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_if_cyc_1;

    /* 0x80C : ef_if_0_manual */
    union {
        struct {
            uint32_t ef_if_a                        : 10; /* [ 9: 0],        r/w,        0x0 */
            uint32_t ef_if_pd                       :  1; /* [   10],        r/w,        0x1 */
            uint32_t ef_if_ps                       :  1; /* [   11],        r/w,        0x0 */
            uint32_t ef_if_strobe                   :  1; /* [   12],        r/w,        0x0 */
            uint32_t ef_if_pgenb                    :  1; /* [   13],        r/w,        0x1 */
            uint32_t ef_if_load                     :  1; /* [   14],        r/w,        0x1 */
            uint32_t ef_if_csb                      :  1; /* [   15],        r/w,        0x1 */
            uint32_t ef_if_0_q                      :  8; /* [23:16],          r,        0x0 */
            uint32_t ef_if_prot_code_manual         :  8; /* [31:24],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_if_0_manual;

    /* 0x810 : ef_if_0_status */
    union {
        struct {
            uint32_t ef_if_0_status                 : 32; /* [31: 0],          r,     0xe400 */
        }BF;
        uint32_t WORD;
    } ef_if_0_status;

    /* 0x814 : ef_if_cfg_0 */
    union {
        struct {
            uint32_t ef_if_sf_aes_mode              :  2; /* [ 1: 0],          r,        0x0 */
            uint32_t ef_if_ai_dis                   :  1; /* [    2],          r,        0x0 */
            uint32_t ef_if_cpu0_dis                 :  1; /* [    3],          r,        0x0 */
            uint32_t ef_if_sboot_en                 :  2; /* [ 5: 4],          r,        0x0 */
            uint32_t ef_if_uart_dis                 :  4; /* [ 9: 6],          r,        0x0 */
            uint32_t ef_if_ble2_dis                 :  1; /* [   10],          r,        0x0 */
            uint32_t ef_if_m1542_dis                :  1; /* [   11],          r,        0x0 */
            uint32_t ef_if_sf_key_re_sel            :  2; /* [13:12],          r,        0x0 */
            uint32_t ef_if_sdu_dis                  :  1; /* [   14],          r,        0x0 */
            uint32_t ef_if_btdm_dis                 :  1; /* [   15],          r,        0x0 */
            uint32_t ef_if_wifi_dis                 :  1; /* [   16],          r,        0x0 */
            uint32_t ef_if_0_key_enc_en             :  1; /* [   17],          r,        0x0 */
            uint32_t ef_if_cam_dis                  :  1; /* [   18],          r,        0x0 */
            uint32_t ef_if_m154_dis                 :  1; /* [   19],          r,        0x0 */
            uint32_t ef_if_cpu1_dis                 :  1; /* [   20],          r,        0x0 */
            uint32_t ef_if_cpu_rst_dbg_dis          :  1; /* [   21],          r,        0x0 */
            uint32_t ef_if_se_dbg_dis               :  1; /* [   22],          r,        0x0 */
            uint32_t ef_if_efuse_dbg_dis            :  1; /* [   23],          r,        0x0 */
            uint32_t ef_if_dbg_jtag_1_dis           :  2; /* [25:24],          r,        0x0 */
            uint32_t ef_if_dbg_jtag_0_dis           :  2; /* [27:26],          r,        0x0 */
            uint32_t ef_if_dbg_mode                 :  4; /* [31:28],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_if_cfg_0;

    /* 0x818 : ef_sw_cfg_0 */
    union {
        struct {
            uint32_t ef_sw_sf_aes_mode              :  2; /* [ 1: 0],        r/w,        0x0 */
            uint32_t ef_sw_ai_dis                   :  1; /* [    2],        r/w,        0x0 */
            uint32_t ef_sw_cpu0_dis                 :  1; /* [    3],        r/w,        0x0 */
            uint32_t ef_sw_sboot_en                 :  2; /* [ 5: 4],        r/w,        0x0 */
            uint32_t ef_sw_uart_dis                 :  4; /* [ 9: 6],        r/w,        0x0 */
            uint32_t ef_sw_ble2_dis                 :  1; /* [   10],        r/w,        0x0 */
            uint32_t ef_sw_m1542_dis                :  1; /* [   11],        r/w,        0x0 */
            uint32_t ef_sw_sf_key_re_sel            :  2; /* [13:12],        r/w,        0x0 */
            uint32_t ef_sw_sdu_dis                  :  1; /* [   14],        r/w,        0x0 */
            uint32_t ef_sw_btdm_dis                 :  1; /* [   15],        r/w,        0x0 */
            uint32_t ef_sw_wifi_dis                 :  1; /* [   16],        r/w,        0x0 */
            uint32_t ef_sw_0_key_enc_en             :  1; /* [   17],        r/w,        0x0 */
            uint32_t ef_sw_cam_dis                  :  1; /* [   18],        r/w,        0x0 */
            uint32_t ef_sw_m154_dis                 :  1; /* [   19],        r/w,        0x0 */
            uint32_t ef_sw_cpu1_dis                 :  1; /* [   20],        r/w,        0x0 */
            uint32_t ef_sw_cpu_rst_dbg_dis          :  1; /* [   21],        r/w,        0x0 */
            uint32_t ef_sw_se_dbg_dis               :  1; /* [   22],        r/w,        0x0 */
            uint32_t ef_sw_efuse_dbg_dis            :  1; /* [   23],        r/w,        0x0 */
            uint32_t ef_sw_dbg_jtag_1_dis           :  2; /* [25:24],        r/w,        0x0 */
            uint32_t ef_sw_dbg_jtag_0_dis           :  2; /* [27:26],        r/w,        0x0 */
            uint32_t ef_sw_dbg_mode                 :  4; /* [31:28],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_sw_cfg_0;

    /* 0x81C : ef_reserved */
    union {
        struct {
            uint32_t ef_reserved                    : 32; /* [31: 0],        r/w,     0xffff */
        }BF;
        uint32_t WORD;
    } ef_reserved;

    /* 0x820 : ef_if_ana_trim_0 */
    union {
        struct {
            uint32_t ef_if_ana_trim_0               : 32; /* [31: 0],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_if_ana_trim_0;

    /* 0x824 : ef_if_sw_usage_0 */
    union {
        struct {
            uint32_t ef_if_sw_usage_0               : 32; /* [31: 0],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_if_sw_usage_0;

    /* 0x828  reserved */
    uint8_t RESERVED0x828[216];

    /* 0x900 : ef_if_ctrl_1 */
    union {
        struct {
            uint32_t reserved_0_1                   :  2; /* [ 1: 0],       rsvd,        0x0 */
            uint32_t ef_if_1_busy                   :  1; /* [    2],          r,        0x0 */
            uint32_t ef_if_1_rw                     :  1; /* [    3],        r/w,        0x0 */
            uint32_t ef_if_1_trig                   :  1; /* [    4],        r/w,        0x0 */
            uint32_t ef_if_1_manual_en              :  1; /* [    5],        r/w,        0x0 */
            uint32_t ef_if_1_cyc_modify             :  1; /* [    6],        r/w,        0x0 */
            uint32_t reserved_7_19                  : 13; /* [19: 7],       rsvd,        0x0 */
            uint32_t ef_if_1_int                    :  1; /* [   20],          r,        0x0 */
            uint32_t ef_if_1_int_clr                :  1; /* [   21],        r/w,        0x1 */
            uint32_t ef_if_1_int_set                :  1; /* [   22],        r/w,        0x0 */
            uint32_t reserved_23_31                 :  9; /* [31:23],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_if_ctrl_1;

    /* 0x904 : ef_if_1_manual */
    union {
        struct {
            uint32_t reserved_0_15                  : 16; /* [15: 0],       rsvd,        0x0 */
            uint32_t ef_if_1_q                      :  8; /* [23:16],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_if_1_manual;

    /* 0x908 : ef_if_1_status */
    union {
        struct {
            uint32_t ef_if_1_status                 : 32; /* [31: 0],          r,     0xe400 */
        }BF;
        uint32_t WORD;
    } ef_if_1_status;

    /* 0x90c  reserved */
    uint8_t RESERVED0x90c[4];

    /* 0x910 : ef_if_ctrl_2 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_if_ctrl_2;

    /* 0x914 : ef_if_2_manual */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_if_2_manual;

    /* 0x918 : ef_if_2_status */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_if_2_status;

    /* 0x91c  reserved */
    uint8_t RESERVED0x91c[228];

    /* 0xA00 : ef_crc_ctrl_0 */
    union {
        struct {
            uint32_t ef_crc_busy                    :  1; /* [    0],          r,        0x0 */
            uint32_t ef_crc_trig                    :  1; /* [    1],        r/w,        0x0 */
            uint32_t ef_crc_en                      :  1; /* [    2],        r/w,        0x1 */
            uint32_t ef_crc_mode                    :  1; /* [    3],        r/w,        0x0 */
            uint32_t ef_crc_error                   :  1; /* [    4],          r,        0x0 */
            uint32_t ef_crc_dout_inv_en             :  1; /* [    5],        r/w,        0x1 */
            uint32_t ef_crc_dout_endian             :  1; /* [    6],        r/w,        0x0 */
            uint32_t ef_crc_din_endian              :  1; /* [    7],        r/w,        0x0 */
            uint32_t ef_crc_int                     :  1; /* [    8],          r,        0x0 */
            uint32_t ef_crc_int_clr                 :  1; /* [    9],        r/w,        0x1 */
            uint32_t ef_crc_int_set                 :  1; /* [   10],        r/w,        0x0 */
            uint32_t ef_crc_lock                    :  1; /* [   11],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t ef_crc_slp_n                   : 16; /* [31:16],        r/w,       0xff */
        }BF;
        uint32_t WORD;
    } ef_crc_ctrl_0;

    /* 0xA04 : ef_crc_ctrl_1 */
    union {
        struct {
            uint32_t ef_crc_data_0_en               : 32; /* [31: 0],        r/w, 0xffffffff */
        }BF;
        uint32_t WORD;
    } ef_crc_ctrl_1;

    /* 0xA08 : ef_crc_ctrl_2 */
    union {
        struct {
            uint32_t ef_crc_data_1_en               : 32; /* [31: 0],        r/w, 0xffffffff */
        }BF;
        uint32_t WORD;
    } ef_crc_ctrl_2;

    /* 0xA0C : ef_crc_ctrl_3 */
    union {
        struct {
            uint32_t ef_crc_iv                      : 32; /* [31: 0],        r/w, 0xffffffff */
        }BF;
        uint32_t WORD;
    } ef_crc_ctrl_3;

    /* 0xA10 : ef_crc_ctrl_4 */
    union {
        struct {
            uint32_t ef_crc_golden                  : 32; /* [31: 0],        r/w, 0xc2a8fa9d */
        }BF;
        uint32_t WORD;
    } ef_crc_ctrl_4;

    /* 0xA14 : ef_crc_ctrl_5 */
    union {
        struct {
            uint32_t ef_crc_dout                    : 32; /* [31: 0],          r, 0xffffffff */
        }BF;
        uint32_t WORD;
    } ef_crc_ctrl_5;

};

typedef volatile struct ef_ctrl_reg ef_ctrl_reg_t;


#endif  /* __EF_CTRL_REG_H__ */
