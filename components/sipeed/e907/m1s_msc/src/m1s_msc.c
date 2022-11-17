#include "m1s_msc.h"

#include <FreeRTOS.h>
#include <bl808_glb.h>
#include <bl_flash.h>
#include <bl_mtd.h>
#include <diskio.h>
#include <ff.h>
#include <hal/soc/sd.h>
#include <hal_sys.h>
#include <sys/fcntl.h>
#include <task.h>
#include <usbd_core.h>
#include <usbd_msc.h>

#pragma GCC diagnostic ignored "-Wint-conversion"

static struct {
    int fatfs_num;
    sd_dev_t sd;
    uint32_t blk_nums;
    uint32_t blk_size;
    uint8_t write_start;
    uint64_t last_write_ms;
    uint8_t *cache_d0fw_buff;
    uint8_t *check_d0fw_buff;
} private;

#define USBD_VID 0xffff
#define USBD_PID 0xffff
#define USBD_LANGID_STRING 1033
#define USB_MSC_DESC_SIZ (unsigned long)(9 + MSC_DESCRIPTOR_LEN)
#define USBD_OUT_EP (0x01)
#define USBD_IN_EP (0x81)
static uint8_t usbd_descriptor[] = {
    USB_DEVICE_DESCRIPTOR_INIT(USB_2_0, 0x00, 0x00, 0x00, USBD_VID, USBD_PID, 0x0001, 0x01),
    USB_CONFIG_DESCRIPTOR_INIT(USB_MSC_DESC_SIZ, 0x01, 0x01, USB_CONFIG_BUS_POWERED, 100),
    MSC_DESCRIPTOR_INIT(0, USBD_OUT_EP, USBD_IN_EP, 0),
    ///////////////////////////////////////
    /// string0 descriptor
    ///////////////////////////////////////
    USB_LANGID_INIT(USBD_LANGID_STRING),
    ///////////////////////////////////////
    /// string1 descriptor
    ///////////////////////////////////////
    0x0E,                       /* bLength */
    USB_DESCRIPTOR_TYPE_STRING, /* bDescriptorType */
    'S', 0x00,                  /* wcChar0 */
    'i', 0x00,                  /* wcChar1 */
    'p', 0x00,                  /* wcChar2 */
    'e', 0x00,                  /* wcChar3 */
    'e', 0x00,                  /* wcChar4 */
    'd', 0x00,                  /* wcChar5 */
    ///////////////////////////////////////
    /// string2 descriptor
    ///////////////////////////////////////
    0x1A,                       /* bLength */
    USB_DESCRIPTOR_TYPE_STRING, /* bDescriptorType */
    'M', 0x00,                  /* wcChar0 */
    'a', 0x00,                  /* wcChar1 */
    's', 0x00,                  /* wcChar2 */
    's', 0x00,                  /* wcChar3 */
    ' ', 0x00,                  /* wcChar4 */
    'S', 0x00,                  /* wcChar5 */
    't', 0x00,                  /* wcChar6 */
    'o', 0x00,                  /* wcChar7 */
    'r', 0x00,                  /* wcChar8 */
    'a', 0x00,                  /* wcChar9 */
    'g', 0x00,                  /* wcChar10 */
    'e', 0x00,                  /* wcChar11 */
    ///////////////////////////////////////
    /// string3 descriptor
    ///////////////////////////////////////
    0x12,                       /* bLength */
    USB_DESCRIPTOR_TYPE_STRING, /* bDescriptorType */
    '2', 0x00,                  /* wcChar0 */
    '0', 0x00,                  /* wcChar1 */
    '2', 0x00,                  /* wcChar2 */
    '2', 0x00,                  /* wcChar3 */
    '1', 0x00,                  /* wcChar4 */
    '0', 0x00,                  /* wcChar5 */
    '1', 0x00,                  /* wcChar6 */
    '4', 0x00,                  /* wcChar7 */
};

static int gen_ram_fatfs(TCHAR *path)
{
    FATFS fs;
    FRESULT res;
    if (FR_OK == (res = f_mount(&fs, path, 1))) {
        res = f_unmount(path);
    } else {
        res = -1;
        uint8_t *work = malloc(FF_MAX_SS);
        if (work) {
            res = f_mkfs(path, 0, work, FF_MAX_SS);
            free(work);
        }
    }
    return res;
}

static void usb_clock_init(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_CGEN_CFG1);
    tmpVal |= (1 << 13);
    BL_WR_REG(GLB_BASE, GLB_CGEN_CFG1, tmpVal);
    GLB_Set_USB_CLK_From_WIFIPLL(1);
}

static void upload_c906_firmware(uint8_t *d0fw, uint32_t size)
{
    bl_mtd_handle_t handle;
    bl_mtd_info_t info = {0};
    bl_mtd_open("D0FW", &handle, BL_MTD_OPEN_FLAG_BUSADDR);
    bl_mtd_info(handle, &info);
    bl_mtd_close(handle);
    if (info.offset != 0 && info.size >= size) {
        info.offset += 0x1000;
        if (bl_flash_erase(info.offset, size) || bl_flash_write(info.offset, d0fw, size) ||
            bl_flash_read(info.offset, private.check_d0fw_buff, size)) {
            printf("flash operation failed..\r\n");
            return;
        }
        if (memcmp(d0fw, private.cache_d0fw_buff, size)) {
            printf("d0fw code check failed, please upload again..\r\n");
            return;
        }
        printf("upload is ok!\r\n");
        hal_reboot();
    }
}

