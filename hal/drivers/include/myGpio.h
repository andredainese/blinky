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
 * @brief Header file for general purpose input output drivers.
 *
 * This header provides the types and routines for gpio drivers.
 *  A gpio driver provides routines for using pins for digital input or
 *    digital output operations.
 */

#ifndef MY_GPIO_H
#define MY_GPIO_H

/*******************************************************************************
 *  INCLUDES
 ******************************************************************************/
#include "myDefs.h"

/*******************************************************************************
 *  PUBLIC DEFINITIONS
 ******************************************************************************/
/**
 * @brief Type used by the driver to represent the logic level on a pin.
 */
typedef enum
{
  myGpioLvl_Lo = 0,
  myGpioLvl_Hi,
} myGpioLvl_t;

/**
 * @brief Type used by the driver to represent the direction of pin.
 */
typedef enum
{
  myGpioDir_Inpt = 0,
  myGpioDir_Outp,
} myGpioDir_t;

/**
 * @brief Type used by the driver to represent the pull setting of an input pin.
 */
typedef enum
{
  myGpioPull_No = 0,
  myGpioPull_Up,
  myGpioPull_Dw,
} myGpioPull_t;

/**
 * @brief Structure containing all the info needed to initialize a gpio pin.
 */
typedef struct
{
  uint8_t port;
  uint8_t pin;
  myGpioDir_t direction;
  myGpioPull_t pull;
} myGpioPars_t;

/**
 * @brief Typedef declaring a forward declared struct that represents
 *          a gpio pin.
 */
typedef struct myGpioPinStruct_t * myGpioPin_t;

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
myRet_t myGpio_Init(myGpioPin_t * pin, myGpioPars_t * pars);

/**
 * @brief Gets the level of a given pin.
 * @param pin Info about the pin to get the level from.
 * @return Current level. If routine fails, it returns low level.
 */
myGpioLvl_t myGpio_Get(myGpioPin_t pin);

/**
 * @brief Sets the level of an output pin.
 * @param pin Info about the pin to get the level from.
 * @param lvl Level to set the pin to.
 * @return Success / Failure
 */
myRet_t myGpio_Set(myGpioPin_t pin, myGpioLvl_t lvl);

#endif
