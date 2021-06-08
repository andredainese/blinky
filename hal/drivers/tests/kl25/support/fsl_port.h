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
 * @file fsl_port.h
 * @brief Header file for mocking the fsl_port sdk module.
 */

#ifndef _FSL_PORT_H_
#define _FSL_PORT_H_

#include "myDefs.h"
#include "fsl_common.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/** PORT - Register Layout Typedef                                            */
typedef void * PORT_Type;

/** PORT Peripherals' fake addresses                                          */
#define PORTA                                           ((PORT_Type) 0x0000001A)
#define PORTB                                           ((PORT_Type) 0x0000001B)
#define PORTC                                           ((PORT_Type) 0x0000001C)
#define PORTD                                           ((PORT_Type) 0x0000001D)
#define PORTE                                           ((PORT_Type) 0x0000001E)

/** Array initializer of PORT peripheral base pointers                        */
#define PORT_BASE_PTRS                     { PORTA, PORTB, PORTC, PORTD, PORTE }

/** @brief Internal resistor pull feature selection */
enum _port_pull
{
    kPORT_PullDisable = 0U, /**< Internal pull-up/down resistor is disabled. */
    kPORT_PullDown = 2U,    /**< Internal pull-down resistor is enabled. */
    kPORT_PullUp = 3U,      /**< Internal pull-up resistor is enabled. */
};

/** @brief Slew rate selection */
enum _port_slew_rate
{
    kPORT_FastSlewRate = 0U, /**< Fast slew rate is configured. */
    kPORT_SlowSlewRate = 1U, /**< Slow slew rate is configured. */
};

/** @brief Open Drain feature enable/disable */
enum _port_open_drain_enable
{
    kPORT_OpenDrainDisable = 0U, /**< Open drain output is disabled. */
    kPORT_OpenDrainEnable = 1U,  /**< Open drain output is enabled. */
};

/** @brief Passive filter feature enable/disable */
enum _port_passive_filter_enable
{
    kPORT_PassiveFilterDisable = 0U, /**< Passive input filter is disabled. */
    kPORT_PassiveFilterEnable = 1U,  /**< Passive input filter is enabled. */
};

/** @brief Configures the drive strength. */
enum _port_drive_strength
{
    kPORT_LowDriveStrength = 0U,  /**< Low-drive strength is configured. */
    kPORT_HighDriveStrength = 1U, /**< High-drive strength is configured. */
};

/** @brief Unlock/lock the pin control register field[15:0] */
enum _port_lock_register
{
    kPORT_UnlockRegister = 0U, /**< Pin Control Register fields [15:0] are not locked. */
    kPORT_LockRegister = 1U,   /**< Pin Control Register fields [15:0] are locked. */
};

/** @brief Pin mux selection */
typedef enum _port_mux
{
    kPORT_PinDisabledOrAnalog = 0U, /**< Corresponding pin is disabled, but is used as an analog pin. */
    kPORT_MuxAsGpio = 1U,           /**< Corresponding pin is configured as GPIO. */
    kPORT_MuxAlt2 = 2U,             /**< Chip-specific */
    kPORT_MuxAlt3 = 3U,             /**< Chip-specific */
    kPORT_MuxAlt4 = 4U,             /**< Chip-specific */
    kPORT_MuxAlt5 = 5U,             /**< Chip-specific */
    kPORT_MuxAlt6 = 6U,             /**< Chip-specific */
    kPORT_MuxAlt7 = 7U,             /**< Chip-specific */
    kPORT_MuxAlt8 = 8U,             /**< Chip-specific */
    kPORT_MuxAlt9 = 9U,             /**< Chip-specific */
    kPORT_MuxAlt10 = 10U,           /**< Chip-specific */
    kPORT_MuxAlt11 = 11U,           /**< Chip-specific */
    kPORT_MuxAlt12 = 12U,           /**< Chip-specific */
    kPORT_MuxAlt13 = 13U,           /**< Chip-specific */
    kPORT_MuxAlt14 = 14U,           /**< Chip-specific */
    kPORT_MuxAlt15 = 15U,           /**< Chip-specific */
} port_mux_t;

/** @brief Digital filter clock source selection */
typedef enum _port_digital_filter_clock_source
{
    kPORT_BusClock = 0U, /**< Digital filters are clocked by the bus clock. */
    kPORT_LpoClock = 1U, /**< Digital filters are clocked by the 1 kHz LPO clock. */
} port_digital_filter_clock_source_t;

/** @brief PORT digital filter feature configuration definition */
typedef struct _port_digital_filter_config
{
    uint32_t digitalFilterWidth;                    /**< Set digital filter width */
    port_digital_filter_clock_source_t clockSource; /**< Set digital filter clockSource */
} port_digital_filter_config_t;


/** @brief PORT pin configuration structure */
typedef struct _port_pin_config
{
    uint16_t pullSelect : 2; /**< No-pull/pull-down/pull-up select */
    uint16_t slewRate : 1; /**< Fast/slow slew rate Configure */
    uint16_t : 1;
    uint16_t passiveFilterEnable : 1; /**< Passive filter enable/disable */
    uint16_t openDrainEnable : 1; /**< Open drain enable/disable */
    uint16_t driveStrength : 1; /**< Fast/slow drive strength configure */
    uint16_t : 1;
    uint16_t mux : 3; /**< Pin mux Configure */
    uint16_t : 4;
} port_pin_config_t;

/*******************************************************************************
* API
******************************************************************************/
/**
 * @brief Sets the port PCR register.
 * @param base   PORT peripheral base pointer.
 * @param pin    PORT pin number.
 * @param config PORT PCR register configuration structure.
 */
void PORT_SetPinConfig(PORT_Type *base, uint32_t pin, const port_pin_config_t *config);

#endif /* _FSL_PORT_H_ */
