#include "api_struct.h"
#include "api_dsp2_back.h"
#include "img_proc.h"

#include "firmware_ccm.h"
#include "firmware_gamma.h"
#include "firmware_sat.h"
#include "firmware_wdr.h"
#include "firmware_nr.h"
#include "firmware_ee.h"
#include "firmware_cs.h"
#include "firmware_yc.h"

DSP2_CCM_PARAM g_ccm = {0};
DSP2_GAMMA_PARAM g_gamma = {0};
DSP2_WDR_PARAM g_wdr = {0};
DSP2_SAT_PARAM g_sat = {0};
DSP2_NR_PARAM g_nr = {0};
DSP2_EE_PARAM g_ee = {0};
DSP2_CS_PARAM g_cs = {0};
DSP2_YC_PARAM g_yc = {0};

BL_SINT32 MM_DSP2_SetCcmAttr(const DSP2_CCM_ATTR *attr)
{
    int i = 0, j = 0;
    DSP2_CCM_PARAM cfg;
    ccm_cw_t cw_tbl;

    if (attr->bCcmEn == 0) {
        imgproc_set_fw_module_en(DSP2_ADJ_CCM, DISABLE);
    } else {
        imgproc_set_fw_module_en(DSP2_ADJ_CCM, ENABLE);
    }

    if (attr->bManualModeEn == 1) {
        imgproc_set_fw_module_manual_mode(DSP2_ADJ_CCM, ENABLE);
    } else {
        imgproc_set_fw_module_manual_mode(DSP2_ADJ_CCM, DISABLE);
    }

    for (i = 0; i < BL_CT_NODES; i++) {
        for (j = 0; j < CCM_COEF_NUM; j++) {
            cfg.coef[j] = attr->ccm[i].coef[j];
        }
        cfg.color_temp = attr->ccm[i].color_temp;
        img_param_sw_set_ccm(i, &cfg);
    }

    for (j = 0; j < CCM_COEF_NUM; j++) {
       g_ccm.coef[j] = attr->ccmLv.coef[j];
    }
    g_ccm.color_temp = attr->ccmLv.color_temp;

    for (i = 0; i < MAX_ENTRY_NUM_AE_ISO_AUTO; i++) {
        cw_tbl.color_weight = attr->ccmCw[i].color_weight;
        img_param_sw_set_ccm_color_weight(i, &cw_tbl);
    }
    imgproc_set_fw_module_en(DSP2_ADJ_AWB, 1);
    imgproc_set_fw_module_en(DSP2_ADJ_AE, 1);

    return BL_RET_OK;
}

BL_SINT32 MM_DSP2_GetCcmAttr(DSP2_CCM_ATTR *attr)
{
    int i = 0, j = 0;
    DSP2_CCM_PARAM *cfg;
    ccm_cw_t *cw_ptr;

    attr->bCcmEn = imgproc_get_fw_module_en(DSP2_ADJ_CCM);
    attr->bManualModeEn = imgproc_get_fw_module_manual_mode(DSP2_ADJ_CCM);
    for (j = 0; j < CCM_COEF_NUM; j++) {
       attr->ccmLv.coef[j] = g_ccm.coef[j];
    }
    attr->ccmLv.color_temp = g_ccm.color_temp;

    for (i = 0; i < BL_CT_NODES; i++) {
        img_param_sw_get_ccm(i, &cfg);
        for (j = 0; j < CCM_COEF_NUM; j++) {
            attr->ccm[i].coef[j] = cfg->coef[j];
        }
        attr->ccm[i].color_temp = cfg->color_temp;
    }
    for (i = 0; i < MAX_ENTRY_NUM_AE_ISO_AUTO; i++) {
        img_param_sw_get_ccm_color_weight(i, &cw_ptr);
        attr->ccmCw[i].color_weight = cw_ptr->color_weight;
    }
    return BL_RET_OK;
}

