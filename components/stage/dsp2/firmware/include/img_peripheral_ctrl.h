#ifndef __IMG_PERIPHERAL_CTRL_H__
#define __IMG_PERIPHERAL_CTRL_H__

#define PWM_ID_IRLED        (0x0) // using MC0 CH0P
#define IRLED_FREQ 50*1000
#define IRLED_DUTY 50.0 // duty = 50%

typedef struct {
    uint32_t freq;
    float duty; // duty = 50%
}pwm_ir_led_cfg;

void ir_cut_switch(bool enable);
void ir_led_en(bool enable);
int ir_led_set_freq(int freq);
int ir_led_get_duty(float *duty);
int ir_led_set_duty(float duty);


#endif /* __IMG_PERIPHERAL_CTRL_H__ */
