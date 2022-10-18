#ifndef __BL_DSP2_H__
#define __BL_DSP2_H__

#include <bl808.h>
#include <bl808_dsp2.h>
#include <bl808_dsp2_wdr.h>
#include <bl808_dvp2axi.h>
#include <bl808_dvp_tsrc.h>
#include <bl808_csi.h>
#include "bl_comm_sns.h"
#include "bl_img_utils.h"

#define DUMP_PORT_NUM    2

typedef enum
{
    BL_SYS_MODE_SENSOR = 0,
    BL_SYS_MODE_RAW_FILE_720P = 1,
    BL_SYS_MODE_RAW_FILE_1080P = 2,
    BL_SYS_MODE_RAW_FILE_UXGA = 3,
    BL_SYS_MODE_IDLE = 5,
    BL_SYS_MODE_NUM,
} SYS_MODE_E;


typedef enum {
    BL_BAYER_PATTERN_RG = 0,
    BL_BAYER_PATTERN_GR,
    BL_BAYER_PATTERN_BG,
    BL_BAYER_PATTERN_GB,
} BL_DSP2_BAYER_PATTERN_T;

typedef enum {
    BL_DSP2_INPUT_FRAME_VALID_LOW = 0,
    BL_DSP2_INPUT_FRAME_VALID_HIGH = 1,
} BL_DSP2_INPUT_FRAME_POLARIT_T;

typedef enum {
    BL_IMAGE_DUMP_SRC_DSP2_INPUT              = 0,
    BL_IMAGE_DUMP_SRC_ACT                    = 0x1,
    BL_IMAGE_DUMP_SRC_DEFECT                 = 0x2,
    BL_IMAGE_DUMP_SRC_COLOR_CORRECTION_R     = 0x3,
    BL_IMAGE_DUMP_SRC_COLOR_CORRECTION_G     = 0x4,
    BL_IMAGE_DUMP_SRC_COLOR_CORRECTION_B     = 0x5,
    BL_IMAGE_DUMP_SRC_GAMMA_CORRECTION_R     = 0x6,
    BL_IMAGE_DUMP_SRC_GAMMA_CORRECTION_G     = 0x7,
    BL_IMAGE_DUMP_SRC_RGB2YUV_CB_Y           = 0x8,
    BL_IMAGE_DUMP_SRC_RGB2YUV_0_CR           = 0x9,
    BL_IMAGE_DUMP_SRC_NOISE_REDUCTION        = 0xa,
    BL_IMAGE_DUMP_SRC_EDGE_ENHANCEMENT_OUT   = 0xb,
    BL_IMAGE_DUMP_SRC_DSP2_OUTPUT             = 0xc,
    BL_IMAGE_DUMP_SRC_OSD_A                  = 0xd,
    BL_IMAGE_DUMP_SRC_OSD_B                  = 0xe,
    BL_IMAGE_DUMP_SRC_OSD_C                  = 0xf,
    BL_IMAGE_DUMP_SRC_OSD_D                  = 0x10,
    BL_IMAGE_DUMP_SRC_SCALER_A               = 0x11,
    BL_IMAGE_DUMP_SRC_SCALER_B               = 0x12,
    BL_IMAGE_DUMP_SRC_SCALER_C               = 0x13,
    BL_IMAGE_DUMP_SRC_SCALER_D               = 0x14,
    BL_IMAGE_DUMP_SRC_ADJ_A                  = 0x15,
    BL_IMAGE_DUMP_SRC_ADJ_B                  = 0x16,
    BL_IMAGE_DUMP_SRC_ADJ_C                  = 0x17,
    BL_IMAGE_DUMP_SRC_ADJ_D                  = 0x18,
    BL_IMAGE_DUMP_SRC_YUV420_A               = 0x19,
    BL_IMAGE_DUMP_SRC_YUV420_B               = 0x1a,
    BL_IMAGE_DUMP_SRC_YUV420_C               = 0x1b,
    BL_IMAGE_DUMP_SRC_YUV420_D               = 0x1c,
    BL_IMAGE_DUMP_SRC_GAMMA_CORRECTION_B     = 0x1d,
    BL_IMAGE_DUMP_SRC_WDR_R                  = 0x1e,
    BL_IMAGE_DUMP_SRC_WDR_G                  = 0x1f,
    BL_IMAGE_DUMP_SRC_WDR_B                  = 0x20,
    BL_IMAGE_DUMP_SRC_LSC                    = 0x21,
    BL_IMAGE_DUMP_SRC_AWB3                   = 0x22,
    BL_IMAGE_DUMP_SRC_YUV2RGB                = 0x23,
} BL_DSP2_IMAGE_DUMP_SRC_T;

