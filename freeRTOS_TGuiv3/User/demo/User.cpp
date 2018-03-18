#include "demo\User.h"



User::User(int32 x, int32 y, int32 w, int32 h,const char* n, TWidget* obj):TWidget(x,y,w,h,n,obj)
{
	TBufPainter p(getBuffer()->getBufAddr(),getRect());
	p.setColors(GOLD, GOLD);
	p.drawFullRect(0,0,w,h); //这个的锅。。。//太简单粗暴了  导致把头数据都覆盖了 以至于后面分配内存又覆盖上去了
}

void User::show()
{
	//TPainter p(getInvalidList(), getPaintInvaild());
	refresh();
}

