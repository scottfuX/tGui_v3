#include "TObject/TBuffer.h"

TBuffer::TBuffer(uint8* pre_addr,uint32 pre_w,uint32 w,uint32 h)
{
    buf = NULL;
    //buf = (uint8*) malloc (w * h * GUI_PIXELSIZE);
	bufW = w;
	bufH = h;
	if(pre_addr)
	{	//搬运父亲背景 至 TBuffer
		buf = new uint8[w * h * GUI_PIXELSIZE];
		obPareBack(pre_addr,pre_w);
	}
	else
	{
		buf = new uint8[w * h * GUI_PIXELSIZE];
		gui_set_rect((uint32_t* )buf,w,0xFFFFFFFF,0 ,0,w,h);
	}
}

TBuffer::~TBuffer()
{
    if(buf)
        delete[] (buf);
		//free(buf);
}


//把 TBuffer 的 srcRect 区域 搬运至 显存    
//注意： srcRect中的 x,y坐标均为绝对坐标
//搬运速度有待提升
/*
|---------------|			|---------------|
|				|			|	showMem	    |
|	|-------|	| 			|	|-------|	|
|	|srcRect|---+-transform-+-->| 		|	|
|	|-------|	|			|	|-------|	|
|	 TBuffer	|			|				|
|---------------|			|---------------|
*/
void TBuffer::transform(int32 x,int32 y,TRect* srcRect)
{//输送一部分内容到显存
		uint32 des_addr = (GUI_FG_BUFADDR + (srcRect->top() * GUI_WIDTH +  srcRect->left()) * GUI_PIXELSIZE);
		uint32 x_offset = srcRect->left() - x; //算出 剪切区域x 相对 TBuffer 偏移
		uint32 y_offset = srcRect->top() - y;	 //算出 剪切区域y 相对 TBuffer 偏移
		uint32 src_addr = (uint32)getBufAddr() + (y_offset * bufW + x_offset ) * GUI_PIXELSIZE;
		for(int i = 0;i < srcRect->height();  i++)
		{
			gui_memcpy((uint8*)des_addr,(uint8*)src_addr,srcRect->width() * GUI_PIXELSIZE);
			src_addr += bufW * GUI_PIXELSIZE;
			des_addr += GUI_WIDTH * GUI_PIXELSIZE;
		}
}

void TBuffer::obPareBack(uint8* pre_addr,uint32 pre_w)
{
	uint32 des_addr = (uint32)buf;
	uint32 src_addr = (uint32)pre_addr;
	for(int i = 0;i < bufH;  ++i)
	{
		gui_memcpy((uint8 *)des_addr,(uint8 *)src_addr,bufW * GUI_PIXELSIZE);
		src_addr += pre_w * GUI_PIXELSIZE;
		des_addr += bufW * GUI_PIXELSIZE;
	}
}

//若用宏定义 减少call 减少执行世界
uint32 TBuffer::readPoint(int32 x,int32 y)
{
	return *(uint32_t* )(((uint32)buf) + (y * bufW + x) * GUI_PIXELSIZE);
}

void TBuffer::writePoint(int32 x,int32 y,uint32 color)
{
	gui_set_rect((uint32_t*)buf,bufW,color,x , y ,1,1);
}






