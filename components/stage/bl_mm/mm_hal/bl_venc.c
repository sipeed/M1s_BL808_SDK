#include <string.h>
#include <math.h>

#include <bl808_mmsys_misc.h>
#include <bl808_mjenc.h>
#include <bl808_h264.h>
#include <bl808_clkrst.h>

#include "bl_venc.h"

#define MAX_STREAM_NUM                     3
#define DEFAULT_IP_RATIO                   8
#define DEFAULT_MIN_QP                     1
#define DEFAULT_MAX_QP                     51
#define DEFUALT_NUM_UNITS_IN_TICK          1000

#define BITSIZE_ROUND_UP_TO_BYTESIZE(x)    (((x) + 7) >> 3)
#define REVERSE_BYTE_ORDER(x)              ((x >> 8) | ((x & 0xFF) << 8))

#define CFG_ROI_IBIT_RATIO_DEFAULT         (1024)
#define CFG_ROI_PBIT_RATIO_DEFAULT         (1024)
#define CFG_ROI_N2R_QP_DECR_DEFAULT        (0)
#define CFG_ROI_IQP_DECR_DEFAULT           (0)
#define CFG_ROI_PQP_DECR_DEFAULT           (0)
#define CFG_ROI_IBIT_OFST_DEFAULT          (0)
#define CFG_ROI_PBIT_OFST_DEFAULT          (0)
#define CFG_NROI_IBIT_OFST_DEFAULT         (0)
#define CFG_NROI_PBIT_OFST_DEFAULT         (0)

#define ROI_NUM_MAX                        8
#define VENC_GET_BIT(x,y)                  (((x) >> (y)) & 1)
#define MIN_MBX_WIDTH                      6
#define MIN_MBY_HEIGHT                     1
#define MIN_MBX_BOUND_DISTANCE             6
#define MULTI_ROI_DISTANCE                 6
#define ADDITIONAL_PREFETCH_BUFFER_SIZE    (1920 << 3) // used when both prefetc is on and deblock is on, size: width*8

#define MAIN_PROFILE_ZSTUF_PADDING_DEFAULT ENABLE
#define H264_BS_FULL_THRESHOLD_RATIO       0           //0-10, 7 means that threshold is 70% bs buffer size

#define JPEG_Q_TABLE_SIZE                  128
#define JPEG_Q_TABLE_BUF_INDEX_0           0
#define JPEG_Q_TABLE_BUF_INDEX_1           1

#define ZIGZAG_TRAVER_MATRIX_SIZE          8

#define BL_IS_BIT_SET(val, bit) (val & (1 << bit))

typedef enum {
    ZIGZAG_DIRECTION_R = 0,    // right
    ZIGZAG_DIRECTION_LD,       // left and down
    ZIGZAG_DIRECTION_D,        // down
    ZIGZAG_DIRECTION_RU,       // right and up
} ZIGZAG_DIRECTION;

typedef struct zigzag_element_info {
    uint32_t x;
    uint32_t y;
    uint32_t direction;
}zigzag_element_info_t;

typedef struct {
    bl_venc_alloc_cb alloc_cb;
    bl_venc_free_cb free_cb;
    bl_venc_frame_cb frame_cb;
    bl_venc_stop_cb stop_cb;
    void *userData;    
} VEnc_Handle_Cfg_Type;

typedef struct {
    uint16_t width;
    uint16_t height;
    BL_Fun_Type cref_en;
    BL_Fun_Type sw_mode;
    uint32_t ref_y_size;
    uint32_t ref_uv_size;
    uint32_t ref_yuv_size;
    uint8_t  bDropUntilNextIDR;
    H264_RC_Cfg_Type bitrate_cfg;
} bl_venc_config_t;

typedef struct {
    int yuv_frm_size;
	int cur_frm_cnt;
	int tot_byte_cnt;
    uint32_t free_byte;
    uint8_t *next_frame_start_addr;
} bl_venc_stream_obj_t;

typedef struct {
    uint8_t *buf_addr;
    uint32_t buf_size;
} bl_venc_buf_t;

typedef struct {
    uint8_t is_static;
    uint8_t iframe;
    uint8_t static_weight;
    uint8_t big_motion_weight;
    uint32_t intra;
} bl_venc_ana_info_t;


#pragma pack(1)
typedef struct {
    uint8_t part_1[0xFE];
    uint16_t height;
    uint16_t width;
    uint8_t part_2[0x1C8];
} JPEG_Header_Type;
#pragma pack()

static unsigned char const defaultQuantizers[JPEG_Q_TABLE_SIZE] = {
    // luma table:
    16, 11, 10, 16, 24, 40, 51, 61,
    12, 12, 14, 19, 26, 58, 60, 55,
    14, 13, 16, 24, 40, 57, 69, 56,
    14, 17, 22, 29, 51, 87, 80, 62,
    18, 22, 37, 56, 68, 109, 103, 77,
    24, 35, 55, 64, 81, 104, 113, 92,
    49, 64, 78, 87, 103, 121, 120, 101,
    72, 92, 95, 98, 112, 100, 103, 99,

    // chroma table:
    17, 18, 24, 47, 99, 99, 99, 99,
    18, 21, 26, 66, 99, 99, 99, 99,
    24, 26, 56, 99, 99, 99, 99, 99,
    47, 66, 99, 99, 99, 99, 99, 99,
    99, 99, 99, 99, 99, 99, 99, 99,
    99, 99, 99, 99, 99, 99, 99, 99,
    99, 99, 99, 99, 99, 99, 99, 99,
    99, 99, 99, 99, 99, 99, 99, 99,

};

static ATTR_SRAM_JPG_HDR_SECTION JPEG_Header_Type jpeg_header_yuv420 = {
    .part_1 = {
        0xFF, 0xD8, 
		0xFF, 0xDB, 0x00, 0x43, 0x00, 0x10, 0x0B, 0x0C, 0x0E, 0x0C, 
		0x0A, 0x10, 0x0E, 0x0D, 0x0E, 0x12, 0x11, 0x10, 0x13, 0x18, 
		0x28, 0x1A, 0x18, 0x16, 0x16, 0x18, 0x31, 0x23, 0x25, 0x1D, 
		0x28, 0x3A, 0x33, 0x3D, 0x3C, 0x39, 0x33, 0x38, 0x37, 0x40, 
		0x48, 0x5C, 0x4E, 0x40, 0x44, 0x57, 0x45, 0x37, 0x38, 0x50, 
		0x6D, 0x51, 0x57, 0x5F, 0x62, 0x67, 0x68, 0x67, 0x3E, 0x4D, 
		0x71, 0x79, 0x70, 0x64, 0x78, 0x5C, 0x65, 0x67, 0x63, 
		0xFF, 0xDB, 0x00, 0x43, 0x01, 0x11, 0x12, 0x12, 0x18, 0x15, 
		0x18, 0x2F, 0x1A, 0x1A, 0x2F, 0x63, 0x42, 0x38, 0x42, 0x63, 
		0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 
		0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 
		0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 
		0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 
		0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 
        0xFF, 0xE1, 0x00, 0x6B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0xFF, 0xC0, 0x00, 0x11, 0x08, 
	},
	.height = REVERSE_BYTE_ORDER(1080),
	.width = REVERSE_BYTE_ORDER(1920),
	.part_2 = {
	    0x03, 0x01, 0x22, 0x00, 0x02, 0x11, 0x01, 0x03, 0x11, 0x01, 
		0xFF, 0xC4, 0x00, 0x1F, 0x00, 0x00, 0x01, 0x05, 0x01, 0x01, 
		0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
		0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 
		0x09, 0x0A, 0x0B, 
		0xFF, 0xC4, 0x00, 0xB5, 0x10, 0x00, 0x02, 0x01, 0x03, 0x03, 
		0x02, 0x04, 0x03, 0x05, 0x05, 0x04, 0x04, 0x00, 0x00, 0x01, 
		0x7D, 0x01, 0x02, 0x03, 0x00, 0x04, 0x11, 0x05, 0x12, 0x21, 
		0x31, 0x41, 0x06, 0x13, 0x51, 0x61, 0x07, 0x22, 0x71, 0x14, 
		0x32, 0x81, 0x91, 0xA1, 0x08, 0x23, 0x42, 0xB1, 0xC1, 0x15, 
		0x52, 0xD1, 0xF0, 0x24, 0x33, 0x62, 0x72, 0x82, 0x09, 0x0A, 
		0x16, 0x17, 0x18, 0x19, 0x1A, 0x25, 0x26, 0x27, 0x28, 0x29, 
		0x2A, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x43, 0x44, 
		0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x53, 0x54, 0x55, 0x56, 
		0x57, 0x58, 0x59, 0x5A, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 
		0x69, 0x6A, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 
		0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x92, 0x93, 
		0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0xA2, 0xA3, 0xA4, 
		0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xB2, 0xB3, 0xB4, 0xB5, 
		0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 
		0xC7, 0xC8, 0xC9, 0xCA, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 
		0xD8, 0xD9, 0xDA, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 
		0xE8, 0xE9, 0xEA, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 
		0xF8, 0xF9, 0xFA,
		0xFF, 0xC4, 0x00, 0x1F, 0x01, 0x00, 0x03, 0x01, 0x01, 0x01,
		0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 
		0x09, 0x0A, 0x0B, 
		0xFF, 0xC4, 0x00, 0xB5, 0x11, 0x00, 0x02, 0x01, 0x02, 0x04, 
		0x04, 0x03, 0x04, 0x07, 0x05, 0x04, 0x04, 0x00, 0x01, 0x02, 
		0x77, 0x00, 0x01, 0x02, 0x03, 0x11, 0x04, 0x05, 0x21, 0x31, 
		0x06, 0x12, 0x41, 0x51, 0x07, 0x61, 0x71, 0x13, 0x22, 0x32, 
		0x81, 0x08, 0x14, 0x42, 0x91, 0xA1, 0xB1, 0xC1, 0x09, 0x23, 
		0x33, 0x52, 0xF0, 0x15, 0x62, 0x72, 0xD1, 0x0A, 0x16, 0x24, 
		0x34, 0xE1, 0x25, 0xF1, 0x17, 0x18, 0x19, 0x1A, 0x26, 0x27, 
		0x28, 0x29, 0x2A, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x43, 
		0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x53, 0x54, 0x55, 
		0x56, 0x57, 0x58, 0x59, 0x5A, 0x63, 0x64, 0x65, 0x66, 0x67, 
		0x68, 0x69, 0x6A, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 
		0x7A, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 
		0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0xA2, 
		0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xB2, 0xB3, 
		0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xC2, 0xC3, 0xC4, 
		0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xD2, 0xD3, 0xD4, 0xD5, 
		0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 
		0xE7, 0xE8, 0xE9, 0xEA, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 
	    0xF8, 0xF9, 0xFA, 
		0xFF, 0xDA, 0x00, 0x0C, 0x03, 0x01, 0x00, 0x02, 0x11, 0x03, 
	    0x11, 0x00, 0x3F, 0x00,
  },
};

static const uint8_t JFIF_EOI[] = {0xFF, 0xD9};


static bl_venc_buf_t bs_buf[MAX_STREAM_NUM];
#if NEW_REF_FRM_CFG_API
static bl_venc_buf_t ref_buf[MAX_STREAM_NUM][3];
#else
static bl_venc_buf_t ref_buf[MAX_STREAM_NUM];
#endif
static bl_venc_buf_t prefetch_buf[MAX_STREAM_NUM];
static uint8_t *g_deblock_buf = 0x3f000000; // Todo: make auto switch to NULL if direct link is used

static uint32_t g_pfch_buf_start = 0;

static VEnc_Handle_Cfg_Type VEnc_Handl_Cfg[MAX_STREAM_NUM];
static bl_venc_config_t venc_config[MAX_STREAM_NUM];
static int is_buffer_alloc[MAX_STREAM_NUM];
static bl_venc_stream_obj_t venc_stream[MAX_STREAM_NUM];

static int jpeg_stream_id;

static bl_venc_ana_info_t last_reg = {0};

