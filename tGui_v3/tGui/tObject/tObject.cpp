#include "tObject/tObject.h"


//-----------------------------OBJECT-------------------------
tObject::tObject(tString* n , tObject* obj )
{
	name = n;
	parents = obj;
	childList = NULL;
	connections = NULL;
}
tObject::~tObject()
{
	destroyChild(this);
	delete childList;
	if (connections)
	{
		connections->setAutoDelete(true);
		connections->clear();
	}
	if (name)
		delete name;
}

bool tObject::connect(void(*sig)(), void(*slot)())
{
	if (!connections)
		connections = new tConnectList();
	int32 num = connections->find(sig);//这边要先遍历一次之前是否还有信号
	if (num >= 0)//存在
	{//这边要先遍历一次之前是否还有槽
		tFuncList* funclist = connections->at(num)->slotList;
		if (funclist->find(slot) < 0)
			funclist->append(slot);
	}
	else//不存在
	{
		connection* con = new connection(sig,slot);
		if (!con)
			return false;
		connections->append(con);
	}
	return true;
}

bool tObject::disconnect(void(*sig)(), void(*slot)())
{
	if (!connections)
		return true;
	int32 num = connections->find(sig);
	if (num >= 0)//存在
	{
		tFuncList* funclist = connections->at(num)->slotList;
		funclist->remove(slot);
	}
	return true;
}

void tObject::unlink(tObject* obj)
{
	if (!(obj->getParents()))
		return;
	obj->getParents()->getChildList()->unlink(obj);
}


void tObject::addChild(tObject* child)
{
	if (!childList)
		childList = new tObjList();
	//检查
	if((childList->find(child)) < 0)
		childList->append(child);
}
void tObject::remChild(tObject* child)
{
	if (!childList)
		return;
	//检查--有没有孩子
	destroyChild(child);
	//删除
	childList->remove(child);
}

void tObject::destroyChild(tObject* obj)
{
	if (obj->childList)
	{	
		destroyChild(obj->childList->getLast());
		delete(obj->childList->getLast());
		obj->childList->removeLast();
	}
}

void tObject::visitAll(tObject* obj,void ( *visit)(tObject* obj))
{
	visit(obj);
	if (obj->childList)
	{
		visitAll(obj->childList->getFirst(), visit);
		while(obj->childList->getCurrent()->getData() != obj->childList->getLast())
			visitAll(obj->childList->getNext(), visit);
	}
}

void tObject::showAll(tObject* obj)
{
	obj->show();
	if (obj->childList)
	{
		showAll(obj->childList->getFirst());
		while (obj->childList->getCurrent()->getData() != obj->childList->getLast())
			showAll(obj->childList->getNext());

	}
}

