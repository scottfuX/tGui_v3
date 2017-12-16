#ifndef _TOBJLIST_H_
#define _TOBJLIST_H_

#include "tList.h"
#include "tObject\tObject.h"

class tObject;
class connection;
class tObjList :tList<tObject*>
{
public:
	void append(tObject* t) { tList<tObject*>::append(t); }
	uint32 count() { return tList<tObject*>::count(); }
	bool insertAt(uint32 index, tObject* t) { return tList<tObject*>::insertAt (index, t); }
	bool remove(tObject* t= 0) { return tList<tObject*>::remove(t); }
	tObject* at(uint32 index) { return tList<tObject*>::at(index); }
	void clear() { tList<tObject*>::clear(); }
	int32 find(tObject* t) { return tList<tObject*>::findRef(t, true); };
	/*void tofirst();
	void tolast();*/
	virtual int32 compareItems(tObject* item1, tObject* item2)
	{ return tList<tObject*>::compareItems(item1, item2); };
};


class tConnectList :tList<connection*>
{
public:
	void append(connection* t) { tList<connection*>::append(t); }
	uint32 count() { return tList<connection*>::count(); }
	bool insertAt(uint32 index, connection* t) { return tList<connection*>::insertAt(index, t); }
	bool remove(connection* t = 0) { return tList<connection*>::remove(t); }
	connection* at(uint32 index) { return tList<connection*>::at(index); }
	void clear() { tList<connection*>::clear(); }
	int32 find(connection* t) { return tList<connection*>::findRef(t, true); };
	int32 findReal(connection* t) { return tList<connection*>::find(t, true); }
	/*void tofirst();
	void tolast();*/
	virtual int32 compareItems(connection* item1, connection* item2)
		{return item1->signal == item2->signal;};
};

class tFuncList :tList<void(*)()>
{
public:
	void append(void(*t)() ) { tList<void(*)()>::append(t); }
	uint32 count() { return tList<void(*)()>::count(); }
	bool insertAt(uint32 index, void(*t)() ) { return tList<void(*)()>::insertAt(index, t); }
	bool remove(void(*t)()  = 0) { return tList<void(*)()>::remove(t); }
	void(* at(uint32 index))() { return tList<void(*)()>::at(index); }
	void clear() { tList<void(*)()>::clear(); }
	int32 find(void(* t)() ) { return tList<void(*)()>::findRef(t, true); };
	/*void tofirst();
	void tolast();*/
	virtual int32 compareItems(void(*item1)(), void(*item2)()) 
		{ return tList<void(*)()>::compareItems(item1, item2); };

};


#endif // !_TOBJLIST_H_

