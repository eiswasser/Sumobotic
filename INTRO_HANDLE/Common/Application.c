/**
 * \file
 * \brief Main application module.
 * \author Marco Bürgi, Pascal Giger
 *
 * In this part the main application module is implementing
 * This module runs all applications and create the different tasks
 */

#include "Platform.h"
#include "Application.h"
#include "WAIT1.h"
#if PL_USE_LED
  #include "LED.h"
#endif

void APP_Start(void) {
	PL_Init(); /* platform initialization */
	for(;;) {
		for (int i = 10; i > 0; --i) {
			LED1_On();
			WAIT1_Waitms(i*100);
			LED1_Off();
			LED2_On();
			WAIT1_Waitms(i*100);
			LED2_Off();
			LED3_On();
			WAIT1_Waitms(i*100);
			LED3_Off();
		}
  }
}
