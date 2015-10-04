
/* Includes ------------------------------------------------------------------*/
#include "main.h"

#ifdef MAIN_EXTENDED

/** @addtogroup STM32F3_Discovery_Peripheral_Examples
  * @{
  */

/** @addtogroup ADC_Example
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint32_t TimingDelay = 0;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  /*!< At this stage the microcontroller clocka setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f30x.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f30x.c file
     */ 
      
  /* Setup SysTick Timer for 1 µsec interrupts  */
  if (SysTick_Config(SystemCoreClock / 1000000))
  { 
    /* Capture error */ 
    while (1)
    {}
  }
  USART_TypeDef * USARTx = USART1;
  char USARTx_str[] = "USART1";

  APP_USART_Init(USARTx, 0);
  APP_USART_SendString(USARTx, "MicroLabDemo - ");
  APP_USART_SendString(USARTx, USARTx_str);
  APP_USART_SendString(USARTx, "\r\nVersion 0");
  APP_USART_SendString(USARTx, "\r\n");
  
  Delay(1000);
  APP_USART_SendString(USARTx, "Ready.\r\n\r\n");

  STM_EVAL_LEDInit(LED3);
  STM_EVAL_LEDInit(LED4);
  STM_EVAL_LEDInit(LED5);

  /* Infinite loop */
#define STEP 2
  while (1)
  {
#if STEP == 1
    APP_USART_SendString(USARTx, "HELLO ");
    Delay(500000);
    APP_USART_SendString(USARTx, "WORLD\r\n"); 
    Delay(1000000);
#endif
#if STEP == 2
    Delay(500000);
    STM_EVAL_LEDToggle(LED3);
#endif
  }
}

/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */
void Delay(__IO uint32_t nTime)
{ 
  TimingDelay = nTime;

  while(TimingDelay != 0);
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */ 

/**
  * @}
  */ 
#endif
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
