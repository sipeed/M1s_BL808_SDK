#include <time.h>
#include <math.h>
#include <ft2build.h>
#include "freetype.h"
#include "bl808_common.h"
#include "bl-api-osd.h"
#include <queue.h>

#define BG_COLOR_INDEX	0
#define FG_COLOR_INDEX	1

#define CAL_EVEN(a)	(a & -2)
#define CAL_ODD(a)	(a | 1)

#define SHIFT_CAL(a, b, c, d)	((a << 24) | (b << 16) | (c << 8) | d)

#define BIT2BYTE	8
#define DWORD_LENGTH	8	/* length in dword(8Bytes) */

#define mainSTART_AP_TASK_PRIORITY (20)

static time_t sys_now = 0;
static time_t sys_last = 0;
static char sys_time[LENGTH_OF_BUF];

static u32 tick_now = 0;
static u32 tick_last = 0;
static char boot_time[LENGTH_OF_BUF];

static char frame_id[LENGTH_OF_BUF];
static char **names;
static u8 detect_msg[101];
struct bl_device_osd *dev_osd = NULL;

/*
 * COMMON
 */

static void draw_bitmap(FT_Bitmap* bitmap, FT_Int x, FT_Int y,
				uint8_t *out_buf, uint32_t width, uint32_t height)
{
	FT_Int i, j, p, q;
	FT_Int x_max = x + bitmap->width;
	FT_Int y_max = y + bitmap->rows;

	/* for simplicity, we assume that `bitmap->pixel_mode' */
	/* is `FT_PIXEL_MODE_GRAY' (i.e., not a bitmap font)   */

	for(i = x, p = 0; i < x_max; i++, p++) {
		for (j = y, q = 0; j < y_max; j++, q++) {
			if (i < 0 || j < 0 || i >= width || j >= height)
				continue;
			out_buf[j * width + i] |= bitmap->buffer[q * bitmap->width + p];
		}
	}
}

#if 0
/*
 * This func can be used to check if recombine_data is right by uart.
 */
static void show_image(uint8_t *image, uint32_t width, uint32_t height)
{
	int  i, j;
	putchar('\r');
	putchar('\n');
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++)
			putchar(image[i * width + j] == 0 ? '*'
					: image[i * width + j] < 128 ? ' '
					: ' ');
		putchar('\r');
		putchar('\n');
	}
}
#endif

static void bl_osd_recombine_data(const struct osd_freetype_font *font, const char *src, u8 *dest)
{
	uint32_t len;
	FT_Face face;
	FT_Vector pen;
	FT_GlyphSlot slot;
	FT_Library library;

	/* initialize library */
	FT_Error error = FT_Init_FreeType(&library);
	/* create face object */
	error = FT_New_Face(library, "/romfs/arial.ttf", 0, &face);
	/* set character size */
	error = FT_Set_Char_Size(face, font->width * 2 * 64, font->height * 64,
					font->horz_resolution, font->vert_resolution );

	slot = face->glyph;
	pen = font->pen;
	len = strlen(src);

	for (int n = 0; n < len; n++) {
		/* set transformation */
		FT_Set_Transform(face, (FT_Matrix*)&font->matrix, &pen);

		/* load glyph image into the slot (erase previous one) */
		error = FT_Load_Char(face, src[n], FT_LOAD_RENDER);
		if (error)
			continue; /* ignore errors */

		draw_bitmap(&slot->bitmap, slot->bitmap_left,
				(uint32_t)font->height - slot->bitmap_top,
				dest, font->width * len, font->height);

		/* increment pen position */
		pen.x += slot->advance.x;
		//pen.x += font->width * 64;
		pen.y += slot->advance.y;
	}
	FT_Done_Face(face);
	FT_Done_FreeType(library);
}

static void bl_osd_blend_set_axis(void __iomem *base_addr, struct text_config *text)
{
	u32 x_start, x_end, y_start, y_end;

	x_start = text->x.start;
	x_end = text->x.end;
	y_start = text->y.start;
	y_end = text->y.end;

	osd_blend_set_axis(base_addr, x_start, x_end, y_start, y_end);
}

