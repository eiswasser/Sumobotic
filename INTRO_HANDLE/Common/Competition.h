/*
 * Competition.h
 *
 *  Created on: 14.11.2014
 *      Author: Marco
 */

#ifndef COMPETITION_H_
#define COMPETITION_H_

/*!
 * \brief handels all the different commands, which can be use with this module
 * @param cmd
 * @param handled
 * @param io
 * @return
 */
uint8_t COMP_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

/*!
 * \brief initial the Competition task
 */
void COMP_Init(void);

/*!
 * actually don't do anything at all
 */
void COMP_Deinit(void);

#endif /* COMPETITION_H_ */
