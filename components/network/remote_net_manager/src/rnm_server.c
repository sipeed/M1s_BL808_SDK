#include <rnm_server.h>

#include <assert.h>
#include <string.h>
#include <bl_wifi.h>
#include <wifi_mgmr_ext.h>
#include <aos/yloop.h>

static inline void inc_stat_scratch_ctr(rnms_t *rnm, int id)
{
    ++rnm->statistic.scratch_counter[id];
}

static void rnms_mgmr_task(void *pvParameters)
{
    rnms_t *env = (rnms_t *)pvParameters;
    rnm_msg_t msg;

    while (1) {
        if (pdPASS == xQueueReceive(env->cmd_msg_queue, &msg, portMAX_DELAY)) {
            rnms_msg_process(env, &msg);
        } else {
            rnm_err("read msg queue failed\r\n");
        }
    }
}

int rnm_cmd_input(rnms_t *rnm, const rnm_msg_t *msg)
{
    if (!(rnm && msg)) {
        return -1;
    }

    if (pdPASS == xQueueSendToBack(rnm->cmd_msg_queue, msg, portMAX_DELAY)) {
        return 0;
    } else {
        return -1;
    }
}

int rnms_cmd_input_raw(rnms_t *rnm, const void *data, uint16_t data_len)
{
    rnm_msg_t msg;
    void *payload;

    assert(rnm && data && data_len);
    assert(data_len >= sizeof(rnm_base_msg_t));

    memset(&msg, 0, sizeof(msg));
    memcpy(&msg.cmd, data, sizeof(rnm_base_msg_t));
    if (data_len > sizeof(rnm_base_msg_t)) {
        payload = rnm_malloc(data_len);
        if (!payload) {
            inc_stat_scratch_ctr(rnm, RNMS_STAT_ERR_INPUT_NOMEM);
            return -1;
        }
        memcpy(payload, data, data_len);
        msg.free_fn = rnm_free;
        msg.data = payload;
        msg.data_len = data_len;
    }
    return rnm_cmd_input(rnm, &msg);
}

static void wifi_event_cb(input_event_t *event, void *private_data)
{
    rnms_t *rnm = (rnms_t *)private_data;

    if (event->code == CODE_WIFI_ON_CONNECTED) {
        rnms_send_simple_async_msg(rnm, BF1B_CMD_STA_CONNECTED_IND);
    } else if (event->code == CODE_WIFI_ON_DISCONNECT) {
        rnms_send_simple_async_msg(rnm, BF1B_CMD_STA_DISCONNECTED_IND);
    } else if (event->code == CODE_WIFI_ON_AP_STARTED) {
        rnms_send_simple_async_msg(rnm, BF1B_CMD_AP_STARTED_IND);
    } else if (event->code == CODE_WIFI_ON_AP_STOPPED) {
        rnms_send_simple_async_msg(rnm, BF1B_CMD_AP_STOPPED_IND);
    } else if (event->code == CODE_WIFI_ON_GOT_IP) {
        rnms_notify_sta_ip_addr(rnm);
    }
}

rnms_t *rnm_server_init(void *output_fn_env, rnm_output_t output_fn, void *ready_cb_arg, rnm_ready_cb_t ready_cb)
{
    rnms_t *env;

    // hack to check limit at compile time
    if (!(RNMS_STAT_MAX <= RNM_STATISTIC_SCRATCH_COUNTER_NUM)) {
        void RNMS_No_enough_scratch_counter_for_stat_Consider_increase_counters(void);
        RNMS_No_enough_scratch_counter_for_stat_Consider_increase_counters();
    }

    if ((env = rnm_malloc(sizeof(rnms_t))) == NULL) {
        return NULL;
    }

    memset(env, 0, sizeof(rnms_t));

    env->output_fn_env = output_fn_env;
    env->output_fn = output_fn;

    env->ready_cb_arg = ready_cb_arg;
    env->ready_cb = ready_cb;

    env->cmd_msg_queue = xQueueCreateStatic(RNMS_CMD_MSG_QUEUE_CAP, RNMS_CMD_MSG_SIZE, env->cmd_msg_queue_storage_buffer, &env->cmd_msg_queue_buffer);
    xTaskCreateStatic(rnms_mgmr_task, "rnms", RNMS_TASK_STACK_DEPTH, env, RNMS_TASK_PRIORITY, env->cmd_task_stack_buffer, &env->cmd_task_buffer);

    aos_register_event_filter(EV_WIFI, wifi_event_cb, env);

    return env;
}

int rnms_send_transparent_msg(rnms_t *rnm, rnm_msg_t *msg)
{
    if (!(rnm && msg)) {
        return -1;
    }
    msg->cmd.flags |= RNM_MSG_FLAG_TRANSPARENT;
    return rnm_cmd_input(rnm, msg);
}

int rnms_send_simple_async_msg(rnms_t *rnm, bf1b_cmd_t cmd)
{
    rnm_msg_t msg;

    memset(&msg, 0, sizeof(msg));
    msg.cmd.cmd = cmd;
    msg.cmd.flags |= RNM_MSG_FLAG_ASYNC;
    return rnms_send_transparent_msg(rnm, &msg);
}

int rnms_msg_output(rnms_t *rnm, const void *data, uint16_t data_length)
{
    rnm_base_msg_t *msg = (rnm_base_msg_t *)data;

    if (!(msg->cmd < BF1B_CMD_MAX)) {
        rnm_err("Unknown cmd %u!\r\n", msg->cmd);
        return -1;
    }
    rnm->statistic.cmds[msg->cmd].tx_cnt++;
    return rnm->output_fn(rnm->output_fn_env, RNM_OUT_COMMAND, data, data_length);
}

#define MD(id, desc) RNM_MAKE_STAT_SCR_CTR_DESC(id, desc)

static rnm_stat_scr_ctr_desc_t rnms_stat_scr_ctr_desc[RNMS_STAT_MAX] = {
    MD(RNMS_STAT_ERR_INVALID_CMD, "invalid CMD"),
    MD(RNMS_STAT_ERR_INPUT_NOMEM, "malloc fail when RX msg"),
    MD(RNMS_STAT_ERR_OUTPUT_NOMEM, "malloc fail when TX msg"),
};

int rnms_statistic_dump(rnms_t *rnm)
{
    return rnm_statistic_dump(&rnm->statistic, rnms_stat_scr_ctr_desc, RNMS_STAT_MAX);
}
