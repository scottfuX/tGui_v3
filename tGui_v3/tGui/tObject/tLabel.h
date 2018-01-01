#ifndef _TLABEL_H_
#define _TLABEL_H_
#include "tObject/tFrame.h"
#include "tPainter/tPainter.h"

class tLabel:public tFrame
{
public:
	tLabel(int32 x, int32 y, int32 w, int32 h, const char* n, tWidget* obj);
	virtual ~tLabel() {};

	virtual void show();
	void slot_showValue(int32 d1, int32 d2);
private:
	colorDef textColor;
	bool hasBack;
};


#endif //_TLABEL_H_
