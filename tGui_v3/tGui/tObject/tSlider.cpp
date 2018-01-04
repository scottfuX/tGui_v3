#include "tObject/tSlider.h"


tSlider::tSlider(int32 x, int32 y, int32 w, int32 h, const char* name, tWidget* obj, bool isHoriz)
	:tAbstractSlider(x,y,w,h,name, obj,isHoriz)
{
}
void tSlider::sig_move(int32 d1, int32 d2)
{
	int32 value_pre = value;
	tPainter p(getInvalidList(),getPaintInvaild());
	if (isHoriz)
	{
		value = ((d1 - x() ) * 100) / (width());
		p.drawHorizSlider(x(), y(), width(), height(), value, value_pre, true, ((tWidget*)getParents())->getBackColor());
	}
	else
	{
		value = ((d2 - y() ) * 100) / (height());
		p.drawVertSlider(x(), y(), width(), height(), value, value_pre, true, ((tWidget*)getParents())->getBackColor());
	}
	sig_valueChange(TYPE_INT, value);
	callSlot((func)&tSlider::sig_move, d1, d2);
}
void tSlider::sig_valueChange(int32 d1, int32 d2)
{
	if (d2 > 100) d2 = 100;
	if (d2 < 0)d2 = 0;
	callSlot((func)&tSlider::sig_valueChange, d1, d2);
}

void tSlider::sig_depress(int32 d1, int32 d2)
{
	tPainter p(getInvalidList(),getPaintInvaild());
	if (isHoriz)
	{
		value = ((d1 - x() ) * 100) / (width());
		p.drawHorizSlider(x(), y(), width(), height(), value, -1, true, ((tWidget*)getParents())->getBackColor());
	}
	else
	{
		value = ((d2 - y() ) * 100) / (height() );
		p.drawVertSlider(x(), y(), width(), height(), value, -1, true, ((tWidget*)getParents())->getBackColor());
	}
	state = true;
	sig_valueChange(TYPE_INT, value);
	callSlot((func)&tSlider::sig_depress, d1, d2);
}

void tSlider::sig_release(int32 d1, int32 d2)
{
	tPainter p(getInvalidList(),getPaintInvaild());
	if (isHoriz)
	{
		value = ((d1 - x()) * 100) / (width() );
		p.drawHorizSlider(x(), y(), width(), height(), value, -1, false, ((tWidget*)getParents())->getBackColor());
	}
	else
	{
		value = ((d2 - y()) * 100) / (height());
		p.drawVertSlider(x(), y(), width(), height(), value, -1, false, ((tWidget*)getParents())->getBackColor());
	}
	state = false;
	if (value > 100) value = 100;
	if (value < 0)value = 0;
	d1 = TYPE_INT;
	d2 = value;
	callSlot((func)&tSlider::sig_release, d1, d2);
}

//就只是释放，不是消息
void tSlider::release()
{
	tPainter p(getInvalidList(),getPaintInvaild());
	if (isHoriz)
		p.drawHorizSlider(x(), y(), width(), height(), value, -1, false, ((tWidget*)getParents())->getBackColor());
	else
		p.drawVertSlider(x(), y(), width(), height(), value, -1, false, ((tWidget*)getParents())->getBackColor());
	state = false;
}

void tSlider::show()
{
	tPainter p(getInvalidList(),getPaintInvaild());
	if (isHoriz)
		p.drawHorizSlider(x(), y(), width(), height(), value, -1, state, ((tWidget*)getParents())->getBackColor());
	else
		p.drawVertSlider(x(), y(), width(), height(), value, -1, state, ((tWidget*)getParents())->getBackColor());
}

void tSlider::touchPressEvent(tTouchEvent *e)
{
	if (isInRealArea(e->x(), e->y()))
		sig_depress(e->x(), e->y());
};

void tSlider::touchReleaseEvent(tTouchEvent *e)
{
	if (state)
	{
		if (isInRealArea(e->x(), e->y()))
			sig_release(e->x(), e->y());
		else
			release();
	}
};

void tSlider::touchMoveEvent(tTouchEvent *e)
{
	if (state)
		sig_move(e->x(), e->y());
};


