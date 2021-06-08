/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file fsl_tpm.h
 * @brief Header file for mocking the fsl_tpm sdk module.
 */

#ifndef _FSL_TPM_H_
#define _FSL_TPM_H_

#include "myDefs.h"
#include "fsl_common.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/** TPM - Register Layout Typedef                                             */
typedef void * TPM_Type;

/** TPM Peripherals' fake addresses                                           */
#define TPM0                                             ((TPM_Type) 0x12345678)
#define TPM1                                             ((TPM_Type) 0x12345679)
#define TPM2                                             ((TPM_Type) 0x1234567A)

/** Array initializer of TPM peripheral base pointers                         */
#define TPM_BASE_PTRS                                       { TPM0, TPM1, TPM2 }

/** Interrupt vectors for the TPM peripheral type                             */
#define TPM_IRQS                             { TPM0_IRQn, TPM1_IRQn, TPM2_IRQn }

/*!
 * @brief List of TPM channels.
 * @note Actual number of available channels is SoC dependent
 */
typedef enum _tpm_chnl
{
    kTPM_Chnl_0 = 0U, /*!< TPM channel number 0*/
    kTPM_Chnl_1,      /*!< TPM channel number 1 */
    kTPM_Chnl_2,      /*!< TPM channel number 2 */
    kTPM_Chnl_3,      /*!< TPM channel number 3 */
    kTPM_Chnl_4,      /*!< TPM channel number 4 */
    kTPM_Chnl_5,      /*!< TPM channel number 5 */
    kTPM_Chnl_6,      /*!< TPM channel number 6 */
    kTPM_Chnl_7       /*!< TPM channel number 7 */
} tpm_chnl_t;

/*! @brief TPM PWM operation modes */
typedef enum _tpm_pwm_mode
{
    kTPM_EdgeAlignedPwm = 0U, /*!< Edge aligned PWM */
    kTPM_CenterAlignedPwm,    /*!< Center aligned PWM */
#if defined(FSL_FEATURE_TPM_HAS_COMBINE) && FSL_FEATURE_TPM_HAS_COMBINE
    kTPM_CombinedPwm /*!< Combined PWM */
#endif
} tpm_pwm_mode_t;

/*! @brief TPM PWM output pulse mode: high-true, low-true or no output */
typedef enum _tpm_pwm_level_select
{
    kTPM_NoPwmSignal = 0U, /*!< No PWM output on pin */
    kTPM_LowTrue,          /*!< Low true pulses */
    kTPM_HighTrue          /*!< High true pulses */
} tpm_pwm_level_select_t;

/*! @brief Options to configure a TPM channel's PWM signal */
typedef struct _tpm_chnl_pwm_signal_param
{
    tpm_chnl_t chnlNumber;        /*!< TPM channel to configure.
                                       In combined mode (available in some SoC's, this represents the
                                       channel pair number */
    tpm_pwm_level_select_t level; /*!< PWM output active level select */
    uint8_t dutyCyclePercent;     /*!< PWM pulse width, value should be between 0 to 100
                                       0=inactive signal(0% duty cycle)...
                                       100=always active signal (100% duty cycle)*/
} tpm_chnl_pwm_signal_param_t;

/*!
 * @brief Trigger options available.
 *
 * This is used for both internal & external trigger sources (external option available in certain SoC's)
 *
 * @note The actual trigger options available is SoC-specific.
 */
typedef enum _tpm_trigger_select
{
    kTPM_Trigger_Select_0 = 0U,
    kTPM_Trigger_Select_1,
    kTPM_Trigger_Select_2,
    kTPM_Trigger_Select_3,
    kTPM_Trigger_Select_4,
    kTPM_Trigger_Select_5,
    kTPM_Trigger_Select_6,
    kTPM_Trigger_Select_7,
    kTPM_Trigger_Select_8,
    kTPM_Trigger_Select_9,
    kTPM_Trigger_Select_10,
    kTPM_Trigger_Select_11,
    kTPM_Trigger_Select_12,
    kTPM_Trigger_Select_13,
    kTPM_Trigger_Select_14,
    kTPM_Trigger_Select_15
} tpm_trigger_select_t;

