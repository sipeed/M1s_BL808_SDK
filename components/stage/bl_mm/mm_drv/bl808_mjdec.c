#include <bl808_comm_mm.h>
#include "bl808_mjdec.h"
#include <mjdec_reg.h>

#undef  DEBUG_MODULE
#define DEBUG_MODULE 0



void MJDEC_Init(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_DEC_BASE, MJDEC_JDEC_CONTROL_1);
    tmpVal = BL_SET_REG_BIT(tmpVal, MJDEC_REG_U_EVEN);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJDEC_REG_W_XLEN, AXI_XLEN_INCR16);
    tmpVal = BL_CLR_REG_BIT(tmpVal, MJDEC_REG_MJ_DEC_ENABLE);
    BL_WR_REG(MJPEG_DEC_BASE, MJDEC_JDEC_CONTROL_1, tmpVal);

    tmpVal = BL_RD_REG(MJPEG_DEC_BASE, MJDEC_JDEC_CONTROL_3);
    tmpVal = BL_SET_REG_BIT(tmpVal, MJDEC_REG_INT_NORMAL_EN);
    tmpVal = BL_SET_REG_BIT(tmpVal, MJDEC_REG_INT_IDLE_EN);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJDEC_REG_FRAME_CNT_TRGR_INT, 1);  /* trigger interrupt every frame */
    BL_WR_REG(MJPEG_DEC_BASE, MJDEC_JDEC_CONTROL_3, tmpVal);
}

void MJDEC_SetYuvFormat(MJDEC_YUV_Format_Type format)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_DEC_BASE, MJDEC_JDEC_CONTROL_1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJDEC_REG_YUV_MODE, format);
    BL_WR_REG(MJPEG_DEC_BASE, MJDEC_JDEC_CONTROL_1, tmpVal);
}

void MJDEC_SetResolution(uint32_t width, uint32_t height)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_DEC_BASE, MJDEC_JDEC_FRAME_SIZE);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJDEC_REG_FRAME_WBLK, BLK_CNT_16X16(width));
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJDEC_REG_FRAME_HBLK, BLK_CNT_16X16(height));
    BL_WR_REG(MJPEG_DEC_BASE, MJDEC_JDEC_FRAME_SIZE, tmpVal);

    tmpVal = BL_RD_REG(MJPEG_DEC_BASE, MJDEC_JDEC_CONTROL_1);
    if (IS_MULTIPULE_OF_16(height)) {
        tmpVal = BL_CLR_REG_BIT(tmpVal, MJDEC_REG_LAST_HF_HBLK_DMY);
    } else {
        tmpVal = BL_SET_REG_BIT(tmpVal, MJDEC_REG_LAST_HF_HBLK_DMY);
    }
    BL_WR_REG(MJPEG_DEC_BASE, MJDEC_JDEC_CONTROL_1, tmpVal);
}

void MJDEC_PushSrcFrame(uint32_t bufAddr)
{
    uint32_t tmpVal;

    /* check if buffer is aligned to 128 bytes boundary */
    CHECK_PARAM((bufAddr & AXI_BURST_INCR16_ALIGNMENT_MASK) == 0 );

    tmpVal = BL_RD_REG(MJPEG_DEC_BASE, MJDEC_JDEC_FRAM_PUSH);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJDEC_REG_JP_ADDR, bufAddr >> 2);
    tmpVal = BL_SET_REG_BIT(tmpVal, MJDEC_REG_JP_PUSH);
    BL_WR_REG(MJPEG_DEC_BASE, MJDEC_JDEC_FRAM_PUSH, tmpVal);
}

void MJDEC_SetYFrameAddr(uint32_t bufAddr)
{
    /* check if buffer is aligned to 128 bytes boundary */
    CHECK_PARAM((bufAddr & AXI_BURST_INCR16_ALIGNMENT_MASK) == 0 );

    BL_WR_REG(MJPEG_DEC_BASE, MJDEC_JDEC_YY_FRAME_ADDR, bufAddr);
}

void MJDEC_SetUVFrameAddr(uint32_t bufAddr)
{
    /* check if buffer is aligned to 128 bytes boundary */
    CHECK_PARAM((bufAddr & AXI_BURST_INCR16_ALIGNMENT_MASK) == 0 );

    BL_WR_REG(MJPEG_DEC_BASE, MJDEC_JDEC_UV_FRAME_ADDR, bufAddr);
}

void MJDEC_SetQuality(MJDEC_Quant_Mode_Type quality)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_DEC_BASE, MJDEC_JDEC_CONTROL_1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJDEC_REG_Q_MODE, quality);
    BL_WR_REG(MJPEG_DEC_BASE, MJDEC_JDEC_CONTROL_1, tmpVal);
}

void MJDEC_StartDec(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_DEC_BASE, MJDEC_JDEC_CONTROL_1);
    tmpVal = BL_SET_REG_BIT(tmpVal, MJDEC_REG_MJ_DEC_ENABLE);
    BL_WR_REG(MJPEG_DEC_BASE, MJDEC_JDEC_CONTROL_1, tmpVal);
}

void MJDEC_StopDec(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_DEC_BASE, MJDEC_JDEC_CONTROL_1);
    tmpVal = BL_CLR_REG_BIT(tmpVal, MJDEC_REG_MJ_DEC_ENABLE);
    BL_WR_REG(MJPEG_DEC_BASE, MJDEC_JDEC_CONTROL_1, tmpVal);
}

void MJDEC_PopStreamFifo(void)
{
}

void MJDEC_ClearIntrFlag(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_DEC_BASE, MJDEC_JDEC_INT_CLR);
    tmpVal = BL_SET_REG_BIT(tmpVal, MJDEC_REG_INT_CLR);
    BL_WR_REG(MJPEG_DEC_BASE, MJDEC_JDEC_INT_CLR, tmpVal);
}

