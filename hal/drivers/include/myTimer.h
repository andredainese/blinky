/**
 * Copyright (c) 2020 by Andre F. N. Dainese
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file myTimer.h
 * @brief Header file for simple time counting drivers.
 *
 * This header provides the types and routines for timer drivers.
 *  A timer driver provides routines for using timer peripherals for time
 *    counting operations.
 */

#ifndef MY_TIMER_H
#define MY_TIMER_H

/*******************************************************************************
 *  INCLUDES
 ******************************************************************************/
#include "myDefs.h"

/*******************************************************************************
 *  PUBLIC DEFINITIONS
 ******************************************************************************/
/**
 * @brief Type used by the driver to determine a timer's operating mode.
 */
typedef enum
{
  myTimerMode_Periodic = 0,
} myTimerMode_t;

/**
 * @brief Structure containing all the info needed to initialize a timer.
 */
typedef struct
{
  myTimerMode_t mode;
} myTimerPars_t;

/**
 * @brief Typedef declaring a forward declared struct that represents
 *          a timer.
 */
typedef struct myTimerStruct_t * myTimer_t;

/*******************************************************************************
 *  PUBLIC FUNCTIONS / ROUTINES
 ******************************************************************************/
/**
 * @brief Initialization routine for a timer.
 * @param timer If successful, it will be written with the data required to use
 *              this timer in the future.
 * @param pars Structure containing all the data required to initialize this
 *              timer.
 * @return Success / Failure
 */
myRet_t myTimer_Init(myTimer_t * timer, myTimerPars_t * pars);

/**
 * @brief Starts the time counting operation for a timer.
 * @param timer Timer to start the operation
 * @param period Time, in ms, to count
 * @param cbk Callback to be called when timer expires
 * @return Success / Failure. If successful, timer will start and callback
 *          will eventually be called.
 */
myRet_t myTimer_Start(myTimer_t timer, uint32_t period, myCbk_t cbk);

/*******************************************************************************
 *  PUBLIC FUNCTIONS / ROUTINES - TEST PURPOSES
 ******************************************************************************/
#ifdef TEST
/**
 * @brief Resets driver's internal logic and its variables.
 */
void myTimer_Reset(void);
#endif

#endif
