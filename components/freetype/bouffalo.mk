# Component Makefile
#
## These include paths would be exported to project level

CFLAGS += -DFT_INTERNAL_OBJECTS_H="<internal/ftobjs.h>"               \
          -DFT_INTERNAL_PIC_H="<internal/ftpic.h>"                    \
          -DFT_INTERNAL_STREAM_H="<internal/ftstream.h>"              \
          -DFT_INTERNAL_MEMORY_H="<internal/ftmemory.h>"              \
          -DFT_INTERNAL_DEBUG_H="<internal/ftdebug.h>"                \
          -DFT_INTERNAL_CALC_H="<internal/ftcalc.h>"                  \
          -DFT_INTERNAL_DRIVER_H="<internal/ftdriver.h>"              \
          -DFT_INTERNAL_TRACE_H="<internal/fttrace.h>"                \
          -DFT_INTERNAL_GLYPH_LOADER_H="<internal/ftgloadr.h>"        \
          -DFT_INTERNAL_SFNT_H="<internal/sfnt.h>"                    \
          -DFT_INTERNAL_SERVICE_H="<internal/ftserv.h>"               \
          -DFT_INTERNAL_RFORK_H="<internal/ftrfork.h>"                \
          -DFT_INTERNAL_VALIDATE_H="<internal/ftvalid.h>"             \
          -DFT_INTERNAL_TRUETYPE_TYPES_H="<internal/tttypes.h>"       \
          -DFT_INTERNAL_TYPE1_TYPES_H="<internal/t1types.h>"          \
          -DFT_INTERNAL_POSTSCRIPT_AUX_H="<internal/psaux.h>"         \
          -DFT_INTERNAL_POSTSCRIPT_HINTS_H="<internal/pshints.h>"     \
          -DFT_INTERNAL_POSTSCRIPT_GLOBALS_H="<internal/psglobal.h>"  \
          -DFT_INTERNAL_AUTOHINT_H="<internal/autohint.h>"            \
          -DFT_ADVANCES_H="<ftadvanc.h>"                              \
          -DFT_MODULE_ERRORS_H="<ftmoderr.h>"                         \
          -DFT_ERROR_DEFINITIONS_H="<fterrdef.h>"                     \
          
COMPONENT_PRIV_INCLUDEDIRS := include/internal
 
COMPONENT_ADD_INCLUDEDIRS := include

COMPONENT_SRCDIRS := src/autofit \
                     src/base \
                     src/bdf \
                     src/bzip2 \
                     src/cache \
                     src/cff \
                     src/cid \
                     src/gxvalid \
                     src/gzip \
                     src/lzw \
                     src/otvalid \
                     src/pcf \
                     src/pfr \
                     src/psaux \
                     src/pshinter \
                     src/psnames \
                     src/raster \
                     src/sfnt \
                     src/smooth \
                     src/truetype \
                     src/type1 \
                     src/type42 \
                     src/winfonts \
                     builds/freertos \

ifeq ($(CONFIG_CHIP_NAME),BL808)
ft_s_src := builds/freertos/ftsystem_nofs.c 
else
ft_s_src := builds/freertos/ftsystem.c 
endif

PROJECT       := freetype
PROJECT_TITLE := FreeType 
SRC_DIR := src
TOP_DIR ?= $(BL_SDK_PATH)/components/freetype
OBJ_DIR ?= $(TOP_DIR)/objs
include $(TOP_DIR)/builds/toplevel.mk
BASE_DIR := $(SRC_DIR)/base
include $(TOP_DIR)/$(BASE_DIR)/rules.mk

BASE_SRC += $(BASE_DIR)/ftinit.c $(BASE_DIR)/ftbitmap.c 

include $(patsubst %,$(TOP_DIR)/src/%/rules.mk,$(MODULES))

COMPONENT_SRCS := $(AUTOF_DRV_SRC) \
                  $(BASE_SRC) \
                  $(BDF_DRV_SRC) \
                  $(BZIP2_DRV_SRC) \
                  $(CACHE_DRV_SRC) \
                  $(CFF_DRV_SRC) \
                  $(CID_DRV_SRC) \
                  $(GXV_DRV_SRC) \
                  $(LZW_DRV_SRC) \
                  $(OTV_DRV_SRC) \
                  $(PCF_DRV_SRC) \
                  $(PFR_DRV_SRC) \
                  $(PSAUX_DRV_SRC) \
                  $(PSHINTER_DRV_SRC) \
                  $(PSNAMES_DRV_SRC) \
                  $(TT_DRV_SRC) \
                  $(T1_DRV_SRC) \
                  $(T42_DRV_SRC) \
                  $(FNT_DRV_SRC) \
                  $(SFNT_DRV_SRC) \
                  $(SMOOTH_DRV_SRC) \
                  $(RASTER_DRV_SRC) \
                  $(ft_s_src) \

COMPONENT_OBJS := $(patsubst %.c,%.o, $(COMPONENT_SRCS)) 

