#ifndef __BL808_MJEPG_H__
#define __BL808_MJEPG_H__

#include <bl808_common.h>
#include <bl808_dvp2axi.h>


typedef enum {
    MJPEG_QUANT_MODE_100 = 0,
    MJPEG_QUANT_MODE_75 = 1,
    MJPEG_QUANT_MODE_50 = 2,
    MJPEG_QUANT_MODE_25 = 3,
    MJPEG_QUANT_MODE_10 = 4,
    MJPEG_QUANT_MODE_5 = 5,
} MJPEG_Quant_Mode_Type;

typedef enum {
    MJPEG_ENC_AUTO_MODE = 0,
    MJPEG_ENC_SW_MODE = 1,
    MJPEG_ENC_SNAPSHOT_MODE = 2,
} MJPEG_Enc_Mode_Type;

typedef enum {
    MJPEG_ENC_INT_NORMAL = 0,
    MJPEG_ENC_INT_CAM = 1,
    MJPEG_ENC_INT_MEM = 2,
    MJPEG_ENC_INT_FRAME = 3,
    MJPEG_ENC_INT_IDLE = 4,
    MJPEG_ENC_INT_MAX,
} MJPEG_Enc_Int_Type;

typedef struct {
    uint32_t width;
    uint32_t height;
} MJPEG_Cfg_Type;

typedef struct {
    uint8_t y_src;
    uint8_t uv_src;
} MJPEG_Src_Chann_Cfg_Type;

void MJENC_Init(void);
void MJENC_SetHeaderSize(uint32_t size);
void MJENC_SetResolution(const MJPEG_Cfg_Type *cfg);
void MJENC_SetSrcBuf_Y(uint32_t bufAddr, uint16_t blkRowCnt);
void MJENC_SetSrcBuf_UV(uint32_t bufAddr, uint16_t blkRowCnt);
void MJENC_SetSrcChannel(MJPEG_Src_Chann_Cfg_Type *portCfg);
void MJENC_SetBitstreamBuf(uint32_t bufAddr, uint32_t bufSize);
void MJENC_SetQuality(MJPEG_Quant_Mode_Type quality);
void MJENC_StartEnc(MJPEG_Enc_Mode_Type mode);
void MJENC_StopEnc(void);
void MJENC_PopStreamFifo(void);
void MJENC_ClearIntrFlag(void);
uint32_t MJENC_Get_Int_Status(void);
void MJENC_Get_Frame(uint8_t **ptr, uint32_t *len);

/* Set Q_table */
void MJENC_SetQTableOffset0(int val1, int val2);
void MJENC_SetQTableOffset1(int val1, int val2);
void MJENC_SetQTableOffset2(int val1, int val2);
void MJENC_SetQTableOffset3(int val1, int val2);
void MJENC_SetQTableOffset4(int val1, int val2);
void MJENC_SetQTableOffset5(int val1, int val2);
void MJENC_SetQTableOffset6(int val1, int val2);
void MJENC_SetQTableOffset7(int val1, int val2);
void MJENC_SetQTableOffset8(int val1, int val2);
void MJENC_SetQTableOffset9(int val1, int val2);
void MJENC_SetQTableOffset10(int val1, int val2);
void MJENC_SetQTableOffset11(int val1, int val2);
void MJENC_SetQTableOffset12(int val1, int val2);
void MJENC_SetQTableOffset13(int val1, int val2);
void MJENC_SetQTableOffset14(int val1, int val2);
void MJENC_SetQTableOffset15(int val1, int val2);
void MJENC_SetQTableOffset16(int val1, int val2);
void MJENC_SetQTableOffset17(int val1, int val2);
void MJENC_SetQTableOffset18(int val1, int val2);
void MJENC_SetQTableOffset19(int val1, int val2);
void MJENC_SetQTableOffset20(int val1, int val2);
void MJENC_SetQTableOffset21(int val1, int val2);
void MJENC_SetQTableOffset22(int val1, int val2);
void MJENC_SetQTableOffset23(int val1, int val2);
void MJENC_SetQTableOffset24(int val1, int val2);
void MJENC_SetQTableOffset25(int val1, int val2);
void MJENC_SetQTableOffset26(int val1, int val2);
void MJENC_SetQTableOffset27(int val1, int val2);
void MJENC_SetQTableOffset28(int val1, int val2);
void MJENC_SetQTableOffset29(int val1, int val2);
void MJENC_SetQTableOffset30(int val1, int val2);
void MJENC_SetQTableOffset31(int val1, int val2);
void MJENC_SetQTableOffset32(int val1, int val2);
void MJENC_SetQTableOffset33(int val1, int val2);
void MJENC_SetQTableOffset34(int val1, int val2);
void MJENC_SetQTableOffset35(int val1, int val2);
void MJENC_SetQTableOffset36(int val1, int val2);
void MJENC_SetQTableOffset37(int val1, int val2);
void MJENC_SetQTableOffset38(int val1, int val2);
void MJENC_SetQTableOffset39(int val1, int val2);
void MJENC_SetQTableOffset40(int val1, int val2);
void MJENC_SetQTableOffset41(int val1, int val2);
void MJENC_SetQTableOffset42(int val1, int val2);
void MJENC_SetQTableOffset43(int val1, int val2);
void MJENC_SetQTableOffset44(int val1, int val2);
void MJENC_SetQTableOffset45(int val1, int val2);
void MJENC_SetQTableOffset46(int val1, int val2);
void MJENC_SetQTableOffset47(int val1, int val2);
void MJENC_SetQTableOffset48(int val1, int val2);
void MJENC_SetQTableOffset49(int val1, int val2);
void MJENC_SetQTableOffset50(int val1, int val2);
void MJENC_SetQTableOffset51(int val1, int val2);
void MJENC_SetQTableOffset52(int val1, int val2);
void MJENC_SetQTableOffset53(int val1, int val2);
void MJENC_SetQTableOffset54(int val1, int val2);
void MJENC_SetQTableOffset55(int val1, int val2);
void MJENC_SetQTableOffset56(int val1, int val2);
void MJENC_SetQTableOffset57(int val1, int val2);
void MJENC_SetQTableOffset58(int val1, int val2);
void MJENC_SetQTableOffset59(int val1, int val2);
void MJENC_SetQTableOffset60(int val1, int val2);
void MJENC_SetQTableOffset61(int val1, int val2);
void MJENC_SetQTableOffset62(int val1, int val2);
void MJENC_SetQTableOffset63(int val1, int val2);
uint8_t MJENC_GetQTableCurrentBufIndex();
void MJENC_EnableQTable();


#endif /* __BL808_MJEPG_H__ */

