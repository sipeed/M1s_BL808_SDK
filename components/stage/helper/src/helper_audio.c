
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <bl60x_i2s.h>
#include <bl60x_gpio.h>
#include <bl60x_glb.h>
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <timers.h>
#include <aos/kernel.h>
#include <aos/yloop.h>
#include <sccb.h>
#include <cli.h>
#include <vfs.h>
#include <sys/fcntl.h>
#include "bl60x_i2s.h"
#include <audio_framework.h>

#include <helper_sdh.h>

#include <helper_media.h>

#include "pub/mp3dec.h"

#include "utils_log.h"

#define I2S_MCLK_GPIO_PIN      GLB_GPIO_PIN_11
#define I2S_MCLK_GPIO_FUN      GPIO11_FUN_I2S0_RCLK_O_I2S0_DI
#define I2S_BCLK_GPIO_PIN      GLB_GPIO_PIN_12
#define I2S_BCLK_GPIO_FUN      GPIO12_FUN_I2S1_BCLK
#define I2S_FS_GPIO_PIN        GLB_GPIO_PIN_29
#define I2S_FS_GPIO_FUN        GPIO29_FUN_I2S1_FS
#define I2S_TX_GPIO_PIN        GLB_GPIO_PIN_30
#define I2S_TX_GPIO_FUN        GPIO30_FUN_I2S1_DIO
#define I2S_RX_GPIO_PIN        GLB_GPIO_PIN_31
#define I2S_RX_GPIO_FUN        GPIO31_FUN_I2S1_RCLK_O_I2S1_DI

#define SD_FILE_NAME_MAX_LEN                (64)

/*
    task_exc_type
        bit0 : play
            0-unuse
            1-use
        bit1 : record
            0-unuse
            1-use
        bit2 : change play_file_name
            0-unuse
            1-use
        bit3 : change play_file_name
            0-unuse
            1-use
        bit4 : enter play_end
            0-unuse
            1-use
        bit5 : enter record_end
            0-unuse
            1-use
*/
#define TASK_EXC_TYPE_INIT                  (0x0000)
#define TASK_EXC_TYPE_PLAY                  (0x0001)
#define TASK_EXC_TYPE_RECORD                (0x0002)
#define TASK_EXC_TYPE_CHANGE_PLAYFD         (0x0004)
#define TASK_EXC_TYPE_CHANGE_RECORDFD       (0x0008)
#define TASK_EXC_TYPE_PLAY_END              (0x0010)
#define TASK_EXC_TYPE_RECORD_END            (0x0020)
#define TASK_EXC_TYPE_PLAYZERO              (0x0040)
#define TASK_EXC_TYPE_LOOP                  (0x0080)

typedef struct {
    TaskHandle_t hdr;               /* task handle */
    uint32_t type;                                  /* task_exc_type */
    uint8_t playname[SD_FILE_NAME_MAX_LEN];         /* task_play_file_name *.pcm */
    uint8_t recordname[SD_FILE_NAME_MAX_LEN];       /* task_record_file_name *.pcm */
    uint8_t fifo[4096];                             /* for play_record_loop */
    uint8_t *cb_txbuf;
    uint16_t cb_txlen;
    // uint32_t cb_txcount; /* for detect count overflow */
    uint8_t *cb_rxbuf;
    uint16_t cb_rxlen;
    // uint32_t cb_rxcount; /* for detect count overflow */
    int32_t record_bytes;
} task_exc_arg_t;

static task_exc_arg_t *task_exc = NULL;

static int task_exc_arg_init(void)
{
    if (NULL != task_exc) {
        log_error("repeat initi ?\r\n");
        return 0;
    }

    task_exc = pvPortMalloc(sizeof(task_exc_arg_t));
    if (NULL == task_exc) {
        log_error("mem err\r\n");
        return -2;
    }

    task_exc->hdr = NULL;

    task_exc->type = TASK_EXC_TYPE_INIT;
    task_exc->type |= TASK_EXC_TYPE_PLAYZERO;

    memset(task_exc->playname, 0, SD_FILE_NAME_MAX_LEN);
    memset(task_exc->playname, 0, SD_FILE_NAME_MAX_LEN);

    memset(task_exc->fifo, 0, 4096);

    task_exc->cb_txbuf = NULL;
    task_exc->cb_txlen = 0;
    // task_exc->cb_txcount = 0;
    task_exc->cb_rxbuf = NULL;
    task_exc->cb_rxlen = 0;
    // task_exc->cb_rxcount = 0;

    task_exc->record_bytes = 0;

    return 0;
}

