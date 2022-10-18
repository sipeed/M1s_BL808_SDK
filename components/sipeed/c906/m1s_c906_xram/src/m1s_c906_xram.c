#include <FreeRTOS.h>
#include <assert.h>
#include <semphr.h>
#include <stdio.h>
#include <xram.h>

// #include "m1s_c906_xram_uartp.h"
#include "m1s_common_xram.h"

static SemaphoreHandle_t s_mutex = NULL;

/* create a mutex for peration
 * param:
 * return:
 *  <0: faild
 *  0: success
 **/
int m1s_c906_xram_mutex_init(void)
{
    if (NULL != s_mutex) {
        return -1;
    }

    if (NULL == (s_mutex = xSemaphoreCreateMutex())) {
        return -1;
    }

    return 0;
}

int m1s_c906_xram_mutex_destory(void)
{
    vSemaphoreDelete(s_mutex);
    s_mutex = NULL;
    return 0;
}

int m1s_c906_xram_mutex_lock()
{
    if (pdTRUE != xSemaphoreTake(s_mutex, portMAX_DELAY)) {
        printf("xram peri semaphore take err!\r\n");
        return -1;
    }

    return 0;
}

int m1s_c906_xram_mutex_unlock()
{
    if (xSemaphoreGive(s_mutex) != pdTRUE) {
        printf("xram peri semaphore give err!\r\n");
        return -1;
    }

    return 0;
}

static int s_plunder_rx_hdr_en = 0;
static struct xram_hdr s_plunder_rx_hdr;
struct xram_hdr *m1s_c906_xram_plunder_rx_hdr()
{
    if (s_plunder_rx_hdr_en) return NULL;

    s_plunder_rx_hdr_en = 1;

    while (s_plunder_rx_hdr_en) {
        vTaskDelay(1);
    }
    return &s_plunder_rx_hdr;
}

void m1s_c906_xram_operation_handle()
{
    struct xram_hdr rx_hdr;
    uint32_t bytes;

    while (1) {
        bytes = XRAMRingRead(XRAM_OP_QUEUE, &rx_hdr, XRAM_MSG_HDR);
        assert(bytes == XRAM_MSG_HDR);
        // LOGINT(rx_hdr.type);LOGINT(rx_hdr.len);LOGINT(rx_hdr.err);LOGINT(s_plunder_rx_hdr_en);
        csi_dcache_clean_invalid_range((uint64_t *)&rx_hdr, XRAM_MSG_HDR);

        /* 抢夺接收数据，当s_plunder_rx_hdr_en && rx_hdr.len == 0时，认为是对端的响应数据 */
        if (s_plunder_rx_hdr_en && rx_hdr.len == 0) {
            memcpy(&s_plunder_rx_hdr, &rx_hdr, sizeof(rx_hdr));
            s_plunder_rx_hdr_en = 0;
            continue;
        }

        switch (rx_hdr.type) {
            case M1S_XRAM_TYPE_UARTP: {
                // m1s_c906_xram_uartp_operation_handle(rx_hdr.len);
                break;
            }
            default: {
                printf("xram operate type err.\r\n");
                break;
            }
        }
    }
}

static void proc_xram_task(void *pvParameters)
{
    if (0 != XRAMHeadInit()) {
        puts("Init XRAM head failed.\r\n");
        goto _exit;
    }

    if (0 != XRAMRingInit()) {
        puts("Init XRAM failed.\r\n");
        goto _exit;
    }
    XRAMRingReset(XRAM_OP_QUEUE);
    m1s_c906_xram_operation_handle();
_exit:
    vTaskDelete(NULL);
}

void m1s_c906_xram_init(void)
{
    static uint8_t is_init = 0;
    if (is_init) return;

    m1s_c906_xram_mutex_init();
    xTaskCreate(proc_xram_task, "xram_task", 512, NULL, 16, NULL);
    is_init = 1;
}
