#ifndef _USER_CALENDAR_
#define _USER_CALENDAR_


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

class UserCalendar :public TDialog
{
public:
	UserCalendar(int32 x,int32 y,TImage* img,const char* n, TWidget* obj,int offset);
	virtual ~UserCalendar() ;
	virtual void show();

    void prevMonth();
    void nextMonth();

private:
    TImageBox* dateContext;
    TPushButton* leftArrow;
    TPushButton* rightArrow;
    TLabel* dateLabel;
   
};

#endif //!_USER_CALENDAR_
