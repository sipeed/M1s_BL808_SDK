
#ifndef __BL808_DSP2_MISC_H__
#define __BL808_DSP2_MISC_H__

#include <bl808_comm_mm.h>
#include <bl808_dvp2axi.h>


typedef void(intCallback_Type)(void);

typedef enum {
    DVP_TSRC_PIX_FROM_DSP2       = 0,
    DVP_TSRC_PIX_FROM_SENSOR    = 1,
} DSP2_DVP_TSRC_PIX_SEL_E;

typedef enum {
    DVP_TSRC_SRC_DVP         = 0,
    DVP_TSRC_SRC_MIPI_CSI    = 1,
} DSP2_DTSRC_SRC_E;

typedef enum {
    DVP2AXI_ID_BAYER   = 0,
    DVP2AXI_ID_YUV     = 1,
} DVP2AXI_ID_E;

typedef enum {
    DVP2AXI_SRC_DSP2_INPUT              = 0,
    DVP2AXI_SRC_ACT_SE                 = 0x1,
    DVP2AXI_SRC_SCALER_FOR_CODEC       = 0x2,
    DVP2AXI_SRC_CODEC_YUV420           = 0x3,
    DVP2AXI_SRC_BNR_OUT                = 0x8,
    DVP2AXI_SRC_LSC                    = 0x9,
    DVP2AXI_SRC_DEFECT                 = 0xa,
    DVP2AXI_SRC_INTERPOLATION_R        = 0xb,
    DVP2AXI_SRC_INTERPOLATION_G        = 0xc,
    DVP2AXI_SRC_INTERPOLATION_B        = 0xd,
    DVP2AXI_SRC_COLOR_CORRECTION_R     = 0xe,
    DVP2AXI_SRC_COLOR_CORRECTION_G     = 0xf,
    DVP2AXI_SRC_COLOR_CORRECTION_B     = 0x10,
    DVP2AXI_SRC_CGAMMA_CORRECTION_GR   = 0x11,
    DVP2AXI_SRC_CGAMMA_CORRECTION_BG   = 0x12,
    DVP2AXI_SRC_EDGE_ENHANCEMENT_OUT   = 0x19,
    DVP2AXI_SRC_YUV_CONTROL_CB_Y       = 0x1a,
    DVP2AXI_SRC_YUV_CONTROL_CR_CB      = 0x1b,
    DVP2AXI_SRC_NOISE_REDUCTION        = 0x1d,
    DVP2AXI_SRC_DSP2_OUTPUT             = 0x1e,
    DVP2AXI_SRC_SCALER_FOR_HDMI        = 0x1f,
    DVP2AXI_SRC_OFF                    = 0x20,
} DVP2AXI_Src_Type;


typedef enum {
    DSP2_AE_INTR = 0,
    DSP2_AE_HIST_INTR,
    DSP2_AWB_INTR,
    DSP2_AWB2_INTR,
    DSP2_AWB3_INTR,
    DSP2_WDR_INTR,
    DSP2_OSD_PB_INTR,
    DSP2_SEOF1_INTR,
    DSP2_SEOF2_INTR,
    DSP2_SEOF3_INTR,
    DSP2_SEOF4_INTR,
    DSP2_DP_SEOF0_INTR,
} DSP2_INTR_SEL_E;

/**
 *  @brief Input V/H sync active level type definition
 */
typedef enum {
    DSP2_MISC_ACTIVE_HIGH, /*!< Input is active-high */
    DSP2_MISC_ACTIVE_LOW,  /*!< Input is active-low */
}DSP2_MISC_Active_Level_Type;

/**
 *  @brief DVP 2X input data order type definition
 */
typedef enum {
    DSP2_MISC_2X_DATA_BYTE_LOWER,  /*!< The first data is lower-byte */
    DSP2_MISC_2X_DATA_BYTE_HIGHER, /*!< The first data is higher-byte */
}DSP2_MISC_2X_Data_Order_Type;

/**
 *  @brief DVP input V/H sync active level type definition
 */
typedef enum {
    DVP_ACTIVE_HIGH,                         /*!< Input is active-high */
    DVP_ACTIVE_LOW,                          /*!< Input is active-low */
}DVP_Active_Level_Type;

/**
 *  @brief DVP input data order type definition
 */
typedef enum {
    DVP_DATA_BYTE_LOWER,                     /*!< The first data is lower-byte */
    DVP_DATA_BYTE_HIGHER,                    /*!< The first data is higher-byte */
}DVP_Data_Order_Type;

/**
 *  @brief DVP as 2x configuration strcut definition
 */
typedef struct {
    DSP2_MISC_Active_Level_Type hSyncLevel;        /*!< Input H-Sync active level */
    DSP2_MISC_Active_Level_Type vSyncLevel;        /*!< Input V-Sync active level */
    DSP2_MISC_2X_Data_Order_Type dataOrder;        /*!< Input data order */
    uint16_t fifoThreshold;                       /*!< Fifo threshold for each DVP line to start to
                                                  output,((Width-Fifo_th)*T_in*2)<(Width*T_out)<((Width-Fifo_th)*T_in*2+Blank*T_in) */
}DVP_2x_Cfg_Type;

/*
    SEOF number
 */
typedef enum {
    DSP2_SEOF0 = 0,
    DSP2_SEOF1,
    DSP2_SEOF2,
    DSP2_SEOF3,
    DSP2_SEOF4,
    DSP2_SEOF_NUM,
}DSP2_SEOF_E;

typedef enum {
    SEOF_INTR_SRC_SENSOR_VSYNC = 0,
    SEOF_INTR_SRC_DSP2_ACT_VSYNC = 1,
    SEOF_INTR_SRC_DSP2_OUT_VSYNC = 2,
    SEOF_INTR_SRC_DTSRC_VSYNC = 3,
    SEOF_INTR_SRC_INVALID,
} DSP2_Seof_Intr_Src_Type;

typedef enum {
    DSP2_DVP_10_BIT = 0,
    DSP2_DVP_12_BIT = 1,
} DSP2_DVP_BIT_DEPTH_E;

typedef enum {
    DSP2_SCALER_A,
    DSP2_SCALER_B,
    DSP2_SCALER_C,
    DSP2_SCALER_D,
} DSP2_Scaler_Type;

typedef enum {
    DSP2_YUV_ADJUST_A,
    DSP2_YUV_ADJUST_B,
    DSP2_YUV_ADJUST_C,
    DSP2_YUV_ADJUST_D,
} DSP2_YUV_Adjust_Type;

typedef enum {
    DSP2_YUV_ADJUST_INPUT_DSP2_OUTPUT ,
    DSP2_YUV_ADJUST_INPUT_DSP2_INPUT,
    DSP2_YUV_ADJUST_INPUT_OSD_A,
    DSP2_YUV_ADJUST_INPUT_OSD_B,
    DSP2_YUV_ADJUST_INPUT_OSD_C,
    DSP2_YUV_ADJUST_INPUT_OSD_D,
    DSP2_YUV_ADJUST_INPUT_SCALER_A,
    DSP2_YUV_ADJUST_INPUT_SCALER_B,
    DSP2_YUV_ADJUST_INPUT_SCALER_C,
    DSP2_YUV_ADJUST_INPUT_SCALER_D,
    DSP2_YUV_ADJUST_INPUT_DVP_2x,
} DSP2_YUV_Adjust_Input;

