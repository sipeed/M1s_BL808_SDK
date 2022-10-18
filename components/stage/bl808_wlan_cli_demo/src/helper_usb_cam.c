#include <stdio.h>
#include <string.h>

#include <FreeRTOS.h>
#include <task.h>
#include <aos/kernel.h>
#include <aos/yloop.h>
#include <cli.h>
#include <vfs.h>
#include <bl_usb_cam.h>

static void usb_cam_test(void *param)
{
    if (bl_usb_cam_init()) {
        printf("init usb cam fail\r\n");
        goto exit;
    }

    while (1) {
        bl_usb_cam_transfer();
        vTaskDelay(5);
    }
exit:
    vTaskDelete(NULL);
}

void cmd_test_usb_cam(char *buf, int len, int argc, char **argv)
{
    xTaskCreate(usb_cam_test, (char*)"yuv sensor", 512, NULL, 10, NULL);
}

// STATIC_CLI_CMD_ATTRIBUTE makes this(these) command(s) static
const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
    { "usb_cam", "usb cam test", cmd_test_usb_cam}
};

int helper_usb_cam_cli_init(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user) / sizeof(cmds_user[0]));
    return 0;
}
