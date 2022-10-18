#ifndef __M1S_C906_XRAM_WIFI_H
#define __M1S_C906_XRAM_WIFI_H

#include "m1s_c906_xram.h"
#include "m1s_common_xram.h"
#include "m1s_common_xram_wifi.h"

int m1s_xram_wifi_init(void);
int m1s_xram_wifi_deinit(void);
int m1s_xram_wifi_connect(char *ssid, char *passwd);
int m1s_xram_wifi_disconnect(void);
int m1s_xram_wifi_upload_stream(char *ip, uint32_t port);
void m1s_c906_xram_wifi_operation_handle(uint32_t len);
#endif
