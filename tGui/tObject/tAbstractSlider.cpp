#include "tObject/tAbstractSlider.h"

tAbstractSlider::tAbstractSlider(int32 x, int32 y, int32 w, int32 h, const char* n, tWidget* obj, bool isHoriz )
	: tWidget(x,y,w,h,n,obj)
{
	 value = 0;
	 state = false; //true => press ;false
	 this->isHoriz = isHoriz;//true horiz
}
