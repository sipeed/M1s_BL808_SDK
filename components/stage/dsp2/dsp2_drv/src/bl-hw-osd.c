#include "bl808.h"
#include "bl808_common.h"
#include "bl-hw-osd-reg.h"
#include "bl-hw-osd.h"

/*
 * OSD_A: support 4 blend, 2 draw * 16 layers
 * OSD_B: support 2 blend, 1 draw * 16 layers
 */
#define OSD_A_BLEND_LAYER0	(OSD_A_BASE + OSD_BLEND0_OFFSET)
#define OSD_A_BLEND_LAYER1	(OSD_A_BASE + OSD_BLEND1_OFFSET)
#define OSD_A_BLEND_LAYER2	(OSD_A_BASE + OSD_BLEND2_OFFSET)
#define OSD_A_BLEND_LAYER3	(OSD_A_BASE + OSD_BLEND3_OFFSET)
#define OSD_A_DRAW_LAYER_L	(OSD_A_BASE + OSD_DRAW_LOW_OFFSET)
#define OSD_A_DRAW_LAYER_H	(OSD_A_BASE + OSD_DRAW_HIGH_OFFSET)
#define OSD_B_BLEND_LAYER0	(OSD_B_BASE + OSD_BLEND0_OFFSET)
#define OSD_B_BLEND_LAYER1	(OSD_B_BASE + OSD_BLEND1_OFFSET)
#define OSD_B_DRAW_LAYER_L	(OSD_B_BASE + OSD_DRAW_LOW_OFFSET)

/*
 * Common
 */
void __iomem *get_osd_base_addr(u32 chn)
{
	void __iomem *base_addr;
	switch(chn)
	{
	case OSD_BASE_A_BLEND_LAYER0:
		base_addr = (void __iomem *)OSD_A_BLEND_LAYER0;
		break;
	case OSD_BASE_A_BLEND_LAYER1:
		base_addr = (void __iomem *)OSD_A_BLEND_LAYER1;
		break;
	case OSD_BASE_A_BLEND_LAYER2:
		base_addr = (void __iomem *)OSD_A_BLEND_LAYER2;
		break;
	case OSD_BASE_A_BLEND_LAYER3:
		base_addr = (void __iomem *)OSD_A_BLEND_LAYER3;
		break;
	case OSD_BASE_A_DRAW_LAYER_L:
		base_addr = (void __iomem *)OSD_A_DRAW_LAYER_L;
		break;
	case OSD_BASE_A_DRAW_LAYER_H:
		base_addr = (void __iomem *)OSD_A_DRAW_LAYER_H;
		break;
	case OSD_BASE_B_BLEND_LAYER0:
		base_addr = (void __iomem *)OSD_B_BLEND_LAYER0;
		break;
	case OSD_BASE_B_BLEND_LAYER1:
		base_addr = (void __iomem *)OSD_B_BLEND_LAYER1;
		break;
	case OSD_BASE_B_DRAW_LAYER_L:
		base_addr = (void __iomem *)OSD_B_DRAW_LAYER_L;
		break;
	default:
		base_addr = NULL;
		break;
	}
	return base_addr;
}


/*
 * OSD BLEND
 */
void osd_blend_enable_layer(void __iomem *base_addr, u32 enable)
{
	bl_hw_set_field(base_addr, &osd_blend_regs[OBND_R_MEM_CONFIG0],
				&osd_blend_fields[OBND_F_LAYER_EN], enable);
}

void osd_blend_set_axis(void __iomem *base_addr, u32 x_start, u32 x_end, u32 y_start, u32 y_end)
{
	bl_hw_set_field(base_addr, &osd_blend_regs[OBND_R_LAYER_XCONFIG],
				&osd_blend_fields[OBND_F_XMIN], x_start);
	bl_hw_set_field(base_addr, &osd_blend_regs[OBND_R_LAYER_XCONFIG],
				&osd_blend_fields[OBND_F_XMAX], x_end);
	bl_hw_set_field(base_addr, &osd_blend_regs[OBND_R_LAYER_YCONFIG],
				&osd_blend_fields[OBND_F_YMIN], y_start);
	bl_hw_set_field(base_addr, &osd_blend_regs[OBND_R_LAYER_YCONFIG],
				&osd_blend_fields[OBND_F_YMAX], y_end);
}

void osd_blend_set_data(void __iomem *base_addr, u32 data_addr, u32 data_count)
{
	bl_hw_set_reg(base_addr, &osd_blend_regs[OBND_R_MEM_CONFIG1], data_addr);
	bl_hw_set_reg(base_addr, &osd_blend_regs[OBND_R_MEM_CONFIG2], data_count);
}

