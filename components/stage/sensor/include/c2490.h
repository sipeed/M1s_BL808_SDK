#ifndef __C2490_H__
#define __C2490_H__


int c2490_init(sensor_t *sensor);
void c2490_get_probe_info(uint8_t *slv_addr, uint32_t *regs_sensor_id, uint16_t *sensor_id);

#endif //__C2490_H__
