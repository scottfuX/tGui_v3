#include "tGuiMain.h"

void tGuiRun()
{
	tTouchDirver dirve;
	tString str = "h";
	User user(&str,0);
	tApplication app(&user, &dirve);
	tPushButton btn(300,220,220,80, "hellobtn");
	tCheckBox chck1(100,50,150,30,"check1");
	tRadioButton radio1(100, 100, 150, 30, "radio1");
	tRadioButton radio2(100, 140, 150, 30, "radio2");
	tRadioButton radio3(100, 180, 150, 30, "radio3");
	tSlider slider(100,350,300,30,NULL);
	radio1.addNextRadio(&radio2);
	radio2.addNextRadio(&radio3);
	btn.connect((func)(&tPushButton::sig_release), &chck1, (func)(&tCheckBox::sig_release));
	app.add(&btn, &user);
	app.add(&radio1, &user);
	app.add(&radio2, &user);
	app.add(&radio3, &user);
	app.add(&chck1, &user);
	app.add(&slider, &user);
	app.show();
	app.run();
}