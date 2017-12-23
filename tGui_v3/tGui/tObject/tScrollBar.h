#ifndef _SCROLLBAR_H_
#define _SCROLLBAR_H_


#include "tObject/tAbstractSlider.h"
class tScrollBar :
	public tAbstractSlider
{
public:
	tScrollBar() :tAbstractSlider() { value = 0; };
	tScrollBar(int32 x, int32 y, int32 w, int32 h, const char* name);
	virtual ~tScrollBar() {};

	virtual void sig_move(int32 d1, int32 d2);
	virtual void sig_depress(int32 d1,int32 d2);
	virtual void sig_release(int32 d1, int32 d2);
	virtual void release();

	virtual void touchPressEvent(tTouchEvent *);
	virtual void touchReleaseEvent(tTouchEvent *);
	virtual void touchMoveEvent(tTouchEvent *);
private:
};


#endif // !_SCROLLBAR_H_

