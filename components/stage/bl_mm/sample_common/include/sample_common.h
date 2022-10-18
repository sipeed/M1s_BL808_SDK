#ifndef __SAMPLE_COMMON_H__
#define __SAMPLE_COMMON_H__

#include "mm_encoder.h"
#include "bl_img_utils.h"

#define CH0_ID                          (0)
#define CH1_ID                          (1)
#define CH2_ID                          (2)
#define CH3_ID                          (3)
#define MAX_CHN_NUM                     (4)

#define BITRATE_720P_Kbs                1000

int sample_get_jpeg_info(uint8_t *quality, uint16_t *width, uint16_t *height);
int sample_get_jpeg_pic(uint8_t **pic_ptr, uint32_t *len, int stream_id);
int sample_get_h264_frame(uint8_t **pic_ptr1, uint32_t *len1, uint8_t **pic_ptr2, uint32_t *len2,int stream_id);
int sample_get_raw_pic(uint8_t **pic_ptr, uint32_t *len, int stream_id);
int sample_start_yuv_pic(int stream_id);
int sample_get_yuv_pic(uint8_t **pic_ptr, uint32_t *len, int stream_id);
int sample_sub_system_init(void);
int sample_system_init(void);
int sample_encoder_init(void);
int sample_system_quick_init(void);
int sample_system_mjpeg_init(void);
void sample_deinit(void);
int sample_system_vir_init(void);
int sample_system_vir_encoder_init();

int sample_get_chann_frame_rate(int chn_id);
int sample_set_chann_resolution(int chn_id, uint32_t width, uint32_t height);
int sample_get_chann_resolution(int chn_id, uint32_t *width, uint32_t *height);
int sample_set_chann_frame_rate_from_sensor(int chn_id, uint32_t fps);
int sample_set_chann_frame_rate(int chn_id, uint32_t fps);
int sample_set_chann_rc_mode(int chn_id, MMEncoderRcMode rcMode);
int sample_set_chann_bit_rate(int chn_id, uint32_t bitRate);
int sample_set_chann_vbr_max_bit_rate(int chn_id, uint32_t bitRate);
int sample_set_chann_ip_ratio(int chn_id, uint32_t ip_ratio);
int sample_set_chann_max_qp(int chn_id, uint32_t qp);
int sample_set_chann_min_qp(int chn_id, uint32_t qp);
int sample_set_rc_level(int chn_id, uint32_t level);
int sample_get_rc_level(int chn_id, uint32_t *level);

int sample_set_chann_quality_level(int chn_id, uint32_t qualityLvl);
int sample_set_jpeg_quality(int chn_id, uint32_t quality);
int sample_start_stream(int chn_id);
int sample_start_stream_frame_mode(int chn_id);
int sample_close_stream(int chn_id);
int sample_start_stream_from_yuv_src(int chn_id, uint8_t *yuv_src_base_addr);

int h264_bittrue_init(void);
void h264_stream_handle_task(void *param);
void h264_change_resolution_task(void *param);
void h264_change_fps_task(void *param);
void h264_change_bitrate_task(void *param);
void jpeg_stream_handle_task(void *param);
void jpeg_stream_handle_jlink_dump_task();

#endif /* __SAMPLE_COMMON_H__ */
