#include <bl808.h>
#include "sensor_internal.h"
#include "sccb.h"
#include <math.h>

/* GC2093 sensor info */
#define SLAVE_ADDR                  0x37
#define SENSOR_ID_H                 0x20
#define SENSOR_ID_L                 0x93
#define MIN_EXPO_TIME               143282                       /* 143282 ns, 4 line */
#define MAX_EXPO_TIME               EXPO_TIME_1_25_SEC          /* 1/25 sec */
#define REG_ADDR_BIT                SENSOR_REG_ADDR_16BIT

//#define MAX_GAIN                    GAIN_DB_FLOAT_TO_INT(53.25)    /* 53.25 dB */
#define MAX_GAIN                    GAIN_DB_FLOAT_TO_INT(36)    /* limit max gain t0 36 dB to avoid bad noise */
#define MAX_AGAIN                   GAIN_DB_FLOAT_TO_INT(23.625)   /* 23.625 dB or 15.5x */
#define MIN_GAIN_STEP               (GAIN_6_DB / 16)            /* 0.375 dB */

/* GC2093 registers */
#define REG_SENSOR_ID_H             0x03f0
#define REG_SENSOR_ID_L             0x03f1

// #define REG_GROUP_HOLD              0x3812
// #define REG_PRECHARGE               0x3314
// #define REG_DIGITAL_GAIN            0x3e06
// #define REG_DIGITAL_FINE_GAIN       0x3e07
// #define REG_COARSE_GAIN             0x3e08
// #define REG_FINE_GAIN               0x3e09

// #define REG_SHUTTER_TIME_H          0x03
// #define REG_SHUTTER_TIME_L          0x04

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
    FORMAT_INDEX_DVP_1080P_25 = 0,
    FORMAT_INDEX_INVALID,
} FORMAT_INDEX;

static const sensor_format_t format_info[] = {
    {   /*  DVP 1080p25 */
        .total_width    = 2640,
        .total_height   = 1125,
        .pix_clk        = 74250000,
        .fps            = 25,
        .bayer_pattern = BAYER_PATTERN_RG,
    },
};

static const int gc2093_mode[] = {\
    DSP2_INPUT_DVP,\
};

