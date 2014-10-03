/**
 * \file
 * \brief LED driver implementation.
 * \author Marco Bürgi, Pascal Giger
 *
 * This module implements a generic LED driver for up to 5 LEDs.
 * It implement specified methods in the interface LED.h
 */

/*! \brief Implementation of the necessary interfaces for the LED driver module
 */
#include "Platform.h"
#include "LED.h"

/*! \brief Put on the different LEDs
 *
 * First of all, all LEDs were initialized and afterwards they're getting put on.
 * The if clauses take care not to try to put on an LED which doesn't exist on the target.
 */
void LED_Init(void){
	LED1_Init();
	LED2_Init();
	LED3_Init();
	#if PL_NOF_LED>=1
		LED1_Off();
	#endif
	#if PL_NOF_LED>=2
		LED2_Off();
	#endif
	#if PL_NOF_LED>=3
		LED3_Off();
	#endif
}

/*! \brief Put off the different LEDs
 *
 * First of all, all LEDs were put off and afterwards they're getting Deinitialized.
 * The if clauses take care not to try to put off an LED which doesn't exist on the target.
 */
void LED_Deinit(void) {
	#if PL_NOF_LED>=1
		LED1_Off();
	#endif
	#if PL_NOF_LED>=2
		LED2_Off();
	#endif
	#if PL_NOF_LED>=3
		LED3_Off();
	#endif
		LED1_Deinit();
		LED2_Deinit();
		LED3_Deinit();
}

/*! \brief LED test routine.
 *  \todo Need a dedicated error routine!
 * This routine tests if:
 * - we can turn the LEDs properly on and off
 * - if we can negate them
 * - if we can set an LED value
 * - if we can get the LED value
 * If the test fails, the program will hanging in an endless loop
 * If the test was successful LED1 is on.
 */
void LED_Test(void) {

	//Put on all LEDs
	LED1_On();
	LED2_On();
	LED3_On();

	//Put off all LEDs
	LED1_Off();
	LED2_Off();
	LED3_Off();

	//Toggle all LEDs, means in this case put on again
	LED1_Neg();
	LED2_Neg();
	LED3_Neg();

	//Checking if the value can be read. The test was successful if the LED is On
	//that means LED1_Get() returns a TRUE
	if (!LED1_Get()) {
		for(;;){} /*! \todo Need a dedicated error routine! */
	}

	//Checking if the LED can be put off. The test was successful if the LED is Off
	//that means LED1_Get() returns a FALSE
	LED1_Off();
	if (LED1_Get()) {
		for(;;){}; /* \todo Need a dedicated error routine! */
	}

	//Checking if the LED can be set. The test was successful if the LED is On
	//that means LED1_Get() returns a TRUE
	LED1_Put(1);
	if (!LED1_Get()) {
		for(;;){}; /* \todo Need a dedicated error routine! */
	}
}



