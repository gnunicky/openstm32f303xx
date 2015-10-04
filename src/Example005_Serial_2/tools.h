#ifndef __TOOLS_H__
#define __TOOLS_H__

void APP_USART_Init(USART_TypeDef *, uint8_t);
void APP_USART_SendData(USART_TypeDef *, uint16_t);
int APP_USART_SendString(USART_TypeDef * , char *);
int APP_USART_SendStringEx(USART_TypeDef *, char *, ...);
int APP_USART_SendString_Safe(USART_TypeDef *, char *, int);
void APP_USART_Interrupt_Echo(USART_TypeDef *);
void APP_USART_Interrupt_EchoHex(USART_TypeDef *);
void APP_USART_Interrupt_StringRecognize(USART_TypeDef *);
void APP_USART_Cmd(USART_TypeDef  *, char *);
inline int Nibble2HexFromByte(int, int);
inline int Nibble2Hex(int);

#endif