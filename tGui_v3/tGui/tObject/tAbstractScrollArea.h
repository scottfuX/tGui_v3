#ifndef _TABSTRACTSCROLLAREA_H_
#define _TABSTRACTSCROLLAREA_H_

#include "tObject/tFrame.h"
#include "tObject/tScrollBar.h"

//带滚动条区域的抽象类
class tAbstractScrollArea :
	public tFrame
{
private:
	tScrollBar* scrollH;
	tScrollBar* scrollV;
public:
	tAbstractScrollArea(int32 x, int32 y, int32 w, int32 h, const char* n, tWidget* obj);
	virtual ~tAbstractScrollArea();
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
	virtual void focusOutEvent(tFocusEvent *) {};
	virtual void enterEvent(tEvent *) {};
	virtual void leaveEvent(tEvent *) {};
	virtual void paintEvent(tPaintEvent *) {};
	virtual void moveEvent(tMoveEvent *) {};
	virtual void resizeEvent(tResizeEvent *) {};
	virtual void closeEvent(tCloseEvent *) {};
};

#endif // !_TABSTRACTSCROLLAREA_H_



