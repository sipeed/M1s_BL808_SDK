#include <stdint.h>
#include "firmware_ccm.h"
#include "bl_dsp2.h"
#include "bl_img_utils.h"
#include "img_param.h"
#include "img_param_parse.h"
#include "api_struct.h"
#include "api_dsp2_back.h"

#define COLOR_WEIGHT_FRAC_BW         (7)
#define COLOR_WEIGHT_UNITY           (1 << COLOR_WEIGHT_FRAC_BW)
#define CCM_FRAC_BW                  (9)
#define CCM_UNITY                    (1 << CCM_FRAC_BW)

typedef struct {
    ccm_t ccm;
    BL_COLOR_TEMP color_temp;
} color_corr_t;

/* TODO: optimize mem usage*/
static bl_dsp2_ccm_coef_s ccm_reg;
static color_corr_t   ccm_fw;
static DSP2_CCM_PARAM ccm_sw = {0};
static ccm_cw_t ccm_sw_cw = {0};

void ccm_init(void)
{
    int i = 0;
    DSP2_CCM_ATTR attr;

    MM_DSP2_GetCcmAttr(&attr);
    for(i = 0; i < CCM_COEF_NUM; i++) {
        attr.ccmLv.coef[i] = attr.ccm[0].coef[i];
    }
    attr.ccmLv.color_temp = attr.ccm[0].color_temp;
    attr.ccmCwLv.color_weight = attr.ccmCw[0].color_weight;
    MM_DSP2_SetCcmAttr(&attr);

}

static int ccm_sw_get_fw_register(DSP2_CCM_PARAM *sw, color_corr_t *fw)
{
    memcpy(&fw->ccm.ccm_coef, &sw->coef, sizeof(ccm_t));
    fw->color_temp = sw->color_temp;

    return 0;
}

void ccm_get_sw_config(DSP2_CCM_PARAM *config)
{
    memcpy(config, &ccm_sw, sizeof(DSP2_CCM_PARAM));
    config->color_temp = ccm_sw.color_temp;
}

void ccm_set_sw_config(const DSP2_CCM_PARAM *config)
{
    memcpy(&ccm_sw, config, sizeof(DSP2_CCM_PARAM));
}

void ccm_get_sw_cw_config(ccm_cw_t *config)
{
    memcpy(config, &ccm_sw_cw, sizeof(ccm_cw_t));
}

void ccm_set_sw_cw_config(const ccm_cw_t *config)
{
    memcpy(&ccm_sw_cw, config, sizeof(ccm_cw_t));
}

static void ccm_get_fw_config(color_corr_t *config)
{
    memcpy(config, &ccm_fw, sizeof(color_corr_t));
}

void ccm_control(const DSP2_CCM_PARAM *sw_config, const ccm_cw_t *sw_cw_config)
{
    int i = 0, temp_val = 0;
    ccm_set_sw_config(sw_config);
    ccm_set_sw_cw_config(sw_cw_config);
    ccm_sw_get_fw_register(sw_config, &ccm_fw);

    if (sw_cw_config->color_weight == COLOR_WEIGHT_UNITY) {
        for(i = 0; i < CCM_COEF_NUM; i++) {
            ccm_reg.coef[i] = ccm_fw.ccm.ccm_coef[i];// int vs int16
        }
    } else {
        for(i = 0; i < CCM_COEF_NUM; i++) {
            temp_val = ccm_fw.ccm.ccm_coef[i] * sw_cw_config->color_weight + (1 << (COLOR_WEIGHT_FRAC_BW - 1));
            if ((i == 0) || (i == 4) ||(i == 8)) {
                ccm_reg.coef[i] = (temp_val + CCM_UNITY * (COLOR_WEIGHT_UNITY - sw_cw_config->color_weight)) >> COLOR_WEIGHT_FRAC_BW;
            } else {
                ccm_reg.coef[i] = (temp_val) >> COLOR_WEIGHT_FRAC_BW;
            }
        }
    }
}

int ccm_img_update(BL_COLOR_TEMP color_temp, BL_GAIN_DB gain)
{
    DSP2_CCM_PARAM sw_config;
    ccm_cw_t sw_cw_config;

    if (calc_ccm_sw_config_by_color_temp(color_temp, &sw_config) == -1) return 0;
    if (calc_ccm_sw_color_weight_by_iso(gain, &sw_cw_config) == -1) return 0;

    ccm_control(&sw_config, &sw_cw_config);

    return 0;
}

int ccm_img_manual(void)
{
    int i = 0;
    DSP2_CCM_ATTR attr;
    DSP2_CCM_PARAM sw_config;
    ccm_cw_t sw_cw_config;

    MM_DSP2_GetCcmAttr(&attr);
    sw_cw_config.color_weight = attr.ccmCwLv.color_weight;
    for(i = 0; i < CCM_COEF_NUM; i++) {
        sw_config.coef[i] = attr.ccmLv.coef[i];
    }
    sw_config.color_temp = attr.ccmLv.color_temp;
    ccm_control(&sw_config, &sw_cw_config);

    return 0;
}

void ccm_hw_update(void)
{
    bl_set_CCM_conf(&ccm_reg);
}

