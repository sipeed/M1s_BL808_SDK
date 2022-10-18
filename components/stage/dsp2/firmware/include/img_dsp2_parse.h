#ifndef __IMG_DSP2_PARSE_H__
#define __IMG_DSP2_PARSE_H__

typedef enum {
    DSP2_PARSE_READ = 0,
    DSP2_PARSE_WRITE,
    DSP2_PARSE_DUMP,
    DSP2_PARSE_LOAD,
} DSP2_PARSE_TYPE;

typedef enum {
    REG_HW = 0,
    REG_FW,
    REG_SW,
    REG_CAL,
} REG_TYPE;

int isIntger(char* str, int* value);
int isFloat(char* str, float* value);
int isIntgerArray(char* str, int* array, int *ret_arr_num);
void strCatVal(char* ret_string, int value);
void strCatVal_u64(char* ret_string, uint64_t value);
void strCatVal_hex(char* ret_string, int value);
int parseToolReg(char *reg_in, char *reg_out);

int DSP2_SYS_HW_Parse(int type, char* reg, int value, char* ret_string);
int DSP2_DSP2_MISC_HW_Parse(int type, char* reg, int value, char* ret_string);
int DSP2_AXI_CTRL_HW_Parse(int type, char* reg, int value, char* ret_string);
int DSP2_TG_HW_Parse(int type, char* reg, int value, char* ret_string);

int DSP2_Module_State_FW_Parse(int type, char* reg, int value, char* ret_string);

int DSP2_AE_FW_Metering_Tbl_Parse(int type, char* reg, int *value, char* ret_string);
int DSP2_AE_FW_Auto_Tbl_Parse(int type, char* reg, int *value, char* ret_string);
int DSP2_AE_FW_Agc_DB_Tbl_Parse(int type, char* reg, int *value, char* ret_string);

int DSP2_AE_FW_Parse(int type, char* reg, int value, char* ret_string);
int DSP2_AE_HW_Parse(int type, char* reg, int value, char* ret_string);
int DSP2_AE_Array_Parse(int type, char* reg, int *value, char* ret_string);

int DSP2_AWB3_Calib_Bin_Parse(int type, char* reg, int *value, char* ret_string);
int DSP2_WB_Info_Calib_Parse(int type, char* reg, int *value, char* ret_string);

int DSP2_AWB_FW_Parse(int type, char* reg, int value, char* ret_string);
int DSP2_AWB3_rgb_Parse(int type, char* reg, int *value, char* ret_string);

int DSP2_AWB3_FW_Preference_Tbl_Parse(int type, char* reg, int *value, char* ret_string);
int DSP2_AWB3_FW_Special_Coloe_Parse(int type, char* reg, int *value, char* ret_string);
int DSP2_AWB_HW_Parse(int type, char* reg, int value, char* ret_string);
int DSP2_AWB_Array_Parse(int type, char* reg, int *value, char* ret_string);

int DSP2_BLC_Calib_Parse(int type, char* reg, int *value, char* ret_string);
int DSP2_BLC_FW_Auto_Parse(int type, char* reg, int *value, char* ret_string);
int DSP2_BLC_FW_Parse(int type, char* reg, int value, char* ret_string);
int DSP2_BLC_HW_Parse(int type, char* reg, int value, char* ret_string);

int DSP2_DPC_Calib_Parse(int type, char* reg, int *value, char* ret_string);
int DSP2_DPC_FW_Auto_Parse(int type, char* reg, int *value, char* ret_string);;
int DSP2_DPC_FW_Parse(int type, char* reg, int value, char* ret_string);
int DSP2_DPC_HW_Parse(int type, char* reg, int value, char* ret_string);

int DSP2_BNR_FW_Auto_Parse(int type, char* reg, int *value, char* ret_string);
int DSP2_BNR_FW_Parse(int type, char* reg, int value, char* ret_string);
int DSP2_BNR_HW_Parse(int type, char* reg, int value, char* ret_string);

