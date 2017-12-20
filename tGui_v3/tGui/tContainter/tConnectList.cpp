#include "tContainter/tConnectList.h"


int32 tConnectList::find(void(*sig)())
{
	tList<connection*>::first();
	while (tList<connection*>::currentNode())
	{
		if (tList<connection*>::currentNode()->getData()->signal == sig)
			return currentIndex();
		tList<connection*>::next();
	}
	return -1;
}
