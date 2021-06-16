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
 * @file test_myTimer_Init.c
 * @brief Test file for testing timer driver logic, operation when
 *          myTimer_Init is called.
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

/*******************************************************************************
 *  PRIVATE PROTOTYPES
 ******************************************************************************/
static void setValidTimerPars(void);

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
  setValidTimerPars();
  myTimer_Reset();
  timer = NULL;
}

void tearDown(void)
{
}

/*******************************************************************************
 *  TESTS
 ******************************************************************************/
/**
 * @brief myTimer_Init logic should return fail if timer argument is invalid.
 */
void test_IfTimerArgIsInvalidThenItFails(void)
{
  const myRet_t result = myTimer_Init(NULL, &pars);

  TEST_ASSERT_EQUAL(myRet_Fail, result);
}

/**
 * @brief myTimer_Init logic should return fail if pars argument is invalid.
 */
void test_IfParsArgIsInvalidThenItFails(void)
{
  const myRet_t result = myTimer_Init(&timer, NULL);

  TEST_ASSERT_EQUAL(myRet_Fail, result);
}

/**
 * @brief myTimer_Init logic should return fail if mode selection is not
 *          periodic.
 */
void test_IfModeIsNotPeriodicThenItFails(void)
{
  myRet_t result;

  pars.mode = (myTimerMode_Periodic + 1);
  result = myTimer_Init(&timer, &pars);

  TEST_ASSERT_EQUAL(myRet_Fail, result);
}

/**
 * @brief When parameters are valid myTimer_Init logic should enable the
 *          peripheral clock by calling the routine CLOCK_SetTpmClock.
 */
void test_LogicCallsCLOCK_SetTpmClock(void)
{
  myTimer_Init(&timer, &pars);

  TEST_ASSERT_CALLED(CLOCK_SetTpmClock);
}

/**
 * @brief When parameters are valid myTimer_Init logic should initialize the
 *          timer peripheral by calling the routine TPM_Init.
 */
void test_LogicCallsTPM_Init(void)
{
  myTimer_Init(&timer, &pars);

  TEST_ASSERT_CALLED(TPM_Init);
}

/**
 * @brief When parameters are valid myTimer_Init logic should enable the
 *          timer peripheral interrupts by calling the routine
 *          TPM_EnableInterrupts.
 */
void test_LogicCallsTPM_EnableInterrupts(void)
{
  myTimer_Init(&timer, &pars);

  TEST_ASSERT_CALLED(TPM_EnableInterrupts);
}

/**
 * @brief When parameters are valid myTimer_Init logic should enable general
 *          interrupts by calling the routine EnableIRQ.
 */
void test_LogicCallsEnableIRQ(void)
{
  myTimer_Init(&timer, &pars);

  TEST_ASSERT_CALLED(EnableIRQ);
}

/**
 * @brief myTimer_Init logic should return ok when initialization ends well.
 */
void test_IfAllIsOkThenItSucceeds(void)
{
  const myRet_t result = myTimer_Init(&timer, &pars);

  TEST_ASSERT_EQUAL(myRet_OK, result);
}

/**
 * @brief myTimer_Init logic should return a valid timer pointer when
 *          initialization ends well.
 */
void test_IfAllIsOkThenItReturnsValidTimer(void)
{
  myTimer_Init(&timer, &pars);

  TEST_ASSERT_NOT_NULL(timer);
}

/*******************************************************************************
 *  PRIVATE FUNCTIONS / ROUTINES
 ******************************************************************************/
static void setValidTimerPars(void)
{
  pars.mode = myTimerMode_Periodic;
}
