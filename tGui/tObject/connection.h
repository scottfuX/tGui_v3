#ifndef _CONNECTION_H_
#define _CONNECTION_H_

#include "tContainter/tFuncList.h"
#include "tGlobal.h"
#include "tObject/tObject.h"//#include "tContainter/tObjList.h"


class connection
{
	friend class tConnectList;
	friend class tObject;
public:
	connection(func  sig);
	connection(func  sig, tObject* receiver,func  slot);
	~connection() { destroy(); }
	void add(tObject* receiver, func  slot) {slotList->append(slot); recvList->append(receiver);}
	void del(tObject* receiver, func  slot) { slotList->remove(slot); recvList -> remove(receiver); }
	void destroy() {if (slotList) slotList->clear(); if (recvList)recvList->clear();}
	void active(int32 d1, int32 d2);
private:
	func  signal;
	tFuncList* slotList;
	tObjList* recvList;
};

#endif // !_CONNECTION_H_

