#ifndef BL_HW_COMMON_H
#define BL_HW_COMMON_H

#include "bl-linux-tmp.h"

enum regdata_type {
	RO = 0,
	RW,
	W1P,
};

struct bl_reg {
	u32	reg_offset;
	char	*reg_name;
};

struct bl_field {
	char			*field_name;
	u32			bit_start;
	u32			bit_width;
	enum regdata_type	type;
	u32			default_value;
};

u32 bl_hw_set_field_value(u32 reg_value, const struct bl_field *field, u32 val);
u32 bl_hw_get_field_value(u32 reg_value, const struct bl_field *field);
void bl_hw_set_reg(void __iomem *base_addr, const struct bl_reg *reg, u32 val);
u32 bl_hw_get_reg(void __iomem *base_addr, const struct bl_reg *reg);
void bl_hw_set_field(void __iomem *base_addr, const struct bl_reg *reg,
			const struct bl_field *field, u32 val);
u32 bl_hw_get_field(void __iomem *base_addr, const struct bl_reg *reg,
			const struct bl_field *field);
// TODO
// void bl_hw_dump_reg(void __iomem *base_addr, const struct bl_reg *reg, u32 total_cnt);

#endif
