#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <aos/kernel.h>
#include <vfs.h>
#include <cli.h>
#include "bl808_codec_misc.h"
#include "bl808_common.h"
#include "bl808_dsp2_misc.h"
#include "bl-api-osd.h"
#include "blai_core.h"
#include "blai_inst_postprocess.h"
#include "helper_pf_det.h"
#include "mm_dsp2.h"

#define INPUT_FROM_DSP2      (1)
#define DSP2_DUMP_PORT_ID    (3)

#define MODEL_SEL           (4)
#define MODEL_USE_NPU_API   (0)
#define CHECK_MEMLEAK
#define INPUT_FORMAT_RGBX
//#define BLAI_OSD_SUPPORT
#ifdef BLAI_OSD_SUPPORT
#define LOCAL_OSD_ENABLE
#endif

#ifdef LOCAL_OSD_ENABLE
#include "bl-osd-app.h"
#endif

#if (MODEL_SEL == 0)
#if (MODEL_USE_NPU_API == 0)
#include <models/bl_dv4.h>
#else
#include <models/npu_api/bl_dv4.h>
#endif
#elif (MODEL_SEL == 1)
#if (MODEL_USE_NPU_API == 0)
#include <models/bl_dv5.h>
#else
#include <models/npu_api/bl_dv5.h>
#endif
#elif (MODEL_SEL == 2)
#if (MODEL_USE_NPU_API == 0)
#include <models/mobilenet_ssd_tflite.h>
#else
#include <models/npu_api/mobilenet_ssd_tflite.h>
#endif
#elif (MODEL_SEL == 3)
#if (MODEL_USE_NPU_API == 0)
#include <models/mbv2_yolov3_bl_nano_voc.h>
#else
#include <models/npu_api/mbv2_yolov3_bl_nano_voc.h>
#endif
#elif (MODEL_SEL == 4)
#if (MODEL_USE_NPU_API == 0)
#include <models/yoloface.h>
#else
#include <models/npu_api/yoloface.h>
#endif
#elif (MODEL_SEL == 5)
#if (MODEL_USE_NPU_API == 0)
#include <models/yolov4_bl_tiny_ng.h>
#else
#include <models/npu_api/yolov4_bl_tiny_ng.h>
#endif
#elif (MODEL_SEL == 6)
#if (MODEL_USE_NPU_API == 0)
#include <models/inception_v_1_224_quant_tflite.h>
#else
#include <models/npu_api/inception_v_1_224_quant_tflite.h>
#endif
#elif (MODEL_SEL == 7)
#if (MODEL_USE_NPU_API == 0)
#include <models/mbv2_1_224_quant_tflite.h>
#else
#include <models/npu_api/mbv2_1_224_quant_tflite.h>
#endif
#elif (MODEL_SEL == 8)
#if (MODEL_USE_NPU_API == 0)
#include <models/mbv2_yolov3_facelandmark.h>
#else
#include <models/npu_api/mbv2_yolov3_facelandmark.h>
#endif
#elif (MODEL_SEL == 9)
#include <models/arcface_blsfc.h>
#elif (MODEL_SEL == 10)
#include <models/dscnn_l_tflite.h>
#elif (MODEL_SEL == 11)
#include <models/ds_cnn_48x20.h>
#elif (MODEL_SEL == 12)
#include <models/mnas_tflite.h>
#elif (MODEL_SEL == 13)
#include <models/squeezenet_tflite.h>
#else
#error "Unspecified MODEL_SEL"
#endif

//uint8_t detect_msg[101];
static int detect_msg_idx = 0;
#define MAX_DISPLAY_LAYER_CNT   (4)

static ai_draw_cb ai_draw = NULL;

#define MSB_BYTE_ORDER(x)                  (x >> 8)
#define LSB_BYTE_ORDER(x)                  (x & 0xff)


#if INPUT_FROM_DSP2
static int img_width  = 1920;
static int img_height = 1080;
#else
static int img_width  = 640;
static int img_height = 422;
#endif

static int g_blai_task_started = 0;

static const char* g_landmark_str[5] = {
    "left eye",
    "right eye",
    "nose",
    "left mouth",
    "right mouth"
};

