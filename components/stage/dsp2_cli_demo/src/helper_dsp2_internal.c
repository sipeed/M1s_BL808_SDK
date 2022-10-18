#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <aos/kernel.h>
#include <cli.h>

#include <bl808_dsp2.h>
#include <bl808_dsp2_wdr.h>
#include <bl_comm_sns.h>
#include <bl_dsp2.h>
#include "helper_dsp2_parse.h"
#include "sensor.h"
#include "hdmi.h"
#include "img_proc.h"
#include "img_param.h"
#include "mm_sensor.h"
#include "mm_dsp2.h"
#include "mm_debug.h"
#include "sample_common.h"
#include "helper_dsp2_internal.h"
#include "ae_algo.h"
#include "awb_algo.h"
#include "firmware_bnr.h"
#include "img_peripheral_ctrl.h"
#include "mm_system.h"


#include "bl_dsp2.h"
#include "api_ae.h"
#include "api_awb.h"

#define MAX_PORT_NUM        (4)
#define MAX_CHANN_NUM       (2)
#define HDMI_PORT_ID        (1)

static int dsp2_ctrl(void);
static int load_reg(uint32_t *addr);
static int hdmi_ctrl(int ctrl_type);
static int dsp2_api_start(void);
static int dsp2_api_pause(void);
static int dsp2_api_resume(void);

enum numeric_short_options {
    SENSOR_INPUT = 1000,

    START,
    PAUSE,
    RESUME,
    
    RAW_FILE_INPUT,
    IMG_DUMP_ADDR,
    IMG_DUMP_SIZE,
    IR_CUT_ENABLE,
    GET_RESOLUTION,
    GET_SENSOR_NAME,
    GET_BLACK_LEVEL,
    GET_BAYER_PATTERN,

    GET_AE_SUM,
    Get_AE_HIST_SUM_Y,
    Get_AE_HIST_SUM_BAYER,

    GET_AWB3_CONF,
    GET_AWB3_SUM,
    GET_AWB3_HIST,

    SET_IR_LED_FREQ,
    SET_IR_LED_DUTY,
    IR_LED_ENABLE,

    SENSOR_REG,
    SYS_REG,
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
    AF_REG,
    DG_REG,
    CCM_AUTO,
    CCM_REG,
    CCM_COEF,
    GAMMA_AUTO,
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


    //ATTR
    MODULE_ATTR,
    REG_ADDR,
    REG_SENSOR_ADDR,

    DUMP_NODE,
};

struct helper_dsp2_internal_property {
    int load_auto_inited;
    int dsp2_inited;
    int dsp2_runed;
    int dsp2_chann_id;
    uint32_t sensor_width;
    uint32_t sensor_height;
    MMDSP2YuvFrame yuv_frm[MAX_CHANN_NUM];
};

static struct helper_dsp2_internal_property helper_preperty = {
    .load_auto_inited = 0,
    .dsp2_inited = 0,
};

static int dsp2fw_init(bool is_virtual, const VirtualSensorInfo *virtSnsInfo)
{
    int ret;
    MM_DBG_EnableVirtualSensor(is_virtual, virtSnsInfo);
    ret = sample_system_init();
    if (-1 == ret) {
        return -1;
    }

    MMSensorAttr snsAttr;
    MM_Sensor_GetChnAttr(0, &snsAttr);
    helper_preperty.sensor_width = snsAttr.picWidth;
    helper_preperty.sensor_height = snsAttr.picHeight;

    helper_preperty.dsp2_inited = 1;
    helper_preperty.dsp2_runed = 1;
    return 0;
}

static void show_usage(void)
{
    aos_cli_printf("dsp2 [options]\r\n");
    aos_cli_printf("--sensor-input Select current sensor as input\r\n");
    aos_cli_printf("--raw-file-input [sensor_name] Bind the IQ param to the specific sensor model \r\n");
    aos_cli_printf("-i [resolution] Set DSP2 input resolution \r\n");
    aos_cli_printf("-o [resolution] Set DSP2 output resolution for channel 0\r\n");
    aos_cli_printf("-O [resolution] Set DSP2 output resolution for channel 1\r\n");
    aos_cli_printf("-H [1/0] Turn on/off HDMI \r\n");
    aos_cli_printf("-n [1/0] Set day/night mode. 1 - night mode, 0 - day mode\r\n");
    aos_cli_printf("-c [dsp2_chann_id] Assign the specific port for image dump. Must be 0 or 1 \r\n");
    aos_cli_printf("-S [src_id] Set image source for the current port. Must be 0~31 \r\n");
    aos_cli_printf("-s Start dumping image \r\n");
    aos_cli_printf("-e Stop dumping image \r\n");
    aos_cli_printf("-r refresh image force \r\n");
    aos_cli_printf("--img-dump-addr Get address of dumped image \r\n");
    aos_cli_printf("--img-dump-size Get size of dumped image \r\n");
    aos_cli_printf("--set/get-dgain Set DSP2 digital gain \r\n");
    aos_cli_printf("--img-dump-addr Get address of dumped image \r\n");
    aos_cli_printf("--set-awb-algo set/get awb algo. 0: grey_world; 1: awb1; 2: awb2\r\n");
    aos_cli_printf("--set/get-awb Set/get awb gain\r\n");
    aos_cli_printf("--enb-cs Enable/disable CS1\r\n");
    aos_cli_printf("--set/get-cs Set/get CS config\r\n");
    aos_cli_printf("--enb-ee Enable/disable EE\r\n");
    aos_cli_printf("--enb-ee-ovrsht Enable/disable EE overshoot \r\n");
    aos_cli_printf("--set/get-ee-thr Set/get EE thresh \r\n");
    aos_cli_printf("--set/get-ee-str Set/get EE strenth \r\n");
    aos_cli_printf("--set/get-ee-luma-wgt Set/get EE luma weight \r\n");
    aos_cli_printf("--enb-gamma Enable gamma curve \r\n");
    aos_cli_printf("--get-gamma Get gamma curve \r\n");
}

