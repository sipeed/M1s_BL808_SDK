#ifndef __BL808_DSP2_WDR_H__
#define __BL808_DSP2_WDR_H__

#include <bl808_dsp2.h>

#define DSP2_WDR_HIST_ROI_NUM                (8)
#define DSP2_WDR_HIST_BIN_NUM                (65)
#define DSP2_WDR_CURVE_COEF_NUM              (64)
#define DSP2_WDR_CURVE_HIST_BIN_NUM          (65)//(257)

typedef struct {
    uint32_t hist_bin[DSP2_WDR_HIST_BIN_NUM];
} DSP2_WDR_Hist_Data_Type;

typedef struct {
    uint16_t curve_coef[DSP2_WDR_CURVE_COEF_NUM];
} DSP2_WDR_Curve_Type;

void DSP2_WDR_Set_WDR_State(BL_Fun_Type state);
void DSP2_WDR_Get_WDR_State(BL_Fun_Type *state);
void DSP2_WDR_Set_CS_State(BL_Fun_Type state);
void DSP2_WDR_Get_CS_State(BL_Fun_Type *state);
void DSP2_WDR_Set_CS_Config(const DSP2_Chroma_Suppress_Type *chromaSupprCfg);
void DSP2_WDR_Get_CS_Config(DSP2_Chroma_Suppress_Type *chromaSupprCfg);
void DSP2_WDR_Set_ROI_State(int roi_id, BL_Fun_Type state);
void DSP2_WDR_Get_ROI_State(int roi_id, BL_Fun_Type *state);
void DSP2_WDR_Set_ROI_Position(int roi_id, int left_x, int right_x,
                                int top_y, int bottom_y);
void DSP2_WDR_Get_ROI_Position(int roi_id, int *left_x, int *right_x,
                                int *top_y, int *bottom_y);
void DSP2_WDR_Set_ROI_Weight(int roi_id, int weight);
void DSP2_WDR_Get_ROI_Weight(int roi_id, int *weight);
int  DSP2_WDR_Get_Hist_Data(DSP2_WDR_Hist_Data_Type *hist);
void DSP2_WDR_Set_WDR_Curve_State(BL_Fun_Type state);
void DSP2_WDR_Get_WDR_Curve_State(BL_Fun_Type *state);
void DSP2_WDR_Set_WDR_Curve(const DSP2_WDR_Curve_Type *wdr_curve);
void DSP2_WDR_Get_WDR_Curve(DSP2_WDR_Curve_Type *wdr_curve);
void DSP2_WDR_Set_WDR_Curve_Weight(int weight);
void DSP2_WDR_Get_WDR_Curve_Weight(int *weight);
void DSP2_WDR_Set_Post_Enhance_State(BL_Fun_Type state);
void DSP2_WDR_Get_Post_Enhance_State(BL_Fun_Type *state);
void DSP2_WDR_Set_Post_Enhance_Weight(int weight);
void DSP2_WDR_Get_Post_Enhance_Weight(int *weight);
void DSP2_WDR_Set_Post_Enhance_Y_Offset(int y_offset);
void DSP2_WDR_Get_Post_Enhance_Y_Offset(int *y_offset);
void DSP2_WDR_Set_Post_Enhance_Luma_Gain(int gain);
void DSP2_WDR_Get_Post_Enhance_Luma_Gain(int *gain);
void DSP2_WDR_Set_Post_Enhance_Chroma_Gain(int gain);
void DSP2_WDR_Get_Post_Enhance_Chroma_Gain(int *gain);

#endif /* __BL808_WDR_H__ */
