/************************************************************************************************************
  Filename    : memlib.s
  
  Core        : ARM Cortex®-M

  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 01.12.2022
  
  Description : bare metal implementation of memcpy and memclr using 32-bytes memory block alignement

************************************************************************************************************/

.file "memlib.s"

.syntax unified

.cpu cortex-m7

/*******************************************************************************/
/* void memlib_32BytesAlign_memcpy(void *dest, const void * src, size_t size) */
/*******************************************************************************/

.thumb_func
.section ".text", "ax"
.align 2
.globl memlib_32BytesAlign_memcpy
.type  memlib_32BytesAlign_memcpy, % function

memlib_32BytesAlign_memcpy:
                            cbz r2, .L_exit_memcpy
                            push {r4-r11}
.L_copy:                    ldm r1!, {r4-r11}
                            stm r0!, {r4-r11}
                            adds r2, r2, #-32
                            bne .L_copy
                            pop  {r4-r11}
.L_exit_memcpy:
                            bx lr


/*******************************************************************************/
/* void memlib_32BytesAlign_memclr(void *src, size_t size) */
/*******************************************************************************/

.thumb_func
.section ".text", "ax"
.align 2
.globl memlib_32BytesAlign_memclr
.type  memlib_32BytesAlign_memclr, % function

memlib_32BytesAlign_memclr:
                            cbz r1, .L_exit_memclr
                            push {r4-r11}
                            mov r4, #0
                            mov r5, #0
                            mov r6, #0
                            mov r7, #0
                            mov r8, #0
                            mov r9, #0
                            mov r10, #0
                            mov r11, #0
.L_clear:                   stm r0!, {r4-r11}
                            adds r1, r1, #-32
                            bne .L_clear
                            pop  {r4-r11}
.L_exit_memclr:
                            bx lr
