#ifndef _TAPPLICATION_H_
#define _TAPPLICATION_H_


#include "tGlobal.h"
#include "tObject/tObject.h"
#include "tObject/tWidget.h"
#include "tObject/tEven.h"
#include "tObject/tDirver.h"

class tApplication
{
	tWidget* widroot;
	int16 objNum;
	tEvent* event;
	tDirver* dirver;

	void distribute();
	void distribute(tObject* obj);
	void translate(tDirver* div);

	void visitAll(tObject* obj, tApplication* app);
	void emit(tObject* obj);
public:
	tApplication(tWidget* r, tDirver* dirver);
	~tApplication();
	tEvent* getEvent() { return event; }
	int32 getObjNum() { return objNum; }
	void add(tObject* obj, tObject* parents = NULL);
	void run();
	void suspension();
	void destroy();
	void show();
};


#endif // !_TAPPLICATION_H_

