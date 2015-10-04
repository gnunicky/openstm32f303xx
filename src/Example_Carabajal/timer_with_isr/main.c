#include "main.h"
// GPIO_InitTypeDef GPIO_InitStructure;


int main(void)
{
  // GPIOE clock enable
  RCC->AHBENR |= RCC_AHBENR_GPIOEEN; 
  // or RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);

  // TIM3 clock enable
  RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

  // PE9 configuration in output push-pull mode 
  GPIOE->MODER |= 1UL << 9*2; 
  // or GPIOE->MODER = 1<<18 
  // or GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  
  GPIOE->OTYPER |= 0L << 9; 
  // or GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;

  GPIOE->OSPEEDR |= 3UL << 9*2; 
  // or GPIOE->OSPEEDR= 2<<18 
  // or GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIOE->PUPDR |= 0L << 9*2; 
  // or GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  
  // delay = 0.5 = (PSC+1)*ARR/FAPB1 =(600*60000)/72000000=0.5 sec
  TIM3->PSC = 599; // Set pre-scaler to 600 (PSC+1)
  TIM3->ARR = 60000; // Auto reload value 60000
  TIM3->CR1 = TIM_CR1_CEN; // Enable timer

  TIM3->DIER |=1 << 0; //Enable interrupt
  NVIC->ISER[0] |=1 <<29; // Enable TIM3 interrupt in NVIC

  /* Infinite loop */
  while (1);
}

void TIM3_IRQHandler (void)
{
  if (TIM3->SR & TIM_SR_UIF){ // if UIF flag is set
    TIM3->SR &= ~TIM_SR_UIF; // clear UIF flag
    GPIOE->ODR ^= 1L<<9; // toggle Led state
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
