#include "tObject/tDirver.h"

//-----------------------------touchdiver----------------
void tTouchDirver::obtainData()
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
		else //之前没按下
		{
			setType(Event_None);
			data1 = -1;
			data2 = -1;
		}
		//else if (data1 != *x || data2 != *y) //按下了且未松手x，y变化了---不好控制速度
		//{
		//	setType(Event_TouchMove);
		//	data1 = *x;
		//	data2 = *y;
		//}
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

