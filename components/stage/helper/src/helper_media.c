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
#include <audio_framework.h>

#include <helper_media.h>

#include "pub/mp3dec.h"

#include "utils_log.h"

#include "cpu1.h"

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

#define PCM_ONE_BUF_SZ  (2560 * 2)
#define PCM_BUF_SZ      (PCM_ONE_BUF_SZ * 3)

#define FILE_BUF_SZ     (5 * 1024)          /*5K*/

TaskHandle_t audio_task_handle;

typedef struct _media_type {
    audio_framework_device_t *audio_fw_device;
    int current_sample_rate;

    /* record */
    TaskHandle_t record_handle;
    uint8_t *record_buf;
    uint32_t record_len;
    uint8_t record_flag;            /* 0_NULL, 1-ready_record 1-recording */

    TaskHandle_t audio_handle;      /* audio fetch task_hd */
    uint8_t *audio_buf;             /* tmp point to dma_src */
    int audio_len;                  /* tmp dma_src need size */
    uint8_t audio_flag;             /* 0_NULL, 1-ready_record 1-recording */

    /* pcm buff from decode */
    uint8_t *pcm_buf;
    uint32_t pcm_bytes_left;
    uint32_t pcm_bytes_maxsize;

    /* mp3 information */
    HMP3Decoder decoder;
    MP3FrameInfo frame_info;

    /* mp3 file descriptor */
    int fd_music;
    int (*fetch_data)(int fd, void *buffer, int length);

    /* mp3 read session */
    uint8_t *file_buf;
    uint32_t file_bytes_left;
    uint32_t file_bytes_maxsize;
} media_type_t;

static media_type_t *media_ptr = NULL;

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

static int ES8311_Write_Reg(uint8_t reg, uint8_t val)
{
    SCCB_Write(0x18, reg, &val);

    return 0;
}

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

