#include "interface_conf/tgui_conf.h"

//id 数值 设置其实ID
volatile int32_t win_id = 0;
volatile int32_t TouchX_pre = -1;
volatile int32_t TouchY_pre = -1;
volatile int32_t TouchX = -1;
volatile int32_t TouchY = -1;
volatile int8_t state = 0;

#if GUI_SET_DMA2D
void gui_dma2d_memset(uint32_t* buf_addr,uint32_t buf_width,uint32_t color,uint32_t xpos,uint32_t ypos,uint32_t width,uint32_t height)
{

// uint32_t* addr = (uint32_t*)((uint32_t)buf_addr + GUI_PIXELSIZE*(buf_width * ypos + xpos));
// printf("addr %x\n",addr);
// for(int i=0;i< height;i++)
// {
// 	for(int j=0;j< width;j++)



// 	{
// 		*addr = color;
// 		addr++;
// 	}
// 	addr += buf_width - width;
// }

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
  DMA2D_InitStruct.DMA2D_OutputAlpha = Alpha_Value;                  
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
void gui_memset(uint32_t* addr,uint32_t color,int32_t width,int32_t height)
{

}
#endif

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


