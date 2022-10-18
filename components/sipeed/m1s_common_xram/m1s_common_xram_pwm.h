#ifndef __M1S_COMMON_XRAM_PWM_H
#define __M1S_COMMON_XRAM_PWM_H

#include <stdint.h>

typedef enum pwm_op_err {
    PWM_OP_OK,
    PWM_OP_ERR,
} PWM_OP_ERR_TYPE;

enum pwm_operation {
    XRAM_PWM_INIT,
    XRAM_PWM_DEINIT,
    XRAM_PWM_START,
    XRAM_PWM_STOP,
    XRAM_PWM_SET_DUTY,
};

struct m1s_xram_pwm {
    uint32_t op;
    uint32_t pin;
    uint32_t freq;
    uint8_t port;
    uint8_t duty;
} __attribute__((packed));
typedef struct m1s_xram_pwm m1s_xram_pwm_t;

#endif
