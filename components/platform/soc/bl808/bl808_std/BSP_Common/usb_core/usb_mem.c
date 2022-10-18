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
#include "usb_mem.h"

uint8_t USB_Date_Space[USB_DATA_SPACE_LENGTH] = {0};
uint32_t USB_Date_Space_Head_Addr = 0;
uint32_t USB_Date_Space_Limit_Addr = 0;
uint32_t USB_Date_Space_Tail_Addr = 0;
uint8_t *pInSpace = NULL;
uint8_t *pOutSpace = NULL;
uint8_t *pHeadSpace = NULL;
uint8_t *pLimitSpace = NULL;
uint8_t *pTailSpace = NULL;
DMA_Channel_Cfg_Type inCfg = {
    .srcDmaAddr = (uint32_t)0,
    .destDmaAddr = (uint32_t)USB_IN_STAGE_FIFO_ADDR,
    .transfLength = 0,
    .dir = DMA_TRNS_M2P,
    .ch = USB_IN_STAGE_CHANNEL,
    .srcTransfWidth = DMA_TRNS_WIDTH_8BITS,
    .dstTransfWidth = DMA_TRNS_WIDTH_8BITS,
    .srcBurstSzie = DMA_BURST_SIZE_1,
    .dstBurstSzie = DMA_BURST_SIZE_1,
    .dstAddMode = DISABLE,
    .dstMinMode = DISABLE,
    .fixCnt = 0,
    .srcAddrInc = 1,
    .destAddrInc = 0,
    .srcPeriph = DMA_REQ_NONE,              /* none?? */
    .dstPeriph = 26,              /* none?? */
};
DMA_Channel_Cfg_Type outCfg = {
    .srcDmaAddr = (uint32_t)USB_OUT_STAGE_FIFO_ADDR,
    .destDmaAddr = (uint32_t)0,
    .transfLength = 0,
    .dir = DMA_TRNS_P2M,
    .ch = USB_OUT_STAGE_CHANNEL,
    .srcTransfWidth = DMA_TRNS_WIDTH_8BITS,
    .dstTransfWidth = DMA_TRNS_WIDTH_8BITS,
    .srcBurstSzie = DMA_BURST_SIZE_1,
    .dstBurstSzie = DMA_BURST_SIZE_1,
    .dstAddMode = DISABLE,
    .dstMinMode = DISABLE,
    .fixCnt = 0,
    .srcAddrInc = 0,
    .destAddrInc = 1,
    .srcPeriph = 25,              /* none?? */
    .dstPeriph = DMA_REQ_NONE,              /* none?? */
};


void USB_INOUT_MEM_Init(void)
{
    memset(USB_Date_Space,0,USB_DATA_SPACE_LENGTH);
    USB_Date_Space_Head_Addr = (uint32_t)&(USB_Date_Space[0]);
    USB_Date_Space_Limit_Addr = (uint32_t)&(USB_Date_Space[USB_DATA_SPACE_LENGTH-1-USB_FS_MAX_PACKET_SIZE-USB_FS_MAX_PACKET_SIZE-4]);
    USB_Date_Space_Tail_Addr = (uint32_t)&(USB_Date_Space[USB_DATA_SPACE_LENGTH-1]);
    pHeadSpace = (uint8_t *)USB_Date_Space_Head_Addr;
    pLimitSpace = (uint8_t *)USB_Date_Space_Limit_Addr;
    pTailSpace = (uint8_t *)USB_Date_Space_Tail_Addr;
    pInSpace = pHeadSpace;
    pOutSpace = pHeadSpace;
}

/* IN stage DMA init */
void USB_IN_Stage_DMA_Init(void)
{
    GLB_Set_DMA_CLK(ENABLE,GLB_DMA_CLK_DMA0_CH5);
    GLB_Set_DMA_CLK(ENABLE,GLB_DMA_CLK_DMA0_CH6);
    DMA_Disable();
    DMA_Channel_Disable(USB_IN_STAGE_CHANNEL);
    DMA_Channel_Init(&inCfg);
    DMA_IntMask(USB_IN_STAGE_CHANNEL, DMA_INT_ALL, MASK);
    DMA_Enable();
}

/* IN stage DMA start */
void USB_IN_Stage_DMA_Start(uint32_t srcAddr,uint16_t len)
{
    DMA_Channel_Update_SrcMemcfg(USB_IN_STAGE_CHANNEL, srcAddr, len);
    DMA_Channel_Enable(USB_IN_STAGE_CHANNEL);
}

/* IN stage DMA data left to transfer */
uint32_t USB_IN_Stage_DMA_Data_Left_Num(void)
{
    return (*(uint32_t *)(USB_IN_STAGE_CHANNEL_CTRL))&0xFFF;
}

/* IN stage DMA stop */
void USB_IN_Stage_DMA_Stop(void)
{
    DMA_Channel_Disable(USB_IN_STAGE_CHANNEL);
}

/* OUT stage DMA init */
void USB_OUT_Stage_DMA_Init(void)
{
    DMA_Disable();
    DMA_Channel_Disable(USB_OUT_STAGE_CHANNEL);
    DMA_Channel_Init(&outCfg);
    DMA_IntMask(USB_OUT_STAGE_CHANNEL, DMA_INT_ALL, MASK);
    DMA_Enable();
}

/* OUT stage DMA start */
void USB_OUT_Stage_DMA_Start(uint32_t dstAddr,uint16_t len)
{
    DMA_Channel_Update_DstMemcfg(USB_OUT_STAGE_CHANNEL, dstAddr, len);
    DMA_Channel_Enable(USB_OUT_STAGE_CHANNEL);
}

/* OUT stage DMA data left to transfer */
uint32_t USB_OUT_Stage_DMA_Data_Left_Num(void)
{
    return (*(uint32_t *)(USB_OUT_STAGE_CHANNEL_CTRL))&0xFFF;
}

/* OUT stage DMA stop */
void USB_OUT_Stage_DMA_Stop(void)
{
    DMA_Channel_Disable(USB_OUT_STAGE_CHANNEL);
}







