#ifndef __BL808_DSP2_H__
#define __BL808_DSP2_H__

#include "bl808_common.h"
#include "bl808_comm_mm.h"



#define DSP2_AWB2_STA_Y_NUM        (5)
#define DSP2_AWB2_STA_C_NUM        (8)
#define DSP2_AE_HIST_Y_BIN_NUM     (257)
#define DSP2_AE_HIST_BAYER_BIN_NUM (65)
#define DSP2_AWB3_WEIGHT_NUM       (9)
#define DSP2_AWB3_HIST_BIN_NUM_MAX (512)
#define DSP2_EE_LUMA_WEIGHT_NUM    (32)

#define AE_STATS_GRID_NUM_X   (12)
#define AE_STATS_GRID_NUM_Y   (8)
#define AE_STATS_GRID_NUM     ((AE_STATS_GRID_NUM_X)*(AE_STATS_GRID_NUM_Y))
#define AE_HIST_BIN_NUM       (256)
#define AE_METERING_TBL_NUM    (4)

/*
    DSP2 SYNC MODE
 */
typedef enum {
    DSP2_SYNC_MODE_INPUT = 0,
    DSP2_SYNC_MODE_OUTPUT,
    DSP2_SYNC_MODE_OUTPUT_INPUT,
    DSP2_SYNC_MODE_INPUT_VBLANK_NO_TOGGLE
}DSP2_SYNC_MODE_TYPE;


/*
    R,Gr,Gb,B black level
*/
typedef struct blDSP2_CLAMP_S {
    int clamp_r;
    int clamp_gr;
    int clamp_gb;
    int clamp_b;
} DSP2_CLAMP_S;

/*
    OB avg output R,Gr,Gb,B 
*/
typedef struct blDSP2_OB_S {
    int16_t ob_r;
    int16_t ob_gr;
    int16_t ob_gb;
    int16_t ob_b;
} DSP2_OB_S;

/*
    Color Correction Matrix Coefficient
*/
typedef enum {
    DSP2_CCM_11 = 0,
    DSP2_CCM_12 = 1,
    DSP2_CCM_13 = 2,
    DSP2_CCM_21 = 3,
    DSP2_CCM_22 = 4,
    DSP2_CCM_23 = 5,
    DSP2_CCM_31 = 6,
    DSP2_CCM_32 = 7,
    DSP2_CCM_33 = 8,
} DSP2_CCM_COEF_TYPE_E;
    
typedef enum {
    DSP2_CCM_OFFSET_0 = 0,
    DSP2_CCM_OFFSET_1 = 1,
    DSP2_CCM_OFFSET_2 = 2,
} DSP2_CCM_CFFSET_TYPE_E;

typedef struct blDSP2_CCM_OFFSET_GROUP_S
{
    int offset[CCM_OFFSET_NUM];
} DSP2_CCM_OFFSET_S;

typedef struct blDSP2_CCM_COEF_GROUP_S
{
    int ccm_coef[CCM_COEF_NUM];
} DSP2_CCM_COEF_S;

typedef struct blDSP2_GAMMA_COEF_GROUP_S{
    uint16_t curve_coef[GAMMA_COEF_NUM];
} DSP2_Gamma_Curve_Type;

/*
    YUV conversion mode
*/
typedef enum {
    DSP2_YUV_CONV_FULL_SCALE = 0,
    DSP2_YUV_CONV_BT601
}DSP2_YUV_CONV_TYPE;

typedef struct blDSP2_SATURATION_S
{
    uint32_t saturation_cb;
    uint32_t saturation_cr;
} DSP2_SATURATION_S;


/*
    Defect correction enhance state
*/
typedef enum {
    DSP2_DPC_Enhance1 = 0,
    DSP2_DPC_Enhance2,
    DSP2_DPC_Enhance3,
    DSP2_DPC_Enhance_Num  /* 3 */
}DSP2_DPC_ENHANCE_TYPE;

/*
    Defect correction enhance state group
*/
typedef struct {
    BL_Fun_Type data[DSP2_DPC_Enhance_Num];
}DSP2_DPC_ENHANCE_GROUP_TYPE;

/*
    Defect correction threadhold
*/
typedef enum {
    DSP2_DPC_th1 = 0,
    DSP2_DPC_th2,
    DSP2_DPC_th3,
    DSP2_DPC_th4,
    DSP2_DPC_th5,
    DSP2_DPC_th_Num /* 5 */
}DSP2_DPC_THRESHOLD_TYPE;

/*
    Defect correction threadhold group
*/
typedef struct {
    int data[DSP2_DPC_th_Num];
}DSP2_DPC_THRESHOLD_GROUP_TYPE;

/*
    Lens Shading Coef
    Acoef range: -4194304-4194303
    Bcoef range: -4096-4095
    Ccoef range: 0-255
    Dcoef range: -4194304-4194303
    Ecoef range: -4096-4095
    Gcoef range: -4194304-4194303
 */

