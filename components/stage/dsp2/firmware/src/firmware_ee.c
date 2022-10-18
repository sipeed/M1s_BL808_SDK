#include <stdint.h>
#include "firmware_ee.h"
#include "bl_dsp2.h"
#include "bl_img_utils.h"
#include "img_param.h"
#include "img_param_parse.h"
#include "api_struct.h"
#include "api_dsp2_back.h"

typedef struct {
    uint8_t posEdgeStr;
    uint8_t negEdgeStr;
    uint8_t posEdgeOvrshtStr;
    uint8_t negEdgeOvrshtStr;
    uint8_t nrStr;
    uint8_t dirShpnessThresh;
    uint8_t noDirShpnessThresh;
    uint8_t flatThresh;
    uint16_t textureThresh;
    uint16_t edgeThresh;
} edge_enhance_t;

typedef struct {
    DSP2_EE_Thresh_Type thr;
    DSP2_EE_Str_Type str;
    DSP2_EE_LUMA_WEIGHT luma_weight;
} ee_reg_internal_t;

/* TODO: optimize mem usage*/
static ee_reg_internal_t ee_reg;
static ee_luma_wgt_t     ee_fw_luma_weight;
static edge_enhance_t    ee_fw;
static DSP2_EE_PARAM     ee_sw = {0};
static uint8_t luma_wgt_update_flag = 0;

void ee_init(void)
{
    DSP2_EE_ATTR attr;

    MM_DSP2_GetEeAttr(&attr);
    attr.eeLv.pos_edge_strength         = attr.ee[0].pos_edge_strength;
    attr.eeLv.neg_edge_strength         = attr.ee[0].neg_edge_strength;
    attr.eeLv.pos_edge_ovrsht_strength  = attr.ee[0].pos_edge_ovrsht_strength;
    attr.eeLv.neg_edge_ovrsht_strength  = attr.ee[0].neg_edge_ovrsht_strength;
    attr.eeLv.nr_strength               = attr.ee[0].nr_strength;
    attr.eeLv.dir_shpness_thr        = attr.ee[0].dir_shpness_thr;
    attr.eeLv.no_dir_shpness_thr     = attr.ee[0].no_dir_shpness_thr;
    attr.eeLv.flat_thr               = attr.ee[0].flat_thr;
    attr.eeLv.texture_thr            = attr.ee[0].texture_thr;
    attr.eeLv.edge_thr               = attr.ee[0].edge_thr;
    MM_DSP2_SetEeAttr(&attr);

}

static int ee_sw_get_fw_register(DSP2_EE_PARAM *sw, edge_enhance_t *fw)
{
    fw->posEdgeStr          = sw->pos_edge_strength;
    fw->negEdgeStr          = sw->neg_edge_strength;
    fw->posEdgeOvrshtStr    = sw->pos_edge_ovrsht_strength;
    fw->negEdgeOvrshtStr    = sw->neg_edge_ovrsht_strength;
    fw->nrStr               = sw->nr_strength;
    fw->dirShpnessThresh    = sw->dir_shpness_thr;
    fw->noDirShpnessThresh  = sw->no_dir_shpness_thr;
    fw->flatThresh          = sw->flat_thr;
    fw->textureThresh       = sw->texture_thr;
    fw->edgeThresh          = sw->edge_thr;

    return 0;
}

void ee_get_sw_config(DSP2_EE_PARAM *config)
{
    config->pos_edge_strength = ee_sw.pos_edge_strength;
    config->neg_edge_strength = ee_sw.neg_edge_strength;
    config->pos_edge_ovrsht_strength = ee_sw.pos_edge_ovrsht_strength; 
    config->neg_edge_ovrsht_strength = ee_sw.neg_edge_ovrsht_strength;
    config->nr_strength = ee_sw.nr_strength;
    config->dir_shpness_thr = ee_sw.dir_shpness_thr;
    config->no_dir_shpness_thr = ee_sw.no_dir_shpness_thr;
    config->flat_thr = ee_sw.flat_thr;
    config->texture_thr = ee_sw.texture_thr;
    config->edge_thr = ee_sw.edge_thr;

}

