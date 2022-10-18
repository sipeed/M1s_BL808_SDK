#ifndef __API_AWB_H__
#define __API_AWB_H__

#include "img_api_struct.h"
#include "api_struct.h"

BL_SINT32 MM_DSP2_AWBAlgo(AWB_ALGO algo);
//BL_SINT32 MM_DSP2_AWBSendCmd(BL_UINT32 u32Cmd,BL_VOID *param);
BL_SINT32 MM_DSP2_GetAwbStats(DSP2_AWB_STATS *stats);
BL_SINT32 MM_DSP2_GetAwbCfg(AWB_DEFAULT_CFG *cfg);
BL_SINT32 MM_DSP2_SetAwbInfo(const DSP2_AWB_WB_INFO *info);
BL_SINT32 MM_DSP2_GetAwbInfo(DSP2_AWB_WB_INFO *info);
BL_SINT32 MM_DSP2_SetAwbAttr(const DSP2_AWB_ATTR *attr);
BL_SINT32 MM_DSP2_GetAwbAttr(DSP2_AWB_ATTR *attr);


#endif