static void dsp2_cmd(char *buf, int len, int argc, char **argv)
{
    VirtualSensorInfo virt_sns_info;
    MMDSP2FrmSrcAttr frmsrc_attr;
    MMDSP2Position dsp2_pos;
    BL_Img_Size_T win;
    int ch;
    uint32_t value = 0;
    int ret = -1;
    optind = 0;

    static struct option long_options[] =
    {
        {"sensor-input",        no_argument,       0, SENSOR_INPUT},
        
        {"start",        no_argument,       0, START},
        {"pause",        no_argument,       0, PAUSE},
        {"resume",        no_argument,       0, RESUME},
        
        {"raw-file-input",      required_argument, 0, RAW_FILE_INPUT},
        {"in-size",             required_argument, 0, 'i'},
        {"out-size",            required_argument, 0, 'o'},
        {"out-size-sub",        required_argument, 0, 'O'},
        {"get-resolution",      required_argument, 0, GET_RESOLUTION},
        {"get-sensor-name",     no_argument,       0, GET_SENSOR_NAME},
        {"get-black-level",     no_argument,       0, GET_BLACK_LEVEL},
        {"get-bayer-pattern",   no_argument,       0, GET_BAYER_PATTERN},
        {"chann-id",            required_argument, 0, 'c'},
        {"fps",                 required_argument, 0, 'f'},
        {"img-dump-src",        required_argument, 0, 'S'},
        {"img-dump-start",      no_argument,       0, 's'},
        {"img-dump-end",        no_argument,       0, 'e'},
        {"img-dump-addr",       no_argument,       0, IMG_DUMP_ADDR},
        {"img-dump-size",       no_argument,       0, IMG_DUMP_SIZE},
        {"hdmi",                required_argument, 0, 'H'},
        {"ir-cut",              required_argument, 0, IR_CUT_ENABLE},
        {"night-mode",          required_argument, 0, 'n'},
        {"refresh",             no_argument,       0, 'r'},
        {"get-ae-sum",          no_argument,       0, GET_AE_SUM},
        {"get-ae-hist-sum-y",   no_argument,       0, Get_AE_HIST_SUM_Y},
        {"get-ae-hist-sum-bayer",   no_argument,   0, Get_AE_HIST_SUM_BAYER},
        {"get-awb3-conf",       no_argument,       0, GET_AWB3_CONF},
        {"get-awb3-sum",        no_argument,       0, GET_AWB3_SUM},
        {"get-awb3-hist",       no_argument,       0, GET_AWB3_HIST},
        {"set-ir-led-freq",     required_argument, 0, SET_IR_LED_FREQ},
        {"set-ir-led-duty",     required_argument, 0, SET_IR_LED_DUTY},
        {"ir-led-en",           required_argument, 0, IR_LED_ENABLE},

        {"sensor-reg",            required_argument, 0, SENSOR_REG},
        {"sys-reg",               required_argument, 0, SYS_REG},
        {"module-state",          required_argument, 0, MODULE_STATE},
        {"ae-auto",               required_argument, 0, AE_AUTO},
        {"ae-reg",                required_argument, 0, AE_REG},
        {"ae-array",              required_argument, 0, AE_ARRAY},
        {"awb-auto",              required_argument, 0, AWB_AUTO},
        {"awb-stats-conf",        required_argument, 0, AWB_STATS_CONF},
        {"awb-cal",               required_argument, 0, AWB_CAL},
        {"awb-reg",               required_argument, 0, AWB_REG},
        {"awb-array",             required_argument, 0, AWB_ARRAY},
        {"blc-cal",               required_argument, 0, BLC_CAL},
        {"blc-auto",              required_argument, 0, BLC_AUTO},
        {"blc-reg",               required_argument, 0, BLC_REG},
        {"dpc-cal",               required_argument, 0, DPC_CAL},
        {"dpc-auto",              required_argument, 0, DPC_AUTO},
        {"dpc-reg",               required_argument, 0, DPC_REG},
        {"bnr-auto",              required_argument, 0, BNR_AUTO},
        {"bnr-reg",               required_argument, 0, BNR_REG},
        {"lsc-auto",              required_argument, 0, LSC_AUTO},
        {"lsc-reg",               required_argument, 0, LSC_REG},
        {"lsc-coef",              required_argument, 0, LSC_COEF},
        {"af-reg",                required_argument, 0, AF_REG},
        {"dg-reg",                required_argument, 0, DG_REG},
        {"ccm-auto",              required_argument, 0, CCM_AUTO},
        {"ccm-reg",               required_argument, 0, CCM_REG},
        {"ccm-coef",              required_argument, 0, CCM_COEF},
        {"gamma-auto",            required_argument, 0, GAMMA_AUTO},
        {"gamma-reg",             required_argument, 0, GAMMA_REG},
        {"gamma-curve",           required_argument, 0, GAMMA_CURVE},
        {"wdr-auto",              required_argument, 0, WDR_AUTO},
        {"wdr-reg",               required_argument, 0, WDR_REG},
        {"wdr-array",             required_argument, 0, WDR_ARRAY},
        {"saturation-auto",       required_argument, 0, SAT_AUTO},
        {"saturation-reg",        required_argument, 0, SAT_REG},
        {"nr-auto",               required_argument, 0, NR_AUTO},
        {"nr-reg",                required_argument, 0, NR_REG},
        {"ee-auto",               required_argument, 0, EE_AUTO},
        {"ee-reg",                required_argument, 0, EE_REG},
        {"ee-tbl",                required_argument, 0, EE_TBL},
        {"cs-auto",               required_argument, 0, CS_AUTO},
        {"cs-reg",                required_argument, 0, CS_REG},
        {"yc-auto",               required_argument, 0, YC_AUTO},
        {"yc-reg",                required_argument, 0, YC_REG},

        //ATTR
        {"module-attr",           required_argument, 0, MODULE_ATTR},
        {"reg-addr",              required_argument, 0, REG_ADDR},
        {"reg-sensor_addr",       required_argument, 0, REG_SENSOR_ADDR},

        {"dump_node",             required_argument  , 0, DUMP_NODE},
        {0, 0, 0, 0}
    };

    if (1 == argc) {
        dsp2_ctrl();
        return;
    }

    while ((ch = getopt_long (argc, argv, "i:c:o:O:f:S:sren:h", long_options, NULL)) != -1) {
        switch (ch)
        {
         case START:
            dsp2_api_start();
            break;
        case PAUSE:
            dsp2_api_pause();
            break;
        case RESUME:
            dsp2_api_resume();
            break;
        case SENSOR_INPUT:
            dsp2fw_init(false, NULL);
            break;

        case RAW_FILE_INPUT:
            virt_sns_info.width = win.width;
            virt_sns_info.height = win.height;

            strncpy(virt_sns_info.sensor_name, optarg, sizeof(virt_sns_info.sensor_name) - 1);
            dsp2fw_init(true, &virt_sns_info);
            break;

        case 'i':
            if (utils_get_resolution_param(optarg, &(win.width), &(win.height)) == 0) {
                BL_LOGI("set input resolution %dx%d\r\n", win.width, win.height);
                bl_dsp2_set_input_resolution(&win);
            } else {
                goto FAIL;
            }
            break;

        case 'o':
            if (utils_get_resolution_param(optarg, &(win.width), &(win.height)) == 0) {
                BL_LOGI("set output resolution %dx%d\r\n", win.width, win.height);

                MM_DSP2_GetFrameSrcChnAttr(0, &frmsrc_attr);
                frmsrc_attr.picWidth = win.width;
                frmsrc_attr.picHeight = win.height;
                frmsrc_attr.dsp2Position = DSP2_POSITION_SCALER_A;
                MM_DSP2_SetFrameSrcChnAttr(0, &frmsrc_attr);

            } else {
                goto FAIL;
            }
            break;

        case 'O':
            if (utils_get_resolution_param(optarg, &(win.width), &(win.height)) == 0) {
                BL_LOGI("set output resolution %dx%d\r\n", win.width, win.height);

                MM_DSP2_GetFrameSrcChnAttr(1, &frmsrc_attr);
                frmsrc_attr.picWidth = win.width;
                frmsrc_attr.picHeight = win.height;
                frmsrc_attr.dsp2Position = DSP2_POSITION_SCALER_B;
                MM_DSP2_SetFrameSrcChnAttr(1, &frmsrc_attr);
            } else {
                goto FAIL;
            }
            break;

        case 'c':
            helper_preperty.dsp2_chann_id = atoi(optarg);
            break;

        case 'f':
            value = atoi(optarg);
            sample_set_chann_frame_rate(helper_preperty.dsp2_chann_id, value);
            break;

        case 'S':
            dsp2_pos = atoi(optarg);

            MM_DSP2_GetFrameSrcChnAttr(helper_preperty.dsp2_chann_id, &frmsrc_attr);
            frmsrc_attr.dsp2Position = dsp2_pos;
            // if pos over dsp2 out, may use the scaler resolution
            if (dsp2_pos <= DSP2_POSITION_DSP2_OUTPUT \
                || dsp2_pos == DSP2_POSITION_SCALER_A || dsp2_pos == DSP2_POSITION_OSD_A || dsp2_pos == DSP2_POSITION_ADJ_A \
                || dsp2_pos == DSP2_POSITION_SCALER_C || dsp2_pos == DSP2_POSITION_OSD_C || dsp2_pos == DSP2_POSITION_ADJ_C) {
                frmsrc_attr.picWidth = helper_preperty.sensor_width;
                frmsrc_attr.picHeight = helper_preperty.sensor_height;
            }
            MM_DSP2_SetFrameSrcChnAttr(helper_preperty.dsp2_chann_id, &frmsrc_attr);
            break;

        case 's':
            if (0 == helper_preperty.dsp2_inited) goto FAIL;
            MM_DSP2_StartRecvPic(helper_preperty.dsp2_chann_id, PIX_FMT_DATA16);
            MM_DSP2_GetOnePicture(helper_preperty.dsp2_chann_id, &helper_preperty.yuv_frm[helper_preperty.dsp2_chann_id]);
            MM_DSP2_StopRecvPic(helper_preperty.dsp2_chann_id);
            break;

        case 'e':
            /* Deprecated */
            break;

        case 'H':
            ret = hdmi_ctrl(atoi(optarg));
            if (ret == -1) goto FAIL;
            break;

        case IR_CUT_ENABLE:
            if (atoi(optarg) == 1) {
                ir_cut_switch(true);
            } else {
                ir_cut_switch(false);
            }
            break;

        case 'n':
            if (atoi(optarg) == 1) {
                imgproc_night_mode_enable(true);
            } else {
                imgproc_night_mode_enable(false);
            }
            ae_force_refresh();
            break;

        case 'r':
            imgproc_update_force();
            break;

        case IMG_DUMP_ADDR:
            value = (uint32_t)helper_preperty.yuv_frm[helper_preperty.dsp2_chann_id].frameStartAddr;
            aos_cli_printf("[OK] IMG_DUMP_ADDR: %u\r\n", value);
            break;

        case IMG_DUMP_SIZE:
            value = helper_preperty.yuv_frm[helper_preperty.dsp2_chann_id].frameSize;
            aos_cli_printf("[OK] IMG_DUMP_SIZE: %u\r\n", value);
            break;

        case GET_RESOLUTION:
            if (0 == atoi(optarg)) {
                if (bl_dsp2_get_input_resolution(&win) == 0) {
                    helper_preperty.sensor_width = win.width;
                    helper_preperty.sensor_height = win.height;
                    aos_cli_printf("[OK] RESOLUTION: %ux%u\r\n", win.width, win.height);
                } else {
                    goto FAIL;
                }
            }
            else {
                if (bl_dsp2_get_out_resolution(&win) == 0) {
                    helper_preperty.sensor_width = win.width;
                    helper_preperty.sensor_height = win.height;
                    aos_cli_printf("[OK] RESOLUTION: %ux%u\r\n", win.width, win.height);
                } else {
                    goto FAIL;
                }
            }

            break;

        case GET_SENSOR_NAME: {
            const char* sensor_name;
            MM_DBG_GetSensorName(&sensor_name);
            aos_cli_printf("[OK] SENSOR_NAME: %s\r\n", sensor_name);
        }
        break;

        case GET_BLACK_LEVEL: {
            DSP2_CLAMP_S clamp;
            DSP2_Get_BLC(&clamp);
            // if black level rggb not equal oneday, open it
            // aos_cli_printf("[OK] %d,%d,%d,%d\r\n", clamp.clamp_r, clamp.clamp_gr, clamp.clamp_gb, clamp.clamp_b);
            aos_cli_printf("[OK] BLACK_LEVEL: %d\r\n", clamp.clamp_gr);
        }
        break;

        case GET_BAYER_PATTERN:
            MM_DBG_GetSensorBayerPattern(&value);
            aos_cli_printf("[OK] BAYER_PATTERN: %s\r\n", bayer_pattern_str_arr[value]);
        break;
        
        case GET_AE_SUM: {
            int i;
            uint32_t luma;
            uint32_t luma_table[AE_STATS_GRID_NUM] = {0};
            for (i = 0; i < AE_STATS_GRID_NUM; i++) {
                DSP2_Get_AE_Sum(i, AE_GRID_DATA_Y, &luma);
                luma_table[i] = luma;
            }

            aos_cli_printf("[OK] GET_AE_SUM: \r\n");
            for (i = 0; i < AE_STATS_GRID_NUM; i++) {
                if ((i % AE_STATS_GRID_NUM_X) == 0){
                    aos_cli_printf("\r\n");
                    }
                aos_cli_printf("%4.d,", luma_table[i]);
            }
            break;
        }
        case Get_AE_HIST_SUM_Y: {
    #if 0
            DSP2_AE_Array_Parse(DSP2_PARSE_READ, "hist_y", NULL, NULL);
            break;
    #else
            AE_HIST_MODE_TYPE_E mode;
            DSP2_Get_AE_Hist_Mode(&mode);
            if(mode != AE_HIST_MODE_Y) {
                aos_cli_printf("Please check hist mode, it's not AE_HIST_MODE_Y.");
                goto FAIL;
            }

            int i;
            uint32_t hist_y_sum[DSP2_AE_HIST_Y_BIN_NUM] = {0};
            DSP2_Get_AE_Hist_SUM_Y(hist_y_sum);

            aos_cli_printf("[OK] Get_AE_HIST_SUM_Y:\r\n");
            for (i = 0; i < DSP2_AE_HIST_Y_BIN_NUM; i++) {
                if ((i % 16) == 0){
                    aos_cli_printf("\r\n");
                    }
                aos_cli_printf("%4.d,", hist_y_sum[i]);
            }
            break;
    #endif
        }
        case Get_AE_HIST_SUM_BAYER: {
    #if 0
            DSP2_AE_Array_Parse(DSP2_PARSE_READ, "hist_bayer", NULL, NULL);
            break;
    #else
            AE_HIST_MODE_TYPE_E mode;
            DSP2_Get_AE_Hist_Mode(&mode);
            if(mode != AE_HIST_MODE_BAYER) {
                aos_cli_printf("Please check hist mode, it's not AE_HIST_MODE_BAYER.");
                goto FAIL;
            }

            int i, j;
            char bayer[4][2] = {"r","gr","gb","b"};
            uint32_t hist_sum[4][DSP2_AE_HIST_BAYER_BIN_NUM] = {0};

            DSP2_Get_AE_Hist_SUM_Bayer(hist_sum[0], hist_sum[1], hist_sum[2], hist_sum[3]);

            aos_cli_printf("[OK] Get_AE_HIST_SUM_BAYER:\r\n");
            for (j = 0; j < 4; j++){
                aos_cli_printf("\r\nbayer %s:", bayer[j]);
                for (i = 0; i < DSP2_AE_HIST_BAYER_BIN_NUM; i++) {
                    if ((i % 16) == 0){
                        aos_cli_printf("\r\n");
                        }
                    aos_cli_printf("%4.d,", hist_sum[j][i]);
                }
            }
            break;
    #endif
        }
        case GET_AWB3_CONF: {
            int i,j;
            dsp2_awb3_stats_conf_t awb_stats_conf;
            DSP2_Get_AWB3_Stats_Conf(&awb_stats_conf);

            aos_cli_printf("[OK] GET_AWB3_CONF: %d\r\n");
            // awb window
            aos_cli_printf("awb window: %d,%d,%d,%d\r\n",
             awb_stats_conf.stat_x_min,awb_stats_conf.stat_x_max,
             awb_stats_conf.stat_y_min,awb_stats_conf.stat_y_max);

            // weight_ratio
            aos_cli_printf("weight_ratio: %d,%d\r\n",
                awb_stats_conf.weight_ratio_en,
                awb_stats_conf.weight_ratio_gain);

            // y coeff
            aos_cli_printf("y coeff:  %d,%d,%d\r\n",
                awb_stats_conf.y_r_coeff,
                awb_stats_conf.y_g_coeff,
                awb_stats_conf.y_b_coeff);
            //weight_y
            aos_cli_printf("weight_y:  %d,%d,%d\r\n",
                awb_stats_conf.weight_y_use_g,
                awb_stats_conf.weight_y_en,
                awb_stats_conf.weight_y_gain);

            aos_cli_printf("weight_y: \r\n");
            for (j = 0; j < DSP2_AWB3_WEIGHT_NUM; j++) {
                for (i = 0; i < DSP2_AWB3_WEIGHT_NUM; i++) {
                    if (i== 0) aos_cli_printf("\r\n");
                    aos_cli_printf("%4.d,", awb_stats_conf.weight_y[j][i]);
                }
            }
            aos_cli_printf("\r\n");

            //
            aos_cli_printf(":  %d,%d,%d,%d,%d,%d,%d\r\n",
                awb_stats_conf.count_zero_weight,
                awb_stats_conf.hist_y_use_g,
                awb_stats_conf.bin_y_level,
                awb_stats_conf.bin_ratio_level,
                awb_stats_conf.bin_clip_en,
                awb_stats_conf.bin_pixel_clip,
                awb_stats_conf.bin_mode);

            //ink
            aos_cli_printf("ink:  %d,%d\r\n",
                awb_stats_conf.ink_type,
                awb_stats_conf.ink_gain);

            // calibration
            aos_cli_printf("cal:  %d,%d,%d,%d,%d,%d,%d\r\n",
                awb_stats_conf.g_divisor,
                awb_stats_conf.r_ratio_ofst,
                awb_stats_conf.b_ratio_ofst,
                awb_stats_conf.r_ratio_mult,
                awb_stats_conf.b_ratio_mult,
                awb_stats_conf.ratio_sum_min,
                awb_stats_conf.ratio_sum_max);

            aos_cli_printf("weight_ratio: \r\n");
            for (j = 0; j < DSP2_AWB3_WEIGHT_NUM; j++) {
                for (i = 0; i < DSP2_AWB3_WEIGHT_NUM; i++) {
                    if (i== 0) aos_cli_printf("\r\n");
                    aos_cli_printf("%4.d,", awb_stats_conf.weight_ratio[j][i]);
                }
            }
            aos_cli_printf("\r\n");
            break;
        }
        case GET_AWB3_SUM: {
            dsp2_awb3_sum_t mode;
            if (-1 == DSP2_Get_AWB3_Sum(&mode)) {
                BL_LOGI("get awb3 bin mode error!\r\n");
                goto FAIL;
            }
            aos_cli_printf("[OK] sum %d %d %d\r\n",
                mode.r_sum, // r, ping-pong, 32'b, = PIXEL_NUM_BW + PIXEL_BW
                mode.g_sum, // r, ping-pong, 32'b, = PIXEL_NUM_BW + PIXEL_BW
                mode.b_sum // r, ping-pong, 32'b, = PIXEL_NUM_BW + PIXEL_BW
                );
            aos_cli_printf("[OK] sum_hex %d %d %d %d\r\n",
                mode.r_sum_hex, // r, ping-pong, 32'b, = PIXEL_NUM_BW + PIXEL_BW
                mode.g_sum_hex, // r, ping-pong, 32'b, = PIXEL_NUM_BW + PIXEL_BW
                mode.b_sum_hex, // r, ping-pong, 32'b, = PIXEL_NUM_BW + PIXEL_BW
                mode.pixel_hex // r, ping-pong, 20'b, = PIXEL_NUM_BW
                );
            aos_cli_printf("[OK] hex_y %lld %lld %d %d\r\n",
                mode.r_ratio_hex_y, // r, ping-pong, 40'b, = PIXEL_NUM_BW + WEIGHT_BW + RATIO_BW
                mode.b_ratio_hex_y, // r, ping-pong, 40'b, = PIXEL_NUM_BW + WEIGHT_BW + RATIO_BW
                mode.weight_hex_y, // r, ping-pong, 28'b, = PIXEL_NUM_BW + WEIGHT_BW
                mode.pixel_hex_y // r, ping-pong, 20'b, = PIXEL_NUM_BW
                );
            aos_cli_printf("[OK] hist %lld %lld %d %d\r\n",
                mode.r_ratio_hist, // r, ping-pong, 40'b, = PIXEL_NUM_BW + WEIGHT_BW + RATIO_BW
                mode.b_ratio_hist, // r, ping-pong, 40'b, = PIXEL_NUM_BW + WEIGHT_BW + RATIO_BW
                mode.weight_hist, // r, ping-pong, 28'b, = PIXEL_NUM_BW + WEIGHT_BW
                mode.pixel_hist // r, ping-pong, 20'b, = PIXEL_NUM_BW
                );
            aos_cli_printf("[OK] hist_clip %lld %lld %d %d\r\n",
                mode.r_ratio_hist_clip, // r, ping-pong, 40'b, = PIXEL_NUM_BW + WEIGHT_BW + RATIO_BW
                mode.b_ratio_hist_clip, // r, ping-pong, 40'b, = PIXEL_NUM_BW + WEIGHT_BW + RATIO_BW
                mode.weight_hist_clip, // r, ping-pong, 28'b, = PIXEL_NUM_BW + WEIGHT_BW
                mode.pixel_hist_clip // r, ping-pong, 20'b, = PIXEL_NUM_BW
                );
            break;
        }
        case GET_AWB3_HIST: {
    #if 0
            DSP2_AWB_Array_Parse(DSP2_PARSE_READ, "hist", NULL, NULL);
            break;
    #else
            int i;
            int bucket_num;
            int *hist_y_sum;
            uint64_t val_l = 0, val_u = 0, r_ratio = 0, b_ratio = 0;
            uint32_t bucket[4] = {0}, weight = 0, pixel= 0;

            DSP2_Get_AWB3_Hist_Bin_Num((uint32_t *)&bucket_num);
            hist_y_sum = malloc(sizeof(int) * bucket_num * 4);
            DSP2_Get_AWB3_Hist((uint32_t *)hist_y_sum);

            aos_cli_printf("[OK] Get_AWB_HIST:\r\n");
            aos_cli_printf("bucket_num: %d\r\n", bucket_num);
            for (i = 0; i < bucket_num; i++) {
                memcpy(bucket, &hist_y_sum[i*4], sizeof(int) * 4);

                val_u = bucket[3] << 8;
                val_l = bucket[2] >> 24;
                r_ratio = val_u + val_l;

                val_u = (bucket[2] & (0x00ffffff)) << 16;
                val_l = bucket[1] >> 16 ;
                b_ratio = val_u + val_l;

                val_u = (bucket[1] & (0x0000ffff)) << 12;
                val_l = bucket[0] >> 20 ;
                weight = val_u + val_l;

                val_u = bucket[0] & (0x000fffff);
                pixel = val_u;

                if (i<bucket_num){
                    //aos_cli_printf("%d: 0x%08x, 0x%08x, 0x%08x, 0x%08x\r\n", i, hist_y_sum[i*4+3], hist_y_sum[i*4+2], hist_y_sum[i*4+1], hist_y_sum[i*4+0]);
                    //aos_cli_printf("%d: 0x%08x, 0x%08x, 0x%08x, 0x%08x\r\n", i, bucket[3], bucket[2], bucket[1], bucket[0]);
                    aos_cli_printf("%d: %ld, %ld, %d, %d,\r\n", i, r_ratio, b_ratio, weight, pixel);
                    //aos_cli_printf("\r\n");
                }
            }
            free(hist_y_sum);
            break;
    #endif

        }
        case SET_IR_LED_FREQ:{
            int freq = atoi(optarg);
            ir_led_set_freq(freq);
            aos_cli_printf("[OK] ir_led_freq: %d\r\n", freq);
            break;
        }
        case SET_IR_LED_DUTY:{
            float duty = atof(optarg);
            ir_led_set_duty(duty);
            aos_cli_printf("[OK] ir_led_duty: %f\r\n", duty);
            break;
        }
        case IR_LED_ENABLE:{
            if (atoi(optarg) == 1) {
                ir_led_en(true);
                aos_cli_printf("[OK] IR_LED on\r\n");
            } else {
                ir_led_en(false);
                aos_cli_printf("[OK] IR_LED off\r\n");
            }
            break;
        }
        case DUMP_NODE: {
#define DUMP_NUM 4
            int i;
            MMDSP2YuvFrame frame[DUMP_NUM];
            uint8_t *buffer[DUMP_NUM];
            printf("======================================");
            value = atoi(optarg);

            for (i = 0; i < DUMP_NUM; i++) {
                buffer[i] = BL_MallocDMA(1, 1920 * 1080 * 2);
                memset(buffer[i], 0, sizeof(uint8_t) * 1920 * 1080 * 2);
            }

            sample_system_init();

            for (i = 0; i < DUMP_NUM; i++) {
                aos_cli_printf("buffer 0x%x 0x%x \r\n", (uint32_t)buffer[i], (uint32_t)(buffer[i] + (sizeof(uint8_t) * 1920 * 1080 * 2)));
                printf("buffer 0x%x 0x%x \r\n", (uint32_t)buffer[i], (uint32_t)(buffer[i] + (sizeof(uint8_t) * 1920 * 1080 * 2)));
                printf("[N:%d][F:%d] start dump\r\n", value, i);
                //is_node_start_dump(0, PIX_FMT_DATA16, value, buffer[i]);
                MM_DSP2_GetOnePicture(0, &frame[i]);
                MM_DSP2_StopRecvPic(0);
                printf("[N:%d][F:%d] end dump\r\n", value, i);
            }

            break;
        }
        case SENSOR_REG:
        case SYS_REG:
        case MODULE_STATE:
        case AE_AUTO:
        case AE_REG:
        case AE_ARRAY:
        case AWB_AUTO:
        case AWB_STATS_CONF:
        case AWB_CAL:
        case AWB_REG:
        case AWB_ARRAY:
        case BLC_CAL:
        case BLC_AUTO:
        case BLC_REG:
        case DPC_CAL:
        case DPC_AUTO:
        case DPC_REG:
        case BNR_AUTO:
        case BNR_REG:
        case LSC_AUTO:
        case LSC_REG:
        case LSC_COEF:
        case AF_REG:
        case DG_REG:
        case CCM_AUTO:
        case CCM_REG:
        case CCM_COEF:
        case GAMMA_AUTO:
        case GAMMA_REG:
        case GAMMA_CURVE:
        case WDR_AUTO:
        case WDR_REG:
        case WDR_ARRAY:
        case SAT_AUTO:
        case SAT_REG:
        case NR_AUTO:
        case NR_REG:
        case EE_AUTO:
        case EE_REG:
        case EE_TBL:
        case CS_AUTO:
        case CS_REG:
        case MODULE_ATTR:
        case REG_ADDR:
        case REG_SENSOR_ADDR:
        case YC_AUTO:
        case YC_REG:{
            const char *format = "--%s";
            char module[32] = {'\0'};
            char argv_reg[32] = {'\0'};
            char argv_val[512] = {'\0'};
            int payload_len_in = 0;
            char ret_string[512] = {'\0'};
            int ret = -1;

            if(sscanf(argv[optind - 2], format, module) != 1) goto FAIL;
            sprintf(argv_reg, "%s", argv[optind - 1]);
            sprintf(argv_val, "%s", argv[optind]);
            payload_len_in = strlen(argv_val);

            //aos_cli_printf("cli avgv  module %s, argv_reg %s, argv_val %s\r\n", argv[optind - 2], argv[optind - 1], argv[optind]);
            //aos_cli_printf("cli  module %s, argv_reg %s, argv_val %s\r\n", module, argv_reg, argv_val);

            ret = parse_dsp2_cmd(module, argv_reg, argv_val, payload_len_in, ret_string);
            if (ret == -1) goto FAIL;
            else aos_cli_printf("[OK] %s\r\n", ret_string);
            break;
        }
        case 'h':
        default:
            show_usage();
            goto FAIL;
        }
    }
    aos_cli_printf("[OK] \r\n");
    return;

FAIL:
    aos_cli_printf("[NG] \r\n");
    return;
}