static const sensor_reg_16_8_t init_reglist_25fps_quick_start[] =
{
/****system****/
{0x03fe,0x80},
{0x03fe,0x80},
{0x03fe,0x80},
{0x03fe,0x00},
{0x03f2,0x00},
{0x03f3,0x0f},
{0x03f4,0x36},
{0x03f5,0xc0},
{0x03f6,0x0A},
{0x03f7,0x01},
{0x03f8,0x32},
{0x03f9,0x10},
{0x03fc,0x8e},

{0x03fe,0x10},
{0x01e1,0x08},  //qcif num
{0x0183,0x01},
{0x0187,0x50},
{0x01a0,0x00},  //awb_en
{0x01af,0x09},  //aec_en
/****CISCTL & ANALOG****/
{0x0087,0x18},
{0x00ee,0x30},
{0x00d0,0xb7},
{0x01a0,0x00},
{0x01a4,0x40},
{0x01a5,0x40},
{0x01a6,0x40},
{0x01af,0x09},
{0x0001,0x00},
{0x0002,0x02},
{0x0003,0x00},
{0x0004,0x02},
{0x0005,0x05},
{0x0006,0x28},
{0x0007,0x00},
{0x0008,0x11},
{0x0009,0x00},
{0x000a,0x02},
{0x000b,0x00},
{0x000c,0x04},
{0x000d,0x04},
{0x000e,0x40},
{0x000f,0x07},
{0x0010,0x8c},
{0x0013,0x15},
{0x0019,0x0c},
{0x0041,0x04},
{0x0042,0x65},
{0x0053,0x60},
{0x008d,0x92},
{0x0090,0x00},
{0x0053,0x60},
{0x00c7,0xe1},
{0x001b,0x73},
{0x0028,0x0d},
{0x0029,0x24},
{0x002b,0x04},
{0x002e,0x23},
{0x0037,0x03},
{0x0043,0x04},
{0x0044,0x20},
{0x0046,0x0b},
{0x004a,0x01},
{0x004b,0x20},
{0x0055,0x20},
{0x0068,0x20},
{0x0069,0x20},
{0x0077,0x00},
{0x0078,0x04},
{0x007c,0x91},
{0x00ce,0x7c},
{0x00d3,0xdc},
{0x00e6,0x50},
/*gain*/
{0x00b6,0xc0},
{0x00b0,0x60},
/*dsp2*/
{0x0102,0x89},
{0x0104,0x01},
/*blk*/
{0x0026,0x20},
{0x0142,0x00},
{0x0149,0x1e},
{0x014a,0x07},
{0x014b,0x80},
{0x0155,0x07},
{0x0414,0x7e},
{0x0415,0x7e},
{0x0416,0x7e},
{0x0417,0x7e},
{0x04e0,0x18},
/*window*/
{0x0192,0x02},
{0x0194,0x03},
{0x0195,0x04},
{0x0196,0x38},
{0x0197,0x07},
{0x0198,0x80},
{0x01b0,0x04}, //aec max exp high
{0x01b1,0x65}, //aec max exp low
{0x01b2,0x10}, //aec min exp
{0x01b3,0x01}, //aec_gain_max[9:8]
{0x01b4,0x80}, //aec_gain_max[7:0]
{0x01b5,0x40}, //aec_y_target
{0x01b6,0x05}, //aec_margin
{0x01b8,0x01}, //aec_win_x0
{0x01b9,0xe0}, //aec_win_x1
{0x01ba,0x01}, //aec_win_y0
{0x01bb,0x80}, //aec_win_y1
/****DVP & MIPI****/
{0x019a,0x06},
{0x007b,0x2a},
{0x0023,0x2d},
{0x0201,0x20},
{0x0202,0x56},
{0x0203,0xb2},
{0x0212,0x80},
{0x0213,0x07},
{0x003e,0x40},
{0x01af,0x0b},  //aec  en
{0x01a0,0xc0},  //awb  en + awb_write_valid
{0x01e0,0x01},  //speed mode
{0x03fe,0x00},  //cisctrl rst
    /* end of reg list */
    {REGLIST_END, 0x00},
};

