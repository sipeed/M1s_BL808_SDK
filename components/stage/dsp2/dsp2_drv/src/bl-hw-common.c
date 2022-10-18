#include "bl-hw-common.h"

u32 bl_hw_set_field_value(u32 reg_value, const struct bl_field *field, u32 val)
{
	u32 field_mask = 0;

	field_mask = (field->bit_width >=32) ? 0xFFFFFFFF : ((1 << field->bit_width) - 1);

	reg_value &= ~(field_mask << field->bit_start);

	reg_value |= ((val & field_mask) << field->bit_start);

	return reg_value;
}

u32 bl_hw_get_field_value(u32 reg_value, const struct bl_field *field)
{
	u32 field_value, field_mask = 0;

	field_mask = (field->bit_width >= 32) ? 0xFFFFFFFF : ((1 << field->bit_width) - 1);

	field_value = ((reg_value >> field->bit_start) & field_mask);

	return field_value;
}

void bl_hw_set_reg(void __iomem *base_addr, const struct bl_reg *reg, u32 val)
{
	writel(val, base_addr + reg->reg_offset);
}

u32 bl_hw_get_reg(void __iomem *base_addr, const struct bl_reg *reg)
{
	u32 reg_value;

	reg_value = readl(base_addr + reg->reg_offset);

	return reg_value;
}

void bl_hw_set_field(void __iomem *base_addr, const struct bl_reg *reg,
	const struct bl_field *field, u32 val)
{
	u32 reg_value;

	reg_value = readl(base_addr + reg->reg_offset); 

	reg_value = bl_hw_set_field_value(reg_value, field, val);

	writel(reg_value, base_addr + reg->reg_offset);
}

u32 bl_hw_get_field(void __iomem *base_addr, const struct bl_reg *reg,
	const struct bl_field *field)
{
	u32 reg_value, field_value;

	reg_value = readl(base_addr + reg->reg_offset);

	field_value = bl_hw_get_field_value(reg_value, field);

	return field_value;
}

/*
void bl_hw_dump_reg(void __iomem *base_addr, const struct bl_reg *reg, u32 total_cnt)
{
	u32 i, reg_value;

	for (i = 0; i < total_cnt; i++) {
		reg_value = readl(base_addr + reg[i].reg_offset);
		printf("[DUMP] reg_offset: 0x%04X, reg_value: 0x%08x\n",
			reg[i].reg_offset, reg_value);
	}
}
*/