#define STREAM_OBJ(id)   (bl_venc_stream_obj_t *)&(venc_stream[id])

int bl_venc_set_jpeg_Qtable(int num, uint16_t *table);

static void set_value_with_byte_by_byte(uint16_t *addr, uint16_t value)
{
    *((uint8_t*)addr) = value & 0xFF;
    *((uint8_t*)addr + 1) = (value >> 8) & 0xFF;
}

static void get_mbs_num_per_frame(int width, int height, int *mbs_num)
{

    int ixsize = width;
    int iysize = height;
    int xsize;
    int ysize;

    // Round picture height and width up to the nearest multiple of 16
    if (!IS_MULTIPULE_OF_16(ixsize))
      xsize = ((ixsize >> 4) + 1) << 4;
    else
      xsize = ixsize;

    if (!IS_MULTIPULE_OF_16(iysize))
      ysize = ((iysize >> 4) + 1) << 4;
    else
      ysize = iysize;

    *mbs_num = (xsize>>4) * (ysize>>4);

}

static void generate_h264_bitrate_cfg(bl_h264_config_t *cfg, H264_RC_Cfg_Type *core_cfg)
{
    int num_pframes = cfg->gop_size - 1;
    int bit_rate = cfg->bit_rate;
    int framerate_num = cfg->frame_rate_num;
    int framerate_den = cfg->frame_rate_den;

    //printf("\r\n");
    //printf("=========== h264_bitrate_cfg %d,%d,%d,  %d,%d, %d,%d, %d,%d \r\n",
    // cfg->enc_type, cfg->bitrate_mode, cfg->profile, cfg->width, cfg->height,
    // cfg->bit_rate, cfg->gop_size, cfg->frame_rate_num, cfg->frame_rate_den);
    //printf("=========== %d, %d,%d,  %d,%d,   %d\r\n",
    // cfg->init_qp, cfg->target_i_qp, cfg->target_p_qp, cfg->min_qp, cfg->max_qp, cfg->force_ip_ratio);

    int num_imb_bits;
    int num_pmb_bits;
    int target_i_qp = 26;
    int target_p_qp = 26;

    float mum_bits;
    float frame_rate;
    int num_mbs_per_frame;
    float iframe_rate;
    float pframe_rate;
    int ip_ratio = DEFAULT_IP_RATIO;
    int iframe_min_qp = DEFAULT_MIN_QP;
    int iframe_max_qp = DEFAULT_MAX_QP;
    int iqp_ofst = 0;

    CHECK_PARAM(bit_rate > 0);
    CHECK_PARAM((framerate_num > 0) && (framerate_den > 0));
    CHECK_PARAM(cfg->gop_size > 0);

    if ((cfg->bitrate_mode == BL_BITRATE_MODE_FIXQP) || (cfg->bitrate_mode == BL_BITRATE_MODE_VBR)) {
        ip_ratio = 4;
    } else {
        if (cfg->force_ip_ratio > 0)
            ip_ratio = cfg->force_ip_ratio;
        else
            ip_ratio = DEFAULT_IP_RATIO;
    }

    get_mbs_num_per_frame(cfg->width, cfg->height, &num_mbs_per_frame);

    frame_rate = (double) framerate_num / framerate_den;
    iframe_rate = frame_rate/(num_pframes + 1);
    pframe_rate = (num_pframes * frame_rate)/(num_pframes + 1);
    // calculate number pf bits per I and P macroblock
    mum_bits = (float)bit_rate/((float)num_mbs_per_frame*(ip_ratio*iframe_rate + pframe_rate));
    num_pmb_bits = (int)(mum_bits + 0.5);
    num_imb_bits = (int)(ip_ratio * mum_bits + 0.5);
    //printf("======ip_ratio %d, mum_bits:%f, num_imb_bits %d, num_pmb_bits %d, \r\n", ip_ratio, mum_bits, num_imb_bits, num_pmb_bits);

    /* Fix QP case */
    if (cfg->bitrate_mode == BL_BITRATE_MODE_FIXQP) {
        num_imb_bits = 0;
        num_pmb_bits = 0;
        target_i_qp = cfg->target_i_qp;
        target_p_qp = cfg->target_p_qp;
        iframe_min_qp = MAX(cfg->min_qp, DEFAULT_MIN_QP);
        iframe_max_qp = MIN(cfg->max_qp, DEFAULT_MAX_QP);
    /* VBR case */
    } else if (cfg->bitrate_mode == BL_BITRATE_MODE_VBR) {
        if (num_imb_bits < 100) {
            // calculate number pf bits per I and P macroblock
            mum_bits = (float)bit_rate / ((float)num_mbs_per_frame*(10 * iframe_rate + pframe_rate));
            num_pmb_bits = (int)(mum_bits + 0.5);
            num_imb_bits = (int)(10 * num_pmb_bits + 0.5);
            ip_ratio = 10;
        }
        else if (num_imb_bits < 140) {
            // calculate number pf bits per I and P macroblock
            mum_bits = (float)bit_rate / ((float)num_mbs_per_frame*(6 * iframe_rate + pframe_rate));
            num_pmb_bits = (int)(mum_bits + 0.5);
            num_imb_bits = (int)(6 * num_pmb_bits + 0.5);
            ip_ratio = 6;
        }
    
        // calculate initial Qp based on num_imb_bits
        if (num_imb_bits >= 250) {
            target_i_qp = 25;
            target_p_qp = target_i_qp + 4;
            iframe_min_qp = 19;
            iqp_ofst = -4;
        }
        else if (num_imb_bits >= 200) {
            target_i_qp = 30;
            target_p_qp = target_i_qp + 3;
            iframe_min_qp = 24;
            iqp_ofst = -3;
        }
        else if (num_imb_bits >= 150) {
            target_i_qp = 35;
            target_p_qp = target_i_qp;
            iframe_min_qp = 30;
            iqp_ofst = 0;
        }
        else if (num_imb_bits >= 120) {
            target_i_qp = 40;
            target_p_qp = target_i_qp;
            iframe_min_qp = 35;
            iqp_ofst = 0;
        }
        else if (num_imb_bits >= 100) {
            target_i_qp = 48;
            target_p_qp = target_i_qp;
            iframe_min_qp = 35;
            iqp_ofst = 0;
        }
        else {
            target_i_qp = 51;
            target_p_qp = target_i_qp;
            iframe_min_qp = 35;
            iqp_ofst = 0;
        }
    /* CBR */
    } else {
        /* tweak the ip ratio if imb is small */
        if (cfg->force_ip_ratio == 0) {
            if (num_imb_bits < 100) {
              // calculate number pf bits per I and P macroblock
              mum_bits = (float)bit_rate/((float)num_mbs_per_frame*(20*iframe_rate + pframe_rate));
              num_pmb_bits = (int)(mum_bits + 0.5);
              num_imb_bits = (int)(20 * num_pmb_bits + 0.5);
              ip_ratio = 20;
            }
            else if (num_imb_bits < 140) {
              // calculate number pf bits per I and P macroblock
              mum_bits = (float)bit_rate/((float)num_mbs_per_frame*(12*iframe_rate + pframe_rate));
              num_pmb_bits = (int)(mum_bits + 0.5);
              num_imb_bits = (int)(12 * num_pmb_bits + 0.5);
              ip_ratio = 12;
            }
        }

        // calculate initial Qp based on num_imb_bits
        if (num_imb_bits >= 250) {
          target_i_qp = 25;
          iframe_min_qp = 19;
        }
        else if (num_imb_bits >= 200) {
          target_i_qp = 30;
          iframe_min_qp = 24;
        }
        else if (num_imb_bits >= 150) {
          target_i_qp = 35;
          iframe_min_qp = 30;
        }
        else if (num_imb_bits >= 120) {
          target_i_qp = 40;
          iframe_min_qp = 35;
        }
        else if (num_imb_bits >= 100) {
          target_i_qp = 48;
          iframe_min_qp = 35;
        }
        else {
          target_i_qp = 51;//40
          iframe_min_qp = 35;
        }
        
        //printf("======a target_i_qp: %d, target_p_qp: %d =============== \r\n", target_i_qp, target_p_qp);
        //printf("======a iframe_min_qp: %d, iframe_max_qp: %d =============== \r\n", iframe_min_qp, iframe_max_qp);

        target_p_qp = target_i_qp;
        if (cfg->init_qp > 0) target_i_qp = cfg->init_qp;

        iframe_min_qp = MAX(iframe_min_qp, cfg->min_qp);
        iframe_max_qp = cfg->max_qp;
        if (target_i_qp < iframe_min_qp) target_i_qp = iframe_min_qp;
        if (target_i_qp > iframe_max_qp) target_i_qp = iframe_max_qp;

    }
    
    //printf("\r\n");
    //printf("====== cfg->init_qp: %d, cfg->min_qp: %d,cfg->max_qp: %d =============== \r\n", cfg->init_qp, cfg->min_qp, cfg->max_qp);
    //printf("====== target_i_qp: %d, target_p_qp: %d =============== \r\n", target_i_qp, target_p_qp);
    //printf("====== iframe_min_qp: %d, pframe_min_qp: %d =============== \r\n", iframe_min_qp, pframe_min_qp);
    //printf("====== iframe_max_qp: %d, pframe_max_qp: %d =============== \r\n", iframe_max_qp, pframe_max_qp);
    //printf("====== num_imb_bits: %d, num_pmb_bits: %d =============== \r\n", num_imb_bits, num_pmb_bits);
    //printf("====== iqp_ofst: %d, ip_ratio: %d =============== \r\n", iqp_ofst, ip_ratio);

    /* fill core config */
    core_cfg->target_i_qp = target_i_qp;
    core_cfg->target_p_qp = target_p_qp;
    core_cfg->iframe_min_qp = iframe_min_qp;
    core_cfg->iframe_max_qp = iframe_max_qp;
    core_cfg->num_imb_bits = num_imb_bits;
    core_cfg->num_pmb_bits = num_pmb_bits;
    core_cfg->iqp_ofst = iqp_ofst;
    core_cfg->ip_ratio = ip_ratio;
}

static void generate_h264_core_size_cfg(bl_h264_config_t *cfg, H264_Core_Size_Cfg_Type *coreSizeCfg)
{
    int ixsize = cfg->width;
    int iysize = cfg->height;

    int xsize;
    int ysize;

    int xsize32, ysize32;
    int lsize;
    int uvxsize32, uvysize32;
    int uvsize;

    int luvsize;

    CHECK_PARAM(ixsize > 0 && ixsize <= 1920);
    CHECK_PARAM(iysize > 0 && iysize <= 1600);

    // Round picture height and width up to the nearest multiple of 16
    if (!IS_MULTIPULE_OF_16(ixsize))
      xsize = ((ixsize >> 4) + 1) << 4;
    else
      xsize = ixsize;

    if (!IS_MULTIPULE_OF_16(iysize))
      ysize = ((iysize >> 4) + 1) << 4;
    else
      ysize = iysize;

    /* Calculate frame size */
    // Luma area
    xsize32 = (xsize>>5) + (xsize&0x1f ? 1 : 0);
    ysize32 = (ysize>>5) + (ysize&0x1f ? 1 : 0);
    lsize=xsize32*ysize32;

    //UV area
    xsize>>=1;
    ysize>>=1;

    uvxsize32 = (xsize>>5) + (xsize&0x1f ? 1 : 0);
    uvysize32 = (ysize>>5) + (ysize&0x1f ? 1 : 0);
    uvsize=uvxsize32*uvysize32;

    luvsize = lsize+2*uvsize;

    coreSizeCfg->ixsize = ixsize;
    coreSizeCfg->iysize = iysize;
    coreSizeCfg->xsize32 = xsize32;
    coreSizeCfg->ysize32 = ysize32;
    coreSizeCfg->uvxsize32 = uvxsize32;
    coreSizeCfg->uvysize32 = uvysize32;
    coreSizeCfg->lsize = lsize;
    coreSizeCfg->uvsize = uvsize;
    coreSizeCfg->luvsize = luvsize;
}

