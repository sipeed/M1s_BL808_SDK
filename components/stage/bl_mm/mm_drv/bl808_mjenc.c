#include "bl808_mjenc.h"
#include "mjenc_reg.h"
#include "mjenc_q_sram_reg.h"

#undef  DEBUG_MODULE
#define DEBUG_MODULE 0

//#define DEBUG_QTABLE

#define BL_BIT_SET(val, bit)    val | (1 << bit)

void MJENC_Init(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_MJPEG_CONTROL_1);
    tmpVal = BL_SET_REG_BIT(tmpVal, MJENC_REG_MJPEG_BIT_ORDER);
    tmpVal = BL_SET_REG_BIT(tmpVal, MJENC_REG_ORDER_U_EVEN);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_REG_W_XLEN, AXI_XLEN_INCR16);
    tmpVal = BL_CLR_REG_BIT(tmpVal, MJENC_REG_MJPEG_ENABLE);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_MJPEG_CONTROL_1, tmpVal);

    /* sw mode related */
    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_MJPEG_CONTROL_2);
    tmpVal = BL_CLR_REG_BIT(tmpVal, MJENC_REG_MJPEG_SW_MODE);
    tmpVal = BL_CLR_REG_BIT(tmpVal, MJENC_REG_MJPEG_SW_RUN);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_REG_SW_FRAME, 10);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_REG_MJPEG_WAIT_CYCLE, 400);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_MJPEG_CONTROL_2, tmpVal);

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_MJPEG_CONTROL_3);
    tmpVal = BL_SET_REG_BIT(tmpVal, MJENC_REG_INT_NORMAL_EN);
    tmpVal = BL_CLR_REG_BIT(tmpVal, MJENC_REG_INT_CAM_EN);
    tmpVal = BL_CLR_REG_BIT(tmpVal, MJENC_REG_INT_MEM_EN);
    tmpVal = BL_SET_REG_BIT(tmpVal, MJENC_REG_INT_FRAME_EN);
    tmpVal = BL_SET_REG_BIT(tmpVal, MJENC_REG_INT_IDLE_EN);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_REG_FRAME_CNT_TRGR_INT, 1);  /* trigger interrupt every frame */
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_MJPEG_CONTROL_3, tmpVal);

#if (MJPG_AUTO_HEADER)
    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_MJPEG_HEADER_BYTE);
    tmpVal = BL_SET_REG_BIT(tmpVal, MJENC_REG_TAIL_EXP);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_MJPEG_HEADER_BYTE, tmpVal);
#endif
}

void MJENC_SetHeaderSize(uint32_t size)
{
#if (MJPG_AUTO_HEADER)
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_MJPEG_HEADER_BYTE);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_REG_HEAD_BYTE, size);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_MJPEG_HEADER_BYTE, tmpVal);
#endif
}

void MJENC_SetResolution(const MJPEG_Cfg_Type *cfg)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_MJPEG_CONTROL_1);
    if (IS_MULTIPULE_OF_16(cfg->height)) {
        tmpVal = BL_CLR_REG_BIT(tmpVal, MJENC_REG_LAST_HF_HBLK_DMY);
#if (BL80X_HW_VER >= BL80X_HW_B0)
        tmpVal = BL_CLR_REG_BIT(tmpVal, MJENC_REG_REFLECT_DMY);
#endif
    } else {
        tmpVal = BL_SET_REG_BIT(tmpVal, MJENC_REG_LAST_HF_HBLK_DMY);
#if (BL80X_HW_VER >= BL80X_HW_B0)
        tmpVal = BL_SET_REG_BIT(tmpVal, MJENC_REG_REFLECT_DMY);
#endif
    }
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_MJPEG_CONTROL_1, tmpVal);

    /* resolution related */
#if (BL80X_HW_VER <= BL80X_HW_A0)
    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_MJPEG_CONTROL_1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_REG_FRAME_WBLK, BLK_CNT_16X16(cfg->width));
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_REG_FRAME_HBLK, BLK_CNT_16X16(cfg->height));
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_MJPEG_CONTROL_1, tmpVal);
#else
    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_MJPEG_FRAME_SIZE);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_REG_FRAME_WBLK, BLK_CNT_16X16(cfg->width));
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_REG_FRAME_HBLK, BLK_CNT_16X16(cfg->height));
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_MJPEG_FRAME_SIZE, tmpVal);
#endif
}

