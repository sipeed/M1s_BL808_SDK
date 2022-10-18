#include <aos/kernel.h>

#include <string.h>
#include <bl_dsp2.h>

#include "img_param.h"
#include "img_param_parse.h"
#include "img_proc.h"
#include "img_peripheral_ctrl.h"
#include "firmware_ae.h"
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

#define VIRTUAL_LOOP            0
#define PERFORMANCE_MONITOR     0
#define IMG_PROC_SKIP_NUM       0
#define DEFAULT_AE_ALGO         AE_ALGO_BL
#define DEFAULT_AWB_ALGO        AWB_ALGO_3
#define DEFAULT_FLICKER_MODE    FLICKER_MODE_50
#define EXTRA_WDR_CONVERGE_FRAME_CNT    5

#define GPIO_IR_BOARD_IRC       (0xFF)
#define GPIO_SENSOR_BOARD_IRC   (0xFF)
#define UNUPDATE_VALUE          (0xFFFFFFFF)

#define IMG_UPDATE_MASK_BLC         (1 << 0)
#define IMG_UPDATE_MASK_DPC         (1 << 1)
#define IMG_UPDATE_MASK_BNR         (1 << 2)
#define IMG_UPDATE_MASK_LSC         (1 << 3)
#define IMG_UPDATE_MASK_WB_GAIN     (1 << 4)
#define IMG_UPDATE_MASK_CCM         (1 << 5)
#define IMG_UPDATE_MASK_GAMMA       (1 << 6)
#define IMG_UPDATE_MASK_WDR         (1 << 7)
#define IMG_UPDATE_MASK_SATURATION  (1 << 8)
#define IMG_UPDATE_MASK_NR          (1 << 9)
#define IMG_UPDATE_MASK_EE          (1 << 10)
#define IMG_UPDATE_MASK_CS          (1 << 11)
#define IMG_UPDATE_MASK_YC          (1 << 12)

typedef struct {
    uint8_t status;
    int stop_imgproc_flag;
    uint16_t skip_num;
    uint16_t start_skip_num;
    uint16_t update_force;
    uint16_t quick_mode_mask; // sensor qucik mode use only
    AE_ALGO  ae_algo;
    AWB_ALGO awb_algo;
    bool is_virtual_sensor;
    const BL_IMG_PARAM_DESC_T *img_param;
    const BL_IMG_PARAM_SW_DESC_T *img_param_sw;
} imgproc_obj_t;

typedef struct
{
    uint8_t fw_module_en[DSP2_ADJ_PARAM_NUM];
    uint8_t fw_module_manual_mode[DSP2_ADJ_PARAM_NUM];
    uint32_t update_mask;
    bl_dsp2_rb_gain_t rb_gain;
} img_porc_dsp2_cfg_t;

typedef struct
{
    int iso_flag;
    int ct_flag;
    BL_GAIN_DB ae_gain;
    BL_EXPO_TIME ae_expo_time;
    BL_GAIN_DB ae_sys_gain;
    BL_COLOR_TEMP awb_ct;
} img_porc_dsp2_keep_cfg_t;

typedef struct {
    uint8_t force;
    uint8_t iso;
    uint8_t expo_time;
    uint8_t sys_gain;
    uint8_t ct;
    uint8_t ae;
    uint8_t awb;
 } imgproc_update_flag_t;

typedef struct {
    uint16_t force;
    BL_GAIN_DB iso;
    BL_EXPO_TIME expo_time;
    BL_GAIN_DB sys_gain;
    BL_COLOR_TEMP ct;
} imgproc_update_val_t;

typedef struct {
    imgproc_update_flag_t flag;
    imgproc_update_val_t value;
} imgproc_update_t;

typedef struct {
    bool fps_flag;
    uint32_t fps;
    uint32_t cur_frame_num;
    TickType_t cur_frame_time;
} imgproc_fps_t;

// TODO: use heap
static imgproc_obj_t img_proc;
static img_porc_dsp2_cfg_t dsp2_cfg;
static img_porc_dsp2_keep_cfg_t dsp2_keep_cfg;//for no HW Eable module
static imgproc_update_t dsp2_update;
static imgproc_fps_t img_proc_fps;
static int img_proc_ae_algo = DEFAULT_AE_ALGO;
static int img_proc_awb_algo = DEFAULT_AWB_ALGO;
static int img_proc_flicker_mode = DEFAULT_FLICKER_MODE;
static bl_dsp2_update_fps_cb imgproc_update_fps_cb = NULL;
static int imgproc_chan_id = 0;/*h264_main*/
static TaskHandle_t hdr;               /* task handle */

#if PERFORMANCE_MONITOR
#define FRM_CNT_FOR_ONE_STATS     100       /* 8 sec */
static int ae_handl_cnt = 0;
static TickType_t ae_handl_start_time = 0;
#endif

static void imgproc_fps_start(void)
{
    img_proc_fps.cur_frame_time = xTaskGetTickCount();
    img_proc_fps.fps_flag = 1;
    img_proc_fps.cur_frame_num = 0;
}

static void imgproc_fps_end(int sec_time)
{
    TickType_t cur_time = 0;
    int run_time = 0;
    if (img_proc_fps.fps_flag == 1) {
        cur_time = xTaskGetTickCount();
        run_time = (cur_time - img_proc_fps.cur_frame_time);
        img_proc_fps.fps = (img_proc_fps.cur_frame_num * 1000 / run_time);
        //printf("do run_time %d, cur_frame_num, %d, fps:%d\r\n", run_time, img_proc_fps.cur_frame_num, img_proc_fps.fps);
        img_proc_fps.fps_flag = 0;
    }
}

static void imgproc_fps_run(uint32_t sec_time)
{
    imgproc_fps_start();
    vTaskDelay((sec_time * 1000));
    imgproc_fps_end(sec_time);
}

