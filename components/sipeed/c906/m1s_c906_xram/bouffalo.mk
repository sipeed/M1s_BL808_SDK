# Component Makefile
#
## These include paths would be exported to project level
COMPONENT_ADD_INCLUDEDIRS += include ../bl808_peri_common

## not be exported to project level
#COMPONENT_PRIV_INCLUDEDIRS :=

## This component's src 
COMPONENT_SRCS := 	src/m1s_c906_xram.c \
					src/m1s_c906_xram_wifi.c \
					src/m1s_c906_xram_audio.c \
					src/m1s_c906_xram_pwm.c \
					src/m1s_c906_xram_usb.c \
					src/m1s_c906_xram_flash.c

COMPONENT_OBJS := $(patsubst %.c,%.o, $(COMPONENT_SRCS))

COMPONENT_SRCDIRS := src


ifeq ($(CONFIG_CPU_E907),1)
	CFLAGS+= -DXRAM_CPU_E907
endif
ifeq ($(CONFIG_CPU_C906),1)
	CFLAGS+= -DXRAM_CPU_C906
endif
ifeq ($(CONFIG_CPU_E902),1)
	CFLAGS+= -DXRAM_CPU_E902
endif
##
#CPPFLAGS += 
