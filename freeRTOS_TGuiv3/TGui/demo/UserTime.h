#ifndef _USER_TIME_
#define _USER_TIME_


#include "TPainter/TBufPainter.h"
#include "TWidget/TWindow.h"

#include "TObject/TImage.h"
#include "TWidget/TDialog.h"
#include "TWidget/TWidget.h"
#include "TWidget/TPushButton.h"
#include "TWidget/TCheckBox.h"
#include "TWidget/TRadioButton.h"
#include "TWidget/TLabel.h"
#include "TWidget/TSlider.h"
#include "TWidget/TImageBox.h"
#include "TWidget/TSwitch.h"
#include "TWidget/TIconButton.h"

#include "TGlobal.h"

class UserTime :public TDialog
{
public:
	UserTime(int32 x,int32 y,TImage* img,const char* n, TWidget* obj,int offset);
	virtual ~UserTime() ;
	virtual void show();


private:
    TImageBox* dateContext;
    // TPushButton* ;
    // TPushButton* ;
    TLabel* timeLabel;
   
};

#endif //!_USER_TIME_
