#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <ctype.h>
#include <aos/kernel.h>
#include <cli.h>
#include <math.h>
#include "bl_img_utils.h"

#include <bl808_dsp2.h>
#include <bl808_dsp2_wdr.h>
#include <bl808_dsp2_misc.h>
#include <bl808_dsp2_axi_ctrl.h>
#include <bl_dsp2.h>
#include "img_proc.h"
#include "sensor.h"
#include "algo_common.h"
//#include "firmware_ae.h"
#include "firmware_awb.h"
#include "firmware_af.h"
#include "firmware_blc.h"
#include "firmware_dpc.h"
#include "firmware_bnr.h"
#include "firmware_lsc.h"
#include "firmware_ccm.h"
#include "firmware_gamma.h"
#include "firmware_wdr.h"
#include "firmware_nr.h"
#include "firmware_ee.h"
#include "firmware_cs.h"
#include "firmware_sat.h"
#include "firmware_yc.h"
#include "img_dsp2_parse.h"

#include "api_struct.h"
#include "api_ae.h"
#include "api_awb.h"
#include "api_dsp2_front.h"
#include "api_dsp2_back.h"

#define AWB_CAL_WB_INFO_NUM     (21)
#define AWB_CAL_AWB_NUM         (88)
#define LSC_CAL_REG_NUM     (LSC_COEF_NUM * 3 + 3 + 1)
#define CCM_CAL_REG_NUM     (CCM_COEF_NUM + 1)
#define GAMMA_CAL_REG_NUM   (GAMMA_COEF_NUM + 1)

static bl_dsp2_ae_grid_sum_t ae_grid_sum = {0};
static bl_dsp2_ae_hist_y_t ae_y_sum = {0};
static bl_dsp2_ae_hist_bayer_t ae_bayer_sum = {0};
static bl_dsp2_awb3_stats_hist_t awb_stats_hist = {0};
static bl_dsp2_wdr_curve_t wdr_curve = {0};

static dsp2_awb3_sum_t awb3_sum = {0};
static DSP2_AWB_STATS awb_stats = {0};
static DSP2_AE_STATS ae_stats = {0};
static DSP2_Gamma_Curve_Type gammaCfg;

int isIntger(char* str, int* value)
{
    int val = 0;
    if (str != NULL) {
        val = atoi(str);
        if ((val != 0) || (str[0] == '0')) {
            *value = val;
            return 1;
        }
    }
    return 0;
}

int isFloat(char* str, float* value)
{
    float val = 0;
    if (str != NULL) {
        val = atof(str);
        if ((val != 0) || (str[0] == '0')) {
            *value = val;
            return 1;
        }
    }
    return 0;
}

int isIntgerArray(char* str, int* array, int *ret_arr_num)
{
    int val = 0, arr_num = 0;
    const char delim[2] = ",";
    char *token;

    if (strstr(str, "[") != NULL) str++;
    token = strtok(str, delim);
    while (token != NULL) {
        if (strstr(token, "]") != NULL) {
            token[strlen(token)-1] = '\0';
        }
        val = atoi(token);
        if ((val != 0) || (token[0] == '0')) {
            *array++ = val;
            arr_num++;
            token = strtok(NULL, delim);
        } else { // '\0'
            *ret_arr_num = arr_num;
            return MIN(1, arr_num);
        }
    }
    *ret_arr_num = arr_num;
    return MIN(1, arr_num);

}

int parseToolReg(char *reg_in, char *reg_out)
{
    char *reg_ptr;

    reg_ptr = strstr(reg_in, "HW_");
    if (reg_ptr != NULL) {
        sprintf(reg_out, (reg_ptr + 3));
        return REG_HW;
    }

    reg_ptr = strstr(reg_in, "SW_");
    if (reg_ptr != NULL) {
        sprintf(reg_out, (reg_ptr + 3));
        return REG_SW;
    }

    reg_ptr = strstr(reg_in, "FW_");
    if (reg_ptr != NULL) {
        sprintf(reg_out, (reg_ptr + 3));
        return REG_FW;
    }

    reg_ptr = strstr(reg_in, "CAL");
    if (reg_ptr != NULL) {
        sprintf(reg_out, (reg_ptr + 3));
        return REG_CAL;
    }

    sprintf(reg_out, reg_in);
    return REG_SW;
}

void strCatVal(char* ret_string, int value)
{
    char value_str[16] = {'\0'};

    sprintf(value_str, "%d,", value);
    strcat(ret_string, value_str);

}

void strCatVal_u64(char* ret_string, uint64_t value)
{
    char value_str[32] = {'\0'};

    sprintf(value_str, "%lu,", value);
    strcat(ret_string, value_str);

}

void strCatVal_hex(char* ret_string, int value)
{
    char value_str[16] = {'\0'};

    sprintf(value_str, "0x%08x,", value);
    strcat(ret_string, value_str);

}

int DSP2_SYS_HW_Parse(int type, char* reg, int value, char* ret_string)
{
    int ret = -1;
    int val_get = 0;
    char str_get[32] = {'\0'};
    BL_Img_Size_T win;
    BAYER_PATTERN_E bayer_pattern = 0;

    if (strcmp(reg, "bayer_pattern") == 0) {
        if (type == DSP2_PARSE_WRITE) {
            bayer_pattern = value;
            DSP2_Set_Bayer_Pattern(bayer_pattern);
        } else {
            DSP2_Get_Bayer_Pattern(&bayer_pattern);
            sprintf(str_get, "%s", bayer_pattern_str_arr[bayer_pattern]);
            sprintf(ret_string, "[OK] sensor_%s: %s", reg, str_get);
            return 0;
        }    
    } else if (strcmp(reg, "bl444to422") == 0) {
        if (type == DSP2_PARSE_WRITE) DSP2_Set_BL444to422(value);
            DSP2_Get_BL444to422(&val_get);
    } else if (strcmp(reg, "cfa_init_en") == 0) {
        if (type == DSP2_PARSE_WRITE) DSP2_Set_CFA_Int_State(value);
            DSP2_Get_CFA_Int_State(&val_get);
    } else {
        return -1;
    }

    if (type == DSP2_PARSE_WRITE) {
        return 0;
    }
    sprintf(ret_string, "[OK] SYS_%s: %d", reg, val_get);

    return 0;
}

int DSP2_DSP2_MISC_HW_Parse(int type, char* reg, int value, char* ret_string)
{
    int ret = -1;
    int val_get = 0;
    char str_get[32] = {'\0'};
    int idx = 0;
    char *str = reg;
    DSP2_MISC_RGB2YUV_Cfg_Type rgb2yuvCfg;
    DSP2_MISC_YUV2RGB_Cfg_Type yuv2rgbCfg;
    DSP2_MISC_Display_Cfg_Type displayCfg;
    DSP2_MISC_Crop_Cfg_Type    cropCfg;
    DSP2_MISC_Scaler_Cfg_Type  scalerCfg;
    DSP2_MISC_OSD_Input_Type   osdInputType;
    DSP2_MISC_OSD_PB_Input_Type osdPbInputType;
    DSP2_YUV_Adjust_Cfg_Type yuvAdjCfg;
    DSP2_FRAME_M_TO_N_S m2nCfg;
    DVP_2x_Cfg_Type dvp2xCfg;

     if (strstr(reg, "pclk_force_on") != NULL) {
        if (type == DSP2_PARSE_WRITE) DSP2_MSIC_Pclk_Force_Set_State(value);
        DSP2_MSIC_Pclk_Force_Get_State(&val_get);
    } else if (strstr(reg, "cr_de_as_hsync") != NULL) {
        if (type == DSP2_PARSE_WRITE) DSP2_MSIC_Cr_De_As_Hsync_Set_State(value);
        DSP2_MSIC_Cr_De_As_Hsync_Get_State(&val_get);
    } else if (strstr(reg, "dsp2_dtsrc_src_sel") != NULL) {
        if (type == DSP2_PARSE_WRITE) DSP2_MSIC_Dtsrc_Set_Mode(value);
        DSP2_MSIC_Dtsrc_Get_Mode(&val_get);
    } else if (strstr(reg, "dvp2x_") != NULL) {
        DSP2_MSIC_DVP_2x_Get_Cfg(&dvp2xCfg);
        if (strstr(reg, "dvp2x_en") != NULL) {
            if (type == DSP2_PARSE_WRITE) {
                if (value == 1) DSP2_MSIC_DVP_2x_Enable();
                else DSP2_MSIC_DVP_2x_Disable();
                return 0;
            }
            DSP2_MSIC_DVP_2x_Get_State(&val_get);
        } else if (strstr(reg, "hSyncLevel") != NULL) {
            if (type == DSP2_PARSE_WRITE) dvp2xCfg.hSyncLevel = value;
            val_get = dvp2xCfg.hSyncLevel;
        } else if (strstr(reg, "vSyncLevel") != NULL) {
            if (type == DSP2_PARSE_WRITE) dvp2xCfg.vSyncLevel = value;
            val_get = dvp2xCfg.vSyncLevel;
        } else if (strstr(reg, "dataOrder") != NULL) {
            if (type == DSP2_PARSE_WRITE) dvp2xCfg.dataOrder = value;
            val_get = dvp2xCfg.dataOrder;
        } else if (strstr(reg, "fifoThreshold") != NULL) {
            if (type == DSP2_PARSE_WRITE) dvp2xCfg.fifoThreshold = value;
            val_get = dvp2xCfg.fifoThreshold;
        }
        if (type == DSP2_PARSE_WRITE) DSP2_MSIC_DVP_2x_Init(&dvp2xCfg);
    } else if (strstr(reg, "seof_intr_src_") != NULL) {
        idx = strtol((str += strlen("seof_intr_src_")), NULL, 10);
        if (type == DSP2_PARSE_WRITE) DSP2_Intr_Ctrl_Set_Src(idx, value);
        DSP2_Intr_Ctrl_Get_Src(idx, &val_get);
    } else if (strstr(reg, "dvp2bus_") != NULL) {
        if (strstr(reg, "dvp2bus_dvp_sel_") != NULL) {
            idx = strtol((str += strlen("dvp2bus_dvp_sel_")), NULL, 10);
            if (type == DSP2_PARSE_WRITE) {
                DSP2_DVP2AXI_Set_Src(idx, (DVP2AXI_Src_Type )value);
                return 0;
            }
            DSP2_DVP2AXI_Get_Src(idx, (DVP2AXI_Src_Type *)&val_get);
        } else if (strstr(reg, "dvp2bus_id_sel_") != NULL) {
            idx = strtol((str += strlen("dvp2bus_id_sel_")), NULL, 10);
            if (type == DSP2_PARSE_WRITE) {
                DSP2_DVP2AXI_Set_Id_Sel(idx, (DVP2AXI_ID_E )value);
                return 0;
            }
            DSP2_DVP2AXI_Get_Id_Sel(idx, (DVP2AXI_ID_E *)&val_get);
        }
    } else if (strstr(reg, "yuv_adjust_") != NULL) {
        if (strstr(reg, "yuv_adjust_state_") != NULL) {
            idx = strtol((str += strlen("yuv_adjust_state_")), NULL, 10);
            if (type == DSP2_PARSE_WRITE) {
                DSP2_YUV_Adjust_Set_State(idx, value);
                return 0;
            }
            DSP2_YUV_Adjust_Get_State(idx, &val_get);
        } else if (strstr(reg, "yuv_adjust_input_sel_") != NULL) {
            idx = strtol((str += strlen("yuv_adjust_input_sel_")), NULL, 10);
            if (type == DSP2_PARSE_WRITE) {
                DSP2_YUV_Adjust_Set_Input(idx, value);
                return 0;
            }
            DSP2_YUV_Adjust_Get_Input(idx, &val_get);
        } else if (strstr(reg, "yuv_adjust_en_") != NULL) {
            idx = strtol((str += strlen("yuv_adjust_en_")), NULL, 10);
            if (type == DSP2_PARSE_WRITE) DSP2_YUV_Adjust_Set_State(idx,value);
            DSP2_YUV_Adjust_Get_State(idx, &val_get);
        } else if (strstr(reg, "yuv_adjust_y_luma_") != NULL) {
            idx = strtol((str += strlen("yuv_adjust_y_luma_")), NULL, 10);
            DSP2_YUV_Adjust_Get_Cfg(idx, &yuvAdjCfg);
            if (type == DSP2_PARSE_WRITE) yuvAdjCfg.y_luma = value;
            val_get = yuvAdjCfg.y_luma;
        } else if (strstr(reg, "yuv_adjust_y_mul0_") != NULL) {
            idx = strtol((str += strlen("yuv_adjust_y_mul0_")), NULL, 10);
            DSP2_YUV_Adjust_Get_Cfg(idx, &yuvAdjCfg);
            if (type == DSP2_PARSE_WRITE) yuvAdjCfg.y_mul0 = value;
            val_get = yuvAdjCfg.y_mul0;
        } else if (strstr(reg, "yuv_adjust_y_mul1_") != NULL) {
            idx = strtol((str += strlen("yuv_adjust_y_mul1_")), NULL, 10);
            DSP2_YUV_Adjust_Get_Cfg(idx, &yuvAdjCfg);
            if (type == DSP2_PARSE_WRITE) yuvAdjCfg.y_mul1 = value;
            val_get = yuvAdjCfg.y_mul1;
        } else if (strstr(reg, "yuv_adjust_y_min_") != NULL) {
            idx = strtol((str += strlen("yuv_adjust_y_min_")), NULL, 10);
            DSP2_YUV_Adjust_Get_Cfg(idx, &yuvAdjCfg);
            if (type == DSP2_PARSE_WRITE) yuvAdjCfg.y_min = value;
            val_get = yuvAdjCfg.y_min;
        } else if (strstr(reg, "yuv_adjust_y_max_") != NULL) {
            idx = strtol((str += strlen("yuv_adjust_y_max_")), NULL, 10);
            DSP2_YUV_Adjust_Get_Cfg(idx, &yuvAdjCfg);
            if (type == DSP2_PARSE_WRITE) yuvAdjCfg.y_max = value;
            val_get = yuvAdjCfg.y_max;
        } else if (strstr(reg, "yuv_adjust_uv_mul0_") != NULL) {
            idx = strtol((str += strlen("yuv_adjust_uv_mul0_")), NULL, 10);
            DSP2_YUV_Adjust_Get_Cfg(idx, &yuvAdjCfg);
            if (type == DSP2_PARSE_WRITE) yuvAdjCfg.uv_mul0 = value;
            val_get = yuvAdjCfg.uv_mul0;
        } else if (strstr(reg, "yuv_adjust_uv_mul1_") != NULL) {
            idx = strtol((str += strlen("yuv_adjust_uv_mul1_")), NULL, 10);
            DSP2_YUV_Adjust_Get_Cfg(idx, &yuvAdjCfg);
            if (type == DSP2_PARSE_WRITE) yuvAdjCfg.uv_mul1 = value;
            val_get = yuvAdjCfg.uv_mul1;
        } else if (strstr(reg, "yuv_adjust_uv_min_") != NULL) {
            idx = strtol((str += strlen("yuv_adjust_uv_min_")), NULL, 10);
            DSP2_YUV_Adjust_Get_Cfg(idx, &yuvAdjCfg);
            if (type == DSP2_PARSE_WRITE) yuvAdjCfg.uv_min = value;
            val_get = yuvAdjCfg.uv_min;
        } else if (strstr(reg, "yuv_adjust_uv_max_") != NULL) {
            idx = strtol((str += strlen("yuv_adjust_uv_max_")), NULL, 10);
            DSP2_YUV_Adjust_Get_Cfg(idx, &yuvAdjCfg);
            if (type == DSP2_PARSE_WRITE) yuvAdjCfg.uv_max = value;
            val_get = yuvAdjCfg.uv_max;
        }
        if (type == DSP2_PARSE_WRITE) DSP2_YUV_Adjust_Set_Cfg(idx, &yuvAdjCfg);
    } else if (strstr(reg, "osd_input_sel_") != NULL) {
        idx = strtol((str += strlen("osd_input_sel_")), NULL, 10);
        if (type == DSP2_PARSE_WRITE) DSP2_MISC_OSD_Input_Select(idx, osdInputType);
        DSP2_MISC_OSD_Get_Input_Select(idx, &osdInputType);
    } else if (strstr(reg, "osd_pb_input_sel_") != NULL) {
        idx = strtol((str += strlen("osd_pb_input_sel_")), NULL, 10);
        if (type == DSP2_PARSE_WRITE) DSP2_MISC_OSD_Pb_Input_Select(osdPbInputType);
        DSP2_MISC_OSD_Pb_Get_Input_Select(&osdPbInputType);
    } else if (strstr(reg, "crop_") != NULL) {
        if (strstr(reg, "crop_en_") != NULL) {
            idx = strtol((str += strlen("crop_hsync_start_")), NULL, 10);
            if (type == DSP2_PARSE_WRITE) {
                if (value == 1) DSP2_MISC_Crop_Enable(idx);
                else DSP2_MISC_Crop_Disable(idx);
                return 0;
            }
            DSP2_MISC_Crop_Get_State(idx, &val_get);
        } else if (strstr(reg, "crop_hsync_start_") != NULL) {
            idx = strtol((str += strlen("crop_hsync_start_")), NULL, 10);
            DSP2_MISC_Crop_Get_Cfg(idx, &cropCfg);
            if (type == DSP2_PARSE_WRITE) cropCfg.hsyncStart = value;
            val_get = cropCfg.hsyncStart;
        } else if (strstr(reg, "crop_hsync_end_") != NULL) {
            idx = strtol((str += strlen("crop_hsync_end_")), NULL, 10);
            DSP2_MISC_Crop_Get_Cfg(idx, &cropCfg);
            if (type == DSP2_PARSE_WRITE) cropCfg.hsyncEnd = value;
            val_get = cropCfg.hsyncEnd;
        } else if (strstr(reg, "crop_vsync_start_") != NULL) {
            idx = strtol((str += strlen("crop_vsync_start_")), NULL, 10);
            DSP2_MISC_Crop_Get_Cfg(idx, &cropCfg);
            if (type == DSP2_PARSE_WRITE) cropCfg.vsyncStart = value;
            val_get = cropCfg.vsyncStart;
        } else if (strstr(reg, "crop_vsync_end_") != NULL) {
            idx = strtol((str += strlen("crop_vsync_end_")), NULL, 10);
            DSP2_MISC_Crop_Get_Cfg(idx, &cropCfg);
            if (type == DSP2_PARSE_WRITE) cropCfg.vsyncEnd = value;
            val_get = cropCfg.vsyncEnd;
        }
        if (type == DSP2_PARSE_WRITE) DSP2_MISC_Crop_Init(idx, &cropCfg);
    } else if (strstr(reg, "scaler_") != NULL) {
        if (strstr(reg, "scaler_en_") != NULL) {
            idx = strtol((str += strlen("scaler_en_")), NULL, 10);
            if (type == DSP2_PARSE_WRITE) {
                if (value == 1) DSP2_MISC_Scaler_Enable(idx);
                else DSP2_MISC_Scaler_Disable(idx);
                return 0;
            }
            DSP2_MISC_Scaler_Get_State(idx, &val_get);
        } else if (strstr(reg, "scaler_input_sel_") != NULL) {
            idx = strtol((str += strlen("scaler_input_sel_")), NULL, 10);
            if (type == DSP2_PARSE_WRITE) {
                DSP2_MISC_Scaler_Input_Select(idx, value);
                return 0;
            }
            DSP2_MISC_Scaler_Get_Input_Select(idx, &val_get);
        } else if (strstr(reg, "scaler_input_width_") != NULL) {
            idx = strtol((str += strlen("scaler_input_width_")), NULL, 10);
            DSP2_MISC_Scaler_Get_Cfg(idx, &scalerCfg);
            if (type == DSP2_PARSE_WRITE) scalerCfg.inputWidth = value;
            val_get = scalerCfg.inputWidth;
        } else if (strstr(reg, "scaler_input_height_") != NULL) {
            idx = strtol((str += strlen("scaler_input_height_")), NULL, 10);
            DSP2_MISC_Scaler_Get_Cfg(idx, &scalerCfg);
            if (type == DSP2_PARSE_WRITE) scalerCfg.inputHeight = value;
            val_get = scalerCfg.inputHeight;
        } else if (strstr(reg, "scaler_output_width_") != NULL) {
            idx = strtol((str += strlen("scaler_output_width_")), NULL, 10);
            DSP2_MISC_Scaler_Get_Cfg(idx, &scalerCfg);
            if (type == DSP2_PARSE_WRITE) scalerCfg.outputWidth = value;
            val_get = scalerCfg.outputWidth;
        } else if (strstr(reg, "scaler_output_height_") != NULL) {
            idx = strtol((str += strlen("scaler_output_height_")), NULL, 10);
            DSP2_MISC_Scaler_Get_Cfg(idx, &scalerCfg);
            if (type == DSP2_PARSE_WRITE) scalerCfg.outputHeight = value;
            val_get = scalerCfg.outputHeight;
        }
        if (type == DSP2_PARSE_WRITE) DSP2_MISC_Scaler_Init(idx, &scalerCfg);

    } else if (strstr(reg, "yuv2rgb") != NULL) {
        if (strstr(reg, "disp_") != NULL) {
            DSP2_MISC_YUV2RGB_Get_Cfg(DSP2_MISC_YUV2RGB_DISPLAY_ID, &yuv2rgbCfg);
            str += strlen("disp_");
        } else {
            DSP2_MISC_YUV2RGB_Get_Cfg(DSP2_MISC_YUV2RGB_NORMAL_ID, &yuv2rgbCfg);
            if (strstr(reg, "yuv2rgb_sel") != NULL) {
                if (type == DSP2_PARSE_WRITE) {
                    DSP2_YUV2RGB_Set_Input(DSP2_YUV2RGB_A, (DSP2_YUV2RGB_Input)value);
                    return 0;
                }
                DSP2_YUV2RGB_Get_Input(DSP2_YUV2RGB_A, (DSP2_YUV2RGB_Input *)&val_get);
            }
        }

        if (strstr(reg, "yuv2rgb_en") != NULL) {
            if (type == DSP2_PARSE_WRITE) yuv2rgbCfg.enable = value;
            val_get = yuv2rgbCfg.enable;
        } else if (strstr(reg, "yuv2rgb_pre_") != NULL) {
            idx = strtol((str += strlen("yuv2rgb_pre_")), NULL, 10);
            if (type == DSP2_PARSE_WRITE) {
                if (idx == 0) yuv2rgbCfg.preOffset0 = value;
                else if (idx == 1) yuv2rgbCfg.preOffset1 = value;
                else if (idx == 2) yuv2rgbCfg.preOffset2 = value;
                else return -1;
            }
            if (idx == 0) val_get = yuv2rgbCfg.preOffset0;
            else if (idx == 1) val_get = yuv2rgbCfg.preOffset1;
            else if (idx == 2) val_get = yuv2rgbCfg.preOffset2;
            else return -1;
        } else if (strstr(reg, "yuv2rgb_post_") != NULL) {
            idx = strtol((str += strlen("yuv2rgb_post_")), NULL, 10);
            if (type == DSP2_PARSE_WRITE) {
                if (idx == 0) yuv2rgbCfg.postOffset0 = value;
                else if (idx == 1) yuv2rgbCfg.postOffset1 = value;
                else if (idx == 2) yuv2rgbCfg.postOffset2 = value;
                else return -1;
            }
            if (idx == 0) val_get = yuv2rgbCfg.postOffset0;
            else if (idx == 1) val_get = yuv2rgbCfg.postOffset1;
            else if (idx == 2) val_get = yuv2rgbCfg.postOffset2;
            else return -1;
        } else if (strstr(reg, "yuv2rgb_mtx_") != NULL) {
            idx = strtol((str += strlen("yuv2rgb_mtx_")), NULL, 10);
            if (type == DSP2_PARSE_WRITE) {
                 if (idx == 0) yuv2rgbCfg.matrix00 = value;
                else if (idx == 1) yuv2rgbCfg.matrix01 = value;
                else if (idx == 2) yuv2rgbCfg.matrix02 = value;
                else if (idx == 10) yuv2rgbCfg.matrix10 = value;
                else if (idx == 11) yuv2rgbCfg.matrix11 = value;
                else if (idx == 12) yuv2rgbCfg.matrix12 = value;
                else if (idx == 20) yuv2rgbCfg.matrix20 = value;
                else if (idx == 21) yuv2rgbCfg.matrix21 = value;
                else if (idx == 22) yuv2rgbCfg.matrix22 = value;
                else return -1;
            }
            if (idx == 0) val_get = yuv2rgbCfg.matrix00;
            else if (idx == 1) val_get = yuv2rgbCfg.matrix01;
            else if (idx == 2) val_get = yuv2rgbCfg.matrix02;
            else if (idx == 10) val_get = yuv2rgbCfg.matrix10;
            else if (idx == 11) val_get = yuv2rgbCfg.matrix11;
            else if (idx == 12) val_get = yuv2rgbCfg.matrix12;
            else if (idx == 20) val_get = yuv2rgbCfg.matrix20;
            else if (idx == 21) val_get = yuv2rgbCfg.matrix21;
            else if (idx == 22) val_get = yuv2rgbCfg.matrix22;
            else return -1;
        }
        if (type == DSP2_PARSE_WRITE) DSP2_MISC_YUV2RGB_Init(idx, &yuv2rgbCfg);
    } else if (strstr(reg, "rgb2yuv") != NULL) {
        DSP2_MISC_Display_RGB2YUV_Get_Cfg(&rgb2yuvCfg);
        if (strstr(reg, "disp_") != NULL) str += strlen("disp_");

        if (strstr(reg, "rgb2yuv_en") != NULL) {
            if (type == DSP2_PARSE_WRITE) rgb2yuvCfg.enable = value;
            val_get = rgb2yuvCfg.enable;
        } else if (strstr(reg, "rgb2yuv_pre_") != NULL) {
            idx = strtol((str += strlen("rgb2yuv_pre_")), NULL, 10);
            if (type == DSP2_PARSE_WRITE) {
                if (idx == 0) rgb2yuvCfg.preOffset0 = value;
                else if (idx == 1) rgb2yuvCfg.preOffset1 = value;
                else if (idx == 2) rgb2yuvCfg.preOffset2 = value;
                else return -1;
            }
            if (idx == 0) val_get = rgb2yuvCfg.preOffset0;
            else if (idx == 1) val_get = rgb2yuvCfg.preOffset1;
            else if (idx == 2) val_get = rgb2yuvCfg.preOffset2;
            else return -1;
        } else if (strstr(reg, "rgb2yuv_post_") != NULL) {
            idx = strtol((str += strlen("rgb2yuv_post_")), NULL, 10);
            if (type == DSP2_PARSE_WRITE) {
                if (idx == 0) rgb2yuvCfg.postOffset0 = value;
                else if (idx == 1) rgb2yuvCfg.postOffset1 = value;
                else if (idx == 2) rgb2yuvCfg.postOffset2 = value;
                else return -1;
            }
            if (idx == 0) val_get = rgb2yuvCfg.postOffset0;
            else if (idx == 1) val_get = rgb2yuvCfg.postOffset1;
            else if (idx == 2) val_get = rgb2yuvCfg.postOffset2;
            else return -1;
        } else if (strstr(reg, "rgb2yuv_mtx_") != NULL) {
            idx = strtol((str += strlen("rgb2yuv_mtx_")), NULL, 10);
            if (type == DSP2_PARSE_WRITE) {
                 if (idx == 0) rgb2yuvCfg.matrix00 = value;
                else if (idx == 1) rgb2yuvCfg.matrix01 = value;
                else if (idx == 2) rgb2yuvCfg.matrix02 = value;
                else if (idx == 10) rgb2yuvCfg.matrix10 = value;
                else if (idx == 11) rgb2yuvCfg.matrix11 = value;
                else if (idx == 12) rgb2yuvCfg.matrix12 = value;
                else if (idx == 20) rgb2yuvCfg.matrix20 = value;
                else if (idx == 21) rgb2yuvCfg.matrix21 = value;
                else if (idx == 22) rgb2yuvCfg.matrix22 = value;
                else return -1;
            }
            if (idx == 0) val_get = rgb2yuvCfg.matrix00;
            else if (idx == 1) val_get = rgb2yuvCfg.matrix01;
            else if (idx == 2) val_get = rgb2yuvCfg.matrix02;
            else if (idx == 10) val_get = rgb2yuvCfg.matrix10;
            else if (idx == 11) val_get = rgb2yuvCfg.matrix11;
            else if (idx == 12) val_get = rgb2yuvCfg.matrix12;
            else if (idx == 20) val_get = rgb2yuvCfg.matrix20;
            else if (idx == 21) val_get = rgb2yuvCfg.matrix21;
            else if (idx == 22) val_get = rgb2yuvCfg.matrix22;
            else return -1;
        }
        if (type == DSP2_PARSE_WRITE) DSP2_MISC_Display_RGB2YUV_Set_Cfg(&rgb2yuvCfg);
    } else if (strstr(reg, "disp_") != NULL) {
        DSP2_MISC_Display_Get_Cfg(&displayCfg);
        if (strstr(reg, "dpiEnable") != NULL) {
            if (type == DSP2_PARSE_WRITE) displayCfg.dpiEnable = value;
            val_get = displayCfg.dpiEnable;
        } else if (strstr(reg, "hdmiEnable") != NULL) {
            if (type == DSP2_PARSE_WRITE) displayCfg.hdmiEnable = value;
            val_get = displayCfg.hdmiEnable;
        } else if (strstr(reg, "bt1120Enable") != NULL) {
            if (type == DSP2_PARSE_WRITE) displayCfg.bt1120Enable = value;
            val_get = displayCfg.bt1120Enable;
        } else if (strstr(reg, "bt656Enable") != NULL) {
            if (type == DSP2_PARSE_WRITE) displayCfg.bt656Enable = value;
            val_get = displayCfg.bt656Enable;
        } else if (strstr(reg, "inputType") != NULL) {
            if (type == DSP2_PARSE_WRITE) displayCfg.inputType = value;
            val_get = displayCfg.inputType;
        } else if (strstr(reg, "osdType") != NULL) {
            if (type == DSP2_PARSE_WRITE) displayCfg.osdType = value;
            val_get = displayCfg.osdType;
        } else if (strstr(reg, "hsyncWidth") != NULL) {
            if (type == DSP2_PARSE_WRITE) displayCfg.hsyncWidth = value;
            val_get = displayCfg.hsyncWidth;
        } else if (strstr(reg, "hfpWidth") != NULL) {
            if (type == DSP2_PARSE_WRITE) displayCfg.hfpWidth = value;
            val_get = displayCfg.hfpWidth;
        } else if (strstr(reg, "vsyncWidth") != NULL) {
            if (type == DSP2_PARSE_WRITE) displayCfg.vsyncWidth = value;
            val_get = displayCfg.vsyncWidth;
        } else if (strstr(reg, "vfpWidth") != NULL) {
            if (type == DSP2_PARSE_WRITE) displayCfg.vfpWidth = value;
            val_get = displayCfg.vfpWidth;
        }
        if (type == DSP2_PARSE_WRITE) DSP2_MISC_Display_Init(&displayCfg);
    } else if (strstr(reg, "dvp_m2n_") != NULL) {
        DSP2_Frame_Get_M_to_N(&m2nCfg);
        if (strstr(reg, "dvp_m2n_en") != NULL) {
            if (type == DSP2_PARSE_WRITE) m2nCfg.enb = value;
            val_get = m2nCfg.enb;
        } else if (strstr(reg, "dvp_m2n_m") != NULL) {
            if (type == DSP2_PARSE_WRITE) m2nCfg.m = value;
            val_get = m2nCfg.m;
        } else if (strstr(reg, "dvp_m2n_n") != NULL) {
            if (type == DSP2_PARSE_WRITE) m2nCfg.n = value;
            val_get = m2nCfg.n;
        } else if (strstr(reg, "dvp_m2n_intv") != NULL) {
            if (type == DSP2_PARSE_WRITE) m2nCfg.intv = value;
            val_get = m2nCfg.intv;
        }
        if (type == DSP2_PARSE_WRITE) DSP2_Frame_M_to_N(&m2nCfg);
    } else {
        return -1;
    }

    if (type == DSP2_PARSE_WRITE) {
        return 0;
    }
    sprintf(ret_string, "[OK] HW DSP2_MISC_%s: %d", reg, val_get);

    return 0;
}

