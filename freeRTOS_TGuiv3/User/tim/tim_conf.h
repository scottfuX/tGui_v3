#ifndef _TIMCONFIG_H_
#define _TIMCONFIG_H_

#include "stm32f4xx.h"

#define BASIC_TIM           		TIM6
#define BASIC_TIM_CLK       		RCC_APB1Periph_TIM6

#define BASIC_TIM_IRQn					TIM6_DAC_IRQn


void TIM_Basic_Config(void);



#endif //！_TIMCONFIG_H_

