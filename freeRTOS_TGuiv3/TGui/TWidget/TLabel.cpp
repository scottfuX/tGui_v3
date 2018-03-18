#include "TWidget/TLabel.h"

TLabel::TLabel(int32 x, int32 y, int32 w, int32 h, const char* n, TWidget* obj)
	:TFrame(x,y,w,h,n,obj)
{
	textColor = BLACK;
	setBackColor(((TWidget*)getParents())->getBackColor());
		//TPainter p(getInvalidList(),getPaintInvaild());
	TBufPainter p(getBuffer()->getBufAddr(),getRect());
	p.drawLabel(0, 0, width(), height(), getName(),textColor,getBackColor());
}

void TLabel::show()
{
	//TPainter p(getInvalidList(),getPaintInvaild());
	TBufPainter p(getBuffer()->getBufAddr(),getRect());
	p.drawLabel(0, 0, width(), height(), getName(),textColor,getBackColor());
	refresh();
}

void TLabel::slot_showValue(int32 d1,int32 d2)
{
	setName((const char*)d1);
	if (d1 == TYPE_INT)
	{
		TString* temp = new TString();
		temp->setNum(d2);
		setName(temp);
	}
	show();
}

