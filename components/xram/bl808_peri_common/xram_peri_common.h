#ifndef BL808_PERI_COMMON_H
#define BL808_PERI_COMMON_H
#include "xram_flash_common.h"
#include "xram_pwm_common.h"
#include "xram_spi_common.h"

#define XRAM_PERI_OP_QUEUE XRAM_RING_ID_PERIPHERAL
enum xram_peri_type{
    XRAM_PERI_TYPE_FLASH = 0x31,
    XRAM_PERI_TYPE_PWM = 0x32,
    XRAM_PERI_TYPE_SPI = 0x33,
    XRAM_PERI_TYPE_MAX
};

struct xram_hdr {
    uint8_t type; /* msg type */
    uint8_t err;  /* err type */
    uint16_t len; /* msg length */
};
#define XRAM_MSG_HDR (sizeof(struct xram_hdr))

#endif
