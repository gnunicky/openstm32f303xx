/**
  *
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AGE_BASE_H
#define __AGE_BASE_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f3_discovery.h"
#include "AGE_Common.h"
    
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void AGE_Init(void);
void AGE_InitDigitalSensor(void);
void AGE_InitAnalogSensor(void);
void AGE_Running(void);

void AGE_Led(Led_TypeDef, int);

GateState_e AGE_GetGateState(void);
MotorState_e AGE_GetMotorState(void);
MotorDir_e AGE_GetMotorDir();

void AGE_SetGateState(GateState_e);
void AGE_SetMotorState(MotorState_e);
void AGE_SetMotorDir(MotorDir_e);

uint8_t AGE_EndOfCarriage(uint8_t);

void AGE_Config_Reset(void);
int AGE_Config_DataValid();
void AGE_Config_Default(void);
int AGE_Config_Load(void);
void AGE_Config_Save(void);
void AGE_Config_Erase(void);

#endif /* __AGE_BASE_H */
