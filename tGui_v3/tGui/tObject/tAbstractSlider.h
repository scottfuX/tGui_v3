#ifndef _TABSRACTSLIDER_H_
#define _TABSRACTSLIDER_H_

#include "tObject/tWidget.h"
class tAbstractSlider :
	public tWidget
{
protected:
	int32 value;
	bool isHoriz;//true horiz
	bool state; //true => press ;false
public:
	tAbstractSlider(int32 x, int32 y, int32 w, int32 h, const char* n = NULL, bool isHoriz = true, tObject* obj = NULL) ;
	virtual ~tAbstractSlider() {};
	virtual void	show() = 0;
	virtual void	sig_move(int32 d1, int32 d2) = 0;
	virtual void	sig_depress(int32 d1, int32 d2) = 0;
	virtual void	sig_release(int32 d1, int32 d2) = 0;
	virtual void	release() = 0;//只响应，不发送signal
	bool isPress() { return state; }

	virtual void touchPressEvent(tTouchEvent *) {};
	virtual void touchReleaseEvent(tTouchEvent *) {};
	virtual void touchClickEvent(tTouchEvent *) {};
	virtual void touchMoveEvent(tTouchEvent *) {};
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

#endif // !_TABSRACTSLIDER_H_
