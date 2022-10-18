#include <FreeRTOS.h>
#include <queue.h>
#include "mm_osal.h"

inline void* BL_Queue_Create(uint32_t queue_len, uint32_t item_size)
{
    return xQueueCreate(queue_len, item_size);
}

inline void BL_Queue_Delete(void *queue)
{
    vQueueDelete(queue);
}

inline int BL_Queue_Put_Item(void *queue, void *item)
{
    return xQueueSend(queue, item, QUEUE_NO_WATI);
}

inline int BL_Queue_Get_Item(void *queue, void *buf, uint32_t wait_time)
{
    return xQueueReceive(queue, buf, wait_time);
}

inline int BL_Queue_Put_Item_FromISR(void *queue, void *item)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    return xQueueSendFromISR(queue, item, &xHigherPriorityTaskWoken);
}

inline int BL_Queue_Get_Item_FromISR(void *queue, void *buf)
{
    BaseType_t xTaskWokenByReceive = pdFALSE;
	
    return xQueueReceiveFromISR(queue, buf, &xTaskWokenByReceive);
}

inline uint32_t BL_Queue_Get_Spaces_Available(void *queue)
{
    return uxQueueSpacesAvailable(queue);
}

inline int BL_Queue_Reset(void *queue)
{
    return xQueueReset(queue);
}
