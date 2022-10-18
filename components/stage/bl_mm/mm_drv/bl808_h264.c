#include <stdio.h>
#include <string.h>

#include "FreeRTOS.h"

#include "bl808_h264.h"
#include "vdo_reg.h"


#undef  DEBUG_MODULE
#define DEBUG_MODULE 0

#define IFRAME_MAX_QP           51
#define PFRAME_MAX_QP           51

#define DEF_NUM_SLICES          (1)

#if DEBUG_MODULE
#define DEBUG_REG() \
    vdo_reg_t *vdo_reg = (vdo_reg_t*)H264_ENC_BASE
#else
#define DEBUG_REG()
#endif

#define BL_BIT_SET(val, bit)    val | (1 << bit)

typedef enum {
    H264_CTRL_MODE_AUTO = 0,
    H264_CTRL_MODE_MANUAL = 2,
} H264_Ctrl_Mode_Type;

void H264_Reset_HW_Status(Stream_ID_Type id)
{
    uint32_t tmpVal;

    /* set reset HW internal status, including BS base, BS wr pointer, total byte cnt */
    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_H264_ENCODER_CTRL);

    /* initialize bitstream pointer to bs_base_addr, clear bs_tot_bycnt */
    H264_SET_CFG_BITS_VAL(id, tmpVal, BS_STATUS_INIT, 1);

#if (BL80X_HW_VER >= BL80X_HW_B0)
    /* as d2b_sync_en=1, reset start position of source buffer to cfg_frame_base_addr */
    H264_SET_CFG_BITS_VAL(id, tmpVal, SRC_LINE_CLR, 1);    /* Reset line cnt, which is synced with dvp2axi */
#endif
    BL_WR_REG(H264_ENC_BASE, VDO_H264_ENCODER_CTRL, tmpVal);
}

void H264_DisableCoreEnc(Stream_ID_Type id)
{
    uint32_t tmpVal;

    /* disable core enc to allow change of core configure */ 
    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_CORE_REG0);
    H264_SET_BITS_VAL(id, tmpVal, ENC_EN, 0);
    BL_WR_REG(H264_ENC_BASE, VDO_CORE_REG0, tmpVal);
}

void H264_Init(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_H264_ENCODER_CTRL);
    tmpVal = BL_SET_REG_BIT(tmpVal, VDO_CFG_CORE_CLK_EN);
    tmpVal = BL_SET_REG_BIT(tmpVal, VDO_CFG_MEM_CLK_EN);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, VDO_CFG_ENC_CTRL_MBY_IDX, 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, VDO_CFG_CTRL_MODE, H264_CTRL_MODE_AUTO);
    tmpVal = BL_CLR_REG_BIT(tmpVal, VDO_CFG_FRAME_START);
    tmpVal = BL_CLR_REG_BIT(tmpVal, VDO_CFG_ENC_SEQ_EN);

#if (BL80X_HW_VER >= BL80X_HW_B0)
    tmpVal = BL_CLR_REG_BIT(tmpVal, VDO_CFG_S_FRAME_START);
    tmpVal = BL_CLR_REG_BIT(tmpVal, VDO_CFG_S_ENC_SEQ_EN);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, VDO_CFG_DUO_BS_EN, 1);
#endif

    BL_WR_REG(H264_ENC_BASE, VDO_H264_ENCODER_CTRL, tmpVal);
}

void H264_Enable_CRef(Stream_ID_Type id, BL_Fun_Type enable)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_H264_ENCODER_CTRL);
    H264_SET_CFG_BITS_VAL(id, tmpVal, CREF_EN, (enable ? 0x01 : 0x00));
    BL_WR_REG(H264_ENC_BASE, VDO_H264_ENCODER_CTRL, tmpVal);
}

void H264_SetDualEnc(BL_Fun_Type newState)
{
#if (BL80X_HW_VER >= BL80X_HW_B0)
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_H264_ENCODER_CTRL);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, VDO_CFG_DUO_BS_EN, ((newState == ENABLE) ? 0x01 : 0x00));
    BL_WR_REG(H264_ENC_BASE, VDO_H264_ENCODER_CTRL, tmpVal);
#endif
}

void H264_SetSwMode(BL_Fun_Type newState)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_H264_ENCODER_CTRL);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, VDO_CFG_CTRL_MODE, 
        ((newState == ENABLE) ? H264_CTRL_MODE_MANUAL : H264_CTRL_MODE_AUTO));
    BL_WR_REG(H264_ENC_BASE, VDO_H264_ENCODER_CTRL, tmpVal);
}

void H264_SetLineBufferAddr(uint32_t addr)
{
    BL_WR_REG(H264_ENC_BASE, VDO_H264_LB_BASE_ADDR, addr);
}

void H264_SetResolution(Stream_ID_Type id, uint32_t width, uint32_t height)
{
    uint32_t tmpVal = 0;

    /* validate input param */
    CHECK_PARAM((width < 2048) && (height < 2048));
    CHECK_PARAM(IS_MULTIPULE_OF_8(height));

    H264_RD_REG(id, tmpVal, VDO_H264, FRAME_SIZE);
    H264_SET_CFG_BITS_VAL(id, tmpVal, FRAME_WIDTH, width);
    H264_SET_CFG_BITS_VAL(id, tmpVal, FRAME_HEIGHT, ENC_HEIGHT(height));
    H264_WR_REG(id, tmpVal, VDO_H264, FRAME_SIZE);

    H264_RD_REG(id, tmpVal, VDO, PADDING_CTRL);
    if (!IS_MULTIPULE_OF_16(height)) {
        H264_SET_BITS_VAL(id, tmpVal, Y_LINE_PAD, 8);
        H264_SET_BITS_VAL(id, tmpVal, Y_PADDING_PIXEL, 0x0);
        H264_SET_BITS_VAL(id, tmpVal, U_PADDING_PIXEL, 0x80);
        H264_SET_BITS_VAL(id, tmpVal, V_PADDING_PIXEL, 0x80);
    } else {
        H264_SET_BITS_VAL(id, tmpVal, Y_LINE_PAD, 0);
    }
    H264_WR_REG(id, tmpVal, VDO, PADDING_CTRL);
}

void H264_SetSrcFrameBuf(Stream_ID_Type id, H264_SRC_BUF_CFG_S *src_buf, uint16_t src_h, uint16_t h)
{
    uint32_t tmpVal;

    /* check if src height is too big (more than double 1088 height) */
    //CHECK_PARAM(src_h <= 2176);

    /* check if buffer is aligned to 128 bytes boundary */
    CHECK_PARAM((src_buf->yBufAddr & AXI_BURST_INCR16_ALIGNMENT_MASK) == 0 );
    CHECK_PARAM((src_buf->uvBufAddr & AXI_BURST_INCR16_ALIGNMENT_MASK) == 0 );

    H264_WR_REG(id, src_buf->yBufAddr, VDO_H264, FRAME_BASE_ADDR_Y);
    H264_WR_REG(id, src_buf->uvBufAddr, VDO_H264, FRAME_BASE_ADDR_UV);

    H264_RD_REG(id, tmpVal, VDO_H264, SRC_BF_HEIGHT);
    H264_SET_CFG_BITS_VAL(id, tmpVal, Y_SRC_BF_HEIGHT, src_h);
    H264_SET_CFG_BITS_VAL(id, tmpVal, C_SRC_BF_HEIGHT, src_h >> 1 );
    H264_WR_REG(id, tmpVal, VDO_H264, SRC_BF_HEIGHT);

#if (BL80X_HW_VER >= BL80X_HW_B0)
    /* need to assign Y/UV_SRCBF_SIZE in case src height is not mulitple of 16,
        or in direct link mode  */
    if (!IS_MULTIPULE_OF_16(src_h) || src_h < h) {
        H264_WR_REG(id, src_buf->yBufSize, VDO_H264, Y_SRCBF_SIZE);
        H264_WR_REG(id, src_buf->uvBufSize, VDO_H264, UV_SRCBF_SIZE);
    } else {
        H264_WR_REG(id, 0, VDO_H264, Y_SRCBF_SIZE);
        H264_WR_REG(id, 0, VDO_H264, UV_SRCBF_SIZE);
    }
#endif
}

