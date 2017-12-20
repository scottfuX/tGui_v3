#ifndef _CONNECTION_H_
#define _CONNECTION_H_

#include "tContainter/tFuncList.h"

class connection
{
	friend class tConnectList;
	friend class tObject;
private:
	void(*signal) ();
	tFuncList *slotList;
public:
	connection(void(*sig) ());
	connection(void(*sig) (), void(*slot)());
	~connection() { destroy(); }
	void addSlot(void(*slot)()) { slotList->append(slot); }
	void delSlot(void(*slot)()) { slotList->remove(slot); }
	void destroy() { if (slotList) slotList->clear(); }
	void active();
};

#endif // !_CONNECTION_H_