static const sensor_reg_16_8_t init_reglist_25fps[] =
{
/****system****/
{0x03fe,0x80},
{0x03fe,0x80},
{0x03fe,0x80},
{0x03fe,0x00},
{0x03f2,0x00 },
{0x03f3,0x0f },
{0x03f4,0x36 },
{0x03f5,0xc0 },
{0x03f6,0x0A },
{0x03f7,0x01 },
{0x03f8,0x2C },
{0x03f9,0x10 },
{0x03fc,0x8e},
/****CISCTL & ANALOG****/
{0x0087,0x18},
{0x00ee,0x30},
{0x00d0,0xb7},
{0x01a0,0x00},
{0x01a4,0x40},
{0x01a5,0x40},
{0x01a6,0x40},
{0x01af,0x09},
{0x0001,0x00},
{0x0002,0x02},
{0x0003,0x00},
{0x0004,0x02},
{0x0005,0x05},
{0x0006,0x28},
{0x0007,0x00},
{0x0008,0x11},
{0x0009,0x00},
{0x000a,0x02},
{0x000b,0x00},
{0x000c,0x04},
{0x000d,0x04},
{0x000e,0x40},
{0x000f,0x07},
{0x0010,0x8c},
{0x0013,0x15},
{0x0019,0x0c},
{0x0041,0x04},
{0x0042,0x65},
{0x0053,0x60},
{0x008d,0x92},
{0x0090,0x00},
{0x0053,0x60},
{0x00c7,0xe1},
{0x001b,0x73},
{0x0028,0x0d},
{0x0029,0x24},
{0x002b,0x04},
{0x002e,0x23},
{0x0037,0x03},
{0x0043,0x04},
{0x0044,0x20},
{0x0046,0x0b},
{0x004a,0x01},
{0x004b,0x20},
{0x0055,0x20},
{0x0068,0x20},
{0x0069,0x20},
{0x0077,0x00},
{0x0078,0x04},
{0x007c,0x91},
{0x00ce,0x7c},
{0x00d3,0xdc},
{0x00e6,0x50},
/*gain*/
{0x00b6,0xc0},
{0x00b0,0x60},
/*dsp2*/
{0x0102,0x89},
{0x0104,0x01},
/*test pattern*/
// {0x018c,0x01},
/*blk*/
{0x0026,0x20},
{0x0142,0x00},
{0x0149,0x1e},
{0x014a,0x07},
{0x014b,0x80},
{0x0155,0x07},
{0x0414,0x7e},
{0x0415,0x7e},
{0x0416,0x7e},
{0x0417,0x7e},
{/*window*/},
{0x0192,0x02},
{0x0194,0x03},
{0x0195,0x04},
{0x0196,0x38},
{0x0197,0x07},
{0x0198,0x80},
/****DVP & MIPI****/
{0x019a,0x06},
{0x007b,0x2a},
{0x0023,0x2d},
{0x0201,0x20},
{0x0202,0x56},
{0x0203,0xb2},
{0x0212,0x80},
{0x0213,0x07},
{0x003e,0x40},

    /* end of reg list */
    {REGLIST_END, 0x00},
};

static int enable(sensor_t *sensor)
{
    uint8_t data;

    // if (DSP2_INPUT_MIPI_1LANE == DSP2_INPUT_MODE) {
    //     data = 0x90;
    // }
    // else if (DSP2_INPUT_MIPI_2LANE == DSP2_INPUT_MODE) {
    //     data = 0x91;
    // }
    // else {
    //
    // }

    data = 0x40;

    // SCCB_Write_Reg16(sensor->slv_addr, 0xfe, 0x00);
    SCCB_Write_Reg16(sensor->slv_addr, 0x003e, data);

    return 0;
}

static int disable(sensor_t *sensor)
{
    // SCCB_Write_Reg16(sensor->slv_addr, 0xfe, 0x00);
    SCCB_Write_Reg16(sensor->slv_addr, 0x003e, 0x00);       /* disable stream */

    return 0;
}

/*****************************GC CODE*****************************/
static uint32_t regValTable[25][7] = {
       //   0xb3 0xb8 0xb9 0x155 0xc2 0xcf 0xd9
            {0x00,0x01,0x00,0x08,0x10,0x08,0x0a},
            {0x10,0x01,0x0c,0x08,0x10,0x08,0x0a},
            {0x20,0x01,0x1b,0x08,0x10,0x08,0x0a},
            {0x30,0x01,0x2c,0x08,0x11,0x08,0x0c},
            {0x40,0x01,0x3f,0x08,0x12,0x08,0x0e},
            {0x50,0x02,0x16,0x08,0x14,0x08,0x12},
            {0x60,0x02,0x35,0x08,0x15,0x08,0x14},
            {0x70,0x03,0x16,0x08,0x17,0x08,0x18},
            {0x80,0x04,0x02,0x08,0x18,0x08,0x1a},
            {0x90,0x04,0x31,0x08,0x19,0x08,0x1c},
            {0xa0,0x05,0x32,0x08,0x1b,0x08,0x20},
            {0xb0,0x06,0x35,0x08,0x1c,0x08,0x22},
            {0xc0,0x08,0x04,0x08,0x1e,0x08,0x26},
            {0x5a,0x09,0x19,0x08,0x1c,0x08,0x26},
            {0x83,0x0b,0x0f,0x08,0x1c,0x08,0x26},
            {0x93,0x0d,0x12,0x08,0x1f,0x08,0x28},
            {0x84,0x10,0x00,0x0b,0x20,0x08,0x2a},
            {0x94,0x12,0x3a,0x0b,0x22,0x08,0x2e},
            {0x5d,0x1a,0x02,0x0b,0x27,0x08,0x38},
            {0x9b,0x1b,0x20,0x0b,0x28,0x08,0x3a},
            {0x8c,0x20,0x0f,0x0b,0x2a,0x08,0x3e},
            {0x9c,0x26,0x07,0x12,0x2d,0x08,0x44},
            {0xB6,0x36,0x21,0x12,0x2d,0x08,0x44},
            {0xad,0x37,0x3a,0x12,0x2d,0x08,0x44},
            {0xbd,0x3d,0x02,0x12,0x2d,0x08,0x44},
};