/**
 *  @brief OSD id type definition
 */
typedef enum {
    DSP2_MISC_OSD_0_ID,                       /*!< OSD 0 port define */
    DSP2_MISC_OSD_1_ID,                       /*!< OSD 1 port define */
    DSP2_MISC_OSD_2_ID,                       /*!< OSD 2 port define */
    DSP2_MISC_OSD_3_ID,                       /*!< OSD 3 port define */
    DSP2_MISC_OSD_ID_MAX,                     /*!< OSD max ID define */
}DSP2_MISC_OSD_ID_Type;

/**
 *  @brief OSD input type definition
 */
typedef enum {
    DSP2_MISC_OSD_DSP2_OUTPUT,                 /*!< Use DSP2 output as OSD input */
    DSP2_MISC_OSD_DSP2_INPUT,                  /*!< Use DSP2 input as OSD input */
    DSP2_MISC_OSD_SCALER_0_OUTPUT,            /*!< Use scaler 0 as OSD input */
    DSP2_MISC_OSD_SCALER_1_OUTPUT,            /*!< Use scaler 1 as OSD input */
    DSP2_MISC_OSD_SCALER_2_OUTPUT,            /*!< Use scaler 2 as OSD input */
    DSP2_MISC_OSD_SCALER_3_OUTPUT,            /*!< Use scaler 3 as OSD input */
    DSP2_MISC_OSD_OSD_0_OUTPUT,               /*!< Use osd 0 as OSD input, only osd 1/osd 3 support */
    DSP2_MISC_OSD_DVP_2X_OUTPUT,              /*!< Use dvp 2x as OSD input */
    DSP2_MISC_OSD_INPUT_MAX,                  /*!< OSD input max ID define */
}DSP2_MISC_OSD_Input_Type;
/**
 *  @brief OSD Pb input type definition
 */
typedef enum {
    DSP2_MISC_OSD_PB_DSP2_OUTPUT,                 /*!< Use DSP2 output as OSD input */
    DSP2_MISC_OSD_PB_DSP2_INPUT,                  /*!< Use DSP2 input as OSD input */
    DSP2_MISC_OSD_PB_MAX,                        /*!< OSD PB max ID define */
}DSP2_MISC_OSD_PB_Input_Type;

typedef enum {
    DSP2_OSD_A,
    DSP2_OSD_B,
    DSP2_OSD_C,
    DSP2_OSD_D,
} DSP2_OSD_Type;

typedef enum {
    DSP2_YUV2RGB_A,
} DSP2_YUV2RGB_Type;

typedef enum {
    DSP2_SCALER_INPUT_DSP2_OUTPUT ,
    DSP2_SCALER_INPUT_DSP2_INPUT,
    DSP2_SCALER_INPUT_OSD_A,
    DSP2_SCALER_INPUT_OSD_B,
    DSP2_SCALER_INPUT_OSD_C,
    DSP2_SCALER_INPUT_OSD_D,
    DSP2_SCALER_DVP_2X,
} DSP2_Scaler_Input;

/**
 *  @brief Crop configuration strcut definition
 */
typedef struct {
    uint16_t hsyncStart;                     /*!< Hsync valid start */
    uint16_t hsyncEnd;                       /*!< Hsync valid end */
    uint16_t vsyncStart;                     /*!< Vsync valid start */
    uint16_t vsyncEnd;                       /*!< Vsync valid end */
}DSP2_MISC_Crop_Cfg_Type;

typedef enum {
    DSP2_OSD_INPUT_DSP2_OUTPUT ,
    DSP2_OSD_INPUT_DSP2_INPUT,
    DSP2_OSD_INPUT_SCALER_A,
    DSP2_OSD_INPUT_SCALER_B,
    DSP2_OSD_INPUT_SCALER_C,
    DSP2_OSD_INPUT_SCALER_D,
    DSP2_OSD_INPUT_OSD_A,
    DSP2_OSD_INPUT_OSD_C,
} DSP2_OSD_Input;

typedef enum {
    DSP2_YUV2RGB_INPUT_DSP2_OUTPUT,
    DSP2_YUV2RGB_INPUT_DSP2_INPUT,
    DSP2_YUV2RGB_INPUT_OSD_A,
    DSP2_YUV2RGB_INPUT_OSD_B,
    DSP2_YUV2RGB_INPUT_OSD_C,
    DSP2_YUV2RGB_INPUT_OSD_D,
    DSP2_YUV2RGB_INPUT_SCALER_A,
    DSP2_YUV2RGB_INPUT_SCALER_B,
    DSP2_YUV2RGB_INPUT_SCALER_C,
    DSP2_YUV2RGB_INPUT_SCALER_D,
    DSP2_YUV2RGB_INPUT_DVP_2X,
    DSP2_YUV2RGB_INPUT_DISABLED,
} DSP2_YUV2RGB_Input;

typedef enum {
    DSP2_YUV2RGB_PARAM_8BIT_BT601 = 0,
    DSP2_YUV2RGB_PARAM_MAX,
} DSP2_YUV2RGB_Param;

typedef struct blDSP2_DVP2AXI_SRC_SEL_S {
    DVP2AXI_Src_Type data[DVP2AXI_NUM];
} DSP2_DVP2AXI_SRC_SEL_S;

typedef struct blDSP2_SCALER_CONFIG_S {
    BL_Img_Size_T input;
    BL_Img_Size_T output;
} DSP2_SCALER_CONFIG_S;

typedef struct blDSP2_FRAME_M_TO_N_S {
    BL_Fun_Type enb;
    int m;
    int n;
    int intv;
} DSP2_FRAME_M_TO_N_S;

struct yuv2rgb_param_t {
    int pre_offset_0;
    int pre_offset_1;
    int pre_offset_2;
    int post_offset_0;
    int post_offset_1;
    int post_offset_2;
    int matrix_00;
    int matrix_01;
    int matrix_02;
    int matrix_10;
    int matrix_11;
    int matrix_12;
    int matrix_20;
    int matrix_21;
    int matrix_22;
};

/**
 *  @brief Bayer data shift direction type definition
 */
typedef enum {
    DSP2_MISC_BAYER_SHIFT_LEFT,               /*!< Bayer data shift left */
    DSP2_MISC_BAYER_SHIFT_RIGHT,              /*!< Bayer data shift right */
}DSP2_MISC_Bayer_Shift_Type;

/**
 *  @brief Display input type definition
 */
