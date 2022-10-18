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
#include "sample_common.h"
#include "mm_dsp2.h"
#include "mm_sensor.h"
#include "mm_debug.h"
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
//#include "helper_dsp2.h"
#include "img_dsp2_parse.h"
#include "helper_dsp2_parse.h"

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

enum numeric_short_options {
    SENSOR_INPUT = 1000,
    SENSOR_REG,
    SYS_REG,
    DSP2_MISC_REG,
    AXI_CTRL_REG,
    TG_REG,
    DATA_DUMP,
    DATA_LOAD,
    MODULE_STATE,
    AE_AUTO,
    AE_REG,
    AE_ARRAY,
    AWB_AUTO,
    AWB_STATS_CONF,
    AWB_CAL,
    AWB_REG,
    AWB_ARRAY,
    BLC_CAL,
    BLC_AUTO,
    BLC_REG,
    DPC_CAL,
    DPC_AUTO,
    DPC_REG,
    BNR_AUTO,
    BNR_REG,
    LSC_AUTO,
    LSC_REG,
    LSC_COEF,
    DG_REG,
    AF_REG,
    CCM_AUTO,
    CCM_REG,
    CCM_COEF,
    GAMMA_AUTO,
    GAMMA_CAL,
    GAMMA_REG,
    GAMMA_CURVE,
    WDR_AUTO,
    WDR_REG,
    WDR_ARRAY,
    SAT_AUTO,
    SAT_REG,
    NR_AUTO,
    NR_REG,
    EE_AUTO,
    EE_REG,
    EE_TBL,
    CS_AUTO,
    CS_REG,
    YC_AUTO,
    YC_REG,
    YUVC_REG,

    MODULE_ATTR,
    REG_ADDR,
    REG_SENSOR_ADDR,
};

static int recvBuf(int dsp2_chann_id, int dsp2_pos, MMDSP2YuvFrame* yuv_frm)
{
    MMDSP2FrmSrcAttr frmsrc_attr;

    MM_DSP2_GetFrameSrcChnAttr(dsp2_chann_id, &frmsrc_attr);
    frmsrc_attr.dsp2Position = dsp2_pos;
    // if pos over dsp2 out, may use the scaler resolution
    #if 0
    if (dsp2_pos <= DSP2_POSITION_DSP2_OUTPUT \
    || dsp2_pos == DSP2_POSITION_SCALER_A || dsp2_pos == DSP2_POSITION_OSD_A || dsp2_pos == DSP2_POSITION_ADJ_A \
    || dsp2_pos == DSP2_POSITION_SCALER_C || dsp2_pos == DSP2_POSITION_OSD_C || dsp2_pos == DSP2_POSITION_ADJ_C) {
      frmsrc_attr.picWidth = 1920;//sensor_width;
      frmsrc_attr.picHeight = 1080;//sensor_height;
    }
    #endif
    MM_DSP2_SetFrameSrcChnAttr(dsp2_chann_id, &frmsrc_attr);

    if (dsp2_pos == DSP2_POSITION_AWB3) MM_DSP2_StartRecvPic(dsp2_chann_id, PIX_FMT_DATA8);
    else MM_DSP2_StartRecvPic(dsp2_chann_id, PIX_FMT_DATA16);
    MM_DSP2_GetOnePicture(dsp2_chann_id, yuv_frm);
    MM_DSP2_StopRecvPic(dsp2_chann_id);

   csi_dcache_invalid_range((void*)yuv_frm->frameStartAddr, yuv_frm->frameSize);

   return 0;

}

static int DSP2_Sensor_Parse(int type, char* reg, int value, char* ret_string)
{
    char *str_ptr = NULL;
    char str_get[16] = {'\0'};
    uint32_t bayerPatternID;

    if (strcmp(reg, "name") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;//read only
        else {
            MM_DBG_GetSensorName(&str_ptr);
            sprintf(str_get, "%s", str_ptr);
        }
    } else if (strcmp(reg, "bayer_pattern") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;//read only
        else {
            MM_DBG_GetSensorBayerPattern(&bayerPatternID);
            sprintf(str_get, "%s", bayer_pattern_str_arr[bayerPatternID]);
        }
    } else {
        return -1;
    }

    if (type == DSP2_PARSE_WRITE) {
        return 0;
    }
    sprintf(ret_string, "[OK] sensor_%s: %s", reg, str_get);

    return 0;
}

static int DSP2_SYS_SW_Parse(int type, char* reg, int value, char* ret_string)
{
    int ret = -1;
    int val_get = 0;
    uint32_t addr = 0;
    char str_get[32] = {'\0'};
    BL_Img_Size_T win;
    BAYER_PATTERN_E bayer_pattern = 0;

    if (strstr(reg, "input") != NULL) {
        if (type == DSP2_PARSE_WRITE)  return -1;//rea only

        bl_dsp2_get_input_resolution(&win);
        if (strcmp(reg, "input_width") == 0) {
            sprintf(str_get, "%d", win.width);
        } else if (strcmp(reg, "input_height") == 0) {
            sprintf(str_get, "%d", win.height);
        } else if (strcmp(reg, "input_resolution") == 0) {
            sprintf(str_get, "%dx%d", win.width, win.height);
        } else {
            return -1;
        }

        if (type == DSP2_PARSE_WRITE) return 0;
        sprintf(ret_string, "[OK] SYS_%s: %s", reg, str_get);
        return 0;
    }

    if (strstr(reg, "output") != NULL) {
        if (type == DSP2_PARSE_WRITE)  return -1;//rea only

        bl_dsp2_get_out_resolution(&win);
        if (strcmp(reg, "output_width") == 0) {
            sprintf(str_get, "%d", win.width);
        } else if (strcmp(reg, "output_height") == 0) {
            sprintf(str_get, "%d", win.height);
        } else if (strcmp(reg, "output_resolution") == 0) {
            sprintf(str_get, "%dx%d", win.width, win.height);
        } else {
            return -1;
        }

        if (type == DSP2_PARSE_WRITE) return 0;
        sprintf(ret_string, "[OK] SYS_%s: %s", reg, str_get);
        return 0;
    }

    if (strcmp(reg, "version") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;//rea only
        sprintf(str_get, "%s", "BL808_v0.0.0\0");
        sprintf(ret_string, "[OK] SYS_%s: %s", reg, str_get);
        return 0;
    } else if (strcmp(reg, "dsp2_status") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;//rea only
        val_get = MM_DSP2_Status();
    } else if (strcmp(reg, "dsp2") == 0) {
        if (type == DSP2_PARSE_WRITE) {
            if(MM_DSP2_Status() == IMGPROC_RUN) return 0;
            ret = sample_system_init();
            return ret;
       }
        else return -1;//write only
    #if 0
    } else if (strcmp(reg, "hdmi") == 0) {
        if (type == DSP2_PARSE_WRITE) {
            ret = hdmi_ctrl(value);
            return ret;
        }
        else return -1;//write only
    #endif
    } else if (strcmp(reg, "log_level") == 0) {
        if (type == DSP2_PARSE_WRITE) ret = BL_DBG_ChgLogPrintLevel((BL_LOGTYPE)value);
        else val_get = BL_DBG_GetLogPrintLevel();
    } else if (strcmp(reg, "algo_log_level") == 0) {
        if (type == DSP2_PARSE_WRITE) ret = BL_ALGO_DBG_ChgLogPrintLevel((BL_LOGTYPE)value);
        else val_get = BL_ALGO_DBG_GetLogPrintLevel();
    } else if (strcmp(reg, "algo_log_ae") == 0) {
        if (type == DSP2_PARSE_WRITE) BL_ALGO_DBG_ChgLogPrintAlgo(BL_ALGO_LOG_AE, (BL_Fun_Type)value);
        else val_get = BL_ALGO_DBG_GetLogPrintAlgo(BL_ALGO_LOG_AE);
    } else if (strcmp(reg, "algo_log_awb") == 0) {
        if (type == DSP2_PARSE_WRITE) BL_ALGO_DBG_ChgLogPrintAlgo(BL_ALGO_LOG_AWB, (BL_Fun_Type)value);
        else val_get = BL_ALGO_DBG_GetLogPrintAlgo(BL_ALGO_LOG_AWB);
    } else if (strcmp(reg, "algo_log_wdr") == 0) {
        if (type == DSP2_PARSE_WRITE) BL_ALGO_DBG_ChgLogPrintAlgo(BL_ALGO_LOG_WDR, (BL_Fun_Type)value);
        else val_get = BL_ALGO_DBG_GetLogPrintAlgo(BL_ALGO_LOG_WDR);
    } else if (strcmp(reg, "flicker_mode") == 0) {
        if (type == DSP2_PARSE_WRITE) ret = imgproc_set_flicker_mode((flicker_mode)value);
        else val_get = imgproc_get_flicker_mode();
    } else if (strcmp(reg, "bayer_pattern") == 0) {
        if (type == DSP2_PARSE_WRITE) {
            bayer_pattern = value;
            DSP2_Set_Bayer_Pattern(bayer_pattern);
        } else {
            DSP2_Get_Bayer_Pattern(&bayer_pattern);
            sprintf(str_get, "%s", bayer_pattern_str_arr[bayer_pattern]);
            sprintf(ret_string, "[OK] sensor_%s: %s", reg, str_get);
            return 0;
        }
    } else if (strcmp(reg, "vir_img_load_addr") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        else MM_DBG_GetVirtSensorTsrcAddr(&addr);
        sprintf(ret_string, "[OK] SYS_%s: 0x%08x", reg, addr);
        return 0;
    } else if (strcmp(reg, "vir_restart") == 0) {
        if (type == DSP2_PARSE_WRITE) imgproc_start();
        else return -1;
        return 0;
    } else {
        return -1;
    }

    if (type == DSP2_PARSE_WRITE) {
        return 0;
    }
    sprintf(ret_string, "[OK] SYS_%s: %d", reg, val_get);

    return 0;
}

static int DSP2_SYS_Parse(int reg_type, int type, char* reg, int value, char* ret_string)
{
    int ret = -1;

    if (reg_type == REG_HW) {
        ret = DSP2_SYS_HW_Parse(type, reg, value, ret_string);
    } else if (reg_type == REG_SW) {
        ret = DSP2_SYS_SW_Parse(type, reg, value, ret_string);
    } else {
        return -1;
    }

    return ret;
}

static int DSP2_DSP2_MISC_Parse(int reg_type, int type, char* reg, int value, char* ret_string)
{
    int ret = -1;

    if (reg_type == REG_HW) {
        ret = DSP2_DSP2_MISC_HW_Parse(type, reg, value, ret_string);
    } else {
        return -1;
    }

    return ret;
}

static int DSP2_AXI_CTRL_Parse(int reg_type, int type, char* reg, int value, char* ret_string)
{
    int ret = -1;

    if (reg_type == REG_HW) {
        ret = DSP2_AXI_CTRL_HW_Parse(type, reg, value, ret_string);
    } else {
        return -1;
    }

    return ret;
}

static int DSP2_TG_Parse(int reg_type, int type, char* reg, int value, char* ret_string)
{
    int ret = -1;

    if (reg_type == REG_HW) {
        ret = DSP2_TG_HW_Parse(type, reg, value, ret_string);
    } else {
        return -1;
    }

    return ret;
}

static int DSP2_Dump_Parse(int type, char* reg, int *value, char* ret_string)
{
    MMDSP2YuvFrame yuv_frm = {0};
    int channel_idx = 0;
    int src_position = 0;
    int data_size = 0;
    int ret = -1;

    if (type != DSP2_PARSE_DUMP) return -1;

    if (strcmp(reg, "src_pos") == 0) {
        channel_idx = value[0];
        src_position = value[1];
        recvBuf(channel_idx, src_position, &yuv_frm);

        sprintf(ret_string, "[OK] Dump_%s: 0x%x,0x%x", reg, (uint32_t)yuv_frm.frameStartAddr, yuv_frm.frameSize);
    } else if (strcmp(reg, "src_addr") == 0) {
        yuv_frm.frameStartAddr = value[0];
        yuv_frm.frameSize = value[1];

        sprintf(ret_string, "[OK] Dump_%s: 0x%x,0x%x", reg, (uint32_t)yuv_frm.frameStartAddr, yuv_frm.frameSize);
    } else  if (strcmp(reg, "nr3d_img") == 0) {
        uint32_t addr = 0, bufSize = 0;
        MMDSP2FrmSrcAttr frmsrc_attr;

        channel_idx = value[0];
        bl_dsp2_get_3dnr_refFrameBuf(&addr, &bufSize);
        MM_DSP2_GetFrameSrcChnAttr(channel_idx, &frmsrc_attr);

        data_size = (frmsrc_attr.picWidth * frmsrc_attr.picHeight ) << 1;
        sprintf(ret_string, "[OK] Dump_%s: 0x%08x,0x%x", reg, (uint32_t)addr, data_size);
        //printf("[OK] Dump_%s: 0x%08x,0x%x", reg, (uint32_t)addr, data_size);
    } else if (strcmp(reg, "gamma_curve") == 0) {
        gamma_cal_t *cal_ptr = NULL;
        int idx = value[0];

        data_size = sizeof(gamma_cal_t);
        img_param_calib_get_gamma(idx, &cal_ptr);
        sprintf(ret_string, "[OK] Dump_%s: 0x%08x,0x%x", reg, (uint32_t)cal_ptr, data_size);
    } else if (strcmp(reg, "wdr_curve") == 0) {
        data_size = sizeof(bl_dsp2_wdr_curve_t);
        bl_get_WDR_curve(&wdr_curve);
        sprintf(ret_string, "[OK] Dump_%s: 0x%08x,0x%x", reg, (uint32_t)&wdr_curve, data_size);
    } else if (strcmp(reg, "wdr_tone_curve") == 0) {
        wdr_tone_curve_conf_t *wdr_tone_curve_ptr = NULL;
        int idx = value[0];

        data_size = sizeof(wdr_tone_curve_conf_t);
        img_param_sw_get_wdr_tone_curve_conf(idx, &wdr_tone_curve_ptr);
        sprintf(ret_string, "[OK] Dump_%s: 0x%08x,0x%x", reg, (uint32_t)wdr_tone_curve_ptr, data_size);
    } else if (strcmp(reg, "ae_hist_y") == 0) {
        data_size = sizeof(bl_dsp2_ae_hist_y_t);
        ret = bl_get_AE_hist_sum_y(&ae_y_sum);
        if (ret < 0) return -1;
        sprintf(ret_string, "[OK] Dump_%s: 0x%08x,0x%x", reg, (uint32_t)&ae_y_sum, data_size);
    } else if (strcmp(reg, "ae_hist_bayer") == 0) {
        data_size = sizeof(bl_dsp2_ae_hist_bayer_t);
        ret = bl_get_AE_hist_sum_bayer(&ae_bayer_sum);
        if (ret < 0) return -1;
        sprintf(ret_string, "[OK] Dump_%s: 0x%08x,0x%x", reg, (uint32_t)&ae_bayer_sum, data_size);
    } else if (strcmp(reg, "ae_grid_sum") == 0) {
        data_size = sizeof(bl_dsp2_ae_grid_sum_t);
        ret = bl_get_AE_stats(&ae_grid_sum);
        if (ret < 0) return -1;
        sprintf(ret_string, "[OK] Dump_%s: 0x%08x,0x%x", reg, (uint32_t)&ae_grid_sum, data_size);
    } else if (strcmp(reg, "awb_sum") == 0) {
        data_size = sizeof(dsp2_awb3_sum_t);
        ret = bl_get_AWB3_sum(&awb3_sum);
        if (ret < 0) return -1;
        sprintf(ret_string, "[OK] Dump_%s: 0x%08x,0x%x", reg, (uint32_t)&awb3_sum, data_size);
    } else {
        return -1;
    }

    return 0;
}

