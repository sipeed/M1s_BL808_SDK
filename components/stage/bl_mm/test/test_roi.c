#include "bl_venc.h"
#include "test_roi.h"
#include "bl808_osd_draw.h"
#include "bl808_dsp2_misc.h"


#define CFG_ROI_IBIT_RATIO_VAL       (2048)
#define CFG_ROI_PBIT_RATIO_VAL       (2048)
#define CFG_ROI_N2R_QP_DECR_VAL      (2)
#define CFG_ROI_IQP_DECR_VAL         (2)
#define CFG_ROI_PQP_DECR_VAL         (2)
#define CFG_ROI_IBIT_OFST_VAL        (0)
#define CFG_ROI_PBIT_OFST_VAL        (0)
#define CFG_NROI_IBIT_OFST_VAL       (0)
#define CFG_NROI_PBIT_OFST_VAL       (0)
static osd_draw_reg_t* g_osddraw = (osd_draw_reg_t*) (OSD_A_BASE + OSD_DRAW_LOW_OFFSET);
struct roi_rect_t {
    uint32_t mbx_s;
    uint32_t mbx_e;
    uint32_t mby_s;
    uint32_t mby_e;
};

static struct roi_rect_t g_roi_rects[BL_H264_ROI_INDEX_MAX];

int test_roi_runing_history_exist(int id, venc_roi_coordinate_info_t *roi_info)
{
    uint32_t stream_id = id;
    uint32_t width = 1920;
    uint32_t height = 1080;
    uint32_t roi_imb_bits = 0;
    uint32_t non_roi_imb_bits = 0;
    uint32_t total_mbs = 0;
    uint32_t ratio = 0;
    uint32_t pmb_bits = 0;
    int ret = 1;

    if (!roi_info) {
        BL_LOGE("Null pointer!!! line:%d\r\n", __LINE__);
        return 1;
    }

    ret = bl_venc_roi_set_coordinate(stream_id, roi_info);
    if (ret) {
        BL_LOGE("Set coordinate fail!! %s line:%d\r\n", __func__, __LINE__);
        return 1;
    }

    /* enlarge cfg_[i|p]bit_ratio */
    bl_venc_set_roi_bit_ratio(stream_id, CFG_ROI_IBIT_RATIO_VAL, CFG_ROI_PBIT_RATIO_VAL);
    /* enlarge cfg_n2r_qp_decr (2~4 in general) */
    bl_venc_set_roi_n2r_qp_decr(stream_id, CFG_ROI_N2R_QP_DECR_VAL);
    /* enlarge cfg_[i|p]qp_decr (2~4 in general) */
    bl_venc_set_roi_iqp_decr(stream_id, CFG_ROI_IQP_DECR_VAL, CFG_ROI_PQP_DECR_VAL);
    /* adjust cfg_roi_[i|p]bit_ofst and cfg_nroi_[i|p]bit_ofst if needed */
    bl_venc_set_roi_bit_ofst(stream_id, CFG_ROI_IBIT_OFST_VAL, CFG_ROI_PBIT_OFST_VAL);
    bl_venc_set_nroi_bit_ofst(stream_id, CFG_NROI_IBIT_OFST_VAL, CFG_NROI_PBIT_OFST_VAL);

    /* 4. Enable roi config */
    ret = bl_venc_roi_en_config(stream_id);
    if (ret) {
        BL_LOGE("Enable roi fail!! %s line:%d\r\n", __func__, __LINE__);
        return 1;
    }

    return 0;
}

void test_roi_set_rect(uint32_t idx, uint32_t start_x, uint32_t start_y, uint32_t end_x, uint32_t end_y)
{
    g_roi_rects[idx].mbx_s = start_x >> 4;
    g_roi_rects[idx].mbx_e = end_x >> 4;
    g_roi_rects[idx].mby_s = start_y >> 4;
    g_roi_rects[idx].mby_e = end_y >> 4;

}
static uint32_t g_object_colors[] = {
    OSD_COLOR_PINK, OSD_COLOR_BLUE, OSD_COLOR_PURPLE,
    OSD_COLOR_ORANGE, OSD_COLOR_DIMGRAY, OSD_COLOR_RED,
    OSD_COLOR_BLACK, OSD_COLOR_WHITE
};

static void test_roi_set(int stream_id, uint32_t roi_idx)
{

    venc_roi_coordinate_info_t roi_info = {0};
    osd_rectangle_t rect;
    uint32_t layer;

    roi_info.index = roi_idx;
    roi_info.mbx_s = g_roi_rects[roi_info.index].mbx_s;
    roi_info.mbx_e = g_roi_rects[roi_info.index].mbx_e;
    roi_info.mby_s = g_roi_rects[roi_info.index].mby_s;
    roi_info.mby_e = g_roi_rects[roi_info.index].mby_e;
    BL_LOGI("[ROI Test] index 0, (%d, %d) (%d, %d)\r\n",
        roi_info.mbx_s << 4, roi_info.mby_s << 4,
        roi_info.mbx_e << 4, roi_info.mby_e << 4);

    if (test_roi_runing_history_exist(stream_id, &roi_info)) {
        BL_LOGI("[ROI Test] fail!! %s line:%d\r\n", __func__, __LINE__);
        return;
    }
    rect.desc.pos.x.start = roi_info.mbx_s << 4;
    rect.desc.pos.x.end = roi_info.mbx_e << 4;
    rect.desc.pos.y.start = roi_info.mby_s << 4;
    rect.desc.pos.y.end = roi_info.mby_e << 4;

    rect.desc.attr.all = g_object_colors[roi_info.index] | 0x6;
    osd_draw_rectangle_onTop(g_osddraw, &rect, &layer);
}

int test_roi_running_main(int stream_id, int state)
{
    DSP2_Scaler_Set_Input(DSP2_SCALER_A, DSP2_SCALER_INPUT_OSD_A);
    DSP2_OSD_Set_Input(DSP2_OSD_A, DSP2_OSD_INPUT_DSP2_OUTPUT);

    bl_venc_roi_reset(stream_id);
    osd_draw_init(g_osddraw);

    BL_LOGI("[ROI Test] state: %d\r\n", state);
    switch (state) {
        case 0:
            BL_LOGI("[ROI Test] reset\r\n");
            break;
        case 1:
            test_roi_set(stream_id, BL_H264_ROI_INDEX_0);
            break;
        case 2:
            test_roi_set(stream_id, BL_H264_ROI_INDEX_1);
            break;
        case 3:
            test_roi_set(stream_id, BL_H264_ROI_INDEX_2);
            break;
        case 9:
            test_roi_set(stream_id, BL_H264_ROI_INDEX_0);
            test_roi_set(stream_id, BL_H264_ROI_INDEX_1);
            test_roi_set(stream_id, BL_H264_ROI_INDEX_2);
            break;

        default:
            BL_LOGI("[ROI Test] unexpected state\r\n");
            break;
    }

    return 0;
}

