/**
 * \file
 * \brief LED Interface.
 * \author Marco Bürgi, Pascal Giger
 *
 * In this part the LED interface is implementing
 * This includes the initializing of the LEDs and defining all macros, which
 * are going to use in the connection with the different projects
 */

#ifndef LED_H_
#define LED_H_

/*! \brief implement the platform inteface to make it work with different projects
 */
#include "Platform.h"

/*! \brief create macros for the LED1, depending on how many LEDs are in use for the board
 *
 * If the LEDs are in use they're getting connected to the specific component. If they're
 * not in use the macros is created either, to make the code still working
 * If the board is FRDM LED1 is the green LED
 * If the board is ROBO LED1 is the red LED on the right side
 */
#if PL_NOF_LED >= 1
	#if PL_IS_FRDM
		#include "LED_green.h"

		#define LED1_On()		LED_green_ClrVal() 		/*! Turn on LED1 */
		#define LED1_Off()		LED_green_SetVal() 		/*! Turn off LED1 */
		#define LED1_Neg()		LED_green_NegVal()		/*! Toggle LED1 */
		#define LED1_Get()		LED_green_GetVal() 		/*! Return TRUE, if LED1 is on, FALSE otherwise */
		#define LED1_Put(val)	LED_green_PutVal(val)	/*! Depending on value, it turns on/off LED1 */
		#define LED1_Init()						 		/*! Initialize LED1 */
		#define LED1_Deinit()					 		/*! Deinitialize LED1 */
	#elif PL_IS_ROBO
		#include "LED_right.h"

		#define LED1_On()		LED_right_ClrVal()		/*! Turn on LED1 */
		#define LED1_Off()		LED_right_SetVal() 		/*! Turn off LED1 */
		#define LED1_Neg()		LED_right_NegVal()		/*! Toggle LED1 */
		#define LED1_Get()		LED_right_GetVal() 		/*! Return TRUE, if LED1 is on, FALSE otherwise */
		#define LED1_Put(val)	LED_right_PutVal(val)	/*! Depending on value, it turns on/off LED1 */
		#define LED1_Init()						 		/*! Initialize LED1 */
		#define LED1_Deinit()					 		/*! Deinitialize LED1 */
	#endif
#else
	#define LED1_On()									/*! Turn on LED1 */
	#define LED1_Off()						 			/*! Turn off LED1 */
	#define LED1_Neg()									/*! Toggle LED1 */
	#define LED1_Get()									/*! Return TRUE, if LED1 is on, FALSE otherwise */
	#define LED1_Put(val)								/*! Depending on value, it turns on/off LED1 */
	#define LED1_Init()							 		/*! Initialize LED1 */
	#define LED1_Deinit()						 		/*! Deinitialize LED1 */
#endif

/*! \brief create macros for the LED2, depending on how many LEDs are in use for the board
 *
 * If the LEDs are in use they're getting connected to the specific component. If they're
 * not in use the macros is created either, to make the code still working
 * If the board is FRDM LED2 is the red LED
 * If the board is ROBO LED2 is the red LED on the left side
 */
#if PL_NOF_LED >= 2
	#if PL_IS_FRDM
		#include "LED_red.h"

		#define LED2_On()		LED_red_ClrVal() 		/*! Turn on LED2 */
		#define LED2_Off()		LED_red_SetVal() 		/*! Turn off LED2 */
		#define LED2_Neg()		LED_red_NegVal()		/*! Toggle LED2 */
		#define LED2_Get()		LED_red_GetVal() 		/*! Return TRUE, if LED2 is on, FALSE otherwise */
		#define LED2_Put(val)	LED_red_PutVal(val)		/*! Depending on value, it turns on/off LED2 */
		#define LED2_Init()						 		/*! Initialize LED2 */
		#define LED2_Deinit()					 		/*! Deinitialize LED2 */
	#elif PL_IS_ROBO
		#include "LED_left.h"

		#define LED2_On()		LED_left_ClrVal()		/*! Turn on LED2 */
		#define LED2_Off()		LED_left_SetVal() 		/*! Turn off LED2 */
		#define LED2_Neg()		LED_left_NegVal()		/*! Toggle LED2 */
		#define LED2_Get()		LED_left_GetVal() 		/*! Return TRUE, if LED2 is on, FALSE otherwise */
		#define LED2_Put(val)	LED_left_PutVal(val)	/*! Depending on value, it turns on/off LED2 */
		#define LED2_Init()						 		/*! Initialize LED2 */
		#define LED2_Deinit()					 		/*! Deinitialize LED2 */
	#endif
#else
	#define LED2_On()									/*! Turn on LED2 */
	#define LED2_Off()									/*! Turn off LED2 */
	#define LED2_Neg()									/*! Toggle LED2 */
	#define LED2_Get()									/*! Return TRUE, if LED2 is on, FALSE otherwise */
	#define LED2_Put(val)								/*! Depending on value, it turns on/off LED2 */
	#define LED2_Init()						 			/*! Initialize LED2 */
	#define LED2_Deinit()					 			/*! Deinitialize LED2 */
#endif

/*! \brief create macros for the LED3, depending on how many LEDs are in use for the board
 *
 * If the LEDs are in use they're getting connected to the specific component. If they're
 * not in use the macros is created either, to make the code still working
 * If the board is FRDM LED3 is the blue LED
 * If the board is ROBO there is no third LED
 */
#if PL_NOF_LED >= 3
	#if PL_IS_FRDM
		#include "LED_blue.h"

		#define LED3_On()		LED_blue_ClrVal() 		/*! Turn on LED3 */
		#define LED3_Off()		LED_blue_SetVal() 		/*! Turn off LED3 */
		#define LED3_Neg()		LED_blue_NegVal()		/*! Toggle LED3 */
		#define LED3_Get()		LED_blue_GetVal() 		/*! Return TRUE, if LED3 is on, FALSE otherwise */
		#define LED3_Put(val)	LED_blue_PutVal(val)		/*! Depending on value, it turns on/off LED3 */
		#define LED3_Init()						 		/*! Initialize LED3 */
		#define LED3_Deinit()					 		/*! Deinitialize LED3 */
	#elif PL_IS_ROBO
		/*
		 * \todo generate error for wrong board an amount of LED combination
		 */
	#endif
#else
	#define LED3_On()						 		/*! Turn on LED3 */
	#define LED3_Off()						 		/*! Turn off LED3 */
	#define LED3_Neg()								/*! Toggle LED3 */
	#define LED3_Get()		(0)				 		/*! Return TRUE, if LED3 is on, FALSE otherwise */
	#define LED3_Put(val)							/*! Depending on value, it turns on/off LED3 */
	#define LED3_Init()						 		/*! Initialize LED3 */
	#define LED3_Deinit()					 		/*! Deinitialize LED3 */
#endif

/*! \brief LED test routine.
 * This routine tests if:
 * - the LED can properly turned on and off
 * - if we can negate them
 * - if we can set an LED value
 * - if we can get the LED value
 * If the test fails, the program will hanging in an endless loop
 */
void LED_Test(void);

/*! \brief LED Driver Initialization.
 */
void LED_Init(void);

/*! \brief LED Driver Deinitialization.
 */
void LED_Deinit(void);

#endif