typedef struct  {
    uint16_t th_base_r; // r/w, shadow, 10'b, range: 0 ~ (2 ^ TH_BW - 1)
    uint16_t th_base_g; // r/w, shadow, 10'b, range: 0 ~ (2 ^ TH_BW - 1)
    uint16_t th_base_b; // r/w, shadow, 10'b, range: 0 ~ (2 ^ TH_BW - 1)
    uint16_t th_slope_r; // r/w, shadow, 8'b, = TH_SLOPE_PRECISION, range: 0 ~ (2 ^ TH_SLOPE_PRECISION - 1)
    uint16_t th_slope_g; // r/w, shadow, 8'b, = TH_SLOPE_PRECISION, range: 0 ~ (2 ^ TH_SLOPE_PRECISION - 1)
    uint16_t th_slope_b; // r/w, shadow, 8'b, = TH_SLOPE_PRECISION, range: 0 ~ (2 ^ TH_SLOPE_PRECISION - 1)
    uint16_t slope_gain; // r/w, shadow, 6'b, = 2 + SLOPE_GAIN_PRECISION, 2.4 fixed-point, range: 0 ~ (2 ^ 6 - 1)
} DSP2_BNR_THRESHOLD_TYPE;

typedef struct  {
    uint16_t fb_lpf_weight; // r/w, shadow, 5'b, = 1 + LPF_WEIGHT_PRECISION, range: 0 ~ (2 ^ LPF_WEIGHT_PRECISION)
    uint16_t fb_level;   // r/w, shadow, 3'b, = FB_LEVEL_BW, range: 0 ~ (2 ^ FB_LEVEL_BW - 1)
} DSP2_BNR_FALLBACK_TYPE;

typedef struct {
    int coef[LSC_COEF_NUM];
}DSP2_LSC_COEF_TYPE;

typedef struct blDSP2_LSC_COEF_S {
    DSP2_LSC_COEF_TYPE lsc_coef_r;
    DSP2_LSC_COEF_TYPE lsc_coef_g;
    DSP2_LSC_COEF_TYPE lsc_coef_b;
} DSP2_LSC_COEF_S;

typedef struct blDSP2_LSC_MAX_S {
    int max_r;
    int max_g;
    int max_b;
} DSP2_LSC_MAX_S;

typedef enum {
    AE_GRID_DATA_RGB = 0,
    AE_GRID_DATA_Y = 1,
} AE_GRID_DATA_TYPE_E;

typedef enum {
    AWB_GRID_DATA_RG = 0,
    AWB_GRID_DATA_B = 1,
} AWB_GRID_DATA_TYPE_E;



typedef struct {
    DSP2_SYNC_MODE_TYPE      sync_mode_value;
    uint32_t                DSP2_clk;
    uint32_t                pix_clk;
    uint16_t                fps;
    uint16_t                total_width;
    uint16_t                total_height;
    uint16_t                active_width;
    uint16_t                active_height;
    uint16_t                out_width;
    uint16_t                out_height;
} DSP2_TG_Cfg_Type;

typedef struct {
    uint8_t                reg_act_vsync_rst_en;
    DSP2_SYNC_MODE_TYPE     sync_mode;
    uint8_t                hsync_in_inv;
    uint8_t                vsync_in_inv;
    uint8_t                hcnt_rst_mode;
    uint8_t                vcnt_rst_mode;
    uint8_t                hblk_line_on;
    uint8_t                fhblk_line_on;
} DSP2_DVP_MODE_CFG_T;

typedef struct _dsp2_ae_stats_conf {
    uint16_t            roi_start_x;
    uint16_t            roi_start_y;
    uint16_t            roi_width;
    uint16_t            roi_height;
    uint16_t            img_width;
    uint16_t            img_height;
    uint8_t             grid_width;
    uint8_t             grid_height;
    uint8_t             grid_num_x;
    uint8_t             grid_num_y;
} dsp2_ae_stats_conf_t;

typedef struct _dsp2_ae_sum {
    uint32_t            r_sum           :   8;
    uint32_t            g_sum           :   8;
    uint32_t            b_sum           :   8;
    uint32_t            reserved_24_31  :   8;
    uint32_t            y_sum           :   8;
    uint32_t            reserved_8_31   :   24;
} dsp2_ae_sum_t;

typedef enum {
    AE_HIST_MODE_BAYER = 0,
    AE_HIST_MODE_Y
} AE_HIST_MODE_TYPE_E;

typedef struct {
    uint16_t    ae_hist_x_min;
    uint16_t    ae_hist_x_max;
    uint16_t    ae_hist_y_min;
    uint16_t    ae_hist_y_max;
} dsp2_ae_hist_roi_t;

typedef struct _dsp2_awb_stats_conf {
    uint16_t            roi_start_x;
    uint16_t            roi_start_y;
    uint16_t            roi_width;
    uint16_t            roi_height;
    uint16_t            img_width;
    uint16_t            img_height;
    uint8_t             grid_width;
    uint8_t             grid_height;
    uint8_t             grid_num_x;
    uint8_t             grid_num_y;
    uint16_t            r_max_thr;
    uint16_t            r_min_thr;
    uint16_t            g_max_thr;
    uint16_t            g_min_thr;
    uint16_t            b_max_thr;
    uint16_t            b_min_thr;
} dsp2_awb_stats_conf_t;

