#include <FreeRTOS.h>
#include <task.h>
#include <string.h>

#include <bl808.h>
#include <bl808_dsp2.h>
#include <bl808_clkrst.h>
#include <bl808_dsp2_misc.h>
#include <bl808_dvp2axi.h>
#include <bl808_dvp_tsrc.h>
#include <bl808_dsp2_axi_ctrl.h>
#include <bl808_dsp2_wdr.h>

#include "bl_dsp2.h"
#include "bl_img_utils.h"
#include "img_param.h"
#include <bl-api-osd.h>
#include "ae_algo.h"
#include "awb_algo.h"

#define PERFORMANCE_MONITOR     0

#define MAX_INPUT_WIDTH         1920
#define MAX_INPUT_HEIGHT        1200
#define MAX_CHANN_NUM           (4)
#define MAX_SCALER_NUM          (4)
#define MAX_DSP2_DUMP_PORT_NUM   (8)

#if FPGA_ULTRASCALE
#define DUMP_PORT(channID)              ((channID) << 1)
#define CHANN_ID(portID)                ((portID) >> 1)
#define ENC_SRC_PORT_Y(channID)         ((channID) << 1)
#define ENC_SRC_PORT_UV(channID)        (((channID) << 1) + 1)
#else
#define DUMP_PORT(channID)              (channID)
#define CHANN_ID(portID)                (portID)
#define ENC_SRC_PORT_Y(channID)         (channID)
#define ENC_SRC_PORT_UV(channID)        (channID)
#endif

#define DVP2AXI_ID(port)                ((DVP2AXI_Port_Type)(port))

typedef struct {
    dsp2_awb3_bucket_t bin[DSP2_AWB3_HIST_BIN_NUM_MAX];
} bl_dsp2_awb3_stats_hist_bin_t;

static DSP2_TG_Cfg_Type cfg_tg;

static BL_Img_Size_T res_scaler[MAX_SCALER_NUM];
static bl_dsp2_stats_ready_cb stats_ready_cb;
static bl_dsp2_frame_ready_cb frame_ready_cb[MAX_CHANN_NUM];

static DVP2AXI_Callback_Cfg_Type dvp2axi_cb;
static bool gFrameAutoPopEnable[MAX_DSP2_DUMP_PORT_NUM] = {0};
static BL_DSP2_DAY_NIGHT_MODE_T day_night_mode = BL_DAY_MODE;

static bl_dsp2_awb3_stats_hist_bin_t awb_hist_bin = {0};
static uint8_t* buf_addr_3dnr = NULL;

#if PERFORMANCE_MONITOR
#define FRM_CNT_FOR_ONE_STATS     100       /* 8 sec */
static int ae_intr_cnt = 0;
static TickType_t ae_intr_start_time = 0;
#endif /* PERFORMANCE_MONITOR */

#if 0
static DSP2_DVP2AXI_DATA_POLARITY_E input_frame_valid;
static DSP2_DVP2AXI_DATA_POLARITY_E get_frame_active(BL_DSP2_IMAGE_DUMP_SRC_T src)
{
    return (BL_IMAGE_DUMP_SRC_DSP2_INPUT == src) ? input_frame_valid : DVP2AXI_DATA_ACTIVE_HIGH;
}
#endif

static int set_scaler_cfg(DSP2_Scaler_Type scaler_type, BL_Img_Size_T *in_size, BL_Img_Size_T *out_size)
{
    DSP2_SCALER_CONFIG_S scaler_cfg;

    //if ((in_size->width != out_size->width) || (in_size->height != out_size->height)) {
        scaler_cfg.input = *in_size;
        scaler_cfg.output.width = out_size->width;
#if !ENCODE_1080P_SVGA
        scaler_cfg.output.height = out_size->height;
#else
        scaler_cfg.output.height = ENC_HEIGHT(out_size->height);
#endif
        DSP2_Scaler_Set_Cfg(scaler_type, &scaler_cfg);
        DSP2_Scaler_Set_State(scaler_type, ENABLE);
    //} else {
    //    DSP2_Scaler_Set_State(scaler_type, DISABLE);
    //}

    return 0;
}

static int dsp2_set_dump_port_src(uint32_t portID, BL_DSP2_IMAGE_DUMP_SRC_T src)
{
    DVP2AXI_Port_Type port = DVP2AXI_ID(portID);

    DSP2_DVP2AXI_Set_Src(port, (DVP2AXI_Src_Type)src);
    DVP2AXI_SetFrameActive(port, DVP2AXI_DATA_ACTIVE_HIGH);

    return 0;
}

static int dsp2_set_image_plane(uint32_t portID, BL_DSP2_IMAGE_PLANE_T plane)
{
    DVP2AXI_Port_Type port = DVP2AXI_ID(portID);
    DSP2_DVP2AXI_CFG_S cfg;

    switch (plane)
    {
        case IMAGE_PLANE_Y_ONLY:
        case IMAGE_PLANE_UV_ONLY:
        case IMAGE_PLANE_8BIT:
            cfg.bit_width = DVP2AXI_DATA_8_BIT;
            break;
        case IMAGE_PLANE_24_EXP_32BIT:
            cfg.bit_width = DVP2AXI_DATA_24_EXP_32BIT;
            break;
        case IMAGE_PLANE_YUV:
        case IMAGE_PLANE_16BIT:
        default:
            cfg.bit_width = DVP2AXI_DATA_16_BIT;
            break;

    }
    cfg.byte_sel = (IMAGE_PLANE_UV_ONLY == plane) ? DVP2AXI_SEL_HIGH_BYTE : DVP2AXI_SEL_LOW_BYTE;
    cfg.v_subsampl_enable = (IMAGE_PLANE_UV_ONLY == plane) ? ENABLE : DISABLE;

    DVP2AXI_Config(port, &cfg);
    return 0;
}

static int dsp2_enable_port(uint32_t portID, bl_dsp2_dump_cfg_t *dump_cfg)
{
    DVP2AXI_Port_Type port = DVP2AXI_ID(portID);

    /* for image dump case, frame size always equal to buffer size */

#if 0 // test crop && cnt exm
    DVP2AXI_Crop( port, 80, 1180, 20, 620);
    DVP2AXI_SetFrameSize(port, 1100*600*2);
    DVP2AXI_Valid_Cnt_Exm(DVP2AXI_ID(portID), ENABLE, 100, 100);
#else
    DVP2AXI_SetFrameSize(port, dump_cfg->frame_size);
#endif
    DVP2AXI_Valid_Cnt_Exm(DVP2AXI_ID(portID), dump_cfg->win.width, dump_cfg->win.height);
    DVP2AXI_MemConfig(port, (uint32_t)dump_cfg->buf_base_addr, dump_cfg->buf_size);
    DVP2AXI_Enable(port);

    return 0;
}

static int dsp2_resume_port(uint32_t portID)
{
    DVP2AXI_Port_Type port = DVP2AXI_ID(portID);

    DVP2AXI_Enable(port);

    return 0;
}


static int dsp2_disable_port(uint32_t portID)
{
    DVP2AXI_Port_Type port = DVP2AXI_ID(portID);

    DVP2AXI_Disable(port);

    while (SET == DVP2AXI_GetBusyStatus(port));

    return 0;
}

static void handle_port_data_ready(DVP2AXI_Port_Type port, void *userData)
{
    bl_dsp2_frame_desc_t yuv_frame;
    uint32_t frame_addr, frame_size;
    int chann_id = CHANN_ID(port);

    if (chann_id >= MAX_CHANN_NUM) {
        BL_ABORT();
    }

    DVP2AXI_Get_FrameBuffer(port, &frame_addr, &frame_size);

    /* pass out chann id so that we can share the frame_ready_cb for all channels */
    yuv_frame.chann_id = chann_id;
    yuv_frame.port = port;
    yuv_frame.frame_start_addr = (uint8_t*)frame_addr;
    yuv_frame.frame_size = frame_size;

    if (gFrameAutoPopEnable[port]) {
        DVP2AXI_FrameFifoPop(port);
    }

    BL_LOGD("port[%d] handle_port_data_ready\r\n", port);

    if (frame_ready_cb[chann_id]) {
        frame_ready_cb[chann_id](NULL, &yuv_frame);
    }
}

static void handle_port_fifo_ovfl(DVP2AXI_Port_Type port, void *userData)
{
    BL_LOGE("port[%d] FIFO overflow!\r\n", port);
    BL_ABORT();
}

static void handle_port_mem_ovwr(DVP2AXI_Port_Type port, void *userData)
{
    BL_LOGE("port[%d] mem over write callback!\r\n", port);
}

static void handle_port_frm_ovwr(DVP2AXI_Port_Type port, void *userData)
{
    // BL_LOGE("port[%d] frame over write!\r\n", port);
}

static void handle_vcnt_non_matching(DVP2AXI_Port_Type port, void *userData)
{
    BL_LOGE("port[%d] v count not matching!\r\n", port);
}

static void handle_hcnt_non_matching(DVP2AXI_Port_Type port, void *userData)
{
    BL_LOGE("port[%d] h count not matching!\r\n", port);
}

static int bl_dsp2_csi_ctrl_cfg(BL_DSP2_INPUT_MODE_E lane_mode)
{
    CSI_RX_LANE_NUM_E lane_num;
    CSI_CFG_S csi_cfg;

    if (lane_mode == DSP2_INPUT_MIPI_1LANE) {
        lane_num = CSI_RX_1_LANE;
    }
    else if (lane_mode == DSP2_INPUT_MIPI_2LANE) {
        lane_num = CSI_RX_2_LANE;
    }
    else {
        printf("DSP2 Input mode[%d] NOT support!\r\n", DSP2_INPUT_DVP);
        return -1;
    }

    csi_cfg.dvp_vc_num      = 0;
    csi_cfg.lane_num        = lane_num;
    csi_cfg.unpack_en       = ENABLE;
    csi_cfg.sync_sp_en      = ENABLE;
    csi_cfg.data_bit_inv_en = DISABLE;

    CSI_Init();
    CSI_Config(&csi_cfg);
    CSI_Set_State(ENABLE);
    return 0;
}

