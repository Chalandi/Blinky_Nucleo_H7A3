/******************************************************************************************
  Filename    : SysTick.c
  
  Core        : ARM Cortex®-M7

  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 22.11.2022
  
  Description : SysTick timer driver implementation
  
******************************************************************************************/

//=========================================================================================
// Includes
//=========================================================================================
#include "SysTick.h"

//-----------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param
///
/// \return
//-----------------------------------------------------------------------------
void SysTick_Init(void)
{
  pSTK_CTRL->u32Register     = 0;
  pSTK_LOAD->bits.u24RELOAD  = OS_SYS_TICK_MS(400);
  pSTK_VAL->u32Register      = 0;
  pSTK_CTRL->bits.u1CLOCKSRC = SYS_TICK_CLKSRC_AHB_DIV_8;
  pSTK_CTRL->bits.u1TICKINT  = SYS_TICK_ENABLE_INT;
}

//-----------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param
///
/// \return
//-----------------------------------------------------------------------------
void SysTick_Start(void)
{
  pSTK_CTRL->bits.u1ENABLE = SYS_TICK_ENABLE_TIMER;
}
