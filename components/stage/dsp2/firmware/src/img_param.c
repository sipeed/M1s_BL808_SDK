#include <string.h>
#include "img_param.h"

extern BL_IMG_PARAM_DESC_T _ld_bl_img_param_desc_start;
extern BL_IMG_PARAM_DESC_T _ld_bl_img_param_desc_end;

#define PARAM_IDX_MIN  0
#define PARAM_MODULE_IDX_MAX        (DSP2_ADJ_PARAM_NUM - 1)
#define PARAM_AE_TARGET_IDX_MAX     (MAX_ENTRY_NUM_AE_SYS_GAIN_AUTO - 1)
#define PARAM_AE_METERING_IDX_MAX   (AE_METERING_TBL_NUM - 1)
#define PARAM_AE_SPEED_LEVEL_MAX    (5)
#define PARAM_AWB_SPEED_LEVEL_MAX   (5)
#define PARAM_AWB_PREF_IDX_MAX      (MAX_ENTRY_NUM_AE_SYS_GAIN_AUTO - 1)
#define PARAM_BLC_IDX_MAX           (MAX_ENTRY_NUM_AE_ISO_AUTO - 1)
#define PARAM_DPC_IDX_MAX           (MAX_ENTRY_NUM_AE_ISO_AUTO - 1)
#define PARAM_BNR_IDX_MAX           (MAX_ENTRY_NUM_AE_ISO_AUTO - 1)
#define PARAM_LSC_IDX_MAX           (MAX_ENTRY_NUM_AWB_CT_AUTO - 1)
#define PARAM_CCM_IDX_MAX           (MAX_ENTRY_NUM_AWB_CT_AUTO - 1)
#define PARAM_CCM_CW_IDX_MAX        (MAX_ENTRY_NUM_AE_ISO_AUTO - 1)
#define PARAM_GAMMA_IDX_MAX         (MAX_ENTRY_NUM_AE_SYS_GAIN_AUTO - 1)
#define PARAM_GAMMA_CAL_IDX_MAX     (MAX_ENTRY_NUM_GAMMA_IDX_AUTO - 1)
#define PARAM_WDR_IDX_MAX           (MAX_ENTRY_NUM_AE_SYS_GAIN_AUTO - 1)
#define PARAM_SAT_IDX_MAX           (MAX_ENTRY_NUM_AE_ISO_AUTO - 1)
#define PARAM_YC_IDX_MAX            (MAX_ENTRY_NUM_AE_ISO_AUTO - 1)
#define PARAM_NR_IDX_MAX            (MAX_ENTRY_NUM_AE_ISO_AUTO - 1)
#define PARAM_EE_IDX_MAX            (MAX_ENTRY_NUM_AE_ISO_AUTO - 1)
#define PARAM_CS_IDX_MAX            (MAX_ENTRY_NUM_AE_ISO_AUTO - 1)

static int load_inited = 0;
static BL_IMG_PARAM_DESC_T *img_param = NULL;
static BL_IMG_PARAM_SW_DESC_T *img_param_sw = NULL;
static BL_IMG_PARAM_SW_BIN_DESC_T *img_param_sw_init = NULL;
static BL_IMG_PARAM_CALIB_BIN_DESC_T *img_param_calib = NULL;

#if 0
typedef struct _img_param_lut {
    BL_SENSOR_UID_E sensor_uid;
    BL_IMG_PARAM_DESC_T *img_param;
} img_param_lut_t;

static const img_param_lut_t img_param_lut[] = {
    {SENSOR_UID_SC1245, &sc1245_img_param},
    {SENSOR_UID_SC2232, &sc2232_img_param},
    {SENSOR_UID_OV9732, &ov9732_img_param},
};

static BL_IMG_PARAM_DESC_T* find_img_param(BL_SENSOR_UID_E sensor_uid)
{
    int i;
    for (i = 0; i < sizeof(img_param_lut)/sizeof(img_param_lut[0]); i++) {
        if (sensor_uid == img_param_lut[i].sensor_uid) {
            return img_param_lut[i].img_param;
        }
    }

    return NULL;
}
#endif

int img_param_init(BL_IMG_PARAM_DESC_T *imgParam)
{
    img_param = imgParam;
    return 0;
}

static int img_param_get_index(int value, int min, int max)
{
    int index = value;
    if (!is_param_valid(index, min, max)) {
        clip_param_range(&index, min, max);
        // BL_LOGE("img_param_get_index: invalid param idx %d, clip to %d\r\n", value, index);
    }

    return index;
}

/*********** calib tbl ************************************************************************************************/
int img_param_free_calib_buffer(void)
{
    if (NULL != img_param_calib) free(img_param_calib);
    return 0;
}

int img_param_calib_load(const char* sensor_name)
{
    img_param_free_calib_buffer();

    // alloc memory for pointer
    img_param_calib = malloc(sizeof(BL_IMG_PARAM_CALIB_BIN_DESC_T));
    memset(img_param_calib, 0, sizeof(BL_IMG_PARAM_CALIB_BIN_DESC_T));

    img_param_calib->wb_info_tbl.wb_info = malloc(sizeof(wb_info_t) * MAX_ENTRY_NUM_AWB_CT_AUTO);
    memset(img_param_calib->wb_info_tbl.wb_info, 0, sizeof(wb_info_t) * MAX_ENTRY_NUM_AWB_CT_AUTO);

    img_param_calib->lsc_cal_tbl.container = malloc(sizeof(lsc_cal_t) * MAX_ENTRY_NUM_AWB_CT_AUTO);
    memset(img_param_calib->lsc_cal_tbl.container, 0, sizeof(lsc_cal_t) * MAX_ENTRY_NUM_AWB_CT_AUTO);

    //copy bl_fw to calib bin
    memcpy(&img_param_calib->name, img_param->name, sizeof(char) * 16);
    memcpy(&img_param_calib->wb_info_tbl, img_param->wb_info_tbl, sizeof(wb_info_container_t));
    memcpy(img_param_calib->wb_info_tbl.wb_info, img_param->wb_info_tbl->wb_info, sizeof(wb_info_t) * img_param->wb_info_tbl->num_wb_info);

    memcpy(&img_param_calib->wb3_cal_tbl, img_param->wb3_cal_tbl, sizeof(wb3_container_cal_t));
    memcpy(&img_param_calib->blc_tbl, img_param_sw->blc_tbl, sizeof(blc_container_sw_t));
    memcpy(&img_param_calib->dpc_cal_tbl, img_param->dpc_cal_tbl, sizeof(dpc_container_cal_t));

    int lsc_cal_num = img_param->lsc_cal_tbl->cal_num;
    memcpy(&img_param_calib->lsc_cal_tbl, img_param->lsc_cal_tbl, sizeof(lsc_container_cal_t));
    memcpy(img_param_calib->lsc_cal_tbl.container, img_param->lsc_cal_tbl->container, sizeof(lsc_container_cal_t) * lsc_cal_num);
    img_param_calib->lsc_cal_tbl.cal_num = lsc_cal_num;

    int ccm_cal_num = get_ccm_sw_tbl_num();
    memcpy(&img_param_calib->ccm_cal_tbl.container, img_param_sw->ccm_tbl->container, sizeof(DSP2_CCM_PARAM) * ccm_cal_num);
    img_param_calib->ccm_cal_tbl.cal_num = ccm_cal_num;

    memcpy(&img_param_calib->gamma_cal_tbl, img_param_sw->gamma_cal_tbl, sizeof(gamma_container_cal_t));

    img_param_sw->blc_tbl = &img_param_calib->blc_tbl;
    img_param_sw->ccm_tbl = &img_param_calib->ccm_cal_tbl;
    img_param_sw->gamma_cal_tbl = &img_param_calib->gamma_cal_tbl;

    print_cal_tbl();
    return 0;

}