int DSP2_AXI_CTRL_HW_Parse(int type, char* reg, int value, char* ret_string)
{
    int ret = -1;
    int val_get = 0;
    char str_get[32] = {'\0'};
    uint32_t bufAddr = 0, bufSize = 0;
    uint16_t width = 0, height = 0;
    DSP2_3DNR_BUS_Cfg_Type bus_cfg;
    DSP2_3DNR_DVP_Cfg_Type dvp_cfg;
    
    DSP2_3DNR_Get_BUS_Cfg(&bus_cfg);
    DSP2_3DNR_Get_DVP_Cfg(&dvp_cfg);
    DSP2_3DNR_GetImageSize(&width, &height);
    DSP2_3DNR_GetRefFrameBuf(&bufAddr, &bufSize);
    if (strcmp(reg, "img_size_width") == 0) {
        if (type == DSP2_PARSE_WRITE) DSP2_3DNR_SetImageSize(value, height);
        val_get = width;
    } else if (strcmp(reg, "img_size_height") == 0) {
        if (type == DSP2_PARSE_WRITE) DSP2_3DNR_SetImageSize(width, value);
        val_get = height;
    } else if (strcmp(reg, "frame_buf_addr") == 0) {
        if (type == DSP2_PARSE_WRITE) DSP2_3DNR_SetRefFrameBuf(value, bufSize);
        val_get = bufAddr;
        sprintf(ret_string, "[OK] Load_%s: 0x%08x", reg, bufAddr);
    } else if (strcmp(reg, "frame_buf_size") == 0) {
        if (type == DSP2_PARSE_WRITE) DSP2_3DNR_SetRefFrameBuf(bufAddr, value);
        val_get = bufSize;
    } else if (strcmp(reg, "qos_sw_mode") == 0) {
        if (type == DSP2_PARSE_WRITE) DSP2_3DNR_Set_Qos_Sw_Mode(value);
        DSP2_3DNR_Get_Qos_Sw_Mode(&val_get);
    } else if (strcmp(reg, "qos_sw_val") == 0) {
        if (type == DSP2_PARSE_WRITE) DSP2_3DNR_Set_Qos_Sw_Val(value);
        DSP2_3DNR_Get_Qos_Sw_Val(&val_get);
    } else if (strcmp(reg, "bus_r_flsh") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        val_get = bus_cfg.r_flsh;
    } else if (strcmp(reg, "bus_r_fend") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        val_get = bus_cfg.r_fend;
    } else if (strcmp(reg, "bus_r_func") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        val_get = bus_cfg.r_func;
    } else if (strcmp(reg, "bus_r_idle") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        val_get = bus_cfg.r_idle;
    } else if (strcmp(reg, "bus_w_flsh") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        val_get = bus_cfg.w_flsh;
    } else if (strcmp(reg, "bus_w_fend") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        val_get = bus_cfg.w_fend;
    } else if (strcmp(reg, "bus_w_func") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        val_get = bus_cfg.w_func;
    } else if (strcmp(reg, "bus_w_idle") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        val_get = bus_cfg.w_idle;
    } else if (strcmp(reg, "dvp_r_flsh") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        val_get = dvp_cfg.r_flsh;
    } else if (strcmp(reg, "dvp_r_fend") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        val_get = dvp_cfg.r_fend;
    } else if (strcmp(reg, "dvp_r_func") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        val_get = dvp_cfg.r_func;
    } else if (strcmp(reg, "dvp_r_wtst") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        val_get = dvp_cfg.r_wtst;
    } else if (strcmp(reg, "dvp_r_idle") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        val_get = dvp_cfg.r_idle;
    } else if (strcmp(reg, "dvp_w_flsh") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        val_get = dvp_cfg.w_flsh;
    } else if (strcmp(reg, "dvp_w_fend") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        val_get = dvp_cfg.w_fend;
    } else if (strcmp(reg, "dvp_w_func") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        val_get = dvp_cfg.w_func;
    } else if (strcmp(reg, "dvp_w_wtst") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        val_get = dvp_cfg.w_wtst;
    } else if (strcmp(reg, "dvp_w_idle") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        val_get = dvp_cfg.w_idle;
    } else {
        return -1;
    }

    if (type == DSP2_PARSE_WRITE) {
        return 0;
    }
    if (strcmp(reg, "frame_buf_addr") == 0) {
        val_get = bufAddr;
        sprintf(ret_string, "[OK] HW AXI_CTRL_%s: 0x%8x", reg, (uint32_t)val_get);
    } else {
        sprintf(ret_string, "[OK] HW AXI_CTRL_%s: %d", reg, val_get);
    }
    return 0;
}

int DSP2_TG_HW_Parse(int type, char* reg, int value, char* ret_string)
{
    int ret = -1;
    int val_get = 0;
    char str_get[32] = {'\0'};
    int version = 0, ip_id = 0;
    int start_pixel = 0, start_line = 0;
    BL_Img_Size_T win = {0};
    DSP2_DVP_MODE_CFG_T dvp_mod_cfg = {0};

    DSP2_Get_IP_Info(&version, &ip_id);
    DSP2_Get_DVP_Mode_Cfg(&dvp_mod_cfg);
    if (strcmp(reg, "version") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        val_get = version;
    } else if (strcmp(reg, "ip_id") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        val_get = ip_id;
    } else if (strcmp(reg, "reg_act_vsync_rst_en") == 0) {
        if (type == DSP2_PARSE_WRITE) dvp_mod_cfg.reg_act_vsync_rst_en = value;
        val_get = dvp_mod_cfg.reg_act_vsync_rst_en;
    } else if (strcmp(reg, "sync_mode") == 0) {
        if (type == DSP2_PARSE_WRITE) dvp_mod_cfg.sync_mode = value;
        val_get = dvp_mod_cfg.sync_mode;
    } else if (strcmp(reg, "hsync_in_inv") == 0) {
        if (type == DSP2_PARSE_WRITE) dvp_mod_cfg.hsync_in_inv = value;
        val_get = dvp_mod_cfg.hsync_in_inv;
    } else if (strcmp(reg, "vsync_in_inv") == 0) {
        if (type == DSP2_PARSE_WRITE) dvp_mod_cfg.vsync_in_inv = value;
        val_get = dvp_mod_cfg.vsync_in_inv;
    } else if (strcmp(reg, "hcnt_rst_mode") == 0) {
        if (type == DSP2_PARSE_WRITE) dvp_mod_cfg.hcnt_rst_mode = value;
        val_get = dvp_mod_cfg.hcnt_rst_mode;
    } else if (strcmp(reg, "vcnt_rst_mode") == 0) {
        if (type == DSP2_PARSE_WRITE) dvp_mod_cfg.vcnt_rst_mode = value;
        val_get = dvp_mod_cfg.vcnt_rst_mode;
    } else if (strcmp(reg, "hblk_line_on") == 0) {
        if (type == DSP2_PARSE_WRITE) dvp_mod_cfg.hblk_line_on = value;
        val_get = dvp_mod_cfg.hblk_line_on;
    } else if (strcmp(reg, "fhblk_line_on") == 0) {
        if (type == DSP2_PARSE_WRITE) dvp_mod_cfg.fhblk_line_on = value;
        val_get = dvp_mod_cfg.fhblk_line_on;
    } else if (strstr(reg, "total_") != NULL) {
        DSP2_Get_Total_Pixels(&win);
        if (strcmp(reg, "total_width") == 0) {
            if (type == DSP2_PARSE_WRITE) win.width = value;
            val_get = win.width;
        } else if (strcmp(reg, "total_height") == 0) {
            if (type == DSP2_PARSE_WRITE) win.height = value;
            val_get = win.height;
        }
        if (type == DSP2_PARSE_WRITE) DSP2_Set_Total_Pixels(&win);
    } else if (strstr(reg, "active_") != NULL) {
        DSP2_Get_Active_Pixels(&start_pixel, &start_line, &win);
        if (strcmp(reg, "active_start_pixel") == 0) {
            if (type == DSP2_PARSE_WRITE) start_pixel = value;
            val_get = start_pixel;
        } else if (strcmp(reg, "active_start_line") == 0) {
            if (type == DSP2_PARSE_WRITE) start_line = value;
            val_get = start_line;
        } else if (strcmp(reg, "active_width") == 0) {
            if (type == DSP2_PARSE_WRITE) win.width = value;
            val_get = win.width;
        } else if (strcmp(reg, "active_height") == 0) {
            if (type == DSP2_PARSE_WRITE) win.height = value;
            val_get = win.height;
        }
        if (type == DSP2_PARSE_WRITE) DSP2_Set_Active_Pixels(start_pixel, start_line, &win);
    } else if (strstr(reg, "output_") != NULL) {
        DSP2_Get_Output_Pixels(&start_pixel, &start_line, &win);
        if (strcmp(reg, "output_start_pixel") == 0) {
            if (type == DSP2_PARSE_WRITE) start_pixel = value;
            val_get = start_pixel;
        } else if (strcmp(reg, "output_start_line") == 0) {
            if (type == DSP2_PARSE_WRITE) start_line = value;
            val_get = start_line;
        } else if (strcmp(reg, "output_width") == 0) {
            if (type == DSP2_PARSE_WRITE) win.width = value;
            val_get = win.width;
        } else if (strcmp(reg, "output_height") == 0) {
            if (type == DSP2_PARSE_WRITE) win.height = value;
            val_get = win.height;
        }
        if (type == DSP2_PARSE_WRITE) DSP2_Set_Output_Pixels(start_pixel, start_line, &win);
    } else {
        return -1;
    }

    if (type == DSP2_PARSE_WRITE) {
        if ((strstr(reg, "total_") != NULL) || (strstr(reg, "active_") != NULL) || (strstr(reg, "output_") != NULL)) return 0;
        DSP2_Set_DVP_Mode_Cfg(&dvp_mod_cfg);
        return 0;
    }
    sprintf(ret_string, "[OK] HW TG_%s: %d", reg, val_get);

    return 0;
}

