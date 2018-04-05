#include "TWidget/TWidget.h"


TWidget::TWidget(int32 x, int32 y, int32 w, int32 h, const char* n, TWidget* obj,bool needBuf):TObject(n,obj)
{
	rect = new TRect();
	offsetWH = new TSize();
	invalidList = NULL;
	//paintInvaild = NULL;
	setX(x);
	setY(y);
	setW(w);
	setH(h);
	backColor = WHITE;
	offsetWH->setWidth(this->x() - obj->x() );//修改 偏移
	offsetWH->setHeight(this->y() - obj->y() );
	
	chgPareInValid();
	
	if(needBuf)
	{
		widgetBuf = new TBuffer(w , h);
	}
	else
	{
		widgetBuf = NULL;
	}

	// if (getParents())
	// {
	// 	backColor = ((TWidget*)getParents())->getBackColor();
	// 	if (((TWidget*)getParents())->getIsVariable())
	// 	{
	// 		isVariable = true;
	// 		chgPareInValid();//若父类可变，则为父类添加无效区域，保证变化时不闪屏
	// 	}

	// }
	// else
	// {
	// 	backColor = WHITE;
	// 	isVariable = false; //默认不可变，除非父类为可变
	// }
	
}


TWidget::TWidget(TRect r, const char* n, TWidget* obj,bool needBuf):TObject(n,obj)
{
	rect = new TRect();
	offsetWH = new TSize();
	invalidList = NULL;
	//paintInvaild = NULL;
	setX(r.x());
	setY(r.y());
	setW(r.width());
	setH(r.height());
	backColor = WHITE;
	offsetWH->setWidth(this->x() - obj->x());//修改 偏移
	offsetWH->setHeight(this->y() - obj->y());
	
	chgPareInValid();
	
	if(needBuf)
	{
		widgetBuf = new TBuffer(r.width() , r.height());
	}
	else
	{
		widgetBuf = NULL;
	}	
}

TWidget::~TWidget() 
{
	if(getParents())//删除父亲的剪切区域
		((TWidget*)getParents())->invalidList->remove(this);
	if(invalidList) //清空自己的剪切区域
		invalidList->clear();
	delete rect; 
	delete offsetWH;
	delete invalidList;
	delete widgetBuf;
}

bool TWidget::isInRealArea(int32 xt, int32 yt)
{
	if (isInArea(xt,yt))
	{
		if (invalidList)
		{
			TWidget * tmp;
			tmp = invalidList->getFirst();
			if (tmp->isInArea(xt, yt))
				return false;
			while ((tmp = invalidList->getNext())!=0)
				if (tmp->isInArea(xt, yt))
					return false;
		}
		return true;
	}
	return false;
}

void TWidget::refresh()
{
	rectCut(getRect());
}

//与图像加载函数对接的函数
//x,y  加载到内存的位置  
//rectFrom 需要加载多大
void TWidget::imgLoadInterface(int32 x,int32 y,TImage* img,TRect* rectFrom ,uint8 readType) 
{
	uint8* addr = getBuffer()->getBufAddr() + (x + y * width())* GUI_PIXELSIZE;
	TSize size2(getBuffer()->getBufW() , getBuffer()->getBufH());
	if(readType == 0) //从父亲buf那读点
	{
		uint8* pareAddr = ((TWidget*)getParents())->getBuffer()->getBufAddr() + \
			(getOffsetWH()->width() + x +  (getOffsetWH()->height() + y) * ((TWidget*)getParents())->width()) * GUI_PIXELSIZE;
		TSize size1(((TWidget*)getParents())->getBuffer()->getBufW(),((TWidget*)getParents())->getBuffer()->getBufH());
		img->imgLoad(pareAddr,&size1,addr,&size2,rectFrom);
	}
	else if(readType == 1) //从自己buf那读点
	{
		img->imgLoad(addr,&size2,addr,&size2,rectFrom);
	}
	else if(readType == 2) //从显存buf那读点
	{
        uint32 pareAddr = GUI_FG_BUFADDR + GUI_PIXELSIZE * (getRect()->x() + x + (getRect()->y() + y)*GUI_WIDTH )   ;
        TSize size1(GUI_WIDTH,GUI_HIGH);
        img->imgLoad((uint8*)pareAddr,&size1,addr,&size2,rectFrom);
	}
}