typedef enum {
    DSP2_MISC_DISPLAY_YUV2RGB_OUTPUT,         /*!< Use yuv2rgb output as display input */
    DSP2_MISC_DISPLAY_OSD_DP_OUTPUT,          /*!< Use OSD_DP output as display input */
    DSP2_MISC_DISPLAY_TSRC_RGB_OUTPUT,        /*!< Use dvp tsrc rgb output as display input */
    DSP2_MISC_DISPLAY_TSRC_YUV422_OUTPUT,     /*!< Use dvp tsrc yuv422 output as display input */
}DSP2_MISC_Display_Input_Type;

/**
 *  @brief Display OSD input type definition
 */
typedef enum {
    DSP2_MISC_DISPLAY_OSD_YUV420TO422_OUTPUT, /*!< Use yuv420to422 output as display OSD input */
    DSP2_MISC_DISPLAY_OSD_RGB2YUV422_OUTPUT,  /*!< Use rgb2yuv422 output as display OSD input */
    DSP2_MISC_DISPLAY_OSD_TSRCYUV422_OUTPUT,  /*!< Use dvp tsrc yuv422 output as display OSD input */
}DSP2_MISC_Display_OSD_Input_Type;

/**
 *  @brief Display configuration structure type definition
 */
typedef struct {
    BL_Fun_Type dpiEnable;                   /*!< Enable or disable dpi function */
    BL_Fun_Type hdmiEnable;                  /*!< Enable or disable hdmi function */
    BL_Fun_Type bt1120Enable;                /*!< Enable or disable BT1120 function, BT1120 and BT656 should not be enabled at the same time */
    BL_Fun_Type bt656Enable;                 /*!< Enable or disable BT656 function, BT1120 and BT656 should not be enabled at the same time */
    DSP2_MISC_Display_Input_Type inputType;   /*!< Select display input */
    DSP2_MISC_Display_OSD_Input_Type osdType; /*!< Select display OSD input */
    uint8_t hsyncWidth;                      /*!< Horizontal synchronization width */
    uint8_t hfpWidth;                        /*!< Horizontal front porch width */
    uint8_t vsyncWidth;                      /*!< Vertical synchronization width */
    uint8_t vfpWidth;                        /*!< Vertical front porch width */
}DSP2_MISC_Display_Cfg_Type;

/**
 *  @brief Display gamma configuration structure type definition
 */
typedef struct {
    BL_Fun_Type ch0Enable;                   /*!< Enable or disable display gamma channel 0 */
    BL_Fun_Type ch1Enable;                   /*!< Enable or disable display gamma channel 1 */
    BL_Fun_Type ch2Enable;                   /*!< Enable or disable display gamma channel 2 */
    uint8_t* gammaCurve;                     /*!< Gamma curve */
}DSP2_MISC_Display_Gamma_Cfg_Type;

typedef struct {
    uint16_t y_luma;
    uint16_t y_mul0;
    uint16_t y_mul1;
    uint8_t y_min;
    uint8_t y_max;
    uint16_t uv_mul0;
    uint16_t uv_mul1;
    uint8_t uv_min;
    uint8_t uv_max;
}DSP2_YUV_Adjust_Cfg_Type;

/**
 *  @brief YUV2RGB configuration strcut definition
 */
typedef struct {
    BL_Fun_Type enable;                      /*!< Enable or disable yuv2rgb function */
    uint16_t preOffset0;                     /*!< YUV2RGB pre offset 0 */
    uint16_t preOffset1;                     /*!< YUV2RGB pre offset 1 */
    uint16_t preOffset2;                     /*!< YUV2RGB pre offset 2 */
    uint16_t postOffset0;                    /*!< YUV2RGB post offset 0 */
    uint16_t postOffset1;                    /*!< YUV2RGB post offset 1 */
    uint16_t postOffset2;                    /*!< YUV2RGB post offset 2 */
    uint16_t matrix00;                       /*!< YUV2RGB matrix 00 */
    uint16_t matrix01;                       /*!< YUV2RGB matrix 01 */
    uint16_t matrix02;                       /*!< YUV2RGB matrix 02 */
    uint16_t matrix10;                       /*!< YUV2RGB matrix 10 */
    uint16_t matrix11;                       /*!< YUV2RGB matrix 11 */
    uint16_t matrix12;                       /*!< YUV2RGB matrix 12 */
    uint16_t matrix20;                       /*!< YUV2RGB matrix 20 */
    uint16_t matrix21;                       /*!< YUV2RGB matrix 21 */
    uint16_t matrix22;                       /*!< YUV2RGB matrix 22 */
}DSP2_MISC_YUV2RGB_Cfg_Type;

/**
 *  @brief RGB2YUV configuration strcut definition
 */
typedef struct {
    BL_Fun_Type enable;                      /*!< Enable or disable rgb2yuv function */
    uint16_t preOffset0;                     /*!< RGB2YUV pre offset 0 */
    uint16_t preOffset1;                     /*!< RGB2YUV pre offset 1 */
    uint16_t preOffset2;                     /*!< RGB2YUV pre offset 2 */
    uint16_t postOffset0;                    /*!< RGB2YUV post offset 0 */
    uint16_t postOffset1;                    /*!< RGB2YUV post offset 1 */
    uint16_t postOffset2;                    /*!< RGB2YUV post offset 2 */
    uint16_t matrix00;                       /*!< RGB2YUV matrix 00 */
    uint16_t matrix01;                       /*!< RGB2YUV matrix 01 */
    uint16_t matrix02;                       /*!< RGB2YUV matrix 02 */
    uint16_t matrix10;                       /*!< RGB2YUV matrix 10 */
    uint16_t matrix11;                       /*!< RGB2YUV matrix 11 */
    uint16_t matrix12;                       /*!< RGB2YUV matrix 12 */
    uint16_t matrix20;                       /*!< RGB2YUV matrix 20 */
    uint16_t matrix21;                       /*!< RGB2YUV matrix 21 */
    uint16_t matrix22;                       /*!< RGB2YUV matrix 22 */
}DSP2_MISC_RGB2YUV_Cfg_Type;

/**
 *  @brief Scaler configuration strcut definition
 */
typedef struct {
    uint16_t inputWidth;                     /*!< Width of input frame */
    uint16_t inputHeight;                    /*!< Height of input frame */
    uint16_t outputWidth;                    /*!< Width of output frame */
    uint16_t outputHeight;                   /*!< Height of output frame */
}DSP2_MISC_Scaler_Cfg_Type;

/**
 *  @brief Scaler input type definition
 */
typedef enum {
    DSP2_MISC_SCALER_DSP2_OUTPUT,              /*!< Use DSP2 output as scaler input */
    DSP2_MISC_SCALER_DSP2_INPUT,               /*!< Use DSP2 input as scaler input */
    DSP2_MISC_SCALER_OSD_0_OUTPUT,            /*!< Use OSD 0 as scaler input */
    DSP2_MISC_SCALER_OSD_1_OUTPUT,            /*!< Use OSD 1 as scaler input */
    DSP2_MISC_SCALER_OSD_2_OUTPUT,            /*!< Use OSD 2 as scaler input */
    DSP2_MISC_SCALER_OSD_3_OUTPUT,            /*!< Use OSD 3 as scaler input */
    DSP2_MISC_SCALER_DVP_2X_OUTPUT,           /*!< Use DVP 2X as scaler input */
}DSP2_MISC_Scaler_Input_Type;


