#include <string.h>
#include "img_param.h"
#include "img_param_parse.h"
#include "sensor.h"
#include "bl_comm_sns.h"
#include "bl_img_utils.h"

#define GAIN_ALPHA_PRECISION         (8)

static void linear_intpl_by_gain(int value_L, int value_H, BL_GAIN_DB gain, int *value_out)
{
    int idx;
    BL_GAIN_DB gain_L, gain_H;

    idx = (gain / GAIN_6_DB);
    if (gain < 0) idx--;
    gain_L = idx * GAIN_6_DB;
    gain_H = gain_L + GAIN_6_DB;

    intpl_point_t point_L = create_intpl_point(gain_L, value_L);
    intpl_point_t point_H = create_intpl_point(gain_H, value_H);
    linear_interpolate(&point_L, &point_H, gain, value_out);
}

#if 0
static void linear_intpl_by_gain_uint32(uint32_t value_L, uint32_t value_H, BL_GAIN_DB gain, uint32_t *value_out)
{
    BL_GAIN_DB gain_L = (gain / GAIN_6_DB) * GAIN_6_DB;
    BL_GAIN_DB gain_H = gain_L + GAIN_6_DB;

    intpl_point_t point_L = create_intpl_point(gain_L, value_L);
    intpl_point_t point_H = create_intpl_point(gain_H, value_H);
    linear_interpolate(&point_L, &point_H, gain,(int *)value_out);
}

static void linear_intpl_by_gain_uint16(uint16_t value_L, uint16_t value_H, BL_GAIN_DB gain, uint16_t *value_out)
{
    BL_GAIN_DB gain_L = (gain / GAIN_6_DB) * GAIN_6_DB;
    BL_GAIN_DB gain_H = gain_L + GAIN_6_DB;

    intpl_point_t point_L = create_intpl_point(gain_L, value_L);
    intpl_point_t point_H = create_intpl_point(gain_H, value_H);
    linear_interpolate(&point_L, &point_H, gain, (int *)value_out);
}

static void linear_intpl_by_gain_uint8(uint8_t value_L, uint8_t value_H, BL_GAIN_DB gain, uint8_t *value_out)
{
    BL_GAIN_DB gain_L = (gain / GAIN_6_DB) * GAIN_6_DB;
    BL_GAIN_DB gain_H = gain_L + GAIN_6_DB;

    intpl_point_t point_L = create_intpl_point(gain_L, value_L);
    intpl_point_t point_H = create_intpl_point(gain_H, value_H);
    linear_interpolate(&point_L, &point_H, gain, (int *)value_out);
}
#endif

static int getSysGainIdx(BL_GAIN_DB sys_gain)
{
    int param_idx = 0;
    int temp_idx = (sys_gain / GAIN_6_DB);
    if (sys_gain < 0) param_idx = temp_idx + 8;
    else param_idx = temp_idx + 9;

    return param_idx;
}

static int getIsoIdx(BL_GAIN_DB gain)
{
    int param_idx = gain / GAIN_6_DB;

    return param_idx;
}

/*********** fw tbl ************************************************************************************************/
int calc_wb_fw_config_by_sys_gain(BL_GAIN_DB sys_gain, bl_dsp2_rb_gain_t *rb_bias)
{
    int wb_bias_idx;
    BL_GAIN_DB sys_gain_L, sys_gain_H;
    const wb_bais_t *wb_bias_L, *wb_bias_H;
    intpl_point_t point_L, point_H;
    int value;
    int num_wb_bias = img_param_get_num_wb_bias();

    for (wb_bias_idx = 0; wb_bias_idx < (num_wb_bias - 1); wb_bias_idx++) {

        img_param_get_wb_bias(wb_bias_idx, &wb_bias_L);
        img_param_get_wb_bias(wb_bias_idx + 1, &wb_bias_H);

        sys_gain_L = INT_TO_GAIN_DB(wb_bias_L->sys_gain_db);
        sys_gain_H = INT_TO_GAIN_DB(wb_bias_H->sys_gain_db);

        if (sys_gain >= sys_gain_L && sys_gain <= sys_gain_H) {
            /* now we get the range of sys gain */

            /* interpolate r_gain */
            point_L = create_intpl_point(sys_gain_L, wb_bias_L->rb_gain.r_gain);
            point_H = create_intpl_point(sys_gain_H, wb_bias_H->rb_gain.r_gain);
            linear_interpolate(&point_L, &point_H, sys_gain, &value);
            rb_bias->r_gain = value;

            /* interpolate b_gain */
            point_L = create_intpl_point(sys_gain_L, wb_bias_L->rb_gain.b_gain);
            point_H = create_intpl_point(sys_gain_H, wb_bias_H->rb_gain.b_gain);
            linear_interpolate(&point_L, &point_H, sys_gain, &value);
            rb_bias->b_gain = value;
            return 0;
        }

        if (wb_bias_idx == 0 && sys_gain < sys_gain_L) {
            *rb_bias = wb_bias_L->rb_gain;
            return 0;
        }

        if (wb_bias_idx == (num_wb_bias - 2) && sys_gain > sys_gain_H) {
            *rb_bias = wb_bias_H->rb_gain;
            return 0;
        }
    }

    return 0;
}

