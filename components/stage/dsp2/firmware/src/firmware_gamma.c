#include <stdint.h>
#include "firmware_gamma.h"
#include "bl_dsp2.h"
#include "bl_img_utils.h"
#include "img_param.h"
#include "img_param_parse.h"
#include "api_struct.h"
#include "api_dsp2_back.h"

typedef struct {
    gamma_curve_t gamma_curve;
    int idx;
} gamma_param_fw_t;

static bl_dsp2_gamma_curve_t gamma_reg;
static gamma_param_fw_t     gamma_fw;
static DSP2_GAMMA_PARAM gamma_sw = {0};

void gamma_init(void)
{
    DSP2_GAMMA_ATTR attr;

    MM_DSP2_GetGammaAttr(&attr);
    attr.gammaLv.idx = attr.gamma[0].idx;
    MM_DSP2_SetGammaAttr(&attr);

}

static int gamma_sw_get_fw_register(DSP2_GAMMA_PARAM *sw, gamma_param_fw_t *fw)
{
    gamma_cal_t cal_config;

    calc_gamma_cal_by_idx(sw->idx, &cal_config);
    memcpy(&fw->gamma_curve , &cal_config.gamma_curve, sizeof(gamma_curve_t));
    fw->idx = sw->idx;

    return 0;
}

void gamma_get_sw_config(DSP2_GAMMA_PARAM *config)
{

    config->idx = gamma_sw.idx;
}

void gamma_set_sw_config(const DSP2_GAMMA_PARAM *config)
{
    gamma_sw.idx = config->idx;
}

static void gamma_get_fw_config(gamma_param_fw_t *config)
{
    memcpy(&config->gamma_curve, &gamma_fw.gamma_curve, sizeof(gamma_curve_t));
}

void gamma_control(const DSP2_GAMMA_PARAM *sw_config)
{
    gamma_set_sw_config(sw_config);
    gamma_sw_get_fw_register(sw_config, &gamma_fw);

    memcpy(gamma_reg.coef, &gamma_fw.gamma_curve, sizeof(gamma_curve_t));
}

int gamma_img_update(BL_GAIN_DB sys_gain)
{
    DSP2_GAMMA_PARAM sw_config;

    if (calc_gamma_sw_config_by_sys_gain(sys_gain, &sw_config) == -1) return 0;
    gamma_control(&sw_config); 

    return 0;
}

int gamma_img_manual(void)
{
    int i = 0;
    DSP2_GAMMA_ATTR attr;
    DSP2_GAMMA_PARAM sw_config;

    MM_DSP2_GetGammaAttr(&attr);
    sw_config.idx = attr.gammaLv.idx;
    gamma_control(&sw_config);

    return 0;
}

void gamma_hw_update(void)
{
    bl_set_GAMMA_curve(&(gamma_reg.coef));
}

