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

void connection::active(int32 d1,int32 d2)
{
	if (!slotList||!recvList)
		return;
	for (int16 i=0; i < slotList->count(); i++)
	{
		printf("i = %d\n", i);
		((*recvList->at(i)).*(slotList->at(i)))(d1,d2);//arg 有问题 把上面的active也改一下，int，int
	}
}