void H264_SetSrcBufCtlCfg(Stream_ID_Type id, uint8_t numSrcFrm, uint32_t FrmYMemSize)
{
#if (BL80X_HW_VER >= BL80X_HW_B0)
    uint32_t tmpVal;
    uint32_t FrmCMemSize;
    
    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_SRC_CTRL);
    H264_SET_BITS_VAL(id, tmpVal, MFRM_BUF_EN, 0);
    H264_SET_BITS_VAL(id, tmpVal, FRM_BUF_NUM, 0);
    BL_WR_REG(H264_ENC_BASE, VDO_SRC_CTRL, tmpVal);

    if (numSrcFrm > 0) {
        /* byte cnt for single y/uv frame, used as y/uv frame address increment */
        FrmCMemSize = (FrmYMemSize >> 1);
        H264_WR_REG(id, FrmYMemSize, VDO_H264, Y_FRAME_MEM_SIZE);
        H264_WR_REG(id, FrmCMemSize, VDO_H264, UV_FRAME_MEM_SIZE);
    }
#endif
}

void H264_SetSrcChannel(Stream_ID_Type id, H264_Src_Chann_Cfg_Type *cfg)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_SRC_DVP_SEL);
    H264_SET_BITS_VAL(id, tmpVal, Y_DVP2AXI_SEL, cfg->y_src);
    H264_SET_BITS_VAL(id, tmpVal, UV_DVP2AXI_SEL, cfg->uv_src);
    BL_WR_REG(H264_ENC_BASE, VDO_SRC_DVP_SEL, tmpVal);
}

void H264_SetBitstreamBuf(Stream_ID_Type id, uint32_t bufAddr, uint32_t bufSize)
{
    /* check if buffer is aligned to 128 bytes boundary */
    CHECK_PARAM((bufAddr & AXI_BURST_INCR16_ALIGNMENT_MASK) == 0 );

    H264_WR_REG(id, bufAddr, VDO_H264, BS_BASE_ADDR);
#if H264_BSB_WORKAROUND
    H264_WR_REG(id, bufSize - 4, VDO_H264, BS_SIZE);
#else
    H264_WR_REG(id, bufSize, VDO_H264, BS_SIZE);
#endif
}

void H264_SetBitstreamBufThreshold(Stream_ID_Type id, uint32_t threshold)
{
    uint32_t tmpVal;

    H264_WR_REG(id, threshold, VDO_H264, BS_FULL_THR);
    H264_RD_REG(id, tmpVal, VDO_H264, BS_FULL_THR);
    //BL_LOGI("[INFO] bs_threshold val:%d\r\n", tmpVal);
}

void H264_GetBSTotalByte(Stream_ID_Type id, uint32_t *total_byte)
{
    uint32_t tmpVal;
    H264_RD_REG(id, tmpVal, VDO, TOTAL_BYTECOUNT);

    *total_byte = tmpVal;
}

#if NEW_REF_FRM_CFG_API
void H264_SetRefFrmMemPlusExtData(Stream_ID_Type id, H264_REF_FRM_ADDR_S *ref_addr)
{
    H264_WR_REG(id, ref_addr->ref_y0_base_addr, VDO_H264, REFY0_BASE_ADDR);
    H264_WR_REG(id, ref_addr->ref_u0_base_addr, VDO_H264, REFU0_BASE_ADDR);
    H264_WR_REG(id, ref_addr->ref_v0_base_addr, VDO_H264, REFV0_BASE_ADDR);
    H264_WR_REG(id, ref_addr->ref_y1_base_addr, VDO_H264, REFY1_BASE_ADDR);
    H264_WR_REG(id, ref_addr->ref_u1_base_addr, VDO_H264, REFU1_BASE_ADDR);
    H264_WR_REG(id, ref_addr->ref_v1_base_addr, VDO_H264, REFV1_BASE_ADDR);
    H264_WR_REG(id, ref_addr->ext_dat_base_addr, VDO_H264, EXT_BASE_ADDR);
}
#else
void H264_SetRefFrmMemPlusExtData(Stream_ID_Type id, uint32_t ref_addr)
{
    H264_WR_REG(id, ref_addr, VDO_H264, REF_BASE_ADDR);
}
#endif

void H264_SetVUITimeScale(Stream_ID_Type id, uint32_t timeScale)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_CORE_REG32);
    H264_SET_BITS_VAL(id, tmpVal, VUI_TIME_SCALE_L, timeScale & 0xffff);
    BL_WR_REG(H264_ENC_BASE, VDO_CORE_REG32, tmpVal);

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_CORE_REG33);
    H264_SET_BITS_VAL(id, tmpVal, VUI_TIME_SCALE_H, (timeScale>>16) & 0xffff);
    BL_WR_REG(H264_ENC_BASE, VDO_CORE_REG33, tmpVal);
}

void H264_SetVUINumUnitsInTick(Stream_ID_Type id, uint32_t numUnitsInTick)
{
    uint32_t tmpVal;
    
    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_CORE_REG34);
    H264_SET_BITS_VAL(id, tmpVal, VUI_NUM_U_TICK_L, numUnitsInTick & 0xffff);
    BL_WR_REG(H264_ENC_BASE, VDO_CORE_REG34, tmpVal);

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_CORE_REG35);
    H264_SET_BITS_VAL(id, tmpVal, VUI_NUM_U_TICK_H, (numUnitsInTick>>16) & 0xffff);
    BL_WR_REG(H264_ENC_BASE, VDO_CORE_REG35, tmpVal);
}

void H264_UpdateSPS(Stream_ID_Type id)
{
#if (BL80X_HW_VER >= BL80X_HW_B0)
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_H264_ENCODER_CTRL);
    H264_SET_CFG_BITS_VAL(id, tmpVal, RC_GOP_UPD, 1);
    BL_WR_REG(H264_ENC_BASE, VDO_H264_ENCODER_CTRL, tmpVal);
#endif 
}

void H264_UpdateRC(Stream_ID_Type id)
{
#if (BL80X_HW_VER >= BL80X_HW_B0)
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_H264_ENCODER_CTRL);
    H264_SET_CFG_BITS_VAL(id, tmpVal, QR_UPD, 1);
    BL_WR_REG(H264_ENC_BASE, VDO_H264_ENCODER_CTRL, tmpVal);
#endif 
}

