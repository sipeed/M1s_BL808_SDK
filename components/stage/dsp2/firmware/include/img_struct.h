#ifndef __IMG_STRUCT_H__
#define __IMG_STRUCT_H__

#include <bl808.h>
#include "bl_dsp2.h"
#include "bl_comm_sns.h"
#include "img_api_struct.h"

#define SENSOR_NAME_STRING_LENGTH           (16)
#define MAX_ENTRY_NUM_AE_ISO_AUTO           (10)
#define MAX_ENTRY_NUM_AE_SYS_GAIN_AUTO      (19)
#define MAX_ENTRY_NUM_AE_AGC_DB_TBL         (16)
#define MAX_ENTRY_NUM_AWB3_CAL_BIN_NUM      (88)
#define MAX_ENTRY_NUM_AWB3_SPECIAL_COLOR    (4)
#define MAX_ENTRY_NUM_AWB_CT_AUTO           (7)
#define MAX_ENTRY_NUM_GAMMA_IDX_AUTO        (3)
#define MAX_ENTRY_NUM_WDR_IDX_AUTO          (3)
#define MAX_ENTRY_NUM_AWB_WHITE_REGION      (6)
#define MAX_ENTRY_NUM_EE_LUMA_WEIGHT        (32)
#define VERT_NUM                            (6)
#define MAX_SYS_GAIN_TBL                 (82944) // 54 *1536
#define MIN_SYS_GAIN_TBL                 (-82944) // 54 *1536
#define WDR_COEF_NUM                        (64)

typedef enum {
    FLICKER_MODE_50 = 0,
    FLICKER_MODE_60,
    FLICKER_MODE_NUM,
} flicker_mode;

typedef enum {
    ISO_AUTO          = 0,
    ISO_100_0DB       = 0,  // 0 DB
    ISO_200_6DB       = 6,  // 6 DB
    ISO_400_12DB      = 12, // 12DB
    ISO_800_18DB      = 18, // 18DB
    ISO_1600_24DB     = 24, // 24DB
    ISO_3200_30DB     = 30, // 30DB
    ISO_6400_36DB     = 36, // 36DB
    ISO_12800_42DB    = 42, // 42DB
    ISO_25600_48DB    = 48, // 48DB
    ISO_51200_54DB    = 54, // 54DB
    ISO_102400_60DB   = 60, // 60DB
    ISO_204800_66DB   = 66, // 66DB
    ISO_409600_72DB   = 72, // 72DB
    ISO_CUSTOM
}ae_iso_mode_t;

typedef enum {
    WB_AUTO,
    WB_H_2300K     = 2300,
    WB_A_2800K     = 2800,
    WB_TL84_4000K  = 4000,
    WB_CWF_4150K   = 4150,
    WB_D50_5000K   = 5000,
    WB_D65_6500K   = 6500,
    WB_D75_7500K   = 7500,
    WB_CUSTOM
}awb_color_temper_mode_t;

typedef enum {
    DSP2_ADJ_AE = 0,
    DSP2_ADJ_AE_TARGET,
    DSP2_ADJ_AWB,
    DSP2_ADJ_AWB_GAIN,
    DSP2_ADJ_AWB3_CAL,
    DSP2_ADJ_AWB_BIAS,
    DSP2_ADJ_AWB_REGION,
    DSP2_ADJ_BLC,
    DSP2_ADJ_DPC,
    DSP2_ADJ_BNR,
    DSP2_ADJ_LSC,
    DSP2_ADJ_CCM,
    DSP2_ADJ_GAMMA,
    DSP2_ADJ_WDR,
    DSP2_ADJ_SATURATION,
    DSP2_ADJ_NR,
    DSP2_ADJ_EE,
    DSP2_ADJ_CS,
    DSP2_ADJ_YC,
    DSP2_ADJ_PARAM_NUM
}img_param_module_t;

typedef enum {
    DSP2_POL_INIT = 0,
    DSP2_POL_INTERPL,
    DSP2_POL_NUM
}img_param_policy_t;

typedef enum {
    DSP2_TBL_AUTO_ISO = 0,
    DSP2_TBL_AUTO_COLOR_TMPER,
    DSP2_TBL_CUSTOM_ISO,
    DSP2_TBL_CUSTOM_COLOR_TMPER,
    DSP2_TBL_CUSTOM_EV,
    DSP2_TBL_INIT,
}img_param_table_t;

// tips for IQ tunner
typedef struct  {
    img_param_module_t module;
    img_param_policy_t policy;
    img_param_table_t  table;
} img_param_header_t;

