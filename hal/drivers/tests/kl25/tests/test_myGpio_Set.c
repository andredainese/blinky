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
 * @file test_myGpio_Set.c
 * @brief Test file for testing gpio driver logic, operation when
 *          test_myGpio_Set is called, after correct initialization.
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
#define TEST_MY_GPIO_PORT                                       myDriverPort_PTB
#define TEST_MY_GPIO_PIN                                          myDriverPin_19

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
 * @brief myGpio_Set logic should call GPIO_WritePinOutput
 */
void test_LogicCallsGPIOWritePinOutput(void)
{
  myGpio_Set(pin, myGpioLvl_Lo);

  TEST_ASSERT_CALLED(GPIO_WritePinOutput);
}

/**
 * @brief myGpio_Set logic should call GPIO_WritePinOutput with the correct
 *          GPIO pointer.
 */
void test_LogicCallsGPIOWritePinOutputWithCorrectGpio(void)
{
  const GPIO_Type * expect = GPIOB;

  /* This test only works if configured port is PTB.                          */
  if(pars.port != (uint8_t) myDriverPort_PTB)
  {
    TEST_NOT_POSSIBLE();
  }
  else
  {
    myGpio_Set(pin, myGpioLvl_Lo);

    TEST_ASSERT_EQUAL_PTR(expect, GPIO_WritePinOutput_fake.arg0_val);
  }
}

/**
 * @brief myGpio_Set logic should call GPIO_WritePinOutput with the correct
 *          pin value.
 */
void test_LogicCallsGPIOWritePinOutputWithCorrectPin(void)
{
  const uint32_t expect = TEST_MY_GPIO_PIN;

  myGpio_Set(pin, myGpioLvl_Lo);

  TEST_ASSERT_EQUAL(expect, GPIO_WritePinOutput_fake.arg1_val);
}

/**
 * @brief myGpio_Set logic should call GPIO_WritePinOutput with pin level zero
 *          when requested level is Low
 */
void test_IfSetIsCalledRequestingLowLevelThenGPIOWritePinOutputIsCalledWithOutputZero(void)
{
  const uint8_t expect = 0;

  myGpio_Set(pin, myGpioLvl_Lo);

  TEST_ASSERT_EQUAL(expect, GPIO_WritePinOutput_fake.arg2_val);
}

/**
 * @brief myGpio_Set logic should call GPIO_WritePinOutput with pin level one
 *          when requested level is High
 */
void test_IfSetIsCalledRequestingLowLevelThenGPIOWritePinOutputIsCalledWithOutputOne(void)
{
  const uint8_t expect = 1;

  myGpio_Set(pin, myGpioLvl_Hi);

  TEST_ASSERT_EQUAL(expect, GPIO_WritePinOutput_fake.arg2_val);
}

/**
 * @brief myGpio_Set logic should not call GPIO_WritePinOutput if pin argument
 *          is invalid.
 */
void test_IfPinArgIsNullThenLogicDoesNotCallGPIOWritePinOutput(void)
{
  myGpio_Set(NULL, myGpioLvl_Hi);

  TEST_ASSERT_NOT_CALLED(GPIO_WritePinOutput);
}

/*******************************************************************************
 *  PRIVATE FUNCTIONS / ROUTINES
 ******************************************************************************/
static void initializePin(void)
{
  pars.port = TEST_MY_GPIO_PORT;
  pars.pin = TEST_MY_GPIO_PIN;
  pars.direction = myGpioDir_Outp;
  pars.pull = myGpioPull_No;

  myGpio_Init(&pin, &pars);
}
