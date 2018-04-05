#ifndef _DESKTOP_H_
#define _DESKTOP_H_
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

#include "demo/UserPhoto.h"
#include "demo/UserGame.h"

class Desktop :public TWindow
{
public:
    // Desktop(const char*  n, TWidget* obj);
	Desktop(const char* filename,TApplication* app,const char*  n = NULL, TWidget* obj = NULL );
	virtual ~Desktop() ;
	virtual void show();

    void openSetup();
    void closeSetup();
    void openGame();
    void openPhoto();

private:
    void createIcon();
    void deleteIcon();

	TIconButton* icon_clock;
    TIconButton* icon_date ;
    TIconButton* icon_setting ;
    TIconButton* icon_calculator ;
    TIconButton* icon_photo ;
    TIconButton* icon_play ;
    TIconButton* icon_search ;
    TIconButton* icon_game ;

    TDialog* dialog ;
    TPushButton* btn1 ;
	TPushButton* btn2 ;
};


#endif // !_DESKTOP_H_