int img_param_calib_get_wb_info(int param_idx, wb_info_t **wb_info)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, img_param_calib->wb_info_tbl.num_wb_info-1);
    *wb_info = &img_param_calib->wb_info_tbl.wb_info[index];

    return 0;
}

int img_param_calib_set_wb_info(const wb_info_t *wb_info_cal, int wb_info_num)
{
    memcpy(img_param_calib->wb_info_tbl.wb_info, wb_info_cal, sizeof(wb_info_t) * wb_info_num);
    return 0;
}

int img_param_calib_get_wb_info_num(void)
{
    return img_param_calib->wb_info_tbl.num_wb_info;
}

int img_param_calib_get_awb(wb3_cal_bin_t **wb3_cal)
{
    *wb3_cal = &img_param_calib->wb3_cal_tbl.wb3_cal.bin;

    return 0;
}

int img_param_calib_set_awb(const wb3_cal_bin_t *wb3_cal)
{
    memcpy(&img_param_calib->wb3_cal_tbl.wb3_cal.bin, wb3_cal, sizeof(wb3_cal_bin_t));
    return 0;
}

int img_param_calib_get_blc(int param_idx, blc_cal_t **blc)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, PARAM_BLC_IDX_MAX);
    *blc = &img_param_calib->blc_tbl.container[index];

    return 0;
}

int img_param_calib_set_blc(const blc_cal_t *blc_cal)
{
    memcpy(&img_param_calib->blc_tbl.container, blc_cal, sizeof(blc_cal_t) * MAX_ENTRY_NUM_AE_ISO_AUTO);
    return 0;
}

int img_param_calib_get_dpc(int param_idx, dpc_cal_t **bpc_cal)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, PARAM_DPC_IDX_MAX);
    *bpc_cal = &img_param_calib->dpc_cal_tbl.container[index];

    return 0;
}

int img_param_calib_set_dpc(const dpc_cal_t *bpc_cal)
{
    memcpy(&img_param_calib->dpc_cal_tbl.container, bpc_cal, sizeof(dpc_cal_t) * MAX_ENTRY_NUM_AE_ISO_AUTO);
    return 0;
}

int img_param_calib_get_lsc(int param_idx, lsc_cal_t **lsc_cal)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, PARAM_LSC_IDX_MAX);
    *lsc_cal = &img_param_calib->lsc_cal_tbl.container[index];

    return 0;
}

int img_param_calib_set_lsc(const lsc_cal_t *lsc_cal, int lsc_num)
{
    memcpy(img_param_calib->lsc_cal_tbl.container, lsc_cal, sizeof(lsc_cal_t) * lsc_num);
    return 0;
}

int img_param_calib_get_lsc_num()
{
    return img_param_calib->lsc_cal_tbl.cal_num;
}

int img_param_calib_set_lsc_num(int num)
{
    int cal_num = img_param_get_index(num, PARAM_IDX_MIN, PARAM_CCM_IDX_MAX);
    img_param_calib->lsc_cal_tbl.cal_num = cal_num;

    return 0;
}

int img_param_calib_get_ccm(int param_idx, ccm_cal_t **ccm_cal)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, PARAM_CCM_IDX_MAX);
    *ccm_cal = &img_param_calib->ccm_cal_tbl.container[index];

    return 0;
}

int img_param_calib_set_ccm(const ccm_cal_t *ccm_cal, int ccm_num)
{
    memcpy(img_param_calib->ccm_cal_tbl.container, ccm_cal, sizeof(ccm_cal_t) * ccm_num);

    return 0;
}

int img_param_calib_get_ccm_num()
{
    return img_param_calib->ccm_cal_tbl.cal_num;
}

int img_param_calib_set_ccm_num(int num)
{
    int cal_num = img_param_get_index(num, PARAM_IDX_MIN, PARAM_CCM_IDX_MAX);
    img_param_calib->ccm_cal_tbl.cal_num = cal_num;

    return 0;
}


int img_param_calib_get_gamma(int param_idx, gamma_cal_t **gamma_cal)
{
    if (param_idx < 0) {
        *gamma_cal = &img_param_calib->gamma_cal_tbl.container;
    } else if (param_idx < MAX_ENTRY_NUM_GAMMA_IDX_AUTO) {
        *gamma_cal = &img_param_calib->gamma_cal_tbl.container[param_idx];
    } else {
        return -1;
    }
    return 0;
}

int img_param_calib_set_gamma(int param_idx, const gamma_cal_t *gamma_cal)
{
    if (param_idx < 0) {
        memcpy(&img_param_calib->gamma_cal_tbl.container, gamma_cal, sizeof(gamma_cal_t) * MAX_ENTRY_NUM_GAMMA_IDX_AUTO);
    } else if (param_idx < MAX_ENTRY_NUM_GAMMA_IDX_AUTO) {
        memcpy(&img_param_calib->gamma_cal_tbl.container[param_idx], gamma_cal, sizeof(gamma_cal_t));
    } else {
        return -1;
    }
    return 0;
}

