
#ifndef _TSWITCH_H_
#define _TSWITCH_H_


#include "TWidget/TAbstractButton.h"
#include "TPainter/TBufPainter.h"
#include "TObject/TImage.h"
#include "TGlobal.h"

class TSwitch :public TAbstractButton
{
public:
	TSwitch(int32 x, int32 y, int32 w, int32 h, const char* name, TWidget* obj);
	TSwitch(int32 x, int32 y,TImage norImg,TImage selImg, const char* name, TWidget* obj);
	virtual ~TSwitch();
	virtual void show();
	virtual void sig_depress(int32 d1, int32 d2);
	virtual void sig_release(int32 d1, int32 d2);
	virtual void release(); //只响应，不发送signal

	bool isSelected() { return selected; };

private:
	bool selected;
	TSwitch* next;

	void changeSelected() { selected? selected = false: selected = true ; }
};


#endif // !_TSWITCH_H_

