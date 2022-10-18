#include <bl808.h>
#include "sensor_internal.h"
#include "sccb.h"
#include "c2399.h"

/* C2399 sensor info */
#define SLAVE_ADDR                  0x36
#define SENSOR_ID_H                 0x02
#define SENSOR_ID_L                 0x0B
#define MIN_EXPO_TIME               32848                       /* 32848 ns or -49.5 dB */
#define MAX_EXPO_TIME               EXPO_TIME_1_25_SEC          /* 1/25 sec */
#define REG_ADDR_BIT                SENSOR_REG_ADDR_16BIT

//#define MAX_GAIN                    GAIN_DB_FLOAT_TO_INT(53.25)    /* 53.25 dB */
#define MAX_GAIN                    GAIN_DB_FLOAT_TO_INT(36)    /* limit max gain t0 36 dB to avoid bad noise */
#define MAX_AGAIN                   GAIN_DB_FLOAT_TO_INT(23.625)   /* 23.625 dB or 15.5x */
#define MIN_GAIN_STEP               (GAIN_6_DB / 16)            /* 0.375 dB */

/* C2399 registers */
#define REG_SENSOR_ID_H             0x0000
#define REG_SENSOR_ID_L             0x0001
#define REG_GROUP_HOLD              0x3812
#define REG_PRECHARGE               0x3314
#define REG_DIGITAL_GAIN            0x3e06
#define REG_DIGITAL_FINE_GAIN       0x3e07
#define REG_COARSE_GAIN             0x3e08
#define REG_FINE_GAIN               0x3e09
#define REG_SHUTTER_TIME_H          0x0202
#define REG_SHUTTER_TIME_L          0x0303

#define REG_TOTAL_WIDTH_H           0x3f06
#define REG_TOTAL_WIDTH_L           0x3f07
#define REG_TOTAL_HEIGHT_H          0x3f04
#define REG_TOTAL_HEIGHT_L          0x3f05

#define REG_OUT_WIDTH_H             0x3f06
#define REG_OUT_WIDTH_L             0x3f07
#define REG_OUT_HEIHT_H             0x3f04
#define REG_OUT_HEIHT_L             0x3f05

#define REG_OUT_START_PIXEL_H       0x3f00
#define REG_OUT_START_PIXEL_L       0x3f01
#define REG_OUT_START_LINE_H        0x3f02
#define REG_OUT_START_LINE_L        0x3f03

typedef enum {
    FORMAT_INDEX_1080P_30 = 0,
    FORMAT_INDEX_1080P_25,
    FORMAT_INDEX_1080P_20,
    FORMAT_INDEX_1080P_20_2,
    FORMAT_INDEX_1080P_15,
    FORMAT_INDEX_1080P_12P5,
    FORMAT_INDEX_1080P_10,
    FORMAT_INDEX_1080P_5,
    FORMAT_INDEX_INVALID,
} FORMAT_INDEX;

static const int c2399_mode[] = {\
    DSP2_INPUT_DVP\
};

/* TODO: make total height even to workaround bayer reverse issue in bottom 3 lines */
static const sensor_format_t format_info[] = {
    {   /* for 1080p30 */
        .total_width    = 1980,
        .total_height   = 1103,
        .pix_clk        = 65600000,
        .fps            = 30,
    },
};

