#include <stdint.h>
#include "firmware_nr.h"
#include "bl_dsp2.h"
#include "bl_img_utils.h"
#include "img_param.h"
#include "img_param_parse.h"
#include "api_struct.h"
#include "api_dsp2_back.h"

typedef struct _noise_reduction {
    uint16_t noise_level;
    uint8_t  filt_str_2d;
    uint8_t  filt_str_3d;
} noise_reduction_t;

static bl_dsp2_nr_conf_t nr_reg;
static noise_reduction_t nr_fw;
static DSP2_NR_PARAM     nr_sw = {0};

void nr_init(void)
{
    DSP2_NR_ATTR attr;

    MM_DSP2_GetNrAttr(&attr);
    attr.nrLv.strength_level = attr.nr[0].strength_level;
    attr.nrLv.strength_2d = attr.nr[0].strength_2d;
    attr.nrLv.strength_3d = attr.nr[0].strength_3d;
    MM_DSP2_SetNrAttr(&attr);

}

static int nr_sw_get_fw_register(const DSP2_NR_PARAM *sw, noise_reduction_t *fw)
{
    fw->noise_level = sw->strength_level;
    fw->filt_str_2d = sw->strength_2d;
    fw->filt_str_3d = sw->strength_3d;

    return 0;
}

void nr_get_sw_config(DSP2_NR_PARAM *config)
{
    config->strength_level = nr_sw.strength_level;
    config->strength_2d = nr_sw.strength_2d;
    config->strength_3d = nr_sw.strength_3d;
}

void nr_set_sw_config(const DSP2_NR_PARAM *config)
{
    nr_sw.strength_level = config->strength_level;
    nr_sw.strength_2d = config->strength_2d;
    nr_sw.strength_3d = config->strength_3d;
}


static void nr_get_fw_config(noise_reduction_t *config)
{
    memcpy(config, &nr_fw, sizeof(noise_reduction_t));
}

void nr_control(const DSP2_NR_PARAM *config)
{
    nr_set_sw_config(config);
    nr_sw_get_fw_register(config, &nr_fw);

    nr_reg.noise_level = nr_fw.noise_level;
    nr_reg.filt_str_2d = nr_fw.filt_str_2d;
    nr_reg.filt_str_3d = nr_fw.filt_str_3d;
}

int nr_img_update(BL_GAIN_DB gain)
{
    DSP2_NR_PARAM sw_config;

    if (calc_nr_sw_config_by_iso(gain, &sw_config) == -1) return 0;
    nr_control(&sw_config);

    return 0;
}

int nr_img_manual(void)
{
    DSP2_NR_ATTR attr;
    DSP2_NR_PARAM sw_config;

    MM_DSP2_GetNrAttr(&attr);
    sw_config.strength_level = attr.nrLv.strength_level;
    sw_config.strength_2d = attr.nrLv.strength_2d;
    sw_config.strength_3d = attr.nrLv.strength_3d;
    nr_control(&sw_config);

    return 0;
}

void nr_hw_update(void)
{
    bl_set_NR_conf(&nr_reg);
}

