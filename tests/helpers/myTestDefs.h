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
 * @file myTestDefs.h
 * @brief Header file containing definitions that may be used for unit testing.
 *
 * This file will contain types, enums, defines and macros that can be used
 *  by the unit test logic to perform their tests.
 */

#ifndef MY_TEST_DEFS_H
#define MY_TEST_DEFS_H

/*******************************************************************************
 *  INCLUDES
 ******************************************************************************/
#include "myDefs.h"

/*******************************************************************************
 *  PUBLIC DEFINITIONS - MACROS
 ******************************************************************************/
/**
 * @brief Declare a test not being possible. Test is ignored and a notification
 *          about this is given when tests are executed.
 */
#define TEST_NOT_POSSIBLE()     TEST_IGNORE_MESSAGE("Cannot perform this test.")

/**
 * @brief Declare a test not being possible if given pointer is NULL.
 */
#define TEST_NOT_POSSIBLE_IF_NULL(PTR)                                         \
{                                                                              \
  if(PTR == NULL) { TEST_IGNORE_MESSAGE("Cannot perform this test."); }        \
}

#endif
