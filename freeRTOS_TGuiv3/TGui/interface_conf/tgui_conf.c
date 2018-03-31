#include "interface_conf/tgui_conf.h"

//id 数值 设置其实ID
volatile int32_t win_id = 0;
volatile int32_t TouchX_pre = -1;
volatile int32_t TouchY_pre = -1;
volatile int32_t TouchX = -1;
volatile int32_t TouchY = -1;
volatile int8_t state = 0;



#if GUI_SET_DMA2D
void gui_set_rect(uint32_t* buf_addr,uint32_t buf_width,uint32_t color,uint32_t xpos,uint32_t ypos,uint32_t width,uint32_t height)
{//DMA2D MODE ---> DMA2D CONFIG HERE
  DMA2D_InitTypeDef      DMA2D_InitStruct;
  uint32_t Xaddress = 0; 
  uint16_t Alpha_Value = 0xff,Red_Value = 0, Green_Value = 0, Blue_Value = 0;
 
#if defined   ARGB_8888	
	Alpha_Value = (0xFF000000 & color)>>24;
	Red_Value = (0x00FF0000 & color)>>16 ;
	Green_Value = (0x0000FF00 & color)>>8;
	Blue_Value = 0x000000FF & color;
#elif defined ARGB_1555 
	Alpha_Value = (	0x00008000 & color)>>15;
	Red_Value = (	0x00007C00 & color)>>10 ;
	Green_Value = (	0x000003E0 & color)>>5;
	Blue_Value = 	0x0000001F & color;
#elif defined RGB_888  
	Alpha_Value = 0xFF;
	Red_Value = (0x00FF0000 & color)>>16 ;
	Green_Value = (0x0000FF00 & color)>>8;
	Blue_Value = 0x000000FF & color;
#elif defined RGB_565
	Alpha_Value = 0xFF;
	Red_Value = (	0x0000F800 & color)>>11;
	Green_Value = (	0x000007E0 & color)>>5;
	Blue_Value = 	0x0000001F & color;
#endif
  
  Xaddress = (uint32_t)buf_addr + GUI_PIXELSIZE*(buf_width * ypos + xpos);
  
  /* configure DMA2D */
  DMA2D_DeInit();
  DMA2D_InitStruct.DMA2D_Mode = DMA2D_R2M;       
#if defined   ARGB_8888
	DMA2D_InitStruct.DMA2D_CMode = DMA2D_ARGB8888;  
#elif defined ARGB_1555 
	DMA2D_InitStruct.DMA2D_CMode = DMA2D_ARGB1555;
#elif defined RGB_888  
	DMA2D_InitStruct.DMA2D_CMode = DMA2D_RGB888;
#elif defined RGB_565
	DMA2D_InitStruct.DMA2D_CMode = DMA2D_ARGB1555;
#endif     
  DMA2D_InitStruct.DMA2D_OutputGreen = Green_Value;      
  DMA2D_InitStruct.DMA2D_OutputBlue = Blue_Value;     
  DMA2D_InitStruct.DMA2D_OutputRed = Red_Value;                
  DMA2D_InitStruct.DMA2D_OutputAlpha = 0xff;//Alpha_Value; //---------------------------------------这个是要改回来的-----------------                 
  DMA2D_InitStruct.DMA2D_OutputMemoryAdd = Xaddress;                
  DMA2D_InitStruct.DMA2D_OutputOffset = (buf_width - width);                
  DMA2D_InitStruct.DMA2D_NumberOfLine = height;            
  DMA2D_InitStruct.DMA2D_PixelPerLine = width;
  DMA2D_Init(&DMA2D_InitStruct); 
  
  /* Start Transfer */ 
  DMA2D_StartTransfer();
  
  /* Wait for CTC Flag activation */
  while(DMA2D_GetFlagStatus(DMA2D_FLAG_TC) == RESET)
  {
  } 
}
#else
void gui_set_rect(uint32_t* buf_addr,uint32_t buf_width,uint32_t color,uint32_t xpos,uint32_t ypos,uint32_t width,uint32_t height)
{//NORMAL MODE ---> NORMAL CONFIG HERE
	uint32_t* addr = (uint32_t*)((uint32_t)buf_addr + GUI_PIXELSIZE*(buf_width * ypos + xpos));
	for(int i=0;i< height;i++)
	{
		for(int j=0;j< width;j++)
		{
			*addr = color;
			addr++;
		}
		addr += buf_width - width;
	}
}
#endif //!GUI_SET_DMA2D




#if GUI_CPY_DMA

//memcpy 最好是字传输  速度最快
void* gui_memcpy(void *dest, void *src, unsigned int count)
{//dma 方式速度很慢 目前有问题
	DMA_InitTypeDef  DMA_InitStructure;
	__IO uint32_t    Timeout = 10000;//TIMEOUT_MAX;  

	/* 使能DMA时钟 */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	/* 复位初始化DMA数据流 */
	DMA_DeInit(DMA2_Stream0);
	/* 确保DMA数据流复位完成 */
	while (DMA_GetCmdStatus(DMA2_Stream0) != DISABLE)
	{
	}

	DMA_InitStructure.DMA_Channel = DMA_Channel_0;  /* DMA数据流通道选择 */
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)src; /* 源数据地址 */
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)dest; /* 目标地址 */
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToMemory;  /* 存储器到存储器模式 */
	DMA_InitStructure.DMA_BufferSize = (uint32_t)count; /* 数据数目 */
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable; /* 使能自动递增功能 */
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; /* 使能自动递增功能 */
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word; /* 源数据是字大小(32位) */
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;  /* 目标数据也是字大小(32位) */
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal; /* 一次传输模式，存储器到存储器模式不能使用循环传输 */
	DMA_InitStructure.DMA_Priority = DMA_Priority_High; /* DMA数据流优先级为高 */
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;     /* 禁用FIFO模式 */
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;/* 单次模式 */
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;/* 单次模式 */
	DMA_Init(DMA2_Stream0, &DMA_InitStructure);/* 完成DMA数据流参数配置 */
	DMA_ClearFlag(DMA2_Stream0,DMA_FLAG_TCIF0);  /* 清除DMA数据流传输完成标志位 */
	DMA_Cmd(DMA2_Stream0, ENABLE);/* 使能DMA数据流，开始DMA数据传输 */

	/* 检测DMA数据流是否有效并带有超时检测功能 */
	while ((DMA_GetCmdStatus(DMA2_Stream0) != ENABLE) && (Timeout-- > 0))
	{
	}

	if (Timeout == 0)/* 判断是否超时 */
	{
		return NULL;
	} 

	while(DMA_GetFlagStatus(DMA2_Stream0,DMA_FLAG_TCIF0) == DISABLE); //一直等待传输好---> 也可以不等待以后再优化
	return dest;
}

#else
void* gui_memcpy(void *dest, void *src, unsigned int count)
{//memcpy
	return memcpy(dest,src,count);
}
#endif //!GUI_CPY_DMA




void guiGetPrePoint(int32_t* x,int32_t* y)
{
	(*x) = TouchX_pre;
	(*y) = TouchY_pre;
}

void guiTouchDown(int32_t pre_x,int32_t pre_y,int32_t x,int32_t y)
{
	TouchX_pre = pre_x;
	TouchY_pre = pre_y;
	TouchX = x;
	TouchY = y;
	state = 1;
}

void guiTouchUp(int32_t xid,int32_t yid)
{
	state = 0;
}

int8_t getState(void)
{
	return state;
}

int32_t getTouchX(void)
{
	return TouchX;
}
int32_t getTouchY(void)
{
	return TouchY;
}


