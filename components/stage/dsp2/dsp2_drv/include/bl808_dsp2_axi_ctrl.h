#ifndef __BL808_DSP2_AXI_CTRL_H__
#define __BL808_DSP2_AXI_CTRL_H__


/**
 *  @brief 3DNR burst type definition
 */
typedef enum {
    DSP2_3DNR_BURST_TYPE_SINGLE,              /*!< DSP2 3DNR burst type:single */
    DSP2_3DNR_BURST_TYPE_INCR4,               /*!< DSP2 3DNR burst type:incrementing 4 */
    DSP2_3DNR_BURST_TYPE_INCR8,               /*!< DSP2 3DNR burst type:incrementing 8 */
    DSP2_3DNR_BURST_TYPE_INCR16,              /*!< DSP2 3DNR burst type:incrementing 16 */
    DSP2_3DNR_BURST_TYPE_INCR32 = 5,          /*!< DSP2 3DNR burst type:incrementing 32 */
    DSP2_3DNR_BURST_TYPE_INCR64,              /*!< DSP2 3DNR burst type:incrementing 64 */
}DSP2_3DNR_Burst_Type;

/**
 *  @brief 3DNR status type definition
 */
typedef enum {
    DSP2_3DNR_STATUS_R_DRAIN = 4,    /*!< Read fifo drain error status */
    DSP2_3DNR_STATUS_W_OVERFLOW,     /*!< Write overflow status */
    DSP2_3DNR_STATUS_W_DVP_IDLE = 8, /*!< Write dvp idle status */
    DSP2_3DNR_STATUS_W_DVP_WTST,     /*!< Write dvp wait start status */
    DSP2_3DNR_STATUS_W_DVP_FUNC,     /*!< Write dvp function status */
    DSP2_3DNR_STATUS_W_DVP_FEND,     /*!< Write dvp function end status */
    DSP2_3DNR_STATUS_W_DVP_FLSH,     /*!< Write dvp flush status */
    DSP2_3DNR_STATUS_W_BUS_IDLE,     /*!< Write bus idle status */
    DSP2_3DNR_STATUS_W_BUS_FUNC,     /*!< Write bus function status */
    DSP2_3DNR_STATUS_W_BUS_FEND,     /*!< Write bus function end status */
    DSP2_3DNR_STATUS_W_BUS_FLSH,     /*!< Write bus flush status */
    DSP2_3DNR_STATUS_R_DVP_IDLE,     /*!< Read dvp idle status */
    DSP2_3DNR_STATUS_R_DVP_WTST,     /*!< Read dvp wait start status */
    DSP2_3DNR_STATUS_R_DVP_FUNC,     /*!< Read dvp function status */
    DSP2_3DNR_STATUS_R_DVP_FEND,     /*!< Read dvp function end status */
    DSP2_3DNR_STATUS_R_DVP_FLSH,     /*!< Read dvp flush status */
    DSP2_3DNR_STATUS_R_BUS_IDLE,     /*!< Read bus idle status */
    DSP2_3DNR_STATUS_R_BUS_FUNC,     /*!< Read bus function status */
    DSP2_3DNR_STATUS_R_BUS_FEND,     /*!< Read bus function end status */
    DSP2_3DNR_STATUS_R_BUS_FLSH,     /*!< Read bus flush status */
    DSP2_3DNR_STATUS_R_IDLE,         /*!< AXI read channel idle status */
    DSP2_3DNR_STATUS_W_IDLE,         /*!< AXI write channel idle status */
} DSP2_3DNR_Status_Type;

/**
 *  @brief 3DNR configure strcut definition
 */
typedef struct {
    DSP2_3DNR_Burst_Type burst;               /*!< 3DNR burst length */
    uint32_t memStart;                       /*!< Data start address */
    uint32_t memSize;                        /*!< Memory size */
    uint16_t hsyncStart;                     /*!< Hsync active start count */
    uint16_t hsyncEnd;                       /*!< Hsync active end count */
    uint16_t vsyncStart;                     /*!< Vsync active start count */
    uint16_t vsyncEnd;                       /*!< Vsync active end count */
}DSP2_3DNR_Cfg_Type;

typedef struct {
    uint8_t r_flsh;
    uint8_t r_fend;
    uint8_t r_func;
    uint8_t r_idle;
    uint8_t w_flsh;
    uint8_t w_fend;
    uint8_t w_func;
    uint8_t w_idle;
}DSP2_3DNR_BUS_Cfg_Type;

