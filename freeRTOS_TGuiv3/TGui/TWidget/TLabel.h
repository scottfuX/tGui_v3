#ifndef _TLABEL_H_
#define _TLABEL_H_
#include "TWidget/TFrame.h"
#include "TPainter/TBufPainter.h"
#include "TObject/TImage.h"

class TLabel:public TFrame
{
public:
	TLabel(int32 x, int32 y, int32 w, int32 h, const char* n, TWidget* obj);
	TLabel(int32 x, int32 y,TImage* img, const char* name,uint8 align, TWidget* obj);
	virtual ~TLabel() ;
	virtual void show();
	void slot_showValue(int32 d1, int32 d2);
private:
	colorDef textColor;
	bool haveImg;
	TImage * labelImg;
	uint8 labelAlign;
};


#endif //_TLABEL_H_
