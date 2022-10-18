#include <bl808.h>
#include "sensor_internal.h"
#include "sccb.h"
#include "sc1245.h"

/* SC1245 sensor info */
#define SENSOR_NAME                 "SC1245"
#define SLAVE_ADDR                  0x30
#define SENSOR_ID_H                 0x12
#define SENSOR_ID_L                 0x45
#define MIN_EXPO_TIME               32848                           /* 32848 ns or -49.5 dB */
#define MAX_EXPO_TIME               EXPO_TIME_1_25_SEC              /* 1/25 sec */
#define REG_ADDR_BIT                SENSOR_REG_ADDR_16BIT

//#define MAX_GAIN                    GAIN_DB_FLOAT_TO_INT(47.625)    /* 47.625 dB */
#define MAX_GAIN                    GAIN_DB_FLOAT_TO_INT(30)        /* limit max gain t0 30 dB to avoid bad noise */
#define MIN_GAIN_STEP               (GAIN_6_DB / 16)                /* 0.375 dB */

/* SC1245 registers */
#define REG_SENSOR_ID_H             0x3107
#define REG_SENSOR_ID_L             0x3108
#define REG_GROUP_HOLD              0x3812
#define REG_GAIN_H                  0x3e07
#define REG_GAIN_M                  0x3e08
#define REG_GAIN_L                  0x3e09
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

#define COL_IDX_FINE_GAIN           0
#define COL_IDX_COARSE_GAIN         1
#define COL_IDX_DGAIN               2


#define NEW_BRIDGE_BOARD            1

typedef enum {
    FORMAT_INDEX_720P_5 = 0,
    FORMAT_INDEX_720P_10 = 1,
    FORMAT_INDEX_720P_20 = 2,
    FORMAT_INDEX_720P_25 = 3,
    FORMAT_INDEX_720P_30,
    FORMAT_INDEX_720P_50,
    FORMAT_INDEX_720P_59_94,
    FORMAT_INDEX_INVALID,
} FORMAT_INDEX;

/* TODO: make total height even to workaround bayer reverse issue in bottom 3 lines */
static const sensor_format_t format_info[] = {
    {   /* for 720p5 */
        .total_width	= 1600,
        .total_height	= 4500,
        .pix_clk        = 36000000,
        .fps            = 5,
    },
    {   /* for 720p10 */
        .total_width	= 1600,
        .total_height	= 2250,
        .pix_clk        = 36000000,
        .fps            = 10,
    },
    {   /* for 720p20 */
        .total_width	= 1600,
        .total_height	= 1125,
        .pix_clk        = 36000000,
        .fps            = 20,
    },
    {   /* for 720p25 */
        .total_width	= 1600,
        .total_height	= 900,
        .pix_clk        = 36000000,
        .fps            = 25,
    },
    {   /* for 720p30 */
        .total_width	= 1600,
        .total_height	= 750,
        .pix_clk        = 36000000,
        .fps            = 30,
    },
    {   /* for 720p50 */
        .total_width	= 1920,
        .total_height	= 750,
        .pix_clk        = 72000000,
        .fps            = 50,
    },
    {   /* for 720p59.94 */
        .total_width	= 1540,
        .total_height	= 780,
        .pix_clk        = 72000000,
        .fps            = 60,
    },
};

static const int sc1245_mode[] = {\
    DSP2_INPUT_DVP,
};

