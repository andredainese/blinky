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
 * @file appButton.h
 * @brief Interface header file for the Button application.
 *
 * This module provides the routines that external parties can call in order
 *  to interact with the Button application.
 */
 
#ifndef APP_BUTTON_H
#define APP_BUTTON_H

/*******************************************************************************
 *  INCLUDES
 ******************************************************************************/
#include "myDefs.h"

/*******************************************************************************
 *  PUBLIC PROTOTYPES
 ******************************************************************************/
/**
 * @brief Initialization routine for the Button Application
 *
 * This routine should be called by your initializer logic so that the Button
 *  application can start.
 * It should be called only once. After it is called, the module will handle
 *  its initialization by itself.
 * @return Success / Failure
 */
myRet_t appButton_Init(void);

#endif
