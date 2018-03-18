#ifndef _USER_H_
#define _USER_H_
#include "TWidget/TWidget.h"
#include "TPainter/TPainter.h"
#include "TPainter/TBufPainter.h"
class User :public TWidget
{
public:
	User(int32 x, int32 y, int32 w, int32 h,const char*  n, TWidget* obj);
	virtual ~User() {};
	virtual void show();
	void slot() { printf("depress_solt\n"); }
	void slot1() { printf("hello world\n"); }
	void slot2() { printf("release_slot\n"); }
};


#endif // !_USER_H_


