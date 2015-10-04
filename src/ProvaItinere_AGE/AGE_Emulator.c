/*
serve per emulare il sensore di posizione ed i sensori di fine corsa
*/

/* Includes ------------------------------------------------------------------*/
#include "AGE_Emulator.h"
#include "AGE_Common.h"
#include "stm32f30x_dac.h"
#include "stm32f30x_gpio.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define TICK_UPDATE_MAX 100 //0.1sec
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint16_t DACValue = 200;
__IO int *pEmulationPosition = 0; /* 0 - 100 */
__IO int TickUpdateCount = 0;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

extern int SensorPosition;

void AGE_Emulator_Init()
{
  pEmulationPosition = &SensorPosition;
 
  //dac to emulate position
  DAC_InitTypeDef DAC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  
  /* DAC Periph clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);

  /* GPIOA clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

  /* Configure A4(DAC_OUT1) as analog */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  //DAC initialization
  DAC_InitStructure.DAC_Trigger = DAC_Trigger_None;
  DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
  //DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bits11_0;
  DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable;
  /* DAC Channel2 Init */
  DAC_Init(DAC_Channel_1, &DAC_InitStructure);
  
  /* Enable DAC Channel1 */
  DAC_Cmd(DAC_Channel_1, ENABLE);
  
  DAC_SetChannel1Data(DAC_Align_12b_R, DACValue);
  
  
  //sensori fine corsa
  /* Enable the GPIO_LED Clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

  /* Configure the GPIO_LED pin */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);  
}

void AGE_Emulator_Running()
{
  MotorDir_e motordir = AGE_GetMotorDir();
  if (motordir != MotorDirNone)
  {
    if (TickUpdateCount == 0)
    {
      //if (motordir == MotorDirOpen && *pEmulationPosition < 100) (*pEmulationPosition)++;
      //if (motordir == MotorDirClose && *pEmulationPosition > 0) (*pEmulationPosition)--;
      if (motordir == MotorDirOpen && (*pEmulationPosition) < 100) DACValue += 10;
      if (motordir == MotorDirClose && (*pEmulationPosition) > 0) DACValue -= 10;
      
      DAC_SetChannel1Data(DAC_Align_12b_R, (uint16_t)DACValue);
    }

    TickUpdateCount++;
    TickUpdateCount %= TICK_UPDATE_MAX;
  }

  //end of carriage emulators update
  if (*pEmulationPosition == 0)
  {
    //close, set C5 and reset C4
    GPIOC->BSRR = (GPIO_Pin_4<<16) | GPIO_Pin_5;
  }
  else if (*pEmulationPosition >= 100)
  {
    //open, set C4 and reset C5
    GPIOC->BSRR = (GPIO_Pin_5<<16) | GPIO_Pin_4;
  }
  else
  {
    //intermediate, reset C4 and C5
    GPIOC->BSRR = (GPIO_Pin_4 | GPIO_Pin_5)<<16;
  }
}
/**
  * @brief  .
  * @param  None
  * @retval None
  */
