#ifndef _USER_PHOTO_H_
#define _USER_PHOTO_H_

#ifdef __cplusplus
extern "C" {
#endif
	
// #include <stdio.h>
// #include "stm32f4xx_conf.h"
// #include "fatfs/ff.h"
// #include "interface_conf/tgui_conf.h"
// #include "libraries/picture_lib/piclib.h"	
// #include "libraries/exfuns_lib/exfuns.h"

#ifdef __cplusplus
}
#endif

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

	void nextPhoto();
	void prevPhoto();
	void closePhoto();

	void scanfile(const char *path);


private:
	TPushButton* close_btn;	
	TPushButton* left_btn;
    TPushButton* right_btn;
	TLabel* title_label;

	bool startStat;
	
	uint8 fileNum;
    uint8 fileName[32][32];
    FILINFO finfo;

	char lfnamebuff[_MAX_LFN];   
	int8 picIndex;
    
};

#endif //!_USER_PHOTO_H_
