
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* FreeRTOS */
#include <FreeRTOS.h>
#include <task.h>
#include <timers.h>

/* aos */
#include <aos/kernel.h>
#include <aos/yloop.h>
#include <cli.h>
#include <device/vfs_uart.h>
#include <event_device.h>
#include <vfs.h>

/* driver */
#include <bl_uart.h>
#include <hosal_uart.h>

#include "m1s_c906_xram.h"
#define UART_ID_C906 (0)
#define UART_TX_C906 (16)
#define UART_RX_C906 (17)
#define UART_BAUD_C906 (2000000)

HOSAL_UART_DEV_DECL(uart_stdio, UART_ID_C906, UART_TX_C906, UART_RX_C906, UART_BAUD_C906)

static void bl808_FreeRTOS_init(void)
{
    extern uint8_t _heap_start_tcm;
    extern uint8_t _heap_size_tcm;

    static HeapRegion_t xHeapRegions[] = {
        {NULL, 0}, /* set on runtime */
        {NULL, 0}  /* Terminates the array */
    };
    xHeapRegions[0].pucStartAddress = (uint8_t *)&_heap_start_tcm;
    xHeapRegions[0].xSizeInBytes = (size_t)&_heap_size_tcm;
    printf("Heap Info: %ld KB @ [0x%p ~ 0x%p]\r\n", xHeapRegions[0].xSizeInBytes >> 10, xHeapRegions[0].pucStartAddress,
           xHeapRegions[0].pucStartAddress + xHeapRegions[0].xSizeInBytes);

    vPortDefineHeapRegions(xHeapRegions);
}

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    puts("Stack Overflow checked\r\n");
    printf("Task Name %s\r\n", pcTaskName);
    while (1) {
        /*empty here*/
    }
}

void vApplicationMallocFailedHook(void)
{
    printf("Memory Allocate Failed. Current left size is %lu bytes\r\n", xPortGetFreeHeapSize());
    while (1) {
        /*empty here*/
    }
}

void vApplicationIdleHook(void) {}

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer,
                                   uint32_t *pulIdleTaskStackSize)
{
    /* If the buffers to be provided to the Idle task are declared inside this
    function then they must be declared static - otherwise they will be allocated on
    the stack and so not exists after this function exits. */
    static StaticTask_t xIdleTaskTCB;
    static StackType_t uxIdleTaskStack[configMINIMAL_STACK_SIZE];

    /* Pass out a pointer to the StaticTask_t structure in which the Idle task's
    state will be stored. */
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;

    /* Pass out the array that will be used as the Idle task's stack. */
    *ppxIdleTaskStackBuffer = uxIdleTaskStack;

    /* Pass out the size of the array pointed to by *ppxIdleTaskStackBuffer.
    Note that, as the array is necessarily of type StackType_t,
    configMINIMAL_STACK_SIZE is specified in words, not bytes. */
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

/* configSUPPORT_STATIC_ALLOCATION and configUSE_TIMERS are both set to 1, so the
application must provide an implementation of vApplicationGetTimerTaskMemory()
to provide the memory that is used by the Timer service task. */
void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer,
                                    uint32_t *pulTimerTaskStackSize)
{
    /* If the buffers to be provided to the Timer task are declared inside this
    function then they must be declared static - otherwise they will be allocated on
    the stack and so not exists after this function exits. */
    static StaticTask_t xTimerTaskTCB;
    static StackType_t uxTimerTaskStack[configTIMER_TASK_STACK_DEPTH];

    /* Pass out a pointer to the StaticTask_t structure in which the Timer
    task's state will be stored. */
    *ppxTimerTaskTCBBuffer = &xTimerTaskTCB;

    /* Pass out the array that will be used as the Timer task's stack. */
    *ppxTimerTaskStackBuffer = uxTimerTaskStack;

    /* Pass out the size of the array pointed to by *ppxTimerTaskStackBuffer.
    Note that, as the array is necessarily of type StackType_t,
    configTIMER_TASK_STACK_DEPTH is specified in words, not bytes. */
    *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}

void vAssertCalled(void)
{
    volatile uint32_t ulSetTo1ToExitFunction = 0;

    taskDISABLE_INTERRUPTS();
    while (ulSetTo1ToExitFunction != 1) {
        __asm volatile("NOP");
    }
}

static inline void main_warpper()
{
    extern void main(void);
    main();
    vTaskDelete(NULL);
}

static void start_main(void *arg) { xTaskCreate(main_warpper, (char *)"main", 4096, NULL, 15, NULL); }

static void aos_loop_proc(void *pvParameters)
{
    int fd_console;
    vfs_init();
    vfs_device_init();

    /* uart */
    vfs_uart_init_simple_mode(UART_ID_C906, UART_TX_C906, UART_RX_C906, UART_BAUD_C906,
                              "/dev/ttyS0");  // UART for cli
    aos_loop_init();

    fd_console = aos_open("/dev/ttyS0", 0);
    if (fd_console >= 0) {
        printf("Init CLI with event Driven\r\n");
        aos_cli_init(0);
        aos_poll_read_fd(fd_console, aos_cli_event_cb_read_get(), (void *)0x12345678);
        aos_post_delayed_action(100, start_main, NULL);
    }

    aos_loop_run();

    puts("------------------------------------------\r\n");
    puts("+++++++++Critical Exit From Loop++++++++++\r\n");
    puts("******************************************\r\n");
    vTaskDelete(NULL);
}

void bfl_main()
{
    bl_uart_c906_init(0, UART_TX_C906, UART_RX_C906, 0, 0, UART_BAUD_C906);

    puts("Starting bl808 now....\r\n");
    bl808_FreeRTOS_init();

    puts("[OS] Starting aos_loop_proc task...\r\n");
    xTaskCreate(aos_loop_proc, (char *)"event_loop", 1024, NULL, 15, NULL);

    puts("[OS] Start c906 xram handle...\r\n");
    m1s_c906_xram_init();
    
    puts("[OS] Starting OS Scheduler...\r\n");
    vTaskStartScheduler();
}
