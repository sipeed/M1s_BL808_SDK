# Component Makefile
#
## These include paths would be exported to project level
COMPONENT_ADD_INCLUDEDIRS += algorithm/include firmware/include api/include dsp2_drv/include dsp2_hal/include

## not be exported to project level
COMPONENT_PRIV_INCLUDEDIRS := dsp2_drv/dsp2_reg

## This component's src


COMPONENT_SRCDIRS := algorithm/lib\
					 firmware/src\
					 api/src\
					 dsp2_drv/src \
					 dsp2_hal/src \

COMPONENT_ADD_LDFLAGS_HEAD := -Wl,--whole-archive
COMPONENT_ADD_LDFLAGS_TAIL := -Wl,--no-whole-archive


LIBS ?= dsp2_algorithm
COMPONENT_ADD_LDFLAGS += -L$(COMPONENT_PATH)/algorithm/lib $(addprefix -l,$(LIBS))
ALL_LIB_FILES := $(patsubst %,$(COMPONENT_PATH)/algorithm/lib/lib%.a,$(LIBS))
COMPONENT_ADD_LINKER_DEPS := $(ALL_LIB_FILES)

