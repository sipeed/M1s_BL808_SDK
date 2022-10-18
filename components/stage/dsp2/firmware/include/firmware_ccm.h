#ifndef __FIRMWARE_CCM_H__
#define __FIRMWARE_CCM_H__

#include "img_struct.h"

void ccm_init(void);

/*** sw ***/
void ccm_get_sw_config(DSP2_CCM_PARAM *config);
void ccm_set_sw_config(const DSP2_CCM_PARAM *config);
void ccm_get_sw_cw_config(ccm_cw_t *config);
void ccm_set_sw_cw_config(const ccm_cw_t *config);

/*** fw ***/
void ccm_control(const DSP2_CCM_PARAM *sw_config, const ccm_cw_t *sw_cw_config);
int ccm_img_update(BL_COLOR_TEMP color_temp, BL_GAIN_DB gain);
int ccm_img_manual(void);

/*** hw ***/
void ccm_hw_update(void);

#endif
