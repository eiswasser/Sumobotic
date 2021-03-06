/**
 * \file
 * \brief Shell Message Queue module.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module uses queues for message passing to the Shell.
 */

#include "Platform.h"
#if PL_HAS_SHELL_QUEUE
#include "ShellQueue.h"
#include "FRTOS1.h"

static xQueueHandle SQUEUE_Queue;

#define SQUEUE_LENGTH      32 /* items in queue, that's my buffer size */
#define SQUEUE_ITEM_SIZE   1  /* each item is a single character */

/*!
 * \brief starts with the first element of the String sends each character to the Queue.
 * \param *str Pointer on a unsigned character array
 */
void SQUEUE_SendString(const unsigned char *str) {
	unsigned char ch;
	while((ch=SQUEUE_ReceiveChar()) && ch!='\0') {
		CLS1_GetStdio()->stdOut(ch);
	}
	while(*str!='\0') {
    if (FRTOS1_xQueueSendToBack(SQUEUE_Queue, str, portMAX_DELAY)!=pdPASS) {
      for(;;){} /* ups? */
    }
    str++;
  }
}

/*!
 * \brief
 */
unsigned char SQUEUE_ReceiveChar(void) {
#if 0
  /*! \todo Implement function when used with malloc by creation */
#else
  unsigned char ch;
  portBASE_TYPE res;

  res = FRTOS1_xQueueReceive(SQUEUE_Queue, &ch, 0);
  if (res==errQUEUE_EMPTY) {
    return '\0';
  } else {
    return ch;
  }
#endif
}

/*!
 * \brief
 */
unsigned short SQUEUE_NofElements(void) {
  return (unsigned short)FRTOS1_uxQueueMessagesWaiting(SQUEUE_Queue);
}

/*!
 * \brief
 */
void SQUEUE_Deinit(void) {
  FRTOS1_vQueueDelete(SQUEUE_Queue);
}

/*!
 * \brief
 */
void SQUEUE_Init(void) {
  SQUEUE_Queue = FRTOS1_xQueueCreate(SQUEUE_LENGTH, SQUEUE_ITEM_SIZE);
  if (SQUEUE_Queue==NULL) {
    for(;;){} /* out of memory? */
  }
  FRTOS1_vQueueAddToRegistry(SQUEUE_Queue, "Shell");
#if PL_HAS_RTOS_TRACE
  RTOSTRC1_vTraceSetQueueName(SQUEUE_Queue, "ShellQueue");
#endif
}
#endif /* PL_HAS_SHELL_QUEUE */
