#ifndef __FIRMWARE_CS_H__
#define __FIRMWARE_CS_H__

#include "img_struct.h"

void cs_init(void);

/*** sw ***/
void cs_get_sw_config(DSP2_CS_PARAM *config);
void cs_set_sw_config(const DSP2_CS_PARAM *config);

/*** fw ***/
void cs_control(const DSP2_CS_PARAM *config);
int cs_img_update(BL_GAIN_DB gain);
int cs_img_manual(void);

/*** hw ***/
void cs_hw_update(void);

#endif
