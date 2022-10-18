#include <stdint.h>
#include "wdr_algo.h"
#include "firmware_wdr.h"
#include "bl_dsp2.h"
#include "bl_img_utils.h"
#include "img_param.h"
#include "img_param_parse.h"
#include "api_struct.h"
#include "api_dsp2_back.h"

static wdr_fw_config_t    wdr_fw;
static DSP2_WDR_PARAM     wdr_sw = {0};

static void wdr_hw_init(void)
{
    bl_dsp2_wdr_sub_state_t state;

    state.cs_en = ENABLE;
    state.curve_en = ENABLE;
    state.enh_en = ENABLE;
    bl_set_WDR_sub_state(&state);

}

int wdr_init()
{
    wdr_algo_set_reg_default();
    wdr_algo_fw_param_init();
    wdr_hw_init();

    DSP2_WDR_ATTR attr;

    MM_DSP2_GetWdrAttr(&attr);
    attr.wdrLv.cs_strength = attr.wdr[0].cs_strength;
    attr.wdrLv.curve_weight = attr.wdr[0].curve_weight;
    attr.wdrLv.enh_weight = attr.wdr[0].enh_weight;
    attr.wdrLv.bright_enh_level = attr.wdr[0].bright_enh_level;
    attr.wdrLv.dark_enh_level = attr.wdr[0].dark_enh_level;
    MM_DSP2_SetWdrAttr(&attr);

    return 0;
}

static int wdr_sw_get_fw_register(const DSP2_WDR_PARAM *sw, wdr_fw_config_t *fw)
{
    int tbl_num = 0, value = 0;
    wdr_trans_tbl_t *trans_tbl = NULL;
    img_param_get_wdr_trans((const wdr_trans_tbl_t **)&trans_tbl, &tbl_num);

    table_linear_interpolate(trans_tbl->cs_strength_tbl, trans_tbl->cs_weight_tbl, tbl_num, sw->cs_strength, &value);
    fw->param.cs_weight = value;
    table_linear_interpolate(trans_tbl->cs_strength_tbl, trans_tbl->cs_grey_thr_tbl, tbl_num, sw->cs_strength, &value);
    fw->param.cs_grey_thr = value;
    
    fw->param.curve_weight = sw->curve_weight;
    fw->param.enh_weight = sw->enh_weight;
    fw->param.bright_enh_level = sw->bright_enh_level;
    fw->param.dark_enh_level = sw->dark_enh_level;

    return 0;
}

void wdr_get_sw_config(DSP2_WDR_PARAM *config)
{
    config->cs_strength = wdr_sw.cs_strength;
    config->curve_weight = wdr_sw.curve_weight;
    config->enh_weight = wdr_sw.enh_weight;
    config->bright_enh_level = wdr_sw.bright_enh_level;
    config->dark_enh_level = wdr_sw.dark_enh_level;
}

void wdr_set_sw_config(const DSP2_WDR_PARAM *config)
{
    wdr_sw.cs_strength = config->cs_strength;
    wdr_sw.curve_weight = config->curve_weight;
    wdr_sw.enh_weight = config->enh_weight;
    wdr_sw.bright_enh_level = config->bright_enh_level;
    wdr_sw.dark_enh_level = config->dark_enh_level;
}

static void wdr_get_fw_config(wdr_fw_config_t *config)
{
    memcpy(config, &wdr_fw, sizeof(wdr_fw_config_t));
}

int wdr_control(const DSP2_WDR_PARAM *config)
{
    int ret = 0;

    wdr_set_sw_config(config);
    wdr_sw_get_fw_register(config, &wdr_fw);
    ret = wdr_algo_control(&wdr_fw);

    return ret;
}

int wdr_img_update(BL_GAIN_DB sys_gain)
{
    DSP2_WDR_PARAM sw_config;

    wdr_fw.sys_gain_db = sys_gain;
    if (calc_wdr_sw_config_by_sys_gain(sys_gain, &sw_config) == -1) return 0;
    wdr_control(&sw_config);

    return 0;
}

int wdr_img_manual(void)
{
    int i = 0;
    DSP2_WDR_ATTR attr;
    DSP2_WDR_PARAM sw_config;

    MM_DSP2_GetWdrAttr(&attr);
    sw_config.cs_strength = attr.wdrLv.cs_strength;
    sw_config.curve_weight = attr.wdrLv.curve_weight;
    sw_config.enh_weight = attr.wdrLv.enh_weight;
    sw_config.bright_enh_level = attr.wdrLv.bright_enh_level;
    sw_config.dark_enh_level = attr.wdrLv.dark_enh_level;
    wdr_control(&sw_config);

    return 0;
}

void wdr_hw_update(void)
{
    wdr_algo_conf_t conf;

    wdr_algo_get_conf(&conf);

    bl_set_WDR_cs(&conf.cs);
    bl_set_WDR_curve(&conf.curve);
    bl_set_WDR_curve_weight(conf.curve_weight);
    bl_set_WDR_enh(&conf.enh);
}

