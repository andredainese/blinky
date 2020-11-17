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
 * @file myBoard.c
 * @brief Header file for board specific operations, KL25Z microcontrollers.
 */

/*******************************************************************************
 *  INCLUDES
 ******************************************************************************/
#include "myBoard.h"
#include "clock_config.h"

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
 * @brief Initialization routine for the board.
 */
void myBoard_Init(void)
{
  /* Simply initialize system clocks.                                         */
  BOARD_InitBootClocks();
}

/*******************************************************************************
 *  PRIVATE FUNCTIONS / ROUTINES
 ******************************************************************************/
