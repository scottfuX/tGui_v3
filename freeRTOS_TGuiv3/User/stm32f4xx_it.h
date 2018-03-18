#ifndef _HANDLER_H_
#define _HANDLER_H_

#include "stm32f4xx_conf.h"
#include "led/led_conf.h"
#include "usart/usart_conf.h"
#include "touch/touch_i2c.h"

#ifdef __cplusplus
 extern "C" {
#endif 
	 
void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

extern void GTP_TouchProcess(void);

//void SysTick_Handler(void);
void USART1_IRQHandler(void);
void EXTI0_IRQHandler(void);
void EXTI15_10_IRQHandler(void);
void ADC_IRQHandler(void);
	 
extern uint32_t tim6_count ;

#ifdef __cplusplus
}
#endif


#endif // !_INTERRUPTHANDLER_H_


