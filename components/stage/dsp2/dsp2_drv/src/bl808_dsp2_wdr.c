#include <bl808_dsp2_wdr.h>
#include <dsp2_tg_reg.h>
#include <dsp2_auto_reg.h>
#include <dsp2_blae_reg.h>
#include <dsp2_blawb_reg.h>
#include <dsp2_gamma_reg.h>

#include <dsp2_front_reg.h>
#include <dsp2_middle_reg.h>
#include <dsp2_middle2_reg.h>
#include <dsp2_middle3_reg.h>
#include <dsp2_middle4_reg.h>
#include <dsp2_middle5_reg.h>
#include <dsp2_blback_reg.h>

#define DSP2_WDR_ROI_WEIGHT_MAX                      (15)
#define DSP2_WDR_CURVE_WEIGHT_MAX                    (16)
#define DSP2_WDR_POST_ENHANCE_WEIGHT_MAX             (16)
#define DSP2_WDR_POST_ENHANCE_Y_OFFSET_MAX           ((1 << 12) - 1)
#define DSP2_WDR_POST_ENHANCE_Y_GAIN_MAX             ((1 << 15) - 1)
#define DSP2_WDR_POST_ENHANCE_C_GAIN_MAX             ((1 << 15) - 1)


void DSP2_WDR_Get_WDR_State(BL_Fun_Type *state)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_0);

    if (BL_IS_REG_BIT_SET(tmpVal, DSP2_BLBACK_WDR_EN_PRE)) {
        *state = ENABLE;
    } else {
        *state = DISABLE;
    }
}

void DSP2_WDR_Set_WDR_State(BL_Fun_Type state)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_0);
    if (ENABLE == state) {
        tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_BLBACK_WDR_EN_PRE);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_BLBACK_WDR_EN_PRE);
    }
    BL_WR_REG(DSP2_BASE, DSP2_BLBACK_WDR_0, tmpVal);
}

void DSP2_WDR_Set_CS_State(BL_Fun_Type state)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_CS_0);
    if (ENABLE == state) {
        tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_BLBACK_WDR_CS_EN_PRE);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_BLBACK_WDR_CS_EN_PRE);
    }
    BL_WR_REG(DSP2_BASE, DSP2_BLBACK_WDR_CS_0, tmpVal);
}

void DSP2_WDR_Get_CS_State(BL_Fun_Type *state)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_CS_0);

    if (BL_IS_REG_BIT_SET(tmpVal, DSP2_BLBACK_WDR_CS_EN_PRE)) {
        *state = ENABLE;
    } else {
        *state = DISABLE;
    }
}

void DSP2_WDR_Set_CS_Config(const DSP2_Chroma_Suppress_Type *chromaSupprCfg)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_WDR_CS_GAIN_PRE, chromaSupprCfg->gain);
    BL_WR_REG(DSP2_BASE, DSP2_BLBACK_WDR_0, tmpVal);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_CS_0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_WDR_CS_WEIGHT_PRE, chromaSupprCfg->weight);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_WDR_CS_GREY_TH_PRE, chromaSupprCfg->grey_thr);
    BL_WR_REG(DSP2_BASE, DSP2_BLBACK_WDR_CS_0, tmpVal);
}

void DSP2_WDR_Get_CS_Config(DSP2_Chroma_Suppress_Type *chromaSupprCfg)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_0);
    chromaSupprCfg->gain = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_WDR_CS_GAIN_PRE);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_CS_0);
    chromaSupprCfg->weight = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_WDR_CS_WEIGHT_PRE);
    chromaSupprCfg->grey_thr = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_WDR_CS_GREY_TH_PRE);
}

