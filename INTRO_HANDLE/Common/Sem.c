/**
 * \file
 * \brief Semaphore usage
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * Module demonstrating semaphores.
 */

#include "Platform.h" /* interface to the platform */
#if PL_HAS_SEMAPHORE
#include "FRTOS1.h"
#include "Sem.h"
#include "LED.h"
#if PL_HAS_RTOS_TRACE
  #include "RTOSTRC1.h"
#endif

#define USE_SEMAPHORES 1

#if USE_SEMAPHORES
static portTASK_FUNCTION(vSlaveTask, pvParameters) {
  xSemaphoreHandle sem;

  sem = (xSemaphoreHandle)pvParameters;
  for(;;) {
    if (sem != NULL) {
      if (FRTOS1_xSemaphoreTake(sem, portMAX_DELAY)==pdTRUE) {
        LED1_Neg();
      }
    }
  }
}

static portTASK_FUNCTION(vMasterTask, pvParameters) {
	xSemaphoreHandle sem = NULL; /* parameter for Slave */

	(void)pvParameters; /* parameter not used */
	FRTOS1_vSemaphoreCreateBinary(sem);
	if (sem==NULL) { /* semaphore creation failed */
		for(;;) {} /* error */
	}
	FRTOS1_vQueueAddToRegistry(sem, "Sem");
	#if PL_HAS_RTOS_TRACE
	  RTOSTRC1_vTraceSetQueueName(sem, "IPC_Sem");
	#endif
	/* create slave task */
	if (FRTOS1_xTaskCreate(vSlaveTask, "Slave", configMINIMAL_STACK_SIZE, sem, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
		for(;;){} /* error */
	}
	for(;;) {
	    if (sem != NULL) { /* valid semaphore? */
	    	(void)xSemaphoreGive(sem); /* give control to other task */
	    	FRTOS1_vTaskDelay(1000/portTICK_RATE_MS);
	    }
	  }
	}
#endif /* USE_SEMAPHORES */

/*! \brief De-Initializes module */
void SEM_Deinit(void) {
  /* nothing */
}

/*! \brief Initializes module */
void SEM_Init(void) {
  if (FRTOS1_xTaskCreate(vMasterTask, "Master", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
  if (FRTOS1_xTaskCreate(vMasterTask, "Slave", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
     for(;;){} /* error */
  }
}

#endif /* PL_HAS_SEMAPHORE */