static void load_api_reg(void)
{
    BL_IMG_PARAM_SW_BIN_DESC_T pstDefaultParam;

    const char name[16] = "GC2053";
    memcpy(pstDefaultParam.name, name, sizeof(char) * 16);
    const img_param_state_container_t   state_tbl = {
    .state[DSP2_ADJ_AE]                = ENABLE,
    .state[DSP2_ADJ_AWB]               = ENABLE,
    .state[DSP2_ADJ_BLC]               = ENABLE,
    .state[DSP2_ADJ_DPC]               = ENABLE,//DISABLE,
    .state[DSP2_ADJ_BNR]               = ENABLE,
    .state[DSP2_ADJ_LSC]               = ENABLE,//DISABLE,
    .state[DSP2_ADJ_CCM]               = ENABLE,
    .state[DSP2_ADJ_GAMMA]             = ENABLE,
    .state[DSP2_ADJ_WDR]               = ENABLE,
    .state[DSP2_ADJ_SATURATION]        = ENABLE,
    .state[DSP2_ADJ_YC]                = ENABLE,
    .state[DSP2_ADJ_NR]                = ENABLE,
    .state[DSP2_ADJ_EE]                = ENABLE,
    .state[DSP2_ADJ_CS]                = ENABLE,
    };
    memcpy(&pstDefaultParam.state_tbl, &state_tbl, sizeof(img_param_state_container_t));

    const ae_container_sw_t             ae_tbl = {
        .container = {
            {2,},  //[0]:-54 db
            {50,},  //[1]:-48 db
            {50,},  //[2]:-42 db
            {50,},  //[3]:-36 db
            {50,},  //[4]:-30 db
            {50,},  //[5]:-24 db
            {50,},  //[6]:-18 db
            {50,},  //[7]:-12 db
            {50,},  //[8]:-6 db
            {50,},  //[9]:0 db
            {50,},  //[10]:6 db
            {50,},  //[11]:12 db
            {50,},  //[12]:18 db
            {50,},  //[13]:24 db
            {50,},  //[14]:30 db
            {50,},  //[15]:36 db
            {50,},  //[16]:42 db
            {50,},  //[17]:48 db
            {1,},  //[18]:54 db
        },
        .metering_tbl = {
            {{ // AE_METERING_AVERAGE
                2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
            }},
            {{ // AE_METERING_CENTER_WEIGHTED
                2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                2, 2, 2, 9, 9, 9, 9, 9, 9, 2, 2, 2,
                2, 2, 2, 9, 9, 9, 9, 9, 9, 2, 2, 2,
                2, 2, 2, 9, 9, 9, 9, 9, 9, 2, 2, 2,
                2, 2, 2, 9, 9, 9, 9, 9, 9, 2, 2, 2,
                2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
            }},
            {{ // AE_METERING_SPOT
                0, 0, 0, 0, 0,  0,  0,  0, 0, 0, 0, 0,
                0, 0, 0, 0, 0,  0,  0,  0, 0, 0, 0, 0,
                0, 0, 0, 0, 0,  0,  0,  0, 0, 0, 0, 0,
                0, 0, 0, 0, 0,  1,  1,  0, 0, 0, 0, 0,
                0, 0, 0, 0, 0,  1,  1,  0, 0, 0, 0, 0,
                0, 0, 0, 0, 0,  0,  0,  0, 0, 0, 0, 0,
                0, 0, 0, 0, 0,  0,  0,  0, 0, 0, 0, 0,
                0, 0, 0, 0, 0,  0,  0,  0, 0, 0, 0, 0
            }},
            {{ // AE_METERING_CUSTOM
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
            }}
        },
        .highlight_weight_conf = { 
            .roi_start = 220, 
            .roi_end = 250,
            .thr = {1000, 2500, 3000, 4000,},
            .highlight_weight = {
                {{2, 255, 255}},  //[0]:-54 db
                {{255, 255, 255}},  //[1]:-48 db
                {{255, 255, 255}},  //[2]:-42 db
                {{255, 255, 255}},  //[3]:-36 db
                {{255, 255, 255}},  //[4]:-30 db
                {{255, 255, 255}},  //[5]:-24 db
                {{255, 255, 255}},  //[6]:-18 db
                {{255, 255, 255}},  //[7]:-12 db
                {{255, 255, 255}},  //[8]:-6 db
                {{255, 255, 255}},  //[9]:0 db
                {{255, 255, 255}},  //[10]:6 db
                {{255, 255, 255}},  //[11]:12 db
                {{255, 255, 255}},  //[12]:18 db
                {{255, 255, 255}},  //[13]:24 db
                {{255, 255, 255}},  //[14]:30 db
                {{255, 255, 255}},  //[15]:36 db
                {{255, 255, 255}},  //[16]:42 db
                {{255, 255, 255}},  //[17]:48 db
                {{1, 1, 1}},  //[18]:54 db
                }
        },
        .metering_mode = 0,
        .speed_level = 3,
    };
    memcpy(&pstDefaultParam.ae_tbl, &ae_tbl, sizeof(ae_container_sw_t));

    static const awb_container_sw_t awb_sw = {
        .preference_gain = {
        {{ {2,4096}, {4096,4096}, {4096,4096} },},  //[0]:-54 db
        {{ {4096,4096}, {4096,4096}, {4096,4096} },},  //[1]:-48 db
        {{ {4096,4096}, {4096,4096}, {4096,4096} },},  //[2]:-42 db
        {{ {4096,4096}, {4096,4096}, {4096,4096} },},  //[3]:-36 db
        {{ {4096,4096}, {4096,4096}, {4096,4096} },},  //[4]:-30 db
        {{ {4096,4096}, {4096,4096}, {4096,4096} },},  //[5]:-24 db
        {{ {4096,4096}, {4096,4096}, {4096,4096} },},  //[6]:-18 db
        {{ {4096,4096}, {4096,4096}, {4096,4096} },},  //[7]:-12 db
        {{ {4096,4096}, {4096,4096}, {4096,4096} },},  //[8]:-6 db
        {{ {4096,4096}, {4096,4096}, {4096,4096} },},  //[9]:0 db
        {{ {4096,4096}, {4096,4096}, {4096,4096} },},  //[10]:6 db
        {{ {4096,4096}, {4096,4096}, {4096,4096} },},  //[11]:12 db
        {{ {4096,4096}, {4096,4096}, {4096,4096} },},  //[12]:18 db
        {{ {4096,4096}, {4096,4096}, {4096,4096} },},  //[13]:24 db
        {{ {4096,4096}, {4096,4096}, {4096,4096} },},  //[14]:30 db
        {{ {4096,4096}, {4096,4096}, {4096,4096} },},  //[15]:36 db
        {{ {4096,4096}, {4096,4096}, {4096,4096} },},  //[16]:42 db
        {{ {4096,4096}, {4096,4096}, {4096,4096} },},  //[17]:48 db
        {{ {4096,4096}, {4096,4096}, {4096,1096} },},  //[18]:54 db
        },
        .speed_level = 2,
    };
    memcpy(&pstDefaultParam.awb_tbl, &awb_sw, sizeof(awb_container_sw_t));
    
    const blc_container_sw_t            blc_tbl = {
        .container = {
        { 2, },      // ISO_100_0DB
        { 256, },      // ISO_200_6DB
        { 256, },      // ISO_400_12DB
        { 256, },      // ISO_800_18DB
        { 256, },      // ISO_1600_24DB
        { 256, },      // ISO_3200_30DB
        { 256, },      // ISO_6400_36DB
        { 256, },      // ISO_12800_42DB
        { 256, },      // ISO_25600_48DB
        { 1, },      // ISO_51200_54DB
    },
    };
    memcpy(&pstDefaultParam.blc_tbl, &blc_tbl, sizeof(blc_container_sw_t));
    
    const dpc_container_sw_t            dpc_tbl = {
        .container = {
        {  2,    },     // ISO_100_0DB
        {  6,    },     // ISO_200_6DB
        {  8,    },     // ISO_400_12DB
        { 11,    },     // ISO_800_18DB
        { 18,    },     // ISO_1600_24DB
        { 32,    },     // ISO_3200_30DB
        { 52,    },     // ISO_6400_36DB
        { 52,    },     // ISO_12800_42DB
        { 52,    },     // ISO_25600_48DB
        { 1,    },     // ISO_51200_54DB
    },
    };
    memcpy(&pstDefaultParam.dpc_tbl, &dpc_tbl, sizeof(dpc_container_sw_t));
    
    const bnr_container_sw_t            bnr_tbl = {
        .container = {
        {    2,},     // ISO_100_0DB
        {    2,},     // ISO_200_6DB
        {    4,},     // ISO_400_12DB
        {    8,},     // ISO_800_18DB
        {    17,},     // ISO_1600_24DB
        {    34,},     // ISO_3200_30DB
        {    68,},     // ISO_6400_36DB
        {    68,},     // ISO_12800_42DB
        {    68,},     // ISO_25600_48DB
        {    1,},     // ISO_51200_54DB
    },
    };
    memcpy(&pstDefaultParam.bnr_tbl, &bnr_tbl, sizeof(bnr_container_sw_t));
    
    const lsc_container_sw_t            lsc_tbl = {
         .container = {
        { 2, 2300 },    // h - 2300K
        { 100, 2856 },    // A - 2856K
        { 100, 4000 },    // TL84 - 4000K
        { 100, 4150 },    // CWF - 4150K
        { 100, 5000 },    // D50 - 5000K
        { 100, 6500 },    // D65 - 6500K
        { 1, 7500 },    // D75 - 7500K
        },
    };
    memcpy(&pstDefaultParam.lsc_tbl, &lsc_tbl, sizeof(lsc_container_sw_t));
    
    const ccm_container_sw_t            ccm_tbl= {
        .container = {
        { { 816, -270, -34, -249, 703, 57, -74, -827, 1414  }, 2300 },    // h - 2300K
        { { 835, -320, -3, -204, 720, -4, -15, -575, 1103   }, 2856 },    // A - 2856K
        { { 847, -331, -4, -167, 707, -27, -20, -316, 848   }, 4000 },    // TL84 - 4000K
        { { 1072, -583, 22, -184, 701, -4, 11, -362, 863    }, 4150 },    // CWF - 4150K
        { { 962, -438, -12, -145, 770, -112, 1, -336, 846   }, 5000 },    // D50 - 5000K
        { { 915, -431, 27, -103, 705, -89, 13, -246, 745    }, 6500 },    // D65 - 6500K
        { { 1, -482, -20, -116, 761, -133, 4, -276, 783  }, 7500 },    // D75 - 7500K
        },
        .num_ccm = 7,
        };
    memcpy(&pstDefaultParam.ccm_tbl, &ccm_tbl, sizeof(ccm_container_sw_t));

    static const gamma_cal_t gamma_cal[] = {
    {
        {{
        2, 5, 115, 172, 228, 284, 339, 393, 447, 500, 553, 605, 656, 707, 757, 807,
        856, 904, 952, 999, 1045, 1091, 1137, 1182, 1226, 1269, 1312, 1355, 1397, 1438, 1479, 1519,
        1559, 1598, 1636, 1674, 1711, 1748, 1784, 1820, 1855, 1889, 1923, 1957, 1990, 2022, 2054, 2085,
        2116, 2146, 2175, 2204, 2233, 2261, 2288, 2315, 2342, 2368, 2393, 2418, 2442, 2466, 2489, 2512,
        2534, 2556, 2577, 2598, 2618, 2638, 2657, 2676, 2695, 2713, 2730, 2748, 2765, 2781, 2797, 2813,
        2829, 2844, 2859, 2874, 2888, 2902, 2916, 2930, 2943, 2957, 2970, 2983, 2995, 3008, 3020, 3032,
        3044, 3056, 3068, 3080, 3092, 3103, 3115, 3126, 3137, 3149, 3160, 3171, 3181, 3192, 3203, 3213,
        3224, 3234, 3244, 3255, 3265, 3275, 3285, 3295, 3305, 3314, 3324, 3333, 3343, 3352, 3362, 3371,
        3380, 3390, 3399, 3408, 3417, 3426, 3435, 3443, 3452, 3461, 3469, 3478, 3486, 3494, 3503, 3511,
        3519, 3527, 3535, 3543, 3550, 3558, 3566, 3573, 3580, 3588, 3595, 3602, 3609, 3616, 3623, 3629,
        3636, 3642, 3649, 3655, 3661, 3667, 3673, 3679, 3685, 3691, 3696, 3702, 3708, 3713, 3719, 3724,
        3729, 3735, 3740, 3745, 3750, 3756, 3761, 3766, 3771, 3776, 3781, 3786, 3791, 3796, 3801, 3806,
        3811, 3816, 3821, 3827, 3832, 3837, 3842, 3847, 3852, 3857, 3862, 3867, 3872, 3877, 3882, 3887,
        3892, 3897, 3902, 3907, 3912, 3916, 3921, 3926, 3931, 3936, 3940, 3945, 3950, 3954, 3959, 3963,
        3968, 3972, 3977, 3981, 3986, 3990, 3994, 3998, 4002, 4006, 4010, 4014, 4018, 4022, 4026, 4030,
        4033, 4037, 4040, 4044, 4047, 4051, 4054, 4057, 4060, 4063, 4066, 4069, 4072, 4074, 4077, 1,
        }},
        0,
    },
    {
        {{
        0, 25, 115, 172, 228, 284, 339, 393, 447, 500, 553, 605, 656, 707, 757, 807,
        856, 904, 952, 999, 1045, 1091, 1137, 1182, 1226, 1269, 1312, 1355, 1397, 1438, 1479, 1519,
        1559, 1598, 1636, 1674, 1711, 1748, 1784, 1820, 1855, 1889, 1923, 1957, 1990, 2022, 2054, 2085,
        2116, 2146, 2175, 2204, 2233, 2261, 2288, 2315, 2342, 2368, 2393, 2418, 2442, 2466, 2489, 2512,
        2534, 2556, 2577, 2598, 2618, 2638, 2657, 2676, 2695, 2713, 2730, 2748, 2765, 2781, 2797, 2813,
        2829, 2844, 2859, 2874, 2888, 2902, 2916, 2930, 2943, 2957, 2970, 2983, 2995, 3008, 3020, 3032,
        3044, 3056, 3068, 3080, 3092, 3103, 3115, 3126, 3137, 3149, 3160, 3171, 3181, 3192, 3203, 3213,
        3224, 3234, 3244, 3255, 3265, 3275, 3285, 3295, 3305, 3314, 3324, 3333, 3343, 3352, 3362, 3371,
        3380, 3390, 3399, 3408, 3417, 3426, 3435, 3443, 3452, 3461, 3469, 3478, 3486, 3494, 3503, 3511,
        3519, 3527, 3535, 3543, 3550, 3558, 3566, 3573, 3580, 3588, 3595, 3602, 3609, 3616, 3623, 3629,
        3636, 3642, 3649, 3655, 3661, 3667, 3673, 3679, 3685, 3691, 3696, 3702, 3708, 3713, 3719, 3724,
        3729, 3735, 3740, 3745, 3750, 3756, 3761, 3766, 3771, 3776, 3781, 3786, 3791, 3796, 3801, 3806,
        3811, 3816, 3821, 3827, 3832, 3837, 3842, 3847, 3852, 3857, 3862, 3867, 3872, 3877, 3882, 3887,
        3892, 3897, 3902, 3907, 3912, 3916, 3921, 3926, 3931, 3936, 3940, 3945, 3950, 3954, 3959, 3963,
        3968, 3972, 3977, 3981, 3986, 3990, 3994, 3998, 4002, 4006, 4010, 4014, 4018, 4022, 4026, 4030,
        4033, 4037, 4040, 4044, 4047, 4051, 4054, 4057, 4060, 4063, 4066, 4069, 4072, 4074, 4077, 11,
        }},
        128,
    },
    {
        {{
        0, 50, 115, 172, 228, 284, 339, 393, 447, 500, 553, 605, 656, 707, 757, 807,
        856, 904, 952, 999, 1045, 1091, 1137, 1182, 1226, 1269, 1312, 1355, 1397, 1438, 1479, 1519,
        1559, 1598, 1636, 1674, 1711, 1748, 1784, 1820, 1855, 1889, 1923, 1957, 1990, 2022, 2054, 2085,
        2116, 2146, 2175, 2204, 2233, 2261, 2288, 2315, 2342, 2368, 2393, 2418, 2442, 2466, 2489, 2512,
        2534, 2556, 2577, 2598, 2618, 2638, 2657, 2676, 2695, 2713, 2730, 2748, 2765, 2781, 2797, 2813,
        2829, 2844, 2859, 2874, 2888, 2902, 2916, 2930, 2943, 2957, 2970, 2983, 2995, 3008, 3020, 3032,
        3044, 3056, 3068, 3080, 3092, 3103, 3115, 3126, 3137, 3149, 3160, 3171, 3181, 3192, 3203, 3213,
        3224, 3234, 3244, 3255, 3265, 3275, 3285, 3295, 3305, 3314, 3324, 3333, 3343, 3352, 3362, 3371,
        3380, 3390, 3399, 3408, 3417, 3426, 3435, 3443, 3452, 3461, 3469, 3478, 3486, 3494, 3503, 3511,
        3519, 3527, 3535, 3543, 3550, 3558, 3566, 3573, 3580, 3588, 3595, 3602, 3609, 3616, 3623, 3629,
        3636, 3642, 3649, 3655, 3661, 3667, 3673, 3679, 3685, 3691, 3696, 3702, 3708, 3713, 3719, 3724,
        3729, 3735, 3740, 3745, 3750, 3756, 3761, 3766, 3771, 3776, 3781, 3786, 3791, 3796, 3801, 3806,
        3811, 3816, 3821, 3827, 3832, 3837, 3842, 3847, 3852, 3857, 3862, 3867, 3872, 3877, 3882, 3887,
        3892, 3897, 3902, 3907, 3912, 3916, 3921, 3926, 3931, 3936, 3940, 3945, 3950, 3954, 3959, 3963,
        3968, 3972, 3977, 3981, 3986, 3990, 3994, 3998, 4002, 4006, 4010, 4014, 4018, 4022, 4026, 4030,
        4033, 4037, 4040, 4044, 4047, 4051, 4054, 4057, 4060, 4063, 4066, 4069, 4072, 4074, 4077, 1,
        }},
        255,
    },
};
memcpy(&pstDefaultParam.gamma_cal_tbl, &gamma_cal, sizeof(gamma_container_cal_t));

static const gamma_container_sw_t gamma_tbl = {
    .container = {
            {2},  //[0]:-54 db
            {12},  //[1]:-48 db
            {12},  //[2]:-42 db
            {12},  //[3]:-36 db
            {12},  //[4]:-30 db
            {12},  //[5]:-24 db
            {12},  //[6]:-18 db
            {12},  //[7]:-12 db
            {12},  //[8]:-6 db
            {12},  //[9]:0 db
            {12},  //[10]:6 db
            {12},  //[11]:12 db
            {12},  //[12]:18 db
            {12},  //[13]:24 db
            {12},  //[14]:30 db
            {12},  //[15]:36 db
            {12},  //[16]:42 db
            {12},  //[17]:48 db
            {1},  //[18]:54 db
    },
};
memcpy(&pstDefaultParam.gamma_tbl, &gamma_tbl, sizeof(gamma_container_sw_t));

    const wdr_container_sw_t            wdr_tbl= {
        .container = {
            { 2, 16, 16, 20, 20, },  //[0]:-54 db
            { 8, 16, 16, 20, 20, },  //[1]:-48 db
            { 8, 16, 16, 20, 20, },  //[2]:-42 db
            { 8, 16, 16, 20, 20, },  //[3]:-36 db
            { 8, 16, 16, 20, 20, },  //[4]:-30 db
            { 8, 16, 16, 20, 20, },  //[5]:-24 db
            { 8, 16, 16, 20, 20, },  //[6]:-18 db
            { 8, 16, 16, 20, 20, },  //[7]:-12 db
            { 8, 16, 16, 20, 20, },  //[8]:-6 db
            { 8, 16, 16, 20, 20, },  //[9]:0 db
            { 8, 16, 16, 20, 20, },  //[10]:6 db
            { 8, 16, 16, 20, 20, },  //[11]:12 db
            { 8, 16, 16, 20, 20, },  //[12]:18 db
            { 8, 16, 16, 20, 20, },  //[13]:24 db
            { 8, 16, 16, 20, 20, },  //[14]:30 db
            { 8, 16, 16, 20, 20, },  //[15]:36 db
            { 8, 16, 16, 20, 20, },  //[16]:42 db
            { 8, 16, 16, 20, 20, },  //[17]:48 db
            { 1,  1,  1 , 1,  1, },  //[18]:54 db
    },
            };
    memcpy(&pstDefaultParam.wdr_tbl, &wdr_tbl, sizeof(wdr_container_sw_t));
    
    const sat_container_sw_t            sat_tbl= {
        .container = {
            { 2,  },    // ISO_100_0DB
            { 128,  },    // ISO_200_6DB
            { 120,  },    // ISO_400_12DB
            { 110,  },    // ISO_800_18DB
            { 105,  },    // ISO_1600_24DB
            { 100,  },    // ISO_3200_30DB
            { 95,   },    // ISO_6400_36DB
            { 90,   },    // ISO_12800_42DB
            { 80,   },    // ISO_25600_48DB
            { 1,   },    // ISO_51200_54DB
        },
    };
    memcpy(&pstDefaultParam.sat_tbl, &sat_tbl, sizeof(sat_container_sw_t));

    const yc_container_sw_t            yc_tbl= {
        .container = {
            { 2,0  },    // ISO_100_0DB
            { 128,0  },    // ISO_200_6DB
            { 128,0  },    // ISO_400_12DB
            { 128,0  },    // ISO_800_18DB
            { 128,0  },    // ISO_1600_24DB
            { 128,0  },    // ISO_3200_30DB
            { 128,0  },    // ISO_6400_36DB
            { 128,0  },    // ISO_12800_42DB
            { 128,0  },    // ISO_25600_48DB
            { 1,1  },    // ISO_51200_54DB
        },
    };
    memcpy(&pstDefaultParam.yc_tbl, &yc_tbl, sizeof(yc_container_sw_t));

    const nr_container_sw_t             nr_tbl= {
        .container = {
        {  2,          4,           2,       },    // ISO_100_0DB
        {  6,          4,           2,       },    // ISO_200_6DB
        {  8,          4,           2,       },    // ISO_400_12DB
        { 10,          6,           3,       },    // ISO_800_18DB
        { 12,          8,           5,       },    // ISO_1600_24DB
        { 16,         10,           6,       },    // ISO_3200_30DB
        { 24,         12,           6,       },    // ISO_6400_36DB
        { 31,         14,           6,       },    // ISO_12800_42DB
        { 31,         14,           6,       },    // ISO_25600_48DB
        { 1,         11,           1,       },    // ISO_51200_54DB
        },
    };
    memcpy(&pstDefaultParam.nr_tbl, &nr_tbl, sizeof(nr_container_sw_t));
    
    const ee_container_sw_t             ee_tbl = {
        .container = {
        { 2,   40,    127,      127, },    // ISO_100_0DB
        { 40,   40,    127,      127,},    // ISO_200_6DB
        { 40,   40,    127,      127,},    // ISO_400_12DB
        { 40,   40,    127,      127,},    // ISO_800_18DB
        { 40,   40,    127,      127,},    // ISO_1600_24DB
        { 40,   40,    127,      127,},    // ISO_3200_30DB
        { 40,   40,    127,      127,},    // ISO_6400_36DB
        { 40,   40,     64,       64,},    // ISO_12800_42DB
        { 40,   40,     32,       32,},    // ISO_25600_48DB
        { 1,   1,     1,       1,},    // ISO_51200_54DB
        },
    };
    memcpy(&pstDefaultParam.ee_tbl, &ee_tbl, sizeof(ee_container_sw_t));
    
    const cs_container_sw_t             cs_tbl = {
        .container = {
        {   2,  },// ISO_100_0DB
        {   20,  },// ISO_200_6DB
        {   40,  },// ISO_400_12DB
        {   60,  },// ISO_800_18DB
        {   60,  },// ISO_1600_24DB
        {   60,  },// ISO_3200_30DB
        {   60,  },// ISO_6400_36DB
        {   60,  },// ISO_12800_42DB
        {   60,  },// ISO_25600_48DB
        {   1,  },// ISO_51200_54DB
        },
    };
    memcpy(&pstDefaultParam.cs_tbl, &cs_tbl, sizeof(cs_container_sw_t));
    MM_DSP2_SetDsp2Param(&pstDefaultParam);

    /*  test as binary file */
    pstDefaultParam.sat_tbl.container[0].value = 4;
    MM_DSP2_LoadDsp2Param((BL_UINT32 *)&pstDefaultParam);

    return;
}