static void bl_osd_blend_set_fmt(void __iomem *base_addr, struct text_config *text)
{
	u32 color_order_a, color_order_rv, color_order_gy, color_order_bu;

	/* 
	 * order --- from LSB to MSB.
	 * eg1: order_a = 3, order_rv=2, order_gy=1, order_bu=0
	 * Byte Address: 0x7   0x6   0x5   0x4   0x3   0x2   0x1   0x0
	 *     ARGB8888:  A1    R1    G1    B1    A0    R0    G0    B0
	 *
	 * eg2: order_a = 3, order_rv=0, order_gy=2, order_bu=1
	 * Byte Address: 0x7   0x6   0x5   0x4   0x3   0x2   0x1   0x0
	 *     AYUV8888:  A1    Y1    U1    V1    A0    Y0    U0    V0
	 *
	 * in order to standardize, do as below:
	 * ry -> order3, gu -> order2, bv -> order1, a -> order0
	 */
	color_order_a = OSD_TEXT_COLOR_ORDER0;
	color_order_rv = OSD_TEXT_COLOR_ORDER3;
	color_order_gy = OSD_TEXT_COLOR_ORDER2;
	color_order_bu = OSD_TEXT_COLOR_ORDER1;

	osd_blend_palette_format_set(base_addr, text->color_fmt,
					color_order_a, color_order_rv,
					color_order_gy, color_order_bu);
}

static void bl_osd_blend_set_data(void __iomem *base_addr, void *data, u32 count)
{
	intptr_t data_addr;

	data_addr = (intptr_t)data;
	osd_blend_set_data(base_addr, (u32)data_addr, count);
}

static void bl_osd_blend_set_palette(void __iomem *base_addr, struct text_config *text, u8 (*palette)[3])
{
	u32 i = 0;

	switch (text->bpp)
	{
	case BPP1:
		osd_blend_palette_update(base_addr, BG_COLOR_INDEX,
						text->bg_color | text->bg_alpha);
		osd_blend_palette_update(base_addr, FG_COLOR_INDEX,
						text->fg_color | text->fg_alpha);
		break;
	case BPP8:
		if (palette == NULL) {
			osd_blend_palette_update(base_addr, BG_COLOR_INDEX,
						text->bg_color | text->bg_alpha);
			for (int i = 1; i < 256; i++) {
				osd_blend_palette_update(base_addr, i,
							text->fg_color | text->fg_alpha);
			}
		} else {
			for (i = 0; i < 256; i++) {
				osd_blend_palette_update(base_addr, i,
							SHIFT_CAL(palette[i][0], palette[i][1],
							palette[i][2], text->fg_alpha));
			}
		};
		break;
	default:
		break;
	}
}

static int get_osd_blend_chn(void)
{
	int i = 0;;

	for (i = OSD_BASE_DRAW_CNT + 1; i < OSD_BASE_BLEND_CNT; i++)
		if (!test_bit(i, &dev_osd->chn))
			break;

	if (i == OSD_BASE_BLEND_CNT) {
		BL_LOGE("[OSD] blend is not enough\r\n");
		return -NORESC;
	}
	set_bit(i, &dev_osd->chn);

	return i;
}

static int get_osd_draw_chn(u32 *chn)
{
	int i = 0, j = 0;

	for (i = 0; i < OSD_BASE_DRAW_CNT; i++) {
		if (!test_bit(i, &dev_osd->chn))
			set_bit(i, &dev_osd->chn);

		for (j = 0; j < LAYERS_OF_EACH_DRAW; j++)
			if (!test_bit(j, &dev_osd->layer[i]))
				goto layer_cfg;
	}

	if (i == OSD_BASE_DRAW_CNT) {
		BL_LOGE("[OSD] draw is not enough\r\n");
		return -NORESC;
	}

layer_cfg:
	*chn = i;
	return j;
}

/*
 * API
 */
int bl_osd_draw(struct draw_config *draw)
{
	int ret = 0;
	void __iomem *base_addr;
	u32 x_start, x_end, y_start, y_end, draw_yuvt;

	x_start = CAL_EVEN(draw->x.start);
	x_end = CAL_ODD(draw->x.end);
	y_start = CAL_EVEN(draw->y.start);
	y_end = CAL_ODD(draw->y.end);

	draw_yuvt = draw->color | draw->thickness;
	draw_yuvt = CAL_EVEN(draw_yuvt);

	ret = get_osd_draw_chn(&draw->chn);
	if (ret < 0)
		return ret;
	draw->layer = ret;

	base_addr = get_osd_base_addr(draw->chn);

	osd_draw_enable(base_addr, draw->layer, ENABLE);
	osd_draw_type(base_addr, draw->layer, draw->type);
	osd_draw_partial_config(base_addr, draw->layer, draw_yuvt, x_start, x_end, y_start, y_end);

	set_bit(draw->layer, &dev_osd->layer[draw->chn]);

	return ret;
}

