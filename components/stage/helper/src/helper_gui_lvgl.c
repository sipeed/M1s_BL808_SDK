#include <stdio.h>
#include <cli.h>
#include "lvgl.h"
#include "lv_test_core/lv_test_core.h"
#include "lv_test_widgets/lv_test_label.h"
#include "lv_freetype.h"
#include "freetype.h"
#include <sys/time.h>
#include <stdlib.h>
#include <FreeRTOS.h>
#include <task.h>
#include <math.h>
#include <wchar.h>
#include "lv_port_disp.h"
#include "lv_api_map.h"
#include "lv_examples.h"
#include "aos/yloop.h"
#include "lv_port_tick.h"
#include "bl808_dma.h"
#include "bl808_dma2d.h"

#if LV_USE_GPU_DMA2D
#include LV_GPU_DMA2D_INCLUDE
#endif

#define DMA2D_TEST 0

#if DMA2D_TEST
static int test_check(lv_color_t *data, lv_color_t cmp_data, uint32_t len)
{
	int i;
	for (i = 0; i < len; i++) {
		if (cmp_data.full != data[i].full) {
			printf("error\r\n");
			return 1;
		}
	}
	return 0;
}


static DMA_LLI_Ctrl_Type lliList1[40];

static void Init_LLI_List(lv_color_t *buffer, lv_color_t color, uint32_t len)
{
    uint32_t i = 0;
    uint32_t count = len/3840;
    struct DMA_Control_Reg dmaCtrlRegVal={
        .TransferSize=3840,
        .SBSize=DMA_BURST_SIZE_4,
        .dst_min_mode=DISABLE,
        .DBSize=DMA_BURST_SIZE_4,
        .dst_add_mode=DISABLE,
        .SWidth=DMA_TRNS_WIDTH_32BITS,
        .DWidth=DMA_TRNS_WIDTH_32BITS,
        .fix_cnt=0,
        .SI=DMA_MINC_DISABLE,
        .DI=DMA_MINC_ENABLE,
        .I=1,
    };

    /* Init LLI List 1*/
    for(i = 0; i < count; i++) {
        lliList1[i].srcDmaAddr = (uint32_t)&color;
        lliList1[i].destDmaAddr = (uint32_t)&buffer[i * 3840];
        lliList1[i].nextLLI=0;
        if(i!=0){
            lliList1[i-1].nextLLI=(uint32_t)&lliList1[i];
        }
        if(i==count-1){
            dmaCtrlRegVal.I=1;
        }else{
            dmaCtrlRegVal.I=0;
        }
        lliList1[i].dmaCtrl= dmaCtrlRegVal;
    }
}

static void test_dma(lv_color_t *buffer, lv_color_t color, uint32_t len)
{
	uint32_t old, now;
	DMA_LLI_Cfg_Type lliCfg={
	    DMA_TRNS_M2M,
	    (DMA_Periph_Req_Type)0,
	    (DMA_Periph_Req_Type)0,
	};
	csi_dcache_disable();
	DMA_Channel_Cfg_Type chCfg={
		(uint32_t)&color,
		(uint32_t)buffer,
		3840,
	    DMA_TRNS_M2M,
		DMA_CH7,
	    DMA_TRNS_WIDTH_32BITS,
	    DMA_TRNS_WIDTH_32BITS,
	    DMA_BURST_SIZE_8,
	    DMA_BURST_SIZE_8,
	    DISABLE,
	    DISABLE,
	    0,
		DMA_MINC_DISABLE,
	    DMA_MINC_ENABLE,
	    DMA_REQ_NONE,
	    DMA_REQ_NONE,
	};
	Init_LLI_List(buffer, color, len);

    DMA_Channel_Disable(chCfg.ch);
	DMA_LLI_Init(chCfg.ch,&lliCfg);
	DMA_Enable();

    old = custom_tick_get();
	DMA_LLI_Update(chCfg.ch, (uint32_t)&(lliList1[0]));
	DMA_Channel_Enable(chCfg.ch);
	while(DMA_Channel_Is_Busy(chCfg.ch)==SET) {
	}
	now = custom_tick_get() - old;
	csi_dcache_enable();
	printf("dma fill %d pixels time = %d ms\r\n", len, now);
}

static void wait_finish(void)
{
    while (SET == DMA2D_Channel_Is_Busy(DMA2D0_ID, 0)) {
    }
}

