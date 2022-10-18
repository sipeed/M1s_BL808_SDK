#ifndef __M1S_COMMON_XRAM_WIFI_H
#define __M1S_COMMON_XRAM_WIFI_H

#include <stdint.h>

typedef enum wifi_op_err {
    WIFI_OP_OK,
    WIFI_OP_ERR,
} WIFI_OP_ERR_TYPE;

enum wifi_operation {
    XRAM_WIFI_INIT,
    XRAM_WIFI_DEINIT,
    XRAM_WIFI_CONNECT,
    XRAM_WIFI_DISCONNECT,
    XRAM_WIFI_UPLOAD_STREAM,
};

struct m1s_xram_wifi {
    uint32_t op;
    union {
        struct {
            char ssid[32];
            char passwd[63];
        } __attribute__((packed)) connect;

        struct {
            uint32_t port;
            char ip[16];
        } __attribute__((packed)) upload_stream;
    };
} __attribute__((packed));
typedef struct m1s_xram_wifi m1s_xram_wifi_t;

#endif
