/*
 * Copyright (C) 2015-2017 Alibaba Group Holding Limited
 */

#ifndef FS_FAT_DISKIO_H
#define FS_FAT_DISKIO_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "diskio.h"

/* Definitions of physical driver number of each drive */
#define DEV_MMC 0   /* Map MMC/SD card to physical drive 0 */
#define DEV_USB 1   /* Map USB to physical drive 1 */
#define DEV_RAM 2   /* Map ramdisk to physical drive 2 */
#define DEV_FLASH 3 /* Map FLASH to physical drive 3 */

#define MMC_MOUNTPOINT      "/sdcard"
#define MMC_PARTITION_ID    "sd:"

#define USB_MOUNTPOINT      "/usb"
#define USB_PARTITION_ID    "usb:"

#define RAM_MOUNTPOINT      "/ramdisk"
#define RAM_PARTITION_ID    "ram:"

#define FLASH_MOUNTPOINT      "/flash"
#define FLASH_PARTITION_ID    "flash:"

#ifdef __cplusplus
 }
#endif


#endif