void TWidget::showAll(TWidget* obj)
{
	obj->show();
	TObjList* list = obj->getChildList();
	TObject* tmp;
	if (list)
	{
		tmp = list->getFirst();
		showAll((TWidget*)tmp);
		while ((tmp = list->getNext())!=0)
		{
			showAll((TWidget*)tmp);
		}
	}
}

//清除在显存中的自己
void TWidget::cleanShowed(TRect* rect)
{	//拿父亲去覆盖自己
	TWidget* pare = (TWidget*) getParents();
	if(pare)
		pare->repaintInvaild(rect,NULL);
}

//改变子类的XY值，保证和自己同步
void TWidget::chgChildsXY(TWidget* widget)
{
	TObjList* list = widget->getChildList();
	TWidget* temp;
	if (list)
	{
		temp = (TWidget*)list->getFirst();
		temp->getRect()->moveTopLeft(widget->x() + temp->getOffsetWH()->width(),
			widget->y() + temp->getOffsetWH()->height());
		chgChildsXY(temp);
		while ((temp = (TWidget*)list->getNext())!=0)
		{
			temp->getRect()->moveTopLeft(widget->x() + temp->getOffsetWH()->width(),
				widget->y() + temp->getOffsetWH()->height());
			chgChildsXY(temp);
		}
	}
}


//改变无效区，如果覆盖了，就增加无效区，如果不覆盖了，就删除无效区
void TWidget::chgInValid(TRect* area1, TRect* area2)
{
	TWidget* pare = (TWidget*)getParents();
	if (pare)
	{
		pare->addAchgInvalid(this, area1, area2);//加/修补 父亲 的无效区
		tLNode<TObject*> * node = pare->unlink(this);//先断开连接
		chgAllInValid(pare->getChildList(), this,area1,area2);//遍历增加兄弟的无效区
		pare->relink(node);//接上连接
	}
}

//在父亲无效区列表中加入自己
void TWidget::chgPareInValid()
{
	if (getParents())
	{
		((TWidget*)getParents())->addAchgInvalid(this,NULL,NULL);
	}
}

//增加无效区
void  TWidget::addAchgInvalid(TWidget* widget, TRect* area1, TRect* area2)
{
	if(invalidList)
	{ 
		if (invalidList->find(widget) == -1) //如果 ‘无效区链表’ 中没有这个widget对象 添加对象 
		{
			invalidList->append(widget);
		}
		else								//有则修改其覆盖区域
		{
			repaintInvaild(area1, area2);//修补无效区
		}
	}
	else
	{
		invalidList = new TWidgetList();
		invalidList->append(widget);
	}
}

//删除无效区
void  TWidget::remInvalid(TWidget* widget)
{
	if(invalidList)
		invalidList->remove(widget);
}

//重绘更改后剩下的区域
void TWidget::repaintInvaild(TRect* area1, TRect* area2)
{
	if (area1&&area1->isValid())
	{	
		//进行绘画
		TRect tmp;
		tmp.setLeft ( MAX(area1->left(), rect->left()));
		tmp.setRight ( MIN(area1->right(), rect->right()));
		tmp.setTop  (MAX(area1->top(), rect->top()));
		tmp.setBottom (MIN(area1->bottom(), rect->bottom()));
		if(tmp.isValid())
			rectCut(&tmp);
	}
	if(area2&&area2->isValid())
	{
		//进行绘画
		TRect tmp;
		tmp.setLeft ( MAX(area2->left(), rect->left()));
		tmp.setRight ( MIN(area2->right(), rect->right()));
		tmp.setTop  (MAX(area2->top(), rect->top()));
		tmp.setBottom (MIN(area2->bottom(), rect->bottom()));
		if(tmp.isValid())
			rectCut(&tmp);
	}	
}