static void audio_gpio_init(void)
{
    GLB_GPIO_Cfg_Type cfg;
    uint8_t gpiopins[5];
    uint8_t gpiofuns[5];
    uint8_t gpioModes[5];
    uint8_t i=0;

    cfg.gpioMode = GPIO_MODE_AF;
    cfg.pullType = GPIO_PULL_UP;
    cfg.drive = 1;
    cfg.smtCtrl = 1;
    cfg.gpioMode = GPIO_MODE_OUTPUT;


    gpiopins[0] = I2S_BCLK_GPIO_PIN;
    gpiopins[1] = I2S_FS_GPIO_PIN;
    gpiopins[2] = I2S_TX_GPIO_PIN;
    gpiopins[3] = I2S_RX_GPIO_PIN;
    gpiopins[4] = I2S_MCLK_GPIO_PIN;
    gpiofuns[0] = I2S_BCLK_GPIO_FUN;
    gpiofuns[1] = I2S_FS_GPIO_FUN;
    gpiofuns[2] = I2S_TX_GPIO_FUN;
    gpiofuns[3] = I2S_RX_GPIO_FUN;
    gpiofuns[4] = I2S_MCLK_GPIO_FUN;
    gpioModes[0] = GPIO_MODE_OUTPUT;
    gpioModes[1] = GPIO_MODE_OUTPUT;
    gpioModes[2] = GPIO_MODE_OUTPUT;
    gpioModes[3] = GPIO_MODE_INPUT;
    gpioModes[4] = GPIO_MODE_OUTPUT;

    for (i = 0; i < sizeof(gpiopins); i++) {
        cfg.gpioPin = gpiopins[i];
        cfg.gpioFun = gpiofuns[i];
        cfg.gpioMode = gpioModes[i];

        GLB_GPIO_Init(&cfg);
    }
}

static int ES8311_Write_Reg(uint8_t reg, uint8_t val)
{
    SCCB_Write(0x18, reg, &val);

    return 0;
}

static int ES8311_Read_Reg(uint8_t reg, uint8_t *val)
{
    SCCB_Read(0x18, reg, val, 1);

    return 0;
}

static int audio_callback_tx(audio_framework_device_t *device, void *uerdata, uint8_t *audiodata, int len, int is_underrun)
{
    BaseType_t xHigherPriorityTaskWoken;

    if ((NULL == task_exc) || (NULL == task_exc->hdr)) {
        return -1;
    }

    if ((NULL == audiodata) || (4096 != len)) {
        log_error("callback_tx audiodata = 0x%08lx  len = %d\r\n", (uint32_t)audiodata, len);
        return -1;
    }
    if (task_exc->cb_txlen !=0 ) {
        // log_warn("recover cb_txlen = %d\r\n", task_exc->cb_txlen);
    }

    task_exc->cb_txbuf = audiodata;
    task_exc->cb_txlen = len;

    vTaskNotifyGiveFromISR(task_exc->hdr, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);

    return 0;
}

static int audio_callback_rx(audio_framework_device_t *device, void *uerdata, uint8_t *audiodata, int len, int is_underrun)
{
    BaseType_t xHigherPriorityTaskWoken;

    if ((NULL == task_exc) && (NULL == task_exc->hdr)) {
        return -1;
    }

    if ((NULL == audiodata) || (4096 != len)) {
        log_error("audiodata = 0x%08lx  len = %d\r\n", (uint32_t)audiodata, len);
        return -1;
    }
    if (task_exc->cb_rxlen !=0 ) {
        // log_warn("recover cb_rxlen = %d\r\n", task_exc->cb_rxlen);
    }

    task_exc->cb_rxbuf = audiodata;
    task_exc->cb_rxlen = len;

    vTaskNotifyGiveFromISR(task_exc->hdr, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);

    return 0;
}

