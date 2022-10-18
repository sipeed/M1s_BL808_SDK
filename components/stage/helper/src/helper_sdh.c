#include <stdio.h>
#include <string.h>
#include <sys/fcntl.h>

#include <FreeRTOS.h>
#include <task.h>

#include <vfs.h>
#include <cli.h>
#include <aos/kernel.h>
#include <helper_sdh.h>

#include "utils_log.h"

static void fatfs_test_cmd(char *buf, int len, int argc, char **argv)
{
    aos_dir_t * dp;
    int fd_txt, counter = 0, ret;
    char path_txt[32];
    char *txt_buffer;

    dp = (aos_dir_t *)aos_opendir("/sdcard");
    if (dp) {
        aos_dirent_t *out_dirent;
        counter = 0;
        while(1) {
            out_dirent = (aos_dirent_t *)aos_readdir(dp);
            if (out_dirent == NULL) {
                break;
            }
            printf("file name is %s\r\n", out_dirent->d_name);
            counter++;
        }
        aos_closedir(dp);
    } else {
        printf("dp is NULL, when dump sdcard\r\n");
    }

    snprintf(path_txt, sizeof(path_txt), "/sdcard/bl60x_%d.txt\r\n", counter);
    printf("Tring to create txt file: %s\r\n", path_txt);
    fd_txt = aos_open(path_txt, O_RDWR | O_CREAT | O_TRUNC);
    if (fd_txt >= 0) {
        aos_write(fd_txt, path_txt, strlen(path_txt));
        aos_close(fd_txt);
    }

    printf("dumping again....\r\n");

    dp = (aos_dir_t *)aos_opendir("/sdcard");
    if (dp) {
        aos_dirent_t *out_dirent;
        counter = 0;
        while(1) {
            out_dirent = (aos_dirent_t *)aos_readdir(dp);
            if (out_dirent == NULL) {
                break;
            }
            printf("file name is %s\r\n", out_dirent->d_name);
            counter++;
        }
        aos_closedir(dp);
    } else {
        printf("dp is NULL, when dump sdcard\r\n");
    }

    fd_txt = aos_open(path_txt, 0);
    if (fd_txt >= 0) {
        txt_buffer = pvPortMalloc(129);
        if (txt_buffer) {
            ret = aos_read(fd_txt, txt_buffer, 128);//one byte left for string tail
            if (ret > 0 && ret < 128) {
                printf("Read %d bytes from file\r\n", ret);
                txt_buffer[ret] = '\0';
                printf("Content is:\r\n %s\r\n", txt_buffer);
            } else {
                printf("Error when read file content, ret is %d\r\n", ret);
                goto error_out;
            }
        } else {
            printf("No mem when alloc for txt buffer");
            goto error_out;
        }
    }

error_out:
    return;
}

void cmd_sdh_wtest(char *buf, int len, int argc, char **argv)
{
    int fd = -1;
    int i;
    char *test_buf = 0;

    test_buf = pvPortMalloc(4096);

    if (test_buf == 0) {
        log_error("SDH buf error.\r\n");
        return;
    }

    log_info("sdh_wtest start.\r\n");
    memset(test_buf, 0x55, 4096);
    fd = aos_open("/sdcard/wtest.txt", O_RDWR | O_CREAT | O_TRUNC);
    if (fd < 0) {
        log_error("open err.\r\n");
        return;
    }

    for(i = 0; i < 100; i++) {
        aos_write(fd, test_buf, 4096);
        aos_msleep(10);
    }

    aos_close(fd);
    vPortFree(test_buf);

    log_info("sdh_wtest stop.\r\n");
}

void cmd_sdh_w100m(char *buf, int len, int argc, char **argv)
{
    int fd = -1;
    char *test_buf = NULL;
    uint32_t i, time_start, time_end;

    test_buf = pvPortMalloc(1024 * 64);

    if (test_buf == 0) {
        log_error("SDH buf error.\r\n");
        return;
    }
    memset(test_buf, 0x55, 1024 * 64);
    log_info("MALLOC test_buf = %p\r\n", test_buf);

    {
        /* 64k */
        fd = aos_open("/sdcard/w64k.txt", O_RDWR | O_CREAT | O_TRUNC);
        if (fd < 0) {
            log_error("open err.\r\n");
            return;
        }
        log_info("start write.\r\n");
        time_start = xTaskGetTickCount();
        for(i = 0; i < 16*100; i++) {
            aos_write(fd, test_buf, 64*1024);
        }
        time_end = xTaskGetTickCount();
        log_info("end write.\r\n");
        log_info("unit 64k, 100M Byte use %ld ms\r\n", (time_end - time_start));
        aos_close(fd);
    }

    {
        /* 32k */
        fd = aos_open("/sdcard/w32k.txt", O_RDWR | O_CREAT | O_TRUNC);
        if (fd < 0) {
            log_error("open err.\r\n");
            return;
        }
        log_info("start write.\r\n");
        time_start = xTaskGetTickCount();
        for(i = 0; i < 32*100; i++) {
            aos_write(fd, test_buf, 32*1024);
        }
        time_end = xTaskGetTickCount();
        log_info("end write.\r\n");
        log_info("unit 32k, 100M Byte use %ld ms\r\n", (time_end - time_start));
        aos_close(fd);
    }

    {
        /* 16k */
        fd = aos_open("/sdcard/w16k.txt", O_RDWR | O_CREAT | O_TRUNC);
        if (fd < 0) {
            log_error("open err.\r\n");
            return;
        }
        log_info("start write.\r\n");
        time_start = xTaskGetTickCount();
        for(i = 0; i < 64*100; i++) {
            aos_write(fd, test_buf, 16*1024);
        }
        time_end = xTaskGetTickCount();
        log_info("end write.\r\n");
        log_info("unit 16k, 100M Byte use %ld ms\r\n", (time_end - time_start));
        aos_close(fd);
    }

    {
        /* 8k */
        fd = aos_open("/sdcard/w8k.txt", O_RDWR | O_CREAT | O_TRUNC);
        if (fd < 0) {
            log_error("open err.\r\n");
            return;
        }
        log_info("start write.\r\n");
        time_start = xTaskGetTickCount();
        for(i = 0; i < 128*100; i++) {
            aos_write(fd, test_buf, 8*1024);
        }
        time_end = xTaskGetTickCount();
        log_info("end write.\r\n");
        log_info("unit 8k, 100M Byte use %ld ms\r\n", (time_end - time_start));
        aos_close(fd);
    }

    vPortFree(test_buf);
}

// STATIC_CLI_CMD_ATTRIBUTE makes this(these) command(s) static
const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
    {"test_sdh", "test SDH based on fatfs", fatfs_test_cmd},
    {"sdh_wtest", "sdh_wtest", cmd_sdh_wtest},
    {"sdh_w100m", "cmd_sdh_w100m", cmd_sdh_w100m},
};

int helper_sdh_cli_init(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user)/sizeof(cmds_user[0]));
    return 0;
}
