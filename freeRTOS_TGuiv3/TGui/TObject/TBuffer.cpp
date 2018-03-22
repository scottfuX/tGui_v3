#include "TObject/TBuffer.h"

TBuffer::TBuffer(uint8* pre_addr,uint32 pre_w,uint32 w,uint32 h)
{
    buf = NULL;
    buf= (uint8*)new uint8[w * h * GUI_PIXELSIZE];
	//buf = 
    bufW = w;
	bufH = h;
	//搬运父亲背景 至 TBuffer
	uint8 * des_addr = buf;
	uint8 * src_addr = pre_addr;
	for(int i = 0;i < h;  i++)
	{
		memcpy(des_addr,src_addr,pre_w * GUI_PIXELSIZE);
		src_addr += pre_w * GUI_PIXELSIZE;
		des_addr += w * GUI_PIXELSIZE;
	}
}
TBuffer::~TBuffer()
{
    if(buf)
        delete[] (buf);
}



