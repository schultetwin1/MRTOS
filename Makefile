CC=arm-none-eabi-gcc
LD=arm-none-eabi-ld
OBJCOPY=arm-none-eabi-objcopy
AS=arm-none-eabi-as

BUILD_DIR = build/release
VERSION ?= RELEASE
ifeq "$(VERSION)" "RELEASE"
	BUILD_DIR = build/release
	CFLAGS += -O3
else
ifeq "$(VERSION)" "DEBUG"
	BUILD_DIR = build/debug
	CFLAGS += -O0 -g
endif
endif

PORT_DIR ?= port/gcc/m0+

SRCS := $(wildcard *.c) $(wildcard drivers/*.c) $(PORT_DIR)/port_task.s
HDRS := $(wildcard include/*.h drivers/*.h)
OBJS := $(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(basename $(notdir $(SRCS)))))

FP_FLAGS ?= -msoft-float
ARCH_FLAGS = -mthumb -mcpu=cortex-m0plus


BINARY = main

LDSCRIPT ?=  $(PORT_DIR)/$(BINARY).ld

##################################
# OpenOCD specific variables

OOCD ?= openocd
OOCD_INTERFACE ?= stlink-v2-1
OOCD_BOARD ?= stm32l0discovery

##################################
# C flags
CFLAGS += -Wall -Werror -Iinclude -Idrivers
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

$(BUILD_DIR)/%.o: %.c Makefile
	$(CC) $(CFLAGS) $(ARCH_FLAGS) $(FP_FLAGS) -o $@ -c $<

$(BUILD_DIR)/%.o: drivers/%.c Makefile
	$(CC) $(CFLAGS) $(ARCH_FLAGS) $(FP_FLAGS) -o $@ -c $<

$(BUILD_DIR)/%.o: $(PORT_DIR)/%.s Makefile
	$(CC) $(CFLAGS) $(ARCH_FLAGS) $(FP_FLAGS) -o $@ -c $<

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