typedef struct _dsp2_awb_sum{
    uint32_t r_sum          :  12;
    uint32_t reserved_12_15 :  4;
    uint32_t g_sum          :  12;
    uint32_t reserved_28_31 :  4;
    uint32_t b_sum          :  12;
    uint32_t reserved_12_31 :  20;
} dsp2_awb_sum_t;

typedef struct _dsp2_awb2_stats_conf {
    uint16_t    stat_x_min; // r/w, shadow, 11'b, range: 0 ~ (width - 1)
    uint16_t    stat_x_max; // r/w, shadow, 11'b, range: 0 ~ (width - 1)
    uint16_t    stat_y_min; // r/w, shadow, 11'b, range: 0 ~ (height - 1)
    uint16_t    stat_y_max; // r/w, shadow, 11'b, range: 0 ~ (height - 1)
    uint32_t    stat_pixel_num; // r/w, shadow, 21'b, = (stat_x_max - stat_x_min + 1) * (stat_y_max - stat_y_min + 1)
    uint16_t    stat_r_gain; // r/w, shadow, 16'b, = 4 + GAIN_PRECISION, 4.12 fixed-point, range: 0 ~ (2 ^ 16 - 1)
    uint16_t    stat_g_gain; // r/w, shadow, 16'b, = 4 + GAIN_PRECISION, 4.12 fixed-point, range: 0 ~ (2 ^ 16 - 1)
    uint16_t    stat_b_gain; // r/w, shadow, 16'b, = 4 + GAIN_PRECISION, 4.12 fixed-point, range: 0 ~ (2 ^ 16 - 1)
    uint16_t    stat_u_gain; // r/w, shadow, 10'b, = 2 + C_GAIN_PRECISION, 2.8 fixed-point, range: 0 ~ (2 ^ 10 - 1)
    uint16_t    stat_v_gain; // r/w, shadow, 10'b, = 2 + C_GAIN_PRECISION, 2.8 fixed-point, range: 0 ~ (2 ^ 10 - 1)
    uint16_t    reserved0;
    uint8_t     y_th[DSP2_AWB2_STA_Y_NUM]; // r/w, shadow, 8'b, = STAT_PIXEL_BW, range: 0 ~ (2 ^ 8 - 1)
    uint8_t     y_weight[DSP2_AWB2_STA_Y_NUM]; // r/w, shadow, 8'b, = STAT_PIXEL_BW, range: 0 ~ (2 ^ 8 - 1)
    uint16_t    reserved1;
    int16_t     y_slope[DSP2_AWB2_STA_Y_NUM]; // r/w, shadow, 9'b, = 7 + SLOPE_PRECISION, signed 2's complement, range: -256 ~ +255
    uint16_t    reserved2;
    int8_t      u[DSP2_AWB2_STA_C_NUM]; // r/w, shadow, 8'b, = STAT_PIXEL_BW, signed 2's complement, range: -128 ~ +127
    int8_t      v[DSP2_AWB2_STA_C_NUM]; // r/w, shadow, 8'b, = STAT_PIXEL_BW, signed 2's complement, range: -128 ~ +127
    uint8_t     c_th[DSP2_AWB2_STA_C_NUM]; // r/w, shadow, 6'b, = STAT_PIXEL_BW - 2, range: 0 ~ (2 ^ 6 - 1)
    uint8_t     c_slope[DSP2_AWB2_STA_C_NUM]; // r/w, shadow, 8'b, = 6 + SLOPE_PRECISION, range: 0 ~ (2 ^ 8 - 1)
} dsp2_awb2_stats_conf_t;

typedef struct _dsp2_awb2_sum{
    uint32_t r_avg; // r, ping-pong, 12'b, = PIXEL_BW
    uint32_t g_avg; // r, ping-pong, 12'b, = PIXEL_BW
    uint32_t b_avg; // r, ping-pong, 12'b, = PIXEL_BW
    uint64_t white_r_sum; // r, ping-pong, 41'b, = max. width * height in bit + WEIGHT_PRECISION + PIXEL_BW
    uint64_t white_g_sum; // r, ping-pong, 41'b, = max. width * height in bit + WEIGHT_PRECISION + PIXEL_BW
    uint64_t white_b_sum; // r, ping-pong, 41'b, = max. width * height in bit + WEIGHT_PRECISION + PIXEL_BW
    uint32_t white_ratio; // r, ping-pong, 15'b, = 1 + RATIO_PRECISION, 1.14 fixed-point
} dsp2_awb2_sum_t;

