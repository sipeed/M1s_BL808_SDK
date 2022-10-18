#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <aos/kernel.h>
#include <cli.h>
#include <errno.h>
#include <core_rv32.h>

#include <lwip/sockets.h>
#include <lwip/tcp.h>

#include "sample_common.h"
#include "helper_socket.h"
#include "helper_dsp2.h"
#include "helper_dsp2_parse.h"
#include "img_struct.h"
#include "img_param.h"
//#include<json-c/json.h>

#define IPERF_BUFSZ     (4 * 1300)
#define PSOT 6666

#define PREFIX_BYTES    5
#define VERSION_BYTES   1
#define CMDIDX_BYTES    2
#define PAYLOADLEN_BYTES    8
#define PAYLOAD_BYTES       256
#define CHECKSUM_BYTES  1

#define PREFIX "BLAIC"

/* blaic_cmd */
enum blaic_cmd {
    BLAIC_MONITOR =  0,
    BLAIC_GET,
    BLAIC_SET,
    BLAIC_DUMP,
    BLAIC_LOAD,
    BLAIC_RET,
    BLAIC_RET_JSTR,
    BLAIC_SIZE,
};

static char re_message[512] = {'\0'};
static char cmd_version0_message[512] = {'\0'};
static char buf_temp[512] = {'\0'};

static int add_formate(char* re_data, unsigned long payload_len, int blaic_cmd, char *re_message)
{
    //char buf[512] = {'\0'};
    int buf_size = 0;
    memset(buf_temp, '\0', sizeof(char) * 512);

    strncat(buf_temp, "BLAIC", sizeof(char) * PREFIX_BYTES);
    //aos_cli_printf("2buf: %s\r\n", buf);

    strncat(buf_temp, "0", sizeof(char) * VERSION_BYTES);
    //aos_cli_printf("3buf: %s\r\n", buf);

    char blaic_cmd_str[3] = {'\0'};
    sprintf(blaic_cmd_str, "%02x", blaic_cmd);
    strncat(buf_temp, blaic_cmd_str, sizeof(char) * CMDIDX_BYTES);
    //aos_cli_printf("4buf: %s\r\n", buf);

    char payload_len_str[9] = {'\0'};
    sprintf(payload_len_str, "%08lX", payload_len);
    //aos_cli_printf("payload_len_str: %s\r\n", payload_len_str);
    strncat(buf_temp, payload_len_str, sizeof(char) * PAYLOADLEN_BYTES);
    //aos_cli_printf("5buf: %s\r\n", buf);

    buf_size = PREFIX_BYTES + VERSION_BYTES + CMDIDX_BYTES + PAYLOADLEN_BYTES;

    if (blaic_cmd != BLAIC_SIZE) {
        buf_size += payload_len;
        strncat(buf_temp, re_data, sizeof(char) * payload_len);
        //aos_cli_printf("6buf: %s\r\n", buf);
    }

    memcpy(re_message, buf_temp, sizeof(char) * buf_size);
    //aos_cli_printf("8buf: %s\r\n", re_message);

    return 0;
}

static int parseFormat(char* recv_data, int* cmd_version)
{
    char cmd_version_str[4] = "0x0";

    strncpy(&cmd_version_str[2], recv_data, VERSION_BYTES);
    *cmd_version = strtoul(cmd_version_str, NULL, 0);// must with '0x  atoi(cmd_version_str);
    recv_data+=VERSION_BYTES;

    return VERSION_BYTES;
}

static int replyClient(int connected, int reply_val, char* message, char* re_message)
{
    // the ret_message less then 512
    int payload_len = 0;
    int transfer_size = 0;
    int message_len = strlen(message);
    char *re_msg_ptr = re_message;

    if (message_len >= 512) return -1;

    if (reply_val == 0) strcat(re_message, "[OK]");
    else strcat(re_message, "[NG]");
    strncat(re_message, message, message_len);
    payload_len = strlen(re_message);
    //aos_cli_printf("===========payload_len %d, %s@\r\n", payload_len, re_message);

    add_formate(re_message, payload_len, BLAIC_RET, re_msg_ptr);
    //aos_cli_printf("re_message:%s@\r\n", re_message);
    transfer_size = send(connected, re_message, strlen(re_message), 0);
    if (transfer_size != strlen(re_message)) return -1;
    //aos_cli_printf("send_size: %d\r\n", transfer_size);

    return 0;
}

