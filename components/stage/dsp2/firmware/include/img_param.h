#ifndef __IMG_PARAM_H__
#define __IMG_PARAM_H__

#include "bl_comm_sns.h"
#include "img_struct.h"

int img_param_malloc_sw_param_init_buffer(void);
int img_param_free_sw_param_init_buffer(void);

//******* calib *********************************************************************************//
int img_param_calib_load(const char* sensor_name);
int img_param_calib_get_wb_info(int param_idx, wb_info_t **wb_info);
int img_param_calib_set_wb_info(const wb_info_t *wb_info_cal, int wb_info_num);
int img_param_calib_get_wb_info_num(void);
int img_param_calib_get_awb(wb3_cal_bin_t **wb3_cal);
int img_param_calib_set_awb(const wb3_cal_bin_t *wb3_cal);
int img_param_calib_get_blc(int param_idx, blc_cal_t **blc);
int img_param_calib_set_blc(const blc_cal_t *blc_cal);
int img_param_calib_get_dpc(int param_idx, dpc_cal_t **bpc_cal);
int img_param_calib_set_dpc(const dpc_cal_t *bpc_cal);
int img_param_calib_get_lsc(int param_idx, lsc_cal_t **lsc_cal);
int img_param_calib_set_lsc(const lsc_cal_t *lsc_cal, int lsc_num);
int img_param_calib_get_lsc_num();
int img_param_calib_set_lsc_num(int num);
int img_param_calib_get_ccm(int param_idx, ccm_cal_t **ccm_cal);
int img_param_calib_set_ccm(const ccm_cal_t *ccm_cal, int ccm_num);
int img_param_calib_get_ccm_num();
int img_param_calib_set_ccm_num(int num);
int img_param_calib_get_gamma(int param_idx, gamma_cal_t **gamma_cal);
int img_param_calib_set_gamma(int param_idx, const gamma_cal_t *gamma_cal);

void print_cal_tbl(void);

//******* fw *********************************************************************************//
int img_param_load(const char* sensor_name);

int img_param_get_module(const BL_IMG_PARAM_DESC_T **module);
int img_param_get_states(const BL_Fun_Type **state);
int img_param_get_ae_agc_db_tbl(ae_agc_db_tbl **cfg);
int img_param_get_ae_slow_shutter_conf(ae_slow_shutter_conf_t **cfg);
int img_param_get_manual_wb_info(int param_idx, const wb_info_t **wb_info);
int img_param_get_num_manual_wb_info(void);
int img_param_get_wb3_cal(const wb3_cal_bin_t **wb3_cal);
int img_param_get_wb_bias(int param_idx, const wb_bais_t **wb_bias);
int img_param_get_num_wb_bias(void);
int img_param_get_white_region(int param_idx, const white_region_t **region);
int img_param_get_num_white_region(void);

int img_param_get_dpc_trans(const dpc_trans_tbl_t **trans_tbl, int *tbl_num);
int img_param_get_wdr_trans(const wdr_trans_tbl_t **trans_tbl, int *tbl_num);
int img_param_get_cs_trans(const cs_trans_tbl_t **trans_tbl, int *tbl_num);

//******* sw *********************************************************************************//
int img_param_sw_tbl_init(void);
int img_param_get_sw_bin_Addr(uint32_t *addr);
int img_param_sw_load(const char* sensor_name);

int img_param_sw_get_module(const BL_IMG_PARAM_SW_DESC_T **module);
int img_param_sw_get_states(int param_idx, BL_Fun_Type **state);
int img_param_sw_set_states(int param_idx, const BL_Fun_Type *state);

int img_param_sw_get_ae(int param_idx, DSP2_AE_SUB_ATTR **cfg);
int img_param_sw_set_ae(int param_idx, const DSP2_AE_SUB_ATTR *cfg);
int img_param_sw_get_ae_metering_tbl(int param_idx, DSP2_AE_METERING_TBL **cfg);
int img_param_sw_set_ae_metering_tbl(int param_idx, const DSP2_AE_METERING_TBL *cfg);
int img_param_sw_get_ae_highlight_weight_en(int *en);
int img_param_sw_set_ae_highlight_weight_en(const int en);
int img_param_sw_get_ae_highlight_weight(int param_idx, DSP2_AE_HIGHLIGHT_WEIGHT **cfg);
int img_param_sw_set_ae_highlight_weight(int param_idx, const DSP2_AE_HIGHLIGHT_WEIGHT *cfg);
int img_param_sw_get_ae_highlight_weight_conf(DSP2_AE_HIGHLIGHT_WEIGHT_CONF **cfg);
int img_param_sw_set_ae_highlight_weight_conf(const DSP2_AE_HIGHLIGHT_WEIGHT_CONF *cfg);
int img_param_sw_get_ae_metering_mode(int *cfg);
int img_param_sw_set_ae_metering_mode(const int cfg);
int img_param_sw_get_ae_speed_level(int *cfg);
int img_param_sw_set_ae_speed_level(const int cfg);

