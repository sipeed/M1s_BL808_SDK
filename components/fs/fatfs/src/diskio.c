/*
 * Copyright (C) 2015-2017 Alibaba Group Holding Limited
 */
#include <string.h>
#include "fatfs_diskio.h"
#include "ff.h"

#ifdef CONFIG_AOS_FATFS_SUPPORT_MMC
#include <hal/soc/sd.h>
#include <aos/kernel.h>

static sd_dev_t sdmmc;
static DSTATUS  SDMMC_initialize()
{
    DSTATUS stat = STA_NOINIT;

    memset(&sdmmc, 0, sizeof(sd_dev_t));
    if (hal_sd_init(&sdmmc) == RES_OK) {
        stat &= ~STA_NOINIT;
    }

    return stat;
}

static DSTATUS SDMMC_status()
{
    hal_sd_stat status;
    if (hal_sd_stat_get(&sdmmc, &status) == 0) {
        if (status == SD_STAT_TRANSFER)
            return 0;
    }

    return STA_NOINIT;
}

static DRESULT SDMMC_read(BYTE *buff, DWORD sector, UINT count)
{
    DRESULT res = RES_OK;

    if (hal_sd_blks_read(&sdmmc, buff, sector, count, AOS_WAIT_FOREVER) != 0) {
        res = RES_ERROR;
    }

    return res;
}

static DRESULT SDMMC_write(BYTE *buff, DWORD sector, UINT count)
{
    DRESULT res = RES_OK;

    if (hal_sd_blks_write(&sdmmc, buff, sector, count, AOS_WAIT_FOREVER) != 0) {
        res = RES_ERROR;
    }

    return res;
}

static DRESULT SDMMC_ioctl(BYTE cmd, void *buff)
{
    DRESULT       res = RES_ERROR;
    hal_sd_info_t info;

    if (SDMMC_status() & STA_NOINIT)
        return RES_NOTRDY;

    switch (cmd) {
        case CTRL_SYNC:
            res = RES_OK;
            break;

#if FF_USE_MKFS
        case GET_SECTOR_COUNT:
            if (hal_sd_info_get(&sdmmc, &info) == 0) {
                *(DWORD *)buff = info.blk_nums;
                res            = RES_OK;
            }
            break;

        case GET_BLOCK_SIZE:
            *(DWORD *)buff = 1;
            res            = RES_OK;
            break;

        case GET_FORMAT_OPTION:
            *(BYTE *)buff = FM_ANY;
            res           = RES_OK;
            break;
#endif

        case GET_SECTOR_SIZE:
            if (hal_sd_info_get(&sdmmc, &info) == 0) {
                *(WORD *)buff = info.blk_size;
                res           = RES_OK;
            }
            break;
        default:
            res = RES_PARERR;
    }

    return res;
}

#endif

#ifdef CONFIG_AOS_FATFS_SUPPORT_RAM
#include <bl808_glb.h>
static struct {
    uint8_t *base_addr;
    uint32_t total_size;
    uint32_t sector_nums;
    uint32_t sector_size;
    uint8_t stat;
}ram_private;
static DSTATUS  RAM_disk_initialize()
{
    DSTATUS stat = STA_NOINIT;
    static uint8_t is_init = 0;
    if (!is_init) {
        ram_private.base_addr = (uint8_t *)0x53A00000;
        ram_private.total_size = 6 * 1000 * 1000;
        ram_private.sector_size = FF_MIN_SS;
        ram_private.sector_nums = ram_private.total_size / FF_MIN_SS;
        ram_private.stat = 0;
        memset(ram_private.base_addr, 0, ram_private.total_size);
        is_init = 1;
    }
    stat &= ~STA_NOINIT;
    return stat;
}

static DSTATUS RAM_disk_status()
{
    DSTATUS stat = STA_NOINIT;
    stat = ram_private.stat;
    return stat;
}

static DRESULT RAM_disk_read(BYTE *buff, DWORD sector, UINT count)
{
    DRESULT res = RES_OK;
    uint8_t *start_addr = ram_private.base_addr + sector * ram_private.sector_size;
    uint32_t size = count * ram_private.sector_size;
    memcpy(buff, start_addr, size);
    csi_dcache_clean_invalid();
    return res;
}

static DRESULT RAM_disk_write(const BYTE *buff, DWORD sector, UINT count)
{
    
    DRESULT res = RES_OK;
    uint8_t *start_addr = ram_private.base_addr + sector * ram_private.sector_size;
    uint32_t size = count * ram_private.sector_size;
    memcpy(start_addr, buff, size);
    csi_dcache_clean_invalid();
    return res;
}

