#ifndef __RING_H_
#define __RING_H_

#include <stdint.h>
#include "xram.h"
// #include "xram_platform.h"

/* NOTE: must be a value power of two */
#define RING_BUFFER_MIN_SIZE 512

/** Memory barriers */
#define mb() __DSB()
#define rmb() __DSB()
#define wmb() __DSB()

struct xram_ring {
    uint16_t head;
    uint16_t tail;
    uint32_t buffer_size;
    uint8_t buffer[];
};
typedef struct xram_ring *xram_ring_t;

struct ring_pos {
    // uint32_t head[XRAM_RING_ID_MAX];
    // uint32_t tail[XRAM_RING_ID_MAX];
    uint32_t head[16];
    uint32_t tail[16];
};

typedef struct ring_pos *ring_pos_t;
#define RING_POSITION_LEN (sizeof(struct ring_pos))
#define RING_TYPE_TX 0
#define RING_TYPE_RX 1

/* EM Region */
#define XRAM_RING_ADDRESS (0x22020000)

#define RING_HEAD_POS(x) ((void *)(x->head + XRAM_RING_ADDRESS))
#define RING_TAIL_POS(x) ((void *)(x->tail + XRAM_RING_ADDRESS))

#define RING_HEAD(x) (*(uint32_t *)(x->head + XRAM_RING_ADDRESS))
#define RING_TAIL(x) (*(uint32_t *)(x->tail + XRAM_RING_ADDRESS))

struct ring_dma {
    uint8_t *src;
    uint32_t len;
};

#define XRAM_RING_HEADER_SIZE (sizeof(struct xram_ring))

void debug_pos(uint32_t i);
xram_ring_t xram_ring_init(void *const buffer, uint32_t buffer_size, uint32_t ring_id, uint32_t cpu, uint32_t flag);
void xram_ring_reset(xram_ring_t ring);
int xram_ring_is_empty(xram_ring_t ring);
int xram_ring_is_full(xram_ring_t ring);

uint32_t xram_ring_used_length(xram_ring_t ring);
uint32_t xram_ring_free_length(xram_ring_t ring);
uint32_t xram_ring_read(xram_ring_t ring, uint8_t *des, uint32_t size);
uint32_t xram_ring_write(xram_ring_t ring, uint8_t *src, uint32_t size);
uint32_t xram_ring_get_dma_node(xram_ring_t ring, struct ring_dma *node, uint32_t size);
#endif

