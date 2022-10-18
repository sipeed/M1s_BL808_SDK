#ifndef __MM_ENCODER_H__
#define __MM_ENCODER_H__

#include <stdbool.h>

#define MMENCODER_VBR_ADAPTIVE_QP               (1)
#define MMENCODER_VBR_QP_FRAME_BCNT_HIST_NUM    (100)
#define MMENCODER_STREAM_STATS_DUR        (1000)
#define MMENCODER_IFRAME_MAX_QP           (51)
#define MMENCODER_PFRAME_MAX_QP           (51)
#define MMENCODER_IFRAME_MIN_QP           (0)
#define MMENCODER_PFRAME_MIN_QP           (0)

typedef enum {
	ENC_TYPE_JPEG,
	ENC_TYPE_H264,
	ENC_TYPE_H265,
} MMEncoderType;

typedef enum {
	ENC_JPEG_FRAME,
	ENC_H264_I_FRAME,
	ENC_H264_P_FRAME,
} MMFrameType;

typedef enum {
    ENC_PROFILE_BASELINE            = 0,
	ENC_PROFILE_MAIN                = 1,
} MMEncoderProfile;
    
typedef enum {
    ENC_RC_MODE_CBR                 = 0,    /**< CBR 模式 */
    ENC_RC_MODE_VBR                 = 1,    /**< VBR 模式*/
    ENC_RC_MODE_FIXQP               = 2,    /**< FIXQP 模式*/
} MMEncoderRcMode;

typedef enum {
    ENC_NORMAL_MODE                 = 0,
    ENC_LOW_POWER_MODE              = 1,
} MMEncoderLowPowerMode;

typedef enum {
    ENC_SW_MODE_DISABLED = 0,
    ENC_SW_MODE_AUTO,
    ENC_SW_MODE_MANUAL,
} MMEncoderFrameEncMode;

typedef enum {
    ENC_SC_MODE_STATIC = 0,
    ENC_SC_MODE_MOVING,
    ENC_SC_MODE_BIGMOVING,
    ENC_SC_MODE_NUM,
} MMEncoderScenceCtrlMode;
    
typedef enum {
    ENC_BITRATE_CTRL_512K = 0,
    ENC_BITRATE_CTRL_1M,
    ENC_BITRATE_CTRL_2M,
    ENC_BITRATE_CTRL_4M,
    ENC_BITRATE_CTRL_NUM,
} MMEncoderBitRateCtrlType;

typedef struct {
    uint32_t start_time;
    int start_bytes;
    int start_frm_cnt;
    int curr_frm_cnt;
    int stat_byte_cnt;
    float br_mbps;
    float fps;
} mmenc_stream_stats_t;

typedef struct {
    MMEncoderProfile        profile;        /**< 编码的等级, 0: baseline; 1:MP; 2:HP */
    MMEncoderLowPowerMode   lowPwrMode;
    uint32_t                gopSize;
} MMEncoderH264Attr;

typedef struct {
    uint32_t                quality;
} MMEncoderJpegAttr;

typedef struct {
    MMEncoderType           encType;
	uint32_t				picWidth;		/**< 编码图像宽度 */
	uint32_t				picHeight;		/**< 编码图像高度 */
    uint32_t                frmRateNum;
    uint32_t	            frmRateDen;
    mmenc_stream_stats_t    stats;
    union {
        MMEncoderH264Attr   attrH264;
        MMEncoderJpegAttr   attrJpeg;
    };
} MMEncoderAttr;

typedef struct {
    uint32_t            initQp;         /**< Init QP for encoder */
    uint32_t            maxQp;         /**< Max QP for encoder */
    uint32_t            minQp;         /**< Min QP for encoder */
    uint32_t            outBitRate;     /**< Output bitrate of steam */
    int                 iBiasLvl;       /**< Force IP Ratio */
} MMEncoderAttrH264CBR;

