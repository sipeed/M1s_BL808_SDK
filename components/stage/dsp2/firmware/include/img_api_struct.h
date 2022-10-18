#ifndef __IMG_API_STRUCT_H__
#define __IMG_API_STRUCT_H__

#include <bl808.h>
#include "bl_dsp2.h"
#include "bl_comm_sns.h"

#define BL_ISO_NODES            (10)
#define BL_BV_NODES             (19)
#define BL_CT_NODES             (7)
#define BL_LSC_COEF_NUM         (6)
#define BL_LSC_MAX_NUM          (3)
#define BL_GAMMA_COEF_NUM       (256)
#define BL_AE_HIST_Y_BIN_NUM    (257)
#define BL_STATS_GRID_NUM       (12*8)
#define BL_AWB_SPECIAL_COLOR    (4)
#define BL_WDR_IDX_NUM          (3)
#define BL_WDR_TONE_NUM         (64)
#define BL_EE_LUMA_WEIGHT_NUM   (32)

typedef void BL_VOID;
typedef bool BL_BOOL;
typedef char BL_CHAR;
typedef signed char     BL_SINT8;
typedef short int       BL_SINT16;
typedef int             BL_SINT32;
typedef long long int   BL_SINT64;
typedef unsigned char           BL_UINT8;
typedef unsigned short int      BL_UINT16;
typedef unsigned int            BL_UINT32;
typedef unsigned long long int  BL_UINT64;


/****************** MODULE STATE TYPE ***********************/

typedef enum {
    DSP2_HW_MODULE_AE = 0,
    DSP2_HW_MODULE_AWB,
    DSP2_HW_MODULE_DPC,
    DSP2_HW_MODULE_BNR,
    DSP2_HW_MODULE_LSC,
    DSP2_HW_MODULE_CCM,
    DSP2_HW_MODULE_GAMMA,
    DSP2_HW_MODULE_WDR,
    DSP2_HW_MODULE_EE,
    DSP2_HW_MODULE_CS,
    DSP2_HW_MODULE_PARAM_NUM
} DSP2_HW_MODULE_STATE_ATTR;

typedef struct  {
    BL_Fun_Type state[DSP2_HW_MODULE_PARAM_NUM];
} DSP2_HW_MODULE_STATE;

/****************** AE PARAM TYPE ***********************/
typedef enum {
    AE_METERING_AVERAGE = 0,
    AE_METERING_CENTER_WEIGHTED,
    AE_METERING_SPOT,
    AE_METERING_CUSTOM,
    AE_METERING_NUM,
} AE_METERING;

typedef struct _DSP2_AE_SUB_ATTR_S_
{
    BL_UINT32 ae_target;
} __attribute__((__packed__)) DSP2_AE_SUB_ATTR;

typedef struct {
    BL_UINT16 coef[AE_STATS_GRID_NUM];
} __attribute__((__packed__)) DSP2_AE_METERING_TBL; 

typedef struct {
    BL_UINT8 idx[3];
} __attribute__((__packed__)) DSP2_AE_HIGHLIGHT_WEIGHT;

typedef struct  {
    BL_UINT8 enable;
    BL_UINT16 roi_start;
    BL_UINT16 roi_end;
    BL_UINT16 thr[4];
    DSP2_AE_HIGHLIGHT_WEIGHT highlight_weight[BL_BV_NODES];
} __attribute__((__packed__)) DSP2_AE_HIGHLIGHT_WEIGHT_CONF;

/****************** AWB PARAM TYPE ***********************/

/****************** BLC PARAM TYPE ***********************/
typedef struct {
    BL_UINT32 black_level;
} __attribute__((__packed__)) DSP2_BLC_PARAM;


/****************** DPC PARAM TYPE ***********************/
typedef struct {
    BL_UINT8 strength;
} __attribute__((__packed__)) DSP2_DPC_PARAM;


/****************** BNR PARAM TYPE ***********************/
typedef struct {
    BL_UINT16 strength;
} __attribute__((__packed__)) DSP2_BNR_PARAM;