static void bl_dsp2_dvp2axi_init()
{
    DVP2AXI_Init(DVP2AXI_A);
    DVP2AXI_Init(DVP2AXI_B);
    DVP2AXI_Init(DVP2AXI_C);
    DVP2AXI_Init(DVP2AXI_D);
    DVP2AXI_Init(DVP2AXI_E);
    DVP2AXI_Init(DVP2AXI_F);
    DVP2AXI_Init(DVP2AXI_G);
    DVP2AXI_Init(DVP2AXI_H);

    dvp2axi_cb.DVP2AXI_CallBack_Data_Ready = handle_port_data_ready;
    dvp2axi_cb.DVP2AXI_CallBack_Mem_Ovwr   = handle_port_mem_ovwr;
    dvp2axi_cb.DVP2AXI_CallBack_Frm_Ovwr   = handle_port_frm_ovwr;
    dvp2axi_cb.DVP2AXI_CallBack_Fifo_Ovfl  = handle_port_fifo_ovfl;
    dvp2axi_cb.DVP2AXI_CallBack_HCnt_Exm   = handle_hcnt_non_matching;
    dvp2axi_cb.DVP2AXI_CallBack_VCnt_Exm   = handle_vcnt_non_matching;

    DVP2AXI_InstallCallback(&dvp2axi_cb, NULL);
}

static void bl_dsp2_scaler_path_init()
{
    DSP2_Scaler_Set_Input(DSP2_SCALER_A, DSP2_SCALER_INPUT_DSP2_OUTPUT);
    DSP2_Scaler_Set_Input(DSP2_SCALER_B, DSP2_SCALER_INPUT_DSP2_OUTPUT);
    DSP2_Scaler_Set_Input(DSP2_SCALER_C, DSP2_SCALER_INPUT_DSP2_OUTPUT);
    DSP2_Scaler_Set_Input(DSP2_SCALER_D, DSP2_SCALER_INPUT_DSP2_OUTPUT);
}

static void bl_dsp2_yuv_adj_init()
{
    DSP2_YUV_Adjust_Init();

    DSP2_YUV_Adjust_Set_Input(DSP2_YUV_ADJUST_A, DSP2_YUV_ADJUST_INPUT_SCALER_A);
    DSP2_YUV_Adjust_Set_Input(DSP2_YUV_ADJUST_B, DSP2_YUV_ADJUST_INPUT_SCALER_B);
    DSP2_YUV_Adjust_Set_Input(DSP2_YUV_ADJUST_C, DSP2_YUV_ADJUST_INPUT_SCALER_C);
}

static void bl_dsp2_intr_config()
{
    DSP2_Intr_Ctrl_Init();

    Interrupt_Handler_Register(AE_STATS_IRQn, DSP2_AE_STATS_IRQHandler);
    System_NVIC_SetPriority(AE_STATS_IRQn, 3, 1);

    Interrupt_Handler_Register(AE_HIST_STATS_IRQn, DSP2_AE_HIST_STATS_IRQHandler);
    System_NVIC_SetPriority(AE_HIST_STATS_IRQn, 3, 1);

    Interrupt_Handler_Register(AWB_STATS_IRQn, DSP2_AWB_STATS_IRQHandler);
    System_NVIC_SetPriority(AWB_STATS_IRQn, 3, 1);

    Interrupt_Handler_Register(AWB2_STATS_IRQn, DSP2_AWB2_STATS_IRQHandler);
    System_NVIC_SetPriority(AWB2_STATS_IRQn, 3, 1);

    Interrupt_Handler_Register(AWB3_STATS_IRQn, DSP2_AWB3_STATS_IRQHandler);
    System_NVIC_SetPriority(AWB3_STATS_IRQn, 3, 1);

    Interrupt_Handler_Register(WDR_STATS_IRQn, DSP2_WDR_STATS_IRQHandler);
    System_NVIC_SetPriority(WDR_STATS_IRQn, 3, 1);

    Interrupt_Handler_Register(SEOF1_IRQn, DSP2_SEOF1_IRQHandler);
    System_NVIC_SetPriority(SEOF1_IRQn, 3, 1);

    Interrupt_Handler_Register(SEOF2_IRQn, DSP2_SEOF2_IRQHandler);
    System_NVIC_SetPriority(SEOF2_IRQn, 3, 1);

    Interrupt_Handler_Register(SEOF3_IRQn, DSP2_SEOF3_IRQHandler);
    System_NVIC_SetPriority(SEOF3_IRQn, 3, 1);

    Interrupt_Handler_Register(SEOF4_IRQn, DSP2_SEOF4_IRQHandler);
    System_NVIC_SetPriority(SEOF4_IRQn, 3, 1);
}

int bl_dsp2_awb_gain_init()
{
    DSP2_RGB_Gain_Type rgb_gain;
    rgb_gain.r_gain = 4096;
    rgb_gain.g_gain = 4096;
    rgb_gain.b_gain = 4096;

    DSP2_Set_AWB_Gain(&rgb_gain);
    DSP2_Set_AWB2_Gain(&rgb_gain);

    return 0;
}

void bl_dsp2_osd_path_init()
{
    DSP2_OSD_Set_Input(DSP2_OSD_A, DSP2_OSD_INPUT_DSP2_OUTPUT);
    DSP2_OSD_Set_Input(DSP2_OSD_B, DSP2_OSD_INPUT_OSD_A);
    DSP2_Scaler_Set_Input(DSP2_SCALER_A, DSP2_SCALER_INPUT_OSD_B);
    DSP2_Scaler_Set_Input(DSP2_SCALER_B, DSP2_SCALER_INPUT_OSD_B);
    DSP2_Scaler_Set_Input(DSP2_SCALER_C, DSP2_SCALER_INPUT_OSD_B);
}

void bl_dsp2_tg_init(bl_vin_config_t *cfg)
{
    CHECK_PARAM((cfg->bit_depth == 10) || (cfg->bit_depth == 12));

    /* DSP2 misc config */
    DSP2_Misc_Config((cfg->bit_depth == 10) ? DSP2_DVP_10_BIT : DSP2_DVP_12_BIT);

    cfg_tg.sync_mode_value = (cfg->is_hsync_toggle_in_vblank) ? DSP2_SYNC_MODE_INPUT :
        DSP2_SYNC_MODE_INPUT_VBLANK_NO_TOGGLE;

    cfg_tg.total_width   = cfg->total_win.width;
    cfg_tg.total_height  = cfg->total_win.height;
    cfg_tg.active_width  = cfg->act_win.width;
    cfg_tg.active_height = cfg->act_win.height;
    cfg_tg.out_width     = cfg->out_win.width;
    cfg_tg.out_height    = cfg->out_win.height;
    cfg_tg.fps           = cfg->fps;

    cfg_tg.pix_clk = cfg->pix_clk;
    cfg_tg.DSP2_clk = cfg->dsp2_clk;

    DSP2_Set_TG_Cfg(&cfg_tg);
#if ENABLE_DVP_RESHAPE
    DSP2_Set_TG_Reshape_Cfg();
#endif

}

void bl_dsp2_sys_init()
{
    bl_dsp2_dvp2axi_init();
    bl_dsp2_scaler_path_init();
    bl_dsp2_yuv_adj_init();
    bl_dsp2_intr_config();
}

void bl_dsp2_datapath_init()
{
    bl_dsp2_dvp2axi_init();
    bl_dsp2_yuv_adj_init();
}

void bl_dsp2_misc_init()
{
#if ENABLE_DVP_RESHAPE
    DSP2_MISC_Reshape_Counter_Clear();
    DSP2_MISC_Reshape_Set_Counter(2);
    DSP2_MISC_Reshape_Set_State(ENABLE);

    DSP2_MISC_Reshape_Set_VSync_Inv(ENABLE);
    DSP2_MISC_Reshape_Set_HSync_Inv(DISABLE);
#endif
}

int bl_dsp2_set_input_total_window(BL_Img_Size_T *win)
{
    cfg_tg.total_width =  win->width;
    cfg_tg.total_height = win->height;

    return 0;
}

int bl_dsp2_set_input_resolution(BL_Img_Size_T *win)
{
    CHECK_PARAM(win->width  > 0 && win->width <= MAX_INPUT_WIDTH);
    CHECK_PARAM(win->height > 0 && win->height <= MAX_INPUT_HEIGHT);

    cfg_tg.active_width =  win->width;
    cfg_tg.active_height = win->height;

    return 0;
}

int bl_dsp2_get_input_resolution(BL_Img_Size_T *win)
{
    win->width  = cfg_tg.active_width;
    win->height = cfg_tg.active_height;

    return 0;
}

int bl_dsp2_get_out_resolution(BL_Img_Size_T *win)
{
    win->width  = cfg_tg.out_width;
    win->height = cfg_tg.out_height;

    return 0;
}

int bl_dsp2_set_crop_roi(int channID, bl_dsp2_crop_roi_t *roi)
{
    DSP2_MISC_Crop_Cfg_Type cropCfg;
    BL_Fun_Type state;

    if (roi->start_x >= roi->end_x || roi->start_y >= roi->end_y) {
        BL_LOGE("== bl_dsp2_set_crop_roi Error, set roi: sx:%d, ex:%d, sy:%d, ey:%d ==\r\n",roi->start_x, roi->end_x, roi->start_y, roi->end_y);
        return -1;
    }

    if ((roi->start_x % 2) || (roi->start_y % 2)) {
        BL_LOGE("== bl_dsp2_set_crop_roi Error, the start position needed to be even. sx:%d, sy:%d ==\r\n",roi->start_x, roi->start_y);
        return -1;
    }

    if (((roi->end_x - roi->start_x) % 2) || ((roi->end_y - roi->start_y) % 2)) {
        BL_LOGE("== bl_dsp2_set_crop_roi Error, the width and height needed to be even. width :%d, height:%d ==\r\n",(roi->end_x - roi->start_x),(roi->end_y - roi->start_y));
        return -1;
    }

    cropCfg.hsyncStart = roi->start_x;
    cropCfg.hsyncEnd = roi->end_x;
    cropCfg.vsyncStart = roi->start_y;
    cropCfg.vsyncEnd = roi->end_y;
    DSP2_MISC_Crop_Init(channID, &cropCfg);
    DSP2_MISC_Crop_Enable(channID);

    return 0;
}

