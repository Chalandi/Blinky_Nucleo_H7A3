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
SRC_DIR    = Code

############################################################################################
# Toolchain
############################################################################################

AS      = arm-none-eabi-as
CC      = arm-none-eabi-gcc
LD      = arm-none-eabi-gcc
OBJDUMP = arm-none-eabi-objdump
OBJCOPY = arm-none-eabi-objcopy
READELF = arm-none-eabi-readelf

PYTHON = python

############################################################################################
# Optimization Compiler flags
############################################################################################

OPT_MODIFIED_O2 = -O1                                          \
                  -falign-functions  -falign-jumps             \
                  -falign-labels  -falign-loops                \
                  -fcaller-saves                               \
                  -fcode-hoisting                              \
                  -fcrossjumping                               \
                  -fcse-follow-jumps  -fcse-skip-blocks        \
                  -fdelete-null-pointer-checks                 \
                  -fdevirtualize  -fdevirtualize-speculatively \
                  -fexpensive-optimizations                    \
                  -ffinite-loops                               \
                  -fgcse  -fgcse-lm                            \
                  -fhoist-adjacent-loads                       \
                  -finline-functions                           \
                  -finline-small-functions                     \
                  -findirect-inlining                          \
                  -fipa-bit-cp  -fipa-cp  -fipa-icf            \
                  -fipa-ra  -fipa-sra  -fipa-vrp               \
                  -fisolate-erroneous-paths-dereference        \
                  -flra-remat                                  \
                  -foptimize-sibling-calls                     \
                  -foptimize-strlen                            \
                  -fpartial-inlining                           \
                  -fpeephole2                                  \
                  -freorder-blocks-algorithm=stc               \
                  -frerun-cse-after-loop                       \
                  -fschedule-insns  -fschedule-insns2          \
                  -fsched-interblock  -fsched-spec             \
                  -fstore-merging                              \
                  -fstrict-aliasing                            \
                  -fthread-jumps                               \
                  -ftree-builtin-call-dce                      \
                  -ftree-loop-vectorize                        \
                  -ftree-pre                                   \
                  -ftree-slp-vectorize                         \
                  -ftree-switch-conversion  -ftree-tail-merge  \
                  -ftree-vrp                                   \
                  -fvect-cost-model=cheap

NO_OPT = -O0

OPT = $(OPT_MODIFIED_O2)

############################################################################################
# C Compiler flags
############################################################################################

COPS  = -mlittle-endian                               \
        -mlong-calls                                  \
        $(OPT)                                        \
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

############################################################################################
# C++ Compiler flags
############################################################################################

CPPOPS  = -mlittle-endian                               \
          -mlong-calls                                  \
          $(OPT)                                        \
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
          -fomit-frame-pointer                          \
          -gdwarf-2                                     \
          -fno-exceptions                               \
          -x c++                                        \
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

############################################################################################
# Source Files
############################################################################################

SRC_FILES :=  $(SRC_DIR)/mcal/Cache          \
              $(SRC_DIR)/mcal/Clock          \
              $(SRC_DIR)/mcal/Mcu            \
              $(SRC_DIR)/mcal/SysTick        \
              $(SRC_DIR)/IntVect             \
              $(SRC_DIR)/main                \
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
	@$(CC) $(CPPOPS) -I$(INC_FILES) $< -o $(OBJ_DIR)/$(basename $(@F)).o 2> $(OBJ_DIR)/$(basename $(@F)).err
	@-$(PYTHON) CompilerErrorFormater.py $(OBJ_DIR)/$(basename $(@F)).err -COLOR

$(OUTPUT_DIR)/$(PRJ_NAME).elf : $(FILES_O)
	@$(LD) $(LOPS) $(FILES_O) -o $(OUTPUT_DIR)/$(PRJ_NAME).elf
	@$(OBJDUMP) -D $(OUTPUT_DIR)/$(PRJ_NAME).elf > $(OUTPUT_DIR)/$(PRJ_NAME).list
	@$(OBJCOPY) $(OUTPUT_DIR)/$(PRJ_NAME).elf -O ihex $(OUTPUT_DIR)/$(PRJ_NAME).hex
	@$(READELF) -S -s $(OUTPUT_DIR)/$(PRJ_NAME).elf > $(OUTPUT_DIR)/$(PRJ_NAME).readelf