static int sendData(int connected, uint8_t *buf_addr, uint32_t buf_size)
{
    int cnt = 0;
    int total_size = buf_size;
    int reast_size = 0;
    int transfer_size = 0;

    while (total_size > 0) {
        reast_size = MIN(1024, total_size);
        transfer_size = send(connected, buf_addr, reast_size, 0);
        if (transfer_size < 0) {
            aos_cli_printf("[socket] write error, errno: %d\r\n", errno);
            return -1;
        } else if (transfer_size == 0) {
            continue;
        } else {
            total_size -= transfer_size;
            buf_addr += transfer_size; 
            //aos_cli_printf("total_size: %d, reast_size: %d \r\n", total_size, reast_size);
            if ((cnt++ % 50) == 0) aos_cli_printf("[socket] remaining data: %d KB\r\n", total_size>>10);
        }
    }
    return 0;
}

static int recvData(int connected, uint8_t *buf_addr, uint32_t buf_size)
{
    int total_size = buf_size;
    int reast_size = 0;
    int transfer_size = 0;

    total_size = buf_size;
    while (total_size > 0) {
        reast_size = MIN(1024, total_size);
        transfer_size = recv(connected, buf_addr, reast_size, 0);
        aos_cli_printf("recved: %d\r\n", transfer_size);
        if (transfer_size < 0){
             aos_cli_printf("[socket] read error, errno: %d\r\n", errno);
             return -1;
        } else if (transfer_size == 0) {
             continue;
        } else {
            total_size -= transfer_size;
            buf_addr += transfer_size; 
            //aos_cli_printf("total_size: %d, reast_size: %d \r\n", total_size, reast_size);
         }
    }
    return 0;
}

static int get_DSP2_reg(int connected, char *recv_data_ptr, int payload_len, char* re_message)
{
    char *token;
    const char delim[2] = " ";
    char module[32] = {'\0'};
    char reg[32] = {'\0'};
    int reply_val = 0;

    token = strtok(recv_data_ptr, delim);
    sprintf(module, token);
    token = strtok(NULL, delim);
    sprintf(reg, token);

    reply_val = parse_dsp2_cmd(module, reg, NULL, payload_len, re_message);
    //aos_cli_printf("module:%s, reg:%s, re_message:%s\r\n", module, reg, re_message);

    return reply_val;
}

static int set_DSP2_reg(int connected, char *recv_data_ptr, int payload_len, char* re_message)
{
    char *token;
    const char delim[2] = " ";
    char module[32] = {'\0'};
    char reg[32] = {'\0'};
    int reply_val = 0;

    token = strtok(recv_data_ptr, delim);
    sprintf(module, token);
    token = strtok(NULL, delim);
    sprintf(reg, token);
    token = strtok(NULL, delim);

    reply_val = parse_dsp2_cmd(module, reg, token, payload_len, re_message);
    //aos_cli_printf("module:%s, reg:%s, val:%s, re_message:%s\r\n", module, reg, token, re_message);

    return reply_val;
}

static int ret_False(int connected, char* re_message)
{
    int transfer_size = 0;

    memset(re_message, '\0', sizeof(char) * 512);
    add_formate(NULL, 0, BLAIC_SIZE, re_message);
    strcat(re_message, "[NG]");
    transfer_size = send(connected, re_message, strlen(re_message), 0);
    if (transfer_size != strlen(re_message)) return -1;

    return 0;
}

static int dump_DSP2_buff(int connected, char *recv_data_ptr, int payload_len, char* re_message)
{
    char *token;
    char *ret_val_ptr;
    const char delim[2] = " ";
    const char delim_colon[2] = ":";
    const char delim_comma[2] = ",";
    char module[32] = {'\0'};
    char reg[32] = {'\0'};
    char addr_str[16] = {'\0'};
    char size_str[16] = {'\0'};
    uint8_t *buf_addr = NULL;
    uint32_t buf_size;
    int reply_val =  0;
    int transfer_size = 0;

    // parse addr_cmd 
    token = strtok(recv_data_ptr, delim);
    sprintf(module, token);
    token = strtok(NULL, delim);
    sprintf(reg, token);
    token = strtok(NULL, delim);
    //aos_cli_printf("module:%s, reg:%s, token:%s\r\n", module, reg, token);

    // DSP2_Dump_Parse
    reply_val = parse_dsp2_cmd(module, reg, token, payload_len, re_message);
    if (reply_val < 0) {
        ret_False(connected, re_message);
        return -1;
    }
    
    ret_val_ptr =  strtok(re_message, delim_colon);
    ret_val_ptr =  strtok(NULL, delim_colon);
    
    token =  strtok(ret_val_ptr, delim_comma);
    buf_addr = strtoul(token, NULL, 0);// must with '0x'
    
    token =  strtok(NULL, delim_comma);
    buf_size = strtoul(token, NULL, 0);// must with '0x'
    //aos_cli_printf("DUMP addr: 0x%x, size: %u\r\n", buf_addr, buf_size);

    // return mem size
    memset(re_message, '\0', sizeof(char) * 512);
    add_formate(NULL, buf_size, BLAIC_SIZE, re_message);
    strcat(re_message, "[OK]");
    //aos_cli_printf("re_message: %s@, strlen(re_message): %d\r\n", re_message, strlen(re_message));
    transfer_size = send(connected, re_message, strlen(re_message), 0);
    if (transfer_size != strlen(re_message)) return -1;

    reply_val = sendData(connected, buf_addr, buf_size);

    return reply_val;
}

