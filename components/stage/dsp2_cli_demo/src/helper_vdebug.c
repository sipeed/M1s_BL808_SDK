/*
    TODO:
        1. Use function pointer to instead of strncmp
        2. Mode Encoder code to another tools
        3. Abstract Error Check function
        4. remove args: pcWriteBuffer, xWriteBufferLen
 */

#include <FreeRTOS.h>
//#include <FreeRTOS_CLI.h>
#include <task.h>

#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdarg.h>

#include <bl808.h>
#include <bl808_dsp2.h>
#include <bl_venc.h>
#include "helper_vdebug.h"
#include "ae_algo.h"
#include "awb_algo.h"
#include "bl_dsp2.h"
#include "sccb.h"
#include "sensor.h"

#include <cli.h>


#undef  DEBUG_MODULE
#define DEBUG_MODULE 0


#define VDEBUG_VALUE_SPLITTTER              ","
#define VDEBUG_PARAM_NUM                    7    /* include command itself*/

#define VDEBUG_PARAM_DOMAIN_DSP2             "-i"
#define VDEBUG_PARAM_DOMAIN_SENSOR          "-s"
#define VDEBUG_PARAM_DOMAIN_ADVANCED        "-a"
#define VDEBUG_PARAM_DOMAIN_PROTOCOL        "-p"
#define VDEBUG_PARAM_DOMAIN_HELP            "-h"


#define VDEBUG_PARAM_OPT_READ               "-r"
#define VDEBUG_PARAM_OPT_WRITE              "-w"

#define VDEBUG_PARAM_COM_ADDR               "--addr"
#define VDEBUG_PARAM_COM_GAIN               "--gain"

#define VDEBUG_PARAM_DSP2_BLC                "--blc"
#define VDEBUG_PARAM_DSP2_CCM                "--ccm"
#define VDEBUG_PARAM_DSP2_GAMMAON            "--gammaon"
#define VDEBUG_PARAM_DSP2_GAMMA              "--gamma"
#define VDEBUG_PARAM_DSP2_YUVMODE            "--yuvmode"
#define VDEBUG_PARAM_DSP2_BRIGHTNESS         "--brightness"
#define VDEBUG_PARAM_DSP2_CONTRAST           "--contrast"
#define VDEBUG_PARAM_DSP2_SATURATION         "--saturation"
#define VDEBUG_PARAM_DSP2_NOISE_LEVEL        "--noiselevel"
#define VDEBUG_PARAM_DSP2_2DNR               "--2dnr"
#define VDEBUG_PARAM_DSP2_3DNR               "--3dnr"
#define VDEBUG_PARAM_DSP2_EELEVEL            "--eelevel"
#define VDEBUG_PARAM_DSP2_EELIMIT            "--eelimit"
#define VDEBUG_PARAM_DSP2_EENOISETHRESHOLD   "--ee-noise-threshold"
#define VDEBUG_PARAM_DSP2_HPF                "--hpf"
#define VDEBUG_PARAM_DSP2_DPCMODE            "--dpcmode"
#define VDEBUG_PARAM_DSP2_DPCENHANCE         "--dpcenhance"
#define VDEBUG_PARAM_DSP2_DPCEHRESHOLD       "--dpcthreshold"
#define VDEBUG_PARAM_DSP2_LSCON              "--lscon"
#define VDEBUG_PARAM_DSP2_LSC                "--lsc"
#define VDEBUG_PARAM_DSP2_LSCMAX             "--lscmax"

#define VDEBUG_PARAM_DSP2_AEMODE             "--aemode"
#define VDEBUG_PARAM_DSP2_AETARGET           "--aetarget"
#define VDEBUG_PARAM_DSP2_AESPEED            "--aespeed"
#define VDEBUG_PARAM_DSP2_AELUMA             "--aeluma"
#define VDEBUG_PARAM_DSP2_AEMAXGAIN          "--aemaxgain"
#define VDEBUG_PARAM_DSP2_AWBMODE            "--awbmode"
#define VDEBUG_PARAM_DSP2_AWBTEMP            "--awbtemp"
#define VDEBUG_PARAM_DSP2_DN_MODE            "--dn-mode"

#define VDEBUG_PARAM_SENSOR_EXPOSURE        "--exposure"
#define VDEBUG_PARAM_SENSOR_MAXGAIN         "--maxgain"
#define VDEBUG_PARAM_SENSOR_RESOLUTION      "--resolution"

#define VDEBUG_PARAM_ADVANCED_SET_SNS_UID   "--sns-uid"
#define VDEBUG_PARAM_ADVANCED_SET_LOG_LVL   "--log-print"
#define VDEBUG_PARAM_ADVANCED_SYS_RST       "--reset"

#define VDEBUG_PARAM_PROTOCOL_SET           "--protocol-set"

#define VDEBUG_MAX(a, b) ((a) > (b)) ? (a): (b)

typedef enum {
    VDEBUG_OK_MSG = 0,
    VDEBUG_ERR_MSG,
} VDEBUG_MSG_TYPE;

typedef enum
{
    VDEBUG_ERR_SUCCCESS = 0,
    VDEBUG_ERR_INVALID_PARAM,
    VDEBUG_ERR_INVALID_NUM,
    VDEBUG_ERR_HELP,
}VDEBUG_ERR_NO;

typedef struct
{
    VDEBUG_ERR_NO no;
    char* msg;
}VDEBUG_ERR_INFO;

static const VDEBUG_ERR_INFO err_info_array[] =
{
    {VDEBUG_ERR_SUCCCESS,        ""},
    {VDEBUG_ERR_INVALID_PARAM,   "Invalid Param!"},
    {VDEBUG_ERR_INVALID_NUM,     "Invalid Input Value!"},
    {VDEBUG_ERR_HELP,    "Please enter 'vdebug -h' to see how to use!"},
};

static bool IS_DDR_MODE = false;

typedef enum
{
    VDEBUG_DSP2_REGISTER = 0,
    VDEBUG_ENCODER_REGISTER,
    VDEBUG_ADVANCED_REGISTER,
    VDEBUG_SENSOR_REGISTER
}VDEBUG_REGISTER_TYPE;

/*
    private protocol:
    VDEBUG_PRIVATE_PROTOCOL:ARG1,ARG2,ARG3...

 */
typedef enum
{
    VDEBUG_MODE_PRIVATE_DVP2BUS_EN,
    VDEBUG_MODE_PRIVATE_GLB_PORT,
    VDEBUG_MODE_PRIVATE_GLB_PORT_MODE,
    VDEBUG_MODE_PRIVATE_GLB_PORT_DB,
    VDEBUG_MODE_PRIVATE_GET_FPGA_TYPE,
}VDEBUG_PRIVATE_PROTOCOL;

const char* VDEBUG_HELP_MESSAGE_SHORT = "\r\n\r\nPlease enter 'vdebug -h' to see how to use vdebug.\r\n\r\n";

