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
 * @file myGpio.h
 * @brief Source file for general purpose input output operations.
 *
 * This file implements the Gpio driver for STM32F10x devices.
 */

/*******************************************************************************
 *  INCLUDES
 ******************************************************************************/
#include "myGpio.h"
#include "myDriverDefs.h"
#include "projConfig.h"

#include "stm32f1xx_hal.h"

#include "myAssert.h"

/*******************************************************************************
 *  PRIVATE DEFINITIONS
 ******************************************************************************/
/* The structure below holds all the items related to a gpio pin instance.    */
typedef struct
{
  GPIO_TypeDef * GPIO;
  uint16_t pinMask;
} myGpioPinStruct_t;

/* Set below the maximum amount of pins that the driver can handle.           */
#ifndef DRIVER_GPIO_PIN_AMOUNT
  #define DRIVER_GPIO_PIN_AMOUNT                                               4
#endif

/*******************************************************************************
 *  PRIVATE PROTOTYPES
 ******************************************************************************/

/*******************************************************************************
 *  PRIVATE VARIABLES
 ******************************************************************************/
static GPIO_TypeDef * const myGpio_GPIOs[] = { GPIOA, GPIOB, GPIOC, GPIOD, GPIOE };
static const uint32_t myGpio_GPIOCnt = sizeof(myGpio_GPIOs) / sizeof(myGpio_GPIOs[0]);

static myGpioPinStruct_t myGpio_Struct[DRIVER_GPIO_PIN_AMOUNT];
static uint32_t myGpio_NextPin = 0;

/*******************************************************************************
 *  PUBLIC FUNCTIONS / ROUTINES
 ******************************************************************************/
/**
 * @brief Initialization routine for a gpio pin.
 * @param pin If successful, it will be written with the data required to use
 *              this pin in the future.
 * @param pars Structure containing all the data required to initialize this
 *              pin.
 * @return Success / Failure
 */
myRet_t myGpio_Init(myGpioPin_t * pin, myGpioPars_t * pars)
{
  myRet_t result = myRet_Fail;

  if((pin != NULL) && (pars != NULL))
  {
    myASSERT(pars->port < myGpio_GPIOCnt);
    myASSERT(pars->pin <= myDriverPin_15);
    myASSERT(pars->direction <= myGpioDir_Outp);
    myASSERT(pars->pull <= myGpioPull_Dw);

    if((pars->port < myGpio_GPIOCnt) && (pars->pin <= myDriverPin_15) && (pars->direction <= myGpioDir_Outp) && (pars->pull <= myGpioPull_Dw))
    {
      const uint32_t thisGpio = myGpio_NextPin++;
      myASSERT(thisGpio < DRIVER_GPIO_PIN_AMOUNT);

      if(thisGpio >= DRIVER_GPIO_PIN_AMOUNT) { myGpio_NextPin--; }
      else
      {
        GPIO_TypeDef * const periph = myGpio_GPIOs[pars->port];
        myGpioPinStruct_t * strc = &myGpio_Struct[thisGpio];
        GPIO_InitTypeDef gpioCfg;

        strc->GPIO = periph;
        strc->pinMask = (0x01 << pars->pin);

        gpioCfg.Pin = strc->pinMask;
        gpioCfg.Speed = GPIO_SPEED_FREQ_LOW;

        if(pars->direction == myGpioDir_Outp)
        {
          gpioCfg.Mode = GPIO_MODE_OUTPUT_PP;
          gpioCfg.Pull = GPIO_NOPULL;
        }
        else
        {
          gpioCfg.Mode = GPIO_MODE_INPUT;

          switch(pars->pull)
          {
            case myGpioPull_Dw: { gpioCfg.Pull = GPIO_PULLDOWN;    } break;
            case myGpioPull_Up: { gpioCfg.Pull = GPIO_PULLUP;      } break;
            default:            { gpioCfg.Pull = GPIO_NOPULL;      } break;
          }
        }

        /* Enable the clock for the required port and initialize this pin.    */
        switch(pars->port)
        {
          case myDriverPort_PA:  { __HAL_RCC_GPIOA_CLK_ENABLE(); } break;
          case myDriverPort_PB:  { __HAL_RCC_GPIOB_CLK_ENABLE(); } break;
          case myDriverPort_PC:  { __HAL_RCC_GPIOC_CLK_ENABLE(); } break;
          case myDriverPort_PD:  { __HAL_RCC_GPIOD_CLK_ENABLE(); } break;
          case myDriverPort_PE:  { __HAL_RCC_GPIOE_CLK_ENABLE(); } break;
          default:               { myASSERT(false);              } break;
        }

        HAL_GPIO_Init(periph, &gpioCfg);

        /* Init is complete.                                                  */
        *pin = (myGpioPin_t) strc;
        result = myRet_OK;
      }
    }
  }

  return result;
}

/**
 * @brief Gets the level of a given pin.
 * @param pin Info about the pin to get the level from.
 * @return Current level. If routine fails, it returns low level.
 */
myGpioLvl_t myGpio_Get(myGpioPin_t pin)
{
  myGpioLvl_t lvl = myGpioLvl_Lo;
  myASSERT(pin != NULL);

  if(pin != NULL)
  {
    myGpioPinStruct_t * strc = (myGpioPinStruct_t *) pin;
    GPIO_PinState state;

    state = HAL_GPIO_ReadPin(strc->GPIO, strc->pinMask);

    if(state == GPIO_PIN_RESET) { lvl = myGpioLvl_Lo; }
    else                        { lvl = myGpioLvl_Hi; }
  }

  return lvl;
}

/**
 * @brief Sets the level of an output pin.
 * @param pin Info about the pin to get the level from.
 * @param lvl Level to set the pin to.
 * @return Success / Failure
 */
myRet_t myGpio_Set(myGpioPin_t pin, myGpioLvl_t lvl)
{
  myRet_t result = myRet_Fail;
  myASSERT(pin != NULL);
  myASSERT(lvl <= myGpioLvl_Hi);

  if(pin != NULL)
  {
    myGpioPinStruct_t * strc = (myGpioPinStruct_t *) pin;
    GPIO_PinState state;

    if(lvl == myGpioLvl_Lo) { state = GPIO_PIN_RESET; }
    else                    { state = GPIO_PIN_SET;   }

    HAL_GPIO_WritePin(strc->GPIO, strc->pinMask, state);
    result = myRet_OK;
  }

  return result;
}

/*******************************************************************************
 *  PUBLIC FUNCTIONS / ROUTINES - TEST PURPOSES
 ******************************************************************************/
#ifdef TEST
/**
 * @brief Resets driver's internal logic and its variables.
 */
void myGpio_Reset(void)
{
  myGpio_NextPin = 0;
}
#endif

/*******************************************************************************
 *  PRIVATE FUNCTIONS / ROUTINES
 ******************************************************************************/
