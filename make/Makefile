#####################################
# Configure
#####################################
BINPATH =/c/gcc-arm/bin

######################################
# C & Headers
######################################
C_SOURCES = \
			$(wildcard \
			../src/*.c \
			../make/*.c \
			../ven/*.c \
			) \

C_OBJS = $(patsubst %c, %o, $(C_SOURCES))

TARGET = stm32f103c8t6
DEBUG = 0
OPT =

BUILD_DIR = build
C_INCLUDES_DIR= \
				$(wildcard \
				../src \
				../ven \
				../make \
				)
C_INCLUDES= \
			$(patsubst %,-I%,$(C_INCLUDES_DIR)) \
			-I. \


#######################################
# binaries
#######################################
PREFIX = arm-none-eabi-
CC = $(BINPATH)/$(PREFIX)gcc
AS = $(BINPATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(BINPATH)/$(PREFIX)objcopy
AR = $(BINPATH)/$(PREFIX)ar
SZ = $(BINPATH)/$(PREFIX)size
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

MCU = -mcpu=cortex-m3 -mthumb

ASFLAGS = $(MCU) $(OPT) -Wall -fdata-sections -ffunction-sections
CFLAGS = $(MCU) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

#ifeq ($(DEBUG), 1)
	#CFLAGS += -g -gdwarf-2
#endif

# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"

# ASM sources
ASM_SOURCES =  \
			   stm32f103c8t6.s

#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = stm32f103c8t6.ld

# libraries
LIBS = -lc -lm -lnosys
LIBDIR =
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin


#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_OBJS)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
	vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	$(CC) --std=c11 -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@

$(BUILD_DIR):
	mkdir $@

#######################################
# clean up
#######################################
clean:
	-rm -fR .dep $(BUILD_DIR)

#######################################
# st-flash write
#######################################
write: all
	-st-flash --reset write ./build/stm32f103c8t6.bin 0x8000000

flash: write



#######################################
# dependencies
#######################################
-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)

# *** EOF ***
