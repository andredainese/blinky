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
 * @file wdayToStr.c
 * @brief Example logic for unit testing demonstration.
 *
 *  This module contains a routine that converts integer values to strings, as
 *    if they represented weekdays.
 */

/*******************************************************************************
 *  INCLUDES
 ******************************************************************************/
#include "wdayToStr.h"

/*******************************************************************************
 *  PUBLIC FUNCTIONS / ROUTINES
 ******************************************************************************/
/**
 * @brief Provide a string that represents a day of the week.
 * @param wday Integer representing a weekday.
 * @return String representation. If integer is invalid, returns NULL.
 */
const char * wdayToStr(int wday)
{
  const char * str;

  /* The switch statements below have one intentional error :)                */
  switch(wday)
  {
    case 0:  { str = "sunday"; } break;
    case 1:  { str = "monday"; } break;
    case 2:  { str = "tuesday"; } break;
    case 3:  { str = "wednesday"; } break;
    case 4:  { str = "thursday"; } break;
    case 5:  { str = "friday"; } break;
    case 6:  { str = "saturday"; }
    default: { str = NULL; }
  }

  return str;
}
