CC=arm-none-eabi-gcc
LD=arm-none-eabi-ld
OBJCOPY=arm-none-eabi-objcopy
AS=arm-none-eabi-as

SOURCES=vector.c gpio.c timer.c nvic.c blink.c vtimer.c utils.c

FP_FLAGS ?= -msoft-float
ARCH_FLAGS = -mthumb -mcpu=cortex-m0plus $(FP_FLAGS)


BINARY = blink
LDSCRIPT ?=  $(BINARY).ld
OBJS += $(SOURCES:%.c=%.o)

##################################
# OpenOCD specific variables

OOCD ?= openocd
OOCD_INTERFACE ?= stlink-v2-1
OOCD_BOARD ?= stm32l0discovery

##################################
# C flags
CFLAGS += -O3
CFLAGS += -Wall -Werror
CFLAGS += -fno-common -ffunction-sections -fdata-sections

##################################
# LD flags

LDFLAGS += --static -nostartfiles
LDFLAGS += -T$(LDSCRIPT)
LDFLAGS += -Map=$(BINARY).map

##################################
##################################
##################################

all: elf

debug: CFLAGS += -O0 -g
debug: elf

elf: $(BINARY).elf
bin: $(BINARY).bin
hex: $(BINARY).hex

flash: $(BINARY).flash

%.bin: %.elf
	$(OBJCOPY) -Obinary $^ $@

%.hex: %.elf
	$(OBJCOPY) -Oihex $^ $@

%.elf %.map: $(OBJS) $(LDSCRIPT)
	$(LD) $(LDFLAGS) $(OBJS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(ARCH_FLAGS) -o $@ -c $^

clean:
	$(RM) *.o *.d *.elf *.bin *.hex *.map

%.flash: %.hex
	$(OOCD) -f interface/$(OOCD_INTERFACE).cfg \
					-f board/$(OOCD_BOARD).cfg \
					-c "init" -c "reset init" \
					-c "flash write_image erase $^" \
					-c "reset" \
					-c "shutdown"
