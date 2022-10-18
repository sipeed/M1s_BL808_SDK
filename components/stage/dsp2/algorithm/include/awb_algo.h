#ifndef __AWB_ALGO_H__
#define __AWB_ALGO_H__

#include <bl_dsp2.h>
#include "bl_comm_sns.h"
#include "bl_comm_aaa.h"

#define COLOR_TEMP_D75      ((BL_COLOR_TEMP)7500)
#define COLOR_TEMP_D65      ((BL_COLOR_TEMP)6500)
#define COLOR_TEMP_D50      ((BL_COLOR_TEMP)5000)
#define COLOR_TEMP_CWF      ((BL_COLOR_TEMP)4150)
#define COLOR_TEMP_TL84     ((BL_COLOR_TEMP)4000)
#define COLOR_TEMP_A        ((BL_COLOR_TEMP)2856)
#define COLOR_TEMP_H        ((BL_COLOR_TEMP)2300)

#define AWB_UPDATE_BIT_MODE             (1 << 0)
#define AWB_UPDATE_BIT_COLOR_TEMP       (1 << 1)
#define AWB_UPDATE_BIT_SPECIAL_COLOR    (1 << 2)

typedef enum {
    AWB_MODE_AUTO = 0,
    AWB_MODE_LOCK,
    AWB_MODE_NUM,
} AWB_MODE;

typedef enum {
    AWB_STATUS_CONVERGENCE = 0,
    AWB_STATUS_STABLE,
} AWB_STATUS;

typedef enum {
    COLOR_TEMP_IDX_H = 0,
    COLOR_TEMP_IDX_A,
    COLOR_TEMP_IDX_TL84,
    COLOR_TEMP_IDX_CWF,
    COLOR_TEMP_IDX_D50,
    COLOR_TEMP_IDX_D65,
    COLOR_TEMP_IDX_D75,
    COLOR_TEMP_IDX_NUM,
} COLOR_TEMP_IDX;

typedef enum {
    AWB_ALGO_GREY_WORLD = 0,
    AWB_ALGO_1, // sw white world
    AWB_ALGO_2, // hw white world, freddy
    AWB_ALGO_3, // advanced hw white world, freddy
    AWB_ALGO_NUM
} AWB_ALGO;

typedef struct {
    aaa_stats_cfg_t stats_cfg;
} awb_config_t;

typedef struct {
    AWB_MODE          awb_mode;
    uint32_t          rb_gain_update;
    uint32_t          ct_update;
    DSP2_RB_Gain_Type  rb_gain;
    DSP2_RB_Gain_Type  rb_bias;
    BL_COLOR_TEMP     color_temp;
    AWB_STATUS        awb_status;
    uint32_t          special_color_update;
}awb_info_t;

typedef struct {
    int (*config)(awb_config_t *config, bool is_virtual_sensor);
    int (*control)(void);
    int (*get_info)(awb_info_t **awb_info);
    int (*set_mode)(AWB_MODE mode);
    int (*get_mode)(AWB_MODE *mode);
    int (*set_gain)(bl_dsp2_rgb_gain_t *rgb_gain);
    int (*get_gain)(bl_dsp2_rgb_gain_t *rgb_gain);
    int (*set_color_temp)(BL_COLOR_TEMP color_temp);
    int (*get_color_temp)(BL_COLOR_TEMP *color_temp);
    int (*set_speed_level)(int level);
    int (*get_speed_level)(int *level);
    int (*set_special_color_flag)(int flag);
    int (*get_special_color_flag)(int *flag);
    int (*set_sys_gain)(BL_GAIN_DB sys_gain);
    int (*set_manual_rgb_gain)(bl_dsp2_rgb_gain_t *rgb_gain);
    int (*get_manual_rgb_gain)(bl_dsp2_rgb_gain_t *rgb_gain);
    int (*get_algo_version)(int *version);
} awb_func_t;

int awb_init(AWB_ALGO algo);
int awb_config(awb_config_t *config, bool is_virtual_sensor);
int awb_control(void);
int awb_get_info(awb_info_t **awb_info);

int awb_set_mode(AWB_MODE mode);
int awb_get_mode(AWB_MODE *mode);

int awb_set_gain(bl_dsp2_rgb_gain_t *rgb_gain);
int awb_get_gain(bl_dsp2_rgb_gain_t *rgb_gain);

/* for debug purpose only */
int awb_set_color_temp(BL_COLOR_TEMP color_temp);
int awb_get_color_temp(BL_COLOR_TEMP *color_temp);

/* for debug purpose only */
int awb_set_special_color_flag(int flag);
int awb_get_special_color_flag(int *flag);

/* Speed value ranges from 0~5 */
int awb_set_speed_level(int level);
int awb_get_speed_level(int *level);

int awb_set_sys_gain(BL_GAIN_DB sys_gain);

int awb_set_manual_rgb_gain(bl_dsp2_rgb_gain_t *rgb_gain);
int awb_get_manual_rgb_gain(bl_dsp2_rgb_gain_t *rgb_gain);

int awb_get_algo_version(int *version);

#endif  //__AWB_ALGO_H__
