#ifndef __API_STRUCT_H__
#define __API_STRUCT_H__

#include <stdbool.h>
#include "img_api_struct.h"


#define AWB1_STATS_GRID_NUM_X   (32)
#define AWB1_STATS_GRID_NUM_Y   (32)
#define AWB1_STATS_GRID_NUM     ((AWB1_STATS_GRID_NUM_X)*(AWB1_STATS_GRID_NUM_Y))
#define EE_LUMA_WEIGHT_NUM      (32)

// RETURN
#define BL_RET_CHANGE_FMT       (2)
#define BL_RET_NO_CHANGE_FMT    (1)
#define BL_RET_OK               (0)
#define BL_RET_NG               (-1)

// ERROR
#define BL_DSP2_CORE_ERR_BASE            (-1000)
#define BL_ERR_WAIT_PICEND_FAILED       (BL_DSP2_CORE_ERR_BASE - 8)
#define BL_ERR_DSP2_RAW_BUFF_NOTENOUGH   (BL_DSP2_CORE_ERR_BASE - 9)
#define BL_ERR_DSP2_SET_CIS_CLK          (BL_DSP2_CORE_ERR_BASE - 10)
#define BL_ERR_DSP2_UNEXPECTED_PIC_SIZE  (BL_DSP2_CORE_ERR_BASE - 11)

#define BL_API_ERR_BASE                 (-3000)
#define BL_ERR_MEMSIZE_UNDERFLOW        (BL_API_ERR_BASE - 1)
#define BL_ERR_NULL_POINTER             (BL_API_ERR_BASE - 2)
#define BL_ERR_DSP2_INIT                 (BL_API_ERR_BASE - 3)

/************ STATS *********************************************************/
typedef struct _DSP2_YHIST_STAT_S_
{
    BL_UINT32 u32YhistStatCnt[BL_AE_HIST_Y_BIN_NUM];
}   DSP2_YHIST_STAT;

typedef struct _DSP2_GRID_STAT_S_
{//12x8
    BL_UINT8 u08RSum[BL_STATS_GRID_NUM];
    BL_UINT8 u08GSum[BL_STATS_GRID_NUM];
    BL_UINT8 u08BSum[BL_STATS_GRID_NUM];
    BL_UINT8 u08YSum[BL_STATS_GRID_NUM];
}   DSP2_GRID_STAT;

/************ AE *********************************************************/

typedef struct _DSP2_AE_GRID_SUM_S_
{
    BL_UINT8 r_sum[AE_STATS_GRID_NUM];
    BL_UINT8 g_sum[AE_STATS_GRID_NUM];
    BL_UINT8 b_sum[AE_STATS_GRID_NUM];
    BL_UINT8 y_sum[AE_STATS_GRID_NUM];
} DSP2_AE_GRID_SUM;

typedef struct _DSP2_AE_STATS_S_
{
    DSP2_AE_GRID_SUM aeGridSum;
    BL_UINT32 aeHistY[DSP2_AE_HIST_Y_BIN_NUM];
} DSP2_AE_STATS;

typedef struct _DSP2_AE_INFO_S_
{
    BL_UINT32 expo_time;
    BL_UINT32 gain;
} DSP2_AE_INFO;

typedef struct _DSP2_AE_ATTR_S_
{
    DSP2_AE_SUB_ATTR subAttr[BL_BV_NODES];
    DSP2_AE_METERING_TBL meteringModeTbl[AE_METERING_NUM];
    DSP2_AE_HIGHLIGHT_WEIGHT_CONF weightConf;
    BL_UINT8 meteringMode;
    BL_UINT8 aeSpeed;
} DSP2_AE_ATTR;


/************ AWB *********************************************************/

typedef struct _DSP2_AWB1_STATS_S_
{
    RGB_SUM_S sum[AWB1_STATS_GRID_NUM];
} DSP2_AWB1_STATS;

typedef struct _DSP2_AWB3_STATS_S_
{
    BL_UINT32 r_sum;
    BL_UINT32 g_sum;
    BL_UINT32 b_sum;
    BL_UINT32 r_sum_hex;
    BL_UINT32 g_sum_hex;
    BL_UINT32 b_sum_hex;
    BL_UINT32 pixel_hex;
    BL_UINT64 r_ratio_hex_y;
    BL_UINT64 b_ratio_hex_y;
    BL_UINT32 weight_hex_y;
    BL_UINT32 pixel_hex_y;
    BL_UINT64 r_ratio_hist;
    BL_UINT64 b_ratio_hist;
    BL_UINT32 weight_hist;
    BL_UINT32 pixel_hist;
    BL_UINT64 r_ratio_hist_clip;
    BL_UINT64 b_ratio_hist_clip;
    BL_UINT32 weight_hist_clip;
    BL_UINT32 pixel_hist_clip;
} DSP2_AWB3_STATS;

typedef struct _DSP2_AWB_STATS_S_
{
    DSP2_AWB1_STATS awb1Stats;
    DSP2_AWB3_STATS awb3Stats;
    //BL_UINT32 awbHist[DSP2_AWB_HIST_Y_BIN_NUM];
} DSP2_AWB_STATS;

typedef struct {
    BL_UINT16 r_gain;
    BL_UINT16 g_gain;
    BL_UINT16 b_gain;
    BL_UINT32 color_temp;
} DSP2_AWB_WB_INFO;

typedef struct _AWB_DEFAULT_CFG_S_
{
    DSP2_AWB_WB_INFO wbInfo[BL_CT_NODES];
} AWB_DEFAULT_CFG;

