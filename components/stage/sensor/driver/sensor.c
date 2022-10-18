#include <string.h>
#include <math.h>

#include <bl808.h>
#include <bl808_clkrst.h>
#include <bl_gpio.h>

#include "bl808_gpio.h"
#include "bl808_glb.h"

#include "sccb.h"
#include "sensor.h"

//#define ENABLE_PWDN_LOW

#define GPIO_SENSOR_BOARD_RST (21)

extern BL_SENSOR_DESC_T _ld_bl_driver_sensor_start;
extern BL_SENSOR_DESC_T _ld_bl_driver_sensor_end;

static sensor_t sensor;
static int sensor_inited = 0;
static BL_SENSOR_DESC_T* cur_sensor = {0};

#if 0
float db_to_gain[] = {
    1   ,
    1.044273782 ,
    1.090507733 ,
    1.138788635 ,
    1.189207115 ,
    1.241857812 ,
    1.296839555 ,
    1.354255547 ,
    1.414213562 ,
    1.476826146 ,
    1.542210825 ,
    1.610490332 ,
    1.681792831 ,
    1.75625216  ,
    1.834008086 ,
    1.915206561 ,
    2   ,
    2.088547565 ,
    2.181015465 ,
    2.27757727  ,
    2.37841423  ,
    2.483715624 ,
    2.593679109 ,
    2.708511094 ,
    2.828427125 ,
    2.953652292 ,
    3.084421651 ,
    3.220980664 ,
    3.363585661 ,
    3.512504321 ,
    3.668016173 ,
    3.830413123 ,
    4   ,
    4.17709513  ,
    4.362030931 ,
    4.555154539 ,
    4.75682846  ,
    4.967431248 ,
    5.187358219 ,
    5.417022188 ,
    5.656854249 ,
    5.907304584 ,
    6.168843302 ,
    6.441961328 ,
    6.727171322 ,
    7.025008641 ,
    7.336032346 ,
    7.660826246 ,
    8   ,
    8.354190259 ,
    8.724061861 ,
    9.110309078 ,
    9.51365692  ,
    9.934862497 ,
    10.37471644 ,
    10.83404438 ,
    11.3137085  ,
    11.81460917 ,
    12.3376866  ,
    12.88392266 ,
    13.45434264 ,
    14.05001728 ,
    14.67206469 ,
    15.32165249 ,
    16  ,
    16.70838052 ,
    17.44812372 ,
    18.22061816 ,
    19.02731384 ,
    19.86972499 ,
    20.74943287 ,
    21.66808875 ,
    22.627417   ,
    23.62921834 ,
    24.67537321 ,
    25.76784531 ,
    26.90868529 ,
    28.10003457 ,
    29.34412938 ,
    30.64330498 ,
    32  ,
    33.41676104 ,
    34.89624745 ,
    36.44123631 ,
    38.05462768 ,
    39.73944999 ,
    41.49886575 ,
    43.3361775  ,
    45.254834   ,
    47.25843667 ,
    49.35074641 ,
    51.53569062 ,
    53.81737058 ,
    56.20006913 ,
    58.68825877 ,
    61.28660996 ,
    64  ,
    66.83352208 ,
    69.79249489 ,
    72.88247262 ,
    76.10925536 ,
    79.47889997 ,
    82.9977315  ,
    86.672355   ,
    90.50966799 ,
    94.51687334 ,
    98.70149283 ,
    103.0713812 ,
    107.6347412 ,
    112.4001383 ,
    117.3765175 ,
    122.5732199 ,
    128 ,
    133.6670442 ,
    139.5849898 ,
    145.7649452 ,
    152.2185107 ,
    158.9577999 ,
    165.995463  ,
    173.34471   ,
    181.019336  ,
    189.0337467 ,
    197.4029857 ,
    206.1427625 ,
    215.2694823 ,
    224.8002765 ,
    234.7530351 ,
    245.1464399 ,
    256 ,
};

static int dB_to_ISO(BL_GAIN_DB gain)
{
#if 1   // optimized version
    int index = DIV_ROUND(gain,96);
    return FLOAT_TO_INT(db_to_gain[index] * 100);
#else
   float gain_x = pow(2, GAIN_DB_INT_TO_FLOAT(gain)/6);
   return FLOAT_TO_INT(gain_x * 100);
#endif
}
#endif

