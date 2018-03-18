#include "TWidget/TRadioButton.h"



TRadioButton::TRadioButton(int32 x, int32 y, int32 w, int32 h, const char* name, TWidget* obj)
	:TAbstractButton(x, y, w, h, name, obj)
{
	next = this;
	selected = false;

	TBufPainter p(getBuffer()->getBufAddr(),getRect());
	p.drawRadio(0, 0, width(), height(), getName(), selected, state, ((TWidget*)getParents())->getBackColor());
}


void TRadioButton::sig_depress(int32 d1, int32 d2)
{
	//TPainter p(getInvalidList(),getPaintInvaild());
	TBufPainter p(getBuffer()->getBufAddr(),getRect());
	p.drawRadio(0, 0, width(), height(), getName(), selected, true,((TWidget*)getParents())->getBackColor());
	refresh();
	state = true;
	callSlot((func)&TRadioButton::sig_depress,d1,d2);
}


void TRadioButton::sig_release(int32 d1, int32 d2)
{
	changeOtherSelect();
	//TPainter p(getInvalidList(),getPaintInvaild());
	TBufPainter p(getBuffer()->getBufAddr(),getRect());
	p.drawRadio(0, 0, width(), height(), getName(), selected, false, ((TWidget*)getParents())->getBackColor());
	refresh();
	state = false;
	callSlot((func)&TRadioButton::sig_release, d1, d2);
}

void TRadioButton::release()
{
	//TPainter p(getInvalidList(),getPaintInvaild());
	TBufPainter p(getBuffer()->getBufAddr(),getRect());
	p.drawRadio(0, 0, width(), height(), getName(), selected, false, ((TWidget*)getParents())->getBackColor());
	refresh();
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
