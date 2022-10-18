#include <stdint.h>
#include <bl808_dsp2_misc.h>
#include <dsp2_misc_reg.h>

#define DSP2_MISC_YUV_ADJUST_DEFAULT_Y_CONTRAST_MUL1   (862)
#define DSP2_MISC_YUV_ADJUST_DEFAULT_Y_CONTRAST_MUL0   (896)
#define DSP2_MISC_YUV_ADJUST_DEFAULT_Y_BRIGHTNESS      (0)

#define DSP2_MISC_YUV_ADJUST_DEFAULT_UV_MAX            (240)
#define DSP2_MISC_YUV_ADJUST_DEFAULT_UV_MIN            (16)
#define DSP2_MISC_YUV_ADJUST_DEFAULT_Y_MAX             (235)
#define DSP2_MISC_YUV_ADJUST_DEFAULT_Y_MIN             (16)

#define DSP2_MISC_YUV_ADJUST_DEFAULT_UV_STURATION_MUL1 (903)
#define DSP2_MISC_YUV_ADJUST_DEFAULT_UV_STURATION_MUL0 (896)

#define DSP2_MISC_RESHAPE_TOGGLE_COUNT_MIN             (0)
#define DSP2_MISC_RESHAPE_TOGGLE_COUNT_MAX             (32)

typedef enum {
    DISPLAY_INTR_SRC_TEST_SRC = 0,
    DISPLAY_INTR_SRC_OUTPUT = 1,
    DISPLAY_INTR_SRC_INVALID,
} DSP2_Display_Intr_Src_Type;

static struct yuv2rgb_param_t g_bt601_yuv2rgb_cfg = {
    .pre_offset_0 = 0,
    .pre_offset_1 = -128,
    .pre_offset_2 = -128,
    .post_offset_0 = 0,
    .post_offset_1 = 0,
    .post_offset_2 = 0,
    .matrix_00 = 512,
    .matrix_01 = 0,
    .matrix_02 = 718,
    .matrix_10 = 512,
    .matrix_11 = -176,
    .matrix_12 = -366,
    .matrix_20 = 512,
    .matrix_21 = 907,
    .matrix_22 = 0
};

/****************************************************************************//**
 * @brief  DVP as 2x function init
 *
 * @param  dvp2xCfg: DVP as 2x configuration structure pointer
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MSIC_DVP_2x_Init(DVP_2x_Cfg_Type* dvp2xCfg)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_DVP_ACTIVE_LEVEL_TYPE(dvp2xCfg->hSyncLevel));
    CHECK_PARAM(IS_DVP_ACTIVE_LEVEL_TYPE(dvp2xCfg->vSyncLevel));
    CHECK_PARAM(IS_DVP_DATA_ORDER_TYPE(dvp2xCfg->dataOrder));

    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_CONFIG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DVPAS_HS_INV, dvp2xCfg->hSyncLevel);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DVPAS_VS_INV, dvp2xCfg->vSyncLevel);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DVPAS_DA_ORDER, dvp2xCfg->dataOrder);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DVPAS_FIFO_TH, dvp2xCfg->fifoThreshold & 0x7ff);
    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_CONFIG, tmpVal);

#ifndef BFLB_USE_HAL_DRIVER
    Interrupt_Handler_Register(SEOF_INT0_IRQn,SEOF0_IRQHandler);
    Interrupt_Handler_Register(SEOF_INT1_IRQn,SEOF1_IRQHandler);
    Interrupt_Handler_Register(SEOF_INT2_IRQn,SEOF2_IRQHandler);
#endif
}

void DSP2_MSIC_DVP_2x_Get_Cfg(DVP_2x_Cfg_Type* dvp2xCfg)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_CONFIG);
    dvp2xCfg->hSyncLevel = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DVPAS_HS_INV);
    dvp2xCfg->vSyncLevel = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DVPAS_VS_INV);
    dvp2xCfg->dataOrder = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DVPAS_DA_ORDER);
    dvp2xCfg->fifoThreshold = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DVPAS_FIFO_TH);
}

/****************************************************************************//**
 * @brief  DVP as 2x function enable
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MSIC_DVP_2x_Enable(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_CONFIG);
    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_CONFIG, BL_SET_REG_BIT(tmpVal, DSP2_MISC_RG_DVPAS_ENABLE));
}

/****************************************************************************//**
 * @brief  DVP as 2x function disable
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MSIC_DVP_2x_Disable(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_CONFIG);
    tmpVal = BL_CLR_REG_BIT(tmpVal,DSP2_MISC_RG_DVPAS_ENABLE);
    BL_WR_REG(DSP2_MISC_BASE,DSP2_MISC_CONFIG,tmpVal);
}

void DSP2_MSIC_DVP_2x_Get_State(BL_Fun_Type *state)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_CONFIG);
    if (BL_IS_REG_BIT_SET(tmpVal, DSP2_MISC_RG_DVPAS_ENABLE)) {
        *state = ENABLE;
    } else {
        *state = DISABLE;
    }
}

void DSP2_MSIC_Pclk_Force_Set_State(BL_Fun_Type state)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_CONFIG);

    if (ENABLE == state) {
        tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_REG_DSP2_PCLK_FORCE_ON);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_MISC_REG_DSP2_PCLK_FORCE_ON);
    }

    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_CONFIG, tmpVal);
}

void DSP2_MSIC_Pclk_Force_Get_State(BL_Fun_Type *state)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_CONFIG);
    if (BL_IS_REG_BIT_SET(tmpVal, DSP2_MISC_REG_DSP2_PCLK_FORCE_ON)) {
        *state = ENABLE;
    } else {
        *state = DISABLE;
    }
}


/****************************************************************************/ /**
 * @brief  Select DVP TSRC data source
 *
 * @param  sourceType: DVP or CSI
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MISC_TSRC_Source_Select(DSP2_MISC_TSRC_Source_Type sourceType)
{
    uint32_t tmpVal;
    
    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_PIX_DATA_CTRL);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_DSP2_DTSRC_SRC, sourceType);
    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_PIX_DATA_CTRL, tmpVal);
}



void DSP2_MSIC_Cr_De_As_Hsync_Set_State(BL_Fun_Type state)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_CONFIG);

    if (ENABLE == state) {
        tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_CR_DSP2_DE_AS_HSYNC);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_MISC_CR_DSP2_DE_AS_HSYNC);
    }

    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_CONFIG, tmpVal);
}

void DSP2_MSIC_Cr_De_As_Hsync_Get_State(BL_Fun_Type *state)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_CONFIG);
    if (BL_IS_REG_BIT_SET(tmpVal, DSP2_MISC_CR_DSP2_DE_AS_HSYNC)) {
        *state = ENABLE;
    } else {
        *state = DISABLE;
    }
}

void DSP2_MSIC_Dtsrc_Set_Mode(DSP2_DTSRC_SRC_E mode)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_PIX_DATA_CTRL);

    if (DVP_TSRC_SRC_MIPI_CSI == mode) {
        tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_REG_DSP2_DTSRC_SRC);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_MISC_REG_DSP2_DTSRC_SRC);
    }

    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_PIX_DATA_CTRL, tmpVal);
}

void DSP2_MSIC_Dtsrc_Get_Mode(DSP2_DTSRC_SRC_E *mode)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_PIX_DATA_CTRL);
    if (BL_IS_REG_BIT_SET(tmpVal, DSP2_MISC_REG_DSP2_DTSRC_SRC)) {
        *mode = DVP_TSRC_SRC_MIPI_CSI;
    } else {
        *mode = DVP_TSRC_SRC_DVP;
    }
}

void DSP2_Misc_Config(DSP2_DVP_BIT_DEPTH_E dvp_bits)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_CONFIG);
    tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_MISC_CR_DSP2_DE_AS_HSYNC);
#if (BL80X_HW_VER <= BL80X_HW_B0)
    //tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_NEW_AE_SEL, NEW_AE_STATS);
    //tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_NEW_AWB_SEL, NEW_AWB_STATS);
    /* select output of codec_scaler */
    tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_DVP_MUX_CH4_SEL);
#endif
    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_CONFIG, tmpVal);

    /*
    Controls two MUXes:
        1. Selection signal of hdmi_dvp_tsrc sensor mode input
            0: From DSP2 scaler output
            1: From sensor
        2. Selection signal of HDMI data format
            0: {2'b0, dvp_test_src_data[15:0]} (for YUV422 data format)
            1: {2'b0, 8'd128, dvp_test_src_data[7:0]} (for Y-only data format)
    */


    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_PIX_DATA_CTRL);
    if (dvp_bits == DSP2_DVP_10_BIT) {
#if (BL80X_HW_VER <= BL80X_HW_A0)
        /* 10 bit DVP sensor, wired to bit[2:11] of DVP interface */
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_PIX_DATA_CTRL, 0xFFC);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_PIX_DATA_SHT_BIT, 0x0);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_PIX_DATA_SHT_DIR, 0x0);
#else
        /* 10 bit DVP sensor, wired to bit[0:9] of DVP interface */
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_PIX_DATA_CTRL, 0x3FF);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_PIX_DATA_SHT_BIT, 0x2);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_PIX_DATA_SHT_DIR, 0x0);
#endif
    } else {
        /* 12 bit DVP sensor, wired to bit[0:11] of DVP interface or
           10 bit DVP sensor, wired to bit[2:11] of DVP interface */
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_PIX_DATA_CTRL, 0xFFF);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_PIX_DATA_SHT_BIT, 0x0);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_PIX_DATA_SHT_DIR, 0x0);
    }
    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_PIX_DATA_CTRL, tmpVal);
}

void DSP2_DVP2AXI_Set_Src(DVP2AXI_Port_Type dvp2axi, DVP2AXI_Src_Type src)
{
    uint32_t tmpVal;

    if (DVP2AXI_A == dvp2axi || DVP2AXI_B == dvp2axi \
        || DVP2AXI_C == dvp2axi || DVP2AXI_D == dvp2axi) {
        tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_DVP2BUS_SRC_SEL_1);

        switch (dvp2axi)
        {
        case DVP2AXI_A:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_D2B_DVP_SEL_A, src);
            break;
        case DVP2AXI_B:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_D2B_DVP_SEL_B, src);
            break;
        case DVP2AXI_C:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_D2B_DVP_SEL_C, src);
            break;
        case DVP2AXI_D:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_D2B_DVP_SEL_D, src);
            break;
        default:
            BL_ABORT();
        }
        BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_DVP2BUS_SRC_SEL_1, tmpVal);
    }
    else if (DVP2AXI_E == dvp2axi || DVP2AXI_F == dvp2axi \
        || DVP2AXI_G == dvp2axi || DVP2AXI_H == dvp2axi){
        tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_DVP2BUS_SRC_SEL_2);

        switch (dvp2axi)
        {
        case DVP2AXI_E:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_D2B_DVP_SEL_E, src);
            break;
        case DVP2AXI_F:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_D2B_DVP_SEL_F, src);
            break;
        case DVP2AXI_G:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_D2B_DVP_SEL_G, src);
            break;
        case DVP2AXI_H:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_D2B_DVP_SEL_H, src);
            break;
        default:
            BL_ABORT();
        }
        BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_DVP2BUS_SRC_SEL_2, tmpVal);
    }
    else {
        BL_ABORT();
    }
}