static void gpu_dma2d_copy(lv_color_t * buf, lv_coord_t buf_w, const lv_color_t * map, lv_coord_t map_w,
                           lv_coord_t copy_w, lv_coord_t copy_h, DMA2D_Trans_Width_Type type)
{
	DMA2D_LLI_Ctrl_Type lliCfg;

	csi_dcache_disable();
	DMA2D_Picture_Cfg_Type fillCfg =
	{
		.transWidth = type,
		.pixWidth = 4,
		.srcAddr = (uint32_t)map,
		.srcWidth = map_w,
		.srcX0 = 0,
		.srcY0 = 0,
		.srcX1 = copy_w,
		.srcY1 = copy_h,
		.dstAddr = (uint32_t)buf,
		.dstWidth = buf_w,
		.dstX0 = 0,
		.dstY0 = 0,
	};
	csi_dcache_enable();

	DMA2D_Picture_Translate_Calculate(&fillCfg, &lliCfg);
	DMA2D_Picture_Transfer_Start(DMA2D0_ID, 0, &lliCfg);
	wait_finish();
}

__attribute__((section(".tcm_code"))) static lv_color_t buffer[320 * 480];
__attribute__((section(".tcm_code"))) static lv_color_t buffer_tmp[320 * 480];

#define COLOR_KEY_VALUE_4BYTE   0x00000000
#define COLOR_KEY_VALUE_3BYTE   0x112233
#define COLOR_KEY_VALUE_2BYTE   0xaabb
#define COLOR_KEY_VALUE_1BYTE   0x55

static void dma2d_color_key_4byte()
{
	int i;
	uint32_t old, now;

	// color key
	memset(buffer_tmp, 0, sizeof(buffer_tmp));
	memset(buffer, 0x10, sizeof(buffer));
	csi_dcache_disable();
	for (i = 0; i < 320 * 480; i += 2) {
		buffer_tmp[i].full = COLOR_KEY_VALUE_4BYTE;
	}
	csi_dcache_enable();

	old = custom_tick_get();
	lv_gpu_dma2d_enable_color_key();
	lv_gpu_dma2d_copy(buffer, 320, buffer_tmp, 320, 320, 480);
	lv_gpu_dma2d_disable_color_key();
	now = custom_tick_get() - old;

	for (i = 0; i < 320 * 480; i += 2) {
		if (buffer[i].full == COLOR_KEY_VALUE_4BYTE) {
			printf("DMA2D copy colorkey failed!!!\r\n");
			return;
		}
	}

	printf("DMA2D copy colorkey 4byte %d pixels time = %d ms\r\n", 320 * 480, now);
}

static void dma2d_color_key_3byte()
{
	int i;
	uint32_t old, now;
	uint8_t *buffer3 = buffer;
	uint8_t *buffer3_tmp = buffer_tmp;

	// color key
	memset(buffer_tmp, 0, sizeof(buffer_tmp));
	memset(buffer, 0x10, sizeof(buffer));
	csi_dcache_disable();
	for (i = 0; i < sizeof(buffer_tmp); i += 2 * 3) {
		buffer3_tmp[i]     = (COLOR_KEY_VALUE_3BYTE & 0xff);
		buffer3_tmp[i + 1] = (COLOR_KEY_VALUE_3BYTE >> 8) & 0xff;
		buffer3_tmp[i + 2] = (COLOR_KEY_VALUE_3BYTE >> 16) & 0xff;
	}
	csi_dcache_enable();

	old = custom_tick_get();
	DMA2D_Color_Key_Enable(DMA2D0_ID, 0, DMA2D_COLOR_KEY_24BIT, COLOR_KEY_VALUE_3BYTE);
	gpu_dma2d_copy(buffer3, 320, buffer3_tmp, 320, 320, 480, DMA2D_TRNS_WIDTH_32BITS);
	DMA2D_Color_Key_Disable(DMA2D0_ID, 0);
	now = custom_tick_get() - old;

	for (i = 0; i < sizeof(buffer_tmp); i += 2 * 3) {
		if ((buffer3[i] == (COLOR_KEY_VALUE_3BYTE & 0xff)) &&
			(buffer3[i + 1] == ((COLOR_KEY_VALUE_3BYTE >> 8) & 0xff)) &&
			(buffer3[i + 2] == ((COLOR_KEY_VALUE_3BYTE >> 16) & 0xff))) {
			printf("DMA2D copy colorkey 3byte failed!!!\r\n");
			return;
		}
	}

	printf("DMA2D copy colorkey 3byte %d pixels time = %d ms\r\n", 320 * 480, now);
}

