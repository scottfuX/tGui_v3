#include "tObject/tApplication.h"


tApplication::tApplication(tObject* r, tDirver* d)
{
	root = r;
	diver = d;
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
		parents = root;
	obj->setParent(parents);
	parents->addChild(obj);
}

void tApplication::run()
{
	while (1)
	{
		translate(diver);
		distribute();
	}
}

void tApplication::suspension()
{
}

void tApplication::show()
{
	root->showAll();
}

static void emit(tObject* obj)
{
	tApplication app;
	obj->eventFilter(app.getEvent());
}

//----------------private--------------

void tApplication::distribute()
{
	root->visitAll(root, emit);
	delete event;
}

void tApplication::distribute(tObject* obj)
{
	obj->visitAll(obj, emit);
	delete event;
}


void tApplication::translate(tDirver* div)
{
	switch (div->type())
	{
		//特殊情况
		//case:{}break;
		default: 
		{//默认直接发送类型，和数据即可
			tPoint p(div->dataFront(), div->dataBack());
			event = new tTouchEvent(div->type(), (const tPoint)p);
		}break;
	}
}


void tApplication::destroy()
{
	delete root;
}

