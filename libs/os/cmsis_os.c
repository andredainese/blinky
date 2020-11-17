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
 * @file cmsis_os.c
 * @brief Interface source file for CMSIS-OS library.
 *
 * This module provides the routines that external parties can call in order
 *  to use the CMSIS-OS logic.
 * This is a temporary source file. As the proper libraries are added to the
 *  repository, the correct files will replace the temporary ones.
 */

/*******************************************************************************
 *  INCLUDES
 ******************************************************************************/
#include "cmsis_os.h"

/*******************************************************************************
 *  PRIVATE DEFINITIONS
 ******************************************************************************/

/*******************************************************************************
 *  PRIVATE PROTOTYPES
 ******************************************************************************/

/*******************************************************************************
 *  PRIVATE VARIABLES
 ******************************************************************************/

/*******************************************************************************
 *  PUBLIC FUNCTIONS / ROUTINES
 ******************************************************************************/
/**
 * @brief Start the RTOS Kernel.
 * @return Status code that indicates the execution status of the function.
 */
osStatus osKernelStart(void)
{
  /* Simply keep itself running an infinite loop.                             */
  while(1);
  return osOK;
}

/*******************************************************************************
 *  PRIVATE FUNCTIONS / ROUTINES
 ******************************************************************************/
