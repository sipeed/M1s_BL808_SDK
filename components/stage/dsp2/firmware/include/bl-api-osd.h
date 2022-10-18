#ifndef BL_API_OSD_H
#define BL_API_OSD_H

#include <bl-hw-osd.h>
#include <fttypes.h>

#define ENABLE_REMOVE_WHITE_PALETTE

// YUV Color
#define YUV2ATTR(y, u, v)		((y << 24) | (u << 16) | (v << 8))
#define OSD_YUV_BLACK			YUV2ATTR(0, 128, 128)
#define OSD_YUV_WHITE			YUV2ATTR(255, 128, 128)
#define OSD_YUV_SILVER			YUV2ATTR(192, 128, 128)
#define OSD_YUV_GRAY			YUV2ATTR(127, 128, 128)
#define OSD_YUV_DIMGRAY			YUV2ATTR(105, 128, 128)
#define OSD_YUV_RED			YUV2ATTR(76, 84, 255)
#define OSD_YUV_GREEN			YUV2ATTR(149, 43, 21)
#define OSD_YUV_BLUE			YUV2ATTR(29, 255, 107)
#define OSD_YUV_SKYBLUE			YUV2ATTR(188, 154, 90)
#define OSD_YUV_INDIGO			YUV2ATTR(37, 180, 154)
#define OSD_YUV_NAVY			YUV2ATTR(14, 192, 117)
#define OSD_YUV_MAGENTA			YUV2ATTR(105, 212, 234)
#define OSD_YUV_PURPLE			YUV2ATTR(52, 170, 181)
#define OSD_YUV_CYAN			YUV2ATTR(178, 171, 0)
#define OSD_YUV_TEAL			YUV2ATTR(89, 149, 64)
#define OSD_YUV_PINK			YUV2ATTR(212, 122, 158)
#define OSD_YUV_DEEPPINK		YUV2ATTR(104, 151, 235)
#define OSD_YUV_YELLOW			YUV2ATTR(255, 0, 148)
#define OSD_YUV_GREENYELLOW		YUV2ATTR(206, 37, 103)
#define OSD_YUV_GOLD			YUV2ATTR(202, 13, 165)
#define OSD_YUV_CHOCOLATE		YUV2ATTR(127, 72, 186)
#define OSD_YUV_ORANGE			YUV2ATTR(173, 30, 186)

// RAW Color
#define RGBA2ATTR(r, g, b)		((r << 24) | (g << 16) | (b << 8))
#define OSD_RGB_WHITE			RGBA2ATTR(255, 255, 255)
#define OSD_RGB_BLACK			RGBA2ATTR(0, 0, 0)
#define OSD_RGB_RED			RGBA2ATTR(255, 0, 0)
#define OSD_RGB_GREEN			RGBA2ATTR(0, 255, 0)
#define OSD_RGB_BLUE			RGBA2ATTR(0, 0, 255)

enum osd_text_color_order {
	OSD_TEXT_COLOR_ORDER0 = 0,
	OSD_TEXT_COLOR_ORDER1,
	OSD_TEXT_COLOR_ORDER2,
	OSD_TEXT_COLOR_ORDER3,
	OSD_TEXT_COLOR_ORDER_MAX = 0x7F
};

enum osd_text_color_fmt {
	OSD_TEXT_COLOR_FMT_ARGB8888 = 0,
	OSD_TEXT_COLOR_FMT_AYUV8888,
	OSD_TEXT_COLOR_FMT_ARGB4444,
	OSD_TEXT_COLOR_FMT_AYUV4444,
	OSD_TEXT_COLOR_FMT_ARGB1555,
	OSD_TEXT_COLOR_FMT_AYUV1555,
	OSD_TEXT_COLOR_FMT_RGB565,
	OSD_TEXT_COLOR_FMT_YUV655,
	OSD_TEXT_COLOR_FMT_A8RGB,
	OSD_TEXT_COLOR_FMT_A8YUV,
	OSD_TEXT_COLOR_FMT_BPP8ARGB = 0x10,
	OSD_TEXT_COLOR_FMT_BPP8AYUV,
	OSD_TEXT_COLOR_FMT_BPP4ARGB,
	OSD_TEXT_COLOR_FMT_BPP4AYUV,
	OSD_TEXT_COLOR_FMT_BPP2ARGB,
	OSD_TEXT_COLOR_FMT_BPP2AYUV,
	OSD_TEXT_COLOR_FMT_BPP1ARGB,
	OSD_TEXT_COLOR_FMT_BPP1AYUV,
	OSD_TEXT_COLOR_FMT_CNT,
	OSD_TEXT_COLOR_FMT_MAX = 0x7F
};