static int do_set_vui_timing_info(int stream_id, int framerate_num, int framerate_den, bool dynamic_update)
{
    int vui_num_units_in_tick = DEFUALT_NUM_UNITS_IN_TICK;
    int vui_time_scale;

    // These timing parameters correspond to the NTSC frame
    // rate of 29.97 FPS.
    //float vui_time_scale = 180000;
    //float vui_num_units_in_tick = 3003;

    vui_time_scale = 2 * framerate_num * vui_num_units_in_tick / framerate_den;
    H264_SetVUITimeScale(stream_id, vui_time_scale);
    H264_SetVUINumUnitsInTick(stream_id, vui_num_units_in_tick);

    if (dynamic_update) {
        H264_UpdateSPS(stream_id);
    }

    return 0;
}

static void do_handle_h264_frame_done(Stream_ID_Type id)
{
    bl_venc_stream_obj_t *stream_obj = STREAM_OBJ(id);
    venc_frame_desc_t frame_desc;
    uint32_t byte_cnt;
    uint8_t *frame_start_addr;
    uint32_t frame_size;
    uint8_t *frame_sec_half_start_addr;
    uint32_t frame_sec_half_size;
    uint8_t *next_frame_start_addr;
    uint32_t bs_buf_left_size;
    uint8_t *bs_buf_base_addr = bs_buf[id].buf_addr;

#if PRINT_FAST_CAP_TIMING
    printf("Frm %lu\r\n", xTaskGetTickCountFromISR());
#endif

#if (BL80X_HW_VER <= BL80X_HW_A0)
    uint32_t tot_byte_cnt;
    H264_RD_REG(id, tot_byte_cnt, VDO, TOTAL_BYTECOUNT);
    byte_cnt = tot_byte_cnt - stream_obj->tot_byte_cnt; 
#else
    BL_Sts_Type is_pframe;
    H264_RD_FRAME_BYTECOUNT_REG((uint32_t)id, &byte_cnt);
    H264_IsCurrentPFrame(id, &is_pframe);
    if (venc_config[id].bDropUntilNextIDR) {
        if (is_pframe == SET)
            return;
        else
            venc_config[id].bDropUntilNextIDR = 0;
    }

#endif

    frame_start_addr = stream_obj->next_frame_start_addr;

    if (0 == byte_cnt) {
        BL_LOGE("[HAL] [strm %d] byte_cnt is zero!!!\r\n", id);
    }

    BL_LOGD("[HAL] [STRM %d] frm_id %d, addr 0x%p, byte_cnt %d\r\n",
        id, stream_obj->cur_frm_cnt, frame_start_addr, byte_cnt);

    bs_buf_left_size = (bs_buf_base_addr + bs_buf[id].buf_size - frame_start_addr);

    /* check if encoder write pointer is rewinded */
    if (byte_cnt <= bs_buf_left_size) {
        frame_size = byte_cnt;
        frame_sec_half_start_addr = NULL;
        frame_sec_half_size = 0;
        next_frame_start_addr = frame_start_addr + frame_size;
    } else {
        frame_size = bs_buf_left_size;
        frame_sec_half_start_addr = bs_buf_base_addr;
        frame_sec_half_size = byte_cnt - bs_buf_left_size;
        next_frame_start_addr = bs_buf_base_addr + frame_sec_half_size;
    }

    frame_desc.stream_id = id;
    frame_desc.frame_id = stream_obj->cur_frm_cnt;
    frame_desc.frame_start_addr = frame_start_addr;
    frame_desc.frame_size = frame_size;
    frame_desc.frame_sec_half_start_addr = frame_sec_half_start_addr;
    frame_desc.frame_sec_half_size = frame_sec_half_size;

#if (BL80X_HW_VER <= BL80X_HW_A0)
    /* frame type is not able to be decided by A0 HW */
    frame_desc.frame_type = BL_H264_UNKNOWN_FRAME;
#else
    frame_desc.frame_type = (is_pframe == SET) ? BL_H264_P_FRAME : BL_H264_I_FRAME;
#endif

    stream_obj->cur_frm_cnt++;
#if (BL80X_HW_VER <= BL80X_HW_A0)
    stream_obj->tot_byte_cnt = tot_byte_cnt;
#endif
    stream_obj->next_frame_start_addr = next_frame_start_addr;

    if (VEnc_Handl_Cfg[id].frame_cb) {
        VEnc_Handl_Cfg[id].frame_cb(VEnc_Handl_Cfg[id].userData, &frame_desc, 0);
    }
}

static void do_handle_jpeg_frame_done(Stream_ID_Type id)
{
    bl_venc_stream_obj_t *stream_obj = STREAM_OBJ(id);
    venc_frame_desc_t frame_desc;
    uint32_t byte_cnt;
    uint8_t *frame_start_addr;
    uint32_t frame_size;
    uint8_t *frame_sec_half_start_addr;
    uint32_t frame_sec_half_size;
    uint32_t bs_buf_left_size;
    uint8_t *bs_buf_base_addr = bs_buf[id].buf_addr;

    MJENC_Get_Frame(&frame_start_addr, &byte_cnt);
    byte_cnt = BITSIZE_ROUND_UP_TO_BYTESIZE(byte_cnt);

    BL_LOGD("[HAL] [strm %d] frm_id %d, addr 0x%p, byte_cnt 0x%x (%d)\r\n",
        id, stream_obj->cur_frm_cnt, frame_start_addr, byte_cnt, byte_cnt);
    bs_buf_left_size = (bs_buf_base_addr + bs_buf[id].buf_size - frame_start_addr);

    /* check if encoder write pointer is rewinded */
    if (byte_cnt <= bs_buf_left_size) {
        frame_size = byte_cnt;
        frame_sec_half_start_addr = NULL;
        frame_sec_half_size = 0;
    } else {
        frame_size = bs_buf_left_size;
        frame_sec_half_start_addr = bs_buf_base_addr;
        frame_sec_half_size = byte_cnt - bs_buf_left_size;
    }

    frame_desc.stream_id = id;
    frame_desc.frame_id = stream_obj->cur_frm_cnt;
    frame_desc.frame_start_addr = frame_start_addr;
    frame_desc.frame_size = frame_size;
    frame_desc.frame_sec_half_start_addr = frame_sec_half_start_addr;
    frame_desc.frame_sec_half_size = frame_sec_half_size;

    stream_obj->cur_frm_cnt++;

    if (VEnc_Handl_Cfg[id].frame_cb) {
        VEnc_Handl_Cfg[id].frame_cb(VEnc_Handl_Cfg[id].userData, &frame_desc, 0);
    }

    /* pop one MJPEG frame */
    MJENC_PopStreamFifo();
}

static int do_handle_seq_done(Stream_ID_Type id)
{
    BL_LOGI("[HAL] [STRM %d] seq end!\r\n", id);
    if (VEnc_Handl_Cfg[id].stop_cb) {
        VEnc_Handl_Cfg[id].stop_cb(VEnc_Handl_Cfg[id].userData, (int)id);
        VEnc_Handl_Cfg[id].stop_cb = NULL;
    }

    return 0;
}

static void do_handle_h264_irq(void)
{
    uint32_t h264_int_status = 0;

    h264_int_status = H264_Get_Intterupt_Status();

    if (BL_IS_BIT_SET(h264_int_status, H264_M_OVERFLOW)) {
        venc_config[STREAM_0_ID].bDropUntilNextIDR = 1;
    }

    if (BL_IS_BIT_SET(h264_int_status, H264_S_OVERFLOW)) {
        venc_config[STREAM_1_ID].bDropUntilNextIDR = 1;
    }

    /* handle main stream */
    if (BL_IS_BIT_SET(h264_int_status, H264_M_FRM_DONE_INT)) {
        do_handle_h264_frame_done(STREAM_0_ID);
    }

    if (BL_IS_BIT_SET(h264_int_status, H264_M_SEQ_DONE_INT)) {
        do_handle_seq_done(STREAM_0_ID);
    }

    if (BL_IS_BIT_SET(h264_int_status, H264_M_BS_FULL_INT)) {
        BL_LOGI("[stream 0] BS full.\r\n");
    }

    /* handle second stream */
#if (BL80X_HW_VER >= BL80X_HW_B0)
    if (BL_IS_BIT_SET(h264_int_status, H264_S_FRM_DONE_INT)) {
        do_handle_h264_frame_done(STREAM_1_ID);
    }
    
    if (BL_IS_BIT_SET(h264_int_status, H264_S_SEQ_DONE_INT)) {
        do_handle_seq_done(STREAM_1_ID);
    }

    if (BL_IS_BIT_SET(h264_int_status, H264_S_BS_FULL_INT)) {
        BL_LOGI("[stream 1] BS full.\r\n");
    }
#endif
}

static void reset_stream_status(int stream_id)
{
    bl_venc_stream_obj_t *stream_obj = STREAM_OBJ(stream_id);
    
    stream_obj->tot_byte_cnt = 0;
    stream_obj->cur_frm_cnt = 0;
    stream_obj->next_frame_start_addr = bs_buf[stream_id].buf_addr;
}

int bl_venc_set_h264_sw_mode(int stream_id, BL_Fun_Type enable)
{
    venc_config[stream_id].sw_mode = enable;
    H264_SetSwMode(enable);

    return 0;
}

int bl_venc_set_h264_sramck_old(BL_Fun_Type state)
{
    H264_EnableSramckModeOld(state);

    return 0;
}

int bl_venc_set_h264_input_channel(int stream_id, uint8_t dsp2_chann_id)
{
    H264_Src_Chann_Cfg_Type src_chan;
    src_chan.y_src = (dsp2_chann_id << 1);
    src_chan.uv_src = (dsp2_chann_id << 1) + 1;
    H264_SetSrcChannel(stream_id, &src_chan);

    return 0;
}

int bl_venc_set_h264_FPS_on_the_fly(int stream_id, int framerate_num, int framerate_den)
{
    do_set_vui_timing_info(stream_id, framerate_num, framerate_den, true);

    return 0;
}

int bl_venc_set_h264_bitrate_on_the_fly(int stream_id, bl_h264_config_t *config)
{
    generate_h264_bitrate_cfg(config, &venc_config[stream_id].bitrate_cfg);
    H264_SetRateCtrlCfg(stream_id, &venc_config[stream_id].bitrate_cfg);
    H264_UpdateRC(stream_id);

    return 0;
}

int bl_venc_set_h264_target_i_qp_on_the_fly(int stream_id, int qp)
{
    H264_GetRateCtrlCfg(stream_id, &venc_config[stream_id].bitrate_cfg);
    venc_config[stream_id].bitrate_cfg.target_i_qp = qp;
    H264_SetRateCtrlCfg(stream_id, &venc_config[stream_id].bitrate_cfg);
    H264_UpdateRC(stream_id);

    return 0;
}

int bl_venc_set_h264_target_p_qp_on_the_fly(int stream_id, int qp)
{
    H264_GetRateCtrlCfg(stream_id, &venc_config[stream_id].bitrate_cfg);
    venc_config[stream_id].bitrate_cfg.target_p_qp = qp;
    H264_SetRateCtrlCfg(stream_id, &venc_config[stream_id].bitrate_cfg);
    H264_UpdateRC(stream_id);

    return 0;
}

int bl_venc_set_h264_max_qp_on_the_fly(int stream_id, int qp)
{
    H264_GetRateCtrlCfg(stream_id, &venc_config[stream_id].bitrate_cfg);
    venc_config[stream_id].bitrate_cfg.iframe_max_qp = qp;
    H264_SetRateCtrlCfg(stream_id, &venc_config[stream_id].bitrate_cfg);
    H264_UpdateRC(stream_id);

    return 0;
}

int bl_venc_set_h264_min_qp_on_the_fly(int stream_id, int qp)
{
    H264_GetRateCtrlCfg(stream_id, &venc_config[stream_id].bitrate_cfg);
    venc_config[stream_id].bitrate_cfg.iframe_min_qp = qp;
    H264_SetRateCtrlCfg(stream_id, &venc_config[stream_id].bitrate_cfg);
    H264_UpdateRC(stream_id);

    return 0;
}

