#include "TObject/TBuffer.h"

TBuffer::TBuffer(uint32* pre_addr,uint32 pre_w,uint32 w,uint32 h)
{
    buf = NULL;
    buf= (uint32*)new uint8[w * h * GUI_PIXELSIZE];
    bufW = w;
	bufH = h;
	//搬运父亲背景 至 TBuffer
	uint32 * des_addr = buf;
	uint32 * src_addr = pre_addr;
	for(int i = 0;i < h;  i++)
	{
		memcpy(des_addr,src_addr,pre_w * GUI_PIXELSIZE);
		src_addr += pre_w;
		des_addr += w;
	}
}
TBuffer::~TBuffer()
{
    if(buf)
        delete[] (buf);
}


void TBuffer::transform()
{

	//直接刷新

	//剪切域剪切后刷新
}

