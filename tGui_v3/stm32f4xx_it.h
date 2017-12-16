#ifndef _HANDLER_H_
#define _HANDLER_H_

#include "stm32f4xx_conf.h"
#include "led/led_conf.h"
#include "usart/usart_conf.h"
#include "touch/touch_i2c.h"



extern int TimeCount;
extern int BufMaxNum;
extern int USART1_Buf[];

extern void GTP_TouchProcess(void);

void SysTick_Handler();
void USART1_IRQHandler();
void EXTI0_IRQHandler();
void EXTI15_10_IRQHandler();
void ADC_IRQHandler();

#endif // !_INTERRUPTHANDLER_H_