void H264_SetRateCtrlCfg(Stream_ID_Type id, const H264_RC_Cfg_Type *cfg)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_CORE_REG3);
    H264_SET_BITS_VAL(id, tmpVal, TARGET_I_QP, cfg->target_i_qp);
    BL_WR_REG(H264_ENC_BASE, VDO_CORE_REG3, tmpVal);

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_CORE_REG5);
    H264_SET_BITS_VAL(id, tmpVal, TARGET_P_QP, cfg->target_p_qp);
    BL_WR_REG(H264_ENC_BASE, VDO_CORE_REG5, tmpVal);

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_CORE_REG23);
    H264_SET_BITS_VAL(id, tmpVal, NUM_IMB_BITS, cfg->num_imb_bits);
    BL_WR_REG(H264_ENC_BASE, VDO_CORE_REG23, tmpVal);

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_CORE_REG24);
    H264_SET_BITS_VAL(id, tmpVal, NUM_PMB_BITS, cfg->num_pmb_bits);
    BL_WR_REG(H264_ENC_BASE, VDO_CORE_REG24, tmpVal);

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_CORE_REG31);
    H264_SET_BITS_VAL(id, tmpVal, IFRAME_MIN_QP, cfg->iframe_min_qp);
    BL_WR_REG(H264_ENC_BASE, VDO_CORE_REG31, tmpVal);

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_CORE_REG31);
    H264_SET_BITS_VAL(id, tmpVal, IFRAME_MAX_QP, cfg->iframe_max_qp);
    BL_WR_REG(H264_ENC_BASE, VDO_CORE_REG31, tmpVal);
}

void H264_GetRateCtrlCfg(Stream_ID_Type id, H264_RC_Cfg_Type *cfg)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_CORE_REG3);
    H264_GET_BITS_VAL(id, tmpVal, TARGET_I_QP, cfg->target_i_qp);

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_CORE_REG5);
    H264_GET_BITS_VAL(id, tmpVal, TARGET_P_QP, cfg->target_p_qp);

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_CORE_REG23);
    H264_GET_BITS_VAL(id, tmpVal, NUM_IMB_BITS, cfg->num_imb_bits);

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_CORE_REG24);
    H264_GET_BITS_VAL(id, tmpVal, NUM_PMB_BITS, cfg->num_pmb_bits);

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_CORE_REG31);
    H264_GET_BITS_VAL(id, tmpVal, IFRAME_MIN_QP, cfg->iframe_min_qp);

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_CORE_REG31);
    H264_GET_BITS_VAL(id, tmpVal, IFRAME_MAX_QP, cfg->iframe_max_qp);
}

void H264_SetRateCtrlQP(Stream_ID_Type id, int target_i_qp, int target_p_qp)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_CORE_REG3);
    H264_SET_BITS_VAL(id, tmpVal, TARGET_I_QP, target_i_qp);
    BL_WR_REG(H264_ENC_BASE, VDO_CORE_REG3, tmpVal);

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_CORE_REG5);
    H264_SET_BITS_VAL(id, tmpVal, TARGET_P_QP, target_p_qp);
    BL_WR_REG(H264_ENC_BASE, VDO_CORE_REG5, tmpVal);
}

void H264_SetCoreSizeCfg(Stream_ID_Type id, H264_Core_Size_Cfg_Type *cfg)
{
    uint32_t tmpVal;

    CHECK_PARAM(cfg->ixsize > 0 && cfg->ixsize <= 1920);
    CHECK_PARAM(cfg->iysize > 0 && cfg->iysize <= 1600);

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_CORE_REG1);
    H264_SET_BITS_VAL(id, tmpVal, IMG_WIDTH, cfg->ixsize);
    BL_WR_REG(H264_ENC_BASE, VDO_CORE_REG1, tmpVal);

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_CORE_REG2);
    H264_SET_BITS_VAL(id, tmpVal, IMG_HEIGHT, cfg->iysize);
    BL_WR_REG(H264_ENC_BASE, VDO_CORE_REG2, tmpVal);

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_CORE_REG6);
    H264_SET_BITS_VAL(id, tmpVal, MB_LINES, (BLK_CNT_16X16(cfg->iysize)/DEF_NUM_SLICES) - 1);
    BL_WR_REG(H264_ENC_BASE, VDO_CORE_REG6, tmpVal);

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_CORE_REG17);
    H264_SET_BITS_VAL(id, tmpVal, FRAME1, cfg->luvsize);
    BL_WR_REG(H264_ENC_BASE, VDO_CORE_REG17, tmpVal);

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_CORE_REG18);
    H264_SET_BITS_VAL(id, tmpVal, EXT_DATA, (cfg->luvsize*2));
    BL_WR_REG(H264_ENC_BASE, VDO_CORE_REG18, tmpVal);

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_CORE_REG19);
    H264_SET_BITS_VAL(id, tmpVal, EXT_MEM_CONFIG0, cfg->xsize32);
    BL_WR_REG(H264_ENC_BASE, VDO_CORE_REG19, tmpVal);

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_CORE_REG20);
    H264_SET_BITS_VAL(id, tmpVal, EXT_MEM_CONFIG1, cfg->uvxsize32);
    BL_WR_REG(H264_ENC_BASE, VDO_CORE_REG20, tmpVal);

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_CORE_REG21);
    H264_SET_BITS_VAL(id, tmpVal, EXT_MEM_CONFIG2, cfg->lsize);
    BL_WR_REG(H264_ENC_BASE, VDO_CORE_REG21, tmpVal);

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_CORE_REG22);
    H264_SET_BITS_VAL(id, tmpVal, EXT_MEM_CONFIG3, cfg->uvsize);
    BL_WR_REG(H264_ENC_BASE, VDO_CORE_REG22, tmpVal);
}

void H264_SetGOPSize(Stream_ID_Type id, uint32_t gopSize)
{
    uint32_t tmpVal;

    CHECK_PARAM(gopSize > 0 && gopSize < 300);

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_CORE_REG8);
    H264_SET_BITS_VAL(id, tmpVal, NUM_PFRAMES, gopSize - 1);
    BL_WR_REG(H264_ENC_BASE, VDO_CORE_REG8, tmpVal);
}

void H264_SetProfile(Stream_ID_Type id, H264_Profile_Type profile)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_CORE_REG12);
    H264_SET_BITS_VAL(id, tmpVal, PROFILE_IDC, profile);
    BL_WR_REG(H264_ENC_BASE, VDO_CORE_REG12, tmpVal);

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_H264_HWBACK_MODE);
    H264_SET_CFG_BITS_VAL(id, tmpVal, NAL_MP_MODE, profile);
    BL_WR_REG(H264_ENC_BASE, VDO_H264_HWBACK_MODE, tmpVal);
}

void H264_EnableDeblock(Stream_ID_Type id, BL_Fun_Type enable)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_CORE_REG9);
    H264_SET_BITS_VAL(id, tmpVal, DIS_FILTER, !enable);
    BL_WR_REG(H264_ENC_BASE, VDO_CORE_REG9, tmpVal);
}

