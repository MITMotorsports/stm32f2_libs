/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f2xx_ll_bus.h"
#include "stm32f2xx_ll_rcc.h"
#include "stm32f2xx_ll_system.h"
#include "stm32f2xx_ll_utils.h"
#include "stm32f2xx_ll_gpio.h"
#include "stm32f2xx_ll_exti.h"
#include "stm32f2xx_ll_usart.h"
#include "stm32f2xx_ll_pwr.h"

/* Exported constants --------------------------------------------------------*/

/* Define used to enable Virtual Com Port use :
     USE_VCP_CONNECTION == 0
       USART1 instance is used. (TX on PA.09, RX on PA.10)
       (requires wiring USART1 TX/Rx Pins to PC connection (could be achieved thanks to a USB to UART adapter)
     USE_VCP_CONNECTION == 1
       USART3 instance is used. (TX on PD.08, RX on PD.09)
       (please ensure that USART communication between the target MCU and ST-LINK MCU is properly enabled
       on HW board in order to support Virtual Com Port)
*/
#define USE_VCP_CONNECTION       1

/* Private definitions covering GPIO clock and USART pins 
   depending on selected USART instance. */
// #if (USE_VCP_CONNECTION == 0)

// /* USART1 instance is used. (TX on PA.09, RX on PA.10)
//    (requires wiring USART1 TX/Rx Pins to USB to UART adapter) */
// #define USARTx_INSTANCE               USART1
// #define USARTx_CLK_ENABLE()           LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1)
// #define USARTx_IRQn                   USART1_IRQn
// #define USARTx_IRQHandler             USART1_IRQHandler

// #define USARTx_GPIO_CLK_ENABLE()      LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA)   /* Enable the peripheral clock of GPIOA */
// #define USARTx_TX_PIN                 LL_GPIO_PIN_9
// #define USARTx_TX_GPIO_PORT           GPIOA
// #define USARTx_SET_TX_GPIO_AF()       LL_GPIO_SetAFPin_8_15(GPIOA, LL_GPIO_PIN_9, LL_GPIO_AF_7)
// #define USARTx_RX_PIN                 LL_GPIO_PIN_10
// #define USARTx_RX_GPIO_PORT           GPIOA
// #define USARTx_SET_RX_GPIO_AF()       LL_GPIO_SetAFPin_8_15(GPIOA, LL_GPIO_PIN_10, LL_GPIO_AF_7)
// #define APB_Div 2

// #else

/* USART3 instance is used. (TX on PD.08, RX on PD.09)
   (please ensure that USART communication between the target MCU and ST-LINK MCU is properly enabled
    on HW board in order to support Virtual Com Port) */
#define USARTx_INSTANCE               USART1
#define USARTx_CLK_ENABLE()           LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1)
#define USARTx_IRQn                   USART1_IRQn
#define USARTx_IRQHandler             USART1_IRQHandler

#define USARTx_GPIO_CLK_ENABLE()      LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB)   /* Enable the peripheral clock of GPIOB */
#define USARTx_TX_PIN                 LL_GPIO_PIN_6
#define USARTx_TX_GPIO_PORT           GPIOB
#define USARTx_SET_TX_GPIO_AF()       LL_GPIO_SetAFPin_0_7(GPIOB, LL_GPIO_PIN_6, LL_GPIO_AF_7)
#define USARTx_RX_PIN                 LL_GPIO_PIN_7
#define USARTx_RX_GPIO_PORT           GPIOB
#define USARTx_SET_RX_GPIO_AF()       LL_GPIO_SetAFPin_0_7(GPIOB, LL_GPIO_PIN_7, LL_GPIO_AF_7)
#define APB_Div 2
// #endif /* (USE_VCP_CONNECTION == 0) */

#define CLOSE_CONTACTOR_PIN                           LL_GPIO_PIN_10
#define CLOSE_CONTACTOR_GPIO_PORT                     GPIOC
#define CLOSE_CONTACTOR_GPIO_CLK_ENABLE()             LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC)

#define MCU_ON_PIN                                    LL_GPIO_PIN_11
#define MCU_ON_GPIO_PORT                              GPIOC
#define MCU_ON_GPIO_CLK_ENABLE()                      LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC)

/**
  * @brief Toggle periods for various blinking modes
  */

#define LED_BLINK_FAST  200
#define LED_BLINK_SLOW  500
#define LED_BLINK_ERROR 1000


#define USER_BUTTON_IRQHANDLER                  EXTI15_10_IRQHandler

/* Exported functions ------------------------------------------------------- */
/* IRQ Handler treatment functions */
void USART_CharReception_Callback(void);
void Error_Callback(void);

#endif /* __MAIN_H */
