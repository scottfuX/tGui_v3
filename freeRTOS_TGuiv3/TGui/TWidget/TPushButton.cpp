#include "TWidget/TPushButton.h"

TPushButton::TPushButton(int32 x, int32 y, int32 w, int32 h, const char* name, TWidget* obj)
	:TAbstractButton(x, y, w, h, name, obj)
{
	TBufPainter p(getBuffer()->getBufAddr(),getRect());
	p.drawButton(0, 0, width(), height(), getName(), state);
}

void TPushButton::sig_depress(int32 d1, int32 d2)
{
	// TPainter p(getInvalidList(),getPaintInvaild());
	//改painter为在buf上面画画 通过refresh进行剪切
	TBufPainter p(getBuffer()->getBufAddr(),getRect());
	p.drawButton(0, 0, width(), height(), getName(), true);
	refresh();
	state = true;
	callSlot((func)&TPushButton::sig_depress,d1,d2);
}

void TPushButton::sig_release(int32 d1, int32 d2)
{
	// TPainter p(getInvalidList(),getPaintInvaild());
	TBufPainter p(getBuffer()->getBufAddr(),getRect());
	p.drawButton(0, 0, width(), height(), getName(), false);
	refresh();
	state = false;
	callSlot((func)&TPushButton::sig_release,d1,d2);
}
void TPushButton::release()
{
	// TPainter p(getInvalidList(),getPaintInvaild());
	TBufPainter p(getBuffer()->getBufAddr(),getRect());
	p.drawButton(0, 0, width(), height(), getName(), false);
	refresh();
	state = false;
	
}

void TPushButton::show()
{
	//TPainter p(getInvalidList(),getPaintInvaild());
	refresh();
}