static const sensor_reg_16_8_t init_reglist_30fps[] =
{
    {0x3288, 0x50}, //tm
    {0x0401, 0x3b},
    {0x0403, 0x00},

    {0x3298, 0x42},
    {0x3290, 0x69},
    {0x3286, 0x77},
    {0x32aa, 0x0f},
    {0x3295, 0x02},
    {0x328b, 0x20},

    {0x3211, 0x16},
    {0x3216, 0x28},
    {0x3217, 0x28},
    {0x3224, 0x99},
    {0x3212, 0x80},

    {0x3d00, 0x33}, // bpc
    {0x3187, 0x07},
    {0x3222, 0x82},
    {0x322c, 0x04},
    {0x3c01, 0x13}, // raw gain
    {0x3087, 0xf0}, //aec off
    {0x3584, 0x02}, // aclk use sclk
    {0x3108, 0xef}, // blc && 10bit
    {0x3112, 0xe0},
    {0x3115, 0x00},
    {0x3118, 0x50},
    {0x311b, 0x01},
    {0x3126, 0x02},
    {0x0202, 0x02}, // integration time write hi
    {0x3584, 0x22}, // clk
    {0x3009, 0x05}, // h windows offset
    {0x022d, 0x1f},
    {0x0101, 0x01}, // hmirror
    {0x0340, 0x04}, // frame length hi  1104
    {0x0341, 0x50}, // frame length lo
    {0x0342, 0x07}, // line length hi 1980
    {0x0343, 0xbc}, // line length lo

    //AEC/AWB},
    {0x3082, 0x00},
    {0x3083, 0x0a},
    {0x3084, 0x80}, // light target
    //0x3087, 0xd0}, // 30/31: 50/60 AEC on f0: aec off
    {0x3089, 0x10}, //0x1c again controlled by reg3293/32a9
                   //0x12 while AEC on(0x3087[7]=1)
                   //0x10 for platform AEC
    {0x3f10, 0x00}, //avg ROI off
    //avg ROI on
    //0x3f10, 0x11
    //0x3f04, 0x07
    //0x3f05, 0x80
    //0x3f06, 0x04
    //0x3f07, 0x38
    //0x3f8c, 0x00 //awb off
    //0x3f8c, 0x32 //awb on

    //dvp},
    {0x0303, 0x01}, // sys driver
    {0x0309, 0x20}, // pll
    {0x0307, 0x52}, // pll
    {0x3882, 0x01},
    {0x3584, 0x2a}, // aclk
    {0x3810, 0x00}, // mipi disable
    {0x3295, 0x55}, //pwr
    {0x3986, 0x01}, // dvp enable
    {0x3981, 0x23}, // dvp
    {0x3987, 0x18}, // half-driver on and pclk inv, data delay
    {0x3988, 0xF8}, // to increasing the driving of pclk and remove the delay on pclk
    {0x3905, 0x00}, // fromat

    {0x3600, 0xc8},
    {0x3602, 0x01},
    {0x3605, 0x22},
    {0x3607, 0x22},
    {0x3583, 0x10}, //i2c
    {0x3584, 0x02}, //i2c
    {0xa000, 0x0b},
    {0xa001, 0xd0},
    {0xa002, 0x00},
    {0xa003, 0x80},
    {0xa004, 0x80},
    {0xa005, 0x80},
    {0xa006, 0x80},
    {0xa007, 0x00},
    {0xa008, 0xce},
    {0xa009, 0x01},
    {0xa00a, 0x03},
    {0xa00b, 0x1c},
    {0xa00c, 0x83},
    {0xa00d, 0x25},
    {0xa00e, 0x8c},
    {0xa00f, 0x01},
    {0xa010, 0x0a},
    {0xa011, 0x10},
    {0xa012, 0x8d},
    {0xa013, 0x01},
    {0xa014, 0x8c},
    {0xa015, 0xd0},
    {0xa016, 0xc6},
    {0xa017, 0xd0},
    {0xa018, 0xa9},
    {0xa019, 0x61},
    {0xa01a, 0x05},
    {0xa01b, 0x81},
    {0xa01c, 0x30},
    {0xa01d, 0x60},
    {0xa01e, 0x06},
    {0xa01f, 0x01},
    {0xa020, 0x88},
    {0xa021, 0x90},
    {0xa022, 0x8f},
    {0xa023, 0x01},
    {0xa024, 0x88},
    {0xa025, 0x10},
    {0xa026, 0x0f},
    {0xa027, 0x81},
    {0xa028, 0x50},
    {0xa029, 0xe1},
    {0xa02a, 0x8f},
    {0xa02b, 0x04},
    {0xa02c, 0x03},
    {0xa02d, 0x38},
    {0xa02e, 0x9a},
    {0xa02f, 0xd0},
    {0xa030, 0x0e},
    {0xa031, 0x83},
    {0xa032, 0xaf},
    {0xa033, 0x50},
    {0xa034, 0xb0},
    {0xa035, 0xe1},
    {0xa036, 0x8f},
    {0xa037, 0x84},
    {0xa038, 0x83},
    {0xa039, 0x38},
    {0xa03a, 0x20},
    {0xa03b, 0xd0},
    {0xa03c, 0x90},
    {0xa03d, 0x60},
    {0xa03e, 0x2e},
    {0xa03f, 0xd0},
    {0xa040, 0x90},
    {0xa041, 0x61},
    {0xa042, 0x8f},
    {0xa043, 0x04},
    {0xa044, 0x03},
    {0xa045, 0x38},
    {0xa046, 0xa6},
    {0xa047, 0xd0},
    {0xa048, 0xa0},
    {0xa049, 0xe0},
    {0xa04a, 0x2e},
    {0xa04b, 0x50},
    {0xa04c, 0xf0},
    {0xa04d, 0xe0},
    {0xa04e, 0x0f},
    {0xa04f, 0x04},
    {0xa050, 0x83},
    {0xa051, 0x38},
    {0xa052, 0xac},
    {0xa053, 0xd0},
    {0xa054, 0xb0},
    {0xa055, 0x60},
    {0xa056, 0x2e},
    {0xa057, 0xd0},
    {0xa058, 0x8f},
    {0xa059, 0x90},
    {0xa05a, 0x70},
    {0xa05b, 0xf9},
    {0xa05c, 0x8e},
    {0xa05d, 0x01},
    {0xa05e, 0xa7},
    {0xa05f, 0x60},
    {0xa060, 0x85},
    {0xa061, 0x01},
    {0xa062, 0xb1},
    {0xa063, 0x60},
    {0xa064, 0x06},
    {0xa065, 0x81},
    {0xa066, 0x0e},
    {0xa067, 0x10},
    {0xa068, 0x08},
    {0xa069, 0x01},
    {0xa06a, 0x90},
    {0xa06b, 0x60},
    {0xa06c, 0x05},
    {0xa06d, 0x01},
    {0xa06e, 0x36},
    {0xa06f, 0xe0},
    {0xa070, 0x86},
    {0xa071, 0x01},
    {0xa072, 0x08},
    {0xa073, 0x83},
    {0xa074, 0x0d},
    {0xa075, 0x10},
    {0xa076, 0x0a},
    {0xa077, 0x01},
    {0xa078, 0x0c},
    {0xa079, 0x9c},
    {0xa07a, 0x03},
    {0xa07b, 0x01},
    {0xa07c, 0xce},
    {0xa07d, 0x9d},
    {0xa07e, 0xce},
    {0xa07f, 0x1c},
    {0xa080, 0x09},
    {0xa081, 0x00},
    {0xa082, 0x83},
    {0xa083, 0x2d},
    {0xa084, 0x81},
    {0xa085, 0xae},
    {0xa086, 0x0b},
    {0xa087, 0x2c},
    {0xa088, 0x0b},
    {0xa089, 0x2f},
    {0xa08a, 0x45},
    {0xa08b, 0xd0},
    {0xa08c, 0x83},
    {0xa08d, 0x83},
    {0xa08e, 0x41},
    {0xa08f, 0xd0},
    {0x3583, 0x00}, // i2c
    {0x3584, 0x2a}, // i2c

    {0x0100, 0x01}, //stream on

    //[blc off]
    //0x3108, 0x00
    //[sleep]
    //0x0100, 0x00
    //0x3288, 0xd0
    //0x3289, 0xc0
    //0x3295, 0x42


    /* end of reg list */
    {REGLIST_END, 0x00},
};