static const lsc_cal_t lsc_unit_map = {
    100,
    {{ 0,0,255,0,0,0, }},      // R
    {{ 0,0,255,0,0,0, }},      // G
    {{ 0,0,255,0,0,0, }},      // B
    {  255, 255,  255 },      // max
    0,
};

int calc_lsc_cal_by_color_temp(BL_COLOR_TEMP color_temp, lsc_cal_t *fw_config)
{
    int lsc_idx, i, value;
    int lsc_num = img_param_calib_get_lsc_num();
    BL_COLOR_TEMP color_temp_L, color_temp_H;
    lsc_cal_t *lsc_corr_L, *lsc_corr_H;
    intpl_point_t point_L, point_H;
    int alpha_hex = 0;

    for (lsc_idx = 0; lsc_idx < (lsc_num - 1); lsc_idx++) {

        img_param_calib_get_lsc(lsc_idx, &lsc_corr_L);
        img_param_calib_get_lsc(lsc_idx + 1, &lsc_corr_H);

        color_temp_L = lsc_corr_L->color_temp;
        color_temp_H = lsc_corr_H->color_temp;

        if (color_temp >= color_temp_L && color_temp <= color_temp_H) {
            /* now we get the range of color temp */

            for (i = 0; i < LSC_COEF_NUM; i++) {
                /* interpolate each coef of LSC R */
                point_L = create_intpl_point(color_temp_L, lsc_corr_L->lsc_coef_r.coef[i]);
                point_H = create_intpl_point(color_temp_H, lsc_corr_H->lsc_coef_r.coef[i]);
                linear_interpolate(&point_L, &point_H, color_temp, &value);
                fw_config->lsc_coef_r.coef[i] = value;
            }
            for (i = 0; i < LSC_COEF_NUM; i++) {
                /* interpolate each coef of LSC G */
                point_L = create_intpl_point(color_temp_L, lsc_corr_L->lsc_coef_g.coef[i]);
                point_H = create_intpl_point(color_temp_H, lsc_corr_H->lsc_coef_g.coef[i]);
                linear_interpolate(&point_L, &point_H, color_temp, &value);
                fw_config->lsc_coef_g.coef[i] = value;
            }
            for (i = 0; i < LSC_COEF_NUM; i++) {
                /* interpolate each coef of LSC B */
                point_L = create_intpl_point(color_temp_L, lsc_corr_L->lsc_coef_b.coef[i]);
                point_H = create_intpl_point(color_temp_H, lsc_corr_H->lsc_coef_b.coef[i]);
                linear_interpolate(&point_L, &point_H, color_temp, &value);
                fw_config->lsc_coef_b.coef[i] = value;
            }
            point_L = create_intpl_point(color_temp_L, lsc_corr_L->strength);
            point_H = create_intpl_point(color_temp_H, lsc_corr_H->strength);
            linear_interpolate(&point_L, &point_H, color_temp, &value);
            fw_config->strength = value;
            point_L = create_intpl_point(color_temp_L, lsc_corr_L->lsc_max.max_r);
            point_H = create_intpl_point(color_temp_H, lsc_corr_H->lsc_max.max_r);
            linear_interpolate(&point_L, &point_H, color_temp, &value);
            fw_config->lsc_max.max_r = value;
            point_L = create_intpl_point(color_temp_L, lsc_corr_L->lsc_max.max_g);
            point_H = create_intpl_point(color_temp_H, lsc_corr_H->lsc_max.max_g);
            linear_interpolate(&point_L, &point_H, color_temp, &value);
            fw_config->lsc_max.max_g = value;
            point_L = create_intpl_point(color_temp_L, lsc_corr_L->lsc_max.max_b);
            point_H = create_intpl_point(color_temp_H, lsc_corr_H->lsc_max.max_b);
            linear_interpolate(&point_L, &point_H, color_temp, &value);
            fw_config->lsc_max.max_b = value;

            break;
        }
        else if (lsc_idx == 0 && color_temp < color_temp_L) {
            alpha_hex = color_temp * 128 / color_temp_L;//color_temp dist weight is 2
            for (i = 0; i < LSC_COEF_NUM; i++) {
                fw_config->lsc_coef_r.coef[i] = alpha_blend(lsc_corr_L->lsc_coef_r.coef[i], lsc_unit_map.lsc_coef_r.coef[i], alpha_hex, GAIN_ALPHA_PRECISION);
                fw_config->lsc_coef_g.coef[i] = alpha_blend(lsc_corr_L->lsc_coef_g.coef[i], lsc_unit_map.lsc_coef_r.coef[i], alpha_hex, GAIN_ALPHA_PRECISION);
                fw_config->lsc_coef_b.coef[i] = alpha_blend(lsc_corr_L->lsc_coef_b.coef[i], lsc_unit_map.lsc_coef_r.coef[i], alpha_hex, GAIN_ALPHA_PRECISION);
            }
            fw_config->strength = alpha_blend(lsc_corr_L->strength, lsc_unit_map.strength, alpha_hex, GAIN_ALPHA_PRECISION);
            fw_config->lsc_max.max_r = alpha_blend(lsc_corr_L->lsc_max.max_r, lsc_unit_map.lsc_max.max_r, alpha_hex, GAIN_ALPHA_PRECISION);
            fw_config->lsc_max.max_g = alpha_blend(lsc_corr_L->lsc_max.max_g, lsc_unit_map.lsc_max.max_g, alpha_hex, GAIN_ALPHA_PRECISION);
            fw_config->lsc_max.max_b = alpha_blend(lsc_corr_L->lsc_max.max_b, lsc_unit_map.lsc_max.max_b, alpha_hex, GAIN_ALPHA_PRECISION);
            break;
        }
        else if (lsc_idx == (lsc_num - 2) && color_temp > color_temp_H) {
            for (i = 0; i < LSC_COEF_NUM; i++) {
                fw_config->lsc_coef_r.coef[i] = lsc_corr_H->lsc_coef_r.coef[i];
                fw_config->lsc_coef_g.coef[i] = lsc_corr_H->lsc_coef_g.coef[i];
                fw_config->lsc_coef_b.coef[i] = lsc_corr_H->lsc_coef_b.coef[i];
            }
            fw_config->strength = lsc_corr_H->strength;
            fw_config->lsc_max.max_r = lsc_corr_H->lsc_max.max_r;
            fw_config->lsc_max.max_g = lsc_corr_H->lsc_max.max_g;
            fw_config->lsc_max.max_b = lsc_corr_H->lsc_max.max_b;
            break;
        }
    }

//    BL_LOGI("img_update_lsc: %d, %d, %d\r\n", dsp2_cfg.lsc.lsc_coef_r.coef[0], dsp2_cfg.lsc.lsc_coef_r.coef[1],
//        dsp2_cfg.lsc.lsc_coef_r.coef[2]);

    return 0;
}

