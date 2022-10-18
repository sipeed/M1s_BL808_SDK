#ifndef __MM_OSAL_H__
#define __MM_OSAL_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* Waiting time define when geting item from queue */
#define QUEUE_WAIT_FOREVER 0xffffffffUL
#define QUEUE_NO_WATI      0x0

/**
* Creates a new queue instance, and returns the queue handle.
*
* @param queue_len The maximum number of items that the queue can contain.
*
* @param item_size The number of bytes each item in the queue will require.
*
* @return instance pointer if create queue successfully, otherwise return NULL.
**/
void* BL_Queue_Create(uint32_t queue_len, uint32_t item_size);

/**
* Delete a new queue instance.
*
* @param queue The queue handle need to be deleted.
*
* @return void.
**/
void BL_Queue_Delete(void *queue);

/**
* Put item into queue in task.
*
* @param queue The queue handle.
*
* @param item The item will to be put into queue.
*
* @return pdTRUE(1) if put successfully, otherwise return pdFALSE(0).
**/
int BL_Queue_Put_Item(void *queue, void *item);

/**
* Get item from queue in task.
*
* @param queue The queue handle.
*
* @param buf Copy item data into the buffer.
*
* @param wait_time Wait time if the queue is empty.
*
* @return pdTRUE(1) if put successfully, otherwise return pdFALSE(0).
**/
int BL_Queue_Get_Item(void *queue, void *buf, uint32_t wait_time);

/**
* Put item into queue in interrupt.
*
* @param queue The queue handle.
*
* @param item The item will to be put into queue.
*
* @return pdTRUE(1) if put successfully, otherwise return pdFALSE(0).
**/
int BL_Queue_Put_Item_FromISR(void *queue, void *item);

/**
* Get item from queue in interrupt.
*
* @param queue The queue handle.
*
* @param buf Copy item data into the buffer.
*
* @return pdTRUE(1) if put successfully, otherwise return pdFALSE(0).
**/
int BL_Queue_Get_Item_FromISR(void *queue, void *buf);

/**
* Return the number of free spaces available in a queue.
*
* @param queue The queue handle.
*
* @return the number of free spaces available.
**/
uint32_t BL_Queue_Get_Spaces_Available(void *queue);

/**
* Reset a queue back to its original empty state.
*
* @param queue The queue handle.
*
* @param buf Copy item data into the buffer.
*
* @return pdPASS(1) if reset successfully, otherwise return pdFAIL(0).
**/
int BL_Queue_Reset(void *queue);


#ifdef __cplusplus
}
#endif

#endif //__MM_OSAL_H__
