#include <mjdec_reg.h>
#include <bl808_mjdec.h>
#include "bl_mjdec.h"

#undef  DEBUG_MODULE
#define DEBUG_MODULE 1

#define NV12_IMAGE_SIZE(width,height)   ((width)*(height)*3/2)


typedef struct {
    uint16_t width;
    uint16_t height;
} mjdec_config_t;

typedef struct {
    bl_mjdec_frame_cb frame_cb;
    void *userData;
} MJDec_Handle_Cfg_Type;


static mjdec_config_t mjdec_config;
static MJDec_Handle_Cfg_Type MJDec_Handl_Cfg;

static void do_handle_decoded_frame_done(void)
{
    mjdec_frame_desc_t frame_desc;
    uint8_t *frame_start_addr;
    uint32_t frame_size;
    frame_start_addr = (uint8_t*)BL_RD_REG(MJPEG_ENC_BASE, MJDEC_JDEC_YY_FRAME_ADDR);
    frame_size = NV12_IMAGE_SIZE(mjdec_config.width, mjdec_config.height);

    frame_desc.frame_start_addr = frame_start_addr;
    frame_desc.frame_size = frame_size;

    if (MJDec_Handl_Cfg.frame_cb) {
        MJDec_Handl_Cfg.frame_cb(MJDec_Handl_Cfg.userData, &frame_desc);
    }

    MJDEC_StopDec();
}

int bl_mjdec_init(void)
{
    MJDEC_Init();

    Interrupt_Handler_Register(MJDEC_IRQn, MJDEC_IRQHandler);
    System_NVIC_SetPriority(MJDEC_IRQn, 7, 1);
    CPU_Interrupt_Enable(MJDEC_IRQn);

    return 0;
}

int bl_mjdec_set_config(bl_mjdec_config_t *config)
{
    MJDEC_SetYuvFormat(MJDEC_YUV420_PLANAR);  /* NV12 format */
    MJDEC_SetResolution(config->width, config->height);
    MJDEC_SetQuality((MJDEC_Quant_Mode_Type)config->quality);

    //MJDEC_PushSrcFrame(config->input_buf_addr);
    MJDEC_SetYFrameAddr((uint32_t)config->output_buf_addr);
    MJDEC_SetUVFrameAddr((uint32_t)(config->output_buf_addr + config->width * config->height));

    /* save the resolution info */
    mjdec_config.width = config->width;
    mjdec_config.height = config->height;

    return 0;
}

int bl_mjdec_start_decoder(uint8_t *jpeg_buf_addr)
{
    MJDEC_StartDec();
    MJDEC_PushSrcFrame((uint32_t)jpeg_buf_addr);

    return 0;
}

void MJDEC_IRQHandler(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_DEC_BASE, MJDEC_JDEC_CONTROL_3);
    MJDEC_ClearIntrFlag();

    if (BL_IS_REG_BIT_SET(tmpVal, MJDEC_STS_NORMAL_INT)) {
        do_handle_decoded_frame_done();
        BL_LOGD("MJDEC frame done.\r\n");
    }

    if (BL_IS_REG_BIT_SET(tmpVal, MJDEC_STS_IDLE_INT)) {
        BL_LOGI("MJDEC enter idle.\r\n");
    }
}

int bl_mjdec_set_callback(bl_mjdec_frame_cb frame_cb, void *usrdata)
{
    MJDec_Handl_Cfg.frame_cb = frame_cb;
    MJDec_Handl_Cfg.userData = usrdata;

    return 0;
}

