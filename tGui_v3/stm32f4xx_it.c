#include "stm32f4xx_it.h"

int USART1BufCount = 0;

void SysTick_Handler()                
{
	TimeCount--;
}

void USART1_IRQHandler()
{
	//主要用于接收数据
	//单缓冲--双缓冲
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != 0)
	{
		USART1_Buf[USART1BufCount++] = USART1_RX();
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		if (USART1BufCount == BufMaxNum)
		{
			USART1BufCount = 0;
			USART1_TX(USART1_Buf, BufMaxNum);
		}
	}	
}

void EXTI15_10_IRQHandler()
{
	if (EXTI_GetITStatus(GTP_INT_EXTI_LINE) != RESET) //确保是否产生了EXTI Line中断
	{
		LED_GREEN_Toggle();
		GTP_TouchProcess();    
		EXTI_ClearITPendingBit(GTP_INT_EXTI_LINE);     //清除中断标志位
	}
}

//void NMI_Handler()                    __attribute__((weak, alias("Default_Handler")));
//void HardFault_Handler()              __attribute__((weak, alias("Default_Handler")));
//void MemManage_Handler()              __attribute__((weak, alias("Default_Handler")));
//void BusFault_Handler()               __attribute__((weak, alias("Default_Handler")));
//void UsageFault_Handler()             __attribute__((weak, alias("Default_Handler")));
//void SVC_Handler()                    __attribute__((weak, alias("Default_Handler")));
//void DebugMon_Handler()               __attribute__((weak, alias("Default_Handler")));
//void PendSV_Handler()                 __attribute__((weak, alias("Default_Handler")));

//void WWDG_IRQHandler()                __attribute__((weak, alias("Default_Handler")));
//void PVD_IRQHandler()                 __attribute__((weak, alias("Default_Handler")));
//void TAMP_STAMP_IRQHandler()          __attribute__((weak, alias("Default_Handler")));
//void RTC_WKUP_IRQHandler()            __attribute__((weak, alias("Default_Handler")));
//void FLASH_IRQHandler()               __attribute__((weak, alias("Default_Handler")));
//void RCC_IRQHandler()                 __attribute__((weak, alias("Default_Handler")));

//void EXTI0_IRQHandler()
//void EXTI1_IRQHandler()               __attribute__((weak, alias("Default_Handler")));
//void EXTI2_IRQHandler()               __attribute__((weak, alias("Default_Handler")));
//void EXTI3_IRQHandler()               __attribute__((weak, alias("Default_Handler")));

