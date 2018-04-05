#ifndef _TAPPLICATION_H_
#define _TAPPLICATION_H_


#include "TGlobal.h"
#include "TObject/TObject.h"
#include "TWidget/TWidget.h"
#include "TContainter/TWidgetList.h"
#include "TObject/TEven.h"
#include "TObject/TDirver.h"
#include "TContainter/TFuncList.h"


#define SHARE_SIGNAL_CLOSE 0x000000FF
#define SHARE_SIGNAL_HIDE  0x0000FF00




class TApplication
{
	TWidget* widroot;//必须是一个窗口类
	TEvent* event;
	TDirver* dirver;
	TWidgetList* windList;

	//需要一个 共同的 信号槽  -->用于接受下面控件传上来的事件
	volatile TWidget* SHARE_SIGNAL_OBJ;
	volatile int32 SHARE_SIGNAL_DATA;
	volatile uint8 SHARE_SIGNAL_INDEX;

	void distribute();
	void distribute(TObject* obj);
	void translate();
	void visitAll(TObject* obj);
	void emit(TObject* obj);
public:
	TApplication(TDirver* dirver);
	~TApplication();
	TEvent* getEvent() { return event; }

	void addWindow(TWidget* window);
	void remWindow(TWidget* window);
	void chgWidRoot(TWidget* window);
	void chgWidRoot();
	void delWidRoot();


	void setSignal(TWidget* wid,int32 data,uint8 index = -1);
	void run();
	void suspension(){};
	void destroy(){};
	void show();
	
};


#endif // !_TAPPLICATION_H_

