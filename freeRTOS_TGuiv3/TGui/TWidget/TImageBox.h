#ifndef _TIMAGEBOX_H_
#define _TIMAGEBOX_H_

#include "TGlobal.h"
#include "TObject/TImage.h"
#include "TWidget/TWidget.h"
#include "TPainter/TBufPainter.h"

class TImageBox :public TWidget
{
public:
	TImageBox(int32 x, int32 y,TImage* img, const char* name, TWidget* obj);
	TImageBox(int32 x, int32 y,uint16 w,uint16 h,const char* filename, const char* name, TWidget* obj,bool DrawInBuf = true );

	virtual ~TImageBox();
	virtual void show();

private:
	TImage* img;
};




#endif //!_TIMAGEBOX_H_