void H264_SetDefaultCoreCfg(Stream_ID_Type id)
{
    int alpha_offset = 0;
    int beta_offset = 0;
    int chroma_qp_offset = 0;

    int constrained_ipred = 0;
    int nal_align = 0;

    int vui_timing_info = 1;

    int vui_fixed_frame_rate = 0;
    int sps_level_idc = 41;
    int aspect_ratio_info_present_flag = 0;
    int aspect_ratio_idc = 255;
    int aspect_ratio_width = 8;
    int aspect_ratio_height = 9;
    int idr_enable = 0;

    uint32_t tmpVal;

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_CORE_REG0);
    /* Encoder disabled */
    H264_SET_BITS_VAL(id, tmpVal, ENC_EN, 0);
    /* VUI aspect ratio information in SPS sent */
    H264_SET_BITS_VAL(id, tmpVal, VUI_ASPECT_INFO, aspect_ratio_info_present_flag);
    /* VUI fixed_frame_rate_flag sent if vui_timing_info is set to 1 */
    H264_SET_BITS_VAL(id, tmpVal, VUI_FIXED_F_RATE, vui_fixed_frame_rate);
    /* VUI timing information in SPS sent */
    H264_SET_BITS_VAL(id, tmpVal, VUI_TIMING_INFO, vui_timing_info);
    /* IDR and SPS and PPS sent at I-frame period */
    H264_SET_BITS_VAL(id, tmpVal, IDR_ENABLE, idr_enable);
    BL_WR_REG(H264_ENC_BASE, VDO_CORE_REG0, tmpVal);


    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_CORE_REG4);
    H264_SET_BITS_VAL(id, tmpVal, CQP_OFFSET, chroma_qp_offset);
    BL_WR_REG(H264_ENC_BASE, VDO_CORE_REG4, tmpVal);

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_CORE_REG7);
    H264_SET_BITS_VAL(id, tmpVal, NUM_SLICES, DEF_NUM_SLICES - 1);
    BL_WR_REG(H264_ENC_BASE, VDO_CORE_REG7, tmpVal);

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_CORE_REG10);
    H264_SET_BITS_VAL(id, tmpVal, ALPHA_OFF, alpha_offset);
    BL_WR_REG(H264_ENC_BASE, VDO_CORE_REG10, tmpVal);

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_CORE_REG11);
    H264_SET_BITS_VAL(id, tmpVal, BETA_OFF, beta_offset);
    BL_WR_REG(H264_ENC_BASE, VDO_CORE_REG11, tmpVal);

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_CORE_REG13);
    H264_SET_BITS_VAL(id, tmpVal, LEVEL_IDC, sps_level_idc);
    BL_WR_REG(H264_ENC_BASE, VDO_CORE_REG13, tmpVal);

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_CORE_REG14);
    H264_SET_BITS_VAL(id, tmpVal, LUMA8X8_COST, 0x4);
    H264_SET_BITS_VAL(id, tmpVal, LUMA16X16_COST, 0x5);
    H264_SET_BITS_VAL(id, tmpVal, CHROMA8X8_COST, 0x3);
    BL_WR_REG(H264_ENC_BASE, VDO_CORE_REG14, tmpVal);

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_CORE_REG16);
    H264_SET_BITS_VAL(id, tmpVal, FRAME0, 0);
    BL_WR_REG(H264_ENC_BASE, VDO_CORE_REG16, tmpVal);

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_CORE_REG23);
    H264_SET_BITS_VAL(id, tmpVal, NAL_ALIGN, nal_align);
    H264_SET_BITS_VAL(id, tmpVal, CONS_IPRED, constrained_ipred);
    BL_WR_REG(H264_ENC_BASE, VDO_CORE_REG23, tmpVal); 

    //BL_LOGI("[enc %d] num_imb_bits %d, num_pmb_bits %d\r\n", id, cfg->num_imb_bits, cfg->num_pmb_bits);

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_CORE_REG25);
    tmpVal = BL_CLR_REG_BIT(tmpVal, VDO_INTERLACE_MODE);
    BL_WR_REG(H264_ENC_BASE, VDO_CORE_REG25, tmpVal);

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_CORE_REG28);
    H264_SET_BITS_VAL(id, tmpVal, PFRAME_MAX_QP, PFRAME_MAX_QP);
    BL_WR_REG(H264_ENC_BASE, VDO_CORE_REG28, tmpVal);

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_CORE_REG30);
    H264_SET_BITS_VAL(id, tmpVal, RESET_I_STATE, 1);
    BL_WR_REG(H264_ENC_BASE, VDO_CORE_REG30, tmpVal);

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_CORE_REG31);
    H264_SET_BITS_VAL(id, tmpVal, IFRAME_MAX_QP, IFRAME_MAX_QP);
    BL_WR_REG(H264_ENC_BASE, VDO_CORE_REG31, tmpVal);

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_CORE_REG36);
    H264_SET_BITS_VAL(id, tmpVal, VUI_ASPECT_IDC, aspect_ratio_idc);
    BL_WR_REG(H264_ENC_BASE, VDO_CORE_REG36, tmpVal);

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_CORE_REG37);
    H264_SET_BITS_VAL(id, tmpVal, VUI_ASPECT_WIDTH, aspect_ratio_width);
    BL_WR_REG(H264_ENC_BASE, VDO_CORE_REG37, tmpVal);

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_CORE_REG38);
    H264_SET_BITS_VAL(id, tmpVal, VUI_ASPECT_HEIGHT, aspect_ratio_height);
    BL_WR_REG(H264_ENC_BASE, VDO_CORE_REG38, tmpVal);
}

void H264_StartEnc(Stream_ID_Type id, BL_Fun_Type sw_mode)
{
    uint32_t tmpVal;

#if (BL80X_HW_VER <= BL80X_HW_A0) 
        /* enable core enc to apply change of configure */
        tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_CORE_REG0);
        H264_SET_BITS_VAL(id, tmpVal, ENC_EN, 1);
        BL_WR_REG(H264_ENC_BASE, VDO_CORE_REG0, tmpVal);
#endif

    if (ENABLE == sw_mode) {
        /* enable core enc to apply change of configure */
        tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_CORE_REG0);
        H264_SET_BITS_VAL(id, tmpVal, ENC_EN, 1);
        BL_WR_REG(H264_ENC_BASE, VDO_CORE_REG0, tmpVal);
    }

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_H264_ENCODER_CTRL);
    if (ENABLE == sw_mode) {
        H264_SET_CFG_BITS_VAL(id, tmpVal, FRAME_START, 1);
    } else {
        H264_SET_CFG_BITS_VAL(id, tmpVal, ENC_SEQ_EN, 1);
    }
    BL_WR_REG(H264_ENC_BASE, VDO_H264_ENCODER_CTRL, tmpVal);
}

void H264_StopEnc(Stream_ID_Type id)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_H264_ENCODER_CTRL);
    H264_SET_CFG_BITS_VAL(id, tmpVal, ENC_SEQ_EN, 0);
    BL_WR_REG(H264_ENC_BASE, VDO_H264_ENCODER_CTRL, tmpVal);
}

void H264_SetPrefetchMode(Stream_ID_Type id, BL_Fun_Type newState)
{
#if (BL80X_HW_VER >= BL80X_HW_B0)
    uint32_t tmpVal;

    H264_RD_REG(id, tmpVal, VDO_H264, PFCH_CTRL);
    H264_SET_CFG_BITS_VAL(id, tmpVal, PFCH_EN, ((newState == ENABLE) ? 0x01 : 0x00));
    H264_WR_REG(id, tmpVal, VDO_H264, PFCH_CTRL);
#endif
}

void H264_SetPrefetchCfg(Stream_ID_Type id, uint8_t mbHeight)
{
#if (BL80X_HW_VER >= BL80X_HW_B0)
    uint32_t tmpVal;

    H264_RD_REG(id, tmpVal, VDO_H264, PFCH_CTRL);
    H264_SET_CFG_BITS_VAL(id, tmpVal, PFCH_MBX_S, 0);
    H264_SET_CFG_BITS_VAL(id, tmpVal, PFCH_MBY_S, mbHeight - 3);
    H264_WR_REG(id, tmpVal, VDO_H264, PFCH_CTRL);
#endif
}

void H264_SetPrefetchBuffer(Stream_ID_Type id, uint32_t YRefAddr, uint32_t UVRefAddr)
{
    /* Y: image width × 80 */
    /* UV: (image width/2) ×40 */

#if (BL80X_HW_VER >= BL80X_HW_B0)
    /* check if buffer is aligned to 128 bytes boundary */
    CHECK_PARAM((YRefAddr & AXI_BURST_INCR16_ALIGNMENT_MASK) == 0 );

    H264_WR_REG(id, YRefAddr, VDO_H264, PFCH_BASE);
    H264_WR_REG(id, UVRefAddr, VDO_H264, PFCHV_BASE);
#endif
}