static void load_api_reg_cmd(char *buf, int len, int argc, char **argv)
{
    load_api_reg();
}

static int dsp2_ctrl(void)
{
    int ret;

    if (helper_preperty.dsp2_inited == 1) {
        aos_cli_printf("[OK] \r\n");
        return 0;
    }

    ret = dsp2fw_init(false, NULL);
    if (-1 == ret) {
        aos_cli_printf("[NG] \r\n");
        return -1;
    }
    hdmi_ctrl(1);
    aos_cli_printf("[OK] \r\n");
    return 0;
}

static int hdmi_ctrl(int ctrl_type)
{
    MMDSP2FrmSrcAttr frmsrc_attr;

    if (ctrl_type == 1) {
        // HDMI only support 720p now
        MM_DSP2_GetFrameSrcChnAttr(1, &frmsrc_attr);
        frmsrc_attr.picWidth = 1280;
        frmsrc_attr.picHeight = 720;
        frmsrc_attr.dsp2Position = DSP2_POSITION_ADJ_B;
        MM_DSP2_SetFrameSrcChnAttr(1, &frmsrc_attr);
        adv7511_enable();
        MM_DSP2_HDMI_Start();
    } else {
        MM_DSP2_HDMI_Stop();
        adv7511_disable();
    }
    return 0;
}

