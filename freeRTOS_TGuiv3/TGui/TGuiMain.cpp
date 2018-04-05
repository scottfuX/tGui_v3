#include "tGuiMain.h"


void TGuiRun()
{
	// 主要的几个问题需要解决
	//1.多线程 
	TTouchDirver dirve;
	TApplication app(&dirve);


	Desktop desk("1:/tgui_pic/desk1.jpg",&app);
	app.addWindow(&desk);
	
	// UserPhoto userphoto("1:/tgui_pic/desk2.jpg",NULL,NULL);
	// app.addWindow(&userphoto);
	// User user("1:/tgui_pic/back2.jpg",&app,"user");
	// app.addWindow(&user);

	app.show(); 
	app.run();
}
