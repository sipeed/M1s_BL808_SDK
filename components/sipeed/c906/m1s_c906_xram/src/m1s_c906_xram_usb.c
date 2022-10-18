#include "m1s_c906_xram_usb.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/****************************************************************************
 *                                Send Handle
 ****************************************************************************/
static int m1s_xram_usb_operation(m1s_xram_usb_t *obj, enum usb_operation operation)
{
    struct xram_hdr tx_hdr;
    uint32_t bytes;
    int ret = -1;

    assert(obj != NULL);

    if (m1s_c906_xram_mutex_lock()) {
        return -1;
    }

    tx_hdr.type = M1S_XRAM_TYPE_USB;
    tx_hdr.err = USB_OP_OK;
    tx_hdr.len = sizeof(m1s_xram_usb_t);
    obj->op = operation;

    bytes = XRAMRingWrite(XRAM_OP_QUEUE, &tx_hdr, sizeof(struct xram_hdr));
    bytes += XRAMRingWrite(XRAM_OP_QUEUE, obj, sizeof(m1s_xram_usb_t));
    if (bytes != sizeof(struct xram_hdr) + sizeof(m1s_xram_usb_t)) {
        printf("xram write operate err.\r\n");
    } else {
        struct xram_hdr *hdr = m1s_c906_xram_plunder_rx_hdr();
        if (hdr && hdr->type == M1S_XRAM_TYPE_USB && hdr->err == USB_OP_OK && hdr->len == 0) {
            ret = 0;
        } else {
            printf("xram plunder rx hdr err.\r\n");
        }
    }

    m1s_c906_xram_mutex_unlock();
    return ret;
}

int m1s_xram_usb_cam_init(void)
{
    m1s_xram_usb_t op = {0};
    return m1s_xram_usb_operation(&op, XRAM_USB_INIT);
}

int m1s_xram_usb_deinit(void)
{
    m1s_xram_usb_t op = {0};
    return m1s_xram_usb_operation(&op, XRAM_USB_DEINIT);
}