static void dma2d_color_key_2byte()
{
	int i;
	uint32_t old, now;

	// color key
	memset(buffer_tmp, 0, sizeof(buffer_tmp));
	memset(buffer, 0x10, sizeof(buffer));
	csi_dcache_disable();
	for (i = 0; i < 320 * 480; i += 2) {
		buffer_tmp[i].ch.blue  = (COLOR_KEY_VALUE_2BYTE & 0xff);
		buffer_tmp[i].ch.green = (COLOR_KEY_VALUE_2BYTE >> 8) & 0xff;
	}
	csi_dcache_enable();

	old = custom_tick_get();
	DMA2D_Color_Key_Enable(DMA2D0_ID, 0, DMA2D_COLOR_KEY_16BIT, COLOR_KEY_VALUE_2BYTE);
	gpu_dma2d_copy(buffer, 320, buffer_tmp, 320, 320, 480, DMA2D_TRNS_WIDTH_16BITS);
	DMA2D_Color_Key_Disable(DMA2D0_ID, 0);
	now = custom_tick_get() - old;

	for (i = 0; i < 320 * 480; i += 2) {
		if ((buffer[i].ch.blue == (COLOR_KEY_VALUE_2BYTE & 0xff)) &&
			(buffer[i].ch.green == ((COLOR_KEY_VALUE_2BYTE >> 8) & 0xff))) {
			printf("DMA2D copy colorkey 2byte failed!!!\r\n");
			return;
		}
	}

	printf("DMA2D copy colorkey 2byte %d pixels time = %d ms\r\n", 320 * 480, now);
}

static void dma2d_color_key_1byte()
{
	int i;
	uint32_t old, now;

	// color key
	memset(buffer_tmp, 0, sizeof(buffer_tmp));
	memset(buffer, 0x10, sizeof(buffer));
	csi_dcache_disable();
	for (i = 0; i < 320 * 480; i += 2) {
		buffer_tmp[i].ch.blue  = (COLOR_KEY_VALUE_1BYTE & 0xff);
	}
	csi_dcache_enable();

	old = custom_tick_get();
	DMA2D_Color_Key_Enable(DMA2D0_ID, 0, DMA2D_COLOR_KEY_8BIT, COLOR_KEY_VALUE_1BYTE);
	gpu_dma2d_copy(buffer, 320, buffer_tmp, 320, 320, 480, DMA2D_TRNS_WIDTH_8BITS);
	DMA2D_Color_Key_Disable(DMA2D0_ID, 0);
	now = custom_tick_get() - old;

	for (i = 0; i < 320 * 480; i += 2) {
		if ((buffer[i].ch.blue == (COLOR_KEY_VALUE_1BYTE & 0xff))) {
			printf("DMA2D copy colorkey 1byte failed!!!\r\n");
			return;
		}
	}

	printf("DMA2D copy colorkey 1byte %d pixels time = %d ms\r\n", 320 * 480, now);
}

static void dma2d_test(void)
{
	volatile lv_color_t color;
	int i;
	uint32_t old, now;

	color.full = 100;

	memset(buffer, 0, sizeof(buffer));
	test_dma(buffer, color, 320 * 480);
	if (test_check(buffer, color, 320 * 480)) {
		return;
	}

	memset(buffer, 0, sizeof(buffer));
	old = custom_tick_get();
	lv_gpu_dma2d_enable_color_key();
	lv_gpu_dma2d_fill(buffer, 320, color, 320, 480);
	lv_gpu_dma2d_disable_color_key();
	now = custom_tick_get() - old;
	if (test_check(buffer, color, 3840)) {
		return;
	}

	printf("dma2d fill %d pixels time = %d ms\r\n", 320 * 480, now);

	memset(buffer, 0, sizeof(buffer));
	csi_dcache_disable();
	old = custom_tick_get();
	for (i = 0; i < 320 * 480; i++) {
		buffer[i].full = color.full;
	}
	now = custom_tick_get() - old;
	csi_dcache_enable();

	if (test_check(buffer, color, 320 * 480)) {
		return;
	}
	printf("CPU fill %d pixels time = %d ms\r\n", 320 * 480, now);

	dma2d_color_key_4byte();
	dma2d_color_key_3byte();
	dma2d_color_key_2byte();
	dma2d_color_key_1byte();
}
#endif

void lvgl_test_main(void *p_arg)
{
    printf("Call lv_init...\r\n");

    lv_init();
#if LV_USE_GPU_DMA2D
    lv_gpu_dma2d_init(0);
#endif
    lv_port_disp_init();

#if DMA2D_TEST
    dma2d_test();
#else
    //lv_example_keyboard_1();
    //lv_example_dropdown_1();
    //void lv_demo_benchmark(void);
    //lv_demo_benchmark();
    lv_example_btnmatrix_2();

    while (1) {
        lv_task_handler();
    }
#endif
    printf("Exit with success!\n");
    vTaskDelete(NULL);
}

static TaskHandle_t g_lvgl_task;

static void cmd_lvgl(char *buf, int len, int argc, char **argv)
{
    xTaskCreate(lvgl_test_main, (char*)"lvgl", 1024 * 8,
                NULL, 30, &g_lvgl_task);
}

const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
    {"lvgl", "lvgl test", cmd_lvgl},
};

int helper_lvgl_cli_init(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user)/sizeof(cmds_user[0]));
    return 0;
}

