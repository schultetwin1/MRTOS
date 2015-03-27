CC=arm-none-eabi-gcc
LD=arm-none-eabi-ld
OBJCOPY=arm-none-eabi-objcopy
AS=arm-none-eabi-as

VERSION = RELEASE

SOURCES=vector.c gpio.c timer.c nvic.c main.c vtimer.c utils.c rcc.c queue.c task.c
ASM=port_task.s

FP_FLAGS ?= -msoft-float
ARCH_FLAGS = -mthumb -mcpu=cortex-m0plus


BINARY = main

ifeq "$(VERSION)" "RELEASE"
	BUILD_DIR = build/release
else
ifeq "$(VERSION)" "DEBUG"
	BUILD_DIR = build/debug
	CFLAGS += -O0 -g
endif
endif

LDSCRIPT ?=  $(BINARY).ld

OBJS = $(SOURCES:%.c=$(BUILD_DIR)/%.o) $(ASM:%.s=$(BUILD_DIR)/%.o)


##################################
# OpenOCD specific variables

OOCD ?= openocd
OOCD_INTERFACE ?= stlink-v2-1
OOCD_BOARD ?= stm32l0discovery

##################################
# C flags
CFLAGS += -O3
CFLAGS += -Wall -Werror
CFLAGS += -fno-common -ffunction-sections -fdata-sections -fomit-frame-pointer

##################################
# LD flags

LDFLAGS += --static -nostartfiles
LDFLAGS += -T$(LDSCRIPT)
LDFLAGS += -Map=$(BUILD_DIR)/$(BINARY).map

##################################
##################################
##################################

.PRECIOUS: $(OBJS)

all: elf


elf: $(BUILD_DIR)/$(BINARY).elf
bin: $(BUILD_DIR)/$(BINARY).bin
hex: $(BUILD_DIR)/$(BINARY).hex

flash: $(BUILD_DIR)/$(BINARY).flash

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf
	$(OBJCOPY) -Obinary $^ $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf
	$(OBJCOPY) -Oihex $^ $@

$(BUILD_DIR)/%.elf $(BUILD_DIR)/%.map: $(BUILD_DIR) $(OBJS) $(LDSCRIPT)
	$(LD) $(LDFLAGS) $(OBJS) -o $@

$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $(ARCH_FLAGS) $(FP_FLAGS) -o $@ -c $^

$(BUILD_DIR)/%.o: %.s
	$(AS) $(ARCH_FLAGS) $^ -o $@ 

$(BUILD_DIR):
	mkdir -p $@

clean:
	$(RM) -r build

$(BUILD_DIR)/%.flash: $(BUILD_DIR)/%.hex
	$(OOCD) -f interface/$(OOCD_INTERFACE).cfg \
					-f board/$(OOCD_BOARD).cfg \
					-c "init" -c "reset init" \
					-c "flash write_image erase $^" \
					-c "reset" \
					-c "shutdown"
