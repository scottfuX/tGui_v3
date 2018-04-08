#include "TObject/TDirver.h"

//-----------------------------basediver-----------------------------

TDirver::TDirver(bool isMulThread,uint32 dirObtainMs) 
{
	this->isMulThread = isMulThread;
	this->dirObtainMs = dirObtainMs;

	divType = 0; 

	if(isMulThread)
		dirQueue = new TQueue<TEvent*>();
	
}

TDirver::~TDirver()
{
	
	if(isMulThread)
	{
		TEvent* tmp ;
		while(dirQueue && dirQueue->count() > 0)
		{
			tmp = dirQueue->dequeue();
		 	delete tmp;
		}
		delete dirQueue;
	}
}



//-----------------------------touchdiver-----------------------------

TTouchDirver::TTouchDirver(bool isMulThread,uint32 dirObtainMs)
	:TDirver(isMulThread,dirObtainMs)
{
	lock = true; 
	setType(0); 
};

void TTouchDirver::enEventQueue()
{
	GUI_MUTEX_TAKE();
	if(dirQueue->count() >= 0 )
	{
		obtainData();
		if(getType() != Event_None)
		{
			while(dirQueue->count() >= QUE_EVENT_NUM)
			{
				TEvent* tmp = (TEvent* )dirQueue->dequeue();
				delete tmp;
			}
			TPoint p(dataFront(), dataBack());
			dirQueue->enqueue(new TTouchEvent(getType(),p));
		}
	}
	GUI_MUTEX_GIVE();
}

TEvent* TTouchDirver::deEventQueue()
{
	GUI_MUTEX_TAKE();
	if(dirQueue->isEmpty())
			return NULL;
	return (TEvent* )dirQueue->dequeue();
	GUI_MUTEX_GIVE();
}

void TTouchDirver::run()
{
	if(isMulThread)
	{
		while(1)
		{	
			enEventQueue();  //每一定时间就获取一次
			GUI_DELAY_MS(dirObtainMs);
		}
	}
	else
	{

	}
}

void TTouchDirver::getEvent(TEvent* event)
{
	//GUI_MUTEX_TAKE();
	if(isMulThread)
	{
		((TTouchEvent* )event)->setTouchEvent(0,0,0);
		TTouchEvent* tmp = (TTouchEvent*)deEventQueue();
		if(tmp)
		{
			((TTouchEvent* )event)->setTouchEvent(tmp->type(),tmp->x(),tmp->y());
			delete tmp;
		}
	}
	else
	{
		obtainData();
		((TTouchEvent* )event)->setTouchEvent(getType(),dataFront(), dataBack());
	}
	//GUI_MUTEX_GIVE();
}

void TTouchDirver::obtainData()
{
	if (getState())//按下
	{
		if (lock)//锁起来(不让重复按)
		{
			changeLock();
			setType(Event_TouchPress);
			data1 = getTouchX();
			data2 = getTouchY() ;		
		}
		else if (data1 != getTouchX() || data2 != getTouchY()) //按下了且未松手x，y变化了---不好控制速度
		{
			setType(Event_TouchMove);
			data1 = getTouchX();
			data2 = getTouchY();
		}
		else //之前没按下
		{
			setType(Event_None);
		}
	}
	else //松手 或 没按下
	{
		if (!lock)  //但之前被锁的话（之前按下了）
		{
			changeLock();
			setType(Event_TouchRelese);
			data1 = getTouchX();
			data2 = getTouchY();
		}
		else //之前没按下
		{
			setType(Event_None);
			data1 = -1;
			data2 = -1;
		}
	}
}