static const sensor_reg_16_8_t init_reglist_50fps[] =
{
    {0x0103, 0x01},
    {0x0100, 0x00},
    {0x4500, 0x51},
    {0x320e, 0x03}, //25fps
    {0x320f, 0x84},
    {0x3e01, 0x38},
    {0x3635, 0xa0},
    {0x3620, 0x28},
    {0x3309, 0xa0},
    {0x331f, 0x9d},
    {0x3321, 0x9f},
    {0x3306, 0x65},
    {0x330b, 0x66},
    {0x3e08, 0x03},
    {0x3e07, 0x00},
    {0x3e09, 0x10},
    {0x3367, 0x18}, //pchtx min
    {0x335e, 0x01},  //ana dithering
    {0x335f, 0x03},
    {0x337c, 0x04},
    {0x337d, 0x06},
    {0x33a0, 0x05},
    {0x3301, 0x05},
    {0x3302, 0x7d},
    {0x3633, 0x43},
    {0x3908, 0x11},
    {0x3621, 0x28},
    {0x3622, 0x02},
    //0714
    {0x3637, 0x1c},
    {0x3308, 0x1c},
    {0x3367, 0x10},
    {0x337f, 0x03},
    {0x3368, 0x04},//auto precharge
    {0x3369, 0x00},
    {0x336a, 0x00},
    {0x336b, 0x00},
    {0x3367, 0x08},
    {0x330e, 0x30},
    {0x3366, 0x7c}, // div_rst gap
    //0805
    {0x3635, 0xc4}, //fpn
    {0x3621, 0x20}, //col_fpn
    {0x3334, 0x40},
    {0x3333, 0x10},
    {0x3302, 0x3d},
    //0807
    {0x335e, 0x01},  //ana dithering
    {0x335f, 0x02},
    {0x337c, 0x03},
    {0x337d, 0x05},
    {0x33a0, 0x04},
    {0x3301, 0x03},
    {0x3633, 0x48},
    {0x3670, 0x0a} , //[1]:3630 logic ctrl  real value in 3681
    {0x367c, 0x07},  //gain0
    {0x367d, 0x0f},  //gain1
    {0x3674, 0x20},  //<gain0
    {0x3675, 0x2f},  //gain0 - gain1
    {0x3676, 0x2f},  //>gain1
    {0x3631, 0x84},
    {0x3622, 0x06},
    {0x3630, 0x20},
    {0x3620, 0x08}, //col_fpn
    {0x330b, 0x66},
    {0x3638, 0x1f}, //ramp by clk
    {0x3625, 0x02},
    {0x3637, 0x1e},
    {0x3636, 0x25},
    {0x3306, 0x1c},  //5.0k
    {0x3637, 0x1a},
    {0x331e, 0x0c},
    {0x331f, 0x9c},
    {0x3320, 0x0c},
    {0x3321, 0x9c},
    {0x366e, 0x08},  // ofs auto en [3]
    {0x366f, 0x2a},  // ofs+finegain  real ofs in 0x3687[4:0]
    {0x3622, 0x16}, //sig clamp
    {0x363b, 0x0c}, //hvdd
    {0x3639, 0x0a},
    {0x3632, 0x28},
    {0x3038, 0x84},
    //0814
    {0x3635, 0xc0},
    {0x3f00, 0x07},  // bit[2] = 1
    {0x3f04, 0x02},
    {0x3f05, 0xfc},  // hts / 2 - 0x24
    {0x3802, 0x01},
    {0x3235, 0x07},
    {0x3236, 0x06}, // vts x 2 - 2
    //0831
    {0x3639, 0x09},
    {0x3670, 0x02},
    //0904
    {0x3635, 0x80},
    //0906
    {0x320e, 0x02},
    {0x320f, 0xee},
    {0x3235, 0x05},
    {0x3236, 0xda},
    {0x3039, 0x51},
    {0x303a, 0xba},
    {0x3034, 0x06},
    {0x3035, 0xe2},
    {0x3208, 0x05},
    {0x3209, 0x08},
    {0x320a, 0x02},
    {0x320b, 0xd8},
    {0x3211, 0x04},
    {0x3213, 0x04},
    {0x3302, 0x7d},//20171027  add 3301 margin
    //1103
    {0x3357, 0x51},
    //1106
    {0x3326, 0x00},
    {0x3303, 0x20},
    {0x3320, 0x07},
    {0x331e, 0x11},
    {0x331f, 0x91},
    {0x366f, 0x2c},
    {0x3333, 0x30},
    {0x331b, 0x83},
    {0x330b, 0x5e},
    {0x3620, 0x28},
    {0x3631, 0x86},
    {0x3633, 0x42},
    {0x3301, 0x04},
    {0x3622, 0xd6},
    //20171108
    {0x3635, 0x84},
    {0x3e01, 0x5d},//20171112
    {0x3e02, 0x80},
    //20171114    50fps
    {0x3208, 0x05},//1280
    {0x3209, 0x00},
    {0x320a, 0x02},//720
    {0x320b, 0xd0},
    {0x3210, 0x00},
    {0x3211, 0x04},
    {0x3212, 0x00},
    {0x3213, 0x08},
    {0x320c, 0x07},//1920
    {0x320d, 0x80},
    {0x320e, 0x02},//750
    {0x3f04, 0x03},
    {0x3f05, 0x9c},  // hts / 2 - 0x24
    {0x3235, 0x05},
    {0x3236, 0xda}, // vts x 2 - 2
    {0x3302, 0x3d},
    {0x3640, 0x01},
    {0x3306, 0x38},
    {0x330b, 0xcc},
    {0x3039, 0x21},
    {0x303a, 0xba},
    {0x3034, 0x06},
    {0x3035, 0xe2},
    {0x3802, 0x01},//20171115
    //init intt & gain
    {0x3e00, 0x00},
    {0x3e01, 0x5d},
    {0x3e02, 0x80},
    {0x3e03, 0x0b},
    {0x3e08, 0x03},
    {0x3e09, 0x10},

#ifdef NEW_BRIDGE_BOARD
    /* 0x02 == Read_Sensor_Register(0x3020) */
	{0x3303,0x20,},
	{0x3309,0xa0,},
	{0x330b,0xcc},
	{0x3635,0x84,},
	{0x3633,0x42,},
	{0x3301,0x05,},
	{0x3622,0xd6,},
#else
    /* 0x03 == Read_Sensor_Register(0x3020) */
	{0x3303,0x18,},
	{0x3309,0x98,},
	{0x330b,0xd0,},
	{0x3635,0x80,},
	{0x3633,0x46,},
	{0x3301,0x06,},
	{0x3622,0xd6,},
	{0x330e,0x58,},
#endif
    /* end of reg list */
    {REGLIST_END, 0x00},
};

