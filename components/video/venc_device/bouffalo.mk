# Component Makefile
#
## These include paths would be exported to project level
COMPONENT_ADD_INCLUDEDIRS += venc_device/include

## not be exported to project level
COMPONENT_PRIV_INCLUDEDIRS := venc_device/include

## This component's src 
COMPONENT_SRCS := bl808_venc/bl808_venc_device.c


COMPONENT_OBJS := $(patsubst %.c,%.o, $(COMPONENT_SRCS))

COMPONENT_SRCDIRS := bl808_venc


##
#CPPFLAGS += 
