# Toolchain
CC = arm-none-eabi-gcc

# Target
TARGET = stm32f446re

# Architecture
CFLAGS = -mcpu=cortex-m4 \
         -march=armv7e-m \
         -mthumb \
         -O0 -g \
         -std=c99 \
         -mfpu=fpv4-sp-d16 \
         -mfloat-abi=hard \
         -save-temps #Generates all the different stages when generating the binary source code.

# Include paths
INCLUDES =	-I../drivers/header/dma \
			-I../drivers/header/rcc \
			-I../drivers/header/exti \
			-I../drivers/header/gpio \
			-I../drivers/header/timer \
			-I../drivers/header/systick \
			-I../drivers/header/utility \
			-I../drivers/header/system \
			-I../drivers/header/usart \
			-I../drivers/CMSIS/Core/Include \
			-I../drivers/CMSIS/Device/Include \
			-I../drivers/unit-test/header
# -I../drivers/header/net/wiznet-5100

# Source files
SRCS = ../drivers/source/dma/*.c \
      	../drivers/source/rcc/*.c \
		../drivers/source/exti/*.c \
		../drivers/source/gpio/*.c \
		../drivers/source/timer/*.c \
		../drivers/source/systick/*.c \
		../drivers/source/usart/*.c \
		../drivers/source/utility/*.c \
		../drivers/source/system/*.c \
      	../drivers/source/init-stm32f446re/*.c \
		../drivers/unit-test/source/*.c \
		../drivers/unit-test/main-test.c \
		../drivers/source/handlers/*.c
#driver-test/*.c
#../drivers/source/net/wiznet-5100/*.c

# Hal source section.
SRCS += ../drivers/stm32f4-HAL/Src/stm32f4xx_hal_spi.c \
		../drivers/stm32f4-HAL/Src/stm32f4xx_hal.c \
		../drivers/stm32f4-HAL/Src/stm32f4xx_hal_gpio.c \
		../drivers/stm32f4-HAL/Src/stm32f4xx_hal_dma.c \
		../drivers/stm32f4-HAL/Src/stm32f4xx_hal_cortex.c

# Hal Include section.
INCLUDES += -I../drivers/stm32f4-HAL/Inc

# Linker flags
LDFLAGS = -Tmy_script.ld \
          -Wl,-Map=firmware.map \
          -L../drivers/CMSIS/Lib -lCMSIS 

# Build rule
all: $(TARGET)

$(TARGET):

	$(CC) $(CFLAGS) $(INCLUDES) $(SRCS) $(LDFLAGS) -o $@

	arm-none-eabi-objcopy -O binary $(TARGET) $(TARGET).bin

clean:
	rm -f *.elf *.map *.i *.s *.o $(TARGET) $(TARGET).bin
