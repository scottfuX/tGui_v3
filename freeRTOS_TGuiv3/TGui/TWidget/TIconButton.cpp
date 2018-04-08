#include "TWidget/TIconButton.h"



TIconButton::TIconButton(int32 x, int32 y,TImage* norImg ,TImage* selImg ,  const char* name, TWidget* obj)
	:TAbstractButton(x, y,norImg->imgW() ,norImg->imgH()  + TFON_HEIGHT,true, name, obj)
{
	this->norImg = norImg;
	this->selImg = selImg;
	
	imgLoadInterface(0,0,norImg);
	getBuffer()->obPareBack(getPareBufCorreAddr(),((TWidget*)getParents())->width(),0 ,norImg->imgH() ,width(),TFON_HEIGHT);
	TBufPainter p(getBuffer()->getBufAddr(),getRect());
	p.drawCenterText(0,norImg->imgH() , width(), TFON_HEIGHT, getName());
}

TIconButton::~TIconButton() 
{
};

void TIconButton::sig_depress(int32 d1, int32 d2)
{
	if(selImg)
	{
		imgLoadInterface(0,0,selImg);
		getBuffer()->obPareBack(getPareBufCorreAddr(),((TWidget*)getParents())->width(),0 ,selImg->imgH(),width(),TFON_HEIGHT);
		TBufPainter p(getBuffer()->getBufAddr(),getRect());
		p.drawCenterText(0,selImg->imgH(), width(), TFON_HEIGHT, getName());
	}
	else
	{	
		TSize size1(((TWidget*)getParents())->getBuffer()->getBufW(),((TWidget*)getParents())->getBuffer()->getBufH());
		TSize size2(getBuffer()->getBufW(),getBuffer()->getBufH());

		norImg->blendPoint(0x84848484,getPareBufCorreAddr(),&size1,getBuffer()->getBufAddr(),&size2);

		getBuffer()->obPareBack(getPareBufCorreAddr(),((TWidget*)getParents())->width(),0 ,norImg->imgH(),width(),TFON_HEIGHT);
		TBufPainter p(getBuffer()->getBufAddr(),getRect());
		p.drawCenterText(0,norImg->imgH(), width(), TFON_HEIGHT, getName());
	}
	
    
    refresh();
	state = true;
	callSlot((func)&TIconButton::sig_depress,d1,d2);
}

void TIconButton::sig_release(int32 d1, int32 d2)
{
	imgLoadInterface(0,0,norImg);
	getBuffer()->obPareBack(getPareBufCorreAddr(),((TWidget*)getParents())->width(),0 ,norImg->imgH(),width(),TFON_HEIGHT);
	TBufPainter p(getBuffer()->getBufAddr(),getRect());
	p.drawCenterText(0,norImg->imgH() , width(), TFON_HEIGHT, getName());
    
    refresh();
	state = false;
	callSlot((func)&TIconButton::sig_release,d1,d2);
}

void TIconButton::release()
{
	imgLoadInterface(0,0,norImg);
	getBuffer()->obPareBack(getPareBufCorreAddr(),((TWidget*)getParents())->width(),0 ,norImg->imgH(),width(),TFON_HEIGHT);
	TBufPainter p(getBuffer()->getBufAddr(),getRect());
	p.drawCenterText(0,norImg->imgH() , width(), TFON_HEIGHT, getName());
    
    refresh();
	state = false;
}

void TIconButton::show()
{
	refresh();
}
