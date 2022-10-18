#include <stdint.h>
#include "firmware_lsc.h"
#include "bl_dsp2.h"
#include "bl_img_utils.h"
#include "img_param.h"
#include "img_param_parse.h"
#include "api_struct.h"
#include "api_dsp2_front.h"

typedef struct {
    int strength;
    lsc_coef_t lsc_coef_r;
    lsc_coef_t lsc_coef_g;
    lsc_coef_t lsc_coef_b;
    lsc_max_t lsc_max;
    BL_COLOR_TEMP color_temp;
} lsc_param_fw_t;

static bl_dsp2_lsc_conf_t lsc_reg;
static lsc_param_fw_t lsc_fw;
static DSP2_LSC_PARAM lsc_sw = {0};

void lsc_init(void)
{
    DSP2_LSC_ATTR attr;

    MM_DSP2_GetLscAttr(&attr);
    attr.lscLv.strength = attr.lsc[0].strength;
    attr.lscLv.color_temp = attr.lsc[0].color_temp;
    MM_DSP2_SetLscAttr(&attr);

}

void lsc_get_sw_config(DSP2_LSC_PARAM *config)
{
    memcpy(config, &lsc_sw, sizeof(DSP2_LSC_PARAM));
}

void lsc_set_sw_config(const DSP2_LSC_PARAM *config)
{
    memcpy(&lsc_sw, config, sizeof(DSP2_LSC_PARAM));
}

static void lsc_set_fw_config(const lsc_cal_t *config)
{
    lsc_fw.strength = config->strength;
    memcpy(&lsc_fw.lsc_coef_r, &config->lsc_coef_r, sizeof(lsc_coef_t));
    memcpy(&lsc_fw.lsc_coef_g, &config->lsc_coef_g, sizeof(lsc_coef_t));
    memcpy(&lsc_fw.lsc_coef_b, &config->lsc_coef_b, sizeof(lsc_coef_t));
    memcpy(&lsc_fw.lsc_max, &config->lsc_max, sizeof(lsc_max_t));
}

static void lsc_get_fw_config(lsc_param_fw_t *config)
{
    config->strength = lsc_fw.strength;
    memcpy(&config->lsc_coef_r, &lsc_fw.lsc_coef_r, sizeof(lsc_coef_t));
    memcpy(&config->lsc_coef_g, &lsc_fw.lsc_coef_g, sizeof(lsc_coef_t));
    memcpy(&config->lsc_coef_b, &lsc_fw.lsc_coef_b, sizeof(lsc_coef_t));
    memcpy(&config->lsc_max, &lsc_fw.lsc_max, sizeof(lsc_max_t));
}

void lsc_control(const BL_COLOR_TEMP color_temp, const DSP2_LSC_PARAM *sw_config)
{
    int i;
    lsc_cal_t cal_config;

    lsc_set_sw_config(sw_config);
    calc_lsc_cal_by_color_temp(color_temp, &cal_config);
    lsc_set_fw_config(&cal_config);

    lsc_fw.strength = sw_config->strength;
    lsc_fw.color_temp = sw_config->color_temp;
    
    for(i = 0; i < LSC_COEF_NUM; i++){
        if (i != 2 ) {
            lsc_reg.coef.r.coef[i] = lsc_fw.lsc_coef_r.coef[i]*lsc_fw.strength*0.01;
            lsc_reg.coef.g.coef[i] = lsc_fw.lsc_coef_g.coef[i]*lsc_fw.strength*0.01;
            lsc_reg.coef.b.coef[i] = lsc_fw.lsc_coef_b.coef[i]*lsc_fw.strength*0.01;
        } else {
            lsc_reg.coef.r.coef[i] = (lsc_fw.lsc_max.max_r - lsc_fw.lsc_coef_r.coef[i])*(100 - lsc_fw.strength)*0.01 + lsc_fw.lsc_coef_r.coef[i];
            lsc_reg.coef.g.coef[i] = (lsc_fw.lsc_max.max_g - lsc_fw.lsc_coef_g.coef[i])*(100 - lsc_fw.strength)*0.01 + lsc_fw.lsc_coef_g.coef[i];
            lsc_reg.coef.b.coef[i] = (lsc_fw.lsc_max.max_b - lsc_fw.lsc_coef_b.coef[i])*(100 - lsc_fw.strength)*0.01 + lsc_fw.lsc_coef_b.coef[i];
        }

    }
    lsc_reg.max.max_r = lsc_fw.lsc_max.max_r;
    lsc_reg.max.max_g = lsc_fw.lsc_max.max_g;
    lsc_reg.max.max_b = lsc_fw.lsc_max.max_b;
}

int lsc_img_update(BL_COLOR_TEMP color_temp)
{
    DSP2_LSC_PARAM sw_config;

    if (calc_lsc_sw_config_by_color_temp(color_temp, &sw_config) == -1) return 0;
    lsc_control(color_temp, &sw_config);

    return 0;
}

int lsc_img_manual(BL_COLOR_TEMP color_temp)
{
    DSP2_LSC_ATTR attr;
    DSP2_LSC_PARAM sw_config;

    MM_DSP2_GetLscAttr(&attr);
    sw_config.strength = attr.lscLv.strength;
    sw_config.color_temp = attr.lscLv.color_temp;
    lsc_control(color_temp, &sw_config);

    return 0;
}

void lsc_hw_update(void)
{
    bl_set_LSC_conf(&lsc_reg);
}