#if 0
static float dB_to_gain(BL_GAIN_DB gain)
{
#if 0
    int index = DIV_ROUND(gain,96);
    return db_to_gain[index];
#else
    return pow(2, GAIN_DB_INT_TO_FLOAT(gain)/6);
#endif
}
#endif
int sensor_is_inited(void)
{
    return sensor_inited;
}

int sensor_is_enabled(void)
{
    return (sensor_inited && sensor.enabled) ? 1 : 0;
}

int sensor_enable(void)
{
    if (!sensor_inited)
        return -1;

    if (sensor.enable(&sensor) < 0)
        return -1;

    sensor.enabled = 1;
    return 0;
}

int sensor_disable(void)
{
    if (sensor.enabled) {
        if (sensor.disable(&sensor) < 0) {
            return -1;
        }

        sensor.enabled = 0;
        sensor_inited = 0;
    }

    return 0;
}

int sensor_getFmt(VIDEO_MODE_E *video_mode)
{
    *video_mode = sensor.video_mode;

    return 0;
}

int sensor_setFmt(VIDEO_MODE_E video_mode)
{
    int ret = 0;
    sensor.video_mode = video_mode;
    ret = cur_sensor->setFmt(&sensor);
    if (ret < 0) {
        BL_LOGE("Sensor format failed! Please check the sensor fomat.\r\n");
    }
    return ret;
}

static void FPGA_Borad_MMA_PWDN()
{
    int tmp;
    tmp = *(uint32_t*)(0x300000FC);
#ifdef ENABLE_PWDN_LOW
    tmp = tmp & 0xFFF7;
#else
    tmp = tmp | 0x08;
#endif
    *(uint32_t*)(0x300000FC) = tmp;
}

//FIXME TODO remove this func after mipi pll && mipi dhpy reigster setting driver provided by liuzhao later
static void test_set_reg_value(uint32_t addr, uint32_t len, uint32_t pos, uint32_t value)
{
    uint32_t tmp = 0;

    tmp = *((uint32_t *)addr);
    tmp = (tmp & (~(((1 << len)-1)<<pos))) | (value<<pos);
    *((uint32_t *)addr) = tmp;
}

//FIXME TODO mipi pll && mipi dhpy reigster setting driver would be provided by liuzhao later
static void power_up_mipipll()
{
    if (DSP2_INPUT_MODE == DSP2_INPUT_MIPI_2LANE) {
        // 2 lane 330M
        test_set_reg_value(0x200007A4, 3, 7, 2);
        //FIXME TODO fix hard code after formula provided
        if (BL808_BOARD_TYPE == BL_BOARD_808_EVB) {
            // TODO sw should more flexible, defaut is GC2053 evb,
            // gc2053
            test_set_reg_value(0x200007a8, 19, 0, 0x21000);
        }
        else if (BL808_BOARD_TYPE == BL_BOARD_808_OPNM8508PA){
            //FIXME TODO fix hard code after formula provided
            *(uint32_t*)(0x200007A0) =  0x8310;
            test_set_reg_value(0x200007a8, 19, 0, 0x9733);
        }
    }
    else if (DSP2_INPUT_MODE == DSP2_INPUT_MIPI_1LANE) {
        // 1lane 696M
        // test_set_reg_value(0x200007A4, 3, 7, 1);
        // test_set_reg_value(0x200007a8, 19, 0, 0x22ccc);
        // 1lane 816M
        test_set_reg_value(0x200007A4, 3, 7, 1);
        //FIXME TODO fix hard code after formula provided
        test_set_reg_value(0x200007a8, 19, 0, 0x28ccc);

    }

    //FIXME TODO glb driver in c906 should be update
    test_set_reg_value(0x20000790, 1, 9, 1);
    test_set_reg_value(0x20000790, 1, 10, 1);
    test_set_reg_value(0x20000790, 1, 2, 0);
    test_set_reg_value(0x20000790, 1, 2, 1);
}

//FIXME TODO mipi pll && mipi dhpy reigster setting driver would be provided by liuzhao later
static void power_up_csi()
{
    test_set_reg_value(0x3001A088, 5, 10, 0x1a);
    test_set_reg_value(0x3001A1BC, 1, 8, 1);
    test_set_reg_value(0x3001A1BC, 1, 29, 1);
    test_set_reg_value(0x3001A080, 3, 0, 7);
    test_set_reg_value(0x3001A080, 2, 12, 3);
    test_set_reg_value(0x3001A080, 1, 31, 1);
}