/*! @brief TPM clock source selection*/
typedef enum _tpm_clock_source
{
    kTPM_SystemClock = 1U, /*!< System clock */
    kTPM_ExternalClock     /*!< External clock */
} tpm_clock_source_t;

/*! @brief TPM prescale value selection for the clock source*/
typedef enum _tpm_clock_prescale
{
    kTPM_Prescale_Divide_1 = 0U, /*!< Divide by 1 */
    kTPM_Prescale_Divide_2,      /*!< Divide by 2 */
    kTPM_Prescale_Divide_4,      /*!< Divide by 4 */
    kTPM_Prescale_Divide_8,      /*!< Divide by 8 */
    kTPM_Prescale_Divide_16,     /*!< Divide by 16 */
    kTPM_Prescale_Divide_32,     /*!< Divide by 32 */
    kTPM_Prescale_Divide_64,     /*!< Divide by 64 */
    kTPM_Prescale_Divide_128     /*!< Divide by 128 */
} tpm_clock_prescale_t;

/*!
 * @brief TPM config structure
 *
 * This structure holds the configuration settings for the TPM peripheral. To initialize this
 * structure to reasonable defaults, call the TPM_GetDefaultConfig() function and pass a
 * pointer to your config structure instance.
 *
 * The config struct can be made const so it resides in flash
 */
typedef struct _tpm_config
{
    tpm_clock_prescale_t prescale;      /*!< Select TPM clock prescale value */
    bool useGlobalTimeBase;             /*!< true: Use of an external global time base is enabled;
                                             false: disabled */
    tpm_trigger_select_t triggerSelect; /*!< Input trigger to use for controlling the counter operation */

    bool enableDoze;            /*!< true: TPM counter is paused in doze mode;
                                     false: TPM counter continues in doze mode */
    bool enableDebugMode;       /*!< true: TPM counter continues in debug mode;
                                     false: TPM counter is paused in debug mode */
    bool enableReloadOnTrigger; /*!< true: TPM counter is reloaded on trigger;
                                     false: TPM counter not reloaded */
    bool enableStopOnOverflow;  /*!< true: TPM counter stops after overflow;
                                     false: TPM counter continues running after overflow */
    bool enableStartOnTrigger;  /*!< true: TPM counter only starts when a trigger is detected;
                                     false: TPM counter starts immediately */
} tpm_config_t;

/*! @brief List of TPM interrupts */
typedef enum _tpm_interrupt_enable
{
    kTPM_Chnl0InterruptEnable = (1U << 0),       /*!< Channel 0 interrupt.*/
    kTPM_Chnl1InterruptEnable = (1U << 1),       /*!< Channel 1 interrupt.*/
    kTPM_Chnl2InterruptEnable = (1U << 2),       /*!< Channel 2 interrupt.*/
    kTPM_Chnl3InterruptEnable = (1U << 3),       /*!< Channel 3 interrupt.*/
    kTPM_Chnl4InterruptEnable = (1U << 4),       /*!< Channel 4 interrupt.*/
    kTPM_Chnl5InterruptEnable = (1U << 5),       /*!< Channel 5 interrupt.*/
    kTPM_Chnl6InterruptEnable = (1U << 6),       /*!< Channel 6 interrupt.*/
    kTPM_Chnl7InterruptEnable = (1U << 7),       /*!< Channel 7 interrupt.*/
    kTPM_TimeOverflowInterruptEnable = (1U << 8) /*!< Time overflow interrupt.*/
} tpm_interrupt_enable_t;

/*! @brief List of TPM flags */
typedef enum _tpm_status_flags
{
    kTPM_Chnl0Flag = (1U << 0),       /*!< Channel 0 flag */
    kTPM_Chnl1Flag = (1U << 1),       /*!< Channel 1 flag */
    kTPM_Chnl2Flag = (1U << 2),       /*!< Channel 2 flag */
    kTPM_Chnl3Flag = (1U << 3),       /*!< Channel 3 flag */
    kTPM_Chnl4Flag = (1U << 4),       /*!< Channel 4 flag */
    kTPM_Chnl5Flag = (1U << 5),       /*!< Channel 5 flag */
    kTPM_Chnl6Flag = (1U << 6),       /*!< Channel 6 flag */
    kTPM_Chnl7Flag = (1U << 7),       /*!< Channel 7 flag */
    kTPM_TimeOverflowFlag = (1U << 8) /*!< Time overflow flag */
} tpm_status_flags_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Ungates the TPM clock and configures the peripheral for basic operation.
 *
 * @note This API should be called at the beginning of the application using the TPM driver.
 *
 * @param base   TPM peripheral base address
 * @param config Pointer to user's TPM config structure.
 */
