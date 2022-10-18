#include <stdint.h>
#include <bl808_pds.h>
#include <bl808_glb.h>
#include <bl808_glb_gpio.h>
#include <mm_misc_reg.h>
#include <core_rv32.h>

/* FIXME: Use std driver */
typedef enum {
    MMSYS_REL_VRAM_64_L2_0  = 0,
    MMSYS_REL_VRAM_0_L2_64 = 1,
}MMSYS_VRAM_L2_SRAM_Type;

typedef enum {
    MMSYS_REL_VRAM_0_PFH_192  = 0,
    MMSYS_REL_VRAM_64_PFH_128 = 1,
    MMSYS_REL_VRAM_128_PFH_64 = 2,
    MMSYS_REL_VRAM_192_PFH_0  = 3
}MMSYS_VRAM_PFH_SRAM_Type;

typedef enum {
    MMSYS_REL_VRAM_0_APU_128 = 0,
    MMSYS_REL_VRAM_128_APU_0 = 1,
}MMSYS_VRAM_APU_SRAM_Type;

typedef enum {
    MMSYS_REL_VRAM_0_DSP2_64 = 0,
    MMSYS_REL_VRAM_64_DSP2_0 = 1,
}MMSYS_VRAM_DSP2_SRAM_Type;

typedef struct {
    MMSYS_VRAM_L2_SRAM_Type  l2sram;
    MMSYS_VRAM_PFH_SRAM_Type pfh;
    MMSYS_VRAM_APU_SRAM_Type apu;
    MMSYS_VRAM_DSP2_SRAM_Type dsp2;
}MMSYS_VRAM_Ctrl_Cfg;

/* 0x50 : vram_ctrl */
#define MMSYS_MISC_VRAM_CTRL_OFFSET                             (0x50)
#define MMSYS_MISC_REG_SYSRAM_SET                               MMSYS_MISC_REG_SYSRAM_SET
#define MMSYS_MISC_REG_SYSRAM_SET_POS                           (0U)
#define MMSYS_MISC_REG_SYSRAM_SET_LEN                           (1U)
#define MMSYS_MISC_REG_SYSRAM_SET_MSK                           (((1U<<MMSYS_MISC_REG_SYSRAM_SET_LEN)-1)<<MMSYS_MISC_REG_SYSRAM_SET_POS)
#define MMSYS_MISC_REG_SYSRAM_SET_UMSK                          (~(((1U<<MMSYS_MISC_REG_SYSRAM_SET_LEN)-1)<<MMSYS_MISC_REG_SYSRAM_SET_POS))
#define MMSYS_MISC_REG_PF_SRAM_REL                              MMSYS_MISC_REG_PF_SRAM_REL
#define MMSYS_MISC_REG_PF_SRAM_REL_POS                          (1U)
#define MMSYS_MISC_REG_PF_SRAM_REL_LEN                          (2U)
#define MMSYS_MISC_REG_PF_SRAM_REL_MSK                          (((1U<<MMSYS_MISC_REG_PF_SRAM_REL_LEN)-1)<<MMSYS_MISC_REG_PF_SRAM_REL_POS)
#define MMSYS_MISC_REG_PF_SRAM_REL_UMSK                         (~(((1U<<MMSYS_MISC_REG_PF_SRAM_REL_LEN)-1)<<MMSYS_MISC_REG_PF_SRAM_REL_POS))
#define MMSYS_MISC_REG_L2_SRAM_REL                              MMSYS_MISC_REG_L2_SRAM_REL
#define MMSYS_MISC_REG_L2_SRAM_REL_POS                          (4U)
#define MMSYS_MISC_REG_L2_SRAM_REL_LEN                          (1U)
#define MMSYS_MISC_REG_L2_SRAM_REL_MSK                          (((1U<<MMSYS_MISC_REG_L2_SRAM_REL_LEN)-1)<<MMSYS_MISC_REG_L2_SRAM_REL_POS)
#define MMSYS_MISC_REG_L2_SRAM_REL_UMSK                         (~(((1U<<MMSYS_MISC_REG_L2_SRAM_REL_LEN)-1)<<MMSYS_MISC_REG_L2_SRAM_REL_POS))
#define MMSYS_MISC_REG_DSP2_SRAM_REL                             MMSYS_MISC_REG_DSP2_SRAM_REL
#define MMSYS_MISC_REG_DSP2_SRAM_REL_POS                         (6U)
#define MMSYS_MISC_REG_DSP2_SRAM_REL_LEN                         (1U)
#define MMSYS_MISC_REG_DSP2_SRAM_REL_MSK                         (((1U<<MMSYS_MISC_REG_DSP2_SRAM_REL_LEN)-1)<<MMSYS_MISC_REG_DSP2_SRAM_REL_POS)
#define MMSYS_MISC_REG_DSP2_SRAM_REL_UMSK                        (~(((1U<<MMSYS_MISC_REG_DSP2_SRAM_REL_LEN)-1)<<MMSYS_MISC_REG_DSP2_SRAM_REL_POS))
#define MMSYS_MISC_REG_APU_SRAM_REL                             MMSYS_MISC_REG_APU_SRAM_REL
#define MMSYS_MISC_REG_APU_SRAM_REL_POS                         (7U)
#define MMSYS_MISC_REG_APU_SRAM_REL_LEN                         (1U)
#define MMSYS_MISC_REG_APU_SRAM_REL_MSK                         (((1U<<MMSYS_MISC_REG_APU_SRAM_REL_LEN)-1)<<MMSYS_MISC_REG_APU_SRAM_REL_POS)
#define MMSYS_MISC_REG_APU_SRAM_REL_UMSK                        (~(((1U<<MMSYS_MISC_REG_APU_SRAM_REL_LEN)-1)<<MMSYS_MISC_REG_APU_SRAM_REL_POS))

#define MMSYS_MISC_BASE             ((uint32_t)0x30000000)            /*!< MMSys misc base address */

static void MMSYS_VRAM_Ctrl(MMSYS_VRAM_Ctrl_Cfg *cfg)
{
    uint32_t tmpVal;

    tmpVal=BL_RD_WORD(MMSYS_MISC_BASE + 0x50);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal, MMSYS_MISC_REG_L2_SRAM_REL,  cfg->l2sram);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal, MMSYS_MISC_REG_PF_SRAM_REL,  cfg->pfh);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal, MMSYS_MISC_REG_APU_SRAM_REL, cfg->apu);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal, MMSYS_MISC_REG_DSP2_SRAM_REL, cfg->dsp2);

    BL_WR_WORD(MMSYS_MISC_BASE + 0x50, tmpVal);

    tmpVal=BL_RD_WORD(MMSYS_MISC_BASE + 0x50);
    tmpVal = BL_SET_REG_BIT(tmpVal, MMSYS_MISC_REG_SYSRAM_SET);
    BL_WR_WORD(MMSYS_MISC_BASE + 0x50, tmpVal);
}

void l2_sram_vram_config(void)
{
    MMSYS_VRAM_Ctrl_Cfg cfg;
    cfg.l2sram = MMSYS_REL_VRAM_64_L2_0;
    cfg.pfh    = MMSYS_REL_VRAM_0_PFH_192;
    cfg.apu    = MMSYS_REL_VRAM_0_APU_128;
    cfg.dsp2    = MMSYS_REL_VRAM_0_DSP2_64;

    MMSYS_VRAM_Ctrl(&cfg);
}
