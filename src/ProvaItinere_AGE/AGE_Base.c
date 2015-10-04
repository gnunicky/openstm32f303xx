
/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "tools.h"

#include "AGE_Base.h"
#include "AGE_Common.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
GateState_e GateState;
MotorState_e MotorState;
MotorDir_e MotorDir;
Config_t Config;
uint32_t ADC2ConvertedValue = 0; //only for debug
int SensorPosition = 0; // <= 500       => 0
                        // 500 <x< 1500 => (x - 500) / 10
                        // >= 1500      => 100
int EndOfCarriageOpen = 0;  //only for debug
int EndOfCarriageClose = 0; //only for debug

int GateStateIndicationTime = 0; //ms
int MotorStateIndicationTime = 0; //ms

int Cmd = 0; //only for debug

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  .
  * @param  None
  * @retval None
  */

void AGE_Init()
{
  //load from flash the configuration
  AGE_Config_Reset();
  if (!AGE_Config_Load())
  {
    AGE_Config_Default();
  }

 //#warning AEG.1
  //** inserire le inizializzazioni per le variabili di stato GateState, MotorState, MotorDir
  //** note: esistono funzioni specifiche per il set
  
  GateState=GateStateClosing;
  MotorState=MotorStateIdle;
  MotorDir=MotorDirNone;
  
     
  AGE_SetGateState(GateStateClose);
  
  
  
 
  
  //status bits
  STM_EVAL_LEDInit(GATE_STATE_PIN0);
  STM_EVAL_LEDInit(GATE_STATE_PIN1);
  STM_EVAL_LEDInit(GATE_STATE_PIN2);

  //state feedback
  STM_EVAL_LEDInit(GATE_STATE_LED);
  
  //motor status
  STM_EVAL_LEDInit(MOTOR_STATE_LED);
  
  //motor direction
  STM_EVAL_LEDInit(LED6); //open direction
  STM_EVAL_LEDInit(LED8); //close direction

  //presence A
  STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_GPIO);
  
#warning AEG.2
  //** configurare le USART1 e USART2
  //** attenzione esistono le define UART_PC e UART_BRIDGE
  //**attenzione2 usare la funzione APP_USART_Init
  
   APP_USART_Init(USART1, 0, UART_PC_SPEED);
   
  
  /* RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART1,ENABLE); 
    
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_7);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_7);

  
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
*/

  
  //PC Interface UART initialization
  
  //Brdige UART initialization
  
  AGE_InitDigitalSensor();
  AGE_InitAnalogSensor();
  
  AGE_Emulator_Init();
}
void AGE_InitDigitalSensor()
{
  //init if digital sensor
  //A6
  //A7
  //A0 -- this pin is initialized as userbutton, don't initialize again it
  //A1
  GPIO_InitTypeDef  GPIO_InitStructure;
  
  /* Enable the GPIO_LED Clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
#warning AEG.3
  //** inizializzare i pin per A0,A1,A6,A7
  //** Attenzione il pin A0 è gia collegato al pushbutton
}

void AGE_InitAnalogSensor()
{
  ADC_InitTypeDef ADC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  ADC_CommonInitTypeDef ADC_CommonInitStructure;
  
  //init of the ADC2 Ch1 GPIO A4
  //used as position sensor

  /* Configure the ADC clock */
  RCC_ADCCLKConfig(RCC_ADC12PLLCLK_Div2);
  
  /* Enable ADC12 clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_ADC12, ENABLE);

  /* ADC Channel configuration */
  /* GPIOC Periph clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

#warning AEG.4
  //** mettere il pin corretto affinché l'adc acquisisca dal canale ADC2_CH2 (pin A5)
  //** decommentare le riche di codice di inizializzazione avendo cura di mettere l'ADC corretta
  /* Configure ADC Channel2 as analog input */
  GPIO_InitStructure.GPIO_Pin = 0xFF ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  ADC_StructInit(&ADC_InitStructure);

  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;                                                                    
  ADC_CommonInitStructure.ADC_Clock = ADC_Clock_AsynClkMode;                    
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;             
  ADC_CommonInitStructure.ADC_DMAMode = ADC_DMAMode_OneShot;                  
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = 0;          
  //** ADC_CommonInit(/* ADC */, &ADC_CommonInitStructure);
  
  ADC_InitStructure.ADC_ContinuousConvMode = ADC_ContinuousConvMode_Enable;
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b; 
  ADC_InitStructure.ADC_ExternalTrigConvEvent = ADC_ExternalTrigConvEvent_0;         
  ADC_InitStructure.ADC_ExternalTrigEventEdge = ADC_ExternalTrigEventEdge_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_OverrunMode = ADC_OverrunMode_Disable;   
  ADC_InitStructure.ADC_AutoInjMode = ADC_AutoInjec_Disable;  
  ADC_InitStructure.ADC_NbrOfRegChannel = 1;
  //** ADC_Init(/* ADC */, &ADC_InitStructure);
  
  /* ADC2 regular channel configuration */ 
  //** ADC_RegularChannelConfig(/* ADC */, ADC_Channel_2, 1, ADC_SampleTime_7Cycles5);
   
  /* Enable ADC2 */
  //** ADC_Cmd(/* ADC */, ENABLE);
  
  /* wait for ADRDY */
  while(!ADC_GetFlagStatus(ADC2, ADC_FLAG_RDY));
  
  ADC_StartConversion(ADC2);
}

