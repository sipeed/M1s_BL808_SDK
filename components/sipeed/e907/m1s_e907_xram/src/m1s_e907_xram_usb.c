#include "m1s_e907_xram_usb.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "FreeRTOS.h"
#include "bl_usb_cam.h"
#include "queue.h"

/****************************************************************************
 *                               Recv Handle
 ****************************************************************************/
static void usb_task(void *param)
{
    while (1) {
        bl_usb_cam_transfer();
        vTaskDelay(5);
    }

    vTaskDelete(NULL);
}

static int usb_init()
{
    if (0 != bl_usb_cam_init()) {
        printf("usb cam init failed!\r\n");
        return -1;
    }

    if (pdTRUE != xTaskCreate(usb_task, "usb task", 256, NULL, 20, NULL)) {
        return -1;
    }

    return 0;
}

static int xram_usb_init(m1s_xram_usb_t *op)
{
    struct xram_hdr hdr;
    uint32_t bytes;
    enum usb_op_err err = USB_OP_OK;

    /* usb init */
    if (0 != usb_init()) {
        err = USB_OP_ERR;
    }

    /* xram response */
    hdr.type = M1S_XRAM_TYPE_USB;
    hdr.err = err;
    hdr.len = 0;
    bytes = XRAMRingWrite(XRAM_OP_QUEUE, &hdr, sizeof(struct xram_hdr));
    if (bytes == sizeof(struct xram_hdr)) {
        return USB_OP_OK;
    } else {
        printf("xram ring write err.\r\n");
        return USB_OP_ERR;
    }
}

static int xram_usb_deinit(m1s_xram_usb_t *op)
{
    struct xram_hdr hdr;
    uint32_t bytes;

    /* usb deinit */

    /* xram response */
    hdr.type = M1S_XRAM_TYPE_USB;
    hdr.err = USB_OP_OK;
    hdr.len = 0;
    bytes = XRAMRingWrite(XRAM_OP_QUEUE, &hdr, sizeof(struct xram_hdr));
    if (bytes == sizeof(struct xram_hdr)) {
        return USB_OP_OK;
    } else {
        printf("xram ring write err.\r\n");
        return USB_OP_ERR;
    }
}

void m1s_e907_xram_usb_operation_handle(uint32_t len)
{
    m1s_xram_usb_t obj_op;
    uint32_t bytes;

    bytes = XRAMRingRead(XRAM_OP_QUEUE, &obj_op, len);
    if (bytes == sizeof(m1s_xram_usb_t)) {
        switch (obj_op.op) {
            case XRAM_USB_INIT: {
                xram_usb_init(&obj_op);
                break;
            }
            case XRAM_USB_DEINIT: {
                xram_usb_deinit(&obj_op);
                break;
            }
            default: {
                printf("xram usb operate type err.\r\n");
                break;
            }
        }
    }
}
