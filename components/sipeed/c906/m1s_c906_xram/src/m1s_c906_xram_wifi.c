#include "m1s_c906_xram_wifi.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/****************************************************************************
 *                                Send Handle
 ****************************************************************************/
static int m1s_xram_wifi_operation(m1s_xram_wifi_t *obj, enum wifi_operation operation)
{
    struct xram_hdr tx_hdr;
    uint32_t bytes;
    int ret = -1;

    assert(obj != NULL);

    if (m1s_c906_xram_mutex_lock()) {
        return -1;
    }

    tx_hdr.type = M1S_XRAM_TYPE_WIFI;
    tx_hdr.err = WIFI_OP_OK;
    tx_hdr.len = sizeof(m1s_xram_wifi_t);
    obj->op = operation;

    bytes = XRAMRingWrite(XRAM_OP_QUEUE, &tx_hdr, sizeof(struct xram_hdr));
    bytes += XRAMRingWrite(XRAM_OP_QUEUE, obj, sizeof(m1s_xram_wifi_t));
    if (bytes != sizeof(struct xram_hdr) + sizeof(m1s_xram_wifi_t)) {
        printf("xram write operate err.\r\n");
    } else {
        struct xram_hdr *hdr = m1s_c906_xram_plunder_rx_hdr();
        if (hdr && hdr->type == M1S_XRAM_TYPE_WIFI && hdr->err == WIFI_OP_OK && hdr->len == 0) {
            ret = 0;
        } else {
            printf("xram plunder rx hdr err.\r\n");
        }
    }

    m1s_c906_xram_mutex_unlock();
    return ret;
}

int m1s_xram_wifi_init(void)
{
    m1s_xram_wifi_t op = {0};
    return m1s_xram_wifi_operation(&op, XRAM_WIFI_INIT);
}

int m1s_xram_wifi_deinit(void)
{
    m1s_xram_wifi_t op = {0};
    return m1s_xram_wifi_operation(&op, XRAM_WIFI_DEINIT);
}

int m1s_xram_wifi_connect(char *ssid, char *passwd)
{
    m1s_xram_wifi_t op = {0};
    strncpy(op.connect.ssid, ssid, sizeof(op.connect.ssid));
    strncpy(op.connect.passwd, passwd, sizeof(op.connect.passwd));
    return m1s_xram_wifi_operation(&op, XRAM_WIFI_CONNECT);
}

int m1s_xram_wifi_disconnect(void)
{
    m1s_xram_wifi_t op = {0};
    return m1s_xram_wifi_operation(&op, XRAM_WIFI_DISCONNECT);
}

int m1s_xram_wifi_upload_stream(char *ip, uint32_t port)
{
    m1s_xram_wifi_t op = {0};
    strncpy(op.upload_stream.ip, ip, sizeof(op.upload_stream.ip));
    op.upload_stream.port = port;
    return m1s_xram_wifi_operation(&op, XRAM_WIFI_UPLOAD_STREAM);
}
/****************************************************************************
 *                               Recv Handle
 ****************************************************************************/
void m1s_c906_xram_wifi_operation_handle(uint32_t len)
{
    m1s_xram_wifi_t obj_op;
    uint32_t bytes;

    bytes = XRAMRingRead(XRAM_OP_QUEUE, &obj_op, len);
    if (bytes == sizeof(m1s_xram_wifi_t)) {
        switch (obj_op.op) {
            default: {
                printf("xram wifi operate type err.\r\n");
                break;
            }
        }
    }
}