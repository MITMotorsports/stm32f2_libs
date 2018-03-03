
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f2xx_hal.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* User can use this section to tailor CANx instance used and associated 
   resources */
/* Definition for CANx clock resources */
#define CANx                            CAN1
#define CANx_CLK_ENABLE()               __HAL_RCC_CAN1_CLK_ENABLE()
#define CANx_GPIO_CLK_ENABLE()          __HAL_RCC_GPIOB_CLK_ENABLE()
     
#define CANx_FORCE_RESET()              __HAL_RCC_CAN1_FORCE_RESET()
#define CANx_RELEASE_RESET()            __HAL_RCC_CAN1_RELEASE_RESET()

/* Definition for USARTx Pins */
#define CANx_TX_PIN                    GPIO_PIN_9
#define CANx_TX_GPIO_PORT              GPIOB  
#define CANx_TX_AF                     GPIO_AF9_CAN1
#define CANx_RX_PIN                    GPIO_PIN_8
#define CANx_RX_GPIO_PORT              GPIOB
#define CANx_RX_AF                     GPIO_AF9_CAN1

/* Definition for USARTx's NVIC */
#define CANx_RX_IRQn                   CAN1_RX0_IRQn
#define CANx_RX_IRQHandler             CAN1_RX0_IRQHandler

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
