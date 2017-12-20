#ifndef _TCONNECTLIST_H_
#define _TCONNECTLIST_H_

#include "tObject/connection.h"
#include "tContainter/tList.h"

class tConnectList :public tList<connection*>
{
	friend class connection;
public:
	void append(connection* t) { tList<connection*>::append(t); }
	uint32 count() { return tList<connection*>::count(); }
	bool insertAt(uint32 index, connection* t) { return tList<connection*>::insertAt(index, t); }
	bool remove(connection* t = 0) { return tList<connection*>::remove(t); }
	connection* at(uint32 index) { return tList<connection*>::at(index); }
	void clear() { tList<connection*>::clear(); }
	int32 find(connection* t) { return tList<connection*>::findRef(t, true); };
	int32 find(void(*sig)());
};


#endif // !_TCONNECTLIST_H_

