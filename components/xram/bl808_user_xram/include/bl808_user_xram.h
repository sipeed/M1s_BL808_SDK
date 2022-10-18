#ifndef __BL808_USER_XRAM_H_
#define __BL808_USER_XRAM_H_
int bl_xram_user_ring_init();
int bl_xram_user_ring_reset();
int bl_xram_user_ring_write(void *data, size_t len);
int bl_xram_user_ring_read(void *data, size_t len);
#endif
