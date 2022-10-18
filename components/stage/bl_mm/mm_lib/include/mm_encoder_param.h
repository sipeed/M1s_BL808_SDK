#ifndef __MM_ENCODER_PARAM_H__
#define __MM_ENCODER_PARAM_H__

#include <string.h>
#include "mm_encoder.h"

static MMEncoderRcAttr rcAttr_init_reg = {
    .rcMode = ENC_RC_MODE_CBR,
    .attrH264Cbr = {
        .outBitRate = 2250000,
        .initQp = 0, //0: decision by algo
        .minQp = 15,
        .maxQp = 51,
        .iBiasLvl = 8, //0: decision by algo
    },
    .attrH264Vbr = {
        .targetBitRate = 2250000,
        .maxBitRate = 2500000,
        .qualityLvl = 35,
        .minQp = 15,
        .maxQp = 51,
        .iBiasLvl = 8, //0: decision by algo
    },
};

static MMEncoderBitRateCtrlAttr bitrate_ctrl_init_reg = {
    .enable = 1,
    .bitrate_ctrl = {
        {//512k
        //thr, gop_size, ip_ratio, min_qp, max_qp
            {
            {  80,  45,  50, 26, 46},//static
            {  30,  15,  40, 26, 44},//moving
            {  80,  15,  30, 26, 42},//big moving
            },
        },
        {//1M
        //thr, gop_size, ip_ratio, min_qp, max_qp
            {
            {  80,  45,  40, 26, 46},//static
            {  30,  15,  30, 26, 44},//moving
            {  80,  15,  30, 26, 42},//big moving
            },
        },
        {//2M
        //thr, gop_size, ip_ratio, min_qp, max_qp
            {
            {  80,  75,  30, 20, 46},//static
            {  30,  25,  20, 23, 43},//moving
            {  80,  25,  20, 25, 40},//big moving
            },
        },
        {//4M
        //thr, gop_size, ip_ratio, min_qp, max_qp
            {
            {  80,  75,  25, 20, 51},//static
            {  30,  25,  15, 23, 48},//moving
            {  80,  25,  15, 25, 46},//big moving
            },
        },
    },
};

#endif /* __MM_ENCODER_PARAM_H__ */