void print_cal_tbl(void)
{
    int i,j;

    BL_LOGD("[OK] img_param_cal_load name %s\r\n", img_param_calib->name);


    BL_LOGD("[OK] img_param_get_wb_info_cal num: %u,\r\n", img_param_calib->wb_info_tbl.num_wb_info);
    for (i = 0; i < img_param_calib->wb_info_tbl.num_wb_info; i++) {
        BL_LOGD("[OK] img_param_get_wb_info_cal cfg[%d]: %d, %d\r\n", i,
            (int)img_param_calib->wb_info_tbl.wb_info[i].rb_gain.r_gain,
            (int)img_param_calib->wb_info_tbl.wb_info[i].rb_gain.b_gain
            );
    }

    for (i = 0; i < MAX_ENTRY_NUM_AWB3_CAL_BIN_NUM; i++) {
            BL_LOGD("[OK] img_param_get_awb_cal cfg[%d]: %u,\r\n", i, img_param_calib->wb3_cal_tbl.wb3_cal.bin[i]);
    }

    for (i = 0; i < MAX_ENTRY_NUM_AE_ISO_AUTO; i++) {
        BL_LOGD("[OK] img_param_get_blc_cal cfg[%d]: %u,\r\n", i, img_param_calib->blc_tbl.container[i].black_level);
    }

    for (i = 0; i < MAX_ENTRY_NUM_AE_ISO_AUTO; i++) {
        BL_LOGD("[OK] img_param_get_dpc_cal cfg[%d]: %d, %d\r\n", i, 
            (int)img_param_calib->dpc_cal_tbl.container[i].defect_thr_1,
            (int)img_param_calib->dpc_cal_tbl.container[i].defect_thr_2
            );
    }

    BL_LOGD("[OK] img_param_get_lsc_cal num: %u,\r\n", img_param_calib->lsc_cal_tbl.cal_num);
    for (i = 0; i < img_param_calib->lsc_cal_tbl.cal_num; i++) {
        BL_LOGD("[OK] img_param_get_lsc_cal cfg[%d]: %d, %d\r\n", i,
            (int)img_param_calib->lsc_cal_tbl.container[i].strength,
            (int)img_param_calib->lsc_cal_tbl.container[i].color_temp
            );
            BL_LOGD("[OK] img_param_get_lsc_cal cfg[%d]: ", i);
            for (j = 0; j < LSC_COEF_NUM; j++) BL_LOGD("%d, ",(int)img_param_calib->lsc_cal_tbl.container[i].lsc_coef_r.coef[j]);
            BL_LOGD("\r\n");
            BL_LOGD("[OK] img_param_get_lsc_cal cfg[%d]: ", i);
            for (j = 0; j < LSC_COEF_NUM; j++) BL_LOGD("%d, ",(int)img_param_calib->lsc_cal_tbl.container[i].lsc_coef_g.coef[j]);
            BL_LOGD("\r\n");
            BL_LOGD("[OK] img_param_get_lsc_cal cfg[%d]: ", i);
            for (j = 0; j < LSC_COEF_NUM; j++) BL_LOGD("%d, ",(int)img_param_calib->lsc_cal_tbl.container[i].lsc_coef_b.coef[j]);
            BL_LOGD("\r\n");
            BL_LOGD("[OK] img_param_get_lsc_cal cfg[%d]: %d, %d, %d\r\n", i,
            (int)img_param_calib->lsc_cal_tbl.container[i].lsc_max.max_r,
            (int)img_param_calib->lsc_cal_tbl.container[i].lsc_max.max_g,
            (int)img_param_calib->lsc_cal_tbl.container[i].lsc_max.max_b
            );
    }

    BL_LOGD("[OK] img_param_get_ccm_cal num: %d,\r\n", (int)img_param_calib->ccm_cal_tbl.cal_num);
    for (i = 0; i < MAX_ENTRY_NUM_AWB_CT_AUTO; i++) {
        BL_LOGD("[OK] img_param_get_ccm_cal cfg[%d]: ", i);
        for (j = 0; j < CCM_COEF_NUM; j++) {
            BL_LOGD(" %d,", img_param_calib->ccm_cal_tbl.container[i].coef[j]);
        }
        BL_LOGD("\r\n");
        BL_LOGD("[OK] img_param_get_ccm_cal cfg[%d]: %d,\r\n", i, (int)img_param_calib->ccm_cal_tbl.container[i].color_temp);
    }
    
    for (i = 0; i < MAX_ENTRY_NUM_GAMMA_IDX_AUTO; i++) {
        BL_LOGD("[OK] img_param_get_gamma_cal cfg[%d]:", i);
        for (j = 0; j < GAMMA_COEF_NUM; j++) {
            BL_LOGD(" %d,", img_param_calib->gamma_cal_tbl.container[i].gamma_curve.coef[j]);
        }
        BL_LOGD("\r\n");
        BL_LOGD("[OK] img_param_get_gamma_cal idx[%d]: %d,\r\n", i, img_param_calib->gamma_cal_tbl.container[i].idx);
    }
}

/*********** fw tbl ************************************************************************************************/
int img_param_load(const char* sensor_name)
{
    BL_IMG_PARAM_DESC_T *start, *end;

    start = &_ld_bl_img_param_desc_start;
    end = &_ld_bl_img_param_desc_end;

    while (start < end) {
        BL_LOGI("try matching the img param desc [%s]\r\n", start->name);
        if(0 == strcmp(sensor_name, start->name)) {
            img_param = start;
            return 0;
        }
        start++;
    }

    return -1;
}

int img_param_get_module(const BL_IMG_PARAM_DESC_T **module)
{
    if (NULL == img_param) {
        BL_LOGE("img_param not init!");
        return -1;
    }

    *module = img_param;
    return 0;
}

int img_param_get_states(const BL_Fun_Type **state)
{
    *state = img_param->state_tbl->state;

    return 0;
}

int img_param_get_ae_agc_db_tbl(ae_agc_db_tbl **cfg)
{
    *cfg = &img_param->ae_init_tbl->max_agc_db_tbl;

    return 0;
}

int img_param_get_ae_slow_shutter_conf(ae_slow_shutter_conf_t **cfg)
{
    *cfg = &img_param->ae_init_tbl->slow_shutter_conf;

    return 0;
}

int img_param_get_manual_wb_info(int param_idx, const wb_info_t **wb_info)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, img_param->wb_info_tbl->num_wb_info-1);
    *wb_info = &img_param->wb_info_tbl->wb_info[index];

    return 0;
}

int img_param_get_num_manual_wb_info(void)
{
    return img_param->wb_info_tbl->num_wb_info;
}

int img_param_get_wb3_cal(const wb3_cal_bin_t **wb3_cal)
{
    *wb3_cal = &img_param->wb3_cal_tbl->wb3_cal.bin;

    return 0;
}

int img_param_get_wb_bias(int param_idx, const wb_bais_t **wb_bias)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, img_param->wb_bias_tbl->num_wb_bias-1);
    *wb_bias = &img_param->wb_bias_tbl->wb_bias[index];

    return 0;
}

int img_param_get_num_wb_bias(void)
{
    return img_param->wb_bias_tbl->num_wb_bias;
}

int img_param_get_white_region(int param_idx, const white_region_t **region)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, img_param->awb_white_region_tbl->num_white_region-1);
    *region = &img_param->awb_white_region_tbl->white_region[index];

    return 0;
}

int img_param_get_num_white_region(void)
{
    return img_param->awb_white_region_tbl->num_white_region;
}

int img_param_get_dpc_trans(const dpc_trans_tbl_t **trans_tbl, int *tbl_num)
{
    *trans_tbl = &img_param->dpc_trans_tbl->strength_tbl;
    *tbl_num = (int)sizeof(img_param->dpc_trans_tbl->strength_tbl) / (int)sizeof(img_param->dpc_trans_tbl->strength_tbl[0]);

    return 0;
}

int img_param_get_wdr_trans(const wdr_trans_tbl_t **trans_tbl, int *tbl_num)
{
    *trans_tbl = &img_param->wdr_trans_tbl->cs_strength_tbl;
    *tbl_num = (int)sizeof(img_param->wdr_trans_tbl->cs_strength_tbl) / (int)sizeof(img_param->wdr_trans_tbl->cs_strength_tbl[0]);

    return 0;
}

int img_param_get_cs_trans(const cs_trans_tbl_t **trans_tbl, int *tbl_num)
{
    *trans_tbl = &img_param->cs_trans_tbl->strength_tbl;
    *tbl_num = (int)sizeof(img_param->cs_trans_tbl->strength_tbl) / (int)sizeof(img_param->cs_trans_tbl->strength_tbl[0]);

    return 0;
}

/*********** fw tbl end ************************************************************************************************/

/*********** sw tbl ************************************************************************************************/
int img_param_malloc_sw_param_init_buffer(void)
{
    if (load_inited == 1) {
        return 0;
    }

    img_param_free_sw_param_init_buffer();
    img_param_sw_init = malloc(sizeof(BL_IMG_PARAM_SW_BIN_DESC_T));
    memset(img_param_sw_init, 0, sizeof(BL_IMG_PARAM_SW_BIN_DESC_T));

    load_inited = 1;
    return load_inited;
}

int img_param_free_sw_param_init_buffer(void)
{
    if (NULL != img_param_sw_init) free(img_param_sw_init);
    return 0;
}

int img_param_free_sw_param_buffer(void)
{
    if (NULL != img_param_sw) free(img_param_sw);
    return 0;
}

int img_param_get_sw_bin_Addr(uint32_t *addr)
{
    *addr = img_param_sw_init;
    return 0;
}

