#include "TWidget/TRadioButton.h"


TRadioButton::TRadioButton(int32 x, int32 y, int32 w, int32 h, const char* name, TWidget* obj)
	:TAbstractButton(x, y, w, h, name, obj)
{
	norImg = NULL;
	selImg = NULL;
	next = this;
	selected = false;

	TBufPainter p(getBuffer()->getBufAddr(),getRect());
	p.drawRadio(0, 0, width(), height(), getName(), selected, state, ((TWidget*)getParents())->getBackColor());
}


TRadioButton::TRadioButton(TRect* rect,TImage* norImg,TImage* selImg, const char* name, TWidget* obj)
	:TAbstractButton(rect->left(), rect->top(), rect->width(), rect->height(), name, obj)
{
	next = this; 
	selected = false; 
	delete rect;

	this->norImg = norImg;
	this->selImg = selImg;

	norImg->ImgLoad(0,(height() - norImg->imgH())/2,getBuffer());
	TBufPainter p(getBuffer()->getBufAddr(),getRect());
	p.drawEnText(norImg->imgW(),0, getName());
}

TRadioButton::~TRadioButton()
{ 	
	if(norImg)
		delete norImg;
	if(selImg)
		delete selImg;
	delRadio(); 
}

void TRadioButton::sig_depress(int32 d1, int32 d2)
{
	if(norImg)
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
	if(norImg)
	{
		if(selected)
			selImg->ImgLoad(0,(height() - selImg->imgH())/2,getBuffer());
		else
			norImg->ImgLoad(0,(height() - norImg->imgH())/2,getBuffer());
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
	if(norImg)
	{
		if(selected)
			selImg->ImgLoad(0,(height() - selImg->imgH())/2,getBuffer());
		else
			norImg->ImgLoad(0,(height() - norImg->imgH())/2,getBuffer());
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
