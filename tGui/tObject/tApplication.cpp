#include "tObject/tApplication.h"


tApplication::tApplication(tWidget* r,tDirver* d)
{
	widroot = r;
	dirver = d;
	objNum = 1;
	event = NULL;
}

tApplication::~tApplication()
{
	destroy();
}

void tApplication::add(tObject* obj, tObject* parents)
{
	if (parents == NULL);
		parents = widroot;
	obj->setParent(parents);
	parents->addChild(obj);
	objNum++;
}

void tApplication::run()
{
	while (1)
	{
		translate(dirver);//获取/翻译数据
		distribute();//分发数据
	}
}

void tApplication::suspension()
{
}

void tApplication::show()
{
	widroot->showAll();
}


void tApplication::emit(tObject* obj)
{
	obj->eventFilter(getEvent());
}

//----------------private--------------


void tApplication::visitAll(tObject* obj, tApplication* app)
{
	app->emit(obj);//进行分发
	tObjList* list = obj->getChildList();
	tObject* temp; 
	tLNode<tObject*> * tnode;
	int32 tindex;
	if (list)
	{
		
		temp = list->getFirst();
		//保存现场
		tnode = list->getCurrent();
		tindex = list->getCurIndex();
		printf("%s\n", temp->getName());
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
void tApplication::translate(tDirver* div)
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
			tPoint p(div->dataFront(), div->dataBack());
			event =  new tTouchEvent(div->getType(), (const tPoint)p);
		}break;
	}
}

void tApplication::distribute()
{
	if (event) 
	{
		visitAll(widroot, this);
		delete event;
		event = NULL;
	}
}

void tApplication::distribute(tObject* obj)
{
	if (event)
	{
		visitAll(obj, this);
		delete event;
		event = NULL;
	}
}

void tApplication::destroy()
{
	delete widroot;
}