void MJENC_SetSrcChannel(MJPEG_Src_Chann_Cfg_Type *portCfg)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_MJPEG_CONTROL_2);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_REG_YY_DVP2AXI_SEL, portCfg->y_src);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_REG_UV_DVP2AXI_SEL, portCfg->uv_src);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_MJPEG_CONTROL_2, tmpVal);
}

void MJENC_SetSrcBuf_Y(uint32_t bufAddr, uint16_t blkRowCnt)
{
    uint32_t tmpVal;

    /* check if buffer is aligned to 128 bytes boundary */
    CHECK_PARAM((bufAddr & AXI_BURST_INCR16_ALIGNMENT_MASK) == 0 );

    BL_WR_REG(MJPEG_ENC_BASE, MJENC_MJPEG_YY_FRAME_ADDR, bufAddr);

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_MJPEG_YUV_MEM);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_REG_YY_MEM_HBLK, blkRowCnt);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_MJPEG_YUV_MEM, tmpVal);
}

void MJENC_SetSrcBuf_UV(uint32_t bufAddr, uint16_t blkRowCnt)
{
    uint32_t tmpVal;

    /* check if buffer is aligned to 128 bytes boundary */
    CHECK_PARAM((bufAddr & AXI_BURST_INCR16_ALIGNMENT_MASK) == 0 );

    BL_WR_REG(MJPEG_ENC_BASE, MJENC_MJPEG_UV_FRAME_ADDR, bufAddr);

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_MJPEG_YUV_MEM);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_REG_UV_MEM_HBLK, blkRowCnt);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_MJPEG_YUV_MEM, tmpVal);
}

void MJENC_SetBitstreamBuf(uint32_t bufAddr, uint32_t bufSize)
{
    /* check if buffer is aligned to 128 bytes boundary */
    CHECK_PARAM((bufAddr & AXI_BURST_INCR16_ALIGNMENT_MASK) == 0 );

    BL_WR_REG(MJPEG_ENC_BASE, MJENC_JPEG_FRAME_ADDR, bufAddr);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_JPEG_STORE_MEMORY, Mem_Size_To_Burst_Cnt(bufSize, AXI_XLEN_INCR16));
}

void MJENC_SetQuality(MJPEG_Quant_Mode_Type quality)
{
#if 0
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_MJPEG_CONTROL_1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_REG_Q_MODE, quality);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_MJPEG_CONTROL_1, tmpVal);
#endif
}

/* FSM for MJPEG encoder
    stop / done with sw_frame_num -> flush state -> idle state -> check sw_mode ->
        0: check mjpeg_enable
            1: -> function state 
        1: set state (ignore mjpeg_enable)-> check sw run
            1: -> sw run state 
*/
void MJENC_StartEnc(MJPEG_Enc_Mode_Type mode)
{
    uint32_t tmpVal;
    if (MJPEG_ENC_SNAPSHOT_MODE == mode) {
        /* enter function state */
        tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_MJPEG_CONTROL_1);
        tmpVal = BL_SET_REG_BIT(tmpVal, MJENC_REG_MJPEG_ENABLE);

#if (BL80X_HW_VER >= BL80X_HW_B0)
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_REG_MJPEG_HW_FRAME, 1);  /* 1 frame only */
#endif
        BL_WR_REG(MJPEG_ENC_BASE, MJENC_MJPEG_CONTROL_1, tmpVal);
    } else if (MJPEG_ENC_AUTO_MODE == mode) {
        /* enter function state */
        tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_MJPEG_CONTROL_1);
        tmpVal = BL_SET_REG_BIT(tmpVal, MJENC_REG_MJPEG_ENABLE);
