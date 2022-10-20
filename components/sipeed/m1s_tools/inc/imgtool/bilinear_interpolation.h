#pragma once
#include <stdint.h>

static void BilinearInterpolation_RGB565(uint16_t *source, uint16_t sw, uint16_t sh, uint16_t *target, uint16_t tw,
                                         uint16_t th)
{
    typedef struct {
        uint16_t b : 5;
        uint16_t g : 6;
        uint16_t r : 5;
    } rgb565_t;
    for (uint32_t hnum = 0; hnum < th; hnum++) {
        for (uint32_t wnum = 0; wnum < tw; wnum++) {
            float d_original_img_hnum = (hnum)*sh / (float)th;
            float d_original_img_wnum = (wnum)*sw / (float)tw;
            int i_original_img_hnum = d_original_img_hnum;
            int i_original_img_wnum = d_original_img_wnum;
            float distance_to_a_x = d_original_img_wnum - i_original_img_wnum;
            //在原图像中与a点的水平距离
            float distance_to_a_y = d_original_img_hnum - i_original_img_hnum;
            //在原图像中与a点的垂直距离
            int original_point_a = i_original_img_hnum * sw + i_original_img_wnum * 1;
            //数组位置偏移量，对应于图像的各像素点RGB的起点,相当于点A
            int original_point_b = i_original_img_hnum * sw + (i_original_img_wnum + 1) * 1;
            //数组位置偏移量，对应于图像的各像素点RGB的起点,相当于点B
            int original_point_c = (i_original_img_hnum + 1) * sw + i_original_img_wnum * 1;
            //数组位置偏移量，对应于图像的各像素点RGB的起点,相当于点C
            int original_point_d = (i_original_img_hnum + 1) * sw + (i_original_img_wnum + 1) * 1;
            //数组位置偏移量，对应于图像的各像素点RGB的起点,相当于点D
            if (i_original_img_hnum + 1 == th - 1) {
                original_point_c = original_point_a;
                original_point_d = original_point_b;
            }
            if (i_original_img_wnum + 1 == tw - 1) {
                original_point_b = original_point_a;
                original_point_d = original_point_c;
            }

            // hnum * write_width + wnum;  //映射尺度变换图像数组位置偏移量

            ((rgb565_t *)target + hnum * tw + wnum)->b =
                ((rgb565_t *)source + original_point_a)->b * (1 - distance_to_a_x) * (1 - distance_to_a_y) +
                ((rgb565_t *)source + original_point_b)->b * distance_to_a_x * (1 - distance_to_a_y) +
                ((rgb565_t *)source + original_point_c)->b * distance_to_a_y * (1 - distance_to_a_x) +
                ((rgb565_t *)source + original_point_d)->b * distance_to_a_y * distance_to_a_x;
            ((rgb565_t *)target + hnum * tw + wnum)->g =
                ((rgb565_t *)source + original_point_a)->g * (1 - distance_to_a_x) * (1 - distance_to_a_y) +
                ((rgb565_t *)source + original_point_b)->g * distance_to_a_x * (1 - distance_to_a_y) +
                ((rgb565_t *)source + original_point_c)->g * distance_to_a_y * (1 - distance_to_a_x) +
                ((rgb565_t *)source + original_point_d)->g * distance_to_a_y * distance_to_a_x;
            ((rgb565_t *)target + hnum * tw + wnum)->r =
                ((rgb565_t *)source + original_point_a)->r * (1 - distance_to_a_x) * (1 - distance_to_a_y) +
                ((rgb565_t *)source + original_point_b)->r * distance_to_a_x * (1 - distance_to_a_y) +
                ((rgb565_t *)source + original_point_c)->r * distance_to_a_y * (1 - distance_to_a_x) +
                ((rgb565_t *)source + original_point_d)->r * distance_to_a_y * distance_to_a_x;
        }
    }
}

