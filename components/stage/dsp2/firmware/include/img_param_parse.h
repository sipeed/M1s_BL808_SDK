#ifndef __IMG_PARAM_PARSE_H__
#define __IMG_PARAM_PARSE_H__

#include "bl_comm_sns.h"
#include "img_struct.h"

/*********** fw tbl ************************************************************************************************/
int calc_wb_fw_config_by_sys_gain(BL_GAIN_DB sys_gain, bl_dsp2_rb_gain_t *rb_bias);
int calc_lsc_cal_by_color_temp(BL_COLOR_TEMP color_temp, lsc_cal_t *fw_config);
int calc_gamma_cal_by_idx(int idx, gamma_cal_t *config);

/*********** sw tbl ************************************************************************************************/
int calc_ae_sw_config_by_sys_gain(BL_GAIN_DB sys_gain, DSP2_AE_SUB_ATTR *sw_config);
int calc_ae_sw_highlight_weight_by_sys_gain(BL_GAIN_DB sys_gain, int hist_val, int *idx);
int calc_awb_sw_config_by_sys_gain(BL_GAIN_DB sys_gain, BL_COLOR_TEMP color_temp, bl_dsp2_rb_gain_t *rb_bias);
int calc_blc_sw_config_by_iso(BL_GAIN_DB gain, DSP2_BLC_PARAM *sw_config);
int calc_dpc_sw_config_by_iso(BL_GAIN_DB gain, DSP2_DPC_PARAM *sw_config);
int calc_bnr_sw_config_by_iso(BL_GAIN_DB gain, DSP2_BNR_PARAM *sw_config);
int calc_lsc_sw_config_by_color_temp(BL_COLOR_TEMP color_temp, DSP2_LSC_PARAM *sw_config);
int calc_ccm_sw_config_by_color_temp(BL_COLOR_TEMP color_temp, DSP2_CCM_PARAM *sw_config);
int calc_ccm_sw_color_weight_by_iso(BL_GAIN_DB gain, ccm_cw_t *sw_config);
int calc_gamma_sw_config_by_sys_gain(BL_GAIN_DB sys_gain, DSP2_GAMMA_PARAM *sw_config);
int calc_wdr_sw_config_by_sys_gain(BL_GAIN_DB sys_gain, DSP2_WDR_PARAM *sw_config);
int calc_wdr_sw_lowlight_weight_idx_by_sys_gain(BL_GAIN_DB sys_gain, int hist_sum, int *idx);
int calc_wdr_sw_tone_curve_by_idx(int idx, wdr_tone_curve_t *config);
int calc_sat_sw_config_by_iso(BL_GAIN_DB gain, DSP2_SAT_PARAM *sw_config);
int calc_yc_sw_config_by_iso(BL_GAIN_DB gain, DSP2_YC_PARAM *sw_config);
int calc_nr_sw_config_by_iso(BL_GAIN_DB gain, DSP2_NR_PARAM *sw_config);
int calc_ee_sw_config_by_iso(BL_GAIN_DB gain, DSP2_EE_PARAM *sw_config);
int calc_cs_sw_config_by_iso(BL_GAIN_DB gain, DSP2_CS_PARAM *sw_config);

#endif /* __IMG_PARAM_PARSE_H__ */

