#include "tObject/tWidget.h"

tWidget::tWidget(const char* n, tWidget* obj) :tObject(n, obj)
{
	rect = new tRect();
	offsetWH = new tSize();
	invalidList = NULL;
	paintInvaild = NULL;
	setX(0);
	setY(0);
	setW(0);
	setH(0);	
	offsetWH->setWidth(obj->x() - this->x()  );//修改 偏移
	offsetWH->setHeight(obj->y() - this->y());
	if (getParents())
	{
		backColor = ((tWidget*)getParents())->getBackColor();
		if (((tWidget*)getParents())->getIsVariable())
		{
			isVariable = true;
			chgPareInValid();//若父类可变，则为父类添加无效区域，保证变化时不闪屏
		}

	}
	else
	{
		backColor = WHITE;
		isVariable = false; //默认不可变，除非父类为可变
	}
};

tWidget::tWidget(int32 x, int32 y, int32 w, int32 h, const char* n, tWidget* obj):tObject(n,obj)
{
	rect = new tRect();
	offsetWH = new tSize();
	invalidList = NULL;
	paintInvaild = NULL;
	setX(x);
	setY(y);
	setW(w);
	setH(h);
	backColor = WHITE;
	offsetWH->setWidth(obj->x() - this->x());//修改 偏移
	offsetWH->setHeight(obj->y() - this->y());
	if (getParents())
	{
		backColor = ((tWidget*)getParents())->getBackColor();
		if (((tWidget*)getParents())->getIsVariable())
		{
			isVariable = true;
			chgPareInValid();//若父类可变，则为父类添加无效区域，保证变化时不闪屏
		}

	}
	else
	{
		backColor = WHITE;
		isVariable = false; //默认不可变，除非父类为可变
	}
}


tWidget::~tWidget() {
	delete rect; 
	delete offsetWH;
	delete invalidList;
}

bool tWidget::isInRealArea(int32 xt, int32 yt)
{
	if (isInArea(xt,yt))
	{
		
		if (invalidList)
		{
			tWidget * tmp;
			tmp = invalidList->getFirst();
			if (tmp->isInArea(xt, yt))
				return false;
			while (tmp = invalidList->getNext())
				if (tmp->isInArea(xt, yt))
					return false;
		}
		return true;
	}
	return false;
}
bool tWidget::isInArea(int32 xt, int32 yt)
{
	if (xt >= x() && yt >= y() && xt < (x() + width()) && yt < (y() + height()))
		return true;
	return false;
}


void tWidget::showAll(tWidget* obj)
{
	obj->show();
	tObjList* list = obj->getChildList();
	tObject* tmp;
	if (list)
	{
		tmp = list->getFirst();
		showAll((tWidget*)tmp);
		while (tmp = list->getNext())
		{
			showAll((tWidget*)tmp);
		}
	}
}

void  tWidget::setIsVariable(bool statVari)
{
	isVariable = statVari;
	chgPareInValid();
	tWidget* tmp;
	if (getChildList())
	{
		tmp = (tWidget*)getChildList()->getFirst();
		tmp->setIsVariable(statVari);
		while (tmp = (tWidget*)getChildList()->getNext())
		{
			tmp->setIsVariable(statVari);
		}
			
	}
}

//改变子类的XY值，保证和自己同步
void tWidget::chgChildsXY(tWidget* widget)
{
	tObjList* list = widget->getChildList();
	tWidget* temp;
	if (list)
	{
		temp = (tWidget*)list->getFirst();
		temp->getRect()->moveTopLeft(widget->x() - temp->getOffsetWH()->width(),
			widget->y() - temp->getOffsetWH()->height());
		chgChildsXY(temp);
		while (temp = (tWidget*)list->getNext())
		{
			temp->getRect()->moveTopLeft(widget->x() - temp->getOffsetWH()->width(),
				widget->y() - temp->getOffsetWH()->height());
			chgChildsXY(temp);
		}
	}
}


//改变无效区，如果覆盖了，就增加无效区，如果不覆盖了，就删除无效区
void tWidget::chgInValid(tRect* area1, tRect* area2)
{
	tWidget* pare = (tWidget*)getParents();
	if (pare)
	{
		pare->addAchgInvalid(this, area1, area2);//加/修补无效
		tLNode<tObject*> * node = pare->unlink(this);//先断开连接
		chgAllInValid(pare->getChildList(), this,area1,area2);//遍历增加无效区
		pare->relink(node);//接上连接
	}
}

void tWidget::chgPareInValid()
{
	if (getParents())
	{
		((tWidget*)getParents())->addAchgInvalid(this,NULL,NULL);
	}
}