static void BilinearInterpolation_RGBA8888(uint32_t *source, uint16_t sw, uint16_t sh, uint32_t *target, uint16_t tw,
                                           uint16_t th)
{
    typedef struct {
        uint32_t r : 8;
        uint32_t g : 8;
        uint32_t b : 8;
        uint32_t a : 8;
    } rgba8888_t;
    for (uint32_t hnum = 0; hnum < th; hnum++) {
        for (uint32_t wnum = 0; wnum < tw; wnum++) {
            float d_original_img_hnum = (hnum)*sh / (float)th;
            float d_original_img_wnum = (wnum)*sw / (float)tw;
            int i_original_img_hnum = d_original_img_hnum;
            int i_original_img_wnum = d_original_img_wnum;
            float distance_to_a_x = d_original_img_wnum - i_original_img_wnum;
            //在原图像中与a点的水平距离
            float distance_to_a_y = d_original_img_hnum - i_original_img_hnum;
            //在原图像中与a点的垂直距离
            int original_point_a = i_original_img_hnum * sw + i_original_img_wnum * 1;
            //数组位置偏移量，对应于图像的各像素点RGB的起点,相当于点A
            int original_point_b = i_original_img_hnum * sw + (i_original_img_wnum + 1) * 1;
            //数组位置偏移量，对应于图像的各像素点RGB的起点,相当于点B
            int original_point_c = (i_original_img_hnum + 1) * sw + i_original_img_wnum * 1;
            //数组位置偏移量，对应于图像的各像素点RGB的起点,相当于点C
            int original_point_d = (i_original_img_hnum + 1) * sw + (i_original_img_wnum + 1) * 1;
            //数组位置偏移量，对应于图像的各像素点RGB的起点,相当于点D
            if (i_original_img_hnum + 1 == th - 1) {
                original_point_c = original_point_a;
                original_point_d = original_point_b;
            }
            if (i_original_img_wnum + 1 == tw - 1) {
                original_point_b = original_point_a;
                original_point_d = original_point_c;
            }

            // hnum * write_width + wnum;  //映射尺度变换图像数组位置偏移量

            ((rgba8888_t *)target + hnum * tw + wnum)->a =
                ((rgba8888_t *)source + original_point_a)->a * (1 - distance_to_a_x) * (1 - distance_to_a_y) +
                ((rgba8888_t *)source + original_point_b)->a * distance_to_a_x * (1 - distance_to_a_y) +
                ((rgba8888_t *)source + original_point_c)->a * distance_to_a_y * (1 - distance_to_a_x) +
                ((rgba8888_t *)source + original_point_d)->a * distance_to_a_y * distance_to_a_x;
            ((rgba8888_t *)target + hnum * tw + wnum)->b =
                ((rgba8888_t *)source + original_point_a)->b * (1 - distance_to_a_x) * (1 - distance_to_a_y) +
                ((rgba8888_t *)source + original_point_b)->b * distance_to_a_x * (1 - distance_to_a_y) +
                ((rgba8888_t *)source + original_point_c)->b * distance_to_a_y * (1 - distance_to_a_x) +
                ((rgba8888_t *)source + original_point_d)->b * distance_to_a_y * distance_to_a_x;
            ((rgba8888_t *)target + hnum * tw + wnum)->g =
                ((rgba8888_t *)source + original_point_a)->g * (1 - distance_to_a_x) * (1 - distance_to_a_y) +
                ((rgba8888_t *)source + original_point_b)->g * distance_to_a_x * (1 - distance_to_a_y) +
                ((rgba8888_t *)source + original_point_c)->g * distance_to_a_y * (1 - distance_to_a_x) +
                ((rgba8888_t *)source + original_point_d)->g * distance_to_a_y * distance_to_a_x;
            ((rgba8888_t *)target + hnum * tw + wnum)->r =
                ((rgba8888_t *)source + original_point_a)->r * (1 - distance_to_a_x) * (1 - distance_to_a_y) +
                ((rgba8888_t *)source + original_point_b)->r * distance_to_a_x * (1 - distance_to_a_y) +
                ((rgba8888_t *)source + original_point_c)->r * distance_to_a_y * (1 - distance_to_a_x) +
                ((rgba8888_t *)source + original_point_d)->r * distance_to_a_y * distance_to_a_x;
        }
    }
}

