#include <bl808.h>

#include "sensor.h"
#include "sensor_internal.h"
#include "sccb.h"
#include "c2490.h"

#if 0
/* C2490 sensor info */
#define SLAVE_ADDR                  0x36
#define SENSOR_ID                   0x0208
#define MIN_EXPO_TIME               32848                       /* 32848 ns or -49.5 dB */
#define MAX_EXPO_TIME               EXPO_TIME_1_25_SEC          /* 1/25 sec */
#define REG_ADDR_BIT                SENSOR_REG_ADDR_16BIT

//#define MAX_GAIN                    GAIN_DB_FLOAT_TO_INT(53.25)    /* 53.25 dB */
#define MAX_GAIN                    GAIN_DB_FLOAT_TO_INT(36)    /* limit max gain t0 36 dB to avoid bad noise */
#define MAX_AGAIN                   GAIN_DB_FLOAT_TO_INT(23.625)   /* 23.625 dB or 15.5x */
#define MIN_GAIN_STEP               (GAIN_6_DB / 16)            /* 0.375 dB */


/* C2490 registers */
#define REG_GROUP_HOLD              0x3812
#define REG_SENSOR_ID_H             0x0000
#define REG_SENSOR_ID_L             0x0001
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
    FORMAT_INDEX_1080P_9,
    FORMAT_INDEX_1080P_9_2,
    FORMAT_INDEX_INVALID,
} FORMAT_INDEX;

static const int c2490_mode[] = {\
    DSP2_INPUT_DVP\
};
/* TODO: make total height even to workaround bayer reverse issue in bottom 3 lines */
static const sensor_format_t format_info[] = {
    {   /* for 1080p30 */
        .total_width	= 2412,
        .total_height	= 1104,
        .pix_clk        = 80000000,
    },
};

static const sensor_reg_16_8_t init_reglist_30fps[] =
{
    {   0x0103,0x01         },

    {   0x3293, 0x00            },
    {   0x3280, 0x86            },
    {   0x32aa, 0x08         },
    {   0x32ab, 0x08            },
    {   0x3286, 0x00            },
    {   0x3287, 0x40            },
    {   0x3290, 0xe5            },
    {   0x3211, 0x14            },
    {   0x3212, 0x80            },
    {   0x3215, 0x20            },
    {   0x3216, 0x34            },
    {   0x3217, 0x30            },
    {   0x3218, 0x50            },
    {   0x3223, 0x20            },
    {   0x3288,0x50            },
    {   0x0401,0x3b         },
    {   0x0403,0x00         },

    {   0x3182,0x30         },
    {   0x3183,0x00           },
    {   0x3180,0x20         },
    {   0x3026,0x01         },

    {   0x3c01,0x17         },
    {   0x3112,0xe8         },
    {   0x32c8,0x22         },
    {   0x32ca,0x22          },
    {   0x3d14,0x22         },
    {   0x3885,0x22         },
    {   0x3640,0x22         },

    {   0x0202,0x04         },
    {   0x0203,0x48         },
    {   0x3293,0x00         },

    {   0x3f10,0x00         },
    {   0x0101,0x00         },

    {   0x0307,0x64         },

    {   0x3905,0x00         },
    {   0x3584,0x2a         },
    {   0x3986,0x01         },
    {   0x3810,0x00         },
    {   0x3295,0x55         },
    {   0x3981,0x23         },
    {   0x3987,0x02         },
    {   0x3988,0xff         },
    {   0x3882,0x01         },

    //{   0x3c00,0x07         },      // test pattern
    {   0x3c00,0x03         },      // test pattern

    {   0x0100,0x01         },

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
    return 0;
}

static int set_gain(sensor_t *sensor, BL_GAIN_DB gain)
{
    return 0;
}

static int set_flipmirror(sensor_t *sensor, FLIP_MIRROR_TYPE_E type)
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

	default:
		BL_LOGE("set_format error: invalid video mode!\r\n");
		return -1;
	}

    sensor->pix_clk         = format_info[format_index].pix_clk;
    sensor->total_win.width     = format_info[format_index].total_width;
    sensor->total_win.height    = format_info[format_index].total_height;
    sensor->out_win.width = 1920;
    sensor->out_win.height = 1080;

    for (i = 0; init_reglist[i].addr != REGLIST_END; i++) {
        SCCB_Write_Reg16(sensor->slv_addr, init_reglist[i].addr, (uint8_t)init_reglist[i].data);
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
    return sensor_probe(SLAVE_ADDR, REG_SENSOR_ID_H, REG_SENSOR_ID_L, SENSOR_ID_H, SENSOR_ID_L);
}

static int init(sensor_t *sensor)
{
    int mode_num = sizeof(c2490_mode)/sizeof(c2490_mode[0]);
    if (!is_sensor_dsp2_input_match(c2490_mode, mode_num)) {
        return -1;
    }

    /* Initialize sensor structure */
    SENSOR_INIT_COMMON(C2490);

    //set_format(sensor, VIDEO_MODE_1080P_30);

    printf("c2490_init done\r\n");

    return 0;
}

const BL_SENSOR_DESC_T sensor_desc_c2496 ATTR_SENSOR_DEVICE_TABLE =
{
    "C2490",
    SLAVE_ADDR,
    probe,
    init,
    setFmt,
};

#endif