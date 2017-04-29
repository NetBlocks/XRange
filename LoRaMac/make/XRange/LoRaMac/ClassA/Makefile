########################################################
# Makefile by NetBlocks.eu
# XRange LoRa Module (sx1272): 
# www.netblocks.eu/xrange-sx1272-lora-datasheet/
########################################################
# Path to gcc
GCC_PATH = /usr/bin/
# Path to st-flash tool
FLASH_PATH = /usr/bin/st-flash

########################################################
# target
########################################################
TARGET = classA

########################################################
# building variables
########################################################
# optimization
OPT = -O2

#########################################################
# pathes
#########################################################
# source path
# Build path
BUILD_DIR = build

########################################################
# source
########################################################
C_SOURCES = \
  ../../../../src/boards/mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_adc.c \
  ../../../../src/boards/mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_adc_ex.c \
  ../../../../src/boards/mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal.c \
  ../../../../src/boards/mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_comp.c \
  ../../../../src/boards/mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_cortex.c \
  ../../../../src/boards/mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_crc.c \
  ../../../../src/boards/mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_cryp.c \
  ../../../../src/boards/mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_cryp_ex.c \
  ../../../../src/boards/mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_dac.c \
  ../../../../src/boards/mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_dac_ex.c \
  ../../../../src/boards/mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_dma.c \
  ../../../../src/boards/mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_flash.c \
  ../../../../src/boards/mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_flash_ex.c \
  ../../../../src/boards/mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_flash_ramfunc.c \
  ../../../../src/boards/mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_gpio.c \
  ../../../../src/boards/mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_i2c.c \
  ../../../../src/boards/mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_i2s.c \
  ../../../../src/boards/mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_irda.c \
  ../../../../src/boards/mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_iwdg.c \
  ../../../../src/boards/mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_lcd.c \
  ../../../../src/boards/mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_msp_template.c \
  ../../../../src/boards/mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_nor.c \
  ../../../../src/boards/mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_opamp.c \
  ../../../../src/boards/mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_opamp_ex.c \
  ../../../../src/boards/mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_pcd.c \
  ../../../../src/boards/mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_pcd_ex.c \
  ../../../../src/boards/mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_pwr.c \
  ../../../../src/boards/mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_pwr_ex.c \
  ../../../../src/boards/mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_rcc.c \
  ../../../../src/boards/mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_rcc_ex.c \
  ../../../../src/boards/mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_rtc.c \
  ../../../../src/boards/mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_rtc_ex.c \
  ../../../../src/boards/mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_sd.c \
  ../../../../src/boards/mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_smartcard.c \
  ../../../../src/boards/mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_spi.c \
  ../../../../src/boards/mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_spi_ex.c \
  ../../../../src/boards/mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_sram.c \
  ../../../../src/boards/mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_tim.c \
  ../../../../src/boards/mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_tim_ex.c \
  ../../../../src/boards/mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_uart.c \
  ../../../../src/boards/mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_usart.c \
  ../../../../src/boards/mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_wwdg.c \
  ../../../../src/boards/mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_ll_fsmc.c \
  ../../../../src/boards/mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_ll_sdmmc.c \
  ../../../../src/boards/XRange/adc-board.c \
  ../../../../src/boards/XRange/board.c \
  ../../../../src/boards/XRange/gpio-board.c \
  ../../../../src/boards/XRange/i2c-board.c \
  ../../../../src/boards/XRange/rtc-board.c \
  ../../../../src/boards/XRange/spi-board.c \
  ../../../../src/boards/XRange/sx1272-board.c \
  ../../../../src/boards/XRange/uart-board.c \
  ../../../../src/mac/LoRaMac.c \
  ../../../../src/mac/LoRaMacCrypto.c \
  ../../../../src/radio/sx1272/sx1272.c \
  ../../../../src/system/adc.c \
  ../../../../src/system/delay.c \
  ../../../../src/system/eeprom.c \
  ../../../../src/system/fifo.c \
  ../../../../src/system/gpio.c \
  ../../../../src/system/i2c.c \
  ../../../../src/system/timer.c \
  ../../../../src/system/uart.c \
  ../../../../src/system/crypto/aes.c \
  ../../../../src/system/crypto/cmac.c \
  ../../../../src/boards/XRange/cmsis/system_stm32l1xx.c \
  ../../../../src/boards/mcu/stm32/utilities.c \
  ../../../../src/apps/LoRaMac/classA/XRange/main.c