//const char* VDEBUG_HELP_MESSAGE_LONG = "\r\n";
const char* VDEBUG_HELP_MESSAGE_LONG =
"\r\nUsage: vdebug [DOMAIN][OPTION][FUNC][VALUE]\r\n\
\r\nDOMAIN:\r\n\
    -i: dsp2\r\n\
    -s: sensor\r\n\
    -e: encoder\r\n\
    -a: advanced\r\n\
    -h: help\r\n\
\r\nOPTION:\r\n\
    -r: read opertion\r\n\
    -w: write opertion\r\n\
\r\nFUNC(DSP2):\r\n\
    --addr:       Address operation\r\n\
        VALUE: [addr](value)\r\n\
    --blc:        Black level(r,gr,gb,b)\r\n\
        range:  0-1023, 1 normalize to 1\r\n\
        VALUE: (r,gr,gb,b)\r\n\
    --gain:       Gain(r,g,b)\r\n\
        range:  0-2047, 128 normalize to 1\r\n\
        VALUE: (r,g,b)\r\n\
    --ccm:        Color correction matrix\r\n\
        range:  -2048-2047, 512 normalize to 1\r\n\
        VALUE: (1,2,3,4,5,6,7,8,9)\r\n\
    --gammaon:  Gamma correction on/off\r\n\
        range:  0/1 , 0 means off, 1 means on\r\n\
        VALUE: (value)\r\n\
    --gamma:   (Deprecated) Gamma correction\r\n\
        range:  0-255, 1 normalize to 1\r\n\
        VALUE: (1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19)\r\n\
    --yuvmode:    RGB conversion YUV mode\r\n\
        range:  0/1 , 0 means full yuv, 1 means bt601\r\n\
        VALUE: (value)\r\n\
    --brightness: Brightness(Y)\r\n\
        range:  -128-127\r\n\
        VALUE: (value)\r\n\
    --contrast:  Contrast(Y)\r\n\
        range:  0-255, 128 normalize to 1\r\n\
        VALUE: (value)\r\n\
    --saturation: Saturation(cb, cr)\r\n\
        range:  0-255, 128 normalize to 1\r\n\
        VALUE: (cb,cr)\r\n\
    --aemode:     Auto exposure mode\r\n\
        range:  0-4, 0 means auto, 1 means lock, 2 means shutter priority\r\n\
            3 means gain priority, 4 means low speed.\r\n\
        VALUE: (value)\r\n\
    --aetarget:   Auto exposure target value\r\n\
        range:  0-255\r\n\
        VALUE: (value)\r\n\
    --aespeed:    Auto exposure change speed\r\n\
        range:  1-16\r\n\
        VALUE: (value)\r\n\
    --aeluma :    aeluma value\r\n\
        range:  0-255,\r\n\
        VALUE: (value)\r\n\
    --aemaxgain:  ae max gain (DB)\r\n\
       range:  0.0 -(sensor maxgain)\r\n\
         VALUE: (value)\r\n\
    --awbmode:     Auto wihte banlance mode\r\n\
        range:  0-7, 0 means auto, 1 means lock\r\n\
            2 - D65, 3 - D50, 4 - CWF, 5 - TL84, 6 - A light, 7 - H light.\r\n\
    --awbtemp:     Auto wihte banlance color temperature\r\n\
        range:  6500, 5000, 4150, 4000, 2856, 2300\r\n\
    --noiselevel: noise level\r\n\
        range:  0-63\r\n\
        VALUE: (value)\r\n\
    --2dnr: 2D noise reduction\r\n\
        range:  0-15\r\n\
        VALUE: (value)\r\n\
    --3dnr: 3D noise reduction\r\n\
        range:  0-15\r\n\
        VALUE: (value)\r\n\
    --eelevel: edge enhancement level\r\n\
        range:  0-127\r\n\
        VALUE: (value)\r\n\
    --eelimit: edge enhancement limit\r\n\
        range:  0-255\r\n\
        VALUE: (value)\r\n\
    --ee-noise-threshold: edge enhancement noise threshold\r\n\
        range:  0-127\r\n\
        VALUE: (value)\r\n\
    --hpf:     hpf rate\r\n\
        range:  0-8\r\n\
        VALUE: (value)\r\n\
    --dpcmode: dpc mode\r\n\
        range:  0-1, 0 means off, 1 means dynamic\r\n\
        VALUE: (value)\r\n\
    --dpcenhance: dpc enhance group\r\n\
        range:  0-1, 0 means off, 1 means on\r\n\
        VALUE: (1,1,1)\r\n\
    --dpcthreshold: dpc threshold group\r\n\
        range:  0-255\r\n\
        VALUE: (70,20,50,50,20)\r\n\
    --lscon: lsc on\r\n\
        range:  0-1, 0 means off, 1 means on\r\n\
        VALUE: (value)\r\n\
    --lsc:   lsc setting\r\n\
        range:  \r\n\
            A: -4194304-4194303\r\n\
            B: -4096-4095\r\n\
            C: 0-255\r\n\
            D: -4194304-4194303\r\n\
            E: -4096-4095\r\n\
            G: -4194304-4194303\r\n\
        VALUE: (R_A,R_B,R_C,R_D,R_E,R_G,G_A,G_B,G_C,G_D,G_E,G_G,B_A,B_B,B_C,B_D,B_E,B_G)\r\n\
    --lscmax: lsc max data\r\n\
        range:  0-255\r\n\
        VALUE: (70,20,50)\r\n\
    --shadow-highlight-mode: shadow highlight mode\r\n\
        range:  0-15, bit[0]: highlight mode, bit[1]:auto highlight\r\n\
               bit[2]: shadow mode, bit[3]:auto shadow\r\n\
        VALUE: (value)\r\n\
    --shadow-strength: shadow strength\r\n\
        range:  0-255\r\n\
        VALUE: (value)\r\n\
    --shadow-range: shadow range\r\n\
        range:  0-127\r\n\
        VALUE: (value)\r\n\
    --highlight-strength: highlight strength\r\n\
        range:  0-255\r\n\
        VALUE: (value)\r\n\
    --highlight-range: highlight range\r\n\
        range:  0-127\r\n\
        VALUE: (value)\r\n\
\r\nFUNC(SENSOR):\r\n\
    --addr:     Address operation\r\n\
        VALUE: [addr](value)\r\n\
    --gain:     Gain (DB)\r\n\
       range:  0.0 - (sensor maxgain)\r\n\
         VALUE: (value)\r\n\
    --maxgain:  max Gain (DB)\r\n\
       range:  sensor property\r\n\
    --exposure: Shutter Time\r\n\
       range:  1/6000-1/25\r\n\
         VALUE: (value)\r\n\
    --resolution: resolution\r\n\
       range:  NA\r\n\
         VALUE: (value)\r\n\
\r\nFUNC(ENCODER):\r\n\
    --addr:       Address operation\r\n\
        VALUE: [addr](value)\r\n\
\r\nFUNC(ADVANCED):\r\n\
    --workmode:  workmode\r\n\
       range:  0-3. 0 - sensor, 1 - raw 720p\r\n\
            2 - raw 1080p, 3 - sensor + MJPEG \r\n\
         VALUE: (value)\r\n\
    --hdmi: enable\r\n\
       range:  0-1. 0 - hdmi off, 1 - hdmi on.\r\n\
         VALUE: (value)\r\n\
    --autopop: enable\r\n\
       range:  0-1. 0 - manual, 1 - auto.\r\n\
    --sns-uid: id\r\n\
       range:  0-2. 0 - sc1245, 1 - sc2232, 2 - ov9732\r\n\
         VALUE: (value)\r\n\
    --log-print: id\r\n\
       range:  0-2. 0 - off, 1 - error, 2 - warning, 3 - info, 4 - debug\r\n\
         VALUE: (value)\r\n\
\r\nDSP2 EXAMPLE:\r\n\
    1. read dsp2 reg\r\n\
        vdebug -i -r --addr 0x4001800A\r\n\
    2. write dsp2 reg\r\n\
        vdebug -i -w --addr 0x40018156 2\r\n\
    3. read dsp2 blc\r\n\
        vdebug -i -r --blc\r\n\
    4. write dsp2 blc\r\n\
        vdebug -i -w --blc 20,20,20,20 \r\n\
    5. read dsp2 gain\r\n\
        vdebug -i -r --gain\r\n\
    6. write dsp2 gain\r\n\
        vdebug -i -w --gain 128,256,300 \r\n\
    7. read dsp2 ccm\r\n\
        vdebug -i -r --ccm\r\n\
    8. write dsp2 ccm\r\n\
        vdebug -i -w --ccm -100,-200,-512,100,200,300,512,512,512 \r\n\
    9. read dsp2 gammaon\r\n\
        vdebug -i -r --gammaon\r\n\
    10. write dsp2 gammaon\r\n\
        vdebug -i -w --gammaon 1 \r\n\
    11. read dsp2 gamma (Deprecated)  \r\n\
        vdebug -i -r --gamma\r\n\
    12. write dsp2 gamma (Deprecated) \r\n\
        vdebug -i -w --gamma  0,5,14,34,75,116,145,167,185,201,213,222,231,239,245,249,251,253,255 \r\n\
    13. read dsp2 yuvmode\r\n\
        vdebug -i -r --yuvmode\r\n\
    14. write dsp2 yuvmode\r\n\
        vdebug -i -w --yuvmode 0 \r\n\
    15. read dsp2 brightness\r\n\
        vdebug -i -r --brightness\r\n\
    16. write dsp2 brightness\r\n\
        vdebug -i -w --brightness 100 \r\n\
    17. read dsp2 contrast\r\n\
        vdebug -i -r --contrast\r\n\
    18. write dsp2 contrast\r\n\
        vdebug -i -w --contrast 100 \r\n\
    19. read dsp2 saturation\r\n\
        vdebug -i -r --saturation\r\n\
    20. write dsp2 saturation\r\n\
        vdebug -i -w --saturation 100,50 \r\n\
    21. write dsp2 ae mode\r\n\
        vdebug -i -w --aemode 0 \r\n\
    22. write dsp2 ae target\r\n\
        vdebug -i -w --aetarget 10 \r\n\
    23. read dsp2  ae target\r\n\
        vdebug -i -r --aetarget \r\n\
    24. read dsp2 ae luma\r\n\
        vdebug -i -r --aeluma  \r\n\
    25. write dsp2 awb mode\r\n\
        vdebug -i -w --awbmode 0 \r\n\
    26. read dsp2 2d noise reduction\r\n\
        vdebug -i -r --2dnr\r\n\
    27. write dsp2 2d noise reductio\r\n\
        vdebug -i -w --2dnr 15 \r\n\
    28. read dsp2 3d noise reduction\r\n\
        vdebug -i -r --3dnr\r\n\
    29. write dsp2 3d noise reductio\r\n\
        vdebug -i -w --3dnr 15 \r\n\
    30. read dsp2 edge enhancement level\r\n\
        vdebug -i -r --eelevel\r\n\
    31. write dsp2 edge enhancement level\r\n\
        vdebug -i -w --eelevel 75 \r\n\
    32. read edge enhancement limit\r\n\
        vdebug -i -r --eelimit\r\n\
    33. write edge enhancement limit\r\n\
        vdebug -i -w --eelimit 15 \r\n\
    34. read hpf rate\r\n\
        vdebug -i -r --hpf\r\n\
    35. write hpf rate 5\r\n\
        vdebug -i -w --hpf 5 \r\n\
    36. write ae max gain \r\n\
        vdebug -i -w --aemaxgain 20.0 \r\n\
    37. write dpc mode 1\r\n\
        vdebug -i -w --dpcmode 1 \r\n\
    38. read  dpc mode\r\n\
        vdebug -i -r --dpcmode\r\n\
    39. write dpc enhance group\r\n\
        vdebug -i -w --dpcenhance 1,1,1 \r\n\
    40. read dpc enhance group\r\n\
        vdebug -i -r --dpcenhance\r\n\
    41. write dpc threshold group\r\n\
        vdebug -i -w --dpcthreshold 70,20,50,50,20 \r\n\
    42. read dpcthreshold group\r\n\
        vdebug -i -r --dpcthreshold\r\n\
    43. write lsc mode 1\r\n\
        vdebug -i -w --lscon 1 \r\n\
    44. read  lsc mode\r\n\
        vdebug -i -r --lscon\r\n\
    45. write lsc setting\r\n\
        vdebug -i -w --lsc 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18 \r\n\
    46. read lsc setting\r\n\
        vdebug -i -r --lsc\r\n\
    47. write lsc max setting\r\n\
        vdebug -i -w --lscmax 1,2,3\r\n\
    48. read lsc max setting\r\n\
        vdebug -i -r --lscmax\r\n\
    49. read dsp2 shadow highlight mode\r\n\
        vdebug -i -r --shadow-highlight-mode\r\n\
    50. write dsp2 shadow highlight mode\r\n\
        vdebug -i -w --shadow-highlight-mode 7 \r\n\
    51. read dsp2 shadow strength\r\n\
        vdebug -i -r --shadow-strength\r\n\
    52. write dsp2 shadow strength\r\n\
        vdebug -i -w --shadow-strength 15 \r\n\
    53. read dsp2 shadow range\r\n\
        vdebug -i -r --shadow-range\r\n\
    54. write dsp2 shadow range\r\n\
        vdebug -i -w --shadow-range 15 \r\n\
    55. read dsp2 highlight strength\r\n\
        vdebug -i -r --highlight-strength\r\n\
    56. write dsp2 highlight strength\r\n\
        vdebug -i -w --highlight-strength 15 \r\n\
    57. read dsp2 highlight range\r\n\
        vdebug -i -r --highlight-range\r\n\
    58. write dsp2 highlight range\r\n\
        vdebug -i -w --highlight-range 15 \r\n\
    59. read dsp2 edge enhancement noise threshold\r\n\
        vdebug -i -r --ee-noise-threshold\r\n\
    60. write dsp2 edge enhancement noise threshold\r\n\
        vdebug -i -w --ee-noise-threshold 15 \r\n\
    61. read dsp2 noise level\r\n\
        vdebug -i -r --noiselevel\r\n\
    62. write dsp2 noise level\r\n\
        vdebug -i -w --noiselevel 15 \r\n\
    63. write dsp2 awb color temperature\r\n\
        vdebug -i -w --awbtemp 6500 \r\n\
    64. read dsp2 awb color temperature\r\n\
        vdebug -i -r --awbtemp \r\n\
\r\nSENSOR EXAMPLE:\r\n\
    1. write sensor addr\r\n\
        vdebug -s -w --addr 0x3101 0x1 \r\n\
    2. read sensor addr\r\n\
        vdebug -s -r --addr 0x3101 \r\n\
    3. write sensor exposure time\r\n\
        vdebug -s -w --exposure 1/25 \r\n\
    4. read sensor exposure time\r\n\
        vdebug -s -r --exposure  \r\n\
    5. write sensor gain\r\n\
        vdebug -s -w --gain 11.1 \r\n\
    6. read sensor gain\r\n\
        vdebug -s -r --gain  \r\n\
    7. read sensor max gain\r\n\
        vdebug -s -r --maxgain  \r\n\
    8. read sensor resolution\r\n\
        vdebug -s -r --resolution  \r\n\
\r\nENCODER EXAMPLE:\r\n\
    1. write encoder addr\r\n\
        vdebug -e -w --addr 0x4001900c 0x10\r\n\
    2. read encoder addr\r\n\
        vdebug -e -r --addr 0x4001900c \r\n\
    3. write encoder exposure time\r\n\
        vdebug -e -w --exposure 1/25 \r\n\
\r\nADVANCED EXAMPLE:\r\n\
    1. workmode\r\n\
        vdebug -a -w --workmode 1\r\n\
    2. hdmi on/off\r\n\
        vdebug -a -w --hdmi 1\r\n\
    3. autopop\r\n\
        vdebug -a -w --autopop 1\r\n\
    4. write 4byte addr\r\n\
        vdebug -a -w --addr 0x4000d040 0x12345678 \r\n\
    5. read 4byte addr\r\n\
        vdebug -a -r --addr 0x4000d040 \r\n\
";


