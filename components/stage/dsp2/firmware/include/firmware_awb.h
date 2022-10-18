#ifndef __FIRMWARE_AWB_H__
#define __FIRMWARE_AWB_H__

#include "img_struct.h"

/*** sw ***/
void awb_sw_init(void);

/*** fw ***/
void awb_set_sys_config(BL_GAIN_DB sys_gain);

/*** hw ***/


#endif
