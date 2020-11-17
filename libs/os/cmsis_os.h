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
 * @file cmsis_os.h
 * @brief Interface header file for CMSIS-OS library.
 *
 * This module provides the routines that external parties can call in order
 *  to use the CMSIS-OS logic.
 * This is a temporary header file. As the proper libraries are added to the
 *  repository, the correct files will replace the temporary ones.
 */

#ifndef CMSIS_OS_H
#define CMSIS_OS_H

/*******************************************************************************
 *  INCLUDES
 ******************************************************************************/
#include "myDefs.h"

/*******************************************************************************
 *  PUBLIC DEFINITIONS
 ******************************************************************************/
/**
 * @brief Status code values returned by CMSIS-RTOS functions.
 */
typedef enum
{
  osOK,
} osStatus;

/*******************************************************************************
 *  PUBLIC PROTOTYPES
 ******************************************************************************/
/**
 * @brief Start the RTOS Kernel.
 * @return Status code that indicates the execution status of the function.
 */
osStatus osKernelStart(void);

#endif
