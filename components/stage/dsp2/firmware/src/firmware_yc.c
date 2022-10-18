#include <stdint.h>
#include "firmware_yc.h"
#include "bl_dsp2.h"
#include "bl_img_utils.h"
#include "img_param.h"
#include "img_param_parse.h"
#include "api_struct.h"
#include "api_dsp2_back.h"

typedef struct {
    uint8_t brightness;
    uint8_t contrast;
} yc_param_fw_t;

static bl_dsp2_yc_conf_t     yc_reg;
static yc_param_fw_t        yc_fw;
static DSP2_YC_PARAM        yc_sw = {0};

void yc_init(void)
{
    DSP2_YC_ATTR attr;

    MM_DSP2_GetYcAttr(&attr);
    attr.ycLv.contrast = attr.yc[0].contrast;
    attr.ycLv.brightness = attr.yc[0].brightness;
    MM_DSP2_SetYcAttr(&attr);
}

static int yc_sw_get_fw_register(DSP2_YC_PARAM *sw, yc_param_fw_t *fw)
{
    fw->brightness = sw->brightness;
    fw->contrast = sw->contrast;

    return 0;
}

void yc_get_sw_config(DSP2_YC_PARAM *config)
{
    config->brightness = yc_sw.brightness;
    config->contrast = yc_sw.contrast;
}

void yc_set_sw_config(const DSP2_YC_PARAM *config)
{
    yc_sw.brightness = config->brightness;
    yc_sw.contrast = config->contrast;
}

static void yc_get_fw_config(yc_param_fw_t *config)
{
    config->brightness = yc_fw.brightness;
    config->contrast = yc_fw.contrast;
}

void yc_control(const DSP2_YC_PARAM *config)
{
    yc_set_sw_config(config);
    yc_sw_get_fw_register(config, &yc_fw);

    yc_reg.brightness = yc_fw.brightness;
    yc_reg.contrast = yc_fw.contrast;

}

int yc_img_update(BL_GAIN_DB gain)
{
    DSP2_YC_PARAM sw_config;

    if (calc_yc_sw_config_by_iso(gain, &sw_config) == -1) return 0;
    yc_control(&sw_config);

    return 0;
}

int yc_img_manual(void)
{
    DSP2_YC_ATTR attr;
    DSP2_YC_PARAM sw_config;

    MM_DSP2_GetYcAttr(&attr);
    sw_config.contrast = attr.ycLv.contrast;
    sw_config.brightness = attr.ycLv.brightness;
    yc_control(&sw_config);

    return 0;
}

void yc_hw_update(void)
{
    bl_set_YC_conf(&yc_reg);
}

