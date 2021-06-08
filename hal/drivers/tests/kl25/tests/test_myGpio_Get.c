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
 * @file test_myGpio_Get.c
 * @brief Test file for testing gpio driver logic, operation when
 *          test_myGpio_Get is called, after correct initialization.
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
#define TEST_MY_GPIO_PORT                                       myDriverPort_PTC
#define TEST_MY_GPIO_PIN                                          myDriverPin_16

/*******************************************************************************
 *  PRIVATE PROTOTYPES
 ******************************************************************************/
static void initializePin(void);

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
  myGpio_Reset();
  initializePin();
}

void tearDown(void)
{
}

/*******************************************************************************
 *  TESTS
 ******************************************************************************/
/**
 * @brief myGpio_Get logic should call GPIO_ReadPinInput
 */
void test_LogicCallsGPIOReadPinInput(void)
{
  myGpio_Get(pin);

  TEST_ASSERT_CALLED(GPIO_ReadPinInput);
}

/**
 * @brief myGpio_Get logic should call GPIO_ReadPinInput with the correct
 *          GPIO pointer.
 */
void test_LogicCallsGPIOReadPinInputWithCorrectGpio(void)
{
  const GPIO_Type * expect = GPIOC;

  /* This test only works if configured port is PTC.                          */
  if(pars.port != (uint8_t) myDriverPort_PTC)
  {
    TEST_NOT_POSSIBLE();
  }
  else
  {
    myGpio_Get(pin);

    TEST_ASSERT_EQUAL_PTR(expect, GPIO_ReadPinInput_fake.arg0_val);
  }
}

/**
 * @brief myGpio_Get logic should call GPIO_ReadPinInput with the correct
 *          pin value.
 */
void test_LogicCallsGPIOReadPinInputWithCorrectPin(void)
{
  const uint32_t expect = TEST_MY_GPIO_PIN;

  myGpio_Get(pin);

  TEST_ASSERT_EQUAL(expect, GPIO_ReadPinInput_fake.arg1_val);
}

/**
 * @brief myGpio_Get logic should inform that level is low if GPIO_ReadPinInput
 *          returns 0.
 */
void test_IfGPIOReadPinAnswersZeroThenLogicReturnsLowLevel(void)
{
  myGpioLvl_t expect = myGpioLvl_Lo;
  myGpioLvl_t result;

  GPIO_ReadPinInput_fake.return_val = 0;
  result = myGpio_Get(pin);

  TEST_ASSERT_EQUAL(expect, result);
}

/**
 * @brief myGpio_Get logic should inform that level is high if GPIO_ReadPinInput
 *          returns 1.
 */
void test_IfGPIOReadPinAnswersOneThenLogicReturnsHighLevel(void)
{
  myGpioLvl_t expect = myGpioLvl_Hi;
  myGpioLvl_t result;

  GPIO_ReadPinInput_fake.return_val = 1;
  result = myGpio_Get(pin);

  TEST_ASSERT_EQUAL(expect, result);
}

/**
 * @brief myGpio_Get logic should not call GPIO_ReadPinInput if pin argument
 *          is invalid.
 */
void test_IfPinArgIsNullThenLogicDoesNotCallGPIOReadPinInput(void)
{
  myGpio_Get(NULL);

  TEST_ASSERT_NOT_CALLED(GPIO_ReadPinInput);
}

/*******************************************************************************
 *  PRIVATE FUNCTIONS / ROUTINES
 ******************************************************************************/
static void initializePin(void)
{
  pars.port = TEST_MY_GPIO_PORT;
  pars.pin = TEST_MY_GPIO_PIN;
  pars.direction = myGpioDir_Inpt;
  pars.pull = myGpioPull_No;

  myGpio_Init(&pin, &pars);
}
