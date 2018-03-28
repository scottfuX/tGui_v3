#include "tGuiMain.h"

void TGuiRun()
{
	// 主要的几个问题需要解决
	//1.多线程 
	//2.贴图问题 
	TTouchDirver dirve;
	User user(0,0,800,480,"1:/tgui_pic/back.jpg","user",NULL);
	//User user(0,0,TImage("1:/tgui_pic/back2.png"),"user",NULL);
	TApplication app(&user, &dirve);
	
	//TRadioButton radio(50, 100, 150, 30, "radio1", &user);
	TRadioButton radio1(TRect(50, 100, 150, 30),TImage("1:/tgui_pic/radio_nor.png"),TImage("1:/tgui_pic/radio_sel.png"),"radio1", &user);
	TRadioButton radio2(TRect(50, 140, 150, 30),TImage("1:/tgui_pic/radio_empty.png"),TImage("1:/tgui_pic/radio_sel.png"),"radio2", &user);
	TRadioButton radio3(TRect(50, 180, 150, 30),TImage("1:/tgui_pic/radio_nor.png"),TImage("1:/tgui_pic/radio_sel.png"),"radio3", &user);
	radio1.addNextRadio(&radio2);
	radio2.addNextRadio(&radio3);

	//TImageBox img2(400,320,100,150,"1:/tgui_pic/date.png","i'm png!",&user);
	TImageBox img(620,0,TImage("1:/tgui_pic/imac.png"),NULL, &user);
	
	//TPushButton btn(50,230,150,65, "button", &user);
	TPushButton btn2(50,220,TImage("1:/tgui_pic/spare/button.png"),TImage("1:/tgui_pic/spare/button_pre.png"), "button", &user);
	// app.show();
	
	//TCheckBox chck(50,50,150,30,"check1", &user);
	TCheckBox chck(TRect(50,20,150,30),TImage("1:/tgui_pic/check1_nor.png"),TImage("1:/tgui_pic/check1_sel.png"),"check1", &user);
	TCheckBox chck1(TRect(50,60,150,30),TImage("1:/tgui_pic/check2_nor.png"),TImage("1:/tgui_pic/check2_sel.png"),"check1", &user);
	
	TSlider slider1(50,355,new TImage("1:/tgui_pic/slider_back.png"),new TImage("1:/tgui_pic/slider_front.png"),new TImage("1:/tgui_pic/slider_bar.png"),NULL,&user);
	TSlider slider2(50,415,new TImage("1:/tgui_pic/slider_back.png"),new TImage("1:/tgui_pic/slider_front.png"),new TImage("1:/tgui_pic/slider_bar.png"),NULL, &user);
	// TSlider slider2(700, 100, 30, 300, NULL, &user,false);	
	TLabel label1(50,305,new TImage("1:/tgui_pic/label_slider.png"),"0", &user);
	
	TDialog dialog1(300, 50, 250, 200, "dialog", &user);
	TLabel label2(315, 100, 190, 50, "hello world", &dialog1);
	TDialog dialog2(350, 150, 250, 200, "dialog", &user);
 	TPushButton btn1(410, 200, TImage("1:/tgui_pic/spare/button.png"),TImage("1:/tgui_pic/spare/button_pre.png"),"btn",&dialog2);
	
	//TPushButton btn2(50,220,new TImage("1:/tgui_pic/imac.png"),new TImage("1:/tgui_pic/mail.png"), "button", &user);

	btn2.connect((func)(&TPushButton::sig_release), &chck1,(func)(&TCheckBox::sig_release));
	slider1.connect((func)(&TSlider::sig_release), &label1, (func)(&TLabel::slot_showValue));
	//slider1.connect((func)(&TSlider::sig_valueChange), &label2, (func)(&TLabel::slot_showValue));

	app.show(); 
	app.run();
}