static int enable(sensor_t *sensor)
{
    SCCB_Write_Reg16(sensor->slv_addr, 0x0100, 0x01);       /* enable stream */

    return 0;
}

static int disable(sensor_t *sensor)
{
    SCCB_Write_Reg16(sensor->slv_addr, 0x0100, 0x00);       /* disable stream */

    return 0;
}

static int set_exposure(sensor_t *sensor, BL_EXPO_TIME expo_time)
{
#if 0
    /* num of half lines = exposure time / (horizontal total pixeles / pixel clock) */
    uint64_t tmp = expo_time * (uint64_t)sensor->pix_clk;
    int num_half_line = NS_TO_SEC(tmp * 2 / sensor->total_win.width);        /* 16bit */

//    BL_LOGD("set_exposure: tmp %lld\r\n", tmp);

    if (num_half_line > sensor->total_win.height *2 - 5)
        num_half_line = sensor->total_win.height *2 - 5;

#if 0
    if (expo_time_sec_LS24 == EXPO_TIME_1_50_SEC)
        num_half_line = 800;

    if (expo_time_sec_LS24 == EXPO_TIME_1_100_SEC)
        num_half_line = 224;
#endif

    BL_LOGD("\t\t set_exposure: num_half_line %d\r\n", num_half_line);

    SCCB_Write_Reg16(sensor->slv_addr, REG_SHUTTER_TIME_H, (num_half_line >> 4) & 0xFF);
    SCCB_Write_Reg16(sensor->slv_addr, REG_SHUTTER_TIME_L, (num_half_line << 4) & 0xF0);

    BL_LOGD("\t\t shutter_h 0x%02x, shutter_l 0x%02x\r\n", (num_half_line >> 4) & 0xFF, (num_half_line << 4) & 0xF0);

    if (num_half_line < 80) {
        SCCB_Write_Reg16(sensor->slv_addr, REG_PRECHARGE, 0x14);
    } else if (num_half_line > 160) {
        SCCB_Write_Reg16(sensor->slv_addr, REG_PRECHARGE, 0x04);
    }

#endif
    return 0;
}