static uint32_t gainLevelTable[26] = {
        64,
        76,
        91,
        107,
        125,
        147,
        177,
        211,
        248,
        297,
        356,
        425,
        504,
        599,
        709,
        836,
        978,
        1153,
        1647,
        1651,
        1935,
        2292,
        3239,
        3959,
        4686,
        0xffffffff,
 };

static int SetSensorGain(sensor_t *sensor, uint32_t gain)
{
    int i;
    int total;
    uint32_t tol_dig_gain = 0;

    total = sizeof(gainLevelTable) / sizeof(uint32_t);

    for (i = 0; i < total; i++)

    {
        if ((gainLevelTable[i] <= gain)&&(gain < gainLevelTable[i+1]))
            break;
    }
    tol_dig_gain = gain*64/gainLevelTable[i];

    SCCB_Write_Reg16(sensor->slv_addr, 0x00b3,regValTable[i][0]);
    SCCB_Write_Reg16(sensor->slv_addr, 0x00b8,regValTable[i][1]);
    SCCB_Write_Reg16(sensor->slv_addr, 0x00b9,regValTable[i][2]);
    SCCB_Write_Reg16(sensor->slv_addr, 0x0155,regValTable[i][3]);
    SCCB_Write_Reg16(sensor->slv_addr, 0x031d,0x2d);
    SCCB_Write_Reg16(sensor->slv_addr, 0x00c2,regValTable[i][4]);
    SCCB_Write_Reg16(sensor->slv_addr, 0x00cf,regValTable[i][5]);
    SCCB_Write_Reg16(sensor->slv_addr, 0x00d9,regValTable[i][6]);
    SCCB_Write_Reg16(sensor->slv_addr, 0x031d,0x28);
    SCCB_Write_Reg16(sensor->slv_addr, 0x00b1,(tol_dig_gain>>6));
    SCCB_Write_Reg16(sensor->slv_addr, 0x00b2,((tol_dig_gain&0x3f)<<2));
    return 0;
}

static int SetSensorIntt(sensor_t *sensor, uint32_t intt)
{
    uint32_t frame_length=1125;

    if (intt> sensor->total_win.height) // line_frame_total
    {
         frame_length=intt+1;
    }
    else
    {
        frame_length=sensor->total_win.height;
    }
    SCCB_Write_Reg16(sensor->slv_addr, 0x0003,(intt>>8)&0x3f);
    SCCB_Write_Reg16(sensor->slv_addr, 0x0004,intt & 0xff);
    SCCB_Write_Reg16(sensor->slv_addr, 0x0041,(frame_length>>8));
    SCCB_Write_Reg16(sensor->slv_addr, 0x0042,(frame_length&0xff));

    return 0;
}