typedef struct  {
    BL_Fun_Type state[DSP2_ADJ_PARAM_NUM];
} img_param_state_container_t;

/*********************************************************/
/****************** AE PARAM TYPE ***********************/

typedef struct {
    uint8_t agc_db[MAX_ENTRY_NUM_AE_AGC_DB_TBL];
} __attribute__((__packed__)) ae_agc_db_tbl;

typedef struct {
    uint8_t  enable;
    uint16_t fps;
} __attribute__((__packed__)) ae_slow_shutter_conf_t;

typedef struct {
    ae_agc_db_tbl max_agc_db_tbl;
    ae_slow_shutter_conf_t slow_shutter_conf;
} __attribute__((__packed__)) ae_init_container_t;

typedef struct  {
    DSP2_AE_SUB_ATTR container[MAX_ENTRY_NUM_AE_SYS_GAIN_AUTO];
    DSP2_AE_METERING_TBL metering_tbl[AE_METERING_TBL_NUM];
    DSP2_AE_HIGHLIGHT_WEIGHT_CONF highlight_weight_conf;
    uint8_t metering_mode;
    uint8_t speed_level;
} __attribute__((__packed__)) ae_container_sw_t;

typedef struct {
    img_param_header_t header;
    ae_container_sw_t ae_sw;
} __attribute__((__packed__)) ae_fw_container_t;

/*********************************************************/
/****************** AWB3 PARAM TYPE ***********************/
typedef struct {
    bl_dsp2_rb_gain_t bais[3];
} awb_bais_t;

typedef struct {
    uint16_t r_gain;
    uint16_t b_gain;
    uint8_t  weight;
} awb_special_color_t;

typedef struct {
    uint8_t preference_enable;
    uint8_t special_color_enable;
    awb_bais_t preference_gain[MAX_ENTRY_NUM_AE_SYS_GAIN_AUTO];
    awb_special_color_t special_color_info[MAX_ENTRY_NUM_AWB3_SPECIAL_COLOR];
    uint8_t speed_level;
} __attribute__((__packed__)) awb_container_sw_t;

typedef struct {
    img_param_header_t header;
    awb_container_sw_t awb_sw;
} __attribute__((__packed__)) awb_fw_container_t;

// AWB Gain
typedef struct blWB_INFO_S {
    DSP2_RB_Gain_Type rb_gain;
    BL_COLOR_TEMP color_temp;
} wb_info_t;

typedef struct {
    img_param_header_t header;
    int num_wb_info;
    const wb_info_t *wb_info;
} wb_info_container_t;

typedef struct blWB3_cal_bin_S {
    int32_t bin[MAX_ENTRY_NUM_AWB3_CAL_BIN_NUM];
} wb3_cal_bin_t;

typedef struct {
    img_param_header_t header;
    const wb3_cal_bin_t wb3_cal;
} wb3_container_cal_t;

/*********************************************************/
/****************** AWB1 PARAM TYPE ***********************/
// AWB Bais
typedef struct blWB_BIAS_S {
    bl_dsp2_rb_gain_t rb_gain;
    int sys_gain_db;
} wb_bais_t;

typedef struct {
    img_param_header_t header;
    int num_wb_bias;
    const wb_bais_t *wb_bias;
} wb_bias_container_t;

// AWB White Region
typedef struct blVERTEX_S {
    int vertx;
    int verty;
} vertex_t;

typedef struct {
    union {
        uint32_t    data[VERT_NUM * 2];
        vertex_t    vert_array[VERT_NUM];
    } hexagon;
    int             weight;
    BL_COLOR_TEMP   color_temp;
} white_region_t;

typedef struct {
    img_param_header_t header;
    int num_white_region;
    const white_region_t *white_region;
} white_region_container_t;

/*********************************************************/
/****************** BLC PARAM TYPE ***********************/

typedef struct {
    DSP2_BLC_PARAM container[MAX_ENTRY_NUM_AE_ISO_AUTO];
} __attribute__((__packed__)) blc_container_sw_t;

typedef struct {
    uint32_t black_level;
} blc_cal_t;

typedef struct {
    blc_cal_t container[MAX_ENTRY_NUM_AE_ISO_AUTO];
} blc_container_cal_t;

typedef struct {
    img_param_header_t header;
    blc_container_sw_t black_lvl_corr;
} __attribute__((__packed__)) black_lvl_corr_container_t;

/*********************************************************/
/****************** DPC PARAM TYPE ***********************/

typedef struct {
    DSP2_DPC_PARAM container[MAX_ENTRY_NUM_AE_ISO_AUTO];
} __attribute__((__packed__)) dpc_container_sw_t;

