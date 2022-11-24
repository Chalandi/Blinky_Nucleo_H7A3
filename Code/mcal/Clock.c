/******************************************************************************************
  Filename    : Clock.c
  
  Core        : ARM Cortex®-M7
  
  MCU         : STM32H7A3ZI
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 22.11.2022
  
  Description : Clock driver implementation
  
******************************************************************************************/

//=========================================================================================
// Includes
//=========================================================================================
#include "STM32H7x3.h"
#include "Clock.h"

//-----------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param
///
/// \return
//-----------------------------------------------------------------------------
void STM32H7A3ZI_InitClock(void)
{
  /* Configure flash wait state (280 MHz --> 6 WS)*/
  Flash->ACR.bit.LATENCY = 6u;

  /* Configure PLL1 */
  RCC->PLLCKSELR.bit.DIVM1    = 32u;
  RCC->PLLCFGR.bit.PLL1RGE    = 0u;
  RCC->PLLCFGR.bit.PLL1VCOSEL = 0u;
  RCC->PLLCFGR.bit.PLL1FRACEN = 0u;

  RCC->PLLCFGR.bit.DIVP1EN = 1u;
  RCC->PLLCFGR.bit.DIVQ1EN = 1u;
  RCC->PLLCFGR.bit.DIVR1EN = 1u;

  RCC->PLL1DIVR.bit.DIVN1 = 279u; /* VCO = 560 MHz       */
  RCC->PLL1DIVR.bit.DIVP1 = 1u;   /* pll1_p_ck = 280 MHz */
  RCC->PLL1DIVR.bit.DIVQ1 = 1u;   /* pll1_q_ck = 280 MHz */
  RCC->PLL1DIVR.bit.DIVR1 = 1u;   /* pll1_r_ck = 280 MHz */

  /* Enable PLL1 */
  RCC->CR.bit.PLL1ON = 1u;

  /* Wait for PLL1 to become ready */
  while(!RCC->CR.bit.PLL1RDY);

  /* Set pll1_p_ck as system clock */
  RCC->CFGR.bit.SW = 3u;

  /* Wait for pll1_p_ck to become system clock*/
  while(RCC->CFGR.bit.SWS != 3u);

  /* Enable GPIOs clock */
  RCC->AHB4ENR.bit.GPIOBEN = 1u;
  RCC->AHB4ENR.bit.GPIOEEN = 1u;
}

