#include <bl808.h>
#include "sensor_internal.h"
#include "sccb.h"
#include "sc2232.h"

/* SC2232 sensor info */
#define SLAVE_ADDR                  0x30
#define SENSOR_ID_H                 0x22
#define SENSOR_ID_L                 0x32
#define MIN_EXPO_TIME               32848                       /* 32848 ns or -49.5 dB */
#define MAX_EXPO_TIME               EXPO_TIME_1_25_SEC          /* 1/25 sec */
#define REG_ADDR_BIT                SENSOR_REG_ADDR_16BIT

//#define MAX_GAIN                    GAIN_DB_FLOAT_TO_INT(53.25)    /* 53.25 dB */
#define MAX_GAIN                    GAIN_DB_FLOAT_TO_INT(36)    /* limit max gain t0 36 dB to avoid bad noise */
#define MAX_AGAIN                   GAIN_DB_FLOAT_TO_INT(23.625)   /* 23.625 dB or 15.5x */
#define MIN_GAIN_STEP               (GAIN_6_DB / 16)            /* 0.375 dB */

/* SC2232 registers */
#define REG_SENSOR_ID_H             0x3107
#define REG_SENSOR_ID_L             0x3108
#define REG_GROUP_HOLD              0x3812
#define REG_PRECHARGE               0x3314
#define REG_DIGITAL_GAIN            0x3e06
#define REG_DIGITAL_FINE_GAIN       0x3e07
#define REG_COARSE_GAIN             0x3e08
#define REG_FINE_GAIN               0x3e09
#define REG_SHUTTER_TIME_H          0x3e01
#define REG_SHUTTER_TIME_L          0x3e02

#define REG_TOTAL_WIDTH_H           0x320c
#define REG_TOTAL_WIDTH_L           0x320d
#define REG_TOTAL_HEIGHT_H          0x320e
#define REG_TOTAL_HEIGHT_L          0x320f

#define REG_OUT_WIDTH_H             0x3208
#define REG_OUT_WIDTH_L             0x3209
#define REG_OUT_HEIHT_H             0x320a
#define REG_OUT_HEIHT_L             0x320b

#define REG_OUT_START_PIXEL_H       0x3210
#define REG_OUT_START_PIXEL_L       0x3211
#define REG_OUT_START_LINE_H        0x3212
#define REG_OUT_START_LINE_L        0x3213

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

static const int sc2232_mode[] = {\
    DSP2_INPUT_DVP,\
};

/* TODO: make total height even to workaround bayer reverse issue in bottom 3 lines */
static const sensor_format_t format_info[] = {
    {   /* for 1080p30 */
        .total_width	= 2080,
        .total_height	= 1250,
        .pix_clk        = 78000000,
        .fps            = 30,
    },
    {   /* for 1080p25 */
        .total_width	= 2080,
        .total_height	= 1500,
        .pix_clk        = 78000000,
        .fps            = 25,
    },
    {   /* for 1080p20 */
        .total_width	= 2200,
        .total_height	= 1126,
        .pix_clk        = 49500000,
        .fps            = 20,
    },
    {   /* for 1080p20_2 */
        .total_width	= 2080,
        .total_height	= 1876,
        .pix_clk        = 78000000,
        .fps            = 20,
    },
    {   /* for 1080p15 */
        .total_width	= 2080,
        .total_height	= 2500,
        .pix_clk        = 78000000,
        .fps            = 15,
    },
    {   /* for 1080p12.5 */
        .total_width	= 2080,
        .total_height	= 3000,
        .pix_clk        = 78000000,
        .fps            = 13,
    },
    {   /* for 1080p10 */
        .total_width	= 2080,
        .total_height	= 3750,
        .pix_clk        = 78000000,
        .fps            = 10,
    },
    {   /* for 1080p5 */
        .total_width	= 2080,
        .total_height	= 7500,
        .pix_clk        = 78000000,
        .fps            = 5,
    },
};