struct dsp2_sensor_if *sensor_func_ptr_inter = {0};

static int dsp2_api_start(void)
{
    if (helper_preperty.dsp2_inited == 1) {
        aos_cli_printf("[OK] inited \r\n");
        return 0;
    }

    //sensor_func_ptr = API_DSP2_Sensor_Create();
    MM_Sensor_RegisterCb(0, &sensor_func_ptr_inter);
    MM_Sensor_Init();
    if (MM_Sensor_SetFmt(VIDEO_MODE_1080P_25) < 0) return -1;

    BL_CHAR *sensor_name;
    sensor_func_ptr_inter->name(&sensor_name);
    printf("============== %s\r\n",sensor_name);

    BL_UINT32 fps;
    sensor_func_ptr_inter->get_fps(&fps);
    printf("============== %d\r\n",fps);
#if 0
    // set pix clk here
    //API_DSP2_SetPixClk(70000000);
    
    DSP2_VI_ATTR_S viAttr;
    API_DSP2_GetViAttr(&viAttr);
    printf("========================= viAttr.u16WndWidth %d \r\n",viAttr.u16WndWidth);
    printf("========================= viAttr.u16WndHeight %d \r\n",viAttr.u16WndHeight);
    printf("========================= viAttr.enBayerType %d \r\n",viAttr.enBayerType);

    #if 1
    // form sensor 0,0 to 1280,720, attr:1125,2640,720,1280,720,1280,25,3,
    viAttr.u16InputWidth = 1280;
    viAttr.u16InputHeight = 720;
    viAttr.u16PicWidth = 1280;
    viAttr.u16PicHeight = 720;
    #else
    // looks like resize to 1280,720, attr:1125,2640,1080,1920,720,1280,25,3,
    viAttr.u16PicWidth = 1280;
    viAttr.u16PicHeight = 720;
    #endif
    API_DSP2_SetViAttr(&viAttr);

    sensor_set_flipmirror(FLIP_MIRROR_TYPE_MIRROR);
#endif
    //API_DSP2_AWBAlgo(1);

    MM_DSP2_Init();
    //load_api_reg();
    if (helper_preperty.dsp2_runed == 1) {
        aos_cli_printf("[OK] runed \r\n");
        return 0;
    }

    //ae_set_mode(AE_MODE_DBG_AE_LINEARITY);
    MM_DSP2_Run();
    hdmi_ctrl(1);
    helper_preperty.dsp2_inited = 1;
    helper_preperty.dsp2_runed = 1;

    return 0;
}