int bl_dsp2_get_crop_roi(int channID, bl_dsp2_crop_roi_t *roi)
{
    DSP2_MISC_Crop_Cfg_Type cropCfg;

    DSP2_MISC_Crop_Get_Cfg(channID, &cropCfg);
    roi->start_x = cropCfg.hsyncStart;
    roi->end_x = cropCfg.hsyncEnd;
    roi->start_y = cropCfg.vsyncStart;
    roi->end_y = cropCfg.vsyncEnd;

    return 0;
}

int bl_dsp2_set_scaler_resolution(int channID, BL_Img_Size_T *win)
{
    BL_Img_Size_T win_out;
    BL_Fun_Type crop_state;
    bl_dsp2_crop_roi_t roi;

    DSP2_MISC_Crop_Get_State(channID, &crop_state);
    if (crop_state == ENABLE) {
        bl_dsp2_get_crop_roi(channID, &roi);
        win_out.width  = roi.end_x - roi.start_x;
        win_out.height = roi.end_y - roi.start_y;
    } else {
        win_out.width  = cfg_tg.out_width;
        win_out.height = cfg_tg.out_height;
    }

    CHECK_PARAM(win->width  > 0 && win->width <= MAX_INPUT_WIDTH);
    CHECK_PARAM(win->height > 0 && win->height <= MAX_INPUT_HEIGHT);

    res_scaler[channID].width  = win->width;
    res_scaler[channID].height = win->height;

    // scaler_type = (channID == 0) ? DSP2_SCALER_A : DSP2_SCALER_B;
    set_scaler_cfg((DSP2_Scaler_Type)channID, &win_out, &res_scaler[channID]);
    return 0;
}

int bl_dsp2_set_yuv_adj_state(int channID, BL_Fun_Type state)
{
    DSP2_YUV_Adjust_Set_State(channID, state);

    return 0;
}

int bl_dsp2_get_scaler_resolution(int channID, BL_Img_Size_T *win)
{
    win->width  = res_scaler[channID].width;
    win->height = res_scaler[channID].height;

    return 0;
}

int bl_dsp2_cfg_init(bl_vin_config_t *cfg)
{
    /******** INIT ********/
    DSP2_Init();

    DSP2_Set_DPC_State(ENABLE);
    DSP2_Set_BNR_State(DISABLE);//it's no ready on bl808 
    DSP2_Set_LSC_State(ENABLE);

    DSP2_Set_CCM_State(ENABLE);
    DSP2_Set_Gamma_State(ENABLE);
    DSP2_WDR_Set_WDR_State(ENABLE);
    /* BT601 disable */
    DSP2_Init_Color_Enhancement();
    // DSP2_Set_YUV_Conv_Mode(DSP2_YUV_CONV_FULL_SCALE);

    DSP2_Enable_BL_DSP2_Back();
    DSP2_Set_EE_State(ENABLE);
    DSP2_Set_ChromaSuppress_State(ENABLE);

    DSP2_Set_Bayer_Pattern(cfg->bayer_pattern);

    bl_dsp2_tg_init(cfg);

#if ENABLE_3DNR
    if (!cfg->is_virtual) bl_dsp2_enable_3dnr(&cfg->act_win);
#endif

    return 0;
}

int bl_dsp2_enable_dump_chann(int channID, BL_DSP2_IMAGE_DUMP_SRC_T src, BL_DSP2_IMAGE_PLANE_T image_plane,
                                bl_dsp2_dump_cfg_t *dump_cfg)
{
    uint32_t portID = DUMP_PORT(channID);

    DVP2AXI_Set_SW_Mode(DVP2AXI_ID(portID), ENABLE);

    dsp2_set_dump_port_src(portID, src);
    dsp2_set_image_plane(portID, image_plane);
    dsp2_enable_port(portID, dump_cfg);

    return 0;
}

int bl_dsp2_disable_dump_chann(int channID)
{
    uint32_t portID = DUMP_PORT(channID);
    dsp2_disable_port(portID);

    return 0;
}

int bl_dsp2_resume_dump_chann(int channID)
{
    uint32_t portID = DUMP_PORT(channID);
    dsp2_resume_port(portID);

    return 0;
}

int bl_dsp2_enable_hdmi_port(int channID, uint8_t *dualBufAddr, uint32_t dualBufSize)
{
    uint32_t portID = DUMP_PORT(channID);
    bl_dsp2_dump_cfg_t dump_cfg;

    dsp2_disable_port(portID);
    DVP2AXI_Set_SW_Mode(DVP2AXI_ID(portID), DISABLE);

    // HDMI tie to ADJB which should be set 720p, limit range
    dsp2_set_dump_port_src(portID, BL_IMAGE_DUMP_SRC_ADJ_B);
    dsp2_set_image_plane(portID, IMAGE_PLANE_YUV);

    dump_cfg.buf_base_addr = dualBufAddr;
    dump_cfg.buf_size      = dualBufSize;
    dump_cfg.frame_size    = (dualBufSize >> 1);
    dump_cfg.win.width     = (&res_scaler[channID])->width;
    dump_cfg.win.height    = (&res_scaler[channID])->height;
    dsp2_enable_port(portID, &dump_cfg);

    return 0;
}

int bl_dsp2_disable_hdmi_port(int channID)
{
    uint32_t portID = DUMP_PORT(channID);
    dsp2_disable_port(portID);

    return 0;
}

int bl_dsp2_enable_ouput_channel(int channID)
{
    uint32_t portY = ENC_SRC_PORT_Y(channID);
    uint32_t portUV = ENC_SRC_PORT_UV(channID);

    DVP2AXI_Enable(DVP2AXI_ID(portY));
    DVP2AXI_Enable(DVP2AXI_ID(portUV));

    return 0;
}

int bl_dsp2_disable_output_channel(int channID)
{
    uint32_t portY = ENC_SRC_PORT_Y(channID);
    uint32_t portUV = ENC_SRC_PORT_UV(channID);

    dsp2_disable_port(portY);
    dsp2_disable_port(portUV);

    return 0;
}

int bl_dsp2_set_ouput_buffer(int channID, bl_dsp2_output_buffer_t *outBuf, BL_Fun_Type sw_mode)
{
    uint32_t frameSize;
    BL_DSP2_IMAGE_DUMP_SRC_T dataSrc;
    BL_Img_Size_T *res = &res_scaler[channID];

    uint32_t portY = ENC_SRC_PORT_Y(channID);
    uint32_t portUV = ENC_SRC_PORT_UV(channID);

    DVP2AXI_Set_SW_Mode(DVP2AXI_ID(portY), sw_mode);
    DVP2AXI_Set_SW_Mode(DVP2AXI_ID(portUV), sw_mode);

    if (sw_mode == ENABLE) {
        gFrameAutoPopEnable[DVP2AXI_ID(portY)] = true;
        gFrameAutoPopEnable[DVP2AXI_ID(portUV)] = true;
    } else {
        gFrameAutoPopEnable[DVP2AXI_ID(portY)] = false;
        gFrameAutoPopEnable[DVP2AXI_ID(portUV)] = false;
    }

    if (0 == channID) {
        dataSrc = BL_IMAGE_DUMP_SRC_YUV420_A;
    }
    else if (1 == channID) {
        dataSrc = BL_IMAGE_DUMP_SRC_YUV420_B;
    }
    else if (2 == channID) {
        dataSrc = BL_IMAGE_DUMP_SRC_YUV420_C;
    }
    else {
        dataSrc = BL_IMAGE_DUMP_SRC_YUV420_A;
    }

    dsp2_set_dump_port_src(portY, dataSrc);
    dsp2_set_dump_port_src(portUV, dataSrc);

    dsp2_set_image_plane(portY,  IMAGE_PLANE_Y_ONLY);
    dsp2_set_image_plane(portUV, IMAGE_PLANE_UV_ONLY);

    frameSize = res->width * ENC_HEIGHT(res->height);

    /* Y frame */
    DVP2AXI_SetFrameSize(DVP2AXI_ID(portY), frameSize);
    DVP2AXI_MemConfig(DVP2AXI_ID(portY), (uint32_t)outBuf->y_frame_base_addr, outBuf->y_frame_size);
    DVP2AXI_Valid_Cnt_Exm(DVP2AXI_ID(portY), res->width, res->height);

    /* UV frame */
    DVP2AXI_SetFrameSize(DVP2AXI_ID(portUV), (frameSize >> 1));
    DVP2AXI_MemConfig(DVP2AXI_ID(portUV), (uint32_t)outBuf->uv_frame_base_addr, outBuf->uv_frame_size);
    DVP2AXI_Valid_Cnt_Exm(DVP2AXI_ID(portUV), res->width, res->height);

    /* Force scaler settings applied */
    DSP2_MISC_Scaler_Sh_Enable(channID);

    return 0;
}

int bl_dsp2_set_channel_frame_rate(int channID, uint32_t snsFrmRate,
                                        uint32_t outFrmRateNum, uint32_t outFrmRateDen)
{
    uint32_t snsFrmRate_2;
    uint32_t bitwiseFrmVld = 0;
    int frmCnt = 0;
    int frmPeriodCnt = 0;

    uint32_t portY = ENC_SRC_PORT_Y(channID);
    uint32_t portUV = ENC_SRC_PORT_UV(channID);

    snsFrmRate_2 = snsFrmRate * outFrmRateDen;

    /* make sure LSB of bit pattern is always 1, so the very first frame is not dropped */
    while (1) {
        bitwiseFrmVld <<= 1;
        frmCnt += outFrmRateNum;
        frmPeriodCnt++;
        if (frmCnt >= snsFrmRate_2) {
            bitwiseFrmVld |= 1;
            frmCnt -= snsFrmRate_2;
            BL_LOGI("1");
            if (frmCnt == 0) {
                break;
            }
        } else {
            BL_LOGI("0");
        }
    }
    BL_LOGI("\r\nbitwiseFrmVld 0x%x\r\n", bitwiseFrmVld);

    DVP2AXI_Set_Frame_Skip(portY, bitwiseFrmVld, frmPeriodCnt - 1);
    DVP2AXI_Set_Frame_Skip(portUV, bitwiseFrmVld, frmPeriodCnt - 1);

    return 0;
}