static void vdebug_output(char *output, VDEBUG_MSG_TYPE msg, const char *format, ...)
{
    char tmp[configCOMMAND_INT_MAX_OUTPUT_SIZE];

    va_list args;
    va_start(args, format);

    vsnprintf(tmp, configCOMMAND_INT_MAX_OUTPUT_SIZE, format, args);
    if (VDEBUG_ERR_MSG == msg) {
        snprintf(output, configCOMMAND_INT_MAX_OUTPUT_SIZE, "[NG] %s\r\n", tmp);
    }
    else if (VDEBUG_OK_MSG == msg) {
        snprintf(output, configCOMMAND_INT_MAX_OUTPUT_SIZE, "[OK] %s\r\n", tmp);
    }
    else {
        BL_LOGE(" VDEBUG_MSG_TYPE not support now\r\n");
    }

    va_end(args);
}

static bool is_expect_value(char *pcWriteBuffer, int expect, int value, char* errmsg)
{
    if (expect != value) {
        vdebug_output(pcWriteBuffer, VDEBUG_ERR_MSG, "%s", errmsg);
        return false;
    }
    return true;
}

static uint32_t vdebug_long_str_pos = 0;
static BaseType_t VDEBUG_HELP_MESSAGE(char *pcWriteBuffer, size_t xWriteBufferLen)
{
    if (vdebug_long_str_pos < strlen(VDEBUG_HELP_MESSAGE_LONG)) {
        snprintf(pcWriteBuffer, xWriteBufferLen, "%s", &VDEBUG_HELP_MESSAGE_LONG[vdebug_long_str_pos]);
        vdebug_long_str_pos += strlen(pcWriteBuffer);
        return pdTRUE;
    }

    vdebug_long_str_pos = 0;
    return pdFALSE;
}

static BaseType_t vdebug_str_to_long(const char *str, uint32_t* val)
{
//    char *endptr = NULL;
    int err = 0;    /* To distinguish success/failure after call */

//    *val = (uint32_t)strtol(str, &endptr, 16);
    sscanf(str, "%x", val);

    /* Check for various possible errors */

    if ((err == ERANGE && (*val == LONG_MAX || *val == LONG_MIN))
           || (err != 0 && *val == 0)) {
        BL_LOGE("errno is %d, *val = %u !\r\n", err, *val);

        BL_LOGE("error: parameter error!\r\n");
        return pdFALSE;
    }

//    if (endptr == str) {
//        BL_LOGE("error: parameter error!\r\n");
//        return pdFALSE;
//    }

    BL_LOGD("debug: vdebug_str_to_long is 0x%x\r\n", *val);
    return pdTRUE;
}

static void vdebug_com_readreg(char *pcWriteBuffer, const char* addr_str, VDEBUG_REGISTER_TYPE type)
{
    uint32_t addr;
    uint8_t value;
    /* check if the param is valid*/
    if (!vdebug_str_to_long(addr_str, &addr)) {
        vdebug_output(pcWriteBuffer, VDEBUG_ERR_MSG, "%s", err_info_array[VDEBUG_ERR_INVALID_PARAM].msg);
        return;
    }

    switch (type) {
        case VDEBUG_DSP2_REGISTER: {
            uint32_t tmp = *((uint32_t*)addr);
            vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "0x%08x", tmp);
            BL_LOGD("debug: output is 0x%x 0x%x\n", addr, tmp);
            break;
        }
        case VDEBUG_ENCODER_REGISTER: {
            uint32_t tmp = *((uint32_t*)addr);
            vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "0x%08x", tmp);
            BL_LOGD("debug: output is 0x%x 0x%x\n", addr, tmp);
            break;
        }
        case VDEBUG_ADVANCED_REGISTER: {
            uint32_t tmp = *((uint32_t*)addr);
            vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "0x%08x", tmp);
            BL_LOGD("debug: output is 0x%x 0x%x\n", addr, tmp);
            break;
        }
        case VDEBUG_SENSOR_REGISTER: {
            uint8_t sl_addr = sensor_get_slv_addr();

            if ((addr >> 8) == 0) {
                value = SCCB_Read_Dbg(sl_addr, (uint8_t)addr);
            } else {
                value = SCCB_Read_Reg16_Dbg(sl_addr, (uint16_t)addr);
            }

            vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "0x%04x", value);
            BL_LOGD("debug:slave addr is 0x%02x, addr is 0x%04x, value is 0x%02x\r\n",sl_addr, (uint16_t)addr, value);
            break;
        }
        default: {
        }
    }
}


static void vdebug_com_writereg(char *pcWriteBuffer, const char* addr_str, const char* value_str, VDEBUG_REGISTER_TYPE type)
{
	uint32_t addr, value;
    /* check if the param is valid*/
    if (!vdebug_str_to_long(addr_str, &addr) || !vdebug_str_to_long(value_str, &value)) {
        vdebug_output(pcWriteBuffer, VDEBUG_ERR_MSG, "%s", err_info_array[VDEBUG_ERR_INVALID_PARAM].msg);
        return;
    }

    switch (type) {
        case VDEBUG_DSP2_REGISTER: {
            *((uint32_t*)addr) = (uint32_t)value;
            BL_LOGD("debug: addr is 0x%x, value is 0x%x\r\n", (uint32_t)addr, (uint32_t)value);
            break;
        }
        case VDEBUG_ENCODER_REGISTER: {
            *((uint32_t*)addr) = (uint32_t)value;
            BL_LOGD("debug: addr is 0x%x, value is 0x%x\r\n", (uint32_t)addr, (uint32_t)value);
            break;
        }
        case VDEBUG_ADVANCED_REGISTER: {
            *((uint32_t*)addr) = (uint32_t)value;
            BL_LOGD("debug: addr is 0x%x, value is 0x%x\r\n", (uint32_t)addr, (uint32_t)value);
            break;
        }
        case VDEBUG_SENSOR_REGISTER: {
            uint8_t sl_addr = sensor_get_slv_addr();

            if ((addr >> 8) == 0) {
                SCCB_Write(sl_addr, (uint8_t)addr, (uint8_t)value);
            } else {
                SCCB_Write_Reg16(sl_addr, (uint16_t)addr, (uint8_t)value);
            }

            BL_LOGD("debug:slave addr is 0x%02x, addr is 0x%04x, value is 0x%02x\r\n", sl_addr, (uint16_t)addr, (uint8_t)value);
            break;
        }
        default: {
            break;
        }
    }
    vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "%s", err_info_array[VDEBUG_ERR_SUCCCESS].msg);
}

