#include <stdio.h>

#include <cli.h>

#include <helper_psm.h>
#include <easyflash.h>

static void psm_set_cmd(char *buf, int len, int argc, char **argv)
{
    if (argc != 3) {
        printf("usage: psm_set [key] [value]\r\n");
        return;
    }
    ef_set_env(argv[1], argv[2]);
    ef_save_env();
}

static void psm_unset_cmd(char *buf, int len, int argc, char **argv)
{
    if (argc != 2) {
        printf("usage: psm_unset [key]\r\n");
        return;
    }
    ef_del_env(argv[1]);
    ef_save_env();
}

static void psm_dump_cmd(char *buf, int len, int argc, char **argv)
{
    ef_print_env();
}

static void psm_erase_cmd(char *buf, int len, int argc, char **argv)
{
    ef_env_set_default();
}

// STATIC_CLI_CMD_ATTRIBUTE makes this(these) command(s) static
const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
        { "psm_set", "psm set", psm_set_cmd },
        { "psm_unset", "psm unset", psm_unset_cmd },
        { "psm_dump", "psm dump", psm_dump_cmd },
        { "psm_erase", "psm dump", psm_erase_cmd },
};                                                                                   

int helper_psm_cli_init(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user)/sizeof(cmds_user[0]));          
    return 0;
}
