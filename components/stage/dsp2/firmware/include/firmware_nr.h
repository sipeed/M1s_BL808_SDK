#ifndef __FIRMWARENR__H__
#define __FIRMWARENR__H__

#include "img_struct.h"

void nr_init(void);

/* sw */
void nr_get_sw_config(DSP2_NR_PARAM *config);
void nr_set_sw_config(const DSP2_NR_PARAM *config);

/* fw */
void nr_control(const DSP2_NR_PARAM *config);
int nr_img_update(BL_GAIN_DB gain);
int nr_img_manual(voids);

/* hw */
void nr_hw_update(void);

#endif
