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
#include "semphr.h"
#include "FreeRTOSConfig.h"
//>>>>>>>>>>-FreeRTOS->>>>>>>>>>>
#include "stm32f4xx_it.h"
#include "led/led_conf.h"
#include "usart/usart_conf.h"
#include "flash/flash_conf.h"
#include "sdio/sdio_sd_conf.h"
#include "fatfs/ff.h"
#include "tim/tim_conf.h"
#include "lcd/lcd_conf.h"
#include "touch/gt9xx.h"
#include "delay/delay_conf.h"
#include "test/lcdtest.h"
#include "test/lcdpalette.h"
#include "libraries/picture_lib/piclib.h"	
#include "libraries/exfuns_lib/exfuns.h"
#include "libraries/exfuns_lib/aux_data.h"
uint32_t tim6_count;

#ifdef __cplusplus
}
#endif
#include "libraries/picture_lib/lodepng.h"

	
#include "TGuiMain.h"
//0xD0400000 >> 480*320* X(类型的字节数 ARGB8888 -> 4 )  背景层
//0XD0577000 >> 480*320* X(类型的字节数 ARGB8888 -> 4 )  前景层
//有透明功能 --> 主要为前景背景层 前景层为覆盖 
//无透明层 可直接操控前景层即可


extern char src_dir[255];
extern char dst_dir[255];
static void wifi_close(void);

static void task0_temp(void *pvParameters);
static void task1_led(void *pvParameters);
static void task2_tgui(void *pvParameters);
static void task3_driver(void *pvParameters);


FATFS fs[2];					/* FatFs文件系统对象 */
DIR dj;         				/*目录搜索对象*/ 
FIL fnew;						/* 文件对象 */
FRESULT res;                	/* 文件操作结果 */
FILINFO fno;
UINT fnum;            			/* 文件成功读写数量 */
BYTE ReadBuffer[100]={0};        /* 读缓冲区 */
BYTE WriteBuffer[] =              /* 写缓冲区*/
"SD Card 测试实验 1234567890\r\n";       
char fpath[50];                  /* 保存当前扫描路径 */ 
char fpath1[50];  					 

SemaphoreHandle_t xMutex;
TTouchDirver* dirver;

int main()
{
	tim6_count = 0;
	LED_GREEN_Config();
	LED_BLUE_Config();
	LED_RED_Config();
	USART1Config();
	TIM_Basic_Config();
	GTP_Init_Panel();
	LCD_Init();
	//SDRAMConfig();  //进入main前，已经初始化了
	//FLASHConfig();
	gui_set_rect((uint32_t* )GUI_FG_BUFADDR,GUI_WIDTH,0xFFFFFFFF,0 ,0,GUI_WIDTH,GUI_HIGH);
	wifi_close();
	
	xMutex = xSemaphoreCreateMutex();//创建二元信号量
	//每个函数都要用while结尾
	if( xMutex == NULL )
	{
		printf("\r\n create mutex failed! \r\n");
		while(1);
	}
	dirver = new TTouchDirver(GUI_MULTTI_THREAD,30);
		
	//xTaskCreate( task0_temp, "gui_temp", 512, NULL,2, NULL );
	xTaskCreate( task1_led, "led_flash", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
	xTaskCreate( task2_tgui, "TGui",20480, NULL,2, NULL );
	xTaskCreate( task3_driver, "driver", 2048, NULL, 1, NULL );
	vTaskStartScheduler();	// 启动调度器，任务开始执行
	
	while(1);
}

static void task0_temp(void *pvParameters)
{
	if(f_mount(&fs[1],"1:",1) != FR_OK)//挂载 flash card
		printf("\r\nflash mount failed ...\r\n");
	if(f_mount(&fs[0],"0:",1) != FR_OK)//挂载 sd card
		printf("\r\nsd mount failed ...\r\n");
	res = copy_file_sd2flash(src_dir,dst_dir);
	if(res == FR_OK)
		printf("\r\n 所有数据已成功复制到FLASH！！！ \r\n");  
	else
		printf("\r\n 复制文件到FLASH失败(文件系统部分)，请复位重试！！ \r\n"); 

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
	if(f_mount(&fs[1],"1:",1) != FR_OK)//挂载 flash card
		printf("\r\nflash mount failed ...\r\n");
	if(f_mount(&fs[0],"0:",1) != FR_OK)//挂载 sd card
		printf("\r\nsd mount failed ...\r\n");
	TGuiRun();	//tGui function
	while(1);
}

static void task3_driver(void *pvParameters)
{
	
	dirver->run();
	while(1);
}


static void wifi_close(void)
{
	/*定义一个GPIO_InitTypeDef类型的结构体*/
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd ( RCC_AHB1Periph_GPIOG, ENABLE); 							   
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 
  GPIO_Init(GPIOG, &GPIO_InitStructure);	
  GPIO_ResetBits(GPIOG,GPIO_Pin_9);  //禁用WiFi模块

}