void AGE_ReadAnalogSensor()
{
  /* Test EOC flag */
  while(ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC) == RESET);

#warning AEG.5
  //** ADC2ConvertedValue deve prendere il valore convertito dell'ADC
  /* Get ADC2 converted data */
  ADC2ConvertedValue = 0; //manca la funzione ...
  
  /* Compute the voltage */
  if (ADC2ConvertedValue <= 500)
  {
    SensorPosition = 0;
  }
  else if (ADC2ConvertedValue >= 1500)
  {
    SensorPosition = 100;
  }
  else
  {
    SensorPosition = (ADC2ConvertedValue - 500) / 10;
  }
}

//called by systick to update the status each 10ms
void AGE_Running()
{
  //Gate state pin
  //set bits
  AGE_Led(GATE_STATE_PIN0, (GateState & 0x01));
  AGE_Led(GATE_STATE_PIN1, (GateState & 0x02));
  AGE_Led(GATE_STATE_PIN2, (GateState & 0x04));

  //Gate state
  switch(GateState)
  {
  case GateStateClose: //gate state led on
    AGE_Led(GATE_STATE_LED, 1);
    break;
  case GateStateOpen: //gate state led off
    AGE_Led(GATE_STATE_LED, 0);
    break;
  case GateStateOpening: //gate state led blink
    AGE_Led(GATE_STATE_LED, GateStateIndicationTime / GATE_STATE_OPENING_BLINK);
    GateStateIndicationTime = (GateStateIndicationTime + 1) % ((GATE_STATE_OPENING_BLINK)<<1);
    break;
  case GateStateClosing: //gate state led blink
    AGE_Led(GATE_STATE_LED, GateStateIndicationTime / GATE_STATE_CLOSING_BLINK);
    GateStateIndicationTime = (GateStateIndicationTime + 1) % ((GATE_STATE_CLOSING_BLINK)<<1);
    break;
  case GateStateFreePosition: //gate state led blink
    AGE_Led(GATE_STATE_LED, GateStateIndicationTime / GATE_STATE_FREEPOS_BLINK);
    GateStateIndicationTime = (GateStateIndicationTime + 1) % ((GATE_STATE_FREEPOS_BLINK)<<1);
    break;
  }

#warning AEG.6
  //** manca la gestione dell'indication per il MotorState, completare lo switch  
  //** attenzione: esistono come per il caso precedente delle define su AGE_Common.h
  //Indication according to MotorState
  switch(MotorState)
  {
  case MotorStateIdle:
    //motorstate led off
    break;
  case MotorStateMotion:
    //motorstate led on
    break;
  case MotorStateErrorTOO:
    //motorstate blink
    break;
  case MotorStateErrorTOC:
    //motorstate blink
    break;
  case MotorStateErrorTOM:
    //motorstate blink
    break;
  }

  AGE_Led(MOTOR_DIR_OPEN_LED, MotorDir == MotorDirOpen);
#warning AEG.7
  //** inserire l'aggiornamento del led anche per la motor dir close  
 
  AGE_ReadAnalogSensor();
  
  //get end of carriage open and close
  EndOfCarriageOpen = AGE_EndOfCarriage(1);
  EndOfCarriageClose = AGE_EndOfCarriage(0);
  
  if (Cmd != 0)
  {
    switch(Cmd)
    {
    case 1:
      AGE_Config_Load();
      break;
    case 2:
      AGE_Config_Save();
      break;
    case 3:
      AGE_Config_Erase();
      break;
    case 4:
      //empty
      break;
    }
    Cmd = 0;
  }
 }

