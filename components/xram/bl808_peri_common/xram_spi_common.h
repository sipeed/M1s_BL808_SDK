/**
 * xram_spi_common.h
 * Copyright (c) 2022 bliu <bliu@bouffalolab.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _XRAM_SPI_COMMON_H_
#define _XRAM_SPI_COMMON_H_

#define SPI_OPERATION_MAX_SIZE (2048)

typedef enum spi_op_err {
    SPI_OP_OK,
    SPI_OP_ERR
} SPI_OP_ERR_TYPE;

enum spi_operation {
    XRAM_SPI_INIT,
    XRAM_SPI_FINALIZE,
    XRAM_SPI_TRANS
};

struct xram_spi_op {
    uint32_t op;
    uint8_t port;               /**< spi port */
    uint8_t mode;           /**< spi communication mode */
    uint8_t dma_enable;     /**< enable dma tansmission or not */
    uint8_t polar_phase;    /**< spi polar and phase */
    uint32_t freq;          /**< communication frequency Hz */
    uint8_t pin_clk;        /**< spi clk pin */
    uint8_t pin_mosi;       /**< spi mosi pin */
    uint8_t pin_miso;       /**< spi miso pin */
    uint8_t pin_cs;       /**< spi cs pin */
    uint32_t timeout;
    uint32_t len;
    uint8_t data[];
};

#endif
