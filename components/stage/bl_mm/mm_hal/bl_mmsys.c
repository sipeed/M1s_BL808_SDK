#include <bl808_comm_mm.h>
#include "bl_mmsys.h"

/* at least 2 x 16x16 block rows for Y, 32 lines */
/* at least 2 x 8x8 block rows for UV, 16 lines */
#define DIRECT_LINK_BUFFER_HEIGHT   (32)
#define BUFFER_CNT                  (1)
#define DIRECT_LINK_VRAM            (0x3f000000) // direct link only used for single stream. framebuffer in psram is used for dual stream

int bl_mmsys_create_bind_buffer(int width,
                                    int height,
                                    BL_MMSYS_BIND_TARGET_T target,
                                    bl_mmsys_bind_buffer_t *buffer)
{
    int enc_h;
    int y_frame_size;
    int uv_frame_size;

    if (BL_MMSYS_BIND_TO_VENC_DIRECT_LINK == target) {
        enc_h = DIRECT_LINK_BUFFER_HEIGHT;
    } else {
        enc_h = ENC_HEIGHT(height) * BUFFER_CNT;
        BL_LOGI("%s line:%d enc_h:%d buffer_cnt:%d\r\n", __func__, __LINE__, enc_h, BUFFER_CNT);
    }

    y_frame_size = width * enc_h;
    uv_frame_size = y_frame_size >> 1;

    BL_LOGI("Alloc bind buffer\r\n");
    if (BL_MMSYS_BIND_TO_VENC_DIRECT_LINK == target) {
        /*FIXME JPEG LINE BUFFER need VRAM ?*/
        if (NULL == buffer->y_frame_base_addr) {
            buffer->y_frame_base_addr = DIRECT_LINK_VRAM;//BL_MallocDMA(2, y_frame_size);
        }
        if (NULL == buffer->uv_frame_base_addr) {
            buffer->uv_frame_base_addr = DIRECT_LINK_VRAM + y_frame_size;//BL_MallocDMA(2, uv_frame_size);
        }
        BL_LOGI("Bind directlink buffer, Y: 0x%x, UV: 0x%x\r\n",
            (uint32_t)buffer->y_frame_base_addr, (uint32_t)buffer->uv_frame_base_addr);
    } else  {
        if (NULL == buffer->y_frame_base_addr) {
            buffer->y_frame_base_addr = BL_MallocDMA(PSRAM_ID_FOR_DSP2_PORT_BUF, y_frame_size);
        }
        if (NULL == buffer->uv_frame_base_addr) {
            buffer->uv_frame_base_addr = BL_MallocDMA(PSRAM_ID_FOR_DSP2_PORT_BUF, uv_frame_size);
        }
    }

    buffer->y_frame_size = y_frame_size;
    buffer->uv_frame_size = uv_frame_size;

    return 0;
}

int bl_mmsys_delete_bind_buffer(        bl_mmsys_bind_buffer_t *buffer, BL_MMSYS_BIND_TARGET_T target)
{
    if (BL_MMSYS_BIND_TO_VENC_DIRECT_LINK == target) {
        buffer->y_frame_base_addr = NULL;
        buffer->uv_frame_base_addr = NULL;
    } else {
        if (NULL != buffer->y_frame_base_addr) {
            BL_FreeDMA(buffer->y_frame_base_addr);
            buffer->y_frame_base_addr = NULL;
        }
        if (NULL != buffer->uv_frame_base_addr) {
            BL_FreeDMA(buffer->uv_frame_base_addr);
            buffer->uv_frame_base_addr = NULL;
        }
    }

    return 0;
}