static void BilinearInterpolation_RGBA88882RGB565(uint32_t *source, uint16_t sw, uint16_t sh, uint16_t *target, uint16_t tw,
                                           uint16_t th)
{
    typedef struct {
        uint32_t r : 8;
        uint32_t g : 8;
        uint32_t b : 8;
        uint32_t a : 8;
    } rgba8888_t;
    typedef struct {
        uint16_t b : 5;
        uint16_t g : 6;
        uint16_t r : 5;
    } rgb565_t;
    for (uint32_t hnum = 0; hnum < th; hnum++) {
        for (uint32_t wnum = 0; wnum < tw; wnum++) {
            float d_original_img_hnum = (hnum)*sh / (float)th;
            float d_original_img_wnum = (wnum)*sw / (float)tw;
            int i_original_img_hnum = d_original_img_hnum;
            int i_original_img_wnum = d_original_img_wnum;
            float distance_to_a_x = d_original_img_wnum - i_original_img_wnum;
            //在原图像中与a点的水平距离
            float distance_to_a_y = d_original_img_hnum - i_original_img_hnum;
            //在原图像中与a点的垂直距离
            int original_point_a = i_original_img_hnum * sw + i_original_img_wnum * 1;
            //数组位置偏移量，对应于图像的各像素点RGB的起点,相当于点A
            int original_point_b = i_original_img_hnum * sw + (i_original_img_wnum + 1) * 1;
            //数组位置偏移量，对应于图像的各像素点RGB的起点,相当于点B
            int original_point_c = (i_original_img_hnum + 1) * sw + i_original_img_wnum * 1;
            //数组位置偏移量，对应于图像的各像素点RGB的起点,相当于点C
            int original_point_d = (i_original_img_hnum + 1) * sw + (i_original_img_wnum + 1) * 1;
            //数组位置偏移量，对应于图像的各像素点RGB的起点,相当于点D
            if (i_original_img_hnum + 1 == th - 1) {
                original_point_c = original_point_a;
                original_point_d = original_point_b;
            }
            if (i_original_img_wnum + 1 == tw - 1) {
                original_point_b = original_point_a;
                original_point_d = original_point_c;
            }

            // hnum * write_width + wnum;  //映射尺度变换图像数组位置偏移量

            ((rgb565_t *)target + hnum * tw + wnum)->b = (uint8_t)(
                ((rgba8888_t *)source + original_point_a)->b * (1 - distance_to_a_x) * (1 - distance_to_a_y) +
                ((rgba8888_t *)source + original_point_b)->b * distance_to_a_x * (1 - distance_to_a_y) +
                ((rgba8888_t *)source + original_point_c)->b * distance_to_a_y * (1 - distance_to_a_x) +
                ((rgba8888_t *)source + original_point_d)->b * distance_to_a_y * distance_to_a_x)>> 3;
            ((rgb565_t *)target + hnum * tw + wnum)->g = (uint8_t)(
                ((rgba8888_t *)source + original_point_a)->g * (1 - distance_to_a_x) * (1 - distance_to_a_y) +
                ((rgba8888_t *)source + original_point_b)->g * distance_to_a_x * (1 - distance_to_a_y) +
                ((rgba8888_t *)source + original_point_c)->g * distance_to_a_y * (1 - distance_to_a_x) +
                ((rgba8888_t *)source + original_point_d)->g * distance_to_a_y * distance_to_a_x)>> 2;
            ((rgb565_t *)target + hnum * tw + wnum)->r = (uint8_t)(
                ((rgba8888_t *)source + original_point_a)->r * (1 - distance_to_a_x) * (1 - distance_to_a_y) +
                ((rgba8888_t *)source + original_point_b)->r * distance_to_a_x * (1 - distance_to_a_y) +
                ((rgba8888_t *)source + original_point_c)->r * distance_to_a_y * (1 - distance_to_a_x) +
                ((rgba8888_t *)source + original_point_d)->r * distance_to_a_y * distance_to_a_x)>> 3;
        }
    }
}