static int set_gain(sensor_t *sensor, BL_GAIN_DB gain)
{
#if 0
    BL_GAIN_DB total_again, total_dgain;
    uint8_t coarse_gain = 0, fine_gain = 0, dgain = 0, fine_dgain = 0;
    uint8_t reg1, reg2, reg3;
    int tmp, num_of_6db;

    if (gain > MAX_AGAIN) {
        total_again = MAX_AGAIN;
        total_dgain = gain - MAX_AGAIN;
    } else {
        total_again = gain;
        total_dgain = 0;
    }

    BL_LOGD("\t\t again: %.4f dB, dgain %.4f dB\r\n", GAIN_DB_INT_TO_FLOAT(total_again), GAIN_DB_INT_TO_FLOAT(total_dgain));

    /****************** Analog Gain ********************************************/
    /* calculate the value for gain_coarse (0x3e08) */
    /* first calculate the number of ones for gain_coarse */
    num_of_6db = GAIN_DB_TO_INT((total_again / 6));
    tmp = num_of_6db + 2;

    if (tmp > 8)
        tmp = 8;

    /* calculate gain_coarse */
    coarse_gain = (1 << tmp) - 1;

    /* calculate the value for fine gain (0x3e09) */
    tmp = total_again - INT_TO_GAIN_DB(num_of_6db * 6);     /* nomalize to 0~6 dB range */
    tmp = DIV_ROUND(tmp, sensor->min_gain_step);     /* calculate the number of steps for fine gain */
    fine_gain = 0x10 + tmp;

    /****************** Digital Gain ********************************************/
    /* calculate the value for dgain (0x3e06) */
    /* first calculate the number of ones for dgain */
    num_of_6db = GAIN_DB_TO_INT((total_dgain / 6));

    /* calculate dgain */
    dgain = (1 << num_of_6db) - 1;

    /* calculate the value for fine dgain (0x3e07) */
    tmp = total_dgain - INT_TO_GAIN_DB(num_of_6db * 6);     /* nomalize to 0~6 dB range */
    tmp = DIV_ROUND(tmp, sensor->min_gain_step);            /* calculate the number of steps for fine gain */
    fine_dgain = 0x80 + (tmp << 3);

    /* if fine_dgain is very close to 6dB, dgain is incremented */
    if (fine_dgain == 0x0) {
        fine_dgain = 0x80;
        dgain = (1 << (num_of_6db + 1)) - 1;       /* dgain increase 6dB */
    }

    BL_LOGD("\t\t coarse_gain 0x%02x, fine_gain 0x%2x, dgain 0x%02x, fine_dgain 0x%02x\r\n",
        coarse_gain, fine_gain, dgain, fine_dgain);

    /* do the gain switch sequence */
    if (coarse_gain == 0x03) {           /* gain < 2 */
        reg1 = 0x06;
        reg2 = 0x48;
        reg3 = 0x08;
    } else if (coarse_gain == 0x07) {    /* 2 <= gain < 4 */
        reg1 = 0x14;
        reg2 = 0x48;
        reg3 = 0x08;
    } else if (coarse_gain == 0x0F) {    /* 4 <= gain < 8 */
        reg1 = 0x18;
        reg2 = 0x48;
        reg3 = 0x08;
    } else if (coarse_gain == 0x1F && fine_gain < 0x1F) {   /* 8 <= gain < 15.5 */
        reg1 = 0x13;
        reg2 = 0x48;
        reg3 = 0x08;
    } else if (dgain == 0x0) {                        /* 15.5 <= gain < 31 */
        reg1 = 0x89;
        reg2 = 0x78;
        reg3 = 0x48;
    } else {                        /* gain >= 31 */
        reg1 = 0x89;
        reg2 = 0x78;
        reg3 = 0x78;
    }

    SCCB_Write_Reg16(sensor->slv_addr, REG_COARSE_GAIN, coarse_gain);
    SCCB_Write_Reg16(sensor->slv_addr, REG_FINE_GAIN, fine_gain);
    SCCB_Write_Reg16(sensor->slv_addr, REG_DIGITAL_GAIN, dgain);
    SCCB_Write_Reg16(sensor->slv_addr, REG_DIGITAL_FINE_GAIN, fine_dgain);

    SCCB_Write_Reg16(sensor->slv_addr, REG_GROUP_HOLD, 0x0);

    SCCB_Write_Reg16(sensor->slv_addr, 0x3301, reg1);
    SCCB_Write_Reg16(sensor->slv_addr, 0x3306, reg2);
    SCCB_Write_Reg16(sensor->slv_addr, 0x3632, reg3);

    SCCB_Write_Reg16(sensor->slv_addr, REG_GROUP_HOLD, 0x30);
#endif
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
    case VIDEO_MODE_1080P_30:
        format_index = FORMAT_INDEX_1080P_30;
        init_reglist = init_reglist_30fps;
        sensor->max_expo_time = EXPO_TIME_1_30_SEC;
        break;



    default:
        BL_LOGE("set_format error: invalid video mode!\r\n");
        return -1;
    }

    sensor->pix_clk         = format_info[format_index].pix_clk;
    sensor->fps             = format_info[format_index].fps;
    sensor->total_win.width     = format_info[format_index].total_width;
    sensor->total_win.height    = format_info[format_index].total_height;
    sensor->out_win.width = 1920;
    sensor->out_win.height = 1080;
    sensor->dsp2_out_win.width  = 1920;
    sensor->dsp2_out_win.height = 1080;

    for (i = 0; init_reglist[i].addr != REGLIST_END; i++) {
        SCCB_Write_Reg16(sensor->slv_addr, init_reglist[i].addr, (uint8_t)init_reglist[i].data);
    }

