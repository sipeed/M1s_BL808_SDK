#include <stdint.h>
#include "firmware_dpc.h"
#include "bl_dsp2.h"
#include "bl_img_utils.h"
#include "img_param.h"
#include "img_param_parse.h"
#include "api_struct.h"
#include "api_dsp2_front.h"

typedef struct {
    uint8_t defect_THR_1;
    uint8_t defect_THR_2;
} defect_corr_t;

static bl_dsp2_dpc_thr_t  dpc_reg;
static defect_corr_t     dpc_fw;
static DSP2_DPC_PARAM    dpc_sw = {0};

void dpc_init(void)
{
    DSP2_DPC_ATTR attr;

    MM_DSP2_GetDpcAttr(&attr);
    attr.dpcLv.strength = attr.dpc[0].strength;
    MM_DSP2_SetDpcAttr(&attr);
}

static int dpc_sw_get_fw_register(DSP2_DPC_PARAM *sw, defect_corr_t *fw)
{
    int tbl_num = 0, value;
    dpc_trans_tbl_t *trans_tbl = NULL;
    img_param_get_dpc_trans(&trans_tbl, &tbl_num);

    table_linear_interpolate(trans_tbl->strength_tbl, trans_tbl->thr1_tbl, tbl_num, sw->strength, &value);
    fw->defect_THR_1 = value;
    table_linear_interpolate(trans_tbl->strength_tbl, trans_tbl->thr2_tbl, tbl_num, sw->strength, &value);
    fw->defect_THR_2 = value;

    return 0;
}

void dpc_get_sw_config(DSP2_DPC_PARAM *config)
{
    int tbl_num = 0;
    dpc_trans_tbl_t *trans_tbl = NULL;
    img_param_get_dpc_trans(&trans_tbl, &tbl_num);

    config->strength = dpc_sw.strength;
}

void dpc_set_sw_config(const DSP2_DPC_PARAM *config)
{
    dpc_sw.strength = config->strength;
}

static void dpc_get_fw_config(defect_corr_t *config)
{
    memcpy(config, &dpc_fw, sizeof(defect_corr_t));
}

void dpc_control(const DSP2_DPC_PARAM *config)
{
    dpc_set_sw_config(config);
    dpc_sw_get_fw_register(config, &dpc_fw);

    dpc_reg.thr_1 = dpc_fw.defect_THR_1;
    dpc_reg.thr_2 = dpc_fw.defect_THR_2;
}

int dpc_img_update(BL_GAIN_DB gain)
{
    DSP2_DPC_PARAM sw_config;

    if (calc_dpc_sw_config_by_iso(gain, &sw_config) == -1) return 0;
    dpc_control(&sw_config);

    return 0;
}

int dpc_img_manual(void)
{
    DSP2_DPC_ATTR attr;
    DSP2_DPC_PARAM sw_config;

    MM_DSP2_GetDpcAttr(&attr);
    sw_config.strength = attr.dpcLv.strength;
    dpc_control(&sw_config);

    return 0;
}

void dpc_hw_update(void)
{
    bl_set_DPC_conf(&dpc_reg);
}