int img_param_sw_tbl_init(void)
{
    img_param_malloc_sw_param_init_buffer();

    memcpy(img_param_sw_init->name, img_param->name, sizeof(char) * 16);
    memcpy(&img_param_sw_init->state_tbl, img_param->state_tbl, sizeof(img_param_state_container_t));
    memcpy(&img_param_sw_init->ae_tbl, &img_param->ae_tbl->ae_sw, sizeof(ae_container_sw_t));
    memcpy(&img_param_sw_init->awb_tbl.preference_enable , &img_param->awb_tbl->awb_sw.preference_enable, sizeof(uint8_t));
    memcpy(&img_param_sw_init->awb_tbl.special_color_enable , &img_param->awb_tbl->awb_sw.special_color_enable, sizeof(uint8_t));
    memcpy(img_param_sw_init->awb_tbl.preference_gain, img_param->awb_tbl->awb_sw.preference_gain, sizeof(awb_bais_t) * MAX_ENTRY_NUM_AE_SYS_GAIN_AUTO);
    memcpy(img_param_sw_init->awb_tbl.special_color_info, img_param->awb_tbl->awb_sw.special_color_info, sizeof(awb_special_color_t) * MAX_ENTRY_NUM_AWB3_SPECIAL_COLOR);
    memcpy(&img_param_sw_init->awb_tbl.speed_level , &img_param->awb_tbl->awb_sw.speed_level, sizeof(uint8_t));
    memcpy(&img_param_sw_init->blc_tbl, &img_param->blc_tbl->black_lvl_corr, sizeof(blc_container_sw_t));
    memcpy(&img_param_sw_init->dpc_tbl, &img_param->defect_corr_tbl->defect_corr, sizeof(dpc_container_sw_t));
    memcpy(&img_param_sw_init->bnr_tbl, &img_param->bnr_config_tbl->bnr_config, sizeof(bnr_container_sw_t));
    memcpy(&img_param_sw_init->lsc_tbl, &img_param->lens_shading_corr_tbl->lens_shading_corr, sizeof(lsc_container_sw_t));
    memcpy(&img_param_sw_init->ccm_tbl.container, img_param->color_corr_tbl->color_corr->container, sizeof(DSP2_CCM_PARAM) * img_param->color_corr_tbl->num_color_corr);
    memcpy(&img_param_sw_init->ccm_tbl.num_ccm, &img_param->color_corr_tbl->num_color_corr, sizeof(int));
    memcpy(&img_param_sw_init->ccm_cw_tbl.container, &img_param->ccm_cw_tbl->container, sizeof(ccm_cw_t) * MAX_ENTRY_NUM_AE_ISO_AUTO);
    memcpy(&img_param_sw_init->gamma_cal_tbl, img_param->gamma_cal_tbl, sizeof(gamma_container_cal_t));
    memcpy(&img_param_sw_init->gamma_tbl, &img_param->gamma_corr_tbl->gamma_corr, sizeof(gamma_container_sw_t));
    memcpy(&img_param_sw_init->wdr_tbl, &img_param->wdr_config_tbl->wdr_config, sizeof(wdr_container_sw_t));
    memcpy(&img_param_sw_init->wdr_manual_conf.enable , &img_param->wdr_manual_conf->enable, sizeof(int));
    memcpy(&img_param_sw_init->wdr_manual_conf.lowlight_weight_conf , &img_param->wdr_manual_conf->lowlight_weight_conf, sizeof(wdr_lowlight_weight_conf_t));
    memcpy(&img_param_sw_init->wdr_manual_conf.tone_curve_container , &img_param->wdr_manual_conf->tone_curve_container, sizeof(wdr_tone_curve_conf_t) * MAX_ENTRY_NUM_WDR_IDX_AUTO);
    memcpy(&img_param_sw_init->sat_tbl, &img_param->saturation_tbl->saturation, sizeof(sat_container_sw_t));
    memcpy(&img_param_sw_init->yc_tbl, &img_param->yc_tbl->ycCfg, sizeof(yc_container_sw_t));
    memcpy(&img_param_sw_init->nr_tbl, &img_param->noise_reduction_tbl->noise_reduction, sizeof(nr_container_sw_t));
    memcpy(&img_param_sw_init->ee_tbl, &img_param->edge_enhance_tbl->edgeEnhance, sizeof(ee_container_sw_t));
    memcpy(&img_param_sw_init->ee_luma_wgt_tbl, &img_param->edge_enhance_tbl->lumaWgtTbl, sizeof(ee_luma_wgt_t));
    memcpy(&img_param_sw_init->cs_tbl, &img_param->cs_tbl->csCfg, sizeof(cs_container_sw_t));

    BL_LOGI("try matching the img param sw img_param_sw_init 0x%x\r\n", (uint32_t)img_param_sw_init);
    BL_LOGI("try matching the img param sw desc [%s]\r\n", img_param_sw_init->name);

    return 0;

}
int img_param_sw_load(const char* sensor_name)
{

    img_param_free_sw_param_buffer();
    img_param_sw = malloc(sizeof(BL_IMG_PARAM_SW_DESC_T));
    memset(img_param_sw, 0, sizeof(BL_IMG_PARAM_SW_DESC_T));

    if ((load_inited == 0) || (strcmp(img_param_sw_init->name, "") == 0)) img_param_sw_tbl_init();

    if(0 == strcmp(sensor_name, img_param_sw_init->name)) {
        img_param_sw->name = img_param_sw_init->name;
        img_param_sw->state_tbl = &img_param_sw_init->state_tbl;
        img_param_sw->ae_tbl = &img_param_sw_init->ae_tbl;
        img_param_sw->awb_tbl = &img_param_sw_init->awb_tbl;
        img_param_sw->blc_tbl = &img_param_sw_init->blc_tbl;
        img_param_sw->dpc_tbl = &img_param_sw_init->dpc_tbl;
        img_param_sw->bnr_tbl = &img_param_sw_init->bnr_tbl;
        img_param_sw->lsc_tbl = &img_param_sw_init->lsc_tbl;
        img_param_sw->ccm_tbl = &img_param_sw_init->ccm_tbl;
        memcpy(&img_param_sw->ccm_tbl->num_ccm, &img_param_sw_init->ccm_tbl.num_ccm, sizeof(int));
        img_param_sw->ccm_cw_tbl = &img_param_sw_init->ccm_cw_tbl;
        img_param_sw->gamma_cal_tbl = &img_param_sw_init->gamma_cal_tbl;
        img_param_sw->gamma_tbl = &img_param_sw_init->gamma_tbl;
        img_param_sw->wdr_tbl = &img_param_sw_init->wdr_tbl;
        img_param_sw->wdr_manual_conf = &img_param_sw_init->wdr_manual_conf;
        img_param_sw->sat_tbl = &img_param_sw_init->sat_tbl;
        img_param_sw->yc_tbl = &img_param_sw_init->yc_tbl;
        img_param_sw->nr_tbl = &img_param_sw_init->nr_tbl;
        img_param_sw->ee_tbl = &img_param_sw_init->ee_tbl;
        img_param_sw->ee_luma_wgt_tbl = &img_param_sw_init->ee_luma_wgt_tbl;
        img_param_sw->cs_tbl = &img_param_sw_init->cs_tbl;

        print_sw_tbl();
        return 0;
    }

    print_sw_tbl();
    return -1;
}

int img_param_sw_get_module(const BL_IMG_PARAM_SW_DESC_T **module)
{
    if (NULL == img_param_sw) {
        BL_LOGE("img_param sw not init!");
        return -1;
    }

    *module = img_param_sw;
    return 0;
}

int img_param_sw_get_states(int param_idx, BL_Fun_Type **state)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, PARAM_MODULE_IDX_MAX);
    *state= &img_param_sw->state_tbl->state[index];

    return 0;
}

int img_param_sw_set_states(int param_idx, const BL_Fun_Type *state)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, PARAM_MODULE_IDX_MAX);
    memcpy(&img_param_sw->state_tbl->state[index], state, sizeof(BL_Fun_Type));

    return 0;
}