static void vdebug_dsp2_get_blc(char *pcWriteBuffer)
{
    int ret = 0;
    DSP2_CLAMP_S clamp;

    ret = DSP2_Get_BLC(&clamp);

    if (!is_expect_value(pcWriteBuffer, 0, ret, err_info_array[VDEBUG_ERR_INVALID_PARAM].msg)) return;

    vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "%d,%d,%d,%d", clamp.clamp_r, clamp.clamp_gr, clamp.clamp_gb, clamp.clamp_b);
}

static void vdebug_dsp2_set_blc(char *pcWriteBuffer, char* value_str)
{
    DSP2_CLAMP_S clamp;
    int ret = sscanf(value_str, "%d,%d,%d,%d", &clamp.clamp_r, &clamp.clamp_gr, &clamp.clamp_gb, &clamp.clamp_b);

    if (!is_expect_value(pcWriteBuffer, 4, ret, err_info_array[VDEBUG_ERR_INVALID_NUM].msg)) return;

    ret = DSP2_Set_BLC(&clamp);

    if (!is_expect_value(pcWriteBuffer, 0, ret, err_info_array[VDEBUG_ERR_INVALID_PARAM].msg)) return;

    vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "%s", err_info_array[VDEBUG_ERR_SUCCCESS].msg);
}

static void vdebug_dsp2_get_gain(char *pcWriteBuffer)
{
    DSP2_RGB_Gain_Type rgb_gain;

    DSP2_Get_AWB_Gain(&rgb_gain);

    vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "%d,%d,%d", rgb_gain.r_gain, rgb_gain.g_gain, rgb_gain.b_gain);
}

static void vdebug_dsp2_set_gain(char *pcWriteBuffer, char* value_str)
{
    DSP2_RGB_Gain_Type rgb_gain;
    int value[3] = {0};
    int ret = sscanf(value_str, "%d,%d,%d", &value[0], &value[1], &value[2]);

    if (!is_expect_value(pcWriteBuffer, 3, ret, err_info_array[VDEBUG_ERR_INVALID_NUM].msg)) return;

    rgb_gain.r_gain = value[0];
    rgb_gain.g_gain = value[1];
    rgb_gain.b_gain = value[2];
    ret = awb_set_gain(&rgb_gain);

    if (!is_expect_value(pcWriteBuffer, 0, ret, err_info_array[VDEBUG_ERR_INVALID_PARAM].msg)) return;

    vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "%s", err_info_array[VDEBUG_ERR_SUCCCESS].msg);
}

static void vdebug_dsp2_get_ccm(char *pcWriteBuffer)
{
    DSP2_CCM_COEF_S ccm;
    DSP2_Get_CCM_Coef(&ccm);

    vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "%d,%d,%d,%d,%d,%d,%d,%d,%d",
        ccm.ccm_coef[DSP2_CCM_11], ccm.ccm_coef[DSP2_CCM_12], ccm.ccm_coef[DSP2_CCM_13],
        ccm.ccm_coef[DSP2_CCM_21], ccm.ccm_coef[DSP2_CCM_22], ccm.ccm_coef[DSP2_CCM_23],
        ccm.ccm_coef[DSP2_CCM_31], ccm.ccm_coef[DSP2_CCM_32], ccm.ccm_coef[DSP2_CCM_33]);
}

static void vdebug_dsp2_set_ccm(char *pcWriteBuffer, char* value_str)
{
    DSP2_CCM_COEF_S ccm;
    int ret = sscanf(value_str, "%d,%d,%d,%d,%d,%d,%d,%d,%d",
        &ccm.ccm_coef[DSP2_CCM_11], &ccm.ccm_coef[DSP2_CCM_12], &ccm.ccm_coef[DSP2_CCM_13],
        &ccm.ccm_coef[DSP2_CCM_21], &ccm.ccm_coef[DSP2_CCM_22], &ccm.ccm_coef[DSP2_CCM_23],
        &ccm.ccm_coef[DSP2_CCM_31], &ccm.ccm_coef[DSP2_CCM_32], &ccm.ccm_coef[DSP2_CCM_33]);
    if (!is_expect_value(pcWriteBuffer, 9, ret, err_info_array[VDEBUG_ERR_INVALID_NUM].msg)) return;

    for (int i = 0; i < CCM_COEF_NUM; i++) {
        BL_LOGD("group.data[i] is %d \r\n", ccm.ccm_coef[i]);
    }

    DSP2_Set_CCM_Coef(&ccm);

    vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "%s", err_info_array[VDEBUG_ERR_SUCCCESS].msg);
}

static void vdebug_dsp2_get_gammaon(char *pcWriteBuffer)
{
    BL_Fun_Type value;
    DSP2_Get_Gamma_State(&value);

    vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "%d", (int)value);
}

static void vdebug_dsp2_set_gammaon(char *pcWriteBuffer, char* value_str)
{
    int value;
    int ret = sscanf(value_str, "%d", &value);
    if (!is_expect_value(pcWriteBuffer, 1, ret, err_info_array[VDEBUG_ERR_INVALID_NUM].msg)) return;

    DSP2_Set_Gamma_State((BL_Fun_Type)value);

    vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "%s", err_info_array[VDEBUG_ERR_SUCCCESS].msg);
}

static void vdebug_dsp2_get_gamma(char* pcWriteBuffer)
{
#if 0
    DSP2_Gamma_Curve_Type gamma;
    DSP2_Get_Gamma_Coef(&gamma);

    vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, \
"\
%d,%d,%d,%d,%d,%d,\
%d,%d,%d,%d,%d,%d,\
%d,%d,%d,%d,%d,%d,\
%d",\
        gamma.curve_coef[0], gamma.curve_coef[1], gamma.curve_coef[2], gamma.curve_coef[3],
        gamma.curve_coef[4], gamma.curve_coef[5], gamma.curve_coef[6], gamma.curve_coef[7],
        gamma.curve_coef[8], gamma.curve_coef[9], gamma.curve_coef[10], gamma.curve_coef[11],
        gamma.curve_coef[12], gamma.curve_coef[13], gamma.curve_coef[14], gamma.curve_coef[15],
        gamma.curve_coef[16], gamma.curve_coef[17], gamma.curve_coef[18]);
#endif
    printf("not support now!\n");
}

static void vdebug_dsp2_set_gamma(char *pcWriteBuffer, char* value_str)
{
#if 0
    DSP2_Gamma_Curve_Type gamma;
    int ret = sscanf(value_str,
"\
%d,%d,%d,%d,%d,%d,\
%d,%d,%d,%d,%d,%d,\
%d,%d,%d,%d,%d,%d,\
%d",\
        (int *)&gamma.curve_coef[0], (int *)&gamma.curve_coef[1], (int *)&gamma.curve_coef[2], (int *)&gamma.curve_coef[3],
        (int *)&gamma.curve_coef[4], (int *)&gamma.curve_coef[5], (int *)&gamma.curve_coef[6], (int *)&gamma.curve_coef[7],
        (int *)&gamma.curve_coef[8], (int *)&gamma.curve_coef[9], (int *)&gamma.curve_coef[10], (int *)&gamma.curve_coef[11],
        (int *)&gamma.curve_coef[12], (int *)&gamma.curve_coef[13], (int *)&gamma.curve_coef[14], (int *)&gamma.curve_coef[15],
        (int *)&gamma.curve_coef[16], (int *)&gamma.curve_coef[17], (int *)&gamma.curve_coef[18]);

    if (!is_expect_value(pcWriteBuffer, 19, ret, err_info_array[VDEBUG_ERR_INVALID_NUM].msg)) return;

    for (int i = 0; i < 19; i++) {
        BL_LOGD("group.data[i] is %d \r\n", gamma.curve_coef[i]);
    }

    DSP2_Set_Gamma_Coef(&gamma);
#endif
    printf("not support now!\n");
    vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "%s", err_info_array[VDEBUG_ERR_SUCCCESS].msg);
}

static void vdebug_dsp2_get_yuvmode(char* pcWriteBuffer)
{
    DSP2_YUV_CONV_TYPE value;
    DSP2_Get_YUV_Conv_Mode(&value);

    // TODO, return BT601, Full YUV
    vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "%d", value);
}

static void vdebug_dsp2_set_yuvmode(char *pcWriteBuffer, char* value_str)
{
    int value;

    int ret = sscanf(value_str, "%d", &value);
    if (!is_expect_value(pcWriteBuffer, 1, ret, err_info_array[VDEBUG_ERR_INVALID_NUM].msg)) return;

    DSP2_Set_YUV_Conv_Mode((DSP2_YUV_CONV_TYPE)value);

    vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "%s", err_info_array[VDEBUG_ERR_SUCCCESS].msg);
}

static void vdebug_dsp2_get_brightness(char* pcWriteBuffer)
{
    int value = 0;
    DSP2_Get_Brightness(&value);
    vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "%d", value);
}

static void vdebug_dsp2_set_brightness(char *pcWriteBuffer, char* value_str)
{
    int value;
    int ret = sscanf(value_str, "%d", &value);
    if (!is_expect_value(pcWriteBuffer, 1, ret, err_info_array[VDEBUG_ERR_INVALID_NUM].msg)) return;

    DSP2_Set_Brightness(value);

    vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "%s", err_info_array[VDEBUG_ERR_SUCCCESS].msg);
}

static void vdebug_dsp2_get_contrast(char* pcWriteBuffer)
{
    int value = 0;
    DSP2_Get_Contrast(&value);
    vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "%d", value);
}

