#include "TWidget/TIconButton.h"



TIconButton::TIconButton(int32 x, int32 y,TImage norImg ,TImage selImg ,  const char* name, TWidget* obj)
	:TAbstractButton(x, y,MAX(norImg.imgW() ,selImg.imgW()),MAX(norImg.imgH() ,selImg.imgH()) + TFON_HEIGHT,true, name, obj)
{
	norImg.ImgLoad(0,0,norBuf);
	selImg.ImgLoad(0,0,selBuf);

	TBufPainter p1(norBuf->getBufAddr(),getRect());
	p1.drawCenterText(0,MAX(norImg.imgH() ,selImg.imgH()), width(), TFON_HEIGHT, getName());
	TBufPainter p2(selBuf->getBufAddr(),getRect());
	p2.drawCenterText(0,MAX(norImg.imgH() ,selImg.imgH()), width(), TFON_HEIGHT, getName());
}

TIconButton::~TIconButton() 
{
};

void TIconButton::sig_depress(int32 d1, int32 d2)
{
	
    setBuffer(selBuf);
    refresh();

	state = true;
	callSlot((func)&TIconButton::sig_depress,d1,d2);
}

void TIconButton::sig_release(int32 d1, int32 d2)
{
	
    setBuffer(norBuf);
    refresh();

	state = false;
	callSlot((func)&TIconButton::sig_release,d1,d2);
}

void TIconButton::release()
{
	
    setBuffer(norBuf);
    refresh();
	
	state = false;
}

void TIconButton::show()
{
	refresh();
}
