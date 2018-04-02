#include "TWidget/TAbstractButton.h"


TAbstractButton::TAbstractButton(int32 x, int32 y, int32 w, int32 h,bool haveImg ,const char* n, TWidget* obj)
	: TWidget(x, y, w, h, n, obj)
{
	norImg = NULL;
	selImg = NULL;
	state = false;
	this->haveImg = haveImg;
};


TAbstractButton::~TAbstractButton()
{
	if(haveImg)
	{
		delete norImg;
		delete selImg;
	}
}

void TAbstractButton::touchPressEvent(TTouchEvent *e)
{
	if (isInRealArea(e->x(), e->y()))
		sig_depress(e->x(), e->y());
};

void TAbstractButton::touchReleaseEvent(TTouchEvent *e)
{
	if (state && isInRealArea(e->x(), e->y()))
		sig_release(e->x(), e->y());
};

void TAbstractButton::touchMoveEvent(TTouchEvent *e)
{
	if (state && !isInRealArea(e->x(), e->y()))//被按下但是位置又不在区域内 就释放
		release();
};
