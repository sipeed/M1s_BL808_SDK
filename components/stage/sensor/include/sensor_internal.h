#ifndef __SENSOR_INTERNAL_H__
#define __SENSOR_INTERNAL_H__
#include <stdint.h>
#include "sensor.h"

#define REGLIST_END                 0xffff

#define SENSOR_INIT_COMMON(SENSOR_NAME)  \
    static const char* name                 = #SENSOR_NAME;  \
    do { \
        sensor->slv_addr                    = SLAVE_ADDR;       \
        sensor->name                        = name;             \
        sensor->reg_addr_bit                = REG_ADDR_BIT;       \
        sensor->min_expo_time               = MIN_EXPO_TIME;    \
        sensor->max_expo_time               = MAX_EXPO_TIME;    \
        sensor->max_gain                    = MAX_GAIN;         \
        sensor->min_gain_step               = MIN_GAIN_STEP;    \
        sensor->enable                      = enable;           \
        sensor->disable                     = disable;          \
        sensor->set_exposure                = set_exposure;     \
        sensor->set_gain                    = set_gain;         \
        sensor->set_flipmirror              = set_flipmirror;    \
        sensor->set_fps                     = set_fps;    \
        sensor->get_property                = get_property;     \
        sensor->quick_mode.is_quick_mode    = 0;                \
        sensor->flip_mirror_type            = FLIP_MIRROR_TYPE_NORMAL;\
        sensor->bayer_pattern               = BAYER_PATTERN_BG;\
    } while (0)

typedef struct _sensor_reg_16_8 {
    uint16_t    addr;
    uint8_t     data;
} sensor_reg_16_8_t;

typedef struct _sensor_format {
    uint16_t    total_width;
    uint16_t    total_height;
    uint32_t    pix_clk;
    uint8_t     fps;
    BAYER_PATTERN_E bayer_pattern;
} sensor_format_t;

int  find_closest_gain_index(BL_GAIN_DB gain, int steps_per_6dB);
int  sensor_probe(uint8_t slv_addr, uint16_t id_addr_h, uint16_t id_addr_l, uint8_t id_h, uint8_t id_l);
int  sensor_probe_8bit(uint8_t slv_addr, uint8_t id_addr_h, uint8_t id_addr_l, uint8_t id_h, uint8_t id_l);
bool is_sensor_dsp2_input_match(const int* sensor_mode, int mode_num);

#endif  //__SENSOR_INTERNAL_H__

