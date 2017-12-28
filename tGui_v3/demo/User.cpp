#include "demo\User.h"



User::User(const char* n, tObject* obj):tWidget(n,obj)
{
	setX(0);
	setY(0);
	setW(800);
	setH(480);
}

void User::show()
{
	tPainter p;
	p.setColors(getBackColor(), getBackColor());
	p.drawFullRect(x(),y(),width(),height());
}

