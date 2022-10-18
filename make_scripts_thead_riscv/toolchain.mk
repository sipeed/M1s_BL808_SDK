##change to your toolchain path
CONFIG_TOOLPREFIX ?= $(BL_SDK_PATH)/toolchain/$(shell uname |cut -d '_' -f1)_$(shell uname -m)/bin/riscv64-unknown-elf-