int calc_gamma_cal_by_idx(int idx, gamma_cal_t *config)
{
    int i, value, gamma_idx, num_gamma;
    int ret = -1;
    int idx_L, idx_H;
    gamma_cal_t *gamma_L, *gamma_H;
    intpl_point_t point_L, point_H;

    num_gamma = MAX_ENTRY_NUM_GAMMA_IDX_AUTO;

    for (gamma_idx = 0; gamma_idx < (num_gamma - 1); gamma_idx++) {

        img_param_calib_get_gamma(gamma_idx, &gamma_L);
        img_param_calib_get_gamma(gamma_idx + 1, &gamma_H);

        idx_L = gamma_L->idx;
        idx_H = gamma_H->idx;

        if (idx >= idx_L && idx <= idx_H) {
            for (i = 0; i < GAMMA_COEF_NUM; i++) {
                /* interpolate each coef of gamma */
                point_L = create_intpl_point(idx_L, gamma_L->gamma_curve.coef[i]);
                point_H = create_intpl_point(idx_H, gamma_H->gamma_curve.coef[i]);
                linear_interpolate(&point_L, &point_H, idx, &value);
                config->gamma_curve.coef[i] = value;
            }
            ret = 0;
            break;
        } else if (gamma_idx == 0 && idx < idx_L) {
            memcpy(config, &gamma_L->gamma_curve, sizeof(gamma_cal_t));
            ret = 0;
            break;
        } else if (gamma_idx == (num_gamma - 2) && idx > idx_H) {
            memcpy(config, &gamma_H->gamma_curve, sizeof(gamma_cal_t));
            ret = 0;
            break;
        }
    }

    return ret;
}

/*********** fw tbl end ************************************************************************************************/

/*********** sw tbl ************************************************************************************************/
int calc_ae_sw_config_by_sys_gain(BL_GAIN_DB sys_gain, DSP2_AE_SUB_ATTR *sw_config)
{
    int param_idx, value;
    DSP2_AE_SUB_ATTR *sw_param_L, *sw_param_H;
    int num_target_tbl = MAX_ENTRY_NUM_AE_SYS_GAIN_AUTO;

    if (sys_gain > MAX_SYS_GAIN_TBL) {
        img_param_sw_get_ae(num_target_tbl - 1, &sw_config);
    } else if (sys_gain < MIN_SYS_GAIN_TBL) {
        img_param_sw_get_ae(0, &sw_config);
    } else {
        param_idx = getSysGainIdx(sys_gain);
        
        img_param_sw_get_ae(param_idx, &sw_param_L);
        img_param_sw_get_ae(param_idx + 1, &sw_param_H);

        linear_intpl_by_gain(sw_param_L->ae_target, sw_param_H->ae_target, sys_gain, &value);
        sw_config->ae_target = value;
    }

     return 0;
}

