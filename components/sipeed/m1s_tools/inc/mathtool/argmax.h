#pragma once

#include <stdint.h>

#define ARGMAX(arr, size)                                         \
    ({                                                            \
        uint32_t __retidx = 0;                                    \
        do {                                                      \
            assert(size > 0);                                     \
            for (uint32_t __idx = 1; __idx < size; __idx++) {     \
                if (arr[__retidx] < arr[__idx]) __retidx = __idx; \
            }                                                     \
        } while (0);                                              \
        (__retidx);                                               \
    })