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
 * @file myMacros.h
 * @brief Header file containing common macros for the repository.
 *
 * This file will contain macros that can be used to perform several typical
 *  operations throughout the repository.
 */
 
#ifndef MY_MACROS_H
#define MY_MACROS_H

/*******************************************************************************
 *  INCLUDES
 ******************************************************************************/
#include "myDefs.h"

/*******************************************************************************
 *  PUBLIC MACROS
 ******************************************************************************/
/**
 * @brief Macro to get the number of elements from an initialized array of
 *          any type.
 */
#define MY_ARRAY_SIZE(ARR)                          (sizeof(ARR)/sizeof(ARR[0]))

#endif