static int calc_ae_highlight_weight_by_sys_gain(BL_GAIN_DB sys_gain, DSP2_AE_HIGHLIGHT_WEIGHT *sw_config)
{
    int param_idx, value;
    DSP2_AE_HIGHLIGHT_WEIGHT *sw_param_L, *sw_param_H;
    int num_target_tbl = MAX_ENTRY_NUM_AE_SYS_GAIN_AUTO;

    if (sys_gain > MAX_SYS_GAIN_TBL) {
        img_param_sw_get_ae_highlight_weight(num_target_tbl - 1, &sw_config);
    } else if (sys_gain < MIN_SYS_GAIN_TBL) {
        img_param_sw_get_ae_highlight_weight(0, &sw_config);
    } else {
        param_idx = getSysGainIdx(sys_gain);

        img_param_sw_get_ae_highlight_weight(param_idx, &sw_param_L);
        img_param_sw_get_ae_highlight_weight(param_idx + 1, &sw_param_H);

        linear_intpl_by_gain(sw_param_L->idx[0], sw_param_H->idx[0], sys_gain, &value);
        sw_config->idx[0] = value;
        linear_intpl_by_gain(sw_param_L->idx[1], sw_param_H->idx[1], sys_gain, &value);
        sw_config->idx[1] = value;
        linear_intpl_by_gain(sw_param_L->idx[2], sw_param_H->idx[2], sys_gain, &value);
        sw_config->idx[2] = value;
    }

     return 0;
}

int calc_ae_sw_highlight_weight_by_sys_gain(BL_GAIN_DB sys_gain, int hist_sum, int *idx)
{
    int value;
    DSP2_AE_HIGHLIGHT_WEIGHT sw_config;
    DSP2_AE_HIGHLIGHT_WEIGHT_CONF *highlight_weight_conf;
    intpl_point_t point_L, point_H;

    calc_ae_highlight_weight_by_sys_gain(sys_gain, &sw_config);

    img_param_sw_get_ae_highlight_weight_conf(&highlight_weight_conf);
     if (hist_sum <= highlight_weight_conf->thr[0]) {
        *idx = (int)sw_config.idx[0];
    } else if (hist_sum < highlight_weight_conf->thr[1]) {
        point_L = create_intpl_point(highlight_weight_conf->thr[0], sw_config.idx[0]);
        point_H = create_intpl_point(highlight_weight_conf->thr[1], sw_config.idx[1]);
        linear_interpolate(&point_L, &point_H, hist_sum, &value);
        *idx = value;
    } else if (hist_sum < highlight_weight_conf->thr[2]) {
        *idx = (int)sw_config.idx[1];
    } else if (hist_sum < highlight_weight_conf->thr[3]) {
        point_L = create_intpl_point(highlight_weight_conf->thr[2], sw_config.idx[1]);
        point_H = create_intpl_point(highlight_weight_conf->thr[3], sw_config.idx[2]);
        linear_interpolate(&point_L, &point_H, hist_sum, &value);
        *idx = value;
    } else {
        *idx = (int)sw_config.idx[2];
    }
    return 0;
}

int calc_awb_sw_config_by_sys_gain(BL_GAIN_DB sys_gain, BL_COLOR_TEMP color_temp, bl_dsp2_rb_gain_t *rb_bias)
{
    int i = 0;
    int gain_idx, value;
    int ct_idx = 2;
    awb_bais_t *awb_bias_L, *awb_bias_H;
    awb_bais_t awb_bias_P;
    intpl_point_t point_L, point_H;
    int num_awb_bias = 19;
    int ct_idx_tbl[] = {2700, 5000, 7000};
    int num_ct = 3;
    int sys_gain_db = 0;;

    if (sys_gain > MAX_SYS_GAIN_TBL) {// 54 * 1536
        img_param_sw_get_awb_preference_gain(num_awb_bias - 1, &awb_bias_L);
        memcpy(&awb_bias_P, awb_bias_L, sizeof(awb_bais_t));
    } else if (sys_gain < MIN_SYS_GAIN_TBL) {// -54 * 1536
        img_param_sw_get_awb_preference_gain(0, &awb_bias_L);
        memcpy(&awb_bias_P, awb_bias_L, sizeof(awb_bais_t));
    } else {
        gain_idx = getSysGainIdx(sys_gain);

        img_param_sw_get_awb_preference_gain(gain_idx, &awb_bias_L);
        img_param_sw_get_awb_preference_gain(gain_idx + 1, &awb_bias_H);
        for (i = 0; i < num_ct; i++) {
            linear_intpl_by_gain((int)awb_bias_L->bais[i].r_gain, (int)awb_bias_H->bais[i].r_gain, sys_gain, &value);
            awb_bias_P.bais[i].r_gain = value;
            linear_intpl_by_gain((int)awb_bias_L->bais[i].b_gain, (int)awb_bias_H->bais[i].b_gain, sys_gain, &value);
            awb_bias_P.bais[i].b_gain = value;
        }
    }

    if (color_temp <= ct_idx_tbl[0]) {
        ct_idx = 0;
        rb_bias->r_gain = awb_bias_P.bais[ct_idx].r_gain;
        rb_bias->b_gain = awb_bias_P.bais[ct_idx].b_gain;
        return 0;
    } else if (color_temp >= ct_idx_tbl[2]) {
        ct_idx = 2;
        rb_bias->r_gain = awb_bias_P.bais[ct_idx].r_gain;
        rb_bias->b_gain = awb_bias_P.bais[ct_idx].b_gain;
        return 0;
    } else {
        for (i = 1; i < num_ct; i++) {
            if (color_temp <= ct_idx_tbl[i]) {
                ct_idx = i - 1;
                break;
            }
        }

        /* interpolate r_gain */
        point_L = create_intpl_point(ct_idx_tbl[ct_idx],   awb_bias_P.bais[ct_idx].r_gain);
        point_H = create_intpl_point(ct_idx_tbl[ct_idx+1], awb_bias_P.bais[ct_idx+1].r_gain);
        linear_interpolate(&point_L, &point_H, color_temp, &value);
        rb_bias->r_gain = value;

        /* interpolate b_gain */
        point_L = create_intpl_point(ct_idx_tbl[ct_idx],   awb_bias_P.bais[ct_idx].b_gain);
        point_H = create_intpl_point(ct_idx_tbl[ct_idx+1], awb_bias_P.bais[ct_idx+1].b_gain);
        linear_interpolate(&point_L, &point_H, color_temp, &value);
        rb_bias->b_gain = value;
    }

    return 0;
}