void DSP2_WDR_Set_ROI_State(int roi_id, BL_Fun_Type state)
{
    uint32_t tmpVal;

    switch(roi_id)
    {
        case 0:
        case 1:
            tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_1);
            if (roi_id & 0x01) {
                tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_ROI1_EN_PRE, state);
            } else {
                tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_ROI0_EN_PRE, state);
            }
            BL_WR_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_1, tmpVal);
            break;
        case 2:
        case 3:
            tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_2);
            if (roi_id & 0x01) {
                tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_ROI3_EN_PRE, state);
            } else {
                tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_ROI2_EN_PRE, state);
            }
            BL_WR_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_2, tmpVal);
            break;
        case 4:
        case 5:
            tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_3);
            if (roi_id & 0x01) {
                tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_ROI5_EN_PRE, state);
            } else {
                tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_ROI4_EN_PRE, state);
            }
            BL_WR_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_3, tmpVal);
            break;
        case 6:
        case 7:
            tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_4);
            if (roi_id & 0x01) {
                tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_ROI7_EN_PRE, state);
            } else {
                tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_ROI6_EN_PRE, state);
            }
            BL_WR_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_4, tmpVal);
            break;
    }
}

void DSP2_WDR_Get_ROI_State(int roi_id, BL_Fun_Type *state)
{
    uint32_t tmpVal;

    switch(roi_id)
    {
        case 0:
        case 1:
            tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_1);
            if (roi_id & 0x01) {
                tmpVal = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_ROI1_EN_PRE);
            } else {
                tmpVal = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_ROI0_EN_PRE);
            }
            if (tmpVal == 1) {
                *state = ENABLE;
            } else {
                *state = DISABLE;
            }
            break;
        case 2:
        case 3:
            tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_2);
            if (roi_id & 0x01) {
                tmpVal = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_ROI3_EN_PRE);
            } else {
                tmpVal = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_ROI2_EN_PRE);
            }
            if (tmpVal == 1) {
                *state = ENABLE;
            } else {
                *state = DISABLE;
            }
            break;
        case 4:
        case 5:
            tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_3);
            if (roi_id & 0x01) {
                tmpVal = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_ROI5_EN_PRE);
            } else {
                tmpVal = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_ROI4_EN_PRE);
            }
            if (tmpVal == 1) {
                *state = ENABLE;
            } else {
                *state = DISABLE;
            }
            break;
        case 6:
        case 7:
            tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_4);
            if (roi_id & 0x01) {
                tmpVal = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_ROI7_EN_PRE);
            } else {
                tmpVal = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_ROI6_EN_PRE);
            }
            if (tmpVal == 1) {
                *state = ENABLE;
            } else {
                *state = DISABLE;
            }
            break;
    }
}

void DSP2_WDR_Set_ROI_Position(int roi_id, int left_x, int right_x,
                                int top_y, int bottom_y)
{
    uint32_t tmpVal;

    switch(roi_id)
    {
        case 0:
            tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_5);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_X0_MIN_PRE, left_x);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_X0_MAX_PRE, right_x);
            BL_WR_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_5, tmpVal);
            tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_6);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_Y0_MIN_PRE, top_y);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_Y0_MAX_PRE, bottom_y);
            BL_WR_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_6, tmpVal);
            break;
        case 1:
            tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_7);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_X1_MIN_PRE, left_x);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_X1_MAX_PRE, right_x);
            BL_WR_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_7, tmpVal);
            tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_8);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_Y1_MIN_PRE, top_y);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_Y1_MAX_PRE, bottom_y);
            BL_WR_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_8, tmpVal);
            break;
        case 2:
            tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_9);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_X2_MIN_PRE, left_x);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_X2_MAX_PRE, right_x);
            BL_WR_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_9, tmpVal);
            tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_10);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_Y2_MIN_PRE, top_y);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_Y2_MAX_PRE, bottom_y);
            BL_WR_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_10, tmpVal);
            break;
        case 3:
            tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_11);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_X3_MIN_PRE, left_x);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_X3_MAX_PRE, right_x);
            BL_WR_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_11, tmpVal);
            tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_12);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_Y3_MIN_PRE, top_y);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_Y3_MAX_PRE, bottom_y);
            BL_WR_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_12, tmpVal);
            break;
        case 4:
            tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_13);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_X4_MIN_PRE, left_x);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_X4_MAX_PRE, right_x);
            BL_WR_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_13, tmpVal);
            tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_14);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_Y4_MIN_PRE, top_y);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_Y4_MAX_PRE, bottom_y);
            BL_WR_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_14, tmpVal);
            break;
        case 5:
            tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_15);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_X5_MIN_PRE, left_x);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_X5_MAX_PRE, right_x);
            BL_WR_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_15, tmpVal);
            tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_16);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_Y5_MIN_PRE, top_y);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_Y5_MAX_PRE, bottom_y);
            BL_WR_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_16, tmpVal);
            break;
        case 6:
            tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_17);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_X6_MIN_PRE, left_x);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_X6_MAX_PRE, right_x);
            BL_WR_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_17, tmpVal);
            tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_18);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_Y6_MIN_PRE, top_y);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_Y6_MAX_PRE, bottom_y);
            BL_WR_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_18, tmpVal);
            break;
        case 7:
            tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_19);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_X7_MIN_PRE, left_x);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_X7_MAX_PRE, right_x);
            BL_WR_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_19, tmpVal);
            tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_20);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_Y7_MIN_PRE, top_y);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_Y7_MAX_PRE, bottom_y);
            BL_WR_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_20, tmpVal);
            break;
    }
}