void osd_blend_palette_format_set(void __iomem *base_addr, u32 fmt, u32 alpha,
				u32 order_r_v, u32 order_g_y, u32 order_b_u)
{
	bl_hw_set_field(base_addr, &osd_blend_regs[OBND_R_LAYER_CONFIG0],
				&osd_blend_fields[OBND_F_COLOR_FORMAT], fmt);
	bl_hw_set_field(base_addr, &osd_blend_regs[OBND_R_LAYER_CONFIG0],
				&osd_blend_fields[OBND_F_ORDER_A], alpha);
	bl_hw_set_field(base_addr, &osd_blend_regs[OBND_R_LAYER_CONFIG0],
				&osd_blend_fields[OBND_F_ORDER_RV], order_r_v);
	bl_hw_set_field(base_addr, &osd_blend_regs[OBND_R_LAYER_CONFIG0],
				&osd_blend_fields[OBND_F_ORDER_GY], order_g_y);
	bl_hw_set_field(base_addr, &osd_blend_regs[OBND_R_LAYER_CONFIG0],
				&osd_blend_fields[OBND_F_ORDER_BU], order_b_u);

}

void osd_blend_palette_update(void __iomem *base_addr, u32 index, u32 data_color)
{
	bl_hw_set_reg(base_addr, &osd_blend_regs[OBND_R_LAYER_CONFIG7], data_color);
	bl_hw_set_field(base_addr, &osd_blend_regs[OBND_R_LAYER_CONFIG6],
				&osd_blend_fields[OBND_F_UPDATE_INDEX], index);
	bl_hw_set_field(base_addr, &osd_blend_regs[OBND_R_LAYER_CONFIG6],
				&osd_blend_fields[OBND_F_UPDATE_TRIGGER], ENABLE);
}

void osd_blend_mem_req_line(void __iomem *base_addr, u32 number)
{
	bl_hw_set_reg(base_addr, &osd_blend_regs[OBND_R_SH], number);
}

/*
 * OSD DRAW
 */
void osd_draw_reset(void __iomem *base_addr)
{
	bl_hw_set_reg(base_addr, &osd_draw_regs[DRAW_R_PARTIAL_CONFIG], DISABLE);
}

void osd_draw_enable(void __iomem *base_addr, u32 layer, u32 enable)
{
	u32 field_en;

	field_en = bl_hw_get_field(base_addr, &osd_draw_regs[DRAW_R_PARTIAL_CONFIG],
					&osd_draw_fields[REG_DRAW_F_EN]);
	if (enable)
		field_en |= (ENABLE << layer);
	else
		field_en &= ~(ENABLE << layer);

	bl_hw_set_field(base_addr, &osd_draw_regs[DRAW_R_PARTIAL_CONFIG],
				&osd_draw_fields[REG_DRAW_F_EN], field_en);
}

void osd_draw_type(void __iomem *base_addr, u32 layer, u32 type)
{
	u32 field_type;

	field_type = bl_hw_get_field(base_addr, &osd_draw_regs[DRAW_R_PARTIAL_CONFIG],
					&osd_draw_fields[REG_DRAW_F_TYPE]);
	if (type) 
		field_type |= (ENABLE << layer);
	else
		field_type &= ~(ENABLE << layer);

	bl_hw_set_field(base_addr, &osd_draw_regs[DRAW_R_PARTIAL_CONFIG],
				&osd_draw_fields[REG_DRAW_F_TYPE], field_type);
}

void osd_draw_partial_config(void __iomem *base_addr, u32 layer, u32 yuv, u32 x_start, u32 x_end,
				u32 y_start, u32 y_end)
{
	bl_hw_set_reg(base_addr, &osd_draw_regs[DRAW_R_PARTIAL_YUV_CONFIG0 + layer * 3], yuv);

	bl_hw_set_field(base_addr, &osd_draw_regs[DRAW_R_PARTIAL_X_CONFIG0 + layer * 3],
				&osd_draw_fields[REG_DRAW_F_X_MIN], x_start);

	bl_hw_set_field(base_addr, &osd_draw_regs[DRAW_R_PARTIAL_X_CONFIG0 + layer * 3],
				&osd_draw_fields[REG_DRAW_F_X_MAX], x_end);

	bl_hw_set_field(base_addr, &osd_draw_regs[DRAW_R_PARTIAL_Y_CONFIG0 + layer * 3],
				&osd_draw_fields[REG_DRAW_F_Y_MIN], y_start);

	bl_hw_set_field(base_addr, &osd_draw_regs[DRAW_R_PARTIAL_Y_CONFIG0 + layer * 3],
				&osd_draw_fields[REG_DRAW_F_Y_MAX], y_end);
}
