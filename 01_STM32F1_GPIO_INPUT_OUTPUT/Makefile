CFLAGS ?= -mcpu=cortex-m3 -mthumb -Wall -Wextra -Wshadow -Werror -Wundef -Wfloat-equal

LDFLAGS ?= -T link.ld -nostdlib

LIBS = -lc -lm -lgcc

SRCS = main.c gpio_driver.c
OBJS = $(SRCS:.c=.o)


$(info OBJS = $(OBJS))

# build target
build: firmware.bin


# convert ELF to binary 
firmware.bin: firmware.elf
	arm-none-eabi-objcopy -O binary $< $@


# link object files to create ELF file 
firmware.elf: $(OBJS)
	arm-none-eabi-gcc $(LDFLAGS) $^ $(LIBS) -o $@


# compile c source to object file 
main.o: main.c 
	arm-none-eabi-gcc $(CFLAGS) -c $< -o $@

gpio_driver.o: gpio_driver.c
	arm-none-eabi-gcc $(CFLAGS) -c $< -o $@


#---------------------------------


# flash firmwere to stm32
stmflash: firmware.bin
	stm32flash -w firmware.bin -v -g 0x08000000 /dev/ttyUSB0

# -w firmware.bin → Writes the firmware to Flash.
# -v → Verifies the write process.
# -g 0x08000000 → Starts execution from Flash.
# /dev/ttyUSB0 → Serial port.

# clean build artifacts
clean: 
	rm -f firmware.* *.o

# start execution from flash
execute:
	stm32flash -g 0x08000000 /dev/ttyUSB0	