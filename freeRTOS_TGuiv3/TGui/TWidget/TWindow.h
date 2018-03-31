#ifndef _TWINDOW_H_
#define _TWINDOW_H_

#include "TWidget/TWidget.h"
#include "TObject/TApplication.h"
#include "TPainter/TBufPainter.h"
#include "TObject/TImage.h"

class TWindow :public TWidget
{
private:
	bool haveImg;
	TImage* windImg;
    TApplication* app;

public:
	TWindow(TApplication* app,const char* n, TWidget* obj = NULL );
	TWindow(const char* filename ,TApplication* app,const char* n, TWidget* obj = NULL);
	virtual ~TWindow();
	virtual void show();
	
	TApplication* getApp(){return app;};
    void slot_close();

};


#endif // !_TWINDOW_H_

