#ifndef _TWIDGET_H_
#define _TWIDGET_H_

#include "TObject/TEven.h"
#include "TObject/TPoint.h"
#include "TObject/TSize.h"
#include "TObject/TObject.h"
#include "TObject/TBuffer.h"
#include "TObject/TImage.h"
#include "TContainter/TWidgetList.h"


class TWidget :public TObject
{
public:
	//TWidget(const char* n, TWidget* obj);
	TWidget(int32 x, int32 y, int32 w, int32 h, const char* n, TWidget* obj);
	TWidget(TRect r, const char* n, TWidget* obj);
	virtual		~TWidget();
	void		setX(int32 x) { rect->setX(x); }
	void		setY(int32 y) { rect->setY(y); }
	void		setW(int32 w) { rect->setWidth(w); }
	void		setH(int32 h) { rect->setHeight(h); }
	int32		x() { return rect->x(); }
	int32		y() { return rect->y(); }
	int32		width() { return rect->width(); }
	int32		height() { return rect->height(); }
	TRect*		getRect() { return rect; };
	void		setZpos(int32 z) { zpos = z; }
	int32		getZpos() { return zpos; }
	void		setBackColor(colorDef c) { backColor = c; };
	colorDef	getBackColor() { return backColor; }
	TBuffer* 	getBuffer(){ return widgetBuf;};
	void 		setBuffer(TBuffer* buf){widgetBuf = buf;};
	void		setOffsetWH(int32 w, int32 h) { offsetWH->setWidth(w); offsetWH->setHeight(h); } //设置与父类的偏移
	void 		updateOffsetWH();
	TSize*		getOffsetWH() { return offsetWH; }	
	void		chgChildsXY(TWidget* widget);//改变子类坐标 -- 父类在动
	void		chgInValid(TRect* area1 = NULL , TRect* area2 = NULL); //修改/添加/删除覆盖区
	void		chgPareInValid();
	TWidgetList* getInvalidList() { return invalidList; } 
	bool		isInRealArea(int32 x, int32 y); //  真实的区域 ，被覆盖后剩下的区域
	bool		isInArea(int32 x, int32 y); //设定的区域
	void        showAll() { showAll(this); }
	void 		cleanShowed(TRect* rect);

	uint8* 		getPareBufCorreAddr();  // 
	void 		imgLoadInterface(int32 x,int32 y,TImage* img,TRect* rectFrom = NULL,bool isOneSelf = false);//与图像加载函数对接的函数

	//TRect*	getPaintInvaild() { return paintInvaild; }
	// void		setIsVariable(bool statVari); //把子类也改变
	// bool		getIsVariable() { return isVariable; }
	


	void refresh();

	virtual void show() =0;
	virtual void eventFilter(TEvent* e);
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

private:
	TRect*	rect;
	TSize*	offsetWH;//根据父窗口的point的偏移
	int32	zpos;
	colorDef   backColor;
	TWidgetList* invalidList; //无效列表
	//bool	isVariable; //窗口是否是可变的  

	TBuffer* widgetBuf;

	void 		rectCut(TRect* srcRect);

	void		showAll(TWidget*);
	void		chgAllInValid(TObjList* chdlist, TWidget* widget,TRect* area1, TRect* area2);
	void		repaintInvaild(TRect* area1, TRect* area2);
	void		addAchgInvalid(TWidget* widget,TRect* area1,TRect* area2);
	void		remInvalid(TWidget* widget);
};


inline bool TWidget::isInArea(int32 xt, int32 yt)
{
	if (xt >= x() && yt >= y() && xt < (x() + width()) && yt < (y() + height()))
		return true;
	return false;
}


inline  void TWidget::updateOffsetWH()
{
	TWidget* wid = (TWidget*)getParents();
	if(wid)
	{
		offsetWH->setWidth(this->x() - wid->x());//修改 偏移
		offsetWH->setHeight(this->y() - wid->y());
	}
}

inline uint8* TWidget::getPareBufCorreAddr()
{
	return (((TWidget*)getParents())->getBuffer()->getBufAddr() + \
		(getOffsetWH()->width() +  getOffsetWH()->height() * ((TWidget*)getParents())->width()) * GUI_PIXELSIZE);
}

#endif // !_TWIDGET_H_

