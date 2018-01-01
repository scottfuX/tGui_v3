#include "tObject/tPushButton.h"

tPushButton::tPushButton(int32 x, int32 y, int32 w, int32 h, const char* name, tWidget* obj)
	:tAbstractButton(x, y, w, h, name, obj)
{
}

void tPushButton::sig_depress(int32 d1, int32 d2)
{
	tPainter p(getInvalidList(),getPaintInvaild());
	p.drawButton(x(), y(), width(), height(), getName(), true);
	state = true;
	callSlot((func)&tPushButton::sig_depress,d1,d2);
}

void tPushButton::sig_release(int32 d1, int32 d2)
{
	tPainter p(getInvalidList(),getPaintInvaild());
	p.drawButton(x(), y(), width(), height(), getName(), false);
	state = false;
	callSlot((func)&tPushButton::sig_release,d1,d2);

}
void tPushButton::release()
{
	tPainter p(getInvalidList(),getPaintInvaild());
	p.drawButton(x(), y(), width(), height(), getName(), false);
	state = false;
}

void tPushButton::show()
{
	tPainter p(getInvalidList(),getPaintInvaild());
	p.drawButton(x(), y(), width(), height(), getName(), state);
}
