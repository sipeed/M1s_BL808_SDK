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
#include "sensor.h"
#include "hdmi.h"
#include "img_proc.h"
#include "img_param.h"
#include "mm_sensor.h"
#include "mm_dsp2.h"
#include "mm_debug.h"
#include "sample_common.h"
#include "helper_dsp2.h"
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

static int dsp2_api_init(char *sensor_fmt);
static int dsp2_api_start(void);
static int dsp2_api_pause(void);
static int dsp2_api_resume(void);

#define DSP2_TEST 1

#if DSP2_TEST
#include "helper_dsp2_parse.h"

static char module[32] = {'\0'};
static char argv_reg[32] = {'\0'};
static char argv_val[512] = {'\0'};
static char ret_string[512] = {'\0'};
#endif
enum numeric_short_options {
    SENSOR_INPUT = 1000,

    INIT,
    START,
    PAUSE,
    RESUME,
    
    RAW_FILE_INPUT,
    PATTERN_GEN_INPUT,
    IMG_DUMP_ADDR,
    IMG_DUMP_SIZE,
    IMG_LOAD_ADDR,
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
    DSP2_MISC_REG,
    AXI_CTRL_REG,
    TG_REG,
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
    YUVC_REG,

    //ATTR
    MODULE_ATTR,
    REG_ADDR,
    REG_SENSOR_ADDR,
};

struct helper_dsp2_property {
    int load_auto_inited;
    int dsp2_chann_id;
    int pattern_gen_mode;
    uint32_t sensor_width;
    uint32_t sensor_height;
    MMDSP2YuvFrame yuv_frm[MAX_CHANN_NUM];
};

static struct helper_dsp2_property helper_preperty = {
    .load_auto_inited = 0,
    .pattern_gen_mode = -1,
};

static int dsp2fw_init(bool is_virtual, const VirtualSensorInfo *virtSnsInfo)
{
    int ret;

    MM_DBG_EnableVirtualSensor(is_virtual, virtSnsInfo);
    if (is_virtual == true) {
        MM_DBG_SetPatternGenMode(helper_preperty.pattern_gen_mode);
        ret = sample_system_vir_init();
    } else {
        ret = sample_system_init();
    }

    if (-1 == ret) {
        return -1;
    }

    MMSensorAttr snsAttr;
    MM_Sensor_GetChnAttr(0, &snsAttr);
    helper_preperty.sensor_width = snsAttr.picWidth;
    helper_preperty.sensor_height = snsAttr.picHeight;

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
}

