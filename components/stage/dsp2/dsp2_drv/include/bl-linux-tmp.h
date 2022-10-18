#ifndef BL_LINUX_TMP_H
#define BL_LINUX_TMP_H

#include <limits.h>

#define __iomem

typedef unsigned char u8;
typedef unsigned int u32;

#define writel(b, addr)	(*(volatile unsigned int *)(addr) = (b))
#define readl(addr)	(*((volatile unsigned int *)(addr)))

#ifndef LONG_BIT
#define LONG_BIT (CHAR_BIT * sizeof(long))
#endif

#undef set_bit
static __inline void set_bit(unsigned int nr, unsigned long *addr)
{
	addr[nr / LONG_BIT] |= (1UL << (nr % LONG_BIT));
}

#undef clear_bit
static __inline void clear_bit(unsigned int nr, unsigned long *addr)
{
	addr[nr / LONG_BIT] &= (~(1UL << (nr % LONG_BIT)));
}

#undef test_bit
static __inline int test_bit(unsigned int nr, unsigned long *addr)
{
	return (int)(addr[nr / LONG_BIT] >> (nr % LONG_BIT)) & 1;
}

#endif