static DRESULT RAM_disk_ioctl(BYTE cmd, void *buff)
{
    DRESULT       res = RES_ERROR;
    if (RAM_disk_status() & STA_NOINIT)
        return RES_NOTRDY;

    switch (cmd) {
        case CTRL_SYNC:
            res = RES_OK;
            break;

#if FF_USE_MKFS
        case GET_SECTOR_COUNT:
            *(DWORD *)buff = ram_private.sector_nums;
            res            = RES_OK;
            break;

        case GET_BLOCK_SIZE:
            *(DWORD *)buff = 1;
            res            = RES_OK;
            break;

        case GET_FORMAT_OPTION:
            *(BYTE *)buff = FM_ANY;
            res           = RES_OK;
            break;
#endif

        case GET_SECTOR_SIZE:
            *(WORD *)buff = ram_private.sector_size;
            res           = RES_OK;
            break;
        default:
            res = RES_PARERR;
    }

    return res;
}

#endif

#ifdef CONFIG_AOS_FATFS_SUPPORT_FLASH
#include <bl808_glb.h>

#ifdef CPU_M0
#define FLASH_ERASE(a, l) bl_flash_erase((a)+0x1000, (l))
#define FLASH_WRITE(a, b, l) bl_flash_write((a)+0x1000, (b), (l))
#define FLASH_READ(a, b, l) bl_flash_read((a)+0x1000, (b), (l))

extern int bl_flash_erase(uint32_t addr, int len);
extern int bl_flash_write(uint32_t addr, void *src, int len);
extern int bl_flash_read(uint32_t addr, void *dst, int len);
#else
#ifdef CPU_D0
#define FLASH_ERASE(a, l) m1s_xram_flash_erase((a), (l))
#define FLASH_WRITE(a, b, l) m1s_xram_flash_write((a), (b), (l))
#define FLASH_READ(a, b, l) m1s_xram_flash_read((a), (b), (l))

extern int m1s_xram_flash_read(uint32_t offset, void *const addr, uint32_t len);
extern int m1s_xram_flash_write(uint32_t offset, void *const addr, uint32_t len);
extern int m1s_xram_flash_erase(uint32_t offset, uint32_t len);
#else
#error "no cpu selected!"
#define FLASH_ERASE(a, l) 
#define FLASH_WRITE(a, b, l) 
#define FLASH_READ(a, b, l) 

#endif
#endif

static int32_t erase_diff[1024] = {0};

static struct {
    uint8_t *base_addr;
    uint32_t total_size;
    uint32_t sector_nums;
    uint32_t sector_size;
    uint8_t stat;
}flash_private;
static DSTATUS  FLASH_disk_initialize()
{
    memset(erase_diff, 0, sizeof(erase_diff));
    DSTATUS stat = STA_NOINIT;
    static uint8_t is_init = 0;
    if (!is_init) {
        flash_private.base_addr = (uint8_t *)0x300000;
        flash_private.total_size = 8 * 1024 * 1024;
        flash_private.sector_size = FF_MAX_SS;
        flash_private.sector_nums = flash_private.total_size / FF_MAX_SS;
        flash_private.stat = 0;
        is_init = 1;
    }
    stat &= ~STA_NOINIT;
    return stat;
}

static DSTATUS FLASH_disk_status()
{
    DSTATUS stat = STA_NOINIT;
    stat = flash_private.stat;
    return stat;
}

static DRESULT FLASH_disk_read(BYTE *buff, DWORD sector, UINT count)
{
    DRESULT res = RES_OK;
    uint8_t *start_addr = flash_private.base_addr + sector * flash_private.sector_size;
    uint32_t size = count * flash_private.sector_size;
    FLASH_READ(start_addr, buff, size);
    csi_dcache_clean_invalid();
    return res;
}

static DRESULT FLASH_disk_write(const BYTE *buff, DWORD sector, UINT count)
{
    
    DRESULT res = RES_OK;
    uint8_t *start_addr = flash_private.base_addr + sector * flash_private.sector_size;
    uint32_t size = count * flash_private.sector_size;
    // erase_diff[sector] += 1;
    // erase_diff[sector+count] -= 1;
    FLASH_ERASE(start_addr, size);
    FLASH_WRITE(start_addr, buff, size);
    csi_dcache_clean_invalid();
    return res;
}

// void show_erase_counts() {
//     static int32_t erase_counts[sizeof(erase_diff)/sizeof(int32_t)];
//     memcpy(erase_counts, erase_diff, sizeof(erase_diff));

//     printf("\r\n""erase count:""\r\n\t%5d", (int)erase_counts[0]);
//     for(int i=1; i<sizeof(erase_diff)/sizeof(int32_t); i++) {
//         erase_counts[i] += erase_counts[i-1];
//         printf(" %5d", (int)erase_counts[i]);
//         if(i%16 == 15) printf("\r\n\t");
//     }
//     printf("\r\n");
// }

