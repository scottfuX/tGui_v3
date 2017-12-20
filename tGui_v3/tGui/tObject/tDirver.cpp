#include "tObject/tDirver.h"

//-----------------------------touchdiver----------------
void tTouchDirver::obtainData()
{
	int32* x;
	int32* y;
	guiGetPoint(x, y);
	if (getState())
	{
		if (!getState_pre() || data1 == *x || data2 == *y)
		{
			setType(Event_TouchPress);
			data1 = *x;
			data2 = *y;
		}
		else
		{
			setType(Event_TouchMove);
			data1 = *x;
			data2 = *y;
		}
	}
	else if (tDirver::type()== Event_TouchPress || tDirver::type() == Event_TouchMove)
	{
		setType(Event_TouchRelese);
		data1 = *x;
		data2 = *y;
	}
	else 
	{
		setType(Event_None);
		data1 = -1;
		data2 = -1;
	}
}

int32 tTouchDirver::type()
{
	obtainData();
	return tDirver::type(); 
}
