#include "demo/UserTime.h"

UserTime::UserTime(int32 x,int32 y,TImage* img,const char* n, TWidget* obj,int offset)
	:TDialog(x,y,img,n,obj,offset)
{
    timeLabel = new TLabel(265,261,269,45,"13:05:55",this,ALIGN_CENTER,false,WHITE);
}

UserTime::~UserTime()
{
    
}


void UserTime::show()
{
	refresh();
}



