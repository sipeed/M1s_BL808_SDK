#ifndef __FIRMWARE_WDR_H__
#define __FIRMWARE_WDR_H__

int  wdr_init(void);

/*** sw ***/
void wdr_get_sw_config(DSP2_WDR_PARAM *config);
void wdr_set_sw_config(const DSP2_WDR_PARAM *config);

/*** fw ***/
int  wdr_control(const DSP2_WDR_PARAM *config);
int wdr_img_update(BL_GAIN_DB sys_gain);
int wdr_img_manual(void);

/*** hw ***/
void wdr_hw_update(void);

#endif
