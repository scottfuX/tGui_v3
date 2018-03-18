#ifdef __cplusplus
extern "C" {
#endif
	
#include <stdio.h>
#include <string.h>
#include "stm32f4xx_conf.h"
//>>>>>>>>>>-FreeRTOS->>>>>>>>>>>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "list.h"
#include "portable.h"
#include "FreeRTOSConfig.h"
#include "stm32f4xx_it.h"
#include "led/led_conf.h"
#include "usart/usart_conf.h"
#include "flash/flash_conf.h"
#include "fatfs/ff.h"
#include "tim/tim_conf.h"
#include "lcd/lcd_conf.h"
#include "touch/gt9xx.h"
#include "delay/delay_conf.h"
#include "test/fstest.h"
#include "test/lcdtest.h"
#include "test/lcdpalette.h"
	
uint32_t tim6_count;

#ifdef __cplusplus
}
#endif

	
#include "TGuiMain.h"
//0xD0400000 >> 480*320* X(类型的字节数 ARGB8888 -> 4 )  背景层
//0XD0577000 >> 480*320* X(类型的字节数 ARGB8888 -> 4 )  前景层
//有透明功能 --> 主要为前景背景层 前景层为覆盖 
//无透明层 可直接操控前景层即可
//memcpy 最好是字传输  速度最快


static void task0_temp(void *pvParameters);
static void task1_led(void *pvParameters);
static void task2_tgui(void *pvParameters);
static void task3_driver(void *pvParameters);


int main()
{
	tim6_count = 0;
	//SDRAMConfig();  //进入main前，已经初始化了
	LED_GREEN_Config();
	LED_BLUE_Config();
	LED_RED_Config();
	USART1Config();
	FLASHConfig();
	TIM_Basic_Config();
	GTP_Init_Panel();
	LCD_Init();
	
	//每个函数都要用while结尾
	xTaskCreate( task0_temp, "gui_temp", 1024, NULL, 1, NULL );
	xTaskCreate( task1_led, "led_flash", configMINIMAL_STACK_SIZE, NULL, 2, NULL );
	xTaskCreate( task2_tgui, "TGui",10000, NULL,2, NULL );
	xTaskCreate( task3_driver, "driver", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
	vTaskStartScheduler();	// 启动调度器，任务开始执行
	
	while(1);
	return 1;
}

static void task0_temp(void *pvParameters)
{
//	static uint32_t* des_buf = (uint32_t*)(GUI_FG_BUFADDR);
//	uint32_t* q;
//	uint32_t* p;
//	unsigned long len = 800*480*4;
//	uint32_t* buf =(uint32_t*)malloc(len); //set mem

//	tim6_count = 0;
//	memset(des_buf,255,800*480*4);//set background
//	printf("init_end_tim: %d \n",tim6_count);

//	tim6_count = 0;
//	//gui_dma2d_memset(buf,0xFF0000FF,800,480,800);
//	printf("dma1_end_tim: %d \n",tim6_count);

//	tim6_count = 0;
//	//gui_dma2d_memset(buf,0xFFFF0000,100,100,800);
//	printf("dma2_end_tim: %d \n",tim6_count);

//	tim6_count = 0;
//	p = buf;
//	q = des_buf;
//	for(int i =0;i < 480 ; i ++)
//	{
//		memcpy(q,p,(uint32_t)800*4);
//		p += 800;
//		q += 800;
//	}
//	printf("end_tim: %d \n",tim6_count);
	while(1);
}

static void task1_led(void *pvParameters)
{
	while(1)
	{
		LED_RED_Toggle();
		Delay(0xffffff);
	}
}

static void task2_tgui(void *pvParameters)
{
	//memcpy((uint8_t*)des_buf,buf,buf_size*4); //源地址为字地址，目标地址为字地址，搬运数量也为字的倍数 速度最快
	TGuiRun();	//tGui function
	while(1);
}

static void task3_driver(void *pvParameters)
{
	while(1);
}
