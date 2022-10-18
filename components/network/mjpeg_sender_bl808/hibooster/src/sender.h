#ifndef __SENDER_H__
#define __SENDER_H__

#include <stdint.h>

#if !defined(MIN)
#define MIN(x, y) ((x) > (y) ? (y) : (x))
#endif

#if !defined(MAX)
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#endif

#define MAX_BUFFERD_FRAMES  4
#define IMAGE_FRAG_PAYLOAD_SIZE_MAX 1024 // 一段最大payload大小
#define USER_MSG_PAYLOAD_SIZE_MAX 128

#define MCU_CTLMSG_PAYLOAD_SIZE_MAX 128

#define IMAGE_SIZE_MAX (4 * 1024 * 1024) // 1帧最大大小

#define IMAGE_APPENDIX_MAX_LEN 32

#define MIN_FRAME_INTERVAL_TICKS pdMS_TO_TICKS(1000 / 30)

// 1帧最多分为多少段
#define IMAGE_FRAGS_COUNT_MAX ( IMAGE_SIZE_MAX / IMAGE_FRAG_PAYLOAD_SIZE_MAX + \
    	(IMAGE_SIZE_MAX % IMAGE_FRAG_PAYLOAD_SIZE_MAX == 0 ? 0 : 1) )

#define FRAGS_ACK_BITMAP_BYTES_MAX ( IMAGE_FRAGS_COUNT_MAX / 8 + \
    	(IMAGE_FRAGS_COUNT_MAX % 8 == 0 ? 0 : 1) )

/*
 * core struct
 *
 * */
#define MAX_IMG_FRAGMENT_SIZE_IN_BYTES    (1024)
#define MAX_IMG_FRAGMENT_SIZE_IN_POWER2   (10)
#define MAX_IMG_SIZE_IN_KB    (4 * 1024)
#define MJPEG_VERSION   (0x01000202)
#define MAX_BUFFERED_FRAME  (4)

#define SET_ADD     0
#define SET_CRC     0
/*XXX this struct is aliged on 8 Bytes boudary*/
typedef struct frame_header_data
{
    uint32_t ver;           //version of protocal
    uint64_t seq_fly;       //IMG SEQ on the fly
    uint64_t seq_total;     //Overall IMG SEQ counting from sensor
    uint64_t seq_acked;     //last acked IMG
    uint32_t fragment_id;   //fragments of IMG
    uint32_t fragment_total; //total fragments for current IMG
    uint32_t len;            //total IMG size in bytes 
    uint32_t len_part;       //ZZ
    uint16_t width;
    uint16_t height;
    uint8_t quality;
    uint8_t frame_pos;       //buffer status when sent from sender
    uint8_t frame_max;       //buffer status when sent from sender
    uint8_t _aligh_pad[1];
} frame_header_data_t;

/*XXX this struct is aliged on 8 Bytes boudary*/
typedef struct frame_header_ack
{
    uint32_t ver;
    uint8_t num;          //numbfer of IMG ack
    struct
    {
        uint64_t seq;
        uint32_t received;
        uint32_t bitmap[MAX_IMG_SIZE_IN_KB/32];
    } img_ack[0];
} frame_header_ack_t;

struct sender_config_t {
    uint8_t is_configured;
    uint16_t local_ctl_port;
    uint16_t send_port;
    uint16_t server_port;
};