int img_param_sw_get_ae(int param_idx, DSP2_AE_SUB_ATTR **cfg)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, PARAM_AE_TARGET_IDX_MAX);
    *cfg = &img_param_sw->ae_tbl->container[index];

    return 0;
}

int img_param_sw_set_ae(int param_idx, const DSP2_AE_SUB_ATTR *cfg)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, PARAM_AE_TARGET_IDX_MAX);
    memcpy(&img_param_sw->ae_tbl->container[index], cfg, sizeof(DSP2_AE_SUB_ATTR));

    return 0;
}

int img_param_sw_get_ae_highlight_weight_en(int *en)
{
    *en = img_param_sw->ae_tbl->highlight_weight_conf.enable;

    return 0;
}

int img_param_sw_set_ae_highlight_weight_en(const int en)
{
    img_param_sw->ae_tbl->highlight_weight_conf.enable = en;
    return 0;
}

int img_param_sw_get_ae_highlight_weight(int param_idx, DSP2_AE_HIGHLIGHT_WEIGHT **cfg)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, PARAM_AE_TARGET_IDX_MAX);
    *cfg = &img_param_sw->ae_tbl->highlight_weight_conf.highlight_weight[index];

    return 0;
}

int img_param_sw_set_ae_highlight_weight(int param_idx, const DSP2_AE_HIGHLIGHT_WEIGHT *cfg)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, PARAM_AE_TARGET_IDX_MAX);
    memcpy(&img_param_sw->ae_tbl->highlight_weight_conf.highlight_weight[index], cfg, sizeof(DSP2_AE_HIGHLIGHT_WEIGHT));

    return 0;
}

int img_param_sw_get_ae_metering_tbl(int param_idx, DSP2_AE_METERING_TBL **cfg)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, PARAM_AE_METERING_IDX_MAX);
    *cfg = &img_param_sw->ae_tbl->metering_tbl[index];

    return 0;
}

int img_param_sw_set_ae_metering_tbl(int param_idx, const DSP2_AE_METERING_TBL *cfg)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, PARAM_AE_METERING_IDX_MAX);
    memcpy(&img_param_sw->ae_tbl->metering_tbl[index], cfg, sizeof(DSP2_AE_METERING_TBL));

    return 0;
}

int img_param_sw_get_ae_highlight_weight_conf(DSP2_AE_HIGHLIGHT_WEIGHT_CONF **cfg)
{
    *cfg = &img_param_sw->ae_tbl->highlight_weight_conf;

    return 0;
}

int img_param_sw_set_ae_highlight_weight_conf(const DSP2_AE_HIGHLIGHT_WEIGHT_CONF *cfg)
{
    memcpy(&img_param_sw->ae_tbl->highlight_weight_conf, cfg, sizeof(DSP2_AE_HIGHLIGHT_WEIGHT_CONF));

    return 0;
}

int img_param_sw_get_ae_metering_mode(int *cfg)
{
    *cfg = img_param_sw->ae_tbl->metering_mode;

    return 0;
}

int img_param_sw_set_ae_metering_mode(const int cfg)
{
    int index = img_param_get_index(cfg, PARAM_IDX_MIN, PARAM_AE_METERING_IDX_MAX);
    memcpy(&img_param_sw->ae_tbl->metering_mode, &index, sizeof(uint8_t));

    return 0;
}

int img_param_sw_get_ae_speed_level(int *cfg)
{
    *cfg = img_param_sw->ae_tbl->speed_level;

    return 0;
}

int img_param_sw_set_ae_speed_level(const int cfg)
{
    int index = img_param_get_index(cfg, PARAM_IDX_MIN, PARAM_AE_SPEED_LEVEL_MAX);
    memcpy(&img_param_sw->ae_tbl->speed_level, &index, sizeof(uint8_t));

    return 0;
}

int img_param_sw_get_awb_preference_en(int *en)
{
    *en = img_param_sw->awb_tbl->preference_enable;

    return 0;
}

int img_param_sw_set_awb_preference_en(const int en)
{
    img_param_sw->awb_tbl->preference_enable = en;

    return 0;
}

int img_param_sw_get_awb_special_color_en(int *en)
{
    *en = img_param_sw->awb_tbl->special_color_enable;

    return 0;
}

int img_param_sw_set_awb_special_color_en(const int en)
{
    img_param_sw->awb_tbl->special_color_enable = en;

    return 0;
}

int img_param_sw_get_awb_preference_gain(int param_idx, awb_bais_t **cfg)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, PARAM_AWB_PREF_IDX_MAX);
    *cfg = &img_param_sw->awb_tbl->preference_gain[index];

    return 0;
}

int img_param_sw_set_awb_preference_gain(int param_idx, const awb_bais_t *cfg)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, PARAM_AWB_PREF_IDX_MAX);
    memcpy(&img_param_sw->awb_tbl->preference_gain[index], cfg, sizeof(awb_bais_t));

    return 0;
}

int img_param_sw_get_awb_special_color(int param_idx, awb_special_color_t **cfg)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, MAX_ENTRY_NUM_AWB3_SPECIAL_COLOR);
    *cfg = &img_param_sw->awb_tbl->special_color_info[index];

    return 0;
}

int img_param_sw_set_awb_special_color(int param_idx, const awb_special_color_t *cfg)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, MAX_ENTRY_NUM_AWB3_SPECIAL_COLOR);
    memcpy(&img_param_sw->awb_tbl->special_color_info[index], cfg, sizeof(awb_special_color_t));

    return 0;
}

int img_param_sw_get_awb_speed_level(int *cfg)
{
    *cfg = img_param_sw->awb_tbl->speed_level;

    return 0;
}

int img_param_sw_set_awb_speed_level(const int cfg)
{
    int index = img_param_get_index(cfg, PARAM_IDX_MIN, PARAM_AWB_SPEED_LEVEL_MAX);
    memcpy(&img_param_sw->awb_tbl->speed_level, &index, sizeof(uint8_t));

    return 0;
}

int img_param_sw_get_blc(int param_idx, DSP2_BLC_PARAM **cfg)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, PARAM_BLC_IDX_MAX);
    *cfg = &img_param_sw->blc_tbl->container[index];

    return 0;
}

int img_param_sw_set_blc(int param_idx, const DSP2_BLC_PARAM *cfg)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, PARAM_BLC_IDX_MAX);
    memcpy(&img_param_sw->blc_tbl->container[index], cfg, sizeof(DSP2_BLC_PARAM));

    return 0;
}

int img_param_sw_get_dpc(int param_idx, DSP2_DPC_PARAM **cfg)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, PARAM_DPC_IDX_MAX);
    *cfg = &img_param_sw->dpc_tbl->container[index];

    return 0;
}

int img_param_sw_set_dpc(int param_idx, const DSP2_DPC_PARAM *cfg)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, PARAM_DPC_IDX_MAX);
    memcpy(&img_param_sw->dpc_tbl->container[index], cfg, sizeof(DSP2_DPC_PARAM));

    return 0;
}

int img_param_sw_get_bnr(int param_idx, DSP2_BNR_PARAM **cfg)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, PARAM_BNR_IDX_MAX);
    *cfg = &img_param_sw->bnr_tbl->container[index];

    return 0;
}

int img_param_sw_set_bnr(int param_idx, const DSP2_BNR_PARAM *cfg)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, PARAM_BNR_IDX_MAX);
    memcpy(&img_param_sw->bnr_tbl->container[index], cfg, sizeof(DSP2_BNR_PARAM));

    return 0;
}

int img_param_sw_get_lsc(int param_idx, DSP2_LSC_PARAM **cfg)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, PARAM_LSC_IDX_MAX);
    *cfg = &img_param_sw->lsc_tbl->container[index];

    return 0;
}