static int SetFlipMirrow(sensor_t *sensor, uint8_t type)
{
    if (type == FLIP_MIRROR_TYPE_NORMAL) SCCB_Write_Reg16(sensor->slv_addr, 0x0017, 0x00);
    else if (type == FLIP_MIRROR_TYPE_FLIP) SCCB_Write_Reg16(sensor->slv_addr, 0x0017, 0x01);
    else if (type == FLIP_MIRROR_TYPE_MIRROR) SCCB_Write_Reg16(sensor->slv_addr, 0x0017, 0x2);
    else if (type == FLIP_MIRROR_TYPE_FLIP_MIRROR) SCCB_Write_Reg16(sensor->slv_addr, 0x0017, 0x03);

    return 0;
}

/******************************************************/

static int set_exposure(sensor_t *sensor, BL_EXPO_TIME expo_time)
{
    uint64_t tmp = expo_time * (uint64_t)sensor->pix_clk;
    int num_line = NS_TO_SEC(tmp / sensor->total_win.width);

    SetSensorIntt(sensor, num_line);
    return 0;
}

static int set_gain(sensor_t *sensor, BL_GAIN_DB gain)
{
    float gain2 = pow(2, GAIN_DB_INT_TO_FLOAT(gain)/6)*64;
    SetSensorGain(sensor, gain2);
    return 0;
}

static int set_flipmirror(sensor_t *sensor, FLIP_MIRROR_TYPE_E type)
{
    uint8_t type_e = type;
    SetFlipMirrow(sensor, type_e);
    return 0;
}

static int set_fps(sensor_t *sensor, uint32_t fps)
{
    return 0;
}

static int quick_mode_get_ae_exposure(sensor_t *sensor, BL_EXPO_TIME *expo_time)
{
    uint8_t data = 0;
    uint32_t expo = 0;
    // SCCB_Write_Reg16(sensor->slv_addr, 0xfe, 0x01);
    SCCB_Read_Reg16(sensor->slv_addr, 0x0003, &data);
    expo = data << 8;
    SCCB_Read_Reg16(sensor->slv_addr, 0x0004, &data);
    expo = expo + data;

    printf("expo = %d\r\n", expo);

    return 0;
}

static int quick_mode_get_ae_gain(sensor_t *sensor, BL_GAIN_DB *gain)
{
    uint8_t data = 0;
    uint32_t gain_2093 = 0;

    SCCB_Read_Reg16(sensor->slv_addr, 0x00b1, &data);
    gain_2093 = (data & 0xf) << 6;
    SCCB_Read_Reg16(sensor->slv_addr, 0x00b2, &data);
    gain_2093 = gain_2093 + (data & 0x3f);

    printf("gain = %d\r\n", gain_2093);

    return 0;
}

static int quick_mode_get_awb_gain(sensor_t *sensor, int *r_gain, int *g_gain, int *b_gain)
{
    uint8_t r_gain_2093, g_gain_2093, b_gain_2093;

    SCCB_Read_Reg16(sensor->slv_addr, 0x01a4, &r_gain_2093);
    SCCB_Read_Reg16(sensor->slv_addr, 0x01a5, &g_gain_2093);
    SCCB_Read_Reg16(sensor->slv_addr, 0x01a6, &b_gain_2093);

    printf("r_gain = %d, g_gain = %d, b_gain = %d\r\n", r_gain_2093, g_gain_2093, b_gain_2093);

    return 0;
}

static int quick_mode_reset(sensor_t *sensor)
{
    // sensor blc
    SCCB_Write_Reg16(sensor->slv_addr, 0x0140, 0x23);
    SCCB_Write_Reg16(sensor->slv_addr, 0x04e0, 0x18);

    // disable sensor aec mode
    SCCB_Write_Reg16(sensor->slv_addr, 0x01af, 0x09);
    // disable sensor awb mode
    SCCB_Write_Reg16(sensor->slv_addr, 0x01a0, 0x00);

    // reset awb gain
    SCCB_Write_Reg16(sensor->slv_addr, 0x01a4, 0x40);
    SCCB_Write_Reg16(sensor->slv_addr, 0x01a5, 0x40);
    SCCB_Write_Reg16(sensor->slv_addr, 0x01a6, 0x40);

    return 0;
}