static void audio_exc_entry(void *pvParameters)
{
    int play_fd = -1;
    int record_fd = -1;

    if ((NULL == task_exc) || (NULL != task_exc->hdr)) {
        log_error("please init hte task_exc arg before enter this thread. or re-start-thred ?\r\n");
        return;
    }
    task_exc->hdr = xTaskGetCurrentTaskHandle();

    while (1) {
        ulTaskNotifyTake(pdFALSE, portMAX_DELAY);

        if (task_exc->type & TASK_EXC_TYPE_CHANGE_PLAYFD) {
            if (play_fd >= 0) {
                aos_close(play_fd);
                play_fd = -1;
            }

            play_fd = aos_open((const char *)task_exc->playname, 0);
            if (play_fd < 0) {
                log_error("open err. fd = %d\r\n", play_fd);
            }

            task_exc->type &= ~TASK_EXC_TYPE_CHANGE_PLAYFD;   /* clear flag */
        }

        if (task_exc->type & TASK_EXC_TYPE_CHANGE_RECORDFD) {
            if (record_fd >= 0) {
                aos_close(record_fd);
                play_fd = -1;
            }

            record_fd = aos_open((const char *)task_exc->recordname, O_RDWR | O_CREAT | O_TRUNC);
            if (record_fd < 0) {
                log_error("open err. fd = %d\r\n", play_fd);
            }

            log_info("open record_fd = %d\r\n", record_fd);

            task_exc->type &= ~TASK_EXC_TYPE_CHANGE_RECORDFD;   /* clear flag */
        }

        if (task_exc->type & TASK_EXC_TYPE_PLAY) {
            if (task_exc->cb_txlen > 0) {
                if ((play_fd < 0) || (task_exc->cb_txbuf == NULL)) {
                    log_error("play fd =%d error\r\n", play_fd);
                } else {
                    while (task_exc->cb_txlen != aos_read(play_fd, task_exc->cb_txbuf, task_exc->cb_txlen)) {
                        task_exc->type |= TASK_EXC_TYPE_PLAY_END;   /* enter play end */
                        break;
                    }
                    log_info("D %02X\r\n", task_exc->cb_txbuf[0]);
                }
                task_exc->cb_txlen = 0;
            }
        }
        if (task_exc->type & TASK_EXC_TYPE_RECORD) {
            if (task_exc->cb_rxlen > 0) {
                if ((record_fd < 0) || (task_exc->cb_rxbuf == NULL)) {
                    log_error("record fd =%d error\r\n", record_fd);
                } else {
                    if (0xEFFFFFFF == task_exc->record_bytes) {
                        aos_write(record_fd, task_exc->cb_rxbuf, task_exc->cb_rxlen);
                        log_info("W %02X %d\r\n", task_exc->cb_rxbuf[0], task_exc->cb_rxlen);
                    } else {
                        if (task_exc->record_bytes > task_exc->cb_rxlen) {
                            aos_write(record_fd, task_exc->cb_rxbuf, task_exc->cb_rxlen);
                            task_exc->record_bytes -= task_exc->cb_rxlen;
                            log_info("W %02X %d\r\n", task_exc->cb_rxbuf[0], task_exc->cb_rxlen);
                        } else {
                            aos_write(record_fd, task_exc->cb_rxbuf, task_exc->record_bytes);
                            log_info("W %02X %ld\r\n", task_exc->cb_rxbuf[0], task_exc->record_bytes);
                            task_exc->record_bytes = 0;
                            task_exc->type |= TASK_EXC_TYPE_RECORD_END; /* enter record end */
                        }
                    }
                }
                task_exc->cb_rxlen = 0;
            }
        }
        if (task_exc->type & TASK_EXC_TYPE_PLAY_END) {
            if (play_fd > 0) {
                // aos_lseek(play_fd, 0, SEEK_SET);
                aos_close(play_fd);
                play_fd = -1;
            }

            log_info("enter play_end close play_fd = %d\r\n", play_fd);
            task_exc->type &= ~TASK_EXC_TYPE_PLAY;                  /* clear flag */
            task_exc->type &= ~TASK_EXC_TYPE_PLAY_END;              /* clear flag */
            task_exc->type |= TASK_EXC_TYPE_PLAYZERO;               /* enter play zero */
        }
        if (task_exc->type & TASK_EXC_TYPE_RECORD_END) {
            if (record_fd > 0) {
                aos_close(record_fd);
                record_fd = -1;
            }

            log_info("enter record_end close record_fd = %d\r\n", record_fd);
            task_exc->type &= ~TASK_EXC_TYPE_RECORD;                /* clear flag */
            task_exc->type &= ~TASK_EXC_TYPE_RECORD_END;            /* clear flag */
        }
        if (task_exc->type & TASK_EXC_TYPE_PLAYZERO) {
            if (task_exc->cb_txlen > 0) {
                if (task_exc->cb_txbuf != NULL) {
                    // log_info("D SET ZERO\r\n");
                    memset(task_exc->cb_txbuf, 0, task_exc->cb_txlen);
                    task_exc->cb_txlen = 0;
                }
            }
        }
        if (task_exc->type & TASK_EXC_TYPE_LOOP) {

            if (task_exc->cb_txlen == 4096) {
                log_info("tx filo -> tx\r\n");
                memcpy(task_exc->cb_txbuf, task_exc->fifo , 4096);
                task_exc->cb_txlen = 0;
            }
            if (task_exc->cb_rxlen == 4096) {
                log_info("tx rx -> fifo\r\n");
                memcpy(task_exc->fifo, task_exc->cb_rxbuf , 4096);
                task_exc->cb_rxlen = 0;
            }
        }
    }
}

