#include <stdio.h>
#include <string.h>
#include <FreeRTOS.h>
#include <task.h>
#include <aos/kernel.h>
#include <aos/yloop.h>
#include <lwip/mem.h>
#include <lwip/memp.h>
#include <lwip/dhcp.h>
#include <lwip/tcpip.h>
#include <lwip/ip_addr.h>
#include <lwip/netifapi.h>
#include <lwip/sockets.h>
#include <cli.h>
#include <wifi_mgmr_ext.h>
#include <helper_wifi.h>
#include <easyflash.h>

#include <airkiss.h>
#include <bl60x_fw_api.h>
#include <bl_efuse.h>
#include <utils_hexdump.h>

#define TYPE_AIRKISS_DONE (EV_USER + 2)  
#define USE_40MHZ_SCAN_LIST (1)

#define WIFI_AP_PSM_SSID           "conf_ap_ssid"
#define WIFI_AP_PSM_PSK            "conf_ap_psk"

static airkiss_context_t akcontex;
static airkiss_result_t akresult;
static int airkiss_is_ready = 0;//1 for airkiss started, 2 for airkiss is locked, 3 for airkiss is finised
static int ds_channel = 0;
static uint8_t airkiss_random = 0;
static int airkiss_finished = 0;
#ifdef USE_40MHZ_SCAN_LIST
static const uint8_t channel_scan_list[][2] = {
    {1, 2},//channel 1 higher band
    {2, 2},//channel 2 higher band
    {3, 2},//channel 3 higher band
    {4, 2},//channel 4 higher band
    {5, 2},//channel 5 higher band
    {6, 2},//channel 6 higher band
    {7, 2},//channel 7 higher band
    {8, 2},//channel 8 higher band
    {9, 2},//channel 9 higher band
    {10, 2},//channel 10 higher band
    {13, 1},//channel 13 lower band
    {12, 1},//channel 1 lower band
    {11, 1},//channel 1 lower band
    {10, 1},//channel 1 lower band
    {9, 1},//channel 1 lower band
    {8, 1},//channel 1 lower band
    {7, 1},//channel 1 lower band
    {6, 1},//channel 1 lower band
    {5, 1},//channel 1 lower band
};
#else
static const uint8_t channel_scan_list[][2] = {
    {1, 0},
    {2, 0},
    {3, 0},
    {4, 0},
    {5, 0},
    {6, 0},
    {7, 0},
    {8, 0},
    {9, 0},
    {10, 0},
    {11, 0},
    {12, 0},
    {13, 0},
    {14, 0},
};
#endif
static int chanel_scan_idx = 1;
static int use_40Mhz = 0;

static void cmd_rf_dump(char *buf, int len, int argc, char **argv)
{
    bl60x_fw_dump_data();
}

static void wifi_scan_cmd(char *buf, int len, int argc, char **argv)
{
    wifi_mgmr_scan();
}

static void wifi_mon_cmd(char *buf, int len, int argc, char **argv)
{
    wifi_mgmr_sniffer_enable();
}

static uint8_t packet_raw[] = {
    0x48, 0x02,
    0x00, 0x00,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0x33, 0x33, 0x33, 0x33, 0x33, 0x33,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0x00, 0x00
};

static void cmd_wifi_raw_send(char *buf, int len, int argc, char **argv)
{
    static uint32_t seq = 0;

    packet_raw[sizeof(packet_raw) - 2] = ((seq << 4) & 0xFF);
    packet_raw[sizeof(packet_raw) - 1] = (((seq << 4) & 0xFF00) >> 8);
    seq++;

    if (wifi_mgmr_raw_80211_send(packet_raw, sizeof(packet_raw))) {
        puts("Raw send failed\r\n");
    } else {
        puts("Raw send succeed\r\n");
    }
}

static void wifi_disconnect_cmd(char *buf, int len, int argc, char **argv)
{
    wifi_mgmr_sta_disconnect();
    /*XXX Must make sure sta is already disconnect, otherwise sta disable won't work*/
    vTaskDelay(1000);
    wifi_mgmr_sta_disable(NULL);
}

static void wifi_connect_cmd(char *buf, int len, int argc, char **argv)
{
    wifi_interface_t wifi_interface;

    if (3 != argc) {
        printf("[USAGE]: %s [ssid] [password]\r\n", argv[0]);
        return;
    }

    wifi_interface = wifi_mgmr_sta_enable();
    wifi_mgmr_sta_connect(wifi_interface, argv[1], argv[2], NULL, NULL, 0, 0);
}

