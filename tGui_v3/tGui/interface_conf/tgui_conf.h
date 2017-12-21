#ifndef _TGUICONF_H_
#define _WINCLASS_H_ 


#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
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


//#define RGB_565
//#define RGB_888
//#define RGB_1555
//#define RGB_8888


//基本LCD	
#define GUI_COLORMODE		RGB_888
#define GUI_PIXELSIZE		3          		 //每个像素3字节
#define GUI_BUFADDR 	0xD0000 //lcd存储基地址 LCD_FRAME_BUFFER
#define GUI_BUFSIZE 	BUFFER_OFFSET
#define GUI_WIDTH			LCD_PIXEL_WIDTH
#define GUI_HIGH			LCD_PIXEL_HEIGHT




void guiGetPrePoint(int32_t* x,int32_t* y);
void guiTouchUp(int32_t xid,int32_t yid);
void guiTouchDown(int32_t pre_x,int32_t pre_y,int32_t x,int32_t y);
int8_t getState(void);
int32_t getTouchX(void);
int32_t getTouchY(void);
#endif //!  _TGUICONF_H_ 