//{'blaic_cmd': BLAIC_LOAD, 'file': file, 'key':'dsp2', 'module': 'data-load', 'type': 'src_input', 'info': int_size}
static int DSP2_Load_Parse(int type, char* reg, int value, char* ret_string)
{
    uint32_t *data_addr = NULL;

    if (type != DSP2_PARSE_LOAD) return -1;

    if (strcmp(reg, "src_input") == 0) {
        #if 0
        data_addr = 0x53000000;//evb:0x53000000, fpga:0xa0000000;
        sprintf(ret_string, "[OK] Load_%s: 0x%08x\r\n", reg, *data_addr);
        #else
        uint32_t addr = 0;
        MM_DBG_GetVirtSensorTsrcAddr(&addr);
        sprintf(ret_string, "[OK] Load_%s: 0x%08x\r\n", reg, (uint32_t)addr);
        #endif
    } else if (strcmp(reg, "src_addr") == 0) {
        sprintf(ret_string, "[OK] Load_%s: ok\r\n", reg);
    } else if (strcmp(reg, "sw_tbl") == 0) {
        uint32_t addr = 0;
        //load_reg(&addr);
        if (img_param_malloc_sw_param_init_buffer() == 1) printf("it's load inited \r\n");
            img_param_get_sw_bin_Addr(addr);
        data_addr = addr;
        sprintf(ret_string, "[OK] Load_%s: 0x%08x", reg, (uint32_t)data_addr);
    } else if (strstr(reg, "gamma_curve") != NULL) {
        int idx = value;
        gamma_cal_t *cal_ptr = NULL;

        img_param_calib_get_gamma(idx, &cal_ptr);//get addr
        sprintf(ret_string, "[OK] Load_%s: 0x%08x", reg, (uint32_t)&cal_ptr->gamma_curve);
        imgproc_set_fw_module_en(DSP2_ADJ_AE, 1);
    } else if (strstr(reg, "wdr_tone_curve") != NULL) {
        int idx = value;
        wdr_tone_curve_conf_t *wdr_tone_curve_ptr = NULL;

        img_param_sw_get_wdr_tone_curve_conf(idx, &wdr_tone_curve_ptr);//get addr
        sprintf(ret_string, "[OK] Load_%s: 0x%08x", reg, (uint32_t)&wdr_tone_curve_ptr->tone_curve);
        imgproc_set_fw_module_en(DSP2_ADJ_AE, 1);
    } else {
        return -1;
    }
    return 0;
}

static int DSP2_Module_State_Parse(int type, char* reg, int value, char* ret_string)
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

static int DSP2_AE_Metering_Tbl_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i = 0, idx = 0;
    
    char *token;
    token = strtok(reg, "metering_tbl_");
    idx = atoi(token);
    DSP2_AE_ATTR attr = {0};
    MM_DSP2_GetAeAttr(&attr);
    if ((idx > AE_METERING_TBL_NUM - 1) || (idx < 0))  return -1;

    if (type == DSP2_PARSE_WRITE) {
        for (i = 0; i < AE_STATS_GRID_NUM; i++) {
            attr.meteringModeTbl[idx].coef[i] = value[i];
        }
        MM_DSP2_SetAeAttr(&attr);
        imgproc_set_fw_module_en(DSP2_ADJ_AE, 1);
        return 0;
    }

    sprintf(ret_string, "[OK] AE_%s: ", reg);
    for (i = 0; i < AE_STATS_GRID_NUM; i++) {
        strCatVal(ret_string, attr.meteringModeTbl[idx].coef[i]);
    }

    return 0;
}

static int DSP2_AE_Agc_DB_Tbl_Parse(int type, char* reg, int *value, char* ret_string)
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

static int DSP2_AE_Auto_Tbl_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i = 0;
    DSP2_AE_ATTR attr = {0};
    MM_DSP2_GetAeAttr(&attr);
    if (type == DSP2_PARSE_WRITE) {
        for (i = 0; i < MAX_ENTRY_NUM_AE_SYS_GAIN_AUTO; i++) {
            if (strcmp(reg, "ae_target") == 0) {
                attr.subAttr[i].ae_target = value[i];
            } else if (strstr(reg, "highlight_weight_idx_") != NULL){
                if (strcmp(reg, "highlight_weight_idx_0") == 0) attr.weightConf.highlight_weight[i].idx[0] = value[i];
                else if (strcmp(reg, "highlight_weight_idx_1") == 0) attr.weightConf.highlight_weight[i].idx[1] = value[i];
                else if (strcmp(reg, "highlight_weight_idx_2") == 0) attr.weightConf.highlight_weight[i].idx[2] = value[i];
                else return -1;
            }
            else return -1;
        }
        MM_DSP2_SetAeAttr(&attr);
        imgproc_set_fw_module_en(DSP2_ADJ_AE, 1);
        return 0;
    }

    sprintf(ret_string, "[OK] auto AE_%s: ", reg);
    for (i = 0; i < MAX_ENTRY_NUM_AE_SYS_GAIN_AUTO; i++) {
        if (strcmp(reg, "ae_target") == 0) {
            strCatVal(ret_string, attr.subAttr[i].ae_target);
        } else if (strstr(reg, "highlight_weight_idx_") != NULL) {
            if (strcmp(reg, "highlight_weight_idx_0") == 0) strCatVal(ret_string, attr.weightConf.highlight_weight[i].idx[0]);
            else if (strcmp(reg, "highlight_weight_idx_1") == 0) strCatVal(ret_string, attr.weightConf.highlight_weight[i].idx[1]);
            else if (strcmp(reg, "highlight_weight_idx_2") == 0) strCatVal(ret_string, attr.weightConf.highlight_weight[i].idx[2]);
            else return -1;
        } else return -1;
    }

    return 0;
}

int DSP2_AE_Auto_Parse(int type, char* reg, int *value, char* ret_string)
{
    int ret = 0;

    if (strstr(reg, "metering_tbl_") != NULL) {
        ret = DSP2_AE_Metering_Tbl_Parse(type, reg, value, ret_string);
    } else if (strstr(reg, "agc_db_tbl") != NULL) {
        ret = DSP2_AE_Agc_DB_Tbl_Parse(type, reg, value, ret_string);
    } else {
        ret = DSP2_AE_Auto_Tbl_Parse(type, reg, value, ret_string);
    }

    return ret;
}


static int DSP2_AE_SW_Parse(int type, char* reg, int value, char* ret_string)
{
    int val_get = 0;
    ae_info_t *ae_info = {0};
    DSP2_AE_INFO ae_info_luma = {0};
    float gain_f = 0.0;
    DSP2_AE_HIGHLIGHT_WEIGHT_CONF *highlight_weight_cfg = {0};
    BL_EXPO_TIME expo_time = EXPO_TIME_1_25_SEC;
    ae_slow_shutter_conf_t *slow_shutter_conf = {0};
    MM_DSP2_GetAeInfo(&ae_info_luma);
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
            ae_info_luma.expo_time = expo_time;
            ae_info_luma.gain = gain_f;
            MM_DSP2_SetAeInfo(&ae_info_luma);
        }
        gain_f = GAIN_DB_INT_TO_FLOAT(ae_info_luma.gain);
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

static int DSP2_AE_Parse(int reg_type, int type, char* reg, int value, char* ret_string)
{
    int ret = -1;

    if (reg_type == REG_HW) {
        ret = DSP2_AE_HW_Parse(type, reg, value, ret_string);
	} else if (reg_type == REG_FW) {
        ret = DSP2_AE_FW_Parse(type, reg, value, ret_string);
    } else if (reg_type == REG_SW) {
        ret = DSP2_AE_SW_Parse(type, reg, value, ret_string);
    } else {
        return -1;
    }

    return ret;
}

static int DSP2_AE_Stats_Hist_Y_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i = 0;
    AE_HIST_MODE_TYPE_E mode;

    bl_get_AE_hist_mode(&mode);
    if(mode == AE_HIST_MODE_BAYER) {
        aos_cli_printf("[NG]Please check hist mode, it's not AE_HIST_MODE_Y.\r\n");
        return -1;
    }

    if (type == DSP2_PARSE_WRITE) {
        return -1;
    }

    bl_get_AE_hist_sum_y(&ae_y_sum);
    sprintf(ret_string, "[OK] AE_Hist_Y: ");
    for (i = 0; i < DSP2_AE_HIST_Y_BIN_NUM; i++) {
        strCatVal(ret_string, ae_y_sum.y[i]);
    }

    return 0;
}

static int DSP2_AE_Stats_Hist_Bayer_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i = 0;
    AE_HIST_MODE_TYPE_E mode;

    bl_get_AE_hist_mode(&mode);
    if(mode == AE_HIST_MODE_Y) {
        aos_cli_printf("[NG]Please check hist mode, it's not AE_HIST_MODE_BAYER.\r\n");
        return -1;
    }

    if (type == DSP2_PARSE_WRITE) {
        return -1;
    }

    bl_get_AE_hist_sum_bayer(&ae_bayer_sum);
    sprintf(ret_string, "[OK] AE_Hist_Bayer: ");
    for (i = 0; i < DSP2_AE_HIST_BAYER_BIN_NUM; i++) strCatVal(ret_string, ae_bayer_sum.r[i]);
    for (i = 0; i < DSP2_AE_HIST_BAYER_BIN_NUM; i++) strCatVal(ret_string, ae_bayer_sum.gr[i]);
    for (i = 0; i < DSP2_AE_HIST_BAYER_BIN_NUM; i++) strCatVal(ret_string, ae_bayer_sum.gb[i]);
    for (i = 0; i < DSP2_AE_HIST_BAYER_BIN_NUM; i++) strCatVal(ret_string, ae_bayer_sum.b[i]);

    return 0;
}

static int DSP2_AE_Stats_Hist_Roi_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i = 0;
    uint16_t x_min = 0, x_max = 0, y_min = 0, y_max = 0;

    if (type == DSP2_PARSE_WRITE) {
        x_min = value[0];
        x_max = value[1];
        y_min = value[2];
        y_max = value[3];
        bl_set_AE_hist_roi(x_min, x_max, y_min, y_max);
        return -1;
    }

    bl_get_AE_hist_roi(&x_min, &x_max, &y_min, &y_max);
    sprintf(ret_string, "[OK] AE_Hist_Roi: ");
    strCatVal(ret_string, x_min);
    strCatVal(ret_string, x_max);
    strCatVal(ret_string, y_min);
    strCatVal(ret_string, y_max);

    return 0;
}

static int DSP2_AE_Stats_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i = 0;
    int sum_val = 0;

    if (type == DSP2_PARSE_WRITE) {
        return -1;
    }

    bl_get_AE_stats(&ae_grid_sum);
    sprintf(ret_string, "[OK] AE_%s: ", reg);
    for (i = 0; i < AE_STATS_GRID_NUM; i++) {
        if (strcmp(reg, "stats_r") == 0) sum_val = ae_grid_sum.r_sum[i];
        else if (strcmp(reg, "stats_g") == 0) sum_val = ae_grid_sum.g_sum[i];
        else if (strcmp(reg, "stats_b") == 0) sum_val = ae_grid_sum.b_sum[i];
        else if (strcmp(reg, "stats_y") == 0) sum_val = ae_grid_sum.y_sum[i];
        strCatVal(ret_string, sum_val);
    }

    return 0;
}

int DSP2_AE_Array_Parse(int type, char* reg, int *value, char* ret_string)
{
    if (strstr(reg, "hist_y") != NULL) {
        DSP2_AE_Stats_Hist_Y_Parse(type, reg, value, ret_string);
    } else if (strstr(reg, "hist_bayer") != NULL) {
        DSP2_AE_Stats_Hist_Bayer_Parse(type, reg, value, ret_string);
    } else if (strstr(reg, "hist_roi") != NULL) {
        DSP2_AE_Stats_Hist_Roi_Parse(type, reg, value, ret_string);
    } else if (strstr(reg, "stats_") != NULL) {
        DSP2_AE_Stats_Parse(type, reg, value, ret_string);
    } else {
        return -1;
    }

    return 0;
}

static int DSP2_AWB3_Stats_Conf_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i = 0, j = 0;
    int val_get = 0;
    dsp2_awb3_stats_conf_t awb_stats_conf;

    DSP2_Get_AWB3_Stats_Conf(&awb_stats_conf);
    if (strcmp(reg, "stat_en") == 0) {
        if (type == DSP2_PARSE_WRITE) DSP2_Set_AWB3_Hist_State(value[0]);
        DSP2_Get_AWB3_Hist_State(&val_get);
    } else if (strcmp(reg, "stat_x_min") == 0) {
        if (type == DSP2_PARSE_WRITE) awb_stats_conf.stat_x_min = value[0];
        val_get = awb_stats_conf.stat_x_min;
    } else if (strcmp(reg, "stat_x_max") == 0) {
        if (type == DSP2_PARSE_WRITE) awb_stats_conf.stat_x_max = value[0];
        val_get = awb_stats_conf.stat_x_max;
    } else if (strcmp(reg, "stat_y_min") == 0) {
        if (type == DSP2_PARSE_WRITE) awb_stats_conf.stat_y_min = value[0];
        val_get = awb_stats_conf.stat_y_min;
    } else if (strcmp(reg, "stat_y_max") == 0) {
        if (type == DSP2_PARSE_WRITE) awb_stats_conf.stat_y_max= value[0];
        val_get = awb_stats_conf.stat_y_max;
    } else if (strcmp(reg, "r_ratio_ofst") == 0) {
        if (type == DSP2_PARSE_WRITE) awb_stats_conf.r_ratio_ofst = value[0];
        val_get = awb_stats_conf.r_ratio_ofst;
    } else if (strcmp(reg, "b_ratio_ofst") == 0) {
        if (type == DSP2_PARSE_WRITE) awb_stats_conf.b_ratio_ofst = value[0];
        val_get = awb_stats_conf.b_ratio_ofst;
    } else if (strcmp(reg, "r_ratio_mult") == 0) {
        if (type == DSP2_PARSE_WRITE) awb_stats_conf.r_ratio_mult = value[0];
        val_get = awb_stats_conf.r_ratio_mult;
    } else if (strcmp(reg, "b_ratio_mult") == 0) {
        if (type == DSP2_PARSE_WRITE) awb_stats_conf.b_ratio_mult = value[0];
        val_get = awb_stats_conf.b_ratio_mult;
    } else if (strcmp(reg, "ratio_sum_min") == 0) {
        if (type == DSP2_PARSE_WRITE) awb_stats_conf.ratio_sum_min = value[0];
        val_get = awb_stats_conf.ratio_sum_min;
    } else if (strcmp(reg, "ratio_sum_max") == 0) {
        if (type == DSP2_PARSE_WRITE) awb_stats_conf.ratio_sum_max = value[0];
        val_get = awb_stats_conf.ratio_sum_max;
    } else if (strcmp(reg, "g_divisor") == 0) {
        if (type == DSP2_PARSE_WRITE) awb_stats_conf.g_divisor = value[0];
        val_get = awb_stats_conf.g_divisor;
    } else if (strcmp(reg, "weight_ratio_en") == 0) {
        if (type == DSP2_PARSE_WRITE) awb_stats_conf.weight_ratio_en = value[0];
        val_get = awb_stats_conf.weight_ratio_en;
    } else if (strcmp(reg, "weight_ratio_gain") == 0) {
        if (type == DSP2_PARSE_WRITE) awb_stats_conf.weight_ratio_gain = value[0];
        val_get = awb_stats_conf.weight_ratio_gain;
    } else if (strcmp(reg, "y_r_coeff") == 0) {
        if (type == DSP2_PARSE_WRITE) awb_stats_conf.y_r_coeff = value[0];
        val_get = awb_stats_conf.y_r_coeff;
    } else if (strcmp(reg, "y_g_coeff") == 0) {
        if (type == DSP2_PARSE_WRITE) awb_stats_conf.y_g_coeff = value[0];
        val_get = awb_stats_conf.y_g_coeff;
    } else if (strcmp(reg, "y_b_coeff") == 0) {
        if (type == DSP2_PARSE_WRITE) awb_stats_conf.y_b_coeff = value[0];
        val_get = awb_stats_conf.y_b_coeff;
    } else if (strcmp(reg, "weight_y_use_g") == 0) {
        if (type == DSP2_PARSE_WRITE) awb_stats_conf.weight_y_use_g = value[0];
        val_get = awb_stats_conf.weight_y_use_g;
    } else if (strcmp(reg, "weight_y_en") == 0) {
        if (type == DSP2_PARSE_WRITE) awb_stats_conf.weight_y_en = value[0];
        val_get = awb_stats_conf.weight_y_en;
    } else if (strcmp(reg, "weight_y_gain") == 0) {
        if (type == DSP2_PARSE_WRITE) awb_stats_conf.weight_y_gain = value[0];
        val_get = awb_stats_conf.weight_y_gain;
    } else if (strcmp(reg, "count_zero_weight") == 0) {
        if (type == DSP2_PARSE_WRITE) awb_stats_conf.count_zero_weight = value[0];
        val_get = awb_stats_conf.count_zero_weight;
    } else if (strcmp(reg, "hist_y_use_g") == 0) {
        if (type == DSP2_PARSE_WRITE) awb_stats_conf.hist_y_use_g = value[0];
        val_get = awb_stats_conf.hist_y_use_g;
    } else if (strcmp(reg, "bin_pixel_clip") == 0) {
        if (type == DSP2_PARSE_WRITE) awb_stats_conf.bin_pixel_clip = value[0];
        val_get = awb_stats_conf.bin_pixel_clip;
    } else if (strcmp(reg, "bin_y_level") == 0) {
        if (type == DSP2_PARSE_WRITE) awb_stats_conf.bin_y_level = value[0];
        val_get = awb_stats_conf.bin_y_level;
    } else if (strcmp(reg, "bin_ratio_level") == 0) {
        if (type == DSP2_PARSE_WRITE) awb_stats_conf.bin_ratio_level = value[0];
        val_get = awb_stats_conf.bin_ratio_level;
    } else if (strcmp(reg, "bin_clip_en") == 0) {
        if (type == DSP2_PARSE_WRITE) awb_stats_conf.bin_clip_en = value[0];
        val_get = awb_stats_conf.bin_clip_en;
    } else if (strcmp(reg, "bin_mode") == 0) {
        if (type == DSP2_PARSE_WRITE) awb_stats_conf.bin_mode = value[0];
        val_get = awb_stats_conf.bin_mode;
    } else if (strcmp(reg, "ink_type") == 0) {
        if (type == DSP2_PARSE_WRITE) awb_stats_conf.ink_type = value[0];
        val_get = awb_stats_conf.ink_type;
    } else if (strcmp(reg, "ink_gain") == 0) {
        if (type == DSP2_PARSE_WRITE) awb_stats_conf.ink_gain = value[0];
        val_get = awb_stats_conf.ink_gain;
    } else if (strcmp(reg, "weight_ratio") == 0) {
        if (type == DSP2_PARSE_WRITE) {
            awb_stats_conf.ink_gain = value[0];
            for (j = 0; j < DSP2_AWB3_WEIGHT_NUM; j++) {
                for (i = 0; i < DSP2_AWB3_WEIGHT_NUM; i++) {
                    awb_stats_conf.weight_ratio[j][i] = value[j * DSP2_AWB3_WEIGHT_NUM + i];
                }
            }
        }
    } else if (strcmp(reg, "weight_y") == 0) {
        if (type == DSP2_PARSE_WRITE) {
            awb_stats_conf.ink_gain = value[0];
            for (j = 0; j < DSP2_AWB3_WEIGHT_NUM; j++) {
                for (i = 0; i < DSP2_AWB3_WEIGHT_NUM; i++) {
                    awb_stats_conf.weight_y[j][i] = value[j * DSP2_AWB3_WEIGHT_NUM + i];
                }
            }
        }
    } else {
        return -1;
    }

    if (type == DSP2_PARSE_WRITE) {
        if (strcmp(reg, "stat_en") == 0) return 0;
        DSP2_Set_AWB3_Stats_Conf(&awb_stats_conf);
        return 0;
    }

    if (strcmp(reg, "weight_ratio") == 0) {
        sprintf(ret_string, "[OK] Stats_Conf AWB_%s: ", reg);
        for (j = 0; j < DSP2_AWB3_WEIGHT_NUM; j++) {
            for (i = 0; i < DSP2_AWB3_WEIGHT_NUM; i++) {
                strCatVal(ret_string, awb_stats_conf.weight_ratio[j][i]);
            }
        }
    } else if (strcmp(reg, "weight_y") == 0) {
        sprintf(ret_string, "[OK] Stats_Conf AWB_%s: ", reg);
        for (j = 0; j < DSP2_AWB3_WEIGHT_NUM; j++) {
            for (i = 0; i < DSP2_AWB3_WEIGHT_NUM; i++) {
                strCatVal(ret_string, awb_stats_conf.weight_y[j][i]);
            }
        }
    } else {
        sprintf(ret_string, "[OK] Stats_Conf AWB_%s: %d", reg, val_get);
    }

    return 0;
}