int bl_venc_set_h264_gop_size_on_the_fly(int stream_id, int gopSize)
{
    H264_SetGOPSize(stream_id, gopSize);
    H264_UpdateRC(stream_id);

    return 0;
}

int bl_venc_set_h264_profile(int stream_id, int profile)
{
    if ((stream_id != 0) && (stream_id != 1)) {
        BL_LOGE("Param is illegal!! line:%d\r\n", __LINE__);
        return 1;
    }

    if ((profile != BL_H264_PROFILE_BASELINE) && (profile != BL_H264_PROFILE_MAIN)) {
        BL_LOGE("Param is illegal!! line:%d\r\n", __LINE__);
        return 1;
    }

    BL_LOGI("[H264][INFO] Profile_id:%d , 0 is baseline, 1 is main!\r\n", profile);
    H264_SetProfile(stream_id, profile);

    if (BL_H264_PROFILE_MAIN == profile) {
        H264_MainPddingConfig(stream_id, MAIN_PROFILE_ZSTUF_PADDING_DEFAULT);
    }

    return 0;
}

void bl_venc_set_qp(int stream_id, int target_i_qp, int target_p_qp)
{
    H264_SetRateCtrlQP(stream_id, target_i_qp, target_p_qp);
    H264_UpdateRC(stream_id);
}

void bl_venc_get_h264_rc_param(int stream_id, int *target_i_qp, int *target_p_qp, int *iframe_min_qp, int *ipratio, int *iqp_ofst)
{
    *target_i_qp = venc_config[stream_id].bitrate_cfg.target_i_qp;
    *target_p_qp = venc_config[stream_id].bitrate_cfg.target_p_qp;
    *iframe_min_qp = venc_config[stream_id].bitrate_cfg.iframe_min_qp;
    *ipratio = venc_config[stream_id].bitrate_cfg.ip_ratio;
    *iqp_ofst = venc_config[stream_id].bitrate_cfg.iqp_ofst;
}

int bl_venc_set_h264_config(int stream_id, bl_h264_config_t *config)
{
    BL_Fun_Type cref_en;
    H264_Core_Size_Cfg_Type coreSizeCfg;
    int ret = 0;

    cref_en = (config->enc_type == BL_H264_ENC_LOW_BANDW) ? ENABLE : DISABLE;

    BL_LOGD("[HAL] BL_ENC %d\r\n", cref_en);
    H264_Enable_CRef(stream_id, cref_en);
    H264_SetResolution(stream_id, config->width, config->height);

    /* update H264 encoder core registers */

    generate_h264_bitrate_cfg(config, &venc_config[stream_id].bitrate_cfg);
    generate_h264_core_size_cfg(config, &coreSizeCfg);

#if !BITTRUE_REGRESSION_TEST
    H264_SetRateCtrlCfg(stream_id, &venc_config[stream_id].bitrate_cfg);
    H264_SetCoreSizeCfg(stream_id, &coreSizeCfg);
    H264_SetGOPSize(stream_id, config->gop_size);

    H264_EnableDeblock(stream_id, (config->enc_type == BL_H264_ENC_LOW_BANDW) ?
        DISABLE : ENABLE);

    do_set_vui_timing_info(stream_id, config->frame_rate_num, config->frame_rate_den, false);
#endif

    ret = bl_venc_set_h264_profile(stream_id, config->profile);
    if (ret) {
        BL_LOGE("Config h264 profile fail!!! %s line:%d\r\n", __func__, __LINE__);
        return 1;
    }

    /* save the venc config info */
    venc_config[stream_id].width = config->width;
    venc_config[stream_id].height = config->height;
    venc_config[stream_id].cref_en = cref_en;
    venc_config[stream_id].bDropUntilNextIDR = 0;

    /* save the real yuv frame size */
    venc_config[stream_id].ref_y_size = (coreSizeCfg.lsize << 10);
    venc_config[stream_id].ref_uv_size = (coreSizeCfg.uvsize << 10);
    venc_config[stream_id].ref_yuv_size = (coreSizeCfg.luvsize << 10);

    return 0;
}

int bl_venc_get_h264_raw_imb_pmb_bits(int stream_id, uint32_t *imb_bits, uint32_t *pmb_bits)
{
    if (((stream_id != 0) && (stream_id != 1)) || (!imb_bits) || (!pmb_bits)) {
        BL_LOGE("Param is illegal!! line:%d\r\n", __LINE__);
        return 1;
    }

    *imb_bits = venc_config[stream_id].bitrate_cfg.num_imb_bits;
    *pmb_bits = venc_config[stream_id].bitrate_cfg.num_pmb_bits;

    return 0;
}

uint16_t bl_venc_get_h264_intra_mbcnt(int stream_id)
{
    return H264_GetIntraMBCnt(stream_id);
}

void bl_venc_get_h264_mv_scence_weight(int stream_id, int *static_weight_out, int *big_motion_weight_out)
{
    int iframe = 0;
    int cnt = 0;
    int is_static = 0;
    int avg_intra = 0;
    int curr_big_motion_weight= 0;
    int static_weight = 0;;
    int big_motion_weight = 0;

    H264_MB_Info_T mb_info;
    H264_GetMbInfo(stream_id, &mb_info);
    //BL_LOGI("========= absmv_sum %08d \tnzmv_mbcnt %08d \tintra_mbcnt %08d \r\n", 
    //    mb_info.absmv_sum, mb_info.nzmv_mbcnt, mb_info.intra_mbcnt);

    int block_num = (venc_config[stream_id].width + 8) / 16 * (venc_config[stream_id].height + 8) / 16;
    int cnt_thr = 50;//get by analyze
    int nzmv_thr = 15;//get by analyze
    int iir = 17;//1/15*255
    float resolution_rate = 0.01;
    float big_motion_low_rate = 0.3;//get by analyze
    float big_motion_high_rate = 0.7;//get by analyze
    
    int intra_mbcnt_thr = block_num * resolution_rate;
    int big_motion_block_low_thr = block_num * big_motion_low_rate;
    int big_motion_block_high_thr = block_num * big_motion_high_rate;
    
    
    if (mb_info.intra_mbcnt == block_num) iframe = 1;
    if (mb_info.nzmv_mbcnt != 0) cnt = mb_info.absmv_sum / mb_info.nzmv_mbcnt + 0.5;

    if (last_reg.iframe || iframe) {
        if (iframe == 1) {
            avg_intra = last_reg.intra;
        } else {
            avg_intra = mb_info.intra_mbcnt;
        }
    } else {
        avg_intra = (last_reg.intra + 3 * mb_info.intra_mbcnt + 2) / 4;
    }

    /* static scence */
    if (iframe == 1) {
        is_static = last_reg.is_static;
    } else if ((avg_intra < intra_mbcnt_thr) || ((cnt < cnt_thr) && (mb_info.nzmv_mbcnt < nzmv_thr))) {
        is_static = 1;
    }
    static_weight = (is_static * iir + last_reg.static_weight * (255 - iir) / 255);
    *static_weight_out = static_weight;
    //BL_LOGI("========= \tavg_intra_mbcnt %08d \tcnt %08d \tiframe %d \tis_static %d \tstatic_weights %d\r\n", 
    //    avg_intra, cnt, iframe, is_static, static_weight);

    /* big motion scence */
    if (avg_intra < big_motion_block_low_thr) {
        curr_big_motion_weight = 0;
    } else if (avg_intra > big_motion_block_high_thr) {
        curr_big_motion_weight = 255;
    } else {
        curr_big_motion_weight = (avg_intra - big_motion_block_low_thr) * 255 / (big_motion_block_high_thr - big_motion_block_low_thr);
    }
    big_motion_weight = (curr_big_motion_weight * iir + last_reg.big_motion_weight * (255 - iir)) / 255;
    *big_motion_weight_out = big_motion_weight;

    //BL_LOGI("========= \tavg_intra_mbcnt %08d \tlow_thr %d \thigh_thr %d \tcurrent_weight %d \tbig_motion_weight %d\r\n", 
    //    avg_intra, big_motion_block_low_thr, big_motion_block_high_thr, curr_big_motion_weight, *big_motion_weight_out);

    /* last register*/
    last_reg.is_static = is_static;
    last_reg.iframe = iframe;
    last_reg.static_weight = static_weight;
    last_reg.big_motion_weight = big_motion_weight;
    last_reg.intra = mb_info.intra_mbcnt;
}

int bl_venc_set_h264_input_buffer(int stream_id, bl_venc_input_buffer_t *input_buffer)
{
    uint16_t src_height;
    H264_SRC_BUF_CFG_S src_buf;

    uint16_t width = venc_config[stream_id].width;
    uint16_t height = venc_config[stream_id].height;

    /* check if y src frame size is multipule of half blk row size (16x16 blk for y) */
    if (input_buffer->y_frame_size % (width << 3)) {
        return -1;
    }

    /* check if uv src frame size is multipule of half blk row size (8x8 blk for uv) */
    if (input_buffer->uv_frame_size % (width << 2)) {
        return -1;
    }

    src_buf.yBufAddr = (uint32_t)input_buffer->y_frame_base_addr;
    src_buf.yBufSize = (uint32_t)input_buffer->y_frame_size;
    src_buf.uvBufAddr = (uint32_t)input_buffer->uv_frame_base_addr;
    src_buf.uvBufSize = (uint32_t)input_buffer->uv_frame_size;

    /* No need to roundup to multipule of 16 later */
    src_height = input_buffer->y_frame_size / width;
    H264_SetSrcFrameBuf(stream_id, &src_buf, src_height, height);
    H264_SetSrcBufCtlCfg(stream_id, (src_height / height), width*height);

    return 0;
}

int bl_venc_get_prebuffer_memory_room()
{
    uint32_t tmpVal;
    uint32_t size = 0;

    tmpVal = BL_RD_REG(MMSYS_MISC_BASE, MMSYS_MISC_VRAM_CTRL);
    tmpVal = BL_GET_REG_BITS_VAL(tmpVal, MMSYS_MISC_REG_PF_SRAM_REL);

	switch (tmpVal) {
        case MMSYS_REL_VRAM_0_PFH_192:
            size = 192 * 1024;
            break;
        case MMSYS_REL_VRAM_64_PFH_128:
            size = 128 * 1024;
            break;
        case MMSYS_REL_VRAM_128_PFH_64:
            size = 64 * 1024;
            break;
        case MMSYS_REL_VRAM_192_PFH_0:
            size = 0;
            break;
        default:
            BL_LOGE("Config prefetch buffer register fail!!\r\n");
            break;
    }

    return size;
}

int bl_venc_prefetch_buffer_init(int stream_id)
{
    uint16_t width = 0;
    bl_venc_buf_t *buf = NULL;
    uint32_t total_mem_size = 0, cur_mem_size = 0;

    if ((stream_id != 0) && (stream_id != 1)) {
        BL_LOGE("Param is illegal!! line:%d\r\n", __LINE__);
        return 1;
    }

    buf = &prefetch_buf[stream_id];
    if (!buf) {
        BL_LOGE("Null pointer!! line:%d\r\n", __LINE__);
        return 1;
    }

    width = venc_config[stream_id].width;
    if (!width) {
        BL_LOGE("Width is illegal!! width:%d line:%d\r\n", width, __LINE__);
        return 1;
    }

    total_mem_size = bl_venc_get_prebuffer_memory_room();
    if (!total_mem_size) {
        BL_LOGE("Prefetch buffer memory is nonexistent!! line:%d\r\n", __LINE__);
        return 1;
    }
    cur_mem_size = total_mem_size - g_pfch_buf_start;

    buf->buf_size = width * 80 + width * 20;
    /* Check prebuffer size */
    if (buf->buf_size > cur_mem_size) {
        BL_LOGE("Prefetch memory is not enough!! stream_id:%d need_size:%d cur_mem_size:%d\r\n",
                 stream_id, buf->buf_size, cur_mem_size);
        return 1;
    }

    buf->buf_addr = g_pfch_buf_start;
    g_pfch_buf_start += buf->buf_size;

    BL_LOGI("Stream_id:%d prebuffer:%p size:0x%x\r\n", stream_id, buf->buf_addr, buf->buf_size);
    H264_SetPrefetchBuffer(stream_id, buf->buf_addr, buf->buf_addr + width * 80);

    return 0;
}