static int audiofw_config(void)
{
    audio_framework_device_t *device;
    int size = 0, ret;

    if (0 != task_exc_arg_init()) {    /* init task_exc arg */
        log_error("fw config err.\r\n");
        return -1;
    }
    audio_gpio_init();  /* init gpio */
    SCCB_Init();        /* init i2c */

    if (audio_framework_factory_build("bl60x_i2s", &device)) {
        log_info("Request I2S device bl60x_i2s failed\r\n ");
    } else {
        log_info("Request I2S device bl60x_i2s @%p\r\n", device);

        /*Init audio device*/
        device->init(device);

        /*Set parameter of audio device*/
        device->set_buffersize_rx(device, 1024 * 8, &size);
        log_info("[AUDIO] buffer size rx: %d\r\n", size);

        device->set_buffersize_tx(device, 1024 * 8, &size);
        log_info("[AUDIO] buffer size tx: %d\r\n", size);

        ret = device->set_samplerate(device, AUDIO_FRAMEWORK_SAMPLERATE_16K);
        log_info("[AUDIO] Configuring sample rate default 16k, ret =%d \r\n", ret);

        ret = device->set_format(device, AUDIO_FRAMEWORK_FORMAT_DATA16BIT_WIDTH16BIT_STERO);
        log_info("[AUDIO] Configuring format default DATA16BIT_WIDTH16BIT_STERO, ret = %d\r\n", ret);

        device->set_txcallback(device, audio_callback_tx);
        device->set_rxcallback(device, audio_callback_rx);
        log_info("[AUDIO] applying config rx_tx cb\r\n");

        /*Set apply settings to hardware*/
        ret = device->config(device);
        log_info("update device config, ret = %d\r\n", ret);

        /*Start audio device streaming*/
        ret = device->start(device);
        log_info("[AUDIO] Starting device, ret = %d\r\n", ret);

        aos_task_new("audio", audio_exc_entry, NULL, 2048);
    }
    return 0;
}

typedef enum {
    ES8311_12M288_8K = 0,
    ES8311_12M288_12K,
    ES8311_12M288_16K,
    ES8311_12M288_24K,
    ES8311_12M288_32K,
    ES8311_12M288_48K,
    ES8311_11M2896_11K025,
    ES8311_11M2896_22K05,
    ES8311_11M2896_44K1,
    ES8311_24M576_16K,
    ES8311_24M576_24K,
    ES8311_24M576_32K,
    ES8311_24M576_48K
} es8311_config_t;

