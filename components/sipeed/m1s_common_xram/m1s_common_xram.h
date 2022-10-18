#ifndef BL808_PERI_COMMON_H
#define BL808_PERI_COMMON_H

#include <ring.h>

#include "bl808_glb.h"

#define XRAM_OP_QUEUE XRAM_RING_ID_PERIPHERAL
enum m1s_xram_type {
    M1S_XRAM_TYPE_UARTP = 0x80,
    M1S_XRAM_TYPE_AUDIO = 0x81,
    M1S_XRAM_TYPE_WIFI = 0x82,
    M1S_XRAM_TYPE_PWM = 0x83,
    M1S_XRAM_TYPE_USB = 0x84,
    M1S_XRAM_TYPE_MAX,
};

struct xram_hdr {
    uint8_t type; /* msg type */
    uint8_t err;  /* err type */
    uint16_t len; /* msg length */
};
#define XRAM_MSG_HDR (sizeof(struct xram_hdr))

#endif
