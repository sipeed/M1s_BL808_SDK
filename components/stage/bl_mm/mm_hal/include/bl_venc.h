#ifndef __BL_ENC_H__
#define __BL_ENC_H__

#include <bl808_comm_mm.h>

#if !defined(MIN)
#define MIN(x, y) ((x) > (y) ? (y) : (x))
#endif

#if !defined(MAX)
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#endif

typedef enum {
    BL_H264_ENC_NORMAL,
    BL_H264_ENC_LOW_BANDW,
} BL_H264_ENC_TYPE_T;

typedef enum {
    BL_BITRATE_MODE_CBR,
    BL_BITRATE_MODE_VBR,
    BL_BITRATE_MODE_FIXQP,
} BL_BITRATE_MODE_T;

typedef enum {
    BL_H264_PROFILE_BASELINE,
    BL_H264_PROFILE_MAIN,
} BL_H264_PROFILE_T;

typedef enum {
    BL_H264_I_FRAME,
    BL_H264_P_FRAME,
    BL_H264_UNKNOWN_FRAME,
} BL_H264_FRAME_TYPE_T;

typedef enum {
    BL_H264_ROI_INDEX_0 = 0,
    BL_H264_ROI_INDEX_1,
    BL_H264_ROI_INDEX_2,
    BL_H264_ROI_INDEX_3,
    BL_H264_ROI_INDEX_4,
    BL_H264_ROI_INDEX_5,
    BL_H264_ROI_INDEX_6,
    BL_H264_ROI_INDEX_7,
    BL_H264_ROI_INDEX_MAX = 8,
} BL_H264_ROI_INDEX_T;

typedef struct {
    uint32_t index;
    uint32_t mbx_s;
    uint32_t mbx_e;
    uint32_t mby_s;
    uint32_t mby_e;
}venc_roi_coordinate_info_t;

typedef struct {
    uint8_t *y_frame_base_addr;
    uint32_t y_frame_size; 
    uint8_t *uv_frame_base_addr;
    uint32_t uv_frame_size;
} bl_venc_input_buffer_t;

typedef struct {
    uint32_t    stream_id;
    uint32_t    frame_id;
    uint8_t     *frame_start_addr;
    uint32_t    frame_size;
    uint8_t     *frame_sec_half_start_addr;
    uint32_t    frame_sec_half_size;
    BL_H264_FRAME_TYPE_T    frame_type;
} venc_frame_desc_t;

typedef struct
{
    BL_H264_ENC_TYPE_T enc_type;
    BL_BITRATE_MODE_T bitrate_mode;
    BL_H264_PROFILE_T profile;
    uint16_t width;
    uint16_t height;
    uint32_t bit_rate;
    uint16_t gop_size;
    uint8_t frame_rate_num;
    uint8_t frame_rate_den;
    uint8_t init_qp;
    uint8_t target_i_qp;
    uint8_t target_p_qp;
    uint8_t min_qp;
    uint8_t max_qp;
    uint8_t force_ip_ratio;
} bl_h264_config_t;

typedef struct {
    uint8_t* base_addr;
    uint32_t size;
    uint8_t* sec_base_addr;
    uint32_t sec_size;
} bl_h264_bs_buff_info_t;

typedef struct
{
    uint16_t width;
    uint16_t height;
    uint8_t quality;
} bl_jpeg_config_t;

typedef int (*bl_venc_alloc_cb)(void *usrdata, size_t size, int is_load_high, void **ptr_mem);
typedef int (*bl_venc_free_cb)(void *usrdata, void *ptr_mem);
typedef int (*bl_venc_frame_cb)(void *usrdata, venc_frame_desc_t *frame_desc, int is_overflow);
typedef int (*bl_venc_stop_cb)(void *usrdata, int stream_id);