BL_SINT32 MM_DSP2_SetGammaAttr(const DSP2_GAMMA_ATTR *attr)
{
    int i = 0;
   DSP2_GAMMA_PARAM cfg;

   if (attr->bGammaEn == 0) {
       imgproc_set_fw_module_en(DSP2_ADJ_GAMMA, DISABLE);
   } else {
       imgproc_set_fw_module_en(DSP2_ADJ_GAMMA, ENABLE);
   }

   if (attr->bManualModeEn == 1) {
       imgproc_set_fw_module_manual_mode(DSP2_ADJ_GAMMA, ENABLE);
   } else {
       imgproc_set_fw_module_manual_mode(DSP2_ADJ_GAMMA, DISABLE);
    }

   for (i = 0; i < BL_BV_NODES; i++) {
       cfg.idx = attr->gamma[i].idx;
       img_param_sw_set_gamma(i, &cfg);
   }

    g_gamma.idx = attr->gammaLv.idx;

    imgproc_set_fw_module_en(DSP2_ADJ_AE, 1);

    return BL_RET_OK;
}

BL_SINT32 MM_DSP2_GetGammaAttr(DSP2_GAMMA_ATTR *attr)
{
    int i = 0;
    DSP2_GAMMA_PARAM *cfg;

    attr->bGammaEn = imgproc_get_fw_module_en(DSP2_ADJ_GAMMA);
    attr->bManualModeEn = imgproc_get_fw_module_manual_mode(DSP2_ADJ_GAMMA);
    attr->gammaLv.idx = g_gamma.idx;
    for (i = 0; i < BL_BV_NODES; i++) {
        img_param_sw_get_gamma(i, &cfg);
        attr->gamma[i].idx = cfg->idx;
    }

    return BL_RET_OK;
}

BL_SINT32 MM_DSP2_SetWdrAttr(const DSP2_WDR_ATTR *attr)
{
    int i, idx, k = 0;
    DSP2_WDR_PARAM cfg;
    wdr_lowlight_weight_conf_t lowlightWeight = {0};

    if (attr->bWdrEn == 0) {
       imgproc_set_fw_module_en(DSP2_ADJ_WDR, DISABLE);
    } else {
       imgproc_set_fw_module_en(DSP2_ADJ_WDR, ENABLE);
    }

    if (attr->bManualModeEn == 1) {
       imgproc_set_fw_module_manual_mode(DSP2_ADJ_WDR, ENABLE);
    } else {
       imgproc_set_fw_module_manual_mode(DSP2_ADJ_WDR, DISABLE);
    }

    for (i = 0; i < BL_BV_NODES; i++) {
        cfg.cs_strength = attr->wdr[i].cs_strength;
        cfg.curve_weight = attr->wdr[i].curve_weight;
        cfg.enh_weight = attr->wdr[i].enh_weight;
        cfg.bright_enh_level = attr->wdr[i].bright_enh_level;
        cfg.dark_enh_level = attr->wdr[i].dark_enh_level;
        img_param_sw_set_wdr(i, &cfg);

        lowlightWeight.lowlight_weight[i].idx[1] = attr->wdrTone.luma_weight_conf.weight[i].idx[1];
        lowlightWeight.lowlight_weight[i].idx[2] = attr->wdrTone.luma_weight_conf.weight[i].idx[2];
        lowlightWeight.lowlight_weight[i].idx[0] = attr->wdrTone.luma_weight_conf.weight[i].idx[0];
    }

    for (idx = 0; idx < BL_WDR_IDX_NUM; idx++){
        wdr_tone_curve_conf_t tone_curve = {0};
        for (k = 0; k < WDR_COEF_NUM; k++) {
            tone_curve.tone_curve.coef[k] = attr->wdrTone.tone_curve_container[idx].tone_curve.coef[k];
        }
        tone_curve.idx = attr->wdrTone.tone_curve_container[idx].tone_curve.coef[WDR_COEF_NUM];
        img_param_sw_set_wdr_tone_curve_conf(idx, &tone_curve);
    }

    g_wdr.cs_strength = attr->wdrLv.cs_strength;
    g_wdr.curve_weight = attr->wdrLv.curve_weight;
    g_wdr.enh_weight = attr->wdrLv.enh_weight;
    g_wdr.bright_enh_level = attr->wdrLv.bright_enh_level;
    g_wdr.dark_enh_level = attr->wdrLv.dark_enh_level;

    img_param_sw_set_wdr_tone_curve_en(attr->wdrTone.enable);
    lowlightWeight.roi_start = attr->wdrTone.luma_weight_conf.roi_start;
    lowlightWeight.roi_end = attr->wdrTone.luma_weight_conf.roi_end;

    lowlightWeight.thr[0] = attr->wdrTone.luma_weight_conf.thr[0];
    lowlightWeight.thr[1] = attr->wdrTone.luma_weight_conf.thr[1];
    lowlightWeight.thr[2] = attr->wdrTone.luma_weight_conf.thr[2];
    lowlightWeight.thr[3] = attr->wdrTone.luma_weight_conf.thr[3];

    img_param_sw_set_wdr_lowlight_weight_conf(&lowlightWeight);
    imgproc_set_fw_module_en(DSP2_ADJ_AE, 1);
    return BL_RET_OK;
}