void bl_venc_prefetch_buffer_deinit(int stream_id)
{
    bl_venc_buf_t *buf = NULL;

    if ((stream_id != 0) && (stream_id != 1)) {
        BL_LOGE("Param is illegal!! line:%d\r\n", __LINE__);
        return;
    }

    if (((H264_PREFETCH_MODE) && (0 == stream_id)) ||
        ((H264_SUB_PREFETCH_MODE) && (1 == stream_id))) {
        buf = &prefetch_buf[stream_id];
        if (!buf) {
            BL_LOGE("Null pointer!! line:%d\r\n", __LINE__);
            return;
        }

        g_pfch_buf_start -= buf->buf_size;

        buf->buf_addr = NULL;
        buf->buf_size = 0;
    }
}

int bl_venc_set_h264_bs_buf_full_threshold(int stream_id, int bs_size, int ratio)
{
    if ((stream_id != 0) && (stream_id != 1)) {
        BL_LOGE("Param is illegal!! line:%d\r\n", __LINE__);
        return 1;
    }

    if (ratio < 0 || ratio > 10) {
        BL_LOGE("Param is illegal!! line:%d\r\n", __LINE__);
        return 1;
    }

    H264_SetBitstreamBufThreshold(stream_id, (bs_size * ratio) / 10);

    return 0;
}

int bl_venc_set_h264_internal_buffer(int stream_id)
{
    bl_venc_buf_t *buf;

    bl_venc_alloc_cb alloc_cb = VEnc_Handl_Cfg[stream_id].alloc_cb;
    void *usr_data = VEnc_Handl_Cfg[stream_id].userData;
    uint16_t width = venc_config[stream_id].width;
    uint16_t height = venc_config[stream_id].height;
    uint8_t ret = 0;

    if (alloc_cb == NULL) {
        BL_ABORT();
    }

    if (!is_buffer_alloc[stream_id]) {
        /* config ref/cref frame buffer */
        /* buffer can hold double yuv420 frames + EXT_DATA 64Byte*(width/16) ? */
#if NEW_REF_FRM_CFG_API
        H264_REF_FRM_ADDR_S ref_frm_addr;

        /* Ref YUV buf 0 */
        buf = &ref_buf[stream_id][0];
        buf->buf_size = venc_config[stream_id].ref_yuv_size;
        BL_LOGI("Alloc ref 0 buffer\r\n");
        alloc_cb(usr_data, buf->buf_size, PSRAM_ID_FOR_REF_BUF, (void **)&buf->buf_addr);
        ref_frm_addr.ref_y0_base_addr = (uint32_t)buf->buf_addr;
        ref_frm_addr.ref_u0_base_addr = ref_frm_addr.ref_y0_base_addr + venc_config[stream_id].ref_y_size;
        ref_frm_addr.ref_v0_base_addr = ref_frm_addr.ref_u0_base_addr + venc_config[stream_id].ref_uv_size;

        /* Ref YUV buf 1 */
        buf = &ref_buf[stream_id][1];
        buf->buf_size = venc_config[stream_id].ref_yuv_size;
        BL_LOGI("Alloc ref 1 buffer\r\n");
        alloc_cb(usr_data, buf->buf_size, PSRAM_ID_FOR_REF_BUF, (void **)&buf->buf_addr);
        ref_frm_addr.ref_y1_base_addr = (uint32_t)buf->buf_addr;
        ref_frm_addr.ref_u1_base_addr = ref_frm_addr.ref_y1_base_addr + venc_config[stream_id].ref_y_size;
        ref_frm_addr.ref_v1_base_addr = ref_frm_addr.ref_u1_base_addr + venc_config[stream_id].ref_uv_size;

        /* EXT_DATA buf */
        buf = &ref_buf[stream_id][2];
        buf->buf_size = (width >> 4 << 6);
        BL_LOGI("Alloc ref 2 buffer\r\n");
        alloc_cb(usr_data, buf->buf_size, PSRAM_ID_FOR_REF_BUF, (void **)&buf->buf_addr);
        ref_frm_addr.ext_dat_base_addr = (uint32_t)buf->buf_addr;

        H264_SetRefFrmMemPlusExtData(stream_id, &ref_frm_addr);
#else
        buf = &ref_buf[stream_id];
        buf->buf_size = (venc_config[stream_id].ref_yuv_size << 1) + (width >> 4 << 6);
        BL_LOGI("Alloc ref buffer\r\n");
        alloc_cb(usr_data, buf->buf_size, PSRAM_ID_FOR_REF_BUF, (void **)&buf->buf_addr);
        H264_SetRefFrmMemPlusExtData(stream_id, (uint32_t)buf->buf_addr);
#endif

        if (((H264_PREFETCH_MODE) && (0 == stream_id)) ||
             ((H264_SUB_PREFETCH_MODE) && (1 == stream_id))) {
            /* config H264 prefetch buffer */
            BL_LOGI("Enable prefetch, stream_id:%d\r\n", stream_id);
            H264_SetPrefetchMode(stream_id, ENABLE);
            H264_SetPrefetchCfg(stream_id, BLK_CNT_16X16(height));

#if (H264_DISFILTER)
            H264_EnableDeblock(stream_id, DISABLE);
            BL_LOGI("[Stream%d] disable deblock\r\n", stream_id);
#else
            H264_EnableDeblock(stream_id, ENABLE);
            H264_SetLineBufferAddr((uint32_t)g_deblock_buf);
            BL_LOGI("[Stream%d] enable deblock, additional buf = 0x%x\r\n",
                stream_id, (uint32_t)g_deblock_buf);
#endif
            ret = bl_venc_prefetch_buffer_init(stream_id);
            if (ret) {
                BL_LOGE("Prefetch buffer init fail!! line:%d\r\n", __LINE__);
                return 1;
            }
        } else {
#if (H264_DISFILTER)
            H264_EnableDeblock(stream_id, DISABLE);
            BL_LOGI("[Stream%d] disable deblock\r\n", stream_id);
#else
            H264_EnableDeblock(stream_id, ENABLE);
            BL_LOGI("[Stream%d] enable deblock\r\n", stream_id);
#endif
        }


        /* config H264 bitstream buffer */
        buf = &bs_buf[stream_id];
        buf->buf_size = BS_BUF_SIZE;
        BL_LOGI("Alloc bitstream buffer\r\n");
        alloc_cb(usr_data, buf->buf_size, PSRAM_ID_FOR_BS_BUF, (void **)&buf->buf_addr);
        H264_SetBitstreamBuf(stream_id, (uint32_t)buf->buf_addr, buf->buf_size);
        ret = bl_venc_set_h264_bs_buf_full_threshold(stream_id, buf->buf_size, H264_BS_FULL_THRESHOLD_RATIO);
        if (ret) {
            BL_LOGE("[ERROR] Set h264 bs buf threshold fail!!!\r\n");
            return 1;
        }

        is_buffer_alloc[stream_id] = 1;
    }

    return 0;
}

int bl_venc_h264_frame_done(int stream_id, bl_h264_bs_buff_info_t *buf_info)
{
    uint32_t bs_buf_size = 0;
    uint32_t bs_produce_size  = 0, free_size = 0;

    if ((stream_id != 0) && (stream_id != 1)) {
        BL_LOGE("Param is illegal!! line:%d\r\n", __LINE__);
        return 1;
    }

    if (!buf_info) {
        BL_LOGE("NUll pointer!! %s line:%d\r\n", __func__, __LINE__);
        return 1;
    }

    bs_buf_size = bs_buf[stream_id].buf_size;
	venc_stream[stream_id].free_byte += buf_info->size + buf_info->sec_size;
    free_size = venc_stream[stream_id].free_byte;
	H264_GetBSTotalByte(stream_id, &bs_produce_size);
    //BL_LOGI("produce_size:0x%x, free_size:0x%0x bs_size:0x%0x\r\n", bs_produce_size, free_size, bs_buf_size);
//    if ((bs_produce_size - free_size) > bs_buf_size) {
//        BL_LOGW("[WARNING] H264 bitstream buffer full!!!\r\n");
//    }

    return 0;
}

int bl_venc_start_h264_enc(int stream_id)
{
    H264_StartEnc(stream_id, venc_config[stream_id].sw_mode);

    return 0;
}

int bl_venc_stop_h264_enc(int stream_id, bl_venc_stop_cb cb)
{
    VEnc_Handl_Cfg[stream_id].stop_cb = cb;
    H264_StopEnc(stream_id);

    return 0;
}

int bl_venc_start_h264_enc_session(int stream_id)
{
    BL_LOGI("[HAL] Start H264 new session\r\n");
    reset_stream_status(stream_id);
    H264_Reset_HW_Status(stream_id);

    return 0;
}

int bl_venc_stop_h264_enc_session(int stream_id)
{
    H264_DisableCoreEnc(stream_id);

    return 0;
}

int bl_venc_stop_recv_h264_pic(int stream_id)
{
    bl_venc_free_cb free_cb = VEnc_Handl_Cfg[stream_id].free_cb;
    void *usr_data = VEnc_Handl_Cfg[stream_id].userData;

    if (is_buffer_alloc[stream_id]) {
        
        if (free_cb == NULL) {
            BL_ABORT();
        }
#if NEW_REF_FRM_CFG_API
        free_cb(usr_data, ref_buf[stream_id][0].buf_addr);
        free_cb(usr_data, ref_buf[stream_id][1].buf_addr);
        free_cb(usr_data, ref_buf[stream_id][2].buf_addr);
#else
        free_cb(usr_data, ref_buf[stream_id].buf_addr);
#endif
        free_cb(usr_data, bs_buf[stream_id].buf_addr);

        bl_venc_prefetch_buffer_deinit(stream_id);
        is_buffer_alloc[stream_id] = 0;
    }

    return 0;
}

int bl_venc_set_jpeg_input_channel(int stream_id, uint8_t dsp2_chann_id)
{
    MJPEG_Src_Chann_Cfg_Type src_chan;
    src_chan.y_src = (dsp2_chann_id << 1);
    src_chan.uv_src = (dsp2_chann_id << 1) + 1;
    MJENC_SetSrcChannel(&src_chan);

    return 0;
}

int bl_venc_set_jpeg_config(int stream_id, bl_jpeg_config_t *config)
{
    MJPEG_Cfg_Type mjpeg_cfg;
    int ret = 0;

    mjpeg_cfg.width = config->width;
    mjpeg_cfg.height = config->height;

    MJENC_SetResolution(&mjpeg_cfg);

    /* Set jpeg Qtable */
    ret = bl_venc_jpeg_set_quality(config->quality);
    if (ret) {
        BL_LOGE("Set jpeg Qtable fail!! %s line:%d\r\n", __func__, __LINE__);
        return 1;
    }

    /* SRAM doesn't support unaligned access, so write in a byte-by-byte fashion */
    set_value_with_byte_by_byte(&jpeg_header_yuv420.width, REVERSE_BYTE_ORDER(config->width));
    set_value_with_byte_by_byte(&jpeg_header_yuv420.height, REVERSE_BYTE_ORDER(config->height));

    /* save the resolution info */
    venc_config[stream_id].width = config->width;
    venc_config[stream_id].height = config->height;

    return 0;
}

int compute_jpeg_Qtable(int quality, uint8_t *result_table)
{
    int factor = quality;
    int q = 0, val = 0, index = 0;

    if (!result_table) {
        BL_LOGE("Param is illegal!! %s line:%d\r\n", __func__, __LINE__);
        return 1;
    }

    if (quality < 1) {
        factor = 1;
    } else if (quality > 99) {
        factor = 99;
    }

    if (quality < 50) {
        q = 5000 / factor;
    } else {
        q = 200 - factor * 2;
    }

    for (index = 0; index < 128; index++) {
        val = (defaultQuantizers[index] * q + 50) / 100;
        if (val < 1) {
            val = 1;
        } else if (val > 255) {
            val = 255;
        }
        result_table[index] = val;
    }

    return 0;
}