void DSP2_WDR_Get_ROI_Position(int roi_id, int *left_x, int *right_x,
                                int *top_y, int *bottom_y)
{
    uint32_t tmpVal;

    switch(roi_id)
    {
        case 0:
            tmpVal  = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_5);
            *left_x = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_X0_MIN_PRE);
            *right_x = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_X0_MAX_PRE);
            tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_6);
            *top_y = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_Y0_MIN_PRE);
            *bottom_y = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_Y0_MAX_PRE);
            break;
        case 1:
            tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_7);
            *left_x = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_X1_MIN_PRE);
            *right_x = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_X1_MAX_PRE);
            tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_8);
            *top_y = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_Y1_MIN_PRE);
            *bottom_y = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_Y1_MAX_PRE);
            break;
        case 2:
            tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_9);
            *left_x = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_X2_MIN_PRE);
            *right_x = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_X2_MAX_PRE);
            tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_10);
            *top_y = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_Y2_MIN_PRE);
            *bottom_y = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_Y2_MAX_PRE);
            break;
        case 3:
            tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_11);
            *left_x = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_X3_MIN_PRE);
            *right_x = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_X3_MAX_PRE);
            tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_12);
            *top_y = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_Y3_MIN_PRE);
            *bottom_y = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_Y3_MAX_PRE);
            break;
        case 4:
            tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_13);
            *left_x = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_X4_MIN_PRE);
            *right_x = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_X4_MAX_PRE);
            tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_14);
            *top_y = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_Y4_MIN_PRE);
            *bottom_y = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_Y4_MAX_PRE);
            break;
        case 5:
            tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_15);
            *left_x = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_X5_MIN_PRE);
            *right_x = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_X5_MAX_PRE);
            tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_16);
            *top_y = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_Y5_MIN_PRE);
            *bottom_y = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_Y5_MAX_PRE);
            break;
        case 6:
            tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_17);
            *left_x = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_X6_MIN_PRE);
            *right_x = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_X6_MAX_PRE);
            tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_18);
            *top_y = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_Y6_MIN_PRE);
            *bottom_y = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_Y6_MAX_PRE);
            break;
        case 7:
            tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_19);
            *left_x = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_X7_MIN_PRE);
            *right_x = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_X7_MAX_PRE);
            tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_20);
            *top_y = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_Y7_MIN_PRE);
            *bottom_y = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_Y7_MAX_PRE);
            break;
    }
}

void DSP2_WDR_Set_ROI_Weight(int roi_id, int weight)
{
    uint32_t tmpVal;

    CHECK_PARAM_MAX(weight, DSP2_WDR_ROI_WEIGHT_MAX);

    switch(roi_id)
    {
        case 0:
        case 1:
            tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_1);
            if (roi_id & 0x01) {
                tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_ROI1_WEIGHT_PRE, weight);
            } else {
                tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_ROI0_WEIGHT_PRE, weight);
            }
            BL_WR_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_1, tmpVal);
            break;
        case 2:
        case 3:
            tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_2);
            if (roi_id & 0x01) {
                tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_ROI3_WEIGHT_PRE, weight);
            } else {
                tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_ROI2_WEIGHT_PRE, weight);
            }
            BL_WR_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_2, tmpVal);
            break;
        case 4:
        case 5:
            tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_3);
            if (roi_id & 0x01) {
                tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_ROI5_WEIGHT_PRE, weight);
            } else {
                tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_ROI4_WEIGHT_PRE, weight);
            }
            BL_WR_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_3, tmpVal);
            break;
        case 6:
        case 7:
            tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_4);
            if (roi_id & 0x01) {
                tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_ROI7_WEIGHT_PRE, weight);
            } else {
                tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_ROI6_WEIGHT_PRE, weight);
            }
            BL_WR_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_4, tmpVal);
            break;
    }
}

