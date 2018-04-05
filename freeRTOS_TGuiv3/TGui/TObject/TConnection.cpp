#include "TObject/TConnection.h"


TConnection::TConnection(func  sig)
{
	signal = sig;
	slotList = new TFuncList();
	recvList = new TObjList();
}

TConnection::TConnection(func  sig, TObject* receiver,func  slot)
{
	signal = sig;
	slotList = new TFuncList();
	recvList = new TObjList();
	if (!slotList || !recvList)
		return;
	slotList->append(slot);
	recvList->append(receiver);
}

TConnection::~TConnection()
{
	if (slotList) 
	{
		slotList->clear(); 
		delete slotList;
	}
	
	if (recvList)
	{
		recvList->clear();
		delete recvList;
	}
}

void TConnection::active(int32 d1,int32 d2)
{
	if (!slotList||!recvList)
		return;
	for (int16 i=0; i < slotList->count(); i++)
	{
		printf("Connection Num = %d\r\n", i);
		((*recvList->at(i)).*(slotList->at(i)))(d1,d2);//arg 有问题 把上面的active也改一下，int，int
	}
}

void TConnection::destroy() 
{

		
}
