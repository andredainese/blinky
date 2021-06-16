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
 * @file myTimer.h
 * @brief Source file for simple time counting operations.
 *
 * This file implements the Timer driver for STM32F10x devices.
 */

/*******************************************************************************
 *  INCLUDES
 ******************************************************************************/
#include "myTimer.h"
#include "projConfig.h"

#include "stm32f1xx_hal.h"

#include "myAssert.h"

/*******************************************************************************
 *  PRIVATE DEFINITIONS
 ******************************************************************************/
/* The structure below holds all the items related to a timer instance.       */
typedef struct
{
  TIM_HandleTypeDef * handle;
  myCbk_t cbk;
} myTimerStruct_t;

/* The enumeration below lists all the TPMs that are available to use.        */
typedef enum
{
  myTimer_TIM3 = 0,
  myTimer_TIM4,
  myTimer_TIM_Count, /* Not an item! For counting only.                       */
} myTimerTIMs_t;

/* Set below the prescaler value that the peripherals will be set to use.     */
#define DRIVER_TIMER_PRESCALER                                            (1024)

/*******************************************************************************
 *  PRIVATE PROTOTYPES
 ******************************************************************************/

/*******************************************************************************
 *  PRIVATE VARIABLES
 ******************************************************************************/
static TIM_TypeDef * const myTimer_TIMs[] = {TIM3, TIM4};
static const IRQn_Type myTimer_IRQs[] = { TIM3_IRQn, TIM4_IRQn };
static const uint32_t myTimer_TIMCnt = sizeof(myTimer_TIMs) / sizeof(myTimer_TIMs[0]);

static TIM_HandleTypeDef myTimer_handle[myTimer_TIM_Count];
static myTimerStruct_t myTimer_Struct[myTimer_TIM_Count];
static myTimerTIMs_t myTimer_NextTIM = myTimer_TIM3;

static uint32_t myTimer_MaxMs;

/*******************************************************************************
 *  PUBLIC FUNCTIONS / ROUTINES
 ******************************************************************************/
/**
 * @brief Initialization routine for a timer.
 * @param timer If successful, it will be written with the data required to use
 *              this timer in the future.
 * @param pars Structure containing all the data required to initialize this
 *              timer.
 * @return Success / Failure
 */
myRet_t myTimer_Init(myTimer_t * timer, myTimerPars_t * pars)
{
  myRet_t result = myRet_Fail;

  if((timer != NULL) && (pars != NULL))
  {
    myASSERT(pars->mode == myTimerMode_Periodic);

    if(pars->mode == myTimerMode_Periodic)
    {
      /* Proceed with initialization only if there is a TIM available.          */
      const myTimerTIMs_t thisTIM = myTimer_NextTIM++;

      myASSERT(myTimer_TIMCnt == myTimer_TIM_Count);
      myASSERT(thisTIM < myTimer_TIMCnt);

      if(thisTIM >= myTimer_TIMCnt) { myTimer_NextTIM--; }
      else
      {
        TIM_TypeDef * const periph = myTimer_TIMs[thisTIM];
        const IRQn_Type IRQ = myTimer_IRQs[thisTIM];
        myTimerStruct_t * const strc = &myTimer_Struct[thisTIM];
        TIM_HandleTypeDef * const handle = &myTimer_handle[thisTIM];
        const uint32_t freq = HAL_RCC_GetPCLK1Freq();

        strc->handle = handle;
        strc->cbk = NULL;

        /* Calculate the maximum period that the TIM will be able to count.   */
        myASSERT(freq != 0);
        myTimer_MaxMs = (uint32_t)(((uint64_t)0x10000 * DRIVER_TIMER_PRESCALER * 1000) / freq);

        /* Prepare fields. Peripheral is not set now but when client requests */
        /*  to start it, which will be later.                                 */
        handle->Instance = periph;
        handle->Init.CounterMode = TIM_COUNTERMODE_UP;
        handle->Init.Prescaler = DRIVER_TIMER_PRESCALER;
        handle->Init.ClockDivision = 0;
        handle->Init.RepetitionCounter = 0;
        handle->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;

        /* Enable the required clock and interrupt.                           */
        switch(thisTIM)
        {
          case myTimer_TIM3: { __HAL_RCC_TIM3_CLK_ENABLE(); } break;
          case myTimer_TIM4: { __HAL_RCC_TIM4_CLK_ENABLE(); } break;
          default:           { myASSERT(false);             } break;
        }

        HAL_NVIC_SetPriority(IRQ, 15, 0);
        HAL_NVIC_EnableIRQ(IRQ);

        /* Initialization is complete.                                        */
        *timer = (myTimer_t) strc;
        result = myRet_OK;
      }
    }
  }

  return result;
}

/**
 * @brief Starts the time counting operation for a timer.
 * @param timer Timer to start the operation
 * @param period Time, in ms, to count
 * @param cbk Callback to be called when timer expires
 * @return Success / Failure. If successful, timer will start and callback
 *          will eventually be called.
 */
myRet_t myTimer_Start(myTimer_t timer, uint32_t period, myCbk_t cbk)
{
  myRet_t result = myRet_Fail;

  myASSERT(period < myTimer_MaxMs);

  if((timer != NULL) && (period != 0) && (cbk != NULL))
  {
    myTimerStruct_t * strc = (myTimerStruct_t *) timer;
    TIM_HandleTypeDef * handle = strc->handle;
    HAL_StatusTypeDef status;
    uint32_t counter;

    strc->cbk = cbk;

    /* Calculate the counter value to be set in the peripheral and put it.    */
    counter = (0x10000 * period) / myTimer_MaxMs;
    handle->Init.Period = counter - 1;

    /* Make sure that peripheral is stopped, then (re)init it and start it.   */
    HAL_TIM_Base_Stop_IT(handle);

    status = HAL_TIM_Base_Init(handle);
    myASSERT(status == HAL_OK);

    if(status == HAL_OK)
    {
      status = HAL_TIM_Base_Start_IT(handle);
      myASSERT(status == HAL_OK);

      if(status == HAL_OK) { result = myRet_OK; }
    }
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
void myTimer_Reset(void)
{
  myTimer_NextTIM = myTimer_TIM3;
}
#endif

/*******************************************************************************
 *  CALLBACK ROUTINES
 ******************************************************************************/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  myTimerTIMs_t thisTIM;
  bool foundTIM = false;

  for(thisTIM = 0; thisTIM < myTimer_TIM_Count; thisTIM++)
  {
    if(&myTimer_handle[thisTIM] == htim)
    {
      myTimerStruct_t * strc = &myTimer_Struct[thisTIM];
      const myCbk_t cbk = strc->cbk;

      foundTIM = true;
      if(cbk != NULL) { cbk(); }
      break;
    }
  }

  myASSERT(foundTIM);
}

/*******************************************************************************
 *  INTERRUPT ROUTINES
 ******************************************************************************/
void TIM3_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&myTimer_handle[myTimer_TIM3]);
}

void TIM4_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&myTimer_handle[myTimer_TIM4]);
}
