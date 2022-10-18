/**
 * xram_pipe_spi.h
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

#ifndef _XRAM_PIPE_SPI_H_
#define _XRAM_PIPE_SPI_H_

/* xram pipe spi object
 **/
struct xram_pipe_spi {
    uint8_t port;               /**< spi port */
    uint8_t mode;           /**< spi communication mode */
    uint8_t dma_enable;     /**< enable dma tansmission or not */
    uint8_t polar_phase;    /**< spi polar and phase */
    uint32_t freq;          /**< communication frequency Hz */
    uint8_t pin_clk;        /**< spi clk pin */
    uint8_t pin_mosi;       /**< spi mosi pin */
    uint8_t pin_miso;       /**< spi miso pin */
    uint8_t pin_cs;       /**< spi cs pin */
};
typedef struct xram_pipe_spi *xram_pipe_spi_t;

/**
 * @brief init SPI
 *
 * @param[in]  obj  the spi device
 *
 * @return  
 *       - 0 : on success 
 *       - other : error
 */
int xram_pipe_spi_init(xram_pipe_spi_t obj);

/**
 * @brief finalize SPI
 *
 *
 * @param[in]  obj  the SPI device to be de-initialised
 *
 * @return 
 *       - 0 : success 
 *       - other : error
 */
int xram_pipe_spi_finalize(xram_pipe_spi_t obj);

/**
 * @brief spi send data and recv
 *
 * @param[in]  obj      the spi device
 * @param[in]  tx_data  spi send data
 * @param[out] rx_data  spi recv data
 * @param[in]  size     spi data to be sent and recived
 * @param[in]  timeout  timeout in milisecond
 *
 * @return  
 *        - 0 : success 
 *        - other : error
 */
int xram_pipe_spi_send_recv(xram_pipe_spi_t obj, void *tx_data, void *rx_data, uint32_t size, uint32_t timeout);

/**
 * @brief spi send data
 *
 * @param[in]  obj      the spi device
 * @param[in]  data    spi send data
 * @param[in]  size     spi data to be sent and recived
 * @param[in]  timeout  timeout in milisecond
 *
 * @return  
 *        - 0 : success 
 *        - other : error
 */
int xram_pipe_spi_send(xram_pipe_spi_t obj, void *data, uint32_t size, uint32_t timeout);

/**
 * @brief spi recv data
 *
 * @param[in]  obj      the spi device
 * @param[out] data  spi recv data
 * @param[in]  size     spi data to be sent and recived
 * @param[in]  timeout  timeout in milisecond
 *
 * @return  
 *        - 0 : success 
 *        - other : error
 */
int xram_pipe_spi_recv(xram_pipe_spi_t obj, void *data, uint32_t size, uint32_t timeout);

#endif
