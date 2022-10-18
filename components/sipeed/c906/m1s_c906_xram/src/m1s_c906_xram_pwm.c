#include "m1s_c906_xram_pwm.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/****************************************************************************
 *                                Send Handle
 ****************************************************************************/
static int m1s_xram_pwm_operation(m1s_xram_pwm_t *obj, enum pwm_operation operation)
{
    struct xram_hdr tx_hdr;
    uint32_t bytes;
    int ret = -1;

    assert(obj != NULL);

    if (m1s_c906_xram_mutex_lock()) {
        return -1;
    }

    tx_hdr.type = M1S_XRAM_TYPE_PWM;
    tx_hdr.err = PWM_OP_OK;
    tx_hdr.len = sizeof(m1s_xram_pwm_t);
    obj->op = operation;

    bytes = XRAMRingWrite(XRAM_OP_QUEUE, &tx_hdr, sizeof(struct xram_hdr));
    bytes += XRAMRingWrite(XRAM_OP_QUEUE, obj, sizeof(m1s_xram_pwm_t));
    if (bytes != sizeof(struct xram_hdr) + sizeof(m1s_xram_pwm_t)) {
        printf("xram write operate err.\r\n");
    } else {
        struct xram_hdr *hdr = m1s_c906_xram_plunder_rx_hdr();
        if (hdr && hdr->type == M1S_XRAM_TYPE_PWM && hdr->err == PWM_OP_OK && hdr->len == 0) {
            ret = 0;
        } else {
            printf("xram plunder rx hdr err.\r\n");
        }
    }

    m1s_c906_xram_mutex_unlock();
    return ret;
}

int m1s_xram_pwm_init(int port, int pin, int freq, int duty)
{
    m1s_xram_pwm_t op = {0};
    op.port = port;
    op.pin = pin;
    op.freq = freq;
    op.duty = duty;
    return m1s_xram_pwm_operation(&op, XRAM_PWM_INIT);
}

int m1s_xram_pwm_deinit(int port)
{
    m1s_xram_pwm_t op = {0};
    op.port = port;
    return m1s_xram_pwm_operation(&op, XRAM_PWM_DEINIT);
}

int m1s_xram_pwm_start(int port, int pin)
{
    m1s_xram_pwm_t op = {0};
    op.port = port;
    op.pin = pin;
    return m1s_xram_pwm_operation(&op, XRAM_PWM_START);
}

int m1s_xram_pwm_stop(int port, int pin)
{
    m1s_xram_pwm_t op = {0};
    op.port = port;
    op.pin = pin;
    return m1s_xram_pwm_operation(&op, XRAM_PWM_STOP);
}

int m1s_xram_pwm_set_duty(int port, int pin, int freq, int duty)
{
    m1s_xram_pwm_t op = {0};
    op.port = port;
    op.pin = pin;
    op.freq = freq;
    op.duty = duty;
    return m1s_xram_pwm_operation(&op, XRAM_PWM_SET_DUTY);
}
