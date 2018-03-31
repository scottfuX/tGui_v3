#ifndef _USER_PHOTO_H_
#define _USER_PHOTO_H_
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

class UserPhoto :public TWindow
{
public:
	UserPhoto(const char* filename,TApplication* app,const char*  n = NULL, TWidget* obj = NULL);
	virtual ~UserPhoto() ;
	virtual void show();
	void slot() { printf("depress_solt\n"); }
	void slot1() { printf("hello world\n"); }
	void slot2() { printf("release_slot\n"); }
private:
	TPushButton* left_btn;
    TPushButton* right_btn;
};

#endif //!_USER_PHOTO_H_
