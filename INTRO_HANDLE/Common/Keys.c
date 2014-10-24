/**
 * \file
 * \brief Key/Switch driver implementation.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements a generic keyboard driver for up to 7 Keys.
 * It is using macros for maximum flexibility with minimal code overhead.
 */

#include "Platform.h"
#if PL_HAS_KEYS
  #include "Keys.h"

#if PL_HAS_EVENTS
  #include "Event.h"
#endif
#if PL_HAS_DEBOUNCE
	#include "KeyDebounce.h"
#endif

/*! \brief
 *
 */
void KEY_Scan(void) {

#if PL_HAS_DEBOUNCE
	KEYDBNC_Process();
#elif PL_HAS_KBI
	#if PL_NOF_KEYS >= 1 && PL_KEY1_POL
	  if (KEY1_Get()) { /* key pressed */
		EVNT_SetEvent(EVNT_SW1_PRESSED);
	  }
	#endif
	#if PL_NOF_KEYS >= 2 && PL_KEY2_POL
	  if (KEY2_Get()) { /* key pressed */
		EVNT_SetEvent(EVNT_SW2_PRESSED);
	  }
	#endif
	#if PL_NOF_KEYS >= 3 && PL_KEY3_POL
	  if (KEY3_Get()) { /* key pressed */
		EVNT_SetEvent(EVNT_SW3_PRESSED);
	  }
	#endif
	#if PL_NOF_KEYS >= 4 && PL_KEY4_POL
	  if (KEY4_Get()) { /* key pressed */
		EVNT_SetEvent(EVNT_SW4_PRESSED);
	  }
	#endif
	#if PL_NOF_KEYS >= 5 && PL_KEY5_POL
	  if (KEY5_Get()) { /* key pressed */
		EVNT_SetEvent(EVNT_SW5_PRESSED);
	  }
	#endif
	#if PL_NOF_KEYS >= 6 && PL_KEY6_POL
	  if (KEY6_Get()) { /* key pressed */
		EVNT_SetEvent(EVNT_SW6_PRESSED);
	  }
	#endif
	#if PL_NOF_KEYS >= 7 && PL_KEY7_POL
	  if (KEY7_Get()) { /* key pressed */
		EVNT_SetEvent(EVNT_SW7_PRESSED);
	  }
	#endif
#endif
}

/*! \brief
 *
 */
#if PL_HAS_KBI

/*! \brief
 *
 */
void KEY_EnableInterrupts(void) {
#if PL_NOF_KEYS >= 1 && !PL_KEY1_POL
  SW1_Enable();
#endif
#if PL_NOF_KEYS >= 2 && !PL_KEY2_POL
  SW2_Enable();
#endif
#if PL_NOF_KEYS >= 3 && !PL_KEY3_POL
  SW3_Enable();
#endif
#if PL_NOF_KEYS >= 4 && !PL_KEY4_POL
  SW4_Enable();
#endif
#if PL_NOF_KEYS >= 5 && !PL_KEY5_POL
  SW5_Enable();
#endif
#if PL_NOF_KEYS >= 6 && !PL_KEY6_POL
  SW6_Enable();
#endif
#if PL_NOF_KEYS >= 7 && !PL_KEY7_POL
  SW7_Enable();
#endif
}

/*! \brief
 *
 */
void KEY_DisableInterrupts(void) {
#if PL_NOF_KEYS >= 1 && !PL_KEY1_POL
  SW1_Disable();
#endif
#if PL_NOF_KEYS >= 2 && !PL_KEY2_POL
  SW2_Disable();
#endif
#if PL_NOF_KEYS >= 3 && !PL_KEY3_POL
  SW3_Disable();
#endif
#if PL_NOF_KEYS >= 4 && !PL_KEY4_POL
  SW4_Disable();
#endif
#if PL_NOF_KEYS >= 5 && !PL_KEY5_POL
  SW5_Disable();
#endif
#if PL_NOF_KEYS >= 6 && !PL_KEY6_POL
  SW6_Disable();
#endif
#if PL_NOF_KEYS >= 7 && !PL_KEY7_POL
  SW7_Disable();
#endif
}

/*! \brief handler for the interrupt for SW4 */
void PORTA_OnInterrupt(void) {
	void Cpu_ivINT_PORTA(void); /* prototype of ISR in Cpu.c */
	/* call interrupt handler created by the ExtInt components */
	Cpu_ivINT_PORTA();
}

#endif

/*! \brief Key driver initialization */
void KEY_Init(void) {
  /* nothing needed for now */
}

/*! \brief Key driver de-initialization */
void KEY_Deinit(void) {
  /* nothing needed for now */
}

#endif /* PL_HAS_KEYS */