#if MMENCODER_VBR_ADAPTIVE_QP
struct mmenc_vbrDynQP_t {
    uint32_t frm_cnt;
    /* qp info for target bitrate changed */
    int target_i_qp;
    int target_p_qp;
    int iframe_min_qp;
    int ipratio;
    int iqp_ofst;
    int tot_mbcnt;
    /* bitrate history and parameter for dynamic qp calc */
    int vbr_budget;
    uint32_t prev_bit_count;
    int inc_count;
    int dec_count;
    int stb_count;
    double bitrate_sta;
    int vbr_qp_ctrl;
    int prate_count;
    double inc_ratio;
    double dec_ratio;
    float intra_pasu;
    uint8_t upWL; //up     trend monitor window length, recommend >=3 (unit : frame)
    uint8_t dnWL; //down   trend monitor window length, recommend >=10(unit : frame)
    uint8_t sbWL; //stable trend monitor window length, recommend >=5 (unit : frame)
    uint32_t gop_prelen;
    uint8_t sta_WL;     //frame bycnt log buffer,            recommend : 100(unit : frame)
    uint8_t prate_WL;     //peak rate qp tunning smooth size,  recommend : 5  (unit : frame)
    uint8_t gp_WL;       //group qp smooth size,              recommend : 60  (unit: frame)
    uint8_t gp_prelen;    //YP:depends on driver requirement, as small as possible, no more than 0.1*gp_WL(unit : frame)
    uint32_t frm_size_hist[MMENCODER_VBR_QP_FRAME_BCNT_HIST_NUM];
    uint8_t frm_size_idx_cur;
    
};
#endif


typedef struct {
    uint32_t                maxQp;          /**< Max QP for encoder */
    uint32_t                minQp;          /**< Min QP for encoder*/
    uint32_t                maxBitRate;     /**< max bitrate */
    uint32_t                targetBitRate;  /**< target bitrate */
    int                     iBiasLvl;       /**< Force IP Ratio (reserved) */
    uint32_t                qualityLvl;     /**< Target QP */
#if MMENCODER_VBR_ADAPTIVE_QP
    struct mmenc_vbrDynQP_t qpInfo;
#endif
} MMEncoderAttrH264VBR;

typedef struct {
	MMEncoderRcMode         rcMode;			    /**< RC 模式 */
	MMEncoderAttrH264CBR	attrH264Cbr;		/**< H.264 协议编码Channel Cbr 模式属性 */
	MMEncoderAttrH264VBR	attrH264Vbr;		/**< H.264 协议编码Channel Vbr 模式属性 */
} MMEncoderRcAttr;

typedef struct {
	uint32_t	frmRateNum;				/**< 在一秒钟内的时间单元的数量, 以时间单元为单位。即帧率的分子 */
	uint32_t	frmRateDen;				/**< 在一帧内的时间单元的数量, 以时间单元为单位。即帧率的分母 */
} MMEncoderFrmRate;

typedef struct {
	uint32_t		        gopSize;			/**< IDR参数 */
} MMEncoderGOPSizeCfg;

typedef struct {
	uint32_t		        bitRate;
} MMEncoderBitRateCfg;

typedef struct {
	uint32_t		        qualityLvl;
} MMEncoderQualityLvlCfg;

typedef struct {
	uint32_t		        quality;
} MMEncoderJpegQualityCfg;

typedef struct {
    MMFrameType frame_type;
    int stream_id;
    uint32_t frame_id;
    uint8_t *frame_start_addr;
    uint32_t frame_size;
    uint8_t *frame_sec_addr;
    uint32_t frame_sec_size;
} MMEncoderStream;

typedef struct {
    int scence_thr;
    uint8_t gop_size;
    uint8_t ip_ratio;
    uint8_t min_qp;
    uint8_t max_qp;
} MMEncoderScenceAttr;

typedef struct {
    MMEncoderScenceAttr scence_attr[ENC_SC_MODE_NUM];
} MMEncoderScenceCtrlAttr;

typedef struct {
    uint8_t enable;
    MMEncoderScenceCtrlAttr bitrate_ctrl[ENC_BITRATE_CTRL_NUM];
} MMEncoderBitRateCtrlAttr;