int calc_blc_sw_config_by_iso(BL_GAIN_DB gain, DSP2_BLC_PARAM *sw_config)
{
    int param_idx, value;
    DSP2_BLC_PARAM *sw_param_L, *sw_param_H;

    param_idx = getIsoIdx(gain);

    img_param_sw_get_blc(param_idx, &sw_param_L);
    img_param_sw_get_blc(param_idx + 1, &sw_param_H);

    linear_intpl_by_gain(sw_param_L->black_level, sw_param_H->black_level, gain, &value);
    sw_config->black_level = value;

    return 0;
}

int calc_dpc_sw_config_by_iso(BL_GAIN_DB gain, DSP2_DPC_PARAM *sw_config)
{
    int param_idx, value;
    DSP2_DPC_PARAM *sw_param_L, *sw_param_H;

    param_idx = getIsoIdx(gain);

    img_param_sw_get_dpc(param_idx, &sw_param_L);
    img_param_sw_get_dpc(param_idx + 1, &sw_param_H);

    linear_intpl_by_gain(sw_param_L->strength, sw_param_H->strength, gain, &value);
    sw_config->strength = value;

    return 0;
}

int calc_bnr_sw_config_by_iso(BL_GAIN_DB gain, DSP2_BNR_PARAM *sw_config)
{
    int param_idx, value;
    DSP2_BNR_PARAM *sw_param_L, *sw_param_H;

    param_idx = getIsoIdx(gain);

    img_param_sw_get_bnr(param_idx, &sw_param_L);
    img_param_sw_get_bnr(param_idx + 1, &sw_param_H);

    linear_intpl_by_gain(sw_param_L->strength, sw_param_H->strength, gain, &value);
    sw_config->strength = value;

    return 0;
}

int calc_lsc_sw_config_by_color_temp(BL_COLOR_TEMP color_temp, DSP2_LSC_PARAM *sw_config)
{
    int container_idx = 0, value;
    int tbl_num = get_lsc_sw_tbl_num();
    BL_COLOR_TEMP color_temp_L, color_temp_H;
    DSP2_LSC_PARAM *sw_param_L, *sw_param_H;
    intpl_point_t point_L, point_H;

    if (tbl_num == 0) {
        return -1;
    }

    for (container_idx = 0; container_idx < (tbl_num - 1); container_idx++) {

        img_param_sw_get_lsc(container_idx, &sw_param_L);
        img_param_sw_get_lsc(container_idx + 1, &sw_param_H);

        color_temp_L = sw_param_L->color_temp;
        color_temp_H = sw_param_H->color_temp;

        if (color_temp >= color_temp_L && color_temp <= color_temp_H) {
            /* now we get the range of color temp */
            point_L = create_intpl_point(color_temp_L, sw_param_L->strength);
            point_H = create_intpl_point(color_temp_H, sw_param_H->strength);
            linear_interpolate(&point_L, &point_H, color_temp, &value);
            sw_config->strength = value;
            sw_config->color_temp = color_temp;
            break;
        }
        else if (container_idx == 0 && color_temp < color_temp_L) {
            sw_config->strength = sw_param_L->strength;
            sw_config->color_temp = color_temp_L;
            break;
        }
        else if (container_idx == (tbl_num - 2) && color_temp > color_temp_H) {
            sw_config->strength = sw_param_H->strength;
            sw_config->color_temp = color_temp_H;
            break;
        }
    }

//    BL_LOGI("img_update_lsc: %d, %d, %d\r\n", dsp2_cfg.lsc.lsc_coef_r.coef[0], dsp2_cfg.lsc.lsc_coef_r.coef[1],
//        dsp2_cfg.lsc.lsc_coef_r.coef[2]);

    return 0;
}

