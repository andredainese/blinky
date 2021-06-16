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

#include "mock_fsl_tpm.h"
#include "mock_fsl_clock.h"
#include "mock_fsl_common.h"
#include "mock_myTimer_TPM.h"

/*******************************************************************************
 *  PRIVATE DEFINITIONS
 ******************************************************************************/
#define TEST_PERIOD_MS                                                     (200)

/*******************************************************************************
 *  PRIVATE PROTOTYPES
 ******************************************************************************/
static void setValidTimerPars(void);
static void triggerInterrupts(void);
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
  setValidTimerPars();
  callbackCallCount = 0;
  myTimer_Reset();
  myTimer_Init(&timer, &pars);
  myTimer_Start(timer, TEST_PERIOD_MS, timerCallback);
  triggerInterrupts();
}

void tearDown(void)
{
}

/*******************************************************************************
 *  TESTS
 ******************************************************************************/
/**
 * @brief When the interrupt is triggered then driver should call the user
 *          callback once.
 */
void test_CallbackIsCalled(void)
{
  TEST_ASSERT_EQUAL(1, callbackCallCount);
}

/*******************************************************************************
 *  PRIVATE FUNCTIONS / ROUTINES
 ******************************************************************************/
static void setValidTimerPars(void)
{
  pars.mode = myTimerMode_Periodic;
}

static void triggerInterrupts(void)
{
  /* As we don't know which TPM was assigned for us then call all the         */
  /*  interrupts. It should not give any problems as only one timer was       */
  /*  initialized.                                                            */
  TPM0_IRQHandler();
  TPM1_IRQHandler();
  TPM2_IRQHandler();
}

static void timerCallback(void)
{
  callbackCallCount++;
}