int img_param_sw_get_awb_speed_level(int *cfg);
int img_param_sw_set_awb_speed_level(const int cfg);
int img_param_sw_get_awb_special_color_en(int *en);
int img_param_sw_set_awb_special_color_en(const int en);
int img_param_sw_get_awb_special_color(int param_idx, awb_special_color_t **cfg);
int img_param_sw_set_awb_special_color(int param_idx, const awb_special_color_t *cfg);
int img_param_sw_get_awb_preference_en(int *en);
int img_param_sw_set_awb_preference_en(const int en);
int img_param_sw_get_awb_preference_gain(int param_idx, awb_bais_t **cfg);
int img_param_sw_set_awb_preference_gain(int param_idx, const awb_bais_t *cfg);

int img_param_sw_get_blc(int param_idx, DSP2_BLC_PARAM **cfg);
int img_param_sw_set_blc(int param_idx, const DSP2_BLC_PARAM *cfg);

int img_param_sw_get_dpc(int param_idx, DSP2_DPC_PARAM **cfg);
int img_param_sw_set_dpc(int param_idx, const DSP2_DPC_PARAM *cfg);

int img_param_sw_get_bnr(int param_idx, DSP2_BNR_PARAM **cfg);
int img_param_sw_set_bnr(int param_idx, const DSP2_BNR_PARAM *cfg);

int img_param_sw_get_lsc(int param_idx, DSP2_LSC_PARAM **cfg);
int img_param_sw_set_lsc(int param_idx, const DSP2_LSC_PARAM *cfg);

int img_param_sw_get_ccm(int param_idx, DSP2_CCM_PARAM **cfg);
int img_param_sw_set_ccm(int param_idx, const DSP2_CCM_PARAM *cfg);
int img_param_sw_get_ccm_color_weight(int param_idx, ccm_cw_t **cfg);
int img_param_sw_set_ccm_color_weight(int param_idx, const ccm_cw_t *cfg);

int img_param_sw_get_gamma_cal(int param_idx, gamma_cal_t **cfg);
int img_param_sw_set_gamma_cal(int param_idx, const gamma_cal_t *cfg);
int img_param_sw_get_gamma(int param_idx, DSP2_GAMMA_PARAM **cfg);
int img_param_sw_set_gamma(int param_idx, const DSP2_GAMMA_PARAM *cfg);

int img_param_sw_get_wdr(int param_idx, DSP2_WDR_PARAM **cfg);
int img_param_sw_set_wdr(int param_idx, const DSP2_WDR_PARAM *cfg);
int img_param_sw_get_wdr_lowlight_weight_conf(wdr_lowlight_weight_conf_t **cfg);
int img_param_sw_set_wdr_lowlight_weight_conf(const wdr_lowlight_weight_conf_t *cfg);
int img_param_sw_get_wdr_lowlight_weight(int param_idx, wdr_lowlight_weight_t **cfg);
int img_param_sw_set_wdr_lowlight_weight(int param_idx, const wdr_lowlight_weight_t *cfg);
int img_param_sw_get_wdr_tone_curve_conf(int param_idx, wdr_tone_curve_conf_t **cfg);
int img_param_sw_set_wdr_tone_curve_conf(int param_idx, const wdr_tone_curve_conf_t *cfg);
int img_param_sw_get_wdr_tone_curve_en(int *en);
int img_param_sw_set_wdr_tone_curve_en(const int en);

int img_param_sw_get_sat(int param_idx, DSP2_SAT_PARAM **cfg);
int img_param_sw_set_sat(int param_idx, const DSP2_SAT_PARAM *cfg);

int img_param_sw_get_yc(int param_idx, DSP2_YC_PARAM **cfg);
int img_param_sw_set_yc(int param_idx, const DSP2_YC_PARAM *cfg);

int img_param_sw_get_nr(int param_idx, DSP2_NR_PARAM **cfg);
int img_param_sw_set_nr(int param_idx, const DSP2_NR_PARAM *cfg);

int img_param_sw_get_ee_over_sht_en(int *en);
int img_param_sw_set_ee_over_sht_en(const int en);
int img_param_sw_get_ee(int param_idx, DSP2_EE_PARAM **cfg);
int img_param_sw_set_ee(int param_idx, const DSP2_EE_PARAM *cfg);
int img_param_sw_get_ee_luma_weight(DSP2_EE_LUMA_WEIGHT **cfg);
int img_param_sw_set_ee_luma_weight(const DSP2_EE_LUMA_WEIGHT *cfg);

int img_param_sw_get_cs(int param_idx, DSP2_CS_PARAM **cfg);
int img_param_sw_set_cs(int param_idx, const DSP2_CS_PARAM *cfg);

int get_lsc_sw_tbl_num(void);
int get_ccm_sw_tbl_num(void);
int get_gamma_sw_tbl_num(void);
int get_wdr_sw_tbl_num(void);

void print_sw_tbl(void);

#endif /* __IMG_PARAM_H__ */

