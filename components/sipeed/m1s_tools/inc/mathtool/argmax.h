#pragma once

#include <assert.h>
#include <stdint.h>

#define ARGMAX_WITHOFF(arr, size, off)                                                \
    ({                                                                                \
        register uint32_t __retidx = 0;                                               \
        do {                                                                          \
            assert((size) > 0);                                                       \
            assert((off) > 0);                                                        \
            for (uint32_t __idx = 1; __idx < (size); __idx++) {                       \
                if ((arr)[__retidx * (off)] < (arr)[__idx * (off)]) __retidx = __idx; \
            }                                                                         \
        } while (0);                                                                  \
        (__retidx);                                                                   \
    })

#define ARGMAX(arr, size) ARGMAX_WITHOFF(arr, size, 1)