ASM_SOURCES = \
  ../../../../src/boards/XRange/cmsis/arm-gcc/startup_stm32l151xc.s
  

#######################################
# binaries
#######################################
PREFIX  = $(GCC_PATH)arm-none-eabi-
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
AR = $(PREFIX)ar
SZ = $(PREFIX)size
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
 
#########################################################
# CFLAGS
#########################################################
# macros for gcc
AS_DEFS =
C_DEFS =  -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32L151xC -DUSE_BAND_868 -DUSE_MODEM_LORA
# includes for gcc
AS_INCLUDES =
C_INCLUDES = -I ../../../../src/boards/XRange/cmsis
C_INCLUDES += -I../../../../src/boards/mcu/stm32/cmsis
C_INCLUDES += -I../../../../src/boards/mcu/stm32/
C_INCLUDES += -I../../../../src/radio
C_INCLUDES += -I../../../../src/boards/XRange
C_INCLUDES += -I../../../../src/boards/mcu/stm32/STM32L1xx_HAL_Driver/Inc
C_INCLUDES += -I../../../../src/mac
C_INCLUDES += -I../../../../src/radio/sx1272
C_INCLUDES += -I../../../../src/system/crypto
C_INCLUDES += -I../../../../src/system
# compile gcc flags
WFLAGS = -Wall -fdata-sections -ffunction-sections -fmessage-length=0 -c
ASFLAGS = -mthumb -mcpu=cortex-m3 $(AS_DEFS) $(AS_INCLUDES) $(OPT) $(WFLAGS)
CFLAGS = -std=c99 -mthumb -mcpu=cortex-m3 -fno-aggressive-loop-optimizations $(C_DEFS) $(C_INCLUDES) $(OPT) $(WFLAGS)
# Generate dependency information
CFLAGS += -MD -MP -MF .dep/$(@F).d

#########################################################
# LDFLAGS
#########################################################
# link script
LDSCRIPT = "../../../../src/boards/XRange/cmsis/arm-gcc/STM32L151CC_FLASH.ld"
# libraries
LIBS = -lc -lm -lnosys
LIBS += 
LIBDIR =
CC_VER := $(shell $(CC) -dumpversion)
ifeq "$(CC_VER)" "4.8.2"
	LDSPECS = -specs=nosys.specs 
else
	LDSPECS = -specs=nano.specs -specs=nosys.specs 
endif
LDFLAGS = -mthumb -mcpu=cortex-m3 $(LDSPECS) -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections,--no-wchar-size-warning

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin

#########################################################
# build the application
#########################################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	@echo "C. Compiling $@..."
	@$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	@echo "S. Compiling $@..."
	@$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	@echo "C. Linking $@..."
	@$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	@echo "H. Linking $@..."
	@$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	@echo "B. Building $@..."
	@$(BIN) $< $@	
	@echo "Used gcc: "$(CC_VER)
	
$(BUILD_DIR):
	mkdir -p $@		

#########################################################
# clean up
#########################################################
clean:
	-rm -fR .dep $(BUILD_DIR)
  
#########################################################
# Code::Blocks commands:
#########################################################
Release: all flash
Debug: CFLAGS += -g -gdwarf-2
Debug: all
cleanDebug: clean
cleanRelease: clean
flash:
	$(FLASH_PATH) erase
	$(FLASH_PATH) --reset write $(BUILD_DIR)/$(TARGET).bin 0x8000000

#########################################################
# dependencies
#########################################################
-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)

# *** EOF ***
