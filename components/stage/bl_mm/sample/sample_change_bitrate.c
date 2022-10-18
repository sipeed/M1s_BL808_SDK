#include <FreeRTOS.h>
#include <aos/kernel.h>
#include "bl808_common.h"
#include "sample_common.h"
#include "sample_app.h"

#define VIDER_STREAM_ID 0
void sample_change_bitrate_main()
{
    int ret = -1, bitrate = 0;
    int fps = 0;

    ret = sample_system_init();
    if (ret) {
        BL_LOGE("Sample system init fail!!\r\n");
        return;
    }

    /* Set default attr about codec, default Bitrate = 2.25Mbps */
    ret = sample_encoder_init();
    if (ret) {
        BL_LOGE("Video codec init fail!!\r\n");
        return;
    }

    /* Set fps,  Codec fps max val is 5 in fpga*/
    fps = 5;
    ret = sample_set_chann_frame_rate(VIDER_STREAM_ID, fps);
    if (ret) {
        BL_LOGE("Set resolution fail!!\r\n");
        return;
    }
    BL_LOGI("[Sample]Set fps:%d\r\n", fps);

    /* Set bitrate */
    bitrate = 1000000;
    ret = sample_set_chann_bit_rate(VIDER_STREAM_ID, bitrate);
    if (ret) {
        BL_LOGE("Set bitrate fail!!\r\n");
        return;
    }
    BL_LOGI("[Sample]Set bitrate:%d\r\n", bitrate);

    aos_task_new((char*)"Video stream handle task", h264_change_bitrate_task, (void *)VIDER_STREAM_ID, 1024);

    sample_start_stream(VIDER_STREAM_ID);
}
