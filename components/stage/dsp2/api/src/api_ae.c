#include <stdint.h>
#include "bl_dsp2.h"
#include "bl_img_utils.h"
#include "img_proc.h"
#include "img_param.h"
#include "img_param_parse.h"
#include "ae_algo.h"
#include "api_struct.h"
#include "api_ae.h"

static bl_dsp2_ae_hist_y_t y_hist;
static bl_dsp2_ae_grid_sum_t grid_sum;

BL_SINT32 MM_DSP2_AEAlgo(AE_ALGO algo)
{
    imgproc_set_ae_algo(algo);
    return BL_RET_OK;
}

#if 0
BL_SINT32 MM_DSP2_AESendCmd(BL_UINT32 u32Cmd,BL_VOID *param)
{
/*
u32Cmd：命令号。
param：参数。
*/
    return BL_RET_OK;
}
#endif
BL_SINT32 MM_DSP2_GetAeStats(DSP2_AE_STATS * stats)
{
    int ret, i;

    ret = bl_get_AE_hist_sum_y(&y_hist);
    if (ret != -1) {
        for (i = 0; i < DSP2_AE_HIST_Y_BIN_NUM; i++) {
            stats->aeHistY[i] = y_hist.y[i];
        }
    }

    bl_get_AE_stats(&grid_sum);
    for (i = 0; i < AE_STATS_GRID_NUM; i++) {
        stats->aeGridSum.y_sum[i] = grid_sum.y_sum[i];
        stats->aeGridSum.r_sum[i] = grid_sum.r_sum[i];
        stats->aeGridSum.g_sum[i] = grid_sum.g_sum[i];
        stats->aeGridSum.b_sum[i] = grid_sum.b_sum[i];
    }

    return BL_RET_OK;
}

BL_SINT32 MM_DSP2_SetAeInfo(const DSP2_AE_INFO *info)
{

    BL_EXPO_TIME expo_time;
    float gain_f;

    expo_time = info->expo_time;
    gain_f = GAIN_DB_INT_TO_FLOAT(info->gain);
    
    ae_set_sensor_exposure(expo_time);
    ae_set_sensor_gain(gain_f);
	imgproc_set_2A_keep_reg("ISO", info->gain , expo_time, NULL);
    return BL_RET_OK;
}

BL_SINT32 MM_DSP2_GetAeInfo(DSP2_AE_INFO *info)
{
    BL_EXPO_TIME expo_time;
    float gain_f;

    ae_get_sensor_exposure(&expo_time);
    ae_get_sensor_gain(&gain_f);

    info->expo_time = expo_time;
    info->gain =  GAIN_DB_FLOAT_TO_INT(gain_f);//gain_f * 256;

    return BL_RET_OK;
}

BL_SINT32 MM_DSP2_SetAeAttr(const DSP2_AE_ATTR *attr)
{
    int i;

    DSP2_AE_HIGHLIGHT_WEIGHT ae_highlight_weight = {0};
    ae_set_speed_level(attr->aeSpeed);
    ae_set_metering_mode(attr->meteringMode);
    for (i = 0; i < BL_BV_NODES; i++) {
        img_param_sw_set_ae(i, &attr->subAttr[i]);
        ae_highlight_weight.idx[0] = attr->weightConf.highlight_weight[i].idx[0];
        ae_highlight_weight.idx[1] = attr->weightConf.highlight_weight[i].idx[1];
        ae_highlight_weight.idx[2] = attr->weightConf.highlight_weight[i].idx[2];
        img_param_sw_set_ae_highlight_weight(i, &ae_highlight_weight);
    }

    for (i = 0; i < AE_METERING_TBL_NUM; i++) {
        img_param_sw_set_ae_metering_tbl(i, &attr->meteringModeTbl[i]);
    }

    return BL_RET_OK;
}

BL_SINT32 MM_DSP2_GetAeAttr(DSP2_AE_ATTR *attr)
{
    int i, k, speed_level;
    AE_METERING mode;
    DSP2_AE_SUB_ATTR *sub_attr;
    DSP2_AE_METERING_TBL *tbl;
    DSP2_AE_HIGHLIGHT_WEIGHT *ae_highlight_weight_ptr;


    ae_get_speed_level(&speed_level);
    ae_get_metering_mode(&mode);

    for (i = 0; i < BL_BV_NODES; i++) {
        img_param_sw_get_ae(i, &sub_attr);
        attr->subAttr[i].ae_target = sub_attr->ae_target;
        img_param_sw_get_ae_highlight_weight(i, &ae_highlight_weight_ptr);
        attr->weightConf.highlight_weight[i].idx[0] = ae_highlight_weight_ptr->idx[0];
        attr->weightConf.highlight_weight[i].idx[1] = ae_highlight_weight_ptr->idx[1];
        attr->weightConf.highlight_weight[i].idx[2] = ae_highlight_weight_ptr->idx[2];
    }

    for (i = 0; i < AE_METERING_TBL_NUM; i++) {
        img_param_sw_get_ae_metering_tbl(i, &tbl);
        memcpy(&attr->meteringModeTbl[i], tbl, sizeof(DSP2_AE_METERING_TBL));
    }
    
    attr->meteringMode = mode;
    attr->aeSpeed = speed_level;
    return BL_RET_OK;
}




