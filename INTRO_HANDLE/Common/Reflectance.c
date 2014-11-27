/**
 * \file
 * \brief Reflectance sensor driver implementation.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements the driver for the bot front sensor.
 */

#include "Platform.h"
#if PL_HAS_LINE_SENSOR
#include "Reflectance.h"
#include "LED_IR.h"
#include "WAIT1.h"
#include "RefCnt.h" /* timer counter to measure reflectance */
#include "IR1.h"
#include "IR2.h"
#include "IR3.h"
#include "IR4.h"
#include "IR5.h"
#include "IR6.h"
#include "UTIL1.h"
#include "FRTOS1.h"
#include "Application.h"
#include "Event.h"
#include "Shell.h"
#include "Timer.h"
#include "TMOUT1.h"
#include "Motor.h"
#include "NVM_Config.h"
#if 1
	#include "Buzzer.h"
#endif
#if PL_HAS_RTOS
	#include "RTOS.h"
#endif

#define REF_NOF_SENSORS 6 	/* number of sensors */
#define THRESHOLD 100
#define MINMAXFAKTOR 0x1000	/* Factor to detect white or black */
#define REF_TIMEOUT_MEASURE_MS 4000

typedef enum{
	NONE,
	EVNT_REF_START_CALIBRATION,
	EVNT_REF_STOP_CALIBRATION
} RefCalibType;
static volatile RefCalibType refCalib = NONE;

typedef enum {
  REF_STATE_INIT,
  REF_STATE_NOT_CALIBRATED,
  REF_STATE_READY
} RefStateType;
static volatile RefStateType refState = REF_STATE_INIT; /* state machine state */

static LDD_TDeviceData *timerHandle;

typedef struct SensorFctType_ {
  void (*SetOutput)(void);
  void (*SetInput)(void);
  void (*SetVal)(void);
  bool (*GetVal)(void);
} SensorFctType;

typedef uint16_t SensorTimeType;
#define MAX_SENSOR_VALUE  ((SensorTimeType)-1)

/* calibration min/max values */
typedef struct SensorCalibT_ {
  SensorTimeType minVal[REF_NOF_SENSORS];
  SensorTimeType maxVal[REF_NOF_SENSORS];
} SensorCalibT;

static SensorCalibT SensorCalibMinMax; /* min/max calibration data in SRAM */
static SensorTimeType SensorRaw[REF_NOF_SENSORS]; /* raw sensor values */
static SensorTimeType SensorCalibrated[REF_NOF_SENSORS]; /* 0 means white/min value, 1000 means black/max value */

/* Functions as wrapper around macro. */
static void S1_SetOutput(void) { IR1_SetOutput(); }
static void S1_SetInput(void) { IR1_SetInput(); }
static void S1_SetVal(void) { IR1_SetVal(); }
static bool S1_GetVal(void) { return IR1_GetVal(); }

static void S2_SetOutput(void) { IR2_SetOutput(); }
static void S2_SetInput(void) { IR2_SetInput(); }
static void S2_SetVal(void) { IR2_SetVal(); }
static bool S2_GetVal(void) { return IR2_GetVal(); }

static void S3_SetOutput(void) { IR3_SetOutput(); }
static void S3_SetInput(void) { IR3_SetInput(); }
static void S3_SetVal(void) { IR3_SetVal(); }
static bool S3_GetVal(void) { return IR3_GetVal(); }

static void S4_SetOutput(void) { IR4_SetOutput(); }
static void S4_SetInput(void) { IR4_SetInput(); }
static void S4_SetVal(void) { IR4_SetVal(); }
static bool S4_GetVal(void) { return IR4_GetVal(); }

static void S5_SetOutput(void) { IR5_SetOutput(); }
static void S5_SetInput(void) { IR5_SetInput(); }
static void S5_SetVal(void) { IR5_SetVal(); }
static bool S5_GetVal(void) { return IR5_GetVal(); }

