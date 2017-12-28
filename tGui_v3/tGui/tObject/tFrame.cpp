#include "tObject/tFrame.h"



tFrame::tFrame(int32 x, int32 y, int32 w, int32 h, const char* n , tObject* obj)
	:tWidget(x,y,w,h,n,obj)
{
}


tFrame::~tFrame()
{
}
