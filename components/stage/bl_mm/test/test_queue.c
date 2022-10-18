#include <stdint.h>
#include <string.h>
#include <FreeRTOS.h>
#include <aos/kernel.h>
#include <task.h>
#include "bl808_common.h"
#include "mm_osal.h"

typedef struct test_msg {
    uint32_t type;
    uint32_t data;
} test_msg_t;

void test_queue_send_task(void *param)
{
    int ret = -1, index = 0;
    test_msg_t msg = {0};
    TaskHandle_t task_handle = NULL;
    void *queue = NULL;

    task_handle = xTaskGetCurrentTaskHandle();

    queue = param;
    if (!queue) {
        BL_LOGE("Queue handle is null!!\r\n");
        vTaskDelete(task_handle);
    }

    /* Put item into queue */
    for (index = 0; index < 10; index++) {
        msg.type = index;
        msg.data = 100 + index;

        ret = BL_Queue_Put_Item(queue, &msg);
        if (pdFALSE == ret) {
            BL_LOGE("Put item into queue fail!!\r\n");
        } else {
            BL_LOGI("Put queue, index:%d, data:%d\r\n", index, msg.data);
        }

        vTaskDelay(10);
    }

    BL_LOGI("Put item into queue over!!\r\n");

    vTaskDelete(task_handle);
}

void test_queue_recv_task(void *param)
{
    int ret = -1, index = 0;
    test_msg_t msg = {0};
    TaskHandle_t task_handle = NULL;
    void *queue = NULL;

    task_handle = xTaskGetCurrentTaskHandle();

    queue = param;
    if (!queue) {
        BL_LOGE("Queue handle is null!!\r\n");
        vTaskDelete(task_handle);
    }

    /* Get item from queue */
    for (index = 0; index < 10; index++) {
        memset(&msg, 0, sizeof(test_msg_t));
        ret = BL_Queue_Get_Item(queue, &msg, QUEUE_WAIT_FOREVER);
        if (pdFALSE == ret) {
            BL_LOGE("Get item from queue fail!!\r\n");
        } else {
            BL_LOGI("Get queue, index:%d, data:%d\r\n", index, msg.data);
        }
    }    

    BL_LOGI("Get item into queue over!!\r\n");

    /* Destroy a queue istance */
    BL_Queue_Delete(queue);

    vTaskDelete(task_handle);
}

void test_queue_within_two_tasks_main()
{
    void *queue = NULL;
    test_msg_t msg = {0};
    uint32_t queue_len = 20;

    /* Create a queue istance */
    queue = BL_Queue_Create(queue_len, sizeof(test_msg_t));
    if (!queue) {
        BL_LOGE("Create queue fail!!\r\n");
        return;
    }

    aos_task_new((char*)"test_queue send task", test_queue_send_task, (void *)queue, 1024);

    aos_task_new((char*)"test_queue recv task", test_queue_recv_task, (void *)queue, 1024);
}

void test_queue_full_task(void *param)
{
    int ret;
    void *queue = NULL;
    test_msg_t msg = {1, 100};
    uint32_t queue_len = 10, space_len = 0, index = 0;
    TaskHandle_t task_handle = NULL;

    task_handle = xTaskGetCurrentTaskHandle();

    /* Create a queue istance */
    queue = BL_Queue_Create(queue_len, sizeof(test_msg_t));
    if (!queue) {
        BL_LOGE("Create queue fail!!\r\n");
        vTaskDelete(task_handle);
    }

    /* Get current space len */
    space_len = BL_Queue_Get_Spaces_Available(queue);
    BL_LOGI("The queue current space len:%d\r\n", space_len);

    /* Put item into queue */
    for (index = 0; index < 20; index++) {
        ret = BL_Queue_Put_Item(queue, &msg);
        if (pdFALSE == ret) {
            BL_LOGE("Put queue fail!! index:%d\r\n", index);
        } else {
            BL_LOGI("Put queue, index:%d, data:%d\r\n", index, msg.data);
        }

        vTaskDelay(10);
    }

    /* Get current space len */
    space_len = BL_Queue_Get_Spaces_Available(queue);
    BL_LOGI("The queue current space len:%d\r\n", space_len);

    /* Reset queue */
    ret = BL_Queue_Reset(queue);
    if (pdFAIL == ret) {
        BL_LOGI("Reset queue fail\r\n");
    }

    /* Get current space len */
    space_len = BL_Queue_Get_Spaces_Available(queue);
    BL_LOGI("After reset queue, the queue current space len:%d\r\n", space_len);

    /* Destroy a queue istance */
    BL_Queue_Delete(queue);

    vTaskDelete(task_handle);
}

void test_queue_full_main(void)
{
    aos_task_new((char*)"test queue full task", test_queue_full_task, NULL, 1024);
}

