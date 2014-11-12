/**
 * \file
 * \brief Shell (command line) interface.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements a command line interface to the application.
 */

#ifndef SHELL_H_
#define SHELL_H_



#define SHELL_CMD_TEST "test"
#define SHELL_CMD_FUCK "fuck you"
#define SHELL_CMD_START_CALIBRATE "cstart"
#define SHELL_CMD_STOP_CALIBRATE "cstop"

/*!
 * \brief Sends a string to the shell/console stdout
 * \param msg Zero terminated string to write
 */
void SHELL_SendString(unsigned char *msg);

/*! \brief Shell Module initialization, creates Shell task */
void SHELL_Init(void);

/*! \brief Shell driver de-initialization */
void SHELL_Deinit(void);

#endif /* SHELL_H_ */