void DSP2_DVP2AXI_Get_Src(DVP2AXI_Port_Type dvp2axi, DVP2AXI_Src_Type *src)
{
    uint32_t tmpVal;

    if (DVP2AXI_A == dvp2axi || DVP2AXI_B == dvp2axi \
        || DVP2AXI_C == dvp2axi || DVP2AXI_D == dvp2axi) {

        tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_DVP2BUS_SRC_SEL_1);
        switch (dvp2axi)
        {
            case DVP2AXI_A:
                *src = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_D2B_DVP_SEL_A);
                break;
            case DVP2AXI_B:
                *src = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_D2B_DVP_SEL_B);
                break;
            case DVP2AXI_C:
                *src = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_D2B_DVP_SEL_C);
                break;
            case DVP2AXI_D:
                *src = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_D2B_DVP_SEL_D);
                break;
            default:
                BL_ABORT();
        }
    }
    else if (DVP2AXI_E == dvp2axi || DVP2AXI_F == dvp2axi \
        || DVP2AXI_G == dvp2axi || DVP2AXI_H == dvp2axi) {

        tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_DVP2BUS_SRC_SEL_2);
        switch (dvp2axi)
        {
            case DVP2AXI_E:
                *src = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_D2B_DVP_SEL_E);
                break;
            case DVP2AXI_F:
                *src = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_D2B_DVP_SEL_F);
                break;
            case DVP2AXI_G:
                *src = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_D2B_DVP_SEL_G);
                break;
            case DVP2AXI_H:
                *src = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_D2B_DVP_SEL_H);
                break;
            default:
                BL_ABORT();
        }
    }
    else {
        BL_ABORT();
    }
}

void DSP2_DVP2AXI_Set_Id_Sel(DVP2AXI_Port_Type dvp2axi, DVP2AXI_ID_E id)
{
    uint32_t tmpVal;

    if (DVP2AXI_A == dvp2axi || DVP2AXI_B == dvp2axi \
        || DVP2AXI_C == dvp2axi || DVP2AXI_D == dvp2axi) {
        tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_DVP2BUS_SRC_SEL_1);

        switch (dvp2axi)
        {
        case DVP2AXI_A:
            if (id == DVP2AXI_ID_BAYER) tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_MISC_RG_D2X_ID_SEL_A);
            else tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_RG_D2X_ID_SEL_A);
            break;
        case DVP2AXI_B:
            if (id == DVP2AXI_ID_BAYER) tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_MISC_RG_D2X_ID_SEL_B);
            else tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_RG_D2X_ID_SEL_B);
            break;
        case DVP2AXI_C:
            if (id == DVP2AXI_ID_BAYER) tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_MISC_RG_D2X_ID_SEL_C);
            else tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_RG_D2X_ID_SEL_C);
            break;
        case DVP2AXI_D:
            if (id == DVP2AXI_ID_BAYER) tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_MISC_RG_D2X_ID_SEL_D);
            else tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_RG_D2X_ID_SEL_D);
            break;
        default:
            BL_ABORT();
        }
        BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_DVP2BUS_SRC_SEL_1, tmpVal);
    }
    else if (DVP2AXI_E == dvp2axi || DVP2AXI_F == dvp2axi \
        || DVP2AXI_G == dvp2axi || DVP2AXI_H == dvp2axi){
        tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_DVP2BUS_SRC_SEL_2);

        switch (dvp2axi)
        {
        case DVP2AXI_E:
            if (id == DVP2AXI_ID_BAYER) tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_MISC_RG_D2X_ID_SEL_E);
            else tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_RG_D2X_ID_SEL_E);
            break;
        case DVP2AXI_F:
            if (id == DVP2AXI_ID_BAYER) tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_MISC_RG_D2X_ID_SEL_F);
            else tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_RG_D2X_ID_SEL_F);
            break;
        case DVP2AXI_G:
            if (id == DVP2AXI_ID_BAYER) tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_MISC_RG_D2X_ID_SEL_G);
            else tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_RG_D2X_ID_SEL_G);
            break;
        case DVP2AXI_H:
            if (id == DVP2AXI_ID_BAYER) tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_MISC_RG_D2X_ID_SEL_H);
            else tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_RG_D2X_ID_SEL_H);
            break;
        default:
            BL_ABORT();
        }
        BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_DVP2BUS_SRC_SEL_2, tmpVal);
    }
    else {
        BL_ABORT();
    }
}

void DSP2_DVP2AXI_Get_Id_Sel(DVP2AXI_Port_Type dvp2axi, DVP2AXI_ID_E *id)
{
    uint32_t tmpVal;

    if (DVP2AXI_A == dvp2axi || DVP2AXI_B == dvp2axi \
        || DVP2AXI_C == dvp2axi || DVP2AXI_D == dvp2axi) {

        tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_DVP2BUS_SRC_SEL_1);
        switch (dvp2axi)
        {
            case DVP2AXI_A:
                if (BL_IS_REG_BIT_SET(tmpVal, DSP2_MISC_RG_D2X_ID_SEL_A)) {
                    *id = DVP2AXI_ID_YUV;
                } else {
                    *id = DVP2AXI_ID_BAYER;
                }
                break;
            case DVP2AXI_B:
                if (BL_IS_REG_BIT_SET(tmpVal, DSP2_MISC_RG_D2X_ID_SEL_B)) {
                    *id = DVP2AXI_ID_YUV;
                } else {
                    *id = DVP2AXI_ID_BAYER;
                }
                break;
            case DVP2AXI_C:
                if (BL_IS_REG_BIT_SET(tmpVal, DSP2_MISC_RG_D2X_ID_SEL_C)) {
                    *id = DVP2AXI_ID_YUV;
                } else {
                    *id = DVP2AXI_ID_BAYER;
                }
                break;
            case DVP2AXI_D:
                if (BL_IS_REG_BIT_SET(tmpVal, DSP2_MISC_RG_D2X_ID_SEL_D)) {
                    *id = DVP2AXI_ID_YUV;
                } else {
                    *id = DVP2AXI_ID_BAYER;
                }
                break;
            default:
                BL_ABORT();
        }
    }
    else if (DVP2AXI_E == dvp2axi || DVP2AXI_F == dvp2axi \
        || DVP2AXI_G == dvp2axi || DVP2AXI_H == dvp2axi) {

        tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_DVP2BUS_SRC_SEL_2);
        switch (dvp2axi)
        {
            case DVP2AXI_E:
                if (BL_IS_REG_BIT_SET(tmpVal, DSP2_MISC_RG_D2X_ID_SEL_E)) {
                    *id = DVP2AXI_ID_YUV;
                } else {
                    *id = DVP2AXI_ID_BAYER;
                }
                break;
            case DVP2AXI_F:
                if (BL_IS_REG_BIT_SET(tmpVal, DSP2_MISC_RG_D2X_ID_SEL_F)) {
                    *id = DVP2AXI_ID_YUV;
                } else {
                    *id = DVP2AXI_ID_BAYER;
                }
                break;
            case DVP2AXI_G:
                if (BL_IS_REG_BIT_SET(tmpVal, DSP2_MISC_RG_D2X_ID_SEL_G)) {
                    *id = DVP2AXI_ID_YUV;
                } else {
                    *id = DVP2AXI_ID_BAYER;
                }
                break;
            case DVP2AXI_H:
                if (BL_IS_REG_BIT_SET(tmpVal, DSP2_MISC_RG_D2X_ID_SEL_H)) {
                    *id = DVP2AXI_ID_YUV;
                } else {
                    *id = DVP2AXI_ID_BAYER;
                }
                break;
            default:
                BL_ABORT();
        }
    }
    else {
        BL_ABORT();
    }
}

void DSP2_Intr_Clr(DSP2_INTR_SEL_E intr_sel)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_INT_CLR);

    switch (intr_sel)
    {
        case DSP2_AE_INTR:
        tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_RG_AE_INT_CLR);
        break;

        case DSP2_AE_HIST_INTR:
        tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_RG_AE_HIST_INT_CLR);
        break;

        case DSP2_AWB_INTR:
        tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_RG_AWB_INT_CLR);
        break;

        case DSP2_AWB2_INTR:
        tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_RG_AWB2_INT_CLR);
        break;

        case DSP2_AWB3_INTR:
        tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_RG_AWB3_INT_CLR);
        break;

        case DSP2_WDR_INTR:
        tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_RG_WDR_INT_CLR);
        break;

        case DSP2_OSD_PB_INTR:
        tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_RG_OSD_PB_INT_CLR);
        break;

        case DSP2_SEOF1_INTR:
        tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_RG_SEOF1_INT_CLR);
        break;

        case DSP2_SEOF2_INTR:
        tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_RG_SEOF2_INT_CLR);
        break;

        case DSP2_SEOF3_INTR:
        tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_RG_SEOF3_INT_CLR);
        break;

        case DSP2_SEOF4_INTR:
        tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_RG_SEOF4_INT_CLR);
        break;

        case DSP2_DP_SEOF0_INTR:
        tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_RG_DP_SEOF0_INT_CLR);
        break;
    }

    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_INT_CLR, tmpVal);
}

void DSP2_Intr_Ctrl_Init(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_INT_CTRL);
    tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_MISC_RG_AE_INT_MASK);
    tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_MISC_RG_AE_HIST_INT_MASK);
    tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_MISC_RG_AWB_INT_MASK);
    tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_MISC_RG_AWB2_INT_MASK);
    tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_MISC_RG_AWB3_INT_MASK);
    tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_MISC_RG_WDR_INT_MASK);
    tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_MISC_RG_OSD_PB_INT_MASK);

    /* Sensor VSYNC pos edge */
    tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_MISC_RG_SEOF1_INT_MASK);
    tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_RG_SEOF1_INT_EDGE);    /* pos edge */
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_SEOF1_INT_SRC, SEOF_INTR_SRC_SENSOR_VSYNC);

    /* Act VSYNC pos edge */
    tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_MISC_RG_SEOF2_INT_MASK);
    tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_RG_SEOF2_INT_EDGE);    /* pos edge */
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_SEOF2_INT_SRC, SEOF_INTR_SRC_DSP2_ACT_VSYNC);

    /* Sensor VSYNC neg edge */
    tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_MISC_RG_SEOF3_INT_MASK);
    tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_MISC_RG_SEOF3_INT_EDGE);    /* neg edge */
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_SEOF3_INT_SRC, SEOF_INTR_SRC_SENSOR_VSYNC);

    /* Act VSYNC pos edge */
    tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_MISC_RG_SEOF4_INT_MASK);
    tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_MISC_RG_SEOF4_INT_EDGE);    /* neg edge */
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_SEOF4_INT_SRC, SEOF_INTR_SRC_DSP2_ACT_VSYNC);

    /* Display edge selection */
    tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_MISC_RG_DP_SEOF0_INT_MASK);
    tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_MISC_RG_DP_SEOF0_INT_EDGE);    /* neg edge */
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DP_SEOF0_INT_SRC, DISPLAY_INTR_SRC_TEST_SRC);

    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_INT_CTRL, tmpVal);

    DSP2_Intr_Clr(DSP2_AE_INTR);
    DSP2_Intr_Clr(DSP2_AE_HIST_INTR);
    DSP2_Intr_Clr(DSP2_AWB_INTR);
    DSP2_Intr_Clr(DSP2_AWB2_INTR);
    DSP2_Intr_Clr(DSP2_AWB3_INTR);
    DSP2_Intr_Clr(DSP2_WDR_INTR);
    DSP2_Intr_Clr(DSP2_OSD_PB_INTR);
    DSP2_Intr_Clr(DSP2_SEOF1_INTR);
    DSP2_Intr_Clr(DSP2_SEOF2_INTR);
    DSP2_Intr_Clr(DSP2_SEOF3_INTR);
    DSP2_Intr_Clr(DSP2_SEOF4_INTR);
    DSP2_Intr_Clr(DSP2_DP_SEOF0_INTR);
}

void DSP2_Intr_Ctrl_Set_Src(DSP2_SEOF_E seof,DSP2_Seof_Intr_Src_Type selection)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_INT_CTRL);
    if (seof == DSP2_SEOF1) tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_SEOF1_INT_SRC, selection);
    else if (seof == DSP2_SEOF2) tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_SEOF2_INT_SRC, selection);
    else if (seof == DSP2_SEOF3) tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_SEOF3_INT_SRC, selection);
    else if (seof == DSP2_SEOF4) tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_SEOF4_INT_SRC, selection);
    else if (seof == DSP2_SEOF0) tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DP_SEOF0_INT_SRC, selection);
    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_INT_CTRL, tmpVal);

}

