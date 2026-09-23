# Toolchain
CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size

# Compiler Flags
CFLAGS  = -mcpu=cortex-m3 -mthumb -Wall -O2 -ffreestanding -nostdlib
LDFLAGS = -T link.ld -nostdlib -lgcc 

# Files
SOURCES = main.c startup.c gpio_driver.c stm32f10x.c systick_driver.c usart_driver.c spi_driver.c i2c_driver.c adc_driver.c help_func.c
OBJECTS = $(SOURCES:.c=.o)
TARGET  = firmware

# Build Rules
all: $(TARGET).elf $(TARGET).bin

$(TARGET).elf: $(OBJECTS) link.ld
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)
	$(SIZE) $@

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

main.o: stm32f10x.h gpio_driver.h systick_driver.h usart_driver.h spi_driver.h i2c_driver.h adc_driver.h help_func.h
gpio_driver.o: gpio_driver.h
stm32f10x.o: stm32f10x.h
systick_driver.o: systick_driver.h
usart_driver.o: usart_driver.h
spi_driver.o: spi_driver.h
i2c_driver.o: i2c_driver.h
adc_driver.o: adc_driver.h
help_func.o: help_func.h

clean:
	rm -f $(OBJECTS) $(TARGET).elf $(TARGET).bin

# flash firmwere to stm32
stmflash: firmware.bin
	stm32flash -w firmware.bin -v -g 0x08000000 /dev/ttyUSB0

# -w firmware.bin → Writes the firmware to Flash.
# -v → Verifies the write process.
# -g 0x08000000 → Starts execution from Flash.
# /dev/ttyUSB0 → Serial port.


# start execution from flash
execute:
	stm32flash -g 0x08000000 /dev/ttyUSB0	