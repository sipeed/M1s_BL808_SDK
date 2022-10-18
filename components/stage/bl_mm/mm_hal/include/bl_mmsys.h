#ifndef __BL_MMSYS_H__
#define __BL_MMSYS_H__

typedef enum {
    BL_MMSYS_BIND_TO_VENC,
    BL_MMSYS_BIND_TO_VENC_DIRECT_LINK,
    BL_MMSYS_BIND_TO_HDMI,
    BL_MMSYS_BIND_TO_NONE,
    BL_MMSYS_BIND_TARGET_NUM,
} BL_MMSYS_BIND_TARGET_T;

typedef struct {
    uint8_t *y_frame_base_addr;
    uint32_t y_frame_size; 
    uint8_t *uv_frame_base_addr;
    uint32_t uv_frame_size;
} bl_mmsys_bind_buffer_t;

int bl_mmsys_create_bind_buffer(int width,
                                    int height, 
                                    BL_MMSYS_BIND_TARGET_T target,
                                    bl_mmsys_bind_buffer_t *buffer);
int bl_mmsys_delete_bind_buffer(        bl_mmsys_bind_buffer_t *buffer, BL_MMSYS_BIND_TARGET_T target);

#endif /* __BL_MMSYS_H__ */