void DSP2_WDR_Get_ROI_Weight(int roi_id, int *weight)
{
    uint32_t tmpVal;

    CHECK_PARAM_MAX(*weight, DSP2_WDR_ROI_WEIGHT_MAX);

    switch(roi_id)
    {
        case 0:
        case 1:
            tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_1);
            if (roi_id & 0x01) {
                *weight = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_ROI1_WEIGHT_PRE);
            } else {
                *weight = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_ROI0_WEIGHT_PRE);
            }
            break;
        case 2:
        case 3:
            tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_2);
            if (roi_id & 0x01) {
                *weight = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_ROI3_WEIGHT_PRE);
            } else {
                *weight = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_ROI2_WEIGHT_PRE);
            }
            break;
        case 4:
        case 5:
            tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_3);
            if (roi_id & 0x01) {
                *weight = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_ROI5_WEIGHT_PRE);
            } else {
                *weight = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_ROI4_WEIGHT_PRE);
            }
            break;
        case 6:
        case 7:
            tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_HIST_4);
            if (roi_id & 0x01) {
                *weight = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_ROI7_WEIGHT_PRE);
            } else {
                *weight = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_HIST_ROI6_WEIGHT_PRE);
            }
            break;
    }
}


int DSP2_WDR_Get_Hist_Data(DSP2_WDR_Hist_Data_Type *hist)
{
    uint32_t tmpVal;
    uint32_t buf_idx;
    uint32_t buf_addr;
    uint32_t w_cnt_idx_start;
    uint32_t w_cnt_idx_end;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_0);
    buf_idx = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_BLWDR_BUF_IDX_R);
    w_cnt_idx_start = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_BLWDR_W_CNT_R);

    if (0 == buf_idx) {
        buf_addr = DSP2_BASE + DSP2_BLBACK_REG_HIST0_0_OFFSET;
        hist->hist_bin[64] = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_REG_HIST0_64);
    } else {
        buf_addr = DSP2_BASE + DSP2_BLBACK_REG_HIST1_0_OFFSET;
        hist->hist_bin[64] = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_REG_HIST1_64);
    }

    /* copy all the histogram bin except for the last one */
    BL60X_MemCpy4(&hist->hist_bin[0], (uint32_t*)buf_addr, 64);

    w_cnt_idx_end = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_BLWDR_W_CNT_R);
    if (w_cnt_idx_start != w_cnt_idx_end) {
        BL_LOGW("wdr statistics overwrite!");
        return -1;
    }

    return 0;
}

void DSP2_WDR_Set_WDR_Curve_State(BL_Fun_Type state)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_CURVE_33);
    if (ENABLE == state) {
        tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_BLBACK_CURVE_EN_PRE);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_BLBACK_CURVE_EN_PRE);
    }
    BL_WR_REG(DSP2_BASE, DSP2_BLBACK_WDR_CURVE_33, tmpVal);
}

void DSP2_WDR_Get_WDR_Curve_State(BL_Fun_Type *state)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_CURVE_33);

    if (BL_IS_REG_BIT_SET(tmpVal, DSP2_BLBACK_CURVE_EN_PRE)) {
        *state = ENABLE;
    } else {
        *state = DISABLE;
    }
}

void DSP2_WDR_Set_WDR_Curve(const DSP2_WDR_Curve_Type *wdr_curve)
{
    BL60X_MemCpy4((uint32_t*)(DSP2_BASE + DSP2_BLBACK_WDR_CURVE_1_OFFSET), (uint32_t*)&wdr_curve->curve_coef[0], DSP2_WDR_CURVE_COEF_NUM / 2);
}

