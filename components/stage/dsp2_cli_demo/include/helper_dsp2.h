#ifndef __HELPER_DSP2_H__
#define __HELPER_DSP2_H__

int dsp2_ctrl(void);
int load_reg(uint32_t *addr);
int hdmi_ctrl(int ctrl_type);

int helper_dsp2_cli_init(void);

#endif /* __HELPER_DSP2_H__ */