/****************** LSC PARAM TYPE ***********************/
typedef struct {
    BL_SINT32 strength;
    BL_COLOR_TEMP color_temp;
} __attribute__((__packed__)) DSP2_LSC_PARAM;

/****************** CCM PARAM TYPE ***********************/
typedef struct {
    BL_SINT16 coef[CCM_COEF_NUM];
    BL_COLOR_TEMP color_temp;
} __attribute__((__packed__)) DSP2_CCM_PARAM;

typedef struct {
    BL_UINT8 color_weight;
} __attribute__((__packed__)) DSP2_CCM_CW_PARAM;

/****************** GAMMA PARAM TYPE *********************/
typedef struct {
    BL_SINT16 idx;
} __attribute__((__packed__)) DSP2_GAMMA_PARAM;


/******************* WDR PARAM TYPE **********************/
typedef struct {
    BL_SINT32 cs_strength;
    BL_SINT32 curve_weight;
    BL_SINT32 enh_weight;
    BL_SINT32 bright_enh_level;
    BL_SINT32 dark_enh_level;
} __attribute__((__packed__)) DSP2_WDR_PARAM;

typedef struct {
    BL_UINT8 idx[3];
} __attribute__((__packed__)) DSP2_WDR_LUMA_WEIGHT;

typedef struct  {
    BL_UINT16 roi_start;
    BL_UINT16 roi_end;
    BL_UINT16 thr[4];
    DSP2_WDR_LUMA_WEIGHT weight[BL_BV_NODES];
} __attribute__((__packed__)) DSP2_WDR_LUMA_WEIGHT_CONF;

typedef struct {
    BL_UINT16 coef[BL_WDR_TONE_NUM];
} DSP2_WDR_TONE_CURVE;

typedef struct {
    DSP2_WDR_TONE_CURVE tone_curve;
    BL_UINT8 idx;
} DSP2_WDR_TONE_CURVE_CONF;

typedef struct {
    BL_UINT8 enable;
    DSP2_WDR_LUMA_WEIGHT_CONF luma_weight_conf;
    DSP2_WDR_TONE_CURVE_CONF tone_curve_container[BL_WDR_IDX_NUM];
} __attribute__((__packed__)) DSP2_WDR_TONE_PARAM;


/**************** SATURATION PARAM TYPE ******************/
typedef struct {
    BL_UINT8 value;
} __attribute__((__packed__)) DSP2_SAT_PARAM;

/******************** NR PARAM TYPE **********************/
typedef struct {
    BL_UINT16 strength_level;
    BL_UINT8  strength_2d;
    BL_UINT8  strength_3d;
} __attribute__((__packed__)) DSP2_NR_PARAM;

/******************** EE PARAM TYPE **********************/
typedef struct {
    BL_UINT8  pos_edge_strength;
    BL_UINT8  neg_edge_strength;
    BL_UINT8  pos_edge_ovrsht_strength;
    BL_UINT8  neg_edge_ovrsht_strength;
    BL_UINT8  nr_strength;
    BL_UINT8  dir_shpness_thr;
    BL_UINT8  no_dir_shpness_thr;
    BL_UINT8  flat_thr;
    BL_UINT16 texture_thr;
    BL_UINT16 edge_thr;
} __attribute__((__packed__)) DSP2_EE_PARAM;

typedef struct {
    BL_UINT16 weight[BL_EE_LUMA_WEIGHT_NUM];
}  __attribute__((__packed__)) DSP2_EE_LUMA_WEIGHT;

/******************** CS PARAM TYPE **********************/
typedef struct {
    BL_UINT8 strength;
} __attribute__((__packed__)) DSP2_CS_PARAM;


/******************** yc PARAM TYPE **********************/
typedef struct {
    BL_UINT8 brightness;
    BL_UINT8 contrast;
} __attribute__((__packed__)) DSP2_YC_PARAM;

/******************** dg PARAM TYPE **********************/


/************ IMG PARAM DESCRIPTION **********************/


#endif /* __IMG_API_STRUCT_H__ */

