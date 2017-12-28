#ifndef _TDIALOG_H_
#define _TDIALOG_H_

#include "tObject/tWidget.h"


class tDialog :
	public tWidget
{
private:
	bool state;
	bool hasFocus;
	int32 movOffsetW;
	int32 movOffsetH;
public:
	tDialog(int32 x, int32 y, int32 w, int32 h, const char* n, tObject* obj = NULL);
	virtual ~tDialog();

	virtual void	show();

	virtual void touchPressEvent(tTouchEvent *);
	virtual void touchReleaseEvent(tTouchEvent *);
	virtual void touchMoveEvent(tTouchEvent *);
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


#endif // !_TDIALOG_H_

