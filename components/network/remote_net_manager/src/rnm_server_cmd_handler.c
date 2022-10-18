#include <rnm_server.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <FreeRTOS.h>
#include <task.h>
#include <hal_sys.h>
#include <bl_os_private.h>
#include <bl_wifi.h>
#include <wifi_mgmr_ext.h>

#include <rnm_ota.h>

#define CMD_HANDLER_FLAG_ACK (0u << 0)
#define CMD_HANDLER_FLAG_NO_ACK (1u << 0)

typedef struct {
    uint16_t status;
    uint16_t flag;
} cmd_handler_ret_t;

typedef cmd_handler_ret_t chr_t;

struct cmd_handler {
    chr_t (*handler)(rnms_t *env, rnm_msg_t *cmd);
};

#define CMD_HANDLER_RET_OK_ACK \
    (const chr_t) { STATUS_OK, CMD_HANDLER_FLAG_ACK }
// CMD is acked by handler. Do not ack in handler caller.
#define CMD_HANDLER_RET_NO_ACK \
    (const chr_t) { STATUS_OK, CMD_HANDLER_FLAG_NO_ACK }
#define CMD_HANDLER_RET_ERR_ACK(e) \
    (const chr_t) { e, CMD_HANDLER_FLAG_ACK }

#define RNM_MSG_FILL_COMMON(ack, msg)             \
    (ack).hdr.cmd = (msg)->cmd.cmd;               \
    (ack).hdr.flags = RNM_MSG_FLAG_ACK;           \
    (ack).hdr.status = STATUS_OK;                 \
    (ack).hdr.session_id = (msg)->cmd.session_id; \
    (ack).hdr.msg_id = ++rnm->last_msg_id;

#define CMD_COMMON_CHECK(cmd, type)                               \
    {                                                             \
        if (!cmd->data || cmd->data_len != sizeof(type)) {        \
            rnm_err("msg format error\r\n");                      \
            return CMD_HANDLER_RET_ERR_ACK(STATUS_INVALID_INPUT); \
        }                                                         \
    }

static inline void inc_stat_scratch_ctr(rnms_t *rnm, int id)
{
    ++rnm->statistic.scratch_counter[id];
}

void rnms_notify_sta_ip_addr(rnms_t *rnm)
{
    rnm_sta_ip_update_ind_msg_t msg;
    uint32_t addr, mask, gw, dns;

    memset(&msg, 0, sizeof(msg));
    msg.hdr.cmd = BF1B_CMD_STA_IP_UPDATE_IND;
    msg.hdr.flags = RNM_MSG_FLAG_ASYNC;
    msg.hdr.msg_id = ++rnm->last_msg_id;

    wifi_sta_ip4_addr_get(&addr, &mask, &gw, &dns);
    memcpy(msg.ip4_addr, &addr, 4);
    memcpy(msg.ip4_mask, &mask, 4);
    memcpy(msg.ip4_gw, &gw, 4);
    memcpy(msg.ip4_dns1, &dns, 4);

    rnms_msg_output(rnm, &msg, sizeof(msg));
}

static void stop_ap()
{
#ifdef CFG_BL616
    wifi_mgmr_ap_stop();
#else
    wifi_mgmr_ap_stop(NULL);
#endif
}

static void stop_sta()
{
#ifdef CFG_BL616
    wifi_sta_disconnect();
#else
    int state1 = WIFI_STATE_UNKNOWN;
    int state2 = WIFI_STATE_UNKNOWN;
    int tries = 100;
    bool do_disconnect = false;

    wifi_mgmr_sta_autoconnect_disable();
    wifi_mgmr_detailed_state_get(&state1, &state2);

    switch (state1) {
    case WIFI_STATE_WITH_AP_IDLE:
        // fallthrough
    case WIFI_STATE_IDLE:
        break;
    case WIFI_STATE_WITH_AP_CONNECTING:
        // fallthrough
    case WIFI_STATE_CONNECTING:
        while (tries > 0) {
            vTaskDelay(pdMS_TO_TICKS(100));
            wifi_mgmr_detailed_state_get(&state1, &state2);
            if (state1 != WIFI_STATE_CONNECTING) {
                break;
            }
            tries--;
        }
        do_disconnect = true;
        break;
    case WIFI_STATE_WITH_AP_CONNECTED_IP_GETTING:
        // fallthrough
    case WIFI_STATE_CONNECTED_IP_GETTING:
        // fallthrough
    case WIFI_STATE_WITH_AP_CONNECTED_IP_GOT:
        // fallthrough
    case WIFI_STATE_CONNECTED_IP_GOT:
        // fallthrough
    case WIFI_STATE_WITH_AP_DISCONNECT:
        // fallthrough
    case WIFI_STATE_DISCONNECT:
        do_disconnect = true;
        break;
    default:
        do_disconnect = false;
        break;
    }

    if (do_disconnect) {
        wifi_mgmr_sta_disconnect();
        vTaskDelay(1000);
        wifi_mgmr_sta_disable(NULL);
    }
#endif
}

