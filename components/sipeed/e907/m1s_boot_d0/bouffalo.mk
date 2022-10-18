# Component Makefile
#
## These include paths would be exported to project level
COMPONENT_ADD_INCLUDEDIRS += inc
							 
## not be exported to project level
COMPONENT_PRIV_INCLUDEDIRS := inc_pri

## This component's src
COMPONENT_SRCDIRS := src

COMPONENT_SRCS := src/boot_cpu0.c src/l2_sram.c
				  
COMPONENT_OBJS := $(patsubst %.c,%.o, $(COMPONENT_SRCS))


##
#CPPFLAGS += 
