#ifndef __SENSOR_H__
#define __SENSOR_H__

#include "bl_comm_sns.h"

/* Special data type */

#define SEC_TO_NS(x)                    ((x) * 1000000000)
#define NS_TO_SEC(x)                    DIV_ROUND(x, 1000000000)

#define FLOAT_TO_EXPO_TIME(x)           (BL_EXPO_TIME)( ( SEC_TO_NS(1)/(x) ) )
#define INT_TO_EXPO_TIME(x)             (BL_EXPO_TIME)(DIV_ROUND(SEC_TO_NS(1),x))
#define EXPO_TIME_TO_INT(x)             (SEC_TO_NS(1) / (int)(x))
#define EXPO_TIME_1_SEC                 1000000000

#define EXPO_TIME_1_15_SEC              INT_TO_EXPO_TIME(15)
#define EXPO_TIME_1_25_SEC              INT_TO_EXPO_TIME(25)//40000000
#define EXPO_TIME_1_50_SEC              INT_TO_EXPO_TIME(50)
#define EXPO_TIME_1_100_SEC             INT_TO_EXPO_TIME(100)//10000000
#define EXPO_TIME_1_30_SEC              INT_TO_EXPO_TIME(30)
#define EXPO_TIME_1_60_SEC              INT_TO_EXPO_TIME(60)
#define EXPO_TIME_1_120_SEC             INT_TO_EXPO_TIME(120)
#define EXPO_TIME_MIN                   1

#define FLOAT_TO_GAIN_DB(x)             (BL_GAIN_DB)((x) * 256)
#define INT_TO_GAIN_DB(x)               (BL_GAIN_DB)((x) << 8)
#define GAIN_DB_TO_INT(x)               ((int)(x) >> 8)

#define GAIN_X_TO_DB(x)                 (log2((float)(x)) * 6)
#define GAIN_DB_FLOAT_TO_INT(x)         ((int)((float)(x) * 256 + 0.5))
#define GAIN_DB_INT_TO_FLOAT(x)         ((float)(x) / 256)
#define DB_TO_GAIN(x)                   (pow(2, GAIN_DB_INT_TO_FLOAT(x)/6))

#define GAIN_6_DB                       1536    /* 6 << 8 */
#define GAIN_0_DB                       0

typedef struct _sensor sensor_t;

typedef enum {
    SENSOR_REG_ADDR_8BIT = 0,
    SENSOR_REG_ADDR_16BIT,
} sensor_reg_addr_bit_e;

typedef struct _sensor_property
{
    BAYER_PATTERN_E bayer_pattern;
} sensor_property_t;

typedef struct _sensor_quick_mode {
    int  is_quick_mode;
    int  (*get_ae_exposure)  (sensor_t *sensor, BL_EXPO_TIME *expo_time);
    int  (*get_ae_gain)      (sensor_t *sensor, BL_GAIN_DB *gain);
    int  (*get_awb_gain)     (sensor_t *sensor, int *r_gain, int *g_gain, int *b_gain);
    int  (*reset)            (sensor_t *sensor);
} sensor_quick_mode_t;

typedef struct _sensor {
    /* Sensor ID */
    const char*         name;
    /* Sensor property */
    uint8_t             slv_addr;                   /* sensor I2C slave address */
    uint8_t             reg_addr_bit;               /* sensor register address bit*/
    uint32_t            pix_clk;                    /* sensor pixel clock */
    BL_Img_Size_T       total_win;                  /* sensor total window */
    BL_Img_Size_T       out_win;                    /* sensor output window */
    BL_Img_Size_T       dsp2_out_win;                /* dsp2 output window， for better picture quality */
    BL_EXPO_TIME        min_expo_time;              /* min exposure time in ns */
    BL_EXPO_TIME        max_expo_time;              /* max exposure time in ns */
    BL_GAIN_DB          max_gain;                   /* max sensor gain in dB (LS8 format) */
    BL_GAIN_DB          min_gain_step;              /* min step of sensor gain change in dB (LS8 format) */
    /* Sensor status */
    int                 enabled;                    /* sensor enable status */
    VIDEO_MODE_E        video_mode;
    BL_EXPO_TIME        expo_time;                  /* current exposure time in second (LS24 format) */
    BL_GAIN_DB          gain;                       /* current gain */
    FLIP_MIRROR_TYPE_E  flip_mirror_type;          /* flip mirror type */
    uint32_t             fps;                       /* fps * 100*/
    /* Sensor operations */
    int                 (*enable)(struct _sensor *sensor);
    int                 (*disable)(struct _sensor *sensor);
    int                 (*set_exposure)(struct _sensor *sensor, BL_EXPO_TIME expo_time);
    int                 (*set_gain)(struct _sensor *sensor, BL_GAIN_DB gain);
    int                 (*set_flipmirror)(struct _sensor *sensor, FLIP_MIRROR_TYPE_E type);
    int                 (*get_property)(struct _sensor *sensor, sensor_property_t *property);
    int                 (*set_fps)(struct _sensor *sensor, uint8_t *fps);
    /* Sensor quick mode */
    sensor_quick_mode_t quick_mode;
    BAYER_PATTERN_E bayer_pattern;
} sensor_t;