static void power_up_csi_io()
{
    //FIXME TODO glb driver in c906 should be update
    test_set_reg_value(0x200006c8, 4, 20, 4);
}

static void sensor_pinmux_init(void)
{
    GLB_GPIO_Cfg_Type cfg;
    if (DSP2_INPUT_MODE == DSP2_INPUT_DVP) {
        uint8_t gpiopins[] = {GLB_GPIO_PIN_17, GLB_GPIO_PIN_16, GLB_GPIO_PIN_24,
                                GLB_GPIO_PIN_19, GLB_GPIO_PIN_18, GLB_GPIO_PIN_32, GLB_GPIO_PIN_31, GLB_GPIO_PIN_30, GLB_GPIO_PIN_29,
                                GLB_GPIO_PIN_28, GLB_GPIO_PIN_27, GLB_GPIO_PIN_26, GLB_GPIO_PIN_25};
        int i;

        cfg.gpioMode=GPIO_MODE_AF;
        cfg.pullType=GPIO_PULL_NONE;
        cfg.drive=0;
        cfg.smtCtrl=1;

        for(i=0;i<sizeof(gpiopins)/sizeof(gpiopins[0]);i++){
            cfg.gpioPin=gpiopins[i];
            cfg.gpioFun=GPIO_FUN_CAM;
            GLB_GPIO_Init(&cfg);
        }

        // REFCLK
        cfg.gpioPin=GLB_GPIO_PIN_33;
        cfg.gpioFun=GPIO_FUN_CLOCK_OUT;
        GLB_GPIO_Init(&cfg);

        cfg.gpioMode=GPIO_MODE_OUTPUT;
        cfg.pullType=GPIO_PULL_UP;
        // RESET
        if (DVP_8BIT_MODE == 1) {
            cfg.gpioPin=GLB_GPIO_PIN_18;
            cfg.gpioFun=GPIO_FUN_GPIO;
            GLB_GPIO_Init(&cfg);
            GLB_GPIO_Write(GLB_GPIO_PIN_18, 0);
            GLB_GPIO_Output_Enable(GLB_GPIO_PIN_18);
        } else {
            cfg.gpioPin=GLB_GPIO_PIN_20;
            cfg.gpioFun=GPIO_FUN_GPIO;
            GLB_GPIO_Init(&cfg);
            GLB_GPIO_Write(GLB_GPIO_PIN_20, 0);
            GLB_GPIO_Output_Enable(GLB_GPIO_PIN_20);
        }

        // PWDN
        cfg.gpioPin=GLB_GPIO_PIN_8;
        cfg.gpioFun=GPIO_FUN_GPIO;
        GLB_GPIO_Init(&cfg);
        GLB_GPIO_Write(GLB_GPIO_PIN_8, 0);
        GLB_GPIO_Output_Enable(GLB_GPIO_PIN_8);

        GLB_Set_ClkOutSel(1, 0); // select dvp_ref_clk pin as cam_ref_clk
        GLB_Set_Cam_Ref_CLK(1, 1, 3); // select cam_ref_clk as 96M / 4 = 24M
    }
    else {
        GLB_GPIO_Cfg_Type cfg;

        cfg.pullType = GPIO_PULL_NONE;
        cfg.drive = 0;
        cfg.smtCtrl = 1;

        if (BL808_BOARD_TYPE == BL_BOARD_808_EVB) {
            // reset
            cfg.gpioPin = GLB_GPIO_PIN_21;
            cfg.gpioFun = GPIO_FUN_GPIO;
            cfg.gpioMode = GPIO_MODE_OUTPUT;
            GLB_GPIO_Init(&cfg);
            GLB_GPIO_Write(GLB_GPIO_PIN_21, 0);
            GLB_GPIO_Output_Enable(GLB_GPIO_PIN_21);

            // pwdn
            cfg.gpioPin = GLB_GPIO_PIN_22;
            cfg.gpioFun = GPIO_FUN_GPIO;
            cfg.gpioMode = GPIO_MODE_OUTPUT;
            GLB_GPIO_Init(&cfg);
            GLB_GPIO_Write(GLB_GPIO_PIN_22, 0);
            GLB_GPIO_Output_Enable(GLB_GPIO_PIN_22);

            // mclk
            cfg.gpioPin = GLB_GPIO_PIN_23;
            cfg.gpioFun = GPIO_FUN_CLOCK_OUT;
            cfg.gpioMode = GPIO_MODE_OUTPUT;
            GLB_GPIO_Init(&cfg);

            GLB_Set_ClkOutSel(3, 0); // select dvp_ref_clk pin as cam_ref_clk
            GLB_Set_Cam_Ref_CLK(1, 1, 3); // select cam_ref_clk as 96M / 4 = 24M
        }
        else if (BL808_BOARD_TYPE == BL_BOARD_808_OPNM8508PA){
            cfg.gpioPin = GLB_GPIO_PIN_41;
            cfg.gpioFun = GPIO_FUN_GPIO;
            cfg.gpioMode = GPIO_MODE_OUTPUT;
            GLB_GPIO_Init(&cfg);
            GLB_GPIO_Write(GLB_GPIO_PIN_41, 0);
            GLB_GPIO_Output_Enable(GLB_GPIO_PIN_41);
        }
    }
}