int img_param_sw_set_lsc(int param_idx, const DSP2_LSC_PARAM *cfg)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, PARAM_LSC_IDX_MAX);
    memcpy(&img_param_sw->lsc_tbl->container[index], cfg, sizeof(DSP2_LSC_PARAM));

    return 0;
}

int img_param_sw_get_ccm(int param_idx, DSP2_CCM_PARAM **cfg)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, PARAM_CCM_IDX_MAX);
    *cfg = &img_param_sw->ccm_tbl->container[index];

    return 0;
}

int img_param_sw_set_ccm(int param_idx, const DSP2_CCM_PARAM *cfg)
{
    int num_ccm = img_param_sw->ccm_tbl->num_ccm;
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, num_ccm - 1);
    memcpy(&img_param_sw->ccm_tbl->container[index], cfg, sizeof(DSP2_CCM_PARAM));

    return 0;
}

int img_param_sw_get_ccm_color_weight(int param_idx, ccm_cw_t **cfg)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, PARAM_CCM_CW_IDX_MAX);
    *cfg = &img_param_sw->ccm_cw_tbl->container[index];

    return 0;
}

int img_param_sw_set_ccm_color_weight(int param_idx, const ccm_cw_t *cfg)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, PARAM_CCM_CW_IDX_MAX);
    memcpy(&img_param_sw->ccm_cw_tbl->container[index], cfg, sizeof(ccm_cw_t));

    return 0;
}

int img_param_sw_get_gamma_cal(int param_idx, gamma_cal_t **cfg)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, PARAM_GAMMA_CAL_IDX_MAX);
    *cfg = &img_param_sw->gamma_cal_tbl->container[index];

    return 0;
}

int img_param_sw_set_gamma_cal(int param_idx, const gamma_cal_t *cfg)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, PARAM_GAMMA_CAL_IDX_MAX);
    memcpy(&img_param_sw->gamma_cal_tbl->container[index], cfg, sizeof(gamma_cal_t));

    return 0;
}


int img_param_sw_get_gamma(int param_idx, DSP2_GAMMA_PARAM **cfg)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, PARAM_GAMMA_IDX_MAX);
    *cfg = &img_param_sw->gamma_tbl->container[index];

    return 0;
}

int img_param_sw_set_gamma(int param_idx, const DSP2_GAMMA_PARAM *cfg)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, PARAM_GAMMA_IDX_MAX);
    memcpy(&img_param_sw->gamma_tbl->container[index], cfg, sizeof(DSP2_GAMMA_PARAM));

    return 0;
}

int img_param_sw_get_wdr(int param_idx, DSP2_WDR_PARAM **cfg)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, PARAM_WDR_IDX_MAX);
    *cfg = &img_param_sw->wdr_tbl->container[index];

    return 0;
}

int img_param_sw_set_wdr(int param_idx, const DSP2_WDR_PARAM *cfg)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, PARAM_WDR_IDX_MAX);
    memcpy(&img_param_sw->wdr_tbl->container[index], cfg, sizeof(DSP2_WDR_PARAM));

    return 0;
}

int img_param_sw_get_wdr_lowlight_weight_conf(wdr_lowlight_weight_conf_t **cfg)
{
    *cfg = &img_param_sw->wdr_manual_conf->lowlight_weight_conf;

    return 0;
}

int img_param_sw_set_wdr_lowlight_weight_conf(const wdr_lowlight_weight_conf_t *cfg)
{
    memcpy(&img_param_sw->wdr_manual_conf->lowlight_weight_conf, cfg, sizeof(wdr_lowlight_weight_conf_t));

    return 0;
}

int img_param_sw_get_wdr_lowlight_weight(int param_idx, wdr_lowlight_weight_t **cfg)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, PARAM_WDR_IDX_MAX);
    *cfg = &img_param_sw->wdr_manual_conf->lowlight_weight_conf.lowlight_weight[index];

    return 0;
}

int img_param_sw_set_wdr_lowlight_weight(int param_idx, const wdr_lowlight_weight_t *cfg)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, PARAM_WDR_IDX_MAX);
     memcpy(&img_param_sw->wdr_manual_conf->lowlight_weight_conf.lowlight_weight[index], cfg, sizeof(wdr_lowlight_weight_t));

    return 0;
}

int img_param_sw_get_wdr_tone_curve_conf(int param_idx, wdr_tone_curve_conf_t **cfg)
{
    if (param_idx < 0) {
        *cfg = &img_param_sw->wdr_manual_conf->tone_curve_container;
    } else if (param_idx < MAX_ENTRY_NUM_WDR_IDX_AUTO) {
        *cfg = &img_param_sw->wdr_manual_conf->tone_curve_container[param_idx];
    } else {
        return -1;
    }
    return 0;
}

int img_param_sw_set_wdr_tone_curve_conf(int param_idx, const wdr_tone_curve_conf_t *cfg)
{
    if (param_idx < 0) {
        memcpy(&img_param_sw->wdr_manual_conf->tone_curve_container, cfg, sizeof(wdr_tone_curve_conf_t) * MAX_ENTRY_NUM_WDR_IDX_AUTO);
    } else if (param_idx < MAX_ENTRY_NUM_WDR_IDX_AUTO) {
        memcpy(&img_param_sw->wdr_manual_conf->tone_curve_container[param_idx], cfg, sizeof(wdr_tone_curve_conf_t));
    } else {
        return -1;
    }

    return 0;
}

int img_param_sw_get_wdr_tone_curve_en(int *en)
{
    *en = img_param_sw->wdr_manual_conf->enable;
    return 0;
}

int img_param_sw_set_wdr_tone_curve_en(const int en)
{
    img_param_sw->wdr_manual_conf->enable = en;

    return 0;
}

int img_param_sw_get_sat(int param_idx, DSP2_SAT_PARAM **cfg)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, PARAM_SAT_IDX_MAX);
    *cfg = &img_param_sw->sat_tbl->container[index];

    return 0;
}

int img_param_sw_set_sat(int param_idx, const DSP2_SAT_PARAM *cfg)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, PARAM_SAT_IDX_MAX);
    memcpy(&img_param_sw->sat_tbl->container[index], cfg, sizeof(DSP2_SAT_PARAM));

    return 0;
}

int img_param_sw_get_yc(int param_idx, DSP2_YC_PARAM **cfg)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, PARAM_YC_IDX_MAX);
    *cfg = &img_param_sw->yc_tbl->container[index];
    return 0;
}

int img_param_sw_set_yc(int param_idx, const DSP2_YC_PARAM *cfg)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, PARAM_YC_IDX_MAX);
    memcpy(&img_param_sw->yc_tbl->container[index], cfg, sizeof(DSP2_YC_PARAM));
    return 0;
}

int img_param_sw_get_nr(int param_idx, DSP2_NR_PARAM **cfg)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, PARAM_NR_IDX_MAX);
    *cfg = &img_param_sw->nr_tbl->container[index];

    return 0;
}

int img_param_sw_set_nr(int param_idx, const DSP2_NR_PARAM *cfg)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, PARAM_NR_IDX_MAX);
    memcpy(&img_param_sw->nr_tbl->container[index], cfg, sizeof(DSP2_NR_PARAM));

    return 0;
}

int img_param_sw_get_ee_over_sht_en(int *en)
{
    *en = (int)img_param_sw->ee_tbl->over_sht_en;

    return 0;
}

int img_param_sw_set_ee_over_sht_en(const int en)
{
   img_param_sw->ee_tbl->over_sht_en = (BL_UINT8)en;

    return 0;
}

