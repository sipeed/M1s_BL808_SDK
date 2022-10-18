#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <aos/kernel.h>
#include <cli.h>

//#include "cpu_utils.h"
#include "mm_dsp2.h"
#include "sample_common.h"
#include "motion_detect.h"


#define PERFORMANCE_MONITOR         (0)


#if PERFORMANCE_MONITOR
#define HANDL_CNT_FOR_ONE_STATS     30
static int md_handl_cnt = 0;
static TickType_t md_handl_start_time = 0;
#endif

static int md_data_chann_id = 0;
static bool md_enable = 0;

static void motion_detection_entry(void *pvParameters)
{
    int i;
    int alarm_count = 0;
    uint32_t width, height;
    AlarmInfoArray alarm_info;
    MMDSP2YuvFrame yuv_frame;
    Rect zone = {0, 999, 0, 999};

    sample_get_chann_resolution(md_data_chann_id, &width, &height);
    BL_LOGI("[MD] resolution: %dx%d\r\n", width, height);

    md_init(width, height);
    add_alarm_zone(&zone, 0, ALARM_SENSITY_LV5);

    MM_DSP2_StartRecvPic(md_data_chann_id, PIX_FMT_GRAY8);

    while (md_enable) {
        MM_DSP2_GetOnePicture(md_data_chann_id, &yuv_frame);
        BL_LOGD("[MD] get Y frame, addr 0x%p, size %d\r\n", yuv_frame.frameStartAddr, yuv_frame.frameSize);

        motion_detect(yuv_frame.frameStartAddr, &alarm_info, &alarm_count);
        for (i = 0; i < alarm_count; i++) {
            BL_LOGI("[MD] Alarm in zone [%d]\r\n", alarm_info[i].id);
        }

#if PERFORMANCE_MONITOR
        do_frame_rate_stats("MD handl", &md_handl_cnt, HANDL_CNT_FOR_ONE_STATS, &md_handl_start_time);
#endif
    }

    MM_DSP2_StopRecvPic(md_data_chann_id);
    rm_alarm_zone(0);
    md_deinit();

    aos_task_exit(0);
}

static void md_start(void)
{
    aos_task_new("motion_detection", motion_detection_entry, NULL, 2048);
}

static int mdfw_config(void)
{
#if 0
    MMDSP2FrmSrcAttr frmsrc_attr;

    MM_DSP2_GetFrameSrcChnAttr(md_data_chann_id, &frmsrc_attr);
    frmsrc_attr.picWidth = 160;
    frmsrc_attr.picHeight = 120;
    frmsrc_attr.dsp2Position = DSP2_POSITION_SCALER_A;
    MM_DSP2_SetFrameSrcChnAttr(md_data_chann_id, &frmsrc_attr);
#endif
    return 0;
}

static void show_usage(void)
{
	aos_cli_printf("md [options]\r\n");
	aos_cli_printf("-c [chann_id] Set the chann id for MD data src \r\n");
	aos_cli_printf("-s Start motion detection \r\n");
	aos_cli_printf("-e Stop motion detection \r\n");
}

static void md_cmd(char *buf, int len, int argc, char **argv)
{
    static char fw_init = 0;
    int ch;

    optind = 0;

    static struct option long_options[] =
    {
        {"chann-id",            required_argument,  0, 'c'},
        {"md-start",            no_argument,        0, 's'},
        {"md-end",              no_argument,        0, 'e'},
        {0, 0, 0, 0}
    };

    if (!fw_init) {
        if (0 != mdfw_config()) {
            BL_LOGE("mdfw_config err.\r\n");
            return;
        }
        fw_init = 1;
    }

    while ((ch = getopt_long (argc, argv, "c:seh", long_options, NULL)) != -1) {
        switch (ch)
        {
        case 'c':
            md_data_chann_id = atoi(optarg);
            break;

        case 's':
            if (!md_enable) {
                md_enable = 1;
                md_start();
            }
            break;

        case 'e':
            if (md_enable) {
                md_enable = 0;
            }
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
    { "md", "motion detection demo", md_cmd },
};

int helper_md_cli_init(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user) / sizeof(cmds_user[0]));
    return 0;
}