static void sensor_input_reset(void)
{
    if (DSP2_INPUT_MODE == DSP2_INPUT_DVP) {
        // GLB_GPIO_Cfg_Type cfg;
        // cfg.gpioMode=GPIO_MODE_AF;
        // cfg.pullType=GPIO_PULL_UP;
        // cfg.drive=1;
        // cfg.smtCtrl=1;

        // PWDN
        GLB_GPIO_Write(GLB_GPIO_PIN_8, 1);

        // RESETB
        GLB_GPIO_Write(GLB_GPIO_PIN_20, 1);
    }
    else {
        if (BL808_BOARD_TYPE == BL_BOARD_808_EVB) {
            // TODO defaut is GC2053 evb,  sw should more flexible
            // PWDN
            GLB_GPIO_Write(GLB_GPIO_PIN_22, 1);
            // RESETB
            GLB_GPIO_Write(GLB_GPIO_PIN_21, 1);
        }
        else if (BL808_BOARD_TYPE == BL_BOARD_808_OPNM8508PA){
            // RESETB
            GLB_GPIO_Write(GLB_GPIO_PIN_41, 1);
        }
    }
    // sc2336: pwdn rising to first i2c transaction >= 4ms
    //BL808_Delay_MS(50);

    // gc2053: pwdn rising to first i2c transaction >= 50us
     BL808_Delay_US(50);

}

static void yuv_sensor_input_reset(void)
{
    // RESET
    GLB_GPIO_Write(GLB_GPIO_PIN_18, 1);
    // PWDN
    GLB_GPIO_Write(GLB_GPIO_PIN_8, 0);
    BL808_Delay_US(50);
}

int sensor_init(void)
{
    uint8_t slv_addr;
    BL_SENSOR_DESC_T *start, *end;

    start = &_ld_bl_driver_sensor_start;
    end = &_ld_bl_driver_sensor_end;

    if (sensor_inited) {
        return 0;
    }

    memset(&sensor, 0, sizeof(sensor));

    if (DSP2_INPUT_MODE != DSP2_INPUT_DVP) {
        power_up_csi_io();
        sensor_pinmux_init();
        power_up_mipipll();
        power_up_csi();
    }
    else {
        sensor_pinmux_init();
    }

    SCCB_Init();
#if (BL80X_HW_VER <= BL80X_HW_A0)
    bl_gpio_enable_output(GPIO_SENSOR_BOARD_RST, 0, 0);
    bl_gpio_output_set(GPIO_SENSOR_BOARD_RST, 0);
    BL808_Delay_MS(2);
    bl_gpio_output_set(GPIO_SENSOR_BOARD_RST, 1);
#else
    DSP2_Sensor_Reset();
    sensor_input_reset();
#endif
    slv_addr = SCCB_Scan(0x1, 0x3c);
    BL_LOGI("slv_addr[0x%02x]\r\n", slv_addr);

    while (start < end) {
        BL_LOGI("try matching the sensor module [%s]\r\n", start->name);
        if(slv_addr == start->addr) {
            SCCB_Init();    /* TODO: will add i2c_abort in SCCB_Scan */
            if (0 == start->probe()){
                BL_LOGI("Initialize sensor module [%s]\r\n", start->name);
                if (start->init(&sensor) < 0) {
                    return -1;
                }

#if PRINT_FAST_CAP_TIMING
                printf("SNS INIT %lu\r\n", xTaskGetTickCountFromISR());
#endif
                sensor_inited = 1;
                sensor.video_mode = VIDEO_MODE_1080P_25;//default
                cur_sensor = start;
                return 0;
            }
        }
        start++;
    }

    BL_LOGE("Sensor probe failed! Please check the sensor connection.\r\n");
    return -1;
}

