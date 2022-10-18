#ifndef __FIRMWARE_LSC_H__
#define __FIRMWARE_LSC_H__

#include "img_struct.h"

void lsc_init(void);

/*** sw ***/
void lsc_get_sw_config(DSP2_LSC_PARAM *config);
void lsc_set_sw_config(const DSP2_LSC_PARAM *config);

/*** fw ***/
void lsc_control(const BL_COLOR_TEMP color_temp, const DSP2_LSC_PARAM *sw_config);
int lsc_img_update(BL_COLOR_TEMP color_temp);
int lsc_img_manual(BL_COLOR_TEMP color_temp);

/*** hw ***/
void lsc_hw_update(void);

#endif