typedef struct _sensor_init_info {
    void (*get_probe_info)  (uint8_t *slv_addr, uint32_t *regs_sensor_id, uint16_t *sensor_id);
    int  (*init)            (sensor_t *sensor);
} sensor_init_info_t;

typedef int (*SENSOR_PROBE_FUNC)(void);
typedef int (*SENSOR_INIT_FUNC)(sensor_t *sensor);
typedef int (*SENSOR_SETFMT_FUNC)(sensor_t *sensor);

typedef struct
{
	char *name;
	uint8_t addr;
    SENSOR_PROBE_FUNC probe;
    SENSOR_INIT_FUNC init;
    SENSOR_SETFMT_FUNC setFmt;
} BL_SENSOR_DESC_T;

typedef struct {
    int VTS;
    int fps;
} fps_info_t;

int sensor_init(void);
int yuvsensor_init(void);
int mipi_sensor_init(void);
int sensor_is_inited(void);
int sensor_is_enabled(void);
int sensor_enable(void);
int sensor_disable(void);
int sensor_reset(void);
int sensor_getFmt(VIDEO_MODE_E *video_mode);
int sensor_setFmt(VIDEO_MODE_E video_mode);

void sensor_get_name(const char** name);

int sensor_get_total_window(BL_Img_Size_T *win);
int sensor_get_output_window(BL_Img_Size_T *win);
int sensor_get_dsp2_output_window(BL_Img_Size_T *win);
int sensor_get_pix_clk(uint32_t *clk);

uint8_t sensor_get_slv_addr(void);
int  sensor_get_bayer_pattern(BAYER_PATTERN_E *bayer);

/* Expo time value ranges from EXPO_TIME_MIN ~ EXPO_TIME_1_25_SEC */
int sensor_get_exposure(BL_EXPO_TIME *expo_time);
int sensor_set_exposure(BL_EXPO_TIME expo_time);

/* Gain value ranges from INT_TO_GAIN_DB(0) ~ INT_TO_GAIN_DB(72) */
int sensor_get_gain(BL_GAIN_DB *gain);
int sensor_set_gain(BL_GAIN_DB gain);

int sensor_get_exposure_max(BL_EXPO_TIME *max_expo_time);
int sensor_get_exposure_min(BL_EXPO_TIME *min_expo_time);
int sensor_get_gain_max(BL_GAIN_DB *max_gain);
int sensor_get_gain_step(BL_GAIN_DB *gain_step);
int sensor_get_flipmirror(FLIP_MIRROR_TYPE_E *type);
int sensor_set_flipmirror(FLIP_MIRROR_TYPE_E type);
int sensor_get_fps(uint32_t *fps);
int sensor_set_fps(uint32_t fps);

int sensor_get_sensor_reg(uint16_t addr, uint8_t *data);
int sensor_set_sensor_reg(uint16_t addr, uint8_t data);
int sensor_is_quick_mode();
int sensor_quick_mode_get_ae_exposure  (BL_EXPO_TIME *expo_time);
int sensor_quick_mode_get_ae_gain      (BL_GAIN_DB *gain);
int sensor_quick_mode_get_awb_gain     (int *r_gain, int *g_gain, int *b_gain);
int sensor_quick_mode_reset            ();

/* helper functions */
void sensor_print_gain(BL_GAIN_DB gain);
void sensor_print_expo_time(BL_EXPO_TIME expo_time);

#define ATTR_SENSOR_DEVICE_TABLE __attribute__((section(".sensor_desc")))  __attribute__((used))


#endif /* __SENSOR_H__ */
