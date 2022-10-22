#include "m1s_c906_xram_flash.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/****************************************************************************
 *                                Send Handle
 ****************************************************************************/
static m1s_xram_flash_t op = {0};

static int m1s_xram_flash_operation(m1s_xram_flash_t *obj, enum flash_operation operation)
{
    struct xram_hdr tx_hdr;
    uint32_t bytes;
    int ret = -1;

    assert(obj != NULL);

    if (m1s_c906_xram_mutex_lock()) {
        return -1;
    }

    tx_hdr.type = M1S_XRAM_TYPE_FLASH;
    tx_hdr.err = FLASH_OP_OK;
    tx_hdr.len = sizeof(m1s_xram_flash_t);
    obj->op = operation;
    // printf("[xram][flash]%s off:%#x, addr:%#x, len:%#x\r\n", (operation==XRAM_FLASH_READ)?"read":(operation==XRAM_FLASH_WRITE)?"write":"erase", obj->offset, obj->addr, obj->len);
    // FIXME: the offset of flash is not equal to the partition table provided to the bflb dev cube
    obj->offset += 0x1000;
    bytes = XRAMRingWrite(XRAM_OP_QUEUE, &tx_hdr, sizeof(struct xram_hdr));
    bytes += XRAMRingWrite(XRAM_OP_QUEUE, obj, sizeof(m1s_xram_flash_t));
    if (bytes != sizeof(struct xram_hdr) + sizeof(m1s_xram_flash_t)) {
        printf("xram write operate err.\r\n");
    } else {
        struct xram_hdr *hdr = m1s_c906_xram_plunder_rx_hdr();
        if (hdr && hdr->type == M1S_XRAM_TYPE_FLASH && hdr->err == FLASH_OP_OK && hdr->len == 0) {
            ret = 0;
        } else {
            printf("xram plunder rx hdr err.\r\n");
        }
    }

    m1s_c906_xram_mutex_unlock();
    if (0 == ret && XRAM_FLASH_ERASE != operation) {
        csi_dcache_clean_invalid_range((uint64_t)obj->addr, obj->len);
    }
    return ret;
}

int m1s_xram_flash_read(uint32_t offset, uint32_t addr, uint32_t len)
{
    op.offset = offset;
    op.addr = addr;
    op.len = len;
    return m1s_xram_flash_operation(&op, XRAM_FLASH_READ);
}

int m1s_xram_flash_write(uint32_t offset, uint32_t addr, uint32_t len)
{
    op.offset = offset;
    op.addr = addr;
    op.len = len;
    return m1s_xram_flash_operation(&op, XRAM_FLASH_WRITE);
}

int m1s_xram_flash_erase(uint32_t offset, uint32_t len)
{
    op.offset = offset;
    op.len = len;
    return m1s_xram_flash_operation(&op, XRAM_FLASH_ERASE);
}
