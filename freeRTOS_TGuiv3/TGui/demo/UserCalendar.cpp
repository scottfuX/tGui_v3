#include "demo/UserCalendar.h"

UserCalendar::UserCalendar(int32 x,int32 y,TImage* img,const char* n, TWidget* obj,int offset)
	:TDialog(x,y,img,n,obj,offset)
{
    dateContext = new TImageBox(300,207,new TImage("1:/calender_pic/day_numbers.png"),NULL,this);
    leftArrow = new TPushButton(296,137,new TImage("1:/calender_pic/left_arrow.png"),NULL,NULL,this);
    rightArrow =  new TPushButton(296,137,new TImage("1:/calender_pic/right_arrow.png"),NULL,NULL,this);
    //dateLabel = new TLabel(331,132,125,27,"2018Äê5ÔÂ",this,ALIGN_CENTER,false,WHITE);
			    
    leftArrow->connect((func)(&TPushButton::sig_release),this,(func)(&UserCalendar::prevMonth));
    rightArrow->connect((func)(&TPushButton::sig_release),this,(func)(&UserCalendar::nextMonth));
}

UserCalendar::~UserCalendar()
{
    
}

void UserCalendar::prevMonth()
{

}

void UserCalendar::nextMonth()
{

}

void UserCalendar::show()
{
	refresh();
}



