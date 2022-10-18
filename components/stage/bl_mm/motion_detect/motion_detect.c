#include <string.h>
#include <bl808_common.h>
#include "motion_detect.h"

 
/* Error code */
#define EC_MEM        1     /* No memery */
#define EC_ID         2     /* ID error */
#define EC_NO_SLOT    3     /* Alarm table full */
#define EC_FRAM1      4     /* Not ready */
#define EC_FRAM2      5     /* Not ready */
#define EC_STATE      6     /* Error state */
 
/* 
 * Bits operation 
 *
 * dat: the target byte.
 * pos: the position you want to operate.
 * len: the width of bits.
 * val: the value you want to set or test.
 *
 * Example:
 *  dat      |  operation                    |   result
 *  ---------+-------------------------------+---------- 
 *  11010001 |  SET_BYTE_BITS(dat, 2, 2, 3)  |   11011101
 *  11010001 |  SET_BYTE_BITS(dat, 4, 2, 3)  |   11110001
 *  10110111 |  TEST_BYTE_BITS(dat, 3, 2, 1) |   flase
 *  10110111 |  TEST_BYTE_BITS(dat, 3, 2, 2) |   true
 */
#define SET_BYTE_BITS(dat, pos, len, val) do {                         \
        (dat) &= ~( (uint32_t)(~(0xFF<<(len))) << (pos) ); /* Set to zero */     \
        (dat) |= ( ((val) & (uint32_t)(~(0xFF<<(len)))) << (pos) ); /* Set val */  \
    } while (0)
#define TEST_BYTE_BITS(dat, pos, len, val)                             \
    ( (((val) & (uint32_t)(~(0xFF<<(len)))) << (pos)) ==                           \
        ( (dat) & ( (uint32_t)(~(0xFF<<(len))) << (pos) ) ) ) 
 
 
/*
 * The last changing direction of Y.
 * 00:  grayscale no changed.
 * 01:  grayscale increased.
 * 10:  grayscale decreased.
 *
 * last_y_direction[]
 *  byte0          byte1          byte2
 *  01 00 10 01    10 10 00 01    10 10 00 01 ...
 *            |
 *            |
 *            V
 *       Start from here, This is the first block.
 *
 */
#define BLK_Y_NO_CHANGE 0
#define BLK_Y_INCREASED 1
#define BLK_Y_DECREASED 2

/* Last y change direction */
static uint8_t *last_y_direction;
 
/* Last grayscale */
static uint8_t *last_y;
 
static uint8_t *alarm_tbl;
 
/* The current width & height of image */
static uint16_t img_width;
static uint16_t img_height;
static uint32_t frame_size;

/* State of motion detecting process */
#define MD_STATE_FRAM1 1
#define MD_STATE_FRAM2 2
#define MD_STATE_FRAM3 3
uint8_t motion_detect_state = MD_STATE_FRAM1;
 
/* Registered alarm zone */
PAlarmZone alarm_zone_tbl[ALARM_ZONE_MAX];

 
static void coordinate_transfer(Rect* alarm_zone, Rect* blk_zone)
{
    blk_zone->left = img_width * alarm_zone->left / 1000;
    blk_zone->right = img_width * alarm_zone->right / 1000;
    blk_zone->top = img_height * alarm_zone->top / 1000;
    blk_zone->bottom = img_height * alarm_zone->bottom / 1000;
}

static bool greyscale_changed(int delta_y)
{
    if (delta_y < 0)
        delta_y = -delta_y;
 
    return (delta_y >= ALARM_SENSITY_VAL_LV5);
}
 
static void update_y_direction(uint32_t block_index, int delta_y)
{
    if (greyscale_changed(delta_y)) {
        SET_BYTE_BITS(last_y_direction[block_index / 4], 
            (block_index % 4) << 1, 2, delta_y > 0 ? BLK_Y_INCREASED : BLK_Y_DECREASED);
        //BL_LOGI("\ty_dir[%d]: delta_y %d, level %d\r\n", block_index, delta_y, level);
    } else {
        SET_BYTE_BITS(last_y_direction[block_index / 4], 
            (block_index % 4) << 1, 2, BLK_Y_NO_CHANGE);
    } 
}

