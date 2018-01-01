#include "tGuiMain.h"

void tGuiRun()
{
	tTouchDirver dirve;
	User user("user",NULL);
	user.setBackColor(GOLD);
	tApplication app(&user, &dirve);
	tDialog dialog1(350, 50, 250, 200, "dialog", &user);
	tDialog dialog2(400, 150, 250, 200, "dialog", &user);
	tPushButton btn(100,230,150,65, "button", &user);
	tCheckBox chck1(100,50,150,30,"check1", &user);
	tRadioButton radio1(100, 100, 150, 30, "radio1", &user);
	tRadioButton radio2(100, 140, 150, 30, "radio2", &user);
	tRadioButton radio3(100, 180, 150, 30, "radio3", &user);
	tSlider slider1(100, 350, 300, 30,NULL, &user,true);
	tSlider slider2(700, 100, 30, 300, NULL, &user, false);
	tLabel label1(400, 350, 50, 30, "0", &user);
	tPushButton btn1(450, 200, 130, 65, "btn",&dialog2);
	radio1.addNextRadio(&radio2);
	radio2.addNextRadio(&radio3);
	btn.connect((func)(&tPushButton::sig_release), &chck1,(func)(&tCheckBox::sig_release));
	slider1.connect((func)(&tSlider::sig_valueChange), &label1, (func)(&tLabel::slot_showValue));
	tLabel label2(355, 100, 190,50, "I LOVE U", &dialog1);
	app.show(); 
	app.run();
}