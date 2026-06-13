CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size

TARGET = main
DEFS = -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER 
CFLAGS = -mcpu=cortex-m3 -mthumb -O2 -g -Wall $(DEFS)

INCLUDES = -ICMSIS -IStdPeriph/inc -IUser

SRCS = $(wildcard CMSIS/*.c) \
       $(wildcard StdPeriph/src/*.c) \
       $(wildcard User/*.c) \
       CMSIS/startup_stm32f10x_md.s

LDSCRIPT = stm32_flash.ld
LDFLAGS = -mcpu=cortex-m3 -mthumb --specs=nano.specs -T$(LDSCRIPT) -Wl,-Map=$(TARGET).map,--gc-sections

all: $(TARGET).elf $(TARGET).bin

$(TARGET).elf: $(SRCS)
	@$(CC) $(CFLAGS) $(INCLUDES) $^ $(LDFLAGS) -o $@
	@$(SIZE) $@

$(TARGET).bin: $(TARGET).elf
	@$(OBJCOPY) -O binary $< $@

clean:
	rm -f $(TARGET).elf $(TARGET).bin $(TARGET).map compile_commands.json

flash: $(TARGET).bin
	openocd -f interface/stlink.cfg -f target/stm32f1x.cfg -c "program $(TARGET).bin verify reset exit"

.PHONY: all clean flash
