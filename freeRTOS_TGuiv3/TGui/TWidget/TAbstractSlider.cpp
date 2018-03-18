#include "TWidget/TAbstractSlider.h"

TAbstractSlider::TAbstractSlider(int32 x, int32 y, int32 w, int32 h, const char* n, TWidget* obj, bool isHoriz )
	: TWidget(x,y,w,h,n,obj)
{
	 value = 0;
	 state = false; //true => press ;false
	 this->isHoriz = isHoriz;//true horiz
}
