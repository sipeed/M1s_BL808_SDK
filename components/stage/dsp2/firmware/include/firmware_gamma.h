#ifndef __FIRMWARE_GAMMA_H__
#define __FIRMWARE_GAMMA_H__

#include "img_struct.h"

void gamma_init(void);

/*** sw ***/
void gamma_get_sw_config(DSP2_GAMMA_PARAM *config);
void gamma_set_sw_config(const DSP2_GAMMA_PARAM *config);

/*** fw ***/
void gamma_control(const DSP2_GAMMA_PARAM *config);
int gamma_img_update(BL_GAIN_DB sys_gain);
int gamma_img_manual(void);

/*** hw ***/
void gamma_hw_update(void);

#endif
