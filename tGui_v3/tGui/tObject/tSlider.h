#ifndef _TSLIDER_H_
#define _TSLIDER_H_

#include "tObject/tAbstractSlider.h"
#include "tPainter/tPainter.h"

class tSlider :
	public tAbstractSlider
{
public:
	tSlider() :tAbstractSlider() { value = 0; };
	tSlider(int32 x, int32 y, int32 w, int32 h, const char* name);
	virtual ~tSlider() {};
	virtual void show();
	virtual void sig_move(int32 d1, int32 d2);
	virtual void sig_depress(int32 d1, int32 d2);
	virtual void sig_release(int32 d1, int32 d2);
	virtual void release();

	virtual void touchPressEvent(tTouchEvent *);
	virtual void touchReleaseEvent(tTouchEvent *);
	virtual void touchMoveEvent(tTouchEvent *);
};


#endif // !_TSLIDER_H_