struct osd_time {
	u32	t;
	char	*name;
};

enum draw_type {
	TYPE_HOLLOW = 0,
	TYPE_SOLID,
	TYPE_MAX
};

struct axis_pos {
	u32 start; /* must be EVEN */
	u32 end; /* must be ODD */
};

enum bpp2byte{
	BPP1 = 1,
	BPP8 = 8,
};

struct osd_freetype_font {
	uint32_t width;
	uint32_t height;
	uint32_t horz_resolution; /* The horizontal resolution in dpi. */
	uint32_t vert_resolution; /* The vertical resolution in dpi. */
	FT_Vector pen;
	FT_Matrix matrix;         /* set up matrix */
};

struct draw_config {
	u32 chn;
	u32 layer;

	u32 type;
	u32 color;
	struct axis_pos x;
	struct axis_pos y;
	u8 thickness;
};

struct text_config {
	u32 chn;

	u32 color_fmt;
	u32 bpp;
	u32 bg_color;
	u32 fg_color;
	struct axis_pos x;
	struct axis_pos y;
	u8 bg_alpha;
	u8 fg_alpha;
};

#define NUM_OF_BUF	2
#define LENGTH_OF_BUF   25
struct dynamic_text {
	struct text_config *cfg;
	struct osd_freetype_font *font;
	u32 index;
	u32 use_len;
	u32 font_stride;
	char data[NUM_OF_BUF][LENGTH_OF_BUF];
	u8 *recombine_data[NUM_OF_BUF];
};

enum bl_osd_funcs {
	BL_OSD_BOOTTIME,
	BL_OSD_SYSTIME,
	BL_OSD_FRAMES,
	BL_OSD_AI
};

enum osd_status {
	VBLANK,
	VVALID,
};

struct bl_device_osd {
	struct dynamic_text *systime;
	struct dynamic_text *boottime;
	struct dynamic_text *frames;
	struct dynamic_text *ai_msg[4];
	unsigned long funcs;
	unsigned long chn;
	unsigned long layer[OSD_BASE_DRAW_CNT];
	int status;
	int fcount;
};

typedef void (* ai_draw_cb)(u8 *detect_result);

extern struct bl_device_osd *dev_osd;

int bl_osd_draw(struct draw_config *draw);
void bl_osd_draw_enable(struct draw_config *draw, u32 enable);
void bl_osd_draw_reset(u32 chn);
void bl_osd_blend_reset(u32 chn);
int bl_osd_user_text(struct text_config *text, struct osd_freetype_font *font,
			char *data, u8 *recombine_data);
void bl_osd_ai_cb_register(ai_draw_cb * cb);
int bl_osd_set_logo(struct text_config *text, void *data, u32 bytes,
				u8 (*palette)[]);

int bl_osd_dev_init(void);
int bl_osd_systime_init(struct text_config *text, struct osd_freetype_font *font);
int bl_osd_boottime_init(struct text_config *text, struct osd_freetype_font *font);
int bl_osd_frames_init(struct text_config *text, struct osd_freetype_font *font);
void bl_osd_ai_draw_init(struct text_config **text_ai, struct osd_freetype_font *font, int max_num);
void bl_osd_set_ai_detect_names(char **ai_detect_names);
void osd_seof_wakeup(void);

#endif
