#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include <FreeRTOS.h>
#include <task.h>

#include <aos/kernel.h>

#include <cpu1.h>
#include <cli.h>
#include <helper_smp.h>

#include "bl_gpio.h"

#include "utils_log.h"

/*called on CPU1*/
static void ATTR_CPU1_CODE _func_on_cpu1(void *arg)
{
    uint32_t *data = (uint32_t*)arg;
    if (data == NULL) {
        printf("arg null.\r\n");
        return;
    }

    printf("[SMP] remote function call test, arg is %lx, \r\n", *data);
    *data = 0x87654321;
}

/*called on CPU0 IRQ*/
static void _func_notify_cpu0(void *arg)
{
    BaseType_t xHigherPriorityTaskWoken;
    TaskHandle_t task_handle = (TaskHandle_t)arg;

    vTaskNotifyGiveFromISR(task_handle, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

/*called on CPU1*/
static void ATTR_CPU1_CODE _cb_on_cpu1(void *arg)
{
    TaskHandle_t task_handle = (TaskHandle_t)arg;
    cpu_task_arg_t task_arg;

    printf("[SMP] function cb called, task handle is %p\r\n", task_handle);

    cpu_build_tskarg(&task_arg, CPU_TASK_TYPE_REALT, NULL, 0, 0);
    cpu0_task_deploy(_func_notify_cpu0, task_handle, NULL, NULL, &task_arg, NULL);
}

void thread_smp_entry(void *arg)
{
    volatile uint32_t data = 0x12345678;
    cpu_task_arg_t task_arg;

    TaskHandle_t task_handle;

    task_handle = xTaskGetCurrentTaskHandle();

    log_info("Deploy task_backgroud to CPU1 during task_handle %p\r\n", task_handle);
    data = 0x12345678;
    cpu_build_tskarg(&task_arg, CPU_TASK_TYPE_BACKG, NULL, 0, 0);
    cpu1_task_deploy(_func_on_cpu1, (void*)&data, _cb_on_cpu1, task_handle, &task_arg, NULL, 1000);
    while (data != 0x87654321) {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        puts("Wait data is set to 0x87654321\r\n");
    }
    vTaskDelay(1000);    /* just for wait cpu1 log end */

    log_info("Deploy task_realtime to CPU1 during task_handle %p\r\n", task_handle);
    data = 0x12345678;
    cpu_build_tskarg(&task_arg, CPU_TASK_TYPE_REALT, NULL, 0, 0);
    cpu1_task_deploy(_func_on_cpu1, (void*)&data, _cb_on_cpu1, task_handle, &task_arg, NULL, 1000);
    while (data != 0x87654321) {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        puts("Wait data is set to 0x87654321\r\n");
    }
    vTaskDelay(1000);    /* just for wait cpu1 log end */
}

static void cmd_cpu1_boot(char *buf, int len, int argc, char **argv)
{
    aos_task_new("smp_tsk", thread_smp_entry, NULL, 1024);
}

/* -------------------------- heart led start -------------------------- */
#define TEST_HEART_TIMEOUT     (10)  /* 10ms exc one times */
#define HEART_LED_INIT  bl_gpio_enable_output(9, 0, 1)
#define HEART_LED_OFF   bl_gpio_output_set(9, 1)
#define HEART_LED_ON    bl_gpio_output_set(9, 0)

static volatile uint32_t heart_led_state ATTR_CPU1_BSS = 0;
static volatile uint16_t heart_led_count ATTR_CPU1_BSS = 0;

const uint16_t heart_count_buf[4] ATTR_CPU1_RAM = {7, 18, 7, 68};
static cpu_task_arg_t *g_heart_arg_addr = NULL;

void heart_led_init(void)
{
    /* set gpio led out */
    HEART_LED_INIT;

    /* reset count */
    heart_led_state = 0;
    heart_led_count = 0;
}

void ATTR_CPU1_CODE _heart_led(void *arg)/* 10ms cb , period = 1s heart led */
{
    switch (heart_led_state)
    {
        case 0:
        {
            heart_led_count++;
            if (heart_led_count > heart_count_buf[0]) {
                heart_led_state = 1;
                heart_led_count = 0;
                HEART_LED_OFF;
            }
        }
        break;
        case 1:
        {
            heart_led_count++;
            if (heart_led_count > heart_count_buf[1]) {
                heart_led_state = 2;
                heart_led_count = 0;
                HEART_LED_ON;
            }
        }
        break;
        case 2:
        {
            heart_led_count++;
            if (heart_led_count > heart_count_buf[2]) {
                heart_led_state = 3;
                heart_led_count = 0;
                HEART_LED_OFF;
            }
        }
        break;
        default:
        {
            heart_led_count++;
            if (heart_led_count > heart_count_buf[3]) {
                heart_led_state = 0;
                heart_led_count = 0;
                HEART_LED_ON;
            }
        }
        break;
    }
}

void heart_led_entry(void *arg)
{
    cpu_task_arg_t task_arg;
    heart_led_init();
    log_info("Deploy heart task_period to CPU1.\r\n");

    cpu_build_tskarg(&task_arg, CPU_TASK_TYPE_PERID, "name_heart_led", TEST_HEART_TIMEOUT, CPU_TASK_NAME_PERID_TIMES_MAX);
    cpu1_task_deploy(_heart_led, NULL, NULL, NULL, &task_arg, &g_heart_arg_addr, 1000);
}

void cmd_heart_start(char *buf, int len, int argc, char **argv)
{
    aos_task_new("heart_led", heart_led_entry, NULL, 1024);
}

void cmd_heart_end(char *buf, int len, int argc, char **argv)
{
    if (cpu1_peridtsk_delete(&g_heart_arg_addr) == 0) {
        printf("delete ok.\r\n");
    } else {
        printf("busy now, please Wait a while and try again.\r\n");
    }
}
/* -------------------------- heart led end -------------------------- */

/* -------------------------- blink log start -------------------------- */
#define TEST_BLINK_TIMEOUT     (500)  /* 500ms exc one times */

static char _g_cb_arg[] = "blink led test";
static cpu_task_arg_t *g_blink_arg_addr = NULL;

static void ATTR_CPU1_CODE _g_blink_on_cpu1(void *arg)
{
    if (NULL == arg) {
        printf("[SMP] remote function call test.\r\n");
        return;
    }
    printf("[SMP] remote function call test %s\r\n", (char *)arg);
}

void blink_entry(void *arg)
{
    cpu_task_arg_t task_arg;

    log_info("Deploy blink task_period to CPU1.\r\n");

    cpu_build_tskarg(&task_arg, CPU_TASK_TYPE_PERID, "name_blink_log", TEST_BLINK_TIMEOUT, 50);
    cpu1_task_deploy(_g_blink_on_cpu1, _g_cb_arg, NULL, NULL, &task_arg, &g_blink_arg_addr, 1000);
}

void cmd_blink_start(char *buf, int len, int argc, char **argv)
{
    aos_task_new("blink_led", blink_entry, NULL, 1024);
}

void cmd_blink_end(char *buf, int len, int argc, char **argv)
{
    if (0 == cpu1_peridtsk_delete(&g_blink_arg_addr)) {
        printf("delete ok.\r\n");
    } else {
        printf("busy now, please Wait a while and try again.\r\n");
    }
}

/* -------------------------- blink led end -------------------------- */
void cmd_tsk_end(char *buf, int len, int argc, char **argv)
{
    uint32_t addr;

    if (argc != 2) {
        return;
    }

    addr = (uint32_t)strtol(argv[1], NULL, 16);

    log_info("addr = 0x%08lX\r\n", addr);

    if (cpu1_peridtsk_delete((cpu_task_arg_t **)&addr) == 0) {
        printf("delete ok.\r\n");
    } else {
        printf("busy now, please Wait a while and try again.\r\n");
    }
}

/* -------------------------- test pri start -------------------------- */
volatile uint32_t g_perid_realt_backg_flag ATTR_CPU1_BSS = 0;

void ATTR_CPU1_CODE _cb_pri_perid_tsk(void *arg)
{
    printf("[%4lu] period_tsk.\r\n", g_perid_realt_backg_flag);
    g_perid_realt_backg_flag++;
}

void ATTR_CPU1_CODE _cb_pri_realt_tsk(void *arg)
{
    printf("\r\nstart realt tsk.\r\n");
    while (1) {
        if (0x4 == (g_perid_realt_backg_flag & 0x7)) {
            printf("\r\nruning realt tsk.\r\n");
        }
        if (0x2F == g_perid_realt_backg_flag) {
            printf("\r\nGo out realt task\r\n");
            break;
        }
    }
    printf("\r\nend realt tsk.\r\n");
}

void ATTR_CPU1_CODE _cb_pri_backg_tsk(void *arg)
{
    printf("\r\nstart backg tsk.\r\n");
    while (1) {
        if (0x4 == (g_perid_realt_backg_flag & 0x7)) {
            printf("\r\nruning backg tsk.\r\n");
        }
        if (0x4F == g_perid_realt_backg_flag) {
            printf("\r\nGo out backg task\r\n");
            break;
        }
    }
    printf("\r\nend backg tsk.\r\n");
}

void cmd_pritest(char *buf, int len, int argc, char **argv)
{
    int res;
    cpu_task_arg_t tskarg;
    int i;

    if (argc != 2) {
        log_error("arg err.\r\n");
        return;
    }

    i = atoi(argv[1]);

    switch (i)
    {
        case 1:
        {
            res = cpu_build_tskarg(&tskarg, CPU_TASK_TYPE_PERID, "perid_test", 500, CPU_TASK_NAME_PERID_TIMES_MAX);
            if (res != 0) {
                log_error("build tskarg error.\r\n");
                return;
            }
            cpu1_task_deploy(_cb_pri_perid_tsk, NULL, NULL, NULL, &tskarg, NULL, 1000);
        }
        break;
        case 2:
        {
            res = cpu_build_tskarg(&tskarg, CPU_TASK_TYPE_REALT, NULL, 0, 0);
            if (res != 0) {
                log_error("build tskarg error.\r\n");
                return;
            }
            cpu1_task_deploy(_cb_pri_realt_tsk, NULL, NULL, NULL, &tskarg, NULL, 1000);
        }
        break;
        case 3:
        {
            res = cpu_build_tskarg(&tskarg, CPU_TASK_TYPE_BACKG, NULL, 0, 0);
            if (res != 0) {
                log_error("build tskarg error.\r\n");
                return;
            }
            cpu1_task_deploy(_cb_pri_backg_tsk, NULL, NULL, NULL, &tskarg, NULL, 1000);
        }
        break;
        default:
        {
            log_error("not support.\r\n");
        }
        break;
    }
}

/* -------------------------- test pri end -------------------------- */
void cmd_cpu_taskperid_list(char *buf, int len, int argc, char **argv)
{
    cpu_taskperid_list();
}

void cmd_cpu1_trigger(char *buf, int len, int argc, char **argv)
{
    cpu1_task_trigger();
}

void cmd_ipc_xipflash(char *buf, int len, int argc, char **argv)
{
    int test_ms;
    uint32_t i;

    if (2 != argc) {
        log_info("arg error.\r\n");
        return;
    }

    test_ms = atoi(argv[1]);

    log_info("test_ms = %d\r\n", test_ms);

    CPU_OPS_FLASH_TASK_SUSPEND;

    for (i = 0; i<16000000; i++) {
        __asm volatile ("nop");
    }
    // dis irq
    // aos_msleep(test_ms);
    // en irq

    CPU_OPS_FLASH_TASK_RESUME;
}

// STATIC_CLI_CMD_ATTRIBUTE makes this(these) command(s) static
const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
    {"cpu1_trigger", "cmd_cpu1_trigger", cmd_cpu1_trigger},
    {"cpu1_boot", "Trigger CPU1 BOOT", cmd_cpu1_boot},
    {"heartstart", "heartstart", cmd_heart_start},
    {"heartend", "heartend", cmd_heart_end},
    {"blinkstart", "blink_start", cmd_blink_start},
    {"blinkend", "blink_end", cmd_blink_end},
    {"tsklist", "cmd_cpu_taskperid_list", cmd_cpu_taskperid_list},
    {"tskend", "cmd_tsk_end", cmd_tsk_end},
    {"prttest", "cmd_pritest", cmd_pritest},
    {"ipcxip", "cmd_ipc_xipflash", cmd_ipc_xipflash},
};

int helper_smp_cli_init(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user)/sizeof(cmds_user[0]));
    return 0;
}