int bl_dsp2_enable_3dnr(BL_Img_Size_T *act_win)
{
    DSP2_3DNR_Cfg_Type cfg;
    uint32_t refBufSize = act_win->width * act_win->height << 1;    /* single YUV frame size for 3DNR */

    if (NULL != buf_addr_3dnr) {
        BL_FreeDMA(buf_addr_3dnr);
    }
    buf_addr_3dnr = BL_MallocDMA(PSRAM_ID_FOR_3DNR_BUF, refBufSize);

    cfg.burst = DSP2_3DNR_BURST_TYPE_INCR64;
    cfg.memStart = (uint32_t) buf_addr_3dnr;;
    cfg.memSize = refBufSize;
    cfg.hsyncStart = 0;
    cfg.hsyncEnd = act_win->width;
    cfg.vsyncStart = 0;
    cfg.vsyncEnd = act_win->height;
    DSP2_3DNR_Init(&cfg);
    DSP2_3DNR_Enable();

    return 0;
}

int bl_dsp2_disable_3dnr(void)
{
    if (NULL != buf_addr_3dnr) {
        BL_FreeDMA(buf_addr_3dnr);
    }
    DSP2_3DNR_Disable();

    return 0;
}

void bl_dsp2_get_3dnr_refFrameBuf(uint32_t *bufAddr, uint32_t *bufSize)
{
    DSP2_3DNR_GetRefFrameBuf(bufAddr, bufSize);
}

int bl_vout_enable_hdmi_out(int channID, uint8_t *inBufAddr, uint32_t inBufSize)
{
    DSP2_DVP_TSRC_CFG_S cfg;
    DVPTSrc_Frame_Size_Cfg_Type frmSizeCfg;

    cfg.dvp_input = DVP_TSRC_INPUT_AHB;
    cfg.is_8bit = 0;
    cfg.swap_mode = ENABLE;
    cfg.swap_index = DUMP_PORT(channID);
    DSP2_DVP_TSrc_Cfg(DVP_TSRC_HDMI, &cfg);

    *((uint32_t*)(0x30010060)) = 0x380;
    frmSizeCfg.width = 1280;
    frmSizeCfg.height = 720;
    frmSizeCfg.hBlank = 700;
    frmSizeCfg.vBlank = 30;
    DSP2_DVPTSrc_SetFrameSize(DVP_TSRC_HDMI, &frmSizeCfg);

    DSP2_DVP_TSrc_MemCfg(DVP_TSRC_HDMI, (uint32_t)inBufAddr, inBufSize);
    DSP2_DVP_TSrc_Enable(DVP_TSRC_HDMI);

    return 0;
}

int bl_vout_disable_hdmi_out(void)
{
    DSP2_DVP_TSrc_Disable(DVP_TSRC_HDMI);

    return 0;
}

static int bl_dsp2_csi_dvptsrc_cfg(uint32_t pixClk, uint32_t dsp2Clk)
{
    DSP2_DVP_TSRC_CFG_S cfg;

    /* used as frequency bridge */
    cfg.dvp_input = DVP_TSRC_INPUT_SENSOR;


#if 0   /* use dynamic calculation instead */
    /* snsr_fifo_th: 768 for 1080p @ 49.5M pclk, 220 for 720p @ 36M pclk,
        64 for 1080p @ 78M pclk */
    if (res->width == 1280) {
        cfg.snsr_fifo_th = 220;
    } else if (res->width == 1920) {
        cfg.snsr_fifo_th = 64;
    }
#endif

    /* FIFO_thresh = width x (Freq2 - Freq1) / Freq2 + margin */
    if (dsp2Clk > pixClk) {
        cfg.snsr_fifo_th = (uint64_t)cfg_tg.active_width * (dsp2Clk - pixClk) / dsp2Clk + 10;
    } else {
        cfg.snsr_fifo_th = 0;
    }

    BL_LOGI("[snsr_fifo_th] = %d\r\n", cfg.snsr_fifo_th);

    cfg.is_8bit = 0;
    cfg.swap_mode = DISABLE;

    DSP2_DVP_TSrc_Cfg(DVP_TSRC_DSP2, &cfg);
    DSP2_DVP_TSrc_Enable(DVP_TSRC_DSP2);

    return 0;
}

int bl_vin_enable_mipi_input(uint32_t pixClk, uint32_t dsp2Clk, BL_DSP2_INPUT_MODE_E lane_mode)
{
    bl_dsp2_csi_ctrl_cfg(lane_mode);
    bl_dsp2_csi_dvptsrc_cfg(pixClk, dsp2Clk);
    return 0;
}

int bl_vin_enable_dvp_input(uint32_t pixClk, uint32_t dsp2Clk)
{
    DSP2_DVP_TSRC_CFG_S cfg;

    /* used as frequency bridge */
    cfg.dvp_input = DVP_TSRC_INPUT_SENSOR;


#if 0   /* use dynamic calculation instead */
    /* snsr_fifo_th: 768 for 1080p @ 49.5M pclk, 220 for 720p @ 36M pclk,
        64 for 1080p @ 78M pclk */
    if (res->width == 1280) {
        cfg.snsr_fifo_th = 220;
    } else if (res->width == 1920) {
        cfg.snsr_fifo_th = 64;
    }
#endif

    /* FIFO_thresh = width x (Freq2 - Freq1) / Freq2 + margin */
    if (dsp2Clk > pixClk) {
        cfg.snsr_fifo_th = (uint64_t)cfg_tg.active_width * (dsp2Clk - pixClk) / dsp2Clk + 10;
    } else {
        cfg.snsr_fifo_th = 0;
    }

    BL_LOGI("[snsr_fifo_th] = %d\r\n", cfg.snsr_fifo_th);

    cfg.is_8bit = 0;
    cfg.swap_mode = DISABLE;

    DSP2_DVP_TSrc_Cfg(DVP_TSRC_DSP2, &cfg);
    DSP2_DVP_TSrc_Enable(DVP_TSRC_DSP2);

    return 0;
}

int bl_vin_enable_raw_file_input(uint8_t *inBufAddr, uint32_t inBufSize)
{
    DSP2_DVP_TSRC_CFG_S cfg;
    DVPTSrc_Frame_Size_Cfg_Type frmSizeCfg;

    cfg.dvp_input = DVP_TSRC_INPUT_AHB;
    cfg.is_8bit = 0;
    cfg.swap_mode = DISABLE;
    DSP2_DVP_TSrc_Cfg(DVP_TSRC_DSP2, &cfg);

    frmSizeCfg.width =  cfg_tg.active_width;
    frmSizeCfg.height = cfg_tg.active_height;
    frmSizeCfg.hBlank = cfg_tg.total_width  - cfg_tg.active_width;
    frmSizeCfg.vBlank = cfg_tg.total_height - cfg_tg.active_height;
    DSP2_DVPTSrc_SetFrameSize(DVP_TSRC_DSP2, &frmSizeCfg);

    DSP2_DVP_TSrc_MemCfg(DVP_TSRC_DSP2, (uint32_t)inBufAddr, inBufSize);
    DSP2_DVP_TSrc_Enable(DVP_TSRC_DSP2);

    return 0;
}

int bl_vin_enable_fakedata_input(int pattern_mode)
{
    DSP2_DVP_TSRC_CFG_S cfg;
    DVPTSrc_Frame_Size_Cfg_Type frmSizeCfg;

    cfg.dvp_input = DVP_TSRC_INPUT_FAKEDATA;
    cfg.is_8bit = 0;
    cfg.swap_mode = DISABLE;
    DSP2_DVP_TSrc_Cfg(DVP_TSRC_DSP2, &cfg);

    frmSizeCfg.width =  cfg_tg.active_width;
    frmSizeCfg.height = cfg_tg.active_height;
    frmSizeCfg.hBlank = cfg_tg.total_width  - cfg_tg.active_width;
    frmSizeCfg.vBlank = cfg_tg.total_height - cfg_tg.active_height;
    DSP2_DVPTSrc_SetFrameSize(DVP_TSRC_DSP2, &frmSizeCfg);

    DSP2_DVP_TSrc_Enable(DVP_TSRC_DSP2);
    DSP2_Set_PatternGen_Mode(pattern_mode);

    return 0;
}

int bl_dsp2_dump_next_frame(int channID)
{
    uint32_t portID = DUMP_PORT(channID);

    DVP2AXI_FrameFifoPop(DVP2AXI_ID(portID));

    return 0;
}

int bl_dsp2_set_day_night_mode(BL_DSP2_DAY_NIGHT_MODE_T mode)
{
    DSP2_SATURATION_S satCfg = {0, 0};
    int prev_nr_str;
    bl_dsp2_rgb_gain_t wb_gain_UNIT       = {4096, 4096, 4096};
    bl_dsp2_rgb_gain_t wb_gain_USE_NORMAL = {   0,    0,    0};

    day_night_mode = mode;

    /* set saturation 0 in black white mode */
    if (mode == BL_NIGHT_MODE) {
        DSP2_Set_Saturation(&satCfg);
        awb_set_manual_rgb_gain(&wb_gain_UNIT);
        DSP2_Set_CCM_State( (BL_Fun_Type)0 );

        DSP2_Get_3D_NR(&prev_nr_str);
        DSP2_Set_3D_NR(0);

        /* Keep 3DNR off for a while to remove the remained cbcr color */
        vTaskDelay(10);     /* 10ms delay */

        DSP2_Set_3D_NR(prev_nr_str);

    } else {

        awb_set_manual_rgb_gain(&wb_gain_USE_NORMAL);
        DSP2_Set_CCM_State( (BL_Fun_Type)1 );
    }


    return 0;
}