int DSP2_Module_State_FW_Parse(int type, char* reg, int value, char* ret_string)
{
    int val_get = 0;
    BL_Fun_Type enable = value;

    if (strcmp(reg, "ae") == 0) {
        if (type == DSP2_PARSE_WRITE) imgproc_set_fw_module_en(DSP2_ADJ_AE, enable);
        val_get = imgproc_get_fw_module_en(DSP2_ADJ_AE);
    } else if (strcmp(reg, "awb") == 0) {
        if (type == DSP2_PARSE_WRITE) imgproc_set_fw_module_en(DSP2_ADJ_AWB, enable);
        val_get = imgproc_get_fw_module_en(DSP2_ADJ_AWB);
    } else if (strcmp(reg, "blc") == 0) {
        if (type == DSP2_PARSE_WRITE) imgproc_set_fw_module_en(DSP2_ADJ_BLC, enable);
        val_get = imgproc_get_fw_module_en(DSP2_ADJ_BLC);
    } else if (strcmp(reg, "dpc") == 0) {
        if (type == DSP2_PARSE_WRITE) imgproc_set_fw_module_en(DSP2_ADJ_DPC, enable);
        val_get = imgproc_get_fw_module_en(DSP2_ADJ_DPC);
    } else if (strcmp(reg, "bnr") == 0) {
        if (type == DSP2_PARSE_WRITE) imgproc_set_fw_module_en(DSP2_ADJ_BNR, enable);
        val_get = imgproc_get_fw_module_en(DSP2_ADJ_BNR);
    } else if (strcmp(reg, "lsc") == 0) {
        if (type == DSP2_PARSE_WRITE) imgproc_set_fw_module_en(DSP2_ADJ_LSC, enable);
        val_get = imgproc_get_fw_module_en(DSP2_ADJ_LSC);
    } else if (strcmp(reg, "ccm") == 0) {
        if (type == DSP2_PARSE_WRITE) imgproc_set_fw_module_en(DSP2_ADJ_CCM, enable);
        val_get = imgproc_get_fw_module_en(DSP2_ADJ_CCM);
    } else if (strcmp(reg, "gamma") == 0) {
        if (type == DSP2_PARSE_WRITE) imgproc_set_fw_module_en(DSP2_ADJ_GAMMA, enable);
        val_get = imgproc_get_fw_module_en(DSP2_ADJ_GAMMA);
    } else if (strcmp(reg, "wdr") == 0) {
        if (type == DSP2_PARSE_WRITE) imgproc_set_fw_module_en(DSP2_ADJ_WDR, enable);
        val_get = imgproc_get_fw_module_en(DSP2_ADJ_WDR);
    } else if (strcmp(reg, "saturation") == 0) {
        if (type == DSP2_PARSE_WRITE) imgproc_set_fw_module_en(DSP2_ADJ_SATURATION, enable);
        val_get = imgproc_get_fw_module_en(DSP2_ADJ_SATURATION);
    } else if (strcmp(reg, "nr") == 0) {
        if (type == DSP2_PARSE_WRITE) imgproc_set_fw_module_en(DSP2_ADJ_NR, enable);
        val_get = imgproc_get_fw_module_en(DSP2_ADJ_NR);
    } else if (strcmp(reg, "ee") == 0) {
        if (type == DSP2_PARSE_WRITE) imgproc_set_fw_module_en(DSP2_ADJ_EE, enable);
        val_get = imgproc_get_fw_module_en(DSP2_ADJ_EE);
    } else if (strcmp(reg, "cs") == 0) {
        if (type == DSP2_PARSE_WRITE) imgproc_set_fw_module_en(DSP2_ADJ_CS, enable);
        val_get = imgproc_get_fw_module_en(DSP2_ADJ_CS);
    } else if (strcmp(reg, "yc") == 0) {
        if (type == DSP2_PARSE_WRITE) imgproc_set_fw_module_en(DSP2_ADJ_YC, enable);
        val_get = imgproc_get_fw_module_en(DSP2_ADJ_YC);
    } else {
        return -1;
    }

    if (type == DSP2_PARSE_WRITE) {
        return 0;
    }
    sprintf(ret_string, "[OK] module_%s: %d", reg, val_get);

    return 0;
}

int DSP2_AE_FW_Metering_Tbl_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i = 0, idx = 0;
    DSP2_AE_METERING_TBL ae_metering_tbl = {0};
    DSP2_AE_METERING_TBL *ae_metering_tbl_ptr;
    
    char *token;
    token = strtok(reg, "metering_tbl_");
    idx = atoi(token);
    if ((idx > AE_METERING_TBL_NUM - 1) || (idx < 0))  return -1;

    if (type == DSP2_PARSE_WRITE) {
        for (i = 0; i < AE_STATS_GRID_NUM; i++) {
            ae_metering_tbl.coef[i] = value[i];
        }
        img_param_sw_set_ae_metering_tbl(idx, &ae_metering_tbl);
        imgproc_set_fw_module_en(DSP2_ADJ_AE, 1);
        return 0;
    }

    img_param_sw_get_ae_metering_tbl(idx, &ae_metering_tbl_ptr);
    sprintf(ret_string, "[OK] AE_%s: ", reg);
    for (i = 0; i < AE_STATS_GRID_NUM; i++) {
        strCatVal(ret_string, ae_metering_tbl_ptr->coef[i]);
    }

    return 0;
}

int DSP2_AE_FW_Agc_DB_Tbl_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i = 0;
    ae_agc_db_tbl *ptr;

    if (type == DSP2_PARSE_WRITE) {
        return -1;
    }

    img_param_get_ae_agc_db_tbl(&ptr);
    sprintf(ret_string, "[OK] AE_%s: ", reg);
    for (i = 0; i < MAX_ENTRY_NUM_AE_AGC_DB_TBL; i++) {
        strCatVal(ret_string, ptr->agc_db[i]);
    }

    return 0;
}

int DSP2_AE_FW_Auto_Tbl_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i = 0;
    DSP2_AE_SUB_ATTR *ptr;
    DSP2_AE_SUB_ATTR tbl = {0};
    DSP2_AE_HIGHLIGHT_WEIGHT *ae_highlight_weight_ptr = {0};
    DSP2_AE_HIGHLIGHT_WEIGHT ae_highlight_weight = {0};

    if (type == DSP2_PARSE_WRITE) {
        for (i = 0; i < MAX_ENTRY_NUM_AE_SYS_GAIN_AUTO; i++) {
            if (strcmp(reg, "ae_target") == 0) {
                img_param_sw_get_ae(i, &ptr);
                memcpy(&tbl, ptr, sizeof(DSP2_AE_SUB_ATTR));
                tbl.ae_target = value[i];
                img_param_sw_set_ae(i, &tbl);
            } else if (strstr(reg, "highlight_weight_idx_") != NULL){
                img_param_sw_get_ae_highlight_weight(i, &ae_highlight_weight_ptr);
                memcpy(&ae_highlight_weight, ae_highlight_weight_ptr, sizeof(DSP2_AE_SUB_ATTR));
                if (strcmp(reg, "highlight_weight_idx_0") == 0) ae_highlight_weight.idx[0] = value[i];
                else if (strcmp(reg, "highlight_weight_idx_1") == 0) ae_highlight_weight.idx[1] = value[i];
                else if (strcmp(reg, "highlight_weight_idx_2") == 0) ae_highlight_weight.idx[2] = value[i];
                else return -1;
                img_param_sw_set_ae_highlight_weight(i, &ae_highlight_weight);
            }
            else return -1;
        }
        imgproc_set_fw_module_en(DSP2_ADJ_AE, 1);
        return 0;
    }

    sprintf(ret_string, "[OK] auto AE_%s: ", reg);
    for (i = 0; i < MAX_ENTRY_NUM_AE_SYS_GAIN_AUTO; i++) {
        if (strcmp(reg, "ae_target") == 0) {
            img_param_sw_get_ae(i, &ptr);
            strCatVal(ret_string, ptr->ae_target);
        } else if (strstr(reg, "highlight_weight_idx_") != NULL) {
            img_param_sw_get_ae_highlight_weight(i, &ae_highlight_weight_ptr);
            if (strcmp(reg, "highlight_weight_idx_0") == 0) strCatVal(ret_string, ae_highlight_weight_ptr->idx[0]);
            else if (strcmp(reg, "highlight_weight_idx_1") == 0) strCatVal(ret_string, ae_highlight_weight_ptr->idx[1]);
            else if (strcmp(reg, "highlight_weight_idx_2") == 0) strCatVal(ret_string, ae_highlight_weight_ptr->idx[2]);
            else return -1;
        } else return -1;
    }

    return 0;
}

int DSP2_AE_FW_Parse(int type, char* reg, int value, char* ret_string)
{
    int val_get = 0;
    ae_info_t *ae_info = {0};
    float gain_f = 0.0;
    DSP2_AE_HIGHLIGHT_WEIGHT_CONF *highlight_weight_cfg = {0};
    BL_EXPO_TIME expo_time = EXPO_TIME_1_25_SEC;
    ae_slow_shutter_conf_t *slow_shutter_conf = {0};

    ae_get_info(&ae_info);
    if (strcmp(reg, "ae_target") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        ae_get_luma_target(&val_get);
    } else if (strcmp(reg, "algo") == 0) {
        if (type == DSP2_PARSE_WRITE) imgproc_set_ae_algo(value);
        val_get = imgproc_get_ae_algo();
    } else if (strcmp(reg, "version") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        ae_get_algo_version(&val_get);
    } else if (strcmp(reg, "ISO") == 0) {
        if (type == DSP2_PARSE_WRITE) {
            if(value == 100) { // 12 db
                expo_time = EXPO_TIME_1_25_SEC;
                gain_f = 0.0;
            } else if(value == 200) { // 18 db
                expo_time = EXPO_TIME_1_25_SEC;
                gain_f = 6.0;
            } else if(value == 400) { // 24 db
                expo_time = EXPO_TIME_1_25_SEC;
                gain_f = 12.0;
            } else if(value == 800) { // 30 db
                expo_time = EXPO_TIME_1_25_SEC;
                gain_f = 18.0;
            } else if(value == 1600) { // 36 db
                expo_time = EXPO_TIME_1_25_SEC;
                gain_f = 24.0;
            } else if(value == 3200) { // 42 db
                expo_time = EXPO_TIME_1_25_SEC;
                gain_f = 30.0;
            } else if(value == 6400) { // 48 db
                expo_time = EXPO_TIME_1_25_SEC;
                gain_f = 36.0;
            } else if(value == 12800) { // 54 db
                expo_time = EXPO_TIME_1_25_SEC;
                gain_f = 42.0;
            }
            ae_set_sensor_exposure(expo_time);
            ae_set_sensor_gain(gain_f);

            imgproc_set_2A_keep_reg("ISO", GAIN_DB_FLOAT_TO_INT(gain_f), expo_time, NULL);
        }
        ae_get_sensor_gain(&gain_f);
        val_get = (int)(pow(2, gain_f / 6) * 100);
    } else if (strcmp(reg, "expo_time") == 0) {
        if (type == DSP2_PARSE_WRITE) ae_set_sensor_exposure(EXPO_TIME_TO_INT(value));// expo: 1/value
        val_get = ae_info->expo_time;
    } else if (strcmp(reg, "gain") == 0) {
        if (type == DSP2_PARSE_WRITE) {
            value = gain_f * 1536;
            ae_set_sensor_gain(value);
        }
        val_get = ae_info->iso / 1536;
    } else if (strcmp(reg, "iso") == 0) {
        if (type == DSP2_PARSE_WRITE) ae_set_sensor_gain(value);
        val_get = ae_info->iso;
    } else if (strcmp(reg, "sys_gain") == 0) {
        if (type == DSP2_PARSE_WRITE) ae_set_sensor_gain(value);
        #if 0
        ae_get_sensor_exposure(&expo_time);
        ae_get_sensor_gain(&gain_f);
        BL_GAIN_DB gain = GAIN_DB_FLOAT_TO_INT(gain_f);
        gen_sys_gain_by_expo_gain(expo_time, gain);
        #else
        val_get = ae_info->sys_gain;
        #endif
    } else if (strstr(reg, "slow_shutter_") != NULL) {
        img_param_get_ae_slow_shutter_conf(&slow_shutter_conf);
        if (strcmp(reg, "slow_shutter_en") == 0) {
            if (type == DSP2_PARSE_WRITE) return -1;
            val_get = slow_shutter_conf->enable;
        } else if (strcmp(reg, "slow_shutter_fps") == 0) {
            if (type == DSP2_PARSE_WRITE) return -1;
            val_get = slow_shutter_conf->fps;
        }
    } else if (strcmp(reg, "highlight_weight_hist_sum") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        val_get = ae_info->highlight_weight.hist_sum;
    } else if (strcmp(reg, "highlight_weight_idx") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        val_get = ae_info->highlight_weight.idx;
    } else if (strcmp(reg, "speed_level") == 0) {
        if (type == DSP2_PARSE_WRITE) ae_set_speed_level(value);
        ae_get_speed_level(&val_get);
    } else if (strcmp(reg, "hist_weight_mode") == 0) {
        if (type == DSP2_PARSE_WRITE) ae_set_hist_weight_mode(value);
        ae_get_hist_weight_mode(&val_get);
    } else if (strcmp(reg, "hist_state") == 0) {
        if (type == DSP2_PARSE_WRITE) bl_set_AE_hist_state(value);
        bl_get_AE_hist_state(&val_get);
    } else if (strcmp(reg, "hist_mode") == 0) {
        if (type == DSP2_PARSE_WRITE) bl_set_AE_hist_mode((AE_HIST_MODE_TYPE_E)value);
        bl_get_AE_hist_mode((AE_HIST_MODE_TYPE_E *)&val_get);
    } else if (strcmp(reg, "metering_mode") == 0) {
        if (type == DSP2_PARSE_WRITE) {
            ae_set_metering_mode((AE_METERING)value);
            imgproc_set_fw_module_en(DSP2_ADJ_AE, 1);
        }
        ae_get_metering_mode((AE_METERING *)&val_get);
    } else if (strcmp(reg, "mode") == 0) {
        if (type == DSP2_PARSE_WRITE) ae_set_mode((AE_MODE)value);
        ae_get_mode((AE_MODE *)&val_get);
    } else if (strcmp(reg, "linearity_mode") == 0) {
        if (type == DSP2_PARSE_WRITE) ae_set_linearity(value);
        ae_get_linearity(&val_get);
    } else if (strcmp(reg, "highlight_weight_en") == 0){
        if (type == DSP2_PARSE_WRITE) {
            img_param_sw_set_ae_highlight_weight_en(value);
            imgproc_set_fw_module_en(DSP2_ADJ_AE, 1);
            return 0;
        }
        img_param_sw_get_ae_highlight_weight_en(&val_get);
    } else if (strstr(reg, "highlight_weight_") != NULL) {
        img_param_sw_get_ae_highlight_weight_conf(&highlight_weight_cfg);
        if (type == DSP2_PARSE_WRITE) {
            if (strcmp(reg, "highlight_weight_thr_0") == 0) highlight_weight_cfg->thr[0] = value;
            else if (strcmp(reg, "highlight_weight_thr_1") == 0) highlight_weight_cfg->thr[1] = value;
            else if (strcmp(reg, "highlight_weight_thr_2") == 0) highlight_weight_cfg->thr[2] = value;
            else if (strcmp(reg, "highlight_weight_thr_3") == 0) highlight_weight_cfg->thr[3] = value;
            else if (strcmp(reg, "highlight_weight_roi_start") == 0) highlight_weight_cfg->roi_start = value;
            else if (strcmp(reg, "highlight_weight_roi_end") == 0) highlight_weight_cfg->roi_end = value;
            else return -1;
            img_param_sw_set_ae_highlight_weight_conf(highlight_weight_cfg);
            imgproc_set_fw_module_en(DSP2_ADJ_AE, 1);
            return 0;
        }
        if (strcmp(reg, "highlight_weight_thr_0") == 0) val_get = highlight_weight_cfg->thr[0];
        else if (strcmp(reg, "highlight_weight_thr_1") == 0) val_get = highlight_weight_cfg->thr[1];
        else if (strcmp(reg, "highlight_weight_thr_2") == 0) val_get = highlight_weight_cfg->thr[2];
        else if (strcmp(reg, "highlight_weight_thr_3") == 0) val_get = highlight_weight_cfg->thr[3];
        else if (strcmp(reg, "highlight_weight_roi_start") == 0) val_get = highlight_weight_cfg->roi_start;
        else if (strcmp(reg, "highlight_weight_roi_end") == 0) val_get = highlight_weight_cfg->roi_end;
        else return -1;
    } else {
        return -1;
    }

    if (type == DSP2_PARSE_WRITE) {
        return 0;
    }
    sprintf(ret_string, "[OK] AE_%s: %d", reg, val_get);

    return 0;
}

