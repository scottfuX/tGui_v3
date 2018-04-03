#include "demo/Desktop.h"

Desktop::Desktop(const char* filename,TApplication* app,const char* n, TWidget* obj)
	:TWindow(filename,app,n,obj)
{
	
    icon_clock = new TIconButton(20,40,new TImage("1:/tgui_pic/clock.png"),NULL/*new TImage("1:/tgui_pic/clock2.png")*/,"时间",this);
    icon_date = new TIconButton(222,45,new TImage("1:/tgui_pic/date.png"),NULL/*new TImage("1:/tgui_pic/date2.png")*/,"日历",this);
    icon_setting = new TIconButton(409,40,new TImage("1:/tgui_pic/setting.png"),NULL/*new TImage("1:/tgui_pic/setting2.png")*/,"设置",this);
    icon_calculator = new TIconButton(599,45,new TImage("1:/tgui_pic/calculator.png"),NULL/*new TImage("1:/tgui_pic/calculator2.png")*/,"计算器",this);
    
    icon_photo = new TIconButton(20,260,new TImage("1:/tgui_pic/photo.png"),NULL /*new TImage("1:/tgui_pic/photo2.png")*/,"照片",this);
    icon_play = new TIconButton(245,260,new TImage("1:/tgui_pic/play.png"),NULL /*new TImage("1:/tgui_pic/play2.png")*/,"播放器",this);
    icon_search = new TIconButton(420,260,new TImage("1:/tgui_pic/search.png"),NULL/*new TImage("1:/tgui_pic/search2.png")*/,"搜索",this);
    icon_weather = new TIconButton(575,260,new TImage("1:/tgui_pic/weather.png"),NULL/*new TImage("1:/tgui_pic/weather2.png")*/,"天气",this);

	
	// dialog2 = new TDialog(250, 100, new TImage("1:/tgui_pic/dialog.png"), "dialog", this,55);
 	// btn1 = new TPushButton(292, 234, TImage("1:/tgui_pic/dialog_btn1.png"),TImage("1:/tgui_pic/dialog_btn1_sel.png"),"确定",dialog2);
	// btn2 = new TPushButton(442, 234, TImage("1:/tgui_pic/dialog_btn2.png"),TImage("1:/tgui_pic/dialog_btn2_sel.png"),"取消",dialog2);
	// btn->connect((func)(&TPushButton::sig_release), chck1,(func)(&TCheckBox::sig_release));
	// slider1->connect((func)(&TSlider::sig_release), label1, (func)(&TLabel::slot_showValue));

    icon_photo->connect((func)(&TIconButton::sig_release),this,(func)(&Desktop::openPhoto));

	
}

Desktop::~Desktop() 
{

}

void Desktop::show()
{
	refresh();
}

void Desktop::openPhoto()
{
    UserPhoto* userphoto = new UserPhoto("1:/tgui_pic/desk2.jpg",getApp());
    getApp()->setSignal(userphoto,Event_Show);
}








