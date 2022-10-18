#ifndef __FIRMWARE_BLC_H__
#define __FIRMWARE_BLC_H__

#include "img_struct.h"

void blc_init(void);

/*** sw ***/
void blc_get_sw_config(DSP2_BLC_PARAM *config);
void blc_set_sw_config(const DSP2_BLC_PARAM *config);

/*** fw ***/
void blc_control(const DSP2_BLC_PARAM *config);
int blc_img_update(BL_GAIN_DB gain);
int blc_img_manual(void);

/*** hw ***/
void blc_hw_update(void);

#endif