int DSP2_AE_HW_Parse(int type, char* reg, int value, char* ret_string)
{
    int val_get = 0;
    int roi_en = 0;
    uint8_t coeff_r = 0, coeff_g = 0, coeff_b = 0;
    dsp2_ae_stats_conf_t ae_stats_conf;
    dsp2_ae_hist_roi_t roi;

    if (strstr(reg, "hist_") != NULL) {
        DSP2_Get_AE_Hist_ROI(ENABLE, &roi);
        if (strcmp(reg, "hist_en") == 0) {
            if (type == DSP2_PARSE_WRITE) DSP2_Set_AE_Hist_State(value);
            DSP2_Get_AE_Hist_State(&val_get);
        } else if (strcmp(reg, "hist_mode") == 0) {
            if (type == DSP2_PARSE_WRITE) DSP2_Set_AE_Hist_Mode(value);
            DSP2_Get_AE_Hist_Mode(&val_get);
        } else if (strcmp(reg, "hist_roi_en") == 0) {
            if (type == DSP2_PARSE_WRITE) DSP2_Set_AE_Hist_ROI_State(value);
            DSP2_Get_AE_Hist_ROI_State(&val_get);
        } else if (strcmp(reg, "hist_roi_x_min") == 0) {
            if (type == DSP2_PARSE_WRITE) roi.ae_hist_x_min = value;
            val_get = roi.ae_hist_x_min;
        } else if (strcmp(reg, "hist_roi_x_max") == 0) {
            if (type == DSP2_PARSE_WRITE) roi.ae_hist_x_max = value;
            val_get = roi.ae_hist_x_max;
        } else if (strcmp(reg, "hist_roi_y_min") == 0) {
            if (type == DSP2_PARSE_WRITE) roi.ae_hist_y_min = value;
            val_get = roi.ae_hist_y_min;
        } else if (strcmp(reg, "hist_roi_y_max") == 0) {
            if (type == DSP2_PARSE_WRITE) roi.ae_hist_y_max = value;
            val_get = roi.ae_hist_y_max;
        } else {
            return -1;
        }

        if (type == DSP2_PARSE_WRITE) {
            if (strstr(reg, "hist_roi") != NULL) DSP2_Set_AE_Hist_ROI(ENABLE, &roi);
            return 0;
        }
        sprintf(ret_string, "[OK] HW AE_%s: %d", reg, val_get);
        return 0;
    }

    DSP2_Get_AE_Ysum_Coeff(&coeff_r, &coeff_g, &coeff_b);
    DSP2_Get_AE_Stats_Conf(&ae_stats_conf);
    if (strstr(reg, "ysum_coeff") != NULL) {
        if (strcmp(reg, "ysum_coeff_r") == 0) {
            if (type == DSP2_PARSE_WRITE) DSP2_Set_AE_Ysum_Coeff(value, coeff_g, coeff_b);
            val_get = coeff_r;
        } else if (strcmp(reg, "ysum_coeff_g") == 0) {
            if (type == DSP2_PARSE_WRITE) DSP2_Set_AE_Ysum_Coeff(coeff_r, value, coeff_b);
            val_get = coeff_g;
        } else if (strcmp(reg, "ysum_coeff_b") == 0) {
            if (type == DSP2_PARSE_WRITE) DSP2_Set_AE_Ysum_Coeff(coeff_r, coeff_g, value);
            val_get = coeff_b;
        } else return -1;
    } else if (strcmp(reg, "roi_start_x") == 0) {
        if (type == DSP2_PARSE_WRITE) ae_stats_conf.roi_start_x = value;
        val_get = ae_stats_conf.roi_start_x;
    } else if (strcmp(reg, "roi_start_y") == 0) {
        if (type == DSP2_PARSE_WRITE) ae_stats_conf.roi_start_y = value;
        val_get = ae_stats_conf.roi_start_y;
    } else if (strcmp(reg, "roi_width") == 0) {
        if (type == DSP2_PARSE_WRITE) ae_stats_conf.roi_width = value;
        val_get = ae_stats_conf.roi_width;
    } else if (strcmp(reg, "roi_height") == 0) {
        if (type == DSP2_PARSE_WRITE) ae_stats_conf.roi_height = value;
        val_get = ae_stats_conf.roi_height;
    } else if (strcmp(reg, "img_width") == 0) {
        if (type == DSP2_PARSE_WRITE) ae_stats_conf.img_width = value;
        val_get = ae_stats_conf.img_width;
    } else if (strcmp(reg, "img_height") == 0) {
        if (type == DSP2_PARSE_WRITE) ae_stats_conf.img_height = value;
        val_get = ae_stats_conf.img_height;
    } else if (strcmp(reg, "grid_width") == 0) {
        if (type == DSP2_PARSE_WRITE) ae_stats_conf.grid_width = value;
        val_get = ae_stats_conf.grid_width;
    } else if (strcmp(reg, "grid_height") == 0) {
        if (type == DSP2_PARSE_WRITE) ae_stats_conf.grid_height = value;
        val_get = ae_stats_conf.grid_height;
    } else if (strcmp(reg, "grid_num_x") == 0) {
        if (type == DSP2_PARSE_WRITE) ae_stats_conf.grid_num_x = value;
        val_get = ae_stats_conf.grid_num_x;
    } else if (strcmp(reg, "grid_num_y") == 0) {
        if (type == DSP2_PARSE_WRITE) ae_stats_conf.grid_num_y = value;
        val_get = ae_stats_conf.grid_num_y;
    } else {
        return -1;
    }

    if (type == DSP2_PARSE_WRITE) {
        if (strstr(reg, "ysum_coeff") != NULL) return 0;
        DSP2_Set_AE_Stats_Conf(&ae_stats_conf);
        return 0;
    }

    sprintf(ret_string, "[OK] HW AE_%s: %d", reg, val_get);

    return 0;
}

int DSP2_WB_Info_Calib_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i = 0, reg_num = 3;
    int tbl_num = img_param_calib_get_wb_info_num();
    wb_info_t *cal_ptr;
    wb_info_t cal_tbl[MAX_ENTRY_NUM_AWB_CT_AUTO] = {0};

    if (type == DSP2_PARSE_WRITE) {
        for (i = 0; i < tbl_num; i++) {
            cal_tbl[i].rb_gain.r_gain = value[i * reg_num + 0];
            cal_tbl[i].rb_gain.b_gain = value[i * reg_num + 1];
            cal_tbl[i].color_temp = value[i * reg_num + 2];
        }
        img_param_calib_set_wb_info(cal_tbl, tbl_num);
        imgproc_set_fw_module_en(DSP2_ADJ_AWB, 1);
        return 0;
    }

    sprintf(ret_string, "[OK] CALIB WB INFO: ");
    for (i = 0; i < tbl_num; i++) {
        img_param_calib_get_wb_info(i, &cal_ptr);
        strCatVal(ret_string, cal_ptr->rb_gain.r_gain);
        strCatVal(ret_string, cal_ptr->rb_gain.b_gain);
        strCatVal(ret_string, cal_ptr->color_temp);
    }

    return 0;
}

int DSP2_AWB3_Calib_Bin_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i = 0;
    wb3_cal_bin_t *cal_ptr;
    wb3_cal_bin_t cal_tbl = {0};

    if (type == DSP2_PARSE_WRITE) {
        for (i = 0; i < MAX_ENTRY_NUM_AWB3_CAL_BIN_NUM; i++) {
            cal_tbl.bin[i] = value[i];
        }
        img_param_calib_set_awb(&cal_tbl);
        imgproc_set_fw_module_en(DSP2_ADJ_AWB, 1);
        return 0;
    }

    sprintf(ret_string, "[OK] CALIB AWB: ");
    img_param_calib_get_awb(&cal_ptr);
    for (i = 0; i < MAX_ENTRY_NUM_AWB3_CAL_BIN_NUM; i++) {
        strCatVal(ret_string, cal_ptr->bin[i]);
    }

    return 0;
}

int DSP2_AWB_FW_Parse(int type, char* reg, int value, char* ret_string)
{
    int64_t val_get = 0;

    bl_get_AWB3_sum(&awb3_sum);
    if (strcmp(reg, "color_temp") == 0) {
        if (type == DSP2_PARSE_WRITE) {
            awb_set_color_temp(value);
            imgproc_set_2A_keep_reg("CT", NULL, NULL, value);
        }
        awb_get_color_temp((BL_COLOR_TEMP *)&val_get);
    } else if (strcmp(reg, "algo") == 0) {
        if (type == DSP2_PARSE_WRITE) imgproc_set_awb_algo(value);
        val_get = imgproc_get_awb_algo();
    } else if (strcmp(reg, "version") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        awb_get_algo_version(&val_get);
    } else if (strcmp(reg, "speed_level") == 0) {
        if (type == DSP2_PARSE_WRITE) awb_set_speed_level(value);
        awb_get_speed_level((int *)&val_get);
    } else if (strcmp(reg, "special_color_flag") == 0) {
        if (type == DSP2_PARSE_WRITE) awb_set_special_color_flag(value);
        awb_get_special_color_flag((int *)&val_get);
    } else if (strcmp(reg, "preference_en") == 0) {
        if (type == DSP2_PARSE_WRITE) img_param_sw_set_awb_preference_en(value);
        img_param_sw_get_awb_preference_en((int *)&val_get);
    } else if (strcmp(reg, "special_color_en") == 0) {
        if (type == DSP2_PARSE_WRITE) {
            img_param_sw_set_awb_special_color_en(value);
            awb_set_special_color_flag(1);
        }
        img_param_sw_get_awb_special_color_en((int *)&val_get);
    } else {
        return -1;
    }

    if (type == DSP2_PARSE_WRITE) {
        return 0;
    }
    sprintf(ret_string, "[OK] AWB_%s: %ld", reg, val_get);

    return 0;
}

int DSP2_AWB_HW_Parse(int type, char* reg, int value, char* ret_string)
{
    int64_t val_get = 0;
    DSP2_RGB_Gain_Type gain;
    DSP2_RGB_Offset_Type offset;

    DSP2_Get_AWB3_Sum(&awb3_sum);
    if (strstr(reg, "gain") != NULL) {
        DSP2_Get_AWB_Gain(&gain);
        if (strcmp(reg, "r_gain") == 0) {
            if (type == DSP2_PARSE_WRITE) gain.r_gain = value;
            val_get = gain.r_gain;
        } else if (strcmp(reg, "g_gain") == 0) {
            if (type == DSP2_PARSE_WRITE) gain.g_gain = value;
            val_get = gain.g_gain;
        } else if (strcmp(reg, "b_gain") == 0) {
            if (type == DSP2_PARSE_WRITE) gain.b_gain = value;
            val_get = gain.b_gain;
        }
        if (type == DSP2_PARSE_WRITE) DSP2_Set_AWB_Gain(&gain);
    } else if (strstr(reg, "offset") != NULL) {
        DSP2_Get_AWB_Offset(&offset);
        if (strcmp(reg, "r_offset") == 0) {
            if (type == DSP2_PARSE_WRITE) offset.r_offset = value;
            val_get = offset.r_offset;
        } else if (strcmp(reg, "g_offset") == 0) {
            if (type == DSP2_PARSE_WRITE) offset.g_offset = value;
            val_get = offset.g_offset;
        } else if (strcmp(reg, "b_offset") == 0) {
            if (type == DSP2_PARSE_WRITE) offset.b_offset = value;
            val_get = offset.b_offset;
        }
        if (type == DSP2_PARSE_WRITE) DSP2_Set_AWB_Offset(&offset);
    } else if (strcmp(reg, "bin_mode") == 0) {
        if (type == DSP2_PARSE_WRITE) DSP2_Set_AWB3_Bin_Mode((dsp2_awb3_bin_mode_e)value);
        DSP2_Get_AWB3_Bin_Mode((dsp2_awb3_bin_mode_e*)&val_get);
    } else if (strcmp(reg, "hist_bin_num") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        DSP2_Get_AWB3_Hist_Bin_Num(&val_get);
    } else if (strcmp(reg, "r_sum") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        val_get = awb3_sum.r_sum;
    } else if (strcmp(reg, "g_sum") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        val_get = awb3_sum.g_sum;
    } else if (strcmp(reg, "b_sum") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        val_get = awb3_sum.b_sum;
    } else if (strcmp(reg, "r_sum_hex") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        val_get = awb3_sum.r_sum_hex;
    } else if (strcmp(reg, "g_sum_hex") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        val_get = awb3_sum.g_sum_hex;
    } else if (strcmp(reg, "b_sum_hex") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        val_get = awb3_sum.b_sum_hex;
    } else if (strcmp(reg, "pixel_hex") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        val_get = awb3_sum.pixel_hex;
    } else if (strcmp(reg, "r_ratio_hex_y") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        val_get = awb3_sum.r_ratio_hex_y;
    } else if (strcmp(reg, "b_ratio_hex_y") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        val_get = awb3_sum.b_ratio_hex_y;
    } else if (strcmp(reg, "weight_hex_y") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        val_get = awb3_sum.weight_hex_y;
    } else if (strcmp(reg, "pixel_hex_y") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        val_get = awb3_sum.pixel_hex_y;
    } else if (strcmp(reg, "r_ratio_hist") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        val_get = awb3_sum.r_ratio_hist;
    } else if (strcmp(reg, "b_ratio_hist") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        val_get = awb3_sum.b_ratio_hist;
    } else if (strcmp(reg, "weight_hist") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        val_get = awb3_sum.weight_hist;
    } else if (strcmp(reg, "pixel_hist") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        val_get = awb3_sum.pixel_hist;
    } else if (strcmp(reg, "r_ratio_hist_clip") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        val_get = awb3_sum.r_ratio_hist_clip;
    } else if (strcmp(reg, "b_ratio_hist_clip") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        val_get = awb3_sum.b_ratio_hist_clip;
    } else if (strcmp(reg, "weight_hist_clip") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        val_get = awb3_sum.weight_hist_clip;
    } else if (strcmp(reg, "pixel_hist_clip") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        val_get = awb3_sum.pixel_hist_clip;
    } else {
        return -1;
    }

    if (type == DSP2_PARSE_WRITE) {
        return 0;
    }
    sprintf(ret_string, "[OK] HW AWB_%s: %ld", reg, val_get);

    return 0;
}

int DSP2_AWB3_rgb_Parse(int type, char* reg, int *value, char* ret_string)
{
    bl_dsp2_rgb_gain_t rgb_gain;

    if (strcmp(reg, "manual_rgb_gain") == 0) {
        if (type == DSP2_PARSE_WRITE) {
            rgb_gain.r_gain = value[0];
            rgb_gain.g_gain = value[1];
            rgb_gain.b_gain = value[2];
            awb_set_manual_rgb_gain(&rgb_gain);
        } else {
            awb_get_manual_rgb_gain(&rgb_gain);
        }
    } else if (strcmp(reg, "rgb_gain") == 0) {
        if (type == DSP2_PARSE_WRITE) {
            rgb_gain.r_gain = value[0];
            rgb_gain.g_gain = value[1];
            rgb_gain.b_gain = value[2];
            awb_set_gain(&rgb_gain);
        } else {
            awb_get_gain(&rgb_gain);
        }
    } else {
        return -1;
    }

    if (type == DSP2_PARSE_WRITE) return 0;

    sprintf(ret_string, "[OK] AWB_%s: ", reg);
    strCatVal(ret_string, rgb_gain.r_gain);
    strCatVal(ret_string, rgb_gain.g_gain);
    strCatVal(ret_string, rgb_gain.b_gain);

    return 0;
}

int DSP2_AWB3_FW_Preference_Tbl_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i = 0, idx = 0;
    awb_bais_t *auto_ptr;
    awb_bais_t auto_tbl = {0};

    char *token;
    token = strtok(reg, "awb_preference_tbl_");
    idx = atoi(token);
    if ((idx > MAX_ENTRY_NUM_AE_SYS_GAIN_AUTO - 1) || (idx < 0))  return -1;
    
    if (type == DSP2_PARSE_WRITE) {
         for (i = 0; i < 3; i++) {
            auto_tbl.bais[i].r_gain = value[i * 2];
            auto_tbl.bais[i].b_gain = value[i * 2 + 1];
        }
        img_param_sw_set_awb_preference_gain(idx, &auto_tbl);
        imgproc_set_fw_module_en(DSP2_ADJ_AWB, 1);
        return 0;
    }

    sprintf(ret_string, "[OK] awb preference gain %d: ", idx);
    img_param_sw_get_awb_preference_gain(idx, &auto_ptr);
    for (i = 0; i < 3; i++) {
        strCatVal(ret_string, auto_ptr->bais[i].r_gain);
        strCatVal(ret_string, auto_ptr->bais[i].b_gain);
    }

    return 0;

}

int DSP2_AWB3_FW_Special_Coloe_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i = 0, idx = 0;
    awb_special_color_t *auto_ptr;
    awb_special_color_t auto_tbl = {0};

    char *token;
    token = strtok(reg, "awb_special_color_");
    idx = atoi(token);

    if ((idx > MAX_ENTRY_NUM_AWB3_SPECIAL_COLOR - 1) || (idx < 0))  return -1;
    
    if (type == DSP2_PARSE_WRITE) {
        auto_tbl.r_gain = value[i];
        auto_tbl.b_gain = value[i + 1];
        auto_tbl.weight = value[i + 2];
        img_param_sw_set_awb_special_color(idx, &auto_tbl);
        awb_set_special_color_flag(1);
        imgproc_set_fw_module_en(DSP2_ADJ_AWB, 1);
        return 0;
    }

    sprintf(ret_string, "[OK] awb special color %d: ", idx);
    img_param_sw_get_awb_special_color(idx, &auto_ptr);
    strCatVal(ret_string, auto_ptr->r_gain);
    strCatVal(ret_string, auto_ptr->b_gain);
    strCatVal(ret_string, auto_ptr->weight);

    return 0;

}

int DSP2_BLC_Calib_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i = 0;
    blc_cal_t *cal_ptr;
    blc_cal_t cal_tbl[MAX_ENTRY_NUM_AE_ISO_AUTO] = {0};

    if (type == DSP2_PARSE_WRITE) {
        for (i = 0; i < MAX_ENTRY_NUM_AE_ISO_AUTO; i++) {
            cal_tbl[i].black_level = value[i];
        }
        img_param_calib_set_blc(cal_tbl);
        imgproc_set_fw_module_en(DSP2_ADJ_AE, 1);
        return 0;
    }

    sprintf(ret_string, "[OK] CALIB BLC_%s: ", reg);
    for (i = 0; i < MAX_ENTRY_NUM_AE_ISO_AUTO; i++) {
        img_param_calib_get_blc(i, &cal_ptr);
        strCatVal(ret_string, cal_ptr->black_level);
    }

    return 0;
}

int DSP2_BLC_FW_Auto_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i = 0;
    DSP2_BLC_PARAM *ptr;
    DSP2_BLC_PARAM tbl = {0};

    if (type == DSP2_PARSE_WRITE) {
        for (i = 0; i < MAX_ENTRY_NUM_AE_ISO_AUTO; i++) {
            img_param_sw_get_blc(i, &ptr);
            memcpy(&tbl, ptr, sizeof(DSP2_BLC_PARAM));
            if (strcmp(reg, "black_level") == 0) tbl.black_level = value[i];
            else return -1;
            img_param_sw_set_blc(i, &tbl);
        }
        imgproc_set_fw_module_en(DSP2_ADJ_AE, 1);
        return 0;
    }

    sprintf(ret_string, "[OK] auto BLC_%s: ", reg);
    for (i = 0; i < MAX_ENTRY_NUM_AE_ISO_AUTO; i++) {
        img_param_sw_get_blc(i, &ptr);
        if (strcmp(reg, "black_level") == 0) strCatVal(ret_string, ptr->black_level);
        else return -1;
    }

    return 0;
}

int DSP2_BLC_FW_Parse(int type, char* reg, int value, char* ret_string)
{
    int val_get = 0;
    DSP2_BLC_PARAM sw_config;
    blc_get_sw_config(&sw_config);

    if (strcmp(reg, "black_level") == 0) {
        if (type == DSP2_PARSE_WRITE) sw_config.black_level = value;
        val_get = sw_config.black_level;
    } else {
        return -1;
    }

    if (type == DSP2_PARSE_WRITE) {
        blc_control(&sw_config);
        blc_hw_update();
        return 0;
    }
    sprintf(ret_string, "[OK] FW BLC_%s: %d", reg, val_get);

    return 0;
}

int DSP2_BLC_HW_Parse(int type, char* reg, int value, char* ret_string)
{
    int val_get = 0;
    DSP2_CLAMP_S cfg = {0};
    DSP2_OB_S cfg_ob = {0};

    DSP2_Get_BLC(&cfg);
    DSP2_Get_OB_Avg(&cfg_ob);
    if (strcmp(reg, "clamp_r") == 0) {
        if (type == DSP2_PARSE_WRITE) {
            cfg.clamp_r = value;
            DSP2_Set_BLC(&cfg);
            return 0;
        }
        val_get = cfg.clamp_r;
    } else if (strcmp(reg, "clamp_gr") == 0) {
        if (type == DSP2_PARSE_WRITE) {
            cfg.clamp_gr = value;
            DSP2_Set_BLC(&cfg);
            return 0;
        }
        val_get = cfg.clamp_gr;
    } else if (strcmp(reg, "clamp_gb") == 0) {
        if (type == DSP2_PARSE_WRITE) {
            cfg.clamp_gb = value;
            DSP2_Set_BLC(&cfg);
            return 00;
        }
        val_get = cfg.clamp_gb;
    } else if (strcmp(reg, "clamp_b") == 0) {
        if (type == DSP2_PARSE_WRITE) {
            cfg.clamp_b = value;
            DSP2_Set_BLC(&cfg);
            return 0;
        }
        val_get = cfg.clamp_b;
    } else if (strcmp(reg, "ob_r") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        val_get = cfg_ob.ob_r;
    } else if (strcmp(reg, "ob_gr") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        val_get = cfg_ob.ob_gr;
    } else if (strcmp(reg, "ob_gb") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        val_get = cfg_ob.ob_gb;
    } else if (strcmp(reg, "ob_b") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        val_get = cfg_ob.ob_b;
    } else {
        return -1;
    }

    sprintf(ret_string, "[OK] HW BLC_%s: %d", reg, val_get);

    return 0;
}

