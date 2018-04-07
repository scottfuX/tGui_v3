#ifndef _USER_GAME_H_
#define _USER_GAME_H_


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

class UserGame :public TWindow
{
public:
	UserGame(const char* filename,TApplication* app,const char*  n = NULL, TWidget* obj = NULL);
	virtual ~UserGame() ;
	virtual void show();

    void closeGame();

	void attack();
	void defend();
	void closeWinDialog();
	void closeLoseDialog();

private:
	TPushButton* close_btn;	
	TPushButton* left_btn;
    TPushButton* right_btn;

	TDialog* win_dialog; 
	TDialog* lose_dialog; 

};

#endif //!_USER_GAME_H_
