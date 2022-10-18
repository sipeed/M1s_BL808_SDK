#include "bl_dsp2.h"
#include "bl_img_utils.h"
#include "img_proc.h"
#include "img_param.h"
#include "img_param_parse.h"
#include "awb_algo.h"
#include "api_struct.h"
#include "api_awb.h"

static bl_dsp2_awb3_stats_hist_t awb_stats_hist = {0};
static dsp2_awb3_sum_t awb3_sum = {0};

BL_SINT32 MM_DSP2_AWBAlgo(AWB_ALGO algo)
{
    imgproc_set_awb_algo(algo);
    return BL_RET_OK;
}

#if 0

BL_SINT32 MM_DSP2_AWBSendCmd(BL_UINT32 u32Cmd,BL_VOID *param)
{
/*
u32Cmd嚗隞文��
param嚗���
*/
    return BL_RET_OK;
}
#endif

static BL_SINT32 MM_DSP2_GetAwb1Stat(DSP2_AWB1_STATS *stats)
{
    int i;
    RGB_SUM_S awb_sum;

    for (i = 0; i < AWB1_STATS_GRID_NUM; i++){
        bl_get_AWB1_sum(i, &awb_sum);
        stats->sum[i].r_sum = awb_sum.r_sum;
        stats->sum[i].g_sum = awb_sum.g_sum;
        stats->sum[i].b_sum = awb_sum.b_sum;
    }

    return BL_RET_OK;
}

static BL_SINT32 MM_DSP2_GetAwb3Stat(DSP2_AWB3_STATS *stats)
{
    bl_get_AWB3_sum(&awb3_sum);
    stats->r_sum = awb3_sum.r_sum;
    stats->g_sum = awb3_sum.g_sum;
    stats->b_sum = awb3_sum.b_sum;
    stats->r_sum_hex = awb3_sum.r_sum_hex;
    stats->g_sum_hex = awb3_sum.g_sum_hex;
    stats->b_sum_hex = awb3_sum.b_sum_hex;
    stats->pixel_hex = awb3_sum.pixel_hex;
    stats->r_ratio_hex_y = awb3_sum.r_ratio_hex_y;
    stats->b_ratio_hex_y = awb3_sum.b_ratio_hex_y;
    stats->weight_hex_y = awb3_sum.weight_hex_y;
    stats->pixel_hex_y = awb3_sum.pixel_hex_y;
    stats->r_ratio_hist = awb3_sum.r_ratio_hist;
    stats->b_ratio_hist = awb3_sum.b_ratio_hist;
    stats->weight_hist = awb3_sum.weight_hist;
    stats->pixel_hist = awb3_sum.pixel_hist;
    stats->r_ratio_hist_clip = awb3_sum.r_ratio_hist_clip;
    stats->b_ratio_hist_clip = awb3_sum.b_ratio_hist_clip;
    stats->weight_hist_clip = awb3_sum.weight_hist_clip;
    stats->pixel_hist_clip = awb3_sum.pixel_hist_clip;

    return BL_RET_OK;
}

BL_SINT32 MM_DSP2_GetAwbStats(DSP2_AWB_STATS *stats)
{
    MM_DSP2_GetAwb1Stat(&(stats->awb1Stats));
    MM_DSP2_GetAwb3Stat(&(stats->awb3Stats));

    return BL_RET_OK;
}

BL_SINT32 MM_DSP2_GetAwbCfg(AWB_DEFAULT_CFG *cfg)
{
    int i,j, speed_level;
    wb_bais_t *wb_bias;
    awb_bais_t *awb_bias;

    for (i = 0; i < BL_CT_NODES; i++){
        img_param_get_wb_bias(i, &wb_bias);
        cfg->wbInfo[i].r_gain = wb_bias->rb_gain.r_gain;
        cfg->wbInfo[i].g_gain = 4096;
        cfg->wbInfo[i].b_gain = wb_bias->rb_gain.b_gain;
    }

    return BL_RET_OK;
}

BL_SINT32 MM_DSP2_SetAwbInfo(const DSP2_AWB_WB_INFO *info)
{
    bl_dsp2_rgb_gain_t rgb_gain;
    BL_COLOR_TEMP color_temp;

    rgb_gain.r_gain = info->r_gain;
    rgb_gain.g_gain = info->g_gain;
    rgb_gain.b_gain = info->b_gain;
    color_temp = info->color_temp;
    
    awb_set_gain(&rgb_gain);
    awb_set_color_temp(color_temp);

    return BL_RET_OK;
}

BL_SINT32 MM_DSP2_GetAwbInfo(DSP2_AWB_WB_INFO *info)
{
    bl_dsp2_rgb_gain_t rgb_gain;
    BL_COLOR_TEMP color_temp;

    awb_get_gain(&rgb_gain);
    awb_get_color_temp(&color_temp);

    info->r_gain = rgb_gain.r_gain;
    info->g_gain = rgb_gain.g_gain;
    info->b_gain = rgb_gain.b_gain;
    info->color_temp = color_temp;

    return BL_RET_OK;
}


BL_SINT32 MM_DSP2_SetAwbAttr(const DSP2_AWB_ATTR *attr)
{
    int i,j, speed_level, special_color_en, preference_en;
    awb_bais_t awb_bias;

    speed_level = attr->awbSpeed;
    special_color_en = attr->special_color_enable;
    preference_en = attr->preference_enable;
    awb_set_speed_level(speed_level);
    img_param_sw_set_awb_special_color_en(special_color_en);
    img_param_sw_set_awb_preference_en(preference_en);

    for (j = 0; j < BL_BV_NODES; j++){
        for (i = 0; i < BL_CT_NODES; i++){
            awb_bias.bais[i].r_gain = attr->preference_gain[j].bais[i].r_gain;
            awb_bias.bais[i].b_gain = attr->preference_gain[j].bais[i].b_gain;
            img_param_sw_set_awb_preference_gain(j, &awb_bias);
        }
    }

    return BL_RET_OK;
}

BL_SINT32 MM_DSP2_GetAwbAttr(DSP2_AWB_ATTR *attr)
{
    int i,j, speed_level, special_color_en, preference_en;
    awb_bais_t *awb_bias;

    awb_get_speed_level(&speed_level);
    img_param_sw_get_awb_special_color_en(&special_color_en);
    img_param_sw_get_awb_preference_en(&preference_en);
    attr->awbSpeed = speed_level;
    attr->special_color_enable = special_color_en;
    attr->preference_enable = preference_en;

    for (j = 0; j < BL_BV_NODES; j++){
        for (i = 0; i < BL_CT_NODES; i++){
            img_param_sw_get_awb_preference_gain(j, &awb_bias);
            attr->preference_gain[j].bais[i].r_gain = awb_bias->bais[i].r_gain;
            attr->preference_gain[j].bais[i].b_gain = awb_bias->bais[i].b_gain;
        }
    }

    return BL_RET_OK;
}





