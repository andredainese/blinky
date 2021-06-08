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
 * @file test_myGpio_Init.c
 * @brief Test file for testing gpio driver logic, operation when
 *          myGpio_Init is called.
 */

/*******************************************************************************
 *  INCLUDES
 ******************************************************************************/
#include "unity.h"
#include "myTestDefs.h"

#include "myGpio.h"
#include "myDriverDefs.h"

#include "mock_fsl_gpio.h"
#include "mock_fsl_port.h"
#include "mock_fsl_clock.h"
#include "mock_fsl_common.h"

/*******************************************************************************
 *  PRIVATE DEFINITIONS
 ******************************************************************************/

/*******************************************************************************
 *  PRIVATE PROTOTYPES
 ******************************************************************************/
static void setValidPinPars(void);

/*******************************************************************************
 *  PRIVATE VARIABLES
 ******************************************************************************/
static myGpioPin_t pin;
static myGpioPars_t pars;

/*******************************************************************************
 *  SET UP / TEAR DOWN
 ******************************************************************************/
void setUp(void)
{
  setValidPinPars();
  myGpio_Reset();
  pin = NULL;
}

void tearDown(void)
{
}

/*******************************************************************************
 *  TESTS
 ******************************************************************************/
/**
 * @brief myGpio_Init logic should return fail if pin argument is invalid.
 */
void test_IfPinArgIsInvalidThenItFails(void)
{
  const myRet_t result = myGpio_Init(NULL, &pars);

  TEST_ASSERT_EQUAL(myRet_Fail, result);
}

/**
 * @brief myGpio_Init logic should return fail if pars argument is invalid.
 */
void test_IfParsArgIsInvalidThenItFails(void)
{
  const myRet_t result = myGpio_Init(&pin, NULL);

  TEST_ASSERT_EQUAL(myRet_Fail, result);
}

/**
 * @brief myGpio_Init logic should return fail if port selection is invalid,
 *          above valid values.
 */
void test_IfPortIsAboveLimitThenItFails(void)
{
  myRet_t result;

  pars.port = (myDriverPort_PTE + 1);
  result = myGpio_Init(&pin, &pars);

  TEST_ASSERT_EQUAL(myRet_Fail, result);
}

/**
 * @brief myGpio_Init logic should return fail if pin selection is invalid,
 *          above valid values.
 */
void test_IfPinIsAboveLimitThenItFails(void)
{
  myRet_t result;

  pars.pin = (myDriverPin_31 + 1);
  result = myGpio_Init(&pin, &pars);

  TEST_ASSERT_EQUAL(myRet_Fail, result);
}

/**
 * @brief myGpio_Init logic should return fail if direction selection is
 *          invalid, above  valid values.
 */
void test_IfDirectionIsInvalidThenItFails(void)
{
  myRet_t result;

  pars.direction = (myGpioDir_t)(myGpioDir_Outp + 1);
  result = myGpio_Init(&pin, &pars);

  TEST_ASSERT_EQUAL(myRet_Fail, result);
}

/**
 * @brief myGpio_Init logic should return fail if pull selection is invalid,
 *          above valid values.
 */
void test_IfPullIsInvalidThenItFails(void)
{
  myRet_t result;

  pars.pull = (myGpioPull_t)(myGpioPull_Dw + 1);
  result = myGpio_Init(&pin, &pars);

  TEST_ASSERT_EQUAL(myRet_Fail, result);
}

/**
 * @brief When parameters are valid myGpio_Init logic should enable the
 *          peripheral clock by calling the routine CLOCK_EnableClock.
 */
void test_GpioInitCallsCLOCK_EnableClock(void)
{
  myGpio_Init(&pin, &pars);

  TEST_ASSERT_CALLED(CLOCK_EnableClock);
}

/**
 * @brief When parameters are valid myGpio_Init logic should initialize the
 *          gpio peripheral by calling the routine GPIO_PinInit.
 */
void test_GpioInitCallsGPIO_PinInit(void)
{
  myGpio_Init(&pin, &pars);

  TEST_ASSERT_CALLED(GPIO_PinInit);
}

/**
 * @brief When parameters are valid myGpio_Init logic should initialize the
 *          port peripheral by calling the routine PORT_SetPinConfig.
 */
void test_GpioInitCallsPORT_SetPinConfig(void)
{
  myGpio_Init(&pin, &pars);

  TEST_ASSERT_CALLED(PORT_SetPinConfig);
}

/**
 * @brief myGpio_Init logic should return ok when initialization ends well.
 */
void test_IfAllIsOkThenItSucceeds(void)
{
  const myRet_t result = myGpio_Init(&pin, &pars);

  TEST_ASSERT_EQUAL(myRet_OK, result);
}

/**
 * @brief myGpio_Init logic should return a valid pin pointer when initialization ends well.
 */
void test_IfAllIsOkThenItReturnsValidPin(void)
{
  myGpio_Init(&pin, &pars);

  TEST_ASSERT_NOT_NULL(pin);
}

/*******************************************************************************
 *  PRIVATE FUNCTIONS / ROUTINES
 ******************************************************************************/
static void setValidPinPars(void)
{
  pars.port = myDriverPort_PTA;
  pars.pin = myDriverPin_00;
  pars.direction = myGpioDir_Inpt;
  pars.pull = myGpioPull_No;
}
