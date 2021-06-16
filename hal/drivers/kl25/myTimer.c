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
 * This file implements the Timer driver for KL25 devices.
 */

/*******************************************************************************
 *  INCLUDES
 ******************************************************************************/
#include "myTimer.h"
#include "projConfig.h"

#include "fsl_tpm.h"
#include "fsl_clock.h"
#include "fsl_common.h"
#include "myTimer_TPM.h"

#include "myAssert.h"
#include "myMacros.h"

/*******************************************************************************
 *  PRIVATE DEFINITIONS
 ******************************************************************************/
/* The structure below holds all the items related to a timer instance.       */
typedef struct
{
  TPM_Type * TPM;
  myCbk_t cbk;
} myTimerStruct_t;

/* The enumeration below lists all the TPMs that are available to use.        */
typedef enum
{
  myTimer_TPM0 = 0,
  myTimer_TPM1,
  myTimer_TPM2,
  myTimer_TPM_Count, /* Not an item! For counting only.                       */
} myTimerTPMs_t;

#define TPM_CLK_SEL_OSCERCLK_CLK                                              2U  /* TPM clock select: OSCERCLK clock */

/*******************************************************************************
 *  PRIVATE PROTOTYPES
 ******************************************************************************/
static void myTimer_Interrupt(myTimerTPMs_t source);

/*******************************************************************************
 *  PRIVATE VARIABLES
 ******************************************************************************/
static TPM_Type * const myTimer_TPMs[] = TPM_BASE_PTRS;
static const uint32_t myTimer_TPMCnt = MY_ARRAY_SIZE(myTimer_TPMs);
static const IRQn_Type myTimer_IRQs[] = TPM_IRQS;

static myTimerStruct_t myTimer_Struct[myTimer_TPM_Count];
static myTimerTPMs_t myTimer_NextTPM = myTimer_TPM0;

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
    /* Only periodic mode is currently supported.                             */
    myASSERT(pars->mode == myTimerMode_Periodic);

    if(pars->mode == myTimerMode_Periodic)
    {
      /* Proceed with initialization only if there is a TPM available.        */
      const myTimerTPMs_t thisTPM = myTimer_NextTPM++;

      myASSERT(myTimer_TPMCnt == myTimer_TPM_Count);
      myASSERT(thisTPM < myTimer_TPMCnt);

      if(thisTPM >= myTimer_TPMCnt) { myTimer_NextTPM--; }
      else
      {
        TPM_Type * const periph = myTimer_TPMs[thisTPM];
        myTimerStruct_t * strc = &myTimer_Struct[thisTPM];
        const IRQn_Type irq = myTimer_IRQs[thisTPM];
        tpm_config_t config;

        strc->TPM = periph;
        strc->cbk = NULL;

        TPM_GetDefaultConfig(&config);
        config.prescale = kTPM_Prescale_Divide_128;
        config.enableStopOnOverflow = false;
        CLOCK_SetTpmClock(TPM_CLK_SEL_OSCERCLK_CLK);
        TPM_Init(periph, &config);
        TPM_EnableInterrupts(periph, kTPM_TimeOverflowInterruptEnable);
        EnableIRQ(irq);

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

  if((timer != NULL) && (period != 0) && (cbk != NULL))
  {
    const uint32_t freq = CLOCK_GetOsc0ErClkFreq() / 128;
    const uint32_t counts = MSEC_TO_COUNT(period, freq);
    myTimerStruct_t * strc = (myTimerStruct_t *) timer;
    TPM_Type * const periph = strc->TPM;

    strc->cbk = cbk;

    TPM_StopTimer(periph);
    TPM_ClearCounter(periph);
    TPM_SetTimerPeriod(periph, counts);
    TPM_StartTimer(periph, kTPM_SystemClock);

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
void myTimer_Reset(void)
{
  myTimer_NextTPM = myTimer_TPM0;
}
#endif

/*******************************************************************************
 *  PRIVATE FUNCTIONS / ROUTINES
 ******************************************************************************/
static void myTimer_Interrupt(myTimerTPMs_t source)
{
  myTimerStruct_t * strc = &myTimer_Struct[source];
  const myCbk_t cbk = strc->cbk;

  TPM_ClearStatusFlags(strc->TPM, kTPM_TimeOverflowFlag);

  if(cbk != NULL) { cbk(); }
}

/*******************************************************************************
 *  INTERRUPT ROUTINES
 ******************************************************************************/
void TPM0_IRQHandler(void)
{
  myTimer_Interrupt(myTimer_TPM0);
}

void TPM1_IRQHandler(void)
{
  myTimer_Interrupt(myTimer_TPM1);
}

void TPM2_IRQHandler(void)
{
  myTimer_Interrupt(myTimer_TPM2);
}
