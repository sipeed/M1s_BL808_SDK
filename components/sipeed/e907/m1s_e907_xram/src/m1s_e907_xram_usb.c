#include "m1s_e907_xram_usb.h"

#include <assert.h>
#include <hal/soc/sd.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <usbd_core.h>
#include <usbd_msc.h>

#include "FreeRTOS.h"
#include "bl_usb_cam.h"
#include "queue.h"

struct {
    sd_dev_t sd;
} private;

/****************************************************************************
 *                               Recv Handle
 ****************************************************************************/
static void usb_cam_task(void *param)
{
    while (1) {
        bl_usb_cam_transfer();
        vTaskDelay(5);
    }

    vTaskDelete(NULL);
}

static int usb_cam_init()
{
    if (0 != bl_usb_cam_init()) {
        printf("usb cam init failed!\r\n");
        return -1;
    }

    if (pdTRUE != xTaskCreate(usb_cam_task, "usb task", 256, NULL, 20, NULL)) {
        return -1;
    }

    return 0;
}

static int xram_usb_cam_init(m1s_xram_usb_t *op)
{
    struct xram_hdr hdr;
    uint32_t bytes;
    enum usb_op_err err = USB_OP_OK;

    /* usb init */
    if (0 != usb_cam_init()) {
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

/*************************************** MSC Class **************************************************/
#define USBD_VID 0xffff
#define USBD_PID 0xffff
#define USBD_LANGID_STRING 1033
#define USB_MSC_DESC_SIZ (unsigned long)(9 + 9 + 7 + 7)
#define USBD_OUT_EP (0x01)
#define USBD_IN_EP (0x81)
const uint8_t usbd_descriptor[] = {
    USB_DEVICE_DESCRIPTOR_INIT(USB_2_0, 0x00, 0x00, 0x00, USBD_VID, USBD_PID, 0x0001, 0x01), 
    USB_CONFIG_DESCRIPTOR_INIT(USB_MSC_DESC_SIZ, 0x02, 0x01, USB_CONFIG_BUS_POWERED, 100),
    MSC_DESCRIPTOR_INIT(1, USBD_OUT_EP, USBD_IN_EP, 0),
    ///////////////////////////////////////
    /// string0 descriptor
    ///////////////////////////////////////
    USB_LANGID_INIT(USBD_LANGID_STRING),
    ///////////////////////////////////////
    /// string1 descriptor
    ///////////////////////////////////////
    0x0E,                       /* bLength */
    USB_DESCRIPTOR_TYPE_STRING, /* bDescriptorType */
    'S', 0x00,                  /* wcChar0 */
    'i', 0x00,                  /* wcChar1 */
    'p', 0x00,                  /* wcChar2 */
    'e', 0x00,                  /* wcChar3 */
    'e', 0x00,                  /* wcChar4 */
    'd', 0x00,                  /* wcChar5 */
    ///////////////////////////////////////
    /// string2 descriptor
    ///////////////////////////////////////
    0x1A,                       /* bLength */
    USB_DESCRIPTOR_TYPE_STRING, /* bDescriptorType */
    'M', 0x00,                  /* wcChar0 */
    'a', 0x00,                  /* wcChar1 */
    's', 0x00,                  /* wcChar2 */
    's', 0x00,                  /* wcChar3 */
    ' ', 0x00,                  /* wcChar4 */
    'S', 0x00,                  /* wcChar5 */
    't', 0x00,                  /* wcChar6 */
    'o', 0x00,                  /* wcChar7 */
    'r', 0x00,                  /* wcChar8 */
    'a', 0x00,                  /* wcChar9 */
    'g', 0x00,                  /* wcChar10 */
    'e', 0x00,                  /* wcChar11 */
    ///////////////////////////////////////
    /// string3 descriptor
    ///////////////////////////////////////
    0x12,                       /* bLength */
    USB_DESCRIPTOR_TYPE_STRING, /* bDescriptorType */
    '2', 0x00,                  /* wcChar0 */
    '0', 0x00,                  /* wcChar1 */
    '2', 0x00,                  /* wcChar2 */
    '2', 0x00,                  /* wcChar3 */
    '1', 0x00,                  /* wcChar4 */
    '0', 0x00,                  /* wcChar5 */
    '1', 0x00,                  /* wcChar6 */
    '4', 0x00,                  /* wcChar7 */
};
/**********************************************************************************************/
void usbd_msc_get_cap(uint8_t lun, uint32_t *block_num, uint16_t *block_size)
{
    *block_num = 0;
    *block_size = 0;

    hal_sd_info_t info;
    if (hal_sd_info_get(&private.sd, &info) == 0) {
        *block_num = info.blk_nums;
        *block_size = info.blk_size;
    }
}

int usbd_msc_sector_read(uint32_t sector, uint8_t *buffer, uint32_t length)
{
    if (hal_sd_blks_read(&private.sd, buffer, sector, length / 512, -1) != 0) {
        return -1;
    }
    return 0;
}

int usbd_msc_sector_write(uint32_t sector, uint8_t *buffer, uint32_t length)
{
    if (hal_sd_blks_write(&private.sd, buffer, sector, length / 512, -1) != 0) {
        return -1;
    }
    return 0;
}

static void usb_clock_init(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_CGEN_CFG1);
    tmpVal |= (1 << 13);
    BL_WR_REG(GLB_BASE, GLB_CGEN_CFG1, tmpVal);
    GLB_Set_USB_CLK_From_WIFIPLL(1);
}

static int usb_msc_init()
{
    memset(&private.sd, 0, sizeof(sd_dev_t));
    if (0 != hal_sd_init(&private.sd)) return -1;
    usb_clock_init();
    usbd_desc_register(usbd_descriptor);
    usbd_msc_class_init(USBD_OUT_EP, USBD_IN_EP);
    if (0 != usbd_initialize()) return -1;
    return 0;
}

static int xram_usb_msc_init(m1s_xram_usb_t *op)
{
    struct xram_hdr hdr;
    uint32_t bytes;
    enum usb_op_err err = USB_OP_OK;

    /* usb init */
    if (0 != usb_msc_init()) {
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
            case XRAM_UVC_INIT: {
                xram_usb_cam_init(&obj_op);
                break;
            }
            case XRAM_MSC_INIT: {
                xram_usb_msc_init(&obj_op);
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
