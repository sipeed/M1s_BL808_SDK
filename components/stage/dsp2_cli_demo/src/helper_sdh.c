#include <stdio.h>
#include <string.h>
#include <sys/fcntl.h>

#include <FreeRTOS.h>
#include <task.h>

#include <vfs.h>
#include <cli.h>
#include <helper_sdh.h>


#define INPUT_PCM_FILE_NAME     "/sdcard/input.pcm"
#define READ_SIZE 512

static void fatfs_test_cmd(char *buf, int len, int argc, char **argv)
{
    aos_dir_t * dp;
    int fd_txt, counter = 0, ret;
    char path_txt[32];
    //char big_chunk[1024];
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

    snprintf(path_txt, sizeof(path_txt), "/sdcard/bl60x__%d.txt\r\n", counter);
    printf("Tring to create txt file: %s\r\n", path_txt);
    fd_txt = aos_open(path_txt, O_RDWR | O_CREAT | O_TRUNC);
    if (fd_txt >= 0) {
        aos_write(fd_txt, path_txt, strlen(path_txt));
//        aos_write(fd_txt, big_chunk, sizeof(big_chunk));  // write for second time
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
        txt_buffer = pvPortMalloc(READ_SIZE+1);
        if (txt_buffer) {
            ret = aos_read(fd_txt, txt_buffer, READ_SIZE);//one byte left for string tail
            if (ret > 0 && ret <= READ_SIZE) {
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

const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
    {"test_sdh", "test SDH based on fatfs", fatfs_test_cmd},                                       
};                                                                                   

int helper_sdh_cli_init(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user) / sizeof(cmds_user[0]));
    return 0;
}
