#include "TWidget/TIconButton.h"



TIconButton::TIconButton(int32 x, int32 y,TImage* norImg ,TImage* selImg ,  const char* name, TWidget* obj)
	:TAbstractButton(x, y,MAX(norImg->imgW() ,selImg->imgW()),MAX(norImg->imgH() ,selImg->imgH()) + TFON_HEIGHT,true, name, obj)
{
	this->norImg = norImg;
	this->selImg = selImg;
	
	imgLoadInterface(0,0,norImg);
	getBuffer()->obPareBack(getPareBufCorreAddr(),((TWidget*)getParents())->width(),0 ,MAX(norImg->imgH() ,selImg->imgH()),width(),TFON_HEIGHT);
	TBufPainter p(getBuffer()->getBufAddr(),getRect());
	p.drawCenterText(0,MAX(norImg->imgH() ,selImg->imgH()), width(), TFON_HEIGHT, getName());
}

TIconButton::~TIconButton() 
{
};

void TIconButton::sig_depress(int32 d1, int32 d2)
{
	imgLoadInterface(0,0,selImg);
	getBuffer()->obPareBack(getPareBufCorreAddr(),((TWidget*)getParents())->width(),0 ,MAX(norImg->imgH() ,selImg->imgH()),width(),TFON_HEIGHT);
	TBufPainter p(getBuffer()->getBufAddr(),getRect());
	p.drawCenterText(0,MAX(norImg->imgH() ,selImg->imgH()), width(), TFON_HEIGHT, getName());
    
    refresh();
	state = true;
	callSlot((func)&TIconButton::sig_depress,d1,d2);
}

void TIconButton::sig_release(int32 d1, int32 d2)
{
	imgLoadInterface(0,0,norImg);
	getBuffer()->obPareBack(getPareBufCorreAddr(),((TWidget*)getParents())->width(),0 ,MAX(norImg->imgH() ,selImg->imgH()),width(),TFON_HEIGHT);
	TBufPainter p(getBuffer()->getBufAddr(),getRect());
	p.drawCenterText(0,MAX(norImg->imgH() ,selImg->imgH()), width(), TFON_HEIGHT, getName());
    
    refresh();
	state = false;
	callSlot((func)&TIconButton::sig_release,d1,d2);
}

void TIconButton::release()
{
	imgLoadInterface(0,0,norImg);
	getBuffer()->obPareBack(getPareBufCorreAddr(),((TWidget*)getParents())->width(),0 ,MAX(norImg->imgH() ,selImg->imgH()),width(),TFON_HEIGHT);
	TBufPainter p(getBuffer()->getBufAddr(),getRect());
	p.drawCenterText(0,MAX(norImg->imgH() ,selImg->imgH()), width(), TFON_HEIGHT, getName());
    
    refresh();
	state = false;
}

void TIconButton::show()
{
	refresh();
}