static DRESULT FLASH_disk_ioctl(BYTE cmd, void *buff)
{
    DRESULT       res = RES_ERROR;
    if (FLASH_disk_status() & STA_NOINIT)
        return RES_NOTRDY;

    switch (cmd) {
        case CTRL_SYNC:
            res = RES_OK;
            break;

#if FF_USE_MKFS
        case GET_SECTOR_COUNT:
            *(DWORD *)buff = flash_private.sector_nums;
            res            = RES_OK;
            break;

        case GET_BLOCK_SIZE:
            *(DWORD *)buff = 1;
            res            = RES_OK;
            break;

        case GET_FORMAT_OPTION:
            *(BYTE *)buff = FM_ANY;
            res           = RES_OK;
            break;
#endif

        case GET_SECTOR_SIZE:
            *(WORD *)buff = flash_private.sector_size;
            res           = RES_OK;
            break;
        default:
            res = RES_PARERR;
    }

    return res;
}

#endif

DSTATUS ff_disk_status(BYTE pdrv)
{
    switch (pdrv) {
#ifdef CONFIG_AOS_FATFS_SUPPORT_MMC
        case DEV_MMC:
            return SDMMC_status();
#endif

#ifdef CONFIG_AOS_FATFS_SUPPORT_USB
        case DEV_USB:
            retutn USB_disk_status();
#endif

#ifdef CONFIG_AOS_FATFS_SUPPORT_RAM
        case DEV_RAM:
            return RAM_disk_status();
#endif

#ifdef CONFIG_AOS_FATFS_SUPPORT_FLASH
        case DEV_FLASH:
            return FLASH_disk_status();
#endif
        default:
            break;
    }
    return STA_NOINIT;
}

DSTATUS ff_disk_initialize(BYTE pdrv)
{
    switch (pdrv) {
#ifdef CONFIG_AOS_FATFS_SUPPORT_MMC
        case DEV_MMC:
            return SDMMC_initialize();
#endif

#ifdef CONFIG_AOS_FATFS_SUPPORT_USB
        case DEV_USB:
            return USB_disk_initialize();
#endif

#ifdef CONFIG_AOS_FATFS_SUPPORT_RAM
        case DEV_RAM:
            return RAM_disk_initialize();
#endif

#ifdef CONFIG_AOS_FATFS_SUPPORT_FLASH
        case DEV_FLASH:
            return FLASH_disk_initialize();
#endif
        default:
            break;
    }
    return STA_NOINIT;
}

DRESULT ff_disk_read(BYTE pdrv, BYTE *buff, DWORD sector, UINT count)
{
    switch (pdrv) {
#ifdef CONFIG_AOS_FATFS_SUPPORT_MMC
        case DEV_MMC:
            return SDMMC_read(buff, sector, count);
#endif

#ifdef CONFIG_AOS_FATFS_SUPPORT_USB
        case DEV_USB:
            return USB_disk_read(buff, sector, count);
#endif

#ifdef CONFIG_AOS_FATFS_SUPPORT_RAM
        case DEV_RAM:
            return RAM_disk_read(buff, sector, count);
#endif

#ifdef CONFIG_AOS_FATFS_SUPPORT_FLASH
        case DEV_FLASH:
            return FLASH_disk_read(buff, sector, count);
#endif
        default:
            break;
    }
    return RES_PARERR;
}

DRESULT ff_disk_write(BYTE pdrv, const BYTE *buff, DWORD sector, UINT count)
{
    switch (pdrv) {
#ifdef CONFIG_AOS_FATFS_SUPPORT_MMC
        case DEV_MMC:
            return SDMMC_write((BYTE *)buff, sector, count);
#endif

#ifdef CONFIG_AOS_FATFS_SUPPORT_USB
        case DEV_USB:
            return USB_disk_write(buff, sector, count);
#endif

#ifdef CONFIG_AOS_FATFS_SUPPORT_RAM
        case DEV_RAM:
            return RAM_disk_write(buff, sector, count);
#endif

#ifdef CONFIG_AOS_FATFS_SUPPORT_FLASH
        case DEV_FLASH:
            return FLASH_disk_write(buff, sector, count);
#endif
        default:
            break;
    }
    return RES_PARERR;
}

DRESULT ff_disk_ioctl(BYTE pdrv, BYTE cmd, void *buff)
{
    switch (pdrv) {
#ifdef CONFIG_AOS_FATFS_SUPPORT_MMC
        case DEV_MMC:
            return SDMMC_ioctl(cmd, buff);
#endif

#ifdef CONFIG_AOS_FATFS_SUPPORT_USB
        case DEV_USB:
            return USB_disk_ioctl(cmd, buff);
#endif

#ifdef CONFIG_AOS_FATFS_SUPPORT_RAM
        case DEV_RAM:
            return RAM_disk_ioctl(cmd, buff);
#endif

#ifdef CONFIG_AOS_FATFS_SUPPORT_FLASH
        case DEV_FLASH:
            return FLASH_disk_ioctl(cmd, buff);
#endif
        default:
            break;
    }
    return RES_PARERR;
}
