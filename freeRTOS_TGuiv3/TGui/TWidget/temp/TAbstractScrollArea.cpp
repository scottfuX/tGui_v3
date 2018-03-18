#ifndef _TABSTRACTSCROLLAREA_H_
#define _TABSTRACTSCROLLAREA_H_

#include "TWidget/TFrame.h"
#include "TWidget/TScrollBar.h"

//带滚动条区域的抽象类
class TAbstractScrollArea :
	public TFrame
{
private:
	TScrollBar* scrollH;
	TScrollBar* scrollV;
public:
	TAbstractScrollArea(int32 x, int32 y, int32 w, int32 h, const char* n, TWidget* obj);
	virtual ~TAbstractScrollArea();
	virtual void show() = 0;

	void showScroll(int32 realW, int32 realH, int32 scrollSize, bool hasH ,bool hasV);

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
	virtual void focusOuTEvent(tFocusEvent *) {};
	virtual void enterEvent(TEvent *) {};
	virtual void leaveEvent(TEvent *) {};
	virtual void painTEvent(tPainTEvent *) {};
	virtual void moveEvent(tMoveEvent *) {};
	virtual void resizeEvent(tResizeEvent *) {};
	virtual void closeEvent(tCloseEvent *) {};
};

#endif // !_TABSTRACTSCROLLAREA_H_



