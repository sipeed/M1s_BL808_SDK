#ifndef __API_DSP2_FRONT_H__
#define __API_DSP2_FRONT_H__

#include "img_api_struct.h"

BL_SINT32 MM_DSP2_SetBlcAttr(const DSP2_BLC_ATTR *attr);
BL_SINT32 MM_DSP2_GetBlcAttr(DSP2_BLC_ATTR *attr);

BL_SINT32 MM_DSP2_SetDpcAttr(const DSP2_DPC_ATTR *attr);
BL_SINT32 MM_DSP2_GetDpcAttr(DSP2_DPC_ATTR *attr);

BL_SINT32 MM_DSP2_SetBnrAttr(const DSP2_BNR_ATTR *attr);
BL_SINT32 MM_DSP2_GetBnrAttr(DSP2_BNR_ATTR *attr);

BL_SINT32 MM_DSP2_SetLscAttr(const DSP2_LSC_ATTR *attr);
BL_SINT32 MM_DSP2_GetLscAttr(DSP2_LSC_ATTR *attr);


#endif
