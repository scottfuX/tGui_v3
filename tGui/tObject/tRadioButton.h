#ifndef _TRADIOBUTTON_H
#define _TRADIOBUTTON_H

#include "tObject/tAbstractButton.h"
#include "tPainter/tPainter.h"

class tRadioButton :
	public tAbstractButton
{
public:
	tRadioButton(int32 x, int32 y, int32 w, int32 h, const char* name,tObject* obj = NULL);
	virtual ~tRadioButton() { delRadio(); };
	virtual void	show();
	virtual void sig_depress(int32 d1, int32 d2);
	virtual void sig_release(int32 d1, int32 d2);
	virtual void release(); //只响应，不发送signal

	bool isSelected() { return selected; };
	tRadioButton* getNext() { return next; }
	void addNextRadio(tRadioButton* radio);
	void delRadio();

private:
	bool selected;
	tRadioButton* next;
	void changeSelected() { selected ? selected = false : selected = true; }
	void changeOtherSelect();
	
};

#endif // !_TRADIOBUTTON_H

