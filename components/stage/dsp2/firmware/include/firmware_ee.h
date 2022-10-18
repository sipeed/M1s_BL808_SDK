#ifndef __FIRMWARE_EE_H__
#define __FIRMWARE_EE_H__

#include "img_struct.h"

void ee_init(void);

/* sw */
void ee_get_sw_config(DSP2_EE_PARAM *config);
void ee_set_sw_config(const DSP2_EE_PARAM *config);

/*** fw ***/
void ee_control(const DSP2_EE_PARAM *config);
int ee_img_update(BL_GAIN_DB gain);
int ee_img_manual(void);

/*** hw ***/
void ee_hw_update(void);
void ee_luma_weight_hw_update(void);

#endif