int DSP2_DPC_Calib_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i = 0, reg_num = 2;
    dpc_cal_t *cal_ptr;
    dpc_cal_t cal_tbl[MAX_ENTRY_NUM_AE_ISO_AUTO] = {0};

    if (type == DSP2_PARSE_WRITE) {
        for (i = 0; i < MAX_ENTRY_NUM_AE_ISO_AUTO; i++) {
            cal_tbl[i].defect_thr_1 = value[i * reg_num + 0];
            cal_tbl[i].defect_thr_2 = value[i * reg_num + 1];
        }
        img_param_calib_set_dpc(cal_tbl);
        imgproc_set_fw_module_en(DSP2_ADJ_AE, 1);
        return 0;
    }

    sprintf(ret_string, "[OK] CALIB DPC: ");
    for (i = 0; i < MAX_ENTRY_NUM_AE_ISO_AUTO; i++) {
        img_param_calib_get_dpc(i, &cal_ptr);
        strCatVal(ret_string, cal_ptr->defect_thr_1);
        strCatVal(ret_string, cal_ptr->defect_thr_2);
    }

    return 0;
}

int DSP2_DPC_FW_Auto_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i = 0;
    DSP2_DPC_PARAM *ptr;
    DSP2_DPC_PARAM tbl = {0};

    if (type == DSP2_PARSE_WRITE) {
        for (i = 0; i < MAX_ENTRY_NUM_AE_ISO_AUTO; i++) {
            img_param_sw_get_dpc(i, &ptr);
            memcpy(&tbl, ptr, sizeof(DSP2_DPC_PARAM));
            if (strcmp(reg, "strength") == 0) tbl.strength = value[i];
            else return -1;
            img_param_sw_set_dpc(i, &tbl);
        }
        imgproc_set_fw_module_en(DSP2_ADJ_AE, 1);
        return 0;
    }

    sprintf(ret_string, "[OK] auto DPC_%s: ", reg);
    for (i = 0; i < MAX_ENTRY_NUM_AE_ISO_AUTO; i++) {
        img_param_sw_get_dpc(i, &ptr);
        if (strcmp(reg, "strength") == 0) strCatVal(ret_string, ptr->strength);
        else return -1;
    }

    return 0;
}

int DSP2_DPC_FW_Parse(int type, char* reg, int value, char* ret_string)
{
    int val_get = 0;
    DSP2_DPC_PARAM sw_config;
    dpc_get_sw_config(&sw_config);

    if (strcmp(reg, "strength") == 0) {
        if (type == DSP2_PARSE_WRITE) sw_config.strength = value;
        val_get = sw_config.strength;
    } else {
        return -1;
    }

    if (type == DSP2_PARSE_WRITE) {
        dpc_control(&sw_config);
        dpc_hw_update();
        return 0;
    }
    sprintf(ret_string, "[OK] FW DPC_%s: %d", reg, val_get);

    return 0;
}

int DSP2_DPC_HW_Parse(int type, char* reg, int value, char* ret_string)
{
    int val_get = 0;
    int pos_x = 0, pos_y = 0;
    DSP2_DPC_THRESHOLD_GROUP_TYPE thr_group = {0};
    DSP2_DPC_ENHANCE_GROUP_TYPE enh_group = {0};
        
    DSP2_Get_Defect_Correction_Threshold_Group(&thr_group);
    DSP2_Get_Defect_Correction_Enhance_Group(&enh_group);
    DSP2_Get_Defect_Postion(&pos_x, &pos_y);
    if (strcmp(reg, "defect_thr_1") == 0) {
        if (type == DSP2_PARSE_WRITE) thr_group.data[DSP2_DPC_th1] = value;
        val_get = thr_group.data[DSP2_DPC_th1];
    } else if (strcmp(reg, "defect_thr_2") == 0) {
        if (type == DSP2_PARSE_WRITE) thr_group.data[DSP2_DPC_th2] = value;
        val_get = thr_group.data[DSP2_DPC_th2];
    } else if (strcmp(reg, "defect_thr_3") == 0) {
        if (type == DSP2_PARSE_WRITE) thr_group.data[DSP2_DPC_th3] = value;
        val_get = thr_group.data[DSP2_DPC_th3];
    } else if (strcmp(reg, "defect_thr_4") == 0) {
        if (type == DSP2_PARSE_WRITE) thr_group.data[DSP2_DPC_th4] = value;
        val_get = thr_group.data[DSP2_DPC_th4];
    } else if (strcmp(reg, "defect_thr_5") == 0) {
        if (type == DSP2_PARSE_WRITE) thr_group.data[DSP2_DPC_th5] = value;
        val_get = thr_group.data[DSP2_DPC_th5];
    } else if (strcmp(reg, "resolution_enh_1") == 0) {
        if (type == DSP2_PARSE_WRITE) enh_group.data[DSP2_DPC_Enhance1] = value;
        val_get = enh_group.data[DSP2_DPC_Enhance1];
    } else if (strcmp(reg, "resolution_enh_2") == 0) {
        if (type == DSP2_PARSE_WRITE) enh_group.data[DSP2_DPC_Enhance2] = value;
        val_get = enh_group.data[DSP2_DPC_Enhance2];
    } else if (strcmp(reg, "resolution_enh_3") == 0) {
        if (type == DSP2_PARSE_WRITE) enh_group.data[DSP2_DPC_Enhance3] = value;
        val_get = enh_group.data[DSP2_DPC_Enhance3];
    } else if (strcmp(reg, "position_x") == 0) {
        if (type == DSP2_PARSE_WRITE) pos_x = value;
        val_get = pos_x;
    } else if (strcmp(reg, "position_y") == 0) {
        if (type == DSP2_PARSE_WRITE) pos_y = value;
        val_get = pos_y;
    } else {
        return -1;
    }

    if (type == DSP2_PARSE_WRITE) {
        if (strstr(reg, "thr") != NULL) DSP2_Set_Defect_Correction_Threshold_Group(&thr_group);
        if (strstr(reg, "enh") != NULL) DSP2_Set_Defect_Correction_Enhance_Group(&enh_group);
        if (strstr(reg, "position") != NULL) DSP2_Set_Defect_Postion(pos_x, pos_y);
        return 0;
    }
    sprintf(ret_string, "[OK] HW DPC_%s: %d", reg, val_get);

    return 0;
}

int DSP2_BNR_FW_Auto_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i = 0;
    DSP2_BNR_PARAM *ptr;
    DSP2_BNR_PARAM tbl = {0};

    if (type == DSP2_PARSE_WRITE) {
        for (i = 0; i < MAX_ENTRY_NUM_AE_ISO_AUTO; i++) {
            img_param_sw_get_bnr(i, &ptr);
            memcpy(&tbl, ptr, sizeof(DSP2_BNR_PARAM));
            if (strcmp(reg, "strength") == 0) tbl.strength = value[i];
            else return -1;
            img_param_sw_set_bnr(i, &tbl);
        }
        imgproc_set_fw_module_en(DSP2_ADJ_AE, 1);
        return 0;
    }

    sprintf(ret_string, "[OK] auto BNR_%s: ", reg);
    for (i = 0; i < MAX_ENTRY_NUM_AE_ISO_AUTO; i++) {
        img_param_sw_get_bnr(i, &ptr);
        if (strcmp(reg, "strength") == 0) strCatVal(ret_string, ptr->strength);
        else return -1;
    }

    return 0;
}

int DSP2_BNR_FW_Parse(int type, char* reg, int value, char* ret_string)
{
    int val_get = 0;
    DSP2_BNR_PARAM sw_config = {0};
    bnr_get_sw_config(&sw_config);

    if (strcmp(reg, "strength") == 0) {
        if (type == DSP2_PARSE_WRITE) sw_config.strength = value;
        val_get =  sw_config.strength;
    } else {
        return -1;
    }

    if (type == DSP2_PARSE_WRITE) {
        bnr_control(&sw_config);
        bnr_hw_update();
        return 0;
    }
    sprintf(ret_string, "[OK] FW BNR_%s: %d", reg, val_get);

    return 0;
}

int DSP2_BNR_HW_Parse(int type, char* reg, int value, char* ret_string)
{
    int val_get = 0;
    int bnr_weight;
    int lpf_weight;
    BL_Fun_Type state;
    DSP2_BNR_THRESHOLD_TYPE bnr_thr;
    DSP2_BNR_FALLBACK_TYPE  bnr_fb;

    if (strstr(reg, "fb") != NULL) {
        DSP2_Get_BNR_Fallback(&bnr_fb);
        if (strcmp(reg, "fb_lpf_weight") == 0) {
            if (type == DSP2_PARSE_WRITE) bnr_fb.fb_lpf_weight = value;
            val_get = bnr_fb.fb_lpf_weight;
        } else if (strcmp(reg, "fb_level") == 0) {
            if (type == DSP2_PARSE_WRITE) bnr_fb.fb_level = value;
            val_get =  bnr_fb.fb_level;
        } else {
            return -1;
        }

        if (type == DSP2_PARSE_WRITE) {
            DSP2_Set_BNR_Fallback(&bnr_fb);
            return 0;
        }
        sprintf(ret_string, "[OK] HW BNR_%s: %d", reg, val_get);
        return 0;
    }

    if ((strstr(reg, "th") != NULL) || (strstr(reg, "slope_gain") != NULL)) {
        DSP2_Get_BNR_Threshold(&bnr_thr);
        if (strcmp(reg, "th_base_r") == 0) {
            if (type == DSP2_PARSE_WRITE) bnr_thr.th_base_r = value;
            val_get = bnr_thr.th_base_r;
        } else if (strcmp(reg, "th_base_g") == 0) {
            if (type == DSP2_PARSE_WRITE) bnr_thr.th_base_g = value;
            val_get =  bnr_thr.th_base_g;
        } else if (strcmp(reg, "th_base_b") == 0) {
            if (type == DSP2_PARSE_WRITE) bnr_thr.th_base_b = value;
            val_get = bnr_thr.th_base_b;
        } else if (strcmp(reg, "th_slope_r") == 0) {
            if (type == DSP2_PARSE_WRITE) bnr_thr.th_slope_r = value;
            val_get = bnr_thr.th_slope_r;
        } else if (strcmp(reg, "th_slope_g") == 0) {
            if (type == DSP2_PARSE_WRITE) bnr_thr.th_slope_g = value;
            val_get = bnr_thr.th_slope_g;
        } else if (strcmp(reg, "th_slope_b") == 0) {
           if (type == DSP2_PARSE_WRITE) bnr_thr.th_slope_b = value;
           val_get =  bnr_thr.th_slope_b;
        } else if (strcmp(reg, "slope_gain") == 0) {
            if (type == DSP2_PARSE_WRITE) bnr_thr.slope_gain = value;
            val_get =  bnr_thr.slope_gain;
        } else {
            return -1;
        }

        if (type == DSP2_PARSE_WRITE) {
            DSP2_Set_BNR_Threshold(&bnr_thr);
            return 0;
        }
        sprintf(ret_string, "[OK] HW BNR_%s: %d", reg, val_get);
        return 0;
    }

    if (strcmp(reg, "bnr_en") == 0) {
        if (type == DSP2_PARSE_WRITE) DSP2_Set_BNR_State(value);
        DSP2_Get_BNR_State(&val_get);
    } else if (strcmp(reg, "bnr_weight") == 0) {
        if (type == DSP2_PARSE_WRITE) DSP2_Set_BNR_Weight(value);
        DSP2_Get_BNR_Weight(&val_get);
    } else if (strcmp(reg, "lpf_weight") == 0) {
        if (type == DSP2_PARSE_WRITE) DSP2_Set_BNR_LPF_Weight(value);
        DSP2_Get_BNR_LPF_Weight(&val_get);
    } else {
        return -1;
    }

    if (type == DSP2_PARSE_WRITE) {
        return 0;
    }
    sprintf(ret_string, "[OK] HW BNR_%s: %d", reg, val_get);

    return 0;
}

int DSP2_LSC_Calib_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i = 0, j = 0, reg_num = LSC_COEF_NUM * 3 + 3 + 1;
    int tbl_num = 2;//img_param_get_num_lsc();
    lsc_cal_t *cal_ptr;
    lsc_cal_t cal_tbl[2] = {0};

    if (type == DSP2_PARSE_WRITE) {
        for (i = 0; i < tbl_num; i++) {
            for (j = 0; j < LSC_COEF_NUM; j++) {
                cal_tbl[i].lsc_coef_r.coef[j] = value[i * reg_num + j];
                cal_tbl[i].lsc_coef_g.coef[j] = value[i * reg_num + LSC_COEF_NUM + j];
                cal_tbl[i].lsc_coef_b.coef[j] = value[i * reg_num + LSC_COEF_NUM * 2 + j];
            }
            cal_tbl[i].lsc_max.max_r = value[i * reg_num + LSC_COEF_NUM * 3 + 0];
            cal_tbl[i].lsc_max.max_g = value[i * reg_num + LSC_COEF_NUM * 3 + 1];
            cal_tbl[i].lsc_max.max_b = value[i * reg_num + LSC_COEF_NUM * 3 + 2];
            cal_tbl[i].color_temp    = value[i * reg_num + LSC_COEF_NUM * 3 + 3];
        }
        img_param_calib_set_lsc(cal_tbl, tbl_num);
        imgproc_set_fw_module_en(DSP2_ADJ_AWB, 1);
        return 0;
    }

    sprintf(ret_string, "[OK] CALIB LSC: ");
    for (i = 0; i < tbl_num; i++) {
        img_param_calib_get_lsc(i, &cal_ptr);
        for (j = 0; j < LSC_COEF_NUM; j++) {
            strCatVal(ret_string, cal_ptr->lsc_coef_r.coef[j]);
        }
        for (j = 0; j < LSC_COEF_NUM; j++) {
            strCatVal(ret_string, cal_ptr->lsc_coef_g.coef[j]);
        }
        for (j = 0; j < LSC_COEF_NUM; j++) {
            strCatVal(ret_string, cal_ptr->lsc_coef_b.coef[j]);
        }
        strCatVal(ret_string, cal_ptr->lsc_max.max_r);
        strCatVal(ret_string, cal_ptr->lsc_max.max_g);
        strCatVal(ret_string, cal_ptr->lsc_max.max_b);
        strCatVal(ret_string, cal_ptr->color_temp);
    }

    return 0;
}

int DSP2_LSC_FW_Auto_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i = 0;
    DSP2_LSC_PARAM *ptr;
    DSP2_LSC_PARAM tbl = {0};

    if (type == DSP2_PARSE_WRITE) {
        for (i = 0; i < MAX_ENTRY_NUM_AWB_CT_AUTO; i++) {
            img_param_sw_get_lsc(i, &ptr);
            memcpy(&tbl, ptr, sizeof(DSP2_LSC_PARAM));
            if (strcmp(reg, "strength") == 0) tbl.strength = value[i];
            else if (strcmp(reg, "color_temp") == 0) tbl.color_temp = value[i];
            else return -1;
            img_param_sw_set_lsc(i, &tbl);
        }
        imgproc_set_fw_module_en(DSP2_ADJ_AWB, 1);
        return 0;
    }

    sprintf(ret_string, "[OK] auto LSC_%s: ", reg);
    for (i = 0; i < MAX_ENTRY_NUM_AWB_CT_AUTO; i++) {
        img_param_sw_get_lsc(i, &ptr);
        if (strcmp(reg, "strength") == 0) strCatVal(ret_string, ptr->strength);
        else if (strcmp(reg, "color_temp") == 0) strCatVal(ret_string, ptr->color_temp);
        else return -1;
    }

    return 0;
}

int DSP2_LSC_FW_Parse(int type, char* reg, int value, char* ret_string)
{
    int val_get = 0;
    BL_COLOR_TEMP color_temp;
    DSP2_LSC_PARAM sw_config;
    lsc_get_sw_config(&sw_config);
    awb_get_color_temp(&color_temp);

    if (strcmp(reg, "strength") == 0) {
        if (type == DSP2_PARSE_WRITE) sw_config.strength = value;
        else val_get = sw_config.strength;
    } else if (strcmp(reg, "color_temp") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        else awb_get_color_temp(&val_get);
    } else {
        return -1;
    }

    if (type == DSP2_PARSE_WRITE) {
        lsc_control(color_temp, &sw_config);
        lsc_hw_update();
        return 0;
    }

    sprintf(ret_string, "[OK] FW LSC_%s: %d", reg, val_get);

    return 0;
}

int DSP2_LSC_HW_Parse(int type, char* reg, int value, char* ret_string)
{
    int val_get = 0;
    int offset_x = 0, offset_y = 0;
    DSP2_LSC_MAX_S lsc_max = {0};

    DSP2_Get_LSC_Max(&lsc_max);
    DSP2_Get_LSC_Offset(&offset_x, &offset_y);
    if (strcmp(reg, "lsc_max_r") == 0) {
        if (type == DSP2_PARSE_WRITE) lsc_max.max_r = value;
        else val_get = lsc_max.max_r;
    } else if (strcmp(reg, "lsc_max_g") == 0) {
        if (type == DSP2_PARSE_WRITE) lsc_max.max_g = value;
        else val_get = lsc_max.max_g;
    } else if (strcmp(reg, "lsc_max_b") == 0) {
        if (type == DSP2_PARSE_WRITE) lsc_max.max_b = value;
        else val_get = lsc_max.max_b;
    } else if (strcmp(reg, "offset_x") == 0) {
        if (type == DSP2_PARSE_WRITE) offset_x = value;
        else val_get = offset_x;
    } else if (strcmp(reg, "offset_y") == 0) {
        if (type == DSP2_PARSE_WRITE) offset_y = value;
        else val_get = offset_y;
    } else {
        return -1;
    }

    if (type == DSP2_PARSE_WRITE) {
        if (strstr(reg, "max") != NULL) DSP2_Set_LSC_Max(&lsc_max);
        if (strstr(reg, "offset") != NULL) DSP2_Set_LSC_Offset(offset_x, offset_y);
        return 0;
    }
    sprintf(ret_string, "[OK] HW LSC_%s: %d", reg, val_get);

    return 0;
}

int DSP2_LSC_Coef_HW_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i = 0, ret = 0;
    int type_idx = 0;
    int coef_idx = -1;
    char *str_type_idx[3] = {"r","g","b"};
    DSP2_LSC_COEF_TYPE cfg = {0};
    const char delim[2] = ",";
    char *str = reg;

    if (strstr(reg, "lsc_coef_r") != NULL) {
        type_idx = 0;
        if (strstr(reg, "lsc_coef_r_") != NULL) coef_idx = strtol((str += strlen("lsc_coef_r_")), NULL, 10);
    } else if (strstr(reg, "lsc_coef_g") != NULL) {
        type_idx = 1;
        if (strstr(reg, "lsc_coef_g_") != NULL) coef_idx = strtol((str += strlen("lsc_coef_g_")), NULL, 10);
    } else if (strstr(reg, "lsc_coef_b") != NULL) {
        type_idx = 2;
        if (strstr(reg, "lsc_coef_b_") != NULL) coef_idx = strtol((str += strlen("lsc_coef_b_")), NULL, 10);
    } else {
        return -1;
    }

    if (type == DSP2_PARSE_WRITE) {
        if (coef_idx != -1) {
            DSP2_Get_LSC_Coeff_Type(type_idx, &cfg);
            cfg.coef[coef_idx] = value;
        } else {
            for (i = 0; i < LSC_COEF_NUM; i++) {
                cfg.coef[i] = value[i];
            }
        }
        ret = DSP2_Set_LSC_Coeff_Type(type_idx, &cfg);
        return ret;
    }

    DSP2_Get_LSC_Coeff_Type(type_idx, &cfg);
    if (coef_idx != -1) {
        sprintf(ret_string, "[OK] HW LSC_COEF_%s_%d: ", str_type_idx[type_idx], coef_idx);
        strCatVal(ret_string, cfg.coef[coef_idx]);
    } else {
        sprintf(ret_string, "[OK] HW LSC_COEF_%s: ", str_type_idx[type_idx]);
        for (i = 0; i < LSC_COEF_NUM; i++) {
            strCatVal(ret_string, cfg.coef[i]);
        }
    }

    return 0;
}

