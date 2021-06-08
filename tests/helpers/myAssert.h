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
 * @file myAssert.h
 * @brief Header file containing definitions for logic assertion, suited for
 *          unit testing operations.
 */

#ifndef MY_ASSERT_H
#define MY_ASSERT_H

/*******************************************************************************
 *  INCLUDES
 ******************************************************************************/
#include "myDefs.h"
#include <stdio.h>

/*******************************************************************************
 *  PUBLIC DEFINITIONS
 ******************************************************************************/
#ifndef TEST_DISABLE_ASSERTS
  #define myASSERT(EXP) if((EXP) == false) { printf("%s:%u: Assertion FAILED!\n", __FILE__, __LINE__); }
#else
  #define myASSERT(EXP) (void)((EXP))
#endif

#endif