void DSP2_Intr_Ctrl_Get_Src(DSP2_SEOF_E seof,DSP2_Seof_Intr_Src_Type *selection)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_INT_CTRL);
    if (seof == DSP2_SEOF1) *selection = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_SEOF1_INT_SRC);
    else if (seof == DSP2_SEOF2) *selection = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_SEOF2_INT_SRC);
    else if (seof == DSP2_SEOF3) *selection = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_SEOF3_INT_SRC);
    else if (seof == DSP2_SEOF4) *selection = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_SEOF4_INT_SRC);
    else if (seof == DSP2_SEOF0) *selection = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DP_SEOF0_INT_SRC);

}

#define YUV_SCALER_SET_STATE_MACRO(name) \
    {tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_SCALER##name##_I_SIZE);\
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_SCALER##name##_BYPASS, !state);\
    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_SCALER##name##_I_SIZE, tmpVal);}

void DSP2_Scaler_Set_State(DSP2_Scaler_Type type, BL_Fun_Type state)
{
    uint32_t tmpVal;

    if (DSP2_SCALER_A == type) {
        YUV_SCALER_SET_STATE_MACRO(A)
    } else if (DSP2_SCALER_B == type) {
        YUV_SCALER_SET_STATE_MACRO(B)
    } else if (DSP2_SCALER_C == type) {
        YUV_SCALER_SET_STATE_MACRO(C)
    } else if (DSP2_SCALER_D == type) {
        YUV_SCALER_SET_STATE_MACRO(D)
    }
    else {
        printf("YUV Scaler not support!\r\n");
    }
}

#define YUV_SCALER_SET_CONFIG_MACRO(name) \
    {tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_SCALER##name##_I_SIZE);\
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_SCALER##name##_I_W, scaler_conf->input.width);\
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_SCALER##name##_I_H, scaler_conf->input.height);\
    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_SCALER##name##_I_SIZE, tmpVal);\
    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_SCALER##name##_O_SIZE);\
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_SCALER##name##_O_W, scaler_conf->output.width);\
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_SCALER##name##_O_H, scaler_conf->output.height);\
    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_SCALER##name##_O_SIZE, tmpVal);}

// TODO add interface to set scaler input, default is dsp2 out
void DSP2_Scaler_Set_Cfg(DSP2_Scaler_Type type, DSP2_SCALER_CONFIG_S *scaler_conf)
{
    uint32_t tmpVal;
    if (DSP2_SCALER_A == type) {
        YUV_SCALER_SET_CONFIG_MACRO(A)
    } else if (DSP2_SCALER_B == type) {
        YUV_SCALER_SET_CONFIG_MACRO(B)
    } else if (DSP2_SCALER_C == type) {
        YUV_SCALER_SET_CONFIG_MACRO(C)
    } else if (DSP2_SCALER_D == type) {
        YUV_SCALER_SET_CONFIG_MACRO(D)
    }
    else {
        printf("YUV Scaler not support!\r\n");
    }
}

void DSP2_Frame_M_to_N(DSP2_FRAME_M_TO_N_S *cfg)
{
    uint32_t frm_m_to_n;

    frm_m_to_n = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_DVP_FRAME_M_TO_N);
    frm_m_to_n = BL_SET_REG_BITS_VAL(frm_m_to_n, DSP2_MISC_CR_FRAME_M_TO_N_EN, cfg->enb);
    frm_m_to_n = BL_SET_REG_BITS_VAL(frm_m_to_n, DSP2_MISC_CR_FRAME_CNT_M, cfg->m);
    frm_m_to_n = BL_SET_REG_BITS_VAL(frm_m_to_n, DSP2_MISC_CR_FRAME_CNT_N, cfg->n);
    frm_m_to_n = BL_SET_REG_BITS_VAL(frm_m_to_n, DSP2_MISC_CR_FRAME_INTERVAL, cfg->intv);
    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_DVP_FRAME_M_TO_N, frm_m_to_n);
}

void DSP2_Frame_Get_M_to_N(DSP2_FRAME_M_TO_N_S *cfg)
{
    uint32_t frm_m_to_n;

    frm_m_to_n = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_DVP_FRAME_M_TO_N);
    cfg->enb  = BL_GET_REG_BITS_VAL(frm_m_to_n, DSP2_MISC_CR_FRAME_M_TO_N_EN);
    cfg->m    = BL_GET_REG_BITS_VAL(frm_m_to_n, DSP2_MISC_CR_FRAME_CNT_M);
    cfg->n    = BL_GET_REG_BITS_VAL(frm_m_to_n, DSP2_MISC_CR_FRAME_CNT_N);
    cfg->intv = BL_GET_REG_BITS_VAL(frm_m_to_n, DSP2_MISC_CR_FRAME_INTERVAL);
}

void DSP2_Enable_BL_DSP2_Back(void)
{
    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_DUMMY, 1);
}

