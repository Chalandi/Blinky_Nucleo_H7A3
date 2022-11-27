/******************************************************************************************
  Filename    : Cache.c
  
  Core        : ARM Cortex®-M7
  
  MCU         : STM32H7A3ZI
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 24.11.2022
  
  Description : Cache maintenance driver implementation
  
******************************************************************************************/

//=========================================================================================
// Includes
//=========================================================================================
#include "STM32H7x3.h"
#include "Cache.h"


//-----------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param
///
/// \return
//-----------------------------------------------------------------------------
void Cache_EnableICache(void)
{
  if(!SCB->CCR.bit.IC)
  {
    __asm("DSB");
    __asm("ISB");

    /* Invalidate the instruction cache */
    ICIALLU->reg = 0UL;
    __asm("DSB");
    __asm("ISB");

    /* Enable the Instruction cache */
    SCB->CCR.bit.IC = 1u;
    __asm("DSB");
    __asm("ISB");
  }
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
void Cache_DisableICache(void)
{
  if(SCB->CCR.bit.IC)
  {
    __asm("DSB");
    __asm("ISB");

    /* Disable the Instruction cache */
    SCB->CCR.bit.IC = 0u;
    __asm("DSB");
    __asm("ISB");

    /* Invalidate the instruction cache */
    ICIALLU->reg = 0UL;
    __asm("DSB");
    __asm("ISB");
  }
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
void Cache_InvalidateICache(void)
{
  __asm("DSB");
  __asm("ISB");

  /* Invalidate the instruction cache */
  ICIALLU->reg = 0UL;

  __asm("DSB");
  __asm("ISB");
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
void Cache_EnableDCache(void)
{
  uint32 sets = 0;
  uint32 ways = 0;

  if(!SCB->CCR.bit.DC)
  {
    /* Enable selection of data cache */
    CSSELR->reg = 0;
    __asm("DSB");

    /* Invalidate the data cache */
    sets = CCSIDR->bits.NumSets;
    __asm("DSB");
    do
    {
      ways = CCSIDR->bits.Associativity;
      __asm("DSB");
      do
      {
        DCISW->reg = (ways << 30u) | (sets << 5u);
        __asm("DSB");
      }while(ways-- != 0);
      __asm("DSB");
    
    }while(sets-- != 0);
    __asm("DSB");

    /* Enable the data cache */
    SCB->CCR.bit.DC = 1u;
    __asm("DSB");
    __asm("ISB");
  }
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
void Cache_DisableDCache(void)
{
  uint32 sets = 0;
  uint32 ways = 0;

  if(SCB->CCR.bit.DC)
  {
    /* Enable selection of data cache */
    CSSELR->reg = 0;
    __asm("DSB");

    /* Disable the data cache */
    SCB->CCR.bit.DC = 0u;
    __asm("DSB");
    __asm("ISB");

    /* Clean and invalidate the data cache */
    sets = CCSIDR->bits.NumSets;
    do
    {
      ways = CCSIDR->bits.Associativity;
      __asm("DSB");
      do
      {
        DCCISW->reg = (ways << 30u) | (sets << 5u);
        __asm("DSB");
      }while(ways-- != 0);
    
    }while(sets-- != 0);
    
    __asm("DSB");
    __asm("ISB");
  }
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
void Cache_InvalidateDCache(void)
{
  uint32 sets = 0;
  uint32 ways = 0;

  /* Enable selection of data cache */
  CSSELR->reg = 0;
  __asm("DSB");

  /* Invalidate the data cache */
  sets = CCSIDR->bits.NumSets;
  do
  {
    ways = CCSIDR->bits.Associativity;
    __asm("DSB");
    do
    {
      DCISW->reg = (ways << 30u) | (sets << 5u);
      __asm("DSB");
    }while(ways-- != 0);
  
  }while(sets-- != 0);
  
  __asm("DSB");
  __asm("ISB");
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
void Cache_CleanDCache(void)
{
  uint32 sets = 0;
  uint32 ways = 0;

  /* Enable selection of data cache */
  CSSELR->reg = 0;
  __asm("DSB");

  /* Clean the data cache */
  sets = CCSIDR->bits.NumSets;
  do
  {
    ways = CCSIDR->bits.Associativity;
    __asm("DSB");
    do
    {
      DCCSW->reg = (ways << 30u) | (sets << 5u);
      __asm("DSB");
    }while(ways-- != 0);
  
  }while(sets-- != 0);
  
  __asm("DSB");
  __asm("ISB");
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
void Cache_CleanInvlaidateDCache(void)
{
  uint32 sets = 0;
  uint32 ways = 0;

  /* Enable selection of data cache */
  CSSELR->reg = 0;
  __asm("DSB");

  /* Clean and invalidate the data cache */
  sets = CCSIDR->bits.NumSets;
  do
  {
    ways = CCSIDR->bits.Associativity;
    __asm("DSB");
    do
    {
      DCCISW->reg = (ways << 30u) | (sets << 5u);
      __asm("DSB");
    }while(ways-- != 0);
  
  }while(sets-- != 0);
  
  __asm("DSB");
  __asm("ISB");
}

