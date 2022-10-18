# Component Makefile
#
## These include paths would be exported to project level
COMPONENT_ADD_INCLUDEDIRS += mm_lib/include \
							 sample_common/include \
							 file_sink/include \
							 motion_detect/include \
							 sample/include \
							 test/include \
							 mm_drv/include \
							 mm_hal/include \

COMPONENT_PRIV_INCLUDEDIRS := mm_drv/mm_reg

## This component's src
COMPONENT_SRCDIRS :=  mm_drv mm_hal mm_lib sample_common file_sink motion_detect sample test


##
#CPPFLAGS +=