static const sensor_reg_16_8_t init_reglist_30fps[] =
{
    {0x0103, 0x01}, /* software reset */
    {0x0100, 0x00}, /* sleep mode */
    {0x3018, 0x1f},
    {0x3019, 0xff},
    {0x301c, 0xb4},
    {0x3624, 0x08},
    {0x5000, 0x06}, /* black/white dead pixel cancel enable */
    {0x3213, 0x0a}, /* start line L */
    {0x337f, 0x03},
    {0x3368, 0x04},
    {0x3369, 0x00},
    {0x336a, 0x00},
    {0x336b, 0x00},
    {0x3367, 0x08},
    {0x330e, 0x30},
    {0x3366, 0x7c},
    {0x3302, 0x1f},
    {0x303f, 0x81},
    {0x3907, 0x00}, /* BLC target */
    {0x3902, 0x45}, /* BLC auto mode */
    {0x3908, 0x11}, /* BLC target */
    {0x335e, 0x01},
    {0x335f, 0x03},
    {0x337c, 0x04},
    {0x337d, 0x06},
    {0x33a0, 0x05},
    {0x3633, 0x4f},
    {0x3622, 0x06},
    {0x3631, 0x84},
    {0x366e, 0x08},
    {0x3637, 0x59},
    {0x3326, 0x00},
    {0x3303, 0x20},
    {0x3638, 0x1f},
    {0x3636, 0x25},
    {0x3625, 0x02},
    {0x331b, 0x83},
    {0x3333, 0x30},
    {0x3635, 0xa0},
    {0x363c, 0x05},
    {0x363b, 0x0b},
    {0x3038, 0xff},
    {0x3639, 0x09},
    {0x3621, 0x28},
    {0x3211, 0x0c}, /* start pixel L */
    {0x366f, 0x2f},
    {0x3320, 0x01},
    {0x331e, 0x19},
    {0x330b, 0xd3},
    {0x3620, 0x28},
    {0x3309, 0x60},
    {0x331f, 0x59},
    {0x3308, 0x10},
    {0x3f00, 0x07},
    {0x3630, 0x1c},
    {0x320c, 0x08}, /* pixel width: 2080 */
    {0x320d, 0x20},
    {0x320e, 0x04}, /* line height: 1250 */
    {0x320f, 0xe2},
    {0x3f04, 0x03},
    {0x3f05, 0xec},
    {0x3235, 0x09}, /* group hold valid line in one frame */
    {0x3236, 0xc2},


    {0x3039, 0x54},         /* 78MHz pix clk */
//    {0x3039, 0x74},       /* 39MHz pix clk */
//    {0x3039, 0x64},       /* 39MHz pix clk */
    {0x303a, 0xb3},
//    {0x303a, 0xf3},
    {0x303b, 0x06},
    {0x303c, 0x0e},
    {0x3034, 0x01},
    {0x3035, 0x9b},
    {0x33aa, 0x10},
    {0x3640, 0x01}, /* PCLK DLY, 2ns/step */
    {0x3677, 0x84},
    {0x3678, 0x88},
    {0x3679, 0x88},
    {0x367e, 0x08},
    {0x367f, 0x28},
    {0x3670, 0x0c},
    {0x3690, 0x34},
    {0x3691, 0x11},
    {0x3692, 0x42},
    {0x369c, 0x08},
    {0x369d, 0x28},
    {0x360f, 0x01},
    {0x3671, 0xc6},
    {0x3672, 0x06},
    {0x3673, 0x16},
    {0x367a, 0x28},
    {0x367b, 0x3f},
    {0x3802, 0x00}, /* group hold, frame delay */
    {0x3222, 0x29},
    {0x3901, 0x02},
    {0x3905, 0x98}, /* BLC channel */
    {0x3e1e, 0x34},
    {0x3314, 0x08},
    {0x391b, 0x80},
    {0x5780, 0xff}, /* DPC */
    {0x5781, 0x04}, /* white dead pixel threshold0 */
    {0x5785, 0x18}, /* black dead pixel threshold0 */
    {0x3301, 0x06},
    {0x3306, 0x48},
    {0x3632, 0x08},
    {0x3e00, 0x00},
    //{0x3e01, 0x46}, /* shutter time */
    //{0x3e02, 0x10},
    //{0x3e03, 0x0b}, /* gain */
    //{0x3e06, 0x00},
    {0x3e07, 0x80},
    {0x3e08, 0x03},
    {0x3e09, 0x10},

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

    return 0;
}