static int DSP2_AWB1_Stats_Conf_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i = 0, j = 0;
    int val_get = 0;
    dsp2_awb_stats_conf_t awb_stats_conf;

    DSP2_Get_AWB_Stats_Conf(&awb_stats_conf);
    if (strcmp(reg, "roi_start_x") == 0) {
        if (type == DSP2_PARSE_WRITE) awb_stats_conf.roi_start_x = value[0];
        val_get = awb_stats_conf.roi_start_x;
    } else if (strcmp(reg, "roi_start_y") == 0) {
        if (type == DSP2_PARSE_WRITE) awb_stats_conf.roi_start_y = value[0];
        val_get = awb_stats_conf.roi_start_y;
    } else if (strcmp(reg, "roi_width") == 0) {
        if (type == DSP2_PARSE_WRITE) awb_stats_conf.roi_width = value[0];
        val_get = awb_stats_conf.roi_width;
    } else if (strcmp(reg, "roi_height") == 0) {
        if (type == DSP2_PARSE_WRITE) awb_stats_conf.roi_height= value[0];
        val_get = awb_stats_conf.roi_height;
    } else if (strcmp(reg, "img_width") == 0) {
        if (type == DSP2_PARSE_WRITE) awb_stats_conf.img_width = value[0];
        val_get = awb_stats_conf.img_width;
    } else if (strcmp(reg, "img_height") == 0) {
        if (type == DSP2_PARSE_WRITE) awb_stats_conf.img_height = value[0];
        val_get = awb_stats_conf.img_height;
    } else if (strcmp(reg, "grid_width") == 0) {
        if (type == DSP2_PARSE_WRITE) awb_stats_conf.grid_width = value[0];
        val_get = awb_stats_conf.grid_width;
    } else if (strcmp(reg, "grid_height") == 0) {
        if (type == DSP2_PARSE_WRITE) awb_stats_conf.grid_height = value[0];
        val_get = awb_stats_conf.grid_height;
    } else if (strcmp(reg, "grid_num_x") == 0) {
        if (type == DSP2_PARSE_WRITE) awb_stats_conf.grid_num_x = value[0];
        val_get = awb_stats_conf.grid_num_x;
    } else if (strcmp(reg, "grid_num_y") == 0) {
        if (type == DSP2_PARSE_WRITE) awb_stats_conf.grid_num_y = value[0];
        val_get = awb_stats_conf.grid_num_y;
    } else if (strcmp(reg, "r_max_thr") == 0) {
        if (type == DSP2_PARSE_WRITE) awb_stats_conf.r_max_thr = value[0];
        val_get = awb_stats_conf.r_max_thr;
    } else if (strcmp(reg, "r_min_thr") == 0) {
        if (type == DSP2_PARSE_WRITE) awb_stats_conf.r_min_thr = value[0];
        val_get = awb_stats_conf.r_min_thr;
    } else if (strcmp(reg, "g_max_thr") == 0) {
        if (type == DSP2_PARSE_WRITE) awb_stats_conf.g_max_thr = value[0];
        val_get = awb_stats_conf.g_max_thr;
    } else if (strcmp(reg, "g_min_thr") == 0) {
        if (type == DSP2_PARSE_WRITE) awb_stats_conf.g_min_thr = value[0];
        val_get = awb_stats_conf.g_min_thr;
    } else if (strcmp(reg, "b_max_thr") == 0) {
        if (type == DSP2_PARSE_WRITE) awb_stats_conf.b_max_thr = value[0];
        val_get = awb_stats_conf.b_max_thr;
    } else if (strcmp(reg, "b_min_thr") == 0) {
        if (type == DSP2_PARSE_WRITE) awb_stats_conf.b_min_thr = value[0];
        val_get = awb_stats_conf.b_min_thr;
    } else {
        return -1;
    }

    if (type == DSP2_PARSE_WRITE) {
        DSP2_Set_AWB_Stats_Conf(&awb_stats_conf);
        return 0;
    }
    sprintf(ret_string, "[OK] Stats_Conf AWB_%s: %d", reg, val_get);

    return 0;
}

static int DSP2_AWB_Stats_Conf_Parse(int type, char* reg, int *value, char* ret_string)
{
    char *sub_reg = reg;

    if (strstr(reg, "awb3") != NULL) {
        sub_reg = reg + strlen("awb3_");
        DSP2_AWB3_Stats_Conf_Parse(type, sub_reg, value, ret_string);
    } else {
        DSP2_AWB1_Stats_Conf_Parse(type, reg, value, ret_string);
    }

    return 0;
}

static int DSP2_AWB_Calib_Parse(int type, char* reg, int *value, char* ret_string)
{
    if (strstr(reg, "awb") != NULL) {
        DSP2_AWB3_Calib_Bin_Parse(type, reg, value, ret_string);
    } else if (strstr(reg, "wb_info") != NULL) {
        DSP2_WB_Info_Calib_Parse(type, reg, value, ret_string);
    } else {
        return -1;
    }

    return 0;
}

static int DSP2_AWB_SW_Parse(int type, char* reg, int value, char* ret_string)
{
    int64_t val_get = 0;
    DSP2_AWB_ATTR attr = {0};
    DSP2_AWB_WB_INFO info = {0};
    AWB_ALGO algo;
    MM_DSP2_GetAwbAttr(&attr);
    MM_DSP2_GetAwbInfo(&info);
    algo = imgproc_get_awb_algo();
    if (strcmp(reg, "color_temp") == 0) {
        if (type == DSP2_PARSE_WRITE) {
            info.color_temp = value;
            MM_DSP2_SetAwbInfo(value);
            imgproc_set_2A_keep_reg("CT", NULL, NULL, value);
        }
        val_get = info.color_temp;
    } else if (strcmp(reg, "algo") == 0) {
        if (type == DSP2_PARSE_WRITE) MM_DSP2_AWBAlgo(value);
        val_get = algo;
    } else if (strcmp(reg, "version") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        awb_get_algo_version(&val_get);
    } else if (strcmp(reg, "speed_level") == 0) {
        if (type == DSP2_PARSE_WRITE) attr.awbSpeed = value;
        val_get = attr.awbSpeed;
    } else if (strcmp(reg, "special_color_flag") == 0) {
        if (type == DSP2_PARSE_WRITE) awb_set_special_color_flag(value);
        awb_get_special_color_flag((int *)&val_get);
    } else if (strcmp(reg, "preference_en") == 0) {
        if (type == DSP2_PARSE_WRITE) attr.preference_enable = value;
        val_get = attr.preference_enable;
    } else if (strcmp(reg, "special_color_en") == 0) {
        if (type == DSP2_PARSE_WRITE) {
            attr.special_color_enable = value;
            awb_set_special_color_flag(1);
        }
        val_get = attr.special_color_enable;
    } else {
        return -1;
    }

    if (type == DSP2_PARSE_WRITE) {
        MM_DSP2_SetAwbAttr(&attr);
        return 0;
    }
    sprintf(ret_string, "[OK] AWB_%s: %ld", reg, val_get);

    return 0;
}

static int DSP2_AWB_Parse(int reg_type, int type, char* reg, int value, char* ret_string)
{
    int ret = -1;

    if (reg_type == REG_HW) {
        ret = DSP2_AWB_HW_Parse(type, reg, value, ret_string);
	} else if (reg_type == REG_FW) {
        ret = DSP2_AWB_FW_Parse(type, reg, value, ret_string);
    } else if (reg_type == REG_SW) {
        ret = DSP2_AWB_SW_Parse(type, reg, value, ret_string);
    } else {
        return -1;
    }

    return ret;
}

static int DSP2_AWB3_Stats_Hist_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i = 0;
    uint32_t bucket_num;
    uint64_t val_l = 0, val_u = 0, r_ratio = 0, b_ratio = 0;
    uint32_t weight = 0, pixel= 0;
    dsp2_awb3_bin_mode_e mode;

    if (type == DSP2_PARSE_WRITE) {
        return -1;
    }

    bl_get_AWB3_bin_mode(&mode);
    bl_get_AWB3_hist_bin_num(&bucket_num);
    bl_get_AWB3_hist(&awb_stats_hist);

    sprintf(ret_string, "[OK] AWB3_%s %d: ", reg, bucket_num);
    #if 1
    for (i = 0; i < bucket_num; i++) {
        #if 1
        aos_cli_printf("%d: %lu, %lu, %u, %u,\r\n", i, awb_stats_hist.r_ratio[i], awb_stats_hist.b_ratio[i], awb_stats_hist.weight[i], awb_stats_hist.pixel[i]);
        #else
        if (strcmp(reg, "hist_r_ratio") == 0) strCatVal_u64(ret_string, awb_stats_hist.r_ratio[i]);
        else if (strcmp(reg, "hist_b_ratio") == 0) strCatVal_u64(ret_string, awb_stats_hist.b_ratio[i]);
        else if (strcmp(reg, "hist_weight") == 0) strCatVal(ret_string, awb_stats_hist.weight[i]);
        else if (strcmp(reg, "hist_pixel") == 0) strCatVal(ret_string, awb_stats_hist.pixel[i]);
        else {
            if (mode == 0) return -1;
            strCatVal_u64(ret_string, awb_stats_hist.r_ratio[i]);
            strCatVal_u64(ret_string, awb_stats_hist.b_ratio[i]);
            strCatVal(ret_string, awb_stats_hist.weight[i]);
            strCatVal(ret_string, awb_stats_hist.pixel[i]);
        }
        #endif
    }
    #else
    for (i = 0; i < bucket_num; i++) {
        val_u = ((awb_stats_hist.bin[i].footprint[3] << 8) & (0xffffffff00));
        val_l = ((awb_stats_hist.bin[i].footprint[2] >> 24) & (0xff));
        r_ratio = val_u + val_l;//40bit

        val_u = ((awb_stats_hist.bin[i].footprint[2] & (0x00ffffff)) << 16 & (0xffffff0000));
        val_l = (awb_stats_hist.bin[i].footprint[1] >> 16 & (0xffff));
        b_ratio = val_u + val_l;//40bit

        val_u = ((awb_stats_hist.bin[i].footprint[1] & (0x0000ffff)) << 12 & (0xffff000));
        val_l = (awb_stats_hist.bin[i].footprint[0] >> 20 & (0xfff));
        weight = val_u + val_l;//28bit

        val_u = awb_stats_hist.bin[i].footprint[0] & (0x000fffff);
        pixel = val_u;//20bit

        if (i < bucket_num){
            #if 0
            aos_cli_printf("%d: %lu, %lu, %u, %u,\r\n", i, r_ratio, b_ratio, weight, pixel);
            #else
            if (strcmp(reg, "hist_r_ratio") == 0) strCatVal_u64(ret_string, r_ratio);
            else if (strcmp(reg, "hist_b_ratio") == 0) strCatVal_u64(ret_string, b_ratio);
            else if (strcmp(reg, "hist_weight") == 0) strCatVal(ret_string, weight);
            else if (strcmp(reg, "hist_pixel") == 0) strCatVal(ret_string, pixel);
            else {
                if (mode == 0) return -1;
                strCatVal_u64(ret_string, r_ratio);
                strCatVal_u64(ret_string, b_ratio);
                strCatVal(ret_string, weight);
                strCatVal(ret_string, pixel);
            }
            #endif
        }
    }
#endif
    return 0;
}

static int DSP2_AWB3_Sum_Parse(int type, char* reg, int *value, char* ret_string)
{
    if (type == DSP2_PARSE_WRITE) {
        return -1;
    }

    bl_get_AWB3_sum(&awb3_sum);
    sprintf(ret_string, "[OK] AWB3_%s: ", reg);
    strCatVal_u64(ret_string, awb3_sum.r_sum);
    strCatVal_u64(ret_string, awb3_sum.g_sum);
    strCatVal_u64(ret_string, awb3_sum.b_sum);

    strCatVal_u64(ret_string, awb3_sum.r_sum_hex);
    strCatVal_u64(ret_string, awb3_sum.g_sum_hex);
    strCatVal_u64(ret_string, awb3_sum.b_sum_hex);
    strCatVal(ret_string, awb3_sum.pixel_hex);

    strCatVal_u64(ret_string, awb3_sum.r_ratio_hex_y);
    strCatVal_u64(ret_string, awb3_sum.b_ratio_hex_y);
    strCatVal(ret_string, awb3_sum.weight_hex_y);
    strCatVal(ret_string, awb3_sum.pixel_hex_y);

    strCatVal_u64(ret_string, awb3_sum.r_ratio_hist);
    strCatVal_u64(ret_string, awb3_sum.b_ratio_hist);
    strCatVal(ret_string, awb3_sum.weight_hist);
    strCatVal(ret_string, awb3_sum.pixel_hist);

    strCatVal_u64(ret_string, awb3_sum.r_ratio_hist_clip);
    strCatVal_u64(ret_string, awb3_sum.b_ratio_hist_clip);
    strCatVal(ret_string, awb3_sum.weight_hist_clip);
    strCatVal(ret_string, awb3_sum.pixel_hist_clip);

    return 0;

}

int DSP2_AWB_Array_Parse(int type, char* reg, int *value, char* ret_string)
{
    if (strstr(reg, "hist") != NULL) {
        DSP2_AWB3_Stats_Hist_Parse(type, reg, value, ret_string);
    } else if (strstr(reg, "sum") != NULL) {
        DSP2_AWB3_Sum_Parse(type, reg, value, ret_string);
    } else if (strstr(reg, "rgb_gain") != NULL) {
        DSP2_AWB3_rgb_Parse(type, reg, value, ret_string);
    } else {
        return -1;
    }

    return 0;
}

