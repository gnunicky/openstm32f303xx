/**
  *
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AGE_COMMON_H
#define __AGE_COMMON_H

#include "stm32f30x.h"

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define CONFIG_CODE_SIZE 8
#define CONFIG_NAME_SIZE 12
#define CONFIG_MAGIC_NUMBER 0xCAFECAFE

#define CONFIG_TOO_DEF 20 //sec
#define CONFIG_TOC_DEF 30 //sec
#define CONFIG_TOM_DEF 5 //sec

#define GATE_STATE_PIN0 LED5
#define GATE_STATE_PIN1 LED7
#define GATE_STATE_PIN2 LED9

#define GATE_STATE_LED LED3
#define GATE_STATE_OPENING_BLINK 400 //0.4sec    
#define GATE_STATE_CLOSING_BLINK 200 //0.2sec    
#define GATE_STATE_FREEPOS_BLINK 100 //0.1sec    

#define MOTOR_STATE_LED LED4
#define MOTOR_STATE_TOO_BLINK 500 //0.5sec    
#define MOTOR_STATE_TOC_BLINK 200 //0.2sec    
#define MOTOR_STATE_TOM_BLINK 100 //0.1sec    

#define MOTOR_DIR_OPEN_LED LED6
#define MOTOR_DIR_CLOSE_LED LED8

#define UART_PC         USART1
#define UART_BRIDGE     USART2
#define UART_PC_SPEED         115200
#define UART_BRIDGE_SPEED     115200

/* Exported types ------------------------------------------------------------*/
    typedef enum {
      TypeUnspecified = 0,
      TypeSliding = 1,
      TypeSwing = 2,
   } Type_e;

   typedef struct {
      uint32_t magic_number;
      char name[CONFIG_NAME_SIZE];
      char code[CONFIG_CODE_SIZE];
      uint8_t id;
      uint8_t to_open;
      uint8_t to_close;
      uint8_t to_move;
      Type_e type;
   } Config_t;

   typedef enum {
      GateStateClose        = 0x00, //000
      GateStateOpening      = 0x01, //001
      GateStateOpen         = 0x02, //010
      GateStateClosing      = 0x03, //011
      GateStateFreePosition = 0x04, //100
   } GateState_e;
   
   typedef enum {
      MotorStateIdle        = 0x00, 
      MotorStateMotion      = 0x01, 
      MotorStateErrorTOO    = 0x02, 
      MotorStateErrorTOC    = 0x03, 
      MotorStateErrorTOM    = 0x04, 
   } MotorState_e;

   typedef enum {
      MotorDirOpen = 1, 
      MotorDirNone = 0, 
      MotorDirClose = -1, 
   } MotorDir_e;
   
/* Includes ------------------------------------------------------------------*/
#include "AGE_Base.h"
#include "AGE_Commands.h"
#include "AGE_Emulator.h"
#include "AGE_UART_Protocol.h"
   
/* Exported functions ------------------------------------------------------- */

#endif /* __AGE_COMMON_H */
