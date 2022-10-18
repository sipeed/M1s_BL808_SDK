#include <stdio.h>
#include <string.h>
#include <FreeRTOS.h>
#include <bl808_common.h>
#include <bl_dsp2.h>
#include "bl-api-osd.h"
#include "tmall8bpp.h"
#include <bouffalo_logo_8bpp.h>
//#include "tmall_256.h"
#include <math.h>

#define ENABLE_AI_OSD
#define ENABLE_TMALL_LOGO
//#define ENABLE_SYS_TIME
void bl_osd_init()
{
    struct osd_freetype_font *text_font;
    u32 i, j;
    int ret = 0;
    text_font = (struct osd_freetype_font *)pvPortMalloc(sizeof(struct osd_freetype_font));
    if (NULL == text_font) {
    	BL_LOGE("[OSD] pvPortMalloc fail\r\n");
    	return;
    }
    bl_dsp2_osd_path_init();
    memset(text_font, 0, sizeof(struct osd_freetype_font));

    text_font->width = 16;
    text_font->height = 32;
    text_font->horz_resolution = 64;
    text_font->vert_resolution = 64;
    text_font->pen.x = 0 * 64;
    text_font->pen.y = (32 - 24) * 64;
    text_font->matrix.xx = (FT_Fixed)( cos( 0 ) * 0x10000L );
    text_font->matrix.xy = (FT_Fixed)(-sin( 0 ) * 0x10000L );
    text_font->matrix.yx = (FT_Fixed)( sin( 0 ) * 0x10000L );
    text_font->matrix.yy = (FT_Fixed)( cos( 0 ) * 0x10000L );
    
    bl_osd_dev_init();

#ifdef ENABLE_AI_OSD

    struct text_config *ai_text[4];
    for (i = 0; i < 4; i++) {
        ai_text[i] = (struct text_config *)pvPortMalloc(sizeof(struct text_config));
        if (NULL == ai_text[i]) {
        	BL_LOGE("[OSD] ai text malloc fail\r\n");
        	return;
        }
        memset(ai_text[i], 0, sizeof(struct text_config ));
        ai_text[i]->color_fmt = OSD_TEXT_COLOR_FMT_BPP8ARGB;
        ai_text[i]->bpp = BPP8;
        ai_text[i]->bg_color = OSD_RGB_WHITE;
        ai_text[i]->bg_alpha = 0;
        ai_text[i]->fg_color = OSD_RGB_BLACK;
        ai_text[i]->fg_alpha = 0xfe;
        ai_text[i]->x.start = 1;
        ai_text[i]->y.start = 0;
    }
    bl_osd_ai_draw_init(ai_text, text_font, 4);
#endif
#ifdef ENABLE_TMALL_LOGO
    struct text_config *logo_b_layer0 = (struct text_config *)pvPortMalloc(sizeof(struct text_config));
    if (NULL == logo_b_layer0) {
    	BL_LOGE("[OSD] logo malloc fail\r\n");
    	return;
    }
    logo_b_layer0->color_fmt = OSD_TEXT_COLOR_FMT_BPP8ARGB;
    logo_b_layer0->bpp = BPP8;
    logo_b_layer0->bg_alpha = 0;
    logo_b_layer0->fg_alpha = 192;
    logo_b_layer0->x.start = 300;
    logo_b_layer0->x.end =  300 + 238;
    logo_b_layer0->y.start = 2;
    logo_b_layer0->y.end = 2 + 132;
    
    ret = bl_osd_set_logo(logo_b_layer0, logo8bpp_data, 239 * 133,
    			logo8bpp_data_cmap);
    if (ret < 0) {
	    BL_LOGE("[OSD] %s fail(%d)\r\n", __func__, ret);
    }
#endif

#ifdef ENABLE_SYS_TIME
    struct text_config *text_b_layer1 = (struct text_config *)pvPortMalloc(sizeof(struct text_config));
    if (NULL == text_b_layer1) {
        BL_LOGE("[OSD] systime malloc fail\r\n");
    	return;
    }
    
    text_b_layer1->color_fmt = OSD_TEXT_COLOR_FMT_BPP8ARGB;
    text_b_layer1->bpp = BPP8;
    text_b_layer1->bg_color = OSD_RGB_WHITE;
    text_b_layer1->bg_alpha = 0;
    text_b_layer1->fg_color = OSD_RGB_WHITE;
    text_b_layer1->fg_alpha = 0xFE;
    text_b_layer1->x.start = 2;
    text_b_layer1->y.start = 2;
    
    ret = bl_osd_systime_init(text_b_layer1, text_font);
    if (ret < 0) {
        BL_LOGE("[OSD] %s fail(%d)\r\n", __func__, ret);
    }
#endif

#ifdef ENABLE_DRAW_TEST
    struct draw_config draw[48];

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 16; j++) {
            draw[i * 16 + j].type = TYPE_HOLLOW;
            draw[i * 16 + j].color = OSD_YUV_RED;
            draw[i * 16 + j].thickness = 5;
            draw[i * 16 + j].x.start = 50 * j + 20;
            draw[i * 16 + j].x.end = 50 * j + 50;
            draw[i * 16 + j].y.start = 50 * i + 20;
            draw[i * 16 + j].y.end = 50 * i + 50;

            ret = bl_osd_draw(&draw[i * 16 + j]);
            if (ret < 0) {
                BL_LOGE("[OSD] %s fail(%d)\r\n", __func__, ret);
            }
            vTaskDelay(200);
        }
    }

    // disable
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 16; j++) {
            bl_osd_draw_enable(&draw[i * 16 + j], DISABLE);
            vTaskDelay(200);
        }
    }

    // enable
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 16; j++) {
            bl_osd_draw_enable(&draw[i * 16 + j], ENABLE);
            vTaskDelay(200);
        }
    }
#endif
}