static int dsp2_api_pause(void)
{
    if (helper_preperty.dsp2_runed == 0) {
        aos_cli_printf("[OK] not runed \r\n");
        return 0;
    }

    helper_preperty.dsp2_runed = 0;
    
    MM_Sensor_UnRegisterCb(0);

    MM_DSP2_Pause();
    hdmi_ctrl(0);

    return 0;
}


static int dsp2_api_resume(void)
{
    if (helper_preperty.dsp2_runed == 1) {
        aos_cli_printf("[OK] runed \r\n");
        return 0;
    }

    //MM_DSP2_ChangeFmt(VIDEO_MODE_1080P_25);
    //MM_DSP2_ChangeFmt(VIDEO_MODE_1080P_30);
    //MM_DSP2_ChangeFmt(VIDEO_MODE_720P_59_94);
    //MM_DSP2_ChangeFmt(VIDEO_MODE_720P_30);

    MM_Sensor_RegisterCb(0, &sensor_func_ptr_inter);

    BL_CHAR *sensor_name;
    sensor_func_ptr_inter->name(&sensor_name);
    printf("==============dsp2_api_resume  %s\r\n",sensor_name);

    BL_UINT32 fps;
    sensor_func_ptr_inter->get_fps(&fps);
    printf("==============dsp2_api_resume  %d\r\n",fps);

#if 0
    MMDSP2VinAttr viAttr;
    MM_DSP2_GetVinAttr(&viAttr);
    // form sensor 1920,1080 to 1280,720, attr: 2640,1125,1920,1080,1280,720,0,25,
    viAttr.out_win.width = 1280;
    viAttr.out_win.height = 720;
    viAttr.bayer_pattern = 0;
    printf("========================= viAttr.u16WndWidth %d \r\n",viAttr.out_win.width);
    printf("========================= viAttr.u16WndHeight %d \r\n",viAttr.out_win.height);
    printf("========================= viAttr.bayer_pattern %d \r\n",viAttr.bayer_pattern);
    MM_DSP2_SetVinAttr(&viAttr);
#endif
    //sensor_set_flipmirror(FLIP_MIRROR_TYPE_MIRROR);


    MM_DSP2_Resume();
    vTaskDelay(1);
    hdmi_ctrl(1);
    helper_preperty.dsp2_runed = 1;

    return 0;
}


const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
        { "idsp2", "DSP2 related operation", dsp2_cmd },
        //{ "iload_api", "Load DSP2 related register", load_api_reg_cmd },
};

int helper_dsp2_internal_cli_init(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user) / sizeof(cmds_user[0]));
    return 0;
}