static int DSP2_AWB3_Preference_Tbl_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i = 0, idx = 0;
    DSP2_AWB_ATTR attr = {0};
    char *token;
    token = strtok(reg, "awb_preference_tbl_");
    idx = atoi(token);
    if ((idx > BL_BV_NODES - 1) || (idx < 0))  return -1;
    MM_DSP2_GetAwbAttr(&attr);
    if (type == DSP2_PARSE_WRITE) {
         for (i = 0; i < 3; i++) {
            attr.preference_gain[idx].bais[i].r_gain = value[i * 2];
            attr.preference_gain[idx].bais[i].b_gain = value[i * 2 + 1];
        }
        MM_DSP2_SetAwbAttr(&attr);
        imgproc_set_fw_module_en(DSP2_ADJ_AWB, 1);
        return 0;
    }

    sprintf(ret_string, "[OK] awb preference gain %d: ", idx);
    for (i = 0; i < 3; i++) {
        strCatVal(ret_string, attr.preference_gain[idx].bais[i].r_gain);
        strCatVal(ret_string, attr.preference_gain[idx].bais[i].b_gain);
    }

    return 0;

}

static int DSP2_AWB3_Special_Coloe_Parse(int type, char* reg, int *value, char* ret_string)
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

int DSP2_AWB_Auto_Parse(int type, char* reg, int *value, char* ret_string)
{
    if (strstr(reg, "awb_preference_tbl_") != NULL) {
        DSP2_AWB3_Preference_Tbl_Parse(type, reg, value, ret_string);
    } else if (strstr(reg, "awb_special_color_") != NULL) {
        DSP2_AWB3_Special_Coloe_Parse(type, reg, value, ret_string);
    } else {
        return -1;
    }

    return 0;
}

static int DSP2_BLC_Auto_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i = 0;
    DSP2_BLC_ATTR attr = {0};

    MM_DSP2_GetBlcAttr(&attr);
    if (type == DSP2_PARSE_WRITE) {
        for (i = 0; i < BL_ISO_NODES; i++) {
            if (strcmp(reg, "black_level") == 0) attr.blc[i].black_level = value[i];
            else return -1;
        }
        MM_DSP2_SetBlcAttr(&attr);
        return 0;
    }

    sprintf(ret_string, "[OK] auto BLC_%s: ", reg);
    for (i = 0; i < BL_ISO_NODES; i++) {
        if (strcmp(reg, "black_level") == 0) strCatVal(ret_string, attr.blc[i].black_level);
        else return -1;
    }

    return 0;
}

static int DSP2_BLC_SW_Parse(int type, char* reg, int value, char* ret_string)
{
    int val_get = 0;
    DSP2_BLC_ATTR attr = {0};

    MM_DSP2_GetBlcAttr(&attr);
    if (strcmp(reg, "manual_mode") == 0) {
        if (type == DSP2_PARSE_WRITE) attr.bManualModeEn = value;
        val_get = attr.bManualModeEn;
    } else if (strcmp(reg, "black_level") == 0) {
        if (type == DSP2_PARSE_WRITE) attr.blcLv.black_level = value;
        val_get = attr.blcLv.black_level;
    } else {
        return -1;
    }

    if (type == DSP2_PARSE_WRITE) {
        MM_DSP2_SetBlcAttr(&attr);
        return 0;
    }
    sprintf(ret_string, "[OK] SW BLC_%s: %d", reg, val_get);

    return 0;
}

static int DSP2_BLC_Parse(int reg_type, int type, char* reg, int value, char* ret_string)
{
    int ret = -1;

    if (reg_type == REG_HW) {
        ret = DSP2_BLC_HW_Parse(type, reg, value, ret_string);
	} else if (reg_type == REG_FW) {
        ret = DSP2_BLC_FW_Parse(type, reg, value, ret_string);
    } else if (reg_type == REG_SW) {
        ret = DSP2_BLC_SW_Parse(type, reg, value, ret_string);
    } else {
        return -1;
    }

    return ret;
}

static int DSP2_DPC_Auto_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i = 0;
    DSP2_DPC_ATTR attr = {0};

    MM_DSP2_GetDpcAttr(&attr);
    if (type == DSP2_PARSE_WRITE) {
        for (i = 0; i < BL_ISO_NODES; i++) {
            if (strcmp(reg, "strength") == 0) attr.dpc[i].strength = value[i];
            else return -1;
        }
        MM_DSP2_SetDpcAttr(&attr);
        return 0;
    }

    sprintf(ret_string, "[OK] auto DPC_%s: ", reg);
    for (i = 0; i < BL_ISO_NODES; i++) {
        if (strcmp(reg, "strength") == 0) strCatVal(ret_string, attr.dpc[i].strength);
        else return -1;
    }

    return 0;
}

static int DSP2_DPC_SW_Parse(int type, char* reg, int value, char* ret_string)
{
    int val_get = 0;
    DSP2_DPC_ATTR attr = {0};

    MM_DSP2_GetDpcAttr(&attr);
    if (strcmp(reg, "manual_mode") == 0) {
        if (type == DSP2_PARSE_WRITE) attr.bManualModeEn = value;
        val_get = attr.bManualModeEn;
    } else if (strcmp(reg, "strength") == 0) {
        if (type == DSP2_PARSE_WRITE) attr.dpcLv.strength = value;
        val_get = attr.dpcLv.strength;
    } else {
        return -1;
    }

    if (type == DSP2_PARSE_WRITE) {
        MM_DSP2_SetDpcAttr(&attr);
        return 0;
    }
    sprintf(ret_string, "[OK] SW DPC_%s: %d", reg, val_get);

    return 0;
}

static int DSP2_DPC_Parse(int reg_type, int type, char* reg, int value, char* ret_string)
{
    int ret = -1;

    if (reg_type == REG_HW) {
        ret = DSP2_DPC_HW_Parse(type, reg, value, ret_string);
	} else if (reg_type == REG_FW) {
        ret = DSP2_DPC_FW_Parse(type, reg, value, ret_string);
    } else if (reg_type == REG_SW) {
        ret = DSP2_DPC_SW_Parse(type, reg, value, ret_string);
    } else {
        return -1;
    }

    return ret;
}

static int DSP2_BNR_Auto_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i = 0;
    DSP2_BNR_ATTR attr = {0};

    MM_DSP2_GetBnrAttr(&attr);
    if (type == DSP2_PARSE_WRITE) {
        for (i = 0; i < BL_ISO_NODES; i++) {
            if (strcmp(reg, "strength") == 0) attr.bnr[i].strength = value[i];
            else return -1;
        }
        MM_DSP2_SetBnrAttr(&attr);
        return 0;
    }

    sprintf(ret_string, "[OK] auto BNR_%s: ", reg);
    for (i = 0; i < BL_ISO_NODES; i++) {
        if (strcmp(reg, "strength") == 0) strCatVal(ret_string, attr.bnr[i].strength);
        else return -1;
    }

    return 0;
}

static int DSP2_BNR_SW_Parse(int type, char* reg, int value, char* ret_string)
{
    int val_get = 0;
    DSP2_BNR_ATTR attr = {0};

    MM_DSP2_GetBnrAttr(&attr);
    if (strcmp(reg, "manual_mode") == 0) {
        if (type == DSP2_PARSE_WRITE) attr.bManualModeEn = value;
        val_get = attr.bManualModeEn;
    } else if (strcmp(reg, "strength") == 0) {
        if (type == DSP2_PARSE_WRITE) attr.bnrLv.strength = value;
        val_get =  attr.bnrLv.strength;
    } else {
        return -1;
    }

    if (type == DSP2_PARSE_WRITE) {
        MM_DSP2_SetBnrAttr(&attr);
        return 0;
    }
    sprintf(ret_string, "[OK] SW BNR_%s: %d", reg, val_get);

    return 0;
}

static int DSP2_BNR_Parse(int reg_type, int type, char* reg, int value, char* ret_string)
{
    int ret = -1;

    if (reg_type == REG_HW) {
        ret = DSP2_BNR_HW_Parse(type, reg, value, ret_string);
	} else if (reg_type == REG_FW) {
        ret = DSP2_BNR_FW_Parse(type, reg, value, ret_string);
    } else if (reg_type == REG_SW) {
        ret = DSP2_BNR_SW_Parse(type, reg, value, ret_string);
    } else {
        return -1;
    }

    return ret;
}

static int DSP2_LSC_Auto_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i = 0;
    DSP2_LSC_ATTR attr = {0};

    MM_DSP2_GetLscAttr(&attr);
    if (type == DSP2_PARSE_WRITE) {
        for (i = 0; i < MAX_ENTRY_NUM_AWB_CT_AUTO; i++) {
            if (strcmp(reg, "strength") == 0) attr.lsc[i].strength = value[i];
            else if (strcmp(reg, "color_temp") == 0) attr.lsc[i].color_temp = value[i];
            else return -1;
        }
        MM_DSP2_SetLscAttr(&attr);
        return 0;
    }

    sprintf(ret_string, "[OK] auto LSC_%s: ", reg);
    for (i = 0; i < MAX_ENTRY_NUM_AWB_CT_AUTO; i++) {
        if (strcmp(reg, "strength") == 0) strCatVal(ret_string, attr.lsc[i].strength);
        else if (strcmp(reg, "color_temp") == 0) strCatVal(ret_string, attr.lsc[i].color_temp);
        else return -1;
    }

    return 0;
}

static int DSP2_LSC_SW_Parse(int type, char* reg, int value, char* ret_string)
{
    int val_get = 0;
    DSP2_LSC_ATTR attr = {0};

    MM_DSP2_GetLscAttr(&attr);
    if (strcmp(reg, "manual_mode") == 0) {
        if (type == DSP2_PARSE_WRITE) attr.bManualModeEn = value;
        val_get = attr.bManualModeEn;
    } else if (strcmp(reg, "strength") == 0) {
        if (type == DSP2_PARSE_WRITE) attr.lscLv.strength = value;
        else val_get = attr.lscLv.strength;
    } else if (strcmp(reg, "color_temp") == 0) {
        if (type == DSP2_PARSE_WRITE) attr.lscLv.color_temp = value;
        else val_get = attr.lscLv.color_temp;
    } else {
        return -1;
    }

    if (type == DSP2_PARSE_WRITE) {
        MM_DSP2_SetLscAttr(&attr);
        return 0;
    }

    sprintf(ret_string, "[OK] SW LSC_%s: %d", reg, val_get);

    return 0;
}

static int DSP2_LSC_Parse(int reg_type, int type, char* reg, int value, char* ret_string)
{
    int ret = -1;

    if (reg_type == REG_HW) {
        ret = DSP2_LSC_HW_Parse(type, reg, value, ret_string);
	} else if (reg_type == REG_FW) {
        ret = DSP2_LSC_FW_Parse(type, reg, value, ret_string);
    } else if (reg_type == REG_SW) {
        ret = DSP2_LSC_SW_Parse(type, reg, value, ret_string);
    } else {
        return -1;
    }

    return ret;
}

static int DSP2_LSC_Coef_Parse(int reg_type, int type, char* reg, int *value, char* ret_string)
{
    int ret = -1;

    if (reg_type == REG_HW) {
        ret = DSP2_LSC_Coef_HW_Parse(type, reg, value, ret_string);
    } else if (reg_type == REG_CAL) {
        ret = DSP2_LSC_Calib_Parse(type, reg, value, ret_string);
    } else {
        return -1;
    }

    return ret;
}

static int DSP2_DG_Auto_Parse(int type, char* reg, int *value, char* ret_string)
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
static int DSP2_DG_SW_Parse(int type, char* reg, int value, char* ret_string)
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
    sprintf(ret_string, "[OK] SW DG_%s: %d", reg, val_get);

    return 0;
}
#endif
static int DSP2_DG_Parse(int reg_type, int type, char* reg, int value, char* ret_string)
{
    int ret = -1;

    if (reg_type == REG_HW) {
        ret = DSP2_DG_HW_Parse(type, reg, value, ret_string);
    //} else if (reg_type == REG_SW) {
    //    ret = DSP2_DG_SW_Parse(type, reg, value, ret_string);
    } else {
        return -1;
    }

    return ret;

}

static int DSP2_AF_Parse(int reg_type, int type, char* reg, int value, char* ret_string)
{
    int ret = -1;

    if (reg_type == REG_HW) {
        ret = DSP2_AF_HW_Parse(type, reg, value, ret_string);
    } else {
        return -1;
    }

    return ret;

}

static int DSP2_CCM_Auto_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i = 0, idx = -1;

    DSP2_CCM_ATTR attr = {0};
    MM_DSP2_GetCcmAttr(&attr);
    char *token;
    if (strstr(reg, "coef_") != NULL) {
        token = strtok(reg, "coef_");
        if(token != NULL) idx = atoi(token);
        else return -1;
    }
    if (type == DSP2_PARSE_WRITE) {
        if (strstr(reg, "coef_") != NULL) {
            for (i = 0; i < CCM_COEF_NUM; i++) attr.ccm[idx].coef[i] = value[i];
        } else if (strcmp(reg, "color_temp") == 0) {
            for (i = 0; i < MAX_ENTRY_NUM_AWB_CT_AUTO; i++) {
                attr.ccm[i].color_temp = value[i];
            }
        } else if (strstr(reg, "color_weight") != NULL) {
            for (i = 0; i < MAX_ENTRY_NUM_AE_ISO_AUTO; i++) {
                attr.ccmCw[i].color_weight = value[i];
            }
        } else return -1;
        MM_DSP2_SetCcmAttr(&attr);
        imgproc_set_fw_module_en(DSP2_ADJ_AE, 1);
        imgproc_set_fw_module_en(DSP2_ADJ_AWB, 1);

        return 0;
    }

    sprintf(ret_string, "[OK] auto CCM_%s: ", reg);
    if (strstr(reg, "coef_") != NULL) {
        for (i = 0; i < CCM_COEF_NUM; i++) strCatVal(ret_string, attr.ccm[idx].coef[i]);
    } else if (strcmp(reg, "color_temp") == 0) {
        for (i = 0; i < MAX_ENTRY_NUM_AWB_CT_AUTO; i++) {
            strCatVal(ret_string, attr.ccm[i].color_temp);
        }
    } else if (strcmp(reg, "color_weight") == 0) {
        for (i = 0; i < MAX_ENTRY_NUM_AE_ISO_AUTO; i++) {
            strCatVal(ret_string, attr.ccmCw[i].color_weight);
        }
    } else return -1;

    return 0;
}

static int DSP2_CCM_SW_Parse(int type, char* reg, int value, char* ret_string)
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

static int DSP2_CCM_Parse(int reg_type, int type, char* reg, int value, char* ret_string)
{
    int ret = -1;

    if (reg_type == REG_HW) {
        ret = DSP2_CCM_HW_Parse(type, reg, value, ret_string);
	} else if (reg_type == REG_FW) {
        ret = DSP2_CCM_FW_Parse(type, reg, value, ret_string);
    } else if (reg_type == REG_SW) {
        ret = DSP2_CCM_SW_Parse(type, reg, value, ret_string);
    } else {
        return -1;
    }

    return ret;

}

static int DSP2_CCM_Coef_SW_Parse(int type, char* reg, int *value, char* ret_string)
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

    sprintf(ret_string, "[OK] SW CCM: ");
    for (i = 0; i < CCM_COEF_NUM; i++) {
        strCatVal(ret_string, sw_config.coef[i]);
    }

    return 0;
}

static int DSP2_CCM_Coef_Parse(int reg_type, int type, char* reg, int *value, char* ret_string)
{
    int ret = -1;

    if (reg_type == REG_HW) {
        ret = DSP2_CCM_Coef_HW_Parse(type, reg, value, ret_string);
	} else if (reg_type == REG_FW) {
        ret = DSP2_CCM_Coef_FW_Parse(type, reg, value, ret_string);
    } else if (reg_type == REG_SW) {
        ret = DSP2_CCM_Coef_SW_Parse(type, reg, value, ret_string);
    } else if (reg_type == REG_CAL) {
        ret = DSP2_CCM_Calib_Parse(type, reg, value, ret_string);
    } else {
        return -1;
    }

    return ret;
}

