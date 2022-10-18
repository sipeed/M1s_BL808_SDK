#include <string.h>
#include <bl808_mmsys_misc.h>
#include <img_peripheral_ctrl.h>

#include <bl_gpio.h>
#include <bl_pwm.h>

static pwm_ir_led_cfg ir_led_cfg = {0};

void ir_cut_switch(bool enable)
{
#if (BL80X_HW_VER <= BL80X_HW_A0)
    //bl_gpio_output_set(GPIO_SENSOR_BOARD_IRC, gpio_val);
#else
    uint8_t gpio_val = enable ? 1 : 0;
    MMSYS_Set_SW_GPIO(2, gpio_val);
#endif
}

void ir_led_en(bool enable)
{
    if(ir_led_cfg.freq == 0) {
        ir_led_cfg.freq = IRLED_FREQ;////2000;//
    }

    if(ir_led_cfg.duty == 0) {
        ir_led_cfg.duty = IRLED_DUTY;////99.0;//
    }

    if(enable == 1){
        bl_pwm_init(PWM_ID_IRLED, 0, ir_led_cfg.freq);
        bl_pwm_set_duty(PWM_ID_IRLED, ir_led_cfg.duty);
        bl_pwm_start(PWM_ID_IRLED);
    } else {
        bl_pwm_stop(PWM_ID_IRLED);
    }
}

int ir_led_set_freq(int freq)
{
    bl_pwm_set_freq(PWM_ID_IRLED, freq);
    ir_led_cfg.freq = freq;

    return 0;
}

int ir_led_get_duty(float* duty)
{
    bl_pwm_get_duty(PWM_ID_IRLED, &ir_led_cfg.duty);
    *duty = ir_led_cfg.duty;

    return 0;
}

int ir_led_set_duty(float duty)
{
    bl_pwm_set_duty(PWM_ID_IRLED, duty);
    ir_led_cfg.duty = duty;

    return 0;
}

