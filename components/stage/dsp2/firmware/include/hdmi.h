#ifndef __HDMI_H__
#define __HDMI_H__
#include <stdint.h>


typedef enum
{
    HDMI_MODE_720P60 = 0,
    HDMI_MODE_720P50,
    HDMI_MODE_1080P60,
    HDMI_MODE_1080P50,
    HDMI_MODE_1080P30,
    HDMI_MODE_OFF,
} HDMI_MODE;
  
typedef enum
{
    HDMI_FROM_DRAM = 0,
    HDMI_FROM_FAKE_DATA,
} HDMI_SRC;


void bl_hdmi_init(void);
int adv7511_enable(void);
int adv7511_disable(void);


#endif //__HDMI_H__
