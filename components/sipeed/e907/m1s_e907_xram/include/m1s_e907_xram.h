#ifndef __M1S_E907_XRAM_H
#define __M1S_E907_XRAM_H

int m1s_e907_xram_mutex_init(void);
int m1s_e907_xram_mutex_destory(void);
int m1s_e907_xram_mutex_lock();
int m1s_e907_xram_mutex_unlock();
struct xram_hdr *m1s_e907_xram_plunder_rx_hdr(void);
void m1s_e907_xram_operation_handle();
void m1s_e907_xram_init(void);
#endif
