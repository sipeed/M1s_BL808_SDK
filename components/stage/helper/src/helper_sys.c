#include <stdio.h>
#include <cli.h>

#include <helper_sys.h>
#include <easyflash.h>
#include <bl_sys.h>

static void reset_cmd(char *buf, int len, int argc, char **argv)
{
    ef_env_set_default();
    bl_sys_reset_por();
}

// STATIC_CLI_CMD_ATTRIBUTE makes this(these) command(s) static
const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
        { "reset", "reset and reboot", reset_cmd },
};                                                                                   

int helper_sys_cli_init(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user)/sizeof(cmds_user[0]));          
    return 0;
}
