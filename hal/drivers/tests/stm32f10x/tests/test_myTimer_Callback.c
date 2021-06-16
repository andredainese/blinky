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
 * @file test_myTimer_Callback.c
 * @brief Test file for testing timer driver logic, operation when
 *          a timer was initialized, started and timer expires.
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
#define TEST_PERIOD_MS                                                     (200)

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
static bool callbackCallCount = 0;

/*******************************************************************************
 *  SET UP / TEAR DOWN
 ******************************************************************************/
void setUp(void)
{
  prepareMocks();
  setValidTimerPars();
  callbackCallCount = 0;
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
 * @brief When the TIM3 interrupt is triggered then driver should call the HAL's
 *          IRQ Handler logic
 */
void test_IfTIM3InterruptIsCalledThenHAL_TIM_IRQHandlerIsCalled(void)
{
  TIM3_IRQHandler();
  TEST_ASSERT_CALLED(HAL_TIM_IRQHandler);
}

/**
 * @brief When the TIM4 interrupt is triggered then driver should call the HAL's
 *          IRQ Handler logic
 */
void test_IfTIM4InterruptIsCalledThenHAL_TIM_IRQHandlerIsCalled(void)
{
  TIM4_IRQHandler();
  TEST_ASSERT_CALLED(HAL_TIM_IRQHandler);
}

/**
 * @brief When HAL calls the period elapsed callback then logic should call
 *          the user callback routine once.
 */
void test_IfHAL_TIM_PeriodElapsedCallbackIsCalledThenLogicCallsUserCallbackOnce(void)
{
  /* The callback should be called with the handle that the logic has provided*/
  /*  when it called the HAL_TIM_Base_Start_IT.                               */
  TIM_HandleTypeDef * const handle = HAL_TIM_Base_Start_IT_fake.arg0_val;

  HAL_TIM_PeriodElapsedCallback(handle);

  TEST_ASSERT_EQUAL(1, callbackCallCount);
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
  callbackCallCount++;
}
