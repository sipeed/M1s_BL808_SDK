#ifndef __FIRMWARE_SAT_H__
#define __FIRMWARE_SAT_H__

#include "img_struct.h"

void sat_init(void);

/*** sw ***/
void sat_get_sw_config(DSP2_SAT_PARAM *config);
void sat_set_sw_config(const DSP2_SAT_PARAM *config);

/*** fw ***/
void sat_control(const DSP2_SAT_PARAM *config);
int sat_img_update(BL_GAIN_DB gain);
int sat_img_manual(void);

/*** hw ***/
void sat_hw_update(void);

#endif