BL_SINT32 MM_DSP2_GetWdrAttr(DSP2_WDR_ATTR *attr)
{
    int i, idx, k = 0;
    DSP2_WDR_PARAM *cfg;
    wdr_tone_curve_conf_t *tone_curve;
    wdr_lowlight_weight_conf_t *lowlight_weight_cfg;

    img_param_sw_get_wdr_lowlight_weight_conf(&lowlight_weight_cfg);
    attr->bWdrEn = imgproc_get_fw_module_en(DSP2_ADJ_WDR);
    attr->bManualModeEn = imgproc_get_fw_module_manual_mode(DSP2_ADJ_WDR);
    attr->wdrLv.cs_strength = g_wdr.cs_strength;
    attr->wdrLv.curve_weight = g_wdr.curve_weight;
    attr->wdrLv.enh_weight = g_wdr.enh_weight;
    attr->wdrLv.bright_enh_level = g_wdr.bright_enh_level;
    attr->wdrLv.dark_enh_level = g_wdr.dark_enh_level;

    img_param_sw_get_wdr_tone_curve_en(&attr->wdrTone.enable);
    attr->wdrTone.luma_weight_conf.roi_start = lowlight_weight_cfg->roi_start;
    attr->wdrTone.luma_weight_conf.roi_end = lowlight_weight_cfg->roi_end;
    attr->wdrTone.luma_weight_conf.thr[0] = lowlight_weight_cfg->thr[0];
    attr->wdrTone.luma_weight_conf.thr[1] = lowlight_weight_cfg->thr[1];
    attr->wdrTone.luma_weight_conf.thr[2] = lowlight_weight_cfg->thr[2];
    attr->wdrTone.luma_weight_conf.thr[3] = lowlight_weight_cfg->thr[3];

    for (i = 0; i < BL_BV_NODES; i++) {
        img_param_sw_get_wdr(i, &cfg);

        attr->wdr[i].cs_strength = cfg->cs_strength;
        attr->wdr[i].curve_weight = cfg->curve_weight;
        attr->wdr[i].enh_weight = cfg->enh_weight;
        attr->wdr[i].bright_enh_level = cfg->bright_enh_level;
        attr->wdr[i].dark_enh_level = cfg->dark_enh_level;

        attr->wdrTone.luma_weight_conf.weight[i].idx[1] = lowlight_weight_cfg->lowlight_weight[i].idx[1];
        attr->wdrTone.luma_weight_conf.weight[i].idx[2] = lowlight_weight_cfg->lowlight_weight[i].idx[2];
        attr->wdrTone.luma_weight_conf.weight[i].idx[0] = lowlight_weight_cfg->lowlight_weight[i].idx[0];

    }

    for (idx = 0; idx < BL_WDR_IDX_NUM; idx++){
        img_param_sw_get_wdr_tone_curve_conf(idx, &tone_curve);
        for (k = 0; k < WDR_COEF_NUM; k++) {
            attr->wdrTone.tone_curve_container[idx].tone_curve.coef[k] = tone_curve->tone_curve.coef[k];
        }
        attr->wdrTone.tone_curve_container[idx].idx = tone_curve->idx;
    }
    return BL_RET_OK;
}