static void S6_SetOutput(void) { IR6_SetOutput(); }
static void S6_SetInput(void) { IR6_SetInput(); }
static void S6_SetVal(void) { IR6_SetVal(); }
static bool S6_GetVal(void) { return IR6_GetVal(); }

static const SensorFctType SensorFctArray[REF_NOF_SENSORS] = {
  {S1_SetOutput, S1_SetInput, S1_SetVal, S1_GetVal},
  {S2_SetOutput, S2_SetInput, S2_SetVal, S2_GetVal},
  {S3_SetOutput, S3_SetInput, S3_SetVal, S3_GetVal},
  {S4_SetOutput, S4_SetInput, S4_SetVal, S4_GetVal},
  {S5_SetOutput, S5_SetInput, S5_SetVal, S5_GetVal},
  {S6_SetOutput, S6_SetInput, S6_SetVal, S6_GetVal},
};

/*!
 * \brief Returns a bool if the selected Color have been detected or not
 *
 */
bool REF_GetMeasure(REF_Color color){
	int i = 0;
	if(color == COLOR_W){
		for(i = 0; i < REF_NOF_SENSORS; i++){
			if(SensorRaw[i] < (SensorCalibMinMax.maxVal[i] - MINMAXFAKTOR))
				return TRUE;
			else
				i++;
		}
	}
	if(color == COLOR_B){
		for(i = 0; i < REF_NOF_SENSORS; i++){
			if(SensorRaw[i] > (SensorCalibMinMax.minVal[i] + MINMAXFAKTOR))
				return TRUE;
			else
				i++;
		}
	}
	return FALSE;
}

static void REF_MeasureRaw(SensorTimeType raw[REF_NOF_SENSORS]) {
  uint8_t cnt; /* number of sensor */
  uint8_t i;

  LED_IR_On(); /* IR LED's on */
  WAIT1_Waitus(100); /*! \todo adjust time as needed 50 should be easy possible*/

  for(i=0;i<REF_NOF_SENSORS;i++) {
    SensorFctArray[i].SetOutput(); /* turn I/O line as output */
    SensorFctArray[i].SetVal(); /* put high */
    raw[i] = MAX_SENSOR_VALUE;
  }
  WAIT1_Waitus(5); /* give some time to charge the capacitor */
  FRTOS1_taskENTER_CRITICAL();
  for(i=0;i<REF_NOF_SENSORS;i++) {
	  SensorFctArray[i].SetInput(); /* turn I/O line as input */
  }
  (void)RefCnt_ResetCounter(timerHandle); /* reset timer counter */
  do {
    cnt = 0;
    if(REF_TIMEOUT_MEASURE_MS < RefCnt_GetCounterValue(timerHandle)){
        break;
    }
    for(i=0;i<REF_NOF_SENSORS;i++) {
    	if (raw[i]==MAX_SENSOR_VALUE) { /* not measured yet? */
    		if (SensorFctArray[i].GetVal()==0){
    			raw[i] = RefCnt_GetCounterValue(timerHandle);
    		}
    	}
    	else /* have value */
    		cnt++;
    }
  } while(cnt!=REF_NOF_SENSORS);
  FRTOS1_taskEXIT_CRITICAL();
  LED_IR_Off();
}

/*!
 * \brief
 */
static void REF_CalibrateMinMax(SensorTimeType min[REF_NOF_SENSORS], SensorTimeType max[REF_NOF_SENSORS], SensorTimeType raw[REF_NOF_SENSORS]) {
  int i;
  
  REF_MeasureRaw(raw);
  for(i=0;i<REF_NOF_SENSORS;i++) {
    if (raw[i] < min[i]) {
      min[i] = raw[i];
    }
    if (raw[i]> max[i]) {
      max[i] = raw[i];
    }
  }
}

/*!
 * \brief
 */