/**
 *  @brief DVP TSRC data source type definition
 */
typedef enum {
    DSP2_MISC_TSRC_SOURCE_DVP, /*!< DVP TSRC data source is DVP */
    DSP2_MISC_TSRC_SOURCE_CSI, /*!< DVP TSRC data source is MIPI CSI */
}DSP2_MISC_TSRC_Source_Type;


/**
 *  @brief Scaler id type definition
 */
typedef enum {
    DSP2_MISC_SCALER_0_ID,                    /*!< Scaler 0 port define */
    DSP2_MISC_SCALER_1_ID,                    /*!< Scaler 1 port define */
    DSP2_MISC_SCALER_2_ID,                    /*!< Scaler 2 port define */
    DSP2_MISC_SCALER_3_ID,                    /*!< Scaler 3 port define */
    DSP2_MISC_SCALER_ID_MAX,                  /*!< Scaler max ID define */
}DSP2_MISC_Scaler_ID_Type;

/**
 *  @brief Crop id type definition
 */
typedef enum {
    DSP2_MISC_CROP_0_ID,                      /*!< Crop 0 port define */
    DSP2_MISC_CROP_1_ID,                      /*!< Crop 1 port define */
    DSP2_MISC_CROP_2_ID,                      /*!< Crop 2 port define */
    DSP2_MISC_CROP_3_ID,                      /*!< Crop 3 port define */
    DSP2_MISC_CROP_ID_MAX,                    /*!< Crop max ID define */
}DSP2_MISC_Crop_ID_Type;

/**
 *  @brief CAM id type definition
 */
typedef enum {
    DSP2_MISC_CAM_0_ID,                       /*!< CAM 0 port define */
    DSP2_MISC_CAM_1_ID,                       /*!< CAM 1 port define */
    DSP2_MISC_CAM_2_ID,                       /*!< CAM 2 port define */
    DSP2_MISC_CAM_3_ID,                       /*!< CAM 3 port define */
    DSP2_MISC_CAM_4_ID,                       /*!< CAM 4 port define */
    DSP2_MISC_CAM_5_ID,                       /*!< CAM 5 port define */
    DSP2_MISC_CAM_6_ID,                       /*!< CAM 6 port define */
    DSP2_MISC_CAM_7_ID,                       /*!< CAM 7 port define */
    DSP2_MISC_CAM_ID_MAX,                     /*!< CAM max ID define */
}DSP2_MISC_CAM_ID_Type;

/**
 *  @brief CAM input type definition
 */
typedef enum {
    DSP2_MISC_CAM_DSP2_INPUT,                  /*!< Use DSP2 input as CAM input */
    DSP2_MISC_CAM_ACTIVE_DVP_OUTPUT,          /*!< Use active DVP(TG) as CAM input */
    DSP2_MISC_CAM_DEFECT_CORRECT_OUTPUT,      /*!< Use defect correct as CAM input */
    DSP2_MISC_CAM_CCM_R_OUTPUT,               /*!< Use CCM R as CAM input */
    DSP2_MISC_CAM_CCM_G_OUTPUT,               /*!< Use CCM G as CAM input */
    DSP2_MISC_CAM_CCM_B_OUTPUT,               /*!< Use CCM B as CAM input */
    DSP2_MISC_CAM_GAMMA_R_OUTPUT,             /*!< Use gamma R as CAM input */
    DSP2_MISC_CAM_GAMMA_G_OUTPUT,             /*!< Use gamma G as CAM input */
    DSP2_MISC_CAM_NONE_OUTPUT,                /*!< Don't use */
    DSP2_MISC_CAM_BNR_OUTPUT,                 /*!< Use BNR as CAM input */
    DSP2_MISC_CAM_NR_OUTPUT,                  /*!< Use NR as CAM input */
    DSP2_MISC_CAM_EE_OUTPUT,                  /*!< Use EE as CAM input */
    DSP2_MISC_CAM_DSP2_OUTPUT,                 /*!< Use DSP2 output as CAM input */
    DSP2_MISC_CAM_OSD_0_OUTPUT,               /*!< Use OSD 0 as CAM input */
    DSP2_MISC_CAM_OSD_1_OUTPUT,               /*!< Use OSD 1 as CAM input */
    DSP2_MISC_CAM_OSD_2_OUTPUT,               /*!< Use OSD 2 as CAM input */
    DSP2_MISC_CAM_OSD_3_OUTPUT,               /*!< Use OSD 3 as CAM input */
    DSP2_MISC_CAM_SCALER_0_OUTPUT,            /*!< Use scaler 0 as CAM input */
    DSP2_MISC_CAM_SCALER_1_OUTPUT,            /*!< Use scaler 1 as CAM input */
    DSP2_MISC_CAM_SCALER_2_OUTPUT,            /*!< Use scaler 2 as CAM input */
    DSP2_MISC_CAM_SCALER_3_OUTPUT,            /*!< Use scaler 3 as CAM input */
    DSP2_MISC_CAM_ADJUST_0_OUTPUT,            /*!< Use adjust 0 as CAM input */
    DSP2_MISC_CAM_ADJUST_1_OUTPUT,            /*!< Use adjust 1 as CAM input */
    DSP2_MISC_CAM_ADJUST_2_OUTPUT,            /*!< Use adjust 2 as CAM input */
    DSP2_MISC_CAM_ADJUST_3_OUTPUT,            /*!< Use adjust 3 as CAM input */
    DSP2_MISC_CAM_YUV420_0_OUTPUT,            /*!< Use YUV420 0 as CAM input */
    DSP2_MISC_CAM_YUV420_1_OUTPUT,            /*!< Use YUV420 1 as CAM input */
    DSP2_MISC_CAM_YUV420_2_OUTPUT,            /*!< Use YUV420 2 as CAM input */
    DSP2_MISC_CAM_YUV420_3_OUTPUT,            /*!< Use YUV420 3 as CAM input */
    DSP2_MISC_CAM_GAMMA_B_OUTPUT,             /*!< Use gamma B as CAM input */
    DSP2_MISC_CAM_WDR_Y_OUTPUT,               /*!< Use WDR Y as CAM input */
    DSP2_MISC_CAM_WDR_U_OUTPUT,               /*!< Use WDR U as CAM input */
    DSP2_MISC_CAM_WDR_V_OUTPUT,               /*!< Use WDR V as CAM input */
    DSP2_MISC_CAM_LSC_OUTPUT,                 /*!< Use LSC as CAM input */
    DSP2_MISC_CAM_YUV2RGB_OUTPUT = 35,        /*!< Use YUV2RGB as CAM input */
    DSP2_MISC_CAM_DVP2X_OUTPUT = 36,          /*!< Use DVP2X as CAM input */
}DSP2_MISC_CAM_Input_Type;