static void vdebug_dsp2_set_contrast(char *pcWriteBuffer, char* value_str)
{
    int value;
    int ret = sscanf(value_str, "%d", &value);
    if (!is_expect_value(pcWriteBuffer, 1, ret, err_info_array[VDEBUG_ERR_INVALID_NUM].msg)) return;

    DSP2_Set_Contrast(value);

    vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "%s", err_info_array[VDEBUG_ERR_SUCCCESS].msg);
}

static void vdebug_dsp2_get_saturation(char* pcWriteBuffer)
{
    DSP2_SATURATION_S saturation;
    DSP2_Get_Saturation(&saturation);

    vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "%d,%d", saturation.saturation_cb, saturation.saturation_cr);
}


static void vdebug_dsp2_set_saturation(char *pcWriteBuffer, char* value_str)
{
    DSP2_SATURATION_S saturation;
    int ret = sscanf(value_str, "%d,%d", &saturation.saturation_cb, &saturation.saturation_cr);
    if (!is_expect_value(pcWriteBuffer, 2, ret, err_info_array[VDEBUG_ERR_INVALID_NUM].msg)) return;

    DSP2_Set_Saturation(&saturation);

    vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "%s", err_info_array[VDEBUG_ERR_SUCCCESS].msg);
}

static void vdebug_dsp2_set_aemode(char *pcWriteBuffer, char* value_str)
{
    int value;
    int ret = sscanf(value_str, "%d", &value);
    if (!is_expect_value(pcWriteBuffer, 1, ret, err_info_array[VDEBUG_ERR_INVALID_NUM].msg)) return;

    ret = ae_set_mode((AE_MODE)value);
    if (!is_expect_value(pcWriteBuffer, 0, ret, err_info_array[VDEBUG_ERR_INVALID_PARAM].msg)) return;

    vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "%s", err_info_array[VDEBUG_ERR_SUCCCESS].msg);
}

static void vdebug_dsp2_get_aetarget(char *pcWriteBuffer)
{
    int value;
    ae_get_luma_target(&value);
    vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "%d", value);
}

static void vdebug_dsp2_get_aeluma(char *pcWriteBuffer)
{
    int value = ae_get_luma();
    vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "%d", value);
}

static void vdebug_dsp2_set_aetarget(char *pcWriteBuffer, char* value_str)
{
    int value;
    int ret = sscanf(value_str, "%d", &value);
    if (!is_expect_value(pcWriteBuffer, 1, ret, err_info_array[VDEBUG_ERR_INVALID_NUM].msg)) return;

    ret = ae_set_luma_target(value);
    if (!is_expect_value(pcWriteBuffer, 0, ret, err_info_array[VDEBUG_ERR_INVALID_PARAM].msg)) return;

    vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "%s", err_info_array[VDEBUG_ERR_SUCCCESS].msg);
}

static void vdebug_dsp2_set_aespeed(char *pcWriteBuffer, char* value_str)
{
    int value;
    int ret = sscanf(value_str, "%d", &value);
    if (!is_expect_value(pcWriteBuffer, 1, ret, err_info_array[VDEBUG_ERR_INVALID_NUM].msg)) return;

    ret = ae_set_speed(value);
    if (!is_expect_value(pcWriteBuffer, 0, ret, err_info_array[VDEBUG_ERR_INVALID_PARAM].msg)) return;

    vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "%s", err_info_array[VDEBUG_ERR_SUCCCESS].msg);
}

static void vdebug_dsp2_set_gain_upper_limit(char *pcWriteBuffer, char* value_str)
{
    float value;
    int ret = sscanf(value_str, "%f", &value);
    if (!is_expect_value(pcWriteBuffer, 1, ret, err_info_array[VDEBUG_ERR_INVALID_NUM].msg)) return;

    ret = ae_set_gain_max(value);
    if (!is_expect_value(pcWriteBuffer, 0, ret, err_info_array[VDEBUG_ERR_INVALID_PARAM].msg)) return;

    vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "%s", err_info_array[VDEBUG_ERR_SUCCCESS].msg);
}

static void vdebug_dsp2_set_awbmode(char *pcWriteBuffer, char* value_str)
{
    int value;
    int ret = sscanf(value_str, "%d", &value);
    if (!is_expect_value(pcWriteBuffer, 1, ret, err_info_array[VDEBUG_ERR_INVALID_NUM].msg)) return;

    ret = awb_set_mode((AWB_MODE)value);
    if (!is_expect_value(pcWriteBuffer, 0, ret, err_info_array[VDEBUG_ERR_INVALID_PARAM].msg)) return;

    vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "%s", err_info_array[VDEBUG_ERR_SUCCCESS].msg);
}

static void vdebug_dsp2_get_awbmode(char *pcWriteBuffer)
{
    AWB_MODE value = 0;
    awb_get_mode(&value);
    vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "%d", value);
}

static void vdebug_dsp2_set_awbtemp(char *pcWriteBuffer, char* value_str)
{
    int value;
    int ret = sscanf(value_str, "%d", &value);
    if (!is_expect_value(pcWriteBuffer, 1, ret, err_info_array[VDEBUG_ERR_INVALID_NUM].msg)) return;

    ret = awb_set_color_temp((BL_COLOR_TEMP)value);
    if (!is_expect_value(pcWriteBuffer, 0, ret, err_info_array[VDEBUG_ERR_INVALID_PARAM].msg)) return;

    vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "%s", err_info_array[VDEBUG_ERR_SUCCCESS].msg);
}

static void vdebug_dsp2_get_awbtemp(char *pcWriteBuffer)
{
    int value = 0;
    awb_get_color_temp(&value);
    vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "%d", value);
}

static void vdebug_dsp2_get_noiselevel(char *pcWriteBuffer)
{
    int value = 0;
    DSP2_Get_Noise_Level(&value);
    vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "%d", value);
}

static void vdebug_dsp2_set_noiselevel(char *pcWriteBuffer, char* value_str)
{
    int value;
    int ret = sscanf(value_str, "%d", &value);
    if (!is_expect_value(pcWriteBuffer, 1, ret, err_info_array[VDEBUG_ERR_INVALID_NUM].msg)) return;

    DSP2_Set_Noise_Level(value);
    vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "%s", err_info_array[VDEBUG_ERR_SUCCCESS].msg);
}

static void vdebug_dsp2_get_2dnr(char *pcWriteBuffer)
{
    int value = 0;
    DSP2_Get_2D_NR(&value);
    vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "%d", value);
}

static void vdebug_dsp2_set_2dnr(char *pcWriteBuffer, char* value_str)
{
    int value;
    int ret = sscanf(value_str, "%d", &value);
    if (!is_expect_value(pcWriteBuffer, 1, ret, err_info_array[VDEBUG_ERR_INVALID_NUM].msg)) return;

    DSP2_Set_2D_NR(value);
    vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "%s", err_info_array[VDEBUG_ERR_SUCCCESS].msg);
}

static void vdebug_dsp2_get_3dnr(char *pcWriteBuffer)
{
    int value = 0;
    DSP2_Get_3D_NR(&value);
    vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "%d", value);
}

static void vdebug_dsp2_set_3dnr(char *pcWriteBuffer, char* value_str)
{
    int value;
    int ret = sscanf(value_str, "%d", &value);
    if (!is_expect_value(pcWriteBuffer, 1, ret, err_info_array[VDEBUG_ERR_INVALID_NUM].msg)) return;

    DSP2_Set_3D_NR(value);
    vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "%s", err_info_array[VDEBUG_ERR_SUCCCESS].msg);
}

static void vdebug_dsp2_set_dpcmode(char *pcWriteBuffer, char* value_str)
{
    int value;
    int ret = sscanf(value_str, "%d", &value);
    if (!is_expect_value(pcWriteBuffer, 1, ret, err_info_array[VDEBUG_ERR_INVALID_NUM].msg)) return;

    if (value) {
        DSP2_Enable_DPC();
    } else {
        DSP2_Disable_DPC();
    }

    vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "%s", err_info_array[VDEBUG_ERR_SUCCCESS].msg);
}

static void vdebug_dsp2_get_dpcenhance(char *pcWriteBuffer)
{
    DSP2_DPC_ENHANCE_GROUP_TYPE group;
    DSP2_Get_Defect_Correction_Enhance_Group(&group);

    vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "%d,%d,%d",
        (group.data)[0], (group.data)[1], (group.data)[2]);
}

static void vdebug_dsp2_set_dpcenhance(char *pcWriteBuffer, char* value_str)
{
    DSP2_DPC_ENHANCE_GROUP_TYPE group;
    int value[3] = {0};
    int ret = sscanf(value_str, "%d,%d,%d", &value[0], &value[1], &value[2]);
    if (!is_expect_value(pcWriteBuffer, 3, ret, err_info_array[VDEBUG_ERR_INVALID_NUM].msg)) return;

    for (int i = 0; i < 3; i++) {
        BL_LOGD("value[i] is %d, group.data[i] is %d \r\n", (int16_t)value[i], group.data[i]);
        group.data[i] = (BL_Fun_Type)(value[i]);
    }

    ret = DSP2_Set_Defect_Correction_Enhance_Group(&group);

    if (!is_expect_value(pcWriteBuffer, 0, ret, err_info_array[VDEBUG_ERR_INVALID_PARAM].msg)) return;

    vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "%s", err_info_array[VDEBUG_ERR_SUCCCESS].msg);
}

static void vdebug_dsp2_get_dpcthreshold(char *pcWriteBuffer)
{
    DSP2_DPC_THRESHOLD_GROUP_TYPE group;
    DSP2_Get_Defect_Correction_Threshold_Group(&group);

    vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "%d,%d,%d,%d,%d",
        (group.data)[0], (group.data)[1], (group.data)[2], (group.data)[3], (group.data)[4]);
}

