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
 * @file myGpio.h
 * @brief Source file for general purpose input output operations.
 *
 * This file implements the Gpio driver for KL25 devices.
 */

/*******************************************************************************
 *  INCLUDES
 ******************************************************************************/
#include "myGpio.h"

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
 * @brief Initialization routine for a gpio pin.
 * @param pin If successful, it will be written with the data required to use
 *              this pin in the future.
 * @param pars Structure containing all the data required to initialize this
 *              pin.
 * @return Success / Failure
 */
myRet_t myGpio_Init(myGpioPin_t * pin, myGpioPars_t * pars)
{
  /* Not implemented yet.                                                     */
  return myRet_OK;
}

/**
 * @brief Gets the level of a given pin.
 * @param pin Info about the pin to get the level from.
 * @return Current level. If routine fails, it returns low level.
 */
myGpioLvl_t myGpio_Get(myGpioPin_t pin)
{
  /* Not implemented yet.                                                     */
  return myGpioLvl_Lo;
}

/**
 * @brief Sets the level of an output pin.
 * @param pin Info about the pin to get the level from.
 * @param lvl Level to set the pin to.
 * @return Success / Failure
 */
myRet_t myGpio_Set(myGpioPin_t pin, myGpioLvl_t lvl)
{
  /* Not implemented yet.                                                     */
  return myRet_OK;
}

/*******************************************************************************
 *  PRIVATE FUNCTIONS / ROUTINES
 ******************************************************************************/
