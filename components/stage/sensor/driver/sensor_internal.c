#include "bl_comm_sns.h"
#include "sccb.h"
#include "sensor_internal.h"

int find_closest_gain_index(BL_GAIN_DB gain, int steps_per_6dB)
{
    int index;

    /* TODO: add check param */

    /* (gain / 256) / 6 * steps_per_6dB */
    index = DIV_ROUND((gain * steps_per_6dB), 6 << 8);

    return index;
}

int sensor_probe(uint8_t slv_addr, uint16_t id_addr_h, uint16_t id_addr_l, uint8_t id_h, uint8_t id_l)
{
    BL_LOGI("------------------sensor probe---------------\r\n");
    uint8_t value_h = 0, value_l = 0;

    SCCB_Read_Reg16(slv_addr, id_addr_h, &value_h);
    BL_LOGI("------------------%02x \r\n", value_h);
	SCCB_Read_Reg16(slv_addr, id_addr_l, &value_l);
	BL_LOGI("------------------%02x \r\n", value_l);

	if(value_h == id_h && value_l == id_l)
		return 0;
	else
		return -1;
}

int sensor_probe_8bit(uint8_t slv_addr, uint8_t id_addr_h, uint8_t id_addr_l, uint8_t id_h, uint8_t id_l)
{
    BL_LOGI("------------------sensor probe---------------\r\n");
    uint8_t value_h = 0, value_l = 0;

    SCCB_Read(slv_addr, id_addr_h, &value_h);
    BL_LOGI("------------------%02x \r\n", value_h);
	SCCB_Read(slv_addr, id_addr_l, &value_l);
	BL_LOGI("------------------%02x \r\n", value_l);

	if(value_h == id_h && value_l == id_l)
		return 0;
	else
		return -1;
}

bool is_sensor_dsp2_input_match(const int* sensor_mode, int mode_num)
{
    int i = 0;

    for (i = 0; i < mode_num; i++) {
        if (DSP2_INPUT_MODE == sensor_mode[i]) {
            return true;
        }
    }

    printf("ERROR: DSP2 Input mode not support in current Sensor\r\n");
    return false;
}