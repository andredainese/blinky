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
 * @file myDriverDefs.h
 * @brief Header file containing custom definitions for STM32F10x drivers.
 *
 * This file will contain types, enums, and defines that can be used
 *  by the application to better use this driver implementation.
 */

#ifndef MY_DRIVER_DEFS_H
#define MY_DRIVER_DEFS_H

/*******************************************************************************
 *  INCLUDES
 ******************************************************************************/
#include "myDefs.h"

/*******************************************************************************
 *  PUBLIC DEFINITIONS
 ******************************************************************************/
/**
 * @brief Type that names the io ports that the device has.
 */
typedef enum
{
  myDriverPort_PA = 0,
  myDriverPort_PB,
  myDriverPort_PC,
  myDriverPort_PD,
  myDriverPort_PE,
} myDriverPort_t;

/**
 * @brief Type that names the io pins that the device has.
 */
typedef enum
{
  myDriverPin_00 = 0,
  myDriverPin_01,
  myDriverPin_02,
  myDriverPin_03,
  myDriverPin_04,
  myDriverPin_05,
  myDriverPin_06,
  myDriverPin_07,
  myDriverPin_08,
  myDriverPin_09,
  myDriverPin_10,
  myDriverPin_11,
  myDriverPin_12,
  myDriverPin_13,
  myDriverPin_14,
  myDriverPin_15,
} myDriverPin_t;

#endif