typedef struct {
    img_param_header_t header;
    dpc_container_sw_t defect_corr;
} defect_corr_container_t;

typedef struct {
    uint8_t defect_thr_1;
    uint8_t defect_thr_2;
} dpc_cal_t;

typedef struct {
    dpc_cal_t container[MAX_ENTRY_NUM_AE_ISO_AUTO];
} dpc_container_cal_t;

typedef struct {
    int strength_tbl[2];
    int thr1_tbl[2];
    int thr2_tbl[2];
} dpc_trans_tbl_t;

/*********************************************************/

/*********************************************************/
/****************** BNR PARAM TYPE ***********************/

typedef struct {
    DSP2_BNR_PARAM container[MAX_ENTRY_NUM_AE_ISO_AUTO];
} __attribute__((__packed__)) bnr_container_sw_t;

typedef struct {
    img_param_header_t header;
    bnr_container_sw_t bnr_config;
} bnr_config_container_t;

/*********************************************************/

/*********************************************************/
/****************** LSC PARAM TYPE ***********************/

typedef struct {
    int16_t coef[LSC_COEF_NUM];
} lsc_coef_t;

typedef struct {
    uint16_t max_r;
    uint16_t max_g;
    uint16_t max_b;
} lsc_max_t;

typedef struct {
    DSP2_LSC_PARAM container[MAX_ENTRY_NUM_AWB_CT_AUTO];
} __attribute__((__packed__)) lsc_container_sw_t;

typedef struct {
    img_param_header_t header;
    lsc_container_sw_t lens_shading_corr;
} lens_shade_corr_container_t;

typedef struct {
    int strength;
    lsc_coef_t lsc_coef_r;
    lsc_coef_t lsc_coef_g;
    lsc_coef_t lsc_coef_b;
    lsc_max_t lsc_max;
    BL_COLOR_TEMP color_temp;
} lsc_cal_t;

typedef struct {
    int cal_num;
    lsc_cal_t *container;
} lsc_container_cal_t;


/****************** CCM PARAM TYPE ***********************/

typedef struct {
    uint8_t color_weight;
} ccm_cw_t;

typedef struct {
    ccm_cw_t container[MAX_ENTRY_NUM_AE_ISO_AUTO];
} __attribute__((__packed__)) ccm_cw_container_sw_t;

typedef struct {
    DSP2_CCM_PARAM container[MAX_ENTRY_NUM_AWB_CT_AUTO];
    int num_ccm;
} __attribute__((__packed__)) ccm_container_sw_t;

typedef struct {
    int16_t ccm_coef[CCM_COEF_NUM];
} ccm_t;

typedef struct {
    img_param_header_t header;
    int num_color_corr;
    const ccm_container_sw_t *color_corr;
} color_corr_container_t;

typedef struct {
    int16_t coef[CCM_COEF_NUM];
    BL_COLOR_TEMP color_temp;
} ccm_cal_t;

typedef struct {
    DSP2_CCM_PARAM container[MAX_ENTRY_NUM_AWB_CT_AUTO];
    int cal_num;
} ccm_container_cal_t;

/*********************************************************/
/****************** GAMMA PARAM TYPE *********************/

typedef struct {
    int16_t coef[GAMMA_COEF_NUM];
} __attribute__((__packed__)) gamma_curve_t;

typedef struct {
    gamma_curve_t gamma_curve;
    int idx;
} __attribute__((__packed__)) gamma_cal_t;

typedef struct {
    gamma_cal_t container[MAX_ENTRY_NUM_GAMMA_IDX_AUTO];
} __attribute__((__packed__)) gamma_container_cal_t;

typedef struct {
    DSP2_GAMMA_PARAM container[MAX_ENTRY_NUM_AE_SYS_GAIN_AUTO];
} __attribute__((__packed__)) gamma_container_sw_t;

typedef struct {
    img_param_header_t header;
    gamma_container_sw_t gamma_corr;
} __attribute__((__packed__)) gamma_corr_container_t;

/*********************************************************/
/******************* WDR PARAM TYPE **********************/

typedef struct {
    DSP2_WDR_PARAM container[MAX_ENTRY_NUM_AE_SYS_GAIN_AUTO];
} __attribute__((__packed__)) wdr_container_sw_t;

typedef struct {
    img_param_header_t header;
    wdr_container_sw_t wdr_config;;
} __attribute__((__packed__)) wdr_config_container_t;