static void imgproc_set_update_state(const imgproc_update_flag_type_t flag_type, bool flag, int value)
{
    switch (flag_type)
        {
        case FORCE_FLAG:
            dsp2_update.flag.force = flag;
            if (value != UNUPDATE_VALUE) dsp2_update.value.force = value;
            break;
        case ISO_FLAG:
            dsp2_update.flag.iso = flag;
            if (value != UNUPDATE_VALUE) dsp2_update.value.iso = value;
            break;
        case EXPO_TIME_FLAG:
            dsp2_update.flag.expo_time = flag;
            if (value != UNUPDATE_VALUE) dsp2_update.value.expo_time = value;
            break;
        case SYS_GAIN_FLAG:
            dsp2_update.flag.sys_gain = flag;
            if (value != UNUPDATE_VALUE) dsp2_update.value.sys_gain = value;
            break;
        case CT_FLAG:
            dsp2_update.flag.ct = flag;
            if (value != UNUPDATE_VALUE) dsp2_update.value.ct = value;
            break;
        default:
            break;
        }

}

BL_Fun_Type imgproc_get_fw_module_manual_mode(const img_param_module_t module)
{
    return dsp2_cfg.fw_module_manual_mode[module];
}

int imgproc_set_fw_module_manual_mode(const img_param_module_t module, BL_Fun_Type enable)
{
    if ((enable != ENABLE) && (enable != DISABLE)) {
        return -1;
    }
    dsp2_cfg.fw_module_manual_mode[module] = enable;

    return 0;
}

BL_Fun_Type imgproc_get_fw_module_en(const img_param_module_t module)
{
    BL_Fun_Type enable = dsp2_cfg.fw_module_en[module];
    return enable;
}

int imgproc_set_fw_module_en(const img_param_module_t module, BL_Fun_Type enable)
{
    if ((enable != ENABLE) && (enable != DISABLE)) {
        return -1;
    }

    dsp2_cfg.fw_module_en[module] = enable;
    if (enable == ENABLE) imgproc_update_force();
    if (module == DSP2_ADJ_AE) {
        if (enable == DISABLE) {
            ae_set_mode((AE_MODE)AE_MODE_LOCK);
            dsp2_update.flag.ae = AE_MODE_LOCK;
        } else {
            ae_set_mode((AE_MODE)AE_MODE_AUTO);
            dsp2_update.flag.ae = AE_MODE_AUTO;
        }
     } else if (module == DSP2_ADJ_AWB) {
        if (enable == DISABLE) {
            awb_set_mode((AWB_MODE)AWB_MODE_LOCK);
            dsp2_update.flag.awb = AWB_MODE_LOCK;
        } else {
            awb_set_mode((AWB_MODE)AWB_MODE_AUTO);
            dsp2_update.flag.awb = AWB_MODE_AUTO;
        }
    }

    return 0;
}


int imgproc_set_2A_keep_reg(char* reg, BL_GAIN_DB gain_db, BL_EXPO_TIME expo_time, BL_COLOR_TEMP color_temp)
{
    if (strcmp(reg, "ISO") == 0) {//Current only for tunning tool with 100,200...6400
        dsp2_keep_cfg.iso_flag = 1;
        dsp2_keep_cfg.ae_gain = gain_db;
        dsp2_keep_cfg.ae_expo_time = expo_time;
        dsp2_keep_cfg.ae_sys_gain = (BL_GAIN_DB)(GAIN_DB_FLOAT_TO_INT(12.0) + gain_db);//(BL_GAIN_DB)(-GAIN_DB_FLOAT_TO_INT(GAIN_X_TO_DB((float)EXPO_TIME_1_100_SEC/exp + gain_db)o_time)) + gain_db);
    } else if (strcmp(reg, "CT") == 0) {
        dsp2_keep_cfg.ct_flag = 1;
        dsp2_keep_cfg.awb_ct = (BL_COLOR_TEMP)color_temp;
    } else {
        return -1;
    }

    return 0;
}

static bool imgproc_is_update_force()
{
    return ((0 != img_proc.update_force)? true: false);
}

static void imgproc_update_down()
{
    if (img_proc.update_force > 0) {
        img_proc.update_force--;
    }
}

static int imgproc_is_update_fps(ae_ss_conf_t *ss_conf)
{
    if ((ss_conf->enable) && (ss_conf->is_update)) {
        if (imgproc_update_fps_cb == NULL) {
            BL_LOGE("imgproc_is_update_fps: invalid imgproc_update_fps_cb \r\n");
            return -1;
        }
        if ((imgproc_chan_id < 0) || (imgproc_chan_id > 3)) {
            BL_LOGE("imgproc_is_update_fps: invalid imgproc_chan_id \r\n");
            return -1;
        }
        imgproc_update_fps_cb(imgproc_chan_id, (ss_conf->fps / 100));
    }

    return 0;
}

int imgproc_update_force()
{
    img_proc.update_force = 10;
    return 0;
}

int imgproc_set_module_enable(img_param_module_t module, BL_Fun_Type enable)
{
    if ((enable != ENABLE) && (enable != DISABLE)) {
        return -1;
    } else {
        img_proc.img_param_sw->state_tbl->state[module] = enable;
        if (module == DSP2_ADJ_AE) bl_set_AE_state(enable);
        else if (module == DSP2_ADJ_AWB) bl_set_AWB_state(enable);
    }
    return 0;
}

BL_Fun_Type imgproc_is_module_enable(img_param_module_t module)
{
    return (img_proc.img_param_sw->state_tbl->state)[module];
}

static uint32_t imgproc_is_module_update(uint32_t mask)
{
    return mask & dsp2_cfg.update_mask;
}

static void imgproc_set_module_update(uint32_t mask)
{
    dsp2_cfg.update_mask |= mask;
}

static void imgproc_clear_module_update()
{
    dsp2_cfg.update_mask = 0;
}