int calc_ccm_sw_config_by_color_temp(BL_COLOR_TEMP color_temp, DSP2_CCM_PARAM *sw_config)
{
    int container_idx, i, value;
    int tbl_num = get_ccm_sw_tbl_num();
    BL_COLOR_TEMP color_temp_L, color_temp_H;
    DSP2_CCM_PARAM *sw_param_L, *sw_param_H;
    intpl_point_t point_L, point_H;

    if (tbl_num == 0) {
        return -1;
    }

    for (container_idx = 0; container_idx < (tbl_num - 1); container_idx++) {

        img_param_sw_get_ccm(container_idx, &sw_param_L);
        img_param_sw_get_ccm(container_idx + 1, &sw_param_H);

        color_temp_L = sw_param_L->color_temp;
        color_temp_H = sw_param_H->color_temp;

        if (color_temp >= color_temp_L && color_temp <= color_temp_H) {
            /* now we get the range of color temp */
            for (i = 0; i < CCM_COEF_NUM; i++) {
                /* interpolate each coef of CCM */
                point_L = create_intpl_point(color_temp_L, sw_param_L->coef[i]);
                point_H = create_intpl_point(color_temp_H, sw_param_H->coef[i]);
                linear_interpolate(&point_L, &point_H, color_temp, &value);
                sw_config->coef[i] = value;
            }
            return 0;
        }
        else if (container_idx == 0 && color_temp < color_temp_L) {
            memcpy(sw_config, sw_param_L, sizeof(DSP2_CCM_PARAM));
            return 0;
        }
        else if (container_idx == (tbl_num - 2) && color_temp > color_temp_H) {
            memcpy(sw_config, sw_param_H, sizeof(DSP2_CCM_PARAM));
            return 0;
        }
    }

    BL_ABORT();  /* shouldn't reach here */
    return -1;
}

int calc_ccm_sw_color_weight_by_iso(BL_GAIN_DB gain, ccm_cw_t *sw_config)
{
    int param_idx, value;
    ccm_cw_t *sw_param_L, *sw_param_H;

    param_idx = getIsoIdx(gain);

    img_param_sw_get_ccm_color_weight(param_idx, &sw_param_L);
    img_param_sw_get_ccm_color_weight(param_idx + 1, &sw_param_H);

    linear_intpl_by_gain(sw_param_L->color_weight, sw_param_H->color_weight, gain, &value);
    sw_config->color_weight = value;

    return 0;
}

int calc_gamma_sw_config_by_sys_gain(BL_GAIN_DB sys_gain, DSP2_GAMMA_PARAM *sw_config)
{
    int param_idx, value;
    DSP2_GAMMA_PARAM *sw_param_L, *sw_param_H;
    int num_gamma_bias = MAX_ENTRY_NUM_AE_SYS_GAIN_AUTO;

    if (sys_gain > MAX_SYS_GAIN_TBL) {
        img_param_sw_get_gamma(num_gamma_bias - 1, &sw_config);
    } else if (sys_gain < MIN_SYS_GAIN_TBL) {
        img_param_sw_get_gamma(0, &sw_config);
    } else {
        param_idx = getSysGainIdx(sys_gain);

        img_param_sw_get_gamma(param_idx, &sw_param_L);
        img_param_sw_get_gamma(param_idx + 1, &sw_param_H);
        linear_intpl_by_gain(sw_param_L->idx, sw_param_H->idx, sys_gain, &value);
        sw_config->idx = value;
    }

    return 0;
}

int calc_wdr_sw_config_by_sys_gain(BL_GAIN_DB sys_gain, DSP2_WDR_PARAM *sw_config)
{
    int param_idx, value;
    DSP2_WDR_PARAM *sw_param_L, *sw_param_H;
    int num_wdr_tbl = MAX_ENTRY_NUM_AE_SYS_GAIN_AUTO;
    
    if (sys_gain > MAX_SYS_GAIN_TBL) {
        img_param_sw_get_wdr(num_wdr_tbl - 1, &sw_config);
    } else if (sys_gain < MIN_SYS_GAIN_TBL) {
        img_param_sw_get_wdr(0, &sw_config);
    } else {
        param_idx = getSysGainIdx(sys_gain);

        img_param_sw_get_wdr(param_idx, &sw_param_L);
        img_param_sw_get_wdr(param_idx + 1, &sw_param_H);

        linear_intpl_by_gain(sw_param_L->cs_strength, sw_param_H->cs_strength, sys_gain, &value);
        sw_config->cs_strength = value;
        linear_intpl_by_gain(sw_param_L->curve_weight, sw_param_H->curve_weight, sys_gain, &value);
        sw_config->curve_weight = value;
        linear_intpl_by_gain(sw_param_L->enh_weight, sw_param_H->enh_weight, sys_gain, &value);
        sw_config->enh_weight = value;
        linear_intpl_by_gain(sw_param_L->bright_enh_level, sw_param_H->bright_enh_level, sys_gain, &value);
        sw_config->bright_enh_level = value;
        linear_intpl_by_gain(sw_param_L->dark_enh_level, sw_param_H->dark_enh_level, sys_gain, &value);
        sw_config->dark_enh_level = value;
    }
    
    return 0;
}

