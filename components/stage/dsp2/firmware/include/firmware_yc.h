#ifndef __FIRMWARE_YC_H__
#define __FIRMWARE_YC_H__

#include "img_struct.h"

void yc_init(void);

/*** sw ***/
void yc_get_sw_config(DSP2_YC_PARAM *config);
void yc_set_sw_config(const DSP2_YC_PARAM *config);

/*** fw ***/
void yc_control(const DSP2_YC_PARAM *config);
int yc_img_update(BL_GAIN_DB gain);
int yc_img_manual(void);

/*** hw ***/
void yc_hw_update(void);

#endif