static chr_t handle_reset(rnms_t *rnm, rnm_msg_t *cmd)
{
    rnm_debug("handle reset\r\n");
    switch (rnm->mode) {
    case RNM_WIFI_MODE_AP:
        stop_ap();
        break;
    case RNM_WIFI_MODE_STA:
        stop_sta();
        break;
    case RNM_WIFI_MODE_AP_STA:
        stop_ap();
        stop_sta();
        break;
    case RNM_WIFI_MODE_SNIFFER:
#ifdef CFG_BL616
        // unimplemented
#else
        wifi_mgmr_sniffer_disable();
        wifi_mgmr_sniffer_unregister(NULL);
#endif
        break;
    default:
        break;
    }
    rnm->mode = RNM_WIFI_MODE_NONE;

    return CMD_HANDLER_RET_OK_ACK;
}

static chr_t handle_hello(rnms_t *rnm, rnm_msg_t *cmd)
{
    rnm_debug("handle hello\r\n");

    if (rnm->ready_cb) {
        rnm->ready_cb(rnm->ready_cb_arg);
    }
    return CMD_HANDLER_RET_OK_ACK;
}

static chr_t handle_ping(rnms_t *rnm, rnm_msg_t *cmd)
{
    rnm_debug("handle ping\r\n");
    return CMD_HANDLER_RET_OK_ACK;
}

static chr_t handle_get_mac_addr(rnms_t *rnm, rnm_msg_t *cmd)
{
    rnm_debug("handle get_mac_addr\r\n");
    rnm_mac_addr_ind_msg_t msg;

    RNM_MSG_FILL_COMMON(msg, cmd);
#ifdef CFG_BL616
    // FIXME
    wifi_mgmr_sta_mac_get(msg.mac);
#else
    bl_wifi_mac_addr_get(msg.mac);
#endif
    rnm_debug("Responding with MAC " MAC_ADDR_FMT "\r\n", ARR_ELE_LIST_6(msg.mac));
    rnms_msg_output(rnm, &msg, sizeof(msg));
    return CMD_HANDLER_RET_NO_ACK;
}

#ifndef CFG_BL616
static uint8_t auth_to_rnm(uint8_t auth)
{
    uint8_t ret;
    switch (auth) {
    default:
        ret = RNM_WIFI_AUTH_UNKNOWN;
        break;
    case WM_WIFI_AUTH_OPEN:
        ret = RNM_WIFI_AUTH_OPEN;
        break;
    case WM_WIFI_AUTH_WEP:
        ret = RNM_WIFI_AUTH_WEP;
        break;
    case WM_WIFI_AUTH_WPA_PSK:
        ret = RNM_WIFI_AUTH_WPA_PSK;
        break;
    case WM_WIFI_AUTH_WPA2_PSK:
        ret = RNM_WIFI_AUTH_WPA2_PSK;
        break;
    case WM_WIFI_AUTH_WPA_WPA2_PSK:
        ret = RNM_WIFI_AUTH_WPA_WPA2_PSK;
        break;
    case WM_WIFI_AUTH_WPA_ENTERPRISE:
        ret = RNM_WIFI_AUTH_WPA_ENTERPRISE;
        break;
    case WM_WIFI_AUTH_WPA3_SAE:
        ret = RNM_WIFI_AUTH_WPA3_SAE;
        break;
    case WM_WIFI_AUTH_WPA2_PSK_WPA3_SAE:
        ret = RNM_WIFI_AUTH_WPA2_PSK_WPA3_SAE;
        break;
    }
    return ret;
}

