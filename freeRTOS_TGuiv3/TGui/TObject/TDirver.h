#ifndef _TDIRVER_H_
#define _TDIRVER_H_
#include "TGlobal.h"
#include "TObject/TEven.h"
#include "interface_conf/tgui_conf.h"

class TDirver
{
	int32 divType;
protected:
	void setType(int32 t) { this->divType = t; };
public:
	TDirver() { divType = 0; }
	int32 getType() { return this->divType; };
	virtual int32 dataFront() {return 0;};
	virtual int32 dataBack() {return 0;};
	virtual void obtainData() {};
};

class TTouchDirver :public TDirver
{
	int32 data1;
	int32 data2;
	bool lock;
public:
	TTouchDirver() { lock = true; setType(0); };
	void changeLock() { lock ? lock = false : lock = true; }
	virtual void obtainData();
	virtual int32 dataFront(){return data1;}
	virtual int32 dataBack(){return data2;}
};

#endif //_TDIRVER_H_