#ifdef TEST_DIRTY_EDGE_FOR_SC1245 // output 1288x728
static const sensor_reg_16_8_t init_reglist_30fps[] =
{
    {   0x0103,0x01,    },
    {   0x0100,0x00,    },
    {   0x3034,0x06,    },
    {   0x3035,0xe2,    },
    {   0x3038,0x84,    },
    {   0x3039,0x51,    },
    {   0x303a,0xba,    },
    {   0x3208,0x05,    },
    {   0x3209,0x08,    },
    {   0x320a,0x02,    },
    {   0x320b,0xd8,    },
    {   0x320e,0x02,    },
    {   0x320f,0xee,    },
    {   0x3211,0x04,    },
    {   0x3213,0x04,    },
    {   0x3235,0x05,    },
    {   0x3236,0xda,    },
    {   0x3301,0x04,    },
    {   0x3302,0x7d,    },
    {   0x3303,0x20,    },
    {   0x3306,0x1c,    },
    {   0x3308,0x1c,    },
    {   0x3309,0xa0,    },
    {   0x330b,0x5e,    },
    {   0x330e,0x30,    },
    {   0x331b,0x83,    },
    {   0x331e,0x11,    },
    {   0x331f,0x91,    },
    {   0x3320,0x07,    },
    {   0x3321,0x9c,    },
    {   0x3326,0x00,    },
    {   0x3333,0x30,    },
    {   0x3334,0x40,    },
    {   0x3357,0x51,    },
    {   0x335e,0x01,    },
    {   0x335f,0x02,    },
    {   0x3366,0x7c,    },
    {   0x3367,0x08,    },
    {   0x3368,0x04,    },
    {   0x3369,0x00,    },
    {   0x336a,0x00,    },
    {   0x336b,0x00,    },
    {   0x337c,0x03,    },
    {   0x337d,0x05,    },
    {   0x337f,0x03,    },
    {   0x33a0,0x04,    },
    {   0x3620,0x28,    },
    {   0x3621,0x20,    },
    {   0x3622,0xd6,    },
    {   0x3625,0x02,    },
    {   0x3630,0x20,    },
    {   0x3631,0x86,    },
    {   0x3632,0x28,    },
    {   0x3633,0x42,    },
    {   0x3635,0x84,    },
    {   0x3636,0x25,    },
    {   0x3637,0x1a,    },
    {   0x3638,0x1f,    },
    {   0x3639,0x09,    },
    {   0x363b,0x0c,    },
    {   0x366e,0x08,    },
    {   0x366f,0x2c,    },
    {   0x3670,0x02,    },
    {   0x3674,0x20,    },
    {   0x3675,0x2f,    },
    {   0x3676,0x2f,    },
    {   0x367c,0x07,    },
    {   0x367d,0x0f,    },
    {   0x3802,0x01,    },
    {   0x3908,0x11,    },
    {   0x3e00,0x00,    },
    {   0x3e01,0x5d,    },
    {   0x3e02,0x80,    },
    {   0x3e03,0x0b,    },
    {   0x3e07,0x00,    },
    {   0x3e08,0x03,    },
    {   0x3e09,0x10,    },
    {   0x3f00,0x07,    },
    {   0x3f04,0x02,    },
    {   0x3f05,0xfc,    },
    {   0x4500,0x51,    },
#ifdef NEW_BRIDGE_BOARD
    /* 0x02 == Read_Sensor_Register(0x3020) */
    {   0x3303,0x20,    },
    {   0x3309,0xa0,    },
    {   0x3635,0x84,    },
    {   0x3633,0x42,    },
    {   0x3301,0x04,    },
    {   0x3622,0xd6,    },
#else
    /* 0x03 == Read_Sensor_Register(0x3020) */
    {   0x3303,0x18,    },
    {   0x3309,0x98,    },
    {   0x3635,0x80,    },
    {   0x3633,0x46,    },
    {   0x3301,0x03,    },
    {   0x3622,0xd6,    },
    {   0x330e,0x58,    },
#endif

    /* end of reg list */
    {REGLIST_END, 0x00},
};
#else
static const sensor_reg_16_8_t init_reglist_30fps[] =
{
    {   0x0103,0x01,    },
    {   0x0100,0x00,    },
    {   0x3034,0x06,    },
    {   0x3035,0xe2,    },
    {   0x3038,0x84,    },
    {   0x3039,0x51,    },
    {   0x303a,0xba,    },
    {   0x3208,0x05,    },
    {   0x3209,0x00,    },
    {   0x320a,0x02,    },
    {   0x320b,0xd0,    },
    {   0x320e,0x03,    },
    {   0x320f,0x84,    },
    {   0x3211,0x08,    },
    {   0x3213,0x08,    },
    {   0x3235,0x05,    },
    {   0x3236,0xda,    },
    {   0x3301,0x04,    },
    {   0x3302,0x7d,    },
    {   0x3303,0x20,    },
    {   0x3306,0x1c,    },
    {   0x3308,0x1c,    },
    {   0x3309,0xa0,    },
    {   0x330b,0x5e,    },
    {   0x330e,0x58,    },
    {   0x331b,0x83,    },
    {   0x331e,0x11,    },
    {   0x331f,0x91,    },
    {   0x3320,0x07,    },
    {   0x3321,0x9c,    },
    {   0x3326,0x00,    },
    {   0x3333,0x30,    },
    {   0x3334,0x40,    },
    {   0x3357,0x51,    },
    {   0x335e,0x01,    },
    {   0x335f,0x02,    },
    {   0x3366,0x7c,    },
    {   0x3367,0x08,    },
    {   0x3368,0x04,    },
    {   0x3369,0x00,    },
    {   0x336a,0x00,    },
    {   0x336b,0x00,    },
    {   0x337c,0x03,    },
    {   0x337d,0x05,    },
    {   0x337f,0x03,    },
    {   0x33a0,0x04,    },
    {   0x3620,0x28,    },
    {   0x3621,0x20,    },
    {   0x3622,0xd6,    },
    {   0x3625,0x02,    },
    {   0x3630,0x20,    },
    {   0x3631,0x86,    },
    {   0x3632,0x28,    },
    {   0x3633,0x42,    },
    {   0x3635,0x84,    },
    {   0x3636,0x25,    },
    {   0x3637,0x1a,    },
    {   0x3638,0x1f,    },
    {   0x3639,0x09,    },
    {   0x363b,0x0c,    },
    {   0x366e,0x08,    },
    {   0x366f,0x2c,    },
    {   0x3670,0x02,    },
    {   0x3674,0x20,    },
    {   0x3675,0x2f,    },
    {   0x3676,0x2f,    },
    {   0x367c,0x07,    },
    {   0x367d,0x0f,    },
    {   0x3802,0x01,    },
    {   0x3908,0x11,    },
    {   0x3e00,0x00,    },
    {   0x3e01,0x5d,    },
    {   0x3e02,0x80,    },
    {   0x3e03,0x0b,    },
    {   0x3e07,0x00,    },
    {   0x3e08,0x03,    },
    {   0x3e09,0x10,    },
    {   0x3f00,0x07,    },
    {   0x3f04,0x02,    },
    {   0x3f05,0xfc,    },
    {   0x4500,0x51,    },
    {   0x330e,0x58,    },
#ifdef NEW_BRIDGE_BOARD
    /* 0x02 == Read_Sensor_Register(0x3020) */
    {   0x3303,0x20,    },
    {   0x3309,0xa0,    },
    {   0x3635,0x84,    },
    {   0x3633,0x42,    },
    {   0x3301,0x04,    },
    {   0x3622,0xd6,    },
#else
    /* 0x03 == Read_Sensor_Register(0x3020) */
	{   0x3303,0x18,    },
	{   0x3309,0x98,    },
	{   0x3635,0x80,    },
	{   0x3633,0x46,    },
	{   0x3301,0x03,    },
	{   0x3622,0xd6,    },
	{   0x330e,0x58,    },
#endif
    /* end of reg list */
    {REGLIST_END, 0x00},
};
#endif

