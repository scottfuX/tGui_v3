#include "demo\User.h"



User::User(int32 x, int32 y, int32 w, int32 h, const char* n,TWidget* obj)
	:TWidget(x,y,w,h,n,obj)
{
	TBufPainter p(getBuffer()->getBufAddr(),getRect());
	p.setColors(GOLD, GOLD);
	p.drawFullRect(0,0,w,h); 
}

User::User(int32 x, int32 y, int32 w, int32 h,const char* filename,const char* n, TWidget* obj)
	:TWidget(x,y,w,h,n,obj)
{
	TImage img(getBuffer(), w, h, filename);
}

User::User(int32 x, int32 y,TImage img,const char* n, TWidget* obj)
	:TWidget(x,y,img.imgW(),img.imgH(),n,obj)
{
	img.ImgLoad(0,0,getBuffer());
}

void User::show()
{
	//TPainter p(getInvalidList(), getPaintInvaild());
	refresh();
}

