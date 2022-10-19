#ifndef __M1S_C906_XRAM_USB_H
#define __M1S_C906_XRAM_USB_H

#include "m1s_c906_xram.h"
#include "m1s_common_xram.h"
#include "m1s_common_xram_usb.h"

int m1s_xram_usb_cam_init(void);
int m1s_xram_usb_msc_init(void);
int m1s_xram_usb_deinit(void);
void m1s_c906_xram_usb_operation_handle(uint32_t len);
#endif