BL_SINT32 MM_DSP2_SetSaturationAttr(const DSP2_SAT_ATTR *attr)
{
    int i = 0;
    DSP2_SAT_PARAM cfg;

    if (attr->bSaturationEn == 0) {
        imgproc_set_fw_module_en(DSP2_ADJ_SATURATION, DISABLE);
    } else {
        imgproc_set_fw_module_en(DSP2_ADJ_SATURATION, ENABLE);
    }

    if (attr->bManualModeEn == 1) {
        imgproc_set_fw_module_manual_mode(DSP2_ADJ_SATURATION, ENABLE);
    } else {
        imgproc_set_fw_module_manual_mode(DSP2_ADJ_SATURATION, DISABLE);
    }

    for (i = 0; i < BL_ISO_NODES; i++) {
        cfg.value = attr->sat[i].value;
        img_param_sw_set_sat(i, &cfg);
    }

    g_sat.value = attr->satLv.value;

    imgproc_set_fw_module_en(DSP2_ADJ_AE, 1);

    return BL_RET_OK;
}

BL_SINT32 MM_DSP2_GetSaturationAttr(DSP2_SAT_ATTR *attr)
{
    int i = 0;
    DSP2_SAT_PARAM *cfg;

    attr->bSaturationEn = imgproc_get_fw_module_en(DSP2_ADJ_SATURATION);
    attr->bManualModeEn = imgproc_get_fw_module_manual_mode(DSP2_ADJ_SATURATION);
    attr->satLv.value = g_sat.value;
    for (i = 0; i < BL_ISO_NODES; i++) {
        img_param_sw_get_sat(i, &cfg);
        attr->sat[i].value = cfg->value;
    }

    return BL_RET_OK;
}

BL_SINT32 MM_DSP2_SetNrAttr(const DSP2_NR_ATTR *attr)
{
    int i = 0;
    DSP2_NR_PARAM cfg;

    if (attr->bNrEn == 0) {
        imgproc_set_fw_module_en(DSP2_ADJ_NR, DISABLE);
    } else {
        imgproc_set_fw_module_en(DSP2_ADJ_NR, ENABLE);
    }

    if (attr->bManualModeEn == 1) {
        imgproc_set_fw_module_manual_mode(DSP2_ADJ_NR, ENABLE);
    } else {
        imgproc_set_fw_module_manual_mode(DSP2_ADJ_NR, DISABLE);
    }

    for (i = 0; i < BL_ISO_NODES; i++) {
        cfg.strength_level = attr->nr[i].strength_level;
        cfg.strength_2d = attr->nr[i].strength_2d;
        cfg.strength_3d = attr->nr[i].strength_3d;
        img_param_sw_set_nr(i, &cfg);
    }


    g_nr.strength_level = attr->nrLv.strength_level;
    g_nr.strength_2d = attr->nrLv.strength_2d;
    g_nr.strength_3d = attr->nrLv.strength_3d;

    imgproc_set_fw_module_en(DSP2_ADJ_AE, 1);

    return BL_RET_OK;
}

BL_SINT32 MM_DSP2_GetNrAttr(DSP2_NR_ATTR *attr)
{
    int i = 0;
    DSP2_NR_PARAM *cfg;

    attr->bNrEn = imgproc_get_fw_module_en(DSP2_ADJ_NR);
    attr->bManualModeEn = imgproc_get_fw_module_manual_mode(DSP2_ADJ_NR);
    attr->nrLv.strength_level = g_nr.strength_level;
    attr->nrLv.strength_2d = g_nr.strength_2d;
    attr->nrLv.strength_3d = g_nr.strength_3d;
    for (i = 0; i < BL_ISO_NODES; i++) {
        img_param_sw_get_nr(i, &cfg);
        attr->nr[i].strength_level = cfg->strength_level;
        attr->nr[i].strength_2d = cfg->strength_2d;
        attr->nr[i].strength_3d = cfg->strength_3d;
    }

    return BL_RET_OK;
}



