#ifndef __MM_DSP2_H__
#define __MM_DSP2_H__

#include <bl_dsp2.h>
#include "mm_common.h"
#include "mm_debug.h"
#include "img_struct.h"

typedef enum {
    DSP2_POSITION_DSP2_INPUT              = 0,
    DSP2_POSITION_ACT                    = 0x1,
    DSP2_POSITION_DEFECT                 = 0x2,
    DSP2_POSITION_COLOR_CORRECTION_R     = 0x3,
    DSP2_POSITION_COLOR_CORRECTION_G     = 0x4,
    DSP2_POSITION_COLOR_CORRECTION_B     = 0x5,
    DSP2_POSITION_GAMMA_CORRECTION_R     = 0x6,
    DSP2_POSITION_GAMMA_CORRECTION_G     = 0x7,
    DSP2_POSITION_RESERVED               = 0x8,
    DSP2_POSITION_BAYER_NOISE_REDUCTION  = 0x9,
    DSP2_POSITION_NOISE_REDUCTION        = 0xa,
    DSP2_POSITION_EDGE_ENHANCEMENT_OUT   = 0xb,
    DSP2_POSITION_DSP2_OUTPUT             = 0xc,
    DSP2_POSITION_OSD_A                  = 0xd,
    DSP2_POSITION_OSD_B                  = 0xe,
    DSP2_POSITION_OSD_C                  = 0xf,
    DSP2_POSITION_OSD_D                  = 0x10,
    DSP2_POSITION_SCALER_A               = 0x11,
    DSP2_POSITION_SCALER_B               = 0x12,
    DSP2_POSITION_SCALER_C               = 0x13,
    DSP2_POSITION_SCALER_D               = 0x14,
    DSP2_POSITION_ADJ_A                  = 0x15,
    DSP2_POSITION_ADJ_B                  = 0x16,
    DSP2_POSITION_ADJ_C                  = 0x17,
    DSP2_POSITION_ADJ_D                  = 0x18,
    DSP2_POSITION_YUV420_A               = 0x19,
    DSP2_POSITION_YUV420_B               = 0x1a,
    DSP2_POSITION_YUV420_C               = 0x1b,
    DSP2_POSITION_YUV420_D               = 0x1c,
    DSP2_POSITION_GAMMA_CORRECTION_B     = 0x1d,
    DSP2_POSITION_WDR_Y                  = 0x1e,
    DSP2_POSITION_WDR_U                  = 0x1f,
    DSP2_POSITION_WDR_V                  = 0x20,
    DSP2_POSITION_LSC                    = 0x21,
    DSP2_POSITION_AWB3                   = 0x22,
    DSP2_POSITION_YUV2RGB                = 0x23,
    DSP2_POSITION_DVPAS2X                = 0x24,
} MMDSP2Position;

typedef struct {
	uint32_t enable;		/**< 使能裁剪功能 */
	uint32_t left;		    /**< 裁剪左起始点 */
	uint32_t top;		    /**< 裁剪上起始点 */
	uint32_t width;		    /**< 图片裁剪宽度 */
	uint32_t height;		/**< 图片裁剪高度 */
} MMDSP2FrmSrcCrop;

typedef struct {
	uint32_t enable;		/**< 使能缩放功能 */
	uint32_t outwidth;	    /**< 缩放后图片宽度 */
	uint32_t outheight;	    /**< 缩放后图片高度 */
} MMDSP2FrmSrcScaler;

typedef struct {
	uint32_t	frmRateNum;				/**< 在一秒钟内的时间单元的数量, 以时间单元为单位。即帧率的分子 */
	uint32_t	frmRateDen;				/**< 在一帧内的时间单元的数量, 以时间单元为单位。即帧率的分母 */
} MMDSP2FrmRate;

typedef struct {
	uint32_t picWidth;				/**< 图片宽度 */
	uint32_t picHeight;				/**< 图片高度 */
	MMPixelFormat pixFmt;		    /**< 图片格式 */
	uint32_t outFrmRateNum;			/**< 通道的输出帧率分子 */
	uint32_t outFrmRateDen;			/**< 通道的输出帧率分母 */
    bool     isFullRange;           /**< YUV Range */
    MMDSP2Position dsp2Position;      /**< for debug only */
} MMDSP2FrmSrcAttr;

typedef struct
{
    BL_Img_Size_T total_win;
    BL_Img_Size_T act_win;
    BL_Img_Size_T out_win;
    BAYER_PATTERN_E bayer_pattern;
    uint8_t fps;
} MMDSP2VinAttr;

typedef struct {
    uint8_t *frameStartAddr;
    uint32_t frameSize;
} MMDSP2YuvFrame;

int MM_DSP2_Init_Run(void);
int MM_Virsensor_Init(uint8_t *buf, uint8_t is_fakedata);
int MM_DSP2_Init(void);
int MM_DSP2_Run(void);
int MM_DSP2_Pause(void);
int MM_DSP2_Resume(void);
int MM_DSP2_Exit(void);
int MM_DSP2_Status(void);

int MM_YUVSensor_Init(void);
int MM_DSP2_GetBinAddr(uint32_t *addr,uint32_t *size);
int MM_DSP2_LoadDsp2Param(uint32_t *dsp2_param_buff);
int MM_DSP2_SetDsp2Param(BL_IMG_PARAM_SW_BIN_DESC_T *pstDefaultParam);
int MM_DSP2_GetDsp2Reg(uint32_t addr,uint32_t *data);
int MM_DSP2_SetDsp2Reg(uint32_t addr,uint32_t data);
int MM_DSP2_GetHWmoduleCfg(uint32_t *modulecfg);
int MM_DSP2_SetHWmoduleCfg(uint32_t modulecfg);
int MM_DSP2_SetVinAttr(MMDSP2VinAttr *vin_attr);
int MM_DSP2_GetVinAttr(MMDSP2VinAttr *vin_attr);
int MM_DSP2_CreateFrameSrcChn(int chnID, MMDSP2FrmSrcAttr *frmSrcAttr);
int MM_DSP2_SetFrameSrcChnAttr_crop(int frmSrcChn, MMDSP2FrmSrcCrop *frmSrcCropRoi);
int MM_DSP2_SetFrameSrcChnAttr(int chnID, const MMDSP2FrmSrcAttr *frmSrcAttr);
int MM_DSP2_GetFrameSrcChnAttr(int chnID, MMDSP2FrmSrcAttr *frmSrcAttr);
int MM_DSP2_SetFrameSrcChnFPS(int frmSrcChn, const MMDSP2FrmRate *fpsCfg);
int MM_DSP2_GetFrameSrcChnFPS(int frmSrcChn, MMDSP2FrmRate *fpsCfg);
int MM_DSP2_StartRecvPic(int frmSrcChn, MMPixelFormat picFormat);
int MM_DSP2_StartDumpPic(int frmSrcChn, MMPixelFormat picFormat, BL_DSP2_IMAGE_DUMP_SRC_T frm_src);
int MM_DSP2_StopRecvPic(int frmSrcChn);
int MM_DSP2_GetOnePicture(int frmSrcChn, MMDSP2YuvFrame *yuvFrame);
int MM_DSP2_ResumDumpPic(int frmSrcChn);
int MM_DSP2_PauseDumpPic(int frmSrcChn);
int MM_DSP2_HDMI_Start(void);
int MM_DSP2_HDMI_Stop(void);

void MM_DSP2_Update_FPS_Register(bl_dsp2_update_fps_cb *cb);


#endif /* __MM_DSP2_H__ */
