#ifndef BL808_FLASH_COMMON_H
#define BL808_FLASH_COMMON_H

#define XRAM_ADDR_LIMIT (0x1000000)

#define FLASH_OPERATION_MAX_SIZE (256)

enum xram_flash_id {
    XRAM_FLASH_ID_0,
    XRAM_FLASH_ID_1,
    XRAM_FLASH_ID_2,
    XRAM_FLASH_ID_3,
    XRAM_FLASH_ID_4,
    XRAM_FLASH_ID_5,
    XRAM_FLASH_ID_6,
    XRAM_FLASH_ID_MAX
};

typedef enum flash_op_err {
    FLASH_OP_OK,
    FLASH_OP_ERR
} FLASH_OP_ERR_TYPE;

enum flash_operation {
    XRAM_FLASH_CREATE,
    XRAM_FLASH_DESTROY,
    XRAM_FLASH_READ,
    XRAM_FLASH_WRITE,
    XRAM_FLASH_ERASE
};

struct xram_flash_op {
    uint32_t flash_id;  /* flash id */
    uint32_t size;      /* flash size */
    uint32_t offset;    /* the offset of flash address */
    uint32_t len;       /* flash operation range */
    uint8_t op;         /* flsh operation type*/
    uint8_t data[];
};
typedef struct xram_flash_op *xram_flash_op_t;
#define XRAM_FLASH_OPERATION (sizeof(struct xram_flash_op))

#endif
