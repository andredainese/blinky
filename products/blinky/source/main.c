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
 * @file main.c
 * @brief Main operation file, where board, apps and OS are started.
 */

/*******************************************************************************
 *  INCLUDES
 ******************************************************************************/
#include "myBoard.h"
#include "cmsis_os.h"

#include "appButton.h"
#include "appLed.h"

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
int main(void)
{
  /* Start by initializing all that is required by the board.                 */
  myBoard_Init();

  /* Now start all the required applications.                                 */
  appLed_Init();
  appButton_Init();

  /* Finish by starting the scheduler.                                        */
  osKernelStart();

  /* The scheduler should never return, but...                                */
  while(1);
  return 0;
}

/*******************************************************************************
 *  PRIVATE FUNCTIONS / ROUTINES
 ******************************************************************************/
