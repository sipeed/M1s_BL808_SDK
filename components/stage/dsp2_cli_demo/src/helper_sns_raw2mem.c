#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <FreeRTOS.h>
#include <task.h>

#include <getopt.h>
#include <aos/kernel.h>
#include <cli.h>
#include <bl_comm_sns.h>
#include<core_rv64.h>
#include <sample_common.h>
#include "sensor.h"
#include "helper_sns_raw2mem.h"
#include "mm_sensor.h"

#define mainSTART_AP_TASK_PRIORITY  ( 20 )

void sns_raw2mem_task(void *_params)
{
    uint8_t *raw_addr = NULL;
    uint32_t raw_len = 0;
    int32_t i = 0;

    MM_Sensor_Raw2Mem_Init_Run(VIDEO_MODE_328_744_10);

    while (i++ < 20) {
        sample_get_raw_pic(&raw_addr, &raw_len, 0);
        csi_dcache_invalid_range(raw_addr, raw_len);
    }

    vTaskDelete(NULL);
}

static void sns_raw2mem_cmd(char *buf, int len, int argc, char **argv)
{
    xTaskCreate(sns_raw2mem_task, "sns_raw2mem", 1024, NULL, mainSTART_AP_TASK_PRIORITY, NULL);
}

const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
        { "sns_raw2mem", "get sensor raw data to mem", sns_raw2mem_cmd },
};

int helper_sns_raw2mem_cli_init(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user) / sizeof(cmds_user[0]));
    return 0;
}
