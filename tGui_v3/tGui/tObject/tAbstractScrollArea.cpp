#include "tObject/tAbstractScrollArea.h"



tAbstractScrollArea::tAbstractScrollArea(int32 x, int32 y, int32 w, int32 h, const char* n, tWidget* obj)
	:tFrame(x,y,w,h,n,obj)
{
	scrollH = NULL;
	scrollV = NULL;
}


tAbstractScrollArea::~tAbstractScrollArea()
{
	delete scrollH;
	delete scrollV;
}

//真实宽度，真实高度，滚动条的短长度，是否有水平滚动条，是否有竖直滚动条
void tAbstractScrollArea::showScroll(int32 realW, int32 realH, int32 scrollSize, bool hasH, bool hasV)
{
	//水平滚动条
	if (hasH)
	{
		scrollH = new tScrollBar(x(), y(), width(), scrollSize, NULL, this, true);
		if (realW > width())
			scrollH->setRealLen(width()*width() / realW);
		else
			scrollH->setRealLen(width());
	}
	
	//竖直滚动条
	if (hasV)
	{
		scrollV = new tScrollBar(x(), y(), scrollSize, height(), NULL, this, true);
		if (realH > height())
			scrollH->setRealLen(height()*height() / realH);
		else
			scrollH->setRealLen(height());
	}
}