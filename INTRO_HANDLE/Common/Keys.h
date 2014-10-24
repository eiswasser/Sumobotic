/**
 * \file
 * \brief Key/switch driver interface.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements a generic keyboard driver for up to 4 Keys.
 * It is using macros for maximum flexibility with minimal code overhead.
 */

#ifndef KEYS_H_
#define KEYS_H_

#include "Platform.h"

#if PL_HAS_KEYS

#define PL_KEY1_POL		(0)
#define PL_KEY2_POL		(0)
#define PL_KEY3_POL		(0)
#define PL_KEY4_POL		(0)
#define PL_KEY5_POL		(1)
#define PL_KEY6_POL		(1)
#define PL_KEY7_POL		(0)

#if PL_NOF_KEYS>=1
  #include "SW1.h"
  #define KEY1_Get()  (!(SW1_GetVal()))
    /*!< Macro which returns TRUE if key is pressed */
#else
  #define KEY1_Get()  FALSE
    /*!< if we do not have a button, then return 'not pressed' */
#endif

#if PL_NOF_KEYS>=2
  #include "SW2.h"
  #define KEY2_Get()  (!(SW2_GetVal()))
    /*!< Macro which returns TRUE if key is pressed */
#else
  #define KEY2_Get()  FALSE
    /*!< if we do not have a button, then return 'not pressed' */
#endif

#if PL_NOF_KEYS>=3
  #include "SW3.h"
  #define KEY3_Get()  (!(SW3_GetVal()))
    /*!< Macro which returns TRUE if key is pressed */
#else
  #define KEY3_Get()  FALSE
    /*!< if we do not have a button, then return 'not pressed' */
#endif

#if PL_NOF_KEYS>=4
  #include "SW4.h"
  #define KEY4_Get()  (!(SW4_GetVal()))
    /*!< Macro which returns TRUE if key is pressed */
#else
  #define KEY4_Get()  FALSE
    /*!< if we do not have a button, then return 'not pressed' */
#endif

#if PL_NOF_KEYS>=5
  #include "SW5.h"
  #define KEY5_Get()  (!(SW5_GetVal()))
    /*!< Macro which returns TRUE if key is pressed */
#else
  #define KEY5_Get()  FALSE
    /*!< if we do not have a button, then return 'not pressed' */
#endif

#if PL_NOF_KEYS>=6
  #include "SW6.h"
  #define KEY6_Get()  (!(SW6_GetVal()))
    /*!< Macro which returns TRUE if key is pressed */
#else
  #define KEY6_Get()  FALSE
    /*!< if we do not have a button, then return 'not pressed' */
#endif

#if PL_NOF_KEYS>=7
  #include "SW7.h"
  #define KEY7_Get()  (!(SW7_GetVal()))
    /*!< Macro which returns TRUE if key is pressed */
#else
  #define KEY7_Get()  FALSE
    /*!< if we do not have a button, then return 'not pressed' */
#endif


#if PL_HAS_KBI
/*!
 * \brief Function called from a keyboard interrupt (if supported).
 * \param button Button for which interrupt has been generated.
 */
void PORTA_OnInterrupt(void);

#endif


/*!
 * \brief Checks the key status and generates the events.
 */
void KEY_Scan(void);

/*! \brief Get access to key hardware. Use KEY_Close() afterwards. */
void KEY_Open(void);

/*! \brief Finish access to key hardware. Called after KEY_Open(). */
void KEY_Close(void);

/*! \brief Key driver initialization */
void KEY_Init(void);

/*! \brief */
void KEY_EnableInterrupts(void);

/*! \brief */
void KEY_EnableInterrupts(void);

/*! \brief Key driver de-initialization */
void KEY_Deinit(void);

#endif /* PL_HAS_KEYS */

#endif /* KEYS_H_ */
