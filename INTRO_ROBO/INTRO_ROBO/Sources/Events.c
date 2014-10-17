/* ###################################################################
**     Filename    : Events.c
**     Project     : INTRO_ROBO
**     Processor   : MK22FX512VLQ12
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2014-09-29, 12:17, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         Cpu_OnNMIINT - void Cpu_OnNMIINT(void);
**
** ###################################################################*/
/*!
** @file Events.c
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"

/*! \brief Imports which are not from the Processor Expert itself
 */
#include "Platform.h"
#if PL_HAS_EVENTS
	#include "Event.h"
#endif
#if PL_HAS_TIMER
	#include "Timer.h"
#endif
#if PL_HAS_KEYS
	#include "Keys.h"
#endif
#if PL_HAS_TRIGGER
	#include "Trigger.h"
#endif


#ifdef __cplusplus
extern "C" {
#endif 


/* User includes (#include below this line is not maintained by Processor Expert) */

/*
** ===================================================================
**     Event       :  Cpu_OnNMIINT (module Events)
**
**     Component   :  Cpu [MK22FN1M0LQ12]
*/
/*!
**     @brief
**         This event is called when the Non maskable interrupt had
**         occurred. This event is automatically enabled when the [NMI
**         interrupt] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnNMIINT(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  TI1_OnInterrupt (module Events)
**
**     Component   :  TI1 [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void TI1_OnInterrupt(void)
{
#if PL_HAS_TIMER
	TMR_OnInterrupt();
#endif
#if PL_HAS_TRIGGER
	TRG_IncTick();
#endif
}

/*
** ===================================================================
**     Event       :  SW1_OnInterrupt (module Events)
**
**     Component   :  SW1 [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void SW1_OnInterrupt(void)
{
#if PL_HAS_KBI
		EVNT_SetEvent(EVNT_SW1_PRESSED);
#endif
}

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.4 [05.10]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
