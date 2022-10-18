#include <stdio.h>
#include "bl808_i2c.h"
#include "bl808_glb.h"

#include "hdmi.h"

#if (BL80X_HW_VER <= BL80X_HW_A0)
#define HDMI_I2C_PORT       I2C0_ID
#else
#define HDMI_I2C_PORT       I2C1_ID
#endif

#define HDMI_PHY_SLV_ADDR   0x39

//static I2C_CFG_Type i2cCfgStruct;


#if (BL80X_HW_VER <= BL80X_HW_A0)
static void hdmi_gpio_init(void)
{
    GLB_GPIO_Cfg_Type cfg;
    uint8_t gpiopins[20];
    uint8_t gpiofuns[20];
    int i;

    cfg.gpioMode=GPIO_MODE_AF;
    cfg.pullType=GPIO_PULL_NONE;
    cfg.drive=0;
    cfg.smtCtrl=1;

	gpiopins[0]=GLB_GPIO_PIN_47;
    gpiofuns[0]=GPIO47_FUN_HDMI_CK;

    gpiopins[1]=GLB_GPIO_PIN_2;
    gpiofuns[1]=GPIO2_FUN_HDMI_HSYNC;

    gpiopins[2]=GLB_GPIO_PIN_3;
    gpiofuns[2]=GPIO3_FUN_HDMI_VSYNC;

    gpiopins[3]=GLB_GPIO_PIN_4;
    gpiofuns[3]=GPIO4_FUN_HDMI_DE;

    gpiopins[4]=GLB_GPIO_PIN_37;
    gpiofuns[4]=GPIO37_FUN_HDMI_D_0;

    gpiopins[5]=GLB_GPIO_PIN_38;
    gpiofuns[5]=GPIO38_FUN_HDMI_D_1;

    gpiopins[6]=GLB_GPIO_PIN_39;
    gpiofuns[6]=GPIO39_FUN_HDMI_D_2;

    gpiopins[7]=GLB_GPIO_PIN_40;
    gpiofuns[7]=GPIO40_FUN_HDMI_D_3;

    gpiopins[8]=GLB_GPIO_PIN_41;
    gpiofuns[8]=GPIO41_FUN_HDMI_D_4;

    gpiopins[9]=GLB_GPIO_PIN_42;
    gpiofuns[9]=GPIO42_FUN_HDMI_D_5;

    gpiopins[10]=GLB_GPIO_PIN_43;
    gpiofuns[10]=GPIO43_FUN_HDMI_D_6;

    gpiopins[11]=GLB_GPIO_PIN_44;
    gpiofuns[11]=GPIO44_FUN_HDMI_D_7;

    gpiopins[12]=GLB_GPIO_PIN_45;
    gpiofuns[12]=GPIO45_FUN_HDMI_D_8;

    gpiopins[13]=GLB_GPIO_PIN_46;
    gpiofuns[13]=GPIO46_FUN_HDMI_D_9;

    gpiopins[14]=GLB_GPIO_PIN_48;
    gpiofuns[14]=GPIO48_FUN_HDMI_D_10;

    gpiopins[15]=GLB_GPIO_PIN_49;
    gpiofuns[15]=GPIO49_FUN_HDMI_D_11;

    gpiopins[16]=GLB_GPIO_PIN_50;
    gpiofuns[16]=GPIO50_FUN_HDMI_D_12;

    gpiopins[17]=GLB_GPIO_PIN_51;
    gpiofuns[17]=GPIO51_FUN_HDMI_D_13;

    gpiopins[18]=GLB_GPIO_PIN_52;
    gpiofuns[18]=GPIO52_FUN_HDMI_D_14;

    gpiopins[19]=GLB_GPIO_PIN_53;
    gpiofuns[19]=GPIO53_FUN_HDMI_D_15;

    for(i=0;i<sizeof(gpiopins)/sizeof(gpiopins[0]);i++){
        cfg.gpioPin=gpiopins[i];
        cfg.gpioFun=gpiofuns[i];
        GLB_GPIO_Init(&cfg);
    }
}
#endif

static uint8_t hdmi_read(uint8_t reg_addr)
{
    I2C_Transfer_Cfg cfg;
    uint8_t rdata = 0;
    uint8_t temp = reg_addr;
	cfg.slaveAddr = HDMI_PHY_SLV_ADDR;
	cfg.subAddrSize = 1;
	cfg.subAddr = &temp;
	cfg.dataSize = 1;
	cfg.data = &rdata;
    cfg.clk = 100000;
	I2C_MasterReceiveBlocking(HDMI_I2C_PORT, &cfg);

    return rdata;
}

