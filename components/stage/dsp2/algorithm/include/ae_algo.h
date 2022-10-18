#ifndef __AE_ALGO_H__
#define __AE_ALGO_H__

#include "bl_comm_aaa.h"
#include "sensor.h"
#include "img_struct.h"

typedef enum {
    AE_ALGO_BL = 0,
    AE_ALGO_NUM
} AE_ALGO;

typedef enum {
    AE_MODE_AUTO = 0,
    AE_MODE_LOCK,
    AE_MODE_DBG_VIRTUAL,
    AE_MODE_DBG_AE_LINEARITY,
    AE_MODE_INVALID,
} AE_MODE;

typedef enum {
    AE_STATE_IDLE = 0,
    AE_STATE_INITED,
    AE_STATE_RUNNING,
    AE_STATE_PENDING,
} AE_STATE;

typedef enum {
    AE_HIST_WEIGHT_IDX_0 = 0,
    AE_HIST_WEIGHT_IDX_128,
    AE_HIST_WEIGHT_IDX_255,
    AE_HIST_WEIGHT_IDX_NUM,
} AE_HIST_WEIGHT_IDX;

typedef struct {
    aaa_stats_cfg_t stats_cfg;
} ae_config_t;

typedef struct {
    int     enable;
    int     hist_sum;
    int     idx;
} ae_highlight_weight_idx_info_t;

typedef struct {
    uint8_t  enable;
    uint8_t  is_update;
    uint16_t fps;
} ae_ss_conf_t;

typedef struct {
    AE_MODE       ae_mode;
    AE_METERING   ae_metering;
    uint32_t      expo_time_update;
    uint32_t      iso_update;
    uint32_t      sys_gain_update;
    BL_EXPO_TIME  expo_time;
    BL_GAIN_DB    iso;
    BL_GAIN_DB    sys_gain;
    int           luma_target;
    int           hist_weight_mode;
    ae_highlight_weight_idx_info_t  highlight_weight;
    ae_ss_conf_t ae_slow_shutter_conf;
} ae_info_t;

typedef struct {
    BL_EXPO_TIME  expo_time;
    BL_GAIN_DB    iso;
    BL_GAIN_DB    sys_gain;
    int           luma_target;
} ae_history_info_t;

typedef struct {
    uint8_t coef[AE_HIST_BIN_NUM];
} ae_hist_weight_tbl_t;

typedef struct {
    ae_hist_weight_tbl_t container[3];
} ae_hist_weight_tbl_container_t;

typedef struct {
    int (*config)(ae_config_t *config, bool is_virtual_sensor);
    int (*control)(void);
    int (*get_info)(ae_info_t **ae_info);
    int (*update_stats)(void);
    int (*set_mode)(AE_MODE mode);
    int (*get_mode)(AE_MODE *mode);
    int (*set_luma_target)(int target);
    int (*get_luma_target)(int *target);
    int (*set_metering_mode)(AE_METERING mode);
    int (*get_metering_mode)(AE_METERING *mode);
    int (*set_hist_weight_mode)(int mode);
    int (*get_hist_weight_mode)(int *mode);
    int (*set_hist_weight_tbl)(AE_HIST_WEIGHT_IDX mode, ae_hist_weight_tbl_t *tbl);
    int (*get_hist_weight_tbl)(AE_HIST_WEIGHT_IDX mode, ae_hist_weight_tbl_t *tbl);
    int (*set_speed)(int speed);
    int (*get_speed)(int *speed);
    int (*set_speed_level)(int level);
    int (*get_speed_level)(int *level);
    int (*get_luma)(void);
    int (*set_exposure_max)(BL_EXPO_TIME max_expo);
    int (*get_exposure_max)(BL_EXPO_TIME *max_expo);
    int (*set_exposure_min)(BL_EXPO_TIME min_expo);
    int (*get_exposure_min)(BL_EXPO_TIME *min_expo);
    int (*set_gain_max)(float gain_f);
    int (*get_gain_max)(float *gain_f);
    int (*get_sensor_exposure_max)(BL_EXPO_TIME *max_expo);
    int (*get_sensor_exposure_min)(BL_EXPO_TIME *min_expo);
    int (*get_sensor_gain_max)(float *max_gain_f);
    int (*set_sensor_exposure)(BL_EXPO_TIME expo_time);
    int (*get_sensor_exposure)(BL_EXPO_TIME *expo_time);
    int (*get_sensor_gain)(float *gain_f);
    int (*set_sensor_gain)(float gain_f);
    int (*get_algo_version)(int *version);

    int (*force_refresh)(void);
    int (*gen_sys_gain_by_expo_gain)(BL_EXPO_TIME expo, BL_GAIN_DB gain, BL_GAIN_DB *out_gain);
    int (*set_linearity)(int mode);
    int (*get_linearity)(int *mode);
} ae_func_t;


int ae_init(AE_ALGO algo);
int ae_config(ae_config_t *ae_config, bool is_virtual_sensor);
int ae_control(void);
int ae_get_info(ae_info_t **ae_info);

/* Update ae statistics from hw*/
int ae_update_stats(void);

/* set/get ae mode */
int ae_set_mode(AE_MODE mode);
int ae_get_mode(AE_MODE *mode);

/* Target value ranges from 0~255 */
int ae_set_luma_target(int target);
int ae_get_luma_target(int *target);

/* set/get ae metering mode */
int ae_set_metering_mode(AE_METERING mode);
int ae_get_metering_mode(AE_METERING *mode);

/* set/get ae hist weight mode */
int ae_set_hist_weight_mode(int mode);
int ae_get_hist_weight_mode(int *mode);

/* set/get ae hist weight tbl */
int ae_set_hist_weight_tbl(AE_HIST_WEIGHT_IDX mode, ae_hist_weight_tbl_t *tbl);
int ae_get_hist_weight_tbl(AE_HIST_WEIGHT_IDX mode, ae_hist_weight_tbl_t *tbl);

/* Speed value ranges from 0~16 */
int ae_set_speed(int speed);
int ae_get_speed(int *speed);

/* Speed value ranges from 0~5 */
int ae_set_speed_level(int level);
int ae_get_speed_level(int *level);

/* Luma value ranges from 0~255 */
int ae_get_luma(void);

/* Set and get SW limitation by AE strategy */
int ae_set_exposure_max(BL_EXPO_TIME max_expo);
int ae_get_exposure_max(BL_EXPO_TIME *max_expo);
int ae_set_exposure_min(BL_EXPO_TIME min_expo);
int ae_get_exposure_min(BL_EXPO_TIME *min_expo);
int ae_set_gain_max(float gain_f);
int ae_get_gain_max(float *gain_f);

/* Get HW limitation of sensor */
int ae_get_sensor_exposure_max(BL_EXPO_TIME *max_expo);
int ae_get_sensor_exposure_min(BL_EXPO_TIME *min_expo);
int ae_get_sensor_gain_max(float *max_gain_f);

/* Set and get sensor exposure and gain */
int ae_set_sensor_exposure(BL_EXPO_TIME expo_time);
int ae_get_sensor_exposure(BL_EXPO_TIME *expo_time);
int ae_get_sensor_gain(float *gain_f);
int ae_set_sensor_gain(float gain_f);

int ae_get_algo_version(int *version);

/* Misc */
int ae_force_refresh(void);
int ae_gen_sys_gain_by_expo_gain(BL_EXPO_TIME expo, BL_GAIN_DB gain, BL_GAIN_DB *out_gain);
int ae_set_linearity(int mode);
int ae_get_linearity(int *mode);

#endif //__AE_ALGO_H__
