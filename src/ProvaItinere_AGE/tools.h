#ifndef __TOOLS_H__
#define __TOOLS_H__

#include "main.h"

#define MAX_BUFFER 300
#define PKT_START 0x2E

void APP_USART_Init(USART_TypeDef *, uint8_t, uint32_t);
void APP_USART_SendData(USART_TypeDef *, uint16_t);
int APP_USART_SendString(USART_TypeDef * , char *);
int APP_USART_SendStringEx(USART_TypeDef *, char *, ...);
int APP_USART_SendString_Safe(USART_TypeDef *, char *, int);
void APP_USART_Interrupt_Echo(USART_TypeDef *);
void APP_USART_Interrupt_EchoHex(USART_TypeDef *);
void APP_USART_Interrupt_StringRecognize(USART_TypeDef *);
void APP_USART_Cmd(USART_TypeDef  *, char *);

void APP_USART_Interrupt_PacketRecognize(USART_TypeDef *);

inline int Nibble2HexFromByte(int, int);
inline int Nibble2Hex(int);

//flash
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;
#define FLASH_PAGE_SIZE         ((uint32_t)0x00000800)   /* FLASH Page Size */
#define FLASH_USER_START_ADDR   ((uint32_t)0x08006000)   /* Start @ of user Flash area */
#define FLASH_USER_END_ADDR     ((uint32_t)0x08007000)   /* End @ of user Flash area */

void APP_FLASH_Write(char * pbuffer, uint8_t size);
void APP_FLASH_Read(char * pbuffer, uint8_t size);
void APP_FLASH_Erase(void);
#endif