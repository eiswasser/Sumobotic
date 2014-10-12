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
}