static void imgproc_set_reg()
{
    if (imgproc_is_module_update(IMG_UPDATE_MASK_BLC)) {
        blc_hw_update();
    }

    if (imgproc_is_module_update(IMG_UPDATE_MASK_DPC)) {
        dpc_hw_update();
    }

    if (imgproc_is_module_update(IMG_UPDATE_MASK_BNR)) {
        bnr_hw_update();
    }

    if (imgproc_is_module_update(IMG_UPDATE_MASK_LSC)) {
        lsc_hw_update();
    }

    if (imgproc_is_module_update(IMG_UPDATE_MASK_WB_GAIN)) {
        bl_set_RB_gain(&(dsp2_cfg.rb_gain));
    }

    if (imgproc_is_module_update(IMG_UPDATE_MASK_CCM)) {
        ccm_hw_update();
    }

    if (imgproc_is_module_update(IMG_UPDATE_MASK_GAMMA)) {
        gamma_hw_update();
    }

    if (imgproc_is_module_update(IMG_UPDATE_MASK_WDR)) {
        wdr_hw_update();
    }

    if (imgproc_is_module_update(IMG_UPDATE_MASK_SATURATION)) {
        sat_hw_update();
    }

    if (imgproc_is_module_update(IMG_UPDATE_MASK_YC)) {
        yc_hw_update();
    }

    if (imgproc_is_module_update(IMG_UPDATE_MASK_NR)) {
        nr_hw_update();
    }

    if (imgproc_is_module_update(IMG_UPDATE_MASK_EE)) {
        ee_hw_update();
    }

    if (imgproc_is_module_update(IMG_UPDATE_MASK_CS)) {
        cs_hw_update();
    }

    imgproc_clear_module_update();
}

static int imgproc_check_param_table()
{
    int ret = 1;

    ret *= (DSP2_TBL_CUSTOM_EV \
        == (img_proc.img_param->ae_tbl->header.table));
    ret *= (DSP2_TBL_CUSTOM_COLOR_TMPER \
        == (img_proc.img_param->awb_white_region_tbl->header.table));
    ret *= (DSP2_TBL_CUSTOM_COLOR_TMPER \
        == (img_proc.img_param->wb_bias_tbl->header.table));
    ret *= (DSP2_TBL_CUSTOM_COLOR_TMPER \
        == (img_proc.img_param->wb_info_tbl->header.table));
    ret *= (DSP2_TBL_AUTO_ISO \
        == (img_proc.img_param->blc_tbl->header.table));
    ret *= (DSP2_TBL_AUTO_ISO \
        == (img_proc.img_param->defect_corr_tbl->header.table));
    ret *= (DSP2_TBL_AUTO_ISO \
        == (img_proc.img_param->bnr_config_tbl->header.table));
    ret *= (DSP2_TBL_CUSTOM_COLOR_TMPER \
        == (img_proc.img_param->lens_shading_corr_tbl->header.table));
    ret *= (DSP2_TBL_CUSTOM_COLOR_TMPER \
        == (img_proc.img_param->color_corr_tbl->header.table));
    ret *= (DSP2_TBL_CUSTOM_EV \
        == (img_proc.img_param->gamma_corr_tbl->header.table));
    ret *= (DSP2_TBL_CUSTOM_EV \
        == (img_proc.img_param->wdr_config_tbl->header.table));
    ret *= (DSP2_TBL_AUTO_ISO \
        == (img_proc.img_param->saturation_tbl->header.table));
    ret *= (DSP2_TBL_AUTO_ISO \
        == (img_proc.img_param->yc_tbl->header.table));
    ret *= (DSP2_TBL_AUTO_ISO \
        == (img_proc.img_param->noise_reduction_tbl->header.table));
    ret *= (DSP2_TBL_AUTO_ISO \
        == (img_proc.img_param->edge_enhance_tbl->header.table));
    ret *= (DSP2_TBL_AUTO_ISO \
        == (img_proc.img_param->cs_tbl->header.table));

    return (ret == 1) ? 0 : -1;
}

static int imgproc_check_param_policy()
{
    int ret = 1;

    ret *= (DSP2_POL_INTERPL \
        == (img_proc.img_param->ae_tbl->header.policy));
    ret *= (DSP2_POL_INTERPL \
        == (img_proc.img_param->awb_white_region_tbl->header.policy));
    ret *= (DSP2_POL_INTERPL \
        == (img_proc.img_param->wb_bias_tbl->header.policy));
    ret *= (DSP2_POL_INTERPL \
        == (img_proc.img_param->wb_info_tbl->header.policy));
    ret *= (DSP2_POL_INTERPL \
        == (img_proc.img_param->blc_tbl->header.policy));
    ret *= (DSP2_POL_INTERPL \
        == (img_proc.img_param->defect_corr_tbl->header.policy));
    ret *= (DSP2_POL_INIT \
        == (img_proc.img_param->bnr_config_tbl->header.policy));
    ret *= (DSP2_POL_INTERPL \
        == (img_proc.img_param->lens_shading_corr_tbl->header.policy));
    ret *= (DSP2_POL_INTERPL \
        == (img_proc.img_param->color_corr_tbl->header.policy));
    ret *= (DSP2_POL_INTERPL \
        == (img_proc.img_param->gamma_corr_tbl->header.policy));
    ret *= (DSP2_POL_INTERPL \
        == (img_proc.img_param->wdr_config_tbl->header.policy));
    ret *= (DSP2_POL_INTERPL \
        == (img_proc.img_param->saturation_tbl->header.policy));
    ret *= (DSP2_POL_INTERPL \
        == (img_proc.img_param->yc_tbl->header.policy));
    ret *= (DSP2_POL_INTERPL \
        == (img_proc.img_param->noise_reduction_tbl->header.policy));
    ret *= (DSP2_POL_INTERPL \
        == (img_proc.img_param->edge_enhance_tbl->header.policy));
    ret *= (DSP2_POL_INTERPL \
        == (img_proc.img_param->cs_tbl->header.policy));

    return (ret == 1) ? 0 : -1;
}

static int img_module_ae()
{
    if (!imgproc_is_module_enable(DSP2_ADJ_AE)) {
        return -1;
    }

    ae_control();
    return 0;
}

static int img_update_ae_target(BL_GAIN_DB sys_gain, int *ae_target)
{
    DSP2_AE_SUB_ATTR sw_config;

    if (calc_ae_sw_config_by_sys_gain(sys_gain, &sw_config) == -1) return 0;
    *ae_target = sw_config.ae_target;

    return 0;
}

static int img_module_ae_target(int *ae_target)
{
    if (!imgproc_is_module_enable(DSP2_ADJ_AE)) {
        return -1;
    }

    if (dsp2_update.flag.sys_gain || imgproc_is_update_force()) {
        img_update_ae_target(dsp2_update.value.sys_gain, ae_target);
    }

    return 0;

}