static int calc_wdr_sw_lowlight_weight_by_sys_gain(BL_GAIN_DB sys_gain, wdr_lowlight_weight_t *config)
{
    int param_idx, value;
    wdr_lowlight_weight_t *param_L, *param_H;
    int num_target_tbl = MAX_ENTRY_NUM_AE_SYS_GAIN_AUTO;

    if (sys_gain > MAX_SYS_GAIN_TBL) {
        img_param_sw_get_wdr_lowlight_weight(num_target_tbl - 1, &config);
    } else if (sys_gain < MIN_SYS_GAIN_TBL) {
        img_param_sw_get_wdr_lowlight_weight(0, &config);
    } else {
        param_idx = getSysGainIdx(sys_gain);

        img_param_sw_get_wdr_lowlight_weight(param_idx, &param_L);
        img_param_sw_get_wdr_lowlight_weight(param_idx + 1, &param_H);

        linear_intpl_by_gain(param_L->idx[0], param_H->idx[0], sys_gain, &value);
        config->idx[0] = value;
        linear_intpl_by_gain(param_L->idx[1], param_H->idx[1], sys_gain, &value);
        config->idx[1] = value;
        linear_intpl_by_gain(param_L->idx[2], param_H->idx[2], sys_gain, &value);
        config->idx[2] = value;
    }

     return 0;
}

int calc_wdr_sw_lowlight_weight_idx_by_sys_gain(BL_GAIN_DB sys_gain, int hist_sum, int *idx)
{
    int value;
    wdr_lowlight_weight_t config;
    wdr_lowlight_weight_conf_t *weight_conf;
    intpl_point_t point_L, point_H;

    calc_wdr_sw_lowlight_weight_by_sys_gain(sys_gain, &config);
    img_param_sw_get_wdr_lowlight_weight_conf(&weight_conf);
     if (hist_sum <= weight_conf->thr[0]) {
        *idx = (int)config.idx[0];
    } else if (hist_sum < weight_conf->thr[1]) {
        point_L = create_intpl_point(weight_conf->thr[0], config.idx[0]);
        point_H = create_intpl_point(weight_conf->thr[1], config.idx[1]);
        linear_interpolate(&point_L, &point_H, hist_sum, &value);
        *idx = value;
    } else if (hist_sum < weight_conf->thr[2]) {
        *idx = (int)config.idx[1];
    } else if (hist_sum < weight_conf->thr[3]) {
        point_L = create_intpl_point(weight_conf->thr[2], config.idx[1]);
        point_H = create_intpl_point(weight_conf->thr[3], config.idx[2]);
        linear_interpolate(&point_L, &point_H, hist_sum, &value);
        *idx = value;
    } else {
        *idx = (int)config.idx[2];
    }
    return 0;
}

int calc_wdr_sw_tone_curve_by_idx(int idx, wdr_tone_curve_t *tone_curve)
{
    int i, value, curve_idx, num_curve;
    int ret = -1;
    int idx_L, idx_H;
    wdr_tone_curve_conf_t *curve_L, *curve_H;
    intpl_point_t point_L, point_H;

    num_curve = MAX_ENTRY_NUM_GAMMA_IDX_AUTO;

    for (curve_idx = 0; curve_idx < (num_curve - 1); curve_idx++) {

        img_param_sw_get_wdr_tone_curve_conf(curve_idx, &curve_L);
        img_param_sw_get_wdr_tone_curve_conf(curve_idx + 1, &curve_H);

        idx_L = curve_L->idx;
        idx_H = curve_H->idx;

        if (idx >= idx_L && idx <= idx_H) {
            for (i = 0; i < WDR_COEF_NUM; i++) {
                /* interpolate each coef of gamma */
                point_L = create_intpl_point(idx_L, curve_L->tone_curve.coef[i]);
                point_H = create_intpl_point(idx_H, curve_H->tone_curve.coef[i]);
                linear_interpolate(&point_L, &point_H, idx, &value);
                tone_curve->coef[i] = value;
            }
            ret = 0;
            break;
        } else if (curve_idx == 0 && idx < idx_L) {
            memcpy(tone_curve, &curve_L->tone_curve, sizeof(wdr_tone_curve_t));
            ret = 0;
            break;
        } else if (curve_idx == (num_curve - 2) && idx > idx_H) {
            memcpy(tone_curve, &curve_H->tone_curve, sizeof(wdr_tone_curve_t));
            ret = 0;
            break;
        }
    }

    return ret;
}