static int hdmi_write(uint8_t reg_addr, uint8_t data)
{
    I2C_Transfer_Cfg cfg;
	cfg.slaveAddr = HDMI_PHY_SLV_ADDR;
	cfg.subAddrSize = 1;
	cfg.subAddr = &reg_addr;
	cfg.dataSize = 1;
	cfg.data = &data;
    cfg.clk = 100000;
    if (SUCCESS == I2C_MasterSendBlocking(HDMI_I2C_PORT, &cfg)){
		 return 0;
    } else {
        BL_LOGE("hdmi_write error!\r\n");
        return -1;
    }
}

#if !FPGA_ULTRASCALE
static int configure_i2c_switch(void)
{
    I2C_Transfer_Cfg cfg;
    uint8_t tempdata = 0x20;

	cfg.slaveAddr = 0x74;
	cfg.subAddrSize = 0;
	cfg.subAddr = NULL;
	cfg.dataSize = 1;
	cfg.data = &tempdata;
    cfg.clk = 100000;
    if (SUCCESS == I2C_MasterSendBlocking(HDMI_I2C_PORT, &cfg)){
		 return 0;
    } else {
        return -1;
    }
}
#endif

void bl_hdmi_init(void)
{
// #if (BL80X_HW_VER <= BL80X_HW_A0)
//     GLB_Set_HDMI_CLK(ENABLE, HDMI_CLK_160_MHZ, 1);
// #else
//     GLB_Set_HDMI_CLK(ENABLE, HDMI_CLK_74_25_MHZ, 0);
//     GLB_Set_I2C_CLK(1, GLB_I2C_CLK_BCLK, 0);

//     I2C_Disable(HDMI_I2C_PORT);
//     I2C_SetDefaultConfig(&i2cCfgStruct);
//     I2C_MasterInit(HDMI_I2C_PORT, &i2cCfgStruct);
// #endif

// #if !FPGA_ULTRASCALE
// 	/* configure I2C switch to enable HDMI phy device */
//     configure_i2c_switch();
// #endif
}

int adv7511_enable(void)
{
#if (BL80X_HW_VER <= BL80X_HW_A0)
    hdmi_gpio_init();
#endif

    //hdmi_write(0x41, 0x50);     /* power down */
    hdmi_write(0x41, 0x10);     /* power up */

    /* fixed registers */
    hdmi_write(0x98, 0x03);
    hdmi_write(0x9A, 0xE0);
    hdmi_write(0x9C, 0x30);
    hdmi_write(0x9D, 0x61);
    hdmi_write(0xA2, 0xa4);
    hdmi_write(0xA3, 0xa4);
    hdmi_write(0xE0, 0xD0);
    hdmi_write(0xF9, 0x00);

    // hdmi_write(0xFB, 0x06);     /* Low refresh rate 30Hz */

    hdmi_write(0x15, 0x01);     /* input video format: YCbCr 422, separate syncs */
    hdmi_write(0x16, 0x39);     /* output format 444, color depth 8 bit, input style 1 */

    // 0x48 should be align to 0x16 input style
    hdmi_write(0x48, 0x08);     /* bit justification for YCbCr 422: right justified */

    // 0x55 should be align to 0x16 output format
    // hdmi_write(0x55, 0x20);     /* output format: YCbCr 422 */
    hdmi_write(0x55, 0x40);     /* output format: YCbCr 444 */

    hdmi_write(0x18, 0x00);     /* CSC disabled */
    hdmi_write(0xAF, 0x16);     /* select HDMI mode */

    /* check ADV7511 status */
    BL_LOGD("Output format: 0x%02x\r\n", hdmi_read(0x55));
    BL_LOGD("PLL lock status: 0x%02x\r\n", hdmi_read(0x9E));
    BL_LOGI("VIC code: 0x%02x, 0x%02x, 0x%02x\r\n", hdmi_read(0x3D), hdmi_read(0x3E), hdmi_read(0x3F));

    return 0;
}

int adv7511_disable(void)
{
    hdmi_write(0x41, 0x50);     /* power down */

    return 0;
}

