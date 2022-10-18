/*
 * Copyright (c) 2020 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <string.h>
#include <venc_framework.h>

extern venc_framework_device_t _ld_symbol_rom_framework_venc_device_start;
extern venc_framework_device_t _ld_symbol_rom_framework_venc_device_end;

extern venc_framework_device_t h264enc_main_dev;
extern venc_framework_device_t h264enc_sub_dev;
extern venc_framework_device_t jpeg_enc_dev;

int venc_framework_factory_build(const char *name, venc_framework_device_t **device)
{
    /* TODO: use device table later */
    //venc_framework_device_t *start, *end;

    if (0 == strcmp(name, "h264_main")) {
        *device = &h264enc_main_dev;
        return 0;
    }
    if (0 == strcmp(name, "h264_sub")) {
        *device = &h264enc_sub_dev;
        return 0;
    }
    if (0 == strcmp(name, "jpeg")) {
        *device = &jpeg_enc_dev;
        return 0;
    }

    return -1;
}

int venc_framework_factory_destory(venc_framework_device_t **device)
{
    if (!device)
        return -1;

    *device = NULL;

    return 0;
}

