#ifndef __MM_SENSOR_H__
#define __MM_SENSOR_H__

#include <bl_dsp2.h>
#include "mm_common.h"

typedef struct {
	uint32_t picWidth;
	uint32_t picHeight;
    uint32_t fps;
} MMSensorAttr;

struct dsp2_sensor_if
{
    void (*name)(char** name);
    int (*init)(void); //static int init(sensor_t *sensor)
    void (*reset)(void); //int sensor_disable(void)

    int (*set_gain)(uint32_t gain);//int sensor_get_gain(BL_GAIN_DB *gain)
    int (*get_gain)(uint32_t *gain);
    int (*set_intt)(uint32_t intt);//int sensor_set_exposure(BL_EXPO_TIME expo_time)o_time)
    int (*get_intt)(uint32_t *intt);
    int (*set_flipmirror)(uint32_t flipmirror_type);
    int (*get_flipmirror)(uint32_t *flipmirror_type);

    int (*get_fps)(uint32_t *value);
    int (*get_bayer_pattern)(BAYER_PATTERN_E *bayer);
    int (*get_sensor_window)(BL_Img_Size_T *win);
    int (*get_act_window)(BL_Img_Size_T *win);
    int (*get_pic_window)(BL_Img_Size_T *wins);

    int (*set_sns_fmt)(uint32_t format); //static int set_format(sensor_t *sensor, VIDEO_MODE_E video_mode)
    int (*set_sns_reg)(uint16_t addr, uint16_t data); //int set_format(sensor_t *sensor, VIDEO_MODE_E video_mode)
};

int MM_Sensor_RegisterCb(uint32_t chanId, struct dsp2_sensor_if** pstSensorFunc);
int MM_Sensor_UnRegisterCb(uint32_t chanId);

int MM_Sensor_Init(void);
int MM_Sensor_GetSensorTime(void);
int MM_Sensor_SetFmt(VIDEO_MODE_E format);
int MM_Sensor_GetFmt(VIDEO_MODE_E *format);
int MM_Sensor_ChangeFmt(VIDEO_MODE_E format);
int MM_Sensor_ChangeFPS(uint32_t fps);
int MM_Sensor_GetFPS(uint32_t *fps);

int MM_Sensor_SetChnAttr(int snsChn, const MMSensorAttr *snsAttr);
int MM_Sensor_GetChnAttr(int snsChn, MMSensorAttr *snsAttr);
int MM_Sensor_SetPixClk(uint32_t pix_clk);
int MM_Sensor_GetPixClk(uint32_t *pix_clk);

int MM_Sensor_GetSensorReg(uint16_t addr,uint8_t *data);
int MM_Sensor_SetSensorReg(uint16_t addr,uint8_t data);

int MM_Sensor_Raw2Mem_Init_Run(VIDEO_MODE_E video_mode);
#endif /* __MM_SENSOR_H__ */