typedef enum {
    BL_DAY_MODE = 0,
    BL_NIGHT_MODE = 1,
} BL_DSP2_DAY_NIGHT_MODE_T;

typedef enum {
    BL_DUMP_PORT_MODE_SENSOR = 0,
    BL_DUMP_PORT_MODE_DSP2,
    BL_DUMP_PORT_MODE_DSP2_Y,
    BL_DUMP_PORT_MODE_DSP2_UV,
    BL_DUMP_PORT_MODE_DSP2_Y_DUAL_ENC,
    BL_DUMP_PORT_MODE_DSP2_UV_DUAL_ENC,
    BL_DUMP_PORT_MODE_DSP2_Y_DIRECT_LINK,
    BL_DUMP_PORT_MODE_DSP2_UV_DIRECT_LINK,
    BL_DUMP_PORT_MODE_HDMI,
    BL_DUMP_PORT_MODE_INVALID,
} DBG_DUMP_PORT_MODE_E;

typedef enum {
    // yuv domain use only
    IMAGE_PLANE_YUV,
    IMAGE_PLANE_Y_ONLY,
    IMAGE_PLANE_UV_ONLY,
    // all domain
    IMAGE_PLANE_8BIT,
    IMAGE_PLANE_16BIT,
    IMAGE_PLANE_24_EXP_32BIT,
    IMAGE_PLANE_NONE,
} BL_DSP2_IMAGE_PLANE_T;

typedef enum {
    DSP2_MISC_SCALER_A,
    DSP2_MISC_SCALER_B,
    DSP2_MISC_SCALER_C,
    DSP2_MISC_SCALER_D,
} BL_DSP2_SCALER_TYPE_T;

typedef enum {
    BL_DSP2_AF_WIN_A = 0,
    BL_DSP2_AF_WIN_B,
    BL_DSP2_AF_WIN_NUM,
} BL_DSP2_AF_WIN_IDX_T;

typedef struct
{
    uint32_t pix_clk;
    uint32_t dsp2_clk;
    BL_Img_Size_T total_win;
    BL_Img_Size_T act_win;
    BL_Img_Size_T out_win;
    uint8_t bit_depth;
    uint8_t is_hsync_toggle_in_vblank;
    BAYER_PATTERN_E bayer_pattern;
    char sensor_name[12];
    uint8_t is_virtual;
    uint8_t fps;
} bl_vin_config_t;

typedef struct {
    uint8_t *y_frame_base_addr;
    uint32_t y_frame_size;
    uint8_t *uv_frame_base_addr;
    uint32_t uv_frame_size;
} bl_dsp2_output_buffer_t;

typedef struct {
    DVP2AXI_Port_Type   port;
    uint32_t            chann_id;
    uint8_t            *frame_start_addr;
    uint32_t            frame_size;
} bl_dsp2_frame_desc_t;

typedef struct {
    uint8_t *buf_base_addr;
    uint32_t buf_size;
    uint32_t frame_size;
    BL_Img_Size_T win;
} bl_dsp2_dump_cfg_t;