int yuvsensor_init(void)
{
    uint8_t slv_addr;
    BL_SENSOR_DESC_T *start, *end;

    start = &_ld_bl_driver_sensor_start;
    end = &_ld_bl_driver_sensor_end;
    sensor_pinmux_init();

    SCCB_Init();
    DSP2_Sensor_Reset();
    yuv_sensor_input_reset();

    slv_addr = SCCB_Scan(0x1, 0x7f);
    BL_LOGI("slv_addr[0x%02x]\r\n", slv_addr);

    while (start < end) {
        BL_LOGI("try matching the sensor module [%s]\r\n", start->name);
        if(slv_addr == start->addr) {
            SCCB_Init();    /* TODO: will add i2c_abort in SCCB_Scan */
            if (0 == start->probe()){
                BL_LOGI("Initialize sensor module [%s]\r\n", start->name);
                if (start->init(NULL) < 0) {
                    return -1;
                }

#if PRINT_FAST_CAP_TIMING
                printf("SNS INIT %lu\r\n", xTaskGetTickCountFromISR());
#endif
                return 0;
            }
        }
        start++;
    }

    BL_LOGE("Sensor probe failed! Please check the sensor connection.\r\n");
    return -1;

}

static void sipeed_board_pinmux_init(GLB_GPIO_Type mclk, GLB_GPIO_Type pwdn, GLB_GPIO_Type reset)
{
    GLB_GPIO_Cfg_Type cfg;

    cfg.drive = 0;
    cfg.smtCtrl = 1;
    // REFCLK
    cfg.gpioPin=mclk;
    cfg.gpioFun=GPIO_FUN_CLOCK_OUT;
    GLB_GPIO_Init(&cfg);

    cfg.gpioMode=GPIO_MODE_OUTPUT;
    cfg.pullType=GPIO_PULL_UP;
    // PWDN
    cfg.gpioPin=pwdn;
    cfg.gpioFun=GPIO_FUN_GPIO;
    GLB_GPIO_Init(&cfg);
    GLB_GPIO_Write(pwdn, 1);
    GLB_GPIO_Output_Enable(pwdn);

    // RESET
    cfg.gpioPin=reset;
    cfg.gpioFun=GPIO_FUN_GPIO;
    GLB_GPIO_Init(&cfg);
    GLB_GPIO_Write(reset, 1);
    GLB_GPIO_Output_Enable(reset);

    GLB_Set_CAM_CLK(ENABLE, GLB_CAM_CLK_WIFIPLL_96M, 3); // select cam_ref_clk as 96M / 4 = 24M
}

int mipi_sensor_init(void)
{
    uint8_t slv_addr;
    BL_SENSOR_DESC_T *start, *end;

    start = &_ld_bl_driver_sensor_start;
    end = &_ld_bl_driver_sensor_end;
    sipeed_board_pinmux_init(GLB_GPIO_PIN_33, GLB_GPIO_PIN_40, GLB_GPIO_PIN_41);
    SIPEED_SCCB_Init();

    slv_addr = SCCB_Scan(0x1, 0x7f);
    slv_addr = 0x3c;
    BL_LOGI("slv_addr[0x%02x]\r\n", slv_addr);

    while (start < end) {
        BL_LOGI("try matching the sensor module [%s]\r\n", start->name);
        if(slv_addr == start->addr) {
            if (0 == start->probe()){
                BL_LOGI("Initialize sensor module [%s]\r\n", start->name);
                if (start->init(NULL) < 0) {
                    return -1;
                }

                return 0;
            }
        }
        start++;
    }

    BL_LOGE("Sensor probe failed! Please check the sensor connection.\r\n");
    return -1;
}

#if 0
void sensor_get_uid(BL_SENSOR_UID_E *uid)
{
    *uid = sensor.uid;
}
#endif

