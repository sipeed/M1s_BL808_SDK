#include <cli.h>
#include <stdint.h>
#include <FreeRTOS.h>
#include <aos/kernel.h>

#include "register_test_app.h"
#include "test_queue.h"

static void test_queue_cmd(char *buf, int len, int argc, char **argv)
{
    test_queue_within_two_tasks_main();
}

static void test_queue_full_cmd(char *buf, int len, int argc, char **argv)
{
    test_queue_full_main();
}

static void test_queue_empty_cmd(char *buf, int len, int argc, char **argv)
{
    test_queue_empty_main();
}

static void test_queue_put_fromISR_cmd(char *buf, int len, int argc, char **argv)
{
    test_queue_put_fromISR_main();
}

static void test_queue_get_fromISR_cmd(char *buf, int len, int argc, char **argv)
{
    test_queue_get_fromISR_main();
}

const static struct cli_command cmds_user[] = {                                      
    {"test_queue", "test queue within two tasks", test_queue_cmd},
    {"test_queue_full", "test queue full", test_queue_full_cmd},
    {"test_queue_empty", "test queue empty", test_queue_empty_cmd},
    {"test_queue_put_fromISR", "test queue put fromISR", test_queue_put_fromISR_cmd},
    {"test_queue_get_fromISR", "test queue get fromISR", test_queue_get_fromISR_cmd},
};                                                                                   

void register_test_app_init(void)
{
    aos_cli_register_commands(cmds_user, sizeof(cmds_user)/sizeof(cmds_user[0]));          
}