typedef struct _dsp2_awb3_stats_conf {
    // control register
    // int8_t stat_en; // r/w, shadow, 1'b
    uint16_t stat_x_min; // r/w, shadow, 11'b, range: 0 ~ (width - 1), must be even
    uint16_t stat_x_max; // r/w, shadow, 11'b, range: 0 ~ (width - 1), must be odd
    uint16_t stat_y_min; // r/w, shadow, 11'b, range: 0 ~ (height - 1)
    uint16_t stat_y_max; // r/w, shadow, 11'b, range: 0 ~ (height - 1)
    uint16_t r_ratio_ofst; // r/w, shadow, 12'b, = RATIO_BW, 4.8 fixed-point, range: 0 ~ (2 ^ 12 - 1)
    uint16_t b_ratio_ofst; // r/w, shadow, 12'b, = RATIO_BW, 4.8 fixed-point, range: 0 ~ (2 ^ 12 - 1)
    uint16_t r_ratio_mult; // r/w, shadow, 12'b, integer, range: 0 ~ (2 ^ 12 - 1)
    uint16_t b_ratio_mult; // r/w, shadow, 12'b, integer, range: 0 ~ (2 ^ 12 - 1)
    uint16_t ratio_sum_min;  // r/w, shadow, 9'b, = NORM_BW + 1, range: 0 ~ (2 ^ 9 - 1)
    uint16_t ratio_sum_max; // r/w, shadow, 9'b, = NORM_BW + 1, range: 0 ~ (2 ^ 9 - 1)
    uint8_t g_divisor; // r/w, shadow, 1'b
    uint8_t weight_ratio_en; // r/w, shadow, 1'b
    uint8_t weight_ratio_gain; // r/w, shadow, 8'b, = WEIGHT_GAIN_BW, 4.4 fixed-point, range: 0 ~ (2 ^ 8 - 1)
    uint8_t _pad1[1];
    uint8_t weight_ratio[DSP2_AWB3_WEIGHT_NUM][DSP2_AWB3_WEIGHT_NUM]; // r/w, shadow, 8'b, = WEIGHT_BW, range: 0 ~ (2 ^ 8 - 1)
    uint8_t _pad2[3];
    uint16_t y_r_coeff; // r/w, shadow, 12'b, = COEFF_BW, 4.8 fixed-point, range: 0 ~ (2 ^ 12 - 1)
    uint16_t y_g_coeff; // r/w, shadow, 12'b, = COEFF_BW, 4.8 fixed-point, range: 0 ~ (2 ^ 12 - 1)
    uint16_t y_b_coeff; // r/w, shadow, 12'b, = COEFF_BW, 4.8 fixed-point, range: 0 ~ (2 ^ 12 - 1)
    uint8_t weight_y_use_g; // r/w, shadow, 1'b
    uint8_t weight_y_en; // r/w, shadow, 1'b
    uint8_t weight_y_gain; // r/w, shadow, 8'b, = WEIGHT_GAIN_BW, 4.4 fixed-point, range: 0 ~ (2 ^ 8 - 1)
    uint8_t _pad3[3];
    uint8_t weight_y[DSP2_AWB3_WEIGHT_NUM][DSP2_AWB3_WEIGHT_NUM]; // r/w, shadow, 8'b, = WEIGHT_BW, range: 0 ~ (2 ^ 8 - 1)
    uint8_t count_zero_weight; // r/w, shadow, 1'b
    uint8_t hist_y_use_g; // r/w, shadow, 1'b
    int32_t bin_pixel_clip; // r/w, shadow, 20'b, = PIXEL_NUM_BW, range: 0 ~ (2 ^ 20 - 1)
    uint8_t bin_y_level; // r/w, shadow, 3'b, range: 0 ~ 7
    uint8_t bin_ratio_level; // r/w, shadow, 3'b, range: 0 ~ 4
    uint8_t bin_clip_en; // r/w, shadow, 1'b
    uint8_t bin_mode; // r/w, shadow, 2'b, range: 0 ~ 3
    uint8_t ink_type; // r/w, shadow, 2'b, range: 0 ~ 2
    uint8_t ink_gain; // r/w, shadow, 4'b, integer, range: 0 ~ (2 ^ 4 - 1)
} dsp2_awb3_stats_conf_t;