int sensor_reset(void)
{
    if (!sensor.enabled)
        return -1;

    if (sensor.disable(&sensor) < 0)
        return -1;

    return 0;
}

void sensor_get_name(const char** name)
{
    *name = sensor.name;
}

int sensor_get_total_window(BL_Img_Size_T *win)
{
    if (!sensor_inited)
        return -1;

    win->width = sensor.total_win.width;
    win->height = sensor.total_win.height;

    return 0;
}

int sensor_get_output_window(BL_Img_Size_T *win)
{
    if (!sensor_inited)
        return -1;

    win->width = sensor.out_win.width;
    win->height = sensor.out_win.height;

    return 0;
}

int sensor_get_dsp2_output_window(BL_Img_Size_T *win)
{
    if (!sensor_inited)
        return -1;

    if (0 == sensor.dsp2_out_win.width) {
        sensor.dsp2_out_win.width = sensor.out_win.width;
        sensor.dsp2_out_win.height = sensor.out_win.height;
        win->width  = sensor.out_win.width;
        win->height = sensor.out_win.height;

        return 0;
    }

    win->width = sensor.dsp2_out_win.width;
    win->height = sensor.dsp2_out_win.height;

    return 0;
}

int sensor_get_fps(uint32_t *fps)
{
    if (!sensor_inited)
        return -1;

    *fps = sensor.fps;

    return 0;
}

int sensor_set_fps(uint32_t fps)
{
    if (!sensor.enabled)
        return -1;

    if (sensor.set_fps(&sensor, fps) < 0)
        return -1;

    sensor.fps = fps;
    return 0;
}

int sensor_get_pix_clk(uint32_t *clk)
{
    if (!sensor_inited)
        return -1;

    *clk = sensor.pix_clk;

    return 0;
}

uint8_t sensor_get_slv_addr(void)
{
    return sensor.slv_addr;
}

int sensor_get_bayer_pattern(BAYER_PATTERN_E *bayer)
{
    sensor_property_t property;
    if (!sensor_inited)
        return -1;

    sensor.get_property(&sensor, &property);
    *bayer = property.bayer_pattern;

    return 0;
}

int sensor_get_exposure_max(BL_EXPO_TIME *max_expo_time)
{
    if (!sensor_inited)
        return -1;

    *max_expo_time = sensor.max_expo_time;
    return 0;
}

int sensor_get_exposure_min(BL_EXPO_TIME *min_expo_time)
{
    if (!sensor_inited)
        return -1;

    *min_expo_time = sensor.min_expo_time;
    return 0;
}

int sensor_get_gain_max(BL_GAIN_DB *max_gain)
{
    if (!sensor_inited)
        return -1;

    *max_gain = sensor.max_gain;
    return 0;
}

int sensor_get_gain_step(BL_GAIN_DB *gain_step)
{
    if (!sensor_inited)
        return -1;

    *gain_step = sensor.min_gain_step;
    return 0;
}

int sensor_get_video_mode(VIDEO_MODE_E *video_mode)
{
    *video_mode = sensor.video_mode;

    return 0;
}

/* video_mode value ranges from 0 ~ VIDEO_MODE_INVALID - 1 */
int sensor_set_video_mode(VIDEO_MODE_E video_mode)
{
    if (video_mode < 0 || video_mode > VIDEO_MODE_INVALID - 1) {
        BL_LOGE("\t sensor_set_video_mode: video mode value %d out of range 1/%d ~ 1/%d sec.\r\n", video_mode,
            0, VIDEO_MODE_INVALID - 1);

        return -1;
    }

    sensor.video_mode = video_mode;
    return 0;
}

int sensor_get_exposure(BL_EXPO_TIME *expo_time)
{
    *expo_time = sensor.expo_time;

    return 0;
}

/* Expo time value ranges from EXPO_TIME_MIN ~ EXPO_TIME_1_25_SEC */
int sensor_set_exposure(BL_EXPO_TIME expo_time)
{
    if (expo_time < sensor.min_expo_time || expo_time > sensor.max_expo_time) {
        BL_LOGE("\t sensor_set_exposure: exposure value %d out of range 1/%d ~ 1/%d sec.\r\n", expo_time,
            EXPO_TIME_TO_INT(sensor.min_expo_time), EXPO_TIME_TO_INT(sensor.max_expo_time));

        return -1;
    }

    if (sensor.set_exposure(&sensor, expo_time) < 0)
        return -1;

    sensor.expo_time = expo_time;
    return 0;
}

