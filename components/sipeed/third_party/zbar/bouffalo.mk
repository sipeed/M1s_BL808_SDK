# Component Makefile
#
## These include paths would be exported to project level
COMPONENT_ADD_INCLUDEDIRS += .
							 
## not be exported to project level
COMPONENT_PRIV_INCLUDEDIRS := inc

## This component's src
COMPONENT_SRCDIRS := src

COMPONENT_SRCS := src/bch15_5.c  \
				src/binarize.c  \
				src/decoder.c  \
				src/error.c  \
				src/img_scanner.c  \
				src/isaac.c  \
				src/qrdec.c  \
				src/qrdectxt.c  \
				src/qr_finder.c  \
				src/refcnt.c  \
				src/rs.c  \
				src/scanner.c  \
				src/symbol.c  \
				src/util.c  \
				src/zbar_image.c
				  
COMPONENT_OBJS := $(patsubst %.c,%.o, $(COMPONENT_SRCS))


##
#CPPFLAGS += 
