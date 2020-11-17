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
 * @file appLed.c
 * @brief Interface source file for the LED application.
 *
 * This module provides the routines that external parties can call in order
 *  to interact with the LED application.
 */

/*******************************************************************************
 *  INCLUDES
 ******************************************************************************/
#include "appLed.h"

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
 * @brief Initialization routine for the Button Application
 *
 * This routine should be called by your initializer logic so that the Button
 *  application can start.
 * It should be called only once. After it is called, the module will handle
 *  its initialization by itself.
 * @return Success / Failure
 */
myRet_t appLed_Init(void)
{
  /* Not implemented yet.                                                     */
  return myRet_OK;
}


/**
 * @brief Request application to change the LED blinking period.
 *
 * @param period New period value, in [ms]
 * @return Success / Failure
 */
myRet_t appLed_SetBlinkingPeriod(uint32_t period)
{
  /* Not implemented yet.                                                     */
  return myRet_OK;
}

/*******************************************************************************
 *  PRIVATE FUNCTIONS / ROUTINES
 ******************************************************************************/
