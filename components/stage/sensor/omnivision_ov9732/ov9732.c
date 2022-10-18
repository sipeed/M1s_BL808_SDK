#include <bl808.h>
#include "sensor_internal.h"
#include "sccb.h"
#include "ov9732.h"

/* OV9732 sensor info */
#define SLAVE_ADDR                  0x36
#define SENSOR_ID_H                 0x97
#define SENSOR_ID_L                 0x32
#define MIN_EXPO_TIME               INT_TO_EXPO_TIME(6000)          /* 1/6000 sec */
#define MAX_EXPO_TIME               INT_TO_EXPO_TIME(25)            /* 1/25 sec */
#define REG_ADDR_BIT                SENSOR_REG_ADDR_16BIT

//#define MAX_GAIN                    GAIN_DB_FLOAT_TO_INT(35.8125)      /* 35.8125 dB */
#define MAX_GAIN                    GAIN_DB_FLOAT_TO_INT(24)      /* limit max gain to 24 dB to avoid bad noise */
#define MIN_GAIN_STEP               (GAIN_6_DB / 64)                /* 0.09375 dB */

/* OV9732 registers */
 #define REG_SENSOR_ID_H            0x300a
 #define REG_SENSOR_ID_L            0x300b
 #define REG_GAIN_MSB			    0x350A
 #define REG_GAIN_LSB			    0x350B
 #define REG_R_GAIN_MSB		        0x5180
 #define REG_R_GAIN_LSB		        0x5181
 #define REG_G_GAIN_MSB		        0x5182
 #define REG_G_GAIN_LSB		        0x5183
 #define REG_B_GAIN_MSB		        0x5184
 #define REG_B_GAIN_LSB		        0x5185
 #define REG_LONG_EXPO_H		    0x3500
 #define REG_LONG_EXPO_M		    0x3501
 #define REG_LONG_EXPO_L		    0x3502


#define REG_TOTAL_WIDTH_H           0x380c
#define REG_TOTAL_WIDTH_L           0x380d
#define REG_TOTAL_HEIGHT_H          0x380e
#define REG_TOTAL_HEIGHT_L          0x380f

#define REG_OUT_WIDTH_H             0x3808
#define REG_OUT_WIDTH_L             0x3809
#define REG_OUT_HEIHT_H             0x380a
#define REG_OUT_HEIHT_L             0x380b

typedef enum {
    FORMAT_INDEX_720P_25 = 0,
    FORMAT_INDEX_720P_30,
    FORMAT_INDEX_INVALID,
} FORMAT_INDEX;

static const int ov9732_mode[] = {\
    DSP2_INPUT_DVP,\
};

/* TODO: make total height even to workaround bayer reverse issue in bottom 3 lines */
static const sensor_format_t format_info[] = {
    {   /* for 720p25 */
        .total_width	= 1478,
        .total_height	= 974,
        .pix_clk        = 36000000,
    },
    {   /* for 720p30 */
        .total_width	= 1478,
        .total_height	= 812,
        .pix_clk        = 36000000,
    },
};


