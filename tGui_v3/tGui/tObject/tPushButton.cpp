#include "tObject/tPushButton.h"


void tPushButton::depress_sig()
{
	tPainter p;
	p.drawButton(x(), y(), width(), height(), getName(), true);
	if (getConnections())
	{
		int num = getConnections()->find((func)(&tPushButton::depress_sig));
		if(num >=0 )
			getConnections()->at(num)->active();
	}
}

void tPushButton::release_sig()
{
	tPainter p;
	p.drawButton(x(), y(), width(), height(), getName(), false);
	if (getConnections())
	{
		int num = getConnections()->find((func)(&tPushButton::release_sig));
		if (num >= 0)
			getConnections()->at(num)->active();
	}
}

void tPushButton::show()
{
	tPainter p;
	p.drawButton(x(), y(), width(), height(), getName());
}

void tPushButton::regist(tObject* obj)
{
	obj->addChild(this);
	this->setParent(obj);
}
void tPushButton::logout(tObject* obj)
{
	obj->remChild(this);
	this->setParent(nullptr);
}

void tPushButton::touchPressEvent(tTouchEvent *e)
{
	if (isArea(e->x(), e->y()))
	{
		depress_sig();
	}
};

void tPushButton::touchReleaseEvent(tTouchEvent *e)
{
	if (isArea(e->x(), e->y()))
	{
		release_sig();
	}
};

void tPushButton::touchClickEvent(tTouchEvent *) 
{

};

void tPushButton::touchMoveEvent(tTouchEvent *) 
{

};