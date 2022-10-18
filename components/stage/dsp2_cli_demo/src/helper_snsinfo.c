#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <aos/kernel.h>
#include <cli.h>
#include <bl_comm_sns.h>
#include "sensor.h"
#include "helper_snsinfo.h"

#define SNSINFO_MIPI_CTRL_CONFIG   (0x3001a000)
#define SNSINFO_MIPI_CTRL_SP_CNT   (0x3001a020)
#define SNSINFO_MIPI_DPHY_CONFIG   (0x3001a080)
#define SNSINFO_MIPI_PLL_CONFIG0   (0x20000790)
#define SNSINFO_MIPI_PLL_CONFIG5   (0x200007A4)
#define SNSINFO_MIPI_PLL_CONFIG6   (0x200007A8)
#define SNSINFO_MIPI_LDO15CSI      (0x200006c8)

#define SNSINFO_CSI_CR_CSI_EN_POS                                       (0U)
#define SNSINFO_CSI_CR_LANE_NUM_POS                                     (1U)
#define SNSINFO_CSI_CR_SYNC_SP_EN_POS                                   (5U)
#define SNSINFO_CSI_DL0_ENABLE_POS                                      (0U)
#define SNSINFO_CSI_DL1_ENABLE_POS                                      (1U)
#define SNSINFO_CSI_CL_ENABLE_POS                                       (2U)
#define SNSINFO_CSI_DL0_STOPSTATE_POS                                   (4U)
#define SNSINFO_CSI_DL1_STOPSTATE_POS                                   (5U)
#define SNSINFO_CSI_CL_STOPSTATE_POS                                    (6U)
#define SNSINFO_CSI_DL0_ULPSACTIVENOT_POS                               (8U)
#define SNSINFO_CSI_DL1_ULPSACTIVENOT_POS                               (9U)
#define SNSINFO_CSI_CL_ULPSACTIVENOT_POS                                (10U)

static const char* sensor_interface[] = {
    "DVP", "MIPI_1Lane", "MIPI_2Lane",
};

static void show_usage(void)
{
    aos_cli_printf("snsinfo [options]\r\n");
    aos_cli_printf("-c csi info \r\n");
    aos_cli_printf("-r csi reg \r\n");
}

static void print_sns_basic_info()
{
    const char* sns_name;
    uint32_t fps;
    uint32_t pix_clk;
    BL_Img_Size_T out_win;

    sensor_get_name(&sns_name);
    sensor_get_fps(&fps);
    sensor_get_pix_clk(&pix_clk);
    sensor_get_output_window(&out_win);

    printf("[Name]%s, [Res]%dx%d, [Fps]%d, [Pclk]%d, [IF]%s\r\n",
        sns_name, out_win.width, out_win.height, fps, pix_clk, sensor_interface[DSP2_INPUT_MODE]);
}

static void print_csi_info()
{
    uint32_t value;
    printf("=== mipi setting ===\r\n");
    value = *(uint32_t *)SNSINFO_MIPI_CTRL_CONFIG;
    printf("mipi ctrl: [en]%d, [lane_num]%d, [sync_sp]%d\r\n", \
        (value>>SNSINFO_CSI_CR_CSI_EN_POS)&1, (value>>SNSINFO_CSI_CR_LANE_NUM_POS&1)+1, (value>>SNSINFO_CSI_CR_SYNC_SP_EN_POS)&1);
    value = *(uint32_t *)SNSINFO_MIPI_DPHY_CONFIG;
    printf("mipi phy:  [clk_en]%d, [dl0_en]%d, [dl1_en]%d\r\n", \
        (value>>SNSINFO_CSI_CL_ENABLE_POS)&1, (value>>SNSINFO_CSI_DL0_ENABLE_POS)&1, (value>>SNSINFO_CSI_DL1_ENABLE_POS)&1);

    printf("=== mipi status ===\r\n");
    printf("mipi ctrl:[sp_cnt]%d\r\n", *(uint32_t *)SNSINFO_MIPI_CTRL_SP_CNT);
    printf("mipi phy in stop mode:    [clk]%d, [dl0]%d, [dl1]%d\r\n",  \
        (value>>SNSINFO_CSI_CL_STOPSTATE_POS)&1, (value>>SNSINFO_CSI_DL0_STOPSTATE_POS)&1, (value>>SNSINFO_CSI_DL1_STOPSTATE_POS)&1);
    printf("mipi phy not in ulp mode: [clk]%d, [dl0]%d, [dl1]%d\r\n", \
        (value>>SNSINFO_CSI_CL_ULPSACTIVENOT_POS)&1, (value>>SNSINFO_CSI_DL0_ULPSACTIVENOT_POS)&1, (value>>SNSINFO_CSI_DL1_ULPSACTIVENOT_POS)&1);
}

static void print_csi_reg_info()
{
    uint32_t addr;
    int i, j;

    // csi controller reg
    printf("=== mipi controller ===\r\n");
    addr = SNSINFO_MIPI_CTRL_CONFIG;
    i = 0;
    while(i++ < 3) {
        j = 0;
        printf("[%x]", addr);
        while(j++ < 4) {
            printf(" 0x%08x", *(uint32_t *)addr);
            addr = addr + 4;
        }
        printf("\r\n");
    }

    printf("=== mipi phy ===\r\n");
    addr = SNSINFO_MIPI_DPHY_CONFIG;
    j = 0;
    printf("[%x]", addr);
    while(j++ < 4) {
        printf(" 0x%08x", *(uint32_t *)addr);
        addr = addr + 4;
    }
    printf("\r\n");

    printf("=== mipi pll and io ===\r\n");

    addr = SNSINFO_MIPI_PLL_CONFIG5;
    printf("[%x] 0x%08x\r\n", addr, *(uint32_t *)addr);
    addr = SNSINFO_MIPI_PLL_CONFIG6;
    printf("[%x] 0x%08x\r\n", addr, *(uint32_t *)addr);
    addr = SNSINFO_MIPI_PLL_CONFIG0;
    printf("[%x] 0x%08x\r\n", addr, *(uint32_t *)addr);
    addr = SNSINFO_MIPI_LDO15CSI;
    printf("[%x] 0x%08x\r\n", addr, *(uint32_t *)addr);
}

static void snsinfo_cmd(char *buf, int len, int argc, char **argv)
{
    int ch;
    optind = 0;

    if (!sensor_is_inited()) {
        printf("sensor not connected or not inited\r\n");
        return;
    }

    static struct option long_options[] =
    {
        {"csi",     no_argument, 0, 'c'},
        {"csi-reg", no_argument, 0, 'r'},
        {0, 0, 0, 0},
    };

    print_sns_basic_info();

    if (1 == argc) {
        return;
    }

    while ((ch = getopt_long (argc, argv, "cr", long_options, NULL)) != -1) {
        switch (ch)
        {
            case 'c': {
                print_csi_info();
                break;
            }
            case 'r': {
                print_csi_reg_info();
                break;
            }
            default:
                show_usage();
                return;
        }
    }
}

const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
        { "snsinfo", "get sensor info", snsinfo_cmd },
};

int helper_snsinfo_cli_init(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user) / sizeof(cmds_user[0]));
    return 0;
}

