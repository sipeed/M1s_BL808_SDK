/**
 * xram_pipe_pwm.c
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

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <ring.h>
#include <xram_platform.h>
#include <xram_peripheral.h>
#include <xram_pipe_pwm.h>
#include <xram_peri_common.h>

static int xram_pipe_pwm_operation(xram_pipe_pwm_t obj, enum pwm_operation operation)
{
    struct xram_hdr tx_hdr;
    struct xram_pwm_op flash_op;
    uint32_t bytes;
    int ret = -1;

    assert(obj != NULL);

    if (xram_peri_mutex_lock()) {
        return -1;
    }

    tx_hdr.type = XRAM_PERI_TYPE_PWM;
    tx_hdr.err = PWM_OP_OK;
    tx_hdr.len = sizeof(struct xram_pwm_op);
    flash_op.op = operation;
    memcpy((void *)&flash_op.port, obj, sizeof(struct xram_pipe_pwm));

    bytes = XRAMRingWrite(XRAM_PERI_OP_QUEUE, &tx_hdr, sizeof(struct xram_hdr));
    bytes += XRAMRingWrite(XRAM_PERI_OP_QUEUE, &flash_op, sizeof(struct xram_pwm_op));
    if (bytes != sizeof(struct xram_hdr)+sizeof(struct xram_pwm_op)) {
        printf("xram write operate err.\r\n");
    } else {
        bytes = XRAMRingRead(XRAM_PERI_OP_QUEUE, &tx_hdr, sizeof(struct xram_hdr));
        assert(bytes == sizeof(struct xram_hdr));

        if (tx_hdr.type == XRAM_PERI_TYPE_PWM && tx_hdr.err == PWM_OP_OK && tx_hdr.len == 0) {
            ret = 0;
        }
    }

    xram_peri_mutex_unlock();
    return ret;
}

/**
 * @brief init a PWM pin
 *
 * @param[in]  obj  the PWM device
 *
 * @return  
 *     -  0 : success
 *     - other: fail
 */
int xram_pipe_pwm_init(xram_pipe_pwm_t obj)
{
    return xram_pipe_pwm_operation(obj, XRAM_PWM_INIT);
}

/**
 * @brief finalize PWM
 *
 * @param[in]  obj  the PWM device
 *
 * @return  
 *     -  0 : success
 *     - other: fail
 */
int xram_pipe_pwm_finalize(xram_pipe_pwm_t obj)
{
    return xram_pipe_pwm_operation(obj, XRAM_PWM_FINALIZE);
}

/**
 * @brief start PWM
 *
 * @param[in]  obj  the PWM device
 *
 * @return  
 *     -  0 : success
 *     - other: fail
 */
int xram_pipe_pwm_start(xram_pipe_pwm_t obj)
{
    return xram_pipe_pwm_operation(obj, XRAM_PWM_START);
}

/**
 * @brief stop PWM
 *
 * @param[in]  obj  the PWM device
 *
 * @return  
 *     -  0 : success
 *     - other: fail
 */
int xram_pipe_pwm_stop(xram_pipe_pwm_t obj)
{
    return xram_pipe_pwm_operation(obj, XRAM_PWM_STOP);
}

/**
 * @brief set PWM duty
 *
 * @param[in]  obj   the PWM device
 * @param[in]  duty        the PWM duty
 *
 * @return  
 *     -  0 : success
 *     - other: fail
 */
int xram_pipe_pwm_set_duty(xram_pipe_pwm_t obj)
{
    return xram_pipe_pwm_operation(obj, XRAM_PWM_SET_DUTY);
}

