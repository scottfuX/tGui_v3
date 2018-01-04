#ifndef _SCROLLBAR_H_
#define _SCROLLBAR_H_

#include "tObject/tAbstractSlider.h"
#include "tPainter/tPainter.h"

class tScrollBar :
	public tAbstractSlider
{
public:
	tScrollBar(int32 x, int32 y, int32 w, int32 h, const char* name, tWidget* obj, bool isHoriz = true );
	virtual ~tScrollBar() {};

	virtual void sig_move(int32 d1, int32 d2);
	virtual void sig_depress(int32 d1,int32 d2);
	virtual void sig_release(int32 d1, int32 d2);
	virtual void release();
	virtual void show();
	void setRealLen(int32 reallen);//根据真实的长度计算出其滚动条的长度

	virtual void sig_valueChange(int32 d1, int32 d2);
	virtual void touchPressEvent(tTouchEvent *);
	virtual void touchReleaseEvent(tTouchEvent *);
	virtual void touchMoveEvent(tTouchEvent *);
private:
	int32 scrollLen;
};


#endif // !_SCROLLBAR_H_

