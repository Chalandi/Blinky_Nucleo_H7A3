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

############################################################################################
# Defines
############################################################################################

HW_TARGET  = H7A3
PRJ_NAME   = Blinky_Nucleo_$(HW_TARGET)
OUTPUT_DIR = Output
OBJ_DIR    = $(OUTPUT_DIR)/Obj
LD_SCRIPT  = $(OUTPUT_DIR)/$(PRJ_NAME).ld
SRC_DIR    = Code

############################################################################################
# Variant
############################################################################################
EXECUTE_CODE_FROM_ITCM  = -DVARIANT_EXECUTE_CODE_FROM_ITCM
EXECUTE_CODE_FROM_FLASH = -DVARIANT_EXECUTE_CODE_FROM_FLASH

# Select which variant you want to use
VARIANT = $(EXECUTE_CODE_FROM_FLASH)

############################################################################################
# Toolchain
############################################################################################

AS      = arm-none-eabi-as
CC      = arm-none-eabi-gcc
CPP     = arm-none-eabi-g++
LD      = arm-none-eabi-gcc
OBJDUMP = arm-none-eabi-objdump
OBJCOPY = arm-none-eabi-objcopy
READELF = arm-none-eabi-readelf

PYTHON = python3

############################################################################################
# Optimization Compiler flags
############################################################################################

OPT_MODIFIED_O2 = -O2                               \
                  -fno-reorder-blocks-and-partition \
                  -fno-reorder-functions

NO_OPT = -O0

OPT = $(OPT_MODIFIED_O2)

############################################################################################
# GCC Compiler verbose flags
############################################################################################

VERBOSE_GCC = -frecord-gcc-switches -fverbose-asm

############################################################################################
# C Compiler flags
############################################################################################

COPS  = -mlittle-endian                               \
        -mlong-calls                                  \
        $(OPT)                                        \
        $(VARIANT)                                    \
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
        -std=c11                                      \
        -Wall                                         \
        -Wextra                                       \
        -fomit-frame-pointer                          \
        -gdwarf-2                                     \
        -fno-exceptions

############################################################################################
# C++ Compiler flags
############################################################################################

CPPOPS  = -mlittle-endian                               \
          -mlong-calls                                  \
          $(OPT)                                        \
          $(VARIANT)                                    \
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
          -Wall                                         \
          -Wextra                                       \
          -Wpedantic                                    \
          -fomit-frame-pointer                          \
          -gdwarf-2                                     \
          -fno-exceptions                               \
          -x c++                                        \
          -std=c++20                                    \
          -fno-rtti                                     \
          -fno-use-cxa-atexit                           \
          -fno-nonansi-builtins                         \
          -fno-threadsafe-statics                       \
          -fno-enforce-eh-specs                         \
          -ftemplate-depth=128                          \
          -Wzero-as-null-pointer-constant

############################################################################################
# Assembler flags
############################################################################################

ASOPS =  -march=armv7e-m+fpv5-d16 \
         -mlittle-endian          \
         -mthumb                  \
         -alh 

############################################################################################
# Linker flags
############################################################################################

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
         -dT $(LD_SCRIPT)                       \
         -Map=$(OUTPUT_DIR)/$(PRJ_NAME).map     \
         --specs=nano.specs                     \
         --specs=nosys.specs
else
  LOPS = -nostartfiles                          \
         -nostdlib                              \
         -e Startup_Init                        \
         -march=armv7e-m+fpv5-d16               \
         -mtune=cortex-m7                       \
         -mthumb                                \
         -mfloat-abi=hard                       \
         -ffast-math                            \
         -Wl,--print-memory-usage               \
         -Wl,--print-map                        \
         -Wl,-dT $(LD_SCRIPT)                   \
         -Wl,-Map=$(OUTPUT_DIR)/$(PRJ_NAME).map \
         --specs=nano.specs                     \
         --specs=nosys.specs
endif

############################################################################################
# Source Files
############################################################################################

SRC_FILES :=  $(SRC_DIR)/mcal/Cache          \
              $(SRC_DIR)/mcal/Clock          \
              $(SRC_DIR)/mcal/Mcu            \
              $(SRC_DIR)/mcal/SysTick        \
              $(SRC_DIR)/delete              \
              $(SRC_DIR)/IntVect             \
              $(SRC_DIR)/main                \
              $(SRC_DIR)/memlib              \
              $(SRC_DIR)/shapes              \
              $(SRC_DIR)/Startup

############################################################################################
# Include Paths
############################################################################################
INC_FILES :=  $(SRC_DIR)/mcal                \
              $(SRC_DIR)

############################################################################################
# Rules
############################################################################################

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
	@-$(PYTHON) CompilerErrorFormater.py $(OBJ_DIR)/$(basename $(@F)).err -COLOR

$(OBJ_DIR)/%.o : %.s
	@-echo +++ compile: $(subst \,/,$<) to $(subst \,/,$@)
	@$(AS) $(ASOPS) $< -o $(OBJ_DIR)/$(basename $(@F)).o 2> $(OBJ_DIR)/$(basename $(@F)).err >$(OBJ_DIR)/$(basename $(@F)).lst
	@-$(PYTHON) CompilerErrorFormater.py $(OBJ_DIR)/$(basename $(@F)).err -COLOR

$(OBJ_DIR)/%.o : %.cpp
	@-echo +++ compile: $(subst \,/,$<) to $(subst \,/,$@)
	@$(CPP) $(CPPOPS) $(addprefix -I, $(INC_FILES)) -c $< -o $(OBJ_DIR)/$(basename $(@F)).o 2> $(OBJ_DIR)/$(basename $(@F)).err
	@-$(PYTHON) CompilerErrorFormater.py $(OBJ_DIR)/$(basename $(@F)).err -COLOR

$(OUTPUT_DIR)/$(PRJ_NAME).elf : $(FILES_O) $(LD_SCRIPT)
	@$(LD) $(LOPS) $(FILES_O) -o $(OUTPUT_DIR)/$(PRJ_NAME).elf
	@$(OBJDUMP) -D $(OUTPUT_DIR)/$(PRJ_NAME).elf > $(OUTPUT_DIR)/$(PRJ_NAME).list
	@$(OBJCOPY) $(OUTPUT_DIR)/$(PRJ_NAME).elf -O ihex $(OUTPUT_DIR)/$(PRJ_NAME).hex
	@$(READELF) -S -s $(OUTPUT_DIR)/$(PRJ_NAME).elf > $(OUTPUT_DIR)/$(PRJ_NAME).readelf

$(LD_SCRIPT) : $(SRC_DIR)/Memory_Map.ld
	@$(CC) -E -P -C -x c $(VARIANT) $(SRC_DIR)/Memory_Map.ld > $(LD_SCRIPT)
