#include "TWidget/TRadioButton.h"


TRadioButton::TRadioButton(int32 x, int32 y, int32 w, int32 h, const char* name, TWidget* obj)
	:TAbstractButton(x, y, w, h, false,name, obj)
{
	next = this;
	selected = false;

	TBufPainter p(getBuffer()->getBufAddr(),getRect());
	p.drawRadio(0, 0, width(), height(), getName(), selected, state, ((TWidget*)getParents())->getBackColor());
}


TRadioButton::TRadioButton(TRect rect,TImage norImg,TImage selImg, const char* name, TWidget* obj)
	:TAbstractButton(rect.x(),rect.y(),rect.width(),rect.height(), true,name, obj)
{
	next = this; 
	selected = false; 

	norImg.ImgLoad(0,(height() - norImg.imgH())/2,norBuf);
	TBufPainter p1(norBuf->getBufAddr(),getRect());
	p1.drawEnAlignText(norImg.imgW(),0, getName(),ALIGN_MID_LEFT);

	selImg.ImgLoad(0,(height() - selImg.imgH())/2,selBuf);
	TBufPainter p2(selBuf->getBufAddr(),getRect());
	p2.drawEnAlignText(selImg.imgW(),0, getName(),ALIGN_MID_LEFT);

}

TRadioButton::~TRadioButton()
{ 	
	delRadio(); 
}

void TRadioButton::sig_depress(int32 d1, int32 d2)
{
	if(haveImg)
	{
	}
	else
	{
		//TPainter p(getInvalidList(),getPaintInvaild());
		TBufPainter p(getBuffer()->getBufAddr(),getRect());
		p.drawRadio(0, 0, width(), height(), getName(), selected, true,((TWidget*)getParents())->getBackColor());
		refresh();
	}
	state = true;
	callSlot((func)&TRadioButton::sig_depress,d1,d2);
}


void TRadioButton::sig_release(int32 d1, int32 d2)
{
	changeOtherSelect();
	if(haveImg)
	{
		if(selected)
			setBuffer(selBuf);
		else
			setBuffer(norBuf);
		refresh();
	}
	else
	{
		//TPainter p(getInvalidList(),getPaintInvaild());
		TBufPainter p(getBuffer()->getBufAddr(),getRect());
		p.drawRadio(0, 0, width(), height(), getName(), selected, false, ((TWidget*)getParents())->getBackColor());
		refresh();
	}
	state = false;
	callSlot((func)&TRadioButton::sig_release, d1, d2);
}

void TRadioButton::release()
{
	if(haveImg)
	{
		if(selected)
			setBuffer(selBuf);
		else
			setBuffer(norBuf);
		refresh();
	}
	else
	{
		//TPainter p(getInvalidList(),getPaintInvaild());
		TBufPainter p(getBuffer()->getBufAddr(),getRect());
		p.drawRadio(0, 0, width(), height(), getName(), selected, false, ((TWidget*)getParents())->getBackColor());
		refresh();
	}
	state = false;
}


void TRadioButton::show()
{
	//TPainter p(getInvalidList(),getPaintInvaild());
	//TBufPainter p(getBuffer()->getBufAddr(),getRect());
	//p.drawRadio(0, 0, width(), height(), getName(), selected, state, ((TWidget*)getParents())->getBackColor());
	refresh();
}


void TRadioButton::changeOtherSelect()
{
	changeSelected();
	if (selected)//若为true 改变其他的情况;
	{
		TRadioButton* radio = this;
		while (radio->next != this)
		{	
			radio = radio->next;
			radio->selected = false;
			radio->release();
		}
	}
}

void TRadioButton::addNextRadio(TRadioButton* radio)
{
	radio->next = this->next;
	this->next = radio;
}

void TRadioButton::delRadio()
{
	if (this->next == this)
		return;
	TRadioButton* radio = this;
	while (radio->next != this)
		radio = radio->next;
	radio->next = this->next;
	this->next = this;
}