static int img_update_awb(BL_GAIN_DB sys_gain)
{
    awb_set_sys_config(sys_gain);
    return 0;
}

static int img_module_awb()
{
    if (!imgproc_is_module_enable(DSP2_ADJ_AWB)) {
        return -1;
    }

    img_update_awb(dsp2_update.value.sys_gain);
    awb_control();
    return 0;
}
//AWB_ALGO_1
static int img_update_wb_gain(bl_dsp2_rb_gain_t *rb_gain, BL_COLOR_TEMP color_temp, bl_dsp2_rb_gain_t *rb_bias)
{
    if (!imgproc_is_module_enable(DSP2_ADJ_AWB)) {
        return -1;
    }

    imgproc_set_module_update(IMG_UPDATE_MASK_WB_GAIN);

    /* apply wb gain bias according to color temp thresh */
    if (color_temp <= WB_BIAS_CT_THRESH) {
        dsp2_cfg.rb_gain = *rb_gain;
    } else {
        dsp2_cfg.rb_gain.r_gain = DIV_ROUND(rb_gain->r_gain * rb_bias->r_gain, RGB_GAIN_1X);
        dsp2_cfg.rb_gain.b_gain = DIV_ROUND(rb_gain->b_gain * rb_bias->b_gain, RGB_GAIN_1X);
    }

    BL_LOGD("final wb gain: (%d, %d) -> (%d, %d)\r\n", rb_gain->r_gain, rb_gain->b_gain,
        dsp2_cfg.rb_gain.r_gain, dsp2_cfg.rb_gain.b_gain);

#if PRINT_FAST_CAP_TIMING
    //printf("gain %d, %d\r\n", final_rb_gain.r_gain, final_rb_gain.b_gain);
#endif

    return 0;
}
//AWB_ALGO_1
static int img_update_wb_bias(BL_GAIN_DB sys_gain, bl_dsp2_rb_gain_t *rb_bias)
{
    if (!imgproc_is_module_enable(DSP2_ADJ_AWB)) {
        return -1;
    }

    calc_wb_fw_config_by_sys_gain(sys_gain, rb_bias);

    /* should never reach here */
    BL_ABORT();
    return -1;
}

static int img_module_blc()
{
    if (!(imgproc_is_module_enable(DSP2_ADJ_BLC) && imgproc_get_fw_module_en(DSP2_ADJ_BLC))) {
        bl_dsp2_disable_blc_soft();
        return -1;
    }


    if (imgproc_get_fw_module_manual_mode(DSP2_ADJ_BLC)) {
        imgproc_set_module_update(IMG_UPDATE_MASK_BLC);
        blc_img_manual();
    } else if (dsp2_update.flag.iso || imgproc_is_update_force()) {
        imgproc_set_module_update(IMG_UPDATE_MASK_BLC);
        blc_img_update(dsp2_update.value.iso);
    }

    return 0;

}

static int img_module_dpc()
{
    if (!(imgproc_is_module_enable(DSP2_ADJ_DPC) && imgproc_get_fw_module_en(DSP2_ADJ_DPC))) {
        bl_set_DPC_state(DISABLE);
        return -1;
    }

    bl_set_DPC_state(ENABLE);
    if (imgproc_get_fw_module_manual_mode(DSP2_ADJ_DPC)) {
        dpc_img_manual();
        imgproc_set_module_update(IMG_UPDATE_MASK_DPC);
    } else if (dsp2_update.flag.iso || imgproc_is_update_force()) {
        dpc_img_update(dsp2_update.value.iso);
        imgproc_set_module_update(IMG_UPDATE_MASK_DPC);
    }

    return 0;
}

int img_module_bnr()
{
    if (!(imgproc_is_module_enable(DSP2_ADJ_BNR) && imgproc_get_fw_module_en(DSP2_ADJ_BNR))) {
        bl_set_BNR_state(DISABLE);
        return -1;
    }

    bl_set_BNR_state(ENABLE);
    if (imgproc_get_fw_module_manual_mode(DSP2_ADJ_BNR)) {
        bnr_img_manual();
        imgproc_set_module_update(IMG_UPDATE_MASK_BNR);
    } else if (dsp2_update.flag.iso || imgproc_is_update_force()) {
        bnr_img_update(dsp2_update.value.iso);
        imgproc_set_module_update(IMG_UPDATE_MASK_BNR);
    }

    return 0;

}

static int img_module_lsc()
{
    if (!(imgproc_is_module_enable(DSP2_ADJ_LSC) && imgproc_get_fw_module_en(DSP2_ADJ_LSC))) {
        bl_set_LSC_state(DISABLE);
        return -1;
    }

    bl_set_LSC_state(ENABLE);
    if (imgproc_get_fw_module_manual_mode(DSP2_ADJ_LSC)) {
        lsc_img_manual(dsp2_update.value.ct);
        imgproc_set_module_update(IMG_UPDATE_MASK_LSC);
    } else if (dsp2_update.flag.ct || imgproc_is_update_force()) {
        lsc_img_update(dsp2_update.value.ct);
        imgproc_set_module_update(IMG_UPDATE_MASK_LSC);
    }

    return 0;

}

static int img_module_ccm()
{
    if (!(imgproc_is_module_enable(DSP2_ADJ_CCM) && imgproc_get_fw_module_en(DSP2_ADJ_CCM))) {
        bl_set_CCM_state(DISABLE);
        return -1;
    }

    bl_set_CCM_state(ENABLE);
    if (imgproc_get_fw_module_manual_mode(DSP2_ADJ_CCM)) {
        ccm_img_manual();
        imgproc_set_module_update(IMG_UPDATE_MASK_CCM);
    } else if (dsp2_update.flag.ct || dsp2_update.flag.iso || imgproc_is_update_force()) {
        ccm_img_update(dsp2_update.value.ct, dsp2_update.value.iso);
        imgproc_set_module_update(IMG_UPDATE_MASK_CCM);
    }

    return 0;
}

