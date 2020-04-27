#
#	Makefile for FreeRTOS demo on Raspberry Pi
#
BASE=$(shell pwd)/
BUILD_DIR=$(shell pwd)/build/

MODULE_NAME="RaspberryPi BSP"

TARGETS=kernel.img kernel.list kernel.syms kernel.elf kernel.hex kernel.map
LINKER_SCRIPT=raspberrypi.ld

-include .dbuild/dbuild.mk

#
# all: kernel.list kernel.img kernel.syms kernel.hex
	# @$(SIZE) kernel.elf
all: kernel.img

kernel.img: LDFLAGS += -L "/usr/lib/gcc/arm-none-eabi/6.3.1" -lgcc
kernel.img: LDFLAGS += -L "/usr/lib/arm-none-eabi/lib" -lc -lm
kernel.img: $(OBJECTS)
		$(Q)$(LD) $(OBJECTS) -T $(LINKER_SCRIPT) $(LDFLAGS)

# kernel.img: kernel.elf
# 	$(Q)$(PRETTY) IMAGE $(MODULE_NAME) $@
# 	$(Q)$(OBJCOPY) kernel.elf -O binary $@
#
# kernel.hex: kernel.elf
# 	$(Q)$(PRETTY) HEX $(MODULE_NAME) $@
# 	$(Q)$(OBJCOPY) kernel.elf -O ihex $@
#
# kernel.list: kernel.elf
# 	$(Q)$(PRETTY) LIST $(MODULE_NAME) $@
# 	$(Q)$(OBJDUMP) -D -S  kernel.elf > $@
#
# kernel.syms: kernel.elf
# 	$(Q)$(PRETTY) SYMS $(MODULE_NAME) $@
# 	$(Q)$(OBJDUMP) -t kernel.elf > $@
#
# kernel.elf: LDFLAGS += -L "/usr/lib/gcc/arm-none-eabi/6.3.1" -lgcc
# kernel.elf: LDFLAGS += -L "/usr/lib/arm-none-eabi/lib" -lc
# kernel.elf: $(OBJECTS)
# 		$(Q)$(LD) $(OBJECTS) -Map kernel.map -o $@ -T $(LINKER_SCRIPT) $(LDFLAGS)
