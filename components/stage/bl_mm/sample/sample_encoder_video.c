#include <FreeRTOS.h>
#include <aos/kernel.h>
#include "bl808_common.h"
#include "sample_common.h"
#include "sample_app.h"

#define VIDER_STREAM_ID 0
void sample_encoder_video_main()
{
    int ret = -1;

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

    aos_task_new((char*)"Video stream handle task", h264_stream_handle_task, (void *)VIDER_STREAM_ID, 1024);

    sample_start_stream(VIDER_STREAM_ID);
}
