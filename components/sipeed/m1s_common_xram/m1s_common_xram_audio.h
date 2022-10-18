#ifndef __M1S_COMMON_XRAM_AUDIO_H
#define __M1S_COMMON_XRAM_AUDIO_H

#include <stdint.h>

typedef enum audio_op_err {
    AUDIO_OP_OK,
    AUDIO_OP_ERR,
} AUDIO_OP_ERR_TYPE;

enum audio_operation {
    XRAM_AUDIO_INIT,
    XRAM_AUDIO_DEINIT,
    XRAM_AUDIO_GET,
    XRAM_AUDIO_POP,
};

typedef enum audio_sample_rate {
    AUDIO_SAMPLERATE_16K = 0,
} AUDIO_SAMPLE_RATE_TYPE;

typedef enum {
    AUDIO_CODE_SIGNED_16LB_PCM = 0,
} AUDIO_SAMPLE_CODE_TYPE;

struct m1s_xram_audio {
    uint32_t op;
    union {
        struct {
            uint8_t sample_rate;
            uint8_t coding;
            uint32_t buff0;
            uint32_t buff1;
            uint32_t buff_size;
        } __attribute__((packed)) init;

        struct {
            uint32_t buff;
            uint32_t buff_size;
        } __attribute__((packed)) get;
    };
} __attribute__((packed));
typedef struct m1s_xram_audio m1s_xram_audio_t;

#endif
