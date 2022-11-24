
//=========================================================================================
// Includes
//=========================================================================================
#include "Leds.h"
#include "SysTick.h"
#include "Cache.h"

//=========================================================================================
// Globals
//=========================================================================================
volatile LedTreeBitCounter xLedCounter = {.reg = 0};

//=========================================================================================
// Externs
//=========================================================================================
void Isr_SysTick_IRQn(void);

//-----------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param
///
/// \return
//-----------------------------------------------------------------------------
int main(void)
{
  /* Enable the Cache-I and Cache-D */
  Cache_EnableICache();
  Cache_EnableDCache();

  /* Configure the led gpio */
  LED_G_CONFIGURE();
  LED_Y_CONFIGURE();
  LED_R_CONFIGURE();

  /* Configure and start the systick timer */
  SysTick_Init();
  SysTick_Start();

  /* Endless loop */
  for(;;);

  return 0;
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
void Isr_SysTick_IRQn(void)
{
  xLedCounter.reg++;

  LED_G_SET(xLedCounter.bits.bit0);
  LED_Y_SET(xLedCounter.bits.bit1);
  LED_R_SET(xLedCounter.bits.bit2);

}
