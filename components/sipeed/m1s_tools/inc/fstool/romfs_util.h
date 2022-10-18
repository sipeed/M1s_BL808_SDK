#pragma once

#include <stdio.h>

/* fs */
#include <fs/vfs_romfs.h>
#include <vfs.h>

static int get_file_from_romfs(char *name, char **xip_addr)
{
    int fd = -1;
    romfs_filebuf_t filebuf;

    if (0 > (fd = aos_open(name, 0))) {
        printf("%s not found!\r\n", name);
        return -1;
    }

    aos_ioctl(fd, IOCTL_ROMFS_GET_FILEBUF, (long unsigned int)&filebuf);
    *xip_addr = filebuf.buf;
    printf("Found file %s. XIP Addr %p, len %#x\r\n", name, filebuf.buf, filebuf.bufsize);
    return filebuf.bufsize;
}