#if (BL80X_HW_VER >= BL80X_HW_B0)
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_REG_MJPEG_HW_FRAME, 0);  /* non-stop */
#endif
        BL_WR_REG(MJPEG_ENC_BASE, MJENC_MJPEG_CONTROL_1, tmpVal);
    } else {
        /* enter sw set state */
        tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_MJPEG_CONTROL_2);
        tmpVal = BL_SET_REG_BIT(tmpVal, MJENC_REG_MJPEG_SW_MODE);
        BL_WR_REG(MJPEG_ENC_BASE, MJENC_MJPEG_CONTROL_2, tmpVal);

        /* enter sw run state */
        tmpVal = BL_SET_REG_BIT(tmpVal, MJENC_REG_MJPEG_SW_RUN);
        tmpVal = BL_CLR_REG_BIT(tmpVal, MJENC_REG_MJPEG_SW_MODE);
        BL_WR_REG(MJPEG_ENC_BASE, MJENC_MJPEG_CONTROL_2, tmpVal);
    }
}

void MJENC_StopEnc(void)
{
    uint32_t tmpVal;

    /* enter function state */
    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_MJPEG_CONTROL_1);
    tmpVal = BL_CLR_REG_BIT(tmpVal, MJENC_REG_MJPEG_ENABLE);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_MJPEG_CONTROL_1, tmpVal);
}

void MJENC_PopStreamFifo(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_MJPEG_FRAME_FIFO_POP);
    tmpVal = BL_SET_REG_BIT(tmpVal, MJENC_RFIFO_POP);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_MJPEG_FRAME_FIFO_POP, tmpVal);
}

void MJENC_ClearIntrFlag(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_MJPEG_FRAME_FIFO_POP);
    tmpVal = BL_SET_REG_BIT(tmpVal, MJENC_REG_INT_NORMAL_CLR);
    tmpVal = BL_SET_REG_BIT(tmpVal, MJENC_REG_INT_CAM_CLR);
    tmpVal = BL_SET_REG_BIT(tmpVal, MJENC_REG_INT_MEM_CLR);
    tmpVal = BL_SET_REG_BIT(tmpVal, MJENC_REG_INT_FRAME_CLR);
    tmpVal = BL_SET_REG_BIT(tmpVal, MJENC_REG_INT_IDLE_CLR);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_MJPEG_FRAME_FIFO_POP, tmpVal);
}

#ifdef DEBUG_QTABLE
void MJENC_Qtable_debug(uint32_t tmpVal)
{
    static int index = 0;
    BL_LOGI("[%d]:%d\r\n", 2*index, tmpVal&0x0000ffff);
    BL_LOGI("[%d]:%d\r\n", 2*index + 1, tmpVal>>16);
    index++;
}
#endif

void MJENC_SetQTableOffset0(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_00);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_00, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_01, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_00, tmpVal);
    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_00);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_00));
#endif

}

void MJENC_SetQTableOffset1(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_02);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_02, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_03, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_02, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_02));
#endif
}

void MJENC_SetQTableOffset2(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_04);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_04, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_05, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_04, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_04));
#endif

}

void MJENC_SetQTableOffset3(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_06);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_06, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_07, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_06, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_06));
#endif
}

void MJENC_SetQTableOffset4(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_08);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_08, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_09, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_08, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_08));
#endif
}

void MJENC_SetQTableOffset5(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_0A);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_0A, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_0B, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_0A, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_0A));
#endif

}

void MJENC_SetQTableOffset6(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_0C);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_0C, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_0D, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_0C, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_0C));
#endif
}

void MJENC_SetQTableOffset7(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_0E);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_0E, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_0F, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_0E, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_0E));
#endif
}

void MJENC_SetQTableOffset8(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_10);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_10, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_11, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_10, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_10));
#endif
}

void MJENC_SetQTableOffset9(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_12);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_12, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_13, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_12, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_12));
#endif
}

void MJENC_SetQTableOffset10(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_14);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_14, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_15, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_14, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_14));
#endif
}

void MJENC_SetQTableOffset11(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_16);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_16, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_17, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_16, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_16));
#endif
}

void MJENC_SetQTableOffset12(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_18);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_18, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_19, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_18, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_18));
#endif
}

void MJENC_SetQTableOffset13(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_1A);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_1A, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_1B, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_1A, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_1A));
#endif
}

void MJENC_SetQTableOffset14(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_1C);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_1C, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_1D, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_1C, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_1C));
#endif
}

