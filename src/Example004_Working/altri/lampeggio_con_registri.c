#include "main.h"

__IO uint32_t TimingDelay = 0;
// GPIO_InitTypeDef GPIO_InitStructure;

int main(void)
{
  if (SysTick_Config(SystemCoreClock / 1000)){
    while (1)
    {}
  }
  // GPIOE clock enable
  RCC->AHBENR |= RCC_AHBENR_GPIOEEN; // or RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
  
  // Configure PE9 in output push-pull mode 
  GPIOE->MODER |= 1UL << 9*2; // or GPIOE->MODER = 1<<18 or GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  
  GPIOE->OTYPER |= 0L << 9; // or GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;

  GPIOE->OSPEEDR |= 3UL << 9*2; // or GPIOE->OSPEEDR= 2<<18 or GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIOE->PUPDR |= 0L << 9*2; // or GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

  /* Infinite loop */
  while (1)
  {
    GPIOE->ODR ^= 1L<<9; // Toggle Led state GPIOE->ODR=GPIOE->ODR ^ 1L<<9 ;
    Delay(500); 
    // or
    // GPIOE->ODR = 1<<9;
    // Delay(500); 
    // GPIOE->BRR = 1<<9;
    // Delay(500); 
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
