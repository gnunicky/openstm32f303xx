#include "stm32f30x.h"
#include "stm32f3_discovery.h"
#include <stdio.h>

/* Private variables ---------------------------------------------------------*/
//  RCC_ClocksTypeDef RCC_Clocks;
//__IO uint32_t TimingDelay = 0;

/* Private function prototypes -----------------------------------------------*/
//void TimingDelay_Decrement(void);
//void Delay(__IO uint32_t nTime);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
//void SysTick_Handler(void)
//{
//  TimingDelay_Decrement();
//}

/**
  * @brief  Main program.
  * @param  None 
  * @retval None
  */
int n=0;

int main(void)
{  
  char str[2];
  /* SysTick end of count event each 10ms */
  //RCC_GetClocksFreq(&RCC_Clocks);
  //SysTick_Config(RCC_Clocks.HCLK_Frequency / 100);
  //setbuf(stdout, NULL);
  printf("Hello world1\r\n");
  //scanf("%d",&n);
  //fflush(stdin);

  gets(str);
  printf("Hello world2\r\n");
  puts(str);
  printf("Hello world3\r\n");
  for (;;) ;
  /* Infinite loop */
  //while (1)
  //{      
  //  Delay(50); /*500ms - half second*/
  //}
  return 0;
}
/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in 10 ms.
  * @retval None
  */
//void Delay(__IO uint32_t nTime)
//{
//  TimingDelay = nTime;

//  while(TimingDelay != 0);
//}

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
//void TimingDelay_Decrement(void)
//{
//  if (TimingDelay != 0x00)
//  { 
//    TimingDelay--;
//  }
//}

//#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
//void assert_failed(uint8_t* file, uint32_t line)
//{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
//  while (1)
//  {
//  }
//}
//#endif
