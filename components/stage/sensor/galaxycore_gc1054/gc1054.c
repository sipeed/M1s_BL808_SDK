#include <bl808.h>
#include "sensor_internal.h"
#include "sccb.h"
#include <math.h>

/* GC1054 sensor info */
#define SLAVE_ADDR                  0x21
#define SENSOR_ID_H                 0x10
#define SENSOR_ID_L                 0x54
#define MIN_EXPO_TIME               32848                       /* 32848 ns or -49.5 dB */
#define MAX_EXPO_TIME               EXPO_TIME_1_25_SEC          /* 1/25 sec */
#define REG_ADDR_BIT                SENSOR_REG_ADDR_16BIT

//#define MAX_GAIN                    GAIN_DB_FLOAT_TO_INT(53.25)    /* 53.25 dB */
#define MAX_GAIN                    GAIN_DB_FLOAT_TO_INT(36)    /* limit max gain t0 36 dB to avoid bad noise */
#define MAX_AGAIN                   GAIN_DB_FLOAT_TO_INT(23.625)   /* 23.625 dB or 15.5x */
#define MIN_GAIN_STEP               (GAIN_6_DB / 16)            /* 0.375 dB */

/* GC1054 registers */
#define REG_SENSOR_ID_H             0xf0
#define REG_SENSOR_ID_L             0xf1

#define REG_GROUP_HOLD              0x3812
#define REG_PRECHARGE               0x3314
#define REG_DIGITAL_GAIN            0x3e06
#define REG_DIGITAL_FINE_GAIN       0x3e07
#define REG_COARSE_GAIN             0x3e08
#define REG_FINE_GAIN               0x3e09

#define REG_SHUTTER_TIME_H          0x03
#define REG_SHUTTER_TIME_L          0x04

// #define REG_TOTAL_WIDTH_H           0x320c
// #define REG_TOTAL_WIDTH_L           0x320d
// #define REG_TOTAL_HEIGHT_H          0x320e
// #define REG_TOTAL_HEIGHT_L          0x320f

// #define REG_OUT_WIDTH_H             0x3208
// #define REG_OUT_WIDTH_L             0x3209
// #define REG_OUT_HEIHT_H             0x320a
// #define REG_OUT_HEIHT_L             0x320b

// #define REG_OUT_START_PIXEL_H       0x3210
// #define REG_OUT_START_PIXEL_L       0x3211
// #define REG_OUT_START_LINE_H        0x3212
// #define REG_OUT_START_LINE_L        0x3213

typedef enum {
    FORMAT_INDEX_DVP_720P_25 = 0,
    FORMAT_INDEX_MIPI_1_LANE_720P_25,
    FORMAT_INDEX_INVALID,
} FORMAT_INDEX;

static const sensor_format_t format_info[] = {
    {   /* for dvp 720p25 */
        .total_width    = 1726,
        .total_height   = 765,
        .pix_clk        = 33000000,
        .fps            = 25,
    },
    {   /* for mipi 720p25 */
        .total_width    = 1380,
        .total_height   = 765,
        .pix_clk        = 26400000,
        .fps            = 25,
    },
};

static const int gc1054_mode[] = {\
    DSP2_INPUT_DVP,\
    DSP2_INPUT_MIPI_1LANE,\
};

