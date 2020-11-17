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
 * @brief Source file for simple time counting operations.
 *
 * This file implements the Timer driver for KL25 devices.
 */

/*******************************************************************************
 *  INCLUDES
 ******************************************************************************/
#include "myTimer.h"

/*******************************************************************************
 *  PRIVATE DEFINITIONS
 ******************************************************************************/

/*******************************************************************************
 *  PRIVATE PROTOTYPES
 ******************************************************************************/

/*******************************************************************************
 *  PRIVATE VARIABLES
 ******************************************************************************/

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
myRet_t myTimer_Init(myTimer_t * timer, myTimerPars_t * pars)
{
  /* Not implemented yet.                                                     */
  return myRet_OK;
}

/**
 * @brief Starts the time counting operation for a timer.
 * @param timer Timer to start the operation
 * @param period Time, in ms, to count
 * @param cbk Callback to be called when timer expires
 * @return Success / Failure. If successful, timer will start and callback
 *          will eventually be called.
 */
myRet_t myTimer_Start(myTimer_t timer, uint32_t period, myCbk_t cbk)
{
  /* Not implemented yet.                                                     */
  return myRet_OK;
}

/*******************************************************************************
 *  PRIVATE FUNCTIONS / ROUTINES
 ******************************************************************************/
