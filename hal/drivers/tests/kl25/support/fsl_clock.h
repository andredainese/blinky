/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright (c) 2016 - 2017 , NXP
 * All rights reserved.
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
 * o Neither the name of copyright holder nor the names of its
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
 * @file fsl_clock.h
 * @brief Header file for mocking the fsl_clock sdk module.
 */

#ifndef _FSL_CLOCK_H_
#define _FSL_CLOCK_H_

#include "myDefs.h"
#include "fsl_common.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Clock gate name used for CLOCK_EnableClock/CLOCK_DisableClock. */
typedef enum _clock_ip_name
{
    kCLOCK_IpInvalid,
    kCLOCK_I2c0,
    kCLOCK_I2c1,
    kCLOCK_Uart0,
    kCLOCK_Uart1,
    kCLOCK_Uart2,
    kCLOCK_Usbfs0,
    kCLOCK_Cmp0,
    kCLOCK_Spi0,
    kCLOCK_Spi1,
    kCLOCK_Lptmr0,
    kCLOCK_Tsi0,
    kCLOCK_PortA,
    kCLOCK_PortB,
    kCLOCK_PortC,
    kCLOCK_PortD,
    kCLOCK_PortE,
    kCLOCK_Ftf0,
    kCLOCK_Dmamux0,
    kCLOCK_Pit0,
    kCLOCK_Tpm0,
    kCLOCK_Tpm1,
    kCLOCK_Tpm2,
    kCLOCK_Adc0,
    kCLOCK_Rtc0,
    kCLOCK_Dac0,
    kCLOCK_Dma0,
} clock_ip_name_t;
/*******************************************************************************
 * API
 ******************************************************************************/

/*!
 * @brief Enable the clock for specific IP.
 * @param name  Which clock to enable, see \ref clock_ip_name_t.
 */
void CLOCK_EnableClock(clock_ip_name_t name);

/*! @brief Set TPM clock source. */
void CLOCK_SetTpmClock(uint32_t src);

/*!
 * @brief Get the OSC0 external reference clock frequency (OSC0ERCLK).
 *
 * @return Clock frequency in Hz.
 */
uint32_t CLOCK_GetOsc0ErClkFreq(void);

#endif /* _FSL_CLOCK_H_ */
