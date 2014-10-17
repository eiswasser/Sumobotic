/**
 * \file
 * \brief Timer driver interface.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements the driver for the timers used in the system.
 */

#ifndef TIMER_H_
#define TIMER_H_

#if PL_IS_FRDM
	#define TMR_TICKS_MS  (10)
  	/*!< we get called every x ms */
#endif
#if PL_IS_ROBO
	#define TMR_TICKS_MS (1)
	/*!< we get called every x ms */
#endif

/*! \brief Function called from timer interrupt every TMR_TICK_MS. */
void TMR_OnInterrupt(void);

/*! \brief Timer driver initialization */
void TMR_Init(void);

/*! \brief Timer driver de-initialization */
void TMR_Deinit(void);

#endif /* TIMER_H_ */
