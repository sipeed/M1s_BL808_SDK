#ifndef __M1S_C906_XRAM_PWM_H
#define __M1S_C906_XRAM_PWM_H

#include "m1s_c906_xram.h"
#include "m1s_common_xram.h"
#include "m1s_common_xram_pwm.h"

int m1s_xram_pwm_init(int port, int pin, int freq, int duty);
int m1s_xram_pwm_deinit(int port);
int m1s_xram_pwm_start(int port, int pin);
int m1s_xram_pwm_stop(int port, int pin);
int m1s_xram_pwm_set_duty(int port, int pin, int freq, int duty);
void m1s_c906_xram_pwm_operation_handle(uint32_t len);
#endif
