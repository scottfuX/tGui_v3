#include "demo/UserPhoto.h"

UserPhoto::UserPhoto(const char* filename,TApplication* app,const char* n, TWidget* obj)
	:TWindow(filename,app,n,obj)
{
	
    left_btn = new TPushButton(100,400,TImage("1:/tgui_pic/button.png"),TImage("1:/tgui_pic/button_sel.png"),"上一个", this);
    right_btn = new TPushButton(600,400,TImage("1:/tgui_pic/button.png"),TImage("1:/tgui_pic/button_sel.png"),"下一个", this);
	
    right_btn->connect((func)(&TPushButton::sig_release),this,(func)(&UserPhoto::slot_close));
}

UserPhoto::~UserPhoto() 
{
	delete left_btn;
    delete right_btn;
}

void UserPhoto::show()
{
	refresh();
}