BL_SINT32 MM_DSP2_SetEeAttr(const DSP2_EE_ATTR *attr)
{
    int i = 0;
    DSP2_EE_PARAM cfg;
    DSP2_EE_LUMA_WEIGHT *eeLumaWeightTbl;

    if (attr->bEeEn == 0) {
        imgproc_set_fw_module_en(DSP2_ADJ_EE, DISABLE);
    } else {
        imgproc_set_fw_module_en(DSP2_ADJ_EE, ENABLE);
    }
    
    if (attr->bOvrShtEn == 0) {
        img_param_sw_set_ee_over_sht_en(0);
    } else {
        img_param_sw_set_ee_over_sht_en(1);
    }

    if (attr->bManualModeEn == 1) {
        imgproc_set_fw_module_manual_mode(DSP2_ADJ_EE, ENABLE);
    } else {
        imgproc_set_fw_module_manual_mode(DSP2_ADJ_EE, DISABLE);
    }

     for (i = 0; i < BL_ISO_NODES; i++) {
        cfg.pos_edge_strength        = attr->ee[i].pos_edge_strength;
        cfg.neg_edge_strength        = attr->ee[i].neg_edge_strength;
        cfg.pos_edge_ovrsht_strength = attr->ee[i].pos_edge_ovrsht_strength;
        cfg.neg_edge_ovrsht_strength = attr->ee[i].neg_edge_ovrsht_strength;
        cfg.nr_strength = attr->ee[i].nr_strength;
        cfg.dir_shpness_thr = attr->ee[i].dir_shpness_thr;
        cfg.no_dir_shpness_thr = attr->ee[i].no_dir_shpness_thr;
        cfg.flat_thr = attr->ee[i].flat_thr;
        cfg.texture_thr = attr->ee[i].texture_thr;
        cfg.edge_thr = attr->ee[i].edge_thr;
        img_param_sw_set_ee(i, &cfg);
     }

    g_ee.pos_edge_strength       = attr->eeLv.pos_edge_strength;
    g_ee.neg_edge_strength       = attr->eeLv.neg_edge_strength;
    g_ee.pos_edge_ovrsht_strength = attr->eeLv.pos_edge_ovrsht_strength;
    g_ee.neg_edge_ovrsht_strength = attr->eeLv.neg_edge_ovrsht_strength;
    g_ee.nr_strength = attr->eeLv.nr_strength;
    g_ee.dir_shpness_thr = attr->eeLv.dir_shpness_thr;
    g_ee.no_dir_shpness_thr = attr->eeLv.no_dir_shpness_thr;
    g_ee.flat_thr = attr->eeLv.flat_thr;
    g_ee.texture_thr = attr->eeLv.texture_thr;
    g_ee.edge_thr = attr->eeLv.edge_thr;

    img_param_sw_set_ee_luma_weight(&attr->eeLumaWeightTbl);
    imgproc_set_fw_module_en(DSP2_ADJ_AE, 1);

    return BL_RET_OK;
}

BL_SINT32 MM_DSP2_GetEeAttr(DSP2_EE_ATTR *attr)
{
    int i = 0;
    DSP2_EE_PARAM *cfg;
    DSP2_EE_LUMA_WEIGHT *eeLumaWeightTbl;

    attr->bEeEn = imgproc_get_fw_module_en(DSP2_ADJ_EE);
    img_param_sw_get_ee_over_sht_en(&attr->bOvrShtEn);
    attr->bManualModeEn = imgproc_get_fw_module_manual_mode(DSP2_ADJ_EE);
    attr->eeLv.pos_edge_strength       = g_ee.pos_edge_strength;
    attr->eeLv.neg_edge_strength       = g_ee.neg_edge_strength;
    attr->eeLv.pos_edge_ovrsht_strength = g_ee.pos_edge_ovrsht_strength;
    attr->eeLv.neg_edge_ovrsht_strength = g_ee.neg_edge_ovrsht_strength;
    attr->eeLv.nr_strength = g_ee.nr_strength;
    attr->eeLv.dir_shpness_thr = g_ee.dir_shpness_thr;
    attr->eeLv.no_dir_shpness_thr = g_ee.no_dir_shpness_thr;
    attr->eeLv.flat_thr = g_ee.flat_thr;
    attr->eeLv.texture_thr = g_ee.texture_thr;
    attr->eeLv.edge_thr = g_ee.edge_thr;
    for (i = 0; i < BL_ISO_NODES; i++) {
        img_param_sw_get_ee(i, &cfg);
        attr->ee[i].pos_edge_strength     = cfg->pos_edge_strength;
        attr->ee[i].neg_edge_strength = cfg->neg_edge_strength;
        attr->ee[i].pos_edge_ovrsht_strength = cfg->pos_edge_ovrsht_strength;
        attr->ee[i].neg_edge_ovrsht_strength = cfg->neg_edge_ovrsht_strength;
        attr->ee[i].nr_strength = cfg->nr_strength;
        attr->ee[i].dir_shpness_thr = cfg->dir_shpness_thr;
        attr->ee[i].no_dir_shpness_thr = cfg->no_dir_shpness_thr;
        attr->ee[i].flat_thr = cfg->flat_thr;
        attr->ee[i].texture_thr = cfg->texture_thr;
        attr->ee[i].edge_thr = cfg->edge_thr;
    }

    img_param_sw_get_ee_luma_weight(&eeLumaWeightTbl);
    memcpy(&attr->eeLumaWeightTbl, eeLumaWeightTbl, sizeof(DSP2_EE_LUMA_WEIGHT));

    return BL_RET_OK;
}