static int img_module_gamma()
{
    if (!(imgproc_is_module_enable(DSP2_ADJ_GAMMA) && imgproc_get_fw_module_en(DSP2_ADJ_GAMMA))) {
        bl_set_GAMMA_state(DISABLE);
        return -1;
    }

    bl_set_GAMMA_state(ENABLE);
    if (imgproc_get_fw_module_manual_mode(DSP2_ADJ_GAMMA)) {
        gamma_img_manual();
        imgproc_set_module_update(IMG_UPDATE_MASK_GAMMA);
    } else if (dsp2_update.flag.sys_gain || imgproc_is_update_force()) {
        gamma_img_update(dsp2_update.value.sys_gain);
        imgproc_set_module_update(IMG_UPDATE_MASK_GAMMA);
    }

    return 0;
}

static int img_module_wdr()
{

    static int wdr_need_update = EXTRA_WDR_CONVERGE_FRAME_CNT;

    if (dsp2_update.flag.sys_gain){
        wdr_need_update = EXTRA_WDR_CONVERGE_FRAME_CNT;
    } else{
        if (wdr_need_update > 0)
            wdr_need_update--;
    }
    //printf("=====flag %d  ,  wdr_need_update %d \r\n", dsp2_update.flag.sys_gain, wdr_need_update);


    if (!(imgproc_is_module_enable(DSP2_ADJ_WDR) && imgproc_get_fw_module_en(DSP2_ADJ_WDR))) {
        bl_set_WDR_state(DISABLE);
        return -1;
    }

    bl_set_WDR_state(ENABLE);
    if (imgproc_get_fw_module_manual_mode(DSP2_ADJ_WDR)) {
        wdr_img_manual();
        imgproc_set_module_update(IMG_UPDATE_MASK_WDR);
    } else if (wdr_need_update || imgproc_is_update_force()) {
        wdr_img_update(dsp2_update.value.sys_gain);
        imgproc_set_module_update(IMG_UPDATE_MASK_WDR);
    }

    return 0;
}

static int img_module_saturation()
{
    if (!(imgproc_is_module_enable(DSP2_ADJ_SATURATION) && imgproc_get_fw_module_en(DSP2_ADJ_SATURATION))) {
        bl_dsp2_disable_saturation_soft();
        return -1;
    }

    if (imgproc_get_fw_module_manual_mode(DSP2_ADJ_SATURATION)) {
        imgproc_set_module_update(IMG_UPDATE_MASK_SATURATION);
        sat_img_manual();
    } else if (dsp2_update.flag.iso || imgproc_is_update_force()) {
        imgproc_set_module_update(IMG_UPDATE_MASK_SATURATION);
        sat_img_update(dsp2_update.value.iso);
    }
    return 0;

}

static int img_module_nr()
{
    if (!(imgproc_is_module_enable(DSP2_ADJ_NR) && imgproc_get_fw_module_en(DSP2_ADJ_NR))) {
        bl_dsp2_disable_nr_soft();
        return -1;
    }

    if (imgproc_get_fw_module_manual_mode(DSP2_ADJ_NR)) {
        imgproc_set_module_update(IMG_UPDATE_MASK_NR);
        nr_img_manual();
    } else if (dsp2_update.flag.iso || imgproc_is_update_force()) {
        imgproc_set_module_update(IMG_UPDATE_MASK_NR);
        nr_img_update(dsp2_update.value.iso);
    }
    return 0;
}

static int img_module_ee()
{
    if (!(imgproc_is_module_enable(DSP2_ADJ_EE) && imgproc_get_fw_module_en(DSP2_ADJ_EE))) {
        bl_set_EE_state(DISABLE);
        return -1;
    }

    bl_set_EE_state(ENABLE);
    if (imgproc_get_fw_module_manual_mode(DSP2_ADJ_EE)) {
        ee_img_manual();
        imgproc_set_module_update(IMG_UPDATE_MASK_EE);
    } else if (dsp2_update.flag.iso || imgproc_is_update_force()) {
        ee_img_update(dsp2_update.value.iso);
        imgproc_set_module_update(IMG_UPDATE_MASK_EE);
    }

    return 0;
}

static int img_module_cs()
{
    if (!(imgproc_is_module_enable(DSP2_ADJ_CS) && imgproc_get_fw_module_en(DSP2_ADJ_CS))) {
        bl_set_CS_state(DISABLE);
        return -1;
    }

    bl_set_CS_state(ENABLE);
    if (imgproc_get_fw_module_manual_mode(DSP2_ADJ_CS)) {
        cs_img_manual();
        imgproc_set_module_update(IMG_UPDATE_MASK_CS);
    } else if (dsp2_update.flag.iso || imgproc_is_update_force()) {
        cs_img_update(dsp2_update.value.iso);
        imgproc_set_module_update(IMG_UPDATE_MASK_CS);
    }

    return 0;
}

static int img_module_yc()
{
    if (!(imgproc_is_module_enable(DSP2_ADJ_YC) && imgproc_get_fw_module_en(DSP2_ADJ_YC))) {
        bl_dsp2_disable_yc_soft();
        return -1;
    }

    if (imgproc_get_fw_module_manual_mode(DSP2_ADJ_YC)) {
        imgproc_set_module_update(IMG_UPDATE_MASK_YC);
        yc_img_manual();
    } else if (dsp2_update.flag.iso || imgproc_is_update_force()) {
        imgproc_set_module_update(IMG_UPDATE_MASK_YC);
        yc_img_update(dsp2_update.value.iso);
    }
    return 0;

}