int jpeg_zigzag_next_element(zigzag_element_info_t* element_info)
{
    int ret = 0;
    if (!element_info) {
        return 1;
    }

    switch (element_info->direction) {
    case ZIGZAG_DIRECTION_R:
        element_info->x++;
        if (0 == element_info->y) {
            element_info->direction = ZIGZAG_DIRECTION_LD;
        }
        else if ((ZIGZAG_TRAVER_MATRIX_SIZE - 1) == element_info->y) {
            element_info->direction = ZIGZAG_DIRECTION_RU;
        }
        else {
            ret = 1;
        }
        break;
    case ZIGZAG_DIRECTION_LD:
        element_info->x--;
        element_info->y++;
        if ((0 == element_info->x) && ((ZIGZAG_TRAVER_MATRIX_SIZE - 1) != element_info->y)) {
            element_info->direction = ZIGZAG_DIRECTION_D;
        }
        else if ((ZIGZAG_TRAVER_MATRIX_SIZE - 1) == element_info->y) {
            element_info->direction = ZIGZAG_DIRECTION_R;
        }
        break;
    case ZIGZAG_DIRECTION_D:
        element_info->y++;
        if (0 == element_info->x) {
            element_info->direction = ZIGZAG_DIRECTION_RU;
        }
        else if ((ZIGZAG_TRAVER_MATRIX_SIZE - 1) == element_info->x) {
            element_info->direction = ZIGZAG_DIRECTION_LD;
        }
        else {
            ret = 1;
        }
        break;
    case ZIGZAG_DIRECTION_RU:
        element_info->x++;
        element_info->y--;
        if (0 == element_info->y) {
            element_info->direction = ZIGZAG_DIRECTION_R;
        }
        else if ((ZIGZAG_TRAVER_MATRIX_SIZE - 1) == element_info->x) {
            element_info->direction = ZIGZAG_DIRECTION_D;
        }
        break;
    default:
        ret = 1;
        break;
    }

    return ret;
}

int jpeg_qtable_zigzag_traversal(uint8_t(*src)[ZIGZAG_TRAVER_MATRIX_SIZE], uint8_t(*dst)[ZIGZAG_TRAVER_MATRIX_SIZE])
{
    int i = 0, j = 0, ret = 0;
    zigzag_element_info_t element_info = { 0 };

    if (!src || !dst) {
        printf("Param is illegal!! %s line:%d\r\n", __func__, __LINE__);
        return 1;
    }

    element_info.x = 0;
    element_info.y = 0;
    element_info.direction = ZIGZAG_DIRECTION_R;

    for (i = 0; i < ZIGZAG_TRAVER_MATRIX_SIZE; i++) {
        for (j = 0; j < ZIGZAG_TRAVER_MATRIX_SIZE; j++) {
            // luma handle
            dst[i][j] = src[element_info.y][element_info.x];
            // chrome handle
            dst[i + 8][j] = src[element_info.y + 8][element_info.x];
            ret = jpeg_zigzag_next_element(&element_info);
            if (ret) {
                BL_LOGE("[ERROR]i:%d j:%d element.x= %d y:%d, dir:%d %s line:%d\r\n",
                         i, j,
                         element_info.x, element_info.y, element_info.direction,
                         __func__, __LINE__);
                break;
            }
        }
    }

    return ret;
}

int jpeg_Qtable_handle_for_hardware(uint8_t *src, uint16_t *dst)
{
    int index = 0;
    int rounds = 0, offset = 0;

    if (!src || !dst) {
        BL_LOGE("Param is illegal!! %s line:%d\r\n", __func__, __LINE__);
        return 1;
    }

    for(index = 0; index < 64; index++) {
        offset = index % 8;
        rounds = index / 8;
        dst[index] = round(((float)(1 << 11)) / src[8 * offset + rounds]);    // luma handle
        dst[index + 64] = round(((float)(1 << 11)) / src[8 * offset + rounds + 64]);    // chrome handle
    }

    return 0;
}

int bl_venc_jpeg_Qtable_handle(int index, int val1, int val2)
{
    if (index > (JPEG_Q_TABLE_SIZE/2)) {
        BL_LOGE("Param error!! input index:%d max_index:%d %s line:%d\r\n",
                index, JPEG_Q_TABLE_SIZE/2, __func__, __LINE__);
        return 1;
    }

    //BL_LOGI("index:%d val1:%d val2:%d\r\n", index, val1, val2);
    switch (index) {
        case 0:
            MJENC_SetQTableOffset0(val1, val2);
            break;
        case 1:
            MJENC_SetQTableOffset1(val1, val2);
            break;
        case 2:
            MJENC_SetQTableOffset2(val1, val2);
            break;
        case 3:
            MJENC_SetQTableOffset3(val1, val2);
            break;
        case 4:
            MJENC_SetQTableOffset4(val1, val2);
            break;
        case 5:
            MJENC_SetQTableOffset5(val1, val2);
            break;
        case 6:
            MJENC_SetQTableOffset6(val1, val2);
            break;
        case 7:
            MJENC_SetQTableOffset7(val1, val2);
            break;
        case 8:
           MJENC_SetQTableOffset8(val1, val2);
           break;
        case 9:
           MJENC_SetQTableOffset9(val1, val2);
           break;
        case 10:
           MJENC_SetQTableOffset10(val1, val2);
           break;
        case 11:
           MJENC_SetQTableOffset11(val1, val2);
           break;
        case 12:
           MJENC_SetQTableOffset12(val1, val2);
           break;
        case 13:
           MJENC_SetQTableOffset13(val1, val2);
           break;
        case 14:
           MJENC_SetQTableOffset14(val1, val2);
           break;
        case 15:
           MJENC_SetQTableOffset15(val1, val2);
           break;
        case 16:
           MJENC_SetQTableOffset16(val1, val2);
           break;
        case 17:
           MJENC_SetQTableOffset17(val1, val2);
           break;
        case 18:
           MJENC_SetQTableOffset18(val1, val2);
           break;
        case 19:
           MJENC_SetQTableOffset19(val1, val2);
           break;
        case 20:
           MJENC_SetQTableOffset20(val1, val2);
           break;
        case 21:
           MJENC_SetQTableOffset21(val1, val2);
           break;
        case 22:
           MJENC_SetQTableOffset22(val1, val2);
           break;
        case 23:
           MJENC_SetQTableOffset23(val1, val2);
           break;
        case 24:
           MJENC_SetQTableOffset24(val1, val2);
           break;
        case 25:
            MJENC_SetQTableOffset25(val1, val2);
            break;
        case 26:
            MJENC_SetQTableOffset26(val1, val2);
            break;
        case 27:
            MJENC_SetQTableOffset27(val1, val2);
            break;
        case 28:
            MJENC_SetQTableOffset28(val1, val2);
            break;
        case 29:
            MJENC_SetQTableOffset29(val1, val2);
            break;
        case 30:
            MJENC_SetQTableOffset30(val1, val2);
            break;
        case 31:
            MJENC_SetQTableOffset31(val1, val2);
            break;
        case 32:
            MJENC_SetQTableOffset32(val1, val2);
            break;
        case 33:
            MJENC_SetQTableOffset33(val1, val2);
            break;
        case 34:
            MJENC_SetQTableOffset34(val1, val2);
            break;
        case 35:
            MJENC_SetQTableOffset35(val1, val2);
            break;
        case 36:
            MJENC_SetQTableOffset36(val1, val2);
            break;
        case 37:
            MJENC_SetQTableOffset37(val1, val2);
            break;
        case 38:
            MJENC_SetQTableOffset38(val1, val2);
            break;
        case 39:
            MJENC_SetQTableOffset39(val1, val2);
            break;
        case 40:
            MJENC_SetQTableOffset40(val1, val2);
            break;
        case 41:
            MJENC_SetQTableOffset41(val1, val2);
            break;
        case 42:
            MJENC_SetQTableOffset42(val1, val2);
            break;
        case 43:
            MJENC_SetQTableOffset43(val1, val2);
            break;
        case 44:
            MJENC_SetQTableOffset44(val1, val2);
            break;
        case 45:
            MJENC_SetQTableOffset45(val1, val2);
            break;
        case 46:
            MJENC_SetQTableOffset46(val1, val2);
            break;
        case 47:
            MJENC_SetQTableOffset47(val1, val2);
            break;
        case 48:
            MJENC_SetQTableOffset48(val1, val2);
            break;
        case 49:
            MJENC_SetQTableOffset49(val1, val2);
            break;
        case 50:
            MJENC_SetQTableOffset50(val1, val2);
            break;
        case 51:
            MJENC_SetQTableOffset51(val1, val2);
            break;
        case 52:
            MJENC_SetQTableOffset52(val1, val2);
            break;
        case 53:
            MJENC_SetQTableOffset53(val1, val2);
            break;
        case 54:
            MJENC_SetQTableOffset54(val1, val2);
            break;
        case 55:
            MJENC_SetQTableOffset55(val1, val2);
            break;
        case 56:
            MJENC_SetQTableOffset56(val1, val2);
            break;
        case 57:
            MJENC_SetQTableOffset57(val1, val2);
            break;
        case 58:
            MJENC_SetQTableOffset58(val1, val2);
            break;
        case 59:
            MJENC_SetQTableOffset59(val1, val2);
            break;
        case 60:
            MJENC_SetQTableOffset60(val1, val2);
            break;
        case 61:
            MJENC_SetQTableOffset61(val1, val2);
            break;
        case 62:
            MJENC_SetQTableOffset62(val1, val2);
            break;
        case 63:
            MJENC_SetQTableOffset63(val1, val2);
            break;
    }

    return 0;
}

int bl_venc_set_jpeg_Qtable(int num, uint16_t *table)
{
    int index = 0;
    int ret = 0;

    if ((num > JPEG_Q_TABLE_SIZE) || (!table)) {
        BL_LOGE("Param is illegal!! %s line:%d\r\n", __func__, __LINE__);
        return 1;
    }

    for (index = 0; index < (JPEG_Q_TABLE_SIZE/2); index ++) {
        ret = bl_venc_jpeg_Qtable_handle(index, table[2*index], table[2*index + 1]);
        if (ret) {
            BL_LOGE("Set Qtable fail!! %s line:%d\r\n", __func__, __LINE__);
            return 1;
        }
    }

    //BL_LOGI("%s line:%d Current qtable buffer index:%d", __func__, __LINE__, MJENC_GetQTableCurrentBufIndex());

    MJENC_EnableQTable();
    return 0;
}

int bl_set_jpeg_header_qtable(uint8_t* zigzag_qtable)
{
    int i = 0;

    if (!zigzag_qtable) {
        return 1;
    }

    for (i = 0; i < 64; i++) {
        jpeg_header_yuv420.part_1[7 + i] = zigzag_qtable[i];
        jpeg_header_yuv420.part_1[7 + 64 + 5 + i] = zigzag_qtable[i + 64];
    }

    return 0;
}