static uint8_t cipher_to_rnm(uint8_t cipher)
{
    uint8_t ret;
    switch (cipher) {
    default:
        ret = RNM_WIFI_CIPHER_UNKNOWN;
        break;
    case WM_WIFI_CIPHER_NONE:
        ret = RNM_WIFI_CIPHER_NONE;
        break;
    case WM_WIFI_CIPHER_WEP:
        ret = RNM_WIFI_CIPHER_WEP;
        break;
    case WM_WIFI_CIPHER_AES:
        ret = RNM_WIFI_CIPHER_AES;
        break;
    case WM_WIFI_CIPHER_TKIP:
        ret = RNM_WIFI_CIPHER_TKIP;
        break;
    case WM_WIFI_CIPHER_TKIP_AES:
        ret = RNM_WIFI_CIPHER_TKIP_AES;
        break;
    }
    return ret;
}
#endif

static chr_t handle_scan(rnms_t *rnm, rnm_msg_t *cmd)
{
#ifdef CFG_BL616
    return CMD_HANDLER_RET_OK_ACK;
#else
    int i;
    int ind_msg_len;
    uint32_t cnt = 0;
    wifi_mgmr_ap_item_t *ap_ary = NULL;
    int ret;
    rnm_scan_ind_msg_t *ind_msg;
    int wifi_state, wifi_state_d;

    rnm_debug("handle scan\r\n");

    wifi_mgmr_detailed_state_get(&wifi_state, &wifi_state_d);
    if (wifi_state != WIFI_STATE_IDLE) {
        return CMD_HANDLER_RET_ERR_ACK(STATUS_INVALID_MODE);
    }

    ret = wifi_mgmr_all_ap_scan(&ap_ary, &cnt);
    if (ret != 0) {
        rnm_err("wifi all ap scan error %d\r\n", ret);
        return CMD_HANDLER_RET_ERR_ACK(STATUS_NOMEM);
    }

#ifdef CFG_SDIOWIFI
    // mitigate issue that message is too long for SDIO
    {
        size_t cnt_limit = (2000 - sizeof(rnm_scan_ind_msg_t)) / sizeof(struct bf1b_wifi_scan_record);
        if (cnt > cnt_limit) {
            cnt = cnt_limit;
        }
    }
#endif
    ind_msg_len = sizeof(rnm_scan_ind_msg_t) + cnt * sizeof(struct bf1b_wifi_scan_record);
    ind_msg = (rnm_scan_ind_msg_t *)rnm_malloc(ind_msg_len);
    if (ind_msg == NULL) {
        rnm_err("malloc failed\r\n");
        bl_os_free(ap_ary);
        inc_stat_scratch_ctr(rnm, RNMS_STAT_ERR_OUTPUT_NOMEM);
        return CMD_HANDLER_RET_ERR_ACK(STATUS_NOMEM);
    }

    RNM_MSG_FILL_COMMON(*ind_msg, cmd);
    ind_msg->num = cnt;
    for (i = 0; i < cnt; i++) {
        wifi_mgmr_ap_item_t *si = &ap_ary[i];
        struct bf1b_wifi_scan_record *di = &ind_msg->records[i];
        memset(di, 0, sizeof(*di));
        memcpy(di->bssid, si->bssid, sizeof(di->bssid));
        memcpy(di->ssid, si->ssid, sizeof(di->ssid) - 1);
        di->channel = si->channel;
        di->rssi = si->rssi;
        di->auth_mode = auth_to_rnm(wifi_mgmr_bcnind_auth_to_ext(si->auth));
        di->cipher = cipher_to_rnm(wifi_mgmr_bcnind_cipher_to_ext(si->cipher));
    }

    bl_os_free(ap_ary);
    rnms_msg_output(rnm, ind_msg, ind_msg_len);
    rnm_free(ind_msg);

    return CMD_HANDLER_RET_NO_ACK;
#endif
}