static void event_cb_airkss_done(input_event_t *event, void *private_data)                                                                        
{
    wifi_interface_t wifi_interface;
    airkiss_result_t *result = (airkiss_result_t*)event->value;

    printf("[EVENT] Aikiss Done, result is %p\r\n", result);
    printf("[EVENT] ssid is %s\r\n", result->ssid);
    printf("[EVENT] pwd is %s\r\n", result->pwd);
    printf("[EVENT] ssid len is %d\r\n", result->ssid_length);
    printf("[EVENT] pwd len is %d\r\n", result->pwd_length);
    printf("[EVENT] random is %d\r\n", result->random);
    airkiss_random = result->random;//store random

    /*Clean Sniffer Mode*/
    wifi_mgmr_sniffer_unregister(NULL);
    wifi_mgmr_sniffer_disable();
    wifi_interface = wifi_mgmr_sta_enable();
    wifi_mgmr_sta_connect(wifi_interface, result->ssid, result->pwd, NULL, NULL, 0, 0);
}

static void airkiss_confirm_cb(void *arg)
{
    int state = WIFI_STATE_UNKNOWN;
    int magic_random = (int)arg;

    if (wifi_mgmr_state_get(&state)) {
        printf("[TIMER] Error get wifi state\r\n");
    } else {
        switch (state) {
            case WIFI_STATE_CONNECTED_IP_GOT:
            /*IP is found*/
            {
                struct sockaddr_in sender_local_sockaddr, sock_broadcast;
                int sender_socketfd, i;

                printf("Sending confirm...\r\n");
                sender_socketfd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

                memset(&sender_local_sockaddr, 0, sizeof(struct sockaddr_in));
                sender_local_sockaddr.sin_family = AF_INET;
                sender_local_sockaddr.sin_addr.s_addr = inet_addr("0.0.0.0");
                sender_local_sockaddr.sin_port = htons(10000);

                if (bind(sender_socketfd, (struct sockaddr*)&sender_local_sockaddr, sizeof(sender_local_sockaddr))) {
                    break;
                }

                memset(&sock_broadcast, 0, sizeof(struct sockaddr_in));
                sock_broadcast.sin_family = PF_INET;
                sock_broadcast.sin_port = htons(10000);
                sock_broadcast.sin_addr.s_addr = inet_addr("255.255.255.255");
                for (i = 0; i < 20; i++) {
                    lwip_sendto(sender_socketfd, &magic_random, 1, 0, (struct sockaddr*)&sock_broadcast, sizeof(struct sockaddr_in));
                    vTaskDelay(50);//FIXME use delay called
                }

                lwip_close(sender_socketfd);
                printf("Sending confirm finished\r\n");
                airkiss_finished = 1;
                printf("Notify exiting\r\n");
                //bl_sys_reset_por();
            }
            break;
            case WIFI_STATE_CONNECTED_IP_GETTING:
            case WIFI_STATE_CONNECTING:
            case WIFI_STATE_IDLE:
            case WIFI_STATE_DISCONNECT:
            case WIFI_STATE_UNKNOWN:
            case WIFI_STATE_IFDOWN:
            case WIFI_STATE_SNIFFER:
            default:
            /*Loop Again*/
            {
                aos_post_delayed_action(100, airkiss_confirm_cb, NULL);
            }
        }
    }
}