int bl_venc_jpeg_set_quality(int quality)
{
    uint8_t *result_table = NULL, *zigzag_table = NULL;
    uint16_t *hw_qtable = NULL;
    int ret = 0;

    BL_LOGI("Set jpeg quality, quality_val:%d\r\n", quality);

    result_table = pvPortMalloc(JPEG_Q_TABLE_SIZE * sizeof(uint8_t));
    if (!result_table) {
        BL_LOGE("[ERROR] Malloc fail!! %s line:%d\r\n", __func__, __LINE__);
        return 1;
    }

    zigzag_table = pvPortMalloc(JPEG_Q_TABLE_SIZE * sizeof(uint8_t));
    if (!zigzag_table) {
        vPortFree(result_table);
        BL_LOGE("[ERROR] Malloc fail!! %s line:%d\r\n", __func__, __LINE__);
        return 1;
    }

    hw_qtable = pvPortMalloc(JPEG_Q_TABLE_SIZE * sizeof(uint16_t));
    if (!hw_qtable) {
        vPortFree(result_table);
		vPortFree(zigzag_table);
        BL_LOGE("[ERROR] Malloc fail!! %s line:%d\r\n", __func__, __LINE__);
        return 1;
    }

    ret = compute_jpeg_Qtable(quality, result_table);
    if (ret) {
        BL_LOGE("[ERROR] Compute qtable fail!! %s line:%d\r\n", __func__, __LINE__);
        goto fail;
    }

    // Handle jpeg header qtable
    ret = jpeg_qtable_zigzag_traversal((uint8_t(*)[ZIGZAG_TRAVER_MATRIX_SIZE])result_table,
                                       (uint8_t(*)[ZIGZAG_TRAVER_MATRIX_SIZE])zigzag_table);
    if (ret) {
        BL_LOGE("[ERROR] Compute qtable fail!! %s line:%d\r\n", __func__, __LINE__);
        goto fail;
    }

    ret = bl_set_jpeg_header_qtable(zigzag_table);
    if (ret) {
        BL_LOGE("[ERROR] Set qtable in jpeg header fail!! %s line:%d\r\n", __func__, __LINE__);
        goto fail;
    }
    // Config qtable for jpeg encoder
    ret = jpeg_Qtable_handle_for_hardware(result_table, hw_qtable);
    if (ret) {
        BL_LOGE("[ERROR] Handle qtable for HW fail!! %s line:%d\r\n", __func__, __LINE__);
        goto fail;
    }

    ret = bl_venc_set_jpeg_Qtable(JPEG_Q_TABLE_SIZE, hw_qtable);
    if (ret) {
        BL_LOGE("[ERROR] Handle qtable for HW fail!! %s line:%d\r\n", __func__, __LINE__);
        goto fail;
    }

fail:
    vPortFree(result_table);
    vPortFree(zigzag_table);
	vPortFree(hw_qtable);

    return ret;
}

int bl_venc_get_jpeg_Qtable(int *table, int *size)
{
    if (!table || !size) {
        BL_LOGE("Param is illegal!! %s line:%d\r\n", __func__, __LINE__);
        return 1;
    }

    *table = defaultQuantizers;
    *size = JPEG_Q_TABLE_SIZE;

    return 0;
}

int bl_venc_start_jpeg_enc(int stream_id, bl_venc_input_buffer_t *input_buffer)
{
    bl_venc_buf_t *buf;
    bl_venc_alloc_cb alloc_cb = VEnc_Handl_Cfg[stream_id].alloc_cb;
    void *usr_data = VEnc_Handl_Cfg[stream_id].userData;
    uint16_t width = venc_config[stream_id].width;

    /* check if y src frame size is multipule of half blk row size (16x16 blk) */
    if (input_buffer->y_frame_size % (width << 3)) {
        return -1;
    }

    /* check if uv src frame size is multipule of half blk row size (8x8 blk) */
    if (input_buffer->uv_frame_size % (width << 2)) {
        return -1;
    }

    MJENC_SetSrcBuf_Y((uint32_t)input_buffer->y_frame_base_addr,
        BLK_CNT_16X16(input_buffer->y_frame_size / width));

    MJENC_SetSrcBuf_UV((uint32_t)input_buffer->uv_frame_base_addr,
        BLK_CNT_8X8(input_buffer->uv_frame_size / width));

    /* config JPEG stream buffer */
    buf = &bs_buf[stream_id];
    buf->buf_size = BS_BUF_SIZE;
    BL_LOGI("Alloc bitstream buffer\r\n");
    alloc_cb(usr_data, buf->buf_size, PSRAM_ID_FOR_BS_BUF, (void **)&buf->buf_addr);
    MJENC_SetBitstreamBuf((uint32_t)buf->buf_addr, buf->buf_size);

    //vTaskDelay(100);    /* TODO: delay starting MJPEG encoder to avoid YUV load error (wr_over_rd) */
#if (MJPG_AUTO_HEADER)
    csi_dcache_clean_range(&jpeg_header_yuv420, sizeof(jpeg_header_yuv420));
#endif
    MJENC_StartEnc(MJPEG_ENC_AUTO_MODE);

    jpeg_stream_id = stream_id;
    return 0;
}

int bl_venc_stop_jpeg_enc(int stream_id, bl_venc_stop_cb cb)
{
    VEnc_Handl_Cfg[stream_id].stop_cb = cb;
    MJENC_StopEnc();

    return 0;
}

int bl_venc_stop_recv_jpeg_pic(int stream_id)
{
    bl_venc_free_cb free_cb = VEnc_Handl_Cfg[stream_id].free_cb;
    void *usr_data = VEnc_Handl_Cfg[stream_id].userData;

    if (free_cb == NULL) {
        BL_ABORT();
    }
    free_cb(usr_data, bs_buf[stream_id].buf_addr);

    return 0;
}

int bl_venc_get_JFIF_header(uint8_t **addr, uint32_t *size)
{
    *addr = (uint8_t *)&jpeg_header_yuv420;
    *size = sizeof(jpeg_header_yuv420);

    return 0;
}

int bl_venc_get_JFIF_tail(uint8_t **addr, uint32_t *size)
{
    *addr = (uint8_t*)JFIF_EOI;
    *size = sizeof(JFIF_EOI);

    return 0;
}

int bl_venc_init(void)
{
    CLKRST_H264_ENC_CLK_Sel(2, 0); // select 320M clock

    H264_Init();

    Interrupt_Handler_Register(H264_FRAME_DONE_IRQn, H264_FRAME_DONE_IRQHandler);
    Interrupt_Handler_Register(H264_SEQ_DONE_IRQn, H264_SEQ_DONE_IRQHandler);
    Interrupt_Handler_Register(H264_BS_FULL_IRQn, H264_BS_FULL_IRQHandler);
    System_NVIC_SetPriority(H264_FRAME_DONE_IRQn, 7, 1);
    System_NVIC_SetPriority(H264_SEQ_DONE_IRQn, 7, 1);
    System_NVIC_SetPriority(H264_BS_FULL_IRQn, 7, 1);
    CPU_Interrupt_Enable(H264_FRAME_DONE_IRQn);
    CPU_Interrupt_Enable(H264_SEQ_DONE_IRQn);
    CPU_Interrupt_Enable(H264_BS_FULL_IRQn);
    H264_SetDefaultCoreCfg(STREAM_0_ID);
    H264_EnableSPSOnEachGOP(STREAM_0_ID, ENABLE);

#if (BL80X_HW_VER >= BL80X_HW_B0)
    Interrupt_Handler_Register(H264_S_FRAME_DONE_IRQn, H264_S_FRAME_DONE_IRQHandler);
    Interrupt_Handler_Register(H264_S_SEQ_DONE_IRQn, H264_S_SEQ_DONE_IRQHandler);
    Interrupt_Handler_Register(H264_S_BS_FULL_IRQn, H264_S_BS_FULL_IRQHandler);
    System_NVIC_SetPriority(H264_S_FRAME_DONE_IRQn, 7, 1);
    System_NVIC_SetPriority(H264_S_SEQ_DONE_IRQn, 7, 1);
    System_NVIC_SetPriority(H264_S_BS_FULL_IRQn, 7, 1);
    CPU_Interrupt_Enable(H264_S_FRAME_DONE_IRQn);
    CPU_Interrupt_Enable(H264_S_SEQ_DONE_IRQn);
    CPU_Interrupt_Enable(H264_S_BS_FULL_IRQn);
    H264_SetDefaultCoreCfg(STREAM_1_ID);
    H264_EnableSPSOnEachGOP(STREAM_1_ID, ENABLE);
#endif

#if (H264_DISFILTER == 0)
    /* Prepare deblock buffer when deblock on */
    if (g_deblock_buf == NULL)
        g_deblock_buf = (uint8_t *)BL_MallocDMA(PSRAM_ID_FOR_BS_BUF, ADDITIONAL_PREFETCH_BUFFER_SIZE);
#endif

    MJENC_Init();
    MJENC_SetHeaderSize(sizeof(jpeg_header_yuv420));

    Interrupt_Handler_Register(MJPEG_IRQn, MJENC_IRQHandler);
    System_NVIC_SetPriority(MJPEG_IRQn, 7, 1);
    CPU_Interrupt_Enable(MJPEG_IRQn);

    return 0;
}

void H264_FRAME_DONE_IRQHandler(void)
{
    do_handle_h264_irq();
}

void H264_S_FRAME_DONE_IRQHandler(void)
{
    do_handle_h264_irq();
}

void H264_SEQ_DONE_IRQHandler(void)
{
    do_handle_h264_irq();
}

void H264_S_SEQ_DONE_IRQHandler(void)
{
    do_handle_h264_irq();
}

void H264_BS_FULL_IRQHandler(void)
{
    do_handle_h264_irq();
}

void H264_S_BS_FULL_IRQHandler(void)
{
    do_handle_h264_irq();
}

void MJENC_IRQHandler(void)
{
    int id = jpeg_stream_id;
    uint32_t mjenc_int_type;
    //BL_LOGI("[HAL] [JPEG] vld_cnt %d\r\n", BL_GET_REG_BITS_VAL(tmpVal, MJENC_FRAME_VALID_CNT));
    mjenc_int_type = MJENC_Get_Int_Status();

    if (BL_IS_BIT_SET(mjenc_int_type, MJPEG_ENC_INT_NORMAL)) {
        do_handle_jpeg_frame_done(id);
        BL_LOGD("MJPEG frame done.\r\n");
    }

    if (BL_IS_BIT_SET(mjenc_int_type, MJPEG_ENC_INT_CAM)) {
        BL_LOGE("YUV load error!\r\n");
        BL_ABORT();
    }

    if (BL_IS_BIT_SET(mjenc_int_type, MJPEG_ENC_INT_MEM)) {
        BL_LOGE("MJPEG memory full.\r\n");
        BL_ABORT();
    }

    if (BL_IS_BIT_SET(mjenc_int_type, MJPEG_ENC_INT_FRAME)) {
        BL_LOGE("MJPEG frames full.\r\n");
    }

    if (BL_IS_BIT_SET(mjenc_int_type, MJPEG_ENC_INT_IDLE)) {
        do_handle_seq_done(id);
        BL_LOGI("MJPEG enter idle.\r\n");
    }
}

int bl_venc_set_callback(int stream_id,      bl_venc_alloc_cb alloc_cb, bl_venc_free_cb free_cb,
    bl_venc_frame_cb frame_cb, void *usrdata)
{
    VEnc_Handl_Cfg[stream_id].alloc_cb = alloc_cb;
    VEnc_Handl_Cfg[stream_id].free_cb = free_cb;
    VEnc_Handl_Cfg[stream_id].frame_cb = frame_cb;
    VEnc_Handl_Cfg[stream_id].userData = usrdata;

    return 0;
}

int bl_venc_sync_buffer(int stream_id)
{
    uint16_t y_src_height = 0, c_src_height = 0, width = 0;
    DVP2AXI_Port_Type y_port, uv_port;

    if ((stream_id != 0) && (stream_id != 1)) {
        BL_LOGE("Param is illegal!! line:%d\r\n", __LINE__);
        return 1;
    }

    H264_SetBufferSyncFlag(stream_id);
    y_src_height = H264_GetYSrcHeight(stream_id);
    c_src_height = H264_GetCSrcHeight(stream_id);
    width = H264_GetFrameWidth(stream_id);
    H264_SetBufferByteCnt(stream_id, y_src_height, c_src_height, width);

    if (0 == stream_id) {
        y_port = DVP2AXI_A;
        uv_port = DVP2AXI_B;
    } else {
        y_port = DVP2AXI_C;
        uv_port = DVP2AXI_D;
    }
    DVP2AXI_NoAlignBufferSync(y_port);
    DVP2AXI_NoAlignBufferSync(uv_port);
    return 0;
}

