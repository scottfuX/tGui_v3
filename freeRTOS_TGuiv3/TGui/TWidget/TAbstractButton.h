#ifndef _TABSTRACTBUTTON_H_
#define _TABSTRACTBUTTON_H_

#include "TGlobal.h"
#include "TWidget.h"

class TAbstractButton:public TWidget
{

protected:
	bool state; //true => press ;false
public :
	TAbstractButton(int32 x, int32 y, int32 w, int32 h, const char* n, TWidget* obj) ;
	virtual ~TAbstractButton() {};
	virtual void	show() =0;
	virtual void sig_depress(int32 d1,int32 d2)=0;
	virtual void sig_release(int32 d1, int32 d2)=0;
	virtual void release() = 0;//只响应，不发送signal
	bool isPress() { return state; }

	virtual void touchPressEvent(TTouchEvent *) ;
	virtual void touchReleaseEvent(TTouchEvent *) ;
	virtual void touchMoveEvent(TTouchEvent *) ;
	virtual void touchClickEvent(TTouchEvent *) {};
	virtual void mousePressEvent(TMouseEvent *) {};
	virtual void mouseReleaseEvent(TMouseEvent *) {};
	virtual void mouseDoubleClickEvent(TMouseEvent *) {};
	virtual void mouseClickEvent(TMouseEvent *) {};
	virtual void mouseMoveEvent(TMouseEvent *) {};
	virtual void keyPressEvent(TKeyEvent *) {};
	virtual void keyReleaseEvent(TKeyEvent *) {};
	virtual void focusInEvent(TFocusEvent *) {};
	virtual void focusOuTEvent(TFocusEvent *) {};
	virtual void enterEvent(TEvent *) {};
	virtual void leaveEvent(TEvent *) {};
	virtual void painTEvent(TPainTEvent *) {};
	virtual void moveEvent(TMoveEvent *) {};
	virtual void resizeEvent(TResizeEvent *) {};
	virtual void closeEvent(TCloseEvent *) {};


};

#endif // !_TABSTRACTBUTTON_H_

