#ifndef _TConnectList_H_
#define _TConnectList_H_

#include "TObject/TConnection.h"
#include "TContainter/TList.h"

class TConnection;
class TConnectList :public TList<TConnection*>
{
	friend class TConnection;
public:
	void append(TConnection* t) { TList<TConnection*>::append(t); }
	virtual uint32 count() { return TList<TConnection*>::count(); }
	bool insertAt(uint32 index, TConnection* t) { return TList<TConnection*>::insertAt(index, t); }
	bool remove(TConnection* t = 0) { return TList<TConnection*>::remove(t); }
	TConnection* at(uint32 index) { return TList<TConnection*>::at(index); }
	virtual	void clear() { TList<TConnection*>::clear(); }
	int32 find(TConnection* t) { return TList<TConnection*>::findRef(t, true); };
	int32 find(func  sig);
};


#endif // !_TConnectList_H_