static const uint8_t gain_table[128][3] = {
    {	0x10	,	0x03	,	0x0	},
    {	0x11	,	0x03	,	0x0	},
    {	0x12	,	0x03	,	0x0	},
    {	0x13	,	0x03	,	0x0	},
    {	0x14	,	0x03	,	0x0	},
    {	0x15	,	0x03	,	0x0	},
    {	0x16	,	0x03	,	0x0	},
    {	0x17	,	0x03	,	0x0	},
    {	0x18	,	0x03	,	0x0	},
    {	0x19	,	0x03	,	0x0	},
    {	0x1a	,	0x03	,	0x0	},
    {	0x1b	,	0x03	,	0x0	},
    {	0x1c	,	0x03	,	0x0	},
    {	0x1d	,	0x03	,	0x0	},
    {	0x1e	,	0x03	,	0x0	},
    {	0x1f	,	0x03	,	0x0	},
    {	0x10	,	0x07	,	0x0	},
    {	0x11	,	0x07	,	0x0	},
    {	0x12	,	0x07	,	0x0	},
    {	0x13	,	0x07	,	0x0	},
    {	0x14	,	0x07	,	0x0	},
    {	0x15	,	0x07	,	0x0	},
    {	0x16	,	0x07	,	0x0	},
    {	0x17	,	0x07	,	0x0	},
    {	0x18	,	0x07	,	0x0	},
    {	0x19	,	0x07	,	0x0	},
    {	0x1a	,	0x07	,	0x0	},
    {	0x1b	,	0x07	,	0x0	},
    {	0x1c	,	0x07	,	0x0	},
    {	0x1d	,	0x07	,	0x0	},
    {	0x1e	,	0x07	,	0x0	},
    {	0x1f	,	0x07	,	0x0	},
    {	0x10	,	0x0f	,	0x0	},
    {	0x11	,	0x0f	,	0x0	},
    {	0x12	,	0x0f	,	0x0	},
    {	0x13	,	0x0f	,	0x0	},
    {	0x14	,	0x0f	,	0x0	},
    {	0x15	,	0x0f	,	0x0	},
    {	0x16	,	0x0f	,	0x0	},
    {	0x17	,	0x0f	,	0x0	},
    {	0x18	,	0x0f	,	0x0	},
    {	0x19	,	0x0f	,	0x0	},
    {	0x1a	,	0x0f	,	0x0	},
    {	0x1b	,	0x0f	,	0x0	},
    {	0x1c	,	0x0f	,	0x0	},
    {	0x1d	,	0x0f	,	0x0	},
    {	0x1e	,	0x0f	,	0x0	},
    {	0x1f	,	0x0f	,	0x0	},
    {	0x10	,	0x1f	,	0x0	},
    {	0x11	,	0x1f	,	0x0	},
    {	0x12	,	0x1f	,	0x0	},
    {	0x13	,	0x1f	,	0x0	},
    {	0x14	,	0x1f	,	0x0	},
    {	0x15	,	0x1f	,	0x0	},
    {	0x16	,	0x1f	,	0x0	},
    {	0x17	,	0x1f	,	0x0	},
    {	0x18	,	0x1f	,	0x0	},
    {	0x19	,	0x1f	,	0x0	},
    {	0x1a	,	0x1f	,	0x0	},
    {	0x1b	,	0x1f	,	0x0	},
    {	0x1c	,	0x1f	,	0x0	},
    {	0x1d	,	0x1f	,	0x0	},
    {	0x1e	,	0x1f	,	0x0	},
    {	0x1f	,	0x1f	,	0x0	},
    {	0x10	,	0x3f	,	0x0	},
    {	0x11	,	0x3f	,	0x0	},
    {	0x12	,	0x3f	,	0x0	},
    {	0x13	,	0x3f	,	0x0	},
    {	0x14	,	0x3f	,	0x0	},
    {	0x15	,	0x3f	,	0x0	},
    {	0x16	,	0x3f	,	0x0	},
    {	0x17	,	0x3f	,	0x0	},
    {	0x18	,	0x3f	,	0x0	},
    {	0x19	,	0x3f	,	0x0	},
    {	0x1a	,	0x3f	,	0x0	},
    {	0x1b	,	0x3f	,	0x0	},
    {	0x1c	,	0x3f	,	0x0	},
    {	0x1d	,	0x3f	,	0x0	},
    {	0x1e	,	0x3f	,	0x0	},
    {	0x1f	,	0x3f	,	0x0	},
    {	0x10	,	0x7f	,	0x0	},
    {	0x11	,	0x7f	,	0x0	},
    {	0x12	,	0x7f	,	0x0	},
    {	0x13	,	0x7f	,	0x0	},
    {	0x14	,	0x7f	,	0x0	},
    {	0x15	,	0x7f	,	0x0	},
    {	0x16	,	0x7f	,	0x0	},
    {	0x17	,	0x7f	,	0x0	},
    {	0x18	,	0x7f	,	0x0	},
    {	0x19	,	0x7f	,	0x0	},
    {	0x1a	,	0x7f	,	0x0	},
    {	0x1b	,	0x7f	,	0x0	},
    {	0x1c	,	0x7f	,	0x0	},
    {	0x1d	,	0x7f	,	0x0	},
    {	0x1e	,	0x7f	,	0x0	},
    {	0x1f	,	0x7f	,	0x0	},
    {	0x10	,	0xff	,	0x0	},
    {	0x11	,	0xff	,	0x0	},
    {	0x12	,	0xff	,	0x0	},
    {	0x13	,	0xff	,	0x0	},
    {	0x14	,	0xff	,	0x0	},
    {	0x15	,	0xff	,	0x0	},
    {	0x16	,	0xff	,	0x0	},
    {	0x17	,	0xff	,	0x0	},
    {	0x18	,	0xff	,	0x0	},
    {	0x19	,	0xff	,	0x0	},
    {	0x1a	,	0xff	,	0x0	},
    {	0x1b	,	0xff	,	0x0	},
    {	0x1c	,	0xff	,	0x0	},
    {	0x1d	,	0xff	,	0x0	},
    {	0x1e	,	0xff	,	0x0	},
    {	0x1f	,	0xff	,	0x0	},
    {	0x10	,	0xff	,	0x1	},
    {	0x11	,	0xff	,	0x1	},
    {	0x12	,	0xff	,	0x1	},
    {	0x13	,	0xff	,	0x1	},
    {	0x14	,	0xff	,	0x1	},
    {	0x15	,	0xff	,	0x1	},
    {	0x16	,	0xff	,	0x1	},
    {	0x17	,	0xff	,	0x1	},
    {	0x18	,	0xff	,	0x1	},
    {	0x19	,	0xff	,	0x1	},
    {	0x1a	,	0xff	,	0x1	},
    {	0x1b	,	0xff	,	0x1	},
    {	0x1c	,	0xff	,	0x1	},
    {	0x1d	,	0xff	,	0x1	},
    {	0x1e	,	0xff	,	0x1	},
    {	0x1f	,	0xff	,	0x1	},
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

    if (num_half_line > sensor->total_win.height *2 - 4)
        num_half_line = sensor->total_win.height *2 - 4;

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

    return 0;
}

