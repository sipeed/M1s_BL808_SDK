#include <stdint.h>
#include <bl808_common.h>
#include <bl808_comm_mm.h>

#include "bl808_dsp2_axi_ctrl.h"
#include <dsp2_axi_ctrl_reg.h>


/****************************************************************************//**
 * @brief  3DNR init function
 *
 * @param  dsp23DNRCfg: 3DNR configuration structure pointer
 *
 * @return None
 *
*******************************************************************************/
void DSP2_3DNR_Init(DSP2_3DNR_Cfg_Type *dsp23DNRCfg)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_3DNR_BURST_TYPE(dsp23DNRCfg->burst));

    tmpVal = BL_RD_REG(DSP2_AXI_CTRL_NR3D_BASE,DSP2_AXI_CTRL_NR_CONTROL);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DSP2_AXI_CTRL_REG_XLEN,dsp23DNRCfg->burst);
    BL_WR_REG(DSP2_AXI_CTRL_NR3D_BASE,DSP2_AXI_CTRL_NR_CONTROL,tmpVal);

    BL_WR_REG(DSP2_AXI_CTRL_NR3D_BASE,DSP2_AXI_CTRL_NR_HADDR_START_ADDRESS,dsp23DNRCfg->memStart);
    /*Set memory brust size */
    switch(dsp23DNRCfg->burst){
        case DSP2_3DNR_BURST_TYPE_SINGLE:
            tmpVal = dsp23DNRCfg->memSize >> 3;
            break;
        case DSP2_3DNR_BURST_TYPE_INCR4:
            tmpVal = dsp23DNRCfg->memSize >> 5;
            break;
        case DSP2_3DNR_BURST_TYPE_INCR8:
            tmpVal = dsp23DNRCfg->memSize >> 6;
            break;
        case DSP2_3DNR_BURST_TYPE_INCR16:
            tmpVal = dsp23DNRCfg->memSize >> 7;
            break;
        case DSP2_3DNR_BURST_TYPE_INCR32:
            tmpVal = dsp23DNRCfg->memSize >> 8;
            break;
        case DSP2_3DNR_BURST_TYPE_INCR64:
            tmpVal = dsp23DNRCfg->memSize >> 9;
            break;
        default:
            tmpVal = 0;
            break;
    }
    BL_WR_REG(DSP2_AXI_CTRL_NR3D_BASE,DSP2_AXI_CTRL_NR_MEMORY_BURST_COUNT,tmpVal);

    BL_WR_REG(DSP2_AXI_CTRL_NR3D_BASE,DSP2_AXI_CTRL_NR_HSYNC_CONTROL,dsp23DNRCfg->hsyncStart<<16|dsp23DNRCfg->hsyncEnd);
    BL_WR_REG(DSP2_AXI_CTRL_NR3D_BASE,DSP2_AXI_CTRL_NR_VSYNC_CONTROL,dsp23DNRCfg->vsyncStart<<16|dsp23DNRCfg->vsyncEnd);
}

void DSP2_3DNR_Enable(void)
{
    uint32_t tmpVal;
    
    tmpVal = BL_RD_REG(DSP2_AXI_CTRL_NR3D_BASE, DSP2_AXI_CTRL_NR_CONTROL);
    tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_AXI_CTRL_REG_ENABLE);
    BL_WR_REG(DSP2_AXI_CTRL_NR3D_BASE, DSP2_AXI_CTRL_NR_CONTROL, tmpVal);
}

void DSP2_3DNR_Disable(void)
{
    uint32_t tmpVal;
    
    tmpVal = BL_RD_REG(DSP2_AXI_CTRL_NR3D_BASE, DSP2_AXI_CTRL_NR_CONTROL);
    tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_AXI_CTRL_REG_DRAIN_CLR);
    tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_AXI_CTRL_REG_OVERFLOW_CLR);
    tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_AXI_CTRL_REG_ENABLE);
    BL_WR_REG(DSP2_AXI_CTRL_NR3D_BASE, DSP2_AXI_CTRL_NR_CONTROL, tmpVal);
}

void DSP2_3DNR_Set_Qos_Sw_Mode(int value)
{
    uint32_t tmpVal;
    
    tmpVal = BL_RD_REG(DSP2_AXI_CTRL_NR3D_BASE, DSP2_AXI_CTRL_NR_CONTROL);
    if (value == 1) {
        tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_AXI_CTRL_REG_QOS_SW_MODE);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_AXI_CTRL_REG_QOS_SW_MODE);
    }
    BL_WR_REG(DSP2_AXI_CTRL_NR3D_BASE, DSP2_AXI_CTRL_NR_CONTROL, tmpVal);
}

