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
INCLUDES =	-I../header/dma \
			-I../header/rcc \
			-I../header/exti \
			-I../header/gpio \
			-I../header/timer \
			-I../header/systick \
			-I../header/utility \
			-I../header/system \
			-I../header/usart \
			-I../header/net/wiznet-5100 \
			-I../CMSIS/Core/Include \
			-I../CMSIS/Device/Include \
			-I../unit-test/header

# Source files
SRCS = ../source/dma/*.c \
      	../source/rcc/*.c \
		../source/exti/*.c \
		../source/gpio/*.c \
		../source/timer/*.c \
		../source/systick/*.c \
		../source/usart/*.c \
		../source/utility/*.c \
		../source/system/*.c \
		../source/net/wiznet-5100/*.c \
      	../source/init-stm32f446re/*.c \
		../unit-test/source/*.c \
		../unit-test/main-test.c \
		../source/handlers/*.c \
		#driver-test/*.c

# Hal source section.
SRCS += ../stm32f4-HAL/Src/stm32f4xx_hal_spi.c \
		../stm32f4-HAL/Src/stm32f4xx_hal.c \
		../stm32f4-HAL/Src/stm32f4xx_hal_gpio.c \
		../stm32f4-HAL/Src/stm32f4xx_hal_dma.c \
		../stm32f4-HAL/Src/stm32f4xx_hal_cortex.c

# Hal Include section.
INCLUDES += -I../stm32f4-HAL/Inc

# Linker flags
LDFLAGS = -Tmy_script.ld \
          -Wl,-Map=firmware.map \
          -L../CMSIS/Lib -lCMSIS 

# Build rule
all: $(TARGET)

$(TARGET):

	$(CC) $(CFLAGS) $(INCLUDES) $(SRCS) $(LDFLAGS) -o $@

	arm-none-eabi-objcopy -O binary $(TARGET) $(TARGET).bin

clean:
	rm -f *.elf *.map *.i *.s *.o $(TARGET) $(TARGET).bin
