#include "m1s_c906_xram_audio.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#pragma GCC diagnostic ignored "-Wint-conversion"
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"
/****************************************************************************
 *                                Send Handle
 ****************************************************************************/
static int m1s_xram_audio_operation(m1s_xram_audio_t *obj, enum audio_operation operation)
{
    struct xram_hdr tx_hdr;
    uint32_t bytes;
    int ret = -1;

    assert(obj != NULL);

    if (m1s_c906_xram_mutex_lock()) {
        return -1;
    }

    tx_hdr.type = M1S_XRAM_TYPE_AUDIO;
    tx_hdr.err = AUDIO_OP_OK;
    tx_hdr.len = sizeof(m1s_xram_audio_t);
    obj->op = operation;

    bytes = XRAMRingWrite(XRAM_OP_QUEUE, &tx_hdr, sizeof(struct xram_hdr));
    bytes += XRAMRingWrite(XRAM_OP_QUEUE, obj, sizeof(m1s_xram_audio_t));
    csi_dcache_clean_invalid();
    if (bytes != sizeof(struct xram_hdr) + sizeof(m1s_xram_audio_t)) {
        printf("xram write operate err.\r\n");
    } else {
        struct xram_hdr *hdr = m1s_c906_xram_plunder_rx_hdr();
        if (hdr && hdr->type == M1S_XRAM_TYPE_AUDIO && hdr->err == AUDIO_OP_OK && hdr->len == 0) {
            ret = 0;
        } else {
            printf("xram plunder rx hdr err.\r\n");
        }
    }

    m1s_c906_xram_mutex_unlock();
    return ret;
}

int m1s_xram_audio_init(uint16_t *buff, int buf_size)
{
    if (buf_size == 0 || buf_size % 2 != 0) return -1;
    m1s_xram_audio_t op = {0};
    op.init.coding = AUDIO_CODE_SIGNED_16LB_PCM;
    op.init.sample_rate = AUDIO_SAMPLERATE_16K;
    op.init.buff_size = buf_size >> 1;
    op.init.buff0 = buff;
    op.init.buff1 = buff + op.init.buff_size;
    return m1s_xram_audio_operation(&op, XRAM_AUDIO_INIT);
}

int m1s_xram_audio_deinit(void)
{
    m1s_xram_audio_t op = {0};
    return m1s_xram_audio_operation(&op, XRAM_AUDIO_DEINIT);
}

int m1s_xram_audio_get(uint16_t **buf, uint32_t *buf_size)
{
    m1s_xram_audio_t op = {0};
    *buf = NULL;
    op.get.buff = buf;
    op.get.buff_size = buf_size;
    return m1s_xram_audio_operation(&op, XRAM_AUDIO_GET);
}

int m1s_xram_audio_pop(void)
{
    m1s_xram_audio_t op = {0};
    return m1s_xram_audio_operation(&op, XRAM_AUDIO_POP);
}
/****************************************************************************
 *                               Recv Handle
 ****************************************************************************/
void m1s_c906_xram_audio_operation_handle(uint32_t len)
{
    m1s_xram_audio_t obj_op;
    uint32_t bytes;

    bytes = XRAMRingRead(XRAM_OP_QUEUE, &obj_op, len);
    if (bytes == sizeof(m1s_xram_audio_t)) {
        switch (obj_op.op) {
            default: {
                printf("xram audio operate type err.\r\n");
                break;
            }
        }
    }
}