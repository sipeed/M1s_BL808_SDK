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
#ifndef __USB_MEM_H__
#define __USB_MEM_H__

#include "bflb_bsp_driver_glue.h"
#include "usbd_def.h"

//#define USB_USE_DMA

#define USB_DATA_SPACE_LENGTH                   (4*1024)

#define USB_IN_STAGE_CHANNEL                    (DMA_CH5)
#define USB_IN_STAGE_CHANNEL_CTRL               (0x40007610)
#define USB_IN_STAGE_FIFO_ADDR                  (0x4000DB28)

#define USB_OUT_STAGE_CHANNEL                   (DMA_CH6)
#define USB_OUT_STAGE_CHANNEL_CTRL              (0x4000770C)
#define USB_OUT_STAGE_FIFO_ADDR                 (0x4000DB1C)

#define USB_IN_Stage_DMA_BUSY()                 DMA_Channel_Is_Busy(USB_IN_STAGE_CHANNEL)
#define USB_OUT_Stage_DMA_BUSY()                DMA_Channel_Is_Busy(USB_OUT_STAGE_CHANNEL)

extern uint8_t USB_Date_Space[USB_DATA_SPACE_LENGTH];
extern uint32_t USB_Date_Space_Head_Addr;
extern uint32_t USB_Date_Space_Limit_Addr;
extern uint32_t USB_Date_Space_Tail_Addr;
extern uint8_t *pInSpace;
extern uint8_t *pOutSpace;
extern uint8_t *pHeadSpace;
extern uint8_t *pLimitSpace;
extern uint8_t *pTailSpace;
extern DMA_Channel_Cfg_Type inCfg;
extern DMA_Channel_Cfg_Type outCfg;

void USB_INOUT_MEM_Init(void);

void USB_IN_Stage_DMA_Init(void);
void USB_IN_Stage_DMA_Start(uint32_t srcAddr,uint16_t len);
uint32_t USB_IN_Stage_DMA_Data_Left_Num(void);
void USB_IN_Stage_DMA_Stop(void);

void USB_OUT_Stage_DMA_Init(void);
void USB_OUT_Stage_DMA_Start(uint32_t dstAddr,uint16_t len);
uint32_t USB_OUT_Stage_DMA_Data_Left_Num(void);
void USB_OUT_Stage_DMA_Stop(void);

#endif

