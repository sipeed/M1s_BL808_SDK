#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <aos/kernel.h>
#include <vfs.h>
#include <cli.h>
#include <unistd.h>
#include <math.h>
#include "bl_img_utils.h"

#include "mm_encoder.h"
#include "img_dsp2_parse.h"
#include "helper_venc_parse.h"

enum numeric_short_options {
    SCENCE_CTRL_REG,
    VENC_REG,
    JPEG_REG,
};

int g_chnid = 0;

static int VENC_ScenceCtrl_Parse(int type, char* reg, int value, char* ret_string)
{
    int val_get = 0, encChn = g_chnid;
    MMEncoderScenceAttr attr;
    MMEncoderScenceCtrlMode mode;

    if (strcmp(reg, "enable") == 0) {
        if (type == VENC_PARSE_WRITE) {
            MM_Encoder_SetScenceCtrlStatus(encChn, value);
            MM_Encoder_UpdateCbrScenceCtrl();
        } else {
            MM_Encoder_GetScenceCtrlStatus(encChn, (uint8_t*)&val_get);
        }
        sprintf(ret_string, "[OK] ScenceCtrl_%s: %d", reg, val_get);
        return 0;
    }

    if (strstr(reg, "static-") != NULL) {
        mode = ENC_SC_MODE_STATIC;
    } else if (strstr(reg, "big_moving-") != NULL) {
        mode = ENC_SC_MODE_BIGMOVING;  
    } else if (strstr(reg, "moving-") != NULL) {
        mode = ENC_SC_MODE_MOVING;
    } else {
        return -1;
    }

    MM_Encoder_GetScenceCtrlReg(encChn, mode, &attr);
    if (strstr(reg, "scence_thr") != NULL) {
        if (type == VENC_PARSE_WRITE) attr.scence_thr = value;
        else val_get = attr.scence_thr;
    } else if (strstr(reg, "gop_size") != NULL) {
        if (type == VENC_PARSE_WRITE) attr.gop_size = value;
        else val_get = attr.gop_size;
    } else if (strstr(reg, "ip_ratio") != NULL) {
        if (type == VENC_PARSE_WRITE) attr.ip_ratio = value;
        else val_get = attr.ip_ratio;
    } else if (strstr(reg, "min_qp") != NULL) {
        if (type == VENC_PARSE_WRITE) attr.min_qp = value;
        else val_get = attr.min_qp;
    } else if (strstr(reg, "max_qp") != NULL) {
        if (type == VENC_PARSE_WRITE) attr.max_qp = value;
        else val_get = attr.max_qp;
    } else {
        return -1;
    }

    if (type == VENC_PARSE_WRITE) {
        MM_Encoder_SetScenceCtrlReg(encChn, mode, &attr);
        MM_Encoder_UpdateCbrScenceCtrl();
        return 0;
    }
    sprintf(ret_string, "[OK] ScenceCtrl_%s: %d", reg, val_get);

    return 0;
    
}

static int VENC_JpegReg_Parse(int type, char* reg, int value, char* ret_string)
{
    int val_get = 0, encChn = g_chnid;
    MMEncoderJpegQualityCfg qualityCfg = {0};

    MM_Encoder_GetChnJpegQuality(encChn, &qualityCfg);
    if (strstr(reg, "quality") != NULL) {
        if (type == VENC_PARSE_WRITE) qualityCfg.quality = value;
        else val_get = qualityCfg.quality;
    } else {
        return -1;
    }

    if (type == VENC_PARSE_WRITE) {
        if (strstr(reg, "quality") != NULL)  MM_Encoder_SetChnJpegQuality(encChn, &qualityCfg);
        return 0;
    }
    sprintf(ret_string, "[OK] JpegReg_%s: %d", reg, val_get);

    return 0;
    
}