static const sensor_reg_16_8_t init_reglist[] =
{
    /*
        General status [0x0100, 0x0103, 0x0106, 0x300A ~ 0x300B, 0x302A]
     */
    /* Software reset on*/
    {0x0103, 0x01}, /* Software reset.*/
    /* Sleep mode*/
    {0x0100, 0x00}, /* Mode Select for Software Standby.*/
    {0x3001, 0x1f},
    {0x3002, 0xff},
    {0x3007, 0x40},
    {0x3008, 0x00},

    {0x3009, 0x03}, /* Bit[6:5]:output drive capability for MIPI/DVP */
    {0x3010, 0x00},
    {0x3011, 0x00},
    {0x3014, 0x36},

    /*
        PLL 24MHZ
    */
    {0x301e, 0x15},
    {0x3030, 0x09},
    {0x3080, 0x02}, /* Pre PLL clock divider value */
    {0x3081, 0x3c}, /* PLL multiplier value */
    {0x3082, 0x04}, /* Video timing system clock divider[3:0] */
    {0x3083, 0x00}, /* Video timing pixel clock divider[0] */
    {0x3084, 0x02},
    {0x3085, 0x01},
    {0x3086, 0x01},
    {0x3089, 0x01},
    {0x308a, 0x00},
    {0x3103, 0x01}, /* Output system clock divider */

    /*
        Analog control [0x3600 ~ 0x363F]
        RSVD
     */
    {0x3600, 0xf6},
    {0x3601, 0x72},
    {0x3605, 0x66},
    {0x3610, 0x0c},
    {0x3611, 0x60},
    {0x3612, 0x35},
    {0x3654, 0x10},
    {0x3655, 0x77},
    {0x3656, 0x77},
    {0x3657, 0x07},
    {0x3658, 0x22},
    {0x3659, 0x22},
    {0x365a, 0x02},

    /*
        Sensor control [0x3700 ~ 0x370C]
        RSVD
    */
    {0x3700, 0x1f},
    {0x3701, 0x10},
    {0x3702, 0x0c},
    {0x3703, 0x0b},
    {0x3704, 0x3c},
    {0x3705, 0x51},
    {0x370d, 0x20},
    {0x3710, 0x0d},

    /*
        PSRAM control [0x3780 ~ 0x3785]
        RSVD
     */
    {0x3782, 0x58},
    {0x3783, 0x60},
    {0x3784, 0x05},
    {0x3785, 0x55},
    {0x37c0, 0x07},

    /*
        Frame timing [0x3800 ~ 0x381D, 0x3820 ~ 0x3829]
     */
    /* 4 */
    {0x3800, 0x00}, /* Array horizontal start point high byte */
    {0x3801, 0x04}, /* Array horizontal start point low byte */
    /* 4 */
    {0x3802, 0x00}, /* Array vertical start point high byte */
    {0x3803, 0x04}, /* Array vertical start point low byte */
    /* 1291 */
    {0x3804, 0x05}, /* Array horizontal end point high byte */
    {0x3805, 0x0b}, /* Array horizontal end point low byte */
    /* 731 */
    {0x3806, 0x02}, /* Array vertical end point high byte */
    {0x3807, 0xdb}, /* Array vertical end point low byte */
    /* 1280 */
    {0x3808, 0x05}, /* DSP2 horizontal output width high byte */
    {0x3809, 0x00}, /* DSP2 horizontal output width low byte */
    /* 720 */
    {0x380a, 0x02}, /* DSP2 vertical output height high byte */
    {0x380b, 0xd0}, /* DSP2 vertical output height low byte */

    {0x3810, 0x00}, /* DSP2 horizontal windowing offset high byte */
    {0x3811, 0x04}, /* DSP2 horizontal windowing offset low byte */
    {0x3812, 0x00}, /* DSP2 vertical windowing offset high byte */
    {0x3813, 0x04}, /* DSP2 vertical windowing offset low byte */
    {0x3816, 0x00}, /* Vsync start row high */
    {0x3817, 0x00}, /* Vsync start row low */
    {0x3818, 0x00}, /* Vsync end row high */
    {0x3819, 0x01}, /* Vsync end row low */
    {0x3820, 0x10},
    {0x3821, 0x00}, /* vsub/hsub setting */
    {0x382c, 0x06},

    /*
        AEC control [0x3500 ~ 0x3505, 0x3509 ~ 0x350B, 0x3510 ~ 0x3513]
     */
    {0x3500, 0x00}, /* Bit[3:0]: Long exposure[19:16] */
    {0x3501, 0x20}, /* Long exposure[15:8] */
    {0x3502, 0x00}, /* Bit[7:0]: Long exposure[7:0] Low 4 bits are fraction bits */
    {0x3503, 0x03}, /* AEC MANUAL */
    {0x3504, 0x00}, /* Bit[1:0]: Manual sensor gain[9:8] */
    {0x3505, 0x00}, /* Bit[7:0]: Manual sensor gain[7:0] */
    {0x3509, 0x10}, /* AEC convert gain enable*/
    {0x350a, 0x00}, /* Bit[1:0]: Long gain[9:8] */
    {0x350b, 0x10}, /* Bit[7:0]: Long gain[7:0] */

    {0x3d00, 0x00},
    {0x3d01, 0x00},
    {0x3d02, 0x00},
    {0x3d03, 0x00},
    {0x3d04, 0x00},
    {0x3d05, 0x00},
    {0x3d06, 0x00},
    {0x3d07, 0x00},
    {0x3d08, 0x00},
    {0x3d09, 0x00},
    {0x3d0a, 0x00},
    {0x3d0b, 0x00},
    {0x3d0c, 0x00},
    {0x3d0d, 0x00},
    {0x3d0e, 0x00},
    {0x3d0f, 0x00},
    {0x3d80, 0x00},
    {0x3d81, 0x00},
    {0x3d82, 0x38},
    {0x3d83, 0xa4},
    {0x3d84, 0x00},
    {0x3d85, 0x00},
    {0x3d86, 0x1f},
    {0x3d87, 0x03},
    {0x3d8b, 0x00},
    {0x3d8f, 0x00},

    /*
        BLC control [0x4000 ~ 0x4017, 0x4020 ~ 0x4041, 0x4050 ~ 0x405D]
     */
    {0x4001, 0xe0},
    {0x4004, 0x00}, /* Horizontal win start[10:8] */
    {0x4005, 0x02}, /* Horizontal win start[7:0] */
    {0x4006, 0x01}, /* Horizontal win pad[10:8] */
    {0x4007, 0x40}, /* Horizontal win pad[7:0] */
    {0x4009, 0x0b}, /* Black line end line */

    /*
        Output data clipping [0x4300 ~ 0x4303]
     */
    {0x4300, 0x03}, /* Bit[1:0]: Ymax[9:8] Ymax high byte */
    {0x4301, 0xff}, /* Bit[7:0]: Ymax[7:0] Ymax low byte */
    {0x4304, 0x00},
    {0x4305, 0x00},
    {0x4309, 0x00},
    {0x4600, 0x00},
    {0x4601, 0x04},
    {0x4800, 0x04},
    {0x4805, 0x00},
    {0x4821, 0x3c},
    {0x4823, 0x3c},
    {0x4837, 0x2d},
    {0x4a00, 0x00},
    {0x4f00, 0x80},
    {0x4f01, 0x10},
    {0x4f02, 0x00},
    {0x4f03, 0x00},
    {0x4f04, 0x00},
    {0x4f05, 0x00},
    {0x4f06, 0x00},
    {0x4f07, 0x00},
    {0x4f08, 0x00},
    {0x4f09, 0x00},

    /*
        DSP2 control [0x5000 ~ 0x5004, 0x5006 ~ 0x5009, 0x500B ~ 0x5017]
     */
    {0x5000, 0x13},		/* TODO: disable wc to fix sparkling dark purple dots issue */
    {0x500c, 0x00},
    {0x500d, 0x00},
    {0x500e, 0x00},
    {0x500f, 0x00},
    {0x5010, 0x00},
    {0x5011, 0x00},
    {0x5012, 0x00},
    {0x5013, 0x00},
    {0x5014, 0x00},
    {0x5015, 0x00},
    {0x5016, 0x00},
    {0x5017, 0x00},
    {0x5080, 0x00},
    {0x5180, 0x01},
    {0x5181, 0x00},
    {0x5182, 0x01},
    {0x5183, 0x00},
    {0x5184, 0x01},
    {0x5185, 0x00},
    {0x5708, 0x06},
    {0x5781, 0x0e},
    {0x5783, 0x0f},
};

