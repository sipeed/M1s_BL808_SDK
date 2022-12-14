#ifdef HELPER_OTA_ENABLE
#include <stdio.h>
#include <string.h>

#include <FreeRTOS.h>
#include <task.h>
#include <lwip/mem.h>
#include <lwip/memp.h>
#include <lwip/dhcp.h>
#include <lwip/tcpip.h>
#include <lwip/ip_addr.h>
#include <lwip/sockets.h>
#include <lwip/netdb.h>

#include <cli.h>
#include <bl_sys.h>
#include <helper_ota.h>
#include <hal_boot2.h>
#include <utils_sha256.h>

typedef struct ota_header {
    union {
        struct {
            uint8_t header[16];

            uint8_t type[4];//RAW XZ
            uint32_t len;//body len
            uint8_t pad0[8];

            uint8_t ver_hardware[16];
            uint8_t ver_software[16];

            uint8_t sha256[32];
        } s;
        uint8_t _pad[512];
    } u;
} ota_header_t;
#define OTA_HEADER_SIZE (sizeof(ota_header_t))

static const unsigned char _home_rujun_OTA_bin[] = {
};
static const unsigned int _home_rujun_OTA_bin_len = 47584;

static void ota_test_cmd(char *buf, int len, int argc, char **argv)
{
    unsigned int bin_size, one_time_size, pos;
    uint32_t ota_addr;
    uint8_t activeID;
    PtTable_Entry_Config ptEntry;
    uint32_t buffer[128];

    printf("Starting OTA test. OTA size is %d\r\n", _home_rujun_OTA_bin_len);
    printf("Starting OTA test. OTA bin addr is %p\r\n", (void *)(&_home_rujun_OTA_bin[0]));
    printf("Starting OTA test. OTA header is %08X\r\n", *(unsigned int*)(&_home_rujun_OTA_bin[0]));

    bin_size = _home_rujun_OTA_bin_len;
    activeID = hal_boot2_get_active_partition();
    printf("[OTA] [TEST] activeID is %u\r\n", activeID);

    if (hal_boot2_get_active_entries(PT_ENTRY_FW_CPU0, &ptEntry)) {
        printf("PtTable_Get_Active_Entries fail\r\n");
        return;
    }
    ota_addr = ptEntry.Address[!ptEntry.activeIndex];
    printf("[OTA] [TEST] activeIndex is %u, use OTA address=%08x\r\n", ptEntry.activeIndex, (unsigned int)ota_addr);

    printf("[OTA] [TEST] Erase flash with size %d...", 0x10000);
    XIP_SFlash_Erase_With_Lock(ota_addr, _home_rujun_OTA_bin_len);
    printf("Done\r\n");
    
    
    pos = 0;
    printf("Will Write\r\n");
    while (bin_size) {
        printf("%s:%d\r\n", __func__, __LINE__);
        one_time_size = (bin_size > 512) ? 512 : bin_size;
        printf("%s:%d\r\n", __func__, __LINE__);
        memset(buffer, 0xFF, sizeof(buffer));//OPT only the last page
        printf("%s:%d\r\n", __func__, __LINE__);
        memcpy(buffer, &(_home_rujun_OTA_bin[pos]), one_time_size);
        printf("%s:%d\r\n", __func__, __LINE__);
        printf("[OTA] [TEST] Flash to %p with %u, from %p, byte head %02X\r\n", (void*)(ota_addr + pos), one_time_size, buffer, (unsigned int)buffer[0]);
        XIP_SFlash_Write_With_Lock(ota_addr + pos, (uint8_t*)buffer, one_time_size);
        printf("%s:%d\r\n", __func__, __LINE__);
        printf("%s:%d\r\n", __func__, __LINE__);
        pos += one_time_size;
        printf("%s:%d\r\n", __func__, __LINE__);
        bin_size -= one_time_size;
        printf("%s:%d\r\n", __func__, __LINE__);
    }

    hal_boot2_set_ptable_opt((pPtTable_Flash_Erase)XIP_SFlash_Erase_With_Lock, (pPtTable_Flash_Write)XIP_SFlash_Write_With_Lock); 
    ptEntry.len=_home_rujun_OTA_bin_len;
    hal_boot2_update_ptable(&ptEntry);
    bl_sys_reset_por();
}

