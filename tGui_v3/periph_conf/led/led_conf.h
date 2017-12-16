#ifndef _LEDCONFIG_H_
#define _LEDCONFIG_H_
#include "stm32f4xx_conf.h"

	void LED_RED_Config();
	void LED_GREEN_Config();
	void LED_BLUE_Config();

	void LED_RED_ON();
	void LED_RED_OFF();
	void LED_RED_Toggle();
	
	void LED_GREEN_ON();
	void LED_GREEN_OFF();
	void LED_GREEN_Toggle();

	void LED_BLUE_ON();
	void LED_BLUE_OFF();
	void LED_BLUE_Toggle();
	

#endif // !_LEDCONFIG_H_

