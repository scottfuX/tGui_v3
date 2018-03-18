#ifndef _TFRAME_H_
#define _TFRAME_H_

#include "TWidget/TWidget.h"
class TFrame :
	public TWidget
{
public:
	TFrame(int32 x, int32 y, int32 w, int32 h, const char* n , TWidget* obj );
	virtual ~TFrame();
	virtual void show() = 0;

	virtual void touchPressEvent(TTouchEvent *) {};
	virtual void touchReleaseEvent(TTouchEvent *) {};
	virtual void touchClickEvent(TTouchEvent *) {};
	virtual void touchMoveEvent(TTouchEvent *) {};
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


#endif // !_TFRAME_H_
