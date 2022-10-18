#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

#include "utils_log.h"

#include <bl_cam.h>
#include <bl_gpio.h>
#include <camera.h>
#include <mjpeg_booster.h>
#include <mjpeg_sw_buffer.h>

// MJPEG configs
#define CONF_MJPEG_Q_MAX                      50
#define CONF_MJPEG_Q_MIN                      10
#define CONF_MJPEG_Q_UPGRADE_SIZE_THRESHOLD   (15*1024)
#define CONF_MJPEG_Q_DOWNGRADE_SIZE_THRESHOLD (55*1024)

#define mainSTART_AP_TASK_PRIORITY  ( 20 )

static const rt_camera_desc *cam_desc;

static void enable_camera_module()
{
#define CAM_GPIO_PWR (15)

#if 1
    /*Disable Power Down Mode*/
    bl_gpio_output_set(CAM_GPIO_PWR, 0);
    bl_gpio_enable_output(CAM_GPIO_PWR, 0, 0);
#endif
}

static void configStartSenderTask(void *_)
{
    int ret;
    ret = mjpeg_sender_config(8800, 1234);
    if (ret < 0)
        printf("mjpeg_sender_config error\r\n");
    ret = mjpeg_sender_start();
    if (ret < 0)
        printf("mjpeg_sender_start error\r\n");
    mjpeg_sw_fifo_config(CONF_MJPEG_Q_MAX, CONF_MJPEG_Q_MIN,
            CONF_MJPEG_Q_UPGRADE_SIZE_THRESHOLD, CONF_MJPEG_Q_DOWNGRADE_SIZE_THRESHOLD);
    vTaskDelete(NULL);
}

static void cameraTask(void *pvParameters)
{
    uint16_t frame_count = 0;
    uint32_t tick_now, tick_last = 0;

    TickType_t xDelay = pdMS_TO_TICKS(1000);

    /*enable_24mhz*/
    bl_cam_enable_24MRef();
    vTaskDelay(xDelay);
    enable_camera_module();
    vTaskDelay(xDelay);

    SCCB_Init();
    cam_desc = camera_module_init();
    if (NULL == cam_desc) {
        return;
    }
    /*enable CAM module*/
    bl_cam_init(1, cam_desc);

    if (mjpeg_sw_fifo_init(cam_desc->width, cam_desc->height)) {
        printf("[SENDER] mjpeg_sw_fifo_init failed\r\n");
        while (1) {
            /* empty */;
        }
    }

    /*cam is ready, now start task*/
    xTaskCreate(mjpeg_sender_task, "sender", 1024, NULL, mainSTART_AP_TASK_PRIORITY + 1, NULL);
    xTaskCreate(mjpeg_sender_ctl_task, "senderctl", 512, NULL, mainSTART_AP_TASK_PRIORITY + 2, NULL);
    xTaskCreate(configStartSenderTask, "foo", 2048, NULL, mainSTART_AP_TASK_PRIORITY - 2, NULL);

    //cpu_utils_usage_init();
    xDelay = pdMS_TO_TICKS(1000);
    tick_last = xTaskGetTickCount();

    while (1) {
        tick_now = xTaskGetTickCount();
        if (((int32_t)tick_now) - ((int32_t)tick_last) > 10*1000) {
            tick_last = xTaskGetTickCount();
            /*debug every 30*/
            printf("[MAIN] FPS is %u\r\n", (*(volatile uint16_t*)0x40016028 - frame_count)/10);
            frame_count = *(volatile uint16_t*)0x40016028;
        }
        vTaskDelay(pdMS_TO_TICKS(50 / 2));
    }
}

static void cmd_mjpeg_start(char *buf, int len, int argc, char **argv)
{
    puts("-------------------------->>> Starting MJPEG tasks\r\n");
    xTaskCreate(cameraTask, (char*)"camera", 2048, NULL, mainSTART_AP_TASK_PRIORITY + 3, NULL);
}


// STATIC_CLI_CMD_ATTRIBUTE makes this(these) command(s) static
const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
    { "mjpeg_start", "start mjpeg tasks", cmd_mjpeg_start }
};

int helper_mjpeg_cli_init(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user) / sizeof(cmds_user[0]));
    return 0;
}
