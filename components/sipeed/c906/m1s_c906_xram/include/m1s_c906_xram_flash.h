#ifndef __M1S_C906_XRAM_FLASH_H
#define __M1S_C906_XRAM_FLASH_H

#include "m1s_c906_xram.h"
#include "m1s_common_xram.h"
#include "m1s_common_xram_flash.h"

int m1s_xram_flash_read(uint32_t offset, uint32_t addr, uint32_t len);
int m1s_xram_flash_write(uint32_t offset, uint32_t addr, uint32_t len);
int m1s_xram_flash_erase(uint32_t offset, uint32_t len);
void m1s_c906_xram_flash_operation_handle(uint32_t len);
#endif
