# Component Makefile
#
## These include paths would be exported to project level
COMPONENT_ADD_INCLUDEDIRS += inc

## not be exported to project level
COMPONENT_PRIV_INCLUDEDIRS :=

## This component's src 

COMPONENT_SRCDIRS := src


##
#CPPFLAGS += 
CFLAGS += -Wno-implicit-function-declaration
