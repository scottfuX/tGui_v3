#ifndef _TRADIOBUTTON_H
#define _TRADIOBUTTON_H

#include "TWidget/TAbstractButton.h"
#include "TPainter/TBufPainter.h"
#include "TObject/TImage.h"
#include "TGlobal.h"

class TRadioButton :
	public TAbstractButton
{
public:
	TRadioButton(int32 x, int32 y, int32 w, int32 h, const char* name, TWidget* obj);
	TRadioButton(TRect rect,TImage norImg,TImage selImg, const char* name, TWidget* obj);
	virtual ~TRadioButton();
	virtual void	show();
	virtual void sig_depress(int32 d1, int32 d2);
	virtual void sig_release(int32 d1, int32 d2);
	virtual void release(); //只响应，不发送signal

	bool isSelected() { return selected; };
	TRadioButton* getNext() { return next; }
	void addNextRadio(TRadioButton* radio);
	void delRadio();

private:
	bool selected;
	TRadioButton* next;

	void changeSelected() { selected ? selected = false : selected = true; }
	void changeOtherSelect();
	
};

#endif // !_TRADIOBUTTON_H

