# Component Makefile
#
## These include paths would be exported to project level
COMPONENT_ADD_INCLUDEDIRS +=

## not be exported to project level
COMPONENT_PRIV_INCLUDEDIRS := include

## This component's src
ifeq ("$(CPU_ID)", "D0")
ifeq ($(CONFIG_NO_DSP2_CAM), 1)
COMPONENT_SRCS := src/helper_cam_yuv_sensor.c
else
COMPONENT_SRCS := src/helper_sdh.c \
                  src/helper_mem.c \
                  src/helper_vdebug.c \
                  src/helper_dsp2.c \
                  src/helper_dsp2_parse.c \
                  src/helper_venc.c \
                  src/helper_venc_parse.c \
                  src/helper_mjdec.c \
                  src/helper_md.c \
                  src/helper_fast_vidcap.c \
                  src/helper_mjpeg.c \
                  src/helper_dpi_hw_mode.c \
                  src/helper_socket.c \
                  src/helper_snsinfo.c \
                  src/helper_sns_raw2mem.c \
                  src/helper_cam_yuv_sensor.c \
                  src/helper_pf_det.c \
                  #src/helper_npu_accel.c \
                  #src/helper_yolo.c \
                  #src/helper_amr.c \
                  #src/helper_psm.c \
                  #src/helper_ota.c \
                  #src/helper_http.c \
                  #src/helper_nv.c \
                  #src/helper_wifi.c \
                  #src/helper_opus.c \
                  #src/helper_audio.c \
                  #src/helper_task.c \
                  #src/helper_sys.c \
                  #src/helper_pwm.c \
                  #src/helper_misc.c \
                  #src/helper_mjpeg.c \

endif
else
COMPONENT_SRCS := src/helper_mjpeg.c \
 
endif

COMPONENT_OBJS := $(patsubst %.c,%.o, $(COMPONENT_SRCS))

COMPONENT_SRCDIRS := src


##
#CPPFLAGS +=