#if (BLAI_POSTPROCESS_TYPE != 0)
static void blai_result_handler(struct blai_result_t* result)
{
    if (detect_msg_idx >= MAX_DISPLAY_LAYER_CNT)
        return;

	switch (result->app_type) {
		case OBJECT_DETECTION:
            BL_LOGD("[Result CB][OBJECT_DETECTION] %s(%.0f%%), x: %d, y: %d, width: %d, height: %d\r\n", g_detNames[result->r.objdet.best_class], result->r.objdet.prob, result->r.objdet.rect.x, result->r.objdet.rect.y, result->r.objdet.rect.w, result->r.objdet.rect.h);
            detect_msg[ 1 + detect_msg_idx * 10] = result->r.objdet.best_class;
            detect_msg[ 2 + detect_msg_idx * 10] = (uint8_t) result->r.objdet.prob;
            detect_msg[ 3 + detect_msg_idx * 10] = (uint8_t)MSB_BYTE_ORDER(((uint16_t)result->r.objdet.rect.x));
            detect_msg[ 4 + detect_msg_idx * 10] = (uint8_t)LSB_BYTE_ORDER(((uint16_t)result->r.objdet.rect.x));
            detect_msg[ 5 + detect_msg_idx * 10] = (uint8_t)MSB_BYTE_ORDER(((uint16_t)result->r.objdet.rect.y));
            detect_msg[ 6 + detect_msg_idx * 10] = (uint8_t)LSB_BYTE_ORDER(((uint16_t)result->r.objdet.rect.y));
            detect_msg[ 7 + detect_msg_idx * 10] = (uint8_t)MSB_BYTE_ORDER(((uint16_t)result->r.objdet.rect.w));
            detect_msg[ 8 + detect_msg_idx * 10] = (uint8_t)LSB_BYTE_ORDER(((uint16_t)result->r.objdet.rect.w));
            detect_msg[ 9 + detect_msg_idx * 10] = (uint8_t)MSB_BYTE_ORDER(((uint16_t)result->r.objdet.rect.h));
            detect_msg[10 + detect_msg_idx * 10] = (uint8_t)LSB_BYTE_ORDER(((uint16_t)result->r.objdet.rect.h));
            detect_msg_idx++;
			break;
		case CLASSIFICATION:
            BL_LOGD("[Result CB][CLASSIFICATION] output: %s\r\n", g_detNames[result->r.classification.best_class]);
			break;
		case FACE_RECONGNITION:
            BL_LOGD("[Result CB][FACE_RECONGNITION] output: %s\r\n", g_detNames[result->r.fr.best_class]);
			break;
		case FACE_LANDMARK:
            BL_LOGD("[Result CB][OBJECT_DETECTION] %s(%.0f%%), x: %d, y: %d, width: %d, height: %d\r\n", g_detNames[result->r.landmark.best_class], result->r.landmark.prob, result->r.landmark.rect.x, result->r.landmark.rect.y, result->r.landmark.rect.w, result->r.landmark.rect.h);
            BL_LOGD("%s(%d,%d), %s(%d,%d), %s(%d,%d), %s(%d,%d), %s(%d,%d)\r\n",
                g_landmark_str[result->r.landmark.lx1.pos], result->r.landmark.lx1.x, result->r.landmark.lx1.y,
                g_landmark_str[result->r.landmark.lx2.pos], result->r.landmark.lx2.x, result->r.landmark.lx2.y,
                g_landmark_str[result->r.landmark.lx3.pos], result->r.landmark.lx3.x, result->r.landmark.lx3.y,
                g_landmark_str[result->r.landmark.lx4.pos], result->r.landmark.lx4.x, result->r.landmark.lx4.y,
                g_landmark_str[result->r.landmark.lx5.pos], result->r.landmark.lx5.x, result->r.landmark.lx5.y);
            detect_msg[ 1 + detect_msg_idx * 10] = result->r.landmark.best_class;
            detect_msg[ 2 + detect_msg_idx * 10] = (uint8_t) result->r.landmark.prob;
            detect_msg[ 3 + detect_msg_idx * 10] = (uint8_t)MSB_BYTE_ORDER(((uint16_t)result->r.landmark.rect.x));
            detect_msg[ 4 + detect_msg_idx * 10] = (uint8_t)LSB_BYTE_ORDER(((uint16_t)result->r.landmark.rect.x));
            detect_msg[ 5 + detect_msg_idx * 10] = (uint8_t)MSB_BYTE_ORDER(((uint16_t)result->r.landmark.rect.y));
            detect_msg[ 6 + detect_msg_idx * 10] = (uint8_t)LSB_BYTE_ORDER(((uint16_t)result->r.landmark.rect.y));
            detect_msg[ 7 + detect_msg_idx * 10] = (uint8_t)MSB_BYTE_ORDER(((uint16_t)result->r.landmark.rect.w));
            detect_msg[ 8 + detect_msg_idx * 10] = (uint8_t)LSB_BYTE_ORDER(((uint16_t)result->r.landmark.rect.w));
            detect_msg[ 9 + detect_msg_idx * 10] = (uint8_t)MSB_BYTE_ORDER(((uint16_t)result->r.landmark.rect.h));
            detect_msg[10 + detect_msg_idx * 10] = (uint8_t)LSB_BYTE_ORDER(((uint16_t)result->r.landmark.rect.h));
            detect_msg_idx++;
            detect_msg[ 1 + detect_msg_idx * 10] = 1;
            detect_msg[ 2 + detect_msg_idx * 10] = (uint8_t) 0;
            detect_msg[ 3 + detect_msg_idx * 10] = (uint8_t)MSB_BYTE_ORDER(((uint16_t)result->r.landmark.lx1.x));
            detect_msg[ 4 + detect_msg_idx * 10] = (uint8_t)LSB_BYTE_ORDER(((uint16_t)result->r.landmark.lx1.x));
            detect_msg[ 5 + detect_msg_idx * 10] = (uint8_t)MSB_BYTE_ORDER(((uint16_t)result->r.landmark.lx1.y));
            detect_msg[ 6 + detect_msg_idx * 10] = (uint8_t)LSB_BYTE_ORDER(((uint16_t)result->r.landmark.lx1.y));

            detect_msg[ 7 + detect_msg_idx * 10] = (uint8_t)0;
            detect_msg[ 8 + detect_msg_idx * 10] = (uint8_t)4;
            detect_msg[ 9 + detect_msg_idx * 10] = (uint8_t)0;
            detect_msg[10 + detect_msg_idx * 10] = (uint8_t)4;
            detect_msg_idx++;
            detect_msg[ 1 + detect_msg_idx * 10] = 2;
            detect_msg[ 2 + detect_msg_idx * 10] = (uint8_t) 0;
            detect_msg[ 3 + detect_msg_idx * 10] = (uint8_t)MSB_BYTE_ORDER(((uint16_t)result->r.landmark.lx2.x));
            detect_msg[ 4 + detect_msg_idx * 10] = (uint8_t)LSB_BYTE_ORDER(((uint16_t)result->r.landmark.lx2.x));
            detect_msg[ 5 + detect_msg_idx * 10] = (uint8_t)MSB_BYTE_ORDER(((uint16_t)result->r.landmark.lx2.y));
            detect_msg[ 6 + detect_msg_idx * 10] = (uint8_t)LSB_BYTE_ORDER(((uint16_t)result->r.landmark.lx2.y));
            detect_msg[ 7 + detect_msg_idx * 10] = (uint8_t)0;
            detect_msg[ 8 + detect_msg_idx * 10] = (uint8_t)4;
            detect_msg[ 9 + detect_msg_idx * 10] = (uint8_t)0;
            detect_msg[10 + detect_msg_idx * 10] = (uint8_t)4;
            detect_msg_idx++;
            detect_msg[ 1 + detect_msg_idx * 10] = 3;
            detect_msg[ 2 + detect_msg_idx * 10] = (uint8_t) 0;
            detect_msg[ 3 + detect_msg_idx * 10] = (uint8_t)MSB_BYTE_ORDER(((uint16_t)result->r.landmark.lx3.x));
            detect_msg[ 4 + detect_msg_idx * 10] = (uint8_t)LSB_BYTE_ORDER(((uint16_t)result->r.landmark.lx3.x));
            detect_msg[ 5 + detect_msg_idx * 10] = (uint8_t)MSB_BYTE_ORDER(((uint16_t)result->r.landmark.lx3.y));
            detect_msg[ 6 + detect_msg_idx * 10] = (uint8_t)LSB_BYTE_ORDER(((uint16_t)result->r.landmark.lx3.y));

            detect_msg[ 7 + detect_msg_idx * 10] = (uint8_t)0;
            detect_msg[ 8 + detect_msg_idx * 10] = (uint8_t)4;
            detect_msg[ 9 + detect_msg_idx * 10] = (uint8_t)0;
            detect_msg[10 + detect_msg_idx * 10] = (uint8_t)4;
            detect_msg_idx++;
            detect_msg[ 1 + detect_msg_idx * 10] = 4;
            detect_msg[ 2 + detect_msg_idx * 10] = (uint8_t) 0;
            detect_msg[ 3 + detect_msg_idx * 10] = (uint8_t)MSB_BYTE_ORDER(((uint16_t)result->r.landmark.lx4.x));
            detect_msg[ 4 + detect_msg_idx * 10] = (uint8_t)LSB_BYTE_ORDER(((uint16_t)result->r.landmark.lx4.x));
            detect_msg[ 5 + detect_msg_idx * 10] = (uint8_t)MSB_BYTE_ORDER(((uint16_t)result->r.landmark.lx4.y));
            detect_msg[ 6 + detect_msg_idx * 10] = (uint8_t)LSB_BYTE_ORDER(((uint16_t)result->r.landmark.lx4.y));
            detect_msg[ 7 + detect_msg_idx * 10] = (uint8_t)0;
            detect_msg[ 8 + detect_msg_idx * 10] = (uint8_t)4;
            detect_msg[ 9 + detect_msg_idx * 10] = (uint8_t)0;
            detect_msg[10 + detect_msg_idx * 10] = (uint8_t)4;
            detect_msg_idx++;
            detect_msg[ 1 + detect_msg_idx * 10] = 5;
            detect_msg[ 2 + detect_msg_idx * 10] = (uint8_t) 0;
            detect_msg[ 3 + detect_msg_idx * 10] = (uint8_t)MSB_BYTE_ORDER(((uint16_t)result->r.landmark.lx5.x));
            detect_msg[ 4 + detect_msg_idx * 10] = (uint8_t)LSB_BYTE_ORDER(((uint16_t)result->r.landmark.lx5.x));
            detect_msg[ 5 + detect_msg_idx * 10] = (uint8_t)MSB_BYTE_ORDER(((uint16_t)result->r.landmark.lx5.y));
            detect_msg[ 6 + detect_msg_idx * 10] = (uint8_t)LSB_BYTE_ORDER(((uint16_t)result->r.landmark.lx5.y));
            detect_msg[ 7 + detect_msg_idx * 10] = (uint8_t)0;
            detect_msg[ 8 + detect_msg_idx * 10] = (uint8_t)4;
            detect_msg[ 9 + detect_msg_idx * 10] = (uint8_t)0;
            detect_msg[10 + detect_msg_idx * 10] = (uint8_t)4;

            detect_msg_idx++;

			break;
		default:
			return;
	}
    detect_msg[0] = detect_msg_idx;
}
#endif

