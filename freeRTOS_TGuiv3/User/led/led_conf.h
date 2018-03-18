#ifndef _LEDCONFIG_H_
#define _LEDCONFIG_H_
#include "stm32f4xx_conf.h"

	void LED_RED_Config(void);
	void LED_GREEN_Config(void);
	void LED_BLUE_Config(void);

	void LED_RED_ON(void);
	void LED_RED_OFF(void);
	void LED_RED_Toggle(void);
	
	void LED_GREEN_ON(void);
	void LED_GREEN_OFF(void);
	void LED_GREEN_Toggle(void);

	void LED_BLUE_ON(void);
	void LED_BLUE_OFF(void);
	void LED_BLUE_Toggle(void);
	

#endif // !_LEDCONFIG_H_

