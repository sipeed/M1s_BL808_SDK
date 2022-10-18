#ifndef __M1S_COMMON_XRAM_USB_H
#define __M1S_COMMON_XRAM_USB_H

#include <stdint.h>

typedef enum usb_op_err {
    USB_OP_OK,
    USB_OP_ERR,
} USB_OP_ERR_TYPE;

enum usb_operation {
    XRAM_USB_INIT,
    XRAM_USB_DEINIT,
};

struct m1s_xram_usb {
    uint32_t op;
    union {
        struct {
            uint8_t sample_rate;
            uint8_t coding;
        } __attribute__((packed)) init;
    };
} __attribute__((packed));
typedef struct m1s_xram_usb m1s_xram_usb_t;

#endif