static int set_gain(sensor_t *sensor, BL_GAIN_DB gain)
{
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
        sensor->max_expo_time = EXPO_TIME_1_30_SEC;       /* 1/30 sec */
		break;

	case VIDEO_MODE_1080P_25:
        format_index = FORMAT_INDEX_1080P_25;
        init_reglist = init_reglist_30fps;
        sensor->max_expo_time = EXPO_TIME_1_25_SEC;       /* 1/25 sec */
		break;

	case VIDEO_MODE_1080P_20:
        format_index = FORMAT_INDEX_1080P_20_2;
        init_reglist = init_reglist_30fps;
        sensor->max_expo_time = EXPO_TIME_1_25_SEC;       /* 1/25 sec */
		break;

	case VIDEO_MODE_1080P_15:
        format_index = FORMAT_INDEX_1080P_15;
        init_reglist = init_reglist_30fps;
        sensor->max_expo_time = EXPO_TIME_1_25_SEC;       /* 1/25 sec */
		break;

	case VIDEO_MODE_1080P_12P5:
        format_index = FORMAT_INDEX_1080P_12P5;
        init_reglist = init_reglist_30fps;
        sensor->max_expo_time = EXPO_TIME_1_25_SEC;       /* 1/25 sec */
		break;

	case VIDEO_MODE_1080P_10:
		format_index = FORMAT_INDEX_1080P_10;
		init_reglist = init_reglist_30fps;
		sensor->max_expo_time = EXPO_TIME_1_25_SEC; 	  /* 1/25 sec */
		break;

    case VIDEO_MODE_1080P_5:
        format_index = FORMAT_INDEX_1080P_5;
        init_reglist = init_reglist_30fps;
        sensor->max_expo_time = EXPO_TIME_1_25_SEC;       /* 1/25 sec */
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

    SCCB_Write_Reg16(sensor->slv_addr, REG_TOTAL_WIDTH_H, (uint8_t)(sensor->total_win.width >> 8));
    SCCB_Write_Reg16(sensor->slv_addr, REG_TOTAL_WIDTH_L, (uint8_t)sensor->total_win.width);
    SCCB_Write_Reg16(sensor->slv_addr, REG_TOTAL_HEIGHT_H, (uint8_t)(sensor->total_win.height >> 8));
    SCCB_Write_Reg16(sensor->slv_addr, REG_TOTAL_HEIGHT_L, (uint8_t)sensor->total_win.height);


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
    int mode_num = sizeof(sc2232_mode)/sizeof(sc2232_mode[0]);
    if (!is_sensor_dsp2_input_match(sc2232_mode, mode_num)) {
        return -1;
    }
    /* Initialize sensor structure */
    SENSOR_INIT_COMMON(SC2232);
/*
#if (BL80X_HW_VER <= BL80X_HW_A0)
    set_format(sensor, VIDEO_MODE_1080P_15);
#else
    set_format(sensor, VIDEO_MODE_1080P_25);
#endif
*/
    SCCB_Write_Reg16(sensor->slv_addr, 0x3641, 0x1);        /* IO driver control */
    SCCB_Write_Reg16(sensor->slv_addr, 0x3d08, 0x1);        /* invert the sensor pix clk polarity */
    SCCB_Write_Reg16(sensor->slv_addr, 0x3640, 0x0);        /* pixel delay */

#if 0   // enable test pattern
    SCCB_Write_Reg16(sensor->slv_addr, 0x4501, 0xc8);     /* test pattern enable */
    SCCB_Write_Reg16(sensor->slv_addr, 0x3902, 0x05);     /* manual BLC  */
#endif

    return 0;
}

const BL_SENSOR_DESC_T sensor_desc_sc2232 ATTR_SENSOR_DEVICE_TABLE =
{
	"SC2232",
    SLAVE_ADDR,
    probe,
    init,
    setFmt,
};

