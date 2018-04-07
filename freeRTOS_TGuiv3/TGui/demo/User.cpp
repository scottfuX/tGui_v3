#include "demo/User.h"


User::User(const char* filename,TApplication* app,const char* n, TWidget* obj)
	:TWindow(filename,app,n,obj)
{
	
	//TRadioButton* radio = new TRadioButton(50, 100, 150, 30, "radio1", this);
	radio1 = new TRadioButton(TRect(50, 100, 150, 30),new TImage("1:/tgui_pic/radio_nor.png"),new TImage("1:/tgui_pic/radio_sel.png"),"单选1", this);
	radio2 = new TRadioButton(TRect(50, 140, 150, 30),new TImage("1:/tgui_pic/radio_nor.png"),new TImage("1:/tgui_pic/radio_sel.png"),"单选2", this);
	radio3 = new TRadioButton(TRect(50, 180, 150, 30),new TImage("1:/tgui_pic/radio_nor.png"),new TImage("1:/tgui_pic/radio_sel.png"),"单选3", this);
	radio1->addNextRadio(radio2);
	radio2->addNextRadio(radio3);

	//TImageBox* img2 = new TImageBox(400,320,100,150,"1:/tgui_pic/date.png","i'm png!",this);
	
	//TPushButton* btn = new TPushButton(50,230,150,65, "button", this);
	btn = new TPushButton(50,220,new TImage("1:/tgui_pic/button.png"),new TImage("1:/tgui_pic/button_sel.png"),"按钮", this);
	swtch = new TSwitch(50,270,new TImage("1:/tgui_pic/switch_off.png"),new TImage("1:/tgui_pic/switch_on.png"),NULL, this);
	
	//TCheckBox* chck = new TCheckBox(50,50,150,30,"check1", this);
	chck = new TCheckBox(TRect(50,20,150,30),new TImage("1:/tgui_pic/check1_nor.png"),new TImage("1:/tgui_pic/check1_sel.png"),"复选1", this);
	chck1 = new TCheckBox(TRect(50,60,150,30),new TImage("1:/tgui_pic/check2_nor.png"),new TImage("1:/tgui_pic/check2_sel.png"),"复选2", this);
	
	slider1 = new TSlider(50,370,new TImage("1:/tgui_pic/slider_back.png"),new TImage("1:/tgui_pic/slider_front.png"),new TImage("1:/tgui_pic/slider_bar.png"),NULL,this);
		slider1->setBarSadSize(10);
	slider2 = new TSlider(50,415,new TImage("1:/tgui_pic/slider_back.png"),new TImage("1:/tgui_pic/slider_front.png"),new TImage("1:/tgui_pic/slider_bar.png"),NULL, this);
		slider2->setBarSadSize(10);
	// TSlider* slider2 = new TSlider(700, 100, 30, 300, NULL, this,false);	
	label1 = new TLabel(50,320,new TImage("1:/tgui_pic/label_slider.png"),"0",ALIGN_UP_MID,this);


	icon = new TIconButton(649,0,new TImage("1:/game_pic/Scull.png"),NULL,"X",this);//new TImage("1:/tgui_pic/play.png")
	
	// TDialog* dialog1 = new TDialog(300, 50, 250, 200, "dialog", this);
	// TLabel* label2 = new TLabel(315, 100, 190, 50, "hello world", &dialog1);
	// dialog2 = new TDialog(250, 100, new TImage("1:/tgui_pic/dialog.png"), "dialog", this,55);
 	// btn1 = new TPushButton(292, 234, new TImage("1:/tgui_pic/dialog_btn1.png"),new TImage("1:/tgui_pic/dialog_btn1_sel.png"),"确定",dialog2);
	// btn2 = new TPushButton(442, 234,new TImage("1:/tgui_pic/dialog_btn2.png"),new TImage("1:/tgui_pic/dialog_btn2_sel.png"),"取消",dialog2);
	

	btn->connect((func)(&TPushButton::sig_release), chck1,(func)(&TCheckBox::sig_release));
	slider1->connect((func)(&TSlider::sig_release), label1, (func)(&TLabel::slot_showValue));
	icon->connect((func)(&TIconButton::sig_release), this, (func)(&TWindow::slot_close));
	
}

User::~User() 
{
	
}

void User::show()
{
	refresh();
}