static chr_t handle_sta_connect(rnms_t *rnm, rnm_msg_t *cmd)
{
    rnm_debug("handle sta_connect\r\n");
    bool use_dhcp = false;
#ifndef CFG_BL616
    wifi_interface_t wifi_interface;
#endif
    rnm_sta_connect_msg_t *ccmd;
    void *password;

    if (!(rnm->mode == RNM_WIFI_MODE_NONE || rnm->mode == RNM_WIFI_MODE_STA)) {
        rnm_err("mode incorrect, ignore connect ap\r\n");
        return CMD_HANDLER_RET_ERR_ACK(STATUS_INVALID_MODE);
    }
    CMD_COMMON_CHECK(cmd, rnm_sta_connect_msg_t);

    ccmd = (rnm_sta_connect_msg_t *)cmd->data;
    if (strlen((char *)ccmd->ssid) == 0) {
        rnm_info("SSID NULL\r\n");
        return CMD_HANDLER_RET_ERR_ACK(STATUS_INVALID_INPUT);
    }
    rnm_debug("cur mode:%d\r\n", rnm->mode);
    if (rnm->mode == RNM_WIFI_MODE_NONE) {
        rnm->mode = RNM_WIFI_MODE_STA;
    } else if (rnm->mode == RNM_WIFI_MODE_AP) {
        rnm->mode = RNM_WIFI_MODE_AP_STA;
    } else {
        // STA->STA, AP_STA->AP_STA
        stop_sta();
    }
    rnm_debug("changed to mode %d\r\n", rnm->mode);

    password = ccmd->password;
    if (ccmd->password[0] == 0) {
        password = NULL;
    }
#ifdef DHCP_IN_EMB
    use_dhcp = true;
#endif

#ifdef CFG_BL616
    wifi_sta_connect((char *)ccmd->ssid, (char *)password, NULL, NULL, 0, 0, use_dhcp);
#else
    wifi_mgmr_sta_autoconnect_enable();
    wifi_interface = wifi_mgmr_sta_enable();
    wifi_mgmr_sta_connect_mid(wifi_interface, (char *)ccmd->ssid, (char *)password, NULL, NULL, 0, 0, use_dhcp, 0);
#endif

    return CMD_HANDLER_RET_OK_ACK;
}

static chr_t handle_sta_disconnect(rnms_t *rnm, rnm_msg_t *cmd)
{
    rnm_debug("handle sta_disconnect\r\n");

    stop_sta();

    rnm_debug("cur mode:%d\r\n", rnm->mode);
    if (rnm->mode == RNM_WIFI_MODE_STA) {
        rnm->mode = RNM_WIFI_MODE_NONE;
    } else if (rnm->mode == RNM_WIFI_MODE_AP_STA) {
        rnm->mode = RNM_WIFI_MODE_AP;
    } else {
        // nothing
    }
    return CMD_HANDLER_RET_OK_ACK;
}

static chr_t handle_sta_set_auto_reconnect(rnms_t *rnm, rnm_msg_t *cmd)
{
    rnm_debug("handle sta_set_auto_reconnect\r\n");
#ifndef CFG_BL616
    rnm_sta_set_auto_reconnect_msg_t *ccmd;
#endif

    if (rnm->mode != RNM_WIFI_MODE_STA) {
        rnm_err("mode incorrect, ignore set auto reconnect\r\n");
        return CMD_HANDLER_RET_ERR_ACK(STATUS_INVALID_MODE);
    }

    CMD_COMMON_CHECK(cmd, rnm_sta_set_auto_reconnect_msg_t);

#ifdef CFG_BL616
#else
    ccmd = (rnm_sta_set_auto_reconnect_msg_t *)cmd->data;

    if (ccmd->en) {
        rnm_debug("Enable sta autoconnect\r\n");
        wifi_mgmr_sta_autoconnect_enable();
    } else {
        rnm_debug("Disable sta autoconnect\r\n");
        wifi_mgmr_sta_autoconnect_disable();
    }
#endif
    return CMD_HANDLER_RET_OK_ACK;
}

