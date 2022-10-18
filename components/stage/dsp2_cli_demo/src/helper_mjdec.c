#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <aos/kernel.h>
#include <vfs.h>
#include <cli.h>

#include <bl_mjdec.h>
#include "sample_common.h"
#include "helper_mjdec.h"

#define NV12_IMAGE_SIZE(width,height)   ((width)*(height)*3/2)

enum numeric_short_options {
	IMG_DUMP_ADDR = 1000,
	IMG_DUMP_SIZE,
};

typedef struct {
    uint32_t width;
    uint32_t height;
    uint8_t *jpeg_buf_addr;
    uint8_t *nv12_buf_addr;
} mjdec_config_t;

static mjdec_config_t mjdec_config;

static void jpeg_decode(void)
{
    bl_mjdec_config_t config;

    BL_LOGI("Alloc NV12 buffer\r\n");
    config.output_buf_addr = BL_MallocDMA(PSRAM_ID_FOR_STREAM_BUF,
        NV12_IMAGE_SIZE(mjdec_config.width, mjdec_config.height));

    config.width = mjdec_config.width;
    config.height = mjdec_config.height;
    config.quality = 50;

    bl_mjdec_set_config(&config);
    bl_mjdec_start_decoder(mjdec_config.jpeg_buf_addr);
}

static int vencfw_config(void)
{
    bl_mjdec_init();

    return 0;
}

static void show_usage(void)
{
	aos_cli_printf("enc [options]\r\n");
	aos_cli_printf("-s [addr] Start decoding jpeg from specific address \r\n");
}

static void mjdec_cmd(char *buf, int len, int argc, char **argv)
{
    static char fw_init = 0;
    uint32_t value = 0;
    uint32_t width, height;
    int ch;

    if (!fw_init) {
        if (0 != vencfw_config()) {
            BL_LOGE("vencfw_config err.\r\n");
            return;
        }
        fw_init = 1;
    }

    optind = 0;

    static struct option long_options[] =
    {
        {"input-size",      required_argument, 0, 'i'},
        {"start",           required_argument, 0, 's'},
        {"img-dump-addr",   no_argument,       0, IMG_DUMP_ADDR},
        {"img-dump-size",   no_argument,       0, IMG_DUMP_SIZE},
    };

    while ((ch = getopt_long (argc, argv, "i:s:h", long_options, NULL)) != -1) {
        switch (ch)
        {
        case 'i':
            if (utils_get_resolution_param(optarg, &width, &height) == 0) {
                BL_LOGI("set resolution %dx%d\r\n", width, height);
                mjdec_config.width = width;
                mjdec_config.height = height;
            } else {
                goto FAIL;
            }
            break;

        case 's':
            sscanf(optarg, "%x", &value);
            mjdec_config.jpeg_buf_addr = (uint8_t *)value;
            jpeg_decode();
            break;

        case IMG_DUMP_ADDR:
            value = (uint32_t)mjdec_config.nv12_buf_addr;
            aos_cli_printf("[OK] %u\r\n", value);
            break;

        case IMG_DUMP_SIZE:
            value = NV12_IMAGE_SIZE(mjdec_config.width, mjdec_config.height);
            aos_cli_printf("[OK] %u\r\n", value);
            break;

        case 'h':
		default:
			show_usage();
            goto FAIL;
        }
    }
    aos_cli_printf("[OK] \r\n");
    return;

FAIL:
    aos_cli_printf("[NG] \r\n");
    return;
}

const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
    { "mjdec", "mjpeg decoder related operation", mjdec_cmd },
};

int helper_mjdec_cli_init(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user) / sizeof(cmds_user[0]));
    return 0;
}

