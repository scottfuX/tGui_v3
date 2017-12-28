#ifndef _TWIDGET_H_
#define _TWIDGET_H_

#include "tObject/tEven.h"
#include "tObject/tPoint.h"
#include "tObject/tSize.h"
#include "tObject/tObject.h"
#include "tPainter/tPainter.h"


class tWidget :public tObject
{
	void	showAll(tWidget*);
public:
	tWidget(const char* n, tObject* obj);
	tWidget(int32 x, int32 y, int32 w, int32 h, const char* n, tObject* obj);
	virtual ~tWidget() { delete point; delete size; }
	void		setX(int32 x) { point->setX(x); }
	void		setY(int32 y) { point->setY(y); }
	void		setW(int32 w) { size->setWidth(w); }
	void		setH(int32 h) { size->setHeight(h); }
	int32		x() { return point->x(); }
	int32		y() { return point->y(); }
	int32		width() { return size->width(); }
	int32		height() { return size->height(); }
	void		setPoint(tPoint* p) { point = p; }
	tPoint*		getPoint() { return point; };
	void		setSize(tSize* s) { size = s; }
	tSize*		getSize() { return size; }
	void		setZpos(int32 z) { zpos = z; }
	int32		getZpos() { return zpos; }
	void		setBackColor(colorDef c) { backColor = c; };
	colorDef	getBackColor() { return backColor; }
	bool		isArea(int32 x, int32 y);
	void        showAll() { showAll(this); }
	
	virtual void	show() =0;


	virtual void eventFilter(tEvent* e);
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
private:
	tPoint* point;
	tSize*	size;
	int32	zpos;
	colorDef   backColor;

};


#endif // !_TWIDGET_H_