typedef struct {
    int cs_strength_tbl[2];
    int cs_weight_tbl[2];
    int cs_grey_thr_tbl[2];
} wdr_trans_tbl_t;

typedef struct {
    BL_UINT8 idx[3];
} wdr_lowlight_weight_t;

typedef struct  {
    BL_UINT16 roi_start;
    BL_UINT16 roi_end;
    BL_UINT16 thr[4];
    wdr_lowlight_weight_t lowlight_weight[BL_BV_NODES];
} wdr_lowlight_weight_conf_t;

typedef struct {
    uint16_t coef[WDR_COEF_NUM];
} wdr_tone_curve_t;

typedef struct {
    wdr_tone_curve_t tone_curve;
    uint8_t idx;
} wdr_tone_curve_conf_t;

typedef struct {
    uint8_t enable;
    wdr_lowlight_weight_conf_t lowlight_weight_conf;
    wdr_tone_curve_conf_t tone_curve_container[MAX_ENTRY_NUM_WDR_IDX_AUTO];
} __attribute__((__packed__)) wdr_manual_conf_t;
/*********************************************************/
/**************** SATURATION PARAM TYPE ******************/

typedef struct {
    DSP2_SAT_PARAM container[MAX_ENTRY_NUM_AE_ISO_AUTO];
} __attribute__((__packed__)) sat_container_sw_t;

typedef struct blSATURATION_S {
    uint8_t value;
} saturation_t;

typedef struct {
    img_param_header_t header;
    sat_container_sw_t saturation;
} saturation_container_t;

/*********************************************************/
/******************** NR PARAM TYPE **********************/

typedef struct {
    DSP2_NR_PARAM container[MAX_ENTRY_NUM_AE_ISO_AUTO];
} __attribute__((__packed__)) nr_container_sw_t;

typedef struct {
    img_param_header_t header;
    nr_container_sw_t noise_reduction;
} noise_reduct_container_t;

/*********************************************************/
/******************** EE PARAM TYPE **********************/

typedef struct {
    BL_UINT8 over_sht_en;
    DSP2_EE_PARAM container[MAX_ENTRY_NUM_AE_ISO_AUTO];
} __attribute__((__packed__)) ee_container_sw_t;

typedef struct {
    uint16_t lumaWgtTbl[MAX_ENTRY_NUM_EE_LUMA_WEIGHT];
} ee_luma_wgt_t;

typedef struct {
    img_param_header_t header;
    ee_container_sw_t edgeEnhance;
    ee_luma_wgt_t lumaWgtTbl;
} __attribute__((__packed__)) edge_enhance_container_t;

/*********************************************************/
/******************** CS PARAM TYPE **********************/

typedef struct {
    DSP2_CS_PARAM container[MAX_ENTRY_NUM_AE_ISO_AUTO];
} __attribute__((__packed__)) cs_container_sw_t;

typedef struct {
    img_param_header_t header;
    cs_container_sw_t csCfg;
} chroma_suppress_container_t;

typedef struct {
    int strength_tbl[2];
    int weight_tbl[2];
    int grey_thr_tbl[2];
} cs_trans_tbl_t;

/******************** yc PARAM TYPE **********************/

typedef struct {
    DSP2_YC_PARAM container[MAX_ENTRY_NUM_AE_ISO_AUTO];
} __attribute__((__packed__)) yc_container_sw_t;

typedef struct {
    img_param_header_t header;
    yc_container_sw_t ycCfg;
} yc_container_t;

/******************** dg PARAM TYPE **********************/
typedef struct {
    uint16_t r_gain;
    uint16_t gr_gain;
    uint16_t gb_gain;
    uint16_t b_gain;
} dg_param_sw_t;

typedef struct {
    dg_param_sw_t container[MAX_ENTRY_NUM_AE_SYS_GAIN_AUTO];
} __attribute__((__packed__)) dg_container_sw_t;

typedef struct {
    img_param_header_t header;
    dg_container_sw_t dgCfg;
} dg_container_t;

/*********************************************************/
/************ IMG PARAM DESCRIPTION **********************/
typedef struct {
    char name[16];
    img_param_state_container_t   state_tbl;
    ae_container_sw_t             ae_tbl;
    awb_container_sw_t            awb_tbl;
    blc_container_sw_t            blc_tbl;
    dpc_container_sw_t            dpc_tbl;
    bnr_container_sw_t            bnr_tbl;
    lsc_container_sw_t            lsc_tbl;
    ccm_container_sw_t            ccm_tbl;
    ccm_cw_container_sw_t         ccm_cw_tbl;
    gamma_container_cal_t         gamma_cal_tbl;
    gamma_container_sw_t          gamma_tbl;
    wdr_container_sw_t            wdr_tbl;
    wdr_manual_conf_t             wdr_manual_conf;
    sat_container_sw_t            sat_tbl;
    yc_container_sw_t             yc_tbl;
    nr_container_sw_t             nr_tbl;
    ee_container_sw_t             ee_tbl;
    ee_luma_wgt_t                 ee_luma_wgt_tbl;
    cs_container_sw_t             cs_tbl;
} BL_IMG_PARAM_SW_BIN_DESC_T;

