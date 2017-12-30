#include "tObject/tAbstractButton.h"


tAbstractButton::tAbstractButton(int32 x, int32 y, int32 w, int32 h, const char* n, tWidget* obj)
	: tWidget(x, y, w, h, n, obj)
{
	state = false;
};

void tAbstractButton::touchPressEvent(tTouchEvent *e)
{
	if (isArea(e->x(), e->y()))
		sig_depress(e->x(), e->y());
};

void tAbstractButton::touchReleaseEvent(tTouchEvent *e)
{
	if (state && isArea(e->x(), e->y()))
		sig_release(e->x(), e->y());
};

void tAbstractButton::touchMoveEvent(tTouchEvent *e)
{
	if (state && !isArea(e->x(), e->y()))//被按下但是位置又不在区域内 就释放
		release();
};