int DSP2_DG_FW_Auto_Parse(int type, char* reg, int *value, char* ret_string)
{
#if 0
    int i = 0;
    dg_param_sw_t *ptr;
    dg_param_sw_t tbl = {0};

    if (type == DSP2_PARSE_WRITE) {
        for (i = 0; i < MAX_ENTRY_NUM_AE_SYS_GAIN_AUTO; i++) {
            img_param_sw_get_dg(i, &ptr);
            memcpy(&tbl, ptr, sizeof(dg_param_sw_t));
            if (strcmp(reg, "r_gain") == 0) tbl.r_gain = value[i];
            else if (strcmp(reg, "gr_gain") == 0) tbl.gr_gain = value[i];
            else if (strcmp(reg, "gb_gain") == 0) tbl.gb_gain = value[i];
            else if (strcmp(reg, "b_gain") == 0) tbl.b_gain = value[i];
            else return -1;
            img_param_sw_set_dg(i, &tbl);
        }
        return 0;
    }

    sprintf(ret_string, "[OK] auto DG_%s: ", reg);
    for (i = 0; i < MAX_ENTRY_NUM_AE_SYS_GAIN_AUTO; i++) {
        img_param_sw_get_dg(i, &ptr);
        if (strcmp(reg, "r_gain") == 0) strCatVal(ret_string, ptr->r_gain);
        else if (strcmp(reg, "gr_gain") == 0) strCatVal(ret_string, ptr->gr_gain);
        else if (strcmp(reg, "gb_gain") == 0) strCatVal(ret_string, ptr->gb_gain);
        else if (strcmp(reg, "b_gain") == 0) strCatVal(ret_string, ptr->b_gain);
        else return -1;
    }
#endif
    return 0;
}
#if 0
static int DSP2_DG_FW_Parse(int type, char* reg, int value, char* ret_string)
{
    int val_get = 0;
    dg_param_sw_t sw_config;
    dg_get_sw_config(&sw_config);

    if (strcmp(reg, "r_gain") == 0) {
        if (type == DSP2_PARSE_WRITE) sw_config.r_gain = value;
        val_get = sw_config.r_gain;
    } else if (strcmp(reg, "gr_gain") == 0) {
        if (type == DSP2_PARSE_WRITE) sw_config.gr_gain = value;
        val_get = sw_config.gr_gain;
    } else if (strcmp(reg, "gb_gain") == 0) {
        if (type == DSP2_PARSE_WRITE) sw_config.gb_gain = value;
        val_get = sw_config.gb_gain;
    } else if (strcmp(reg, "b_gain") == 0) {
        if (type == DSP2_PARSE_WRITE) sw_config.b_gain = value;
        val_get = sw_config.b_gain;
    } else {
        return -1;
    }

    if (type == DSP2_PARSE_WRITE) {
        dg_control(&sw_config);
        dg_hw_update();
        return 0;
    }
    sprintf(ret_string, "[OK] FW DG_%s: %d", reg, val_get);

    return 0;
}
#endif
int DSP2_DG_HW_Parse(int type, char* reg, int value, char* ret_string)
{
    int val_get = 0;
    int r_gain = 0;
    int gr_gain = 0;
    int gb_gain = 0;
    int b_gain = 0;
    DSP2_Get_Digital_Gain(&r_gain, &gr_gain, &gb_gain, &b_gain);

    if (strcmp(reg, "r_gain") == 0) {
        if (type == DSP2_PARSE_WRITE) r_gain = value;
        else val_get = r_gain;
    } else if (strcmp(reg, "gr_gain") == 0) {
        if (type == DSP2_PARSE_WRITE) gr_gain = value;
        else val_get = gr_gain;
    } else if (strcmp(reg, "gb_gain") == 0) {
        if (type == DSP2_PARSE_WRITE) gb_gain = value;
        else val_get = gb_gain;
    } else if (strcmp(reg, "b_gain") == 0) {
        if (type == DSP2_PARSE_WRITE) b_gain = value;
        else val_get = b_gain;
    } else {
        return -1;
    }

    if (type == DSP2_PARSE_WRITE) {
        DSP2_Set_Digital_Gain(r_gain, gr_gain, gb_gain, b_gain);
        return 0;
    }
    sprintf(ret_string, "[OK] HW DG_%s: %d", reg, val_get);

    return 0;
}

int DSP2_AF_HW_Parse(int type, char* reg, int value, char* ret_string)
{
    int val_get = 0;
    DSP2_AF_CONF_Type cfg = {0};
    DSP2_AF_WINDOW_Type winCfg = {0};
    dsp2_af_stats_conf_t stats = {0};
    
    DSP2_Get_AF_Stats(&stats);
    if (strstr(reg, "wa") != NULL) {
        DSP2_Get_AF_Window_A(&winCfg);
    } else if (strstr(reg, "wb") != NULL) {
        DSP2_Get_AF_Window_B(&winCfg);
    } else {
        DSP2_Get_AF_Stats_Conf(&cfg);
    }
    
    if (strstr(reg, "start_x") != NULL) {
        if (type == DSP2_PARSE_WRITE) winCfg.start_x = value;
        val_get = winCfg.start_x;
    } else if (strstr(reg, "start_y") != NULL) {
        if (type == DSP2_PARSE_WRITE) winCfg.start_y = value;
        val_get =  winCfg.start_y;
    } else if (strstr(reg, "end_x") != NULL) {
        if (type == DSP2_PARSE_WRITE) winCfg.end_x = value;
        val_get = winCfg.end_x;
    } else if (strstr(reg, "end_y") != NULL) {
        if (type == DSP2_PARSE_WRITE) winCfg.end_y = value;
        val_get =  winCfg.end_y;
    } else if (strstr(reg, "sum_shift") != NULL) {
        if (type == DSP2_PARSE_WRITE) winCfg.sum_shift = value;
        val_get = winCfg.sum_shift;
    } else if (strstr(reg, "gamma_pattern") != NULL) {
        if (type == DSP2_PARSE_WRITE) cfg.gamma_pattern = value;
        val_get = cfg.gamma_pattern;
    } else if (strstr(reg, "fcore1") != NULL) {
        if (type == DSP2_PARSE_WRITE) cfg.fcore1 = value;
        val_get = cfg.fcore1;
    } else if (strstr(reg, "fcore2") != NULL) {
        if (type == DSP2_PARSE_WRITE) cfg.fcore2 = value;
        val_get = cfg.fcore2;
    } else if (strcmp(reg, "wa_hpf1_sum") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        val_get = stats.wa_hpf1_sum;
    } else if (strcmp(reg, "wa_hpf2_sum") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        val_get =  stats.wa_hpf2_sum;
    } else if (strcmp(reg, "wb_hpf1_sum") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        val_get = stats.wb_hpf1_sum;
    } else if (strcmp(reg, "wb_hpf2_sum") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        val_get =  stats.wb_hpf2_sum;
    } else {
        return -1;
    }

    if (type == DSP2_PARSE_WRITE) {
        if (strstr(reg, "wa") != NULL) {
            DSP2_Set_AF_Window_A(&winCfg);
        } else if (strstr(reg, "wb") != NULL) {
            DSP2_Set_AF_Window_B(&winCfg);
        } else {
            DSP2_Set_AF_Stats_Conf(&cfg);
        }
        return 0;
    }
    sprintf(ret_string, "[OK] HW AF_%s: %d", reg, val_get);

    return 0;
}

int DSP2_CCM_Calib_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i = 0, j = 0, reg_num = CCM_COEF_NUM + 1;
    int tbl_num = 7;//img_param_get_num_color_corr();
    ccm_cal_t *cal_ptr;
    ccm_cal_t cal_tbl[7] = {0};

    if (type == DSP2_PARSE_WRITE) {
        for (i = 0; i < tbl_num; i++) {
            for (j = 0; j < CCM_COEF_NUM; j++) {
                cal_tbl[i].coef[j] = value[i * reg_num + j];
            }
            cal_tbl[i].color_temp = value[i * reg_num + CCM_COEF_NUM];
        }
        img_param_calib_set_ccm(cal_tbl, tbl_num);
        imgproc_set_fw_module_en(DSP2_ADJ_AWB, 1);
        return 0;
    }

    sprintf(ret_string, "[OK] CALIB CCM: ");
    for (i = 0; i < tbl_num; i++) {
        img_param_calib_get_ccm(i, &cal_ptr);
        for (j = 0; j < CCM_COEF_NUM; j++) {
            strCatVal(ret_string, cal_ptr->coef[j]);
        }
        strCatVal(ret_string, cal_ptr->color_temp);
    }

    return 0;
}

int DSP2_CCM_FW_Auto_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i = 0, idx = -1;
    DSP2_CCM_PARAM *ptr;
    DSP2_CCM_PARAM tbl = {0};
    ccm_cw_t *cw_ptr;
    ccm_cw_t cw_tbl = {0};

    char *token;
    if (strstr(reg, "coef_") != NULL) {
        token = strtok(reg, "coef_");
        if(token != NULL) idx = atoi(token);
        else return -1;
    }

    if (type == DSP2_PARSE_WRITE) {
        if (strstr(reg, "coef_") != NULL) {
            img_param_sw_get_ccm(idx, &ptr);
            memcpy(&tbl, ptr, sizeof(DSP2_CCM_PARAM));
            for (i = 0; i < CCM_COEF_NUM; i++) tbl.coef[i] = value[i];
            img_param_sw_set_ccm(idx, &tbl);
        } else if (strcmp(reg, "color_temp") == 0) {
            for (i = 0; i < MAX_ENTRY_NUM_AWB_CT_AUTO; i++) {
                img_param_sw_get_ccm(i, &ptr);
                memcpy(&tbl, ptr, sizeof(DSP2_CCM_PARAM));
                tbl.color_temp = value[i];
                img_param_sw_set_ccm(i, &tbl);
            }
        } else if (strstr(reg, "color_weight") != NULL) {
            for (i = 0; i < MAX_ENTRY_NUM_AE_ISO_AUTO; i++) {
                img_param_sw_get_ccm_color_weight(i, &cw_ptr);
                memcpy(&cw_tbl, cw_ptr, sizeof(ccm_cw_t));
                cw_tbl.color_weight = value[i];
                img_param_sw_set_ccm_color_weight(i, &cw_tbl);
            }
        } else return -1;
        imgproc_set_fw_module_en(DSP2_ADJ_AE, 1);
        imgproc_set_fw_module_en(DSP2_ADJ_AWB, 1);
        return 0;
    }

    sprintf(ret_string, "[OK] auto CCM_%s: ", reg);
    if (strstr(reg, "coef_") != NULL) {
        img_param_sw_get_ccm(idx, &ptr);
        for (i = 0; i < CCM_COEF_NUM; i++) strCatVal(ret_string, ptr->coef[i]);
    } else if (strcmp(reg, "color_temp") == 0) {
        for (i = 0; i < MAX_ENTRY_NUM_AWB_CT_AUTO; i++) {
            img_param_sw_get_ccm(i, &ptr);
            strCatVal(ret_string, ptr->color_temp);
        }
    } else if (strcmp(reg, "color_weight") == 0) {
        for (i = 0; i < MAX_ENTRY_NUM_AE_ISO_AUTO; i++) {
            img_param_sw_get_ccm_color_weight(i, &cw_ptr);
            strCatVal(ret_string, cw_ptr->color_weight);
        }
    } else return -1;

    return 0;
}

int DSP2_CCM_FW_Parse(int type, char* reg, int value, char* ret_string)
{
    int val_get = 0;
    ccm_cw_t sw_cw_config;
    ccm_get_sw_cw_config(&sw_cw_config);

    if (strcmp(reg, "color_temp") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        else awb_get_color_temp(&val_get);
    } else if (strcmp(reg, "cal_num") == 0) {
        if (type == DSP2_PARSE_WRITE) img_param_calib_set_ccm_num(value);
        else val_get = img_param_calib_get_ccm_num();
    } else if (strcmp(reg, "color_weight") == 0) {
        if (type == DSP2_PARSE_WRITE) {
            sw_cw_config.color_weight = value;
            ccm_set_sw_cw_config(&sw_cw_config);
        } else {
            val_get = sw_cw_config.color_weight;
        }
    } else {
        return -1;
    }

    sprintf(ret_string, "[OK] CCM_%s: %d", reg, val_get);

    return 0;
}

int DSP2_CCM_HW_Parse(int type, char* reg, int value, char* ret_string)
{
    int val_get = 0;
    char *str = reg;
    int idx = 0;
    DSP2_CCM_OFFSET_S pre_offset = {0};
    DSP2_CCM_OFFSET_S post_offset = {0};
    DSP2_CCM_COEF_S coef = {0};

    DSP2_Get_CCM_Coef(&coef);
    DSP2_Get_CCM_Pre_Offset(&pre_offset);
    DSP2_Get_CCM_Post_Offset(&post_offset);
    if (strstr(reg, "pre_offset_") != NULL) {
        idx = strtol((str += strlen("pre_offset_")), NULL, 10);
        if (type == DSP2_PARSE_WRITE) {
            if ((idx < 0) || (idx > CCM_OFFSET_NUM)) return -1;
            pre_offset.offset[idx] = value;
            DSP2_Set_CCM_Pre_Offset(&pre_offset);
        }
        val_get = pre_offset.offset[idx];
    } else if (strstr(reg, "post_offset_") != NULL) {
        idx = strtol((str += strlen("post_offset_")), NULL, 10);
        if (type == DSP2_PARSE_WRITE) {
            if ((idx < 0) || (idx > CCM_OFFSET_NUM)) return -1;
            post_offset.offset[idx] = value;
            DSP2_Set_CCM_Post_Offset(&post_offset);
        }
        val_get = post_offset.offset[idx];
    } else if (strstr(reg, "coef_") != NULL) {
        idx = strtol((str += (strlen("coef_"))), NULL, 10);
        if (type == DSP2_PARSE_WRITE) {
            if ((idx < 0) || (idx > CCM_COEF_NUM)) return -1;
            coef.ccm_coef[idx] = value;
            DSP2_Set_CCM_Coef(&coef);
        }
        val_get = coef.ccm_coef[idx];
    } else {
        return -1;
    }

    if (type == DSP2_PARSE_WRITE) {
        return 0;
    }
    sprintf(ret_string, "[OK] HW CCM_%s: %d", reg, val_get);

    return 0;
}

int DSP2_CCM_Coef_FW_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i = 0;
    DSP2_CCM_PARAM sw_config;
    ccm_cw_t sw_cw_config;
    ccm_get_sw_config(&sw_config);
    ccm_get_sw_cw_config(&sw_cw_config);

    if (type == DSP2_PARSE_WRITE) {
        for (i = 0; i < CCM_COEF_NUM; i++) {
            sw_config.coef[i] = value[i];
        }
        ccm_control(&sw_config, &sw_cw_config);
        ccm_hw_update();
        return 0;
    }

    sprintf(ret_string, "[OK] FW CCM: ");
    for (i = 0; i < CCM_COEF_NUM; i++) {
        strCatVal(ret_string, sw_config.coef[i]);
    }

    return 0;
}

int DSP2_CCM_Coef_HW_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i = 0;
    DSP2_CCM_COEF_S hw_config;

    if (type == DSP2_PARSE_WRITE) {
        for (i = 0; i < CCM_COEF_NUM; i++) {
            hw_config.ccm_coef[i] = value[i];
        }
        DSP2_Set_CCM_Coef(&hw_config);
        return 0;
    }
    DSP2_Get_CCM_Coef(&hw_config);

    sprintf(ret_string, "[OK] HW CCM: ");
    for (i = 0; i < CCM_COEF_NUM; i++) {
        strCatVal(ret_string, hw_config.ccm_coef[i]);
    }


    return 0;
}

int DSP2_Gamma_Calib_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i, idx;
    gamma_cal_t *ptr;
    gamma_cal_t tbl = {0};

    char *token;
    token = strtok(reg, "idx_");
    idx = atoi(token);

    if ((idx > MAX_ENTRY_NUM_GAMMA_IDX_AUTO - 1) || (idx < 0)) return -1;

    if (type == DSP2_PARSE_WRITE) {
        if (strstr(reg, "idx_") != NULL) {
            for (i = 0; i < GAMMA_COEF_NUM; i++) {
                tbl.gamma_curve.coef[i] = value[i];
            }
            tbl.idx = value[GAMMA_COEF_NUM];
            img_param_calib_set_gamma(idx, &tbl);
        }
        else return -1;
        imgproc_set_fw_module_en(DSP2_ADJ_AE, 1);
        return 0;
    }

    sprintf(ret_string, "[OK] cal GAMMA_%s: ", reg);
    img_param_calib_get_gamma(idx, &ptr);
    if (strstr(reg, "idx_") != NULL) {
        for (i = 0; i < GAMMA_COEF_NUM; i++) {
            strCatVal(ret_string, ptr->gamma_curve.coef[i]);
        }
        strCatVal(ret_string, ptr->idx);
    }
    else return -1;

    return 0;
}

int DSP2_Gamma_FW_Auto_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i = 0;
    DSP2_GAMMA_PARAM *ptr;
    DSP2_GAMMA_PARAM tbl = {0};

    if (type == DSP2_PARSE_WRITE) {
        for (i = 0; i < MAX_ENTRY_NUM_AE_SYS_GAIN_AUTO; i++) {
            img_param_sw_get_gamma(i, &ptr);
            memcpy(&tbl, ptr, sizeof(DSP2_GAMMA_PARAM));
            if (strcmp(reg, "idx") == 0) tbl.idx = value[i];
            else return -1;
            img_param_sw_set_gamma(i, &tbl);
        }
        imgproc_set_fw_module_en(DSP2_ADJ_AE, 1);
        return 0;
    }

    sprintf(ret_string, "[OK] auto GAMMA_%s: ", reg);
    for (i = 0; i < MAX_ENTRY_NUM_AE_SYS_GAIN_AUTO; i++) {
        img_param_sw_get_gamma(i, &ptr);
        if (strcmp(reg, "idx") == 0) strCatVal(ret_string, ptr->idx);
        else return -1;
    }

    return 0;
}

int DSP2_Gamma_FW_Parse(int type, char* reg, int value, char* ret_string)
{
    int val_get = 0;
    DSP2_GAMMA_PARAM sw_config;
    gamma_get_sw_config(&sw_config);

    if (strcmp(reg, "idx") == 0) {
        if (type == DSP2_PARSE_WRITE) sw_config.idx = value;
        else val_get = sw_config.idx;
    }
    else {
        return -1;
    }

    if (type == DSP2_PARSE_WRITE) {
        gamma_set_sw_config(&sw_config);
        gamma_control(&sw_config);
        gamma_hw_update();
        return 0;
    }
    sprintf(ret_string, "[OK] FW GAMMA_%s: %d", reg, val_get);

    return 0;
}

int DSP2_Gamma_Curve_HW_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i = 0;

    if (type == DSP2_PARSE_WRITE) {
        for (i = 0; i < GAMMA_COEF_NUM; i++) {
            gammaCfg.curve_coef[i] = value[i];
        }
        DSP2_Set_Gamma_Coef(&gammaCfg);
        return 0;
    }

    DSP2_Get_Gamma_Coef(&gammaCfg);
    sprintf(ret_string, "[OK] HW GAMMA_%s: ", reg);
    for (i = 0; i < GAMMA_COEF_NUM; i++) {
        strCatVal(ret_string, gammaCfg.curve_coef[i]);
    }

    return 0;
}

