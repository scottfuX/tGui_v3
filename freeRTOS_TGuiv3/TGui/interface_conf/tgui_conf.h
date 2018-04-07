#ifndef _TGUICONF_H_
#define _WINCLASS_H_ 


#ifdef __cplusplus
extern "C" {
#endif

//>>>>>>>>>>-FreeRTOS->>>>>>>>>>>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "list.h"
#include "portable.h"
#include "semphr.h"
#include "FreeRTOSConfig.h"
//>>>>>>>>>>-FreeRTOS->>>>>>>>>>>

#include <stdio.h>
#include "stm32f4xx_conf.h"
#include "led/led_conf.h"
#include "usart/usart_conf.h"
#include "flash/flash_conf.h"
#include "fatfs/ff.h"
#include "lcd/lcd_conf.h"
#include "touch/gt9xx.h"
#include "delay/delay_conf.h"
#include "test/lcdtest.h"
#include "test/lcdpalette.h"

#ifdef __cplusplus
}
#endif


//#define RGB_565
//#define RGB_888
//#define ARGB_1555
#define ARGB_8888


#define GUI_DELAY_MS(x)        vTaskDelay(x);       //延时函数

//基本LCD	
#define GUI_COLORMODE		ARGB_8888
#define GUI_PIXELSIZE		4          		        //每个像素4字节
#define GUI_BG_BUFADDR      (uint32_t)(0XD0400000)  //background
#define GUI_FG_BUFADDR      (uint32_t)(0XD0577000)  //frontground
#define GUI_BUFADDR 	    LCD_FRAME_BUFFER //lcd存储基地址 LCD_FRAME_BUFFER
#define GUI_BUFSIZE 	    BUFFER_OFFSET
#define GUI_WIDTH			LCD_PIXEL_WIDTH
#define GUI_HIGH			LCD_PIXEL_HEIGHT

#define GUI_SET_DMA2D           1                   //是否使用DMA2D进行绘图
#define GUI_CPY_DMA             0                   //是否使用DMA进行拷贝内存


#define TFON_FILE           "0:/GBK16HEI.FON"
#define TFON_WIDTH          16
#define TFON_HEIGHT         16
#define TFON_TYPE           T_GBK
#define TFON_ASCII          Font16x16   //Font32x32 Font24x24 Font16x16 Font12x12


extern SemaphoreHandle_t xMutex;;
//信号量 TAKE>用于获取二元信号量 GIVE>用于释放二元信号量
void GUI_MUTEX_TAKE(); 
void GUI_MUTEX_GIVE(); 



void gui_set_rect(uint32_t* buf_addr,uint32_t buf_width,uint32_t color,uint32_t xpos,uint32_t ypos,uint32_t width,uint32_t height);
void* gui_memcpy(void *dest, void *src, unsigned int count);



//Touch 获取数据函数
void guiGetPrePoint(int32_t* x,int32_t* y);
void guiTouchUp(int32_t xid,int32_t yid);
void guiTouchDown(int32_t pre_x,int32_t pre_y,int32_t x,int32_t y);
int8_t getState(void);
int32_t getTouchX(void);
int32_t getTouchY(void);

#endif //!  _TGUICONF_H_ 