int MM_Encoder_GetRegInit(MMEncoderRcAttr *encRcAttr);
int MM_Encoder_CreateChn(int encChn);
int MM_Encoder_SetChnAttr(int encChn, const MMEncoderAttr *encAttr);
int MM_Encoder_GetChnAttr(int encChn, MMEncoderAttr *encAttr);
int MM_Encoder_SetChnRcAttr(int encChn, const MMEncoderRcAttr *encRcAttr);
int MM_Encoder_GetChnRcAttr(int encChn, MMEncoderRcAttr *encRcAttr);
int MM_Encoder_SetDirectLinkMode(bool enable);
int MM_Encoder_SetChnFrmRate(int encChn, const MMEncoderFrmRate *fpsCfg);
int MM_Encoder_GetChnFrmRate(int encChn, MMEncoderFrmRate *fpsCfg);
int MM_Encoder_SetChnGOPSize(int encChn, const MMEncoderGOPSizeCfg *gopSizeCfg);
int MM_Encoder_GetChnGOPSize(int encChn, MMEncoderGOPSizeCfg *gopSizeCfg);
int MM_Encoder_SetChnBitRate(int encChn, const MMEncoderBitRateCfg *bitRateCfg);
int MM_Encoder_GetChnBitRate(int encChn, MMEncoderBitRateCfg *bitRateCfg);
int MM_Encoder_SetChnMaxBitRate(int encChn, const MMEncoderBitRateCfg *bitRateCfg);
int MM_Encoder_GetChnMaxBitRate(int encChn, MMEncoderBitRateCfg *bitRateCfg);
int MM_Encoder_SetChnIpRatio(int encChn, const uint32_t ip_ratio);
int MM_Encoder_GetChnIpRatio(int encChn, uint32_t *ip_ratio);
int MM_Encoder_SetChnMaxQP(int encChn, const uint32_t qp);
int MM_Encoder_GetChnMaxQP(int encChn, uint32_t *qp);
int MM_Encoder_SetChnMinQP(int encChn, const uint32_t qp);
int MM_Encoder_GetChnMinQP(int encChn, uint32_t *qp);
int MM_Encoder_SetChnQualityLvl(int encChn, const MMEncoderQualityLvlCfg *qualityLvlCfg);
int MM_Encoder_GetChnQualityLvl(int encChn, MMEncoderQualityLvlCfg *qualityLvlCfg);
int MM_Encoder_SetChnJpegQuality(int encChn, const MMEncoderJpegQualityCfg *qualityCfg);
int MM_Encoder_GetChnJpegQuality(int encChn, MMEncoderJpegQualityCfg *qualityCfg);
int MM_Encoder_StartRecvPic(int encChn);
int MM_Encoder_StartRecvSnapshot(int encChn);
int MM_Encoder_Stop(int encChn);
int MM_Encoder_StopRecvPic(int encChn);
int MM_Encoder_GetStream(int encChn, MMEncoderStream *stream);
int MM_Encoder_H264_Frame_Done(int encChn, MMEncoderStream *stream);
int MM_Encoder_ResetStreamQueue(int encChn);
bool MM_Encoder_CheckStreamBusy(int encChn);
int MM_Encoder_EncodeOneFrame(int encChn, uint8_t *yuv_frame_addr, uint32_t *read_bytes);
float MM_Encoder_GetStreamBitrate(int encChn);
float MM_Encoder_GetStreamFPS(int encChn);
int MM_Encoder_FrameModeGetSource(int frmSrcChn, uint32_t *start_addr, uint32_t *size, uint8_t *y_uv);
int MM_Encoder_Frame_Encode_Next(int encChn, uint32_t y_buffer, uint32_t y_size, uint32_t uv_buffer, uint32_t uv_size);
void MM_Encoder_SWModeConfig(int encChn, MMEncoderFrameEncMode mode, uint8_t *base_addr);

int MM_Encoder_SetRcLevel(int encChn, const uint8_t level);
int MM_Encoder_GetRcLevel(int encChn, uint8_t *level);

int MM_Encoder_GetScenceCtrlRegInit(int encChn, uint32_t bitrate);
int MM_Encoder_SetScenceCtrlStatus(int encChn, uint8_t status);
int MM_Encoder_GetScenceCtrlStatus(int encChn, uint8_t *status);
int MM_Encoder_SetScenceCtrlReg(int encChn, const MMEncoderScenceCtrlMode mode, const MMEncoderScenceAttr *attr);
int MM_Encoder_GetScenceCtrlReg(int encChn, const MMEncoderScenceCtrlMode mode, MMEncoderScenceAttr *attr);
int MM_Encoder_UpdateCbrScenceCtrl(void);

int MM_Encoder_New(int id);
int MM_Encoder_Delete(int id);

#endif /* __MM_ENCODER_H__ */
