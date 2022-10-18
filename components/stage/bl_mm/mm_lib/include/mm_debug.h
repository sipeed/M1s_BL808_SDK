#ifndef __MM_DEBUG_H__
#define __MM_DEBUG_H__

typedef struct {
    uint16_t width;
    uint16_t height;
    char sensor_name[10];
} VirtualSensorInfo;

int MM_DBG_EnableVirtualSensor(bool enable, const VirtualSensorInfo *virtSnsInfo);
int MM_DBG_IsVirtualSensor(bool *enable);
int MM_DBG_GetSensorName(const char** name);
int MM_DBG_GetSensorBayerPattern(uint32_t *bayerPatternID);
int MM_DBG_SetPatternGenMode(int mode);
int MM_DBG_GetVirtSensorTsrcAddr(uint32_t *addr);

// for debug only
void build_vin_from_virt_sensor(bl_vin_config_t *vin_cfg, VirtualSensorInfo *vir_sns_info);

#endif /* __MM_DEBUG_H__ */
