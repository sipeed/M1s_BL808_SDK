#include <stdio.h>

#include <FreeRTOS.h>
#include <task.h>
#include <sccb.h>
#include <camera.h>
#include <bl_cam.h>
#include <bl_gpio.h>

#include <cli.h>

#include <helper_cam.h>

#define mainSTART_AP_TASK_PRIORITY     (20)

static void enable_camera_module()
{
#define CAM_GPIO_PWR (15)

    /*Disable Power Down Mode*/
    bl_gpio_output_set(CAM_GPIO_PWR, 0);
    bl_gpio_enable_output(CAM_GPIO_PWR, 0, 0);
}

static void cameraTask_mjpeg(void *pvParameters)
{
    uint8_t *ptr1, *ptr2;
    uint32_t len1, len2, counter, frames;
    const rt_camera_desc *desc;

    TickType_t xDelay = pdMS_TO_TICKS(1000);

    /*enable_24mhz*/
    bl_cam_enable_24MRef();
    vTaskDelay(xDelay);
    enable_camera_module();
    vTaskDelay(xDelay);

    SCCB_Init();

    desc = camera_module_init();
    if (NULL == desc) {
        return;
    }
    /*enable CAM module*/
    bl_cam_init(1, desc);

    counter = 0;
    while (1) {
        bl_cam_frame_wait();
        if (0 == bl_cam_frame_get(&frames, &ptr1, &len1, &ptr2, &len2)) {
            printf("[MJPEG] [MAIN] @%d frames %u, frame ptr1 %p len %u, ptr2 %p len %u; counter %u\r\n",
                    (int)xTaskGetTickCount(),
                    (unsigned int)frames,
                    ptr1,
                    (unsigned int)len1,
                    ptr2,
                    (unsigned int)len2,
                    (unsigned int)counter++
            );
        }
        bl_cam_frame_pop();
    }
}

static volatile int pop = 0;
static void _manu_pop_wait()
{
    while (0 == pop) {
        vTaskDelay(100);
    }
    pop = 0;
}

static void _manu_pop_do()
{
    uint32_t jpeg_size = 0x100000;

    if (0 == bl_cam_mjpeg_encoder(0x21100000, 0x21300000, &jpeg_size,  1280, 720, 50)) {
        printf("[MJPEG] encoder OK, result size is 0x%lx(%lu) Bits, 0x%lX(%lu) Bytes\r\n",
                jpeg_size,
                jpeg_size,
                (jpeg_size + 7) >> 3,
                (jpeg_size + 7) >> 3
        );
    } else {
        puts("[MJPEG] encoder failed\r\n");
    }

    pop = 1;
    bl_cam_yuv_frame_pop();
}

static void cmd_camera_pop(char *buf, int len, int argc, char **argv)
{
    _manu_pop_do();
}

static void cameraTask_yuv(void *pvParameters)
{
    uint8_t *ptr1, *ptr2;
    uint32_t len1, len2, counter, frames;
    int auto_mode = (int)pvParameters;
    const rt_camera_desc *desc;

    TickType_t xDelay = pdMS_TO_TICKS(1000);

    /*enable_24mhz*/
    bl_cam_enable_24MRef();
    vTaskDelay(xDelay);
    enable_camera_module();
    vTaskDelay(xDelay);

    SCCB_Init();
    desc = camera_module_init();
    if (NULL == desc) {
        return;
    }
    /*enable CAM module*/
    bl_cam_init(1, desc);

    counter = 0;
    while (1) {
        bl_cam_yuv_frame_wait();
        if (0 == bl_cam_yuv_frame_get(&frames, &ptr1, &len1, &ptr2, &len2)) {
            printf("[YUV] [%s] @%d frames %u, frame ptr1 %p len %u, ptr2 %p len %u; counter %u\r\n",
                    auto_mode ? "AUTO" : "MANU",
                    (int)xTaskGetTickCount(),
                    (unsigned int)frames,
                    ptr1,
                    (unsigned int)len1,
                    ptr2,
                    (unsigned int)len2,
                    (unsigned int)counter++
            );
            if (auto_mode) {
                bl_cam_yuv_frame_pop();
            } else {
                _manu_pop_wait();
            }
        }
    }
}

static void cmd_camera_start(char *buf, int len, int argc, char **argv)
{
    static int started = 0;

    if (started) {
        return;
    }
    started = 1;
    xTaskCreate(cameraTask_mjpeg, (char*)"mjpeg", 4096, NULL, mainSTART_AP_TASK_PRIORITY - 5, NULL);
}

static void cmd_yuv_start(char *buf, int len, int argc, char **argv)
{
    static int started = 0;

    if (started) {
        return;
    }
    started = 1;
    xTaskCreate(cameraTask_yuv, (char*)"yuv", 4096, 2 == argc ? (void*)0 : (void*)1, mainSTART_AP_TASK_PRIORITY - 5, NULL);
}

static void cmd_camera_scan(char *buf, int len, int argc, char **argv)
{
    SCCB_Init();
    SCCB_Scan(1, 0xFE);
}

// STATIC_CLI_CMD_ATTRIBUTE makes this(these) command(s) static
const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
    {"cam_start", "Start Camera Interface", cmd_camera_start},
    {"cam_yuv", "Start Camera Interface", cmd_yuv_start},
    {"cam_pop", "Start Camera Interface", cmd_camera_pop},
    {"cam_scan", "scan devices on I2S bus", cmd_camera_scan},
};

int helper_cam_cli_init(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user)/sizeof(cmds_user[0]));
    return 0;
}
