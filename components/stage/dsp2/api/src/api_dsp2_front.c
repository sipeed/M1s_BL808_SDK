#include "api_struct.h"
#include "api_dsp2_front.h"
#include "img_proc.h"

#include "firmware_blc.h"
#include "firmware_dpc.h"
#include "firmware_bnr.h"
#include "firmware_lsc.h"

DSP2_BLC_PARAM g_blc = {0};
DSP2_DPC_PARAM g_dpc = {0};
DSP2_BNR_PARAM g_bnr = {0};
DSP2_LSC_PARAM g_lsc = {0};

BL_SINT32 MM_DSP2_SetBlcAttr(const DSP2_BLC_ATTR * attr)
{
    int i = 0;
    DSP2_BLC_PARAM cfg;

    if (attr->bBlcEn == 0) {
        imgproc_set_fw_module_en(DSP2_ADJ_BLC, DISABLE);
    } else {
        imgproc_set_fw_module_en(DSP2_ADJ_BLC, ENABLE);
    }

    if (attr->bManualModeEn == 1) {
        imgproc_set_fw_module_manual_mode(DSP2_ADJ_BLC, ENABLE);
    } else {
        imgproc_set_fw_module_manual_mode(DSP2_ADJ_BLC, DISABLE);
    }
    for (i = 0; i < BL_ISO_NODES; i++) {
        cfg.black_level = attr->blc[i].black_level;
        img_param_sw_set_blc(i, &cfg);
    }

    g_blc.black_level = attr->blcLv.black_level;

    imgproc_set_fw_module_en(DSP2_ADJ_AE, 1);

    return BL_RET_OK;
}

BL_SINT32 MM_DSP2_GetBlcAttr(DSP2_BLC_ATTR * attr)
{
    int i = 0;
    DSP2_BLC_PARAM *cfg;

    attr->bBlcEn = imgproc_get_fw_module_en(DSP2_ADJ_BLC);
    attr->bManualModeEn = imgproc_get_fw_module_manual_mode(DSP2_ADJ_BLC);
    attr->blcLv.black_level = g_blc.black_level;
    for (i = 0; i < BL_ISO_NODES; i++) {
        img_param_sw_get_blc(i, &cfg);
        attr->blc[i].black_level = cfg->black_level;
    }

    return BL_RET_OK;
}


BL_SINT32 MM_DSP2_SetDpcAttr(const DSP2_DPC_ATTR *attr)
{
    int i = 0;
    DSP2_DPC_PARAM cfg;

    if (attr->bDpcEn == 0) {
        imgproc_set_fw_module_en(DSP2_ADJ_DPC, DISABLE);
    } else {
        imgproc_set_fw_module_en(DSP2_ADJ_DPC, ENABLE);
    }

    if (attr->bManualModeEn == 1) {
        imgproc_set_fw_module_manual_mode(DSP2_ADJ_DPC, ENABLE);
    } else {
        imgproc_set_fw_module_manual_mode(DSP2_ADJ_DPC, DISABLE);
    }

    for (i = 0; i < BL_ISO_NODES; i++) {
        cfg.strength = attr->dpc[i].strength;
        img_param_sw_set_dpc(i, &cfg);
    }

    g_dpc.strength = attr->dpcLv.strength;

    imgproc_set_fw_module_en(DSP2_ADJ_AE, 1);

    return BL_RET_OK;
}

BL_SINT32 MM_DSP2_GetDpcAttr(DSP2_DPC_ATTR *attr)
{
    int i = 0;
    DSP2_DPC_PARAM *cfg;

    attr->bDpcEn = imgproc_get_fw_module_en(DSP2_ADJ_DPC);
    attr->bManualModeEn = imgproc_get_fw_module_manual_mode(DSP2_ADJ_DPC);
    attr->dpcLv.strength = g_dpc.strength;
    for (i = 0; i < BL_ISO_NODES; i++) {
        img_param_sw_get_dpc(i, &cfg);
        attr->dpc[i].strength = cfg->strength;
    }

    return BL_RET_OK;
}


BL_SINT32 MM_DSP2_SetBnrAttr(const DSP2_BNR_ATTR *attr)
{
    int i = 0;
    DSP2_BNR_PARAM cfg;

    if (attr->bBnrEn == 0) {
        imgproc_set_fw_module_en(DSP2_ADJ_BNR, DISABLE);
    } else {
        imgproc_set_fw_module_en(DSP2_ADJ_BNR, ENABLE);
    }

    if (attr->bManualModeEn == 1) {
        imgproc_set_fw_module_manual_mode(DSP2_ADJ_BNR, ENABLE);
    } else {
        imgproc_set_fw_module_manual_mode(DSP2_ADJ_BNR, DISABLE);
    }

    for (i = 0; i < BL_ISO_NODES; i++) {
        cfg.strength = attr->bnr[i].strength;
        img_param_sw_set_bnr(i, &cfg);
    }

    g_bnr.strength = attr->bnrLv.strength;

    imgproc_set_fw_module_en(DSP2_ADJ_AE, 1);

    return BL_RET_OK;
}

BL_SINT32 MM_DSP2_GetBnrAttr(DSP2_BNR_ATTR *attr)
{
    int i = 0;
    DSP2_BNR_PARAM *cfg;

    attr->bBnrEn = imgproc_get_fw_module_en(DSP2_ADJ_BNR);
    attr->bManualModeEn = imgproc_get_fw_module_manual_mode(DSP2_ADJ_BNR);
    attr->bnrLv.strength = g_bnr.strength;
    for (i = 0; i < BL_ISO_NODES; i++) {
        img_param_sw_get_bnr(i, &cfg);
        attr->bnr[i].strength = cfg->strength;
    }

    return BL_RET_OK;
}


BL_SINT32 MM_DSP2_SetLscAttr(const DSP2_LSC_ATTR *attr)
{
    int i = 0;
    DSP2_LSC_PARAM cfg;

    if (attr->bLscEn == 0) {
        imgproc_set_fw_module_en(DSP2_ADJ_LSC, DISABLE);
    } else {
        imgproc_set_fw_module_en(DSP2_ADJ_LSC, ENABLE);
    }

    if (attr->bManualModeEn == 1) {
        imgproc_set_fw_module_manual_mode(DSP2_ADJ_LSC, ENABLE);
    } else {
        imgproc_set_fw_module_manual_mode(DSP2_ADJ_LSC, DISABLE);
    }
    for (i = 0; i < BL_CT_NODES; i++) {
        cfg.strength = attr->lsc[i].strength;
        cfg.color_temp = attr->lsc[i].color_temp;
        img_param_sw_set_lsc(i, &cfg);
    }

    g_lsc.strength = attr->lscLv.strength;
    g_lsc.color_temp = attr->lscLv.color_temp;

    imgproc_set_fw_module_en(DSP2_ADJ_AWB, 1);

    return BL_RET_OK;
}

BL_SINT32 MM_DSP2_GetLscAttr(DSP2_LSC_ATTR *attr)
{
    int i = 0;
    DSP2_LSC_PARAM *cfg;

    attr->bLscEn = imgproc_get_fw_module_en(DSP2_ADJ_LSC);
    attr->bManualModeEn = imgproc_get_fw_module_manual_mode(DSP2_ADJ_LSC);
    attr->lscLv.strength = g_lsc.strength;
    attr->lscLv.color_temp = g_lsc.color_temp;
    for (i = 0; i < BL_CT_NODES; i++) {
        img_param_sw_get_lsc(i, &cfg);
        attr->lsc[i].strength = cfg->strength;
        attr->lsc[i].color_temp = cfg->color_temp;
    }

    return BL_RET_OK;
}



