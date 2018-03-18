#include "TWidget/TSlider.h"


TSlider::TSlider(int32 x, int32 y, int32 w, int32 h, const char* name, TWidget* obj, bool isHoriz)
	:TAbstractSlider(x,y,w,h,name, obj,isHoriz)
{
	TBufPainter p(getBuffer()->getBufAddr(),getRect());
	if (isHoriz)
		p.drawHorizSlider(0, 0, width(), height(), value, -1, state, ((TWidget*)getParents())->getBackColor());
	else
		p.drawVertSlider(0, 0, width(), height(), value, -1, state, ((TWidget*)getParents())->getBackColor());
}
void TSlider::sig_move(int32 d1, int32 d2)
{
	int32 value_pre = value;
	TBufPainter p(getBuffer()->getBufAddr(),getRect());
	if (isHoriz)
	{
		value = ((d1 - x() ) * 100) / (width());
		p.drawHorizSlider(0, 0, width(), height(), value, value_pre, true, ((TWidget*)getParents())->getBackColor());
		refresh();
	}
	else
	{
		value = ((d2 - y() ) * 100) / (height());
		p.drawVertSlider(0, 0, width(), height(), value, value_pre, true, ((TWidget*)getParents())->getBackColor());
		refresh();
	}
	sig_valueChange(TYPE_INT, value);
	callSlot((func)&TSlider::sig_move, d1, d2);
}
void TSlider::sig_valueChange(int32 d1, int32 d2)
{
	if (d2 > 100) d2 = 100;
	if (d2 < 0)d2 = 0;
	callSlot((func)&TSlider::sig_valueChange, d1, d2);
}

void TSlider::sig_depress(int32 d1, int32 d2)
{
	TBufPainter p(getBuffer()->getBufAddr(),getRect());
	if (isHoriz)
	{
		value = ((d1 - x() ) * 100) / (width());
		p.drawHorizSlider(0, 0, width(), height(), value, -1, true, ((TWidget*)getParents())->getBackColor());
		refresh();
	}
	else
	{
		value = ((d2 - y() ) * 100) / (height() );
		p.drawVertSlider(0, 0, width(), height(), value, -1, true, ((TWidget*)getParents())->getBackColor());
		refresh();
	}
	state = true;
	sig_valueChange(TYPE_INT, value);
	callSlot((func)&TSlider::sig_depress, d1, d2);
}

void TSlider::sig_release(int32 d1, int32 d2)
{
	TBufPainter p(getBuffer()->getBufAddr(),getRect());
	if (isHoriz)
	{
		value = ((d1 - x()) * 100) / (width() );
		p.drawHorizSlider(0, 0, width(), height(), value, -1, false, ((TWidget*)getParents())->getBackColor());
		refresh();
	}
	else
	{
		value = ((d2 - y()) * 100) / (height());
		p.drawVertSlider(0, 0, width(), height(), value, -1, false, ((TWidget*)getParents())->getBackColor());
		refresh();
	}
	state = false;
	if (value > 100) value = 100;
	if (value < 0)value = 0;
	d1 = TYPE_INT;
	d2 = value;
	callSlot((func)&TSlider::sig_release, d1, d2);
}

//就只是释放，不是消息
void TSlider::release()
{
	TBufPainter p(getBuffer()->getBufAddr(),getRect());
	if (isHoriz)
		p.drawHorizSlider(0, 0, width(), height(), value, -1, false, ((TWidget*)getParents())->getBackColor());
	else
		p.drawVertSlider(0, 0, width(), height(), value, -1, false, ((TWidget*)getParents())->getBackColor());
	refresh();
	state = false;
}

void TSlider::show()
{
	refresh();
}

void TSlider::touchPressEvent(TTouchEvent *e)
{
	if (isInRealArea(e->x(), e->y()))
		sig_depress(e->x(), e->y());
};

void TSlider::touchReleaseEvent(TTouchEvent *e)
{
	if (state)
	{
		if (isInRealArea(e->x(), e->y()))
			sig_release(e->x(), e->y());
		else
			release();
	}
};

void TSlider::touchMoveEvent(TTouchEvent *e)
{
	if (state)
		sig_move(e->x(), e->y());
};


