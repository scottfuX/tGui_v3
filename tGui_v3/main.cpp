#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <string.h>
#include "stm32f4xx_conf.h"
#include "led/led_conf.h"
#include "usart/usart_conf.h"
#include "flash/flash_conf.h"
#include "fatfs/ff.h"
#include "lcd/lcd_conf.h"
#include "touch/gt9xx.h"
#include "delay/delay_conf.h"
#include "test/fstest.h"
#include "test/lcdtest.h"
#include "test/lcdpalette.h"

#ifdef __cplusplus
}
#endif

#include "tGuiMain.h"

int USART1_Buf[5];
int BufMaxNum = 5;

//default FLASH 34K RAM 1332byte

int main()
{
	LED_GREEN_Config();
	LED_BLUE_Config();
	LED_RED_Config();
	DelayMSConfig();
	USART1Config();
	SDRAMConfig();
	FLASHConfig();
	GTP_Init_Panel();
	LCD_Init();
	LCD_Clear(WHITE);
	//LCDPalette();
	printf("234.");
	//tGui function
	tGuiRun();
	for (;;){
		printf("123.");
		LED_BLUE_Toggle();
		DelayHandler(1000);
	}
	return 0;
}