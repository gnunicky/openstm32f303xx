/**
  ******************************************************************************
  * @file    ADC_Example/main.c 
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    20-September-2012
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdio.h>
#include <string.h>

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

//RCC_ClocksTypeDef RCC_Clocks;
__IO uint32_t TimingDelay = 0;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void Delay(__IO uint32_t nTime);

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */

int i=0, n, f;
char buffer [4];
char *str;

int fattoriale_ricorsivo(int num) 
{
   if (num<0) return -1;
   if (num==0) return 1;
   else 
    return num*fattoriale_ricorsivo (num-1);    
} 

int fattoriale_iterativo(int num) 
{
  int j, f;
  if (num<0) return -1;
  if (num==0) return 1;
  f=1;
  for (j=1; j <= num; j++) f = f * j;
 return f;
}

char* itoa(int val, int base){
	static char buf[32] = {0};
	int i = 30;
	for(; val && i ; --i, val /= base)
		buf[i] = "0123456789abcdef"[val % base];
 return &buf[i+1];	
}



int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f30x.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f30x.c file
  */ 
  // Setup SysTick Timer for 1 ms interrupts  
   if (SysTick_Config(SystemCoreClock / 1000))  // SystemCoreClock = 72 Mhz 
    //SysTick interrupt period = the Reload Value register divided by clock frequency = (SystemCoreClock/1000)/SystemCoreClock = 1/1000 = 1ms
     { 
       //Capture error 
       while (1);
     }
  
  n=1;  
  /* Infinite loop */
  while (1)
  {
    printf("Enter an number >= 0:\r\n");
    fgets (buffer, 4, stdin);
    n = atoi (buffer);
    //f=fattoriale_iterativo(n);
    f=fattoriale_ricorsivo(n);
    str=itoa(f,10);
    puts(str);
    printf("End factorial\r\n");
    i++;
   Delay(50);
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
