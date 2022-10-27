#include "boot_cpu0.h"

#include <FreeRTOS.h>
#include <aos/kernel.h>
#include <aos/yloop.h>
#include <bl808_glb.h>
#include <bl808_glb_gpio.h>
#include <bl808_tzc_sec.h>
#include <bl_mm_clock.h>
#include <bl_mtd.h>
#include <bl_psram.h>
#include <bl_romfs.h>
#include <bl_sys.h>
#include <bl_timer.h>
#include <bl_wifi.h>
#include <cli.h>
#include <core_rv32.h>
#include <fs/vfs_romfs.h>
#include <getopt.h>
#include <hal_sys.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <task.h>
#include <vfs.h>
#include "m1s_msc.h"

#include "l2_sram.h"

#define C906_START_ADDR (0x50100000)

void mm_clk_config(void)
{
    bl_mm_xclk_config(XCLK_XTAL);                /*xclk select XTAL*/
    bl_mm_bclk_config(BCLK_MUXPLL_160M);         /*bclk1x select 160M*/
    bl_mm_cpu_root_clk_config(CPU_ROOT_CLK_PLL); /*cpu root clk select PLL*/
    bl_mm_cpu_clk_config(CPU_CLK_MUXPLL_400M);   /*cpu pll select 400M*/
    bl_mm_uart_clk_config(UART_CLK_XCLK1);       /*uart select xclk and xclk select XTAL*/
    bl_mm_i2c_clk_config(I2C_CLK_XCLK);          /*i2c select xclk and xclk select XTAL*/
}

int check_key_press(void)
{
    GLB_GPIO_Cfg_Type cfg;
    cfg.drive=0;
    cfg.smtCtrl=1;
    cfg.gpioFun = GPIO_FUN_GPIO;                
    cfg.gpioMode = GPIO_MODE_INPUT;
    cfg.pullType = GPIO_PULL_UP;
    cfg.gpioPin = 22;
    GLB_GPIO_Input_Enable(cfg.gpioPin);
    GLB_GPIO_Init(&cfg);

    cfg.gpioPin = 23;
    GLB_GPIO_Input_Enable(cfg.gpioPin);
    GLB_GPIO_Init(&cfg);

    if (!GLB_GPIO_Read(22) && !GLB_GPIO_Read(23)) {
        return 1;
    }
    return 0;
}

void c906_bringup(uint32_t start_addr)
{
    if (check_key_press()) {
        m1s_msc_init(2);
    } else {
#if 0
        // 留着这里的代码，加载产测固件时再修改
        int fd = -1;
        romfs_filebuf_t filebuf;
        fd = aos_open("/romfs/c906.bin", 0);
        aos_ioctl(fd, IOCTL_ROMFS_GET_FILEBUF, (long unsigned int)&filebuf);
        if (fd < 0) {
            printf("/romfs/c906.bin not found!\r\n");
            vTaskDelete(NULL);
            return;
        }

        aos_close(fd);
        printf("Found file %s. XIP Addr %p, len %lu\r\n",
                "/romfs/c906.bin",
                filebuf.buf,
                (unsigned long)filebuf.bufsize);
        memcpy((void *)start_addr, filebuf.buf, (unsigned long)filebuf.bufsize);
        csi_dcache_clean_range((uint32_t *)start_addr, (unsigned long)filebuf.bufsize);
#else
        bl_mtd_handle_t handle_d0fw;
        bl_mtd_info_t info;
        int ret = -1;

        if ((ret = bl_mtd_open("D0FW", &handle_d0fw, BL_MTD_OPEN_FLAG_BUSADDR))) {
            printf("[EF] [PART] [XIP] error when get D0FW partition %d\r\n", ret);
            return;
        }
        memset(&info, 0, sizeof(info));
        bl_mtd_info(handle_d0fw, &info);
        if (0 == info.xip_addr) {
            printf("D0FW has no XIP-Addr\r\n");
            return;
        }

        printf("D0FW addr:%#lx size:%#lx\r\n", (uint32_t)info.xip_addr, (uint32_t)info.size);
        memcpy((void *)start_addr, (void *)info.xip_addr, (unsigned long)info.size);
        csi_dcache_clean_range((uint32_t *)start_addr, (unsigned long)info.size);
        bl_mtd_close(handle_d0fw);
#endif
        /* boot c906 */
        hal_enable_cpu0();
        hal_halt_cpu0();
        mm_clk_config();
        l2_sram_vram_config();
        bl_mtimer_c906_clock_init();
        hal_boot_cpu0(start_addr);
        bl_mm_clk_dump();
    }
}

static void c906_bringup_entry(void *arg)
{
    c906_bringup(C906_START_ADDR);

    vTaskDelete(NULL);
}

static void cmd_halt_cpu0(char *buf, int len, int argc, char **argv) { hal_halt_cpu0(); }

static void cmd_release_cpu0(char *buf, int len, int argc, char **argv) { hal_release_cpu0(); }

static void sipeed_bl_sys_enabe_jtag(int cpuid)
{
    GLB_GPIO_Cfg_Type gpio_cfg;

    gpio_cfg.drive = 0;
    gpio_cfg.smtCtrl = 1;
    gpio_cfg.pullType = GPIO_PULL_NONE;

    gpio_cfg.gpioMode = GPIO_MODE_AF;
    switch (cpuid) {
        case 0: {
            gpio_cfg.gpioFun = GPIO_FUN_JTAG_M0;
            puts("Enable CPU0 (M0/E907) on PIN0/PIN1/PIN2/PIN3(TCK/TDI/TMS/TDO)\r\n");
        } break;
        case 1: {
            gpio_cfg.gpioFun = GPIO_FUN_JTAG_D0;
            puts("Enable CPU1 (D0/C906) on PIN0/PIN1/PIN2/PIN3(TCK/TDI/TMS/TDO)\r\n");
        } break;
        default: {
        } break;
    }
    gpio_cfg.gpioPin = GLB_GPIO_PIN_0;
    GLB_GPIO_Init(&gpio_cfg);

    gpio_cfg.gpioPin = GLB_GPIO_PIN_1;
    GLB_GPIO_Init(&gpio_cfg);

    gpio_cfg.gpioPin = GLB_GPIO_PIN_2;
    GLB_GPIO_Init(&gpio_cfg);

    gpio_cfg.gpioPin = GLB_GPIO_PIN_3;
    GLB_GPIO_Init(&gpio_cfg);
}

static void cmd_jtag_cpu0(char *buf, int len, int argc, char **argv) { sipeed_bl_sys_enabe_jtag(1); }

static void cmd_jtag_m0(char *buf, int len, int argc, char **argv) { sipeed_bl_sys_enabe_jtag(0); }

static void cmd_c906_bringup(char *buf, int len, int argc, char **argv) { xTaskCreate(c906_bringup_entry, (char *)"bootc906", 2048, NULL, 10, NULL); }

const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
    {"halt_cpu0", "cpu0 halt", cmd_halt_cpu0}, {"jtag_cpu0", "cpu0 jtag", cmd_jtag_cpu0}, {"release_cpu0", "cpu0 release", cmd_release_cpu0},
    {"c906", "setup c906", cmd_c906_bringup},  {"jtag_m0", "cpu m0 jtag", cmd_jtag_m0},
};

int boot_cpu0_cli_init(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds
    // list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    // return aos_cli_register_commands(cmds_user, sizeof(cmds_user)/sizeof(cmds_user[0]));
    return 0;
}