void H264_IsCurrentPFrame(Stream_ID_Type id, BL_Sts_Type *status)
{
#if (BL80X_HW_VER >= BL80X_HW_B0)
    uint32_t tmpVal;

    H264_RD_REG(id, tmpVal, VDO, CORE_DBG2);
    H264_GET_BITS_VAL(id, tmpVal, PFRAME, *status);
#endif
}

void H264_EnableSPSOnEachGOP(Stream_ID_Type id, BL_Fun_Type newState)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_CORE_REG0);
    H264_SET_BITS_VAL(id, tmpVal, IDR_ENABLE, ((newState == ENABLE) ? 0x01 : 0x00));
    BL_WR_REG(H264_ENC_BASE, VDO_CORE_REG0, tmpVal);
}

void H264_EnableSramckModeOld(BL_Fun_Type newState)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_H264_HWBACK_MODE);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, VDO_CFG_SRAMCK_MODE, newState);
    BL_WR_REG(H264_ENC_BASE, VDO_H264_HWBACK_MODE, tmpVal);
}

void H264_SetBufferSyncFlag(Stream_ID_Type id)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_H264_SRC_DBG);
    if (STREAM_0_ID == id) {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, VDO_D2B_SYNC_EN, 0x1);
    } else {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, VDO_S_D2B_SYNC_EN, 0x1);
    }
    BL_WR_REG(H264_ENC_BASE, VDO_H264_SRC_DBG, tmpVal);
}

uint16_t H264_GetYSrcHeight(Stream_ID_Type id)
{
    uint32_t tmpVal;
    uint16_t y_src_height = 0;

    H264_RD_REG(id, tmpVal, VDO_H264, SRC_BF_HEIGHT);
    H264_GET_CFG_BITS_VAL(id, tmpVal, Y_SRC_BF_HEIGHT, y_src_height);
    return y_src_height;
}

uint16_t H264_GetCSrcHeight(Stream_ID_Type id)
{
    uint32_t tmpVal;
    uint16_t c_src_height = 0;

    H264_RD_REG(id, tmpVal, VDO_H264, SRC_BF_HEIGHT);
    H264_GET_CFG_BITS_VAL(id, tmpVal, C_SRC_BF_HEIGHT, c_src_height);

    return c_src_height;
}

uint16_t H264_GetFrameHeight(Stream_ID_Type id)
{
    uint32_t tmpVal;
    uint16_t height = 0;

    H264_RD_REG(id, tmpVal, VDO_H264, FRAME_SIZE);
    H264_GET_CFG_BITS_VAL(id, tmpVal, FRAME_HEIGHT, height);

    return height;
}

uint16_t H264_GetFrameWidth(Stream_ID_Type id)
{
    uint32_t tmpVal;
    uint16_t width = 0;

    H264_RD_REG(id, tmpVal, VDO_H264, FRAME_SIZE);
    H264_GET_CFG_BITS_VAL(id, tmpVal, FRAME_WIDTH, width);

    return width;
}

void H264_SetBufferByteCnt(Stream_ID_Type id, uint32_t y_src_height,
                                     uint32_t c_src_height, uint32_t width)
{
   uint32_t tmpVal;
   uint32_t Val;

   H264_RD_REG(id, tmpVal, VDO_H264, Y_SRCBF_SIZE);
   Val = y_src_height * width;
   H264_SET_CFG_BITS_VAL(id, tmpVal, Y_SRCBF_BYCNT, Val);
   H264_WR_REG(id, tmpVal, VDO_H264, Y_SRCBF_SIZE);

   H264_RD_REG(id, tmpVal, VDO_H264, UV_SRCBF_SIZE);
   Val = c_src_height * width;
   H264_SET_CFG_BITS_VAL(id, tmpVal, UV_SRCBF_BYCNT, Val);
   H264_WR_REG(id, tmpVal, VDO_H264, UV_SRCBF_SIZE);
}

uint16_t H264_GetIntraMBCnt(Stream_ID_Type id)
{
    uint32_t val;

    H264_RD_REG(id, val, VDONR, IMBCNT);
    return val;
}

void H264_GetMbInfo(Stream_ID_Type id, H264_MB_Info_T *info)
{
    uint32_t tmpVal;
    
    H264_RD_REG(id, info->absmv_sum, VDONR, ABSMV_SUM);
    H264_RD_REG(id, tmpVal, VDONR, MVLEVEL);
    H264_GET_BITS_VAL(id, tmpVal, NZMV_MBCNT, info->nzmv_mbcnt);
    H264_RD_REG(id, info->intra_mbcnt, VDONR, IMBCNT);

}

void H264_RoiSetRoi0Coordinate(Stream_ID_Type id, H264_ROI_Coordinate_Info_T *coordinate_info)
{
    uint32_t tmpVal;
    uint8_t val;

    H264_RD_REG(id, tmpVal, VDO_H264, ROI0);
    H264_SET_CFG_BITS_VAL(id, tmpVal, ROI0_MBX_S, coordinate_info->mbx_s);
    H264_SET_CFG_BITS_VAL(id, tmpVal, ROI0_MBX_E, coordinate_info->mbx_e);
    H264_SET_CFG_BITS_VAL(id, tmpVal, ROI0_MBY_S, coordinate_info->mby_s);
    H264_SET_CFG_BITS_VAL(id, tmpVal, ROI0_MBY_E, coordinate_info->mby_e);
    H264_WR_REG(id, tmpVal, VDO_H264, ROI0);

    H264_RD_REG(id, tmpVal, VDO_H264, ROI_MODE);
    H264_GET_CFG_BITS_VAL(id, tmpVal, ROI_EN, val);
    val = val | 0x1;
    H264_SET_CFG_BITS_VAL(id, tmpVal, ROI_EN, val);
    H264_WR_REG(id, tmpVal, VDO_H264, ROI_MODE);
}

void H264_RoiSetRoi1Coordinate(Stream_ID_Type id, H264_ROI_Coordinate_Info_T *coordinate_info)
{
    uint32_t tmpVal;
    uint8_t val;

    H264_RD_REG(id, tmpVal, VDO_H264, ROI1);
    H264_SET_CFG_BITS_VAL(id, tmpVal, ROI1_MBX_S, coordinate_info->mbx_s);
    H264_SET_CFG_BITS_VAL(id, tmpVal, ROI1_MBX_E, coordinate_info->mbx_e);
    H264_SET_CFG_BITS_VAL(id, tmpVal, ROI1_MBY_S, coordinate_info->mby_s);
    H264_SET_CFG_BITS_VAL(id, tmpVal, ROI1_MBY_E, coordinate_info->mby_e);
    H264_WR_REG(id, tmpVal, VDO_H264, ROI1);

    H264_RD_REG(id, tmpVal, VDO_H264, ROI_MODE);
    H264_GET_CFG_BITS_VAL(id, tmpVal, ROI_EN, val);
    val = val | 0x2;
    H264_SET_CFG_BITS_VAL(id, tmpVal, ROI_EN, val);
    H264_WR_REG(id, tmpVal, VDO_H264, ROI_MODE);
}