static int DSP2_Gamma_Auto_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i = 0;
    DSP2_GAMMA_ATTR attr = {0};

    MM_DSP2_GetGammaAttr(&attr);
    if (type == DSP2_PARSE_WRITE) {
        for (i = 0; i < BL_BV_NODES; i++) {
            if (strcmp(reg, "idx") == 0) attr.gamma[i].idx = value[i];
            else return -1;
        }
        MM_DSP2_SetGammaAttr(&attr);
        return 0;
    }

    sprintf(ret_string, "[OK] auto GAMMA_%s: ", reg);
    for (i = 0; i < BL_BV_NODES; i++) {
        if (strcmp(reg, "idx") == 0) strCatVal(ret_string, attr.gamma[i].idx);
        else return -1;
    }

    return 0;
}

static int DSP2_Gamma_SW_Parse(int type, char* reg, int value, char* ret_string)
{
    int val_get = 0;
    DSP2_GAMMA_ATTR attr = {0};

    MM_DSP2_GetGammaAttr(&attr);
    if (strcmp(reg, "manual_mode") == 0) {
        if (type == DSP2_PARSE_WRITE) attr.bManualModeEn = value;
        val_get = attr.bManualModeEn;
    } else if (strcmp(reg, "idx") == 0) {
        if (type == DSP2_PARSE_WRITE) attr.gammaLv.idx = value;
        else val_get = attr.gammaLv.idx;
    }
    else {
        return -1;
    }

    if (type == DSP2_PARSE_WRITE) {
        MM_DSP2_SetGammaAttr(&attr);
        return 0;
    }
    sprintf(ret_string, "[OK] SW GAMMA_%s: %d", reg, val_get);

    return 0;
}

static int DSP2_Gamma_Parse(int reg_type, int type, char* reg, int value, char* ret_string)
{
    int ret = -1;

    if (reg_type == REG_SW) {
        ret = DSP2_Gamma_SW_Parse(type, reg, value, ret_string);
   } else if (reg_type == REG_FW) {
        ret = DSP2_Gamma_FW_Parse(type, reg, value, ret_string);
    } else {
        return -1;
    }

    return ret;
}

static int DSP2_Gamma_Curve_Parse(int reg_type, int type, char* reg, int *value, char* ret_string)
{
    int ret = -1;

    if (reg_type == REG_HW) {
        ret = DSP2_Gamma_Curve_HW_Parse(type, reg, value, ret_string);
    } else {
        return -1;
    }

    return ret;
}

static int DSP2_WDR_Auto_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i, idx= 0;
    char *token;

    DSP2_WDR_ATTR attr = {0};
    if (strstr(reg, "tone_curve_idx_") != NULL) {
        token = strtok(reg, "tone_curve_idx_");
        idx = atoi(token);
    }
    else if (strstr(reg, "lowlight_weight_idx_") != NULL) {
        token = strtok(reg, "lowlight_weight_idx_");
        idx = atoi(token);
    }
    MM_DSP2_GetWdrAttr(&attr);
    if (type == DSP2_PARSE_WRITE) {

        for (i = 0; i < BL_BV_NODES; i++) {
            if (strcmp(reg, "cs_strength") == 0) attr.wdr[i].cs_strength = value[i];
            else if (strcmp(reg, "curve_weight") == 0) attr.wdr[i].curve_weight = value[i];
            else if (strcmp(reg, "enh_weight") == 0) attr.wdr[i].enh_weight = value[i];
            else if (strcmp(reg, "bright_enh_level") == 0) attr.wdr[i].bright_enh_level = value[i];
            else if (strcmp(reg, "dark_enh_level") == 0) attr.wdr[i].dark_enh_level = value[i];
            else if (strstr(reg, "tone_curve_idx_") != NULL) {
            for (i = 0; i < WDR_COEF_NUM; i++) {
                    attr.wdrTone.tone_curve_container[idx].tone_curve.coef[i] = value[i];
                }
                attr.wdrTone.tone_curve_container[idx].idx = value[WDR_COEF_NUM];
                break;
            }
            else if (strstr(reg, "lowlight_weight_idx_") != NULL){
                attr.wdrTone.luma_weight_conf.weight[i].idx[idx] = value[i];
            } 
            else return -1;

        }

        MM_DSP2_SetWdrAttr(&attr);
        imgproc_set_fw_module_en(DSP2_ADJ_AE, 1);

        return 0;
    }
    sprintf(ret_string, "[OK] auto WDR_%s: ", reg);

    for (i = 0; i < BL_BV_NODES; i++) {
        if (strcmp(reg, "cs_strength") == 0) strCatVal(ret_string, attr.wdr[i].cs_strength);
        else if (strcmp(reg, "curve_weight") == 0) strCatVal(ret_string, attr.wdr[i].curve_weight);
        else if (strcmp(reg, "enh_weight") == 0) strCatVal(ret_string, attr.wdr[i].enh_weight);
        else if (strcmp(reg, "bright_enh_level") == 0) strCatVal(ret_string, attr.wdr[i].bright_enh_level);
        else if (strcmp(reg, "dark_enh_level") == 0) strCatVal(ret_string, attr.wdr[i].dark_enh_level);
        else if (strstr(reg, "tone_curve_idx_") != NULL) {
                strCatVal(ret_string, attr.wdrTone.tone_curve_container[idx].tone_curve.coef[i]);
                strCatVal(ret_string, attr.wdrTone.tone_curve_container[idx].idx);
        }
        else if (strstr(reg, "lowlight_weight_idx_") != NULL) {
            strCatVal(ret_string, attr.wdrTone.luma_weight_conf.weight[i].idx[idx]);
        }
        else return -1;
    }

    return 0;
}

static int DSP2_WDR_Reg_Parse(int type, char* reg, int value, char* ret_string)
{
    int val_get = 0;

    if (strcmp(reg, "version") == 0) {
        if (type == DSP2_PARSE_WRITE) return -1;
        wdr_get_algo_version(&val_get);
    } else {
        return -1;
    }

    sprintf(ret_string, "[OK] WDR_%s: %d", reg, val_get);

    return 0;
}

static int DSP2_WDR_SW_Parse(int type, char* reg, int value, char* ret_string)
{
    int val_get = 0;

    DSP2_WDR_ATTR attr;

    MM_DSP2_GetWdrAttr(&attr);
    if (strstr(reg, "lowlight_weight_") != NULL) {
        if (type == DSP2_PARSE_WRITE) {
            if (strcmp(reg, "lowlight_weight_thr_0") == 0) attr.wdrTone.luma_weight_conf.thr[0] = value;
            else if (strcmp(reg, "lowlight_weight_thr_1") == 0) attr.wdrTone.luma_weight_conf.thr[1] = value;
            else if (strcmp(reg, "lowlight_weight_thr_2") == 0) attr.wdrTone.luma_weight_conf.thr[2] = value;
            else if (strcmp(reg, "lowlight_weight_thr_3") == 0) attr.wdrTone.luma_weight_conf.thr[3] = value;
            else if (strcmp(reg, "lowlight_weight_roi_start") == 0) attr.wdrTone.luma_weight_conf.roi_start = value;
            else if (strcmp(reg, "lowlight_weight_roi_end") == 0) attr.wdrTone.luma_weight_conf.roi_end = value;
            else return -1;
        }
        if (strcmp(reg, "lowlight_weight_thr_0") == 0) val_get = attr.wdrTone.luma_weight_conf.thr[0];
        else if (strcmp(reg, "lowlight_weight_thr_1") == 0) val_get = attr.wdrTone.luma_weight_conf.thr[1];
        else if (strcmp(reg, "lowlight_weight_thr_2") == 0) val_get = attr.wdrTone.luma_weight_conf.thr[2];
        else if (strcmp(reg, "lowlight_weight_thr_3") == 0) val_get = attr.wdrTone.luma_weight_conf.thr[3];
        else if (strcmp(reg, "lowlight_weight_roi_start") == 0) val_get = attr.wdrTone.luma_weight_conf.roi_start;
        else if (strcmp(reg, "lowlight_weight_roi_end") == 0) val_get = attr.wdrTone.luma_weight_conf.roi_end;
        else return -1;
    } else if (strcmp(reg, "tone_curve_en") == 0) {
        if (type == DSP2_PARSE_WRITE) {
            attr.wdrTone.enable = value;
        }
        val_get = attr.wdrTone.enable;
    } else if (strcmp(reg, "cs_strength") == 0) {
        if (type == DSP2_PARSE_WRITE) attr.wdrLv.cs_strength = value;
        val_get = attr.wdrLv.cs_strength;
    } else if (strcmp(reg, "enh_weight") == 0) {
        if (type == DSP2_PARSE_WRITE) attr.wdrLv.enh_weight = value;
        val_get = attr.wdrLv.enh_weight;
    } else if (strcmp(reg, "curve_weight") == 0) {
        if (type == DSP2_PARSE_WRITE) attr.wdrLv.curve_weight = value;
        val_get = attr.wdrLv.curve_weight;
    } else if (strcmp(reg, "bright_enh_level") == 0) {
        if (type == DSP2_PARSE_WRITE) attr.wdrLv.bright_enh_level = value;
        val_get = attr.wdrLv.bright_enh_level;
    } else if (strcmp(reg, "dark_enh_level") == 0) {
        if (type == DSP2_PARSE_WRITE) attr.wdrLv.dark_enh_level = value;
        val_get = attr.wdrLv.dark_enh_level;
    } else if (strcmp(reg, "manual_mode") == 0) {
        if (type == DSP2_PARSE_WRITE) attr.bManualModeEn = value;
        val_get = attr.bManualModeEn;
    } else {
        return -1;
    }

    if (type == DSP2_PARSE_WRITE) {
        MM_DSP2_SetWdrAttr(&attr);
        return 0;
    }
    sprintf(ret_string, "[OK] SW WDR_%s: %d", reg, val_get);

    return 0;
}

static int DSP2_WDR_Parse(int reg_type, int type, char* reg, int value, char* ret_string)
{
    int ret = -1;
    
    if (strcmp(reg, "version") == 0) {
        ret = DSP2_WDR_Reg_Parse(type, reg, value, ret_string);
    } else if (reg_type == REG_HW) {
        ret = DSP2_WDR_HW_Parse(type, reg, value, ret_string);
    } else if (reg_type == REG_SW) {
        ret = DSP2_WDR_SW_Parse(type, reg, value, ret_string);
    } else {
        return -1;
    }

    return ret;
}

static int DSP2_WDR_Curve_Parse(int type, char* reg, int *value, char* ret_string)
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

static int DSP2_WDR_Array_Parse(int type, char* reg, int *value, char* ret_string)
{
    int ret = -1;

    if (strstr(reg, "curve") != NULL) {
        ret = DSP2_WDR_Curve_Parse(type, reg, value, ret_string);
    } else if (strstr(reg, "hist_roi") != NULL) {
        ret = DSP2_WDR_Stats_Hist_Roi_Parse(type, reg, value, ret_string);
    } else if (strstr(reg, "hist") != NULL) {
        ret = DSP2_WDR_Stats_Hist_Parse(type, reg, value, ret_string);
    } else {
        return -1;
    }

    return ret;
}

static int DSP2_SAT_Auto_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i = 0;
    DSP2_SAT_ATTR attr = {0};

    MM_DSP2_GetSaturationAttr(&attr);
    if (type == DSP2_PARSE_WRITE) {
        if (strcmp(reg, "value") == 0) {
            for (i = 0; i < BL_ISO_NODES; i++) {
                attr.sat[i].value = value[i];
            }
            MM_DSP2_SetSaturationAttr(&attr);
            return 0;
        } else return -1;
    }

    sprintf(ret_string, "[OK] auto SAT_%s: ", reg);
    if (strcmp(reg, "value") == 0){
        for (i = 0; i < BL_ISO_NODES; i++) {
             strCatVal(ret_string, attr.sat[i].value);
        }
    } else return -1;

    return 0;
}

static int DSP2_SAT_SW_Parse(int type, char* reg, int value, char* ret_string)
{
    int val_get = 0;
    DSP2_SAT_ATTR attr;

    MM_DSP2_GetSaturationAttr(&attr);
    if (strcmp(reg, "manual_mode") == 0) {
        if (type == DSP2_PARSE_WRITE) attr.bManualModeEn = value;
        val_get = attr.bManualModeEn;
    } else if (strcmp(reg, "value") == 0) {
        if (type == DSP2_PARSE_WRITE) {
            attr.satLv.value = value;
        }
        val_get = attr.satLv.value;
    } else {
        return -1;
    }

    if (type == DSP2_PARSE_WRITE) {
        MM_DSP2_SetSaturationAttr(&attr);
        return 0;
    }
    sprintf(ret_string, "[OK] SW SAT_%s: %d", reg, val_get);

    return 0;
}

static int DSP2_SAT_Parse(int reg_type, int type, char* reg, int value, char* ret_string)
{
    int ret = -1;

    if (reg_type == REG_HW) {
        ret = DSP2_SAT_HW_Parse(type, reg, value, ret_string);
	} else if (reg_type == REG_FW) {
        ret = DSP2_SAT_FW_Parse(type, reg, value, ret_string);
    } else if (reg_type == REG_SW) {
        ret = DSP2_SAT_SW_Parse(type, reg, value, ret_string);
    } else {
        return -1;
    }

    return ret;
}

static int DSP2_NR_Auto_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i = 0;
    DSP2_NR_ATTR attr = {0};

    MM_DSP2_GetNrAttr(&attr);
    if (type == DSP2_PARSE_WRITE) {
        for (i = 0; i < BL_ISO_NODES; i++) {
            if (strcmp(reg, "strength_level") == 0) attr.nr[i].strength_level = value[i];
            else if (strcmp(reg, "strength_2d") == 0) attr.nr[i].strength_2d = value[i];
            else if (strcmp(reg, "strength_3d") == 0) attr.nr[i] .strength_3d= value[i];
            else return -1;
        }
        MM_DSP2_SetNrAttr(&attr);
        return 0;
    }

    sprintf(ret_string, "[OK] auto NR_%s: ", reg);
    for (i = 0; i < BL_ISO_NODES; i++) {
        if (strcmp(reg, "strength_level") == 0) strCatVal(ret_string, attr.nr[i].strength_level);
        else if (strcmp(reg, "strength_2d") == 0) strCatVal(ret_string, attr.nr[i].strength_2d);
        else if (strcmp(reg, "strength_3d") == 0) strCatVal(ret_string, attr.nr[i].strength_3d);
        else return -1;
    }

    return 0;
}

static int DSP2_NR_SW_Parse(int type, char* reg, int value, char* ret_string)
{
    int val_get = 0;
    DSP2_NR_ATTR attr = {0};

    MM_DSP2_GetNrAttr(&attr);
    if (strcmp(reg, "manual_mode") == 0) {
        if (type == DSP2_PARSE_WRITE) attr.bManualModeEn = value;
        val_get = attr.bManualModeEn;
    } else if (strcmp(reg, "strength_level") == 0) {
        if (type == DSP2_PARSE_WRITE) attr.nrLv.strength_level = value;
        val_get = attr.nrLv.strength_level;
    } else if (strcmp(reg, "strength_2d") == 0) {
        if (type == DSP2_PARSE_WRITE) attr.nrLv.strength_2d = value;
        val_get = attr.nrLv.strength_2d;
    } else if (strcmp(reg, "strength_3d") == 0) {
        if (type == DSP2_PARSE_WRITE) attr.nrLv.strength_3d = value;
        val_get = attr.nrLv.strength_3d;
    } else {
        return -1;
    }

    if (type == DSP2_PARSE_WRITE) {
        MM_DSP2_SetNrAttr(&attr);
        return 0;
    }
    sprintf(ret_string, "[OK] SW NR_%s: %d", reg, val_get);


    return 0;
}

static int DSP2_NR_Parse(int reg_type, int type, char* reg, int value, char* ret_string)
{
    int ret = -1;

    if (reg_type == REG_HW) {
        ret = DSP2_NR_HW_Parse(type, reg, value, ret_string);
    } else if (reg_type == REG_FW) {
        ret = DSP2_NR_FW_Parse(type, reg, value, ret_string);
    } else if (reg_type == REG_SW) {
        ret = DSP2_NR_SW_Parse(type, reg, value, ret_string);
    } else {
        return -1;
    }

    return ret;
}