typedef struct _dsp2_awb3_sum{
    // status register
    uint32_t r_sum; // r, ping-pong, 32'b, = PIXEL_NUM_BW + PIXEL_BW
    uint32_t g_sum; // r, ping-pong, 32'b, = PIXEL_NUM_BW + PIXEL_BW
    uint32_t b_sum; // r, ping-pong, 32'b, = PIXEL_NUM_BW + PIXEL_BW
    uint32_t r_sum_hex; // r, ping-pong, 32'b, = PIXEL_NUM_BW + PIXEL_BW
    uint32_t g_sum_hex; // r, ping-pong, 32'b, = PIXEL_NUM_BW + PIXEL_BW
    uint32_t b_sum_hex; // r, ping-pong, 32'b, = PIXEL_NUM_BW + PIXEL_BW
    uint32_t pixel_hex; // r, ping-pong, 20'b, = PIXEL_NUM_BW
    uint64_t r_ratio_hex_y; // r, ping-pong, 40'b, = PIXEL_NUM_BW + WEIGHT_BW + RATIO_BW
    uint64_t b_ratio_hex_y; // r, ping-pong, 40'b, = PIXEL_NUM_BW + WEIGHT_BW + RATIO_BW
    uint32_t weight_hex_y; // r, ping-pong, 28'b, = PIXEL_NUM_BW + WEIGHT_BW
    uint32_t pixel_hex_y; // r, ping-pong, 20'b, = PIXEL_NUM_BW
    uint64_t r_ratio_hist; // r, ping-pong, 40'b, = PIXEL_NUM_BW + WEIGHT_BW + RATIO_BW
    uint64_t b_ratio_hist; // r, ping-pong, 40'b, = PIXEL_NUM_BW + WEIGHT_BW + RATIO_BW
    uint32_t weight_hist; // r, ping-pong, 28'b, = PIXEL_NUM_BW + WEIGHT_BW
    uint32_t pixel_hist; // r, ping-pong, 20'b, = PIXEL_NUM_BW
    uint64_t r_ratio_hist_clip; // r, ping-pong, 40'b, = PIXEL_NUM_BW + WEIGHT_BW + RATIO_BW
    uint64_t b_ratio_hist_clip; // r, ping-pong, 40'b, = PIXEL_NUM_BW + WEIGHT_BW + RATIO_BW
    uint32_t weight_hist_clip; // r, ping-pong, 28'b, = PIXEL_NUM_BW + WEIGHT_BW
    uint32_t pixel_hist_clip; // r, ping-pong, 20'b, = PIXEL_NUM_BW
} dsp2_awb3_sum_t;

typedef struct _dsp2_awb3_bucket{
    int32_t footprint[4];
} dsp2_awb3_bucket_t;

typedef enum {
    AWB3_BIN_MODE_FULL = 0,
    AWB3_BIN_MODE_RATIO,
    AWB3_BIN_MODE_Y,
    AWB3_BIN_MODE_NONE,
} dsp2_awb3_bin_mode_e;

typedef struct _dsp2_af_stats_conf{
    int16_t wa_hpf1_sum;
    int16_t wa_hpf2_sum;
    int16_t wb_hpf1_sum;
    int16_t wb_hpf2_sum;
} dsp2_af_stats_conf_t;

typedef struct {
    uint8_t  dirShpnessThresh;
    uint8_t  noDirShpnessThresh;
    uint8_t  flatThresh;
    uint16_t textureThresh;
    uint16_t edgeThresh;
} DSP2_EE_Thresh_Type;

typedef struct {
    uint8_t posEdgeOvrshtStr;
    uint8_t negEdgeOvrshtStr;
    uint8_t posEdgeStr;
    uint8_t negEdgeStr;
    uint8_t nrStr;
} DSP2_EE_Str_Type;

typedef struct {
    uint16_t lumaWgtTbl[DSP2_EE_LUMA_WEIGHT_NUM];
} DSP2_EE_Luma_Weight_Type;

typedef struct {
    uint16_t gain;
    uint8_t  weight;
    uint8_t  grey_thr;
} DSP2_Chroma_Suppress_Type;

typedef struct {
    uint16_t r_gain;
    uint16_t g_gain;
    uint16_t b_gain;
} DSP2_RGB_Gain_Type;

typedef struct {
    uint16_t r_offset;
    uint16_t g_offset;
    uint16_t b_offset;
} DSP2_RGB_Offset_Type;

typedef struct {
    uint16_t r_gain;
    uint16_t b_gain;
} DSP2_RB_Gain_Type;

typedef struct {
    uint8_t gamma_pattern;
    uint8_t fcore1;
    uint8_t fcore2;
} DSP2_AF_CONF_Type;

typedef struct {
    uint8_t start_x;
    uint8_t start_y;
    uint8_t end_x;
    uint8_t end_y;
    uint8_t sum_shift;
} DSP2_AF_WINDOW_Type;

#define IS_DSP2_YUV_CONV_TYPE(type)                      (((type) == DSP2_YUV_CONV_FULL_SCALE) || \
                                                          ((type) == DSP2_YUV_CONV_BT601))

void DSP2_Init(void);

void DSP2_Get_IP_Info(int *version, int *ip_id);
void DSP2_Set_TG_Cfg(const DSP2_TG_Cfg_Type *cfg);
void DSP2_Set_TG_Reshape_Cfg();

void DSP2_Set_DVP_Mode_Cfg(DSP2_DVP_MODE_CFG_T *cfg);
void DSP2_Get_DVP_Mode_Cfg(DSP2_DVP_MODE_CFG_T *cfg);
void DSP2_Set_Total_Pixels(BL_Img_Size_T *out_win);
void DSP2_Get_Total_Pixels(BL_Img_Size_T *out_win);
void DSP2_Set_Active_Pixels(int start_pixel, int start_line, BL_Img_Size_T *out_win);
void DSP2_Get_Active_Pixels(int *start_pixel, int *start_line, BL_Img_Size_T *out_win);
void DSP2_Set_Output_Pixels(int start_pixel, int start_line, BL_Img_Size_T *out_win);
void DSP2_Get_Output_Pixels(int *start_pixel, int *start_line, BL_Img_Size_T *out_win);
void DSP2_Set_Hsync_Pixels(int start_pixel, int start_line, BL_Img_Size_T *out_win);
void DSP2_Get_Hsync_Pixels(int *start_pixel, int *start_line, BL_Img_Size_T *out_win);
void DSP2_Set_Vsync_Pixels(int start_pixel, int start_line, int end_pixel, int line_height);
void DSP2_Get_Vsync_Pixels(int *start_pixel, int *start_line, int *end_pixel, int *line_height);
void DSP2_Set_Bayer_Pattern(const BAYER_PATTERN_E pattern);
void DSP2_Get_Bayer_Pattern(BAYER_PATTERN_E *pattern);