#define YUV_ADJUST_INIT_MACRO(name) \
    {tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_ADJ##name##_CTRL_0);\
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_ADJ##name##_Y_MUL0,  DSP2_MISC_YUV_ADJUST_DEFAULT_Y_CONTRAST_MUL0);\
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_ADJ##name##_Y_MUL1,  DSP2_MISC_YUV_ADJUST_DEFAULT_Y_CONTRAST_MUL1);\
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_ADJ##name##_Y_LUMA,  DSP2_MISC_YUV_ADJUST_DEFAULT_Y_BRIGHTNESS);\
    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_ADJ##name##_CTRL_0, tmpVal);\
    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_ADJ##name##_CTRL_1);\
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_ADJ##name##_UV_MAX,  DSP2_MISC_YUV_ADJUST_DEFAULT_UV_MAX);\
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_ADJ##name##_UV_MIN,  DSP2_MISC_YUV_ADJUST_DEFAULT_UV_MIN);\
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_ADJ##name##_Y_MAX,   DSP2_MISC_YUV_ADJUST_DEFAULT_Y_MAX);\
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_ADJ##name##_Y_MIN,   DSP2_MISC_YUV_ADJUST_DEFAULT_Y_MIN);\
    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_ADJ##name##_CTRL_1, tmpVal);\
    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_ADJ##name##_CTRL_2);\
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_ADJ##name##_UV_MUL0,  DSP2_MISC_YUV_ADJUST_DEFAULT_UV_STURATION_MUL0);\
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_ADJ##name##_UV_MUL1,  DSP2_MISC_YUV_ADJUST_DEFAULT_UV_STURATION_MUL1);\
    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_ADJ##name##_CTRL_2, tmpVal);}

void DSP2_YUV_Adjust_Init()
{
    uint32_t tmpVal;

    YUV_ADJUST_INIT_MACRO(A)
    YUV_ADJUST_INIT_MACRO(B)
    YUV_ADJUST_INIT_MACRO(C)
    YUV_ADJUST_INIT_MACRO(D)

    DSP2_YUV_Adjust_Set_State(DSP2_YUV_ADJUST_A, DISABLE);
    DSP2_YUV_Adjust_Set_State(DSP2_YUV_ADJUST_B, DISABLE);
    DSP2_YUV_Adjust_Set_State(DSP2_YUV_ADJUST_C, DISABLE);
    DSP2_YUV_Adjust_Set_State(DSP2_YUV_ADJUST_D, DISABLE);
}

#define YUV_ADJUST_SET_CFG_MACRO(name) \
    {tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_ADJ##name##_CTRL_0);\
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_ADJ##name##_Y_MUL0,  cfg->y_mul0);\
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_ADJ##name##_Y_MUL1,  cfg->y_mul1);\
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_ADJ##name##_Y_LUMA,  cfg->y_luma);\
    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_ADJ##name##_CTRL_0, tmpVal);\
    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_ADJ##name##_CTRL_1);\
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_ADJ##name##_UV_MAX,  cfg->uv_max);\
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_ADJ##name##_UV_MIN,  cfg->uv_min);\
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_ADJ##name##_Y_MAX,   cfg->y_max);\
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_ADJ##name##_Y_MIN,   cfg->y_min);\
    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_ADJ##name##_CTRL_1, tmpVal);\
    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_ADJ##name##_CTRL_2);\
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_ADJ##name##_UV_MUL0,  cfg->uv_mul0);\
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_ADJ##name##_UV_MUL1,  cfg->uv_mul1);\
    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_ADJ##name##_CTRL_2, tmpVal);}

void DSP2_YUV_Adjust_Set_Cfg(DSP2_YUV_Adjust_Type type, DSP2_YUV_Adjust_Cfg_Type *cfg)
{
    uint32_t tmpVal;

    if (DSP2_YUV_ADJUST_A == type) {
        YUV_ADJUST_SET_CFG_MACRO(A)
    } else if (DSP2_YUV_ADJUST_B == type) {
        YUV_ADJUST_SET_CFG_MACRO(B)
    } else if (DSP2_YUV_ADJUST_C == type) {
        YUV_ADJUST_SET_CFG_MACRO(C)
    } else if (DSP2_YUV_ADJUST_D == type) {
        YUV_ADJUST_SET_CFG_MACRO(D)
    }
    else {
        printf("YUV Adjust not support!\r\n");
    }

}

#define YUV_ADJUST_GET_CFG_MACRO(name) \
    {tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_ADJ##name##_CTRL_0);\
    cfg->y_mul0 = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_ADJ##name##_Y_MUL0);\
    cfg->y_mul1 = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_ADJ##name##_Y_MUL1);\
    cfg->y_luma = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_ADJ##name##_Y_LUMA);\
    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_ADJ##name##_CTRL_1);\
    cfg->uv_max = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_ADJ##name##_UV_MAX);\
    cfg->uv_min = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_ADJ##name##_UV_MIN);\
    cfg->y_max = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_ADJ##name##_Y_MAX);\
    cfg->y_min = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_ADJ##name##_Y_MIN);\
    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_ADJ##name##_CTRL_2);\
    cfg->uv_mul0 = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_ADJ##name##_UV_MUL0);\
    cfg->uv_mul1 = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_ADJ##name##_UV_MUL1);}

void DSP2_YUV_Adjust_Get_Cfg(DSP2_YUV_Adjust_Type type, DSP2_YUV_Adjust_Cfg_Type *cfg)
{
    uint32_t tmpVal;

    if (DSP2_YUV_ADJUST_A == type) {
        YUV_ADJUST_GET_CFG_MACRO(A)
    } else if (DSP2_YUV_ADJUST_B == type) {
        YUV_ADJUST_GET_CFG_MACRO(B)
    } else if (DSP2_YUV_ADJUST_C == type) {
        YUV_ADJUST_GET_CFG_MACRO(C)
    } else if (DSP2_YUV_ADJUST_D == type) {
        YUV_ADJUST_GET_CFG_MACRO(D)
    }
    else {
        printf("YUV Adjust not support!\r\n");
    }

}

#define YUV_ADJUST_SET_STATE_MACRO(name) \
    {tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_ADJ##name##_CTRL_0);\
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_ADJ##name##_ADJ_EB, state);\
    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_ADJ##name##_CTRL_0, tmpVal);}

void DSP2_YUV_Adjust_Set_State(DSP2_YUV_Adjust_Type type, BL_Fun_Type state)
{
    uint32_t tmpVal;
    if (DSP2_YUV_ADJUST_A == type) {
        YUV_ADJUST_SET_STATE_MACRO(A)
    } else if (DSP2_YUV_ADJUST_B == type) {
        YUV_ADJUST_SET_STATE_MACRO(B)
    } else if (DSP2_YUV_ADJUST_C == type) {
        YUV_ADJUST_SET_STATE_MACRO(C)
    } else if (DSP2_YUV_ADJUST_D == type) {
        YUV_ADJUST_SET_STATE_MACRO(D)
    }
    else {
        printf("YUV Adjust not support!\r\n");
    }
}

#define YUV_ADJUST_GET_STATE_MACRO(name) \
    {tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_ADJ##name##_CTRL_0);\
    *state = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_ADJ##name##_ADJ_EB);}

void DSP2_YUV_Adjust_Get_State(DSP2_YUV_Adjust_Type type, BL_Fun_Type *state)
{
    uint32_t tmpVal;
    if (DSP2_YUV_ADJUST_A == type) {
        YUV_ADJUST_GET_STATE_MACRO(A)
    } else if (DSP2_YUV_ADJUST_B == type) {
        YUV_ADJUST_GET_STATE_MACRO(B)
    } else if (DSP2_YUV_ADJUST_C == type) {
        YUV_ADJUST_GET_STATE_MACRO(C)
    } else if (DSP2_YUV_ADJUST_D == type) {
        YUV_ADJUST_GET_STATE_MACRO(D)
    }
    else {
        printf("YUV Adjust not support!\r\n");
    }
}

#define YUV_ADJUST_SET_INPUT_MACRO(name) \
    {tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_ADJ##name##_CTRL_2);\
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_ADJ##name##_SEL, input);\
    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_ADJ##name##_CTRL_2, tmpVal);}

void DSP2_YUV_Adjust_Set_Input(DSP2_YUV_Adjust_Type type, DSP2_YUV_Adjust_Input input)
{
    uint32_t tmpVal;
    if (DSP2_YUV_ADJUST_A == type) {
        YUV_ADJUST_SET_INPUT_MACRO(A)
    } else if (DSP2_YUV_ADJUST_B == type) {
        YUV_ADJUST_SET_INPUT_MACRO(B)
    } else if (DSP2_YUV_ADJUST_C == type) {
        YUV_ADJUST_SET_INPUT_MACRO(C)
    } else if (DSP2_YUV_ADJUST_D == type) {
        YUV_ADJUST_SET_INPUT_MACRO(D)
    }
    else {
        printf("YUV Adjust not support!\r\n");
    }
}

#define YUV_ADJUST_GET_INPUT_MACRO(name) \
    {tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_ADJ##name##_CTRL_2);\
    *input = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_ADJ##name##_SEL);}

void DSP2_YUV_Adjust_Get_Input(DSP2_YUV_Adjust_Type type, DSP2_YUV_Adjust_Input *input)
{
    uint32_t tmpVal;
    if (DSP2_YUV_ADJUST_A == type) {
        YUV_ADJUST_GET_INPUT_MACRO(A)
    } else if (DSP2_YUV_ADJUST_B == type) {
        YUV_ADJUST_GET_INPUT_MACRO(B)
    } else if (DSP2_YUV_ADJUST_C == type) {
        YUV_ADJUST_GET_INPUT_MACRO(C)
    } else if (DSP2_YUV_ADJUST_D == type) {
        YUV_ADJUST_GET_INPUT_MACRO(D)
    }
    else {
        printf("YUV Adjust not support!\r\n");
    }
}

#define SCALER_SET_INPUT_MACRO(name) \
    {tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_SCALER##name##_I_SIZE);\
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_SCALER##name##_SEL, input);\
    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_SCALER##name##_I_SIZE, tmpVal);}

void DSP2_Scaler_Set_Input(DSP2_Scaler_Type type, DSP2_Scaler_Input input)
{
    uint32_t tmpVal;
    if (DSP2_SCALER_A == type) {
        SCALER_SET_INPUT_MACRO(A)
    } else if (DSP2_SCALER_B == type) {
        SCALER_SET_INPUT_MACRO(B)
    } else if (DSP2_SCALER_C == type) {
        SCALER_SET_INPUT_MACRO(C)
    } else if (DSP2_SCALER_D == type) {
        SCALER_SET_INPUT_MACRO(D)
    } else {
        BL_LOGE("Scaler type %d not support!\r\n", type);
    }
}

#define SCALER_GET_INPUT_MACRO(name) \
    {tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_SCALER##name##_I_SIZE);\
    *input = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_SCALER##name##_SEL);}
            
void DSP2_Scaler_Get_Input(DSP2_Scaler_Type type, DSP2_Scaler_Input *input)
{
    uint32_t tmpVal;
    if (DSP2_SCALER_A == type) {
        SCALER_GET_INPUT_MACRO(A)
    } else if (DSP2_SCALER_B == type) {
        SCALER_GET_INPUT_MACRO(B)
    } else if (DSP2_SCALER_C == type) {
        SCALER_GET_INPUT_MACRO(C)
    } else if (DSP2_SCALER_D == type) {
        SCALER_GET_INPUT_MACRO(D)
    } else {
        BL_LOGE("Scaler type %d not support!\r\n", type);
    }
}

#define OSD_SET_INPUT_MACRO(name) \
    {tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_OSD##name##_I_CTRL);\
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_OSD##name##_SEL, input);\
    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_OSD##name##_I_CTRL, tmpVal);}

void DSP2_OSD_Set_Input(DSP2_OSD_Type type, DSP2_OSD_Input input)
{
    uint32_t tmpVal;
    if ((DSP2_OSD_A == type || DSP2_OSD_C == type) && (input == DSP2_OSD_INPUT_OSD_A || input == DSP2_OSD_INPUT_OSD_C)) {
        printf("Input from OsdA and OsdC are only supported by OsdB and OsdD\r\n");
        return;
    }
    if (DSP2_OSD_A == type) {
        OSD_SET_INPUT_MACRO(A)
    } else if (DSP2_OSD_B == type) {
        OSD_SET_INPUT_MACRO(B)
    } else if (DSP2_OSD_C == type) {
        OSD_SET_INPUT_MACRO(C)
    } else if (DSP2_OSD_D == type) {
        OSD_SET_INPUT_MACRO(D)
    } else {
        BL_LOGE("OSD type %d not support!\r\n", type);
    }
}

#define OSD_GET_INPUT_MACRO(name) \
    {tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_OSD##name##_I_CTRL);\
    *input = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_OSD##name##_SEL);}

void DSP2_OSD_Get_Input(DSP2_OSD_Type type, DSP2_OSD_Input *input)
{
    uint32_t tmpVal;
    if ((DSP2_OSD_A == type || DSP2_OSD_C == type) && (input == DSP2_OSD_INPUT_OSD_A || input == DSP2_OSD_INPUT_OSD_C)) {
        printf("Input from OsdA and OsdC are only supported by OsdB and OsdD\r\n");
        return;
    }
    if (DSP2_OSD_A == type) {
        OSD_GET_INPUT_MACRO(A)
    } else if (DSP2_OSD_B == type) {
        OSD_GET_INPUT_MACRO(B)
    } else if (DSP2_OSD_C == type) {
        OSD_GET_INPUT_MACRO(C)
    } else if (DSP2_OSD_D == type) {
        OSD_GET_INPUT_MACRO(D)
    } else {
        BL_LOGE("OSD type %d not support!\r\n", type);
    }
}

#define YUV2RGB_SET_INPUT_MACRO(name) \
    {tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_Y2R##name##_CONFIG_0);\
     tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_Y2R##name##_SEL, (input == DSP2_YUV2RGB_INPUT_DISABLED) ? 0 : input);\
     tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_Y2R##name##_EN,  (input == DSP2_YUV2RGB_INPUT_DISABLED) ? 0 : 1);\
     BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_Y2R##name##_CONFIG_0, tmpVal);}

void DSP2_YUV2RGB_Set_Input(DSP2_YUV2RGB_Type type, DSP2_YUV2RGB_Input input)
{
    uint32_t tmpVal;

    if (DSP2_YUV2RGB_A == type) {
        YUV2RGB_SET_INPUT_MACRO(A)
    } else {
        BL_LOGE("YUV2RGB type %d not support!\r\n", type);
    }
}

#define YUV2RGB_GET_INPUT_MACRO(name) \
    {tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_Y2R##name##_CONFIG_0);\
     *input = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_Y2R##name##_SEL);}

void DSP2_YUV2RGB_Get_Input(DSP2_YUV2RGB_Type type, DSP2_YUV2RGB_Input *input)
{
    uint32_t tmpVal;

    if (DSP2_YUV2RGB_A == type) {
        YUV2RGB_GET_INPUT_MACRO(A)
    } else {
        BL_LOGE("YUV2RGB type %d not support!\r\n", type);
    }
}

static void DSP2_YUV2RGB_Set_Config(struct yuv2rgb_param_t *param)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_Y2RA_CONFIG_0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_Y2RA_PRE_0, param->pre_offset_0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_Y2RA_POS_0, param->post_offset_0);
    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_Y2RA_CONFIG_0, tmpVal);

    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_Y2RA_CONFIG_1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_Y2RA_PRE_1, param->pre_offset_1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_Y2RA_POS_1, param->post_offset_1);
    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_Y2RA_CONFIG_1, tmpVal);

    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_Y2RA_CONFIG_2);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_Y2RA_PRE_2, param->pre_offset_2);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_Y2RA_POS_2, param->post_offset_2);
    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_Y2RA_CONFIG_2, tmpVal);

    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_Y2RA_CONFIG_3);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_Y2RA_MTX_00, param->matrix_00);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_Y2RA_MTX_01, param->matrix_01);
    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_Y2RA_CONFIG_3, tmpVal);

    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_Y2RA_CONFIG_4);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_Y2RA_MTX_02, param->matrix_02);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_Y2RA_MTX_10, param->matrix_10);
    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_Y2RA_CONFIG_4, tmpVal);

    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_Y2RA_CONFIG_5);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_Y2RA_MTX_11, param->matrix_11);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_Y2RA_MTX_12, param->matrix_12);
    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_Y2RA_CONFIG_5, tmpVal);

    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_Y2RA_CONFIG_6);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_Y2RA_MTX_20, param->matrix_20);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_Y2RA_MTX_21, param->matrix_21);
    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_Y2RA_CONFIG_6, tmpVal);

    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_Y2RA_CONFIG_7);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_Y2RA_MTX_22, param->matrix_22);
    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_Y2RA_CONFIG_7, tmpVal);

}

void DSP2_YUV2RGB_Init(DSP2_YUV2RGB_Param type)
{
    switch (type) {
        case DSP2_YUV2RGB_PARAM_8BIT_BT601:
            DSP2_YUV2RGB_Set_Config(&g_bt601_yuv2rgb_cfg);
            break;
        default:
            BL_LOGE("Unknown yuv2rgb type %d\r\n", type);
            break;
    }
}

