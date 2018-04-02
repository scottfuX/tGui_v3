#include "TWidget/TPushButton.h"

TPushButton::TPushButton(int32 x, int32 y, int32 w, int32 h, const char* name, TWidget* obj)
	:TAbstractButton(x, y, w, h,false, name, obj)
{
	TBufPainter p(getBuffer()->getBufAddr(),getRect());
	p.drawButton(0, 0, width(), height(), getName(), state);
	selImg = NULL;
	norImg = NULL;
}


TPushButton::TPushButton(int32 x, int32 y, TImage* norImg ,TImage* selImg ,  const char* name, TWidget* obj)
	:TAbstractButton(x, y,MAX(norImg->imgW() ,selImg->imgW()),MAX(norImg->imgH() ,selImg->imgH()),true, name, obj)
{
	this->norImg = norImg;
	this->selImg = selImg;

	imgLoadInterface(0,0,norImg);
	
	TBufPainter p(getBuffer()->getBufAddr(),getRect());
	p.drawCenterText(0,0, width(), height(), getName());
}

TPushButton::~TPushButton() 
{
};

void TPushButton::sig_depress(int32 d1, int32 d2)
{
	if(haveImg)
	{
		imgLoadInterface(0,0,selImg);
		TBufPainter p(getBuffer()->getBufAddr(),getRect());
		p.drawCenterText(0,0, width(), height(), getName());
	}
	else
	{
		//改painter为在buf上面画画 通过refresh进行剪切
		TBufPainter p(getBuffer()->getBufAddr(),getRect());
		p.drawButton(0, 0, width(), height(), getName(), true);
	}
	refresh();
	state = true;
	callSlot((func)&TPushButton::sig_depress,d1,d2);
}

void TPushButton::sig_release(int32 d1, int32 d2)
{
	if(haveImg)
	{
		imgLoadInterface(0,0,norImg);
		TBufPainter p(getBuffer()->getBufAddr(),getRect());
		p.drawCenterText(0,0, width(), height(), getName());
	}
	else
	{
		TBufPainter p(getBuffer()->getBufAddr(),getRect());
		p.drawButton(0, 0, width(), height(), getName(), false);	
	}
	refresh();
	state = false;
	callSlot((func)&TPushButton::sig_release,d1,d2);
}

void TPushButton::release()
{
	if(haveImg)
	{
		imgLoadInterface(0,0,norImg);
		TBufPainter p(getBuffer()->getBufAddr(),getRect());
		p.drawCenterText(0,0, width(), height(), getName());
	}
	else
	{
		TBufPainter p(getBuffer()->getBufAddr(),getRect());
		p.drawButton(0, 0, width(), height(), getName(), false);
	}
	refresh();
	state = false;
}

void TPushButton::show()
{
	refresh();
}
