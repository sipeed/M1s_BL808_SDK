#include <FreeRTOS.h>
#include <aos/kernel.h>
#include "bl808_common.h"
#include "sample_common.h"
#include "sample_app.h"

#define VIDER_STREAM_ID 0

void sample_set_fps_main()
{
    int ret = -1;
    uint32_t fps;

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

    /* Set fps */
    fps = 5;
    ret = sample_set_chann_frame_rate(VIDER_STREAM_ID, fps);
    if (ret) {
        BL_LOGE("Set resolution fail!!\r\n");
        return;
    }
    BL_LOGI("[Sample]Set fps:%d\r\n", fps);

    /* Change fps task */
    aos_task_new((char*)"Video stream handle task", h264_change_fps_task, (void *)VIDER_STREAM_ID, 1024);

    sample_start_stream(VIDER_STREAM_ID);
}