/****************************************************************************//**
 * @brief  OSD input selection
 *
 * @param  osdId: OSD id
 * @param  inputType: OSD input type
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MISC_OSD_Input_Select(DSP2_MISC_OSD_ID_Type osdId,DSP2_MISC_OSD_Input_Type inputType)
{
    uint32_t tmpVal;
    uint32_t osdAddr = DSP2_MISC_BASE+DSP2_MISC_OSDA_I_CTRL_OFFSET+4*osdId;

    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_MISC_OSD_ID_TYPE(osdId));
    CHECK_PARAM(IS_DSP2_MISC_OSD_INPUT_TYPE(inputType));

    tmpVal = BL_RD_WORD(osdAddr);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_OSDA_SEL,inputType);
    BL_WR_WORD(osdAddr,tmpVal);
}

void DSP2_MISC_OSD_Get_Input_Select(DSP2_MISC_OSD_ID_Type osdId,DSP2_MISC_OSD_Input_Type *inputType)
{
    uint32_t tmpVal;
    uint32_t osdAddr = DSP2_MISC_BASE+DSP2_MISC_OSDA_I_CTRL_OFFSET+4*osdId;

    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_MISC_OSD_ID_TYPE(osdId));
    CHECK_PARAM(IS_DSP2_MISC_OSD_INPUT_TYPE(inputType));

    tmpVal = BL_RD_WORD(osdAddr);
    *inputType = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_OSDA_SEL);
}

void DSP2_MISC_OSD_Pb_Input_Select(DSP2_MISC_OSD_PB_Input_Type inputType)
{
    uint32_t tmpVal;
    
    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_MISC_OSD_PB_INPUT_TYPE(inputType));

    tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_OSDA_I_CTRL);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_OSD_PB_SEL,inputType);
    BL_WR_REG(DSP2_MISC_BASE,DSP2_MISC_OSDA_I_CTRL,tmpVal);
}

void DSP2_MISC_OSD_Pb_Get_Input_Select(DSP2_MISC_OSD_PB_Input_Type *inputType)
{
    uint32_t tmpVal;
    
    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_MISC_OSD_PB_INPUT_TYPE(inputType));

    tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_OSDA_I_CTRL);
    *inputType = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_OSD_PB_SEL);
}

/****************************************************************************//**
 * @brief  Configure bayer data shift function
 *
 * @param  bitEnable: Enable bits used
 * @param  shiftType: Set shift direction
 * @param  bitShift: Set Shift bits
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MISC_Bayer_Shift(uint16_t bitEnable,DSP2_MISC_Bayer_Shift_Type shiftType,uint8_t bitShift)
{
    uint32_t tmpVal = 0;

    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_MISC_BAYER_SHIFT_TYPE(shiftType));

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_REG_PIX_DATA_CTRL,bitEnable);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_REG_PIX_DATA_SHT_BIT,bitShift);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_REG_PIX_DATA_SHT_DIR,shiftType);
    BL_WR_REG(DSP2_MISC_BASE,DSP2_MISC_PIX_DATA_CTRL,tmpVal);
}

/****************************************************************************//**
 * @brief  YUV2RGB init
 *
 * @param  yuv2rgbId: YUV2RGB ID type
 * @param  yuv2rgbCfg: YUV2RGB configuration structure pointer
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MISC_YUV2RGB_Init(DSP2_MISC_YUV2RGB_ID_Type yuv2rgbId,DSP2_MISC_YUV2RGB_Cfg_Type* yuv2rgbCfg)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_MISC_YUV2RGB_ID_TYPE(yuv2rgbId));

    if(yuv2rgbId == DSP2_MISC_YUV2RGB_DISPLAY_ID){
        tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_DISP_YUV_RGB_CONFIG_0);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_Y2R_PRE_0,yuv2rgbCfg->preOffset0);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_Y2R_PRE_1,yuv2rgbCfg->preOffset1);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_Y2R_PRE_2,yuv2rgbCfg->preOffset2);
        BL_WR_REG(DSP2_MISC_BASE,DSP2_MISC_DISP_YUV_RGB_CONFIG_0,tmpVal);

        tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_DISP_YUV_RGB_CONFIG_1);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_Y2R_POS_0,yuv2rgbCfg->postOffset0);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_Y2R_POS_1,yuv2rgbCfg->postOffset1);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_Y2R_POS_2,yuv2rgbCfg->postOffset2);
        BL_WR_REG(DSP2_MISC_BASE,DSP2_MISC_DISP_YUV_RGB_CONFIG_1,tmpVal);

        tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_DISP_YUV_RGB_CONFIG_2);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_Y2R_MTX_00,yuv2rgbCfg->matrix00);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_Y2R_MTX_01,yuv2rgbCfg->matrix01);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_Y2R_MTX_02_L,yuv2rgbCfg->matrix02);
        BL_WR_REG(DSP2_MISC_BASE,DSP2_MISC_DISP_YUV_RGB_CONFIG_2,tmpVal);

        tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_DISP_YUV_RGB_CONFIG_3);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_Y2R_MTX_02_U,(yuv2rgbCfg->matrix02>>8));
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_Y2R_MTX_10,yuv2rgbCfg->matrix10);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_Y2R_MTX_11,yuv2rgbCfg->matrix11);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_Y2R_MTX_12_L,yuv2rgbCfg->matrix12);
        BL_WR_REG(DSP2_MISC_BASE,DSP2_MISC_DISP_YUV_RGB_CONFIG_3,tmpVal);

        tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_DISP_YUV_RGB_CONFIG_4);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_Y2R_MTX_12_U,(yuv2rgbCfg->matrix12>>4));
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_Y2R_MTX_20,yuv2rgbCfg->matrix20);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_Y2R_MTX_21,yuv2rgbCfg->matrix21);
        BL_WR_REG(DSP2_MISC_BASE,DSP2_MISC_DISP_YUV_RGB_CONFIG_4,tmpVal);

        tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_DISP_YUV_RGB_CONFIG_5);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_Y2R_MTX_22,yuv2rgbCfg->matrix22);
        BL_WR_REG(DSP2_MISC_BASE,DSP2_MISC_DISP_YUV_RGB_CONFIG_5,tmpVal);

        /* Enable or disable function */
        tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_DISP_YUV_RGB_CONFIG_0);
        BL_WR_REG(DSP2_MISC_BASE,DSP2_MISC_DISP_YUV_RGB_CONFIG_0,BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_Y2R_EN,yuv2rgbCfg->enable));

    }else if(yuv2rgbId == DSP2_MISC_YUV2RGB_NORMAL_ID){
        tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_Y2RA_CONFIG_0);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_Y2RA_PRE_0,yuv2rgbCfg->preOffset0);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_Y2RA_POS_0,yuv2rgbCfg->postOffset0);
        BL_WR_REG(DSP2_MISC_BASE,DSP2_MISC_Y2RA_CONFIG_0,tmpVal);

        tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_Y2RA_CONFIG_1);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_Y2RA_PRE_1,yuv2rgbCfg->preOffset1);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_Y2RA_POS_1,yuv2rgbCfg->postOffset1);
        BL_WR_REG(DSP2_MISC_BASE,DSP2_MISC_Y2RA_CONFIG_1,tmpVal);

        tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_Y2RA_CONFIG_2);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_Y2RA_PRE_2,yuv2rgbCfg->preOffset2);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_Y2RA_POS_2,yuv2rgbCfg->postOffset2);
        BL_WR_REG(DSP2_MISC_BASE,DSP2_MISC_Y2RA_CONFIG_2,tmpVal);

        tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_Y2RA_CONFIG_3);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_Y2RA_MTX_00,yuv2rgbCfg->matrix00);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_Y2RA_MTX_01,yuv2rgbCfg->matrix01);
        BL_WR_REG(DSP2_MISC_BASE,DSP2_MISC_Y2RA_CONFIG_3,tmpVal);

        tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_Y2RA_CONFIG_4);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_Y2RA_MTX_02,yuv2rgbCfg->matrix02);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_Y2RA_MTX_10,yuv2rgbCfg->matrix10);
        BL_WR_REG(DSP2_MISC_BASE,DSP2_MISC_Y2RA_CONFIG_4,tmpVal);

        tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_Y2RA_CONFIG_5);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_Y2RA_MTX_11,yuv2rgbCfg->matrix11);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_Y2RA_MTX_12,yuv2rgbCfg->matrix12);
        BL_WR_REG(DSP2_MISC_BASE,DSP2_MISC_Y2RA_CONFIG_5,tmpVal);

        tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_Y2RA_CONFIG_6);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_Y2RA_MTX_20,yuv2rgbCfg->matrix20);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_Y2RA_MTX_21,yuv2rgbCfg->matrix21);
        BL_WR_REG(DSP2_MISC_BASE,DSP2_MISC_Y2RA_CONFIG_6,tmpVal);

        tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_Y2RA_CONFIG_7);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_Y2RA_MTX_22,yuv2rgbCfg->matrix22);
        BL_WR_REG(DSP2_MISC_BASE,DSP2_MISC_Y2RA_CONFIG_7,tmpVal);

        tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_Y2RA_CONFIG_0);
        BL_WR_REG(DSP2_MISC_BASE,DSP2_MISC_Y2RA_CONFIG_0,BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_Y2RA_EN,yuv2rgbCfg->enable));
    }
}

void DSP2_MISC_YUV2RGB_Get_Cfg(DSP2_MISC_YUV2RGB_ID_Type yuv2rgbId,DSP2_MISC_YUV2RGB_Cfg_Type* yuv2rgbCfg)
{
    uint32_t tmpVal;
    uint16_t temp_mtx_l, temp_mtx_u;

    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_MISC_YUV2RGB_ID_TYPE(yuv2rgbId));

    if(yuv2rgbId == DSP2_MISC_YUV2RGB_DISPLAY_ID){
        tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_DISP_YUV_RGB_CONFIG_0);
        yuv2rgbCfg->preOffset0 = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_Y2R_PRE_0);
        yuv2rgbCfg->preOffset1 = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_Y2R_PRE_1);
        yuv2rgbCfg->preOffset2 = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_Y2R_PRE_2);

        tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_DISP_YUV_RGB_CONFIG_1);
        yuv2rgbCfg->postOffset0 = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_Y2R_POS_0);
        yuv2rgbCfg->postOffset1 = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_Y2R_POS_1);
        yuv2rgbCfg->postOffset2 = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_Y2R_POS_2);

        tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_DISP_YUV_RGB_CONFIG_2);
        yuv2rgbCfg->matrix00 = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_Y2R_MTX_00);
        yuv2rgbCfg->matrix01 = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_Y2R_MTX_01);
        temp_mtx_l = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_Y2R_MTX_02_L);

        tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_DISP_YUV_RGB_CONFIG_3);
        temp_mtx_u = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_Y2R_MTX_02_U);
        yuv2rgbCfg->matrix02 = (temp_mtx_u << 8) + temp_mtx_l;
        
        yuv2rgbCfg->matrix10 = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_Y2R_MTX_10);
        yuv2rgbCfg->matrix11 = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_Y2R_MTX_11);
        temp_mtx_l = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_Y2R_MTX_12_L);

        tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_DISP_YUV_RGB_CONFIG_4);
        temp_mtx_u = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_Y2R_MTX_12_U);
        yuv2rgbCfg->matrix12 = (temp_mtx_u << 4) + temp_mtx_l;
        
        yuv2rgbCfg->matrix20 = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_Y2R_MTX_20);
        yuv2rgbCfg->matrix21 = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_Y2R_MTX_21);

        tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_DISP_YUV_RGB_CONFIG_5);
        yuv2rgbCfg->matrix22 = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_Y2R_MTX_22);

        /* Enable or disable function */
        tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_DISP_YUV_RGB_CONFIG_0);
        yuv2rgbCfg->enable = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_Y2R_EN);

    }else if(yuv2rgbId == DSP2_MISC_YUV2RGB_NORMAL_ID){
        tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_Y2RA_CONFIG_0);
        yuv2rgbCfg->preOffset0 = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_Y2RA_PRE_0);
        yuv2rgbCfg->postOffset0 = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_Y2RA_POS_0);

        tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_Y2RA_CONFIG_1);
        yuv2rgbCfg->preOffset1 = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_Y2RA_PRE_1);
        yuv2rgbCfg->postOffset1 = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_Y2RA_POS_1);

        tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_Y2RA_CONFIG_2);
        yuv2rgbCfg->preOffset2 = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_Y2RA_PRE_2);
        yuv2rgbCfg->postOffset2 = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_Y2RA_POS_2);

        tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_Y2RA_CONFIG_3);
        yuv2rgbCfg->matrix00 = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_Y2RA_MTX_00);
        yuv2rgbCfg->matrix01 = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_Y2RA_MTX_01);

        tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_Y2RA_CONFIG_4);
        yuv2rgbCfg->matrix02 = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_Y2RA_MTX_02);
        yuv2rgbCfg->matrix10 = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_Y2RA_MTX_10);

        tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_Y2RA_CONFIG_5);
        yuv2rgbCfg->matrix11 = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_Y2RA_MTX_11);
        yuv2rgbCfg->matrix12 = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_Y2RA_MTX_12);

        tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_Y2RA_CONFIG_6);
        yuv2rgbCfg->matrix20 = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_Y2RA_MTX_20);
        yuv2rgbCfg->matrix21 = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_Y2RA_MTX_21);

        tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_Y2RA_CONFIG_7);
        yuv2rgbCfg->matrix22 = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_Y2RA_MTX_22);

        tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_Y2RA_CONFIG_0);
        yuv2rgbCfg->enable = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_Y2RA_EN);
    }
}