typedef struct {
    uint32_t y[DSP2_AE_HIST_Y_BIN_NUM];
} bl_dsp2_ae_hist_y_t;

typedef struct {
    uint32_t r[DSP2_AE_HIST_BAYER_BIN_NUM];
    uint32_t gr[DSP2_AE_HIST_BAYER_BIN_NUM];
    uint32_t gb[DSP2_AE_HIST_BAYER_BIN_NUM];
    uint32_t b[DSP2_AE_HIST_BAYER_BIN_NUM];
} bl_dsp2_ae_hist_bayer_t;

typedef struct {
    uint8_t r_sum[AE_STATS_GRID_NUM];
    uint8_t g_sum[AE_STATS_GRID_NUM];
    uint8_t b_sum[AE_STATS_GRID_NUM];
    uint8_t y_sum[AE_STATS_GRID_NUM];
} bl_dsp2_ae_grid_sum_t;

typedef struct {
    uint16_t            img_width;
    uint16_t            img_height;
    uint8_t             grid_num_x;
    uint8_t             grid_num_y;
} bl_dsp2_ae_stats_conf_t;

typedef struct {
    uint64_t r_ratio[DSP2_AWB3_HIST_BIN_NUM_MAX];
    uint64_t b_ratio[DSP2_AWB3_HIST_BIN_NUM_MAX];
    uint32_t weight[DSP2_AWB3_HIST_BIN_NUM_MAX];
    uint32_t pixel[DSP2_AWB3_HIST_BIN_NUM_MAX];
} bl_dsp2_awb3_stats_hist_t;

typedef struct {
    uint16_t r_gain;
    uint16_t g_gain;
    uint16_t b_gain;
} bl_dsp2_rgb_gain_t;

typedef struct {
    uint16_t r_gain;
    uint16_t b_gain;
} bl_dsp2_rb_gain_t;

typedef struct {
    uint16_t r_gain;
    uint16_t gr_gain;
    uint16_t gb_gain;
    uint16_t b_gain;
} bl_dsp2_bayer_gain_t;

typedef struct {
    uint16_t gain;
    uint8_t  weight;
    uint8_t  grey_thr;
} bl_dsp2_cs_conf_t;

typedef struct {
    int cs_en;
    int curve_en;
    int enh_en;
} bl_dsp2_wdr_sub_state_t;

typedef struct {
    int id;
    int state;
    int weight;
    int x_start;
    int x_end;
    int y_start;
    int y_end;
} bl_dsp2_wdr_roi_info_t;

typedef struct {
    uint32_t hist_bin[DSP2_WDR_HIST_BIN_NUM];
} bl_dsp2_wdr_hist_data_t;

typedef struct {
    uint16_t coef[DSP2_WDR_CURVE_COEF_NUM];
} bl_dsp2_wdr_curve_t;

typedef struct {
    int weight;
    int y_offset;
    int y_gain;
    int c_gain;
} bl_dsp2_wdr_enh_t;

typedef struct  {
    uint16_t th_base_r;
    uint16_t th_base_g;
    uint16_t th_base_b;
    uint16_t th_slope_r;
    uint16_t th_slope_g;
    uint16_t th_slope_b;
    uint16_t slope_gain;
} bl_dsp2_bnr_thr_t;

typedef struct  {
    uint16_t fb_lpf_weight;
    uint16_t fb_level;
} bl_dsp2_bnr_fb_t;

typedef struct {
    int thr_1;
    int thr_2;
} bl_dsp2_dpc_thr_t;

typedef struct {
    int coef[LSC_COEF_NUM];
} bl_dsp2_lsc_coef_t;

typedef struct {
    bl_dsp2_lsc_coef_t r;
    bl_dsp2_lsc_coef_t g;
    bl_dsp2_lsc_coef_t b;
} bl_dsp2_lsc_coef_s;

typedef struct {
    int max_r;
    int max_g;
    int max_b;
} bl_dsp2_lsc_max_s;