int img_param_sw_get_ee(int param_idx, DSP2_EE_PARAM **cfg)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, PARAM_NR_IDX_MAX);
    *cfg = &img_param_sw->ee_tbl->container[index];

    return 0;
}

int img_param_sw_set_ee(int param_idx, const DSP2_EE_PARAM *cfg)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, PARAM_NR_IDX_MAX);
    memcpy(&img_param_sw->ee_tbl->container[index], cfg, sizeof(DSP2_EE_PARAM));

    return 0;
}

int img_param_sw_get_ee_luma_weight(DSP2_EE_LUMA_WEIGHT **cfg)
{

    *cfg = &img_param_sw->ee_luma_wgt_tbl->lumaWgtTbl;

    return 0;
}

int img_param_sw_set_ee_luma_weight(const DSP2_EE_LUMA_WEIGHT *cfg)
{
    memcpy(&img_param_sw->ee_luma_wgt_tbl->lumaWgtTbl, cfg, sizeof(ee_luma_wgt_t));

    return 0;
}

int img_param_sw_get_cs(int param_idx, DSP2_CS_PARAM **cfg)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, PARAM_CS_IDX_MAX);
    *cfg = &img_param_sw->cs_tbl->container[index];

    return 0;
}

int img_param_sw_set_cs(int param_idx, const DSP2_CS_PARAM *cfg)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, PARAM_CS_IDX_MAX);
    memcpy(&img_param_sw->cs_tbl->container[index], cfg, sizeof(DSP2_CS_PARAM));

    return 0;
}

int get_lsc_sw_tbl_num(void)
{
    return MAX_ENTRY_NUM_AWB_CT_AUTO;
}

int get_ccm_sw_tbl_num(void)
{
    return img_param_sw->ccm_tbl->num_ccm;
}

int get_gamma_sw_tbl_num(void)
{
    return MAX_ENTRY_NUM_AE_SYS_GAIN_AUTO;
}

int get_wdr_sw_tbl_num(void)
{
    return MAX_ENTRY_NUM_AE_SYS_GAIN_AUTO;
}

