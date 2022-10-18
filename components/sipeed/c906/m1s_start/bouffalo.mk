# Component Makefile
#
## These include paths would be exported to project level
COMPONENT_ADD_INCLUDEDIRS += 
							 
## not be exported to project level
COMPONENT_PRIV_INCLUDEDIRS := 

## This component's src
COMPONENT_SRCDIRS := src

COMPONENT_SRCS := src/start_main.c
				  
COMPONENT_OBJS := $(patsubst %.c,%.o, $(COMPONENT_SRCS))


##
#CPPFLAGS += 
