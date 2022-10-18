#ifndef __BL_MJDEC_H__
#define __BL_MJDEC_H__

#include <bl808_comm_mm.h>

typedef struct
{
    uint16_t width;
    uint16_t height;
    uint8_t quality;
    uint8_t *input_buf_addr;
    uint8_t *output_buf_addr;
} bl_mjdec_config_t;

typedef struct {
    uint8_t     *frame_start_addr;
    uint32_t    frame_size;
} mjdec_frame_desc_t;


typedef int (*bl_mjdec_frame_cb)(void *usrdata, mjdec_frame_desc_t *frame_desc);

int bl_mjdec_init(void);
int bl_mjdec_set_config(bl_mjdec_config_t *config);
int bl_mjdec_start_decoder(uint8_t *jpeg_buf_addr);
int bl_mjdec_set_callback(bl_mjdec_frame_cb frame_cb, void *usrdata);

void MJDEC_IRQHandler(void);


#endif /* __BL_MJDEC_H__ */