#ifdef CFG_BL616
#else
// XXX not complete
static void fill_sta_status(struct bf1b_wifi_ap_record *record)
{
    int value_int;

    /* Link Status*/
    if (0 == wifi_mgmr_state_get(&value_int)) {
        if (WIFI_STATE_CONNECTED_IP_GOT == value_int ||
            WIFI_STATE_CONNECTED_IP_GETTING == value_int) {
            record->link_status = BF1B_WIFI_LINK_STATUS_UP;
        } else {
            record->link_status = BF1B_WIFI_LINK_STATUS_DOWN;
        }
    } else {
        record->link_status = BF1B_WIFI_LINK_STATUS_UNKNOWN;
    }

    /*bssid*/
    // uint8_t bssid[6];

    /*ssid*/
    // uint8_t ssid[32 + 1];

    /*channel*/
    if (0 == wifi_mgmr_channel_get(&value_int)) {
        record->channel = value_int;
    } else {
        record->channel = -1;
    }

    /*rssi*/
    if (0 == wifi_mgmr_rssi_get(&value_int)) {
        record->rssi = value_int;
    } else {
        record->rssi = -127;
    }

    /*auth_mode*/
    record->auth_mode = RNM_WIFI_AUTH_UNKNOWN;
    record->cipher = RNM_WIFI_CIPHER_NONE;
}
#endif

static chr_t handle_sta_get_link_status(rnms_t *rnm, rnm_msg_t *cmd)
{
    rnm_debug("handle sta_get_link_status\r\n");
    rnm_sta_link_status_ind_msg_t rsp;

    memset(&rsp, 0, sizeof(rsp));
    RNM_MSG_FILL_COMMON(rsp, cmd);
#ifdef CFG_BL616
    // unimplemented
#else
    fill_sta_status(&rsp.record);
#endif

    rnms_msg_output(rnm, &rsp, sizeof(rsp));
    return CMD_HANDLER_RET_NO_ACK;
}

static chr_t handle_ap_start(rnms_t *rnm, rnm_msg_t *cmd)
{
    rnm_debug("handle ap_start\r\n");
    rnm_ap_start_msg_t *ccmd;
    bool use_dhcpd = false;
#ifdef CFG_BL616
    wifi_mgmr_ap_params_t config = {};
#else
    wifi_interface_t wifi_interface;
#endif
    int channel;
    char *passwd;

    CMD_COMMON_CHECK(cmd, rnm_ap_start_msg_t);
    if (!(rnm->mode == RNM_WIFI_MODE_NONE || rnm->mode == RNM_WIFI_MODE_STA)) {
        rnm_err("mode incorrect, ignore start ap\r\n");
        return CMD_HANDLER_RET_ERR_ACK(STATUS_INVALID_MODE);
    }

    ccmd = (rnm_ap_start_msg_t *)cmd->data;

    if (strlen((char *)ccmd->ssid) == 0) {
        rnm_err("SSID null\r\n");
        return CMD_HANDLER_RET_ERR_ACK(STATUS_INVALID_INPUT);
    }

    channel = ccmd->channel;
    if (ccmd->is_open) {
#ifdef CFG_BL616
        passwd = "";
#else
        passwd = NULL;
#endif
    } else {
        passwd = (char *)ccmd->password;
    }
#ifdef DHCP_IN_EMB
    use_dhcpd = true;
#endif
    rnm_debug("Starting AP with SSID %s, channel %d, password %s\r\n",
              ccmd->ssid,
              channel,
              passwd ? passwd : "[nil]");
    if (rnm->mode == RNM_WIFI_MODE_NONE) {
        rnm->mode = RNM_WIFI_MODE_AP;
    } else {
        rnm->mode = RNM_WIFI_MODE_AP_STA;
    }
#ifdef CFG_BL616
    config.ssid = (char *)ccmd->ssid;
    config.key = passwd;
    config.chan = channel;
    config.use_dhcpd = use_dhcpd;
    wifi_mgmr_ap_start(&config);
#else
    wifi_interface = wifi_mgmr_ap_enable();
    wifi_mgmr_ap_start_adv(wifi_interface, (char *)ccmd->ssid, 0, passwd, channel, use_dhcpd);
#endif
    return CMD_HANDLER_RET_OK_ACK;
}