static void config_es8311_reg(es8311_config_t es_config)
{
    uint8_t dataSizeCfg = 3;
    uint8_t dataModeCfg = 0;

    /* Reset codec*/
    ES8311_Write_Reg(0x00,0x1F);
    ES8311_Write_Reg(0x45,0x00);
    /*set ADC/DAC CLK*/
    ES8311_Write_Reg(0x01,0x30);//set mclkin,clk_adc/clk_dac
    ES8311_Write_Reg(0x02,0x10);

    switch (es_config) {
        case ES8311_12M288_8K:
        {
            log_info("Set ES8311_12M288_8K.\r\n");
            ES8311_Write_Reg(0x02,0xA0);
            ES8311_Write_Reg(0x03,0x10);
            ES8311_Write_Reg(0x04,0x10);
            ES8311_Write_Reg(0x16,0x24);
        }
        break;
        case ES8311_12M288_12K:
        {
            log_info("Set ES8311_12M288_12K.\r\n");
            ES8311_Write_Reg(0x02,0x60);
            ES8311_Write_Reg(0x03,0x10);
            ES8311_Write_Reg(0x04,0x10);
            ES8311_Write_Reg(0x16,0x24);
        }
        break;
        case ES8311_12M288_16K:
        {
            log_info("Set ES8311_12M288_16K.\r\n");
            ES8311_Write_Reg(0x02,0x40);
            ES8311_Write_Reg(0x03,0x10);
            ES8311_Write_Reg(0x04,0x10);
            ES8311_Write_Reg(0x16,0x24);
        }
        break;
        case ES8311_12M288_24K:
        {
            log_info("Set ES8311_12M288_24K.\r\n");
            ES8311_Write_Reg(0x02,0x20);
            ES8311_Write_Reg(0x03,0x10);
            ES8311_Write_Reg(0x04,0x10);
            ES8311_Write_Reg(0x16,0x24);
        }
        break;
        case ES8311_12M288_32K:
        {
            log_info("Set ES8311_12M288_32K.\r\n");
            ES8311_Write_Reg(0x02,0x00);
            ES8311_Write_Reg(0x03,0x18);
            ES8311_Write_Reg(0x04,0x18);
            ES8311_Write_Reg(0x16,0x21);
        }
        break;
        case ES8311_12M288_48K:
        {
            log_info("Set ES8311_12M288_48K.\r\n");
            ES8311_Write_Reg(0x02,0x00);
            ES8311_Write_Reg(0x03,0x10);
            ES8311_Write_Reg(0x04,0x10);
            ES8311_Write_Reg(0x16,0x24);
        }
        break;
        case ES8311_11M2896_11K025:
        {
            log_info("Set ES8311_11M2896_11K025.\r\n");
            ES8311_Write_Reg(0x02,0x60);
            ES8311_Write_Reg(0x03,0x10);
            ES8311_Write_Reg(0x04,0x10);
            ES8311_Write_Reg(0x16,0x24);
        }
        break;
        case ES8311_11M2896_22K05:
        {
            log_info("Set ES8311_11M2896_22K05.\r\n");
            ES8311_Write_Reg(0x02,0x20);
            ES8311_Write_Reg(0x03,0x10);
            ES8311_Write_Reg(0x04,0x10);
            ES8311_Write_Reg(0x16,0x24);
        }
        break;
        case ES8311_11M2896_44K1:
        {
            log_info("Set ES8311_11M2896_44K1.\r\n");
            ES8311_Write_Reg(0x02,0x00);
            ES8311_Write_Reg(0x03,0x10);
            ES8311_Write_Reg(0x04,0x10);
            ES8311_Write_Reg(0x16,0x24);
        }
        break;
        default:
        {
            log_error("unknow es_config.\r\n");
        }
        break;
    }
    ES8311_Write_Reg(0x05,0x00);//set adc_mclk,dac_mclk

    /*set system power up*/
    ES8311_Write_Reg(0x0B,0x00);//power up stage A/B time
    ES8311_Write_Reg(0x0C,0x00);//power up stage B/C time
    ES8311_Write_Reg(0x10,0x1F);//set vmid/ibias
    ES8311_Write_Reg(0x11,0x7F);//set vsel
    ES8311_Write_Reg(0x00,0x80);//chip powerup,master mode(0xC2)

    vTaskDelay(50);

    ES8311_Write_Reg(0x0D,0x01);//power up analog
    ES8311_Write_Reg(0x01,0x3F);//power up digital,include ADC

    ES8311_Write_Reg(0x14,0x1A);
    /*set dac*/
    ES8311_Write_Reg(0x12,0x00);
    /*enable HP drive */
    ES8311_Write_Reg(0x13,0x10);
    /*set dac data format*/
    ES8311_Write_Reg(0x09,0x00|(dataSizeCfg<<2)|(dataModeCfg));//set dac format=16bit i2s
    /*set dac data format*/
    ES8311_Write_Reg(0x0A,0x00|(dataSizeCfg<<2)|(dataModeCfg));//set adc format=16bit i2s

    ES8311_Write_Reg(0x0E,0x02);//enable analog pga/adc modulator
    /*set low power mode*/
    //ES8311_Write_Reg(0x0F,0x7F);
    //Disable low power mode
    ES8311_Write_Reg(0x0F,0x00);
    /*set adc */
    ES8311_Write_Reg(0x15,0x40);//set softramp//ES8311_Write_Reg(0x15,0xA0);//set softramp
    ES8311_Write_Reg(0x1B,0x0a);//set adc hpf
    ES8311_Write_Reg(0x1C,0x6A);//set adc hpf,ADC_EQ bypass
    ES8311_Write_Reg(0x17,0xBF);//set adc digtal vol
    /*set dac */
    ES8311_Write_Reg(0x37,0x48);//set dac softramp,disable DAC_EQ
    ES8311_Write_Reg(0x32,0xBF);
    /*set adc/dac data form*/
    ES8311_Write_Reg(0x44,0x08);//adc to dac disable,ADCDATA=ADC(L)+ADC(R)

    /*only set adc alc funtion for amic record*/
    //ES8311_Write_Reg(0x16,0x22);//set adc gain scale up
    ES8311_Write_Reg(0x16,0x24);//set adc gain scale up
    ES8311_Write_Reg(0x17,0xCF);//set adc alc maxgain
    ES8311_Write_Reg(0x18,0x0A);//adc alc enable,alc_winsize//ES8311_Write_Reg(0x18,0x87);//adc alc enable,alc_winsize
    ES8311_Write_Reg(0x19,0xFB);//set alc target level

    ES8311_Write_Reg(0x1A,0x03);//set adc_automute noise gate
    ES8311_Write_Reg(0x1B,0xEA);//set adc_automute vol
}