void DSP2_3DNR_Get_Qos_Sw_Mode(int *value)
{
    uint32_t tmpVal;
    
    tmpVal = BL_RD_REG(DSP2_AXI_CTRL_NR3D_BASE, DSP2_AXI_CTRL_NR_CONTROL);

    if (BL_IS_REG_BIT_SET(tmpVal, DSP2_AXI_CTRL_REG_QOS_SW_MODE)) {
        *value = 1;
    } else {
        *value = 0;
    }
}

void DSP2_3DNR_Set_Qos_Sw_Val(int value)
{
    uint32_t tmpVal;
    
    tmpVal = BL_RD_REG(DSP2_AXI_CTRL_NR3D_BASE, DSP2_AXI_CTRL_NR_CONTROL);
    if (value == 1) {
        tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_AXI_CTRL_REG_QOS_SW);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_AXI_CTRL_REG_QOS_SW);
    }
    BL_WR_REG(DSP2_AXI_CTRL_NR3D_BASE, DSP2_AXI_CTRL_NR_CONTROL, tmpVal);
}

void DSP2_3DNR_Get_Qos_Sw_Val(int *value)
{
    uint32_t tmpVal;
    
    tmpVal = BL_RD_REG(DSP2_AXI_CTRL_NR3D_BASE, DSP2_AXI_CTRL_NR_CONTROL);

    if (BL_IS_REG_BIT_SET(tmpVal, DSP2_AXI_CTRL_REG_QOS_SW)) {
        *value = 1;
    } else {
        *value = 0;
    }
}

void DSP2_3DNR_SetImageSize(uint16_t width, uint16_t height)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_AXI_CTRL_NR3D_BASE, DSP2_AXI_CTRL_NR_HSYNC_CONTROL);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_AXI_CTRL_REG_HSYNC_ACT_START, 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_AXI_CTRL_REG_HSYNC_ACT_END, width);
    BL_WR_REG(DSP2_AXI_CTRL_NR3D_BASE, DSP2_AXI_CTRL_NR_HSYNC_CONTROL, tmpVal);

    tmpVal = BL_RD_REG(DSP2_AXI_CTRL_NR3D_BASE, DSP2_AXI_CTRL_NR_VSYNC_CONTROL);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_AXI_CTRL_REG_VSYNC_ACT_START, 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_AXI_CTRL_REG_VSYNC_ACT_END, height);
    BL_WR_REG(DSP2_AXI_CTRL_NR3D_BASE, DSP2_AXI_CTRL_NR_VSYNC_CONTROL, tmpVal);
}

void DSP2_3DNR_GetImageSize(uint16_t *width, uint16_t *height)
{
    uint32_t tmpVal;
    uint32_t start, end;

    tmpVal = BL_RD_REG(DSP2_AXI_CTRL_NR3D_BASE, DSP2_AXI_CTRL_NR_HSYNC_CONTROL);
    start = BL_GET_REG_BITS_VAL(tmpVal, DSP2_AXI_CTRL_REG_HSYNC_ACT_START);
    end = BL_GET_REG_BITS_VAL(tmpVal, DSP2_AXI_CTRL_REG_HSYNC_ACT_END);
    *width = (end - start);

    tmpVal = BL_RD_REG(DSP2_AXI_CTRL_NR3D_BASE, DSP2_AXI_CTRL_NR_VSYNC_CONTROL);
    start = BL_GET_REG_BITS_VAL(tmpVal, DSP2_AXI_CTRL_REG_VSYNC_ACT_START);
    end = BL_GET_REG_BITS_VAL(tmpVal, DSP2_AXI_CTRL_REG_VSYNC_ACT_END);
    *height = (end - start);
}

void DSP2_3DNR_SetRefFrameBuf(uint32_t bufAddr, uint32_t bufSize)
{
    /* check if buffer is aligned to 128 bytes boundary */
    CHECK_PARAM((bufAddr & AXI_BURST_INCR16_ALIGNMENT_MASK) == 0 );

    BL_WR_REG(DSP2_AXI_CTRL_NR3D_BASE, DSP2_AXI_CTRL_NR_HADDR_START_ADDRESS, bufAddr);
    BL_WR_REG(DSP2_AXI_CTRL_NR3D_BASE, DSP2_AXI_CTRL_NR_MEMORY_BURST_COUNT,
        Mem_Size_To_Burst_Cnt(bufSize, AXI_XLEN_INCR16));
}

