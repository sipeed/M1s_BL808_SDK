#include <stdint.h>
#include "firmware_cs.h"
#include "bl_dsp2.h"
#include "bl_img_utils.h"
#include "img_param.h"
#include "img_param_parse.h"
#include "api_struct.h"
#include "api_dsp2_back.h"

typedef struct {
    int weight;
    int grey_thr;
} chroma_suppress_t;

static bl_dsp2_cs_conf_t         cs_reg;
static chroma_suppress_t        cs_fw;
static DSP2_CS_PARAM            cs_sw = {0};

void cs_init(void)
{
    DSP2_CS_ATTR attr;

    MM_DSP2_GetCsAttr(&attr);
    attr.csLv.strength = attr.cs[0].strength;
    MM_DSP2_SetCsAttr(&attr);

}

static int cs_sw_get_fw_register(DSP2_CS_PARAM *sw, chroma_suppress_t *fw)
{
    int tbl_num = 0, value;
    cs_trans_tbl_t *trans_tbl = NULL;
    img_param_get_cs_trans(&trans_tbl, &tbl_num);

    table_linear_interpolate(trans_tbl->strength_tbl, trans_tbl->weight_tbl, tbl_num, sw->strength, &value);
    fw->weight = value;
    table_linear_interpolate(trans_tbl->strength_tbl, trans_tbl->grey_thr_tbl, tbl_num, sw->strength, &value);
    fw->grey_thr = value;

    return 0;
}

void cs_get_sw_config(DSP2_CS_PARAM *config)
{
    int tbl_num = 0;
    cs_trans_tbl_t *trans_tbl = NULL;
    img_param_get_cs_trans(&trans_tbl, &tbl_num);

    config->strength = cs_sw.strength;
}

void cs_set_sw_config(const DSP2_CS_PARAM *config)
{
    cs_sw.strength = config->strength;
}

static void cs_get_fw_config(chroma_suppress_t *config)
{
    config->weight = cs_fw.weight;
    config->grey_thr = cs_fw.grey_thr;
}

void cs_control(const DSP2_CS_PARAM *config)
{
    int divisor;

    cs_set_sw_config(config);
    cs_sw_get_fw_register(config, &cs_fw);

    cs_reg.weight = cs_fw.weight;
    cs_reg.grey_thr = cs_fw.grey_thr;

    // ref to wdr
    divisor = (1 << (8 - 1)) - cs_fw.grey_thr;
    cs_reg.gain = ((1 << (8 - 1)) * (1 << 8) + (divisor - 1)) / divisor;

}

int cs_img_update(BL_GAIN_DB gain)
{
    DSP2_CS_PARAM sw_config;

    if (calc_cs_sw_config_by_iso(gain, &sw_config) == -1) return 0;
    cs_control(&sw_config);

    return 0;
}

int cs_img_manual(void)
{
    DSP2_CS_ATTR attr;
    DSP2_CS_PARAM sw_config;

    MM_DSP2_GetCsAttr(&attr);
    sw_config.strength = attr.csLv.strength;
    cs_control(&sw_config);

    return 0;
}

void cs_hw_update(void)
{
    bl_set_CS_conf(&cs_reg);
}