void TPM_Init(TPM_Type *base, const tpm_config_t *config);

/*!
 * @brief  Fill in the TPM config struct with the default settings
 *
 * The default values are:
 * @code
 *     config->prescale = kTPM_Prescale_Divide_1;
 *     config->useGlobalTimeBase = false;
 *     config->dozeEnable = false;
 *     config->dbgMode = false;
 *     config->enableReloadOnTrigger = false;
 *     config->enableStopOnOverflow = false;
 *     config->enableStartOnTrigger = false;
 *#if FSL_FEATURE_TPM_HAS_PAUSE_COUNTER_ON_TRIGGER
 *     config->enablePauseOnTrigger = false;
 *#endif
 *     config->triggerSelect = kTPM_Trigger_Select_0;
 *#if FSL_FEATURE_TPM_HAS_EXTERNAL_TRIGGER_SELECTION
 *     config->triggerSource = kTPM_TriggerSource_External;
 *#endif
 * @endcode
 * @param config Pointer to user's TPM config structure.
 */
void TPM_GetDefaultConfig(tpm_config_t *config);

/*!
 * @brief Enables the selected TPM interrupts.
 *
 * @param base TPM peripheral base address
 * @param mask The interrupts to enable. This is a logical OR of members of the
 *             enumeration ::tpm_interrupt_enable_t
 */
void TPM_EnableInterrupts(TPM_Type *base, uint32_t mask);

/*!
 * @brief Disables the selected TPM interrupts.
 *
 * @param base TPM peripheral base address
 * @param mask The interrupts to disable. This is a logical OR of members of the
 *             enumeration ::tpm_interrupt_enable_t
 */
void TPM_DisableInterrupts(TPM_Type *base, uint32_t mask);

/*!
 * @brief Gets the TPM status flags
 *
 * @param base TPM peripheral base address
 *
 * @return The status flags. This is the logical OR of members of the
 *         enumeration ::tpm_status_flags_t
 */
uint32_t TPM_GetStatusFlags(TPM_Type *base);

/*!
 * @brief Clears the TPM status flags
 *
 * @param base TPM peripheral base address
 * @param mask The status flags to clear. This is a logical OR of members of the
 *             enumeration ::tpm_status_flags_t
 */
void TPM_ClearStatusFlags(TPM_Type *base, uint32_t mask);

/*!
 * @brief Sets the timer period in units of ticks.
 *
 * Timers counts from 0 until it equals the count value set here. The count value is written to
 * the MOD register.
 *
 * @note
 * 1. This API allows the user to use the TPM module as a timer. Do not mix usage
 *    of this API with TPM's PWM setup API's.
 * 2. Call the utility macros provided in the fsl_common.h to convert usec or msec to ticks.
 *
 * @param base TPM peripheral base address
 * @param ticks A timer period in units of ticks, which should be equal or greater than 1.
 */
void TPM_SetTimerPeriod(TPM_Type *base, uint32_t ticks);

/*!
 * @brief Reads the current timer counting value.
 *
 * This function returns the real-time timer counting value in a range from 0 to a
 * timer period.
 *
 * @note Call the utility macros provided in the fsl_common.h to convert ticks to usec or msec.
 *
 * @param base TPM peripheral base address
 *
 * @return The current counter value in ticks
 */
uint32_t TPM_GetCurrentTimerCount(TPM_Type *base);

/*!
 * @brief Starts the TPM counter.
 *
 *
 * @param base        TPM peripheral base address
 * @param clockSource TPM clock source; once clock source is set the counter will start running
 */
void TPM_StartTimer(TPM_Type *base, tpm_clock_source_t clockSource);

/*!
 * @brief Stops the TPM counter.
 *
 * @param base TPM peripheral base address
 */
void TPM_StopTimer(TPM_Type *base);

#if defined(__cplusplus)
}
#endif

#endif /* _FSL_TPM_H_ */
