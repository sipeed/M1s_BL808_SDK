#ifndef BL_HW_OSD_H
#define BL_HW_OSD_H

#include "bl-hw-common.h"

#define LAYERS_OF_EACH_DRAW	16

enum osd_base_name {
	OSD_BASE_A_DRAW_LAYER_L,
	OSD_BASE_A_DRAW_LAYER_H,
	OSD_BASE_B_DRAW_LAYER_L,
	OSD_BASE_DRAW_CNT,

	OSD_BASE_A_BLEND_LAYER0,
	OSD_BASE_A_BLEND_LAYER1,
	OSD_BASE_A_BLEND_LAYER2,
	OSD_BASE_A_BLEND_LAYER3,
	OSD_BASE_B_BLEND_LAYER0,
	OSD_BASE_B_BLEND_LAYER1,
	OSD_BASE_BLEND_CNT,
};

void __iomem *get_osd_base_addr(u32 chn);

void osd_blend_enable_layer(void __iomem *base_addr, u32 enable);
void osd_blend_set_axis(void __iomem *base_addr, u32 x_start, u32 x_end, u32 y_start, u32 y_end);
void osd_blend_set_data(void __iomem *base_addr, u32 data_addr, u32 data_count);
void osd_blend_palette_format_set(void __iomem *base_addr, u32 fmt, u32 alpha,
				u32 order_r_v, u32 order_g_y, u32 order_b_u);
void osd_blend_palette_update(void __iomem *base_addr, u32 index, u32 data_color);
void osd_blend_mem_req_line(void __iomem *base_addr, u32 number);

void osd_draw_reset(void __iomem *base_addr);
void osd_draw_enable(void __iomem *base_addr, u32 layer, u32 enable);
void osd_draw_type(void __iomem *base_addr, u32 layer, u32 type);
void osd_draw_partial_config(void __iomem *base_addr, u32 layer, u32 yuv, u32 x_start, u32 x_end,
				u32 y_start, u32 y_end);

#endif