static void ReadCalibrated(SensorTimeType calib[REF_NOF_SENSORS], SensorTimeType raw[REF_NOF_SENSORS]) {
  int i;
  int32_t x, denominator;
  
  REF_MeasureRaw(raw);
  for(i=0;i<REF_NOF_SENSORS;i++) {
    x = 0;
    denominator = SensorCalibMinMax.maxVal[i]-SensorCalibMinMax.minVal[i];
    if (denominator!=0) {
      x = (((int32_t)raw[i]-SensorCalibMinMax.minVal[i])*1000)/denominator;
    }
    if (x<0) {
      x = 0;
    } else if (x>1000) {
      x = 1000;
    }
    calib[i] = x;
  }
}

/*!
 * \brief
 */
static void REF_Measure(void) {
  ReadCalibrated(SensorCalibrated, SensorRaw);
}

static void REF_CalibDrive(void){
	#if PL_HAS_SHELL
		SHELL_SendString((unsigned char*)"start calibration...\r\n");
	#endif
	MOT_StartMotor(MOT_GetMotorHandle(MOT_MOTOR_LEFT),-20);
	MOT_StartMotor(MOT_GetMotorHandle(MOT_MOTOR_RIGHT),-20);
	FRTOS1_vTaskDelay(1000/portTICK_RATE_MS);
	MOT_StopMotor();
	refCalib = EVNT_REF_STOP_CALIBRATION;								//Command for statemachine
	#if PL_HAS_SHELL
		SHELL_SendString((unsigned char*)"stop calibration\r\n");
	#endif
}
static uint8_t PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"ref", (unsigned char*)"Group of Reflectance commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  CLS1_SendHelpStr("  cstart", "to start the calibration of the line sensor\r\n", io->stdOut);
  return ERR_OK;
}

static unsigned char*REF_GetStateString(void) {
  switch (refState) {
    case REF_STATE_INIT:                return (unsigned char*)"INIT";
    case REF_STATE_NOT_CALIBRATED:      return (unsigned char*)"NOT CALIBRATED";
    case REF_STATE_READY:               return (unsigned char*)"READY";
    default:
      break;
  } /* switch */
  return (unsigned char*)"UNKNOWN";
}

static uint8_t PrintStatus(const CLS1_StdIOType *io) {
  unsigned char buf[24];
  int i;

  CLS1_SendStatusStr((unsigned char*)"reflectance", (unsigned char*)"\r\n", io->stdOut);
  
  CLS1_SendStatusStr((unsigned char*)"  state", REF_GetStateString(), io->stdOut);
  CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);

  CLS1_SendStatusStr((unsigned char*)"  raw val", (unsigned char*)"", io->stdOut);
  for (i=0;i<REF_NOF_SENSORS;i++) {
    if (i==0) {
      CLS1_SendStr((unsigned char*)"0x", io->stdOut);
    } else {
      CLS1_SendStr((unsigned char*)" 0x", io->stdOut);
    }
    buf[0] = '\0'; UTIL1_strcatNum16Hex(buf, sizeof(buf), SensorRaw[i]);
    CLS1_SendStr(buf, io->stdOut);
  }
  CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);
  
  CLS1_SendStatusStr((unsigned char*)"  min val", (unsigned char*)"", io->stdOut);
  for (i=0;i<REF_NOF_SENSORS;i++) {
    if (i==0) {
      CLS1_SendStr((unsigned char*)"0x", io->stdOut);
    } else {
      CLS1_SendStr((unsigned char*)" 0x", io->stdOut);
    }
    buf[0] = '\0'; UTIL1_strcatNum16Hex(buf, sizeof(buf), SensorCalibMinMax.minVal[i]);
    CLS1_SendStr(buf, io->stdOut);
  }
  CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  max val", (unsigned char*)"", io->stdOut);
  for (i=0;i<REF_NOF_SENSORS;i++) {
    if (i==0) {
      CLS1_SendStr((unsigned char*)"0x", io->stdOut);
    } else {
      CLS1_SendStr((unsigned char*)" 0x", io->stdOut);
    }
    buf[0] = '\0'; UTIL1_strcatNum16Hex(buf, sizeof(buf), SensorCalibMinMax.maxVal[i]);
    CLS1_SendStr(buf, io->stdOut);
  }
  CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);
 
  CLS1_SendStatusStr((unsigned char*)"  calib val", (unsigned char*)"", io->stdOut);
  for (i=0;i<REF_NOF_SENSORS;i++) {
    if (i==0) {
      CLS1_SendStr((unsigned char*)"0x", io->stdOut);
    } else {
      CLS1_SendStr((unsigned char*)" 0x", io->stdOut);
    }
    buf[0] = '\0'; UTIL1_strcatNum16Hex(buf, sizeof(buf), SensorCalibrated[i]);
    CLS1_SendStr(buf, io->stdOut);
  }
  CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);
  return ERR_OK;
}

