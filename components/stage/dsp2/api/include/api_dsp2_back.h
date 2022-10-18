#ifndef __API_DSP2_BACK_H__
#define __API_DSP2_BACK_H__

#include "img_api_struct.h"

BL_SINT32 MM_DSP2_SetCcmAttr(const DSP2_CCM_ATTR *attr);
BL_SINT32 MM_DSP2_GetCcmAttr(DSP2_CCM_ATTR *attr);

BL_SINT32 MM_DSP2_SetGammaAttr(const DSP2_GAMMA_ATTR *attr);
BL_SINT32 MM_DSP2_GetGammaAttr(DSP2_GAMMA_ATTR *attr);

BL_SINT32 MM_DSP2_SetWdrAttr(const DSP2_WDR_ATTR *attr);
BL_SINT32 MM_DSP2_GetWdrAttr(DSP2_WDR_ATTR *attr);

BL_SINT32 MM_DSP2_SetSaturationAttr(const DSP2_SAT_ATTR *attr);
BL_SINT32 MM_DSP2_GetSaturationAttr(DSP2_SAT_ATTR *attr);

BL_SINT32 MM_DSP2_SetNrAttr(const DSP2_NR_ATTR *attr);
BL_SINT32 MM_DSP2_GetNrAttr(DSP2_NR_ATTR *attr);

BL_SINT32 MM_DSP2_SetEeAttr(const DSP2_EE_ATTR *attr);
BL_SINT32 MM_DSP2_GetEeAttr(DSP2_EE_ATTR *attr);

BL_SINT32 MM_DSP2_SetCsAttr(const DSP2_CS_ATTR *attr);
BL_SINT32 MM_DSP2_GetCsAttr(DSP2_CS_ATTR *attr);

BL_SINT32 MM_DSP2_SetYcAttr(const DSP2_YC_ATTR *attr);
BL_SINT32 MM_DSP2_GetYcAttr(DSP2_YC_ATTR *attr);


#endif
