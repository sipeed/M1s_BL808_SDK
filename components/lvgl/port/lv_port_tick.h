#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <FreeRTOS.h>
#include <task.h>

static inline uint32_t custom_tick_get(void)
{
#if 0
    static uint64_t start_ms = 0;
    if(start_ms == 0) {
        struct timeval tv_start;
        gettimeofday(&tv_start, NULL);
        start_ms = (tv_start.tv_sec * 1000000 + tv_start.tv_usec) / 1000;
    }

    struct timeval tv_now;
    gettimeofday(&tv_now, NULL);
    uint64_t now_ms;
    now_ms = (tv_now.tv_sec * 1000000 + tv_now.tv_usec) / 1000;

    uint32_t time_ms = now_ms - start_ms;
#endif
    return (uint32_t)xTaskGetTickCount();
}

