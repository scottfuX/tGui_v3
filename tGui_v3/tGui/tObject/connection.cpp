#include "tObject/connection.h"


connection::connection(func  sig)
{
	signal = sig;
	slotList = new tFuncList();
	recvList = new tObjList();
}

connection::connection(func  sig, tObject* receiver,func  slot)
{
	signal = sig;
	slotList = new tFuncList();
	recvList = new tObjList();
	if (!slotList || !recvList)
		return;
	slotList->append(slot);
	recvList->append(receiver);
}

void connection::active()
{
	if (!slotList||!recvList)
		return;
	printf("slot num = %d\n", slotList->count());
	for (int16 i=0; i < slotList->count(); i++)
	{
		printf("i = %d\n", i);
		((*recvList->at(i)).*(slotList->at(i)))();
	}
}