static void app_delayed_action(void *arg)
{
    switch (airkiss_is_ready) {
        case 0: 
        /*Just schedule next action*/
        {
            aos_post_delayed_action(100, app_delayed_action, NULL);
        }
        break;
        case 1:
        /*scan channel*/
        {
            chanel_scan_idx++;
            chanel_scan_idx = chanel_scan_idx > (sizeof(channel_scan_list)/sizeof(channel_scan_list[0])) ? 1 : chanel_scan_idx;
            wifi_mgmr_channel_set(channel_scan_list[chanel_scan_idx - 1][0], channel_scan_list[chanel_scan_idx - 1][1]);
            aos_post_delayed_action(100, app_delayed_action, NULL);
            if (1 == chanel_scan_idx) {
                printf("\r[TIMER] Switching channel %02d...", chanel_scan_idx);
            } else {
                printf("\b\b\b\b\b%02d...", chanel_scan_idx);
            }
        }
        break;
        case 2:
        /*airkiss is locked*/
        {
            if (ds_channel > 0) {
                wifi_mgmr_channel_set(ds_channel, use_40Mhz);
                printf("[TIMER] Fix channel to %d\r\n", ds_channel);
                airkiss_is_ready = 3;
            } else {
                int channel = 0;
                /*Wait for ds_channel*/

                wifi_mgmr_channel_get(&channel);
                channel++;
                channel = channel > 13 ? 1 : channel;
                wifi_mgmr_channel_set(channel, 0);
                printf("[TIMER] Scan Target BSSID Beacon @ channel %d\r\n", channel);
            }
            aos_post_delayed_action(330, app_delayed_action, NULL);
        }
        break;
        case 3:
        /*airkiss is finished, wait for IP*/
        {
            aos_post_delayed_action(100, airkiss_confirm_cb, (void*)(uint32_t)airkiss_random);
        }
        break;
        default:
        {
            /*empty here*/
            //FIXME should we assert here?
            printf("[TIMER] Exiting with Fault\r\n");
        }
    }
}

static int sniffer_found = 0, sniffer_bssid_found = 0, sniffer_ds_found = 0;
static uint8_t sniffer_mac[6];
static uint32_t sniffer_counter = 0;
static uint32_t sniffer_last = 0;
static void sniffer_cb(void *env, uint8_t *pkt, int len)
{
    int ret;
    uint32_t now;

    now = xTaskGetTickCount();
    sniffer_counter++;
    if (((int32_t)now - (int32_t)sniffer_last) > 10000) {
        printf("\r\n   pkt %lu\r, now %lu, last %lu, pkt %lu\r\n", sniffer_counter, now, sniffer_last, sniffer_counter);
        sniffer_last = now;
        sniffer_counter = 0;
    }
    if (airkiss_is_ready && 0 == sniffer_found) {
        ret = airkiss_recv(&akcontex, pkt, len);
        switch (ret) {
            case AIRKISS_STATUS_CONTINUE:
            {
                if (sniffer_bssid_found && 0 == sniffer_ds_found) {
                    int pos;

                    if (0x80 == pkt[0] && 0x00 == pkt[1]) {
                        /*check BSSID in Beacon*/
                        if (0 == memcmp(sniffer_mac, pkt + 2 + 2 + 12, 6)) {
                            printf("[AK] Beacon Found for locked packet, tring to find DS tag\r\n");
                            pos = 36;//TAGGED element start @ 36 bytes offset
                            /*looking for DS tag*/
                            while (pos + 2 < len) {
                                if (3 == pkt[pos] && 1 == pkt[pos + 1]) {
                                    printf("[AK] DS is %u\r\n", pkt[pos + 2]);
                                    sniffer_ds_found = 1;
                                    ds_channel = pkt[pos + 2];
                                    break;
                                } else {
                                    pos += (pkt[pos + 1] + 2);
                                }
                            }
                            /*looking for */
                            pos = 36;//TAGGED element start @ 36 bytes offset
                            while (pos + 2 < len) {
                                if (61 == pkt[pos] && 22 == pkt[pos + 1]) {
                                    printf("[AK] found HT information, primary channel %u, secondary channel info is %u\r\n", pkt[pos + 2], pkt[pos + 3]);
                                    if (0x3 == (0x3 & pkt[pos + 3])) {
                                        printf("[AK] secondary channel is below primary channel\r\n");
                                        use_40Mhz = 1;
                                    } else if (0x1 == (0x3 & pkt[pos + 3])) {
                                        use_40Mhz = 2;
                                        printf("[AK] secondary channel is above primary channel\r\n");
                                    }
                                    break;
                                } else {
                                    pos += (pkt[pos + 1] + 2);
                                }
                            }
                        }
                    }
                }
            }
            break;
            case AIRKISS_STATUS_CHANNEL_LOCKED:
            {
                uint8_t flag;

                printf("\r\n[AK] Lock channel now %02X%02X\r\n", pkt[0], pkt[1]);//FIXME this is buggy because of timing
                flag = (pkt[1] & 0x03);//get DS filed
                switch (flag) {
                    case 1:
                    /*To DS*/
                    {
                        memcpy(sniffer_mac, pkt + 4, 6);
                        printf("[AK] MAC in ToDS %02X:%02X:%02X:%02X:%02X:%02X\r\n",
                                sniffer_mac[0],
                                sniffer_mac[1],
                                sniffer_mac[2],
                                sniffer_mac[3],
                                sniffer_mac[4],
                                sniffer_mac[5]
                        );
                        sniffer_bssid_found = 1;
                    }
                    break;
                    case 2:
                    /*From DS*/
                    {
                        memcpy(sniffer_mac, pkt + 10, 6);
                        printf("[AK] MAC in FromDS %02X:%02X:%02X:%02X:%02X:%02X\r\n",
                                sniffer_mac[0],
                                sniffer_mac[1],
                                sniffer_mac[2],
                                sniffer_mac[3],
                                sniffer_mac[4],
                                sniffer_mac[5]
                        );
                        sniffer_bssid_found = 1;
                    }
                    break;
                    default:
                    {
                        printf("[AK] MAC in FromToDS is NOT supportedr\r\n");
                    }
                }
                airkiss_is_ready = 2;
            }
            break;
            case AIRKISS_STATUS_COMPLETE:
            {
                printf("[AK] Found key!\r\n");
                airkiss_get_result(&akcontex, &akresult);

                printf("[AK] ssid is %s\r\n", akresult.ssid);
                printf("[AK] pwd is %s\r\n", akresult.pwd);
                printf("[AK] ssid len is %d\r\n", akresult.ssid_length);
                printf("[AK] pwd len is %d\r\n", akresult.pwd_length);
                printf("[AK] random is %d\r\n", akresult.random);
                sniffer_found = 1;
                airkiss_is_ready = 3;
                /*publish this event*/
                aos_post_event(TYPE_AIRKISS_DONE, 0, (long unsigned int)&akresult);
            }
            break;
            default:
            {
                /*empty here*/
            }
        }
    }
}

