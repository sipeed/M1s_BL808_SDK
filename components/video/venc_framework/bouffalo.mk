# Component Makefile
#
## These include paths would be exported to project level
COMPONENT_ADD_INCLUDEDIRS += venc_framework/include

## not be exported to project level
COMPONENT_PRIV_INCLUDEDIRS := venc_framework/include

## This component's src 
COMPONENT_SRCS := venc_framework/venc_framework.c

COMPONENT_OBJS := $(patsubst %.c,%.o, $(COMPONENT_SRCS))

COMPONENT_SRCDIRS := venc_framework


##
#CPPFLAGS += 