#if 1
static int set_gain(sensor_t *sensor, BL_GAIN_DB gain)
{
    int index;

    /* 6 dB range corresponds to 16 index range */
    index = find_closest_gain_index(gain, 16);

    uint8_t fine_gain = 0, coarse_gain = 0, dgain = 0;
    uint8_t reg1, reg2, reg3, reg4;

    fine_gain = gain_table[index][COL_IDX_FINE_GAIN];
    coarse_gain = gain_table[index][COL_IDX_COARSE_GAIN];
    dgain = gain_table[index][COL_IDX_DGAIN];

    BL_LOGD("\t\t fine_gain 0x%02x, coarse_gain 0x%02x, dgain 0x%02x\r\n", fine_gain, coarse_gain, dgain);

    /* do the gain switch sequence */
#ifdef NEW_BRIDGE_BOARD    // [0x3020] == 0x3
    if (coarse_gain == 0x03) {           /* gain < 2 */
        reg1 = 0x42;
        reg2 = 0x04;
        reg3 = 0xd6;
        reg4 = 0x89;
    } else if (coarse_gain == 0x07) {    /* 2 <= gain < 4 */
        reg1 = 0x42;
        reg2 = 0x05;
        reg3 = 0xd6;
        reg4 = 0x86;
    } else if (coarse_gain == 0x0F) {    /* 4 <= gain < 8 */
        reg1 = 0x42;
        reg2 = 0x05;
        reg3 = 0xd6;
        reg4 = 0x84;
    } else if (coarse_gain == 0x1F && fine_gain < 0x1F) {   /* 8 <= gain < 15.5 */
        reg1 = 0x42;
        reg2 = 0x07;
        reg3 = 0x16;
        reg4 = 0x82;
    } else {                        /* gain >= 15.5 */
        reg1 = 0x42;
        reg2 = 0x11;
        reg3 = 0x16;
        reg4 = 0x80;
    }
#else
    if (coarse_gain == 0x03) {           /* gain < 2 */
        reg1 = 0x46;
        reg2 = 0x03;
        reg3 = 0xd6;
        reg4 = 0x89;
    } else if (coarse_gain == 0x07) {    /* 2 <= gain < 4 */
        reg1 = 0x42;
        reg2 = 0x0a;
        reg3 = 0xd6;
        reg4 = 0x86;
    } else if (coarse_gain == 0x0F) {    /* 4 <= gain < 8 */
        reg1 = 0x42;
        reg2 = 0x0b;
        reg3 = 0x16;
        reg4 = 0x84;
    } else if (coarse_gain == 0x1F && fine_gain < 0x1F) {   /* 8 <= gain < 15.5 */
        reg1 = 0x42;
        reg2 = 0x0c;
        reg3 = 0x16;
        reg4 = 0x82;
    } else {                        /* gain >= 15.5 */
#if 0   /* according to user guide */
        reg1 = 0x42;
        reg2 = 0x32;
        reg3 = 0x16;
        reg4 = 0x80;
#else   /* sometimes brightness spikes when gain changed to 15.5 dB */
        reg1 = 0x42;
        reg2 = 0x0c;
        reg3 = 0x16;
        reg4 = 0x82;
#endif
    }
#endif

    SCCB_Write_Reg16(sensor->slv_addr, REG_GAIN_H, dgain);
    SCCB_Write_Reg16(sensor->slv_addr, REG_GAIN_M, coarse_gain);
    SCCB_Write_Reg16(sensor->slv_addr, REG_GAIN_L, fine_gain);

    SCCB_Write_Reg16(sensor->slv_addr, 0x3903, 0x84);    /* according to sc1245 app note */
    SCCB_Write_Reg16(sensor->slv_addr, 0x3903, 0x04);    /* according to sc1245 app note */
    SCCB_Write_Reg16(sensor->slv_addr, REG_GROUP_HOLD, 0x0);

    SCCB_Write_Reg16(sensor->slv_addr, 0x3633, reg1);
    SCCB_Write_Reg16(sensor->slv_addr, 0x3301, reg2);
    SCCB_Write_Reg16(sensor->slv_addr, 0x3622, reg3);
    SCCB_Write_Reg16(sensor->slv_addr, 0x3635, reg4);

    SCCB_Write_Reg16(sensor->slv_addr, REG_GROUP_HOLD, 0x30);

    return 0;
}

