#include <stdint.h>
#include "firmware_awb.h"
#include "img_param.h"
#include "awb_algo.h"


void awb_sw_init(void)
{
}

void awb_set_sys_config(BL_GAIN_DB sys_gain) {

    awb_set_sys_gain(sys_gain);
}