typedef struct {
    bl_dsp2_lsc_coef_s coef;
    bl_dsp2_lsc_max_s max;
} bl_dsp2_lsc_conf_t;

typedef struct {
    uint8_t  dirShpnessThresh;
    uint8_t  noDirShpnessThresh;
    uint8_t  flatThresh;
    uint16_t textureThresh;
    uint16_t edgeThresh;
} bl_dsp2_ee_thr_t;

typedef struct {
    uint8_t posEdgeOvrshtStr;
    uint8_t negEdgeOvrshtStr;
    uint8_t posEdgeStr;
    uint8_t negEdgeStr;
    uint8_t nrStr;
} bl_dsp2_ee_str_t;

typedef struct {
    int over_sht_state;
    bl_dsp2_ee_thr_t thr;
    bl_dsp2_ee_str_t str;
} bl_dsp2_ee_conf_t;

typedef struct {
    uint16_t lumaWgtTbl[DSP2_EE_LUMA_WEIGHT_NUM];
} bl_dsp2_ee_luma_weight_t;

typedef struct {
    int coef[CCM_COEF_NUM];
} bl_dsp2_ccm_coef_s;

typedef struct {
    uint16_t coef[GAMMA_COEF_NUM];
} bl_dsp2_gamma_curve_t;

typedef struct {
    uint16_t noise_level;
    uint8_t  filt_str_2d;
    uint8_t  filt_str_3d;
} bl_dsp2_nr_conf_t;

typedef struct {
    uint8_t  brightness;
    uint8_t  contrast;
} bl_dsp2_yc_conf_t;

typedef struct {
    int16_t wa_hpf1_sum;
    int16_t wa_hpf2_sum;
    int16_t wb_hpf1_sum;
    int16_t wb_hpf2_sum;
} bl_dsp2_af_stats_t;

typedef struct {
    uint8_t gamma_pattern;
    uint8_t fcore1;
    uint8_t fcore2;
} bl_dsp2_af_conf_t;

typedef struct {
    uint8_t start_x;
    uint8_t start_y;
    uint8_t end_x;
    uint8_t end_y;
    uint8_t sum_shift;
} bl_dsp2_af_win_t;

typedef struct {
    uint16_t start_x;
    uint16_t start_y;
    uint16_t end_x;
    uint16_t end_y;
} bl_dsp2_crop_roi_t;


#define IS_DSP2_DVP_TSRC(dvp_tsrc)       (DVP_TSRC_DSP2 == dvp_tsrc)
#define IS_HDMI_DVP_TSRC(dvp_tsrc)      (DVP_TSRC_HDMI == dvp_tsrc)

typedef void (*bl_dsp2_stats_ready_cb)(void *usrdata);
typedef void (*bl_dsp2_frame_ready_cb)(void *usrdata, bl_dsp2_frame_desc_t *frame);
typedef void (* bl_dsp2_update_fps_cb)(int chn_id, uint32_t fps);


void bl_dsp2_scaler_path_dvp2x(BL_DSP2_SCALER_TYPE_T scaler);
void bl_dsp2_osd_path_init(void);
void bl_dsp2_misc_init();
void bl_dsp2_sys_init();
void bl_dsp2_datapath_init();
int bl_dsp2_cfg_init(bl_vin_config_t *cfg);
void bl_dsp2_tg_init(bl_vin_config_t *cfg);
int bl_dsp2_awb_gain_init();

int bl_dsp2_set_input_resolution(BL_Img_Size_T *win);
int bl_dsp2_set_input_total_window(BL_Img_Size_T *win);
int bl_dsp2_get_input_resolution(BL_Img_Size_T *win);
int bl_dsp2_get_out_resolution(BL_Img_Size_T *win);