int bl_dsp2_low_fps_cfg(uint8_t m)
{
    DSP2_FRAME_M_TO_N_S frm_m_to_n;

    frm_m_to_n.enb = ENABLE;
    frm_m_to_n.m = m;
    frm_m_to_n.n = 0;
    frm_m_to_n.intv = 0;
    DSP2_Frame_M_to_N(&frm_m_to_n);

    return 0;
}

int bl_dsp2_stats_ready_config(bl_dsp2_stats_ready_cb cb, void *usrdata)
{
    stats_ready_cb = cb;

    return 0;
}

int bl_dsp2_frame_ready_config(int channID, bl_dsp2_frame_ready_cb cb, void *usrdata)
{
    frame_ready_cb[channID] = cb;

    return 0;
}

void bl_dsp2_scaler_path_dvp2x(BL_DSP2_SCALER_TYPE_T scaler)
{
    DSP2_Scaler_Set_Input((DSP2_Scaler_Type)scaler, DSP2_SCALER_DVP_2X);
}
#if PRINT_FAST_CAP_TIMING
static int ae_count =0;
static int aeh_count =0;
static int awb_count =0;
static int wdr_count =0;
static int sp_count =0;
static int sn_count =0;
static int ap_count =0;
static int an_count =0;
#endif

void DSP2_AE_STATS_IRQHandler(void)
{
    /* clear interrupt signal */
    DSP2_Intr_Clr(DSP2_AE_INTR);
#if PRINT_FAST_CAP_TIMING
    printf("AE %d %lu\r\n",  ae_count++, xTaskGetTickCountFromISR());
#endif

#if 0   /* test shutter & gain synchronization */
    static int cnt = 0;
    bl808_delay_ms(10);

    /* Skip every other frame */
    if (cnt++ % 30 == 0) {
        if ((cnt / 30) % 3 == 0) {
           sensor_set_exposure(EXPO_TIME_1_25_SEC);
           sensor_set_gain(INT_TO_GAIN_DB(0));
        } else if ((cnt / 30) % 3 == 1) {
            sensor_set_exposure(EXPO_TIME_1_50_SEC);
            sensor_set_gain(GAIN_6_DB);
        } else {
            sensor_set_exposure(EXPO_TIME_1_100_SEC);
            sensor_set_gain(INT_TO_GAIN_DB(12));
        }
    }
    return;
#endif

// #if PERFORMANCE_MONITOR
//     do_frame_rate_stats("ae intr", &ae_intr_cnt, FRM_CNT_FOR_ONE_STATS, &ae_intr_start_time);
// #endif

//     /* take this interrupt opportunity to check system error */
//     DSP2_DVP_TSrc_Check_Status(DVP_TSRC_DSP2);
//     DSP2_DVP_TSrc_Check_Status(DVP_TSRC_HDMI);
// #if ENABLE_3DNR
//     DSP2_3DNR_AXI_Ctrl_Check_Status();
// #endif
//     if (stats_ready_cb) {
//         stats_ready_cb(NULL);
//     }
}

void DSP2_AE_HIST_STATS_IRQHandler(void)
{
    /* clear interrupt signal */
    DSP2_Intr_Clr(DSP2_AE_HIST_INTR);
#if PRINT_FAST_CAP_TIMING
    printf("AEH %d, %lu\r\n", aeh_count++, xTaskGetTickCountFromISR());
#endif
}

void DSP2_AWB_STATS_IRQHandler(void)
{
    /* clear interrupt signal */
    DSP2_Intr_Clr(DSP2_AWB_INTR);

#if PRINT_FAST_CAP_TIMING
    printf("AWB %lu\r\n", xTaskGetTickCountFromISR());
#endif
}

void DSP2_AWB2_STATS_IRQHandler(void)
{
    /* clear interrupt signal */
    DSP2_Intr_Clr(DSP2_AWB2_INTR);

#if PRINT_FAST_CAP_TIMING
    printf("AWB2 %lu\r\n", xTaskGetTickCountFromISR());
#endif
}

void DSP2_AWB3_STATS_IRQHandler(void)
{
    /* clear interrupt signal */
    DSP2_Intr_Clr(DSP2_AWB3_INTR);

#if PRINT_FAST_CAP_TIMING
    printf("WB3 %d %lu\r\n", awb_count++, xTaskGetTickCountFromISR());
#endif
}

void DSP2_WDR_STATS_IRQHandler(void)
{
    /* clear interrupt signal */
    DSP2_Intr_Clr(DSP2_WDR_INTR);

#if PRINT_FAST_CAP_TIMING
    printf("WDR %d %lu\r\n",wdr_count++ ,  xTaskGetTickCountFromISR());
#endif
}

void DSP2_SEOF1_IRQHandler(void)
{
    DSP2_Intr_Clr(DSP2_SEOF1_INTR);
#if PRINT_FAST_CAP_TIMING
    // sensor positive edge
    printf("SP %d %lu\r\n", sp_count++, xTaskGetTickCountFromISR());
#endif

}

void DSP2_SEOF2_IRQHandler(void)
{
    DSP2_Intr_Clr(DSP2_SEOF2_INTR);
#if PRINT_FAST_CAP_TIMING
    // act_out positive edge
     printf("AP %d %lu\r\n", ap_count++, xTaskGetTickCountFromISR());
#endif

#if PERFORMANCE_MONITOR
    do_frame_rate_stats("ae intr", &ae_intr_cnt, FRM_CNT_FOR_ONE_STATS, &ae_intr_start_time);
#endif

    /* take this interrupt opportunity to check system error */
    DSP2_DVP_TSrc_Check_Status(DVP_TSRC_DSP2);
    DSP2_DVP_TSrc_Check_Status(DVP_TSRC_HDMI);
#if ENABLE_3DNR
    DSP2_3DNR_AXI_Ctrl_Check_Status();
#endif
    if (stats_ready_cb) {
        stats_ready_cb(NULL);
    }
    if ((dev_osd != NULL) && (test_bit(BL_OSD_SYSTIME, &dev_osd->funcs) ||
		    test_bit(BL_OSD_BOOTTIME, &dev_osd->funcs) ||
            test_bit(BL_OSD_FRAMES, &dev_osd->funcs) ||
            test_bit(BL_OSD_AI, &dev_osd->funcs))) {
        dev_osd->fcount++;
        dev_osd->status = VVALID;
        osd_seof_wakeup();
    }
}

void DSP2_SEOF3_IRQHandler(void)
{
    DSP2_Intr_Clr(DSP2_SEOF3_INTR);
#if PRINT_FAST_CAP_TIMING
    // act_out negative edge
    printf("SN %d %lu\r\n", sn_count++, xTaskGetTickCountFromISR());
#endif
}

void DSP2_SEOF4_IRQHandler(void)
{
    DSP2_Intr_Clr(DSP2_SEOF4_INTR);
#if PRINT_FAST_CAP_TIMING
    // act_out negative edge
    printf("AN %d %lu\r\n", an_count++, xTaskGetTickCountFromISR());
#endif
}

/*******************************************************************/
int bl_set_AE_state(BL_Fun_Type state)
{
    DSP2_Set_AE_State(state);
    return 0;
}

int bl_set_AE_state_enable(void)
{
    DSP2_Set_AE_State(ENABLE);
    DSP2_Set_AE_Hist_State(ENABLE);
    return 0;
}

int bl_set_AE_stats_conf (bl_dsp2_ae_stats_conf_t *conf)
{
    dsp2_ae_stats_conf_t ae_stats_conf;

    ae_stats_conf.grid_num_x  = conf->grid_num_x;
    ae_stats_conf.grid_num_y  = conf->grid_num_y;
    ae_stats_conf.img_width   = conf->img_width;
    ae_stats_conf.img_height  = conf->img_height;
    ae_stats_conf.grid_width  = even_division(conf->img_width, conf->grid_num_x);
    ae_stats_conf.grid_height = even_division(conf->img_height, conf->grid_num_y);
    ae_stats_conf.roi_start_x = (ae_stats_conf.img_width \
        - conf->grid_num_x*ae_stats_conf.grid_width)/2 ;
    ae_stats_conf.roi_start_y = (ae_stats_conf.img_height \
        - conf->grid_num_y*ae_stats_conf.grid_height)/2 ;
    ae_stats_conf.roi_width   = conf->grid_num_x*ae_stats_conf.grid_width;
    ae_stats_conf.roi_height  = conf->grid_num_y*ae_stats_conf.grid_height;

    DSP2_Set_AE_Stats_Conf(&ae_stats_conf);
    return 0;
}

int bl_get_AE_stats_conf (bl_dsp2_ae_stats_conf_t *conf)
{
    dsp2_ae_stats_conf_t ae_stats_conf;
    DSP2_Get_AE_Stats_Conf(&ae_stats_conf);

    conf->grid_num_x = ae_stats_conf.grid_num_x;
    conf->grid_num_y = ae_stats_conf.grid_num_y;
    conf->img_width = ae_stats_conf.img_width;
    conf->img_height = ae_stats_conf.img_height;

    return 0;
}

int bl_get_AE_stats(bl_dsp2_ae_grid_sum_t *stats)
{
    int i = 0;
    dsp2_ae_sum_t sum[AE_STATS_GRID_NUM];
    DSP2_Get_AE_Stats(AE_STATS_GRID_NUM, (uint32_t *)&sum);

    for (i = 0; i < AE_STATS_GRID_NUM; i++) {
        stats->y_sum[i] = sum[i].y_sum;
        stats->r_sum[i] = sum[i].r_sum;
        stats->g_sum[i] = sum[i].g_sum;
        stats->b_sum[i] = sum[i].b_sum;
    }

    return 0;
}

int bl_get_AE_hist_state(BL_Fun_Type *state)
{
    return DSP2_Get_AE_Hist_State(state);
}

int bl_set_AE_hist_state(BL_Fun_Type state)
{
    DSP2_Set_AE_Hist_State(state);
    return 0;
}

int bl_get_AE_hist_mode(AE_HIST_MODE_TYPE_E *mode)
{
    return DSP2_Get_AE_Hist_Mode(mode);
}

int bl_set_AE_hist_mode(AE_HIST_MODE_TYPE_E mode)
{
    DSP2_Set_AE_Hist_Mode(mode);
    return 0;
}

