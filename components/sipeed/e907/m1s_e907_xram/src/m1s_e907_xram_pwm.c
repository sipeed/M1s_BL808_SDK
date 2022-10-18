#include "m1s_e907_xram_pwm.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "FreeRTOS.h"
#include "bl808_glb.h"
#include "hosal_pwm.h"
#include "queue.h"

/****************************************************************************
 *                               Recv Handle
 ****************************************************************************/
static int pwm_init(uint32_t port, uint32_t pin, uint32_t freq, uint32_t duty)
{
    if (freq > 40 * 1000 * 1000) return -1;
    duty = duty > 100 ? 100 : duty;

    hosal_pwm_dev_t pwm;
    pwm.port = port;
    pwm.config.pin = pin;
    pwm.config.duty_cycle = duty * 10000 / 100;
    pwm.config.freq = freq;
    if (hosal_pwm_init(&pwm) != 0) {
        return -1;
    }
    return 0;
}

static int xram_pwm_init(m1s_xram_pwm_t *op)
{
    struct xram_hdr hdr;
    uint32_t bytes;
    enum pwm_op_err err = PWM_OP_OK;

    /* pwm init */
    if (0 != pwm_init(op->port, op->pin, op->freq, op->duty)) {
        err = PWM_OP_ERR;
    }

    /* xram response */
    hdr.type = M1S_XRAM_TYPE_PWM;
    hdr.err = err;
    hdr.len = 0;
    bytes = XRAMRingWrite(XRAM_OP_QUEUE, &hdr, sizeof(struct xram_hdr));
    if (bytes == sizeof(struct xram_hdr)) {
        return PWM_OP_OK;
    } else {
        printf("xram ring write err.\r\n");
        return PWM_OP_ERR;
    }
}

static int pwm_deinit(uint32_t port)
{
    hosal_pwm_dev_t pwm;
    pwm.port = port;
    if (hosal_pwm_finalize(&pwm) != 0) {
        return -1;
    }
    return 0;
}

static int xram_pwm_deinit(m1s_xram_pwm_t *op)
{
    struct xram_hdr hdr;
    uint32_t bytes;
    enum pwm_op_err err = PWM_OP_OK;

    /* pwm deinit */
    if (0 != pwm_deinit(op->port)) {
        err = PWM_OP_ERR;
    }

    /* xram response */
    hdr.type = M1S_XRAM_TYPE_PWM;
    hdr.err = err;
    hdr.len = 0;
    bytes = XRAMRingWrite(XRAM_OP_QUEUE, &hdr, sizeof(struct xram_hdr));
    if (bytes == sizeof(struct xram_hdr)) {
        return PWM_OP_OK;
    } else {
        printf("xram ring write err.\r\n");
        return PWM_OP_ERR;
    }
}

static int pwm_start(uint32_t port, uint32_t pin)
{
    hosal_pwm_dev_t pwm;
    pwm.port = port;
    pwm.config.pin = pin;

    if (hosal_pwm_start(&pwm) != 0) {
        return -1;
    }

    return 0;
}

static int xram_pwm_start(m1s_xram_pwm_t *op)
{
    struct xram_hdr hdr;
    uint32_t bytes;
    enum pwm_op_err err = PWM_OP_OK;

    /* pwm deinit */
    if (0 != pwm_start(op->port, op->pin)) {
        err = PWM_OP_ERR;
    }

    /* xram response */
    hdr.type = M1S_XRAM_TYPE_PWM;
    hdr.err = err;
    hdr.len = 0;
    bytes = XRAMRingWrite(XRAM_OP_QUEUE, &hdr, sizeof(struct xram_hdr));
    if (bytes == sizeof(struct xram_hdr)) {
        return PWM_OP_OK;
    } else {
        printf("xram ring write err.\r\n");
        return PWM_OP_ERR;
    }
}

static int pwm_stop(uint32_t port, uint32_t pin)
{
    hosal_pwm_dev_t pwm;
    pwm.port = port;
    pwm.config.pin = pin;

    if (hosal_pwm_stop(&pwm) != 0) {
        return -1;
    }

    return 0;
}

static int xram_pwm_stop(m1s_xram_pwm_t *op)
{
    struct xram_hdr hdr;
    uint32_t bytes;
    enum pwm_op_err err = PWM_OP_OK;

    /* pwm deinit */
    if (0 != pwm_stop(op->port, op->pin)) {
        err = PWM_OP_ERR;
    }

    /* xram response */
    hdr.type = M1S_XRAM_TYPE_PWM;
    hdr.err = err;
    hdr.len = 0;
    bytes = XRAMRingWrite(XRAM_OP_QUEUE, &hdr, sizeof(struct xram_hdr));
    if (bytes == sizeof(struct xram_hdr)) {
        return PWM_OP_OK;
    } else {
        printf("xram ring write err.\r\n");
        return PWM_OP_ERR;
    }
}

static int pwm_set_duty(uint32_t port, uint32_t pin, uint32_t freq, uint32_t duty)
{
    if (freq > 40 * 1000 * 1000) return -1;
    duty = duty > 100 ? 100 : duty;
    duty = duty * 100;

    hosal_pwm_dev_t pwm;
    pwm.port = port;
    pwm.config.pin = pin;
    pwm.config.freq = freq;
    if (hosal_pwm_duty_set(&pwm, duty) != 0) {
        return -1;
    }

    return 0;
}

static int xram_pwm_set_duty(m1s_xram_pwm_t *op)
{
    struct xram_hdr hdr;
    uint32_t bytes;
    enum pwm_op_err err = PWM_OP_OK;

    /* pwm deinit */
    if (0 != pwm_set_duty(op->port, op->pin, op->freq, op->duty)) {
        err = PWM_OP_ERR;
    }

    /* xram response */
    hdr.type = M1S_XRAM_TYPE_PWM;
    hdr.err = err;
    hdr.len = 0;
    bytes = XRAMRingWrite(XRAM_OP_QUEUE, &hdr, sizeof(struct xram_hdr));
    if (bytes == sizeof(struct xram_hdr)) {
        return PWM_OP_OK;
    } else {
        printf("xram ring write err.\r\n");
        return PWM_OP_ERR;
    }
}

void m1s_e907_xram_pwm_operation_handle(uint32_t len)
{
    m1s_xram_pwm_t obj_op;
    uint32_t bytes;

    bytes = XRAMRingRead(XRAM_OP_QUEUE, &obj_op, len);
    if (bytes == sizeof(m1s_xram_pwm_t)) {
        switch (obj_op.op) {
            case XRAM_PWM_INIT: {
                xram_pwm_init(&obj_op);
                break;
            }
            case XRAM_PWM_DEINIT: {
                xram_pwm_deinit(&obj_op);
                break;
            }
            case XRAM_PWM_START: {
                xram_pwm_start(&obj_op);
                break;
            }
            case XRAM_PWM_STOP: {
                xram_pwm_stop(&obj_op);
                break;
            }
            case XRAM_PWM_SET_DUTY: {
                xram_pwm_set_duty(&obj_op);
                break;
            }
            default: {
                printf("xram pwm operate type err.\r\n");
                break;
            }
        }
    }
}
