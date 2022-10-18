#include <stdint.h>
#include "firmware_af.h"
#include "bl_dsp2.h"
#include "bl_img_utils.h"

void af_init(void)
{
    bl_dsp2_af_conf_t conf;
    bl_dsp2_af_win_t win_conf;

    conf.gamma_pattern = 0;
    conf.fcore1 = 15;
    conf.fcore2 = 15;
    bl_set_AF_conf(&conf);

    win_conf.start_x = 0;
    win_conf.start_y = 0;
    win_conf.end_x = 255;
    win_conf.end_y = 255;
    win_conf.sum_shift = 3;

    bl_set_AF_win_conf(BL_DSP2_AF_WIN_A, &win_conf);

    win_conf.start_x = 0;
    win_conf.start_y = 0;
    win_conf.end_x = 255;
    win_conf.end_y = 255;
    win_conf.sum_shift = 7;
    bl_set_AF_win_conf(BL_DSP2_AF_WIN_B, &win_conf);
}