int DSP2_LSC_Calib_Parse(int type, char* reg, int *value, char* ret_string);
int DSP2_LSC_FW_Auto_Parse(int type, char* reg, int *value, char* ret_string);
int DSP2_LSC_FW_Parse(int type, char* reg, int value, char* ret_string);
int DSP2_LSC_HW_Parse(int type, char* reg, int value, char* ret_string);
int DSP2_LSC_Coef_HW_Parse(int type, char* reg, int *value, char* ret_string);

int DSP2_DG_FW_Auto_Parse(int type, char* reg, int *value, char* ret_string);
int DSP2_DG_HW_Parse(int type, char* reg, int value, char* ret_string);

int DSP2_AF_HW_Parse(int type, char* reg, int value, char* ret_string);

int DSP2_CCM_Calib_Parse(int type, char* reg, int *value, char* ret_string);
int DSP2_CCM_FW_Auto_Parse(int type, char* reg, int *value, char* ret_string);

int DSP2_CCM_FW_Parse(int type, char* reg, int value, char* ret_string);
int DSP2_CCM_HW_Parse(int type, char* reg, int value, char* ret_string);
int DSP2_CCM_Coef_FW_Parse(int type, char* reg, int *value, char* ret_string);
int DSP2_CCM_Coef_HW_Parse(int type, char* reg, int *value, char* ret_string);

int DSP2_Gamma_Calib_Parse(int type, char* reg, int *value, char* ret_string);
int DSP2_Gamma_FW_Auto_Parse(int type, char* reg, int *value, char* ret_string);
int DSP2_Gamma_FW_Parse(int type, char* reg, int value, char* ret_string);
int DSP2_Gamma_Curve_HW_Parse(int type, char* reg, int *value, char* ret_string);

int DSP2_WDR_FW_Auto_Parse(int type, char* reg, int *value, char* ret_string);

int DSP2_WDR_FW_Parse(int type, char* reg, int value, char* ret_string);
int DSP2_WDR_HW_Parse(int type, char* reg, int value, char* ret_string);

int DSP2_WDR_FW_Curve_Parse(int type, char* reg, int *value, char* ret_string);
int DSP2_WDR_Stats_Hist_Roi_Parse(int type, char* reg, int *value, char* ret_string);
int DSP2_WDR_Stats_Hist_Parse(int type, char* reg, int *value, char* ret_string);

int DSP2_SAT_FW_Auto_Parse(int type, char* reg, int *value, char* ret_string);
int DSP2_SAT_FW_Parse(int type, char* reg, int value, char* ret_string);
int DSP2_SAT_HW_Parse(int type, char* reg, int value, char* ret_string);

int DSP2_NR_FW_Auto_Parse(int type, char* reg, int *value, char* ret_string);
int DSP2_NR_FW_Parse(int type, char* reg, int value, char* ret_string);
int DSP2_NR_HW_Parse(int type, char* reg, int value, char* ret_string);

int DSP2_EE_FW_Auto_Parse(int type, char* reg, int *value, char* ret_string);
int DSP2_EE_FW_Parse(int type, char* reg, int value, char* ret_string);
int DSP2_EE_HW_Parse(int type, char* reg, int value, char* ret_string);
int DSP2_EE_FW_Tbl_Parse(int type, char* reg, int *value, char* ret_string);
int DSP2_EE_HW_Tbl_Parse(int type, char* reg, int *value, char* ret_string);

int DSP2_CS_FW_Parse(int type, char* reg, int value, char* ret_string);
int DSP2_CS_FW_Auto_Parse(int type, char* reg, int *value, char* ret_string);
int DSP2_CS_HW_Parse(int type, char* reg, int value, char* ret_string);

int DSP2_YC_FW_Auto_Parse(int type, char* reg, int *value, char* ret_string);
int DSP2_YC_FW_Parse(int type, char* reg, int value, char* ret_string);
int DSP2_YC_HW_Parse(int type, char* reg, int value, char* ret_string);

int DSP2_YUVC_HW_Parse(int type, char* reg, int value, char* ret_string);

#endif /* __IMG_DSP2_PARAM_H__ */

