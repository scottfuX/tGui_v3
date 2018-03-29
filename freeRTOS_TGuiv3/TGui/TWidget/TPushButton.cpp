#include "TWidget/TPushButton.h"

TPushButton::TPushButton(int32 x, int32 y, int32 w, int32 h, const char* name, TWidget* obj)
	:TAbstractButton(x, y, w, h,false, name, obj)
{
	TBufPainter p(getBuffer()->getBufAddr(),getRect());
	p.drawButton(0, 0, width(), height(), getName(), state);
	selBuf = NULL;
	norBuf = NULL;
}


TPushButton::TPushButton(int32 x, int32 y, TImage norImg ,TImage selImg ,  const char* name, TWidget* obj)
	:TAbstractButton(x, y,MAX(norImg.imgW() ,selImg.imgW()),MAX(norImg.imgH() ,selImg.imgH()),true, name, obj)
{
	norImg.ImgLoad(0,0,norBuf);
	selImg.ImgLoad(0,0,selBuf);

	TBufPainter p1(norBuf->getBufAddr(),getRect());
	p1.drawCenterEnText(0,0, width(), height(), getName());
	TBufPainter p2(selBuf->getBufAddr(),getRect());
	p2.drawCenterEnText(0,0, width(), height(), getName());
}

TPushButton::~TPushButton() 
{
};

void TPushButton::sig_depress(int32 d1, int32 d2)
{
	if(haveImg)
	{
		setBuffer(selBuf);
		refresh();
	}
	else
	{
		//改painter为在buf上面画画 通过refresh进行剪切
		TBufPainter p(getBuffer()->getBufAddr(),getRect());
		p.drawButton(0, 0, width(), height(), getName(), true);
		refresh();
	}
	state = true;
	callSlot((func)&TPushButton::sig_depress,d1,d2);
}

void TPushButton::sig_release(int32 d1, int32 d2)
{
	if(haveImg)
	{
		setBuffer(norBuf);
		refresh();
	}
	else
	{
		TBufPainter p(getBuffer()->getBufAddr(),getRect());
		p.drawButton(0, 0, width(), height(), getName(), false);
		refresh();
	}
	state = false;
	callSlot((func)&TPushButton::sig_release,d1,d2);
}

void TPushButton::release()
{
	if(haveImg)
	{
		setBuffer(norBuf);
		refresh();
	}
	else
	{
		TBufPainter p(getBuffer()->getBufAddr(),getRect());
		p.drawButton(0, 0, width(), height(), getName(), false);
		refresh();
	}
	state = false;
}

void TPushButton::show()
{
	TBufPainter p(getBuffer()->getBufAddr(),getRect());
	p.displayCHStr(0,0,"你好",false);
	refresh();
}