inline void AGE_Led(Led_TypeDef led, int value)
{
#warning AEG.8
  //** completare questa funzione usando le funzioni fornite dal layer del discovery kit
  if (value)
  {
    //on
  }
  else
  {
    //off
  }
}

GateState_e AGE_GetGateState()
{
  return GateState;
}
void AGE_SetGateState(GateState_e gatestate)
{
  GateState = gatestate;
  
  //reset blink counter
  GateStateIndicationTime = 0;
}

MotorState_e AGE_GetMotorState()
{
#warning AEG.9
  //** sistemare la funzione
  return MotorStateIdle;
}
void AGE_SetMotorState(MotorState_e motorstate)
{
#warning AEG.10
  //** sistemare la funzione
  //assign value
  //** manca qualcosa
  
  //reset blink counter  
  //** manca qualcosa altro
}
MotorDir_e AGE_GetMotorDir()
{
  return MotorDir;
}
void AGE_SetMotorDir(MotorDir_e motordir)
{
  MotorDir = motordir;
}

uint8_t AGE_EndOfCarriage(uint8_t open) /* 1 open, 0 close */
{
#warning AEG.11
  //** sistemare la funzione considerato che deve restituire il valore del pin A6 se open e A7 se close
  //** usare la funzione GPIO_ReadInputDataBit
  return 0;
}


//** Flash don't touch, please
void AGE_Config_Reset()
{
  memset(&Config, 0, sizeof(Config_t));
  Config.magic_number = CONFIG_MAGIC_NUMBER;
}

int AGE_Config_DataValid()
{
  Config_t conf_tmp;
  
  APP_FLASH_Read((char *)&conf_tmp, sizeof(Config_t));
  return (conf_tmp.magic_number == CONFIG_MAGIC_NUMBER);
}

void AGE_Config_Default()
{
  Config.magic_number = CONFIG_MAGIC_NUMBER;
  strcpy(Config.name, "NONE");
  strcpy(Config.code, "0000");
  Config.id = 0xFF;
  Config.to_open = CONFIG_TOO_DEF;
  Config.to_close = CONFIG_TOC_DEF;
  Config.to_move = CONFIG_TOM_DEF;
  Config.type = TypeUnspecified;
}
int AGE_Config_Load()
{
  Config_t conf_tmp;
  int ret = 0;
  APP_FLASH_Read((char *)&conf_tmp, sizeof(Config_t));
  ret = conf_tmp.magic_number == CONFIG_MAGIC_NUMBER;
  if (ret)
  {
    memcpy(&Config, &conf_tmp, sizeof(Config_t));
  }
  return ret;
}

void AGE_Config_Save()
{
  APP_FLASH_Write((char *)&Config, sizeof(Config_t));
}

void AGE_Config_Erase()
{
  APP_FLASH_Erase();
}