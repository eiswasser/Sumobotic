/**
 * \file
 * \brief Application Interface.
 * \author Marco Bürgi, Pascal Giger
 *
 * In this part the main application interface is implementing
 * This interface runs all applications and create the different tasks
 */

#ifndef __APPLICATION_H_
#define __APPLICATION_H_

#if PL_HAS_EVENTS
	#include "Event.h"
#endif
/*! \brief Start main application and main routine
 */
void APP_Start(void);

#if PL_HAS_EVENTS
	void APP_HandleEvent(EVNT_Handle event);
#endif

#endif