void print_sw_tbl(void)
{
    int i,j,x;

    BL_LOGD("[OK] img_param_sw_load name %s\r\n", img_param_sw->name);

    for (i = 0; i < DSP2_ADJ_PARAM_NUM; i++) {
        int val = img_param_sw->state_tbl->state[i];
        BL_LOGD("[OK] img_param_sw_get_states cfg[%d]: %d,\r\n", i, val);
    }

    for (i = 0; i < MAX_ENTRY_NUM_AE_SYS_GAIN_AUTO; i++) {
        BL_LOGD("[OK] img_param_get_ae_sw cfg[%d]: %u\r\n", i, img_param_sw->ae_tbl->container[i].ae_target);
    }

    for (x = 0; x < AE_METERING_TBL_NUM; x++) {
        BL_LOGD("[OK] img_param_get_ae_sw metering_tbl[%d]:\r\n", x);
        for (j = 0; j < AE_STATS_GRID_NUM_Y; j++) {
            for (i = 0; i < AE_STATS_GRID_NUM_X; i++) {
                BL_LOGD("%u, ", img_param_sw->ae_tbl->metering_tbl[x].coef[j * AE_STATS_GRID_NUM_X + i]);
            }
            BL_LOGD("\r\n");
        }
    }
    BL_LOGD("[OK] img_param_get_ae_sw highlight weight en: %d,\r\n", img_param_sw->ae_tbl->highlight_weight_conf.enable);
    for (i = 0; i < MAX_ENTRY_NUM_AE_SYS_GAIN_AUTO; i++) {
        BL_LOGD("[OK] img_param_get_ae_sw highlight weight[%d]: %u, %u, %u,\r\n", i,
            img_param_sw->ae_tbl->highlight_weight_conf.highlight_weight[i].idx[0],
            img_param_sw->ae_tbl->highlight_weight_conf.highlight_weight[i].idx[1],
            img_param_sw->ae_tbl->highlight_weight_conf.highlight_weight[i].idx[2]);
    }
    BL_LOGD("[OK] img_param_get_ae_sw highlight_weight conf: %u, %u, {%u, %u, %u, %u,}\r\n", 
        img_param_sw->ae_tbl->highlight_weight_conf.roi_start,img_param_sw->ae_tbl->highlight_weight_conf.roi_end,
        img_param_sw->ae_tbl->highlight_weight_conf.thr[0],img_param_sw->ae_tbl->highlight_weight_conf.thr[1],
        img_param_sw->ae_tbl->highlight_weight_conf.thr[2],img_param_sw->ae_tbl->highlight_weight_conf.thr[3]);
    BL_LOGD("[OK] img_param_get_ae_sw metering mode: %u,\r\n", img_param_sw->ae_tbl->metering_mode);
    BL_LOGD("[OK] img_param_get_ae_sw speed_levl: %u,\r\n", img_param_sw->ae_tbl->speed_level);

    BL_LOGD("[OK] img_param_get_awb_sw preference en: %u,\r\n", img_param_sw->awb_tbl->preference_enable);
    BL_LOGD("[OK] img_param_get_awb_sw special_color en: %u,\r\n", img_param_sw->awb_tbl->special_color_enable);
    for (i = 0; i < MAX_ENTRY_NUM_AE_SYS_GAIN_AUTO; i++) {
        BL_LOGD("[OK] img_param_get_awb_sw preference_gain[%d]: (%d, %d), (%d, %d), (%d, %d)\r\n", i,
            img_param_sw->awb_tbl->preference_gain[i].bais[0].r_gain,img_param_sw->awb_tbl->preference_gain[i].bais[0].b_gain,
            img_param_sw->awb_tbl->preference_gain[i].bais[1].r_gain,img_param_sw->awb_tbl->preference_gain[i].bais[1].b_gain,
            img_param_sw->awb_tbl->preference_gain[i].bais[2].r_gain,img_param_sw->awb_tbl->preference_gain[i].bais[2].b_gain
            );
    }
    for (i = 0; i < MAX_ENTRY_NUM_AWB3_SPECIAL_COLOR; i++) {
        BL_LOGD("[OK] img_param_get_awb_sw special color conf [%d]: %d, %d %d\r\n", i,
            img_param_sw->awb_tbl->special_color_info[i].r_gain,img_param_sw->awb_tbl->special_color_info[i].b_gain,
            img_param_sw->awb_tbl->special_color_info[i].weight);
    }
    BL_LOGD("[OK] img_param_get_awb_sw speed_levl: %u,\r\n", img_param_sw->awb_tbl->speed_level);

    for (i = 0; i < MAX_ENTRY_NUM_AE_ISO_AUTO; i++) {
        BL_LOGD("[OK] img_param_get_blc_sw cfg[%d]: %u,\r\n", i, img_param_sw->blc_tbl->container[i].black_level);
    }

    for (i = 0; i < MAX_ENTRY_NUM_AE_ISO_AUTO; i++) {
        BL_LOGD("[OK] img_param_get_dpc_sw cfg[%d]: %d,\r\n", i, (uint8_t)img_param_sw->dpc_tbl->container[i].strength);
    }

    for (i = 0; i < MAX_ENTRY_NUM_AE_ISO_AUTO; i++) {
        BL_LOGD("[OK] img_param_get_bnr_sw cfg[%d]: %d,\r\n", i, (uint16_t)img_param_sw->bnr_tbl->container[i].strength);
    }

    for (i = 0; i < MAX_ENTRY_NUM_AWB_CT_AUTO; i++) {
        BL_LOGD("[OK] img_param_get_lsc_sw cfg[%d]: %d, %d\r\n", i,
            (int)img_param_sw->lsc_tbl->container[i].strength,
            (int)img_param_sw->lsc_tbl->container[i].color_temp
            );
    }
    
    BL_LOGD("[OK] img_param_get_ccm_sw num: %d,\r\n", (uint16_t)img_param_sw->ccm_tbl->num_ccm);
    for (i = 0; i < MAX_ENTRY_NUM_AWB_CT_AUTO; i++) {
        BL_LOGD("[OK] img_param_get_ccm_sw cfg[%d]: ", i);
        for (j = 0; j < CCM_COEF_NUM; j++) {
            BL_LOGD(" %d,", img_param_sw->ccm_tbl->container[i].coef[j]);
        }
        BL_LOGD("\r\n");
        BL_LOGD("[OK] img_param_get_ccm_sw cfg[%d]: %d,\r\n", i, (int)img_param_sw->ccm_tbl->container[i].color_temp);
    }
    for (i = 0; i < MAX_ENTRY_NUM_AE_ISO_AUTO; i++) {
            BL_LOGD("[OK] img_param_get_ccm_cw_sw cfg[%d]: %u,\r\n", i, img_param_sw->ccm_cw_tbl->container[i].color_weight);
    }

    for (i = 0; i < MAX_ENTRY_NUM_GAMMA_IDX_AUTO; i++) {
        BL_LOGD("[OK] img_param_get_gamma_cal cfg[%d]:", i);
        for (j = 0; j < GAMMA_COEF_NUM; j++) {
            BL_LOGD(" %d,", img_param_sw->gamma_cal_tbl->container[i].gamma_curve.coef[j]);
        }
        BL_LOGD("\r\n");
        BL_LOGD("[OK] img_param_get_gamma_cal idx[%d]: %d,\r\n", i, img_param_sw->gamma_cal_tbl->container[i].idx);
    }

    for (i = 0; i < MAX_ENTRY_NUM_AE_SYS_GAIN_AUTO; i++) {
        BL_LOGD("[OK] img_param_get_gamma_sw cfg[%d]: %d,\r\n", i, img_param_sw->gamma_tbl->container[i].idx);
    }

    for (i = 0; i < MAX_ENTRY_NUM_AE_SYS_GAIN_AUTO; i++) {
        BL_LOGD("[OK] img_param_get_wdr_sw cfg[%d]: %d, %d, %d, %d, %d, \r\n", i,
            img_param_sw->wdr_tbl->container[i].cs_strength,
            img_param_sw->wdr_tbl->container[i].curve_weight,
            img_param_sw->wdr_tbl->container[i].enh_weight,
            img_param_sw->wdr_tbl->container[i].bright_enh_level,
            img_param_sw->wdr_tbl->container[i].dark_enh_level
            );
    }
    BL_LOGD("[OK] img_param_get_wdr_sw tone curve en: %d\r\n", img_param_sw->wdr_manual_conf->enable);
    BL_LOGD("[OK] img_param_get_wdr_sw lowlight_weight conf: %u, %u, {%u, %u, %u, %u,}\r\n", 
        img_param_sw->wdr_manual_conf->lowlight_weight_conf.roi_start,img_param_sw->wdr_manual_conf->lowlight_weight_conf.roi_end,
        img_param_sw->wdr_manual_conf->lowlight_weight_conf.thr[0],img_param_sw->wdr_manual_conf->lowlight_weight_conf.thr[1],
        img_param_sw->wdr_manual_conf->lowlight_weight_conf.thr[2],img_param_sw->wdr_manual_conf->lowlight_weight_conf.thr[3]);
    for (i = 0; i < MAX_ENTRY_NUM_AE_SYS_GAIN_AUTO; i++) {
        BL_LOGD("[OK] img_param_get_wdr_sw lowlight weight[%d]: %u, %u, %u,\r\n", i,
            img_param_sw->wdr_manual_conf->lowlight_weight_conf.lowlight_weight[i].idx[0],
            img_param_sw->wdr_manual_conf->lowlight_weight_conf.lowlight_weight[i].idx[1],
            img_param_sw->wdr_manual_conf->lowlight_weight_conf.lowlight_weight[i].idx[2]);
    }
    for (i = 0; i < MAX_ENTRY_NUM_WDR_IDX_AUTO; i++) {
        BL_LOGD("[OK] img_param_get_wdr_manual cfg[%d]:", i);
        for (j = 0; j < WDR_COEF_NUM; j++) {
            BL_LOGD(" %d,", img_param_sw->wdr_manual_conf->tone_curve_container[i].tone_curve.coef[j]);
        }
        BL_LOGD("\r\n");
        BL_LOGD("[OK] img_param_get_wdr_manual idx[%d]: %d,\r\n", i, img_param_sw->wdr_manual_conf->tone_curve_container[i].idx);
    }

    for (i = 0; i < MAX_ENTRY_NUM_AE_ISO_AUTO; i++) {
        BL_LOGD("[OK] img_param_get_sat_sw cfg[%d]: %d,\r\n", i, img_param_sw->sat_tbl->container[i].value);
    }
    for (i = 0; i < MAX_ENTRY_NUM_AE_ISO_AUTO; i++) {
        BL_LOGD("[OK] img_param_get_yc_sw cfg[%d]: %d,%d,\r\n", i, 
            img_param_sw->yc_tbl->container[i].brightness,
            img_param_sw->yc_tbl->container[i].contrast);
    }
    for (i = 0; i < MAX_ENTRY_NUM_AE_ISO_AUTO; i++) {
        BL_LOGD("[OK] img_param_get_nr_sw cfg[%d]: %d, %d, %d,\r\n", i,
            img_param_sw->nr_tbl->container[i].strength_level,
            img_param_sw->nr_tbl->container[i].strength_2d,
            img_param_sw->nr_tbl->container[i].strength_3d
            );
    }

    BL_LOGD("[OK] img_param_get_ee_over_shut_en: %d,\r\n", img_param_sw->ee_tbl->over_sht_en);
    for (i = 0; i < MAX_ENTRY_NUM_AE_ISO_AUTO; i++) {
        BL_LOGD("[OK] img_param_get_ee_sw cfg[%d]: %d, %d, %d, %d, %d, %d, %d, %d, %d, %d,\r\n", i,
            img_param_sw->ee_tbl->container[i].pos_edge_strength,
            img_param_sw->ee_tbl->container[i].neg_edge_strength,
            img_param_sw->ee_tbl->container[i].pos_edge_ovrsht_strength,
            img_param_sw->ee_tbl->container[i].neg_edge_ovrsht_strength,
            img_param_sw->ee_tbl->container[i].nr_strength,
            img_param_sw->ee_tbl->container[i].dir_shpness_thr,
            img_param_sw->ee_tbl->container[i].no_dir_shpness_thr,
            img_param_sw->ee_tbl->container[i].flat_thr,
            img_param_sw->ee_tbl->container[i].texture_thr,
            img_param_sw->ee_tbl->container[i].edge_thr
            );
    }
    for (i = 0; i < MAX_ENTRY_NUM_EE_LUMA_WEIGHT; i++) {
        BL_LOGD("[OK] img_param_get_ee_luma_weight cfg[%d]: %d,\r\n", i, img_param_sw->ee_luma_wgt_tbl->lumaWgtTbl[i]);
    }

    for (i = 0; i < MAX_ENTRY_NUM_AE_ISO_AUTO; i++) {
        BL_LOGD("[OK] img_param_get_cs_sw cfg[%d]: %d\r\n", i, img_param_sw->cs_tbl->container[i].strength);
    }

}

/*********** sw tbl end ************************************************************************************************/

