#include "tObject/tSlider.h"


tSlider::tSlider(int32 x, int32 y, int32 w, int32 h, const char* name, bool isHoriz, tObject* obj) 
	:tAbstractSlider(x,y,w,h,name,isHoriz,obj)
{
}
void tSlider::sig_move(int32 d1, int32 d2)
{
	printf("move y = %d", d2);
	int32 value_pre = value;
	tPainter p;
	if (isHoriz)
	{
		value = ((d1 - x() + height() * 4 / 6) * 10) / (width() / 10);
		p.drawHorizSlider(x(), y(), width(), height(), value, value_pre, true);
	}
	else
	{
		value = ((d2 - y() + width() * 4 / 6) * 10) / (height() / 10);
		p.drawVertSlider(x(), y(), width(), height(), value, value_pre, true);
	}
	
	if (value > 100) value = 100;
	if (value < 0)value = 0;
	d1 = TYPE_INT;
	d2 = value;
	callSlot((func)&tSlider::sig_move, d1, d2);
}

void tSlider::sig_depress(int32 d1, int32 d2)
{
	tPainter p;
	if (isHoriz)
	{
		value = ((d1 - x() + height() * 4 / 6) * 10) / (width() / 10);
		p.drawHorizSlider(x(), y(), width(), height(), value, -1, true);
	}
	else
	{
		value = ((d2 - y() + width() * 4 / 6) * 10) / (height() / 10);
		p.drawVertSlider(x(), y(), width(), height(), value, -1, true);
	}
	state = true;
	if (value > 100) value = 100;
	if (value < 0)value = 0;
	d1 = TYPE_INT;
	d2 = value;
	callSlot((func)&tSlider::sig_depress, d1, d2);
}

void tSlider::sig_release(int32 d1, int32 d2)
{
	tPainter p;
	if (isHoriz)
	{
		value = ((d1 - x() + height() * 4 / 6) * 10) / (width() / 10);
		p.drawHorizSlider(x(), y(), width(), height(), value, -1, false);
	}
	else
	{
		value = ((d2 - y() + width() * 4 / 6) * 10) / (height() / 10);
		p.drawVertSlider(x(), y(), width(), height(), value, -1, false);
	}
	state = false;
	if (value > 100) value = 100;
	if (value < 0)value = 0;
	d1 = TYPE_INT;
	d2 = value;
	callSlot((func)&tSlider::sig_release, d1, d2);
}
void tSlider::release()
{
	tPainter p;
	if (isHoriz)
		p.drawHorizSlider(x(), y(), width(), height(), value, -1, false);
	else
		p.drawVertSlider(x(), y(), width(), height(), value, -1, false);
	state = false;
}

void tSlider::show()
{
	tPainter p;
	if (isHoriz)
		p.drawHorizSlider(x(), y(), width(), height(), value, -1, state);
	else
		p.drawVertSlider(x(), y(), width(), height(), value, -1, state);
}

void tSlider::touchPressEvent(tTouchEvent *e)
{
	if (isArea(e->x(), e->y()))
		sig_depress(e->x(), e->y());
};

void tSlider::touchReleaseEvent(tTouchEvent *e)
{
	if (state && isArea(e->x(), e->y()))
		sig_release(e->x(), e->y());
	if (state)
		release();
};

void tSlider::touchMoveEvent(tTouchEvent *e)
{
	if (state)
		sig_move(e->x(), e->y());
};