void test_queue_empty_task(void *param)
{
    int ret;
    void *queue = NULL;
    test_msg_t msg = {1, 100};
    uint32_t queue_len = 10, space_len = 0, index = 0, wait_time = 1000;
    TaskHandle_t task_handle = NULL;

    task_handle = xTaskGetCurrentTaskHandle();

    /* Create a queue istance */
    queue = BL_Queue_Create(queue_len, sizeof(test_msg_t));
    if (!queue) {
        BL_LOGE("Create queue fail!!\r\n");
        vTaskDelete(task_handle);
    }

    /* Get current space len */
    space_len = BL_Queue_Get_Spaces_Available(queue);
    BL_LOGI("The queue current space len:%d\r\n", space_len);

    /* Get item from queue */
    for (index = 0; index < 10; index++) {
        memset(&msg, 0, sizeof(test_msg_t));
        ret = BL_Queue_Get_Item(queue, &msg, wait_time);
        if (pdFALSE == ret) {
            BL_LOGE("Get item from queue fail!! index:%d\r\n", index);
        } else {
            BL_LOGI("Get queue, index:%d, data:%d\r\n", index, msg.data);
        }
    }  

    /* Get current space len */
    space_len = BL_Queue_Get_Spaces_Available(queue);
    BL_LOGI("The queue current space len:%d\r\n", space_len);

    /* Destroy a queue istance */
    BL_Queue_Delete(queue);

    vTaskDelete(task_handle);
}

void test_queue_empty_main(void)
{
    aos_task_new((char*)"test queue empty task", test_queue_empty_task, NULL, 1024);
}

void *queue_test_put_fromISR = NULL;
/* Test put queue in isr, call following func in isr */
void test_queue_put_isr()
{
    static int cnt = 0;
    int ret;

    if(!queue_test_put_fromISR)
        return;

    cnt++;
    if (cnt > 10)
		return;

    ret = BL_Queue_Put_Item_FromISR(queue_test_put_fromISR, &cnt);
    if (pdFALSE == ret) {
        BL_LOGE("Put item into queue fail in isr!! cnt:%d\r\n", cnt);
    } else {
        BL_LOGI("Put queue in ISR, data:%d\r\n", cnt);
    }
}

void test_queue_put_fromISR_task(void *param)
{
    int ret;
    uint32_t index = 0, data, queue_len = 5;
    TaskHandle_t task_handle = NULL;

	task_handle = xTaskGetCurrentTaskHandle();

    /* Create a queue istance */
    queue_test_put_fromISR = BL_Queue_Create(queue_len, sizeof(uint32_t));
    if (!queue_test_put_fromISR) {
        BL_LOGE("Create queue fail!!\r\n");
        return;
    }

    /* Test queue full in isr */
    vTaskDelay(10000);

    /* Get item from queue */
    for (index = 0; index < 5; index++) {
        data = 0;
        ret = BL_Queue_Get_Item(queue_test_put_fromISR, &data, QUEUE_WAIT_FOREVER);
        if (pdFALSE == ret) {
            BL_LOGE("Get item from queue fail!! index:%d\r\n", index);
        } else {
            BL_LOGI("Get queue, index:%d, data:%d\r\n", index, data);
        }
    }  

    /* Destroy a queue istance */
    BL_Queue_Delete(queue_test_put_fromISR);

    vTaskDelete(task_handle);
}

void test_queue_put_fromISR_main(void)
{
    aos_task_new((char*)"test queue put from ISR task", test_queue_put_fromISR_task, NULL, 1024);
}

void *queue_test_get_fromISR = NULL;
/* Test get queue in isr, call following func in isr */
void test_queue_get_isr()
{
    static int cnt = 0;
    int ret;
    int data;
    if(!queue_test_get_fromISR)
		return;

    cnt++;
    if (cnt > 15)
		return;

    ret = BL_Queue_Get_Item_FromISR(queue_test_get_fromISR, &data);
    if (pdFALSE == ret) {
        BL_LOGE("Get item into queue fail in isr!! cnt:%d\r\n", cnt);
    } else {
        BL_LOGI("Get queue in ISR, data:%d\r\n", data);
    }
}

void test_queue_get_fromISR_task(void *param)
{
    int ret;
    uint32_t queue_len = 10, space_len = 0, index = 0;
    TaskHandle_t task_handle = NULL;

    task_handle = xTaskGetCurrentTaskHandle();

    /* Create a queue istance */
    queue_test_get_fromISR = BL_Queue_Create(queue_len, sizeof(uint32_t));
    if (!queue_test_get_fromISR) {
        BL_LOGE("Create queue fail!!\r\n");
        vTaskDelete(task_handle);
    }

    /* Put item into queue */
    for (index = 0; index < 10; index++) {
        ret = BL_Queue_Put_Item(queue_test_get_fromISR, &index);
        if (pdFALSE == ret) {
            BL_LOGE("Put item into queue fail!!\r\n");
        } else {
            BL_LOGI("Put queue, data:%d\r\n", index);
        }

        vTaskDelay(10);
    }

    BL_LOGI("Put item into queue over!!\r\n");

    vTaskDelete(task_handle);
}

void test_queue_get_fromISR_main(void)
{
    aos_task_new((char*)"test queue get from ISR task", test_queue_get_fromISR_task, NULL, 1024);
}
