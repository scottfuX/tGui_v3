#ifndef _USER_H_
#define _USER_H_
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

class User :public TWindow
{
public:
	//User(const char*  n, TWidget* obj);
	User(const char* filename,TApplication* app,const char*  n = NULL, TWidget* obj = NULL);
	virtual ~User() ;
	virtual void show();
	void slot() { printf("depress_solt\n"); }
	void slot1() { printf("hello world\n"); }
	void slot2() { printf("release_slot\n"); }
private:
	TRadioButton* radio1,*radio2,*radio3;
	TImageBox* img;
	TPushButton* btn,*btn1,*btn2;
	TSwitch* swtch;
	TCheckBox* chck,*chck1;
	TSlider* slider1,*slider2;
	TLabel* label1;
	TDialog* dialog2;
	TIconButton* icon;
};


#endif // !_USER_H_


