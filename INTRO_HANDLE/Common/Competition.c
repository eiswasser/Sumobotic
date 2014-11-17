/**
 * \file Competition.c
 * \brief race and test file for differnet causes.
 * \author Marco Bürgi, Pascal Giger
 *
 * In this part the of the application are differnet race routines and
 * testparts to test teh functions of the robo
 */

#include "Platform.h"
#if PL_HAS_REFLECTANCE
	#include "Reflectance.h"
	#include "UTIL1.h"
#endif
#if PL_HAS_MOTOR
#include "Motor.h"
#endif

/*!
 *
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
 *
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
    	MOT_StartMotor((MOT_GetMotorHandle(MOT_MOTOR_LEFT)),50);
    	MOT_StartMotor((MOT_GetMotorHandle(MOT_MOTOR_RIGHT)),50);
    	if(REF_GetMeasure(COLOR_W))
    		MOT_StopMotor();
        *handled = TRUE;
    }else {
        CLS1_SendStr((unsigned char*)"Wrong argument\r\n", io->stdErr);
        res = ERR_FAILED;
    }
  return res;
}