static int _check_ota_header(ota_header_t *ota_header, uint32_t *ota_len, int *use_xz)
{
    char str[33];//assume max segment size
    int i;

    memcpy(str, ota_header->u.s.header, sizeof(ota_header->u.s.header));
    str[sizeof(ota_header->u.s.header)] = '\0';
    puts("[OTA] [HEADER] ota header is ");
    puts(str);
    puts("\r\n");

    memcpy(str, ota_header->u.s.type, sizeof(ota_header->u.s.type));
    str[sizeof(ota_header->u.s.type)] = '\0';
    puts("[OTA] [HEADER] file type is ");
    puts(str);
    puts("\r\n");
    if (strstr(str, "XZ")) {
        *use_xz = 1;
    } else {
        *use_xz = 0;
    }

    memcpy(ota_len, &(ota_header->u.s.len), 4);
    printf("[OTA] [HEADER] file length (exclude ota header) is %lu\r\n", *ota_len);

    memcpy(str, ota_header->u.s.ver_hardware, sizeof(ota_header->u.s.ver_hardware));
    str[sizeof(ota_header->u.s.ver_hardware)] = '\0';
    puts("[OTA] [HEADER] ver_hardware is ");
    puts(str);
    puts("\r\n");

    memcpy(str, ota_header->u.s.ver_software, sizeof(ota_header->u.s.ver_software));
    str[sizeof(ota_header->u.s.ver_software)] = '\0';
    puts("[OTA] [HEADER] ver_software is ");
    puts(str);
    puts("\r\n");

    memcpy(str, ota_header->u.s.sha256, sizeof(ota_header->u.s.sha256));
    str[sizeof(ota_header->u.s.sha256)] = '\0';
    puts("[OTA] [HEADER] sha256 is ");
    for (i = 0; i < sizeof(ota_header->u.s.sha256); i++) {
        printf("%02X", str[i]);
    }
    puts("\r\n");

    return 0;
}

