#include "tObject/tCheckBox.h"


tCheckBox::tCheckBox(int32 x, int32 y, int32 w, int32 h, const char* name) :tAbstractButton()
{
	next = this; 
	selected = false; 
	state = false;
	setX(x);
	setY(y);
	setW(w);
	setH(h);
	setName(name);
}


void tCheckBox::sig_depress(int32 d1, int32 d2)
{
	tPainter p;
	p.drawCheck(x(), y(), width(), height(), getName(),selected, true);
	state = true;
	callSlot((func)&tCheckBox::sig_depress,d1,d2);
}


void tCheckBox::sig_release(int32 d1, int32 d2)
{
	changeSelected();
	tPainter p;
	p.drawCheck(x(), y(), width(), height(), getName(), selected, false);
	state = false;
	printf("d1=%d,d2=%d", d1, d2);
	callSlot((func)&tCheckBox::sig_release,d1,d2);
}

void tCheckBox::release()
{
	tPainter p;
	p.drawCheck(x(), y(), width(), height(), getName(), selected, false);
	state = false;
}

void tCheckBox::show()
{
	tPainter p;
	p.drawCheck(x(), y(),width() ,height(), getName(), selected,state);
}
