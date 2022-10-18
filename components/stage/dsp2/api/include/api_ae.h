#ifndef __API_AE_H__
#define __API_AE_H__

#include "img_api_struct.h"
#include "api_struct.h"

BL_SINT32 MM_DSP2_AEAlgo(AE_ALGO algo);
//BL_SINT32 MM_DSP2_AESendCmd(BL_UINT32 u32Cmd,BL_VOID *param);
BL_SINT32 MM_DSP2_GetAeStats(DSP2_AE_STATS * stats);
BL_SINT32 MM_DSP2_SetAeInfo(const DSP2_AE_INFO *info);
BL_SINT32 MM_DSP2_GetAeInfo(DSP2_AE_INFO *info);
BL_SINT32 MM_DSP2_SetAeAttr(const DSP2_AE_ATTR *attr);
BL_SINT32 MM_DSP2_GetAeAttr(DSP2_AE_ATTR *attr);

#endif
