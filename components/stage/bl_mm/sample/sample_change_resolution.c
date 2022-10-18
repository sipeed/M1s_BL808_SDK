#include <FreeRTOS.h>
#include <aos/kernel.h>
#include "bl808_common.h"
#include "sample_common.h"
#include "sample_app.h"

#define VIDEO_STREAM_ID 0

void sample_change_resolution_main()
{
    int ret = -1;
    uint32_t width = 0, height = 0;

    ret = sample_system_init();
    if (ret) {
        BL_LOGE("Sample system init fail!!\r\n");
        return;
    }

    ret = sample_encoder_init();
    if (ret) {
        BL_LOGE("Video codec init fail!!\r\n");
        return;
    }

    /* Set resolution */
    width = 1920;
    height = 1080;
    ret = sample_set_chann_resolution(VIDEO_STREAM_ID, width, height);
    if (ret) {
        BL_LOGE("Set resolution fail!!\r\n");
        return;
    }
    BL_LOGI("Resolution width:%d height:%d\r\n", width, height);

    aos_task_new((char*)"Video stream handle task", h264_change_resolution_task, (void *)VIDEO_STREAM_ID, 1024);

    sample_start_stream(VIDEO_STREAM_ID);
}
