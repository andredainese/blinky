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
 * This file implements the Gpio driver for KL25 devices.
 */

/*******************************************************************************
 *  INCLUDES
 ******************************************************************************/
#include "myGpio.h"
#include "myDriverDefs.h"
#include "projConfig.h"

#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_clock.h"
#include "fsl_common.h"

#include "myMacros.h"
#include "myAssert.h"

/*******************************************************************************
 *  PRIVATE DEFINITIONS
 ******************************************************************************/
/* The structure below holds all the items related to a gpio pin instance.    */
typedef struct
{
  GPIO_Type * GPIO;
  uint32_t pin;
} myGpioPinStruct_t;

/* Set below the maximum amount of pins that the driver can handle.           */
#ifndef DRIVER_GPIO_PIN_AMOUNT
  #define DRIVER_GPIO_PIN_AMOUNT                                               4
#endif

/*******************************************************************************
 *  PRIVATE PROTOTYPES
 ******************************************************************************/
static bool parsAreValid(myGpioPars_t * pars);

/*******************************************************************************
 *  PRIVATE VARIABLES
 ******************************************************************************/
static GPIO_Type * const myGpio_GPIOs[] = GPIO_BASE_PTRS;
static PORT_Type * const myGpio_PORTs[] = PORT_BASE_PTRS;
static const uint32_t myGpio_GPIOCnt = MY_ARRAY_SIZE(myGpio_GPIOs);

static const clock_ip_name_t myGpio_Clocks[] = { kCLOCK_PortA, kCLOCK_PortB, kCLOCK_PortC, kCLOCK_PortD, kCLOCK_PortE };

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
    myASSERT(pars->pin <= myDriverPin_31);
    myASSERT(pars->direction <= myGpioDir_Outp);

    if(parsAreValid(pars))
    {
      const uint32_t thisGpio = myGpio_NextPin++;
      myASSERT(thisGpio < DRIVER_GPIO_PIN_AMOUNT);

      if(thisGpio >= DRIVER_GPIO_PIN_AMOUNT) { myGpio_NextPin--; }
      else
      {
        GPIO_Type * const periph = myGpio_GPIOs[pars->port];
        PORT_Type * const port = myGpio_PORTs[pars->port];
        clock_ip_name_t clock = myGpio_Clocks[pars->port];
        myGpioPinStruct_t * strc = &myGpio_Struct[thisGpio];

        strc->GPIO = periph;
        strc->pin = pars->pin;

        /* First initialize the GPIO settings.                                */
        {
          gpio_pin_config_t gpioCfg;

          CLOCK_EnableClock(clock);

          if(pars->direction == myGpioDir_Inpt) { gpioCfg.pinDirection = kGPIO_DigitalInput;  }
          else                                  { gpioCfg.pinDirection = kGPIO_DigitalOutput; }
          gpioCfg.outputLogic = 0;

          GPIO_PinInit(periph, strc->pin, &gpioCfg);
        }

        /* Now initializes the PORT settings.                                 */
        {
          port_pin_config_t portCfg;

          if(pars->direction == myGpioDir_Inpt)
          {
            switch(pars->pull)
            {
              case myGpioPull_Dw: { portCfg.pullSelect = kPORT_PullDown;    } break;
              case myGpioPull_Up: { portCfg.pullSelect = kPORT_PullUp;      } break;
              default:            { portCfg.pullSelect = kPORT_PullDisable; } break;
            }
          }
          else
          {
            portCfg.pullSelect = kPORT_PullDisable;
          }

          portCfg.slewRate = kPORT_SlowSlewRate;
          portCfg.passiveFilterEnable = kPORT_PassiveFilterDisable;
          portCfg.driveStrength = kPORT_LowDriveStrength;
          portCfg.mux = kPORT_MuxAsGpio;

          PORT_SetPinConfig(port, strc->pin, &portCfg);
        }

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
  myGpioPinStruct_t * strc = (myGpioPinStruct_t *) pin;
  uint32_t value;
  myGpioLvl_t lvl = myGpioLvl_Lo;

  myASSERT(strc != NULL);

  if(strc != NULL)
  {
    value = GPIO_ReadPinInput(strc->GPIO, strc->pin);
    if(value != 0) { lvl = myGpioLvl_Hi; }
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
  myGpioPinStruct_t * strc = (myGpioPinStruct_t *) pin;
  uint8_t output;
  myRet_t result = myRet_Fail;

  myASSERT(strc != NULL);
  myASSERT(lvl <= myGpioLvl_Hi);

  if(strc != NULL)
  {
    if(lvl == myGpioLvl_Lo) { output = 0; }
    else                    { output = 1; }

    GPIO_WritePinOutput(strc->GPIO, strc->pin, output);
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
static bool parsAreValid(myGpioPars_t * pars)
{
  bool areValid;

  if( (pars->port < myGpio_GPIOCnt) && (pars->pin <= myDriverPin_31) &&
      (pars->direction <= myGpioDir_Outp) && (pars->pull <= myGpioPull_Dw) )
  {
    areValid = true;
  }
  else
  {
    areValid = false;
  }

  return areValid;
}
