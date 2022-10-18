/**
 * xram_pwm_common.h
 * Copyright (c) 2022 bliu <bliu@bouffalolab.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _XRAM_PWM_COMMON_H_
#define _XRAM_PWM_COMMON_H_

typedef enum pwm_op_err {
    PWM_OP_OK,
    PWM_OP_ERR
} PWM_OP_ERR_TYPE;

enum pwm_operation {
    XRAM_PWM_INIT,
    XRAM_PWM_FINALIZE,
    XRAM_PWM_START,
    XRAM_PWM_STOP,
    XRAM_PWM_SET_DUTY
};

struct xram_pwm_op {
    uint32_t op;
    uint8_t port;       /**< pwm port  */
    uint8_t pin;        /**< pwm pin  */
    uint16_t duty_cycle; /**< the pwm duty_cycle 0 ~ 10000(0 ~ 100%)*/
    uint32_t freq;       /**< the pwm freq,range is between 0 and 40M */
};

#endif