int sensor_get_gain(BL_GAIN_DB *gain)
{
    if (!sensor.enabled)
        return -1;

    *gain = sensor.gain;
    return 0;
}

int sensor_set_gain(BL_GAIN_DB gain)
{
    if (!sensor.enabled)
        return -1;

    if (gain < 0 || gain > sensor.max_gain) {
        BL_LOGE("\t sensor_set_gain: invalid gain value %d!\r\n", gain);
        return -1;
    }

    if (sensor.set_gain(&sensor, gain) < 0)
        return -1;

    sensor.gain = gain;
    return 0;
}

int sensor_get_flipmirror(FLIP_MIRROR_TYPE_E *type)
{
    if (sensor.enabled)
        return -1;

    *type = sensor.flip_mirror_type;
    return 0;
}

int sensor_set_flipmirror(FLIP_MIRROR_TYPE_E type)
{
    if (sensor.enabled)
        return -1;

    if (type < FLIP_MIRROR_TYPE_NORMAL || type > FLIP_MIRROR_TYPE_FLIP_MIRROR) {
        BL_LOGE("\t sensor_set_flipmirror: invalid flip  mirror value %d!\r\n", type);
        return -1;
    }

    if (sensor.set_flipmirror(&sensor, type) < 0)
        return -1;

    sensor.flip_mirror_type = type;
    return 0;
}

int sensor_get_sensor_reg(uint16_t addr, uint8_t *data)
{
    int ret = 0;

    if (sensor.reg_addr_bit == SENSOR_REG_ADDR_8BIT) {
        ret = SCCB_Read(sensor.slv_addr, (uint8_t)addr, data);
    } else {
        ret = SCCB_Read_Reg16(sensor.slv_addr, addr, data);
    }

    return ret;
}

int sensor_set_sensor_reg(uint16_t addr, uint8_t data)
{
    int ret = 0;

    if (sensor.reg_addr_bit == SENSOR_REG_ADDR_8BIT) {
        ret = SCCB_Write(sensor.slv_addr, (uint8_t)addr, data);
    } else {
        ret = SCCB_Write_Reg16(sensor.slv_addr, addr, data);
    }

    return ret;
}

int  sensor_is_quick_mode()
{
    return sensor.quick_mode.is_quick_mode;
}

int  sensor_quick_mode_get_ae_exposure(BL_EXPO_TIME *expo_time)
{
    if (!sensor.enabled)
        return -1;

    if (!sensor.quick_mode.is_quick_mode)
        return -1;

    if (sensor.quick_mode.get_ae_exposure(&sensor, expo_time) < 0)
        return -1;

    return 0;
}

int  sensor_quick_mode_get_ae_gain(BL_GAIN_DB *gain)
{
    if (!sensor.enabled)
        return -1;

    if (!sensor.quick_mode.is_quick_mode)
        return -1;

    if (sensor.quick_mode.get_ae_gain(&sensor, gain) < 0)
        return -1;

    return 0;
}

int  sensor_quick_mode_get_awb_gain(int *r_gain, int *g_gain, int *b_gain)
{
    if (!sensor.enabled)
        return -1;

    if (!sensor.quick_mode.is_quick_mode)
        return -1;

    if (sensor.quick_mode.get_awb_gain(&sensor, r_gain, g_gain, b_gain) < 0)
        return -1;

    return 0;

}

int sensor_quick_mode_reset()
{
    if (!sensor.enabled)
        return -1;

    if (!sensor.quick_mode.is_quick_mode)
        return -1;

    if (sensor.quick_mode.reset(&sensor) < 0)
        return -1;

    return 0;
}


/************************************* sensor quick mode functions *************************************/


/************************************* helper functions *************************************/
void sensor_print_gain(BL_GAIN_DB gain)
{
    BL_LOGI("\t sensor gain: %.4f dB, gain %.3fx\r\n", GAIN_DB_INT_TO_FLOAT(gain), DB_TO_GAIN(gain));
}

void sensor_print_expo_time(BL_EXPO_TIME expo_time)
{
    BL_LOGI("\t sensor expo time: %d ns or 1/%d sec\r\n", expo_time, EXPO_TIME_TO_INT(expo_time));
}


