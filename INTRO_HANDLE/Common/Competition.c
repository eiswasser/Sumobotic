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
#if PL_HAS_DRIVE
	#include "Drive.h"
#endif
#if PL_HAS_ULTRASONIC
	#include "Ultrasonic.h"
	#include "TMOUT1.h"
#endif
#if PL_HAS_EVENTS
	#include "Event.h"
#endif
#if PL_HAS_ACCEL
	#include "Accel.h"
#endif

/*!
 \brief Enumeration of all our states for the competition
*/
typedef enum CompStat {
	READY,
	FINDLINE,
	TURN,
	TURNAROUND,
	STOP,
	NOC				//Number of competition functions
} CompStateType;

static CompStateType CompState = READY;
#if PL_HAS_DRIVE
	static int32_t speed;
	#define MAXSPEED 6200
	#define TURNSPEED 2500
#else
	static MOT_SpeedPercent speed;
#endif
	uint16_t cm = 0,us = 0;
#if PL_HAS_ULTRASONIC
	#define US_TIMEOUT_MEASURE_MS1	2000
	static TMOUT1_CounterHandle USHandle1;
	#define US_TIMEOUT_MEASURE_MS2 	800
	static TMOUT1_CounterHandle USHandle2;
#endif
#if PL_HAS_ACCEL
	static int16_t x;
	static int16_t y;
	static int16_t z;
#endif

/*!
 *
 * @param CompTask
 * @param pvParameters
 */
static portTASK_FUNCTION(CompTask, pvParameters) {
  (void)pvParameters; /* not used */
  for(;;) {
	  #if PL_HAS_ACCEL && 0
	  	 ACCEL_GetValues(&x, &y, &z);
	  	 if (z<=500){
	  		 EVNT_SetEvent(EVNT_STOP_ENGINE);
	  		 CompState= READY;
	  	 }
	  #endif
	  switch(CompState){
	  case FINDLINE:
		  	#if PL_HAS_DRIVE
	  	  	  	DRV_EnableDisable(TRUE);
		  	  	us = US_Measure_us();
		 	    cm = US_GetLastCentimeterValue();
		  	  	if(0 < cm && cm <= 30){
	  		  		DRV_SetSpeed(MAXSPEED,MAXSPEED);
	  		  	} else{
	  		  		DRV_SetSpeed(speed,speed);
	  		  	}
				if(REF_GetMeasure(COLOR_W)){
					DRV_SetSpeed(-speed,-speed);
					FRTOS1_vTaskDelay(200/portTICK_RATE_MS);
					if(TMOUT1_CounterExpired(USHandle1)){
						DRV_SetSpeed(-TURNSPEED,TURNSPEED);
						TMOUT1_SetCounter(USHandle2,US_TIMEOUT_MEASURE_MS2);
						CompState = TURNAROUND;
					} else {
						CompState = TURN;
					}
				}
			#else
			MOT_StartMotor(MOT_GetMotorHandle(MOT_MOTOR_RIGHT),speed);
			MOT_StartMotor(MOT_GetMotorHandle(MOT_MOTOR_LEFT),speed);
			if(REF_GetMeasure(COLOR_W)){
				MOT_StartMotor(MOT_GetMotorHandle(MOT_MOTOR_RIGHT),-speed);
				MOT_StartMotor(MOT_GetMotorHandle(MOT_MOTOR_LEFT),-speed);
				FRTOS1_vTaskDelay(200/portTICK_RATE_MS);
				if(TMOUT1_CounterExpired(USHandle1)){
					MOT_StartMotor(MOT_GetMotorHandle(MOT_MOTOR_RIGHT),30);
					MOT_StartMotor(MOT_GetMotorHandle(MOT_MOTOR_LEFT),-30);
					TMOUT1_SetCounter(USHandle2,US_TIMEOUT_MEASURE_MS2);
					CompState = TURNAROUND;
				} else {
					CompState = TURN;
				}
			}
			#endif
			  break;
		  case TURN:
			  us = US_Measure_us();
			  cm = US_GetLastCentimeterValue();
			  if(0 < cm && cm <= 30){
				DRV_EnableDisable(TRUE);
			  	DRV_SetSpeed(MAXSPEED,MAXSPEED);
			  }
			  else{
				  #if PL_HAS_DRIVE
					DRV_SetSpeed(TURNSPEED,-TURNSPEED);
				  #else
					MOT_StartMotor(MOT_GetMotorHandle(MOT_MOTOR_RIGHT),30);
					MOT_StartMotor(MOT_GetMotorHandle(MOT_MOTOR_LEFT),-30);
				  #endif
					FRTOS1_vTaskDelay(200/portTICK_RATE_MS);
			  }
			  CompState = FINDLINE;
		      break;
		  case TURNAROUND:
			  if(us == 0){
				#if PL_HAS_DRIVE
				  	DRV_EnableDisable(TRUE);
					DRV_SetSpeed(-TURNSPEED,TURNSPEED);
				#else
					MOT_StartMotor(MOT_GetMotorHandle(MOT_MOTOR_RIGHT),50);
					MOT_StartMotor(MOT_GetMotorHandle(MOT_MOTOR_LEFT),-50);
				#endif
					us = US_Measure_us();
			  }else {
			    us = US_Measure_us();
			    cm = US_GetLastCentimeterValue();
			    if(0 < cm && cm <= 30){
			    	CompState = FINDLINE;
			    	break;
			    }
			    if(TMOUT1_CounterExpired(USHandle2)){
			    	CompState = FINDLINE;
			    	TMOUT1_SetCounter(USHandle1,US_TIMEOUT_MEASURE_MS1);
			    }
			  }
			    break;
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
  CLS1_SendHelpStr((unsigned char*)"  findline <speed>", (unsigned char*)"starts the engines and drive with specific speed until the white line have been detected\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  stop", (unsigned char*)"stops the findline routine inkl. engine\r\n", io->stdOut);
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
    } else if (UTIL1_strncmp((char*)cmd, (char*)"comp findline ", sizeof("comp findline ")-1)==0) {
		p = cmd+sizeof("comp findline");
		if (UTIL1_xatoi(&p, &val)==ERR_OK && val >=-100 && val<=100) {
		  #if PL_HAS_DRIVE
		  speed = (val * MAXSPEED) / 100;		//ugly division but for the moment no other fittable ideal ^^
		  #else
		  speed = (MOT_SpeedPercent)val;
		  #endif
		  CompState = FINDLINE;
		  TMOUT1_SetCounter(USHandle1,US_TIMEOUT_MEASURE_MS1);
		  *handled = TRUE;
		}
    } else if(UTIL1_strcmp((char*)cmd, (char*)"comp stop")==0) {
    	CompState = READY;
    	EVNT_SetEvent(EVNT_STOP_ENGINE);
		*handled = TRUE;
    }
  return res;
}

/*!
 * \brief
 */
void COMP_SetFindline(void* p){
	CompState = FINDLINE;
#if PL_HAS_DRIVE
	speed = 3000;
#else
	speed = 50;
#endif
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
  if (FRTOS1_xTaskCreate(CompTask, "Comp", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}

#endif /*PL_COMP_ENABLE*/


