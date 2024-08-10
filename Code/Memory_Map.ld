/******************************************************************************************
  Filename    : Memory_Map.ld

  Core        : ARM Cortex-M7

  MCU         : STM32H7A3ZI

  Author      : Chalandi Amine

  Owner       : Chalandi Amine

  Date        : 22.11.2022

  Description : Linker description file for STM32H7A3ZI

******************************************************************************************/

INPUT(libc.a)

OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)

/******************************************************************************************
 Globals
******************************************************************************************/
__SYS_STACK_SIZE = 1K;

FLASH_START_ADDRESS         = 0x08000000;
FLASH_LENGTH                = 2M;

AXI_SRAM1_START_ADDRESS     = 0x24000000;
AXI_SRAM1_LENGTH            = 256K;

AXI_SRAM2_START_ADDRESS     = 0x24040000;
AXI_SRAM2_LENGTH            = 384K;

AXI_SRAM3_START_ADDRESS     = 0x240A0000;
AXI_SRAM3_LENGTH            = 384K;

AHB_SRAM1_START_ADDRESS     = 0x30000000;
AHB_SRAM1_LENGTH            = 64K;

AHB_SRAM2_START_ADDRESS     = 0x30010000;
AHB_SRAM2_LENGTH            = 64K;

SRAM_DTCM_START_ADDRESS     = 0x20000000;
SRAM_DTCM_LENGTH            = 128K;

SRAM_ITCM_START_ADDRESS     = 0x00000000;
SRAM_ITCM_LENGTH            = 64K;


/******************************************************************************************
 Memory configuration
******************************************************************************************/

MEMORY
{
#ifdef VARIANT_EXECUTE_CODE_FROM_ITCM
  ITCM(rx)  : ORIGIN = SRAM_ITCM_START_ADDRESS, LENGTH = SRAM_ITCM_LENGTH
#endif
  ROM(rx)   : ORIGIN = FLASH_START_ADDRESS, LENGTH = FLASH_LENGTH
  RAM(rwx)  : ORIGIN = SRAM_DTCM_START_ADDRESS, LENGTH = SRAM_DTCM_LENGTH
}

/******************************************************************************************
 Sections definition
******************************************************************************************/
SECTIONS
{
#ifdef VARIANT_EXECUTE_CODE_FROM_ITCM
   /* Boot sector (Flash) */
   .boot : ALIGN(4)
   {
     *(.ExceptionTable)
     *Startup.o(.text)
     *Clock.o(.text)
     *Mcu.o(.text)
     *memlib.o(.text)
   } > ROM

  /* Interrupt vector table */
  .intvect : ALIGN(4)
  {
    PROVIDE(__INTVECT_BASE_ADDRESS = .) ;
    *(.intvect)
    KEEP(*(.intvect))
    . = ALIGN(32);
  } > ITCM  AT>ROM
  
  /* Program code (text) */
  .text : ALIGN(4)
  {
    *(.text)
    . = ALIGN(32);
    *(.text*)
    . = ALIGN(32);
    *(.progmem*)
    . = ALIGN(32);
    *(.glue_7)
    . = ALIGN(32);
    *(.glue_7t)
    . = ALIGN(32);
  } > ITCM  AT>ROM

  /* Read-only data (.rodata) */
  .rodata : ALIGN(4)
  {
    *(.rodata)
    . = ALIGN(32);
    *(.rodata*)
    . = ALIGN(32);
  } > ITCM  AT>ROM
#else
  /* Interrupt vector table */
  .intvect : ALIGN(4)
  {
    PROVIDE(__INTVECT_BASE_ADDRESS = .) ;
    *(.intvect)
    KEEP(*(.intvect))
    . = ALIGN(32);
  } > ROM
  
  /* Program code (text) */
  .text : ALIGN(4)
  {
    *(.text)
    . = ALIGN(32);
    *(.text*)
    . = ALIGN(32);
    *(.progmem*)
    . = ALIGN(32);
    *(.glue_7)
    . = ALIGN(32);
    *(.glue_7t)
    . = ALIGN(32);
  } > ROM

  /* Read-only data (.rodata) */
  .rodata : ALIGN(4)
  {
    *(.rodata)
    . = ALIGN(32);
    *(.rodata*)
    . = ALIGN(32);
  } > ROM
#endif
 /* Section for constructors */
  .ctors : ALIGN(4)
  {
    __CTOR_LIST__ = . ;
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array))
    LONG(-1) ;
    __CTOR_END__ = . ;
  }  > ROM


  /* Section for destructors */
  .dtors : ALIGN(4)
  {
    __DTOR_LIST__ = . ;
    KEEP (*(SORT(.dtors.*)))
    KEEP (*(.dtors))
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array))
    LONG(-1) ;
    __DTOR_END__ = . ;
  } > ROM

  /* Runtime clear table */
  .clear_sec : ALIGN(4)
  {
    PROVIDE(__RUNTIME_CLEAR_TABLE = .) ;
    LONG(0 + ADDR(.bss));   LONG(SIZEOF(.bss));
    LONG(-1);               LONG(-1);
  } > ROM

  /* Runtime copy table */
  .copy_sec : ALIGN(4)
  {
    PROVIDE(__RUNTIME_COPY_TABLE = .) ;
#ifdef VARIANT_EXECUTE_CODE_FROM_ITCM
    /* RAM CODE (ITCM) */
    LONG(LOADADDR(.intvect)); LONG(0 + ADDR(.intvect)); LONG(SIZEOF(.intvect));
    LONG(LOADADDR(.text));    LONG(0 + ADDR(.text));    LONG(SIZEOF(.text));
    LONG(LOADADDR(.rodata));  LONG(0 + ADDR(.rodata));  LONG(SIZEOF(.rodata));
#endif
    /* RAM DATA */
    LONG(LOADADDR(.data));  LONG(0 + ADDR(.data));  LONG(SIZEOF(.data));
    LONG(-1);                 LONG(-1);                  LONG(-1);
  } > ROM

  .ARM.extab : ALIGN(4)
  {
    *(.ARM.extab)
    . = ALIGN(32);
    *(.ARM.extab*)
    . = ALIGN(32);
    *(.gnu.linkonce.armextab.*)
    . = ALIGN(32);
  } > ROM

  .exidx : ALIGN(4)
  {
    PROVIDE(__exidx_start = .);
    *(.ARM.exidx*)
    . = ALIGN(32);
    PROVIDE(__exidx_end = .);
    . = ALIGN(32);
  } > ROM

  .ARM.attributes : ALIGN(4)
  {
    *(.ARM.attributes)
    . = ALIGN(32);
  } > ROM

  /* The ROM-to-RAM initialized data section */
  .data : ALIGN(4)
  {
    *(.data)
    . = ALIGN(32);
  } > RAM  AT>ROM

  /* The uninitialized (zero-cleared) bss section */
  .bss : ALIGN(4)
  {
    *(.bss)
    . = ALIGN(32);
  } > RAM

  PROVIDE(end = .);
  PROVIDE(_fini = .);

  /* user-system mode stack definition */
  .stack :
  {
    . = ALIGN(MAX(__SYS_STACK_SIZE , .), 8);
    PROVIDE(__SYS_STACK_TOP = .) ;
  } > RAM
}