static const sensor_reg_16_8_t init_reglist_25fps_MIPI_1lane[] = {
/////////////////////////////////////////////////////
//////////////////////   SYS   //////////////////////
/////////////////////////////////////////////////////
{0xf2,0x00},
{0xf6,0x00},
{0xfc,0x04},
{0xf7,0x01},
{0xf8,0x0a},
{0xf9,0x06},
{0xfa,0x80},
{0xfc,0x0e},
{0xfe,0x00},
{0x03,0x02},
{0x04,0xa6},
{0x05,0x02}, //HB
{0x06,0x07},
{0x07,0x00}, //VB
{0x08,0x19},
{0x09,0x00},
{0x0a,0x04}, //row start
{0x0b,0x00},
{0x0c,0x00}, //col start
{0x0d,0x02},
{0x0e,0xd4}, //height 724
{0x0f,0x05},
{0x10,0x08}, //width 1288
{0x17,0xc0},
{0x18,0x02},
{0x19,0x08},
{0x1a,0x18},
{0x1d,0x12},
{0x1e,0x50},
{0x1f,0x80},
{0x21,0x30},
{0x23,0xf8},
{0x25,0x10},
{0x28,0x20},
{0x34,0x08}, //data low
{0x3c,0x10},
{0x3d,0x0e},
{0xcc,0x8e},
{0xcd,0x9a},
{0xcf,0x70},
{0xd0,0xa9},
{0xd1,0xc5},
{0xd2,0xed}, //data high
{0xd8,0x3c}, //dacin offset
{0xd9,0x7a},
{0xda,0x12},
{0xdb,0x50},
{0xde,0x0c},
{0xe3,0x60},
{0xe4,0x78},
{0xfe,0x01},
{0xe3,0x01},
{0xe6,0x10}, //ramps offset
{0xfe,0x01},
{0x80,0x50},
{0x88,0x73},
{0x89,0x03},
{0x90,0x01},
{0x92,0x02}, //crop win 2<=y<=4
{0x94,0x03}, //crop win 2<=x<=5
{0x95,0x02}, //crop win height
{0x96,0xd0},
{0x97,0x05}, //crop win width
{0x98,0x00},
{0xfe,0x01},
{0x8c,0x01}, // test mode
{0x40,0x22},
{0x43,0x03},
{0x4e,0x3c},
{0x4f,0x00},
{0x60,0x00},
{0x61,0x80},
{0xfe,0x01},
{0xb0,0x48},
{0xb1,0x01},
{0xb2,0x00},
{0xb6,0x00},
{0xfe,0x02},
{0x01,0x00},
{0x02,0x01},
{0x03,0x02},
{0x04,0x03},
{0x05,0x04},
{0x06,0x05},
{0x07,0x06},
{0x08,0x0e},
{0x09,0x16},
{0x0a,0x1e},
{0x0b,0x36},
{0x0c,0x3e},
{0x0d,0x56},
{0xfe,0x02},
{0xb0,0x00}, //col_gain[11:8]
{0xb1,0x00},
{0xb2,0x00},
{0xb3,0x11},
{0xb4,0x22},
{0xb5,0x54},
{0xb6,0xb8},
{0xb7,0x60},
{0xb9,0x00}, //col_gain[12]
{0xba,0xc0},
{0xc0,0x20}, //col_gain[7:0]
{0xc1,0x2d},
{0xc2,0x40},
{0xc3,0x5b},
{0xc4,0x80},
{0xc5,0xb5},
{0xc6,0x00},
{0xc7,0x6a},
{0xc8,0x00},
{0xc9,0xd4},
{0xca,0x00},
{0xcb,0xa8},
{0xcc,0x00},
{0xcd,0x50},
{0xce,0x00},
{0xcf,0xa1},
{0xfe,0x02},
{0x54,0xf7},
{0x55,0xf0},
{0x56,0x00},
{0x57,0x00},
{0x58,0x00},
{0x5a,0x04},
{0xfe,0x04},
{0x81,0x8a},
{0xfe,0x03},
{0x01,0x03},
{0x02,0x11},
{0x03,0x90},
// {0x10,0x90},
{0x11,0x2b},
{0x12,0x40},
{0x13,0x06},
{0x15,0x06},
{0x21,0x02},
{0x22,0x02},
{0x23,0x08},
{0x24,0x02},
{0x25,0x10},
{0x26,0x04},
{0x29,0x02},
{0x2a,0x02},
{0x2b,0x04},
{0xfe,0x00},
    /* end of reg list */
    {REGLIST_END, 0x00},
};

