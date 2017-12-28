#include "tGuiMain.h"

void tGuiRun()
{
	tTouchDirver dirve;
	User user("user",NULL);
	user.setBackColor(GOLD);
	tApplication app(&user, &dirve);
	tDialog dialog1(350, 50, 250, 200, "dialog");
	tPushButton btn(100,230,150,65, "button");
	tCheckBox chck1(100,50,150,30,"check1");
	tRadioButton radio1(100, 100, 150, 30, "radio1");
	tRadioButton radio2(100, 140, 150, 30, "radio2");
	tRadioButton radio3(100, 180, 150, 30, "radio3");
	tSlider slider1(100, 350, 300, 30, NULL, true);
	tSlider slider2(700, 100, 30, 300, NULL, false);
	tLabel label1(400, 350, 50, 30, "0", &user);
	radio1.addNextRadio(&radio2);
	radio2.addNextRadio(&radio3);
	btn.connect((func)(&tPushButton::sig_release), &chck1,(func)(&tCheckBox::sig_release));
	slider1.connect((func)(&tSlider::sig_valueChange), &label1, (func)(&tLabel::slot_showValue));
	app.add(&dialog1, &user);
	app.add(&btn, &user);
	app.add(&radio1, &user);
	app.add(&radio2, &user);
	app.add(&radio3, &user);
	app.add(&chck1, &user);
	app.add(&slider1, &user);
	app.add(&slider2, &user);
	app.add(&label1, &user);
	app.show();
	app.run();
}