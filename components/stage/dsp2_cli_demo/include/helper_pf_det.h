
#ifndef __HELPER_PF_DEC_H__
#define __HELPER_PF_DEC_H__

#include "blai_def.h"

#define DETECT_RESULT_NUM   (4)
struct blai_result_draw_t {
    int count;
    struct blai_result_t result[DETECT_RESULT_NUM];
};
uint8_t detect_msg[101];

int helper_pf_det_cli_init(void);
#endif /* __HELPER_PF_DEC_H__ */

