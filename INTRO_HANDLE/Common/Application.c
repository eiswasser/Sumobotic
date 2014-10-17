/**
 * \file
 * \brief Main application module.
 * \author Marco B�rgi, Pascal Giger
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
#if PL_HAS_EVENTS
	#include "Event.h"
#endif
#if PL_HAS_TIMER
	#include "Timer.h"
#endif
#if PL_HAS_KEYS
	#include "Keys.h"
#endif
#if PL_HAS_MEALY
	#include "Mealy.h"
#endif
#if PL_HAS_SHELL
	#include "CLS1.h"
#endif

#if PL_IS_FRDM
/*! \brief Function that only is a support for the Event handling, to show that the events
 *  have been initialized
 *
 *
 */
static void APP_HandleEvent(EVNT_Handle event){
	switch(event){
	case EVNT_INIT:
		CLS1_SendStr("Hello World\n",CLS1_GetStdio()->stdOut);
		break;
	case EVNT_LED_HEARTBEAT:
		LED2_Neg();
		break;
#if PL_NOF_KEYS >= 1
	case EVNT_SW1_PRESSED:
		CLS1_SendStr("button 1 pressed\n",CLS1_GetStdio()->stdOut);
		break;
#endif
#if PL_NOF_KEYS >= 2
	case EVNT_SW2_PRESSED:
		CLS1_SendStr("button 2 pressed\n",CLS1_GetStdio()->stdOut);
		break;
#endif
#if PL_NOF_KEYS >= 3
	case EVNT_SW3_PRESSED:
		CLS1_SendStr("button 3 pressed\n",CLS1_GetStdio()->stdOut);
		break;
#endif
#if PL_NOF_KEYS >= 4
	case EVNT_SW4_PRESSED:
		CLS1_SendStr("button 4 pressed\n",CLS1_GetStdio()->stdOut);
		break;
#endif
#if PL_NOF_KEYS >= 5
	case EVNT_SW5_PRESSED:
		CLS1_SendStr("button 5 pressed\n",CLS1_GetStdio()->stdOut);
		break;
#endif
#if PL_NOF_KEYS >= 6
	case EVNT_SW6_PRESSED:
		CLS1_SendStr("button 6 pressed\n",CLS1_GetStdio()->stdOut);
		break;
#endif
#if PL_NOF_KEYS >= 7
	case EVNT_SW7_PRESSED:
		CLS1_SendStr("button 7 pressed\n",CLS1_GetStdio()->stdOut);
		break;
#endif
	default:
		break;
	}
}

/*! \brief Loop function, which call the handling function which checks if an event is set
 */
static void APP_Loop_FRDM(void){
	for(;;){
		#if PL_HAS_EVENTS
			EVNT_HandleEvent(APP_HandleEvent);
		#endif
		#if PL_HAS_KEYS
			KEY_Scan();
		#endif
		WAIT1_Waitms(10);
	}
}
#endif

#if PL_IS_ROBO
static void APP_HandleEvent(EVNT_Handle event){
	switch(event){
	case EVNT_INIT:
		LED1_On();
		WAIT1_Waitms(50);
		LED1_Off();
		LED2_On();
		WAIT1_Waitms(50);
		LED2_Off();
		break;
	case EVNT_LED_HEARTBEAT:
		LED1_Neg();
		LED2_Neg();
		break;
#if PL_NOF_KEYS >= 1
	case EVNT_SW1_PRESSED:
		CLS1_SendStr("button 1 pressed\n",CLS1_GetStdio()->stdOut);
		break;
#endif
	}
}

/*! \brief Loop function, which call the handling function which checks if an event is set
 */
static void APP_Loop_ROBO(void){
	for(;;){
		#if PL_HAS_EVENTS
			EVNT_HandleEvent(APP_HandleEvent);
		#endif
		#if PL_HAS_KEYS
			KEY_Scan();
		#endif
		WAIT1_Waitms(10);
	}
}
#endif

/*! \brief Startup function
 * 	initial the whole platform, sets an Event and call the loop() function
 */
void APP_Start() {
	PL_Init(); /* platform initialization */
	EVNT_SetEvent(EVNT_INIT);
#if PL_IS_FRDM
	APP_Loop_FRDM();
#endif
#if PL_IS_ROBO
	APP_Loop_ROBO();
#endif
	for(;;){
	#if PL_HAS_MEALY && 0
		MEALY_Step();
	#elif 0
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
	PL_Deinit();
}
