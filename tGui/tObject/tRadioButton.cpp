#include "tObject/tRadioButton.h"



tRadioButton::tRadioButton(int32 x, int32 y, int32 w, int32 h, const char* name,tObject* obj) 
	:tAbstractButton(x, y, w, h, name, obj)
{
	next = this;
	selected = false;
}


void tRadioButton::sig_depress(int32 d1, int32 d2)
{
	tPainter p;
	p.drawRadio(x(), y(), width(), height(), getName(), selected, true,((tWidget*)getParents())->getBackColor());
	state = true;
	callSlot((func)&tRadioButton::sig_depress,d1,d2);
}


void tRadioButton::sig_release(int32 d1, int32 d2)
{
	changeOtherSelect();
	tPainter p;
	p.drawRadio(x(), y(), width(), height(), getName(), selected, false, ((tWidget*)getParents())->getBackColor());
	state = false;
	callSlot((func)&tRadioButton::sig_release, d1, d2);
}

void tRadioButton::release()
{
	tPainter p;
	p.drawRadio(x(), y(), width(), height(), getName(), selected, false, ((tWidget*)getParents())->getBackColor());
	state = false;
}


void tRadioButton::show()
{
	tPainter p;
	p.drawRadio(x(), y(), width(), height(), getName(), selected, state, ((tWidget*)getParents())->getBackColor());
}


void tRadioButton::changeOtherSelect()
{
	changeSelected();
	if (selected)//若为true 改变其他的情况;
	{
		tRadioButton* radio = this;
		while (radio->next != this)
		{	
			radio = radio->next;
			radio->selected = false;
			radio->show();
		}
	}
}

void tRadioButton::addNextRadio(tRadioButton* radio)
{
	radio->next = this->next;
	this->next = radio;
}

void tRadioButton::delRadio()
{
	if (this->next == this)
		return;
	tRadioButton* radio = this;
	while (radio->next != this)
		radio = radio->next;
	radio->next = this->next;
	this->next = this;
}