BL_SINT32 MM_DSP2_SetCsAttr(const DSP2_CS_ATTR *attr)
{
    int i = 0;
    DSP2_CS_PARAM cfg;

    if (attr->bCsEn == 0) {
        imgproc_set_fw_module_en(DSP2_ADJ_CS, DISABLE);
    } else {
        imgproc_set_fw_module_en(DSP2_ADJ_CS, ENABLE);
    }

    if (attr->bManualModeEn == 1) {
        imgproc_set_fw_module_manual_mode(DSP2_ADJ_CS, ENABLE);
    } else {
        imgproc_set_fw_module_manual_mode(DSP2_ADJ_CS, DISABLE);
    }

     for (i = 0; i < BL_ISO_NODES; i++) {
         cfg.strength = attr->cs[i].strength;
         img_param_sw_set_cs(i, &cfg);
     }

    g_cs.strength = attr->csLv.strength;

    imgproc_set_fw_module_en(DSP2_ADJ_AE, 1);

    return BL_RET_OK;
}

BL_SINT32 MM_DSP2_GetCsAttr(DSP2_CS_ATTR *attr)
{
    int i = 0;
    DSP2_CS_PARAM *cfg;

    attr->bCsEn = imgproc_get_fw_module_en(DSP2_ADJ_CS);
    attr->bManualModeEn = imgproc_get_fw_module_manual_mode(DSP2_ADJ_CS);
    attr->csLv.strength = g_cs.strength;
    for (i = 0; i < BL_ISO_NODES; i++) {
        img_param_sw_get_cs(i, &cfg);
        attr->cs[i].strength = cfg->strength;
    }

    return BL_RET_OK;

}


BL_SINT32 MM_DSP2_SetYcAttr(const DSP2_YC_ATTR *attr)
{
    int i = 0;
    DSP2_YC_PARAM cfg;

    if (attr->bYcEn == 0) {
        imgproc_set_fw_module_en(DSP2_ADJ_YC, DISABLE);
    } else {
        imgproc_set_fw_module_en(DSP2_ADJ_YC, ENABLE);
    }

    if (attr->bManualModeEn == 1) {
        imgproc_set_fw_module_manual_mode(DSP2_ADJ_YC, ENABLE);
    } else {
        imgproc_set_fw_module_manual_mode(DSP2_ADJ_YC, DISABLE);
    }

     for (i = 0; i < BL_ISO_NODES; i++) {
        cfg.contrast = attr->yc[i].contrast;
        cfg.brightness = attr->yc[i].brightness;
        img_param_sw_set_yc(i, &cfg);
    }

    g_yc.contrast = attr->ycLv.contrast;
    g_yc.brightness = attr->ycLv.brightness;

    imgproc_set_fw_module_en(DSP2_ADJ_AE, 1);

    return BL_RET_OK;
}

BL_SINT32 MM_DSP2_GetYcAttr(DSP2_YC_ATTR *attr)
{
    int i = 0;
    DSP2_YC_PARAM *cfg;

    attr->bYcEn = imgproc_get_fw_module_en(DSP2_ADJ_YC);
    attr->bManualModeEn = imgproc_get_fw_module_manual_mode(DSP2_ADJ_YC);
    attr->ycLv.contrast = g_yc.contrast;
    attr->ycLv.brightness = g_yc.brightness;
    for (i = 0; i < BL_ISO_NODES; i++) {
        img_param_sw_get_yc(i, &cfg);
        attr->yc[i].contrast = cfg->contrast;
        attr->yc[i].brightness = cfg->brightness;
    }

    return BL_RET_OK;
}


