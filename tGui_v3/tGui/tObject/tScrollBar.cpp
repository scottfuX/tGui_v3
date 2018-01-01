#include "tObject/tScrollBar.h"


tScrollBar::tScrollBar(int32 x, int32 y, int32 w, int32 h, const char* name, tWidget* obj, bool isHoriz )
	:tAbstractSlider(x, y, w, h, name, obj, isHoriz)
{

}


void tScrollBar::sig_move(int32 d1, int32 d2)
{

}

void tScrollBar::sig_depress(int32 d1, int32 d2)
{

}

void tScrollBar::sig_release(int32 d1, int32 d2)
{

}
void tScrollBar::release()
{

}

void tScrollBar::touchPressEvent(tTouchEvent *e)
{
	if (isInRealArea(e->x(), e->y()))
		sig_depress(e->x(), e->y());
};

void tScrollBar::touchReleaseEvent(tTouchEvent *e)
{
	if (isInRealArea(e->x(), e->y()))
		sig_release(e->x(), e->y());
};

void tScrollBar::touchMoveEvent(tTouchEvent *e)
{
	if (isInRealArea(e->x(), e->y()))
		sig_move(e->x(), e->y());
	else
		release();
};