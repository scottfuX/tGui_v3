#include "TObject/TApplication.h"


TApplication::TApplication(TWidget* r,TDirver* d)
{
	widroot = r;
	dirver = d;
	objNum = 1;
	event = NULL;
}

TApplication::~TApplication()
{
	destroy();
}

void TApplication::add(TObject* obj, TObject* parents)
{
	if (parents == NULL)
		parents = widroot;
	obj->setParent(parents);
	parents->addChild(obj);
	objNum++;
}

void TApplication::run()
{
	while (1)
	{
		translate(dirver);//获取/翻译数据
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

//----------------private--------------


void TApplication::visitAll(TObject* obj, TApplication* app)
{
	app->emit(obj);//emit event
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
		printf("%s\n", temp->getName());
		//if this event is not all emit && event is not in this's area 
		// stop to visit son
		visitAll(temp, app);
		
		//恢复现场
		list->setCurIndex(tindex);
		list->setCurNode(tnode);
		while (temp = list->getNext())
		{//保存现场
			tnode = list->getCurrent();
			tindex = list->getCurIndex();
			printf("%s\n", temp->getName());
			visitAll(temp, app);
			//恢复现场
			list->setCurIndex(tindex);
			list->setCurNode(tnode);
		}
	}
}
void TApplication::translate(TDirver* div)
{
	if (!div)
		return;
	div->obtainData();//获取数据
	switch (div->getType())
	{
		//特殊情况
		case Event_None: break;
		default:
		{//默认直接发送类型，和数据即可
			printf("type = %d\n", div->getType());
			TPoint p(div->dataFront(), div->dataBack());
			event =  new TTouchEvent(div->getType(), (const TPoint)p);
		}break;
	}
}

void TApplication::distribute()
{
	if (event) 
	{
		visitAll(widroot, this);
		delete event;
		event = NULL;
	}
}

void TApplication::distribute(TObject* obj)
{
	if (event)
	{
		visitAll(obj, this);
		delete event;
		event = NULL;
	}
}

void TApplication::destroy()
{
	delete widroot;
}