int DSP2_WDR_FW_Auto_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i, idx = 0;
    char *token;
    DSP2_WDR_PARAM *ptr;
    DSP2_WDR_PARAM tbl = {0};
    wdr_lowlight_weight_t *lowlight_weight_ptr = {0};
    wdr_lowlight_weight_t lowlight_weight = {0};
    wdr_tone_curve_conf_t *tone_curve_ptr = {0};
    wdr_tone_curve_conf_t tone_curve = {0};

    if (strstr(reg, "tone_curve_idx_") != NULL) {
        token = strtok(reg, "tone_curve_idx_");
        idx = atoi(token);
    }

    if (type == DSP2_PARSE_WRITE) {
        for (i = 0; i < MAX_ENTRY_NUM_AE_SYS_GAIN_AUTO; i++) {
            if (strstr(reg, "lowlight_weight_idx_") != NULL){
                img_param_sw_get_wdr_lowlight_weight(i, &lowlight_weight_ptr);
                memcpy(&lowlight_weight, lowlight_weight_ptr, sizeof(DSP2_AE_SUB_ATTR));
                if (strcmp(reg, "lowlight_weight_idx_0") == 0) lowlight_weight.idx[0] = value[i];
                else if (strcmp(reg, "lowlight_weight_idx_1") == 0) lowlight_weight.idx[1] = value[i];
                else if (strcmp(reg, "lowlight_weight_idx_2") == 0) lowlight_weight.idx[2] = value[i];
                else return -1;
                img_param_sw_set_wdr_lowlight_weight(i, &lowlight_weight);
            } else if (strstr(reg, "tone_curve_idx_") != NULL) {
                for (i = 0; i < WDR_COEF_NUM; i++) {
                    tone_curve.tone_curve.coef[i] = value[i];
                }
                tone_curve.idx = value[WDR_COEF_NUM];
                img_param_sw_set_wdr_tone_curve_conf(idx, &tone_curve);
            } else {
                img_param_sw_get_wdr(i, &ptr);
                memcpy(&tbl, ptr, sizeof(DSP2_WDR_PARAM));
                if (strcmp(reg, "cs_strength") == 0) tbl.cs_strength = value[i];
                else if (strcmp(reg, "curve_weight") == 0) tbl.curve_weight = value[i];
                else if (strcmp(reg, "enh_weight") == 0) tbl.enh_weight = value[i];
                else if (strcmp(reg, "bright_enh_level") == 0) tbl.bright_enh_level = value[i];
                else if (strcmp(reg, "dark_enh_level") == 0) tbl.dark_enh_level = value[i];
                else return -1;
                img_param_sw_set_wdr(i, &tbl);
            }
        }
        imgproc_set_fw_module_en(DSP2_ADJ_AE, 1);
        return 0;
    }

    sprintf(ret_string, "[OK] auto WDR_%s: ", reg);
    for (i = 0; i < MAX_ENTRY_NUM_AE_SYS_GAIN_AUTO; i++) {
        if (strstr(reg, "lowlight_weight_idx_") != NULL) {
            img_param_sw_get_wdr_lowlight_weight(i, &lowlight_weight_ptr);
            if (strcmp(reg, "lowlight_weight_idx_0") == 0) strCatVal(ret_string, lowlight_weight_ptr->idx[0]);
            else if (strcmp(reg, "lowlight_weight_idx_1") == 0) strCatVal(ret_string, lowlight_weight_ptr->idx[1]);
            else if (strcmp(reg, "lowlight_weight_idx_2") == 0) strCatVal(ret_string, lowlight_weight_ptr->idx[2]);
            else return -1;
        } else if (strstr(reg, "tone_curve_idx_") != NULL) {
            img_param_sw_get_wdr_tone_curve_conf(idx, &tone_curve_ptr);
            for (i = 0; i < WDR_COEF_NUM; i++) {
                strCatVal(ret_string, tone_curve_ptr->tone_curve.coef[i]);
            }
            strCatVal(ret_string, tone_curve_ptr->idx);
        } else {
            img_param_sw_get_wdr(i, &ptr);
            if (strcmp(reg, "cs_strength") == 0) strCatVal(ret_string, ptr->cs_strength);
            else if (strcmp(reg, "curve_weight") == 0) strCatVal(ret_string, ptr->curve_weight);
            else if (strcmp(reg, "enh_weight") == 0) strCatVal(ret_string, ptr->enh_weight);
            else if (strcmp(reg, "bright_enh_level") == 0) strCatVal(ret_string, ptr->bright_enh_level);
            else if (strcmp(reg, "dark_enh_level") == 0) strCatVal(ret_string, ptr->dark_enh_level);
            else return -1;
        }
    }

    return 0;
}

int DSP2_WDR_FW_Parse(int type, char* reg, int value, char* ret_string)
{
    int val_get = 0;
    DSP2_WDR_PARAM sw_config;
    wdr_lowlight_weight_conf_t *lowlight_weight_cfg = {0};
    wdr_get_sw_config(&sw_config);

    if (strstr(reg, "lowlight_weight_") != NULL) {
        img_param_sw_get_wdr_lowlight_weight_conf(&lowlight_weight_cfg);
        if (type == DSP2_PARSE_WRITE) {
            if (strcmp(reg, "lowlight_weight_thr_0") == 0) lowlight_weight_cfg->thr[0] = value;
            else if (strcmp(reg, "lowlight_weight_thr_1") == 0) lowlight_weight_cfg->thr[1] = value;
            else if (strcmp(reg, "lowlight_weight_thr_2") == 0) lowlight_weight_cfg->thr[2] = value;
            else if (strcmp(reg, "lowlight_weight_thr_3") == 0) lowlight_weight_cfg->thr[3] = value;
            else if (strcmp(reg, "lowlight_weight_roi_start") == 0) lowlight_weight_cfg->roi_start = value;
            else if (strcmp(reg, "lowlight_weight_roi_end") == 0) lowlight_weight_cfg->roi_end = value;
            else return -1;
            img_param_sw_set_wdr_lowlight_weight_conf(lowlight_weight_cfg);
            imgproc_set_fw_module_en(DSP2_ADJ_AE, 1);
            return 0;
        }
        if (strcmp(reg, "lowlight_weight_thr_0") == 0) val_get = lowlight_weight_cfg->thr[0];
        else if (strcmp(reg, "lowlight_weight_thr_1") == 0) val_get = lowlight_weight_cfg->thr[1];
        else if (strcmp(reg, "lowlight_weight_thr_2") == 0) val_get = lowlight_weight_cfg->thr[2];
        else if (strcmp(reg, "lowlight_weight_thr_3") == 0) val_get = lowlight_weight_cfg->thr[3];
        else if (strcmp(reg, "lowlight_weight_roi_start") == 0) val_get = lowlight_weight_cfg->roi_start;
        else if (strcmp(reg, "lowlight_weight_roi_end") == 0) val_get = lowlight_weight_cfg->roi_end;
        else return -1;
    } else if (strcmp(reg, "tone_curve_en") == 0) {
        if (type == DSP2_PARSE_WRITE) {
            img_param_sw_set_wdr_tone_curve_en(value);
            imgproc_set_fw_module_en(DSP2_ADJ_AE, 1);
            return 0;
        }
        img_param_sw_get_wdr_tone_curve_en(&val_get);
    } else if (strcmp(reg, "cs_strength") == 0) {
        if (type == DSP2_PARSE_WRITE) sw_config.cs_strength = value;
        val_get = sw_config.cs_strength;
    } else if (strcmp(reg, "enh_weight") == 0) {
        if (type == DSP2_PARSE_WRITE) sw_config.enh_weight = value;
        val_get = sw_config.enh_weight;
    } else if (strcmp(reg, "curve_weight") == 0) {
        if (type == DSP2_PARSE_WRITE) sw_config.curve_weight = value;
        val_get = sw_config.curve_weight;
    } else if (strcmp(reg, "bright_enh_level") == 0) {
        if (type == DSP2_PARSE_WRITE) sw_config.bright_enh_level = value;
        val_get = sw_config.bright_enh_level;
    } else if (strcmp(reg, "dark_enh_level") == 0) {
        if (type == DSP2_PARSE_WRITE) sw_config.dark_enh_level = value;
        val_get = sw_config.dark_enh_level;
    } else {
        return -1;
    }

    if (type == DSP2_PARSE_WRITE) {
        wdr_control(&sw_config);
        wdr_hw_update();
        return 0;
    }
    sprintf(ret_string, "[OK] FW WDR_%s: %d", reg, val_get);

    return 0;
}

int DSP2_WDR_HW_Parse(int type, char* reg, int value, char* ret_string)
{
    int val_get = 0;
    DSP2_Chroma_Suppress_Type chromaSupprCfg = {0};

    if ((strstr(reg, "cs") != NULL) && (strstr(reg, "cs_en") == NULL)) {
        DSP2_WDR_Get_CS_Config(&chromaSupprCfg);
        if (strcmp(reg, "cs_weight") == 0) {
            if (type == DSP2_PARSE_WRITE) chromaSupprCfg.weight = value;
            val_get = chromaSupprCfg.weight;
        } else if (strcmp(reg, "cs_grey_thr") == 0) {
            if (type == DSP2_PARSE_WRITE) chromaSupprCfg.grey_thr = value;
            val_get =  chromaSupprCfg.grey_thr;
        } else if (strcmp(reg, "cs_gain") == 0) {
            if (type == DSP2_PARSE_WRITE) chromaSupprCfg.gain = value;
            val_get =  chromaSupprCfg.gain;
        } else {
            return -1;
        }

        if (type == DSP2_PARSE_WRITE) {
            DSP2_WDR_Set_CS_Config(&chromaSupprCfg);
            return 0;
        }
        sprintf(ret_string, "[OK] HW WDR_%s: %d", reg, val_get);
        return 0;
    }

    if (strcmp(reg, "enh_en") == 0) {
        if (type == DSP2_PARSE_WRITE) DSP2_WDR_Set_Post_Enhance_State(value);
        DSP2_WDR_Get_Post_Enhance_State((BL_Fun_Type*)&val_get);
    } else if (strcmp(reg, "enh_weight") == 0) {
        if (type == DSP2_PARSE_WRITE) DSP2_WDR_Set_Post_Enhance_Weight(value);
        DSP2_WDR_Get_Post_Enhance_Weight(&val_get);
    } else if (strcmp(reg, "enh_y_offset") == 0) {
        if (type == DSP2_PARSE_WRITE) DSP2_WDR_Set_Post_Enhance_Y_Offset(value);
        DSP2_WDR_Get_Post_Enhance_Y_Offset(&val_get);
    } else if (strcmp(reg, "enh_y_gain") == 0) {
        if (type == DSP2_PARSE_WRITE) DSP2_WDR_Set_Post_Enhance_Luma_Gain(value);
        DSP2_WDR_Get_Post_Enhance_Luma_Gain(&val_get);
    } else if (strcmp(reg, "enh_c_gain_extra_slope") == 0) {
        if (type == DSP2_PARSE_WRITE) DSP2_WDR_Set_Post_Enhance_Chroma_Gain(value);
        DSP2_WDR_Get_Post_Enhance_Chroma_Gain(&val_get);
    } else if (strcmp(reg, "curve_en") == 0) {
        if (type == DSP2_PARSE_WRITE) DSP2_WDR_Set_WDR_Curve_State(value);
        DSP2_WDR_Get_WDR_Curve_State((BL_Fun_Type*)&val_get);
    } else if (strcmp(reg, "curve_weight") == 0) {
        if (type == DSP2_PARSE_WRITE) DSP2_WDR_Set_WDR_Curve_Weight(value);
        DSP2_WDR_Get_WDR_Curve_Weight(&val_get);
    } else if (strcmp(reg, "cs_en") == 0) {
        if (type == DSP2_PARSE_WRITE) DSP2_WDR_Set_CS_State(value);
        DSP2_WDR_Get_CS_State((BL_Fun_Type*)&val_get);
    } else {
        return -1;
    }

    if (type == DSP2_PARSE_WRITE) {
        return 0;
    }
    sprintf(ret_string, "[OK] HW WDR_%s: %d", reg, val_get);

    return 0;
}

int DSP2_WDR_FW_Curve_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i = 0;
    DSP2_WDR_Curve_Type Cfg;

    if (type == DSP2_PARSE_WRITE) {
        for (i = 0; i < DSP2_WDR_CURVE_COEF_NUM; i++) {
            Cfg.curve_coef[i] = value[i];
        }
        DSP2_WDR_Set_WDR_Curve(&Cfg);
        return 0;
    }
    DSP2_WDR_Get_WDR_Curve(&Cfg);

    sprintf(ret_string, "[OK] WDR_CURVE: ");
    for (i = 0; i < DSP2_WDR_CURVE_COEF_NUM; i++) {
        strCatVal(ret_string, Cfg.curve_coef[i]);
    }

    return 0;
}

int DSP2_WDR_Stats_Hist_Roi_Parse(int type, char* reg, int *value, char* ret_string)
{
    char *str = reg;
    int i = 0, idx = -1;
    int state = 0, weight = 0, left_x = 0, right_x = 0, top_y = 0, bottom_y = 0;
    
    if (strstr(reg, "hist_roi_") != NULL) {
        idx = strtol((str += strlen("hist_roi_")), NULL, 10);
        if (type == DSP2_PARSE_WRITE) {
            state   = value[0];
            weight  = value[1];
            left_x  = value[2];
            right_x = value[3];
            top_y   = value[4];
            bottom_y = value[5];
            DSP2_WDR_Set_ROI_State(idx, state);
            DSP2_WDR_Set_ROI_Weight(idx, weight);
            DSP2_WDR_Set_ROI_Position(idx, left_x, right_x, top_y, bottom_y);
            return 0;
        }
    } else if (strcmp(reg, "hist_roi") == 0) {
        idx = DSP2_WDR_HIST_ROI_NUM;
    } else {
        return -1;
    }

    sprintf(ret_string, "[OK] WDR_%s: ", reg);
    if (idx == DSP2_WDR_HIST_ROI_NUM) {
        for (i = 0; i < DSP2_WDR_HIST_ROI_NUM; i++) {
            DSP2_WDR_Get_ROI_State(i, &state);
            DSP2_WDR_Get_ROI_Weight(i, &weight);
            DSP2_WDR_Get_ROI_Position(i, &left_x, &right_x, &top_y, &bottom_y);
            strCatVal(ret_string, i);
            strCatVal(ret_string, state);
            strCatVal(ret_string, weight);
            strCatVal(ret_string, left_x);
            strCatVal(ret_string, right_x);
            strCatVal(ret_string, top_y);
            strCatVal(ret_string, bottom_y);
        }
    } else {
        DSP2_WDR_Get_ROI_State(idx, &state);
        DSP2_WDR_Get_ROI_Weight(idx, &weight);
        DSP2_WDR_Get_ROI_Position(idx, &left_x, &right_x, &top_y, &bottom_y);
        strCatVal(ret_string, idx);
        strCatVal(ret_string, state);
        strCatVal(ret_string, weight);
        strCatVal(ret_string, left_x);
        strCatVal(ret_string, right_x);
        strCatVal(ret_string, top_y);
        strCatVal(ret_string, bottom_y);
    }

    return 0;
}

int DSP2_WDR_Stats_Hist_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i = 0;
    DSP2_WDR_Hist_Data_Type hist;

    if (type == DSP2_PARSE_WRITE) {
        aos_cli_printf("[NG] %s is ready only\r\n", reg);
        return -1;
    }

    DSP2_WDR_Get_Hist_Data(&hist);

    sprintf(ret_string, "[OK] WDR_Hist: ");
    for (i = 0; i < DSP2_WDR_HIST_BIN_NUM; i++) {
        strCatVal(ret_string, hist.hist_bin[i]);
    }


    return 0;
}

int DSP2_SAT_FW_Auto_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i = 0;
    DSP2_SAT_PARAM *ptr;
    DSP2_SAT_PARAM tbl = {0};

    if (type == DSP2_PARSE_WRITE) {
        for (i = 0; i < MAX_ENTRY_NUM_AE_ISO_AUTO; i++) {
            img_param_sw_get_sat(i, &ptr);
            memcpy(&tbl, ptr, sizeof(DSP2_SAT_PARAM));
            if (strcmp(reg, "value") == 0) tbl.value = value[i];
            else return -1;
            img_param_sw_set_sat(i, &tbl);
        }
        imgproc_set_fw_module_en(DSP2_ADJ_AE, 1);
        return 0;
    }

    sprintf(ret_string, "[OK] auto SAT_%s: ", reg);
    for (i = 0; i < MAX_ENTRY_NUM_AE_ISO_AUTO; i++) {
        img_param_sw_get_sat(i, &ptr);
        if (strcmp(reg, "value") == 0) strCatVal(ret_string, ptr->value);
        else return -1;
    }

    return 0;
}

int DSP2_SAT_FW_Parse(int type, char* reg, int value, char* ret_string)
{
    int val_get = 0;
    DSP2_SAT_PARAM sw_config;

    sat_get_sw_config(&sw_config);
    if (strcmp(reg, "value") == 0) {
        if (type == DSP2_PARSE_WRITE) sw_config.value = value;
        val_get = sw_config.value;
    } else {
        return -1;
    }

    if (type == DSP2_PARSE_WRITE) {
        sat_control(&sw_config);
        sat_hw_update();
        return 0;
    }
    sprintf(ret_string, "[OK] FW SAT_%s: %d", reg, val_get);

    return 0;
}

int DSP2_SAT_HW_Parse(int type, char* reg, int value, char* ret_string)
{
    int val_get = 0;
    DSP2_SATURATION_S saturation;

    DSP2_Get_Saturation(&saturation);
    if (strcmp(reg, "saturation_cb") == 0) {
        if (type == DSP2_PARSE_WRITE) {
            saturation.saturation_cb = value;
        }
        val_get = saturation.saturation_cb;
    } else if (strcmp(reg, "saturation_cr") == 0) {
        if (type == DSP2_PARSE_WRITE) {
            saturation.saturation_cr = value;
        }
        val_get = saturation.saturation_cr;
    } else {
        return -1;
    }

    if (type == DSP2_PARSE_WRITE) {
        DSP2_Set_Saturation(&saturation);
        return 0;
    }
    sprintf(ret_string, "[OK] HW SAT_%s: %d", reg, val_get);

    return 0;
}

int DSP2_NR_FW_Auto_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i = 0;
    DSP2_NR_PARAM *ptr;
    DSP2_NR_PARAM tbl = {0};

    if (type == DSP2_PARSE_WRITE) {
        for (i = 0; i < MAX_ENTRY_NUM_AE_ISO_AUTO; i++) {
            img_param_sw_get_nr(i, &ptr);
            memcpy(&tbl, ptr, sizeof(DSP2_NR_PARAM));
            if (strcmp(reg, "strength_level") == 0) tbl.strength_level = value[i];
            else if (strcmp(reg, "strength_2d") == 0) tbl.strength_2d = value[i];
            else if (strcmp(reg, "strength_3d") == 0) tbl.strength_3d = value[i];
            else return -1;
            img_param_sw_set_nr(i, &tbl);
        }
        imgproc_set_fw_module_en(DSP2_ADJ_AE, 1);
        return 0;
    }

    sprintf(ret_string, "[OK] auto NR_%s: ", reg);
    for (i = 0; i < MAX_ENTRY_NUM_AE_ISO_AUTO; i++) {
        img_param_sw_get_nr(i, &ptr);
        if (strcmp(reg, "strength_level") == 0) strCatVal(ret_string, ptr->strength_level);
        else if (strcmp(reg, "strength_2d") == 0) strCatVal(ret_string, ptr->strength_2d);
        else if (strcmp(reg, "strength_3d") == 0) strCatVal(ret_string, ptr->strength_3d);
        else return -1;
    }

    return 0;
}

int DSP2_NR_FW_Parse(int type, char* reg, int value, char* ret_string)
{
    int val_get = 0;
    DSP2_NR_PARAM sw_config;
    nr_get_sw_config(&sw_config);

    if (strcmp(reg, "strength_level") == 0) {
        if (type == DSP2_PARSE_WRITE) {
            sw_config.strength_level = value;
        }
        val_get = sw_config.strength_level;
    } else if (strcmp(reg, "strength_2d") == 0) {
        if (type == DSP2_PARSE_WRITE) {
            sw_config.strength_2d = value;
        }
        val_get = sw_config.strength_2d;
    } else if (strcmp(reg, "strength_3d") == 0) {
        if (type == DSP2_PARSE_WRITE) {
            sw_config.strength_3d = value;
        }
        val_get = sw_config.strength_3d;
    } else {
        return -1;
    }

    if (type == DSP2_PARSE_WRITE) {
        nr_control(&sw_config);
        nr_hw_update();
        return 0;
    }
    sprintf(ret_string, "[OK] FW NR_%s: %d", reg, val_get);


    return 0;
}

