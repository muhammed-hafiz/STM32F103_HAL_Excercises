# Toolchain
CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size

# Compiler Flags
CFLAGS  = -mcpu=cortex-m3 -mthumb -Wall -O2 -ffreestanding -nostdlib
LDFLAGS = -T stm32f103c8t6.ld -nostdlib

# Files
SOURCES = main.c startup.c
OBJECTS = $(SOURCES:.c=.o)
TARGET  = firmware

# Build Rules
all: $(TARGET).elf $(TARGET).bin

$(TARGET).elf: $(OBJECTS) stm32f103c8t6.ld
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)
	$(SIZE) $@

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET).elf $(TARGET).bin