static int setFmt(sensor_t *sensor)
{
    int i;
    FORMAT_INDEX format_index;
    const sensor_reg_16_8_t *init_reglist;

    switch (sensor->video_mode) {
    case VIDEO_MODE_1080P_25:
        if (DSP2_INPUT_DVP == DSP2_INPUT_MODE) {
            format_index = FORMAT_INDEX_DVP_1080P_25;
            if (sensor->quick_mode.is_quick_mode   == 1) {
                init_reglist = init_reglist_25fps_quick_start;
            } else {
                init_reglist = init_reglist_25fps;
            }
        }
        else {
            BL_LOGE("gc2093 format[%d] not support now\r\n", sensor->video_mode);
            return -1;
        }
        sensor->max_expo_time = EXPO_TIME_1_25_SEC;       /* 1/25 sec */
        sensor->out_win.width  = 1920;
        sensor->out_win.height = 1080;
        break;

    default:
        BL_LOGE("set_format error: invalid video mode!\r\n");
        return -1;
    }

    sensor->pix_clk             = format_info[format_index].pix_clk;
    sensor->fps                 = format_info[format_index].fps;
    sensor->total_win.width     = format_info[format_index].total_width;
    sensor->total_win.height    = format_info[format_index].total_height;
    sensor->bayer_pattern       = format_info[format_index].bayer_pattern;


    for (i = 0; init_reglist[i].addr != REGLIST_END; i++) {
        SCCB_Write_Reg16(sensor->slv_addr, init_reglist[i].addr, (uint8_t)init_reglist[i].data);
    }

    // uint8_t data;
    // // SCCB_Write_Reg16(sensor->slv_addr, 0xfe, 0x01);
    // SCCB_Read_Reg16(sensor->slv_addr, 0x02aa, &data);
    // printf("[0x02aa] = 0x%x\r\n", data);
    // SCCB_Read_Reg16(sensor->slv_addr, 0x0027, &data);
    // printf("[0x0027] = 0x%x\r\n", data);
    // sensor->video_mode = video_mode;
    // SCCB_Read_Reg16(sensor->slv_addr, 0x0187, &data);
    // printf("[0x0187] = 0x%x\r\n", data);

    return 0;
}

static int get_property(sensor_t *sensor, sensor_property_t *property)
{
    CHECK_PARAM(sensor != NULL);

    property->bayer_pattern = sensor->bayer_pattern;//BAYER_PATTERN_BG;

    return 0;
}

static int probe(void)
{
	return sensor_probe(SLAVE_ADDR, REG_SENSOR_ID_H, REG_SENSOR_ID_L, SENSOR_ID_H, SENSOR_ID_L);
}

static int init(sensor_t *sensor)
{
    int mode_num = sizeof(gc2093_mode)/sizeof(gc2093_mode[0]);
    if (!is_sensor_dsp2_input_match(gc2093_mode, mode_num)) {
        return -1;
    }

    /* Initialize sensor structure */
    SENSOR_INIT_COMMON(GC2093);

    sensor->quick_mode.is_quick_mode   = 1;
    sensor->quick_mode.get_ae_exposure = quick_mode_get_ae_exposure;
    sensor->quick_mode.get_ae_gain     = quick_mode_get_ae_gain;
    sensor->quick_mode.get_awb_gain    = quick_mode_get_awb_gain;
    sensor->quick_mode.reset           = quick_mode_reset;

    //set_format(sensor, VIDEO_MODE_1080P_25);
    return 0;
}

const BL_SENSOR_DESC_T sensor_desc_gc2093 ATTR_SENSOR_DEVICE_TABLE =
{
	"GC2093",
    SLAVE_ADDR,
    probe,
    init,
    setFmt,
};

