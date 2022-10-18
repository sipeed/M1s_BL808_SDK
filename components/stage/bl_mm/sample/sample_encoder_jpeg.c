#include <FreeRTOS.h>
#include <aos/kernel.h>
#include "bl808_common.h"
#include "sample_common.h"
#include "sample_app.h"

#define VIDER_STREAM_ID 2

void sample_encoder_jpeg_main()
{
    int ret = -1;
    TaskHandle_t task_handle = NULL;

    task_handle = xTaskGetCurrentTaskHandle();

    //ret = sample_system_init();
    ret = sample_system_mjpeg_init();
    if (ret) {
        BL_LOGE("Sample system init fail!!\r\n");
        return;
    }

    /* Wait dsp2 stable, then start mjpeg encoder */
    vTaskDelay(1000);

    ret = sample_encoder_init();
    if (ret) {
        BL_LOGE("Video codec init fail!!\r\n");
        return;
    }

    // Save data into sdcard
    //aos_task_new((char*)"Mjpeg stream handle task", jpeg_stream_handle_task, (void *)VIDER_STREAM_ID, 2048);

    sample_start_stream(VIDER_STREAM_ID);

    // Save data into ddr
    aos_task_new((char*)"Mjpeg stream handle task", jpeg_stream_handle_jlink_dump_task, (void *)VIDER_STREAM_ID, 2048);

    vTaskDelete(task_handle);
}