static void es8311_config(char *arg)
{
    if (!arg) {
        log_info("es8311_config\r\n");
    } else {
        log_info("es8311_config %s\r\n", arg);
    }

    if (!arg) {
        log_info("no arg, use default config(16k).\r\n");
        config_es8311_reg(ES8311_12M288_16K);
        return;
    }

    if ((strstr(arg, "12M288_8K") != 0)&&(strstr(arg, "24M576_48K") == 0)) {
        config_es8311_reg(ES8311_12M288_8K);
    } else if (strstr(arg, "12M288_12K") != 0) {
        config_es8311_reg(ES8311_12M288_12K);
    } else if (strstr(arg, "12M288_16K") != 0) {
        config_es8311_reg(ES8311_12M288_16K);
    } else if (strstr(arg, "12M288_24K") != 0) {
        config_es8311_reg(ES8311_12M288_24K);
    } else if (strstr(arg, "12M288_32K") != 0) {
        config_es8311_reg(ES8311_12M288_32K);
    } else if (strstr(arg, "12M288_48K") != 0) {
        config_es8311_reg(ES8311_12M288_48K);
    } else if (strstr(arg, "11M2896_11K025") != 0) {
        config_es8311_reg(ES8311_11M2896_11K025);
    } else if (strstr(arg, "11M2896_22K05") != 0) {
        config_es8311_reg(ES8311_11M2896_22K05);
    } else if (strstr(arg, "11M2896_44K1") != 0) {
        config_es8311_reg(ES8311_11M2896_44K1);
    }else if (strstr(arg, "24M576_16K") != 0) {
        config_es8311_reg(ES8311_24M576_16K);
    }else if (strstr(arg, "24M576_24K") != 0) {
        config_es8311_reg(ES8311_24M576_24K);
    }else if (strstr(arg, "24M576_32K") != 0) {
        config_es8311_reg(ES8311_24M576_32K);
    }else if (strstr(arg, "24M576_48K") != 0) {
        config_es8311_reg(ES8311_24M576_48K);
    } else {
        log_error("arg err.\r\n");
        return;
    }
}

static void i2s_config(char *arg)
{
    audio_framework_device_t *device;
    int ret;

    if (!arg) {
        log_info("i2s_config\r\n");
    } else {
        log_info("i2s_config %s\r\n", arg);
    }

    if (audio_framework_factory_build("bl60x_i2s", &device)) {
        log_error("Request I2S device bl60x_i2s failed\r\n ");
        return;
    }

    if (!arg) {
        log_info("no arg, use default config(16k).\r\n");
        device->set_mclk(device, 12288000);
        ret = device->reset_samplerate(device, AUDIO_FRAMEWORK_SAMPLERATE_16K);
        if (ret != 0) {
            log_error("reset_samplerate err.\r\n");
        }
        return;
    }

    if (strstr(arg, "12M288_8K") != 0) {
        device->set_mclk(device, 12288000);
        ret = device->reset_samplerate(device, AUDIO_FRAMEWORK_SAMPLERATE_8K);
    } else if (strstr(arg, "12M288_12K") != 0) {
        device->set_mclk(device, 12288000);
        ret = device->reset_samplerate(device, AUDIO_FRAMEWORK_SAMPLERATE_12K);
    } else if (strstr(arg, "12M288_16K") != 0) {
        device->set_mclk(device, 12288000);
        ret = device->reset_samplerate(device, AUDIO_FRAMEWORK_SAMPLERATE_16K);
    } else if (strstr(arg, "12M288_24K") != 0) {
        device->set_mclk(device, 12288000);
        ret = device->reset_samplerate(device, AUDIO_FRAMEWORK_SAMPLERATE_24K);
    } else if (strstr(arg, "12M288_32K") != 0) {
        device->set_mclk(device, 12288000);
        ret = device->reset_samplerate(device, AUDIO_FRAMEWORK_SAMPLERATE_32K);
    } else if (strstr(arg, "12M288_48K") != 0) {
        device->set_mclk(device, 12288000);
        ret = device->reset_samplerate(device, AUDIO_FRAMEWORK_SAMPLERATE_48K);
    }else if (strstr(arg, "24M576_16K") != 0) {
        device->set_mclk(device, 24576000);
        ret = device->reset_samplerate(device, AUDIO_FRAMEWORK_SAMPLERATE_16K);
    } else if (strstr(arg, "24M576_24K") != 0) {
        device->set_mclk(device, 24576000);
        ret = device->reset_samplerate(device, AUDIO_FRAMEWORK_SAMPLERATE_24K);
    }else if (strstr(arg, "24M576_32K") != 0) {
        device->set_mclk(device, 24576000);
        ret = device->reset_samplerate(device, AUDIO_FRAMEWORK_SAMPLERATE_32K);
    }else if (strstr(arg, "24M576_48K") != 0) {
        device->set_mclk(device, 24576000);
        ret = device->reset_samplerate(device, AUDIO_FRAMEWORK_SAMPLERATE_48K);
    } else if (strstr(arg, "11M2896_11K025") != 0) {
        device->set_mclk(device, 11289600);
        ret = device->reset_samplerate(device, AUDIO_FRAMEWORK_SAMPLERATE_11P025K);
    } else if (strstr(arg, "11M2896_22K05") != 0) {
        device->set_mclk(device, 11289600);
        ret = device->reset_samplerate(device, AUDIO_FRAMEWORK_SAMPLERATE_22P05K);
    } else if (strstr(arg, "11M2896_44K1") != 0) {
        device->set_mclk(device, 11289600);
        ret = device->reset_samplerate(device, AUDIO_FRAMEWORK_SAMPLERATE_44P1K);
    } else {
        log_error("arg err.\r\n");
        return;
    }

    if (ret != 0) {
        log_error("reset_samplerate err.\r\n");
    }
}

