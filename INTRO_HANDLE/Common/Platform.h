/**
 * \file
 * \brief Platform Interface.
 * \author Marco B�rgi, Pascal Giger
 *
 * In this part the platform interface is implementing
 * This includes the initializing of the platform and defining all macros, which
 * are going to use in the connection with the different projects
 */

#ifndef __PLATFORM_H_
#define __PLATFORM_H_

#include "PE_Types.h" /* for common Processor Expert types used throughout the project*/
#include "PE_Error.h" /* global error constants */
#include <stddef.h>   /* for NULL */

/*! \brief List of the different boards which are in use for the project.
 *
 * This gives the opportunity to chose afterwards one of the boards in the code line.
 * The name is written as plattform_board_is_xx - PL_BOARD_IS_xx
 * The compiler option from the projects defines the following macros.
 */
#define PL_IS_FRDM	(defined(PL_BOARD_IS_FRDM))
#define PL_IS_ROBO	(defined(PL_BOARD_IS_ROBO))

/*! \brief Connect the specific board with specific functions or elements
 *
 * In case of which board is used this macro implements the number of LEDs that are
 * on the board, if events are used or not and if the LEDs are used
 * The FRDM board has 3 LEDs (RGB)
 * The ROBO board has 2 LEDs
 */
#if PL_IS_FRDM
	#define PL_NOF_LED	   		(3)
	#define PL_HAS_EVENTS   	(1)
	#define PL_USE_LED      	(1)
	#define PL_HAS_TIMER    	(1)
	#define PL_HAS_KEYS     	(1)
	#define PL_HAS_KBI      	(1)
	#define PL_NOF_KEYS			(7)
	#define PL_HAS_MEALY		(0 && PL_NOF_LEDS>=1 && PL_NOF_KEYS>=1)
	#define PL_HAS_TRIGGER		(1 && PL_HAS_TIMER)
	#define PL_HAS_BUZZER		(1 && PL_HAS_TRIGGER && PL_IS_ROBO)
	#define PL_HAS_DEBOUNCE		(1 && PL_HAS_KEYS)
	#define PL_SEND_TEXT 		(1)
	#define PL_HAS_RTOS			(1)
	#define PL_HAS_SHELL		(1)
	#define PL_HAS_SHELL_QUEUE	(1)
	#define PL_HAS_BLUETOOTH	(0)
	#define PL_HAS_USB_CDC		(0)
	#define PL_HAS_SEMAPHORE	(1)

#elif PL_IS_ROBO
	#define PL_NOF_LED	    	(2)
	#define PL_HAS_EVENTS   	(1)
	#define PL_USE_LED 	    	(1)
	#define PL_HAS_TIMER    	(1)
	#define PL_HAS_KEYS     	(1)
	#define PL_HAS_KBI      	(1)
	#define PL_NOF_KEYS			(1)
	#define PL_HAS_MEALY		(0 && PL_NOF_LEDS>=1 && PL_NOF_KEYS>=1)
	#define PL_HAS_TRIGGER		(1 && PL_HAS_TIMER)
	#define PL_HAS_BUZZER		(1 && PL_HAS_TRIGGER && PL_IS_ROBO)
	#define PL_HAS_DEBOUNCE		(1 && PL_HAS_KEYS)
	#define PL_SEND_TEXT 		(0)
	#define PL_HAS_RTOS			(1)
	#define PL_HAS_SHELL		(1)
	#define PL_HAS_SHELL_QUEUE	(1)
	#define PL_HAS_BLUETOOTH	(0)
	#define PL_HAS_USB_CDC		(0)
	#define PL_HAS_SEMAPHORE	(1)
	#define PL_HAS_LINE_SENSOR	(1)
#else
	#error "unknown board configuration"
#endif

/*! \brief Platform initialization
 */
void PL_Init(void);

/*! \brief Platform deinitialization
 */
void PL_Deinit(void);
#endif
