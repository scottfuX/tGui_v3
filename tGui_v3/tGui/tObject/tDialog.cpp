#include "tDialog.h"



tDialog::tDialog(int32 x, int32 y, int32 w, int32 h, const char* n, tObject* obj)
	:tWidget(x, y, w, h, n, obj)
{
	movOffsetW = -1;
	movOffsetH = -1;
	state = false;
	hasFocus = true;
}

tDialog::~tDialog()
{

}

void tDialog::show()
{
	tPainter p;
	p.drawDialog(x(), y(), width(), height(), getName(), true);
}

void tDialog::touchPressEvent(tTouchEvent *e)
{
	if (isArea(e->x(), e->y()))
	{//在区域内，且之前为失去焦点的，重新加上焦点
		if (!hasFocus)
		{
			state = true;
			hasFocus = true;
			tPainter p;
			p.drawDialogTitle(x(), y(), width(), getName(), true);
		}
		if ( e->x() < (x() + width()) &&  e->y() < (y() + WIN_TITLE_H))
		{
			state = true;
			movOffsetW = e->x() - x();
			movOffsetH = e->y() - y();
		}
	}
	else if(hasFocus)
	{
		hasFocus = false;
		tPainter p;
		p.drawDialogTitle(x(), y(), width(), getName(), false);
	}
};

void tDialog::touchReleaseEvent(tTouchEvent *e)
{
	state = false;
	movOffsetW = -1;
	movOffsetH = -1;
};

void tDialog::touchMoveEvent(tTouchEvent *e)
{
	if (state && movOffsetW != -1)
	{ 
		//改变自己的坐标
		setX(e->x() - movOffsetW);
		setY(e->y() - movOffsetH);
		//遍历改变子类的坐标


		//
		//遍历画全部的子类的图像
		show();
	}
};
