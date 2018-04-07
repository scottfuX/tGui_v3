#include "demo/UserGame.h"

UserGame::UserGame(const char* filename,TApplication* app,const char* n, TWidget* obj)
	:TWindow(filename,app,n,obj)
{
    win_dialog = NULL; 
    lose_dialog = NULL;
    close_btn = new TPushButton(710,20,new TImage("1:/game_pic/Bt_continue.png"),NULL,NULL, this);
    left_btn = new TPushButton(10,345,new TImage("1:/game_pic/Sword.png"),NULL,NULL, this);
    right_btn = new TPushButton(660,345,new TImage("1:/game_pic/Shield.png"),NULL,NULL, this);
	

    close_btn->connect((func)(&TPushButton::sig_release),this,(func)(&UserGame::closeGame));
    left_btn->connect((func)(&TPushButton::sig_release),this,(func)(&UserGame::attack));
    right_btn->connect((func)(&TPushButton::sig_release),this,(func)(&UserGame::defend));
    					    
}

UserGame::~UserGame()
{
    delete win_dialog;
    delete lose_dialog;
}

void UserGame::attack()
{
    if(!win_dialog)
    {
       // delete calcu_dialog; 
        TImageBox* imgbox = new TImageBox(370,195,new TImage("1:/tgui_pic/wait.png"),2,NULL,this);
        imgbox->showAll();
        delete imgbox;
        win_dialog = new TDialog(200, 50, new TImage("1:/game_pic/Win_dialog.png"), NULL,this,70);
        TPushButton* repeat_btn = new TPushButton(367,202,new TImage("1:/game_pic/Bt_repeat.png"),NULL,NULL, win_dialog);
        repeat_btn->connect((func)(&TPushButton::sig_release),this,(func)(&UserGame::closeWinDialog));
        win_dialog->showAll();
    }
}

void UserGame::closeWinDialog()
{
    getApp()->setSignal(win_dialog,Event_Close);
    win_dialog = NULL;
}

void UserGame::defend()
{
    if(!lose_dialog)
    {
       // delete calcu_dialog; 
        TImageBox* imgbox = new TImageBox(370,195,new TImage("1:/tgui_pic/wait.png"),2,NULL,this);
        imgbox->showAll();
        delete imgbox;
        lose_dialog = new TDialog(230, 80, new TImage("1:/game_pic/Loose_dialog.png"), NULL, this,70);
        TPushButton* repeat_btn = new TPushButton(364,205,new TImage("1:/game_pic/Bt_repeat.png"),NULL,NULL, lose_dialog);
        repeat_btn->connect((func)(&TPushButton::sig_release),this,(func)(&UserGame::closeLoseDialog));
        lose_dialog->showAll();
    }
}
void UserGame::closeLoseDialog()
{
    getApp()->setSignal(lose_dialog,Event_Close);
    lose_dialog = NULL;
}

void UserGame::closeGame()
{
    
    slot_close();
}


void UserGame::show()
{
	refresh();
}


