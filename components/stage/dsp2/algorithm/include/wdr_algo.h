#ifndef __WDR_ALGO_H__
#define __WDR_ALGO_H__

#include <img_param.h>
#include "bl_dsp2.h"
#include "bl_comm_sns.h"
#include "bl_comm_aaa.h"

typedef struct {
    aaa_stats_cfg_t stats_cfg;
} wdr_config_t;

typedef struct {
    int cs_weight;
    int cs_grey_thr;
    int curve_weight;
    int enh_weight;
    int bright_enh_level;
    int dark_enh_level;
} wdr_param_t;

typedef struct {
    wdr_param_t param;
    int sys_gain_db;
} wdr_fw_config_t;

typedef struct {
    bl_dsp2_wdr_curve_t curve;
    int curve_weight;
    bl_dsp2_cs_conf_t cs;
    bl_dsp2_wdr_enh_t enh;
} wdr_algo_conf_t;

int wdr_get_algo_version(int *version);
int wdr_config(wdr_config_t *config, bool is_virtual_sensor);
void wdr_algo_set_reg_default(void);
void wdr_algo_fw_param_init(void);
int wdr_algo_control(const wdr_fw_config_t *wdr_fw);
int wdr_algo_get_conf(wdr_algo_conf_t *conf);


#endif
