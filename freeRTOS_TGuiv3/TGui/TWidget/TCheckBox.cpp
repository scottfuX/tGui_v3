#include "TWidget/TCheckBox.h"


TCheckBox::TCheckBox(int32 x, int32 y, int32 w, int32 h, const char* name, TWidget* obj)
	:TAbstractButton(x, y, w, h, name, obj)
{
	next = this; 
	selected = false; 
	TBufPainter p(getBuffer()->getBufAddr(),getRect());
	p.drawCheck(0,0, width(), height(), getName(), selected, state, getBackColor());
}


void TCheckBox::sig_depress(int32 d1, int32 d2)
{
	//TPainter p(getInvalidList(),getPaintInvaild());
	TBufPainter p(getBuffer()->getBufAddr(),getRect());
	p.drawCheck(0, 0, width(), height(), getName(),selected, true, getBackColor());
	refresh();
	state = true;
	callSlot((func)&TCheckBox::sig_depress,d1,d2);
}


void TCheckBox::sig_release(int32 d1, int32 d2)
{
	changeSelected();
	//TPainter p(getInvalidList(),getPaintInvaild());
	TBufPainter p(getBuffer()->getBufAddr(),getRect());
	p.drawCheck(0, 0, width(), height(), getName(), selected, false, getBackColor());
	refresh();
	state = false;
	callSlot((func)&TCheckBox::sig_release,d1,d2);
}

void TCheckBox::release()
{
	//TPainter p(getInvalidList(),getPaintInvaild());
	TBufPainter p(getBuffer()->getBufAddr(),getRect());
	p.drawCheck(0, 0, width(), height(), getName(), selected, false, getBackColor());
	refresh();
	state = false;
}

void TCheckBox::show()
{
	//TPainter p(getInvalidList(),getPaintInvaild());
	refresh();
}