void MJENC_SetQTableOffset15(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_1E);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_1E, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_1F, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_1E, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_1E));
#endif
}

void MJENC_SetQTableOffset16(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_20);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_20, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_21, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_20, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_20));
#endif
}

void MJENC_SetQTableOffset17(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_22);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_22, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_23, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_22, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_22));
#endif
}

void MJENC_SetQTableOffset18(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_24);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_24, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_25, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_24, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_24));
#endif
}

void MJENC_SetQTableOffset19(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_26);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_26, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_27, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_26, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_26));
#endif
}

void MJENC_SetQTableOffset20(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_28);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_28, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_29, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_28, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_28));
#endif
}

void MJENC_SetQTableOffset21(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_2A);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_2A, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_2B, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_2A, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_2A));
#endif
}

void MJENC_SetQTableOffset22(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_2C);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_2C, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_2D, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_2C, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_2C));
#endif
}

void MJENC_SetQTableOffset23(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_2E);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_2E, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_2F, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_2E, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_2E));
#endif
}

void MJENC_SetQTableOffset24(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_30);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_30, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_31, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_30, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_30));
#endif
}

void MJENC_SetQTableOffset25(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_32);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_32, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_33, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_32, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_32));
#endif
}

void MJENC_SetQTableOffset26(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_34);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_34, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_35, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_34, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_34));
#endif
}

void MJENC_SetQTableOffset27(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_36);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_36, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_37, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_36, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_36));
#endif
}

void MJENC_SetQTableOffset28(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_38);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_38, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_39, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_38, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_38));
#endif
}

void MJENC_SetQTableOffset29(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_3A);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_3A, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_3B, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_3A, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_3A));
#endif
}

void MJENC_SetQTableOffset30(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_3C);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_3C, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_3D, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_3C, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_3C));
#endif
}

void MJENC_SetQTableOffset31(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_3E);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_3E, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_0_3F, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_3E, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_3E));
#endif
}

void MJENC_SetQTableOffset32(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_40);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_00, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_01, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_40, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_40));
#endif
}

void MJENC_SetQTableOffset33(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_42);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_02, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_03, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_42, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_42));
#endif
}

void MJENC_SetQTableOffset34(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_44);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_04, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_05, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_44, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_44));
#endif
}

void MJENC_SetQTableOffset35(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_46);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_06, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_07, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_46, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_46));
#endif
}

void MJENC_SetQTableOffset36(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_48);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_08, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_09, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_48, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_48));
#endif
}

void MJENC_SetQTableOffset37(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_4A);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_0A, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_0B, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_4A, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_4A));
#endif
}

void MJENC_SetQTableOffset38(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_4C);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_0C, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_0D, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_4C, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_4C));
#endif
}

void MJENC_SetQTableOffset39(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_4E);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_0E, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_0F, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_4E, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_4E));
#endif
}

void MJENC_SetQTableOffset40(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_50);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_10, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_11, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_50, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_50));
#endif
}

void MJENC_SetQTableOffset41(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_52);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_12, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_13, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_52, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_52));
#endif
}

void MJENC_SetQTableOffset42(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_54);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_14, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_15, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_54, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_54));
#endif
}

void MJENC_SetQTableOffset43(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_56);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_16, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_17, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_56, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_56));
#endif
}

void MJENC_SetQTableOffset44(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_58);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_18, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_19, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_58, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_58));
#endif
}

void MJENC_SetQTableOffset45(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_5A);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_1A, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_1B, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_5A, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_5A));
#endif
}

void MJENC_SetQTableOffset46(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_5C);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_1C, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_1D, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_5C, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_5C));
#endif
}

void MJENC_SetQTableOffset47(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_5E);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_1E, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_1F, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_5E, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_5E));
#endif
}

void MJENC_SetQTableOffset48(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_60);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_20, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_21, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_60, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_60));
#endif
}

void MJENC_SetQTableOffset49(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_62);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_22, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_23, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_62, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_62));
#endif
}

void MJENC_SetQTableOffset50(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_64);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_24, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_25, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_64, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_64));
#endif
}

void MJENC_SetQTableOffset51(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_66);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_26, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_27, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_66, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_66));
#endif
}

