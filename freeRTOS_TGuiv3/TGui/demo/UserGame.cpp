#include "demo/UserGame.h"

UserGame::UserGame(const char* filename,TApplication* app,const char* n, TWidget* obj)
	:TWindow(filename,app,n,obj)
{
    close_btn = new TPushButton(710,20,new TImage("1:/game_pic/Bt_continue.png"),NULL,NULL, this);
    left_btn = new TPushButton(10,345,new TImage("1:/game_pic/Sword.png"),NULL,NULL, this);
    right_btn = new TPushButton(660,345,new TImage("1:/game_pic/Shield.png"),NULL,NULL, this);
	

    close_btn->connect((func)(&TPushButton::sig_release),this,(func)(&UserGame::closeGame));
    					    
}

UserGame::~UserGame()
{
    
}



void UserGame::closeGame()
{
    
    slot_close();
}


void UserGame::show()
{
	refresh();
}


