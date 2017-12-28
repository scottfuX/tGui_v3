#include "tObject/tObject.h"


//-----------------------------OBJECT-------------------------
tObject::tObject(const char* n , tObject* obj )
{
	name = NULL;
	setName(n);
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

void tObject::setName(const char* str) 
{ 
	if(!name)
		name = new tString(str);
	else
		name->setStr(str);
}

void tObject::regist(tObject* obj)
{
	obj->addChild(this);
	this->setParent(obj);
}
void tObject::logout(tObject* obj)
{
	obj->remChild(this);
	this->setParent(nullptr);
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



bool tObject::connect(func  sig, tObject* receiver, func  slot)
{
	if (!connections)
		connections = new tConnectList();
	int32 num = connections->find(sig);//这边要先遍历一次之前是否还有信号
	if (num >= 0)//存在
	{//这边要先遍历一次之前是否还有槽
		tFuncList* funclist = connections->at(num)->slotList;
		tObjList* objlist = connections->at(num)->recvList;
		if (funclist->find(slot) < 0)
		{
			funclist->append(slot);
			objlist->append(receiver);
		}
	}
	else//不存在
	{
		connection* con = new connection(sig, receiver, slot);
		if (!con)
			return false;
		connections->append(con);
	}
	return true;
}

bool tObject::disconnect(func  sig, tObject* receiver, func  slot)
{
	if (!connections)
		return true;
	int32 num = connections->find(sig);
	if (num >= 0)//存在
	{
		tFuncList* funclist = connections->at(num)->slotList;
		tObjList* objlist = connections->at(num)->recvList;
		funclist->remove(slot);
		objlist->remove(receiver);
	}
	return true;
}

void tObject::callSlot(func sig, int32 d1, int32 d2)
{
	if (getConnections())
	{
		int num = getConnections()->find(sig);
		if (num >= 0)
			getConnections()->at(num)->active(d1,d2);
	}
}