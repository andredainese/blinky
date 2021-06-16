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
 * @file test_myTimer_Start.c
 * @brief Test file for testing timer driver logic, operation when
 *          myTimer_Start is called after a timer was initialized.
 */

/*******************************************************************************
 *  INCLUDES
 ******************************************************************************/
#include "unity.h"
#include "myTestDefs.h"

#include "myTimer.h"
#include "myDriverDefs.h"

#include "mock_stm32f1xx_hal.h"
#include "mock_stm32f1xx_hal_tim.h"
#include "mock_stm32f1xx_hal_rcc.h"

/*******************************************************************************
 *  PRIVATE DEFINITIONS
 ******************************************************************************/
#define TEST_PERIOD_MS                                                     (100)

/*******************************************************************************
 *  PRIVATE PROTOTYPES
 ******************************************************************************/
static void prepareMocks(void);
static void setValidTimerPars(void);
static void timerCallback(void);

/*******************************************************************************
 *  PRIVATE VARIABLES
 ******************************************************************************/
static myTimer_t timer = NULL;
static myTimerPars_t pars;

/*******************************************************************************
 *  SET UP / TEAR DOWN
 ******************************************************************************/
void setUp(void)
{
  prepareMocks();
  setValidTimerPars();
  myTimer_Reset();
  myTimer_Init(&timer, &pars);
  myTimer_Start(timer, TEST_PERIOD_MS, timerCallback);
}

void tearDown(void)
{
}

/*******************************************************************************
 *  TESTS
 ******************************************************************************/
/**
 * @brief When a timer is started then logic should make sure that the TIM
 *          is not running by calling HAL_TIM_Base_Stop_IT
 */
void test_LogicCallsHAL_TIM_Base_Stop_IT(void)
{
  TEST_ASSERT_CALLED(HAL_TIM_Base_Stop_IT);
}

/**
 * @brief When a timer is started then logic should initialize/config the
 *          peripheral by calling HAL_TIM_Base_Init
 */
void test_LogicCallsHAL_TIM_Base_Init(void)
{
  TEST_ASSERT_CALLED(HAL_TIM_Base_Init);
}

/**
 * @brief When a timer is started then logic should start the time count by
 *          calling HAL_TIM_Base_Start_IT
 */
void test_LogicCallsHAL_TIM_Base_Start_IT(void)
{
  TEST_ASSERT_CALLED(HAL_TIM_Base_Start_IT);
}

/*******************************************************************************
 *  PRIVATE FUNCTIONS / ROUTINES
 ******************************************************************************/
static void prepareMocks(void)
{
  HAL_RCC_GetPCLK1Freq_fake.return_val = 1000000;
}

static void setValidTimerPars(void)
{
  pars.mode = myTimerMode_Periodic;
}

static void timerCallback(void)
{
}