static chr_t handle_ap_stop(rnms_t *rnm, rnm_msg_t *cmd)
{
    rnm_debug("handle stop ap\r\n");
#ifdef CFG_BL616
    wifi_mgmr_ap_stop();
#else
    wifi_mgmr_ap_stop(NULL);
#endif

    rnm_debug("cur mode:%d\r\n", rnm->mode);
    if (rnm->mode == RNM_WIFI_MODE_AP) {
        rnm->mode = RNM_WIFI_MODE_NONE;
    } else if (rnm->mode == RNM_WIFI_MODE_AP_STA) {
        rnm->mode = RNM_WIFI_MODE_STA;
    } else {
        // nothing
    }

    return CMD_HANDLER_RET_OK_ACK;
}

static chr_t handle_ap_get_sta_list(rnms_t *rnm, rnm_msg_t *cmd)
{
    rnm_debug("handle ap_get_sta_list\r\n");
#ifdef CFG_BL616
    // unimplemented
    return CMD_HANDLER_RET_ERR_ACK(STATUS_NOT_IMPLEMENTED);
#else
    uint8_t sta_cnt = 0, length;
    struct wifi_sta_basic_info sta_info;
    rnm_ap_sta_list_ind_msg_t *rsp = NULL;
    int filtered_sta_cnt = 0;

    wifi_mgmr_ap_sta_cnt_get(&sta_cnt);
    length = sizeof(*rsp) + sta_cnt * sizeof(struct wifi_sta_info);
    rsp = rnm_malloc(length);

    if (!rsp) {
        inc_stat_scratch_ctr(rnm, RNMS_STAT_ERR_OUTPUT_NOMEM);
        return CMD_HANDLER_RET_ERR_ACK(STATUS_NOMEM);
    }

    memset(rsp, 0, length);
    RNM_MSG_FILL_COMMON(*rsp, cmd);

    for (int i = 0; i < sta_cnt; i++) {
        wifi_mgmr_ap_sta_info_get(&sta_info, i);
        if (!sta_info.is_used) {
            continue;
        }
        rnm_debug("idx %i MAC " MAC_ADDR_FMT "\r\n",
                  filtered_sta_cnt,
                  ARR_ELE_LIST_6(sta_info.sta_mac));
        memcpy(rsp->sta[filtered_sta_cnt++].mac, sta_info.sta_mac, 6);
    }

    rnm_debug("sta_cnt %d vs filtered_sta_cnt %d\r\n", sta_cnt, filtered_sta_cnt);
    rsp->num = filtered_sta_cnt;
    length -= (sta_cnt - filtered_sta_cnt) * sizeof(struct wifi_sta_info);
    rnms_msg_output(rnm, rsp, length);
    rnm_free(rsp);
    return CMD_HANDLER_RET_NO_ACK;
#endif
}

#ifdef CFG_BL616
#else
static void sniffer_cb(void *env, void *pkt_wrap, bl_rx_info_t *info)
{
    rnms_t *rnm = env;
    if (!(rnm->mode == RNM_WIFI_MODE_SNIFFER)) {
        return;
    }
    rnm->output_fn(rnm->output_fn_env, RNM_OUT_SNIFFER_FRAME, pkt_wrap, 0);
}
#endif

static chr_t handle_monitor_start(rnms_t *rnm, rnm_msg_t *cmd)
{
    rnm_debug("handle monitor_start\r\n");
#ifdef CFG_BL616
    return CMD_HANDLER_RET_ERR_ACK(STATUS_NOT_IMPLEMENTED);
#else
    if (!(rnm->mode == RNM_WIFI_MODE_NONE)) {
        rnm_err("mode incorrect, ignore start monitor\r\n");
        return CMD_HANDLER_RET_ERR_ACK(STATUS_INVALID_MODE);
    }
    rnm->mode = RNM_WIFI_MODE_SNIFFER;
    wifi_mgmr_sniffer_enable();
    wifi_mgmr_sniffer_register_adv(rnm, sniffer_cb);
    return CMD_HANDLER_RET_OK_ACK;
#endif
}