int bl_get_AE_hist_roi(uint16_t *x_min, uint16_t *x_max, uint16_t *y_min, uint16_t *y_max)
{
    dsp2_ae_hist_roi_t roi;

    DSP2_Get_AE_Hist_ROI(true, &roi);
    *x_min = roi.ae_hist_x_min;
    *x_max = roi.ae_hist_x_max;
    *y_min = roi.ae_hist_y_min;
    *y_max = roi.ae_hist_y_max;

    return 0;
}

int bl_set_AE_hist_roi(uint16_t x_min, uint16_t  x_max, uint16_t y_min, uint16_t y_max)
{
    dsp2_ae_hist_roi_t roi;

    roi.ae_hist_x_min = x_min;
    roi.ae_hist_x_max = x_max;
    roi.ae_hist_y_min = y_min;
    roi.ae_hist_y_max = y_max;

    return DSP2_Set_AE_Hist_ROI(true, &roi);
}

int bl_get_AE_hist_sum_y(bl_dsp2_ae_hist_y_t *y_sum)
{
    int ret = 0;
    AE_HIST_MODE_TYPE_E mode;

    DSP2_Get_AE_Hist_Mode(&mode);
    if(mode == AE_HIST_MODE_BAYER) return -1;
    ret = DSP2_Get_AE_Hist_SUM_Y((uint32_t *)y_sum);

    return ret;
}

int bl_get_AE_hist_sum_bayer(bl_dsp2_ae_hist_bayer_t *sum)
{
    int ret = 0;
    AE_HIST_MODE_TYPE_E mode;

    DSP2_Get_AE_Hist_Mode(&mode);
    if(mode == AE_HIST_MODE_Y) return -1;
    ret = DSP2_Get_AE_Hist_SUM_Bayer(sum->r, sum->gr, sum->gb, sum->b);

    return ret;
}

int bl_set_AWB_state(BL_Fun_Type state)
{
    DSP2_Set_AWB_State(state);
    return 0;
}

int bl_get_AWB_gain(bl_dsp2_rgb_gain_t *gain)
{
    DSP2_RGB_Gain_Type rgb_gain;

    DSP2_Get_AWB_Gain(&rgb_gain);
    gain->r_gain = rgb_gain.r_gain;
    gain->g_gain = rgb_gain.g_gain;
    gain->b_gain = rgb_gain.b_gain;

    return 0;
}

int bl_set_AWB_gain(bl_dsp2_rgb_gain_t *gain)
{
    DSP2_RGB_Gain_Type rgb_gain;

    rgb_gain.r_gain = gain->r_gain;
    rgb_gain.g_gain = gain->g_gain;
    rgb_gain.b_gain = gain->b_gain;

    DSP2_Set_AWB_Gain(&rgb_gain);

    return 0;
}

int bl_set_RB_gain(const bl_dsp2_rb_gain_t *rb_gain)
{
    DSP2_RGB_Gain_Type rgb_gain;

    rgb_gain.r_gain = rb_gain->r_gain;
    rgb_gain.g_gain = 4096;
    rgb_gain.b_gain = rb_gain->b_gain;

    DSP2_Set_AWB_Gain(&rgb_gain);

    return 0;
}


//******** algo 1***************************************************************//
int bl_set_AWB1_stats_conf(dsp2_awb_stats_conf_t *awb_stats_conf)
{
    DSP2_Set_AWB_Stats_Conf(awb_stats_conf);
    return 0;
}

int bl_get_AWB1_stats_conf(dsp2_awb_stats_conf_t *awb_stats_conf)
{
    DSP2_Set_AWB_Stats_Conf(awb_stats_conf);
    return 0;
}

int bl_get_AWB1_stats(int grid_num, uint32_t *data)
{
    DSP2_Get_AWB_Stats(grid_num, data);

    return 0;
}

int bl_get_AWB1_sum(int grid_idx, RGB_SUM_S *rgb_sum)
{
    DSP2_Get_AWB_Sum(grid_idx, rgb_sum);

    return 0;
}

//****** algo 3*****************************************************************//
int bl_set_AWB3_stats_conf(dsp2_awb3_stats_conf_t *awb_stats_conf)
{
    DSP2_Set_AWB3_Stats_Conf(awb_stats_conf);
    return 0;
}

int bl_get_AWB3_stats_conf(dsp2_awb3_stats_conf_t *awb_stats_conf)
{
    DSP2_Get_AWB3_Stats_Conf(awb_stats_conf);
    return 0;
}

int bl_get_AWB3_bin_mode(dsp2_awb3_bin_mode_e *mode)
{
    return DSP2_Get_AWB3_Bin_Mode(mode);
}

int bl_set_AWB3_bin_mode(dsp2_awb3_bin_mode_e mode)
{
    DSP2_Set_AWB3_Bin_Mode(mode);
    return 0;
}

int bl_get_AWB3_hist_bin_num(uint32_t *bucket_num)
{
    return DSP2_Get_AWB3_Hist_Bin_Num(bucket_num);
}

int bl_get_AWB3_hist(bl_dsp2_awb3_stats_hist_t *awb3_hist)
{
    int i = 0;
    uint32_t bucket_num;
    uint64_t val_l = 0, val_u = 0;

    DSP2_Get_AWB3_Hist_Bin_Num(&bucket_num);
#if 1
    DSP2_Get_AWB3_Hist((uint32_t *)&awb_hist_bin);
        for (i = 0; i < bucket_num; i++) {
        val_u = ((awb_hist_bin.bin[i].footprint[3] << 8) & (0xffffffff00));
        val_l = ((awb_hist_bin.bin[i].footprint[2] >> 24) & (0xff));
        awb3_hist->r_ratio[i] = val_u + val_l;//40bit

        val_u = ((awb_hist_bin.bin[i].footprint[2] & (0x00ffffff)) << 16 & (0xffffff0000));
        val_l = (awb_hist_bin.bin[i].footprint[1] >> 16 & (0xffff));
        awb3_hist->b_ratio[i] = val_u + val_l;//40bit

        val_u = ((awb_hist_bin.bin[i].footprint[1] & (0x0000ffff)) << 12 & (0xffff000));
        val_l = (awb_hist_bin.bin[i].footprint[0] >> 20 & (0xfff));
        awb3_hist->weight[i] = val_u + val_l;//28bit

        val_u = awb_hist_bin.bin[i].footprint[0] & (0x000fffff);
        awb3_hist->pixel[i] = val_u;//20bit
    }
#else
    bl_dsp2_awb3_stats_hist_bin_t *awb_hist_bin  =  ((uint32_t)0x30017000);//AWB3_HIST_BUCKET_ADDR;
    for (i = 0; i < bucket_num; i++) {
        val_u = ((awb_hist_bin->bin[i].footprint[3] << 8) & (0xffffffff00));
        val_l = ((awb_hist_bin->bin[i].footprint[2] >> 24) & (0xff));
        awb3_hist->r_ratio[i] = val_u + val_l;//40bit

        val_u = ((awb_hist_bin->bin[i].footprint[2] & (0x00ffffff)) << 16 & (0xffffff0000));
        val_l = (awb_hist_bin->bin[i].footprint[1] >> 16 & (0xffff));
        awb3_hist->b_ratio[i] = val_u + val_l;//40bit

        val_u = ((awb_hist_bin->bin[i].footprint[1] & (0x0000ffff)) << 12 & (0xffff000));
        val_l = (awb_hist_bin->bin[i].footprint[0] >> 20 & (0xfff));
        awb3_hist->weight[i] = val_u + val_l;//28bit

        val_u = awb_hist_bin->bin[i].footprint[0] & (0x000fffff);
        awb3_hist->pixel[i] = val_u;//20bit
    }
#endif
    return 0;
}

int bl_get_AWB3_gDivisor(int *value)
{
    return DSP2_Get_AWB3_G_Divisor(value);
}

int bl_set_AWB3_gDivisor(int value)
{
    DSP2_Set_AWB3_G_Divisor(value);
    return 0;
}

int bl_get_AWB3_sum(dsp2_awb3_sum_t *awb3_sum)
{
    return DSP2_Get_AWB3_Sum(awb3_sum);
}

int bl_get_WDR_state(BL_Fun_Type *state)
{
    DSP2_WDR_Get_WDR_State(state);
    return 0;
}

int bl_set_WDR_state(BL_Fun_Type state)
{
    DSP2_WDR_Set_WDR_State(state);
    return 0;
}

int bl_get_WDR_sub_state(bl_dsp2_wdr_sub_state_t *state)
{
    DSP2_WDR_Get_CS_State((BL_Fun_Type *)&state->cs_en);
    DSP2_WDR_Get_WDR_Curve_State((BL_Fun_Type *)&state->curve_en);
    DSP2_WDR_Get_Post_Enhance_State((BL_Fun_Type *)&state->enh_en);
    return 0;
}

int bl_set_WDR_sub_state(bl_dsp2_wdr_sub_state_t *state)
{
    DSP2_WDR_Set_CS_State((BL_Fun_Type)state->cs_en);
    DSP2_WDR_Set_WDR_Curve_State((BL_Fun_Type)state->curve_en);
    DSP2_WDR_Set_Post_Enhance_State((BL_Fun_Type)state->enh_en);
    return 0;
}

int bl_get_WDR_hist_roi_info(bl_dsp2_wdr_roi_info_t *info)
{
    DSP2_WDR_Get_ROI_State(info->id, (BL_Fun_Type *)&info->state);
    DSP2_WDR_Get_ROI_Weight(info->id, &info->weight);
    DSP2_WDR_Get_ROI_Position(info->id, &info->x_start, &info->x_end, &info->y_start, &info->y_end);

    return 0;
}

int bl_set_WDR_hist_roi_info(bl_dsp2_wdr_roi_info_t *info)
{
    DSP2_WDR_Set_ROI_State(info->id, info->state);
    DSP2_WDR_Set_ROI_Weight(info->id, info->weight);
    DSP2_WDR_Set_ROI_Position(info->id, info->x_start, info->x_end, info->y_start, info->y_end);
    return 0;
}

