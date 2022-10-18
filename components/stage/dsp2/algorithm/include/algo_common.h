#ifndef __ALGO_COMMON_H__
#define __ALGO_COMMON_H__

#include "bl808_common.h"

#define DEBUG_ALGO_MODULE 1

typedef enum
{
    BL_ALGO_LOG_AE = 0,
    BL_ALGO_LOG_AWB,
    BL_ALGO_LOG_WDR,
    BL_ALGO_LOG_NUM,
} BL_ALGO_LOGBIT;

extern int bl_algo_log_print_level;
extern uint8_t *bl_algo_log_print_bit_ptr;

#ifndef BL_ALGO_LOG_PRINT
#define BL_ALGO_LOG_PRINT(debug_module, type, algo, ...) \
    (((debug_module && (bl_algo_log_print_level != BL_LOG_OFF) && ((uint8_t)bl_algo_log_print_bit_ptr[algo])) && (type <= bl_algo_log_print_level))  \
    ? ((void)printf(__VA_ARGS__)) \
    : (void)0)
#endif

#define BL_AE_ALGO_LOGE(...) ((void)BL_ALGO_LOG_PRINT(DEBUG_ALGO_MODULE, BL_LOG_ERROR, BL_ALGO_LOG_AE, __VA_ARGS__))
#define BL_AE_ALGO_LOGW(...) ((void)BL_ALGO_LOG_PRINT(DEBUG_ALGO_MODULE, BL_LOG_WARNING, BL_ALGO_LOG_AE, __VA_ARGS__))
#define BL_AE_ALGO_LOGI(...) ((void)BL_ALGO_LOG_PRINT(DEBUG_ALGO_MODULE, BL_LOG_INFO, BL_ALGO_LOG_AE, __VA_ARGS__))
#define BL_AE_ALGO_LOGD(...) ((void)BL_ALGO_LOG_PRINT(DEBUG_ALGO_MODULE, BL_LOG_DEBUG, BL_ALGO_LOG_AE, __VA_ARGS__))

#define BL_AWB_ALGO_LOGE(...) ((void)BL_ALGO_LOG_PRINT(DEBUG_ALGO_MODULE, BL_LOG_ERROR, BL_ALGO_LOG_AWB, __VA_ARGS__))
#define BL_AWB_ALGO_LOGW(...) ((void)BL_ALGO_LOG_PRINT(DEBUG_ALGO_MODULE, BL_LOG_WARNING, BL_ALGO_LOG_AWB, __VA_ARGS__))
#define BL_AWB_ALGO_LOGI(...) ((void)BL_ALGO_LOG_PRINT(DEBUG_ALGO_MODULE, BL_LOG_INFO, BL_ALGO_LOG_AWB, __VA_ARGS__))
#define BL_AWB_ALGO_LOGD(...) ((void)BL_ALGO_LOG_PRINT(DEBUG_ALGO_MODULE, BL_LOG_DEBUG, BL_ALGO_LOG_AWB, __VA_ARGS__))

#define BL_WDR_ALGO_LOGE(...) ((void)BL_ALGO_LOG_PRINT(DEBUG_ALGO_MODULE, BL_LOG_ERROR, BL_ALGO_LOG_WDR, __VA_ARGS__))
#define BL_WDR_ALGO_LOGW(...) ((void)BL_ALGO_LOG_PRINT(DEBUG_ALGO_MODULE, BL_LOG_WARNING, BL_ALGO_LOG_WDR, __VA_ARGS__))
#define BL_WDR_ALGO_LOGI(...) ((void)BL_ALGO_LOG_PRINT(DEBUG_ALGO_MODULE, BL_LOG_INFO, BL_ALGO_LOG_WDR, __VA_ARGS__))
#define BL_WDR_ALGO_LOGD(...) ((void)BL_ALGO_LOG_PRINT(DEBUG_ALGO_MODULE, BL_LOG_DEBUG, BL_ALGO_LOG_WDR, __VA_ARGS__))


int BL_ALGO_DBG_ChgLogPrintLevel(BL_LOGTYPE level);
BL_LOGTYPE BL_ALGO_DBG_GetLogPrintLevel(void);
int BL_ALGO_DBG_ChgLogPrintAlgo(BL_ALGO_LOGBIT algo, BL_Fun_Type enable);
BL_Fun_Type BL_ALGO_DBG_GetLogPrintAlgo(BL_ALGO_LOGBIT algo);

#endif /* __ALGO_COMMON_H__ */