static void vdebug_dsp2_set_dpcthreshold(char *pcWriteBuffer, char* value_str)
{
    DSP2_DPC_THRESHOLD_GROUP_TYPE group;
    int value[5] = {0};
    int ret = sscanf(value_str, "%d,%d,%d,%d,%d",
        &value[0], &value[1], &value[2], &value[3], &value[4]);
    if (!is_expect_value(pcWriteBuffer, 5, ret, err_info_array[VDEBUG_ERR_INVALID_NUM].msg)) return;

    for (int i = 0; i < 5; i++) {
        BL_LOGD("(int16_t)value[i] is %d, group.data[i] is %d \r\n", (int16_t)value[i], group.data[i]);
        group.data[i] = value[i];
    }

    ret = DSP2_Set_Defect_Correction_Threshold_Group(&group);
    if (!is_expect_value(pcWriteBuffer, 0, ret, err_info_array[VDEBUG_ERR_INVALID_PARAM].msg)) return;

    vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "%s", err_info_array[VDEBUG_ERR_SUCCCESS].msg);
}

static void vdebug_dsp2_set_lscon(char *pcWriteBuffer, char* value_str)
{
    int value;
    int ret = sscanf(value_str, "%d", &value);
    if (!is_expect_value(pcWriteBuffer, 1, ret, err_info_array[VDEBUG_ERR_INVALID_NUM].msg)) return;

    if (value) {
        DSP2_Enable_LSC();
    } else {
        DSP2_Disable_LSC();
    }

    vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "%s", err_info_array[VDEBUG_ERR_SUCCCESS].msg);
}

static void vdebug_dsp2_get_lscon(char *pcWriteBuffer)
{
    BL_Fun_Type value;
    DSP2_Get_LSC_State(&value);
    vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "%d", (int)value);
}

static void vdebug_dsp2_get_lsc(char *pcWriteBuffer)
{
    DSP2_LSC_COEF_S lsc;
    DSP2_Get_LSC_Coeff(&lsc);

    vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, \
"\
%d,%d,%d,%d,%d,%d,\
%d,%d,%d,%d,%d,%d,\
%d,%d,%d,%d,%d,%d",\
lsc.lsc_coef_r.coef[0], lsc.lsc_coef_r.coef[1], lsc.lsc_coef_r.coef[2], lsc.lsc_coef_r.coef[3], lsc.lsc_coef_r.coef[4], lsc.lsc_coef_r.coef[5],\
lsc.lsc_coef_g.coef[0], lsc.lsc_coef_g.coef[1], lsc.lsc_coef_g.coef[2], lsc.lsc_coef_g.coef[3], lsc.lsc_coef_g.coef[4], lsc.lsc_coef_g.coef[5],\
lsc.lsc_coef_b.coef[0], lsc.lsc_coef_b.coef[1], lsc.lsc_coef_b.coef[2], lsc.lsc_coef_b.coef[3], lsc.lsc_coef_b.coef[4], lsc.lsc_coef_b.coef[5]);
}

static void vdebug_dsp2_set_lsc(char *pcWriteBuffer, char* value_str)
{
    DSP2_LSC_COEF_S lsc;
    int value[18] = {0};
    int ret = sscanf(value_str,
"\
%d,%d,%d,%d,%d,%d,\
%d,%d,%d,%d,%d,%d,\
%d,%d,%d,%d,%d,%d",\
&value[0], &value[1], &value[2], &value[3], &value[4], &value[5],\
&value[6], &value[7], &value[8], &value[9], &value[10], &value[11],\
&value[12], &value[13], &value[14], &value[15], &value[16], &value[17]);
    if (!is_expect_value(pcWriteBuffer, 18, ret, err_info_array[VDEBUG_ERR_INVALID_NUM].msg)) return;

    for (int i = 0; i < LSC_COEF_NUM; i++) {
       lsc.lsc_coef_r.coef[i] = value[i];
       lsc.lsc_coef_g.coef[i] = value[i + 6];
       lsc.lsc_coef_b.coef[i] = value[i + 12];
    }

    ret = DSP2_Set_LSC_Coeff(&lsc);
    if (!is_expect_value(pcWriteBuffer, 0, ret, err_info_array[VDEBUG_ERR_INVALID_PARAM].msg)) return;

    vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "%s", err_info_array[VDEBUG_ERR_SUCCCESS].msg);
}

static void vdebug_dsp2_get_lscmax(char *pcWriteBuffer)
{
    DSP2_LSC_MAX_S lsc_max;
    DSP2_Get_LSC_Max(&lsc_max);

    vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "%d,%d,%d", lsc_max.max_r, lsc_max.max_g, lsc_max.max_b);
}

static void vdebug_dsp2_set_lscmax(char *pcWriteBuffer, char* value_str)
{
    DSP2_LSC_MAX_S lsc_max;
    int ret = sscanf(value_str, "%d,%d,%d", &lsc_max.max_r, &lsc_max.max_g, &lsc_max.max_b);
    if (!is_expect_value(pcWriteBuffer, 3, ret, err_info_array[VDEBUG_ERR_INVALID_NUM].msg)) return;

    ret = DSP2_Set_LSC_Max(&lsc_max);
    if (!is_expect_value(pcWriteBuffer, 0, ret, err_info_array[VDEBUG_ERR_INVALID_PARAM].msg)) return;

    vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "%s", err_info_array[VDEBUG_ERR_SUCCCESS].msg);
}

/*sensor func*/
static void vdebug_sensor_get_gain(char *pcWriteBuffer)
{
    if (IS_DDR_MODE) {
        vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "NULL");
        return;
    }

    float value;
    ae_get_sensor_gain(&value);
    vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "%.4f", value);
}

static void vdebug_sensor_set_gain(char *pcWriteBuffer, char* value_str)
{
    float value;
    int ret = sscanf(value_str, "%f", &value);
    if (!is_expect_value(pcWriteBuffer, 1, ret, err_info_array[VDEBUG_ERR_INVALID_NUM].msg)) return;

    ret = ae_set_sensor_gain(value);
    if (!is_expect_value(pcWriteBuffer, 0, ret, err_info_array[VDEBUG_ERR_INVALID_PARAM].msg)) return;

    vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "%s", err_info_array[VDEBUG_ERR_SUCCCESS].msg);
}

static void vdebug_sensor_get_exposure(char *pcWriteBuffer)
{
    if (IS_DDR_MODE) {
        vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "NULL");
        return;
    }

    BL_EXPO_TIME value;
    ae_get_sensor_exposure(&value);

    vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "1/%d", INT_TO_EXPO_TIME(value));
}

static void vdebug_sensor_set_exposure(char *pcWriteBuffer, char* value_str)
{
    int value;
    int ret = sscanf(value_str, "1/%d", &value);
    if (!is_expect_value(pcWriteBuffer, 1, ret, err_info_array[VDEBUG_ERR_INVALID_NUM].msg)) return;

    ret = ae_set_sensor_exposure(EXPO_TIME_TO_INT(value));
    if (!is_expect_value(pcWriteBuffer, 0, ret, err_info_array[VDEBUG_ERR_INVALID_PARAM].msg)) return;

    vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "%s", err_info_array[VDEBUG_ERR_SUCCCESS].msg);
}

static void vdebug_sensor_get_maxgain(char *pcWriteBuffer)
{
    float value;
    ae_get_sensor_gain_max(&value);
    vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "%.4f", value);
}

static void vdebug_advanced_set_log_level(char *pcWriteBuffer, char* value_str)
{
    int value;
    int ret = sscanf(value_str, "%d", &value);
    if (!is_expect_value(pcWriteBuffer, 1, ret, err_info_array[VDEBUG_ERR_INVALID_NUM].msg)) return;

    ret = BL_DBG_ChgLogPrintLevel((BL_LOGTYPE)value);

    if (!is_expect_value(pcWriteBuffer, 0, ret, err_info_array[VDEBUG_ERR_INVALID_PARAM].msg)) return;

    vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "%s", err_info_array[VDEBUG_ERR_SUCCCESS].msg);
}

static void vdebug_advanced_system_reset(char *pcWriteBuffer, char* value_str)
{
    int value;
    int ret = sscanf(value_str, "%d", &value);
    if (!is_expect_value(pcWriteBuffer, 1, ret, err_info_array[VDEBUG_ERR_INVALID_NUM].msg)) return;
#if CPU_CA5
    extern void Warm_Reset(void);
    Warm_Reset();
//    Global_Reset();
#endif

    vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "%s", err_info_array[VDEBUG_ERR_SUCCCESS].msg);
}

/*
    VDEBUG_MODE_PRIVATE_DVP2BUS_EN,           PROTOCOL:arg1,arg2
    VDEBUG_MODE_PRIVATE_GLB_PORT,             PROTOCOL:arg1,arg2
    VDEBUG_MODE_PRIVATE_GLB_PORT_MODE,        PROTOCOL:arg1,arg2
    VDEBUG_MODE_PRIVATE_GLB_PORT_DB,          PROTOCOL:arg1,arg2
 */
static void vdebug_protocol_set(char *pcWriteBuffer, char* value_str)
{
    int key;
    char key_value[128] = {0};
    int ret = sscanf(value_str, "%d:%s", &key, key_value);
    BL_LOGD("ret is %d, key is %d, value is %s\r\n", ret, key, key_value);

    switch (key) {
        default: {
            break;
        }
    }

    vdebug_output(pcWriteBuffer, VDEBUG_OK_MSG, "%s", err_info_array[VDEBUG_ERR_SUCCCESS].msg);
}

/* todo */
typedef struct
{
    void (*read) (char *argv1);
    void (*write)(char *argv1, char *argv2);
    char *name;
}VDEBUG_OPS_T;