/**
 *  @brief DSP2 MISC interrupt type definition
 */
typedef enum {
    DSP2_MISC_INT_AWB0,    /*!< AWB 0 interrupt */
    DSP2_MISC_INT_AE,      /*!< AE interrupt */
    DSP2_MISC_INT_WDR,     /*!< WDR interrupt */
    DSP2_MISC_INT_AWB1,    /*!< AWB 1 interrupt */
    DSP2_MISC_INT_OSD_PB,  /*!< OSD probe interrupt */
    DSP2_MISC_INT_SEOF0,   /*!< S/E-oF 0 interrupt */
    DSP2_MISC_INT_SEOF1,   /*!< S/E-oF 1 interrupt */
    DSP2_MISC_INT_SEOF2,   /*!< S/E-oF 2 interrupt */
    DSP2_MISC_INT_AE_HIST, /*!< AE hist interrupt */
    DSP2_MISC_INT_AWB2,    /*!< AWB 2 interrupt */
    DSP2_MISC_INT_DISPLAY, /*!< Display S/E-oF 0 interrupt */
    DSP2_MISC_INT_SEOF3,   /*!< S/E-oF 3 interrupt */
    DSP2_MISC_INT_ALL,     /*!< All the interrupt */
} DSP2_MISC_INT_Type;


/**
 *  @brief SEOF interrupt vsync source type definition
 */
typedef enum {
    DSP2_MISC_SEOF_VSYNC_SENSOR = 0,     /*!< Use sensor vsync as SEOF vsync source */
    DSP2_MISC_SEOF_VSYNC_DSP2_ACT = 1,    /*!< Use dsp2 active vsync as SEOF vsync source */
    DSP2_MISC_SEOF_VSYNC_DSP2_OUT = 2,    /*!< Use dsp2 out vsync as SEOF vsync source */
    DSP2_MISC_SEOF_VSYNC_DVP_TSRC = 3,   /*!< Use dvp tsrc vsync as SEOF vsync source */
    DSP2_MISC_SEOF_DISPLAY_TEST_SRC = 0, /*!< Use display test source as display SEOF vsync source */
    DSP2_MISC_SEOF_DISPLAY_OUTPUT = 1,   /*!< Use display output as display SEOF vsync source */
} DSP2_MISC_SEOF_Source_Type;

/**
 *  @brief SEOF interrupt trigger vsync edge type definition
 */
typedef enum {
    DSP2_MISC_SEOF_VSYNC_NEGEDGE, /*!< Vsync negedge will trigger interrupt */
    DSP2_MISC_SEOF_VSYNC_POSEDGE, /*!< Vsync posedge will trigger interrupt */
} DSP2_MISC_SEOF_Edge_Type;

/**
 *  @brief YUV2RGB id type definition
 */
typedef enum {
    DSP2_MISC_YUV2RGB_DISPLAY_ID,             /*!< Display YUV2RGB port define, disp_y2r*/
    DSP2_MISC_YUV2RGB_NORMAL_ID,              /*!< Normal YUV2RGB port define, y2rA */
    DSP2_MISC_YUV2RGB_ID_MAX,                 /*!< YUV2RGB max ID define */
}DSP2_MISC_YUV2RGB_ID_Type;

/** @defgroup  DSP2_MISC_CAM_ID_TYPE
 *  @{
 */
#define IS_DSP2_MISC_CAM_ID_TYPE(type)                    (((type) == DSP2_MISC_CAM_0_ID) || \
                                                          ((type) == DSP2_MISC_CAM_1_ID) || \
                                                          ((type) == DSP2_MISC_CAM_2_ID) || \
                                                          ((type) == DSP2_MISC_CAM_3_ID) || \
                                                          ((type) == DSP2_MISC_CAM_4_ID) || \
                                                          ((type) == DSP2_MISC_CAM_5_ID) || \
                                                          ((type) == DSP2_MISC_CAM_6_ID) || \
                                                          ((type) == DSP2_MISC_CAM_7_ID) || \
                                                          ((type) == DSP2_MISC_CAM_ID_MAX))

/** @defgroup  DSP2_MISC_SCALER_ID_TYPE
 *  @{
 */
#define IS_DSP2_MISC_SCALER_ID_TYPE(type)                 (((type) == DSP2_MISC_SCALER_0_ID) || \
                                                          ((type) == DSP2_MISC_SCALER_1_ID) || \
                                                          ((type) == DSP2_MISC_SCALER_2_ID) || \
                                                          ((type) == DSP2_MISC_SCALER_3_ID) || \
                                                          ((type) == DSP2_MISC_SCALER_ID_MAX))

/** @defgroup  DSP2_MISC_TSRC_SOURCE_TYPE
 *  @{
 */
#define IS_DSP2_MISC_TSRC_SOURCE_TYPE(type) (((type) == DSP2_MISC_TSRC_SOURCE_DVP) || \
                                            ((type) == DSP2_MISC_TSRC_SOURCE_CSI))


/** @defgroup  DSP2_MISC_OSD_ID_TYPE
 *  @{
 */
#define IS_DSP2_MISC_OSD_ID_TYPE(type)                    (((type) == DSP2_MISC_OSD_0_ID) || \
                                                          ((type) == DSP2_MISC_OSD_1_ID) || \
                                                          ((type) == DSP2_MISC_OSD_2_ID) || \
                                                          ((type) == DSP2_MISC_OSD_3_ID) || \
                                                          ((type) == DSP2_MISC_OSD_ID_MAX))

/** @defgroup  DSP2_MISC_ADJUST_ID_TYPE
 *  @{
 */
#define IS_DSP2_MISC_ADJUST_ID_TYPE(type)                 (((type) == DSP2_MISC_ADJUST_0_ID) || \
                                                          ((type) == DSP2_MISC_ADJUST_1_ID) || \
                                                          ((type) == DSP2_MISC_ADJUST_2_ID) || \
                                                          ((type) == DSP2_MISC_ADJUST_3_ID) || \
                                                          ((type) == DSP2_MISC_ADJUST_ID_MAX))

/** @defgroup  DSP2_MISC_YUV2RGB_ID_TYPE
 *  @{
 */
#define IS_DSP2_MISC_YUV2RGB_ID_TYPE(type)                (((type) == DSP2_MISC_YUV2RGB_DISPLAY_ID) || \
                                                          ((type) == DSP2_MISC_YUV2RGB_NORMAL_ID) || \
                                                          ((type) == DSP2_MISC_YUV2RGB_ID_MAX))

/** @defgroup  DSP2_MISC_CAM_INPUT_TYPE
 *  @{
 */