void MJENC_SetQTableOffset52(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_68);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_28, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_29, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_68, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_68));
#endif
}

void MJENC_SetQTableOffset53(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_6A);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_2A, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_2B, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_6A, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_6A));
#endif
}

void MJENC_SetQTableOffset54(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_6C);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_2C, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_2D, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_6C, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_6C));
#endif
}

void MJENC_SetQTableOffset55(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_6E);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_2E, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_2F, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_6E, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_6E));
#endif
}

void MJENC_SetQTableOffset56(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_70);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_30, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_31, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_70, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_70));
#endif
}

void MJENC_SetQTableOffset57(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_72);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_32, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_33, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_72, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_72));
#endif
}

void MJENC_SetQTableOffset58(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_74);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_34, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_35, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_74, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_74));
#endif
}

void MJENC_SetQTableOffset59(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_76);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_36, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_37, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_76, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_76));
#endif
}

void MJENC_SetQTableOffset60(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_78);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_38, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_39, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_78, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_78));
#endif
}

void MJENC_SetQTableOffset61(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_7A);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_3A, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_3B, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_7A, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_7A));
#endif
}

void MJENC_SetQTableOffset62(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_7C);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_3C, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_3D, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_7C, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_7C));
#endif
}

void MJENC_SetQTableOffset63(int val1, int val2)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_7E);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_3E, val1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_Q_SRAM_REG_Q_1_3F, val2);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_7E, tmpVal);
#ifdef DEBUG_QTABLE
    MJENC_Qtable_debug(BL_RD_REG(MJPEG_ENC_BASE, MJENC_Q_SRAM_MJPEG_Q_PARAM_7E));
#endif
}

uint8_t MJENC_GetQTableCurrentBufIndex()
{
    uint32_t tmpVal;
    uint8_t index;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_MJPEG_Q_ENC);
    index = BL_GET_REG_BITS_VAL(tmpVal, MJENC_STS_Q_SRAM_ENC);

    return index;
}

void MJENC_EnableQTable()
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_MJPEG_Q_ENC);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJENC_REG_Q_SRAM_SW, 0x1);
    BL_WR_REG(MJPEG_ENC_BASE, MJENC_MJPEG_Q_ENC, tmpVal);
}

uint32_t MJENC_Get_Int_Status(void)
{
    uint32_t tmpVal;
    uint32_t ret = 0;

    tmpVal = BL_RD_REG(MJPEG_ENC_BASE, MJENC_MJPEG_CONTROL_3);
    MJENC_ClearIntrFlag();

    if (BL_IS_REG_BIT_SET(tmpVal, MJENC_STS_NORMAL_INT)) {
        ret = BL_BIT_SET(ret, MJPEG_ENC_INT_NORMAL);
    }

    if (BL_IS_REG_BIT_SET(tmpVal, MJENC_STS_CAM_INT)) {
        ret = BL_BIT_SET(ret, MJPEG_ENC_INT_CAM);
    }

    if (BL_IS_REG_BIT_SET(tmpVal, MJENC_STS_MEM_INT)) {
        ret = BL_BIT_SET(ret, MJPEG_ENC_INT_MEM);
    }

    if (BL_IS_REG_BIT_SET(tmpVal, MJENC_STS_FRAME_INT)) {
        ret = BL_BIT_SET(ret, MJPEG_ENC_INT_FRAME);
    }

    if (BL_IS_REG_BIT_SET(tmpVal, MJENC_STS_IDLE_INT)) {
        ret = BL_BIT_SET(ret, MJPEG_ENC_INT_IDLE);
    }
 
    return ret;
}

void MJENC_Get_Frame(uint8_t **ptr, uint32_t *len)
{
    *len = BL_RD_REG(MJPEG_ENC_BASE, MJENC_MJPEG_BIT_CNT0);
#if __riscv_xlen == 64
    *ptr = (uint8_t *)(uint64_t)BL_RD_REG(MJPEG_ENC_BASE, MJENC_MJPEG_START_ADDR0);
#else
    *ptr = (uint8_t *)BL_RD_REG(MJPEG_ENC_BASE, MJENC_MJPEG_START_ADDR0);
#endif
}