/* This is 16-step gain table, OV9732_GAIN_ROWS = 383, OV9732_GAIN_COLS = 3 */
static const uint8_t OV9732_GAIN_TABLE[383][3] = {
    {0x10, 0x01, 0x00}, /* index:0, gain:0.00000db -> x1.000000 */
    {0x10, 0x01, 0x00}, /* index:1, gain:0.09375db -> x1.010852 */
    {0x10, 0x01, 0x00}, /* index:2, gain:0.18750db -> x1.021821 */
    {0x11, 0x01, 0x00}, /* index:3, gain:0.28125db -> x1.032910 */
    {0x11, 0x01, 0x00}, /* index:4, gain:0.37500db -> x1.044119 */
    {0x11, 0x01, 0x00}, /* index:5, gain:0.46875db -> x1.055450 */
    {0x11, 0x01, 0x00}, /* index:6, gain:0.56250db -> x1.066903 */
    {0x11, 0x01, 0x00}, /* index:7, gain:0.65625db -> x1.078481 */
    {0x11, 0x01, 0x00}, /* index:8, gain:0.75000db -> x1.090184 */
    {0x12, 0x01, 0x00}, /* index:9, gain:0.84375db -> x1.102015 */
    {0x12, 0x01, 0x00}, /* index:10, gain:0.93750db -> x1.113974 */
    {0x12, 0x01, 0x00}, /* index:11, gain:1.03125db -> x1.126063 */
    {0x12, 0x01, 0x00}, /* index:12, gain:1.12500db -> x1.138282 */
    {0x12, 0x01, 0x00}, /* index:13, gain:1.21875db -> x1.150635 */
    {0x13, 0x01, 0x00}, /* index:14, gain:1.31250db -> x1.163121 */
    {0x13, 0x01, 0x00}, /* index:15, gain:1.40625db -> x1.175743 */
    {0x13, 0x01, 0x00}, /* index:16, gain:1.50000db -> x1.188502 */
    {0x13, 0x01, 0x00}, /* index:17, gain:1.59375db -> x1.201400 */
    {0x13, 0x01, 0x00}, /* index:18, gain:1.68750db -> x1.214437 */
    {0x14, 0x01, 0x00}, /* index:19, gain:1.78125db -> x1.227616 */
    {0x14, 0x01, 0x00}, /* index:20, gain:1.87500db -> x1.240938 */
    {0x14, 0x01, 0x00}, /* index:21, gain:1.96875db -> x1.254404 */
    {0x14, 0x01, 0x00}, /* index:22, gain:2.06250db -> x1.268017 */
    {0x15, 0x01, 0x00}, /* index:23, gain:2.15625db -> x1.281777 */
    {0x15, 0x01, 0x00}, /* index:24, gain:2.25000db -> x1.295687 */
    {0x15, 0x01, 0x00}, /* index:25, gain:2.34375db -> x1.309747 */
    {0x15, 0x01, 0x00}, /* index:26, gain:2.43750db -> x1.323960 */
    {0x15, 0x01, 0x00}, /* index:27, gain:2.53125db -> x1.338328 */
    {0x16, 0x01, 0x00}, /* index:28, gain:2.62500db -> x1.352851 */
    {0x16, 0x01, 0x00}, /* index:29, gain:2.71875db -> x1.367532 */
    {0x16, 0x01, 0x00}, /* index:30, gain:2.81250db -> x1.382372 */
    {0x16, 0x01, 0x00}, /* index:31, gain:2.90625db -> x1.397374 */
    {0x17, 0x01, 0x00}, /* index:32, gain:3.00000db -> x1.412538 */
    {0x17, 0x01, 0x00}, /* index:33, gain:3.09375db -> x1.427866 */
    {0x17, 0x01, 0x00}, /* index:34, gain:3.18750db -> x1.443361 */
    {0x17, 0x01, 0x00}, /* index:35, gain:3.28125db -> x1.459024 */
    {0x18, 0x01, 0x00}, /* index:36, gain:3.37500db -> x1.474857 */
    {0x18, 0x01, 0x00}, /* index:37, gain:3.46875db -> x1.490862 */
    {0x18, 0x01, 0x00}, /* index:38, gain:3.56250db -> x1.507041 */
    {0x18, 0x01, 0x00}, /* index:39, gain:3.65625db -> x1.523395 */
    {0x19, 0x01, 0x00}, /* index:40, gain:3.75000db -> x1.539927 */
    {0x19, 0x01, 0x00}, /* index:41, gain:3.84375db -> x1.556638 */
    {0x19, 0x01, 0x00}, /* index:42, gain:3.93750db -> x1.573530 */
    {0x19, 0x01, 0x00}, /* index:43, gain:4.03125db -> x1.590606 */
    {0x1a, 0x01, 0x00}, /* index:44, gain:4.12500db -> x1.607867 */
    {0x1a, 0x01, 0x00}, /* index:45, gain:4.21875db -> x1.625315 */
    {0x1a, 0x01, 0x00}, /* index:46, gain:4.31250db -> x1.642952 */
    {0x1b, 0x01, 0x00}, /* index:47, gain:4.40625db -> x1.660782 */
    {0x1b, 0x01, 0x00}, /* index:48, gain:4.50000db -> x1.678804 */
    {0x1b, 0x01, 0x00}, /* index:49, gain:4.59375db -> x1.697022 */
    {0x1b, 0x01, 0x00}, /* index:50, gain:4.68750db -> x1.715438 */
    {0x1c, 0x01, 0x00}, /* index:51, gain:4.78125db -> x1.734054 */
    {0x1c, 0x01, 0x00}, /* index:52, gain:4.87500db -> x1.752871 */
    {0x1c, 0x01, 0x00}, /* index:53, gain:4.96875db -> x1.771893 */
    {0x1d, 0x01, 0x00}, /* index:54, gain:5.06250db -> x1.791121 */
    {0x1d, 0x01, 0x00}, /* index:55, gain:5.15625db -> x1.810558 */
    {0x1d, 0x01, 0x00}, /* index:56, gain:5.25000db -> x1.830206 */
    {0x1e, 0x01, 0x00}, /* index:57, gain:5.34375db -> x1.850067 */
    {0x1e, 0x01, 0x00}, /* index:58, gain:5.43750db -> x1.870144 */
    {0x1e, 0x01, 0x00}, /* index:59, gain:5.53125db -> x1.890438 */
    {0x1f, 0x01, 0x00}, /* index:60, gain:5.62500db -> x1.910953 */
    {0x1f, 0x01, 0x00}, /* index:61, gain:5.71875db -> x1.931690 */
    {0x1f, 0x01, 0x00}, /* index:62, gain:5.81250db -> x1.952653 */
    {0x20, 0x01, 0x00}, /* index:63, gain:5.90625db -> x1.973842 */
    {0x20, 0x01, 0x00}, /* index:64, gain:6.00000db -> x1.995262 */
    {0x20, 0x01, 0x00}, /* index:65, gain:6.09375db -> x2.016915 */
    {0x21, 0x01, 0x00}, /* index:66, gain:6.18750db -> x2.038802 */
    {0x21, 0x01, 0x00}, /* index:67, gain:6.28125db -> x2.060927 */
    {0x21, 0x01, 0x00}, /* index:68, gain:6.37500db -> x2.083291 */
    {0x22, 0x01, 0x00}, /* index:69, gain:6.46875db -> x2.105899 */
    {0x22, 0x01, 0x00}, /* index:70, gain:6.56250db -> x2.128752 */
    {0x22, 0x01, 0x00}, /* index:71, gain:6.65625db -> x2.151852 */
    {0x23, 0x01, 0x00}, /* index:72, gain:6.75000db -> x2.175204 */
    {0x23, 0x01, 0x00}, /* index:73, gain:6.84375db -> x2.198809 */
    {0x24, 0x01, 0x00}, /* index:74, gain:6.93750db -> x2.222670 */
    {0x24, 0x01, 0x00}, /* index:75, gain:7.03125db -> x2.246790 */
    {0x24, 0x01, 0x00}, /* index:76, gain:7.12500db -> x2.271172 */
    {0x25, 0x01, 0x00}, /* index:77, gain:7.21875db -> x2.295818 */
    {0x25, 0x01, 0x00}, /* index:78, gain:7.31250db -> x2.320732 */
    {0x26, 0x01, 0x00}, /* index:79, gain:7.40625db -> x2.345916 */
    {0x26, 0x01, 0x00}, /* index:80, gain:7.50000db -> x2.371374 */
    {0x26, 0x01, 0x00}, /* index:81, gain:7.59375db -> x2.397107 */
    {0x27, 0x01, 0x00}, /* index:82, gain:7.68750db -> x2.423120 */
    {0x27, 0x01, 0x00}, /* index:83, gain:7.78125db -> x2.449416 */
    {0x28, 0x01, 0x00}, /* index:84, gain:7.87500db -> x2.475996 */
    {0x28, 0x01, 0x00}, /* index:85, gain:7.96875db -> x2.502865 */
    {0x28, 0x01, 0x00}, /* index:86, gain:8.06250db -> x2.530026 */
    {0x29, 0x01, 0x00}, /* index:87, gain:8.15625db -> x2.557482 */
    {0x29, 0x01, 0x00}, /* index:88, gain:8.25000db -> x2.585235 */
    {0x2a, 0x01, 0x00}, /* index:89, gain:8.34375db -> x2.613289 */
    {0x2a, 0x01, 0x00}, /* index:90, gain:8.43750db -> x2.641648 */
    {0x2b, 0x01, 0x00}, /* index:91, gain:8.53125db -> x2.670315 */
    {0x2b, 0x01, 0x00}, /* index:92, gain:8.62500db -> x2.699293 */
    {0x2c, 0x01, 0x00}, /* index:93, gain:8.71875db -> x2.728585 */
    {0x2c, 0x01, 0x00}, /* index:94, gain:8.81250db -> x2.758195 */
    {0x2d, 0x01, 0x00}, /* index:95, gain:8.90625db -> x2.788127 */
    {0x2d, 0x01, 0x00}, /* index:96, gain:9.00000db -> x2.818383 */
    {0x2e, 0x01, 0x00}, /* index:97, gain:9.09375db -> x2.848968 */
    {0x2e, 0x01, 0x00}, /* index:98, gain:9.18750db -> x2.879884 */
    {0x2f, 0x01, 0x00}, /* index:99, gain:9.28125db -> x2.911136 */
    {0x2f, 0x01, 0x00}, /* index:100, gain:9.37500db -> x2.942727 */
    {0x30, 0x01, 0x00}, /* index:101, gain:9.46875db -> x2.974661 */
    {0x30, 0x01, 0x00}, /* index:102, gain:9.56250db -> x3.006942 */
    {0x31, 0x01, 0x00}, /* index:103, gain:9.65625db -> x3.039572 */
    {0x31, 0x01, 0x00}, /* index:104, gain:9.75000db -> x3.072557 */
    {0x32, 0x01, 0x00}, /* index:105, gain:9.84375db -> x3.105900 */
    {0x32, 0x01, 0x00}, /* index:106, gain:9.93750db -> x3.139605 */
    {0x33, 0x01, 0x00}, /* index:107, gain:10.03125db -> x3.173675 */
    {0x33, 0x01, 0x00}, /* index:108, gain:10.12500db -> x3.208116 */
    {0x34, 0x01, 0x00}, /* index:109, gain:10.21875db -> x3.242930 */
    {0x34, 0x01, 0x00}, /* index:110, gain:10.31250db -> x3.278121 */
    {0x35, 0x01, 0x00}, /* index:111, gain:10.40625db -> x3.313695 */
    {0x36, 0x01, 0x00}, /* index:112, gain:10.50000db -> x3.349654 */
    {0x36, 0x01, 0x00}, /* index:113, gain:10.59375db -> x3.386004 */
    {0x37, 0x01, 0x00}, /* index:114, gain:10.68750db -> x3.422749 */
    {0x37, 0x01, 0x00}, /* index:115, gain:10.78125db -> x3.459892 */
    {0x38, 0x01, 0x00}, /* index:116, gain:10.87500db -> x3.497438 */
    {0x39, 0x01, 0x00}, /* index:117, gain:10.96875db -> x3.535391 */
    {0x39, 0x01, 0x00}, /* index:118, gain:11.06250db -> x3.573757 */
    {0x3a, 0x01, 0x00}, /* index:119, gain:11.15625db -> x3.612539 */
    {0x3a, 0x01, 0x00}, /* index:120, gain:11.25000db -> x3.651741 */
    {0x3b, 0x01, 0x00}, /* index:121, gain:11.34375db -> x3.691369 */
    {0x3c, 0x01, 0x00}, /* index:122, gain:11.43750db -> x3.731427 */
    {0x3c, 0x01, 0x00}, /* index:123, gain:11.53125db -> x3.771920 */
    {0x3d, 0x01, 0x00}, /* index:124, gain:11.62500db -> x3.812853 */
    {0x3e, 0x01, 0x00}, /* index:125, gain:11.71875db -> x3.854229 */
    {0x3e, 0x01, 0x00}, /* index:126, gain:11.81250db -> x3.896054 */
    {0x3f, 0x01, 0x00}, /* index:127, gain:11.90625db -> x3.938333 */
    {0x40, 0x01, 0x00}, /* index:128, gain:12.00000db -> x3.981072 */
    {0x40, 0x01, 0x00}, /* index:129, gain:12.09375db -> x4.024274 */
    {0x41, 0x01, 0x00}, /* index:130, gain:12.18750db -> x4.067944 */
    {0x42, 0x01, 0x00}, /* index:131, gain:12.28125db -> x4.112089 */
    {0x43, 0x01, 0x00}, /* index:132, gain:12.37500db -> x4.156712 */
    {0x43, 0x01, 0x00}, /* index:133, gain:12.46875db -> x4.201821 */
    {0x44, 0x01, 0x00}, /* index:134, gain:12.56250db -> x4.247418 */
    {0x45, 0x01, 0x00}, /* index:135, gain:12.65625db -> x4.293510 */
    {0x45, 0x01, 0x00}, /* index:136, gain:12.75000db -> x4.340103 */
    {0x46, 0x01, 0x00}, /* index:137, gain:12.84375db -> x4.387200 */
    {0x47, 0x01, 0x00}, /* index:138, gain:12.93750db -> x4.434810 */
    {0x48, 0x01, 0x00}, /* index:139, gain:13.03125db -> x4.482936 */
    {0x49, 0x01, 0x00}, /* index:140, gain:13.12500db -> x4.531584 */
    {0x49, 0x01, 0x00}, /* index:141, gain:13.21875db -> x4.580759 */
    {0x4a, 0x01, 0x00}, /* index:142, gain:13.31250db -> x4.630469 */
    {0x4b, 0x01, 0x00}, /* index:143, gain:13.40625db -> x4.680719 */
    {0x4c, 0x01, 0x00}, /* index:144, gain:13.50000db -> x4.731513 */
    {0x4d, 0x01, 0x00}, /* index:145, gain:13.59375db -> x4.782858 */
    {0x4d, 0x01, 0x00}, /* index:146, gain:13.68750db -> x4.834761 */
    {0x4e, 0x01, 0x00}, /* index:147, gain:13.78125db -> x4.887227 */
    {0x4f, 0x01, 0x00}, /* index:148, gain:13.87500db -> x4.940262 */
    {0x50, 0x01, 0x00}, /* index:149, gain:13.96875db -> x4.993873 */
    {0x51, 0x01, 0x00}, /* index:150, gain:14.06250db -> x5.048066 */
    {0x52, 0x01, 0x00}, /* index:151, gain:14.15625db -> x5.102846 */
    {0x53, 0x01, 0x00}, /* index:152, gain:14.25000db -> x5.158221 */
    {0x53, 0x01, 0x00}, /* index:153, gain:14.34375db -> x5.214198 */
    {0x54, 0x01, 0x00}, /* index:154, gain:14.43750db -> x5.270781 */
    {0x55, 0x01, 0x00}, /* index:155, gain:14.53125db -> x5.327979 */
    {0x56, 0x01, 0x00}, /* index:156, gain:14.62500db -> x5.385797 */
    {0x57, 0x01, 0x00}, /* index:157, gain:14.71875db -> x5.444243 */
    {0x58, 0x01, 0x00}, /* index:158, gain:14.81250db -> x5.503323 */
    {0x59, 0x01, 0x00}, /* index:159, gain:14.90625db -> x5.563044 */
    {0x5a, 0x01, 0x00}, /* index:160, gain:15.00000db -> x5.623413 */
    {0x5b, 0x01, 0x00}, /* index:161, gain:15.09375db -> x5.684437 */
    {0x5c, 0x01, 0x00}, /* index:162, gain:15.18750db -> x5.746124 */
    {0x5d, 0x01, 0x00}, /* index:163, gain:15.28125db -> x5.808480 */
    {0x5e, 0x01, 0x00}, /* index:164, gain:15.37500db -> x5.871513 */
    {0x5f, 0x01, 0x00}, /* index:165, gain:15.46875db -> x5.935229 */
    {0x60, 0x01, 0x00}, /* index:166, gain:15.56250db -> x5.999637 */
    {0x61, 0x01, 0x00}, /* index:167, gain:15.65625db -> x6.064744 */
    {0x62, 0x01, 0x00}, /* index:168, gain:15.75000db -> x6.130558 */
    {0x63, 0x01, 0x00}, /* index:169, gain:15.84375db -> x6.197086 */
    {0x64, 0x01, 0x00}, /* index:170, gain:15.93750db -> x6.264335 */
    {0x65, 0x01, 0x00}, /* index:171, gain:16.03125db -> x6.332315 */
    {0x66, 0x01, 0x00}, /* index:172, gain:16.12500db -> x6.401032 */
    {0x68, 0x01, 0x00}, /* index:173, gain:16.21875db -> x6.470495 */
    {0x69, 0x01, 0x00}, /* index:174, gain:16.31250db -> x6.540712 */
    {0x6a, 0x01, 0x00}, /* index:175, gain:16.40625db -> x6.611690 */
    {0x6b, 0x01, 0x00}, /* index:176, gain:16.50000db -> x6.683439 */
    {0x6c, 0x01, 0x00}, /* index:177, gain:16.59375db -> x6.755966 */
    {0x6d, 0x01, 0x00}, /* index:178, gain:16.68750db -> x6.829282 */
    {0x6e, 0x01, 0x00}, /* index:179, gain:16.78125db -> x6.903392 */
    {0x70, 0x01, 0x00}, /* index:180, gain:16.87500db -> x6.978306 */
    {0x71, 0x01, 0x00}, /* index:181, gain:16.96875db -> x7.054033 */
    {0x72, 0x01, 0x00}, /* index:182, gain:17.06250db -> x7.130582 */
    {0x73, 0x01, 0x00}, /* index:183, gain:17.15625db -> x7.207963 */
    {0x75, 0x01, 0x00}, /* index:184, gain:17.25000db -> x7.286182 */
    {0x76, 0x01, 0x00}, /* index:185, gain:17.34375db -> x7.365250 */
    {0x77, 0x01, 0x00}, /* index:186, gain:17.43750db -> x7.445176 */
    {0x78, 0x01, 0x00}, /* index:187, gain:17.53125db -> x7.525970 */
    {0x7a, 0x01, 0x00}, /* index:188, gain:17.62500db -> x7.607641 */
    {0x7b, 0x01, 0x00}, /* index:189, gain:17.71875db -> x7.690198 */
    {0x7c, 0x01, 0x00}, /* index:190, gain:17.81250db -> x7.773650 */
    {0x7e, 0x01, 0x00}, /* index:191, gain:17.90625db -> x7.858008 */
    {0x7f, 0x01, 0x00}, /* index:192, gain:18.00000db -> x7.943282 */
    {0x80, 0x01, 0x00}, /* index:193, gain:18.09375db -> x8.029482 */
    {0x82, 0x01, 0x00}, /* index:194, gain:18.18750db -> x8.116616 */
    {0x83, 0x01, 0x00}, /* index:195, gain:18.28125db -> x8.204696 */
    {0x85, 0x01, 0x00}, /* index:196, gain:18.37500db -> x8.293732 */
    {0x86, 0x01, 0x00}, /* index:197, gain:18.46875db -> x8.383734 */
    {0x88, 0x01, 0x00}, /* index:198, gain:18.56250db -> x8.474713 */
    {0x89, 0x01, 0x00}, /* index:199, gain:18.65625db -> x8.566679 */
    {0x8b, 0x01, 0x00}, /* index:200, gain:18.75000db -> x8.659643 */
    {0x8c, 0x01, 0x00}, /* index:201, gain:18.84375db -> x8.753616 */
    {0x8e, 0x01, 0x00}, /* index:202, gain:18.93750db -> x8.848608 */
    {0x8f, 0x01, 0x00}, /* index:203, gain:19.03125db -> x8.944633 */
    {0x91, 0x01, 0x00}, /* index:204, gain:19.12500db -> x9.041698 */
    {0x92, 0x01, 0x00}, /* index:205, gain:19.21875db -> x9.139817 */
    {0x94, 0x01, 0x00}, /* index:206, gain:19.31250db -> x9.239000 */
    {0x95, 0x01, 0x00}, /* index:207, gain:19.40625db -> x9.339260 */
    {0x97, 0x01, 0x00}, /* index:208, gain:19.50000db -> x9.440609 */
    {0x99, 0x01, 0x00}, /* index:209, gain:19.59375db -> x9.543057 */
    {0x9a, 0x01, 0x00}, /* index:210, gain:19.68750db -> x9.646616 */
    {0x9c, 0x01, 0x00}, /* index:211, gain:19.78125db -> x9.751299 */
    {0x9e, 0x01, 0x00}, /* index:212, gain:19.87500db -> x9.857118 */
    {0x9f, 0x01, 0x00}, /* index:213, gain:19.96875db -> x9.964087 */
    {0xa1, 0x01, 0x00}, /* index:214, gain:20.06250db -> x10.072214 */
    {0xa3, 0x01, 0x00}, /* index:215, gain:20.15625db -> x10.181517 */
    {0xa5, 0x01, 0x00}, /* index:216, gain:20.25000db -> x10.292006 */
    {0xa6, 0x01, 0x00}, /* index:217, gain:20.34375db -> x10.403692 */
    {0xa8, 0x01, 0x00}, /* index:218, gain:20.43750db -> x10.516592 */
    {0xaa, 0x01, 0x00}, /* index:219, gain:20.53125db -> x10.630714 */
    {0xac, 0x01, 0x00}, /* index:220, gain:20.62500db -> x10.746078 */
    {0xae, 0x01, 0x00}, /* index:221, gain:20.71875db -> x10.862694 */
    {0xb0, 0x01, 0x00}, /* index:222, gain:20.81250db -> x10.980572 */
    {0xb2, 0x01, 0x00}, /* index:223, gain:20.90625db -> x11.099733 */
    {0xb4, 0x01, 0x00}, /* index:224, gain:21.00000db -> x11.220183 */
    {0xb5, 0x01, 0x00}, /* index:225, gain:21.09375db -> x11.341944 */
    {0xb7, 0x01, 0x00}, /* index:226, gain:21.18750db -> x11.465026 */
    {0xb9, 0x01, 0x00}, /* index:227, gain:21.28125db -> x11.589441 */
    {0xbb, 0x01, 0x00}, /* index:228, gain:21.37500db -> x11.715209 */
    {0xbd, 0x01, 0x00}, /* index:229, gain:21.46875db -> x11.842338 */
    {0xc0, 0x01, 0x00}, /* index:230, gain:21.56250db -> x11.970850 */
    {0xc2, 0x01, 0x00}, /* index:231, gain:21.65625db -> x12.100757 */
    {0xc4, 0x01, 0x00}, /* index:232, gain:21.75000db -> x12.232071 */
    {0xc6, 0x01, 0x00}, /* index:233, gain:21.84375db -> x12.364812 */
    {0xc8, 0x01, 0x00}, /* index:234, gain:21.93750db -> x12.498991 */
    {0xca, 0x01, 0x00}, /* index:235, gain:22.03125db -> x12.634629 */
    {0xcc, 0x01, 0x00}, /* index:236, gain:22.12500db -> x12.771739 */
    {0xcf, 0x01, 0x00}, /* index:237, gain:22.21875db -> x12.910334 */
    {0xd1, 0x01, 0x00}, /* index:238, gain:22.31250db -> x13.050436 */
    {0xd3, 0x01, 0x00}, /* index:239, gain:22.40625db -> x13.192055 */
    {0xd5, 0x01, 0x00}, /* index:240, gain:22.50000db -> x13.335214 */
    {0xd8, 0x01, 0x00}, /* index:241, gain:22.59375db -> x13.479927 */
    {0xda, 0x01, 0x00}, /* index:242, gain:22.68750db -> x13.626207 */
    {0xdc, 0x01, 0x00}, /* index:243, gain:22.78125db -> x13.774078 */
    {0xdf, 0x01, 0x00}, /* index:244, gain:22.87500db -> x13.923549 */
    {0xe1, 0x01, 0x00}, /* index:245, gain:22.96875db -> x14.074647 */
    {0xe4, 0x01, 0x00}, /* index:246, gain:23.06250db -> x14.227384 */
    {0xe6, 0x01, 0x00}, /* index:247, gain:23.15625db -> x14.381775 */
    {0xe9, 0x01, 0x00}, /* index:248, gain:23.25000db -> x14.537845 */
    {0xeb, 0x01, 0x00}, /* index:249, gain:23.34375db -> x14.695604 */
    {0xee, 0x01, 0x00}, /* index:250, gain:23.43750db -> x14.855080 */
    {0xf0, 0x01, 0x00}, /* index:251, gain:23.53125db -> x15.016287 */
    {0xf3, 0x01, 0x00}, /* index:252, gain:23.62500db -> x15.179238 */
    {0xf6, 0x01, 0x00}, /* index:253, gain:23.71875db -> x15.343962 */
    {0xf8, 0x01, 0x00}, /* index:254, gain:23.81250db -> x15.510470 */
    {0xf8, 0x01, 0x02}, /* index:255, gain:23.90625db -> x15.678788 */
    {0xf8, 0x01, 0x05}, /* index:256, gain:24.00000db -> x15.848934 */
    {0xf8, 0x01, 0x08}, /* index:257, gain:24.09375db -> x16.020921 */
    {0xf8, 0x01, 0x0b}, /* index:258, gain:24.18750db -> x16.194779 */
    {0xf8, 0x01, 0x0e}, /* index:259, gain:24.28125db -> x16.370519 */
    {0xf8, 0x01, 0x11}, /* index:260, gain:24.37500db -> x16.548171 */
    {0xf8, 0x01, 0x14}, /* index:261, gain:24.46875db -> x16.727751 */
    {0xf8, 0x01, 0x17}, /* index:262, gain:24.56250db -> x16.909275 */
    {0xf8, 0x01, 0x1a}, /* index:263, gain:24.65625db -> x17.092773 */
    {0xf8, 0x01, 0x1d}, /* index:264, gain:24.75000db -> x17.278258 */
    {0xf8, 0x01, 0x20}, /* index:265, gain:24.84375db -> x17.465760 */
    {0xf8, 0x01, 0x23}, /* index:266, gain:24.93750db -> x17.655298 */
    {0xf8, 0x01, 0x26}, /* index:267, gain:25.03125db -> x17.846887 */
    {0xf8, 0x01, 0x29}, /* index:268, gain:25.12500db -> x18.040560 */
    {0xf8, 0x01, 0x2d}, /* index:269, gain:25.21875db -> x18.236330 */
    {0xf8, 0x01, 0x30}, /* index:270, gain:25.31250db -> x18.434230 */
    {0xf8, 0x01, 0x33}, /* index:271, gain:25.40625db -> x18.634277 */
    {0xf8, 0x01, 0x37}, /* index:272, gain:25.50000db -> x18.836490 */
    {0xf8, 0x01, 0x3a}, /* index:273, gain:25.59375db -> x19.040902 */
    {0xf8, 0x01, 0x3d}, /* index:274, gain:25.68750db -> x19.247528 */
    {0xf8, 0x01, 0x41}, /* index:275, gain:25.78125db -> x19.456401 */
    {0xf8, 0x01, 0x44}, /* index:276, gain:25.87500db -> x19.667540 */
    {0xf8, 0x01, 0x48}, /* index:277, gain:25.96875db -> x19.880966 */
    {0xf8, 0x01, 0x4b}, /* index:278, gain:26.06250db -> x20.096713 */
    {0xf8, 0x01, 0x4f}, /* index:279, gain:26.15625db -> x20.314795 */
    {0xf8, 0x01, 0x53}, /* index:280, gain:26.25000db -> x20.535250 */
    {0xf8, 0x01, 0x56}, /* index:281, gain:26.34375db -> x20.758098 */
    {0xf8, 0x01, 0x5a}, /* index:282, gain:26.43750db -> x20.983357 */
    {0xf8, 0x01, 0x5e}, /* index:283, gain:26.53125db -> x21.211067 */
    {0xf8, 0x01, 0x62}, /* index:284, gain:26.62500db -> x21.441243 */
    {0xf8, 0x01, 0x65}, /* index:285, gain:26.71875db -> x21.673922 */
    {0xf8, 0x01, 0x69}, /* index:286, gain:26.81250db -> x21.909126 */
    {0xf8, 0x01, 0x6d}, /* index:287, gain:26.90625db -> x22.146876 */
    {0xf8, 0x01, 0x71}, /* index:288, gain:27.00000db -> x22.387213 */
    {0xf8, 0x01, 0x75}, /* index:289, gain:27.09375db -> x22.630151 */
    {0xf8, 0x01, 0x79}, /* index:290, gain:27.18750db -> x22.875732 */
    {0xf8, 0x01, 0x7d}, /* index:291, gain:27.28125db -> x23.123978 */
    {0xf8, 0x01, 0x82}, /* index:292, gain:27.37500db -> x23.374912 */
    {0xf8, 0x01, 0x86}, /* index:293, gain:27.46875db -> x23.628575 */
    {0xf8, 0x01, 0x8a}, /* index:294, gain:27.56250db -> x23.884984 */
    {0xf8, 0x01, 0x8e}, /* index:295, gain:27.65625db -> x24.144182 */
    {0xf8, 0x01, 0x93}, /* index:296, gain:27.75000db -> x24.406193 */
    {0xf8, 0x01, 0x97}, /* index:297, gain:27.84375db -> x24.671041 */
    {0xf8, 0x01, 0x9b}, /* index:298, gain:27.93750db -> x24.938770 */
    {0xf8, 0x01, 0xa0}, /* index:299, gain:28.03125db -> x25.209397 */
    {0xf8, 0x01, 0xa4}, /* index:300, gain:28.12500db -> x25.482967 */
    {0xf8, 0x01, 0xa9}, /* index:301, gain:28.21875db -> x25.759507 */
    {0xf8, 0x01, 0xae}, /* index:302, gain:28.31250db -> x26.039040 */
    {0xf8, 0x01, 0xb2}, /* index:303, gain:28.40625db -> x26.321614 */
    {0xf8, 0x01, 0xb7}, /* index:304, gain:28.50000db -> x26.607248 */
    {0xf8, 0x01, 0xbc}, /* index:305, gain:28.59375db -> x26.895988 */
    {0xf8, 0x01, 0xc1}, /* index:306, gain:28.68750db -> x27.187861 */
    {0xf8, 0x01, 0xc5}, /* index:307, gain:28.78125db -> x27.482895 */
    {0xf8, 0x01, 0xca}, /* index:308, gain:28.87500db -> x27.781137 */
    {0xf8, 0x01, 0xcf}, /* index:309, gain:28.96875db -> x28.082609 */
    {0xf8, 0x01, 0xd4}, /* index:310, gain:29.06250db -> x28.387360 */
    {0xf8, 0x01, 0xd9}, /* index:311, gain:29.15625db -> x28.695417 */
    {0xf8, 0x01, 0xdf}, /* index:312, gain:29.25000db -> x29.006810 */
    {0xf8, 0x01, 0xe4}, /* index:313, gain:29.34375db -> x29.321590 */
    {0xf8, 0x01, 0xe9}, /* index:314, gain:29.43750db -> x29.639778 */
    {0xf8, 0x01, 0xee}, /* index:315, gain:29.53125db -> x29.961427 */
    {0xf8, 0x01, 0xf4}, /* index:316, gain:29.62500db -> x30.286567 */
    {0xf8, 0x01, 0xf9}, /* index:317, gain:29.71875db -> x30.615226 */
    {0xf8, 0x01, 0xff}, /* index:318, gain:29.81250db -> x30.947461 */
    {0xf8, 0x02, 0x04}, /* index:319, gain:29.90625db -> x31.283292 */
    {0xf8, 0x02, 0x0a}, /* index:320, gain:30.00000db -> x31.622777 */
    {0xf8, 0x02, 0x0f}, /* index:321, gain:30.09375db -> x31.965945 */
    {0xf8, 0x02, 0x15}, /* index:322, gain:30.18750db -> x32.312829 */
    {0xf8, 0x02, 0x1b}, /* index:323, gain:30.28125db -> x32.663485 */
    {0xf8, 0x02, 0x21}, /* index:324, gain:30.37500db -> x33.017938 */
    {0xf8, 0x02, 0x27}, /* index:325, gain:30.46875db -> x33.376247 */
    {0xf8, 0x02, 0x2d}, /* index:326, gain:30.56250db -> x33.738444 */
    {0xf8, 0x02, 0x33}, /* index:327, gain:30.65625db -> x34.104562 */
    {0xf8, 0x02, 0x39}, /* index:328, gain:30.75000db -> x34.474663 */
    {0xf8, 0x02, 0x3f}, /* index:329, gain:30.84375db -> x34.848770 */
    {0xf8, 0x02, 0x45}, /* index:330, gain:30.93750db -> x35.226947 */
    {0xf8, 0x02, 0x4c}, /* index:331, gain:31.03125db -> x35.609227 */
    {0xf8, 0x02, 0x52}, /* index:332, gain:31.12500db -> x35.995646 */
    {0xf8, 0x02, 0x58}, /* index:333, gain:31.21875db -> x36.386269 */
    {0xf8, 0x02, 0x5f}, /* index:334, gain:31.31250db -> x36.781120 */
    {0xf8, 0x02, 0x66}, /* index:335, gain:31.40625db -> x37.180267 */
    {0xf8, 0x02, 0x6c}, /* index:336, gain:31.50000db -> x37.583745 */
    {0xf8, 0x02, 0x73}, /* index:337, gain:31.59375db -> x37.991591 */
    {0xf8, 0x02, 0x7a}, /* index:338, gain:31.68750db -> x38.403873 */
    {0xf8, 0x02, 0x81}, /* index:339, gain:31.78125db -> x38.820619 */
    {0xf8, 0x02, 0x88}, /* index:340, gain:31.87500db -> x39.241898 */
    {0xf8, 0x02, 0x8f}, /* index:341, gain:31.96875db -> x39.667748 */
    {0xf8, 0x02, 0x96}, /* index:342, gain:32.06250db -> x40.098209 */
    {0xf8, 0x02, 0x9d}, /* index:343, gain:32.15625db -> x40.533352 */
    {0xf8, 0x02, 0xa4}, /* index:344, gain:32.25000db -> x40.973206 */
    {0xf8, 0x02, 0xac}, /* index:345, gain:32.34375db -> x41.417845 */
    {0xf8, 0x02, 0xb3}, /* index:346, gain:32.43750db -> x41.867309 */
    {0xf8, 0x02, 0xba}, /* index:347, gain:32.53125db -> x42.321639 */
    {0xf8, 0x02, 0xc2}, /* index:348, gain:32.62500db -> x42.780911 */
    {0xf8, 0x02, 0xca}, /* index:349, gain:32.71875db -> x43.245154 */
    {0xf8, 0x02, 0xd1}, /* index:350, gain:32.81250db -> x43.714448 */
    {0xf8, 0x02, 0xd9}, /* index:351, gain:32.90625db -> x44.188835 */
    {0xf8, 0x02, 0xe1}, /* index:352, gain:33.00000db -> x44.668357 */
    {0xf8, 0x02, 0xe9}, /* index:353, gain:33.09375db -> x45.153095 */
    {0xf8, 0x02, 0xf1}, /* index:354, gain:33.18750db -> x45.643081 */
    {0xf8, 0x02, 0xfa}, /* index:355, gain:33.28125db -> x46.138397 */
    {0xf8, 0x03, 0x02}, /* index:356, gain:33.37500db -> x46.639088 */
    {0xf8, 0x03, 0x0a}, /* index:357, gain:33.46875db -> x47.145199 */
    {0xf8, 0x03, 0x13}, /* index:358, gain:33.56250db -> x47.656816 */
    {0xf8, 0x03, 0x1b}, /* index:359, gain:33.65625db -> x48.173972 */
    {0xf8, 0x03, 0x24}, /* index:360, gain:33.75000db -> x48.696753 */
    {0xf8, 0x03, 0x2d}, /* index:361, gain:33.84375db -> x49.225207 */
    {0xf8, 0x03, 0x35}, /* index:362, gain:33.93750db -> x49.759382 */
    {0xf8, 0x03, 0x3e}, /* index:363, gain:34.03125db -> x50.299367 */
    {0xf8, 0x03, 0x47}, /* index:364, gain:34.12500db -> x50.845199 */
    {0xf8, 0x03, 0x50}, /* index:365, gain:34.21875db -> x51.396968 */
    {0xf8, 0x03, 0x5a}, /* index:366, gain:34.31250db -> x51.954725 */
    {0xf8, 0x03, 0x63}, /* index:367, gain:34.40625db -> x52.518520 */
    {0xf8, 0x03, 0x6c}, /* index:368, gain:34.50000db -> x53.088447 */
    {0xf8, 0x03, 0x76}, /* index:369, gain:34.59375db -> x53.664545 */
    {0xf8, 0x03, 0x7f}, /* index:370, gain:34.68750db -> x54.246909 */
    {0xf8, 0x03, 0x89}, /* index:371, gain:34.78125db -> x54.835593 */
    {0xf8, 0x03, 0x93}, /* index:372, gain:34.87500db -> x55.430651 */
    {0xf8, 0x03, 0x9d}, /* index:373, gain:34.96875db -> x56.032181 */
    {0xf8, 0x03, 0xa7}, /* index:374, gain:35.06250db -> x56.640223 */
    {0xf8, 0x03, 0xb1}, /* index:375, gain:35.15625db -> x57.254879 */
    {0xf8, 0x03, 0xbb}, /* index:376, gain:35.25000db -> x57.876205 */
    {0xf8, 0x03, 0xc6}, /* index:377, gain:35.34375db -> x58.504258 */
    {0xf8, 0x03, 0xd0}, /* index:378, gain:35.43750db -> x59.139143 */
    {0xf8, 0x03, 0xdb}, /* index:379, gain:35.53125db -> x59.780900 */
    {0xf8, 0x03, 0xe6}, /* index:380, gain:35.62500db -> x60.429639 */
    {0xf8, 0x03, 0xf0}, /* index:381, gain:35.71875db -> x61.085418 */
    {0xf8, 0x03, 0xfb}, /* index:382, gain:35.81250db -> x61.748296 */
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
    /* num of lines = exposure time / (horizontal total pixeles / pixel clock) */
    uint64_t tmp = expo_time * (uint64_t)sensor->pix_clk;
    int num_line = NS_TO_SEC(tmp / sensor->total_win.width);        /* 16bit */

//    BL_LOGD("set_exposure: tmp %lld\r\n", tmp);
    BL_LOGD("\t\t set_exposure: num_line %d\r\n", num_line);

    if (num_line > sensor->total_win.height - 4)
        num_line = sensor->total_win.height - 4;

    SCCB_Write_Reg16(sensor->slv_addr, REG_LONG_EXPO_H, (num_line >> 12) & 0x0F);
    SCCB_Write_Reg16(sensor->slv_addr, REG_LONG_EXPO_M, (num_line >> 4) & 0xFF);
    SCCB_Write_Reg16(sensor->slv_addr, REG_LONG_EXPO_L, (num_line << 4) & 0xFF);

    return 0;
}

