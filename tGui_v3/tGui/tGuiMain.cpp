#include "tGuiMain.h"

void tGuiRun()
{
	tTouchDirver dirve;
	User user("h123",NULL);
	tApplication app(&user, &dirve);
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
	btn.connect((func)(&tPushButton::sig_release), &chck1, (func)(&tCheckBox::sig_release));
	slider1.connect((func)(&tSlider::sig_move), &label1, (func)(&tLabel::slot_showValue));
	app.add(&btn, &user);
	app.add(&radio1, &user);
	app.add(&radio2, &user);
	app.add(&radio3, &user);
	app.add(&chck1, &user);
	app.add(&slider1, &user);
	app.add(&slider2, &user);
	app.show();
	tPainter p;
	p.drawRect(400,150,200,200);
	p.drawTriangle(400,250,500,150+1,600, 250);
	p.drawCircle(500 , 250 , 100);
	p.drawEllipse(500, 250, 100, 50);
	app.run();
}