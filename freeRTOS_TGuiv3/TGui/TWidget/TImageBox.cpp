#include "TWidget/TImageBox.h"


TImageBox::TImageBox(int32 x, int32 y,TImage* img, const char* name, TWidget* obj)
	:TWidget(x, y, img->imgW(),img->imgH(), name, obj)
{
    img->ImgLoad(0,0,getBuffer());
    delete img;
    TBufPainter p(getBuffer()->getBufAddr(),getRect());
    p.drawCenterEnText(0,0,getRect()->width(),getRect()->height(),getName());
}

TImageBox::TImageBox(int32 x, int32 y,uint16 w,uint16 h,const char* filename, const char* name, TWidget* obj)
    :TWidget(x, y, w , h, name, obj)
{
    TImage img(getBuffer(), w, h, filename);
    TBufPainter p(getBuffer()->getBufAddr(),getRect());
    p.drawCenterEnText(0,0,getRect()->width(),getRect()->height(),getName());
}

TImageBox::~TImageBox()
{

}


void TImageBox::show()
{
   
    refresh();
}