int bl_dsp2_set_crop_roi(int channID, bl_dsp2_crop_roi_t *win);
int bl_dsp2_get_crop_roi(int channID, bl_dsp2_crop_roi_t *win);
int bl_dsp2_set_scaler_resolution(int chann_id, BL_Img_Size_T *win);
int bl_dsp2_get_scaler_resolution(int chann_id, BL_Img_Size_T *win);
int bl_dsp2_set_yuv_adj_state(int channID, BL_Fun_Type state);

int bl_dsp2_enable_dump_chann(int channID, BL_DSP2_IMAGE_DUMP_SRC_T src, BL_DSP2_IMAGE_PLANE_T image_plane,
                                bl_dsp2_dump_cfg_t *dump_cfg);
int bl_dsp2_disable_dump_chann(int channID);
int bl_dsp2_resume_dump_chann(int channID);
int bl_dsp2_enable_hdmi_port(int channID, uint8_t *dualBufAddr, uint32_t dualBufSize);
int bl_dsp2_disable_hdmi_port(int channID);

int bl_dsp2_enable_ouput_channel(int channID);
int bl_dsp2_disable_output_channel(int channID);

int bl_dsp2_set_ouput_buffer(int channID, bl_dsp2_output_buffer_t *outBuf, BL_Fun_Type sw_mode);

int bl_dsp2_set_channel_frame_rate(int channID, uint32_t snsFrmRate,
                                    uint32_t outFrmRateNum, uint32_t outFrmRateDen);

int bl_dsp2_enable_3dnr(BL_Img_Size_T *win);
int bl_dsp2_disable_3dnr(void);
void bl_dsp2_get_3dnr_refFrameBuf(uint32_t *bufAddr, uint32_t *bufSize);

int bl_vout_enable_hdmi_out(int channID, uint8_t *inBufAddr, uint32_t inBufSize);
int bl_vout_disable_hdmi_out(void);
int bl_vin_enable_dvp_input(uint32_t pixClk, uint32_t dsp2Clk);
int bl_vin_enable_mipi_input(uint32_t pixClk, uint32_t dsp2Clk, BL_DSP2_INPUT_MODE_E lane_mode);
int bl_vin_enable_raw_file_input(uint8_t *inBufAddr, uint32_t inBufSize);
int bl_vin_enable_fakedata_input();

int bl_dsp2_dump_next_frame(int channID);
int bl_dsp2_set_day_night_mode(BL_DSP2_DAY_NIGHT_MODE_T mode);
int bl_dsp2_low_fps_cfg(uint8_t m);

int bl_dsp2_stats_ready_config(bl_dsp2_stats_ready_cb cb, void *usrdata);
int bl_dsp2_frame_ready_config(int chann_id, bl_dsp2_frame_ready_cb cb, void *usrdata);

void DSP2_Set_PatternGen_Mode(PATTERN_MODE_E mode);
void DSP2_Get_PatternGen_Mode(PATTERN_MODE_E *mode);

void DSP2_AE_STATS_IRQHandler(void);
void DSP2_AE_HIST_STATS_IRQHandler(void);
void DSP2_AWB_STATS_IRQHandler(void);
void DSP2_AWB2_STATS_IRQHandler(void);
void DSP2_AWB3_STATS_IRQHandler(void);
void DSP2_WDR_STATS_IRQHandler(void);
void DSP2_SEOF1_IRQHandler(void);
void DSP2_SEOF2_IRQHandler(void);
void DSP2_SEOF3_IRQHandler(void);
void DSP2_SEOF4_IRQHandler(void);