#if INPUT_FROM_DSP2
static int dsp2_dump_init(uint32_t width, uint32_t height)
{
    MMDSP2FrmSrcAttr frmsrc_attr;

#ifdef INPUT_FORMAT_RGBX
    /* Setting 8bit BT.601 YUV to RGB */
    DSP2_YUV2RGB_Init(DSP2_YUV2RGB_PARAM_8BIT_BT601);
    /* Make blai input data RGBX format */
    DSP2_YUV2RGB_Set_Input(DSP2_YUV2RGB_A, DSP2_YUV2RGB_INPUT_SCALER_D);
#endif

    MM_DSP2_GetFrameSrcChnAttr(DSP2_DUMP_PORT_ID, &frmsrc_attr);
    frmsrc_attr.picWidth = width;
    frmsrc_attr.picHeight = height;
    frmsrc_attr.dsp2Position = DSP2_POSITION_SCALER_D;
    MM_DSP2_SetFrameSrcChnAttr(DSP2_DUMP_PORT_ID, &frmsrc_attr);

    return 0;
}

static void dsp2_dump_uninit(void)
{
    MM_DSP2_StopRecvPic(DSP2_DUMP_PORT_ID);
}

static void dump_image(uint8_t *imgBuf, uint8_t bFirst)
{
    MMDSP2YuvFrame yuv_frame;
    if (bFirst) {
#ifdef INPUT_FORMAT_RGBX
        MM_DSP2_StartDumpPic(DSP2_DUMP_PORT_ID , PIX_FMT_RGB0, BL_IMAGE_DUMP_SRC_YUV2RGB);
#else
        MM_DSP2_StartDumpPic(DSP2_DUMP_PORT_ID , PIX_FMT_DATA8, BL_IMAGE_DUMP_SRC_SCALER_D);
#endif
    } else {
        MM_DSP2_ResumDumpPic(DSP2_DUMP_PORT_ID);
    }
    MM_DSP2_GetOnePicture(DSP2_DUMP_PORT_ID , &yuv_frame);
    MM_DSP2_PauseDumpPic(DSP2_DUMP_PORT_ID);

    memcpy(imgBuf, yuv_frame.frameStartAddr , yuv_frame.frameSize);
    csi_dcache_clean_range((uintptr_t *)imgBuf, (int32_t)yuv_frame.frameSize);
}
#endif

