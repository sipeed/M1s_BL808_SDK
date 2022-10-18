#include <bl808_comm_mm.h>
#include <mm_utility.h>

void* fifoGet(fifo_t *fifo)
{
    void *data;

    xSemaphoreTake(fifo->mutex, portMAX_DELAY);     /* enter critical section */

    if (fifo->dataslot == fifo->emptyslot) {
        fifo->getWaiting = TRUE;        /* tell putFifo to signal us when data is available */
        xSemaphoreGive(fifo->mutex);    /* leave critical section (allow input from HW ..) */
        xSemaphoreTake(fifo->getSem, portMAX_DELAY);    /* wait for new data */
        xSemaphoreTake(fifo->mutex, portMAX_DELAY);     /* reenter critical section */
    }

    data = fifo->data[fifo->dataslot++];
    fifo->len--;

    if (fifo->dataslot == FIFOSIZE) {
        fifo->dataslot = 0;
    }

    xSemaphoreGive(fifo->mutex);     /* leave critical section */
    return data;
}

void* fifoGetNonBlock(fifo_t *fifo)
{
    void *data;

    xSemaphoreTake(fifo->mutex, portMAX_DELAY);     /* enter critical section */

    if (fifo->dataslot == fifo->emptyslot) {
            /* empty fifo */
        data = NULL;
    } else {
        data = fifo->data[fifo->dataslot++];
        fifo->len--;

        if (fifo->dataslot == FIFOSIZE) {
            fifo->dataslot = 0;
        }
    }
    xSemaphoreGive(fifo->mutex);    /* leave critical section */
    return data;
}


void fifoPut(fifo_t *fifo, void *data)
{
    xSemaphoreTake(fifo->mutex, portMAX_DELAY);     /* enter critical section */

    BL_LOGI("fifoput: len%d dat%d empt%d --> ", fifo->len, fifo->dataslot, fifo->emptyslot);

    /* put the new data to empty slot */
    fifo->data[fifo->emptyslot] = data;

    fifo->emptyslot++;
    fifo->len++;

    BL_LOGI("len%d dat%d empt%d\r\n", fifo->len, fifo->dataslot, fifo->emptyslot);

    if ( fifo->len > FIFOSIZE )
    {
        printf( "ERROR: fifo overrun detected len=%d, flushing\n", fifo->len );
        fifo->dataslot  = 0;
        fifo->emptyslot = 0;
        fifo->len = 0;
    }

    if ( fifo->emptyslot == FIFOSIZE )
    {
        fifo->emptyslot = 0;
        BL_LOGI("fifo wrap.\r\n");

        xSemaphoreGive(fifo->mutex ); /* leave critical */
        return;
    }
    if ( fifo->getWaiting )
    {
        fifo->getWaiting = FALSE;
        xSemaphoreGive(fifo->getSem );
    }

    xSemaphoreGive(fifo->mutex); /* leave critical */
    return;
}


void fifoInit(fifo_t * fifo)
{
    fifo->dataslot  = 0;
    fifo->emptyslot = 0;
    fifo->len       = 0;

    fifo->mutex = xSemaphoreCreateMutex();
    fifo->getSem = xSemaphoreCreateBinary();

    fifo->getWaiting = FALSE;
}
