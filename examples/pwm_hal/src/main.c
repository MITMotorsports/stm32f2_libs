#include "main.h"

#define  PERIOD_VALUE       (uint32_t)(366 - 1)  /* Period Value  */
#define  PULSE1_VALUE       (uint32_t)(PERIOD_VALUE/2)        /* Capture Compare 1 Value  */
#define  PULSE2_VALUE       (uint32_t)(PERIOD_VALUE*50/100) /* Capture Compare 2 Value  */
#define  PULSE3_VALUE       (uint32_t)(PERIOD_VALUE/4)        /* Capture Compare 3 Value  */
#define  PULSE4_VALUE       (uint32_t)(PERIOD_VALUE*12.5/100) /* Capture Compare 4 Value  */

TIM_HandleTypeDef TimHandle; // Timer handler typdef
TIM_OC_InitTypeDef sConfig; // timer output compare configuration structure decl
uint32_t uhPrescalerValue = 0; // counter prescaler value

int main(void) {
  HAL_Init();

  SystemClock_Config();

  GPIO_BEGIN_INIT();

  //USART_Init(115200);

  // Setup an LED for debugging
  DGPIO_INIT_OUT(        LED, GPIO_PIN_SET);

  // Compute the prescaler value to have TIM3 counter clock equal to 10000000 Hz
  uhPrescalerValue = (uint32_t)(SystemCoreClock / 2 / 10000000) - 1;

  TIM_Init();

  while (1) {
    static uint32_t i = 0;
    // static uint32_t lastt = 0;

    // if (HAL_GetTick() - lastt > 1000) {
    //   HAL_GPIO_TogglePin(GPIO(LED));
    //   printf("[ALIVE]\r\n");

    //   lastt = HAL_GetTick();
    // }
   
    // For 50% duty cycle, (370*50 - 140) / 100 
    static uint32_t desired_val = (370*50 - 140) / 100;
    // If you would like to vary the duty cycle, you will need to find a mapping to the COMPARE bit
    __HAL_TIM_SET_COMPARE(&TimHandle, TIM_CHANNEL_2, desired_val);

    //HAL_GPIO_TogglePin(GPIO(LED));
    HAL_Delay(10);
  }
}

void Error_Handler(const char *s) {
  while (1) {
    // printf("FORCED HANG IN Error_Handler\r\n");
    // printf(           "Error Message: %s\r\n", s);
    HAL_Delay(1000);
  }
}

void TIM_Init() {
  /*##-1- Configure the TIM peripheral #######################################*/
  /* -----------------------------------------------------------------------
  TIM3 Configuration: generate 4 PWM signals with 4 different duty cycles.

    In this example TIM3 input clock (TIM3CLK) is set to APB1 clock x 2,
    since APB1 prescaler is equal to 2.
      TIM3CLK = APB1CLK*2
      APB1CLK = HCLK/4
      => TIM3CLK = HCLK/2 = SystemCoreClock/2

    To get TIM3 counter clock at 10 MHz, the prescaler is computed as follows:
       Prescaler = (TIM3CLK / TIM3 counter clock) - 1
       Prescaler = ((SystemCoreClock / 2) /10 MHz) - 1

    To get TIM3 output clock at 15 KHz, the period (ARR)) is computed as follows:
       ARR = (TIM3 counter clock / TIM3 output clock) - 1
           = 665

    TIM3 Channel1 duty cycle = (TIM3_CCR1/ TIM3_ARR + 1)* 100 = 50%
    TIM3 Channel2 duty cycle = (TIM3_CCR2/ TIM3_ARR + 1)* 100 = 37.5%
    TIM3 Channel3 duty cycle = (TIM3_CCR3/ TIM3_ARR + 1)* 100 = 25%
    TIM3 Channel4 duty cycle = (TIM3_CCR4/ TIM3_ARR + 1)* 100 = 12.5%

    Note:
     SystemCoreClock variable holds HCLK frequency and is defined in system_stm32f2xx.c file.
     Each time the core clock (HCLK) changes, user had to update SystemCoreClock
     variable value. Otherwise, any configuration based on this variable will be incorrect.
     This variable is updated in three ways:
      1) by calling CMSIS function SystemCoreClockUpdate()
      2) by calling HAL API function HAL_RCC_GetSysClockFreq()
      3) each time HAL_RCC_ClockConfig() is called to configure the system clock frequency
  ----------------------------------------------------------------------- */

  /* Initialize TIMx peripheral as follows:
       + Prescaler = (SystemCoreClock / 2 / 10000000) - 1
       + Period = (666 - 1)
       + ClockDivision = 0
       + Counter direction = Up
  */

  /* Initialize TIMx peripheral as follows:
       + Prescaler = (SystemCoreClock / 2 / 10000000) - 1
       + Period = (666 - 1)
       + ClockDivision = 0
       + Counter direction = Up
  */
  TimHandle.Instance               = TIMx;
  TimHandle.Init.Prescaler         = uhPrescalerValue;
  TimHandle.Init.Period            = PERIOD_VALUE;
  TimHandle.Init.ClockDivision     = 0;
  TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;
  TimHandle.Init.RepetitionCounter = 0;
  TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&TimHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler("");
  }

  /*##-2- Configure the PWM channels #########################################*/
  /* Common configuration for all channels */
  sConfig.OCMode       = TIM_OCMODE_PWM1;
  sConfig.OCPolarity   = TIM_OCPOLARITY_HIGH;
  sConfig.OCFastMode   = TIM_OCFAST_DISABLE;
  sConfig.OCNPolarity  = TIM_OCNPOLARITY_HIGH;
  sConfig.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  sConfig.OCIdleState  = TIM_OCIDLESTATE_RESET;

  /* Set the pulse value for channel 1 */
  sConfig.Pulse = PULSE1_VALUE;
  if (HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig, TIM_CHANNEL_1) != HAL_OK)
  {
    /* Configuration Error */
    Error_Handler("");
  }

  /* Set the pulse value for channel 2 */
  sConfig.Pulse = PULSE2_VALUE;
  if (HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig, TIM_CHANNEL_2) != HAL_OK)
  {
    /* Configuration Error */
    Error_Handler("");
  }

  /* Set the pulse value for channel 3 */
  sConfig.Pulse = PULSE3_VALUE;
  if (HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig, TIM_CHANNEL_3) != HAL_OK)
  {
    /* Configuration Error */
    Error_Handler("");
  }

  /* Set the pulse value for channel 4 */
  sConfig.Pulse = PULSE4_VALUE;
  if (HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig, TIM_CHANNEL_4) != HAL_OK)
  {
    /* Configuration Error */
    Error_Handler("");
  }

  /*##-3- Start PWM signals generation #######################################*/
  /* Start channel 1 */
  if (HAL_TIM_PWM_Start(&TimHandle, TIM_CHANNEL_1) != HAL_OK)
  {
    /* PWM Generation Error */
    Error_Handler("");
  }
  /* Start channel 2 */
  if (HAL_TIM_PWM_Start(&TimHandle, TIM_CHANNEL_2) != HAL_OK)
  {
    /* PWM Generation Error */
    Error_Handler("");
  }
  /* Start channel 3 */
  if (HAL_TIM_PWM_Start(&TimHandle, TIM_CHANNEL_3) != HAL_OK)
  {
    /* PWM generation Error */
    Error_Handler("");
  }
  /* Start channel 4 */
  if (HAL_TIM_PWM_Start(&TimHandle, TIM_CHANNEL_4) != HAL_OK)
  {
    /* PWM generation Error */
    Error_Handler("");
  }

}
  
