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

#include "mock_fsl_tpm.h"
#include "mock_fsl_clock.h"
#include "mock_fsl_common.h"
#include "mock_myTimer_TPM.h"

/*******************************************************************************
 *  PRIVATE DEFINITIONS
 ******************************************************************************/
#define TEST_PERIOD_MS                                                     (100)

/*******************************************************************************
 *  PRIVATE PROTOTYPES
 ******************************************************************************/
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
 * @brief When a timer is started then logic should get which is the TPMs'
 *          base clock by calling the CLOCK_GetOsc0ErClkFreq routine.
 */
void test_LogicCallsCLOCK_GetOsc0ErClkFreq(void)
{
  TEST_ASSERT_CALLED(CLOCK_GetOsc0ErClkFreq);
}

/**
 * @brief When a timer is started then logic should make sure that the TPM
 *          is not running, so it should call TPM_StopTimer routine.
 */
void test_LogicCallsTPM_StopTimer(void)
{
  TEST_ASSERT_CALLED(TPM_StopTimer);
}

/**
 * @brief If the timer being started was already running then it is very
 *          likely that its counter is not zero. Therefore, in order to make
 *          sure that the counting period is correct logic should call
 *          TPM_ClearCounter routine.
 */
void test_LogicCallsTPM_ClearCounter(void)
{
  TEST_ASSERT_CALLED(TPM_ClearCounter);
}

/**
 * @brief When a timer is started then logic should set the counting period
 *          by calling TPM_SetTimerPeriod routine.
 */
void test_LogicCallsTPM_SetTimerPeriod(void)
{
  TEST_ASSERT_CALLED(TPM_SetTimerPeriod);
}

/**
 * @brief When a timer is started then logic should effectively starting the
 *          time count by calling TPM_StartTimer routine.
 */
void test_LogicCallsTPM_StartTimer(void)
{
  TEST_ASSERT_CALLED(TPM_StartTimer);
}

/*******************************************************************************
 *  PRIVATE FUNCTIONS / ROUTINES
 ******************************************************************************/
static void setValidTimerPars(void)
{
  pars.mode = myTimerMode_Periodic;
}

static void timerCallback(void)
{
}
