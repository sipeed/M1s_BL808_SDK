#ifndef __M1S_COMMON_XRAM_FLASH_H
#define __M1S_COMMON_XRAM_FLASH_H

#include <stdint.h>

typedef enum flash_op_err {
    FLASH_OP_OK,
    FLASH_OP_ERR,
} FLASH_OP_ERR_TYPE;

enum flash_operation {
    XRAM_FLASH_READ,
    XRAM_FLASH_WRITE,
    XRAM_FLASH_ERASE,
};

struct m1s_xram_flash {
    uint32_t op;
    uint32_t offset;
    uint32_t addr;
    uint32_t len;
} __attribute__((packed));
typedef struct m1s_xram_flash m1s_xram_flash_t;

#endif