typedef struct
{
    char *name;
    void (*fn)(char *argv1);
}VDEBUG_ARGC1_T;

typedef struct
{
    char *name;
    void (*fn)(char *argv1, char *argv2);
}VDEBUG_ARGC2_T;

typedef struct
{
    char *name;
    void (*fn)(char *argv1, char *argv2, char *argv3);
}VDEBUG_ARGC3_T;


/*
    TODO: READ  && WRITE in one table
 */
static const VDEBUG_ARGC1_T DSP2_READ_TABLE[] =
{
    {VDEBUG_PARAM_DSP2_BLC,                vdebug_dsp2_get_blc},
    {VDEBUG_PARAM_DSP2_CCM,                vdebug_dsp2_get_ccm},
    {VDEBUG_PARAM_COM_GAIN,               vdebug_dsp2_get_gain},
    {VDEBUG_PARAM_DSP2_GAMMAON,            vdebug_dsp2_get_gammaon},
    {VDEBUG_PARAM_DSP2_GAMMA,              vdebug_dsp2_get_gamma},
    {VDEBUG_PARAM_DSP2_YUVMODE,            vdebug_dsp2_get_yuvmode},
    {VDEBUG_PARAM_DSP2_BRIGHTNESS,         vdebug_dsp2_get_brightness},
    {VDEBUG_PARAM_DSP2_CONTRAST,           vdebug_dsp2_get_contrast},
    {VDEBUG_PARAM_DSP2_SATURATION,         vdebug_dsp2_get_saturation},
    {VDEBUG_PARAM_DSP2_AETARGET,           vdebug_dsp2_get_aetarget},
    {VDEBUG_PARAM_DSP2_AELUMA,             vdebug_dsp2_get_aeluma},
    {VDEBUG_PARAM_DSP2_2DNR,               vdebug_dsp2_get_2dnr},
    {VDEBUG_PARAM_DSP2_3DNR,               vdebug_dsp2_get_3dnr},
    {VDEBUG_PARAM_DSP2_DPCENHANCE,         vdebug_dsp2_get_dpcenhance},
    {VDEBUG_PARAM_DSP2_DPCEHRESHOLD,       vdebug_dsp2_get_dpcthreshold},
    {VDEBUG_PARAM_DSP2_LSCON,              vdebug_dsp2_get_lscon},
    {VDEBUG_PARAM_DSP2_LSC,                vdebug_dsp2_get_lsc},
    {VDEBUG_PARAM_DSP2_LSCMAX,             vdebug_dsp2_get_lscmax},
    {VDEBUG_PARAM_DSP2_NOISE_LEVEL,        vdebug_dsp2_get_noiselevel},
    {VDEBUG_PARAM_DSP2_AWBTEMP,            vdebug_dsp2_get_awbtemp},
    {VDEBUG_PARAM_DSP2_AWBMODE,            vdebug_dsp2_get_awbmode},
};

static const VDEBUG_ARGC2_T DSP2_WRITE_TABLE[] =
{
    {VDEBUG_PARAM_DSP2_BLC,                vdebug_dsp2_set_blc},
    {VDEBUG_PARAM_DSP2_CCM,                vdebug_dsp2_set_ccm},
    {VDEBUG_PARAM_COM_GAIN,               vdebug_dsp2_set_gain},
    {VDEBUG_PARAM_DSP2_GAMMAON,            vdebug_dsp2_set_gammaon},
    {VDEBUG_PARAM_DSP2_GAMMA,              vdebug_dsp2_set_gamma},
    {VDEBUG_PARAM_DSP2_YUVMODE,            vdebug_dsp2_set_yuvmode},
    {VDEBUG_PARAM_DSP2_BRIGHTNESS,         vdebug_dsp2_set_brightness},
    {VDEBUG_PARAM_DSP2_CONTRAST,           vdebug_dsp2_set_contrast},
    {VDEBUG_PARAM_DSP2_SATURATION,         vdebug_dsp2_set_saturation},
    {VDEBUG_PARAM_DSP2_AEMODE,             vdebug_dsp2_set_aemode},
    {VDEBUG_PARAM_DSP2_AETARGET,           vdebug_dsp2_set_aetarget},
    {VDEBUG_PARAM_DSP2_AESPEED,            vdebug_dsp2_set_aespeed},
    {VDEBUG_PARAM_DSP2_AEMAXGAIN,          vdebug_dsp2_set_gain_upper_limit},
    {VDEBUG_PARAM_DSP2_AWBMODE,            vdebug_dsp2_set_awbmode},
    {VDEBUG_PARAM_DSP2_AWBTEMP,            vdebug_dsp2_set_awbtemp},
    {VDEBUG_PARAM_DSP2_2DNR,               vdebug_dsp2_set_2dnr},
    {VDEBUG_PARAM_DSP2_3DNR,               vdebug_dsp2_set_3dnr},
    {VDEBUG_PARAM_DSP2_DPCMODE,            vdebug_dsp2_set_dpcmode},
    {VDEBUG_PARAM_DSP2_DPCENHANCE,         vdebug_dsp2_set_dpcenhance},
    {VDEBUG_PARAM_DSP2_DPCEHRESHOLD,       vdebug_dsp2_set_dpcthreshold},
    {VDEBUG_PARAM_DSP2_LSCON,              vdebug_dsp2_set_lscon},
    {VDEBUG_PARAM_DSP2_LSC,                vdebug_dsp2_set_lsc},
    {VDEBUG_PARAM_DSP2_LSCMAX,             vdebug_dsp2_set_lscmax},
    {VDEBUG_PARAM_DSP2_NOISE_LEVEL,        vdebug_dsp2_set_noiselevel},
};

static const VDEBUG_ARGC1_T SENSOR_READ_TABLE[] =
{
    {VDEBUG_PARAM_COM_GAIN,             vdebug_sensor_get_gain},
    {VDEBUG_PARAM_SENSOR_MAXGAIN,       vdebug_sensor_get_maxgain},
    {VDEBUG_PARAM_SENSOR_EXPOSURE,      vdebug_sensor_get_exposure},
};

static const VDEBUG_ARGC2_T SENSOR_WRITE_TABLE[] =
{
    {VDEBUG_PARAM_COM_GAIN,             vdebug_sensor_set_gain},
    {VDEBUG_PARAM_SENSOR_EXPOSURE,      vdebug_sensor_set_exposure},
};

static const VDEBUG_ARGC2_T ADVANCED_WRITE_TABLE[] =
{
    {VDEBUG_PARAM_ADVANCED_SET_LOG_LVL,     vdebug_advanced_set_log_level},
    {VDEBUG_PARAM_ADVANCED_SYS_RST,         vdebug_advanced_system_reset},
};

/*todo */
static const VDEBUG_ARGC2_T PROTOCOL_WRITE_TABLE[] =
{
    {VDEBUG_PARAM_PROTOCOL_SET,   vdebug_protocol_set},
};


static void vdebug_dsp2_domain_operation(char *pcWriteBuffer, size_t xWriteBufferLen, int argc, char** argv)
{
    if (argc < 3) {
        return;
    }

    /* READ */
    /* TODO ADDR*/
    if (0 == strncmp(argv[1], VDEBUG_PARAM_OPT_READ, strlen(VDEBUG_PARAM_OPT_READ))) {
        if (0 == strncmp(argv[2], VDEBUG_PARAM_COM_ADDR, strlen(VDEBUG_PARAM_COM_ADDR))) {
            BL_CHECK_POINTER(argv[3]);
            vdebug_com_readreg(pcWriteBuffer, (const char*)argv[3], VDEBUG_DSP2_REGISTER);
            return;
        }

        for (int i = 0; i < sizeof(DSP2_READ_TABLE) / sizeof(DSP2_READ_TABLE[0]); ++i) {
            if (0 == strncmp(argv[2], DSP2_READ_TABLE[i].name, \
                VDEBUG_MAX(strlen(DSP2_READ_TABLE[i].name), strlen(argv[2])))) {
                DSP2_READ_TABLE[i].fn(pcWriteBuffer);
                return;
            }

        }
    }
    /* Write */
    /* TODO ADDR*/
    else if (0 == strncmp(argv[1], VDEBUG_PARAM_OPT_WRITE, strlen(VDEBUG_PARAM_OPT_WRITE))) {
        if (0 == strncmp(argv[2], VDEBUG_PARAM_COM_ADDR, strlen(VDEBUG_PARAM_COM_ADDR))) {
            BL_CHECK_POINTER(argv[3]);
            BL_CHECK_POINTER(argv[4]);
            vdebug_com_writereg(pcWriteBuffer, (const char*)argv[3], (const char*)argv[4], VDEBUG_DSP2_REGISTER);
            return;
        }

        for (int i = 0; i < sizeof(DSP2_WRITE_TABLE) / sizeof(DSP2_WRITE_TABLE[0]); ++i) {
            if (0 == strncmp(argv[2], DSP2_WRITE_TABLE[i].name, \
                VDEBUG_MAX(strlen(DSP2_WRITE_TABLE[i].name), strlen(argv[2])))) {
                BL_CHECK_POINTER(argv[3]);
                DSP2_WRITE_TABLE[i].fn(pcWriteBuffer, argv[3]);
                return;
            }
        }
    }
    else {
    }

    BL_LOGE("vdebug could not recognize this opertion\r\n");
    vdebug_output(pcWriteBuffer, VDEBUG_ERR_MSG, "%s", err_info_array[VDEBUG_ERR_HELP].msg);
}

