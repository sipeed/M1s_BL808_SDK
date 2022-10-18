#ifndef __MOTION_DETECT_H__
#define __MOTION_DETECT_H__

/* How many zones which are being monitored */
#define ALARM_ZONE_MAX 2

/* 
 *   -----------------------     level 5     The least sensitive 
 * 
 *   -----------------------     level 4
 * 
 *   -----------------------     level 3
 *         | ALARM_SENSITY_STEP_VAL 
 *   -----------------------     level 2
 * 
 *   -----------------------     ALARM_SENSITY_START_VAL, start threshold, 
 *                               level 1, The most sensitive
 *
 *   -----------------------     zero, means no changing.
 */

 
/* Don't be great than 5 */
#define ALARM_SENSITY_LEVEL_MAX 5

/* The start threshold */
#define ALARM_SENSITY_START_VAL 5
/* The stepping value of each sensity level */ 
#define ALARM_SENSITY_STEP_VAL 10
 
/* Each level */
#if ALARM_SENSITY_LEVEL_MAX >= 1
#define ALARM_SENSITY_LV1 1 
#define ALARM_SENSITY_VAL_LV1 ALARM_SENSITY_START_VAL
#define USING_ALARM_LV1
#endif
#if ALARM_SENSITY_LEVEL_MAX >= 2
#define ALARM_SENSITY_LV2 2 
#define ALARM_SENSITY_VAL_LV2 (ALARM_SENSITY_START_VAL + \
        ALARM_SENSITY_STEP_VAL * (ALARM_SENSITY_LV2 - 1))
#define USING_ALARM_LV2
#endif
#if ALARM_SENSITY_LEVEL_MAX >= 3
#define ALARM_SENSITY_LV3 3 
#define ALARM_SENSITY_VAL_LV3 (ALARM_SENSITY_START_VAL + \
        ALARM_SENSITY_STEP_VAL * (ALARM_SENSITY_LV3 - 1))
#define USING_ALARM_LV3
#endif
#if ALARM_SENSITY_LEVEL_MAX >= 4
#define ALARM_SENSITY_LV4 4 
#define ALARM_SENSITY_VAL_LV4 (ALARM_SENSITY_START_VAL + \
        ALARM_SENSITY_STEP_VAL * (ALARM_SENSITY_LV4 - 1))
#define USING_ALARM_LV4
#endif
#if ALARM_SENSITY_LEVEL_MAX >= 5
#define ALARM_SENSITY_LV5 5 
#define ALARM_SENSITY_VAL_LV5 (ALARM_SENSITY_START_VAL + \
        ALARM_SENSITY_STEP_VAL * (ALARM_SENSITY_LV5 - 1))
#define USING_ALARM_LV5
#endif

/* Rectangle define */
typedef struct _tag_rect {
    unsigned short left;
    unsigned short right;
    unsigned short top;
    unsigned short bottom;
} Rect, *PRect;

/* Define the alarm zone */
typedef struct _tag_alarm_zone {
    int id;
    Rect zone;
    uint8_t alarm_level;
} AlarmZone, *PAlarmZone;

/* 
 * Return the alarm info into an array whose type is AlarmInfoArray when 
 *  invoke motion_detect()
 */
typedef AlarmZone AlarmInfoArray[ALARM_ZONE_MAX];

int md_init(uint16_t width, uint16_t height);
int md_deinit(void);
int add_alarm_zone(Rect* zone, int id, uint8_t alarm_level);
int rm_alarm_zone(int id);
int motion_detect(uint8_t *frame_addr, AlarmInfoArray* alarm_info, int* alarm_count);

#endif /* __MOTION_DETECT_H__ */
