#ifndef _TDIRVER_H_
#define _TDIRVER_H_

#include "TGlobal.h"
#include "TObject/TEven.h"
#include "TContainter/TQueue.h"
#include "interface_conf/tgui_conf.h"

class TDirver
{
private:
	int32 divType;
protected:
	void setType(int32 t) { this->divType = t; };
	TQueue<TEvent*>* dirQueue;
	uint32 dirObtainMs;
	bool isMulThread;
public:
	TDirver(bool isMulThread = false,uint32 dirObtainMs = 0);
	virtual ~TDirver();
	int32 getType() { return this->divType; };
	virtual int32 dataFront() {return 0;};
	virtual int32 dataBack() {return 0;};
	virtual void getEvent(TEvent* event) = 0;
	virtual void obtainData() = 0;
	virtual void run(){};
};

class TTouchDirver :public TDirver
{
private:
	int32 data1;
	int32 data2;
	bool lock;
public:
	TTouchDirver(bool isMulThread = false,uint32 dirObtainMs = 0);
	virtual ~TTouchDirver() {};
	void changeLock() { lock ? lock = false : lock = true; }
	virtual void obtainData();
	virtual int32 dataFront(){return data1;}
	virtual int32 dataBack(){return data2;}
	virtual void 	enEventQueue();
	virtual TEvent* deEventQueue();
	virtual void getEvent(TEvent* event);
	virtual void run();
};

#endif //_TDIRVER_H_