#else
static int set_gain(sensor_t *sensor, BL_GAIN_DB gain)
{
    uint8_t dgain = 0, coarse_gain = 0, fine_gain = 0;
    uint8_t reg1, reg2, reg3, reg4;
    int tmp, num_of_6db;

    /* calculate the value for dgain (0x3e07) */
    if (gain >= INT_TO_GAIN_DB(42))
        dgain = 0x1;

    /* calculate the value for coarse_gain (0x3e08) */
    /* first calculate the number of ones for coarse_gain */
    num_of_6db = GAIN_DB_TO_INT((gain / 6));
    tmp = num_of_6db + 2;

    if (tmp > 8)
        tmp = 8;

    /* calculate coarse_gain */
    coarse_gain = (1 << tmp) - 1;

    /* calculate the value for fine_gain (0x3e09) */
    tmp = gain - INT_TO_GAIN_DB(num_of_6db * 6);     /* nomalize to 0~6 dB range */
    tmp = DIV_ROUND(tmp, sensor->min_gain_step);     /* calculate the number of step for fine gain */
    fine_gain = 0x10 + tmp;

    BL_LOGD("\t\t dgain 0x%lx, coarse_gain 0x%lx, fine_gain 0x%lx\r\n", dgain, coarse_gain, fine_gain);

    /* do the gain switch sequence */
    if (coarse_gain == 0x03) {           /* gain < 2 */
        reg1 = 0x46;
        reg2 = 0x03;
        reg3 = 0xd6;
        reg4 = 0x89;
    } else if (coarse_gain == 0x07) {    /* 2 <= gain < 4 */
        reg1 = 0x42;
        reg2 = 0x0a;
        reg3 = 0xd6;
        reg4 = 0x86;
    } else if (coarse_gain == 0x0F) {    /* 4 <= gain < 8 */
        reg1 = 0x42;
        reg2 = 0x0a;
        reg3 = 0xd6;
        reg4 = 0x84;
    } else if (coarse_gain == 0x1F && fine_gain < 0x1F) {   /* 8 <= gain < 15.5 */
        reg1 = 0x42;
        reg2 = 0x0c;
        reg3 = 0x16;
        reg4 = 0x82;
    } else {                        /* gain >= 15.5 */
#if 1   /* according to user guide */
        reg1 = 0x42;
        reg2 = 0x32;
        reg3 = 0x16;
        reg4 = 0x80;
#else   /* sometimes brightness spikes when gain changed to 15.5 dB */
        reg1 = 0x42;
        reg2 = 0x0c;
        reg3 = 0x16;
        reg4 = 0x82;
#endif
    }

    SCCB_Write_Reg16(sensor->slv_addr, REG_GAIN_H, dgain);
    SCCB_Write_Reg16(sensor->slv_addr, REG_GAIN_M, coarse_gain);
    SCCB_Write_Reg16(sensor->slv_addr, REG_GAIN_L, fine_gain);

    SCCB_Write_Reg16(sensor->slv_addr, 0x3903, 0x84);    /* according to sc1245 app note */
    SCCB_Write_Reg16(sensor->slv_addr, 0x3903, 0x04);    /* according to sc1245 app note */
    SCCB_Write_Reg16(sensor->slv_addr, REG_GROUP_HOLD, 0x0);

    SCCB_Write_Reg16(sensor->slv_addr, 0x3633, reg1);
    SCCB_Write_Reg16(sensor->slv_addr, 0x3301, reg2);
    SCCB_Write_Reg16(sensor->slv_addr, 0x3622, reg3);
    SCCB_Write_Reg16(sensor->slv_addr, 0x3635, reg4);

    SCCB_Write_Reg16(sensor->slv_addr, REG_GROUP_HOLD, 0x30);

    return 0;
}
#endif

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
    int i, ret;
    FORMAT_INDEX format_index = 0;
    const sensor_reg_16_8_t *init_reglist = {0};

    switch (sensor->video_mode) {
	case VIDEO_MODE_720P_5:
        format_index = FORMAT_INDEX_720P_5;
        init_reglist = init_reglist_30fps;
        sensor->max_expo_time = EXPO_TIME_1_25_SEC;       /* 1/25 sec */
		break;

	case VIDEO_MODE_720P_10:
        format_index = FORMAT_INDEX_720P_10;
        init_reglist = init_reglist_30fps;
        sensor->max_expo_time = EXPO_TIME_1_25_SEC;       /* 1/25 sec */
		break;

	case VIDEO_MODE_720P_20:
        format_index = FORMAT_INDEX_720P_20;
        init_reglist = init_reglist_30fps;
        sensor->max_expo_time = EXPO_TIME_1_25_SEC;       /* 1/25 sec */
		break;

	case VIDEO_MODE_720P_25:
        format_index = FORMAT_INDEX_720P_25;
        init_reglist = init_reglist_30fps;
        sensor->max_expo_time = EXPO_TIME_1_25_SEC;       /* 1/25 sec */
		break;

	case VIDEO_MODE_720P_30:
        format_index = FORMAT_INDEX_720P_30;
        init_reglist = init_reglist_30fps;
        sensor->max_expo_time = EXPO_TIME_1_30_SEC;       /* 1/30 sec */
		break;

	case VIDEO_MODE_720P_50:
        format_index = FORMAT_INDEX_720P_50;
        init_reglist = init_reglist_50fps;
        sensor->max_expo_time = EXPO_TIME_1_50_SEC;       /* 1/50 sec */
		break;

	default:
		BL_LOGE("set_format error: invalid video mode!\r\n");
		BL_ABORT();
	}

    sensor->pix_clk = format_info[format_index].pix_clk;
    sensor->fps = format_info[format_index].fps;
    sensor->total_win.width = format_info[format_index].total_width;
    sensor->total_win.height = format_info[format_index].total_height;