typedef struct imgs_desc{
    uint32_t used;
    uint32_t frames;// number of frames in hardware used buffer, when this IMG is got
    uint8_t *addr1;
    uint8_t *addr2;
    uint32_t len1;
    uint32_t len2;
    uint8_t quality;
    uint16_t width;
    uint16_t height;
    uint64_t seq_fly;
    uint64_t seq_total;
    uint32_t fragment_sending;
    uint32_t fragment_total;
    uint32_t len_piece; //len of last IMG fragment
    uint32_t retry_count;
#define IMGS_DESC_T_SEND_STATUS_NEW          (0)
#define IMGS_DESC_T_SEND_STATUS_PART         (1)
#define IMGS_DESC_T_SEND_STATUS_ALL_SENT     (2)
#define IMGS_DESC_T_SEND_STATUS_RESENDING    (3)
#define IMGS_DESC_T_SEND_STATUS_FINISHED     (4)
    uint32_t send_status; //0: fresh new, 1: part sent, 2:all sent
    uint32_t ack_status_from_remote;//0: no any ACK, 1 parttly acked, 2 all acked
    uint32_t bitmap[MAX_IMG_SIZE_IN_KB/32];
#if SET_ADD
    //add
    int image_appendix_len;
    uint8_t image_appendix_data[IMAGE_APPENDIX_MAX_LEN];
#endif
} imgs_desc_t;


struct mcu_msg_min_header {
    uint8_t magic_num; // =0x93
    uint8_t type;
    uint16_t length;
};

struct mcu_msg_ack {
    uint8_t magic_num; // =0x93
    uint8_t type;
    uint16_t length;
    uint32_t seq;
};

struct image_fragment_header {
    uint8_t magic_num; // =0x93
    uint8_t type;
    uint16_t len_pkt;
    uint32_t ver;           //version of protocal
    uint64_t seq_fly;       //IMG SEQ on the fly
    uint64_t seq_total;     //Overall IMG SEQ counting from sensor
    uint64_t seq_acked;     //last acked IMG
    uint32_t fragment_id;   //fragments of IMG
    uint32_t fragment_total; //total fragments for current IMG
    uint32_t len_img_total;            //total IMG size in bytes 
    uint16_t width;
    uint16_t height;
    uint8_t quality;
    uint8_t frame_pos;       //buffer status when sent from sender
    uint8_t frame_max;       //buffer status when sent from sender
    uint8_t retry;

    //add
#if SET_ADD
    uint16_t appendix_length;
    uint16_t appendix_offset;
#endif

#if SET_CRC
    uint32_t crc;
#endif
};

struct mcu_msg_ctlmsg_header {
    uint8_t magic_num; // =0x93
    uint8_t type; // =0x04
    uint16_t length;
    uint32_t mcu_ctlmsg_seq;
    uint16_t mcu_ctlmsg_length;
    uint8_t _pad0[2];
    // ctlmsg
};

struct mcu_msg_queryinfo_resp {
    uint8_t magic_num; // =0x93
    uint8_t type; // =0x04
    uint16_t length;
    uint32_t seq;
    uint8_t mac[6];
    uint8_t ssid[33];
    uint8_t psk[65];
    uint16_t channel;
    uint16_t rate;
};

#define MCU_MSG_MAGIC_NUM  0x93
#define MCU_MSG_PROTO_FRAG 0x01
#define MCU_MSG_PROTO_ACK  0x02
#define MCU_MSG_PROTO_CTLMSG 0x04
#define MCU_MSG_QUERYINFO_RESP 0x08

#define IMAGE_FRAG_HEADER_SIZE (sizeof(struct image_fragment_header))
#define IMAGE_FRAG_SIZE_MAX (IMAGE_FRAG_HEADER_SIZE + IMAGE_FRAG_PAYLOAD_SIZE_MAX)

#define MCU_MSG_CTLMSG_HEADER_SIZE (sizeof(struct mcu_msg_ctlmsg_header))
#define MCU_MSG_CTLMSG_SIZE_MAX (MCU_MSG_CTLMSG_HEADER_SIZE + MCU_CTLMSG_PAYLOAD_SIZE_MAX)

#define MCU_MSG_ACK_SIZE (sizeof(struct mcu_msg_ack))
#define MCU_MSG_SIZE_MAX MAX(MAX(IMAGE_FRAG_SIZE_MAX, MCU_MSG_ACK_SIZE), MCU_MSG_CTLMSG_SIZE_MAX)

struct control_msg_min_header {
    uint8_t magic_num; // =0xEF
    uint8_t type;
    uint16_t length;
};

