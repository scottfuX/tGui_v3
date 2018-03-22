#include "stm32f4xx_it.h"



/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{}
	
	
//在 portable中port.c 与这些重复  这里需要注释
//SVC_Handler、PendSV_Handler、SysTick_Handler
/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
//void SVC_Handler(void)
//{}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
//void PendSV_Handler(void)
//{}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
//void SysTick_Handler(void)
//{}

void USART1_IRQHandler()
{
	
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

//TIM6_DAC_IRQHandler 
//中断函数
void TIM6_DAC_IRQHandler(void) 
{
	if ( TIM_GetITStatus( TIM6, TIM_IT_Update) != RESET ) 
	{	
		//LED_BLUE_Toggle();
		tim6_delay_count--;
    tim6_count++;
		TIM_ClearITPendingBit(TIM6 , TIM_IT_Update);  		 
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
