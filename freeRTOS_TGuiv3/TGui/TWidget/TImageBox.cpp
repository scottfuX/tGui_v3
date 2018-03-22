#include "TWidget/TImageBox.h"


TImageBox::TImageBox(int32 x, int32 y,TImage* img, const char* name, TWidget* obj)
	:TWidget(x, y, img->imgW(),img->imgH(), name, obj)
{
     img->ImgLoad(0,0,getBuffer());
     delete img;
}

TImageBox::~TImageBox()
{

}


void TImageBox::show()
{
    TBufPainter p(getBuffer()->getBufAddr(),getRect());
    p.drawCenterEnText(0,0,getRect()->width(),getRect()->height(),getName());
    refresh();
}