/****************************************************************************//**
 * @brief  Scaler init
 *
 * @param  scalerId: Scaler id
 * @param  scalerCfg: Scaler configuration structure pointer
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MISC_Scaler_Init(DSP2_MISC_Scaler_ID_Type scalerId,DSP2_MISC_Scaler_Cfg_Type* scalerCfg)
{
    uint32_t tmpVal;
    uint32_t scalerAddr = DSP2_MISC_BASE+DSP2_MISC_SCALERA_I_SIZE_OFFSET+8*scalerId;

    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_MISC_SCALER_ID_TYPE(scalerId));

    tmpVal = BL_RD_WORD(scalerAddr);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_SCALERA_I_W,scalerCfg->inputWidth);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_SCALERA_I_H,(scalerCfg->inputHeight&0x7ff));
    BL_WR_WORD(scalerAddr,tmpVal);

    scalerAddr += 4;
    tmpVal = BL_RD_WORD(scalerAddr);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_SCALERA_O_W,scalerCfg->outputWidth);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_SCALERA_O_H,scalerCfg->outputHeight);
    BL_WR_WORD(scalerAddr,tmpVal);
}

/****************************************************************************//**
 * @brief  Scaler get cfg
 *
 * @param  scalerId: Scaler id
 * @param  scalerCfg: Scaler configuration structure pointer
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MISC_Scaler_Get_Cfg(DSP2_MISC_Scaler_ID_Type scalerId,DSP2_MISC_Scaler_Cfg_Type* scalerCfg)
{
    uint32_t tmpVal;
    uint32_t scalerAddr = DSP2_MISC_BASE+DSP2_MISC_SCALERA_I_SIZE_OFFSET+8*scalerId;

    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_MISC_SCALER_ID_TYPE(scalerId));

    tmpVal = BL_RD_WORD(scalerAddr);
    scalerCfg->inputWidth = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_SCALERA_I_W);
    scalerCfg->inputHeight = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_SCALERA_I_H);

    scalerAddr += 4;
    tmpVal = BL_RD_WORD(scalerAddr);
    scalerCfg->outputWidth = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_SCALERA_O_W);
    scalerCfg->outputHeight = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_SCALERA_O_H);
}

/****************************************************************************//**
 * @brief  Scaler input selection
 *
 * @param  scalerId: Scaler id
 * @param  inputType: Scaler input type
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MISC_Scaler_Input_Select(DSP2_MISC_Scaler_ID_Type scalerId,DSP2_MISC_Scaler_Input_Type inputType)
{
    uint32_t tmpVal;
    uint32_t scalerAddr = DSP2_MISC_BASE+DSP2_MISC_SCALERA_I_SIZE_OFFSET+8*scalerId;

    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_MISC_SCALER_ID_TYPE(scalerId));
    CHECK_PARAM(IS_DSP2_MISC_SCALER_INPUT_TYPE(inputType));

    tmpVal = BL_RD_WORD(scalerAddr);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_SCALERA_SEL,inputType);
    BL_WR_WORD(scalerAddr,tmpVal);
}

void DSP2_MISC_Scaler_Get_Input_Select(DSP2_MISC_Scaler_ID_Type scalerId,DSP2_MISC_Scaler_Input_Type *inputType)
{
    uint32_t tmpVal;
    uint32_t scalerAddr = DSP2_MISC_BASE+DSP2_MISC_SCALERA_I_SIZE_OFFSET+8*scalerId;

    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_MISC_SCALER_ID_TYPE(scalerId));
    CHECK_PARAM(IS_DSP2_MISC_SCALER_INPUT_TYPE(inputType));

    tmpVal = BL_RD_WORD(scalerAddr);
    *inputType = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_SCALERA_SEL);
}

/****************************************************************************//**
 * @brief  Scaler enable
 *
 * @param  scalerId: Scaler id
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MISC_Scaler_Enable(DSP2_MISC_Scaler_ID_Type scalerId)
{
    uint32_t tmpVal;
    uint32_t scalerAddr = DSP2_MISC_BASE+DSP2_MISC_SCALERA_I_SIZE_OFFSET+8*scalerId;

    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_MISC_SCALER_ID_TYPE(scalerId));

    tmpVal = BL_RD_WORD(scalerAddr);
    tmpVal = BL_CLR_REG_BIT(tmpVal,DSP2_MISC_RG_SCALERA_BYPASS);
    BL_WR_WORD(scalerAddr,tmpVal);
}

/****************************************************************************//**
 * @brief  Scaler disable
 *
 * @param  scalerId: Scaler id
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MISC_Scaler_Disable(DSP2_MISC_Scaler_ID_Type scalerId)
{
    uint32_t tmpVal;
    uint32_t scalerAddr = DSP2_MISC_BASE+DSP2_MISC_SCALERA_I_SIZE_OFFSET+8*scalerId;

    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_MISC_SCALER_ID_TYPE(scalerId));

    tmpVal = BL_RD_WORD(scalerAddr);
    tmpVal = BL_SET_REG_BIT(tmpVal,DSP2_MISC_RG_SCALERA_BYPASS);
    BL_WR_WORD(scalerAddr,tmpVal);
}

void DSP2_MISC_Scaler_Get_State(DSP2_MISC_Scaler_ID_Type scalerId, BL_Fun_Type *state)
{
    uint32_t tmpVal;
    uint32_t scalerAddr = DSP2_MISC_BASE+DSP2_MISC_SCALERA_I_SIZE_OFFSET+8*scalerId;

    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_MISC_SCALER_ID_TYPE(scalerId));

    tmpVal = BL_RD_WORD(scalerAddr);
    if (BL_IS_REG_BIT_SET(tmpVal, DSP2_MISC_RG_SCALERA_BYPASS)) {
        *state = DISABLE;
    } else {
        *state = ENABLE;
    }
}

void DSP2_MISC_Scaler_Sh_Enable(DSP2_MISC_Scaler_ID_Type scalerId)
{
    uint32_t tmpVal;
    uint32_t scalerAddr = DSP2_MISC_BASE+DSP2_MISC_SCALERA_I_SIZE_OFFSET+8*scalerId;

    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_MISC_SCALER_ID_TYPE(scalerId));

    tmpVal = BL_RD_WORD(scalerAddr);
    tmpVal = BL_SET_REG_BIT(tmpVal,DSP2_MISC_RG_SCLRB_SW_SH);
    BL_WR_WORD(scalerAddr,tmpVal);
}

void DSP2_MISC_Scaler_Sh_Disable(DSP2_MISC_Scaler_ID_Type scalerId)
{
    uint32_t tmpVal;
    uint32_t scalerAddr = DSP2_MISC_BASE+DSP2_MISC_SCALERA_I_SIZE_OFFSET+8*scalerId;

    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_MISC_SCALER_ID_TYPE(scalerId));

    tmpVal = BL_RD_WORD(scalerAddr);
    tmpVal = BL_CLR_REG_BIT(tmpVal,DSP2_MISC_RG_SCLRB_SW_SH);
    BL_WR_WORD(scalerAddr,tmpVal);
}

/****************************************************************************//**
 * @brief  CAM input selection
 *
 * @param  camId: CAM id
 * @param  inputType: CAM input type
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MISC_CAM_Input_Select(DSP2_MISC_CAM_ID_Type camId,DSP2_MISC_CAM_Input_Type inputType)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_MISC_CAM_ID_TYPE(camId));
    CHECK_PARAM(IS_DSP2_MISC_CAM_INPUT_TYPE(inputType));

    if(camId < DSP2_MISC_CAM_4_ID){
        tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_DVP2BUS_SRC_SEL_1);
        tmpVal = (tmpVal&~(0x3f<<(camId*8)))|(inputType&0x3f)<<(camId*8);
        BL_WR_REG(DSP2_MISC_BASE,DSP2_MISC_DVP2BUS_SRC_SEL_1,tmpVal);
    }else{
        camId -= 4;
        tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_DVP2BUS_SRC_SEL_2);
        tmpVal = (tmpVal&~(0x3f<<(camId*8)))|(inputType&0x3f)<<(camId*8);
        BL_WR_REG(DSP2_MISC_BASE,DSP2_MISC_DVP2BUS_SRC_SEL_2,tmpVal);
    }
}

/****************************************************************************//**
 * @brief  Display init
 *
 * @param  displayCfg: Display configuration structure pointer
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MISC_Display_Init(DSP2_MISC_Display_Cfg_Type* displayCfg)
{
    uint32_t tmpVal;

    /* Check the parameters */
    //CHECK_PARAM(IS_DSP2_MISC_ADJUST_ID_TYPE(adjustId));
    //CHECK_PARAM(IS_DSP2_MISC_DISPLAY_OSD_INPUT_TYPE(displayCfg->osdType));
    //CHECK_PARAM(IS_DSP2_MISC_DISPLAY_INPUT_TYPE(displayCfg->inputType));

    tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_DISP_CONFIG);
    //tmpVal = BL_CLR_REG_BIT(tmpVal,DSP2_MISC_RG_DISP_BT656_EN);//delet on excel
    tmpVal = BL_CLR_REG_BIT(tmpVal,DSP2_MISC_RG_DISP_BT1120_EN);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_DPI_EN,displayCfg->dpiEnable);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_HDMI_EN,displayCfg->hdmiEnable);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_MUX_SEL,displayCfg->inputType);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_OSDDP_SEL,displayCfg->osdType);
    BL_WR_REG(DSP2_MISC_BASE,DSP2_MISC_DISP_CONFIG,tmpVal);

    if(displayCfg->bt1120Enable){
        tmpVal = BL_SET_REG_BIT(tmpVal,DSP2_MISC_RG_DISP_BT1120_EN);
    }else{
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_BT656_EN,displayCfg->bt656Enable);
    }
    BL_WR_REG(DSP2_MISC_BASE,DSP2_MISC_DISP_CONFIG,tmpVal);

    tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_DISP_DPI_CONFIG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_DPI_HS_W,displayCfg->hsyncWidth);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_DPI_HFP_W,displayCfg->hfpWidth);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_DPI_VS_W,displayCfg->vsyncWidth);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_DPI_VFP_W,displayCfg->vfpWidth);
    BL_WR_REG(DSP2_MISC_BASE,DSP2_MISC_DISP_DPI_CONFIG,tmpVal);
}

void DSP2_MISC_Display_Get_Cfg(DSP2_MISC_Display_Cfg_Type* displayCfg)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_DISP_CONFIG);
    displayCfg->bt656Enable  = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_BT656_EN);
    displayCfg->bt1120Enable = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_BT1120_EN);
    displayCfg->dpiEnable   = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_DPI_EN);
    displayCfg->hdmiEnable  = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_HDMI_EN);
    displayCfg->inputType   = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_MUX_SEL);
    displayCfg->osdType     = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_OSDDP_SEL);

    tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_DISP_DPI_CONFIG);
    displayCfg->hsyncWidth  = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_DPI_HS_W);
    displayCfg->hfpWidth    = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_DPI_HFP_W);
    displayCfg->vsyncWidth  = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_DPI_VS_W);
    displayCfg->vfpWidth    = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_DPI_VFP_W);
}

void DSP2_MISC_Display_Set_Clk_Output_Inv(int value)
{
    uint32_t tmpVal;
    
    tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_DISP_CONFIG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_CLKO_INV, value);

    BL_WR_REG(DSP2_MISC_BASE,DSP2_MISC_DISP_CONFIG,tmpVal);
}

