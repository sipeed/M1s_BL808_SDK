/**
 * xram_pipe_pwm.h
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

#ifndef _XRAM_PIPE_PWM_H_
#define _XRAM_PIPE_PWM_H_

/* xram pipe pwm object
 **/
struct xram_pipe_pwm {
    uint8_t port;
    uint8_t pin;        /**< pwm pin  */
    uint16_t duty_cycle; /**< the pwm duty_cycle 0 ~ 10000(0 ~ 100%)*/
    uint32_t freq;       /**< the pwm freq,range is between 1000 and 1M */
};
typedef struct xram_pipe_pwm *xram_pipe_pwm_t;

/**
 * @brief init a PWM pin
 *
 * @param[in]  obj  the PWM device
 *
 * @return  
 *     -  0 : success
 *     - other: fail
 */
int xram_pipe_pwm_init(xram_pipe_pwm_t obj);

/**
 * @brief finalize PWM
 *
 * @param[in]  obj  the PWM device
 *
 * @return  
 *     -  0 : success
 *     - other: fail
 */
int xram_pipe_pwm_finalize(xram_pipe_pwm_t obj);

/**
 * @brief start PWM
 *
 * @param[in]  obj  the PWM device
 *
 * @return  
 *     -  0 : success
 *     - other: fail
 */
int xram_pipe_pwm_start(xram_pipe_pwm_t obj);

/**
 * @brief stop PWM
 *
 * @param[in]  obj  the PWM device
 *
 * @return  
 *     -  0 : success
 *     - other: fail
 */
int xram_pipe_pwm_stop(xram_pipe_pwm_t obj);

/**
 * @brief set PWM duty
 *
 * @param[in]  obj   the PWM device
 *
 * @return  
 *     -  0 : success
 *     - other: fail
 */
int xram_pipe_pwm_set_duty(xram_pipe_pwm_t obj);

#endif
