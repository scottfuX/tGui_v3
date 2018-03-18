#include "tGuiMain.h"

void TGuiRun()
{
	// 主要的几个问题需要解决
	//1.多线程
	//2.贴图问题 --- 解决了一半 已经有了button
	TTouchDirver dirve;
	User user(0,0,800,480,"user",NULL);
	user.setBackColor(GOLD);
	TApplication app(&user, &dirve);
	TPushButton btn(100,230,150,65, "button", &user);
	TPushButton btn2(400,230,150,65, "button", &user);
	TCheckBox chck1(100,50,150,30,"check1", &user);
	TRadioButton radio1(100, 100, 150, 30, "radio1", &user);
	TRadioButton radio2(100, 140, 150, 30, "radio2", &user);
	TRadioButton radio3(100, 180, 150, 30, "radio3", &user);
	radio1.addNextRadio(&radio2);
	radio2.addNextRadio(&radio3);
	TSlider slider1(100, 350, 300, 30,NULL, &user,true);
	TSlider slider11(100, 400, 300, 30,NULL, &user,true);
	TSlider slider12(100, 440, 300, 30,NULL, &user,true);
	TSlider slider2(700, 100, 30, 300, NULL, &user,false);

	TLabel label1(400, 350, 50, 30, "0", &user);
	TDialog dialog1(300, 50, 250, 200, "dialog", &user);
	TLabel label2(315, 100, 190, 50, "hello world", &dialog1);
	TDialog dialog2(350, 150, 250, 200, "dialog", &user);
	TPushButton btn1(410, 200, 130, 65, "btn",&dialog2);

	btn.connect((func)(&TPushButton::sig_release), &chck1,(func)(&TCheckBox::sig_release));
	slider1.connect((func)(&TSlider::sig_valueChange), &label1, (func)(&TLabel::slot_showValue));

	app.show(); 
	app.run();
}