static chr_t handle_monitor_stop(rnms_t *rnm, rnm_msg_t *cmd)
{
    rnm_debug("handle monitor_stop\r\n");
#ifdef CFG_BL616
    return CMD_HANDLER_RET_ERR_ACK(STATUS_NOT_IMPLEMENTED);
#else
    if (!(rnm->mode == RNM_WIFI_MODE_SNIFFER)) {
        rnm_err("mode incorrect, ignore stop monitor\r\n");
        return CMD_HANDLER_RET_ERR_ACK(STATUS_INVALID_MODE);
    }
    rnm->mode = RNM_WIFI_MODE_NONE;
    wifi_mgmr_sniffer_disable();
    wifi_mgmr_sniffer_unregister(NULL);
    return CMD_HANDLER_RET_OK_ACK;
#endif
}

static chr_t handle_montior_set_channel(rnms_t *rnm, rnm_msg_t *cmd)
{
    rnm_debug("handle montior_set_channel\r\n");
#ifdef CFG_BL616
    return CMD_HANDLER_RET_ERR_ACK(STATUS_NOT_IMPLEMENTED);
#else
    rnm_monitor_set_channel_msg_t *ccmd;

    CMD_COMMON_CHECK(cmd, rnm_monitor_set_channel_msg_t);

    if (!(rnm->mode == RNM_WIFI_MODE_SNIFFER)) {
        rnm_err("mode incorrect, ignore set channel\r\n");
        return CMD_HANDLER_RET_ERR_ACK(STATUS_INVALID_MODE);
    }
    ccmd = (rnm_monitor_set_channel_msg_t *)cmd->data;
    uint8_t chn = ccmd->channel;
    if (chn >= 1 && chn <= 14) {
        wifi_mgmr_channel_set(ccmd->channel, 0);
    }
    return CMD_HANDLER_RET_OK_ACK;
#endif
}

static chr_t handle_montior_get_channel(rnms_t *rnm, rnm_msg_t *cmd)
{
    rnm_debug("handle monitor_get_channel\r\n");
#ifdef CFG_BL616
    return CMD_HANDLER_RET_ERR_ACK(STATUS_NOT_IMPLEMENTED);
#else
    int chn;
    rnm_monitor_channel_ind_msg_t msg;

    wifi_mgmr_channel_get(&chn);
    rnm_debug("Current channel: %d\r\n", chn);

    RNM_MSG_FILL_COMMON(msg, cmd);
    msg.channel = chn;

    rnms_msg_output(rnm, &msg, sizeof(msg));
    return CMD_HANDLER_RET_NO_ACK;
#endif
}

static chr_t handle_set_lpm_mode(rnms_t *rnm, rnm_msg_t *cmd)
{
#ifdef CFG_BL616
    return CMD_HANDLER_RET_ERR_ACK(STATUS_NOT_IMPLEMENTED);
#else
    rnm_set_lpm_mode_msg_t *ccmd;
    rnm_debug("handle set_lpm_mode\r\n");
    if (!(rnm->mode == RNM_WIFI_MODE_STA)) {
        rnm_debug("mode incorrect, set lpm mode\r\n");
        return CMD_HANDLER_RET_ERR_ACK(STATUS_INVALID_MODE);
    }

    CMD_COMMON_CHECK(cmd, rnm_set_lpm_mode_msg_t);

    ccmd = (rnm_set_lpm_mode_msg_t *)cmd->data;
    // XXX not implemented
    (void)ccmd->en;

    return CMD_HANDLER_RET_ERR_ACK(STATUS_NOT_IMPLEMENTED);
#endif
}

static chr_t handle_get_dev_version(rnms_t *rnm, rnm_msg_t *cmd)
{
    rnm_dev_version_ind_msg_t msg;

    RNM_MSG_FILL_COMMON(msg, cmd);
    msg.version.version_num = RNM_VERSION;

    rnms_msg_output(rnm, &msg, sizeof(msg));
    return CMD_HANDLER_RET_NO_ACK;
}

static chr_t handle_ota(rnms_t *rnm, rnm_msg_t *cmd)
{
    rnms_handle_ota(rnm, cmd);
    return CMD_HANDLER_RET_NO_ACK;
}

static chr_t handle_reboot(rnms_t *rnm, rnm_msg_t *cmd)
{
    hal_reboot();
    return CMD_HANDLER_RET_OK_ACK;
}

