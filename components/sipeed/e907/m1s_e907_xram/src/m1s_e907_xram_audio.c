#include "m1s_e907_xram_audio.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "FreeRTOS.h"
#include "audio_player.h"
#include "bl808_common.h"
#include "bl808_glb.h"
#include "queue.h"
#pragma GCC diagnostic ignored "-Wint-conversion"
struct {
    uint8_t flush_id;
    uint8_t start;
    uint8_t *buf[2];
    uint8_t buf_sta[2];
    int buff_size;
    int curr_size;
} private;

/****************************************************************************
 *                               Recv Handle
 ****************************************************************************/
static void audio_task(void *param)
{
    audio_player_t *player = NULL;
    audio_player_get(&player);
    assert(player != NULL);

    while (1) {
        if (!private.start) {
            vTaskDelete(NULL);
        }

        int len = player->record_read(player, private.buf[private.flush_id], private.buff_size - private.curr_size);
        csi_dcache_clean_invalid_range((void *)private.buf[private.flush_id], private.buff_size - private.curr_size);
        private.curr_size += len;
        if (private.buff_size == private.curr_size) {  // 切换缓存
            private.buf_sta[private.flush_id] = 1;     // 0,空；1，满；2，刷新中；3，占用中
            if (private.buf_sta[!private.flush_id] != 3) {
                private.flush_id = !private.flush_id;
            }
            private.buf_sta[private.flush_id] = 2;
            private.curr_size = 0;
        }

        vTaskDelay(1);
    }
}

static int audio_init(AUDIO_SAMPLE_RATE_TYPE sample_rate, AUDIO_SAMPLE_CODE_TYPE code)
{
    /* only support samplerate 16000, code signel littlt-endian 16bit pcm, signed channel  */
    if (AUDIO_SAMPLERATE_16K != sample_rate || AUDIO_CODE_SIGNED_16LB_PCM != code) return -1;

    audio_player_t *player = NULL;
    audio_player_init();
    audio_player_get(&player);
    if (player != NULL) {
        player->init(player);
    } else {
        printf("player init fail!\r\n");
        return -1;
    }

    if (pdTRUE != (xTaskCreate(audio_task, "audio task", 256, NULL, 15, NULL))) {
        return -1;
    }
    return 0;
}

static int xram_audio_init(m1s_xram_audio_t *op)
{
    struct xram_hdr hdr;
    uint32_t bytes;
    enum audio_op_err err = AUDIO_OP_OK;

    /* audio init */
    if (0 != audio_init(op->init.sample_rate, op->init.coding)) {
        err = AUDIO_OP_ERR;
    }

    private.buf[0] = (uint8_t *)op->init.buff0;
    private.buf[1] = (uint8_t *)op->init.buff1;
    private.buff_size = op->init.buff_size;
    private.curr_size = 0;
    private.start = 1;

    /* xram response */
    hdr.type = M1S_XRAM_TYPE_AUDIO;
    hdr.err = err;
    hdr.len = 0;
    bytes = XRAMRingWrite(XRAM_OP_QUEUE, &hdr, sizeof(struct xram_hdr));
    if (bytes == sizeof(struct xram_hdr)) {
        return AUDIO_OP_OK;
    } else {
        printf("xram ring write err.\r\n");
        return AUDIO_OP_ERR;
    }
}

static int xram_audio_deinit(m1s_xram_audio_t *op)
{
    struct xram_hdr hdr;
    uint32_t bytes;

    /* audio deinit */
    audio_player_deinit();
    private.start = 0;

    /* xram response */
    hdr.type = M1S_XRAM_TYPE_AUDIO;
    hdr.err = AUDIO_OP_OK;
    hdr.len = 0;
    bytes = XRAMRingWrite(XRAM_OP_QUEUE, &hdr, sizeof(struct xram_hdr));
    if (bytes == sizeof(struct xram_hdr)) {
        return AUDIO_OP_OK;
    } else {
        printf("xram ring write err.\r\n");
        return AUDIO_OP_ERR;
    }
}

static int xram_audio_get(m1s_xram_audio_t *op)
{
    struct xram_hdr hdr;
    uint32_t bytes;
    enum audio_op_err err = AUDIO_OP_OK;

    /* audio get */
    uint32_t *buff_addr = op->get.buff;
    uint32_t *buff_size = op->get.buff_size;
    int i = 0;
    csi_dcache_clean_range(buff_addr, sizeof(uint32_t));
    csi_dcache_clean_range(buff_size, sizeof(uint32_t));
    for (; i < sizeof(private.buf_sta); i++) {
        if (private.buf_sta[i] == 1) {
            private.buf_sta[i] = 3;
            *buff_addr = (uint32_t) private.buf[i];
            *buff_size = (uint32_t) private.buff_size;
            printf("*op->get.buff:%p  op->get.buff_size:%p buff_addr:%lx buff_size:%lx\r\n", buff_addr, buff_size, *buff_addr, *buff_size);
            break;
        }
    }

    if (i >= sizeof(private.buf_sta)) {
        *buff_addr = 0x0;
        *buff_size = 0x0;
    }
    csi_dcache_clean_invalid_range(buff_addr, sizeof(uint32_t));
    csi_dcache_clean_invalid_range(buff_size, sizeof(uint32_t));

    /* xram response */
    hdr.type = M1S_XRAM_TYPE_AUDIO;
    hdr.err = err;
    hdr.len = 0;
    bytes = XRAMRingWrite(XRAM_OP_QUEUE, &hdr, sizeof(struct xram_hdr));
    if (bytes == sizeof(struct xram_hdr)) {
        return AUDIO_OP_OK;
    } else {
        printf("xram ring write err.\r\n");
        return AUDIO_OP_ERR;
    }
}

static int xram_audio_pop(m1s_xram_audio_t *op)
{
    struct xram_hdr hdr;
    uint32_t bytes;
    enum audio_op_err err = AUDIO_OP_OK;

    /* audio pop */
    for (int i = 0; i < sizeof(private.buf_sta); i++) {
        if (private.buf_sta[i] == 3) {
            private.buf_sta[i] = 0;
        }
    }

    /* xram response */
    hdr.type = M1S_XRAM_TYPE_AUDIO;
    hdr.err = err;
    hdr.len = 0;
    bytes = XRAMRingWrite(XRAM_OP_QUEUE, &hdr, sizeof(struct xram_hdr));
    if (bytes == sizeof(struct xram_hdr)) {
        return AUDIO_OP_OK;
    } else {
        printf("xram ring write err.\r\n");
        return AUDIO_OP_ERR;
    }
}

void m1s_e907_xram_audio_operation_handle(uint32_t len)
{
    m1s_xram_audio_t obj_op;
    uint32_t bytes;

    bytes = XRAMRingRead(XRAM_OP_QUEUE, &obj_op, len);
    if (bytes == sizeof(m1s_xram_audio_t)) {
        switch (obj_op.op) {
            case XRAM_AUDIO_INIT: {
                xram_audio_init(&obj_op);
                break;
            }
            case XRAM_AUDIO_DEINIT: {
                xram_audio_deinit(&obj_op);
                break;
            }
            case XRAM_AUDIO_GET: {
                xram_audio_get(&obj_op);
                break;
            }
            case XRAM_AUDIO_POP: {
                xram_audio_pop(&obj_op);
                break;
            }
            default: {
                printf("xram audio operate type err.\r\n");
                break;
            }
        }
    }
}
