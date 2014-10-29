/**
 * \file
 * \brief Real Time Operating System (RTOS) main program.
 * \author Erich Styger, erich.styger@hslu.ch
 */

#include "Platform.h"
#if PL_HAS_RTOS
#include "RTOS.h"
#include "FRTOS1.h"
#include "LED.h"

#if
	static portTASK_FUNCTION(T1, pvParameters) {
		for(;;) {
			LED1_Neg();
		}
	}
	static portTASK_FUNCTION(T1, pvParameters) {
		for(;;) {
			LED2_Neg();
		}
	}
#endif

void RTOS_Run(void) {
  FRTOS1_vTaskStartScheduler();
}

void RTOS_Init(void) {
  /*! \todo Add tasks here */
#if
	if (FRTOS1_xTaskCreate(T1, (signed portCHAR *)"T1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL) != pdPASS) {
		for(;;){} /* error */
		}
	if (FRTOS1_xTaskCreate(T2, (signed portCHAR *)"T2", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL) != pdPASS) {
	    for(;;){} /* error */
	  	  }
	}
#endif
void RTOS_Deinit(void) {
}

#endif /* PL_HAS_RTOS */
