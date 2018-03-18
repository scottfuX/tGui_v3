#ifndef _CONNECTION_H_
#define _CONNECTION_H_

#include "TContainter/TFuncList.h"
#include "TGlobal.h"
#include "TObject/TObject.h"
//#include "TContainter/TObjList.h"


class TConnection
{
	friend class TConnectList;
	friend class TObject;
public:
	TConnection(func  sig);
	TConnection(func  sig, TObject* receiver,func  slot);
	~TConnection() { destroy(); }
	void add(TObject* receiver, func  slot) {slotList->append(slot); recvList->append(receiver);}
	void del(TObject* receiver, func  slot) { slotList->remove(slot); recvList -> remove(receiver); }
	void destroy() {if (slotList) slotList->clear(); if (recvList)recvList->clear();}
	void active(int32 d1, int32 d2);
private:
	func  signal;
	TFuncList* slotList;
	TObjList* recvList;
};

#endif // !_CONNECTION_H_