/*******************************************************************/
int bl_set_AE_state(BL_Fun_Type state);
int bl_set_AE_state_enable(void);
int bl_get_AE_stats_conf (bl_dsp2_ae_stats_conf_t *conf);
int bl_set_AE_stats_conf (bl_dsp2_ae_stats_conf_t *conf);
int bl_get_AE_stats(bl_dsp2_ae_grid_sum_t *stats);
int bl_get_AE_hist_state(BL_Fun_Type *state);
int bl_set_AE_hist_state(BL_Fun_Type state);
int bl_get_AE_hist_mode(AE_HIST_MODE_TYPE_E *mode);
int bl_set_AE_hist_mode(AE_HIST_MODE_TYPE_E mode);
int bl_get_AE_hist_roi(uint16_t *x_min, uint16_t *x_max, uint16_t *y_min, uint16_t *y_max);
int bl_set_AE_hist_roi(uint16_t x_min, uint16_t x_max, uint16_t y_min, uint16_t y_max);
int bl_get_AE_hist_sum_y(bl_dsp2_ae_hist_y_t *y_sum);
int bl_get_AE_hist_sum_bayer(bl_dsp2_ae_hist_bayer_t *sum);

int bl_set_AWB_state(BL_Fun_Type state);
int bl_get_AWB_gain(bl_dsp2_rgb_gain_t *gain);
int bl_set_AWB_gain(bl_dsp2_rgb_gain_t *gain);
int bl_set_RB_gain(const bl_dsp2_rb_gain_t *rb_gain);

int bl_set_AWB1_stats_conf(dsp2_awb_stats_conf_t *awb_stats_conf);
int bl_get_AWB1_stats_conf(dsp2_awb_stats_conf_t *awb_stats_conf);
int bl_get_AWB1_stats(int grid_num, uint32_t *data);
int bl_get_AWB1_sum(int grid_idx, RGB_SUM_S *rgb_sum);

int bl_set_AWB3_stats_conf(dsp2_awb3_stats_conf_t *awb_stats_conf);
int bl_get_AWB3_stats_conf(dsp2_awb3_stats_conf_t *awb_stats_conf);
int bl_get_AWB3_bin_mode(dsp2_awb3_bin_mode_e *mode);
int bl_set_AWB3_bin_mode(dsp2_awb3_bin_mode_e mode);
int bl_get_AWB3_hist_bin_num(uint32_t *bucket_num);
int bl_get_AWB3_hist(bl_dsp2_awb3_stats_hist_t *awb3_hist);
int bl_get_AWB3_gDivisor(int *value);
int bl_set_AWB3_gDivisor(int value);
int bl_get_AWB3_sum(dsp2_awb3_sum_t *awb3_sum);

int bl_get_WDR_state(BL_Fun_Type *state);
int bl_set_WDR_state(BL_Fun_Type state);
int bl_get_WDR_sub_state(bl_dsp2_wdr_sub_state_t *state);
int bl_set_WDR_sub_state(bl_dsp2_wdr_sub_state_t *state);
int bl_get_WDR_hist_roi_info(bl_dsp2_wdr_roi_info_t *info);
int bl_set_WDR_hist_roi_info(bl_dsp2_wdr_roi_info_t *info);
int bl_get_WDR_hist_data(bl_dsp2_wdr_hist_data_t *data);
int bl_get_WDR_curve(bl_dsp2_wdr_curve_t *data);
int bl_set_WDR_curve(bl_dsp2_wdr_curve_t *data);
int bl_get_WDR_curve_weight(int *weight);
int bl_set_WDR_curve_weight(int weight);
int bl_get_WDR_enh(bl_dsp2_wdr_enh_t *conf);
int bl_set_WDR_enh(bl_dsp2_wdr_enh_t *conf);
int bl_get_WDR_cs(bl_dsp2_cs_conf_t *conf);
int bl_set_WDR_cs(bl_dsp2_cs_conf_t *conf);

int bl_dsp2_disable_blc_soft();
int bl_get_BLC_ob(int *ob);
int bl_set_BLC_ob(int ob);