void bl_osd_draw_enable(struct draw_config *draw, u32 enable)
{
	void __iomem *base_addr;

	base_addr = get_osd_base_addr(draw->chn);

	if (base_addr) {
		osd_draw_enable(base_addr, draw->layer, enable);

		if (enable)
			set_bit(draw->layer, &dev_osd->layer[draw->chn]);
		else
			clear_bit(draw->layer, &dev_osd->layer[draw->chn]);
	}
}

void bl_osd_draw_reset(u32 chn)
{
	void __iomem *base_addr;

	base_addr = get_osd_base_addr(chn);
	if (base_addr) {
		osd_draw_reset(base_addr);
		dev_osd->layer[chn] = 0;
		clear_bit(chn, &dev_osd->chn);
	}
}

int bl_osd_set_logo(struct text_config *text, void *data, u32 bytes, u8 (*palette)[3])
{
	int i = 0, ret = 0;
	void __iomem *base_addr;

	ret = get_osd_blend_chn();
	if (ret < 0)
		return ret;
	text->chn = ret;

	base_addr = get_osd_base_addr(text->chn);

	osd_blend_enable_layer(base_addr, DISABLE);
	bl_osd_blend_set_axis(base_addr, text);
	bl_osd_blend_set_fmt(base_addr, text);
	bl_osd_blend_set_data(base_addr, data, bytes / DWORD_LENGTH);
	bl_osd_blend_set_palette(base_addr, text, palette);
#ifdef ENABLE_REMOVE_WHITE_PALETTE
	/*
	 * An extra palette_update is required because the alpha of white color should
	 * be 0 for aesthetic.
	 * it depends on the specific case.
	 */
	for (i = 0; i < 256; i++) {
		if (palette[i][0] >= 240 && palette[i][1] >= 240 && palette[i][2] >= 240)
			osd_blend_palette_update(base_addr, i, 0xffffff00);
	}
#endif
	osd_blend_mem_req_line(base_addr, 0);
	osd_blend_enable_layer(base_addr, ENABLE);

	return ret;
}

int bl_osd_user_text(struct text_config *text, struct osd_freetype_font *font,
			char *data, u8 *recombine_data)
{
	void __iomem *base_addr;

	u32 stride, len;
	int ret = 0;

	ret = get_osd_blend_chn();
	if (ret < 0)
		return ret;
	text->chn = ret;

	len = strlen(data);
	stride = font->width * font->height * text->bpp / BIT2BYTE;

	if (NULL == recombine_data) {
		recombine_data = (u8 *)pvPortMalloc(sizeof(u8) * stride * len);
		if (NULL == recombine_data) {
			BL_LOGE("[OSD] malloc fail\r\n");
			return -NORESC;
		}
		memset(recombine_data, 0, sizeof(u8) * stride * len);
	}

	text->x.end = text->x.start + font->width * len - 1;
	text->y.end = text->y.start + font->height - 1;

	bl_osd_recombine_data(font, data, recombine_data);
	csi_dcache_clean_range((uintptr_t *)recombine_data, stride * len);

	base_addr = get_osd_base_addr(text->chn);

	osd_blend_enable_layer(base_addr, DISABLE);
	bl_osd_blend_set_axis(base_addr, text);
	bl_osd_blend_set_fmt(base_addr, text);
	bl_osd_blend_set_data(base_addr, recombine_data, len * stride / DWORD_LENGTH);
	bl_osd_blend_set_palette(base_addr, text, NULL);
	osd_blend_mem_req_line(base_addr, 0);
	osd_blend_enable_layer(base_addr, ENABLE);

	return ret;
}

static TaskHandle_t osd_seof = NULL;

