#include <cli.h>
#include <FreeRTOS.h>
#include <task.h>
#include "sample_register_app.h"
#include "sample_app.h"

static void encoder_video_cmd(char *buf, int len, int argc, char **argv)
{
    sample_encoder_video_main();
}

static void encoder_jpeg_cmd(char *buf, int len, int argc, char **argv)
{
    xTaskCreate(sample_encoder_jpeg_main, (char*)"jpeg_main", 1024, NULL, 10, NULL);;
}

const static struct cli_command cmds_user[] = {                                      
    //{"sample_encoder_video", "sample encoder video", encoder_video_cmd},
    {"sample_encoder_jpeg", "sample encoder jpeg", encoder_jpeg_cmd},
};                                                                                   

void sample_register_app_init(void)
{
    aos_cli_register_commands(cmds_user, sizeof(cmds_user)/sizeof(cmds_user[0]));          
}

