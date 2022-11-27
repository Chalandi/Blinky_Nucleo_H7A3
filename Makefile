# ******************************************************************************************
#   Filename    : Makefile
#
#   Author      : Chalandi Amine
#
#   Owner       : Chalandi Amine
#
#   Date        : 22.11.2022
#
#   Description : Build system
#
# ******************************************************************************************

HW_TARGET = H7A3

PRJ_NAME = Blinky_Nucleo_$(HW_TARGET)

OUTPUT_DIR = Output

OBJ_DIR    = $(OUTPUT_DIR)/Obj

SRC_DIR = Code

AS = arm-none-eabi-as
CC = arm-none-eabi-gcc
LD = arm-none-eabi-gcc

ARMGNU = arm-none-eabi

COPS  = -mlittle-endian                               \
        -O2                                           \
        -march=armv7e-m+fpv5-d16                      \
        -mtune=cortex-m7                              \
        -mthumb                                       \
        -mfloat-abi=hard                              \
        -ffast-math                                   \
        -Wa,-adhln=$(OBJ_DIR)/$(basename $(@F)).lst   \
        -g3                                           \
        -Wconversion                                  \
        -Wsign-conversion                             \
        -Wunused-parameter                            \
        -Wuninitialized                               \
        -Wmissing-declarations                        \
        -Wshadow                                      \
        -Wunreachable-code                            \
        -Wmissing-include-dirs                        \
        -x c                                          \
        -std=c99                                      \
        -Wall                                         \
        -Wextra                                       \
        -fomit-frame-pointer                          \
        -gdwarf-2                                     \
        -fno-exceptions

ifeq ($(LD), arm-none-eabi-ld)
  LOPS = -nostartfiles                          \
         -nostdlib                              \
         -march=armv7e-m+fpv5-d16               \
         -mtune=cortex-m7                       \
         -mthumb                                \
         -mfloat-abi=hard                       \
         -ffast-math                            \
         -e Startup_Init                        \
         --print-memory-usage                   \
         --print-map                            \
         -dT $(SRC_DIR)/Memory_Map.ld           \
         -Map=$(OUTPUT_DIR)/$(PRJ_NAME).map     \
         --specs=nano.specs                     \
         --specs=nosys.specs
else
  LOPS = -nostartfiles                          \
         -e Startup_Init                        \
         -march=armv7e-m+fpv5-d16               \
         -mtune=cortex-m7                       \
         -mthumb                                \
         -mfloat-abi=hard                       \
         -ffast-math                            \
         -Wl,--print-memory-usage               \
         -Wl,--print-map                        \
         -Wl,-dT $(SRC_DIR)/Memory_Map.ld       \
         -Wl,-Map=$(OUTPUT_DIR)/$(PRJ_NAME).map \
         --specs=nano.specs                     \
         --specs=nosys.specs
endif


SRC_FILES :=  $(SRC_DIR)/mcal/Cache          \
              $(SRC_DIR)/mcal/Clock          \
              $(SRC_DIR)/mcal/Mcu            \
              $(SRC_DIR)/mcal/SysTick        \
              $(SRC_DIR)/IntVect             \
              $(SRC_DIR)/main                \
              $(SRC_DIR)/Startup


INC_FILES :=  $(SRC_DIR)/mcal                \
              $(SRC_DIR)

VPATH := $(subst \,/,$(sort $(dir $(SRC_FILES)) $(OBJ_DIR)))

FILES_O := $(addprefix $(OBJ_DIR)/, $(notdir $(addsuffix .o, $(SRC_FILES))))


ifeq ($(MAKECMDGOALS),build)
-include $(subst .o,.d,$(FILES_O))
endif

build : $(OUTPUT_DIR)/$(PRJ_NAME).elf

all : $(OUTPUT_DIR)/$(PRJ_NAME).elf


.PHONY : clean
clean :
	@-rm -rf $(OUTPUT_DIR) *.o    2>/dev/null || true
	@-rm -rf $(OUTPUT_DIR) *.hex  2>/dev/null || true
	@-rm -rf $(OUTPUT_DIR) *.elf  2>/dev/null || true
	@-rm -rf $(OUTPUT_DIR) *.list 2>/dev/null || true
	@-rm -rf $(OUTPUT_DIR) *.map  2>/dev/null || true
	@-rm -rf $(OUTPUT_DIR) *.txt  2>/dev/null || true
	@-mkdir -p $(subst \,/,$(OBJ_DIR))

$(OBJ_DIR)/%.o : %.c
	@-echo +++ compile: $(subst \,/,$<) to $(subst \,/,$@)
	@-$(CC) $(COPS) $(addprefix -I, $(INC_FILES)) -c $< -o $(OBJ_DIR)/$(basename $(@F)).o 2> $(OBJ_DIR)/$(basename $(@F)).err

$(OBJ_DIR)/%.o : %.s
	@-echo +++ compile: $(subst \,/,$<) to $(subst \,/,$@)
	@$(AS) $< -o $(OBJ_DIR)/$(basename $(@F)).o


$(OBJ_DIR)/%.o : %.cpp
	@-echo +++ compile: $(subst \,/,$<) to $(subst \,/,$@)
	@$(CC) $(COPS) -I$(INC_FILES) $< -o $(OBJ_DIR)/$(basename $(@F)).o

$(OUTPUT_DIR)/$(PRJ_NAME).elf : $(FILES_O)
	@$(LD) $(LOPS) $(FILES_O) -o $(OUTPUT_DIR)/$(PRJ_NAME).elf
	@$(ARMGNU)-objdump -D $(OUTPUT_DIR)/$(PRJ_NAME).elf > $(OUTPUT_DIR)/$(PRJ_NAME).list
	@$(ARMGNU)-objcopy $(OUTPUT_DIR)/$(PRJ_NAME).elf -O ihex $(OUTPUT_DIR)/$(PRJ_NAME).hex