#ifdef TEST_DIRTY_EDGE_FOR_SC1245
    sensor->out_win.width      = 1288;
    sensor->out_win.height     = 728;
    sensor->dsp2_out_win.width  = 1280;
    sensor->dsp2_out_win.height = 720;
#else
    sensor->out_win.width      = 1280;
    sensor->out_win.height     = 720;
    sensor->dsp2_out_win.width  = 1280;
    sensor->dsp2_out_win.height = 720;
#endif

    for (i = 0; init_reglist[i].addr != REGLIST_END; i++) {
        SCCB_Write_Reg16(sensor->slv_addr, init_reglist[i].addr, (uint8_t)init_reglist[i].data);
        //printf("reg 0x%04x = 0x%02x\r\n", init_reglist[i].addr, SCCB_Read_Reg16_Dbg(sensor->slv_addr, init_reglist[i].addr));
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
    int mode_num = sizeof(sc1245_mode)/sizeof(sc1245_mode[0]);
    if (!is_sensor_dsp2_input_match(sc1245_mode, mode_num)) {
        return -1;
    }

    /* Initialize sensor structure */
    SENSOR_INIT_COMMON(SC1245);
/*
#if (BL80X_HW_VER <= BL80X_HW_A0)
    set_format(sensor, VIDEO_MODE_720P_25);
#else
    set_format(sensor, VIDEO_MODE_720P_25);
#endif
*/
    BL_LOGI("SC1245 batch: 0x%02x\r\n", SCCB_Read_Reg16_Dbg(sensor->slv_addr, 0x3020));

    SCCB_Write_Reg16(sensor->slv_addr, 0x3640, 0x00);       /* IO driver control */
    SCCB_Write_Reg16(sensor->slv_addr, 0x3641, 0x1);      /*TODO: pixel delay */

//    SCCB_Write_Reg16(sensor->slv_addr, 0x3d08, 0x0);      /*TODO: invert the sensor pix clk polarity */

#if 0   // enable test pattern
    SCCB_Write_Reg16(sensor->slv_addr, 0x4501, 0xc8);     /* test pattern enable */
    SCCB_Write_Reg16(sensor->slv_addr, 0x3902, 0x05);     /* manual BLC  */
#endif

    return 0;
}

const BL_SENSOR_DESC_T sensor_desc_sc1245 ATTR_SENSOR_DEVICE_TABLE =
{
	SENSOR_NAME,
    SLAVE_ADDR,
    probe,
    init,
    setFmt,
};

