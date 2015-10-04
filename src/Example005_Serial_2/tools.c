/**
  ******************************************************************************
  * @file    tools.c 
  * @author  AR
  * @version V1.0.0
  * @date    
  * @brief   
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************  
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f30x_usart.h"
#include "tools.h"
#include "stm32f3_discovery.h"

    
void APP_USART_Init(USART_TypeDef * USARTx, uint8_t conf)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    uint8_t USARTx_IRQn = -1;
    
    if (USARTx == USART2)
    {
	/* enable peripheral clock for USART2 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	/* GPIOA clock enable */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	/* GPIOA Configuration:  USART2 TX on PA2, RX on PA3 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Connect USART2 pins to AF7 */
	// TX = PA2
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_7);
	// RX = PA3
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_7);
        
        USARTx_IRQn = USART2_IRQn;
    }

    if (USARTx == USART1)
    {
      switch(conf)
      {
        case 0:
          //configure USART1 on PA9 and PA10
          
          /* enable peripheral clock for USART1 */
          RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

          /* GPIOB clock enable */
          RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

          /* GPIOA Configuration:  USART1 TX on PA9, RX on PA10 */
          GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
          GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
          GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
          GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
          GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
          GPIO_Init(GPIOA, &GPIO_InitStructure);

          /* Connect USART1 pins to AF2 */
          // TX = PA9
          GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_7);
          // RX = PA10
          GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_7);
          break;
        
      case 1:
          //configure USART1 on PB6 and PB7
          
          /* enable peripheral clock for USART1 */
          RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

          /* GPIOB clock enable */
          RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

          /* GPIOA Configuration:  USART1 TX on PB6, RX on PB7 */
          GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
          GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
          GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
          GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
          GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
          GPIO_Init(GPIOB, &GPIO_InitStructure);

          /* Connect USART1 pins to AF2 */
          // TX = PB6
          GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_7);
          // RX = PB7
          GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_7);
          break;
      }
      
      USARTx_IRQn = USART1_IRQn;
    }

    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USARTx, &USART_InitStructure);

    //Configure interrupt
    //enable interrupt for USARTx
    USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);
    USART_Cmd(USARTx, ENABLE); // enable USARTx
    
    /* Enable USART Interrupt */
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = USARTx_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);    
    
}

inline void APP_USART_SendData(USART_TypeDef * USARTx, uint16_t data)
{
    while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
    USART_SendData(USARTx, data);  
}

int APP_USART_SendString(USART_TypeDef * USARTx, char * str)
{
  return APP_USART_SendString_Safe(USARTx, str, 0xff);
}
int APP_USART_SendStringEx(USART_TypeDef * USARTx, char * str, ...)
{
  return APP_USART_SendString_Safe(USARTx, str, 0xff);
}
int APP_USART_SendString_Safe(USART_TypeDef * USARTx, char * str, int max_size)
{
  int n = 0;

  while (str != 0 && n < max_size && str[n] != 0)
  {
    APP_USART_SendData(USARTx, str[n]);
    n++;
  }
  return n;
}

int _data_arrived = 0;
int _nibble_high  = 0;
int _nibble_low   = 0;
void APP_USART_Interrupt_Echo(USART_TypeDef * USARTx)
{
    if ( USART_GetITStatus(USARTx, USART_IT_RXNE) == SET)
    {
      USART_ClearITPendingBit(USARTx, USART_IT_RXNE);

      _data_arrived = USART_ReceiveData(USARTx);

      //echo
      APP_USART_SendData(USARTx, _data_arrived);
    }  
}
void APP_USART_Interrupt_EchoHex(USART_TypeDef * USARTx)
{
    if ( USART_GetITStatus(USARTx, USART_IT_RXNE) == SET)
    {
      USART_ClearITPendingBit(USARTx, USART_IT_RXNE);

      _data_arrived = USART_ReceiveData(USARTx);
      _nibble_high = Nibble2HexFromByte(_data_arrived, 4);
      _nibble_low  = Nibble2HexFromByte(_data_arrived, 0);
      
      //echo
      APP_USART_SendData(USARTx, _nibble_high);
      APP_USART_SendData(USARTx, _nibble_low);
    }  
}
#define MAX_BUFFER 128
char buffer_copy[MAX_BUFFER];
char buffer[MAX_BUFFER];
int buffer_pos = -1;
//void* (*usartcallbackfunc)(const char *); 

void APP_USART_Interrupt_StringRecognize(USART_TypeDef * USARTx) /* terminated with \0 \r \n */
{
  if ( USART_GetITStatus(USARTx, USART_IT_RXNE) == SET)
    {
      USART_ClearITPendingBit(USARTx, USART_IT_RXNE);

      if (buffer_pos == -1) //buffer empty condition
      {
        memset(buffer, 0, MAX_BUFFER);
        buffer_pos = 0;
      }
      _data_arrived = USART_ReceiveData(USARTx);
      if (_data_arrived == '\0' || _data_arrived == '\r' || _data_arrived == '\n')
      {
        memcpy(buffer_copy, buffer, MAX_BUFFER);
        //printf("%s\n", buffer);
        APP_USART_Cmd(USARTx, buffer_copy);
        buffer_pos = -1;
      }
      else
      {
        buffer[buffer_pos++] = _data_arrived;
      }
          
    }
}
inline int Nibble2HexFromByte(int value, int shift)
{
  return Nibble2Hex((value >> shift) & 0xF);
}
inline int Nibble2Hex(int nibble)
{
  return nibble < 0xA ? nibble + '0' : nibble - 0xA + 'A';
}

extern GPIO_TypeDef* GPIO_PORT[];
extern const uint16_t GPIO_PIN[];

void APP_USART_Cmd(USART_TypeDef * USARTx, char *lpszcommand)
{
  if (strncmp(lpszcommand, "?", 3) == 0)
  {
    APP_USART_SendString(USARTx, "Command: ?,LED,ECHO\r\n");
  }
  else if (strncmp(lpszcommand, "LED", 3) == 0)
  {
    char led = lpszcommand[4];
    if (led >= '3' && led <= '9')
    {
      Led_TypeDef l = (Led_TypeDef)(led - '3');
      if (lpszcommand[5] == 0)
      {
        //get command
        char response[] = "Led X is O    \0";
        response[4] = led;
        if (GPIO_ReadInputDataBit(GPIO_PORT[l], GPIO_PIN[l]))
        {
          response[10] = 'N';
        }
        else
        {
          response[10] = 'F';
          response[11] = 'F';
        }
        APP_USART_SendString(USARTx, response);
      }
      else
      {
        //set command
        char * param1 = &lpszcommand[6];
        if (strncmp(param1, "ON", 2) == 0 || lpszcommand[6] == '1')
        {
          STM_EVAL_LEDOn(l);
        }
        else if (strncmp(param1, "OFF", 3) == 0 || lpszcommand[6] == '0')
        {
          STM_EVAL_LEDOff(l);
        }
        else if (strncmp(param1, "TOGGLE", 5) == 0 || lpszcommand[6] == 'X')
        {
          STM_EVAL_LEDToggle(l);
        }
      }
    }
    else
    {
      APP_USART_SendString(USARTx, "Invalid led");
    }
  }
  else if (strncmp(lpszcommand, "ECHO", 3) == 0)
  {
    if (lpszcommand[4] != 0)
    {
      APP_USART_SendString(USARTx, &lpszcommand[5]);
    }
    else
    {
      APP_USART_SendString(USARTx, "No param");
    }
  }
  APP_USART_SendString(USARTx, "\r\n");
}