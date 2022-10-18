#ifndef __M1S_C906_XRAM_AUDIO_H
#define __M1S_C906_XRAM_AUDIO_H

#include "m1s_c906_xram.h"
#include "m1s_common_xram.h"
#include "m1s_common_xram_audio.h"

int m1s_xram_audio_init(uint16_t *buff, int buf_size);
int m1s_xram_audio_deinit(void);
int m1s_xram_audio_get(uint16_t **buf, uint32_t *buf_size);
int m1s_xram_audio_pop(void);
void m1s_c906_xram_audio_operation_handle(uint32_t len);
#endif
