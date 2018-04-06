#ifndef _USER_CALCULATE_H_
#define _USER_CALCULATE_H_


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

class UserCalculate :public TDialog
{
public:
	UserCalculate(int32 x,int32 y,TImage* img,const char* n, TWidget* obj,int offset);
	virtual ~UserCalculate() ;
	virtual void show();

    void closeCalculate();

private:

    void addNum(int32 d1,int32 d2);
    void addOperat(int32 d1,int32 d2);
    void clearData(int32 d1,int32 d2);

    double value;
    TString * tempValue;
    
    TLabel*  label;
	TPushButton* close_btn;	
    TPushButton* btn0;
    TPushButton* btn1;
    TPushButton* btn2;
    TPushButton* btn3;
    TPushButton* btn4;
    TPushButton* btn5;
    TPushButton* btn6;
    TPushButton* btn7;
    TPushButton* btn8;
    TPushButton* btn9;
    TPushButton* btn_plus;
    TPushButton* btn_de;
    TPushButton* btn_mul;
    TPushButton* btn_div;
    TPushButton* btn_equ;
    TPushButton* btn_mode;   
    TPushButton* btn_point ;
    TPushButton* btn_ac;
    TPushButton* btn_c;
};

#endif //!_USER_CALCULATE_H_
