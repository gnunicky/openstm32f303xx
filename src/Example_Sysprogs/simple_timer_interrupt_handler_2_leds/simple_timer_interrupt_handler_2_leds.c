       #include "main.h"
       __IO uint32_t TimingDelay=0;
       GPIO_InitTypeDef gpioStructure;

       void InitializeLEDs()
       {
           RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
           gpioStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
           gpioStructure.GPIO_Mode = GPIO_Mode_OUT;
           gpioStructure.GPIO_Speed = GPIO_Speed_50MHz;
           GPIO_Init(GPIOE, &gpioStructure);
           GPIO_WriteBit(GPIOE, GPIO_Pin_8 | GPIO_Pin_9, Bit_RESET);
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
       
       void EnableTimerInterrupt()
       {
           NVIC_InitTypeDef nvicStructure;
           nvicStructure.NVIC_IRQChannel = TIM2_IRQn;
           nvicStructure.NVIC_IRQChannelPreemptionPriority = 0;
           nvicStructure.NVIC_IRQChannelSubPriority = 1;
           nvicStructure.NVIC_IRQChannelCmd = ENABLE;
           NVIC_Init(&nvicStructure);
       }

       void Delay(uint32_t nTime)
       {
	   TimingDelay = nTime;
	   while (TimingDelay != 0);
       }

       int main()
       {   
	   if (SysTick_Config(SystemCoreClock / 1000))
	   {
		while (1);
	   }
           InitializeLEDs();
           InitializeTimer();
	   EnableTimerInterrupt();	
           for (int i = 0; i < 1000000; i++)
	   {
	     GPIOE->ODR ^= 1L <<8;
             Delay(500);
	   }    
       }
