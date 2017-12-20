#include "tObject/tPushButton.h"


void tPushButton::depress()
{
	

}

void tPushButton::release()
{


}

void tPushButton::show()
{
	tPainter p;
	p.drawButton(x(), y(), width(), height(), "btn", 3);
}

void tPushButton::regist(tObject* obj)
{
	obj->addChild(this);
	this->setParent(obj);
	show();
}
void tPushButton::logout(tObject* obj)
{
	obj->remChild(this);
	this->setParent(nullptr);
}

void tPushButton::touchPressEvent(tTouchEvent *)
{
	tPainter p;
	p.drawButton(x(), y(), width(), height(), "btn", 3,true);
};

void tPushButton::touchReleaseEvent(tTouchEvent *)
{
	tPainter p;
	p.drawButton(x(), y(), width(), height(), "btn", 3, false);
};

void tPushButton::touchClickEvent(tTouchEvent *) 
{

};

void tPushButton::touchMoveEvent(tTouchEvent *) 
{

};