#define IS_DSP2_MISC_CAM_INPUT_TYPE(type)                 (((type) == DSP2_MISC_CAM_DSP2_INPUT) || \
                                                          ((type) == DSP2_MISC_CAM_ACTIVE_DVP_OUTPUT) || \
                                                          ((type) == DSP2_MISC_CAM_DEFECT_CORRECT_OUTPUT) || \
                                                          ((type) == DSP2_MISC_CAM_CCM_R_OUTPUT) || \
                                                          ((type) == DSP2_MISC_CAM_CCM_G_OUTPUT) || \
                                                          ((type) == DSP2_MISC_CAM_CCM_B_OUTPUT) || \
                                                          ((type) == DSP2_MISC_CAM_GAMMA_R_OUTPUT) || \
                                                          ((type) == DSP2_MISC_CAM_GAMMA_G_OUTPUT) || \
                                                          ((type) == DSP2_MISC_CAM_NONE_OUTPUT) || \
                                                          ((type) == DSP2_MISC_CAM_BNR_OUTPUT) || \
                                                          ((type) == DSP2_MISC_CAM_NR_OUTPUT) || \
                                                          ((type) == DSP2_MISC_CAM_EE_OUTPUT) || \
                                                          ((type) == DSP2_MISC_CAM_DSP2_OUTPUT) || \
                                                          ((type) == DSP2_MISC_CAM_OSD_0_OUTPUT) || \
                                                          ((type) == DSP2_MISC_CAM_OSD_1_OUTPUT) || \
                                                          ((type) == DSP2_MISC_CAM_OSD_2_OUTPUT) || \
                                                          ((type) == DSP2_MISC_CAM_OSD_3_OUTPUT) || \
                                                          ((type) == DSP2_MISC_CAM_SCALER_0_OUTPUT) || \
                                                          ((type) == DSP2_MISC_CAM_SCALER_1_OUTPUT) || \
                                                          ((type) == DSP2_MISC_CAM_SCALER_2_OUTPUT) || \
                                                          ((type) == DSP2_MISC_CAM_SCALER_3_OUTPUT) || \
                                                          ((type) == DSP2_MISC_CAM_ADJUST_0_OUTPUT) || \
                                                          ((type) == DSP2_MISC_CAM_ADJUST_1_OUTPUT) || \
                                                          ((type) == DSP2_MISC_CAM_ADJUST_2_OUTPUT) || \
                                                          ((type) == DSP2_MISC_CAM_ADJUST_3_OUTPUT) || \
                                                          ((type) == DSP2_MISC_CAM_YUV420_0_OUTPUT) || \
                                                          ((type) == DSP2_MISC_CAM_YUV420_1_OUTPUT) || \
                                                          ((type) == DSP2_MISC_CAM_YUV420_2_OUTPUT) || \
                                                          ((type) == DSP2_MISC_CAM_YUV420_3_OUTPUT) || \
                                                          ((type) == DSP2_MISC_CAM_GAMMA_B_OUTPUT) || \
                                                          ((type) == DSP2_MISC_CAM_WDR_Y_OUTPUT) || \
                                                          ((type) == DSP2_MISC_CAM_WDR_U_OUTPUT) || \
                                                          ((type) == DSP2_MISC_CAM_WDR_V_OUTPUT) || \
                                                          ((type) == DSP2_MISC_CAM_YUV2RGB_OUTPUT) || \
                                                          ((type) == DSP2_MISC_CAM_DVP2X_OUTPUT) || \
                                                          ((type) == DSP2_MISC_CAM_LSC_OUTPUT))

/** @defgroup  DSP2_MISC_SCALER_INPUT_TYPE
 *  @{
 */
#define IS_DSP2_MISC_SCALER_INPUT_TYPE(type)              (((type) == DSP2_MISC_SCALER_DSP2_OUTPUT) || \
                                                          ((type) == DSP2_MISC_SCALER_DSP2_INPUT) || \
                                                          ((type) == DSP2_MISC_SCALER_OSD_0_OUTPUT) || \
                                                          ((type) == DSP2_MISC_SCALER_OSD_1_OUTPUT) || \
                                                          ((type) == DSP2_MISC_SCALER_OSD_2_OUTPUT) || \
                                                          ((type) == DSP2_MISC_SCALER_OSD_3_OUTPUT) || \
                                                          ((type) == DSP2_MISC_SCALER_DVP_2X_OUTPUT))

/** @defgroup  DSP2_MISC_OSD_INPUT_TYPE
 *  @{
 */
#define IS_DSP2_MISC_OSD_INPUT_TYPE(type)                 (((type) == DSP2_MISC_OSD_DSP2_OUTPUT) || \
                                                          ((type) == DSP2_MISC_OSD_DSP2_INPUT) || \
                                                          ((type) == DSP2_MISC_OSD_SCALER_0_OUTPUT) || \
                                                          ((type) == DSP2_MISC_OSD_SCALER_1_OUTPUT) || \
                                                          ((type) == DSP2_MISC_OSD_SCALER_2_OUTPUT) || \
                                                          ((type) == DSP2_MISC_OSD_SCALER_3_OUTPUT) || \
                                                          ((type) == DSP2_MISC_OSD_OSD_0_OUTPUT) || \
                                                          ((type) == DSP2_MISC_OSD_DVP_2X_OUTPUT))
/** @defgroup  DSP2_MISC_OSD_PB_INPUT_TYPE
 *  @{
 */
#define IS_DSP2_MISC_OSD_PB_INPUT_TYPE(type)              (((type) == DSP2_MISC_OSD_PB_DSP2_OUTPUT) || \
                                                          ((type) == DSP2_MISC_OSD_PB_DSP2_INPUT))

/** @defgroup  DSP2_MISC_YUV2RGB_INPUT_TYPE
 *  @{
 */
#define IS_DSP2_MISC_YUV2RGB_INPUT_TYPE(type)             (((type) == DSP2_MISC_YUV2RGB_DSP2_OUTPUT) || \
                                                          ((type) == DSP2_MISC_YUV2RGB_DSP2_INPUT) || \
                                                          ((type) == DSP2_MISC_YUV2RGB_OSD_0_OUTPUT) || \
                                                          ((type) == DSP2_MISC_YUV2RGB_OSD_1_OUTPUT) || \
                                                          ((type) == DSP2_MISC_YUV2RGB_OSD_2_OUTPUT) || \
                                                          ((type) == DSP2_MISC_YUV2RGB_OSD_3_OUTPUT) || \
                                                          ((type) == DSP2_MISC_YUV2RGB_SCALER_0_OUTPUT) || \
                                                          ((type) == DSP2_MISC_YUV2RGB_SCALER_1_OUTPUT) || \
                                                          ((type) == DSP2_MISC_YUV2RGB_SCALER_2_OUTPUT) || \
                                                          ((type) == DSP2_MISC_YUV2RGB_SCALER_3_OUTPUT))

/** @defgroup  DSP2_MISC_BAYER_SHIFT_TYPE
 *  @{
 */
#define IS_DSP2_MISC_BAYER_SHIFT_TYPE(type)               (((type) == DSP2_MISC_BAYER_SHIFT_LEFT) || \
                                                          ((type) == DSP2_MISC_BAYER_SHIFT_RIGHT))

/** @defgroup  DSP2_MISC_INT_TYPE
 *  @{
 */
