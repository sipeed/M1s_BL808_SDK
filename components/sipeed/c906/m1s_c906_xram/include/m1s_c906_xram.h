#ifndef _XRAM_PERIPHERAL_H_
#define _XRAM_PERIPHERAL_H_

#include "xram.h"

int m1s_c906_xram_mutex_init(void);
int m1s_c906_xram_mutex_destory(void);
int m1s_c906_xram_mutex_lock();
int m1s_c906_xram_mutex_unlock();
struct xram_hdr *m1s_c906_xram_plunder_rx_hdr();
void m1s_c906_xram_operation_handle();
void m1s_c906_xram_init(void);
#endif