void DSP2_Set_AE_State(BL_Fun_Type state);
void DSP2_Set_AE_Stats_Conf(const dsp2_ae_stats_conf_t *ae_stats_conf);
void DSP2_Get_AE_Stats_Conf(dsp2_ae_stats_conf_t *ae_stats_conf);
void DSP2_Get_AE_Sum(int grid_idx, AE_GRID_DATA_TYPE_E data_type, uint32_t *data);
void DSP2_Set_AE_Ysum_Coeff(uint8_t coeff_r, uint8_t coeff_g, uint8_t coeff_b);
void DSP2_Get_AE_Ysum_Coeff(uint8_t *coeff_r, uint8_t *coeff_g, uint8_t *coeff_b);
int  DSP2_Get_AE_Stats(int grid_num, uint32_t *data);

void DSP2_Set_AE_Hist_State(BL_Fun_Type state);
int  DSP2_Get_AE_Hist_State(BL_Fun_Type *state);
void DSP2_Set_AE_Hist_Mode(AE_HIST_MODE_TYPE_E mode);
int  DSP2_Get_AE_Hist_Mode(AE_HIST_MODE_TYPE_E *mode);
void DSP2_Set_AE_Hist_ROI_State(BL_Fun_Type state);
int  DSP2_Get_AE_Hist_ROI_State(BL_Fun_Type *state);
int  DSP2_Set_AE_Hist_ROI(BL_Fun_Type state, const dsp2_ae_hist_roi_t *roi);
int  DSP2_Get_AE_Hist_ROI(BL_Fun_Type state, dsp2_ae_hist_roi_t *roi);
int  DSP2_Get_AE_Hist_SUM_Y(uint32_t *y_sum);
int  DSP2_Get_AE_Hist_SUM_Bayer(uint32_t *r_sum, uint32_t *gr_sum, uint32_t *gb_sum, uint32_t *b_sum);

void DSP2_Set_AWB_State(BL_Fun_Type state);
int  DSP2_Get_AWB_Stats(int grid_num, uint32_t *data);
void DSP2_Set_AWB_Stats_Conf(const dsp2_awb_stats_conf_t *awb_stats_conf);
void DSP2_Get_AWB_Stats_Conf(dsp2_awb_stats_conf_t *awb_stats_conf);
void DSP2_Get_AWB_Sum(int grid_idx, RGB_SUM_S *rgb_sum);
void DSP2_Get_AWB_ValidGridNum(int *valid_grid_num);

void DSP2_Set_AWB_Gain(const DSP2_RGB_Gain_Type* rgb_gain);
void DSP2_Get_AWB_Gain(DSP2_RGB_Gain_Type *rgb_gain);
void DSP2_Set_AWB_Offset(const DSP2_RGB_Offset_Type *Offset);
void DSP2_Get_AWB_Offset(DSP2_RGB_Offset_Type *Offset);
void DSP2_Set_RB_Gain(const DSP2_RB_Gain_Type *rb_gain);

void DSP2_Set_AWB2_Stats_State(BL_Fun_Type state);
void DSP2_Set_AWB2_Stats_Conf(const dsp2_awb2_stats_conf_t *awb_stats_conf);
int  DSP2_Get_AWB2_Sum(dsp2_awb2_sum_t *sum);
void DSP2_Set_AWB2_Gain_State(BL_Fun_Type state);
void DSP2_Set_AWB2_Gain(const DSP2_RGB_Gain_Type *gain);
void DSP2_Get_AWB2_Gain(DSP2_RGB_Gain_Type *rgb_gain);

void DSP2_Set_AWB3_Hist_State(BL_Fun_Type state);
void DSP2_Get_AWB3_Hist_State(BL_Fun_Type *state);
void DSP2_Set_AWB3_Stats_Conf(const dsp2_awb3_stats_conf_t *awb_stats_conf);
void DSP2_Get_AWB3_Stats_Conf(dsp2_awb3_stats_conf_t *awb_stats_conf);
int  DSP2_Get_AWB3_Sum(dsp2_awb3_sum_t *sum);
int  DSP2_Get_AWB3_Bin_Mode(dsp2_awb3_bin_mode_e *mode);
void DSP2_Set_AWB3_Bin_Mode(dsp2_awb3_bin_mode_e mode);
int  DSP2_Get_AWB3_Hist_Bin_Num(uint32_t *num);
int  DSP2_Get_AWB3_Hist(uint32_t *data);
int  DSP2_Get_AWB3_G_Divisor(int *value);
void DSP2_Set_AWB3_G_Divisor(int value);

