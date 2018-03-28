#include "TWidget/TAbstractButton.h"


TAbstractButton::TAbstractButton(int32 x, int32 y, int32 w, int32 h,bool haveImg ,const char* n, TWidget* obj)
	: TWidget(x, y, w, h, n, obj)
{
	selBuf = NULL;
	norBuf = NULL;
	state = false;
	this->haveImg = haveImg;
	if(haveImg)
	{
		norBuf = getBuffer();
		if(obj == NULL)
			selBuf = new TBuffer(NULL, width() ,width(), height());
		else
			selBuf = new TBuffer(obj->getBuffer()->getBufAddr() + (getOffsetWH()->width() +  getOffsetWH()->height() * obj->width())*GUI_PIXELSIZE,obj->width() ,width(), height());
	}
};


TAbstractButton::~TAbstractButton()
{
	if(haveImg)
	{
		setBuffer(norBuf);
		delete selBuf;
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