void H264_RoiSetRoi2Coordinate(Stream_ID_Type id, H264_ROI_Coordinate_Info_T *coordinate_info)
{
    uint32_t tmpVal;
    uint8_t val;

    H264_RD_REG(id, tmpVal, VDO_H264, ROI2);
    H264_SET_CFG_BITS_VAL(id, tmpVal, ROI2_MBX_S, coordinate_info->mbx_s);
    H264_SET_CFG_BITS_VAL(id, tmpVal, ROI2_MBX_E, coordinate_info->mbx_e);
    H264_SET_CFG_BITS_VAL(id, tmpVal, ROI2_MBY_S, coordinate_info->mby_s);
    H264_SET_CFG_BITS_VAL(id, tmpVal, ROI2_MBY_E, coordinate_info->mby_e);
    H264_WR_REG(id, tmpVal, VDO_H264, ROI2);

    H264_RD_REG(id, tmpVal, VDO_H264, ROI_MODE);
    H264_GET_CFG_BITS_VAL(id, tmpVal, ROI_EN, val);
    val = val | 0x4;
    H264_SET_CFG_BITS_VAL(id, tmpVal, ROI_EN, val);
    H264_WR_REG(id, tmpVal, VDO_H264, ROI_MODE);
}

void H264_RoiSetRoi3Coordinate(Stream_ID_Type id, H264_ROI_Coordinate_Info_T *coordinate_info)
{
    uint32_t tmpVal;
    uint8_t val;

    H264_RD_REG(id, tmpVal, VDO_H264, ROI3);
    H264_SET_CFG_BITS_VAL(id, tmpVal, ROI3_MBX_S, coordinate_info->mbx_s);
    H264_SET_CFG_BITS_VAL(id, tmpVal, ROI3_MBX_E, coordinate_info->mbx_e);
    H264_SET_CFG_BITS_VAL(id, tmpVal, ROI3_MBY_S, coordinate_info->mby_s);
    H264_SET_CFG_BITS_VAL(id, tmpVal, ROI3_MBY_E, coordinate_info->mby_e);
    H264_WR_REG(id, tmpVal, VDO_H264, ROI3);

    H264_RD_REG(id, tmpVal, VDO_H264, ROI_MODE);
    H264_GET_CFG_BITS_VAL(id, tmpVal, ROI_EN, val);
    val = val | 0x8;
    H264_SET_CFG_BITS_VAL(id, tmpVal, ROI_EN, val);
    H264_WR_REG(id, tmpVal, VDO_H264, ROI_MODE);
}

void H264_RoiSetRoi4Coordinate(Stream_ID_Type id, H264_ROI_Coordinate_Info_T *coordinate_info)
{
    uint32_t tmpVal;
    uint8_t val;

    H264_RD_REG(id, tmpVal, VDO_H264, ROI4);
    H264_SET_CFG_BITS_VAL(id, tmpVal, ROI4_MBX_S, coordinate_info->mbx_s);
    H264_SET_CFG_BITS_VAL(id, tmpVal, ROI4_MBX_E, coordinate_info->mbx_e);
    H264_SET_CFG_BITS_VAL(id, tmpVal, ROI4_MBY_S, coordinate_info->mby_s);
    H264_SET_CFG_BITS_VAL(id, tmpVal, ROI4_MBY_E, coordinate_info->mby_e);
    H264_WR_REG(id, tmpVal, VDO_H264, ROI4);

    H264_RD_REG(id, tmpVal, VDO_H264, ROI_MODE);
    H264_GET_CFG_BITS_VAL(id, tmpVal, ROI_EN, val);
    val = val | 0x10;
    H264_SET_CFG_BITS_VAL(id, tmpVal, ROI_EN, val);
    H264_WR_REG(id, tmpVal, VDO_H264, ROI_MODE);
}

void H264_RoiSetRoi5Coordinate(Stream_ID_Type id, H264_ROI_Coordinate_Info_T *coordinate_info)
{
    uint32_t tmpVal;
    uint8_t val;

    H264_RD_REG(id, tmpVal, VDO_H264, ROI5);
    H264_SET_CFG_BITS_VAL(id, tmpVal, ROI5_MBX_S, coordinate_info->mbx_s);
    H264_SET_CFG_BITS_VAL(id, tmpVal, ROI5_MBX_E, coordinate_info->mbx_e);
    H264_SET_CFG_BITS_VAL(id, tmpVal, ROI5_MBY_S, coordinate_info->mby_s);
    H264_SET_CFG_BITS_VAL(id, tmpVal, ROI5_MBY_E, coordinate_info->mby_e);
    H264_WR_REG(id, tmpVal, VDO_H264, ROI5);

    H264_RD_REG(id, tmpVal, VDO_H264, ROI_MODE);
    H264_GET_CFG_BITS_VAL(id, tmpVal, ROI_EN, val);
    val = val | 0x20;
    H264_SET_CFG_BITS_VAL(id, tmpVal, ROI_EN, val);
    H264_WR_REG(id, tmpVal, VDO_H264, ROI_MODE);
}

void H264_RoiSetRoi6Coordinate(Stream_ID_Type id, H264_ROI_Coordinate_Info_T *coordinate_info)
{
    uint32_t tmpVal;
    uint8_t val;

    H264_RD_REG(id, tmpVal, VDO_H264, ROI6);
    H264_SET_CFG_BITS_VAL(id, tmpVal, ROI6_MBX_S, coordinate_info->mbx_s);
    H264_SET_CFG_BITS_VAL(id, tmpVal, ROI6_MBX_E, coordinate_info->mbx_e);
    H264_SET_CFG_BITS_VAL(id, tmpVal, ROI6_MBY_S, coordinate_info->mby_s);
    H264_SET_CFG_BITS_VAL(id, tmpVal, ROI6_MBY_E, coordinate_info->mby_e);
    H264_WR_REG(id, tmpVal, VDO_H264, ROI6);

    H264_RD_REG(id, tmpVal, VDO_H264, ROI_MODE);
    H264_GET_CFG_BITS_VAL(id, tmpVal, ROI_EN, val);
    val = val | 0x40;
    H264_SET_CFG_BITS_VAL(id, tmpVal, ROI_EN, val);
    H264_WR_REG(id, tmpVal, VDO_H264, ROI_MODE);
}

void H264_RoiSetRoi7Coordinate(Stream_ID_Type id, H264_ROI_Coordinate_Info_T *coordinate_info)
{
    uint32_t tmpVal;
    uint8_t val;

    H264_RD_REG(id, tmpVal, VDO_H264, ROI7);
    H264_SET_CFG_BITS_VAL(id, tmpVal, ROI7_MBX_S, coordinate_info->mbx_s);
    H264_SET_CFG_BITS_VAL(id, tmpVal, ROI7_MBX_E, coordinate_info->mbx_e);
    H264_SET_CFG_BITS_VAL(id, tmpVal, ROI7_MBY_S, coordinate_info->mby_s);
    H264_SET_CFG_BITS_VAL(id, tmpVal, ROI7_MBY_E, coordinate_info->mby_e);
    H264_WR_REG(id, tmpVal, VDO_H264, ROI7);

    H264_RD_REG(id, tmpVal, VDO_H264, ROI_MODE);
    H264_GET_CFG_BITS_VAL(id, tmpVal, ROI_EN, val);
    val = val | 0x80;
    H264_SET_CFG_BITS_VAL(id, tmpVal, ROI_EN, val);
    H264_WR_REG(id, tmpVal, VDO_H264, ROI_MODE);
}

uint8_t  H264_RoiGetEnPositonVal(Stream_ID_Type id)
{
    uint32_t tmpVal;
    uint8_t val;

    H264_RD_REG(id, tmpVal, VDO_H264, ROI_MODE);
    H264_GET_CFG_BITS_VAL(id, tmpVal, ROI_EN, val);

    return val;
}

