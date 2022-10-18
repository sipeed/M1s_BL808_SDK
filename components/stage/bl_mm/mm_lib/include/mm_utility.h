#ifndef __MM_UTILITY_H__
#define __MM_UTILITY_H__

#include <FreeRTOS.h>
#include <semphr.h>


/***************************** Fifo ************************************/
/** How many bytes in fifo */
#define FIFOSIZE 2048

/** fifo data structure, this one is passed to all fifo functions */
typedef struct fifo_t {
  void *data[FIFOSIZE]; /* data segment, +10 is a hack probably not needed.. FIXME! */
  int dataslot;           /* index to next char to be read */
  int emptyslot;          /* index to next empty slot */
  int len;                /* len probably not needed, may be calculated from dataslot and emptyslot in conjunction with FIFOSIZE */

  SemaphoreHandle_t mutex;      /* semaphore protecting simultaneous data manipulation */
  SemaphoreHandle_t getSem;     /* sepaphore used to signal new data if getWaiting is set */
  uint8_t getWaiting;       /* flag used to indicate that fifoget is waiting for data. fifoput is suposed to clear */
                        /* this flag prior to signaling the getSem semaphore */
} fifo_t;


/**
*   Get a character from fifo
*   Blocking call.
*   @param  fifo pointer to fifo data structure
*   @return character read from fifo
*/
void* fifoGet(fifo_t *fifo);

/**
*   Get a character from fifo
*   Non blocking call.
*   @param  fifo pointer to fifo data structure
*   @return character read from fifo, or < zero if non was available
*/
void* fifoGetNonBlock(fifo_t *fifo);

/**
*   fifoput is called by the signalhandler when new data has arrived (or some other event is indicated)
*   fifoput reads directly from the serialport and is thus highly dependent on unix arch at this moment
*   @param  fifo pointer to fifo data structure
*   @param  fd  unix file descriptor
*/
void fifoPut(fifo_t *fifo, void *data);

/**
*   fifoinit initiate fifo
*   @param  fifo    pointer to fifo data structure, allocated by the user
*/
void fifoInit(fifo_t *fifo);

#endif