int calc_sat_sw_config_by_iso(BL_GAIN_DB gain, DSP2_SAT_PARAM *sw_config)
{
    int param_idx, value;
    DSP2_SAT_PARAM *sw_param_L, *sw_param_H;

    param_idx = getIsoIdx(gain);

    img_param_sw_get_sat(param_idx, &sw_param_L);
    img_param_sw_get_sat(param_idx + 1, &sw_param_H);

    linear_intpl_by_gain(sw_param_L->value, sw_param_H->value, gain, &value);
    sw_config->value = value;

    return 0;
}

int calc_yc_sw_config_by_iso(BL_GAIN_DB gain, DSP2_YC_PARAM *sw_config)
{
    int param_idx, value;
    DSP2_YC_PARAM *sw_param_L, *sw_param_H;

    param_idx = gain / GAIN_6_DB;

    img_param_sw_get_yc(param_idx, &sw_param_L);
    img_param_sw_get_yc(param_idx + 1, &sw_param_H);

    linear_intpl_by_gain(sw_param_L->brightness, sw_param_H->brightness, gain, &value);
    sw_config->brightness = value;
    linear_intpl_by_gain(sw_param_L->contrast, sw_param_H->contrast, gain, &value);
    sw_config->contrast = value;

    return 0;
}

int calc_nr_sw_config_by_iso(BL_GAIN_DB gain, DSP2_NR_PARAM *sw_config)
{
    int param_idx, value;
    DSP2_NR_PARAM *sw_param_L, *sw_param_H;

    param_idx = getIsoIdx(gain);

    img_param_sw_get_nr(param_idx, &sw_param_L);
    img_param_sw_get_nr(param_idx + 1, &sw_param_H);

    linear_intpl_by_gain(sw_param_L->strength_level, sw_param_H->strength_level, gain, &value);
    sw_config->strength_level = value;
    linear_intpl_by_gain(sw_param_L->strength_2d, sw_param_H->strength_2d, gain, &value);
    sw_config->strength_2d = value;
    linear_intpl_by_gain(sw_param_L->strength_3d, sw_param_H->strength_3d, gain, &value);
    sw_config->strength_3d = value;

    return 0;
}

int calc_ee_sw_config_by_iso(BL_GAIN_DB gain, DSP2_EE_PARAM *sw_config)
{
    int param_idx, value;
    DSP2_EE_PARAM *sw_param_L, *sw_param_H;

    param_idx = getIsoIdx(gain);

    img_param_sw_get_ee(param_idx, &sw_param_L);
    img_param_sw_get_ee(param_idx + 1, &sw_param_H);

    linear_intpl_by_gain(sw_param_L->pos_edge_strength, sw_param_H->pos_edge_strength, gain, &value);
    sw_config->pos_edge_strength = value;
    linear_intpl_by_gain(sw_param_L->neg_edge_strength, sw_param_H->neg_edge_strength, gain, &value);
    sw_config->neg_edge_strength = value;
    linear_intpl_by_gain(sw_param_L->pos_edge_ovrsht_strength, sw_param_H->pos_edge_ovrsht_strength, gain, &value);
    sw_config->pos_edge_ovrsht_strength = value;
    linear_intpl_by_gain(sw_param_L->neg_edge_ovrsht_strength, sw_param_H->neg_edge_ovrsht_strength, gain, &value);
    sw_config->neg_edge_ovrsht_strength = value;
    linear_intpl_by_gain(sw_param_L->nr_strength, sw_param_H->nr_strength, gain, &value);
    sw_config->nr_strength = value;
    linear_intpl_by_gain(sw_param_L->dir_shpness_thr, sw_param_H->dir_shpness_thr, gain, &value);
    sw_config->dir_shpness_thr = value;
    linear_intpl_by_gain(sw_param_L->no_dir_shpness_thr, sw_param_H->no_dir_shpness_thr, gain, &value);
    sw_config->no_dir_shpness_thr = value;
    linear_intpl_by_gain(sw_param_L->flat_thr, sw_param_H->flat_thr, gain, &value);
    sw_config->flat_thr = value;
    linear_intpl_by_gain(sw_param_L->texture_thr, sw_param_H->texture_thr, gain, &value);
    sw_config->texture_thr = value;
    linear_intpl_by_gain(sw_param_L->edge_thr, sw_param_H->edge_thr, gain, &value);
    sw_config->edge_thr = value;

    return 0;
}


int calc_cs_sw_config_by_iso(BL_GAIN_DB gain, DSP2_CS_PARAM *sw_config)
{
    int param_idx, value;
    DSP2_CS_PARAM *sw_param_L, *sw_param_H;

    param_idx = getIsoIdx(gain);

    img_param_sw_get_cs(param_idx, &sw_param_L);
    img_param_sw_get_cs(param_idx + 1, &sw_param_H);

    linear_intpl_by_gain(sw_param_L->strength, sw_param_H->strength, gain, &value);
    sw_config->strength = value;
    return 0;
}
/*********** sw tbl end ************************************************************************************************/