//遍历所有 加/减/修补无效区 
void TWidget::chgAllInValid(TObjList* chdlist, TWidget* widget, TRect* area1, TRect* area2)
{
	int32 tindex;
	tLNode<TObject*> * tnode;
	if (chdlist)
	{  //找自己的兄弟，并addInvali(),然后递归下去
		TWidget* temp = ((TWidget*)chdlist->getFirst());
		//保存现场
		tnode = chdlist->getCurrent();
		tindex = chdlist->getCurIndex();
		if (temp->getRect()->intersects(*(widget->getRect())))//看看是否在里面
		{
			temp->addAchgInvalid(widget, area1, area2);//加/修补无效区
			chgAllInValid(temp->getChildList(), widget, area1, area2);
		}
		else
		{
			temp->remInvalid(widget);//减无效区
			chgAllInValid(temp->getChildList(), widget, area1, area2);
		}
		//恢复现场
		chdlist->setCurIndex(tindex);
		chdlist->setCurNode(tnode);
		while ((temp = ((TWidget*)chdlist->getNext()))!=0)
		{//保存现场
			tnode = chdlist->getCurrent();
			tindex = chdlist->getCurIndex();
			if (temp->getRect()->intersects(*(widget->getRect())))
			{
				temp->addAchgInvalid(widget, area1, area2);//加/修补无效区
				chgAllInValid(temp->getChildList(), widget, area1, area2);
			}
			else
			{
				temp->remInvalid(widget);//减无效区
				chgAllInValid(temp->getChildList(), widget, area1, area2);
			}//恢复现场
			chdlist->setCurIndex(tindex);
			chdlist->setCurNode(tnode);
		}
	}
}


// //加上边界无效区
// void	setIsVariable(bool statVari)
// {
// 	isVariable = statVari;
// 	if(statVari)//可变的
// 	{
// 		TRect(- GUI_WIDTH,- GUI_HIGH,GUI_WIDTH,GUI_HIGH * 2);
// 		TRect(0,- GUI_HIGH,GUI_WIDTH * 2,GUI_HIGH);
// 		TRect(GUI_WIDTH,0,GUI_WIDTH ,GUI_HIGH * 2);
// 		TRect(- GUI_WIDTH,GUI_HIGH,GUI_WIDTH * 2,GUI_HIGH );
// 	}
// 	TWidget* tmp;
// 	if (getChildList())
// 	{
// 		tmp = (TWidget*)getChildList()->getFirst();
// 		tmp->setIsVariable(statVari);
// 		while ((tmp = (TWidget*)getChildList()->getNext())!=0)
// 		{
// 			tmp->setIsVariable(statVari);
// 		}
// 	}
// }


void TWidget::eventFilter(TEvent* e)
{
	switch (e->type())
	{
		case  Event_None: {}break;
		case  Event_Timer: {}break;
		case  Event_TouchPress:{touchPressEvent((TTouchEvent *)e) ;}break;
		case  Event_TouchRelese: {touchReleaseEvent((TTouchEvent *)e);}break;
		case  Event_TouchClick: {touchClickEvent((TTouchEvent *)e);}break;
		case  Event_TouchMove: {touchMoveEvent((TTouchEvent *)e);}break;
		case  Event_MousePress: {mousePressEvent((TMouseEvent *)e);}break;
		case  Event_MouseRelease: {mouseReleaseEvent((TMouseEvent *)e);}break;
		case  Event_MouseClick: {mouseDoubleClickEvent((TMouseEvent *)e);}break;
		case  Event_MouseDblClick: {mouseClickEvent((TMouseEvent *)e);}break;
		case  Event_MouseMove: {mouseMoveEvent((TMouseEvent *)e);}break;
		case  Event_KeyPress: {keyPressEvent((TKeyEvent *)e);}break;
		case  Event_KeyRelease: {keyReleaseEvent((TKeyEvent *)e);}break;
		case  Event_KeyClick: {	}break;
		case  Event_FocusIn: {focusInEvent((TFocusEvent *)e); }break;
		case  Event_FocusOut: {focusOuTEvent((TFocusEvent *)e);}break;
		case  Event_Enter: {enterEvent(e);}break;
		case  Event_Leave: {leaveEvent(e);}break;
		case  Event_Paint: {painTEvent((TPainTEvent *)e);}break;
		case  Event_Move: {moveEvent((TMoveEvent *)e);}break;
		case  Event_Resize: {resizeEvent((TResizeEvent *)e);}break;
		case  Event_Create: {}break;
		case  Event_Destroy: {}break;
		case  Event_Show: {}break;
		case  Event_Hide: {}break;
		case  Event_Close: {closeEvent((TCloseEvent *)e); }break;
		case  Event_User: {}break;
		default:
			break;
	}
}