int bl_get_WDR_hist_data(bl_dsp2_wdr_hist_data_t *data)
{
    DSP2_WDR_Hist_Data_Type hist;
    DSP2_WDR_Get_Hist_Data(&hist);
    memcpy(data, &hist, sizeof(bl_dsp2_wdr_hist_data_t));
    return 0;
}

int bl_get_WDR_curve(bl_dsp2_wdr_curve_t *data)
{
    DSP2_WDR_Curve_Type wdr_curve;
    DSP2_WDR_Get_WDR_Curve(&wdr_curve);
    memcpy(data, &wdr_curve,  sizeof(uint16_t) * DSP2_WDR_CURVE_COEF_NUM);
    return 0;
}

int bl_set_WDR_curve(bl_dsp2_wdr_curve_t *data)
{
    DSP2_WDR_Curve_Type wdr_curve;
    memcpy(&wdr_curve, data, sizeof(uint16_t) * DSP2_WDR_CURVE_COEF_NUM);
    DSP2_WDR_Set_WDR_Curve(&wdr_curve);
    return 0;
}

int bl_get_WDR_curve_weight(int *weight)
{
    DSP2_WDR_Get_WDR_Curve_Weight(weight);
    return 0;
}

int bl_set_WDR_curve_weight(int weight)
{
    DSP2_WDR_Set_WDR_Curve_Weight(weight);
    return 0;
}

int bl_get_WDR_enh(bl_dsp2_wdr_enh_t *conf)
{
    DSP2_WDR_Get_Post_Enhance_Weight(&conf->weight);
    DSP2_WDR_Get_Post_Enhance_Y_Offset(&conf->y_offset);
    DSP2_WDR_Get_Post_Enhance_Luma_Gain(&conf->y_gain);
    DSP2_WDR_Get_Post_Enhance_Chroma_Gain(&conf->c_gain);

    return 0;
}

int bl_set_WDR_enh(bl_dsp2_wdr_enh_t *conf)
{
    DSP2_WDR_Set_Post_Enhance_Weight(conf->weight);
    DSP2_WDR_Set_Post_Enhance_Y_Offset(conf->y_offset);
    DSP2_WDR_Set_Post_Enhance_Luma_Gain(conf->y_gain);
    DSP2_WDR_Set_Post_Enhance_Chroma_Gain(conf->c_gain);

    return 0;
}

int bl_get_WDR_cs(bl_dsp2_cs_conf_t *conf)
{
    DSP2_Chroma_Suppress_Type chromaSupprCfg;
    DSP2_WDR_Get_CS_Config(&chromaSupprCfg);

    conf->gain = chromaSupprCfg.gain;
    conf->grey_thr = chromaSupprCfg.grey_thr;
    conf->weight = chromaSupprCfg.weight;

    return 0;
}

int bl_set_WDR_cs(bl_dsp2_cs_conf_t *conf)
{
    DSP2_Chroma_Suppress_Type chromaSupprCfg;

    chromaSupprCfg.gain = conf->gain;
    chromaSupprCfg.grey_thr = conf->grey_thr;
    chromaSupprCfg.weight = conf->weight;

    DSP2_WDR_Set_CS_Config(&chromaSupprCfg);
    return 0;
}

int bl_dsp2_disable_blc_soft()
{
    DSP2_CLAMP_S cfg;

    cfg.clamp_b = 0;
    cfg.clamp_gb = 0;
    cfg.clamp_gr = 0;
    cfg.clamp_r = 0;
    DSP2_Set_BLC(&cfg);

    return 0;
}

int bl_get_BLC_ob(int *ob)
{
    DSP2_CLAMP_S clamp;
    DSP2_Get_BLC(&clamp);
    *ob = clamp.clamp_gr;

    return 0;
}

int bl_set_BLC_ob(int ob)
{
    DSP2_CLAMP_S clamp;
    clamp.clamp_b = ob;
    clamp.clamp_gb = ob;
    clamp.clamp_gr = ob;
    clamp.clamp_r = ob;
    DSP2_Set_BLC(&clamp);
    return 0;
}

int bl_get_BNR_state(BL_Fun_Type *state)
{
    DSP2_Get_BNR_State(state);
    return 0;
}

int bl_set_BNR_state(BL_Fun_Type state)
{
    DSP2_Set_BNR_State(state);
    return 0;
}

int bl_get_BNR_weight(int *weight)
{
    DSP2_Get_BNR_Weight(weight);
    return 0;
}

int bl_set_BNR_weight(int weight)
{
    DSP2_Set_BNR_Weight(weight);
    return 0;
}

int bl_get_BNR_lpf_weight(int *weight)
{
    DSP2_Get_BNR_LPF_Weight(weight);
    return 0;
}

int bl_set_BNR_lpf_weight(int weight)
{
    DSP2_Set_BNR_LPF_Weight(weight);
    return 0;
}

int bl_get_BNR_threshold(bl_dsp2_bnr_thr_t *thr)
{
    DSP2_BNR_THRESHOLD_TYPE value;
    DSP2_Get_BNR_Threshold(&value);
    thr->th_base_r = value.th_base_r;
    thr->th_base_g = value.th_base_g;
    thr->th_base_b = value.th_base_b;
    thr->th_slope_r = value.th_slope_r;
    thr->th_slope_g = value.th_slope_g;
    thr->th_slope_b = value.th_slope_b;
    thr->slope_gain = value.slope_gain;

    return 0;
}

int bl_set_BNR_threshold(bl_dsp2_bnr_thr_t *thr)
{
    DSP2_BNR_THRESHOLD_TYPE value;
    value.th_base_r = thr->th_base_r;
    value.th_base_g = thr->th_base_g;
    value.th_base_b = thr->th_base_b;
    value.th_slope_r = thr->th_slope_r;
    value.th_slope_g = thr->th_slope_g;
    value.th_slope_b = thr->th_slope_b;
    value.slope_gain = thr->slope_gain;

    DSP2_Set_BNR_Threshold(&value);
    return 0;
}

int bl_get_BNR_fallback(bl_dsp2_bnr_fb_t *fb)
{
    DSP2_BNR_FALLBACK_TYPE value;

    DSP2_Get_BNR_Fallback(&value);
    fb->fb_level = value.fb_level;
    fb->fb_lpf_weight = value.fb_lpf_weight;

    return 0;
}

int bl_set_BNR_fallback(bl_dsp2_bnr_fb_t *fb)
{
    DSP2_BNR_FALLBACK_TYPE value;
    value.fb_level = fb->fb_level;
    value.fb_lpf_weight = fb->fb_lpf_weight;
    DSP2_Set_BNR_Fallback(&value);

    return 0;
}

int bl_get_DPC_state(BL_Fun_Type *state)
{
    DSP2_Get_DPC_State(state);
    return 0;
}

int bl_set_DPC_state(BL_Fun_Type state)
{
    DSP2_Set_DPC_State(state);
    return 0;
}

int bl_get_DPC_conf(bl_dsp2_dpc_thr_t *conf)
{
    DSP2_DPC_THRESHOLD_GROUP_TYPE dpc_reg;

    DSP2_Get_Defect_Correction_Threshold_Group(&dpc_reg);
    conf->thr_1 = dpc_reg.data[0];
    conf->thr_2 = dpc_reg.data[1];

    return 0;
}

int bl_set_DPC_conf(bl_dsp2_dpc_thr_t *conf)
{
    DSP2_DPC_THRESHOLD_GROUP_TYPE dpc_reg;

    dpc_reg.data[0] = conf->thr_1;
    dpc_reg.data[1] = conf->thr_2;
    dpc_reg.data[2] = 50;
    dpc_reg.data[3] = 50;
    dpc_reg.data[4] = 20;

    DSP2_Set_Defect_Correction_Threshold_Group(&dpc_reg);

    return 0;
}

int bl_get_LSC_state(BL_Fun_Type *state)
{
    DSP2_Get_LSC_State(state);
    return 0;
}

int bl_set_LSC_state(BL_Fun_Type state)
{
    DSP2_Set_LSC_State(state);
    return 0;
}

int bl_get_LSC_conf(bl_dsp2_lsc_conf_t *conf)
{
    DSP2_Get_LSC_Coeff_Type(0, (DSP2_LSC_COEF_TYPE *)&(conf->coef.r));
    DSP2_Get_LSC_Coeff_Type(1, (DSP2_LSC_COEF_TYPE *)&(conf->coef.g));
    DSP2_Get_LSC_Coeff_Type(2, (DSP2_LSC_COEF_TYPE *)&(conf->coef.b));
    DSP2_Get_LSC_Max((DSP2_LSC_MAX_S *)&(conf->max));

    return 0;
}

int bl_set_LSC_conf(bl_dsp2_lsc_conf_t *conf)
{
    DSP2_Set_LSC_Coeff_Type(0, (DSP2_LSC_COEF_TYPE *)&(conf->coef.r));
    DSP2_Set_LSC_Coeff_Type(1, (DSP2_LSC_COEF_TYPE *)&(conf->coef.g));
    DSP2_Set_LSC_Coeff_Type(2, (DSP2_LSC_COEF_TYPE *)&(conf->coef.b));
    DSP2_Set_LSC_Max((DSP2_LSC_MAX_S *)&(conf->max));

    return 0;
}

int bl_dsp2_disable_dg_soft()
{
    int r_gain = 4096;
    int gr_gain = 4096;
    int gb_gain = 4096;
    int b_gain = 4096;

    DSP2_Set_Digital_Gain(r_gain, gr_gain, gb_gain, b_gain);

    return 0;
}

int bl_get_DG_conf(bl_dsp2_bayer_gain_t *conf)
{
    int r_gain, gr_gain, gb_gain, b_gain;

    DSP2_Get_Digital_Gain(&r_gain, &gr_gain, &gb_gain, &b_gain);
    conf->r_gain = r_gain;
    conf->gr_gain = gr_gain;
    conf->gb_gain = gb_gain;
    conf->b_gain = b_gain;

    return 0;
}

int bl_set_DG_conf(bl_dsp2_bayer_gain_t *conf)
{
    DSP2_Set_Digital_Gain(conf->r_gain, conf->gr_gain, conf->gb_gain, conf->b_gain);
    return 0;
}

