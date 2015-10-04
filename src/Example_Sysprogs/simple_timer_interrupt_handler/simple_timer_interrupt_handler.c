       #include "main.h"
       void InitializeLEDs()
       {
           RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
           GPIO_InitTypeDef gpioStructure;
           gpioStructure.GPIO_Pin = GPIO_Pin_9;
           gpioStructure.GPIO_Mode = GPIO_Mode_OUT;
           gpioStructure.GPIO_Speed = GPIO_Speed_50MHz;
           GPIO_Init(GPIOE, &gpioStructure);
           GPIO_WriteBit(GPIOE, GPIO_Pin_9 | GPIO_Pin_8, Bit_RESET);
       }
       void InitializeTimer()
       {
           RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
           TIM_TimeBaseInitTypeDef timerInitStructure;
           timerInitStructure.TIM_Prescaler = 40000;
           timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
           timerInitStructure.TIM_Period = 500;
           timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
           timerInitStructure.TIM_RepetitionCounter = 0;
           TIM_TimeBaseInit(TIM2, &timerInitStructure);
           TIM_Cmd(TIM2, ENABLE);
	   TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
       }
       void TIM2_IRQHandler(void)
       {
           if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
           {
               TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	       GPIOE->ODR ^= 1L <<9;
           }
       }
       void EnableTimerInterrupt()
       {
           NVIC_InitTypeDef nvicStructure;
           nvicStructure.NVIC_IRQChannel = TIM2_IRQn;
           nvicStructure.NVIC_IRQChannelPreemptionPriority = 0;
           nvicStructure.NVIC_IRQChannelSubPriority = 1;
           nvicStructure.NVIC_IRQChannelCmd = ENABLE;
           NVIC_Init(&nvicStructure);
       }
       int main()
       {
           InitializeLEDs();
           InitializeTimer();
	   EnableTimerInterrupt();	
           for (;;)
           {
           }
       }