int  DSP2_Set_Output_Window(BL_Img_Size_T *out_win);
int  DSP2_Get_Output_Window(BL_Img_Size_T *out_win);
void DSP2_Set_BL444to422(int mode);
void DSP2_Get_BL444to422(int *mode);


/*
    Set R/G/B BLC
    value range:
        0-1023
 */
int DSP2_Set_BLC(const DSP2_CLAMP_S *clamp);
int DSP2_Get_BLC(DSP2_CLAMP_S *clamp);
int DSP2_Get_OB_Avg(DSP2_OB_S *ob);

void DSP2_Set_DPC_State(BL_Fun_Type state);
void DSP2_Get_DPC_State(BL_Fun_Type *state);
void DSP2_Enable_DPC(void);
void DSP2_Disable_DPC(void);
int  DSP2_Set_Defect_Correction_Enhance_Group(const DSP2_DPC_ENHANCE_GROUP_TYPE *value);
int  DSP2_Get_Defect_Correction_Enhance_Group(DSP2_DPC_ENHANCE_GROUP_TYPE *value);
int  DSP2_Set_Defect_Correction_Threshold_Group(const DSP2_DPC_THRESHOLD_GROUP_TYPE *value);
int  DSP2_Get_Defect_Correction_Threshold_Group(DSP2_DPC_THRESHOLD_GROUP_TYPE *value);
int  DSP2_Set_Defect_Postion(const int pos_x, const int pos_y);
int  DSP2_Get_Defect_Postion(int *pos_x, int *pos_y);

void DSP2_Set_BNR_State(BL_Fun_Type state);
void DSP2_Get_BNR_State(BL_Fun_Type *state);
void DSP2_Set_BNR_Weight(int value);
void DSP2_Get_BNR_Weight(int *value);
void DSP2_Set_BNR_LPF_Weight(int value);
void DSP2_Get_BNR_LPF_Weight(int *value);
void DSP2_Set_BNR_Threshold(const DSP2_BNR_THRESHOLD_TYPE *value);
void DSP2_Get_BNR_Threshold(DSP2_BNR_THRESHOLD_TYPE *value);
void DSP2_Set_BNR_Fallback(const DSP2_BNR_FALLBACK_TYPE *value);
void DSP2_Get_BNR_Fallback(DSP2_BNR_FALLBACK_TYPE *value);

void DSP2_Set_Brightness(int value);
void DSP2_Get_Brightness(int *value);

void DSP2_Set_LSC_State(BL_Fun_Type state);
void DSP2_Enable_LSC(void);
void DSP2_Disable_LSC(void);
void DSP2_Get_LSC_State(BL_Fun_Type *state);
/*
    Set Lens Shading Correction offset
*/
int DSP2_Set_LSC_Offset(int xoffset, int yoffset);
int DSP2_Get_LSC_Offset(int *xoffset, int *yoffset);

/*
    Set/Get Lens Shading Correction setting
    value range: please see DSP2_LSC_COEF_S
*/
int DSP2_Set_LSC_Coeff(const DSP2_LSC_COEF_S *lsc);
int DSP2_Get_LSC_Coeff(DSP2_LSC_COEF_S *lsc);
int DSP2_Set_LSC_Coeff_Type(const int type_idx, DSP2_LSC_COEF_TYPE *lsc);
int DSP2_Get_LSC_Coeff_Type(const int type_idx, DSP2_LSC_COEF_TYPE *lsc);

/*
    Set/Get Lens Shading Correction R,G,B MAX
    value range: 0-255 (refs to demo app)
*/
int DSP2_Set_LSC_Max(const DSP2_LSC_MAX_S *lsc_max);
int DSP2_Get_LSC_Max(DSP2_LSC_MAX_S *lsc_max);

void DSP2_Set_Digital_Gain(int r_gain, int gr_gain, int gb_gain, int b_gain);
void DSP2_Get_Digital_Gain(int *r_gain, int *gr_gain, int *gb_gain, int *b_gain);

void DSP2_Set_CFA_Int_State(BL_Fun_Type state);
void DSP2_Get_CFA_Int_State(BL_Fun_Type *state);

void DSP2_Set_CCM_State(BL_Fun_Type state);
void DSP2_Get_CCM_State(BL_Fun_Type *state);

/*
    Set/Get Color Correction Matrix Coefficient Value
    value range: 0-4095, 512 normalize to 1
 */
void  DSP2_Set_CCM_Coef(const DSP2_CCM_COEF_S *ccm);
void  DSP2_Get_CCM_Coef(DSP2_CCM_COEF_S *ccm);
void DSP2_Set_CCM_Pre_Offset(const DSP2_CCM_OFFSET_S *ccm);
void DSP2_Get_CCM_Pre_Offset(DSP2_CCM_OFFSET_S *ccm);
void DSP2_Set_CCM_Post_Offset(const DSP2_CCM_OFFSET_S *ccm);
void DSP2_Get_CCM_Post_Offset(DSP2_CCM_OFFSET_S *ccm);


