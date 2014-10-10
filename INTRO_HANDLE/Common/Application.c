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
#if PL_HAS_EVENT
	#include "Event.h"
#endif
#if PL_HAS_TIMER
	#include "Timer.h"
#endif

/*! \brief Function that only is a support for the Event handling, to show that the events
 *  have been initialized
 *
 *
 */
static void APP_HandleEvent(EVNT_Handle event){
	switch(event){
	case EVNT_INIT:
		LED1_On();
		WAIT1_Waitms(100);
		LED1_Off();
		break;
	case EVNT_LED_HEARTBEAT:
		LED2_On();
		WAIT1_Waitms(100);
		LED2_Off();
	//case:

	default:
		break;
	}
}

/*! \brief Loop function, which call the handling function which checks if an event is set
 */
static void APP_Loop(void){
	for(;;){
		#if PL_HAS_EVENT
			EVNT_HandleEvent(APP_HandleEvent);
		#endif
		WAIT1_Waitms(100);
	}
}

/*! \brief Startup function
 * 	initial the whole platform, sets an Event and call the loop() function
 */
void APP_Start() {
	PL_Init(); /* platform initialization */
	EVNT_SetEvent(EVNT_INIT);
	APP_Loop();
#if 0
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
#endif
}
