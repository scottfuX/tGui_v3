#ifndef _TAPPLICATION_H_
#define _TAPPLICATION_H_


#include "TGlobal.h"
#include "TObject/TObject.h"
#include "TWidget/TWidget.h"
#include "TObject/TEven.h"
#include "TObject/TDirver.h"

class TApplication
{
	TWidget* widroot;
	int16 objNum;
	TEvent* event;
	TDirver* dirver;

	void distribute();
	void distribute(TObject* obj);
	void translate(TDirver* div);

	void visitAll(TObject* obj, TApplication* app);
	void emit(TObject* obj);
public:
	TApplication(TWidget* r, TDirver* dirver);
	~TApplication();
	TEvent* getEvent() { return event; }
	int32 getObjNum() { return objNum; }
	void add(TObject* obj, TObject* parents = NULL);
	void run();
	void suspension();
	void destroy();
	void show();
};


#endif // !_TAPPLICATION_H_

