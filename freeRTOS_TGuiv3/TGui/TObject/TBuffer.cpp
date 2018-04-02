#include "TObject/TBuffer.h"

TBuffer::TBuffer(uint8* pre_addr,uint32 pre_w,uint32 w,uint32 h)
{
    contextType = 0;
	addr = (uint8*)malloc(w * h * GUI_PIXELSIZE);
	bufW = w;
	bufH = h;
}

TBuffer::TBuffer(TImage* img,uint8* readAddr,TSize* readSize)
{
	contextType = 0;
	bufW = img->imgW();
	bufH = img->imgH();
	if(img->getImgType() == T_PNG)
	{
		addr = (uint8*)malloc(bufW * bufH * GUI_PIXELSIZE);
		TSize size(bufW,bufH);
		//if(readAddr = NULL)
		img->ImgBlendLoad(readAddr,readSize,addr,&size);
	}
	else
	{
		addr = img->imgBuf();
	}	

}

TBuffer::~TBuffer()
{
	if(addr)
		free (addr);
	addr = NULL;
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
		uint32 src_addr = (uint32)getBufAddr() + (y_offset * getBufW() + x_offset ) * GUI_PIXELSIZE;
		for(int i = 0;i < srcRect->height();  i++)
		{
			gui_memcpy((uint8*)des_addr,(uint8*)src_addr,srcRect->width() * GUI_PIXELSIZE);
			src_addr += getBufW() * GUI_PIXELSIZE;
			des_addr += GUI_WIDTH * GUI_PIXELSIZE;
		}
}

void TBuffer::obPareBack(uint8* pre_addr,uint32 pre_w)
{
	uint32 des_addr = (uint32)getBufAddr();
	uint32 src_addr = (uint32)pre_addr;
	for(int i = 0;i < getBufH();  ++i)
	{
		gui_memcpy((uint8 *)des_addr,(uint8 *)src_addr,getBufW() * GUI_PIXELSIZE);
		src_addr += pre_w * GUI_PIXELSIZE;
		des_addr += getBufW() * GUI_PIXELSIZE;
	}
}

//若用宏定义 减少call 减少执行世界
uint32 TBuffer::readPoint(int32 x,int32 y)
{
	return *(uint32_t* )(((uint32)getBufAddr()) + (y * getBufW() + x) * GUI_PIXELSIZE);
}

void TBuffer::writePoint(int32 x,int32 y,uint32 color)
{
	gui_set_rect((uint32_t*)getBufAddr(),getBufW(),color,x , y ,1,1);
}






