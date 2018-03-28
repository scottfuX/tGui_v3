#include "TWidget/TSlider.h"


TSlider::TSlider(int32 x, int32 y, int32 w, int32 h, const char* name, TWidget* obj, bool isHoriz)
	:TAbstractSlider(x,y,w,h,name, obj,isHoriz)
{
	haveImg = false;
	TBufPainter p(getBuffer()->getBufAddr(),getRect());
	if (isHoriz)
		p.drawHorizSlider(0, 0, width(), height(), value, -1, state, ((TWidget*)getParents())->getBackColor());
	else
		p.drawVertSlider(0, 0, width(), height(), value, -1, state, ((TWidget*)getParents())->getBackColor());
}

TSlider::TSlider(int32 x, int32 y,TImage* backImg,TImage* frontImg,TImage* barImg, const char* name, TWidget* obj, bool isHoriz)
 	:TAbstractSlider(x,y,backImg->imgW()+barImg->imgW(),barImg->imgH(),name, obj,isHoriz)
{
	haveImg = true;
	this->backImg = backImg;
	this->frontImg = frontImg;
	this->barImg = barImg;
	value  = 0;
	if(isHoriz)
	{
		//根据不同的value 
		//加载 ----- 背景，前景，bar  
		//问题1:用buf转移 速度会不会不够快 不会
		//问题2:应该记住现在的slider的位置然后到时还原 全部刷新
		uint32 w = value * frontImg->imgW() / 100;
		backImg->ImgLoad(barImg->imgW()/2,(height() - backImg->imgH())/2,getBuffer());
		frontImg->ImgLoad(barImg->imgW()/2,(height() - frontImg->imgH())/2, w ,frontImg->imgH(),getBuffer());
		barImg->ImgLoad(w ,0,getBuffer()); //注意  barImg->imgW() 而不是imgH() 因为height可能会有阴影 ---前提要是圆的

	}
	else
	{
		//根据不同的value 

		//加载 ----- 背景，前景，bar 
	}
}

TSlider::~TSlider()
{
	if(backImg)
		delete backImg;
	if(frontImg)
		delete frontImg;
	if(barImg)
		delete barImg;
}

void TSlider::sig_move(int32 d1, int32 d2)
{
	int32 value_pre = value;
	TBufPainter p(getBuffer()->getBufAddr(),getRect());
	if (isHoriz)
	{
		value = ((d1 - x() ) * 100) / (width());
		if(haveImg)
		{
			if (value > 100) value = 100;
			if (value < 0)value = 0;
			uint32 w = value * frontImg->imgW() / 100;
			getBuffer()->obPareBack(((TWidget*)getParents())->getBuffer()->getBufAddr() + (getOffsetWH()->width() +  getOffsetWH()->height() * ((TWidget*)getParents())->width())*GUI_PIXELSIZE,((TWidget*)getParents())->width() );
			backImg->ImgLoad(barImg->imgW()/2,(height() - backImg->imgH())/2,getBuffer());
			frontImg->ImgLoad(barImg->imgW()/2,(height() - frontImg->imgH())/2, w ,frontImg->imgH(),getBuffer());
			barImg->ImgLoad(w,0,getBuffer()); //注意  barImg->imgW() 而不是imgH() 因为height可能会有阴影 ---前提要是圆的
		}
		else
		{
			p.drawHorizSlider(0, 0, width(), height(), value, value_pre, true, ((TWidget*)getParents())->getBackColor());
		}
	}
	else
	{
		value = ((d2 - y() ) * 100) / (height());
		if(haveImg)
		{

		}
		else
		{
			p.drawVertSlider(0, 0, width(), height(), value, value_pre, true, ((TWidget*)getParents())->getBackColor());
		}
	}
	refresh();
	sig_valueChange(TYPE_INT, value);
	callSlot((func)&TSlider::sig_move, d1, d2);
}

void TSlider::sig_depress(int32 d1, int32 d2)
{
	TBufPainter p(getBuffer()->getBufAddr(),getRect());
	if (isHoriz)
	{
		value = ((d1 - x() ) * 100) / (width());
		if(haveImg)
		{
		}
		else
		{
			p.drawHorizSlider(0, 0, width(), height(), value, -1, true, ((TWidget*)getParents())->getBackColor());
		}
	}
	else
	{
		value = ((d2 - y() ) * 100) / (height() );
		if(haveImg)
		{
		}
		else
		{
			p.drawVertSlider(0, 0, width(), height(), value, -1, true, ((TWidget*)getParents())->getBackColor());
		}
	}
	refresh();
	state = true;
	sig_valueChange(TYPE_INT, value);
	callSlot((func)&TSlider::sig_depress, d1, d2);
}

void TSlider::sig_release(int32 d1, int32 d2)
{
	release();
	if (value > 100) value = 100;
	if (value < 0)value = 0;
	//bar所在的位置
	if(isHoriz)
		callSlot((func)&TSlider::sig_release, d1,0);
	else
		callSlot((func)&TSlider::sig_release,0,d2);
	d1 = TYPE_INT;
	d2 = value;
	callSlot((func)&TSlider::sig_release, d1, d2);
}

//就只是释放，不是消息
void TSlider::release()
{
	TBufPainter p(getBuffer()->getBufAddr(),getRect());
	if (isHoriz)
	{
		if(haveImg)
		{
			if (value > 100) value = 100;
			if (value < 0)value = 0;
			uint32 w = value * frontImg->imgW() / 100;
			getBuffer()->obPareBack(((TWidget*)getParents())->getBuffer()->getBufAddr() + (getOffsetWH()->width() +  getOffsetWH()->height() * ((TWidget*)getParents())->width())*GUI_PIXELSIZE,((TWidget*)getParents())->width() );
			backImg->ImgLoad(barImg->imgW()/2,(height() - backImg->imgH())/2,getBuffer());
			frontImg->ImgLoad(barImg->imgW()/2,(height() - frontImg->imgH())/2, w ,frontImg->imgH(),getBuffer());
			barImg->ImgLoad(w,0,getBuffer()); //注意  barImg->imgW() 而不是imgH() 因为height可能会有阴影 ---前提要是圆的
		}
		else
		{
			p.drawHorizSlider(0, 0, width(), height(), value, -1, false, ((TWidget*)getParents())->getBackColor());
		}
	}
	else
	{
		if(haveImg)
		{

		}
		else
		{
			p.drawVertSlider(0, 0, width(), height(), value, -1, false, ((TWidget*)getParents())->getBackColor());
		}
	}
	refresh();
	state = false;
}

void TSlider::show()
{
	refresh();
}

void TSlider::sig_valueChange(int32 d1, int32 d2)
{
	if (d2 > 100) d2 = 100;
	if (d2 < 0)d2 = 0;
	callSlot((func)&TSlider::sig_valueChange, d1, d2);
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


