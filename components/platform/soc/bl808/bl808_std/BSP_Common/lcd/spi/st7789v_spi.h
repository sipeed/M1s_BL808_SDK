#ifndef __ST7789V_SPI_H
#define __ST7789V_SPI_H

#include "stdint.h"

#define ST7789V_SPI_DIR (1)
#if ST7789V_SPI_DIR == 1
#define ST7789V_SPI_W 280
#define ST7789V_SPI_H 240
#else
#define ST7789V_SPI_W 240
#define ST7789V_SPI_H 280
#endif

#define ST7789V_SPI_OFFSET_X 0
#define ST7789V_SPI_OFFSET_Y 20

#define ST7789V_SPI_COLOR_DEPTH 16

int st7789v_spi_init(void);
int st7789v_spi_deinit(void);
int st7789v_spi_clear(uint16_t color);
void st7789v_spi_async_callback_register(void (*callback)(void));
int st7789v_spi_set_area(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
int st7789v_spi_set_dir(uint8_t dir, uint8_t mir_flag);
int st7789v_spi_draw_point(uint16_t x, uint16_t y, uint16_t color);
int st7789v_spi_draw_area(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void st7789v_spi_draw_picture_nonblocking(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t *picture);
void st7789v_spi_draw_picture_blocking(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t *picture);
int st7789v_spi_draw_is_busy(void);

#endif  // __ST7789V_SPI_H