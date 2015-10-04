#include "main.h"

#ifdef MAIN_EASY

/* Includes ------------------------------------------------------------------*/

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
GPIO_InitTypeDef GPIO_InitStructure;
int data_arrived = 0;
int nibble_high  = 0;
int nibble_low   = 0;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
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
//USART1
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);    
  //RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE); 
    
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_7);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_7);

  /* conf */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_9 | GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  //USART configuration
  USART_InitTypeDef USART_InitStructure;

  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_HardwareFlowControl = 
  USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;    
  USART_Init(USART1, &USART_InitStructure);
  
  USART_Cmd(USART1, ENABLE);

  USART_SendData(USART1, 'H');  Delay(100);
  USART_SendData(USART1, 'e');  Delay(100);
  USART_SendData(USART1, 'l');  Delay(100);
  USART_SendData(USART1, 'l');  Delay(100);
  USART_SendData(USART1, 'o');  Delay(100);
  USART_SendData(USART1, ' ');  Delay(100);
  USART_SendData(USART1, 'W');  Delay(100);
  USART_SendData(USART1, 'o');  Delay(100);
  USART_SendData(USART1, 'r');  Delay(100);
  USART_SendData(USART1, 'l');  Delay(100);
  USART_SendData(USART1, 'd');  Delay(100);
  USART_SendData(USART1, '!');  Delay(100);
  USART_SendData(USART1, '\r');  Delay(100);
  USART_SendData(USART1, '\n');  Delay(100);

  /* Infinite loop */
  while (1)
  {
    if ( USART_GetFlagStatus(USART1, USART_IT_RXNE) == SET)
    {
      USART_ClearFlag(USART1, USART_IT_RXNE);

      data_arrived = USART_ReceiveData(USART1);

      //divido il byte nei due nibble
      nibble_high = (data_arrived & 0xF0) / 16;
      nibble_low  = data_arrived & 0x0F;
      
      char data;
      
      //mando il primo nibble
      
      //verifico se e' compreso tra 0 e 9
      if (nibble_high >= 0 && nibble_high <= 9)
      {
        data = nibble_high + 48;
      }
      else
      {
        //altrimenti e' una lettera
        switch(nibble_high)
        {
        case 10: data = 'A'; break;
        case 11: data = 'B'; break;
        case 12: data = 'C'; break;
        case 13: data = 'D'; break;
        case 14: data = 'E'; break;
        case 15: data = 'F'; break;
        }
      }

      //invio il dato sulla seriale
      USART_SendData(USART1, data); Delay(100);

      //mando il secondo nibble
      
      //verifico se e' compreso tra 0 e 9
      if (nibble_low >= 0 && nibble_low <= 9)
      {
        data = nibble_low + 48;
      }
      else
      {
        //altrimenti e' una lettera
        switch(nibble_low)
        {
        case 10: data = 'A'; break;
        case 11: data = 'B'; break;
        case 12: data = 'C'; break;
        case 13: data = 'D'; break;
        case 14: data = 'E'; break;
        case 15: data = 'F'; break;
        }
      }

      //invio il dato sulla seriale
      USART_SendData(USART1, data); Delay(100);
    }  
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