struct control_msg_start_stop {
    uint8_t magic_num; // =0xEF
    uint8_t type;
    uint16_t length;
};

struct control_msg_user_header {
    uint8_t magic_num;
    uint8_t type;
    uint16_t length;
    uint32_t user_msg_seq;
    uint16_t user_msg_length;
    uint8_t _pad0[2];
    // user_msg
};

struct img_ack {
#define CONTROL_MSG_ACK_HEADER_IMG_ACK_HEADER_SIZE        (16)
    uint64_t seq;
#define CONTROL_MSG_ACK_HEADER_RECEIVED_STATUS_PART       (0)
#define CONTROL_MSG_ACK_HEADER_RECEIVED_STATUS_ACKED      (1)
#define CONTROL_MSG_ACK_HEADER_RECEIVED_STATUS_DROPPED    (2)
#define CONTROL_MSG_ACK_HEADER_RECEIVED_STATUS_LOSTALL    (3)
    uint32_t received;
    uint32_t len;// total len including img_ack
    uint32_t bitmap[MAX_IMG_SIZE_IN_KB/32];
};

struct control_msg_ack_header {
    uint8_t magic_num; // =0xEF
    uint8_t type;
    uint16_t length;
    uint32_t ver;
    uint8_t num;          //numbfer of IMG ack
    uint8_t pad[3];
    uint32_t flyctl_msg_seq;
    uint8_t flyctl_msg_data[8];
    uint8_t quality1;
    uint8_t quality2;
    uint8_t q_threshold1;
    uint8_t q_threshold2;
    uint8_t active_cam_idx;
    uint8_t _pad[3];
    struct img_ack ack[0];
};

// ACK msg sent from phone to MCU
struct peer_control_msg_ack {
    uint8_t magic_num; // =0xEF
    uint8_t type; // =0x08
    uint16_t length;
    uint32_t seq;
};

struct control_msg_queryinfo_header {
    uint8_t magic_num; // =0xEF
    uint8_t type;      // =0x10
    uint16_t length;
    uint32_t seq;
};

#define CONTROL_MSG_MAGIC_NUM    0xEF
#define CONTROL_PROTO_START      0x00
#define CONTROL_PROTO_STOP       0x01
#define CONTROL_PROTO_ACK        0x02
#define CONTROL_PROTO_USER       0x04
#define CONTROL_PROTO_MCUMSG_ACK 0x08
#define CONTROL_PROTO_QUERYINFO  0x10

#define CONTROL_MSG_MIN_HEADER_SIZE (sizeof(struct control_msg_min_header))
#define CONTROL_MSG_STARTSTOP_SIZE (sizeof(struct control_msg_start_stop))
#define CONTROL_MSG_ACK_HEADER_SIZE (sizeof(struct control_msg_ack_header))
#define CONTROL_MSG_USER_HEADER_SIZE (sizeof(struct control_msg_user_header))
#define CONTROL_MSG_MCUCTL_ACK_HEADER_SIZE (sizeof(struct peer_control_msg_ack))

#define FRAGS_IMG_ACK_BYTES_MAX  ((MAX_BUFFERD_FRAMES + 1) * sizeof(struct img_ack))
#define CONTROL_MSG_ACK_SIZE_MAX (CONTROL_MSG_ACK_HEADER_SIZE + FRAGS_IMG_ACK_BYTES_MAX)
#define CONTROL_MSG_USER_SIZE_MAX (CONTROL_MSG_USER_HEADER_SIZE + USER_MSG_PAYLOAD_SIZE_MAX)
#define CONTROL_MSG_MCUCTL_ACK_SIZE_MAX CONTROL_MSG_MCUCTL_ACK_HEADER_SIZE

#define CONTROL_MSG_SIZE_MAX MAX(MAX(CONTROL_MSG_ACK_SIZE_MAX, CONTROL_MSG_USER_SIZE_MAX), CONTROL_MSG_MCUCTL_ACK_SIZE_MAX)

#endif
