#ifndef _TLABEL_H_
#define _TLABEL_H_
#include "TWidget/TFrame.h"
#include "TPainter/TBufPainter.h"
#include "TPainter/TPainter.h"

class TLabel:public TFrame
{
public:
	TLabel(int32 x, int32 y, int32 w, int32 h, const char* n, TWidget* obj);
	virtual ~TLabel() {};

	virtual void show();
	void slot_showValue(int32 d1, int32 d2);
private:
	colorDef textColor;
	bool hasBack;
};


#endif //_TLABEL_H_
