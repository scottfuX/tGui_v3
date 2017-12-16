#include "tObject.h"


connection::connection(void(*sig) ())
{
	signal = sig;
	slotList = new tFuncList();
}

void connection::active()
{
	signal();
	tListIterator<void(*)()> iterator((*((tList<void(*)()>*)slotList)));
	while(iterator.get())//遍历执行
	{iterator()();}
}


tObject::tObject(tString* n = NULL, tObject* obj = NULL)
{
	name = n;
	parents = obj;
	childList = NULL;
	connections = NULL;
}
tObject::~tObject()
{
	if (childList)
		childList->clear();
	if (connections)
		connections->clear();

}

bool tObject::connect(void(*sig)(), void(*slot)())
{
	if (!connections)
		connections = new tConnectList();
	connection* con = new connection(sig);
	if (!con)
		return false;
	int32 num = connections->findReal(con);//这边要先遍历一次之前是否还有信号
	if (num < 0)//不存在
		connections->append(con);
	else//存在
	{//这边要先遍历一次之前是否还有槽
		delete con;
		tFuncList* funclist = connections->at(num)->slotList;
		if (funclist->find(slot) < 0)
			funclist->append(slot);
	}
	return true;
}

bool tObject::disconnect(void(*sig)(), void(*slot)())
{
	if (!connections)
		return true;
	connection* con = new connection(sig);
	if (!con)
		return false;
	int32 num = connections->findReal(con);
	if (num >= 0)//存在
	{
		tFuncList* funclist = connections->at(num)->slotList;
		funclist->remove(slot);
	}
	delete con;
	return true;
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
	//检查
	childList->remove(child);
}