typedef struct {
    char *name;
    img_param_state_container_t   *state_tbl;
    ae_container_sw_t             *ae_tbl;
    awb_container_sw_t            *awb_tbl;
    blc_container_sw_t            *blc_tbl;
    dpc_container_sw_t            *dpc_tbl;
    bnr_container_sw_t            *bnr_tbl;
    lsc_container_sw_t            *lsc_tbl;
    ccm_container_sw_t            *ccm_tbl;
    ccm_cw_container_sw_t         *ccm_cw_tbl;
    gamma_container_cal_t         *gamma_cal_tbl;
    gamma_container_sw_t          *gamma_tbl;
    wdr_container_sw_t            *wdr_tbl;
    wdr_manual_conf_t             *wdr_manual_conf;
    sat_container_sw_t            *sat_tbl;
    yc_container_sw_t             *yc_tbl;
    nr_container_sw_t             *nr_tbl;
    ee_container_sw_t             *ee_tbl;
    ee_luma_wgt_t                 *ee_luma_wgt_tbl;
    cs_container_sw_t             *cs_tbl;
} BL_IMG_PARAM_SW_DESC_T;

typedef struct {
    char name[16];
    wb_info_container_t         wb_info_tbl;
    wb3_container_cal_t         wb3_cal_tbl;
    blc_container_cal_t         blc_tbl;
    dpc_container_cal_t         dpc_cal_tbl;
    lsc_container_cal_t         lsc_cal_tbl;
    ccm_container_cal_t         ccm_cal_tbl;
    gamma_container_cal_t       gamma_cal_tbl;
} BL_IMG_PARAM_CALIB_BIN_DESC_T;

typedef struct {
    const char* name;
    const img_param_state_container_t *state_tbl;               //sw    fw
    const ae_init_container_t         *ae_init_tbl;             //         init
    const ae_fw_container_t           *ae_tbl;                  //sw
    const awb_fw_container_t          *awb_tbl;                 //sw
    const wb_info_container_t         *wb_info_tbl;             //      cal
    const wb3_container_cal_t         *wb3_cal_tbl;             //      cal
    const wb_bias_container_t         *wb_bias_tbl;             //      fw
    const white_region_container_t    *awb_white_region_tbl;    //      fw
    const black_lvl_corr_container_t  *blc_tbl;                 //sw    cal
    const dpc_container_cal_t         *dpc_cal_tbl;             //      cal
    const dpc_trans_tbl_t             *dpc_trans_tbl;           //      fw
    const defect_corr_container_t     *defect_corr_tbl;         //sw
    const bnr_config_container_t      *bnr_config_tbl;          //sw
    const lsc_container_cal_t         *lsc_cal_tbl;             //      cal
    const lens_shade_corr_container_t *lens_shading_corr_tbl;   //sw
    const color_corr_container_t      *color_corr_tbl;          //sw    cal
    const ccm_cw_container_sw_t       *ccm_cw_tbl;              //sw
    const gamma_container_cal_t       *gamma_cal_tbl;           //sw    cal
    const gamma_corr_container_t      *gamma_corr_tbl;          //sw
    const wdr_trans_tbl_t             *wdr_trans_tbl;           //      fw
    const wdr_config_container_t      *wdr_config_tbl;          //sw
    const wdr_manual_conf_t           *wdr_manual_conf;       //      fw
    const saturation_container_t      *saturation_tbl;          //sw
    const yc_container_t              *yc_tbl;                  //sw
    const noise_reduct_container_t    *noise_reduction_tbl;     //sw
    const edge_enhance_container_t    *edge_enhance_tbl;        //sw
    const cs_trans_tbl_t              *cs_trans_tbl;            //      fw
    const chroma_suppress_container_t *cs_tbl;                  //sw
} __attribute__((__packed__)) BL_IMG_PARAM_DESC_T;


#define ATTR_IMG_PARAM_DESC_TABLE __attribute__((section(".img_param_desc")))  __attribute__((used))


#endif /* __IMG_STRUCT_H__ */