int bl_venc_set_h264_sw_mode(int stream_id, BL_Fun_Type enable);
int bl_venc_set_h264_sramck_old(BL_Fun_Type state);
int bl_venc_set_h264_input_channel(int stream_id, uint8_t dsp2_chann_id);
int bl_venc_set_h264_FPS_on_the_fly(int stream_id, int framerate_num, int framerate_den);
int bl_venc_set_h264_bitrate_on_the_fly(int stream_id, bl_h264_config_t *config);
int bl_venc_set_h264_gop_size_on_the_fly(int stream_id, int gopSize);
int bl_venc_set_h264_target_i_qp_on_the_fly(int stream_id, int qp);
int bl_venc_set_h264_target_p_qp_on_the_fly(int stream_id, int qp);
int bl_venc_set_h264_max_qp_on_the_fly(int stream_id, int qp);
int bl_venc_set_h264_min_qp_on_the_fly(int stream_id, int qp);
int bl_venc_set_h264_profile(int stream_id, int profile);
int bl_venc_set_h264_config(int stream_id, bl_h264_config_t *config);
int bl_venc_set_h264_input_buffer(int stream_id, bl_venc_input_buffer_t *input_buffer);
int bl_venc_set_h264_internal_buffer(int stream_id);
uint16_t bl_venc_get_h264_intra_mbcnt(int stream_id);
void bl_venc_get_h264_mv_scence_weight(int stream_id, int *static_weight_out, int *big_motion_weight_out);
void bl_venc_get_h264_rc_param(int stream_id, int *target_i_qp, int *target_p_qp, int *iframe_min_qp, int *ipratio, int *iqp_ofst);
void bl_venc_set_qp(int stream_id, int target_i_qp, int target_p_qp);
int bl_venc_sync_buffer(int stream_id);
int bl_venc_start_h264_enc(int stream_id);
int bl_venc_h264_frame_done(int stream_id, bl_h264_bs_buff_info_t *buf_info);
int bl_venc_stop_h264_enc(int stream_id, bl_venc_stop_cb cb);
int bl_venc_stop_recv_h264_pic(int stream_id);
int bl_venc_start_h264_enc_session(int stream_id);
int bl_venc_stop_h264_enc_session(int stream_id);
int bl_venc_set_jpeg_input_channel(int stream_id, uint8_t dsp2_chann_id);
int bl_venc_set_jpeg_config(int stream_id, bl_jpeg_config_t *config);
int bl_venc_set_jpeg_Qtable(int num, uint16_t *table);
int bl_venc_get_jpeg_Qtable(int *table, int *size);
int bl_venc_jpeg_set_quality(int quality);
int bl_venc_start_jpeg_enc(int stream_id, bl_venc_input_buffer_t *input_buffer);
int bl_venc_stop_jpeg_enc(int stream_id, bl_venc_stop_cb cb);
int bl_venc_stop_recv_jpeg_pic(int stream_id);
int bl_venc_get_JFIF_header(uint8_t **addr, uint32_t *size);
int bl_venc_get_JFIF_tail(uint8_t **addr, uint32_t *size);

/*Roi API */
int bl_venc_roi_set_coordinate(uint32_t stream_id, venc_roi_coordinate_info_t *roi_info);
/* Note: bl_venc_roi_set_imb_bits
param@total_mbs:must be round to 16*16, ex：1920*1080 -> 1920 *1088 */
int bl_venc_set_roi_bit_ratio(uint32_t stream_id, uint32_t ibit_ratio, uint32_t pbit_ratio);
int bl_venc_set_roi_n2r_qp_decr(uint32_t stream_id, uint32_t qp);
int bl_venc_set_roi_iqp_decr(uint32_t stream_id, uint32_t iqp, uint32_t pqp);
int bl_venc_set_roi_bit_ofst(uint32_t stream_id, uint32_t iofst, uint32_t pofst);
int bl_venc_set_nroi_bit_ofst(uint32_t stream_id, uint32_t iofst, uint32_t pofst);
int bl_venc_roi_reset(uint32_t stream_id);
int bl_venc_roi_en_config(uint32_t stream_id);

int bl_venc_init(void);
int bl_venc_set_callback(int stream_id, bl_venc_alloc_cb alloc_cb, bl_venc_free_cb free_cb,
    bl_venc_frame_cb frame_cb, void *usrdata);

int bl_venc_set_3dnr(uint32_t stream_id, int level, int strength);

void MJENC_IRQHandler(void);

#endif /* __BL_ENC_H__ */