static const sensor_reg_16_8_t init_reglist_25fps[] =
{

{0xf2,0x00},
{0xf6,0x00},
{0xfc,0x04},
{0xf7,0x01},
{0xf8,0x0a},
{0xf9,0x00},
{0xfa,0x80},
{0xfc,0x0e},
{0xfe,0x00},
{0x03,0x02},
{0x04,0xa6},
{0x05,0x02}, //HB
{0x06,0x07},
{0x07,0x00}, //VB
{0x08,0x19},
{0x09,0x00},
{0x0a,0x04}, //row start
{0x0b,0x00},
{0x0c,0x00}, //col start
{0x0d,0x02},
{0x0e,0xd4}, //height 724
{0x0f,0x05},
{0x10,0x08}, //width 1288
{0x17,0xc0},
{0x18,0x02},
{0x19,0x08},
{0x1a,0x18},
{0x1d,0x12},
{0x1e,0x50},
{0x1f,0x80},
{0x21,0x30},
{0x23,0xf8},
{0x25,0x10},
{0x28,0x20},
{0x34,0x08}, //data low
{0x3c,0x10},
{0x3d,0x0e},
{0xcc,0x8e},
{0xcd,0x9a},
{0xcf,0x70},
{0xd0,0xa9},
{0xd1,0xc5},
{0xd2,0xed}, //data high
{0xd8,0x3c}, //dacin offset
{0xd9,0x7a},
{0xda,0x12},
{0xdb,0x50},
{0xde,0x0c},
{0xe3,0x60},
{0xe4,0x78},
{0xfe,0x01},
{0xe3,0x01},
{0xe6,0x10}, //ramps offset
{0xfe,0x01},
{0x8c,0x01}, // test mode
{0x80,0x50},
{0x88,0x33},
{0x89,0x03},
{0x90,0x01},
{0x92,0x02}, //crop win 2<=y<=4
{0x94,0x03}, //crop win 2<=x<=5
{0x95,0x02}, //crop win height
{0x96,0xd0},
{0x97,0x05}, //crop win width
{0x98,0x00},
{0xfe,0x01},
{0x40,0x22},
{0x43,0x03},
{0x4e,0x3c},
{0x4f,0x00},
{0x60,0x00},
{0x61,0x80},
{0xfe,0x01},
{0xb0,0x48},
{0xb1,0x01},
{0xb2,0x00},
{0xb6,0x00},
{0xfe,0x02},
{0x01,0x00},
{0x02,0x01},
{0x03,0x02},
{0x04,0x03},
{0x05,0x04},
{0x06,0x05},
{0x07,0x06},
{0x08,0x0e},
{0x09,0x16},
{0x0a,0x1e},
{0x0b,0x36},
{0x0c,0x3e},
{0x0d,0x56},
{0xfe,0x02},
{0xb0,0x00}, //col_gain[11:8]
{0xb1,0x00},
{0xb2,0x00},
{0xb3,0x11},
{0xb4,0x22},
{0xb5,0x54},
{0xb6,0xb8},
{0xb7,0x60},
{0xb9,0x00}, //col_gain[12]
{0xba,0xc0},
{0xc0,0x20}, //col_gain[7:0]
{0xc1,0x2d},
{0xc2,0x40},
{0xc3,0x5b},
{0xc4,0x80},
{0xc5,0xb5},
{0xc6,0x00},
{0xc7,0x6a},
{0xc8,0x00},
{0xc9,0xd4},
{0xca,0x00},
{0xcb,0xa8},
{0xcc,0x00},
{0xcd,0x50},
{0xce,0x00},
{0xcf,0xa1},
{0xfe,0x02},
{0x54,0xf7},
{0x55,0xf0},
{0x56,0x00},
{0x57,0x00},
{0x58,0x00},
{0x5a,0x04},
{0xfe,0x04},
{0x81,0x8a},
{0xfe,0x03},
{0x01,0x00},
{0x02,0x00},
{0x03,0x00},
{0x10,0x11},
{0x15,0x00},
{0x40,0x01},
{0x41,0x00},
{0xfe,0x00},
{0xf2,0x0f},

    /* end of reg list */
    {REGLIST_END, 0x00},
};

static int enable(sensor_t *sensor)
{
    if (DSP2_INPUT_MIPI_1LANE == DSP2_INPUT_MODE) {
        SCCB_Write(sensor->slv_addr, 0xfe, 0x03);
        SCCB_Write(sensor->slv_addr, 0x10, 0x90);
        SCCB_Write(sensor->slv_addr, 0xfe, 0x00);
    }
    else {
    SCCB_Write(sensor->slv_addr, 0xfe, 0x03);
    SCCB_Write(sensor->slv_addr, 0xf2, 0x0f);
    SCCB_Write(sensor->slv_addr, 0xfe, 0x00);
    }

    // SCCB_Write(sensor->slv_addr, 0xfe, 0x03);
    // SCCB_Write(sensor->slv_addr, 0x10, 0x91);
    // SCCB_Write(sensor->slv_addr, 0xfe, 0x00);

    return 0;
}

