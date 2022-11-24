/******************************************************************************************
  Filename    : Mcu.c
  
  Core        : ARM Cortex®-M7
  
  MCU         : STM32H7A3ZI
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 22.11.2022
  
  Description : Mcu driver implementation
  
******************************************************************************************/
//=========================================================================================
// Includes
//=========================================================================================
#include "STM32H7x3.h"
#include "Clock.h"
#include "Mcu.h"

//-----------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param
///
/// \return
//-----------------------------------------------------------------------------
void HwInitialization(void)
{
  extern unsigned long __INTVECT_BASE_ADDRESS;
  
  /* Setup the VTOR */
  SCB->VTOR.reg = (unsigned long)&__INTVECT_BASE_ADDRESS;
  
  /* Initialize the FPU: Enable CP10 and CP11. */
  CPACR |= 0x00F00000UL;

  /* Enable ITCM and DTCM */
  ITCMCR |= 1UL;
  DTCMCR |= 1UL;

  __asm("DSB");
  __asm("ISB");

  /* Init the system clock */
  STM32H7A3ZI_InitClock();
}