void  H264_RoiResetEnPositonVal(Stream_ID_Type id)
{
    uint32_t tmpVal;

    H264_RD_REG(id, tmpVal, VDO_H264, ROI_MODE);
    H264_SET_CFG_BITS_VAL(id, tmpVal, ROI_EN, 0x0);
    H264_WR_REG(id, tmpVal, VDO_H264, ROI_MODE);
}

void H264_RoiGetRoi0Coordinate(Stream_ID_Type id, H264_ROI_Coordinate_Info_T *coordinate_info)
{
    uint32_t tmpVal;

    H264_RD_REG(id, tmpVal, VDO_H264, ROI0);
    H264_GET_CFG_BITS_VAL(id, tmpVal, ROI0_MBX_S, coordinate_info->mbx_s);
    H264_GET_CFG_BITS_VAL(id, tmpVal, ROI0_MBX_E, coordinate_info->mbx_e);
    H264_GET_CFG_BITS_VAL(id, tmpVal, ROI0_MBY_S, coordinate_info->mby_s);
    H264_GET_CFG_BITS_VAL(id, tmpVal, ROI0_MBY_E, coordinate_info->mby_e);
}

void H264_RoiGetRoi1Coordinate(Stream_ID_Type id, H264_ROI_Coordinate_Info_T *coordinate_info)
{
    uint32_t tmpVal;

    H264_RD_REG(id, tmpVal, VDO_H264, ROI1);
    H264_GET_CFG_BITS_VAL(id, tmpVal, ROI1_MBX_S, coordinate_info->mbx_s);
    H264_GET_CFG_BITS_VAL(id, tmpVal, ROI1_MBX_E, coordinate_info->mbx_e);
    H264_GET_CFG_BITS_VAL(id, tmpVal, ROI1_MBY_S, coordinate_info->mby_s);
    H264_GET_CFG_BITS_VAL(id, tmpVal, ROI1_MBY_E, coordinate_info->mby_e);
}

void H264_RoiGetRoi2Coordinate(Stream_ID_Type id, H264_ROI_Coordinate_Info_T *coordinate_info)
{
    uint32_t tmpVal;

    H264_RD_REG(id, tmpVal, VDO_H264, ROI2);
    H264_GET_CFG_BITS_VAL(id, tmpVal, ROI2_MBX_S, coordinate_info->mbx_s);
    H264_GET_CFG_BITS_VAL(id, tmpVal, ROI2_MBX_E, coordinate_info->mbx_e);
    H264_GET_CFG_BITS_VAL(id, tmpVal, ROI2_MBY_S, coordinate_info->mby_s);
    H264_GET_CFG_BITS_VAL(id, tmpVal, ROI2_MBY_E, coordinate_info->mby_e);
}

void H264_RoiGetRoi3Coordinate(Stream_ID_Type id, H264_ROI_Coordinate_Info_T *coordinate_info)
{
    uint32_t tmpVal;

    H264_RD_REG(id, tmpVal, VDO_H264, ROI3);
    H264_GET_CFG_BITS_VAL(id, tmpVal, ROI3_MBX_S, coordinate_info->mbx_s);
    H264_GET_CFG_BITS_VAL(id, tmpVal, ROI3_MBX_E, coordinate_info->mbx_e);
    H264_GET_CFG_BITS_VAL(id, tmpVal, ROI3_MBY_S, coordinate_info->mby_s);
    H264_GET_CFG_BITS_VAL(id, tmpVal, ROI3_MBY_E, coordinate_info->mby_e);
}

void H264_RoiGetRoi4Coordinate(Stream_ID_Type id, H264_ROI_Coordinate_Info_T *coordinate_info)
{
    uint32_t tmpVal;

    H264_RD_REG(id, tmpVal, VDO_H264, ROI4);
    H264_GET_CFG_BITS_VAL(id, tmpVal, ROI4_MBX_S, coordinate_info->mbx_s);
    H264_GET_CFG_BITS_VAL(id, tmpVal, ROI4_MBX_E, coordinate_info->mbx_e);
    H264_GET_CFG_BITS_VAL(id, tmpVal, ROI4_MBY_S, coordinate_info->mby_s);
    H264_GET_CFG_BITS_VAL(id, tmpVal, ROI4_MBY_E, coordinate_info->mby_e);
}

void H264_RoiGetRoi5Coordinate(Stream_ID_Type id, H264_ROI_Coordinate_Info_T *coordinate_info)
{
    uint32_t tmpVal;

    H264_RD_REG(id, tmpVal, VDO_H264, ROI5);
    H264_GET_CFG_BITS_VAL(id, tmpVal, ROI5_MBX_S, coordinate_info->mbx_s);
    H264_GET_CFG_BITS_VAL(id, tmpVal, ROI5_MBX_E, coordinate_info->mbx_e);
    H264_GET_CFG_BITS_VAL(id, tmpVal, ROI5_MBY_S, coordinate_info->mby_s);
    H264_GET_CFG_BITS_VAL(id, tmpVal, ROI5_MBY_E, coordinate_info->mby_e);
}

void H264_RoiGetRoi6Coordinate(Stream_ID_Type id, H264_ROI_Coordinate_Info_T *coordinate_info)
{
    uint32_t tmpVal;

    H264_RD_REG(id, tmpVal, VDO_H264, ROI6);
    H264_GET_CFG_BITS_VAL(id, tmpVal, ROI6_MBX_S, coordinate_info->mbx_s);
    H264_GET_CFG_BITS_VAL(id, tmpVal, ROI6_MBX_E, coordinate_info->mbx_e);
    H264_GET_CFG_BITS_VAL(id, tmpVal, ROI6_MBY_S, coordinate_info->mby_s);
    H264_GET_CFG_BITS_VAL(id, tmpVal, ROI6_MBY_E, coordinate_info->mby_e);
}

void H264_RoiGetRoi7Coordinate(Stream_ID_Type id, H264_ROI_Coordinate_Info_T *coordinate_info)
{
    uint32_t tmpVal;

    H264_RD_REG(id, tmpVal, VDO_H264, ROI7);
    H264_GET_CFG_BITS_VAL(id, tmpVal, ROI7_MBX_S, coordinate_info->mbx_s);
    H264_GET_CFG_BITS_VAL(id, tmpVal, ROI7_MBX_E, coordinate_info->mbx_e);
    H264_GET_CFG_BITS_VAL(id, tmpVal, ROI7_MBY_S, coordinate_info->mby_s);
    H264_GET_CFG_BITS_VAL(id, tmpVal, ROI7_MBY_E, coordinate_info->mby_e);
}

void H264_RoiSetIBitRatio(Stream_ID_Type id, uint32_t bit_ratio)
{
    uint32_t tmpVal;

    H264_RD_REG(id, tmpVal, VDO_H264, ROI_BIT);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, VDO_CFG_IBIT_RATIO, bit_ratio);
    H264_WR_REG(id, tmpVal, VDO_H264, ROI_BIT);
}

void H264_RoiSetPBitRatio(Stream_ID_Type id, uint32_t bit_ratio)
{
    uint32_t tmpVal;

    H264_RD_REG(id, tmpVal, VDO_H264, ROI_BIT);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, VDO_CFG_PBIT_RATIO, bit_ratio);
    H264_WR_REG(id, tmpVal, VDO_H264, ROI_BIT);
}

void H264_RoiSetN2RQPDecr(Stream_ID_Type id, uint32_t val)
{
    uint32_t tmpVal;

    H264_RD_REG(id, tmpVal, VDO_H264, ROI_QPTUNE);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, VDO_CFG_N2R_QP_DECR, val);
    H264_WR_REG(id, tmpVal, VDO_H264, ROI_QPTUNE);
}

