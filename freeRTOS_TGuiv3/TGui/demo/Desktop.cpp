#include "demo/Desktop.h"

Desktop::Desktop(const char* filename,TApplication* app,const char* n, TWidget* obj)
	:TWindow(filename,app,n,obj)
{
	set_dialog = NULL;
    calcu_dialog = NULL;
    date_dialog = NULL;
    timer_dialog = NULL;
    currWinId = 0;

    icon_clock = new TIconButton(20,40,new TImage("1:/tgui_pic/clock.png"),NULL/*new TImage("1:/tgui_pic/clock2.png")*/,"时间",this);
    icon_date = new TIconButton(222,45,new TImage("1:/tgui_pic/date.png"),NULL/*new TImage("1:/tgui_pic/date2.png")*/,"日历",this);
    icon_setting = new TIconButton(409,40,new TImage("1:/tgui_pic/setting.png"),NULL/*new TImage("1:/tgui_pic/setting2.png")*/,"设置",this);
    icon_calculator = new TIconButton(599,45,new TImage("1:/tgui_pic/calculator.png"),NULL/*new TImage("1:/tgui_pic/calculator2.png")*/,"计算器",this);
    
    icon_photo = new TIconButton(20,260,new TImage("1:/tgui_pic/photo.png"),NULL /*new TImage("1:/tgui_pic/photo2.png")*/,"照片",this);
    icon_play = new TIconButton(245,260,new TImage("1:/tgui_pic/play.png"),NULL /*new TImage("1:/tgui_pic/play2.png")*/,"播放器",this);
    icon_search = new TIconButton(420,260,new TImage("1:/tgui_pic/search.png"),NULL/*new TImage("1:/tgui_pic/search2.png")*/,"搜索",this);
    icon_game = new TIconButton(599,260,new TImage("1:/tgui_pic/imac.png"),NULL/*new TImage("1:/tgui_pic/weather2.png")*/,"游戏",this);
	
    icon_clock->connect((func)(&TIconButton::sig_release),this,(func)(&Desktop::openTimer));
    icon_date->connect((func)(&TIconButton::sig_release),this,(func)(&Desktop::openDate));
    icon_setting->connect((func)(&TIconButton::sig_release),this,(func)(&Desktop::openSetup));
    icon_calculator->connect((func)(&TIconButton::sig_release),this,(func)(&Desktop::openCalculate));
    icon_photo->connect((func)(&TIconButton::sig_release),this,(func)(&Desktop::openPhoto));
	icon_game->connect((func)(&TIconButton::sig_release),this,(func)(&Desktop::openGame));
    icon_search->connect((func)(&TIconButton::sig_release),this,(func)(&Desktop::openUser));
    
}

Desktop::~Desktop() 
{
}

void Desktop::show()
{
    createIcon();
	refresh();
    currWinId = 0;
}

void Desktop::openSetup()
{
    if(!set_dialog)
    {
       // delete calcu_dialog; 
        TImageBox* imgbox = new TImageBox(370,195,new TImage("1:/tgui_pic/wait.png"),2,NULL,this);
        imgbox->show();
        delete imgbox;

        set_dialog = new TDialog(250, 100, new TImage("1:/tgui_pic/dialog.png"), "设置", this,55);
	    TPushButton*  btn1 = new TPushButton(292, 234, new TImage("1:/tgui_pic/dialog_btn1.png"),new TImage("1:/tgui_pic/dialog_btn1_sel.png"),"确定",set_dialog);
	    TPushButton*  btn2 = new TPushButton(442, 234,new TImage("1:/tgui_pic/dialog_btn2.png"),new TImage("1:/tgui_pic/dialog_btn2_sel.png"),"取消",set_dialog);
        btn1->connect((func)(&TPushButton::sig_release),this,(func)(&Desktop::closeSetup));
        set_dialog->showAll();
    }
}

void Desktop::closeSetup()
{
    getApp()->setSignal(set_dialog,Event_Close);
    set_dialog = NULL;
}

void Desktop::openCalculate()
{
    if(!calcu_dialog)
    {
        //delete date_dialog;
        //delete set_dialog; //把其他的dialog删掉
        TImageBox* imgbox = new TImageBox(370,195,new TImage("1:/tgui_pic/wait.png"),2,NULL,this);
        imgbox->show();
        delete(imgbox);

        calcu_dialog = new UserCalculate(224,17,new TImage("1:/calculate_pic/calculator.png"),NULL,this,65);
        calcu_dialog->showAll();
    }
    else//再按一下 就删除
    {
        delete calcu_dialog;
        calcu_dialog = NULL;
        showAll();
    }
}


void Desktop::openDate()
{
    if(!date_dialog)
    {
        //delete calcu_dialog; 
        TImageBox* imgbox = new TImageBox(370,195,new TImage("1:/tgui_pic/wait.png"),2,NULL,this);
        imgbox->show();//showAll();
        delete(imgbox);

        date_dialog = new UserCalendar(271,118,new TImage("1:/calendar_pic/calendar.png"),NULL,this,55);
        date_dialog->showAll();
    }
    else//再按一下 就删除
    {
        delete date_dialog;
        date_dialog = NULL;
        showAll();
    }
}   

void Desktop::openTimer()
{
    if(!timer_dialog)
    {
        TImageBox* imgbox = new TImageBox(370,195,new TImage("1:/tgui_pic/wait.png"),2,NULL,this);
        imgbox->show();
        delete(imgbox);

        timer_dialog = new UserTime(225,116,new TImage("1:/time_pic/time_dialog.png"),NULL,this,55);
        timer_dialog->showAll();
    }
    else//再按一下 就删除
    {
        delete timer_dialog;
        timer_dialog = NULL;
        showAll();
    }
}