static int VENC_VencReg_Parse(int type, char* reg, int value, char* ret_string)
{
    int val_get = 0, ret = 0, encChn = g_chnid;
    uint32_t ip_ratio = 0, qp = 0;
    MMEncoderGOPSizeCfg gopSizeCfg = {0};
    MMEncoderQualityLvlCfg qualityLvlCfg = {0};
    MMEncoderBitRateCfg bitRateCfg = {0};
    MMEncoderRcAttr encRcAttr = {0};
    MMEncoderFrmRate fpsCfg = {0};

    if (strstr(reg, "rc-mode") != NULL) {
        MM_Encoder_GetChnRcAttr(encChn, &encRcAttr);
        if (type == VENC_PARSE_WRITE) encRcAttr.rcMode = value;
        else val_get = encRcAttr.rcMode;
    } else if (strstr(reg, "bitrate") != NULL) {
        MM_Encoder_GetChnBitRate(encChn, &bitRateCfg);
        if (type == VENC_PARSE_WRITE) bitRateCfg.bitRate = value;
        else val_get = bitRateCfg.bitRate;
    } else if (strstr(reg, "gop-size") != NULL) {
        MM_Encoder_GetChnGOPSize(encChn, &gopSizeCfg);
        if (type == VENC_PARSE_WRITE) gopSizeCfg.gopSize = value;
        else val_get = gopSizeCfg.gopSize;
    } else if (strstr(reg, "frmRate") != NULL) {
        MM_Encoder_GetChnFrmRate(encChn, &fpsCfg);
        if (strstr(reg, "frmRateNum") != NULL) {
            if (type == VENC_PARSE_WRITE) return -1;
            else val_get = fpsCfg.frmRateNum;
        } else  if (strstr(reg, "frmRateDen") != NULL) {
            if (type == VENC_PARSE_WRITE) return -1;
            else val_get = fpsCfg.frmRateDen;
        } else return -1;
    } else if (strstr(reg, "ip-ratio") != NULL) {
        MM_Encoder_GetChnIpRatio(encChn, &ip_ratio);
        if (type == VENC_PARSE_WRITE) ip_ratio = value;
        else val_get = ip_ratio;
    } else if (strstr(reg, "quality-lvl") != NULL) {
        MM_Encoder_GetChnQualityLvl(encChn, &qualityLvlCfg);
        if (type == VENC_PARSE_WRITE) qualityLvlCfg.qualityLvl = value;
        else val_get = qualityLvlCfg.qualityLvl;
    } else if (strstr(reg, "maxbitrate") != NULL) {
        MM_Encoder_GetChnMaxBitRate(encChn, &bitRateCfg);
        if (type == VENC_PARSE_WRITE) bitRateCfg.bitRate = value;
        else val_get = bitRateCfg.bitRate;
    } else if (strstr(reg, "min-qp") != NULL) {
        MM_Encoder_GetChnMinQP(encChn, &qp);
        if (type == VENC_PARSE_WRITE) qp = value;
        else val_get = qp;
    } else if (strstr(reg, "max-qp") != NULL) {
        MM_Encoder_GetChnMaxQP(encChn, &qp);
        if (type == VENC_PARSE_WRITE) qp = value;
        else val_get = qp;
    } else {
        return -1;
    }

    if (type == VENC_PARSE_WRITE) {
        if (strstr(reg, "rc-mode") != NULL) MM_Encoder_SetChnRcAttr(encChn, &encRcAttr);
        else if (strstr(reg, "bitrate") != NULL) MM_Encoder_SetChnBitRate(encChn, &bitRateCfg);
        else if (strstr(reg, "gop-size") != NULL) MM_Encoder_SetChnGOPSize(encChn, &gopSizeCfg);
        else if (strstr(reg, "ip-ratio") != NULL)  MM_Encoder_SetChnIpRatio(encChn, ip_ratio);
        else if (strstr(reg, "quality-lvl") != NULL) MM_Encoder_SetChnQualityLvl(encChn, &qualityLvlCfg);
        else if (strstr(reg, "maxbitrate") != NULL) MM_Encoder_SetChnMaxBitRate(encChn, &bitRateCfg);
        else if (strstr(reg, "min-qp") != NULL) ret = MM_Encoder_SetChnMinQP(encChn, qp);
        else if (strstr(reg, "max-qp") != NULL) ret = MM_Encoder_SetChnMaxQP(encChn, qp);
        return ret;
    }
    sprintf(ret_string, "[OK] VencReg_%s: %d", reg, val_get);

    return 0;
    
}

static int swich_cmd(char *str)
{
    if (strcmp(str, "scence_ctrl") == 0) return SCENCE_CTRL_REG;
    else if (strcmp(str, "venc-reg") == 0) return VENC_REG;
    else if (strcmp(str, "jpeg-reg") == 0) return JPEG_REG;
    else return -1;
}

void setChnId(int chnid)
{
    g_chnid = chnid;
}

int parse_venc_cmd(char* module, char* argv_reg, char* argv_val, int payload_len_in, char* ret_string)
{
    int arr_num = 0;
    int ret = -1;
    int *array = NULL;

    //aos_cli_printf("swich_cmd(module) %d, %d\r\n", swich_cmd(module));
    //aos_cli_printf(" module %s, argv_reg %s, argv_val %s\r\n", module, argv_reg, argv_val);

    if (argv_val != NULL) {
        array = malloc(sizeof(int) * payload_len_in);
        memset(array, 0, sizeof(int) * payload_len_in);
        isIntgerArray(argv_val, array, &arr_num); // because token,so argv_val will be change
    }
    //aos_cli_printf("arr_num %d\r\n", arr_num);

    int ch = swich_cmd(module);
    switch (ch)
    {
    case SCENCE_CTRL_REG: {
        if (arr_num != 0) {
            ret = VENC_ScenceCtrl_Parse(VENC_PARSE_WRITE, argv_reg, array[0], ret_string);
        } else {
            ret = VENC_ScenceCtrl_Parse(VENC_PARSE_READ, argv_reg, NULL, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    case VENC_REG: {
        if (arr_num != 0) {
            ret = VENC_VencReg_Parse(VENC_PARSE_WRITE, argv_reg, array[0], ret_string);
        } else {
            ret = VENC_VencReg_Parse(VENC_PARSE_READ, argv_reg, NULL, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    case JPEG_REG: {
        if (arr_num != 0) {
            ret = VENC_JpegReg_Parse(VENC_PARSE_WRITE, argv_reg, array[0], ret_string);
        } else {
            ret = VENC_JpegReg_Parse(VENC_PARSE_READ, argv_reg, NULL, ret_string);
        }
        if (ret < 0) goto FAIL;
        break;
    }
    default:
       goto FAIL;
    }

    if (argv_val != NULL) {
        free(array);
    }

    return 0;

FAIL:
    return -1;

}
