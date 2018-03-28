#ifndef _TSLIDER_H_
#define _TSLIDER_H_

#include "TWidget/TAbstractSlider.h"
#include "TPainter/TBufPainter.h"
#include "TPainter/TPainter.h"
#include "TObject/TRect.h"
#include "TObject/TImage.h"

class TSlider :
	public TAbstractSlider
{
private:
	TImage* backImg;
	TImage* frontImg;
	TImage* barImg;
	bool haveImg;
public:
	TSlider(int32 x, int32 y, int32 w, int32 h, const char* n, TWidget* obj , bool isHoriz = true);
	TSlider(int32 x, int32 y,TImage* backImg,TImage* frontImg,TImage* barImg, const char* name, TWidget* obj, bool isHoriz = true);
	virtual ~TSlider() ;
	virtual void show();
	virtual void sig_move(int32 d1, int32 d2);
	virtual void sig_depress(int32 d1, int32 d2);
	virtual void sig_release(int32 d1, int32 d2);
	virtual void sig_valueChange(int32 d1, int32 d2);
	virtual void release();

	virtual void touchPressEvent(TTouchEvent *);
	virtual void touchReleaseEvent(TTouchEvent *);
	virtual void touchMoveEvent(TTouchEvent *);
};


#endif // !_TSLIDER_H_