//    SCCB_Write_Reg16(sensor->slv_addr, REG_TOTAL_WIDTH_H, (uint8_t)(sensor->total_win.width >> 8));
//    SCCB_Write_Reg16(sensor->slv_addr, REG_TOTAL_WIDTH_L, (uint8_t)sensor->total_win.width);
//    SCCB_Write_Reg16(sensor->slv_addr, REG_TOTAL_HEIGHT_H, (uint8_t)(sensor->total_win.height >> 8));
//    SCCB_Write_Reg16(sensor->slv_addr, REG_TOTAL_HEIGHT_L, (uint8_t)sensor->total_win.height);

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
    return sensor_probe(SLAVE_ADDR, REG_SENSOR_ID_H, REG_SENSOR_ID_L, SENSOR_ID_H, SENSOR_ID_L);
}

static int init(sensor_t *sensor)
{
    int mode_num = sizeof(c2399_mode)/sizeof(c2399_mode[0]);
    if (!is_sensor_dsp2_input_match(c2399_mode, mode_num)) {
        return -1;
    }

    /* Initialize sensor structure */
    SENSOR_INIT_COMMON(C2399);

    //set_format(sensor, VIDEO_MODE_1080P_30);

    // SCCB_Write_Reg16(sensor->slv_addr, 0x3641, 0x1);        /* IO driver control */
    // SCCB_Write_Reg16(sensor->slv_addr, 0x3d08, 0x1);        /* invert the sensor pix clk polarity */
    // SCCB_Write_Reg16(sensor->slv_addr, 0x3640, 0x0);        /* pixel delay */

    return 0;
}

const BL_SENSOR_DESC_T sensor_desc_c2399 ATTR_SENSOR_DEVICE_TABLE =
{
    "C2399",
    SLAVE_ADDR,
    probe,
    init,
    setFmt,
};