static void update_alarm_tbl(uint32_t block_index, int delta_y)
{
    if (greyscale_changed(delta_y)) {
        if ( 
             /* Bright  -> Dark -> Bright */
             (delta_y > 0 && TEST_BYTE_BITS(
                    last_y_direction[block_index / 4],
                    (block_index % 4) << 1, 2, BLK_Y_DECREASED))  || 
             /* Dark -> Bright -> Dark */
             (delta_y < 0 && TEST_BYTE_BITS(
                    last_y_direction[block_index / 4],
                    (block_index % 4) << 1, 2, BLK_Y_INCREASED))  
                ) {
            //BL_LOGI("alarm_tbl: delta_y %d, level %d\r\n", delta_y, level);
            alarm_tbl[block_index / 8] |= 0x01 << (block_index % 8);
        }
    }
    /* Cover the old table */
    update_y_direction(block_index, delta_y);
}

/* 
 * Check whether the selected block zone contains valid alarm.
 *
 * @blk_zone: Rectangle descripted by jpeg block coordinate system.
 * @alarm_level:  which alarm level do you want to check?
 *
 * @return:  true for ALARM and false for NO alarm.
 */
static bool is_alarm(Rect* blk_zone)
{
    int row, col;
    int blk_index;
    int alarm_blk_cnt = 0;

    for (row = blk_zone->top; row <= blk_zone->bottom; row++) {
        for (col = blk_zone->left; col <= blk_zone->right; col++) {
            blk_index = img_width * row + col;
            if (alarm_tbl[blk_index / 8] & (0x01 << (blk_index % 8))) {
                alarm_blk_cnt++;
                //BL_LOGI("alarm at idx %d\r\n", blk_index);
            }
        }
    }

    if (alarm_blk_cnt >= MD_ALARM_BLOCK_CNT_THRESH) {
        BL_LOGI("alarm_blk_cnt %d\r\n", alarm_blk_cnt);
        return true;
    }

    return false; 
}
 
/*
 * Scan the alarm table, when valid and the corresponding area 
 *   is registered, return alarm info.
 *
 * @alarm_info:  Alarm info, this is an array.
 * @alarm_count: The valid length of @alarm_info array. 
 */
static void generate_alarm(AlarmInfoArray* alarm_info, int* alarm_count)
{
    int i;
    int index = 0;
 
    /* Reset the count */
    *alarm_count = 0;
        
    for (i = 0; i < ALARM_ZONE_MAX; i++) {
        if (alarm_zone_tbl[i]) {
            if (is_alarm(&(alarm_zone_tbl[i]->zone))) {
                memcpy(&(*alarm_info)[index], alarm_zone_tbl[i], sizeof(AlarmZone));
                index++; 
            }
        }
    }
    *alarm_count = index;
}
 
/*
 * Invoke this at every image frame 
 *
 * @img:         An image object pointer. Contains buffer and length.
 * @alarm_info:  Alarm info, this is an array.
 * @alarm_count: The valid length of @alarm_info array. 
 *
 * @return: 0 for OK. The output parameters are valid only when return 0.
 */
int motion_detect(uint8_t *frame_addr, AlarmInfoArray* alarm_info, int* alarm_count)
{
    uint8_t *crt_y = frame_addr;

    uint32_t i;
    int delta_y;

    switch (motion_detect_state) {
        /* Not ready, only one frame. */
        case MD_STATE_FRAM1: 
            memcpy(last_y, crt_y, frame_size);
            motion_detect_state = MD_STATE_FRAM2;
            return EC_FRAM1;
 
        /* Not ready, only two frames. */
        case MD_STATE_FRAM2: 
            for (i = 0; i < frame_size; i++) {
                delta_y = crt_y[i] - last_y[i];
                update_y_direction(i, delta_y);
            }
            memcpy(last_y, crt_y, frame_size);
            motion_detect_state = MD_STATE_FRAM3;
            return EC_FRAM2;
 
        /* YES! Loops in this case */
        case MD_STATE_FRAM3:
            for (i = 0; i < frame_size; i++) {
                delta_y = crt_y[i] - last_y[i];
                update_alarm_tbl(i, delta_y);
            }
 
            memcpy(last_y, crt_y, frame_size);
            
            generate_alarm(alarm_info, alarm_count);

            /* Reset alarm_tbl. This is very IMPORTANT! */
            memset(alarm_tbl, 0x00, (frame_size >> 3));
            return 0;
 
        /* NOT expected */
        default:
            return EC_STATE;
    }
}

