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
		translate(dirver);
		distribute();
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
	app->emit(obj);
	tObjList* list = obj->getChildList();
	tObject* temp;
	if (list)
	{
		visitAll(list->getFirst(), app);
		while (temp = list->getNext())
				visitAll(temp, app);
	}
}
void tApplication::translate(tDirver* div)
{
	if (!div)
		return;
	div->obtainData();
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

