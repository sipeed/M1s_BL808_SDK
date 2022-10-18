#include <stdint.h>
#include "firmware_blc.h"
#include "bl_dsp2.h"
#include "bl_img_utils.h"
#include "img_param.h"
#include "img_param_parse.h"
#include "api_struct.h"
#include "api_dsp2_front.h"

typedef struct {
    uint32_t black_level;
} DSP2_BLC_PARAM_FW;

static DSP2_CLAMP_S      blc_reg;
static DSP2_BLC_PARAM_FW blc_fw;
static DSP2_BLC_PARAM    blc_sw = {0};

void blc_init(void)
{
    DSP2_BLC_ATTR attr;

    MM_DSP2_GetBlcAttr(&attr);
    attr.blcLv.black_level = attr.blc[0].black_level;
    MM_DSP2_SetBlcAttr(&attr);

}

static int blc_sw_get_fw_register(DSP2_BLC_PARAM *sw, DSP2_BLC_PARAM_FW *fw)
{
    fw->black_level = sw->black_level;

    return 0;
}

void blc_get_sw_config(DSP2_BLC_PARAM *config)
{
    config->black_level = blc_sw.black_level;
}

void blc_set_sw_config(const DSP2_BLC_PARAM *config)
{
    blc_sw.black_level = config->black_level;
}

static void blc_get_fw_config(DSP2_BLC_PARAM_FW *config)
{
    memcpy(config, &blc_fw, sizeof(DSP2_BLC_PARAM_FW));
}

void blc_control(const DSP2_BLC_PARAM *sw_config)
{
    blc_set_sw_config(sw_config);
    blc_sw_get_fw_register(sw_config, &blc_fw);

    blc_reg.clamp_r = blc_fw.black_level;
    blc_reg.clamp_gr = blc_fw.black_level;
    blc_reg.clamp_gb = blc_fw.black_level;
    blc_reg.clamp_b = blc_fw.black_level;

}

int blc_img_update(BL_GAIN_DB gain)
{
    DSP2_BLC_PARAM sw_config;

    if (calc_blc_sw_config_by_iso(gain, &sw_config) == -1) return 0;
    blc_control(&sw_config);

    return 0;
}

int blc_img_manual(void)
{
    DSP2_BLC_ATTR attr;
    DSP2_BLC_PARAM sw_config;

    MM_DSP2_GetBlcAttr(&attr);
    sw_config.black_level = attr.blcLv.black_level;
    blc_control(&sw_config);

    return 0;
}

void blc_hw_update(void)
{
    bl_set_BLC_ob(blc_reg.clamp_r);
}

