#include "tGuiMain.h"

void tGuiRun()
{
	tTouchDirver dirve;
	tString str = "h";
	User user(&str,0);
	tApplication app(&user, &dirve);
	tPushButton btn;
	btn.setX(300);
	btn.setY(200);
	btn.setH(80);
	btn.setW(200);
	btn.setName("hellobtn");
	btn.connect((func)(&tPushButton::depress_sig), &user, (func)(&User::slot));
	btn.connect((func)(&tPushButton::release_sig),&user ,(func)(&User::slot2));
	btn.connect((func)(&tPushButton::release_sig), &user, (func)(&User::slot1));
	app.add(&btn, &user);
	app.show();
	app.run();
}