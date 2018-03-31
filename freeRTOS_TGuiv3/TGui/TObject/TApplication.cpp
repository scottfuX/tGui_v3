#include "TObject/TApplication.h"


TApplication::TApplication(TDirver* d)
{
	widroot = NULL;
	windList = new TWidgetList();
	dirver = d;
	event = NULL;
	SHARE_SIGNAL_OBJ = 0;
	SHARE_SIGNAL_DATA = 0;
}

TApplication::~TApplication()
{
	destroy();
	windList->clear();
	delete windList;
}

void TApplication::addWindow(TWidget* window)
{
	if(windList->count() == 0)
		widroot = window;
	windList->append(window);
};

void TApplication::remWindow(TWidget* window)
{
	windList->remove(window);
	delete window;
}

void TApplication::chgWidRoot(TWidget* window)
{
	if(windList->find(window) == -1)
		windList->append(window);
	widroot = window;
	show();
}

void TApplication::chgWidRoot()
{//默认回到第一个
	widroot = windList->getFirst();
	if(widroot)
		show();
}

void TApplication::delWidRoot()
{//删除widroot所在的，改变
	remWindow(widroot);
	chgWidRoot();
}

void TApplication::run()
{
	while (1)
	{
		translate();//获取/翻译数据
		distribute();//分发数据
	}
}

void TApplication::suspension()
{
}

void TApplication::show()
{
	widroot->showAll();
}


void TApplication::emit(TObject* obj)
{
	obj->eventFilter(getEvent());
}


void TApplication::setSignal(TWidget* wid,int32 data)
{
	SHARE_SIGNAL_OBJ = wid;
	SHARE_SIGNAL_DATA = data;
}


//----------------private--------------


void TApplication::visitAll(TObject* obj)
{
	emit(obj);//emit event
	TObjList* list = obj->getChildList();
	TObject* temp; 
	tLNode<TObject*> * tnode;
	int32 tindex;
	if (list)
	{
		temp = list->getFirst();
		//保存现场
		tnode = list->getCurrent();
		tindex = list->getCurIndex();
		//if this event is not all emit && event is not in this's area 
		// stop to visit son
		visitAll(temp);
		
		//恢复现场
		list->setCurIndex(tindex);
		list->setCurNode(tnode);
		while (temp = list->getNext())
		{//保存现场
			tnode = list->getCurrent();
			tindex = list->getCurIndex();
			visitAll(temp);
			//恢复现场
			list->setCurIndex(tindex);
			list->setCurNode(tnode);
		}
	}
}

void TApplication::translate()
{
	//printf("\r\nin SHARE Deal With! %x\r\n",SHARE_SIGNAL_OBJ);
	if(SHARE_SIGNAL_OBJ)
	{ //有内部上传事件
		switch(SHARE_SIGNAL_DATA)
		{
			case Event_None: break;
			case Event_Close:
			{
				printf("\r\ntype = %d,close\r\n", SHARE_SIGNAL_DATA);
				event =  new TCloseEvent(SHARE_SIGNAL_DATA);
			}break;
			case Event_Show:
			{
				chgWidRoot((TWidget*)SHARE_SIGNAL_OBJ);
			}
			default:break;
		}
		SHARE_SIGNAL_OBJ = NULL;
		SHARE_SIGNAL_DATA = 0;
	}
	else
	{//驱动事件
		dirver->obtainData();//获取数据
		switch (dirver->getType())
		{
			//特殊情况
			case Event_None: break;
			default:
			{//默认直接发送类型，和数据即可
				printf("\r\ntype = %d\r\n", dirver->getType());
				TPoint p(dirver->dataFront(), dirver->dataBack());
				event =  new TTouchEvent(dirver->getType(), (const TPoint)p);
			}break;
		}
	}
}

void TApplication::distribute()
{
	if (event) 
	{
		visitAll(widroot);
		if(event->type() == Event_Close)
		{
			delWidRoot();
		}
		delete event;
		event = NULL;
	}
}

void TApplication::distribute(TObject* obj)
{
	if (event)
	{
		visitAll(obj);
		if(event->type() == Event_Close)
		{
			delWidRoot();
		}
		delete event;
		event = NULL;
	}
}

void TApplication::destroy()
{
	delete widroot;
}