static int disable(sensor_t *sensor)
{
    if (DSP2_INPUT_MIPI_1LANE == DSP2_INPUT_MODE) {
        SCCB_Write(sensor->slv_addr, 0xfe, 0x03);
        SCCB_Write(sensor->slv_addr, 0x10, 0x00);
        SCCB_Write(sensor->slv_addr, 0xfe, 0x00);
    }
    else {
        SCCB_Write(sensor->slv_addr, 0xfe, 0x03);
        SCCB_Write(sensor->slv_addr, 0xf2, 0x00);
        SCCB_Write(sensor->slv_addr, 0xfe, 0x00);
    }

    return 0;
}

/*****************************GC CODE*****************************/


/******************************************************/

static int set_exposure(sensor_t *sensor, BL_EXPO_TIME expo_time)
{
    // uint64_t tmp = expo_time * (uint64_t)sensor->pix_clk;
    // int num_half_line = NS_TO_SEC(tmp / sensor->total_win.width);

    // SetSensorIntt(sensor, num_half_line);
    return 0;
}

static int set_gain(sensor_t *sensor, BL_GAIN_DB gain)
{
    // float gain2 = pow(2, GAIN_DB_INT_TO_FLOAT(gain)/6)*64;
    // SetSensorGain(sensor, gain2);
    return 0;
}

static int set_flipmirror(sensor_t *sensor, FLIP_MIRROR_TYPE_E type)
{
    return 0;
}

static int set_fps(sensor_t *sensor, uint32_t fps)
{
    return 0;
}

static int setFmt(sensor_t *sensor)
{
    int i;
    FORMAT_INDEX format_index;
    const sensor_reg_16_8_t *init_reglist;

    switch (sensor->video_mode) {
    case VIDEO_MODE_720P_25:
        if (DSP2_INPUT_MIPI_1LANE == DSP2_INPUT_MODE) {
            init_reglist = init_reglist_25fps_MIPI_1lane;
            format_index = FORMAT_INDEX_MIPI_1_LANE_720P_25;
        }
        else {
            init_reglist = init_reglist_25fps;
            format_index = FORMAT_INDEX_DVP_720P_25;
        }
        sensor->max_expo_time = EXPO_TIME_1_25_SEC;       /* 1/25 sec */
        break;

    default:
        BL_LOGE("set_format error: invalid video mode!\r\n");
        return -1;
    }

    sensor->pix_clk             = format_info[format_index].pix_clk;
    sensor->fps                 = format_info[format_index].fps;
    sensor->total_win.width     = format_info[format_index].total_width;
    sensor->total_win.height    = format_info[format_index].total_height;
    sensor->out_win.width  = 1280;
    sensor->out_win.height = 720;

    for (i = 0; init_reglist[i].addr != REGLIST_END; i++) {
        SCCB_Write(sensor->slv_addr, init_reglist[i].addr, (uint8_t)init_reglist[i].data);
    }



    return 0;
}

static int get_property(sensor_t *sensor, sensor_property_t *property)
{
    CHECK_PARAM(sensor != NULL);

    property->bayer_pattern = BAYER_PATTERN_BG;

    return 0;
}

static int probe(void)
{
    return sensor_probe_8bit(SLAVE_ADDR, REG_SENSOR_ID_H, REG_SENSOR_ID_L, SENSOR_ID_H, SENSOR_ID_L);
}

static int init(sensor_t *sensor)
{
    int mode_num = sizeof(gc1054_mode)/sizeof(gc1054_mode[0]);
    if (!is_sensor_dsp2_input_match(gc1054_mode, mode_num)) {
        return -1;
    }

    /* Initialize sensor structure */
    SENSOR_INIT_COMMON(GC1054);

    //set_format(sensor, VIDEO_MODE_720P_25);

#if 0   // enable test pattern
    SCCB_Write_Reg16(sensor->slv_addr, 0x4501, 0xc8);     /* test pattern enable */
    SCCB_Write_Reg16(sensor->slv_addr, 0x3902, 0x05);     /* manual BLC  */
#endif

    return 0;
}

const BL_SENSOR_DESC_T sensor_desc_gc1054 ATTR_SENSOR_DEVICE_TABLE =
{
    "GC1054",
    SLAVE_ADDR,
    probe,
    init,
    setFmt,
};

