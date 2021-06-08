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

#include "mock_stm32f1xx_hal.h"
#include "mock_stm32f1xx_hal_gpio.h"
#include "mock_stm32f1xx_hal_rcc.h"

/*******************************************************************************
 *  PRIVATE DEFINITIONS
 ******************************************************************************/
#define TEST_MY_GPIO_PORT                                        myDriverPort_PC
#define TEST_MY_GPIO_PIN                                          myDriverPin_10

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
 * @brief myGpio_Get logic should call HAL_GPIO_ReadPin
 */
void test_LogicCallsHAL_GPIO_ReadPin(void)
{
  myGpio_Get(pin);

  TEST_ASSERT_CALLED(HAL_GPIO_ReadPin);
}

/**
 * @brief myGpio_Get logic should call HAL_GPIO_ReadPin with the correct
 *          GPIO pointer.
 */
void test_LogicCallsHAL_GPIO_ReadPinWithCorrectGpio(void)
{
  const GPIO_TypeDef * expect = GPIOC;

  /* This test only works if configured port is PC.                           */
  if(pars.port != (uint8_t) myDriverPort_PC)
  {
    TEST_NOT_POSSIBLE();
  }
  else
  {
    myGpio_Get(pin);

    TEST_ASSERT_EQUAL_PTR(expect, HAL_GPIO_ReadPin_fake.arg0_val);
  }
}

/**
 * @brief myGpio_Get logic should call HAL_GPIO_ReadPin with the correct
 *          pin value.
 */
void test_LogicCallsHAL_GPIO_ReadPinWithCorrectPin(void)
{
  const uint32_t expect = (0x01 << TEST_MY_GPIO_PIN);

  myGpio_Get(pin);

  TEST_ASSERT_EQUAL(expect, HAL_GPIO_ReadPin_fake.arg1_val);
}

/**
 * @brief myGpio_Get logic should inform that level is low if HAL_GPIO_ReadPin
 *          returns GPIO_PIN_RESET.
 */
void test_IfHAL_GPIO_ReadPinAnswersZeroThenLogicReturnsLowLevel(void)
{
  myGpioLvl_t expect = myGpioLvl_Lo;
  myGpioLvl_t result;

  HAL_GPIO_ReadPin_fake.return_val = GPIO_PIN_RESET;
  result = myGpio_Get(pin);

  TEST_ASSERT_EQUAL(expect, result);
}

/**
 * @brief myGpio_Get logic should inform that level is high if HAL_GPIO_ReadPin
 *          returns GPIO_PIN_SET.
 */
void test_IfHAL_GPIO_ReadPinAnswersOneThenLogicReturnsHighLevel(void)
{
  myGpioLvl_t expect = myGpioLvl_Hi;
  myGpioLvl_t result;

  HAL_GPIO_ReadPin_fake.return_val = GPIO_PIN_SET;
  result = myGpio_Get(pin);

  TEST_ASSERT_EQUAL(expect, result);
}

/**
 * @brief myGpio_Get logic should not call HAL_GPIO_ReadPin if pin argument
 *          is invalid.
 */
void test_IfPinArgIsNullThenLogicDoesNotCallHAL_GPIO_ReadPin(void)
{
  myGpio_Get(NULL);

  TEST_ASSERT_NOT_CALLED(HAL_GPIO_ReadPin);
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
