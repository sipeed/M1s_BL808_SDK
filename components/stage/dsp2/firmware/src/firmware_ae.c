#include <stdint.h>
#include "firmware_ae.h"
#include "img_param.h"
#include "ae_algo.h"

void ae_sw_init(void)
{
}

void ae_set_auto_config(int mode) {

    ae_set_hist_weight_mode(mode);
}

