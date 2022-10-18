#ifndef __FIRMWARE_BNR_H__
#define __FIRMWARE_BNR_H__

#include "img_struct.h"

void bnr_init();

/*** sw ***/
void bnr_get_sw_config(DSP2_BNR_PARAM *config);
void bnr_set_sw_config(const DSP2_BNR_PARAM *config);

/*** fw ***/
void bnr_control(DSP2_BNR_PARAM *config);
int bnr_img_update(BL_GAIN_DB gain);
int bnr_img_manual(void);

/*** hw ***/
void bnr_hw_update(void);

void bnr_control_debug();
#endif