void H264_RoiSetIQPDecr(Stream_ID_Type id, uint32_t val)
{
    uint32_t tmpVal;

    H264_RD_REG(id, tmpVal, VDO_H264, ROI_QPTUNE);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, VDO_CFG_IQP_DECR, val);
    H264_WR_REG(id, tmpVal, VDO_H264, ROI_QPTUNE);
}

void H264_RoiSetPQPDecr(Stream_ID_Type id, uint32_t val)
{
    uint32_t tmpVal;

    H264_RD_REG(id, tmpVal, VDO_H264, ROI_QPTUNE);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, VDO_CFG_PQP_DECR, val);
    H264_WR_REG(id, tmpVal, VDO_H264, ROI_QPTUNE);
}
void H264_RoiSetIBitOfst(Stream_ID_Type id, uint32_t val)
{
    uint32_t tmpVal;

    H264_RD_REG(id, tmpVal, VDO_H264, ROI_BITTUNE);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, VDO_CFG_ROI_IBIT_OFST, val);
    H264_WR_REG(id, tmpVal, VDO_H264, ROI_BITTUNE);
}
void H264_RoiSetPBitOfst(Stream_ID_Type id, uint32_t val)
{
    uint32_t tmpVal;

    H264_RD_REG(id, tmpVal, VDO_H264, ROI_BITTUNE);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, VDO_CFG_ROI_PBIT_OFST, val);
    H264_WR_REG(id, tmpVal, VDO_H264, ROI_BITTUNE);
}
void H264_NRoiSetIBitOfst(Stream_ID_Type id, uint32_t val)
{
    uint32_t tmpVal;

    H264_RD_REG(id, tmpVal, VDO_H264, ROI_BITTUNE);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, VDO_CFG_NROI_IBIT_OFST, val);
    H264_WR_REG(id, tmpVal, VDO_H264, ROI_BITTUNE);
}
void H264_NRoiSetPBitOfst(Stream_ID_Type id, uint32_t val)
{
    uint32_t tmpVal;

    H264_RD_REG(id, tmpVal, VDO_H264, ROI_BITTUNE);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, VDO_CFG_NROI_PBIT_OFST, val);
    H264_WR_REG(id, tmpVal, VDO_H264, ROI_BITTUNE);
}

void H264_RoiEnableConfig(Stream_ID_Type id)
{
    uint32_t tmpVal;

    H264_RD_REG(id, tmpVal, VDO_H264, ROI_MODE);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, VDO_CFG_ROI_UPD, 0x1);
    H264_WR_REG(id, tmpVal, VDO_H264, ROI_MODE);
}

void H264_NRSetVal(Stream_ID_Type id, int level, int strength)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDONR);
    H264_SET_BITS_VAL(id, tmpVal, NOISELEVEL, level);
    H264_SET_BITS_VAL(id, tmpVal, TEMPERALFILTERSTRENGTH, strength);
    BL_WR_REG(H264_ENC_BASE, VDONR, tmpVal);
}

void H264_NREnable(Stream_ID_Type id)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_H264_ENCODER_CTRL);
    H264_SET_CFG_BITS_VAL(id, tmpVal, VDONR_EN, 0x1);
    BL_WR_REG(H264_ENC_BASE, VDO_H264_ENCODER_CTRL, tmpVal);
}

void H264_MainPddingConfig(Stream_ID_Type id, BL_Fun_Type val)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_H264_ENCODER_CTRL);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, VDO_CFG_ZSTUF_DIS, !val);
    BL_WR_REG(H264_ENC_BASE, VDO_H264_ENCODER_CTRL, tmpVal);
}

uint32_t H264_Get_Intterupt_Status(void)
{
    uint32_t ret = 0;
    uint32_t tmpVal;

    /* check if w/r buffer overflow */

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_H264_ENCODER_CTRL);
    H264_GET_CFG_BITS_VAL(STREAM_0_ID, tmpVal, ENC_SEQ_EN, tmpVal);
    if (tmpVal == 1) { // only check overflow in seq encode mode
        tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_SRC_R_DBG);
        if (BL_IS_REG_BIT_SET(tmpVal, VDO_SRC_WR_OV_RD)) {
            //BL_LOGE("[stream 0] sync buf overflow!\r\n");
            tmpVal = BL_SET_REG_BIT(0, VDO_SRC_Y_WOVR_CLR);
            tmpVal = BL_SET_REG_BIT(tmpVal, VDO_SRC_UV_WOVR_CLR);
            BL_WR_REG(H264_ENC_BASE, VDO_SRC_STA_CLR, tmpVal);
            ret = BL_BIT_SET(ret, H264_M_OVERFLOW);
        }
    }

    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_H264_ENCODER_CTRL);
    H264_GET_CFG_BITS_VAL(STREAM_1_ID, tmpVal, ENC_SEQ_EN, tmpVal);
    if (tmpVal == 1) { // only check overflow in seq encode mode
        tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_S_SRC_R_DBG);
        if (BL_IS_REG_BIT_SET(tmpVal, VDO_S_SRC_WR_OV_RD)) {
            //BL_LOGE("[stream 1] sync buf overflow!\r\n");
            tmpVal = BL_SET_REG_BIT(0, VDO_S_SRC_Y_WOVR_CLR);
            tmpVal = BL_SET_REG_BIT(tmpVal, VDO_S_SRC_UV_WOVR_CLR);
            BL_WR_REG(H264_ENC_BASE, VDO_SRC_STA_CLR, tmpVal);
            ret = BL_BIT_SET(ret, H264_S_OVERFLOW);
        }
    }

    /* check for interrupt */
    tmpVal = BL_RD_REG(H264_ENC_BASE, VDO_INT);
    
    /* clear interrupt status */
    BL_WR_REG(H264_ENC_BASE, VDO_INT_CLR, tmpVal);
    /* handle main stream */
    if (BL_IS_REG_BIT_SET(tmpVal, VDO_FRM_DONE_INT)) {
        ret = BL_BIT_SET(ret, H264_M_FRM_DONE_INT);
    }

    if (BL_IS_REG_BIT_SET(tmpVal, VDO_SEQ_DONE_INT)) {
        ret = BL_BIT_SET(ret, H264_M_SEQ_DONE_INT);
    }

    if (BL_IS_REG_BIT_SET(tmpVal, VDO_BS_FULL_INT)) {
        ret = BL_BIT_SET(ret, H264_M_BS_FULL_INT);
    }

    /* handle second stream */
    if (BL_IS_REG_BIT_SET(tmpVal, VDO_S_FRM_DONE_INT)) {
        ret = BL_BIT_SET(ret, H264_S_FRM_DONE_INT);
    }
    
    if (BL_IS_REG_BIT_SET(tmpVal, VDO_S_SEQ_DONE_INT)) {
        ret = BL_BIT_SET(ret, H264_S_SEQ_DONE_INT);
    }

    if (BL_IS_REG_BIT_SET(tmpVal, VDO_S_BS_FULL_INT)) {
        ret = BL_BIT_SET(ret, H264_S_BS_FULL_INT);
    }
    return ret;
}

void H264_RD_FRAME_BYTECOUNT_REG(uint32_t id, uint32_t *val)
{
    if (id==STREAM_0_ID) { 
        *val = BL_RD_REG(H264_ENC_BASE, VDO_FRAME_BYTECOUNT);
    } else {
        *val = BL_RD_REG(H264_ENC_BASE, VDO_S_FRAME_BYTECOUNT);
    }
}

