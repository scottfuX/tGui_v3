#ifndef _TCHECKBOX_H_
#define _TCHECKBOX_H_


#include "tObject/tAbstractButton.h"
#include "tPainter/tPainter.h"

class tCheckBox :
	public tAbstractButton
{
public:
	tCheckBox(int32 x, int32 y, int32 w, int32 h, const char* name, tObject* obj = NULL);
	virtual ~tCheckBox() {};
	virtual void	show();
	virtual void sig_depress(int32 d1, int32 d2);
	virtual void sig_release(int32 d1, int32 d2);
	virtual void release(); //只响应，不发送signal

	bool isSelected() { return selected; };

private:
	bool selected;
	tCheckBox* next;

	void changeSelected() { selected? selected = false: selected = true ; }
};


#endif // !_TCHECKBOX_H_

