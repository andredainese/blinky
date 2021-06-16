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
 * @file myTimer_TPM.h
 * @brief Header file for KL25 timer driver submodule for custom TPM usage.
 *
 * This header provides helper routines to perform operations over the TPM
 *  peripherals that are not supported by the regular FSL library.
 */

#ifndef MY_TIMER_TPM_H
#define MY_TIMER_TPM_H

/*******************************************************************************
 *  INCLUDES
 ******************************************************************************/
#include "myDefs.h"
#include "fsl_tpm.h"

/*******************************************************************************
 *  PUBLIC DEFINITIONS
 ******************************************************************************/

/*******************************************************************************
 *  PUBLIC FUNCTIONS / ROUTINES
 ******************************************************************************/
/**
 * @brief Clear the current counter value for a TPM, putting it back to zero.
 * @param base Base address of the TPM peripheral.
 */
void TPM_ClearCounter(TPM_Type * base);

#endif