static void blai_inference_task(void *arg)
{
    blai_model_hdl_t blai_hdl;
    uint8_t* img_buf;
    uint32_t width = 0, height = 0;
    int bfirst = 1;

    CODEC_MISC_BLAI_Limit_RD(0x10f);
    CODEC_MISC_BLAI_Limit_WR(0x10f);

    BL_LOGI("blai_inference_task start, model = %d\r\n", MODEL_SEL);
#ifdef CHECK_MEMLEAK
    BL_LOGI("[MEM][Sart] Heap size: %lu bytes\r\n", xPortGetFreeHeapSize());
#endif
    blai_hdl = blai_create();

    blai_load_model_from_buffer(blai_hdl, blai_model_bin);

#if (BLAI_POSTPROCESS_TYPE == 1)
    load_postprocess_classification(blai_hdl, g_detNames, BLAI_DET_NAME_COUNT);
    blai_setResultCB(blai_hdl, blai_result_handler);
#ifdef BLAI_OSD_SUPPORT
    bl_osd_set_ai_detect_names(g_detNames);
#endif
#elif (BLAI_POSTPROCESS_TYPE == 2)
    load_postprocess_face_recongnition(blai_hdl, g_detNames, BLAI_DET_NAME_COUNT, g_feature_list, BALI_DET_FEATURE_NUM);
    blai_setResultCB(blai_hdl, blai_result_handler);
#ifdef BLAI_OSD_SUPPORT
    bl_osd_set_ai_detect_names(g_detNames);
#endif
#endif

#if (INPUT_FROM_DSP2 == 0)
#if (MODEL_SEL == 8) // yolo landmark
    int image_width = 267;
    int image_height = 267;
#else // (MODEL_SEL == 8)
	int image_width = 640;
	int image_height = 422;
#endif // (MODEL_SEL == 8)
    blai_setSourceResolution(blai_hdl, image_width, image_height);
#else (INPUT_FROM_DSP2 == 0)
    if (blai_getInputResolution(blai_hdl, &width, &height) != BLAI_STATUS_NO_ERROR) {
        BL_LOGE("[%s] Cannot get input resolution\r\n", __func__);
        goto exit;
    }

    if (dsp2_dump_init(width, height) < 0) {
        BL_LOGE("[%s] init dsp2 fail\r\n", __func__);
        goto exit;
    }

    MMDSP2FrmSrcAttr frmsrc_attr;
    MM_DSP2_GetFrameSrcChnAttr(0, &frmsrc_attr);
    blai_setSourceResolution(blai_hdl, frmsrc_attr.picWidth, frmsrc_attr.picHeight);

#ifdef BLAI_OSD_SUPPORT
#ifdef LOCAL_OSD_ENABLE
    bl_osd_init();
#endif // LOCAL_OSD_ENABLE
    bl_osd_ai_cb_register(&ai_draw);
#endif // BLAI_OSD_SUPPORT

#endif // (INPUT_FROM_DSP2 == 0)

    while (g_blai_task_started) {
        img_buf = blai_getInputBuffer(blai_hdl);

        if (img_buf == NULL) {
            BL_LOGE("img_buf unavailable\r\n");
            goto exit;
        }

        /* Prepare Input */
#if INPUT_FROM_DSP2
        dump_image(img_buf, bfirst);
        bfirst = 0;
#else
        memcpy(img_buf, img_bin, sizeof(img_bin));
        csi_dcache_clean_range((uintptr_t *)img_buf, (int32_t)sizeof(img_bin));
#endif
        detect_msg_idx = 0;
        memset(detect_msg, 0, sizeof(detect_msg));

        /* Start Inference */
        blai_startCompute(blai_hdl);

#if INPUT_FROM_DSP2
        if (ai_draw) {
            ai_draw(detect_msg);
        }
#else
        break;
#endif
    }
exit:
#if INPUT_FROM_DSP2
    dsp2_dump_uninit();
#endif
    /* Uninit handler */
    blai_free(blai_hdl);
#ifdef CHECK_MEMLEAK
    printf("[MEM][Stop] Heap size: %lu bytes\r\n", xPortGetFreeHeapSize());
#endif
    g_blai_task_started = 0;
    *(int *)arg = 0;
    vTaskDelete(NULL);
}

static void blai_cmd(char *buf, int len, int argc, char **argv)
{
    if (g_blai_task_started == 0) {
        g_blai_task_started = 1;
        BL_LOGI("create blai inference thread\r\n");
        xTaskCreate(blai_inference_task, "blai_inference_test", 4096, NULL, 10, NULL);
    } else {
        g_blai_task_started = 0;
        BL_LOGI("stop blai inference thread\r\n");
    }
}

const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
    { "pf_det", "PF detection", blai_cmd },
};

int helper_pf_det_cli_init(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user) / sizeof(cmds_user[0]));
    return 0;
}

