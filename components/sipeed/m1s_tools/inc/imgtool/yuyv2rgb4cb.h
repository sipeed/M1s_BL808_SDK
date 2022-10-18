#pragma once

#include <stdint.h>
// #include <stdio.h>

static void yuyv2rgb4cb(const uint8_t* const src_yuyv, uint16_t src_w,
                        uint16_t src_h, uint16_t dst_w, uint16_t dst_h,
                        void (*cb)(uint16_t x, uint16_t y, uint8_t r, uint8_t g,
                                   uint8_t b)) {
#define CLAMP(x) (((x) < 0) ? 0 : ((x) > 255) ? 255 : (x))

  if (dst_w > src_w || dst_h > src_h) return;
  // printf("input: %ux%u, output: %ux%u\r\n", src_w, src_h, dst_w, dst_h);

  const uint8_t step_x = src_w / dst_w;
  const uint8_t step_y = src_h / dst_h;
  // printf("step: x(%u),y(%u)\r\n", step_x, step_y);

  int16_t b, g, r;
  for (uint32_t h = 0; h < dst_h; h++) {
    for (uint32_t w = 0, yuyv_offset = 0; w < dst_w; w++) {
      yuyv_offset = (h * step_y * src_w + w * step_x) >> 1 << 2;

      uint8_t y1 = src_yuyv[yuyv_offset];
      uint8_t u1 = src_yuyv[yuyv_offset + 1];
      uint8_t y2 = src_yuyv[yuyv_offset + 2 + (step_x << 1)];
      uint8_t v1 = src_yuyv[yuyv_offset + 3 + (step_x << 1)];

      b = (int16_t)y1 + ((7289 * u1) >> 12) - 228;
      g = (int16_t)y1 - ((1415 * u1) >> 12) - ((2936 * v1) >> 12) + 136;
      r = (int16_t)y1 + ((5765 * v1) >> 12) - 180;
      b = 0xff & CLAMP(b);
      g = 0xff & CLAMP(g);
      r = 0xff & CLAMP(r);
      cb(w, h, r, g, b);

      w++;
      b = (int16_t)y2 + ((7289 * u1) >> 12) - 228;
      g = (int16_t)y2 - ((1415 * u1) >> 12) - ((2936 * v1) >> 12) + 136;
      r = (int16_t)y2 + ((5765 * v1) >> 12) - 180;
      b = 0xff & CLAMP(b);
      g = 0xff & CLAMP(g);
      r = 0xff & CLAMP(r);
      cb(w, h, r, g, b);
    }
  }

#undef CLAMP
}