static int set_gain(sensor_t *sensor, BL_GAIN_DB gain)
{
    int index;
    uint8_t again, dgain_h, dgain_l;

    /* 6 dB range corresponds to 64 index range */
    index = GAIN_DB_TO_INT((gain << 6) / 6);

    again = OV9732_GAIN_TABLE[index][0];
    dgain_h = OV9732_GAIN_TABLE[index][1];
    dgain_l = OV9732_GAIN_TABLE[index][2];

    BL_LOGD("\t\t again 0x%02x, dgain_h 0x%02x, dgain_l 0x%02x\r\n", again, dgain_h, dgain_l);

    SCCB_Write_Reg16(sensor->slv_addr, REG_GAIN_LSB, again);

    SCCB_Write_Reg16(sensor->slv_addr, REG_R_GAIN_MSB, dgain_h);
    SCCB_Write_Reg16(sensor->slv_addr, REG_R_GAIN_LSB, dgain_l);
    SCCB_Write_Reg16(sensor->slv_addr, REG_G_GAIN_MSB, dgain_h);
    SCCB_Write_Reg16(sensor->slv_addr, REG_G_GAIN_LSB, dgain_l);
    SCCB_Write_Reg16(sensor->slv_addr, REG_B_GAIN_MSB, dgain_h);
    SCCB_Write_Reg16(sensor->slv_addr, REG_B_GAIN_LSB, dgain_l);

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
    FORMAT_INDEX format_index;

    switch (sensor->video_mode) {
	case VIDEO_MODE_720P_25:
        format_index = FORMAT_INDEX_720P_25;
		break;

	case VIDEO_MODE_720P_30:
        format_index = FORMAT_INDEX_720P_30;
		break;

	default:
		BL_LOGE("set_format error: invalid video mode!\r\n");
		return -1;
	}

    sensor->pix_clk = format_info[format_index].pix_clk;
    sensor->total_win.width = format_info[format_index].total_width;
    sensor->total_win.height = format_info[format_index].total_height;
    sensor->out_win.width = 1280;
    sensor->out_win.height = 720;

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
    int i;

    int mode_num = sizeof(ov9732_mode)/sizeof(ov9732_mode[0]);
    if (!is_sensor_dsp2_input_match(ov9732_mode, mode_num)) {
        return -1;
    }

    /* Initialize sensor structure */
    SENSOR_INIT_COMMON(OV9732);

    for (i = 0; i < sizeof(init_reglist)/sizeof(init_reglist[0]); i++) {
        SCCB_Write_Reg16(sensor->slv_addr, init_reglist[i].addr, (uint8_t)init_reglist[i].data);
        printf("reg 0x%04x = 0x%02x\r\n", init_reglist[i].addr, SCCB_Read_Reg16_Dbg(sensor->slv_addr, init_reglist[i].addr));
    }

    //set_format(sensor, VIDEO_MODE_720P_25);

    return 0;
}

const BL_SENSOR_DESC_T sensor_desc_ov9732 ATTR_SENSOR_DEVICE_TABLE =
{
	"OV9732",
    SLAVE_ADDR,
    probe,
    init,
    setFmt,
};

