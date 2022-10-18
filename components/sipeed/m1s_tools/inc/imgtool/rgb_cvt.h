#pragma once
#include <stdint.h>

static void RGBA88882RGB565(uint32_t *src, uint16_t *dest, uint16_t w, uint16_t h)
{
    typedef struct {
        uint16_t b : 5;
        uint16_t g : 6;
        uint16_t r : 5;
    } rgb565_t;
    typedef struct {
        uint8_t a;
        uint8_t b;
        uint8_t g;
        uint8_t r;
    } rgba8888_t;

    for (uint16_t i = 0; i < h; i++) {
        for (uint16_t j = 0; j < w; j++) {
            ((rgb565_t *)dest + i * w + j)->b = ((rgba8888_t *)dest + i * w + j)->b >> 3;
            ((rgb565_t *)dest + i * w + j)->g = ((rgba8888_t *)dest + i * w + j)->g >> 2;
            ((rgb565_t *)dest + i * w + j)->r = ((rgba8888_t *)dest + i * w + j)->r >> 3;
        }
    }
}

static void RGB5652RGBA8888(uint32_t *src, uint16_t *dest, uint16_t w, uint16_t h)
{
    typedef struct {
        uint16_t b : 5;
        uint16_t g : 6;
        uint16_t r : 5;
    } rgb565_t;
    typedef struct {
        uint8_t a;
        uint8_t b;
        uint8_t g;
        uint8_t r;
    } rgba8888_t;

    for (uint16_t i = 0; i < h; i++) {
        for (uint16_t j = 0; j < w; j++) {
            ((rgba8888_t *)dest + i * w + j)->a = 0;
            ((rgba8888_t *)dest + i * w + j)->b = (uint8_t)((rgb565_t *)dest + i * w + j)->b << 3;
            ((rgba8888_t *)dest + i * w + j)->g = (uint8_t)((rgb565_t *)dest + i * w + j)->g << 2;
            ((rgba8888_t *)dest + i * w + j)->r = (uint8_t)((rgb565_t *)dest + i * w + j)->r << 3;
        }
    }
}