static void audio_gpio_init(void)
{
    GLB_GPIO_Cfg_Type cfg;
    uint8_t gpiopins[5];
    uint8_t gpiofuns[5];
    uint8_t gpioModes[5];
    uint8_t i;

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

static int audio_callback_tx(audio_framework_device_t *device, void *uerdata, uint8_t *audiodata, int len, int is_underrun)
{
    BaseType_t xHigherPriorityTaskWoken;

    // log_info("tx\r\n");
    if (media_ptr->audio_flag == 2) {
        // puts("Notify ");
        media_ptr->audio_buf = audiodata;
        media_ptr->audio_len = len;

        vTaskNotifyGiveFromISR(media_ptr->audio_handle, &xHigherPriorityTaskWoken);
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }

    return 0;
}

static int audio_callback_rx(audio_framework_device_t *device, void *uerdata, uint8_t *audiodata, int len, int is_underrun)
{
    BaseType_t xHigherPriorityTaskWoken;
    // log_info("rx\r\n");
    if (media_ptr->record_flag == 2) {
        // puts("Notify ");
        media_ptr->record_buf = audiodata;
        media_ptr->record_len = len;

        vTaskNotifyGiveFromISR(media_ptr->record_handle, &xHigherPriorityTaskWoken);
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }

    return 0;
}

uint8_t *pcm_buf_get_startptr(media_type_t *ptr)
{
    if (!ptr) {
        return 0;
    }

    return (ptr->pcm_buf + ptr->pcm_bytes_left);
}

int pcm_buf_pop_4k(media_type_t *ptr, uint8_t *buf)
{
    if (ptr->pcm_bytes_left < 4096) {
        return -1;
    }

    memmove(buf, ptr->pcm_buf, 4096);

    log_info("ptr->pcm_buf[] = %02x %02x %02x %02x ...\r\n",
        ptr->pcm_buf[0],  ptr->pcm_buf[1],  ptr->pcm_buf[2], ptr->pcm_buf[3]);

    ptr->pcm_bytes_left -= 4096;
    if (ptr->pcm_bytes_left > 0) {
        memmove(ptr->pcm_buf, ptr->pcm_buf + 4096, ptr->pcm_bytes_left);
    }
    return 0;
}

int pcm_buf_push_end(media_type_t *ptr, int len)
{
    if (ptr->pcm_bytes_left + len >= ptr->pcm_bytes_maxsize) {
        return -1;
    }
    ptr->pcm_bytes_left += len;
    return 0;
}

int pcm_buf_get_used_size(media_type_t *ptr)
{
    return (ptr->pcm_bytes_left);
}

/* */
typedef struct _mp3_decoder_str {
    HMP3Decoder hMP3Decoder;
    unsigned char **inbuf;
    int *bytesLeft;
    short *outbuf;
    int useSize;
} mp3_decoder_str_t;

mp3_decoder_str_t g_decoder_arg ATTR_ACP_SWAP_BSS;

/*called on CPU1*/
static void ATTR_CPU1_CODE _decodemp3_on_cpu1(void *arg)
{
    int *ptmp_err = (int *)arg;
    printf("[SMP] remote function call test, \r\n");
    *ptmp_err = MP3Decode(g_decoder_arg.hMP3Decoder, g_decoder_arg.inbuf, g_decoder_arg.bytesLeft,
            g_decoder_arg.outbuf, g_decoder_arg.useSize);
}

/*called on CPU0 IRQ*/
static void _func_notify_cpu0(void *arg)
{
    BaseType_t xHigherPriorityTaskWoken;
    TaskHandle_t task_handle = (TaskHandle_t)arg;

    vTaskNotifyGiveFromISR(task_handle, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

/*called on CPU1*/
static void ATTR_CPU1_CODE _cb_on_cpu1(void *arg)
{
    TaskHandle_t task_handle = (TaskHandle_t)arg;
    cpu_task_arg_t task_arg;

    printf("[SMP] function cb called, task handle is %p\r\n", task_handle);

    cpu_build_tskarg(&task_arg, CPU_TASK_TYPE_REALT, NULL, 0, 0);
    cpu0_task_deploy(_func_notify_cpu0, task_handle, NULL, NULL, &task_arg, NULL);
}

/* */
#define FILE_SDH_ALIGN          (64)
#define FILE_MP3_ONEPACK_MAX    (1152)
#define FILE_MP3_BUF_SIZE       (FILE_MP3_ONEPACK_MAX * 3)

static int mp3_decoder_run2(void)
{
    media_type_t *ptr = media_ptr;
    int i;
    int bytes_read;
    int tmp_offset;
    int tmp_err;
    int tmp_len;
    uint8_t *tmp_buf;
    // int res;

    for (i = 0; ; i++) {
        /* file fill data */
        log_debug("[%d]file_bytes_left = %ld\r\n", i, ptr->file_bytes_left);
        if (ptr->file_bytes_left < FILE_MP3_ONEPACK_MAX) {
            if (0 == (ptr->file_bytes_left % 64)) {
                // log_info("[%d]file_bytes_left = %ld\r\n", i, ptr->file_bytes_left);
                bytes_read = aos_read(ptr->fd_music, (ptr->file_buf + ptr->file_bytes_left), FILE_MP3_ONEPACK_MAX);
                if (bytes_read == FILE_MP3_ONEPACK_MAX) {

                    ptr->file_bytes_left += FILE_MP3_ONEPACK_MAX;
                    log_info("file_bytes_left = %ld\r\n", ptr->file_bytes_left);       // delete
                    // log_debug("file_buf addr = 0x%08lx 0x%x\r\n", (uint32_t)ptr->file_buf, ptr->file_buf[0]);  // delete
                    // log_info("media_ptr->file_buf 0x%08lx\r\n", (uint32_t)media_ptr->file_buf); // delete
                    // log_buf(ptr->file_buf, ptr->file_bytes_left);                       // delete
                    // aos_msleep(3000);                                                   // delete

                } else {
                    log_error("can't read %d btyes.\r\n", FILE_MP3_ONEPACK_MAX);
                    log_info("lseek SEEK_SET ************************************************** \r\n");
#if 0
                    // return -1;
#else
                    aos_lseek(ptr->fd_music, 0, SEEK_SET);
                    continue;
#endif
                }
            } else {
                log_debug("[%d]file_bytes_left = %ld\r\n", i, ptr->file_bytes_left);
                bytes_read = aos_read(ptr->fd_music, (ptr->file_buf + (FILE_MP3_ONEPACK_MAX * 2)), FILE_MP3_ONEPACK_MAX);
                if (bytes_read == FILE_MP3_ONEPACK_MAX) {
                    memmove((ptr->file_buf + ptr->file_bytes_left), (ptr->file_buf + (FILE_MP3_ONEPACK_MAX * 2)), FILE_MP3_ONEPACK_MAX);
                    ptr->file_bytes_left += FILE_MP3_ONEPACK_MAX;

                    log_debug("file_bytes_left = %ld\r\n", ptr->file_bytes_left);        // delete
                    // log_debug("file_buf addr = 0x%08lx 0x%x\r\n", (uint32_t)ptr->file_buf, ptr->file_buf[0]);  // delete
                    // log_info("media_ptr->file_buf 0x%08lx\r\n", (uint32_t)media_ptr->file_buf); // delete
                    // log_buf(ptr->file_buf, ptr->file_bytes_left);                       // delete
                    // aos_msleep(3000);                                                   // delete

                } else {
                    log_error("can't read %d btyes.\r\n", FILE_MP3_ONEPACK_MAX);
                    return -1;
                }
            }
        }

        /* find sync word */
        log_info(" 0x%08lx[%ld] %02x %02x %02x %02x %02x %02x ...\r\n", (uint32_t)ptr->file_buf, ptr->file_bytes_left,
        ptr->file_buf[0], ptr->file_buf[1], ptr->file_buf[2], ptr->file_buf[3], ptr->file_buf[4], ptr->file_buf[5]);
        tmp_offset = MP3FindSyncWord(ptr->file_buf, ptr->file_bytes_left);

        if ((tmp_offset > ptr->file_bytes_left) || (tmp_offset < 0)) {
            log_error("it's impossible. tmp_offset = %d\r\n", tmp_offset);
            log_buf(ptr->file_buf, ptr->file_bytes_left);
            aos_msleep(1000);
            if (tmp_offset < 0) {
                ptr->file_bytes_left = 0;
                continue;
            }
            return -1;
        }

        if (tmp_offset > 0) {
            /* reset file data and continue */
            if ((ptr->file_bytes_left - tmp_offset) > 0) {
                memmove(ptr->file_buf, (ptr->file_buf + tmp_offset), (ptr->file_bytes_left - tmp_offset));
            }
            ptr->file_bytes_left -= tmp_offset;
            log_debug("tmp_offset = %d\r\n", tmp_offset);
            continue;
        }

        /* decode mp3 data */
        // log_debug("decode mp3 data.\r\n");
        tmp_len = ptr->file_bytes_left;
        if (0 == pcm_buf_get_startptr(ptr)) {
            log_debug("pcm_buf_get_startptr err.\r\n");
            return -1;
        }

        tmp_buf = ptr->file_buf;
        log_info("pcm_buf_get_startptr(ptr) = 0x%08lx\r\n", (uint32_t)pcm_buf_get_startptr(ptr));
        #if 0
        {
            tmp_err = MP3Decode(ptr->decoder, &(ptr->file_buf), &tmp_len,
            (short *)pcm_buf_get_startptr(ptr), 0);
        }
        #else
        {
            TaskHandle_t task_handle;
            cpu_task_arg_t task_arg;

            task_handle = xTaskGetCurrentTaskHandle();

            {
                g_decoder_arg.hMP3Decoder = ptr->decoder;
                g_decoder_arg.inbuf = &(ptr->file_buf);
                g_decoder_arg.bytesLeft = &tmp_len;
                g_decoder_arg.outbuf = (short *)pcm_buf_get_startptr(ptr);
                g_decoder_arg.useSize = 0;
            }

            cpu_build_tskarg(&task_arg, CPU_TASK_TYPE_BACKG, NULL, 0, 0);
            cpu1_task_deploy(_decodemp3_on_cpu1, (void*)&tmp_err,
                _cb_on_cpu1, task_handle, &task_arg,
                NULL, 1000);
            ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        }
        #endif

        ptr->file_buf = tmp_buf;

        if (tmp_len > ptr->file_bytes_left) {
            log_error("it's impossible. tmp_len = %d\r\n", tmp_len);
        }

        if (tmp_err != ERR_MP3_NONE) {
            log_debug("need handle. tmp_err = %d\r\n", tmp_err);
            return -1;
        }

        /* push to pcm buf */
        // log_debug("push to pcm buf.\r\n");
        MP3GetLastFrameInfo(ptr->decoder, &ptr->frame_info);
        if (ptr->frame_info.samprate != media_ptr->current_sample_rate) {

            log_info("current_sample_rate = %d ---- > frame_info.samprate = %d \r\n",
                media_ptr->current_sample_rate, ptr->frame_info.samprate);

            media_ptr->current_sample_rate = ptr->frame_info.samprate;
          #if 0
            media_ptr->audio_fw_device->stop(media_ptr->audio_fw_device);
            config_es8311_reg();

            switch (ptr->frame_info.samprate) {
                case 8000:
                {
                    res = media_ptr->audio_fw_device->set_samplerate(media_ptr->audio_fw_device, AUDIO_FRAMEWORK_SAMPLERATE_8K);
                }
                break;
                case 11025:
                {
                    res = media_ptr->audio_fw_device->set_samplerate(media_ptr->audio_fw_device, AUDIO_FRAMEWORK_SAMPLERATE_11P025K);
                }
                break;
                case 12000:
                {
                    res = media_ptr->audio_fw_device->set_samplerate(media_ptr->audio_fw_device, AUDIO_FRAMEWORK_SAMPLERATE_12K);
                }
                break;
                case 16000:
                {
                    res = media_ptr->audio_fw_device->set_samplerate(media_ptr->audio_fw_device, AUDIO_FRAMEWORK_SAMPLERATE_16K);
                }
                break;
                case 22050:
                {
                    res = media_ptr->audio_fw_device->set_samplerate(media_ptr->audio_fw_device, AUDIO_FRAMEWORK_SAMPLERATE_22P05K);
                }
                break;
                case 24000:
                {
                    res = media_ptr->audio_fw_device->set_samplerate(media_ptr->audio_fw_device, AUDIO_FRAMEWORK_SAMPLERATE_24K);
                }
                break;
                case 32000:
                {
                    res = media_ptr->audio_fw_device->set_samplerate(media_ptr->audio_fw_device, AUDIO_FRAMEWORK_SAMPLERATE_32K);
                }
                break;
                case 44100:
                {
                    res = media_ptr->audio_fw_device->set_samplerate(media_ptr->audio_fw_device, AUDIO_FRAMEWORK_SAMPLERATE_44P1K);
                }
                break;
                case 48000:
                {
                    res = media_ptr->audio_fw_device->set_samplerate(media_ptr->audio_fw_device, AUDIO_FRAMEWORK_SAMPLERATE_48K);
                }
                break;
                case 96000:
                {
                    res = media_ptr->audio_fw_device->set_samplerate(media_ptr->audio_fw_device, AUDIO_FRAMEWORK_SAMPLERATE_96K);
                }
                break;
                case 192000:
                {
                    res = media_ptr->audio_fw_device->set_samplerate(media_ptr->audio_fw_device, AUDIO_FRAMEWORK_SAMPLERATE_192K);
                }
                break;
                default :
                {
                    res = -1;
                }
                break;
            }
            if (res != 0) {
                log_error("res = %d  not support samprate = %d\r\n", res, ptr->frame_info.samprate);
                return -1;
            }
            media_ptr->audio_fw_device->start(media_ptr->audio_fw_device);
          #endif
        }

        // if ((ptr->frame_info.samprate != 48000) || (ptr->frame_info.nChans != 2) ||
        //     (ptr->frame_info.outputSamps != 2304)) {
        //     log_error("not support samprate = %d  nChans = %d  outputSamps = %d\r\n",
        //         ptr->frame_info.samprate, ptr->frame_info.nChans, ptr->frame_info.outputSamps);
        //     return -1;
        // }

        if (pcm_buf_push_end(ptr, ptr->frame_info.outputSamps * sizeof(uint16_t)) != 0) {
            log_error("pcm_buf_push_end err.\r\n");
            return -1;
        }

        /* reset file data */
        if ((ptr->file_bytes_left - tmp_len) > 0) {
            memmove(ptr->file_buf, ptr->file_buf + ptr->file_bytes_left - tmp_len, tmp_len);
        }
        ptr->file_bytes_left = tmp_len;

        log_info("file_bytes_left = %ld\r\n", ptr->file_bytes_left);
        break;
    }

    return 0;
}

int audio_fetch_mp3(int fd, void *buf, int nbytes)
{
    int res;

    if (nbytes != 4096) {
        log_error("nbytes = %d\r\n", nbytes);
        return 0;
    }

    while (1) {
        if (pcm_buf_get_used_size(media_ptr) < 4096) {
            res = mp3_decoder_run2();
            if (res < 0) {
                log_error("mp3_decoder_run2 break.\r\n");
                break;
            }

            // log_info("get used size = %d\r\n", pcm_buf_get_used_size(media_ptr));
            continue;
        }

        log_info("pcm_buf_get_used_size = %d\r\n", pcm_buf_get_used_size(media_ptr));
        if (0 != pcm_buf_pop_4k(media_ptr, buf)) {
            log_error("pcm_buf_pop_4k break.\r\n");
            break;
        }
        log_info("pcm_buf_get_used_size = %d\r\n", pcm_buf_get_used_size(media_ptr));
        return 4096;
    }

    return 0;
}

int audio_fetch_pcm(int fd, void *buf, int nbytes)
{
    log_info("audio_fetch_pcm.\r\n");
    while(nbytes != aos_read(fd, buf, nbytes)) {
        log_info("lseek 0\r\n");
        aos_lseek(fd, 0, SEEK_SET);
    }

    return nbytes;
}

static int audio_fetch_init(uint8_t *name)
{
    char fullpath[64] = {0};

    if (!name) {
        log_error("arg err.\r\n");
        return -1;
    }

    /* must 1->2 */
    if (media_ptr->audio_flag != 1) {
        log_error("media_ptr->audio_flag = %d\r\n", media_ptr->audio_flag);
        return -1;
    }

    memset(fullpath, 0, sizeof(fullpath));
    snprintf(fullpath, sizeof(fullpath), "/sdcard/%s", name);
    fullpath[sizeof(fullpath) - 1] = '\0';
    printf("Opening PCM file %s\r\n", fullpath);

    if (media_ptr->fd_music >= 0) {
        log_error("fd = %d\r\n", media_ptr->fd_music);
        return -1;
    }
    /* set fd */
    media_ptr->fd_music = aos_open(fullpath, 0);
    printf("MUSIC fd is %d\r\n", media_ptr->fd_music);
    if (media_ptr->fd_music < 0) {
        log_error("aos_open[%s] err.\r\n", fullpath);
        return -1;
    }

    /* set fetch */
    if (strstr(fullpath, ".mp3") != 0) {
        log_info("set audio_fetch_mp3.\r\n");
        media_ptr->fetch_data = audio_fetch_mp3;
    } else if (strstr(fullpath, ".pcm") != 0) {
        log_info("set audio_fetch_pcm.\r\n");
        media_ptr->fetch_data = audio_fetch_pcm;
    } else {
        log_error("music type not support!\r\n");
        return -1;
    }

    return 0;
}

// chq_16K_stero_32Kbps.mp3 chq_16K_16bit_stero.pcm record.pcm
static void audio_fetch(void *arg)
{
    uint8_t *name = arg;
    if (!name) {
        log_error("arg err.\r\n");
        goto audio_fetch_exit;
    }

    media_ptr->audio_handle = xTaskGetCurrentTaskHandle();

    media_ptr->audio_flag = 1;

    if (audio_fetch_init(name) != 0) {
        goto audio_fetch_exit;
    }

    media_ptr->audio_flag = 2;

    while (1) {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        log_debug("audio_fetch.\r\n");
        if (media_ptr->audio_buf) {
            if (media_ptr->audio_len != media_ptr->fetch_data(media_ptr->fd_music, media_ptr->audio_buf, media_ptr->audio_len)) {
                // log_info("reset.\r\n");
                break;
            }
        } else {
            log_error("buf null.\r\n");
        }
    }

audio_fetch_exit:
    log_info("audio_fetch_exit.\r\n");
    media_ptr->audio_flag = 1;

    aos_msleep(20);
    if (media_ptr->fd_music >= 0) {
        aos_close(media_ptr->fd_music);
    }
    media_ptr->fd_music = -1;
    media_ptr->audio_flag = 0;
}

static void record_fetch(void *arg)
{
    int fd = -1;
    uint8_t *name = arg;
    int i = 100;/* record 64ms * 100 */

    if (!name) {
        log_error("arg err.\r\n");
        goto record_fetch_exit;
    }

    media_ptr->record_handle = xTaskGetCurrentTaskHandle();
    media_ptr->record_flag = 1;
    fd = aos_open((const char *)name, O_RDWR | O_CREAT | O_TRUNC);
    if (fd < 0) {
        log_error("open err.\r\n");
        return;
    }
    media_ptr->record_flag = 2;

    while (1) {
        if (i < 1) {
            break;
        }

        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        if (media_ptr->record_len > 0) {
            log_info("write start.\r\n");
            aos_write(fd, media_ptr->record_buf, media_ptr->record_len);
            log_info("write stop.\r\n");
        } else {
            log_error("err.\r\n");
        }

        i--;
    }

record_fetch_exit:
    media_ptr->record_flag = 1;
    aos_msleep(20);
    log_info("close fd.\r\n");
    aos_close(fd);
    media_ptr->record_flag = 0;
}

static int media_create(void)
{
    if (media_ptr != NULL) {
        log_error("reinit ?\r\n");
        return -2;
    }

    /* init media_ptr */
    media_ptr = pvPortMalloc(sizeof(media_type_t));
    if (NULL == media_ptr) {
        log_error("mem err.\r\n");
        return -1;
    }

    /* audio fw device */
    media_ptr->audio_fw_device = 0;
    media_ptr->current_sample_rate = 16000;/* 48000 16000 */

    /* pcm */
    media_ptr->pcm_buf = 0;
    media_ptr->pcm_bytes_maxsize = PCM_BUF_SZ;
    media_ptr->pcm_bytes_left = 0;
    media_ptr->pcm_buf = pvPortMalloc(PCM_BUF_SZ);
    log_info("media_ptr->pcm_buf = 0x%08lx\r\n", (uint32_t)media_ptr->pcm_buf);
    if (0 == media_ptr->pcm_buf) {
        log_error("mem err.\r\n");
        return -1;
    }

    /* record */
    media_ptr->record_handle = NULL;
    media_ptr->record_buf = NULL;
    media_ptr->record_len = 0;
    media_ptr->record_flag = 0;

    /* audio */
    media_ptr->audio_handle = NULL;
    media_ptr->audio_buf = NULL;
    media_ptr->audio_len = 0;
    media_ptr->audio_flag = 0;

    /* pcm */

    /* mp3 information */
    media_ptr->decoder = MP3InitDecoder();

    /* mp3 file init */
    media_ptr->file_bytes_left = 0;
    media_ptr->file_buf = NULL;
    media_ptr->file_buf = pvPortMallocDMA(FILE_MP3_BUF_SIZE);
    log_info("media_ptr->file_buf 0x%08lx\r\n", (uint32_t)media_ptr->file_buf);
    memset(media_ptr->file_buf, 0, FILE_MP3_BUF_SIZE);

    if (NULL == media_ptr->file_buf) {
        log_error("mem err.\r\n");

        vPortFree(media_ptr);
        media_ptr = NULL;

        return -1;
    }

    return 0;
}

static int media_init_flag = 0;

void audio_framwork_device_init(audio_framework_device_t *device)
{
    int size = 0, ret;
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
}

static int audiofw_config(void)
{
    if (media_init_flag != 0) {
        log_error("err. reinit ?\r\n");
        return -1;
    }

    config_es8311_reg(ES8311_12M288_8K);
    audio_gpio_init();  /* init gpio */
    SCCB_Init();        /* init i2c */

    if (media_create() != 0) {
        log_error("media_create error!\r\n");
        return -1;
    }

    if (audio_framework_factory_build("bl60x_i2s", &media_ptr->audio_fw_device)) {
        printf("Request I2S device bl60x_i2s failed\r\n ");
    } else {
        audio_framwork_device_init(media_ptr->audio_fw_device);

        media_ptr->fd_music = -1;
        media_ptr->fetch_data = NULL;
    }

    media_init_flag = 1;

    return 0;
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

static void cmd_media_config(char *buf, int len, int argc, char **argv)
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

static void cmd_media(char *buf, int len, int argc, char **argv)
{
    if (argc != 3) {
        log_error("err.\r\n");
        return;
    }
    if (media_init_flag == 0) {
        log_error("err. not init, use media_config\r\n");
        return;
    }

    if (memcmp(argv[1], "play", 4) == 0) {
        if (media_ptr->audio_flag == 0) {
            xTaskCreate(audio_fetch, (char*)"audio", 4096, argv[2], 28, NULL);
            log_info("audio_fetch task creat.\r\n");
        } else {
            log_error("err.\r\n");
            return;
        }
    } else if (memcmp(argv[1], "record", 4) == 0) {
        if (media_ptr->record_flag == 0) {
            xTaskCreate(record_fetch, (char*)"record", 4096, argv[2], 28, NULL);
            log_info("record_fetch task creat.\r\n");
        } else {
            log_error("err.\r\n");
            return;
        }
    } else {
        log_error("argv not match.\r\n");
    }
}

const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
    {"media_config", "media_config 8k", cmd_media_config},
    {"media", "play mp3 or pcm from sd", cmd_media}
};

int helper_media_cli_init(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user)/sizeof(cmds_user[0]));
    return 0;
}
