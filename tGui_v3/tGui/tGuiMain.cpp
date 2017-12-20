#include "tGuiMain.h"

void tGuiRun()
{
	tTouchDirver dirve;
	tString str = "hello";
	User user(&str,0);
	tApplication app(&user,&dirve);
	tPushButton btn;
	btn.setX(300);
	btn.setY(200);
	btn.setH(50);
	btn.setW(100);
	btn.regist(&user);
	//app.add(&btn,&user);
	app.run();
}