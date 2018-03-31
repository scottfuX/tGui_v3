#ifndef _TDIALOG_H_
#define _TDIALOG_H_

#include "TWidget/TWidget.h"
#include "TPainter/TBufPainter.h"
#include "TObject/TImage.h"

class TDialog :
	public TWidget
{
private:
	bool state;
	bool hasFocus;
	int32 preX;
	int32 preY;
	int32 contactOffsetW; //按下点的偏移
	int32 contactOffsetH; //按下点的偏移
	uint16 titleHeight;
	bool haveImg;
	TImage* dialogImg;

	void restRect(int32 preX, int32 preY, int32 nowX, int32 nowY, TRect &r1, TRect &r2);

public:
	TDialog(int32 x, int32 y, int32 w, int32 h, const char* n, TWidget* obj,uint16 title_height = WIN_TITLE_H);
	TDialog(int32 x, int32 y,TImage* dialogImg ,const char* n, TWidget* obj,uint16 title_height = WIN_TITLE_H);
	virtual ~TDialog();
	virtual void	show();

	virtual void touchPressEvent(TTouchEvent *);
	virtual void touchReleaseEvent(TTouchEvent *);
	virtual void touchMoveEvent(TTouchEvent *);
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


#endif // !_TDIALOG_H_

