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
#if PL_HAS_TRIGGER
	#include "Trigger.h"
#endif
#if PL_HAS_BUZZER
	#include "Buzzer.h"
#endif
#if PL_HAS_RTOS
	#include "RTOS.h"
#endif
#if PL_HAS_SHELL
	#include "Shell.h"
#endif
#if PL_HAS_DRIVE
	#include "Drive.h"
#endif
#if PL_COMP_ENABLE
	#include "Competition.h"
#endif


#if PL_HAS_RADIO
	#include "CLS1.h"
#endif
#if PL_IS_FRDM
	/*! \brief Function that only is a support for the Event handling, to show that the events
	 *  have been initialized
	 */
	void APP_HandleEvent(EVNT_Handle event){
		switch(event){
		case EVNT_INIT:
			SHELL_SendString("FRDM is ready\n");
		break;
		case EVNT_LED_HEARTBEAT:
			LED2_Neg();
		break;
	#if PL_NOF_KEYS >= 1
		case EVNT_SW1_PRESSED:
			#if PL_SEND_TEXT
			SHELL_SendString("button 1 pressed\n");
			#endif
			break;
	#endif
	#if PL_NOF_KEYS >= 2
		case EVNT_SW2_PRESSED:
			#if PL_SEND_TEXT
			SHELL_SendString("button 2 pressed\n");
			#endif
			break;
	#endif
	#if PL_NOF_KEYS >= 3
		case EVNT_SW3_PRESSED:
			#if PL_SEND_TEXT
			SHELL_SendString("button 3 pressed\n");
			#endif
			break;
	#endif
	#if PL_NOF_KEYS >= 4
		case EVNT_SW4_PRESSED:
			#if PL_SEND_TEXT
			SHELL_SendString("button 4 pressed\n");
			#endif
			break;
	#endif
	#if PL_NOF_KEYS >= 5
		case EVNT_SW5_PRESSED:
			#if PL_SEND_TEXT
			SHELL_SendString("button 5 pressed\n");
			#endif
			break;
	#endif
	#if PL_NOF_KEYS >= 6
		case EVNT_SW6_PRESSED:
			#if PL_SEND_TEXT
			SHELL_SendString("button 6 pressed\n");
			#endif
			break;
	#endif
	#if PL_NOF_KEYS >= 7
		case EVNT_SW7_PRESSED:
			#if PL_SEND_TEXT
			SHELL_SendString("button 7 pressed\n");
			#endif
			break;
	#endif
		default:
			break;
		}
	}
#endif

#if PL_IS_ROBO
	void APP_HandleEvent(EVNT_Handle event){
		switch(event){
			case EVNT_INIT:
				LED1_On();
				LED2_On();
				#if PL_SEND_TEXT
				SHELL_SendString("ROBO is ready\n");
				#endif
				TRG_SetTrigger(TRG_LED_INIT_OFF,50/TMR_TICK_MS,LED_Off_TRG,NULL);
			break;
			case EVNT_LED_HEARTBEAT:
				LED1_Neg();
				LED2_Neg();
			break;
			case EVNT_STOP_ENGINE:
			#if PL_HAS_DRIVE
			  	DRV_SetSpeed(0,0);				// Sets the value to zero for the speed
			  	DRV_EnableDisable(FALSE);		// Disable the Drive Module, because not in use; also resets the PID parameters
		 	#else
			  	MOT_StopMotor();
			#endif
				break;
			#if PL_NOF_KEYS >= 1
				case EVNT_SW1_PRESSED:
					TRG_SetTrigger(TRG_START_COMP,5000/TMR_TICK_MS,COMP_SetState,NULL);
					BUZ_Beep(900,1000);
				break;
			#endif
		}
	}
#endif

void APP_DebugPrint(unsigned char *str) {
	#if PL_HAS_SHELL
	  CLS1_SendStr(str, CLS1_GetStdio()->stdOut);
	#endif
}

/*! \brief Startup function
 * 	initial the whole platform, sets an Event and call the loop() function
 */
void APP_Start() {
	PL_Init(); /* platform initialization */
	EVNT_SetEvent(EVNT_INIT);
	#if PL_HAS_RTOS
		RTOS_Run();
	#endif
	PL_Deinit();
}
