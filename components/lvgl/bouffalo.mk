# Component Makefile
#
## These include paths would be exported to project level

CFLAGS += -DLV_LVGL_H_INCLUDE_SIMPLE -DLV_BUILD_TEST=1 -DLV_BUILD_TEST_NO_MAIN=1

COMPONENT_ADD_INCLUDEDIRS := .
COMPONENT_ADD_INCLUDEDIRS += lvgl/
COMPONENT_ADD_INCLUDEDIRS += lvgl/src
COMPONENT_ADD_INCLUDEDIRS += lvgl/src/core
COMPONENT_ADD_INCLUDEDIRS += lvgl/src/draw
COMPONENT_ADD_INCLUDEDIRS += lvgl/src/draw/arm2d
COMPONENT_ADD_INCLUDEDIRS += lvgl/src/draw/nxp
COMPONENT_ADD_INCLUDEDIRS += lvgl/src/draw/sdl
COMPONENT_ADD_INCLUDEDIRS += lvgl/src/draw/stm32_dma2d
COMPONENT_ADD_INCLUDEDIRS += lvgl/src/draw/sw
COMPONENT_ADD_INCLUDEDIRS += lvgl/src/draw/swm341_dma2d
COMPONENT_ADD_INCLUDEDIRS += lvgl/src/font
COMPONENT_ADD_INCLUDEDIRS += lvgl/src/hal
COMPONENT_ADD_INCLUDEDIRS += lvgl/src/misc
COMPONENT_ADD_INCLUDEDIRS += lvgl/src/widgets
COMPONENT_ADD_INCLUDEDIRS += lvgl/src/extra
COMPONENT_ADD_INCLUDEDIRS += lvgl/src/extra/layouts/flex
COMPONENT_ADD_INCLUDEDIRS += lvgl/src/extra/layouts/grid
COMPONENT_ADD_INCLUDEDIRS += lvgl/src/extra/themes/
COMPONENT_ADD_INCLUDEDIRS += lvgl/src/extra/themes/basic
COMPONENT_ADD_INCLUDEDIRS += lvgl/src/extra/themes/default
COMPONENT_ADD_INCLUDEDIRS += lvgl/src/extra/themes/mono
COMPONENT_ADD_INCLUDEDIRS += lvgl/src/extra/widgets/animimg
COMPONENT_ADD_INCLUDEDIRS += lvgl/src/extra/widgets/calendar
COMPONENT_ADD_INCLUDEDIRS += lvgl/src/extra/widgets/chart
COMPONENT_ADD_INCLUDEDIRS += lvgl/src/extra/widgets/colorwheel
COMPONENT_ADD_INCLUDEDIRS += lvgl/src/extra/widgets/imgbtn
COMPONENT_ADD_INCLUDEDIRS += lvgl/src/extra/widgets/keyboard
COMPONENT_ADD_INCLUDEDIRS += lvgl/src/extra/widgets/led
COMPONENT_ADD_INCLUDEDIRS += lvgl/src/extra/widgets/list
COMPONENT_ADD_INCLUDEDIRS += lvgl/src/extra/widgets/menu
COMPONENT_ADD_INCLUDEDIRS += lvgl/src/extra/widgets/meter
COMPONENT_ADD_INCLUDEDIRS += lvgl/src/extra/widgets/msgbox
COMPONENT_ADD_INCLUDEDIRS += lvgl/src/extra/widgets/span
COMPONENT_ADD_INCLUDEDIRS += lvgl/src/extra/widgets/spinbox
COMPONENT_ADD_INCLUDEDIRS += lvgl/src/extra/widgets/spinner
COMPONENT_ADD_INCLUDEDIRS += lvgl/src/extra/widgets/tabview
COMPONENT_ADD_INCLUDEDIRS += lvgl/src/extra/widgets/tileview
COMPONENT_ADD_INCLUDEDIRS += lvgl/src/extra/widgets/win
COMPONENT_ADD_INCLUDEDIRS += lvgl/demos

#COMPONENT_ADD_INCLUDEDIRS += lv_lib_freetype
COMPONENT_ADD_INCLUDEDIRS += port

