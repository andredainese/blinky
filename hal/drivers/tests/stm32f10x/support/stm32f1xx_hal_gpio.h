/**
 * @file stm32f1xx_hal_gpio.h
 * @brief Header file for mocking the stm32f1xx_hal_gpio sdk module.
 */

#ifndef STM32F1xx_HAL_GPIO_H
#define STM32F1xx_HAL_GPIO_H

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
/** GPIO - Register Layout Typedef                                            */
typedef void * GPIO_TypeDef;

/** GPIO Peripherals' fake addresses                                          */
#define GPIOA                                        ((GPIO_TypeDef) 0x0000000A)
#define GPIOB                                        ((GPIO_TypeDef) 0x0000000B)
#define GPIOC                                        ((GPIO_TypeDef) 0x0000000C)
#define GPIOD                                        ((GPIO_TypeDef) 0x0000000D)
#define GPIOE                                        ((GPIO_TypeDef) 0x0000000E)

typedef struct
{
  uint32_t Pin;       /*!< Specifies the GPIO pins to be configured.
                           This parameter can be any value of @ref GPIO_pins_define */

  uint32_t Mode;      /*!< Specifies the operating mode for the selected pins.
                           This parameter can be a value of @ref GPIO_mode_define */

  uint32_t Pull;      /*!< Specifies the Pull-up or Pull-Down activation for the selected pins.
                           This parameter can be a value of @ref GPIO_pull_define */

  uint32_t Speed;     /*!< Specifies the speed for the selected pins.
                           This parameter can be a value of @ref GPIO_speed_define */
} GPIO_InitTypeDef;

typedef enum
{
  GPIO_PIN_RESET = 0u,
  GPIO_PIN_SET
} GPIO_PinState;

#define GPIO_PIN_0                                            ((uint16_t)0x0001)  /* Pin 0 selected    */
#define GPIO_PIN_1                                            ((uint16_t)0x0002)  /* Pin 1 selected    */
#define GPIO_PIN_2                                            ((uint16_t)0x0004)  /* Pin 2 selected    */
#define GPIO_PIN_3                                            ((uint16_t)0x0008)  /* Pin 3 selected    */
#define GPIO_PIN_4                                            ((uint16_t)0x0010)  /* Pin 4 selected    */
#define GPIO_PIN_5                                            ((uint16_t)0x0020)  /* Pin 5 selected    */
#define GPIO_PIN_6                                            ((uint16_t)0x0040)  /* Pin 6 selected    */
#define GPIO_PIN_7                                            ((uint16_t)0x0080)  /* Pin 7 selected    */
#define GPIO_PIN_8                                            ((uint16_t)0x0100)  /* Pin 8 selected    */
#define GPIO_PIN_9                                            ((uint16_t)0x0200)  /* Pin 9 selected    */
#define GPIO_PIN_10                                           ((uint16_t)0x0400)  /* Pin 10 selected   */
#define GPIO_PIN_11                                           ((uint16_t)0x0800)  /* Pin 11 selected   */
#define GPIO_PIN_12                                           ((uint16_t)0x1000)  /* Pin 12 selected   */
#define GPIO_PIN_13                                           ((uint16_t)0x2000)  /* Pin 13 selected   */
#define GPIO_PIN_14                                           ((uint16_t)0x4000)  /* Pin 14 selected   */
#define GPIO_PIN_15                                           ((uint16_t)0x8000)  /* Pin 15 selected   */
#define GPIO_PIN_All                                          ((uint16_t)0xFFFF)  /* All pins selected */

#define GPIO_PIN_MASK                                                0x0000FFFFu  /* PIN mask for assert test */

#define  GPIO_MODE_INPUT                                             0x00000000u  /*!< Input Floating Mode                   */
#define  GPIO_MODE_OUTPUT_PP                                         0x00000001u  /*!< Output Push Pull Mode                 */
#define  GPIO_MODE_OUTPUT_OD                                         0x00000011u  /*!< Output Open Drain Mode                */
#define  GPIO_MODE_AF_PP                                             0x00000002u  /*!< Alternate Function Push Pull Mode     */
#define  GPIO_MODE_AF_OD                                             0x00000012u  /*!< Alternate Function Open Drain Mode    */
#define  GPIO_MODE_AF_INPUT                                      GPIO_MODE_INPUT  /*!< Alternate Function Input Mode         */

#define  GPIO_MODE_ANALOG                                            0x00000003u  /*!< Analog Mode  */

#define  GPIO_MODE_IT_RISING                                         0x10110000u  /*!< External Interrupt Mode with Rising edge trigger detection          */
#define  GPIO_MODE_IT_FALLING                                        0x10210000u  /*!< External Interrupt Mode with Falling edge trigger detection         */
#define  GPIO_MODE_IT_RISING_FALLING                                 0x10310000u  /*!< External Interrupt Mode with Rising/Falling edge trigger detection  */

#define  GPIO_MODE_EVT_RISING                                        0x10120000u  /*!< External Event Mode with Rising edge trigger detection               */
#define  GPIO_MODE_EVT_FALLING                                       0x10220000u  /*!< External Event Mode with Falling edge trigger detection              */
#define  GPIO_MODE_EVT_RISING_FALLING                                0x10320000u  /*!< External Event Mode with Rising/Falling edge trigger detection       */

#define  GPIO_SPEED_FREQ_LOW                                  ((uint16_t)0x0001)  /*!< Low speed */
#define  GPIO_SPEED_FREQ_MEDIUM                               ((uint16_t)0x0002)  /*!< Medium speed */
#define  GPIO_SPEED_FREQ_HIGH                                 ((uint16_t)0x0003)  /*!< High speed */

#define  GPIO_NOPULL                                                 0x00000000u  /*!< No Pull-up or Pull-down activation  */
#define  GPIO_PULLUP                                                 0x00000001u  /*!< Pull-up activation                  */
#define  GPIO_PULLDOWN                                               0x00000002u  /*!< Pull-down activation                */

/*******************************************************************************
 * API
 ******************************************************************************/
void  HAL_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init);
void  HAL_GPIO_DeInit(GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pin);
GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);
void HAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
HAL_StatusTypeDef HAL_GPIO_LockPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void HAL_GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

#ifdef __cplusplus
}
#endif

#endif
