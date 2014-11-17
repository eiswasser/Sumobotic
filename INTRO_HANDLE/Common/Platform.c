/**
 * \file
 * \brief Platform implementation module.
 * \author Marco Bürgi, Pascal Giger
 *
 * In this part the modules from the platform are initializing
 * This includes the initializing of the platform and defined all macros, which
 * are going to use in the connection with the different projects
 */

/*! \brief implements the defined interface
 */
#include "Platform.h"

/*! \brief implements the necessary interface if LEDs are in use
 */
#if PL_USE_LED
	#include "LED.h"
#endif

/*! \brief implements the necessary interface if Events are in use
 */
#if PL_HAS_EVENTS
	#include "Event.h"
#endif

/*! \brief implements the necessary interface if Keys are in use
 */
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
#if PL_HAS_DEBOUNCE
	#include "Debounce.h"
	#include "KeyDebounce.h"
#endif
#if PL_HAS_RTOS
	#include "RTOS.h"
#endif
#if PL_HAS_SHELL
	#include "Shell.h"
#endif
#if PL_HAS_SHELL_QUEUE
	#include "ShellQueue.h"
#endif
#if PL_HAS_SEMAPHORE
	#include "Sem.h"
#endif
#if PL_HAS_LINE_SENSOR
	#include "Reflectance.h"
#endif
#if PL_HAS_MOTOR
	#include "Motor.h"
#endif
#if PL_HAS_MCP4728
	#include "MCP4728.h"
#endif

/*! \brief implements the initial method for the board
 */
void PL_Init(void) {
#if PL_USE_LED
	LED_Init();
#endif
#if PL_HAS_EVENTS
	EVNT_Init();
#endif
#if PL_HAS_KEYS
	KEY_Init();
#endif
#if PL_HAS_MEALY
	MEALY_Init();
#endif
#if PL_HAS_TRIGGER
	TRG_Init();
#endif
#if PL_HAS_BUZZER
	BUZ_Init();
#endif
#if PL_HAS_DEBOUNCE
	DBNC_Init();
	KEYDBNC_Init();
#endif
#if PL_HAS_RTOS
	RTOS_Init();
#endif
#if PL_HAS_SHELL
	SHELL_Init();
#endif
#if PL_HAS_SHELL_QUEUE
	SQUEUE_Init();
#endif
#if PL_HAS_SEMAPHORE
	SEM_Init();
#endif
#if PL_HAS_LINE_SENSOR
	REF_Init();
#endif
#if PL_HAS_MOTOR
	MOT_Init();
#endif
#if PL_HAS_MCP4728
	MCP4728_Init();
#endif
}

/*! \brief implements the de-initial methods for the board
 */
void PL_Deinit(void) {
#if PL_USE_LED
  LED_Deinit();
#endif
#if PL_HAS_EVENTS
  EVNT_Deinit();
#endif
#if PL_HAS_KEYS
  KEY_Deinit();
#endif
#if PL_HAS_MEALY
  MEALY_Deinit();
#endif
#if PL_HAS_TRIGGER
  TRG_Deinit();
#endif
#if PL_HAS_BUZZER
  BUZ_Deinit();
#endif
#if PL_HAS_DEBOUNCE
  DBNC_Deinit();
  KEYDBNC_Deinit();
#endif
#if PL_HAS_RTOS
  RTOS_Deinit();
#endif
#if PL_HAS_SHELL
	SHELL_Deinit();
#endif
#if PL_HAS_SHELL_QUEUE
	SQUEUE_Deinit();
#endif
#if PL_HAS_SEMAPHORE
	SEM_Deinit();
#endif
#if PL_HAS_LINE_SENSOR
	REF_Deinit();
#endif
#if PL_HAS_MOTOR
	MOT_Deinit();
#endif
#if PL_HAS_MCP4728
	MCP4728_Deinit();
#endif
}