COMPONENT_SRCDIRS := .
COMPONENT_SRCDIRS := lvgl/
COMPONENT_SRCDIRS += lvgl/src
COMPONENT_SRCDIRS += lvgl/src/core
COMPONENT_SRCDIRS += lvgl/src/draw
COMPONENT_SRCDIRS += lvgl/src/draw/arm2d
COMPONENT_SRCDIRS += lvgl/src/draw/nxp
COMPONENT_SRCDIRS += lvgl/src/draw/sdl
COMPONENT_SRCDIRS += lvgl/src/draw/stm32_dma2d
COMPONENT_SRCDIRS += lvgl/src/draw/sw
COMPONENT_SRCDIRS += lvgl/src/draw/swm341_dma2d
COMPONENT_SRCDIRS += lvgl/src/font
COMPONENT_SRCDIRS += lvgl/src/hal
COMPONENT_SRCDIRS += lvgl/src/misc
COMPONENT_SRCDIRS += lvgl/src/widgets
COMPONENT_SRCDIRS += lvgl/src/extra
COMPONENT_SRCDIRS += lvgl/src/extra/layouts/flex
COMPONENT_SRCDIRS += lvgl/src/extra/layouts/grid
COMPONENT_SRCDIRS += lvgl/src/extra/themes/
COMPONENT_SRCDIRS += lvgl/src/extra/themes/basic
COMPONENT_SRCDIRS += lvgl/src/extra/themes/default
COMPONENT_SRCDIRS += lvgl/src/extra/themes/mono
COMPONENT_SRCDIRS += lvgl/src/extra/widgets/animimg
COMPONENT_SRCDIRS += lvgl/src/extra/widgets/calendar
COMPONENT_SRCDIRS += lvgl/src/extra/widgets/chart
COMPONENT_SRCDIRS += lvgl/src/extra/widgets/colorwheel
COMPONENT_SRCDIRS += lvgl/src/extra/widgets/imgbtn
COMPONENT_SRCDIRS += lvgl/src/extra/widgets/keyboard
COMPONENT_SRCDIRS += lvgl/src/extra/widgets/led
COMPONENT_SRCDIRS += lvgl/src/extra/widgets/list
COMPONENT_SRCDIRS += lvgl/src/extra/widgets/menu
COMPONENT_SRCDIRS += lvgl/src/extra/widgets/meter
COMPONENT_SRCDIRS += lvgl/src/extra/widgets/msgbox
COMPONENT_SRCDIRS += lvgl/src/extra/widgets/span
COMPONENT_SRCDIRS += lvgl/src/extra/widgets/spinbox
COMPONENT_SRCDIRS += lvgl/src/extra/widgets/spinner
COMPONENT_SRCDIRS += lvgl/src/extra/widgets/tabview
COMPONENT_SRCDIRS += lvgl/src/extra/widgets/tileview
COMPONENT_SRCDIRS += lvgl/src/extra/widgets/win
COMPONENT_SRCDIRS += lvgl/demos
COMPONENT_SRCDIRS += port
#COMPONENT_SRCDIRS += lv_lib_freetype

#COMPONENT_SRCDIRS += lvgl/tests
COMPONENT_SRCDIRS += lvgl/demos/benchmark
COMPONENT_SRCDIRS += lvgl/demos/benchmark/assets
COMPONENT_SRCDIRS += lvgl/demos/keypad_encoder
COMPONENT_SRCDIRS += lvgl/demos/music
COMPONENT_SRCDIRS += lvgl/demos/music/assets
COMPONENT_SRCDIRS += lvgl/demos/stress
COMPONENT_SRCDIRS += lvgl/demos/widgets
COMPONENT_SRCDIRS += lvgl/demos/widgets/assets


# CFLAGS += -DLV_LVGL_H_INCLUDE_SIMPLE
# CPP_DEFINE += -DCFG_STA_MAX="1"
# CPPFLAGS += -DCFG_STA_MAX="1"
# ASMFLAGS += -DportasmHANDLE_INTERRUPT=interrupt_entry