static int load_DSP2_buff(int connected, char *recv_data_ptr, int payload_len, char* re_message)
{
    char *token;
    char *ret_val_ptr;
    const char delim[2] = " ";
    const char delim_colon[2] = ":";
    const char delim_comma[2] = ",";
    char module[32] = {'\0'};
    char reg[32] = {'\0'};
    int reply_val = 0;
    int transfer_size = 0;
    char addr_str[16] = {'\0'};
    char size_str[16] = {'\0'};
    uint8_t *buf_addr = 0;
    uint32_t buf_size;
    char hex_value[] = "0x00000000";

    if (payload_len == 0){
        ret_False(connected, re_message);
        return -1;
    }

   // parse addr_cmd 
   token = strtok(recv_data_ptr, delim);
   sprintf(module, token);
   token = strtok(NULL, delim);
   sprintf(reg, token);
   token = strtok(NULL, delim);
   if (strstr(reg, "gamma_curve") != NULL) {
        buf_size = sizeof(gamma_cal_t);
   } else if (strstr(reg, "wdr_tone_curve") != NULL) {
        buf_size = sizeof(wdr_tone_curve_conf_t);
   } else {
        buf_size = strtoul(token, NULL, 0);// must with '0x'
   }
   //aos_cli_printf("module:%s, reg:%s, buf_size:%d\r\n", module, reg, buf_size);

   add_formate(NULL, buf_size, BLAIC_SIZE, re_message);
   strcat(re_message, "[OK]");
   transfer_size = send(connected, re_message, strlen(re_message), 0);
   if (transfer_size != strlen(re_message)) return -1;

   // DSP2_Load_Parse
   memset(re_message, '\0', sizeof(char) * 512);
   reply_val = parse_dsp2_cmd(module, reg, token, payload_len, re_message);
   //aos_cli_printf("re_message:%s@\r\n",re_message);
   if (reply_val < 0) return -1;
   ret_val_ptr =  strtok(re_message, delim_colon);
   ret_val_ptr =  strtok(NULL, delim_colon);
   //aos_cli_printf("ret_val_ptr:%s@\r\n",ret_val_ptr);

   token =  strtok(ret_val_ptr, delim_comma);
   buf_addr = strtoul(token, NULL, 0);// must with '0x'
    //aos_cli_printf("buf_addr:%d, buf_size: 0x%x, \r\n", (uint32_t)buf_addr, buf_size);
    reply_val = recvData(connected, buf_addr, buf_size);
    csi_dcache_clean_range(buf_addr, buf_size);

    return reply_val;
}

int cmd_version0(int connected, char* recv_data, char*re_message)
{
    //version tpye 0:{cmd_idx}{payload_en}{paylen}, paylen: {module} {reg} {val}
    char *recv_data_ptr = recv_data;
    int blaic_cmd;
    unsigned long payload_len = 0;
    int reply_val = 0;
    char blaic_cmd_str[5] = "0x00";
    char hex_value[11] = "0x00000000";

    memset(cmd_version0_message, '\0', sizeof(char) * 512);

    strncpy(&blaic_cmd_str[2], recv_data_ptr, CMDIDX_BYTES);
    blaic_cmd = strtoul(blaic_cmd_str, NULL, 0);// must with '0x  atoi(blaic_cmd_str);
    recv_data_ptr+=CMDIDX_BYTES;

    strncpy(&hex_value[2], recv_data_ptr, PAYLOADLEN_BYTES);
    payload_len = strtoul(hex_value, NULL, 0);// must with '0x'
    recv_data_ptr+=PAYLOADLEN_BYTES;

    if(blaic_cmd == BLAIC_MONITOR) {
       sprintf(cmd_version0_message, "BLAIC_MONITOR");
    } else if (blaic_cmd == BLAIC_GET) {
       reply_val = get_DSP2_reg(connected,recv_data_ptr, payload_len, cmd_version0_message);
    } else if (blaic_cmd == BLAIC_SET) {
       reply_val = set_DSP2_reg(connected,recv_data_ptr, payload_len, cmd_version0_message);
    } else if(blaic_cmd == BLAIC_DUMP) {
       reply_val = dump_DSP2_buff(connected, recv_data_ptr, payload_len, cmd_version0_message);
       memset(cmd_version0_message, '\0', sizeof(char) * 512);
    } else if(blaic_cmd == BLAIC_LOAD) {
       reply_val = load_DSP2_buff(connected, recv_data_ptr, payload_len, cmd_version0_message);
       memset(cmd_version0_message, '\0', sizeof(char) * 512);
    }
    if (blaic_cmd == BLAIC_DUMP) return 0;
    reply_val = replyClient(connected, reply_val, cmd_version0_message, re_message);

    return reply_val;
}

