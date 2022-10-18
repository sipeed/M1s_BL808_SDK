/**
 * xram_pipe_flash.c
 * Copyright (c) 2022 jni <jni@bouffalolab.com>
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

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <ring.h>
#include <xram_platform.h>
#include <xram_peripheral.h>
#include <xram_pipe_flash.h>
#include <xram_peri_common.h>

static uint8_t s_tx_buffer[XRAM_MSG_HDR + XRAM_FLASH_OPERATION + FLASH_OPERATION_MAX_SIZE];
static xram_pipe_flash_t flash_obj = NULL;
/* create a xram pipe flash object, connect e907 backend service
 * param:
 *  flash_id: the flash_id to operate
 * return:
 *  null: faild
 *  other: the flash object
 **/
xram_pipe_flash_t xram_pipe_flash_create(int flash_id)
{
    struct xram_hdr *hdr = NULL;
    struct xram_hdr rx_hdr;
    struct xram_flash_op rx_opt;
    xram_pipe_flash_t xram_flash = NULL;
    xram_flash_op_t flash_op = NULL;
    uint32_t bytes;

    assert(flash_id < XRAM_FLASH_ID_MAX && flash_id >= XRAM_FLASH_ID_1);

    if (xram_peri_mutex_lock()) {
        return NULL;
    }

    hdr = (struct xram_hdr *)s_tx_buffer;
    hdr->type = XRAM_PERI_TYPE_FLASH;
    hdr->len = XRAM_FLASH_OPERATION;

    flash_op = (xram_flash_op_t)(s_tx_buffer + XRAM_MSG_HDR);
    flash_op->flash_id = flash_id;
    flash_op->size = 0;
    flash_op->offset = 0;
    flash_op->len = 0;
    flash_op->op = XRAM_FLASH_CREATE;

    bytes = XRAMRingWrite(XRAM_PERI_OP_QUEUE, s_tx_buffer, XRAM_MSG_HDR + hdr->len);
    if (!bytes) {
        printf("xram flash operate err.\r\n");
    } else {
        while (1) {
            bytes = XRAMRingRead(XRAM_PERI_OP_QUEUE, &rx_hdr, XRAM_MSG_HDR);
            assert(bytes == XRAM_MSG_HDR);

            if (rx_hdr.type == XRAM_PERI_TYPE_FLASH && rx_hdr.err == FLASH_OP_OK && rx_hdr.len > 0) {
                bytes = XRAMRingRead(XRAM_PERI_OP_QUEUE, &rx_opt, rx_hdr.len);
                if (bytes) {
                    xram_flash = calloc(1, sizeof(struct xram_pipe_flash));
                    if (xram_flash == NULL) {
                        printf("calloc xram_flash failed!\r\n");
                        break;
                    }

                    xram_flash->flash_id = rx_opt.flash_id;
                    xram_flash->size = rx_opt.size;
                    break;
                } else {
                    printf("xram flash read err msg.\r\n");
                }
            }
        }
    }

    if (xram_peri_mutex_unlock()) {
        return NULL;
    }

    return xram_flash;
}

/* destroy the xram pipe flash object, close e907 backend service
 * param:
 *  obj: the flash object
 * return:
 *  none
 **/
void xram_pipe_flash_destroy(xram_pipe_flash_t *obj)
{
    assert(obj != NULL);

    /* FIXME */
    free(*obj);
    *obj = NULL;
}

/* read flash
 * param:
 *  obj: the flash object
 *  offset: offset to read
 *  buffer: the buffer to hold content for flash read operate
 *  length: the buffer length
 * return:
 *  >=0: number of bytes read
 *  <0: error
 **/
int xram_pipe_flash_read(xram_pipe_flash_t obj, unsigned int offset, void *buffer, size_t length)
{
    struct xram_hdr *hdr = NULL;
    struct xram_hdr rx_hdr;
    xram_flash_op_t flash_op = NULL;
    uint32_t bytes = 0;

    assert(obj != NULL && buffer != NULL);
    assert(offset + length <= obj->size);

    if (xram_peri_mutex_lock()) {
        return NULL;
    }

    hdr = (struct xram_hdr *)s_tx_buffer;
    hdr->type = XRAM_PERI_TYPE_FLASH;
    hdr->len = XRAM_FLASH_OPERATION;

    flash_op = (xram_flash_op_t)(s_tx_buffer + XRAM_MSG_HDR);
    flash_op->flash_id = obj->flash_id;
    flash_op->size = obj->size;
    flash_op->offset = offset;
    flash_op->len = length;
    flash_op->op = XRAM_FLASH_READ;

    bytes = XRAMRingWrite(XRAM_PERI_OP_QUEUE, s_tx_buffer, XRAM_MSG_HDR + hdr->len);
    if (!bytes) {
        printf("xram flash operate err.\r\n");
    } else {
        while (1) {
            bytes = XRAMRingRead(XRAM_PERI_OP_QUEUE, &rx_hdr, XRAM_MSG_HDR);
            assert(bytes == XRAM_MSG_HDR);

            if (rx_hdr.type == XRAM_PERI_TYPE_FLASH && rx_hdr.err == FLASH_OP_OK && rx_hdr.len > 0) {
                bytes = XRAMRingRead(XRAM_PERI_OP_QUEUE, buffer, rx_hdr.len);
                if (!bytes) {
                    printf("xram flash read err msg.\r\n");
                } else {
                    break;
                }
            }else{
                bytes = 0;
                printf("flash read err hdr.\r\n");
            }
        }
    }

    if (xram_peri_mutex_unlock()) {
        return 0;
    }
    return bytes;
}

