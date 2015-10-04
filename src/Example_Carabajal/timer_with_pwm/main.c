#include "main.h"
// GPIO_InitTypeDef GPIO_InitStructure;


int main(void)
{
  // Enable GPIOE clock
  RCC->AHBENR |= RCC_AHBENR_GPIOCEN; 
  // or RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

  // Enable TIM 3 clock
  RCC->APB1ENR |= RCC_APB1ENR_TIM3EN; 

  //PC8 configuration
  GPIOC->MODER |= 2 << (8*2); // Alternate function mode
  // or GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;

  GPIOC->OTYPER |= 0L << 8; // Output push pull (reset state)
  // or GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;

  GPIOC->OSPEEDR |= 0 << (8*2); // 2 Mhz High speed 
  // or GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;

  GPIOC->AFR[1] |= 2 << ((8-8)*4); // Select AF2 for PC8: TIM3_CH3
  
  // Period = (PSC+1)*ARR/FAPB1 =(600*6000)/72000000 = 50 ms, Duty = 25ms
  TIM3->PSC = 599; // Set pre-scaler to 600 (PSC+1)
  TIM3->ARR = 600; // Auto reload value 600
  TIM3->CCR3 = 600/5; // Start PWM duty for channel 3
  TIM3->CCMR2 |= TIM_CCMR2_OC3M_2 |  TIM_CCMR2_OC3M_1; // PWM mode 1 on channel 3  
  TIM3->CCER |= TIM_CCER_CC3E; // Enable compare on channel 3
  TIM3->CR1 |= TIM_CR1_CEN; // Enable timer

  /* Infinite loop */
  while (1);
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
