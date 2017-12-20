#ifndef _TDIRVER_H_
#define _TDIRVER_H_
#include "tGlobal.h"
#include "tObject/tEven.h"
#include "interface_conf/tgui_conf.h"

class tDirver
{
	int32 divType;
protected:
	void setType(int32 t) { divType = t; };
public:
	virtual int32 type() { return divType; };
	virtual int32 dataFront()=0;
	virtual int32 dataBack() {};
};

class tTouchDirver :public tDirver
{
	int32 data1;
	int32 data2;
public:
	void obtainData();
	virtual int32 type();
	virtual int32 dataFront(){return data1;}
	virtual int32 dataBack(){return data2;}
};

#endif //_TDIRVER_H_

