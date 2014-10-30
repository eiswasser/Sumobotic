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
	#include "Event.h"
	#include "Application.h"
	#include "Keys.h"
	#if 0
		static portTASK_FUNCTION(T1, pvParameters) {
			for(;;) {
				LED1_Neg();
				FRTOS1_vTaskDelay(200);
			}
		}
		static portTASK_FUNCTION(T2, pvParameters) {
			for(;;) {
				LED2_Neg();
				FRTOS1_vTaskDelay(400);
			}
		}
		static portTASK_FUNCTION(T3, pvParameters) {
			for(;;) {
				LED3_Neg();
				FRTOS1_vTaskDelay(800);
			}
		}
	#endif

	static portTASK_FUNCTION(APP_LOOP, pvParameters) {
		for(;;) {
			#if PL_HAS_EVENTS
				EVNT_HandleEvent(APP_HandleEvent);
			#endif
			#if PL_HAS_KEYS
				KEY_Scan();
			#endif
		}
	}

	void RTOS_Run(void) {
	  FRTOS1_vTaskStartScheduler();
	}

	void RTOS_Init(void) {
	  /*! \todo Add tasks here */
		#if 0
			if (FRTOS1_xTaskCreate(T1, (signed portCHAR *)"T1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL) != pdPASS) {
				for(;;){} /* error */
			}
			if (FRTOS1_xTaskCreate(T2, (signed portCHAR *)"T2", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL) != pdPASS) {
				for(;;){} /* error */
			}
			if (FRTOS1_xTaskCreate(T3, (signed portCHAR *)"T3", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL) != pdPASS) {
				for(;;){} /* error */
			}
		#endif

		if (FRTOS1_xTaskCreate(APP_LOOP, (signed portCHAR *)"APP_LOOP", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL) != pdPASS) {
							for(;;){} /* error */
		}
	}

	void RTOS_Deinit(void) {
	}

#endif /* PL_HAS_RTOS */

