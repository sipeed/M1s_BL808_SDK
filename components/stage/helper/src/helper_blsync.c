
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <timers.h>
#include <aos/kernel.h>
#include <aos/yloop.h>
#include <lwip/mem.h>
#include <lwip/memp.h>
#include <lwip/dhcp.h>
#include <lwip/tcpip.h>
#include <lwip/ip_addr.h>
#include <lwip/netifapi.h>
#include <lwip/sockets.h>
#include <cli.h>
#include <wifi_mgmr_ext.h>

#include <bl_sync.h>

#include <utils_log.h>
#include <utils_fec.h>

#include <helper_wifi.h>
#include <helper_blsync.h>

#include <bl60x_fw_api.h>

void blsync_reult_cb(void *arg)
{
    blsync_t *context = (blsync_t *)arg;
    static blsync_result_t blsync_result_context;

    if (!arg) {
        return;
    }

    blsync_get_result(context, &blsync_result_context);
    log_info("blsync_reult_cb.\r\n");

    log_info("blsync_result_context.randombuf = %02X %02X %02X %02X\r\n",
                blsync_result_context.randombuf[0],
                blsync_result_context.randombuf[1],
                blsync_result_context.randombuf[2],
                blsync_result_context.randombuf[3]);

    log_info("blsync_result_context.ssid_len = %d\r\n", blsync_result_context.ssid_length);
    log_info("blsync_result_context.ssid     = %s\r\n", blsync_result_context.ssid);
    log_info("blsync_result_context.pwd_len  = %d\r\n", blsync_result_context.pwd_length);
    log_info("blsync_result_context.pwd      = %s\r\n", blsync_result_context.pwd);

    blsync_stop(context);
}

static blsync_t blsync_context;

static void blsync_cmd(char *buf, int len, int argc, char **argv)
{
    memset(&blsync_context, 0, sizeof(blsync_t));
    blsync_init(&blsync_context, blsync_reult_cb);
    blsync_start(&blsync_context);
}

// STATIC_CLI_CMD_ATTRIBUTE makes this(these) command(s) static
const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
    { "blsync", "blsync cmd", blsync_cmd}
};

int helper_blsync_cli_init(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user)/sizeof(cmds_user[0]));
    return 0;
}
