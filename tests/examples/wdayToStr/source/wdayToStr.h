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
 * @file wdayToStr.h
 * @brief Example logic for unit testing demonstration.
 *
 *  This module contains a routine that converts integer values to strings, as 
 *    if they represented weekdays.
 */

#ifndef WDAY_TO_STR_H
#define WDAY_TO_STR_H

/*******************************************************************************
 *  INCLUDES
 ******************************************************************************/
#include "myDefs.h"

/*******************************************************************************
 *  PUBLIC FUNCTIONS / ROUTINES
 ******************************************************************************/
/**
 * @brief Provide a string that represents a day of the week.
 * @param wday Integer representing a weekday.
 * @return String representation. If integer is invalid, returns NULL.
 */
const char * wdayToStr(int wday);

#endif