static void airkiss_entry(void *pvParameters)
{
    int ret;
    const airkiss_config_t akconf = {   
        (airkiss_memset_fn)&memset,     
        (airkiss_memcpy_fn)&memcpy,     
        (airkiss_memcmp_fn)&memcmp,     
        (airkiss_printf_fn)&printf 
    };

    memset(&akcontex, 0, sizeof(akcontex));
    memset(&akresult, 0, sizeof(akcontex));
    airkiss_is_ready = 0;
    ds_channel = 0;
    airkiss_random = 0;
    airkiss_finished = 0;
    sniffer_found = 0;
    sniffer_bssid_found = 0;
    sniffer_ds_found = 0;
    memset(sniffer_mac, 0, sizeof(sniffer_mac));
    sniffer_counter = 0;
    sniffer_last = 0;


    printf("Starting Airkiss Demo...");
    ret = airkiss_init(&akcontex, &akconf);
    if (ret) {
        printf("Init Failed\r\n");
    } else {
        printf("Done\r\n");
        airkiss_is_ready = 1;
    }
    airkiss_change_channel(&akcontex);
    wifi_mgmr_sniffer_register(NULL, sniffer_cb);
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(4000));
        if (1 == airkiss_finished) {
            printf("Exiting Airkis thread now...\r\n");
            break;
        }
    }
    aos_unregister_event_filter(TYPE_AIRKISS_DONE, event_cb_airkss_done, NULL);
    /*aos thread here, just return from entry*/
}

static void airkiss_cmd(char *buf, int len, int argc, char **argv)
{
    wifi_mgmr_sniffer_enable();

    aos_register_event_filter(TYPE_AIRKISS_DONE, event_cb_airkss_done, NULL);
    aos_post_delayed_action(100, app_delayed_action, NULL);

    aos_task_new("airkiss", airkiss_entry, NULL, 2048);

}

static void wifi_rc_fixed_enable(char *buf, int len, int argc, char **argv)
{
    uint8_t mcs = 0;
    uint8_t gi = 0;
    uint16_t rc = 0x1000; //format mode is HT_MF only

    if (argc != 3) {
        printf("rc_fix_en [MCS] [GI]");
        return;
    }
    mcs = atoi(argv[1]);
    gi = atoi(argv[2]);

    rc |= gi << 9 | mcs;

    wifi_mgmr_rate_config(rc);
}

static void wifi_rc_fixed_disable(char *buf, int len, int argc, char **argv)
{
    uint16_t rc = 0xFFFF;

    wifi_mgmr_rate_config(rc);
}

