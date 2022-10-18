#ifndef __IMG_PORC_H__
#define __IMG_PORC_H__

#include "bl_comm_aaa.h"

#include "ae_algo.h"
#include "awb_algo.h"
#include "wdr_algo.h"
#include "img_param.h"

#define AE_ENABLE_BIT          (1 << 0)
#define AWB_ENABLE_BIT         (1 << 1)

typedef enum {
    FORCE_FLAG = 0,
    ISO_FLAG,
    EXPO_TIME_FLAG,
    SYS_GAIN_FLAG,
    CT_FLAG
} imgproc_update_flag_type_t;

typedef struct {
    aaa_stats_cfg_t stats_cfg;
} img_proc_cfg_t;

typedef enum {
    IMGPROC_INIT = 0,
    IMGPROC_RUN,
    IMGPROC_PAUSE,
    IMGPROC_STOP,
    IMGPROC_STATUS_NUM,
} imgproc_status_type_t;

int imgproc_init(bl_vin_config_t *cfg);
int  imgproc_bind_sensor_model(const char* sensor_name);
int  imgproc_set_config(img_proc_cfg_t *config, bool is_virtual_sensor);
int  imgproc_start(void);
int  imgproc_stop(void);
int imgproc_status(int     *status);
int  imgproc_update_force(void);
void imgproc_night_mode_enable(bool enable);
int imgproc_set_ae_algo(AE_ALGO algo);
int imgproc_get_ae_algo(void);
int imgproc_set_awb_algo(AWB_ALGO algo);
int imgproc_get_awb_algo(void);
int imgproc_set_flicker_mode(flicker_mode mode);
int imgproc_get_flicker_mode(void);
int imgproc_set_module_enable(img_param_module_t module, BL_Fun_Type enable);
BL_Fun_Type imgproc_is_module_enable(img_param_module_t module);
BL_Fun_Type imgproc_get_fw_module_en(const img_param_module_t module);
int imgproc_set_fw_module_en(const img_param_module_t module, BL_Fun_Type enable);
BL_Fun_Type imgproc_get_fw_module_manual_mode(const img_param_module_t module);
int imgproc_set_fw_module_manual_mode(const img_param_module_t module, BL_Fun_Type enable);
int imgproc_get_2A_keep_reg(char* reg, BL_GAIN_DB *gain_f, BL_EXPO_TIME *expo_time, BL_COLOR_TEMP *color_temp);
int imgproc_set_2A_keep_reg(char* reg, BL_GAIN_DB gain_f, BL_EXPO_TIME expo_time, BL_COLOR_TEMP color_temp);
uint32_t imgproc_get_fps(void);
void imgproc_update_fps_register(bl_dsp2_update_fps_cb *cb);

#endif  /* __IMG_PROC_H__ */