/* write flash
 * param:
 *  obj: the flash object
 *  offset: offset to write
 *  buffer: the buffer to hold content for flash read operate
 *  length: the buffer length
 * return:
 *  >=0: number of bytes write
 *  <0: error
 **/
int xram_pipe_flash_write(xram_pipe_flash_t obj, unsigned int offset, const void *buffer, size_t length)
{
    struct xram_hdr *hdr = NULL;
    struct xram_hdr rx_hdr;
    xram_flash_op_t flash_op = NULL;
    uint32_t bytes;

    assert(obj != NULL && buffer != NULL);
    assert(offset + length <= obj->size);

    if (xram_peri_mutex_lock()) {
        return NULL;
    }

    hdr = (struct xram_hdr *)s_tx_buffer;
    hdr->type = XRAM_PERI_TYPE_FLASH;
    hdr->len = XRAM_FLASH_OPERATION + length;

    flash_op = (xram_flash_op_t)(s_tx_buffer + XRAM_MSG_HDR);
    flash_op->flash_id = obj->flash_id;
    flash_op->size = obj->size;
    flash_op->offset = offset;
    flash_op->len = length;
    flash_op->op = XRAM_FLASH_WRITE;
    memcpy(flash_op->data, buffer, length);

    bytes = XRAMRingWrite(XRAM_PERI_OP_QUEUE, s_tx_buffer, XRAM_MSG_HDR + hdr->len);
    if (!bytes) {
        printf("xram flash operate err.\r\n");
    } else {
        while (1) {
            bytes = XRAMRingRead(XRAM_PERI_OP_QUEUE, &rx_hdr, XRAM_MSG_HDR);
            assert(bytes == XRAM_MSG_HDR);

            if (rx_hdr.type == XRAM_PERI_TYPE_FLASH && rx_hdr.err == FLASH_OP_OK && rx_hdr.len == 0) {
                bytes = length;
                break;
            }
        }
    }
    
    if (xram_peri_mutex_unlock()) {
        return 0;
    }
    return bytes;
}

/* erase flash
 * param:
 *  obj: the flash object
 *  offset: offset to erase
 *  length: the length to erase
 * return:
 *  0: success
 *  <0: error
 **/
int xram_pipe_flash_erase(xram_pipe_flash_t obj, unsigned int offset, size_t length)
{
    struct xram_hdr *hdr = NULL;
    struct xram_hdr rx_hdr;
    xram_flash_op_t flash_op = NULL;
    uint32_t bytes;

    assert(obj != NULL);
    assert(offset + length <= obj->size);

    if (xram_peri_mutex_lock()) {
        return NULL;
    }

    hdr = (struct xram_hdr *)s_tx_buffer;
    hdr->type = XRAM_PERI_TYPE_FLASH;
    hdr->len = XRAM_FLASH_OPERATION;

    flash_op = (xram_flash_op_t)(s_tx_buffer + XRAM_MSG_HDR);
    flash_op->flash_id = obj->flash_id;
    flash_op->size = obj->size;
    flash_op->offset = offset;
    flash_op->len = length;
    flash_op->op = XRAM_FLASH_ERASE;

    bytes = XRAMRingWrite(XRAM_PERI_OP_QUEUE, s_tx_buffer, XRAM_MSG_HDR + hdr->len);
    if (!bytes) {
        bytes = -1;
        printf("xram flash operate err.\r\n");
    } else {
        while (1) {
            bytes = XRAMRingRead(XRAM_PERI_OP_QUEUE, &rx_hdr, XRAM_MSG_HDR);
            assert(bytes == XRAM_MSG_HDR);

            if (rx_hdr.type == XRAM_PERI_TYPE_FLASH && rx_hdr.err == FLASH_OP_OK && rx_hdr.len == 0) {
                bytes = 0;
                break;
            }
        }
    }

    if (xram_peri_mutex_unlock()) {
        return 0;
    }
    return bytes;
}

int bl_xram_flash_init(void)
{
    XRAMRingReset(XRAM_PERI_OP_QUEUE);
    
    if(xram_peri_mutex_init())
    {
        printf("[thread 1] xram flash semaphore init failed!\r\n");
    }

    flash_obj = xram_pipe_flash_create(XRAM_FLASH_ID_1);
    if(flash_obj){
        if(flash_obj->flash_id == XRAM_FLASH_ID_1 && flash_obj->size == XRAM_ADDR_LIMIT){
            printf("[thread 1] xram pipe flash create success.[%p] [%d] [%x]\r\n",flash_obj,XRAM_FLASH_ID_1,XRAM_ADDR_LIMIT);
        }
    }else{
        xram_peri_mutex_destory();
        printf("creat flash obj failed,\r\n");
        return -1;
    }
    return 0;
}

int bl_xram_flash_erase(unsigned int addr, size_t length)
{
    return xram_pipe_flash_erase(flash_obj, addr, length);
}

int bl_xram_flash_write(unsigned int addr, const void *buffer, size_t length)
{
    return xram_pipe_flash_write(flash_obj, addr, buffer, length);
}

int bl_xram_flash_read(unsigned int addr, const void *buffer, size_t length)
{
    return xram_pipe_flash_read(flash_obj, addr, buffer, length);
}

int bl_xram_flash_deinit(void)
{
    xram_pipe_flash_destroy(&flash_obj);
    return 0;
}
