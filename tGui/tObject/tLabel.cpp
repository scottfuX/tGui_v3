#include "tObject/tLabel.h"

tLabel::tLabel(int32 x, int32 y, int32 w, int32 h, const char* n, tObject* obj)
	:tFrame(x,y,w,h,n,obj)
{
}

void tLabel::show()
{
	tPainter p;
	p.drawLabel(x(), y(), width(), height(), getName(),BLACK,getBackColor());
}

void tLabel::slot_showValue(int32 d1,int32 d2)
{
	setName((const char*)d1);
	if (d1 == TYPE_INT)
	{
		tString* temp = new tString();
		temp->setNum(d2);
		setName(temp);
	}
	show();
}