static void wifi_capcode_update(char *buf, int len, int argc, char **argv)
{
    uint8_t cap_in, cap_out;

    if (argc == 1) {
        bl60x_fw_xtal_capcode_get(&cap_in, &cap_out);
        printf("[RF] [CAP] Dump capcode in:out %u:%u\r\n", cap_in, cap_out);
        return;
    }
    if (argc != 3) {
        printf("%s [capcode_in] [capcode_out]\r\n", argv[0]);
        return;
    }

    bl60x_fw_xtal_capcode_get(&cap_in, &cap_out);
    printf("[RF] [CAP] Dump capcode in:out %u:%u\r\n", cap_in, cap_out);
    cap_in = atoi(argv[1]);
    cap_out = atoi(argv[2]);
    printf("[RF] [CAP] Updating capcode to in:out %u:%u\r\n", cap_in, cap_out);
    bl60x_fw_xtal_capcode_update(cap_in, cap_out);
    bl60x_fw_xtal_capcode_get(&cap_in, &cap_out);
    printf("[RF] [CAP] Dump Again capcode in:out %u:%u\r\n", cap_in, cap_out);
}

static void cmd_wifi_ap_start(char *buf, int len, int argc, char **argv)
{
    uint8_t mac[6];
    char ssid_name[32];
    wifi_interface_t wifi_interface;

    memset(mac, 0, sizeof(mac));
    bl_efuse_read_mac(mac);
    memset(ssid_name, 0, sizeof(ssid_name));
    snprintf(ssid_name, sizeof(ssid_name), "BL60X_uAP_%02X%02X%02X", mac[3], mac[4], mac[5]);
    ssid_name[sizeof(ssid_name) - 1] = '\0';

    wifi_interface = wifi_mgmr_ap_enable();
    if (1 == argc) {
        /*no password when only one param*/
        wifi_mgmr_ap_start(wifi_interface, ssid_name, 0, NULL, 1);
    } else {
        /*hardcode password*/
        wifi_mgmr_ap_start(wifi_interface, ssid_name, 0, "bouffalolab", 1);
    }
}

static void cmd_wifi_ap_stop(char *buf, int len, int argc, char **argv)
{
    wifi_mgmr_ap_stop(NULL);
    printf("--->>> cmd_wifi_ap_stop\r\n");
}

static void cmd_wifi_dump(char *buf, int len, int argc, char **argv)
{
    if (argc > 1) {
        puts("[CLI] Dump statistic use forced mode\r\n");
        taskENTER_CRITICAL();
        bl60x_fw_dump_statistic(1);
        taskEXIT_CRITICAL();
    } else {
        puts("[CLI] Dump statistic use normal mode\r\n");
        taskENTER_CRITICAL();
        bl60x_fw_dump_statistic(0);
        taskEXIT_CRITICAL();
    }
}

static void cmd_wifi_mib(char *buf, int len, int argc, char **argv)
{
void hal_mib_dump();
    hal_mib_dump();
    utils_hexdump(argv[0], 30);
}
// STATIC_CLI_CMD_ATTRIBUTE makes this(these) command(s) static
const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
        { "rf_dump", "rf dump", cmd_rf_dump},
        { "wifi_scan", "wifi scan", wifi_scan_cmd},
        { "wifi_mon", "wifi monitor", wifi_mon_cmd},
        { "wifi_raw_send", "wifi raw send test", cmd_wifi_raw_send},
        { "wifi_sta_disconnect", "wifi station disconnect", wifi_disconnect_cmd},
        { "wifi_sta_connect", "wifi station connect", wifi_connect_cmd},
        { "airkiss", "airkiss", airkiss_cmd},
        { "rc_fix_en", "wifi rate control fixed rate enable", wifi_rc_fixed_enable},
        { "rc_fix_dis", "wifi rate control fixed rate diable", wifi_rc_fixed_disable},
        { "wifi_capcode", "capcode utils\r\n wifi_capcode [cap_in] [cap_out]", wifi_capcode_update},
        { "wifi_ap_start", "start Ap mode", cmd_wifi_ap_start},
        { "wifi_ap_stop", "start Ap mode", cmd_wifi_ap_stop},
        { "wifi_dump", "dump fw statistic", cmd_wifi_dump},
        { "wifi_mib", "dump mib statistic", cmd_wifi_mib},
};                                                                                   

int helper_wifi_cli_init(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user)/sizeof(cmds_user[0]));          
    return 0;
}