void Desktop::openGame()
{
    TImageBox* imgbox = new TImageBox(370,195,new TImage("1:/tgui_pic/wait.png"),2,NULL,this);
    imgbox->show();
    delete(imgbox);

    currWinId = (0x0080 ^ 0xffff);
    deleteIcon();
    //---开启游戏窗口-----
    UserGame* usergame = new UserGame("1:/game_pic/GameBack.jpg",getApp());
    getApp()->setSignal(usergame,Event_Show);
}

void Desktop::openUser()
{
    TImageBox* imgbox = new TImageBox(370,195,new TImage("1:/tgui_pic/wait.png"),2,NULL,this);
    imgbox->show();
    delete(imgbox);

    //deleteIcon();

    //---开启游戏窗口-----
    User* user = new User("1:/tgui_pic/desk2.jpg",getApp());
    getApp()->setSignal(user,Event_Show);
}

void Desktop::openPhoto()
{
    TImageBox* imgbox = new TImageBox(370,195,new TImage("1:/tgui_pic/wait.png"),2,NULL,this);
        imgbox->show();
    delete(imgbox);

    //deleteIcon();

    UserPhoto* userphoto = new UserPhoto("1:/tgui_pic/back3.jpg",getApp());
    getApp()->setSignal(userphoto,Event_Show);
}

void Desktop::createIcon()
{
    if(!currWinId)
        return;
    //uint16 tmp = currWinId ^ 0xffff;
    uint16 tmp = currWinId;
    if((tmp & 0x0001)==0x0001)
    {
        icon_clock = new TIconButton(20,40,new TImage("1:/tgui_pic/clock.png"),NULL/*new TImage("1:/tgui_pic/clock2.png")*/,"时间",this);
        icon_clock->connect((func)(&TIconButton::sig_release),this,(func)(&Desktop::openTimer));
    }
    if((tmp & 0x0002)==0x0002)
    {
        icon_date = new TIconButton(222,45,new TImage("1:/tgui_pic/date.png"),NULL/*new TImage("1:/tgui_pic/date2.png")*/,"日历",this);
        icon_date->connect((func)(&TIconButton::sig_release),this,(func)(&Desktop::openDate));
    }
    if((tmp & 0x0004)==0x0004)
    {
        icon_setting = new TIconButton(409,40,new TImage("1:/tgui_pic/setting.png"),NULL/*new TImage("1:/tgui_pic/setting2.png")*/,"设置",this);
        icon_setting->connect((func)(&TIconButton::sig_release),this,(func)(&Desktop::openSetup));
    }
    if((tmp & 0x0008)==0x0008)
    {
        icon_calculator = new TIconButton(599,45,new TImage("1:/tgui_pic/calculator.png"),NULL/*new TImage("1:/tgui_pic/calculator2.png")*/,"计算器",this);
        icon_calculator->connect((func)(&TIconButton::sig_release),this,(func)(&Desktop::openCalculate));
    }

   if((tmp & 0x0010)==0x0010)
    {
        icon_photo = new TIconButton(20,260,new TImage("1:/tgui_pic/photo.png"),NULL /*new TImage("1:/tgui_pic/photo2.png")*/,"照片",this);
        icon_photo->connect((func)(&TIconButton::sig_release),this,(func)(&Desktop::openPhoto));
    }
    if((tmp & 0x0020)==0x0020)
    {
        icon_play = new TIconButton(245,260,new TImage("1:/tgui_pic/play.png"),NULL /*new TImage("1:/tgui_pic/play2.png")*/,"播放器",this);
    }
    if((tmp & 0x0040)==0x0040)
    {
        icon_search = new TIconButton(420,260,new TImage("1:/tgui_pic/search.png"),NULL/*new TImage("1:/tgui_pic/search2.png")*/,"搜索",this);
        icon_search->connect((func)(&TIconButton::sig_release),this,(func)(&Desktop::openUser));
    }
    if((tmp & 0x0080)==0x0080)
    {
        icon_game = new TIconButton(599,260,new TImage("1:/tgui_pic/imac.png"),NULL/*new TImage("1:/tgui_pic/weather2.png")*/,"游戏",this);
        icon_game->connect((func)(&TIconButton::sig_release),this,(func)(&Desktop::openGame));
    }
}

void Desktop::deleteIcon()
{
    if(!currWinId)
        return;
    //uint16 tmp = currWinId ^ 0xffff;
    uint16 tmp = currWinId;
    if((tmp & 0x0001)==0x0001)
    {
        delete( icon_clock);
        icon_clock = NULL;
    }
    if((tmp & 0x0002)==0x0002)
    {
        delete( icon_date );
        icon_date = NULL;
    }
    if((tmp & 0x0004)==0x0004)
    {
        delete( icon_setting);
        icon_setting = NULL;
    }
    if((tmp & 0x0008)==0x0008)
    {
        delete( icon_calculator) ;
        icon_calculator = NULL;
    }
    if((tmp & 0x0010)==0x0010)
    {
        delete( icon_photo) ;
        icon_photo = NULL;
    }
    if((tmp & 0x0020)==0x0020)
    {
        delete( icon_play) ;
        icon_play = NULL;
    }
    if((tmp & 0x0040)==0x0040)
    {
        delete( icon_search) ;
        icon_search = NULL;
    }
    if((tmp & 0x0080)==0x0080)
    {
        delete( icon_game) ;
        icon_game = NULL;
    } 
}