static void dsp2_stats_ready_cb(void *usrdata)
{
    BaseType_t xHigherPriorityTaskWoken;

#if PRINT_FAST_CAP_TIMING
    //printf("FF %d\r\n", xTaskGetTickCountFromISR());
#endif

    xHigherPriorityTaskWoken = pdFALSE;
    vTaskNotifyGiveFromISR(hdr, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

static int imgproc_is_boot_frame()
{
    if (0 != img_proc.start_skip_num && img_proc.start_skip_num-- > 0) {
        return 1;
    }

    return 0;
}


static int imgproc_is_skip_frame(int *count)
{
    if ((*count)++ < img_proc.skip_num - 1) {
        return 1;
    }

    *count = 0;
    return 0;
}

static void imgproc_reset_sensor_quick_mode()
{
    if (!sensor_is_quick_mode())
        return;

    if (img_proc.quick_mode_mask) {
        sensor_quick_mode_reset();
        img_proc.quick_mode_mask = 0;
    }
}

static void imgproc_set_interrupt(BL_Fun_Type state)
{
    if (DISABLE == state) {
        CPU_Interrupt_Disable(AE_STATS_IRQn);
        CPU_Interrupt_Disable(AE_HIST_STATS_IRQn);
        CPU_Interrupt_Disable(AWB_STATS_IRQn);
        CPU_Interrupt_Disable(AWB2_STATS_IRQn);
        CPU_Interrupt_Disable(AWB3_STATS_IRQn);
        CPU_Interrupt_Disable(WDR_STATS_IRQn);

        CPU_Interrupt_Disable(SEOF1_IRQn);
        CPU_Interrupt_Disable(SEOF2_IRQn);
        CPU_Interrupt_Disable(SEOF3_IRQn);
    }
    else {
        CPU_Interrupt_Enable(AE_STATS_IRQn);
        if (AWB_ALGO_1 == img_proc.awb_algo) {
            CPU_Interrupt_Enable(AWB_STATS_IRQn);
        }
        else if (AWB_ALGO_2 == img_proc.awb_algo) {
            CPU_Interrupt_Enable(AWB2_STATS_IRQn);
        }
        else if (AWB_ALGO_3 == img_proc.awb_algo) {
           CPU_Interrupt_Enable(AWB3_STATS_IRQn);
        }
        else {
            BL_LOGE("AWB algo NOT Support!\r\n");
        }
        CPU_Interrupt_Enable(WDR_STATS_IRQn);
        CPU_Interrupt_Enable(AE_HIST_STATS_IRQn);
        CPU_Interrupt_Enable(SEOF1_IRQn);
        CPU_Interrupt_Enable(SEOF2_IRQn);
    #if PRINT_FAST_CAP_TIMING
        CPU_Interrupt_Enable(SEOF3_IRQn);
    #endif
    }
}

static void imgproc_sw_reg_init(void)
{
    int i;

    ae_sw_init();
    awb_sw_init();
    blc_init();
    dpc_init();
    bnr_init();
    lsc_init();
    ccm_init();
    gamma_init();
    wdr_init();
    nr_init();
    ee_init();
    cs_init();
    yc_init();
    sat_init();

    af_init();

    for(i = 0; i < DSP2_ADJ_PARAM_NUM; i++) {
        imgproc_set_fw_module_en(i, img_proc.img_param_sw->state_tbl->state[i]);
        imgproc_set_fw_module_manual_mode(i, DISABLE);
    }

    /* Set default value of IQ */
    BL_GAIN_DB gain = 1536;
    BL_GAIN_DB sys_gain = 1536;
    BL_COLOR_TEMP color_temp = COLOR_TEMP_D65;

    blc_img_update(gain);
    dpc_img_update(gain);
    //bnr_img_update(gain);

    lsc_img_update(color_temp);
    ccm_img_update(color_temp, gain);

    gamma_img_update(sys_gain);
    wdr_img_update(sys_gain);

    sat_img_update(gain);
    yc_img_update(gain);
    ee_img_update(gain);
    nr_img_update(gain);
    cs_img_update(gain);

    imgproc_set_module_update(IMG_UPDATE_MASK_BLC);
    imgproc_set_module_update(IMG_UPDATE_MASK_DPC);
    //imgproc_set_module_update(IMG_UPDATE_MASK_BNR);
    imgproc_set_module_update(IMG_UPDATE_MASK_LSC);
    imgproc_set_module_update(IMG_UPDATE_MASK_CCM);
    imgproc_set_module_update(IMG_UPDATE_MASK_GAMMA);
    imgproc_set_module_update(IMG_UPDATE_MASK_WDR);
    imgproc_set_module_update(IMG_UPDATE_MASK_SATURATION);
    imgproc_set_module_update(IMG_UPDATE_MASK_YC);
    imgproc_set_module_update(IMG_UPDATE_MASK_NR);
    imgproc_set_module_update(IMG_UPDATE_MASK_EE);
    imgproc_set_module_update(IMG_UPDATE_MASK_CS);

    imgproc_set_reg();

}

int imgproc_set_ae_algo(AE_ALGO algo)
{
    if (algo < 0 || algo > AE_ALGO_NUM) {
        return -1;
    }

    img_proc_ae_algo = algo;
    return 0;
}

int imgproc_get_ae_algo(void)
{
    return img_proc_ae_algo;
}

int imgproc_set_awb_algo(AWB_ALGO algo)
{
    if (algo < 0 || algo > AWB_ALGO_NUM) {
        return -1;
    }
    img_proc_awb_algo = algo;
    return 0;
}

int imgproc_get_awb_algo(void)
{
    return img_proc_awb_algo;
}

int imgproc_set_flicker_mode(flicker_mode mode)
{
    if (mode < 0 || mode > FLICKER_MODE_NUM) {
        return -1;
    }
    img_proc_flicker_mode = mode;
    return 0;
}

int imgproc_get_flicker_mode(void)
{
    return img_proc_flicker_mode;
}

static void imgproc_show_algo_info(void)
{
    int ae_version = 0;
    int awb_version = 0;
    int wdr_version = 0;

    ae_get_algo_version(&ae_version);
    awb_get_algo_version(&awb_version);
    wdr_get_algo_version(&wdr_version);

    BL_LOGI("AE algo: %d, version: %d\r\n", imgproc_get_ae_algo(), ae_version);
    BL_LOGI("AWB algo: %d, version: %d\r\n", imgproc_get_awb_algo(), awb_version);
    BL_LOGI("WDR version: %d\r\n", wdr_version);
}

static int imgproc_win_init(bl_vin_config_t *vin_cfg)
{
    int ret;
    img_proc_cfg_t cfg;

    cfg.stats_cfg.act_win.width =  vin_cfg->act_win.width;
    cfg.stats_cfg.act_win.height = vin_cfg->act_win.height;
    cfg.stats_cfg.out_win.width =  vin_cfg->out_win.width;
    cfg.stats_cfg.out_win.height = vin_cfg->out_win.height;
    ret = imgproc_set_config(&cfg, vin_cfg->is_virtual);

    return ret;
}

static int imgproc_algo_register(void)
{
    if (ae_init(img_proc_ae_algo) < 0) return -1;
    if (awb_init(img_proc_awb_algo) < 0) return -1;
    imgproc_show_algo_info();

    return 0;
}

static int imgproc_cfg_init(void)
{
    int ret;

    memset(&img_proc, 0, sizeof(img_proc));
    memset(&dsp2_cfg, 0, sizeof(dsp2_cfg));
    memset(&dsp2_update, 0, sizeof(dsp2_update));
    memset(&dsp2_keep_cfg, -1, sizeof(dsp2_keep_cfg));
    memset(&img_proc_fps, 0, sizeof(img_proc_fps));

    ret = img_param_sw_get_module(&(img_proc.img_param_sw));
    if (-1 == ret) {
        BL_LOGE("improc: Get sensor param sw failed!\n");
    }

    ret = img_param_get_module(&(img_proc.img_param));
    if (-1 == ret) {
        BL_LOGE("improc: Get sensor param failed!\n");
    }

    ret = imgproc_check_param_table();
    if (-1 == ret) {
        BL_LOGE("improc: Please check module table!\n");
    }

    ret = imgproc_check_param_policy();
    if (-1 == ret) {
        BL_LOGE("improc: Please check module policy!\n");
    }

    img_proc.status = IMGPROC_INIT;
    img_proc.skip_num = IMG_PROC_SKIP_NUM;
    img_proc.start_skip_num  = IMG_START_SKIP_NUM;
    img_proc.ae_algo = img_proc_ae_algo;
    img_proc.awb_algo = img_proc_awb_algo;
    img_proc.quick_mode_mask = 1; // quick mode use only

    imgproc_set_interrupt(DISABLE);
    imgproc_sw_reg_init();

    //ir_board_config();
    //sensor_board_config();

    return 0;
}

int imgproc_init(bl_vin_config_t *vin_cfg)
{
    if (imgproc_bind_sensor_model(vin_cfg->sensor_name) < 0) {
        BL_LOGE("cannot match any IQ param to sensor model %s\r\n", vin_cfg->sensor_name);
        return -1;
    }

    if (imgproc_algo_register() < 0) {
        BL_LOGE("register auto algo failed\r\n");
        return -1;
    }

    if (imgproc_win_init(vin_cfg) < 0) {
        BL_LOGE("set win config failed\r\n");
        return -1;
    }

    if (imgproc_cfg_init() < 0) {
        BL_LOGE("sensor param init failed\r\n");
        return -1;
    }
    img_proc.is_virtual_sensor = vin_cfg->is_virtual;

    return 0;
}

int imgproc_bind_sensor_model(const char* sensor_name)
{
    int ret = -1;

    ret = img_param_load(sensor_name);
    if (ret == 0) {
        img_param_sw_load(sensor_name);
        img_param_calib_load(sensor_name);
    }

    return ret;
}

int imgproc_set_config(img_proc_cfg_t *cfg, bool is_virtual_sensor)
{
    ae_config_t  ae_cfg;
    awb_config_t awb_cfg;
    wdr_config_t wdr_cfg;

    memcpy(&(ae_cfg.stats_cfg),  &(cfg->stats_cfg), sizeof(aaa_stats_cfg_t));
    memcpy(&(awb_cfg.stats_cfg), &(cfg->stats_cfg), sizeof(aaa_stats_cfg_t));
    memcpy(&(wdr_cfg.stats_cfg), &(cfg->stats_cfg), sizeof(aaa_stats_cfg_t));

    if (ae_config(&ae_cfg, is_virtual_sensor) < 0)
        return -1;

    if (awb_config(&awb_cfg, is_virtual_sensor) < 0)
        return -1;

    if (wdr_config(&wdr_cfg, is_virtual_sensor) < 0)
        return -1;

    return 0;
}

void vImageControlTask(void *pvParameters)
{
    int skip_cnt = img_proc.skip_num;

    ae_info_t  *ae_info;
    awb_info_t *awb_info;
    ae_get_info(&ae_info);
    awb_get_info(&awb_info);

    hdr = xTaskGetCurrentTaskHandle();

    //imgproc_update_force();
    //imgproc_set_init_only_module();
    bl_dsp2_stats_ready_config(dsp2_stats_ready_cb, NULL);

    /* interrupts should be enabled after scheduler is started,
        otherwise deferring any work in ISR to Daemon task will assert */

    imgproc_set_interrupt(ENABLE);

#if VIRTUAL_LOOP
    while (1) {
        if (img_proc.is_virtual_sensor) vTaskDelay(1);
#endif
    while (!img_proc.stop_imgproc_flag) {
#if PRINT_FAST_CAP_TIMING
        TickType_t ae_stats_done_time;
#endif

        BL_LOGD("wait event ...\r\n");
        ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
        BL_LOGD("wait event done.\r\n");

        imgproc_reset_sensor_quick_mode();

        if (imgproc_is_skip_frame(&skip_cnt)) {
            continue;
        }

#if PRINT_FAST_CAP_TIMING
        ae_stats_done_time = xTaskGetTickCount();
#endif
        if (img_proc_fps.fps_flag == 1) img_proc_fps.cur_frame_num++;

        img_module_ae();
        img_module_awb();

        if (imgproc_is_boot_frame()) {
            continue;
        }

        imgproc_is_update_fps(&ae_info->ae_slow_shutter_conf);

         if (ae_info->expo_time_update || imgproc_is_update_force()) {
             if (ae_info->ae_mode != AE_MODE_DBG_VIRTUAL) {
                 sensor_set_exposure(ae_info->expo_time);
             }
         }
         if (ae_info->iso_update || imgproc_is_update_force()) {
             if (ae_info->ae_mode != AE_MODE_DBG_VIRTUAL) {
                 sensor_set_gain(ae_info->iso);
             }
 #if PRINT_FAST_CAP_TIMING
             printf("ae upd delay %lu\r\n", xTaskGetTickCount() - ae_stats_done_time);
 #endif
         }
        if (img_proc.is_virtual_sensor) {
            ae_info->iso_update = 1;
            ae_info->expo_time_update = 1;
            ae_info->sys_gain_update = 1;
            awb_info->ct_update = 1;

            printf("====== ae_info->iso_update %d, ae_info->iso %d\r\n",ae_info->iso_update, ae_info->iso);
            printf("====== ae_info->expo_time_update %d, ae_info->expo_time %d\r\n",ae_info->expo_time_update, ae_info->expo_time);
            printf("====== ae_info->sys_gain_updatev %d, ae_info->sys_gain %d\r\n",ae_info->sys_gain_update, ae_info->sys_gain);
            printf("====== awb_info->ct_update %d, awb_info->color_temp %d\r\n",awb_info->ct_update, awb_info->color_temp);
        }
        imgproc_set_update_state(ISO_FLAG, ae_info->iso_update, ae_info->iso);
        imgproc_set_update_state(EXPO_TIME_FLAG, ae_info->expo_time_update, ae_info->expo_time);
        imgproc_set_update_state(SYS_GAIN_FLAG, ae_info->sys_gain_update, ae_info->sys_gain);
        imgproc_set_update_state(CT_FLAG, awb_info->ct_update, awb_info->color_temp);

        // Use for tool when ae/awb is enable with auto, then regist needs to update
        if (dsp2_update.flag.ae == AE_MODE_AUTO) {
            imgproc_set_update_state(ISO_FLAG, true, UNUPDATE_VALUE);
            imgproc_set_update_state(SYS_GAIN_FLAG, true, UNUPDATE_VALUE);
            dsp2_update.flag.ae = AE_MODE_INVALID;
        } else if ((dsp2_update.flag.ae == AE_MODE_LOCK) && (dsp2_keep_cfg.iso_flag == 1)) {
            imgproc_set_update_state(ISO_FLAG, true, dsp2_keep_cfg.ae_gain);
            imgproc_set_update_state(SYS_GAIN_FLAG, true, dsp2_keep_cfg.ae_sys_gain);
            dsp2_keep_cfg.iso_flag = 0;
        }

        if (dsp2_update.flag.awb == AWB_MODE_AUTO) {
            imgproc_set_update_state(CT_FLAG, true, UNUPDATE_VALUE);
            dsp2_update.flag.awb = AWB_MODE_NUM;
        } else if ((dsp2_update.flag.awb == AWB_MODE_LOCK) && (dsp2_keep_cfg.ct_flag == 1)) {
            imgproc_set_update_state(CT_FLAG, true, dsp2_keep_cfg.awb_ct);
            dsp2_keep_cfg.ct_flag = 0;
        }

        if (AWB_ALGO_1 == img_proc.awb_algo) {
            if (ae_info->sys_gain_update || imgproc_is_update_force()) {
                img_update_wb_bias(ae_info->sys_gain, &(awb_info->rb_bias));
            }
            if (awb_info->rb_gain_update || imgproc_is_update_force()) {
                img_update_wb_gain(&(awb_info->rb_gain), awb_info->color_temp, &(awb_info->rb_bias));
            }
        }

        img_module_ae_target(&(ae_info->luma_target));

        img_module_blc();
        img_module_dpc();
        img_module_bnr();

        img_module_lsc();
        img_module_ccm();

        img_module_gamma();
        img_module_wdr();

        img_module_saturation();
        img_module_yc();
        img_module_ee();
        img_module_nr();
        img_module_cs();

        imgproc_set_reg();

#if 0
        bl_dsp2_af_stats_t af_stats;
        bl_get_AF_stats(&af_stats);
        printf("=========AF %d, %d, %d, %d \r\n",af_stats.wa_hpf1_sum, af_stats.wa_hpf2_sum, af_stats.wb_hpf1_sum, af_stats.wb_hpf2_sum);
#endif

        imgproc_update_down();
#if USE_IR_LED_BOARD
        /* control day/night mode based on signal from IR LED board */
        imgproc_night_mode_enable(bl_gpio_input_get_value(GPIO_IR_BOARD_IRC) ? true : false);
#endif

#if PERFORMANCE_MONITOR
        do_frame_rate_stats("img handl", &ae_handl_cnt, FRM_CNT_FOR_ONE_STATS, &ae_handl_start_time);
#endif

#if VIRTUAL_LOOP
    if (img_proc.is_virtual_sensor) img_proc.stop_imgproc_flag = 1;
    }
    if (!img_proc.is_virtual_sensor && img_proc.stop_imgproc_flag == 0) break;
#endif
    }
}

void imgproc_night_mode_enable(bool enable)
{
    static bool pre_state;

    if (enable != pre_state) {
        ir_led_en(enable);
        bl_dsp2_set_day_night_mode(enable ? BL_NIGHT_MODE : BL_DAY_MODE);
        ir_cut_switch(enable);
        pre_state = enable;
        BL_LOGI("night mode %d\r\n", enable);
    }
}

int imgproc_start(void)
{
    if ((img_proc.status == IMGPROC_INIT)) {
        img_proc.status = IMGPROC_RUN;
        img_proc.stop_imgproc_flag = 0;
        if (hdr == NULL) aos_task_new("Image_control", vImageControlTask, NULL, 4096);
    }

    if (img_proc.is_virtual_sensor) {
        img_proc.status = IMGPROC_RUN;
        img_proc.stop_imgproc_flag = 0;
    }

    return 0;
}

int imgproc_stop(void)
{
    if (hdr == NULL) img_proc.status = IMGPROC_STOP;
    else img_proc.status = IMGPROC_PAUSE;
    img_proc.stop_imgproc_flag = 1;

    return 0;
}

int imgproc_status(int     *status)
{
    if (img_proc.status >= IMGPROC_STATUS_NUM) {
        BL_LOGE("imgproc_status is over status numer %d\r\n", img_proc.status);
        return -1;
    }
    *status = img_proc.status;
    return 0;

}

uint32_t imgproc_get_fps(void)
{
    uint32_t sec_time = 1;
    imgproc_fps_run(sec_time);
    return img_proc_fps.fps;
}

void imgproc_update_fps_register(bl_dsp2_update_fps_cb *cb)
{
    imgproc_update_fps_cb = *cb;
}