// THE NETHER REGIONS -- TREAD CAREFULLY

// FOR REFERENCE:
// typedef enum
// {
//   HAL_OK       = 0x00U,
//   HAL_ERROR    = 0x01U,
//   HAL_BUSY     = 0x02U,
//   HAL_TIMEOUT  = 0x03U
// } HAL_StatusTypeDef;

/**
 * @brief  Retargets the C library printf function to the USART.
 * @param  None
 * @retval None
 */
PUTCHAR_PROTOTYPE {
  /* Place your implementation of fputc here */

  /* e.g. write a character to the EVAL_COM1 and Loop until the end of
     transmission */
  // HAL_USART_Transmit(&USARTHandle, (uint8_t *)&ch, 1, 0xFFFF);

  return ch;
}

// void USART_Init(uint32_t baudrate) {
//   // Setup USART for debugging
//   USARTHandle.Instance         = USARTx_INSTANCE;
//   USARTHandle.Init.BaudRate    = baudrate;
//   USARTHandle.Init.WordLength  = USART_WORDLENGTH_8B;
//   USARTHandle.Init.StopBits    = USART_STOPBITS_1;
//   USARTHandle.Init.Parity      = USART_PARITY_NONE;
//   USARTHandle.Init.Mode        = USART_MODE_TX_RX;
//   USARTHandle.Init.CLKPolarity = USART_POLARITY_LOW;
//   USARTHandle.Init.CLKPhase    = USART_PHASE_1EDGE;
//   USARTHandle.Init.CLKLastBit  = USART_LASTBIT_DISABLE;

//   if (HAL_USART_Init(&USARTHandle) != HAL_OK) {
//     Error_Handler("UART Initialization");
//   }
// }

/**
 * @brief  System Clock Configuration
 *         The system Clock is configured as follow :
 *            System Clock source            = PLL (HSE)
 *            SYSCLK(Hz)                     = 120000000
 *            HCLK(Hz)                       = 120000000
 *            AHB Prescaler                  = 1
 *            APB1 Prescaler                 = 4
 *            APB2 Prescaler                 = 2
 *            HSE Frequency(Hz)              = 25000000
 *            PLL_M                          = 25
 *            PLL_N                          = 240
 *            PLL_P                          = 2
 *            PLL_Q                          = 5
 *            VDD(V)                         = 3.3
 *            Flash Latency(WS)              = 3
 * @param  None
 * @retval None
 */
static void SystemClock_Config(void) {
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState       = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState   = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource  = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM       = 16;
  RCC_OscInitStruct.PLL.PLLN       = 240;
  RCC_OscInitStruct.PLL.PLLP       = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ       = 5;

  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler("Oscillator Initialization");
  }

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
  RCC_ClkInitStruct.ClockType =
    (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 |
     RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider  = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK) {
    Error_Handler("Clock Config Initialization");
  }
}

#ifdef  USE_FULL_ASSERT

/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line) {
  /* User can add his own implementation to report the file name and line
     number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  printf("Assertion failed on: file %s on line %d. HALTING...\r\n", file, line);

  while (1) {}
}

#endif /* ifdef  USE_FULL_ASSERT */