static int set_block_mode(int fd, int mode)
{
    int flags = 0;

    if ((flags = fcntl(fd, F_GETFL, 0)) < 0) {
        printf("Get flags of socket error");
        return -1;
    }

    flags = mode ? (flags & ~O_NONBLOCK) : (flags | O_NONBLOCK);
    if (fcntl(fd, F_SETFL, flags) < 0) {
        printf("Set flags of socket error");
        return -1;
    }
    return 0;
}

void socket_server(void)
{
    char *recv_data = NULL;
    uint32_t sin_size;
    char *recv_data_ptr;
    char blaic_key[6] = {'\0'};
    int cmd_version = 0;
    int reply_val = 0;
    int offset = 0;

    int sock = -1, connected, bytes_received = 0;
    struct sockaddr_in server_addr, client_addr;

    recv_data = (char *)pvPortMalloc(IPERF_BUFSZ);
    if (recv_data == NULL)
    {
        printf("No memory\r\n");
        goto __exit;
    }
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        printf("Socket error\r\n");
        goto __exit;
    }

    server_addr.sin_family = PF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PSOT);

    if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1) {
        printf("Unable to bind\r\n");
        goto __exit;
    }

    if (listen(sock, 5) == -1) {
        printf("Listen error\r\n");
        goto __exit;
    }
    aos_cli_printf("wait to listen...\r\n");

    sin_size = sizeof(struct sockaddr_in);
    while(1) {
        connected = accept(sock, (struct sockaddr *)&client_addr, (socklen_t *)&sin_size);
        if (connected < 0) {
               printf("accept error\r\n");
               goto __exit;
        }
        printf("new client connected from (%s, %d)\r\n",
                  inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));

        while (1) {
            bytes_received = recv(connected, recv_data, IPERF_BUFSZ, 0);
            if (bytes_received <= 0) {
                printf("recv: %s (%d)\n", strerror(errno), errno);
                break;
            }
            aos_cli_printf("=========================================================\r\n");
            aos_cli_printf("Get:%s@ %d\r\n",recv_data, bytes_received);

            strncpy(blaic_key, recv_data, PREFIX_BYTES);
            if (strcmp(blaic_key, "BLAIC") != 0) {
                memset(blaic_key, '\0', sizeof(char) * (PREFIX_BYTES + 1));
                break;
            }
            recv_data+=PREFIX_BYTES;

            offset = parseFormat(recv_data, &cmd_version);
            recv_data_ptr = recv_data + offset;
            if (cmd_version == 0) {
                memset(re_message, '\0', sizeof(char) * 512);
                reply_val = cmd_version0(connected, recv_data_ptr, re_message);
            } else{
                 reply_val = -1;
            }
       }

        if (connected >= 0) closesocket(connected);
        connected = -1;
    }

__exit:
    if (sock >= 0) closesocket(sock);
    if (recv_data) vPortFree(recv_data);

    //return 0;
}

void socket_server_entry(void)
{
    int host_len;
    char *host;
    const char name[] = "socket_server";
    host_len = strlen(name) + 4;
    host = pvPortMalloc(host_len);//mem will be free in tcpc_entry
    strcpy(host, name);
    aos_task_new("dsp2_socket", socket_server, host, 4096);
}

static void socket_reg_cmd(char *buf, int len, int argc, char **argv)
{
    socket_server_entry();
}

const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
        { "socket", "socket related register", socket_reg_cmd },
};

int helper_socket_cli_init(void)
{
    return 0;
}

