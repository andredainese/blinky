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
 * @file test_wdayToStr.c
 * @brief Example test file for testing wdayToStr logic
 */

/*******************************************************************************
 *  INCLUDES
 ******************************************************************************/
#include "unity.h"
#include "myTestDefs.h"

#include "wdayToStr.h"

/*******************************************************************************
 *  SET UP / TEAR DOWN
 ******************************************************************************/
void setUp(void)
{
}

void tearDown(void)
{
}

/*******************************************************************************
 *  TESTS
 ******************************************************************************/
void test_1stDayIsSunday(void)
{
  TEST_ASSERT_EQUAL_STRING("sunday", wdayToStr(0));
}

void test_2ndDayIsMonday(void)
{
  TEST_ASSERT_EQUAL_STRING("monday", wdayToStr(1));
}

void test_3rdDayIsTuesday(void)
{
  TEST_ASSERT_EQUAL_STRING("tuesday", wdayToStr(2));
}

void test_4thDayIsWednesday(void)
{
  TEST_ASSERT_EQUAL_STRING("wednesday", wdayToStr(3));
}

void test_5thDayIsThursday(void)
{
  TEST_ASSERT_EQUAL_STRING("thursday", wdayToStr(4));
}

void test_6thDayIsFriday(void)
{
  TEST_ASSERT_EQUAL_STRING("friday", wdayToStr(5));
}

void test_7thDayIsSaturday(void)
{
  TEST_ASSERT_EQUAL_STRING("saturday", wdayToStr(6));
}

void test_8thDayIsInvalid(void)
{
  TEST_ASSERT_NULL(wdayToStr(7));
}
