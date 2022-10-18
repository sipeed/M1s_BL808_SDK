#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <cli.h>
#include <bl_nv_data.h>
#include <helper_nv.h>

static void msg_set_cmd(char *buf, int len, int argc, char **argv)
{
    if (argc != 2) {
        printf("usage: msg_set [value]\r\n");
        return;
    }
    bl_nv_data_msg_push(argv[1], strlen(argv[1]) + 1);
}

static void msg_get_cmd(char *buf, int len, int argc, char **argv)
{
    if (argc != 2) {
        printf("usage: msg_get [idx]\r\n");
        return;
    }
    char msg_ctn[128] = {0};
    memset(msg_ctn, 0, sizeof(msg_ctn));
    bl_nv_data_msg_get_by_idx(atoi(argv[1]), msg_ctn, sizeof(msg_ctn));
    printf("msg get (%d:%s)\r\n", atoi(argv[1]), msg_ctn);
}

static void msg_dump_cmd(char *buf, int len, int argc, char **argv)
{
    if (argc != 1) {
        printf("usage: msg_dump\r\n");
        return;
    }
    char msg_ctn[128] = {0};
    int i = 0;

    /*we assume max msg is 128*/
    while (i < bl_nv_data_msg_total_size()) {
        memset(msg_ctn, 0, sizeof(msg_ctn));
        bl_nv_data_msg_get_by_idx(i, msg_ctn, sizeof(msg_ctn));
        printf("[%03d] msg: %s\r\n", i, msg_ctn);
        i++;
    }
}

static void msg_reset_cmd(char *buf, int len, int argc, char **argv)
{
    if (argc != 1) {
        printf("usage: msg_reset\r\n");
        return;
    }
    bl_nv_data_reset();
} 

static void msg_set_t1_cmd(char *buf, int len, int argc, char **argv)
{
    if (argc != 3) {
        printf("usage: msg_set [time] [string]\r\n");
        return;
    }
    uint32_t time = atoi(argv[1]);
    uint32_t cnt = 0;
    for (cnt = 0; cnt < time; cnt++) {
        bl_nv_data_msg_push(argv[2], strlen(argv[2]) + 1);
    }
}     

// STATIC_CLI_CMD_ATTRIBUTE makes this(these) command(s) static
const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
    {"msg_set", "message set", msg_set_cmd },
    {"msg_get", "message get", msg_get_cmd },
    {"msg_dump", "message dump", msg_dump_cmd },
    {"msg_reset", "erase all message regions", msg_reset_cmd},
    {"msg_set_t1", "message set test 1", msg_set_t1_cmd },        
};                                                                                   

int helper_nv_cli_init(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user)/sizeof(cmds_user[0]));          
    return 0;
}
