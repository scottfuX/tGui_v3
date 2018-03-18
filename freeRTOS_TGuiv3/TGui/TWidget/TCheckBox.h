#ifndef _TCHECKBOX_H_
#define _TCHECKBOX_H_


#include "TWidget/TAbstractButton.h"
#include "TPainter/TBufPainter.h"
#include "TPainter/TPainter.h"

class TCheckBox :
	public TAbstractButton
{
public:
	TCheckBox(int32 x, int32 y, int32 w, int32 h, const char* name, TWidget* obj);
	virtual ~TCheckBox() {};
	virtual void	show();
	virtual void sig_depress(int32 d1, int32 d2);
	virtual void sig_release(int32 d1, int32 d2);
	virtual void release(); //只响应，不发送signal

	bool isSelected() { return selected; };

private:
	bool selected;
	TCheckBox* next;

	void changeSelected() { selected? selected = false: selected = true ; }
};


#endif // !_TCHECKBOX_H_

