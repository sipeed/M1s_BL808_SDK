#include "bl_venc.h"
#include "test_mjpeg_qtable.h"

#define JPEG_Q_TABLE_SIZE_TEST                  128

static int Qtable_zero[JPEG_Q_TABLE_SIZE_TEST] = {0};
static int default_Qtable_test[JPEG_Q_TABLE_SIZE_TEST] =
{
    128, 171, 146, 146, 114, 85, 42, 28,
    186, 171, 158, 120, 93,  59, 32, 22,
    205, 146, 128, 93,  55,  37, 26, 22,
    128, 108, 85,  71,  37,  32, 24, 21,
    85,  79,  51,  40,  30,  25, 20, 18,
    51,  35,  36,  24,  19,  20, 17, 20,
    40,  34,  30,  26,  20,  18, 17, 20,
    34,  37,  37,  33,  27,  22, 20, 21,
    120, 114, 85,  44,  21,  21, 21, 21,
    114, 98,  79,  31,  21,  21, 21, 21,
    85,  79,  37,  21,  21,  21, 21, 21,
    44,  31,  21,  21,  21,  21, 21, 21,
    21,  21,  21,  21,  21,  21, 21, 21,
    21,  21,  21,  21,  21,  21, 21, 21,
    21,  21,  21,  21,  21,  21, 21, 21,
    21,  21,  21,  21,  21,  21, 21, 21,
};

int test_Mjpeg_qtable_main()
{
    static int cnt = 0;
    int ret = 0;

    cnt++;

    /* Set jpeg Qtable */
    if (2 == cnt) {
        BL_LOGI("================Set jpeg Qtable ==================\r\n");
        ret = bl_venc_set_jpeg_Qtable(JPEG_Q_TABLE_SIZE_TEST, Qtable_zero);
        if (ret) {
            BL_LOGE("Set jpeg Qtable fail!! %s line:%d\r\n", __func__, __LINE__);
            return 1;
        }
    }

    if (4 == cnt) {
       BL_LOGI("================Set jpeg Qtable 00000==================\r\n");
        ret = bl_venc_set_jpeg_Qtable(JPEG_Q_TABLE_SIZE_TEST, default_Qtable_test);
        if (ret) {
            BL_LOGE("Set jpeg Qtable fail!! %s line:%d\r\n", __func__, __LINE__);
            return 1;
        }
    }

    if (6 == cnt) {
        BL_LOGI("================Set jpeg Qtable 0000==================\r\n");
        ret = bl_venc_set_jpeg_Qtable(JPEG_Q_TABLE_SIZE_TEST, Qtable_zero);
        if (ret) {
            BL_LOGE("Set jpeg Qtable fail!! %s line:%d\r\n", __func__, __LINE__);
            return 1;
        }
    }

    if (8 == cnt) {
        BL_LOGI("================Set jpeg Qtable ==================\r\n");
        ret = bl_venc_set_jpeg_Qtable(JPEG_Q_TABLE_SIZE_TEST, default_Qtable_test);
        if (ret) {
            BL_LOGE("Set jpeg Qtable fail!! %s line:%d\r\n", __func__, __LINE__);
            return 1;
        }
    }

    return 0;
}

