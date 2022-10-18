#include <stdint.h>
#include "firmware_bnr.h"
#include "bl_dsp2.h"
#include "bl_img_utils.h"
#include "img_param.h"
#include "img_param_parse.h"
#include "api_struct.h"
#include "api_dsp2_front.h"

#define PIXEL_BW                  (12)
#define PIXEL_MAX                 ((1 << PIXEL_BW) - 1)
#define LPF_WEIGHT_PRECISION      (4)
#define LPF_WEIGHT_MAX            (1 << LPF_WEIGHT_PRECISION)
#define TH_BW                     (10)
#define TH_MAX                    ((1 << TH_BW) - 1)
#define TH_SLOPE_PRECISION        (8)
#define SLOPE_BW                  (12)
#define SLOPE_MAX                 ((1 << SLOPE_BW) - 1)
#define SLOPE_GAIN_PRECISION      (4)
#define WEIGHT_INI_MAX            (15)
#define FB_LEVEL_BW               (3)
#define FB_LEVEL_MAX              ((1 << FB_LEVEL_BW) - 1)
#define BNR_WEIGHT_PRECISION      (6)
#define BNR_WEIGHT_MAX            (1 << BNR_WEIGHT_PRECISION)

#define BNR_STRENGTH_PRECISION    (6)
#define BNR_STRENGTH_HALF         (1 << (BNR_STRENGTH_PRECISION - 1))
#define TH_SLOPE_ADJUST_PRECISION (6)

typedef struct {
    uint16_t strength;
    uint16_t bnr_weight;
    uint16_t max_bnr_weight;
    uint16_t th_base_r;
    uint16_t th_base_g;
    uint16_t th_base_b;
    uint16_t th_slope_r_adj;
    uint16_t th_slope_g_adj;
    uint16_t th_slope_b_adj;
} bnr_fw_config_t;

typedef struct
{
    uint16_t bnr_weight;
    uint16_t lpf_weight;
    bl_dsp2_bnr_thr_t bnr_thr;
    bl_dsp2_bnr_fb_t  bnr_fb;
} bnr_reg_internal_t;

/* TODO: optimize mem usage*/
static bnr_reg_internal_t bnr_reg;
static bnr_fw_config_t    bnr_fw;
static DSP2_BNR_PARAM     bnr_sw = {0};
static uint32_t           iso_debug;

void bnr_init(void)
{
    bnr_reg.bnr_thr.slope_gain = 21;
    bnr_reg.bnr_fb.fb_level = 5;

    DSP2_BNR_ATTR attr;

    MM_DSP2_GetBnrAttr(&attr);
    attr.bnrLv.strength = attr.bnr[0].strength;
    MM_DSP2_SetBnrAttr(&attr);
}

static int bnr_sw_get_fw_register(DSP2_BNR_PARAM *sw, bnr_fw_config_t *fw)
{
    fw->strength = sw->strength;
    fw->bnr_weight = 32;
    fw->max_bnr_weight = 32;
    fw->th_base_r = 15;
    fw->th_base_g = 15;
    fw->th_base_b = 15;
    fw->th_slope_r_adj = 20;
    fw->th_slope_g_adj = 20;
    fw->th_slope_b_adj = 20;
    
    return 0;
}

void bnr_get_sw_config(DSP2_BNR_PARAM *config)
{
    config->strength = bnr_sw.strength;
}

void bnr_set_sw_config(const DSP2_BNR_PARAM *config)
{
    bnr_sw.strength = config->strength;
}

void bnr_set_config(const bnr_fw_config_t *config)
{
    memcpy(&bnr_fw, config, sizeof(bnr_fw_config_t));
}

void bnr_get_config(bnr_fw_config_t *config)
{
    config->strength = bnr_fw.strength;
    config->bnr_weight = bnr_fw.bnr_weight;
    config->max_bnr_weight = bnr_fw.max_bnr_weight;
    config->th_base_r = bnr_fw.th_base_r;
    config->th_base_g = bnr_fw.th_base_g;
    config->th_base_b = bnr_fw.th_base_b;
    config->th_slope_r_adj = bnr_fw.th_slope_r_adj;
    config->th_slope_g_adj = bnr_fw.th_slope_g_adj;
    config->th_slope_b_adj = bnr_fw.th_slope_b_adj;

}

void bnr_control(DSP2_BNR_PARAM *sw_config)
{
    bnr_set_sw_config(sw_config);
    bnr_sw_get_fw_register(sw_config, &bnr_fw);

    // adjust ISO based on BNR strength
    uint16_t iso_adj = sw_config->strength * 4096 / 100;//(iso * bnr_fw.fw_bnr_strength) >> (BNR_STRENGTH_PRECISION - 1);

    // strength and ISO adaptive setting
    bnr_reg.bnr_weight = MIN(bnr_fw.max_bnr_weight, bnr_fw.bnr_weight + (iso_adj >> 4));
    bnr_reg.lpf_weight = MIN(16, (MAX(0, bnr_fw.bnr_weight - BNR_STRENGTH_HALF) >> 1) + (iso_adj >> 8));
    bnr_reg.bnr_thr.th_base_r  = MIN(256, ((bnr_fw.th_base_r * bnr_fw.bnr_weight) >> (BNR_STRENGTH_PRECISION - 1)) + (iso_adj >> 5));
    bnr_reg.bnr_thr.th_base_g  = MIN(256, ((bnr_fw.th_base_g * bnr_fw.bnr_weight) >> (BNR_STRENGTH_PRECISION - 1)) + (iso_adj >> 5));
    bnr_reg.bnr_thr.th_base_b  = MIN(256, ((bnr_fw.th_base_b * bnr_fw.bnr_weight) >> (BNR_STRENGTH_PRECISION - 1)) + (iso_adj >> 5));

    // general default setting
    bnr_reg.bnr_thr.th_slope_r = (bnr_reg.bnr_thr.th_base_r * bnr_fw.th_slope_r_adj) >> (TH_SLOPE_ADJUST_PRECISION - 1);
    bnr_reg.bnr_thr.th_slope_g = (bnr_reg.bnr_thr.th_base_g * bnr_fw.th_slope_g_adj) >> (TH_SLOPE_ADJUST_PRECISION - 1);
    bnr_reg.bnr_thr.th_slope_b = (bnr_reg.bnr_thr.th_base_b * bnr_fw.th_slope_b_adj) >> (TH_SLOPE_ADJUST_PRECISION - 1);
    bnr_reg.bnr_fb.fb_lpf_weight = bnr_reg.lpf_weight >> 1;

}

int bnr_img_update(BL_GAIN_DB gain)
{
    DSP2_BNR_PARAM sw_config;

    if (calc_bnr_sw_config_by_iso(gain, &sw_config) == -1) return 0;
    bnr_control(&sw_config); 

    return 0;
}

int bnr_img_manual(void)
{
    DSP2_BNR_ATTR attr;
    DSP2_BNR_PARAM sw_config;

    MM_DSP2_GetBnrAttr(&attr);
    sw_config.strength = attr.bnrLv.strength;
    bnr_control(&sw_config);

    return 0;
}

void bnr_hw_update(void)
{
    bl_set_BNR_weight(bnr_reg.bnr_weight);
    bl_set_BNR_lpf_weight(bnr_reg.lpf_weight);
    bl_set_BNR_threshold(&(bnr_reg.bnr_thr));
    bl_set_BNR_fallback(&(bnr_reg.bnr_fb));
}

