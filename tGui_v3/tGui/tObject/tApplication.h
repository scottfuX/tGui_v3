#ifndef _TAPPLICATION_H_
#define _TAPPLICATION_H_


#include "tGlobal.h"
#include "tObject/tObject.h"
#include "tObject/tEven.h"
#include "tObject/tDirver.h"

class tApplication
{
	tObject* root;
	int16 objNum;
	tDirver* diver;
	tEvent* event;

	void distribute();
	void distribute(tObject* obj);
	void translate(tDirver* div);
public:
	tApplication() {};
	tApplication(tObject* r, tDirver* d);
	~tApplication();
	tEvent* getEvent() { return event; }
	void add(tObject* obj, tObject* parents = NULL);
	void run();
	void suspension();
	void destroy();
	void show();
	

};


#endif // !_TAPPLICATION_H_

