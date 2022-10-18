#pragma once

#include <stdint.h>

#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <lwip/netif.h>

#include <rnm_config.h>
#include <rnm_msg.h>
#include <rnm_utils.h>
#include <rnm_common.h>

#ifdef __cplusplus
extern "C" {
#endif

// TODO hide info that should be kept private

#define RNMS_TASK_PRIORITY              21
#define RNMS_TASK_STACK_SIZE            2048
#define RNMS_TASK_STACK_DEPTH           (RNMS_TASK_STACK_SIZE / sizeof(StackType_t))
#define RNMS_CMD_MSG_QUEUE_CAP          8
#define RNMS_CMD_MSG_SIZE               sizeof(rnm_msg_t)
#define RNMS_CMD_MSG_QUEUE_STORAGE_SIZE (RNMS_CMD_MSG_QUEUE_CAP * RNMS_CMD_MSG_SIZE)

typedef enum {
    RNM_WIFI_MODE_NONE,
    RNM_WIFI_MODE_AP,
    RNM_WIFI_MODE_STA,
    RNM_WIFI_MODE_AP_STA,
    RNM_WIFI_MODE_SNIFFER,
} rnm_wifi_mode_t;

typedef void (*rnm_ready_cb_t)(void *arg);

typedef struct {
    rnm_wifi_mode_t mode;

    uint16_t last_msg_id;
    void *output_fn_env;
    rnm_output_t output_fn;

    void *ready_cb_arg;
    rnm_ready_cb_t ready_cb;

    StaticTask_t cmd_task_buffer;
    StackType_t cmd_task_stack_buffer[RNMS_TASK_STACK_DEPTH];

    QueueHandle_t cmd_msg_queue;
    StaticQueue_t cmd_msg_queue_buffer;
    uint8_t cmd_msg_queue_storage_buffer[RNMS_CMD_MSG_QUEUE_STORAGE_SIZE];

    void *ota;

    rnm_statistic_t statistic;
} rnms_t;

enum {
    RNMS_STAT_ERR_INVALID_CMD,
    RNMS_STAT_ERR_INPUT_NOMEM,
    RNMS_STAT_ERR_OUTPUT_NOMEM,
    RNMS_STAT_MAX,
};

/**
 * @brief  Process message.
 *
 * @param rnm  RNM server.
 * @param msg  Message.
 */
void rnms_msg_process(rnms_t *rnm, rnm_msg_t *msg);

/**
 * @brief  Init RNM server.
 *
 * @param output_fn_env  Callback argument passed to output_fn.
 * @param output_fn      Callback called to transfer data by lower layer.
 * @param ready_cb_arg   Callback argument passed to ready_cb.
 * @param ready_cb       Optional callback called when HELLO message is received.
 *
 * @return  Context of created RNM server or NULL on error.
 */
rnms_t *rnm_server_init(void *output_fn_env, rnm_output_t output_fn, void *ready_cb_arg, rnm_ready_cb_t ready_cb);

/**
 * @brief  Send a message that is transfered directly to client by rnm task.
 *
 * @param rnm  RNM server.
 * @param msg  Message to send.
 *
 * @return  0 on success, -1 on error
 */
int rnm_server_send_transparent_msg(rnms_t *rnm, rnm_msg_t *msg);

/**
 * @brief   Pass command to RNM to process.
 *
 * @param rnm       RNM server.
 * @param data      Data.
 * @param data_len  Length of data.
 *
 * @return  0 on success, -1 on error.
 */
int rnms_cmd_input_raw(rnms_t *rnm, const void *data, uint16_t data_len);

/**
 * @brief  Send simple async message to client.
 *         This function is used typically to notify client of
 *         STA connection and disconnection.
 *
 * @param rnm  RNM server.
 * @param cmd  Command ID.
 *
 * @return  0 on success, -1 on error.
 */
int rnms_send_simple_async_msg(rnms_t *rnm, bf1b_cmd_t cmd);

/**
 * @brief  Send raw message to peer.
 *
 * @param rnm          RNM server.
 * @param data         Message to send.
 * @param data_length  Length of data.
 *
 * @return  Value returned by registered output function.
 */
int rnms_msg_output(rnms_t *rnm, const void *data, uint16_t data_length);

/**
 * @brief  Notify host STA IP address.
 *
 * @param rnm  RNM server.
 */
void rnms_notify_sta_ip_addr(rnms_t *rnm);

/**
 * @brief  Dump statistic of RNM.
 *
 * @param rnm  RNM server.
 *
 * @note  RNM log should be enabled to output statistic data.
 *
 * @return  0 on success, -1 on error.
 */
int rnms_statistic_dump(rnms_t *rnm);

#ifdef __cplusplus
}
#endif