int bl_get_CCM_state(BL_Fun_Type *state)
{
    DSP2_Get_CCM_State(state);
    return 0;
}

int bl_set_CCM_state(BL_Fun_Type state)
{
    if (BL_DAY_MODE == day_night_mode) {
    DSP2_Set_CCM_State(state);
    } else {
        DSP2_Set_CCM_State( (BL_Fun_Type)0 );
    }

    return 0;
}

int bl_get_CCM_conf(bl_dsp2_ccm_coef_s *coef)
{
    DSP2_Get_CCM_Coef((DSP2_CCM_COEF_S*)coef);
    return 0;
}

int bl_set_CCM_conf(bl_dsp2_ccm_coef_s *coef)
{
    DSP2_Set_CCM_Coef((DSP2_CCM_COEF_S*)coef);
    return 0;
}

int bl_get_GAMMA_state(BL_Fun_Type *state)
{
    DSP2_Get_Gamma_State(state);
    return 0;
}

int bl_set_GAMMA_state(BL_Fun_Type state)
{
    DSP2_Set_Gamma_State(state);
    return 0;
}

int bl_get_GAMMA_curve(bl_dsp2_gamma_curve_t *curve)
{
    DSP2_Get_Gamma_Coef((DSP2_Gamma_Curve_Type*)curve);
    return 0;
}

int bl_set_GAMMA_curve(bl_dsp2_gamma_curve_t *curve)
{
    DSP2_Set_Gamma_Coef((DSP2_Gamma_Curve_Type*)curve);
    return 0;
}

int bl_dsp2_disable_saturation_soft()
{
    bl_dsp2_set_saturation(128);

    return 0;
}

int bl_dsp2_get_saturation(uint32_t *saturation)
{
    DSP2_SATURATION_S satCfg;

    DSP2_Get_Saturation(&satCfg);
    *saturation = satCfg.saturation_cb;

    return 0;
}

int bl_dsp2_set_saturation(uint32_t saturation)
{
    DSP2_SATURATION_S satCfg;

    if (BL_DAY_MODE == day_night_mode) {
        satCfg.saturation_cb = saturation;
        satCfg.saturation_cr = saturation;
        DSP2_Set_Saturation(&satCfg);
    } else {
        satCfg.saturation_cb = 0;
        satCfg.saturation_cr = 0;
        DSP2_Set_Saturation(&satCfg);
    }

    return 0;
}

int bl_get_EE_state(BL_Fun_Type *state)
{
    DSP2_Get_EE_State(state);
    return 0;
}

int bl_set_EE_state(BL_Fun_Type state)
{
    DSP2_Set_EE_State(state);
    return 0;
}

int bl_get_EE_conf(bl_dsp2_ee_conf_t *conf)
{
    BL_Fun_Type state;

    DSP2_Get_EEOverShoot_State(&state);
    if (state == ENABLE) conf->over_sht_state = ENABLE;
    else conf->over_sht_state = DISABLE;

    DSP2_Get_EE_Strength((DSP2_EE_Str_Type*)&(conf->str));
    DSP2_Get_EE_Thresh((DSP2_EE_Thresh_Type*)&(conf->thr));
    return 0;
}
int bl_set_EE_conf(bl_dsp2_ee_conf_t *conf)
{
    BL_Fun_Type state;

    if (conf->over_sht_state == 1) state = ENABLE;
    else state = DISABLE;
    DSP2_Set_EEOverShoot_State(state);
    DSP2_Set_EE_Strength((DSP2_EE_Str_Type*)&(conf->str));
    DSP2_Set_EE_Thresh((DSP2_EE_Thresh_Type*)&(conf->thr));
    return 0;
}

int bl_get_EE_luma_weight(bl_dsp2_ee_luma_weight_t *conf)
{
    DSP2_Get_EE_LumaWeight((DSP2_EE_Luma_Weight_Type*)conf);
    return 0;
}

int bl_set_EE_luma_weight(bl_dsp2_ee_luma_weight_t *conf)
{
    DSP2_Set_EE_LumaWeight((DSP2_EE_Luma_Weight_Type*)conf);
    return 0;
}

int bl_dsp2_disable_nr_soft()
{
    DSP2_Set_Noise_Level(0);

    return 0;
}

int bl_get_NR_conf(bl_dsp2_nr_conf_t *conf)
{
    DSP2_Get_Noise_Level((int *)&conf->noise_level);
    DSP2_Get_2D_NR((int *)&conf->filt_str_2d);
    DSP2_Get_3D_NR((int *)&conf->filt_str_3d);
    return 0;
}

int bl_set_NR_conf(bl_dsp2_nr_conf_t *conf)
{
    DSP2_Set_Noise_Level((int)conf->noise_level);
    DSP2_Set_2D_NR((int)conf->filt_str_2d);
    DSP2_Set_3D_NR((int)conf->filt_str_3d);
    return 0;
}

int bl_get_CS_state(BL_Fun_Type *state)
{
    DSP2_Get_ChromaSuppress_State(state);
    return 0;
}

int bl_set_CS_state(BL_Fun_Type state)
{
    DSP2_Set_ChromaSuppress_State(state);
    return 0;
}

int bl_get_CS_conf(bl_dsp2_cs_conf_t *conf)
{
    DSP2_Get_ChromaSuppress((DSP2_Chroma_Suppress_Type*)conf);
    return 0;
}

int bl_set_CS_conf(bl_dsp2_cs_conf_t *conf)
{
    DSP2_Set_ChromaSuppress((DSP2_Chroma_Suppress_Type*)conf);
    return 0;
}

int bl_dsp2_disable_yc_soft()
{
    bl_dsp2_yc_conf_t conf;

    conf.brightness = 128;
    conf.contrast = 0;
    bl_set_YC_conf(&conf);

    return 0;
}

int bl_get_YC_conf(bl_dsp2_yc_conf_t *conf)
{
    int brightness = 0;
    int contrast = 0;

    DSP2_Get_Brightness(&brightness);
    DSP2_Get_Contrast(&contrast);

    conf->brightness = brightness + 128;
    conf->contrast = contrast;

    return 0;
}

int bl_set_YC_conf(bl_dsp2_yc_conf_t *conf)
{
    int brightness = conf->brightness - 128;
    DSP2_Set_Brightness(brightness);
    DSP2_Set_Contrast((int)conf->contrast);
    return 0;
}

int bl_dsp2_disable_af_soft()
{
    bl_dsp2_af_conf_t conf;
    bl_dsp2_af_win_t win_conf;

    conf.fcore1 = 0;
    conf.fcore2 = 0;
    bl_set_AF_conf(&conf);

    win_conf.start_x = 0;
    win_conf.end_x = 0;
    win_conf.start_y = 0;
    win_conf.end_y = 0;
    win_conf.sum_shift = 0;
    bl_set_AF_win_conf(BL_DSP2_AF_WIN_A, &win_conf);
    bl_set_AF_win_conf(BL_DSP2_AF_WIN_B, &win_conf);

    return 0;
}


int bl_get_AF_stats(bl_dsp2_af_stats_t *conf)
{
    dsp2_af_stats_conf_t afStats;

    DSP2_Get_AF_Stats(&afStats);
    conf->wa_hpf1_sum = afStats.wa_hpf1_sum;
    conf->wa_hpf2_sum = afStats.wa_hpf2_sum;
    conf->wb_hpf1_sum = afStats.wb_hpf1_sum;
    conf->wb_hpf2_sum = afStats.wb_hpf2_sum;

    return 0;
}

int bl_get_AF_conf(bl_dsp2_af_conf_t *conf)
{
    DSP2_AF_CONF_Type afCfg;

    DSP2_Get_AF_Stats_Conf(&afCfg);
    conf->gamma_pattern = afCfg.gamma_pattern;
    conf->fcore1 = afCfg.fcore1;
    conf->fcore2 = afCfg.fcore2 ;

    return 0;
}

int bl_set_AF_conf( bl_dsp2_af_conf_t *conf)
{
    DSP2_AF_CONF_Type afCfg;

    afCfg.gamma_pattern = conf->gamma_pattern;
    afCfg.fcore1 = conf->fcore1;
    afCfg.fcore2  = conf->fcore2 ;

    DSP2_Set_AF_Stats_Conf(&afCfg);

    return 0;
}

int bl_get_AF_win_conf(int win_idx, bl_dsp2_af_win_t *conf)
{
    DSP2_AF_WINDOW_Type afWinCfg;

    if (win_idx == BL_DSP2_AF_WIN_A) {
        DSP2_Get_AF_Window_A(&afWinCfg);
    } else if (win_idx == BL_DSP2_AF_WIN_B) {
        DSP2_Get_AF_Window_B(&afWinCfg);
    } else return -1;

    conf->start_x = afWinCfg.start_x;
    conf->start_y = afWinCfg.start_y;
    conf->end_x = afWinCfg.end_x;
    conf->end_y = afWinCfg.end_y;
    conf->sum_shift = afWinCfg.sum_shift;
    return 0;
}

int bl_set_AF_win_conf(int win_idx, bl_dsp2_af_win_t *conf)
{
    DSP2_AF_WINDOW_Type afWinCfg;

    afWinCfg.start_x = conf->start_x;
    afWinCfg.start_y = conf->start_y;
    afWinCfg.end_x = conf->end_x;
    afWinCfg.end_y = conf->end_y;
    afWinCfg.sum_shift = conf->sum_shift;

    if (win_idx == BL_DSP2_AF_WIN_A) {
        DSP2_Set_AF_Window_A(&afWinCfg);
    } else if (win_idx == BL_DSP2_AF_WIN_B) {
        DSP2_Set_AF_Window_B(&afWinCfg);
    } else return -1;

    return 0;
}

int bl_get_addr_data(uint32_t addr,uint32_t *data)
{
    uint32_t tmpVal;
    tmpVal = BL_RD_WORD(addr);
    *data = tmpVal;

    return 0;
}

int bl_set_addr_data(uint32_t addr,uint32_t data)
{
    BL_WR_WORD(addr, data);

    return 0;
}


