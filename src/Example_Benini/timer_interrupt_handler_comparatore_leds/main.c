#include "main.h"

NVIC_InitTypeDef NVIC_InitStructure;
   TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;  // definizione della struttura per configurare i TIMER
   TIM_OCInitTypeDef  TIM_OCInitStructure; // definizione della strutura per configurare la periferica
  GPIO_InitTypeDef GPIO_InitStructure;


__IO uint16_t CCR1_Val = 0;
uint16_t PrescalerValue = 0;

static void NVIC_Configuration(void);
void LEDs_Configuration(void);

int main(void)
{
   NVIC_Configuration();
   LEDs_Configuration();
   
   // Calcolo del valore del prescaler value, 500 kHz è il contatore del clock del TIMER (CK_CNT) che noi vogliamo
   PrescalerValue = (uint16_t) ((SystemCoreClock / 2) / 500000) - 1; // deve essere impostato prima della funzione TIM_PrescalerConfig (...)

  // Configurazione base del Timer 
  TIM_TimeBaseStructure.TIM_Period = 65535; // 2^16
  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);  //Inizializzazione del TIMER --> Chiedere: il canale dei timer TIM3_CH1 è collegato alla porta PE2, ma i LED3 sono collegato alla PE9 ?

  // Configurazione del Prescaler
  TIM_PrescalerConfig(TIM3, PrescalerValue, TIM_PSCReloadMode_Immediate);

  //Configurazione del canale 1 in Compare Timing Mode 
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing; 
  // Il confronto tra l'uscita del registro di comparazione e il valore del contatore non ha alcun effetto sulle uscite. 
  // (questa modalità è usata per generare una base di temporizzazione). Siamo interessati a un interrupt non in forma d'onda in uscita
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; // Il segnale OC1 è attivo alto nel corrispondente pin di uscita
  TIM_OCInitStructure.TIM_Pulse = 0; // IL registro di confronto è settato a 0 N.B. TIME_BASE NON C'È
  TIM_OC1Init(TIM3, &TIM_OCInitStructure); // Inizializzazione del TIMER3 sul canale 1

  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Disable); // Il registro di confronto può essere scritto in qualsiasi momento, 
                                                     // il nuovo valore è preso in considerazione subito

  // Abilitiamo l'interrupt del canale 1 del TIMER 3
  TIM_ITConfig(TIM3, TIM_IT_CC1, ENABLE);

  /* Abilitiamo il contatore del TIMER3 */
  TIM_Cmd(TIM3, ENABLE);

  /* Infinite loop */
  while (1)
  {
  }
}

/**
  * @brief  Configure the TIM IRQ Handler.
  * @param  None
  * @retval None
  */
static void NVIC_Configuration(void)
{
 
  // Abilita il clock del TIM3 
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

  // Abilita l'interrupt globale del TIM3 gloabal Interrupt 
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

// Inizializza il LED 3 associato alla GPIO_Pin_9 
void LEDs_Configuration(void){
  // STM_EVAL_LEDInit(LED3);
  // or

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
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
