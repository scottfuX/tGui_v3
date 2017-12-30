#include "tObject/tLabel.h"

tLabel::tLabel(int32 x, int32 y, int32 w, int32 h, const char* n, tWidget* obj)
	:tFrame(x,y,w,h,n,obj)
{
}

void tLabel::show()
{
	tPainter p(getInvalidList(),getPaintInvaild());
	p.drawLabel(x(), y(), width(), height(), getName(),BLACK, ((tWidget*)getParents())->getBackColor());
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