extern int XIP_SFlash_Erase_With_Lock(uint32_t addr, int len);
extern int XIP_SFlash_Write_With_Lock(uint32_t addr, uint8_t *src, int len);
#define OTA_PROGRAM_SIZE (512)
static void ota_tcp_cmd(char *buf, int len, int argc, char **argv)
{
    int sockfd, i;
    struct hostent *hostinfo;
    uint8_t *recv_buffer;
    struct sockaddr_in dest;
    iot_sha256_context ctx;
    uint8_t sha256_result[32];
    uint8_t sha256_img[32];

    if (2 != argc) {
        printf("Usage: %s IP\r\n", argv[0]);
        return;
    }
    hostinfo = gethostbyname(argv[1]);
    if (!hostinfo) {
        puts("gethostbyname Failed\r\n");
        return;
    }

    /* Create a socket */
    /*---Open socket for streaming---*/
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Error in socket\r\n");
        return;
    }

    /*---Initialize server address/port struct---*/
    memset(&dest, 0, sizeof(dest));
    dest.sin_family = AF_INET;
    dest.sin_port = htons(3333);
    dest.sin_addr = *((struct in_addr *) hostinfo->h_addr);
    uint32_t address = dest.sin_addr.s_addr;
    char *ip = inet_ntoa(address);

    int ret = 0;
    int total = 0;
    int ota_header_found, use_xz;
    ota_header_t *ota_header;

    recv_buffer = pvPortMalloc(OTA_PROGRAM_SIZE);

    unsigned int buffer_offset, flash_offset, ota_addr;
    uint32_t bin_size, part_size;
    uint8_t activeID;
    PtTable_Entry_Config ptEntry;

    activeID = hal_boot2_get_active_partition();

    printf("Starting OTA test. OTA bin addr is %p\r\n", recv_buffer);

    printf("[OTA] [TEST] activeID is %u\r\n", activeID);

    if (hal_boot2_get_active_entries(PT_ENTRY_FW_CPU0, &ptEntry)) {
        printf("PtTable_Get_Active_Entries fail\r\n");
        vPortFree(recv_buffer);
        return;
    }
    ota_addr = ptEntry.Address[!ptEntry.activeIndex];
    bin_size = ptEntry.maxLen[!ptEntry.activeIndex];
    part_size = ptEntry.maxLen[!ptEntry.activeIndex];
    (void) part_size;
    /*XXX if you use bin_size is product env, you may want to set bin_size to the actual
     * OTA BIN size, and also you need to splilt XIP_SFlash_Erase_With_Lock into
     * serveral pieces. Partition size vs bin_size check is also needed
     */
    printf("Starting OTA test. OTA size is %lu\r\n", bin_size);

    printf("[OTA] [TEST] activeIndex is %u, use OTA address=%08x\r\n", ptEntry.activeIndex, (unsigned int)ota_addr);

    printf("[OTA] [TEST] Erase flash with size %lu...", bin_size);
    XIP_SFlash_Erase_With_Lock(ota_addr, bin_size);
    printf("Done\r\n");

    printf("Server ip Address : %s\r\n", ip);
    /*---Connect to server---*/
    if (connect(sockfd, (struct sockaddr *)&dest, sizeof(dest)) != 0) {
        printf("Error in connect\r\n");
        close(sockfd);
        vPortFree(recv_buffer);
        return;
    }
            
    buffer_offset = 0;
    flash_offset = 0;
    ota_header_found = 0;
    use_xz = 0;

    utils_sha256_init(&ctx);
    utils_sha256_starts(&ctx);
    memset(sha256_result, 0, sizeof(sha256_result));
    while (1) {
        /*first 512 bytes of TCP stream is OTA header*/
        ret = read(sockfd, recv_buffer + buffer_offset, OTA_PROGRAM_SIZE - buffer_offset);
        if (ret < 0) {
            printf("ret = %d, err = %d\n\r", ret, errno);
            break;
        } else {
            total += ret;
            if (0 == ret) {
                printf("[OTA] [TEST] seems ota file ends unexpectedly, already transfer %u\r\n", total);
                break;
            }
            printf("total = %d, ret = %d\n\r", total, ret);
            buffer_offset += ret;

            /*Only handle this case when ota header is NOT found*/
            if (0 == ota_header_found) {
                if (buffer_offset < OTA_PROGRAM_SIZE) {
                    continue;
                } else if (buffer_offset > OTA_PROGRAM_SIZE) {
                    printf("[OTA] [TCP] Assert for unexpected error %d\r\n", buffer_offset);
                    while (1) {
                        /*empty*/
                    }
                }
                /*ota_header is got, we assume alignment of recv_buffer is OK*/
                ota_header_found = 1;
                ota_header = (ota_header_t*)recv_buffer;
                if (_check_ota_header(ota_header, &bin_size, &use_xz)) {
                    /*ota header is NOT OK*/
                    break;
                }
                memcpy(sha256_img, ota_header->u.s.sha256, sizeof(sha256_img));
                /*we think OTA_PROGRAM_SIZE is the same OTA_HEADER_SIZE, and refix total to exclude OTA_PROGRAM_SIZE*/
                total -= OTA_PROGRAM_SIZE;
                buffer_offset = 0;
                printf("[OTA] [TCP] Update bin_size to %lu, file status %s\r\n", bin_size, use_xz ? "XZ" : "RAW");
                continue;
            }

            if (bin_size != total) {
                if (buffer_offset < OTA_PROGRAM_SIZE) {
                    continue;
                } else if (buffer_offset > OTA_PROGRAM_SIZE) {
                    printf("[OTA] [TCP] Assert for unexpected error %d\r\n", buffer_offset);
                    while (1) {
                        /*empty*/
                    }
                }
            } else if (total > bin_size) {
                printf("[OTA] [TCP] Server has bug?\r\n");
                while (1) {
                }
            }

            printf("Will Write %u to %08X from %p\r\n", buffer_offset, ota_addr + flash_offset, recv_buffer);
            utils_sha256_update(&ctx, recv_buffer, buffer_offset);
            XIP_SFlash_Write_With_Lock(ota_addr + flash_offset, (uint8_t*)recv_buffer, buffer_offset);
            flash_offset += buffer_offset;
            buffer_offset = 0;
            if (bin_size == total) {
                utils_sha256_finish(&ctx, sha256_result);
                puts("\r\nCalculated SHA256 Checksum:");
                for (i = 0; i < sizeof(sha256_result); i++) {
                    printf("%02X", sha256_result[i]);
                }
                puts("\r\nHeader SET SHA256 Checksum:");
                for (i = 0; i < sizeof(sha256_img); i++) {
                    printf("%02X", sha256_img[i]);
                }
                puts("\r\n");
                if (memcmp(sha256_img, sha256_result, sizeof(sha256_img))) {
                    /*Error found*/
                    printf("[OTA] [TCP] SHA256 NOT Correct\r\n");
                    break;
                }
                printf("[OTA] [TCP] prepare OTA partition info\r\n");
                hal_boot2_set_ptable_opt((pPtTable_Flash_Erase)XIP_SFlash_Erase_With_Lock, (pPtTable_Flash_Write)XIP_SFlash_Write_With_Lock); 
                ptEntry.len = bin_size;
                printf("[OTA] [TCP] Update PARTITION, partition len is %lu\r\n", ptEntry.len);
                hal_boot2_update_ptable(&ptEntry);
                printf("[OTA] [TCP] Rebooting\r\n");
                bl_sys_reset_por();
            }
        }
    }


    /*---Clean up---*/
    close(sockfd);
    vPortFree(recv_buffer);
    utils_sha256_free(&ctx);

    return;
}

static void ota_dump_cmd(char *buf, int len, int argc, char **argv)
{
    hal_boot2_dump();
}

// STATIC_CLI_CMD_ATTRIBUTE makes this(these) command(s) static
static const struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
    {"ota_test", "OTA test", ota_test_cmd},
    {"ota_tcp", "OTA from TCP server port 3333", ota_tcp_cmd},
    {"ota_dump", "dump partitions for ota related", ota_dump_cmd},
};

int helper_ota_cli_init(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user)/sizeof(cmds_user[0]));          
    return 0;
}
#endif