/* 
 * Initial or reset the motion detecting system. 
 * 
 * @return: 0 for OK
 */
int md_init(uint16_t width, uint16_t height)
{
    img_width = width;
    img_height = height;
    frame_size = width * height;
    motion_detect_state = MD_STATE_FRAM1;

    BL_LOGI("Alloc last_Y buffer ...\r\n");
    last_y = pvPortMalloc(frame_size);
    last_y_direction = pvPortMalloc(frame_size >> 2);
    alarm_tbl = pvPortMalloc(frame_size >> 3);

    memset(last_y_direction, 0x00, (frame_size >> 2));
    memset(alarm_tbl, 0x00, (frame_size >> 3));

    return 0;
}


int md_deinit(void)
{
    BL_LOGI("Free last_Y buffer ...\r\n");
    vPortFree(last_y);
    vPortFree(last_y_direction);
    vPortFree(alarm_tbl);

    return 0;
}

/* 
 * Add alarm zone.
 *
 * @zone: selected alarm zone, a rectangle(check header file for details). 
 * @id:   Registered id.
 * @alarm_level: use macro defined in the header file.
 * 
 * @return: 0 for OK.
 */
int add_alarm_zone(Rect* zone, int id, uint8_t alarm_level)
{
    PAlarmZone p;
    int i;
    
    /* Check the zone id, no repeated */
    for (i = 0; i < ALARM_ZONE_MAX; i++) {
        if (alarm_zone_tbl[i]) {
            if (alarm_zone_tbl[i]->id == id)
                return EC_ID;
        }
    }
 
    /* Find an empty slot */
    for (i = 0; i < ALARM_ZONE_MAX; i++) {
        if (!alarm_zone_tbl[i])
            break;
    }
 
    /* No empty slot */
    if (i == ALARM_ZONE_MAX)
        return EC_NO_SLOT;
 
    /* Get memory */
    p = (PAlarmZone )pvPortMalloc(sizeof(AlarmZone));
    if (!p) {
        return EC_MEM;
    }
 
    /* Check the range of rectangle */
    if (zone->left > 999) zone->left = 999;
    if (zone->right > 999) zone->right = 999;
    if (zone->top > 999) zone->top = 999;
    if (zone->bottom > 999) zone->bottom = 999;

    /* Initialize */
    p->id = id;
    p->alarm_level = alarm_level;
    coordinate_transfer(zone, &p->zone);
 
    /* Insert to one empty slot */
    alarm_zone_tbl[i] = p;
 
    return 0;
}
 
 
/*
 * Remove alarm zone by id.
 *
 * @id:  id of alarm zone.
 *
 * @return: 0 for OK
 */
int rm_alarm_zone(int id)
{
    int i;
    
    for (i = 0; i < ALARM_ZONE_MAX; i++) {
        if (alarm_zone_tbl[i]) {  
            if (alarm_zone_tbl[i]->id == id) {
                vPortFree(alarm_zone_tbl[i]);
                alarm_zone_tbl[i] = NULL;
                return 0;
            }
        }
    }
 
    return EC_ID;
}
 
 
/*
 * Remove all alarm zone .
 *
 * @return: 0 for OK
 */
int rm_all_alarm(void)
{
    memset(alarm_zone_tbl, 0x00, sizeof(alarm_zone_tbl));
    return 0;
}


