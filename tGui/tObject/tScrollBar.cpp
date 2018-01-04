#include "tObject/tScrollBar.h"


tScrollBar::tScrollBar(int32 x, int32 y, int32 w, int32 h, const char* name, tWidget* obj, bool isHoriz )
	:tAbstractSlider(x, y, w, h, name, obj, isHoriz)
{
	if(isHoriz)
		scrollLen = w;//test
	else
		scrollLen = h;//test
}

void tScrollBar::sig_valueChange(int32 d1, int32 d2)
{
	if (d2 > 100) d2 = 100;
	if (d2 < 0)d2 = 0;
	callSlot((func)&tScrollBar::sig_valueChange, d1, d2);
}

void tScrollBar::sig_move(int32 d1, int32 d2)
{
	int32 value_pre = value;
	tPainter p(getInvalidList(), getPaintInvaild());
	if (isHoriz)
	{
		value = (d1 - x() ) * 100 / width() ;
		p.drawHorizScroll(x(), y(), width(), height(),scrollLen, value, value_pre, true);
	}
	else
	{
		value = (d2 - y())  * 100 / height() ;
		p.drawVertScroll(x(), y(), width(), height(), scrollLen, value, value_pre, true);
	}
	sig_valueChange(TYPE_INT, value);
	callSlot((func)&tScrollBar::sig_move, d1, d2);
}

void tScrollBar::sig_depress(int32 d1, int32 d2)
{
	tPainter p(getInvalidList(), getPaintInvaild());
	if (isHoriz)
	{
		if (d1 < value * width() / 100 + x() - scrollLen / 2)
			value -=  scrollLen * 100 / width();
		else  if(d1 > value * width() / 100 + x() + scrollLen / 2)
			value +=  scrollLen * 100 / width();
		p.drawHorizScroll(x(), y(), width(), height(), scrollLen, value, -1, true);
	}
	else
	{
		if (d2 < value * height() / 100 + y() - scrollLen / 2)
			value -= scrollLen * 100 / height();
		else  if (d2 > value * height() / 100 + y() + scrollLen / 2)
			value += scrollLen * 100 / height();
		p.drawVertScroll(x(), y(), width(), height(), scrollLen, value, -1, true);
	}
	state = true;
	sig_valueChange(TYPE_INT, value);
	callSlot((func)&tScrollBar::sig_depress, d1, d2);
}

void tScrollBar::sig_release(int32 d1, int32 d2)
{
	tPainter p(getInvalidList(), getPaintInvaild());
	if (isHoriz)
	{
		p.drawHorizScroll(x(), y(), width(), height(), scrollLen, value, -1, false);
	}
	else
	{
		p.drawVertScroll(x(), y(), width(), height(), scrollLen, value, -1, false);
	}
	state = false;
	if (value > 100) value = 100;
	if (value < 0)value = 0;
	d1 = TYPE_INT;
	d2 = value;
	callSlot((func)&tScrollBar::sig_release, d1, d2);
}

void tScrollBar::release()
{
	tPainter p(getInvalidList(), getPaintInvaild());
	if (isHoriz)
		p.drawHorizScroll(x(), y(), width(), height(), scrollLen, value, -1, false);
	else
		p.drawVertScroll(x(), y(), width(), height(), scrollLen, value, -1, false);
	state = false;
}

void tScrollBar::show()
{
	tPainter p(getInvalidList(), getPaintInvaild());
	if (isHoriz)
		p.drawHorizScroll(x(), y(), width(), height(), scrollLen, value, -1, state);
	else
		p.drawVertScroll(x(), y(), width(), height(), scrollLen, value, -1, state);
}

//根据真实的长度计算出其滚动条的长度
void tScrollBar::setRealLen(int32 reallen) 
{
	if (isHoriz)
		scrollLen = width() * width() / reallen;
	else
		scrollLen = height() * height() / reallen;
	show();
}

void tScrollBar::touchPressEvent(tTouchEvent *e)
{
	if (isInRealArea(e->x(), e->y()))
		sig_depress(e->x(), e->y());
};

void tScrollBar::touchReleaseEvent(tTouchEvent *e)
{
	if (state)
	{
		if (isInRealArea(e->x(), e->y()))
			sig_release(e->x(), e->y());
		else 
			release();
	}
};

void tScrollBar::touchMoveEvent(tTouchEvent *e)
{
	if (state)
		sig_move(e->x(), e->y());
};