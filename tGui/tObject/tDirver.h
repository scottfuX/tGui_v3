#ifndef _TDIRVER_H_
#define _TDIRVER_H_
#include "tGlobal.h"
#include "tObject/tEven.h"
#include "interface_conf/tgui_conf.h"

class tDirver
{
	int32 divType;
protected:
	void setType(int32 t) { this->divType = t; };
public:
	tDirver() { divType = 0; }
	int32 getType() { return this->divType; };
	virtual int32 dataFront() {};
	virtual int32 dataBack() {};
	virtual void obtainData() {};
};

class tTouchDirver :public tDirver
{
	int32 data1;
	int32 data2;
	bool lock;
public:
	tTouchDirver() { lock = true; setType(0); };
	void changeLock() { lock ? lock = false : lock = true; }
	virtual void obtainData();
	virtual int32 dataFront(){return data1;}
	virtual int32 dataBack(){return data2;}
};

#endif //_TDIRVER_H_

