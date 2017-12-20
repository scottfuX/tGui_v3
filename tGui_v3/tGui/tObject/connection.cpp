#include "tObject/connection.h"


connection::connection(void(*sig) ())
{
	signal = sig;
	slotList = new tFuncList();
}

connection::connection(void(*sig) (), void(*slot)())
{
	signal = sig;
	slotList = new tFuncList();
	if (slotList)
		return;
	slotList->append(slot);
}

void connection::active()
{
	tListIterator<void(*)()> iterator((*((tList<void(*)()>*)slotList)));
	while (iterator.get())//±éÀúÖ´ĞĞ
	{
		iterator()();
	}
}