typedef struct {
    uint8_t r_flsh;
    uint8_t r_fend;
    uint8_t r_func;
    uint8_t r_wtst;
    uint8_t r_idle;
    uint8_t w_flsh;
    uint8_t w_fend;
    uint8_t w_func;
    uint8_t w_wtst;
    uint8_t w_idle;
}DSP2_3DNR_DVP_Cfg_Type;

/** @defgroup  DSP2_3DNR_BURST_TYPE
 *  @{
 */
#define IS_DSP2_3DNR_BURST_TYPE(type)                     (((type) == DSP2_3DNR_BURST_TYPE_SINGLE) || \
                                                          ((type) == DSP2_3DNR_BURST_TYPE_INCR4) || \
                                                          ((type) == DSP2_3DNR_BURST_TYPE_INCR8) || \
                                                          ((type) == DSP2_3DNR_BURST_TYPE_INCR16) || \
                                                          ((type) == DSP2_3DNR_BURST_TYPE_INCR32) || \
                                                          ((type) == DSP2_3DNR_BURST_TYPE_INCR64))

/** @defgroup  DSP2_3DNR_STATUS_TYPE
 *  @{
 */
#define IS_DSP2_3DNR_STATUS_TYPE(type) (((type) == DSP2_3DNR_STATUS_R_DRAIN) ||    \
                                       ((type) == DSP2_3DNR_STATUS_W_OVERFLOW) || \
                                       ((type) == DSP2_3DNR_STATUS_W_DVP_IDLE) || \
                                       ((type) == DSP2_3DNR_STATUS_W_DVP_WTST) || \
                                       ((type) == DSP2_3DNR_STATUS_W_DVP_FUNC) || \
                                       ((type) == DSP2_3DNR_STATUS_W_DVP_FEND) || \
                                       ((type) == DSP2_3DNR_STATUS_W_DVP_FLSH) || \
                                       ((type) == DSP2_3DNR_STATUS_W_BUS_IDLE) || \
                                       ((type) == DSP2_3DNR_STATUS_W_BUS_FUNC) || \
                                       ((type) == DSP2_3DNR_STATUS_W_BUS_FEND) || \
                                       ((type) == DSP2_3DNR_STATUS_W_BUS_FLSH) || \
                                       ((type) == DSP2_3DNR_STATUS_R_DVP_IDLE) || \
                                       ((type) == DSP2_3DNR_STATUS_R_DVP_WTST) || \
                                       ((type) == DSP2_3DNR_STATUS_R_DVP_FUNC) || \
                                       ((type) == DSP2_3DNR_STATUS_R_DVP_FEND) || \
                                       ((type) == DSP2_3DNR_STATUS_R_DVP_FLSH) || \
                                       ((type) == DSP2_3DNR_STATUS_R_BUS_IDLE) || \
                                       ((type) == DSP2_3DNR_STATUS_R_BUS_FUNC) || \
                                       ((type) == DSP2_3DNR_STATUS_R_BUS_FEND) || \
                                       ((type) == DSP2_3DNR_STATUS_R_BUS_FLSH) || \
                                       ((type) == DSP2_3DNR_STATUS_R_IDLE) ||     \
                                       ((type) == DSP2_3DNR_STATUS_W_IDLE))

void DSP2_3DNR_Init(DSP2_3DNR_Cfg_Type *dsp23DNRCfg);
void DSP2_3DNR_Enable(void);
void DSP2_3DNR_Disable(void);
void DSP2_3DNR_Set_Qos_Sw_Mode(int value);
void DSP2_3DNR_Get_Qos_Sw_Mode(int *value);
void DSP2_3DNR_Set_Qos_Sw_Val(int value);
void DSP2_3DNR_Get_Qos_Sw_Val(int *value);
void DSP2_3DNR_SetImageSize(uint16_t width, uint16_t height);
void DSP2_3DNR_GetImageSize(uint16_t *width, uint16_t *height);
void DSP2_3DNR_SetRefFrameBuf(uint32_t bufAddr, uint32_t bufSize);
void DSP2_3DNR_GetRefFrameBuf(uint32_t *bufAddr, uint32_t *bufSize);
void DSP2_3DNR_AXI_Ctrl_Check_Status(void);
void DSP2_3DNR_Get_BUS_Cfg(DSP2_3DNR_BUS_Cfg_Type *cfg);
void DSP2_3DNR_Get_DVP_Cfg(DSP2_3DNR_DVP_Cfg_Type *cfg);


#endif /* __BL808_DSP2_AXI_CTRL_H__ */
