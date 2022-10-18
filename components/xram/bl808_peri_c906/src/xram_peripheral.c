#include <stdio.h>
#include <FreeRTOS.h>
#include <semphr.h>
#include "xram_peripheral.h"

static SemaphoreHandle_t g_peri_mutex = NULL;

/* create a mutex for peripheral operation
 * param:
 * return:
 *  <0: faild
 *  0: success
 **/
int xram_peri_mutex_init(void)
{
    if (NULL != g_peri_mutex) {
        return -1;
    }

    if (NULL == (g_peri_mutex = xSemaphoreCreateMutex())) {
        return -1;
    }

    return 0;
}

int xram_peri_mutex_destory(void)
{
    vSemaphoreDelete(g_peri_mutex);
    g_peri_mutex = NULL;
    return 0;
}


int xram_peri_mutex_lock()
{
    if (pdTRUE != xSemaphoreTake(g_peri_mutex, portMAX_DELAY)) {
        printf("xram peri semaphore take err!\r\n");
        return -1;
    }

    return 0;
}

int xram_peri_mutex_unlock()
{
    if( xSemaphoreGive(g_peri_mutex) != pdTRUE ){
        printf("xram peri semaphore give err!\r\n");
        return -1;
    }

    return 0;
}
