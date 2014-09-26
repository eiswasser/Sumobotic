/**
 * \file
 * \brief Platform implementation module.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This implements the platform module. 
 * Here the platform gets initialized, and all platform dependent macros get defined.
 */

#include "Platform.h"
#if PL_HAS_LED
  #include "LED.h"
#endif

void PL_Init(void) {
#if PL_HAS_LED
  LED_Init();
#endif  
}

void PL_Deinit(void) {
#if PL_HAS_LED
  LED_Deinit();
#endif
}