int DSP2_NR_HW_Parse(int type, char* reg, int value, char* ret_string)
{
    int val_get = 0;

    if (strcmp(reg, "noise_level") == 0) {
        if (type == DSP2_PARSE_WRITE) DSP2_Set_Noise_Level(value);
        DSP2_Get_Noise_Level(&val_get);
    } else if (strcmp(reg, "filt_str_2d") == 0) {
        if (type == DSP2_PARSE_WRITE) DSP2_Set_2D_NR(value);
        DSP2_Get_2D_NR(&val_get);
    } else if (strcmp(reg, "filt_str_3d") == 0) {
        if (type == DSP2_PARSE_WRITE) DSP2_Set_3D_NR(value);
        DSP2_Get_3D_NR(&val_get);
    } else if (strcmp(reg, "hsize") == 0) {
        if (type == DSP2_PARSE_WRITE) DSP2_Set_NR_HSize(value);
        DSP2_Get_NR_HSize(&val_get);
    } else {
        return -1;
    }

    if (type == DSP2_PARSE_WRITE) {
        //it's soft enable so hw-reg will be set by fw-register.
        return 0;
    }
    sprintf(ret_string, "[OK] HW NR_%s: %d", reg, val_get);


    return 0;
}

int DSP2_EE_FW_Auto_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i = 0;
    DSP2_EE_PARAM *ptr;
    DSP2_EE_PARAM tbl = {0};

    if (type == DSP2_PARSE_WRITE) {
        for (i = 0; i < MAX_ENTRY_NUM_AE_ISO_AUTO; i++) {
            img_param_sw_get_ee(i, &ptr);
            memcpy(&tbl, ptr, sizeof(DSP2_EE_PARAM));
            if (strcmp(reg, "pos_edge_strength") == 0) tbl.pos_edge_strength = value[i];
            else if (strcmp(reg, "neg_edge_strength") == 0) tbl.neg_edge_strength = value[i];
            else if (strcmp(reg, "pos_edge_ovrsht_strength") == 0) tbl.pos_edge_ovrsht_strength = value[i];
            else if (strcmp(reg, "neg_edge_ovrsht_strength") == 0) tbl.neg_edge_ovrsht_strength = value[i];
            else if (strcmp(reg, "nr_strength") == 0) tbl.nr_strength = value[i];
            else if (strcmp(reg, "dir_shpness_thr") == 0) tbl.dir_shpness_thr = value[i];
            else if (strcmp(reg, "no_dir_shpness_thr") == 0) tbl.no_dir_shpness_thr = value[i];
            else if (strcmp(reg, "flat_thr") == 0) tbl.flat_thr = value[i];
            else if (strcmp(reg, "texture_thr") == 0) tbl.texture_thr = value[i];
            else if (strcmp(reg, "edge_thr") == 0) tbl.edge_thr = value[i];
            else return -1;
            img_param_sw_set_ee(i, &tbl);
        }
        imgproc_set_fw_module_en(DSP2_ADJ_AE, 1);
        return 0;
    }

    sprintf(ret_string, "[OK] auto EE_%s: ", reg);
    for (i = 0; i < MAX_ENTRY_NUM_AE_ISO_AUTO; i++) {
        img_param_sw_get_ee(i, &ptr);
        if (strcmp(reg, "pos_edge_strength") == 0) strCatVal(ret_string, ptr->pos_edge_strength);
        else if (strcmp(reg, "neg_edge_strength") == 0) strCatVal(ret_string, ptr->neg_edge_strength);
        else if (strcmp(reg, "pos_edge_ovrsht_strength") == 0) strCatVal(ret_string, ptr->pos_edge_ovrsht_strength);
        else if (strcmp(reg, "neg_edge_ovrsht_strength") == 0) strCatVal(ret_string, ptr->neg_edge_ovrsht_strength);
        else if (strcmp(reg, "nr_strength") == 0) strCatVal(ret_string, ptr->nr_strength);
        else if (strcmp(reg, "dir_shpness_thr") == 0) strCatVal(ret_string, ptr->dir_shpness_thr);
        else if (strcmp(reg, "no_dir_shpness_thr") == 0) strCatVal(ret_string, ptr->no_dir_shpness_thr);
        else if (strcmp(reg, "flat_thr") == 0) strCatVal(ret_string, ptr->flat_thr);
        else if (strcmp(reg, "texture_thr") == 0) strCatVal(ret_string, ptr->texture_thr);
        else if (strcmp(reg, "edge_thr") == 0) strCatVal(ret_string, ptr->edge_thr);
        else return -1;
    }

    return 0;
}

int DSP2_EE_FW_Parse(int type, char* reg, int value, char* ret_string)
{
    int val_get = 0;
    DSP2_EE_PARAM sw_config;
    ee_get_sw_config(&sw_config);

    if (strcmp(reg, "ovrsht_en") == 0) {
        if (type == DSP2_PARSE_WRITE) img_param_sw_set_ee_over_sht_en(value);
        img_param_sw_get_ee_over_sht_en(&val_get);
    } else if (strcmp(reg, "pos_edge_strength") == 0) {
        if (type == DSP2_PARSE_WRITE) sw_config.pos_edge_strength = value;
        val_get = sw_config.pos_edge_strength;
    } else if (strcmp(reg, "pos_edge_ovrsht_strength") == 0) {
        if (type == DSP2_PARSE_WRITE) sw_config.pos_edge_ovrsht_strength = value;
        val_get =  sw_config.pos_edge_ovrsht_strength;
    } else if (strcmp(reg, "neg_edge_strength") == 0) {
        if (type == DSP2_PARSE_WRITE) sw_config.neg_edge_strength = value;
        val_get = sw_config.neg_edge_strength;
    } else if (strcmp(reg, "neg_edge_ovrsht_strength") == 0) {
        if (type == DSP2_PARSE_WRITE) sw_config.neg_edge_ovrsht_strength = value;
        val_get =  sw_config.neg_edge_ovrsht_strength;
    } else if (strcmp(reg, "nr_strength") == 0) {
        if (type == DSP2_PARSE_WRITE) sw_config.nr_strength = value;
        val_get =  sw_config.nr_strength;
    } else if (strcmp(reg, "dir_shpness_thr") == 0) {
        if (type == DSP2_PARSE_WRITE) sw_config.dir_shpness_thr = value;
        val_get =  sw_config.dir_shpness_thr;
    } else if (strcmp(reg, "no_dir_shpness_thr") == 0) {
        if (type == DSP2_PARSE_WRITE) sw_config.no_dir_shpness_thr = value;
        val_get =  sw_config.no_dir_shpness_thr;
    } else if (strcmp(reg, "flat_thr") == 0) {
        if (type == DSP2_PARSE_WRITE) sw_config.flat_thr = value;
        val_get =  sw_config.flat_thr;
    } else if (strcmp(reg, "texture_thr") == 0) {
        if (type == DSP2_PARSE_WRITE) sw_config.texture_thr = value;
        val_get =  sw_config.texture_thr;
    } else if (strcmp(reg, "edge_thr") == 0) {
        if (type == DSP2_PARSE_WRITE) sw_config.edge_thr = value;
        val_get =  sw_config.edge_thr;
    } else {
        return -1;
    }

    if (type == DSP2_PARSE_WRITE) {
        ee_control(&sw_config);
        ee_hw_update();
        return 0;
    }
    sprintf(ret_string, "[OK] FW EE_%s: %d", reg, val_get);

    return 0;
}

int DSP2_EE_HW_Parse(int type, char* reg, int value, char* ret_string)
{
    int val_get = 0;
    BL_Fun_Type state = 0;
    DSP2_EE_Str_Type str_cfg = {0};
    DSP2_EE_Thresh_Type thr_cfg = {0};
    
    if (strstr(reg, "en") != NULL) {
        if (strcmp(reg, "ee_en") == 0) {
            if (type == DSP2_PARSE_WRITE) DSP2_Set_EE_State(value);
            DSP2_Get_EE_State(&val_get);
        } else if (strcmp(reg, "ovrsht_en") == 0) {
            if (type == DSP2_PARSE_WRITE) DSP2_Set_EEOverShoot_State(value);
            DSP2_Get_EEOverShoot_State(&val_get);
        } else {
            return -1;
        }

        if (type == DSP2_PARSE_WRITE) {
            return 0;
        }
        sprintf(ret_string, "[OK] EE_%s: %d", reg, val_get);
        return 0;
    }

    if (strstr(reg, "Str") != NULL) {
        DSP2_Get_EE_Strength(&str_cfg);
        if (strcmp(reg, "posEdgeStr") == 0) {
            if (type == DSP2_PARSE_WRITE) str_cfg.posEdgeStr = value;
            val_get = str_cfg.posEdgeStr;
        } else if (strcmp(reg, "negEdgeStr") == 0) {
            if (type == DSP2_PARSE_WRITE) str_cfg.negEdgeStr = value;
            val_get =  str_cfg.negEdgeStr;
        } else if (strcmp(reg, "posEdgeOvrshtStr") == 0) {
            if (type == DSP2_PARSE_WRITE) str_cfg.posEdgeOvrshtStr = value;
            val_get = str_cfg.posEdgeOvrshtStr;
        } else if (strcmp(reg, "negEdgeOvrshtStr") == 0) {
            if (type == DSP2_PARSE_WRITE) str_cfg.negEdgeOvrshtStr = value;
            val_get =  str_cfg.negEdgeOvrshtStr;
        } else if (strcmp(reg, "nrStr") == 0) {
            if (type == DSP2_PARSE_WRITE) str_cfg.nrStr = value;
            val_get = str_cfg.nrStr;
        } else {
            return -1;
        }

        if (type == DSP2_PARSE_WRITE) {
            DSP2_Set_EE_Strength(&str_cfg);
            return 0;
        }
        sprintf(ret_string, "[OK] EE_%s: %d", reg, val_get);
        return 0;
    }

    if (strstr(reg, "Thresh") != NULL) {
        DSP2_Get_EE_Thresh(&thr_cfg);
        if (strcmp(reg, "dirShpnessThresh") == 0) {
            if (type == DSP2_PARSE_WRITE) thr_cfg.dirShpnessThresh = value;
            val_get = thr_cfg.dirShpnessThresh;
        } else if (strcmp(reg, "noDirShpnessThresh") == 0) {
            if (type == DSP2_PARSE_WRITE) thr_cfg.noDirShpnessThresh = value;
            val_get =  thr_cfg.noDirShpnessThresh;
        } else if (strcmp(reg, "flatThresh") == 0) {
            if (type == DSP2_PARSE_WRITE) thr_cfg.flatThresh = value;
            val_get = thr_cfg.flatThresh;
        } else if (strcmp(reg, "textureThresh") == 0) {
            if (type == DSP2_PARSE_WRITE) thr_cfg.textureThresh = value;
            val_get =  thr_cfg.textureThresh;
        } else if (strcmp(reg, "edgeThresh") == 0) {
            if (type == DSP2_PARSE_WRITE) thr_cfg.edgeThresh = value;
            val_get = thr_cfg.edgeThresh;
        } else {
            return -1;
        }

        if (type == DSP2_PARSE_WRITE) {
            DSP2_Set_EE_Thresh(&thr_cfg);
            return 0;
        }
        sprintf(ret_string, "[OK] HW EE_%s: %d", reg, val_get);
        return 0;
    }

    return 0;
}

int DSP2_EE_FW_Tbl_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i = 0;
    DSP2_EE_LUMA_WEIGHT luma_weight_cgf = {0};

    if (type == DSP2_PARSE_WRITE) {
        for (i = 0; i < DSP2_EE_LUMA_WEIGHT_NUM; i++) {
            luma_weight_cgf.weight[i] = value[i];
        }
        img_param_sw_set_ee_luma_weight(&luma_weight_cgf);
        return 0;
    }
    img_param_sw_get_ee_luma_weight(&luma_weight_cgf);

    sprintf(ret_string, "[OK] HW EE_LUMA_WEIGHT: ");
    for (i = 0; i < DSP2_EE_LUMA_WEIGHT_NUM; i++) {
        strCatVal(ret_string, luma_weight_cgf.weight[i]);
    }


    return 0;
}

int DSP2_EE_HW_Tbl_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i = 0;
    DSP2_EE_Luma_Weight_Type luma_weight_cgf = {0};

    if (type == DSP2_PARSE_WRITE) {
        for (i = 0; i < DSP2_EE_LUMA_WEIGHT_NUM; i++) {
            luma_weight_cgf.lumaWgtTbl[i] = value[i];
        }
        DSP2_Set_EE_LumaWeight(&luma_weight_cgf);
        return 0;
    }
    DSP2_Get_EE_LumaWeight(&luma_weight_cgf);

    sprintf(ret_string, "[OK] HW EE_LUMA_WEIGHT: ");
    for (i = 0; i < DSP2_EE_LUMA_WEIGHT_NUM; i++) {
        strCatVal(ret_string, luma_weight_cgf.lumaWgtTbl[i]);
    }


    return 0;
}

int DSP2_CS_FW_Auto_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i = 0;
    DSP2_CS_PARAM *ptr;
    DSP2_CS_PARAM tbl = {0};

    if (type == DSP2_PARSE_WRITE) {
        for (i = 0; i < MAX_ENTRY_NUM_AE_ISO_AUTO; i++) {
            img_param_sw_get_cs(i, &ptr);
            memcpy(&tbl, ptr, sizeof(DSP2_CS_PARAM));
            if (strcmp(reg, "strength") == 0) tbl.strength = value[i];
            else return -1;
            img_param_sw_set_cs(i, &tbl);
        }
        imgproc_set_fw_module_en(DSP2_ADJ_AE, 1);
        return 0;
    }

    sprintf(ret_string, "[OK] auto CS_%s: ", reg);
    for (i = 0; i < MAX_ENTRY_NUM_AE_ISO_AUTO; i++) {
        img_param_sw_get_cs(i, &ptr);
        if (strcmp(reg, "strength") == 0) strCatVal(ret_string, ptr->strength);
        else return -1;
    }

    return 0;
}

int DSP2_CS_FW_Parse(int type, char* reg, int value, char* ret_string)
{
    int val_get = 0;
    DSP2_CS_PARAM sw_config;
    cs_get_sw_config(&sw_config);

    if (strcmp(reg, "strength") == 0) {
        if (type == DSP2_PARSE_WRITE) {
            sw_config.strength = value;
        }
        val_get = sw_config.strength;
    } else {
        return -1;
    }

    if (type == DSP2_PARSE_WRITE) {
        cs_control(&sw_config);
        cs_hw_update();
        return 0;
    }
    sprintf(ret_string, "[OK] FW CS_%s: %d", reg, val_get);

    return 0;
}

int DSP2_CS_HW_Parse(int type, char* reg, int value, char* ret_string)
{
    int val_get = 0;
    DSP2_Chroma_Suppress_Type cfg;
    DSP2_Get_ChromaSuppress(&cfg);

    if (strcmp(reg, "cs_en") == 0) {
        if (type == DSP2_PARSE_WRITE) DSP2_Set_ChromaSuppress_State(value);
        DSP2_Get_ChromaSuppress_State(&val_get);
    } else if (strcmp(reg, "gain") == 0) {
        if (type == DSP2_PARSE_WRITE) cfg.gain = value;
        val_get = cfg.gain;
    } else if (strcmp(reg, "weight") == 0) {
        if (type == DSP2_PARSE_WRITE) cfg.weight = value;
        val_get = cfg.weight;
    } else if (strcmp(reg, "grey_thr") == 0) {
        if (type == DSP2_PARSE_WRITE) cfg.grey_thr = value;
        val_get =  cfg.grey_thr;
    } else {
        return -1;
    }

    if (type == DSP2_PARSE_WRITE) {
        if (strcmp(reg, "cs_en") == 0) return 0;
        DSP2_Set_ChromaSuppress(&cfg);
        return 0;
    }
    sprintf(ret_string, "[OK] HW CS_%s: %d", reg, val_get);

    return 0;
}

int DSP2_YC_FW_Auto_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i = 0;
    DSP2_YC_PARAM *ptr;
    DSP2_YC_PARAM tbl = {0};

    if (type == DSP2_PARSE_WRITE) {
        for (i = 0; i < MAX_ENTRY_NUM_AE_ISO_AUTO; i++) {
            img_param_sw_get_yc(i, &ptr);
            memcpy(&tbl, ptr, sizeof(DSP2_YC_PARAM));
            if (strcmp(reg, "brightness") == 0) tbl.brightness = value[i];
            else if (strcmp(reg, "contrast") == 0) tbl.contrast = value[i];
            else return -1;
            img_param_sw_set_yc(i, &tbl);
            imgproc_set_fw_module_en(DSP2_ADJ_AE, 1);
        }
        return 0;
    }

    sprintf(ret_string, "[OK] auto YC_%s: ", reg);
    for (i = 0; i < MAX_ENTRY_NUM_AE_ISO_AUTO; i++) {
        img_param_sw_get_yc(i, &ptr);
        if (strcmp(reg, "brightness") == 0) strCatVal(ret_string, ptr->brightness);
        else if (strcmp(reg, "contrast") == 0) strCatVal(ret_string, ptr->contrast);
        else return -1;
    }

    return 0;
}

int DSP2_YC_FW_Parse(int type, char* reg, int value, char* ret_string)
{
    int val_get = 0;
    DSP2_YC_PARAM sw_config;
    yc_get_sw_config(&sw_config);

    if (strcmp(reg, "brightness") == 0) {
        if (type == DSP2_PARSE_WRITE) sw_config.brightness = value;
        val_get = sw_config.brightness;
    } else if (strcmp(reg, "contrast") == 0) {
        if (type == DSP2_PARSE_WRITE) sw_config.contrast = value;
        val_get = sw_config.contrast;
    } else {
        return -1;
    }

    if (type == DSP2_PARSE_WRITE) {
        yc_control(&sw_config);
        yc_hw_update();
        return 0;
    }
    sprintf(ret_string, "[OK] FW YC_%s: %d", reg, val_get);

    return 0;
}


int DSP2_YC_HW_Parse(int type, char* reg, int value, char* ret_string)
{
    int val_get = 0;

    if (strcmp(reg, "brightness") == 0) {
        if (type == DSP2_PARSE_WRITE) DSP2_Set_Brightness(value);
        DSP2_Get_Brightness(&val_get);
    } else if (strcmp(reg, "contrast") == 0) {
        if (type == DSP2_PARSE_WRITE) DSP2_Set_Contrast(value);
        DSP2_Get_Contrast(&val_get);
    } else {
        return -1;
    }

    if (type == DSP2_PARSE_WRITE) {
        return 0;
    }
    sprintf(ret_string, "[OK] HW YC_%s: %d", reg, val_get);

    return 0;
}

int DSP2_YUVC_HW_Parse(int type, char* reg, int value, char* ret_string)
{
    int val_get = 0;
    int SepiaCr = 0, SepiaCb = 0;

    DSP2_Get_Sepia(&SepiaCr, &SepiaCb);
    if (strcmp(reg, "special_mode") == 0) {
        if (type == DSP2_PARSE_WRITE) DSP2_Set_Special_Mode(value);
        DSP2_Get_Special_Mode(&val_get);
    } else if (strcmp(reg, "lpf_filter_mode") == 0) {
        if (type == DSP2_PARSE_WRITE) DSP2_Set_LPF_Filting_Mode(value);
        DSP2_Get_LPF_Filting_Mode(&val_get);
    } else if (strcmp(reg, "solar_thred") == 0) {
        if (type == DSP2_PARSE_WRITE) DSP2_Set_Solar_Thred(value);
        DSP2_Get_Solar_Thred(&val_get);
    } else if (strcmp(reg, "sepia_cr") == 0) {
        if (type == DSP2_PARSE_WRITE) DSP2_Set_Sepia(value, SepiaCb);
        val_get = SepiaCr;
    } else if (strcmp(reg, "sepia_cb") == 0) {
        if (type == DSP2_PARSE_WRITE) DSP2_Set_Sepia(SepiaCr, value);
        val_get = SepiaCb;
    } else {
        return -1;
    }

    if (type == DSP2_PARSE_WRITE) {
        return 0;
    }
    sprintf(ret_string, "[OK] HW YC_%s: %d", reg, val_get);

    return 0;
}