void ee_set_sw_config(const DSP2_EE_PARAM *config)
{
    ee_sw.pos_edge_strength = config->pos_edge_strength;
    ee_sw.neg_edge_strength = config->neg_edge_strength;
    ee_sw.pos_edge_ovrsht_strength = config->pos_edge_ovrsht_strength; 
    ee_sw.neg_edge_ovrsht_strength = config->neg_edge_ovrsht_strength;
    ee_sw.nr_strength = config->nr_strength;
    ee_sw.dir_shpness_thr = config->dir_shpness_thr;
    ee_sw.no_dir_shpness_thr = config->no_dir_shpness_thr;
    ee_sw.flat_thr = config->flat_thr;
    ee_sw.texture_thr = config->texture_thr;
    ee_sw.edge_thr = config->edge_thr;
}

static void ee_get_fw_config(edge_enhance_t *config)
{
    memcpy(config, &ee_fw, sizeof(edge_enhance_t));
}

void ee_control(const DSP2_EE_PARAM *config)
{
    const DSP2_EE_LUMA_WEIGHT lumaWgt = {0};

    ee_set_sw_config(config);
    ee_sw_get_fw_register(config, &ee_fw);

    ee_reg.str.posEdgeStr = ee_fw.posEdgeStr;
    ee_reg.str.negEdgeStr = ee_fw.negEdgeStr;
    ee_reg.str.posEdgeOvrshtStr = ee_fw.posEdgeOvrshtStr;
    ee_reg.str.negEdgeOvrshtStr = ee_fw.negEdgeOvrshtStr;
    ee_reg.str.nrStr = ee_fw.nrStr;
    ee_reg.thr.dirShpnessThresh = ee_fw.dirShpnessThresh;
    ee_reg.thr.noDirShpnessThresh = ee_fw.noDirShpnessThresh;
    ee_reg.thr.flatThresh = ee_fw.flatThresh;
    ee_reg.thr.textureThresh = ee_fw.textureThresh;
    ee_reg.thr.edgeThresh = ee_fw.edgeThresh;
}

int ee_img_update(BL_GAIN_DB gain)
{
    DSP2_EE_PARAM sw_config;

    if (calc_ee_sw_config_by_iso(gain, &sw_config) == -1) return 0;
    ee_control(&sw_config); //set fw config

    return 0;
}

int ee_img_manual(void)
{
    DSP2_EE_ATTR attr;
    DSP2_EE_PARAM sw_config;

    MM_DSP2_GetEeAttr(&attr);
    sw_config.pos_edge_strength = attr.eeLv.pos_edge_strength;
    sw_config.neg_edge_strength = attr.eeLv.neg_edge_strength;
    sw_config.pos_edge_ovrsht_strength = attr.eeLv.pos_edge_ovrsht_strength;
    sw_config.neg_edge_ovrsht_strength = attr.eeLv.neg_edge_ovrsht_strength;
    sw_config.nr_strength = attr.eeLv.nr_strength;
    sw_config.dir_shpness_thr = attr.eeLv.dir_shpness_thr;
    sw_config.no_dir_shpness_thr = attr.eeLv.no_dir_shpness_thr;
    sw_config.flat_thr = attr.eeLv.flat_thr;
    sw_config.texture_thr = attr.eeLv.texture_thr;
    sw_config.edge_thr = attr.eeLv.edge_thr;
    ee_control(&sw_config);

    return 0;
}

void ee_hw_update(void)
{
    bl_dsp2_ee_conf_t conf;
    DSP2_EE_LUMA_WEIGHT *lumaWgt;

    img_param_sw_get_ee_over_sht_en(&conf.over_sht_state);
    memcpy(&conf.str, &(ee_reg.str), sizeof(bl_dsp2_ee_str_t));
    memcpy(&conf.thr, &(ee_reg.thr), sizeof(bl_dsp2_ee_thr_t));
    bl_set_EE_conf(&conf);

    img_param_sw_get_ee_luma_weight(&lumaWgt);
    memcpy(&ee_reg.luma_weight, lumaWgt, sizeof(bl_dsp2_ee_luma_weight_t));
    ee_luma_weight_hw_update();
}

void ee_luma_weight_hw_update(void)
{
    bl_set_EE_luma_weight(&ee_reg.luma_weight);
}