// clang-format off
static const struct cmd_handler cmd_handler_table[BF1B_CMD_MAX] = {
    [BF1B_CMD_REBOOT]       = {handle_reboot},
    [BF1B_CMD_RESET]        = {handle_reset},
    [BF1B_CMD_HELLO]        = {handle_hello},
    [BF1B_CMD_PING]         = {handle_ping},
    [BF1B_CMD_GET_MAC_ADDR] = {handle_get_mac_addr},
    [BF1B_CMD_SCAN]         = {handle_scan},
    // STA
    [BF1B_CMD_STA_CONNECT]            = {handle_sta_connect},
    [BF1B_CMD_STA_DISCONNECT]         = {handle_sta_disconnect},
    [BF1B_CMD_STA_SET_AUTO_RECONNECT] = {handle_sta_set_auto_reconnect},
    [BF1B_CMD_STA_GET_LINK_STATUS]    = {handle_sta_get_link_status},
    // AP
    [BF1B_CMD_AP_START]        = {handle_ap_start},
    [BF1B_CMD_AP_STOP]         = {handle_ap_stop},
    [BF1B_CMD_AP_GET_STA_LIST] = {handle_ap_get_sta_list},
    // Monitor
    [BF1B_CMD_MONITOR_START]       = {handle_monitor_start},
    [BF1B_CMD_MONITOR_STOP]        = {handle_monitor_stop},
    [BF1B_CMD_MONITOR_SET_CHANNEL] = {handle_montior_set_channel},
    [BF1B_CMD_MONITOR_GET_CHANNEL] = {handle_montior_get_channel},

    [BF1B_CMD_SET_LPM_MODE] = {handle_set_lpm_mode},

    [BF1B_CMD_GET_DEV_VERSION] = {handle_get_dev_version},
    [BF1B_CMD_OTA]             = {handle_ota},
};
// clang-format on

void rnms_msg_process(rnms_t *rnm, rnm_msg_t *msg)
{
    uint16_t cmd_id = msg->cmd.cmd;
    chr_t ret;
    rnm_ack_msg_t ack;

    if (!(msg->cmd.cmd < BF1B_CMD_MAX)) {
        rnm_err("Unknown cmd %u!\r\n", msg->cmd.cmd);
        inc_stat_scratch_ctr(rnm, RNMS_STAT_ERR_INVALID_CMD);
        goto free;
    }

    if (msg->cmd.flags & RNM_MSG_FLAG_TRANSPARENT) {
        rnm_base_msg_t *msg_to_send = &msg->cmd;
        size_t msg_len = sizeof(*msg_to_send);
        if (msg->data) {
            msg_to_send = (rnm_base_msg_t *)msg->data;
            msg_len = msg->data_len;
        }
        msg_to_send->flags &= ~RNM_MSG_FLAG_TRANSPARENT;
        msg_to_send->msg_id = ++rnm->last_msg_id;
        rnm_debug("sending TRANSPARENT msg with msg_id %u\r\n", msg_to_send->msg_id);
        rnms_msg_output(rnm, msg_to_send, msg_len);
        goto free;
    }

    rnm_debug("received cmd %u, session_id %u, msg_id %u\r\n", msg->cmd.cmd, msg->cmd.session_id, msg->cmd.msg_id);
    if (cmd_id < BF1B_CMD_MAX && cmd_handler_table[cmd_id].handler) {
        rnm->statistic.cmds[msg->cmd.cmd].rx_cnt++;

        ret = cmd_handler_table[cmd_id].handler(rnm, msg);
        if (ret.flag & CMD_HANDLER_FLAG_NO_ACK) {
            goto free;
        }
        RNM_MSG_FILL_COMMON(ack, msg);
        ack.hdr.status = ret.status;
    } else {
        rnm_err("Unknown CMD or no handler. CMD ID %u\r\n", cmd_id);
        inc_stat_scratch_ctr(rnm, RNMS_STAT_ERR_INVALID_CMD);
        RNM_MSG_FILL_COMMON(ack, msg);
        ack.hdr.status = STATUS_NOT_IMPLEMENTED;
    }
    rnm_debug("sending ack session_id %u, msg_id %u\r\n", ack.hdr.session_id, ack.hdr.msg_id);
    rnms_msg_output(rnm, &ack, sizeof(ack));

free:
    if (msg->data) {
        msg->free_fn(msg->data);
    }
}