void osd_seof_wakeup(void)
{
	BaseType_t xHigherPriorityTaskWoken;
	xHigherPriorityTaskWoken = pdFALSE;
	vTaskNotifyGiveFromISR(osd_seof, &xHigherPriorityTaskWoken);
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

static QueueHandle_t AI_xQueue = NULL;

void osd_ai_draw_send(u8 *detect_result)
{
	xQueueSend(AI_xQueue, detect_result, portMAX_DELAY);
}

static void bl_osd_copy_text(struct dynamic_text *dtext, char *src)
{
	struct text_config *text = dtext->cfg;
	struct osd_freetype_font * font = dtext->font;
	u32 total_width;

	dtext->index++;
	if (dtext->index == NUM_OF_BUF)
		dtext->index = 0;

	memset(dtext->data[dtext->index], 0, sizeof (char) * LENGTH_OF_BUF);
	strcpy(dtext->data[dtext->index], src);

	dtext->use_len = strlen(dtext->data[dtext->index]);
	total_width = dtext->use_len * font->width;

	text->x.end = text->x.start + total_width - 1;
	text->y.end = text->y.start + font->height - 1;

	memset(dtext->recombine_data[dtext->index], 0,
				sizeof(u8) * dtext->font_stride * dtext->use_len);
	bl_osd_recombine_data(dtext->font, dtext->data[dtext->index],
				dtext->recombine_data[dtext->index]);
	csi_dcache_clean_range((uintptr_t *)dtext->recombine_data[dtext->index],
				dtext->font_stride * dtext->use_len);
}

static void bl_osd_update_text(struct dynamic_text *dtext)
{
	void __iomem *base_addr;
	struct text_config *text = dtext->cfg;

	u32 count = dtext->use_len * dtext->font_stride / DWORD_LENGTH;
	
	base_addr = get_osd_base_addr(text->chn);

	osd_blend_enable_layer(base_addr, DISABLE);	
	bl_osd_blend_set_axis(base_addr, text);
	bl_osd_blend_set_data(base_addr, dtext->recombine_data[dtext->index], count);
	osd_blend_enable_layer(base_addr, ENABLE);
}

void bl_osd_blend_reset(u32 chn)
{
	void __iomem *base_addr; 

	base_addr = get_osd_base_addr(chn);
	if (base_addr) {
		osd_blend_enable_layer(base_addr, DISABLE);
		clear_bit(chn, &dev_osd->chn);
	}
}

static void osd_sof_handler(void)
{
	if (test_bit(BL_OSD_SYSTIME, &dev_osd->funcs)) {
		sys_now = time(NULL);

		if (sys_now != sys_last) {
			struct dynamic_text *syst = dev_osd->systime;
    			struct tm *utc_tm = gmtime(&sys_now);
			memset(sys_time, 0, sizeof(sys_time));
			sys_last = sys_now;

			//sprintf(sys_time, "%s", ctime(&sys_now));
			sprintf(sys_time, "%s", asctime(utc_tm));
			sys_time[strlen(sys_time) - 1] = '\0';

			bl_osd_copy_text(syst, sys_time);

			bl_osd_update_text(syst);

			return;
		}
        }

	if (test_bit(BL_OSD_BOOTTIME, &dev_osd->funcs)) {
		tick_now = xTaskGetTickCount() / 1000;

		if (tick_now != tick_last) {
			struct dynamic_text *bt = dev_osd->boottime;
			tick_last = tick_now;

			memset(boot_time, 0, sizeof(boot_time));
			sprintf(boot_time, "%d", tick_now);

			bl_osd_copy_text(bt, boot_time);

			bl_osd_update_text(bt);

			return;
		}
        }

	if (test_bit(BL_OSD_FRAMES, &dev_osd->funcs)) {
		struct dynamic_text *frames = dev_osd->frames;

		memset(frame_id, 0, sizeof(frame_id));
		sprintf(frame_id, "%d", dev_osd->fcount);

		bl_osd_copy_text(frames, frame_id);

		bl_osd_update_text(frames);
        }
}

static void osd_eof_handler(void)
{
}

static void ai_detect_proc(void)
{
    int i;
    char num[4][30];
    uint8_t count;
    struct draw_config ai_draw_config;
    ai_draw_config.chn = OSD_BASE_A_DRAW_LAYER_L;
    if (AI_xQueue) {
        if (xQueueReceive(AI_xQueue, detect_msg, 0)) {
            bl_osd_draw_reset(ai_draw_config.chn);
            for (i = 0; i < 4; i++) {
                bl_osd_blend_reset(dev_osd->ai_msg[i]->cfg->chn);
            }
            count = 0;
            for (i = 0; i < detect_msg[0]; i++) {
                if (detect_msg[2 + i * 10] > 40) {
                    ai_draw_config.type = TYPE_HOLLOW;
                    ai_draw_config.color = OSD_YUV_GREEN;
                    ai_draw_config.thickness = 8;
                    ai_draw_config.x.start = (detect_msg[3 + i * 10] << 8) | detect_msg[4 + i * 10];
                    ai_draw_config.y.start = (detect_msg[5 + i * 10] << 8) | detect_msg[6 + i * 10];
                    ai_draw_config.x.end = ai_draw_config.x.start + ((detect_msg[7 + i * 10] << 8) | detect_msg[8 + i * 10]);
                    ai_draw_config.y.end = ai_draw_config.y.start + ((detect_msg[9 + i * 10] << 8) | detect_msg[10 + i * 10]);
                    bl_osd_draw(&ai_draw_config);
                    if (count < 4) {
                        memset(num[count], 0, sizeof(num[0]));
                        sprintf(num[count], "%s %d%%", names[detect_msg[1 + i * 10]], (int)detect_msg[2 + i * 10]);
                        dev_osd->ai_msg[count]->cfg->x.start = ai_draw_config.x.start + 8;
                        dev_osd->ai_msg[count]->cfg->y.start = ai_draw_config.y.start + 8;
                        if ((dev_osd->ai_msg[count]->cfg->x.start + 16 * strlen(num[count])) > 1920) {
                            dev_osd->ai_msg[count]->cfg->x.start -= dev_osd->ai_msg[count]->cfg->x.start + 16 * strlen(num[count]) - 1920;
                        }
                        if (dev_osd->ai_msg[count]->cfg->y.start + 32 > 1080) {
                            dev_osd->ai_msg[count]->cfg->y.start -= dev_osd->ai_msg[count]->cfg->y.start + 32 - 1080;
                        }
                        count++;
                    }
                }
            }
            for (i = 0; i< count; i++) {
                    bl_osd_copy_text(dev_osd->ai_msg[i], num[i]);
                    bl_osd_update_text(dev_osd->ai_msg[i]);
            }
        }
    }
}

void osd_seof_task(void *_)
{
	while (1) {
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
		if (dev_osd->fcount > 0) {
			switch(dev_osd->status)
			{
			case VBLANK:
				osd_eof_handler();
				break;
			case VVALID:
				osd_sof_handler();
				break;
			default:
				BL_LOGE("[OSD] cannot defect status\r\n");
				break;
			}
		}
		ai_detect_proc();
	}
}

int bl_osd_dev_init(void)
{
	int ret = 0;

	dev_osd = (struct bl_device_osd *)pvPortMalloc(sizeof(struct bl_device_osd));
	if (NULL == dev_osd) {
		BL_LOGE("[OSD] malloc fail\r\n");
		return -NORESC;
	}
	memset(dev_osd, 0, sizeof(struct bl_device_osd));

	dev_osd->status = -1;
	dev_osd->fcount = -1;

	xTaskCreate(osd_seof_task, "osd_seof", 1024, NULL, mainSTART_AP_TASK_PRIORITY + 4, &osd_seof);
	return ret;
}

static int bl_osd_dynamic_text_init(struct dynamic_text *dtext, struct osd_freetype_font *font)
{
	int ret = 0;
	u32 i, stride;
	struct text_config *text;

	dtext->font = font;
	dtext->index = 0;

	text = dtext->cfg;

	stride = font->width * font->height * text->bpp / BIT2BYTE;
	dtext->font_stride = stride;

	for (i = 0; i < NUM_OF_BUF; i++) {
		dtext->recombine_data[i] = (u8 *)pvPortMalloc(sizeof(u8) * stride * LENGTH_OF_BUF);
		if (NULL == dtext->recombine_data[i]) {
			BL_LOGE("[OSD] malloc fail\r\n");
			return -NORESC;
		}
		memset(dtext->recombine_data[i], 0, sizeof(u8) * stride * LENGTH_OF_BUF);
	}

	ret = bl_osd_user_text(dtext->cfg, dtext->font, dtext->data[dtext->index],
				dtext->recombine_data[dtext->index]);
	return ret;
}

void bl_osd_set_ai_detect_names(char **ai_detect_names)
{
     names = ai_detect_names;
}

void bl_osd_ai_draw_init(struct text_config **text_ai, struct osd_freetype_font *font, int max_num)
{
    int i;
    AI_xQueue = xQueueCreate(1, sizeof(detect_msg));
    set_bit(BL_OSD_AI, &dev_osd->funcs);
    struct dynamic_text *ai_text;
    for (i = 0; i < max_num; i++) {
        ai_text = (struct dynamic_text *)pvPortMalloc(sizeof(struct dynamic_text));
        if (NULL == ai_text) {
            BL_LOGE("[OSD] ai text malloc fail\r\n");
            return;
        }
        memset(ai_text, 0, sizeof(struct dynamic_text));
        ai_text->cfg = text_ai[i];
        dev_osd->ai_msg[i] = ai_text;
        bl_osd_dynamic_text_init(dev_osd->ai_msg[i], font);
    }
}

void bl_osd_ai_cb_register(ai_draw_cb * cb)
{
	*cb = osd_ai_draw_send;
}

int bl_osd_boottime_init(struct text_config *text, struct osd_freetype_font *font)
{
	int ret = 0;
	struct dynamic_text *boottime;

	if (dev_osd == NULL) {
		BL_LOGE("[OSD] dev_osd is NULL\r\n");
		return -INVALID;
	}

	boottime = (struct dynamic_text *)malloc(sizeof(struct dynamic_text));
	if (NULL == boottime) {
		BL_LOGE("[OSD] malloc fail\r\n");
		return -NORESC;
	}
	memset(boottime, 0, sizeof(struct dynamic_text));

	boottime->cfg = text;
	strcpy(boottime->data[0], " ");

	dev_osd->boottime = boottime;

	ret = bl_osd_dynamic_text_init(boottime, font);
	if (ret < 0)
		BL_LOGE("[OSD] %s fail(%d)\r\n", __func__, ret);
	else
		set_bit(BL_OSD_BOOTTIME, &dev_osd->funcs);

	return ret;
}

int bl_osd_systime_init(struct text_config *text, struct osd_freetype_font *font)
{
	int ret = 0;
	struct dynamic_text *systime;

	if (dev_osd == NULL) {
		BL_LOGE("[OSD] dev_osd is NULL\r\n");
		return -INVALID;
	}

	systime = (struct dynamic_text *)malloc(sizeof(struct dynamic_text));
	if (NULL == systime) {
		BL_LOGE("[OSD] malloc fail\r\n");
		return -NORESC;
	}
	memset(systime, 0, sizeof(struct dynamic_text));

	systime->cfg = text;
	strcpy(systime->data[0], " ");

	dev_osd->systime = systime;

	ret = bl_osd_dynamic_text_init(systime, font);
	if (ret < 0)
		BL_LOGE("[OSD] %s fail(%d)\r\n", __func__, ret);
	else
		set_bit(BL_OSD_SYSTIME, &dev_osd->funcs);

	return ret;
}

int bl_osd_frames_init(struct text_config *text, struct osd_freetype_font *font)
{
	int ret = 0;
	struct dynamic_text *frames;

	if (dev_osd == NULL) {
		BL_LOGE("[OSD] dev_osd is NULL\r\n");
		return -INVALID;
	}

	frames = (struct dynamic_text *)malloc(sizeof(struct dynamic_text));
	if (NULL == frames) {
		BL_LOGE("[OSD] malloc fail\r\n");
		return -NORESC;
	}
	memset(frames, 0, sizeof(struct dynamic_text));

	frames->cfg = text;
	strcpy(frames->data[0], " ");

	dev_osd->frames = frames;

	ret = bl_osd_dynamic_text_init(frames, font);
	if (ret < 0)
		BL_LOGE("[OSD] %s fail(%d)\r\n", __func__, ret);
	else
		set_bit(BL_OSD_FRAMES, &dev_osd->funcs);

	return ret;
}
