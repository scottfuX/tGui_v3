#include "TObject/TBuffer.h"

TBuffer::TBuffer(uint8* pre_addr,uint32 pre_w,uint32 w,uint32 h)
{
    buf = NULL;
    //buf= (uint8*)new uint8[w * h * GUI_PIXELSIZE];
    buf = (uint8*) malloc (w * h * GUI_PIXELSIZE);
	bufW = w;
	bufH = h;
	if(pre_addr)
	{//搬运父亲背景 至 TBuffer
		uint8 * des_addr = buf;
		uint8 * src_addr = pre_addr;
		for(int i = 0;i < h;  i++)
		{
			memcpy(des_addr,src_addr,pre_w * GUI_PIXELSIZE);
			src_addr += pre_w * GUI_PIXELSIZE;
			des_addr += w * GUI_PIXELSIZE;
		}
	}
	else
	{
		gui_dma2d_memset((uint32_t*)pre_addr,w,WHITE,0 , 0,w,h);
	}
}


TBuffer::~TBuffer()
{
    if(buf)
        //delete[] (buf);
		free(buf);
}

//若用宏定义 减少call 减少执行世界
uint32 TBuffer::readPoint(int32 x,int32 y)
{
	return *(uint32_t* )(((uint32)buf) + (y * bufW + x) * GUI_PIXELSIZE);
}

void TBuffer::writePoint(int32 x,int32 y,uint32 color)
{
	gui_dma2d_memset((uint32_t*)buf,bufW,color,x , y ,1,1);
}






