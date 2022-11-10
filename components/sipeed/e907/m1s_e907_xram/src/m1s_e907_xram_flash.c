#include "m1s_e907_xram_flash.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "FreeRTOS.h"
#include "bl808_common.h"
#include "bl808_glb.h"
#include "bl_flash.h"
#include "queue.h"
#pragma GCC diagnostic ignored "-Wint-conversion"

/****************************************************************************
 *                               Recv Handle
 ****************************************************************************/
// static inline void log_hex(unsigned int *a, uint32_t l)
// {
//     l /= 4;
//     for (uint32_t i = 0; i < l; i++) {
//         if ((i & 0x3) == 0) printf("%08x:", (unsigned int)&a[i]);
//         printf(" %08x", a[i]);
//         if ((i & 0x3) == 0x3) printf("\r\n");
//     }
//     if (l & 0x3) printf("\r\n");
// }

static int xram_flash_read(m1s_xram_flash_t *op)
{
    struct xram_hdr hdr;
    uint32_t bytes;
    enum flash_op_err err = FLASH_OP_OK;

    /* flash deinit */
    if (0 != bl_flash_read(op->offset, op->addr, op->len)) {
        err = FLASH_OP_ERR;
    }
    // log_hex(op->addr, op->len);
    csi_dcache_clean_invalid_range((uint8_t *)op->addr, op->len);

    /* xram response */
    hdr.type = M1S_XRAM_TYPE_FLASH;
    hdr.err = err;
    hdr.len = 0;
    bytes = XRAMRingWrite(XRAM_OP_QUEUE, &hdr, sizeof(struct xram_hdr));
    if (bytes == sizeof(struct xram_hdr)) {
        return FLASH_OP_OK;
    } else {
        printf("xram ring write err.\r\n");
        return FLASH_OP_ERR;
    }
}

static int xram_flash_write(m1s_xram_flash_t *op)
{
    struct xram_hdr hdr;
    uint32_t bytes;
    enum flash_op_err err = FLASH_OP_OK;

    csi_dcache_invalid_range((uint8_t *)op->addr, op->len);
    // log_hex(op->addr, op->len);
    /* flash deinit */
    if (0 != bl_flash_write(op->offset, op->addr, op->len)) {
        err = FLASH_OP_ERR;
    }

    /* xram response */
    hdr.type = M1S_XRAM_TYPE_FLASH;
    hdr.err = err;
    hdr.len = 0;
    bytes = XRAMRingWrite(XRAM_OP_QUEUE, &hdr, sizeof(struct xram_hdr));
    if (bytes == sizeof(struct xram_hdr)) {
        return FLASH_OP_OK;
    } else {
        printf("xram ring write err.\r\n");
        return FLASH_OP_ERR;
    }
}

static int xram_flash_erase(m1s_xram_flash_t *op)
{
    struct xram_hdr hdr;
    uint32_t bytes;
    enum flash_op_err err = FLASH_OP_OK;

    /* flash deinit */
    if (0 != bl_flash_erase(op->offset, op->len)) {
        err = FLASH_OP_ERR;
    }

    /* xram response */
    hdr.type = M1S_XRAM_TYPE_FLASH;
    hdr.err = err;
    hdr.len = 0;
    bytes = XRAMRingWrite(XRAM_OP_QUEUE, &hdr, sizeof(struct xram_hdr));
    if (bytes == sizeof(struct xram_hdr)) {
        return FLASH_OP_OK;
    } else {
        printf("xram ring write err.\r\n");
        return FLASH_OP_ERR;
    }
}

void m1s_e907_xram_flash_operation_handle(uint32_t len)
{
    m1s_xram_flash_t obj_op;
    uint32_t bytes;

    bytes = XRAMRingRead(XRAM_OP_QUEUE, &obj_op, len);
    if (bytes == sizeof(m1s_xram_flash_t)) {
        // printf("xram flash handle %s, off:%#x, addr:%#x, len:%#x\r\n",
        //        (obj_op.op == XRAM_FLASH_READ)    ? "read"
        //        : (obj_op.op == XRAM_FLASH_WRITE) ? "write"
        //                                          : "erase",
        //        (unsigned int)obj_op.offset, (unsigned int)obj_op.addr, (unsigned int)obj_op.len);
        switch (obj_op.op) {
            case XRAM_FLASH_READ: {
                xram_flash_read(&obj_op);
                break;
            }
            case XRAM_FLASH_WRITE: {
                xram_flash_write(&obj_op);
                break;
            }
            case XRAM_FLASH_ERASE: {
                xram_flash_erase(&obj_op);
                break;
            }
            default: {
                printf("xram flash operate type err.\r\n");
                break;
            }
        }
    }
}
