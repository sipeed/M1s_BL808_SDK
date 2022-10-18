#ifndef __BOOT_CPU0_H__
#define __BOOT_CPU0_H__

#include <stdint.h>

int boot_cpu0_cli_init(void);
void c906_bringup(uint32_t start_addr);
#endif
