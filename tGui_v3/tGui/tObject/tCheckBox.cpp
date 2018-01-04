#include "tObject/tCheckBox.h"


tCheckBox::tCheckBox(int32 x, int32 y, int32 w, int32 h, const char* name, tWidget* obj)
	:tAbstractButton(x, y, w, h, name, obj)
{
	next = this; 
	selected = false; 
}


void tCheckBox::sig_depress(int32 d1, int32 d2)
{
	tPainter p(getInvalidList(),getPaintInvaild());
	p.drawCheck(x(), y(), width(), height(), getName(),selected, true, getBackColor());
	state = true;
	callSlot((func)&tCheckBox::sig_depress,d1,d2);
}


void tCheckBox::sig_release(int32 d1, int32 d2)
{
	changeSelected();
	tPainter p(getInvalidList(),getPaintInvaild());
	p.drawCheck(x(), y(), width(), height(), getName(), selected, false, getBackColor());
	state = false;
	callSlot((func)&tCheckBox::sig_release,d1,d2);
}

void tCheckBox::release()
{
	tPainter p(getInvalidList(),getPaintInvaild());
	p.drawCheck(x(), y(), width(), height(), getName(), selected, false, getBackColor());
	state = false;
}

void tCheckBox::show()
{
	tPainter p(getInvalidList(),getPaintInvaild());
	p.drawCheck(x(), y(), width(), height(), getName(), selected, state, getBackColor());
}
