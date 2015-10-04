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
uint32_t stato=50;
GPIO_InitTypeDef GPIO_InitStructure; // dichiariamo la struttura abilitando 
// il GPIO_LED Clock 

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
      
  /* Setup SysTick Timer for 1 msec interrupts  */
  if (SysTick_Config(SystemCoreClock / 1000))
  // SysTick Interrupt Period = Reload Value Register divided  Clock Frequency:
  // (SystemCoreClock /1000)/SystemCoreClock = 1/1000 = 1ms
  // definisce in stm32f30x_it.c SysTick_Handler
  { 
    /* Capture error */ 
    while (1)
    {}
  }
  
  /* Inzializza i LED della STM32F3-Discovery board */
  // STM_EVAL_LEDInit(LED3); // e' riferito al pin PE9, led rosso  
  // STM_EVAL_LEDInit(LED4); //e' riferito al pin PE8, led blu
  // STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_GPIO); // Pulsante e' riferito al pin PA0, 
  // tale funzione vuole un Buttone e la modalità, dove abbiamo 2 modalità tramite
  // EXTI (cioe' interrupt) o GPIO (che trattiamo) 
  
  // FUNZIONI DI LIBRERIA VALGONO PER QUALSIASI MICRO
  
  //Configura il GPIO_LED pin e abilita AHB1 BUS Port E
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
  /*Configura il Pin 8 e 9 nella Port E come output*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOE,&GPIO_InitStructure);
   
  //Configura il GPIO_LED pin e abilita AHB1 BUS Port A
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  /*Configura il Pin 0 nella Port A come input*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA,&GPIO_InitStructure); 
  
  /* Infinite loop */
  while (1)
  {
    /* LEDs Off */
    //STM_EVAL_LEDOn(LED3);
    //STM_EVAL_LEDOn(LED4);
    //for(int i=0;i<0xFFFFF;i++);  Al poststo del Delay posso utilizzare un ciclo for fino a FFFFF(16)=1048575(10)
    //Delay(50); /*500ms - half second --> il periodo e' T=100 ms*/

    /* LEDs Off */
    //STM_EVAL_LEDOff(LED3);
    //STM_EVAL_LEDOff(LED4);
    // for(int i=0;i<0xFFFFF;i++); // Al poststo del Delay posso utilizzare un ciclo for fino a FFFFF(16)=1048575(10)
    //Delay(50); /*500ms - half second --> il periodo e' T=100 ms*/
    
    /*Variabile Stato, si accende il LED 4 alla pressione del BUTTON_USER*/
    // stato=STM_EVAL_PBGetState(BUTTON_USER); 
    // if(stato==0) {
    //   STM_EVAL_LEDOff(LED4);
    // }
    // else {
    //  STM_EVAL_LEDOn(LED4);
    // }
    // oppure
    // if(state!=0){
    //    STM_EVAL_LEDOn(LED4);
    //    Delay(50);
    //    STM_EVAL_LEDOff(LED4);
    //    Delay(50);
    //  }
    
    /* LEDs On */
    // GPIO_SetBits(GPIOE, GPIO_Pin_9 | GPIO_Pin_8); 
    // oppure
    // GPIOE->BSRR = 1<<9; // GPIO port bit set/reset, setta a 1, con uno shift 
    // verso sinistra il pin PE9, quindi si accende il LED3
    // Delay(50);
    
    /* LEDs Off */
    // GPIO_ResetBits(GPIOE, GPIO_Pin_9 | GPIO_Pin_8);
    // oppure
    // GPIOE->BRR = 1<<9; // GPIO Port bit reset, setta a 0, con uno shift 
    // verso sinistra il pin PE9, quindi si spegne il LED3
    // oppure
    // GPIOE->BSRR = (1<<9)<<16; // Shift a sinistra sulla parte bassa dei 16 bit
    // Delay(50); 
    
     /*Variabile Stato, si accende il LED 4 alla pressione del BUTTON_USER*/
     // stato=STM_EVAL_PBGetState(BUTTON_USER); 
     stato = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
     GPIOE->BSRR = stato == 0 ? ((1<<8)<<16) : (1<<8);
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
