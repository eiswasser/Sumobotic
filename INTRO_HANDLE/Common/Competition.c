/**
 * \file Competition.c
 * \brief race and test file for differnet causes.
 * \author Marco Bürgi, Pascal Giger
 *
 * In this part the of the application are differnet race routines and
 * testparts to test teh functions of the robo
 */

#include "Platform.h"
#if PL_COMP_ENABLE
#if PL_HAS_REFLECTANCE
	#include "Reflectance.h"
	#include "UTIL1.h"
#endif
#if PL_HAS_MOTOR
	#include "Motor.h"
#endif
#if PL_HAS_RTOS
	#include "FRTOS1.h"
#endif

/*!
 \brief Enumeration of all our states for the competition
*/
typedef enum CompStat {
	READY,
	FINDLINE,
	STEERING,
	TURN,
	NOC				//Number of competition functions
} CompStateType;

static CompStateType CompState = READY;

/*!
 *
 * @param CompTask
 * @param pvParameters
 */
static portTASK_FUNCTION(CompTask, pvParameters) {
  (void)pvParameters; /* not used */
  for(;;) {
	  switch(CompState){
	  case FINDLINE:
		  MOT_StartMotor(MOT_GetMotorHandle(MOT_MOTOR_RIGHT),50);
		  MOT_StartMotor(MOT_GetMotorHandle(MOT_MOTOR_LEFT),50);
		  if(REF_GetMeasure(COLOR_W)){
			  MOT_StopMotor();
		  	  CompState = STEERING;
		  }
		  break;
	  case STEERING:
		  MOT_StartMotor(MOT_GetMotorHandle(MOT_MOTOR_RIGHT),-50);
		  MOT_StartMotor(MOT_GetMotorHandle(MOT_MOTOR_LEFT),-50);
		  FRTOS1_taskYIELD();
		  if(REF_GetMeasure(COLOR_B)){
		  			  MOT_StopMotor();
		  		  	  CompState = TURN;
		  }
		  break;
	  case TURN:
		  MOT_StartMotor(MOT_GetMotorHandle(MOT_MOTOR_RIGHT),50);
		  MOT_StartMotor(MOT_GetMotorHandle(MOT_MOTOR_LEFT),-50);
		  FRTOS1_vTaskDelay(200/portTICK_RATE_MS);
		  	  MOT_StopMotor();
		  	  CompState = FINDLINE;
	  default:
		  break;
	  }
    FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
  }
}

/*!
 * \brief
 * @param cmd
 * @param handled
 * @param io
 * @return
 */
static uint8_t COMP_PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"comp", (unsigned char*)"Group of competition commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help", (unsigned char*)"Print help information\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  findline", (unsigned char*)"starts the engines and drive with 50% speed ntil the white line have been detected\r\n", io->stdOut);
  return ERR_OK;
}

/*!
 * \brief
 * @param cmd
 * @param handled
 * @param io
 * @return
 */
uint8_t COMP_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t res = ERR_OK;
  int32_t val;
  const unsigned char *p;

  if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, (char*)"comp help")==0) {
  		COMP_PrintHelp(io);
  		*handled = TRUE;
    } else if (UTIL1_strcmp((char*)cmd, (char*)"comp findline")==0) {
    	CompState = FINDLINE;
        *handled = TRUE;
    }
  return res;
}

/*!
 * \brief
 */
void COMP_Deinit() {
}

/*!
 * \brief Initial the module Competition and create a task fo this
 */
void COMP_Init() {
  if (FRTOS1_xTaskCreate(CompTask, "Comp", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}

#endif /*PL_COMP_ENABLE*/


