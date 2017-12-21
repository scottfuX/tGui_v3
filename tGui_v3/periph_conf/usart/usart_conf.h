#ifndef _USARTCONFIG_H_
#define _USARTCONFIG_H_

#include "stm32f4xx_conf.h"
#include <stdio.h>
	

//int fputc(int ch, FILE *f);
//int fgetc(FILE  *f);

void USART1Config();
static void USART1_NVICConfig();

void USART1_TX(int*buf, int bufnum);
int USART1_RX();

void USART1_TXByte(uint8_t ch);
void USART1_TXString(char *str);
void USART1_TXHalfWord(uint16_t ch);

void out(const char *str);
void outInt(int x);
void USART_SendByte(USART_TypeDef * pUSARTx, uint8_t ch);
void USART_SendString(USART_TypeDef * pUSARTx, char *str);
void USART_SendHalfWord(USART_TypeDef * pUSARTx, uint16_t ch);


#endif // !_USARTCONFIG_H_