static void vdebug_encoder_domain_operation(char *pcWriteBuffer, size_t xWriteBufferLen, int argc, char** argv)
{
    if (argc < 3) {
        return;
    }

    if (0 == strncmp(argv[1], VDEBUG_PARAM_OPT_READ, strlen(VDEBUG_PARAM_OPT_READ))) {
        if (0 == strncmp(argv[2], VDEBUG_PARAM_COM_ADDR, strlen(VDEBUG_PARAM_COM_ADDR))) {
            BL_CHECK_POINTER(argv[3]);
            vdebug_com_readreg(pcWriteBuffer, (const char*)argv[3], VDEBUG_ENCODER_REGISTER);
            return;
        }

#if 0
        for (int i = 0; i < sizeof(ENCODER_READ_TABLE) / sizeof(ENCODER_READ_TABLE[0]); ++i) {
            if (0 == strncmp(argv[2], ENCODER_READ_TABLE[i].name, strlen(ENCODER_READ_TABLE[i].name))) {
                ENCODER_READ_TABLE[i].fn(pcWriteBuffer);
                return;
            }
        }
#endif
    }
    else if (0 == strncmp(argv[1], VDEBUG_PARAM_OPT_WRITE, strlen(VDEBUG_PARAM_OPT_WRITE))) {
        if (0 == strncmp(argv[2], VDEBUG_PARAM_COM_ADDR, strlen(VDEBUG_PARAM_COM_ADDR))) {
            BL_CHECK_POINTER(argv[3]);
            BL_CHECK_POINTER(argv[4]);
            vdebug_com_writereg(pcWriteBuffer, (const char*)argv[3], (const char*)argv[4], VDEBUG_ENCODER_REGISTER);
            return;
        }
#if 0
        for (int i = 0; i < sizeof(ENCODER_WRITE_TABLE) / sizeof(ENCODER_WRITE_TABLE[0]); ++i) {
            if (0 == strncmp(argv[2], ENCODER_WRITE_TABLE[i].name, strlen(ENCODER_WRITE_TABLE[i].name))) {
                BL_CHECK_POINTER(argv[3]);
                ENCODER_WRITE_TABLE[i].fn(pcWriteBuffer, argv[3]);
                return;
            }
        }
#endif
    }
    else {
    }

    BL_LOGE("vdebug could not recognize this opertion\r\n");
    vdebug_output(pcWriteBuffer, VDEBUG_ERR_MSG, "%s", err_info_array[VDEBUG_ERR_HELP].msg);
}

static void vdebug_sensor_domain_operation(char *pcWriteBuffer, size_t xWriteBufferLen, int argc, char** argv)
{
    if (argc < 3) {
        return;
    }

    if (0 == strncmp(argv[1], VDEBUG_PARAM_OPT_READ, strlen(VDEBUG_PARAM_OPT_READ))) {
        if (0 == strncmp(argv[2], VDEBUG_PARAM_COM_ADDR, strlen(VDEBUG_PARAM_COM_ADDR))) {
            BL_CHECK_POINTER(argv[3]);
            vdebug_com_readreg(pcWriteBuffer, (const char*)argv[3], VDEBUG_SENSOR_REGISTER);
            return;
        }

        for (int i = 0; i < sizeof(SENSOR_READ_TABLE) / sizeof(SENSOR_READ_TABLE[0]); ++i) {
            if (0 == strncmp(argv[2], SENSOR_READ_TABLE[i].name, \
                VDEBUG_MAX(strlen(SENSOR_READ_TABLE[i].name), strlen(argv[2])))) {
                SENSOR_READ_TABLE[i].fn(pcWriteBuffer);
                return;
            }
        }

    }
    else if (0 == strncmp(argv[1], VDEBUG_PARAM_OPT_WRITE, strlen(VDEBUG_PARAM_OPT_WRITE))) {
        if (0 == strncmp(argv[2], VDEBUG_PARAM_COM_ADDR, strlen(VDEBUG_PARAM_COM_ADDR))) {
            BL_CHECK_POINTER(argv[3]);
            BL_CHECK_POINTER(argv[4]);
            vdebug_com_writereg(pcWriteBuffer, (const char*)argv[3], (const char*)argv[4], VDEBUG_SENSOR_REGISTER);
            return;
        }

        for (int i = 0; i < sizeof(SENSOR_WRITE_TABLE) / sizeof(SENSOR_WRITE_TABLE[0]); ++i) {
            if (0 == strncmp(argv[2], SENSOR_WRITE_TABLE[i].name, \
                VDEBUG_MAX(strlen(SENSOR_WRITE_TABLE[i].name), strlen(argv[2])))) {
                BL_CHECK_POINTER(argv[3]);
                SENSOR_WRITE_TABLE[i].fn(pcWriteBuffer, argv[3]);
                return;
            }
        }
    }
    else {
    }

    BL_LOGE("vdebug could not recognize this opertion\r\n");
    vdebug_output(pcWriteBuffer, VDEBUG_ERR_MSG, "%s", err_info_array[VDEBUG_ERR_HELP].msg);
}

static void vdebug_advanced_domain_operation(char *pcWriteBuffer, size_t xWriteBufferLen, int argc, char** argv)
{
    if (argc < 3) {
        return;
    }

    if (0 == strncmp(argv[1], VDEBUG_PARAM_OPT_READ, strlen(VDEBUG_PARAM_OPT_READ))) {
        if (0 == strncmp(argv[2], VDEBUG_PARAM_COM_ADDR, strlen(VDEBUG_PARAM_COM_ADDR))) {
            BL_CHECK_POINTER(argv[3]);
            vdebug_com_readreg(pcWriteBuffer, (const char*)argv[3], VDEBUG_ADVANCED_REGISTER);
            return;
        }
    }
    else if (0 == strncmp(argv[1], VDEBUG_PARAM_OPT_WRITE, strlen(VDEBUG_PARAM_OPT_WRITE))) {
        if (0 == strncmp(argv[2], VDEBUG_PARAM_COM_ADDR, strlen(VDEBUG_PARAM_COM_ADDR))) {
            BL_CHECK_POINTER(argv[3]);
            BL_CHECK_POINTER(argv[4]);
            vdebug_com_writereg(pcWriteBuffer, (const char*)argv[3], (const char*)argv[4], VDEBUG_ADVANCED_REGISTER);
            return;
        }

        for (int i = 0; i < sizeof(ADVANCED_WRITE_TABLE) / sizeof(ADVANCED_WRITE_TABLE[0]); ++i) {
            if (0 == strncmp(argv[2], ADVANCED_WRITE_TABLE[i].name, strlen(ADVANCED_WRITE_TABLE[i].name))) {
                BL_CHECK_POINTER(argv[3]);
                ADVANCED_WRITE_TABLE[i].fn(pcWriteBuffer, argv[3]);
                return;
            }
        }
    }
    else {
    }

    BL_LOGE("vdebug could not recognize this opertion\r\n");
    vdebug_output(pcWriteBuffer, VDEBUG_ERR_MSG, "%s", err_info_array[VDEBUG_ERR_HELP].msg);
}

static void vdebug_protocol_domain_operation(char *pcWriteBuffer, size_t xWriteBufferLen, int argc, char** argv)
{
    if (argc < 3) {
        return;
    }

    if (0 == strncmp(argv[1], VDEBUG_PARAM_OPT_READ, strlen(VDEBUG_PARAM_OPT_READ))) {
        return;
    }
    else if (0 == strncmp(argv[1], VDEBUG_PARAM_OPT_WRITE, strlen(VDEBUG_PARAM_OPT_WRITE))) {
        for (int i = 0; i < sizeof(PROTOCOL_WRITE_TABLE) / sizeof(PROTOCOL_WRITE_TABLE[0]); ++i) {
            if (0 == strncmp(argv[2], PROTOCOL_WRITE_TABLE[i].name, strlen(PROTOCOL_WRITE_TABLE[i].name))) {
                BL_CHECK_POINTER(argv[3]);
                PROTOCOL_WRITE_TABLE[i].fn(pcWriteBuffer, argv[3]);
                return;
            }
        }
    }
    else {
    }

    BL_LOGE("vdebug could not recognize this opertion\r\n");
    vdebug_output(pcWriteBuffer, VDEBUG_ERR_MSG, "%s", err_info_array[VDEBUG_ERR_HELP].msg);
}

static void handle_vdebug_cmd(char *buf, int len, int argc, char **argv)
{
    int vdebug_argc = argc - 1;
    char **vdebug_argv = (argv + 1);

    /* clear output buffer */
    memset( buf, 0x00, len );

    BL_LOGD("debug: the num of valid parameter is %d\r\n", argc - 1);

    for (int i = 0; i < argc; ++i) {
        BL_LOGD("debug: argv[%d] is %s\r\n", i, argv[i]);
    }

    /* check the parameter*/
    if (0 == vdebug_argc) {
        strncpy(buf, (char*)VDEBUG_HELP_MESSAGE_SHORT, len );
        return;
    }

    /* domain sel */
    switch (argv[1][1]) {
        case 'i': {
            vdebug_dsp2_domain_operation(buf, len, vdebug_argc, vdebug_argv);
            break;
        }
        case 's': {
            vdebug_sensor_domain_operation(buf, len, vdebug_argc, vdebug_argv);
            break;
        }
        case 'a': {
            vdebug_advanced_domain_operation(buf, len, vdebug_argc, vdebug_argv);
            break;
        }
        case 'e': {
            vdebug_encoder_domain_operation(buf, len, vdebug_argc, vdebug_argv);
            break;
        }
        case 'p': {
            vdebug_protocol_domain_operation(buf, len, vdebug_argc, vdebug_argv);
            break;
        }
        case 'h':
        default: {
            VDEBUG_HELP_MESSAGE(buf, len);
            break;
        }
    }
}

const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
    {"vdebug", "video debug utility", handle_vdebug_cmd},
};

int helper_vdebug_cli_init(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user) / sizeof(cmds_user[0]));
    return 0;
}