void DSP2_WDR_Get_WDR_Curve(DSP2_WDR_Curve_Type *wdr_curve)
{
    BL60X_MemCpy4((uint32_t*)&wdr_curve->curve_coef[0], (uint32_t*)(DSP2_BASE + DSP2_BLBACK_WDR_CURVE_1_OFFSET), DSP2_WDR_CURVE_COEF_NUM / 2);
}

void DSP2_WDR_Set_WDR_Curve_Weight(int weight)
{
    uint32_t tmpVal;

    CHECK_PARAM_MAX(weight, DSP2_WDR_CURVE_WEIGHT_MAX);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_CURVE_33);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_CURVE_WEIGHT_PRE, weight);
    BL_WR_REG(DSP2_BASE, DSP2_BLBACK_WDR_CURVE_33, tmpVal);
}

void DSP2_WDR_Get_WDR_Curve_Weight(int *weight)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_CURVE_33);
    *weight = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_CURVE_WEIGHT_PRE);
}

void DSP2_WDR_Get_Post_Enhance_State(BL_Fun_Type *state)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_ENH_1);

    if (BL_IS_REG_BIT_SET(tmpVal, DSP2_BLBACK_ENH_EN_PRE)) {
        *state = ENABLE;
    } else {
        *state = DISABLE;
    }
}

void DSP2_WDR_Set_Post_Enhance_State(BL_Fun_Type state)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_ENH_1);
    if (ENABLE == state) {
        tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_BLBACK_ENH_EN_PRE);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_BLBACK_ENH_EN_PRE);
    }
    BL_WR_REG(DSP2_BASE, DSP2_BLBACK_WDR_ENH_1, tmpVal);
}

void DSP2_WDR_Set_Post_Enhance_Weight(int weight)
{
    uint32_t tmpVal;

    CHECK_PARAM_MAX(weight, DSP2_WDR_POST_ENHANCE_WEIGHT_MAX);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_ENH_1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_ENH_WEIGHT_PRE, weight);
    BL_WR_REG(DSP2_BASE, DSP2_BLBACK_WDR_ENH_1, tmpVal);
}

void DSP2_WDR_Get_Post_Enhance_Weight(int *weight)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_ENH_1);
    *weight = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_ENH_WEIGHT_PRE);
}

void DSP2_WDR_Set_Post_Enhance_Y_Offset(int y_offset)
{
    uint32_t tmpVal;

    CHECK_PARAM_MAX(y_offset, DSP2_WDR_POST_ENHANCE_Y_OFFSET_MAX);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_ENH_1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_ENH_Y_OFFSET_PRE, y_offset);
    BL_WR_REG(DSP2_BASE, DSP2_BLBACK_WDR_ENH_1, tmpVal);
}

void DSP2_WDR_Get_Post_Enhance_Y_Offset(int *y_offset)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_ENH_1);
    *y_offset = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_ENH_Y_OFFSET_PRE);
}

void DSP2_WDR_Set_Post_Enhance_Luma_Gain(int gain)
{
    uint32_t tmpVal;

    CHECK_PARAM_MAX(gain, DSP2_WDR_POST_ENHANCE_Y_GAIN_MAX);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_ENH_2);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_ENH_Y_GAIN_PRE, gain);
    BL_WR_REG(DSP2_BASE, DSP2_BLBACK_WDR_ENH_2, tmpVal);
}

void DSP2_WDR_Get_Post_Enhance_Luma_Gain(int *gain)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_ENH_2);
    *gain = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_ENH_Y_GAIN_PRE);
}

void DSP2_WDR_Set_Post_Enhance_Chroma_Gain(int gain)
{
    uint32_t tmpVal;

    CHECK_PARAM_MAX(gain, DSP2_WDR_POST_ENHANCE_C_GAIN_MAX);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_ENH_2);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_ENH_C_GAIN_PRE, gain);
    BL_WR_REG(DSP2_BASE, DSP2_BLBACK_WDR_ENH_2, tmpVal);
}

void DSP2_WDR_Get_Post_Enhance_Chroma_Gain(int *gain)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_WDR_ENH_2);
    *gain = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_ENH_C_GAIN_PRE);
}

