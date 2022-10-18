#ifndef __BL808_VENC_H__
#define __BL808_VENC_H__

#include "bl808_common.h"
#include "bl808_dvp2axi.h"



#if (BL80X_HW_VER <= BL80X_HW_A0)
#define H264_SET_BITS_VAL(id, val, bitname, bitval) \
    do {    \
        CHECK_PARAM(id == STREAM_0_ID);   \
        val = BL_SET_REG_BITS_VAL(val, VDO_##bitname, bitval);   \
    } while (0)

#define H264_GET_BITS_VAL(id, val, bitname, bitval) \
    do {    \
        CHECK_PARAM(id == STREAM_0_ID);   \
        bitval = BL_GET_REG_BITS_VAL(val, VDO_##bitname);   \
    } while (0)

#define H264_SET_CFG_BITS_VAL(id, val, bitname, bitval) \
    do {    \
        CHECK_PARAM(id == STREAM_0_ID);   \
        val = BL_SET_REG_BITS_VAL(val, VDO_CFG_##bitname, bitval);   \
    } while (0)

#define H264_RD_REG(id, val, prefix, regname) \
    do {    \
        CHECK_PARAM(id == STREAM_0_ID);   \
        val = BL_RD_REG(H264_ENC_BASE, prefix##_##regname);     \
    } while (0)

#define H264_WR_REG(id, val, prefix, regname) \
    do {    \
        CHECK_PARAM(id == STREAM_0_ID);   \
        BL_WR_REG(H264_ENC_BASE, prefix##_##regname, val);    \
    } while (0)
#else
#define H264_SET_BITS_VAL(id, val, bitname, bitval) \
    do {    \
        if (id==STREAM_0_ID) {  \
            val = BL_SET_REG_BITS_VAL(val, VDO_##bitname, bitval);   \
        } else {   \
            val = BL_SET_REG_BITS_VAL(val, VDO_S_##bitname, bitval);   \
        }   \
    } while (0)

#define H264_GET_BITS_VAL(id, val, bitname, bitval) \
    do {    \
        if (id==STREAM_0_ID) {  \
            bitval = BL_GET_REG_BITS_VAL(val, VDO_##bitname);   \
        } else {   \
            bitval = BL_GET_REG_BITS_VAL(val, VDO_S_##bitname);   \
        }   \
    } while (0)

#define H264_SET_CFG_BITS_VAL(id, val, bitname, bitval) \
    do {    \
        if (id==STREAM_0_ID) {  \
            val = BL_SET_REG_BITS_VAL(val, VDO_CFG_##bitname, bitval);   \
        } else {   \
            val = BL_SET_REG_BITS_VAL(val, VDO_CFG_S_##bitname, bitval);   \
        }   \
    } while (0)

#define H264_GET_CFG_BITS_VAL(id, val, bitname, bitval) \
    do {    \
        if (id==STREAM_0_ID) {  \
            bitval = BL_GET_REG_BITS_VAL(val, VDO_CFG_##bitname);   \
        } else {   \
            bitval = BL_GET_REG_BITS_VAL(val, VDO_CFG_S_##bitname);   \
        }   \
    } while (0)

#define H264_RD_REG(id, val, prefix, regname) \
    do {    \
        if (id==STREAM_0_ID) {  \
            val = BL_RD_REG(H264_ENC_BASE, prefix##_##regname);     \
        } else {   \
            val = BL_RD_REG(H264_ENC_BASE, prefix##_S_##regname);     \
        }   \
    } while (0)

#define H264_WR_REG(id, val, prefix, regname) \
    do {    \
        if (id==STREAM_0_ID) {  \
            BL_WR_REG(H264_ENC_BASE, prefix##_##regname, val);    \
        } else {   \
            BL_WR_REG(H264_ENC_BASE, prefix##_S_##regname, val);    \
        }   \
    } while (0)
#endif


typedef enum {
    STREAM_0_ID = 0,
    STREAM_1_ID = 1,
    STREAM_NUM = 2,
} Stream_ID_Type;

typedef enum {
    H264_NORMAL_ENC = 0,
    H264_BL_ENC = 1,
} H264_Enc_Sel_Type;

typedef enum {
    H264_RC_MODE_CBR = 0,
    H264_RC_MODE_VBR = 1,
} H264_RC_MODE_E;

typedef enum {
    H264_PROFILE_BASELINE = 0,
    H264_PROFILE_MAIN = 1,
} H264_Profile_Type;

typedef enum {
    H264_M_FRM_DONE_INT = 0,
    H264_M_SEQ_DONE_INT = 1,
    H264_M_BS_FULL_INT = 2,
    H264_M_OVERFLOW = 3,
    H264_S_FRM_DONE_INT = 4,
    H264_S_SEQ_DONE_INT = 5,
    H264_S_BS_FULL_INT = 6,
    H264_S_OVERFLOW = 7,
} H264_Int_Status_type;

typedef struct blH264_REF_FRM_ADDR_S {
    uint32_t ref_y0_base_addr;
    uint32_t ref_u0_base_addr;
    uint32_t ref_v0_base_addr;
    uint32_t ref_y1_base_addr;
    uint32_t ref_u1_base_addr;
    uint32_t ref_v1_base_addr;
    uint32_t ext_dat_base_addr;
} H264_REF_FRM_ADDR_S;

typedef struct blH264_REF_FRM_SIZE_S {
    uint32_t y_size;
    uint32_t u_v_size;
} H264_REF_FRM_SIZE_S;

typedef struct {
    int ixsize;
    int iysize;
    int xsize32;
    int ysize32;
    int uvxsize32;
    int uvysize32;
    int lsize;
    int uvsize;
    int luvsize;
} H264_Core_Size_Cfg_Type;

typedef struct {
    int target_i_qp;
    int target_p_qp;
    int iframe_min_qp;
    int iframe_max_qp;
    int num_imb_bits;
    int num_pmb_bits;
    int ip_ratio;
    int iqp_ofst;
} H264_RC_Cfg_Type;

typedef struct blH264_SRC_BUF_CFG_S {
    uint32_t yBufAddr;
    uint32_t yBufSize;
    uint32_t uvBufAddr;
    uint32_t uvBufSize;
} H264_SRC_BUF_CFG_S;

typedef struct {
    uint8_t y_src;
    uint8_t uv_src;
} H264_Src_Chann_Cfg_Type;

typedef struct {
    uint32_t mbx_s;
    uint32_t mbx_e;
    uint32_t mby_s;
    uint32_t mby_e;
} H264_ROI_Coordinate_Info_T;

typedef struct {
    uint32_t absmv_sum;
    uint16_t nzmv_mbcnt;
    uint16_t intra_mbcnt;
} H264_MB_Info_T;

void H264_Init(void);
void H264_Enable_CRef(Stream_ID_Type id, BL_Fun_Type enable);
void H264_SetDualEnc(BL_Fun_Type newState);
void H264_SetSwMode(BL_Fun_Type newState);
void H264_SetResolution(Stream_ID_Type id, uint32_t width, uint32_t height);
void H264_SetSrcFrameBuf(Stream_ID_Type id, H264_SRC_BUF_CFG_S *src_buf, uint16_t src_h, uint16_t h);
void H264_SetSrcBufCtlCfg(Stream_ID_Type id, uint8_t numSrcFrm, uint32_t FrmYMemSize);
void H264_SetSrcChannel(Stream_ID_Type id, H264_Src_Chann_Cfg_Type *dvp);
void H264_SetBitstreamBuf(Stream_ID_Type id, uint32_t bufAddr, uint32_t bufSize);
void H264_SetBitstreamBufThreshold(Stream_ID_Type id, uint32_t threshold);
void H264_GetBSTotalByte(Stream_ID_Type id, uint32_t *total_byte);
#if NEW_REF_FRM_CFG_API
void H264_SetRefFrmMemPlusExtData(Stream_ID_Type id, H264_REF_FRM_ADDR_S *ref_addr);
#else
void H264_SetRefFrmMemPlusExtData(Stream_ID_Type id, uint32_t ref_addr);
#endif
void H264_SetVUITimeScale(Stream_ID_Type id, uint32_t timeScale);
void H264_SetVUINumUnitsInTick(Stream_ID_Type id, uint32_t numUnitsInTick);
void H264_SetRateCtrlCfg(Stream_ID_Type id, const H264_RC_Cfg_Type *cfg);
void H264_GetRateCtrlCfg(Stream_ID_Type id, H264_RC_Cfg_Type *cfg);
void H264_SetRateCtrlQP(Stream_ID_Type id, int target_i_qp, int target_p_qp);
void H264_UpdateSPS(Stream_ID_Type id);
void H264_UpdateRC(Stream_ID_Type id);
void H264_SetDefaultCoreCfg(Stream_ID_Type id);
void H264_SetCoreSizeCfg(Stream_ID_Type id, H264_Core_Size_Cfg_Type *cfg);
void H264_SetGOPSize(Stream_ID_Type id, uint32_t gopSize);
void H264_SetProfile(Stream_ID_Type id, H264_Profile_Type profile);
void H264_EnableDeblock(Stream_ID_Type id, BL_Fun_Type enable);
void H264_StartEnc(Stream_ID_Type id, BL_Fun_Type sw_mode);
void H264_StopEnc(Stream_ID_Type id);
void H264_DisableCoreEnc(Stream_ID_Type id);
void H264_Reset_HW_Status(Stream_ID_Type id);


void H264_SetPrefetchMode(Stream_ID_Type id, BL_Fun_Type newState);
void H264_SetPrefetchCfg(Stream_ID_Type id, uint8_t mbHeight);
void H264_SetPrefetchBuffer(Stream_ID_Type id, uint32_t YRefAddr, uint32_t UVRefAddr);
void H264_IsCurrentPFrame(Stream_ID_Type id, BL_Sts_Type *status);
void H264_EnableSPSOnEachGOP(Stream_ID_Type id, BL_Fun_Type newState);
void H264_EnableSramckModeOld(BL_Fun_Type newState);


void H264_FRAME_DONE_IRQHandler(void);
void H264_SEQ_DONE_IRQHandler(void);
void H264_BS_FULL_IRQHandler(void);
void H264_S_FRAME_DONE_IRQHandler(void);
void H264_S_SEQ_DONE_IRQHandler(void);
void H264_S_BS_FULL_IRQHandler(void);

void H264_SetBufferSyncFlag(Stream_ID_Type id);
uint16_t H264_GetYSrcHeight(Stream_ID_Type id);
uint16_t H264_GetCSrcHeight(Stream_ID_Type id);
uint16_t H264_GetFrameHeight(Stream_ID_Type id);
uint16_t H264_GetFrameWidth(Stream_ID_Type id);
void H264_SetBufferByteCnt(Stream_ID_Type id, uint32_t y_src_height,
                                     uint32_t c_src_height, uint32_t width);
uint16_t H264_GetIntraMBCnt(Stream_ID_Type id);
void H264_GetMbInfo(Stream_ID_Type id, H264_MB_Info_T *info);


/* Roi API */
void H264_RoiSetRoi0Coordinate(Stream_ID_Type id, H264_ROI_Coordinate_Info_T *coordinate_info);
void H264_RoiSetRoi1Coordinate(Stream_ID_Type id, H264_ROI_Coordinate_Info_T *coordinate_info);
void H264_RoiSetRoi2Coordinate(Stream_ID_Type id, H264_ROI_Coordinate_Info_T *coordinate_info);
void H264_RoiSetRoi3Coordinate(Stream_ID_Type id, H264_ROI_Coordinate_Info_T *coordinate_info);
void H264_RoiSetRoi4Coordinate(Stream_ID_Type id, H264_ROI_Coordinate_Info_T *coordinate_info);
void H264_RoiSetRoi5Coordinate(Stream_ID_Type id, H264_ROI_Coordinate_Info_T *coordinate_info);
void H264_RoiSetRoi6Coordinate(Stream_ID_Type id, H264_ROI_Coordinate_Info_T *coordinate_info);
void H264_RoiSetRoi7Coordinate(Stream_ID_Type id, H264_ROI_Coordinate_Info_T *coordinate_info);
uint8_t  H264_RoiGetEnPositonVal(Stream_ID_Type id);
void  H264_RoiResetEnPositonVal(Stream_ID_Type id);
void H264_RoiGetRoi0Coordinate(Stream_ID_Type id, H264_ROI_Coordinate_Info_T *coordinate_info);
void H264_RoiGetRoi1Coordinate(Stream_ID_Type id, H264_ROI_Coordinate_Info_T *coordinate_info);
void H264_RoiGetRoi2Coordinate(Stream_ID_Type id, H264_ROI_Coordinate_Info_T *coordinate_info);
void H264_RoiGetRoi3Coordinate(Stream_ID_Type id, H264_ROI_Coordinate_Info_T *coordinate_info);
void H264_RoiGetRoi4Coordinate(Stream_ID_Type id, H264_ROI_Coordinate_Info_T *coordinate_info);
void H264_RoiGetRoi5Coordinate(Stream_ID_Type id, H264_ROI_Coordinate_Info_T *coordinate_info);
void H264_RoiGetRoi6Coordinate(Stream_ID_Type id, H264_ROI_Coordinate_Info_T *coordinate_info);
void H264_RoiGetRoi7Coordinate(Stream_ID_Type id, H264_ROI_Coordinate_Info_T *coordinate_info);
void H264_RoiSetIBitRatio(Stream_ID_Type id, uint32_t bit_ratio);
void H264_RoiSetPBitRatio(Stream_ID_Type id, uint32_t bit_ratio);
void H264_RoiSetN2RQPDecr(Stream_ID_Type id, uint32_t val);
void H264_RoiSetIQPDecr(Stream_ID_Type id, uint32_t val);
void H264_RoiSetPQPDecr(Stream_ID_Type id, uint32_t val);
void H264_RoiSetIBitOfst(Stream_ID_Type id, uint32_t val);
void H264_RoiSetPBitOfst(Stream_ID_Type id, uint32_t val);
void H264_NRoiSetIBitOfst(Stream_ID_Type id, uint32_t val);
void H264_NRoiSetPBitOfst(Stream_ID_Type id, uint32_t val);
void H264_RoiEnableConfig(Stream_ID_Type id);

/* 3DNR API */
void H264_NRSetVal(Stream_ID_Type id, int level, int strength);
void H264_NREnable(Stream_ID_Type id);

/* Padding zero stuffing when Main profile */
void H264_MainPddingConfig(Stream_ID_Type id, BL_Fun_Type val);

/* Set VRAM base address of additional line buffer
 * for prefetch on and filter on
*/
void H264_SetLineBufferAddr(uint32_t addr);

uint32_t H264_Get_Intterupt_Status(void);
void H264_RD_FRAME_BYTECOUNT_REG(uint32_t id, uint32_t *val);
#endif /* __BL808_VENC_H__ */

