/**
 * \file
 * \brief Platform Interface.
 * \author Marco Bürgi, Pascal Giger
 *
 * In this part the platform interface is implementing
 * This includes the initializing of the platform and defining all macros, which
 * are going to use in the connection with the different projects
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#include "PE_Types.h" /* for common Processor Expert types used throughout the project*/
#include "PE_Error.h" /* global error constants */
#include <stddef.h>   /* for NULL */

/*! \brief List of the different boards which are in use for the project.
 *
 * This gives the opportunity to chose afterwards one of the boards in the code line.
 * The name is written as plattform_board_is_xx - PL_BOARD_IS_xx
 * The compiler option from the projects defines the following macros.
 */
#define PL_IS_FRDM	(defined(PL_BOARD_IS_FRDM))
#define PL_IS_ROBO	(defined(PL_BOARD_IS_ROBO))

/*! \brief The following macros select the support of the LEDs in the project.
 *
 * So it gives the opportunity to switch on or off the LEDs in the project.
 */
#define PL_USE_LED (1)

/*! \brief Connect the amount of LEDs with the specific board
 *
 * In case of which board is used this macro implements the number of LEDs that are
 * on the board
 * The FRDM board has 3 LEDs (RGB)
 * The ROBO board has 2 LEDs
 */
#if PL_IS_FRDM
	#define PL_NOF_LED	(3)
#elif PL_IS_ROBO
	#define PL_NOF_LED	(2)
#else
	#error "unknown board configuration"
#endif

/*! \brief Platform initialization
 */
void PL_Init(void);

/*! \brief Platform deinitialization
 */
void PL_Deinit(void);

#endif