int bl_get_BNR_state(BL_Fun_Type *state);
int bl_set_BNR_state(BL_Fun_Type state);
int bl_get_BNR_weight(int *weight);
int bl_set_BNR_weight(int weight);
int bl_get_BNR_lpf_weight(int *weight);
int bl_set_BNR_lpf_weight(int weight);
int bl_get_BNR_threshold(bl_dsp2_bnr_thr_t *thr);
int bl_set_BNR_threshold(bl_dsp2_bnr_thr_t *thr);
int bl_get_BNR_fallback(bl_dsp2_bnr_fb_t *fb);
int bl_set_BNR_fallback(bl_dsp2_bnr_fb_t *fb);

int bl_get_DPC_state(BL_Fun_Type *state);
int bl_set_DPC_state(BL_Fun_Type state);
int bl_get_DPC_conf(bl_dsp2_dpc_thr_t *conf);
int bl_set_DPC_conf(bl_dsp2_dpc_thr_t *conf);

int bl_get_LSC_state(BL_Fun_Type *state);
int bl_set_LSC_state(BL_Fun_Type state);
int bl_get_LSC_conf(bl_dsp2_lsc_conf_t *conf);
int bl_set_LSC_conf(bl_dsp2_lsc_conf_t *conf);

int bl_dsp2_disable_dg_soft();
int bl_get_DG_conf(bl_dsp2_bayer_gain_t *conf);
int bl_set_DG_conf(bl_dsp2_bayer_gain_t *conf);

int bl_get_CCM_state(BL_Fun_Type *state);
int bl_set_CCM_state(BL_Fun_Type state);
int bl_get_CCM_conf(bl_dsp2_ccm_coef_s *coef);
int bl_set_CCM_conf(bl_dsp2_ccm_coef_s *coef);

int bl_get_GAMMA_state(BL_Fun_Type *state);
int bl_set_GAMMA_state(BL_Fun_Type state);
int bl_get_GAMMA_curve(bl_dsp2_gamma_curve_t *curve);
int bl_set_GAMMA_curve(bl_dsp2_gamma_curve_t *curve);

int bl_dsp2_disable_saturation_soft();
int bl_dsp2_get_saturation(uint32_t *saturation);
int bl_dsp2_set_saturation(uint32_t saturation);

int bl_get_EE_state(BL_Fun_Type *state);
int bl_set_EE_state(BL_Fun_Type state);
int bl_get_EE_conf(bl_dsp2_ee_conf_t *conf);
int bl_set_EE_conf(bl_dsp2_ee_conf_t *conf);
int bl_get_EE_luma_weight(bl_dsp2_ee_luma_weight_t *conf);
int bl_set_EE_luma_weight(bl_dsp2_ee_luma_weight_t *conf);

int bl_dsp2_disable_nr_soft();
int bl_get_NR_conf(bl_dsp2_nr_conf_t *conf);
int bl_set_NR_conf(bl_dsp2_nr_conf_t *conf);

int bl_get_CS_state(BL_Fun_Type *state);
int bl_set_CS_state(BL_Fun_Type state);
int bl_get_CS_conf(bl_dsp2_cs_conf_t *conf);
int bl_set_CS_conf(bl_dsp2_cs_conf_t *conf);

int bl_dsp2_disable_yc_soft();
int bl_get_YC_conf(bl_dsp2_yc_conf_t *conf);
int bl_set_YC_conf(bl_dsp2_yc_conf_t *conf);

int bl_dsp2_disable_af_soft();
int bl_get_AF_stats(bl_dsp2_af_stats_t *conf);
int bl_get_AF_conf(bl_dsp2_af_conf_t *conf);
int bl_set_AF_conf( bl_dsp2_af_conf_t *conf);
int bl_get_AF_win_conf(int win_idx, bl_dsp2_af_win_t *conf);
int bl_set_AF_win_conf(int win_idx, bl_dsp2_af_win_t *conf);

int bl_get_addr_data(uint32_t addr, uint32_t *data);
int bl_set_addr_data(uint32_t addr,  uint32_t data);


#endif /* __BL_DSP2_H__ */