#define IS_DSP2_MISC_INT_TYPE(type) (((type) == DSP2_MISC_INT_AWB0) ||    \
                                    ((type) == DSP2_MISC_INT_AE) ||      \
                                    ((type) == DSP2_MISC_INT_WDR) ||     \
                                    ((type) == DSP2_MISC_INT_AWB1) ||    \
                                    ((type) == DSP2_MISC_INT_OSD_PB) ||  \
                                    ((type) == DSP2_MISC_INT_SEOF0) ||   \
                                    ((type) == DSP2_MISC_INT_SEOF1) ||   \
                                    ((type) == DSP2_MISC_INT_SEOF2) ||   \
                                    ((type) == DSP2_MISC_INT_AE_HIST) || \
                                    ((type) == DSP2_MISC_INT_AWB2) ||    \
                                    ((type) == DSP2_MISC_INT_DISPLAY) || \
                                    ((type) == DSP2_MISC_INT_SEOF3) ||   \
                                    ((type) == DSP2_MISC_INT_ALL))
/** @defgroup  DSP2_MISC_SEOF_SOURCE_TYPE
 *  @{
 */
#define IS_DSP2_MISC_SEOF_SOURCE_TYPE(type) (((type) == DSP2_MISC_SEOF_VSYNC_SENSOR) ||     \
                                            ((type) == DSP2_MISC_SEOF_VSYNC_DSP2_ACT) ||    \
                                            ((type) == DSP2_MISC_SEOF_VSYNC_DSP2_OUT) ||    \
                                            ((type) == DSP2_MISC_SEOF_VSYNC_DVP_TSRC) ||    \
                                            ((type) == DSP2_MISC_SEOF_DISPLAY_TEST_SRC) || \
                                            ((type) == DSP2_MISC_SEOF_DISPLAY_OUTPUT))




/** @defgroup  DSP2_MISC_SEOF_EDGE_TYPE
 *  @{
 */
#define IS_DSP2_MISC_SEOF_EDGE_TYPE(type)                 (((type) == DSP2_MISC_SEOF_VSYNC_NEGEDGE) || \
                                                          ((type) == DSP2_MISC_SEOF_VSYNC_POSEDGE))

/** @defgroup  DSP2_MISC_DISPLAY_INPUT_TYPE
 *  @{
 */
#define IS_DSP2_MISC_DISPLAY_INPUT_TYPE(type)             (((type) == DSP2_MISC_DISPLAY_YUV2RGB_OUTPUT) || \
                                                          ((type) == DSP2_MISC_DISPLAY_YUV422_OUTPUT))

/*@} end of group DSP2_MISC_Public_Constants */

/** @defgroup  DSP2_MISC_CROP_ID_TYPE
 *  @{
 */
#define IS_DSP2_MISC_CROP_ID_TYPE(type)                   (((type) == DSP2_MISC_CROP_0_ID) || \
                                                          ((type) == DSP2_MISC_CROP_1_ID) || \
                                                          ((type) == DSP2_MISC_CROP_2_ID) || \
                                                          ((type) == DSP2_MISC_CROP_3_ID) || \
                                                          ((type) == DSP2_MISC_CROP_ID_MAX))

/** @defgroup  DVP_DATA_ORDER_TYPE
 *  @{
 */
#define IS_DVP_DATA_ORDER_TYPE(type)                     (((type) == DSP2_MISC_2X_DATA_BYTE_LOWER) || \
                                                          ((type) == DSP2_MISC_2X_DATA_BYTE_HIGHER))

/** @defgroup  DVP_ACTIVE_LEVEL_TYPE
 *  @{
 */
#define IS_DVP_ACTIVE_LEVEL_TYPE(type)                   (((type) == DSP2_MISC_ACTIVE_HIGH) || \
                                                          ((type) == DSP2_MISC_ACTIVE_LOW))
void Display_IRQHandler(void);
void DSP2_MISC_Int_Callback_Install(DSP2_MISC_INT_Type intType, intCallback_Type *cbFun);
void DSP2_MISC_Int_Mask(DSP2_MISC_INT_Type intType, BL_Mask_Type intMask);
void DSP2_MISC_Int_Clear_1(DSP2_MISC_INT_Type intType);
void DSP2_MISC_SEOF_Set_Source(DSP2_MISC_INT_Type intType, DSP2_MISC_SEOF_Source_Type source);
void DSP2_MISC_SEOF_Set_Edge(DSP2_MISC_INT_Type intType, DSP2_MISC_SEOF_Edge_Type edge);
void DSP2_Misc_Config(DSP2_DVP_BIT_DEPTH_E dvp_bits);
void DSP2_DVP2AXI_Set_Src(DVP2AXI_Port_Type dvp2axi, DVP2AXI_Src_Type sel);
void DSP2_DVP2AXI_Get_Src(DVP2AXI_Port_Type dvp2axi, DVP2AXI_Src_Type *sel);
void DSP2_DVP2AXI_Set_Id_Sel(DVP2AXI_Port_Type dvp2axi, DVP2AXI_ID_E id);
void DSP2_DVP2AXI_Get_Id_Sel(DVP2AXI_Port_Type dvp2axi, DVP2AXI_ID_E *id);

void DSP2_MISC_TSRC_Source_Select(DSP2_MISC_TSRC_Source_Type sourceType);

void DSP2_Intr_Ctrl_Init(void);
void DSP2_Intr_Ctrl_Set_Src(DSP2_SEOF_E seof,DSP2_Seof_Intr_Src_Type selection);
void DSP2_Intr_Ctrl_Get_Src(DSP2_SEOF_E seof, DSP2_Seof_Intr_Src_Type *selection);
void DSP2_Intr_Clr(DSP2_INTR_SEL_E intr_sel);
void DSP2_Scaler_Set_State(DSP2_Scaler_Type type, BL_Fun_Type state);
void DSP2_Scaler_Set_Cfg(DSP2_Scaler_Type scaler, DSP2_SCALER_CONFIG_S *scaler_conf);
void DSP2_Frame_M_to_N(DSP2_FRAME_M_TO_N_S *cfg);
void DSP2_Frame_Get_M_to_N(DSP2_FRAME_M_TO_N_S *cfg);
void DSP2_Enable_BL_DSP2_Back(void);

void DSP2_YUV_Adjust_Init();
void DSP2_YUV_Adjust_Set_Cfg(DSP2_YUV_Adjust_Type id, DSP2_YUV_Adjust_Cfg_Type *cfg);
void DSP2_YUV_Adjust_Get_Cfg(DSP2_YUV_Adjust_Type id, DSP2_YUV_Adjust_Cfg_Type *cfg);
void DSP2_YUV_Adjust_Set_State(DSP2_YUV_Adjust_Type type, BL_Fun_Type state);
void DSP2_YUV_Adjust_Get_State(DSP2_YUV_Adjust_Type type, BL_Fun_Type *state);
void DSP2_YUV_Adjust_Set_Input(DSP2_YUV_Adjust_Type type, DSP2_YUV_Adjust_Input input);
void DSP2_YUV_Adjust_Get_Input(DSP2_YUV_Adjust_Type type, DSP2_YUV_Adjust_Input *input);

