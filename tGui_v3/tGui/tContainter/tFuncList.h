#ifndef _TFUNCLIST_H_
#define _TFUNCLIST_H_

#include "tContainter/tList.h"

class tFuncList :public tList<void(*)()>
{
public:
	void append(void(*t)()) { tList<void(*)()>::append(t); }
	uint32 count() { return tList<void(*)()>::count(); }
	bool insertAt(uint32 index, void(*t)()) { return tList<void(*)()>::insertAt(index, t); }
	bool remove(void(*t)() = 0) { return tList<void(*)()>::remove(t); }
	void(*at(uint32 index))() { return tList<void(*)()>::at(index); }
	void clear() { tList<void(*)()>::clear(); }
	int32 find(void(*t)()) { return tList<void(*)()>::findRef(t, true); };
	/*void tofirst();
	void tolast();*/
	virtual int32 compareItems(void(*item1)(), void(*item2)())
	{
		return tList<void(*)()>::compareItems(item1, item2);
	};
};


#endif // !_TFUNCLIST_H_

