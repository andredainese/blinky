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
 * @file myDefs.h
 * @brief Header file containing common definitions for the repository.
 *
 * This file will contain types, enums, and defines that can be used
 *  anywhere througout the repository.
 */
 
#ifndef MY_DEFS_H
#define MY_DEFS_H

/*******************************************************************************
 *  INCLUDES
 ******************************************************************************/
#include <stdint.h>
#include <stdbool.h>

/*******************************************************************************
 *  PUBLIC DEFINITIONS - TYPES
 ******************************************************************************/
/**
 * @brief Basic type that all logic should use to indicate success or failure.
 *
 * This enumeration should be used to represent if an operation went well or
 *  not. Notice that the success result has the value of zero.
 */
typedef enum
{
  myRet_OK = 0,
  myRet_Fail,
} myRet_t;

/*******************************************************************************
 *  PUBLIC DEFINITIONS - CALLBACKS
 ******************************************************************************/
/**
 * @brief Basic callback for simple actions.
 *
 * This callback is used when a module doesn't need to provide any data when 
 *  it'll answer back the result of an operation.
 */
typedef void (*myCbk_t)(void);

#endif
