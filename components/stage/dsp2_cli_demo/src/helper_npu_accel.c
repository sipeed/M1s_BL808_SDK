#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <aos/kernel.h>
#include <vfs.h>
#include <cli.h>
#include "bl808_common.h"
#include "blai_core.h"
#include "blai_inst_cpu.h"
#include "blai_inst_npu.h"
#include "helper_nn.h"

enum nn_options {
	BLAI_NN_CONV = 1000,
};

static void do_npu_conv(void)
{
    blai_model_hdl_t hdl = blai_create();

    // Build NPU data buffer
    fixed_point_t* DATA_buf = (fixed_point_t*)BL_MallocDMA(0, 65536 * 4 * 32 * sizeof(fixed_point_t));
    memset(DATA_buf, 0, 65536 * 4 * 32 * sizeof(fixed_point_t));

    //net setting
    struct blai_net_info_t *net = blai_getNetInfo(hdl);
    net->use_npu_accel = 1;
    net->use_tflite = 0;
    net->unsign_input = 0;

    blai_npu_initCfg(hdl);

    //**************************//
    // test convolutional layer //
    //**************************//
    net->layers = (struct cpu_inst_layer_t*)BL_MallocDMA(0, 2*sizeof(struct cpu_inst_layer_t));
    int current_layer = 1;

    struct cpu_inst_layer_t *l = &net->layers[current_layer];
    memset(l, 0, sizeof(struct cpu_inst_layer_t));
    l->type = CONVOLUTIONAL;
    l->activation = RELU;
    l->w = 8;
    l->h = 8;
    l->c = 8;
    l->out_w = 8;
    l->out_h = 8;
    l->out_c = 8;
    l->n = 1; // number of input
    l->input_num = 1; // number of input
    l->size = 3;
    l->groups = 1;
    l->stride = 1;
    l->dilation = 1;

    l->fdata = 7;
    l->fweight = 6;
    l->fbias = 3;
    l->fout = 2;

    int input_size = l->w * l->h * l->c;
    int output_size = l->out_w * l->out_h * l->out_c;
    int filter_size = l->c * l->size * l->size * l->out_c;

    l->input_i8[0]  = (fixed_point_t*)BL_MallocDMA(0, input_size * sizeof(fixed_point_t));
    l->output_i8 = (fixed_point_t*)BL_MallocDMA(0, output_size * sizeof(fixed_point_t));
    l->weights = (int*)BL_MallocDMA(0, filter_size * sizeof(int));
    l->biases = (int*)BL_MallocDMA(0, l->out_c * sizeof(int));

    for (int i = 0; i < input_size; i++)
        l->input_i8[0][i] = (rand() % 256 - 128);
    for (int i = 0; i < filter_size; i++)
        l->weights[i] = (rand() % 256 - 128);
    for (int i = 0; i < l->out_c; i++)
        l->biases[i] = (rand() % 256 - 128);

    // NPU BEGIN
    forward_NPU(net, DATA_buf, current_layer);
    // NPU END
    printf("=========NPU===========\r\n");
    for (int i = 0; i < output_size; i++) {
        if (i && i % 16 == 0)
            printf("\n");
        printf("0x%02x, ", l->output_i8[i]);
    }
    // DSP BEGIN
    forward_CONVOLUTIONAL(net, l, DATA_buf, current_layer);
    // DSP END
    printf("=========DSP===========\r\n");
    for (int i = 0; i < output_size; i++) {
        if (i && i % 16 == 0)
            printf("\n");
        printf("0x%02x, ", l->output_i8[i]);
    }
}


static void blai_cmd(char *buf, int len, int argc, char **argv)
{
    int ch;
    optind = 0;

    static struct option long_options[] =
    {
        {"conv",            no_argument,       0, BLAI_NN_CONV},
        {0, 0, 0, 0}
    };

    while ((ch = getopt_long (argc, argv, "h", long_options, NULL)) != -1) {
        switch (ch)
        {
        case BLAI_NN_CONV:
            do_npu_conv();
            break;
        default:
            BL_LOGE("[%s:%d] command %d not found\r\n", __func__, __LINE__, ch);
            break;
        }
    }

}

const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
    { "blai_nn", "BL AI NN Example", blai_cmd },
};

int helper_nn_cli_init(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user) / sizeof(cmds_user[0]));
    return 0;
}