static int DSP2_EE_Auto_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i = 0;
    DSP2_EE_ATTR attr = {0};

    MM_DSP2_GetEeAttr(&attr);
    if (type == DSP2_PARSE_WRITE) {
        for (i = 0; i < MAX_ENTRY_NUM_AE_ISO_AUTO; i++) {
            if (strcmp(reg, "pos_edge_strength") == 0) attr.ee[i].pos_edge_strength = value[i];
            else if (strcmp(reg, "neg_edge_strength") == 0) attr.ee[i] .neg_edge_strength= value[i];
            else if (strcmp(reg, "pos_edge_ovrsht_strength") == 0) attr.ee[i].pos_edge_ovrsht_strength = value[i];
            else if (strcmp(reg, "neg_edge_ovrsht_strength") == 0) attr.ee[i].neg_edge_ovrsht_strength= value[i];
            else if (strcmp(reg, "nr_strength") == 0) attr.ee[i].nr_strength= value[i];
            else if (strcmp(reg, "dir_shpness_thr") == 0) attr.ee[i].dir_shpness_thr= value[i];
            else if (strcmp(reg, "no_dir_shpness_thr") == 0) attr.ee[i].no_dir_shpness_thr= value[i];
            else if (strcmp(reg, "flat_thr") == 0) attr.ee[i].flat_thr= value[i];
            else if (strcmp(reg, "texture_thr") == 0) attr.ee[i].texture_thr= value[i];
            else if (strcmp(reg, "edge_thr") == 0) attr.ee[i].edge_thr= value[i];
            else return -1;
        }
        MM_DSP2_SetEeAttr(&attr);
        return 0;
    }

    sprintf(ret_string, "[OK] auto EE_%s: ", reg);
    for (i = 0; i < MAX_ENTRY_NUM_AE_ISO_AUTO; i++) {
        if (strcmp(reg, "pos_edge_strength") == 0) strCatVal(ret_string, attr.ee[i].pos_edge_strength);
        else if (strcmp(reg, "neg_edge_strength") == 0) strCatVal(ret_string, attr.ee[i].neg_edge_strength);
        else if (strcmp(reg, "pos_edge_ovrsht_strength") == 0) strCatVal(ret_string, attr.ee[i].pos_edge_ovrsht_strength);
        else if (strcmp(reg, "neg_edge_ovrsht_strength") == 0) strCatVal(ret_string, attr.ee[i].neg_edge_ovrsht_strength);
        else if (strcmp(reg, "nr_strength") == 0) strCatVal(ret_string, attr.ee[i].nr_strength);
        else if (strcmp(reg, "dir_shpness_thr") == 0) strCatVal(ret_string, attr.ee[i].dir_shpness_thr);
        else if (strcmp(reg, "no_dir_shpness_thr") == 0) strCatVal(ret_string, attr.ee[i].no_dir_shpness_thr);
        else if (strcmp(reg, "flat_thr") == 0) strCatVal(ret_string, attr.ee[i].flat_thr);
        else if (strcmp(reg, "texture_thr") == 0) strCatVal(ret_string, attr.ee[i].texture_thr);
        else if (strcmp(reg, "edge_thr") == 0) strCatVal(ret_string, attr.ee[i].edge_thr);
        else return -1;
    }

    return 0;
}

static int DSP2_EE_SW_Parse(int type, char* reg, int value, char* ret_string)
{
    int val_get = 0;
    DSP2_EE_ATTR attr = {0};

    MM_DSP2_GetEeAttr(&attr);
    if (strcmp(reg, "manual_mode") == 0) {
        if (type == DSP2_PARSE_WRITE) attr.bManualModeEn = value;
        val_get = attr.bManualModeEn;
    } else if (strcmp(reg, "ovrsht_en") == 0) {
        if (type == DSP2_PARSE_WRITE) attr.bOvrShtEn = value;
        val_get = attr.bOvrShtEn;
    } else if (strcmp(reg, "pos_edge_strength") == 0) {
        if (type == DSP2_PARSE_WRITE) attr.eeLv.pos_edge_strength = value;
        val_get = attr.eeLv.pos_edge_strength;
    } else if (strcmp(reg, "pos_edge_ovrsht_strength") == 0) {
        if (type == DSP2_PARSE_WRITE) attr.eeLv.pos_edge_ovrsht_strength = value;
        val_get =  attr.eeLv.pos_edge_ovrsht_strength;
    } else if (strcmp(reg, "neg_edge_strength") == 0) {
        if (type == DSP2_PARSE_WRITE) attr.eeLv.neg_edge_strength = value;
        val_get = attr.eeLv.neg_edge_strength;
    } else if (strcmp(reg, "neg_edge_ovrsht_strength") == 0) {
        if (type == DSP2_PARSE_WRITE) attr.eeLv.neg_edge_ovrsht_strength = value;
        val_get =  attr.eeLv.neg_edge_ovrsht_strength;
    } else if (strcmp(reg, "nr_strength") == 0) {
        if (type == DSP2_PARSE_WRITE) attr.eeLv.nr_strength = value;
        val_get =  attr.eeLv.nr_strength;
    } else if (strcmp(reg, "dir_shpness_thr") == 0) {
        if (type == DSP2_PARSE_WRITE) attr.eeLv.dir_shpness_thr = value;
        val_get =  attr.eeLv.dir_shpness_thr;
    } else if (strcmp(reg, "no_dir_shpness_thr") == 0) {
        if (type == DSP2_PARSE_WRITE) attr.eeLv.no_dir_shpness_thr = value;
        val_get =  attr.eeLv.no_dir_shpness_thr;
    } else if (strcmp(reg, "flat_thr") == 0) {
        if (type == DSP2_PARSE_WRITE) attr.eeLv.flat_thr = value;
        val_get =  attr.eeLv.flat_thr;
    } else if (strcmp(reg, "texture_thr") == 0) {
        if (type == DSP2_PARSE_WRITE) attr.eeLv.texture_thr = value;
        val_get =  attr.eeLv.texture_thr;
    } else if (strcmp(reg, "edge_thr") == 0) {
        if (type == DSP2_PARSE_WRITE) attr.eeLv.edge_thr = value;
        val_get =  attr.eeLv.edge_thr;
    } else {
        return -1;
    }

    if (type == DSP2_PARSE_WRITE) {
        MM_DSP2_SetEeAttr(&attr);
        return 0;
    }
    sprintf(ret_string, "[OK] SW EE_%s: %d", reg, val_get);

    return 0;
}

static int DSP2_EE_Parse(int reg_type, int type, char* reg, int value, char* ret_string)
{
    int ret = -1;

    if (reg_type == REG_HW) {
        ret = DSP2_EE_HW_Parse(type, reg, value, ret_string);
    } else if (reg_type == REG_FW) {
        ret = DSP2_EE_FW_Parse(type, reg, value, ret_string);
    } else if (reg_type == REG_SW) {
        ret = DSP2_EE_SW_Parse(type, reg, value, ret_string);
    } else {
        return -1;
    }

    return ret;
}

static int DSP2_EE_SW_Tbl_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i = 0;
    DSP2_EE_ATTR attr = {0};

    MM_DSP2_GetEeAttr(&attr);
    if (type == DSP2_PARSE_WRITE) {
        for (i = 0; i < BL_EE_LUMA_WEIGHT_NUM; i++) {
            attr.eeLumaWeightTbl.weight[i] = value[i];
        }
        MM_DSP2_SetEeAttr(&attr);
        return 0;
    }

    sprintf(ret_string, "[OK] SW EE_LUMA_WEIGHT: ");
    for (i = 0; i < BL_EE_LUMA_WEIGHT_NUM; i++) {
        strCatVal(ret_string, attr.eeLumaWeightTbl.weight[i]);
    }


    return 0;
}

static int DSP2_EE_Tbl_Parse(int reg_type, int type, char* reg, int value, char* ret_string)
{
    int ret = -1;

    if (reg_type == REG_HW) {
        ret = DSP2_EE_HW_Tbl_Parse(type, reg, value, ret_string);
    } else if (reg_type == REG_FW) {
        ret = DSP2_EE_FW_Tbl_Parse(type, reg, value, ret_string);
    } else if (reg_type == REG_SW) {
        ret = DSP2_EE_SW_Tbl_Parse(type, reg, value, ret_string);
    } else {
        return -1;
    }

    return ret;
}

static int DSP2_CS_Auto_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i = 0;
    DSP2_CS_ATTR attr = {0};

    MM_DSP2_GetCsAttr(&attr);
    if (type == DSP2_PARSE_WRITE) {
        for (i = 0; i < MAX_ENTRY_NUM_AE_ISO_AUTO; i++) {
            if (strcmp(reg, "strength") == 0) attr.cs[i].strength = value[i];
            else return -1;
        }
        MM_DSP2_SetCsAttr(&attr);
        return 0;
    }

    sprintf(ret_string, "[OK] auto CS_%s: ", reg);
    for (i = 0; i < MAX_ENTRY_NUM_AE_ISO_AUTO; i++) {
        if (strcmp(reg, "strength") == 0) strCatVal(ret_string, attr.cs[i].strength);
        else return -1;
    }

    return 0;
}

static int DSP2_CS_SW_Parse(int type, char* reg, int value, char* ret_string)
{
    int val_get = 0;
    DSP2_CS_ATTR attr = {0};

    MM_DSP2_GetCsAttr(&attr);
    if (strcmp(reg, "manual_mode") == 0) {
        if (type == DSP2_PARSE_WRITE) attr.bManualModeEn = value;
        val_get = attr.bManualModeEn;
    } else if (strcmp(reg, "strength") == 0) {
        if (type == DSP2_PARSE_WRITE) {
            attr.csLv.strength = value;
        }
        val_get = attr.csLv.strength;
    } else {
        return -1;
    }

    if (type == DSP2_PARSE_WRITE) {
        MM_DSP2_SetCsAttr(&attr);
        return 0;
    }
    sprintf(ret_string, "[OK] SW CS_%s: %d", reg, val_get);

    return 0;
}

static int DSP2_CS_Parse(int reg_type, int type, char* reg, int value, char* ret_string)
{
    int ret = -1;

    if (reg_type == REG_HW) {
        ret = DSP2_CS_HW_Parse(type, reg, value, ret_string);
	} else if (reg_type == REG_FW) {
        ret = DSP2_CS_FW_Parse(type, reg, value, ret_string);
    } else if (reg_type == REG_SW) {
        ret = DSP2_CS_SW_Parse(type, reg, value, ret_string);
    } else {
        return -1;
    }

    return ret;
}

static int DSP2_YC_Auto_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i = 0;
    DSP2_YC_ATTR attr = {0};

    MM_DSP2_GetYcAttr(&attr);
    if (type == DSP2_PARSE_WRITE) {
        for (i = 0; i < MAX_ENTRY_NUM_AE_ISO_AUTO; i++) {
            if (strcmp(reg, "brightness") == 0) attr.yc[i].brightness = value[i];
            else if (strcmp(reg, "contrast") == 0) attr.yc[i].contrast = value[i];
            else return -1;
        }
        MM_DSP2_SetYcAttr(&attr);
        return 0;
    }

    sprintf(ret_string, "[OK] auto YC_%s: ", reg);
    for (i = 0; i < MAX_ENTRY_NUM_AE_ISO_AUTO; i++) {
        if (strcmp(reg, "brightness") == 0) strCatVal(ret_string,attr.yc[i].brightness);
        else if (strcmp(reg, "contrast") == 0) strCatVal(ret_string, attr.yc[i].contrast);
        else return -1;
    }

    return 0;
}

static int DSP2_YC_SW_Parse(int type, char* reg, int value, char* ret_string)
{
    int val_get = 0;
    DSP2_YC_ATTR attr = {0};

    MM_DSP2_GetYcAttr(&attr);
    if (strcmp(reg, "manual_mode") == 0) {
        if (type == DSP2_PARSE_WRITE) attr.bManualModeEn = value;
        val_get = attr.bManualModeEn;
    } else if (strcmp(reg, "brightness") == 0) {
        if (type == DSP2_PARSE_WRITE) attr.ycLv.brightness = value;
        val_get = attr.ycLv.brightness;
    } else if (strcmp(reg, "contrast") == 0) {
        if (type == DSP2_PARSE_WRITE) attr.ycLv.contrast = value;
        val_get = attr.ycLv.contrast;
    } else {
        return -1;
    }

    if (type == DSP2_PARSE_WRITE) {
        MM_DSP2_SetYcAttr(&attr);
        return 0;
    }
    sprintf(ret_string, "[OK] SW YC_%s: %d", reg, val_get);

    return 0;
}

static int DSP2_YC_Parse(int reg_type, int type, char* reg, int value, char* ret_string)
{
    int ret = -1;

    if (reg_type == REG_HW) {
        ret = DSP2_YC_HW_Parse(type, reg, value, ret_string);
    } else if (reg_type == REG_SW) {
        ret = DSP2_YC_SW_Parse(type, reg, value, ret_string);
    } else {
        return -1;
    }

    return ret;
}

static int DSP2_YUVC_Parse(int reg_type, int type, char* reg, int value, char* ret_string)
{
    int ret = -1;

    if (reg_type == REG_HW) {
        ret = DSP2_YUVC_HW_Parse(type, reg, value, ret_string);
    } else {
        return -1;
    }

    return ret;
}

static int DSP2_MODULE_Attr_Parse(int type, char* reg, int *value, char* ret_string)
{
    int i = 0, j = 0, ret = 0;
    char str_get[32] = {'\0'};
    DSP2_SAT_ATTR sat;
    MMSensorAttr sns_attr;
    MMDSP2VinAttr vin_attr;
    DSP2_AE_INFO ae_info;
    DSP2_AWB_WB_INFO awb_info;
    uint32_t hw_module_cfg;
    VIDEO_MODE_E sensor_fmt;
    uint32_t binAddr, binSize, pix_clk, sec_time, fps;

    if (type == DSP2_PARSE_WRITE) {
        if (strcmp(reg, "sat") == 0) {
            sat.bSaturationEn = value[0];
            sat.bManualModeEn = value[1];
            sat.satLv.value = value[2];
            for (i = 0; i < BL_ISO_NODES; i++) {
                sat.sat[i].value = value[3 + i];
            }
            ret = MM_DSP2_SetSaturationAttr(&sat);
            imgproc_set_fw_module_en(DSP2_ADJ_AE, 1);
        } else if (strcmp(reg, "HWmoduleCfg") == 0) {
            hw_module_cfg = value[0];
            ret = MM_DSP2_SetHWmoduleCfg(hw_module_cfg);
        } else if (strcmp(reg, "pix_clk") == 0) {
            pix_clk = value[0];
            ret = MM_Sensor_SetPixClk(pix_clk);
        } else if (strcmp(reg, "sensor_fmt") == 0) {
            sensor_fmt = value[0];
            ret = MM_Sensor_SetFmt(sensor_fmt);
        } else if (strcmp(reg, "img_proc_fps") == 0) {
            return -1;
        } else if (strcmp(reg, "sensor_fps") == 0) {
            return -1;
        } else if (strcmp(reg, "vi_attr") == 0) {
            vin_attr.total_win.width  = value[0];
            vin_attr.total_win.height = value[1];
            vin_attr.act_win.width  = value[2];
            vin_attr.act_win.height = value[3];
            vin_attr.out_win.width  = value[4];
            vin_attr.out_win.height = value[5];
            vin_attr.bayer_pattern= value[6]; 
            vin_attr.fps= value[7];
            ret = MM_DSP2_SetVinAttr(&vin_attr);
        } else if (strcmp(reg, "change_resolution") == 0) {
            ret = MM_Sensor_ChangeFmt((VIDEO_MODE_E)value[0]);
        } else if (strcmp(reg, "awb_info") == 0) {
            awb_info.r_gain = value[0];
            awb_info.g_gain = value[1];
            awb_info.b_gain = value[2];
            awb_info.color_temp = value[3];
            ret = MM_DSP2_SetAwbInfo(&awb_info);
        } else if (strcmp(reg, "ae_info") == 0) {
            ae_info.expo_time = value[0];
            ae_info.gain = value[1];
            ret = MM_DSP2_SetAeInfo(&ae_info);
        }
        return ret;
    }

    sprintf(ret_string, "[OK] module attr %s: ", reg);
    if (strcmp(reg, "sat") == 0) {
        ret = MM_DSP2_GetSaturationAttr(&sat);
        strCatVal(ret_string, sat.bSaturationEn);
        strCatVal(ret_string, sat.bManualModeEn);
        strCatVal(ret_string, sat.satLv.value);
        for (i = 0; i < BL_ISO_NODES; i++) {
            strCatVal(ret_string, sat.sat[i].value);
        }
    } else if (strcmp(reg, "HWmoduleCfg") == 0) {
        ret = MM_DSP2_GetHWmoduleCfg(&hw_module_cfg);
        strCatVal(ret_string, hw_module_cfg);
    } else if (strcmp(reg, "pix_clk") == 0) {
        ret = MM_Sensor_GetPixClk(&pix_clk);
        strCatVal(ret_string, pix_clk);
    } else if (strcmp(reg, "sensor_fmt") == 0) {
        ret = MM_Sensor_GetFmt(&sensor_fmt);
        //strCatVal(ret_string, sensor_fmt);
        sprintf(str_get, "%s,", video_mode_str_arr[sensor_fmt]);
        strcat(ret_string, str_get);
    } else if (strcmp(reg, "img_proc_fps") == 0) {
        fps = imgproc_get_fps();
        strCatVal(ret_string, fps);
    } else if (strcmp(reg, "sensor_fps") == 0) {
        sensor_get_fps(&fps);
        strCatVal(ret_string, fps);
    } else if (strcmp(reg, "bin_addr") == 0) {
        ret = MM_DSP2_GetBinAddr(&binAddr, &binSize);
        sprintf(str_get, "0x%x,%d", binAddr, binSize);
        strcat(ret_string, str_get);
    } else if (strcmp(reg, "vi_state") == 0) {
        MM_Sensor_GetChnAttr(0, &sns_attr);
        strCatVal(ret_string, sns_attr.picWidth);
        strCatVal(ret_string, sns_attr.picHeight);
        strCatVal(ret_string, sns_attr.fps);
    } else if (strcmp(reg, "vi_attr") == 0) {
        MM_DSP2_GetVinAttr(&vin_attr);
        strCatVal(ret_string, vin_attr.total_win.width);
        strCatVal(ret_string, vin_attr.total_win.height);
        strCatVal(ret_string, vin_attr.act_win.width);
        strCatVal(ret_string, vin_attr.act_win.height);
        strCatVal(ret_string, vin_attr.out_win.width);
        strCatVal(ret_string, vin_attr.out_win.height);
        strCatVal(ret_string, vin_attr.bayer_pattern);
        strCatVal(ret_string, vin_attr.fps);
    } else if (strcmp(reg, "ae_stats_sum") == 0) {
        ret = MM_DSP2_GetAeStats(&ae_stats);
        for(i = 0; i < 3; i++) {//for(i = 0; i < AE_STATS_GRID_NUM; i++) {
            strCatVal(ret_string, ae_stats.aeGridSum.r_sum[i]);
            strCatVal(ret_string, ae_stats.aeGridSum.g_sum[i]);
            strCatVal(ret_string, ae_stats.aeGridSum.b_sum[i]);
            strCatVal(ret_string, ae_stats.aeGridSum.y_sum[i]);
        }
    } else if (strcmp(reg, "ae_stats_hist") == 0) {
        ret = MM_DSP2_GetAeStats(&ae_stats);
        for(i = 0; i < 13; i++) {//for(i = 0; i < DSP2_AE_HIST_Y_BIN_NUM; i++) {
            strCatVal(ret_string, ae_stats.aeHistY[i]);
        }
    } else if (strcmp(reg, "awb1_stats") == 0) {
        ret = MM_DSP2_GetAwbStats(&awb_stats);
        for(j = 0; j < 3; j++) { //for(j = 0; j < AWB1_STATS_GRID_NUM_Y; j++) {
            for(i = 0; i < 3; i++) {//for(i = 0; i < AWB1_STATS_GRID_NUM_X; i++)
                strCatVal(ret_string, awb_stats.awb1Stats.sum[j * AWB1_STATS_GRID_NUM_X + i].r_sum);
                strCatVal(ret_string, awb_stats.awb1Stats.sum[j * AWB1_STATS_GRID_NUM_X + i].g_sum);
                strCatVal(ret_string, awb_stats.awb1Stats.sum[j * AWB1_STATS_GRID_NUM_X + i].b_sum);
            }
        }
    } else if (strcmp(reg, "awb3_stats") == 0) {
        ret = MM_DSP2_GetAwbStats(&awb_stats);
        strCatVal(ret_string, awb_stats.awb3Stats.r_sum);
        strCatVal(ret_string, awb_stats.awb3Stats.g_sum);
        strCatVal(ret_string, awb_stats.awb3Stats.b_sum);
    } else if (strcmp(reg, "awb_info") == 0) {
        ret = MM_DSP2_GetAwbInfo(&awb_info);
        strCatVal(ret_string, awb_info.r_gain);
        strCatVal(ret_string, awb_info.g_gain);
        strCatVal(ret_string, awb_info.b_gain);
        strCatVal(ret_string, awb_info.color_temp);
    } else if (strcmp(reg, "ae_info") == 0) {
        ret = MM_DSP2_GetAeInfo(&ae_info);
        strCatVal(ret_string, ae_info.expo_time);
        strCatVal(ret_string, ae_info.gain);
    }
    
    
    return ret;
}