void DSP2_3DNR_GetRefFrameBuf(    uint32_t *bufAddr, uint32_t *bufSize)
{
    uint32_t burst_cont;

    *bufAddr = BL_RD_REG(DSP2_AXI_CTRL_NR3D_BASE, DSP2_AXI_CTRL_NR_HADDR_START_ADDRESS);
    burst_cont = BL_RD_REG(DSP2_AXI_CTRL_NR3D_BASE, DSP2_AXI_CTRL_NR_MEMORY_BURST_COUNT);
    *bufSize = Burst_Cnt_To_Mem_Size(burst_cont, AXI_XLEN_INCR16);
}

void DSP2_3DNR_AXI_Ctrl_Check_Status(void)
{
    dsp2_axi_ctrl_reg_t *dsp2_axi_ctrl_reg = (dsp2_axi_ctrl_reg_t*)DSP2_AXI_CTRL_NR3D_BASE;
//    BL_LOGD("DVPSRC status: 0x%lx\n", dvpsrc_reg->ahb2dvp_status);

    if (dsp2_axi_ctrl_reg->nr_status.BF.status_r_drain) {
        BL_LOGE("3DNR AXI ctrl drain error!\r\n");
        dsp2_axi_ctrl_reg->nr_control.BF.reg_drain_clr = 1;
        dsp2_axi_ctrl_reg->nr_control.BF.reg_drain_clr = 0;
        BL_ABORT();
    }

    if (dsp2_axi_ctrl_reg->nr_status.BF.status_w_overflow) {
        BL_LOGE("3DNR AXI ctrl fifo overflow!\r\n");
        dsp2_axi_ctrl_reg->nr_control.BF.reg_overflow_clr = 1;
        dsp2_axi_ctrl_reg->nr_control.BF.reg_overflow_clr = 0;
        BL_ABORT();
    }
}

void DSP2_3DNR_Get_BUS_Cfg(DSP2_3DNR_BUS_Cfg_Type *cfg)
{
    dsp2_axi_ctrl_reg_t *dsp2_axi_ctrl_reg = (dsp2_axi_ctrl_reg_t*)DSP2_AXI_CTRL_NR3D_BASE;

    cfg->r_flsh = dsp2_axi_ctrl_reg->nr_status.BF.state_r_bus_flsh;
    cfg->r_fend = dsp2_axi_ctrl_reg->nr_status.BF.state_r_bus_fend;
    cfg->r_func = dsp2_axi_ctrl_reg->nr_status.BF.state_r_bus_func;
    cfg->r_idle = dsp2_axi_ctrl_reg->nr_status.BF.state_r_bus_idle;
    
    cfg->w_flsh = dsp2_axi_ctrl_reg->nr_status.BF.state_w_bus_flsh;
    cfg->w_fend = dsp2_axi_ctrl_reg->nr_status.BF.state_w_bus_fend;
    cfg->w_func = dsp2_axi_ctrl_reg->nr_status.BF.state_w_bus_func;
    cfg->w_idle = dsp2_axi_ctrl_reg->nr_status.BF.state_w_bus_idle;
}

void DSP2_3DNR_Get_DVP_Cfg(DSP2_3DNR_DVP_Cfg_Type *cfg)
{
    dsp2_axi_ctrl_reg_t *dsp2_axi_ctrl_reg = (dsp2_axi_ctrl_reg_t*)DSP2_AXI_CTRL_NR3D_BASE;

    cfg->r_flsh = dsp2_axi_ctrl_reg->nr_status.BF.state_r_dvp_flsh;
    cfg->r_fend = dsp2_axi_ctrl_reg->nr_status.BF.state_r_dvp_fend;
    cfg->r_func = dsp2_axi_ctrl_reg->nr_status.BF.state_r_dvp_func;
    cfg->r_wtst = dsp2_axi_ctrl_reg->nr_status.BF.state_r_dvp_wtst;
    cfg->r_idle = dsp2_axi_ctrl_reg->nr_status.BF.state_r_dvp_idle;
    
    cfg->w_flsh = dsp2_axi_ctrl_reg->nr_status.BF.state_w_dvp_flsh;
    cfg->w_fend = dsp2_axi_ctrl_reg->nr_status.BF.state_w_dvp_fend;
    cfg->w_func = dsp2_axi_ctrl_reg->nr_status.BF.state_w_dvp_func;
    cfg->w_wtst = dsp2_axi_ctrl_reg->nr_status.BF.state_w_dvp_wtst;
    cfg->w_idle = dsp2_axi_ctrl_reg->nr_status.BF.state_w_dvp_idle;
}