void DSP2_MISC_OSD_Input_Select(DSP2_MISC_OSD_ID_Type osdId,DSP2_MISC_OSD_Input_Type inputType);
void DSP2_MISC_OSD_Get_Input_Select(DSP2_MISC_OSD_ID_Type osdId,DSP2_MISC_OSD_Input_Type *inputType);
void DSP2_MISC_OSD_Pb_Input_Select(DSP2_MISC_OSD_PB_Input_Type inputType);
void DSP2_MISC_OSD_Pb_Get_Input_Select(DSP2_MISC_OSD_PB_Input_Type *inputType);
void DSP2_MISC_Bayer_Shift(uint16_t bitEnable,DSP2_MISC_Bayer_Shift_Type shiftType,uint8_t bitShift);

void DSP2_MISC_Scaler_Init(DSP2_MISC_Scaler_ID_Type scalerId,DSP2_MISC_Scaler_Cfg_Type* scalerCfg);
void DSP2_MISC_Scaler_Get_Cfg(DSP2_MISC_Scaler_ID_Type scalerId,DSP2_MISC_Scaler_Cfg_Type* scalerCfg);
void DSP2_MISC_Scaler_Input_Select(DSP2_MISC_Scaler_ID_Type scalerId,DSP2_MISC_Scaler_Input_Type inputType);
void DSP2_MISC_Scaler_Get_Input_Select(DSP2_MISC_Scaler_ID_Type scalerId,DSP2_MISC_Scaler_Input_Type *inputType);
void DSP2_MISC_Scaler_Enable(DSP2_MISC_Scaler_ID_Type scalerId);
void DSP2_MISC_Scaler_Disable(DSP2_MISC_Scaler_ID_Type scalerId);
void DSP2_MISC_Scaler_Get_State(DSP2_MISC_Scaler_ID_Type scalerId, BL_Fun_Type *state);
void DSP2_MISC_Scaler_Sh_Enable(DSP2_MISC_Scaler_ID_Type scalerId);
void DSP2_MISC_Scaler_Sh_Disable(DSP2_MISC_Scaler_ID_Type scalerId);

void DSP2_MISC_YUV2RGB_Init(DSP2_MISC_YUV2RGB_ID_Type yuv2rgbId,DSP2_MISC_YUV2RGB_Cfg_Type* yuv2rgbCfg);
void DSP2_MISC_YUV2RGB_Get_Cfg(DSP2_MISC_YUV2RGB_ID_Type yuv2rgbId,DSP2_MISC_YUV2RGB_Cfg_Type* yuv2rgbCfg);

void DSP2_MISC_CAM_Input_Select(DSP2_MISC_CAM_ID_Type camId,DSP2_MISC_CAM_Input_Type inputType);

void DSP2_MISC_Display_Init(DSP2_MISC_Display_Cfg_Type* displayCfg);
void DSP2_MISC_Display_Get_Cfg(DSP2_MISC_Display_Cfg_Type* displayCfg);
void DSP2_MISC_Display_Set_Clk_Output_Inv(int value);
void DSP2_MISC_Display_Get_Clk_Output_Inv(int *value);
void DSP2_MISC_Display_RGB2YUV_Set_Cfg(DSP2_MISC_RGB2YUV_Cfg_Type* rgb2yuvCfg);
void DSP2_MISC_Display_RGB2YUV_Get_Cfg(DSP2_MISC_RGB2YUV_Cfg_Type* rgb2yuvCfg);

void DSP2_Scaler_Set_Input(DSP2_Scaler_Type type, DSP2_Scaler_Input input);
void DSP2_Scaler_Get_Input(DSP2_Scaler_Type type, DSP2_Scaler_Input *input);
void DSP2_OSD_Set_Input(DSP2_OSD_Type type, DSP2_OSD_Input input);
void DSP2_OSD_Get_Input(DSP2_OSD_Type type, DSP2_OSD_Input *input);
void DSP2_YUV2RGB_Set_Input(DSP2_YUV2RGB_Type type, DSP2_YUV2RGB_Input input);
void DSP2_YUV2RGB_Get_Input(DSP2_YUV2RGB_Type type, DSP2_YUV2RGB_Input *input);
void DSP2_YUV2RGB_Init(DSP2_YUV2RGB_Param type);

void DSP2_MISC_Crop_Init(DSP2_MISC_Crop_ID_Type cropId,DSP2_MISC_Crop_Cfg_Type* cropCfg);
void DSP2_MISC_Crop_Get_Cfg(DSP2_MISC_Crop_ID_Type cropId, DSP2_MISC_Crop_Cfg_Type* cropCfg);
void DSP2_MISC_Crop_Enable(DSP2_MISC_Crop_ID_Type cropId);
void DSP2_MISC_Crop_Disable(DSP2_MISC_Crop_ID_Type cropId);
void DSP2_MISC_Crop_Get_State(DSP2_MISC_Crop_ID_Type cropId, BL_Fun_Type *state);
void DSP2_MSIC_DVP_2x_Init(DVP_2x_Cfg_Type* dvp2xCfg);
void DSP2_MSIC_DVP_2x_Get_Cfg(DVP_2x_Cfg_Type* dvp2xCfg);
void DSP2_MSIC_DVP_2x_Enable(void);
void DSP2_MSIC_DVP_2x_Disable(void);
void DSP2_MSIC_DVP_2x_Get_State(BL_Fun_Type *state);
void DSP2_MSIC_Pclk_Force_Set_State(BL_Fun_Type state);
void DSP2_MSIC_Pclk_Force_Get_State(BL_Fun_Type *state);
void DSP2_MSIC_Cr_De_As_Hsync_Set_State(BL_Fun_Type state);
void DSP2_MSIC_Cr_De_As_Hsync_Get_State(BL_Fun_Type *state);
void DSP2_MSIC_Dtsrc_Set_Mode(DSP2_DTSRC_SRC_E mode);
void DSP2_MSIC_Dtsrc_Get_Mode(DSP2_DTSRC_SRC_E *mode);

/* DVP reshape */
void DSP2_MISC_Reshape_Set_State(BL_Fun_Type state);
void DSP2_MISC_Reshape_Get_State(BL_Fun_Type *state);
void DSP2_MISC_Reshape_Counter_Clear();
void DSP2_MISC_Reshape_Set_Counter(int value);
void DSP2_MISC_Reshape_Get_Counter(int *value);
void DSP2_MISC_Reshape_Set_HSync_Inv(BL_Fun_Type state);
void DSP2_MISC_Reshape_Get_HSync_Inv(BL_Fun_Type *state);
void DSP2_MISC_Reshape_Set_VSync_Inv(BL_Fun_Type state);
void DSP2_MISC_Reshape_Get_VSync_Inv(BL_Fun_Type *state);

#endif //__BL808_DSP2_MISC_H__