void DSP2_MISC_Display_Get_Clk_Output_Inv(int *value)
{
    uint32_t tmpVal;
    
    tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_DISP_CONFIG);
    *value = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_CLKO_INV);
}

void DSP2_MISC_Display_RGB2YUV_Set_Cfg(DSP2_MISC_RGB2YUV_Cfg_Type* rgb2yuvCfg)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_DISP_RGB2YUV_CONFIG_0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_R2Y_PRE_0,rgb2yuvCfg->preOffset0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_R2Y_PRE_1,rgb2yuvCfg->preOffset1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_R2Y_PRE_2,rgb2yuvCfg->preOffset2);
    BL_WR_REG(DSP2_MISC_BASE,DSP2_MISC_DISP_RGB2YUV_CONFIG_0,tmpVal);

    tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_DISP_RGB2YUV_CONFIG_1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_R2Y_POS_0,rgb2yuvCfg->postOffset0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_R2Y_POS_1,rgb2yuvCfg->postOffset1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_R2Y_POS_2,rgb2yuvCfg->postOffset2);
    BL_WR_REG(DSP2_MISC_BASE,DSP2_MISC_DISP_RGB2YUV_CONFIG_1,tmpVal);

    tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_DISP_RGB2YUV_CONFIG_2);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_R2Y_MTX_00,rgb2yuvCfg->matrix00);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_R2Y_MTX_01,rgb2yuvCfg->matrix01);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_R2Y_MTX_02_L,(rgb2yuvCfg->matrix02 & 0xf));
    BL_WR_REG(DSP2_MISC_BASE,DSP2_MISC_DISP_RGB2YUV_CONFIG_2,tmpVal);

    tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_DISP_RGB2YUV_CONFIG_3);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_R2Y_MTX_02_U,(rgb2yuvCfg->matrix02>>8));
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_R2Y_MTX_10,rgb2yuvCfg->matrix10);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_R2Y_MTX_11,rgb2yuvCfg->matrix11);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_R2Y_MTX_12_L,(rgb2yuvCfg->matrix12 & 0x3));
    BL_WR_REG(DSP2_MISC_BASE,DSP2_MISC_DISP_RGB2YUV_CONFIG_3,tmpVal);

    tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_DISP_RGB2YUV_CONFIG_4);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_R2Y_MTX_12_U,(rgb2yuvCfg->matrix12>>4));
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_R2Y_MTX_20,rgb2yuvCfg->matrix20);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_R2Y_MTX_21,rgb2yuvCfg->matrix21);
    BL_WR_REG(DSP2_MISC_BASE,DSP2_MISC_DISP_RGB2YUV_CONFIG_4,tmpVal);

    tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_DISP_RGB2YUV_CONFIG_5);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_R2Y_MTX_22,rgb2yuvCfg->matrix22);
    BL_WR_REG(DSP2_MISC_BASE,DSP2_MISC_DISP_RGB2YUV_CONFIG_5,tmpVal);

    /* Enable or disable function */
    tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_DISP_RGB2YUV_CONFIG_0);
    BL_WR_REG(DSP2_MISC_BASE,DSP2_MISC_DISP_RGB2YUV_CONFIG_0,BL_SET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_R2Y_EN,rgb2yuvCfg->enable));

}

void DSP2_MISC_Display_RGB2YUV_Get_Cfg(DSP2_MISC_RGB2YUV_Cfg_Type* rgb2yuvCfg)
{
    uint32_t tmpVal;
    uint16_t temp_mtx_l, temp_mtx_u;

    tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_DISP_RGB2YUV_CONFIG_0);
    rgb2yuvCfg->preOffset0 = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_R2Y_PRE_0);
    rgb2yuvCfg->preOffset1 = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_R2Y_PRE_1);
    rgb2yuvCfg->preOffset2 = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_R2Y_PRE_2);

    tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_DISP_RGB2YUV_CONFIG_1);
    rgb2yuvCfg->postOffset0 = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_R2Y_POS_0);
    rgb2yuvCfg->postOffset1 = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_R2Y_POS_1);
    rgb2yuvCfg->postOffset2 = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_R2Y_POS_2);

    tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_DISP_RGB2YUV_CONFIG_2);
    rgb2yuvCfg->matrix00 = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_R2Y_MTX_00);
    rgb2yuvCfg->matrix01 = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_R2Y_MTX_01);
    temp_mtx_l = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_R2Y_MTX_02_L);

    tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_DISP_RGB2YUV_CONFIG_3);
    temp_mtx_u = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_R2Y_MTX_02_U);
    rgb2yuvCfg->matrix02 = (temp_mtx_u << 8) + temp_mtx_l;
    
    rgb2yuvCfg->matrix10 = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_R2Y_MTX_10);
    rgb2yuvCfg->matrix11 = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_R2Y_MTX_11);
    temp_mtx_l = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_R2Y_MTX_12_L);

    tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_DISP_RGB2YUV_CONFIG_4);
    temp_mtx_u = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_R2Y_MTX_12_U);
    rgb2yuvCfg->matrix12 = (temp_mtx_u << 4) + temp_mtx_l;
    
    rgb2yuvCfg->matrix20 = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_R2Y_MTX_20);
    rgb2yuvCfg->matrix21 = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_R2Y_MTX_21);

    tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_DISP_RGB2YUV_CONFIG_5);
    rgb2yuvCfg->matrix22 = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_R2Y_MTX_22);

    /* Enable or disable function */
    tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_DISP_RGB2YUV_CONFIG_0);
    rgb2yuvCfg->enable = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_RG_DISP_R2Y_EN);
}

