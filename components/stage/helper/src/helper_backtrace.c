#include <stdio.h>
#include <cli.h>

#include <helper_sys.h>
#include <easyflash.h>
#include <bl_sys.h>

static void fault_test_by_div0(void) 
{
    volatile int * SCB_CCR = (volatile int *) 0xE000ED14; // SCB->CCR
    int x, y, z;

    *SCB_CCR |= (1 << 4); /* bit4: DIV_0_TRP. */

    x = 10;
    y = 0;
    z = x / y;
    printf("z:%d\n", z);
}

static void test_backtrace_func()
{
    fault_test_by_div0();
}

static void test_backtrace_cmd(char *buf, int len, int argc, char **argv)
{
    test_backtrace_func();
}

static void test_null_cmd(char *buf, int len, int argc, char **argv)
{
    int *p = NULL;
    *p = 123;
}

static void test_backtrace_api_child_func()
{
    extern int freertos_backtrace_now();
    freertos_backtrace_now();
}

static void test_backtrace_api(char *buf, int len, int argc, char **argv)
{
    test_backtrace_api_child_func();
}

// STATIC_CLI_CMD_ATTRIBUTE makes this(these) command(s) static
const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
        { "test_backtrace", "test_backtrace", test_backtrace_cmd },
        { "test_null", "test_null", test_null_cmd },
        { "test_backtrace_api", "test_backtrace_api", test_backtrace_api },
};                                                                                   

int helper_backtrace_cli_init(void)
{
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user)/sizeof(cmds_user[0]));          
    return 0;
}
