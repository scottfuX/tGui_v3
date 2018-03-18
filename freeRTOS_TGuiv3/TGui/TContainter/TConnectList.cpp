#include "TContainter/TConnectList.h"


int32 TConnectList::find(func  sig)
{
	TList<TConnection*>::first();
	while (TList<TConnection*>::currentNode())
	{
		if (TList<TConnection*>::currentNode()->getData()->signal == sig)
			return currentIndex();
		TList<TConnection*>::next();
	}
	return -1;
}