static void cmd_audio_config(char *buf, int len, int argc, char **argv)
{
    static char fw_init = 0;

    if (!fw_init) {
        if (0 != audiofw_config()) {
            log_error("audio config err.\r\n");
            return;
        }
        fw_init = 1;
    }

    if (2 == argc) {
        if ((strstr(argv[1], "48k") != 0) || (strstr(argv[1], "48K") != 0)) {
            es8311_config("12M288_48K");
            i2s_config("12M288_48K");
        } else if ((strstr(argv[1], "8k") != 0) || (strstr(argv[1], "8K") != 0)) {
            es8311_config("12M288_8K");
            i2s_config("12M288_8K");
        } else if ((strstr(argv[1], "12k") != 0) || (strstr(argv[1], "12K") != 0)) {
            es8311_config("12M288_12K");
            i2s_config("12M288_12K");
        } else if ((strstr(argv[1], "16k") != 0) || (strstr(argv[1], "16K") != 0)) {
            es8311_config("12M288_16K");
            i2s_config("12M288_16K");
        } else if ((strstr(argv[1], "24k") != 0) || (strstr(argv[1], "24K") != 0)) {
            es8311_config("12M288_24K");
            i2s_config("12M288_24K");
        } else if ((strstr(argv[1], "32k") != 0) || (strstr(argv[1], "32K") != 0)) {
            es8311_config("12M288_32K");
            i2s_config("12M288_32K");
        } else if ((strstr(argv[1], "11p025") != 0) || (strstr(argv[1], "11P025") != 0)) {
            es8311_config("11M2896_11K025");
            i2s_config("11M2896_11K025");
        } else if ((strstr(argv[1], "22p05") != 0) || (strstr(argv[1], "22P05") != 0)) {
            es8311_config("11M2896_22K05");
            i2s_config("11M2896_22K05");
        } else if ((strstr(argv[1], "44p1") != 0) || (strstr(argv[1], "44P1") != 0)) {
            es8311_config("11M2896_44K1");
            i2s_config("11M2896_44K1");
        }
    } else {
        log_info("use default.\r\n");
        es8311_config(NULL);
        i2s_config(NULL);
        return;
    }
}

static void cmd_audio_play(char *buf, int len, int argc, char **argv)
{
    char path[SD_FILE_NAME_MAX_LEN];

    if (NULL == task_exc) {
        log_error("please config it before play.\r\n");
        return;
    }

    /* use default name */
    if (1 == argc) {
        log_info("no arg, use default name(play.pcm).\r\n");
        memset(path, 0, sizeof(path));
        memcpy(path, "/sdcard/play.pcm", sizeof("/sdcard/play.pcm"));
        memcpy(task_exc->playname, path, SD_FILE_NAME_MAX_LEN);
    }

    /* use config name */
    if (2 == argc) {
        memset(path, 0, sizeof(path));
        snprintf(path, sizeof(path), "/sdcard/%s", argv[1]);
        path[sizeof(path) - 1] = '\0';
        memcpy(task_exc->playname, path, SD_FILE_NAME_MAX_LEN);
    }

    log_info("play_file_name = %s\r\n", task_exc->playname);

    task_exc->type &= ~TASK_EXC_TYPE_PLAYZERO;
    task_exc->type |= TASK_EXC_TYPE_CHANGE_PLAYFD | TASK_EXC_TYPE_PLAY;
}

