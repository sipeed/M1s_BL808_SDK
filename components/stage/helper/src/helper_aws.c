#include <FreeRTOS.h>
#include <task.h>

#include <cli.h>
#include <helper_aws.h>

static void cmd_aws(char *buf, int len, int argc, char **argv) 
{
void aws_main_entry(void *arg);
    xTaskCreate(aws_main_entry, (char*)"aws_iot", 4096, NULL, 15, NULL);
}

// STATIC_CLI_CMD_ATTRIBUTE makes this(these) command(s) static
const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
    {"aws_shadow", "aws_shadow", cmd_aws},
};                                                                                   

int helper_aws_cli_init(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user)/sizeof(cmds_user[0]));          
    return 0;
}