static int DSP2_REG_ADDR_Parse(int type, char* reg, int value, char* ret_string)
{
    int ret = 0;
    uint32_t data = 0, addr = 0;
    addr = strtoul(reg, NULL, 0);// must with '0x'

    if (type == DSP2_PARSE_WRITE) {
        if (strstr(reg, "0x") != NULL) {
            ret = MM_DSP2_SetDsp2Reg(addr, value);
        }
        return ret;
    }

    sprintf(ret_string, "[OK] reg addr %s: ", reg);
    if (strstr(reg, "0x") != NULL) {
        ret = MM_DSP2_GetDsp2Reg(addr, &data);
        strCatVal(ret_string, data);
        strCatVal_hex(ret_string, data);
    }
    return ret;
}

static int DSP2_REG_SENSOR_ADDR_Parse(int type, char* reg, int value, char* ret_string)
{
    int ret = 0;
    uint32_t data = 0, addr = 0;
    addr = strtoul(reg, NULL, 16);// must with '0x'

    if (type == DSP2_PARSE_WRITE) {
        if (strstr(reg, "0x") != NULL) {
            ret = MM_Sensor_SetSensorReg(addr, value);
        }
        return ret;
    }

    sprintf(ret_string, "[OK] reg addr %s: ", reg);
    if (strstr(reg, "0x") != NULL) {
        ret = MM_Sensor_GetSensorReg(addr, &data);
        strCatVal(ret_string, data);
    }
    return ret;
}

static int swich_cmd(char *str)
{
    if (strcmp(str, "sensor-reg") == 0) return SENSOR_REG;
    else if (strcmp(str, "sys-reg") == 0) return SYS_REG;
    else if (strcmp(str, "dsp2-misc-reg") == 0) return DSP2_MISC_REG;
    else if (strcmp(str, "axi-ctrl-reg") == 0) return AXI_CTRL_REG;
    else if (strcmp(str, "tg-reg") == 0) return  TG_REG;
    else if (strcmp(str, "data-dump") == 0) return DATA_DUMP;
    else if (strcmp(str, "data-load") == 0) return DATA_LOAD;
    else if (strcmp(str, "module-state") == 0) return MODULE_STATE;
    else if (strcmp(str, "ae-auto") == 0) return  AE_AUTO;
    else if (strcmp(str, "ae-reg") == 0) return  AE_REG;
    else if (strcmp(str, "ae-array") == 0) return  AE_ARRAY;
    else if (strcmp(str, "awb-auto") == 0) return  AWB_AUTO;
    else if (strcmp(str, "awb-stats-conf") == 0) return  AWB_STATS_CONF;
    else if (strcmp(str, "awb-cal") == 0) return  AWB_CAL;
    else if (strcmp(str, "awb-reg") == 0) return  AWB_REG;
    else if (strcmp(str, "awb-array") == 0) return  AWB_ARRAY;
    else if (strcmp(str, "blc-cal") == 0) return  BLC_CAL;
    else if (strcmp(str, "blc-auto") == 0) return  BLC_AUTO;
    else if (strcmp(str, "blc-reg") == 0) return  BLC_REG;
    else if (strcmp(str, "dpc-cal") == 0) return  DPC_CAL;
    else if (strcmp(str, "dpc-auto") == 0) return  DPC_AUTO;
    else if (strcmp(str, "dpc-reg") == 0) return  DPC_REG;
    else if (strcmp(str, "bnr-auto") == 0) return  BNR_AUTO;
    else if (strcmp(str, "bnr-reg") == 0) return  BNR_REG;
    else if (strcmp(str, "lsc-auto") == 0) return  LSC_AUTO;
    else if (strcmp(str, "lsc-reg") == 0) return  LSC_REG;
    else if (strcmp(str, "lsc-coef") == 0) return  LSC_COEF;
    else if (strcmp(str, "dg-reg") == 0) return  DG_REG;
    else if (strcmp(str, "af-reg") == 0) return AF_REG;
    else if (strcmp(str, "ccm-auto") == 0) return  CCM_AUTO;
    else if (strcmp(str, "ccm-reg") == 0) return  CCM_REG;
    else if (strcmp(str, "ccm-coef") == 0) return  CCM_COEF;
    else if (strcmp(str, "gamma-auto") == 0) return  GAMMA_AUTO;
    else if (strcmp(str, "gamma-cal") == 0) return  GAMMA_CAL;
    else if (strcmp(str, "gamma-reg") == 0) return  GAMMA_REG;
    else if (strcmp(str, "gamma-curve") == 0) return  GAMMA_CURVE;
    else if (strcmp(str, "wdr-auto") == 0) return  WDR_AUTO;
    else if (strcmp(str, "wdr-reg") == 0) return  WDR_REG;
    else if (strcmp(str, "wdr-array") == 0) return  WDR_ARRAY;
    else if (strcmp(str, "saturation-auto") == 0) return SAT_AUTO;
    else if (strcmp(str, "saturation-reg") == 0) return SAT_REG;
    else if (strcmp(str, "nr-auto") == 0) return  NR_AUTO;
    else if (strcmp(str, "nr-reg") == 0) return  NR_REG;
    else if (strcmp(str, "ee-auto") == 0) return  EE_AUTO;
    else if (strcmp(str, "ee-reg") == 0) return  EE_REG;
    else if (strcmp(str, "ee-tbl") == 0) return  EE_TBL;
    else if (strcmp(str, "cs-auto") == 0) return  CS_AUTO;
    else if (strcmp(str, "cs-reg") == 0) return  CS_REG;
    else if (strcmp(str, "yc-auto") == 0) return  YC_AUTO;
    else if (strcmp(str, "yc-reg") == 0) return YC_REG;
    else if (strcmp(str, "yuvc-reg") == 0) return YUVC_REG;

    else if (strcmp(str, "module-attr") == 0) return MODULE_ATTR;
    else if (strcmp(str, "reg-addr") == 0) return REG_ADDR;
    else if (strcmp(str, "reg-sensor_addr") == 0) return REG_SENSOR_ADDR;
    else return -1;

}

