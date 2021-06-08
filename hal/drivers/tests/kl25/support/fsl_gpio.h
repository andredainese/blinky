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
 * @file fsl_gpio.h
 * @brief Header file for mocking the fsl_gpio sdk module.
 */

#ifndef _FSL_GPIO_H_
#define _FSL_GPIO_H_

#include "myDefs.h"
#include "fsl_common.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/** GPIO - Register Layout Typedef                                            */
typedef void * GPIO_Type;

/** GPIO Peripherals' fake addresses                                          */
#define GPIOA                                           ((GPIO_Type) 0x0000000A)
#define GPIOB                                           ((GPIO_Type) 0x0000000B)
#define GPIOC                                           ((GPIO_Type) 0x0000000C)
#define GPIOD                                           ((GPIO_Type) 0x0000000D)
#define GPIOE                                           ((GPIO_Type) 0x0000000E)

/** Array initializer of GPIO peripheral base pointers                        */
#define GPIO_BASE_PTRS                     { GPIOA, GPIOB, GPIOC, GPIOD, GPIOE }

/** @brief GPIO direction definition */
typedef enum _gpio_pin_direction
{
    kGPIO_DigitalInput = 0U,  /*!< Set current pin as digital input*/
    kGPIO_DigitalOutput = 1U, /*!< Set current pin as digital output*/
} gpio_pin_direction_t;

/**
 * @brief The GPIO pin configuration structure.
 *
 * Each pin can only be configured as either an output pin or an input pin at a time.
 * If configured as an input pin, leave the outputConfig unused.
 * Note that in some use cases, the corresponding port property should be configured in advance
 *        with the PORT_SetPinConfig().
 */
typedef struct _gpio_pin_config
{
    gpio_pin_direction_t pinDirection; /*!< GPIO direction, input or output */
    /* Output configurations; ignore if configured as an input pin */
    uint8_t outputLogic; /*!< Set a default output logic, which has no use in input */
} gpio_pin_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/**
 * @brief Initializes a GPIO pin used by the board.
 * @param base   GPIO peripheral base pointer (GPIOA, GPIOB, GPIOC, and so on.)
 * @param pin    GPIO port pin number
 * @param config GPIO pin configuration pointer
 */
void GPIO_PinInit(GPIO_Type *base, uint32_t pin, const gpio_pin_config_t *config);

/**
 * @brief Sets the output level of the multiple GPIO pins to the logic 1 or 0.
 * @param base    GPIO peripheral base pointer (GPIOA, GPIOB, GPIOC, and so on.)
 * @param pin     GPIO pin number
 * @param output  GPIO pin output logic level.
 *        - 0: corresponding pin output low-logic level.
 *        - 1: corresponding pin output high-logic level.
 */
void GPIO_WritePinOutput(GPIO_Type *base, uint32_t pin, uint8_t output);

/**
 * @brief Sets the output level of the multiple GPIO pins to the logic 1.
 * @param base GPIO peripheral base pointer (GPIOA, GPIOB, GPIOC, and so on.)
 * @param mask GPIO pin number macro
 */
void GPIO_SetPinsOutput(GPIO_Type *base, uint32_t mask);

/**
 * @brief Sets the output level of the multiple GPIO pins to the logic 0.
 * @param base GPIO peripheral base pointer (GPIOA, GPIOB, GPIOC, and so on.)
 * @param mask GPIO pin number macro
 */
void GPIO_ClearPinsOutput(GPIO_Type *base, uint32_t mask);

/**
 * @brief Reverses the current output logic of the multiple GPIO pins.
 * @param base GPIO peripheral base pointer (GPIOA, GPIOB, GPIOC, and so on.)
 * @param mask GPIO pin number macro
 */
void GPIO_TogglePinsOutput(GPIO_Type *base, uint32_t mask);

/**
 * @brief Reads the current input value of the GPIO port.
 * @param base GPIO peripheral base pointer (GPIOA, GPIOB, GPIOC, and so on.)
 * @param pin     GPIO pin number
 * @retval GPIO port input value
 *        - 0: corresponding pin input low-logic level.
 *        - 1: corresponding pin input high-logic level.
 */
uint32_t GPIO_ReadPinInput(GPIO_Type *base, uint32_t pin);

/**
 * @brief Reads the GPIO port interrupt status flag.
 * If a pin is configured to generate the DMA request, the corresponding flag
 * is cleared automatically at the completion of the requested DMA transfer.
 * Otherwise, the flag remains set until a logic one is written to that flag.
 * If configured for a level sensitive interrupt that remains asserted, the flag
 * is set again immediately.
 *
 * @param base GPIO peripheral base pointer (GPIOA, GPIOB, GPIOC, and so on.)
 * @retval The current GPIO port interrupt status flag, for example, 0x00010001 means the
 *         pin 0 and 17 have the interrupt.
 */
uint32_t GPIO_GetPinsInterruptFlags(GPIO_Type *base);

/**
 * @brief Clears multiple GPIO pin interrupt status flags.
 * @param base GPIO peripheral base pointer (GPIOA, GPIOB, GPIOC, and so on.)
 * @param mask GPIO pin number macro
 */
void GPIO_ClearPinsInterruptFlags(GPIO_Type *base, uint32_t mask);

#if defined(__cplusplus)
}
#endif

#endif /* _FSL_GPIO_H_*/
