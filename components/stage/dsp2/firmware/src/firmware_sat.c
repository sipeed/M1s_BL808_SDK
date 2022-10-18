#include <stdint.h>
#include "firmware_sat.h"
#include "bl_dsp2.h"
#include "bl_img_utils.h"
#include "img_param.h"
#include "img_param_parse.h"
#include "api_struct.h"
#include "api_dsp2_back.h"

typedef struct {
    uint8_t value;
} sat_param_fw_t;

static uint8_t          sat_reg;
static sat_param_fw_t   sat_fw;
static DSP2_SAT_PARAM   sat_sw = {0};

void sat_init(void)
{
    DSP2_SAT_ATTR attr;

    MM_DSP2_GetSaturationAttr(&attr);
    attr.satLv.value = attr.sat[0].value;
    MM_DSP2_SetSaturationAttr(&attr);
}

static int sat_sw_get_fw_register(DSP2_SAT_PARAM *sw, sat_param_fw_t *fw)
{
    fw->value = sw->value;

    return 0;
}

void sat_get_sw_config(DSP2_SAT_PARAM *config)
{
    config->value = sat_sw.value;
}

void sat_set_sw_config(const DSP2_SAT_PARAM *config)
{
    sat_sw.value = config->value;
}

static void sat_get_fw_config(sat_param_fw_t *config)
{
    config->value = sat_fw.value;
}

void sat_control(const DSP2_SAT_PARAM *config)
{
    sat_set_sw_config(config);
    sat_sw_get_fw_register(config, &sat_fw);

    sat_reg = sat_fw.value;

}

int sat_img_update(BL_GAIN_DB gain)
{
    DSP2_SAT_PARAM sw_config;

    if (calc_sat_sw_config_by_iso(gain, &sw_config) == -1) return 0;
    sat_control(&sw_config);

    return 0;
}

int sat_img_manual(void)
{
    DSP2_SAT_ATTR attr;
    DSP2_SAT_PARAM sw_config;

    MM_DSP2_GetSaturationAttr(&attr);
    sw_config.value = attr.satLv.value;
    sat_control(&sw_config);

    return 0;
}

void sat_hw_update(void)
{
    bl_dsp2_set_saturation(sat_reg);
}