/*------------------------------剪切域-------------------------------*/
void TWidget::rectCut(TRect* srcRect)
{
	if (!srcRect)
		return;
	TRect rect(0,0,-1,-1);
	if (invalidList && invalidList->getFirst())//若无效列表存在，且当前的位置有数据
	{//这里等于是真的赋值么？
		rect = srcRect->intersect(*invalidList->getCurrent()->getData()->getRect());//进行交集
		if (!rect.isValid())
		{
			while (invalidList->getNext())//继续遍历查看覆盖区
			{
				TWidget* w = invalidList->getCurrent()->getData();
				rect = srcRect->intersect(*w->getRect());
				if (rect.isValid())//是覆盖区
					break;
			}
		}
	}
	if (rect.isValid())//这个是无效区的矩形
	{//保存现场
		TRect tmp;
		/*//Area of up
		*|--------1-------| 5个矩形----进行递归
		*|--|----------|--|
		*|	| invlidal |  |
		*|--|----------|--|
		*|----------------|
		*/
		if (srcRect->top() < rect.top())
		{//恢复现场
			tmp.setLeft(srcRect->left());
			tmp.setTop(srcRect->top());
			tmp.setRight(srcRect->right());
			tmp.setBottom(rect.top()-1);
			rectCut(&tmp);
		}

		/*//Area of left
		*|----------------| 5个矩形----进行递归
		*|--|----------|--|
		*|2	| invlidal |  |
		*|--|----------|--|
		*|----------------|
		*/
		if (srcRect->left() < rect.left())
		{//恢复现场
			tmp.setLeft(srcRect->left());
			tmp.setTop(rect.top());
			tmp.setRight(rect.left()-1);
			tmp.setBottom(rect.bottom());
			rectCut(&tmp);
		}

		/*//Area of right
		*|----------------| 5个矩形----进行递归
		*|--|----------|--|
		*|	| invlidal |3 |
		*|--|----------|--|
		*|----------------|
		*/
		if (rect.right() < srcRect->right())
		{//恢复现场
			tmp.setLeft(rect.right()+1);
			tmp.setTop(rect.top());
			tmp.setRight(srcRect->right());
			tmp.setBottom(rect.bottom());
			rectCut(&tmp);
		}

		/*//Area of down
		*|----------------| 5个矩形----进行递归
		*|--|----------|--|
		*|	| invlidal |  |
		*|--|----------|--|
		*|-------4--------|
		*/
		if (rect.bottom() < srcRect->bottom())
		{//恢复现场
			tmp.setLeft(srcRect->left());
			tmp.setTop(rect.bottom()+1);
			tmp.setRight(srcRect->right());
			tmp.setBottom(srcRect->bottom());
			rectCut(&tmp);
		}
	}
	else//没有无效区矩形
	{
		//搬运TBuffer剪切后的区域 至 显存  
		getBuffer()->transform(x(),y(),srcRect);
	}
}


