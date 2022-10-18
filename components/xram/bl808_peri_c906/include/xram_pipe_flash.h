/**
 * xram_pipe_flash.h
 * Copyright (c) 2022 Bouffalolab
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

#ifndef _XRAM_PIPE_FLASH_
#define _XRAM_PIPE_FLASH_

/* xram pipe flash object
 **/
struct xram_pipe_flash {
    int flash_id;
    unsigned int size;
};
typedef struct xram_pipe_flash *xram_pipe_flash_t;

/* create a xram pipe flash object, connect e907 backend service
 * param:
 *  flash_id: the flash_id to operate
 * return:
 *  null: faild
 *  other: the flash object
 **/
xram_pipe_flash_t xram_pipe_flash_create(int flash_id);

/* destroy the xram pipe flash object, close e907 backend service
 * param:
 *  obj: the flash object
 * return:
 *  none
 **/
void xram_pipe_flash_destroy(xram_pipe_flash_t *obj);

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
int xram_pipe_flash_read(xram_pipe_flash_t obj, unsigned int offset, void *buffer, size_t length);

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
int xram_pipe_flash_write(xram_pipe_flash_t obj, unsigned int offset, const void *buffer, size_t length);

/* erase flash
 * param:
 *  obj: the flash object
 *  offset: offset to erase
 *  length: the length to erase
 * return:
 *  0: success
 *  <0: error
 **/
int xram_pipe_flash_erase(xram_pipe_flash_t obj, unsigned int offset, size_t length);

/* init flash
 * param:
 * NULL 
 * return:
 *  0: success
 *  <0: error
 **/
int bl_xram_flash_init(void);

/* erase flash
 * param:
 *  addr: offset to erase
 *  length: the length to erase
 * return:
 *  0: success
 *  <0: error
 **/
int bl_xram_flash_erase(unsigned int addr, size_t length);

/* write flash
 * param:
 *  addr: offset to write
 *  buffer: the buffer to hold content for flash read operate
 *  length: the buffer length
 * return:
 *  >=0: number of bytes write
 *  <0: error
 **/
int bl_xram_flash_write(unsigned int addr, const void *buffer, size_t length);

/* read flash
 * param:
 *  addr: offset to read
 *  buffer: the buffer to hold content for flash read operate
 *  length: the buffer length
 * return:
 *  >=0: number of bytes read
 *  <0: error
 **/
int bl_xram_flash_read(unsigned int addr, const void *buffer, size_t length);

/* deinit flash
 * param:
 * NULL
 * return:
 *  >=0: number of bytes read
 *  <0: error
 **/
int bl_xram_flash_deinit(void);
#endif
