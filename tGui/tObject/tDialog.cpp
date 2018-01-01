#include "tDialog.h"



tDialog::tDialog(int32 x, int32 y, int32 w, int32 h, const char* n, tWidget* obj)
	:tWidget(x, y, w, h, n, obj)
{
	contactOffsetW = -1;
	contactOffsetH = -1;
	preX = -1;
	preY = -1;
	state = false;
	hasFocus = true;
	setBackColor(MIDLIGHT);
}

tDialog::~tDialog()
{

}

void tDialog::show()
{
	tPainter p(getInvalidList(),getPaintInvaild());
	p.drawDialog(x(), y(), width(), height(), getName(), hasFocus, getBackColor());
}

void tDialog::touchPressEvent(tTouchEvent *e)
{
	if (isInRealArea(e->x(), e->y()))
	{
		//在区域内，且之前为失去焦点的，重新加上焦点
		if (!hasFocus)
		{
			state = true;
			hasFocus = true;
			tPainter p(getInvalidList(),getPaintInvaild());
			p.drawDialogTitle(x(), y(), width(), getName(), true);
		}
		if ( e->x() < (x() + width()) &&  e->y() < (y() + WIN_TITLE_H))
		{
			state = true;
			contactOffsetW = e->x() - x();
			contactOffsetH = e->y() - y();
			preX = x();
			preY = y();
		}
		if (getInvalidList())//被激活，且有覆盖区
		{
			getInvalidList()->clear();//清理覆盖区
			tObjList* list = getChildList(); //这里只查看子类的没有递归查看子类
			if (list)	
			{
				tWidget* tmp;
				tmp = (tWidget*)list->getFirst();
				tmp->getInvalidList()->clear();
				while (tmp = (tWidget*)list->getNext())
					tmp->getInvalidList()->clear();
			}
			showAll();//重绘  -------保证在最顶端
		}
	}
	else if(hasFocus)
	{
		hasFocus = false;
		tPainter p(getInvalidList(), getPaintInvaild());
		p.drawDialogTitle(x(), y(), width(), getName(), false);
	}
};

void tDialog::touchReleaseEvent(tTouchEvent *e)
{
	state = false;
	contactOffsetW = -1;
	contactOffsetH = -1;
};

void tDialog::touchMoveEvent(tTouchEvent *e)
{
	if (state && contactOffsetW != -1)
	{ 
		//改变自己的坐标
		getRect()->moveTopLeft(e->x() - contactOffsetW, e->y() - contactOffsetH);
		//遍历改变子类的坐标 
		chgChildsXY(this);
		
		//遍历画全部的子类的图像
		showAll();
		//遍历树，并设置覆盖情况  Zpos / 移动后面补充没加
		
		int32 nowX = e->x() - contactOffsetW;
		int32 nowY = e->y() - contactOffsetH;
		tRect r1(preX, preY, width(), height());//收集移动后留下的空隙为两个矩形构成
		tRect r2(nowX, nowY, width(), height());
		restRect(preX, preY, nowX, nowY, r1, r2);
		chgInValid(&r1, &r2);
		//告诉被覆盖的对象，重绘移动后的区域
		preX = nowX;
		preY =nowY;
	}
};


//移动后释放的区域  
void tDialog::restRect(int32 preX, int32 preY, int32 nowX, int32 nowY ,tRect &r1, tRect &r2)
{
	//chgInValid(&r1, NULL); //整个dialog刷新
	/*	|---------|
	|---|-----|	  |
	|	|	  |	  |
	|	|-----|---|
	|---------|*/
	if (nowX > preX)
	{
		if (preY > nowY)//右上方移动
		{
			r1.setLeft(preX);
			r1.setTop(preY);
			r1.setWidth(nowX - preX + 1);
			r1.setHeight(height() + nowY - preY + 1);
			r2.setLeft(preX);
			r2.setTop(nowY + height() - 1);
			r2.setWidth(width());
			r2.setHeight(preY - nowY + 1);
		}
		else //右下方移动
		{
			r1.setLeft(preX);
			r1.setTop(preY);
			r1.setWidth(width());
			r1.setHeight(nowY - preY + 1);
			r2.setLeft(preX);
			r2.setTop(nowY);
			r2.setWidth(nowX - preX + 1);
			r2.setHeight(height() + nowY - preY + 1);
		}
	}
	else
	{
		if (preY > nowY)//左上方移动
		{
			r1.setLeft(nowX + width() - 1);
			r1.setTop(preY);
			r1.setWidth(preX - nowX + 1);
			r1.setHeight(nowY + height() - preY + 1);
			r2.setLeft(preX);
			r2.setTop(nowY + height() - 1);
			r2.setWidth(width());
			r2.setHeight(preY - nowY + 1);
		}
		else   //左下发移动
		{
			r1.setLeft(preX);
			r1.setTop(preY);
			r1.setWidth(width());
			r1.setHeight(nowY - preY + 1);
			r2.setLeft(nowX + width() - 1);
			r2.setTop(nowY);
			r2.setWidth(preX - nowX + 1);
			r2.setHeight(preY + height() - nowY + 1);
		}
	}
}