/****************************************************************************//**
 * @brief  Crop init
 *
 * @param  cropId: Crop id
 * @param  cropCfg: Crop configuration structure pointer
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MISC_Crop_Init(DSP2_MISC_Crop_ID_Type cropId, DSP2_MISC_Crop_Cfg_Type* cropCfg)
{
    uint32_t cropAddr = DSP2_MISC_BASE+DSP2_MISC_CROPA_HSYNC_OFFSET+8*cropId;

    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_MISC_CROP_ID_TYPE(cropId));

    BL_WR_WORD(cropAddr,cropCfg->hsyncEnd<<16|cropCfg->hsyncStart);
    cropAddr += 4;
    BL_WR_WORD(cropAddr,cropCfg->vsyncEnd<<16|cropCfg->vsyncStart);
}

void DSP2_MISC_Crop_Get_Cfg(DSP2_MISC_Crop_ID_Type cropId, DSP2_MISC_Crop_Cfg_Type* cropCfg)
{
    uint32_t tmpVal;
    uint32_t cropAddr = DSP2_MISC_BASE+DSP2_MISC_CROPA_HSYNC_OFFSET+8*cropId;

    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_MISC_CROP_ID_TYPE(cropId));

    tmpVal = BL_RD_WORD(cropAddr);
    cropCfg->hsyncStart = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_REG_CROPA_HSYNC_START);
    cropCfg->hsyncEnd = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_REG_CROPA_HSYNC_END);

    cropAddr += 4;
    tmpVal = BL_RD_WORD(cropAddr);
    cropCfg->vsyncStart = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_REG_CROPA_VSYNC_START);
    cropCfg->vsyncEnd = BL_GET_REG_BITS_VAL(tmpVal,DSP2_MISC_REG_CROPA_VSYNC_END);
}

/****************************************************************************//**
 * @brief  Crop enable
 *
 * @param  cropId: Crop id
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MISC_Crop_Enable(DSP2_MISC_Crop_ID_Type cropId)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_MISC_CROP_ID_TYPE(cropId));

    tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_CROP_ENABLE);
    switch(cropId){
        case DSP2_MISC_CROP_0_ID:
            tmpVal = BL_SET_REG_BIT(tmpVal,DSP2_MISC_REG_CROPA_ENABLE);
            break;
        case DSP2_MISC_CROP_1_ID:
            tmpVal = BL_SET_REG_BIT(tmpVal,DSP2_MISC_REG_CROPB_ENABLE);
            break;
        case DSP2_MISC_CROP_2_ID:
            tmpVal = BL_SET_REG_BIT(tmpVal,DSP2_MISC_REG_CROPC_ENABLE);
            break;
        case DSP2_MISC_CROP_3_ID:
            tmpVal = BL_SET_REG_BIT(tmpVal,DSP2_MISC_REG_CROPD_ENABLE);
            break;
        default:
            break;
    }
    BL_WR_REG(DSP2_MISC_BASE,DSP2_MISC_CROP_ENABLE,tmpVal);
}

/****************************************************************************//**
 * @brief  Crop disable
 *
 * @param  cropId: Crop id
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MISC_Crop_Disable(DSP2_MISC_Crop_ID_Type cropId)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_MISC_CROP_ID_TYPE(cropId));

    tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_CROP_ENABLE);
    switch(cropId){
        case DSP2_MISC_CROP_0_ID:
            tmpVal = BL_CLR_REG_BIT(tmpVal,DSP2_MISC_REG_CROPA_ENABLE);
            break;
        case DSP2_MISC_CROP_1_ID:
            tmpVal = BL_CLR_REG_BIT(tmpVal,DSP2_MISC_REG_CROPB_ENABLE);
            break;
        case DSP2_MISC_CROP_2_ID:
            tmpVal = BL_CLR_REG_BIT(tmpVal,DSP2_MISC_REG_CROPC_ENABLE);
            break;
        case DSP2_MISC_CROP_3_ID:
            tmpVal = BL_CLR_REG_BIT(tmpVal,DSP2_MISC_REG_CROPD_ENABLE);
            break;
        default:
            break;
    }
    BL_WR_REG(DSP2_MISC_BASE,DSP2_MISC_CROP_ENABLE,tmpVal);
}

void DSP2_MISC_Crop_Get_State(DSP2_MISC_Crop_ID_Type cropId, BL_Fun_Type *state)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_MISC_CROP_ID_TYPE(cropId));

    tmpVal = BL_RD_REG(DSP2_MISC_BASE,DSP2_MISC_CROP_ENABLE);
    switch(cropId){
        case DSP2_MISC_CROP_0_ID:
            if (BL_IS_REG_BIT_SET(tmpVal, DSP2_MISC_REG_CROPA_ENABLE)) {
                *state = ENABLE;
            } else {
                *state = DISABLE;
            }
            break;
        case DSP2_MISC_CROP_1_ID:
            if (BL_IS_REG_BIT_SET(tmpVal, DSP2_MISC_REG_CROPB_ENABLE)) {
                *state = ENABLE;
            } else {
                *state = DISABLE;
            }
            break;
        case DSP2_MISC_CROP_2_ID:
            if (BL_IS_REG_BIT_SET(tmpVal, DSP2_MISC_REG_CROPC_ENABLE)) {
                *state = ENABLE;
            } else {
                *state = DISABLE;
            }
            break;
        case DSP2_MISC_CROP_3_ID:
            if (BL_IS_REG_BIT_SET(tmpVal, DSP2_MISC_REG_CROPD_ENABLE)) {
                *state = ENABLE;
            } else {
                *state = DISABLE;
            }
            break;
        default:
            break;
    }
}

void DSP2_MISC_Reshape_Set_State(BL_Fun_Type state)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_DVP_RESHAPE);

    if (ENABLE == state) {
        tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_REG_RSHP_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_MISC_REG_RSHP_EN);
    }

    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_DVP_RESHAPE, tmpVal);
}

void DSP2_MISC_Reshape_Get_State(BL_Fun_Type *state)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_DVP_RESHAPE);
    if (BL_IS_REG_BIT_SET(tmpVal, DSP2_MISC_REG_RSHP_EN)) {
        *state = ENABLE;
    } else {
        *state = DISABLE;
    }
}

void DSP2_MISC_Reshape_Counter_Clear()
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_DVP_RESHAPE);
    tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_REG_RSHP_CLR);
    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_DVP_RESHAPE, tmpVal);
}

void DSP2_MISC_Reshape_Set_Counter(int value)
{
    uint32_t tmpVal;

    CHECK_PARAM_RANGE(value, DSP2_MISC_RESHAPE_TOGGLE_COUNT_MIN, DSP2_MISC_RESHAPE_TOGGLE_COUNT_MAX);

    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_DVP_RESHAPE);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_RSHP_TGL_COUNT, value);
    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_DVP_RESHAPE, tmpVal);
}

void DSP2_MISC_Reshape_Get_Counter(int *value)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_DVP_RESHAPE);
    *value = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_RSHP_TGL_COUNT);
}

void DSP2_MISC_Reshape_Set_HSync_Inv(BL_Fun_Type state)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_DVP_RESHAPE);

    if (ENABLE == state) {
        tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_REG_RSHP_HSYNC_INV);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_MISC_REG_RSHP_HSYNC_INV);
    }

    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_DVP_RESHAPE, tmpVal);
}

void DSP2_MISC_Reshape_Get_HSync_Inv(BL_Fun_Type *state)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_DVP_RESHAPE);

    if (BL_IS_REG_BIT_SET(tmpVal, DSP2_MISC_REG_RSHP_HSYNC_INV)) {
        *state = ENABLE;
    } else {
        *state = DISABLE;
    }
}

void DSP2_MISC_Reshape_Set_VSync_Inv(BL_Fun_Type state)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_DVP_RESHAPE);

    if (ENABLE == state) {
        tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_REG_RSHP_VSYNC_INV);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_MISC_REG_RSHP_VSYNC_INV);
    }

    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_DVP_RESHAPE, tmpVal);
}

void DSP2_MISC_Reshape_Get_VSync_Inv(BL_Fun_Type *state)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_DVP_RESHAPE);

    if (BL_IS_REG_BIT_SET(tmpVal, DSP2_MISC_REG_RSHP_VSYNC_INV)) {
        *state = ENABLE;
    } else {
        *state = DISABLE;
    }

}


/****************************************************************************/ /**
 * @brief  Select SEOF interrupt vsync source
 *
 * @param  intType: SEOF interrupt type
 * @param  source: SEOF interrupt vsync source type
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MISC_SEOF_Set_Source(DSP2_MISC_INT_Type intType, DSP2_MISC_SEOF_Source_Type source)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_MISC_INT_TYPE(intType));
    CHECK_PARAM(IS_DSP2_MISC_SEOF_SOURCE_TYPE(source));

    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_INT_CTRL);

    switch (intType) {
        case DSP2_MISC_INT_SEOF0:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_SEOF1_INT_SRC, source);
            break;

        case DSP2_MISC_INT_SEOF1:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_SEOF2_INT_SRC, source);
            break;

        case DSP2_MISC_INT_SEOF2:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_SEOF3_INT_SRC, source);
            break;

        case DSP2_MISC_INT_DISPLAY:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DP_SEOF0_INT_SRC, source & 0x1);
            break;

        case DSP2_MISC_INT_SEOF3:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_SEOF4_INT_SRC, source);
            break;

        default:
            return;
            break;
    }

    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_INT_CTRL, tmpVal);
}


/****************************************************************************/ /**
 * @brief  Select SEOF interrupt vsync source
 *
 * @param  intType: SEOF interrupt type
 * @param  edge: SEOF interrupt edge type
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MISC_SEOF_Set_Edge(DSP2_MISC_INT_Type intType, DSP2_MISC_SEOF_Edge_Type edge)
{
    uint32_t tmpVal;

    /* Check the parameters */
    // CHECK_PARAM(IS_DSP2_MISC_INT_TYPE(intType));
    // CHECK_PARAM(IS_DSP2_MISC_SEOF_EDGE_TYPE(edge));

    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_INT_CTRL);

    switch (intType) {
        case DSP2_MISC_INT_SEOF0:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_SEOF1_INT_EDGE, edge);
            break;

        case DSP2_MISC_INT_SEOF1:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_SEOF2_INT_EDGE, edge);
            break;

        case DSP2_MISC_INT_SEOF2:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_SEOF3_INT_EDGE, edge);
            break;

        case DSP2_MISC_INT_DISPLAY:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DP_SEOF0_INT_EDGE, edge);
            break;

        case DSP2_MISC_INT_SEOF3:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_SEOF4_INT_EDGE, edge);
            break;

        default:
            return;
            break;
    }

    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_INT_CTRL, tmpVal);
}
/****************************************************************************/ /**
 * @brief  Mask/Unmask certain or all of the interrupt
 *
 * @param  intType: Interrupt type
 * @param  intMask: Mask or unmask
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MISC_Int_Mask(DSP2_MISC_INT_Type intType, BL_Mask_Type intMask)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_MISC_INT_TYPE(intType));
    CHECK_PARAM(IS_BL_MASK_TYPE(intMask));

    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_INT_CTRL);

    switch (intType) {
#if 1
        case DSP2_MISC_INT_AWB0:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_AWB_INT_MASK, intMask);
            break;

        case DSP2_MISC_INT_AE:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_AE_INT_MASK, intMask);
            break;

        case DSP2_MISC_INT_WDR:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_WDR_INT_MASK, intMask);
            break;

        case DSP2_MISC_INT_AWB1:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_AWB2_INT_MASK, intMask);
            break;

        case DSP2_MISC_INT_OSD_PB:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_OSD_PB_INT_MASK, intMask);
            break;

        case DSP2_MISC_INT_SEOF0:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_SEOF1_INT_MASK, intMask);
            break;

        case DSP2_MISC_INT_SEOF1:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_SEOF2_INT_MASK, intMask);
            break;

        case DSP2_MISC_INT_SEOF2:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_SEOF3_INT_MASK, intMask);
            break;

        case DSP2_MISC_INT_AE_HIST:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_AE_HIST_INT_MASK, intMask);
            break;

        case DSP2_MISC_INT_AWB2:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_AWB3_INT_MASK, intMask);
            break;
#endif
        case DSP2_MISC_INT_DISPLAY:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DP_SEOF0_INT_MASK, intMask);
            break;

        case DSP2_MISC_INT_SEOF3:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_SEOF4_INT_MASK, intMask);
            break;

        case DSP2_MISC_INT_ALL:
            if (intMask == MASK) {
                tmpVal |= 0x1131111f;
            } else {
                tmpVal &= ~0x1131111f;
            }

            break;

        default:
            break;
    }

    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_INT_CTRL, tmpVal);
}
#if 1
/****************************************************************************/ /**
 * @brief  Clear certain or all of the interrupt
 *
 * @param  intType: Interrupt type
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MISC_Int_Clear_1(DSP2_MISC_INT_Type intType)
{
    uint32_t tmpVal = 0;

    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_MISC_INT_TYPE(intType));

    switch (intType) {
#if 1
        case DSP2_MISC_INT_AWB0:
            tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_RG_AWB_INT_CLR);
            break;

        case DSP2_MISC_INT_AE:
            tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_RG_AE_INT_CLR);
            break;

        case DSP2_MISC_INT_WDR:
            tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_RG_WDR_INT_CLR);
            break;

        case DSP2_MISC_INT_AWB1:
            tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_RG_AWB2_INT_CLR);
            break;

        case DSP2_MISC_INT_OSD_PB:
            tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_RG_OSD_PB_INT_CLR);
            break;

        case DSP2_MISC_INT_SEOF0:
            tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_RG_SEOF1_INT_CLR);
            break;

        case DSP2_MISC_INT_SEOF1:
            tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_RG_SEOF2_INT_CLR);
            break;

        case DSP2_MISC_INT_SEOF2:
            tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_RG_SEOF3_INT_CLR);
            break;

        case DSP2_MISC_INT_AE_HIST:
            tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_RG_AE_HIST_INT_CLR);
            break;

        case DSP2_MISC_INT_AWB2:
            tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_RG_AWB3_INT_CLR);
            break;
#endif
        case DSP2_MISC_INT_DISPLAY:
            tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_RG_DP_SEOF0_INT_CLR);
            break;

        case DSP2_MISC_INT_SEOF3:
            tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_RG_SEOF4_INT_CLR);
            break;

        case DSP2_MISC_INT_ALL:
            tmpVal = 0x7f1f;
            break;

        default:
            break;
    }

    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_INT_CLR, tmpVal);
}
/*@} end of group DSP2_MISC_Private_Types */
#endif
/** @defgroup  DSP2_MISC_Private_Variables
 *  @{
 */
//#ifndef BFLB_USE_HAL_DRIVER
static intCallback_Type *dsp2MiscIntCbfArra[DSP2_MISC_INT_ALL] = {
    NULL
};
//#endif

/****************************************************************************/ /**
 * @brief  Display interrupt handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
//#ifndef BFLB_USE_HAL_DRIVER
void Display_IRQHandler(void)
{
    DSP2_MISC_Int_Clear_1(DSP2_MISC_INT_DISPLAY);

    if (dsp2MiscIntCbfArra[DSP2_MISC_INT_DISPLAY] != NULL) {
        dsp2MiscIntCbfArra[DSP2_MISC_INT_DISPLAY]();
    }
}
//#endif
#if 1

/****************************************************************************/ /**
 * @brief  Install dsp2 misc interrupt callback function
 *
 * @param  intType: DSP2 misc interrupt type
 * @param  cbFun: Pointer to interrupt callback function. The type should be void (*fn)(void)
 *
 * @return None
 *
*******************************************************************************/
//#ifndef BFLB_USE_HAL_DRIVER
void DSP2_MISC_Int_Callback_Install(DSP2_MISC_INT_Type intType, intCallback_Type *cbFun)
{
    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_MISC_INT_TYPE(intType));

    switch (intType) {
#if 0
#if defined(CPU_D0)

        case DSP2_MISC_INT_AWB0:
            Interrupt_Handler_Register(DSP2_AWB0_IRQn, AWB0_IRQHandler);
            break;
#endif

        case DSP2_MISC_INT_AE:
            Interrupt_Handler_Register(DSP2_AE_IRQn, AE_IRQHandler);
            break;

        case DSP2_MISC_INT_WDR:
            Interrupt_Handler_Register(DSP2_WDR_IRQn, WDR_IRQHandler);
            break;

        case DSP2_MISC_INT_AWB1:
            Interrupt_Handler_Register(DSP2_AWB1_IRQn, AWB1_IRQHandler);
            break;

        case DSP2_MISC_INT_OSD_PB:
            Interrupt_Handler_Register(OSD_PB_IRQn, OSD_PB_IRQHandler);
            break;

        case DSP2_MISC_INT_SEOF0:
            Interrupt_Handler_Register(SEOF_INT0_IRQn, SEOF0_IRQHandler);
            break;

        case DSP2_MISC_INT_SEOF1:
            Interrupt_Handler_Register(SEOF_INT1_IRQn, SEOF1_IRQHandler);
            break;

        case DSP2_MISC_INT_SEOF2:
            Interrupt_Handler_Register(SEOF_INT2_IRQn, SEOF2_IRQHandler);
            break;

        case DSP2_MISC_INT_AE_HIST:
            Interrupt_Handler_Register(DSP2_AE_HIST_IRQn, AE_HIST_IRQHandler);
            break;

        case DSP2_MISC_INT_AWB2:
            Interrupt_Handler_Register(DSP2_AWB2_IRQn, AWB2_IRQHandler);
            break;
#endif
        case DSP2_MISC_INT_DISPLAY:
            Interrupt_Handler_Register(DISPLAY_IRQn, Display_IRQHandler);
            break;
#if 0
        case DSP2_MISC_INT_SEOF3:
            Interrupt_Handler_Register(SEOF_INT3_IRQn, SEOF3_IRQHandler);
            break;
#endif
        default:
            break;
    }

    dsp2MiscIntCbfArra[intType] = cbFun;
}
#endif
//#endif