typedef struct {
    BL_UINT16 r_gain;
    BL_UINT16 b_gain;
} DSP2_AWB_RB_GAIN;

typedef struct {
    DSP2_AWB_RB_GAIN bais[3];
} DSP2_AWB_BAIS;

typedef struct {
    BL_UINT16 r_gain;
    BL_UINT16 b_gain;
    BL_UINT8  weight;
} DSP2_AWB_SPECIAL_COLOR;

typedef struct _DSP2_AWB_ATTR_S_
{
    BL_UINT8 preference_enable;
    BL_UINT8 special_color_enable;
    DSP2_AWB_BAIS preference_gain[BL_BV_NODES];
    DSP2_AWB_SPECIAL_COLOR special_color_info[BL_AWB_SPECIAL_COLOR];
    BL_UINT8 awbSpeed;
} DSP2_AWB_ATTR;

/************ DSP2 FRONT *********************************************************/
/*********** BLC *************************************/
typedef struct _DSP2_BLC_ATTR_S_
{
    BL_BOOL bBlcEn;
    BL_BOOL bManualModeEn;
    DSP2_BLC_PARAM blcLv;
    DSP2_BLC_PARAM blc[BL_ISO_NODES];
} DSP2_BLC_ATTR;

/************ DPC *************************************/
typedef struct _DSP2_DPC_ATTR_S_
{
    BL_BOOL bDpcEn;
    BL_BOOL bManualModeEn;
    DSP2_DPC_PARAM dpcLv;
    DSP2_DPC_PARAM dpc[BL_ISO_NODES];
} DSP2_DPC_ATTR;


/************ BNR *************************************/
typedef struct _DSP2_BNR_ATTR_S_
{
    BL_BOOL bBnrEn;
    BL_BOOL bManualModeEn;
    DSP2_BNR_PARAM bnrLv;
    DSP2_BNR_PARAM bnr[BL_ISO_NODES];
} DSP2_BNR_ATTR;

/************ LSC *************************************/
typedef struct _DSP2_LSC_ATTR_S_
{
    BL_BOOL bLscEn;
    BL_BOOL bManualModeEn;
    DSP2_LSC_PARAM lscLv;
    DSP2_LSC_PARAM lsc[BL_CT_NODES];
} DSP2_LSC_ATTR;

/************ DSP2 BACK *********************************************************/
/************ CCM *************************************/
typedef struct _DSP2_CCM_ATTR_S_
{
    BL_BOOL bCcmEn;
    BL_BOOL bManualModeEn;
    DSP2_CCM_PARAM ccmLv;
    DSP2_CCM_PARAM ccm[BL_CT_NODES];
    DSP2_CCM_CW_PARAM ccmCwLv;
    DSP2_CCM_CW_PARAM ccmCw[BL_ISO_NODES];
} DSP2_CCM_ATTR;

/************ GAMMA *************************************/
typedef struct _DSP2_GAMMA_ATTR_S_
{
    BL_BOOL bGammaEn;
    BL_BOOL bManualModeEn;
    DSP2_GAMMA_PARAM gammaLv;
    DSP2_GAMMA_PARAM gamma[BL_BV_NODES];
} DSP2_GAMMA_ATTR;

/************ WDR *************************************/
typedef struct _DSP2_WDR_ATTR_S_
{
    BL_BOOL bWdrEn;
    BL_BOOL bManualModeEn;
    DSP2_WDR_PARAM wdrLv;
    DSP2_WDR_PARAM wdr[BL_BV_NODES];
    DSP2_WDR_TONE_PARAM wdrTone;
} DSP2_WDR_ATTR;

/************ SAT *************************************/
typedef struct _DSP2_SAT_ATTR_S_
{
    BL_BOOL bSaturationEn;
    BL_BOOL bManualModeEn;
    DSP2_SAT_PARAM satLv;
    DSP2_SAT_PARAM sat[BL_ISO_NODES];
} DSP2_SAT_ATTR;

/************ NR *************************************/
typedef struct _DSP2_NR_ATTR_S_
{
    BL_BOOL bNrEn;
    BL_BOOL bManualModeEn;
    DSP2_NR_PARAM nrLv;
    DSP2_NR_PARAM nr[BL_ISO_NODES];
} DSP2_NR_ATTR;

/************ EE *************************************/
typedef struct _DSP2_EE_ATTR_S_
{
    BL_BOOL bEeEn;
    BL_BOOL bOvrShtEn;
    BL_BOOL bManualModeEn;
    DSP2_EE_PARAM eeLv;
    DSP2_EE_PARAM ee[BL_ISO_NODES];
    DSP2_EE_LUMA_WEIGHT eeLumaWeightTbl;
}  DSP2_EE_ATTR;


/************ CS *************************************/
typedef struct _DSP2_CS_ATTR_S_
{
    BL_BOOL bCsEn;
    BL_BOOL bManualModeEn;
    DSP2_CS_PARAM csLv;
    DSP2_CS_PARAM cs[BL_ISO_NODES];
} DSP2_CS_ATTR;


/************ YC *************************************/
typedef struct _DSP2_YC_ATTR_S_
{
    BL_BOOL bYcEn;
    BL_BOOL bManualModeEn;
    DSP2_YC_PARAM ycLv;
    DSP2_YC_PARAM yc[BL_ISO_NODES];
} DSP2_YC_ATTR;


#endif

