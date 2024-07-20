
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
volatile unsigned int cpt = 0;
//=========================================================================================
// Externs
//=========================================================================================
void Isr_SysTick_IRQn(void);

extern void shapes_draw_circle(void);

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

  /* Test the non-trivlal use of the C++ language in the project. */
  shapes_draw_circle();

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
  if(++cpt == 4)
  {
   xLedCounter.reg++;
   LED_G_SET(xLedCounter.bits.bit0);
   LED_Y_SET(xLedCounter.bits.bit1);
   LED_R_SET(xLedCounter.bits.bit2);
   cpt = 0;
  }
}