static void cmd_audio_record(char *buf, int len, int argc, char **argv)
{
    char path[SD_FILE_NAME_MAX_LEN];

    if (NULL == task_exc) {
        log_error("please config it before record.\r\n");
        return;
    }

    if ((1 != argc) && (2 != argc)) {
        log_error("arg err.\r\n");
        return;
    }

    /* use default name */
    if (1 == argc) {
        log_info("no arg, use default name(record.pcm).\r\n");
        memset(path, 0, sizeof(path));
        memcpy(path, "/sdcard/record.pcm", sizeof("/sdcard/record.pcm"));
        memcpy(task_exc->recordname, path, SD_FILE_NAME_MAX_LEN);
    }

    /* use config name */
    if (2 == argc) {
        memset(path, 0, sizeof(path));
        snprintf(path, sizeof(path), "/sdcard/%s", argv[1]);
        path[sizeof(path) - 1] = '\0';
        memcpy(task_exc->recordname, path, SD_FILE_NAME_MAX_LEN);
    }

    task_exc->record_bytes = 4096 * 100;

    log_info("record_file_name = %s len = %ld\r\n", task_exc->recordname, task_exc->record_bytes);

    task_exc->type |= TASK_EXC_TYPE_CHANGE_RECORDFD | TASK_EXC_TYPE_RECORD | TASK_EXC_TYPE_PLAYZERO;
}
static void cmd_audio_loop(char *buf, int len, int argc, char **argv)
{
    task_exc->type = TASK_EXC_TYPE_LOOP;
}
static int32_t get_filesize(uint8_t *file_name)
{
    int file_fd;
    int32_t file_size;

    if (NULL == file_name) {
        log_error("arg err\r\n");
        return -1;
    }

    file_fd = aos_open((const char *)file_name, 0);
    file_size = aos_lseek(file_fd, 0, SEEK_END);
    aos_close(file_fd);

    return file_size;
}

static void cmd_audio_playrecord(char *buf, int len, int argc, char **argv)
{
    int32_t file_size;
    char path[SD_FILE_NAME_MAX_LEN];

    if (NULL == task_exc) {
        log_error("please config it before playrecord.\r\n");
        return;
    }

    /* use default name */
    if (1 == argc) {
        log_info("no arg, use default name(play.pcm record.pcm).\r\n");
        memset(task_exc->playname, 0, SD_FILE_NAME_MAX_LEN);
        memcpy(task_exc->playname, "/sdcard/play.pcm", sizeof("/sdcard/play.pcm"));
        memset(task_exc->recordname, 0, SD_FILE_NAME_MAX_LEN);
        memcpy(task_exc->recordname, "/sdcard/record.pcm", sizeof("/sdcard/record.pcm"));
        task_exc->record_bytes = 0xEFFFFFFF;
    }

    /* use config name */
    if (3 == argc) {
        memset(path, 0, sizeof(path));
        snprintf(path, sizeof(path), "/sdcard/%s", argv[1]);
        path[sizeof(path) - 1] = '\0';
        memcpy(task_exc->playname, path, SD_FILE_NAME_MAX_LEN);

        memset(path, 0, sizeof(path));
        snprintf(path, sizeof(path), "/sdcard/%s", argv[2]);
        path[sizeof(path) - 1] = '\0';
        memcpy(task_exc->recordname, path, SD_FILE_NAME_MAX_LEN);

        file_size = get_filesize(task_exc->playname);
        log_info("file_size = %ld\r\n", file_size);
        task_exc->record_bytes = file_size;
    }

    log_info("play_file_name = %s\r\n", task_exc->playname);
    log_info("record_file_name = %s\r\n", task_exc->recordname);

    task_exc->type |= TASK_EXC_TYPE_PLAYZERO;
    task_exc->type |= TASK_EXC_TYPE_CHANGE_PLAYFD | TASK_EXC_TYPE_PLAY |\
                        TASK_EXC_TYPE_CHANGE_RECORDFD | TASK_EXC_TYPE_RECORD;
}

static void cmd_audio_regdump(char *buf, int len, int argc, char **argv)
{
    int i;
    uint8_t tmp;

    static uint8_t buffer[29] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x09, 0x0a, 0x0b, 0x0c,
        0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16,
        0x17, 0x18, 0x19, 0x1a, 0x1b, 0x32, 0x37, 0x44, 0x45
    };
    static uint8_t val[29];

    memset(val, 0, sizeof(val));

    for (i = 0; i < sizeof(buffer); i++) {
        ES8311_Read_Reg(buffer[i], &tmp);
        val[i] = tmp;
    }

    log_info("i2x reg table:\r\n");
    log_buf(buffer, sizeof(buffer));

    log_info("i2x val table:\r\n");
    log_buf(val, sizeof(val));
}

// STATIC_CLI_CMD_ATTRIBUTE makes this(these) command(s) static
const struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
    { "audio_config", "audio_config 8k", cmd_audio_config},
    { "audio_play", "audio_play test.pcm", cmd_audio_play},
    { "audio_record", "audio_record test.pcm", cmd_audio_record},
    { "audio_playrecord", "audio_playrecord play.pcm record.pcm", cmd_audio_playrecord},
    { "audio_loop", "audio_loop", cmd_audio_loop},
    { "audio_regdump", "audio_regdump", cmd_audio_regdump},
};

int helper_audio_cli_init(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user)/sizeof(cmds_user[0]));
    return 0;
}