//void DMA1_Stream0_IRQHandler()        __attribute__((weak, alias("Default_Handler")));
//void DMA1_Stream1_IRQHandler()        __attribute__((weak, alias("Default_Handler")));
//void DMA1_Stream2_IRQHandler()        __attribute__((weak, alias("Default_Handler")));
//void DMA1_Stream3_IRQHandler()        __attribute__((weak, alias("Default_Handler")));
//void DMA1_Stream4_IRQHandler()        __attribute__((weak, alias("Default_Handler")));
//void DMA1_Stream5_IRQHandler()        __attribute__((weak, alias("Default_Handler")));
//void DMA1_Stream6_IRQHandler()        __attribute__((weak, alias("Default_Handler")));
//void ADC_IRQHandler()               
//void CAN1_TX_IRQHandler()             __attribute__((weak, alias("Default_Handler")));
//void CAN1_RX0_IRQHandler()            __attribute__((weak, alias("Default_Handler")));
//void CAN1_RX1_IRQHandler()            __attribute__((weak, alias("Default_Handler")));
//void CAN1_SCE_IRQHandler()            __attribute__((weak, alias("Default_Handler")));
//void EXTI9_5_IRQHandler()             __attribute__((weak, alias("Default_Handler")));
//void TIM1_BRK_TIM9_IRQHandler()       __attribute__((weak, alias("Default_Handler")));
//void TIM1_UP_TIM10_IRQHandler()       __attribute__((weak, alias("Default_Handler")));
//void TIM1_TRG_COM_TIM11_IRQHandler()  __attribute__((weak, alias("Default_Handler")));
//void TIM1_CC_IRQHandler()             __attribute__((weak, alias("Default_Handler")));
//void TIM2_IRQHandler()                __attribute__((weak, alias("Default_Handler")));
//void TIM3_IRQHandler()                __attribute__((weak, alias("Default_Handler")));
//void TIM4_IRQHandler()                __attribute__((weak, alias("Default_Handler")));
//void I2C1_EV_IRQHandler()             __attribute__((weak, alias("Default_Handler")));
//void I2C1_ER_IRQHandler()             __attribute__((weak, alias("Default_Handler")));
//void I2C2_EV_IRQHandler()             __attribute__((weak, alias("Default_Handler")));
//void I2C2_ER_IRQHandler()             __attribute__((weak, alias("Default_Handler")));
//void SPI1_IRQHandler()                __attribute__((weak, alias("Default_Handler")));
//void SPI2_IRQHandler()                __attribute__((weak, alias("Default_Handler")));

		
//void USART2_IRQHandler()              __attribute__((weak, alias("Default_Handler")));
//void USART3_IRQHandler()              __attribute__((weak, alias("Default_Handler")));
//void EXTI15_10_IRQHandler()           __attribute__((weak, alias("Default_Handler")));
//void RTC_Alarm_IRQHandler()           __attribute__((weak, alias("Default_Handler")));
//void OTG_FS_WKUP_IRQHandler()         __attribute__((weak, alias("Default_Handler")));
//void TIM8_BRK_TIM12_IRQHandler()      __attribute__((weak, alias("Default_Handler")));
//void TIM8_UP_TIM13_IRQHandler()       __attribute__((weak, alias("Default_Handler")));
//void TIM8_TRG_COM_TIM14_IRQHandler()  __attribute__((weak, alias("Default_Handler")));
//void TIM8_CC_IRQHandler()             __attribute__((weak, alias("Default_Handler")));
//void DMA1_Stream7_IRQHandler()        __attribute__((weak, alias("Default_Handler")));
//void FMC_IRQHandler()                 __attribute__((weak, alias("Default_Handler")));
//void SDIO_IRQHandler()                __attribute__((weak, alias("Default_Handler")));
//void TIM5_IRQHandler()                __attribute__((weak, alias("Default_Handler")));
//void SPI3_IRQHandler()                __attribute__((weak, alias("Default_Handler")));
//void UART4_IRQHandler()               __attribute__((weak, alias("Default_Handler")));
//void UART5_IRQHandler()               __attribute__((weak, alias("Default_Handler")));
//void TIM6_DAC_IRQHandler()            __attribute__((weak, alias("Default_Handler")));
//void TIM7_IRQHandler()                __attribute__((weak, alias("Default_Handler")));
//void DMA2_Stream0_IRQHandler()        __attribute__((weak, alias("Default_Handler")));
//void DMA2_Stream1_IRQHandler()        __attribute__((weak, alias("Default_Handler")));
//void DMA2_Stream2_IRQHandler()        __attribute__((weak, alias("Default_Handler")));
//void DMA2_Stream3_IRQHandler()        __attribute__((weak, alias("Default_Handler")));
//void DMA2_Stream4_IRQHandler()        __attribute__((weak, alias("Default_Handler")));
//void ETH_IRQHandler()                 __attribute__((weak, alias("Default_Handler")));
//void ETH_WKUP_IRQHandler()            __attribute__((weak, alias("Default_Handler")));
//void CAN2_TX_IRQHandler()             __attribute__((weak, alias("Default_Handler")));
//void CAN2_RX0_IRQHandler()            __attribute__((weak, alias("Default_Handler")));
//void CAN2_RX1_IRQHandler()            __attribute__((weak, alias("Default_Handler")));
//void CAN2_SCE_IRQHandler()            __attribute__((weak, alias("Default_Handler")));
//void OTG_FS_IRQHandler()              __attribute__((weak, alias("Default_Handler")));
//void DMA2_Stream5_IRQHandler()        __attribute__((weak, alias("Default_Handler")));
//void DMA2_Stream6_IRQHandler()        __attribute__((weak, alias("Default_Handler")));
//void DMA2_Stream7_IRQHandler()        __attribute__((weak, alias("Default_Handler")));
//void USART6_IRQHandler()              __attribute__((weak, alias("Default_Handler")));
//void I2C3_EV_IRQHandler()             __attribute__((weak, alias("Default_Handler")));
//void I2C3_ER_IRQHandler()             __attribute__((weak, alias("Default_Handler")));
//void OTG_HS_EP1_OUT_IRQHandler()      __attribute__((weak, alias("Default_Handler")));
//void OTG_HS_EP1_IN_IRQHandler()       __attribute__((weak, alias("Default_Handler")));
//void OTG_HS_WKUP_IRQHandler()         __attribute__((weak, alias("Default_Handler")));
//void OTG_HS_IRQHandler()              __attribute__((weak, alias("Default_Handler")));
//void DCMI_IRQHandler()                __attribute__((weak, alias("Default_Handler")));
//void HASH_RNG_IRQHandler()            __attribute__((weak, alias("Default_Handler")));
//void FPU_IRQHandler()                 __attribute__((weak, alias("Default_Handler")));
//void UART7_IRQHandler()               __attribute__((weak, alias("Default_Handler")));
//void UART8_IRQHandler()               __attribute__((weak, alias("Default_Handler")));
//void SPI4_IRQHandler()                __attribute__((weak, alias("Default_Handler")));
//void SPI5_IRQHandler()                __attribute__((weak, alias("Default_Handler")));
//void SPI6_IRQHandler()                __attribute__((weak, alias("Default_Handler")));
//void SAI1_IRQHandler()                __attribute__((weak, alias("Default_Handler")));
//void LTDC_IRQHandler()                __attribute__((weak, alias("Default_Handler")));
//void LTDC_ER_IRQHandler()             __attribute__((weak, alias("Default_Handler")));
//void DMA2D_IRQHandler()               __attribute__((weak, alias("Default_Handler")));
