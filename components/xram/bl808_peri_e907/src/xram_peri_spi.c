/**
 * xram_peri_spi.c
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
#include <bl_flash.h>
#include <xram_peripheral.h>
#include <xram_peri_spi.h>
#include <xram_peri_common.h>
#include <xram_spi_common.h>
#include <bl808_common.h>
#include <xram.h>
#include "hosal_spi.h"

static int xram_spi_int(struct xram_spi_op *op)
{
    struct xram_hdr hdr;
    uint32_t bytes;
    uint8_t operation_ret = SPI_OP_OK;

    hosal_spi_dev_t spi;
    spi.port = op->port;
    spi.config.mode = op->mode;
    spi.config.dma_enable = op->dma_enable;
    spi.config.polar_phase = op->polar_phase;
    spi.config.freq = op->freq;
    spi.config.pin_clk = op->pin_clk;
    spi.config.pin_mosi = op->pin_mosi;
    spi.config.pin_miso = op->pin_miso;
    if (hosal_spi_init(&spi) != 0)
        operation_ret = SPI_OP_ERR;

    hdr.type = XRAM_PERI_TYPE_SPI;
    hdr.err = operation_ret;
    hdr.len = 0;
    bytes = XRAMRingWrite(XRAM_PERI_OP_QUEUE, &hdr, sizeof(struct xram_hdr));
    if (bytes == sizeof(struct xram_hdr)) {
        return SPI_OP_OK;
    } else {
        printf("xram ring write err.\r\n");
        return SPI_OP_ERR;
    }
}

static int xram_spi_finalize(struct xram_spi_op *op)
{
    struct xram_hdr hdr;
    uint32_t bytes;
    uint8_t operation_ret = SPI_OP_OK;

    hosal_spi_dev_t spi;
    spi.port = op->port;
    spi.config.mode = op->mode;
    spi.config.dma_enable = op->dma_enable;
    spi.config.polar_phase = op->polar_phase;
    spi.config.freq = op->freq;
    spi.config.pin_clk = op->pin_clk;
    spi.config.pin_mosi = op->pin_mosi;
    spi.config.pin_miso = op->pin_miso;
    if (hosal_spi_finalize(&spi) != 0)
        operation_ret = SPI_OP_ERR;
    else
        hosal_spi_set_cs(op->pin_cs, 1);

    hdr.type = XRAM_PERI_TYPE_SPI;
    hdr.err = operation_ret;
    hdr.len = 0;
    bytes = XRAMRingWrite(XRAM_PERI_OP_QUEUE, &hdr, sizeof(struct xram_hdr));
    if (bytes == sizeof(struct xram_hdr)) {
        return SPI_OP_OK;
    } else {
        printf("xram ring write err.\r\n");
        return SPI_OP_ERR;
    }
}

static int xram_spi_trans(struct xram_spi_op *op, void *data, uint32_t size, uint32_t timeout)
{
    struct xram_hdr hdr;
    uint32_t bytes;
    uint8_t operation_ret = SPI_OP_OK;

    hosal_spi_dev_t spi;
    spi.port = op->port;
    spi.config.mode = op->mode;
    spi.config.dma_enable = op->dma_enable;
    spi.config.polar_phase = op->polar_phase;
    spi.config.freq = op->freq;
    spi.config.pin_clk = op->pin_clk;
    spi.config.pin_mosi = op->pin_mosi;
    spi.config.pin_miso = op->pin_miso;
    hosal_spi_set_cs(op->pin_cs, 0);
    if (hosal_spi_send_recv(&spi, data, data, size, timeout) != 0)
        operation_ret = SPI_OP_ERR;
    hosal_spi_set_cs(op->pin_cs, 1);

    hdr.type = XRAM_PERI_TYPE_SPI;
    hdr.err = operation_ret;
    hdr.len = sizeof(struct xram_spi_op)+size;
    bytes = XRAMRingWrite(XRAM_PERI_OP_QUEUE, &hdr, sizeof(struct xram_hdr));
    bytes += XRAMRingWrite(XRAM_PERI_OP_QUEUE, op, sizeof(struct xram_spi_op)+size);
    if (bytes == sizeof(struct xram_hdr)+sizeof(struct xram_spi_op)+size) {
        return SPI_OP_OK;
    } else {
        printf("xram ring write err.\r\n");
        return SPI_OP_ERR;
    }
}

void xram_spi_operation_handle(uint32_t len)
{
    struct xram_spi_op *spi_op;
    uint32_t bytes;
    uint8_t *buffer = (uint8_t *)pvPortMalloc(len);

    assert(buffer);

    bytes = XRAMRingRead(XRAM_PERI_OP_QUEUE, buffer, len);
    if (bytes == len) {
        spi_op = ( struct xram_spi_op *)buffer;

        switch (spi_op->op){
            case XRAM_SPI_INIT: {
                xram_spi_int(spi_op);
                break;
               }
            case XRAM_SPI_FINALIZE: {
                xram_spi_finalize(spi_op);
                break;
            }
            case XRAM_SPI_TRANS: {
                xram_spi_trans(spi_op, spi_op->data, spi_op->len, spi_op->timeout);
                break;
            }
            default: {
                printf("xram spi operate type err.\r\n");
                break;
            }
        }
    }
    vPortFree(buffer);
}

