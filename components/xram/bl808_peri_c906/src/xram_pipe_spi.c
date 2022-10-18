/**
 * xram_pipe_spi.c
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

#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <ring.h>
#include <xram_platform.h>
#include <xram_peripheral.h>
#include <xram_pipe_spi.h>
#include <xram_peri_common.h>

static int xram_pipe_spi_operation(xram_pipe_spi_t obj, enum spi_operation operation)
{
    struct xram_hdr tx_hdr;
    struct xram_spi_op spi_op;
    uint32_t bytes;
    int ret = -1;

    assert(obj != NULL);

    if (xram_peri_mutex_lock()) {
        return -1;
    }

    tx_hdr.type = XRAM_PERI_TYPE_SPI;
    tx_hdr.err = SPI_OP_OK;
    tx_hdr.len = sizeof(struct xram_spi_op);
    spi_op.op = operation;
    memcpy((void *)&spi_op.port, obj, sizeof(struct xram_pipe_spi));

    bytes = XRAMRingWrite(XRAM_PERI_OP_QUEUE, &tx_hdr, sizeof(struct xram_hdr));
    bytes += XRAMRingWrite(XRAM_PERI_OP_QUEUE, &spi_op, sizeof(struct xram_spi_op));
    if (bytes != sizeof(struct xram_hdr)+sizeof(struct xram_spi_op)) {
        printf("xram write operate err.\r\n");
    } else {
        bytes = XRAMRingRead(XRAM_PERI_OP_QUEUE, &tx_hdr, sizeof(struct xram_hdr));
        assert(bytes == sizeof(struct xram_hdr));

        if (tx_hdr.type == XRAM_PERI_TYPE_SPI && tx_hdr.err == SPI_OP_OK && tx_hdr.len == 0) {
            ret = 0;
        }
    }

    xram_peri_mutex_unlock();
    return ret;
}

static int xram_pipe_spi_trans(xram_pipe_spi_t obj, void *tx_data, void *rx_data, uint32_t size, uint32_t timeout)
{
    struct xram_hdr tx_hdr;
    struct xram_spi_op *spi_op;
    int opt_len = 0;
    uint32_t bytes;
    int ret = -1;

    assert(obj != NULL);
    assert(tx_data || rx_data);
    assert(size <= SPI_OPERATION_MAX_SIZE);

    if (xram_peri_mutex_lock()) {
        return -1;
    }

    opt_len = sizeof(struct xram_spi_op) + size;
    spi_op = (struct xram_spi_op *)pvPortMalloc(opt_len);
    if (!spi_op) {
        printf("xram malloc err.\r\n");
        xram_peri_mutex_unlock();
        return -1;
    }

    tx_hdr.type = XRAM_PERI_TYPE_SPI;
    tx_hdr.err = SPI_OP_OK;
    tx_hdr.len = opt_len;   
    spi_op->op = XRAM_SPI_TRANS;
    memcpy(&spi_op->port, obj, sizeof(struct xram_pipe_spi));
    spi_op->timeout = timeout;
    spi_op->len = size;
    if (tx_data)
        memcpy(spi_op->data, tx_data, size);

    bytes = XRAMRingWrite(XRAM_PERI_OP_QUEUE, &tx_hdr, sizeof(struct xram_hdr));
    bytes += XRAMRingWrite(XRAM_PERI_OP_QUEUE, spi_op, opt_len);
    if (bytes != sizeof(struct xram_hdr)+opt_len) {
        printf("xram write operate err.\r\n");
    } else {
        bytes = XRAMRingRead(XRAM_PERI_OP_QUEUE, &tx_hdr, sizeof(struct xram_hdr));
        bytes += XRAMRingRead(XRAM_PERI_OP_QUEUE, spi_op, opt_len);
        assert(bytes == sizeof(struct xram_hdr)+opt_len);

        if (tx_hdr.type == XRAM_PERI_TYPE_SPI && tx_hdr.err == SPI_OP_OK && tx_hdr.len == opt_len) {
            if (rx_data)
                memcpy(rx_data, spi_op->data, spi_op->len);
            ret = 0;
        }
    }
    vPortFree(spi_op);
    
    xram_peri_mutex_unlock();
    return ret;
}

/**
 * @brief init SPI
 *
 * @param[in]  obj  the spi device
 *
 * @return  
 *       - 0 : on success 
 *       - other : error
 */
int xram_pipe_spi_init(xram_pipe_spi_t obj)
{
    return xram_pipe_spi_operation(obj, XRAM_SPI_INIT);
}

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
int xram_pipe_spi_finalize(xram_pipe_spi_t obj)
{
    return xram_pipe_spi_operation(obj, XRAM_SPI_FINALIZE);
}

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
int xram_pipe_spi_send_recv(xram_pipe_spi_t obj, void *tx_data, void *rx_data, uint32_t size, uint32_t timeout)
{
    return xram_pipe_spi_trans(obj, tx_data, rx_data, size, timeout);
}

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
int xram_pipe_spi_send(xram_pipe_spi_t obj, void *data, uint32_t size, uint32_t timeout)
{
    return xram_pipe_spi_trans(obj, data, NULL, size, timeout);
}

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
int xram_pipe_spi_recv(xram_pipe_spi_t obj, void *data, uint32_t size, uint32_t timeout)
{
    return xram_pipe_spi_trans(obj, NULL, data, size, timeout);
}

