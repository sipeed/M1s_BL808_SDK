#ifndef __FIRMWARE_DPC_H__
#define __FIRMWARE_DPC_H__

#include "img_struct.h"

void dpc_init(void);

/*** sw ***/
void dpc_get_sw_config(DSP2_DPC_PARAM *config);
void dpc_set_sw_config(const DSP2_DPC_PARAM *config);

/*** fw ***/
void dpc_control(const DSP2_DPC_PARAM *config);
int dpc_img_update(BL_GAIN_DB gain);
int dpc_img_manual(void);

/*** hw ***/
void dpc_hw_update(void);

#endif