int parse_dsp2_cmd(char* module, char* argv_reg, char* argv_val, int payload_len_in, char* ret_string)
{
    int arr_num = 0;
    int ret = -1;
    int *array = NULL;
    char reg_in[32] = {0}, reg[32] = {0};
    int reg_type;

    //aos_cli_printf("swich_cmd(module) %d, %d\r\n", swich_cmd(module));
    //aos_cli_printf(" module %s, argv_reg %s, argv_val %s\r\n", module, argv_reg, argv_val);

    if (argv_val != NULL) {
        array = malloc(sizeof(int) * payload_len_in);
        memset(array, 0, sizeof(int) * payload_len_in);
        isIntgerArray(argv_val, array, &arr_num); // because token,so argv_val will be change
    }
    //aos_cli_printf("arr_num %d\r\n", arr_num);

    int ch = swich_cmd(module);
    switch (ch)
    {
    case SENSOR_REG: {
        if (arr_num != 0) {
            ret = DSP2_Sensor_Parse(DSP2_PARSE_WRITE, argv_reg, array[0], ret_string);
        } else {
            ret = DSP2_Sensor_Parse(DSP2_PARSE_READ, argv_reg, NULL, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    case SYS_REG: {
        sprintf(reg_in, argv_reg);
        reg_type = parseToolReg((char*)&reg_in, (char*)&reg);
        if (arr_num != 0) {
            ret = DSP2_SYS_Parse(reg_type, DSP2_PARSE_WRITE, reg, array[0], ret_string);
        } else {
            ret = DSP2_SYS_Parse(reg_type, DSP2_PARSE_READ, reg, NULL, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    case DSP2_MISC_REG: {
        sprintf(reg_in, argv_reg);
        reg_type = parseToolReg((char*)&reg_in, (char*)&reg);
        if (arr_num != 0) {
            ret = DSP2_DSP2_MISC_Parse(reg_type, DSP2_PARSE_WRITE, reg, array[0], ret_string);
        } else {
            ret = DSP2_DSP2_MISC_Parse(reg_type, DSP2_PARSE_READ, reg, NULL, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    case AXI_CTRL_REG: {
        sprintf(reg_in, argv_reg);
        reg_type = parseToolReg((char*)&reg_in, (char*)&reg);
        if (arr_num != 0) {
            ret = DSP2_AXI_CTRL_Parse(reg_type, DSP2_PARSE_WRITE, reg, array[0], ret_string);
        } else {
            ret = DSP2_AXI_CTRL_Parse(reg_type, DSP2_PARSE_READ, reg, NULL, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    case TG_REG: {
        sprintf(reg_in, argv_reg);
        reg_type = parseToolReg((char*)&reg_in, (char*)&reg);
        if (arr_num != 0) {
            ret = DSP2_TG_Parse(reg_type, DSP2_PARSE_WRITE, reg, array[0], ret_string);
        } else {
            ret = DSP2_TG_Parse(reg_type, DSP2_PARSE_READ, reg, NULL, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    case DATA_DUMP: {
        if (arr_num != 0) {
            ret = DSP2_Dump_Parse(DSP2_PARSE_DUMP, argv_reg, array, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    case DATA_LOAD: {
        if (arr_num != 0) {
          ret = DSP2_Load_Parse(DSP2_PARSE_LOAD, argv_reg, array[0], ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    case MODULE_STATE: {
        if (arr_num != 0) {
            ret = DSP2_Module_State_Parse(DSP2_PARSE_WRITE, argv_reg, array[0], ret_string);
        } else {
            ret = DSP2_Module_State_Parse(DSP2_PARSE_READ, argv_reg, NULL, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    case AE_AUTO: {
        if (arr_num != 0) {
            if ((arr_num != MAX_ENTRY_NUM_AE_SYS_GAIN_AUTO) && (arr_num != AE_STATS_GRID_NUM)) ret = -1;
            else ret = DSP2_AE_Auto_Parse(DSP2_PARSE_WRITE, argv_reg, array, ret_string);
        } else {
            ret = DSP2_AE_Auto_Parse(DSP2_PARSE_READ, argv_reg, NULL, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    case AE_REG: {
        sprintf(reg_in, argv_reg);
        reg_type = parseToolReg((char*)&reg_in, (char*)&reg);
        if (arr_num != 0) {
            ret = DSP2_AE_Parse(reg_type, DSP2_PARSE_WRITE, reg, array[0], ret_string);
        } else {
            ret = DSP2_AE_Parse(reg_type, DSP2_PARSE_READ, reg, NULL, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    case AE_ARRAY: {
        if (arr_num != 0) {
            ret = DSP2_AE_Array_Parse(DSP2_PARSE_WRITE, argv_reg, array, ret_string);
        } else {
            ret = DSP2_AE_Array_Parse(DSP2_PARSE_READ, argv_reg, NULL, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    case AWB_AUTO: {
        if (arr_num != 0) {
            ret = DSP2_AWB_Auto_Parse(DSP2_PARSE_WRITE, argv_reg, array, ret_string);
        } else {
            ret = DSP2_AWB_Auto_Parse(DSP2_PARSE_READ, argv_reg, NULL, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    case AWB_STATS_CONF: {
        if (arr_num != 0) {
            ret = DSP2_AWB_Stats_Conf_Parse(DSP2_PARSE_WRITE, argv_reg, array, ret_string);
        } else {
            ret = DSP2_AWB_Stats_Conf_Parse(DSP2_PARSE_READ, argv_reg, NULL, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    case AWB_CAL: {
        sprintf(reg_in, argv_reg);
        reg_type = parseToolReg((char*)&reg_in, (char*)&reg);
        if (arr_num != 0) {
            if ((arr_num != AWB_CAL_WB_INFO_NUM) && (arr_num != AWB_CAL_AWB_NUM)) ret = -1;
            else ret = DSP2_AWB_Calib_Parse(DSP2_PARSE_WRITE, reg, array, ret_string);
        } else {
            ret = DSP2_AWB_Calib_Parse(DSP2_PARSE_READ, reg, NULL, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    case AWB_REG: {
        sprintf(reg_in, argv_reg);
        reg_type = parseToolReg((char*)&reg_in, (char*)&reg);
        if (arr_num != 0) {
            ret = DSP2_AWB_Parse(reg_type, DSP2_PARSE_WRITE, reg, array[0], ret_string);
        } else {
            ret = DSP2_AWB_Parse(reg_type, DSP2_PARSE_READ, reg, NULL, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    case AWB_ARRAY: {
        if (arr_num != 0) {
            ret = DSP2_AWB_Array_Parse(DSP2_PARSE_WRITE, argv_reg, array, ret_string);
        } else {
            ret = DSP2_AWB_Array_Parse(DSP2_PARSE_READ, argv_reg, NULL, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    case BLC_CAL: {
        sprintf(reg_in, argv_reg);
        reg_type = parseToolReg((char*)&reg_in, (char*)&reg);
        if (arr_num != 0) {
            if (arr_num != MAX_ENTRY_NUM_AE_ISO_AUTO) ret = -1;
            else ret = DSP2_BLC_Calib_Parse(DSP2_PARSE_WRITE, reg, array, ret_string);
        } else {
            ret = DSP2_BLC_Calib_Parse(DSP2_PARSE_READ, reg, NULL, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    case BLC_AUTO: {
        if (arr_num != 0) {
            if (arr_num != MAX_ENTRY_NUM_AE_ISO_AUTO) ret = -1;
            else ret = DSP2_BLC_Auto_Parse(DSP2_PARSE_WRITE, argv_reg, array, ret_string);
        } else {
            ret = DSP2_BLC_Auto_Parse(DSP2_PARSE_READ, argv_reg, NULL, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    case BLC_REG: {
        sprintf(reg_in, argv_reg);
        reg_type = parseToolReg((char*)&reg_in, (char*)&reg);
       if (arr_num != 0) {
            ret = DSP2_BLC_Parse(reg_type, DSP2_PARSE_WRITE, reg, array[0], ret_string);
        } else {
            ret = DSP2_BLC_Parse(reg_type, DSP2_PARSE_READ, reg, NULL, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    case DPC_CAL: {
        sprintf(reg_in, argv_reg);
        reg_type = parseToolReg((char*)&reg_in, (char*)&reg);
        if (arr_num != 0) {
            if (arr_num != MAX_ENTRY_NUM_AE_ISO_AUTO * 2) ret = -1;
            else ret = DSP2_DPC_Calib_Parse(DSP2_PARSE_WRITE, reg, array, ret_string);
        } else {
            ret = DSP2_DPC_Calib_Parse(DSP2_PARSE_READ, reg, NULL, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    case DPC_AUTO: {
        if (arr_num != 0) {
            if (arr_num != MAX_ENTRY_NUM_AE_ISO_AUTO) ret = -1;
            else ret = DSP2_DPC_Auto_Parse(DSP2_PARSE_WRITE, argv_reg, array, ret_string);
        } else {
            ret = DSP2_DPC_Auto_Parse(DSP2_PARSE_READ, argv_reg, NULL, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    case DPC_REG: {
        sprintf(reg_in, argv_reg);
        reg_type = parseToolReg((char*)&reg_in, (char*)&reg);
        if (arr_num != 0) {
            ret = DSP2_DPC_Parse(reg_type, DSP2_PARSE_WRITE, reg, array[0], ret_string);
        } else {
            ret = DSP2_DPC_Parse(reg_type, DSP2_PARSE_READ, reg, NULL, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    case BNR_AUTO: {
        if (arr_num != 0) {
            if (arr_num != MAX_ENTRY_NUM_AE_ISO_AUTO) ret = -1;
            else ret = DSP2_BNR_Auto_Parse(DSP2_PARSE_WRITE, argv_reg, array, ret_string);
        } else {
            ret = DSP2_BNR_Auto_Parse(DSP2_PARSE_READ, argv_reg, NULL, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    case BNR_REG: {
        sprintf(reg_in, argv_reg);
        reg_type = parseToolReg((char*)&reg_in, (char*)&reg);
        if (arr_num != 0) {
            ret = DSP2_BNR_Parse(reg_type, DSP2_PARSE_WRITE, reg, array[0], ret_string);
        } else {
            ret = DSP2_BNR_Parse(reg_type, DSP2_PARSE_READ, reg, NULL, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    case LSC_AUTO: {
        if (arr_num != 0) {
            if (arr_num != MAX_ENTRY_NUM_AWB_CT_AUTO) ret = -1;
            else ret = DSP2_LSC_Auto_Parse(DSP2_PARSE_WRITE, argv_reg, array, ret_string);
        } else {
            ret = DSP2_LSC_Auto_Parse(DSP2_PARSE_READ, argv_reg, NULL, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    case LSC_REG: {
        sprintf(reg_in, argv_reg);
        reg_type = parseToolReg((char*)&reg_in, (char*)&reg);
        if (arr_num != 0) {
            ret = DSP2_LSC_Parse(reg_type, DSP2_PARSE_WRITE, reg, array[0], ret_string);
        } else {
            ret = DSP2_LSC_Parse(reg_type, DSP2_PARSE_READ, reg, NULL, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    case LSC_COEF: {
        sprintf(reg_in, argv_reg);
        reg_type = parseToolReg((char*)&reg_in, (char*)&reg);

        if (arr_num != 0) {
            if ((arr_num == LSC_COEF_NUM) || (arr_num == LSC_CAL_REG_NUM * 2)) {
               ret = DSP2_LSC_Coef_Parse(reg_type, DSP2_PARSE_WRITE, reg, array, ret_string);
            } else {
                ret = -1;
            }
        } else {
            ret = DSP2_LSC_Coef_Parse(reg_type, DSP2_PARSE_READ, reg, NULL, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    case DG_REG: {
        sprintf(reg_in, argv_reg);
        reg_type = parseToolReg((char*)&reg_in, (char*)&reg);
        if (arr_num != 0) {
            ret = DSP2_DG_Parse(reg_type, DSP2_PARSE_WRITE, reg, array[0], ret_string);
        } else {
            ret = DSP2_DG_Parse(reg_type, DSP2_PARSE_READ, reg, NULL, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    case AF_REG: {
        sprintf(reg_in, argv_reg);
        reg_type = parseToolReg((char*)&reg_in, (char*)&reg);
        if (arr_num != 0) {
            ret = DSP2_AF_Parse(reg_type, DSP2_PARSE_WRITE, reg, array[0], ret_string);
        } else {
            ret = DSP2_AF_Parse(reg_type, DSP2_PARSE_READ, reg, NULL, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    case CCM_AUTO: {
        if (arr_num != 0) {
            if ((arr_num != MAX_ENTRY_NUM_AWB_CT_AUTO) && (arr_num != CCM_COEF_NUM) && (arr_num != MAX_ENTRY_NUM_AE_ISO_AUTO)) ret = -1;
            else ret = DSP2_CCM_Auto_Parse(DSP2_PARSE_WRITE, argv_reg, array, ret_string);
        } else {
            ret = DSP2_CCM_Auto_Parse(DSP2_PARSE_READ, argv_reg, NULL, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    case CCM_REG: {
        sprintf(reg_in, argv_reg);
        reg_type = parseToolReg((char*)&reg_in, (char*)&reg);
        if (arr_num != 0) {
            ret = DSP2_CCM_Parse(reg_type, DSP2_PARSE_WRITE, reg, array[0], ret_string);
        } else {
            ret = DSP2_CCM_Parse(reg_type, DSP2_PARSE_READ, reg, NULL, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    case CCM_COEF: {
        sprintf(reg_in, argv_reg);
        reg_type = parseToolReg((char*)&reg_in, (char*)&reg);
        if (arr_num != 0) {
            if ((arr_num == CCM_COEF_NUM) || (arr_num == CCM_CAL_REG_NUM * 7)) {
                ret = DSP2_CCM_Coef_Parse(reg_type, DSP2_PARSE_WRITE, reg, array, ret_string);
            } else {
                ret = -1;
            }
        } else {
            ret = DSP2_CCM_Coef_Parse(reg_type, DSP2_PARSE_READ, reg, NULL, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    case GAMMA_AUTO: {
        if (arr_num != 0) {
            if (arr_num != MAX_ENTRY_NUM_AE_SYS_GAIN_AUTO) ret = -1;
            else ret = DSP2_Gamma_Auto_Parse(DSP2_PARSE_WRITE, argv_reg, array, ret_string);
        } else {
            ret = DSP2_Gamma_Auto_Parse(DSP2_PARSE_READ, argv_reg, NULL, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    case GAMMA_CAL: {
        if (arr_num != 0) {
            if ((arr_num != MAX_ENTRY_NUM_GAMMA_IDX_AUTO) || (arr_num != GAMMA_COEF_NUM)) ret = -1;
            else ret = DSP2_Gamma_Calib_Parse(DSP2_PARSE_WRITE, argv_reg, array, ret_string);
        } else {
            ret = DSP2_Gamma_Calib_Parse(DSP2_PARSE_READ, argv_reg, NULL, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    case GAMMA_REG: {
        sprintf(reg_in, argv_reg);
        reg_type = parseToolReg((char*)&reg_in, (char*)&reg);
        if (arr_num != 0) {
            ret = DSP2_Gamma_Parse(reg_type, DSP2_PARSE_WRITE, reg, array[0], ret_string);
        } else {
            ret = DSP2_Gamma_Parse(reg_type, DSP2_PARSE_READ, reg, NULL, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    case GAMMA_CURVE: {
        sprintf(reg_in, argv_reg);
        reg_type = parseToolReg((char*)&reg_in, (char*)&reg);
        if (arr_num != 0) {
            if ((arr_num == GAMMA_COEF_NUM) || (arr_num == GAMMA_CAL_REG_NUM * 3)) {
                ret = DSP2_Gamma_Curve_Parse(reg_type, DSP2_PARSE_WRITE, reg, array, ret_string);
            } else {
                ret = -1;
            }
        } else {
            ret = DSP2_Gamma_Curve_Parse(reg_type, DSP2_PARSE_READ, reg, NULL, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    case WDR_AUTO: {
        if (arr_num != 0) {
            if (arr_num != MAX_ENTRY_NUM_AE_SYS_GAIN_AUTO) ret = -1;
            else ret = DSP2_WDR_Auto_Parse(DSP2_PARSE_WRITE, argv_reg, array, ret_string);
        } else {
            ret = DSP2_WDR_Auto_Parse(DSP2_PARSE_READ, argv_reg, NULL, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    case WDR_REG: {
        sprintf(reg_in, argv_reg);
        reg_type = parseToolReg((char*)&reg_in, (char*)&reg);
        if (arr_num != 0) {
            ret = DSP2_WDR_Parse(reg_type, DSP2_PARSE_WRITE, reg, array[0], ret_string);
        } else {
            ret = DSP2_WDR_Parse(reg_type, DSP2_PARSE_READ, reg, NULL, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    case WDR_ARRAY: {
        if (arr_num != 0) {
            ret = DSP2_WDR_Array_Parse(DSP2_PARSE_WRITE, argv_reg, array, ret_string);
        } else {
            ret = DSP2_WDR_Array_Parse(DSP2_PARSE_READ, argv_reg, NULL, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    case SAT_AUTO: {
        if (arr_num != 0) {
            if (arr_num != MAX_ENTRY_NUM_AE_ISO_AUTO) ret = -1;
            else ret = DSP2_SAT_Auto_Parse(DSP2_PARSE_WRITE, argv_reg, array, ret_string);
        } else {
            ret = DSP2_SAT_Auto_Parse(DSP2_PARSE_READ, argv_reg, NULL, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    case SAT_REG: {
        sprintf(reg_in, argv_reg);
        reg_type = parseToolReg((char*)&reg_in, (char*)&reg);
        if (arr_num != 0) {
            ret = DSP2_SAT_Parse(reg_type, DSP2_PARSE_WRITE, reg, array[0], ret_string);
        } else {
            ret = DSP2_SAT_Parse(reg_type, DSP2_PARSE_READ, reg, NULL, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    case NR_AUTO: {
        if (arr_num != 0) {
            if (arr_num != MAX_ENTRY_NUM_AE_ISO_AUTO) ret = -1;
            else ret = DSP2_NR_Auto_Parse(DSP2_PARSE_WRITE, argv_reg, array, ret_string);
        } else {
            ret = DSP2_NR_Auto_Parse(DSP2_PARSE_READ, argv_reg, NULL, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    case NR_REG: {
        sprintf(reg_in, argv_reg);
        reg_type = parseToolReg((char*)&reg_in, (char*)&reg);
        if (arr_num != 0) {
            ret = DSP2_NR_Parse(reg_type, DSP2_PARSE_WRITE, reg, array[0], ret_string);
        } else {
            ret = DSP2_NR_Parse(reg_type, DSP2_PARSE_READ, reg, NULL, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    case EE_AUTO: {
        if (arr_num != 0) {
            if (arr_num != MAX_ENTRY_NUM_AE_ISO_AUTO) ret = -1;
            else ret = DSP2_EE_Auto_Parse(DSP2_PARSE_WRITE, argv_reg, array, ret_string);
        } else {
            ret = DSP2_EE_Auto_Parse(DSP2_PARSE_READ, argv_reg, NULL, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    case EE_REG: {
        sprintf(reg_in, argv_reg);
        reg_type = parseToolReg((char*)&reg_in, (char*)&reg);
        if (arr_num != 0) {
            ret = DSP2_EE_Parse(reg_type, DSP2_PARSE_WRITE, reg, array[0], ret_string);
        } else {
            ret = DSP2_EE_Parse(reg_type, DSP2_PARSE_READ, reg, NULL, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    case EE_TBL: {
        sprintf(reg_in, argv_reg);
        reg_type = parseToolReg((char*)&reg_in, (char*)&reg);
        if (arr_num != 0) {
            if (arr_num != BL_EE_LUMA_WEIGHT_NUM) ret = -1;
            else ret = DSP2_EE_Tbl_Parse(reg_type, DSP2_PARSE_WRITE, reg, array, ret_string);
        } else {
            ret = DSP2_EE_Tbl_Parse(reg_type, DSP2_PARSE_READ, reg, NULL, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    case CS_AUTO: {
        if (arr_num != 0) {
            if (arr_num != MAX_ENTRY_NUM_AE_ISO_AUTO) ret = -1;
            else ret = DSP2_CS_Auto_Parse(DSP2_PARSE_WRITE, argv_reg, array, ret_string);
        } else {
            ret = DSP2_CS_Auto_Parse(DSP2_PARSE_READ, argv_reg, NULL, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    case CS_REG: {
        sprintf(reg_in, argv_reg);
        reg_type = parseToolReg((char*)&reg_in, (char*)&reg);
        if (arr_num != 0) {
            ret = DSP2_CS_Parse(reg_type, DSP2_PARSE_WRITE, reg, array[0], ret_string);
        } else {
            ret = DSP2_CS_Parse(reg_type, DSP2_PARSE_READ, reg, NULL, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    case YC_AUTO: {
        if (arr_num != 0) {
            if (arr_num != MAX_ENTRY_NUM_AE_ISO_AUTO) ret = -1;
            else ret = DSP2_YC_Auto_Parse(DSP2_PARSE_WRITE, argv_reg, array, ret_string);
        } else {
            ret = DSP2_YC_Auto_Parse(DSP2_PARSE_READ, argv_reg, NULL, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    case YC_REG: {
        sprintf(reg_in, argv_reg);
        reg_type = parseToolReg((char*)&reg_in, (char*)&reg);
        if (arr_num != 0) {
            ret = DSP2_YC_Parse(reg_type, DSP2_PARSE_WRITE, reg, array[0], ret_string);
        } else {
            ret = DSP2_YC_Parse(reg_type, DSP2_PARSE_READ, reg, NULL, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    case YUVC_REG: {
        sprintf(reg_in, argv_reg);
        reg_type = parseToolReg((char*)&reg_in, (char*)&reg);
        if (arr_num != 0) {
            ret = DSP2_YUVC_Parse(reg_type, DSP2_PARSE_WRITE, reg, array[0], ret_string);
        } else {
            ret = DSP2_YUVC_Parse(reg_type, DSP2_PARSE_READ, reg, NULL, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    case MODULE_ATTR: {
        if (arr_num != 0) {
            ret = DSP2_MODULE_Attr_Parse(DSP2_PARSE_WRITE, argv_reg, array, ret_string);
        } else {
            ret = DSP2_MODULE_Attr_Parse(DSP2_PARSE_READ, argv_reg, NULL, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    case REG_ADDR: {
        if (arr_num != 0) {
            ret = DSP2_REG_ADDR_Parse(DSP2_PARSE_WRITE, argv_reg, array[0], ret_string);
        } else {
            ret = DSP2_REG_ADDR_Parse(DSP2_PARSE_READ, argv_reg, NULL, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    case REG_SENSOR_ADDR: {
        if (arr_num != 0) {
            ret = DSP2_REG_SENSOR_ADDR_Parse(DSP2_PARSE_WRITE, argv_reg, array[0], ret_string);
        } else {
            ret = DSP2_REG_SENSOR_ADDR_Parse(DSP2_PARSE_READ, argv_reg, NULL, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    default:
       goto FAIL;
    }

    if (argv_val != NULL) {
        free(array);
    }

    return 0;

FAIL:
    memcpy(ret_string, "[NG]\0", sizeof(char) * 5);
    return -1;

}

