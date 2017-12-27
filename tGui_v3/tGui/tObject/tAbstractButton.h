#ifndef _TABSTRACTBUTTON_H_
#define _TABSTRACTBUTTON_H_

#include "tGlobal.h"
#include "tWidget.h"

class tAbstractButton:public tWidget
{

protected:
	bool state; //true => press ;false
public :
	tAbstractButton(int32 x, int32 y, int32 w, int32 h, const char* n = NULL, tObject* obj = NULL) ;
	virtual ~tAbstractButton() {};
	virtual void	show() =0;
	virtual void sig_depress(int32 d1,int32 d2)=0;
	virtual void sig_release(int32 d1, int32 d2)=0;
	virtual void release() = 0;//只响应，不发送signal
	bool isPress() { return state; }

	virtual void touchPressEvent(tTouchEvent *) ;
	virtual void touchReleaseEvent(tTouchEvent *) ;
	virtual void touchMoveEvent(tTouchEvent *) ;
	virtual void touchClickEvent(tTouchEvent *) {};
	virtual void mousePressEvent(tMouseEvent *) {};
	virtual void mouseReleaseEvent(tMouseEvent *) {};
	virtual void mouseDoubleClickEvent(tMouseEvent *) {};
	virtual void mouseClickEvent(tMouseEvent *) {};
	virtual void mouseMoveEvent(tMouseEvent *) {};
	virtual void keyPressEvent(tKeyEvent *) {};
	virtual void keyReleaseEvent(tKeyEvent *) {};
	virtual void focusInEvent(tFocusEvent *) {};
	virtual void focusOutEvent(tFocusEvent *) {};
	virtual void enterEvent(tEvent *) {};
	virtual void leaveEvent(tEvent *) {};
	virtual void paintEvent(tPaintEvent *) {};
	virtual void moveEvent(tMoveEvent *) {};
	virtual void resizeEvent(tResizeEvent *) {};
	virtual void closeEvent(tCloseEvent *) {};


};

#endif // !_TABSTRACTBUTTON_H_

