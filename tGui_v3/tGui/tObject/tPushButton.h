#ifndef _TPUSHBUTTON_H_
#define _TPUSHBUTTON_H_

#include "tAbstractButton.h"
#include "tPainter/tPainter.h"

class tPushButton :public tAbstractButton
{
public:
	tPushButton() :tAbstractButton() {}
	virtual ~tPushButton() {};

	virtual void	show();
	void regist(tObject* obj);
	void logout(tObject* obj);


	virtual void touchPressEvent(tTouchEvent *);
	virtual void touchReleaseEvent(tTouchEvent *);
	virtual void touchClickEvent(tTouchEvent *);
	virtual void touchMoveEvent(tTouchEvent *);
	virtual void mousePressEvent(tMouseEvent *) {};
	virtual void mouseReleaseEvent(tMouseEvent *) {};
	virtual void mouseDoubleClickEvent(tMouseEvent *) {};
	virtual void mouseClickEvent(tMouseEvent *) {};
	virtual void focusInEvent(tFocusEvent *) {};
	virtual void focusOutEvent(tFocusEvent *) {};
	virtual void enterEvent(tEvent *) {};
	virtual void leaveEvent(tEvent *) {};
	virtual void paintEvent(tPaintEvent *) {};
	virtual void moveEvent(tMoveEvent *) {};
	virtual void resizeEvent(tResizeEvent *) {};
	virtual void closeEvent(tCloseEvent *) {};
private:

	void depress();
	void release();
};

#endif // !_TPUSHBUTTON_H_
