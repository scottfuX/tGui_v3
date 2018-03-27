#include "tGuiMain.h"

void TGuiRun()
{
	// 主要的几个问题需要解决
	//1.多线程 
	//2.贴图问题 还有点小瑕疵  》》 TImage 两种加载方式结果不一样   //这种就有问题 User user(0,0,800,480,"1:/tgui_pic/back.png","user",NULL);
	TTouchDirver dirve;
	//User user(0,0,800,480,"1:/tgui_pic/back.png","user",NULL);
	User user(0,0,new TImage("1:/tgui_pic/back2.png"),"user",NULL);
	TApplication app(&user, &dirve);
	
	//TRadioButton radio(50, 100, 150, 30, "radio1", &user);
	TRadioButton radio1(new TRect(50, 100, 150, 30),new TImage("1:/tgui_pic/radio.png"),new TImage("1:/tgui_pic/radio_sel.png"),"radio1", &user);
	TRadioButton radio2(new TRect(50, 140, 150, 30),new TImage("1:/tgui_pic/radio.png"),new TImage("1:/tgui_pic/radio_sel.png"),"radio2", &user);
	TRadioButton radio3(new TRect(50, 180, 150, 30),new TImage("1:/tgui_pic/radio.png"),new TImage("1:/tgui_pic/radio_sel.png"),"radio3", &user);
	radio1.addNextRadio(&radio2);
	radio2.addNextRadio(&radio3);

	//TImageBox img2(400,320,100,150,"1:/tgui_pic/date.png","i'm png!",&user);
	TImageBox img(620,0,new TImage("1:/tgui_pic/note.png"),NULL, &user);
	
	//TPushButton btn(50,230,150,65, "button", &user);
	 TPushButton btn2(50,220,new TImage("1:/tgui_pic/imac.png"),new TImage("1:/tgui_pic/mail.png"), "button", &user);
	// app.show();
	
	//TCheckBox chck(50,50,150,30,"check1", &user);
	TCheckBox chck1(new TRect(50,50,150,30),new TImage("1:/tgui_pic/check.png"),new TImage("1:/tgui_pic/check_sel.png"),"check1", &user);
	
	
	
	// TSlider slider1(100, 350, 300, 30,NULL, &user,true);
	// TSlider slider11(100, 400, 300, 30,NULL, &user,true);
	// TSlider slider12(100, 440, 300, 30,NULL, &user,true);
	// TSlider slider2(700, 100, 30, 300, NULL, &user,false);	
	// TLabel label1(400, 350, 50, 30, "0", &user);
	
	TDialog dialog1(300, 50, 250, 200, "dialog", &user);
	TLabel label2(315, 100, 190, 50, "hello world", &dialog1);
	TDialog dialog2(350, 150, 250, 200, "dialog", &user);
 	TPushButton btn1(410, 200, new TImage("1:/tgui_pic/button3.png"),new TImage("1:/tgui_pic/button_pre.png"),"btn",&dialog2);
	
	//TPushButton btn2(50,220,new TImage("1:/tgui_pic/imac.png"),new TImage("1:/tgui_pic/mail.png"), "button", &user);

	btn2.connect((func)(&TPushButton::sig_release), &chck1,(func)(&TCheckBox::sig_release));
	//slider1.connect((func)(&TSlider::sig_valueChange), &label1, (func)(&TLabel::slot_showValue));

	app.show(); 
	app.run();
}