byte REF_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "ref help")==0) {
	  *handled = TRUE;
	  return PrintHelp(io);
  } else if ((UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0) || (UTIL1_strcmp((char*)cmd, "ref status")==0)) {
	  *handled = TRUE;
	  return PrintStatus(io);
  } else if (UTIL1_strcmp((char*)cmd, REF_CMD_START_CALIBRATE)==0 || UTIL1_strcmp((char*)cmd, "cstart")==0) {
	  *handled = TRUE;
	  refCalib = EVNT_REF_START_CALIBRATION;							//Command for statemachine
	  BUZ_Beep(300,500/TMR_TICK_MS);
	  REF_CalibDrive();
  }
  return ERR_OK;
}

static void REF_StateMachine(void) {
  int i;

  switch (refState) {
    case REF_STATE_INIT:
    	if (NVMC_GetReflectanceData()==NULL){
    		for(i=0;i<REF_NOF_SENSORS;i++) {
    			SensorCalibMinMax.minVal[i] = MAX_SENSOR_VALUE;
    			SensorCalibMinMax.maxVal[i] = 0;
    			SensorCalibrated[i] = 0;
    		}
    	}
    	else
    		SensorCalibMinMax= *((SensorCalibT*)NVMC_GetReflectanceData());
	  #if PL_HAS_SHELL
      SHELL_SendString((unsigned char*)"INFO: No calibration data present.\r\n");
	  #endif
      refState = REF_STATE_NOT_CALIBRATED;
      break;
      
    case REF_STATE_NOT_CALIBRATED:
    	if (refCalib == EVNT_REF_START_CALIBRATION) {
    		REF_CalibrateMinMax(SensorCalibMinMax.minVal, SensorCalibMinMax.maxVal, SensorRaw);
    	}
    	if (refCalib == EVNT_REF_STOP_CALIBRATION){
    		NVMC_SaveReflectanceData(&SensorCalibMinMax,sizeof(SensorCalibMinMax));
    		refState = REF_STATE_READY;
    		refCalib = NONE;
    	}
    break;
        
    case REF_STATE_READY:
    	REF_Measure();
    	if (refCalib == EVNT_REF_START_CALIBRATION) {
    		refState = REF_STATE_NOT_CALIBRATED;
    		refCalib = EVNT_REF_START_CALIBRATION;
    		REF_CalibDrive();
    	}
     break;
  } /* switch */
}

static portTASK_FUNCTION(ReflTask, pvParameters) {
  (void)pvParameters; /* not used */
  for(;;) {
    REF_StateMachine();
    FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
  }
}

void REF_Deinit(void) {

}

void REF_Init(void) {
  refState = REF_STATE_INIT;
  timerHandle = RefCnt_Init(NULL);
  /*! \todo You might need to adjust priority or other task settings */
  if (FRTOS1_xTaskCreate(ReflTask, "Refl", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}
#endif /* PL_HAS_LINE_SENSOR */
