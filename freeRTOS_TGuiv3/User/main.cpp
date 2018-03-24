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
//memcpy 最好是字传输  速度最快

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
	gui_dma2d_memset((uint32_t* )GUI_FG_BUFADDR,GUI_WIDTH,0xFFFFFFFF,0 ,0,GUI_WIDTH,GUI_HIGH);
	wifi_close();
	
	//每个函数都要用while结尾
	xTaskCreate( task0_temp, "gui_temp", 1000, NULL, 1, NULL );
	xTaskCreate( task1_led, "led_flash", configMINIMAL_STACK_SIZE, NULL, 2, NULL );
	xTaskCreate( task2_tgui, "TGui",16318, NULL,2, NULL );
	xTaskCreate( task3_driver, "driver", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
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

//   unsigned int error;
//   //unsigned char* 
//   u8* image;
//   unsigned int width = 0;
//   unsigned int height = 0;
// 	tim6_count = 0;
//   error = lodepng_decode32_file(&image, &width, &height, "1:/Picture/0.png");
//   //error = bmp_decode_file(&image, &width,&height, "1:/PICTURE/1.bmp");				//解码JPG/JPEG	
//   if(error) 
// 		printf("error %u: %s\n", error, lodepng_error_text(error));

// 	uint32 * des_addr = (uint32 *)GUI_FG_BUFADDR ;
// 	//uint32 * src_addr = (uint32 *)(image);

// 	u32 color_tmp;
// 	u32 offset;
// 	u16 i,j;
// 	uint32 a;
// 	for(i=0;i<height;i++)
// 	{
// 		for(j=0;j<width;j++)
// 		{ 
// 			offset = (i * width  + j) * 4;
// 			a = image[offset + 3]  ;
// 			color_tmp |= ((image[offset]  * a + 0xFF * (0xff - a)) >> 8) << 16;
// 			color_tmp |= ((image[offset + 1] * a + 0xFF * (0xff - a)) >> 8) << 8;
// 			color_tmp |= ((image[offset + 2]* a + 0xFF * (0xff - a)) >> 8);
// 			color_tmp |= (image[offset + 3] << 24);

// 			gui_dma2d_memset((uint32_t* )des_addr,GUI_WIDTH, color_tmp ,  j ,  i , 1 , 1);
// 			color_tmp = 0;
// 		}
// 	}

// 	// for(int i = 0;i < height;  i++)
// 	// {
// 	// 	//memcpy 模式
// 	// 	memcpy(des_addr,src_addr,width * GUI_PIXELSIZE);
// 	// 	//dma 模式
// 	// 	//--------------------------
// 	// 	src_addr += width;
// 	// 	des_addr += GUI_WIDTH;
// 	// }


// 	printf("end_tim: %d \n",tim6_count);
//   	free(image);

// 	piclib_init((uint8 *)GUI_FG_BUFADDR,GUI_WIDTH,GUI_HIGH);
// 	tim6_count = 0;
// 	ai_load_picfile("1:/PICTURE/2.jpg",0,0,GUI_WIDTH,GUI_HIGH,1);//显示图片   
// 	printf("end_tim: %d \n",tim6_count);
	
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
	//memcpy((uint8_t*)des_buf,buf,buf_size*4); //源地址为字地址，目标地址为字地址，搬运数量也为字的倍数 速度最快
	TGuiRun();	//tGui function
	while(1);
}

static void task3_driver(void *pvParameters)
{
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

