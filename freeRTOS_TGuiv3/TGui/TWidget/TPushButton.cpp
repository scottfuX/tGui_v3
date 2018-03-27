#include "TWidget/TPushButton.h"

TPushButton::TPushButton(int32 x, int32 y, int32 w, int32 h, const char* name, TWidget* obj)
	:TAbstractButton(x, y, w, h, name, obj)
{
	TBufPainter p(getBuffer()->getBufAddr(),getRect());
	p.drawButton(0, 0, width(), height(), getName(), state);
	pressBuf = NULL;
	norBuf = NULL;
}


TPushButton::TPushButton(int32 x, int32 y, TImage* norImg ,TImage* pressImg ,  const char* name, TWidget* obj)
	//:TAbstractButton(x, y,norImg->imgW(),norImg->imgH(),name,obj)
	:TAbstractButton(x, y,MAX(norImg->imgW(),pressImg->imgW()),MAX(norImg->imgH(),pressImg->imgH()), name, obj)
{
	if(getParents() == NULL)
		pressBuf = new TBuffer(NULL, width() ,width(), height());
	else
	{
		pressBuf = new TBuffer(((TWidget*)getParents())->getBuffer()->getBufAddr(), ((TWidget*)getParents())->width() ,width(), height());
	}

	norBuf =  getBuffer();
	norImg->ImgLoad(0,0,getBuffer());
    delete norImg;

	pressImg->ImgLoad(0,0,pressBuf);
	delete pressImg;
	TBufPainter p(getBuffer()->getBufAddr(),getRect());
	p.drawCenterEnText(0,0, width(), height(), getName());
}

TPushButton::~TPushButton() 
{
	if(pressBuf)
	{
		setBuffer(norBuf);
		delete pressBuf;
	}
};

void TPushButton::sig_depress(int32 d1, int32 d2)
{
	if(pressBuf)
	{
		setBuffer(pressBuf);
		TBufPainter p(getBuffer()->getBufAddr(),getRect());
		p.drawCenterEnText(0,0, width(), height(), getName());
		refresh();
	}
	else
	{
		// TPainter p(getInvalidList(),getPaintInvaild());
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
	if(pressBuf)
	{
		setBuffer(norBuf);
		TBufPainter p(getBuffer()->getBufAddr(),getRect());
		p.drawCenterEnText(0,0, width(), height(), getName());
		refresh();
	}
	else
	{
		// TPainter p(getInvalidList(),getPaintInvaild());
		TBufPainter p(getBuffer()->getBufAddr(),getRect());
		p.drawButton(0, 0, width(), height(), getName(), false);
		refresh();
	}
	state = false;
	callSlot((func)&TPushButton::sig_release,d1,d2);
}
void TPushButton::release()
{
	if(pressBuf)
	{
		setBuffer(norBuf);
		TBufPainter p(getBuffer()->getBufAddr(),getRect());
		p.drawCenterEnText(0,0, width(), height(), getName());
		refresh();
	}
	else
	{
		// TPainter p(getInvalidList(),getPaintInvaild());
		TBufPainter p(getBuffer()->getBufAddr(),getRect());
		p.drawButton(0, 0, width(), height(), getName(), false);
		refresh();
	}
	state = false;
}

void TPushButton::show()
{
	//TPainter p(getInvalidList(),getPaintInvaild());
	refresh();
}