static void upload_firmware_cb(TCHAR *path)
{
    FATFS fs;
    FIL fil;
    FRESULT res;
    DIR dir;
    FILINFO fno;
    UINT br;
    TCHAR fw_path[50] = {0};

    if (FR_OK != (res = f_mount(&fs, path, 0))) goto _exit;

    if (FR_OK != (res = f_opendir(&dir, path))) goto _exit;
    while (1) {
        res = f_readdir(&dir, &fno);
        if (res != FR_OK || fno.fname[0] == 0) break;

        if (!(fno.fattrib & AM_DIR)) {
            printf("%s%s\r\n", path, fno.fname);
            int len = strlen(fno.fname);
            if (fno.fname[len - 4] == '.' && fno.fname[len - 3] == 'b' && fno.fname[len - 2] == 'i' &&
                fno.fname[len - 1] == 'n') {
                snprintf(fw_path, sizeof(fw_path), "%s%s", path, fno.fname);
                printf("find bin:%s\r\n", fw_path);
                break;
            }
        }
    }
    f_closedir(&dir);

    if (FR_OK != (res = f_stat(fw_path, &fno))) goto _exit;
    if (FR_OK != (res = f_open(&fil, fw_path, FA_READ))) goto _exit;
    if (FR_OK != (res = f_read(&fil, private.cache_d0fw_buff, fno.fsize, &br))) goto _exit;
    if (fno.fsize == br) upload_c906_firmware(private.cache_d0fw_buff, br);
    if (FR_OK != (res = f_close(&fil))) goto _exit;
    if (FR_OK != (res = f_unlink(fw_path))) goto _exit;
    if (FR_OK != (res = f_unmount(fw_path))) goto _exit;
_exit:
    return;
}

static void upload_firmware_handle(void *param)
{
    char *path = (char *)param;
    while (1) {
        uint64_t curr_ms = xTaskGetTickCount();
        if (private.write_start) {
            if (curr_ms - private.last_write_ms > 500) {
                upload_firmware_cb(path);
                private.write_start = 0;
            }
        }
        vTaskDelay(50);
    }
}

void usbd_msc_get_cap(uint8_t lun, uint32_t *block_num, uint16_t *block_size)
{
    *block_num = 0;
    *block_size = 0;

    switch (private.fatfs_num) {
        case 0:
        case 2:
        case 3:
            disk_ioctl(private.fatfs_num, GET_SECTOR_COUNT, block_num);
            disk_ioctl(private.fatfs_num, GET_SECTOR_SIZE, block_size);

            break;
    }

    private.blk_nums = *block_num;
    private.blk_size = *block_size;
}

int usbd_msc_sector_read(uint32_t sector, uint8_t *buffer, uint32_t length)
{
    switch (private.fatfs_num) {
        case 0:
        case 2:
        case 3:
            if (RES_OK != disk_read(private.fatfs_num, buffer, sector, length / private.blk_size)) {
                return -1;
            }
            break;
    }

    return 0;
}

int usbd_msc_sector_write(uint32_t sector, uint8_t *buffer, uint32_t length)
{
    switch (private.fatfs_num) {
        case 0:
        case 2:
        case 3:
            if (RES_OK != disk_write(private.fatfs_num, buffer, sector, length / private.blk_size)) {
                return -1;
            }
            if (private.fatfs_num == 2) {
                private.last_write_ms = xTaskGetTickCount();
                private.write_start = 1;
            }
            break;
    }

    return 0;
}

int m1s_msc_init(uint8_t type)
{
    private.fatfs_num = type;
    if (type == 0) {  // MMC Fatfs
        printf("flash usb disk\r\n");
    } else if (type == 2) {  // RAM Fatfs
        char *path = "2:";
        if (0 != gen_ram_fatfs(path)) return -1;
        /*
            Note: 0x52000000~0x527FFFFF(8M) used to cache d0fw
                  0x52800000~0x52FFFFFF(8M) used to check d0fw
                  At this time, c906 is not started, so this part of memory can be used safely
        */
        private.cache_d0fw_buff = 0x52000000;
        private.check_d0fw_buff = 0x52800000;
        if (pdTRUE != xTaskCreate(upload_firmware_handle, "upload firmware", 10*1024, path, 15, NULL)) return -1;
    } else if (type == 3) {  // RAM Fatfs
        printf("flash usb disk\r\n");
    }

    // msc init
    usb_clock_init();
    usbd_desc_register(usbd_descriptor);
    usbd_msc_class_init(USBD_OUT_EP, USBD_IN_EP);
    if (0 != usbd_initialize()) return -1;
    return 0;
}
