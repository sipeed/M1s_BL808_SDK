/**
 * xram_peri_pwm.c
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
#include <bl_flash.h>
#include <xram_peripheral.h>
#include <xram_peri_pwm.h>
#include <xram_peri_common.h>
#include <xram_pwm_common.h>
#include <bl808_common.h>
#include <xram.h>
#include "hosal_pwm.h"

static int xram_pwm_int(struct xram_pwm_op *op)
{
    struct xram_hdr hdr;
    uint32_t bytes;
    uint8_t operation_ret = PWM_OP_OK;

    hosal_pwm_dev_t pwm;
    pwm.port = op->port;
    pwm.config.pin = op->pin;
    pwm.config.duty_cycle = op->duty_cycle;
    pwm.config.freq = op->freq;
    if (hosal_pwm_init(&pwm) != 0)
        operation_ret = PWM_OP_ERR;

    hdr.type = XRAM_PERI_TYPE_PWM;
    hdr.err = operation_ret;
    hdr.len = 0;
    bytes = XRAMRingWrite(XRAM_PERI_OP_QUEUE, &hdr, sizeof(struct xram_hdr));
    if (bytes == sizeof(struct xram_hdr)) {
        return PWM_OP_OK;
    } else {
        printf("xram ring write err.\r\n");
        return PWM_OP_ERR;
    }
}

static int xram_pwm_finalize(struct xram_pwm_op *op)
{
    struct xram_hdr hdr;
    uint32_t bytes;
    uint8_t operation_ret = PWM_OP_OK;

    hosal_pwm_dev_t pwm;
    pwm.port = op->port;
    pwm.config.pin = op->pin;
    pwm.config.duty_cycle = op->duty_cycle;
    pwm.config.freq = op->freq;
    if (hosal_pwm_finalize(&pwm) != 0)
        operation_ret = PWM_OP_ERR;

    hdr.type = XRAM_PERI_TYPE_PWM;
    hdr.err = operation_ret;
    hdr.len = 0;
    bytes = XRAMRingWrite(XRAM_PERI_OP_QUEUE, &hdr, sizeof(struct xram_hdr));
    if (bytes == sizeof(struct xram_hdr)) {
        return PWM_OP_OK;
    } else {
        printf("xram ring write err.\r\n");
        return PWM_OP_ERR;
    }
}

static int xram_pwm_start(struct xram_pwm_op *op)
{
    struct xram_hdr hdr;
    uint32_t bytes;
    uint8_t operation_ret = PWM_OP_OK;

    hosal_pwm_dev_t pwm;
    pwm.port = op->port;
    pwm.config.pin = op->pin;
    pwm.config.duty_cycle = op->duty_cycle;
    pwm.config.freq = op->freq;
    if (hosal_pwm_start(&pwm) != 0)
        operation_ret = PWM_OP_ERR;

    hdr.type = XRAM_PERI_TYPE_PWM;
    hdr.err = operation_ret;
    hdr.len = 0;
    bytes = XRAMRingWrite(XRAM_PERI_OP_QUEUE, &hdr, sizeof(struct xram_hdr));
    if (bytes == sizeof(struct xram_hdr)) {
        return PWM_OP_OK;
    } else {
        printf("xram ring write err.\r\n");
        return PWM_OP_ERR;
    }
}

static int xram_pwm_stop(struct xram_pwm_op *op)
{
    struct xram_hdr hdr;
    uint32_t bytes;
    uint8_t operation_ret = PWM_OP_OK;

    hosal_pwm_dev_t pwm;
    pwm.port = op->port;
    pwm.config.pin = op->pin;
    pwm.config.duty_cycle = op->duty_cycle;
    pwm.config.freq = op->freq;
    if (hosal_pwm_stop(&pwm) != 0)
        operation_ret = PWM_OP_ERR;

    hdr.type = XRAM_PERI_TYPE_PWM;
    hdr.err = operation_ret;
    hdr.len = 0;
    bytes = XRAMRingWrite(XRAM_PERI_OP_QUEUE, &hdr, sizeof(struct xram_hdr));
    if (bytes == sizeof(struct xram_hdr)) {
        return PWM_OP_OK;
    } else {
        printf("xram ring write err.\r\n");
        return PWM_OP_ERR;
    }
}

static int xram_pwm_set_duty(struct xram_pwm_op *op)
{
    struct xram_hdr hdr;
    uint32_t bytes;
    uint8_t operation_ret = PWM_OP_OK;

    hosal_pwm_dev_t pwm;
    pwm.port = op->port;
    pwm.config.pin = op->pin;
    pwm.config.duty_cycle = op->duty_cycle;
    pwm.config.freq = op->freq;
    if (hosal_pwm_duty_set(&pwm, op->duty_cycle) != 0)
        operation_ret = PWM_OP_ERR;

    hdr.type = XRAM_PERI_TYPE_PWM;
    hdr.err = operation_ret;
    hdr.len = 0;
    bytes = XRAMRingWrite(XRAM_PERI_OP_QUEUE, &hdr, sizeof(struct xram_hdr));
    if (bytes == sizeof(struct xram_hdr)) {
        return PWM_OP_OK;
    } else {
        printf("xram ring write err.\r\n");
        return PWM_OP_ERR;
    }
}

void xram_pwm_operation_handle(uint32_t len)
{
    struct xram_pwm_op pwm_op;
    uint32_t bytes;

    bytes = XRAMRingRead(XRAM_PERI_OP_QUEUE, &pwm_op, len);
    if (bytes == sizeof(struct xram_pwm_op)) {
        switch (pwm_op.op){
            case XRAM_PWM_INIT: {
                xram_pwm_int(&pwm_op);
                break;
               }
            case XRAM_PWM_FINALIZE: {
                xram_pwm_finalize(&pwm_op);
                break;
            }
            case XRAM_PWM_START: {
                xram_pwm_start(&pwm_op);
                break;
            }
            case XRAM_PWM_STOP: {
                xram_pwm_stop(&pwm_op);
                break;
            }
            case XRAM_PWM_SET_DUTY: {
                xram_pwm_set_duty(&pwm_op);
                break;
            }
            default: {
                printf("xram pwm operate type err.\r\n");
                break;
            }
        }
    }
}

