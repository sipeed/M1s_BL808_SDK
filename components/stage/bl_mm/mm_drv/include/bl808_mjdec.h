#ifndef __BL808_MJDEC_H__
#define __BL808_MJDEC_H__

#include <bl808_common.h>



typedef enum {
    MJDEC_QUANT_MODE_100 = 0,
    MJDEC_QUANT_MODE_75 = 1,
    MJDEC_QUANT_MODE_50 = 2,
    MJDEC_QUANT_MODE_25 = 3,
    MJDEC_QUANT_MODE_10 = 4,
    MJDEC_QUANT_MODE_5 = 5,
} MJDEC_Quant_Mode_Type;

typedef enum {
    MJDEC_YUV420_PLANAR = 0,
    MJDEC_YUV400_GREY_SCALE = 1,
    MJDEC_YUV422_PLANAR = 2,
} MJDEC_YUV_Format_Type;

void MJDEC_Init(void);
void MJDEC_SetYuvFormat(MJDEC_YUV_Format_Type format);
void MJDEC_SetResolution(uint32_t width, uint32_t height);
void MJDEC_PushSrcFrame(uint32_t bufAddr);
void MJDEC_SetYFrameAddr(uint32_t bufAddr);
void MJDEC_SetUVFrameAddr(uint32_t bufAddr);
void MJDEC_SetQuality(MJDEC_Quant_Mode_Type quality);
void MJDEC_StartDec(void);
void MJDEC_StopDec(void);
void MJDEC_ClearIntrFlag(void);


#endif /* __BL808_MJDEC_H__ */