int bl_venc_get_roi_coordinate_based_index(uint32_t stream_id, uint32_t index, H264_ROI_Coordinate_Info_T *coordinate_info)
{
    int ret = 0;

    if (((stream_id != 0) && (stream_id != 1)) || (index >= ROI_NUM_MAX) || (!coordinate_info)) {
        BL_LOGE("Param is illegal!! line:%d\r\n", __LINE__);
        return 1;
    }

    switch (index) {
        case BL_H264_ROI_INDEX_0:
            H264_RoiGetRoi0Coordinate(stream_id, coordinate_info);
            break;
        case BL_H264_ROI_INDEX_1:
            H264_RoiGetRoi1Coordinate(stream_id, coordinate_info);
            break;
        case BL_H264_ROI_INDEX_2:
            H264_RoiGetRoi2Coordinate(stream_id, coordinate_info);
            break;
        case BL_H264_ROI_INDEX_3:
            H264_RoiGetRoi3Coordinate(stream_id, coordinate_info);
            break;
        case BL_H264_ROI_INDEX_4:
            H264_RoiGetRoi4Coordinate(stream_id, coordinate_info);
            break;
        case BL_H264_ROI_INDEX_5:
            H264_RoiGetRoi5Coordinate(stream_id, coordinate_info);
            break;
        case BL_H264_ROI_INDEX_6:
            H264_RoiGetRoi6Coordinate(stream_id, coordinate_info);
            break;
        case BL_H264_ROI_INDEX_7:
            H264_RoiGetRoi7Coordinate(stream_id, coordinate_info);
            break;
        default:
            BL_LOGE("Index is illegal!! %s line:%d\r\n", __func__, __LINE__);
            ret = 1;
            break;
    }

    BL_LOGI("%s line:%d roi_index:%u mbx_e:%u mbx_s:%u mby_e:%u mby_s:%u\r\n", __func__, __LINE__,
             index,
             coordinate_info->mbx_e,
             coordinate_info->mbx_s,
             coordinate_info->mby_e,
             coordinate_info->mby_s);

    return ret;
}

int bl_venc_set_roi_coordinate_based_index(uint32_t stream_id, uint32_t index, H264_ROI_Coordinate_Info_T *coordinate_info)
{
    int ret = 0;

    if (((stream_id != 0) && (stream_id != 1)) || (index >= ROI_NUM_MAX) || (!coordinate_info)) {
        BL_LOGE("Param is illegal!! line:%d\r\n", __LINE__);
        return 1;
    }

    switch (index) {
        case BL_H264_ROI_INDEX_0:
            H264_RoiSetRoi0Coordinate(stream_id, coordinate_info);
            break;
        case BL_H264_ROI_INDEX_1:
            H264_RoiSetRoi1Coordinate(stream_id, coordinate_info);
            break;
        case BL_H264_ROI_INDEX_2:
            H264_RoiSetRoi2Coordinate(stream_id, coordinate_info);
            break;
        case BL_H264_ROI_INDEX_3:
            H264_RoiSetRoi3Coordinate(stream_id, coordinate_info);
            break;
        case BL_H264_ROI_INDEX_4:
            H264_RoiSetRoi4Coordinate(stream_id, coordinate_info);
            break;
        case BL_H264_ROI_INDEX_5:
            H264_RoiSetRoi5Coordinate(stream_id, coordinate_info);
            break;
        case BL_H264_ROI_INDEX_6:
            H264_RoiSetRoi6Coordinate(stream_id, coordinate_info);
            break;
        case BL_H264_ROI_INDEX_7:
            H264_RoiSetRoi7Coordinate(stream_id, coordinate_info);
            break;
        default:
            BL_LOGE("Index is illegal!! %s line:%d\r\n", __func__, __LINE__);
            ret = 1;
            break;
    }

    BL_LOGI("%s line:%d roi_index:%u mbx_e:%u mbx_s:%u mby_e:%u mby_s:%u\r\n", __func__, __LINE__,
             index,
             coordinate_info->mbx_e,
             coordinate_info->mbx_s,
             coordinate_info->mby_e,
             coordinate_info->mby_s);

    return ret;
}

int bl_venc_roi_check_boundry(uint32_t stream_id, H264_ROI_Coordinate_Info_T *coordinate_info)
{
    uint32_t max_mb_x, max_mb_y;

    if (((stream_id != 0) && (stream_id != 1)) || (!coordinate_info))
        return 1;

    /* ROI to frame size boundary should > 5 */
    /* Check mbx_s, mby_s */
    if (coordinate_info->mbx_s < MIN_MBX_BOUND_DISTANCE || coordinate_info->mby_s < MIN_MBX_BOUND_DISTANCE) {
        BL_LOGE("[ROI] start position must be >= %d, mbx_s = %d, mby_s = %d\r\n",
                MIN_MBX_BOUND_DISTANCE,
                coordinate_info->mbx_s,
                coordinate_info->mby_s);
        return 1;
    }

    /* Check mbx_e, mby_e */
    max_mb_x = H264_GetFrameWidth(stream_id)/16 - MIN_MBX_BOUND_DISTANCE;
    max_mb_y = H264_GetFrameHeight(stream_id)/16 - MIN_MBX_BOUND_DISTANCE;
    if (coordinate_info->mbx_e > max_mb_x || coordinate_info->mby_e > max_mb_y) {
        BL_LOGE("[ROI] end position must be <= (%d, %d), mbx_s = %d, mby_s = %d\r\n",
                max_mb_x, max_mb_y,
                coordinate_info->mbx_s,
                coordinate_info->mby_s);
        return 1;
    }

    /* ROI itself width should > 5, height should >=1 */
    if (coordinate_info->mbx_s >= coordinate_info->mbx_e || (coordinate_info->mbx_e - coordinate_info->mbx_s < MIN_MBX_WIDTH)
        || coordinate_info->mby_s >= coordinate_info->mby_e || (coordinate_info->mby_e - coordinate_info->mby_s < MIN_MBY_HEIGHT)) {
        BL_LOGE("[ROI] width must > %d, height must > %d, mbx_s = %d, mby_s = %d, , mbx_e = %d, mby_e = %d\r\n",
                MIN_MBX_WIDTH, MIN_MBY_HEIGHT,
                coordinate_info->mbx_s, coordinate_info->mby_s, 
                coordinate_info->mbx_e, coordinate_info->mby_e);
        return 1;
    }

    return 0;
}

int bl_venc_roi_check_two_roi_distance(uint32_t mbx, uint32_t mbx_exist)
{
    uint32_t distance = 0;

    distance = (mbx > mbx_exist) ? (mbx - mbx_exist) : (mbx_exist - mbx);
    if (distance < MULTI_ROI_DISTANCE) {
        BL_LOGE("Multio roi check fail!! mb_s:%d, exist roi mbs_s:%d %s line:%d\r\n",
                 mbx,
                 mbx_exist,
                 __func__, __LINE__);
        return 1;
    }

    return 0;
}
int bl_venc_roi_check_limit_mulitple_rois(uint32_t stream_id, H264_ROI_Coordinate_Info_T *coordinate_info)
{
    uint8_t roi_en_val = 0;
    int ret = 0, index = 0;

    H264_ROI_Coordinate_Info_T coordinate_info_exist = {0};
    if (((stream_id != 0) && (stream_id != 1)) || (!coordinate_info))
        return 1;

    roi_en_val = H264_RoiGetEnPositonVal(stream_id);
    for (index = 0; index < ROI_NUM_MAX; index++) {
        if (VENC_GET_BIT(roi_en_val, index)) {
            ret = bl_venc_get_roi_coordinate_based_index(stream_id, index, &coordinate_info_exist);
            if (!ret) {
                /* Check mbx_s */
                ret = bl_venc_roi_check_two_roi_distance(coordinate_info->mbx_s, coordinate_info_exist.mbx_s);
                if (ret) {
                    BL_LOGE("Multio roi check mb_x fail!! Exist roi index:%d %s line:%d\r\n",
                             index,
                             __func__, __LINE__);
                    return 1;
                }

                /* Check mbx_e */
                ret = bl_venc_roi_check_two_roi_distance(coordinate_info->mbx_e, coordinate_info_exist.mbx_e);
                if (ret) {
                    BL_LOGE("Multio roi check mb_e fail!! Exist roi index:%d %s line:%d\r\n", 
                             index,
                             __func__, __LINE__);
					return 1;
                }
            }
        }
    }

    return 0;
}

int bl_venc_roi_set_coordinate(uint32_t stream_id, venc_roi_coordinate_info_t *roi_info)
{
    H264_ROI_Coordinate_Info_T coordinate_info = {0};
    int ret = 0;

    if (((stream_id != 0) && (stream_id != 1)) || (!roi_info)) {
        BL_LOGE("Param is illegal!! line:%d\r\n", __LINE__);
        return 1;
    }

    coordinate_info.mbx_s = roi_info->mbx_s;
    coordinate_info.mbx_e = roi_info->mbx_e;
    coordinate_info.mby_s = roi_info->mby_s;
    coordinate_info.mby_e = roi_info->mby_e;

    /* Check roi boundary */
    ret = bl_venc_roi_check_boundry(stream_id, &coordinate_info);
    if (ret) {
        BL_LOGE("Check roi boundry fail!! %s line:%d\r\n", __func__, __LINE__);
        return 1;
    }

    /* Check limit multi-roi */
    ret = bl_venc_roi_check_limit_mulitple_rois(stream_id, &coordinate_info);
    if (ret) {
        BL_LOGE("Check multi-roi fail!! %s line:%d\r\n", __func__, __LINE__);
        return 1;
    }

    /* Set coodinate */
    ret = bl_venc_set_roi_coordinate_based_index(stream_id, roi_info->index, &coordinate_info);
    if (ret) {
        BL_LOGE("Set coordinate fail!! %s line:%d\r\n", __func__, __LINE__);
        return 1;
    }

    return 0;
}

int bl_venc_set_roi_bit_ratio(uint32_t stream_id, uint32_t ibit_ratio, uint32_t pbit_ratio)
{
    H264_RoiSetIBitRatio(stream_id, ibit_ratio);
    H264_RoiSetPBitRatio(stream_id, pbit_ratio);
    return 0;
}
int bl_venc_set_roi_n2r_qp_decr(uint32_t stream_id, uint32_t qp)
{
    H264_RoiSetN2RQPDecr(stream_id, qp);
    return 0;
}
int bl_venc_set_roi_iqp_decr(uint32_t stream_id, uint32_t iqp, uint32_t pqp)
{
    H264_RoiSetIQPDecr(stream_id, iqp);
    H264_RoiSetPQPDecr(stream_id, pqp);
    return 0;
}
int bl_venc_set_roi_bit_ofst(uint32_t stream_id, uint32_t iofst, uint32_t pofst)
{
    H264_RoiSetIBitOfst(stream_id, iofst);
    H264_RoiSetPBitOfst(stream_id, pofst);
    return 0;
}
int bl_venc_set_nroi_bit_ofst(uint32_t stream_id, uint32_t iofst, uint32_t pofst)
{
    H264_NRoiSetIBitOfst(stream_id, iofst);
    H264_NRoiSetPBitOfst(stream_id, pofst);
    return 0;
}

int bl_venc_roi_reset(uint32_t stream_id)
{
    int ret = 1;

    if ((stream_id != 0) && (stream_id != 1)) {
        BL_LOGE("Param is illegal!! line:%d\r\n", __LINE__);
        return 1;
    }

    H264_RoiResetEnPositonVal(stream_id);

    /* Reset update */
    ret = bl_venc_roi_en_config(stream_id);
    if (ret) {
        BL_LOGE("Reset Roi fail!! line:%d\r\n", __LINE__);
        return 1;
    }

    return 0;
}

int bl_venc_roi_en_config(uint32_t stream_id)
{
    if ((stream_id != 0) && (stream_id != 1)) {
        BL_LOGE("Param is illegal!! line:%d\r\n", __LINE__);
        return 1;
    }

    H264_RoiEnableConfig(stream_id);

    return 0;
}

int bl_venc_set_3dnr(uint32_t stream_id, int level, int strength)
{
    if ((stream_id != 0) && (stream_id != 1)) {
        BL_LOGE("Param is illegal!! line:%d\r\n", __LINE__);
        return 1;
    }

    BL_LOGI("%s line:%d, Set 3DNR, level:%d strength:%d\r\n", __func__, __LINE__, level, strength);
    H264_NRSetVal(stream_id, level, strength);
    H264_NREnable(stream_id);

    return 0;
}
