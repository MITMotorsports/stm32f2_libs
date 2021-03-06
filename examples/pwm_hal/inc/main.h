#ifndef __MAIN_H
#define __MAIN_H

#include <stdbool.h>
#include "stdio.h"

#include "stm32f2xx_hal.h"

#include "gpio.h"

#ifdef __GNUC__

// With GCC Compilers, small printf
// (option LD Linker->Libraries->Small printf set to 'Yes') calls __io_putchar()

  # define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else // ifdef __GNUC__
  # define PUTCHAR_PROTOTYPE int fputc(int ch, FILE * f)
#endif /* __GNUC__ */

// - TIMERS FOR PWM -------------------------------------------
/* User can use this section to tailor TIMx instance used and associated
   resources */
/* Definition for TIMx clock resources */
#define TIMx                           TIM3
#define TIMx_CLK_ENABLE()              __HAL_RCC_TIM3_CLK_ENABLE()

/* Definition for TIMx Channel Pins */
#define TIMx_CHANNEL_GPIO_PORT()       __HAL_RCC_GPIOB_CLK_ENABLE();
#define TIMx_GPIO_PORT_CHANNEL1        GPIOB
#define TIMx_GPIO_PORT_CHANNEL2        GPIOB
#define TIMx_GPIO_PORT_CHANNEL3        GPIOB
#define TIMx_GPIO_PORT_CHANNEL4        GPIOB
#define TIMx_GPIO_PIN_CHANNEL1         GPIO_PIN_4
#define TIMx_GPIO_PIN_CHANNEL2         GPIO_PIN_5
#define TIMx_GPIO_PIN_CHANNEL3         GPIO_PIN_0
#define TIMx_GPIO_PIN_CHANNEL4         GPIO_PIN_1
#define TIMx_GPIO_AF_CHANNEL1          GPIO_AF2_TIM3
#define TIMx_GPIO_AF_CHANNEL2          GPIO_AF2_TIM3
#define TIMx_GPIO_AF_CHANNEL3          GPIO_AF2_TIM3
#define TIMx_GPIO_AF_CHANNEL4          GPIO_AF2_TIM3

// USART -------------------------------------------------------
// #define USARTx_INSTANCE               USART1
// #define USARTx_CLK_ENABLE() __HAL_RCC_USART1_CLK_ENABLE()
// #define USARTx_GPIO_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE()

// #define USARTx_FORCE_RESET() __HAL_RCC_USART1_FORCE_RESET()
// #define USARTx_RELEASE_RESET() __HAL_RCC_USART1_RELEASE_RESET()

// #define USARTx_TX_PIN                 GPIO_PIN_6
// #define USARTx_TX_GPIO_PORT           GPIOB
// #define USARTx_TX_AF                  GPIO_AF7_USART1
// #define USARTx_RX_PIN                 GPIO_PIN_7
// #define USARTx_RX_GPIO_PORT           GPIOB
// #define USARTx_RX_AF                  GPIO_AF7_USART1

// #define USARTx_RX_IRQn                USART1_IRQn
//#define USARTx_RX_IRQHandler          USART1_IRQHandler

// CAN ------------------------------------------------------------
// #define CANx                            CAN1
// #define CANx_CLK_ENABLE() __HAL_RCC_CAN1_CLK_ENABLE()
// #define CANx_GPIO_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE()

// #define CANx_FORCE_RESET() __HAL_RCC_CAN1_FORCE_RESET()
// #define CANx_RELEASE_RESET() __HAL_RCC_CAN1_RELEASE_RESET()

// #define CANx_TX_PIN                    GPIO_PIN_9
// #define CANx_TX_GPIO_PORT              GPIOB
// #define CANx_TX_AF                     GPIO_AF9_CAN1
// #define CANx_RX_PIN                    GPIO_PIN_8
// #define CANx_RX_GPIO_PORT              GPIOB
// #define CANx_RX_AF                     GPIO_AF9_CAN1

// #define CANx_RX_IRQn                   CAN1_RX0_IRQn
// #define CANx_RX_IRQHandler             CAN1_RX0_IRQHandler

void USART_Init(uint32_t baudrate);
static void SystemClock_Config(void);

// USART_HandleTypeDef USARTHandle;
//CAN_HandleTypeDef   CanHandle;

#endif // ifndef __MAIN_H
