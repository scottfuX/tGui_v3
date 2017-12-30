#include "tObject/tFrame.h"



tFrame::tFrame(int32 x, int32 y, int32 w, int32 h, const char* n , tWidget* obj)
	:tWidget(x,y,w,h,n,obj)
{
}


tFrame::~tFrame()
{
}