//增加无效区
void  tWidget::addAchgInvalid(tWidget* area, tRect* area1, tRect* area2)
{
	if(invalidList)
	{ 
		if (invalidList->find(area) == -1)
		{
			invalidList->append(area);
		}
		else
		{
			repaintInvaild(area1, area2);//修补无效区
		}
	}
	else
	{
		invalidList = new tWidgetList();
		invalidList->append(area);
	}
}

//删除无效区
void  tWidget::remInvalid(tWidget* area)
{
	if(invalidList)
		invalidList->remove(area);
}

//重绘更改后剩下的区域
void tWidget::repaintInvaild(tRect* area1, tRect* area2)
{
	if (area1&&area1->isValid())
	{	//增加修补区
		paintInvaild = area1;
		//进行绘画
		show();
		paintInvaild = NULL;
	}
	if(area2&&area2->isValid())
	{	paintInvaild = area2;
		//进行绘画
		show();
		//去除修补区
		paintInvaild = NULL;
	}	
	
}


//遍历所有 加/减/修补无效区 
void tWidget::chgAllInValid(tObjList* chdlist, tWidget* area, tRect* area1, tRect* area2)
{
	int32 tindex;
	tLNode<tObject*> * tnode;
	if (chdlist)
	{  //找自己的兄弟，并addInvali(),然后递归下去
		tWidget* temp = ((tWidget*)chdlist->getFirst());
		//保存现场
		tnode = chdlist->getCurrent();
		tindex = chdlist->getCurIndex();
		if (temp->getRect()->intersects(*(area->getRect())))//看看是否在里面
		{
			temp->addAchgInvalid(area, area1, area2);//加/修补无效区
			//temp->repaintInvaild(area1, area2);//修补无效区
			chgAllInValid(temp->getChildList(), area, area1, area2);
		}
		else
		{
			temp->remInvalid(area);//减无效区
			chgAllInValid(temp->getChildList(), area, area1, area2);
		}
		//恢复现场
		chdlist->setCurIndex(tindex);
		chdlist->setCurNode(tnode);
		while (temp = ((tWidget*)chdlist->getNext()))
		{//保存现场
			tnode = chdlist->getCurrent();
			tindex = chdlist->getCurIndex();
			if (temp->getRect()->intersects(*(area->getRect())))
			{
				temp->addAchgInvalid(area, area1, area2);//加/修补无效区
				chgAllInValid(temp->getChildList(), area, area1, area2);
			}
			else
			{
				temp->remInvalid(area);//减无效区
				chgAllInValid(temp->getChildList(), area, area1, area2);
			}//恢复现场
			chdlist->setCurIndex(tindex);
			chdlist->setCurNode(tnode);
		}
	}
}




void tWidget::eventFilter(tEvent* e)
{
	switch (e->type())
	{
		case  Event_None: {}break;
		case  Event_Timer: {}break;
		case  Event_TouchPress:{touchPressEvent((tTouchEvent *)e) ;}break;
		case  Event_TouchRelese: {touchReleaseEvent((tTouchEvent *)e);}break;
		case  Event_TouchClick: {touchClickEvent((tTouchEvent *)e);}break;
		case  Event_TouchMove: {touchMoveEvent((tTouchEvent *)e);}break;
		case  Event_MousePress: {mousePressEvent((tMouseEvent *)e);}break;
		case  Event_MouseRelease: {mouseReleaseEvent((tMouseEvent *)e);}break;
		case  Event_MouseClick: {mouseDoubleClickEvent((tMouseEvent *)e);}break;
		case  Event_MouseDblClick: {mouseClickEvent((tMouseEvent *)e);}break;
		case  Event_MouseMove: {mouseMoveEvent((tMouseEvent *)e);}break;
		case  Event_KeyPress: {keyPressEvent((tKeyEvent *)e);}break;
		case  Event_KeyRelease: {keyReleaseEvent((tKeyEvent *)e);}break;
		case  Event_KeyClick: {	}break;
		case  Event_FocusIn: {focusInEvent((tFocusEvent *)e); }break;
		case  Event_FocusOut: {focusOutEvent((tFocusEvent *)e);}break;
		case  Event_Enter: {enterEvent(e);}break;
		case  Event_Leave: {leaveEvent(e);}break;
		case  Event_Paint: {paintEvent((tPaintEvent *)e);}break;
		case  Event_Move: {moveEvent((tMoveEvent *)e);}break;
		case  Event_Resize: {resizeEvent((tResizeEvent *)e);}break;
		case  Event_Create: {closeEvent((tCloseEvent *)e); }break;
		case  Event_Destroy: {}break;
		case  Event_Show: {}break;
		case  Event_Hide: {}break;
		case  Event_Close: {}break;
		case  Event_User: {}break;
		default:
			break;
	}
}