static void dsp2_cmd(char *buf, int len, int argc, char **argv)
{
    VirtualSensorInfo virt_sns_info;
    MMDSP2FrmSrcAttr frmsrc_attr;
    MMDSP2Position dsp2_pos;
    MMDSP2FrmSrcCrop frmSrcCropRoi = {0};
    BL_Img_Size_T win;
    int ch;
    char sensor_fmt[16];
    uint32_t value = 0;
    uint32_t addr, size;
    uint32_t **data_val = 0;
    int ret = -1;
    optind = 0;

    static struct option long_options[] =
    {
        {"sensor-input",        no_argument,       0, SENSOR_INPUT},

        {"init",                required_argument, 0, INIT},
        {"start",               no_argument,       0, START},
        {"pause",               no_argument,       0, PAUSE},
        {"resume",              no_argument,       0, RESUME},
        
        {"raw-file-input",      required_argument, 0, RAW_FILE_INPUT},
        {"pattern-gen-input",   required_argument, 0, PATTERN_GEN_INPUT},
        {"in-size",             required_argument, 0, 'i'},
        {"out-size",            required_argument, 0, 'o'},
        {"out-size-sub",        required_argument, 0, 'O'},
        {"get-resolution",      required_argument, 0, GET_RESOLUTION},
        {"get-sensor-name",     no_argument,       0, GET_SENSOR_NAME},
        {"get-black-level",     no_argument,       0, GET_BLACK_LEVEL},
        {"get-bayer-pattern",   no_argument,       0, GET_BAYER_PATTERN},
        {"chann-id",            required_argument, 0, 'c'},
        {"fps",                 required_argument, 0, 'f'},
        {"set-sensor-fps",      required_argument, 0, 'F'},
        {"img-dump-multi-src",  required_argument, 0, 'm'},
        {"img-dump-src",        required_argument, 0, 'S'},
        {"img-dump-start",      no_argument,       0, 's'},
        {"img-dump-end",        no_argument,       0, 'e'},
        {"img-dump-addr",       no_argument,       0, IMG_DUMP_ADDR},
        {"img-dump-size",       no_argument,       0, IMG_DUMP_SIZE},
        {"img-load-addr",       no_argument,       0, IMG_LOAD_ADDR},
        {"img-crop-test",       no_argument,       0, 't'},
        {"img-scaler-test",     no_argument,       0, 'T'},
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
        {"dsp2-misc-reg",          required_argument, 0, DSP2_MISC_REG},
        {"axi-ctrl-reg",          required_argument, 0, AXI_CTRL_REG},
        {"tg-reg",                required_argument, 0, TG_REG},
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
        {"yuvc-reg",              required_argument, 0, YUVC_REG},

        //ATTR
        {"module-attr",           required_argument, 0, MODULE_ATTR},
        {"reg-addr",              required_argument, 0, REG_ADDR},
        {"reg-sensor_addr",       required_argument, 0, REG_SENSOR_ADDR},

        {0, 0, 0, 0}
    };

    if (1 == argc) {
        dsp2_ctrl();
        return;
    }

    while ((ch = getopt_long (argc, argv, "i:c:o:O:f:S:sm:ren:h", long_options, NULL)) != -1) {
        switch (ch)
        {
        case INIT:
            strncpy(&sensor_fmt, optarg, sizeof(char) * 16 - 1);
            printf("%s \r\n", optarg);
            dsp2_api_init(sensor_fmt);
            break;
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
            MM_DBG_GetVirtSensorTsrcAddr(&addr);
            aos_cli_printf("[OK] IMG_LOAD_ADDR: 0x%08x \r\n", addr);
            break;

        case PATTERN_GEN_INPUT:
            virt_sns_info.width = win.width;
            virt_sns_info.height = win.height;
            strncpy(virt_sns_info.sensor_name, "GC2053", sizeof(virt_sns_info.sensor_name) - 1);

            helper_preperty.pattern_gen_mode = atoi(optarg);;
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

        case 'F':
            value = atoi(optarg);
            if (sample_set_chann_frame_rate_from_sensor(helper_preperty.dsp2_chann_id, value) < 0) goto FAIL;
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
            MM_DSP2_GetFrameSrcChnAttr(helper_preperty.dsp2_chann_id, &frmsrc_attr);
            if (frmsrc_attr.dsp2Position == DSP2_POSITION_AWB3) {
                MM_DSP2_StartRecvPic(helper_preperty.dsp2_chann_id, PIX_FMT_DATA8);
            } else {
                MM_DSP2_StartRecvPic(helper_preperty.dsp2_chann_id, PIX_FMT_DATA16);
            }
            MM_DSP2_GetOnePicture(helper_preperty.dsp2_chann_id, &helper_preperty.yuv_frm[helper_preperty.dsp2_chann_id]);
            MM_DSP2_StopRecvPic(helper_preperty.dsp2_chann_id);

            uint32_t addr = (uint32_t)helper_preperty.yuv_frm[helper_preperty.dsp2_chann_id].frameStartAddr;
            uint32_t size = helper_preperty.yuv_frm[helper_preperty.dsp2_chann_id].frameSize;
            csi_dcache_invalid_range(addr, size);
            printf("addr: 0x%08x 0x%08x, size: %d\r\n", addr, addr + size, size);
            break;

        case 'm':
            helper_preperty.dsp2_chann_id = 0;
            int start_dsp2_chann_id = helper_preperty.dsp2_chann_id;
            int dsp2_chann_id = 0;
            int dump_num = 0, idx = 0;
            int dsp2_pos[4] = {0};//MAX_NUM_FRAMESOURCE

            if (sscanf(optarg, "%d_%d_%d_%d", &dsp2_pos[0], &dsp2_pos[1], &dsp2_pos[2], &dsp2_pos[3]) == 4) {
                dump_num = 4;
            } else if (sscanf(optarg, "%d_%d_%d", &dsp2_pos[0], &dsp2_pos[1], &dsp2_pos[2]) == 3) {
                dump_num = 3;
            } else if (sscanf(optarg, "%d_%d", &dsp2_pos[0], &dsp2_pos[1]) == 2) {
                dump_num = 2;
            } else if (sscanf(optarg, "%d", &dsp2_pos[0]) == 1) {
                dump_num = 1;
            } else {
                goto FAIL;
            }

            if (IMGPROC_RUN != MM_DSP2_Status()) goto FAIL;
            for (idx = 0; idx < dump_num; idx++) {
                dsp2_chann_id = start_dsp2_chann_id + idx;
                MM_DSP2_GetFrameSrcChnAttr(start_dsp2_chann_id, &frmsrc_attr);
                frmsrc_attr.dsp2Position = (MMDSP2Position)dsp2_pos[idx];
                if (frmsrc_attr.dsp2Position == DSP2_POSITION_AWB3) {
                    frmsrc_attr.pixFmt = PIX_FMT_DATA8;
                } else if (frmsrc_attr.dsp2Position == DSP2_POSITION_YUV2RGB) {
                    frmsrc_attr.pixFmt = PIX_FMT_RGB0;
                } else {
                    frmsrc_attr.pixFmt = PIX_FMT_DATA16;
                }

                /*printf("======= idx: %d: w:%d, h:%d, fmt:%d, %d, %d, %d, pos:%d\r\n", dsp2_chann_id,
                    frmsrc_attr.picWidth,frmsrc_attr.picHeight,
                    frmsrc_attr.pixFmt, frmsrc_attr.outFrmRateNum, frmsrc_attr.outFrmRateDen,
                    frmsrc_attr.isFullRange,frmsrc_attr.dsp2Position);*/
                MM_DSP2_SetFrameSrcChnAttr(dsp2_chann_id, &frmsrc_attr);
                MM_DSP2_StartDumpPic(dsp2_chann_id, frmsrc_attr.pixFmt, frmsrc_attr.dsp2Position);
            }

            for (idx = 0; idx < dump_num; idx++) {
                dsp2_chann_id = start_dsp2_chann_id + idx;
                MM_DSP2_GetOnePicture(dsp2_chann_id, &helper_preperty.yuv_frm[dsp2_chann_id]);
                MM_DSP2_StopRecvPic(dsp2_chann_id);
            }

            for (idx = 0; idx < dump_num; idx++) {
                dsp2_chann_id = start_dsp2_chann_id + idx;
                addr = (uint32_t)helper_preperty.yuv_frm[dsp2_chann_id].frameStartAddr;
                size = helper_preperty.yuv_frm[dsp2_chann_id].frameSize;
                csi_dcache_invalid_range(addr, size);
                printf("[OK] %d addr: 0x%08x 0x%08x, size: %d\r\n", dsp2_chann_id, addr, addr + size, size);
            }
            break;

        case 'e':
            /* Deprecated */
            break;

        case 't':
           frmSrcCropRoi.enable = 1;
           frmSrcCropRoi.left = 0;
           frmSrcCropRoi.top = 0;
           frmSrcCropRoi.width = 1282;
           frmSrcCropRoi.height = 722;
           helper_preperty.dsp2_chann_id = 1;
           ret = MM_DSP2_SetFrameSrcChnAttr_crop(helper_preperty.dsp2_chann_id, &frmSrcCropRoi);
           if (ret == -1) goto FAIL;

           MM_DSP2_GetFrameSrcChnAttr(helper_preperty.dsp2_chann_id, &frmsrc_attr);
           frmsrc_attr.picWidth = frmSrcCropRoi.width;
           frmsrc_attr.picHeight = frmSrcCropRoi.height;
           MM_DSP2_SetFrameSrcChnAttr(helper_preperty.dsp2_chann_id, &frmsrc_attr);
           break;

        case 'T':
            helper_preperty.dsp2_chann_id = 1;
            MM_DSP2_GetFrameSrcChnAttr(helper_preperty.dsp2_chann_id, &frmsrc_attr);
            frmsrc_attr.picWidth = 1280;
            frmsrc_attr.picHeight = 720;
            frmsrc_attr.dsp2Position = DSP2_POSITION_ADJ_B;
            MM_DSP2_SetFrameSrcChnAttr(helper_preperty.dsp2_chann_id, &frmsrc_attr);
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

        case IMG_LOAD_ADDR:
            MM_DBG_GetVirtSensorTsrcAddr(&addr);
            *data_val = &addr;
            aos_cli_printf("[OK] IMG_LOAD_ADDR: 0x%08x, 0x%08x \r\n", addr, *data_val);
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
        }
        case Get_AE_HIST_SUM_BAYER: {
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
#if DSP2_TEST
        case SENSOR_REG:
        case SYS_REG:
        case DSP2_MISC_REG:
        case AXI_CTRL_REG:
        case TG_REG:
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
        case YC_REG:
        case YUVC_REG:{
            const char *format = "--%s";
            int payload_len_in = 0;
            int ret = -1;

            memset(module, '\0', sizeof(char) * 32);
            memset(argv_reg, '\0', sizeof(char) * 32);
            memset(argv_val, '\0', sizeof(char) * 512);
            memset(ret_string, '\0', sizeof(char) * 512);

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
#endif
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

int load_reg(uint32_t *addr)
{
    if (img_param_malloc_sw_param_init_buffer() == 1) printf("it's load inited \r\n");
    img_param_get_sw_bin_Addr(addr);

    return 0;
}

static void load_reg_cmd(char *buf, int len, int argc, char **argv)
{
    int ret = 0;
    uint32_t addr = 0;

    if (1 == argc) {
        ret = load_reg(&addr);
        if (-1 == ret) {
            aos_cli_printf("[NG] \r\n");
            return;
        }
        aos_cli_printf("[OK] load start_ptr: 0x%x, %d\r\n", addr, sizeof(BL_IMG_PARAM_SW_BIN_DESC_T));

        return;
    }
}

int dsp2_ctrl(void)
{
    int ret;

    if (IMGPROC_RUN == MM_DSP2_Status()) {
        aos_cli_printf("[OK] \r\n");
        return 0;
    }

    ret = dsp2fw_init(false, NULL);
    if (-1 == ret) {
        aos_cli_printf("[NG] \r\n");
        return -1;
    }
    //hdmi_ctrl(1);
    aos_cli_printf("[OK] \r\n");
    return 0;
}

int hdmi_ctrl(int ctrl_type)
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

struct dsp2_sensor_if *sensor_func_ptr = {0};

static int dsp2_api_enc(void)
{
    sample_sub_system_init();

    return 0;
}

static int dsp2_api_init(char *sensor_fmt)
{
    int i;
    VIDEO_MODE_E format = -1;
    MMSensorAttr snsAttr;

    for(i = 0; i < VIDEO_MODE_UXGA_25; i++) {
        printf("sensor_fmt |%s|, video_mode_str_arr[%d] |%s|\r\n",sensor_fmt, i, video_mode_str_arr[i]);
        if(strcmp(sensor_fmt, video_mode_str_arr[i]) == 0) {
            format = i;
            continue;
        }
    }

    if (format == -1) {
        aos_cli_printf("[NG] please check the sensor formate!!!! \r\n");
        return -1;
    }

    if (IMGPROC_RUN == MM_DSP2_Status()) {
        aos_cli_printf("[OK] inited format %s\r\n", video_mode_str_arr[format]);
        return 0;
    }

    MM_System_Init();

    MM_Sensor_RegisterCb(0, &sensor_func_ptr);
    MM_Sensor_Init();
    if (MM_Sensor_SetFmt(format) < 0) return -1;

    MM_Sensor_GetChnAttr(0, &snsAttr);
    helper_preperty.sensor_width = snsAttr.picWidth;
    helper_preperty.sensor_height = snsAttr.picHeight;

    return 0;
}

static int dsp2_api_start(void)
{
    MM_DSP2_Exit();
    MM_DSP2_Init();
    //load_api_reg();
    if (IMGPROC_RUN == MM_DSP2_Status()) {
        aos_cli_printf("[OK] runed \r\n");
        return 0;
    }

    //ae_set_mode(AE_MODE_DBG_AE_LINEARITY);
    MM_DSP2_Run();
    dsp2_api_enc();
    //hdmi_ctrl(1);

    return 0;
}



static int dsp2_api_pause(void)
{
    if (IMGPROC_RUN != MM_DSP2_Status()) {
        aos_cli_printf("[OK] not runed \r\n");
        return 0;
    }

    
    MM_Sensor_UnRegisterCb(0);

    MM_DSP2_Pause();
    //hdmi_ctrl(0);

    return 0;
}


static int dsp2_api_resume(void)
{
    if (IMGPROC_RUN == MM_DSP2_Status()) {
        aos_cli_printf("[OK] runed \r\n");
        return 0;
    }

    MM_Sensor_RegisterCb(0, &sensor_func_ptr);

    MM_DSP2_Resume();
    dsp2_api_enc();
    //vTaskDelay(1);
    //hdmi_ctrl(1);

    return 0;
}


const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
        { "load", "Load DSP2 related register", load_reg_cmd },
        { "dsp2", "DSP2 related operation", dsp2_cmd },
};

int helper_dsp2_cli_init(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user) / sizeof(cmds_user[0]));
    return 0;
}

