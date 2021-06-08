/**
 * @file stm32f1xx_hal_rcc.h
 * @brief Header file for mocking the stm32f1xx_hal_rcc sdk module.
 */

#ifndef __STM32F1xx_HAL_RCC_H
#define __STM32F1xx_HAL_RCC_H

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * INCLUDES
 ******************************************************************************/
#include "stm32f1xx_hal_def.h"

/*******************************************************************************
 * DEFINITIONS
 ******************************************************************************/

/*******************************************************************************
 * API
 ******************************************************************************/
void __HAL_RCC_GPIOA_CLK_ENABLE(void);
void __HAL_RCC_GPIOB_CLK_ENABLE(void);
void __HAL_RCC_GPIOC_CLK_ENABLE(void);
void __HAL_RCC_GPIOD_CLK_ENABLE(void);
void __HAL_RCC_GPIOE_CLK_ENABLE(void);

void __HAL_RCC_TIM3_CLK_ENABLE(void);
void __HAL_RCC_TIM4_CLK_ENABLE(void);

uint32_t HAL_RCC_GetPCLK1Freq(void);

#ifdef __cplusplus
}
#endif

#endif
