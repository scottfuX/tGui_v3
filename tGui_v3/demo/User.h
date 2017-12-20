#ifndef _USER_H_
#define _USER_H_
#include "tObject/tWidget.h"
class User :public tWidget
{
public:
	User(tString* n, tObject* obj);
	~User();
	void slot() { out("hello world\n"); }
};


#endif // !_USER_H_


