#include "tObject/tSlider.h"


tSlider::tSlider(int32 x, int32 y, int32 w, int32 h, const char* name) :tAbstractSlider()
{
	value = 0;
	setX(x);
	setY(y);
	setW(w);
	setH(h);
	setName(name);
}
void tSlider::sig_move(int32 d1, int32 d2)
{
	printf("move y = %d", d2);
	value =  ((d1 - x() + height() * 4 / 6) * 10) / (width()/10);//问题在这里。。
	tPainter p;
	p.drawSlider(x(), y(), width(), height(), value, 0, true);
	callSlot((func)&tSlider::sig_move, d1, d2);
}

void tSlider::sig_depress(int32 d1, int32 d2)
{
	tPainter p;
	//value = ((d2 - y() + height() * 4 / 6) * 100) / width();
	p.drawSlider(x(), y(), width(), height(), value, 0, true);
	state = true;
	callSlot((func)&tSlider::sig_depress, d1, d2);
}

void tSlider::sig_release(int32 d1, int32 d2)
{
	tPainter p;
	//value = ((d2 - y() + height() * 4 / 6) * 100) / width();
	p.drawSlider(x(), y(), width(), height(), value, 0, false);
	state = false;
	callSlot((func)&tSlider::sig_release, d1, d2);
}
void tSlider::release()
{
	tPainter p;
	p.drawSlider(x(), y(), width(), height(), value, 0, false);
	state = false;
}

void tSlider::show()
{
	tPainter p;
	p.drawSlider(x(), y(), width(), height(), value, 0,state);
}

void tSlider::touchPressEvent(tTouchEvent *e)
{
	if (isArea(e->x(), e->y()))
		sig_depress(e->x(), e->y());
};

void tSlider::touchReleaseEvent(tTouchEvent *e)
{
	if (isArea(e->x(), e->y()))
		sig_release(e->x(), e->y());
};

void tSlider::touchMoveEvent(tTouchEvent *e)
{
	if (isArea(e->x(), e->y()))
		sig_move(e->x(), e->y());
	else if(state)
		release();
};


