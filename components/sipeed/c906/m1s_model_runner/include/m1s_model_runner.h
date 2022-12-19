#pragma once

#include <stdint.h>

typedef enum {
    SM_OK,
    SM_ERR,
    SM_NO_RAM,
    SM_INVALID_PATH,
    SM_INVALID_MODEL,
    SM_LOAD_MODEL_ERR,
} sm_status_e;

typedef struct {
    uint8_t *output;
    float scale;
    int zero_point;
    uint32_t output_shape[3];
} model_result_t;

typedef void *(model_result_cb_t)(model_result_t *result, void *arg);

sm_status_e m1s_model_load(const char *model_path);
sm_status_e m1s_model_unload();
sm_status_e m1s_model_feed(const void *data_in);
sm_status_e m1s_model_forward(model_result_cb_t cb, void *cb_arg, void **cb_ret);