void DSP2_Set_Gamma_State(BL_Fun_Type state);
void DSP2_Get_Gamma_State(BL_Fun_Type *state);

/*
    Set/Get Gamma
    value range: 0-4095
 */
void DSP2_Set_Gamma_Coef(const DSP2_Gamma_Curve_Type *gamma_curve);
void DSP2_Get_Gamma_Coef(DSP2_Gamma_Curve_Type *gamma_curve);


void DSP2_Init_Color_Enhancement();
/*
    Set/Get YUV Conversion mode
    @ deprecated
    if you want to change the yuv range, please set yuv adjust
 */
void DSP2_Set_YUV_Conv_Mode(DSP2_YUV_CONV_TYPE  type);
void DSP2_Get_YUV_Conv_Mode(DSP2_YUV_CONV_TYPE *type);


/*
    Set/Get Brightness
    value range: TODO  -128-127
 */
void DSP2_Set_Brightness(int value);
void DSP2_Get_Brightness(int *value);

/*
    Set/Get Contrast
    value range: TODO 0-255
*/
void DSP2_Set_Contrast(int value);
void DSP2_Get_Contrast(int *value);

/*
    Set/Get Saturation
    value range:TODO  0-255
*/
void DSP2_Set_Saturation(const DSP2_SATURATION_S *saturation);
void DSP2_Get_Saturation(DSP2_SATURATION_S *saturation);

void DSP2_Set_Special_Mode(int value);
void DSP2_Get_Special_Mode(int *value);
void DSP2_Set_LPF_Filting_Mode(int value);
void DSP2_Get_LPF_Filting_Mode(int *value);
void DSP2_Set_Sepia(int SepiaCr, int SepiaCb);
void DSP2_Get_Sepia(int *SepiaCr, int *SepiaCb);
void DSP2_Set_Solar_Thred(int value);
void DSP2_Get_Solar_Thred(int *value);

/*
    Set/Get Noise Level
    value range: 0-63
*/
void DSP2_Set_Noise_Level(int value);
void DSP2_Get_Noise_Level(int *value);

/*
    Set/Get 2D Noise Reduction
    value range: 0-31
*/
void DSP2_Set_2D_NR(int value);
void DSP2_Get_2D_NR(int *value);

/*
    Set/Get 3D Noise Reduction
    value range: 0-31
*/
void DSP2_Set_3D_NR(int value);
void DSP2_Get_3D_NR(int *value);
void DSP2_Set_NR_HSize(const int value);
void DSP2_Get_NR_HSize(int *value);

void DSP2_Set_EE_State(BL_Fun_Type state);
void DSP2_Get_EE_State(BL_Fun_Type *state);
void DSP2_Enable_EE(void);
void DSP2_Disable_EE(void);
void DSP2_EnableEEOverShoot(void);
void DSP2_DisableEEOverShoot(void);
void DSP2_Set_EEOverShoot_State(BL_Fun_Type state);
void DSP2_Get_EEOverShoot_State(BL_Fun_Type *state);
void DSP2_Set_EE_Thresh(const DSP2_EE_Thresh_Type *threshCfg);
void DSP2_Get_EE_Thresh(DSP2_EE_Thresh_Type *threshCfg);
void DSP2_Set_EE_Strength(const DSP2_EE_Str_Type *strCfg);
void DSP2_Get_EE_Strength(DSP2_EE_Str_Type *strCfg);
void DSP2_Set_EE_LumaWeight(const DSP2_EE_Luma_Weight_Type *lumaWgtCfg);
void DSP2_Get_EE_LumaWeight(DSP2_EE_Luma_Weight_Type *lumaWgtCfg);

void DSP2_Set_ChromaSuppress_State(BL_Fun_Type state);
void DSP2_Get_ChromaSuppress_State(BL_Fun_Type *state);
void DSP2_Enable_ChromaSuppress(void);
void DSP2_Disable_ChromaSuppress(void);

void DSP2_Set_ChromaSuppress(const DSP2_Chroma_Suppress_Type *chromaSupprCfg);
void DSP2_Get_ChromaSuppress(DSP2_Chroma_Suppress_Type *chromaSupprCfg);

void DSP2_Get_AF_Stats(dsp2_af_stats_conf_t *afStats);
void DSP2_Set_AF_Stats_Conf(const DSP2_AF_CONF_Type *afCfg);
void DSP2_Get_AF_Stats_Conf(DSP2_AF_CONF_Type *afCfg);
void DSP2_Set_AF_Window_A(const DSP2_AF_WINDOW_Type *afWinCfg);
void DSP2_Get_AF_Window_A(DSP2_AF_WINDOW_Type *afWinCfg);
void DSP2_Set_AF_Window_B(const DSP2_AF_WINDOW_Type *afWinCfg);
void DSP2_Get_AF_Window_B(DSP2_AF_WINDOW_Type *afWinCfg);

#endif  /* __BL808_DSP2_H__ */
